#include "lsm6dsl.h"

#include  <tgmath.h>

#define LSM_RESET 0x00000001
#define LSM_DEVID 0x01101010

#define LSM_CRTL3_C 0x12
#define LSM_WHO_AM_I 0x0F

#define XL_GS 0x08
#define XL_INC_RATE XL_GS/0x0111111111111111 

#define G_FULL_SCALE 0x00 //00 -> 11 250-2000 dps
#define G_DPS 250 * pow(2,G_FULL_SCALE)
#define G_INC_RATE (G_DPS/2)/0x0111111111111111

Lsm6dsl::Lsm6dsl(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

// https://www.st.com/content/ccc/resource/technical/document/datasheet/ee/23/a0/dc/1d/68/45/52/DM00237456.pdf/files/DM00237456.pdf/jcr:content/translations/en.DM00237456.pdf
// read angular and linear accel on all 3 axes | sample rate  
// SENSOR_SYNC_TIME_FRAME (04h) | 0000 TPH_3 TPH_2 TPH_1 TPH_0
// CTRL3_C (12h) | 1s place is software reset
//pg 60 for control settings
// pg 72 for output registers
// pg 81 for timestamp data

int Lsm6dsl::begin(){

    write_data(LSM_CRTL3_C, LSM_RESET); // Reset software
    if (LSM_DEVID != read_from_reg(0x0F)){
        return 1;
    }
}

double Lsm6dsl::getGX(){
    uint16_t val = (read_from_reg(0x23) << 8) | read_from_reg(0x22);
    return (double)val * G_INC_RATE;
}

double Lsm6dsl::getGY(){
    uint16_t val = (read_from_reg(0x25) << 8) | read_from_reg(0x24);
    return (double)val * G_INC_RATE;
}

double Lsm6dsl::getGZ(){
    uint16_t val = (read_from_reg(0x27) << 8) | read_from_reg(0x26);
    return (double)val * G_INC_RATE;
}

double Lsm6dsl::getXLX(){
    uint16_t val = (read_from_reg(0x29) << 8) | read_from_reg(0x28);
    return (double)val * XL_INC_RATE;
}

double Lsm6dsl::getXLY(){
    uint16_t val = (read_from_reg(0x2B) << 8) | read_from_reg(0x2A);
    return (double)val * XL_INC_RATE;
}

double Lsm6dsl::getXLZ(){
    uint16_t val = (read_from_reg(0x2D) << 8) | read_from_reg(0x2C);
    return (double)val * XL_INC_RATE;
}








