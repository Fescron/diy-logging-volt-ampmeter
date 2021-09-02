/***************************************************************************//**
 * @file display.c
 * @brief Display updating functionality for high-precision logging voltage/current meter.
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
 * @todo
 *   **Future improvements:**@n
 *     - Change left/right display selection logic so the two update methods can
 *       work independently and without `finishDisplayUpdates`.
 *     - Check/optimize flow in display updating logic.
 *     - Add page for setting min/max volt/amp (/watt/time?) values for relay opening functionality.
 *     - Add status message display functionality on left display/save icon location,
 *       stops running & gets removed by any (?) key-press.
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


#include "display.h"    /* Include corresponding header file */

#include <stdint.h>     /* (u)intXX_t */
#include "ssd1306.h"	/* Lower-level display functionality */
#include "conversion.h" /* Conversion and settings */
#include "util.h"       /* Utility functionality */
#include "rtc.h"        /* Date and Time functionality */


/* Local definitions */
// None


/* Local variables */
// None


/* Local prototypes */
// None


/**************************************************************************//**
 * @brief
 *   Function to initialize the OLED displays.
 *****************************************************************************/
void initDisplays(void)
{
	/* Initialize LEFT display */
	ssd1306_SelectDisplay(0);
	ssd1306_Init();
	ssd1306_SetContrast(0xFF); /* 90 about equals 255/0xFF of RIGHT display... */
	ssd1306_UpdateScreen();

	/* Initialize RIGHT display */
	ssd1306_SelectDisplay(1);
	ssd1306_Init();
	ssd1306_SetContrast(0xFF);
	ssd1306_UpdateScreen();
}


/**************************************************************************//**
 * @brief
 *   Function to display updated info on the LEFT OLED screen.
 *
 * @details
 *   Only updated and visible items on the OLED screens get redrawn.
 *****************************************************************************/
