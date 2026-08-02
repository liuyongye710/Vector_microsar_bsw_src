/*
********************************************************************************
*
*  File name:	Os_Arch_Kernal_Lcfg.h
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
#ifndef OS_ARCH_KERNAL_LCFG_H_
#define OS_ARCH_KERNAL_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Isr_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define OS_ARCH_PHYSICAL_CORE_NUM                     (3U)

#define OS_ARCH_KERNAL_OSCORE0_STACK_SIZE             (1024U)
#define OS_ARCH_DEFAULT_INIT_TASK_CORE0_STACK_SIZE    (1024U)
#define OS_ARCH_IDLE_TASK_CORE0_STACK_SIZE            (2048U)
#define OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE0_STACK_SIZE (1024U)
#define OS_ARCH_MULTICOMMISR_OSCORE_CORE0_STACK_SIZE  (1024U)
#define OS_ARCH_OS_MONITOR_ISR_STACK_SIZE             (1024U)
#define OS_ARCH_TASK_INIT_CORE0_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_10MS_CORE0_QM_STACK_SIZE         (4096U)
#define OS_ARCH_TASK_20MS_CORE0_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_50MS_CORE0_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_100MS_CORE0_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_200MS_CORE0_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_500MS_CORE0_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_1000MS_CORE0_QM_STACK_SIZE       (1024U)
#define OS_ARCH_TASK_2MS_CORE0_QM_STACK_SIZE          (4096U)

#define OS_ARCH_KERNAL_OSCORE1_STACK_SIZE             (1024U)
#define OS_ARCH_DEFAULT_INIT_TASK_CORE1_STACK_SIZE    (1024U)
#define OS_ARCH_IDLE_TASK_CORE1_STACK_SIZE            (2048U)
#define OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE1_STACK_SIZE (1024U)
#define OS_ARCH_MULTICOMMISR_OSCORE_CORE1_STACK_SIZE  (1024U)
#define OS_ARCH_TASK_INIT_CORE1_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_5MS_CORE1_QM_STACK_SIZE          (1024U)
#define OS_ARCH_TASK_10MS_CORE1_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_20MS_CORE1_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_50MS_CORE1_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_100MS_CORE1_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_200MS_CORE1_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_500MS_CORE1_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_1000MS_CORE1_QM_STACK_SIZE       (1024U)

#define OS_ARCH_KERNAL_OSCORE2_STACK_SIZE             (1024U)
#define OS_ARCH_DEFAULT_INIT_TASK_CORE2_STACK_SIZE    (1024U)
#define OS_ARCH_IDLE_TASK_CORE2_STACK_SIZE            (1024U)
#define OS_ARCH_COUNTERISR_SYSTEMTIMER_CORE2_STACK_SIZE (1024U)
#define OS_ARCH_MULTICOMMISR_OSCORE_CORE2_STACK_SIZE  (1024U)
#define OS_ARCH_FLASHDONE_ISR_STACK_SIZE              (1024U)
#define OS_ARCH_PIT0_CH4_STACK_SIZE                   (1024U)
#define OS_ARCH_PIT0_CH5_STACK_SIZE                   (1024U)
#define OS_ARCH_PIT0_CH6_STACK_SIZE                   (1024U)
#define OS_ARCH_CAN1_ISR_STACK_SIZE                   (1024U)
#define OS_ARCH_CAN2_ISR_STACK_SIZE                   (1024U)
#define OS_ARCH_CAN3_ISR_STACK_SIZE                   (1024U)
#define OS_ARCH_CAN4_ISR_STACK_SIZE                   (1024U)
#define OS_ARCH_ADC89_GRP0_ISR_STACK_SIZE             (2048U)
#define OS_ARCH_ADC89_GRP1_ISR_STACK_SIZE             (2048U)
#define OS_ARCH_ADC89_GRP2_ISR_STACK_SIZE             (1024U)
#define OS_ARCH_ADC89_GRP3_ISR_STACK_SIZE             (1024U)
#define OS_ARCH_ADC89_GRP4_ISR_STACK_SIZE             (1024U)
#define OS_ARCH_ADC89_GRP5_ISR_STACK_SIZE             (1024U)
#define OS_ARCH_TASK_INIT_CORE2_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_1MS_CORE2_QM_STACK_SIZE          (1024U)
#define OS_ARCH_TASK_4MS_CORE2_QM_STACK_SIZE          (1024U)
#define OS_ARCH_TASK_5MS_CORE2_QM_STACK_SIZE          (4096U)
#define OS_ARCH_TASK_10MS_CORE2_QM_STACK_SIZE         (2048U)
#define OS_ARCH_TASK_20MS_CORE2_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_50MS_CORE2_QM_STACK_SIZE         (1024U)
#define OS_ARCH_TASK_100MS_CORE2_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_200MS_CORE2_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_500MS_CORE2_QM_STACK_SIZE        (1024U)
#define OS_ARCH_TASK_1000MS_CORE2_QM_STACK_SIZE       (1024U)

#define OS_ISR_LEVEL59                                (59U)
#define OS_ISR_LEVEL5                                 (5U)
#define OS_ISR_LEVEL9                                 (9U)
#define OS_ISR_LEVEL60                                (60U)
#define OS_ISR_LEVEL61                                (61U)
#define OS_ISR_LEVEL22                                (22U)
#define OS_ISR_LEVEL38                                (38U)
#define OS_ISR_LEVEL11                                (11U)
#define OS_ISR_LEVEL12                                (12U)
#define OS_ISR_LEVEL13                                (13U)
#define OS_ISR_LEVEL14                                (14U)
#define OS_ISR_LEVEL54                                (54U)

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
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore0;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core0;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core0;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core0;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core0;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Os_Monitor_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core0_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_2ms_Core0_QM;

extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore1;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core1;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core1;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core1;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core1;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_5ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core1_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core1_QM;

extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Kernal_OsCore2;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Default_Init_Task_Core2;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Idle_Task_Core2;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_CounterIsr_SystemTimer_Core2;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_MultiCommIsr_OsCore_Core2;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_FlashDone_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH4;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH5;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_PIT0_CH6;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can1_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can2_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can3_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Can4_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp0_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp1_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp2_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp3_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp4_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Adc89_Grp5_Isr;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_Init_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_4ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_5ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_10ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_20ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_50ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_100ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_200ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_500ms_Core2_QM;
extern const Os_Arch_ContextCfgType OsCfg_Arch_Context_Task_1000ms_Core2_QM;

extern const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core0;
extern const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core1;
extern const Os_Arch_Mach_TimerPitCfgType OsCfg_Arch_TimerPit_SystemTimer_Core2;
extern const Os_Arch_Mach_TimerHrtCfgType OsCfg_Arch_TimerHrt_Os_Monitor_Counter;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core0;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core0;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Os_Monitor_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_GTM_ATOM10;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_SIUL_External_Interrupt_0;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_SIUL_External_Interrupt_1;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_EDMA_CH80;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core1;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core1;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_GTM_ATOM40;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_CounterIsr_SystemTimer_Core2;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_MultiCommIsr_OsCore_Core2;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_FlashDone_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH4;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH5;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_PIT0_CH6;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can1_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can2_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can3_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Can4_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp0_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp1_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp2_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp3_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp4_Isr;
extern const Os_Arch_IsrSourceType OsCfg_Arch_Source_Adc89_Grp5_Isr;
extern const CoreIdType Os_Arch_CoreMappingTable[OS_ARCH_PHYSICAL_CORE_NUM];
extern const Os_Arch_IsrMaskLevelType* const OsCfg_Arch_IsrMaskLevel[OS_COREID_COUNT + 1];

#endif /* OS_ARCH_KERNAL_LCFG_H_ */

