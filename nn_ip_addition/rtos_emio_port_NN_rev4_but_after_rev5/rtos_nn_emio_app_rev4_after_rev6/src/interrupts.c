/*
 * interrupts.c
 *
 *  Created on: May 25, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes:	Hosts most of the interface peripherals' interrupt handlers and
 *      handles the interrupts setup.
 *      Also handles registering of the interrupt handlers to the Interrupt
 *      Controller. Each peripheral software module, in the init function, has
 *      to line up their handlers and SetupInterruptSystem() then registers them
 *      all at once after all the peripherals have been initialized - this last
 *      part is done right after the scheduler is started, at the beginning of
 *      the SSI task.
 *
 *      !!! Important: Note that the Interrupt Controller is actually part of
 *      the FreeRTOS architecture port for the ARM Cortex-A9 - the port handles
 *      most of its initialization and needs it for proper execution of the
 *      scheduler - meddling with it might have undesired side effects.
 *
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "xscugic.h"
#include "xparameters.h"
#include "interrupts.h"
#include "xuartps.h"
#include "xcanps.h"
#include "timer.h"
#include "can.h"
#include "setup.h"
#include <stdio.h>
#include "ChinookCanUtils.h"
#include "ChinookSteeringWheelUtils.h"
#include "encoder_ad36.h"
#include "senstel_acq_config.h"
#include "xtime_l.h"



//==============================================================================
// PUBLIC VARIABLES
//==============================================================================
volatile int RxTimeout, RxFifoTrigFlag;	/* UART Interrupt flags */
volatile u8 i = 0;
volatile u8 PitchSystemMode = 1;
volatile u8 EnableCalibLogic = 0;


//==============================================================================
// FUNCTION DEFINITIONS
//==============================================================================
void InitHandlersArray(sInstExcptnHandlers_t *DevExcHndlrs)
/*
* \brief       Initialize the array used to line up the peripherals' interrupt
*              handlers.
*
* \param[in]   DevExcHndlrs         - Pointer to the array.
*
*/
{
	DevExcHndlrs->index = 0;
}

void AddHandler2InitTable(void *DevInstPtr, int DevIntId,
		Xil_ExceptionHandler DevHandler,
		sInstExcptnHandlers_t *DevExcHndlrs)
/*
* \brief       Lines up a peripheral's interrupt handler for later registration
*              to the Controller.
*
* \param[in]   DevInstPtr       - Pointer to the peripheral struct instance for whom we
*                                 desire to register the handler.
* \param[in]   DevIntId         - Peripheral's Interrupt Controller event ID.
* \param[in]   DevHandler       - Device's exception handler for the peripheral.
* \param[in]   DevExcHndlrs     - Container struct the function puts the peripheral
*                                 interrupt data in.
*
*/
{
	sInstExcptnHandler_t *DevInst = &DevExcHndlrs->InstHandlers[DevExcHndlrs->index];
	DevInst->DeviceExceptionHandler = DevHandler;
	DevInst->DeviceIntId = DevIntId;
	DevInst->DeviceInstancePtr = DevInstPtr;

	DevExcHndlrs->index++;
}

void PrivateTimerHandler(void *CallBackRef)
/* Could be removed - intended use was to make basic code profiling facilities
 * but I ran out of time and couldn't finish it. This is the handler for the
 * Core Timer that provides the time base.
 */
{
	u8 tmp = 0;
	i ^= 1;
	XScuTimer_ClearInterruptStatus((XScuTimer *)CallBackRef);
	XGpioPs_WritePin(PInst.EmioBankPins, 56, i);
	ulCoreMicroSecondsTicks++;
	xil_printf("scuint\n");
}


