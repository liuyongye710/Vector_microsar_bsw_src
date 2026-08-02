/********************************************************************************
*
*  File name:   Com_Appl.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Com_Appl.h"
#include "ComRx_Indication.h"
#include "J1939Tp_Cfg.h"
/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/
#define   DM1_J1939TpID    1
/*********************************************************************************
*   Global Variables
*********************************************************************************/
extern VAR(J1939Tp_TxSduStateType, J1939TP_VAR_INIT) J1939Tp_TxSduState[J1939TP_TXNSDU_NUMBER + 1U];
/*********************************************************************************
*   Local Variables
*********************************************************************************/
/*********************************************************************************
*   Global Functions
*********************************************************************************/

/*********************************************************************************
*   Local Functions
*********************************************************************************/
FUNC(uint16, COM_CODE) User_GetJ1939MessageDM1DaL(void)
{
    uint16 Len_DM1_EMS;
    
    Len_DM1_EMS = Com_TxPduInfo[Hnd_Msg_Tx_DM1MCU_D3_sO0].acPduLenth;

    return Len_DM1_EMS;
}

FUNC(void, COM_CODE) User_SetJ1939MessageDM1DaL(uint16 sLength)
{

    Com_TxPduInfo[Hnd_Msg_Tx_DM1MCU_D3_sO0].acPduLenth = sLength;
    J1939Tp_TxSduInfo[DM1_J1939TpID].SduLength = sLength;
    Com_TxPduInfo[Hnd_Msg_Tx_DM1MCU_D3_sO0].pduTpMonitor->pduRemainLen = sLength;

}
FUNC(boolean, COM_CODE) Com_WriteTxMessage(PduIdType ComTxIPduHandle,P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) DataPtr)
{
    boolean retVal = FALSE;
    Std_ReturnType ComRet = E_NOT_OK;
    COM_TxPduInfo_st* com_astPdu = NULL_PTR;
    com_astPdu = Com_TxPduInfo;
    uint8* pduDataPtr = Com_TxPduInfo[ComTxIPduHandle].dataRaw;
 	PduInfoType astSenderPduMsg = {NULL_PTR, COM_INIT_ZERO};
    
    if((ComTxIPduHandle < COM_TXPDU_NUM) && (DataPtr != NULL_PTR))
    {
        if( COM_PDU_STA_INACTIVE != com_astPdu->astPduInterMonitor->pduSta )
        {
            memcpy(pduDataPtr, DataPtr, com_astPdu[ComTxIPduHandle].acPduLenth);
            if(ComTxIPduHandle != Hnd_Msg_Tx_DCDC_Cmd1_VR82BV)
            {
                astSenderPduMsg.SduLength = com_astPdu[ComTxIPduHandle].acPduLenth;
                astSenderPduMsg.SduDataPtr = pduDataPtr;
                ComRet = PduR_ComTransmit(Com_TxPduInfo[ComTxIPduHandle].lowLayerPduID,&astSenderPduMsg);
                if(E_OK == ComRet)
                {
                    retVal = TRUE;
                }
            }
            else
            {
                retVal = TRUE;
            }
        }
    }

    return retVal;
}

FUNC(boolean, COM_CODE) Com_ReadRxMessage(PduIdType ComRxIPduHandle, P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) DataPtr)
{
    boolean retVal = FALSE;

    if((ComRxIPduHandle < COM_RXPDU_NUM) && (DataPtr != NULL_PTR))
    {
        for(uint8 i=0; i<Com_RxPduInfo[ComRxIPduHandle].acPduLenth; i++)
        {
    	    DataPtr[i] = Com_RxPduInfo[ComRxIPduHandle].datavalid[i];
        }
	    retVal = TRUE;
    }

    return retVal;
}
