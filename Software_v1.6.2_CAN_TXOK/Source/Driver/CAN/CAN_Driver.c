#include "TM4C123GH6PM.h"
#include "CAN_Driver.h"
#include "Common_Macros.h"
#include "Common_Datatype.h"
#include "Timer_Interface.h"

/***********************************************************************************************************************/
uint8_t CAN_Data_0x010[MSG_DLC_0x010] = {0x11 , 0x22 , 0x33 , 0x44 , 0x55 , 0x66 , 0x77 , 0x88};
uint8_t CAN_Data_0x100[MSG_DLC_0x100] = {0x11 , 0x22 , 0x33 , 0x44 , 0x55 };
uint8_t CAN_Data_0x200[MSG_DLC_0x200] = {0x11 , 0x22 , 0x33 , 0x44 , 0x55 , 0x66 , 0x77 , 0x88};
uint8_t CAN_Data_0x3C2[MSG_DLC_0x3C2] = {0x11 , 0x22 , 0x33 , 0x44 , 0x55 , 0x66 , 0x77 };
uint8_t CAN_Data_0x500[MSG_DLC_0x500] = {0xAA};

static uint8_t CAN0_Init_Flag = RESET;

const CAN0_MSG_Obj MSG_Obj[mTotal_MSG_Obj] = {{0x010 , MSG_DLC_0x010 , MSG_ObjNo_0x010},
											  {0x100 , MSG_DLC_0x100 , MSG_ObjNo_0x100},
										   	  {0x200 , MSG_DLC_0x200 , MSG_ObjNo_0x200},
											  {0x3C2 , MSG_DLC_0x3C2 , MSG_ObjNo_0x3C2},
											  {0x500 , MSG_DLC_0x500 , MSG_ObjNo_0x500}};



/***********************************************************************************************************************/

void CAN0_Driver()
{
	uint8_t msg_obj_count = 0;
	
	
	if(CAN0_Init_Flag == (uint8_t)0)
	{
		CAN0_Init();
		
		for(msg_obj_count = 0 ; msg_obj_count < mTotal_MSG_Obj ; msg_obj_count++)
		{
			CAN0_Transmit_Obj(MSG_Obj[msg_obj_count]);
		}
		
		CAN0_Init_Flag = SET;	
	}
	
	if(Flag_100ms == 1)
	{
		CAN0_Transmit_Data(MSG_Obj[MSG_ObjIndex_0x010] , CAN_Data_0x010);
		
		CAN0_Transmit_Data(MSG_Obj[MSG_ObjIndex_0x500] , CAN_Data_0x500);		
	}
	
	if(Flag_1000ms == 1)
	{
		CAN0_Transmit_Data(MSG_Obj[MSG_ObjIndex_0x100] , CAN_Data_0x100);
		
		CAN0_Transmit_Data(MSG_Obj[MSG_ObjIndex_0x200] , CAN_Data_0x200);		
	}
	
	if(Flag_2000ms == 1)
	{
		CAN0_Transmit_Data(MSG_Obj[MSG_ObjIndex_0x3C2] , CAN_Data_0x3C2);		
	}
	
	else
	{
		;
	}
		
	
}

/***********************************************************************************************************************/

//This function intialises the CAN Bus on Port B
void CAN0_Init()
{
    {
        //Port E CAN // PBE = TX and PBE = RX
        //Here the Port E is prepared for CAN operation
        
        volatile unsigned long delay;
        SYSCTL->RCGC0  |=  (1<<24);                     // Enable Clock for CAN0 Module
        SYSCTL->RCGC2  |=  (1<<4);                  	// Port B clock gating control
        
        //delay = SYSCTL_RCGC2_R;         			    // delay
        
        GPIOE->CR      |=   ((1<<4) | (1<<5));          // allow changes to PE4-5 //Commit Register
        GPIOE->AMSEL   &=  ~((1<<4) | (1<<5));          // disable analog function
        GPIOE->DEN     |=   ((1<<4) | (1<<5));          // Enable Digital Pins
        GPIOE->DIR     |=    (1<<4);            	    // Direction Output for PE5 and Input for PE4
        GPIOE->AFSEL   |=   ((1<<4) | (1<<5));   		// CAN0 alternate function on PE4-5
        GPIOE->PCTL    |=   ((8<<16) | (8<<20));        ///CONIGURING PORT E PIN 4 AND PIN 5 AS CAN0

    }
 
    //Initialise CAN0 Module
    {
        //Place CAN0 in Init Mode
        CAN0->CTL   |=   0x01; //Set Init Bit in the Register
        while(CAN0->IF1CRQ & 0x00008000); //wait while CAN0 Module is BUSY
    }
 
    //Enabling Loopback test mode
    CAN0->CTL  |=  0x81;			
    CAN0->TST  |=  0x10;					//loop back mode enable
  
    //Bit rate setting
    {
        CAN0->CTL |= 0x40; //Setting the CCE bit to edit CANBIT Register
        CAN0->BIT |= 0x0203; //Setting calculated according to example 1 in datasheet, 16Mhz and 1Mbps = 0x0203
        //But it gave a 500Kbps bit rate soo by trial and error 1Mbps = 0x0201
    }
 
    //No interrupts are used
    //CAN is enabled (Init = 0)
    CAN0->CTL &= ~0x41;
}

