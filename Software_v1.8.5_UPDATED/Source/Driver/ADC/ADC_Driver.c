#include "TM4C123GH6PM.h"
#include "ADC_Driver.h"
#include "Common_Macros.h"
#include "Common_Const.h"


static uint8_t  ADC_port_Flag[12] = {0};
static uint8_t  ADC_Init_Flag  = 0;


void ADC_Init(void)
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
    
    ADC0->PC = 0x7;                                         // SAMPLE RATE 1 Mbps
    
    ADC_Init_Flag = 1;
    
    /*
    3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
    configure, see Table 23-4 on page 1344.
    */
}

void ADC_port_Init(uint8_t port_num ,  uint8_t pin_num , uint8_t ch_num)
{

    PORT[port_num]->AFSEL	  |= (1<<pin_num);				// SETTING alternate function
    
    
    /*
    4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    GPIO Digital Enable (GPIODEN) register (see page 682).
    */
    PORT[port_num]->DEN	      &= ~(1<<pin_num);				// Disabling  Digital funtionality
    
    
    /*
    5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
    */
    PORT[port_num]->AMSEL	  |= (1<<pin_num);				// Disabling  the Analog isolation circuit for PORT D bit 0
    
    ADC_port_Flag[ch_num] = (uint8_t)1;
    
}


static void ADC_SS_Init(int AINn)
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


uint32_t analogRead(GPIO_PORT port)
{
	uint8_t port_num =  get_port(port);
	uint8_t pin_num  =  get_pin(port);
	uint8_t adc_ch   =  (uint8_t)0;
	
	switch(port)
	{
            case PE3: 	adc_ch = 0 ;   break;
            case PE2: 	adc_ch = 1 ;   break;
            case PE1: 	adc_ch = 2 ;   break;
            case PE0: 	adc_ch = 3 ;   break;
            case PD3: 	adc_ch = 4 ;   break;
            case PD2: 	adc_ch = 5 ;   break;
            case PD1: 	adc_ch = 6 ;   break;
            case PD0: 	adc_ch = 7 ;   break;
            case PE5: 	adc_ch = 8 ;   break;
            case PE4: 	adc_ch = 9 ;   break;
            case PB4: 	adc_ch = 10;   break;
            case PB5: 	adc_ch = 11;   break;
            default :	           ;   break;
	}
	
	volatile uint32_t  ADC_VALUE = 0;
	
	if(ADC_Init_Flag == 0)
	{
		ADC_Init();
	}
	
	else
	{
		;
	}
	
	if(ADC_port_Flag[adc_ch] == 0)
	{
		ADC_port_Init(port_num ,  pin_num , adc_ch);
	}
	
	else
	{
		;
	}
	
	ADC_SS_Init(adc_ch);
	
	ADC0->PSSI |= (1<<3);             // ADC0 SAMPLE SEQUENCER 3 IS INITIATED
	
	while((ADC0->RIS & 8) == 0);    //WAIT UNTIL SAMPLE SEQUENCE IS COMPLETED;
	
        ADC0->ISC |= (1<<3); 			// CLEARING convertion clear flag
        
	ADC_VALUE = ADC0->SSFIFO3;

	return(ADC_VALUE);
}
