/*
********************************************************************************
*
*  File name:	Os_Arch_Kernal_Lcfg.c
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
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Types.h"
#include "Os_Arch_Kernal_Lcfg.h"
#include "Os_Arch_Context_Types.h"
#include "Os_Arch_Types.h"
#include "Os_Lcfg.h"
#include "Os_Task.h"
#include "Os_Isr.h"
#include "Os_MultiCore.h"
#include "Os_Arch_Mach_MP_Types.h"
#include "Os_Arch_Mach_Timer.h"
#include "Os_TmProtection.h"
#include "Os_MemMap.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/

#define OS_START_SEC_STACK_OSCORE0 
#include "Os_MemMap.h"
Os_Stack_Address OsCfg_Arch_Stack_Kernal_OsCore0 [OS_ARCH_KERNAL_OSCORE0_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Default_Init_Task_Core0[OS_ARCH_DEFAULT_INIT_TASK_CORE0_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Idle_Task_Core0[OS_ARCH_IDLE_TASK_CORE0_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core0[OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE0_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core0[OS_ARCH_MULTICOMMISR_OSCORE_CORE0_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Os_Monitor_Isr[OS_ARCH_OS_MONITOR_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_Init_Core0_QM[OS_ARCH_TASK_INIT_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_10ms_Core0_QM[OS_ARCH_TASK_10MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_20ms_Core0_QM[OS_ARCH_TASK_20MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_50ms_Core0_QM[OS_ARCH_TASK_50MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_100ms_Core0_QM[OS_ARCH_TASK_100MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_200ms_Core0_QM[OS_ARCH_TASK_200MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_500ms_Core0_QM[OS_ARCH_TASK_500MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_1000ms_Core0_QM[OS_ARCH_TASK_1000MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_2ms_Core0_QM[OS_ARCH_TASK_2MS_CORE0_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
#define OS_STOP_SEC_STACK_OSCORE0 
#include "Os_MemMap.h"

#define OS_START_SEC_STACK_OSCORE1 
#include "Os_MemMap.h"
Os_Stack_Address OsCfg_Arch_Stack_Kernal_OsCore1 [OS_ARCH_KERNAL_OSCORE1_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Default_Init_Task_Core1[OS_ARCH_DEFAULT_INIT_TASK_CORE1_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Idle_Task_Core1[OS_ARCH_IDLE_TASK_CORE1_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core1[OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE1_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core1[OS_ARCH_MULTICOMMISR_OSCORE_CORE1_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_Init_Core1_QM[OS_ARCH_TASK_INIT_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_5ms_Core1_QM[OS_ARCH_TASK_5MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_10ms_Core1_QM[OS_ARCH_TASK_10MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_20ms_Core1_QM[OS_ARCH_TASK_20MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_50ms_Core1_QM[OS_ARCH_TASK_50MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_100ms_Core1_QM[OS_ARCH_TASK_100MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_200ms_Core1_QM[OS_ARCH_TASK_200MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_500ms_Core1_QM[OS_ARCH_TASK_500MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_1000ms_Core1_QM[OS_ARCH_TASK_1000MS_CORE1_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
#define OS_STOP_SEC_STACK_OSCORE1 
#include "Os_MemMap.h"

#define OS_START_SEC_STACK_OSCORE2 
#include "Os_MemMap.h"
Os_Stack_Address OsCfg_Arch_Stack_Kernal_OsCore2 [OS_ARCH_KERNAL_OSCORE2_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Default_Init_Task_Core2[OS_ARCH_DEFAULT_INIT_TASK_CORE2_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Idle_Task_Core2[OS_ARCH_IDLE_TASK_CORE2_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core2[OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE2_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core2[OS_ARCH_MULTICOMMISR_OSCORE_CORE2_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_FlashDone_Isr[OS_ARCH_FLASHDONE_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_PIT0_CH4[OS_ARCH_PIT0_CH4_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_PIT0_CH5[OS_ARCH_PIT0_CH5_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_PIT0_CH6[OS_ARCH_PIT0_CH6_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Can1_Isr[OS_ARCH_CAN1_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Can2_Isr[OS_ARCH_CAN2_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Can3_Isr[OS_ARCH_CAN3_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Can4_Isr[OS_ARCH_CAN4_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp0_Isr[OS_ARCH_ADC89_GRP0_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp1_Isr[OS_ARCH_ADC89_GRP1_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp2_Isr[OS_ARCH_ADC89_GRP2_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp3_Isr[OS_ARCH_ADC89_GRP3_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp4_Isr[OS_ARCH_ADC89_GRP4_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Adc89_Grp5_Isr[OS_ARCH_ADC89_GRP5_ISR_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_Init_Core2_QM[OS_ARCH_TASK_INIT_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_1ms_Core2_QM[OS_ARCH_TASK_1MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_4ms_Core2_QM[OS_ARCH_TASK_4MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_5ms_Core2_QM[OS_ARCH_TASK_5MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_10ms_Core2_QM[OS_ARCH_TASK_10MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_20ms_Core2_QM[OS_ARCH_TASK_20MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_50ms_Core2_QM[OS_ARCH_TASK_50MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_100ms_Core2_QM[OS_ARCH_TASK_100MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_200ms_Core2_QM[OS_ARCH_TASK_200MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_500ms_Core2_QM[OS_ARCH_TASK_500MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
Os_Stack_Address OsCfg_Arch_Stack_Task_1000ms_Core2_QM[OS_ARCH_TASK_1000MS_CORE2_QM_STACK_SIZE / OS_STACK_TYPE_WIDTH];
#define OS_STOP_SEC_STACK_OSCORE2 
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_OSCORE0 
#include "Os_MemMap.h"
Os_Arch_ContextDynType OsCfg_Arch_Context_Kernal_OsCore0_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Default_Init_Task_Core0_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Idle_Task_Core0_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core0_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core0_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Os_Monitor_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_Init_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_10ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_20ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_50ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_100ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_200ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_500ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_1000ms_Core0_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_2ms_Core0_QM_Dyn;
#define OS_STOP_SEC_VAR_OSCORE0 
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_OSCORE1 
#include "Os_MemMap.h"
Os_Arch_ContextDynType OsCfg_Arch_Context_Kernal_OsCore1_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Default_Init_Task_Core1_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Idle_Task_Core1_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core1_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core1_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_Init_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_5ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_10ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_20ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_50ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_100ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_200ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_500ms_Core1_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_1000ms_Core1_QM_Dyn;
#define OS_STOP_SEC_VAR_OSCORE1 
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_OSCORE2 
#include "Os_MemMap.h"
Os_Arch_ContextDynType OsCfg_Arch_Context_Kernal_OsCore2_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Default_Init_Task_Core2_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Idle_Task_Core2_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core2_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core2_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_FlashDone_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_PIT0_CH4_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_PIT0_CH5_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_PIT0_CH6_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Can1_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Can2_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Can3_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Can4_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp0_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp1_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp2_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp3_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp4_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Adc89_Grp5_Isr_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_Init_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_1ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_4ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_5ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_10ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_20ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_50ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_100ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_200ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_500ms_Core2_QM_Dyn;
Os_Arch_ContextDynType OsCfg_Arch_Context_Task_1000ms_Core2_QM_Dyn;
#define OS_STOP_SEC_VAR_OSCORE2 
#include "Os_MemMap.h"


/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variable
********************************************************************************
*/
#define OS_START_SEC_CONST 
#include "Os_MemMap.h"
const CoreIdType Os_Arch_CoreMappingTable[OS_ARCH_PHYSICAL_CORE_NUM] =
{
    OS_CORE_ID_0,
    OS_CORE_ID_1,
    OS_CORE_ID_2
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore0 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Kernal_OsCore0_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ 0U,
    /* exitAddr       = */ 0U,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Kernal_OsCore0, OS_ARCH_KERNAL_OSCORE0_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Kernal_OsCore0)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core0 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Default_Init_Task_Core0_Dyn,
    /* msr            = */ OS_INITIAL_MSR&OS_INITIAL_MSR_EE,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Default_Init_Task_Core0,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Default_Init_Task_Core0, OS_ARCH_DEFAULT_INIT_TASK_CORE0_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Default_Init_Task_Core0)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core0 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Idle_Task_Core0_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Idle_Task_Core0,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Idle_Task_Core0, OS_ARCH_IDLE_TASK_CORE0_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Idle_Task_Core0)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core0 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core0_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL59,
    /* entryAddr      = */ (uint32)&OS_PIT,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core0, OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE0_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core0)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core0 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core0_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL5,
    /* entryAddr      = */ (uint32)&Os_MultiCoreServer_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core0, OS_ARCH_MULTICOMMISR_OSCORE_CORE0_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core0)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Os_Monitor_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Os_Monitor_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL9,
    /* entryAddr      = */ (uint32)&OS_HRT,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Os_Monitor_Isr, OS_ARCH_OS_MONITOR_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Os_Monitor_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_Init_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_Init_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_Init_Core0_QM, OS_ARCH_TASK_INIT_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_Init_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_10ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_10ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_10ms_Core0_QM, OS_ARCH_TASK_10MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_10ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_20ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_20ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_20ms_Core0_QM, OS_ARCH_TASK_20MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_20ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_50ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_50ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_50ms_Core0_QM, OS_ARCH_TASK_50MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_50ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_100ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_100ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_100ms_Core0_QM, OS_ARCH_TASK_100MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_100ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_200ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_200ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_200ms_Core0_QM, OS_ARCH_TASK_200MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_200ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_500ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_500ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_500ms_Core0_QM, OS_ARCH_TASK_500MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_500ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_1000ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_1000ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_1000ms_Core0_QM, OS_ARCH_TASK_1000MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_1000ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_2ms_Core0_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_2ms_Core0_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_2ms_Core0_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_2ms_Core0_QM, OS_ARCH_TASK_2MS_CORE0_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_2ms_Core0_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore1 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Kernal_OsCore1_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ 0U,
    /* exitAddr       = */ 0U,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Kernal_OsCore1, OS_ARCH_KERNAL_OSCORE1_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Kernal_OsCore1)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core1 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Default_Init_Task_Core1_Dyn,
    /* msr            = */ OS_INITIAL_MSR&OS_INITIAL_MSR_EE,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Default_Init_Task_Core1,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Default_Init_Task_Core1, OS_ARCH_DEFAULT_INIT_TASK_CORE1_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Default_Init_Task_Core1)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core1 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Idle_Task_Core1_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Idle_Task_Core1,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Idle_Task_Core1, OS_ARCH_IDLE_TASK_CORE1_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Idle_Task_Core1)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core1 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core1_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL59,
    /* entryAddr      = */ (uint32)&OS_PIT,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core1, OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE1_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core1)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core1 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core1_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL5,
    /* entryAddr      = */ (uint32)&Os_MultiCoreServer_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core1, OS_ARCH_MULTICOMMISR_OSCORE_CORE1_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core1)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_Init_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_Init_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_Init_Core1_QM, OS_ARCH_TASK_INIT_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_Init_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_5ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_5ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_5ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_5ms_Core1_QM, OS_ARCH_TASK_5MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_5ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_10ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_10ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_10ms_Core1_QM, OS_ARCH_TASK_10MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_10ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_20ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_20ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_20ms_Core1_QM, OS_ARCH_TASK_20MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_20ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_50ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_50ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_50ms_Core1_QM, OS_ARCH_TASK_50MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_50ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_100ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_100ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_100ms_Core1_QM, OS_ARCH_TASK_100MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_100ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_200ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_200ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_200ms_Core1_QM, OS_ARCH_TASK_200MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_200ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_500ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_500ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_500ms_Core1_QM, OS_ARCH_TASK_500MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_500ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core1_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_1000ms_Core1_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_1000ms_Core1_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_1000ms_Core1_QM, OS_ARCH_TASK_1000MS_CORE1_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_1000ms_Core1_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore2 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Kernal_OsCore2_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ 0U,
    /* exitAddr       = */ 0U,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Kernal_OsCore2, OS_ARCH_KERNAL_OSCORE2_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Kernal_OsCore2)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core2 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Default_Init_Task_Core2_Dyn,
    /* msr            = */ OS_INITIAL_MSR&OS_INITIAL_MSR_EE,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Default_Init_Task_Core2,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Default_Init_Task_Core2, OS_ARCH_DEFAULT_INIT_TASK_CORE2_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Default_Init_Task_Core2)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core2 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Idle_Task_Core2_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Idle_Task_Core2,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Idle_Task_Core2, OS_ARCH_IDLE_TASK_CORE2_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Idle_Task_Core2)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core2 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_CounterIsr_SystemTimer_Core2_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL59,
    /* entryAddr      = */ (uint32)&OS_PIT,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core2, OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE2_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_CounterIsr_SystemTimer_Core2)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core2 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_MultiCommIsr_OsCore_Core2_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL5,
    /* entryAddr      = */ (uint32)&Os_MultiCoreServer_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core2, OS_ARCH_MULTICOMMISR_OSCORE_CORE2_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_MultiCommIsr_OsCore_Core2)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_FlashDone_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_FlashDone_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL22,
    /* entryAddr      = */ (uint32)&FLASH_Cmd_Done_ISR,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_FlashDone_Isr, OS_ARCH_FLASHDONE_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_FlashDone_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH4 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_PIT0_CH4_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL38,
    /* entryAddr      = */ (uint32)&PIT0_CH4_ISR,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_PIT0_CH4, OS_ARCH_PIT0_CH4_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_PIT0_CH4)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH5 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_PIT0_CH5_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL38,
    /* entryAddr      = */ (uint32)&PIT0_CH5_ISR,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_PIT0_CH5, OS_ARCH_PIT0_CH5_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_PIT0_CH5)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH6 =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_PIT0_CH6_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL38,
    /* entryAddr      = */ (uint32)&PIT0_CH6_ISR,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_PIT0_CH6, OS_ARCH_PIT0_CH6_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_PIT0_CH6)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can1_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Can1_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL11,
    /* entryAddr      = */ (uint32)&Can1_Isr_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Can1_Isr, OS_ARCH_CAN1_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Can1_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can2_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Can2_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL12,
    /* entryAddr      = */ (uint32)&Can2_Isr_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Can2_Isr, OS_ARCH_CAN2_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Can2_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can3_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Can3_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL13,
    /* entryAddr      = */ (uint32)&Can3_Isr_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Can3_Isr, OS_ARCH_CAN3_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Can3_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can4_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Can4_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL14,
    /* entryAddr      = */ (uint32)&Can4_Isr_Handler,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Can4_Isr, OS_ARCH_CAN4_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Can4_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp0_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp0_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP0,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp0_Isr, OS_ARCH_ADC89_GRP0_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp0_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp1_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp1_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP1,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp1_Isr, OS_ARCH_ADC89_GRP1_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp1_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp2_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp2_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP2,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp2_Isr, OS_ARCH_ADC89_GRP2_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp2_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp3_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp3_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP3,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp3_Isr, OS_ARCH_ADC89_GRP3_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp3_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp4_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp4_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP4,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp4_Isr, OS_ARCH_ADC89_GRP4_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp4_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp5_Isr =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Adc89_Grp5_Isr_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_ISR_LEVEL54,
    /* entryAddr      = */ (uint32)&ADC89_GRP5,
    /* exitAddr       = */ (uint32)&Os_Isr_Exit,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Adc89_Grp5_Isr, OS_ARCH_ADC89_GRP5_ISR_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Adc89_Grp5_Isr)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_Init_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_Init_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_Init_Core2_QM, OS_ARCH_TASK_INIT_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_Init_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_1ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_1ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_1ms_Core2_QM, OS_ARCH_TASK_1MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_1ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_4ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_4ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_4ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_4ms_Core2_QM, OS_ARCH_TASK_4MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_4ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_5ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_5ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_5ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_5ms_Core2_QM, OS_ARCH_TASK_5MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_5ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_10ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_10ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_10ms_Core2_QM, OS_ARCH_TASK_10MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_10ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_20ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_20ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_20ms_Core2_QM, OS_ARCH_TASK_20MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_20ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_50ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_50ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_50ms_Core2_QM, OS_ARCH_TASK_50MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_50ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_100ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_100ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_100ms_Core2_QM, OS_ARCH_TASK_100MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_100ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_200ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_200ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_200ms_Core2_QM, OS_ARCH_TASK_200MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_200ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_500ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_500ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_500ms_Core2_QM, OS_ARCH_TASK_500MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_500ms_Core2_QM)
};

