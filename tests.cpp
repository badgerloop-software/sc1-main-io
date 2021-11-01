#include <stdio.h>

#include "mcp23017.h"
#include "serial.h"

// Test functions go here
int func() {
  // initialize the device
  Mcp23017 dev = Mcp23017(2, 0x00)
      // begin the device dev.begin(array of 16 bits)
      if (dev.begin(arr)) return 1;
  // write one output to bank a, and one to bank b

  // read from pin that was written to

  return 0;
}

int main() {
  Serial serial = Serial();
  if (serial.openDevice(4, 9600) != 1) std::cout << "error\n";
  printf("Begnning MCP23017 tests\n");
  serial.writeString("mcp23017");

  // Test calls go here

  serial.closeDevice();
  return 0;
}
