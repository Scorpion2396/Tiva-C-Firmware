#ifndef __OSC__
#define __OSC__

typedef enum
{
    _16MHz      = 0b1111,
    _8MHz       = 0b1110,
    _4MHz       = 0b1101,
    _2MHz       = 0b1100,
    _1MHz       = 0b1011,
    _500KHz     = 0b0111,
    _250KHz     = 0b0110,
    _125KHz     = 0b0101,
    _62P9KHz    = 0b0100,
    _31P25KHz   = 0b0010,
    _31KHz      = 0b0000,
}Internal_Osc_Freq_Type;

void set_osc_freq(Internal_Osc_Freq_Type freq);

#endif