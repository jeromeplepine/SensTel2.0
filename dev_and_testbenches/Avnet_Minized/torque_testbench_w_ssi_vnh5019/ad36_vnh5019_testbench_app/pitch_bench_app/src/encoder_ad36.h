/*
 * encoder_ad36.h
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */
#include "xparameters.h"
#include "xgpiops.h"
#include <stdio.h>

#ifndef SRC_ENCODER_AD36_H_
#define SRC_ENCODER_AD36_H_


u32 initSSIpins(XGpioPs* bankPins);
int readPos(XGpioPs* bankPins);



#endif /* SRC_ENCODER_AD36_H_ */
