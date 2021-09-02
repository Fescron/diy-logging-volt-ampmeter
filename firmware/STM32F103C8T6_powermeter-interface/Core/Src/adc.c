/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

// TODO Got example from https://github.com/STMicroelectronics/STM32CubeF1/tree/master/Projects/STM32F103RB-Nucleo/Examples_LL/ADC/ADC_SingleConversion_TriggerSW_IT

#include "SEGGER_RTT.h"
#include "util.h"
#include "conversion.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Definitions of ADC hardware constraints delays */
/* Note: Only ADC IP HW delays are defined in ADC LL driver driver,           */
/*       not timeout values:                                                  */
/*       Timeout values for ADC operations are dependent to device clock      */
/*       configuration (system clock versus ADC clock),                       */
/*       and therefore must be defined in user application.                   */
/*       Refer to @ref ADC_LL_EC_HW_DELAYS for description of ADC timeout     */
/*       values definition.                                                   */

  /* Timeout values for ADC operations. */
  /* (enable settling time, disable settling time, ...)                       */
  /* Values defined to be higher than worst cases: low clock frequency,       */
  /* maximum prescalers.                                                      */
  /* Example of profile very low frequency : ADC clock frequency 12MHz        */
  /* prescaler 6, sampling time 1.5 ADC clock cycles, resolution 12 bits.     */
  /*  - ADC enable time: maximum delay is 1 us                                */
  /*    (refer to device datasheet, parameter "tSTAB")                        */
  /*  - ADC disable time: maximum delay should be a few ADC clock cycles      */
  /*  - ADC stop conversion time: maximum delay should be a few ADC clock     */
  /*    cycles                                                                */
  /*  - ADC conversion time: with this hypothesis of clock settings, maximum  */
  /*    delay will be 7us.                                                   */
  /*    (refer to device reference manual, section "Timing")                  */
  /* Unit: ms                                                                 */
  #define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t)   1)
  #define ADC_ENABLE_TIMEOUT_MS            ((uint32_t)   1)
  #define ADC_DISABLE_TIMEOUT_MS           ((uint32_t)   1)
  #define ADC_STOP_CONVERSION_TIMEOUT_MS   ((uint32_t)   1)
  #define ADC_CONVERSION_TIMEOUT_MS        ((uint32_t)   2)

  /* Delay between ADC enable and ADC end of calibration.                     */
  /* Delay estimation in CPU cycles: Case of ADC calibration done             */
  /* immediately after ADC enable, ADC clock setting slow                     */
  /* (LL_ADC_CLOCK_ASYNC_DIV32). Use a higher delay if ratio                  */
  /* (CPU clock / ADC clock) is above 32.                                     */
  #define ADC_DELAY_ENABLE_CALIB_CPU_CYCLES  (LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES * 32)


/* Definitions of environment analog values */
  /* Value of analog reference voltage (Vref+), connected to analog voltage   */
  /* supply Vdda (unit: mV).                                                  */
  #define VDDA_APPLI                       ((uint32_t)3300)

/* Definitions of data related to this example */
  /* Init variable out of expected ADC conversion data range */
  #define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Value to add to the converted ADC voltage as a sort of calibration */
static const float adcVoltReadoutCalbration = 0.03;

/* Variables for ADC conversion data */
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE; /* ADC group regular conversion data */

/* Variables for ADC conversion data computation to physical values */
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;  /* Value of voltage calculated from ADC conversion data (unit: mV) */

/* Variable to report status of ADC group regular unitary conversion          */
/*  0: ADC group regular unitary conversion is not completed                  */
/*  1: ADC group regular unitary conversion is completed                      */
/*  2: ADC group regular unitary conversion has not been started yet          */
/*     (initial state)                                                        */
__IO uint8_t ubAdcGrpRegularUnitaryConvStatus = 2; /* Variable set into ADC interruption callback */


/* USER CODE END 0 */

/* ADC1 init function */
void MX_ADC1_Init(void)
{
	LL_ADC_InitTypeDef ADC_InitStruct = {0};
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	/* ADC1 interrupt Init */
	NVIC_SetPriority(ADC1_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(ADC1_2_IRQn);

	/** Common config
	*/
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
	LL_ADC_Init(ADC1, &ADC_InitStruct);
	ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
	LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	/** Configure Regular Channel
	*/
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_TEMPSENSOR);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR);
}


/* ADC2 init function */
void MX_ADC2_Init(void)
{
	LL_ADC_InitTypeDef ADC_InitStruct = {0};
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	/**ADC2 GPIO Configuration
	PB0   ------> ADC2_IN8
	*/
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* ADC2 interrupt Init */
	NVIC_SetPriority(ADC1_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(ADC1_2_IRQn);

	/** Common config
	*/
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
	LL_ADC_Init(ADC2, &ADC_InitStruct);
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	LL_ADC_REG_Init(ADC2, &ADC_REG_InitStruct);
	/** Configure Regular Channel
	*/
	LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_8);
	LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_1CYCLE_5);
}

/* USER CODE BEGIN 1 */

/**
  * @brief  Perform ADC activation procedure to make it ready to convert
  *         (ADC instance: ADC2).
  * @note   Operations:
  *         - ADC instance
  *           - Run ADC self calibration
  *           - Enable ADC
  *         - ADC group regular
  *           none: ADC conversion start-stop to be performed
  *                 after this function
  *         - ADC group injected
  *           none: ADC conversion start-stop to be performed
  *                 after this function
  * @param  None
  * @retval None
  */
