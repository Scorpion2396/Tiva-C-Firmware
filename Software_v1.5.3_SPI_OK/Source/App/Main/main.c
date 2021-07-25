
#include "TM4C123GH6PM.h"
#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
#include "LCD_Interface.h"
#include "I2C_Interface.h"
//#include "SPI_Interface.h"
#include "MCP3208_Interface.h"
#include<stdio.h>

void main()
{

unsigned int  *data ;

  while(1)
  {
   Timer_scheduler();

//    if(Flag_50ms == 1)
    {
	   data = MCP3208(); 
           
           printf("ch0 = %d\n",data[0]);
 /*          printf("ch1 = %d\n",data[1]);
           printf("ch2 = %d\n",data[2]);
           printf("ch3 = %d\n",data[3]);
           printf("ch4 = %d\n",data[4]);
           printf("ch5 = %d\n",data[5]);
           printf("ch6 = %d\n",data[6]);
           printf("ch7 = %d\n",data[7]);   */
    }

  }
}
