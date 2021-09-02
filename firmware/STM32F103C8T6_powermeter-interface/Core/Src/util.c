/***************************************************************************//**
 * @file util.c
 * @brief Utility functionality for high-precision logging voltage/current meter.
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


#include "util.h"   /* Include corresponding header file */

#include <stdint.h> /* (u)intXX_t */


/* Local definitions */
/* Macro definition that returns a character when given a value */
#define TO_DEC(i) (i <= 9 ? '0' + i : '?') /* return "?" if out of range */


/* Local variables */
// None


/* Local prototypes */
// None


/**************************************************************************//**
 * @brief
 *   Convert four bytes into a float.
 *
 * @param[in] byte0
 *   First byte.
 *
 * @param[in] byte1
 *   Second byte.
 *
 * @param[in] byte2
 *   Third byte.
 *
 * @param[in] byte3
 *   Fourth byte.
 *
 * @return
 *   The converted float-value.
 *****************************************************************************/
float bytes_to_float(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
	/* Define union */
	union
	{
		float fValue;
		uint8_t byte[4];
	} data;

	/* Assign the four bytes to the union array */
	data.byte[0]=byte0;
	data.byte[1]=byte1;
	data.byte[2]=byte2;
	data.byte[3]=byte3;

	return (data.fValue);
}


/**************************************************************************//**
 * @brief
 *   Split a `float` value in two `uint` values (before and after the comma).
 *
 * @param[in] fValue
 *   The float value to convert.
 *
 * @param[in,out] beforeComma
 *   Pointer to the `uint16_t` value before the comma.
 *
 * @param[in,out] afterComma
 *   Pointer to the `uint16_t` value after the comma.
 *
 * @param[in] decimalPlaces
 *   Amount of decimal places to use after the comma.
 *****************************************************************************/
void splitFloat(float fValue, uint16_t *beforeComma, uint16_t *afterComma, uint8_t decimalPlaces)
{
	/* Separate value before comma */
	*beforeComma = (uint16_t)fValue;

	/* Separate value after comma according to given argument */
	float multiplicationFactor = 1.0;
	for (uint8_t counter = 0; counter < decimalPlaces; counter++) multiplicationFactor *= 10.0;
	*afterComma = (uint16_t)((float)(fValue-(*beforeComma))*multiplicationFactor);

	/* Round up if necessary */
	uint8_t roundingNumber = (uint8_t)(((float)(fValue-(*beforeComma))*(multiplicationFactor*10.0))-(*afterComma)*10);
	if (roundingNumber > 4)
	{
		(*afterComma)++;
		if ((decimalPlaces == 1) && (*afterComma) == 10)
		{
			(*beforeComma)++;
			(*afterComma) = 0;
		}
	}
}


/**************************************************************************//**
 * @brief
 *   Convert a `uint32_t` value to a decimal char array (string).
 *
 * @details
 *   This method can also add a specific amount of leading zero's if necessary.
 *
 * @param[out] buf
 *   The buffer to put the resulting string in.@n
 *   **This needs to have a length of 10: `char buf[10];`!**
 *
 * @param[in] value
 *   The `uint32_t` value to convert to a string.
 *
 * @param [in] totalChars
 *   Total amount of characters, to be filled with leading zero's if necessary. @n
 *   **If a value <= 1 is given, no zero's will be added**
 *****************************************************************************/
void uint32_to_charDec(char *buf, uint32_t value, uint8_t totalChars)
{
	if (value == 0)
	{
		uint8_t counter;
		for (counter = 0; counter < totalChars; counter++)
		{
			buf[counter] = '0';
		}

		buf[counter++] = '\0'; /* NULL termination character */
	}
	else
	{
		/* MAX uint32_t value = FFFFFFFFh = 4294967295d (10 decimal chars) */
		char backwardsBuf[10];

		uint32_t calcval = value;
		uint8_t length = 0;
		uint8_t lengthCounter = 0;


		/* Loop until the value is zero (separate characters 0-9) and calculate length */
		while (calcval)
		{
			uint32_t rem = calcval % 10;
			backwardsBuf[length] = TO_DEC(rem); /* Convert to ASCII character */
			length++;

			calcval = calcval - rem;
			calcval = calcval / 10;
		}

		uint8_t index = 0;
		uint8_t addedZeros = 0;

		/* Add leading zero's if necessary */
		if (totalChars > 1)
		{
			/* Calculate power */
			uint16_t power = 1;
			while (totalChars != 1) {
				power *= 10;
				totalChars--;
			}

			/* Print leading zero's if necessary */
			if (value < power)
			{
				/* Add the correct amount of zero's */
				uint16_t checkValue = value;
				while (checkValue < power)
				{
					buf[index] = '0';
					addedZeros++;
					checkValue *= 10;
					index++;
				}
			}
		}

		/* Backwards counter */
		lengthCounter = length;

		/* Reverse the characters in the buffer for the final string */
		while (index < (length + addedZeros))
		{
			buf[index] = backwardsBuf[lengthCounter-1];
			lengthCounter--;
			index++;
		}

		/* Add NULL termination character */
		buf[(length + addedZeros)] = '\0';
	}
}
