#include "can.h"

#include <errno.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <iostream>

/*
Initialize canbus
Returns 0 on success, -1 on failure
*/
int Can::init(const char *can_i) {
  if (this->isInit) return 0;

  lock_guard<mutex> l(mu);

  struct ifreq ifr;
  struct sockaddr_can addr;

  this->sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  strcpy(ifr.ifr_name, can_i);

  if (ioctl(this->sock, SIOCGIFINDEX, &ifr)) {
    std::cout << "ERROR: Could not locate CAN bus";
    return -1;
  }

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (!bind(this->sock, (struct sockaddr *)&addr, sizeof(addr))) {
    std::cout << "ERROR: Error binding address to socket\n";
    return -1;
  }

  this->isInit = true;

  t = thread(&Can::loop, this);

  return 0;
}

/*
Reads from CAN bus
Returns number of bytes read or -1 on failure
*/
int Can::read(struct can_frame *msg) {
  lock_guard<mutex> l(mu);
  return recv(this->sock, msg, sizeof(struct can_frame), MSG_DONTWAIT);
}

/*
Sends a CAN frame to the CAN bus.
Returns number of bytes sent or -1 on failure
*/
int Can::send(int id, uint8_t *data, uint8_t size) {
  struct can_frame msg;

  msg.len = size > CAN_MAX_DLEN ? CAN_MAX_DLEN : size;
  msg.can_id = id;

  memcpy(msg.data, data, msg.len);

  lock_guard<mutex> l(mu);
  return ::send(this->sock, &msg, sizeof(struct can_frame), MSG_DONTWAIT);
}

void Can::add(CanDevice *c) {
  lock_guard<mutex> l(mu);
  devices.push_back(c);
}

void Can::loop() {
  struct can_frame msg;
  while (isInit && read(&msg))
    for (CanDevice *d : devices)
      if (d->parse(msg) == 0) break;
  isInit = false;
}

Can::~Can() {
  isInit = false;
  t.join();
}
