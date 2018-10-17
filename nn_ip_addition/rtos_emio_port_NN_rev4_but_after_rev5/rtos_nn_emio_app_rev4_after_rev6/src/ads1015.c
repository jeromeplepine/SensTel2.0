/*
 * ads1015.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes:
 *      This is the driver for the ADS1015 ADC breakout board
 *      from Adafruit which is interfaced through I2C. It is used to get torque
 *      and thrust readings from the Futek TRD305 and LLB400 signal amplifiers.
 *
 *      The Zynq's built-in ADCs have not been used because it was more time-
 *      efficient to validate I2C (which can also be used for a real-time clock
 *      and several other common external devices) AND ADC functions rather than
 *      ADCs alone. In this way, a working SensTel prototype could be ready earlier.
 *      Most of it has been ported from Adafruit example code
 *
 *		The configuration steps probably could be moved to a separate function
 *		called only once, at setup, instead of at every read request. This would
 *		considerably speed up the execution since reading the torque is done
 *		potentially very often (depends on the specified acquisition period).
 *
 *      Although it is not currently used as such, the part could be used for
 *      differential reads - which would make sense since the Futek amps we use
 *      have differential outputs.
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "ads1015.h"
#include "xparameters.h"


s16 readADCSingleEnded(XIicPs *inst, u32 ZynqIicAddress, u8 channel){
/*
* \brief       Read an ADC value using the ADS1015 Adafruit breakout.
*
* \param[in]   inst           - Pointer to the i2c peripheral instance needed for driver calls.
* \param[in]   ZynqIicAddress - This is already included in the specified inst if it is init'd
*                               correctly.
* \param[in]   channel        - Specifies which of the four channel the part should set its
*                               multiplexer at.
*
* \return                     - The 12-bit read value
*/
	adsGain_t gain = GAIN_ONE;
	u16 config = 0;
	u8 w_value[2];
	u8 r_value[2];


	/* Set to default values */
	config = ADS1015_REG_CONFIG_CQUE_NONE    | /* Disable the comparator (default val) */
						ADS1015_REG_CONFIG_CLAT_NONLAT  | /* Non-latching (default val) */
						ADS1015_REG_CONFIG_CPOL_ACTVLOW | /* Alert/Rdy active low   (default val) */
						ADS1015_REG_CONFIG_CMODE_TRAD   | /* Traditional comparator (default val) */
						ADS1015_REG_CONFIG_DR_1600SPS   | /* 1600 samples per second (default) */
						ADS1015_REG_CONFIG_MODE_SINGLE; /* Single-shot mode (default) */
	/* Set PGA/Voltage range */
	config |= gain;

	/* Select a single input channel (can also be setup as differential) */
	switch (channel)
	{
		case (0):
		  config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
		  break;
		case (1):
		  config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
		  break;
		case (2):
		  config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
		  break;
		case (3):
		  config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
		  break;
	}

	/* Set 'start single-conversion' bit */
	config |= ADS1015_REG_CONFIG_OS_SINGLE;

	/* Separates the configuration word into 2 bytes */
	w_value[0] = (u8) config & 0x00FF;
	w_value[1] = (u8) ((config & 0xFF00) >> 8);

	/* Send the 2 byte ADC read request */
	I2C_write(inst, XPAR_XIICPS_1_DEVICE_ID, ADS1015_ADDRESS, ADS1015_REG_POINTER_CONFIG, 2, w_value);

	/* Wait for the conversion to be complete */
	/* TODO: This works but needs to be replaced by a proper delay. */
	for(int i = 0; i < 100000; i++){};

	/* Read the conversion results */
	I2C_read(inst, XPAR_XIICPS_1_DEVICE_ID, ADS1015_ADDRESS, ADS1015_REG_POINTER_CONVERT, r_value);

	/* Re-order the read values to obtain the actual 12-bit value */
	return ( (s16) r_value[1] | ( ( (s16) r_value[0] ) << 8) ) >> 4;

}


