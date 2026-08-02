/********************************************************************************
*
*  File name:   ComRx_Indication.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "ComRx_Indication.h"
#include "string.h"
#include "Nrd_Cfg.h"
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
uint8	COM_RxMsgData_TSC1Mtr_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_EEC2HCU_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_CCVSHCU_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_TC1_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_TC1Handle_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_ETC1_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_ETC2_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_AMT3_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCUMCU_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCUMCU2_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_SC_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_TSC1Mtr2_D3_sO0[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};

uint8	COM_RxMsgData_DCDC_Status1_VR82BV[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_DCDC_Status2_VR82BV[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_DCDC_Status3_VR82BV[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCUDCDC_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCUAPCU_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCUOPCU_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_HCU3_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_BMS5_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};
uint8	COM_RxMsgData_MCU2_OjcG_c[8U] = {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,};

/*********************************************************************************
*   Local Variables
*********************************************************************************/
boolean Com_RxIpduCallout_TSC1Mtr_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_TSC1Mtr_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_TSC1Mtr_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_EEC2HCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_EEC2HCU_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_EEC2HCU_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_EEC2HCU_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_EEC2HCU_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_EEC2HCU_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_CCVSHCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_CCVSHCU_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_CCVSHCU_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_CCVSHCU_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_CCVSHCU_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_CCVSHCU_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_TC1_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_TC1_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_TC1_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_TC1Handle_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_TC1Handle_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1Handle_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1Handle_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_TC1Handle_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TC1Handle_D3_sO0, TRUE);
}


boolean Com_RxIpduCallout_ETC1_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_ETC1_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC1_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC1_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_ETC1_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC1_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_ETC2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_ETC2_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC2_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC2_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_ETC2_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_ETC2_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_AMT3_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_AMT3_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_AMT3_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_AMT3_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_AMT3_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_AMT3_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_HCUMCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCUMCU_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCUMCU_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_HCUMCU2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCUMCU2_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU2_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU2_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCUMCU2_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_HCUMCU2_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_SC_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_SC_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_SC_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_SC_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_SC_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_SC_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_TSC1Mtr2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_TSC1Mtr2_D3_sO0, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr2_D3_sO0, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr2_D3_sO0, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_TSC1Mtr2_D3_sO0(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN2, Hnd_Msg_Rx_TSC1Mtr2_D3_sO0, TRUE);
}

boolean Com_RxIpduCallout_DCDC_Status1_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_DCDC_Status1_VR82BV, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status1_VR82BV, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status1_VR82BV, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_DCDC_Status1_VR82BV(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status1_VR82BV, TRUE);
}

boolean Com_RxIpduCallout_DCDC_Status2_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_DCDC_Status2_VR82BV, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status2_VR82BV, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status2_VR82BV, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_DCDC_Status2_VR82BV(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status2_VR82BV, TRUE);
}

boolean Com_RxIpduCallout_DCDC_Status3_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_DCDC_Status3_VR82BV, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status3_VR82BV, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status3_VR82BV, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_DCDC_Status3_VR82BV(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN0, Hnd_Msg_Rx_DCDC_Status3_VR82BV, TRUE);
}

boolean Com_RxIpduCallout_HCUDCDC_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCUDCDC_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUDCDC_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUDCDC_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCUDCDC_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUDCDC_OjcG_c, TRUE);
}

boolean Com_RxIpduCallout_HCUAPCU_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCUAPCU_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUAPCU_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUAPCU_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCUAPCU_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUAPCU_OjcG_c, TRUE);
}

boolean Com_RxIpduCallout_HCUOPCU_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCUOPCU_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUOPCU_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUOPCU_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCUOPCU_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCUOPCU_OjcG_c, TRUE);
}

boolean Com_RxIpduCallout_HCU3_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_HCU3_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCU3_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_HCU3_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_HCU3_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_HCU3_OjcG_c, TRUE);
}

boolean Com_RxIpduCallout_BMS5_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_BMS5_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_BMS5_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_BMS5_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_BMS5_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_BMS5_OjcG_c, TRUE);
}

boolean Com_RxIpduCallout_MCU2_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr )
{
    memcpy(COM_RxMsgData_MCU2_OjcG_c, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_MCU2_OjcG_c, FALSE);
    Nrd_Set_RxDetected_Status(Nrd_CAN4, Hnd_Msg_Rx_MCU2_OjcG_c, TRUE);
    
    return TRUE;
}
void Com_RxIpduTimeout_MCU2_OjcG_c(void)
{
    Nrd_Set_TimeOut_Status(Nrd_CAN4, Hnd_Msg_Rx_MCU2_OjcG_c, TRUE);
}