#ifndef _FLASH_H_
#define _FLASH_H_

#define FLASH_FMA              (*((volatile uint32_t *)0x400FD000))
#define FLASH_FMD              (*((volatile uint32_t *)0x400FD004))
#define FLASH_FMC              (*((volatile uint32_t *)0x400FD008))
#define FLASH_FCRIS_R            (*((volatile uint32_t *)0x400FEA08))
#define FLASH_FMC_WRKEY          0xA4420000
#define FLASH_FMC_WRITE          0x1
#define FLASH_FMC_ERASE          0x2
#define FLASH_FMC_MERASE         0x4
#define FLASH_FMC_COMT           0x8

#define FLASH_FMC_RDY            0x00000001

#define FLASH_FMC_START          0x00000001

#define FLASH_BASE_ADDRESS       0x00000000
#define FLASH_BLOCK_SIZE         1024  // 1KB flash block size for TM4C123




uint8_t FlashProgram(uint32_t address, uint32_t *data, uint32_t count);
uint8_t FlashProgram_ByteArr(uint32_t address, uint8_t *data, uint32_t count);
uint8_t FlashErase(uint32_t address, uint32_t count);


#endif