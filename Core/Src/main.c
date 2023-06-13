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
#include "cmsis_os.h"

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
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim14;

/* Definitions for ledhandlertask */
osThreadId_t ledhandlertaskHandle;
const osThreadAttr_t ledhandlertask_attributes = {
  .name = "ledhandlertask",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buttonhandlertask */
osThreadId_t buttonhandlertaskHandle;
const osThreadAttr_t buttonhandlertask_attributes = {
  .name = "buttonhandlertask",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for maintask */
osThreadId_t maintaskHandle;
const osThreadAttr_t maintask_attributes = {
  .name = "maintask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buzzerhandlertask */
osThreadId_t buzzerhandlertaskHandle;
const osThreadAttr_t buzzerhandlertask_attributes = {
  .name = "buzzerhandlertask",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for errorhandlertask */
osThreadId_t errorhandlertaskHandle;
const osThreadAttr_t errorhandlertask_attributes = {
  .name = "errorhandlertask",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM14_Init(void);
void LedHandler(void *argument);
void ButtonHandler(void *argument);
void MainTaskHandler(void *argument);
void BuzzerHandler(void *argument);
void ErrorHandler(void *argument);

/* USER CODE BEGIN PFP */

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
  MX_ADC_Init();
  MX_TIM6_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ledhandlertask */
  ledhandlertaskHandle = osThreadNew(LedHandler, NULL, &ledhandlertask_attributes);

  /* creation of buttonhandlertask */
  buttonhandlertaskHandle = osThreadNew(ButtonHandler, NULL, &buttonhandlertask_attributes);

  /* creation of maintask */
  maintaskHandle = osThreadNew(MainTaskHandler, NULL, &maintask_attributes);

  /* creation of buzzerhandlertask */
  buzzerhandlertaskHandle = osThreadNew(BuzzerHandler, NULL, &buzzerhandlertask_attributes);

  /* creation of errorhandlertask */
  errorhandlertaskHandle = osThreadNew(ErrorHandler, NULL, &errorhandlertask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 6-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 48-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 100;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BOILER_Pin|PUMP_Pin|SOL_1_Pin|COLD_PULSE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SOL_2_Pin|HOT_PULSE_LED_Pin|K_CUP_TEA_LED_Pin|K_CUP_COFFEE_LED_Pin
                          |NESPRESSO_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SMALL_SIZE_LED_Pin|BIG_SIZE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUZZER_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FLOWMETER_Pin */
  GPIO_InitStruct.Pin = FLOWMETER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FLOWMETER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ZERO_CROSS_Pin */
  GPIO_InitStruct.Pin = ZERO_CROSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ZERO_CROSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BOILER_Pin PUMP_Pin SOL_1_Pin COLD_PULSE_LED_Pin */
  GPIO_InitStruct.Pin = BOILER_Pin|PUMP_Pin|SOL_1_Pin|COLD_PULSE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SOL_2_Pin HOT_PULSE_LED_Pin K_CUP_TEA_LED_Pin K_CUP_COFFEE_LED_Pin
                           NESPRESSO_LED_Pin */
  GPIO_InitStruct.Pin = SOL_2_Pin|HOT_PULSE_LED_Pin|K_CUP_TEA_LED_Pin|K_CUP_COFFEE_LED_Pin
                          |NESPRESSO_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : NESPRESSO_Pin K_CUP_COFFEE_Pin */
  GPIO_InitStruct.Pin = NESPRESSO_Pin|K_CUP_COFFEE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : K_CUP_TEA_Pin HOT_PULSE_Pin COLD_PULSE_Pin BIG_SIZE_Pin
                           SMALL_SIZE_Pin */
  GPIO_InitStruct.Pin = K_CUP_TEA_Pin|HOT_PULSE_Pin|COLD_PULSE_Pin|BIG_SIZE_Pin
                          |SMALL_SIZE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SMALL_SIZE_LED_Pin BIG_SIZE_LED_Pin */
  GPIO_InitStruct.Pin = SMALL_SIZE_LED_Pin|BIG_SIZE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : LEVER_Pin */
  GPIO_InitStruct.Pin = LEVER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LEVER_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == ZERO_CROSS_Pin)  
    {		
			zero_cross_handler();
		}
		
	else if(GPIO_Pin == FLOWMETER_Pin)
		{
			
		}
		
	else osThreadFlagsSet(buttonhandlertaskHandle,(uint32_t)GPIO_Pin);
	
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_LedHandler */
/**
  * @brief  Function implementing the ledhandlertask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LedHandler */
void LedHandler(void *argument)
{
  /* USER CODE BEGIN 5 */
	uint32_t evnt  = 0;

  /* Infinite loop */
	for(;;)
  {
		
		evnt = osThreadFlagsWait(LED_TASK_WAIT_BITS,osFlagsWaitAny,osWaitForever);
		
		led_handler(evnt);
		
		osThreadFlagsClear(LED_TASK_WAIT_BITS);	
		
    osDelay(10);
		
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_ButtonHandler */
/**
* @brief Function implementing the buttonhandlerta thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonHandler */
void ButtonHandler(void *argument)
{
  /* USER CODE BEGIN ButtonHandler */
	uint32_t evnt = 0;
	uint32_t current_mode = RESET_MODE;
	
	// Check for Prog Mode on Startup and send default sleep timeout value to main task
	check_prog_mode(&current_mode);
		
	//	osThreadFlagsClear(ALL_BITS); // ??
				 
  /* Infinite loop */
  for(;;)
  {
		
		// needs semaphore or some synchronisation from maintask in error mode 
		
		evnt = osThreadFlagsWait(BUTTON_TASK_WAIT_BITS,osFlagsWaitAny,osWaitForever);

		button_handler(evnt,&current_mode);
		
		osThreadFlagsClear(BUTTON_TASK_WAIT_BITS);
					
    osDelay(10);
  }
  /* USER CODE END ButtonHandler */
}

/* USER CODE BEGIN Header_MainTaskHandler */
/**
* @brief Function implementing the maintask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MainTaskHandler */
void MainTaskHandler(void *argument)
{
  /* USER CODE BEGIN MainTaskHandler */
	uint32_t evnt = 0;
	uint32_t sleep_timeout_val = 0;
	 // wait for sleep timeout value from parser task
	sleep_timeout_val = osThreadFlagsWait(BUTTON_WAIT_BITS,osFlagsWaitAny,osWaitForever);
	// save 
	
	pump_handler_timer_enable();
	
  /* Infinite loop */
  for(;;)
  {
		Process_Handler();
    osDelay(10);
  }
  /* USER CODE END MainTaskHandler */
}

/* USER CODE BEGIN Header_BuzzerHandler */
/**
* @brief Function implementing the buzzerhandlertask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BuzzerHandler */
void BuzzerHandler(void *argument)
{
  /* USER CODE BEGIN BuzzerHandler */
	uint32_t evnt = 0;
  /* Infinite loop */
  for(;;)
  {
		evnt = osThreadFlagsWait(BUZZER_TASK_WAIT_BITS,osFlagsWaitAny,osWaitForever);

		buzzer_handler(evnt);
		
		osThreadFlagsClear(BUZZER_TASK_WAIT_BITS);
					
    osDelay(10);

  }
  /* USER CODE END BuzzerHandler */
}

/* USER CODE BEGIN Header_ErrorHandler */
/**
* @brief Function implementing the errorhandlertask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ErrorHandler */
void ErrorHandler(void *argument)
{
  /* USER CODE BEGIN ErrorHandler */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END ErrorHandler */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	Buzzer_Beep_TIM_handler(htim);
  /* USER CODE END Callback 1 */
}

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
