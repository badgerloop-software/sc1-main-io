#ifndef __GPIO_H__
#define __GPIO_H__

#include <fcntl.h>
#include <linux/gpio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;

#define MAX_PINS (32)
#define BANKS (4)

class Gpio {
 private:
  int fds[BANKS];
  const vector<string> chips;

 public:
  struct Pin {
    int line;
    int bank;
    gpiohandle_request req;
    gpiohandle_data data;
    Pin(const Gpio &g, int pin, __u32 flag)
        : line(pin % MAX_PINS), bank(pin / MAX_PINS) {
      memset(req.default_values, 0, sizeof(req.default_values));
      req.lineoffsets[0] = line;
      req.lines = 1;
      req.fd = -1;
      if (g.fds[bank] != -1) {
        strcpy(req.consumer_label, "Bloop");
        req.flags = flag;
        if (ioctl(g.fds[bank], GPIO_GET_LINEHANDLE_IOCTL, &req) < 0)
          perror("Error getting linehandles");
      }
    };
    ~Pin() {
      if (req.fd != -1) close(req.fd);
    }
  };

  int getValue(Pin &p, bool &value) {
    if (p.req.fd == -1) return -1;
    if (ioctl(p.req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &p.data) < 0) {
      perror("Error getting line values");
      return -1;
    }
    value = p.data.values[0];
    return 0;
  }

  int setValue(Pin &p, bool value) {
    if (p.req.fd == -1) return -1;
    p.data.values[0] = value;
    if (ioctl(p.req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &p.data) < 0) {
      perror("Error setting line values");
      return -1;
    }
    return 0;
  }

  Gpio(vector<string> &&chips) : chips(chips) {
    for (int i = 0; i < BANKS; i++) fds[i] = -1;
  }

  ~Gpio() {
    for (int i = 0; i < BANKS; i++)
      if (fds[i] != -1) close(fds[i]);
  }

  int begin() {
    for (const auto &c : chips) {
      int chipno;
      if (sscanf(c.c_str(), "/dev/gpiochip%d", &chipno) < 1) return -1;
      fds[chipno] = open(c.c_str(), O_RDWR);
      if (fds[chipno] < 0) return -1;
    }
    return 0;
  }
};

#endif
