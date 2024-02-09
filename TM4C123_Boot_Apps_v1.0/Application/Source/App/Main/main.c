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
#include "bsp.h"
#include "mirtos.h"

/******************************************************************************/
void led1();
void led2();
void led3();

/*********************************************************************/

uint32_t stack_led1[40];
OSThread led1_thread;
void led1()
{
  while(1)
  {
/*    DigitalWrite(PF1, HIGH);
    UART_print("Red Led ON\n\r");
    OS_delay(BSP_TICK_PER_SEC / 100);
    DigitalWrite(PF1, LOW);
    UART_print("Red Led OFF\n\r");
    OS_delay(BSP_TICK_PER_SEC / 100);
*/
    UART_print("LED_1\n\r");
    OS_delay(BSP_TICK_PER_SEC/10);
  }

}

/**********************************************************/
uint32_t stack_led2[40];
OSThread led2_thread;

void led2()
{

  while(1)
  {
 /*     DigitalWrite(PF2, LOW);
      UART_print("Blue Led ON\n\r");
      OS_delay(BSP_TICK_PER_SEC / 200);
      DigitalWrite(PF2, HIGH);
      UART_print("Blue Led OFF\n\r");
      OS_delay(BSP_TICK_PER_SEC / 200);
*/
      UART_print("LED_2\n\r");
      OS_delay(BSP_TICK_PER_SEC/10);
  }

}

/**********************************************************/
uint32_t stack_led3[40];
OSThread led3_thread;

void led3()
{

  while(1)
  {
/*      DigitalWrite(PF3, LOW);
      UART_print("Green Led ON\n\r");
      OS_delay(BSP_TICK_PER_SEC/500);
      DigitalWrite(PF3, HIGH);
      UART_print("Green Led OFF\n\r");
      OS_delay(BSP_TICK_PER_SEC/500);
*/
      UART_print("LED_3\n\r");
      OS_delay(BSP_TICK_PER_SEC/10);
  }

}

/**********************************************************/
uint32_t volatile* intreg;
void main()
{
    UART_init(UART_0,115200);
    BSP_init();
    OS_init();
    
    OSThread_start(&led1_thread,
                   &led1,
                   stack_led1,
                   sizeof(stack_led1));

    OSThread_start(&led2_thread,
                         &led2,
                         stack_led2,
                         sizeof(stack_led2));

    OSThread_start(&led3_thread,
                         &led3,
                         stack_led3,
                         sizeof(stack_led3));


    /* transfer control to the RTOS to run the threads */
    OS_run();
    
}




