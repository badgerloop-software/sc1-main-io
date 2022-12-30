#include <gtest/gtest.h>

#include "i2c-dev.h"
#include "mcp23017.h"

class helper : private I2c {
 public:
  helper(int bus, int addr) : I2c(bus, addr, O_RDWR) {}
  int begin() { return open_i2c(); }
  int rbyte(uint8_t reg) { return read_byte(reg); }
};

TEST(I2c, mcp23017) {
  Mcp23017 m(STUB_BUS, 0x24);
  helper h(STUB_BUS, 0x24);

  uint8_t directions[MCP_NUM_PINS] = {1, 1, 0, 1, 0, 1, 0, 0,
                                      0, 1, 1, 1, 1, 1, 0, 1};
  EXPECT_EQ(m.begin(directions), 0);
  EXPECT_EQ(h.begin(), 0);
  uint8_t dirA = 0, dirB = 0;
  int i = 0;
  for (; i < MCP_NUM_PINS / 2; i++) dirA |= directions[i] << i;

  for (; i < MCP_NUM_PINS; i++) dirB |= directions[i] << (i - MCP_NUM_PINS / 2);

  EXPECT_EQ(h.rbyte(MCP_DIRA_REG), dirA);
  EXPECT_EQ(h.rbyte(MCP_DIRB_REG), dirB);

  int pin = 2;
  int val = 1;
  m.set_state(pin, val);
  EXPECT_EQ((h.rbyte(MCP_GPIOA_REG) >> pin) & 1, val);
  pin = 1;  // setting input should fail
  EXPECT_EQ(m.set_state(pin, val), -EINVAL);
}
