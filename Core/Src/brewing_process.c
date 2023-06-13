/* Private includes ----------------------------------------------------------*/
#include "brewing_process.h"

/* External Varibles ---------------------------------------------------------*/


/* Private Varibles ----------------------------------------------------------*/
volatile int16_t Current_Temp;
volatile int16_t Current_Error;
volatile int16_t Target_Temp;

/* Private function prototypes -----------------------------------------------*/
static void boiler_heat_up(void);

/* function Definition -------------------------------------------------------*/
static void boiler_heat_up(void)
{
		Current_Error = Target_Temp - Current_Temp;
	
			if(Current_Error >= (int16_t)50)
			 {
				 boiler_set_duty(5);
			 } 
			 
			 else if((Current_Error < (int16_t)50) && (Current_Error >= (int16_t)40)) boiler_set_duty(5);
			 
			 else if((Current_Error < (int16_t)40) && (Current_Error >= (int16_t)30)) boiler_set_duty(4);
			 
			 else if((Current_Error < (int16_t)30) && (Current_Error >= (int16_t)20)) boiler_set_duty(3);
			 
			 else if((Current_Error < (int16_t)20) && (Current_Error >= (int16_t)10)) boiler_set_duty(2);
			 
			 else if((Current_Error < (int16_t)10) && (Current_Error >  (int16_t)0)) 	boiler_set_duty(1);
				
				else {
								boiler_set_duty(0);
						 }

}



void Process_Handler(void)
{
	Current_Temp = Get_NTC_Temp();
	Target_Temp = BOILER_HEAT_UP_TEMP;
	
	// Start heat up
	boiler_heat_up();
		
}


