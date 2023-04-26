#ifndef Lcd_Interface_h
#define Lcd_Interface_h

#include "Common_Datatype.h"
#include "TM4C123GH6PM.h"

extern void LCD_Setup(GPIO_PORT RS_pin ,  GPIO_PORT EN_pin , GPIO_PORT D4_pin ,    //
			          GPIO_PORT D5_pin , GPIO_PORT D6_pin , GPIO_PORT D7_pin  );
extern void LCD_Init();
extern void LCD_SetCursor(uint8_t row , uint8_t pos);
extern void LCD_Clear();
extern void LCD_Write(char* lcd_data);


#endif	
