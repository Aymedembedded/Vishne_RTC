/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "system.h"
/* Defines ------------------------------------------------------------------*/


	uint16_t ImageBuffer[6000];
	uint8_t displayState=0;
	uint8_t pageNo = 0;
	uint16_t memNo = 0;
	uint8_t memPos=1;
	uint16_t TotPatNo=0;
	int PTNi=1;
	uint8_t pageNumber = 1;
	char displayBuff[16]=" ";
	extern char PatientAscii[10];
	uint16_t measurementNumber;
	bool redBarFlag[5];
	
/*	extern char	asciiresult[10];
	extern char asciiresult2[10];*/
	extern uint8_t rx_buff[20];
	/*main screen display************************************************************/
	void mainScreenDisplay (void)
	{
		
			ILI9341_FillRectangle(0,65,240,255,ILI9341_BLUE);
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
		//	batLevel();
			backSetScreen();
		
			displayState = MainScreen;
	}
	/*test screen display************************************************************/
	void testScreenDisplay (void)
	{
		
			displayState = EndOfTestScreen;
			//ILI9341_FillRectangle(0,66,240,190,ILI9341_BLUE);
		
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
			
			printBilirubinVal_mg_dL(BilResult[0], 40, 140, ILI9341_BLUE, ILI9341_WHITE);
			
		
	}
		/*Introtest screen display************************************************************/
	void testCalDisplay (void)
	{
		
		
		ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
		ILI9341_FillRectangle(0,100,240,135,ILI9341_WHITE);
		ILI9341_WriteString(20, 150, "Referansi okutunuz", Font_11x18, ILI9341_BLUE, ILI9341_WHITE);	
		ILI9341_WriteString(20, 200, "!!Referans sarj unitesindeki         kapagin altinda bulunur", Font_7x10, ILI9341_RED, ILI9341_WHITE);
		displayState = TestCalScreen;
		HAL_Delay(3000);
		
		

		//ILI9341_WriteString(30, 160, "Yapiniz", Font_16x26, ILI9341_BLUE, ILI9341_WHITE);	
	}	
	/*Introtest screen display************************************************************/
	void testIntroDisplay (void)
	{

			ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
		
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
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,29,0,12000);
			ILI9341_DrawImage(0, 241, 240, 25 , (const uint16_t*)ImageBuffer);
			ILI9341_FillRectangle(0,241,240,10,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,30,0,12000);
			ILI9341_DrawImage(0, 266, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,31,0,12000);
			ILI9341_DrawImage(0, 291, 240, 25 , (const uint16_t*)ImageBuffer);
			
		
	}	
	/*Test Saved screen display************************************************************/	
		void testSavedDisplay (void)
		{
			
			
			ILI9341_FillRectangle(0,100,240,135,ILI9341_WHITE);
			ILI9341_WriteString(40, 90, PatientAscii, Font_16x26, ILI9341_BLUE, ILI9341_WHITE);
			ILI9341_WriteString(85, 100, "Test", Font_16x26, ILI9341_BLUE, ILI9341_WHITE);
			ILI9341_WriteString(55, 130, "Kaydedildi!", Font_11x18, ILI9341_BLUE, ILI9341_WHITE);	
			
			/*Display time format hh:mm:ss */
			sprintf(time,"Tarih:%02d:%02d:%02d",hour3,minute3,second3);
			/*Display date format dd:mm:yy */
			sprintf(date,"Saat:%02d:%02d:%02d",day3,month3,year3);

			ILI9341_WriteString(20, 160,date, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
			ILI9341_WriteString(20, 190,time, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
					
			sprintf(time,"Test No: %d",(measurementNumber));
			ILI9341_WriteString(20, 220,time, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
			displayState = testSavedScreen;
			DWT_Delay_us(1500000);
		}	
		
		/*Settings screen display************************************************************/	
		void SettingsDisplay (void)
		{
			ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
			
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
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,30,0,12000);
			ILI9341_DrawImage(0, 266, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,31,0,12000);
			ILI9341_DrawImage(0, 291, 240, 25 , (const uint16_t*)ImageBuffer);
			
			//backSetScreen();
			displayState = SettingsScreen;
			
		}
		void dataSettings(void)
		{
						/* klinik testlerde kullanilir*/
			ILI9341_FillRectangle(0,100,240,135,ILI9341_BLUE);
			ILI9341_FillRectangle(10,100,220,60,ILI9341_WHITE);
			ILI9341_FillRectangle(13,103,214,54,ILI9341_BLUE);
			ILI9341_WriteString(20, 120, " Verileri Aktar ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(10,175,220,60,ILI9341_WHITE);
			ILI9341_FillRectangle(13,178,214,54,ILI9341_BLUE);
			ILI9341_WriteString(20, 195, " Hafizayi Temizle ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			
			displayState = dataSettingsScreen;
		}
		/*Date Settings screen display************************************************************/	
			void setDateScreen (void)
	{		
			ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,32,0,12000);
			ILI9341_DrawImage(0, 66, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,33,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,34,0,12000);			
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,35,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,36,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,37,0,12000);			
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,38,0,12000);
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
		
			backApplyScreen();
			displayState = SetDateScreen;
	}
	
	
	/*Hour Settings screen display************************************************************/	
			void setTimeScreen (void)
	{
			ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
			
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,39,0,12000);
			ILI9341_DrawImage(0, 66, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,40,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,41,0,12000);			
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,42,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,43,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
		
			backApplyScreen();
			displayState = SetHourScreen;
	}	
		
					void CalDisplay1(void)
	{	
			ILI9341_FillRectangle(0,66,240,255,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,48,0,12000);
			ILI9341_DrawImage(0, 91, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,49,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,50,0,12000);			
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,51,0,12000);
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,52,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,53,0,12000);			
			ILI9341_DrawImage(0, 216, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,54,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,55,0,12000);			
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);		
			displayState = CalScreen1;
	}
			void CalDisplay2(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,56,0,12000
		);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,57,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,58,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,59,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			displayState = CalScreen2;
	}
	
		void CalDisplay3(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,60,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,61,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,62,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,63,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			displayState = CalScreen3;
	}
	
			void CalDisplay4(void)
	{	
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,64,0,12000);
			ILI9341_DrawImage(0, 116, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,65,0,12000);
			ILI9341_DrawImage(0, 141, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,66,0,12000);			
			ILI9341_DrawImage(0, 166, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,67,0,12000);
			ILI9341_DrawImage(0, 191, 240, 25 , (const uint16_t*)ImageBuffer);
			displayState = CalScreen4;
	}
		void DetailScreen (void)
	{		

			
			ILI9341_FillRectangle(0,66,240,240,ILI9341_BLUE);
			ILI9341_WriteString(10, 222, " T.Bil:      umol/L", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
		
			/* Mu sembolü */
			for(int i = 0; i < 20; i++)
			{
				ILI9341_DrawPixel(154,227+i,ILI9341_WHITE);
				ILI9341_DrawPixel(155,227+i,ILI9341_WHITE);
			}
		
			printBilirubinVal_umol_L(BilResult[0], 90, 222, ILI9341_WHITE, ILI9341_BLUE);
			
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,68,0,12000);
			ILI9341_DrawImage(0, 70, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,69,0,12000);
			ILI9341_DrawImage(0, 95, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,70,0,12000);			
			ILI9341_DrawImage(0, 120, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,71,0,12000);
			ILI9341_DrawImage(0, 145, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,72,0,12000);
			ILI9341_DrawImage(0, 170, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,73,0,10560);
			ILI9341_DrawImage(0, 195, 240, 22 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,29,0,12000);
			ILI9341_DrawImage(0, 241, 240, 25 , (const uint16_t*)ImageBuffer);
			ILI9341_FillRectangle(0,241,240,10,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,30,0,12000);
			ILI9341_DrawImage(0, 266, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,31,0,12000);
			ILI9341_DrawImage(0, 291, 240, 25 , (const uint16_t*)ImageBuffer);

			printbilirubinAsGraph();
			

			displayState = DetlScreen;
			
			//ILI9341_WriteString(50, 130, " GRAFIK", Font_16x26, ILI9341_WHITE, ILI9341_BLUE);
			//ILI9341_DrawImage(30, 90, 180, 135, (const uint16_t*)image_data_grafik);

	}
	
		void MemDetailScreen (void)
	{		
			float bilirubinValue;

			ILI9341_FillRectangle(10,30,240,217,ILI9341_WHITE);
			ILI9341_WriteString(92, 40, "DETAY ", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
			ILI9341_WriteString(20, 75, "ID: ", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);

			sprintf(displayBuff,"%u",memNo);
			ILI9341_WriteString(60, 75,displayBuff, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
		
			uint8_t *readmeasurementDate;
			uint16_t dataNumber = memPos;
			readmeasurementDate = (uint8_t *) malloc(3);
		
			uint8_t *readmeasurementTime;
			readmeasurementTime = (uint8_t *) malloc(3);
		
			uint8_t *readmeasurementBilirubin;
			readmeasurementBilirubin = (uint8_t *) malloc(3);
			
			uint32_t measurementNo;
			
			measurementNo = memNo - 1;
			measurementNo = measurementNo * 9;
	
			
			W25qxx_ReadByte(readmeasurementTime, eepromMemoryinByte - (measurementNo));
			W25qxx_ReadByte(readmeasurementTime+1, eepromMemoryinByte - (measurementNo+1));
			W25qxx_ReadByte(readmeasurementTime+2, eepromMemoryinByte - (measurementNo+2));
			W25qxx_ReadByte(readmeasurementDate, eepromMemoryinByte - (measurementNo+3));
			W25qxx_ReadByte(readmeasurementDate+1, eepromMemoryinByte - (measurementNo+4));
			W25qxx_ReadByte(readmeasurementDate+2, eepromMemoryinByte - (measurementNo+5));
			
			W25qxx_ReadByte(readmeasurementBilirubin, eepromMemoryinByte - (measurementNo+6));
			W25qxx_ReadByte(readmeasurementBilirubin+1, eepromMemoryinByte - (measurementNo+7));
			W25qxx_ReadByte(readmeasurementBilirubin+2, eepromMemoryinByte - (measurementNo+8));
			
			/* Bilirubin value calculation as float and printing it on the screen*/
			
			
			
			bilirubinValue = 0;
			bilirubinValue = readmeasurementBilirubin[0] * 1000;
			bilirubinValue = bilirubinValue + readmeasurementBilirubin[1]  * 10.0;
			bilirubinValue = bilirubinValue + readmeasurementBilirubin[2]; 
			bilirubinValue = bilirubinValue / 1000;
			
			
		
			if(memNo < measurementNumber)
			{
				sprintf(date,"Tarih:%02d:%02d:%02d",readmeasurementDate[0],readmeasurementDate[1],readmeasurementDate[2]);
				ILI9341_WriteString(20, 105, date, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
		
				sprintf(time,"Saat:%02d:%02d:%02d",readmeasurementTime[0],readmeasurementTime[1],readmeasurementTime[2]);
				ILI9341_WriteString(20, 135, time, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
				ILI9341_WriteString(20, 175, "T.Bil:      mg/dL ", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
			
				printBilirubinVal_mg_dL(bilirubinValue, 90, 175, ILI9341_BLACK, ILI9341_WHITE);
	
				ILI9341_WriteString(20, 205, "T.Bil:      umol/dL", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);	
			
				printBilirubinVal_umol_L(bilirubinValue, 90, 205, ILI9341_BLACK, ILI9341_WHITE);
			}
			else
			{
				sprintf(date,"Tarih: ");
				ILI9341_WriteString(20, 105, date, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
		
				sprintf(time,"Saat: ");
				ILI9341_WriteString(20, 135, time, Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
				
				ILI9341_WriteString(20, 175, "T.Bil:  -   mg/dL ", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
				
				ILI9341_WriteString(20, 205, "T.Bil:  -   umol/dL", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);	
			}
			

			
			for(int i = 0; i < 15; i++)
			{
				ILI9341_DrawPixel(153,210+i,ILI9341_BLACK);
				ILI9341_DrawPixel(154,210+i,ILI9341_BLACK);
			}
			
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,29,0,12000);
			ILI9341_DrawImage(0, 241, 240, 25 , (const uint16_t*)ImageBuffer);
			ILI9341_FillRectangle(0,241,240,10,ILI9341_WHITE);
			ILI9341_FillRectangle(0,249,240,2,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,30,0,12000);
			ILI9341_DrawImage(0, 266, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,31,0,12000);
			ILI9341_DrawImage(0, 291, 240, 25 , (const uint16_t*)ImageBuffer);
			
			displayState = MemDetlScreen;
	}
		/*Memory screen display************************************************************/	
		void MemoryDisplay (void)
		{
		
			displayState = MemoryScreen;
			

			
			ILI9341_FillRectangle(0,0,240,30,ILI9341_BLUE);
			ILI9341_WriteString(87, 11, "HAFIZA", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
		//	ILI9341_FillRectangle(0,31,240,220,ILI9341_WHITE);
			
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,19,0,12000);
			ILI9341_DrawImage(0, 236, 240, 25 , (const uint16_t*)ImageBuffer);
			ILI9341_FillRectangle(0,236,240,20,ILI9341_BLUE);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,20,0,12000);
			ILI9341_DrawImage(0, 261, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,21,0,12000);			
			ILI9341_DrawImage(0, 286, 240, 25 , (const uint16_t*)ImageBuffer);

			
			memoryPageDisplay(pageNumber);
			
		}
		
		void memoryPageDisplay(uint8_t pageNumber)
		{
			char displayBuff[16];
			measurementNum();
			ILI9341_FillRectangle(0,30,240,220,ILI9341_WHITE);
			for(int i = (5 * (pageNumber - 1) + 1),j = 1; i <= (5 * pageNumber), j <= 5; i++, j++)
			{
				if(i < measurementNumber)
				{
					sprintf(displayBuff,"*");
					ILI9341_WriteString(175, (j*40)+((j-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
				}
				sprintf(displayBuff,"%u. OLCUM",i);
				ILI9341_WriteString(20, (j*40)+((j-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
			}
			
			sprintf(displayBuff," ^ ");
			ILI9341_WriteString(190, 50, displayBuff, Font_16x26, ILI9341_RED, ILI9341_YELLOW);
			sprintf(displayBuff," v ");
			ILI9341_WriteString(190, 215, displayBuff, Font_16x26, ILI9341_RED, ILI9341_YELLOW);
			
			
		}
		
		void printMeasurementInfo(uint8_t *date, uint8_t *time)
		{
			sprintf(displayBuff,"Tarih: %02u:%02u:%02u",date[0], date[1], date[2]);
			ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);	
			
			sprintf(displayBuff,"Saat: %02u:%02u:%02u",time[0], time[1], time[2]);
			ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);	
		}
		

		
				/*DltMem screen display************************************************************/	
		void DltMemDisplay (void)
		{
			
			ILI9341_FillRectangle(0,100,240,135,ILI9341_BLUE);
			
			ILI9341_FillRectangle(10,100,220,60,ILI9341_WHITE);
			ILI9341_FillRectangle(13,103,214,54,ILI9341_BLUE);
			ILI9341_WriteString(20, 120, " SIL ", Font_11x18, ILI9341_RED, ILI9341_BLUE);
			ILI9341_FillRectangle(10,175,220,60,ILI9341_WHITE);
			ILI9341_FillRectangle(13,178,214,54,ILI9341_BLUE);
			ILI9341_WriteString(20, 195, " VAZGEC ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			
			displayState = DltMemScreen;
		}
		
		void keyboard(void){
			
			ILI9341_FillRectangle(0,100,240,135,ILI9341_BLUE);
			ILI9341_FillRectangle(65,235,175,85,ILI9341_BLUE);
			ILI9341_FillRectangle(5,100,70,35,ILI9341_WHITE);
			ILI9341_WriteString(23, 108, " 1 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(85,100,70,35,ILI9341_WHITE);
			ILI9341_WriteString(103, 108, " 2 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(165,100,70,35,ILI9341_WHITE);
			ILI9341_WriteString(183, 108, " 3 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);

			ILI9341_FillRectangle(5,150,70,35,ILI9341_WHITE);
			ILI9341_WriteString(23, 158, " 4 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(85,150,70,35,ILI9341_WHITE);
			ILI9341_WriteString(103, 158, " 5 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(165,150,70,35,ILI9341_WHITE);
			ILI9341_WriteString(183, 158, " 6 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);

			ILI9341_FillRectangle(5,200,70,35,ILI9341_WHITE);
			ILI9341_WriteString(23, 208, " 7 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(85,200,70,35,ILI9341_WHITE);
			ILI9341_WriteString(103, 208, " 8 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_FillRectangle(165,200,70,35,ILI9341_WHITE);
			ILI9341_WriteString(183, 208, " 9 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			
			ILI9341_FillRectangle(85,250,70,35,ILI9341_WHITE);
			ILI9341_WriteString(103, 258, " 0 ", Font_11x18, ILI9341_WHITE, ILI9341_BLUE);
			
			ILI9341_FillRectangle(165,250,70,35,ILI9341_YELLOW);
			ILI9341_WriteString(173, 258, " Sil ", Font_11x18, ILI9341_BLUE, ILI9341_YELLOW);
			
			displayState = KeyBoardScreen;
		}
		
		void batLevel(void){
			ILI9341_FillRectangle(210,76,25,4,ILI9341_BLACK);
			ILI9341_FillRectangle(213,72,22,12,ILI9341_BLACK);
		}
				void backSetScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,44,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,45,0,12000);
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
	
		void backApplyScreen (void)
	{
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,46,0,12000);
			ILI9341_DrawImage(0, 253, 240, 25 , (const uint16_t*)ImageBuffer);
			W25qxx_ReadBlock((uint8_t *)ImageBuffer,47,0,12000);
			ILI9341_DrawImage(0, 278, 240, 25 , (const uint16_t*)ImageBuffer);
	}
	
void printBilirubinVal_mg_dL(float BiliResult, uint16_t x_coord, uint16_t y_coord, uint16_t color, uint16_t bgcolor)
{
	char bilResult_mg_dL[50] = {'/0'};
	sprintf(bilResult_mg_dL,"%.3lf",BiliResult/17.10000063270002f);
	ILI9341_WriteString(x_coord, y_coord, bilResult_mg_dL, Font_11x18, color, bgcolor);
}
void printBilirubinVal_umol_L(float BiliResult, uint16_t x_coordi, uint16_t y_coordi, uint16_t color, uint16_t bgcolor)
{
	char bilResult_umol_L[50] = {'/0'};
	sprintf(bilResult_umol_L,"%.2lf",BiliResult);
	ILI9341_WriteString(x_coordi, y_coordi, bilResult_umol_L, Font_11x18, color, bgcolor);
}

void printbilirubinAsGraph(void)
{
	uint8_t x_ekseni;
	float y_ekseni;
		for (x_ekseni = 0; x_ekseni < 255; x_ekseni++)
		{
			y_ekseni = VIDEO_DATA[x_ekseni]/256;
			y_ekseni = 0.35f * y_ekseni;
			ILI9341_WriteString(45+x_ekseni/1.5, (180-(int)y_ekseni), " ", Font_7x10, ILI9341_BLUE, ILI9341_YELLOW);
		}
	
}

		/*Get Patient memory number ************************************************************/	
		void getpatientNum(void)
		{
				for(int id=0;id<20;id++)
			{
				patientFr.patient.id[id]=NULL;
			}
			W25qxx_ReadSector((uint8_t *)PatientCounter ,PtnMEM , 0, 2);
			TotPatNo=(PatientCounter[0]-StartMem);
			//sprintf(displayBuff,"%u",PatientCounter[0]-StartMem+1);
			if((uint16_t)(PatientCounter[0]-StartMem+1) < measurementMemorySize)
			{
				measurementNumber = (PatientCounter[0] - StartMem + 1);
				sprintf(displayBuff,"%u",PatientCounter[0]-StartMem+1);
				
			}
			else if((uint16_t)(PatientCounter[0]-StartMem+1) == 0)
			{
				measurementNumber = 1;
				sprintf(displayBuff,"%u",measurementNumber);
				
			}
			else
			{
				measurementNumber = 1;
				sprintf(displayBuff,"1");
			}
			patientFr.patient.id[0]=(uint16_t)(PatientCounter[0]-StartMem+1);
			ILI9341_WriteString(60, 215,displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
		
		}	
		
		void measurementNum(void)
		{
			for(int id=0;id<20;id++)
			{
				patientFr.patient.id[id]=NULL;
			}
			W25qxx_ReadSector((uint8_t *)PatientCounter ,PtnMEM , 0, 2);
			TotPatNo=(PatientCounter[0]-StartMem);
			//sprintf(displayBuff,"%u",PatientCounter[0]-StartMem+1);
			if((uint16_t)(PatientCounter[0]-StartMem+1) < measurementMemorySize)
			{
				measurementNumber = (PatientCounter[0] - StartMem + 1);
			}
			else if((uint16_t)(PatientCounter[0]-StartMem+1) == 0)
			{
				measurementNumber = 1;
				
			}
			else
			{
				measurementNumber = 1;
			}
			patientFr.patient.id[0]=(uint16_t)(PatientCounter[0]-StartMem+1);
		}
		


		
		void ErrorDisplay3(void){
			
			ILI9341_FillRectangle(0,90,240,160,ILI9341_YELLOW);
			ILI9341_WriteString(5, 100, " HATA:03 ", Font_16x26, ILI9341_RED, ILI9341_YELLOW);
			ILI9341_WriteString(5, 180, " Referans Disi olcum", Font_11x18, ILI9341_BLACK, ILI9341_YELLOW);
			
			displayState = DetlScreen;
		}