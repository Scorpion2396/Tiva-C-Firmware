#ifndef  ADC_DRIVER_H
#define  ADC_DRIVER_H

#include "Common_Datatype.h"
#include "GPIO_Driver_Interface.h"

uint32_t analogRead(GPIO_PORT port_num);
void ADC_Init();
static void ADC_port_Init(uint8_t port_num ,  uint8_t pin_num , uint8_t adc_ch);
static void ADC_SS_Init(int AINn);

#endif
