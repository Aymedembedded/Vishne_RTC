

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "touchscreen.h"
#include "system.h"
#include "display.h"

/* Includes ------------------------------------------------------------------*/
//#include "stm32f429i_discovery_ts.h"
//#include "stm32f429i_discovery_io.h"

/* Includes ------------------------------------------------------------------*/
//#include "stm32f429i_discovery.h"


  /**
  * @brief STM32F429I DISCO BSP Driver version number V2.1.6
  */
#define __STM32F429I_DISCO_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32F429I_DISCO_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32F429I_DISCO_BSP_VERSION_SUB2   (0x06) /*!< [15:8]  sub2 version */
#define __STM32F429I_DISCO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F429I_DISCO_BSP_VERSION        ((__STM32F429I_DISCO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F429I_DISCO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F429I_DISCO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F429I_DISCO_BSP_VERSION_RC)) 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_Variables STM32F429I DISCOVERY LOW LEVEL Private Variables
  * @{
  */ 

uint32_t I2cxTimeout = I2Cx_TIMEOUT_MAX; /*<! Value of Timeout when I2C communication fails */  

I2C_HandleTypeDef I2cHandle;
//2C_HandleTypeDef hi2c2;

/**
  * @}
  */ 

/** @defgroup STM32F429I_DISCOVERY_LOW_LEVEL_Private_FunctionPrototypes STM32F429I DISCOVERY LOW LEVEL Private FunctionPrototypes
  * @{
  */ 
/* I2Cx bus function */
static void               I2Cx_Init(void);
static void               I2Cx_ITConfig(void);
static void               I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value);
static void               I2Cx_WriteBuffer(uint8_t Addr, uint8_t Reg,  uint8_t *pBuffer, uint16_t Length);
static uint8_t            I2Cx_ReadData(uint8_t Addr, uint8_t Reg);
static uint8_t            I2Cx_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
static void               I2Cx_Error(void);
static void               I2Cx_MspInit(I2C_HandleTypeDef *hi2c);  

/* IOExpander IO functions */
void                      IOE_Init(void);
void                      IOE_ITConfig(void);
void                      IOE_Delay(uint32_t Delay);
void                      IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t                   IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t                  IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);
void                      IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);


/**
  * @brief  This method returns the STM32F429I DISCO BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F429I_DISCO_BSP_VERSION;
}

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/

/**
  * @brief  I2Cx MSP Initialization
  * @param  hi2c: I2C handle
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;  

  if (hi2c->Instance ==I2C2)
  {
    /* Configure the GPIOs ---------------------------------------------------*/ 
    /* Enable GPIO clock */
    DISCOVERY_I2Cx_SDA_GPIO_CLK_ENABLE();
    DISCOVERY_I2Cx_SCL_GPIO_CLK_ENABLE();
      
    /* Configure I2C Tx as alternate function  */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
      
    /* Configure I2C Rx as alternate function  */
//    GPIO_InitStruct.Pin = DISCOVERY_I2Cx_SDA_PIN;
//    HAL_GPIO_Init(DISCOVERY_I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
    
    
    /* Configure the Discovery I2Cx peripheral -------------------------------*/ 
    /* Enable I2C3 clock */
    __HAL_RCC_I2C2_CLK_ENABLE();
    
    /* Force the I2C Peripheral Clock Reset */  
    DISCOVERY_I2Cx_FORCE_RESET();
      
    /* Release the I2C Peripheral Clock Reset */  
    DISCOVERY_I2Cx_RELEASE_RESET(); 
    
    /* Enable and set Discovery I2Cx Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);
    
    /* Enable and set Discovery I2Cx Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn);  

  }
}

/**
  * @brief  I2Cx Bus initialization.
  */
static void I2Cx_Init(void)
{
  /* USER CODE END I2C2_Init 1 */
  I2cHandle.Instance = I2C2;
  I2cHandle.Init.Timing = 0x2000090E;
  I2cHandle.Init.OwnAddress1 = 0;
  I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2 = 0;
  I2cHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&I2cHandle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&I2cHandle, 0) != HAL_OK)
  {
    Error_Handler();
  }
    I2Cx_MspInit(&I2cHandle);
    HAL_I2C_Init(&I2cHandle);
  
}

