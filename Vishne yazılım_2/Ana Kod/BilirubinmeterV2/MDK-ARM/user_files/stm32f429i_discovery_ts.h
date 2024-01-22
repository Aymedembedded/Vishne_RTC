
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_TS_H
#define __STM32F429I_DISCOVERY_TS_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
/* Include TouchScreen component driver */
#include "stmpe811.h"   
   
/** @defgroup STM32F429I_DISCOVERY_TS_Exported_Types STM32F429I DISCOVERY TS Exported Types
  * @{
  */ 
typedef struct
{
  uint16_t TouchDetected;
  uint16_t X;
  uint16_t Y;
  uint16_t Z;
}TS_StateTypeDef;
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_TS_Exported_Constants STM32F429I DISCOVERY TS Exported Constants
  * @{
  */ 
#define TS_SWAP_NONE                    0x00
#define TS_SWAP_X                       0x01
#define TS_SWAP_Y                       0x02
#define TS_SWAP_XY                      0x04

typedef enum 
{
  TS_OK       = 0x00,
  TS_ERROR    = 0x01,
  TS_TIMEOUT  = 0x02
}TS_StatusTypeDef;
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_TS_Exported_Macros STM32F429I DISCOVERY TS Exported Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_TS_Exported_Functions STM32F429I DISCOVERY TS Exported Functions
  * @{
  */
uint8_t BSP_TS_Init(uint16_t XSize, uint16_t YSize);
void    BSP_TS_GetState(TS_StateTypeDef *TsState);
uint8_t BSP_TS_ITConfig(void);
uint8_t BSP_TS_ITGetStatus(void);
void    BSP_TS_ITClear(void);

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_TS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
