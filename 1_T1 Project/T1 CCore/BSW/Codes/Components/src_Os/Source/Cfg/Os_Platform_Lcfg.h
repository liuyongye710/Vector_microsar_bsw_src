/*
********************************************************************************
*
*  File name:	Os_Platform_Lcfg.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef OS_PLATFORM_LCFG_H_
#define OS_PLATFORM_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Types_Cfg.h"
#include "Os_Core_Types.h"
#include "Os_Cfg.h"
#include "Os_Arch_Kernal_Lcfg.h"
#include "Os_Alarm_Types.h"
#include "Os_Counter_Types.h"
#include "Os_App_Types.h"
#include "Os_Task_Types.h"
#include "Os_Isr_Types.h"
#include "Os_Resource_Types.h"
#include "Os_TrustFun_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define OS_SYSTEMAPPLICATION_OSCORE_CORE0_ACCESS      ((uint32)(1U << (SYSTEMAPPLICATION_OSCORE_CORE0)))
#define OS_APP_APPLICATION_CORE0_QM_ACCESS            ((uint32)(1U << (APP_APPLICATION_CORE0_QM)))
#define OS_SYSTEMAPPLICATION_OSCORE_CORE1_ACCESS      ((uint32)(1U << (SYSTEMAPPLICATION_OSCORE_CORE1)))
#define OS_APP_APPLICATION_CORE1_QM_ACCESS            ((uint32)(1U << (APP_APPLICATION_CORE1_QM)))
#define OS_SYSTEMAPPLICATION_OSCORE_CORE2_ACCESS      ((uint32)(1U << (SYSTEMAPPLICATION_OSCORE_CORE2)))
#define OS_APP_APPLICATION_CORE2_QM_ACCESS            ((uint32)(1U << (APP_APPLICATION_CORE2_QM)))
#define OS_CFG_NUM_CAT1ISR_OSCORE0 (4U)
#define OS_CFG_NUM_CAT1ISR_OSCORE1 (1U)
#define OS_CFG_NUM_CAT1ISR_OSCORE2 (0U)
#define OS_CFG_NUM_TASKQUEUES_OSCORE0                 (11U)
#define OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE0       (8U)
#define OS_CFG_SIZE_TASKQUEUE0_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE1_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE2_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE3_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE4_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE5_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE6_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE7_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE8_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE9_OSCORE0                (100U)
#define OS_CFG_SIZE_TASKQUEUE10_OSCORE0               (100U)
#define OS_CFG_NUM_TASKQUEUES_OSCORE1                 (11U)
#define OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE1       (8U)
#define OS_CFG_SIZE_TASKQUEUE0_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE1_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE2_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE3_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE4_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE5_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE6_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE7_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE8_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE9_OSCORE1                (100U)
#define OS_CFG_SIZE_TASKQUEUE10_OSCORE1               (100U)
#define OS_CFG_NUM_TASKQUEUES_OSCORE2                 (13U)
#define OS_CFG_NUM_TASKQUEUES_SYSTEMTIMER_CORE2       (10U)
#define OS_CFG_SIZE_TASKQUEUE0_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE1_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE2_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE3_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE4_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE5_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE6_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE7_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE8_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE9_OSCORE2                (100U)
#define OS_CFG_SIZE_TASKQUEUE10_OSCORE2               (100U)
#define OS_CFG_SIZE_TASKQUEUE11_OSCORE2               (100U)
#define OS_CFG_SIZE_TASKQUEUE12_OSCORE2               (100U)
#define OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE0     (1U)
#define OS_TICKS2NS_SYSTEMTIMER_CORE0(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE0* 1000000.0))
#define OS_TICKS2US_SYSTEMTIMER_CORE0(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE0 * 1000))
#define OS_TICKS2MS_SYSTEMTIMER_CORE0(x)              ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE0 * 1.0))
#define OS_TICKS2SEC_SYSTEMTIMER_CORE0(x)             ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE0 / 1000.0))
#define OS_OSSECONDSPERTICK_HRT_OS_MONITOR_COUNTER    (1000U)
#define OS_TICKS2NS_OS_MONITOR_COUNTER(x)             ((PhysicalTimeType) (((uint64)(x)) * 1000000000.0 / OS_OSSECONDSPERTICK_HRT_OS_MONITOR_COUNTER))
#define OS_TICKS2US_OS_MONITOR_COUNTER(x)             ((PhysicalTimeType) (((uint64)(x)) * 1000000.0 / OS_OSSECONDSPERTICK_HRT_OS_MONITOR_COUNTER))
#define OS_TICKS2MS_OS_MONITOR_COUNTER(x)             ((PhysicalTimeType) (((uint64)(x)) * 1000 / OS_OSSECONDSPERTICK_HRT_OS_MONITOR_COUNTER))
#define OS_TICKS2SEC_OS_MONITOR_COUNTER(x)            ((PhysicalTimeType) (((uint32)(x)) * 1.0 / OS_OSSECONDSPERTICK_HRT_OS_MONITOR_COUNTER))
#define OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE1     (1U)
#define OS_TICKS2NS_SYSTEMTIMER_CORE1(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE1* 1000000.0))
#define OS_TICKS2US_SYSTEMTIMER_CORE1(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE1 * 1000))
#define OS_TICKS2MS_SYSTEMTIMER_CORE1(x)              ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE1 * 1.0))
#define OS_TICKS2SEC_SYSTEMTIMER_CORE1(x)             ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE1 / 1000.0))
#define OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE2     (1U)
#define OS_TICKS2NS_SYSTEMTIMER_CORE2(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE2* 1000000.0))
#define OS_TICKS2US_SYSTEMTIMER_CORE2(x)              ((PhysicalTimeType) (((uint64)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE2 * 1000))
#define OS_TICKS2MS_SYSTEMTIMER_CORE2(x)              ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE2 * 1.0))
#define OS_TICKS2SEC_SYSTEMTIMER_CORE2(x)             ((PhysicalTimeType) (((uint32)(x)) * OS_OSSECONDSPERTICK_PIT_SYSTEMTIMER_CORE2 / 1000.0))
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/*
********************************************************************************
*    Global Variable
********************************************************************************
*/
extern const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core0;
extern const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core0;
extern const Os_IsrCfgType OsCfg_Isr_Os_Monitor_Isr;
extern const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core1;
extern const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core1;
extern const Os_IsrCfgType OsCfg_Isr_CounterIsr_SystemTimer_Core2;
extern const Os_IsrCfgType OsCfg_Isr_MultiCommIsr_OsCore_Core2;
extern const Os_IsrCfgType OsCfg_Isr_FlashDone_Isr;
extern const Os_IsrCfgType OsCfg_Isr_PIT0_CH4;
extern const Os_IsrCfgType OsCfg_Isr_PIT0_CH5;
extern const Os_IsrCfgType OsCfg_Isr_PIT0_CH6;
extern const Os_IsrCfgType OsCfg_Isr_Can1_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Can2_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Can3_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Can4_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp0_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp1_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp2_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp3_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp4_Isr;
extern const Os_IsrCfgType OsCfg_Isr_Adc89_Grp5_Isr;
extern const Os_SchedulerCfgType OsCfg_Scheduler_OsCore0;
extern const Os_SchedulerCfgType OsCfg_Scheduler_OsCore1;
extern const Os_SchedulerCfgType OsCfg_Scheduler_OsCore2;
extern const Os_SystemCfgType Os_SystemCfgData;
extern const Os_CoreCfgType* Os_CoreCfgData[OS_COREID_COUNT + 1];
extern const Os_AppCfgType* Os_AppCfgData[OS_APPID_COUNT + 1];
extern const Os_TaskCfgType* Os_TaskCfgData[OS_TASKID_COUNT + 1];
extern const Os_IsrCfgType* Os_IsrCfgData[OS_ISRID_COUNT + 1];
extern const Os_AlarmCfgType* Os_AlarmCfgData[OS_ALARMID_COUNT + 1];
extern const Os_CounterBaseCfgType* Os_CounterCfgData[OS_COUNTERID_COUNT + 1];
extern const Os_SpinlockCfgType* Os_SpinlockCfgData[OS_SPINLOCKID_COUNT + 1];
extern const Os_ResourceCfgType* Os_ResourceCfgData[OS_RESOURCEID_COUNT + 1];
extern const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore0[OS_CFG_NUM_CAT1ISR_OSCORE0 + 1];
extern const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore1[OS_CFG_NUM_CAT1ISR_OSCORE1 + 1];
extern const Os_IsrCat1CfgType* Os_Cat1IsrCfgData_OsCore2[OS_CFG_NUM_CAT1ISR_OSCORE2 + 1];
extern const uint32 _start;
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
#if(OS_CFG_STARTUPHOOK_SYSTEM == STD_ON)
extern void StartupHook(void);
#endif

#if(OS_CFG_ERRORHOOK_SYSTEM == STD_ON)
extern void ErrorHook(StatusType Error);
#endif

#if(OS_CFG_SHUTDOWNHOOK_SYSTEM == STD_ON)
extern void ShutdownHook(StatusType Fatalerror);
#endif

#if(OS_CFG_PROTECTIONHOOK_SYSTEM == STD_ON)
extern ProtectionReturnType ProtectionHook(StatusType Fatalerror);
#endif



#endif /* OS_PLATFORM_LCFG_H_ */


