#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "TM4C123GH6PM.h"
#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
#include "I2C_Interface.h"
#include "UART_Interface.h"
#include "timercnter_interface.h"
#include "DS3231_Interface.h"
#include "SSD1306_Interface.h"

#define WIDTH 128 // Width of the game screen
#define HEIGHT 64 // Height of the game screen
#define MAX_LENGTH 100 // Maximum length of the snake

typedef struct {
    int x, y; // Snake segment position
} Segment;

typedef struct {
    Segment body[MAX_LENGTH]; // Array of snake segments
    int length; // Current length of the snake
} Snake;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;

typedef struct 
{
    Snake snake;        // Snake object
    int fruitX, fruitY; // Fruit position
    bool gameOver;      // Game over flag
    int score;          // Current score
    Direction direction; // Current direction of the snake
} Game;


void initGame(Game* game);
void updateGame(Game* game, bool buttonLeftPressed, bool buttonRightPressed);
void drawGame(Game* game);
void Delay_ms(unsigned int delay_value);

unsigned char is_key_pressed(GPIO_PORT key);
unsigned char is_key_pressed_sw1();
unsigned char is_key_pressed_sw2();

// Function to initialize the game state
void initGame(Game* game) 
{
    game->snake.body[0].x = WIDTH / 2;
    game->snake.body[0].y = HEIGHT / 2;
    game->snake.length = 1;
    game->fruitX = rand() % WIDTH;
    game->fruitY = rand() % HEIGHT;
    game->gameOver = false; // Set gameOver flag to false initially
    game->score = 0;
    game->direction = RIGHT; // Set initial direction to RIGHT
}

void updateGame(Game* game, bool switchLeftPressed, bool switchRightPressed) 
{
    // Check the switch inputs and update the snake's direction
    if (switchLeftPressed)
    {
        // Rotate the snake's direction to the left
        if (game->direction == LEFT)
        {
            game->direction = DOWN;
        }
        else if (game->direction == RIGHT)
        {
            game->direction = UP;
        }
        else if (game->direction == UP)
        {
            game->direction = LEFT;
        }
        else if (game->direction == DOWN)
        {
            game->direction = RIGHT;
        }
    }
    else if (switchRightPressed)
    {
        // Rotate the snake's direction to the right
        if (game->direction == LEFT)
        {
            game->direction = UP;
        }
        else if (game->direction == RIGHT)
        {
            game->direction = DOWN;
        }
        else if (game->direction == UP)
        {
            game->direction = RIGHT;
        }
        else if (game->direction == DOWN)
        {
            game->direction = LEFT;
        }
    }
    
    // Move the snake forward in its current direction
    int newX = game->snake.body[0].x;
    int newY = game->snake.body[0].y;

    if (game->direction == LEFT && game->snake.body[0].x > 0)
    {
        newX--;
    }
    else if (game->direction == RIGHT && game->snake.body[0].x < WIDTH - 1)
    {
	newX++;
    }
    else if (game->direction == UP && game->snake.body[0].y > 0)
    {
	newY--;
    }
    else if (game->direction == DOWN && game->snake.body[0].y < HEIGHT - 1)
    {
	newY++;
    }
    
    // Update the snake's position
    for (int i = game->snake.length - 1; i > 0; i--)
    {
	game->snake.body[i] = game->snake.body[i - 1];
    }
    game->snake.body[0].x = newX;
    game->snake.body[0].y = newY;
	
    // Check if the snake has eaten the fruit
    if (game->snake.body[0].x == game->fruitX && game->snake.body[0].y == game->fruitY) 
    {
	// Increase the length of the snake
	if (game->snake.length < MAX_LENGTH)
	{
		game->snake.length++;
	}
	
        // Generate new fruit position
        do {
            game->fruitX = rand() % (WIDTH - 3) + 1;  // Generate X position within the border
            game->fruitY = rand() % (HEIGHT - 3) + 1; // Generate Y position within the border
        } while (game->fruitX == game->snake.body[0].x && game->fruitY == game->snake.body[0].y);
	
	
	// Increase the score
	game->score++;
    }
    
}

void drawGame(Game* game) 
{
    ssd1306_clear();
    
    ssd1306_DrawRect(0, 0, 128, 64);
    
    // Draw the snake
    for (int i = 0; i < game->snake.length; i++) {
        ssd1306_draw_pixel(game->snake.body[i].x, game->snake.body[i].y, 1);
    }
    
    // Draw the fruit
    ssd1306_draw_pixel(game->fruitX, game->fruitY, 1);
    
    // Check if the snake's head hits the border
    if (game->snake.body[0].x == 0 || game->snake.body[0].x == WIDTH - 1 ||
        game->snake.body[0].y == 0 || game->snake.body[0].y == HEIGHT - 1) 
    {
        game->gameOver = true;                       // Set game over flag
    }
    
    ssd1306_refresh();
    
}



void main() 
{
    uint8_t str1[50] = {0};
  
    I2C_Init(I2C_2, 500);
    DigitalWrite(PB0, LOW);
    DigitalWrite(PB1, HIGH);
    Delay_ms(100);
    ssd1306_init();

    srand(123);

    Game game;
    initGame(&game);

    while (!game.gameOver) {
        // Read
        // Read the switch inputs
        bool switchLeftPressed  = is_key_pressed(PF0);
        bool switchRightPressed = is_key_pressed(PF4);


        updateGame(&game, switchLeftPressed, switchRightPressed);
        drawGame(&game);
    }
    
    ssd1306_clear();
    ssd1306_DrawRect(0, 0, 128, 64);
    ssd1306_refresh();
    
    ssd1306_setcursor(1,16);
    ssd1306_Print_String("Game Over !!!");
    
    sprintf(str1,"Score : %d\r\n", game.score);
    ssd1306_setcursor(3,16);
    ssd1306_Print_String(str1);
}



void Delay_ms(unsigned int delay_value) {
    uint32_t i, j;
    for (i = 0; i < delay_value; i++) {
        for (j = 0; j < 3180; j++) {
            // Delay loop
        }
    }
}




/*****************************************************************/
unsigned char is_key_pressed(GPIO_PORT key)
{
    if(key == PF0)
        return (is_key_pressed_sw2());

    else if(key == PF4)
            return (is_key_pressed_sw1());

    else
        return 0;
}

/*****************************************************************/
unsigned char is_key_pressed_sw1()
{
    static uint8_t onec_pressed = 0;

    if((DigitalRead(PF4, PU) == 0) && (onec_pressed == 0))
    {
        onec_pressed = 1;
        return 1;
    }
    else if(DigitalRead(PF4, PU) == 1)
    {
        onec_pressed = 0;
        return 0;
    }
    else
        return 0;
}

/*****************************************************************/
unsigned char is_key_pressed_sw2()
{
    static uint8_t onec_pressed = 0;

    if((DigitalRead(PF0, PU) == 0) && (onec_pressed == 0))
    {
        onec_pressed = 1;
        return 1;
    }
    else if(DigitalRead(PF0, PU) == 1)
    {
        onec_pressed = 0;
        return 0;
    }
    else
        return 0;
}