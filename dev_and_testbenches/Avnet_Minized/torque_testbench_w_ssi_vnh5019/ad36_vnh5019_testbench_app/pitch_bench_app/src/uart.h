/*
 * uart.h
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#define UART0_BASEADDR		XPAR_XUARTPS_0_BASEADDR
#define UART1_BASEADDR		XPAR_XUARTPS_0_BASEADDR
#define UART0_CLOCK_HZ		XPAR_XUARTPS_0_CLOCK_HZ
#define UART1_CLOCK_HZ		XPAR_XUARTPS_0_CLOCK_HZ

#define BUF_LEN			64

#define CHAR_ESC		0x1b	/* 'ESC' character is used as terminator */
#define CARR_RTRN		'\r'
#define NEW_LN			'\n'

#define SUCCESS			0
#define	ERROR			1
#define BUF_OVRFLOW		2

void initUartModule(u32 UartBaseAddress);
u32 sendBuffer(u32 UartBaseAddress, char *Buffer, u32 BufferLength);
void initUartModules(u32 Uart0BaseAddress, u32 Uart1BaseAddress);	// Old, peripheral test function. Phase out when better function(s) in place

#endif /* SRC_UART_H_ */
