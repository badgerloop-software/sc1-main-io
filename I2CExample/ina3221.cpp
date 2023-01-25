#include "ina3221.h"
#include <array>

#define INA_DEVID 0x5449
#define INA_GET_VBUS_REG(channel) (channel * 2)
#define INA_GET_CURR_REG(channel) ((channel * 2) - 1)
#define INA_GET_WARN_REG(channel) ((channel * 2) + 6)
#define INA_GET_CRIT_REG(channel) ((channel * 2) + 5)

/* Register address offsets */
#define INA_CONFIG_REG 0x00
#define INA_DEVID_REG 0xFE
#define INA_PV_UPPER_REG 0x10
#define INA_PV_LOWER_REG 0x11

/* Tresholds */

// These are all currentyl defaults
#define INA_CH1_CRIT_LIM 0x7ff8
#define INA_CH2_CRIT_LIM 0x7ff8
#define INA_CH3_CRIT_LIM 0x7ff8

#define INA_CH1_WARN_LIM 0x7ff8
#define INA_CH2_WARN_LIM 0x7ff8
#define INA_CH3_WARN_LIM 0x7ff8

#define INA_PV_LOWER_LIM 0x2328
#define INA_PV_UPPER_LIM 0x2710

/* Register Bit offsets */
#define INA_CONFIG_RST 0x8000
#define INA_VOLTAGE_MASK 0x0FFF
#define INA_VOLTAGE_SIGN 0x8000

/* Calculations */
#define INA_BVOLTAGE_MULT (.008 / 8)
#define INA_SVOLTAGE_MULT (.00004 / 8)

/*
INA3221 constructor

Shunt resistor values should be passed in ohms. 1 shunt resistor per channel
*/
Ina3221::Ina3221(int addr, float shunt1, float shunt2, float shunt3, I2C& i2c) : i2cBus(i2c) {
  this->addr = addr;
  this->shunts[0] = shunt1;
  this->shunts[1] = shunt2;
  this->shunts[2] = shunt3;
}

void formatCommand(char (& buf)[3], uint8_t reg, uint16_t val) {
  buf[0] = reg;
  buf[1] = val >> 8;
  buf[2] = val & 0xFF;
}

uint16_t getData(const char (& buf)[3]) {
    uint16_t data = 0;
    data |= buf[0] << 8;
    data |= buf[1];
    return data;
}

/**
 * Verifies connection with INA3221 by reading device ID register
 * Initiates power on reset
 */
int Ina3221::begin() {
  int rc;
  // For write operations: buf[0] is the register offset, buf[1-2] is write data
  // For read operations, buf[0-1] is the read data
  // Use formatCommand/getData helpers to manage
  char buf[3];

  // Read device register
  formatCommand(buf, INA_DEVID_REG, 0);
  if ((rc = i2cBus.write(addr, buf, 1)) || (rc = i2cBus.read(addr, buf, 2))) {
    printf("Error reading device address\n");
    return rc;
  } else if (getData(buf) != INA_DEVID) {
    printf("Did not read correct device ID, read: %d\n", getData(buf));
    return -EIO;
  }


  // Initiate Power on Reset
  formatCommand(buf, INA_CONFIG_REG, INA_CONFIG_RST);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error initiating POR\n");
    return rc;
  }


  // Set thresholds
  uint16_t temp = INA_CH1_CRIT_LIM;
  formatCommand(buf, INA_GET_CRIT_REG(1), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Crit Reg 1\n");
    return rc;
  }
  formatCommand(buf, INA_GET_CRIT_REG(2), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Crit Reg 2\n");
    return rc;
  }
  formatCommand(buf, INA_GET_CRIT_REG(3), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Crit Reg 3\n");
    return rc;
  }

  temp = INA_CH1_WARN_LIM;
  formatCommand(buf, INA_GET_WARN_REG(1), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Warn Reg 1\n");
    return rc;
  }
  formatCommand(buf, INA_GET_WARN_REG(1), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Warn Reg 2\n");
    return rc;
  }
  formatCommand(buf, INA_GET_WARN_REG(1), temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for Warn Reg 3\n");
    return rc;
  }

  temp = INA_PV_LOWER_LIM;
  formatCommand(buf, INA_PV_LOWER_REG, temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for lower limit\n");
    return rc;
  }
  temp = INA_PV_UPPER_LIM;
  formatCommand(buf, INA_PV_UPPER_REG, temp);
  if ((rc = i2cBus.write(addr, buf, 3))) {
    printf("Error setting theshold for upper limit\n");
    return rc;
  }

  return rc;
}

/*
Reads bus voltage for a specified channel. Returns volts.
*/
float Ina3221::readVoltage(int channel) {
  int16_t voltage_from_reg;
  int reg;
  int rc;
  // For write operations: buf[0] is the register offset, buf[1-2] is the write data
  // For read operations: buf[0-1] is the data
  // Use formatCommand/getData helpers to manage
  char buf[3];

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    printf("Channel out of range\n");
    return -EINVAL;
  }

  reg = INA_GET_VBUS_REG(channel);
  formatCommand(buf, reg, 0);
  if ((rc = i2cBus.write(addr, buf, 1)) || (rc = i2cBus.read(addr, buf, 2))) {
    printf("Error reading INA Voltage register %d\n", reg);
    return rc;
  }

  
  // Get actual value from register
  voltage_from_reg = getData(buf);
  if (voltage_from_reg & INA_VOLTAGE_SIGN)
    voltage_from_reg = voltage_from_reg * -1;

  return (float)voltage_from_reg * INA_BVOLTAGE_MULT;
}

/*
Reads current for a specific channel. Returns amps.
*/
float Ina3221::readCurrent(int channel) {
  int16_t current_from_reg;
  int reg;
  int rc;
  // For r/w operations: buf[0] is the register offset, buf[1-2] is the read/write data
  // Use formatCommand/getData helpers to manage
  char buf[3];

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    printf("Channel out of range\n");
    return -EINVAL;
  }

  reg = INA_GET_CURR_REG(channel);
  formatCommand(buf, reg, 0);
  if ((rc = i2cBus.write(addr, buf, 1)) || (rc = i2cBus.read(addr, buf, 2))) {
    printf("Error reading INA Current register %d\n", reg);
    return rc;
  }

  // Get actual value from register
  current_from_reg = getData(buf);
  if (current_from_reg & INA_VOLTAGE_SIGN)
    current_from_reg = current_from_reg * -1;

  // Return voltage divided by shunt resistor
  return ((float)current_from_reg * INA_SVOLTAGE_MULT) /
         this->shunts[channel - 1];
}
