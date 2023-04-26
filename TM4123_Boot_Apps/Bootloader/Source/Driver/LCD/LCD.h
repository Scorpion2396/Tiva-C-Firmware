#ifndef Lcd_h
#define Lcd_h

#include "TM4C123GH6PM.h"
#include "Common_Datatype.h"
#include "GPIO_Driver_Interface.h"

void LCD_Setup(GPIO_PORT RS_pin ,  GPIO_PORT EN_pin , GPIO_PORT D4_pin ,    //
	       GPIO_PORT D5_pin , GPIO_PORT D6_pin , GPIO_PORT D7_pin  );

void LCD_Init();
void LCD_SetCursor(uint8_t row , uint8_t pos);
void LCD_Clear();
void LCD_Write(char* lcd_data);
static void Data_Write(uint8_t data);
static void Cmd_Write(uint8_t cmd);
static void upper_nibble(uint8_t UpperNibble_data);
static void lower_nibble(uint8_t LowerNibble_data);
static void toggle_enable_signal();
static void delay(uint8_t count);


#endif			
