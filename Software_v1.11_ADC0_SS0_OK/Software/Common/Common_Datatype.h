#ifndef   COMMON_DATATYPE_H
#define   COMMON_DATATYPE_H

#include "TM4C123GH6PM.h"

typedef enum 
{
	
	PB3 = 13U,
	
	PC4 = 24U,
	PC5 = 25U,
	PC6 = 26U,
	PC7 = 27U,
	
	PD6 = 36U,
	PD7 = 37U,
		
	PF0 = 50U,
	PF1 = 51U,
	PF2 = 52U,
	PF3 = 53U,
	PF4 = 54U,
	
} GPIO_PORT;

typedef enum
{
	
	PD = 0U,
	PU = 1U,
	
} GPIO_PU_PD;

typedef enum
{
	
	LOW  = 0U,
	HIGH = 1U,
	
} GPIO_HI_LO;

typedef struct
{
	uint8_t Timer_Flag_20ms       :1;
	uint8_t Timer_Flag_30ms       :1;
	uint8_t Timer_Flag_50ms       :1;
	uint8_t Timer_Flag_100ms      :1;
	uint8_t Timer_Flag_200ms      :1;
	uint8_t Timer_Flag_500ms      :1;
	uint8_t Timer_Flag_1000ms     :1;
	uint8_t Timer_Flag_2000ms     :1;
}Timer_Flag_Stucture;

typedef enum 
{
	PE2 = 0,
	PE1 = 1,
	PD3 = 2,
	PD2 = 3,
	PD1 = 4,
	PD0 = 5,	
} ADC_PORT;
		

#endif
