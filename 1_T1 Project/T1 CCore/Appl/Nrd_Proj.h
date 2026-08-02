/********************************************************************************
*
*  File name:   Nrd_Proj.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "ComStack_Types.h"
#include "CanSM.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
/*********************************************************************************
*   Global  Macros
*********************************************************************************/
#define NRD_CAN_BUSOFF_CHANNEL_NUM     5
#define NRD_CHN_NUM       5U
#define NRD_TX_MSG_NUM    23U
#define NRD_RX_MSG_NUM    21U


#define RX_MSG    0U
#define TX_MSG    1U

#define Hnd_Msg_Tx_MCU1_D3_sO0 	        0U
#define Hnd_Msg_Tx_ECMCU_D3_sO0 	    1U
#define Hnd_Msg_Tx_MCU3_D3_sO0 	        2U
#define Hnd_Msg_Tx_MCU21_D3_sO0 	    3U
#define Hnd_Msg_Tx_MCU22_D3_sO0 	    4U
#define Hnd_Msg_Tx_MCU23_D3_sO0 	    5U
#define Hnd_Msg_Tx_DM1MCU_D3_sO0 	    6U
#define Hnd_Msg_Tx_DM1MCU2_D3_sO0 	    7U
#define Hnd_Msg_Tx_MCU2_D3_sO0 	        8U
#define Hnd_Msg_Tx_DCDC_Cmd1_VR82BV     9U
#define Hnd_Msg_Tx_APCU1_OjcG_c         10U
#define Hnd_Msg_Tx_APCU2_OjcG_c         11U
#define Hnd_Msg_Tx_DM1APCU_OjcG_c       12U
#define Hnd_Msg_Tx_DCDC1_OjcG_c         13U
#define Hnd_Msg_Tx_DM1DCDC_OjcG_c       14U
#define Hnd_Msg_Tx_DM1OPCU_OjcG_c       15U
#define Hnd_Msg_Tx_OPCU1_OjcG_c         16U
#define Hnd_Msg_Tx_OPCU2_OjcG_c         17U
#define Hnd_Msg_Tx_RelayState_OjcG_c    18U
#define Hnd_Msg_Tx_RelayState2_OjcG_c   19U
#define Hnd_Msg_Tx_IMCU1PTU_OjcG_c      20U
#define Hnd_Msg_Tx_MECU1Reserved_OjcG_c 21U
#define Hnd_Msg_Tx_DM1PTU_OjcG_c        22U

//Rx
#define Hnd_Msg_Rx_TSC1Mtr_D3_sO0	    0U
#define Hnd_Msg_Rx_EEC2HCU_D3_sO0	    1U
#define Hnd_Msg_Rx_CCVSHCU_D3_sO0	    2U
#define Hnd_Msg_Rx_TC1_D3_sO0	        3U
#define Hnd_Msg_Rx_TC1Handle_D3_sO0	    4U
#define Hnd_Msg_Rx_ETC1_D3_sO0	        5U
#define Hnd_Msg_Rx_ETC2_D3_sO0	        6U
#define Hnd_Msg_Rx_AMT3_D3_sO0	        7U
#define Hnd_Msg_Rx_HCUMCU_D3_sO0	    8U
#define Hnd_Msg_Rx_HCUMCU2_D3_sO0	    9U
#define Hnd_Msg_Rx_SC_D3_sO0	        10U
#define Hnd_Msg_Rx_TSC1Mtr2_D3_sO0	    11U
#define Hnd_Msg_Rx_DCDC_Status1_VR82BV  12U
#define Hnd_Msg_Rx_DCDC_Status2_VR82BV  13U
#define Hnd_Msg_Rx_DCDC_Status3_VR82BV  14U
#define Hnd_Msg_Rx_HCUDCDC_OjcG_c       15U
#define Hnd_Msg_Rx_HCUAPCU_OjcG_c       16U
#define Hnd_Msg_Rx_HCUOPCU_OjcG_c       17U
#define Hnd_Msg_Rx_HCU3_OjcG_c          18U
#define Hnd_Msg_Rx_BMS5_OjcG_c          19U
#define Hnd_Msg_Rx_MCU2_OjcG_c          20U
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
extern uint8   Nrd_ub_GetBusOffStatus (uint8 ub_Chn);
extern boolean Nrd_b_IsMsgRxTimeOut (uint8 ub_Channel, uint8 ub_MsgNum);
extern boolean Nrd_b_IsMsgRxLiveCounterFailure(uint8 ub_Channel, uint8 ub_MsgNum);
extern boolean Nrd_b_IsMsgRxCheckSumFailure(uint8 ub_Channel, uint8 ub_MsgNum);
extern boolean Nrd_b_IsMsgRxDetected (uint8 ub_Channel, uint8 ub_MsgNum);
extern boolean Nrd_b_RxMsgDetected(uint8 ub_Channel, uint8 ub_MsgNum, const uint8* SduPtr);
extern boolean Nrd_b_TxMsgHandler (uint8 ub_Channel, uint8 ub_MsgNum, const uint8* SduPtr);
extern boolean Nrd_b_GetKeyStatus (boolean* b_SystemKey);
extern uint32  Nrd_ul_GetPowerVltg(void);
extern void    Nrd_v_SetRxMsgTOTime(uint8 ub_Channel, uint8 ub_MsgNum, uint16 uw_TOTime);
extern void    Nrd_v_SetMsgID (uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint32 ul_MsgId);
extern void    Nrd_v_SetMsgEnable (uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint8 ub_MsgEnable);
extern void    Nrd_v_SetMsgCSAlgo (uint8 ub_Channel, uint8 ub_MsgNum, uint8 ub_MsgType, uint8 ub_CsAlgo);
extern uint8   Nrd_ub_MsgCsLcCheck_AlgApp(uint32 ul_Identifer, const uint8* SduPtr, uint8 ub_MessegLength);
extern uint8   Nrd_ub_IsMsgRxError(uint8 ub_Channel, uint8 ub_MsgNum);
