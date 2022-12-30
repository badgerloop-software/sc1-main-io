#include <gtest/gtest.h>

#include "i2c-dev.h"
#include "mcp23017.h"

class helper : private I2c {
 public:
  helper(int bus, int addr) : I2c(bus, addr, O_RDWR) {}
  int begin() { return open_i2c(); }
  int rbyte(uint8_t reg) { return read_byte(reg); }
};  // helper for manual reading of registers

/*
TEST(SuiteName, DeviceName)
*/
TEST(I2c, mcp23017) {
  Mcp23017 DUT(STUB_BUS, 0x24);  // Device Under Test
  helper h(STUB_BUS, 0x24);

  /*

     directions:                pins {0, 1, 2, 3, 4, 5, 6, 7,
     0 output, 1 input                8, 9, 10,11,12,13,14,15}

  */
  uint8_t directions[MCP_NUM_PINS] = {1, 1, 0, 1, 0, 1, 0, 0,
                                      0, 1, 1, 1, 1, 1, 0, 1};

  // make sure devices startup right
  EXPECT_EQ(DUT.begin(directions), 0);
  EXPECT_EQ(h.begin(), 0);

  // generate what we expect to see on the direction registers
  uint8_t dirA = 0, dirB = 0;
  int i = 0;
  for (; i < MCP_NUM_PINS / 2; i++) dirA |= directions[i] << i;

  for (; i < MCP_NUM_PINS; i++) dirB |= directions[i] << (i - MCP_NUM_PINS / 2);

  // check what we generated against what helper got
  EXPECT_EQ(h.rbyte(MCP_DIRA_REG), dirA);
  EXPECT_EQ(h.rbyte(MCP_DIRB_REG), dirB);

  // try setting outputs
  int pin = 2;  // this pin is an output (check above)
  int val = 1;  // raise pin high
  DUT.set_state(pin, val);
  // use helper to check that the gpio register looks like what we expect
  EXPECT_EQ((h.rbyte(MCP_GPIOA_REG) >> pin) & 1, val);

  val = 0;  // now lower same pin to make sure we didn't get lucky
  DUT.set_state(pin, val);
  EXPECT_EQ((h.rbyte(MCP_GPIOA_REG) >> pin) & 1, val);

  pin = 0;  // this pin is an input (check above)
  EXPECT_EQ(DUT.set_state(pin, val), -EINVAL);  // setting an input should fail
}
