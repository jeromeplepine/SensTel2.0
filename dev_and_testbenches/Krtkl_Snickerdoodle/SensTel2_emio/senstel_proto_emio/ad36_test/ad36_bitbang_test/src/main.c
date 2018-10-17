/*
 * main.c
 *
 *  Created on: May 5, 2018
 *      Author: Jerome Pare-Lepine
 */

#include "encoder_ad36.h"

int main()
{
	XGpioPs bankPins;
	int pos = 0;
	initSSIpins(&bankPins);
	while(1)
	{
		pos = readPos(&bankPins);
	}
}

