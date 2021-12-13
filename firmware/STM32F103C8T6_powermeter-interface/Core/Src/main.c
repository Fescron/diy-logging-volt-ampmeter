/* USER CODE BEGIN Header */

/***************************************************************************//**
 * @file main.c
 * @brief Main source-file for the high-precision logging voltage/current meter project.
 * @details
 *   The code in this project asks two BY56W volt/current meters for measurements,
 *   calculates a few additional values (min/max/power/Ah/Wh) with these, prints
 *   them to displays and sends them (with time/date values) to a UART port so
 *   a Sparkfun OpenLog can log these measurements to a `.TXT` file, which can
 *   eventually be renamed to a `.CSV` so the measurements can be easily plotted.
 * @version 1.2
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version.
 *   @li v1.1: Started printing date before time for each measurement-line, removed day-writing in footer.
 *   @li v1.2: Compared power floats more reliably.
 *
 * ******************************************************************************
 *
 * @todo
 *   **Things to do in the near future:**@n
 *     - Check Ah/Wh calculations.
 *     - Check if the power/Ah/Wh calculations are done using wrong/old measurements.
 *     - Handle uint32_t wraparound for time between calculations measurements and waiting time.
 *     - Don't send/do certain functions if one of the meters is powered down.
 *
 * @todo
 *   **Long-term future improvements:**@n
 *     - Add function to stop measurements when the voltage/current is (above/) below a certain value.
 *     - Add external temperature reading functionality.
 *     - Add internal temperature reading functionality (`MX_ADC1_Init();`).
 *     - Add interrupt-logging functionality.
 *     - Add relay-opening functionality.
 *     - Add "manual measurement-mode" to log on up-button press.
 *     - Add "performance-mode" with no display refreshes.
 *        - (sub-page on right display, start/stop with up, beeps for confirmation)
 *     - Add low-battery beeping.
 *     - Add buzzer functionality using TIM2 (`MX_TIM2_Init();`).
 *        -  (short beep button-press, longer when measurement taken, add ON/OFF settings page)
 *     - Optimize encoder logic so there is less copy-pasting.
 *     - Add debounce logic to `getSW0();`, `getSW1();` and `getENCkey();`.
 *     - Use `LL_GetTick();` instead of `HAL_GetTick();`?
 *     - Add circular pages for setting day/month/hour/minute/second (`changeDateTime`).
 *     - Add day-checking in function of the month?
 *     - Use defines for circular pages?
 *     - Start using `aBY56W_ContinuousRead`? Send on every meter power-up?
 *     - Only one while-loop (`USART_HandleContinuousReception`) when one meter is
 *       connected, way more if both are? Optimize this?
 *     - Add overflow catch if data.voltage/current are negative values?
 *        - `data.power > 999.999`, `data.ah > 9999.999`, `data.wh > 9999.999`
 *     - Remove all Segger-RTT functionality?
 *     - Store settings in power-down-safe memory.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usart.h"      /* UART communication functionality */
#include "SEGGER_RTT.h" /* Segger RTT debugging functionality */
#include "util.h"       /* Utility functionality */
#include "conversion.h" /* Conversion and settings */
#include "display.h"    /* Display functionality */
#include "rtc.h"        /* Real Time Clock and Calendar functionality */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/** Max amount of while loop passes before exiting the while loop early (~meter unresponsive) */
#define MAX_WHILELOOPS_METER_RESPONSE 9000

/** Waiting time before shutting down the external UART logger after writing the footer */
#define SHUTDOWN_DELAY_UART_MODULE_MS 500

/** Waiting time for an external UART power-up message before writing the header */
#define STARTUP_DELAY_UART_MODULE_MS  2000

