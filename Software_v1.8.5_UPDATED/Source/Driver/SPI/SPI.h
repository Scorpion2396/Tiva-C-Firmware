/*
 * SPI.h
 *
 *  Created on: 18-Jul-2021
 *      Author: saksham
 */

/******************************************************************************************************************************/

#ifndef SPI_H_
#define SPI_H_

void SSI_2_Init();
void SPI_Write(unsigned char data);
unsigned char SPI_Read_Write(unsigned char data);
void Enable_Chip_Select(GPIO_PORT port_x);
void Disable_Chip_Select(GPIO_PORT port_x);
static void SSI_2_Init(void);


#endif /* DRIVER_SPI_SPI_H_ */
