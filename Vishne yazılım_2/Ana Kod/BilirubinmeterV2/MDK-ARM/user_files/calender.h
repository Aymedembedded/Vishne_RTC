#ifndef __CALENDER_H__
#define __CALENDER_H__


#include "includes.h"
extern	RTC_TimeTypeDef sTime;
extern  RTC_DateTypeDef sDate;
extern	char hour1[5];
extern	char minute1[5]; 
extern	char second1[5];
extern	char day1[5];
extern	char month1[5];
extern	char year1[5];
extern	uint8_t hour2;
extern	uint8_t minute2;
extern	uint8_t day2;
extern	uint8_t month2;
extern	uint8_t year2;
extern	uint8_t hour3;
extern	uint8_t minute3;
extern	uint8_t day3;
extern	uint8_t month3;
extern	uint8_t year3;
extern	uint8_t second3;
extern	char date[16];
extern	char time[16];
void getCalender(void);
void setCalender(void);
void setTime(void);
void setDate(void);
void Init_Calender(void);
void setDateDsp(void);
void setTimeDsp(void);
void writeCalendertoMemory(void);

#endif // __CALENDER_H__