/*
 * senstel_acq.c
 *
 *  Created on: May 30, 2018
 *      Author: Jerome Pare-Lepine
 *      Notes:
 *      Sensors have a specific array storage assigned to them and they
 *      are identified using profile structures. Data conversion and avg'ing
 *      for the different destinations is done with the help of these profiles.
 *      Decoupling the buffers allow more flexible data acquisition and
 *      conversion for managing different destinations.
 *      Ex: The steering wheel might need a float value while we want to log
 *      only the raw data. We might also want a higher sampling rate for logging
 *      the torque while we don't need to have a very detailed value to issue
 *      on CAN.
 *      All of the software that takes care of this is hosted on this file.
 *
 *      Conversion formulas are also located in this file.
 *
 *      WIPs:
 *      - The gear system's absolute position to gear number has yet to be debug-
 *        ged;
 *      - Pitch position calibration (or zero'ing) is not yet functional - the
 *        logic behind the steering wheel calibration selection is working and
 *        the wind direction zero calibration also is. The issue might
 *        instead come from the pitch encoder's absolution position to angle
 *        conversion logic - the values shown on the steering do not make sense.
 *
 */

//==============================================================================
// INCLUDES
//==============================================================================
#include "senstel_acq_config.h"
#include <stdio.h>


//==============================================================================
// PRIVATE TYPE DEFINITIONS
//==============================================================================
/* One buffer per destination is allocated to every sensor. Such a structure
 * is then allocated.*/
typedef sSensorDataBuffer_t aSensorDataBuffers_t[COMM_DEST_TOTAL];

/* Assign the different pre-compiled sensor profiles to actual variables */
sSensorData_t WindSpeedProf = CV7_WSPD_PROFILE,
				WindDirProf = CV7_WDIR_PROFILE,
				PitchAngleProf = PITCH_ABSENC_PROFILE,
				GearAngleProf = GEAR_ABSENC_PROFILE,
				TurbineRPMProf = TURB_INCENC_PROFILE,
				WheelSpeedProf = AXLE_INCENC_PROFILE,
				TurbinePowerProf = TURB_TORQUE_PROFILE,
				TurbineThrustProf = THRUST_LOAD_PROFILE;

/* Array for the sensor lookup table. */
static sSensorData_t SensProfTable[SENSOR_TOTAL];


//==============================================================================
// PRIVATE FUNCTION PROTOTYPES
//==============================================================================
float fKnotsToMperSec(float f);
float ICIntervalToTurbineSpeed(u32 ul);
float ICIntervalToWheelSpeed(u32 ul);
float AbsEnc12ToPitchFloatAngle(u32 ul);
u8 AbsEnc12ToGear(u32 ul);
float AbsEnc22ToPitchFloatAngle(u32 ul);
float VToTorque( u32 ul );
float VToThrust( u32 ul );
u32	fToul(float f, u32 decimals);


//==============================================================================
// PRIVATE VARIABLES
//==============================================================================
/* Data buffer declarations */
static aSensorDataBuffers_t WindSpeedBuffers,
							WindDirBuffers,
							PitchAngleBuffers,
							GearAngleBuffers,
							TurbineRPMBuffers,
							WheelSpeedBuffers,
							TurbinePowerBuffers,
							TurbineThrustBuffers;

/* Data buffers' pointers are stored into another array. Note
 * the order */
static aSensorDataBuffers_t *BufferArray[SENSOR_TOTAL] = {
							&WindSpeedBuffers,
							&WindDirBuffers,
							&PitchAngleBuffers,
							&GearAngleBuffers,
							&TurbineRPMBuffers,
							&WheelSpeedBuffers,
							&TurbinePowerBuffers,
							&TurbineThrustBuffers
};

/*
 * WIP: Variables for the gear's encoder position-to-speed-number conversion. "minX"
 * and "maxX" are the lower and upper gear range positions, in terms of raw sensor
 * position. "nextX" is the difference between the upper position of gear "n"
 * and the lower position of gear "n+1".
 */
static u32 min1, max1, min2, max2, min3, max3, min4, max4, min5, max5, min6, max6,
			min7, max7, min8, max8, min9, max9, min10, max10, min11, max11, min12,
			max12, min13, max13, min14, max14;
