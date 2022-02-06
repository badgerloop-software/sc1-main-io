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

void Gpio::begin() {
  this->pinNumberSize = 1;  // find the size of the pin number. Either 1 or 2
  if (this->pinNumber > 9) {
    this->pinNumberSize++;
  }

  int fd = open("/sys/class/gpio/export", O_WRONLY);  // set up the pin file
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/export";
    return;
  }
  if (write(fd, std::to_string(this->pinNumber), pinNumberSize) !=
      pinNumberSize) {
    std::cout << "Error writing to /sys/class/gpio/export";
    return;
  }
  close(fd);

  fd = open(
      "/sys/class/gpio/gpio" + std::to_string(this->pinNumber) + "/direction",
      O_WRONLY);  // set up direction
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/direction";
    return;
  }
  if (direction) {  // input
    char* in = "in";
    if (write(fd, in, 2) != 2) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/direction";
      return;
    }
  } else {  // output
    char* out = "out";
    if (write(fd, out, 3) != 3) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/direction";
      return;
    }
  }
  close(fd);
}
void Gpio::unexport() {
  int fd = open("/sys/class/gpio/unexport", O_WRONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/unexport";
    return;
  }
  if (write(fd, std::to_string(this->pinNumber), pinNumberSize) !=
      pinNumberSize) {
    std::cout << "Error writing to /sys/class/gpio/unexport";
    return;
  }
  close(fd);
}

void Gpio::setValue(bool value) {  // OUTPUT
  if (this->direction) {           // don't write value if it's an input
    return;
  }
  int fd = open("/sys/class/gpio/gpio" + std::to_string(pinNumber) + "/value",
                O_WRONLY);
  if (fd == -1) {
    std::cout << "Unable to open /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return;
  }
  if (value) {
    if (write(fd, "1", 1) != 1) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/value";
      return;
    }
  } else {
    if (write(fd, "0", 1) != 1) {
      std::cout << "Error writing to /sys/class/gpio/gpio" +
                       std::to_string(this->pinNumber) + "/value";
      return;
    }
  }
  close(fd);
}
int Gpio::getValue() {     // returns -1 if pin is output OR if error
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
  if (this_ > value != 1) {
    std::cout << "Error reading from /sys/class/gpio/gpio" +
                     std::to_string(this->pinNumber) + "/value";
    return -1;
  }
  close(fd);
  return value;
}
