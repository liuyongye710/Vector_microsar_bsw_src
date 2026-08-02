/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : CAN
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Can_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifndef CAN_CFG_H_
#define CAN_CFG_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "StandardTypes.h"
#include "Mcal.h"

#define CAN_CFG_H_VENDOR_ID                     176
#define CAN_CFG_H_AR_REL_MAJOR_VER              4
#define CAN_CFG_H_AR_REL_MINOR_VER              4
#define CAN_CFG_H_AR_REL_REV_VER                0
#define CAN_CFG_H_SW_MAJOR_VER                  3
#define CAN_CFG_H_SW_MINOR_VER                  0
#define CAN_CFG_H_SW_PATCH_VER                  0

#if (MCAL_VENDOR_ID != CAN_CFG_H_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_CFG_H_VENDOR_ID "
#endif
#if (MCAL_AR_RELEASE_MAJOR_VERSION != CAN_CFG_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_AR_REL_MAJOR_VER "
#endif
#if (MCAL_AR_RELEASE_MINOR_VERSION != CAN_CFG_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_AR_REL_MINOR_VER "
#endif
#if (MCAL_AR_RELEASE_REVISION_VERSION != CAN_CFG_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_AR_REL_REV_VER "
#endif
#if (MCAL_SW_MAJOR_VERSION != CAN_CFG_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_SW_MAJOR_VER "
#endif
#if (MCAL_SW_MINOR_VERSION != CAN_CFG_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_SW_MINOR_VER "
#endif
#if (MCAL_SW_PATCH_VERSION != CAN_CFG_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_CFG_H_SW_PATCH_VER "
#endif


#define CAN_PRECOMPILE_SUPPORT    (STD_OFF)

#define CAN_MULTICORE_ENABLED    (STD_OFF)

#define CAN_CHECK_WAKEUP_API    (STD_OFF)

#define CAN_FD_MODE_ENABLE    (STD_OFF)

#define CAN_DEV_ERROR_DETECT    (STD_OFF)

#define CAN_VERSION_INFO_API    (STD_OFF)

#define CAN_INSTANCE    (0U)

#define CAN_MAINFUNCTION_BUSOFF_PERIOD    (0U)

#define CAN_MAINFUNCTION_MODE_PERIOD    (0U)

#define CAN_MAINFUNCTION_WAKEUP_PERIOD    (0U)

#define CAN_MULTIPLEXED_TRANSMISSION    (STD_ON)

#define CAN_SET_BAUDRATE_API    (STD_OFF)

#define CAN_MAINFUNCTION_BUSOFF_API    (STD_OFF)
#define CAN_MAINFUNCTION_WAKEUP_API    (STD_OFF)
#define CAN_WAKEUP_SUPPORT    (STD_OFF)
/* The unit is us. */
#define CAN_TIMEOUT_DURATION    1000000U

#define CAN_MULTIPLE_READ_PERIOD   (STD_ON)
#define CAN_MULTIPLE_WRITE_PERIOD  (STD_ON)
#define CAN_CONTROLLER_COUNT    5U
#define CAN_MAINFUNCTION_WRITE_API    (STD_OFF)
#define CAN_MAINFUNCTION_READ_API    (STD_OFF)
#define CAN_TRIGGER_TRANSMIT_EN    (STD_OFF)

#define CAN_INLINE    LOCAL_INLINE

#define CAN_MB_COUNT       54U
#define CAN_HOH_CNT_MAX    18U
#define CAN_DEFAULT_COREID 2U

#define DCDC_Status_CAN0    0U  /* RECEIVE object of Controller Id 0 */
#define AMT3_CAN2    1U  /* RECEIVE object of Controller Id 2 */
#define CCVSHCU_CAN2    2U  /* RECEIVE object of Controller Id 2 */
#define EEC2HCU_ETC1_CAN2    3U  /* RECEIVE object of Controller Id 2 */
#define ETC2_SC_CAN2    4U  /* RECEIVE object of Controller Id 2 */
#define HCUMCU_CAN2    5U  /* RECEIVE object of Controller Id 2 */
#define TC_TSC_CAN2    6U  /* RECEIVE object of Controller Id 2 */
#define MCU_Rx_Data_1_CAN3    7U  /* RECEIVE object of Controller Id 3 */
#define MCU_Rx_Data_2_CAN3    8U  /* RECEIVE object of Controller Id 3 */
#define XCP_Request_CAN3    9U  /* RECEIVE object of Controller Id 3 */
#define GL_Rx_REQ_CAN3    10U  /* RECEIVE object of Controller Id 3 */
#define HCU_OPCU_DCDC_CAN4    11U  /* RECEIVE object of Controller Id 4 */
#define HCU_APCU_3_CAN4    12U  /* RECEIVE object of Controller Id 4 */
#define BMS5_MCU2_CAN4    13U  /* RECEIVE object of Controller Id 4 */
#define TX_CAN0    14U  /* TRANSMIT object of Controller Id 0 */
#define TX_CAN2    15U  /* TRANSMIT object of Controller Id 2 */
#define TX_CAN3    16U  /* TRANSMIT object of Controller Id 3 */
#define TX_CAN4    17U  /* TRANSMIT object of Controller Id 4 */

#define CAN0    0U  /* MCAN_1 */
#define CAN1    1U  /* MCAN_5 */
#define CAN2    2U  /* MCAN_9 */
#define CAN3    3U  /* MCAN_10 */
#define CAN4    4U  /* MCAN_11 */

#define CAN_PB_CONFIG_DECLARATION   extern CONST(Can_ConfigType, CAN_VAR) Can_Config;

#ifdef __cplusplus
}
#endif

#endif /* CAN_CFG_H_ */
