/***************************************************************************//**
 * @file rtc.c
 * @brief RTC functionality for high-precision logging voltage/current meter.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version.
 *
 * *****************************************************************************
 *
 * @todo
 *   **Future improvements:**@n
 *     - Init `RTC_dateTime_t` struct somewhere?
 *     - Use `rtc.wday` somewhere?
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
 *   @n
 *
 *   Some methods also use code obtained from examples from STMicroelectronics.
 *
 *   @li https://github.com/STMicroelectronics/STM32CubeF1/tree/master/Projects/STM32F103RB-Nucleo/Examples_LL/RTC/RTC_Calendar
 *
 *   **Copyright (c) 2020 STMicroelectronics. All rights reserved.**
 *
 *   These sections are licensed by ST under BSD 3-Clause license, the "License";
 *   One may not use these example files except in compliance with the License.
 *   One may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 *
 *   @n
 *
 *   Some methods also use code obtained from https://github.com/mkdxdx/stm32f103_logger
 *
 *   @n
 *
 *   These seem to be heavily based on https://github.com/LonelyWolf/stm32/blob/master/stm32l-dosfs/RTC.c
 *
 ******************************************************************************/


#include "rtc.h"                 /* Include corresponding header file */

#include <stdint.h>              /* (u)intXX_t */
#include "stm32f1xx_ll_bus.h"    /* Low-Level Clock Management */
#include "stm32f1xx_ll_rcc.h"    /* Low-Level Clock Management */
#include "stm32f1xx_ll_pwr.h"    /* Low-Level Power Management */
#include "stm32f1xx_ll_rtc.h"    /* Low-Level Real Time Clock Peripheral API */
#include "stm32f1xx_ll_exti.h"   /* Low-level interrupt functionality */
#include "stm32f1xx_ll_cortex.h" /* For LL_SYSTICK_IsActiveCounterFlag() */
#include "util.h"		         /* Utility functionality */


/* Local definitions */

/** Oscillator time-out values */
#define RTC_TIMEOUT_MS    ((uint32_t)1000)

/** ck_apre = LSEFreq / (ASYNC prediv + 1) = 1Hz with LSEFreq = 32768Hz */
#define RTC_ASYNCH_PREDIV ((uint32_t)0x7FFF)


/* Local variables */
/** Variable used for Timeout management */
static uint32_t Timeout = 0;


/* Local prototypes */
static void RTCcounter_to_dateTime(uint32_t counter);
static uint32_t dateTime_to_RTCcounter(void);


/**************************************************************************//**
 * @brief
 *   Function to initialize the Real Time Clock.
 *****************************************************************************/
void RTC_Init(void)
{
	/* Enable the PWR Clock and access to the backup domain */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_BKP);
	LL_PWR_EnableBkUpAccess();

	/* Enable LSE only if disabled.*/
	if (LL_RCC_LSE_IsReady() != 1)
	{
		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
		LL_RCC_LSE_Enable();

		Timeout = LSE_TIMEOUT_VALUE;

		while (LL_RCC_LSE_IsReady() != 1)
		{
			if (LL_SYSTICK_IsActiveCounterFlag()) Timeout --;

			if (Timeout == 0) while(1); /* LSE activation error */
		}
	}

	/* Set LSE as the clock source for the RTC if not already the case */
	if (LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
	{
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
	}

	/* Enable RTC peripheral Clock */
	LL_RCC_EnableRTC();


	/* Disable RTC registers write protection */
	LL_RTC_DisableWriteProtection(RTC);

	/* Enter in initialization mode */
	if (LL_RTC_EnterInitMode(RTC) != 0)
	{
		while(1); /* Initialization Error */
	}

	/* Configure RTC prescaler, set Asynch Prediv value according to source clock */
	LL_RTC_SetAsynchPrescaler(RTC, RTC_ASYNCH_PREDIV);

	/* RTC_Alarm Interrupt Configuration: EXTI configuration */
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_17);
	LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_17);

	/* Configure the NVIC for RTC Alarm */
	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);

	/* Enable Second Interrupt */
	LL_RTC_EnableIT_SEC(RTC);

	/* Exit of initialization mode */
	LL_RTC_ExitInitMode(RTC);

	/* Enable RTC registers write protection */
	LL_RTC_EnableWriteProtection(RTC);


	/* Signal logic so the hour/min/second fields have to be converted to chars after RTC initialization (~boot) */
	rtc.firstUpdate = 1;
}


/**************************************************************************//**
 * @brief
 *   Function to convert the RTC counter value to date-time values in the struct.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *
 * @param[in] counter
 *   RTC counter-value (`uint32_t`).
 *****************************************************************************/
