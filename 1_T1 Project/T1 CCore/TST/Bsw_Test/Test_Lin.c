/********************************************************************************
*
*  File name:   Test_Lin.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Test_Lin.h"
#include "Com.h"
//#include "Lin.h"
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
#if( TEST_LIN_ENABLE == STD_ON )
uint8 AGM1_EMS_Test[4] = {0};
uint8 AGM2_EMS_Test[4] = {0};
uint8 HandleToEMS_Test[4] = {0};
uint8 MSWToEMS_Test[6] = {0};
#endif
/*********************************************************************************
*   Local Functions
*****/
#if( TEST_LIN_ENABLE == STD_ON )
void Test_Lin_SendSignal(void)
{
    uint8 u8Test_Lin = 1;

    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM1_CMD_QDCKJS_AGM1_POSITION_CMD_EMS_AGM1_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM1_CMD_QDCKJS_AGM1_CALBISENBLD_CMD_EMS_AGM1_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM1_CMD_QDCKJS_AGM1BOOSTTRQ_CMD_EMS_AGM1_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM1_CMD_QDCKJS_AGM1_HLDGCURSTG_CMD_EMS_AGM1_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);

    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM2_CMD_QDCKJS_AGM2_POSITION_CMD_EMS_AGM2_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM2_CMD_QDCKJS_AGM2_CALBISENBLD_CMD_EMS_AGM2_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM2_CMD_QDCKJS_AGM2BOOSTTRQ_CMD_EMS_AGM2_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
    Com_SendSignal(COMCONF_COMSIGNAL_EMS_AGM2_CMD_QDCKJS_AGM2_HLDGCURSTG_CMD_EMS_AGM2_CMD_FAW_EMS_AGM_LIN_V1_0_LDF_TX,&u8Test_Lin);
}

void Test_Lin_SendMessage(void)
{
    uint8 Test_Lin1[4] = {1,2,3,4};
    uint8 Test_Lin2[4] = {5,6,7,8};

    Com_WriteTxMessage(Hnd_Msg_Tx_EMS_AGM1_CMD_QdCKJs, Test_Lin1);
    Com_WriteTxMessage(Hnd_Msg_Tx_EMS_AGM2_CMD_QdCKJs, Test_Lin2);
}

void Test_Lin_ReceiveMessage(void)
{
    Com_ReadRxMessage(Hnd_Msg_Rx_AGM1_EMS_ST_QdCKJs, AGM1_EMS_Test);
    Com_ReadRxMessage(Hnd_Msg_Rx_AGM2_EMS_ST_QdCKJs, AGM2_EMS_Test);
    Com_ReadRxMessage(Hnd_Msg_Rx_HandleToEMS_QdCKJs, HandleToEMS_Test);
    Com_ReadRxMessage(Hnd_Msg_Rx_MSWToEMS_QdCKJs, MSWToEMS_Test);
}

#endif