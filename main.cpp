#include <unistd.h>  // for usleep, sleep

#include <iostream>  // for operator<<, basic_ostream::operator<<

#include "can.h"       // for CAN
#include "mcp23017.h"  // for Mcp23017, MCP_NUM_PINS, morty_directions

int main() {
  CAN c;
  Mcp23017 rick = Mcp23017(2, 0x20);
  Mcp23017 morty = Mcp23017(2, 0x21);

  rick.begin(rick_directions);
  morty.begin(morty_directions);

  std::cout << "Rick\n";
  for (int i = 0; i < MCP_NUM_PINS; i++) {
    rick.set_state(i, 1);
    usleep(1000);
    std::cout << "Pin " << +i << " val " << (int)rick.get_state(i) << std::endl;
  }

  sleep(2);

  for (int i = 0; i < MCP_NUM_PINS; i++) {
    rick.set_state(i, 0);
    usleep(1000);
    std::cout << "Pin " << +i << " val " << (int)rick.get_state(i) << std::endl;
  }

  std::cout << "Morty\n";
  for (int i = 0; i < MCP_NUM_PINS; i++) {
    morty.set_state(i, 1);
    usleep(1000);
    std::cout << "Pin " << +i << " val " << (int)morty.get_state(i)
              << std::endl;
  }

  sleep(2);

  for (int i = 0; i < MCP_NUM_PINS; i++) {
    morty.set_state(i, 0);
    usleep(1000);
    std::cout << "Pin " << +i << " val " << (int)morty.get_state(i)
              << std::endl;
  }

  return 0;
}
