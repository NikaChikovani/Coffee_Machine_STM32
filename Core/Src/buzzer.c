/* Private includes ----------------------------------------------------------*/
#include "buzzer.h"

/* External Varibles ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim_buzzer;

/* Private varibles ----------------------------------------------------------*/
volatile uint8_t  buzzer_flg = 0;

/* Private function prototypes -----------------------------------------------*/
static void buzzer_handler_timer_enable(void);
static void buzzer_handler_timer_disable(void);
static void buzzer_on(void);
static void buzzer_off(void);

/* function Definition -------------------------------------------------------*/
void buzzer_handler_timer_enable(void)
{	
	HAL_TIM_Base_Start_IT(&htim_buzzer);
	__HAL_TIM_SetCounter(&htim_buzzer,0);
}

void buzzer_handler_timer_disable(void)
{	
	HAL_TIM_Base_Stop_IT(&htim_buzzer);
	__HAL_TIM_SetCounter(&htim_buzzer,0);
}

void buzzer_on(void)
{
	buzzer_flg = PROCESS_ON;
	buzzer_handler_timer_enable();	
}


void buzzer_off(void)
{
	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	buzzer_flg = PROCESS_OFF;
	buzzer_handler_timer_disable();
}

void buzzer_handler(uint32_t event)
{
		switch(event)
		{    
			case SERVED_MODE:  
			 buzzer_on();	 
			 osDelay(BUZZER_SERVED_BEEP);
			 buzzer_off();	
			
			 break;   
			
			case LEVER_OPEN_WHILE_BREWING_ERROR:
			 for(uint8_t i = 0; i<BUZZER_LEVER_ERR_TRIAL; i++)
					{
						buzzer_on();				
						osDelay(BUZZER_LEVER_BEEP);
						buzzer_off();
						osDelay(BUZZER_LEVER_BEEP);
					}

			 break; 
			
			case PROG_MODE:    
			 buzzer_on();	 
			 osDelay(BUZZER_PROG_BEEP);
			 buzzer_off();	

			 break;  
			
			case HEATER_ERROR:
			 while(1)
			 {
				 for(uint8_t i = 0; i<BUZZER_HEATER_ERR_TRIAL; i++)
					{
						buzzer_on();				
						osDelay(BUZZER_HEATER_ERR_BEEP);
						buzzer_off();
						osDelay(BUZZER_HEATER_ERR_BEEP);
					}
					osDelay(BUZZER_HEATER_ERR_LOOP);
				} 
			
			case WATER_ERROR:    
			 for(uint8_t i = 0; i<BUZZER_WATER_ERR_TRIAL; i++)
					{
						buzzer_on();				
						osDelay(BUZZER_WATER_ERR_BEEP);
						buzzer_off();
						osDelay(BUZZER_WATER_ERR_BEEP);
					}
 
			 break;  
				
			default:     
					break;   
		} 
	
}



void Buzzer_Beep_TIM_handler(TIM_HandleTypeDef* htim)
{
  
	if (htim->Instance == BUZZER_TIMER)
		{
			if(buzzer_flg == PROCESS_ON)
					HAL_GPIO_TogglePin(BUZZER_GPIO_Port,BUZZER_Pin);
		} 
		
}


