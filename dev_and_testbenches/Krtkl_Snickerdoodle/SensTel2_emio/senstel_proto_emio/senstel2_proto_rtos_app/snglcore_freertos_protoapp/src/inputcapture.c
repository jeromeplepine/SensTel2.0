/*
 * inputcapture.c
 *
 *  Created on: May 28, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "inputcapture.h"
#include "interrupts.h"


void InitTmrCtrs(XTmrCtr *Inst)
{
	XTmrCtr_Config *TmpConf;
	u32 csRegValue = 0;

	TmpConf = XTmrCtr_LookupConfig(DEVICE_TMR_0);
	XTmrCtr_CfgInitialize(Inst, TmpConf, XPAR_AXI_TIMER_0_BASEADDR);

	XTmrCtr_SetOptions(Inst, DEVICE_TMR_0,
				XTC_INT_MODE_OPTION);

	csRegValue = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, DEVICE_TMR_0);
	csRegValue |= XTC_CSR_INT_OCCURED_MASK \
			| XTC_CSR_EXT_CAPTURE_MASK \
			| XTC_CSR_CAPTURE_MODE_MASK \
			| XTC_CSR_ENABLE_TMR_MASK;
	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, DEVICE_TMR_0, csRegValue);

	XTmrCtr_SetOptions(Inst, DEVICE_TMR_1,
				XTC_INT_MODE_OPTION);

	csRegValue = XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, DEVICE_TMR_1);
	csRegValue |= XTC_CSR_INT_OCCURED_MASK \
			| XTC_CSR_EXT_CAPTURE_MASK \
			| XTC_CSR_CAPTURE_MODE_MASK \
			| XTC_CSR_ENABLE_TMR_MASK;
	XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR, DEVICE_TMR_1, csRegValue);

	XTmrCtr_Start(Inst, DEVICE_TMR_0);
	XTmrCtr_Start(Inst, DEVICE_TMR_1);

}


void InitTmrCtrInterrupts(XTmrCtr *Inst)
{
//	XScuGic_SetPriorityTriggerType(IntcInstancePtr, IntrId, 0xA0, 0x3);
	XTmrCtr_SetHandler(Inst, (void *) TmrCtrHandler, (void *)Inst);
	//TODO: Implement Interrupts for second half once the first is validated
	//	XTmrCtr_SetHandler(Inst1, (void *) XTmrCtr_InterruptHandler, (void *)Inst1);


	AddHandler2InitTable(Inst, XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR,
			(Xil_InterruptHandler) XTmrCtr_InterruptHandler,
			(void *)&ExceptionHandlers);

}

void StartTmrCtrInterrupts(XTmrCtr *Inst)
{
//	XTmrCtr_EnableIntr(Inst->BaseAddress, DEVICE_TMR_0);
}

