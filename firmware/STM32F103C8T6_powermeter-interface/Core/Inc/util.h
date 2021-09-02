/***************************************************************************//**
 * @file util.h
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


/* Include guards prevent multiple inclusions of the same header */
#ifndef __UTIL_H_
#define __UTIL_H_


/* Includes necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/* Public definitions */
// None


/* Public prototypes */
float bytes_to_float(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3);
void splitFloat(float fValue, uint16_t *beforeComma, uint16_t *afterComma, uint8_t decimalPlaces);
void uint32_to_charDec(char *buf, uint32_t value, uint8_t totalChars);


#endif /* __UTIL_H_ */
