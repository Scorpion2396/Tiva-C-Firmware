#include "DS3231.h"
#include "I2C_Interface.h"

/*******************************************************************************/
static int process_get_data(int value)
{
    return( value - (6 * (value >> 4)));
}

/*******************************************************************************/
static int process_set_data(int value)
{
    return( value + (6 * (value / 10)));
}

/*******************************************************************************/
int ds3231_read_sec()
{
	int rec_data = 0;
        int rec_sec_data = 0;
	
	rec_data = I2C_Read_Memory(DS3231_SLAVE_ADD, DS3231_SEC_ADD);
        
        rec_sec_data = process_get_data(rec_data);
	
	return(rec_sec_data);
}

/*******************************************************************************/
void ds3231_write_sec(int sec_value)
{
        int send_sec_data = 0;
        
        send_sec_data = process_set_data(sec_value);
	
	I2C_Write_Memory(DS3231_SLAVE_ADD, DS3231_SEC_ADD, send_sec_data);	
}

/*******************************************************************************/
int ds3231_read_min()
{
	int rec_data = 0;
        int rec_min_data = 0;
	
	rec_data = I2C_Read_Memory(DS3231_SLAVE_ADD, DS3231_MIN_ADD);
        
        rec_min_data = process_get_data(rec_data);
	
	return(rec_min_data);
}

/*******************************************************************************/
void ds3231_write_min(int min_value)
{
        int send_min_data = 0;
        
        send_min_data = process_set_data(min_value);
	
	I2C_Write_Memory(DS3231_SLAVE_ADD, DS3231_MIN_ADD, send_min_data);	
}

/*******************************************************************************/
int ds3231_read_hrs()
{
	int rec_data = 0;
        int rec_hrs_data = 0;
	
	rec_data = I2C_Read_Memory(DS3231_SLAVE_ADD, DS3231_HRS_ADD);
        
        rec_hrs_data = process_get_data(rec_data);
	
	return(rec_hrs_data);
}

/*******************************************************************************/
void ds3231_write_hrs(int hrs_value)
{
        int send_hrs_data = 0;
        
        send_hrs_data = process_set_data(hrs_value);
	
	I2C_Write_Memory(DS3231_SLAVE_ADD, DS3231_HRS_ADD, send_hrs_data);	
}

