/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __calculation_H
#define __calculation_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
extern float BilResult[1];
long absolute(long value) ;
void movingAvarage(void);
uint16_t find_maximum(uint16_t a[], uint16_t n) ;
void BilCalculation(void);



#ifdef __cplusplus
}
#endif

#endif
