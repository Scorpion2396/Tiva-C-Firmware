#ifndef GPIOdriver_H
#define GPIOdriver_H

#include "Common_Datatype.h"

void GPIO_Init();
void DigitalWrite(GPIO_PORT port_x , GPIO_HI_LO value);
uint8_t DigitalRead(GPIO_PORT port_x , GPIO_PU_PD state);

#endif

