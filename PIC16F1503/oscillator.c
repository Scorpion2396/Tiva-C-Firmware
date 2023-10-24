/*
 * File:   oscillator.c
 * Author: saksh
 *
 * Created on October 5, 2023, 12:27 AM
 */


#include <xc.h>
#include"oscillator.h"

void set_osc_freq(Internal_Osc_Freq_Type freq) 
{
    uint8_t frequency = (uint8_t)freq;
    
    OSCCONbits.SCS = 0b10;   // internal oscillator
    
    if(frequency == 0)
    {
         while(!OSCSTATbits.LFIOFR); // wait till low frequency i.e 31Khz oscillator is ready, view page no. 50 of data sheet
    }
    else
    {
        while(!OSCSTATbits.HFIOFR); // wait till High frequency i.e 16MHz oscillator is ready, view page no. 50 of data sheet
        while(!OSCSTATbits.HFIOFR); // wait till High frequency i.e 16MHz oscillator is stable, view page no. 50 of data sheet 
    }
    OSCCONbits.IRCF = 0b1111;   //16MHz
    return;
}
