/***************************************************************************//**
 * @file usart.h
 * @brief U(S)ART functionality for high-precision logging voltage/current meter.
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
 *   @n
 *
 *   Some methods also use code obtained from examples from STMicroelectronics.
 *
 *   **Copyright (c) 2020 STMicroelectronics. All rights reserved.**
 *
 *   These sections are licensed by ST under BSD 3-Clause license, the "License";
 *   One may not use these example files except in compliance with the License.
 *   One may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************/


/* Include guards prevent multiple inclusions of the same header */
#ifndef __USART_H_
#define __USART_H_


/* Includes necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/* Public definitions */
// None


/* Public prototypes */
void USART_HandleContinuousReception(void);
void USART2_SendCommand(uint8_t *command, uint8_t bytes);
void USART3_SendCommand(uint8_t *command, uint8_t bytes);
void USART1_INIT(void);
void USART2_INIT(void);
void USART3_INIT(void);
void USART1_print(char *message);
//void USART1_SendData(char *string, uint32_t size);
//void USART2_SendData(uint8_t *string, uint32_t size);
//void USART3_SendData(uint8_t *string, uint32_t size);
void USART1_CharReception_Callback(void);
void USART2_CharReception_Callback(void);
void USART3_CharReception_Callback(void);
void USART1_Error_Callback(void);
void USART2_Error_Callback(void);
void USART3_Error_Callback(void);


#endif /* __USART_H_ */
