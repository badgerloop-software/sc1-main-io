#include "can.h"

#include <errno.h>
#include <net/if.h>
#include <poll.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <csignal>
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
    std::cout << "ERROR: Could not locate CAN bus";
    return -1;
  }

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    std::cout << "ERROR: Error binding address to socket\n";
    return -1;
  }

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

void Can::add(vector<callback> &callbacks) {
  lock_guard<mutex> l(mu);

  // theoretically moves callback memory into hashtable
  for (callback &c : callbacks) callback_map.emplace(std::move(c));
  callbacks.clear();  // invalidate local callbacks
}

void Can::loop() {
  struct can_frame msg;
  struct pollfd fd = {sock, POLLIN};

  while (isInit) {
    int ret = poll(&fd, 1, 200);  // check isInit every 200ms but immediately
                                  // return if message is on the socket
    if (ret > 0) {
      if (read(msg) < 0)  // not good. Try to re-initialize
        break;
      // const iterator is gross, use auto
      auto pair = callback_map.find(msg.can_id);
      if (pair != callback_map.end()) (*pair).second(msg);  // execute function
    }
  }

  isInit = false;  // will retry on next r/w
  close(sock);
}

Can::~Can() {
  isInit = false;
  if (t.joinable()) t.join();
}
