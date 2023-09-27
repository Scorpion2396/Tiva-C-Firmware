#ifndef    COMMON_MACROS_H
#define    COMMON_MACROS_H

#include "TM4C123GH6PM.h"

//#include "Common_Macros.h"

/* system clock setting [Hz] */
#define SYS_CLOCK_HZ 16000000U

#define  Flag_20ms         (Timer_Flag.Timer_Flag_20ms)
#define  Flag_30ms         (Timer_Flag.Timer_Flag_30ms)
#define  Flag_50ms         (Timer_Flag.Timer_Flag_50ms)
#define  Flag_100ms        (Timer_Flag.Timer_Flag_100ms)
#define  Flag_200ms        (Timer_Flag.Timer_Flag_200ms)
#define  Flag_500ms        (Timer_Flag.Timer_Flag_500ms)
#define  Flag_1000ms       (Timer_Flag.Timer_Flag_1000ms)
#define  Flag_2000ms       (Timer_Flag.Timer_Flag_2000ms)

#define  SET               (uint8_t)1
#define  RESET             (uint8_t)0

#define mTotal_MSG_Obj      (uint8_t)5

#define MSG_DLC_0x010		(uint16_t)8
#define MSG_DLC_0x100		(uint16_t)5
#define MSG_DLC_0x200		(uint16_t)8
#define MSG_DLC_0x3C2		(uint16_t)7
#define MSG_DLC_0x500		(uint16_t)1

#define MSG_ObjNo_0x010		(uint8_t)1
#define MSG_ObjNo_0x100		(uint8_t)2
#define MSG_ObjNo_0x200		(uint8_t)3
#define MSG_ObjNo_0x3C2		(uint8_t)4
#define MSG_ObjNo_0x500		(uint8_t)5

#define MSG_ObjIndex_0x010		(uint8_t)0
#define MSG_ObjIndex_0x100		(uint8_t)1
#define MSG_ObjIndex_0x200		(uint8_t)2
#define MSG_ObjIndex_0x3C2		(uint8_t)3
#define MSG_ObjIndex_0x500		(uint8_t)4

/**********************************> MACRO FUNCTIONs <*************************************************/

#define get_port(val)      ((val)/(uint8_t)10)
#define get_pin(val)       ((val)%(uint8_t)10)

#define GETBYTE(value , byte_no)                           ((uint8_t*)&(value))[(uint8_t)(byte_no)]
#define PUTBYTE(value , byte_no , output_value)        (((uint8_t)&(value))[(byte_no)] = (output_value))

#define MAX(x,y)                ((x)>(y)?(x):(y))
#define MIN(x,y)                ((x)<(y)?(x):(y))
#define MAX_OF_THREE(x,y,z)     (MAX(MAX(x,y),MAX(y,z)))
#define MIN_OF_THREE(x,y,z)     (MIN(MIN(x,y),MIN(y,z)))
#define ABS(x,y)                (((x)<=(y)?(-x):(x)
#define DIFF(x,y)               (((x)>(y))?((x)-(y)):((y)-(x)))
#define SATURATION_OPT(x,y)     (((x)>=(y))? ((x)=(y)) : ((x)=(x)))
#define SATURATION(x,y,z)       (((x)>=(z))?((x)=(z)):(((x)<=(y))?((x)=(y)):((x)=(x))))

#endif
