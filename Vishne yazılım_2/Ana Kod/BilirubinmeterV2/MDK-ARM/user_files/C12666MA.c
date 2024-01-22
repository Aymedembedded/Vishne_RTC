#include "C12666MA.h"
#define SPEC_CHANNELS		256
__IO uint32_t Video_data;
__IO uint16_t C12666MA_VIDEO=0;
__IO int16_t InjectedConvData = 0;
__IO uint32_t InjChannel = 0;
uint16_t VIDEO_DATA[ SPEC_CHANNELS];

extern SDADC_HandleTypeDef hsdadc2;

void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef *hsdadc);

void HAL_SDADC_InjectedConvCpltCallback(SDADC_HandleTypeDef* hsdadc)
{
  /* Get conversion value */
  InjectedConvData = HAL_SDADC_InjectedGetValue(&hsdadc2, (uint32_t *) &InjChannel);
	C12666MA_VIDEO=(InjectedConvData+32768);
}

void C12666MA_Init(void)
{
	HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPEC_START_GPIO_Port,SPEC_START_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPEC_GAIN_GPIO_Port,SPEC_GAIN_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
}

	void readSpectrometer(void)
	{
		int delayTime=1;
		int readTime=35;
		int intTime=20;
		int  idx = 0;	
		int accumulateMode = false;		
		// Step 1: start leading clock pulses
		for (int i = 0; i < SPEC_CHANNELS; i++) 
			{
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);			
			}
			//	DWT_Delay_us (100);		
		// Step 2: Send start pulse to signal start of integration/light collection
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SPEC_START_GPIO_Port,SPEC_START_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);	
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);	
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SPEC_START_GPIO_Port,SPEC_START_Pin,GPIO_PIN_SET);
		DWT_Delay_us (delayTime);	
	
		// Step 3: Integration time -- sample for a period of time determined by the intTime parameter		
		int blockTime = delayTime* 8;
		long int  numIntegrationBlocks = ((long)intTime * (long)1000) /(long) blockTime;	
		
	  for (int i = 0; i < numIntegrationBlocks; i++) 
			{
							// Four clocks per pixel
							// First block of 2 clocks -- measurement
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);	
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);	

				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);	
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);				
			}				
		
	  // Step 4: Send start pulse to signal end of integration/light collection	
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SPEC_START_GPIO_Port,SPEC_START_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);	
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
		DWT_Delay_us (delayTime);	
		HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SPEC_START_GPIO_Port,SPEC_START_Pin,GPIO_PIN_SET);
		DWT_Delay_us (delayTime);				
			
			
	//	HAL_GPIO_WritePin(C12666MA_LED_GPIO_Port,C12666MA_LED_Pin,GPIO_PIN_RESET);
			
			LED_OFF
			
			// Step 5: Read Data 2 (this is the actual read, since the spectrometer has now sampled data)	
			  idx = 0;	
			for (int i = 0; i < SPEC_CHANNELS; i++) 
			{ 
			// Four clocks per pixel
			// First block of 2 clocks -- measurement	
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
			DWT_Delay_us (delayTime);
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
			DWT_Delay_us (delayTime);	
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);		
			//DWT_Delay_us (100);// islem beklemesi
			// Analog value is valid on low transition		
			if(accumulateMode == false) 
			{
				DWT_Delay_us (150);	
				
//			for(int k=0;k<300;k++) 
//			{
//			Video_data +=	C12666MA_VIDEO;
//			}
//			Video_data=(Video_data/300);
			Video_data =	C12666MA_VIDEO;
			VIDEO_DATA[idx]=(int16_t)Video_data;
			}
			else {}

			//	SDADC DEN VIDEO OKUNACAK!!!!!!!!!
			idx += 1;
			if (delayTime > readTime)  DWT_Delay_us(delayTime - readTime);   // Read takes about 135uSec				
				
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);	
			DWT_Delay_us (delayTime);
			// Second block of 2 clocks -- idle
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
			DWT_Delay_us (delayTime);
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
			DWT_Delay_us (delayTime);	
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
			DWT_Delay_us (delayTime);
			HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
			DWT_Delay_us (delayTime);
		}	
		  // Step 6: trailing clock pulses
		  for (int i = 0; i < SPEC_CHANNELS; i++) 
			{
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_RESET);
				DWT_Delay_us (delayTime);
				HAL_GPIO_WritePin(SPEC_CLK_GPIO_Port,SPEC_CLK_Pin,GPIO_PIN_SET);
				DWT_Delay_us (delayTime);		
			}
	}
	
