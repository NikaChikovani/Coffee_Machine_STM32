/* Private includes ----------------------------------------------------------*/
#include "led_driver.h"

/* External varibles ---------------------------------------------------------*/
extern osThreadId buzzerhandlertaskHandle;

/* Private varibles ----------------------------------------------------------*/


/* Private Function prototypes -----------------------------------------------*/
static void led_Reset_all(void);
static void led_turn_on_all(void);
static void led_turn_on_func(void);
static void led_toggle_func(void);
static void led_toggle_all(void); 
static void led_function_button_blink(GPIO_TypeDef *gpio_port,uint16_t function_pin);
static void serve_process_button_blink(GPIO_TypeDef *func_gpio_port,uint16_t function_pin,GPIO_TypeDef *size_gpio_port,uint16_t size_pin);
static void led_heat_up(void); 
static void led_ready(void);
static void led_prog_mode(void);
/*
static void led_rins_mode(void);
static void led_lever_open(void); */
/* Function definition ------------------------------------------------------------*/
static void led_Reset_all(void)
{
	HAL_GPIO_WritePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin	, LED_PIN_RESET);
	HAL_GPIO_WritePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin, LED_PIN_RESET); 
}

static void led_turn_on_all(void)
{
	HAL_GPIO_WritePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin	, LED_PIN_SET);
	HAL_GPIO_WritePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin, LED_PIN_SET); 	
}

static void led_turn_on_func(void)
{
	HAL_GPIO_WritePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin	, LED_PIN_SET);
} 

static void led_toggle_func(void)
{
	HAL_GPIO_TogglePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin);
	HAL_GPIO_TogglePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin);
	HAL_GPIO_TogglePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin);
	HAL_GPIO_TogglePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin);
	HAL_GPIO_TogglePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin);		
}

static void led_toggle_all(void)
{
	HAL_GPIO_TogglePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin);
	HAL_GPIO_TogglePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin);
	HAL_GPIO_TogglePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin);
	HAL_GPIO_TogglePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin);
	HAL_GPIO_TogglePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin);
	HAL_GPIO_TogglePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
	HAL_GPIO_TogglePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);		
}

static void led_function_button_blink(GPIO_TypeDef *gpio_port,uint16_t function_pin)
{
	led_Reset_all();	
	HAL_GPIO_WritePin(gpio_port, function_pin, LED_PIN_SET);
	HAL_GPIO_WritePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin, LED_PIN_SET); 
}

static void serve_process_button_blink(GPIO_TypeDef *func_gpio_port,uint16_t function_pin,GPIO_TypeDef *size_gpio_port,uint16_t size_pin)
{
	led_Reset_all();				
	HAL_GPIO_WritePin(func_gpio_port, function_pin, LED_PIN_SET);
	
	while(osThreadFlagsGet() != SERVED_MODE)
	{
		HAL_GPIO_TogglePin(size_gpio_port, size_pin);
		osDelay(SERVING_BLINK_DELAY);
	}
	
	HAL_GPIO_WritePin(func_gpio_port, function_pin, LED_PIN_SET);
	HAL_GPIO_WritePin(size_gpio_port, size_pin, LED_PIN_SET);
	osDelay(SERVED_BLINK_DELAY);
	
	for(uint8_t i = 0; i < SERVED_BLINK_CNT; i++)
	{
		HAL_GPIO_TogglePin(func_gpio_port, function_pin);
		HAL_GPIO_TogglePin(size_gpio_port, size_pin);	
		osDelay(SERVED_BLINK_DELAY);
	}
}

static void led_heat_up(void)
{
	led_turn_on_all();
	osDelay(HEAT_UP_BLINK_DELAY);
	HAL_GPIO_WritePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin, LED_PIN_RESET);
	HAL_GPIO_WritePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin, LED_PIN_RESET);
	
	while(osThreadFlagsGet() != READY_MODE)
	{
		led_toggle_func();
		osDelay(HEAT_UP_BLINK_DELAY);
	}
}

static void led_ready(void)
{
	led_Reset_all();
	
	HAL_GPIO_WritePin(NESPRESSO_LED_GPIO_Port, NESPRESSO_LED_Pin, LED_PIN_SET);
	osDelay(READY_BLINK_DELAY);
	HAL_GPIO_WritePin(K_CUP_COFFEE_LED_GPIO_Port, K_CUP_COFFEE_LED_Pin, LED_PIN_SET);
	osDelay(READY_BLINK_DELAY);	
	HAL_GPIO_WritePin(K_CUP_TEA_LED_GPIO_Port, K_CUP_TEA_LED_Pin, LED_PIN_SET);
	osDelay(READY_BLINK_DELAY);
	HAL_GPIO_WritePin(HOT_PULSE_LED_GPIO_Port, HOT_PULSE_LED_Pin, LED_PIN_SET);
	osDelay(READY_BLINK_DELAY);
	HAL_GPIO_WritePin(COLD_PULSE_LED_GPIO_Port, COLD_PULSE_LED_Pin, LED_PIN_SET);
}

