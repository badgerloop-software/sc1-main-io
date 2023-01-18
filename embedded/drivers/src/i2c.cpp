#include "i2c.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

/* Also need deconsturctor to close file descriptor */
I2c::I2c(int bus, int addr, int mode)
    : bus(bus), deviceAddress(addr), openMode(mode), fd(-1) {}

I2c::~I2c() {
  if (!(fd < 0)) close(fd);
}

bool I2c::is_open() { return fd != -1; }

int I2c::open() {
  char filename[20];

  if (is_open()) return 0;

  if (bus < 0 || !deviceAddress || !openMode) {
    std::cerr << "Device not inited.\n";
    return -EINVAL;
  }

  sprintf(filename, "/dev/i2c-%d", bus);
  fd = ::open(filename, openMode);
  if (fd < 0) {
    std::cerr << "Error - Could not open file\n";
    return -ENODEV;
  }

  if (ioctl(fd, I2C_SLAVE, deviceAddress)) {
    std::cerr << "Error Could not set I2C Address\n";
  }

  return 0;
}

int I2c::read_byte(uint8_t reg) { return i2c_smbus_read_byte_data(fd, reg); }

int I2c::read_word(uint8_t reg) { return i2c_smbus_read_word_data(fd, reg); }

int I2c::write_byte(uint8_t reg, uint8_t val) {
  return i2c_smbus_write_byte_data(fd, reg, val);
}

int I2c::write_word(uint8_t reg, uint16_t val) {
  return i2c_smbus_write_word_data(fd, reg, val);
}