/** Time between battery voltage measurements */
#define VBAT_MEASUREMENT_PERIOD_S     10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* BY56W meter commands */
static const uint8_t aBY56W_SingleRead[4]     = {0x88, 0xAE, 0x00, 0x11}; /* 0x00 = Device address */
//static const uint8_t aBY56W_ContinuousRead[4] = {0x88, 0xAE, 0x00, 0x21}; /* 0x00 = Device address */
//static const uint8_t aBY56W_StopRead[4]       = {0x88, 0xAE, 0x00, 0x01}; /* 0x00 = Any byte */

/* Data in structs */
struct Data_t         data;     /* Measurement data (changes a lot) */
struct cData_t        cData;    /* Measuremtn data converted to char-arrays */
struct Settings_t     settings; /* General data/settings (changes less frequently */
struct RTC_dateTime_t rtc;      /* Date and time */

/** LUT for period selection [s] (0 = as fast as possible) */
static const uint16_t LUT_period_s[16] = {0, 1, 2, 5, 10, 15, 30, 60, 120, 300, 600, 900, 1800, 3600, 7200, 18000};

/** Length of LUT */
static const uint8_t LUT_period_s_length = 16;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void writeHeader(void);
void writeFooter(void);
void writeMeasurements(void);
void checkEncoder(void);
void checkSwitches(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
//  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_ADC2_Init();
  MX_TIM3_Init();
//  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* Power down UART voltage output */
  LL_GPIO_SetOutputPin(UART1_3V3out_GPIO_Port, UART1_3V3out_Pin); /* P-MOS so inverted logic! */

  /* Power up UART DTR (~reset)-pin so we're not resetting the module */
  LL_GPIO_SetOutputPin(UART1_DTRout_GPIO_Port, UART1_DTRout_Pin);


  /* Enable output channel 1 (rotary encoder) */
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2);

  /* Enable counter */
  LL_TIM_EnableCounter(TIM3);

  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM3);


  /* Initialize date/time functionality */
  RTC_Init();


  /* Enable the update interrupt (logging-timing) */
//  LL_TIM_EnableIT_UPDATE(TIM2); // TODO change to buzzer timing

  /* Enable counter */
//  LL_TIM_EnableCounter(TIM2); // TODO change to buzzer timing

  /* Force update generation */
//  LL_TIM_GenerateEvent_UPDATE(TIM2); // TODO change to buzzer timing


  /* Initialize UART functionality */
  USART1_INIT();
  USART2_INIT();
  USART3_INIT();

  /* Initialize structs */
  initDataStruct();
  initSettingsStruct();

  /* Activate ADC for battery voltage measurements */
  Activate_ADC();

  /* Clear Terminal for Segger RTT functionality */
  SEGGER_RTT_WriteString(0, RTT_CTRL_CLEAR"START\r\n");

  /* Initialize displays */
  initDisplays();

  /* Disable buzzer */
//  LL_GPIO_ResetOutputPin(Buzzer_GPIO_Port, Buzzer_Pin);

//	  LL_GPIO_TogglePin(Relay_GPIO_Port, Relay_Pin);
//	  LL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);


//  SEGGER_RTT_printf(0, "%sTime:%s%s %.7d\n\r",
//                        RTT_CTRL_RESET,
//                        RTT_CTRL_BG_BRIGHT_RED,
//                        RTT_CTRL_TEXT_BRIGHT_WHITE,
//                        1111111
//                        );
//  SEGGER_RTT_WriteString(0, RTT_CTRL_RESET"Red: "RTT_CTRL_TEXT_BRIGHT_RED"This text is red."RTT_CTRL_TEXT_BLACK""RTT_CTRL_BG_BRIGHT_RED"This background is red. "RTT_CTRL_RESET"Normal text again.\n\r");
//	SEGGER_RTT_printf(0, "Value = %x\r\n", value);
//	SEGGER_RTT_printf(0, RTT_CTRL_RESET"%-.3d ", value);
//	SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_RED"0x%.2x ", value);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  checkEncoder();
	  checkSwitches();

	  USART2_SendCommand(aBY56W_SingleRead, 4); /* Voltage */
	  USART3_SendCommand(aBY56W_SingleRead, 4); /* Current */

	  uint16_t whileLoops = 0;

	  while (!(data.voltReceived) && !(data.currReceived) && (whileLoops < MAX_WHILELOOPS_METER_RESPONSE))
	  {
		  USART_HandleContinuousReception();
		  whileLoops++;
	  }

