#ifndef __MIRTOS_H__
#define __MIRTOS_H__
/******************************************************/
#include <stdint.h>
//#include "GPIO_Driver_Interface.h"
#include "UART_Interface.h"

/******************************************************/
#define MAX_THREAD (32U + 1U)

void enable_irq(void);
void disable_irq(void);

/******************************************************/
/* Thread control block */
typedef struct
{
  void *sp;                                 /*stack pointer */
  uint32_t timeout;                         /* time out delay down counter */
  /*......... other parameter later */
}OSThread;

typedef void (*OSThreadHandler)();


/*******************************************************/
extern OSThread * volatile OS_curr;         /* pointer to the current thread */
extern OSThread * volatile OS_next;         /* pointer to the next thread */

extern OSThread *OS_Thread[32 + 1];         /* array of threads  started so far */
extern volatile uint8_t OS_threadNum;       /* Number of threads started so far */
extern volatile uint8_t OS_prevThread_Idx;         /* previous thread index for round robin */
extern volatile uint8_t OS_currIdx;         /* current thread index for round robin */
extern volatile uint8_t OS_currThread_Idx;  /* current thread index for round robin */
extern uint32_t OS_readySet;                /* bitmask of threads that are ready to run, each bits corresponds to a thread (upto 32 threads) */

extern uint32_t stack_idle[40];             /* idle thread stack */
extern OSThread idle_thread;                /* idle thread handler */
/*******************************************************/


void OS_init(void);
void OS_run(void);
void OS_sched(void);
void OS_Error(void);
void OS_idle_thread(void);
void OS_onIdle(void);
void OS_delay(uint32_t ticks);
void OS_tick(void);


void OSThread_start(
    OSThread *me,
    OSThreadHandler threadhandler,
    void *pvt_stack,
    uint32_t stack_size);
                  
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);


void mutex_lock(volatile uint8_t *val);
void mutex_unlock(volatile uint8_t *val);

#endif
