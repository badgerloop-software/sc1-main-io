#include "mppt.h"

#include <cstdint>
#include <cstring>
#include <iostream>

Mppt::Mppt(Can &c) : CanDevice(c) {}

int Mppt::sendMaxOutputCurrent(float moc) {
  return bus.send(MaxOutputCurrent, (uint8_t *)&moc, sizeof(moc));
}

int Mppt::parse(struct can_frame &msg) {
  switch (msg.can_id) {
  case Test:
    push(msg);
    break;
  default:
    return -1;
  }
  return 0;
}
