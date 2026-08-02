/* PRQA S 2053, 0380, 1258, 0704,4342 EOF */
/**
*   @file Icu_Cfg.c
*   @version 3.0.0
*
*   @brief   AUTOSAR Icu - contains the configuration data of the ICU driver
*   @details Contains the configuration data of the ICU driver
*
*   @addtogroup ICU_MODULE
*   @{
*/
/**************************************************************************** 
* 
* Copyright (c) 2022  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/

/**
*   @file    Icu_Cfg.c 
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "Icu_Cfg.h"
#include "Icu.h"
#include "Icu_Gtm_Tim_LLDrivers.h"
#include "Icu_eMIOS_HAL_Wrapper.h"
#include "Icu_eMIOS_Wrapper.h"
#include "Icu_eTPU_HAL_Wrapper.h"
#include "Icu_eTPU_Wrapper.h"
#include "eDMA_LLDriver.h"
#include "EcuM_Cbk.h"
#include "Icu_Wkpu_LLDrivers.h"


/*=====================================SOURCE FILE VERSION INFORMATION==============================*/

#define ICU_CFG_VENDOR_ID_C                 176

#define ICU_CFG_AR_MAJOR_VER_C              4
#define ICU_CFG_AR_MINOR_VER_C              4
#define ICU_CFG_AR_PATCH_VER_C              0

#define ICU_CFG_SW_MAJOR_VER_C              3
#define ICU_CFG_SW_MINOR_VER_C              0
#define ICU_CFG_SW_PATCH_VER_C              0

/*============================================FILE VERSION CHECKS===================================*/

#if (ICU_CFG_VENDOR_ID_C != ICU_VENDOR_ID_CFG)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_CFG_AR_MAJOR_VER_C != ICU_AR_RELEASE_MAJOR_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_AR_RELEASE_MAJOR_VERSION_CFG"
#endif
#if (ICU_CFG_AR_MINOR_VER_C != ICU_AR_RELEASE_MINOR_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_AR_RELEASE_MINOR_VERSION_CFG"
#endif
#if (ICU_CFG_AR_PATCH_VER_C != ICU_AR_RELEASE_REVISION_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_AR_RELEASE_REVISION_VERSION_CFG"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_CFG_SW_MAJOR_VER_C != ICU_SW_MAJOR_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VERSION_CFG"
#endif
#if (ICU_CFG_SW_MINOR_VER_C != ICU_SW_MINOR_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VERSION_CFG"
#endif
#if (ICU_CFG_SW_PATCH_VER_C != ICU_SW_PATCH_VERSION_CFG)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VERSION_CFG"
#endif

/*====================================================================================================
                                   EXTERN CALLBACK FUNCTION
====================================================================================================*/




/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/

/*===================================================================================================
*                                       LOCAL MACROS
====================================================================================================*/

/*===================================================================================================
*                                      LOCAL CONSTANTS
====================================================================================================*/

/*===================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
====================================================================================================*/



