#include <iostream>
#include <stdint.h>
#include "mcpxxxx.h"

int Mcpxxxx::set_state(int pin, uint8_t val) {
    this->write(MCP_STATE_REG, val);
    return 0;
}
uint8_t Mcpxxxx::get_state(int pin) {
    return (this->read(MCP_STATE_REG));
}

int Mcpxxxx::set_dir(int reg, uint8_t dir) {
    this->write(MCP_DIR_REG, dir);
    return 0;
}

uint8_t Mcpxxxx::get_dir(int pin) {
    return (this->read(MCP_DIR_REG));
}

int Mcpxxxx::clear_settings() {
    /*make calls to reset pins */
    std::cout << "Resetting settings\n";
    return 0;
}

/* Also need deconstructor to call parent deconstructor */
Mcpxxxx::Mcpxxxx(int bus, int addr) : I2c(bus, addr) {
    this->clear_settings();
}