//	  SEGGER_RTT_printf(0, "%d ", whileLoops);

	  if (whileLoops < MAX_WHILELOOPS_METER_RESPONSE)
	  {
		  /* Store tick-value of latest measurements */
		  if (data.latestMScounter == 0)
		  {
			  data.msCounter1 = HAL_GetTick();
			  data.latestMScounter = 1;
		  }
		  else if (data.latestMScounter == 1)
		  {
			  data.msCounter0 = HAL_GetTick();
			  data.latestMScounter = 0;
		  }
	  }

	  /* Calculate power, Ah and Wh */
	  if (data.voltReceived || data.currReceived)
	  {
		  data.power = data.voltage * data.current;
		  if (data.power > 999.999) data.power = 999.999;

		  /* Convert floats to uint32_t (power has 3 decimal places: *1000) */
		  uint32_t oldPower = FLOAT_TO_INT(data.oldPower*1000);
		  uint32_t power = FLOAT_TO_INT(data.power*1000);

		  if (oldPower != power)
		  {
			  data.oldPower = data.power;
			  data.newPow = 1;
		  }

		  /* Calculate time between measurements */
		  uint32_t msTime = 0;
		  if (data.latestMScounter == 0) msTime = data.msCounter0 - data.msCounter1;
		  else if (data.latestMScounter == 1) msTime = data.msCounter1 - data.msCounter0;

//			  SEGGER_RTT_printf(0, "%dms ", msTime);

		  data.ah += data.current * ((float)msTime / 3600000.0);
		  if (data.ah > 9999.999) data.ah = 9999.999;

		  data.newAh = 1;

		  data.wh += data.power * ((float)msTime / 3600000.0);
		  if (data.wh > 9999.999) data.wh = 9999.999;

		  data.newWh = 1;
	  }

	  data.voltReceived = 0;
	  data.currReceived = 0;

	  /* Change variables if one second is elapsed */
	  if (decSecondPassed())
	  {
		  /* Signal (second) conversion logic */
		  settings.newSec = 1;

		  /* Get new RTC values if not changing the date/time manually */
		  if ((settings.changeDateTime == 0) && (settings.secPassed == 0)) readFromRTC();

		  /* Update runtime if running */
		  if ((settings.mode == 1) && settings.loggerReady)
		  {
			  if (settings.remMeasPeriodS > 0) settings.remMeasPeriodS--;

			  /* Re-calculate runtime */
			  if (data.runSecs < 59) data.runSecs++;
			  else if (data.runSecs == 59)
			  {
				  if (data.runMins < 59) data.runMins++;
				  else if (data.runMins == 59)
				  {
					  if (data.runHours < 99) data.runHours++;

					  data.newRunHours = 1; /* Display needs updating */
					  data.runMins = 0;
				  }
				  data.newRunMins = 1; /* Display needs updating */
				  data.runSecs = 0;
			  }
			  data.newRunSecs = 1; /* Display needs updating */
		  }

		  if (settings.vbatCounter > 0) settings.vbatCounter--;
		  else if (settings.vbatCounter == 0)
		  {
			  startBattVoltMeasurement();
			  settings.vbatCounter = VBAT_MEASUREMENT_PERIOD_S;
		  }
	  }

	  convertValues();

	  /* Stopped, Logger needs to be disabled */
	  if ((settings.mode == 0) && settings.headerSaved)
	  {
		  if (settings.msWaiting == 0)
		  {
			  /* Make sure all values are converted to chars */
			  forceConversion();

			  displaySaveIcon();
			  writeFooter();

			  /* Set waiting time */
			  settings.msWaiting = SHUTDOWN_DELAY_UART_MODULE_MS;
			  settings.msWaitingStart = HAL_GetTick();
		  }
		  else if ((HAL_GetTick() - settings.msWaitingStart) >= settings.msWaiting)
		  {
			  /* Disable power to logger */
			  LL_GPIO_SetOutputPin(UART1_3V3out_GPIO_Port, UART1_3V3out_Pin); /* P-MOS so inverted logic! */

			  /* Reset waiting functionality */
			  settings.msWaiting = 0;
			  settings.msWaitingStart = 0;

			  settings.loggerReady = 0;
			  settings.headerSaved = 0;
		  }
	  }

	  /* Just started, header not yet saved */
	  if ((settings.mode == 1) && !(settings.headerSaved))
	  {
		  if (settings.msWaiting == 0)
		  {
			  settings.remMeasPeriodS = 0; /* Force immediate measurement */
			  settings.rightPage = 2; /* Go to runtime sub-page */

			  /* Enable power to logger */
			  LL_GPIO_ResetOutputPin(UART1_3V3out_GPIO_Port, UART1_3V3out_Pin); /* P-MOS so inverted logic! */

			  /* Set waiting-time */
			  settings.msWaiting = STARTUP_DELAY_UART_MODULE_MS;
			  settings.msWaitingStart = HAL_GetTick();
		  }
		  else if (((HAL_GetTick() - settings.msWaitingStart) >= settings.msWaiting) || settings.loggerReady)
		  {
			  /* Reset values */
			  initDataStruct();
			  convertValues();

			  displaySaveIcon();
			  writeHeader();

			  /* Reset waiting functionality */
			  settings.msWaiting = 0;
			  settings.msWaitingStart = 0;

			  settings.loggerReady = 1; /* If we got here by timeout make sure the runtime logic will still work */
			  settings.headerSaved = 1;
		  }
	  }
	  /* Running, header already saved, amount of seconds necessary reached */
	  else if ((settings.mode == 1) && settings.headerSaved && (settings.remMeasPeriodS == 0))
	  {
		  settings.remMeasPeriodS = LUT_period_s[settings.measPeriodIndex];

		  displaySaveIcon();
		  writeMeasurements();

	  }

	  updateLeftDisplay();
	  updateRightDisplay();
	  finishDisplayUpdates();

	  /* Insert millisecond delay */
