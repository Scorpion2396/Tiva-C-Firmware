#include "TM4C123GH6PM.h"
#include "ADC_Driver.h"




static uint8_t  ADC_Init_Flag  = 0;


void ADC_Init()
{

/**********************************************************************************************************************************************
13.4.1 Module Initialization

Initialization of the ADC module is a simple process with very few steps: enabling the clock to the
ADC, disabling the analog isolation circuit associated with all inputs that are to be used, and
reconfiguring the sample sequencer priorities (if needed).
The initialization sequence for the ADC is as follows:
**********************************************************************************************************************************************/


/*
1. Enable the ADC clock using the RCGCADC register (see page 352).
*/
SYSCTL->RCGCADC   |= (1<<0);                // Enabling clock to ADC0

/*
2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
To find out which GPIO ports to enable, refer to “Signal Description” on page 801.
*/
SYSCTL->RCGCGPIO   = 0x3F;					// Enabling Clock to all GPIO Port

/*
3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
configure, see Table 23-4 on page 1344.
*/
/*
GPIOD->LOCK        = 0x4C4F434B;			// Unlocking Port D for register configaration
GPIOE->LOCK        = 0x4C4F434B;			// Unlocking Port E for register configaration

GPIOD->CR	      |= (1<<0);				// SETTING Commit Register for PORT D bit 0
GPIOD->CR	      |= (1<<1);				// SETTING Commit Register for PORT D bit 1
GPIOD->CR	      |= (1<<2);				// SETTING Commit Register for PORT D bit 2
GPIOD->CR	      |= (1<<3);				// SETTING Commit Register for PORT D bit 3

GPIOE->CR	      |= (1<<1);				// SETTING Commit Register for PORT E bit 1
GPIOE->CR	      |= (1<<2);				// SETTING Commit Register for PORT E bit 2
*/

GPIOD->AFSEL	  |= (1<<0);				// SETTING alternate function for PORT D bit 0
GPIOD->AFSEL	  |= (1<<1);				// SETTING alternate function for PORT D bit 1
GPIOD->AFSEL	  |= (1<<2);				// SETTING alternate function for PORT D bit 2
GPIOD->AFSEL	  |= (1<<3);				// SETTING alternate function for PORT D bit 3

GPIOE->AFSEL	  |= (1<<1);				// SETTING alternate function for PORT E bit 1
GPIOE->AFSEL	  |= (1<<2);				// SETTING alternate function for PORT E bit 2
//GPIOE->AFSEL	  |= (0x6);

/*
4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
GPIO Digital Enable (GPIODEN) register (see page 682).
*/
GPIOD->DEN	      &= ~(1<<0);				// Disabling  Digital funtionality for PORT D bit 0
GPIOD->DEN	      &= ~(1<<1);				// Disabling  Digital funtionality for PORT D bit 1
GPIOD->DEN	      &= ~(1<<2);				// Disabling  Digital funtionality for PORT D bit 2
GPIOD->DEN	      &= ~(1<<3);				// Disabling  Digital funtionality for PORT D bit 3

GPIOE->DEN	      &= ~(1<<1);				// Disabling  Digital funtionality for PORT E bit 1
GPIOE->DEN	      &= ~(1<<2);				// Disabling  Digital funtionality for PORT E bit 2

/*
5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
*/
GPIOD->AMSEL	  |= (1<<0);				// Disabling  the Analog isolation circuit for PORT D bit 0
GPIOD->AMSEL	  |= (1<<1);				// Disabling  the Analog isolation circuit for PORT D bit 1
GPIOD->AMSEL	  |= (1<<2);				// Disabling  the Analog isolation circuit for PORT D bit 2
GPIOD->AMSEL	  |= (1<<3);				// Disabling  the Analog isolation circuit for PORT D bit 3

GPIOE->AMSEL	  |= (1<<1);				// Disabling  the Analog isolation circuit for PORT E bit 1
GPIOE->AMSEL	  |= (1<<2);				// Disabling  the Analog isolation circuit for PORT E bit 2
//GPIOE->AMSEL	  |= (0x6);

ADC0->PC = 0x7;                                         // SAMPLE RATE 1 Mbps

ADC_Init_Flag = 1;
}


void ADC_SS_Init(int AINn)
{

/******************************************************************************************************************************
13.4.2 Sample Sequencer Configuration

Configuration of the sample sequencers is slightly more complex than the module initialization
because each sample sequencer is completely programmable.
The configuration for each sample sequencer should be as follows:
*******************************************************************************************************************************/

/*
1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
ADCACTSS register. Programming of the sample sequencers is allowed without having them
enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
event were to occur during the configuration process.
*/
ADC0->ACTSS  &=  ~(1<<3);      //ADC0 Sample sequencer 3 is disabled

/*
2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
*/
ADC0->EMUX  &=   ~(0xF<<12);   //Processor triggered selected for Sample sequencer 3

/*
3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
(ADCTSSEL) register to specify in which PWM module the generator is located. The default
register reset selects PWM module 0 for all generators.
*/
//    N/A

/*
4. For each sample in the sample sequence, configure the corresponding input source in the
ADCSSMUXn register.
*/

 	ADC0->SSMUX3  =  AINn;		     	// AIN ie   sample input PIN
			

/*
5. For each sample in the sample sequence, configure the sample control bits in the corresponding
nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
is set. Failure to set the END bit causes unpredictable behavior.
*/
ADC0->SSCTL3   =  0x6;

/*
6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
*/
//  N/A

/*
7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
register.
*/
ADC0->ACTSS  |=  (1<<3);      //ADC0 Sample sequencer 3 is Enabled

}


/*************************************************************************************************************************/


int analogRead(ADC_PORT port_num)
{
	volatile uint32_t  ADC_VALUE = 0;
	
	if(ADC_Init_Flag == 0)
	{
		ADC_Init();
	}
	
	ADC_SS_Init(port_num);
	
	ADC0->PSSI |= (1<<3);             // ADC0 SAMPLE SEQUENCER 3 IS INITIATED
	
	while((ADC0->RIS & 8) == 0);    //WAIT UNTIL SAMPLE SEQUENCE IS COMPLETED;
	
        ADC0->ISC |= (1<<3); 			// CLEARING convertion clear flag
        
	ADC_VALUE = ADC0->SSFIFO3;

	


	return(ADC_VALUE);
}
