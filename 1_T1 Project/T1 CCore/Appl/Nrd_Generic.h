/********************************************************************************
*
*  File name:   Nrd_Generic.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nrd_Cfg.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
/*********************************************************************************
*   Global  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/

/*********************************************************************************
*   Global Functions
*********************************************************************************/
extern void  Nrd_CanBusOff_Notify(uint8 ub_Channel, uint8 ub_Status);
extern uint8 Nrd_CanMsg_EN(uint8 ub_MsgType, uint8 ub_Channel, uint8 ub_MsgNum);
extern void Nrd_Set_TimeOut_Status(uint8 ub_Channel, uint8 ub_MsgNum, boolean b_Status);
extern boolean Nrd_Get_TimeOut_Status(uint8 ub_Channel, uint8 ub_MsgNum);
extern void Nrd_Set_RxDetected_Status(uint8 ub_Channel, uint8 ub_MsgNum, boolean b_Status);
extern boolean Nrd_Get_RxDetected_Status(uint8 ub_Channel, uint8 ub_MsgNum);
extern void Nrd_Set_ComTimeoutValue(uint8 ub_Channel, uint8 ub_MsgNum, uint16 uw_TOTime);
extern void Nrd_SetRxMsgID(uint8 ub_MsgNum, uint32 ul_MsgId);
extern void Nrd_SetTxMsgID(uint8 ub_MsgNum, uint32 ul_MsgId);
extern void Nrd_SetRxTimeoutCnt(uint8 ub_MsgNum, uint16 uw_TOTime);
extern void Nrd_SetRxMsgEN(uint8 ub_MsgNum, uint8 ub_EN);
extern void Nrd_SetTxMsgEN(uint8 ub_MsgNum, uint8 ub_EN);
extern void Nrd_SetRxMsgCSA(uint8 ub_MsgNum, uint8 ub_CSA);
extern void Nrd_SetTxMsgCSA(uint8 ub_MsgNum, uint8 ub_CSA);
