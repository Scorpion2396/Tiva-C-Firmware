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

uint8_t led_State = 0U;

void main()
{
    int rtc_val = 0;
    char str[100];

    ds3231_write_hrs(0x65);
    ds3231_write_hrs(0x66);
    ds3231_write_min(52);
    ds3231_write_sec(0);
      
    while(1)
    {
        Timer_scheduler();
        
        if(Flag_1000ms == 1)
        {
            rtc_val = ds3231_read_hrs();
            sprintf(str,"%d", rtc_val);
            UART_print("HRS = ");
            UART_print(str);
            
            rtc_val = ds3231_read_min();
            sprintf(str,"%d", rtc_val);
            UART_print(" : MIN = ");
            UART_print(str);
           
            rtc_val = ds3231_read_sec();
            sprintf(str,"%d\r\n", rtc_val);
            UART_print(" : SEC = ");
            UART_print(str);
            
        }

    }
}
