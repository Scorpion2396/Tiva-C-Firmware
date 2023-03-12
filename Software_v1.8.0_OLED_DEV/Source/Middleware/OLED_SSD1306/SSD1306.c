#include "SSD1306.h"
#include "I2C_Interface.h"
#include "TM4C123GH6PM.h"
#include "Common_Macros.h"

const uint8_t font_width = 5;

const uint8_t font_5x8[96][5] = 
{
    {0x00, 0x00, 0x00, 0x00, 0x00}, 		// 20 (space)
    {0x00, 0x00, 0x5f, 0x00, 0x00}, 		// 21 !
    {0x00, 0x07, 0x00, 0x07, 0x00}, 		// 22 "
    {0x14, 0x7f, 0x14, 0x7f, 0x14}, 		// 23 #
    {0x24, 0x2a, 0x7f, 0x2a, 0x12}, 		// 24 $
    {0x23, 0x13, 0x08, 0x64, 0x62}, 		// 25 %
    {0x36, 0x49, 0x55, 0x22, 0x50}, 		// 26 &
    {0x00, 0x05, 0x03, 0x00, 0x00}, 		// 27 '
    {0x00, 0x1c, 0x22, 0x41, 0x00}, 		// 28 (
    {0x00, 0x41, 0x22, 0x1c, 0x00}, 		// 29 )
    {0x14, 0x08, 0x3e, 0x08, 0x14}, 		// 2a *
    {0x08, 0x08, 0x3e, 0x08, 0x08}, 		// 2b +
    {0x00, 0x50, 0x30, 0x00, 0x00}, 		// 2c ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, 		// 2d -
    {0x00, 0x60, 0x60, 0x00, 0x00}, 		// 2e .
    {0x20, 0x10, 0x08, 0x04, 0x02}, 		// 2f /
    {0x3e, 0x51, 0x49, 0x45, 0x3e}, 		// 30 0
    {0x00, 0x42, 0x7f, 0x40, 0x00}, 		// 31 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, 		// 32 2
    {0x21, 0x41, 0x45, 0x4b, 0x31}, 		// 33 3
    {0x18, 0x14, 0x12, 0x7f, 0x10}, 		// 34 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, 		// 35 5
    {0x3c, 0x4a, 0x49, 0x49, 0x30}, 		// 36 6
	{0x01, 0x71, 0x09, 0x05, 0x03}, 		// 37 7
	{0x36, 0x49, 0x49, 0x49, 0x36}, 		// 38 8
	{0x06, 0x49, 0x49, 0x29, 0x1e}, 		// 39 9
	{0x00, 0x36, 0x36, 0x00, 0x00}, 		// 3a :
	{0x00, 0x56, 0x36, 0x00, 0x00}, 		// 3b ;
	{0x08, 0x14, 0x22, 0x41, 0x00}, 		// 3c <
	{0x14, 0x14, 0x14, 0x14, 0x14}, 		// 3d =
	{0x00, 0x41, 0x22, 0x14, 0x08}, 		// 3e >
	{0x02, 0x01, 0x51, 0x09, 0x06}, 		// 3f ?
	{0x32, 0x49, 0x79, 0x41, 0x3e}, 		// 40 @
	{0x7e, 0x11, 0x11, 0x11, 0x7e}, 		// 41 A
	{0x7f, 0x49, 0x49, 0x49, 0x36}, 		// 42 B
	{0x3e, 0x41, 0x41, 0x41, 0x22}, 		// 43 C
	{0x7f, 0x41, 0x41, 0x22, 0x1c}, 		// 44 D
	{0x7f, 0x49, 0x49, 0x49, 0x41}, 		// 45 E
	{0x7f, 0x09, 0x09, 0x09, 0x01}, 		// 46 F
	{0x3e, 0x41, 0x49, 0x49, 0x7a}, 		// 47 G
	{0x7f, 0x08, 0x08, 0x08, 0x7f}, 		// 48 H
	{0x00, 0x41, 0x7f, 0x41, 0x00}, 		// 49 I
	{0x20, 0x40, 0x41, 0x3f, 0x01}, 		// 4a J
	{0x7f, 0x08, 0x14, 0x22, 0x41}, 		// 4b K
	{0x7f, 0x40, 0x40, 0x40, 0x40}, 		// 4c L
	{0x7f, 0x02, 0x0c, 0x02, 0x7f}, 		// 4d M 
	{0x7f, 0x04, 0x08, 0x10, 0x7f}, 		// 4e N
	{0x3e, 0x41, 0x41, 0x41, 0x3e}, 		// 4f O
	{0x7f, 0x09, 0x09, 0x09, 0x06}, 		// 50 P
	{0x3e, 0x41, 0x51, 0x21, 0x5e}, 		// 51 Q
	{0x7f, 0x09, 0x19, 0x29, 0x46}, 		// 52 R
	{0x46, 0x49, 0x49, 0x49, 0x31}, 		// 53 S
	{0x01, 0x01, 0x7f, 0x01, 0x01}, 		// 54 T
	{0x3f, 0x40, 0x40, 0x40, 0x3f}, 		// 55 U
	{0x1f, 0x20, 0x40, 0x20, 0x1f}, 		// 56 V
	{0x3f, 0x40, 0x38, 0x40, 0x3f}, 		// 57 W
	{0x63, 0x14, 0x08, 0x14, 0x63}, 		// 58 X
	{0x07, 0x08, 0x70, 0x08, 0x07}, 		// 59 Y
	{0x61, 0x51, 0x49, 0x45, 0x43}, 		// 5a Z
	{0x00, 0x7f, 0x41, 0x41, 0x00}, 		// 5b [
	{0x02, 0x04, 0x08, 0x10, 0x20}, 		// 5c
	{0x00, 0x41, 0x41, 0x7f, 0x00}, 		// 5d ]
	{0x04, 0x02, 0x01, 0x02, 0x04}, 		// 5e ^
	{0x40, 0x40, 0x40, 0x40, 0x40}, 		// 5f _
	{0x00, 0x01, 0x02, 0x04, 0x00}, 		// 60 `
	{0x20, 0x54, 0x54, 0x54, 0x78}, 		// 61 a
	{0x7f, 0x48, 0x44, 0x44, 0x38}, 		// 62 b
	{0x38, 0x44, 0x44, 0x44, 0x20}, 		// 63 c
	{0x38, 0x44, 0x44, 0x48, 0x7f}, 		// 64 d
	{0x38, 0x54, 0x54, 0x54, 0x18}, 		// 65 e
	{0x08, 0x7e, 0x09, 0x01, 0x02}, 		// 66 f
	{0x0c, 0x52, 0x52, 0x52, 0x3e}, 		// 67 g
	{0x7f, 0x08, 0x04, 0x04, 0x78}, 		// 68 h
	{0x00, 0x44, 0x7d, 0x40, 0x00}, 		// 69 i
	{0x20, 0x40, 0x44, 0x3d, 0x00}, 		// 6a j
	{0x7f, 0x10, 0x28, 0x44, 0x00}, 		// 6b k
	{0x00, 0x41, 0x7f, 0x40, 0x00}, 		// 6c l
	{0x7c, 0x04, 0x18, 0x04, 0x78}, 		// 6d m
	{0x7c, 0x08, 0x04, 0x04, 0x78}, 		// 6e n
	{0x38, 0x44, 0x44, 0x44, 0x38}, 		// 6f o
	{0x7c, 0x14, 0x14, 0x14, 0x08}, 		// 70 p
	{0x08, 0x14, 0x14, 0x18, 0x7c}, 		// 71 q
	{0x7c, 0x08, 0x04, 0x04, 0x08}, 		// 72 r
	{0x48, 0x54, 0x54, 0x54, 0x20}, 		// 73 s
	{0x04, 0x3f, 0x44, 0x40, 0x20}, 		// 74 t
	{0x3c, 0x40, 0x40, 0x20, 0x7c}, 		// 75 u
	{0x1c, 0x20, 0x40, 0x20, 0x1c}, 		// 76 v
	{0x3c, 0x40, 0x30, 0x40, 0x3c}, 		// 77 w
	{0x44, 0x28, 0x10, 0x28, 0x44}, 		// 78 x
	{0x0c, 0x50, 0x50, 0x50, 0x3c}, 		// 79 y
	{0x44, 0x64, 0x54, 0x4c, 0x44}, 		// 7a z
	{0x00, 0x08, 0x36, 0x41, 0x00}, 		// 7b {
	{0x00, 0x00, 0x7f, 0x00, 0x00}, 		// 7c |
	{0x40, 0x00, 0x00, 0x00, 0x00}, 		// 7d }
	{0x10, 0x08, 0x08, 0x10, 0x08}, 		// 7e ~
	{0x78, 0x46, 0x41, 0x46, 0x78}, 		// 7f DEL
};

