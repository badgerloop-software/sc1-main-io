#include <iostream>
#include "i2c.h"

/* Also need deconsturctor to close file descriptor */
I2c::I2c(int bus, int addr) {
    this->bus = bus;
    this->deviceAddress = addr;
    std::cout << "Initializing i2c device\n";
    /*This would also open the file and set file descriptor */
}

int I2c::write(uint8_t reg, uint8_t val) {
    std::cout << "Writing " << (int)val << " to register " << (int)reg << " to device at address " << this->deviceAddress << " on bus " << this->bus << "\n";
    return 0;
}

uint8_t I2c::read(uint8_t reg) {
    std::cout << "Reading from register " << (int)reg << " in the device at address " << this->deviceAddress << " on bus " << this->bus << "\n";
    return 0;
}