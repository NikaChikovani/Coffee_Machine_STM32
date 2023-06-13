/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUZZER_H
#define __BUZZER_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Global defines ------------------------------------------------------------*/
#define htim_buzzer		 						 htim6				  			// define timer instance for buzzer event handling
#define BUZZER_TIMER 	 						 TIM6						 			// define timer for buzzer event handling

#define BUZZER_SERVED_BEEP				 (uint32_t)1000U
#define BUZZER_PROG_BEEP 	 	 			 (uint32_t)500U		
#define BUZZER_LEVER_BEEP	   			 (uint32_t)1000U
#define BUZZER_LEVER_ERR_TRIAL     (uint8_t)3U
#define BUZZER_WATER_ERR_BEEP 	 	 (uint32_t)1000U	
#define BUZZER_WATER_ERR_TRIAL	 	 (uint8_t)3U
#define BUZZER_HEATER_ERR_BEEP 	 	 (uint32_t)500U	
#define BUZZER_HEATER_ERR_LOOP	 	 (uint32_t)10000U
#define BUZZER_HEATER_ERR_TRIAL	 	 (uint8_t)3U

/* Exported types -----------------------------------------------------------*/


/* Global function prototypes -----------------------------------------------*/
void buzzer_handler(uint32_t event);
void Buzzer_Beep_TIM_handler(TIM_HandleTypeDef* htim);

#endif /* __BUZZER_H */
