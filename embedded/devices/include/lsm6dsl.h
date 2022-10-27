#ifndef __lsm6dsl_h__
#define __lsm6dsl_h__

#include <stdint.h>
#include "i2c.h"

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
