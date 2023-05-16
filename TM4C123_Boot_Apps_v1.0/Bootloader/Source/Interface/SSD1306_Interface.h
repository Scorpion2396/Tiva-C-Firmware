#ifndef __SSD1306_INTERFACE_H__
#define __SSD1306_INTERFACE_H__

extern void ssd1306_init(void);
extern void ssd1306_command(uint8_t command);
extern void ssd1306_data(uint8_t data);
extern void ssd1306_clear(void);
extern void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
extern void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t value) ;
extern void ssd1306_refresh() ;
extern void ssd1306_setcursor(uint8_t page, uint8_t column);
extern void ssd1306_Print_String(uint8_t* str);
extern void ssd1306_shiva_logo(void);
extern void ssd1306_set_text_size(uint8_t size);
extern void ssd1306_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
extern void ssd1306_DrawRect(int x, int y, int width, int height);
extern void ssd1306_SetDrawWindow(int x0, int y0, int x1, int y1) ;
extern void ssd1306_set_display_mode(uint8_t mode) ;
extern void ssd1306_DrawCircle(int16_t x0, int16_t y0, uint8_t r) ;
extern void ssd1306_clear_row(uint8_t row_num);

extern void dino_game() ;

#endif
