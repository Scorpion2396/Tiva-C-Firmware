#ifndef __MIRTOS_H__
#define __MIRTOS_H__

/******************************************************/
#define MAX_THREAD (32U + 1U)

/******************************************************/
/* Thread control block */
typedef struct
{
  void *sp;         /*stack pointer */
  uint32_t timeout  /* time out delay down counter */
  /*......... other parameter later */
}OSThread;

typedef void (*OSThreadHandler)();

/*******************************************************/

void OS_init(void);
void OS_run(void);
void OS_onStartup(void);
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

#endif