//	  SEGGER_RTT_printf(0, "Loop ");
//	  LL_mDelay(250);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_PWR_EnableBkUpAccess();
  LL_RCC_LSE_Enable();

   /* Wait till LSE is ready */
  while(LL_RCC_LSE_IsReady() != 1)
  {

  }
  if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
  }
  LL_RCC_EnableRTC();
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_SetSystemCoreClock(8000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_2);
}

/* USER CODE BEGIN 4 */


/**************************************************************************//**
 * @brief
 *   Function to handle switch presses.
 *****************************************************************************/
void checkSwitches(void)
{
	/* UP */
	if (getSW0())
	{
		if ((settings.mode == 0) && !(settings.headerSaved) && (settings.changeDateTime == 0))
		{
			settings.mode = 1;
			settings.newMode = 1; /* Display needs updating */
		}
		else if (settings.mode == 1)
		{
			settings.mode = 0;
			settings.newMode = 1; /* Display needs updating */
		}

		setSW0(0); /* Interrupt handled */
	}

	/* DOWN */
	if (getSW1())
	{
		if (settings.selectedDisplay == 0) settings.selectedDisplay = 1;
		else if (settings.selectedDisplay == 1) settings.selectedDisplay = 0;

		settings.newSelDisplay = 1; /* Display needs updating */

		setSW1(0); /* Interrupt handled */
	}

	/* Encoder press */
	if (getENCkey())
	{
		/* Only change when not running */
		if (settings.mode == 0)
		{
			/* Reset value on selected LEFT page */
			if ((settings.selectedDisplay == 0) && (settings.leftPage == 0))
			{
				data.firstVolt  = 1;
				data.minVoltage = 0.0;
				data.newMinVolt = 1;
				data.maxVoltage = 0.0;
				data.newMaxVolt = 1;
			}
			else if ((settings.selectedDisplay == 0) && (settings.leftPage == 1))
			{
				data.firstCurr  = 1;
				data.minCurrent = 0.0;
				data.newMinCurr = 1;
				data.maxCurrent = 0.0;
				data.newMaxCurr = 1;
			}
			else if ((settings.selectedDisplay == 0) && (settings.leftPage == 2))
			{
				data.ah    = 0.0;
				data.newAh = 1;
				data.wh    = 0.0;
				data.newWh = 1;
			}

			/* Set values on selected RIGHT page */
			if ((settings.selectedDisplay == 1) && (settings.rightPage == 0))
			{
				if (settings.changeDateTime == 0)
				{
					settings.changeDateTime = 1; /* Start by changing day */
					settings.dateTimeChanged = 1; /* Force display update (a.o. underline) */
				}
				else if (settings.changeDateTime == 6) /* End by changing seconds */
				{
					settings.changeDateTime = 0;
					settings.dateTimeChanged = 1; /* Force display update (a.o. underline) */
					writeToRTC();
				}
				else if (settings.changeDateTime > 0)
				{
					settings.changeDateTime++;
					settings.dateTimeChanged = 1;
				}
			}
			else if ((settings.selectedDisplay == 1) && (settings.rightPage == 1))
			{
				/* Enable/disable period change on encoder turn */
				if (settings.changePeriod == 0)
				{
					settings.changePeriod = 1;
					settings.periodChanged = 1;
				}
				else if (settings.changePeriod == 1)
				{
					settings.changePeriod = 0;
					settings.periodChanged = 1;
				}
			}
			/* Directly change period on encoder press on runtime page */
			else if ((settings.selectedDisplay == 1) && (settings.rightPage == 2))
			{
				settings.rightPage = 1;
				settings.changePeriod = 1;
				settings.periodChanged = 1;
			}
		}

		setENCkey(0); /* Interrupt handled */
	}
}


