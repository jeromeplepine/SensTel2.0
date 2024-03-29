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
* This file contains a design example using the hardware interface.
*
* First, certain character sequence is output onto the terminal. Then any
* characters typed in are echoed back, for letters, cases are switched.
* An 'ESC' character terminates the execution of the example.
*
* This example requires an external SchmartModule to be connected to the
* appropriate pins for the device through a daughter board. The test uses
* the default settings of the device:
*	. baud rate of 9600
*	. 8 bits data
* 	. 1 stop bit
* 	. no parity
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
#include "xil_types.h"
#include "xil_assert.h"
#include "xuartps_hw.h"
#include "xuartps.h"
#include "xil_printf.h"

/************************** Constant Definitions ***************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART_BASEADDR		XPAR_XUARTPS_0_BASEADDR
#define UART_CLOCK_HZ		XPAR_XUARTPS_0_CLOCK_HZ
/*
 * The following constant controls the length of the buffers to be sent
 * and received with the device. This constant must be 32 bytes or less so the
 * entire buffer will fit into the TX and RX FIFOs of the device.
 */
#define TEST_BUFFER_SIZE	16

#define CHAR_ESC		0x1b	/* 'ESC' character is used as terminator */

/**************************** Type Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *******************/

/************************** Function Prototypes ****************************/

int UartPsEchoExample(u32 Uart0BaseAddress, u32 Uart1BaseAddress);
void InitUartModules(u32 Uart0BaseAddress,u32 Uart1BaseAddress);


/************************** Variable Definitions ***************************/

/*
 * The following buffers are used in this example to send and receive data
 * with the UART.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];	/* Buffer for Transmitting Data */


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
	u32 regval = 0;
	XUartPs_Config *CUart0, *CUart1;
	XUartPsFormat FUart0, FUart1;
	XUartPs Uart0, Uart1;

	/* XUartPs_Format might lead the coder to think that it contains all the right
	 * peripheral configurations. However, I found out that the baud rate is not right as it
	 * states that it is set at 115200 regardlesss of the current peripheral setting	*/
//	CUart0 = XUartPs_LookupConfig(XPAR_PS7_UART_0_DEVICE_ID);
//	CUart1 = XUartPs_LookupConfig(XPAR_PS7_UART_1_DEVICE_ID);
//	XUartPs_CfgInitialize(&Uart0, CUart0, XPAR_PS7_UART_0_BASEADDR);
//	XUartPs_CfgInitialize(&Uart1, CUart1, XPAR_PS7_UART_1_BASEADDR);
//	XUartPs_GetDataFormat(&Uart0, &FUart0);
//	XUartPs_GetDataFormat(&Uart1, &FUart1);
//	XUartPs_SetBaudRate(&Uart0, (u32)4800);

	/* If callbacks with the UART are used, I suggest doing config related stuff using
	 * the direct register r/w Xilinx API functions. UG585 ref manual at p.593 gives the formulaes
	 * to calculate a baud rate from the register values:*/
	regval = XUartPs_ReadReg(XPAR_PS7_UART_0_BASEADDR, XUARTPS_BAUDDIV_OFFSET); // Get the baud sample divider value (BDIV)
	regval = XUartPs_ReadReg(XPAR_PS7_UART_0_BASEADDR, XUARTPS_BAUDGEN_OFFSET);	// Get the ref clk div value (CD)
	/* The baudrate for UART0 can be calculated as follows: UART_REF_CLK/(CD*(BDIV+1)).
	 * Here for example, I got 99999999/(4166*(4+1)) = 4800.77 which matches the value I setup in Vivado */
	regval = XUartPs_ReadReg(XPAR_PS7_UART_1_BASEADDR, XUARTPS_BAUDDIV_OFFSET);
	regval = XUartPs_ReadReg(XPAR_PS7_UART_1_BASEADDR, XUARTPS_BAUDGEN_OFFSET);


//	InitUartModules(XPAR_PS7_UART_0_BASEADDR, XPAR_PS7_UART_1_BASEADDR);
	/*
	 * Run the Uart Echo example , specify the Base Address that is
	 * generated in xparameters.h
	 */
	Status = UartPsEchoExample(XPAR_PS7_UART_0_BASEADDR, XPAR_PS7_UART_1_BASEADDR);
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
	int Index;
	u32 Running;
	u8 RecvChar;
	u32 dly1 = 2000, dly2 = 5000, dummy = 0;

	/*
	 * Initialize the send buffer bytes with a pattern to send and the
	 * the receive buffer bytes to zero
	 */

	Running = TRUE;
	while (Running) {
		 /* Cv7 wind tunnel basic loopback - Wait until there is data */
//		while (!XUartPs_IsReceiveData(Uart0BaseAddress)); // Works for 1 as Rx/Tx test
//
//		RecvChar = XUartPs_ReadReg(Uart0BaseAddress,
//					    XUARTPS_FIFO_OFFSET);
//
//		/* Echo the character back */
//		XUartPs_WriteReg(Uart1BaseAddress,  XUARTPS_FIFO_OFFSET,
//				  RecvChar);

		/* Cv7 emulator */
		for(int i=0; i < dly1; i++){	/* Makeshift 500ms delay */
			for(int j=0; j < dly2; j++){
				dummy ^= 1;
			}
		}

		xil_printf("$IIMWV,225.0,R,018.5,N,A*38\r\n");
		xil_printf("$WIXDR,C,031.5,N,,*38\r\n");
		xil_printf("$PLCJ,5801,5F01,AA,4253,3341\r\n");
		xil_printf("$PLCJEA870,6D98,C500,0056,AC\r\n");

	}

	return XST_SUCCESS;
}

void InitUartModules(u32 Uart0BaseAddress,u32 Uart1BaseAddress)
{
	u32 CntrlRegister0, CntrlRegister1, BaudModeRegister, BaudGeneratorRegister, BaudRDividerRegister;

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
//			( (BaudGeneratorRegister & ~XUARTPS_BAUDGEN_MASK) | 0x00000082U));
//	BaudGeneratorRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_BAUDGEN_OFFSET);
//	BaudRDividerRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_BAUDDIV_OFFSET);
//	XUartPs_WriteReg(UartBaseAddress, XUARTPS_BAUDDIV_OFFSET,
//			( (BaudRDividerRegister & ~XUARTPS_BAUDDIV_MASK) | 0x00000009U));
//	BaudRDividerRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_BAUDDIV_OFFSET);

	/* Enable TX and RX for the device */
	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_CR_OFFSET,
			  ((CntrlRegister0 & ~XUARTPS_CR_EN_DIS_MASK) |
//			   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));
//	   	   	   XUARTPS_CR_RX_EN));
	   	   	   XUARTPS_CR_TX_EN));

	XUartPs_WriteReg(Uart1BaseAddress, XUARTPS_CR_OFFSET,
				  ((CntrlRegister1 & ~XUARTPS_CR_EN_DIS_MASK) |
//				   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));
	   	   	   	   XUARTPS_CR_TX_EN));

}
