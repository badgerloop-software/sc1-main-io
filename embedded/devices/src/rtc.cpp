#include "rtc.h"

#include <fcntl.h>

RTC::RTC(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int RTC::begin(void) { return open_i2c(); }
