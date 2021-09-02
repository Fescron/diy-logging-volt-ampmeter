/***************************************************************************//**
 * @file display.h
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
#ifndef __DISPLAY_H_
#define __DISPLAY_H_


/* Includes necessary for this header file */
// None


/* Public definitions */
// None


/* Public prototypes */
void initDisplays(void);
void updateLeftDisplay(void);
void updateRightDisplay(void);
void finishDisplayUpdates(void);
void displaySaveIcon(void);


#endif /* __DISPLAY_H_ */
