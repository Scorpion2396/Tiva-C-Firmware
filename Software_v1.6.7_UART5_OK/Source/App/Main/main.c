#include<stdio.h>
#include "TM4C123GH6PM.h"
//#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
//#include "LCD_Interface.h"
//#include "I2C_Interface.h"
//#include "SPI_Interface.h"
//#include "MCP3208_Interface.h"
//#include "CAN_Interface.h"
#include "UART_Interface.h"
#include "timercnter_interface.h"

uint8_t led_State = 0U;

void main()
{
    int adc_val = 0;
    char str[100];
      
    while(1)
    {
        Timer_scheduler();
        
        if(Flag_500ms == 1)
        {
            adc_val = analogRead(PD1);
            sprintf(str,"%d\r\n", adc_val);
    
            //UART_print("\r\n");
            UART_print(str);
        }

    }
}
