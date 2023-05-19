/******************************************************************************/
#include "main.h"
/******************************************************************************/


void main()
{

    uint8_t err = 1;
    uint8_t sel_opt = 1;
    uint8_t cur_sel = 0;
    uint8_t ok_det  = 0;

    DigitalWrite(PB0,LOW );
    DigitalWrite(PB1, HIGH);
    Delay_ms(100);

    I2C_Init(I2C_2, 500);
    UART_init(UART_0, 115200);
    ssd1306_init();


    ssd1306_clear_row(7);
    ssd1306_setcursor(7,0);
    ssd1306_Print_String("Running Bootloader");

    ssd1306_clear_row(0);
    ssd1306_setcursor(0,8);
    ssd1306_Print_String("Continue to App");
    ssd1306_clear_row(1);
    ssd1306_setcursor(1,8);
    ssd1306_Print_String("Flash New App");
    ssd1306_setcursor(cur_sel,0);
    ssd1306_Print_String(">");

    while( sel_opt )
    {
        if(is_key_pressed(PF0))
        {
            cur_sel ^= 1;
            ssd1306_setcursor(cur_sel,0);
            ssd1306_Print_String(">");
            ssd1306_setcursor(!cur_sel,0);
            ssd1306_Print_String(" ");

        }

        if(is_key_pressed(PF4))
        {
            ok_det = 1;
        }

        if((cur_sel == 1) && (ok_det))
        {
            err = downloadNflashApps();

            if(err == 0)
            {
                ssd1306_clear_row(7);
                ssd1306_setcursor(7,0);
                ssd1306_Print_String("Error Loading Apps");
            }

            sel_opt = 0;

        }

        else if((cur_sel == 0) && (ok_det))
        {
            sel_opt = 0;
        }

        else
        {
            ; //nop
        }
    }

    ssd1306_clear();
    ssd1306_refresh();




    fun_ptr  jump_to_apps = (void(*)(void)) (*((unsigned int*)(APPS_RESET_HANDLER_ADDR)));
    unsigned int apps_stack_ptr = APPS_STACK_PTR_ADDR;

    if(verify_apps())
    {
        DigitalWrite(PF2, HIGH);
        Delay_ms(1000);
        DigitalWrite(PF2, LOW);
        ssd1306_clear_row(7);
        ssd1306_setcursor(7,0);
        ssd1306_Print_String("Going to Apps");
        Delay_ms(500);


        __set_MSP(apps_stack_ptr);
        jump_to_apps();
    }
    else
    {
        ssd1306_clear_row(7);
        ssd1306_setcursor(7,0);
        ssd1306_Print_String("Apps not present");
        while(1)
            DigitalWrite(PF1,HIGH);
    }
}

/**************************************************************************************/
void Delay_ms(unsigned int delay_value)
{
    uint32_t i = 0;
    uint32_t j = 0;
    for(i=0 ; i<delay_value ; i++)
    {
        for(j=0 ; j < 3180 ; j++);
    }
}

/**************************************************************************************/
unsigned char verify_apps(void)
{
    if((*((unsigned int*)(APPS_RESET_HANDLER_ADDR))) != APPS_INVALID)
    {
        return 1;
    }
    else
    {
        return 0;
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