void TmrCtrHandler(void *CallBackRef, u8 TmrCtrNumber)
/*
* \brief       TmrCtr handler.
*
* \param[in]   CallBackRef      - Used by the Interrupt Controller to trace the
*                                 interrupt source's handler. (Not used by the app
*                                 code anyways)
* \param[in]   TmrCtrNumber     - Which one of the two TmrCntr are we using?
*
*/
{
	XTmrCtr *InstancePtr = (XTmrCtr *)CallBackRef;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	if(XTmrCtr_HasEventOccurred(InstancePtr->BaseAddress, TmrCtrNumber)){
		if(TmrCtrNumber == DEVICE_TMR_0){
			xSemaphoreGiveFromISR(xIc0_0AcqSem, &xHigherPriorityTaskWoken);
		}
		else if(TmrCtrNumber == DEVICE_TMR_1){
			xSemaphoreGiveFromISR(xIc0_1AcqSem, &xHigherPriorityTaskWoken);
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

	}

}

void UartHandler(void *CallBackRef, u32 Event, unsigned int EventData)
/*
* \brief       Only manages the CV7's UART interface. Since it outputs a
*              constant stream of characters and we don't want to
*              spend most of our time handling them one by one, rx automation
*              was needed. Once the rx fifo threshold is reached, we must empty
*              it. Once it is, we can resume receiving characters.
*
* \param[in]   CallBackRef
*
* \param[in]   Event      - Not used - could be removed
* \param[in]   EventData  - Not used - could be removed
*
*/
{
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	XUartPs *InstPtr = (XUartPs *)CallBackRef;
	u32 RegVal, tout = 0, rxfifotrigd = 0;

	RegVal = XUartPs_ReadReg(InstPtr->Config.BaseAddress, XUARTPS_SR_OFFSET);
	rxfifotrigd = RegVal & XUARTPS_SR_RXOVR;
	tout = RegVal & XUARTPS_IXR_TOUT;

	/* This is never reached since the event is processed in the TIMEOUT inteerupt handler before
	 * this handler here executes... */
	/* Later found out that the Xilinx supplied interrupts handler just doesnt signal any handler for TOUT
	 * so we have to evaluate it directly in here. Also found out that it never triggers - could be removed*/
	if(tout){
		xil_printf("tout\r\n");
	}

	if(rxfifotrigd){
		xSemaphoreGiveFromISR(xUartBufferSem, &xHigherPriorityTaskWoken);
		XUartPs_WriteReg(InstPtr->Config.BaseAddress, XUARTPS_CR_OFFSET,
				   (XUARTPS_CR_TORST | XUARTPS_CR_TX_DIS));
		XUartPs_SetRecvTimeout(InstPtr, UART_TIMEOUT_THRESHOLD); /* Could be removed - never triggered */
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

/*****************************************************************************/
/**
*
* Callback function (called from interrupt handler) to handle confirmation of
* transmit events when in interrupt mode.
*
* @param	CallBackRef is the callback reference passed from the interrupt
*		handler, which in our case is a pointer to the driver instance.
*
* @return	None.
*
* @note		This function is called by the driver within interrupt context.
*
******************************************************************************/
void CANSendHandler(void *CallBackRef)
/*
* \brief       CANSendHandler. No actions are taken after
*              a successful transmission.
*
* \param[in]   CallBackRef
*/
{

	/*
	 * The frame was sent successfully. Notify the task context.
	 */
	SendDone = TRUE;
}

/*****************************************************************************/
/**
*
* Callback function (called from interrupt handler) to handle frames received in
* interrupt mode.  This function is called once per frame received.
* The driver's receive function is called to read the frame from RX FIFO.
*
* @param	CallBackRef is the callback reference passed from the interrupt
*		handler, which in our case is a pointer to the device instance.
*
* @return	None.
*
* @note		This function is called by the driver within interrupt context.
*
******************************************************************************/
void CANRecvHandler(void *CallBackRef)
/*
* \brief       Used to handle received CAN messages - typically requests such
*              as steering wheel commands.
*              Note: XID is basically an SID from ChinookCanUtils or WheelUtils
*              converted to fit Xilinx's driver format.
*
* \param[in]   CallBackRef
*
*/
{
	XCanPs *CanPtr = (XCanPs *)CallBackRef;
	int Status;
	int Index, Temp;
	u8 *FramePtr;
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	static u32 count;

	Status = XCanPs_Recv(CanPtr, RxFrame);
	if (Status != XST_SUCCESS) {
		LoopbackError = TRUE;
		RecvDone = TRUE;
		return;
	}

	if(RxFrame[0] == VOLANT_SW_MSG_XID)
	{
		/* Toggle SD card data logging. Is off by default. */
		if( RxFrame[2] == AQUISITION_BUTTON )
		{
			xTaskNotifyFromISR(xSdManTask, (u32)SD_NOTICE, eSetBits, &xHigherPriorityTaskWoken);
		}

		/* Toggle zero/calib mode logic. */
		else if( RxFrame[2] == CALIB_ENGAGE_BUTTON ){
			//TODO: Implement a 3s seconds timer to match the volant's delay Should work as is though
			if(EnableCalibLogic){
				CalibSystem = 1;
				EnableCalibLogic = 0;
			}
		}
	}

	/* Toggle automatic Pitch control. Default is manual mode - no interference with
	 * the steering pitch commands. When automatic pitch is chosen, it basically mimics
	 * what would happen if the car's pilot was issuing the commands */
	if( RxFrame[0] == PITCHSYS_MODE_XID){
		PitchSysMode = RxFrame[2];
	}

	/* Automatic pitch related - pitch set point is reached. */
	if( RxFrame[0] == PITCHSYS_DONE_XID){
		PitchCmdDone = 1;
	}

	if( (RxFrame[0] == PITCHSYS_ZERO_XID) | (RxFrame[0] == WINDDIR_ZERO_XID) | !CalibSystem){
		EnableCalibLogic = 1;
		switch(RxFrame[0]){
			case PITCHSYS_ZERO_XID:
				SystemToZero = PitchAbsEnc;
				break;
			case WINDDIR_ZERO_XID:
				SystemToZero = Cv7_Wdir;
				break;
			case GEAR_ZERO_XID:
				SystemToZero = GearAbsEnc;
				break;
		}
	}

	/* For debug purposes */
	Temp = (21 << (int)RxFrame[0]);


	/* Remnants from Xilinx's driver exmaple code */
	if ((RxFrame[1] & ~XCANPS_DLCR_TIMESTAMP_MASK) != TxFrame[1]) {
		LoopbackError = TRUE;
		RecvDone = TRUE;
		return;
	}

	RecvDone = TRUE;
}

/*****************************************************************************/
/**
*
* Callback function (called from interrupt handler) to handle error interrupt.
* Error code read from Error Status register is passed into this function.
*
* @param	CallBackRef is the callback reference passed from the interrupt
*		handler, which in our case is a pointer to the driver instance.
* @param	ErrorMask is a bit mask indicating the cause of the error.
*		Its value equals 'OR'ing one or more XCANPS_ESR_* defined in
*		xcanps_hw.h.
*
* @return	None.
*
* @note		This function is called by the driver within interrupt context.
*
******************************************************************************/
void CANErrorHandler(void *CallBackRef, u32 ErrorMask)
/*
 * Not used - could be removed
 */
{

	if(ErrorMask & XCANPS_ESR_ACKER_MASK) {
		/*
		 * ACK Error handling code should be put here.
		 */
	}

	if(ErrorMask & XCANPS_ESR_BERR_MASK) {
		/*
		 * Bit Error handling code should be put here.
		 */
	}

	if(ErrorMask & XCANPS_ESR_STER_MASK) {
		/*
		 * Stuff Error handling code should be put here.
		 */
	}

	if(ErrorMask & XCANPS_ESR_FMER_MASK) {
		/*
		 * Form Error handling code should be put here.
		 */
	}

	if(ErrorMask & XCANPS_ESR_CRCER_MASK) {
		/*
		 * CRC Error handling code should be put here.
		 */
	}

	/*
	 * Set the shared variables.
	 */
	LoopbackError = TRUE;
	RecvDone = TRUE;
	SendDone = TRUE;
}

/*****************************************************************************/
/**
*
* Callback function (called from interrupt handler) to handle the following
* interrupts:
*   - XCANPS_IXR_BSOFF_MASK:	Bus Off Interrupt
*   - XCANPS_IXR_RXOFLW_MASK:	RX FIFO Overflow Interrupt
*   - XCANPS_IXR_RXUFLW_MASK:	RX FIFO Underflow Interrupt
*   - XCANPS_IXR_TXBFLL_MASK:	TX High Priority Buffer Full Interrupt
*   - XCANPS_IXR_TXFLL_MASK:	TX FIFO Full Interrupt
*   - XCANPS_IXR_WKUP_MASK:	Wake up Interrupt
*   - XCANPS_IXR_SLP_MASK:	Sleep Interrupt
*   - XCANPS_IXR_ARBLST_MASK:	Arbitration Lost Interrupt
*
*
* @param	CallBackRef is the callback reference passed from the
*		interrupt Handler, which in our case is a pointer to the
*		driver instance.
* @param	IntrMask is a bit mask indicating pending interrupts.
*		Its value equals 'OR'ing one or more of the XCANPS_IXR_*_MASK
*		value(s) mentioned above.
*
* @return	None.
*
* @note		This function is called by the driver within interrupt context.
* 		This function should be changed to meet specific application
*		needs.
*
******************************************************************************/
void CANEventHandler(void *CallBackRef, u32 IntrMask)
{
	XCanPs *CanPtr = (XCanPs *)CallBackRef;

	if (IntrMask & XCANPS_IXR_BSOFF_MASK) {
		/*
		 * Entering Bus off status interrupt requires
		 * the CAN device be reset and reconfigured.
		 */
		XCanPs_Reset(CanPtr);
		return;
	}

	if(IntrMask & XCANPS_IXR_RXOFLW_MASK) {
		/*
		 * Code to handle RX FIFO Overflow Interrupt should be put here.
		 */
	}

	if(IntrMask & XCANPS_IXR_RXUFLW_MASK) {
		/*
		 * Code to handle RX FIFO Underflow Interrupt
		 * should be put here.
		 */
	}

	if(IntrMask & XCANPS_IXR_TXBFLL_MASK) {
		/*
		 * Code to handle TX High Priority Buffer Full
		 * Interrupt should be put here.
		 */
	}

	if(IntrMask & XCANPS_IXR_TXFLL_MASK) {
		/*
		 * Code to handle TX FIFO Full Interrupt should be put here.
		 */
	}

	if (IntrMask & XCANPS_IXR_WKUP_MASK) {
		/*
		 * Code to handle Wake up from sleep mode Interrupt
		 * should be put here.
		 */
	}

	if (IntrMask & XCANPS_IXR_SLP_MASK) {
		/*
		 * Code to handle Enter sleep mode Interrupt should be put here.
		 */
	}

	if (IntrMask & XCANPS_IXR_ARBLST_MASK) {
		/*
		 * Code to handle Lost bus arbitration Interrupt
		 * should be put here.
		 */
	}
}

int SetupInterruptSystem(XScuGic *IntcInstancePtr, sInstExcptnHandlers_t *DevExcHndlrs)
/*
* \brief       Registers all of the peripheral interrupt handlers and their vector IDs
*              to the Interrupt Controller.
*              !! Note: During the development, it was useful to always know how many
*              peripheral interrupts were currently enabled. If the amount of lined up
*              periph ints doesn't match DRIVER_INST_HANDLER_NUM, no interrupts happen
*              at all. Make sure to update this define when adding an interrupt. Or
*              just remove this if it annoys you too much.
*
* \param[in]   IntcInstancePtr     - Interrupt Controller peripheral struct instance
* \param[in]   DevExcHndlrs        - Array where the
*/
{
	int Status;

	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler) XScuGic_InterruptHandler,
				IntcInstancePtr);

	/*
	 * If not enough device exception handlers have been registered
	 */
	if (DevExcHndlrs->index != DRIVER_INST_HANDLER_NUM) {
			return XST_FAILURE;
		}

	/*
	 * Connect device driver handlers
	 */
	for(int i = 0; i < DRIVER_INST_HANDLER_NUM; i++){
		sInstExcptnHandler_t inst = DevExcHndlrs->InstHandlers[i];
		Status = XScuGic_Connect(IntcInstancePtr, inst.DeviceIntId,
					  inst.DeviceExceptionHandler,
					  inst.DeviceInstancePtr);

		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/* Enable the interrupt for the device */
		XScuGic_Enable(IntcInstancePtr, inst.DeviceIntId);
	}

	return XST_SUCCESS;
}

void StartScuGicInterrupts()
/*
* \brief       Enables the global interrupt controller's interrupts,
*  		       which allows all configured interrupts to start.
*/
{
	/* Enable interrupts */
	 Xil_ExceptionEnable();
}