/**
  * @brief  Configures Interruption pin for I2C communication.
  */
static void I2Cx_ITConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
    
  /* Enable the GPIO EXTI Clock */
  STMPE811_INT_CLK_ENABLE();
  
  GPIO_InitStruct.Pin   = STMPE811_INT_PIN;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
  HAL_GPIO_Init(STMPE811_INT_GPIO_PORT, &GPIO_InitStruct);
    
  /* Enable and set GPIO EXTI Interrupt to the highest priority */
  HAL_NVIC_SetPriority((IRQn_Type)(STMPE811_INT_EXTI), 0x0F, 0x00);
  HAL_NVIC_EnableIRQ((IRQn_Type)(STMPE811_INT_EXTI));
}

/**
  * @brief  Writes a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written 
  */
static void I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value)
  {
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout); 
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }        
}

/**
  * @brief  Writes a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  */
static void I2Cx_WriteBuffer(uint8_t Addr, uint8_t Reg,  uint8_t *pBuffer, uint16_t Length)
  {
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, I2cxTimeout); 

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  }        
}

/**
  * @brief  Reads a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @retval Data read at register address
  */
static uint8_t I2Cx_ReadData(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;
  
  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2cxTimeout);
 
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();
  
  }
  return value;
}

/**
  * @brief  Reads multiple data on the BUS.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to read data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
static uint8_t I2Cx_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, I2cxTimeout);
  
  /* Check the communication status */
  if(status == HAL_OK)
  {
    return 0;
  }
  else
  {
    /* Re-Initialize the BUS */
    I2Cx_Error();

    return 1;
  }
}


/**
  * @brief  I2Cx error treatment function
  */
static void I2Cx_Error(void)
{
  /* De-initialize the SPI communication BUS */
  HAL_I2C_DeInit(&I2cHandle);
  
  /* Re-Initialize the SPI communication BUS */
  I2Cx_Init();
}


/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

/********************************* LINK IOE ***********************************/

/**
  * @brief  IOE Low Level Initialization.
  */
 void IOE_Init(void) 
{
  I2Cx_Init();
}

/**
  * @brief  IOE Low Level Interrupt configuration.
  */
void IOE_ITConfig(void)
{
  I2Cx_ITConfig();
}

/**
  * @brief  IOE Writes single data operation.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  Value: Data to be written
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(Addr, Reg, Value);
}

/**
  * @brief  IOE Reads single data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @retval The read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_ReadData(Addr, Reg);
}

/**
  * @brief  IOE Writes multiple data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to data buffer
  * @param  Length: length of the data
  */
void IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
  I2Cx_WriteBuffer(Addr, Reg, pBuffer, Length);
}

/**
  * @brief  IOE Reads multiple data.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  pBuffer: pointer to data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
 return I2Cx_ReadBuffer(Addr, Reg, pBuffer, Length);
}

/**
  * @brief  IOE Delay.
  * @param  Delay in ms
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/*****************************************************************************************************************************************************************************************************************************************************************/

/** @defgroup STM32F429I_DISCOVERY_TS_Private_Variables STM32F429I DISCOVERY TS Private Variables
  * @{
  */
static TS_DrvTypeDef     *TsDrv;
static uint16_t          TsXBoundary, TsYBoundary; 


/**
  * @brief  Initializes and configures the touch screen functionalities and 
  *         configures all necessary hardware resources (GPIOs, clocks..).
  * @param  XSize: The maximum X size of the TS area on LCD
  * @param  YSize: The maximum Y size of the TS area on LCD  
  * @retval TS_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t XSize, uint16_t YSize)
{
  uint8_t ret = TS_ERROR;

  /* Initialize x and y positions boundaries */
  TsXBoundary = XSize;
  TsYBoundary = YSize;

  /* Read ID and verify if the IO expander is ready */
  if(stmpe811_ts_drv.ReadID(TS_I2C_ADDRESS) == STMPE811_ID)
  {
    /* Initialize the TS driver structure */
    TsDrv = &stmpe811_ts_drv;

    ret = TS_OK;
  }

  if(ret == TS_OK)
  {
    /* Initialize the LL TS Driver */
    TsDrv->Init(TS_I2C_ADDRESS);
    TsDrv->Start(TS_I2C_ADDRESS);
  }

  return ret;
}

