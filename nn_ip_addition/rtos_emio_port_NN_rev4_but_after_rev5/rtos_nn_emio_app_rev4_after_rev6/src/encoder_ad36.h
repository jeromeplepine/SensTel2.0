/*
 * encoder_ad36.h
 *
 *  Created on: Mar 24, 2018
 *      Author: Jerome Pare-Lepine
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "xparameters.h"
#include "xgpiops.h"
#include <stdio.h>

#ifndef SRC_ENCODER_AD36_H_
#define SRC_ENCODER_AD36_H_


//==============================================================================
// DEFINITIONS
//==============================================================================
/* Numbers [54:...] are the numbers used to specify which EMIO pin
 * the developer wishes to use. Pins [0:53] are used to designate
 * the MIO pins.*/
#define SSI_BB_GEAR_CLK		54
#define SSI_BB_GEAR_DAT		55
#define SSI_BB_PITCH_CLK	56
#define SSI_BB_PITCH_DAT	57

/* The value used in a for loop to create a delay
 * allowing the interface circuitry to stabilize between reads */
#define	READ_DLY			110

#define PITCH_ENC_RESO_12		4096.0	// For a 12-bits absolute encoder
#define PITCH_ENC_RESO_22		4194303.0 //3577992 fixed zero	// For a 12-bits absolute encoder
#define ROTOR_GBOX2BLADES_RATIO		1.5
#define ENC_DEGS_PER_BIT_12		(360.0 / PITCH_ENC_RESO_12)
#define ENC_DEGS_PER_BIT_22		(360.0 / PITCH_ENC_RESO_22)

/* Gear range definitions */
#define GEARS_RANGE	42
/* Difference between safe gear ranges. Characterized on an actual workbench,
 * Ernesto has the data. */
#define UPR1_2LWR	259
#define UPR2_3LWR	277
#define UPR3_4LWR	266
#define UPR4_5LWR	264
#define UPR5_6LWR	273
#define UPR6_7LWR	264
#define UPR7_8LWR	255
#define UPR8_9LWR	289
#define UPR9_10LWR	276
#define UPR10_11LWR	266
#define UPR11_12LWR	262
#define UPR12_13LWR	267
#define UPR13_14LWR	260

typedef enum eEncResolution eEncResolution_t;

enum eEncResolution{
	TwelveBits = 0,
	TwentyTwoBits
};

//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================
u32 initSSIpins(XGpioPs* bankPins);
u32 readPos(XGpioPs* bankPins, eEncResolution_t res);



#endif /* SRC_ENCODER_AD36_H_ */
