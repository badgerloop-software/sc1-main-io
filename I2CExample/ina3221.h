#ifndef __INA3221_H__
#define __INA3221_H__

#include <stdint.h>
#include <errno.h>

#include "mbed.h"

#define INA_NUM_CHANNELS 0x3

class Ina3221 {
 private:
  float shunts[3];
  int addr;
  I2C& i2cBus;

 public:
  Ina3221(int addr, float shunt1, float shunt2, float shunt3, I2C& i2cBus);
  int begin();
  float readVoltage(int channel);
  float readCurrent(int channel);
};

#endif
