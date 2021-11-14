#include <unistd.h>

#include <iostream>

#include "i2c.h"
#include "mcp23017.h"
#include "serial.h"

int main() {
  Serial serial = Serial();
  if (serial.openDevice(4, 115200) != 1) std::cout << "error\n";
  char buff[1];

  serial.writeString("Hello world");

  return 0;
}
