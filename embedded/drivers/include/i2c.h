#ifndef __i2c_h__
#define __i2c_h__

#include <cstring>
#include <iostream>

extern "C" {
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "i2c-dev.h"
}

class I2c {
 private:
  int fd;
  int bus;
  int deviceAddress;
  int openMode;

 protected:
  I2c(int bus, int addr, int mode);
  ~I2c();
  int open_i2c();
  bool is_open();
  int read_word(uint8_t reg);
  int read_byte(uint8_t reg);
  int write_byte(uint8_t reg, uint8_t val);
  int write_word(uint8_t reg, uint16_t val);
};

#endif
