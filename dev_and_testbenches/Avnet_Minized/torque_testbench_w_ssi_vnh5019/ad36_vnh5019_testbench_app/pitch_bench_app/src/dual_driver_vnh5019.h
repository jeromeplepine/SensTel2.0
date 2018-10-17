/*
 * dual_driver_vnh5019.h
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */
#ifndef SRC_DUAL_DRIVER_VNH5019_H_
#define SRC_DUAL_DRIVER_VNH5019_H_

#include "xparameters.h"
#include "xgpiops.h"

#define	FPGA_BANK	0x2U

#define PIN_M1INA	58
#define PIN_M1INB	59
#define	PIN_M1EN	60
#define PIN_M2INA	61
#define PIN_M2INB	62
//#define	M1PWM	63	// Set elsewhere as TTC waveouts
//#define M2PWM	64
#define	PIN_M2EN	63
#define	PIN_M1CS	64
#define PIN_M2CS	65

// HI means a pin is an output. The four LSBs are an SSI config
#define OUT_M1INA	(HI << 4)
#define OUT_M1INB	(HI << 5)
#define	OUT_M1EN	(LO << 6)
#define OUT_M2INA	(HI << 7)
#define OUT_M2INB	(HI << 8)
#define	OUT_M2EN	(LO << 9)
#define	OUT_M1CS	(LO << 10)
#define OUT_M2CS	(LO << 11)

#define OUT_REG		(OUT_M1INA|OUT_M1INB|OUT_M1EN|OUT_M2INA| \
					OUT_M2INB|OUT_M2EN|OUT_M1CS|OUT_M2CS)

#define HI		1
#define	LO		0

#define FWD		0
#define BWD		1
#define	CUT		2

#define STEP1	0b000010010000
#define STEP2	0b000010010000
#define	STEP3	0b000010010000
#define STEP4	0b000010010000

// Depending on your EMIO setup in Vivado.
// I have 12 GPIO as EMIO, their offset ranging from 54 to <max>
#define PHA			0
#define PHB			1
#define PHA_OFST	4
#define PHB_OFST	7
#define PHA_FWD		(0x01 << PHA_OFST)
#define PHB_FWD		(0x01 << PHB_OFST)
#define PHA_CUT		(0x00 << PHA_OFST)
#define PHB_CUT		(0x00 << PHB_OFST)
#define PHA_BWD		(0x10 << PHA_OFST)
#define PHB_BWD		(0x10 << PHB_OFST)
#define	PHX_MSK_OFS	4
#define PHX_MASK	(0x1B << PHX_MSK_OFS)
#define SET_A_FWD	XGpioPs_WritePin(bankPins, PIN_M1INA, HI)

#define FULSTEP		4
#define HALFSTEP	2
#define	QRTRSTEP	1


void initShieldPins(XGpioPs* bankPins);
void disDriver(XGpioPs* bankPins);
void oneStep(XGpioPs* bankPins, u8 dir, u8 stepdiv);
void updateDriver(XGpioPs* bankPins, s32 phA, s32 phB);
void setPins(XGpioPs* bankPins, u8 phase, u8 dir);
void stepCmd(XGpioPs* bankPins, int* stpstate);


#endif /* SRC_DUAL_DRIVER_VNH5019_H_ */