static void led_prog_mode(void)
{
	led_Reset_all();
	
	HAL_GPIO_WritePin(BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin, LED_PIN_SET);
	HAL_GPIO_WritePin(SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin, LED_PIN_SET); 
}


void led_handler(uint32_t evnt)
{
	switch(evnt)
	{ 
		/* ------------ Function leds -------------*/   
		case (uint32_t)NESPRESSO_Pin:  
		 led_function_button_blink(NESPRESSO_LED_GPIO_Port,NESPRESSO_LED_Pin); 		
		 break;   
		
		case (uint32_t)K_CUP_COFFEE_Pin:  
		 led_function_button_blink(K_CUP_COFFEE_LED_GPIO_Port,K_CUP_COFFEE_LED_Pin);		
		 break; 
		
		case (uint32_t)K_CUP_TEA_Pin: 
		 led_function_button_blink(K_CUP_TEA_LED_GPIO_Port,K_CUP_TEA_LED_Pin);	
		 break;  
		
		case (uint32_t)HOT_PULSE_Pin: 
		 led_function_button_blink(HOT_PULSE_LED_GPIO_Port,HOT_PULSE_LED_Pin);	
		 break;  
		
		case (uint32_t)COLD_PULSE_Pin: 
		 led_function_button_blink(COLD_PULSE_LED_GPIO_Port,COLD_PULSE_LED_Pin);  		
		 break;  
		
		/* ------------ Serving process -------------*/
		case NESPRESSO_SMALL: 
		 serve_process_button_blink(NESPRESSO_LED_GPIO_Port,NESPRESSO_LED_Pin,SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);
		 break;  
		
		case NESPRESSO_BIG: 
		 serve_process_button_blink(NESPRESSO_LED_GPIO_Port,NESPRESSO_LED_Pin,BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
		 break; 
		
		case K_CUP_COFFEE_SMALL: 
		 serve_process_button_blink(K_CUP_COFFEE_LED_GPIO_Port,K_CUP_COFFEE_LED_Pin,SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);
		 break;  
		
		case K_CUP_COFFEE_BIG: 
		 serve_process_button_blink(K_CUP_COFFEE_LED_GPIO_Port,K_CUP_COFFEE_LED_Pin,BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
		 break; 
		
		case K_CUP_TEA_SMALL: 
		 serve_process_button_blink(K_CUP_TEA_LED_GPIO_Port,K_CUP_TEA_LED_Pin,SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);
		 break;  
		
		case K_CUP_TEA_BIG: 
		 serve_process_button_blink(K_CUP_TEA_LED_GPIO_Port,K_CUP_TEA_LED_Pin,BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
		 break; 
		
		case HOT_PULSE_SMALL: 
		 serve_process_button_blink(HOT_PULSE_LED_GPIO_Port,HOT_PULSE_LED_Pin,SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);
		 break;  
		
		case HOT_PULSE_BIG: 
		 serve_process_button_blink(HOT_PULSE_LED_GPIO_Port,HOT_PULSE_LED_Pin,BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
		 break; 
		
		case COLD_PULSE_SMALL: 
		 serve_process_button_blink(COLD_PULSE_LED_GPIO_Port,COLD_PULSE_LED_Pin,SMALL_SIZE_LED_GPIO_Port, SMALL_SIZE_LED_Pin);
		 break;  
		
		case COLD_PULSE_BIG: 
		 serve_process_button_blink(COLD_PULSE_LED_GPIO_Port,COLD_PULSE_LED_Pin,BIG_SIZE_LED_GPIO_Port, BIG_SIZE_LED_Pin);
		 break; 

		/* ------------ Ready ----------------*/
		case READY_MODE: 
		 led_ready();
		 break; 

		/* ------------ Heat_up --------------*/
		case HEATING_UP_MODE: 
		 led_heat_up();
		 break; 

		/* ------------ Prog mode -------------*/
		case PROG_MODE: 
		 led_prog_mode();

		 break;
	
		
		/* ------------ Rins mode -------------*/
		
		
		/* ------------ Lever open ------------*/
		
		
		/* ------------ error process ---------*/


		default:     
				return;   
	}   
	
}

