#include <xc.h>
#include <stdint.h>
#include "I2C.h"

#define SYSTEM_CLK_KHZ 16000  // 4MHz

// MSSP defines and macros
#define I2C_BUS_IDLE   !(SSP1STATbits.R_nW | (0x1F & SSP1CON2))                // R/W bit OR-ing with SEN, RSEN, PEN, RCEN or ACKEN will indicate if the MSSP is in Idle mode.
#define I2C_START      (SSP1CON2bits.SEN)                                      // I2C Start 
#define I2C_RESTART    (SSP1CON2bits.RSEN)                                     // I2C Restart
#define I2C_STOP       (SSP1CON2bits.PEN)                                      // I2C Stop
#define I2C_NACKED     (SSP1CON2bits.ACKSTAT)                                  // Returns true if the client NACK'ed, false if the client ACK'ed

#define WRITE_DATA 0
#define READ_DATA  1

/*************************************************/
void I2C_init(uint16_t I2C_frequency_KHz)
{
    // Configure I2C pins (SCL and SDA) as inputs
    TRISCbits.TRISC0 = 1; // SCL as input
    TRISCbits.TRISC1 = 1; // SDA as input
    
    //Disable analog mode
    ANSELCbits.ANSC0 = 0;
    ANSELCbits.ANSC1 = 0;
    
    //RESET I2C Reg
    SSPCON1 = 0x00;
    SSP1STAT = 0x00;
    SSPCON2 = 0x00;
    SSPCON3 = 0x00;
    
    //I2C in Standard Mode , Disable slew rate
    SSPSTATbits.SMP = 0x1;

    //I2C Host Mode
    SSP1CON1bits.SSPM =  0b1000; //Master mode

    // Set I2C master mode, clock = FOSC / (4 * (SSP1ADD + 1)) , FOSC = 4MHz
    // SSP1ADD = (((FOSC / (4 * clock )) - 1)
    //SSP1ADD = 0x09;        // Example baud rate for 100 kHz
    SSP1ADD = ((SYSTEM_CLK_KHZ / (4 * I2C_frequency_KHz )) - 1);   
    
    //Clear the host interrupt flag
    PIR1bits.SSP1IF = 0;
    
    //Disable the interrupt 
    PIE1bits.SSP1IE = 0;
    
    SSP1CON1bits.SSPEN = 1; // Enable I2C
     
}

/*************************************************/
void I2C_begin_transmission() 
{
    //Wait until the I2C Bus is not idle
    while(!I2C_BUS_IDLE);
    
    //Set the start bit
    I2C_START = 1;

    while(I2C_START);
}

/*************************************************/
void I2C_stop_transmission() 
{
    //Set I2C stop bit
    I2C_STOP = 1;
    
    //wait until I2C module is idle
    while(!I2C_STOP);
}

/*************************************************/
void I2C_set_address(uint8_t address, uint8_t read_write_flag) 
{
    if(read_write_flag == 1) // read condition
    {
        //send I2C address
        SSP1BUF = ((address << 1) + 0x01);
    }
    else
    {
        //send I2C address
        SSP1BUF = ((address << 1) & 0xFE);
    }
    
    while(!I2C_BUS_IDLE);
    
    if(I2C_NACKED)
    {
        I2C_stop_transmission();
    }
    
}

/*************************************************/
void I2C_transmit_data_array(uint8_t data[], uint32_t size) 
{
    for (uint32_t i = 0; i < size; i++) 
    {

        // Write data byte to the I2C bus
        SSP1BUF = data[i];
        while(!I2C_BUS_IDLE); // Wait for acknowledge
    }
}

/*************************************************/
void I2C_transmit_data(uint8_t data) 
{
    // Write data byte to the I2C bus
    SSP1BUF = data;
    while(!I2C_BUS_IDLE); // Wait for acknowledge
}

/*************************************************/
void I2C_receive_data(uint8_t *data, uint32_t size) 
{
    for (uint32_t i = 0; i < size; i++) 
    {
        if (i == (size - 1)) {
            // Last byte to be received, so send NACK
            SSP1CON2bits.ACKDT = 1; // NACK
        } 
        else 
        {
            // More bytes to receive, so send ACK
            SSP1CON2bits.ACKDT = 0; // ACK
        }
        
        SSP1CON2bits.ACKEN = 1; // Enable ACK/NACK bit
        while (SSP1CON2bits.ACKEN); // Wait for ACK/NACK to be sent
        
        // Wait for the receive buffer to be full
        while (!SSP1STATbits.BF);
        
        // Read received data
        data[i] = SSP1BUF;
    }
}


/*************************************************/
void I2C_write_memory(uint8_t slave_addr, uint8_t memory_addr, uint8_t data)
{
    I2C_begin_transmission();
    I2C_set_address(slave_addr, WRITE_DATA);
    I2C_transmit_data(memory_addr);
    I2C_transmit_data(data);
    I2C_stop_transmission();
}

/*************************************************/
void I2C_write_memory_array(uint8_t slave_addr, uint8_t memory_addr, uint8_t data[], uint32_t size)
{
    I2C_begin_transmission();
    I2C_set_address(slave_addr, WRITE_DATA);
    I2C_transmit_data(memory_addr);
    I2C_transmit_data_array(data, size);
    I2C_stop_transmission();
}
