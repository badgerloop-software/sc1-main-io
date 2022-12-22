#include "mppt.h"

#include <cstdint>
#include <cstring>
#include <iostream>

#define MPPT_BASE_ID 0x0000

Mppt::Mppt(Can &c) : CanDevice(c) {}

int Mppt::sendMaxOutputCurrent(float moc) {
  return bus.send(MaxOutputCurrent, (uint8_t *)&moc, 4);
}

int Mppt::parse(struct can_frame &msg) {
  switch (msg.can_id) {
    case Test:
      std::cout << (char*)msg.data << std::endl;
      break;
    default:
      return -1;
  }
  return 0;
}
