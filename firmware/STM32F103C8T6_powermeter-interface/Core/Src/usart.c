/***************************************************************************//**
 * @file usart.c
 * @brief U(S)ART functionality for high-precision logging voltage/current meter.
 * @version 1.1
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version.
 *   @li v1.1: Compared floats more reliably (and faster?) and implemented data-check to hopefully fix max/min logic.
 *
 * ******************************************************************************
 *
 * @todo
 *   **Future improvements:**@n
 *     - Add overflow catch if data.voltage/current are negative values?
 *        - `data.current > 9.9999`, `data.voltage > 99.999` (these checks are as of v1.1 of this file unnecessary...)
 *     - Increase baudrate for USART2/3 communication?
 *     - Add separate USART1 handler? (`USART_HandleContinuousReception();`)
 *     - Check if we really did receive the openLog startup-message `12<`.
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
 *   @li https://github.com/STMicroelectronics/STM32CubeF1/tree/master/Projects/STM32F103RB-Nucleo/Examples_LL/USART/USART_Communication_Rx_IT_Continuous
 *
 *   **Copyright (c) 2020 STMicroelectronics. All rights reserved.**
 *
 *   These sections are licensed by ST under BSD 3-Clause license, the "License";
 *   One may not use these example files except in compliance with the License.
 *   One may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************/


#include "usart.h"              /* Include corresponding header file */

#include <stdint.h>             /* (u)intXX_t */
#include "stm32f1xx_ll_bus.h"   /* Low-Level Clock Management */
#include "stm32f1xx_ll_gpio.h"  /* Low-Level General Purpose IO (GPIO) peripheral API */
#include "stm32f1xx_ll_usart.h" /* Low-Level Universal synchr./asynchr. receiver/transmitter (USART/UART) Peripheral API */
#include "SEGGER_RTT.h"         /* Segger RTT functionality (debugging) */

#include "util.h"               /* Utility functionality */
#include "main.h"				/* Pin mapping */
#include "conversion.h"			/* Conversion and settings */


/* Local definitions */
#define RX_BUFFER_SIZE       8
#define RX_BUFFER_SIZE_UART1 3
#define BAUDRATE_METER       9600   /* Baudrate of volt/currentmeter */
#define BAUDRATE_LOGGER      115200 /* Baudrate of external datalogger */


/* Local variables */

/* USART1 RX buffers for storing received data */
uint8_t aRXBufferA_USART1[RX_BUFFER_SIZE_UART1];
uint8_t aRXBufferB_USART1[RX_BUFFER_SIZE_UART1];
__IO uint32_t uwNbReceivedChars_USART1;
__IO uint32_t uwBufferReadyIndication_USART1;
uint8_t *pBufferReadyForUser_USART1;
uint8_t *pBufferReadyForReception_USART1;

/* USART2 RX buffers for storing received data */
uint8_t aRXBufferA_USART2[RX_BUFFER_SIZE];
uint8_t aRXBufferB_USART2[RX_BUFFER_SIZE];
__IO uint32_t uwNbReceivedChars_USART2;
__IO uint32_t uwBufferReadyIndication_USART2;
uint8_t *pBufferReadyForUser_USART2;
uint8_t *pBufferReadyForReception_USART2;

/* USART3 RX buffers for storing received data */
uint8_t aRXBufferA_USART3[RX_BUFFER_SIZE];
uint8_t aRXBufferB_USART3[RX_BUFFER_SIZE];
__IO uint32_t uwNbReceivedChars_USART3;
__IO uint32_t uwBufferReadyIndication_USART3;
uint8_t *pBufferReadyForUser_USART3;
uint8_t *pBufferReadyForReception_USART3;


/* Local prototypes */
// None


/**************************************************************************//**
 * @brief
 *   This function monitors USART1/2/3 buffer filling indication and
 *   moves data around accordingly.
 *****************************************************************************/
