/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef __BUTTON_DRIVER_H
#define __BUTTON_DRIVER_H

/* Private includes --------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Global defines ----------------------------------------------------------------*/
#define BUTTON_PRESS_TIME						(uint32_t)100U    			// define button press time (MilliSeconds)
#define RINS_PRESS_TIME	 						(uint32_t)5000U   			// define rinsing mode button press time (MilliSeconds)
#define BUTTON_VALID_PRESS_NUM	 		(uint8_t)5U   					// define max button press at the same time value (7 - 5 = 2)
#define BUTTON_PIN_RESET_STATE 			 GPIO_PIN_SET 					// define button reset state

#define SERVING_MODE 								(uint32_t)0x00000001U
#define RESET_MODE									(uint32_t)0xFFFFFFFFU	
/* Exported types ----------------------------------------------------------------*/
/* ----- Button press status enum ----*/
typedef enum
{
	PRESS_ERROR 	= 0x00U,
  PRESS_OK			= 0x01U			
} ButtonPress_StatusTypeDef;

/* ----- Button type status enum ----*/
typedef enum
{
	DEFAULT          = 0x00U,
	FUNCTION_BUTTON  = 0x01U,
  SIZE_BUTTON			 = 0x02U			
} Buttontype_StatusTypeDef;


/* Process status enum ---------------*/
typedef enum
{
	PROCESS_OFF = 0x00U,
  PROCESS_ON	= 0x01U			
} Process_StatusTypeDef;

/* Exported function prototypes --------------------------------------------------*/
void button_handler(uint32_t evnt, uint32_t* current_mode);
void check_prog_mode(uint32_t *current_mode);

#endif /* __BUTTON_DRIVER_H	*/

