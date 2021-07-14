#include "can.h"

#include <stdio.h>       // for printf
#include <sys/ioctl.h>   // for ioctl, SIOCGIFINDEX
#include <sys/socket.h>  // for bind, recv, send, socket, MSG_DONTWAIT
#include <unistd.h>      // for usleep

#include <cstring>  // for strcpy

CANDevice::CANDevice(CAN* c) : can(c) { c->devices.push_back(this); }

void CANDevice::canDeviceLoop() {
  while (1) {
    if (this->messages.size()) {
      can_frame* can_mesg = this->messages.front();
      this->messages.pop();
      this->parser(can_mesg->can_id, can_mesg->data, NO_FILTER);
      usleep(50);
    }
  }
}

int CANDevice::begin() {
  canDeviceThread = std::thread(&CANDevice::canDeviceLoop, this);
  return 0;
}

void CAN::canLoop() {
  struct can_frame* can_mesg;
  while (1) {
    sem_wait(&canSem);
    if (!this->canRead(can_mesg)) {
      for (CANDevice* c : this->devices) {
        if (!(*c).validMsg(can_mesg)) {
          break;  // validMsg returns 0 if message was valid and added to queue
                  // else check next device validMsg
        }
      }
    }
    sem_post(&canSem);
    usleep(50);
  }
}

int CAN::begin() {
  this->socket = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
  strcpy(this->ifr.ifr_name, CAN_INTF);

  if (ioctl(this->socket, SIOCGIFINDEX, &this->ifr) == -1) {
    printf("Failed to find bus\n\r");
    return 1;
  }

  this->addr.can_family = AF_CAN;
  this->addr.can_ifindex = ifr.ifr_ifindex;
  bind(this->socket, (struct sockaddr*)&this->addr, sizeof(this->addr));

  canThread = std::thread(&CAN::canLoop, this);
  sem_init(&this->canSem, 0, 1);
  return 0;
}

int CAN::canRead(struct can_frame* recvd_msg) {
  int nBytes =
      recv(this->socket, recvd_msg, sizeof(struct can_frame), MSG_DONTWAIT);
  /* This is actually ok if it fails here, it just means no new info */
  if (nBytes < 0) {
    return 1;
  }
  return 0;
}

int CAN::canSend(uint32_t id, uint8_t* data, uint8_t size) {
  struct can_frame tx_msg;

  tx_msg.can_dlc = size;
  tx_msg.can_id = id;  // Should actually be 11 bits max
  int i;
  for (i = 0; i < size; i++) {
    tx_msg.data[i] = data[i];
  }
  send(this->socket, &tx_msg, sizeof(struct can_frame), MSG_DONTWAIT);

  return 0;  // Not much we do with error codes here
}
