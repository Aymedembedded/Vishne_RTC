/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "fonts.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
 uint16_t ImageBuffer[6000];
 
		void backSetScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,42,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,43,0,12000);
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
	
		void backApplyScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,44,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,45,0,12000);
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	void mainScreen (void)
	{

			W25qxx_ReadBlock((uint8_t *)ImageBuffer,1,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,2,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,3,0,12000);			
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,4,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,5,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,6,0,12000);			
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
			backSetScreen ();
	}
	
	
	
	void testScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,7,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,8,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,9,0,12000);			
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,10,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,11,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,12,0,12000);			
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
			backSetScreen ();
	}
	
	
	
		void resultScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,13,0,12000);
			ILI9341_DrawImage(0, 86, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,14,0,12000);
			ILI9341_DrawImage(0, 111, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,15,0,12000);			
			ILI9341_DrawImage(0, 136, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,16,0,12000);
			ILI9341_DrawImage(0, 161, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,17,0,12000);
			ILI9341_DrawImage(0, 186, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,18,0,12000);			
			ILI9341_DrawImage(0, 211, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,19,0,12000);
			ILI9341_DrawImage(0, 236, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,20,0,12000);
			ILI9341_DrawImage(0, 261, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,21,0,12000);			
			ILI9341_DrawImage(0, 286, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
			void settingScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,22,0,12000);
			ILI9341_DrawImage(0, 66, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,23,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,24,0,12000);			
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,25,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,26,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,27,0,12000);			
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,28,0,12000);
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,29,0,12000);
			ILI9341_DrawImage(0, 241, 240, 25 , (const uint16_t*)ImageBuffer);
		backSetScreen ();
	}
	
	
	
		void setDateScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,30,0,12000);
			ILI9341_DrawImage(0, 66, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,31,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,32,0,12000);			
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,33,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,34,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,35,0,12000);			
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,36,0,12000);
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
		backApplyScreen();
	}
	
	
	
			void setHourScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,37,0,12000);
			ILI9341_DrawImage(0, 66, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,38,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,39,0,12000);			
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,40,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,41,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
		backApplyScreen();
	}
	
	
			void CalScreen1(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,46,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,47,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,48,0,12000);			
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,49,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,50,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,51,0,12000);			
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,52,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,53,0,12000);			
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);		
			//backSetScreen ();
	}
			void CalScreen2(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,54,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,55,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,56,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,57,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
		void CalScreen3(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,58,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,59,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,60,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,61,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
			void CalScreen4(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,62,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,63,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,64,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,65,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
	}