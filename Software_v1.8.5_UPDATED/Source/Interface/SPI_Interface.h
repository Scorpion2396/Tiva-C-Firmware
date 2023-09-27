/*
 * SPI_Interface.h
 *
 *  Created on: 18-Jul-2021
 *      Author: saksham
 */

/******************************************************************************************************************************/

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "Common_Datatype.h"

extern void SSI_2_Init();
extern void SPI_Write(unsigned char data);
extern unsigned char SPI_Read_Write(unsigned char data);
extern void Enable_Chip_Select(GPIO_PORT port_x);
extern void Disable_Chip_Select(GPIO_PORT port_x);

#endif /* DRIVER_SPI_SPI_H_ */
