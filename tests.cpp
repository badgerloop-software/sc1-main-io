#include <stdio.h>

#include "mcp23017.h"
#include "serial.h"

// Test functions go here
int func() {
  // initialize the device
  Mcp23017 dev = Mcp23017(2, 0x24);
  // begin the device dev.begin(array of 16 bits)
  dev.begin(rick_directions);
  if (dev.begin(rick_directions)) return 1;
  // write one output to bank a, and one to bank b
  dev.set_state(3, 00001000);
  dev.set_state(11, 00101010);

  // read from pin that was written to
  dev.get_state(3);
  dev.get_state(11);

  return 0;
}

int main() {
  Serial serial = Serial();
  if (serial.openDevice(4, 9600) != 1) std::cout << "error\n";
  printf("Begnning MCP23017 tests\n");
  serial.writeString("mcp23017");

  // Test calls go here
  int func();

  serial.closeDevice();
  return 0;
}
