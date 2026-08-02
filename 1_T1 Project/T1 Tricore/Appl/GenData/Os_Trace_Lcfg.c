/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Trace_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:45
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_TRACE_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Trace_Lcfg.h"
#include "Os_Trace.h"

/* Os kernel module dependencies */
#include "Os_Common_Types.h"

/* Os hal dependencies */


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define OS_START_SEC_PUBLIC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic trace data: IdleTask_OsCore0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_IdleTask_OsCore0_Dyn;

/*! Dynamic trace data: Task1000ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1000ms_Core0_Dyn;

/*! Dynamic trace data: Task100ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task100ms_Core0_Dyn;

/*! Dynamic trace data: Task10ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task10ms_Core0_Dyn;

/*! Dynamic trace data: Task1ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1ms_Core0_Dyn;

/*! Dynamic trace data: Task200ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task200ms_Core0_Dyn;

/*! Dynamic trace data: Task20ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task20ms_Core0_Dyn;

/*! Dynamic trace data: Task500ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task500ms_Core0_Dyn;

/*! Dynamic trace data: Task50ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task50ms_Core0_Dyn;

/*! Dynamic trace data: Task5ms_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task5ms_Core0_Dyn;

/*! Dynamic trace data: TaskInit_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskInit_Core0_Dyn;

/*! Dynamic trace data: TaskSchM_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskSchM_Core0_Dyn;

/*! Dynamic trace data: CanIsr_0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_CanIsr_0_Dyn;

/*! Dynamic trace data: CounterIsr_SystemTimer_Core0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_CounterIsr_SystemTimer_Core0_Dyn;

/*! Dynamic trace data: XSignalIsr_OsCore0 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_XSignalIsr_OsCore0_Dyn;

#define OS_STOP_SEC_PUBLIC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_PUBLIC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic trace data: IdleTask_OsCore1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_IdleTask_OsCore1_Dyn;

/*! Dynamic trace data: Task1000ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1000ms_Core1_Dyn;

/*! Dynamic trace data: Task100ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task100ms_Core1_Dyn;

/*! Dynamic trace data: Task10ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task10ms_Core1_Dyn;

/*! Dynamic trace data: Task1ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1ms_Core1_Dyn;

/*! Dynamic trace data: Task200ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task200ms_Core1_Dyn;

/*! Dynamic trace data: Task20ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task20ms_Core1_Dyn;

/*! Dynamic trace data: Task500ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task500ms_Core1_Dyn;

/*! Dynamic trace data: Task50ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task50ms_Core1_Dyn;

/*! Dynamic trace data: Task5ms_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task5ms_Core1_Dyn;

/*! Dynamic trace data: TaskInit_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskInit_Core1_Dyn;

/*! Dynamic trace data: TaskSchM_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskSchM_Core1_Dyn;

/*! Dynamic trace data: Adc0Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc0Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc1Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc1Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc2Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc2Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc3Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc3Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc4Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc4Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc5Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc5Sr0_Isr_Dyn;

/*! Dynamic trace data: Adc6Sr0_Isr */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Adc6Sr0_Isr_Dyn;

/*! Dynamic trace data: CounterIsr_SystemTimer_Core1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_CounterIsr_SystemTimer_Core1_Dyn;

/*! Dynamic trace data: Isr_TIM02 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Isr_TIM02_Dyn;

/*! Dynamic trace data: Isr_TIM03 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Isr_TIM03_Dyn;

/*! Dynamic trace data: XSignalIsr_OsCore1 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_XSignalIsr_OsCore1_Dyn;

#define OS_STOP_SEC_PUBLIC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_PUBLIC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic trace data: IdleTask_OsCore2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_IdleTask_OsCore2_Dyn;

/*! Dynamic trace data: Task1000ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1000ms_Core2_Dyn;

/*! Dynamic trace data: Task100ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task100ms_Core2_Dyn;

/*! Dynamic trace data: Task10ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task10ms_Core2_Dyn;

/*! Dynamic trace data: Task1ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task1ms_Core2_Dyn;

/*! Dynamic trace data: Task200ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task200ms_Core2_Dyn;

/*! Dynamic trace data: Task20ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task20ms_Core2_Dyn;

/*! Dynamic trace data: Task500ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task500ms_Core2_Dyn;

/*! Dynamic trace data: Task50ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task50ms_Core2_Dyn;

/*! Dynamic trace data: Task5ms_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_Task5ms_Core2_Dyn;

/*! Dynamic trace data: TaskInit_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskInit_Core2_Dyn;

/*! Dynamic trace data: TaskSchM_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_TaskSchM_Core2_Dyn;

/*! Dynamic trace data: CounterIsr_SystemTimer_Core2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_CounterIsr_SystemTimer_Core2_Dyn;

/*! Dynamic trace data: XSignalIsr_OsCore2 */
OS_LOCAL VAR(Os_TraceThreadType, OS_VAR_NOINIT) OsCfg_Trace_XSignalIsr_OsCore2_Dyn;