/**************************************************************************//**
 * @brief
 *   Function to handle encoder rotation logic.
 *****************************************************************************/
void checkEncoder(void)
{
	int16_t steps = 0;
	uint16_t encValue = LL_TIM_GetCounter(TIM3);

	if (encValue != settings.oldTIM3)
	{
		/* Make sure we get a stable value */
		while ((encValue % 4) > 0) encValue++;

		/* Calculate steps */
		steps = encValue - settings.oldTIM3;
		steps /= 4;

		/* Logic for circular pages */
		if (steps > 0)
		{
			for (uint8_t counter = 0; counter < steps; counter++)
			{
				/* Rotate LEFT display pages (if selected) */
				if (settings.selectedDisplay == 0)
				{
					if (settings.leftPage < 2) settings.leftPage++;
					else settings.leftPage = 0;

					/* Indicate that a certain page needs to be updated */
					if (settings.leftPage == 0)
					{
						cData.newPow     = 1;
						cData.newMaxVolt = 1;
						cData.newMinVolt = 1;
					}
					else if (settings.leftPage == 1)
					{
						cData.newPow     = 1;
						cData.newMaxCurr = 1;
						cData.newMinCurr = 1;
					}
					else if (settings.leftPage == 2)
					{
						cData.newPow = 1;
						cData.newAh  = 1;
						cData.newWh  = 1;
					}
				}

				/* Rotate RIGHT display pages (if selected) */
				if (settings.selectedDisplay == 1)
				{
					/* Change period (if selected) */
					if (settings.changePeriod == 1)
					{
						if (settings.measPeriodIndex < (LUT_period_s_length - 1))
						{
							settings.measPeriodIndex++;
							settings.remMeasPeriodS = LUT_period_s[settings.measPeriodIndex];
							settings.measPeriodS = LUT_period_s[settings.measPeriodIndex];
							settings.periodChanged = 1;
						}
					}
					/* Change day (if selected) */
					else if (settings.changeDateTime == 1)
					{
						if ((rtc.latest == 0) && (rtc.day0 < 31)) rtc.day0++;
						else if ((rtc.latest == 1) && (rtc.day1 < 31)) rtc.day1++;

						settings.dateTimeChanged = 1;
					}
					/* Change month (if selected) */
					else if (settings.changeDateTime == 2)
					{
						if ((rtc.latest == 0) && (rtc.month0 < 12)) rtc.month0++;
						else if ((rtc.latest == 1) && (rtc.month1 < 12)) rtc.month1++;

						settings.dateTimeChanged = 1;
					}
					/* Change year (if selected) */
					else if (settings.changeDateTime == 3)
					{
						if (rtc.latest == 0) rtc.year0++;
						else if (rtc.latest == 1) rtc.year1++;

						settings.dateTimeChanged = 1;
					}
					/* Change hour (if selected) */
					else if (settings.changeDateTime == 4)
					{
						if ((rtc.latest == 0) && (rtc.hour0 < 23)) rtc.hour0++;
						else if ((rtc.latest == 1) && (rtc.hour1 < 23)) rtc.hour1++;

						settings.dateTimeChanged = 1;
					}
					/* Change minutes (if selected) */
					else if (settings.changeDateTime == 5)
					{
						if ((rtc.latest == 0) && (rtc.min0 < 59)) rtc.min0++;
						else if ((rtc.latest == 1) && (rtc.min1 < 59)) rtc.min1++;

						settings.dateTimeChanged = 1;
					}
					/* Change seconds (if selected) */
					else if (settings.changeDateTime == 6)
					{
						if ((rtc.latest == 0) && (rtc.sec0 < 59)) rtc.sec0++;
						else if ((rtc.latest == 1) && (rtc.sec1 < 59)) rtc.sec1++;

						settings.dateTimeChanged = 1;
					}
					else
					{
						/* Rotate right display pages (if selected) */
						if (settings.rightPage < 2) settings.rightPage++;
						else settings.rightPage = 0;

						/* Indicate that a certain page needs to be updated after switching between them */
						if (settings.rightPage == 0)
						{
							settings.dateTimeChanged = 1;
						}
						else if (settings.rightPage == 1)
						{
							settings.periodChanged = 1;
						}
						else if (settings.rightPage == 2)
						{
							cData.newRunHours = 1;
							cData.newRunMins = 1;
							cData.newRunSecs = 1;
						}
					}
				}
			}
		}
		else if (steps < 0)
		{
			for (int8_t counter = 0; counter > steps; counter--)
			{
				/* Rotate LEFT display pages (if selected) */
				if (settings.selectedDisplay == 0)
				{
					if (settings.leftPage > 0) settings.leftPage--;
					else settings.leftPage = 2;

					/* Indicate that a certain page needs to be updated */
					if (settings.leftPage == 0)
					{
						cData.newPow     = 1;
						cData.newMaxVolt = 1;
						cData.newMinVolt = 1;
					}
					else if (settings.leftPage == 1)
					{
						cData.newPow     = 1;
						cData.newMaxCurr = 1;
						cData.newMinCurr = 1;
					}
					else if (settings.leftPage == 2)
					{
						cData.newPow = 1;
						cData.newAh  = 1;
						cData.newWh  = 1;
					}
				}

				/* Rotate RIGHT display pages (if selected) */
				if (settings.selectedDisplay == 1)
				{
					/* Change period (if selected) */
					if (settings.changePeriod == 1)
					{
						if (settings.measPeriodIndex > 0)
						{
							settings.measPeriodIndex--;
							settings.remMeasPeriodS = LUT_period_s[settings.measPeriodIndex];
							settings.measPeriodS = LUT_period_s[settings.measPeriodIndex];
							settings.periodChanged = 1;
						}
					}
					/* Change day (if selected) */
					else if (settings.changeDateTime == 1)
					{
						if ((rtc.latest == 0) && (rtc.day0 > 1)) rtc.day0--;
						else if ((rtc.latest == 1) && (rtc.day1 > 1)) rtc.day1--;

						settings.dateTimeChanged = 1;
					}
					/* Change month (if selected) */
					else if (settings.changeDateTime == 2)
					{
						if ((rtc.latest == 0) && (rtc.month0 > 1)) rtc.month0--;
						else if ((rtc.latest == 1) && (rtc.month1 > 1)) rtc.month1--;

						settings.dateTimeChanged = 1;
					}
					/* Change year (if selected) */
					else if (settings.changeDateTime == 3)
					{
						if (rtc.latest == 0) rtc.year0--;
						else if (rtc.latest == 1) rtc.year1--;

						settings.dateTimeChanged = 1;
					}
					/* Change hour (if selected) */
					else if (settings.changeDateTime == 4)
					{
						if ((rtc.latest == 0) && (rtc.hour0 > 0)) rtc.hour0--;
						else if ((rtc.latest == 1) && (rtc.hour1 > 0)) rtc.hour1--;

						settings.dateTimeChanged = 1;
					}
					/* Change minutes (if selected) */
					else if (settings.changeDateTime == 5)
					{
						if ((rtc.latest == 0) && (rtc.min0 > 0)) rtc.min0--;
						else if ((rtc.latest == 1) && (rtc.min1 > 0)) rtc.min1--;

						settings.dateTimeChanged = 1;
					}
					/* Change seconds (if selected) */
					else if (settings.changeDateTime == 6)
					{
						if ((rtc.latest == 0) && (rtc.sec0 > 0)) rtc.sec0--;
						else if ((rtc.latest == 1) && (rtc.sec1 > 0)) rtc.sec1--;

						settings.dateTimeChanged = 1;
					}
					else
					{
						/* Rotate right display pages (if selected) */
						if (settings.rightPage > 0) settings.rightPage--;
						else settings.rightPage = 2;

						/* Indicate that a certain page needs to be updated */
						if (settings.rightPage == 0)
						{
							settings.dateTimeChanged = 1;
						}
						else if (settings.rightPage == 1)
						{
							settings.periodChanged = 1;
						}
						else if (settings.rightPage == 2)
						{
							cData.newRunHours = 1;
							cData.newRunMins = 1;
							cData.newRunSecs = 1;
						}
					}
				}
			}
		}

		/* Update field with new value */
		settings.oldTIM3 = encValue;
	}
}


