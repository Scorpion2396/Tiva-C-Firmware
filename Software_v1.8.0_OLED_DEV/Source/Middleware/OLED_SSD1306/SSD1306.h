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
void ssd1306_setcursor(uint8_t page, uint8_t column);
void ssd1306_Print_String(uint8_t* str);
void ssd1306_shiva_logo(void);





  #define SSD1306_SET_MUX_RATIO     0xA8
  #define SSD1306_SET_DIS_CLK_DIV   0xD5
  #define SSD1306_DISPLAY_OFFSET    0xD3
  #define SSD1306_DISPLAY_ON        0xAF
  #define SSD1306_DISPLAY_OFF       0xAE
  #define SSD1306_DIS_ENT_DISP_ON   0xA4
  #define SSD1306_DIS_IGNORE_RAM    0xA5
  #define SSD1306_DIS_NORMAL        0xA6
  #define SSD1306_DIS_INVERSE       0xA7
  #define SSD1306_DEACT_SCROLL      0x2E
  #define SSD1306_ACTIVE_SCROLL     0x2F
  #define SSD1306_SET_START_LINE    0x40
  #define SSD1306_MEMORY_ADDR_MODE  0x20
  #define SSD1306_SET_COLUMN_ADDR   0x21
  #define SSD1306_SET_PAGE_ADDR     0x22
  #define SSD1306_SEG_REMAP         0xA0
  #define SSD1306_SEG_REMAP_OP      0xA1
  #define SSD1306_COM_SCAN_DIR      0xC0
  #define SSD1306_COM_SCAN_DIR_OP   0xC8
  #define SSD1306_COM_PIN_CONF      0xDA
  #define SSD1306_SET_CONTRAST      0x81
  #define SSD1306_SET_OSC_FREQ      0xD5
  #define SSD1306_SET_CHAR_REG      0x8D
  #define SSD1306_SET_PRECHARGE     0xD9
  #define SSD1306_VCOM_DESELECT     0xDB

  #define START_PAGE_ADDR           0
  #define END_PAGE_ADDR             7     // 7 for 128x64, 3 for 128x32 version
  #define START_COLUMN_ADDR         0
  #define END_COLUMN_ADDR           127


#endif
