#ifndef   _CAN_DRIVER_H_
#define   _CAN_DRIVER_H_

#include "Common_Datatype.h"

void CAN0_Driver();
void CAN0_Init();
static void CAN0_Transmit_Obj(const CAN0_MSG_Obj msg_obj_detail) ;
static void CAN0_Transmit_Data(const CAN0_MSG_Obj msg_obj_detail , uint8_t* MSG_data);


#endif
