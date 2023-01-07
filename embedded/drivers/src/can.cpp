#include "can.h"

#include <errno.h>
#include <net/if.h>
#include <poll.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

Can::Can(const char *can_i) : can_i(can_i) {}

/*
Initialize canbus
Returns 0 on success, -1 on failure
*/
int Can::init() {
  if (isInit) return 0;

  lock_guard<mutex> l(mu);

  struct ifreq ifr;
  struct sockaddr_can addr;

  sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  strcpy(ifr.ifr_name, can_i);

  if (ioctl(sock, SIOCGIFINDEX, &ifr)) {
    std::cerr << "Error: Could not locate CAN bus\n";
    return -1;
  }

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    std::cerr << "Error: Error binding address to socket\n";
    return -1;
  }

  if (pipe(pfd) < 0) return -1;

  isInit = true;

  t = thread(&Can::loop, this);

  return 0;
}

/*
Reads from CAN bus
Returns number of bytes read or -1 on failure
*/
int Can::read(struct can_frame &msg) {
  if (init() < 0) return -1;

  lock_guard<mutex> l(mu);

  return recv(sock, &msg, sizeof(struct can_frame), MSG_DONTWAIT);
}

/*
Sends a CAN frame to the CAN bus.
Returns number of bytes sent or -1 on failure
*/
int Can::send(int id, uint8_t *data, uint8_t size) {
  if (init() < 0 || size > CAN_MAX_DLEN) return -1;

  lock_guard<mutex> l(mu);

  struct can_frame msg;
  msg.can_dlc = size;
  msg.can_id = id;
  memcpy(msg.data, data, msg.can_dlc);

  return ::send(sock, &msg, sizeof(struct can_frame), MSG_DONTWAIT);
}

void Can::add(const vector<callback> &callbacks) {
  lock_guard<mutex> l(mu);

  callback_map.insert(callbacks.begin(), callbacks.end());
}

void Can::loop() {
  struct can_frame msg;
  // poll both socket and pipe for end condition
  struct pollfd fds[2] = {{sock, POLLIN}, {pfd[0], POLLIN}};

  while (isInit) {
    int ret = poll(fds, 2, -1);  // wait indefinitely for message on any fd
    // only check socket for message
    if (ret > 0 && fds[0].revents & POLLIN) {
      if (read(msg) < 0) break;  // not good. Try to re-initialize
      auto pair = callback_map.find(msg.can_id);
      if (pair != callback_map.end()) (*pair).second(msg);  // execute function
    }
  }

  lock_guard<mutex> l(mu);

  close(sock);
  close(pfd[0]);
  close(pfd[1]);
  isInit = false;  // make sure not init (failures within thread)
                   // will retry on next r/w
}

Can::~Can() {
  {
    lock_guard<mutex> l(mu);
    isInit = false;
    write(pfd[1], "\0", 1);  // stop loop
  }
  if (t.joinable()) t.join();
}