uint8_t ssd1306_current_col  = 0;
uint8_t ssd1306_current_page = 0;


// The SSD1306 display buffer
static uint8_t ssd1306_buffer[SSD1306_BUFFER_SIZE];

// Send a command byte to the SSD1306 display
void ssd1306_command(uint8_t command) 
{
    // Send the control and command bytes to the display over I2C
    I2C_Write_Memory(SSD1306_ADDRESS, SSD1306_COMMAND, command);
}


// Send a data byte to the SSD1306 display
void ssd1306_data(uint8_t data) 
{	
	// Send the control and data bytes to the display over I2C
	I2C_Write_Memory(SSD1306_ADDRESS, SSD1306_DATA, data);
}

// Initialize the SSD1306 display
void ssd1306_init(void) 
{
    // Reset the display
    ssd1306_command(SSD1306_COMMAND_DISPLAYOFF);
    ssd1306_command(SSD1306_COMMAND_SETDISPLAYCLOCKDIV);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_COMMAND_SETMULTIPLEX);
    ssd1306_command(SSD1306_HEIGHT - 1);
    ssd1306_command(SSD1306_COMMAND_SETDISPLAYOFFSET);
    ssd1306_command(0x0);
    ssd1306_command(SSD1306_COMMAND_SETSTARTLINE | 0x0);
    ssd1306_command(SSD1306_COMMAND_CHARGEPUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_COMMAND_MEMORYMODE);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_COMMAND_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMMAND_COMSCANDEC);
    ssd1306_command(SSD1306_COMMAND_SETCOMPINS);
    ssd1306_command(0x02);
    ssd1306_command(SSD1306_COMMAND_SETCONTRAST);
    ssd1306_command(0x8F);
    ssd1306_command(SSD1306_COMMAND_SETPRECHARGE);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_COMMAND_SETVCOMDETECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_COMMAND_DISPLAYALLON_RESUME);
    ssd1306_command(SSD1306_COMMAND_NORMALDISPLAY);
    ssd1306_command(SSD1306_COMMAND_DISPLAYON);
    
    // Clear the display buffer
    ssd1306_clear();
}

