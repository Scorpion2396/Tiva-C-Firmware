/******************************************************************************/

#include "mirtos.h"

/******************************************************************************/
OSThread * volatile OS_curr; /* pointer to the current thread */
OSThread * volatile OS_next; /* pointer to the next thread */

OSThread *OS_Thread[32 + 1]; /* array of threads  started so far */
volatile uint8_t OS_threadNum = 0;    /* Number of threads started so far */
volatile uint8_t OS_prevThread_Idx = 0;      /* previous thread index for round robin */
volatile uint8_t OS_currIdx = 0;      /* current thread index for round robin */
volatile uint8_t OS_currThread_Idx = 0;      /* current thread index for round robin */
uint32_t OS_readySet = 0;    /* bitmask of threads that are ready to run, each bits corresponds to a thread (upto 32 threads) */

uint32_t stack_idle[40];     /* idle thread stack */
OSThread idle_thread;        /* idle thread handler */


/******************************************************************************/

void OS_init(void)
{
    /* disable irq */
    __asm volatile ("cpsid i" : : : "memory");

    /* set the SysTick interrupt priority to highest i.e to 0x00 */
    *(uint32_t volatile*)0xE000ED20 &= ~(0xFFU << 16);     // NVIC_SetPriority(SysTick_IRQn, 0x00U);

   /* set PendSV interrupt priority to the lowest level i.e to 0xFF */
    *(uint32_t volatile*)0xE000ED20 |= (0xFFU << 16);      // NVIC_SetPriority(PendSV_IRQn, 0xFFU);


    OSThread_start(&idle_thread,
                     &OS_idle_thread,
                     stack_idle,
                     sizeof(stack_idle));
} 

/******************************************************************************/
void OSThread_start(
    OSThread *me,
    OSThreadHandler threadhandler,
    void *pvt_stack,
    uint32_t stack_size)
{
    uint32_t *sp = (uint32_t*)((((uint32_t)pvt_stack + stack_size) / 8) * 8);
    uint32_t *stack_limit;

    /* STACK FRAME  */
    *(--sp) = (1U << 24);               /* xPSR  set the Thumb state */
    *(--sp) = (uint32_t)threadhandler;  /*  PC  */
    *(--sp) = 0x0000000EU;              /*  LR  */
    *(--sp) = 0x0000000CU;              /* R12  */
    *(--sp) = 0x00000003U;              /*  R3  */
    *(--sp) = 0x00000002U;              /*  R2  */
    *(--sp) = 0x00000001U;              /*  R1  */
    *(--sp) = 0x00000000U;              /*  R0  */
    /* additional regs*/
    *(--sp) = 0x0000000BU;              /*  R11 */
    *(--sp) = 0x0000000AU;              /*  R10 */
    *(--sp) = 0x00000009U;              /*  R9  */
    *(--sp) = 0x00000008U;              /*  R8  */
    *(--sp) = 0x00000007U;              /*  R7  */
    *(--sp) = 0x00000006U;              /*  R6  */
    *(--sp) = 0x00000005U;              /*  R5  */
    *(--sp) = 0x00000004U;              /*  R4  */

    me->sp = sp;

    stack_limit = (uint32_t*)(((((uint32_t)pvt_stack - 1U) / 8) + 1U) * 8);

    for(sp = sp - 1 ; sp >= stack_limit ; sp--)
    {
        *sp = 0xDEADBEEFU;
    }

    /* check if num of thread is less then MAX allowed thread */
    if(OS_threadNum < MAX_THREAD)
    {
        /* register the thread with os */
        OS_Thread[OS_threadNum] = me;

        /* if the thread is non idle thread */
        if(OS_threadNum > 0U)
        {
            /* set the ready to run bit for that thread */
            OS_readySet |= (1U << (OS_threadNum - 1U));
        }

        /* increment the thread num */
        ++OS_threadNum;
    }
    else
    {
        OS_Error(); /* to include error handling later */
    }

}

/******************************************************************************/

void OS_run(void)
{

    /* disable irq */
    __asm volatile ("cpsid i" : : : "memory");

    OS_sched();

    OS_prevThread_Idx   =   OS_currIdx;
    OS_currThread_Idx   =   OS_currIdx;

    /* enable irq */
    __asm volatile ("cpsie i" : : : "memory");

    /* ERROR condition as program should never be here */
    OS_Error();
}


/******************************************************************************/

