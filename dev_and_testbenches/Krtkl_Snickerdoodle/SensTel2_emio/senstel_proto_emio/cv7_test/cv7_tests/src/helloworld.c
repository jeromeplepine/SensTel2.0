/******************************************************************************
*
* Copyright (C) 2010 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/****************************************************************************/
/**
* @file     xuartps_low_echo_example.c
*
* Basic CV7 test on the SensTel2 pre-outdoor tests prototype.
* UART 0 is used as the user serial console and UART1 is the CV7
* Rx interface. 4800, 8 data, no parity, 1 stop
*
* @note
* The test hangs if communication channel from the user terminal to the device
* is broken.
*
* MODIFICATION HISTORY:
* <pre>
* Ver   Who    Date     Changes
* ----- ------ -------- -----------------------------------------------------
* 1.00a drg/jz 01/13/10 First release
* 3.4   ms     01/23/17 Added xil_printf statement in main function to
*                       ensure that "Successfully ran" and "Failed" strings
*                       are available in all examples. This is a fix for
*                       CR-965028.
* </pre>
****************************************************************************/

/***************************** Include Files *******************************/

#include "xparameters.h"
#include "xstatus.h"
#include "xscugic.h"	//Interrupts driver
#include "xil_types.h"
#include "xil_assert.h"
#include "xuartps_hw.h"
#include "xuartps.h"
#include "xil_printf.h"
#include "stdio.h"
#include "fifo.h"

/************************** Constant Definitions ***************************/

/*
 * CV7 input uart interface
 */
#define UART_BASEADDR		XPAR_XUARTPS_1_BASEADDR
#define UART_CLOCK_HZ		XPAR_XUARTPS_1_CLOCK_HZ
/*
 * The following constant controls the length of the buffers to be sent
 * and received with the device. This constant must be 32 bytes or less so the
 * entire buffer will fit into the TX and RX FIFOs of the device.
 */
#define TEST_BUFFER_SIZE	16

#define RXFIFO_TRIG_LVL		28		// Only valuable part of CV7-OEM payload, at beginning
#define NMEA_BUF_SZ			32
#define NMEA_BCKSLSH_HEX	0x5C
#define STR_TERMINATOR		'\0'
#define TOUT_TEST_PRINT_QTY	8
#define UART_INT			XUARTPS_IMR_OFFSET
#define UART_DEVICE_ID		XPAR_XUARTPS_1_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define UART_INT_IRQ_ID		XPAR_XUARTPS_1_INTR


#define CHAR_ESC		0x1b	/* 'ESC' character is used as terminator */

/**************************** Type Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *******************/

/************************** Function Prototypes ****************************/

int UartPsEchoExample(u32 Uart0BaseAddress, u32 Uart1BaseAddress);
void InitUartModules(u32 Uart0BaseAddress,u32 Uart1BaseAddress);
void InitUartModuleswAPI(XUartPs_Config*, XUartPs_Config*);
//void InitUartModuleswAPI(XUartPs_Config*);
void UartHandler(void *CallBackRef, u32 Event, unsigned int EventData);
static int SetupInterruptSystem(XScuGic *IntcInstancePtr,
				XUartPs *UartInstancePtr,
				u16 UartIntrId);

/************************** Variable Definitions ***************************/

/*
 * The following buffers are used in this example to send and receive data
 * with the UART.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];	/* Buffer for Transmitting Data */
XUartPs Cv7UartInst;	/* Cv7 Sensor Uart interface */
XUartPs SnickerUartInst;	/* Cv7 Sensor Uart interface */
XScuGic INTCInst;	/* Interrupt controller instance */

u8	RxFifoTrigFlag = 0;
u8	RxTimeout = 0;

sFifo_t *sNmeaFifo;
char pcNmeaBuf[NMEA_BUF_SZ];
u8 NmeaStatusFlag = 0;
char str_end[3] = "\r\n";

