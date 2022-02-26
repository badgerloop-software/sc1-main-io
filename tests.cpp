#include <stdio.h>

#include <iostream>

#include "mcp23017.h"
#include "serial.h"
#include "tca6416.h"

// Test functions go here
int mcp23017_test() {
  static const uint8_t test_array[16] = {0, 1, 0, 0, 1, 0, 1, 1,
                                         0, 1, 0, 0, 0, 1, 1, 1};
  // initialize the device
  Mcp23017 dev = Mcp23017(2, 0x24);

  // begin the device dev.begin(array of 16 bits)
  if (dev.begin(test_array)) return 1;

  // set two outputs on bank a, and two on bank b
  // and read from pin each time it is written
  dev.set_state(3, 1);
  if (dev.get_state(3) != 1) return 1;
  dev.set_state(2, 0);
  if (dev.get_state(2) != 0) return 1;

  dev.set_state(11, 1);
  if (dev.get_state(11) != 1) return 1;
  dev.set_state(9, 0);
  if (dev.get_state(9) != 0) return 1;

  return 0;
}

int tca6416_test() {
  static const uint8_t test_array[16] = {0, 1, 0, 0, 1, 0, 1, 1,
                                         0, 1, 0, 0, 0, 1, 1, 1};
  // initialize the device
  Tca6416 dev = Tca6416(2, 0x24);

  // begin the device - dev
  if (dev.begin(test_array)) return -1;

  // set state and check
  // get to make sure written properly

  // testing for pin 7 on bank 0
  if (!dev.set_state(0, 7, 0)) {  // if successfully set then, return would be 0
    if (dev.get_state(0, 7) != 0) return -1;  // then go to check if get works
  } else {
    return -1;
  }
  if (!dev.set_state(0, 7, 1)) {  // if successfully set then, return would be 0
    if (dev.get_state(0, 7) != 1) return -1;  // then go to check if get works
  } else {
    return -1;
  }

  // testing for pin 3 on bank 0
  if (!dev.set_state(0, 3, 1)) {
    if (dev.get_state(0, 3) != 1) return -1;
    return -1;
  }
  if (!dev.set_state(0, 3, 0)) {
    if (dev.get_state(0, 3) != 0) return -1;
  } else {
    return -1;
  }

  // testing for pin 4 on bank 1
  if (!dev.set_state(1, 4, 1)) {
    if (dev.get_state(1, 4) != 1) return -1;
    return -1;
  }
  if (!dev.set_state(1, 4, 0)) {
    if (dev.get_state(1, 4) != 0) return -1;
  } else {
    return -1;
  }

  // testing for pin 6 on bank 1
  if (!dev.set_state(1, 6, 0)) {
    if (dev.get_state(1, 6) != 0) return -1;
    return -1;
  }
  if (!dev.set_state(1, 6, 1)) {
    if (dev.get_state(1, 6) != 1) return -1;
  } else {
    return -1;
  }

  // test for invalid constructor input
  static const uint8_t invalid_array[16] = {0, 1, 1, 0, 1, 0, 1, 1,
                                            0, 1, 0, 0, 3, 1, 1, 2};

  Tca6416 inv = Tca6416(2, 0x24);

  if (!inv.begin(invalid_array)) {  // return should be not zero, if it is,
                                    // return -1 for error
    return -1;
  }

  // testing for invalid input to set_state
  // test for invalid pin number
  if (!dev.set_state(0, 8, 1)) {
    return -1;
  }

  // test for invalid value
  if (!dev.set_state(0, 2, 3)) {
    return -1;
  }

  // test for invalid inputs to get_state
  // test for invalid pin number
  if (!dev.get_state(0, 9)) {
    return -1;
  }

  // make sure to check that just default settings are not being applied by
  // setting then verifying by get and then set again and verify checking for
  // not being set to default means changing the value twice, 1 to 0 to 1

  // pin 0,7 has val = 1 i.e input
  // pin 0,3 has val = 0 i.e output

  return 0;
}

int main() {
  Serial serial = Serial();
  if (serial.openDevice(4, 9600) != 1) std::cout << "error\n";
  std::cout << "Begnning MCP23017 tests\n";
  serial.writeString("mcp23017");

  // Test calls go here
  if (mcp23017_test()) {
    std::cout << "MCP23017 test failed/n";
    return 1;
  }

  serial.writeString("tca6416");
  usleep(10000);  // delay to allow device to change
  std::cout << "Beginning TCA tests\n";
  if (tca6416_test()) {
    std::cout << "TCA6416 test failed\n";
    return -1;
  }

  serial.closeDevice();
  return 0;
}
