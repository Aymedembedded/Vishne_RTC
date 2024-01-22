#include "barcode.h"
#include "serialwrite.h"

void Barcode_Init(void)
	{
			HAL_GPIO_WritePin(BR_WAKE_GPIO_Port,BR_WAKE_Pin,1);
			HAL_GPIO_WritePin(BR_TRIG_GPIO_Port,BR_TRIG_Pin,1);
			HAL_GPIO_WritePin(BR_FLASH_GPIO_Port,BR_FLASH_Pin,1);	
	/*		
			char str[] = {'\0'};
			sprintf(str,"%s","0A80040000062000FFFFFD4E");
			sprintf(str,"%01x",2000);
			HAL_UART_Transmit_IT(&huart3, str, sizeof(str));
			HAL_UART_Transmit_IT(&huart2, str, sizeof(str));
			HAL_Delay(20);
			sprintf(str,"%02x",2000);
			HAL_UART_Transmit_IT(&huart3, str, sizeof(str));
			HAL_UART_Transmit_IT(&huart2, str, sizeof(str));
			HAL_Delay(20);
			sprintf(str,"%s","0A");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","80");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","04");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","00");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","00");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","06");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","20");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","00");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","FF");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","FF");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","FD");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","4E");
			HAL_UART_Transmit_IT(&huart3, str, 2);
			HAL_UART_Transmit_IT(&huart2, str, 2);
			HAL_Delay(10);
			sprintf(str,"%s","0C8000000008200000F000F0FD6C");
			HAL_UART_Transmit_IT(&huart3, str, 28);
			HAL_UART_Transmit_IT(&huart2, str, 28);
			HAL_Delay(10000);*/
	}


void readBarcode(void)
	{
/*		uint8_t str[35] = {'\0'};
		HAL_Delay(100);
		HAL_GPIO_WritePin(BR_TRIG_GPIO_Port,BR_TRIG_Pin,0);
		HAL_Delay(100);
		sprintf(str, "Value of Pi = %f", 3);
		HAL_UART_Transmit(&huart3, str, sizeof(str), 100);
*/		
		HAL_GPIO_WritePin(BR_TRIG_GPIO_Port,BR_TRIG_Pin,0);
		for(uint32_t i=0 ; i<10000000 ; i++){};
		HAL_GPIO_WritePin(BR_TRIG_GPIO_Port,BR_TRIG_Pin,1);
		
	}

	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{

		BuzzerBip();
		testIntroDisplay();
		ILI9341_WriteString(60, 215,(char *)rx_buff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
			for(int id=0;id<13;id++)
	{
		patientFr.patient.id[id]=rx_buff[id];
	}
	}