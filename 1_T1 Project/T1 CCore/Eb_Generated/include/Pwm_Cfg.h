/* PRQA S 2053,0722,1535 EOF */

/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
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
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           :
*   Build Version        :
*
*****************************************************************************/

/**
*   @file    Pwm_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Pwm MCAL driver.
*
*   @addtogroup Pwm
*   @{
*/

#ifndef PWM_CFG_H_
#define PWM_CFG_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "Mcal.h"
#include "Pwm_Emios_LLDriver.h"
#include "StandardTypes.h"



#define PWM_INDEX                                (0U)
#define PWM_CHANNEL_NUM                          (24U)

#define PWM_TOM_MAX                              (5U)
#define PWM_TOM_CHANNEL_MAX                      (16U)

#define PWM_ATOM_MAX                             (9U)
#define PWM_ATOM_CHANNEL_MAX                     (8U)

#define PWM_EMIOS_MAX                            (2U)
#define PWM_EMIOS_CHANNEL_MAX                    (24U)

#define PWM_ETPU_MAX                             (3U)
#define PWM_ETPU_CHANNEL_MAX                     (32U)

typedef uint8 Pwm_IndexType;
typedef uint16 Pwm_ChannelType;
typedef uint32 Pwm_PeriodType;
typedef uint32 Pwm_DutycycleType;

typedef enum
{
    FXClk0 = 0,
    FXClk1,
    FXClk2,
    FXClk3,
    FXClk4
} Pwm_TOM_ClkSrcType;

typedef enum
{
    CMU_CLK0 = 0,
    CMU_CLK1,
    CMU_CLK2,
    CMU_CLK3,
    CMU_CLK4,
    CMU_CLK5,
    CMU_CLK6,
    CMU_CLK7
} Pwm_ATOM_ClkSrcType;

typedef struct{
    CONST(Pwm_TOM_ClkSrcType,      PWM_CONST) ClkSrc;
}Pwm_TOM_ClkType;

typedef struct{
    CONST(Pwm_ATOM_ClkSrcType,     PWM_CONST) ClkSrc;
}Pwm_ATOM_ClkType;

typedef union{
    CONST(Pwm_TOM_ClkType,      PWM_CONST) TOM_ClkSrc;
    CONST(Pwm_ATOM_ClkType,     PWM_CONST) ATOM_ClkSrc;
}Pwm_CmuClkType;

typedef enum
{
    PWM_TOM = 0,
    PWM_ATOM,
    PWM_EMIOS,
    PWM_ETPU
} Pwm_HwIPType;

typedef enum
{
    Bit_16 = 0,
    Bit_24
} Pwm_PrecisionType;

