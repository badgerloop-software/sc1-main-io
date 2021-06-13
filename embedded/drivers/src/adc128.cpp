#include "adc128.h"
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>

Adc::Adc(int bus, AdcAddr adc) : I2c(bus, {(int) adc}, O_RDWR) {
    this->isInit = false;
}

int Adc::init() {
    if (this->isInit) {
        return 0;
    }
    uint8_t flush[1];
    uint8_t cmd[2];
    uint8_t reg[1];
    uint8_t data[1];

    printf("I2C Init\n");

    if(this->open_i2c() != 0) {
        fprintf(stderr, "Could not open i2c bus.\n");
        return -1;
    }

    /* check if there actually is a device there */
    if (this->read_data(flush, 1)) {
        fprintf(stderr, "There is not device at bus");
        return -1;
    }

    /* Adv Config Reg */
    reg[0] = 0x0B;
    if (this->write_byte(*reg)) {
        fprintf(stderr, "Failed t write to adv config reg\n");
        return 1;
    }

    if (this->read_data(data, 1)) {
        return 1;
    }

    /* We always need to follow read-modify-write pattern */
    data[0] &= ~(0x07);
    data[0] |= 0x03;

    cmd[0] = reg[0];
    cmd[1] = data[0];  /* Ext ref, Mode 1 */
    printf("[ADC128] Ext ref, Mode 1");
    if (this->write_data(*cmd, 2)) {
        return 1;
    }

    usleep(10000);

    /* Conv rate reg*/
    reg[0] = 0x07;
    if (this->write_data(*reg, 1)) {
        return 1;    
    }

    if (this->read_data(data, 1)) {
        return 1;    
    }

    data[0] &= ~(0x01); 
    data[0] |= 0x01;    /* Cont conv */

    cmd[0] = reg[0];
    cmd[1] = data[0];

    if (this->write_data(*cmd, 2)) {
        return 1;
    }

    usleep(10000);

    /* Limit Regs */
    /*    reg[0] = */
    /*    for int*/


    /* Config Reg */
    reg[0] = 0x00;
    if (this->write_data(*reg, 1)) {
        return 1;
    }

    if (this->read_data(data, 1)) {
        return 1;
    }
    usleep(10000);
    data[0] &= ~(0x09);
    data[0] |= 0x01;

    cmd[0] = reg[0];
    cmd[1] = data[0];

    if (this->write_data(*cmd, 2)) {
        return 1;
    }

    usleep(10000);

    if (this->write_data(*reg, 1)) {
        return 1;
    }

    if (this->read_data(data, 1)) {
        return 1;
    }
    this->isInit = true; 
    return 0;
}

/* TODO: Possible optimization, if we store as 2 8 bit ints, we could then
 * directly send rather than converting back */
uint16_t Adc::readChannel(AdcChan chan) {
    unsigned char cmd[1] = {(char) chan};

    if (!this->isInit) {
        return 0;
    }

    if (this->write_data(*cmd, 1)) {
        return 0;
    }

    unsigned char d[2];
    if (this->read_data(d, 2)) {
        return 0;
    }
    uint16_t ret = ((( (uint16_t) d[1]) & 0xf) << 8) | ((uint16_t) d[0]);
    return ret;
}

int Adc::isBusy() {
    unsigned char cmd[1];
    cmd[0] = 0x0C;
    
    if (!this->isInit) {
        return 0;
    }

    if (this->write_data(*cmd, 1)) {
        return 1;    
    }

    if (this->read_data(cmd, 1)) {
        return 1;    
    }
    printf("Check success: reg[0] & 0x03 == %d\n\r", cmd[0] & 0x03);
    /* 0x01 means its powering up, 0x02 is converting, we just generally want to know if it is free */
    return cmd[0] & 0x03; 
}

int Adc::debug() {
    printf("ADC FOUND\n\r");
    return 0;
}
