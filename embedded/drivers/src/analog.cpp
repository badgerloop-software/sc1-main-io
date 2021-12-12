#include "analog.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

#define NUM_ANALOG_PINS 7
#define PIN_FILE_PATH "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw"

Analog::Analog(int pin, int scale) {
  this->scale = scale;
  this->pin = pin;
}

Analog::~Analog() { close(this->fd); }

bool Analog::begin() {
  char filePath[49];

  if (this->pin < 0 || this->pin >= NUM_ANALOG_PINS) {
    std::cout << "Pin number not in range\n";
    return false;
  }
  sprintf(filePath, PIN_FILE_PATH, this->pin);
  this->fd = open(filePath, O_RDONLY);
  if (!this->isOpen()) {
    std::cout << "Failed to open file\n";
    return false;
  }
  return true;
}

bool Analog::isOpen() { return this->fd > 0; }

float Analog::readPin() {
  char raw[4];
  float val;

  // need to read this as a char array for some reason
  read(this->fd, &raw[0], 4);
  val = atof(raw);

  // reset the file pointer to start from the beginning on next read
  lseek(this->fd, 0, SEEK_SET);

  return (1.8 / 4096.0) * val;
}
