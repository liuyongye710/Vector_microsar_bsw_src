/*
********************************************************************************
*
* File name: CanIf_Lcfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: YanCL/2024.7.15
* Change: 1.Add Memmap segment definition.
*         2.Update copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef CANIF_LCFG_H_
#define CANIF_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "CanIf_Cfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/

#define CANIF_NEUSAR_CANDRIVER    FALSE
#include "Can.h"


#define CANIF_RXPDU_NUM                        (25U)

#define CANIF_TXPDU_NUM                        (31U)

#define XCP_CONF_XCP_RXPDU                     (13U)

#define CANTP_CONF_CANTP_RX_FCNPDU             (14U)

#define CANTP_CONF_CANTP_RX_NPDU               (15U)

#define CANNM_CONF_CANNM_RXPDU_MODE_CAN1NM     (0xFFFFU)

#define XCP_CONF_XCP_TXPDU                     (11U)

#define CANTP_CONF_CANTP_TX_FCNPDU             (12U)

#define CANNM_CONF_CANNM_TXPDU                 (0xFFFFU)

#define CANIF_TRCVCFG_NUM                      (0U)


#define CANIF_CHANNEL_CAN_MATRIX_DCDC_V0_1_20250414_VR82BV_INDEX        (0U)
#define CANIF_CHANNEL_CANIFCTRLCFG1_INDEX                               (1U)
#define CANIF_CHANNEL_FAW_MCD_MCU_CAN_V1_4_1_D3_SO0_INDEX               (2U)
#define CANIF_CHANNEL_FAW2_MCD_MCU_CAN_DBC_V0_1_CHL_20241216_VOXYRF_INDEX (3U)
#define CANIF_CHANNEL_FAW3_HVAC_V2_0DBC_OJCG_C_INDEX                    (4U)


#define CANIF_TX_PDU_CFG_MCU1_D3_SO0_INDEX                      (0U)
#define CANIF_TX_PDU_CFG_MCU3_D3_SO0_INDEX                      (1U)
#define CANIF_TX_PDU_CFG_MCU21_D3_SO0_INDEX                     (2U)
#define CANIF_TX_PDU_CFG_MCU22_D3_SO0_INDEX                     (3U)
#define CANIF_TX_PDU_CFG_MCU23_D3_SO0_INDEX                     (4U)
#define CANIF_TX_PDU_CFG_MCU2_D3_SO0_INDEX                      (5U)
#define CANIF_TX_PDU_CFG_TPCMBAMMCU2_D3_SO0_INDEX               (6U)
#define CANIF_TX_PDU_CFG_TPDTMCU2_D3_SO0_INDEX                  (7U)
#define CANIF_TX_PDU_CFG_TPCMBAMMCU_D3_SO0_INDEX                (8U)
#define CANIF_TX_PDU_CFG_TPDTMCU_D3_SO0_INDEX                   (9U)
#define CANIF_TX_PDU_CFG_GL_TX_RES_VOXYRF_INDEX                 (10U)
#define CANIF_TX_PDU_CFG_XCP_RESPONSE_VOXYRF_INDEX              (11U)
#define CANIF_TX_PDU_CFG_MCU_TX_DATA_VOXYRF_INDEX               (12U)
#define CANIF_TX_PDU_CFG_DCDC_CMD1_VR82BV_INDEX                 (13U)
#define CANIF_TX_PDU_CFG_APCU1_OJCG_C_INDEX                     (14U)
#define CANIF_TX_PDU_CFG_APCU2_OJCG_C_INDEX                     (15U)
#define CANIF_TX_PDU_CFG_DCDC1_OJCG_C_INDEX                     (16U)
#define CANIF_TX_PDU_CFG_OPCU1_OJCG_C_INDEX                     (17U)
#define CANIF_TX_PDU_CFG_OPCU2_OJCG_C_INDEX                     (18U)
#define CANIF_TX_PDU_CFG_RELAYSTATE_OJCG_C_INDEX                (19U)
#define CANIF_TX_PDU_CFG_RELAYSTATE2_OJCG_C_INDEX               (20U)
#define CANIF_TX_PDU_CFG_IMCU1PTU_OJCG_C_INDEX                  (21U)
#define CANIF_TX_PDU_CFG_MECU1RESERVED_OJCG_C_INDEX             (22U)
#define CANIF_TX_PDU_CFG_TPCMBAMDCDC_OJCG_C_INDEX               (23U)
#define CANIF_TX_PDU_CFG_TPDTDCDC_OJCG_C_INDEX                  (24U)
#define CANIF_TX_PDU_CFG_TPCMBAMOPCU_OJCG_C_INDEX               (25U)
#define CANIF_TX_PDU_CFG_TPDTOPCU_OJCG_C_INDEX                  (26U)
#define CANIF_TX_PDU_CFG_TPCMBAMAPCU_OJCG_C_INDEX               (27U)
#define CANIF_TX_PDU_CFG_TPDTAPCU_OJCG_C_INDEX                  (28U)
#define CANIF_TX_PDU_CFG_TPCMBAMPTU_OJCG_C_INDEX                (29U)
#define CANIF_TX_PDU_CFG_TPDTPTU_OJCG_C_INDEX                   (30U)


#define CANIF_RX_PDU_CFG_TSC1MTR_D3_SO0_INDEX                   (0U)
#define CANIF_RX_PDU_CFG_EEC2HCU_D3_SO0_INDEX                   (1U)
#define CANIF_RX_PDU_CFG_CCVSHCU_D3_SO0_INDEX                   (2U)
#define CANIF_RX_PDU_CFG_TC1_D3_SO0_INDEX                       (3U)
#define CANIF_RX_PDU_CFG_TC1HANDLE_D3_SO0_INDEX                 (4U)
#define CANIF_RX_PDU_CFG_ETC1_D3_SO0_INDEX                      (5U)
#define CANIF_RX_PDU_CFG_ETC2_D3_SO0_INDEX                      (6U)
#define CANIF_RX_PDU_CFG_AMT3_D3_SO0_INDEX                      (7U)
#define CANIF_RX_PDU_CFG_HCUMCU_D3_SO0_INDEX                    (8U)
#define CANIF_RX_PDU_CFG_HCUMCU2_D3_SO0_INDEX                   (9U)
#define CANIF_RX_PDU_CFG_SC_D3_SO0_INDEX                        (10U)
#define CANIF_RX_PDU_CFG_TSC1MTR2_D3_SO0_INDEX                  (11U)
#define CANIF_RX_PDU_CFG_GL_RX_REQ_VOXYRF_INDEX                 (12U)
#define CANIF_RX_PDU_CFG_XCP_REQUEST_VOXYRF_INDEX               (13U)
#define CANIF_RX_PDU_CFG_MCU_RX_DATA_2_VOXYRF_INDEX             (14U)
#define CANIF_RX_PDU_CFG_MCU_RX_DATA_1_VOXYRF_INDEX             (15U)
#define CANIF_RX_PDU_CFG_DCDC_STATUS1_VR82BV_INDEX              (16U)
#define CANIF_RX_PDU_CFG_DCDC_STATUS2_VR82BV_INDEX              (17U)
#define CANIF_RX_PDU_CFG_DCDC_STATUS3_VR82BV_INDEX              (18U)
#define CANIF_RX_PDU_CFG_HCUDCDC_OJCG_C_INDEX                   (19U)
#define CANIF_RX_PDU_CFG_HCUAPCU_OJCG_C_INDEX                   (20U)
#define CANIF_RX_PDU_CFG_HCUOPCU_OJCG_C_INDEX                   (21U)
#define CANIF_RX_PDU_CFG_HCU3_OJCG_C_INDEX                      (22U)
#define CANIF_RX_PDU_CFG_BMS5_OJCG_C_INDEX                      (23U)
#define CANIF_RX_PDU_CFG_MCU2_OJCG_C_INDEX                      (24U)

#define CANIF_CONTROLLER_NUM         (5U)

#define CANIF_INITHOHCFG_NUM_CAN     (18U)


#define CANIF_CAN_CONTROLLER_NUM     (5U)

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define CANIF_START_SEC_CONFIG_DATA
#include "CanIf_MemMap.h"

#if (CANIF_NEUSAR_CANDRIVER == TRUE) 
extern CONST(Can_MsgCycles_st, CANIF_CONFIG_DATA) CanIf_RxPduInfo[CANIF_RXPDU_NUM];
extern CONST(Can_MsgCycles_st, CANIF_CONFIG_DATA) CanIf_TxPduInfo[CANIF_TXPDU_NUM];
#endif

extern CONST(CanIf_TrcvMapType, CANIF_CONFIG_DATA) CanIf_TrcvMap[CANIF_TRCVCFG_NUM+CANIF_VALUE_ONE];
extern CONST(CanIf_CanObjectMapType, CANIF_CONFIG_DATA) CanIf_Can_ObjectMap[CANIF_INITHOHCFG_NUM_CAN];
extern CONST(uint8, CANIF_CONFIG_DATA) CanIf_ControllerMap[CANIF_CONTROLLER_NUM + CANIF_VALUE_ONE];

#if (CANIF_PUB_MULTIPLE_DRV_SUP == STD_ON)
extern CONST(CanIf_CanMultipeDrvInfoType, CANIF_CONFIG_DATA) CanIf_CanMultipeDrvInfo[CANIF_CONTROLLER_NUM];
#endif 

extern VAR(CanIf_RxPduCfgType, CANIF_CONFIG_DATA) CanIf_RxPduCfg[CANIF_RXPDU_NUM + 1U];/* WangM CONST-->VAR for Calibration */
extern VAR(CanIf_TxPduCfgType, CANIF_CONFIG_DATA) CanIf_TxPduCfg[CANIF_TXPDU_NUM + 1U];/* WangM CONST-->VAR for Calibration */

#if (CANIF_PRIVATE_SWFILTER_TYPE == CANIF_SWFILTER_INDEX) 
extern CONSTP2CONST(uint16, CANIF_CONFIG_DATA, CANIF_APPL_CONST) CanIf_CanIdMapRxPduPtrList[CANIF_CONTROLLER_NUM + 1U];
extern CONSTP2CONST(uint16, CANIF_CONFIG_DATA, CANIF_APPL_CONST) CanIf_CanIdMapRxPduPtrList_CANFD[CANIF_CONTROLLER_NUM + 1U];
#endif 

extern CONST(uint8, CANIF_CONFIG_DATA) CanIf_CanControllerIdMap[CANIF_CAN_CONTROLLER_NUM + CANIF_VALUE_ONE];

#define CANIF_STOP_SEC_CONFIG_DATA
#include "CanIf_MemMap.h"

#define CANIF_START_SEC_VAR_INIT
#include "CanIf_MemMap.h"

extern VAR(Can_IdType, CANIF_VAR_INIT) CanIf_TxCanId[CANIF_TXPDU_NUM + 1U];

#define CANIF_STOP_SEC_VAR_INIT
#include "CanIf_MemMap.h"


/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif /* CANIF_LCFG_H_ */


