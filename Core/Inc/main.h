/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led_driver.h"
#include "button_driver.h"
#include "task_signal_bit_defines.h"
#include "main_process.h"
#include "sleep.h"
#include "ntc.h"
#include "buzzer.h"
#include "brewing_process.h"
#include "boiler.h"
#include "zero_cross.h"
#include "pump.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_13
#define BUZZER_GPIO_Port GPIOC
#define NTC_Pin GPIO_PIN_2
#define NTC_GPIO_Port GPIOA
#define FLOWMETER_Pin GPIO_PIN_3
#define FLOWMETER_GPIO_Port GPIOA
#define FLOWMETER_EXTI_IRQn EXTI2_3_IRQn
#define ZERO_CROSS_Pin GPIO_PIN_4
#define ZERO_CROSS_GPIO_Port GPIOA
#define ZERO_CROSS_EXTI_IRQn EXTI4_15_IRQn
#define BOILER_Pin GPIO_PIN_5
#define BOILER_GPIO_Port GPIOA
#define PUMP_Pin GPIO_PIN_6
#define PUMP_GPIO_Port GPIOA
#define SOL_1_Pin GPIO_PIN_7
#define SOL_1_GPIO_Port GPIOA
#define SOL_2_Pin GPIO_PIN_0
#define SOL_2_GPIO_Port GPIOB
#define NESPRESSO_Pin GPIO_PIN_14
#define NESPRESSO_GPIO_Port GPIOB
#define NESPRESSO_EXTI_IRQn EXTI4_15_IRQn
#define K_CUP_COFFEE_Pin GPIO_PIN_15
#define K_CUP_COFFEE_GPIO_Port GPIOB
#define K_CUP_COFFEE_EXTI_IRQn EXTI4_15_IRQn
#define K_CUP_TEA_Pin GPIO_PIN_8
#define K_CUP_TEA_GPIO_Port GPIOA
#define K_CUP_TEA_EXTI_IRQn EXTI4_15_IRQn
#define HOT_PULSE_Pin GPIO_PIN_9
#define HOT_PULSE_GPIO_Port GPIOA
#define HOT_PULSE_EXTI_IRQn EXTI4_15_IRQn
#define COLD_PULSE_Pin GPIO_PIN_10
#define COLD_PULSE_GPIO_Port GPIOA
#define COLD_PULSE_EXTI_IRQn EXTI4_15_IRQn
#define BIG_SIZE_Pin GPIO_PIN_11
#define BIG_SIZE_GPIO_Port GPIOA
#define BIG_SIZE_EXTI_IRQn EXTI4_15_IRQn
#define SMALL_SIZE_Pin GPIO_PIN_12
#define SMALL_SIZE_GPIO_Port GPIOA
#define SMALL_SIZE_EXTI_IRQn EXTI4_15_IRQn
#define SMALL_SIZE_LED_Pin GPIO_PIN_6
#define SMALL_SIZE_LED_GPIO_Port GPIOF
#define BIG_SIZE_LED_Pin GPIO_PIN_7
#define BIG_SIZE_LED_GPIO_Port GPIOF
#define COLD_PULSE_LED_Pin GPIO_PIN_15
#define COLD_PULSE_LED_GPIO_Port GPIOA
#define HOT_PULSE_LED_Pin GPIO_PIN_3
#define HOT_PULSE_LED_GPIO_Port GPIOB
#define K_CUP_TEA_LED_Pin GPIO_PIN_4
#define K_CUP_TEA_LED_GPIO_Port GPIOB
#define K_CUP_COFFEE_LED_Pin GPIO_PIN_5
#define K_CUP_COFFEE_LED_GPIO_Port GPIOB
#define NESPRESSO_LED_Pin GPIO_PIN_8
#define NESPRESSO_LED_GPIO_Port GPIOB
#define LEVER_Pin GPIO_PIN_9
#define LEVER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
