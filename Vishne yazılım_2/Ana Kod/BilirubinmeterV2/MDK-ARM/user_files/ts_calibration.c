
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static TS_StateTypeDef  TS_State;
static uint8_t Calibration_Done = 0;
static int16_t  A1, A2, B1, B2;
static int16_t aPhysX[2], aPhysY[2], aLogX[2], aLogY[2];

/* Private function prototypes -----------------------------------------------*/
static void GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY);
static void WaitForPressedState(uint8_t Pressed);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Performs the TS calibration
  * @param  None
  * @retval None
  */
void Touchscreen_Calibration(void)
{ 
  uint8_t status = 0;
  uint8_t i = 0;  
  status = BSP_TS_Init(240, 320);
  
  if (status != TS_OK)
  {
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
  }
  
  while (1)
  {
    if (status == TS_OK)
    {
//      aLogX[0] = 15;
//      aLogY[0] = 15;
//      aLogX[1] = BSP_LCD_GetXSize() - 15;
//      aLogY[1] = BSP_LCD_GetYSize() - 15;
//      
//      for (i = 0; i < 2; i++) 
//      {
//        GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i]);
//      }
//      A1 = (1000 * ( aLogX[1] - aLogX[0]))/ ( aPhysX[1] - aPhysX[0]); 
//      B1 = (1000 * aLogX[0]) - A1 * aPhysX[0]; 
//      
//      A2 = (1000 * ( aLogY[1] - aLogY[0]))/ ( aPhysY[1] - aPhysY[0]); 
//      B2 = (1000 * aLogY[0]) - A2 * aPhysY[0]; 
//      	
			
			A1 = (972); 
      B1 = (-555); 
      
      A2 = (993); 
      B2 = (-1762); 
      	
			
      Calibration_Done = 1;
      return;
    }
    
    HAL_Delay(5);
  }
}


/**
  * @brief  Get Physical position
  * @param  LogX : logical X position
  * @param  LogY : logical Y position
  * @param  pPhysX : Physical X position
  * @param  pPhysY : Physical Y position
  * @retval None
  */
static void GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY) 
{
 
  
  /* Wait until touch is pressed */
  WaitForPressedState(1);
  
  BSP_TS_GetState(&TS_State);
  *pPhysX = TS_State.X;
  *pPhysY = TS_State.Y; 
  
  /* Wait until touch is released */
  WaitForPressedState(0);

}

/**
  * @brief  Wait For Pressed State.
  * @param  None
  * @retval None
  */
static void WaitForPressedState(uint8_t Pressed) 
{
  TS_StateTypeDef  State;
  
  do 
  {
    BSP_TS_GetState(&State);
    HAL_Delay(10);
    if (State.TouchDetected == Pressed) 
    {
      uint16_t TimeStart = HAL_GetTick();
      do {
        BSP_TS_GetState(&State);
        HAL_Delay(10);
        if (State.TouchDetected != Pressed) 
        {
          break;
        } else if ((HAL_GetTick() - 100) > TimeStart) 
        {
          return;
        }
      } while (1);
    }
  } while (1);
}

/**
  * @brief  Calibrate X position
  * @param  x : X position
  * @retval Calibrated x
  */
uint16_t Calibration_GetX(uint16_t x)
{
  return (((A1 * x) + B1)/1000);
}

/**
  * @brief  Calibrate Y position
  * @param  y : Y position
  * @retval Calibrated y
  */
uint16_t Calibration_GetY(uint16_t y)
{
  return (((A2 * y) + B2)/1000);
}

/**
  * @brief  check if the TS is calibrated
  * @param  None
  * @retval Calibration state (1 : calibrated / 0: no)
  */ 
uint8_t IsCalibrationDone(void)
{
  return (Calibration_Done);
}

