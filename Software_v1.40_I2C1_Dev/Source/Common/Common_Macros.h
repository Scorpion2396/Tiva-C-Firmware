#ifndef    COMMON_MACROS_H
#define    COMMON_MACROS_H

#include "TM4C123GH6PM.h"

//#include "Common_Macros.h"

#define  Flag_20ms         (Timer_Flag.Timer_Flag_20ms)
#define  Flag_30ms         (Timer_Flag.Timer_Flag_30ms)
#define  Flag_50ms         (Timer_Flag.Timer_Flag_50ms)
#define  Flag_100ms        (Timer_Flag.Timer_Flag_100ms)
#define  Flag_200ms        (Timer_Flag.Timer_Flag_200ms)
#define  Flag_500ms        (Timer_Flag.Timer_Flag_500ms)
#define  Flag_1000ms       (Timer_Flag.Timer_Flag_1000ms)
#define  Flag_2000ms       (Timer_Flag.Timer_Flag_2000ms)

#define  SET     (uint8_t)1
#define  RESET   (uint8_t)0

#define get_port(val)      ((val)/(uint8_t)10)
#define get_pin(val)       ((val)%(uint8_t)10)

#endif
