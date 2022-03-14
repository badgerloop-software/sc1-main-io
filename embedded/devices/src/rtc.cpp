#include "rtc.h"

#include <errno.h>
#include <fcntl.h>

#include <chrono>
#include <iostream>
#include <numeric>

RTC::RTC(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int RTC::begin(void) {
  if (open_i2c() || write_data(SR, (BIT7 | BIT4))) return -EIO;

  std::time_t time =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::tm date = *gmtime(&time);
  if (setRTC(d2bcd(date.tm_wday), d2bcd(date.tm_year - 100),
             d2bcd(date.tm_mon + 1), d2bcd(date.tm_mday), d2bcd(date.tm_hour),
             d2bcd(date.tm_min), d2bcd(date.tm_sec > 59 ? 59 : date.tm_sec)))
    return -EIO;

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
      write_data(DT, dt) || write_data(HR, hr) || write_data(MN, mn) ||
      write_data(SC, sc))
    return -EIO;
  return 0;
}
