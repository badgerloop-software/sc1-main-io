#ifndef __mcp__h__
#define __mcp__h__
#include <stdint.h>
#include "i2c.h"

#define MCP_DIR_REG 0x20
#define MCP_STATE_REG 0x10

class Mcpxxxx: private I2c {
    private:
        int bus;
        int address;
        int clear_settings();
        int set_dir(int pin, uint8_t dir);
        uint8_t get_dir(int pin);
    public:
        Mcpxxxx(int bus, int addr);
        uint8_t get_state(int pin);
        int set_state(int pin, uint8_t val);
};
#endif