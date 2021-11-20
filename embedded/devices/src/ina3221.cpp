#include "ina3221.h"

#include <errno.h>

#include <iostream>

/* Register address offsets */
#define INA_CONFIG_REG 0x0
#define INA_NUM_CHANNELS 0x3

/* Register Bit offsets */
#define INA_CONFIG_RST 1 << 15
#define INA_VOLTAGE_MASK 0x0FFF
#define INA_VOLTAGE_SIGN 0x8000

/* Calculations */
#define INA_BVOLTAGE_MULT .008
#define INA_SVOLTAGE_MULT .00004

Ina3221::Ina3221(int bus, int addr, float shunt1, float shunt2, float shunt3)
    : I2c(bus, addr, O_RDWR) {
  this->shunts[0] = shunt1;
  this->shunts[1] = shunt2;
  this->shunts[2] = shunt3;
}

int Ina3221::begin() {
  int rc;

  rc = this->open_i2c();
  if (!rc) return rc;

  // Initiate POR
  rc = write_data(INA_CONFIG_REG, INA_CONFIG_RST);
  if (!rc) return rc;

  // Wait for POR to finish
  while (read_from_reg(INA_CONFIG_REG) & INA_CONFIG_RST) {
  };
  return 0;
}

float Ina3221::readVoltage(int channel) {
  uint16_t voltage_from_reg;
  int reg;
  float voltage;

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    std::cout << "Channel out of range\n";
    return -EINVAL;
  }

  reg = channel * 2;
  voltage_from_reg = read_from_reg(reg);

  // Get actual value from register
  voltage = (float)((voltage_from_reg >> 3) & INA_VOLTAGE_MASK);

  // Preserve signedness
  if (voltage_from_reg & INA_VOLTAGE_SIGN) voltage *= -1;

  return voltage * INA_BVOLTAGE_MULT;
}

float Ina3221::readCurrent(int channel) {
  uint16_t voltage_from_reg;
  int reg;
  float voltage;

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    std::cout << "Channel out of range\n";
    return -EINVAL;
  }

  reg = (channel * 2) - 1;
  voltage_from_reg = read_from_reg(reg);

  // Get actual value from register
  voltage = (float)((voltage_from_reg >> 3) & INA_VOLTAGE_MASK);

  // Preserve signedness
  if (voltage_from_reg & INA_VOLTAGE_SIGN) voltage *= -1;

  // Return voltage divided by shunt resistor
  return (voltage * INA_SVOLTAGE_MULT) / this->shunts[channel - 1];
}
