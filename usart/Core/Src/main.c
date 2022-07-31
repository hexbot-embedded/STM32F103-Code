/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../Hardware/usart/usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
int check_sw();
void LED_ALL(uint8_t a);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1);//��������2�����ж�
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if(USART2_RX_STA!=0)
      {
    	  int receive = USART2_RX_BUF[0] - 48;
    	  if(receive == 1||receive == 2||receive == 3||receive == 4)
    	  {
        	  LED_ALL(1);
        	  HAL_Delay(receive*100);
        	  LED_ALL(0);
        	  HAL_Delay(receive*100);
        	  LED_ALL(1);
    		  HAL_Delay(receive*100);
    		  LED_ALL(0);
    		  HAL_Delay(receive*100);
    	  }
    	  USART2_RX_STA=0;//�����־λ
      }
      int check = check_sw();
      if(check == 1||check == 2||check == 3||check == 4)
      {
    	  LED_ALL(1);
    	  HAL_Delay(check*100);
    	  LED_ALL(0);
    	  HAL_Delay(check*100);
    	  LED_ALL(1);
		  HAL_Delay(check*100);
		  LED_ALL(0);
		  HAL_Delay(check*100);
		  switch(check)
		  {
		  case 1:
			  HAL_UART_Transmit(&huart2,(uint8_t*)&"1\r\n",3,0xffff);
		  case 2:
			  HAL_UART_Transmit(&huart2,(uint8_t*)&"2\r\n",3,0xffff);
		  case 3:
			  HAL_UART_Transmit(&huart2,(uint8_t*)&"3\r\n",3,0xffff);
		  case 4:
			  HAL_UART_Transmit(&huart2,(uint8_t*)&"4\r\n",3,0xffff);
		  }
      }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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

  /** Initializes the CPU, AHB and APB buses clocks
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED16_Pin|LED15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED13_Pin|LED14_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED17_Pin|LED12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED16_Pin LED15_Pin */
  GPIO_InitStruct.Pin = LED16_Pin|LED15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SW4_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SW4_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED13_Pin LED14_Pin */
  GPIO_InitStruct.Pin = LED13_Pin|LED14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LED17_Pin LED12_Pin */
  GPIO_InitStruct.Pin = LED17_Pin|LED12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin SW1_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//check which sw is pressed
int check_sw(){
	//check if sw1 is pressed
	if(HAL_GPIO_ReadPin(GPIOD, SW1_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, SW1_Pin)){
			return 1;
		}
	}

	//check if sw2 is pressed
	if(HAL_GPIO_ReadPin(GPIOD, SW2_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, SW2_Pin)){
			return 2;
		}
	}

	//check if sw3 is pressed
	if(HAL_GPIO_ReadPin(GPIOB, SW3_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOB, SW3_Pin)){
			return 3;
		}
	}

	//check if sw4 is pressed
	if(HAL_GPIO_ReadPin(GPIOB, SW4_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOB, SW4_Pin)){
			return 4;
		}
	}
	return 0;
}

void LED_ALL(uint8_t a)//LED1�������ƺ�����0ΪϨ������ֵΪ������
{
	if(a)
	{
		HAL_GPIO_WritePin(GPIOC,LED12_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD,LED13_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD,LED14_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,LED15_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,LED16_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,LED17_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC,LED12_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,LED13_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,LED14_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE,LED15_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE,LED16_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,LED17_Pin,GPIO_PIN_RESET);
	}
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
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */