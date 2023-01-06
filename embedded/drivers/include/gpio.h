#ifndef __GPIO_H__
#define __GPIO_H__

#include <gpiod.h>

#include <iostream>
#include <vector>

using std::pair;
using std::vector;

#define LINE_NUM (P)(P % 32)
#define BANK_NUM (P)(P / 32)

class Gpio {
 private:
  const char *name;
  int fd;
  struct gpiod_chip *chip;
  gpiod_line *lines[GPIOD_LINE_BULK_MAX_LINES] = {0};

 public:
  Gpio(const char *name) : name(name) {}
  int begin();
  int write(const vector<pair<unsigned int, bool>> &pins, const char *name);
};

#endif
