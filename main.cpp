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

  struct {
    float speed;
    bool crash;
    char state;
  } data_format_read, data_format_write;

  data_format_write.speed = 1.01;
  data_format_write.crash = true;
  data_format_write.state = 'a';

  // loop goes here
  while (true) {
    serial.writeBytes(&data_format_write, 6);
    usleep(1000000);
    serial.readBytes(&data_format_read, 6, 1000, 0);
    serial.flushReceiver();
    usleep(1000000);
    std::cout << "speed: " << data_format_read.speed << std::endl;
    std::cout << "crash: " << data_format_read.crash << std::endl;
    std::cout << "state: " << data_format_read.state << std::endl;
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
