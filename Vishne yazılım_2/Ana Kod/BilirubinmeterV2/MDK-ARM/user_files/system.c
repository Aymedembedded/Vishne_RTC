/* Includes ------------------------------------------------------------------*/
#include "system.h"
#include "testimg.h"
/* Defines ------------------------------------------------------------------*/
void movingAvarage(void);
extern uint16_t movAvData[256];

 uint8_t rx_buff[20];
 uint32_t battery1Val;
 uint8_t battState=0;
 uint8_t BtCounter=0;
 uint8_t PowerState;
 uint32_t sleepCounter = 0;
 
void BuzzerBip(void)
{
		for(int i=0; i<40;i++){
		BEEP_ON
		DWT_Delay_us (200);	
		BEEP_OFF
		DWT_Delay_us (200);
		}
}


/********************* integer to string *************************/
int i2a(char *s, int n){
    div_t qr;
    int pos;

    if(n == 0) return 0;

    qr = div(n, 10);
    pos = i2a(s, qr.quot);
    s[pos] = qr.rem + '0';
    return pos + 1;
}

char* my_itoa(char *output_buff, int num){
    char *p = output_buff;
    if(num < 0){
        *p++ = '-';
        num *= -1;
    } else if(num == 0)
        *p++ = '0';
    p[i2a(p, num)]='\0';
    return output_buff;
}



/********************* external interrupt *************************/
// optik sensor aktif oldugunda ölçüm islemi yapilir.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	DWT_Delay_us(300000);
	if (PowerState == PowerST_ON)
	{
	
  if(GPIO_Pin == GPIO_PIN_10) 
  {
			if (displayState == MainScreen) 
			{

			}
			else if (displayState == TestCalScreen) 
			{
				LED_ON
				DWT_Delay_us(4000);
				readSpectrometer();
				LED_OFF
				BilCalculation();
				testIntroDisplay();
				HAL_Delay(100);
			}	
			else if (displayState == IntroTestScreen || displayState == BackToTheEndOfTestScreen) 
			{

				BilResult[0] = NULL; 
				LED_ON
				DWT_Delay_us(10000);
				readSpectrometer();
				DWT_Delay_us(10000);
				LED_OFF
				BuzzerBip();
				BilCalculation();
				//testScreenDisplay();
				if(BilResult[0]/17.10000063270002f < 20.0f)
				{
					testScreenDisplay();
					HAL_Delay(100);
				}
				else
				{
				 ErrorDisplay3();
				 HAL_Delay(2500);
				 mainScreenDisplay ();
				 HAL_Delay(100);
				}
				//ErrorDisplay3();
			}	
			else if (displayState == CalScreen2) 
			{
				LED_OFF
				DWT_Delay_us(10000);
				readSpectrometer();
				LED_OFF
				BuzzerBip();
				displayState = CalScreen22;
			}	
			else if (displayState == CalScreen3) 
			{
				LED_ON
				DWT_Delay_us(10000);
				readSpectrometer();
				DWT_Delay_us(10000);
				LED_OFF
				BuzzerBip();
				displayState = CalScreen33;
			}	
			DWT_Delay_us(100000);

			LED_OFF

			
			HAL_UART_Transmit_IT(&huart3,(uint8_t*)VIDEO_DATA,512);
  }

	
	if(GPIO_Pin == BUTTON_Pin){
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,0);
		for(uint32_t i=0;i<10000000;i++){}
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1);
		
		}
	}
}




/********************* System Init*************************/


void SysInit(void)
	{
		PowerState = PowerST_ON;
		/* Uart init */
		__HAL_UART_ENABLE_IT(&huart3,UART_IT_TC);
		HAL_UART_Receive_DMA(&huart2,rx_buff,13);
		//Barcode_Init();
		//HAL_Delay(150);
		LCD_ON
			/* flash init */
		W25qxx_Init();
		
		/* SDADC IT  init */
		HAL_SDADC_InjectedStart_IT(&hsdadc2); 
		/* microsecond init */
		DWT_Delay_Init ();
		/* spectrometer init */
		C12666MA_Init();
		readSpectrometer();
		
		/* ILI9341 init */
		ILI9341_Unselect();
		ILI9341_Init();

		ILI9341_FillScreen(ILI9341_BLUE);
		ILI9341_DrawImage(0, 0, 240, 65, (const uint16_t*)image_data_aymedLogo);
		//Init_Calender();
		
		mainScreenDisplay();
		HAL_Delay(100);
		
	
//		HAL_UART_RxCpltCallback(&huart2);

		
		/* touchscreen init */
		Touchscreen_demo();
		
	}