void USART_HandleContinuousReception(void)
{
	/* Checks if USART1 Buffer full indication has been set */
	if (uwBufferReadyIndication_USART1 != 0)
	{
		/* Call user Callback in charge of consuming data from filled USART2 buffer */
		SEGGER_RTT_printf(0, "Current USART1 RX buffer full: [%s], Reception will go on in alternate buffer.\n\r", pBufferReadyForUser_USART1);

		/* Signal logic that the logger has correctly started up */
		settings.loggerReady = 1;

		/* Reset USART1 indication */
		uwBufferReadyIndication_USART1 = 0;
	}

	/* Checks if USART2 Buffer full indication has been set */
	if (uwBufferReadyIndication_USART2 != 0)
	{
		/** Format of the data coming from the meters:
		 *   - Byte 0     = 0xFA
		 *   - Byte 1     = 0xFB
		 *   - Byte 2     = Device address (default: 0x00)
		 *   - Byte 3 - 6 = Measurement (~float value)
		 *   - Byte 7     = CRC check (SUM of bytes 3 - 6)
		 */

		uint8_t checksum = pBufferReadyForUser_USART2[3] + pBufferReadyForUser_USART2[4] + pBufferReadyForUser_USART2[5] + pBufferReadyForUser_USART2[6];

		/* Only use the bytes if the data is valid */
		if ((pBufferReadyForUser_USART2[0] == 0xFA) && (pBufferReadyForUser_USART2[1] == 0xFB) && (pBufferReadyForUser_USART2[7] == checksum))
		{
			data.voltage = bytes_to_float(pBufferReadyForUser_USART2[6], pBufferReadyForUser_USART2[5], pBufferReadyForUser_USART2[4], pBufferReadyForUser_USART2[3]);

			if (data.voltage < 99.999) /* Meter reads max 50V ... */
			{
				/* Convert floats to uint16_t (voltage has 3 decimal places: *1000) */
				uint16_t oldVolt = FLOAT_TO_INT(data.oldVolt*1000);
				uint16_t voltage = FLOAT_TO_INT(data.voltage*1000);
				uint16_t minVoltage = FLOAT_TO_INT(data.minVoltage*1000);
				uint16_t maxVoltage = FLOAT_TO_INT(data.maxVoltage*1000);

				if (oldVolt != voltage)
				{
				  data.oldVolt = data.voltage;
				  data.newVolt = 1;
				}

				/* Update min/max fields if necessary */
				if (voltage < minVoltage)
				{
					data.minVoltage = data.voltage;
					data.newMinVolt = 1;
				}
				else if (data.firstVolt)
				{
					data.minVoltage = data.voltage;
					data.newMinVolt = 1;
					data.firstVolt = 0;
				}

				if (voltage > maxVoltage)
				{
					data.maxVoltage = data.voltage;
					data.newMaxVolt = 1;
				}

				data.voltReceived = 1;
			}
		}

		/* Reset USART2 indication */
		uwBufferReadyIndication_USART2 = 0;

	}

	/* Checks if USART3 Buffer full indication has been set */
	if (uwBufferReadyIndication_USART3 != 0)
	{
		/** Format of the data coming from the meters:
		 *   - Byte 0     = 0xFA
		 *   - Byte 1     = 0xFB
		 *   - Byte 2     = Device address (default: 0x00)
		 *   - Byte 3 - 6 = Measurement (~float value)
		 *   - Byte 7     = CRC check (SUM of bytes 3 - 6)
		 */

		uint8_t checksum = pBufferReadyForUser_USART3[3] + pBufferReadyForUser_USART3[4] + pBufferReadyForUser_USART3[5] + pBufferReadyForUser_USART3[6];

		/* Only use the bytes if the data is valid */
		if ((pBufferReadyForUser_USART3[0] == 0xFA) && (pBufferReadyForUser_USART3[1] == 0xFB) && (pBufferReadyForUser_USART3[7] == checksum))
		{
			data.current = bytes_to_float(pBufferReadyForUser_USART3[6], pBufferReadyForUser_USART3[5], pBufferReadyForUser_USART3[4], pBufferReadyForUser_USART3[3]);

			if (data.current < 9.9999) /* Meter reads max 5A ... */
			{
				/* Convert floats to uint16_t (current has 4 decimal places: *10000) */
				uint16_t oldCurr = FLOAT_TO_INT(data.oldCurr*10000);
				uint16_t current = FLOAT_TO_INT(data.current*10000);
				uint16_t minCurrent = FLOAT_TO_INT(data.minCurrent*10000);
				uint16_t maxCurrent = FLOAT_TO_INT(data.maxCurrent*10000);

				if (oldCurr != current)
				{
				  data.oldCurr = data.current;
				  data.newCurr = 1;
				}

				/* Update min/max fields if necessary */
				if (current < minCurrent)
				{
					data.minCurrent = data.current;
					data.newMinCurr = 1;
				}
				else if (data.firstCurr)
				{
					data.minCurrent = data.current;
					data.newMinCurr = 1;
					data.firstCurr = 0;
				}

				if (current > maxCurrent)
				{
					data.maxCurrent = data.current;
					data.newMaxCurr = 1;
				}

				data.currReceived = 1;
			}
		}

		/* Reset USART3indication */
		uwBufferReadyIndication_USART3 = 0;
	}

	/* Set values if the voltmeter is powered down */
	if (!LL_GPIO_IsInputPinSet(V_ENin_GPIO_Port, V_ENin_Pin))
	{
		data.voltage = 0.0;

		/* Convert floats to uint16_t (voltage has 3 decimal places: *1000) */
		uint16_t oldVolt = FLOAT_TO_INT(data.oldVolt*1000);
		uint16_t voltage = FLOAT_TO_INT(data.voltage*1000);

		if (oldVolt != voltage)
		{
		  data.oldVolt = data.voltage;
		  data.newVolt = 1;
		}

		data.voltReceived = 1;
	}

	/* Set values if the current meter is powered down */
	if (!LL_GPIO_IsInputPinSet(A_ENin_GPIO_Port, A_ENin_Pin))
	{
		data.current = 0.0;

		/* Convert floats to uint16_t (current has 4 decimal places: *10000) */
		uint16_t oldCurr = FLOAT_TO_INT(data.oldCurr*10000);
		uint16_t current = FLOAT_TO_INT(data.current*10000);

		if (oldCurr != current)
		{
		  data.oldCurr = data.current;
		  data.newCurr = 1;
		}

		data.currReceived = 1;
	}
}


