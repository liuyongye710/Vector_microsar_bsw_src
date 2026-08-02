/********************************************************************************
*
*  File name:   CDS_Temp.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "CDS_Temp.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
#define XCP_START_SEC_CONST_CORE0_BLOCK0 
#include "FAW_MemMap.h"
/* Receive Message Config Structure */
const TypeRecvMsgCfg ReceiveMessageConfig[CDS_MSG_RX_CNT_MAX] = 
{
/*  EN Node    ID        pCallback   pSTATE   TO(ERR,OK) CS(ERR,OK) Mask  Period  Tick */
                                     /* CAN2 */
/* 0*/{1, 2,   0x0C002703,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* TSC1Mtr_D3_sO0       */
/* 1*/{1, 2,   0x0CF00327,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* EEC2HCU_D3_sO0       */
/* 2*/{1, 2,   0x18FEF127,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* CCVSHCU_D3_sO0       */
/* 3*/{1, 2,   0x0C010327,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* TC1_D3_sO0           */ 
/* 4*/{1, 2,   0x0C010005,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* TC1Handle_D3_sO0     */
/* 5*/{1, 2,   0x0CF00203,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* ETC1_D3_sO0          */
/* 6*/{1, 2,   0x18F00503,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* ETC2_D3_sO0          */
/* 7*/{1, 2,   0x18FF6503,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* AMT3_D3_sO0          */
/* 8*/{1, 2,   0x0BFF0527,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCUMCU_D3_sO0        */
/* 9*/{1, 2,   0x0BFF9327,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCUMCU2_D3_sO0       */
/*10*/{1, 2,   0x18FF0227,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* SC_D3_sO0            */
/*11*/{1, 2,   0x0C002704,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* TSC1Mtr2_D3_sO0      */
                                     /* CAN3 */
/*12*/{1, 3,   0x000007FA,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* GL_Rx_REQ_Voxyrf     */
/*13*/{1, 3,   0x000007A0,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* XCP_Request_Voxyrf   */
/*14*/{1, 3,   0x18DBEFF1,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* MCU_Rx_Data_2_Voxyrf */
/*15*/{1, 3,   0x18DAEFF1,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* MCU_Rx_Data_1_Voxyrf */
                                     /* CAN1 */
/*16*/{1, 0,   0x00000302,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* DCDC_Status1_VR82BV  */
/*17*/{1, 0,   0x00000303,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* DCDC_Status2_VR82BV  */
/*18*/{1, 0,   0x00000304,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* DCDC_Status3_VR82BV  */
                                     /* CAN4 */
/*19*/{1, 4,   0x18FF0727,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCUDCDC_OjcG_c       */
/*20*/{1, 4,   0x18FF0827,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCUAPCU_OjcG_c       */
/*21*/{1, 4,   0x18FF0627,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCUOPCU_OjcG_c       */
/*22*/{1, 4,   0x18FF0F27,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* HCU3_OjcG_c          */
/*23*/{1, 4,   0x18FF3AF3,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* BMS5_OjcG_c          */
/*24*/{1, 4,   0x18FFDFEF,  NULL_PTR,  NULL_PTR,  10,  10,   10,  10,   255,  100,    0}, /* MCU2_OjcG_c          */
};

/* Send Message Config Structure */
const TypeTranMsgCfg TransmitMessageConfig[CDS_MSG_TX_CNT_MAX] = 
{
/*  EN  Node    ID       pCallback  Period Tick */
             /* CAN2 */
/* 0*/{1,  2,  0x0CFFDEEF,  NULL_PTR,   0,    0}, /* MCU1_D3_sO0          */
/* 1*/{1,  2,  0x18FF3EEF,  NULL_PTR,   0,    0}, /* MCU3_D3_sO0          */
/* 2*/{1,  2,  0x0CFFDEF0,  NULL_PTR,   0,    0}, /* MCU21_D3_sO0         */
/* 3*/{1,  2,  0x18FFDFF0,  NULL_PTR,   0,    0}, /* MCU22_D3_sO0         */
/* 4*/{1,  2,  0x18FF3EF0,  NULL_PTR,   0,    0}, /* MCU23_D3_sO0         */
/* 5*/{1,  2,  0x18FFDFEF,  NULL_PTR,   0,    0}, /* MCU2_D3_sO0          */
/* 6*/{1,  2,  0x1CECFFF0,  NULL_PTR,   0,    0}, /* TPCMBAMMCU2_D3_sO0   */
/* 7*/{1,  2,  0x1CEBFFF0,  NULL_PTR,   0,    0}, /* TPDTMCU2_D3_sO0      */
/* 8*/{1,  2,  0x1CECFFEF,  NULL_PTR,   0,    0}, /* TPCMBAMMCU_D3_sO0    */
/* 9*/{1,  2,  0x1CEBFFEF,  NULL_PTR,   0,    0}, /* TPDTMCU_D3_sO0       */
             /* CAN3 */
/*10*/{1,  3,  0x000007CB,  NULL_PTR,   0,    0}, /* GL_Tx_RES_Voxyrf     */
/*11*/{1,  3,  0x000007A1,  NULL_PTR,   0,    0}, /* XCP_Response_Voxyrf  */
/*12*/{1,  3,  0x18DAF1EF,  NULL_PTR,   0,    0}, /* MCU_Tx_Data_Voxyrf   */
             /* CAN1 */
/*13*/{1,  0,  0x00000300,  NULL_PTR,   0,    0}, /* DCDC_Cmd1_VR82BV     */
             /* CAN4 */
/*14*/{1,  4,  0x18FFE830,  NULL_PTR,   0,    0}, /* APCU1_OjcG_c         */
/*15*/{1,  4,  0x18FFE930,  NULL_PTR,   0,    0}, /* APCU2_OjcG_c         */
/*16*/{1,  4,  0x18FFE31A,  NULL_PTR,   0,    0}, /* DCDC1_OjcG_c         */
/*17*/{1,  4,  0x18FFE02E,  NULL_PTR,   0,    0}, /* OPCU1_OjcG_c         */
/*18*/{1,  4,  0x18FFE12E,  NULL_PTR,   0,    0}, /* OPCU2_OjcG_c         */
/*19*/{1,  4,  0x18FFE760,  NULL_PTR,   0,    0}, /* RelayState_OjcG_c    */
/*20*/{1,  4,  0x18FFB460,  NULL_PTR,   0,    0}, /* RelayState2_OjcG_c   */
/*21*/{1,  4,  0x18FF0960,  NULL_PTR,   0,    0}, /* IMCU1PTU_OjcG_c      */
/*22*/{1,  4,  0x18FFED60,  NULL_PTR,   0,    0}, /* MECU1Reserved_OjcG_c */
/*23*/{1,  4,  0x1CECFF1A,  NULL_PTR,   0,    0}, /* TPCMBAMDCDC_OjcG_c   */
/*24*/{1,  4,  0x1CEBFF1A,  NULL_PTR,   0,    0}, /* TPDTDCDC_OjcG_c      */
/*25*/{1,  4,  0x1CECFF2E,  NULL_PTR,   0,    0}, /* TPCMBAMOPCU_OjcG_c   */
/*26*/{1,  4,  0x1CEBFF2E,  NULL_PTR,   0,    0}, /* TPDTOPCU_OjcG_c      */
/*27*/{1,  4,  0x1CECFF30,  NULL_PTR,   0,    0}, /* TPCMBAMAPCU_OjcG_c   */
/*28*/{1,  4,  0x1CEBFF30,  NULL_PTR,   0,    0}, /* TPDTAPCU_OjcG_c      */
/*29*/{1,  4,  0x1CECFF60,  NULL_PTR,   0,    0}, /* TPCMBAMPTU_OjcG_c    */
/*30*/{1,  4,  0x1CEBFF60,  NULL_PTR,   0,    0}, /* TPDTPTU_OjcG_c       */
};
#define XCP_STOP_SEC_CONST_CORE0_BLOCK0 
#include "FAW_MemMap.h"
/*********************************************************************************
*   Local Variables
*********************************************************************************/
/*********************************************************************************
*   Global Functions
*********************************************************************************/

/*********************************************************************************
*   Local Functions
*********************************************************************************/
void Can_Config_Init(void)
{
    uint16 rx_cnt = 0;
    uint16 tx_cnt = 0;
    for(rx_cnt = 0; rx_cnt < CDS_MSG_RX_CNT_MAX; rx_cnt++)
    {
        if(ReceiveMessageConfig[rx_cnt].id_config > 0x7FF)
        {
            CanIf_RxPduCfg[rx_cnt].canId = (CANIF_EXTENDED_CANID_TYPE | ReceiveMessageConfig[rx_cnt].id_config);
        }
        else
        {
            CanIf_RxPduCfg[rx_cnt].canId = ReceiveMessageConfig[rx_cnt].id_config;
        }
        CanIf_RxPduCfg[rx_cnt].ctrlId = ReceiveMessageConfig[rx_cnt].node_config;
    }

    for(tx_cnt = 0; tx_cnt < CDS_MSG_TX_CNT_MAX; tx_cnt++)
    {
        if(TransmitMessageConfig[tx_cnt].id_config > 0x7FF)
        {
            CanIf_TxCanId[tx_cnt] = (CANIF_EXTENDED_CANID_TYPE | TransmitMessageConfig[tx_cnt].id_config);
        }
        else
        {
        	CanIf_TxCanId[tx_cnt] = TransmitMessageConfig[tx_cnt].id_config;
        }
        CanIf_TxPduCfg[tx_cnt].ctrlId = TransmitMessageConfig[tx_cnt].node_config;
    }
}
