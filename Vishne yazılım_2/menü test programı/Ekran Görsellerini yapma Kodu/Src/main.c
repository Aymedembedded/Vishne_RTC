/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "fonts.h"
#include "testimg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SCREENCOOR_X 240
#define SCREENCOOR_Y 320

#define EEPROMBLOCKNUMBER 256

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
int count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
int i2a(char *s, int n);
char* my_itoa(char *output_buff, int num);
void CalScreen1(void);
void CalScreen2(void);
void CalScreen3(void);
void CalScreen4(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t	id;

 uint16_t ImageBuffer1[4950];
uint32_t READ_ADRESS = 0x20000080;
char sayi = 80;
char patientCntVal[2];
///metin[] = "Merhaba C." ;
int a , l ;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
patientCntVal[0]=80;
patientCntVal[1]=81;
	    int number = -254;
    char string[12];
	my_itoa(string, number);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	
			W25qxx_Init();
			ILI9341_Unselect();
			ILI9341_Init();
			
			
			
			//ILI9341_WriteString(15,15,"brk",Font_11x18,ILI9341_BLACK,ILI9341_BLUE);
			//ILI9341_DrawImage(0, 0, 240, 65, (const uint16_t*)image_data_aymedLogo);
			for(count = 1; count <= EEPROMBLOCKNUMBER; count++)
			{
				W25qxx_EraseBlock(count);
			}
			W25qxx_EraseChip();
			//ILI9341_FillScreen(ILI9341_BLUE);
			
//			W25qxx_EraseBlock(1);
//			W25qxx_EraseBlock(2);
//			W25qxx_EraseBlock(3);
//			W25qxx_EraseBlock(4);
//			W25qxx_EraseBlock(5);
//			W25qxx_EraseBlock(6);
//			W25qxx_WriteBlock((uint8_t *)main_screen1,1,0,12000);
//			W25qxx_WriteBlock((uint8_t *)main_screen2,2,0,12000);
//			W25qxx_WriteBlock((uint8_t *)main_screen3,3,0,12000);
//			W25qxx_WriteBlock((uint8_t *)main_screen4,4,0,12000);
//			W25qxx_WriteBlock((uint8_t *)main_screen5,5,0,12000);
//			W25qxx_WriteBlock((uint8_t *)main_screen6,6,0,12000);
////			
//			W25qxx_EraseBlock(7);
//			W25qxx_EraseBlock(8);
//			W25qxx_EraseBlock(9);
//			W25qxx_EraseBlock(10);
//			W25qxx_EraseBlock(11);
//			W25qxx_EraseBlock(12);
//			W25qxx_WriteBlock((uint8_t *)test_screen1,7,0,12000);
//			W25qxx_WriteBlock((uint8_t *)test_screen2,8,0,12000);
//			W25qxx_WriteBlock((uint8_t *)test_screen3,9,0,12000);
//			W25qxx_WriteBlock((uint8_t *)test_screen4,10,0,12000);
//			W25qxx_WriteBlock((uint8_t *)test_screen5,11,0,12000);
//			W25qxx_WriteBlock((uint8_t *)test_screen6,12,0,12000);			
		
//			W25qxx_EraseBlock(13);
//			W25qxx_EraseBlock(14);
//			W25qxx_EraseBlock(15);
//			W25qxx_EraseBlock(16);
//			W25qxx_WriteBlock((uint8_t *)result_screen1,13,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen2,14,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen3,15,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen4,16,0,12000);

//			W25qxx_EraseBlock(17);
//			W25qxx_EraseBlock(18);
//			W25qxx_EraseBlock(19);
//			W25qxx_EraseBlock(20);
//			W25qxx_EraseBlock(21);
//			W25qxx_WriteBlock((uint8_t *)result_screen5,17,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen6,18,0,12000);	
//			W25qxx_WriteBlock((uint8_t *)result_screen7,19,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen8,20,0,12000);
//			W25qxx_WriteBlock((uint8_t *)result_screen9,21,0,12000);


//			W25qxx_EraseBlock(22);
//			W25qxx_EraseBlock(23);
//			W25qxx_EraseBlock(24);
//			W25qxx_EraseBlock(25);

//			W25qxx_WriteBlock((uint8_t *)set_screen1,22,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen2,23,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen3,24,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen4,25,0,12000);
			
			
//			W25qxx_EraseBlock(26);
//			W25qxx_EraseBlock(27);
//			W25qxx_EraseBlock(28);
//			W25qxx_EraseBlock(29);
//			W25qxx_EraseBlock(28);
//			W25qxx_EraseBlock(29);
//			W25qxx_EraseBlock(30);
//			W25qxx_EraseBlock(31);			
//			W25qxx_WriteBlock((uint8_t *)set_screen5,26,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen6,27,0,12000);	
//			W25qxx_WriteBlock((uint8_t *)set_screen7,28,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen8,29,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen9,30,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_screen10,31,0,12000);


//			W25qxx_EraseBlock(32);
//			W25qxx_EraseBlock(33);
//			W25qxx_EraseBlock(34);
//			W25qxx_EraseBlock(35);
//			W25qxx_EraseBlock(36);
//			W25qxx_EraseBlock(37);
//			W25qxx_EraseBlock(38);
//			W25qxx_WriteBlock((uint8_t *)set_date1,32,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_date2,33,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_date3,34,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_date4,35,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_date5,36,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_date6,37,0,12000);	
//			W25qxx_WriteBlock((uint8_t *)set_date7,38,0,12000);




//			W25qxx_EraseBlock(39);
//			W25qxx_EraseBlock(40);
//			W25qxx_EraseBlock(41);
//			W25qxx_EraseBlock(42);
//			W25qxx_EraseBlock(43);
//			W25qxx_WriteBlock((uint8_t *)set_hour1,39,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_hour2,40,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_hour3,41,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_hour4,42,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_hour5,43,0,12000);




//			W25qxx_EraseBlock(44);
//			W25qxx_EraseBlock(45);
//			W25qxx_EraseBlock(46);
//			W25qxx_EraseBlock(47);
//			W25qxx_WriteBlock((uint8_t *)set_back_buttons1,44,0,12000);
//			W25qxx_WriteBlock((uint8_t *)set_back_buttons2,45,0,12000);
//			W25qxx_WriteBlock((uint8_t *)apply_back_but1,46,0,12000);
//			W25qxx_WriteBlock((uint8_t *)apply_back_but2,47,0,12000);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			W25qxx_EraseBlock(48);
//			W25qxx_EraseBlock(49);
//			W25qxx_EraseBlock(50);
//			W25qxx_EraseBlock(51);

//			W25qxx_WriteBlock((uint8_t *)caribration1,48,0,12000);
//			W25qxx_WriteBlock((uint8_t *)caribration2,49,0,12000);
//			W25qxx_WriteBlock((uint8_t *)caribration3,50,0,12000);			
//			W25qxx_WriteBlock((uint8_t *)caribration4,51,0,12000);


//			W25qxx_EraseBlock(52);
//			W25qxx_EraseBlock(53);
//			W25qxx_EraseBlock(54);
//			W25qxx_EraseBlock(55);
//			W25qxx_WriteBlock((uint8_t *)caribration5,52,0,12000);	
//			W25qxx_WriteBlock((uint8_t *)caribration6,53,0,12000);
//			W25qxx_WriteBlock((uint8_t *)caribration7,54,0,12000);
//			W25qxx_WriteBlock((uint8_t *)caribration8,55,0,12000);


//			W25qxx_EraseBlock(56);
//			W25qxx_EraseBlock(57);
//			W25qxx_EraseBlock(58);
//			W25qxx_EraseBlock(59);
//			W25qxx_WriteBlock((uint8_t *)calibration22,56,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration23,57,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration24,58,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration25,59,0,12000);





//			W25qxx_EraseBlock(60);
//			W25qxx_EraseBlock(61);
//			W25qxx_EraseBlock(62);
//			W25qxx_EraseBlock(63);
//			W25qxx_WriteBlock((uint8_t *)calibration32,60,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration33,61,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration34,62,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calibration35,63,0,12000);






//			W25qxx_EraseBlock(64);
//			W25qxx_EraseBlock(65);
//			W25qxx_EraseBlock(66);
//			W25qxx_EraseBlock(67);
//			W25qxx_WriteBlock((uint8_t *)calComplated2,64,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calComplated3,65,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calComplated4,66,0,12000);
//			W25qxx_WriteBlock((uint8_t *)calComplated5,67,0,12000);

/*
			W25qxx_EraseBlock(68);
			W25qxx_EraseBlock(69);
			W25qxx_EraseBlock(70);
			W25qxx_EraseBlock(71);
			W25qxx_EraseBlock(72);
			W25qxx_EraseBlock(73);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik1,68,0,12000);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik2,69,0,12000);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik3,70,0,12000);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik4,71,0,12000);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik5,72,0,12000);
			W25qxx_WriteBlock((uint8_t *)image_data_grafik6,73,0,10560);
*/			
			
CalScreen1();
HAL_Delay(1000);
CalScreen2();
HAL_Delay(1000);
CalScreen3();
HAL_Delay(1000);
CalScreen4();
//mainScreen();
//HAL_Delay(1000);
//ILI9341_FillScreen(ILI9341_BLUE);
//testScreen();
//HAL_Delay(1000);
//ILI9341_FillScreen(ILI9341_BLUE);
//resultScreen ();
//HAL_Delay(1000);
//ILI9341_FillScreen(ILI9341_BLUE);
//settingScreen ();
//HAL_Delay(1000);
//ILI9341_FillScreen(ILI9341_BLUE);
//setDateScreen ();
//HAL_Delay(1000);
//ILI9341_FillScreen(ILI9341_BLUE);
//setHourScreen ();


//			ILI9341_DrawImage(125, 100, 110, 135, (const uint16_t*)image_data_memory_button);
//			ILI9341_DrawImage(187, 250, 48, 60, (const uint16_t*)image_data_settings_button);
//			ILI9341_DrawImage(5, 100, 110, 135, (const uint16_t*)image_data_new_test_button);
//			ILI9341_DrawImage(125, 100, 110, 135, (const uint16_t*)image_data_reTest_button);
			
//ILI9341_WriteString(120, 120,"Tdd", Ubuntu, ILI9341_WHITE, ILI9341_BLUE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, ILI9341_DC_Pin|ILI9341_RES_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ILI9341_DC_Pin ILI9341_RES_Pin */
  GPIO_InitStruct.Pin = ILI9341_DC_Pin|ILI9341_RES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : FLASH_CS_Pin */
  GPIO_InitStruct.Pin = FLASH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FLASH_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ILI9341_CS_Pin */
  GPIO_InitStruct.Pin = ILI9341_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ILI9341_CS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int i2a(char *s, int n){
    div_t qr;
    int pos;

    if(n == 0) return 0;

    qr = div(n, 10);
    pos = i2a(s, qr.quot);
    s[pos] = qr.rem + '0';
    return pos + 1;
}

char* my_itoa(char *output_buff, int num){
    char *p = output_buff;
    if(num < 0){
        *p++ = '-';
        num *= -1;
    } else if(num == 0)
        *p++ = '0';
    p[i2a(p, num)]='\0';
    return output_buff;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
