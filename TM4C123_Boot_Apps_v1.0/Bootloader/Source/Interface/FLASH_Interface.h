/*
 * FLASH_Interface.h
 *
 *  Created on: 07-May-2023
 *      Author: saksh
 */

#ifndef _FLASH_INTERFACE_H_
#define _FLASH_INTERFACE_H_

extern uint8_t FlashProgram(uint32_t address, uint32_t *data, uint32_t count);
extern uint8_t FlashProgram_ByteArr(uint32_t address, uint8_t *data, uint32_t count);
extern uint8_t FlashErase(uint32_t address, uint32_t count);

#endif /* SOURCE_INTERFACE_FLASH_INTERFACE_H_ */
