#ifndef __MIRTOS_H__
#define __MIRTOS_H__

/******************************************************/
#define MAX_THREAD (32U + 1U)

/******************************************************/
/* Thread control block */
typedef struct
{
  void *sp;     /*stack pointer */
  /*......... other parameter later */
}OSThread;

typedef void (*OSThreadHandler)();
/*******************************************************/

void OS_init(void);
void OS_run(void);
void OS_onStartup(void);
void OS_sched(void);
void OS_Error(void);

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadhandler,
    void *pvt_stack,
    uint32_t stack_size);
                  
extern void PendSV_Handler(void);

#endif
