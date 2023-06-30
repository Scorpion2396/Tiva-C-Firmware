#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "TM4C123GH6PM.h"

#define SSD1306_ADDRESS   0x3C

#define OLED_WIDTH    128
#define OLED_HEIGHT   64

#define SSD1306_WIDTH  128   // OLED display width in pixels
#define SSD1306_HEIGHT 64   // OLED display height in pixels

#define SSD1306_PAGES 8

// Define the SSD1306 command and data byte commands
#define SSD1306_COMMAND     0x00
#define SSD1306_DATA        0xC0
#define SSD1306_DATA_STREAM 0x40

// Define the SSD1306 buffer size in bytes
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * (SSD1306_HEIGHT / 8))

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

#define SSD1306_SET_TEXT_SIZE 	  0x22
#define SSD1306_TEXT_SIZE_2X  	  0x08
#define SSD1306_TEXT_SIZE_1X  	  0x00

#define SSD1306_COLOR_WHITE 1
#define SSD1306_COLOR_BLACK 0

#define START_PAGE_ADDR           0
#define END_PAGE_ADDR             7     // 7 for 128x64, 3 for 128x32 version
#define START_COLUMN_ADDR         0
#define END_COLUMN_ADDR           127


// Display modes
#define SSD1306_DISPLAY_HORIZONTAL 0
#define SSD1306_DISPLAY_VERTICAL   1
#define SSD1306_DISPLAY_PAGE       2

// SSD1306 commands for display mode
#define SSD1306_SETDISPLAYMODE     0x20
#define SSD1306_HORIZONTAL_MODE   0x00
#define SSD1306_VERTICAL_MODE     0x01
#define SSD1306_PAGE_MODE         0x02


/****************************************************************/
/*********************function declaration **********************/
/****************************************************************/
void ssd1306_init(void);
void ssd1306_command(uint8_t command);
void ssd1306_data(uint8_t data);
void ssd1306_buffer_flush(uint8_t *data, uint32_t buffer_size) ;
void ssd1306_clear(void);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t value) ;
void ssd1306_refresh() ;
void ssd1306_setcursor(uint8_t page, uint8_t column);
void ssd1306_Print_String(uint8_t* str);
void ssd1306_shiva_logo(void);
void ssd1306_set_text_size(uint8_t size);
void ssd1306_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void ssd1306_DrawRect(int x, int y, int width, int height);
void ssd1306_SetDrawWindow(int x0, int y0, int x1, int y1) ;
void ssd1306_set_display_mode(uint8_t mode) ;
void ssd1306_DrawCircle(int16_t x0, int16_t y0, uint8_t r) ;

#endif