void OS_sched(void)
{
/*---------------------------------------*/
  //  static uint8_t test = 0;
  //  test ^= 1;
  //  DigitalWrite(PA2, test);
/*---------------------------------------*/

    /* check for idle condition of thread i.e ready to run or not */
    if(OS_readySet == 0U)
    {
        /* if none of the thread is ready then, run the idle thread at index 0 */
        OS_currIdx = 0U;
    }
    else
    {
        do
        {
            ++OS_currIdx;

            /* if current thread index is the last in round robin then */
            if(OS_currIdx == OS_threadNum)
            {
                /* change the current thread index to 1, not zero because 0 is the idle thread index   */
                /* and this thread will only gets called when all of the threads are in blocking state */
                OS_currIdx = 1U;
            }
        }while((OS_readySet & (1U << (OS_currIdx - 1U))) == 0U); /* checking for the threads whose ready to run bit is set */

    }

    OS_next = OS_Thread[OS_currIdx];


    /* if current thread is not equal to next thread the switch the thread by triggering the Pendsv handler*/
    if(OS_next != OS_curr)
    {
        /* trigger PendSV irq handler */
        *(uint32_t volatile *)0xE000ED04 |= (1U << 28); // 0xE000ED04 = (SCB->ICSR)
    }
}

/*****************************************************************************/


/******************************************************************************/

void SysTick_Handler(void)
{
    OS_tick();
    
    /* disable irq */
    __asm volatile ("cpsid i" : : : "memory");

    OS_prevThread_Idx   = OS_currIdx;

    OS_sched();

    OS_currThread_Idx   =   OS_currIdx;

    /* enable irq */
    __asm volatile ("cpsie i" : : : "memory");

}

/******************************************************************************/
__attribute__ ((naked, optimize("-fno-stack-protector")))
void PendSV_Handler(void)
{
__asm volatile (

    /* __disable_irq(); */
    "  CPSID         I                 \n"

    /* if (OS_curr != (OSThread *)0) { */
    "  LDR           r1,=OS_curr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  CBZ           r1,PendSV_restore \n"

    /*     push registers r4-r11 on the stack */
    "  PUSH          {r4-r11}          \n"

    /*     OS_curr->sp = sp; */
    "  LDR           r1,=OS_curr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  STR           sp,[r1,#0x00]     \n"
    /* } */

    "PendSV_restore:                   \n"
    /* sp = OS_next->sp; */
    "  LDR           r1,=OS_next       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           sp,[r1,#0x00]     \n"

    /* OS_curr = OS_next; */
    "  LDR           r1,=OS_next       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r2,=OS_curr       \n"
    "  STR           r1,[r2,#0x00]     \n"

    /* pop registers r4-r11 */
    "  POP           {r4-r11}          \n"

    /* __enable_irq(); */
    "  CPSIE         I                 \n"

    /* return to the next thread */
    "  BX            lr                \n"
    );
}

/****************************************************************/
void OS_Error(void)
{
    while(1)
    {
        UART_print("**************> ERROR !!! <****************\n\r");
    }
}

/******************************************************************/

void OS_idle_thread(void)
{
  while(1)
  {
      OS_onIdle();
  }
}

/********************************************************************************/
void OS_onIdle(void)
{
    UART_print(" In Idle Thread:\n\r");
    __asm volatile ("wfi"); /* wait for interrupt to wake up, going to low power mode */
}

/******************************************************************/

void OS_tick(void)
{
    uint8_t n;

    /* for loop starting from n =1 to avoid the idle thread, as idle thread is at index 0 */
    for(n = 1U ; n < OS_threadNum ; ++n)
    {
        if(OS_Thread[n]->timeout != 0U)
        {
            --(OS_Thread[n]->timeout);

            if(OS_Thread[n]->timeout == 0U)
            {
                OS_readySet |= (1U << (n-1));
            }
        }
    }
}

/******************************************************************/
void OS_delay(uint32_t ticks)
{
    /* disable irq */
    __asm volatile ("cpsid i" : : : "memory");

    /* check if OS_delay is not called from idle thread as idle thread should never go to the blocking state */
    if(OS_curr != OS_Thread[0])
    {
        /* stores the delay tick for the particular thread in it's thread handler timeout variable */
        OS_curr->timeout = ticks;

        /* make the thread not ready to run by clearing the bit for the particular thread in the OS_readySet variable*/
        OS_readySet &= ~(1U << ((OS_currIdx - 1U)));

        /* calling the scheduler to immediately switch the context to next ready thread */
        OS_sched();
    }
    else
    {
        OS_Error();
    }

    /* enable irq */
    __asm volatile ("cpsie i" : : : "memory");
}


/******************************************************************/
__inline void disable_irq(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}


/******************************************************************/
__inline void enable_irq(void)
{
    __asm volatile ("cpsie i" : : : "memory");
}











    
