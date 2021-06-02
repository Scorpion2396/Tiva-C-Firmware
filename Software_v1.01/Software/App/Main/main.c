#include "TM4C123GH6PM.h"
//#include "GPIOdriver.h"
//#include "Timer.h"

#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"



int main()
{

	int a = 0 ;
    int b = 0 ;
    int c = 0 ;

  
  while(1)
  {
  	
  	Timer_0();
  	
    
    if(Flag_500ms == 1)
    {
    	a ^= 1;
    	
    	if(a == 1)
       		DigitalWrite( PF1 , HIGH);
       		
   		else
   		   DigitalWrite( PF1 , LOW);
      		    
	}

    if(Flag_1000ms == 1)
    {
    	b ^= 1;
    	
    	if(b == 1)
       		DigitalWrite( PF2 , HIGH);
       		
   		else
   		   DigitalWrite( PF2 , LOW);
      		    
	}
    
        if(Flag_2000ms == 1)
    {
    	c ^= 1;
    	
    	if(c == 1)
       		DigitalWrite( PF3 , HIGH);
       		
   		else
   		   DigitalWrite( PF3 , LOW);
      		    
	}

  }
}
