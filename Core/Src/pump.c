/* Private includes ----------------------------------------------------------*/
#include "pump.h"

/* External varibles ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim_pump;
volatile uint8_t Pump_Timer_Duty = PUMP_DUTY_MAX_VAL;
extern volatile uint8_t 	Zero_Cross_Flag;

/* Private varibles ----------------------------------------------------------*/
volatile uint8_t  dimmer_en_flg = 0;
volatile uint16_t Pump_Sine_Counter = 0;
volatile uint8_t  Period_elapse_flg = 0;

/* Private Function prototypes ------------------------------------------------*/
static void pump_handler(void);


/* Function definition --------------------------------------------------------*/

void pump_handler_timer_enable(void)
{
	__HAL_TIM_SetCounter(&htim_pump,0);
	HAL_TIM_Base_Start_IT(&htim_pump);
}	

void pump_handler_timer_disable(void)
{
	__HAL_TIM_SetCounter(&htim_pump,0);
	HAL_TIM_Base_Stop_IT(&htim_pump);
}
	
void Pump_Turn_On(void)
{
	HAL_GPIO_WritePin(PUMP_GPIO_Port, PUMP_Pin, GPIO_PIN_SET);
}

void Pump_Turn_Off(void)
{
	HAL_GPIO_WritePin(PUMP_GPIO_Port, PUMP_Pin, GPIO_PIN_RESET);		
} 

void pump_set_duty(uint8_t duty)
{
	if( duty > PUMP_DUTY_MAX_VAL)
		{
			Pump_Timer_Duty = PUMP_TIMER_MAX_VAL;
		}

	else if(duty < PUMP_DUTY_MIN_VAL)
		{
			Pump_Timer_Duty = PUMP_TIMER_MIN_VAL;	
		}
		else 
			{
				Pump_Timer_Duty = duty;	
			}
} 

static void pump_handler(void)
{
	if(Period_elapse_flg )
		{
			Zero_Cross_Flag = 0;
			Pump_Sine_Counter = 0;					
			Period_elapse_flg = 0;	
			Pump_Turn_Off();
		} 
								
			if(Pump_Timer_Duty == 0)
				{
					Pump_Turn_On();	
					Pump_Sine_Counter = 0;
				}

			else if(Pump_Sine_Counter == (Pump_Timer_Duty + ZERO_CROSS_FALL_OFFSET))
				{
					Pump_Turn_On();	
				}
				
			else if(Pump_Sine_Counter == (Pump_Timer_Duty + ZERO_CROSS_RISE_OFFSET + ZERO_CROSS_FALL_OFFSET))
				{
					Pump_Turn_On();							
					Period_elapse_flg  = 1;							
				} 
					else {
								 Pump_Turn_Off();																
							 }			

} 


 void Pump_Tim_Handler(TIM_HandleTypeDef* htim)
{
		if (htim->Instance == PUMP_TIMER)
		{			
			if(Zero_Cross_Flag)
				{			
					Pump_Sine_Counter++;
					pump_handler();

				}
		} 
	
} 


