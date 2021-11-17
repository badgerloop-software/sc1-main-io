#ifndef __ANALOG_H__
#define __ANALOG_H__
#include <stdint.h>

class Analog {
 private:
  int fd;
  uint16_t scale;
  int pin;

 public:
  Analog(int pin, int scale);
  ~Analog();
  bool begin();
  bool isOpen();
  float read();
};

#endif
