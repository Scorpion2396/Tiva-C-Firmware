#include "GPIOdriver.h"
#include "TM4C123GH6PM.h"
#include "Common_Const.h"

GPIOA_Type* const PORT[6] = { GPIOA , GPIOB , GPIOC , GPIOD , GPIOE , GPIOF };

static uint8_t Port_IO_flag[6] = {(uint8_t)0};
static uint8_t GPIO_Init_flag  = (uint8_t)0;

/************************************* <THIS FUNCTION IS USE TO INITIALIZE DIGITAL INPUT/OUTPUT PORT> ************************************/
void GPIO_Init()
{ 
    SYSCTL->RCGCGPIO = 0x3F;
	
    GPIOA->LOCK = 0x4C4F434B;
    GPIOB->LOCK = 0x4C4F434B;
    GPIOC->LOCK = 0x4C4F434B;
    GPIOD->LOCK = 0x4C4F434B;
    GPIOE->LOCK = 0x4C4F434B;
    GPIOF->LOCK = 0x4C4F434B;
       
    GPIO_Init_flag = (uint8_t)1;  
}

/************************************************ <THIS FUNCTION IS USE FOR DIGITAL WRITE> **********************************************/
void DigitalWrite(GPIO_PORT port_x , GPIO_HI_LO value)
{
	uint8_t port_num = ((port_x)/(uint8_t)10) ;
	uint8_t pin_num  = ((port_x)%(uint8_t)10) ;
        
    uint8_t IO_flag = (Port_IO_flag[port_num] & (1<<(pin_num)));
            IO_flag = (IO_flag >> pin_num);      
                
 	//printf("out op_flag = %d\n",OP_flag);	
    
	// printf("out ip_flag = %d\n",IP_flag); 
	
	if(GPIO_Init_flag == 0)
	{
		GPIO_Init();
	}
	
				
	if(IO_flag == 0) 
	{
		PORT[port_num]->CR     |=  (1<<(pin_num));
		//	PORT[port_num]->AFSEL  &= ~(1<<(pin_num));
		PORT[port_num]->DIR    |=  (1<<(pin_num));
	    PORT[port_num]->DEN    |=  (1<<(pin_num));
	    
	    Port_IO_flag[port_num] |= (1<<(pin_num));
	}	
			
	else
	{
        ;
	} 
			
	if(value == HIGH)   
	{
        PORT[port_num]->DATA  |=  (1<<(pin_num));
	}
    		
    else
    {
    	PORT[port_num]->DATA  &=  ~(1<<(pin_num));
	}

}


/************************************************ <THIS FUNCTION IS USE FOR DIGITAL READ> **********************************************/
char DigitalRead(GPIO_PORT port_x , GPIO_PU_PD state)
{
		
	uint8_t port_num = ((port_x) / (uint8_t)10) ;
	uint8_t pin_num  = ((port_x) % (uint8_t)10) ;
        
    uint8_t IO_flag = (Port_IO_flag[port_num] & (1<<(pin_num)));
            IO_flag = (IO_flag >> pin_num);
                              
 	// printf("in op_flag = %d\n",OP_flag);	
    // printf("in ip_flag = %d\n",IP_flag);
	
	__IO uint8_t Input_Data = 0U;
	
	if(GPIO_Init_flag == 0)
	{
		GPIO_Init();	
	}


	if(IO_flag == 0)
	{
		PORT[port_num]->CR     |=  (1<<(pin_num));
	//	PORT[port_num]->AFSEL  &= ~(1<<(pin_num));				
		PORT[port_num]->DIR    &= ~(1<<(pin_num));
	    PORT[port_num]->DEN    |=  (1<<(pin_num));
	    		
	    Port_IO_flag[port_num] |= (1<<(pin_num));
    }
			
	else
	{
        ;
	} 
			
			
	if( state == PU )
	{
		PORT[port_num]->PUR   |=  (1<<(pin_num));				
	}
	
	else
	{
		PORT[port_num]->PDR   |=  (1<<(pin_num));				
	}
			 	
    Input_Data  = PORT[port_num]->DATA;      
	Input_Data &= (1 << (pin_num));
	Input_Data  = (Input_Data >> (pin_num));
                      
return(Input_Data);
    		
}
