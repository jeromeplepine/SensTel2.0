/*
 * i2c.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "xparameters.h"
#include "xiicps.h"
#include "xstatus.h"

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#define I2C_ADDRESS		XPAR_PS7_I2C_1_DEVICE_ID
#define TX_BUFFER_SZ	16
#define	I2C_SPEED		100000


int I2C_write(XIicPs *i2cinst, u32 ZynqIicAddress, u8 slave_address, u8 register_offset, u8 byte_count, u8 *write_values);
int I2C_read(XIicPs *i2cinst, u32 ZynqIicAddress, u8 slave_address, u8 register_offset, u8 *read_value);
void InitI2CPeripherals(XIicPs *i2cinst, u32 Baseaddress);


#endif /* SRC_I2C_H_ */
