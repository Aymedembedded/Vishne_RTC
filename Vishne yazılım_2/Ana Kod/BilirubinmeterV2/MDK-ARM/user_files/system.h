#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PowerST_ON   11
#define PowerST_OFF   12
# define 	LED_ON 			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
# define 	LED_OFF 		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
# define  BEEP_ON			HAL_GPIO_WritePin(BEEPER_GPIO_Port,BEEPER_Pin,GPIO_PIN_SET);
#define		BEEP_OFF	HAL_GPIO_WritePin(BEEPER_GPIO_Port,BEEPER_Pin,GPIO_PIN_RESET);

#define LCD_ON HAL_GPIO_WritePin(TFT_ON_GPIO_Port,TFT_ON_Pin,GPIO_PIN_SET);
#define LCD_OFF HAL_GPIO_WritePin(TFT_ON_GPIO_Port,TFT_ON_Pin,GPIO_PIN_RESET);

#define POWER_ON 	HAL_GPIO_WritePin(PS_HOLD_GPIO_Port,PS_HOLD_Pin,GPIO_PIN_SET);
#define POWER_OFF 	HAL_GPIO_WritePin(PS_HOLD_GPIO_Port,PS_HOLD_Pin,GPIO_PIN_RESET);
extern uint8_t rx_buff[20];
extern uint32_t battery1Val;
extern uint8_t PowerState;


void BuzzerBip(void);
char* my_itoa(char *output_buff, int num);
void SysInit(void);
void BilCalculation(void);//calibration header kismina alinacak
void batteryLevel(void);
void CheckPushBt(void);
void sleepCounterReset(void);
#endif // __SYSTEM_H__

