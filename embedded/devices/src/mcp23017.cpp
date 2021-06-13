#include <iostream>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include "mcp23017.h"

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
        if (rc)
            return rc;
    }

    rc = this->clear_settings();
    if (rc) {
        std::cerr << "Error clearing settings\n";
        return rc;
    }

    for (int i = 0; i < MCP_NUM_PINS; i++)
        this->set_dir(i, directions[i]);
    
    for (int i = 0; i < MCP_NUM_PINS; i++) {
        if (this->get_dir(i) != directions[i]) {
            std::cerr << "Error setting direction of pin " << i << "\n";
            return -EIO;
        }
    }
    return 0;
}

/* I really don't like these next 3 functions I think they can be consolidated */
static uint8_t getDirBank(int pin) {
    if (pin < (MCP_NUM_PINS >> 1))
        return MCP_DIRA_REG;
    else
        return MCP_DIRB_REG;
}

static uint8_t getGpioBank(int pin) {
    if (pin < (MCP_NUM_PINS >> 1))
        return MCP_GPIOA_REG;
    else
        return MCP_GPIOB_REG;
}

static uint8_t getRelativePin(int pin) {
    if (pin >= (MCP_NUM_PINS >> 1)) {
        pin -= (MCP_NUM_PINS >> 1);
    }
    return pin;
}


/* These 4 methods have way too much in common
 * Definitely need some helper methods */
uint8_t Mcp23017::get_dir(int pin) {
    uint8_t current_status;
    uint8_t dirReg;

    if (pin >= MCP_NUM_PINS)
        return -EINVAL;

    dirReg = getDirBank(pin);
    pin = getRelativePin(pin);

    current_status = this->read_from_addr(dirReg);

    return ((current_status >> pin) & 1);
}

int Mcp23017::set_dir(int pin, uint8_t dir) {
    uint8_t current_status;
    uint8_t dirReg;
    int rc;

    if (pin >= MCP_NUM_PINS)
        return -EINVAL;

    dirReg = getDirBank(pin);
    pin = getRelativePin(pin);

    current_status = this->read_from_addr(dirReg);

    if (dir)
        rc = this->write_data(dirReg, current_status | (1 << pin));
    else
        rc = this->write_data(dirReg, current_status & ~(1 << pin));

    return rc;
}

uint8_t Mcp23017::get_state(int pin) {
    uint8_t current_status;
    uint8_t stateReg;

    if (pin >= MCP_NUM_PINS)
        return -EINVAL;

    stateReg = getGpioBank(pin);
    pin = getRelativePin(pin);

    current_status = this->read_from_addr(stateReg);

    return ((current_status >> pin) & 1);
}

int Mcp23017::set_state(int pin, uint8_t dir) {
    uint8_t current_status;
    uint8_t current_dir;
    uint8_t stateReg;
    uint8_t dirReg;
    int rc;

    if (pin >= MCP_NUM_PINS)
        return -EINVAL;

    stateReg = getGpioBank(pin);
    dirReg = getDirBank(pin);
    pin = getRelativePin(pin);

    current_dir = this->read_from_addr(dirReg);

    if (current_dir)
        return -EINVAL;
    current_status = this->read_from_addr(stateReg);

    if (dir)
        rc = this->write_data(stateReg, current_status | (1 << pin));
    else
        rc = this->write_data(stateReg, current_status & ~(1 << pin));

    return rc;
}
