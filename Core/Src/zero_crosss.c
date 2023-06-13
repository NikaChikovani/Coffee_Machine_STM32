/* Private includes ----------------------------------------------------------*/
#include "zero_cross.h"

/* External varibles ---------------------------------------------------------*/


/* Private varibles ----------------------------------------------------------*/
volatile uint8_t 	Zero_Cross_Flag = 0;


/* Private Function prototypes -----------------------------------------------*/



/* Function definition -------------------------------------------------------*/

void zero_cross_handler(void)
{
	Zero_Cross_Flag = 1;
	boiler_handler();
}




