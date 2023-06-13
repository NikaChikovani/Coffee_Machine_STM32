/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PUMP_H
#define __PUMP_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"


/* Global define ------------------------------------------------------------*/
#define htim_pump		  				  htim14		// define timer instance for ero cross event handling
#define PUMP_TIMER 		          TIM14			// define timer for Zero cross event handling

#define ZERO_CROSS_FALL_OFFSET  10  	    // sine falling edge offset 
#define ZERO_CROSS_RISE_OFFSET  100  	    // sine rising edge offset 

#define	PUMP_DUTY_MAX_VAL       100       // Pump Max power duty %
#define	PUMP_DUTY_MIN_VAL       40   	    // Pump Min  power duty %

#define	PUMP_TIMER_MAX_VAL      0       // Pump Max power duty %
#define	PUMP_TIMER_MIN_VAL      100   	    // Pump Min  power duty %
	    

/* Global function prototypes -----------------------------------------------*/
void pump_set_duty(uint8_t duty);
void Pump_Tim_Handler(TIM_HandleTypeDef* htim);
void pump_handler_timer_enable(void);
void pump_handler_timer_disable(void);
void Set_Pump_Duty(uint8_t duty);
void Pump_Turn_On(void);
void Pump_Turn_Off(void);

#endif /* __PUMP_H */
