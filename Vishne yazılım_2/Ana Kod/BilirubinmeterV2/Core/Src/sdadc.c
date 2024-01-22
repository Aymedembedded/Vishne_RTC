/**
  ******************************************************************************
  * File Name          : SDADC.c
  * Description        : This file provides code for the configuration
  *                      of the SDADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "sdadc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SDADC_HandleTypeDef hsdadc2;

/* SDADC2 init function */
void MX_SDADC2_Init(void)
{
  SDADC_ConfParamTypeDef ConfParamStruct = {0};

  /** Configure the SDADC low power mode, fast conversion mode,
  slow clock mode and SDADC1 reference voltage 
  */
  hsdadc2.Instance = SDADC2;
  hsdadc2.Init.IdleLowPowerMode = SDADC_LOWPOWER_NONE;
  hsdadc2.Init.FastConversionMode = SDADC_FAST_CONV_DISABLE;
  hsdadc2.Init.SlowClockMode = SDADC_SLOW_CLOCK_DISABLE;
  hsdadc2.Init.ReferenceVoltage = SDADC_VREF_EXT;
  hsdadc2.InjectedTrigger = SDADC_SOFTWARE_TRIGGER;
  if (HAL_SDADC_Init(&hsdadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Injected Mode 
  */
  if (HAL_SDADC_SelectInjectedDelay(&hsdadc2, SDADC_INJECTED_DELAY_NONE) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_SDADC_SelectInjectedTrigger(&hsdadc2, SDADC_SOFTWARE_TRIGGER) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_SDADC_InjectedConfigChannel(&hsdadc2, SDADC_CHANNEL_5, SDADC_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  /** Set parameters for SDADC configuration 0 Register 
  */
  ConfParamStruct.InputMode = SDADC_INPUT_MODE_SE_ZERO_REFERENCE;
  ConfParamStruct.Gain = SDADC_GAIN_1;
  ConfParamStruct.CommonMode = SDADC_COMMON_MODE_VSSA;
  ConfParamStruct.Offset = 0;
  if (HAL_SDADC_PrepareChannelConfig(&hsdadc2, SDADC_CONF_INDEX_0, &ConfParamStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Injected Channel 
  */
  if (HAL_SDADC_AssociateChannelConfig(&hsdadc2, SDADC_CHANNEL_5, SDADC_CONF_INDEX_0) != HAL_OK)
  {
    Error_Handler();
  }
		 /* USER CODE BEGIN SDADC2_Init 2 */
  /* Start Calibration in polling mode */
  if (HAL_SDADC_CalibrationStart(&hsdadc2, SDADC_CALIBRATION_SEQ_1) != HAL_OK)
  {
    /* An error occurs during the starting phase of the calibration */
    Error_Handler();
  }

  /* Pool for the end of calibration */
  if (HAL_SDADC_PollForCalibEvent(&hsdadc2, HAL_MAX_DELAY) != HAL_OK)
  {
    /* An error occurs while waiting for the end of the calibration */
    Error_Handler();
  }
  /* USER CODE END SDADC2_Init 2 */
}

void HAL_SDADC_MspInit(SDADC_HandleTypeDef* sdadcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(sdadcHandle->Instance==SDADC2)
  {
  /* USER CODE BEGIN SDADC2_MspInit 0 */

  /* USER CODE END SDADC2_MspInit 0 */
    /* SDADC2 clock enable */
    __HAL_RCC_SDADC2_CLK_ENABLE();
  
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**SDADC2 GPIO Configuration    
    PE7     ------> SDADC2_AIN5P 
    */
    GPIO_InitStruct.Pin = VIDEO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(VIDEO_GPIO_Port, &GPIO_InitStruct);

    /* SDADC2 interrupt Init */
    HAL_NVIC_SetPriority(SDADC2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SDADC2_IRQn);
  /* USER CODE BEGIN SDADC2_MspInit 1 */

  /* USER CODE END SDADC2_MspInit 1 */
  }
}

void HAL_SDADC_MspDeInit(SDADC_HandleTypeDef* sdadcHandle)
{

  if(sdadcHandle->Instance==SDADC2)
  {
  /* USER CODE BEGIN SDADC2_MspDeInit 0 */

  /* USER CODE END SDADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDADC2_CLK_DISABLE();
  
    /**SDADC2 GPIO Configuration    
    PE7     ------> SDADC2_AIN5P 
    */
    HAL_GPIO_DeInit(VIDEO_GPIO_Port, VIDEO_Pin);

    /* SDADC2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDADC2_IRQn);
  /* USER CODE BEGIN SDADC2_MspDeInit 1 */

  /* USER CODE END SDADC2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
