#include <unistd.h>

#include <iomanip>
#include <iostream>

#include "can.h"

void printTable(uint16_t curGPIO, float curRPM, float curAccel,
                float curBrake) {
  // Wipe screen
  std::cout << "\033[2J\033[1;1H";

  // Table printout
  std::cout << "  Signal Name  |  Value" << std::endl;
  std::cout << "  RPM          |  " << curRPM << std::endl;
  std::cout << "  Accel V      |  " << curAccel << std::endl;
  std::cout << "  Brake V      |  " << curBrake << std::endl;
  std::cout << "  Power        |  " << (((curGPIO >> 0) & 0x1) ? "On" : "Off")
            << std::endl;
  std::cout << "  Direction    |  "
            << (((curGPIO >> 1) & 0x1) ? "Forward" : "Reverse") << std::endl;
  std::cout << "  Brake        |  " << (((curGPIO >> 2) & 0x1) ? "On" : "Off")
            << std::endl;
  std::cout << "  Eco          |  "
            << (((curGPIO >> 3) & 0x1) ? "Eco" : "Sport") << std::endl;
  std::cout << "  Crz Enable   |  " << (((curGPIO >> 4) & 0x1) ? "On" : "Off")
            << std::endl;
  std::cout << "  Crz Mode     |  " << (((curGPIO >> 5) & 0x1) ? "B" : "A")
            << std::endl;
  std::cout << "  MC Status    |  " << (((curGPIO >> 6) & 0x1) ? "Error" : "")
            << std::endl;
}

// Monitor CAN Bus for messages from the MCC
// Update current on screen values on arrival
int main() {
  // Define variables
  std::setprecision(3);
  uint16_t curGPIO = 0;
  float curRPM = 0;
  float curAccel = 0;
  float curBrake = 0;

  // Initialize bus
  Can busMonitor;
  busMonitor.init();
  struct can_frame newMessage;

  // Poll forever, updating printout on new data
  while (1) {
    printTable(curGPIO, curRPM, curAccel, curBrake);

    busMonitor.canRead(&newMessage);

    // Check if from MCC
    if (newMessage.can_id & 0x200) {
      switch (newMessage.can_id & 0x7) {
        case 0:
          curRPM = *(float*)newMessage.data;
          break;
        case 1:
          curGPIO = *(uint16_t*)newMessage.data;
          break;
        case 2:
          curAccel = *(float*)newMessage.data;
        case 3:
          curBrake = *(float*)newMessage.data;
          break;
        default:
          break;
      }
    }
  }

  return 0;
}