static u32 next1, next2, next3, next4, next5, next6, next7, next8, next9, next10, next11,
			next12, next13;


//==============================================================================
// FUNCTION DEFINITIONS
//==============================================================================
void InitSensorProfilesArray( void )
/*
* \brief       Populate the sensor profiles' lookup table.
*
*              Notice that the order of the sensors in the table matches that
*              of the sensor data buffer pointer array, BufferArray[].
*              Notice also that the array indexes are accessed using enum
*              values that were created to match the aforementioned order.
*              Enforcing this logic is important.
*
*/
{
	SensProfTable[Cv7_Wspd] = WindSpeedProf;
	SensProfTable[Cv7_Wdir] = WindDirProf;
	SensProfTable[PitchAbsEnc] = PitchAngleProf;
	SensProfTable[GearAbsEnc] = GearAngleProf;
	SensProfTable[TurbineIncEnc] = TurbineRPMProf;
	SensProfTable[AxleIncEnc] = WheelSpeedProf;
	SensProfTable[TurbineTorque] = TurbinePowerProf;
	SensProfTable[LoadCell] = TurbineThrustProf;
}

void UpdateSensorBiasInArray( eSensor_t Sen, u32 Val )
/*
* \brief       Register a new bias, or zero value, into a sensor profile.
*              This value is taken into account upon sensor data conversion.
*
* \param[in]   Sen         - Enum value of the sensor for which the zero is to
*                            be registered.
*
* \param[in]   Val         - Bias value to be registered
*/
{
	SensProfTable[Sen].CalBias = Val;
}

void InitSensorBuffersTable( void )
/*
* \brief       Initialize every destination data buffers for
*              every sensors
*/
{
	eSensor_t Sens;
	eDestinationType_t Dest;
	aSensorDataBuffers_t *pBufs;
	for(Sens = Cv7_Wspd; Sens < SENSOR_TOTAL; Sens++)
	{
		pBufs = BufferArray[Sens];
		for(Dest = CanType; Dest < COMM_DEST_TOTAL; Dest++)
		{
			static sSensorDataBuffer_t destBuf = {0};
			(*pBufs)[Dest] = destBuf;
		}
	}
}

u8 GetSensorTransmitData(eXmitCmd_t Cmd, eSensor_t Sensor, sXmitData2Dest_t *Data)
/*
* \brief      Fetches a sensor's data for a specific destination from the array
*             of buffer pointers array.
*
* \param[in]   Cmd         - Identifies the destinator(s) of the data request(s).
*
* \param[in]   Sensor      - The sensor for which transmission data is requested.
*
* \param[in]   Data        - Pointer to the sensor data container struct array. These
*                            containers are also populated with information useful all
*                            along the subsequent data path.
*
* \return      The total amount of data that was fetched - which should match the
*              amount of new data in the array passed as argument.
*
*/
{
	static u8 NumReq = 0;
	aSensorDataBuffers_t *sensorxmitbufs = BufferArray[Sensor];
	static sSensorData_t sSens;

	NumReq = 0;	/* Reset the request counter. */
	sSens.CanData = 0;
	sSens.ComputeAvg = 0;
	sSens.Data = 0;
	sSens.Profile = 0;
	sSens.Sensor = 0;
	sSens.Sid = 0;

	UpdateTaskHighWaterMark(&oTHWM, NULL);    /* For stack size evaluation (debug) purposes */
	/* Before attempting to extract data from a sensor's buffer, validate that the
	 * requested sensor actually exists in the table */
	if (GetSensorProfile(Sensor, &sSens)){
		if(Cmd & CanXmit){
			Data[NumReq].eDataType = CanType;
			Data[NumReq].sSensProfile = &sSens;
			Data[NumReq].sSensProfile->Data = (*sensorxmitbufs)[CanType].ulBuffer;
			/* The buffer's data is now outdated and can be cleared.
			 * New sensor data will be accumulated. */
			(*sensorxmitbufs)[CanType].usBufferFlags |= SENSDAT_BUF_CLR;
			NumReq++;
		}
		if(Cmd & SdWrite){
			(Data[NumReq]).eDataType = SdType;
			Data[NumReq].sSensProfile = &sSens;
			(Data[NumReq]).sSensProfile->Data = (*sensorxmitbufs)[SdType].ulBuffer;
			(*sensorxmitbufs)[SdType].usBufferFlags |= SENSDAT_BUF_CLR;
			NumReq++;
		}
		if(Cmd & NNUpdate){
			(Data[NumReq]).eDataType = NNType;
			Data[NumReq].sSensProfile = &sSens;
			(Data[NumReq]).sSensProfile->Data = (*sensorxmitbufs)[NNType].ulBuffer;
			(*sensorxmitbufs)[NNType].usBufferFlags |= SENSDAT_BUF_CLR;
			NumReq++;
		}
		if(Cmd & LoRaXmit){
			(Data[NumReq]).eDataType = LoRaType;
			Data[NumReq].sSensProfile = &sSens;
			(Data[NumReq]).sSensProfile->Data = (*sensorxmitbufs)[LoRaType].ulBuffer;
			(*sensorxmitbufs)[LoRaType].usBufferFlags |= SENSDAT_BUF_CLR;
			NumReq++;
		}
		if(Cmd & SerialXmit){
			(Data[NumReq]).eDataType = SerialType;
			Data[NumReq].sSensProfile = &sSens;
			(Data[NumReq]).sSensProfile->Data = (*sensorxmitbufs)[SerialType].ulBuffer;
			(*sensorxmitbufs)[SerialType].usBufferFlags |= SENSDAT_BUF_CLR;
			NumReq++;
		}
		UpdateTaskHighWaterMark(&oTHWM, NULL);

		return NumReq;
	}

	else return 0;
}