#define OS_STOP_SEC_PUBLIC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Trace configuration data: IdleTask_OsCore0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore0 =
{
  /* .Dyn  = */ &OsCfg_Trace_IdleTask_OsCore0_Dyn,
  /* .Id   = */ Os_TraceId_IdleTask_OsCore0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: IdleTask_OsCore1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore1 =
{
  /* .Dyn  = */ &OsCfg_Trace_IdleTask_OsCore1_Dyn,
  /* .Id   = */ Os_TraceId_IdleTask_OsCore1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: IdleTask_OsCore2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore2 =
{
  /* .Dyn  = */ &OsCfg_Trace_IdleTask_OsCore2_Dyn,
  /* .Id   = */ Os_TraceId_IdleTask_OsCore2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1000ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1000ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task1000ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1000ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1000ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task1000ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1000ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1000ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task1000ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task100ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task100ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task100ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task100ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task100ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task100ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task100ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task100ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task100ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task10ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task10ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task10ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task10ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task10ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task10ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task10ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task10ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task10ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task1ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task1ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task1ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task1ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task1ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task200ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task200ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task200ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task200ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task200ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task200ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task200ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task200ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task200ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task20ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task20ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task20ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task20ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task20ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task20ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task20ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task20ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task20ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task500ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task500ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task500ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task500ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task500ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task500ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task500ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task500ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task500ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task50ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task50ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task50ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task50ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task50ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task50ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task50ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task50ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task50ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task5ms_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task5ms_Core0_Dyn,
  /* .Id   = */ Os_TraceId_Task5ms_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task5ms_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task5ms_Core1_Dyn,
  /* .Id   = */ Os_TraceId_Task5ms_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Task5ms_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_Task5ms_Core2_Dyn,
  /* .Id   = */ Os_TraceId_Task5ms_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskInit_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskInit_Core0_Dyn,
  /* .Id   = */ Os_TraceId_TaskInit_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskInit_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskInit_Core1_Dyn,
  /* .Id   = */ Os_TraceId_TaskInit_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskInit_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskInit_Core2_Dyn,
  /* .Id   = */ Os_TraceId_TaskInit_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskSchM_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskSchM_Core0_Dyn,
  /* .Id   = */ Os_TraceId_TaskSchM_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskSchM_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskSchM_Core1_Dyn,
  /* .Id   = */ Os_TraceId_TaskSchM_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: TaskSchM_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_TaskSchM_Core2_Dyn,
  /* .Id   = */ Os_TraceId_TaskSchM_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_TASK
};

/*! Trace configuration data: Adc0Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc0Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc0Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc0Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc1Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc1Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc1Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc1Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc2Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc2Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc2Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc2Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc3Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc3Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc3Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc3Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc4Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc4Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc4Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc4Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc5Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc5Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc5Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc5Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Adc6Sr0_Isr */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc6Sr0_Isr =
{
  /* .Dyn  = */ &OsCfg_Trace_Adc6Sr0_Isr_Dyn,
  /* .Id   = */ Os_TraceId_Adc6Sr0_Isr,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: CanIsr_0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CanIsr_0 =
{
  /* .Dyn  = */ &OsCfg_Trace_CanIsr_0_Dyn,
  /* .Id   = */ Os_TraceId_CanIsr_0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: CounterIsr_SystemTimer_Core0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core0 =
{
  /* .Dyn  = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core0_Dyn,
  /* .Id   = */ Os_TraceId_CounterIsr_SystemTimer_Core0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: CounterIsr_SystemTimer_Core1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core1 =
{
  /* .Dyn  = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core1_Dyn,
  /* .Id   = */ Os_TraceId_CounterIsr_SystemTimer_Core1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: CounterIsr_SystemTimer_Core2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core2 =
{
  /* .Dyn  = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core2_Dyn,
  /* .Id   = */ Os_TraceId_CounterIsr_SystemTimer_Core2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Isr_TIM02 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Isr_TIM02 =
{
  /* .Dyn  = */ &OsCfg_Trace_Isr_TIM02_Dyn,
  /* .Id   = */ Os_TraceId_Isr_TIM02,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: Isr_TIM03 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Isr_TIM03 =
{
  /* .Dyn  = */ &OsCfg_Trace_Isr_TIM03_Dyn,
  /* .Id   = */ Os_TraceId_Isr_TIM03,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: XSignalIsr_OsCore0 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore0 =
{
  /* .Dyn  = */ &OsCfg_Trace_XSignalIsr_OsCore0_Dyn,
  /* .Id   = */ Os_TraceId_XSignalIsr_OsCore0,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: XSignalIsr_OsCore1 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore1 =
{
  /* .Dyn  = */ &OsCfg_Trace_XSignalIsr_OsCore1_Dyn,
  /* .Id   = */ Os_TraceId_XSignalIsr_OsCore1,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

/*! Trace configuration data: XSignalIsr_OsCore2 */
CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore2 =
{
  /* .Dyn  = */ &OsCfg_Trace_XSignalIsr_OsCore2_Dyn,
  /* .Id   = */ Os_TraceId_XSignalIsr_OsCore2,
  /* .Type = */ OS_TRACE_THREAD_TYPE_ISR
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Trace_Lcfg.c
 *********************************************************************************************************************/
