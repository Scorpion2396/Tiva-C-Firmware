#ifndef __SSD1306_INTERFACE_H__
#define __SSD1306_INTERFACE_H__

extern void ssd1306_init(void);
extern void ssd1306_command(uint8_t command);
extern void ssd1306_data(uint8_t data);
extern void ssd1306_clear(void);
extern void ssd1306_set_pixel(uint8_t x, uint8_t y, uint8_t value) ;
extern void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t value) ;
extern void ssd1306_refresh() ;
extern void ssd1306_setcursor(uint8_t page, uint8_t column);
extern void ssd1306_Print_String(uint8_t* str);

#endif
