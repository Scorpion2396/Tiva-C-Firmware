/*
 * MCP3208.c
 *
 *  Created on: 24-Jul-2021
 *      Author: saksham
 */

/******************************************************************************************************************************/

#include "SPI_Interface.h"
#include "TM4C123GH6PM.h"
#include "MCP3208.h"
//#include<stdio.h>

unsigned int MCP3208_Rec_data[8]        = {0};
static 	uint8_t  channel_no     = 0U;

unsigned int* MCP3208()
{
	static	 uint8_t  temp_rev_byte  = 0U;
	static   uint8_t  temp_send_byte = 0U;
	static   uint32_t temp_rev_data  = 0U;	
	
	for(channel_no = 0 ; channel_no < 8 ; channel_no++)
	{		
		temp_rev_data    = 0U;
		temp_rev_byte    = 0U;
                
                Enable_Chip_Select();
                
                temp_send_byte   =   0U;
                temp_send_byte  |=   ((1<<2) | (1<<1) | (channel_no>>2));       // 0 , 0 , 0 , 0 , 0 , (start_bit = 1) , (Singhle_Mode = 1) , ( D0 )			
		temp_rev_byte    =   SPI_Read_Write(temp_send_byte);			   // Read Write data from SPI and MCP3208	
		temp_rev_data   |=   (0x00 & temp_rev_byte);
		temp_rev_data    =   (temp_rev_data<<8);
		
                temp_send_byte   =  0U;
		temp_send_byte  |=  (channel_no<<6);                            // D1 , D2 , 0 , 0 , 0 , 0 , 0 , 0 , 0			
		temp_rev_byte    =  SPI_Read_Write(temp_send_byte);		// Read Write data from SPI and MCP3208			
		temp_rev_data   |=  (0x0F & temp_rev_byte);
		temp_rev_data    =  (temp_rev_data<<8);
			 
		temp_send_byte   =  0U;				
		temp_rev_byte    =  SPI_Read_Write(temp_send_byte);		// Read Write data from SPI and MCP3208			
		temp_rev_data   |=  (0xFF & temp_rev_byte);			
		
                Disable_Chip_Select();
                
		MCP3208_Rec_data[channel_no] = temp_rev_data;
                
//              printf("ch%d = %d\n",channel_no,MCP3208_Rec_data[channel_no]);		
	}
	
	return (MCP3208_Rec_data);
}
