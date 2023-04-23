#include<stdio.h>
#include "TM4C123GH6PM.h"
#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
//#include "LCD_Interface.h"
#include "I2C_Interface.h"
//#include "SPI_Interface.h"
//#include "MCP3208_Interface.h"
//#include "CAN_Interface.h"
#include "UART_Interface.h"
#include "timercnter_interface.h"
#include "DS3231_Interface.h"
#include "SSD1306_Interface.h"

void delay(uint8_t count);

void main()
{
  int col = 0;
  
  DigitalWrite(PB0,LOW );
  DigitalWrite(PB1, HIGH);
 
  delay(10);
  
  I2C_Init(I2C_2, 500);
  UART_init(UART_0, 115200);
  ssd1306_init();

    ssd1306_shiva_logo();
}


void delay(uint8_t count)
{
	uint32_t i = 0;
	uint32_t j = 0;
	for(i=0 ; i<count ; i++)
	{
		for(j=0 ; j < 3180 ; j++);
	}
}
