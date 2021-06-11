#ifndef __i2c_h__
#define __i2c_h__
#include <stdint.h>
class I2c {
    private:
        int fd;
        int bus;
        int deviceAddress;
        int openMode;
    protected:
        I2c(int bus, int addr);
        int write(uint8_t reg, uint8_t val);
        uint8_t read(uint8_t reg);
};
#endif
