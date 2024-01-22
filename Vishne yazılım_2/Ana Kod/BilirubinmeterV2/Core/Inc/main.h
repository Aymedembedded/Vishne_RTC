/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "includes.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern I2C_HandleTypeDef hi2c2;

extern RTC_HandleTypeDef hrtc;

extern SDADC_HandleTypeDef hsdadc2;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern TIM_HandleTypeDef htim6;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
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
void Joystick_demo (void);
void Touchscreen_demo (void);
void LCD_demo (void);
void MEMS_demo (void);
void Log_demo(void);

void SD_demo (void);
void Touchscreen_Calibration (void);
uint16_t Calibration_GetX(uint16_t x);
uint16_t Calibration_GetY(uint16_t y);
uint8_t IsCalibrationDone(void);
uint8_t CheckForUserInput(void);
void Toggle_Leds(void);
void getAllTests(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STANDBY_Pin GPIO_PIN_3
#define STANDBY_GPIO_Port GPIOE
#define CHARGE_Pin GPIO_PIN_4
#define CHARGE_GPIO_Port GPIOE
#define PB_OUT_Pin GPIO_PIN_6
#define PB_OUT_GPIO_Port GPIOE
#define PS_HOLD_Pin GPIO_PIN_9
#define PS_HOLD_GPIO_Port GPIOF
#define OPTC_SENS_Pin GPIO_PIN_10
#define OPTC_SENS_GPIO_Port GPIOF
#define OPTC_SENS_EXTI_IRQn EXTI15_10_IRQn
#define LEDR_Pin GPIO_PIN_0
#define LEDR_GPIO_Port GPIOC
#define LEDG_Pin GPIO_PIN_1
#define LEDG_GPIO_Port GPIOC
#define BUTTON_Pin GPIO_PIN_2
#define BUTTON_GPIO_Port GPIOF
#define BUTTON_EXTI_IRQn EXTI2_TSC_IRQn
#define BAT_LEV_Pin GPIO_PIN_0
#define BAT_LEV_GPIO_Port GPIOA
#define BEEPER_Pin GPIO_PIN_5
#define BEEPER_GPIO_Port GPIOA
#define LED2_FLT_Pin GPIO_PIN_7
#define LED2_FLT_GPIO_Port GPIOA
#define LED3_FLT_Pin GPIO_PIN_4
#define LED3_FLT_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_1
#define LED3_GPIO_Port GPIOB
#define VIDEO_Pin GPIO_PIN_7
#define VIDEO_GPIO_Port GPIOE
#define LCD_DC_Pin GPIO_PIN_14
#define LCD_DC_GPIO_Port GPIOE
#define LCD_RST_Pin GPIO_PIN_15
#define LCD_RST_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOD
#define FLASH_CS_Pin GPIO_PIN_6
#define FLASH_CS_GPIO_Port GPIOC
#define TP_INT1_Pin GPIO_PIN_8
#define TP_INT1_GPIO_Port GPIOA
#define TP_INT1_EXTI_IRQn EXTI9_5_IRQn
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOA
#define TFT_ON_Pin GPIO_PIN_15
#define TFT_ON_GPIO_Port GPIOA
#define LED1_FLT_Pin GPIO_PIN_10
#define LED1_FLT_GPIO_Port GPIOC
#define BR_FLASH_Pin GPIO_PIN_11
#define BR_FLASH_GPIO_Port GPIOC
#define BR_PWR_Pin GPIO_PIN_12
#define BR_PWR_GPIO_Port GPIOC
#define BR_BPR_Pin GPIO_PIN_0
#define BR_BPR_GPIO_Port GPIOD
#define BR_DLED_Pin GPIO_PIN_1
#define BR_DLED_GPIO_Port GPIOD
#define BR_WAKE_Pin GPIO_PIN_2
#define BR_WAKE_GPIO_Port GPIOD
#define BR_TRIG_Pin GPIO_PIN_7
#define BR_TRIG_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOB
#define SPEC_START_Pin GPIO_PIN_5
#define SPEC_START_GPIO_Port GPIOB
#define SPEC_CLK_Pin GPIO_PIN_6
#define SPEC_CLK_GPIO_Port GPIOB
#define SPEC_EOS_Pin GPIO_PIN_7
#define SPEC_EOS_GPIO_Port GPIOB
#define SPEC_GAIN_Pin GPIO_PIN_0
#define SPEC_GAIN_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