// Clear the SSD1306 display buffer
void ssd1306_clear(void) 
{
    for (uint16_t i = 0; i < sizeof(ssd1306_buffer); i++) 
	{
        ssd1306_buffer[i] = 0x00;
    }
}

// Set a pixel in the SSD1306 display buffer
/*
* The function takes three arguments: x, y, and value. 
* x and y specify the coordinates of the pixel, 
* and value specifies whether the pixel should be turned on (value = 1) or off (value = 0).
*/
void ssd1306_set_pixel(uint8_t x, uint8_t y, uint8_t value) 
{
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) 
	{
        return;
    }

    if (value) 
	{
        ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
    } 
	else 
	{
        ssd1306_buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

// Draw a line on the SSD1306 display buffer
void ssd1306_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t value) 
{
    // Bresenham's line algorithm
    int16_t dx = DIFF(x1, x0);
    int16_t dy = DIFF(y1, y0);
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t sy = y0 < y1 ? 1 : -1;
    int16_t err = dx - dy;

    // Set the pixels along the line
    while (1) 
	{
        // Set the current pixel
        ssd1306_set_pixel(x0, y0, value);

        // Check if the end point is reached
        if (x0 == x1 && y0 == y1) 
		{
            break;
        }

        // Update the error and move to the next pixel
        int16_t e2 = 2 * err;
        if (e2 > -dy) 
		{
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) 
		{
            err += dx;
            y0 += sy;
        }
    }
}

// Refresh the display with the contents of the display buffer
void ssd1306_refresh() 
{
    // Set the column address range
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(0);
    ssd1306_command(SSD1306_WIDTH - 1);

    // Set the page address range
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(0);
    ssd1306_command((SSD1306_HEIGHT / 8) - 1);

    // Send the display buffer
    for (uint16_t i = 0; i < SSD1306_BUFFER_SIZE; i++) 
	{
        ssd1306_data(ssd1306_buffer[i]);
    }
}


//Set the cursor (x = column , y = page)
void ssd1306_setcursor(uint8_t column, uint8_t page) 
{
    if (column >= SSD1306_WIDTH || page >= SSD1306_PAGES) 
	{
        return; // Invalid coordinates
    }

    ssd1306_current_col = column;
    ssd1306_current_page = page;

    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(column);
    ssd1306_command(SSD1306_WIDTH - 1);
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(page);
    ssd1306_command(SSD1306_PAGES - 1);
}

//Print string
void ssd1306_Print_String(uint8_t* str)
{
	uint16_t str_cnt = 0;
	uint8_t font_col = 0;
	
	for(str_cnt = 0 ; str[str_cnt] != '\0' ; str_cnt++)
	{
		if((str[str_cnt] >= 32) && (str[str_cnt] <= 127))
		{
			for(font_col = 0 ; font_col < 5 ; font_col++)
			{
				ssd1306_data(font_5x8[str[str_cnt] - 32][font_col]);
                                
                                if(ssd1306_current_col < (SSD1306_WIDTH - font_width))
                                {
                                   ssd1306_current_col += font_width;
                                }
                                else
                                {
                                   ssd1306_current_col += font_width;
                                   ssd1306_current_col %= SSD1306_WIDTH ;
                                   
                                   if(ssd1306_current_page < (SSD1306_PAGES - 1))
                                   {
                                       ssd1306_current_page++;
                                   }
                                   else
                                   {
                                       ssd1306_current_page = 0;
                                   }
                                }
			}	
		}
		
	}
}

