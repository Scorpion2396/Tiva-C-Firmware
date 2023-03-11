#ifndef I2C_H
#define I2C_H

#include "TM4C123GH6PM.h"
#include "Common_Datatype.h"

/******************* function prototypes *********************/
void I2C_Init(I2C_Channel I2C_Ch_Index, uint32_t I2C_Freq_KHz);

void I2C_Write(uint8_t slave_address , uint8_t data );
void I2C_Write_Memory(uint8_t slave_address , uint8_t slave_memory_address , uint8_t data );
void I2C_Write_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data);
void I2C_Write_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , char* data , uint8_t num_of_data);

int I2C_Read(uint8_t slave_address);
void I2C_Read_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data);
int I2C_Read_Memory(uint8_t slave_address , uint8_t slave_memory_address);
void I2C_Read_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , char *data , uint8_t num_of_data);


static void Check_I2C_BUS_busy();
static void Check_I2C_busy();
static int Check_I2C_error();

#endif
