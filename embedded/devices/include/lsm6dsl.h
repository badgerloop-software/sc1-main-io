#ifndef __lsm6dsl_h__
#define __lsm6dsl_h__

#include <stdint.h>
#include "i2c.h"

#define LSM_RESET	1
#define LSM_DEVICE_ID	01101010

/*Read from register wrapper*/
#define read_byte(reg) read_from_reg(reg)
/*Write data wrapper*/
#define write_byte(reg,val) write_data(reg,val)
/**
 * Performs the following operations:
 * 1) Read the high byte, and typecast it into a 16 bit unsigned int.
 * 2) Shift said int by 8 bits
 * 3) And the int with the value from the low byte
 */
#define read_two_bytes(regl,regh) ((((uint16_t)read_from_reg(regh))<<8)|((uint16_t)read_from_reg(regl)))
/**
 * Performs the following operations
 * 1) Bitwise and with a mask containing 0xFF to clear the upper bits
 * 2) Write this to the lower register
 * 3) Right shift the value with 8 (to clear the lower bits and move the upper bits lower)
 * 4) Case to uint8_t and write.
 */
#define write_two_bytes(regl,regh,val) (write_data(regl,(uint8_t)(val&0x00FF));write_data(regh,(uint8_t)(val>>8)))

class Lsm6dsl : private I2c{
	private:
	public:
	/**
	 * creates a new instance of the Lsm driver
	 */
	Lsm6dsl(int bus, int address);
	int begin(void);
	int read_linear_x(void);
	int read_linear_y(void);
	int read_linear_z(void);
	int read_angular_x(void);
	int read_angular_y(void);
	int read_angular_z(void);
};

/*
 * Notes
 * 3 operating modes available
 * only accelerometer
 * only gyro
 * Both active, independent ODR
 * Activate gyroscope by writing ODR_XL[3:0] in CTRL1_XL(10h)
 * Activate accelerometer by writing ODR_XL[3:0] in CTRL2_G(11h)
 *
 * for selection between high perf and low perf mode
 * G_HM_MODE bit in ctrl7_G(16h)
 * set to 0 - high perf. Set to 1 - low perf
 * For accelerometer, same deal, but with XL_HM_MODE bit in CTRL6_C(15h)
 */

#endif /*__lsm6dsl_h__*/
