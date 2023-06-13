/* Private includes ----------------------------------------------------------*/
#include "button_driver.h"

/* External varibles ---------------------------------------------------------*/
extern osThreadId maintaskHandle;
extern osThreadId ledhandlertaskHandle;
extern osThreadId buzzerhandlertaskHandle;
extern uint32_t button_evnt;

/* Private varibles ----------------------------------------------------------*/



/* Private Function prototypes -----------------------------------------------*/
ButtonPress_StatusTypeDef check_button_press_validity(void);


/* Function definition -------------------------------------------------------*/
ButtonPress_StatusTypeDef check_button_press_validity(void)
{
	if( ( HAL_GPIO_ReadPin(COLD_PULSE_GPIO_Port, COLD_PULSE_Pin) 			+
				HAL_GPIO_ReadPin(HOT_PULSE_GPIO_Port, HOT_PULSE_Pin)				+  
				HAL_GPIO_ReadPin(NESPRESSO_GPIO_Port, NESPRESSO_Pin)   			+
				HAL_GPIO_ReadPin(K_CUP_TEA_GPIO_Port, K_CUP_TEA_Pin)  			+
				HAL_GPIO_ReadPin(SMALL_SIZE_GPIO_Port, SMALL_SIZE_Pin) 		  +
				HAL_GPIO_ReadPin(K_CUP_COFFEE_GPIO_Port, K_CUP_COFFEE_Pin) 	+
				HAL_GPIO_ReadPin(BIG_SIZE_GPIO_Port, BIG_SIZE_Pin)) < BUTTON_VALID_PRESS_NUM)
		
		{
			return PRESS_ERROR;
		} 
	
			return PRESS_OK;
}

void check_prog_mode(uint32_t *current_mode)
{
	if(check_button_press_validity() != PRESS_OK)
		{
			osThreadFlagsSet(maintaskHandle,NESPRESSO_Pin);
			return;
		}
			
	if((HAL_GPIO_ReadPin(SMALL_SIZE_GPIO_Port, SMALL_SIZE_Pin) != BUTTON_PIN_RESET_STATE) &&
		 (HAL_GPIO_ReadPin(BIG_SIZE_GPIO_Port, BIG_SIZE_Pin) != BUTTON_PIN_RESET_STATE))
		{	
			*current_mode = PROG_MODE;
			osThreadFlagsSet(ledhandlertaskHandle,PROG_MODE);
			osThreadFlagsSet(buzzerhandlertaskHandle,PROG_MODE);			
		}
		
			else osThreadFlagsSet(maintaskHandle,NESPRESSO_Pin);
}


void button_handler(uint32_t evnt, uint32_t* current_mode)
{
	uint32_t gpio_pin = RESET_MODE;
	Buttontype_StatusTypeDef button_type = DEFAULT;
	
/* ---------------------------------------------------------------------------*/
/* ********************* Check for button press timeout	***********************/		
/* ---------------------------------------------------------------------------*/	
	switch(evnt)
	{ 		
		case RESET_PARSE_VALUE:
		 *current_mode = RESET_MODE;
		 return;	
		
		case (uint32_t)NESPRESSO_Pin:    
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(NESPRESSO_GPIO_Port, NESPRESSO_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)NESPRESSO_Pin;
				button_type = FUNCTION_BUTTON;
				// reset sleep timer		 
		 break;   
		
		case (uint32_t)K_CUP_COFFEE_Pin:    
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(K_CUP_COFFEE_GPIO_Port, K_CUP_COFFEE_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)K_CUP_COFFEE_Pin;
				button_type = FUNCTION_BUTTON;
				// reset sleep timer	   
		 break; 
		
		case (uint32_t)K_CUP_TEA_Pin:    
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(K_CUP_TEA_GPIO_Port, K_CUP_TEA_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)K_CUP_TEA_Pin;
				button_type = FUNCTION_BUTTON;
				// reset sleep timer	   
		 break;  
		
		case (uint32_t)HOT_PULSE_Pin:    
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(HOT_PULSE_GPIO_Port, HOT_PULSE_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)HOT_PULSE_Pin;
				button_type = FUNCTION_BUTTON;
				// reset sleep timer	 
		 break;  
		
		case (uint32_t)COLD_PULSE_Pin:    
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(COLD_PULSE_GPIO_Port, COLD_PULSE_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)COLD_PULSE_Pin;
				button_type = FUNCTION_BUTTON;
				// reset sleep timer	   
		 break;  
		
		case (uint32_t)BIG_SIZE_Pin:     
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(BIG_SIZE_GPIO_Port, BIG_SIZE_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)BIG_SIZE_Pin;
				button_type = SIZE_BUTTON;
				// reset sleep timer	  
		 break;  
		
		case (uint32_t)SMALL_SIZE_Pin:      
		 osDelay(BUTTON_PRESS_TIME);
		 if(HAL_GPIO_ReadPin(SMALL_SIZE_GPIO_Port, SMALL_SIZE_Pin) != BUTTON_PIN_RESET_STATE)
				gpio_pin = (uint32_t)SMALL_SIZE_Pin;
				button_type = SIZE_BUTTON;
				// reset sleep timer	
		 break;  
		
		default:			
				return;   
	}    
	
/* -------------------------------------------------------------------------------------*/
/* ********************* Check for multiple button press	*******************************/		
/* -------------------------------------------------------------------------------------*/	
	if(check_button_press_validity() != PRESS_OK)
		{
			return;
		}	 
		
/* -------------------------------------------------------------------------------------*/
/* ********************* Check for prog mode	*******************************************/		
/* -------------------------------------------------------------------------------------*/
	 if((*current_mode == PROG_MODE) && (gpio_pin != RESET_MODE))
		{
			osThreadFlagsSet(ledhandlertaskHandle,gpio_pin);
			osDelay(1000U);
			osThreadFlagsSet(maintaskHandle,gpio_pin);
			*current_mode = RESET_MODE;	
			return;
		}		
		
/* -------------------------------------------------------------------------------------*/
/* ********************* Check for rins stop press	*************************************/		
/* -------------------------------------------------------------------------------------*/
	 if((*current_mode == RINS_MODE) && (gpio_pin != RESET_MODE))
		{
			osThreadFlagsSet(maintaskHandle,SERVED_MODE);
			*current_mode = RESET_MODE;
			return;
		}		 
	
/* -------------------------------------------------------------------------------------*/
/* ********************* Parse incoming button press	***********************************/		
/* -------------------------------------------------------------------------------------*/

		/* ------------ Stop serving process -------------*/
	 if((*current_mode == SERVING_MODE) && (button_type == SIZE_BUTTON))
		{			
			osThreadFlagsSet(maintaskHandle,SERVED_MODE);	
			*current_mode = RESET_MODE;
		}	 
		/* ------------ Start serving process -------------*/		
	 else if((*current_mode != RESET_MODE) && (button_type == SIZE_BUTTON))
		{			
			osThreadFlagsSet(maintaskHandle,gpio_pin|(*current_mode));
			osThreadFlagsSet(ledhandlertaskHandle,gpio_pin|(*current_mode));	
			*current_mode = SERVING_MODE;		
		}	
		/* ------------ Select function mode -------------*/			
	 else if((*current_mode != SERVING_MODE) && (button_type == FUNCTION_BUTTON))
		{	
			
			if(*current_mode == gpio_pin)
				{
					osThreadFlagsSet(ledhandlertaskHandle,READY_MODE);
					*current_mode = RESET_MODE;
				}
					else 
						{
							osThreadFlagsSet(ledhandlertaskHandle,gpio_pin);	
							*current_mode = gpio_pin;						
						}

		}		
			
}




