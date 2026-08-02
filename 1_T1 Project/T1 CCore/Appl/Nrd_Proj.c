/********************************************************************************
*
*  File name:   Nrd_Proj.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nrd_Proj.h"
#include "Nrd_Cfg.h"
#include "Com_Appl.h"

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
uint8 Nrd_ub_GetBusOffStatus(uint8 ub_Chn)
{
    return Nrd_CanBusOff_Status[ub_Chn];
}

boolean Nrd_b_IsMsgRxTimeOut(uint8 ub_Channel, uint8 ub_MsgNum)
{
    boolean ret = FALSE;

    if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
    {
        ret = Nrd_Get_TimeOut_Status(ub_Channel, ub_MsgNum);
    }

    return ret;
}

boolean Nrd_b_IsMsgRxLiveCounterFailure(uint8 ub_Channel, uint8 ub_MsgNum)
{
    return TRUE;
}

boolean Nrd_b_IsMsgRxCheckSumFailure(uint8 ub_Channel, uint8 ub_MsgNum)
{
    return TRUE;
}

boolean Nrd_b_IsMsgRxDetected(uint8 ub_Channel, uint8 ub_MsgNum)
{
    boolean ret = FALSE;

    if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
    {
        ret = Nrd_Get_RxDetected_Status(ub_Channel, ub_MsgNum);

        if(ret == TRUE)
        {
            Nrd_Set_RxDetected_Status(ub_Channel, ub_MsgNum, FALSE);
        }
    }
    
    return ret;
}

boolean Nrd_b_RxMsgDetected(uint8 ub_Channel, uint8 ub_MsgNum, const uint8* SduPtr)
{
    boolean ret = FALSE;

    if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
    {
        ret = Com_ReadRxMessage(ub_MsgNum, SduPtr);
    }

    return ret;
}

boolean Nrd_b_TxMsgHandler(uint8 ub_Channel, uint8 ub_MsgNum, const uint8* SduPtr)
{
    boolean ret = FALSE;

    if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_TX_MSG_NUM) && (Nrd_CanMsg_EN(TX_MSG, ub_Channel, ub_MsgNum)))
    {
        ret = Com_WriteTxMessage(ub_MsgNum, SduPtr);
    }

    return ret;
}

boolean Nrd_b_GetKeyStatus(boolean* b_SystemKey)
{
    return TRUE;
}

uint32 Nrd_ul_GetPowerVltg(void)
{
    return 0;
}

void Nrd_v_SetRxMsgTOTime(uint8 ub_Channel, uint8 ub_MsgNum, uint16 uw_TOTime)
{
    if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
    {
        Nrd_SetRxTimeoutCnt(ub_MsgNum, uw_TOTime*10);
        Nrd_Set_ComTimeoutValue(ub_Channel, ub_MsgNum, uw_TOTime*10);
    }
}

void Nrd_v_SetMsgID (uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint32 ul_MsgId)
{
    if(ub_Channel < NRD_CHN_NUM)
    {
        if(ub_MsgType == RX_MSG)
        {
            if((ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
            {
                Nrd_SetRxMsgID(ub_MsgNum, ul_MsgId);
            }
        }
        else if(ub_MsgType == TX_MSG)
        {
            if((ub_MsgNum < NRD_TX_MSG_NUM) && (Nrd_CanMsg_EN(TX_MSG, ub_Channel, ub_MsgNum)))
            {
                Nrd_SetTxMsgID(ub_MsgNum, ul_MsgId);
            }
        }
        else
        {

        }
    }
}

void Nrd_v_SetMsgEnable(uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint8 ub_MsgEnable)
{
    if(ub_Channel < NRD_CHN_NUM)
    {
        if(ub_MsgType == RX_MSG)
        {
            if(ub_MsgNum < NRD_RX_MSG_NUM)
            {
                Nrd_SetRxMsgEN(ub_MsgNum, ub_MsgEnable);
            }
        }
        else if(ub_MsgType == TX_MSG)
        {
            if(ub_MsgNum < NRD_TX_MSG_NUM)
            {
                Nrd_SetTxMsgEN(ub_MsgNum, ub_MsgEnable);
            }
        }
        else
        {

        }
    }
}

void Nrd_v_SetMsgCSAlgo(uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint8 ub_CsAlgo)
{
    if(ub_Channel < NRD_CHN_NUM)
    {
        if(ub_MsgType == RX_MSG)
        {
            if((ub_MsgNum < NRD_RX_MSG_NUM) && (Nrd_CanMsg_EN(RX_MSG, ub_Channel, ub_MsgNum)))
            {
                Nrd_SetRxMsgCSA(ub_MsgNum, ub_CsAlgo);
            }
        }
        else if((ub_MsgType == TX_MSG) && (Nrd_CanMsg_EN(TX_MSG, ub_Channel, ub_MsgNum)))
        {
            if(ub_MsgNum < NRD_TX_MSG_NUM)
            {
                Nrd_SetTxMsgCSA(ub_MsgNum, ub_CsAlgo);
            }
        }
        else
        {

        }
    }
}

uint8 Nrd_ub_MsgCsLcCheck_AlgApp(uint32 ul_Identifer, const uint8* SduPtr, uint8 ub_MessegLength)
{
    return 0;
}

uint8 Nrd_ub_IsMsgRxError(uint8 ub_Channel, uint8 ub_MsgNum)
{
	uint8 ub_RetVal = 0;

	if((ub_Channel < NRD_CHN_NUM) && (ub_MsgNum < NRD_RX_MSG_NUM))
	{
		if(Nrd_ub_GetBusOffStatus(ub_Channel))
		{
			ub_RetVal = 0;
		}
		else
		{
			ub_RetVal = Nrd_b_IsMsgRxTimeOut(ub_Channel, ub_MsgNum);
			ub_RetVal |= (uint8)(Nrd_b_IsMsgRxDetected(ub_Channel, ub_MsgNum) << 1);
		}
	}
	return ub_RetVal;
}
