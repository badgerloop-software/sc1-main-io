#ifndef __lsm6dsl__h__
#define __lsm6dsl__h__
#include "i2c.h"
#include "stdint.h"

#define RESET 0x00000001
#define DEVID 0x01101010

#define CRTL3_C 0x12
#define WHO_AM_I 0x0F

#define CTRL1_XL 0x10 // 4 and 5 are two bits for XL full scale selection
#define CTRL2_G 0x11 // 4 and 5 are two bits for G full scale selection
#define OUTX_L_G 0x22
#define OUTX_H_G 0x23
#define OUTY_L_G 0x24
#define OUTY_H_G 0x25
#define OUTZ_L_G 0x26
#define OUTZ_H_G 0x27
#define OUTX_L_XL 0x28
#define OUTX_H_XL 0x29
#define OUTY_L_XL 0x2A
#define OUTY_H_XL 0x2B
#define OUTZ_L_XL 0x2C
#define OUTZ_H_XL 0x2D

#define write_two_bytes(regl,regh,val) (write_data(regl,(uint8_t)(val&0x00FF));write_data(regh,(uint8_t)(val>>8)))


class Lsm6dsl : private I2c {
 public:
  Lsm6dsl(int bus, int addr);
  double g_full_scale;
  double xl_full_scale;
  int begin();
  double getXLX();
  double getXLY();
  double getXLZ();
  double getGX();
  double getGY();
  double getGZ();

  int setRangeXL(uint8_t select);
  int setRangeG(uint8_t select);
};

int get_xl_scale(int x);
#endif