/********************* Get battery Level	*************************/
void batteryLevel(void){
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,100);
		battery1Val=HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);

	HAL_GPIO_ReadPin(CHARGE_GPIO_Port,CHARGE_Pin);
	
	// sarja takili ise pil seviyesinin ekrana bastirilmasi
	if (HAL_GPIO_ReadPin(CHARGE_GPIO_Port,CHARGE_Pin) == 0){
		if (battery1Val > 3331 && battery1Val < 4096 && battState != 11 ){
			battState=11;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_GREEN);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_GREEN);
		}
		else if(battery1Val > 3211 && battery1Val < 3330 && battState != 12){
			battState = 12;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_GREEN);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_GREEN);
			ILI9341_FillRectangle(215,74,4,8,ILI9341_COLOR565(66, 66, 69));
		}
		else if(battery1Val > 3091 && battery1Val < 3210 && battState != 13){
			battState = 13;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_GREEN);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_GREEN);
			ILI9341_FillRectangle(215,74,8,8,ILI9341_COLOR565(66, 66, 69));
		}
		else if(battery1Val > 2970 && battery1Val < 3090 && battState != 14){
			battState = 14;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_GREEN);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_GREEN);
			ILI9341_FillRectangle(215,74,12,8,ILI9341_COLOR565(66, 66, 69));
		}
		else if(battery1Val > 0 && battery1Val < 3042 && battState != 15){
			battState = 15;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_GREEN);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_GREEN);
			ILI9341_FillRectangle(215,74,18,8,ILI9341_COLOR565(66, 66, 69));
		}			
	}
	
	// sarja takili degil ise pil seviyesinin ekrana bastirilmasi
	else	{
		if (battery1Val > 3331 && battery1Val < 4096 && battState != 21 ){
			battState=21;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(213,72,22,12,ILI9341_COLOR565(180, 180, 180));
		}
		else if(battery1Val > 3211 && battery1Val < 3330 && battState != 22){
			battState = 22;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(213,72,22,12,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(215,74,4,8,ILI9341_COLOR565(66, 66, 69));
		}
		else if(battery1Val > 3091 && battery1Val < 3210 && battState != 23){
			battState = 23;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(213,72,22,12,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(215,74,8,8,ILI9341_COLOR565(66, 66, 69));
		}
		else if(battery1Val > 2970 && battery1Val < 3090 && battState != 24){
			battState = 24;
			ILI9341_FillRectangle(210,76,25,4,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(213,72,22,12,ILI9341_COLOR565(180, 180, 180));
			ILI9341_FillRectangle(215,74,12,8,ILI9341_COLOR565(66, 66, 69));
		}	
			else if(battery1Val > 0 && battery1Val < 3042 && battState != 25){
			battState = 25;
//			BuzzerBip();
//			HAL_Delay(200);
//			BuzzerBip();
//			HAL_Delay(500);
//			BuzzerBip();
//			HAL_Delay(200);
//			BuzzerBip();
			ILI9341_FillRectangle(210,76,25,4,ILI9341_RED);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_RED);
			ILI9341_FillRectangle(215,74,18,8,ILI9341_COLOR565(66, 66, 69));
		}	
	}
}

/********************* Check Push Button*************************/
void CheckPushBt(void){
	HAL_GPIO_ReadPin(BUTTON_GPIO_Port,BUTTON_Pin);
	sleepCounter++;
	if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port,BUTTON_Pin) == 0){ //butona basilip basilmadigi kontrol ediliyor
		BtCounter++;
		if (BtCounter == 30 && PowerState == PowerST_ON){

						BuzzerBip();
						HAL_Delay(500);
						BuzzerBip();
						HAL_Delay(500);
						BuzzerBip();
						HAL_Delay(500);
						POWER_OFF
						PowerState = PowerST_OFF;		
							
						LCD_OFF
						HAL_Delay(500);
						NVIC_SystemReset();	
		}
			
	}
	else{
		BtCounter = 0;
	}
		if((sleepCounter>800) && (PowerState == PowerST_ON)){	//800 = 56sn
		POWER_OFF
		PowerState = PowerST_OFF;	
		LCD_OFF
		HAL_Delay(500);
		NVIC_SystemReset();
	}
}
	
void sleepCounterReset(void){
	sleepCounter = 0;
}


