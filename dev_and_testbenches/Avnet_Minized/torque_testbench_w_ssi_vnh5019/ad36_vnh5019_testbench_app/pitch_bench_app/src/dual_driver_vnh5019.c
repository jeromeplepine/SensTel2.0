/*
 * dual_driver_vnh5019.c
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */
#include "dual_driver_vnh5019.h"
#include "pwm.h"

// Non-ultrascale Zynq SoCs have 4 I/O banks; 0&1 are MIO and 2&3 are EMIO.
// In the case of the z7007s, the MIO bank pin numbers range from [53:0] while the
// EMIO pins range from [MAX:54]. Knowing this, the developer can access its EMIO
// pins declared in Vivado using the xgpiops driver by calling pin 54, for atomical functions
// ie: XGpioPs_SetDirectionPin, or the whole EMIO bank starting with bank 2, for the bank
// functions ie: XGpioPs_SetDirection.

//	Private Functions
int bankMask(int, int);

//	Public Functions
void initShieldPins(XGpioPs* bankPins){
//	Make sure initSSIpins have already been called...
	XGpioPs_SetDirection(bankPins, FPGA_BANK, (0x00000005U | OUT_REG));
	XGpioPs_SetOutputEnable(bankPins, FPGA_BANK, (0x00000005U | OUT_REG));

//	TODO: Integrate to motor ctrl function
	XGpioPs_WritePin(bankPins, PIN_M1INA, HI);
	XGpioPs_WritePin(bankPins, PIN_M1INB, LO);

	XGpioPs_WritePin(bankPins, PIN_M2INA, LO);
	XGpioPs_WritePin(bankPins, PIN_M2INB, HI);

}

//void disDriver(XGpioPs* bankPins){
//	XGpioPs_WritePin(bankPins, M1EN, LO);
//}

void getFault(XGpioPs* bankPins){
	XGpioPs_ReadPin(bankPins, PIN_M1EN);
}

void oneStep(XGpioPs* bankPins, u8 dir, u8 stepdiv){
	// this static variable lets us remember what step we're on so we
	// can change to the appropriate next state in the sequence
	static unsigned char step = 0;

	// compute the next step based on the direction argument dir
	// and the step mode.  Full stepping skips half and quarter steps,
	// and half stepping skips quarter steps.  Quarter stepping cycles
	// through all 16 steps.
	if (dir == 1)
		step += stepdiv;
	else
		step -= stepdiv;

	switch (step & 15)
	{
		case 0:	// full step (both coils energized at 71%)
			updateDriver(bankPins, 180, 180);
			break;
		case 1:	// quarter step (coil 1 at 38% and coil 2 at 92%)
			updateDriver(bankPins, 98, 236);
			break;
		case 2: // half step (coil 1 at 0% and coil 2 at 100%)
			updateDriver(bankPins, 0, 255);
			break;
		case 3: // quarter step
			updateDriver(bankPins, -98, 236);
			break;
		case 4: // full step
			updateDriver(bankPins, -180, 180);
			break;
		case 5: // quarter step
			updateDriver(bankPins, -236, 98);
			break;
		case 6: // half step
			updateDriver(bankPins, -255, 0);
			break;
		case 7: // quarter step
			updateDriver(bankPins, -236, -98);
			break;
		case 8: // full step
			updateDriver(bankPins, -180, -180);
			break;
		case 9: // quarter step
			updateDriver(bankPins, -98, -236);
			break;
		case 10: // half step
			updateDriver(bankPins, 0, -255);
			break;
		case 11: // quarter step
			updateDriver(bankPins, 98, -236);
			break;
		case 12: // full step
			updateDriver(bankPins, 180, -180);
			break;
		case 13: // quarter step
			updateDriver(bankPins, 236, -98);
			break;
		case 14: // half step
			updateDriver(bankPins, 255, 0);
			break;
		case 15: // quarter step
			updateDriver(bankPins, 236, 98);
			break;
	}
}

void updateDriver(XGpioPs* bankPins, s32 phA, s32 phB){
	if((phA>255) || (-255>phA)){return;}
	else if((phB>255) || (-255>phB)){return;}


	if(phA < 0){
//		pins = driver_pins(PHA_BWD, pins);
		setPins(bankPins, PHA, BWD);
	}
	else if(phA == 0){
//		pins = driver_pins(PHA_CUT, pins);
		setPins(bankPins, PHA, CUT);
	}

	else if(phA > 0){
//		pins = driver_pins(PHA_FWD, pins);
		setPins(bankPins, PHA, FWD);
	}

	if(phB < 0){
//		pins = driver_pins(PHB_BWD, pins);
		setPins(bankPins, PHB, BWD);
	}

	else if(phB == 0){
//		pins = driver_pins(PHB_CUT, pins);
		setPins(bankPins, PHB, CUT);
	}

	else if(phB > 0){
//		pins = driver_pins(PHB_FWD, pins);
		setPins(bankPins, PHB, FWD);
	}

	//Update register
//	reg |= ( (XGpioPs_Read(bankPins, 0x02U) & ~PHX_MASK) | pins);
//	XGpioPs_Write(bankPins, 0x02U, reg);
	//Update PWM values
	setPwm(phA, phB);
}

void setPins(XGpioPs* bankPins, u8 phase, u8 dir){
	if(phase == PHA){
		if(dir == FWD){
			XGpioPs_WritePin(bankPins, PIN_M1INA, HI);
			XGpioPs_WritePin(bankPins, PIN_M1INB, LO);
		}
		else if(dir == BWD){
			XGpioPs_WritePin(bankPins, PIN_M1INA, LO);
			XGpioPs_WritePin(bankPins, PIN_M1INB, HI);
		}
		else{
			XGpioPs_WritePin(bankPins, PIN_M1INA, LO);
			XGpioPs_WritePin(bankPins, PIN_M1INB, LO);
		}
	}
	else{	//phase b
		if(dir == FWD){
			XGpioPs_WritePin(bankPins, PIN_M2INA, HI);
			XGpioPs_WritePin(bankPins, PIN_M2INB, LO);
		}
		else if(dir == BWD){
			XGpioPs_WritePin(bankPins, PIN_M2INA, LO);
			XGpioPs_WritePin(bankPins, PIN_M2INB, HI);
		}
		else{
			XGpioPs_WritePin(bankPins, PIN_M2INA, LO);
			XGpioPs_WritePin(bankPins, PIN_M2INB, LO);
		}
	}
}


// TODO: Integrate the polulu example
void stepCmd(XGpioPs* bankPins, int* stpstate){

	int pins = 0;
//	TODO: Extract Gpio operations to a separate src & h
	pins = XGpioPs_Read(bankPins, 0x02U);

	switch (*stpstate){
	case 0: // Evaluate both of the phases' directions
		pins = bankMask(pins, STEP1);
		XGpioPs_Write(bankPins, 0x2U, pins);	// Write to the correct banks
		// Update PWM
		break;
	case 1:
		pins = bankMask(pins, STEP2);
		XGpioPs_Write(bankPins, 0x2U, pins);
		break;
	case 2:
		pins = bankMask(pins, STEP3);
		XGpioPs_Write(bankPins, 0x2U, pins);
		break;
	case 3:
		pins = bankMask(pins, STEP4);
		XGpioPs_Write(bankPins, 0x2U, pins);
	}

//	TODO: Increment the state counter
	*stpstate += 1;
	if((*stpstate >= 4) | (*stpstate < 0)){
		*stpstate = 0;
	}
}

int bankMask(int rread, int mask){
	rread |= mask;
	rread &= mask;
	return rread;
}