enum eNmeaSeq{
	NmeaNone= 0,
	NmeaDollr,
	NmeaI1,
	NmeaI2,
	NmeaM,
	NmeaW,
	NmeaV,
	NmeaComma,
	NmeaStar,
	NmeaSeqLocked
};


/***************************************************************************/
/**
*
* Main function to call the Uart Echo example.
*
* @param	None
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None
*
****************************************************************************/
int main(void)
{
	int Status;
	XUartPs_Config *Config;
	XUartPs_Config Config0;
	XUartPs_Config Config1;

//
//	Config = XUartPs_LookupConfig(XPAR_XUARTPS_1_DEVICE_ID);
//	if (NULL == Config) {
//		return XST_FAILURE;
//	}
//
//	Status = XUartPs_CfgInitialize(&Cv7UartInst, Config, Config->BaseAddress);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}

	fifo_init(sNmeaFifo, (void *)pcNmeaBuf, NMEA_BUF_SZ);
	InitUartModuleswAPI(&Config0, &Config1);
//	InitUartModuleswAPI(Config1);	// Doesnt work with only one argument.... wtf
//	InitUartModules(XPAR_PS7_UART_1_BASEADDR, XPAR_PS7_UART_0_BASEADDR);
	/*
	 * Run the Uart Echo example , specify the Base Address that is
	 * generated in xparameters.h
	 */
	Status = UartPsEchoExample(XPAR_PS7_UART_1_BASEADDR, XPAR_PS7_UART_0_BASEADDR);
	if (Status != XST_SUCCESS) {
		xil_printf("Uartps low echo Example Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Uartps low echo Example\r\n");
	return XST_SUCCESS;
}


/**************************************************************************/
/**
*
* This function does a minimal test on the UART device using the hardware
* interface.
*
* @param	UartBaseAddress is the base address of the device
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful
*
* @note		None.
*
**************************************************************************/
int UartPsEchoExample(u32 Uart0BaseAddress,u32 Uart1BaseAddress)
{
	int Index, Status, CrRegVal, n;
	u32 Running, IntrMask, RxdBytes, TxdBytes;
	u8 RecvChar;
	u8 CharFifo[RXFIFO_TRIG_LVL];
	char CharFifo2[128];
	char RecvChar2, c1;
	float wspd, wdir;

	Running = TRUE;

	/*
	 * Connect the UART to the interrupt subsystem such that interrupts
	 * can occur. This function is application specific.
	 */
	Status = SetupInterruptSystem(&INTCInst, &Cv7UartInst,	\
			UART_INT_IRQ_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handlers for the UART that will be called from the
	 * interrupt context when data has been sent and received, specify
	 * a pointer to the UART driver instance as the callback reference
	 * so the handlers are able to access the instance data
	 */
	XUartPs_SetHandler(&Cv7UartInst, (XUartPs_Handler)&UartHandler, &Cv7UartInst);

	/*
	 * Enable the interrupt of the UART so interrupts will occur
	 */
	IntrMask = XUARTPS_IXR_RXOVR;

	XUartPs_SetInterruptMask(&Cv7UartInst, IntrMask);

	while (Running) {
		if(RxFifoTrigFlag){
//			char RecvChar2;
			for(int i = 0; i < RXFIFO_TRIG_LVL; i++){
				RecvChar2 = XUartPs_ReadReg(XPAR_XUARTPS_1_BASEADDR, XUARTPS_FIFO_OFFSET);
				if(NmeaStatusFlag != NmeaComma){
					if( (RecvChar2 == '$') && (NmeaStatusFlag == NmeaNone) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == 'I') && (NmeaStatusFlag == NmeaDollr) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == 'I') && (NmeaStatusFlag == NmeaI1) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == 'M') && (NmeaStatusFlag == NmeaI2) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == 'W') && (NmeaStatusFlag == NmeaM) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == 'V') && (NmeaStatusFlag == NmeaW) ){
						NmeaStatusFlag++;
					}
					else if( (RecvChar2 == ',') && (NmeaStatusFlag == NmeaV) ){
						NmeaStatusFlag++;
					}
				}
				else if(NmeaStatusFlag == NmeaComma){
					if(RecvChar2 == '*'){
						NmeaStatusFlag = 0;
						fifo_write(sNmeaFifo, (void *)str_end, 2);
						n = sscanf(pcNmeaBuf, "%f,%c,%f%*s", &wdir, &c1, &wspd);
						printf("%f %f\r\n", wspd, wdir);
						fifo_reset(sNmeaFifo);
						CrRegVal = XUartPs_ReadReg(XPAR_XUARTPS_1_BASEADDR, XUARTPS_CR_OFFSET);
						XUartPs_WriteReg(XPAR_XUARTPS_1_BASEADDR, XUARTPS_CR_OFFSET, (CrRegVal | XUARTPS_CR_RXRST) );
					}
					else if(RecvChar2 != '\0'){
						fifo_write(sNmeaFifo, (void *)&RecvChar2, 1);
					}
				}
			}

			RxFifoTrigFlag = 0;
		}

		if(RxTimeout){
			for(int i=0; i < TOUT_TEST_PRINT_QTY; i++){
				XUartPs_WriteReg(Uart1BaseAddress,  XUARTPS_FIFO_OFFSET,
										  'z');
			}
			RxTimeout = 0;
		}
	}

	return XST_SUCCESS;
}

