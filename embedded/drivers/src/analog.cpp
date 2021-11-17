#include "analog.h"

#include <fcntl.h>
#include <unistd.h>

#include <iostream>

Analog::Analog(int pin, int scale) {}

Analog::~Analog() {}

bool Analog::begin() {}

bool Analog::isOpen() { return true; }

float Analog::read() { return 0; }
