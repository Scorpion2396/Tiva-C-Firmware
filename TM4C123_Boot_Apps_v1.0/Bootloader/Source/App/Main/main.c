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

/******************************************************************************/
void Delay_ms(unsigned int delay_value);
unsigned char verify_apps(void);

/******************************************************************************/
//#define APPS_FLASH_START_ADDR    0x00020000
//#define APPS_STACK_PTR_ADDR      0x20004000
//#define APPS_STACK_SIZE          4096         // 4KB
#define APPS_FLASH_START_ADDR    0x00020000
#define APPS_STACK_PTR_ADDR      (*((unsigned int*)(APPS_FLASH_START_ADDR)))
#define APPS_RESET_HANDLER_ADDR  APPS_FLASH_START_ADDR + 4
#define APPS_INVALID             0xFFFFFFFF

/******************************************************************************/
typedef void (*fun_ptr)(void);

/******************************************************************************/


/******************************************************************************/

void main()
{
    fun_ptr  jump_to_apps = (void(*)(void)) (*((unsigned int*)(APPS_RESET_HANDLER_ADDR)));

    //unsigned int *apps_stack_ptr = (APPS_STACK_PTR_ADDR + APPS_STACK_SIZE);
    unsigned int *apps_stack_ptr = APPS_STACK_PTR_ADDR;

    DigitalWrite(PF2, HIGH);
    Delay_ms(100);
    DigitalWrite(PF2, LOW);


    if(verify_apps())
    {
        __set_MSP(apps_stack_ptr);
        jump_to_apps();
    }
    else
    {
        while(1)
            DigitalWrite(PF1,HIGH);
    }
}

/**************************************************************************************/
void Delay_ms(unsigned int delay_value)
{
    int a, b;

    for(a=0 ; a<delay_value ; a++)
    {
        for(b = 0 ; b<16000 ; b++);

    }
}

/**************************************************************************************/
unsigned char verify_apps(void)
{
    if((*((unsigned int*)(APPS_RESET_HANDLER_ADDR))) != APPS_INVALID)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
