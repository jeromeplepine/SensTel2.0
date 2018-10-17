/*
 * timer.c
 *
 *  Created on: Jun 24, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes: Driver of the Core Timer that was intended to be used in the
 *             runtime profiling facilities. Development for this was halted
 *             due to a lack of time.
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "timer.h"
#include "interrupts.h"

//==============================================================================
// FUNCTION DEFINITIONS
//==============================================================================
u32 GetScuCounterValue(XScuTimer *tmrinst)
{
	return ulCoreMicroSecondsTicks;

}

void InitScuTimer(XScuTimer *tmrinst, u32 devid)
{
	XScuTimer_Config *conf;

	conf = XScuTimer_LookupConfig( (u16)devid );
	XScuTimer_CfgInitialize(tmrinst, conf, conf->BaseAddr);

	XScuTimer_Stop(tmrinst);
//	XScuTimer_DisableInterrupt(tmrinst);
	XScuTimer_ClearInterruptStatus(tmrinst);
	XScuTimer_SetPrescaler(tmrinst, SCU_TMR_PRESCALER);
	XScuTimer_SetLoadReg(tmrinst->Config.BaseAddr, SCU_TMR_RELOAD_VAL);
//	XScuTimer_EnableAutoReload(tmrinst);
	XScuTimer_DisableAutoReload(tmrinst);
	u32 regval = XScuTimer_ReadReg(tmrinst->Config.BaseAddr, XSCUTIMER_CONTROL_OFFSET);
//	XScuTimer_RestartTimer(tmrinst);
//	XScuTimer_WriteReg(tmrinst->Config.BaseAddr, XSCUTIMER_LOAD_OFFSET, SCU_TMR_RELOAD_VAL);
//	regval = XScuTimer_ReadReg(tmrinst->Config.BaseAddr, XSCUTIMER_LOAD_OFFSET);
}

void InitScuTimerInterrupts(XScuTimer *tmrinst, Xil_ExceptionHandler handler, u16 DevIntId)
{
//	AddHandler2InitTable((void *)tmrinst, DevIntId, handler, (void *)&ExceptionHandlers);
}


void StartScuTimerInterrupts(XScuTimer *tmrinst)
{
//	XScuTimer_Start(tmrinst);
//	XScuTimer_EnableInterrupt(tmrinst);
}

