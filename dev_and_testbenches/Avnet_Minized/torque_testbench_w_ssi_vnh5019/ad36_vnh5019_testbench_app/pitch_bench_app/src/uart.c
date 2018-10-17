/*
 * uart.c
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "xuartps_hw.h"
#include "xparameters.h"
#include "xstatus.h"
#include "uart.h"

void initUartModule(u32 UartBaseAddress)
{
	u32 CntrlRegister,
		BaudModeRegister;

	CntrlRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_CR_OFFSET);
	BaudModeRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_MR_OFFSET);
	XUartPs_WriteReg(UartBaseAddress, XUARTPS_MR_OFFSET,
	(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE);
	BaudModeRegister = XUartPs_ReadReg(UartBaseAddress, XUARTPS_MR_OFFSET);

	/* Enable TX and RX for the device */
	XUartPs_WriteReg(UartBaseAddress, XUARTPS_CR_OFFSET,
				  ((CntrlRegister & ~XUARTPS_CR_EN_DIS_MASK) |
				   XUARTPS_CR_TX_EN));
}

u32 sendBuffer(u32 UartBaseAddress, char *Buffer, u32 BufferLength)
{
	if(BufferLength > BUF_LEN) return BUF_OVRFLOW;

	for(int i=0; i <= BufferLength+1; i++)
	{
		if(Buffer[i] == '\000') break;
		XUartPs_WriteReg(UART1_BASEADDR,  XUARTPS_FIFO_OFFSET, Buffer[i]);
	}

	return SUCCESS;
}

void initUartModules(u32 Uart0BaseAddress,u32 Uart1BaseAddress)
{
	u32 CntrlRegister0,
		CntrlRegister1,
		BaudModeRegister,
		BaudGeneratorRegister,
		BaudRDividerRegister;

//	// UART 0 init: 8bits, no parity, 1 stop bit, div/8 uart ref clk sel.
//	// Set BR in Vivado at 4800. This is for the CV7 Rx
//	CntrlRegister0 = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_CR_OFFSET);
//	BaudModeRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_MR_OFFSET);
//	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_MR_OFFSET,
//	(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE);
//	// Correct settings validation for UART 0
//	BaudModeRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_MR_OFFSET);
//	BaudGeneratorRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_BAUDGEN_OFFSET);
//	BaudRDividerRegister = XUartPs_ReadReg(Uart0BaseAddress, XUARTPS_BAUDDIV_OFFSET);

	// UART 1 init: 8bits, no parity, 1 stop bit, div/8 uart ref clk sel.
	// Set BR in Vivado at 9600. This is for the terminal data dump.
	CntrlRegister1 = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_CR_OFFSET);
	BaudModeRegister = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_MR_OFFSET);
	XUartPs_WriteReg(Uart1BaseAddress, XUARTPS_MR_OFFSET,
	(BaudModeRegister & ~XUARTPS_MR_PARITY_MASK) | XUARTPS_MR_PARITY_NONE);
	BaudModeRegister = XUartPs_ReadReg(Uart1BaseAddress, XUARTPS_MR_OFFSET);

	/* Enable TX and RX for the device */
	XUartPs_WriteReg(Uart0BaseAddress, XUARTPS_CR_OFFSET,
			  ((CntrlRegister0 & ~XUARTPS_CR_EN_DIS_MASK) |
	   	   	   XUARTPS_CR_RX_EN));

	XUartPs_WriteReg(Uart1BaseAddress, XUARTPS_CR_OFFSET,
				  ((CntrlRegister1 & ~XUARTPS_CR_EN_DIS_MASK) |
	   	   	   	   XUARTPS_CR_TX_EN));

}



