#ifndef __C12666MA_H__
#define __C12666MA_H__
#include "main.h"
#include "dwt_stm32_delay.h"
#include <stdbool.h>
#include "main.h"
#include "i2c.h"
#include "sdadc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"


extern uint16_t VIDEO_DATA[ 256];
void C12666MA_Init(void);
void readSpectrometer(void);


#endif // __C12666MA_H__
