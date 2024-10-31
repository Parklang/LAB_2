/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
uint8_t display_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t segments[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Định nghĩa các chân GPIO để điều khiển từng đoạn của LED
#define SEG_0 GPIO_PIN_0
#define SEG_1 GPIO_PIN_1
#define SEG_2 GPIO_PIN_2
#define SEG_3 GPIO_PIN_3
#define SEG_4 GPIO_PIN_4
#define SEG_5 GPIO_PIN_5
#define SEG_6 GPIO_PIN_6

void displayNumber(uint8_t num, uint8_t display) {
    uint8_t segment_value;

    if (num > 9) return;  // Giới hạn số hiển thị từ 0 đến 9

    segment_value = segments[num];

    // Cấu hình các đoạn 0-6 dựa trên giá trị số được chọn
    if (display == 1) {
        HAL_GPIO_WritePin(GPIOB, SEG_0, (segment_value & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_1, (segment_value & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_2, (segment_value & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_3, (segment_value & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_4, (segment_value & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_5, (segment_value & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, SEG_6, (segment_value & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    } else if (display == 2) {
        HAL_GPIO_WritePin(GPIOC, SEG_0, (segment_value & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_1, (segment_value & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_2, (segment_value & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_3, (segment_value & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_4, (segment_value & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_5, (segment_value & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, SEG_6, (segment_value & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 499;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|EN0_Pin|EN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_0_Pin|SEG_1_Pin|SEG_2_Pin|SEG_3_Pin
                          |SEG_4_Pin|SEG_5_Pin|SEG_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin EN0_Pin EN1_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|EN0_Pin|EN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_0_Pin SEG_1_Pin SEG_2_Pin SEG_3_Pin
                           SEG_4_Pin SEG_5_Pin SEG_6_Pin */
  GPIO_InitStruct.Pin = SEG_0_Pin|SEG_1_Pin|SEG_2_Pin|SEG_3_Pin
                          |SEG_4_Pin|SEG_5_Pin|SEG_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        // Thay đổi giữa hiển thị 1 và 2
        if (display_flag == 0) {
            displayNumber(1, 1);  // Hiển thị số 1 trên LED thứ nhất
            display_flag = 1;
        } else {
            displayNumber(2, 2);  // Hiển thị số 2 trên LED thứ hai
            display_flag = 0;
        }
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