void updateLeftDisplay(void)
{
	/* Variable for selective screen updating logic */
	uint8_t needsUpdate = 0;

	/* Select LEFT display */
	ssd1306_SelectDisplay(0);


	/* Update POWER value if necessary */
	if (cData.newPow)
	{
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString(cData.pLeft, Font_16x26, White);
		ssd1306_WriteChar('.', Font_16x26, White);
		ssd1306_WriteString(cData.pRight, Font_16x26, White);
		ssd1306_WriteString(" W   ", Font_16x26, White);

		cData.newPow = 0;

		needsUpdate = 1;
	}

	if (settings.leftPage == 0)
	{
		/* Update MAX VOLT value if necessary */
		if (cData.newMaxVolt)
		{
			/* Erase previous pixels above smaller text */
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString("    ", Font_11x18, White);

			/* Draw new text */
			ssd1306_SetCursor(2, 32);
			ssd1306_WriteString("Max: ", Font_7x10, White);
			ssd1306_SetCursor(37, 26);
			ssd1306_WriteString(cData.vMaxLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.vMaxRight, Font_11x18, White);
			ssd1306_WriteString(" V", Font_11x18, White);

			cData.newMaxVolt = 0;

			needsUpdate = 1;
		}

		/* Update MIN VOLT value if necessary */
		if (cData.newMinVolt)
		{
			/* Erase previous pixels above smaller text */
			ssd1306_SetCursor(2, 44);
			ssd1306_WriteString("    ", Font_11x18, White);

			/* Draw new text */
			ssd1306_SetCursor(2, 52);
			ssd1306_WriteString("Min: ", Font_7x10, White);
			ssd1306_SetCursor(37, 44);
			ssd1306_WriteString(cData.vMinLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.vMinRight, Font_11x18, White);
			ssd1306_WriteString(" V", Font_11x18, White);

			cData.newMinVolt = 0;

			needsUpdate = 1;
		}
	}
	else if (settings.leftPage == 1)
	{
		/* Update MAX CURR value if necessary */
		if (cData.newMaxCurr)
		{
			/* Erase previous pixels above smaller text */
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString("    ", Font_11x18, White);

			/* Draw new text */
			ssd1306_SetCursor(2, 32);
			ssd1306_WriteString("Max: ", Font_7x10, White);
			ssd1306_SetCursor(37, 26);
			ssd1306_WriteString(cData.aMaxLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.aMaxRight, Font_11x18, White);
			ssd1306_WriteString(" A", Font_11x18, White);

			cData.newMaxCurr = 0;

			needsUpdate = 1;
		}

		/* Update MIN CURR value if necessary */
		if (cData.newMinCurr)
		{
			/* Erase previous pixels above smaller text */
			ssd1306_SetCursor(2, 44);
			ssd1306_WriteString("    ", Font_11x18, White);

			/* Draw new text */
			ssd1306_SetCursor(2, 52);
			ssd1306_WriteString("Min: ", Font_7x10, White);
			ssd1306_SetCursor(37, 44);
			ssd1306_WriteString(cData.aMinLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.aMinRight, Font_11x18, White);
			ssd1306_WriteString(" A", Font_11x18, White);

			cData.newMinCurr = 0;

			needsUpdate = 1;
		}
	}
	else if (settings.leftPage == 2)
	{
		/* Update Ah value if necessary */
		if (cData.newAh)
		{
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString(cData.ahLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.ahRight, Font_11x18, White);
			ssd1306_WriteString("      ", Font_11x18, White);
			ssd1306_SetCursor(104, 26);
			ssd1306_WriteString("Ah", Font_11x18, White);

			cData.newAh = 0;

			needsUpdate = 1;
		}

		/* Update Wh value if necessary */
		if (cData.newWh)
		{
			ssd1306_SetCursor(2, 44);
			ssd1306_WriteString(cData.whLeft, Font_11x18, White);
			ssd1306_WriteChar('.', Font_11x18, White);
			ssd1306_WriteString(cData.whRight, Font_11x18, White);
			ssd1306_WriteString("      ", Font_11x18, White);
			ssd1306_SetCursor(104, 44);
			ssd1306_WriteString("Wh", Font_11x18, White);

			cData.newWh = 0;

			needsUpdate = 1;
		}
	}


	/* Update display selection lines if necessary */
	if ((settings.selectedDisplay == 0) && settings.newSelDisplay)
	{
		/* Draw display selection-lines */
		ssd1306_Line(2, 63, 129, 63, White);
		ssd1306_Line(129, 53, 129, 63, White);

		needsUpdate = 1;
	}
	else if ((settings.selectedDisplay == 1) && settings.newSelDisplay)
	{
		/* Remove display selection-lines */
		ssd1306_Line(2, 63, 129, 63, Black);
		ssd1306_Line(129, 53, 129, 63, Black);

		needsUpdate = 1;
	}


	/* Write changes to LEFT display if necessary */
	if (needsUpdate)
	{
//		SEGGER_RTT_printf(0, "Left");
		ssd1306_UpdateScreen();
	}
}


/**************************************************************************//**
 * @brief
 *   Function to display updated info on the RIGHT OLED screen.
 *
 * @details
 *   Only updated and visible items on the OLED screens get redrawn.
 *****************************************************************************/
