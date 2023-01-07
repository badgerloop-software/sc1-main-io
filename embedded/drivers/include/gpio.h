#ifndef __GPIO_H__
#define __GPIO_H__

#include <linux/gpio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using std::pair;
using std::string;
using std::vector;

#define MAX_PINS (32)
#define MAX_BANKS (3)

class Gpio {
  typedef __aligned_u64 u64;

 private:
  unsigned int nbanks;
  bool isInit;
  uint64_t directions;
  uint64_t values;
  struct gpiohandle_request request[GPIOHANDLES_MAX];
  char bank_name[MAX_BANKS][32];
  int bank_fd[MAX_BANKS] = {0};

 public:
  class Pins {
   public:
    Pins(const vector<unsigned int> &pins){};
    int bank_count[MAX_BANKS] = {0};               // number of pins requested
    gpiohandle_data line_values[MAX_BANKS] = {0};  // passed in ioctl
    int offset[MAX_BANKS][MAX_PINS] = {
        0};  // keep track of what index is what pin
  };

  Gpio(const vector<string> &chips);
  ~Gpio() {
    for (int i = 0; i < nbanks; i++)
      if (bank_fd[i]) close(bank_fd[i]);
  }
  int begin();
  int Io(Pins &pins);
  void mark_pin(Pins &pin, pair<unsigned int, bool> req);
};

#endif
