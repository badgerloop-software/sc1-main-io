#include <stdio.h>

#include <iostream>

#include "gpio.h"
#include "ina3221.h"
#include "mcp23017.h"
#include "mppt.h"
#include "serial.h"
#include "tca6416.h"

#define OUTPUT_PIN_NUM 26  // dummy pin numbers
#define INPUT_PIN_NUM 44

// Test functions go here
int mcp23017_test() {
  static const uint8_t test_array[16] = {0, 1, 0, 0, 1, 0, 1, 1,
                                         0, 1, 0, 0, 0, 1, 1, 1};
  // initialize the device
  Mcp23017 dev = Mcp23017(STUB_BUS, 0x24);

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
  static const uint8_t test_array[16] = {0, 1, 0, 0, 1, 0, 1, 0,
                                         0, 1, 0, 0, 0, 1, 0, 1};
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
  } else {
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
  } else {
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
  } else {
    return -1;
  }
  if (!dev.set_state(1, 6, 1)) {
    if (dev.get_state(1, 6) != 1) return -1;
  } else {
    return -1;
  }

  // test for invalid constructor input
  static const uint8_t invalid_array[16] = {0, 10, 1, 0, 1, 0, 1, 1,
                                            0, 1,  0, 0, 3, 1, 1, 2};

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

int ina3221_test() {
  Ina3221 dev(2, 0x24, 1e3, 2e3, 3e3);
  if (dev.begin()) return 1;

  for (int i = 1; i <= INA_NUM_CHANNELS; i++) {
    float voltage = dev.readVoltage(i);
    float current = dev.readCurrent(i);
    if ((voltage < 0) || (current < 0)) return 1;
    std::cout << "Read Voltage Ch " << i << " : " << voltage << " V\n";
    std::cout << "Read Current Ch " << i << " : " << current << " A\n";
  }

  return 0;
}

/*
int gpio_test(Serial serial) {
  int returnCondition = 0;
  // initialize the pins
  Gpio outputTest(OUTPUT_PIN_NUM, 0);  // pin number is currently a dummy number
  outputTest.begin();
  Gpio inputTest(INPUT_PIN_NUM, 1);
  inputTest.begin();
  char read[1];  // char array to read messages from the Pi
  // output 1 test
  if (outputTest.setValue(1) != 0) {  // set the pin on BBB
    std::cout << "Error setting output pin to 1\n";
    returnCondition = 1;
  }
  serial.writeString("gpio r 1\n");  // tell Pi the pin is set
  serial.readString(read, 1);
  if (strcmp(read, "y") != 0) {  // read message from Pi
    std::cout << "read " << strcmp(read, "y") << "\n";
    std::cout << "Pi did not read pin set to 1 correctly\n";
    returnCondition = 1;
  }
  serial.flushReceiver();
  // output 0 test
  if (outputTest.setValue(0) != 0) {
    std::cout << "Error setting output pin to 0\n";
    returnCondition = 1;
  }
  serial.writeString("gpio r 0\n");
  serial.readString(read, 1);
  if (strcmp(read, "y") != 0) {
    std::cout << "Pi did not read pin set to 0 correctly\n";
    returnCondition = 1;
  }
  serial.flushReceiver();
  // input 1 test
  serial.writeString("gpio w 1\n");
  serial.readString(read, 1);
  if (strcmp(read, "y") != 0) {
    std::cout << "Pi did not set the pin correctly\n";
    returnCondition = 1;
  }
  if (inputTest.getValue() != 1) {
    std::cout << "Did not get 1 from input pin\n";
    std::cout << "Got " << inputTest.getValue() << "instead\n";
    returnCondition = 1;
  }
  serial.flushReceiver();
  // input 0 test
  serial.writeString("gpio w 0\n");
  serial.readString(read, 1);
  if (strcmp(read, "y") != 0) {
    std::cout << "Pi did not set the pin correctly\n";
    returnCondition = 1;
  }
  if (inputTest.getValue() != 0) {
    std::cout << "Did not get 0 from input pin\n";
    returnCondition = 1;
  }
  serial.flushReceiver();
  return returnCondition;
}
*/

int main() {
  Gpio a({"/dev/gpiochip0"});
  a.begin();
  io_req req;
  a.mark_pin(req, 0, 1);
  a.Io(req);
  usleep(2000000);
  return 0;
}

/*
Serial serial = Serial();
if (serial.openDevice(4, 9600) != 1) std::cout << "error\n";
std::cout << "Beginning MCP23017 tests\n";
serial.writeString("mcp23017\n");

// Test calls go here
if (mcp23017_test()) {
  std::cout << "MCP23017 test failed\n";
  return 1;
}

serial.writeString("tca6416\n");
usleep(10000);  // delay to allow device to change
std::cout << "Beginning TCA tests\n";
if (tca6416_test()) {
  std::cout << "TCA6416 test failed\n";
  return -1;
}
std::cout << "TCA6416 tests passed\n";

std::cout << "Beginning GPIO tests\n";
if (gpio_test(serial)) {
  std::cout << "GPIO test failed\n";
  return 1;
}

std::cout << "Begnning INA3221 tests\n";
//  serial.writeString("ina3221");
if (ina3221_test()) {
  std::cout << "INA3221 test failed\n";
  return -1;
}

std::cout << "GPIO test passed\n";

serial.closeDevice();

*/
