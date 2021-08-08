# Badgerloop Serial Communication Drivers

## I<sup>2</sup>C

### Creating a New I<sup>2</sup>C Device

Create a new I<sup>2</sup>C device by deriving your device off of the base I2C class

```c++
class MyI2CDevice: private I2c {
    ...
}
```

### Opening the I<sup>2</sup>C Connection

I<sup>2</sup>C devices `begin` functions should contain this open wrapper.

```c++
if(!this->is_open()) {
    this->open_i2c();
}
```

Interact with the I<sup>2</sup>C bus by using these functions

```c++
int write_byte(uint8_t reg); // Write a byte to a register
int write_data(uint8_t, uint8_t val); // Write data to a register
int read_data(uint8_t *buff, int size); //Read data from a device
uint8_t read_from_reg(uint8_t reg); // Read data from a specific register
```

## CAN Bus

A CAN object has a thread parsing its CAN bus. The canLoop thread uses the devices in its devices vector. Devices add themselves to this vector when they are passed a CAN object in their constructor.

Because devices are automatically pushed to a list, the developer need not interact with the CAN object asside from creating it initially in main.