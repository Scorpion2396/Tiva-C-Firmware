#ifndef   COMMON_DATATYPE_H
#define   COMMON_DATATYPE_H

#include "TM4C123GH6PM.h"

//#include "Common_Datatype.h"

typedef enum 
{
	PA0 = 00U,
	PA1 = 01U,
	PA2 = 02U,
	PA3 = 03U,
	PA4 = 04U,
	PA5 = 05U,
	PA6 = 06U,
	PA7 = 07U,	
	
	PB0 = 10U,
	PB1 = 11U,
	PB2 = 12U,
	PB3 = 13U,
	PB4 = 14U,
	PB5 = 15U,
	PB6 = 16U,
	PB7 = 17U,
	
	PC0 = 20U,
	PC1 = 21U,
	PC2 = 22U,
	PC3 = 23U,
	PC4 = 24U,
	PC5 = 25U,
	PC6 = 26U,
	PC7 = 27U,
	
	PD0 = 30U,
	PD1 = 31U,
	PD2 = 32U,
	PD3 = 33U,
	PD4 = 34U,
	PD5 = 35U,
	PD6 = 36U,
	PD7 = 37U,
	
	PE0 = 40U,
	PE1 = 41U,
	PE2 = 42U,
	PE3 = 43U,
	PE4 = 44U,
	PE5 = 45U,
		
	PF0 = 50U,
	PF1 = 51U,
	PF2 = 52U,
	PF3 = 53U,
	PF4 = 54U,
	
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

typedef struct
{
	uint16_t MSG_ID    ;
	uint8_t  MSG_DLC   ;
	uint8_t  MSG_ObjNo ;
}CAN0_MSG_Obj;


/********************* I2C ***************************/
typedef struct
{
    I2C0_Type* const I2C_Perif_Addr;           
    GPIOA_Type* const GPIO_Perif_Addr;  
    const uint8_t GPIO_Perif_Index;
    const uint8_t SCL_Pin;
    const uint8_t SDA_Pin;
    const uint8_t GPIOPCTL_Index;
}I2C_config_type;


typedef enum
{
  I2C_0 = 0,
  I2C_1 = 1,
  I2C_2 = 2,
  I2C_3 = 3
}I2C_Channel;
	

/********************* UART ***************************/
typedef struct
{
    UART0_Type* const UART_Perif_Addr;           
    GPIOA_Type* const GPIO_Perif_Addr;  
    const uint8_t GPIO_Perif_Index;
    const uint8_t RX_Pin;
    const uint8_t TX_Pin;
    const uint8_t GPIOPCTL_Index;
}UART_config_type;


typedef enum
{
  UART_0 = 0,
  UART_1 = 1,
  UART_2 = 2,
  UART_3 = 3,
  UART_4 = 4,
  UART_5 = 5,
  UART_6 = 6,
  UART_7 = 7
}UART_Channel;


#endif
