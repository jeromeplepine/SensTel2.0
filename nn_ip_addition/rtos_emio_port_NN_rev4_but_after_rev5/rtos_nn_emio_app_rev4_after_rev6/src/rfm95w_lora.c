/*
 * rfm95w_lora.c
 *
 *  Created on: Jul 7, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes: WIP
 *      1. The LoRa modules are sourced from Adafruit and can be configured to
 *      operate on both european and north american frequencies. We currently have 2
 *      in stock. Libraries from Airhead are available for Arduino and are
 *      easily ported to C once you understand how to work with SPI. The SPI
 *      and IO hardware needed have already been allocated in Vivado.
 *      2. The modules need at least 1 meter between them to be able to communicate.
 *
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "rfm95w_lora.h"


u32 InitLoRaRadio( XGpioPs* bankPins, XSpiPs* SpiInst )
/*
* \brief       (WIP) Initialize GPIOs and SPI for the LoRa wireless module.
*
* \param[in]   bankPins           - Pointer to the EMIO gpio peripheral instance
* \param[in]   SpiInst            - Pointer to the SPI peripheral instance
*
*/
{
	/* Reset */
	XGpioPs_WritePin(bankPins, LORA_RST_PIN, 0);
	XGpioPs_WritePin(bankPins, LORA_RST_PIN, 1);
	XGpioPs_WritePin(bankPins, LORA_RST_PIN, 0);

	/* Set sleep mode, so we can also set LORA mode: */
	//spiWrite(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_SLEEP | RH_RF95_LONG_RANGE_MODE);


	/* Small delay ot make sure the changes have been made */

	/* Read back the sleep mode and the range mode settings */

	/* Set interrupt pin? */

	/* Set up FIFO
	 * We configure it so that we can use the entire 256 byte FIFO for
	 * either receive or transmit, but not both at the same time
	 */
//    spiWrite(RH_RF95_REG_0E_FIFO_TX_BASE_ADDR, 0);
//    spiWrite(RH_RF95_REG_0F_FIFO_RX_BASE_ADDR, 0);

}
