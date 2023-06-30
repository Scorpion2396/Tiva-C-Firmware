/* Board Support Package */
#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "mirtos.h"

/**************************************************************************/
static uint32_t volatile l_tickCtr;

/**************************************************************************/
__attribute__((naked)) void assert_failed (char const *file, int line)
{
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

/**************************************************************************/
void BSP_init()
{
    ;
}

/**************************************************************************/

void SysTick_Handler(void)
{
    ++l_tickCtr;
    
    /* disable irq */
    __ASM volatile ("cpsid i" : : : "memory");
    
    OS_sched();
    

    /* enable irq */
    __ASM volatile ("cpsie i" : : : "memory");
    
}

/*******************************************************************************/
static uint32_t BSP_tickCtr(void)
{
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

/*******************************************************************************/
void BSP_delay(uint32_t ticks)
{
    uint32_t start = BSP_tickCtr();

    while((BSP_tickCtr() - start) < ticks)
    {
        ;
    }
}

/*******************************************************************************/
void OS_onStartup(void)
{
    /* configuring systick irq time duration to be triggered */
    SysTick->LOAD = (SYS_CLOCK_HZ / 1000U) - 1U ;
    SysTick->LOAD = (SYS_CLOCK_HZ / 2U) - 1U ;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0);

    /* set the SysTick interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, 0U);

}


