/* Private includes ----------------------------------------------------------*/
#include "boiler.h"

/* External varibles ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim_boiler;

/* Private varibles ----------------------------------------------------------*/
volatile uint8_t boiler_tim_cnt = 0;
volatile uint8_t Boiler_Timer_Duty_sample = 0;
volatile uint8_t Zero_cross_cnt = 0;
volatile uint8_t Boiler_Timer_Duty = 0;

/* Private Function prototypes -----------------------------------------------*/


/* Function definition -------------------------------------------------------*/
void boiler_handler_timer_enable(void)
{
	__HAL_TIM_SetCounter(&htim_boiler,0);
	HAL_TIM_Base_Start_IT(&htim_boiler);
}	

void boiler_handler_timer_disable(void)
{
	HAL_TIM_Base_Stop_IT(&htim_boiler);
	__HAL_TIM_SetCounter(&htim_boiler,0);
}

void boiler_Turn_On(void)
{
	HAL_GPIO_WritePin(BOILER_GPIO_Port, BOILER_Pin, GPIO_PIN_SET);
}

void boiler_Turn_Off(void)
{
	HAL_GPIO_WritePin(BOILER_GPIO_Port, BOILER_Pin, GPIO_PIN_RESET);
} 

void boiler_set_duty(uint8_t duty)
{
	if( duty > BOILER_MAX_VAL)
		{
			Boiler_Timer_Duty = BOILER_MAX_VAL;
		}
	else 
		{		
			Boiler_Timer_Duty = duty;
		}
		
}

void boiler_handler(void)
{
	Zero_cross_cnt++;
	
	if( Zero_cross_cnt > BOILER_MAX_VAL)
		{
			Zero_cross_cnt = 1;
		}
	
	if( Zero_cross_cnt == 1)
		{
			Boiler_Timer_Duty_sample = Boiler_Timer_Duty;
		}
				
	if(Zero_cross_cnt <= Boiler_Timer_Duty_sample)
		{
			boiler_Turn_On();
		}
		
		else boiler_Turn_Off();		
}






