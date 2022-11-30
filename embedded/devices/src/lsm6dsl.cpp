#include "lsm6dsl.h"

#include <tgmath.h>

Lsm6dsl::Lsm6dsl(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

// https://www.st.com/content/ccc/resource/technical/document/datasheet/ee/23/a0/dc/1d/68/45/52/DM00237456.pdf/files/DM00237456.pdf/jcr:content/translations/en.DM00237456.pdf
// read angular and linear accel on all 3 axes | sample rate
// SENSOR_SYNC_TIME_FRAME (04h) | 0000 TPH_3 TPH_2 TPH_1 TPH_0
// CTRL3_C (12h) | 1s place is software reset
// pg 60 for control settings
// pg 72 for output registers
// pg 81 for timestamp data

// Just define register val in fsxl and fsg in crtl1 and crtl2
// Time stamp and frequency just wait until James ben and Noah figure it out

// Still need to add config methods | config ODR -> frequency selection for both
// full scales
// CRTL1 and 2 do the math as if its at the default value

int Lsm6dsl::begin() {
  write_data(CRTL3_C, RESET);  // Reset software
  if (DEVID != read_from_reg(WHO_AM_I)) {
    return 1;
  }
  setRangeG(0);
  setRangeXL(0);
  setPowerModeG(1);
  setPowerModeXL(1);
}
double Lsm6dsl::getGX() {
  int16_t val = (read_from_reg(OUTX_H_G) << 8) | read_from_reg(OUTX_L_G);
  return (double)twos_complement(val) *
         ((pow(2.0, g_full_scale) * 250.0) / 0xFFFF);
}

double Lsm6dsl::getGY() {
  int16_t val = (read_from_reg(OUTY_H_G) << 8) | read_from_reg(OUTY_L_G);
  return (double)twos_complement(val) *
         ((pow(2.0, g_full_scale) * 250.0) / 0xFFFF);
}

double Lsm6dsl::getGZ() {
  int16_t val = (read_from_reg(OUTZ_H_G) << 8) | read_from_reg(OUTZ_L_G);
  return (double)twos_complement(val) *
         ((pow(2.0, g_full_scale) * 250.0) / 0xFFFF);
}

double Lsm6dsl::getXLX() {
  int16_t val = (read_from_reg(OUTX_H_XL) << 8) | read_from_reg(OUTX_L_XL);
  return (double)twos_complement(val) *
         ((double)get_xl_scale(xl_full_scale) / 0xFFFF);
}

double Lsm6dsl::getXLY() {
  int16_t val = (read_from_reg(OUTY_H_XL) << 8) | read_from_reg(OUTY_L_XL);
  return (double)twos_complement(val) *
         ((double)get_xl_scale(xl_full_scale) / 0xFFFF);
}

double Lsm6dsl::getXLZ() {
  int16_t val = (read_from_reg(OUTZ_H_XL) << 8) | read_from_reg(OUTZ_L_XL);
  return (double)twos_complement(val) *
         ((double)get_xl_scale(xl_full_scale) / 0xFFFF);
}

// 1 is lowest power, 0 is off
int Lsm6dsl::setPowerModeXL(uint8_t select) {
  return write_data(CTRL1_XL, read_from_reg(CTRL1_XL) & 0x0F | select << 4);
}

int Lsm6dsl::setPowerModeG(uint8_t select) {
  return write_data(CTRL2_G, read_from_reg(CTRL2_G) & 0x0F | select << 4);
}

int Lsm6dsl::setRangeG(uint8_t select) {
  this->g_full_scale = select;
  return write_data(CTRL2_G, (read_from_reg(CTRL2_G) & 0xF3) | select << 2);
}

int get_xl_scale(int x) {
  int a[] = {4, 32, 8, 16};
  return a[x];
}

int Lsm6dsl::setRangeXL(uint8_t select) {
  this->xl_full_scale = select;
  return write_data(CTRL1_XL, (read_from_reg(CTRL2_G) & 0xF3) | select << 2);
}

// Stolen from stack overflow because mine didn't work
int16_t twos_complement(int16_t two_compliment_val) {
  int16_t sign_mask = 0x8000;
  // if positive
  if ((two_compliment_val & sign_mask) == 0) {
    return two_compliment_val;
    //  if negative
  } else {
    // invert all bits, add one, and make negative
    return -(~two_compliment_val + 1);
  }
}