void Activate_ADC(void)
{
	/* Increase sampling time */
	LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_28CYCLES_5);

	/* Enable interruption ADC group regular end of unitary conversion */
	LL_ADC_EnableIT_EOS(ADC2);


	/* Logic discribe in the note now follows */
	__IO uint32_t wait_loop_index = 0;

	uint32_t Timeout = 0; /* Variable used for timeout management */

	/*## Operation on ADC hierarchical scope: ADC instance #####################*/

	/* Note: Hardware constraint (refer to description of the functions         */
	/*       below):                                                            */
	/*       On this STM32 serie, setting of these features are not             */
	/*       conditioned to ADC state.                                          */
	/*       However, in order to be compliant with other STM32 series          */
	/*       and to show the best practice usages, ADC state is checked.        */
	/*       Software can be optimized by removing some of these checks, if     */
	/*       they are not relevant considering previous settings and actions    */
	/*       in user application.                                               */
	if (LL_ADC_IsEnabled(ADC2) == 0)
	{
		/* Enable ADC */
		LL_ADC_Enable(ADC2);

		/* Delay between ADC enable and ADC start of calibration.                 */
		/* Note: Variable divided by 2 to compensate partially                    */
		/*       CPU processing cycles (depends on compilation optimization).     */
		wait_loop_index = (ADC_DELAY_ENABLE_CALIB_CPU_CYCLES >> 1);
		while (wait_loop_index != 0) wait_loop_index--;

		/* Run ADC self calibration */
		LL_ADC_StartCalibration(ADC2);

		/* Poll for ADC effectively calibrated */
		Timeout = ADC_CALIBRATION_TIMEOUT_MS;

		while (LL_ADC_IsCalibrationOnGoing(ADC2) != 0)
		{
			/* Check Systick counter flag to decrement the time-out value */
			if (LL_SYSTICK_IsActiveCounterFlag())
			{
				if (Timeout-- == 0) while (1); /* Time-out occurred */
			}
		}
	}

  /*## Operation on ADC hierarchical scope: ADC group regular ################*/
  /* Note: No operation on ADC group regular performed here.                  */
  /*       ADC group regular conversions to be performed after this function  */
  /*       using function:                                                    */
  /*       "LL_ADC_REG_StartConversion();"                                    */

  /*## Operation on ADC hierarchical scope: ADC group injected ###############*/
  /* Note: No operation on ADC group injected performed here.                 */
  /*       ADC group injected conversions to be performed after this function */
  /*       using function:                                                    */
  /*       "LL_ADC_INJ_StartConversion();"                                    */

}


void startBattVoltMeasurement(void)
{
	/* Reset status variable of ADC group regular unitary conversion before     */
	/* performing a new ADC group regular conversion start.                     */
	/* Note: Optionally, for this example purpose, check ADC unitary            */
	/*       conversion status before starting another ADC conversion.          */

	if (ubAdcGrpRegularUnitaryConvStatus != 0)
	{
		ubAdcGrpRegularUnitaryConvStatus = 0;
	}
	else
	{
		/* Error: Previous action (ADC conversion or DMA transfer) not yet        */
		/* completed.                                                             */
		while (1);
	}

	/* Init variable containing ADC conversion data */
	uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;

	/* Start ADC group regular conversion */
	/* Note: Hardware constraint (refer to description of the functions         */
	/*       below):                                                            */
	/*       On this STM32 serie, setting of these features are not             */
	/*       conditioned to ADC state.                                          */
	/*       However, in order to be compliant with other STM32 series          */
	/*       and to show the best practice usages, ADC state is checked.        */
	/*       Software can be optimized by removing some of these checks, if     */
	/*       they are not relevant considering previous settings and actions    */
	/*       in user application.                                               */
	if (LL_ADC_IsEnabled(ADC2) == 1) LL_ADC_REG_StartConversionSWStart(ADC2);
	else
	{
		/* Error: ADC conversion start could not be performed */
		while(1);
	}

}


/**
  * @brief  ADC group regular end of unitary conversion interruption callback
  * @note   This function is executed when the ADC group regular
  *         sequencer has converted one rank of the sequence.
  *         Therefore, this function is executed as many times as number
  *         of ranks in the sequence.
  * @retval None
  */
void AdcGrpRegularUnitaryConvComplete_Callback(void)
{
	/* Retrieve ADC conversion data */
	/* (data maximum amplitude corresponds to ADC resolution: 12 bits) */
	uhADCxConvertedData = LL_ADC_REG_ReadConversionData12(ADC2);

	/* Computation of ADC conversions raw data to physical values               */
	/* using LL ADC driver helper macro.                                        */
	uhADCxConvertedData_Voltage_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, uhADCxConvertedData, LL_ADC_RESOLUTION_12B);

	/* Update status variable of ADC unitary conversion */
	ubAdcGrpRegularUnitaryConvStatus = 1;

	/* Calculate real voltage */
	settings.vbat = ((uhADCxConvertedData_Voltage_mVolt * 0.001) * 3.2) / 2.2; /* Voltage divider of 1kohm and 2.2kohm */

	/* Read voltage tends to be 0.03V lower so add this value manually (~calibration) */
	settings.vbat += adcVoltReadoutCalbration;

//	SEGGER_RTT_printf(0, "ADC = %u mV vbat = %u mV\n\r", uhADCxConvertedData_Voltage_mVolt, (uint16_t)(settings.vbat * 1000));

	/* Signal logic that the battery voltage needs to be converted */
	settings.newVbat = 1;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
