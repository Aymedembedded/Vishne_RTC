#include "patient.h"
#pragma pack(1)
//ptn patient;
ptnFrm patientFr;
ptnFrm readPtn;


//uint16_t patientNo[1];
//siz = sizeof(patient.bilResult);
void setPatientInfo(void)
{	
	getCalender();
	patientFr.patient.Date[0] = sDate.Date;
	patientFr.patient.Month[0] = sDate.Month;
	patientFr.patient.Year[0] = sDate.Year;
	patientFr.patient.bilResult[0] = BilResult[0];
	
	/*	for(int sp=0;sp<256;sp++)
	{
		patientFr.patient.spec[sp]=VIDEO_DATA[sp];
	}*/

}


void savePatient(void){
	setPatientInfo();
	uint32_t Sector_Addr ;
	W25qxx_ReadSector((uint8_t *)PatientCounter ,PtnMEM , 0, 2);
	Sector_Addr = PatientCounter[0];
	if( Sector_Addr >= StartMem && Sector_Addr <=EndMem)
	{
		W25qxx_EraseSector(Sector_Addr);
		W25qxx_WriteSector(patientFr.frame,Sector_Addr,0,533);
		
	}
	
	else
	{
		Sector_Addr = StartMem;
		PatientCounter[0] = Sector_Addr;
		W25qxx_EraseSector(Sector_Addr);
		W25qxx_WriteSector(patientFr.frame,Sector_Addr,0,533);
		
	}	
	PatientCounter[0]++;
	
	W25qxx_EraseSector(PtnMEM);
	W25qxx_WriteSector((uint8_t *)PatientCounter,PtnMEM,0,2);
}

void readPatient(void){
		uint32_t  SctrAdrr ;
		W25qxx_ReadSector((uint8_t *)PatientCounter ,PtnMEM , 0, 2);
		SctrAdrr = PatientCounter[0];
		W25qxx_ReadSector(readPtn.frame,SctrAdrr-1,0,533);	
	}