void UpdateSensorBuffers(sSensorData_t *NewData)
/*
* \brief       Inject a new value in the raw data array and update the buffer's
*              status
*
* \param[in]   NewData       - Pointer to the structure containing the new data
*                              and other necessary information
*
*/
{
	static eDestinationType_t type;
	aSensorDataBuffers_t *sensorxmitbufs = BufferArray[NewData->Sensor];

#ifdef DEBUG_DATA_PATH_PRINTS
			xil_printf("USB: Sensor->%d, data->%d\n", NewData->Sensor, NewData->Data);
#endif

	for(type = CanType; type < COMM_DEST_TOTAL; type++){
		u32 tmp = (*sensorxmitbufs)[type].usBufferFlags & SENSDAT_BUF_CLR; /* For debug purposes */
		tmp = !(NewData->ComputeAvg);
		tmp = (*sensorxmitbufs)[type].usDataCntr == 0;

		/*
		 * If it tests true, we assume either:
		 * - the buffer's data has already been sent through the data path
		 * and should be cleared and/or
		 * - the profile of the originating sensor is set to non-averaging mode and/or
		 * - the buffer has just been initialized and is empty
		 */
		if( ( (*sensorxmitbufs)[type].usBufferFlags & SENSDAT_BUF_CLR) |
				!(NewData->ComputeAvg) | ( (*sensorxmitbufs)[type].usDataCntr == 0) )
		{
			(*sensorxmitbufs)[type].ulBuffer = NewData->Data;
			(*sensorxmitbufs)[type].usBufferFlags &= ~(SENSDAT_BUF_CLR);
			(*sensorxmitbufs)[type].usDataCntr = 1;
		}
		else{
			u32 tmp = ( (*sensorxmitbufs)[type].ulBuffer + NewData->Data ) >> 1;
			(*sensorxmitbufs)[type].ulBuffer = tmp;
			if((*sensorxmitbufs)[type].usDataCntr == SENSDAT_BUF_OVRFLW_THRESH)
			{
				(*sensorxmitbufs)[type].usBufferFlags &= SENSDAT_BUF_OVRFLW;
			}
			(*sensorxmitbufs)[type].usDataCntr++;
#ifdef DEBUG_DATA_PATH_PRINTS
			xil_printf("data cnt: %d\n", (*sensorxmitbufs)[type].usDataCntr);
#endif
		}
	}
}

