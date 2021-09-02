/* USER CODE BEGIN Header */

/***************************************************************************//**
 * @file main.h
 * @brief Main header-file for the high-precision logging voltage/current meter project.
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
 * @attention
 *   Due to mistakes in the schematic/PCB-layout of the first hardware board
 *   the functionality of some GPIO pins is swapped:
 *    - `UART1_ENout` is not used, but `UART1_3V3out` instead.
 *    - `SW0`and `SW0` are swapped with `GPIO1`and `GPIO2` so the internal
 *      circuitry can be used for encoder-turn logic.
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

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_rtc.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW0_Pin LL_GPIO_PIN_0
#define SW0_GPIO_Port GPIOA
#define SW0_EXTI_IRQn EXTI0_IRQn
#define SW1_Pin LL_GPIO_PIN_1
#define SW1_GPIO_Port GPIOA
#define SW1_EXTI_IRQn EXTI1_IRQn
#define V_ENin_Pin LL_GPIO_PIN_4
#define V_ENin_GPIO_Port GPIOA
#define A_ENin_Pin LL_GPIO_PIN_1
#define A_ENin_GPIO_Port GPIOB
#define LED_Pin LL_GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define Buzzer_Pin LL_GPIO_PIN_13
#define Buzzer_GPIO_Port GPIOB
#define UART1_3V3out_Pin LL_GPIO_PIN_14
#define UART1_3V3out_GPIO_Port GPIOB
#define Relay_Pin LL_GPIO_PIN_8
#define Relay_GPIO_Port GPIOA
#define ENC_Key_Pin LL_GPIO_PIN_5
#define ENC_Key_GPIO_Port GPIOB
#define ENC_Key_EXTI_IRQn EXTI9_5_IRQn
#define UART1_ENout_Pin LL_GPIO_PIN_8
#define UART1_ENout_GPIO_Port GPIOB
#define UART1_DTRout_Pin LL_GPIO_PIN_9
#define UART1_DTRout_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define GPIO1_Pin LL_GPIO_PIN_5
#define GPIO1_Port GPIOA
#define GPIO2_Pin LL_GPIO_PIN_13
#define GPIO2_Port GPIOC

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
