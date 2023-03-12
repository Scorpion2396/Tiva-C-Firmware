#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "TM4C123GH6PM.h"

#define SSD1306_ADDRESS   0x3C

#define OLED_WIDTH    128
#define OLED_HEIGHT   64

#define SSD1306_PAGES 8

// Define the SSD1306 command and data byte commands
#define SSD1306_COMMAND     0x00
#define SSD1306_DATA        0xC0

// Define the SSD1306 initialization commands
#define SSD1306_COMMAND_DISPLAYOFF            0xAE
#define SSD1306_COMMAND_SETDISPLAYCLOCKDIV    0xD5
#define SSD1306_COMMAND_SETMULTIPLEX          0xA8
#define SSD1306_HEIGHT                        64
#define SSD1306_COMMAND_SETDISPLAYOFFSET      0xD3
#define SSD1306_COMMAND_SETSTARTLINE          0x40
#define SSD1306_COMMAND_CHARGEPUMP            0x8D
#define SSD1306_COMMAND_MEMORYMODE            0x20
#define SSD1306_COMMAND_SEGREMAP              0xA0
#define SSD1306_COMMAND_COMSCANDEC            0xC8
#define SSD1306_COMMAND_SETCOMPINS            0xDA
#define SSD1306_COMMAND_SETCONTRAST           0x81
#define SSD1306_COMMAND_SETPRECHARGE          0xD9
#define SSD1306_COMMAND_SETVCOMDETECT         0xDB
#define SSD1306_COMMAND_DISPLAYALLON_RESUME   0xA4
#define SSD1306_COMMAND_NORMALDISPLAY         0xA6
#define SSD1306_COMMAND_DISPLAYON             0xAF

#define SSD1306_COLUMNADDR   0x21 // Set Column Address
#define SSD1306_PAGEADDR     0x22 // Set Page Address

#define SSD1306_WIDTH 128   // OLED display width in pixels
#define SSD1306_HEIGHT 64   // OLED display height in pixels

// Define the SSD1306 buffer size in bytes
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * (SSD1306_HEIGHT / 8))



/********************function prototype ******************/
void ssd1306_init(void);
void ssd1306_command(uint8_t command);
void ssd1306_data(uint8_t data);
void ssd1306_clear(void);
void ssd1306_set_pixel(uint8_t x, uint8_t y, uint8_t value) ;
void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t value) ;
void ssd1306_refresh() ;
void ssd1306_setcursor(uint8_t column, uint8_t page);
void ssd1306_Print_String(uint8_t* str);



#endif