void updateRightDisplay(void)
{
	/* Variable for selective screen updating logic */
	uint8_t needsUpdate = 0;

	/* Select RIGHT display */
	ssd1306_SelectDisplay(1);


	/* Update internal battery voltage value if necessary */
	if (settings.newCharVbat)
	{
		ssd1306_SetCursor(2, 4);
		ssd1306_WriteString(settings.vbatLeft, Font_7x10, White);
		ssd1306_WriteChar('.', Font_7x10, White);
		ssd1306_WriteString(settings.vbatRight, Font_7x10, White);
		ssd1306_WriteString(" Vbat", Font_7x10, White);

		settings.newCharVbat = 0;

		needsUpdate = 1;
	}


	/* Update mode indication field if necessary */
	if (settings.newMode)
	{
		if (settings.mode == 0)
		{
			ssd1306_SetCursor(80, 0);
			ssd1306_WriteString("STOP", Font_11x18, White);
		}
		else if (settings.mode == 1)
		{
			ssd1306_SetCursor(80, 0);
			ssd1306_WriteString("RUN ", Font_11x18, White);
		}

		settings.newMode = 0;

		needsUpdate = 1;
	}


	/* Enter logic if we're on the correct page and a second has passed or the time was manually changed */
	if (((settings.rightPage == 0) && rtc.newCharSec) || settings.dateTimeChanged)
	{
		/* Update day if necessary */
		if (rtc.newCharDay || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString(rtc.charDay, Font_11x18, White);
			rtc.newCharDay = 0;
			ssd1306_WriteString("/", Font_11x18, White);
		}

		/* Update month if necessary */
		if (rtc.newCharMonth || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(35, 26);
			ssd1306_WriteString(rtc.charMonth, Font_11x18, White);
			rtc.newCharMonth = 0;
			ssd1306_WriteString("/", Font_11x18, White);
		}

		/* Update year if necessary */
		if (rtc.newCharYear || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(68, 26);
			ssd1306_WriteString(rtc.charYear, Font_11x18, White);
			rtc.newCharYear = 0;
		}

		/* Update hour if necessary */
		if (rtc.newCharHour || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(2, 44);
			ssd1306_WriteString(" ", Font_11x18, White);
			ssd1306_WriteString(rtc.charHour, Font_11x18, White);
			rtc.newCharHour = 0;
			ssd1306_WriteString(":", Font_11x18, White);
		}

		/* Update minutes if necessary */
		if (rtc.newCharMin || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(46, 44);
			ssd1306_WriteString(rtc.charMin, Font_11x18, White);
			rtc.newCharMin = 0;
			ssd1306_WriteString(":", Font_11x18, White);
		}

		/* Update seconds if necessary */
		if (rtc.newCharSec || settings.dateTimeChanged)
		{
			ssd1306_SetCursor(79, 44);
			ssd1306_WriteString(rtc.charSec, Font_11x18, White);
			rtc.newCharSec = 0;
			ssd1306_WriteString(" ", Font_11x18, White);
		}

		/* Draw editing-line under day-field if necessary */
		if ((settings.changeDateTime == 1) && settings.dateTimeChanged)
		{
			ssd1306_Line(2, 42, 22, 42, White);
			ssd1306_Line(2, 43, 22, 43, White);
		}

		/* Draw editing-line under month-field if necessary */
		if ((settings.changeDateTime == 2) && settings.dateTimeChanged)
		{
			ssd1306_Line(35, 42, 55, 42, White);
			ssd1306_Line(35, 43, 55, 43, White);
		}

		/* Draw editing-line under year-field if necessary */
		if ((settings.changeDateTime == 3) && settings.dateTimeChanged)
		{
			ssd1306_Line(68, 42, 110, 42, White);
			ssd1306_Line(68, 43, 110, 43, White);
		}

		/* Draw editing-line under hour-field if necessary */
		if ((settings.changeDateTime == 4) && settings.dateTimeChanged)
		{
			ssd1306_Line(13, 60, 35, 60, White);
			ssd1306_Line(13, 61, 35, 61, White);
		}

		/* Draw editing-line under minutes-field if necessary */
		if ((settings.changeDateTime == 5) && settings.dateTimeChanged)
		{
			ssd1306_Line(46, 60, 68, 60, White);
			ssd1306_Line(46, 61, 68, 61, White);
		}

		/* Draw editing-line under seconds-field if necessary */
		if ((settings.changeDateTime == 6) && settings.dateTimeChanged)
		{
			ssd1306_Line(79, 60, 101, 60, White);
			ssd1306_Line(79, 61, 101, 61, White);
		}

		/* Reset date/time updating logic if time was manually changed */
		if (settings.dateTimeChanged) settings.dateTimeChanged = 0;

		needsUpdate = 1;
	}
	/* Update measurement-period if necessary */
	else if ((settings.rightPage == 1) && settings.periodChanged)
	{
		ssd1306_SetCursor(2, 26);
		ssd1306_WriteString("  Period  ", Font_11x18, White);

		ssd1306_SetCursor(2, 44);
		ssd1306_WriteString("   ", Font_11x18, White);

		/* Calculate hours-mins-secs from selected period value */
		uint16_t secs = settings.measPeriodS;
		uint16_t mins = secs / 60;
		secs = secs - (60 * mins);
		uint8_t hours = mins / 60;
		mins = mins - (60 * hours);

		/* Write hours to screen if necessary */
		if (hours > 0)
		{
			char charHours[3]; /* Value won't exceed 99 (2 chars + NULL termination = 3) */
			uint32_to_charDec(charHours, hours, 2);
			ssd1306_WriteString(charHours, Font_11x18, White);
			ssd1306_WriteString("h ", Font_11x18, White);
		}

		/* Write minutes to screen if necessary */
		if (mins > 0)
		{
			char charMins[3]; /* Value won't exceed 59 (2 chars + NULL termination = 3) */
			uint32_to_charDec(charMins, mins, 2);
			ssd1306_WriteString(charMins, Font_11x18, White);
			ssd1306_WriteString("m ", Font_11x18, White);
		}

		/* Write seconds to screen if necessary */
		if (secs > 0)
		{
			char charSecs[3]; /* Value won't exceed 59 (2 chars + NULL termination = 3) */
			uint32_to_charDec(charSecs, secs, 2);
			ssd1306_WriteString(charSecs, Font_11x18, White);
			ssd1306_WriteString("s ", Font_11x18, White);
		}

		ssd1306_WriteString("      ", Font_11x18, White);


		/* Draw editing-line under period field if necessary */
		if (settings.changePeriod == 1)
		{
			ssd1306_Line(35, 60, 68, 60, White);
			ssd1306_Line(35, 61, 68, 61, White);
		}

		settings.periodChanged = 0;

		needsUpdate = 1;
	}
	/* Update runtime hour/minute values if necessary */
	else if ((settings.rightPage == 2) && (cData.newRunHours || cData.newRunMins))
	{
		ssd1306_SetCursor(2, 26);
		ssd1306_WriteString(" Runtime  ", Font_11x18, White);
		ssd1306_SetCursor(2, 44);

		ssd1306_WriteString(" ", Font_11x18, White);
		ssd1306_WriteString(cData.charRunHours, Font_11x18, White);
		ssd1306_WriteString(":", Font_11x18, White);
		ssd1306_WriteString(cData.charRunMins, Font_11x18, White);
		ssd1306_WriteString(":", Font_11x18, White);

		cData.newRunHours = 0;
		cData.newRunMins = 0;

		needsUpdate = 1;
	}

	/* Update runtime second value if necessary */
	if ((settings.rightPage == 2) && cData.newRunSecs)
	{
		ssd1306_SetCursor(77, 44);
		ssd1306_WriteString(cData.charRunSecs, Font_11x18, White);
		ssd1306_WriteString(" ", Font_11x18, White);

		cData.newRunSecs = 0;

		needsUpdate = 1;
	}


	/* Update display selection lines if necessary */
	if ((settings.selectedDisplay == 1) && settings.newSelDisplay)
	{
		/* Draw display selection-lines */
		ssd1306_Line(2, 63, 129, 63, White);
		ssd1306_Line(129, 53, 129, 63, White);

		needsUpdate = 1;
	}
	else if ((settings.selectedDisplay == 0) && settings.newSelDisplay)
	{
		/* Remove display selection-lines */
		ssd1306_Line(2, 63, 129, 63, Black);
		ssd1306_Line(129, 53, 129, 63, Black);

		needsUpdate = 1;
	}


	/* Write changes to RIGHT display if necessary */
	if (needsUpdate)
	{
//		SEGGER_RTT_printf(0, "Right");
		ssd1306_UpdateScreen();
	}
}


/**************************************************************************//**
 * @brief
 *   Function to finish the screen-updates.
 *
 * @details
 *   This function partially handles the selected-screen line logic.
 *****************************************************************************/
void finishDisplayUpdates(void)
{
	if (settings.newSelDisplay) settings.newSelDisplay = 0;
}


/**************************************************************************//**
 * @brief
 *   Function to display the SAVE status icon on the RIGHT OLED screen.
 *****************************************************************************/
void displaySaveIcon(void)
{
	/* Select RIGHT display */
	ssd1306_SelectDisplay(1);

	ssd1306_SetCursor(80, 0);
	ssd1306_WriteString("SAVE", Font_11x18, White);

	/* Make sure other display logic replaces the icon again */
	settings.newMode = 1;

	/* Write changes to RIGHT display */
	ssd1306_UpdateScreen();
}
