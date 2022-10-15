#ifndef __lsm6dsl__h__
#define __lsm6dsl__h__
#include "i2c.h"
#include "stdint.h"


class Lsm6dsl : private I2c {
 public:
  Lsm6dsl(int bus, int addr);
  int begin();
  double getXLX();
  double getXLY();
  double getXLZ();
  double getGX();
  double getGY();
  double getGZ();
};
#endif
