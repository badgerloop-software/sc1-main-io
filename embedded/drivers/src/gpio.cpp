#include "gpio.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#define NUM_GPIO_PINS 117  // highest possible pin number

Gpio::Gpio(int pinNumber, bool direction) {
  if (pinNumber < 0 ||
      pinNumber > NUM_GPIO_PINS) {  // make sure pin number is valid
    return;
  }
  this->pinNumber = pinNumber;
  this->direction = direction;
}

// exports the pin (creates pin file) and sets the direction.
int Gpio::begin() {
  // find the size(number of digits) of the pin number. Either 2 or 3
  this->pinNumberSize = 2;
  if (this->pinNumber > 99) {
    this->pinNumberSize = 3;
  }
  // check if the pin has been exported
  std::string filePathString =
      "/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/direction";
  const char* filePath = filePathString.c_str();
  int check = open(filePath, O_WRONLY);
  if (check != -1) {
    std::cout << "Pin has already been exported";
    close(check);
  } else {                                              // export the pin
    int fd = open("/sys/class/gpio/export", O_WRONLY);  // set up the pin file
    if (fd == -1) {
      std::cout << "Unable to open /sys/class/gpio/export";
      return -1;
    }
    if (write(fd, std::to_string(this->pinNumber).c_str(),
              this->pinNumberSize) != this->pinNumberSize) {
      std::cout << "Error writing to /sys/class/gpio/export";
      return -1;
    }
    close(fd);
  }
  std::string filePathString =
      "/sys/class/gpio/gpio" + std::to_string(this->pinNumber) + "/direction";
  const char* filePath = filePathString.c_str();
  int fd = open(filePath, O_WRONLY);  // set up direction
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/direction";
    return -1;
  }
  if (direction) {  // input
    std::string inString = "in";
    const char* in = inString.c_str();
    if (write(fd, in, 2) != 2) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/direction";
      return -1;
    }
  } else {  // output
    std::string outString = "out";
    const char* out = outString.c_str();
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
  if (write(fd, std::to_string(this->pinNumber).c_str(), this->pinNumberSize) !=
      this->pinNumberSize) {
    std::cout << "Error writing to /sys/class/gpio/unexport";
    return -1;
  }
  close(fd);
  return 0;
}
// destructor. Calls unexport()
Gpio::~Gpio() { this->unexport(); }

// set the value of an OUTPUT pin
// return -1 if error or if it's an input pin.
// return 0 if no errors.
int Gpio::setValue(bool value) {
  if (this->direction) {  // don't write value if it's an input
    return -1;
  }
  std::string filePathString =
      "/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/value";
  const char* filePath = filePathString.c_str();
  int fd = open(filePath, O_WRONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  if (value) {
    std::string oneString = "1";
    const char* one = oneString.c_str();
    if (write(fd, one, 1) != 1) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/value";
      return -1;
    }
  } else {
    std::string zeroString = "0";
    const char* zero = zeroString.c_str();
    if (write(fd, zero, 1) != 1) {
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
  std::string filePathString =
      "/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/value";
  const char* filePath = filePathString.c_str();
  int fd = open(filePath, O_RDONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  std::string oneString = "1";
  char value;
  read(fd, &value, 1);
  close(fd);
  const char* valueCompare = &value;
  if (strcmp(valueCompare, "1") == 0) {
    return 1;
  } else {
    return 0;
  }
}
