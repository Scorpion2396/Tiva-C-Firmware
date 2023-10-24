#ifndef __I2C__
#define __I2C__

void I2C_init(uint16_t I2C_frequency_KHz);
void I2C_begin_transmission();
void I2C_stop_transmission();
void I2C_set_address(uint8_t address, uint8_t read_write_flag);
void I2C_transmit_data(uint8_t data);
void I2C_transmit_data_array(uint8_t data[], uint32_t size);
void I2C_receive_data(uint8_t *data, uint32_t size);
void I2C_write_memory(uint8_t slave_addr, uint8_t memory_addr, uint8_t data);
void I2C_write_memory_array(uint8_t slave_addr, uint8_t memory_addr, uint8_t data[], uint32_t size);


#endif