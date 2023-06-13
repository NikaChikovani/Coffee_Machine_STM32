/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SLEEP_H
#define __SLEEP_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Global defines ------------------------------------------------------------*/


/* Exported Types ------------------------------------------------------------*/

/*---- Sleep mode enum ----*/
typedef enum
{
  MIN_15	= 15U, 			
  MIN_30 	= 30U, 			
	MIN_60 	= 60U, 
	MIN_120 = 120U,  
	MIN_240 = 240U
} Sleep_ModeTypeDef;	


/* Global function prototypes ------------------------------------------------*/
void sleep_handler(void);


#endif /* __SLEEP_H */
