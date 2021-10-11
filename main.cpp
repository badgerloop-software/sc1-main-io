#include <unistd.h>

#include <iostream>

#include "i2c.h"
#include "mcp23017.h"

int main(int argc, char *argv[]) {
  Mcp23017 mcps[2] = {Mcp23017(2, 0x24), Mcp23017(2, 0x25)};
  if (argc<2) {
      fprintf(stderr, "Pass value to write\n");
      exit(1);
  }


  int val = atoi(argv[1]);
  for (int i = 0; i<2; i++) {
    Mcp23017 device = mcps[i];
    device.begin();
    std::cout << "write...\n";
    device.test_write_data(0x00, val);
    sleep(1);
    std::cout << "hopefully " << val << "...\n" <<
        device.test_read_from_reg(0x00) << std::endl;
  }

  return 0;
}
