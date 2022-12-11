#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "i2c.h"
#include "ina3221.h"
#include "mcp23017.h"
#include "serial.h"

int main() {
  // Mcp23017 rick = Mcp23017(2, 0x20);
  // Mcp23017 morty = Mcp23017(2, 0x21);

  // rick.begin(rick_directions);
  // morty.begin(morty_directions);

  // std::cout << "Rick\n";
  // for (int i = 0; i < MCP_NUM_PINS; i++) {
  //   rick.set_state(i, 1);
  //   usleep(1000);
  //   std::cout << "Pin " << +i << " val " << (int)rick.get_state(i) <<
  //   std::endl;
  // }

  // sleep(2);

  // for (int i = 0; i < MCP_NUM_PINS; i++) {
  //   rick.set_state(i, 0);
  //   usleep(1000);
  //   std::cout << "Pin " << +i << " val " << (int)rick.get_state(i) <<
  //   std::endl;
  // }

  // std::cout << "Morty\n";
  // for (int i = 0; i < MCP_NUM_PINS; i++) {
  //   morty.set_state(i, 1);
  //   usleep(1000);
  //   std::cout << "Pin " << +i << " val " << (int)morty.get_state(i)
  //             << std::endl;
  // }

  // sleep(2);

  // for (int i = 0; i < MCP_NUM_PINS; i++) {
  //   morty.set_state(i, 0);
  //   usleep(1000);
  //   std::cout << "Pin " << +i << " val " << (int)morty.get_state(i)
  //             << std::endl;
  // }
  Serial serial = Serial();
  serial.openDevice(2, 115200);
  char message[] = "abcdefghij";

  // loop goes here
  while (true) {
    std::string checkMessage = "";
    // write a random number of bytes (1-9) to the Pi
    unsigned int numWriteBytes = rand() % 9 + 1;
    // std::cout << message + numWriteBytes << std::endl;
    char nwb = char(numWriteBytes + 48);  // convert number of bytes to a char
    // std::cout << "number of bytes to write: " << nwb << std::endl;
    serial.writeString(&nwb);                  // write number of bytes
    for (int i = 0; i < numWriteBytes; i++) {  // write message using for loop
      serial.writeString(&message[i]);
      checkMessage = checkMessage + message[i];
    }
    std::cout << "write: " << nwb << checkMessage << std::endl;
    usleep(1000000);

    // read the number of bytes of incoming data
    // std::cout << "bytes available : " << serial.available() << std::endl;
    char readBytesIn[1];
    serial.readString(readBytesIn, 1);
    unsigned int numReadBytes = (int)readBytesIn[0] - 48;
    std::cout << "nrb: " << numReadBytes << " char: " << readBytesIn
              << std::endl;

    // read that number of bytes to get the data.
    // std::cout << "bytes available : " << serial.available() << std::endl;
    char readResult[numReadBytes];
    serial.readString(readResult, numReadBytes);
    std::cout << "message read: " << readResult << std::endl;
    // serial.flushReceiver();
    usleep(1000000);
  }

  // Ina3221 test = Ina3221(2, 0x40, 0.005, 0.005, 0.005);
  // test.begin();
  // std::cout << "Ina3221" << std::endl;
  // for (int i = 0; i < 1000; i++) {
  //   // std::cout << "channel 1 voltage: " << test.readVoltage(0x1) <<
  //   std::endl;
  //   // std::cout << "channel 2 voltage: " << test.readVoltage(0x2) <<
  //   std::endl;
  //   // std::cout << "channel 3 voltage: " << test.readVoltage(0x3) <<
  //   std::endl; std::cout << "channel 3 current: " << test.readCurrent(0x3) <<
  //   std::endl; std::cout << std::endl; usleep(1000000);
  // }

  return 0;
}
