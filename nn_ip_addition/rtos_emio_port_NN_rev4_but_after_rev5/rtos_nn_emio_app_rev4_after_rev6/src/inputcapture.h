/*
 * inputcapture.h
 *
 *  Created on: May 28, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_INPUTCAPTURE_H_
#define SRC_INPUTCAPTURE_H_

// Xilinx TimerCounter Ip Core driver API
#include "xtmrctr.h"
#include "xparameters.h"

#define DEVICE_TMR_0	0
#define DEVICE_TMR_1	1

void InitTmrCtrs(XTmrCtr *Inst);
void InitTmrCtrInterrupts(XTmrCtr *Inst);
void StartTmrCtrInterrupts(XTmrCtr *Inst);


#endif /* SRC_INPUTCAPTURE_H_ */
