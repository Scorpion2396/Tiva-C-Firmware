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
  int cnt = 0;
  unsigned int curr_time = 0;
  unsigned char str[100] = {0};
  int fps = 0;
  
  
  DigitalWrite(PB0,LOW );
  DigitalWrite(PB1, HIGH);
  DigitalWrite(PF3, HIGH);
  delay(100);
  
  init_Timer_Counter();
  I2C_Init(I2C_2, 600);
  ssd1306_init();
  
  Start_Timer_counter();
  
    while (1) 
    { 

        cnt+=1;
        ssd1306_clear();
        ssd1306_DrawCircle(cnt, 32, 10);
        ssd1306_draw_line(0, 43, 127, 43, 1); 
        ssd1306_refresh(); 
        
        if(cnt == 127)
          cnt = 0;

        
        curr_time = millis();    
        sprintf(str,"Curr time = %d\r\n", curr_time);
//        UART_print(str);


        fps = 1000/curr_time;
        sprintf(str,"FPS = %d\r\n", fps);
        ssd1306_setcursor(7,5);
        ssd1306_Print_String(str);


        Refresh_Timer_counter();
        curr_time = 0;
        
        
        
        
    }

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