/**************************************************************************//**
 * @brief
 *   Send a byte (`uint8_t`) command to USART2.
 *
 * @details
 *   This method also resets `uwNbReceivedChars_USART2` just in case.
 *
 * @param[in] command
 *   Pointer to the byte-array containing the commands.
 *
 * @param[in] bytes
 *   Amount of bytes to send.
 *****************************************************************************/
void USART2_SendCommand(uint8_t *command, uint8_t bytes)
{
	/* Send characters one per one, until last char to be sent */
	for (uint32_t index = 0; index < bytes; index++)
	{
		/* Wait for TXE flag to be raised */
		while (!LL_USART_IsActiveFlag_TXE(USART2));

		/* Write character in Transmit Data register.
		   TXE flag is cleared by writing data in DR register */
		LL_USART_TransmitData8(USART2, command[index]);
	}

	/* Wait for TC flag to be raised for last char */
	while (!LL_USART_IsActiveFlag_TC(USART2));

	/* Reset buffer mechanism */
	uwNbReceivedChars_USART2 = 0;
//	uwBufferReadyIndication_USART2 = 0; // TODO Maybe use this when using contiuous output?
}


/**************************************************************************//**
 * @brief
 *   Send a byte (`uint8_t`) command to USART3.
 *
 * @details
 *   This method also resets `uwNbReceivedChars_USART3` just in case.
 *
 * @param[in] command
 *   Pointer to the byte-array containing the commands.
 *
 * @param[in] bytes
 *   Amount of bytes to send.
 *****************************************************************************/
void USART3_SendCommand(uint8_t *command, uint8_t bytes)
{
	/* Send characters one per one, until last char to be sent */
	for (uint32_t index = 0; index < bytes; index++)
	{
		/* Wait for TXE flag to be raised */
		while (!LL_USART_IsActiveFlag_TXE(USART3));

		/* Write character in Transmit Data register.
		   TXE flag is cleared by writing data in DR register */
		LL_USART_TransmitData8(USART3, command[index]);
	}

	/* Wait for TC flag to be raised for last char */
	while (!LL_USART_IsActiveFlag_TC(USART3));

	/* Reset buffer mechanism */
	uwNbReceivedChars_USART3 = 0;
//	uwBufferReadyIndication_USART3 = 0; // TODO Maybe use this when using contiuous output?
}


