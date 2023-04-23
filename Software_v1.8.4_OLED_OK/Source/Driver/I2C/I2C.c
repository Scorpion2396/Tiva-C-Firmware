#include "I2C.h"

/********************* Structure Defination*** ************************/
I2C_config_type I2C_config[] = 
{
  {
    .I2C_Perif_Addr      = (I2C0_Type*)I2C0,
    .GPIO_Perif_Addr     = (GPIOA_Type*)GPIOB,
    .GPIO_Perif_Index    = 1,
    .SCL_Pin             = 2,
    .SDA_Pin             = 3,
    .GPIOPCTL_Index      = 3
  },
  {
    .I2C_Perif_Addr      = (I2C0_Type*)I2C1,
    .GPIO_Perif_Addr     = (GPIOA_Type*)GPIOA,
    .GPIO_Perif_Index    = 0,
    .SCL_Pin             = 6,
    .SDA_Pin             = 7,
    .GPIOPCTL_Index      = 3
  },
  {
    .I2C_Perif_Addr      = (I2C0_Type*)I2C2,
    .GPIO_Perif_Addr     = (GPIOA_Type*)GPIOE,
    .GPIO_Perif_Index    = 4,
    .SCL_Pin             = 4,
    .SDA_Pin             = 5,
    .GPIOPCTL_Index      = 3
  },
  {
    .I2C_Perif_Addr      = (I2C0_Type*)I2C3,
    .GPIO_Perif_Addr     = (GPIOA_Type*)GPIOD,
    .GPIO_Perif_Index    = 3,
    .SCL_Pin             = 0,
    .SDA_Pin             = 1,
    .GPIOPCTL_Index      = 3
  }
};
  
static uint32_t I2C_Index       = 0; 
static int error_code           = 0;
static uint8_t I2C_Init_Flag    =  (uint8_t)0;
static uint32_t I2C_TPR         = 0;
static uint8_t I2C_is_first_data = 0;

