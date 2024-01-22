#ifndef __PATIENT_H__
#define __PATIENT_H__


#include "includes.h"

#define StartMem  	1623
#define EndMem			2623
#define PtnMEM			2624

#define DateMemory	3000
#define TimeMemory		4000

#define measurementMemorySize 1000

#define eepromMemoryinByte 16777215
#define eepromMemoryinPage 65536
#define eepromMemoryinSector 4096
#define eepromMemoryinBlock 512

#define oneSectorLength 4096

#pragma pack(1)
typedef struct  {
	uint8_t id[20];			//barcode
	uint8_t Date[1];     //Specifies the RTC Date.	
	uint8_t Month[1];     //Specifies the RTC Date Month
	uint8_t Year[1];      //Specifies the RTC Date Year.
	float bilResult[1];			//Bilirubin Result
	uint16_t spec[256];//Spectrum Data
}ptn;
typedef union{
	uint8_t frame[533];
	ptn patient;
}ptnFrm;

//extern struct ptn patient;
void setPatientInfo(void);
void savePatient(void);
void readPatient(void);
extern ptnFrm patientFr;
extern ptnFrm readPtn;

#endif // __PATIENT_H__
