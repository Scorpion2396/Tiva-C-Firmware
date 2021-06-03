#include "TM4C123GH6PM.h"
//#include "GPIOdriver.h"
//#include "Timer.h"
#include <stdio.h>

#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"



int main()
{
    DigitalWrite(PF2,HIGH);
    DigitalWrite(PF3,LOW);
    DigitalWrite(PB3,HIGH);
    DigitalWrite(PC4,LOW);
    DigitalWrite(PC5,HIGH);
    DigitalWrite(PC6,LOW);
    
    volatile int val_1 = 0 ;
    volatile int val_2 = 0 ;
    volatile int val_3 = 0 ;
    volatile int val_4 = 0 ;
    volatile int val_5 = 0 ;
    volatile int val_6 = 0 ;
    
  while(1)
  {
     ADC_0();	
   Timer_0();

  	
   val_1 = analogRead(PE2);
   val_2 = analogRead(PE1);
   val_3 = analogRead(PD3);
   val_4 = analogRead(PD2);
   val_5 = analogRead(PD1);
   val_6 = analogRead(PD0);
    
    if(Flag_1000ms == 1)
    {
        printf("PE2 = %d\n",val_1);
        printf("PE1 = %d\n",val_2);
        printf("PD3 = %d\n",val_3);
        printf("PD2 = %d\n",val_4);
        printf("PD1 = %d\n",val_5);
        printf("PD0 = %d\n",val_6);
      		    
    }

  }
}
