#include "mcp23017.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include <iostream>

Mcp23017::Mcp23017(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int Mcp23017::clear_settings() {
  /* Reset dir regs */
  if (this->write_data(MCP_DIRA_REG, 0xFF) ||
      this->write_data(MCP_DIRB_REG, 0xFF))
    return -EIO;

  /* Reset GPIO regs */
  if (this->write_data(MCP_GPIOA_REG, 0x00) ||
      this->write_data(MCP_GPIOB_REG, 0x00))
    return -EIO;

  return 0;
}

int Mcp23017::begin(const uint8_t directions[]) {
  int rc;

  if (!this->is_open()) {
    rc = this->open_i2c();
    if (rc) return rc;
  }

  rc = this->clear_settings();
  if (rc) {
    std::cerr << "Error clearing settings\n";
    return rc;
  }

  for (int i = 0; i < MCP_NUM_PINS; i++) this->set_dir(i, directions[i]);

  for (int i = 0; i < MCP_NUM_PINS; i++) {
    if (this->get_dir(i) != directions[i]) {
      std::cerr << "Error setting direction of pin " << i << "\n";
      return -EIO;
    }
  }
  return 0;
}

uint8_t Mcp23017::get_dir(int pin) {
  uint8_t current_status;
  uint8_t dirReg;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  pin = GET_REL_PIN(pin);

  current_status = this->read_from_reg(dirReg);

  return ((current_status >> pin) & 1);
}

int Mcp23017::set_dir(int pin, uint8_t dir) {
  uint8_t current_status;
  uint8_t dirReg;
  int rc;
printf("Setting pin %d to %d", pin, dir);
  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  pin = GET_REL_PIN(pin);

  current_status = this->read_from_reg(dirReg);
  printf("current status = 0x%2x\n", current_status);
  if (dir) {
	printf("Writing 0x%2x\n", current_status | (1 << pin));
    rc = this->write_data(dirReg, current_status | (1 << pin));
	
}
  else{
	printf("Writing 0x%2x\n", current_status & ~(1 << pin)); 
   rc = this->write_data(dirReg, current_status & ~(1 << pin));
}
  return rc;
}

uint8_t Mcp23017::get_state(int pin) {
  uint8_t current_status;
  uint8_t stateReg;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  stateReg = IS_BANK_A(pin) ? MCP_GPIOA_REG : MCP_GPIOB_REG;
  pin = GET_REL_PIN(pin);

  current_status = this->read_from_reg(stateReg);

  return ((current_status >> pin) & 1);
}

int Mcp23017::set_state(int pin, uint8_t val) {
  uint8_t current_status;
  uint8_t current_dir;
  uint8_t stateReg;
  uint8_t dirReg;
  int rc;

  if (pin >= MCP_NUM_PINS) return -EINVAL;

  dirReg = IS_BANK_A(pin) ? MCP_DIRA_REG : MCP_DIRB_REG;
  stateReg = IS_BANK_A(pin) ? MCP_GPIOA_REG : MCP_GPIOB_REG;
  pin = GET_REL_PIN(pin);

  current_dir = this->read_from_reg(dirReg);

  if ((current_dir >> pin) & 0x1) return -EINVAL;
  current_status = this->read_from_reg(stateReg);

  if (val)
    rc = this->write_data(stateReg, current_status | (1 << pin));
  else
    rc = this->write_data(stateReg, current_status & ~(1 << pin));

  return rc;
}
