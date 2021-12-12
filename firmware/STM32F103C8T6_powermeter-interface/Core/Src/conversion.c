/***************************************************************************//**
 * @file conversion.c
 * @brief Conversion and settings-related methods and structs
 *        for high-precision logging voltage/current meter.
 * @version 1.1
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version.
 *   @li v1.1: Changed default measurement period to 10s.
 *
 * ******************************************************************************
 *
 * @todo
 *   **Future improvements:**@n
 *     - Check/optimize flow in `convertValues`.
 *     - Convert negative float values.
 *     - Add max/min power fields.
 *
 * ******************************************************************************
 *
 * @section License
 *
 *   **Copyright (C) 2021 - Brecht Van Eeckhoudt**
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the **GNU General Public License** as published by
 *   the Free Software Foundation, either **version 3** of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   *A copy of the GNU General Public License can be found in the `LICENSE`
 *   file along with this source code.*
 *
 ******************************************************************************/


#include "conversion.h" /* Include corresponding header file */

#include <stdint.h>		/* (u)intXX_t */
#include "usart.h"		/* U(S)ART functionality */
#include "util.h"		/* Utility functionality */
#include "rtc.h"        /* Date and Time functionality */


/* Local definitions */
// None


/* Local variables */
// None


/* Local prototypes */
// None


/**************************************************************************//**
 * @brief
 *   Function to initialize/reset the values in the data-struct.
 *****************************************************************************/
void initDataStruct(void)
{
	data.voltReceived = 0;
	data.firstVolt = 1;     /* Reset minVolt logic */
	data.voltage = 0.0;
	data.oldVolt = 0.0;
	data.newVolt = 1;       /* Force char conversion and display update */
	data.minVoltage = 0.0;
	data.newMinVolt = 1;    /* Force char conversion and display update */
	data.maxVoltage = 0.0;
	data.newMaxVolt = 1;    /* Force char conversion and display update */

	data.currReceived = 0;
	data.firstCurr = 1;     /* Reset minCurr logic */
	data.current = 0.0;
	data.oldCurr = 0.0;
	data.newCurr = 1;       /* Force char conversion and display update */
	data.minCurrent = 0.0;
	data.newMinCurr = 1;    /* Force char conversion and display update */
	data.maxCurrent = 0.0;
	data.newMaxCurr = 1;    /* Force char conversion and display update */

	data.power = 0.0;
	data.oldPower = 0.0;
	data.newPow = 1;        /* Force char conversion and display update */

	data.ah = 0.0;
	data.newAh = 1;         /* Force char conversion and display update */
	data.wh = 0.0;
	data.newWh = 1;         /* Force char conversion and display update */

	data.runHours = 0;
	data.newRunHours = 1;   /* Force char conversion and display update */
	data.runMins = 0;
	data.newRunMins = 1;    /* Force char conversion and display update */
	data.runSecs = 0;
	data.newRunSecs = 1;    /* Force char conversion and display update */

	settings.forceConv = 0; /* Don't convert all invisible values yet */

//	data.msCounter0 = 0;
//	data.msCounter1 = 0;
//	data.latestMScounter = 0;
}


/**************************************************************************//**
 * @brief
 *   Function to initialize/reset the values in the settings-struct.
 *****************************************************************************/
void initSettingsStruct(void)
{
	settings.selectedDisplay = 0; /* Left display selected */
	settings.leftPage = 0;		  /* Left display starts on page 0 */
	settings.rightPage = 0; 	  /* Right display starts on page 0 */
	settings.newSelDisplay = 1;   /* Draw selection lines */
	settings.mode = 0; 			  /* Starting mode = STOP */
	settings.newMode = 1;		  /* Force display update */

	settings.changeDateTime = 0;  /* We're not changing the date/time yet */
	settings.dateTimeChanged = 1; /* Force display update */
	settings.changePeriod = 0;    /* We're not changing the period yet */
	settings.periodChanged = 1;   /* Force display update */
	settings.remMeasPeriodS = 0;  /* Make sure we directly save the next measurement */
	settings.measPeriodIndex = 4; /* Default index for measurement-period LUT */
	settings.measPeriodS = 10;    /* Default to 10s measurement period */

	settings.vbat = 0.0;          /* Reset battery voltage */
	settings.vbatCounter = 0;     /* Check battery voltage on startup */
	settings.newCharVbat = 1;     /* Force display update */

	settings.secPassed = 0;       /* Reset value for second interrupt signaling */
	settings.headerSaved = 0;     /* UART logger not yet initialized */
	settings.oldTIM3 = 0;         /* Reset value for encoder logic */
	settings.newSec = 1;          /* Force display update */
	settings.loopAsDelay = 0;     /* We're not doing additional loops on startup */
	settings.loggerReady = 0;     /* UART logger not yet started up */
	settings.msWaiting = 0;       /* Reset waiting-time functionality */
	settings.msWaitingStart = 0;  /* Reset waiting-time functionality */
}