const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core2_QM =
{
    /* contextDyn     = */ &OsCfg_Arch_Context_Task_1000ms_Core2_QM_Dyn,
    /* msr            = */ OS_INITIAL_MSR,
    /* cpr            = */ OS_INITIAL_CPR,
    /* entryAddr      = */ (uint32)&Os_Task_Task_1000ms_Core2_QM,
    /* exitAddr       = */ (uint32)&Os_Task_WrongReturn,
    /* stackStartAddr = */ OS_GET_STACK_TOP(OsCfg_Arch_Stack_Task_1000ms_Core2_QM, OS_ARCH_TASK_1000MS_CORE2_QM_STACK_SIZE),
    /* stackEndAddr   = */ OS_GET_STACK_BOTTOM(OsCfg_Arch_Stack_Task_1000ms_Core2_QM)
};

const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core0 =
{
    /* TimerPitBaseAdress = */ OS_HAL_PIT0_BASE_ADDRESS,
    /* TimerPitChannel    = */ 0U,
    /* ReloadValue        = */ 80000U,
};

const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core1 =
{
    /* TimerPitBaseAdress = */ OS_HAL_PIT0_BASE_ADDRESS,
    /* TimerPitChannel    = */ 1U,
    /* ReloadValue        = */ 80000U,
};

