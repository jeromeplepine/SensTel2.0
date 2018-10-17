/*
 * pwm.c
 *
 *  Created on: Mar 25, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "pwm.h"

/*
 * Convert from an index to the correct timer counter number as defined in
 * xttcps_hw.h
 */
static u32 TimerCounterBaseAddr[] = {
	XPAR_XTTCPS_0_BASEADDR,
	XPAR_XTTCPS_1_BASEADDR
};

static u32 PrescalerSettings[] = {
	2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
	32768, 65536, 1
};

static TmrCntrSetup SettingsTable[] = {
	/* Table offset of 0 */
	{10, 50, 6},
	{10, 25, 6},
	{10, 75, 6},

	/* Table offset of 3 */
	{100, 50, 3},
	{200, 25, 2},
	{400, 12.5, 1},

	/* Table offset of 6 */
	{500, 50, 1},
	{1000, 50, 0},
	{5000, 50, 16},

	/* Table offset of 9 */
	{20000, 50, 16},
	{20000, 50, 16},
	{20000, 50, 16},

	/* Table offset of 12 */
	{500000, 50, 16},
	{1000000, 50, 16},
	{5000000, 50, 16},
	/* Note: at greater than 1 MHz the timer reload is noticeable. */

};

static TmrCntrSetup genSettings = {20000, 100, 16};

#define SETTINGS_TABLE_SIZE  (sizeof(SettingsTable)/sizeof(TmrCntrSetup))

int configTtc(XTtcPs* timerInst, u8 SettingsTableOffset, TmrCntrSetup *CurrSetup){
	u32 LoopCount;
	u32 TmrCtrBaseAddress,
		RegValue,
		IntervalValue,
		MatchValue;

	for (LoopCount = 0; LoopCount < TTC_NUM_DEVICES; LoopCount++) {
			/*
			 * Set the timer counter number to use
			 */
			TmrCtrBaseAddress = TimerCounterBaseAddr[LoopCount];

			/* And get the setup for that counter
			 */
			CurrSetup = &SettingsTable[SettingsTableOffset + LoopCount];
//			CurrSetup = &genSettings;

			/*
			 * Set the Clock Control Register
			 */
			if (16 > CurrSetup->PrescalerValue) {
				/* Use the clock prescaler */
				RegValue =
					(CurrSetup->
					 PrescalerValue <<
					 XTTCPS_CLK_CNTRL_PS_VAL_SHIFT) &
					XTTCPS_CLK_CNTRL_PS_VAL_MASK;
				RegValue |= XTTCPS_CLK_CNTRL_PS_EN_MASK;
			}
			else {
				/* Do not use the clock prescaler */
				RegValue = 0;
			}
			XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_CLK_CNTRL_OFFSET,
					  RegValue);


			/*
			 * Set the Interval register. This determines the frequency of
			 * the waveform. The counter will be reset to 0 each time this
			 * value is reached.
			 */
			IntervalValue = PCLK_FREQ_HZ /
				(u32) (PrescalerSettings[CurrSetup->PrescalerValue] *
				       CurrSetup->OutputHz);

			/*
			 * Make sure the value is not to large or too small
			 */
			if ((65535 < IntervalValue) || (4 > IntervalValue)) {
				return XST_FAILURE;
			}

			XTtcPs_WriteReg(TmrCtrBaseAddress,
					  XTTCPS_INTERVAL_VAL_OFFSET, IntervalValue);

			/*
			 * Set the Match register. This determines the duty cycle of the
			 * waveform. The waveform output will be toggle each time this
			 * value is reached.
			 */
			MatchValue = (IntervalValue * CurrSetup->OutputDutyCycle) / 100;

			/*
			 * Make sure the value is not to large or too small
			 */
			if ((65535 < MatchValue) || (4 > MatchValue)) {
				return XST_FAILURE;
			}
			XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_MATCH_0_OFFSET,
					  MatchValue);

			/*
			 * Set the Counter Control Register
			 */
			RegValue =
				~(XTTCPS_CNT_CNTRL_DIS_MASK |
				  XTTCPS_CNT_CNTRL_EN_WAVE_MASK) &
				(XTTCPS_CNT_CNTRL_INT_MASK |
				 XTTCPS_CNT_CNTRL_MATCH_MASK |
				 XTTCPS_CNT_CNTRL_RST_MASK);
			XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_CNT_CNTRL_OFFSET,
					  RegValue);

			/*
			 * Write to the Interrupt enable register. The status flags are
			 * not active if this is not done.
			 */
			XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_IER_OFFSET,
					  XTTCPS_IXR_INTERVAL_MASK);
	}
	return XST_SUCCESS;
}

