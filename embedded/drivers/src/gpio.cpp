#include "gpio.h"

#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>

#include <iostream>

Gpio::Gpio(const vector<string> &chips) {
  nbanks = chips.size();
  int i = 0;
  for (auto &s : chips) strcpy(bank_name[i++], s.c_str());
}

void Gpio::mark_pin(Pins &pins, pair<unsigned int, bool> req) {
  // get pin location
  int line = req.first % MAX_PINS;
  int bank = req.first / MAX_PINS;

  int *count = &pins.bank_count[bank];

  pins.offset[bank][*count] = line;  // store line offset
  pins.line_values[bank].values[*count] = req.second;

  (*count)++;
}

int Gpio::Io(Pins &req) {
  if (begin() < 0) return -1;
  for (int bank = 0; bank < nbanks; bank++) {
    if (req.bank_count[bank]) {
      struct gpiohandle_request lreq;
      memset(&lreq.default_values, 0, sizeof(lreq.default_values));
      lreq.flags = GPIOHANDLE_REQUEST_OUTPUT;
      strcpy(lreq.consumer_label, "TESTIO");
      lreq.lines = req.bank_count[bank];

      for (int line = 0; line < lreq.lines; line++) {
        lreq.lineoffsets[line] = req.offset[bank][line];
      }

      // request linehandles
      if (ioctl(bank_fd[bank], GPIO_GET_LINEHANDLE_IOCTL, &lreq) < 0) {
        perror("Error requesting linehandles: ");
        return -1;
      }

      // provide data
      if (ioctl(lreq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL,
                &req.line_values[bank]) < 0) {
        perror("Error setting values: ");
        return -1;
      }
    }
  }
  return 0;
}

int Gpio::begin() {
  if (isInit) return 0;

  for (int i = 0; i < nbanks; i++) {
    if ((bank_fd[i] = open(bank_name[i], O_RDWR)) < 0) {
      std::cerr << "Error opening " << bank_name[i] << std::endl;
      return -1;
    }
    struct gpiochip_info info;
    if ((ioctl(bank_fd[i], GPIO_GET_CHIPINFO_IOCTL, &info)) < 0) {
      std::cerr << "Error getting chip info " << bank_name[i] << std::endl;
    }
    std::cout << "Name: " << info.name << "\nLabel: " << info.label
              << "\nLines: " << info.lines << std::endl;
  }

  isInit = true;
  return 0;
};
