
#include "TM4C123GH6PM.h"
#include "GPIO_Driver_Interface.h"
#include "Timer_Interface.h"
//#include "ADC_Driver_Interface.h"
#include "Common_Datatype.h"
#include "Common_Macros.h"
//#include "LCD_Interface.h"
//#include "I2C_Interface.h"
//#include "SPI_Interface.h"
//#include "MCP3208_Interface.h"
#include "CAN_Interface.h"


void main()
{

  while(1)
  {
   Timer_scheduler();

	CAN0_Driver();

  }
}