/**
  * @brief  Configures and enables the touch screen interrupts.
  * @retval TS_OK: if ITconfig is OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{
  /* Enable the TS ITs */
  TsDrv->EnableIT(TS_I2C_ADDRESS);

  return TS_OK;
}

/**
  * @brief  Gets the TS IT status.
  * @retval Interrupt status.
  */  
uint8_t BSP_TS_ITGetStatus(void)
{
  /* Return the TS IT status */
  return (TsDrv->GetITStatus(TS_I2C_ADDRESS));
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TsState: Pointer to touch screen current state structure
  */
void BSP_TS_GetState(TS_StateTypeDef* TsState)
{
  static uint32_t _x = 0, _y = 0;
  uint16_t xDiff, yDiff , x , y, xr, yr;
  
  TsState->TouchDetected = TsDrv->DetectTouch(TS_I2C_ADDRESS);
  
  if(TsState->TouchDetected)
  {
    TsDrv->GetXY(TS_I2C_ADDRESS, &x, &y);
    
    /* Y value first correction */
    y -= 360;  
    
    /* Y value second correction */
    yr = y / 11;
    
    /* Return y position value */
    if(yr <= 0)
    {
      yr = 0;
    }
    else if (yr > TsYBoundary)
    {
      yr = TsYBoundary - 1;
    }
    else
    {}
    y = yr;
    
    /* X value first correction */
    if(x <= 3000)
    {
      x = 3870 - x;
    }
    else
    {
      x = 3800 - x;
    }
    
    /* X value second correction */  
    xr = x / 15;
    
    /* Return X position value */
    if(xr <= 0)
    {
      xr = 0;
    }
    else if (xr > TsXBoundary)
    {
      xr = TsXBoundary - 1;
    }
    else 
    {}
    
    x = xr;
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y); 
    
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y; 
    }
    
    /* Update the X position */
    TsState->X = _x;
    
    /* Update the Y position */  
    TsState->Y = _y;
  }
}

/**
  * @brief  Clears all touch screen interrupts.
  */  
void BSP_TS_ITClear(void)
{
	
	
	
  /* Clear TS IT pending bits */
  TsDrv->ClearIT(TS_I2C_ADDRESS); 
}













/**************************************************************************************************************************************************************************************************************************************************************
Touch Screen.c
***************************************************************************************************************************************************************************************************************************************************************/
/* Private variables ---------------------------------------------------------*/
static TS_StateTypeDef  TS_State;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void Touchscreen_demo(void)
{ 
		

  uint8_t status = 0;
  uint16_t x,y;
  uint8_t state = 0;
  
  if(IsCalibrationDone() == 0)
  {
    Touchscreen_Calibration();
  }
  
  //Touchscreen_SetHint();
  
  status = BSP_TS_Init(240, 320);
  
  if (status != TS_OK)
  {
////////
  }
  else
  {
////////
  }
  
  while (PowerState != PowerST_OFF)
  {
		batteryLevel();
		getCalender();
		CheckPushBt();
    if (status == TS_OK)
    {
			//BuzzerBip();
      BSP_TS_GetState(&TS_State);
      
      if (TS_State.TouchDetected) 
				{
        x = Calibration_GetX(TS_State.X);
        y = Calibration_GetY(TS_State.Y);
				HAL_Delay(1);
				sleepCounterReset();
 /*Mainscreen display************************************************************/					
				if(displayState == MainScreen)
				{
					
					if((y >95)&& (y < 170)&& (x>10)&& (x < 230) )//new test button
					{
						BuzzerBip();
						testIntroDisplay();
						getpatientNum();
						displayState = IntroTestScreen;

					}

					else if((y >185)&& (y < 235)&& (x>10)&& (x < 230) )//memory button
					{
						BuzzerBip();    
						MemoryDisplay();

					}
					
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230))//Settings button
					{
						BuzzerBip();
						SettingsDisplay();

					}
					else if((y >0)&& (y <50)&& (x>0)&& (x < 70))//Shutdonw button
					{
//						BuzzerBip();
//						HAL_Delay(500);
//						BuzzerBip();
//						HAL_Delay(500);
//						BuzzerBip();
//						HAL_Delay(500);
//						POWER_OFF
					}
				}	
 /*End of Test screen display************************************************************/				
				else if(displayState == EndOfTestScreen)
				{
				
					if((y >180)&& (y < 240)&& (x>10)&& (x < 115))//save test button
					{
						BuzzerBip();
						SaveSpectrumToSector();
						writeCalendertoMemory();
						writeBilirubintoMemory(BilResult[0]);
//						savePatient();
//						readPatient();
//						getpatientNum();
						
						testSavedDisplay();
						mainScreenDisplay();

					}
					
					else if((y >180)&& (y < 240)&& (x>126)&& (x < 230) )//retest button
					{

						BuzzerBip();
						testIntroDisplay();
						getpatientNum();
						displayState = BackToTheEndOfTestScreen;
					}
					
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();

					}
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//detail button
					{
						BuzzerBip();
						DetailScreen();

					}

					
				}
				
/*BackToTheEndOfTestScreen**********************************************************/
				
else if(displayState == BackToTheEndOfTestScreen)
				{
					if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();		

					}
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230))//Back button
					{
						BuzzerBip();
						testScreenDisplay();		

					}
					else if((y >210)&& (y < 235)&& (x>50)&& (x < 200))//Keyboard
					{
//						BuzzerBip();
//						keyboard();
					}
				}
