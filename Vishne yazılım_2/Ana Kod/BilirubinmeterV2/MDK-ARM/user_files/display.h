
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "main.h"
#include "ili9341.h"
#include "fonts.h" 
#include "system.h"
#define MainScreen							0
#define TestScreen 							1
#define IntroTestScreen 				2
#define EndOfTestScreen			3
#define testSavedScreen			4
#define SettingsScreen			 	5
#define MemoryScreen					6
#define	DltMemScreen				17
#define CalScreen1					 		7
#define CalScreen2							8
#define CalScreen3							9
#define CalScreen4							16
#define CalScreen22						10
#define CalScreen33    					11
#define TestCalScreen					12
#define KeyBoardScreen			13
#define SetDateScreen					14
#define SetHourScreen					15
#define DetlScreen								18
#define MemDetlScreen				19
#define dataSettingsScreen	20
#define BackToTheEndOfTestScreen	21

#define totalPageNumber 200

void mainScreenDisplay (void);
void testScreenDisplay (void);
void testIntroDisplay (void);
void testSavedDisplay (void);
void MemoryDisplay (void);
void SettingsDisplay (void);
void setDateScreen (void);
void setTimeScreen (void);
void CalDisplay1(void);
void CalDisplay2(void);
void CalDisplay3(void);
void CalDisplay4(void);
void DltMemDisplay (void);
void testCalDisplay (void);
void keyboard(void);
void batLevel(void);
void backSetScreen (void);
void backApplyScreen (void);
void DetailScreen (void);
void MemDetailScreen (void);
void dataSettings(void);
void memoryPageDisplay(uint8_t pageNumber);
extern	uint16_t ImageBuffer[6000];
extern	uint8_t displayState;
extern uint8_t ScreenState;
extern uint8_t memPos;
extern uint16_t measurementNumber;
extern int PTNi;
extern uint8_t pageNumber;
extern uint16_t memNo;
extern uint16_t TotPatNo;
extern const uint16_t image_data_grafik[24300] ;
extern char displayBuff[16];
extern bool redBarFlag[5];
void getpatientNum(void);
void measurementNum(void);
void ErrorDisplay3(void);
void printBilirubinVal(void);
void printBilirubinVal_mg_dL(float BiliResult, uint16_t x_coord, uint16_t y_coord, uint16_t color, uint16_t bgcolor);
void printBilirubinVal_umol_L(float BiliResult, uint16_t x_coordi, uint16_t y_coordi, uint16_t color, uint16_t bgcolor);
void printbilirubinAsGraph(void);

#endif // __DISPLAY_H__
