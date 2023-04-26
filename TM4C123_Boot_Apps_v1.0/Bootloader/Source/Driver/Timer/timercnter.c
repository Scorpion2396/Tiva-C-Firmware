#include"timercnter.h"
#include "TM4C123GH6PM.h"

void init_Timer_Counter(void)
{
	SYSCTL->RCGCWTIMER |=  (1<<1);		// enable clock to timer 1 module
	WTIMER1->CTL       &= ~(1<<0);		// disable GPTM A
	WTIMER1->TAPR	   |=  15999  ;			// prescaler for 16000 is 16001, so that 16Mhz/16000 = 1ms
 //       WTIMER1->TAPMR	   |=  15999  ;			// prescaler for 16000 is 16001, so that 16Mhz/16000 = 1ms
	WTIMER1->CFG       |=  0x4;		// selects the 32-bit timer configuration.
	WTIMER1->TAMR      |=  (2<<0) ;      // GPTM Timer A  Periodic Timer mode
	WTIMER1->TAMR      &=  ~(1<<4) ;      // GPTM Timer A  Counts up
//	WTIMER1->TAMR      |=  (1<<4) ;      // GPTM Timer A  Counts up
	WTIMER1->TAILR     = 0xFFFFFFFF;     //Maximum value 
//        WTIMER1->TAMATCHR  = 0xFFFFFFFF;     //Maximum value 
        
}


/************************************************************ <Start Timer-A-0 > *************************************************************/
void Start_Timer_counter(void)
{
	WTIMER1->CTL      |= (1<<0);                         // Enable Timer A
}



/************************************************************ <Start Timer-A-0 > *************************************************************/
void Stop_Timer_counter(void)
{
	WTIMER1->CTL      &= ~(1<<0);                         // Disabling Timer A
        WTIMER1->TAV       = 0;
}


/************************************************************ <Start Timer-A-0 > *************************************************************/
void Pause_Timer_counter(void)
{
	WTIMER1->CTL      &= ~(1<<0);                         // Disabling Timer A
}


/************************************************************ <Refresh Timer-A-0 > *************************************************************/
void Refresh_Timer_counter(void)
{
	WTIMER1->CTL      &= ~(1<<0);                         // Disabling Timer A
        WTIMER1->TAV       = 0;                               //Reset timer data
	WTIMER1->CTL      |= (1<<0);                         // Enable Timer A
}

/************************************************************ <Refresh Timer-A-0 > *************************************************************/
unsigned int millis(void)
{
	unsigned int timer_value = 0U;
	
	timer_value = WTIMER1->TAV;
	
	return(~timer_value);
}
