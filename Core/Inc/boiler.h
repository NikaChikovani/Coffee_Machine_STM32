/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOILER_H
#define __BOILER_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Global define -------------------------------------------------------------*/
#define htim_boiler		  	htim14				// define timer instance for boiler event handling
#define BOILER_TIMER 		  TIM14					// define timer for boiler event handling
#define BOILER_MAX_VAL	  5					
	
/* Global function prototypes ------------------------------------------------*/
void boiler_handler(void);
void boiler_Turn_On(void);
void boiler_Turn_Off(void);
void boiler_handler_timer_enable(void);
void boiler_handler_timer_disable(void);
void boiler_set_duty(uint8_t duty);
#endif /* __BOILER_H */