/*
 * For some reason, using the funciton with onlu config1 doesnt work. I have to
 * also use config0 as empty shell to obtain the readings from cv7..... very weird indeed
 */
void InitUartModuleswAPI(XUartPs_Config* config0, XUartPs_Config* config1)
//void InitUartModuleswAPI(XUartPs_Config* config1)
{
	u8 opermode1, opermode0;
	XUartPsFormat format1;
	XUartPsFormat format0;

	config0 = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
	XUartPs_CfgInitialize(&SnickerUartInst, config0, config0->BaseAddress);
//	opermode0 = XUartPs_GetOperMode(&SnickerUartInst);
//	XUartPs_GetDataFormat(&SnickerUartInst, format0);

	config1 = XUartPs_LookupConfig(XPAR_XUARTPS_1_DEVICE_ID);
	XUartPs_CfgInitialize(&Cv7UartInst, config1, config1->BaseAddress);
	opermode1 = XUartPs_GetOperMode(&Cv7UartInst);
	XUartPs_GetDataFormat(&Cv7UartInst, &format1);
	format1.BaudRate = 4800;
	XUartPs_SetDataFormat(&Cv7UartInst, &format1);


}

void InitUartModules(u32 Uart0BaseAddress,u32 Uart1BaseAddress)
{
	u32 CntrlRegister0, CntrlRegister1, BaudModeRegister, BaudGeneratorRegister, BaudRDividerRegister,	\
		RxTrigLvl0;

	// UART 0 init: 8bits, no parity, 1 stop bit, div/8 uart ref clk sel (but the latter might not be right).
	// Set BR in Vivado at 4800. This is for the CV7 Rx
	CntrlRegister0 = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_CR_OFFSET);
	BaudModeRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_MR_OFFSET);
	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_MR_OFFSET,
//			(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE | XUARTPS_MR_CLKSEL);
	(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE);
	// Correct settings validation for UART 0
	BaudModeRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_MR_OFFSET);
	BaudGeneratorRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_BAUDGEN_OFFSET);
	BaudRDividerRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_BAUDDIV_OFFSET);
	RxTrigLvl0 = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_RXWM_OFFSET);	// Reset value of 0x20

	// UART 1 init: 8bits, no parity, 1 stop bit, div/8 uart ref clk sel (but the latter might not be right).
	// Set BR in Vivado at 9600. This is for the terminal data dump.
	CntrlRegister1 = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_CR_OFFSET);
	BaudModeRegister = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_MR_OFFSET);
	XUartPs_WriteReg(Uart1BaseAddress, XUARTPS_MR_OFFSET,
//				(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE | XUARTPS_MR_CLKSEL);
	(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE);
	BaudModeRegister = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_MR_OFFSET);
	// The following clock settings are taken care of in Vivado, PS properties, PS-PL configuraiton, general.
