/*
********************************************************************************
*
*  File name: PduR_cfg.h
*
*  Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: LuQ/2024.05.20
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef PDUR_CFG_H_
#define PDUR_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* PduRGeneral Start */
/**
 * Name: PduRDevErrorDetect
 * Brief: Switches the Default Error Tracer (Det) detection and notification
 *        ON or OFF.
 */
#define PDUR_DEV_ERROR_DETECT (STD_OFF)

/**
 * Name: PduRVersionInfoApi
 * Brief: If true the PduR_GetVersionInfo API is available.
 */
#define PDUR_VERSION_INFO_API (STD_OFF)
/**
 * Name: PduRZeroCostOperation
 * Brief: If set the PduR configuration generator will report an error if
 *        zero-costoperation cannot be fulfilled.
 */
#define PDUR_ZERO_COST_OPERATION (STD_OFF)
#define PDUR_SUPPORT_MULTICORE (STD_OFF)
/* PduRGeneral End   */

/**
 * Note:
 * The gateway requirements are deliberately separated to allow an efficient
 * implementation of the PDU Router module in case
 * gatewaying is not needed.
 * In case the PDU Router module allows gatewaying of I-PDUs, these requirements
 * are seen as additional and not replacing previous requirements.
 */
#if ((defined PDUR_SUPPORT_IF_GETWAY) || (defined PDUR_SUPPORT_TP_GETWAY))
#define PDUR_SUPPORT_GETWAY             (STD_ON)
#else   /* #if ((defined PDUR_SUPPORT_IF_GETWAY) || (defined PDUR_SUPPORT_TP_GETWAY)) */
#define PDUR_SUPPORT_GETWAY             (STD_OFF)
#endif   /* #if ((defined PDUR_SUPPORT_IF_GETWAY) || (defined PDUR_SUPPORT_TP_GETWAY)) */


/* Note:
   The multicast feature is separated to an own section since there are issues using
   this feature as described in section 4.1.1.
*/
#if ((defined PDUR_SUPPORT_IF_MULICAST) || (defined PDUR_SUPPORT_TP_MULICAST))
#define PDUR_SUPPORT_MULICAST               (STD_ON)
#else   /* #if ((defined PDUR_SUPPORT_IF_MULICAST) || (defined PDUR_SUPPORT_TP_MULICAST)) */
#define PDUR_SUPPORT_MULICAST               (STD_OFF)
#endif   /* #if ((defined PDUR_SUPPORT_IF_MULICAST) || (defined PDUR_SUPPORT_TP_MULICAST)) */

#if ((defined PDUR_SUPPORT_IF_MULICAST) && (defined PDUR_SUPPORT_TP_MULICAST))
#define PDUR_SUPPORT_MULICAST_IF_AND_TP     (STD_ON)
#else   /* #if ((defined PDUR_SUPPORT_IF_MULICAST) || (defined PDUR_SUPPORT_TP_MULICAST)) */
#define PDUR_SUPPORT_MULICAST_IF_AND_TP     (STD_OFF)
#endif   /* #if ((defined PDUR_SUPPORT_IF_MULICAST) || (defined PDUR_SUPPORT_TP_MULICAST)) */

/* The NeuSAR communication module does not currently support MeteData processing. */

#if (defined NEUSAR_SUPPORT_METE_DATA_LENGTH && (STD_ON == NEUSAR_SUPPORT_METE_DATA_LENGTH))
#error This version does not support meteData, please do not enable this item.
#endif  /* #if (defined NEUSAR_SUPPORT_METE_DATA_LENGTH && (STD_ON == NEUSAR_SUPPORT_METE_DATA_LENGTH)) */

