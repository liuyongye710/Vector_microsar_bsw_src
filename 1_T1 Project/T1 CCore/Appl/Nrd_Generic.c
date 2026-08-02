/********************************************************************************
*
*  File name:   Nrd_Generic.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nrd_Generic.h"
#include "Com.h"

/*********************************************************************************
*   Local  Macros
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

/*********************************************************************************
*   Local Functions
*********************************************************************************/
void Nrd_CanBusOff_Notify(uint8 ub_Channel, uint8 ub_Status)
{
    Nrd_CanBusOff_Status[ub_Channel] = ub_Status;
}

uint8 Nrd_CanMsg_EN(uint8 ub_MsgType, uint8 ub_Channel, uint8 ub_MsgNum)
{
    uint8 En_Sts = 0;
    
    if(RX_MSG == ub_MsgType)
    {
        En_Sts = CheckSumPar_RX[ub_MsgNum].ub_Enable;
    }
    else if(TX_MSG == ub_MsgType)
    {
        En_Sts = CheckSumPar_TX[ub_MsgNum].ub_Enable;
    }
    else
    {

    }

    return En_Sts;
}

void Nrd_Set_TimeOut_Status(uint8 ub_Channel, uint8 ub_MsgNum, boolean b_Status)
{
    Rx_Msg_Status[ub_MsgNum].b_MsgTOError = b_Status;
}
boolean Nrd_Get_TimeOut_Status(uint8 ub_Channel, uint8 ub_MsgNum)
{
    return Rx_Msg_Status[ub_MsgNum].b_MsgTOError;
}

void Nrd_Set_RxDetected_Status(uint8 ub_Channel, uint8 ub_MsgNum, boolean b_Status)
{
    Rx_Msg_Status[ub_MsgNum].b_RxFlg = b_Status;
}
boolean Nrd_Get_RxDetected_Status(uint8 ub_Channel, uint8 ub_MsgNum)
{
    return Rx_Msg_Status[ub_MsgNum].b_RxFlg;
}

void Nrd_Set_ComTimeoutValue(uint8 ub_Channel, uint8 ub_MsgNum, uint16 uw_TOTime)
{
    Com_RxPduInfo[ub_MsgNum].sigMinimumTimeout = (uw_TOTime/COM_RX_TIMEBASE);
    Com_RxPduInfo[ub_MsgNum].sigMinimumFirstTimeout = (uw_TOTime/COM_RX_TIMEBASE);
//    Com_RxSignalInfo[Rx_ComTimeoutId[ub_MsgNum].uw_SignalId].rxTimeOut = (uw_TOTime/COM_RX_TIMEBASE);
//    Com_RxSignalInfo[Rx_ComTimeoutId[ub_MsgNum].uw_SignalId].acRxFirstTimeout = (uw_TOTime/COM_RX_TIMEBASE);
}

void Nrd_SetRxMsgID(uint8 ub_MsgNum, uint32 ul_MsgId)
{
    CheckSumPar_RX[ub_MsgNum].id = ul_MsgId;
}

void Nrd_SetTxMsgID(uint8 ub_MsgNum, uint32 ul_MsgId)
{
    CheckSumPar_TX[ub_MsgNum].id = ul_MsgId;
}

void Nrd_SetRxTimeoutCnt(uint8 ub_MsgNum, uint16 uw_TOTime)
{
    CheckSumPar_RX[ub_MsgNum].uw_TOCnt = uw_TOTime;
}

void Nrd_SetRxMsgEN(uint8 ub_MsgNum, uint8 ub_EN)
{
    CheckSumPar_RX[ub_MsgNum].ub_Enable = ub_EN;
}

void Nrd_SetTxMsgEN(uint8 ub_MsgNum, uint8 ub_EN)
{
    CheckSumPar_TX[ub_MsgNum].ub_Enable = ub_EN;
}

void Nrd_SetRxMsgCSA(uint8 ub_MsgNum, uint8 ub_CSA)
{
    CheckSumPar_RX[ub_MsgNum].CsAlg = ub_CSA;
}

void Nrd_SetTxMsgCSA(uint8 ub_MsgNum, uint8 ub_CSA)
{
    CheckSumPar_TX[ub_MsgNum].CsAlg = ub_CSA;
}