static void RTCcounter_to_dateTime(uint32_t counter)
{
	unsigned long time;
	unsigned long t1, a, b, c, d, e, m;
	int year = 0;
	int mon = 0;
	int wday = 0;
	int mday = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;
	uint64_t jd = 0;;
	uint64_t jdn = 0;

	jd = ((counter+43200)/(86400>>1)) + (2440587<<1) + 1;
	jdn = jd>>1;

	time = counter;
	t1 = time/60;
	sec = time - t1*60;

	time = t1;
	t1 = time/60;
	min = time - t1*60;

	time = t1;
	t1 = time/24;
	hour = time - t1*24;

	wday = jdn%7;

	a = jdn + 32044;
	b = (4*a+3)/146097;
	c = a - (146097*b)/4;
	d = (4*c+3)/1461;
	e = c - (1461*d)/4;
	m = (5*e+2)/153;
	mday = e - (153*m+2)/5 + 1;
	mon = m + 3 - 12*(m/10);
	year = 100*b + d - 4800 + (m/10);

	if (rtc.latest == 0)
	{
		rtc.year1 = year;
		rtc.month1 = mon;
		rtc.day1 = mday;
		rtc.hour1 = hour;
		rtc.min1 = min;
		rtc.sec1 = sec;
		rtc.latest = 1;
	}
	else if (rtc.latest == 1)
	{
		rtc.year0 = year;
		rtc.month0 = mon;
		rtc.day0 = mday;
		rtc.hour0 = hour;
		rtc.min0 = min;
		rtc.sec0 = sec;
		rtc.latest = 0;
	}

	rtc.wday = wday;
}


/**************************************************************************//**
 * @brief
 *   Function to convert the date-time values in the struct
 *   to a corresponding RTC counter value.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *
 * @return
 *   The corresponding RTC counter value (`uint32_t`)
 *****************************************************************************/
static uint32_t dateTime_to_RTCcounter(void)
{
	uint8_t a;
	uint16_t y;
	uint8_t m;
	uint32_t JDN;

	if (rtc.latest == 0)
	{
		a=(14-rtc.month0)/12;
		y=rtc.year0+4800-a;
		m=rtc.month0+(12*a)-3;

		JDN=rtc.day0;
		JDN+=(153*m+2)/5;
		JDN+=365*y;
		JDN+=y/4;
		JDN+=-y/100;
		JDN+=y/400;
		JDN = JDN -32045;
		JDN = JDN - JULIAN_DATE_BASE;
		JDN*=86400;
		JDN+=(rtc.hour0*3600);
		JDN+=(rtc.min0*60);
		JDN+=(rtc.sec0);
	}
	else if (rtc.latest == 1)
	{
		a=(14-rtc.month1)/12;
		y=rtc.year1+4800-a;
		m=rtc.month1+(12*a)-3;

		JDN=rtc.day1;
		JDN+=(153*m+2)/5;
		JDN+=365*y;
		JDN+=y/4;
		JDN+=-y/100;
		JDN+=y/400;
		JDN = JDN -32045;
		JDN = JDN - JULIAN_DATE_BASE;
		JDN*=86400;
		JDN+=(rtc.hour1*3600);
		JDN+=(rtc.min1*60);
		JDN+=(rtc.sec1);
	}

	return (JDN);
}


/**************************************************************************//**
 * @brief
 *   Function to update the RTC data in the struct.
 *****************************************************************************/
void readFromRTC(void)
{
	RTCcounter_to_dateTime(LL_RTC_TIME_Get(RTC));
}


/**************************************************************************//**
 * @brief
 *   Function to update the RTC values according to the data in the struct.
 *****************************************************************************/
void writeToRTC(void)
{
	/* Disable RTC registers write protection */
	LL_RTC_DisableWriteProtection(RTC);

	/* Enter in initialization mode */
	if (LL_RTC_EnterInitMode(RTC) != 0)
	{
		while(1); /* Initialization Error */
	}

	/* Set time and date according to struct values, which have been converted to onee uint32_t value */
	LL_RTC_TIME_SetCounter(RTC, dateTime_to_RTCcounter());

	/* Clear RSF flag */
	LL_RTC_ClearFlag_RS(RTC);

    Timeout = RTC_TIMEOUT_MS;

    /* Wait until the RTC Time and Date registers (RTC_TR and RTC_DR) are synchronized with RTC APB clock */
	while(LL_RTC_IsActiveFlag_RS(RTC) != 1)
	{
		if (LL_SYSTICK_IsActiveCounterFlag()) Timeout --;

		if (Timeout == 0) while(1); /* Initialization Error */
	}

	/* Exit of initialization mode */
	if (LL_RTC_ExitInitMode(RTC) != 0)
	{
		while(1); /* Initialization Error */
	}

	/* Enable RTC registers write protection */
	LL_RTC_EnableWriteProtection(RTC);
}