/**************************************************************************//**
 * @brief
 *   Function to force a conversion of all values not (yet) displayed on the OLED screens.
 *****************************************************************************/
void forceConversion(void)
{
	settings.forceConv = 1;

	convertValues();

	settings.forceConv = 0;
}


/**************************************************************************//**
 * @brief
 *   Function to convert the measurements to char-arrays.
 *
 * @details
 *   Only updated and visible items on the OLED screens get converted.
 *****************************************************************************/
void convertValues(void)
{
	/* Fields for float splitting */
	uint16_t beforeComma = 0;
	uint16_t afterComma  = 0;

	/* Update battery voltage if necessary */
	if (settings.newVbat == 1)
	{
		splitFloat(settings.vbat, &beforeComma, &afterComma, 2);

		/* Limit values just in case */
		if (beforeComma > 9) beforeComma = 9;
		if (afterComma > 99)  afterComma = 99;

		uint32_to_charDec(settings.vbatLeft, beforeComma, 1);
		uint32_to_charDec(settings.vbatRight, afterComma, 2);

		settings.newVbat = 0;

		/* Indicate that the display needs to be updated */
		settings.newCharVbat = 1;
	}


	/* Update VOLT fields if necessary */
	if (data.newVolt)
	{
		splitFloat(data.voltage, &beforeComma, &afterComma, 3);

		data.newVolt = 0;

		uint32_to_charDec(cData.vLeft, beforeComma, 1);
		uint32_to_charDec(cData.vRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newVolt = 1;
	}

	/* Update MIN VOLT fields if necessary */
	if ((data.newMinVolt && (settings.leftPage == 0)) || settings.forceConv)
	{
		splitFloat(data.minVoltage, &beforeComma, &afterComma, 3);

		data.newMinVolt = 0;

		uint32_to_charDec(cData.vMinLeft, beforeComma, 2);
		uint32_to_charDec(cData.vMinRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newMinVolt = 1;
	}

	/* Update MAX VOLT fields if necessary */
	if ((data.newMaxVolt && (settings.leftPage == 0)) || settings.forceConv)
	{
		splitFloat(data.maxVoltage, &beforeComma, &afterComma, 3);

		data.newMaxVolt = 0;

		uint32_to_charDec(cData.vMaxLeft, beforeComma, 2);
		uint32_to_charDec(cData.vMaxRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newMaxVolt = 1;
	}


	/* Update CURR fields if necessary */
	if (data.newCurr)
	{
		splitFloat(data.current, &beforeComma, &afterComma, 4);

		data.newCurr = 0;

		uint32_to_charDec(cData.aLeft, beforeComma, 1);
		uint32_to_charDec(cData.aRight, afterComma, 4);

		/* Indicate that the display needs to be updated */
		cData.newCurr = 1;
	}

	/* Update MIN CURR fields if necessary */
	if ((data.newMinCurr && (settings.leftPage == 1)) || settings.forceConv)
	{
		splitFloat(data.minCurrent, &beforeComma, &afterComma, 4);

		data.newMinCurr = 0;

		uint32_to_charDec(cData.aMinLeft, beforeComma, 1);
		uint32_to_charDec(cData.aMinRight, afterComma, 4);

		/* Indicate that the display needs to be updated */
		cData.newMinCurr = 1;
	}

	/* Update MAX CURR fields if necessary */
	if ((data.newMaxCurr && (settings.leftPage == 1)) || settings.forceConv)
	{
		splitFloat(data.maxCurrent, &beforeComma, &afterComma, 4);

		data.newMaxCurr = 0;

		uint32_to_charDec(cData.aMaxLeft, beforeComma, 1);
		uint32_to_charDec(cData.aMaxRight, afterComma, 4);

		/* Indicate that the display needs to be updated */
		cData.newMaxCurr = 1;
	}


	/* Update POWER fields if necessary */
	if (data.newPow)
	{
		splitFloat(data.power, &beforeComma, &afterComma, 3);

		data.newPow = 0;

		uint32_to_charDec(cData.pLeft, beforeComma, 1);
		uint32_to_charDec(cData.pRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newPow = 1;
	}

	/* Update Ah fields if necessary */
	if ((data.newAh && (settings.leftPage == 2)) || settings.forceConv)
	{
		splitFloat(data.ah, &beforeComma, &afterComma, 3);

		data.newAh = 0;

		uint32_to_charDec(cData.ahLeft, beforeComma, 2);
		uint32_to_charDec(cData.ahRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newAh = 1;
	}

	/* Update Wh fields if necessary */
	if ((data.newWh && (settings.leftPage == 2)) || settings.forceConv)
	{
		splitFloat(data.wh, &beforeComma, &afterComma, 3);

		data.newWh = 0;

		uint32_to_charDec(cData.whLeft, beforeComma, 2);
		uint32_to_charDec(cData.whRight, afterComma, 3);

		/* Indicate that the display needs to be updated */
		cData.newWh = 1;
	}


	/* Update runtime HOUR field if necessary */
	if (data.newRunHours)
	{
		data.newRunHours = 0;

		uint32_to_charDec(cData.charRunHours, data.runHours, 2);

		/* Indicate that the display needs to be updated */
		cData.newRunHours = 1;
	}

	/* Update runtime MIN field if necessary */
	if (data.newRunMins)
	{
		data.newRunMins = 0;

		uint32_to_charDec(cData.charRunMins, data.runMins, 2);

		/* Indicate that the display needs to be updated */
		cData.newRunMins = 1;
	}

	/* Update runtime SEC field if necessary */
	if (data.newRunSecs)
	{
		data.newRunSecs = 0;

		uint32_to_charDec(cData.charRunSecs, data.runSecs, 2);

		/* Indicate that the display needs to be updated */
		cData.newRunSecs = 1;
	}


	/* Update DAY field if necessary */
	if (((rtc.day0 != rtc.day1) && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 1) && settings.dateTimeChanged))
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charDay, rtc.day0, 2);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charDay, rtc.day1, 2);

		/* Indicate that the display needs to be updated */
		rtc.newCharDay = 1;
	}

	/* Update MONTH field if necessary */
	if (((rtc.month0 != rtc.month1) && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 2) && settings.dateTimeChanged))
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charMonth, rtc.month0, 2);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charMonth, rtc.month1, 2);

		/* Indicate that the display needs to be updated */
		rtc.newCharMonth = 1;
	}

	/* Update YEAR field if necessary */
	if (((rtc.year0 != rtc.year1) && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 3) && settings.dateTimeChanged))
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charYear, rtc.year0, 4);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charYear, rtc.year1, 4);

		/* Indicate that the display needs to be updated */
		rtc.newCharYear = 1;
	}


	/* Update HOUR field if necessary */
	if (((rtc.hour0 != rtc.hour1) && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 4) && settings.dateTimeChanged)  || rtc.firstUpdate)
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charHour, rtc.hour0, 2);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charHour, rtc.hour1, 2);

		/* Indicate that the display needs to be updated */
		rtc.newCharHour = 1;
	}

	/* Update MINUTE field if necessary */
	if (((rtc.min0 != rtc.min1) && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 5) && settings.dateTimeChanged)  || rtc.firstUpdate)
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charMin, rtc.min0, 2);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charMin, rtc.min1, 2);

		/* Indicate that the display needs to be updated */
		rtc.newCharMin = 1;
	}

	/* Update SECOND field if necessary */
	if ((settings.newSec && (settings.changeDateTime == 0)) || ((settings.changeDateTime == 6) && settings.dateTimeChanged)  || rtc.firstUpdate)
	{
		if (rtc.latest == 0) uint32_to_charDec(rtc.charSec, rtc.sec0, 2);
		else if (rtc.latest == 1) uint32_to_charDec(rtc.charSec, rtc.sec1, 2);

		settings.newSec = 0;

		/* Indicate that the display needs to be updated */
		rtc.newCharSec = 1;
	}


	/* Reset hour/min/sec char conversion logic after startup */
	if (rtc.firstUpdate) rtc.firstUpdate = 0;
}


/**************************************************************************//**
 * @brief
 *   Function to increase the value of `secondPassed`.
 *****************************************************************************/
void incSecondPassed(void)
{
	settings.secPassed++;
}


/**************************************************************************//**
 * @brief
 *   Function to decrease the value of `secondPassed`.
 *
 * @return
 *   @li `0` - Could not decrease, value already at zero.
 *   @li `1` - `secondPassed` decreased by one.
 *****************************************************************************/
uint8_t decSecondPassed(void)
{
	if (settings.secPassed > 0)
	{
		settings.secPassed--;
		return (1);
	}

	return (0);
}
