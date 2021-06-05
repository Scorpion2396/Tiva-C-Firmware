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



 int main()
{
  LCD_Setup(PC6 , PC5 , PC4 , PB3 , PF3 , PF2);
//LCD_Setup(PC6 , PC5 , PC4 , PB3 , PF3 , PF2);

  char a[] = "WELCOME TO";
  char b[] = "EMBEDDED SYSTEM";
  char c[] = "TIVA C LAUNCHPAD";
  char d[] = "INTERFACE WITH LCD";
  


    
  while(1)
  {
	
   Timer_0();
	
   
    
    if(Flag_500ms == 1)
    {
  //      LCD_Clear();
        
        LCD_SetCursor(0,0);
        LCD_Write(a);
     
        LCD_SetCursor(1,0);
        LCD_Write(b);
        
        LCD_SetCursor(2,0);
        LCD_Write(c);
        
        LCD_SetCursor(3,0);
        LCD_Write(d); 
        
    }

  }
  
 
}
