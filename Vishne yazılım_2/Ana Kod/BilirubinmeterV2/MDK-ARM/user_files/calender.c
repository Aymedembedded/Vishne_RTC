#include "calender.h"
	RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
	//RTC_DateTypeDef sDate1;
	char date[16];
	char time[16];
	char hour1[5];
	uint8_t hour2;
	uint8_t minute2;
	uint8_t day2;
	uint8_t month2;
	uint8_t year2;
	uint8_t second3;
	uint8_t hour3;
	uint8_t minute3;
	uint8_t day3;
	uint8_t month3;
	uint8_t year3;
	char minute1[5]; 
	char second1[5];
	char day1[5];
	char month1[5];
	char year1[5];
void getCalender(void)
	{

		if( displayState == MainScreen || displayState == IntroTestScreen || displayState == EndOfTestScreen){
			/*Get the RTC current Time */
			HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
			/*Get the RTC current date */
			HAL_RTC_GetDate(&hrtc,&sDate, RTC_FORMAT_BIN);

			/*Display time format hh:mm:ss */
			sprintf(time,"%02d:%02d:%02d",sTime.Hours,sTime.Minutes,sTime.Seconds);
			/*Display date format dd:mm:yy */
			sprintf(date,"%02d:%02d:%02d",sDate.Date,sDate.Month,sDate.Year);

			ILI9341_WriteString(10, 75,date, Font_7x10, ILI9341_WHITE, ILI9341_BLUE);
			ILI9341_WriteString(150, 75,time, Font_7x10, ILI9341_WHITE, ILI9341_BLUE);
			hour2=sTime.Hours;
			minute2=sTime.Minutes;
			day2=sDate.Date;
			month2=sDate.Month;
			year2=sDate.Year;
		}
		else if( displayState == SetDateScreen){

		}
		else if( displayState == SetHourScreen){

			//ILI9341_WriteString(125, 200,year1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
		}
	}
	
void writeCalendertoMemory(void)
{
		uint32_t measurementNo;
		/*Get the RTC current Time */
		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		/*Get the RTC current date */
		HAL_RTC_GetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
	
		hour3 = sTime.Hours;
		minute3 = sTime.Minutes;
		second3 = sTime.Seconds;
		day3 = sDate.Date;
		month3 = sDate.Month;
		year3 = sDate.Year;
	
	
		measurementNo = measurementNumber - 1;
		measurementNo = measurementNo * 9;
		
		
		W25qxx_WriteByte(hour3, eepromMemoryinByte - (measurementNo));
		W25qxx_WriteByte(minute3, eepromMemoryinByte - (measurementNo+1));
		W25qxx_WriteByte(second3, eepromMemoryinByte - (measurementNo+2));
		W25qxx_WriteByte(day3, eepromMemoryinByte - (measurementNo+3));
		W25qxx_WriteByte(month3, eepromMemoryinByte - (measurementNo+4));
		W25qxx_WriteByte(year3, eepromMemoryinByte - (measurementNo+5));
		
}


		void setTime(void){

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = hour2;
  sTime.Minutes = minute2;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
			
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

	}
	
	
		void setDate(void){

  /** Initialize RTC and set the Time and Date 
  */
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

  //sDate.WeekDay = RTC_WEEKDAY_FRIDAY;
  sDate.Month = month2;
  sDate.Date = day2;
  sDate.Year = year2;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
	}
	
	void setCalender(void){

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 14;
  sTime.Minutes = 20;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_FRIDAY;
  sDate.Month = RTC_MONTH_APRIL;
  sDate.Date = 24;
  sDate.Year = 20;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
	}
	
	
	void Init_Calender(void){
		if( HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F2){
			setCalender();
		}
	}
	
	
	void setDateDsp(void){
			sprintf(day1,"%02d",day2);
			sprintf(month1,"%02d",month2);
			sprintf(year1,"%02d",year2);
			ILI9341_WriteString(125, 110,day1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
			ILI9341_WriteString(125, 155,month1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
			ILI9341_WriteString(125, 200,year1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
	}
	
	
		void setTimeDsp(void){
			sprintf(hour1,"%02d",hour2);
			sprintf(minute1,"%02d",minute2);
			sprintf(second1,"%02d",sTime.Seconds);
			ILI9341_WriteString(128, 110,hour1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
			ILI9341_WriteString(128, 155,minute1, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
	}
	
		
		
		
		