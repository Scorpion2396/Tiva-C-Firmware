#ifndef  ADC_DRIVER_H
#define  ADC_DRIVER_H

#include "Common_Datatype.h"

int analogRead(ADC_PORT port_num);
void ADC_Init();
void ADC_SS_Init(int AINn);

#endif