const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core2 =
{
    /* TimerPitBaseAdress = */ OS_HAL_PIT0_BASE_ADDRESS,
    /* TimerPitChannel    = */ 2U,
    /* ReloadValue        = */ 80000U,
};

const Os_Arch_Mach_TimerHrtCfgType OsCfg_Arch_TimerHrt_Os_Monitor_Counter =
{
    /* TimerSmtBaseAddress = */ OS_HAL_STM0_BASE_ADDRESS,
    /* TimerSmtChannel     = */ 0U,
    /* Source              = */ &OsCfg_Arch_Source_Os_Monitor_Isr
};

const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core0 =
{
    /* number = */ 226U,
    /* level  = */ OS_ISR_LEVEL59
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core0 =
{
    /* number = */ 0U,
    /* level  = */ OS_ISR_LEVEL5
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Os_Monitor_Isr =
{
    /* number = */ 36U,
    /* level  = */ OS_ISR_LEVEL9
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_GTM_ATOM10 =
{
    /* number = */ 841U,
    /* level  = */ OS_ISR_LEVEL60
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_SIUL_External_Interrupt_0 =
{
    /* number = */ 243U,
    /* level  = */ OS_ISR_LEVEL61
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_SIUL_External_Interrupt_1 =
{
    /* number = */ 244U,
    /* level  = */ OS_ISR_LEVEL61
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_EDMA_CH80 =
{
    /* number = */ 133U,
    /* level  = */ OS_ISR_LEVEL60
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core1 =
{
    /* number = */ 227U,
    /* level  = */ OS_ISR_LEVEL59
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core1 =
{
    /* number = */ 1U,
    /* level  = */ OS_ISR_LEVEL5
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_GTM_ATOM40 =
{
    /* number = */ 853U,
    /* level  = */ OS_ISR_LEVEL60
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core2 =
{
    /* number = */ 228U,
    /* level  = */ OS_ISR_LEVEL59
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core2 =
{
    /* number = */ 2U,
    /* level  = */ OS_ISR_LEVEL5
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_FlashDone_Isr =
{
    /* number = */ 185U,
    /* level  = */ OS_ISR_LEVEL22
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH4 =
{
    /* number = */ 230U,
    /* level  = */ OS_ISR_LEVEL38
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH5 =
{
    /* number = */ 231U,
    /* level  = */ OS_ISR_LEVEL38
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH6 =
{
    /* number = */ 232U,
    /* level  = */ OS_ISR_LEVEL38
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can1_Isr =
{
    /* number = */ 688U,
    /* level  = */ OS_ISR_LEVEL11
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can2_Isr =
{
    /* number = */ 445U,
    /* level  = */ OS_ISR_LEVEL12
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can3_Isr =
{
    /* number = */ 447U,
    /* level  = */ OS_ISR_LEVEL13
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can4_Isr =
{
    /* number = */ 449U,
    /* level  = */ OS_ISR_LEVEL14
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp0_Isr =
{
    /* number = */ 989U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp1_Isr =
{
    /* number = */ 990U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp2_Isr =
{
    /* number = */ 991U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp3_Isr =
{
    /* number = */ 992U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp4_Isr =
{
    /* number = */ 993U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp5_Isr =
{
    /* number = */ 994U,
    /* level  = */ OS_ISR_LEVEL54
};
const Os_Arch_IsrMaskLevelType OsCfg_Arch_IsrMaskLevel_OsCore0 =
{
    /* Cat1MaskLevel       */ OS_ISR_LEVEL61,
    /* Cat2MaskLevel       */ OS_ISR_LEVEL59,
    /* IntDisableMaskLevel */ OS_ISR_LEVEL59
};
const Os_Arch_IsrMaskLevelType OsCfg_Arch_IsrMaskLevel_OsCore1 =
{
    /* Cat1MaskLevel       */ OS_ISR_LEVEL60,
    /* Cat2MaskLevel       */ OS_ISR_LEVEL59,
    /* IntDisableMaskLevel */ OS_ISR_LEVEL59
};
const Os_Arch_IsrMaskLevelType OsCfg_Arch_IsrMaskLevel_OsCore2 =
{
    /* Cat1MaskLevel       */ OS_ISR_LEVEL59,
    /* Cat2MaskLevel       */ OS_ISR_LEVEL59,
    /* IntDisableMaskLevel */ OS_ISR_LEVEL59
};
const Os_Arch_IsrMaskLevelType* const OsCfg_Arch_IsrMaskLevel[OS_COREID_COUNT + 1] =
{
    &OsCfg_Arch_IsrMaskLevel_OsCore0,
    &OsCfg_Arch_IsrMaskLevel_OsCore1,
    &OsCfg_Arch_IsrMaskLevel_OsCore2,
    NULL_PTR
};
#define OS_STOP_SEC_CONST 
#include "Os_MemMap.h"