/**************************************************************************//**
 * @brief
 *   USART1 Initialization Function.
 *
 * @details
 *   @li Baudrate = BAUDRATE_LOGGER
 *   @li PA9  = USART1_TX
 *   @li PA10 = USART1_RX
 *****************************************************************************/
void USART1_INIT(void)
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	/**USART1 GPIO Configuration
	PA9   ------> USART1_TX
	PA10   ------> USART1_RX
	*/
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART1 interrupt Init */
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART1_IRQn);

	/* UART1 Configuration */
	USART_InitStruct.BaudRate = BAUDRATE_LOGGER;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART1);
	LL_USART_Enable(USART1);

	/* Initiate buffer mechanism */
	pBufferReadyForReception_USART1 = aRXBufferA_USART1;
	pBufferReadyForUser_USART1      = aRXBufferB_USART1;
	uwNbReceivedChars_USART1 = 0;
	uwBufferReadyIndication_USART1 = 0;

	/* Clear Overrun flag, in case characters have already been sent to USART */
	LL_USART_ClearFlag_ORE(USART1);

	/* Enable RXNE and Error interrupts */
	LL_USART_EnableIT_RXNE(USART1);
	LL_USART_EnableIT_ERROR(USART1);
}


/**************************************************************************//**
 * @brief
 *   USART2 Initialization Function.
 *
 * @details
 *   @li Baudrate = BAUDRATE_METER
 *   @li PA2 = USART2_TX
 *   @li PA3 = USART2_RX
 *****************************************************************************/
void USART2_INIT(void)
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	/**USART2 GPIO Configuration
	PA2   ------> USART2_TX
	PA3   ------> USART2_RX
	*/
	GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART2_IRQn);

	/* UART2 Configuration */
	USART_InitStruct.BaudRate = BAUDRATE_METER;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART2);
	LL_USART_Enable(USART2);

	/* Initiate buffer mechanism */
	pBufferReadyForReception_USART2 = aRXBufferA_USART2;
	pBufferReadyForUser_USART2      = aRXBufferB_USART2;
	uwNbReceivedChars_USART2 = 0;
	uwBufferReadyIndication_USART2 = 0;

	/* Clear Overrun flag, in case characters have already been sent to USART */
	LL_USART_ClearFlag_ORE(USART2);

	/* Enable RXNE and Error interrupts */
	LL_USART_EnableIT_RXNE(USART2);
	LL_USART_EnableIT_ERROR(USART2);
}


/**************************************************************************//**
 * @brief
 *   USART3 Initialization Function.
 *
 * @details
 *   @li Baudrate = BAUDRATE_METER
 *   @li PB10 = USART3_TX
 *   @li PB11 = USART3_RX
 *****************************************************************************/
void USART3_INIT(void)
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

	/**USART3 GPIO Configuration
	PB10   ------> USART3_TX
	PB11   ------> USART3_RX
	*/
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USART3 interrupt Init */
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART3_IRQn);

	/* UART3 Configuration */
	USART_InitStruct.BaudRate = BAUDRATE_METER;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART3, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART3);
	LL_USART_Enable(USART3);

	/* Initiate buffer mechanism */
	pBufferReadyForReception_USART3 = aRXBufferA_USART3;
	pBufferReadyForUser_USART3      = aRXBufferB_USART3;
	uwNbReceivedChars_USART3 = 0;
	uwBufferReadyIndication_USART3 = 0;

	/* Clear Overrun flag, in case characters have already been sent to USART */
	LL_USART_ClearFlag_ORE(USART3);

	/* Enable RXNE and Error interrupts */
	LL_USART_EnableIT_RXNE(USART3);
	LL_USART_EnableIT_ERROR(USART3);
}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to USARTx.
 *
 * @note
 *   If the input is not a string (ex.: `"Hello world!"`) but a char array,
 *   the input message (array) needs to end with NULL (`"\0"`)!
 *
 * @param[in] message
 *   The string to print to USARTx.
 *****************************************************************************/
