/*
 * pwm.h
 *
 *  Created on: Mar 25, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "xttcps.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "xstatus.h"
#include <stdlib.h>

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define PCLK_FREQ_HZ		XPAR_XTTCPS_0_CLOCK_HZ /* Input freq */
#define TTC_NUM_DEVICES		2 /* A table holds the device base addresses*/
#define TTC_OUT1			1
#define TTC_OUT2			2

#define TABLE_OFFSET		9
#define MAX_LOOP_COUNT		0xFF
#define PWM_SETUP			{20000, 50, 16}

typedef struct {
	u32 OutputHz;		/* The frequency the timer should output on the
				   waveout pin */
	u8 OutputDutyCycle;	/* The duty cycle of the output wave as a
				   percentage */
	u8 PrescalerValue;	/* Value of the prescaler in the Count Control
				   register */
} TmrCntrSetup;

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

int TmrCtrLowLevelExample(u8 SettingsTableOffset);
// Inits a/the TTC(s) in interval mode for PWM output
int configTtc(XTtcPs* timerInst, u8 SettingsTableOffset, TmrCntrSetup *CurrSetup);
// Changes the Match value the TTC uses as the waveoutput toggle point
void setPwm(s32 pwValA, s32 pwValB);
u32 normPercent(s32);
void testPwm(int* state, int ttcCounter, int tableOffset);


/************************** Variable Definitions *****************************/




#endif /* SRC_PWM_H_ */
