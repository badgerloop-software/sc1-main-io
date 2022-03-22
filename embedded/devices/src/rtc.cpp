#include "rtc.h"

#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <numeric>

RTC::RTC(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int RTC::begin(void) {
  if (open_i2c()) return -EIO;

  if ((read_from_reg(SR) ^ BIT0) & (BIT4 | BIT0)) {
    // RTC already enabled and RCTF is low
    std::tm rtc = {0};
    rtc.tm_year = bcd2d(read_from_reg(YR)) + 100;
    rtc.tm_mon = bcd2d(read_from_reg(MO) - 1);
    rtc.tm_mday = bcd2d(read_from_reg(DT));
    rtc.tm_hour = bcd2d(read_from_reg(HR) & ~BIT7);
    // Get rid of Military time BIT7
    rtc.tm_min = bcd2d(read_from_reg(MN));
    rtc.tm_sec = bcd2d(read_from_reg(SC));
    rtc.tm_wday = bcd2d(read_from_reg(DW));

    timespec t;
    t.tv_sec = mktime(&rtc);
    t.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &t);
  } else {
    if (write_data(SR, (BIT7 | BIT4))) return -EIO;

    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    std::tm date = *gmtime(&t.tv_sec);
    if (setRTC(d2bcd(date.tm_wday), d2bcd(date.tm_year - 100),
               d2bcd(date.tm_mon + 1), d2bcd(date.tm_mday), d2bcd(date.tm_hour),
               d2bcd(date.tm_min), d2bcd(date.tm_sec > 59 ? 59 : date.tm_sec)))
      return -EIO;
  }

  while (read_from_reg(SR) & BIT0) {
  }
  return 0;
}

int RTC::setAlarm(uint8_t dwa, uint8_t moa, uint8_t dta, uint8_t hra,
                  uint8_t mna, uint8_t sca, bool recur) {
  if (read_from_reg(SR) & BIT1) {
    std::cout << "Entered BBM" << std::endl;
    // reading sr clears ALM and BAT,
    // but should we error if in battery backup mode?
  }
  write_data(INT, ((recur ? BIT7 : 0x0) | BIT6));
  if (write_data(DWA, dwa) || write_data(MOA, moa) || write_data(DTA, dta) ||
      write_data(HRA, hra) || write_data(MNA, mna) || write_data(SCA, sca))
    return -EIO;
  return 0;
}

int RTC::setRTC(uint8_t dw, uint8_t yr, uint8_t mo, uint8_t dt, uint8_t hr,
                uint8_t mn, uint8_t sc) {
  if (write_data(DW, dw) || write_data(YR, yr) || write_data(MO, mo) ||
      write_data(DT, dt) || write_data(HR, (hr | BIT7)) || write_data(MN, mn) ||
      write_data(SC, sc))  // BIT7 for Military Time
    return -EIO;
  return 0;
}
