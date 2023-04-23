#ifndef    GPIO_INTERFACE_H
#define    GPIO_INTERFACE_H

#include "Common_Datatype.h"
#include "TM4C123GH6PM.h"

extern void GPIO_Init();
extern void DigitalWrite(GPIO_PORT port_x , GPIO_HI_LO value);
extern char DigitalRead(GPIO_PORT port_x , GPIO_PU_PD state);
extern GPIOA_Type* const PORT[6] ;

#endif
