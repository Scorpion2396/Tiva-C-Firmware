#ifndef   COMMON_DATATYPE_H
#define   COMMON_DATATYPE_H

#include "TM4C123GH6PM.h"

//#include "Common_Datatype.h"

typedef enum 
{
	
	PB3 = (uint8_t)13,
	
	PC4 = (uint8_t)24,
	PC5 = (uint8_t)25,
	PC6 = (uint8_t)26,
	PC7 = (uint8_t)27,
	
	PD6 = (uint8_t)36,
	PD7 = (uint8_t)37,
		
	PF0 = (uint8_t)50,
	PF1 = (uint8_t)51,
	PF2 = (uint8_t)52,
	PF3 = (uint8_t)53,
	PF4 = (uint8_t)54,
	
} GPIO_PORT;

typedef enum
{
	
	PD = (uint8_t)0,
	PU = (uint8_t)1,
	
} GPIO_PU_PD;

typedef enum
{
	
	LOW  = (uint8_t)0,
	HIGH = (uint8_t)1,
	
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
	PE2 = 1,
	PE1 = 2,
	PD3 = 4,
	PD2 = 5,
	PD1 = 6,
	PD0 = 7,	
} ADC_PORT;
		

#endif
