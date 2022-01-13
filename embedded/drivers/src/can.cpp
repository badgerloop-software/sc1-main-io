#include "can.h"

#include <errno.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <iostream>

#define CAN_INTERFACE "can0"

int Can::init() {
  struct ifreq ifr;
  struct sockaddr_can addr;

  if (this->isInit) {
    return 0;
  }

  this->sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  strcpy(ifr.ifr_name, CAN_INTERFACE);

  if (ioctl(this->sock, SIOCGIFINDEX, &ifr)) {
    std::cout << "ERROR: Could not locate CAN bus";
    return -EIO;
  }

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (!bind(this->sock, (struct sockaddr *)&addr, sizeof(addr))) {
    std::cout << "ERROR: Error binding address to socket\n";
    return -EIO;
  }

  this->isInit = true;

  return 0;
}

/*
Reads from CAN bus
Returns number of bytes read
*/
int Can::canRead(struct can_frame *msg) {
  pthread_mutex_lock(&this->canMutex);
  int size = recv(this->sock, msg, sizeof(struct can_frame), MSG_DONTWAIT);
  pthread_mutex_unlock(&this->canMutex);

  return size;
}

/*
Writes a CAN frame to the CAN bus.
Each frame has 1 id and byte array of data that is size bytes long
*/
int Can::canSend(uint16_t id, uint8_t *data, int size) {
  struct can_frame msg;
  int i;

  msg.can_dlc = size;
  msg.can_id = id;

  for (i = 0; i < size; i++) {
    msg.data[i] = data[i];
  }

  pthread_mutex_lock(&this->canMutex);
  send(this->sock, &msg, sizeof(struct can_frame), MSG_DONTWAIT);
  pthread_mutex_unlock(&this->canMutex);

  return 0;
}
