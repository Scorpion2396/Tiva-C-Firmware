
// PIC16F1503 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "I2C_Interface.h"
#include "ssd1306.h"
#include"oscillator.h"
#include"adc.h"
#include"stdio.h"

void delay(uint32_t val)
{
    while(val--);
}

/******************************************************************************/
int main() 
{
    set_osc_freq(_16MHz);
      
    uint8_t data[] = {0x00 , 0xAF}; // Example data to transmit
    uint8_t slaveAddress = 0x3c , led = 0; // Example slave device address
    
    volatile uint16_t ADC_data =  0;
    uint16_t milli_volt = 0;
    uint8_t str[20];

    TRISCbits.TRISC2 = 0;    // Set RC2 as an output (for the LED)
    ANSELCbits.ANSC2 = 0;    // Disable analog input for RC2
    LATCbits.LATC2 = 1;
    
    I2C_init(400U);
    ssd1306_init();
    
    while(1)
    {
        ADC_data = (uint16_t)adc_read();
        ADC_data &= 0x03ff;
        
        //ssd1306_clear_refresh();
        
        ssd1306_setcursor(1,0);
        sprintf(str,"ADC = %hu",ADC_data);
        ssd1306_Print_String(str);
        
        
        ssd1306_setcursor(3,0);
        milli_volt = (uint16_t)(((uint32_t)ADC_data * (uint32_t)3300)/(uint32_t)1023);     
        sprintf(str,"MV = %hu",milli_volt);
        ssd1306_Print_String(str);
        
        
        
        delay(10000);
        delay(10000);
        delay(10000);
    }

    return 0;
}