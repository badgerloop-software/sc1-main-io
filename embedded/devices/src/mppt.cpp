#include "mppt.h"

#include <cstdint>
#include <cstring>
#include <iostream>

int Mppt::sendMaxOutputCurrent(float moc) {
  return bus.send(MaxOutputCurrent, (uint8_t *)&moc, sizeof(moc));
}
