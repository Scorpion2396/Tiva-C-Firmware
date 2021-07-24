/*
 * SPI.c
 *
 *  Created on: 18-Jul-2021
 *      Author: saksham
 */
/***************************************************************************************************************************************************************************************/

#include "TM4C123GH6PM.h"
#include "GPIO_Driver_Interface.h"
#include "Common_Macros.h"
#include "Common_Datatype.h"
#include "SPI.h"

static uint8_t SPI_2_Init_Flag = 0U;


void SSI_2_Init()
{
  	SYSCTL->RCGCSSI   |=   (1<<2);  			 // enable clock to SSI_2 module
	SYSCTL->RCGCGPIO  |=   0x3F;  			   	 // enable clock to ALL GPIO port

	GPIOB->DEN        |=   ((1<<4) | (1<<6) | (1<<7));       // DIGITAL ENABLE  FOR PORT B PIN 4, PIN 6 AND PIN 7
	GPIOB->AFSEL 	  |=   ((1<<4) | (1<<6) | (1<<7));   	 // ENABLE ALTERNATE FUNCTION SELECT FOR PORT B PIN 4, PIN 6 AND PIN 7
	GPIOB->PCTL        =   ((2<<16) | (2<<24) | (2<<28));    //CONIGURING PORT B PIN 4, PIN 6 AND PIN 7 AS SSI
	SSI2->CR1          =   0;				 //(SSE = 0)  SSI Synchronous Serial Port operation is disabled.
	SSI2->CR1         &=  ~(1<<2);			         //(MS = 0)   SSI as Master.
	SSI2->CC           =   0x0;			         //(CS = 0)   SSI USES System clock (based on clock source and divisor factor).
	SSI2->CPSR         =   0x10;				 //(CPSDVSR = 16)  SSInClk = SysClk / CPSDVSR       ==> SSInClk = 16MHz/16 ==> 1MHz
	SSI2->CR0         |=   (1<<8);                           //(SCR = 1)       BR      = SSInClk / (1 + SCR))   ==> BR      =  1MHz/2  ==> 500KHz
	SSI2->CR0         &=  ~(1<<7);                           //(SPH = 0)   SSI Serial Clock Phase  = 0   ==> Data is captured on the first clock edge transition.
	SSI2->CR0         &=  ~(1<<6);                           //(SPO = 0)   SSI Serial Clock Polarity  = 0   ==> A steady state Low value is placed on the SSInClk pin.
	SSI2->CR0         &=  ~((1<<4) | (1<<5));                //(FRF = 0)   SSI Frame Format Select = 0  ==> Freescale SPI Frame Format
	SSI2->CR0         |=   (0x7<<0);                         //(DSS = 0x7)  SSI Data Size Select = 0x7 ==>  8-bit data.
	SSI2->CR1         |=   (1<<1);				 //(SSE = 1)  SSI Synchronous Serial Port operation is enabled.

	SPI_2_Init_Flag = 1U;
}

/*********************************************************************************************************************************/

void SPI_Write(unsigned char data)
{
	if(SPI_2_Init_Flag == 0)
	{
		SSI_2_Init();
	}

	else
	{
		;
	}

    DigitalWrite(PA4, LOW);          /* Make PA4 Chip Selection line (SS) low */

    while((SSI2->SR & 2) == 0);      /* wait untill Tx FIFO is not full */

    SSI2->DR = data;                 /* transmit byte over SSI1Tx line */

    while(SSI2->SR & 0x10);          /* wait until transmit complete */

    DigitalWrite(PA4, HIGH);         /* keep Chip selection line (PA4) high in idle condition */
}

/************************************************************************************************************************************/