//	BaudGeneratorRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_BAUDGEN_OFFSET);
//	XUartPs_WriteReg(UartBaseAddress, XUARTPS_BAUDGEN_OFFSET,

	/* Enable TX and RX for the device */
	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_CR_OFFSET,
			  ((CntrlRegister0 & ~XUARTPS_CR_EN_DIS_MASK) |
	   	   	   XUARTPS_CR_RX_EN));
	/*
	 * Cv7, a part of its output thats only really valuable, is 28 bits long:
	 * $IIMWV,225.0,R,000.0,N,A *38
	 */
	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_RXWM_OFFSET, RXFIFO_TRIG_LVL);
	RxTrigLvl0 = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_RXWM_OFFSET);	// Reset value of 0x20

	XUartPs_WriteReg(Uart1BaseAddress, XUARTPS_CR_OFFSET,
				  ((CntrlRegister1 & ~XUARTPS_CR_EN_DIS_MASK) |
//				   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));
	   	   	   	   XUARTPS_CR_TX_EN));

}

void UartHandler(void *CallBackRef, u32 Event, unsigned int EventData)
{
//	int temp_evntdat;
	/* All of the data has been received */
	if (Event == XUARTPS_IXR_RXOVR) {
//		temp_evntdat = EventData;
		RxFifoTrigFlag = 1;
	}

	/*
	 * Data was received, but not the expected number of bytes, a
	 * timeout just indicates the data stopped for 8 character times
	 */
	if (Event == XUARTPS_EVENT_RECV_TOUT) {
//		temp_evntdat = EventData;
		RxTimeout = 1;
	}
}

static int SetupInterruptSystem(XScuGic *IntcInstancePtr,
				XUartPs *UartInstancePtr,
				u16 UartIntrId)
{
	int Status;

#ifdef XPAR_INTC_0_DEVICE_ID
#ifndef TESTAPP_GEN
	/*
	 * Initialize the interrupt controller driver so that it's ready to
	 * use.
	 */
	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif
	/*
	 * Connect the handler that will be called when an interrupt
	 * for the device occurs, the handler defined above performs the
	 * specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(IntcInstancePtr, UartIntrId,
		(XInterruptHandler) XUartPs_InterruptHandler, UartInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

#ifndef TESTAPP_GEN
	/*
	 * Start the interrupt controller so interrupts are enabled for all
	 * devices that cause interrupts.
	 */
	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif
	/*
	 * Enable the interrupt for uart
	 */
	XIntc_Enable(IntcInstancePtr, UartIntrId);

	#ifndef TESTAPP_GEN
	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler) XIntc_InterruptHandler,
				IntcInstancePtr);
	#endif
#else
#ifndef TESTAPP_GEN
	XScuGic_Config *IntcConfig; /* Config for interrupt controller */

	/* Initialize the interrupt controller driver */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the interrupt controller interrupt handler to the
	 * hardware interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler) XScuGic_InterruptHandler,
				IntcInstancePtr);
#endif

	/*
	 * Connect a device driver handler that will be called when an
	 * interrupt for the device occurs, the device driver handler
	 * performs the specific interrupt processing for the device
	 */
	Status = XScuGic_Connect(IntcInstancePtr, UartIntrId,
				  (Xil_ExceptionHandler) XUartPs_InterruptHandler,
				  (void *) UartInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Enable the interrupt for the device */
	XScuGic_Enable(IntcInstancePtr, UartIntrId);

#endif
#ifndef TESTAPP_GEN
	/* Enable interrupts */
	 Xil_ExceptionEnable();
#endif

	return XST_SUCCESS;
}

