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
#define read_two_bytes(regl,regh) ((((uint16_t)read_from_reg(regh))<<8)&((uint16_t)read_from_reg(regl)))
/**
 * Performs the following operations
 * 1) Bitwise and with a mask containing 0xFF to clear the upper bits
 * 2) Write this to the lower register
 * 3) Right shift the value with 8 (to clear the lower bits and move the upper bits lower)
 * 4) Case to uint8_t and write.
 */
#define write_two_bytes(regl,regh,val) (write_data(regl,(uint8_t)(val&0x00FF));write_data(regh,(uint8_t)(val>>8)))

#define	FIFO_CTRL1			0b00000110
#define	FIFO_CTRL2			0b00000111
#define	FIFO_CTRL3			0b00001000
#define	FIFO_CTRL4			0b00001001
#define	FIFO_CTRL5			0b00001010
#define	DRDY_PULSE_CFG_G		0b00001011
#define	INT1_CTRL
#define	INT2_CTRL
#define	WHO_AM_I
#define	CTRL1_XL
#define	CTRL2_G
#define	CTRL3_C
#define	CTRL4_C
#define	CTRL5_C
#define	CTRL6_C
#define	CTRL7_G
#define	CTRL8_XL
#define	CTRL9_XL
#define	CTRL10_C
#define	MASTER_CONFIG
#define	WAKE_UP_SRC
#define	TAP_SRC
#define	D6D_SRC
#define	STATUS_REG
#define	OUT_TEMP_L
#define	OUT_TEMP_H
#define	OUTX_L_G
#define	OUTX_H_G
#define	OUTY_L_G
#define	OUTY_H_G
#define	OUTZ_L_G
#define	OUTZ_H_G
#define	OUTX_L_XL
#define	OUTX_H_XL
#define	OUTY_L_XL
#define	OUTY_H_XL
#define	OUTZ_L_XL
#define	OUTZ_H_XL
#define	SENSORHUB1_REG
#define	SENSORHUB2_REG
#define	SENSORHUB3_REG
#define	SENSORHUB4_REG
#define	SENSORHUB5_REG
#define	SENSORHUB6_REG
#define	SENSORHUB7_REG
#define	SENSORHUB8_REG
#define	SENSORHUB9_REG
#define	SENSORHUB10_REG
#define	SENSORHUB11_REG
#define	SENSORHUB12_REG
#define	FIFO_STATUS1
#define	FIFO_STATUS2
#define	FIFO_STATUS3
#define	FIFO_STATUS4
#define	FIFO_DATA_OUT_L
#define	FIFO_DATA_OUT_H
#define	TIMESTAMP0_REG
#define	TIMESTAMP1_REG
#define	TIMESTAMP2_REG
#define	STEP_TIMESTAMP_L
#define	STEP_TIMESTAMP_H
#define	STEP_COUNTER_L
#define	STEP_COUNTER_H
#define	SENSORHUB13_REG
#define	SENSORHUB14_REG
#define	SENSORHUB15_REG
#define	SENSORHUB16_REG
#define	SENSORHUB17_REG
#define	SENSORHUB18_REG
#define	FUNC_SRC1
#define	FUNC_SRC2
#define	WRIST_TILT_IA
#define	TAP_CFG
#define	TAP_THS_6D
#define	INT_DUR2
#define	WAKE_UP_THS
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	
#define	

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
