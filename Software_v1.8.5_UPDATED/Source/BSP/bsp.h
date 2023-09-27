#ifndef __BSP_H__
#define __BSP_H__

/* Board Support Package for the EK-TM4C123GXL board */

extern __attribute__((naked)) void assert_failed (char const *file, int line);

#endif // __BSP_H__