/*Detail screen display************************************************************/				
				else if(displayState == DetlScreen)
				{
					if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();

					}
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//detail button
					{
						BuzzerBip();
						testScreenDisplay();

					}
				}				
/*Test Intro screen display************************************************************/				
				else if(displayState == IntroTestScreen)
				{
					if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();		

					}
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230))//Back button
					{
						BuzzerBip();
						mainScreenDisplay ();		

					}
					else if((y >210)&& (y < 235)&& (x>50)&& (x < 200))//Keyboard
					{
//						BuzzerBip();
//						keyboard();
					}
				}
/*Keyboard screen display************************************************************/				
				else if(displayState == KeyBoardScreen)
				{
					if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						testIntroDisplay();

					}
				}	

/*MemDetail screen display************************************************************/				
				else if(displayState == MemDetlScreen)
				{
					 if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						ILI9341_FillScreen(ILI9341_BLUE);
						ILI9341_DrawImage(0, 0, 240, 65, (const uint16_t*)image_data_aymedLogo);
						mainScreenDisplay ();		

					}	
					
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//detail button
					{
						BuzzerBip();
						MemoryDisplay();

					}
				}						
/*Memory screen display************************************************************/	
				else if(displayState == MemoryScreen)
				{
					
					if((y >40)&& (y < 80)&& (x>190)&& (x < 230) )//- button
					{	
						BuzzerBip();
						pageNumber = (pageNumber == 1) ? totalPageNumber : (pageNumber - 1);
						
						memoryPageDisplay(pageNumber);
	/*					if( memNo > 1 && memPos > 1 && memPos <= 5){
							memNo --;
							memPos --;
						}
						else if( memNo > 1 && memPos == 1){
							memNo --;
							memPos = 1;
								while(PTNi <= 5){
										sprintf(displayBuff,"%u.",memNo+PTNi-1);
										ILI9341_WriteString(20, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
										sprintf(displayBuff,"OLCUM");
										ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
										sprintf(displayBuff,"measureNum: %u",measurementNumber);
										ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);

										PTNi++;
							}
						PTNi=1;
						}*/
					}		

					
					if((y >205)&& (y < 245)&& (x>190)&& (x < 230) )//+ button
					{	
						BuzzerBip();
						pageNumber = (pageNumber == totalPageNumber) ? 1 : (pageNumber + 1);
						
						
						memoryPageDisplay(pageNumber);
/*						if( memNo < TotPatNo && memPos >= 1 && memPos < 5){
							memNo ++;
							memPos ++;
						}
						else if( memNo < TotPatNo && memPos == 5){
							memNo ++;
							memPos = 5;	
							while(PTNi <= 5){	
										sprintf(displayBuff,"%u.",memNo+PTNi-1);
										ILI9341_WriteString(20, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
										sprintf(displayBuff,"OLCUM",readPtn.patient.id[0]);
										ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);
										sprintf(displayBuff,"measureNum: %u",measurementNumber);
										ILI9341_WriteString(60, (PTNi*40)+((PTNi-1)*5),displayBuff, Font_11x18, ILI9341_BLUE, ILI9341_WHITE);

									PTNi++;
							}
						PTNi=1;
	
						}*/
					}

					else if((y >30)&& (y < 60)&& (x>10)&& (x < 185) )// Choose one of the measurements
					{
						BuzzerBip();
						memNo = 5 * pageNumber - 4; 
						
						if(redBarFlag[1] == true)
							Draw_rectangle(10, 75, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[2] == true)
							Draw_rectangle(10, 120, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[3] == true)
							Draw_rectangle(10, 165, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[4] == true)
							Draw_rectangle(10, 210, 175, 35, ILI9341_WHITE, 5);
						Draw_rectangle(10, 30, 175, 35, ILI9341_RED, 5);
						redBarFlag[0] = true; redBarFlag[1] = false; redBarFlag[2] = false; redBarFlag[3] = false; redBarFlag[4] = false;
						
					}
					else if((y >75)&& (y < 105)&& (x>10)&& (x < 185) )// Choose one of the measurements
					{
						BuzzerBip();
						memNo = 5 * pageNumber - 3;
						if(redBarFlag[0] == true)
							Draw_rectangle(10, 30, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[2] == true)
							Draw_rectangle(10, 120, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[3] == true)
							Draw_rectangle(10, 165, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[4] == true)
							Draw_rectangle(10, 210, 175, 35, ILI9341_WHITE, 5);
						Draw_rectangle(10, 75, 175, 35, ILI9341_RED, 5);
						redBarFlag[0] = false; redBarFlag[1] = true; redBarFlag[2] = false; redBarFlag[3] = false; redBarFlag[4] = false;
						
					}		
					else if((y >120)&& (y < 150)&& (x>10)&& (x < 185) )// Choose one of the measurements
					{
						BuzzerBip();
						memNo = 5 * pageNumber - 2;
						if(redBarFlag[1] == true)
							Draw_rectangle(10, 75, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[0] == true)
							Draw_rectangle(10, 30, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[3] == true)
							Draw_rectangle(10, 165, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[4] == true)
							Draw_rectangle(10, 210, 175, 35, ILI9341_WHITE, 5);
						Draw_rectangle(10, 120, 175, 35, ILI9341_RED, 5);
						redBarFlag[0] = false; redBarFlag[1] = false; redBarFlag[2] = true; redBarFlag[3] = false; redBarFlag[4] = false;
						
					}
					else if((y >165)&& (y < 195)&& (x>10)&& (x < 185) )// Choose one of the measurements
					{
						BuzzerBip();
						memNo = 5 * pageNumber - 1;
						if(redBarFlag[1] == true)
							Draw_rectangle(10, 75, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[2] == true)
							Draw_rectangle(10, 120, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[0] == true)
							Draw_rectangle(10, 30, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[4] == true)
							Draw_rectangle(10, 210, 175, 35, ILI9341_WHITE, 5);
						Draw_rectangle(10, 165, 175, 35, ILI9341_RED, 5);
						redBarFlag[0] = false; redBarFlag[1] = false; redBarFlag[2] = false; redBarFlag[3] = true; redBarFlag[4] = false;
						
					}
					else if((y >210)&& (y < 240)&& (x>10)&& (x < 185) )// Choose one of the measurements
					{
						BuzzerBip();
						memNo = 5 * pageNumber;
						if(redBarFlag[1] == true)
							Draw_rectangle(10, 75, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[2] == true)
							Draw_rectangle(10, 120, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[3] == true)
							Draw_rectangle(10, 165, 175, 35, ILI9341_WHITE, 5);
						if(redBarFlag[0] == true)
							Draw_rectangle(10, 30, 175, 35, ILI9341_WHITE, 5);
						Draw_rectangle(10, 210, 175, 35, ILI9341_RED, 5);
						redBarFlag[0] = false; redBarFlag[1] = false; redBarFlag[2] = false; redBarFlag[3] = false; redBarFlag[4] = true;
						
					}											
					
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						ILI9341_DrawImage(0, 0, 240, 65, (const uint16_t*)image_data_aymedLogo);
						mainScreenDisplay ();
					}
					
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//detail button
					{
						BuzzerBip();
						MemDetailScreen();
					}
					
	/*				if(memPos<=5 && displayState==MemoryScreen){
						if(memPos<5){
							Draw_rectangle(10,((memPos+1)* 30)+(15*memPos),175,35,ILI9341_WHITE,5);
						}
						if(memPos>1){
							Draw_rectangle(10,((memPos-1)* 30)+(15*(memPos-2)),175,35,ILI9341_WHITE,5);
						}

						Draw_rectangle(10,(memPos* 30)+(15*(memPos-1)),175,35,ILI9341_RED,5);
						
						sprintf(displayBuff," ^ ");
						ILI9341_WriteString(190, 50, displayBuff, Font_16x26, ILI9341_RED, ILI9341_YELLOW);
						sprintf(displayBuff," v ");
						ILI9341_WriteString(190, 215, displayBuff, Font_16x26, ILI9341_RED, ILI9341_YELLOW);
					}*/
				


				}