typedef enum
{
    PWM_VARIABLE_PERIOD = 0,
    PWM_FIXED_PERIOD,
    PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

typedef enum
{
    PWM_LOW = 0,
    PWM_HIGH
} Pwm_OutputStateType;

typedef enum
{
    DIV_1 = 1,
    DIV_2,
    DIV_3,
    DIV_4
} Pwm_eMiosPrescalerType;

typedef enum
{
    PWM_ETPU_TCR1 = 0,
    PWM_ETPU_TCR2
} Pwm_EtpuTimeBaseType;

typedef struct{
    CONST(Pwm_ChannelType,             PWM_CONST) nPwmChannelId;
    CONST(uint8,                       PWM_CONST) nCoreId;
}Pwm_CoreMapItemType;

typedef struct{
    CONST(Pwm_eMiosPrescalerType,      PWM_CONST) nPwmeMiosPrescaler;
    CONST(eMIOS_PWM_ModeType,          PWM_CONST) nPwmeMiosMode;
    CONST(eMIOS_UC_CounterBusSelType,  PWM_CONST) nPwmeMiosBus;
    CONST(uint32,                      PWM_CONST) nIdealDutyCycle;
    CONST(uint32,                      PWM_CONST) nDeadtime;
    CONST(uint32,                      PWM_CONST) nOffset;
    CONST(boolean,                     PWM_CONST) nPwmeMiosDmaSwitch;
}Pwm_eMiosChannelConfigType;

typedef struct
{
    CONST(Pwm_IndexType, PWM_CONST) nPwmHwIndex;
    CONST(Pwm_IndexType, PWM_CONST) nPwmChIndex;
} Pwm_HwConfigType;

typedef void (*Pwm_NotifyType)(void);

typedef struct{
    CONST(Pwm_NotifyType,               PWM_CONST) pNotification;
    CONST(Pwm_ChannelType,              PWM_CONST) nPwmChannelId;
}Pwm_NotifyTableItemType;

typedef struct
{
    CONST(Pwm_ChannelType,              PWM_CONST) nPwmChannelId;
    CONST(Pwm_HwIPType,                 PWM_CONST) ePwmHwIP;
    CONST(Pwm_HwConfigType,             PWM_CONST) sHwConfig;
    CONST(Pwm_PeriodType,               PWM_CONST) nPwmPeriodDefault;
    CONST(Pwm_DutycycleType,            PWM_CONST) nPwmDutycycleDefault;
    CONST(Pwm_ChannelClassType,         PWM_CONST) ePwmChannelClass;
    CONST(Pwm_OutputStateType,          PWM_CONST) ePwmPolarity;
    CONST(Pwm_OutputStateType,          PWM_CONST) ePwmIdleState;
    CONST(Pwm_NotifyType,               PWM_CONST) pfPwmChannelNotification;
    CONST(Pwm_eMiosChannelConfigType,   PWM_CONST) sEmiosChannelConfig;
    CONST(Pwm_CmuClkType,               PWM_CONST) sCmuClk;
    CONST(Pwm_EtpuTimeBaseType,         PWM_CONST) eEtpuTimeBase;
    CONST(Pwm_DutycycleType,            PWM_CONST) nPwmMaxDutycycle;
} Pwm_ChConfigType;

typedef struct
{
    CONST(Pwm_IndexType,                        PWM_CONST)      nNum;
    P2CONST(Pwm_NotifyTableItemType, PWM_CONST, PWM_APPL_CONST) pPwm_TomNotifyTable;
    P2CONST(Pwm_NotifyTableItemType, PWM_CONST, PWM_APPL_CONST) pPwm_AtomNotifyTable;
    P2CONST(Pwm_NotifyTableItemType, PWM_CONST, PWM_APPL_CONST) pPwm_EmiosNotifyTable;
    P2CONST(Pwm_NotifyTableItemType, PWM_CONST, PWM_APPL_CONST) pPwm_EtpuNotifyTable;
    P2CONST(Pwm_CoreMapItemType,     PWM_CONST, PWM_APPL_CONST) pPwm_CoreMap;
    CONST(Pwm_ChConfigType,                     PWM_CONST)      sPwmChConfigs[PWM_CHANNEL_NUM];
} Pwm_ChConfigsType;

typedef Pwm_ChConfigsType Pwm_ConfigType;

#define PWM_CFG_H_VENDOR_ID                      176
#define PWM_CFG_H_AR_REL_MAJOR_VER               4
#define PWM_CFG_H_AR_REL_MINOR_VER               4
#define PWM_CFG_H_AR_REL_REV_VER                 0
#define PWM_CFG_H_SW_MAJOR_VER                   3
#define PWM_CFG_H_SW_MINOR_VER                   0
#define PWM_CFG_H_SW_PATCH_VER                   0

#if (PWM_CFG_H_VENDOR_ID != MCAL_VENDOR_ID)
    #error " NON-MATCHED DATA : PWM_CFG_H_VENDOR_ID "
#endif
#if (PWM_CFG_H_AR_REL_MAJOR_VER != MCAL_AR_RELEASE_MAJOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_H_AR_REL_MAJOR_VER "
#endif
#if (PWM_CFG_H_AR_REL_MINOR_VER != MCAL_AR_RELEASE_MINOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_H_AR_REL_MINOR_VER "
#endif
#if (PWM_CFG_H_AR_REL_REV_VER != MCAL_AR_RELEASE_REVISION_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_H_AR_REL_REV_VER "
#endif
#if (PWM_CFG_H_SW_MAJOR_VER != MCAL_SW_MAJOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_H_SW_MAJOR_VER "
#endif
#if (PWM_CFG_H_SW_MINOR_VER != MCAL_SW_MINOR_VERSION)
    #error " NON-MATCHED DATA : PWM_SW_MINOR_VER "
#endif
#if (PWM_CFG_H_SW_PATCH_VER != MCAL_SW_PATCH_VERSION)
    #error " NON-MATCHED DATA : PWM_SW_PATCH_VER "
#endif

#define PWM_PRECOMPILE_SUPPORT                   (STD_OFF)

#define PWM_DEV_ERROR_DETECT                     (STD_ON)
#define PWM_DEINIT_API                           (STD_ON)
#define PWM_SET_DUTY_CYCLE_API                   (STD_ON)
#define PWM_SET_PERIOD_AND_DUTY_API              (STD_ON)
#define PWM_GET_OUTPUT_STATE_API                 (STD_ON)
#define PWM_SET_OUTPUT_TO_IDLE_API               (STD_ON)
#define PWM_VERSION_INFO_API                     (STD_ON)
#define PWM_NOTIFICATION_SUPPORT                 (STD_ON)
#define PWM_DUTYCYCLE_UPDATED_ENDPERIOD          (STD_ON)
#define PWM_DUTY_PERIOD_UPDATED_ENDPERIOD        (STD_ON)
#define PWM_POWER_STATE_SUPPORTED                (STD_ON)
#define PWM_POWER_STATE_ASYNCH_MODE_SUPPORTED    (STD_OFF)

extern CONST(Pwm_ConfigType, PWM_CONST) Pwm_Config;

#define PWM_INLINE    LOCAL_INLINE



//#define PO_eFuPWM1                             ((Pwm_ChannelType) 0U)
//#define PO_eFuPWM2                             ((Pwm_ChannelType) 1U)
//#define PO_eFuPWM3                             ((Pwm_ChannelType) 2U)
//#define PO_eFuPWM4                             ((Pwm_ChannelType) 3U)
//#define PO_eFuPWM5                             ((Pwm_ChannelType) 4U)
//#define PO_PWM_EFN                             ((Pwm_ChannelType) 5U)
//#define PO_PWM_UL                             ((Pwm_ChannelType) 6U)
//#define PO_PWM_VL                             ((Pwm_ChannelType) 7U)
//#define PO_PWM_WL                             ((Pwm_ChannelType) 8U)
//#define PO_PWM_UH                             ((Pwm_ChannelType) 9U)
//#define PO_PWM_VH                             ((Pwm_ChannelType) 10U)
//#define PO_PWM_WH                             ((Pwm_ChannelType) 11U)
//#define PO_PWM_triADC                             ((Pwm_ChannelType) 12U)
//#define PO_PWM_UH2                             ((Pwm_ChannelType) 13U)
//#define PO_PWM_VH2                             ((Pwm_ChannelType) 14U)
//#define PO_PWM_WH2                             ((Pwm_ChannelType) 15U)
//#define PO_PWM_UL2                             ((Pwm_ChannelType) 16U)
//#define PO_PWM_WL2                             ((Pwm_ChannelType) 17U)
//#define PO_PWM_VL2                             ((Pwm_ChannelType) 18U)
//#define PO_PWM2_triADC                             ((Pwm_ChannelType) 19U)
//#define PO_SDCRC                             ((Pwm_ChannelType) 20U)
//#define PO_RTS_EXC                             ((Pwm_ChannelType) 21U)
//#define PO_RTS_EXC_N                             ((Pwm_ChannelType) 22U)
//#define PO_SA7321_WatchDog                             ((Pwm_ChannelType) 23U)
//
//#define PWM_PO_eFuPWM1                             ((Pwm_ChannelType) 0U)
//#define PWM_PO_eFuPWM2                             ((Pwm_ChannelType) 1U)
//#define PWM_PO_eFuPWM3                             ((Pwm_ChannelType) 2U)
//#define PWM_PO_eFuPWM4                             ((Pwm_ChannelType) 3U)
//#define PWM_PO_eFuPWM5                             ((Pwm_ChannelType) 4U)
//#define PWM_PO_PWM_EFN                             ((Pwm_ChannelType) 5U)
//#define PWM_PO_PWM_UL                             ((Pwm_ChannelType) 6U)
//#define PWM_PO_PWM_VL                             ((Pwm_ChannelType) 7U)
//#define PWM_PO_PWM_WL                             ((Pwm_ChannelType) 8U)
//#define PWM_PO_PWM_UH                             ((Pwm_ChannelType) 9U)
//#define PWM_PO_PWM_VH                             ((Pwm_ChannelType) 10U)
//#define PWM_PO_PWM_WH                             ((Pwm_ChannelType) 11U)
//#define PWM_PO_PWM_triADC                             ((Pwm_ChannelType) 12U)
//#define PWM_PO_PWM_UH2                             ((Pwm_ChannelType) 13U)
//#define PWM_PO_PWM_VH2                             ((Pwm_ChannelType) 14U)
//#define PWM_PO_PWM_WH2                             ((Pwm_ChannelType) 15U)
//#define PWM_PO_PWM_UL2                             ((Pwm_ChannelType) 16U)
//#define PWM_PO_PWM_WL2                             ((Pwm_ChannelType) 17U)
//#define PWM_PO_PWM_VL2                             ((Pwm_ChannelType) 18U)
//#define PWM_PO_PWM2_triADC                             ((Pwm_ChannelType) 19U)
//#define PWM_PO_SDCRC                             ((Pwm_ChannelType) 20U)
//#define PWM_PO_RTS_EXC                             ((Pwm_ChannelType) 21U)
//#define PWM_PO_RTS_EXC_N                             ((Pwm_ChannelType) 22U)
//#define PWM_PO_SA7321_WatchDog                             ((Pwm_ChannelType) 23U)

#ifdef __cplusplus
}
#endif

#endif
