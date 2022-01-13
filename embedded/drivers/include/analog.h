#ifndef __ANALOG_H__
#define __ANALOG_H__
#include <stdint.h>

class Analog {
 private:
  int fd;
  float scale;
  int pin;

 public:
  Analog(int pin, float scale);
  ~Analog();
  bool begin();
  bool isOpen();
  float readPin();
};

#endif
