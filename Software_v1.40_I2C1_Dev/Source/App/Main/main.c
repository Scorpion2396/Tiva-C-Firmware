#include "TM4C123GH6PM.h"
//#include "GPIOdriver.h"
//#include "Timer.h"
//#include <stdio.h>

#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
#include "LCD_Interface.h"
#include "I2C_Interface.h"



 int main()
{
 
  while(1)
  {
	
   Timer_scheduler();

    if(Flag_500ms == 1)
    {

		I2C_Write(0x12 , 8);
        
    }

  }
  
 
}
