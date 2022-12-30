#include "mcp23017.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include <iostream>

Mcp23017::Mcp23017(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int Mcp23017::clear_settings() {
  /* Reset dir regs */
  if (write_byte(MCP_DIRA_REG, 0xFF) || write_byte(MCP_DIRB_REG, 0xFF))
    return -EIO;

  /* Reset GPIO regs */
  if (write_byte(MCP_GPIOA_REG, 0x00) || write_byte(MCP_GPIOB_REG, 0x00))
    return -EIO;

  return 0;
}

int Mcp23017::begin(const uint8_t directions[]) {
  int rc;

  if (!is_open()) {
    rc = open_i2c();
    if (rc < 0) return rc;
  }

  rc = clear_settings();
  if (rc < 0) {
    std::cerr << "Error clearing settings\n";
    return rc;
  }

  for (int i = 0; i < MCP_NUM_PINS; i++) set_dir(i, directions[i]);

  for (int i = 0; i < MCP_NUM_PINS; i++) {
    if (get_dir(i) != directions[i]) {
      std::cerr << "Error setting direction of pin " << i << "\n";
      return -EIO;
    }
  }
  return 0;
}

int Mcp23017::get_dir(int pin) {
  uint8_t dirReg;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  pin = GET_REL_PIN(pin);

  int rc = read_byte(dirReg);
  if (rc < 0) return rc;

  return ((rc >> pin) & 1);
}

int Mcp23017::set_dir(int pin, uint8_t dir) {
  uint8_t current_status;
  uint8_t dirReg;
  int rc;
  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  pin = GET_REL_PIN(pin);

  rc = read_byte(dirReg);
  if (rc < 0) return rc;
  current_status = rc;
  if (dir)
    rc = write_byte(dirReg, current_status | (1 << pin));
  else
    rc = write_byte(dirReg, current_status & ~(1 << pin));

  return rc;
}

int Mcp23017::get_state(int pin) {
  uint8_t stateReg;
  int rc;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  stateReg = IS_BANK_A(pin) ? MCP_GPIOA_REG : MCP_GPIOB_REG;
  pin = GET_REL_PIN(pin);

  rc = read_byte(stateReg);
  if (rc < 0) return rc;

  return ((rc >> pin) & 1);
}

int Mcp23017::set_state(int pin, uint8_t val) {
  uint8_t stateReg;
  uint8_t dirReg;
  int rc;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  stateReg = IS_BANK_A(pin) ? MCP_GPIOA_REG : MCP_GPIOB_REG;
  pin = GET_REL_PIN(pin);

  // check direction
  rc = read_byte(dirReg);
  if (rc < 0) return rc;
  if ((rc >> pin) & 0x1) return -EINVAL;

  // set state
  rc = read_byte(stateReg);
  if (rc < 0) return rc;

  if (val)
    rc = write_byte(stateReg, rc | (1 << pin));
  else
    rc = write_byte(stateReg, rc & ~(1 << pin));

  return rc;
}
