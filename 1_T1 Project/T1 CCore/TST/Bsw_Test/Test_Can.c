/********************************************************************************
*
*  File name:   Test_Can.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Test_Can.h"
#include "Com.h"
#include "Can.h"
#include "Com_Appl.h"
#include "ComRx_Indication.h"
/*********************************************************************************
*   Local  Macros
*********************************************************************************/
#define CANRX_START                       (4U)
#define CANRX_MSG_MAX                     (COM_RXPDU_NUM)

/*********************************************************************************
*   Local Struct
*********************************************************************************/
#if( TEST_CAN_ENABLE == STD_ON )
typedef struct
{
    uint8    SduDataPtr[8]; 
} MsgInfoType;
#endif
/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
#if( TEST_CAN_ENABLE == STD_ON )
MsgInfoType COM_CanRxMsgBuffer[CANRX_MSG_MAX] = {{0x00U},};
#endif

#if( TEST_BUSOFF_ENABLE == STD_ON )
boolean BusOff_Sts = FALSE;
#endif
/*********************************************************************************
*   Local Functions
*********************************************************************************/

#if( TEST_CAN_ENABLE == STD_ON )
void Test_Can_SendMessage(void)
{
    uint8 u8TestMsg_8[8] = {1,2,3,4,5,6,7,8};
    //CAN_2
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU1_D3_sO0,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU3_D3_sO0,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU21_D3_sO0,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU22_D3_sO0,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU23_D3_sO0,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MCU2_D3_sO0,u8TestMsg_8);

    //CAN_1
    Com_WriteTxMessage( Hnd_Msg_Tx_DCDC_Cmd1_VR82BV,u8TestMsg_8);

    //CAN_4
    Com_WriteTxMessage( Hnd_Msg_Tx_APCU1_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_APCU2_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_DCDC1_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_OPCU1_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_OPCU2_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_RelayState_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_RelayState2_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_IMCU1PTU_OjcG_c,u8TestMsg_8);
    Com_WriteTxMessage( Hnd_Msg_Tx_MECU1Reserved_OjcG_c,u8TestMsg_8);

    // //CAN_3
    // Can_PduType pduInfo_123;
    // uint8 txBuffer_123[8] = {1,0,1,0,1,0,1,0};
    // pduInfo_123.id = 0x123;
    // pduInfo_123.length = 8;
    // pduInfo_123.sdu = txBuffer_123;
    // pduInfo_123.swPduHandle = 1;
    // Can_Write(TX_CAN3, &pduInfo_123);
}

void Test_Can_ReceiveMessage(void)
{
    uint8 ComRxCanIPduHandle;

    for(ComRxCanIPduHandle = 0;ComRxCanIPduHandle < COM_RXPDU_NUM;ComRxCanIPduHandle++)
	{
        Com_ReadRxMessage(ComRxCanIPduHandle,&COM_CanRxMsgBuffer[ComRxCanIPduHandle]);
	}
}
#endif

#if( TEST_BUSOFF_ENABLE == STD_ON )
void Test_BusOff_Send_Cycle(void)
{
    if(FALSE == BusOff_Sts)
    {
        Can_PduType pduInfo_123;
        uint8 txBuffer_123[8] = {1,0,1,0,1,0,1,0};

        pduInfo_123.id = 0x123;
        pduInfo_123.length = 8;
        pduInfo_123.sdu = txBuffer_123;
        pduInfo_123.swPduHandle = 1;
        Can_Write(TX_CAN1, &pduInfo_123);
    }
}
void Test_BusOff_Send_Single(void)
{
    Can_PduType pduInfo_321;
    uint8 txBuffer_321[8] = {1,0,1,0,1,0,1,0};

    pduInfo_321.id = 0x321;
    pduInfo_321.length = 8;
    pduInfo_321.sdu = txBuffer_321;
    pduInfo_321.swPduHandle = 1;
    Can_Write(TX_CAN1, &pduInfo_321);
}
void Test_BusOff_SetStatus(boolean Status)
{
    BusOff_Sts = Status;
}
#endif