void USART1_print(char *message)
{
	/* "message[i] != 0" makes "uint32_t length = strlen(message)"
	 * not necessary (given string MUST be terminated by NULL for this to work) */
	for (uint32_t i = 0; message[i] != 0; i++)
	{
		/* Wait for TXE flag to be raised */
		while (!LL_USART_IsActiveFlag_TXE(USART1));

		/* Write character in Transmit Data register.
		   TXE flag is cleared by writing data in DR register */
		LL_USART_TransmitData8(USART1, message[i]);
	}
}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to USART1.
 *
 * @param[in] string
 *   The string to print to USART1.
 *
 * @param[in] size
 *   Length of the string in bytes.
 *****************************************************************************/
//void USART1_SendData(char *string, uint32_t size)
//{
//	uint32_t index = 0;
//	char *pchar = string;
//
//	/* Send characters one per one, until last char to be sent */
//	for (index = 0; index < size; index++)
//	{
//		/* Wait for TXE flag to be raised */
//		while (!LL_USART_IsActiveFlag_TXE(USART1));
//
//		/* Write character in Transmit Data register.
//		   TXE flag is cleared by writing data in DR register */
//		LL_USART_TransmitData8(USART1, *pchar++);
//	}
//
//	/* Wait for TC flag to be raised for last char */
//	while (!LL_USART_IsActiveFlag_TC(USART1));
//}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to USART2.
 *
 * @param[in] string
 *   The string to print to USART2.
 *
 * @param[in] size
 *   Length of the string in bytes.
 *****************************************************************************/
//void USART2_SendData(uint8_t *string, uint32_t size)
//{
//	uint32_t index = 0;
//	uint8_t *pchar = string;
//
//	/* Send characters one per one, until last char to be sent */
//	for (index = 0; index < size; index++)
//	{
//		/* Wait for TXE flag to be raised */
//		while (!LL_USART_IsActiveFlag_TXE(USART2));
//
//		/* Write character in Transmit Data register.
//		   TXE flag is cleared by writing data in DR register */
//		LL_USART_TransmitData8(USART2, *pchar++);
//	}
//
//	/* Wait for TC flag to be raised for last char */
//	while (!LL_USART_IsActiveFlag_TC(USART2));
//}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to USART3.
 *
 * @param[in] string
 *   The string to print to USART3.
 *
 * @param[in] size
 *   Length of the string in bytes.
 *****************************************************************************/
//void USART3_SendData(uint8_t *string, uint32_t size)
//{
//	uint32_t index = 0;
//	uint8_t *pchar = string;
//
//	/* Send characters one per one, until last char to be sent */
//	for (index = 0; index < size; index++)
//	{
//		/* Wait for TXE flag to be raised */
//		while (!LL_USART_IsActiveFlag_TXE(USART3));
//
//		/* Write character in Transmit Data register.
//		   TXE flag is cleared by writing data in DR register */
//		LL_USART_TransmitData8(USART3, *pchar++);
//	}
//
//	/* Wait for TC flag to be raised for last char */
//	while (!LL_USART_IsActiveFlag_TC(USART3));
//}


/**************************************************************************//**
 * @brief
 *   Function called from USART1 IRQ Handler when RXNE flag is set. @n
 *   Function is in charge of reading character received on USART1 RX line.
 *****************************************************************************/
void USART1_CharReception_Callback(void)
{
	uint8_t *ptemp;

	/* Read Received character. RXNE flag is cleared by reading of DR register */
	pBufferReadyForReception_USART1[uwNbReceivedChars_USART1++] = LL_USART_ReceiveData8(USART1);

	/* Checks if Buffer full indication has been set */
	if (uwNbReceivedChars_USART1 >= RX_BUFFER_SIZE_UART1)
	{
		/* Set Buffer swap indication */
		uwBufferReadyIndication_USART1 = 1;

		/* Swap buffers for next bytes to be received */
		ptemp = pBufferReadyForUser_USART1;
		pBufferReadyForUser_USART1 = pBufferReadyForReception_USART1;
		pBufferReadyForReception_USART1 = ptemp;
		uwNbReceivedChars_USART1 = 0;
	}
}


/**************************************************************************//**
 * @brief
 *   Function called from USART2 IRQ Handler when RXNE flag is set. @n
 *   Function is in charge of reading character received on USART2 RX line.
 *****************************************************************************/
