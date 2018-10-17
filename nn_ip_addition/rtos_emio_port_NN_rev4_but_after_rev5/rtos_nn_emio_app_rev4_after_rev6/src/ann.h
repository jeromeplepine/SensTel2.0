/*
 * ann.h
 *
 *  Created on: Jun 25, 2018
 *      Author: Jerome Pare-Lepine
 */

#ifndef SRC_ANN_H_
#define SRC_ANN_H_

//==============================================================================
// INCLUDES
//==============================================================================
#include "NN.h"	/* Artificial Neural Network Accelerator IP Core by Vincent Cournoyer */
#include "xil_io.h"


//==============================================================================
// DEFINITIONS
//==============================================================================
#define NN_REG_PITCH_OFFSET		NN_S0_AXI_SLV_PITCH_OFFSET	/* R/W - Pitch, u32 */
#define NN_REG_WINDSPEED_OFFSET		NN_S0_AXI_SLV_WINDSPEED_OFFSET /* R/W - Wind speed, u32 */
#define NN_REG_TURBINERPM_OFFSET	NN_S0_AXI_SLV_RPM_OFFSET /* R/W - RPM, u32 */
#define NN_REG_COMMAND_OFFSET		NN_S0_AXI_SLV_COM_OFFSET /* Read Only - Command, u32, 4 LSBs */
#define NN_REG_DATAREADY_OFFSET		NN_S0_AXI_SLV_DATARDY_OFFSET /* Write Only - DataReady, u32, LSB @ high */


/* The core shouldnt produce a situation where
 * two opposite commands happen as they are mutually exclusive.
 * Ex: Bits 4 and 3 shouldn't be high at the same time.	*/
#define	NN_REG_COMMAND_PITCHUP		0x8
#define	NN_REG_COMMAND_PITCHDOWN	0x4
#define	NN_REG_COMMAND_GEARUP		0x2
#define	NN_REG_COMMAND_GEARDOWN		0x1

#define	NN_REG_DATAREADY_MASK	1

//==============================================================================
// VARIABLE DEFINITIONS
//==============================================================================
enum eANNCmdVal{
	MaintainPitch = 0,
	PitchUp = NN_REG_COMMAND_PITCHUP,
	PitchDown = NN_REG_COMMAND_PITCHDOWN

};


//==============================================================================
// TYPE DEFINITIONS
//==============================================================================
typedef enum eANNCmdVal eANNCmdVal_t;


//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================
/*
 * @brief	Updates the ANN with values acquired through the vehicle's sensors.
 * 			Once the data has been written to the core's registers, its Data Ready
 * 			register is written to. The core should then be able to analyze the new
 * 			data.
 */
void ANNWriteValues(u32 Pitch, u32 Wspd, u32 TurbRpm);

/*
 * @brief	Reads the command register of the ANN accelerator IP Core.
 * 			A new command should be available a few PL clock cycles after
 * 			values have been written to the core and its Data Ready register
 * 			has been notified.
 */
eANNCmdVal_t ANNReadCommand( void );


#endif /* SRC_ANN_H_ */
