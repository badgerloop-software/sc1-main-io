#include "/root/pod-embedded-beta/embedded/drivers/include/gpio.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#define NUM_GPIO_PINS 32  // dummy number right now

Gpio::Gpio(int pinNumber, bool direction) {
  if (pinNumber < 0 ||
      pinNumber >= NUM_GPIO_PINS) {  // make sure pin number is valid
    return;
  }
  this->pinNumber = pinNumber;
  this->direction = direction;
}

// exports the pin (creates pin file) and sets the direction.
int Gpio::begin() {
  this->pinNumberSize =
      1;  // find the size(number of digits) of the pin number.
  if (this->pinNumber > 9) {
    this->pinNumberSize++;
  }

  int fd = open("/sys/class/gpio/export", O_WRONLY);  // set up the pin file
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/export";
    return -1;
  }
  if (write(fd, std::to_string(this->pinNumber), pinNumberSize) !=
      pinNumberSize) {
    std::cout << "Error writing to /sys/class/gpio/export";
    return -1;
  }
  close(fd);

  fd = open(
      "/sys/class/gpio/gpio" + std::to_string(this->pinNumber) + "/direction",
      O_WRONLY);  // set up direction
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/direction";
    return -1;
  }
  if (direction) {  // input
    char* in = "in";
    if (write(fd, in, 2) != 2) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/direction";
      return -1;
    }
  } else {  // output
    char* out = "out";
    if (write(fd, out, 3) != 3) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/direction";
      return -1;
    }
  }
  close(fd);
  return 0;  // no errors encountered
}

// close the pin
int Gpio::unexport() {
  int fd = open("/sys/class/gpio/unexport", O_WRONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/unexport";
    return -1;
  }
  if (write(fd, std::to_string(this->pinNumber), pinNumberSize) !=
      pinNumberSize) {
    std::cout << "Error writing to /sys/class/gpio/unexport";
    return -1;
  }
  close(fd);
  return 0;
}

// set the value of an OUTPUT pin
// return -1 if error or if it's an input pin.
// return 0 if no errors.
int Gpio::setValue(bool value) {
  if (this->direction) {  // don't write value if it's an input
    return -1;
  }
  int fd = open("/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/value",
                O_WRONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  if (value) {
    if (write(fd, "1", 1) != 1) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/value";
      return -1;
    }
  } else {
    if (write(fd, "0", 1) != 1) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/value";
      return -1;
    }
  }
  close(fd);
  return 0;
}

// get the value of an INPUT pin
// return -1 if error or if it's an output pin
// return 0 or 1 depending on the input pin value.
int Gpio::getValue() {
  if (!this->direction) {  // don't read value if it's an output
    return -1;
  }
  int fd = open("/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/value",
                O_RDONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  this->value = read(fd, "1", 1);
  if (this->value != 1) {
    std::cout << "Error reading from /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  close(fd);
  return value;
}