/*****************************************************************************************************************************************/
void I2C_Init(I2C_Channel I2C_Ch_Index, uint32_t I2C_Freq_KHz)
{
    I2C_Index = (uint32_t)I2C_Ch_Index;
         
	SYSCTL->RCGCGPIO  |=   (1<<(I2C_config[I2C_Index].GPIO_Perif_Index));  	// enable clock to GPIO port 
	SYSCTL->RCGCI2C   |=   (1<<(I2C_Index));  			        			// enable clock to I2C module

	I2C_config[I2C_Index].GPIO_Perif_Addr->DEN        |=   ((1<<(I2C_config[I2C_Index].SCL_Pin)) | (1<<(I2C_config[I2C_Index].SDA_Pin)));                               // DIGITAL ENABLE  FOR PORT A PIN 6 AND PIN 7;        
	
    I2C_config[I2C_Index].GPIO_Perif_Addr->AFSEL 	  |=   ((1<<(I2C_config[I2C_Index].SCL_Pin)) | (1<<(I2C_config[I2C_Index].SDA_Pin)));                               // ENABLE ALTERNATE FUNCTION SELECT FOR PORT A PIN 6 AND PIN 7               
	
	I2C_config[I2C_Index].GPIO_Perif_Addr->ODR        |=   (1<<(I2C_config[I2C_Index].SDA_Pin));                                          // ENABLE OPEN DRAIN FOR I2C->SDA  ie. PORT A PIN 7 , ie. SDA LINE
	
	I2C_config[I2C_Index].GPIO_Perif_Addr->PCTL       |=   ((I2C_config[I2C_Index].GPIOPCTL_Index<<((I2C_config[I2C_Index].SCL_Pin)*4)) | (I2C_config[I2C_Index].GPIOPCTL_Index<<((I2C_config[I2C_Index].SDA_Pin)*4)));                             //CONIGURING PORT A PIN 6 AND PIN 7 AS I2C 
	
	I2C_config[I2C_Index].I2C_Perif_Addr->MCR         |=   (1<<4) ;             // Enable I2C 1 master function
	
	/* Configure I2C 3 clock frequency to 100 KHz
	TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
        TPR = (16MHz/(2*(6+4)*I2C_Freq_Hz))-1;
	*/
    I2C_TPR = (16000000/(2*(6+4)*I2C_Freq_KHz*1000))-1;
	I2C_config[I2C_Index].I2C_Perif_Addr->MTPR        |=   0x7F & I2C_TPR; 
	
	I2C_Init_Flag    =   (uint8_t)1;
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
static inline void Check_I2C_BUS_busy()
{
//	while((I2C_config[I2C_Index].I2C_Perif_Addr->MCS & (1<<6)) != 0);        // wait till I2C bus is busy
}
/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/
static inline void Check_I2C_busy()
{
    while((I2C_config[I2C_Index].I2C_Perif_Addr->MCS & (1<<0) != 0));        // wait till I2C controller is busy
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
static int Check_I2C_error()
{
	if((I2C_config[I2C_Index].I2C_Perif_Addr->MCS & (1<<1)) == (1<<1))         // check for error detection in communication
	{
            if((I2C_config[I2C_Index].I2C_Perif_Addr->MCS & (1<<4)) == (1<<4))
            {
              ;
            }
            else
            {
                I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =   0x4;               // (STOP I2C communication).	
            }
                
             error_code = I2C_config[I2C_Index].I2C_Perif_Addr->MCS & 0xff;               
             return(0);
	}
	
	else 
            return (1);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Write(uint8_t slave_address , uint8_t data)
{
    I2C_Begin(slave_address);
    I2C_Transmit_byte(data);
}
/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/
void I2C_Write_Memory(uint8_t slave_address , uint8_t slave_memory_address , uint8_t data)
{
        I2C_Write_Memory_Multiple(slave_address, slave_memory_address, &data, 1);
}

/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/

void I2C_Write_Multiple(uint8_t slave_address , uint8_t *data , uint32_t num_of_data)
{
    uint32_t cnt;
    
    I2C_Begin(slave_address);
    
    for(cnt = 0 ; cnt < num_of_data - 1 ; cnt++)
    {
        I2C_Transmit(data[cnt]);
    }
    
    I2C_Transmit_end_byte(data[cnt]);
}

/*****************************************************************************************************************************************/

void I2C_Write_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , uint8_t* data , uint32_t num_of_data)
{
    uint32_t cnt;
    
    I2C_Begin(slave_address);
    I2C_Transmit(slave_memory_address);
    
    for(cnt = 0 ; cnt < num_of_data - 1 ; cnt++)
    {
        I2C_Transmit(data[cnt]);
    }
    
    I2C_Transmit_end_byte(data[cnt]);
}

/*****************************************************************************************************************************************/


void I2C_Begin(uint8_t slave_address)
{
    I2C_config[I2C_Index].I2C_Perif_Addr->MSA     =      (slave_address << 1);       //  Defining Slave address
    
    I2C_is_first_data = 1;
}

/*****************************************************************************************************************************************/

void I2C_Transmit(uint8_t data)
{
    uint8_t error = 0;
    
    if(I2C_is_first_data == 1)
    {
        I2C_config[I2C_Index].I2C_Perif_Addr->MSA    &=      ~(1<<0);	        //  Enable Master transmit mode 
        I2C_config[I2C_Index].I2C_Perif_Addr->MDR     = data ;
        Check_I2C_BUS_busy();
        I2C_config[I2C_Index].I2C_Perif_Addr->MCS     =   ((1<<1) | (1<<0));    // (START, RUN).
        I2C_is_first_data = 0;
    }
    else
    {
        I2C_config[I2C_Index].I2C_Perif_Addr->MDR  = data ;
        I2C_config[I2C_Index].I2C_Perif_Addr->MCS  = (1<<0);                    // (RUN).	
    }
            
    Check_I2C_busy();
/*
    if(Check_I2C_error())
    {
        error = error_code;  			
    } 
*/
}

/*****************************************************************************************************************************************/

void I2C_Transmit_start_byte(uint8_t data)
{
    uint8_t error = 0;
    
    I2C_config[I2C_Index].I2C_Perif_Addr->MSA    &=      ~(1<<0);	        //  Enable Master transmit mode 
    I2C_config[I2C_Index].I2C_Perif_Addr->MDR     = data ;
    Check_I2C_BUS_busy();
    I2C_config[I2C_Index].I2C_Perif_Addr->MCS     =   ((1<<1) | (1<<0));    // (START, RUN).
            
    Check_I2C_busy();
/*
    if(Check_I2C_error())
    {
        error = error_code;  			
    } 
*/
    I2C_is_first_data = 0;
}

/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/

void I2C_Transmit_byte(uint8_t data)
{
    uint8_t error = 0;
    
    I2C_config[I2C_Index].I2C_Perif_Addr->MSA    &=      ~(1<<0);	        //  Enable Master transmit mode 
    I2C_config[I2C_Index].I2C_Perif_Addr->MDR     = data ;
    Check_I2C_BUS_busy();
    I2C_config[I2C_Index].I2C_Perif_Addr->MCS     =   ((1<<2) | (1<<1) | (1<<0));    // (STOP, START, RUN).
            
    Check_I2C_busy();
/*
    if(Check_I2C_error())
    {
        error = error_code;  			
    } 
*/
}

/*****************************************************************************************************************************************/

/*****************************************************************************************************************************************/

void I2C_Transmit_end_byte(uint8_t data)
{
    uint8_t error = 0;
    
    I2C_config[I2C_Index].I2C_Perif_Addr->MDR  = data ;
    I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =   ((1<<2) | (1<<0));            // (STOP, RUN).
            
    Check_I2C_busy();
/*    
    if(Check_I2C_error())
    {
        error = error_code;  			
    } 
*/
}

/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/

void I2C_End()
{
    uint8_t error;
    I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =   ((1<<2) | (1<<0));            // (STOP, RUN).
			
    Check_I2C_busy();
/*   
    if(!Check_I2C_error())
    {
      error = error_code;                                                       // To Do error handler for I2C
    }
*/
}

/*****************************************************************************************************************************************/










/*****************************************************************************************************************************************/
int I2C_Read(uint8_t slave_address)
{
	 uint8_t temp_data[1] = {0};	
	I2C_Read_Multiple(slave_address , temp_data  , 1);
	return (*temp_data);
}
/*****************************************************************************************************************************************/


/*****************************************************************************************************************************************/
void I2C_Read_Multiple(uint8_t slave_address , uint8_t *data , uint32_t num_of_data)
{
	int  error  =  0;
	
	if(I2C_Init_Flag == 0)
	{
		I2C_Init(I2C_0, 100);
	}
	else
	{
		;
	}
	
	if(num_of_data > 0)
	{
		I2C_config[I2C_Index].I2C_Perif_Addr->MSA     =      (slave_address << 1);       //  Defining Slave address
		I2C_config[I2C_Index].I2C_Perif_Addr->MSA    |=      (1<<0);					 //  Enable Master Receive mode 
		
		if(num_of_data == 1)
		{
			Check_I2C_BUS_busy();
			
			I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =   ((1<<2) | (1<<1) | (1<<0));  // (STOP, START, RUN).
			
			Check_I2C_busy();
			
			if(Check_I2C_error())
			{
				*data  =  I2C_config[I2C_Index].I2C_Perif_Addr->MDR ;
			}
		}
		
		else
		{
			Check_I2C_BUS_busy();
			
			I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =   ((1<<3) | (1<<1) | (1<<0));            // (Data Acknowledge Enable, START, RUN).
			
			Check_I2C_busy();
			
			if(Check_I2C_error())
			{
				*data++  =  I2C_config[I2C_Index].I2C_Perif_Addr->MDR ;							// READ DATA FROM I2C BUS
			}
			
			while(num_of_data > (uint8_t)2)
			{
				I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =  ((1<<3) | (1<<0));                 // (Data Acknowledge Enable, RUN).
				
				Check_I2C_busy();

				if(Check_I2C_error())
				{
					*data++  =  I2C_config[I2C_Index].I2C_Perif_Addr->MDR ;						// READ DATA FROM I2C BUS
				}
				
				else
				{
					;                                   		 // error in communication
				}
				
				num_of_data--;
			}
			
			I2C_config[I2C_Index].I2C_Perif_Addr->MCS  =  ((1<<2) | (1<<0));                 // (STOP, RUN).
				
			Check_I2C_busy();

			if(Check_I2C_error())
			{
				*data  =  I2C_config[I2C_Index].I2C_Perif_Addr->MDR ;						// READ DATA FROM I2C BUS
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
void I2C_Read_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , uint8_t *data , uint32_t num_of_data)
{
	
	I2C_Write(slave_address , slave_memory_address);
	
	I2C_Read_Multiple(slave_address ,  data ,  num_of_data);
}
/*****************************************************************************************************************************************/

