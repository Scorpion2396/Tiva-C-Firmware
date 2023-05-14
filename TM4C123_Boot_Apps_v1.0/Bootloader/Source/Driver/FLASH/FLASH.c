#include "TM4C123GH6PM.h"
#include "FLASH.h"
/**********************************************************************/
void FlashProgram_ByteArr(uint32_t address, uint8_t *data, uint32_t count)
{

    uint32_t cnt  = 0;
    uint32_t addr = 0;
    uint32_t data_long = 0;
    uint32_t rem_bytes = count % 4;


    for (cnt = 0 , addr = address ; cnt < count; cnt+=4 , addr+=4 )
    {
        data_long  = (uint32_t)((data[cnt+3]<<24) | (data[cnt+2]<<16) | (data[cnt+1]<<8) | (data[cnt+0]<<0));
        // Write the word to the flash memory data register
        FLASH_FMD = data_long;

        // Start the write operation
        FLASH_FMA = 0x3ffff & addr;

        //write wrkey , write and comit
        FLASH_FMC = FLASH_FMC_WRKEY | FLASH_FMC_WRITE  ;

        // Wait for the write operation to complete
        while (FLASH_FMC & (FLASH_FMC_WRITE | FLASH_FMC_COMT));

        // Check if the write operation was successful
        if (*(volatile uint32_t *)addr != data_long)
        {
            // Error: the write operation was unsuccessful
            return;
        }

    }

    if(rem_bytes)
    {
        switch(rem_bytes)
        {
        case 1:
            data_long  = (uint32_t)((0<<24) | (0<<16) | (0<<8) | (data[cnt+0]<<0));
            break;

        case 2:
            data_long  = (uint32_t)((0<<24) | (0<<16) | (data[cnt+1]<<8) | (data[cnt+0]<<0));
            break;

        case 3:
            data_long  = (uint32_t)((0<<24) | (data[cnt+2]<<16) | (data[cnt+1]<<8) | (data[cnt+0]<<0));
            break;

        default:
            break;
        }
    }

}
/***********************************************************************/

void FlashProgram(uint32_t address, uint32_t *data, uint32_t count)
{

    uint32_t cnt  = 0;
    uint32_t addr = 0;

    for (cnt = 0 , addr = address ; cnt < count; cnt++ , addr+=4 )
	{
        // Write the word to the flash memory data register
        FLASH_FMD = data[cnt];

        // Start the write operation
        FLASH_FMA = 0x3ffff & addr;

        //write wrkey , write and comit
        FLASH_FMC = FLASH_FMC_WRKEY | FLASH_FMC_WRITE  ;

        // Wait for the write operation to complete
        while (FLASH_FMC & (FLASH_FMC_WRITE | FLASH_FMC_COMT));

        // Check if the write operation was successful
        if (*(volatile uint32_t *)addr != data[cnt])
		{
            // Error: the write operation was unsuccessful
            return;
        }

    }
}

/*********************************************************************/
void FlashErase(uint32_t address, uint32_t count)
{

    uint32_t cnt  = 0;
    uint32_t addr = 0;

    for (cnt = 0 , addr = address ; cnt < count; cnt++ , addr+=4 )
    {
        // Start the Erase operation
        FLASH_FMA = 0x3ffff & addr;

        //write wrkey , Erase
        FLASH_FMC = FLASH_FMC_WRKEY | FLASH_FMC_ERASE ;

        // Wait for the Erase operation to complete
        while (FLASH_FMC & (FLASH_FMC_ERASE | FLASH_FMC_COMT));

        // Check if the Erase operation was successful
        if (*(volatile uint32_t *)addr != 0xFFFFFFFF)
        {
            // Error: the Erase operation was unsuccessful
            return;
        }

    }
}
