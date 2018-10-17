/*
 * spi.h
 *
 *  Created on: Jul 7, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

#include "xspips.h"
#include "xil_types.h"





void InitSpiInst(XSpiPs* inst);
void SpiWrite(XSpiPs* inst, u32* data);
u32 SpiRead(XSpiPs* inst);

#endif /* SRC_SPI_H_ */