u32 GetSensorProfile(eSensor_t Sens, sSensorData_t *sDat)
/*
* \brief       Fetch a sensor's profile informations.
*
* \param[in]   Sens         - Enum value of the requested sensor
*
* \param[in]   sDat         - The requested data's struct pointer
*
* \return      0 if failure, 1 otherwise.
*/
{
	/* Assert the request's validity */
	if(SensProfTable[Sens].Sensor == Sens)
	{
		sDat->CanData = SensProfTable[Sens].CanData;
		sDat->ComputeAvg = SensProfTable[Sens].ComputeAvg;
		sDat->Data = SensProfTable[Sens].Data;
		sDat->CalBias = SensProfTable[Sens].CalBias;
		sDat->Profile = SensProfTable[Sens].Profile;
		sDat->Sensor = SensProfTable[Sens].Sensor;
		sDat->Sid = SensProfTable[Sens].Sid;
		return 1;
	}
	else{
		return 0;
	}
}

float ConvertSensorData(eSensor_t Sen, void *Input, void *Bias)
/*
* \brief       Applies a bias and converts raw sensor data.
*
* \param[in]   Sen         - Enum value of the sensor for which the value is to be
*                            converted
*
* \param[in]   Input       - Raw value to be converted
*
* \param[in]   Bias        - Pointer to the zero calibration offset
*
* \return      The converted value as a float.
*/
{
	static u32 ultmp, tmp1 = 0;
	static float ftmp, tmp2 = 0;

	if( *(u32 *)Input == 0) return *(float *)Input;
	ultmp = 0, ftmp = 0, tmp1 = 0, tmp2 = 0;
	switch(Sen){
		case Cv7_Wspd:
			ftmp = fKnotsToMperSec( *(float *)Input );
			break;

		case Cv7_Wdir:
#ifdef SETZERO_MODS
			if(*(float *)Input < *(float *)Bias){
				tmp2 = *(float *)Input + WDIR_MAX_VAL - *(float *)Bias;
			}
			else{
				tmp2 = *(float *)Input - *(float *)Bias;
			}
			if( (tmp2 >= 0.0) && (tmp2 < 179.9) ) ftmp = tmp2;
			else if( (tmp2 >= 179.9) && (tmp2 < 360.0) ) ftmp = tmp2 - 360.0;
#else
			ftmp = ( )*(float*)Input - 180.0);
#endif
			break;

		case PitchAbsEnc:
#ifdef SETZERO_MODS
			if(*(u32 *)Input < *(u32 *)Bias){
#ifdef FIXED_PITCH_ZERO
//				tmp1 = *(u32 *)Input + PITCH_ABSENC_MAX_VAL - FIXD_PITCH_ZERO_VAL;
				tmp1 = *(u32 *)Input;
#else
				tmp1 = *(u32 *)Input + PITCH_ABSENC_MAX_VAL - *(u32 *)Bias;
#endif
			}
			else{
#ifdef FIXED_PITCH_ZERO
//				tmp1 = *(u32 *)Input - FIXD_PITCH_ZERO_VAL;
				tmp1 = *(u32 *)Input;
#else
				tmp1 = *(u32 *)Input - *(u32 *)Bias;
#endif
			}
			ftmp = AbsEnc12ToPitchFloatAngle( tmp1 );
#else
			ftmp = AbsEnc22ToPitchFloatAngle( *(u32 *)Input - *(u32 *)Bias );
#endif
			break;

		case GearAbsEnc:
#ifdef DEBUG_GEAR_ENC_PRINTS
            xil_printf("Gear enc.val.= %d\n", *(u32 *)Input);
#endif
#ifdef SETZERO_MODS
            if(*(u32 *)Input < *(u32 *)Bias){
				tmp1 = *(u32 *)Input + GEAR_ABSENC_MAX_VAL - *(u32 *)Bias;
			}
			else{
				tmp1 = *(u32 *)Input - *(u32 *)Bias;
			}
			ftmp = AbsEnc12ToGear( tmp1 );
#else
			ftmp = AbsEnc12ToGear(*(u32 *)Input - *(u32 *)Bias);
#endif
			break;

		case TurbineIncEnc:
			ftmp = ICIntervalToTurbineSpeed( *(u32 *)Input );
			break;

		case AxleIncEnc:
			ftmp = ICIntervalToWheelSpeed( *(u32 *)Input );
			break;

		case TurbineTorque:
			ftmp = VToTorque( *(u32 *)Input);
			break;

		case LoadCell:
			ftmp = VToThrust( *(u32 *)Input);
			break;
	}

	return ftmp;
}

