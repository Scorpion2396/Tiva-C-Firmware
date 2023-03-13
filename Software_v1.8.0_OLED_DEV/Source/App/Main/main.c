#include<stdio.h>
#include "TM4C123GH6PM.h"
//#include "GPIO_Driver_Interface.h"
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

void main()
{
  I2C_Init(I2C_2, 300);
  UART_init(UART_0, 115200);
  ssd1306_init();
      
    ssd1306_setcursor(1,0);
    ssd1306_Print_String("Saksham Raj");
          
    ssd1306_setcursor(3,15);
    ssd1306_Print_String("Loves");
          
    ssd1306_setcursor(5,30);
    ssd1306_Print_String("Pratyusha Jha");          
}
