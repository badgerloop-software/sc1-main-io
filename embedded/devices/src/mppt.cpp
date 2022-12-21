#include "mppt.h"
#define MPPT_BASE_ID 0x0000
#include <pthread.h>

#include <cstdint>
#include <cstring>
#include <iostream>

Mppt::Mppt(Can &c) : CanDevice(c) {}

int Mppt::sendMaxOutputCurrent(float moc) {
  return bus.send(MPPT_BASE_ID + 10, (uint8_t *)&moc, 4);
}