#define PDUR_SrcPduID_MCU1_D3_sO0 (0)
#define PDUR_SrcPduID_ECMCU_D3_sO0 (1)
#define PDUR_SrcPduID_MCU3_D3_sO0 (2)
#define PDUR_SrcPduID_MCU21_D3_sO0 (3)
#define PDUR_SrcPduID_MCU22_D3_sO0 (4)
#define PDUR_SrcPduID_MCU23_D3_sO0 (5)
#define PDUR_SrcPduID_DM1MCU_D3_sO0 (6)
#define PDUR_SrcPduID_DM1MCU2_D3_sO0 (7)
#define PDUR_SrcPduID_MCU2_D3_sO0 (8)
#define PDUR_SrcPduID_TSC1Mtr_D3_sO0 (9)
#define PDUR_SrcPduID_EEC2HCU_D3_sO0 (10)
#define PDUR_SrcPduID_CCVSHCU_D3_sO0 (11)
#define PDUR_SrcPduID_TC1_D3_sO0 (12)
#define PDUR_SrcPduID_TC1Handle_D3_sO0 (13)
#define PDUR_SrcPduID_ETC1_D3_sO0 (14)
#define PDUR_SrcPduID_ETC2_D3_sO0 (15)
#define PDUR_SrcPduID_AMT3_D3_sO0 (16)
#define PDUR_SrcPduID_HCUMCU_D3_sO0 (17)
#define PDUR_SrcPduID_HCUMCU2_D3_sO0 (18)
#define PDUR_SrcPduID_SC_D3_sO0 (19)
#define PDUR_SrcPduID_TSC1Mtr2_D3_sO0 (20)
#define PDUR_SrcPduID_MCU_Tx_Data_Voxyrf (21)
#define PDUR_SrcPduID_MCU_Rx_Data_2_Voxyrf (22)
#define PDUR_SrcPduID_MCU_Rx_Data_1_Voxyrf (23)
#define PDUR_SrcPduID_DCDC_Cmd1_VR82BV (24)
#define PDUR_SrcPduID_DCDC_Status1_VR82BV (25)
#define PDUR_SrcPduID_DCDC_Status2_VR82BV (26)
#define PDUR_SrcPduID_DCDC_Status3_VR82BV (27)
#define PDUR_SrcPduID_APCU1_OjcG_c (28)
#define PDUR_SrcPduID_APCU2_OjcG_c (29)
#define PDUR_SrcPduID_DM1APCU_OjcG_c (30)
#define PDUR_SrcPduID_DCDC1_OjcG_c (31)
#define PDUR_SrcPduID_DM1DCDC_OjcG_c (32)
#define PDUR_SrcPduID_DM1OPCU_OjcG_c (33)
#define PDUR_SrcPduID_OPCU1_OjcG_c (34)
#define PDUR_SrcPduID_OPCU2_OjcG_c (35)
#define PDUR_SrcPduID_RelayState_OjcG_c (36)
#define PDUR_SrcPduID_RelayState2_OjcG_c (37)
#define PDUR_SrcPduID_IMCU1PTU_OjcG_c (38)
#define PDUR_SrcPduID_MECU1Reserved_OjcG_c (39)
#define PDUR_SrcPduID_DM1PTU_OjcG_c (40)
#define PDUR_SrcPduID_HCUDCDC_OjcG_c (41)
#define PDUR_SrcPduID_HCUAPCU_OjcG_c (42)
#define PDUR_SrcPduID_HCUOPCU_OjcG_c (43)
#define PDUR_SrcPduID_HCU3_OjcG_c (44)
#define PDUR_SrcPduID_BMS5_OjcG_c (45)
#define PDUR_SrcPduID_MCU2_OjcG_c (46)
#define PDUR_DstPduID_MCU1_D3_sO0_MCU1_D3_sO0 (0)
#define PDUR_DstPduID_ECMCU_D3_sO0_ECMCU_D3_sO0 (1)
#define PDUR_DstPduID_MCU3_D3_sO0_MCU3_D3_sO0 (2)
#define PDUR_DstPduID_MCU21_D3_sO0_MCU21_D3_sO0 (3)
#define PDUR_DstPduID_MCU22_D3_sO0_MCU22_D3_sO0 (4)
#define PDUR_DstPduID_MCU23_D3_sO0_MCU23_D3_sO0 (5)
#define PDUR_DstPduID_DM1MCU_D3_sO0_DM1MCU_D3_sO0 (6)
#define PDUR_DstPduID_DM1MCU2_D3_sO0_DM1MCU2_D3_sO0 (7)
#define PDUR_DstPduID_MCU2_D3_sO0_MCU2_D3_sO0 (8)
#define PDUR_DstPduID_TSC1Mtr_D3_sO0_TSC1Mtr_D3_sO0 (9)
#define PDUR_DstPduID_EEC2HCU_D3_sO0_EEC2HCU_D3_sO0 (10)
#define PDUR_DstPduID_CCVSHCU_D3_sO0_CCVSHCU_D3_sO0 (11)
#define PDUR_DstPduID_TC1_D3_sO0_TC1_D3_sO0 (12)
#define PDUR_DstPduID_TC1Handle_D3_sO0_TC1Handle_D3_sO0 (13)
#define PDUR_DstPduID_ETC1_D3_sO0_ETC1_D3_sO0 (14)
#define PDUR_DstPduID_ETC2_D3_sO0_ETC2_D3_sO0 (15)
#define PDUR_DstPduID_AMT3_D3_sO0_AMT3_D3_sO0 (16)
#define PDUR_DstPduID_HCUMCU_D3_sO0_HCUMCU_D3_sO0 (17)
#define PDUR_DstPduID_HCUMCU2_D3_sO0_HCUMCU2_D3_sO0 (18)
#define PDUR_DstPduID_SC_D3_sO0_SC_D3_sO0 (19)
#define PDUR_DstPduID_TSC1Mtr2_D3_sO0_TSC1Mtr2_D3_sO0 (20)
#define PDUR_DstPduID_MCU_Tx_Data_Voxyrf_MCU_Tx_Data_Voxyrf (21)
#define PDUR_DstPduID_MCU_Rx_Data_2_Voxyrf_MCU_Rx_Data_2_Voxyrf (22)
#define PDUR_DstPduID_MCU_Rx_Data_1_Voxyrf_MCU_Rx_Data_1_Voxyrf (23)
#define PDUR_DstPduID_DCDC_Cmd1_VR82BV_DCDC_Cmd1_VR82BV (24)
#define PDUR_DstPduID_DCDC_Status1_VR82BV_DCDC_Status1_VR82BV (25)
#define PDUR_DstPduID_DCDC_Status2_VR82BV_DCDC_Status2_VR82BV (26)
#define PDUR_DstPduID_DCDC_Status3_VR82BV_DCDC_Status3_VR82BV (27)
#define PDUR_DstPduID_APCU1_OjcG_c_APCU1_OjcG_c (28)
#define PDUR_DstPduID_APCU2_OjcG_c_APCU2_OjcG_c (29)
#define PDUR_DstPduID_DM1APCU_OjcG_c_DM1APCU_OjcG_c (30)
#define PDUR_DstPduID_DCDC1_OjcG_c_DCDC1_OjcG_c (31)
#define PDUR_DstPduID_DM1DCDC_OjcG_c_DM1DCDC_OjcG_c (32)
#define PDUR_DstPduID_DM1OPCU_OjcG_c_DM1OPCU_OjcG_c (33)
#define PDUR_DstPduID_OPCU1_OjcG_c_OPCU1_OjcG_c (34)
#define PDUR_DstPduID_OPCU2_OjcG_c_OPCU2_OjcG_c (35)
#define PDUR_DstPduID_RelayState_OjcG_c_RelayState_OjcG_c (36)
#define PDUR_DstPduID_RelayState2_OjcG_c_RelayState2_OjcG_c (37)
#define PDUR_DstPduID_IMCU1PTU_OjcG_c_IMCU1PTU_OjcG_c (38)
#define PDUR_DstPduID_MECU1Reserved_OjcG_c_MECU1Reserved_OjcG_c (39)
#define PDUR_DstPduID_DM1PTU_OjcG_c_DM1PTU_OjcG_c (40)
#define PDUR_DstPduID_HCUDCDC_OjcG_c_HCUDCDC_OjcG_c (41)
#define PDUR_DstPduID_HCUAPCU_OjcG_c_HCUAPCU_OjcG_c (42)
#define PDUR_DstPduID_HCUOPCU_OjcG_c_HCUOPCU_OjcG_c (43)
#define PDUR_DstPduID_HCU3_OjcG_c_HCU3_OjcG_c (44)
#define PDUR_DstPduID_BMS5_OjcG_c_BMS5_OjcG_c (45)
#define PDUR_DstPduID_MCU2_OjcG_c_MCU2_OjcG_c (46)

#if (STD_ON == PDUR_SUPPORT_MULTICORE)
#define PDUR_PARTITION_SIZE (4U)
#define PDUR_APPLICATION_SIZE (6U)
#endif /* #if (STD_ON == PDUR_SUPPORT_MULTICORE) */

#define PDUR_SUPPORT_DIAG                               (STD_OFF)

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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif /* #ifndef PDUR_CFG_H_ */

