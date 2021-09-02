/***************************************************************************//**
 * @file rtc.h
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


/* Include guards prevent multiple inclusions of the same header */
#ifndef __RTC_H_
#define __RTC_H_


/* Includes necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/* Public definitions */

/** Unix epoch time in Julian calendar (UnixTime = 00:00:00 01.01.1970 => JDN = 2440588) */
#define JULIAN_DATE_BASE 2440588

/** Struct to store the RTC data */
extern struct RTC_dateTime_t
{
	uint8_t firstUpdate; /* 1 = first boot, hour, min, sec need to be converted to chars */
	uint8_t latest; /* Index (0 or 1) of most recent value */

	uint8_t hour0;
	uint8_t hour1;
	char charHour[3];  /* Max 2 char + NULL termination = 3 */
	uint8_t newCharHour; /* 1 = display needs updating */

    uint8_t min0;
    uint8_t min1;
    char charMin[3]; /* Max 2 char + NULL termination = 3 */
    uint8_t newCharMin;

    uint8_t sec0;
    uint8_t sec1;
    char charSec[3]; /* Max 2 char + NULL termination = 3 */
    uint8_t newCharSec;

    uint8_t day0;
    uint8_t day1;
    char charDay[3]; /* Max 2 char + NULL termination = 3 */
    uint8_t newCharDay;

    uint8_t wday;

    uint8_t month0;
    uint8_t month1;
    char charMonth[3]; /* Max 2 char + NULL termination = 3 */
    uint8_t newCharMonth;

    uint16_t year0;
    uint16_t year1;
    char charYear[5]; /* Max 4 char + NULL termination = 5 */
    uint8_t newCharYear;
} rtc;


/* Public prototypes */
void RTC_Init(void);
void readFromRTC(void);
void writeToRTC(void);


#endif /* __RTC_H_ */
