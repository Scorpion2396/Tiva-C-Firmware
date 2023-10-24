#include "adc.h"

uint16_t adc_read(void)
{
    volatile uint16_t data = 0;
/**********************configure the ADC pin *************************/
    
    /* make RC3 as input*/
    TRISCbits.TRISC3 = 1;
    
    /* make RC3 as analog*/
    ANSELCbits.ANSC3 = 1;
            
/****************** configure the ADC peripheral *********************/
    
    /*disable ADC peripheral*/
    ADCON0bits.ADON = 0;
    
    /*clear ADC status(GO/DONE) bit*/
    ADCON0bits.ADGO = 0;
    
    /*select ADC sampling frequency*/
    ADCON1bits.ADCS = 0b001;
    
    /*select ADC reference voltage */
    ADCON1bits.ADPREF = 0;
    
    /*select ADC result format*/
    ADCON1bits.ADFM = 1;
    
    /*select ADC channel*/
    ADCON0bits.CHS = 0b00111; //AIN7=00111
    
    /*Enable ADC*/
    ADCON0bits.ADON = 1;
    
    /*Trigger ADC request by setting (GO/DONE) bit*/
    ADCON0bits.ADGO = 1;
    
    /*Waiting for the end of ADC conversion*/
    while(ADCON0bits.ADGO);
    
    /*Read data from ADC*/
    data = ADRESH ;
    data = (data << 8);
    data = (data| ADRESL)  ;
    
    return (data & 0x03ff);
    
}