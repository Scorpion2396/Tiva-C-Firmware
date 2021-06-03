/*******************************************************************************************************************************************
11.4.1 One-Shot/Periodic Timer Mode
The GPTM is configured for One-Shot and Periodic modes by the following sequence:

1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
any changes.

2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.

3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
a. Write a value of 0x1 for One-Shot mode.
b. Write a value of 0x2 for Periodic mode.

4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
to select whether to capture the value of the free-running timer at time-out, use an external
trigger to start counting, configure an additional trigger or interrupt, and count up or down.

5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).

6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
(GPTMIMR).

7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.

8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
Register (GPTMICR)

*********************************************************************************************************************************************/


#include "TM4C123GH6PM.h"
#include "Timer.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"


Timer_Flag_Stucture    Timer_Flag = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

static uint8_t Timer0_Init_flag  = (uint8_t)0;

/********************************************************* <Timer-A-0 initialization> *********************************************************/
void Timer_Init()
{
	SYSCTL->RCGCTIMER |=  (1<<0);                         // enable clock gating to Timer 0
	TIMER0->CTL       &= ~(1<<0);                         // Disabling Timer A
	TIMER0->CFG       &= ~((1<<0)|(1<<1)|(1<<2));         // for a 16/32-bit timer, this value selects the 32-bit timer configuration.
	TIMER0->TAMR      |=  (0x2<<0) ;                      // GPTM Timer A  Periodic Timer mode
	TIMER0->TAMR      &=  ~(1<<4) ;                       // GPTM Timer A  Counts down
	TIMER0->TAILR     = 0x27100;                          // 0x27100 = 160000 for 10ms interval, since clockspeed is 16MHz = 16000000 for 1 sec

        Timer0_Init_flag  = (uint8_t)1;

}



/************************************************************ <Start Timer-A-0 > *************************************************************/
static void Start_Timer_0()
{
	TIMER0->CTL      |= (1<<0);                         // Enable Timer A
}



/************************************************************ <Start Timer-A-0 > *************************************************************/
void Stop_Timer_0()
{
	TIMER0->CTL      &= ~(1<<0);                         // Disabling Timer A
}



/************************************************************ <Refresh Timer-A-0 > *************************************************************/
void Refresh_Timer_0()
{
	TIMER0->CTL      &= ~(1<<0);                         // Disabling Timer A
	TIMER0->CTL      |= (1<<0);                         // Enable Timer A
}

/*************************************** <Timer Function which updates timer Flags> ********************************************/

static uint16_t Count_20ms   = 0;
static uint16_t Count_30ms   = 0;
static uint16_t Count_50ms   = 0;
static uint16_t Count_100ms  = 0;
static uint16_t Count_200ms  = 0;
static uint16_t Count_500ms  = 0;
static uint16_t Count_1000ms = 0;
static uint16_t Count_2000ms = 0;


void Timer_0()
{
	if(Timer0_Init_flag == 0)
	{
    	Timer_Init();
	}
  
	Clear_Timer_Flag();
    Start_Timer_0();
	
	if( TIMER0->RIS &0X00000001 == 1 )
	{
		TIMER0->ICR |= (1<<0);
		
		
		if(Count_20ms == (uint16_t)1)
		{
			Flag_20ms  = (uint8_t)1;
			Count_20ms = (uint16_t)0;
		}
		else
		{
			Count_20ms++;
		}

		
		
		if(Count_30ms == (uint16_t)2)
		{
			Flag_30ms  = (uint8_t)1;
			Count_30ms = (uint16_t)0;
		}
		else
		{
			Count_30ms++;
		}
		
		
		if(Count_50ms == (uint16_t)4)
		{
			Flag_50ms  = (uint8_t)1;
			Count_50ms = (uint16_t)0;
		}
		else
		{
			Count_50ms++;
		}
		
		
		if(Count_100ms == (uint16_t)9)
		{
			Flag_100ms  = (uint8_t)1;
			Count_100ms = (uint16_t)0;
		}
		else
		{
			Count_100ms++;
		}
		
		
		if(Count_200ms == (uint16_t)19)
		{
			Flag_200ms  = (uint8_t)1;
			Count_200ms = (uint16_t)0;
		}
		else
		{
			Count_200ms++;
		}
		
		
		if(Count_500ms == (uint16_t)49)
		{
			Flag_500ms  = (uint8_t)1;
			Count_500ms = (uint16_t)0;
		}
		else
		{
			Count_500ms++;
		}
		
		
		if(Count_1000ms == (uint16_t)99)
		{
			Flag_1000ms  = (uint8_t)1;
			Count_1000ms = (uint16_t)0;
		}
		else
		{
			Count_1000ms++;
		}
		
		
		if(Count_2000ms == (uint16_t)199)
		{
			Flag_2000ms  = (uint8_t)1;
			Count_2000ms = (uint16_t)0;
		}
		else
		{
			Count_2000ms++;
		}
		
	}
}

/*******************************************************< Reset all the timer flags> **************************************/
static void Clear_Timer_Flag()
{
	Flag_20ms    =  (uint8_t)0;
	Flag_30ms    =  (uint8_t)0;
	Flag_50ms    =  (uint8_t)0;
	Flag_100ms   =  (uint8_t)0;
	Flag_200ms   =  (uint8_t)0;
	Flag_500ms   =  (uint8_t)0;
	Flag_1000ms  =  (uint8_t)0;
	Flag_2000ms  =  (uint8_t)0;
}