u32 normPercent(s32 pwmVal){
	float temp = 0;

	pwmVal = abs(pwmVal);
	temp = (float) ( (abs(pwmVal)*100) / 255)/* * 100*/;
	return (u32) temp;
}

void setPwm(s32 pwValA, s32 pwValB){
	u32 MatchValue = 0,
		Interval;
	u32 pwValues[2];
		pwValues[0] = normPercent(pwValA);
		pwValues[1] = normPercent(pwValB);
	int TmrCtrBaseAddress, LoopCount;
	TmrCntrSetup *CurrSetup;
	for (LoopCount = 0; LoopCount < TTC_NUM_DEVICES; LoopCount++) {
			/*
			 * Set the Match register. This determines the duty cycle of the
			 * waveform. The waveform output will be toggle each time this
			 * value is reached.
			 */
			CurrSetup = &genSettings;

			Interval = PCLK_FREQ_HZ /
							(u32) (PrescalerSettings[CurrSetup->PrescalerValue] * \
								   CurrSetup->OutputHz);

			MatchValue = (Interval * pwValues[LoopCount]) / 100;

			/*
			 * Make sure the value is not to large or too small
			 */
//			if ((65535 < MatchValue) || (4 > MatchValue)) {
//				return;
//			}

			TmrCtrBaseAddress = TimerCounterBaseAddr[LoopCount];

			XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_MATCH_0_OFFSET,
					MatchValue);
	}
}

void testPwm(int* state, int ttcCounter, int tableOffset){
	u32 dutyCycle = 0,
		MatchValue = 0,
		Interval;
	int TmrCtrBaseAddress, LoopCount;
	TmrCntrSetup *CurrSetup;

	switch (*state){
		case(0):
			dutyCycle = 1;
			break;
		case(1):
			dutyCycle = 13;
			break;
		case(2):
			dutyCycle = 25;
			break;
		case(3):
			dutyCycle = 38;
			break;
		case(4):
			dutyCycle = 50;
			break;
		case(5):
			dutyCycle = 63;
			break;
		case(6):
			dutyCycle = 75;
			break;
		case(7):
			dutyCycle = 88;
			break;
		case(8):
			dutyCycle = 100;
			break;
	}
	*state += 1;
	if (*state > 8){
		*state = 0;
	}

	for (LoopCount = 0; LoopCount < TTC_NUM_DEVICES; LoopCount++) {
		/*
		 * Set the Match register. This determines the duty cycle of the
		 * waveform. The waveform output will be toggle each time this
		 * value is reached.
		 */
		CurrSetup = &SettingsTable[tableOffset + LoopCount];

		Interval = PCLK_FREQ_HZ /
						(u32) (PrescalerSettings[CurrSetup->PrescalerValue] * \
							   CurrSetup->OutputHz);

		MatchValue = (Interval * dutyCycle) / 100;

		/*
		 * Make sure the value is not to large or too small
		 */
		if ((65535 < MatchValue) || (4 > MatchValue)) {
	//		return XST_FAILURE;
			return;
		}

		TmrCtrBaseAddress = TimerCounterBaseAddr[LoopCount];

		XTtcPs_WriteReg(TmrCtrBaseAddress, XTTCPS_MATCH_0_OFFSET,
				MatchValue);
	}
}

