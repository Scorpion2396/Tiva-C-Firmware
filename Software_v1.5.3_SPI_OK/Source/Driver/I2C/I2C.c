#include "I2C.h"


static int error_code = 0;

static uint8_t   I2C_1_Init_Flag  =  (uint8_t)0;

/*****************************************************************************************************************************************/
void I2C_1_Init()
{
	SYSCTL->RCGCGPIO  |=   (1<<0);  			// enable clock to GPIO port D 
	SYSCTL->RCGCI2C   |=   (1<<1);  			// enable clock to I2C_3 module

	GPIOA->DEN        |=   ((1<<6) | (1<<7));   // DIGITAL ENABLE  FOR PORT A PIN 6 AND PIN 7;        
	
    GPIOA->AFSEL 	  |=   ((1<<6) | (1<<7));   // ENABLE ALTERNATE FUNCTION SELECT FOR PORT A PIN 6 AND PIN 7
	
	GPIOA->ODR        |=   (1<<7);              // ENABLE OPEN DRAIN FOR I2C->SDA  ie. PORT A PIN 7 , ie. SDA LINE
	
	GPIOA->PCTL        =   ((3<<28) | (3<<24));   //CONIGURING PORT A PIN 6 AND PIN 7 AS I2C 
	
	I2C1->MCR          =   (1<<4) ;             // Enable I2C 1 master function
	
	/* Configure I2C 3 clock frequency to 100 KHz
	TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
	TPR = (16MHz/(2*(6+4)*100000))-1;
	TPR = 7

        or

        TPR = (16MHz/(2*(6+4)*20000))-1;
	TPR = 39
	*/
	I2C1->MTPR         =   39 ; //
	
	I2C_1_Init_Flag    =   (uint8_t)1;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
static inline void Check_I2C_BUS_busy()
{
//	while((I2C1->MCS & (1<<6)) == (1<<6));        // wait till I2C bus is busy
}
/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/
static inline void Check_I2C_busy()
{
	while((I2C1->MCS & (1<<0) != 0));        // wait till I2C controller is busy
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
static int Check_I2C_error()
{
	if((I2C1->MCS & (1<<1)) == (1<<1))         // check for error detection in communication
	{
            if((I2C1->MCS & (1<<4)) == (1<<4))
            {
              ;
            }
             else
             {
		I2C1->MCS  =   0x4;               // (STOP I2C communication).	
             }
                
             error_code = I2C1->MCS & 0xff;               
             return(0);
	}
	
	else 
		return (1);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Write(uint8_t slave_address , uint8_t data)
{
	char temp_data[1] = {data};	
	I2C_Write_Multiple(slave_address , temp_data  , 1);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Write_Memory(uint8_t slave_address , uint8_t slave_memory_address , uint8_t data)
{
	char temp_data[2] = {slave_memory_address , data};	
	I2C_Write_Multiple(slave_address , temp_data  , 2);
}
/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/
void I2C_Write_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data)
{

        
	int  error  =  0;
	
	if(I2C_1_Init_Flag == 0)
	{
		I2C_1_Init();
	}
	else
	{
		;
	}
	
	if(num_of_data > 0)
	{
		I2C1->MSA     =      (slave_address << 1);       //  Defining Slave address
		I2C1->MSA    &=      ~(1<<0);					 //  Enable Master transmit mode 
		
		if(num_of_data == 1)
		{
			I2C1->MDR = *data;
			
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<2) | (1<<1) | (1<<0));  // (STOP, START, RUN).
			
			Check_I2C_busy();
			
			error = Check_I2C_error();
		}
		
		else
		{
			I2C1->MDR = *data++;
			
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<1) | (1<<0));            // (START, RUN).
			
			while(num_of_data > (uint8_t)2)
			{
                          
                          Check_I2C_busy();
                          
				if(Check_I2C_error())
				{
					I2C1->MDR =  *data++;
					
					I2C1->MCS  =  (1<<0);                 // (RUN).	
				}
				else
				{
					;                                    // error in communication
				}
				
				num_of_data--;
			}
                        
                        Check_I2C_busy();
			
			I2C1->MDR = *data;
			
			I2C1->MCS  =   ((1<<2) | (1<<0));            // (STOP, RUN).
			
			Check_I2C_busy();
			
			error = Check_I2C_error();
		}	
	}
        if(error == 0)
        {
          ;                                                             //I2C communication error
        }

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Write_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , char* data , uint8_t num_of_data)
{
	int  error  =  0;
	
	if(I2C_1_Init_Flag == 0)
	{
		I2C_1_Init();
	}
	else
	{
		;
	}
	
	if(num_of_data > 0)
	{
		
		I2C1->MSA     =      (slave_address << 1);       //  Defining Slave address
		I2C1->MSA    &=      ~(1<<0);					 //  Enable Master transmit mode 
				
		I2C1->MDR = slave_memory_address;
			
		Check_I2C_BUS_busy();
			
		I2C1->MCS  =   ((1<<1) | (1<<0));           				 // (START, RUN).
		
		Check_I2C_busy();		
		
		if(num_of_data == 1)
		{
			I2C1->MDR = *data;
			
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<2) | (1<<0));  // (STOP, RUN).
			
			Check_I2C_busy();
			
			error = Check_I2C_error();
		}
		
		else
		{
			I2C1->MDR = *data++;
			
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<1) | (1<<0));            // (START, RUN).
			
			while(num_of_data > (uint8_t)2)
			{
                          
                          Check_I2C_busy();
                          
				if(Check_I2C_error())
				{
					I2C1->MDR =  *data++;
					
					I2C1->MCS  =  (1<<0);                 // (RUN).	
				}
				else
				{
					;                                    // error in communication
				}
				
				num_of_data--;
			}
                        
                        Check_I2C_busy();
			
			I2C1->MDR = *data;
			
			I2C1->MCS  =   ((1<<2) | (1<<0));            // (STOP, RUN).
			
			Check_I2C_busy();
			
			error = Check_I2C_error();
		}	
	}
        if(error == 0)
        {
          ;                                                             //I2C communication error
        }

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
int I2C_Read(uint8_t slave_address)
{
	 char temp_data[1] = {0};	
	I2C_Read_Multiple(slave_address , temp_data  , 1);
	return (*temp_data);
}
/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/
void I2C_Read_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data)
{
	int  error  =  0;
	
	if(I2C_1_Init_Flag == 0)
	{
		I2C_1_Init();
	}
	else
	{
		;
	}
	
	if(num_of_data > 0)
	{
		I2C1->MSA     =      (slave_address << 1);       //  Defining Slave address
		I2C1->MSA    |=      (1<<0);					 //  Enable Master Receive mode 
		
		if(num_of_data == 1)
		{
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<2) | (1<<1) | (1<<0));  // (STOP, START, RUN).
			
			Check_I2C_busy();
			
			if(Check_I2C_error())
			{
				*data  =  I2C1->MDR ;
			}
		}
		
		else
		{
			Check_I2C_BUS_busy();
			
			I2C1->MCS  =   ((1<<3) | (1<<1) | (1<<0));            // (Data Acknowledge Enable, START, RUN).
			
			Check_I2C_busy();
			
			if(Check_I2C_error())
			{
				*data++  =  I2C1->MDR ;							// READ DATA FROM I2C BUS
			}
			
			while(num_of_data > (uint8_t)2)
			{
				I2C1->MCS  =  ((1<<3) | (1<<0));                 // (Data Acknowledge Enable, RUN).
				
				Check_I2C_busy();

				if(Check_I2C_error())
				{
					*data++  =  I2C1->MDR ;						// READ DATA FROM I2C BUS
				}
				
				else
				{
					;                                   		 // error in communication
				}
				
				num_of_data--;
			}
			
			I2C1->MCS  =  ((1<<2) | (1<<0));                 // (STOP, RUN).
				
			Check_I2C_busy();

			if(Check_I2C_error())
			{
				*data  =  I2C1->MDR ;						// READ DATA FROM I2C BUS
			}
		}	
	}
        
        if(error == 0)
        {
          ;                                                             //I2C communication error
        }

}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
int I2C_Read_Memory(uint8_t slave_address , uint8_t slave_memory_address)
{

	volatile int I2C_recieved_data = 0;
	
	I2C_Write(slave_address , slave_memory_address);
	
	I2C_recieved_data = I2C_Read(slave_address);
	
	return (I2C_recieved_data);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Read_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , char *data , uint8_t num_of_data)
{
	
	I2C_Write(slave_address , slave_memory_address);
	
	I2C_Read_Multiple(slave_address ,  data ,  num_of_data);
}
/*****************************************************************************************************************************************/
