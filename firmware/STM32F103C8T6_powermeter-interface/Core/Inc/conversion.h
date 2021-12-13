/***************************************************************************//**
 * @file conversion.h
 * @brief Conversion and settings-related methods and structs
 *        for high-precision logging voltage/current meter.
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
#ifndef __CONVERSION_H_
#define __CONVERSION_H_


/* Includes necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/* Public definitions */

/** Rounding macro */
#define FLOAT_TO_INT(x) ((x)>=0?(uint32_t)((x)+0.5):(uint32_t)((x)-0.5))

/** Struct to store the gathered measurements */
extern struct Data_t
{
	uint8_t voltReceived;    /* 1 = Voltage value received */
	float voltage;           /* [V] */
	float oldVolt;           /* [V], necessary for optimal char conversion logic */
	uint8_t firstVolt;       /* Necessary for MIN logic */
	uint8_t newVolt;         /* 1 = Value needs to be converted to char array */
	float minVoltage;        /* [V] */
	uint8_t newMinVolt;      /* 1 = Value needs to be converted to char array */
	float maxVoltage;        /* [V] */
	uint8_t newMaxVolt;      /* 1 = Value needs to be converted to char array */

	uint8_t currReceived;    /* 1 = Current value received */
	float current;           /* [A] */
	float oldCurr;           /* [A], necessary for optimal char conversion logic */
	uint8_t firstCurr;       /* Necessary for MIN logic */
	uint8_t newCurr;         /* 1 = Value needs to be converted to char array */
	float minCurrent;        /* [A] */
	uint8_t newMinCurr;      /* 1 = Value needs to be converted to char array */
	float maxCurrent;        /* [A] */
	uint8_t newMaxCurr;      /* 1 = Value needs to be converted to char array */

	float power;             /* [W] */
	float oldPower;          /* [W], necessary for optimal char conversion logic */
	uint8_t newPow;          /* 1 = Value needs to be converted to char array */
	float ah;			     /* [Ah] */
	uint8_t newAh;           /* 1 = Value needs to be converted to char array */
	float wh;			     /* [Wh] */
	uint8_t newWh;           /* 1 = Value needs to be converted to char array */

	uint8_t runHours;        /* [hour] */
	uint8_t newRunHours;     /* 1 = Value needs to be converted to char array */
	uint8_t runMins;         /* [min] */
	uint8_t newRunMins;      /* 1 = Value needs to be converted to char array */
	uint8_t runSecs;         /* [sec] */
	uint8_t newRunSecs;      /* 1 = Value needs to be converted to char array */

	uint32_t msCounter0;     /* 24-bit millisecond tick value (Max "16 777 215" or "0xFFFFFF" ) */
	uint32_t msCounter1;     /* 24-bit millisecond tick value (Max "16 777 215" or "0xFFFFFF" ) */
	uint8_t latestMScounter; /* Index of most recent counter */
} data;

/** Struct to store the converted char-data */
extern struct cData_t
{
	char vLeft  [3];      /* Value won't exceed 50   (2 chars + NULL termination = 3) */
	char vRight [4];      /* Value won't exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newVolt;      /* 1 = Value needs to be updated on the display */
	char vMaxLeft[3];     /* Value won't exceed 50   (2 chars + NULL termination = 3) */
	char vMaxRight[4];    /* Value won't exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newMaxVolt;   /* 1 = Value needs to be updated on the display */
	char vMinLeft[3];     /* Value won't exceed 50   (2 chars + NULL termination = 3) */
	char vMinRight[4];    /* Value won't exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newMinVolt;   /* 1 = Value needs to be updated on the display */

	char aLeft  [2];      /* Value won't exceed 5    (1 char  + NULL termination = 2) */
	char aRight [5];      /* Value won't exceed 9999 (4 chars + NULL termination = 5) */
	uint8_t newCurr;      /* 1 = Value needs to be updated on the display */
	char aMaxLeft[2];     /* Value won't exceed 5    (1 char  + NULL termination = 2) */
	char aMaxRight[5];    /* Value won't exceed 9999 (4 chars + NULL termination = 5) */
	uint8_t newMaxCurr;   /* 1 = Value needs to be updated on the display */
	char aMinLeft[2];     /* Value won't exceed 5    (1 char  + NULL termination = 2) */
	char aMinRight[5];    /* Value won't exceed 9999 (4 chars + NULL termination = 5) */
	uint8_t newMinCurr;   /* 1 = Value needs to be updated on the display */

	char pLeft  [4];      /* Value won't exceed 250  (3 chars + NULL termination = 4) */
	char pRight [4];      /* Value won't exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newPow;       /* 1 = Value needs to be updated on the display */

	char ahLeft [5];      /* Value won't be able to exceed 9999 (4 chars + NULL termination = 5) */
	char ahRight[4];      /* Value won't be able to exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newAh;        /* 1 = Value needs to be updated on the display */
	char whLeft [5];      /* Value won't be able to exceed 9999 (4 chars + NULL termination = 5) */
	char whRight[4];      /* Value won't be able to exceed 999  (3 chars + NULL termination = 4) */
	uint8_t newWh;        /* 1 = Value needs to be updated on the display */

	char charRunHours[3]; /* Value won't exceed 99 (2 chars + NULL termination = 3) */
	uint8_t newRunHours;  /* 1 = Value needs to be updated on the display */
	char charRunMins[3];  /* Value won't exceed 59 (2 chars + NULL termination = 3) */
	uint8_t newRunMins;   /* 1 = Value needs to be updated on the display */
	char charRunSecs[3];  /* Value won't exceed 59 (2 chars + NULL termination = 3) */
	uint8_t newRunSecs;   /* 1 = Value needs to be updated on the display */
} cData;

