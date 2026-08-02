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
 *              File: Os_Hal_Context_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_CONTEXT_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Context.h"

/* Os kernel module dependencies */
#include "OsInt.h"
#include "Os_Core.h"
#include "Os_Hook_Lcfg.h"
#include "Os_Hook.h"
#include "Os_Ioc_Lcfg.h"
#include "Os_Isr_Lcfg.h"
#include "Os_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Task_Lcfg.h"
#include "Os_Task.h"

/* Os hal dependencies */
#include "Os_Hal_Core.h"


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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level2_Dyn;

/*! HAL dynamic ISR2 level context data: Level3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level3_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore0_Dyn;

/*! HAL dynamic task context data: Task1000ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core0_Dyn;

/*! HAL dynamic task context data: Task100ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core0_Dyn;

/*! HAL dynamic task context data: Task10ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core0_Dyn;

/*! HAL dynamic task context data: Task1ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core0_Dyn;

/*! HAL dynamic task context data: Task200ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core0_Dyn;

/*! HAL dynamic task context data: Task20ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core0_Dyn;

/*! HAL dynamic task context data: Task500ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core0_Dyn;

/*! HAL dynamic task context data: Task50ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core0_Dyn;

/*! HAL dynamic task context data: Task5ms_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core0_Dyn;

/*! HAL dynamic task context data: TaskInit_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core0_Dyn;

/*! HAL dynamic task context data: TaskSchM_Core0 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core0_Dyn;

/*! HAL exception context data: OsCore0 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_ExceptionContext;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level2_Dyn;

/*! HAL dynamic ISR2 level context data: Level3 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level3_Dyn;

/*! HAL dynamic ISR2 level context data: Level4 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level4_Dyn;

/*! HAL dynamic ISR2 level context data: Level5 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level5_Dyn;

/*! HAL dynamic ISR2 level context data: Level6 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level6_Dyn;

/*! HAL dynamic ISR2 level context data: Level7 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level7_Dyn;

/*! HAL dynamic ISR2 level context data: Level8 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level8_Dyn;

/*! HAL dynamic ISR2 level context data: Level9 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level9_Dyn;

/*! HAL dynamic ISR2 level context data: Level10 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level10_Dyn;

/*! HAL dynamic ISR2 level context data: Level11 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level11_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore1_Dyn;

/*! HAL dynamic task context data: Task1000ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core1_Dyn;

/*! HAL dynamic task context data: Task100ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core1_Dyn;

/*! HAL dynamic task context data: Task10ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core1_Dyn;

/*! HAL dynamic task context data: Task1ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core1_Dyn;

/*! HAL dynamic task context data: Task200ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core1_Dyn;

/*! HAL dynamic task context data: Task20ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core1_Dyn;

/*! HAL dynamic task context data: Task500ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core1_Dyn;

/*! HAL dynamic task context data: Task50ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core1_Dyn;

/*! HAL dynamic task context data: Task5ms_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core1_Dyn;

/*! HAL dynamic task context data: TaskInit_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core1_Dyn;

/*! HAL dynamic task context data: TaskSchM_Core1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core1_Dyn;

/*! HAL exception context data: OsCore1 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_ExceptionContext;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level2_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore2_Dyn;

/*! HAL dynamic task context data: Task1000ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core2_Dyn;

/*! HAL dynamic task context data: Task100ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core2_Dyn;

/*! HAL dynamic task context data: Task10ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core2_Dyn;

/*! HAL dynamic task context data: Task1ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core2_Dyn;

/*! HAL dynamic task context data: Task200ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core2_Dyn;

/*! HAL dynamic task context data: Task20ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core2_Dyn;

/*! HAL dynamic task context data: Task500ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core2_Dyn;

/*! HAL dynamic task context data: Task50ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core2_Dyn;

/*! HAL dynamic task context data: Task5ms_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core2_Dyn;

/*! HAL dynamic task context data: TaskInit_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core2_Dyn;

/*! HAL dynamic task context data: TaskSchM_Core2 */
VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core2_Dyn;

