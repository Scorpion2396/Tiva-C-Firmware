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
  
  uint8_t data[4] = {0};
  uint32_t temp_data = 0x01234567;
  
  data[0] = GETBYTE(temp_data , 0);
  data[1] = GETBYTE(temp_data , 1);
  data[2] = GETBYTE(temp_data , 2);
  data[3] = GETBYTE(temp_data , 3);
  
  while(1)
  {
	
   Timer_scheduler();

    if(Flag_20ms == 1)
    {

//		I2C_Write_Multiple(0x12 , data , 3);
      I2C_Write_Memory_Multiple(0x12 , 0x55 , data , 4);
        
    }

  }
  
 
}
