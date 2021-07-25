#ifndef     TIMER_INTERFACE_H
#define     TIMER_INTERFACE_H

#include "Common_Datatype.h"

extern Timer_Flag_Stucture    Timer_Flag;

extern void Timer_Init();
extern void Stop_Timer_0();
extern void Refresh_Timer_0();
extern void Timer_scheduler();

#endif
