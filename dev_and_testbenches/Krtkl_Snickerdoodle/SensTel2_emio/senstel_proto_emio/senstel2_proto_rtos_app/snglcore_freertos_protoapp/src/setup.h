/*
 * setup.h
 *
 *  Created on: May 27, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_SETUP_H_
#define SRC_SETUP_H_

#include "can.h"
#include "uart.h"
#include "timer.h"
#include "i2c.h"
#include "inputcapture.h"
#include "encoder_ad36.h"

//==============================================================================
// TYPE DEFINITIONS
//==============================================================================
typedef struct sPeriphInstances sPeriphInstances_t;


//==============================================================================
// VARIABLE DEFINITIONS
//==============================================================================
struct sPeriphInstances{
	XCanPs * CanInst;
	XUartPs *Cv7UartInst, *SerialUartInst;
	XTmrCtr *TmrCtr0Inst, *TmrCtr1Inst;
	XIicPs *Iic0Inst, *Iic1Inst;
	XGpioPs *EmioBankPins;
	XScuTimer *CoreTimer;
};


//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================
void CreatePeriphInstances(sPeriphInstances_t *pinst);
void InitPeripherals(sPeriphInstances_t *pinst);
void StartPeripheralInterrupts(sPeriphInstances_t *pinst);

#endif /* SRC_SETUP_H_ */