/**************************************************************************//**
 * @brief
 *   Function to print the header of the logfile to indicate the columns.
 *
 * @details
 *   This function also prints debugging information using Segger RTT.
 *****************************************************************************/
void writeHeader(void)
{
	USART1_print("Date and Time [day/month/year hour:min:sec],Runtime [hour:min:sec],Voltage [V],Current [A],Power [W]\r\n");
	SEGGER_RTT_printf(0, "Date and Time [day/month/year hour:min:sec], Runtime [hour:min:sec], Voltage [V], Current [A], Power [W]\r\n");
}


/**************************************************************************//**
 * @brief
 *   Function to print the footer of the logfile (two lines).
 *
 * @details
 *   This function prints data which doesn't change every measurement. @n
 *   This function also prints debugging information using Segger RTT.
 *****************************************************************************/
void writeFooter(void)
{
	/* Print footer-header */
	USART1_print("Total runtime [hour:min:sec],Capacity [Ah],Capacity [Wh],Max Volt [V],Min Volt [V],Max Curr [A],Min Curr [A]\r\n");
	SEGGER_RTT_printf(0, "Total runtime [hour:min:sec], Capacity [Ah], Capacity [Wh], Max Volt [V], Min Volt [V], Max Curr [A], Min Curr [A]\r\n");

	/* Print RUNTIME */
	USART1_print(cData.charRunHours);
	USART1_print(":");
	USART1_print(cData.charRunMins);
	USART1_print(":");
	USART1_print(cData.charRunSecs);
	SEGGER_RTT_printf(0, "%s:%s:%s", cData.charRunHours, cData.charRunMins, cData.charRunSecs);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print CAPACITY Ah */
	USART1_print(cData.ahLeft);
	USART1_print(".");
	USART1_print(cData.ahRight);
	SEGGER_RTT_printf(0, "%s.%s Ah", cData.ahLeft, cData.ahRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print CAPACITY Wh */
	USART1_print(cData.whLeft);
	USART1_print(".");
	USART1_print(cData.whRight);
	SEGGER_RTT_printf(0, "%s.%s Wh", cData.whLeft, cData.whRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print MAX VOLTAGE */
	USART1_print(cData.vMaxLeft);
	USART1_print(".");
	USART1_print(cData.vMaxRight);
	SEGGER_RTT_printf(0, "%s.%s V", cData.vMaxLeft, cData.vMaxRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print MIN VOLTAGE */
	USART1_print(cData.vMinLeft);
	USART1_print(".");
	USART1_print(cData.vMinRight);
	SEGGER_RTT_printf(0, "%s.%s V", cData.vMinLeft, cData.vMinRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print MAX CURRENT */
	USART1_print(cData.aMaxLeft);
	USART1_print(".");
	USART1_print(cData.aMaxRight);
	SEGGER_RTT_printf(0, "%s.%s A", cData.aMaxLeft, cData.aMaxRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print MIN CURRENT */
	USART1_print(cData.aMinLeft);
	USART1_print(".");
	USART1_print(cData.aMinRight);
	SEGGER_RTT_printf(0, "%s.%s A", cData.aMinLeft, cData.aMinRight);

	/* Print spacing */
	USART1_print("\r\n");
	SEGGER_RTT_printf(0, "\r\n");
}


/**************************************************************************//**
 * @brief
 *   Function to print measurement data.
 *
 * @details
 *   This function also prints debugging information using Segger RTT.
 *****************************************************************************/
void writeMeasurements(void)
{
	/* Print DATE and TIME */
	USART1_print(rtc.charDay);
	USART1_print("/");
	USART1_print(rtc.charMonth);
	USART1_print("/");
	USART1_print(rtc.charYear);
	USART1_print(" ");
	USART1_print(rtc.charHour);
	USART1_print(":");
	USART1_print(rtc.charMin);
	USART1_print(":");
	USART1_print(rtc.charSec);
	SEGGER_RTT_printf(0, "%s/%s/%s %s:%s:%s", rtc.charDay, rtc.charMonth, rtc.charYear, rtc.charHour, rtc.charMin, rtc.charSec);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print RUNTIME */
	USART1_print(cData.charRunHours);
	USART1_print(":");
	USART1_print(cData.charRunMins);
	USART1_print(":");
	USART1_print(cData.charRunSecs);
	SEGGER_RTT_printf(0, "%s:%s:%s", cData.charRunHours, cData.charRunMins, cData.charRunSecs);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print VOLTAGE */
	USART1_print(cData.vLeft);
	USART1_print(".");
	USART1_print(cData.vRight);
	SEGGER_RTT_printf(0, "%s.%s V", cData.vLeft, cData.vRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print CURRENT */
	USART1_print(cData.aLeft);
	USART1_print(".");
	USART1_print(cData.aRight);
	SEGGER_RTT_printf(0, "%s.%s A", cData.aLeft, cData.aRight);

	/* Print spacing */
	USART1_print(",");
	SEGGER_RTT_printf(0, " ");


	/* Print POWER */
	USART1_print(cData.pLeft);
	USART1_print(".");
	USART1_print(cData.pRight);
	SEGGER_RTT_printf(0, "%s.%s W", cData.pLeft, cData.pRight);

	/* Print spacing */
	USART1_print("\r\n");
	SEGGER_RTT_printf(0, "\r\n");
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