/*Erase Memory screen display************************************************************/	
				else if(displayState == DltMemScreen)
				{
					if((y >100)&& (y < 150)&& (x>10)&& (x < 230) )//Erase memory button
					{	
						BuzzerBip();
						/* Spectrometer Videodata deletion for every measurements*/
						if(StartMem+measurementNumber <= EndMem)
							EraseSectors(StartMem,StartMem+measurementNumber);
						/* 2*(4096bytes / 6bytes) = nearly 1365 dates and Time memory deletion*/
						W25qxx_EraseSector(eepromMemoryinSector-1);
						W25qxx_EraseSector(eepromMemoryinSector-2);
						/* Bilirubin values deletion */
						W25qxx_EraseSector(eepromMemoryinSector-3);
						SettingsDisplay();
					}
					else if((y >185)&& (y < 235)&& (x>10)&& (x < 230) )//Give up button button
					{
						BuzzerBip();
						SettingsDisplay();
					}
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						SettingsDisplay();
					}					
				}
				
/*Settings screen display************************************************************/
				else if(displayState == SettingsScreen)
				{
					if((y >95)&& (y < 135)&& (x>10)&& (x < 120) )//Date button
					{	
						BuzzerBip();
						setDateScreen();
						setDateDsp();
						
					}
					else if((y >95)&& (y < 135)&& (x>120)&& (x < 230))//Hour button
					{
						BuzzerBip();
						setTimeScreen();
						setTimeDsp();
					}
					else if((y >210)&& (y < 250)&& (x>10)&& (x < 230))//Calibration button
					{
						BuzzerBip();
						testCalDisplay();
						CalDisplay1();
					}		
					else if((y >153)&& (y < 193)&& (x>10)&& (x < 230) )//Data Settings Screen button
					{	
						BuzzerBip();
						dataSettings();
					}					
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();
					}
					
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();
					}	

				}
				
				