/*! HAL exception context data: OsCore2 */
VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_ExceptionContext;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Init_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CanIsr_0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CanIsr_0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_CanIsr_0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1000ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio51_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio51_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1000ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task100ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio54_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio54_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task100ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task10ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio57_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio57_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task10ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio59_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio59_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task200ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio53_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio53_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task200ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task20ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio56_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio56_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task20ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task500ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio52_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio52_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task500ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task50ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task50ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task5ms_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio58_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio58_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task5ms_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskInit_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio100_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio100_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskInit_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskSchM_Core0 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core0 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_TaskSchM_Core0_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_TaskSchM_Core0_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskSchM_Core0,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore0_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore0_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn)+1)  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Init_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc0Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc0Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc0Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc1Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc1Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc1Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc2Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc2Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc2Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc3Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc3Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc3Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc4Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc4Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc4Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc5Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc5Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc5Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Adc6Sr0_Isr */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc6Sr0_Isr =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Adc6Sr0_Isr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Isr_TIM02 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Isr_TIM02 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Isr_TIM02,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: Isr_TIM03 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Isr_TIM03 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Isr_TIM03,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1000ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio51_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio51_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1000ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task100ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task100ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task10ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio57_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio57_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task10ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio59_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio59_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task200ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio53_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio53_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task200ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task20ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio56_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio56_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task20ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task500ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio52_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio52_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task500ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task50ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio55_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio55_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task50ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task5ms_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio58_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio58_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task5ms_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskInit_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio100_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio100_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskInit_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskSchM_Core1 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core1 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio90_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio90_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskSchM_Core1,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore1_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore1_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn)+1)  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Init_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Init_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_HookWrapperOs_CoreInitHook,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapHookReturn,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_TimerHrtIsr,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Isr_Os_XSigRecvIsrHandler,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapIsrEpilogue,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)56<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: IdleTask_OsCore2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Os_IdleTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1000ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio51_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio51_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1000ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task100ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio54_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio54_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task100ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task10ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio57_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio57_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task10ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task1ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio59_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio59_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task1ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task200ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task200ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task20ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio56_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio56_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task20ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task500ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio52_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio52_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task500ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task50ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio55_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio55_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task50ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: Task5ms_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio58_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio58_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_Task5ms_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskInit_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio100_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio100_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskInit_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL task context configuration data: TaskSchM_Core2 */
CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core2 =
{
  /* .StackEndAddr     = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio90_Dyn)+1),  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* .StackStartAddr   = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio90_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .ProgramStatus    = */ (uint32)OS_HAL_PSW_IS_MASK | OS_HAL_PSW_CDE_MASK | OS_HAL_PSW_IO_SUPERVISOR | OS_HAL_PSW_S_MASK | OS_HAL_PSW_PRS_PS0,
  /* .Entry            = */ (uint32)&Os_Task_TaskSchM_Core2,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .ReturnAddress    = */ (uint32)&Os_TrapTaskMissingTerminateTask,  /* PRQA S 0305, 0428 */ /* MD_Os_Hal_0305, MD_Os_Hal_0428 */
  /* .IntStatus        = */ ((uint32)0<<OS_HAL_PCXI_PCPN_BIT_POSITION) | OS_HAL_PCXI_PIE_ENABLED
};

/*! HAL kernel stack configuration data: OsCore2_Kernel */
CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore2_Kernel =
{
  /* .StackRegionStart = */ (uint32)OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn),  /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .StackRegionEnd   = */ (uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn)+1)  /* PRQA S 0306, 0489 */ /* MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for HAL exception context. */
CONSTP2VAR(Os_ExceptionContextType, AUTOMATIC, OS_CONST)
  OsCfg_Hal_Context_ExceptionContextRef[OS_CFG_COREPHYSICALID_COUNT + 1] =
{
  &OsCfg_Hal_Context_OsCore0_ExceptionContext,
  &OsCfg_Hal_Context_OsCore1_ExceptionContext,
  &OsCfg_Hal_Context_OsCore2_ExceptionContext,
  NULL_PTR
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
 *  END OF FILE: Os_Hal_Context_Lcfg.c
 *********************************************************************************************************************/
