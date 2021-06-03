#include "TM4C123GH6PM.h"
#include "ADC_Driver.h"
#include "Common_Macros.h"


volatile uint32_t  ADC_VALUE[MAX_ADC_IN] = {0};
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
ADC0->ACTSS  &=  ~(1<<0);      //ADC0 Sample sequencer 0 is disabled

/*
2. Configure the trigger event for the sample sequencer in the ADCEMUX register.
*/
ADC0->EMUX  &=   ~(0xF<<0);   //Processor triggered selected for Sample sequencer 0

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

ADC0->SSMUX0  =  (0x00765421);
/*
ADC0->SSMUX0  |=  (0x1<<0);		// AIN1 ie PE2 as 1st sample input
ADC0->SSMUX0  |=  (0X2<<4);		// AIN2 ie PE1 as 2nd sample input
ADC0->SSMUX0  |=  (0X4<<8);		// AIN4 ie PD3 as 3rd sample input
ADC0->SSMUX0  |=  (0X5<<12);		// AIN5 ie PD2 as 4th sample input
ADC0->SSMUX0  |=  (0X6<<16);		// AIN6 ie PD1 as 5th sample input
ADC0->SSMUX0  |=  (0X7<<20);		// AIN7 ie PD0 as 6th sample input
*/
/*
5. For each sample in the sample sequence, configure the sample control bits in the corresponding
nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
is set. Failure to set the END bit causes unpredictable behavior.
*/
ADC0->SSCTL0   =  0x600000;

/*
6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
*/


/*
7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
register.
*/
ADC0->ACTSS  |=  (1<<0);      //ADC0 Sample sequencer 0 is Enabled

ADC0->PC = 0x7;

ADC_Init_Flag = 1;

}


/*************************************************************************************************************************/

void ADC_0()
{
	if(ADC_Init_Flag == 0)
	{
		ADC_Init();
	}
	
	ADC0->PSSI |= (1<<0);             // ADC0 SAMPLE SEQUENCER 0 IS INITIATED
	
	while((ADC0->RIS & 0x1) == 0);    //WAIT UNTIL SAMPLE SEQUENCE IS COMPLETED;
        
        ADC0->ISC |= (1<<0); 			// CLEARING convertion clear flag
	

	ADC_VALUE[0] = ADC0->SSFIFO0;
	ADC_VALUE[1] = ADC0->SSFIFO0;
	ADC_VALUE[2] = ADC0->SSFIFO0;
	ADC_VALUE[3] = ADC0->SSFIFO0;
	ADC_VALUE[4] = ADC0->SSFIFO0;
	ADC_VALUE[5] = ADC0->SSFIFO0;
	
//	ADC0->ISC |= (1<<0); 			// CLEARING convertion clear flag
}

int analogRead(ADC_PORT port_num)
{
	return(ADC_VALUE[port_num]);
}
