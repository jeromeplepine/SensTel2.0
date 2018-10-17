/*
 * ann.c
 *
 *  Created on: Jun 25, 2018
 *      Author: Jerome Pare-Lepine
 */


//==============================================================================
// INCLUDES
//==============================================================================
#include "ann.h"
#include "xparameters.h"


//==============================================================================
// FUNCTION DEFINITIONS
//==============================================================================
/*
 * @brief	Updates the ANN with values acquired through the vehicle's sensors.
 * 			Once the data has been written to the core's registers, its Data Ready
 * 			register is written to. The core should then be able to analyze the new
 * 			data.
 */
void ANNWriteValues(u32 Pitch, u32 Wspd, u32 TurbRpm)
{
	NN_mWriteReg(XPAR_NN_1_S0_AXI_BASEADDR, NN_REG_PITCH_OFFSET, Pitch);
	NN_mWriteReg(XPAR_NN_1_S0_AXI_BASEADDR, NN_REG_WINDSPEED_OFFSET, Wspd);
	NN_mWriteReg(XPAR_NN_1_S0_AXI_BASEADDR, NN_REG_TURBINERPM_OFFSET, TurbRpm);

	NN_mWriteReg(XPAR_NN_1_S0_AXI_BASEADDR, NN_REG_DATAREADY_OFFSET, NN_REG_DATAREADY_MASK);
}


/*
 * @brief	Reads the command register of the ANN accelerator IP Core.
 * 			A new command should be available a few PL clock cycles after
 * 			values have been written to the core and its Data Ready register
 * 			has been notified.
 */
eANNCmdVal_t ANNReadCommand( void )
{
	static eANNCmdVal_t cmd = MaintainPitch;

	cmd = NN_mReadReg(XPAR_NN_1_S0_AXI_BASEADDR, NN_REG_COMMAND_OFFSET);

	return cmd;
//	return ( cmd & (NN_REG_COMMAND_PITCHUP | NN_REG_COMMAND_PITCHDOWN) );
}