u32 ConvertSensorDataForNN(eSensor_t Sen, void *Input, void *Bias)
/*
* \brief       Applies a bias and converts raw sensor data to the NN core's
*              format.
*
* \param[in]   Sen         - Enum value of the sensor for which the value is to be
*                            converted
*
* \param[in]   Input       - Raw value to be converted
*
* \param[in]   Bias        - Pointer to the zero calibration offset
*
* \return      The converted value in unsigned long integer format.
*/
{
	static u32 ultmp = 0, tmp1 = 0;
	static float ftmp = 0, wspddum = 0, tmp2 = 0;

	ultmp = 0, ftmp = 0;

	/* The NN IP core only accepts unsigned long integers */
	switch(Sen)
	{
		case Cv7_Wspd:
#ifdef	WSPD_DUMMY_VALUE
			wspddum = WSPD_DUMMY_VALUE;
			ftmp = fKnotsToMperSec( *( (float *)&wspddum ) );
#else
			if( *(float *)Input == 0) return 0;
			ftmp = fKnotsToMperSec( *(float *)Input );
#endif
			ultmp = fToul( (ftmp + 0.5) , 0);
			break;

		case PitchAbsEnc:
			if( *(u32 *)Input == 0) return 0;
#ifdef SETZERO_MODS
			if(*(u32 *)Input < *(u32 *)Bias){
#ifdef FIXED_PITCH_ZERO
				tmp1 = *(u32 *)Input + PITCH_ABSENC_MAX_VAL - FIXD_PITCH_ZERO_VAL;
#else
				tmp1 = *(u32 *)Input + PITCH_ABSENC_MAX_VAL - *(u32 *)Bias;
#endif
			}
			else{
#ifdef FIXED_PITCH_ZERO
				tmp1 = *(u32 *)Input - FIXD_PITCH_ZERO_VAL;
#else
				tmp1 = *(u32 *)Input - *(u32 *)Bias;
#endif
			}
			ftmp = AbsEnc12ToPitchFloatAngle( tmp1 );
#else
			ftmp = AbsEnc22ToPitchFloatAngle( *(u32 *)Input - *(u32 *)Bias );
#endif
			ultmp = fToul( ( (8 * ftmp) + 0.5), 0);
			break;

		case TurbineIncEnc:
			if( *(u32 *)Input == 0) return 0;
			ftmp = ICIntervalToTurbineSpeed( *(u32 *)Input - *(u32 *)Bias );
			ultmp = fToul( (ftmp + 0.5) , 0);
			break;

		default:
			break;

	} //switch
	return ultmp;

}

void InitAppProfile(sAppTaskProfiles_t *AppProfiles)
/* Could be removed - intended use was to make basic code profiling facilities
 * but couldn't finish it in time.
 */
{
	AppProfiles->idx = 0;
}

u8 AddTaskProfile(sAppTaskProfiles_t *AppProfiles, char *TaskId, u8 charcount)
/* Could be removed - intended use was to make basic code profiling facilities
 * but couldn't finish it in time. Each tasks to profile had to be registered.
 */
{
	sTaskProfile_t *tprof = &AppProfiles->TaskArray[AppProfiles->idx];
	u8 prevTaskIdx = AppProfiles->idx;

	tprof->AvgLooptime = 0;
	tprof->LastDelta = 0;
	tprof->LoopCount = 0;
	tprof->MaxDelta = 0;
	tprof->MinDelta = 0;

	strncpy(tprof->TaskId, TaskId, charcount);

	AppProfiles->idx++;

	return prevTaskIdx;
}