/* Data Transmitting Option Display***************************************************/
				else if(displayState == dataSettingsScreen)
				{
					/*klinik testlerde kullanilacak*/
				  if((y >100)&& (y < 150)&& (x>10)&& (x < 230) )//Send data button
					{	
						BuzzerBip();
						TransferData();
					}
					else if((y >185)&& (y < 235)&& (x>10)&& (x < 230) )//Clear memory button
					{
						BuzzerBip();
						DltMemDisplay();
					}
					else if((y >255)&& (y < 300)&& (x>130)&& (x < 230))//Back to data screen button
					{
						BuzzerBip();
						SettingsDisplay();
					}	
					
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						ILI9341_DrawImage(0, 0, 240, 65, (const uint16_t*)image_data_aymedLogo);
						mainScreenDisplay ();
					}				
				}
/*Set  Date screen display************************************************************/
				else if(displayState == SetDateScreen)
				{
					if((y >100)&& (y < 130)&& (x>10)&& (x < 65) )//day -
					{	
						
						if( day2  > 1 && day2  <= 31 ){
						BuzzerBip();
						day2--;
						setDateDsp();
						}
						else{
						day2 = 31;
						setDateDsp();
						}
						
					}
					else if((y >100)&& (y < 130)&& (x>175)&& (x < 230))//day +
					{
						if( day2  >= 1 && day2  <31 ){
						BuzzerBip();
						day2++;
						setDateDsp();
						}
						else{
						day2 = 1;
						setDateDsp();
						}
					}
					else if((y >145)&& (y < 175)&& (x>10)&& (x < 65))//month -
					{
						if( month2  > 1 && month2  <= 12 ){
							BuzzerBip();
						month2--;
						setDateDsp();
						}
						else{
						month2 = 12;
						setDateDsp();
						}
					}					
					else if((y >145)&& (y < 175)&& (x>175)&& (x < 230))//month +
					{
						if( month2  >= 1 && month2  < 12 ){
							BuzzerBip();
						month2++;
						setDateDsp();
						}
						else{
						month2 = 1;
						setDateDsp();
						}
					}	
					else if((y >190)&& (y < 220)&& (x>10)&& (x < 65))//year -
					{
						if( year2  > 0 && year2  <= 99 ){
							BuzzerBip();
						year2--;
						setDateDsp();
						}
						else{
						year2 = 99;
						setDateDsp();
						}
					}
					else if((y >190)&& (y < 220)&& (x>175)&& (x < 230))//year +
					{
						if( year2  >= 0 && year2  < 99 ){
							BuzzerBip();
							year2++;
							setDateDsp();
						}
						else{
							year2 = 0;
							setDateDsp();
						}
					}					
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();
						
					}
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230))//Apply button
					{
						BuzzerBip();
						setDate();
						mainScreenDisplay ();
						
					}						
				}

