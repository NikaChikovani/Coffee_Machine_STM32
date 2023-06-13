/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef __TASK_SIGNAL_BIT_DEFINES_H
#define __TASK_SIGNAL_BIT_DEFINES_H

/* Private includes --------------------------------------------------------------*/
#include "main.h"

/* Define Signal values for Inter-Thread Communication  --------------------------*/

/* ---- Serving process signal defines  ----*/
/*
#define NESSPRESSO_SMALL 		  					(uint32_t)0x00010000U
#define NESSPRESSO_BIG 	 		  					(uint32_t)0x00020000U
#define K_CUP_COFFEE_SMALL 							(uint32_t)0x00030000U
#define K_CUP_COFFEE_BIG 								(uint32_t)0x00040000U
#define K_CUP_TEA_SMALL 		  					(uint32_t)0x00050000U
#define K_CUP_TEA_BIG 			  					(uint32_t)0x00060000U
#define HOT_PULSE_SMALL 								(uint32_t)0x00070000U
#define HOT_PULSE_BIG 									(uint32_t)0x00080000U
#define COLD_PULSE_SMALL 								(uint32_t)0x00090000U
#define COLD_PULSE_BIG 									(uint32_t)0x000A0000U */

#define NESPRESSO_SMALL 		  					(uint32_t)(NESPRESSO_Pin|SMALL_SIZE_Pin)
#define NESPRESSO_BIG 	 		  					(uint32_t)(NESPRESSO_Pin|BIG_SIZE_Pin)

#define K_CUP_COFFEE_SMALL 							(uint32_t)(K_CUP_COFFEE_Pin|SMALL_SIZE_Pin)
#define K_CUP_COFFEE_BIG 								(uint32_t)(K_CUP_COFFEE_Pin|BIG_SIZE_Pin)

#define K_CUP_TEA_SMALL 		  					(uint32_t)(K_CUP_TEA_Pin|SMALL_SIZE_Pin)
#define K_CUP_TEA_BIG 			  					(uint32_t)(K_CUP_TEA_Pin|BIG_SIZE_Pin)

#define HOT_PULSE_SMALL 								(uint32_t)(HOT_PULSE_Pin|SMALL_SIZE_Pin)
#define HOT_PULSE_BIG 									(uint32_t)(HOT_PULSE_Pin|BIG_SIZE_Pin)

#define COLD_PULSE_SMALL 								(uint32_t)(COLD_PULSE_Pin|SMALL_SIZE_Pin)
#define COLD_PULSE_BIG 									(uint32_t)(COLD_PULSE_Pin|BIG_SIZE_Pin)

#define RINS_MODE					 							(uint32_t)0x000B0000U

/* ---- Prog and Sleep Mode defines  ----*/
#define SLEEP_MODE 											(uint32_t)0x000C0000U
#define PROG_MODE					 							(uint32_t)0x000D0000U

/* ---- Error Mode defines  ----*/
#define HEATER_ERROR 										(uint32_t)0x000E0000U
#define WATER_ERROR					 						(uint32_t)0x000F0000U
#define LEVER_OPEN_WHILE_BREWING_ERROR	(uint32_t)0x00100000U
#define INTERNAL_ERROR									(uint32_t)0x00200000U

/* ---- Other Mode defines  ----*/
#define READY_MODE 											(uint32_t)0x00300000U
#define SERVED_MODE 										(uint32_t)0x00400000U
#define LEVER_OPEN_MODE									(uint32_t)0x00500000U
#define HEATING_UP_MODE									(uint32_t)0x00600000U

/* ---- Reset bits for parse process ----*/
#define RESET_PARSE_VALUE								(uint32_t)0x00700000U

/* ---- Wait bit defines by event  ----*/
#define BUTTON_WAIT_BITS								(uint32_t)NESPRESSO_Pin|K_CUP_COFFEE_Pin|K_CUP_TEA_Pin|HOT_PULSE_Pin|COLD_PULSE_Pin|BIG_SIZE_Pin|SMALL_SIZE_Pin
#define ERROR_WAIT_BITS									(uint32_t)HEATER_ERROR|WATER_ERROR|LEVER_OPEN_WHILE_BREWING_ERROR|INTERNAL_ERROR
#define MODE_WAIT_BITS									(uint32_t)NESPRESSO_SMALL|NESPRESSO_BIG|K_CUP_COFFEE_SMALL|K_CUP_COFFEE_BIG|K_CUP_TEA_SMALL|K_CUP_TEA_BIG|HOT_PULSE_SMALL|HOT_PULSE_BIG|COLD_PULSE_SMALL|COLD_PULSE_BIG|RINS_MODE
#define EVENT_WAIT_BITS									(uint32_t)PROG_MODE|SLEEP_MODE|HEATING_UP_MODE|READY_MODE|SERVED_MODE|LEVER_OPEN_MODE

/* ---- Wait bit defines for tasks  ----*/
#define LED_TASK_WAIT_BITS							BUTTON_WAIT_BITS|ERROR_WAIT_BITS|MODE_WAIT_BITS|EVENT_WAIT_BITS
#define BUZZER_TASK_WAIT_BITS						ERROR_WAIT_BITS|EVENT_WAIT_BITS
#define MAIN_TASK_WAIT_BITS							MODE_WAIT_BITS|ERROR_WAIT_BITS|EVENT_WAIT_BITS	
#define BUTTON_TASK_WAIT_BITS						BUTTON_WAIT_BITS|RESET_PARSE_VALUE		

#define ALL_BITS												(uint32_t)0xFFFFFFFFU



/* Exported types -----------------	-----------------------------------------------*/





#endif /* __TASK_SIGNAL_BIT_DEFINES_H	*/
