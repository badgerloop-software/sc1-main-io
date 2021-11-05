#include <stdio.h>

#include <iostream>
using namespace std;

#include "mcp23017.h"
#include "serial.h"

// Test functions go here
int mcp23017_test() {
  static const uint8_t test_array[16] = {0, 1, 0, 0, 1, 0, 1, 1,
                                         0, 1, 0, 0, 0, 1, 1, 1};
  // initialize the device
  Mcp23017 dev = Mcp23017(2, 0x24);
  // begin the device dev.begin(array of 16 bits)
  if (dev.begin(test_array)) return 1;
  // write one output to bank a, and one to bank b
  // and read from pin that was written to
  dev.set_state(3, 0);
  if (dev.get_state(3) != 1) return 1;

  dev.set_state(11, 0);
  if (dev.get_state(11) != 1) return 1;

  return 0;
}

int main() {
  Serial serial = Serial();
  if (serial.openDevice(4, 9600) != 1) std::cout << "error\n";
  std::cout << "Begnning MCP23017 tests\n";
  serial.writeString("mcp23017");

  // Test calls go here
  if (!mcp23017_test()) {
    std::cout << "MCP23017 test failed/n";
    return 1;
  }

  serial.closeDevice();
  return 0;
}
