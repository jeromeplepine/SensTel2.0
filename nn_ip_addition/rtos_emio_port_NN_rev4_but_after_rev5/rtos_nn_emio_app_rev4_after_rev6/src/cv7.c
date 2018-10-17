/*
 * cv7.c
 *
 *  Created on: Jun 5, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes: Parses the useful data from a NMEA character stream. The following
 *      application software interacts with two buffers. It sources the raw data
 *      from a ring buffer filled by a UART task and stores the parsed data in
 *      a fifo buffer.
 *
 *      The Cv7-OEM ultrasonic weather station incorporates a wind vane
 *      and an anemometer. The sensor data is formatted in a NMEA stream, which
 *      is interfaced to SensTel via UART. The stream outputs four "sentences"
 *      every 512ms (if I remember well). Only the wind direction and wind
 *      speeds are currently parsed - the sensor also outputs wind temperature
 *      but the following code ignores it.
 *
 *      Improvements could be made such as configuring the sensor to output the
 *      speed in meters per seconds instead of in knots. Other settings could
 *      also be changed but communicating with the sensor would require additional
 *      hardware.
 *
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "cv7.h"
#include "fifo.h"
#include "ringbuffer.h"
#include "uart.h"
#include <stdio.h>


//==============================================================================
// GLOBAL VARIABLES
//==============================================================================
static char pcNmeaBuf[NMEA_BUF_SZ]; /* Actual buffer used for storage */
static sFifo_t *sNmeaFifo; /* Fifo buffer data struct instance */

//==============================================================================
// FUNCTION DEFINITIONS
//==============================================================================
void vInitNmeaCharBuffer(void)
/*
* \brief       Initializes the FIFO buffer the NMEA data parser uses to store payload
*              strings before processing them.
*/
{
	fifo_init(sNmeaFifo, (void *)pcNmeaBuf, NMEA_BUF_SZ);
}

u32 ulProcessCv7CharBuf(u32 baseaddr, float *wdir, float *wspd, buffer_t *pbuffer)
/*
* \brief       Parses the NMEA character stream received from the wind sensor via UART.
*
* \param[in]   baseaddr     - Base address of the UART peripheral used to interface the Cv7
* \param[in]   wdir, wspd   - Pointers to the variables in which the parser will store the
*                             actual float values extracted from the NMEA strings. These are only
*                             updated if the parser found any useful data in the attached buffer.
* \param[in]   pbuffer      - Pointer of the ringbuffer the xUartBufferTask() uses to push the
*                             received bytes into and from which the hereby parser sources its
*                             raw data.
*
*/
{
	u8 RecvChar, c1;
	static char str_end[3] = "\r\n";
	static eNmeaSeq_t NmeaStatusFlag = 0;
	static u32 CrRegVal = 0;

	/* Pop characters one at a time from the ringbuffer while keeping track
	 * of whether a meaningful character is detected or not, and if so, keep
	 * track of where in the meaningful char sequence we're currently at. */
	while(!isempty(pbuffer)){
		RecvChar = popqueue(pbuffer);

		/* Attempt to lock onto the "$IIMWV," char sequence, which precedes
		 * the only part of the stream we need. Discard the rest. */
		if(NmeaStatusFlag != NmeaComma){
			if( (RecvChar == '$') && (NmeaStatusFlag == NmeaNone) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == 'I') && (NmeaStatusFlag == NmeaDollr) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == 'I') && (NmeaStatusFlag == NmeaI1) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == 'M') && (NmeaStatusFlag == NmeaI2) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == 'W') && (NmeaStatusFlag == NmeaM) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == 'V') && (NmeaStatusFlag == NmeaW) ){
				NmeaStatusFlag++;
			}
			else if( (RecvChar == ',') && (NmeaStatusFlag == NmeaV) ){
				NmeaStatusFlag++;
			}
		}

		else if(NmeaStatusFlag == NmeaComma){
			/* Either fill up the payload fifo or extract the actual sensor data from it */
			if(RecvChar == '*'){
				NmeaStatusFlag = 0;

				/* Terminate the character sequence so that string methods can be
				 * used on the payload string */
				fifo_write(sNmeaFifo, (void *)str_end, 2);

				/* At this point, we're sure to have the important part of the Cv7's NMEA
				 * stream, with a character we won't use in the middle. We can extract the float
				 * values using a string methods.*/
				sscanf(pcNmeaBuf, "%f,%c,%f%*s", wdir, &c1, wspd);
				fifo_reset(sNmeaFifo);

				/* Reset the UART receiver so that the raw data acquisition may continue */
				CrRegVal = XUartPs_ReadReg(baseaddr, XUARTPS_CR_OFFSET);
				XUartPs_WriteReg(baseaddr, XUARTPS_CR_OFFSET, (CrRegVal | XUARTPS_CR_RXRST | 0x20) );
				return XST_SUCCESS;
			}
			else if(RecvChar != '\0'){ /* Retain any non-null character */
				fifo_write(sNmeaFifo, (void *)&RecvChar, 1);
			}
		}
	}

	return XST_FAILURE;
}
