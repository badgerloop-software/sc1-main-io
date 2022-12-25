#include "mppt.h"

#include <cstdint>
#include <cstring>
#include <iostream>

static vector<callback> mppt_callbacks{};  // TODO add mppt callbacks

Mppt::Mppt(Can &c) : CanDevice(c, mppt_callbacks) {}

int Mppt::sendMaxOutputCurrent(float moc) {
  return bus.send(MaxOutputCurrent, (uint8_t *)&moc, sizeof(moc));
}
