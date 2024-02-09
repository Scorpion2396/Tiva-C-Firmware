/*
 * mirtos.mutex.c
 *
 *  Created on: 08-Feb-2024
 *      Author: Saksham Raj
 */
/*******************************************************/
#include "mirtos.h"

/*******************************************************/
volatile uint8_t task_expire_flag = 0;

/*******************************************************/
__inline void mutex_lock(volatile uint8_t *val)
{
    disable_irq();

    if(task_expire_flag == 1)
    {
        task_expire_flag = 0;

        *val = 0;

        OS_sched();

        enable_irq();
    }

    while(*val == 1)
    {
        OS_sched();

        enable_irq();
    }

    *val = 1;

    enable_irq();
}


/*******************************************************/
__inline void mutex_unlock(volatile uint8_t *val)
{
    disable_irq();

    if(OS_currThread_Idx != OS_prevThread_Idx)
    {
        task_expire_flag = 1;

        OS_prevThread_Idx = OS_currThread_Idx;
    }

    *val = 0;

    enable_irq();
}

/*******************************************************/

