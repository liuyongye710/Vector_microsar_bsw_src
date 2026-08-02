/* PRQA S 2053,0704 EOF */

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
*   Autosar Revision     :
*   Autosar Conf.Variant :
*   SW Version           :
*   Build Version        :
*
*****************************************************************************/

/**
*   @file    Pwm_Cfg.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Pwm MCAL driver.
*
*   @addtogroup Pwm
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "Pwm_Cfg.h"/* PRQA S 0380 */

#define PWM_CFG_C_VENDOR_ID                      176
#define PWM_CFG_C_AR_REL_MAJOR_VER               4
#define PWM_CFG_C_AR_REL_MINOR_VER               4
#define PWM_CFG_C_AR_REL_REV_VER                 0
#define PWM_CFG_C_SW_MAJOR_VER                   3
#define PWM_CFG_C_SW_MINOR_VER                   0
#define PWM_CFG_C_SW_PATCH_VER                   0

#if (PWM_CFG_C_VENDOR_ID != MCAL_VENDOR_ID)
    #error " NON-MATCHED DATA : PWM_CFG_C_VENDOR_ID "
#endif
#if (PWM_CFG_C_AR_REL_MAJOR_VER != MCAL_AR_RELEASE_MAJOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_AR_REL_MAJOR_VER "
#endif
#if (PWM_CFG_C_AR_REL_MINOR_VER != MCAL_AR_RELEASE_MINOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_AR_REL_MINOR_VER "
#endif
#if (PWM_CFG_C_AR_REL_REV_VER != MCAL_AR_RELEASE_REVISION_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_AR_REL_REV_VER "
#endif
#if (PWM_CFG_C_SW_MAJOR_VER != MCAL_SW_MAJOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_SW_MAJOR_VER "
#endif
#if (PWM_CFG_C_SW_MINOR_VER != MCAL_SW_MINOR_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_SW_MINOR_VER "
#endif
#if (PWM_CFG_C_SW_PATCH_VER != MCAL_SW_PATCH_VERSION)
    #error " NON-MATCHED DATA : PWM_CFG_C_SW_PATCH_VER "
#endif

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_TomNotifyTable[PWM_TOM_MAX * PWM_TOM_CHANNEL_MAX];
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_AtomNotifyTable[PWM_ATOM_MAX * PWM_ATOM_CHANNEL_MAX];
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_EmiosNotifyTable[PWM_EMIOS_MAX * PWM_EMIOS_CHANNEL_MAX];
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_EtpuNotifyTable[PWM_ETPU_MAX * PWM_ETPU_CHANNEL_MAX];
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_CoreMapItemType, PWM_CONST)     Pwm_CoreMap[PWM_CHANNEL_NUM];
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
                            
#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
CONST(Pwm_ConfigType, PWM_CONST) Pwm_Config=
{
    .nNum=PWM_CHANNEL_NUM,
    .pPwm_TomNotifyTable=Pwm_TomNotifyTable,
    .pPwm_AtomNotifyTable=Pwm_AtomNotifyTable,
    .pPwm_EmiosNotifyTable=Pwm_EmiosNotifyTable,
    .pPwm_EtpuNotifyTable=Pwm_EtpuNotifyTable,
    .pPwm_CoreMap=Pwm_CoreMap,
    .sPwmChConfigs={
        {
            .nPwmChannelId=0,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=0
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=1,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=1
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=2,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=5
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=3,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=9
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=4,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=14
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=5,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=1,
                .nPwmChIndex=15
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
        {
            .nPwmChannelId=6,
            .ePwmHwIP=PWM_TOM,
            .sHwConfig={
                .nPwmHwIndex=0,
                .nPwmChIndex=14
            },
            .nPwmPeriodDefault=1,
            .nPwmDutycycleDefault=16384,
            .ePwmChannelClass=PWM_VARIABLE_PERIOD,
            .ePwmPolarity=PWM_HIGH,
            .ePwmIdleState=PWM_LOW,
            .pfPwmChannelNotification=NULL_PTR,
            .sCmuClk={
                .TOM_ClkSrc={
                    .ClkSrc=FXClk0,
                }
            },
            .nPwmMaxDutycycle=32768,
        },
    }
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_TomNotifyTable[PWM_TOM_MAX * PWM_TOM_CHANNEL_MAX]=
{
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=6},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=1},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=2},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=3},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=4},
    {.pNotification=NULL_PTR,.nPwmChannelId=5},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_AtomNotifyTable[PWM_ATOM_MAX * PWM_ATOM_CHANNEL_MAX]=
{
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_EmiosNotifyTable[PWM_EMIOS_MAX * PWM_EMIOS_CHANNEL_MAX]=
{
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_NotifyTableItemType, PWM_CONST) Pwm_EtpuNotifyTable[PWM_ETPU_MAX * PWM_ETPU_CHANNEL_MAX]=
{
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
    {.pNotification=NULL_PTR,.nPwmChannelId=0},
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#define PWM_START_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"
static CONST(Pwm_CoreMapItemType, PWM_CONST) Pwm_CoreMap[PWM_CHANNEL_NUM]=
{
    {
        .nPwmChannelId=0,
        .nCoreId=4
    },
    {
        .nPwmChannelId=1,
        .nCoreId=4
    },
    {
        .nPwmChannelId=2,
        .nCoreId=4
    },
    {
        .nPwmChannelId=3,
        .nCoreId=4
    },
    {
        .nPwmChannelId=4,
        .nCoreId=4
    },
    {
        .nPwmChannelId=5,
        .nCoreId=4
    },
    {
        .nPwmChannelId=6,
        .nCoreId=4
    },
};
#define PWM_STOP_SEC_CONFIG_DATA
#include "Pwm_MemMap.h"

#ifdef __cplusplus
}
#endif