void UpdateTaskProfile(sAppTaskProfiles_t *AppProfiles, u8 TaskIdx, u32 NewTimeDelta)
/*
 * Could be removed - intended use was to make basic code profiling facilities
 * but couldn't finish it in time. This function would have updated the app's
 * profiling data with a time base provided by the core timer.
 */
{
	u32 tmp = 0;
	sTaskProfile_t *tprof = &AppProfiles->TaskArray[TaskIdx];

	if(tprof->LoopCount == 0){
		tprof->AvgLooptime = NewTimeDelta;
		tprof->MinDelta = NewTimeDelta;
		tprof->MaxDelta = NewTimeDelta;
	}
	else{
		tmp = (tprof->AvgLooptime + NewTimeDelta) >> 1;
		tprof->AvgLooptime = tmp;
	}

	if(tprof->LoopCount < 0xFFFFFFFF) tprof->LoopCount++;
	else tprof->LoopCount = 0;

	tprof->LastDelta = NewTimeDelta;

	if(NewTimeDelta > tprof->MaxDelta) tprof->MaxDelta = NewTimeDelta;
	else if( (NewTimeDelta > 0) || (NewTimeDelta < tprof->MinDelta) ) tprof->MinDelta = NewTimeDelta;

}

void UpdateTaskHighWaterMark( u32 *oHWM, TaskHandle_t taskHandle )
/*
* \brief       Refreshes the peak stack useage data.
*/
{
//	*oHWM = uxTaskGetStackHighWaterMark( NULL );
}

inline float fKnotsToMperSec(float f)
{
	float tmpf = (f*33)/64;
	return tmpf;
}

inline u32	fToul(float f, u32 decimals)
/*
* \brief       Converts a float into an unsigned long with a special format.- useful
*              for the NN core. Ex: 105,1 => 1051
*/
{
	float ftmp = f;

	for(u8 i = 0; i < decimals; i++){
		ftmp *= 10;
	}

	return (u32)ftmp;
}

inline float AbsEnc12ToPitchFloatAngle(u32 ul)
{
	return (float)(ul * ENC_DEGS_PER_BIT_12) * ROTOR_GBOX2BLADES_RATIO;
}

void ZeroGearsTable( u32 firstgearlowlimit )
/*
* \brief       Calculates the gear's min and max limits.
*/
{
#ifdef SETZERO_MODS
	min1 = firstgearlowlimit;
	max1 = min1 + GEARS_RANGE;
	if(max1 > GEAR_ABSENC_MAX_VAL) max1 -= GEAR_ABSENC_MAX_VAL;

	min2 = max1 + UPR1_2LWR;
	max2 = min2 + GEARS_RANGE;
	if(max2 > GEAR_ABSENC_MAX_VAL) max2 -= GEAR_ABSENC_MAX_VAL;

	min3 = max2 + UPR2_3LWR;
	max3 = min3 + GEARS_RANGE;
	if(max3 > GEAR_ABSENC_MAX_VAL) max3 -= GEAR_ABSENC_MAX_VAL;

	min4 = max3 + UPR3_4LWR;
	max4 = min4 + GEARS_RANGE;
	if(max4 > GEAR_ABSENC_MAX_VAL) max4 -= GEAR_ABSENC_MAX_VAL;

	min5 = max4 + UPR4_5LWR;
	max5 = min5 + GEARS_RANGE;
	if(max5 > GEAR_ABSENC_MAX_VAL) max5 -= GEAR_ABSENC_MAX_VAL;

	min6 = max5 + UPR5_6LWR;
	max6 = min6 + GEARS_RANGE;
	if(max6 > GEAR_ABSENC_MAX_VAL) max6 -= GEAR_ABSENC_MAX_VAL;

	min7 = max6 + UPR6_7LWR;
	max7 = min7 + GEARS_RANGE;
	if(max7 > GEAR_ABSENC_MAX_VAL) max7 -= GEAR_ABSENC_MAX_VAL;

	min8 = max7 + UPR7_8LWR;
	max8 = min8 + GEARS_RANGE;
	if(max8 > GEAR_ABSENC_MAX_VAL) max8 -= GEAR_ABSENC_MAX_VAL;

	min9 = max8 + UPR8_9LWR;
	max9 = min9 + GEARS_RANGE;
	if(max9 > GEAR_ABSENC_MAX_VAL) max9 -= GEAR_ABSENC_MAX_VAL;

	min10 = max9 + UPR9_10LWR;
	max10 = min10 + GEARS_RANGE;
	if(max10 > GEAR_ABSENC_MAX_VAL) max10 -= GEAR_ABSENC_MAX_VAL;

	min11 = max10 + UPR10_11LWR;
	max11 = min11 + GEARS_RANGE;
	if(max11 > GEAR_ABSENC_MAX_VAL) max11 -= GEAR_ABSENC_MAX_VAL;

	min12 = max11 + UPR11_12LWR;
	max12 = min12 + GEARS_RANGE;
	if(max12 > GEAR_ABSENC_MAX_VAL) max12 -= GEAR_ABSENC_MAX_VAL;

	min13 = max12 + UPR12_13LWR;
	max13 = min13 + GEARS_RANGE;
	if(max13 > GEAR_ABSENC_MAX_VAL) max13 -= GEAR_ABSENC_MAX_VAL;

	min14 = max13 + UPR13_14LWR;
	max14 = min14 + GEARS_RANGE;
	if(max14 > GEAR_ABSENC_MAX_VAL) max14 -= GEAR_ABSENC_MAX_VAL;

#else
	min1 = firstgearlowlimit;
	max1 = min1 + GEARS_RANGE;

	min2 = max1 + UPR1_2LWR;
	max2 = min2 + GEARS_RANGE;

	min3 = max2 + UPR2_3LWR;
	max3 = min3 + GEARS_RANGE;

	min4 = max3 + UPR3_4LWR;
	max4 = min4 + GEARS_RANGE;

	min5 = max4 + UPR4_5LWR;
	max5 = min5 + GEARS_RANGE;

	min6 = max5 + UPR5_6LWR;
	max6 = min6 + GEARS_RANGE;

	min7 = max6 + UPR6_7LWR;
	max7 = min7 + GEARS_RANGE;

	min8 = max7 + UPR7_8LWR;
	max8 = min8 + GEARS_RANGE;

	min9 = max8 + UPR8_9LWR;
	max9 = min9 + GEARS_RANGE;

	min10 = max9 + UPR9_10LWR;
	max10 = min10 + GEARS_RANGE;

	min11 = max10 + UPR10_11LWR;
	max11 = min11 + GEARS_RANGE;

	min12 = max11 + UPR11_12LWR;
	max12 = min12 + GEARS_RANGE;

	min13 = max12 + UPR12_13LWR;
	max13 = min13 + GEARS_RANGE;

	min14 = max13 + UPR13_14LWR;
	max14 = min14 + GEARS_RANGE;
#endif
}

