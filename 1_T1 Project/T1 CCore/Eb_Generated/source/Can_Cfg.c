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
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/
/* PRQA S 0704, 0380, 2053, 1258, 0311 EOF */
/**
*   @file    Can_Cfg.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "Can.h"

#define CAN_CFG_C_VENDOR_ID                     176
#define CAN_CFG_C_AR_REL_MAJOR_VER              4
#define CAN_CFG_C_AR_REL_MINOR_VER              4
#define CAN_CFG_C_AR_REL_REV_VER                0
#define CAN_CFG_C_SW_MAJOR_VER                  3
#define CAN_CFG_C_SW_MINOR_VER                  0
#define CAN_CFG_C_SW_PATCH_VER                  0

#if (MCAL_VENDOR_ID != CAN_CFG_C_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_CFG_C_VENDOR_ID "
#endif
#if (MCAL_AR_RELEASE_MAJOR_VERSION != CAN_CFG_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_AR_REL_MAJOR_VER "
#endif
#if (MCAL_AR_RELEASE_MINOR_VERSION != CAN_CFG_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_AR_REL_MINOR_VER "
#endif
#if (MCAL_AR_RELEASE_REVISION_VERSION != CAN_CFG_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_AR_REL_REV_VER "
#endif
#if (MCAL_SW_MAJOR_VERSION != CAN_CFG_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_SW_MAJOR_VER "
#endif
#if (MCAL_SW_MINOR_VERSION != CAN_CFG_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_SW_MINOR_VER "
#endif
#if (MCAL_SW_PATCH_VERSION != CAN_CFG_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_CFG_C_SW_PATCH_VER "
#endif

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_hwObject, CAN_CONST) Mcan_HardWareObjConfigs[CAN_MB_COUNT] = 
{
    {
        .CanObjectId = 0U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_RANGE_ID,
        .filterCode = 0x00000302U,
        .filterMask = 0x00000304U,
    },
    {
        .CanObjectId = 1U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x18ff6503U,
        .filterMask = 0x1fffffffU,
    },
    {
        .CanObjectId = 2U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x18fef127U,
        .filterMask = 0x1fffffffU,
    },
    {
        .CanObjectId = 3U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x0cf00327U,
        .filterMask = 0x0cf00203U,
    },
    {
        .CanObjectId = 4U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x18f00503U,
        .filterMask = 0x18ff0227U,
    },
    {
        .CanObjectId = 5U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x0bff0527U,
        .filterMask = 0x0bff9327U,
    },
    {
        .CanObjectId = 6U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_RANGE_ID,
        .filterCode = 0x0c002703U,
        .filterMask = 0x0c010327U,
    },
    {
        .CanObjectId = 7U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 0U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x18daeff1U,
        .filterMask = 0x1fffffffU,
    },
    {
        .CanObjectId = 8U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 1U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x18dbeff1U,
        .filterMask = 0x1fffffffU,
    },
    {
        .CanObjectId = 9U,
        .CanControllerId = (uint32)3U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 2U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x000007a0U,
        .filterMask = 0x000007ffU,
    },
    {
        .CanObjectId = 10U,
        .CanControllerId = (uint32)3U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 3U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x000007faU,
        .filterMask = 0x000007ffU,
    },
    {
        .CanObjectId = 11U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x18ff0627U,
        .filterMask = 0x18ff0727U,
    },
    {
        .CanObjectId = 12U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x18ff0827U,
        .filterMask = 0x18ff0f27U,
    },
    {
        .CanObjectId = 13U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = MCAN_STORE_RX_FIFO0,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = RECEIVE,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterCode = 0x18ff3af3U,
        .filterMask = 0x18ffdfefU,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 0U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 1U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 2U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 3U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 4U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 5U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 6U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 7U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 8U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 14U,
        .CanControllerId = (uint32)0U,
        .CanIdType = STANDARD_ID,
        .mbIdex = 9U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 0U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 1U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 2U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 3U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 4U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 5U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 6U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 7U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 8U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 15U,
        .CanControllerId = (uint32)2U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 9U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 0U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 1U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 2U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 3U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 4U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 5U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 6U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 7U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 8U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 16U,
        .CanControllerId = (uint32)3U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 9U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 0U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 1U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 2U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 3U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 4U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 5U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 6U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 7U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 8U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
    {
        .CanObjectId = 17U,
        .CanControllerId = (uint32)4U,
        .CanIdType = EXTENDED_ID,
        .mbIdex = 9U,
        .mbPayloadLength = (uint32)8U,
        .isPolling = 0U,
        .CanObjectType = TRANSMIT,
        .CanFdPaddingValue = 0x00U,
        .PeriodIndex = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterCode = 0x00000000U,
        .filterMask = 0x00000000U,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(McanControlInfor, CAN_CONST) MCAN_CTRL[12U] =
{
    {
        .CanId = 0U,
        .IsUsed = TRUE,
        .BaseWord = 0UL,
        .mram_size_words = 169UL,
    },
    {
        .CanId = 1U,
        .IsUsed = FALSE,
        .BaseWord = 169UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 2U,
        .IsUsed = FALSE,
        .BaseWord = 169UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 3U,
        .IsUsed = FALSE,
        .BaseWord = 169UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 4U,
        .IsUsed = TRUE,
        .BaseWord = 0UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 5U,
        .IsUsed = FALSE,
        .BaseWord = 0UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 6U,
        .IsUsed = FALSE,
        .BaseWord = 0UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 7U,
        .IsUsed = FALSE,
        .BaseWord = 0UL,
        .mram_size_words = 0UL,
    },
    {
        .CanId = 8U,
        .IsUsed = TRUE,
        .BaseWord = 0UL,
        .mram_size_words = 180UL,
    },
    {
        .CanId = 9U,
        .IsUsed = TRUE,
        .BaseWord = 180UL,
        .mram_size_words = 62UL,
    },
    {
        .CanId = 10U,
        .IsUsed = TRUE,
        .BaseWord = 242UL,
        .mram_size_words = 174UL,
    },
    {
        .CanId = 11U,
        .IsUsed = FALSE,
        .BaseWord = 416UL,
        .mram_size_words = 0UL,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(MCANPartitionConfig, CAN_CONST) MCAN_DATA =
{
    .McanCtrl = (McanControlInfor *)MCAN_CTRL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

/* 
    The final value set to the register is as follows:
    Register NBTP.NBRP = brp - 1
    Register NBTP.NTSEG1 = (prop_seg + phase_seg1) - 1
    Register NBTP.NTSEG2 = phase_seg2 - 1
                             clockFrequency
    BitRate = ----------------------------------------------------
                brp * (1 + (prop_seg + phase_seg1) + phase_seg2)
*/
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(bt_config_canfd_struct, CAN_CONST) TIMCFG_0[1U] =
{
    {
        .baudRateConfigId = 0U,
        .brs_ena = FALSE,
        .fd_ena = FALSE,
        .is_noiso = FALSE,
        .nominal = 
        {
            .brp = 5U,
            .prop_seg = 10U,
            .phase_seg1 = 5U,
            .phase_seg2 = 4U,
            .sjw = 2U,
            .tdc = 0U
        },
        .data =
        {
            .brp = 0U,
            .prop_seg = 0U,
            .phase_seg1 = 0U,
            .phase_seg2 = 0U,
            .sjw = 0U,
            .tdc = 0U,
            .tdc_offset = 0U,
        },
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

/* 
    The final value set to the register is as follows:
    Register NBTP.NBRP = brp - 1
    Register NBTP.NTSEG1 = (prop_seg + phase_seg1) - 1
    Register NBTP.NTSEG2 = phase_seg2 - 1
                             clockFrequency
    BitRate = ----------------------------------------------------
                brp * (1 + (prop_seg + phase_seg1) + phase_seg2)
*/
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(bt_config_canfd_struct, CAN_CONST) TIMCFG_1[1U] =
{
    {
        .baudRateConfigId = 0U,
        .brs_ena = FALSE,
        .fd_ena = FALSE,
        .is_noiso = FALSE,
        .nominal = 
        {
            .brp = 5U,
            .prop_seg = 10U,
            .phase_seg1 = 5U,
            .phase_seg2 = 4U,
            .sjw = 2U,
            .tdc = 0U
        },
        .data =
        {
            .brp = 0U,
            .prop_seg = 0U,
            .phase_seg1 = 0U,
            .phase_seg2 = 0U,
            .sjw = 0U,
            .tdc = 0U,
            .tdc_offset = 0U,
        },
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

/* 
    The final value set to the register is as follows:
    Register NBTP.NBRP = brp - 1
    Register NBTP.NTSEG1 = (prop_seg + phase_seg1) - 1
    Register NBTP.NTSEG2 = phase_seg2 - 1
                             clockFrequency
    BitRate = ----------------------------------------------------
                brp * (1 + (prop_seg + phase_seg1) + phase_seg2)
*/
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(bt_config_canfd_struct, CAN_CONST) TIMCFG_2[1U] =
{
    {
        .baudRateConfigId = 0U,
        .brs_ena = FALSE,
        .fd_ena = FALSE,
        .is_noiso = FALSE,
        .nominal = 
        {
            .brp = 5U,
            .prop_seg = 10U,
            .phase_seg1 = 5U,
            .phase_seg2 = 4U,
            .sjw = 2U,
            .tdc = 0U
        },
        .data =
        {
            .brp = 0U,
            .prop_seg = 0U,
            .phase_seg1 = 0U,
            .phase_seg2 = 0U,
            .sjw = 0U,
            .tdc = 0U,
            .tdc_offset = 0U,
        },
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

/* 
    The final value set to the register is as follows:
    Register NBTP.NBRP = brp - 1
    Register NBTP.NTSEG1 = (prop_seg + phase_seg1) - 1
    Register NBTP.NTSEG2 = phase_seg2 - 1
                             clockFrequency
    BitRate = ----------------------------------------------------
                brp * (1 + (prop_seg + phase_seg1) + phase_seg2)
*/
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(bt_config_canfd_struct, CAN_CONST) TIMCFG_3[1U] =
{
    {
        .baudRateConfigId = 0U,
        .brs_ena = FALSE,
        .fd_ena = FALSE,
        .is_noiso = FALSE,
        .nominal = 
        {
            .brp = 5U,
            .prop_seg = 10U,
            .phase_seg1 = 5U,
            .phase_seg2 = 4U,
            .sjw = 2U,
            .tdc = 0U
        },
        .data =
        {
            .brp = 0U,
            .prop_seg = 0U,
            .phase_seg1 = 0U,
            .phase_seg2 = 0U,
            .sjw = 0U,
            .tdc = 0U,
            .tdc_offset = 0U,
        },
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

/* 
    The final value set to the register is as follows:
    Register NBTP.NBRP = brp - 1
    Register NBTP.NTSEG1 = (prop_seg + phase_seg1) - 1
    Register NBTP.NTSEG2 = phase_seg2 - 1
                             clockFrequency
    BitRate = ----------------------------------------------------
                brp * (1 + (prop_seg + phase_seg1) + phase_seg2)
*/
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(bt_config_canfd_struct, CAN_CONST) TIMCFG_4[1U] =
{
    {
        .baudRateConfigId = 0U,
        .brs_ena = FALSE,
        .fd_ena = FALSE,
        .is_noiso = FALSE,
        .nominal = 
        {
            .brp = 5U,
            .prop_seg = 10U,
            .phase_seg1 = 5U,
            .phase_seg2 = 4U,
            .sjw = 2U,
            .tdc = 0U
        },
        .data =
        {
            .brp = 0U,
            .prop_seg = 0U,
            .phase_seg1 = 0U,
            .phase_seg2 = 0U,
            .sjw = 0U,
            .tdc = 0U,
            .tdc_offset = 0U,
        },
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_id_table_t, CAN_CONST) filter_ids_config_0[1U] =
{
    {
        .id1 = 0x00000302U,
        .id2 = 0x00000304U,
        .filterType = FILTER_TYPE_RANGE_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = FALSE,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_filter_config_t, CAN_CONST) RX_FILTER_CFG_0 =
{
    .filterconfigs = filter_ids_config_0,
    .std_filters = 1U,
    .ext_filters = 0U,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"
#define RX_FILTER_CFG_1 NULL_PTR

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_id_table_t, CAN_CONST) filter_ids_config_2[6U] =
{
    {
        .id1 = 0x18ff6503U,
        .id2 = 0x1fffffffU,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x18fef127U,
        .id2 = 0x1fffffffU,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x0cf00327U,
        .id2 = 0x0cf00203U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x18f00503U,
        .id2 = 0x18ff0227U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x0bff0527U,
        .id2 = 0x0bff9327U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x0c002703U,
        .id2 = 0x0c010327U,
        .filterType = FILTER_TYPE_RANGE_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_filter_config_t, CAN_CONST) RX_FILTER_CFG_2 =
{
    .filterconfigs = filter_ids_config_2,
    .std_filters = 0U,
    .ext_filters = 6U,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_id_table_t, CAN_CONST) filter_ids_config_3[4U] =
{
    {
        .id1 = 0x18daeff1U,
        .id2 = 0U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_BUFF,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x18dbeff1U,
        .id2 = 1U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_BUFF,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x000007a0U,
        .id2 = 2U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_BUFF,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = FALSE,
    },
    {
        .id1 = 0x000007faU,
        .id2 = 3U,
        .filterType = FILTER_TYPE_CLASIC,
        .filterConfig = FILTER_CONF_RX_BUFF,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = FALSE,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_filter_config_t, CAN_CONST) RX_FILTER_CFG_3 =
{
    .filterconfigs = filter_ids_config_3,
    .std_filters = 2U,
    .ext_filters = 2U,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_id_table_t, CAN_CONST) filter_ids_config_4[3U] =
{
    {
        .id1 = 0x18ff0627U,
        .id2 = 0x18ff0727U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x18ff0827U,
        .id2 = 0x18ff0f27U,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
    {
        .id1 = 0x18ff3af3U,
        .id2 = 0x18ffdfefU,
        .filterType = FILTER_TYPE_DUAL_ID,
        .filterConfig = FILTER_CONF_RX_FIFO0,
        .ssync = 0UL,
        .esync = 0UL,
        .isExtendedFrame = TRUE,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_filter_config_t, CAN_CONST) RX_FILTER_CFG_4 =
{
    .filterconfigs = filter_ids_config_4,
    .std_filters = 0U,
    .ext_filters = 3U,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_fifo_config_t, CAN_CONST) RX_FIFO_CFG_0 =
{
    .rx_fifo_needed = MCAN_RXFIFO_0_ENABLE,
    .modeFIFO = FIFO_MODE_OVERWRITE,
    .fifo_size_elems = 32U,
    .fifo_watermark = 16U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_fifo_config_t, CAN_CONST) RX_FIFO_CFG_1 =
{
    .rx_fifo_needed = MCAN_RXFIFO_DISABLED,
    .modeFIFO = FIFO_MODE_OVERWRITE,
    .fifo_size_elems = 0U,
    .fifo_watermark = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_fifo_config_t, CAN_CONST) RX_FIFO_CFG_2 =
{
    .rx_fifo_needed = MCAN_RXFIFO_0_ENABLE,
    .modeFIFO = FIFO_MODE_OVERWRITE,
    .fifo_size_elems = 32U,
    .fifo_watermark = 16U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_fifo_config_t, CAN_CONST) RX_FIFO_CFG_3 =
{
    .rx_fifo_needed = MCAN_RXFIFO_DISABLED,
    .modeFIFO = FIFO_MODE_OVERWRITE,
    .fifo_size_elems = 0U,
    .fifo_watermark = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_fifo_config_t, CAN_CONST) RX_FIFO_CFG_4 =
{
    .rx_fifo_needed = MCAN_RXFIFO_0_ENABLE,
    .modeFIFO = FIFO_MODE_OVERWRITE,
    .fifo_size_elems = 32U,
    .fifo_watermark = 16U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_global_filter_config_t, CAN_CONST) GLOBAL_FILTER_CFG_0 =
{
    .anfe = REJECT_NON_MATCHING_FRAMES,
    .anfs = REJECT_NON_MATCHING_FRAMES,
    .rrfe = TRUE,
    .rrfs = TRUE,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_global_filter_config_t, CAN_CONST) GLOBAL_FILTER_CFG_1 =
{
    .anfe = REJECT_NON_MATCHING_FRAMES,
    .anfs = REJECT_NON_MATCHING_FRAMES,
    .rrfe = TRUE,
    .rrfs = TRUE,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_global_filter_config_t, CAN_CONST) GLOBAL_FILTER_CFG_2 =
{
    .anfe = REJECT_NON_MATCHING_FRAMES,
    .anfs = REJECT_NON_MATCHING_FRAMES,
    .rrfe = TRUE,
    .rrfs = TRUE,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_global_filter_config_t, CAN_CONST) GLOBAL_FILTER_CFG_3 =
{
    .anfe = REJECT_NON_MATCHING_FRAMES,
    .anfs = REJECT_NON_MATCHING_FRAMES,
    .rrfe = TRUE,
    .rrfs = TRUE,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_global_filter_config_t, CAN_CONST) GLOBAL_FILTER_CFG_4 =
{
    .anfe = REJECT_NON_MATCHING_FRAMES,
    .anfs = REJECT_NON_MATCHING_FRAMES,
    .rrfe = TRUE,
    .rrfs = TRUE,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_tx_buffer_config_t, CAN_CONST) TX_BUFFER_CFG_0 =
{
    .FIFO_true_QUEUE_false = TRUE,
    .fifo_queue_size = 0U,
    .ded_buffers_number = 10U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_dedicated_buffers_config_t, CAN_CONST) RX_BUFFER_CFG_0 =
{
    .rx_buffer_size_elems = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_tx_buffer_config_t, CAN_CONST) TX_BUFFER_CFG_1 =
{
    .FIFO_true_QUEUE_false = TRUE,
    .fifo_queue_size = 0U,
    .ded_buffers_number = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_dedicated_buffers_config_t, CAN_CONST) RX_BUFFER_CFG_1 =
{
    .rx_buffer_size_elems = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_tx_buffer_config_t, CAN_CONST) TX_BUFFER_CFG_2 =
{
    .FIFO_true_QUEUE_false = TRUE,
    .fifo_queue_size = 0U,
    .ded_buffers_number = 10U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_dedicated_buffers_config_t, CAN_CONST) RX_BUFFER_CFG_2 =
{
    .rx_buffer_size_elems = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_tx_buffer_config_t, CAN_CONST) TX_BUFFER_CFG_3 =
{
    .FIFO_true_QUEUE_false = TRUE,
    .fifo_queue_size = 0U,
    .ded_buffers_number = 10U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_dedicated_buffers_config_t, CAN_CONST) RX_BUFFER_CFG_3 =
{
    .rx_buffer_size_elems = 4U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_tx_buffer_config_t, CAN_CONST) TX_BUFFER_CFG_4 =
{
    .FIFO_true_QUEUE_false = TRUE,
    .fifo_queue_size = 0U,
    .ded_buffers_number = 10U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_dedicated_buffers_config_t, CAN_CONST) RX_BUFFER_CFG_4 =
{
    .rx_buffer_size_elems = 0U,
    .payload = MCAN_PAYLOAD_SIZE_8,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_inter_config_t, CAN_CONST) INTER_CFG_0 =
{
    .ir_line0_select = 0x0000060fUL,
    .ir_line1_select = 0x02000000UL,
    .tx_buffer_tran_ir_enable = 0x000003ffUL,
    .tx_buffer_cancel_fin_ir_enable = 0x000003ffUL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_inter_config_t, CAN_CONST) INTER_CFG_1 =
{
    .ir_line0_select = 0x00000000UL,
    .ir_line1_select = 0x02000000UL,
    .tx_buffer_tran_ir_enable = 0x00000000UL,
    .tx_buffer_cancel_fin_ir_enable = 0x00000000UL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_inter_config_t, CAN_CONST) INTER_CFG_2 =
{
    .ir_line0_select = 0x0000060fUL,
    .ir_line1_select = 0x02000000UL,
    .tx_buffer_tran_ir_enable = 0x000003ffUL,
    .tx_buffer_cancel_fin_ir_enable = 0x000003ffUL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_inter_config_t, CAN_CONST) INTER_CFG_3 =
{
    .ir_line0_select = 0x00080600UL,
    .ir_line1_select = 0x02000000UL,
    .tx_buffer_tran_ir_enable = 0x000003ffUL,
    .tx_buffer_cancel_fin_ir_enable = 0x000003ffUL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_inter_config_t, CAN_CONST) INTER_CFG_4 =
{
    .ir_line0_select = 0x0000060fUL,
    .ir_line1_select = 0x02000000UL,
    .tx_buffer_tran_ir_enable = 0x000003ffUL,
    .tx_buffer_cancel_fin_ir_enable = 0x000003ffUL,
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(CANConfig, CAN_CONST) Mcan_ControllerConfigs[CAN_CONTROLLER_COUNT] = 
{
    {
        .controllerId = MCAN_MOD_ID_1,
        .defaultBaudRateId = (uint16)0U,
        .baudRateConfigCount = 1U,
        .data = &MCAN_DATA,
        .timingconfig = TIMCFG_0,
        .globalfilterconfig = &GLOBAL_FILTER_CFG_0,
        #ifdef RX_FILTER_CFG_0
        .filterconfig = RX_FILTER_CFG_0,
        #else
        .filterconfig = &RX_FILTER_CFG_0,
        #endif
        .rxfifoconfig =  &RX_FIFO_CFG_0,
        .txeventconfig = NULL_PTR,
        .txbufferconfig = &TX_BUFFER_CFG_0,
        .rxbufferconfig = &RX_BUFFER_CFG_0,
        .interconfig = &INTER_CFG_0,
        .stampconfig = NULL_PTR,
        .mcanMode = MCAN_NORMAL_MODE,
        .MRAFNotification = NULL_PTR,
        .ErrorNotification = NULL_PTR,
    },
    {
        .controllerId = MCAN_MOD_ID_5,
        .defaultBaudRateId = (uint16)0U,
        .baudRateConfigCount = 1U,
        .data = &MCAN_DATA,
        .timingconfig = TIMCFG_1,
        .globalfilterconfig = &GLOBAL_FILTER_CFG_1,
        #ifdef RX_FILTER_CFG_1
        .filterconfig = RX_FILTER_CFG_1,
        #else
        .filterconfig = &RX_FILTER_CFG_1,
        #endif
        .rxfifoconfig =  &RX_FIFO_CFG_1,
        .txeventconfig = NULL_PTR,
        .txbufferconfig = &TX_BUFFER_CFG_1,
        .rxbufferconfig = &RX_BUFFER_CFG_1,
        .interconfig = &INTER_CFG_1,
        .stampconfig = NULL_PTR,
        .mcanMode = MCAN_NORMAL_MODE,
        .MRAFNotification = NULL_PTR,
        .ErrorNotification = NULL_PTR,
    },
    {
        .controllerId = MCAN_MOD_ID_9,
        .defaultBaudRateId = (uint16)0U,
        .baudRateConfigCount = 1U,
        .data = &MCAN_DATA,
        .timingconfig = TIMCFG_2,
        .globalfilterconfig = &GLOBAL_FILTER_CFG_2,
        #ifdef RX_FILTER_CFG_2
        .filterconfig = RX_FILTER_CFG_2,
        #else
        .filterconfig = &RX_FILTER_CFG_2,
        #endif
        .rxfifoconfig =  &RX_FIFO_CFG_2,
        .txeventconfig = NULL_PTR,
        .txbufferconfig = &TX_BUFFER_CFG_2,
        .rxbufferconfig = &RX_BUFFER_CFG_2,
        .interconfig = &INTER_CFG_2,
        .stampconfig = NULL_PTR,
        .mcanMode = MCAN_NORMAL_MODE,
        .MRAFNotification = NULL_PTR,
        .ErrorNotification = NULL_PTR,
    },
    {
        .controllerId = MCAN_MOD_ID_10,
        .defaultBaudRateId = (uint16)0U,
        .baudRateConfigCount = 1U,
        .data = &MCAN_DATA,
        .timingconfig = TIMCFG_3,
        .globalfilterconfig = &GLOBAL_FILTER_CFG_3,
        #ifdef RX_FILTER_CFG_3
        .filterconfig = RX_FILTER_CFG_3,
        #else
        .filterconfig = &RX_FILTER_CFG_3,
        #endif
        .rxfifoconfig =  &RX_FIFO_CFG_3,
        .txeventconfig = NULL_PTR,
        .txbufferconfig = &TX_BUFFER_CFG_3,
        .rxbufferconfig = &RX_BUFFER_CFG_3,
        .interconfig = &INTER_CFG_3,
        .stampconfig = NULL_PTR,
        .mcanMode = MCAN_NORMAL_MODE,
        .MRAFNotification = NULL_PTR,
        .ErrorNotification = NULL_PTR,
    },
    {
        .controllerId = MCAN_MOD_ID_11,
        .defaultBaudRateId = (uint16)0U,
        .baudRateConfigCount = 1U,
        .data = &MCAN_DATA,
        .timingconfig = TIMCFG_4,
        .globalfilterconfig = &GLOBAL_FILTER_CFG_4,
        #ifdef RX_FILTER_CFG_4
        .filterconfig = RX_FILTER_CFG_4,
        #else
        .filterconfig = &RX_FILTER_CFG_4,
        #endif
        .rxfifoconfig =  &RX_FIFO_CFG_4,
        .txeventconfig = NULL_PTR,
        .txbufferconfig = &TX_BUFFER_CFG_4,
        .rxbufferconfig = &RX_BUFFER_CFG_4,
        .interconfig = &INTER_CFG_4,
        .stampconfig = NULL_PTR,
        .mcanMode = MCAN_NORMAL_MODE,
        .MRAFNotification = NULL_PTR,
        .ErrorNotification = NULL_PTR,
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"


#if (CAN_MULTICORE_ENABLED == STD_ON)
#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
static CONST(mcan_core_map_t, CAN_CONST) Mcan_CoreMap[CAN_CONTROLLER_COUNT] =
{
    {
        .controllerId = MCAN_MOD_ID_1,
        .CoreId = 2U
    },
    {
        .controllerId = MCAN_MOD_ID_5,
        .CoreId = 2U
    },
    {
        .controllerId = MCAN_MOD_ID_9,
        .CoreId = 2U
    },
    {
        .controllerId = MCAN_MOD_ID_10,
        .CoreId = 2U
    },
    {
        .controllerId = MCAN_MOD_ID_11,
        .CoreId = 2U
    },
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"
#endif

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
CONST(Can_ConfigType, CAN_CONST) Can_Config =
{
    .controllerConfig = Mcan_ControllerConfigs,
    .hwObjectConfig = Mcan_HardWareObjConfigs,
    .HwObjCount = CAN_MB_COUNT,
#if (CAN_MULTICORE_ENABLED == STD_ON)
    .coreMap = Mcan_CoreMap
#endif
};
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif
