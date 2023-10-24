#ifndef __I2C_INTERFACE__
#define __I2C_INTERFACE__

extern void I2C_init(uint16_t I2C_frequency_KHz);
extern void I2C_write_memory(uint8_t slave_addr, uint8_t memory_addr, uint8_t data);
extern void I2C_write_memory_array(uint8_t slave_addr, uint8_t memory_addr, uint8_t data[], uint32_t size);

#endif