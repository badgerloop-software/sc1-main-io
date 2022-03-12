#ifndef __rtc__h__
#define __rtc__h__

#include "i2c.h"

static constexpr unsigned char bit(int n) { return 1 << n; }
constexpr unsigned char BIT0 = bit(0);
constexpr unsigned char BIT1 = bit(1);
constexpr unsigned char BIT2 = bit(2);
constexpr unsigned char BIT3 = bit(3);
constexpr unsigned char BIT4 = bit(4);
constexpr unsigned char BIT5 = bit(5);
constexpr unsigned char BIT6 = bit(6);
constexpr unsigned char BIT7 = bit(7);

/**
 * STATUS REGISTER (SR)
 * ADDR: 07h
 *
 * BIT0: RTCF
 *  1 after total power failure
 *  0 after first valid write to RTC
 *
 * BIT1: BAT
 *  1 when enters battery backup mode
 *  0 if ARST bit or manually via SR
 *
 * BIT2: ALM
 *  1 if alarm matches RTC
 *  0 if ARST bit or manually via SR
 *
 * BIT3: reserved
 *
 * BIT4: WRTC
 *  1 to enable RTC
 *
 * BIT5: reserved
 *
 * BIT6: XTOSCB
 *  1 DISABLES crystal,
 *  allows for external signal
 *
 * BIT7: ARST
 *  1 enables reset after valid read of SR
 *  0 and user must manually reset BAT and ALM
 */
#define SR 0x7h

class RTC : private I2c {
 public:
  RTC(int bus, int addr);
  int begin(void);
};

#endif
