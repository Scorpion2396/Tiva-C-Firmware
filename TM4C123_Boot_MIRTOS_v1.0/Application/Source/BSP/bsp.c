/* Board Support Package */
#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "mirtos.h"

/**************************************************************************/
__attribute__((naked)) void assert_failed (char const *file, int line)
{
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

/**************************************************************************/
void BSP_init()
{
    /* configuring systick irq time duration to be triggered */
    SysTick->LOAD = (SYS_CLOCK_HZ / BSP_TICK_PER_SEC) - 1U ;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0);
}




