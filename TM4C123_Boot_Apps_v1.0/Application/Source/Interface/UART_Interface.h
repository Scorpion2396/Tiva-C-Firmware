/*
 * SPI_Interface.h
 *
 *  Created on: 18-Jul-2021
 *      Author: saksham
 */

/******************************************************************************************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "Common_Datatype.h"

extern void UART_print(char *data);
extern void UART_init(UART_Channel UART_Ch_Index, uint32_t UART_BaudRate);

#endif /* DRIVER_SPI_SPI_H_ */
