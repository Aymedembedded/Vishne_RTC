

///* Define to prevent recursive inclusion -------------------------------------*/
//#ifndef __STM32F429I_DISCOVERY_H
//#define __STM32F429I_DISCOVERY_H

//#ifdef __cplusplus
// extern "C" {
//#endif
//                                              
///* Includes ------------------------------------------------------------------*/
//#include "stm32f3xx_hal.h"
//   
///** 
//  * @brief Define for STM32F429I_DISCO board  
//  */ 
//#if !defined (USE_STM32F429I_DISCO)
// #define USE_STM32F429I_DISCO
//#endif


///** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_BUS STM32F429I DISCOVERY LOW LEVEL BUS
//  * @{
//  */  
///* Exported constanIO --------------------------------------------------------*/
//#define IO_I2C_ADDRESS                      0x82 
//#define TS_I2C_ADDRESS                      0x82


///*############################### I2Cx #######################################*/
///* User can use this section to tailor I2Cx instance used and associated 
//   resources */
//#define DISCOVERY_I2Cx                          I2C2
//#define DISCOVERY_I2Cx_CLOCK_ENABLE()           __HAL_RCC_I2C2_CLK_ENABLE()
//#define DISCOVERY_I2Cx_FORCE_RESET()            __HAL_RCC_I2C2_FORCE_RESET()
//#define DISCOVERY_I2Cx_RELEASE_RESET()          __HAL_RCC_I2C2_RELEASE_RESET()
//#define DISCOVERY_I2Cx_SDA_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
//#define DISCOVERY_I2Cx_SCL_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE() 
//#define DISCOVERY_I2Cx_SDA_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOA_CLK_DISABLE()

///* Definition for DISCO I2Cx Pins */
//#define DISCOVERY_I2Cx_SCL_PIN                  GPIO_PIN_9
//#define DISCOVERY_I2Cx_SCL_GPIO_PORT            GPIOA
//#define DISCOVERY_I2Cx_SCL_SDA_AF               GPIO_AF4_I2C2
//#define DISCOVERY_I2Cx_SDA_PIN                  GPIO_PIN_10
//#define DISCOVERY_I2Cx_SDA_GPIO_PORT            GPIOA

///* Definition for IOE I2Cx's NVIC */
//#define DISCOVERY_I2Cx_EV_IRQn                  I2C2_EV_IRQn
//#define DISCOVERY_I2Cx_ER_IRQn                  I2C2_ER_IRQn

///* I2C clock speed configuration (in Hz) 
//  WARNING: 
//   Make sure that this define is not already declared in other files.
//   It can be used in parallel by other modules. */
//#ifndef BSP_I2C_SPEED
// #define BSP_I2C_SPEED                          100000
//#endif /* BSP_I2C_SPEED */

//#define I2Cx_TIMEOUT_MAX                    0x3000 /*<! The value of the maximal timeout for I2C waiting loops */



///*################################ IOE #######################################*/
///** 
//  * @brief  IOE Control pin  
//  */ 
///* Definition for external IT for STMPE811 */
//#define STMPE811_INT_PIN                        GPIO_PIN_8
//#define STMPE811_INT_GPIO_PORT                  GPIOA
//#define STMPE811_INT_CLK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE()
//#define STMPE811_INT_CLK_DISABLE()              __HAL_RCC_GPIOA_CLK_DISABLE()
//#define STMPE811_INT_EXTI                       EXTI9_5_IRQn
//#define STMPE811_INT_EXTIHandler                EXTI9_5_IRQHandler



//#ifdef __cplusplus
//}
//#endif

//#endif /* __STM32F429I_DISCOVERY_H */

///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