/******************************************************************************************/
/************************************ eMIOS Config ****************************************/
/******************************************************************************************/
#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
static CONST(ICU_eMIOS_HwConfig, ICU_CONST) IcuHwConfig_eMIOS[2] =
{
    {
        .mode = EMIOS_UC_MODE_SAIC_TRIGGER_EDGE_FALLING,
        .timebase = EMIOS_COUNTER_BUS_INTERNAL,
        .filter = EMIOS_INPUT_FILTER_BYPASS,   /* Input signal filter */
        .desirednum = 0, /* Desired edge/pulse number. used for PEA, QDEC mode */
        .startime = 0, /* Start window time. used for PEC, WPTA */
        .endtime = 0,    /* End window time. used for PEC, WPTA */
        .masterPrescaler = 8,   /* EMios module prescaler */
        .channelPrescaler = 0  /* EMios channel prescaler */
    },  
    {
        .mode = EMIOS_UC_MODE_SAIC_TRIGGER_EDGE_FALLING,
        .timebase = EMIOS_COUNTER_BUS_INTERNAL,
        .filter = EMIOS_INPUT_FILTER_BYPASS,   /* Input signal filter */
        .desirednum = 0, /* Desired edge/pulse number. used for PEA, QDEC mode */
        .startime = 0, /* Start window time. used for PEC, WPTA */
        .endtime = 0,    /* End window time. used for PEC, WPTA */
        .masterPrescaler = 8,   /* EMios module prescaler */
        .channelPrescaler = 0  /* EMios channel prescaler */
    },  
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"

#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
static CONST(ICU_eMIOS_ChannelConfig, ICU_CONST) eMiosChannelConfig[2] =
{
    {
        .IcuConfig_Instance = 0,
        .IcuConfig_ModuleId = (Icu_Module_Type)eMIOS_0,
        .IcuConfig_ChannelId = (Icu_ChannelType)EMIOS_BALLS_CHANNEL_6,
        .IcuConfig_ChannelMode = ICU_MODE_EDGE_COUNTER,
        .IcuChannel_DefaultStartEdge = ICU_FALLING_EDGE,
        .IcuChannel_Notification = NULL_PTR,
        .IcuChannel_TimestampNotification = NULL_PTR,
        .IcuChannel_OverflowNotification = NULL_PTR,
        .IcuChannel_SignalMeasurementProperty = (Icu_SignalMeasurementPropertyType)0U,
        .IcuChannel_TimestampBufferProperty = (Icu_TimestampBufferType)0U,
        .IcuChannel_WakeupCapability = (boolean)FALSE, /* Wakeup capability */
    #if(ICU_REPORT_WAKEUP_SOURCE == STD_ON)
        .IcuChannel_WakeupValue = (EcuM_WakeupSourceType)ICU_NONE_ECUM_WAKEUP_SOURCE_REF, /* None Wakeup Source was referred */
    #endif /* (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
        /* eMios config flag */
        .IcuChannel_bDmaSupport = (boolean)FALSE,
        .IcuChannel_DmaChannel = (uint8)0,
        .IcuChannel_bSignalMeasureWithoutInterrupt = (boolean)FALSE,
        .pIcuConfig_HwConfig = &IcuHwConfig_eMIOS[0]
    },
    {
        .IcuConfig_Instance = 1,
        .IcuConfig_ModuleId = (Icu_Module_Type)eMIOS_0,
        .IcuConfig_ChannelId = (Icu_ChannelType)EMIOS_BALLS_CHANNEL_7,
        .IcuConfig_ChannelMode = ICU_MODE_EDGE_COUNTER,
        .IcuChannel_DefaultStartEdge = ICU_FALLING_EDGE,
        .IcuChannel_Notification = NULL_PTR,
        .IcuChannel_TimestampNotification = NULL_PTR,
        .IcuChannel_OverflowNotification = NULL_PTR,
        .IcuChannel_SignalMeasurementProperty = (Icu_SignalMeasurementPropertyType)0U,
        .IcuChannel_TimestampBufferProperty = (Icu_TimestampBufferType)0U,
        .IcuChannel_WakeupCapability = (boolean)FALSE, /* Wakeup capability */
    #if(ICU_REPORT_WAKEUP_SOURCE == STD_ON)
        .IcuChannel_WakeupValue = (EcuM_WakeupSourceType)ICU_NONE_ECUM_WAKEUP_SOURCE_REF, /* None Wakeup Source was referred */
    #endif /* (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
        /* eMios config flag */
        .IcuChannel_bDmaSupport = (boolean)FALSE,
        .IcuChannel_DmaChannel = (uint8)0,
        .IcuChannel_bSignalMeasureWithoutInterrupt = (boolean)FALSE,
        .pIcuConfig_HwConfig = &IcuHwConfig_eMIOS[1]
    },
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"

#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
CONST(ICU_eMIOS_Config, ICU_CONST) Icu_eMoisConfig =
{
    .uChannelCount = 2U,
    .peMiosChannelConfig = eMiosChannelConfig
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"










/******************************************************************************************/
/************************************ Hardware Map ****************************************/
/******************************************************************************************/
#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
static CONST(ICU_HwModule_Type, ICU_CONST) Icu_HwChMap[2] =
{
    ICU_eMIOS_0,
    ICU_eMIOS_0,
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"


#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
static CONST(Icu_CoreMapItemType, ICU_CONST) Icu_CoreMap[2] =
{
    {
        .nIcuChannelId=0,
        .nCoreId=4
    },
    {
        .nIcuChannelId=1,
        .nCoreId=4
    },
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"

/******************************************************************************************/
/************************************* ICU Config *****************************************/
/******************************************************************************************/

#define ICU_START_SEC_CONFIG_DATA
#include "Icu_MemMap.h"
CONST(Icu_ConfigType, ICU_CONST) Icu_Cfg =
{
    .Icu_NumChannels    = 2U,
    .Icu_GtmConfig      = NULL_PTR,
    .Icu_eMoisConfig    = &Icu_eMoisConfig,
    .Icu_eTpuConfig     = NULL_PTR,
    .Icu_WkpuConfig     = NULL_PTR,
    .Icu_HwChMap        = &Icu_HwChMap,
    .Icu_CoreMap        = Icu_CoreMap
};
#define ICU_STOP_SEC_CONFIG_DATA
#include "Icu_MemMap.h"