inline u8 AbsEnc12ToGear(u32 ul)
/*
* \brief       WIP: Converts the gear's encoder position into an actual
*              Rolhoff gear number
*/
{
	static u8 start = 1;

	if(start){
		ZeroGearsTable(ul);
		start = 0;
	}

	if ( (ul >= min1) & (ul <= max1) ) return 1;
	else if ( (ul >= min2) & (ul <= max2) ) return 2;
	else if ( (ul >= min3) & (ul <= max3) ) return 3;
	else if ( (ul >= min4) & (ul <= max4) ) return 4;
	else if ( (ul >= min5) & (ul <= max5) ) return 5;
	else if ( (ul >= min6) & (ul <= max6) ) return 6;
	else if ( (ul >= min7) & (ul <= max7) ) return 7;
	else if ( (ul >= min8) & (ul <= max8) ) return 8;
	else if ( (ul >= min9) & (ul <= max9) ) return 9;
	else if ( (ul >= min10) & (ul <= max10) ) return 10;
	else if ( (ul >= min11) & (ul <= max11) ) return 11;
	else if ( (ul >= min12) & (ul <= max12) ) return 12;
	else if ( (ul >= min13) & (ul <= max13) ) return 13;
	else if ( (ul >= min14) & (ul <= max14) ) return 14;
	else return 0;

}

inline float AbsEnc22ToPitchFloatAngle(u32 ul)
{
	return (float)(ul * ENC_DEGS_PER_BIT_22) / ROTOR_GBOX2BLADES_RATIO;
}

inline float ICIntervalToWheelSpeed(u32 ul)
{
	return (float) XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ / (ul * AXLE_FREQ2RPM_CONST);
}

inline float ICIntervalToTurbineSpeed(u32 ul)
{
	return (float) XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ / (ul * TURB_FREQ2RPM_CONST);
}

inline float VToTorque( u32 ul )
{
	return  (float ) ul * VOLTS_TO_TORQUE;
}

inline float VToThrust( u32 ul )
{
	return  (float ) ul * VOLTS_TO_THRUST;
}
