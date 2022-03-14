#ifndef __rtc__h__
#define __rtc__h__

#include "i2c.h"

static constexpr uint8_t bit(int n) { return 1 << n; }
constexpr uint8_t BIT0 = bit(0);
constexpr uint8_t BIT1 = bit(1);
constexpr uint8_t BIT2 = bit(2);
constexpr uint8_t BIT3 = bit(3);
constexpr uint8_t BIT4 = bit(4);
constexpr uint8_t BIT5 = bit(5);
constexpr uint8_t BIT6 = bit(6);
constexpr uint8_t BIT7 = bit(7);
inline uint8_t d2bcd(uint8_t dec) {
  return ((dec / 10 % 10) << 4) | (dec % 10);
}

/*
 * REAL TIME CLOCK REGISTERS
 * DEFAULT ALL: 0x0
 * BCD
 */
// Second
#define SC 0x0
// Minute
#define MN 0x1
// Hour
#define HR 0x2
// Day
#define DT 0x3
// Month
#define MO 0x4
// Year since 2000?
#define YR 0x5
// Day of Week
#define DW 0x6

/*
 * STATUS REGISTER (SR)
 * DEFAULT: 0x1
 *
 * BIT0: RTCF
 *  1 after total power failure
 *  0 after first valid write to RTC
 *
 * BIT1: BAT
 *  1 when enters BBM (Battery Backup Mode)
 *  0 if ARST bit or manually via SR
 *
 * BIT2: ALM
 *  1 if alarm matches RTC
 *  0 if ARST bit or manually via SR
 *
 * BIT4: WRTC
 *  1 to enable RTC
 *
 * BIT6: XTOSCB
 *  1 DISABLES crystal,
 *  allows for external signal
 *
 * BIT7: ARST
 *  1 enables reset after valid read of SR
 *  0 and user must manually reset BAT and ALM
 */
#define SR 0x7

/*
 * INTERRUPT CONTROL REGISTER (INT)
 * DEFAULT: 0x0
 *
 * BIT3-BIT0: FO
 *  See TABLE 4
 *
 * BIT4: FOBATB
 *  1 disables output during BBM
 *  0 enables output during BBM
 *
 * BIT5: LPMODE
 *  1 low power mode
 *  0 normal mode
 *
 * BIT6: ALME
 *  1 enables alarm
 *  0 disables alarm
 *
 * BIT7: IM
 *  1 recurring alarm
 *  0 single event alarm
 *   low until ALM bit cleared
 *   !!OUTPUT IS ACTIVE LOW!!
 */
#define INT 0x8

/*
 * ANALOG TRIMMING REGISTER (ATR)
 * DEFAULT: 0x0
 *
 * BIT5-BIT0: Trimming Registers
 *  See eq 2
 *
 * BIT7-BIT6: Battery Mode ATR Selection
 *  0x0  0.0pF
 *  0x1 -0.5pF
 *  0x2 +0.5pF
 *  0x3 +1.0pF
 *
 */
#define ATR 0xA

/*
 * DIGITAL TRIMING REGISTER (DTR)
 * DEFAULT: 0x0
 */

/* BIT2: Sign bit
 *  0 is frequency compensation > 0
 *  1 is frequency compensation < 0
 *
 * BIT1-BIT0: magnitude
 *  BIT1 adjusts 40ppm
 *  BIT0 adjusts 20ppm
 *
 */
#define DTR 0xB

/*
 * ALARM REGISTERS
 * DEFAULT ALL: 0x0
 * BCD
 */
// Second
#define SCA 0xC
// Minute
#define MNA 0xD
// Hour
#define HRA 0xE
// Day
#define DTA 0xF
// Month
#define MOA 0x10
// Day of Week
#define DWA 0x11

class RTC : private I2c {
 public:
  RTC(int bus, int addr);
  int begin(void);
  int setAlarm(uint8_t dwa, uint8_t moa, uint8_t dta, uint8_t hra, uint8_t mna,
               uint8_t sca, bool recur);

 private:
  int setRTC(uint8_t dw, uint8_t yr, uint8_t mo, uint8_t dt, uint8_t hr,
             uint8_t mn, uint8_t sc);
};

#endif