/***********************************************************************************************************************/

//Initialise the transmit message object
static void CAN0_Transmit_Obj(const CAN0_MSG_Obj msg_obj_detail) 						//objNo is the Object Number
{
	
	uint16_t Temp_MSG_ID   = (0x7FF & (msg_obj_detail.MSG_ID));
	uint8_t  Temp_MSG_DLC  = (0xF   & (msg_obj_detail.MSG_DLC));
	uint8_t  Temp_ObjNo	   = (0x3F  & (msg_obj_detail.MSG_ObjNo));
	
    int CmdMaskReg = 0;
    int ArbReg0    = 0;                             
    int ArbReg1    = 0;
    int MsgCtrl    = 0;
    int MaskReg0   = 0;
    int MaskReg1   = 0;
 
    while(CAN0->IF1CRQ & 0x00008000);					//wait while CAN0 Module is BUSY
 
    CmdMaskReg  |= 0x93; 								//WRNRD, CONTROL, DATAA, DATAB bits set
    CmdMaskReg  |= 0x20; 								//ARB bit set in CMSK reg
	    
    ArbReg1     |= (1 << 13); 								// DIR bit setting in ARB2 reg
    ArbReg1     |= (Temp_MSG_ID << 2); 						// MSG ID set in ARB2 reg
    ArbReg1     |= (1 << 15); 								//MSG Valid bit set in ARB2 reg 
	   
    //MsgCtrl     |= 0x100; 								//TXRQST bit set (Not Necessary to do this) 
    
    if(Temp_ObjNo == mTotal_MSG_Obj)
    {
    	MsgCtrl     |= (1 << 7); 								// SET this BIT if this is the LAST MSG OBJECT   
	}
	else
	{
		MsgCtrl     &= ~(1 << 7); 								// RESET this BIT if this is NOT the LAST MSG OBJECT   
	}
    
    MsgCtrl     |= Temp_MSG_DLC; 								// DATA LENGTH IS SPECIFIED HERE

    //CAN0->IF1DA1 = 0x0000;								//Actual Data to be sent &quot;START&quot; (Not required here, can be ignored)
    //CAN0->IF1DA2 = 0x0000; 								//This is the first message sent.
    //CAN0->IF1DB1 = 0x0000;
    //CAN0->IF1DB2 = 0x0000;
 
    CAN0->IF1CMSK = CmdMaskReg; 						//Registers updation
    CAN0->IF1MSK1 = MaskReg0;
    CAN0->IF1MSK2 = MaskReg1;
    CAN0->IF1ARB1 = ArbReg0;
    CAN0->IF1ARB2 = ArbReg1;
    CAN0->IF1MCTL = MsgCtrl;
 
    CAN0->IF1CRQ = Temp_ObjNo; 								//Message object number
}

/***********************************************************************************************************************/


//This function actually sends the data on the TX pin.
//Since registers have already been initialised in the CAN0_Transmit_Set function
static void CAN0_Transmit_Data(const CAN0_MSG_Obj msg_obj_detail , uint8_t* MSG_data)
{
	uint8_t Temp_MSG_DATA[8] = {(uint8_t)0};
	uint8_t MSG_len_Count     = (uint8_t)0;
	
	uint8_t  Temp_MSG_DLC  = (0xF    & (msg_obj_detail.MSG_DLC));
	uint8_t  Temp_ObjNo	   = (0x3F   & (msg_obj_detail.MSG_ObjNo));
	
	for(MSG_len_Count = 0 ; MSG_len_Count < Temp_MSG_DLC ; MSG_len_Count++)
	{
		Temp_MSG_DATA[MSG_len_Count] = MSG_data[MSG_len_Count];
	}

    CAN0->IF1CMSK &= ~0x30; 							//Clear ARB and CONTROL bits in CMSK reg
    CAN0->IF1CMSK |= 0x83; 								//Set WRNRD, DATAA, DATAB bits in CMSK
 
    CAN0->IF1DA1 = ((Temp_MSG_DATA[1]<<8) + Temp_MSG_DATA[0]); 				//Actual Data
    CAN0->IF1DA2 = ((Temp_MSG_DATA[3]<<8) + Temp_MSG_DATA[2]);
    CAN0->IF1DB1 = ((Temp_MSG_DATA[5]<<8) + Temp_MSG_DATA[4]);
    CAN0->IF1DB2 = ((Temp_MSG_DATA[7]<<8) + Temp_MSG_DATA[6]);
 
    CAN0->IF1CMSK |= 0x87; 								//Set the NEWDAT and TXRQST bit in CMSK reg
 
    CAN0->IF1CRQ = Temp_ObjNo; 								//Message object number
    
    while(CAN0->IF1CRQ & 0x00008000); 					//Wait for BUSY bit to clear
 
} 
 

/***********************************************************************************************************************/

