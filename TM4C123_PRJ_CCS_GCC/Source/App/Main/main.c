#include "TM4C123GH6PM.h"
//#include "GPIOdriver.h"
//#include "Timer.h"

#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "Common_Datatype.h"


int main()
{
    __enable_irq();

	int sw1 = 0 ;
    int sw2 = 0 ;

  
  while(1)
  {

      sw1 = DigitalRead(PF0,PU);  //normally sw1 = 1, when sw1 is pressed sw1 = 0
      sw2 = DigitalRead(PF4,PU);  //normally sw2 = 1, when sw2 is pressed sw2 = 0

      if(sw1 == 0 && sw2 == 1)
          DigitalWrite( PF3 , HIGH);
      else
          DigitalWrite( PF3 , LOW);


      if(sw2 == 0 && sw1 == 1)
          DigitalWrite( PF1 , HIGH);
      else
          DigitalWrite( PF1 , LOW);


      if(sw1 == 0 && sw2 == 0)
          DigitalWrite( PF2 , HIGH);
      else
          DigitalWrite( PF2 , LOW);


/*  	Timer_0();
  	
    
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
      		    
	} */


  }
}