/*Set Hour screen display************************************************************/
				else if(displayState == SetHourScreen)
				{
					if((y >100)&& (y < 130)&& (x>10)&& (x < 65) )//hour -
					{	
						if( hour2  > 0 && hour2  <= 23 ){
							BuzzerBip();
						hour2--;
						setTimeDsp();
						}
						else{
						hour2 = 23;
						setTimeDsp();
						}
						
					}
					else if((y >100)&& (y < 130)&& (x>175)&& (x < 230))//hour +
					{
						if( hour2  >= 0 && hour2  < 23 ){
							BuzzerBip();
						hour2++;
						setTimeDsp();
						}
						else{
						hour2 = 0;
						setTimeDsp();
						}
					}
					else if((y >145)&& (y < 175)&& (x>10)&& (x < 65))//minute -
					{
						if( minute2  > 0 && minute2  <= 59 ){
							BuzzerBip();
						minute2--;
						setTimeDsp();
						}
						else{
						minute2 = 59;
						setTimeDsp();
						}	
					}					
					else if((y >145)&& (y < 175)&& (x>175)&& (x < 230))//minute +
					{
						if( minute2  >= 0 && minute2  < 59 ){
							BuzzerBip();
						minute2++;
						setTimeDsp();
						}
						else{
						minute2 = 0;
						setTimeDsp();
						}	
					}	
				
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay ();
					}
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230))//Apply button
					{
						BuzzerBip();
						setTime();
						mainScreenDisplay ();
					}						
				}


				
/*Calibration screen display************************************************************/
				else if(displayState == CalScreen1)
				{
					if((y >255)&& (y < 300)&& (x>140)&& (x < 230) )//next Button
					{	
						BuzzerBip();
						CalDisplay2();
					}
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay();
					}	
				}
/*BlackCalibration screen display************************************************************/
				else if(displayState == CalScreen22)
				{
					if((y >255)&& (y < 300)&& (x>140)&& (x < 230) )//next Button
					{	
						BuzzerBip();
						SaveBlcRef();
						CalDisplay3();
					}
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay();
					}	
				}		
/*WhiteCalibration screen display************************************************************/
				else if(displayState == CalScreen33)
				{
					if((y >255)&& (y < 300)&& (x>140)&& (x < 230) )//next Button
					{	
						BuzzerBip();
						SaveWhtRef();
						CalDisplay4();
					}
					else if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay();
					}						
				}		      
/*SaveBlcRef screen display************************************************************/
				else if(displayState == CalScreen4)
				{
					if((y >255)&& (y < 300)&& (x>10)&& (x < 100))//Back to main screen button
					{
						BuzzerBip();
						mainScreenDisplay();
					}
					else if((y >255)&& (y < 300)&& (x>140)&& (x < 230) )//next Button
					{	
						BuzzerBip();
						mainScreenDisplay();
					}					
				}				
						
			

				
			}
				
    }
    
    HAL_Delay(50);
  }
}


