#ifndef _UART_
#define _UART_

#include "Common_Datatype.h"

void UART_init(UART_Channel UART_Ch_Index, uint32_t UART_BaudRate);
void UART_print(char *data);
void UART_Transmitter(char data);
void Delay(unsigned long counter);


#endif