/** Struct to store data (~settings) that change less frequently */
extern struct Settings_t
{
	/* Volatile because it's modified by an interrupt service routine (@RAM) */
	volatile float vbat;          /* Internal battery voltage */
	volatile uint8_t newVbat;     /* 1 = Value needs to be converted to char array */
	char vbatLeft[2]; 	          /* Max 1 char  + NULL termination = 2 */
	char vbatRight[3];            /* Max 2 chars + NULL termination = 3 */
	uint8_t newCharVbat;          /* 1 = Value needs to be updated on the display */
	uint8_t vbatCounter;          /* Countdown timer between battery voltage measurements */

	uint8_t mode;                 /* 0 = STOP, 1 = RUN */
	uint8_t newMode;              /* 1 = Value needs to be updated on the display */
	uint8_t selectedDisplay;      /* 1 = Left display selected, 2 = Right display selected */
	uint8_t newSelDisplay;        /* 1 = Display selection line needs to be updated */
	uint8_t leftPage;             /* 0 = Vmax/min,  1 = Amax/min, 2 = Ah/Wh */
	uint8_t rightPage;            /* 0 = Date/time, 1 = Period,   2 = Runtime */

	uint8_t  measPeriodIndex;     /* Index of LUT for measurement periods */
	uint16_t remMeasPeriodS;      /* Remaining amount of seconds before the next saved measurement */
	uint16_t measPeriodS;         /* Selected measurement period */
	uint8_t  changePeriod;        /* 1 = Changing period */
	uint8_t  periodChanged;       /* 1 = Value needs to be updated on the display */
	uint8_t  changeDateTime;      /* 1 = Changing day, 2 = Month, 3 = Year, 4 = Hours, 5 = Minutes, 6 = Seconds */
	uint8_t  dateTimeChanged;     /* 1 = Value needs to be updated on the display */

	uint8_t headerSaved;          /* 1 = Log-file header is saved (~UART logger is initialized) */
	uint8_t forceConv;            /* 1 = Convert all values not on screens (yet) to chars */
	uint16_t oldTIM3;             /* Encoder rotation logic */
	volatile uint8_t secPassed;   /* Interrupt signaling of seconds */
	uint8_t newSec;               /* 1 = Value needs to be converted to char array */
	uint8_t loopAsDelay;          /* >1 = we need to pass a certain amount of loops before other logic is triggered */
	volatile uint8_t loggerReady; /* 1 = UART logger has started up (startup message detected) */
	uint16_t msWaiting;           /* Waiting-time functionality */
	uint32_t msWaitingStart;      /* Starting value of the waiting-time-counter */
} settings;


/* Public prototypes */
void initDataStruct(void);
void initSettingsStruct(void);
void forceConversion(void);
void convertValues(void);
void setSecondPassed(uint8_t value);
uint8_t getSecondPassed(void);
void incSecondPassed(void);
uint8_t decSecondPassed(void);


#endif /* __CONVERSION_H_ */
