/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

/* Private includes --------------------------------------------------------------*/
#include "main.h"

/* Global defines ----------------------------------------------------------------*/
#define LED_PIN_RESET								GPIO_PIN_RESET 	
#define LED_PIN_SET 								GPIO_PIN_SET 	

#define HEAT_UP_BLINK_DELAY		      (uint32_t)1000U		// 1000 mS
#define READY_BLINK_DELAY		 	      (uint32_t)100U		// 100  mS
#define SERVING_BLINK_DELAY	        (uint32_t)1000U		// 1000 mS
#define SERVED_BLINK_DELAY	 			  (uint32_t)500U		// 500  mS
#define SERVED_BLINK_CNT 			  		(uint8_t)5U				// 3
#define RINS_BLINK_DELAY	 		 			(uint32_t)1000U		// 1000 mS
#define LEVER_BEFORE_BLINK_DELAY 		(uint32_t)1000U		// 1000 mS
#define LEVER_WHILE_BLINK_DELAY 		(uint32_t)500U		// 1000 mS
#define WATER_ERR_BLINK_DELAY 		  (uint32_t)500U		// 500  mS
#define PROG_LED_DELAY							(uint32_t)500U    // 500  mS

#define WAIT_DELAY_FOR_SERVED				(uint32_t)50U     // 50  mS

/* Exported types -----------------------------------------------------------------*/

/* Exported function prototypes ---------------------------------------------------*/
void led_handler(uint32_t evnt);



#endif /* __LED_DRIVER_H	*/