void USART2_CharReception_Callback(void)
{
	uint8_t *ptemp;

	/* Read Received character. RXNE flag is cleared by reading of DR register */
	pBufferReadyForReception_USART2[uwNbReceivedChars_USART2++] = LL_USART_ReceiveData8(USART2);

	/* Checks if Buffer full indication has been set */
	if (uwNbReceivedChars_USART2 >= RX_BUFFER_SIZE)
	{
		/* Set Buffer swap indication */
		uwBufferReadyIndication_USART2 = 1;

		/* Swap buffers for next bytes to be received */
		ptemp = pBufferReadyForUser_USART2;
		pBufferReadyForUser_USART2 = pBufferReadyForReception_USART2;
		pBufferReadyForReception_USART2 = ptemp;
		uwNbReceivedChars_USART2 = 0;
	}
}


/**************************************************************************//**
 * @brief
 *   Function called from USART3 IRQ Handler when RXNE flag is set. @n
 *   Function is in charge of reading character received on USART3 RX line.
 *****************************************************************************/
void USART3_CharReception_Callback(void)
{
	uint8_t *ptemp;

	/* Read Received character. RXNE flag is cleared by reading of DR register */
	pBufferReadyForReception_USART3[uwNbReceivedChars_USART3++] = LL_USART_ReceiveData8(USART3);

	/* Checks if Buffer full indication has been set */
	if (uwNbReceivedChars_USART3 >= RX_BUFFER_SIZE)
	{
		/* Set Buffer swap indication */
		uwBufferReadyIndication_USART3 = 1;

		/* Swap buffers for next bytes to be received */
		ptemp = pBufferReadyForUser_USART3;
		pBufferReadyForUser_USART3 = pBufferReadyForReception_USART3;
		pBufferReadyForReception_USART3 = ptemp;
		uwNbReceivedChars_USART3 = 0;
	}
}


/**************************************************************************//**
 * @brief
 *   Function called in case of error detected in USART1 IT Handler.
 *****************************************************************************/
void USART1_Error_Callback(void)
{
	__IO uint32_t sr_reg;

	/* Disable USART1_IRQn */
	NVIC_DisableIRQ(USART1_IRQn);

	/* Error handling example :
	- Read USART SR register to identify flag that leads to IT raising
	- Perform corresponding error handling treatment according to flag
	*/
	sr_reg = LL_USART_ReadReg(USART1, SR);
	if (sr_reg & LL_USART_SR_NE)
	{
		/* case Noise Error flag is raised : Clear NF Flag */
		LL_USART_ClearFlag_NE(USART1);
	}
	else
	{
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED"Error: "RTT_CTRL_RESET"USART1_Error_Callback\n\r");
		while(1);
	}
}


/**************************************************************************//**
 * @brief
 *   Function called in case of error detected in USART2 IT Handler.
 *****************************************************************************/
void USART2_Error_Callback(void)
{
	__IO uint32_t sr_reg;

	/* Disable USART2_IRQn */
	NVIC_DisableIRQ(USART2_IRQn);

	/* Error handling example :
	- Read USART SR register to identify flag that leads to IT raising
	- Perform corresponding error handling treatment according to flag
	*/
	sr_reg = LL_USART_ReadReg(USART2, SR);
	if (sr_reg & LL_USART_SR_NE)
	{
		/* case Noise Error flag is raised : Clear NF Flag */
		LL_USART_ClearFlag_NE(USART2);
	}
	else
	{
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED"Error: "RTT_CTRL_RESET"USART2_Error_Callback\n\r");
		while(1);
	}
}


/**************************************************************************//**
 * @brief
 *   Function called in case of error detected in USART3 IT Handler.
 *****************************************************************************/
void USART3_Error_Callback(void)
{
	__IO uint32_t sr_reg;

	/* Disable USART3_IRQn */
	NVIC_DisableIRQ(USART3_IRQn);

	/* Error handling example :
	- Read USART SR register to identify flag that leads to IT raising
	- Perform corresponding error handling treatment according to flag
	*/
	sr_reg = LL_USART_ReadReg(USART3, SR);
	if (sr_reg & LL_USART_SR_NE)
	{
		/* case Noise Error flag is raised : Clear NF Flag */
		LL_USART_ClearFlag_NE(USART3);
	}
	else
	{
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED"Error: "RTT_CTRL_RESET"USART3_Error_Callback\n\r");
		while(1);
	}
}
