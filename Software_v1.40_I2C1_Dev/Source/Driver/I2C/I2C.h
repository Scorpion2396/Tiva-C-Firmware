#ifndef I2C_H
#define I2C_H

#include "TM4C123GH6PM.h"

void I2C_1_Init();
void I2C_Write(uint8_t slave_address , uint8_t data );
void I2C_Write_Memory(uint8_t slave_address , uint8_t slave_memory_address , uint8_t data );
void I2C_Write_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data);
int I2C_Read(uint8_t slave_address);
void I2C_Read_Multiple(uint8_t slave_address , char *data , uint8_t num_of_data);
int I2C_Read_Memory(uint8_t slave_address , uint8_t slave_memory_address);
void I2C_Read_Memory_Multiple(uint8_t slave_address , uint8_t slave_memory_address , char *data , uint8_t num_of_data);


static void Check_I2C_BUS_busy();
static void Check_I2C_busy();
static int Check_I2C_error();

#endif
