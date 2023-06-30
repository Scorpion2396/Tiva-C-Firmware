#ifndef _UART_
#define _UART_

#include "Common_Datatype.h"

#define UART_FR_RXFE (1 << 4)

void UART_init(UART_Channel UART_Ch_Index, uint32_t UART_BaudRate);
void UART_print(uint8_t *data);
void UART_Transmit(uint8_t data);
void Delay(unsigned long counter);
uint8_t UART_Receive();
uint32_t UART_Receive_Long();
uint8_t UART_RxReady();


#endif
