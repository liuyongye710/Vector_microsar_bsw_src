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
 *              File: Os_Hal_Context_Lcfg.h
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_HAL_CONTEXT_LCFG_H)                                                 /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_HAL_CONTEXT_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_Context_Types.h"

/* Os kernel module dependencies */
# include "Os_Core_Cfg.h"

/* Os hal dependencies */
# include "Os_Hal_Os_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level2_Dyn;

/*! HAL dynamic ISR2 level context data: Level3 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_Isr_Level3_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore0_Dyn;


/*! HAL dynamic task context data: Task1000ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core0_Dyn;


/*! HAL dynamic task context data: Task100ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core0_Dyn;


/*! HAL dynamic task context data: Task10ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core0_Dyn;


/*! HAL dynamic task context data: Task1ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core0_Dyn;


/*! HAL dynamic task context data: Task200ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core0_Dyn;


/*! HAL dynamic task context data: Task20ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core0_Dyn;


/*! HAL dynamic task context data: Task500ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core0_Dyn;


/*! HAL dynamic task context data: Task50ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core0_Dyn;


/*! HAL dynamic task context data: Task5ms_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core0_Dyn;


/*! HAL dynamic task context data: TaskInit_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core0_Dyn;


/*! HAL dynamic task context data: TaskSchM_Core0 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core0_Dyn;


/*! HAL exception context data: OsCore0 */
extern VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore0_ExceptionContext;

# define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level2_Dyn;

/*! HAL dynamic ISR2 level context data: Level3 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level3_Dyn;

/*! HAL dynamic ISR2 level context data: Level4 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level4_Dyn;

/*! HAL dynamic ISR2 level context data: Level5 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level5_Dyn;

/*! HAL dynamic ISR2 level context data: Level6 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level6_Dyn;

/*! HAL dynamic ISR2 level context data: Level7 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level7_Dyn;

/*! HAL dynamic ISR2 level context data: Level8 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level8_Dyn;

/*! HAL dynamic ISR2 level context data: Level9 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level9_Dyn;

/*! HAL dynamic ISR2 level context data: Level10 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level10_Dyn;

/*! HAL dynamic ISR2 level context data: Level11 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_Isr_Level11_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore1_Dyn;


/*! HAL dynamic task context data: Task1000ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core1_Dyn;


/*! HAL dynamic task context data: Task100ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core1_Dyn;


/*! HAL dynamic task context data: Task10ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core1_Dyn;


/*! HAL dynamic task context data: Task1ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core1_Dyn;


/*! HAL dynamic task context data: Task200ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core1_Dyn;


/*! HAL dynamic task context data: Task20ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core1_Dyn;


/*! HAL dynamic task context data: Task500ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core1_Dyn;


/*! HAL dynamic task context data: Task50ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core1_Dyn;


/*! HAL dynamic task context data: Task5ms_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core1_Dyn;


/*! HAL dynamic task context data: TaskInit_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core1_Dyn;


/*! HAL dynamic task context data: TaskSchM_Core1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core1_Dyn;


/*! HAL exception context data: OsCore1 */
extern VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore1_ExceptionContext;

# define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic hook context data: Os_CoreInitHook_OsCore2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2_Dyn;

/*! HAL dynamic ISR2 level context data: Level1 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level1_Dyn;

/*! HAL dynamic ISR2 level context data: Level2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_Isr_Level2_Dyn;

/*! HAL dynamic task context data: IdleTask_OsCore2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_IdleTask_OsCore2_Dyn;


/*! HAL dynamic task context data: Task1000ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1000ms_Core2_Dyn;


/*! HAL dynamic task context data: Task100ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task100ms_Core2_Dyn;


/*! HAL dynamic task context data: Task10ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task10ms_Core2_Dyn;


/*! HAL dynamic task context data: Task1ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task1ms_Core2_Dyn;


/*! HAL dynamic task context data: Task200ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task200ms_Core2_Dyn;


/*! HAL dynamic task context data: Task20ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task20ms_Core2_Dyn;


/*! HAL dynamic task context data: Task500ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task500ms_Core2_Dyn;


/*! HAL dynamic task context data: Task50ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task50ms_Core2_Dyn;


/*! HAL dynamic task context data: Task5ms_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_Task5ms_Core2_Dyn;


/*! HAL dynamic task context data: TaskInit_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskInit_Core2_Dyn;


/*! HAL dynamic task context data: TaskSchM_Core2 */
extern VAR(Os_Hal_ContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_TaskSchM_Core2_Dyn;


/*! HAL exception context data: OsCore2 */
extern VAR(Os_ExceptionContextType, OS_VAR_NOINIT) OsCfg_Hal_Context_OsCore2_ExceptionContext;

# define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore0;

/*! HAL ISR2 context configuration data: CanIsr_0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CanIsr_0;

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core0;

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore0;

/*! HAL task context configuration data: IdleTask_OsCore0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore0;

/*! HAL task context configuration data: Task1000ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core0;

/*! HAL task context configuration data: Task100ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core0;

/*! HAL task context configuration data: Task10ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core0;

/*! HAL task context configuration data: Task1ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core0;

/*! HAL task context configuration data: Task200ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core0;

/*! HAL task context configuration data: Task20ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core0;

/*! HAL task context configuration data: Task500ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core0;

/*! HAL task context configuration data: Task50ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core0;

/*! HAL task context configuration data: Task5ms_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core0;

/*! HAL task context configuration data: TaskInit_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core0;

/*! HAL task context configuration data: TaskSchM_Core0 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core0;

/*! HAL kernel stack configuration data: OsCore0_Kernel */
extern CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore0_Kernel;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore1;

/*! HAL ISR2 context configuration data: Adc0Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc0Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc1Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc1Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc2Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc2Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc3Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc3Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc4Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc4Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc5Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc5Sr0_Isr;

/*! HAL ISR2 context configuration data: Adc6Sr0_Isr */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Adc6Sr0_Isr;

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core1;

/*! HAL ISR2 context configuration data: Isr_TIM02 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Isr_TIM02;

/*! HAL ISR2 context configuration data: Isr_TIM03 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Isr_TIM03;

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore1;

/*! HAL task context configuration data: IdleTask_OsCore1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore1;

/*! HAL task context configuration data: Task1000ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core1;

/*! HAL task context configuration data: Task100ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core1;

/*! HAL task context configuration data: Task10ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core1;

/*! HAL task context configuration data: Task1ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core1;

/*! HAL task context configuration data: Task200ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core1;

/*! HAL task context configuration data: Task20ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core1;

/*! HAL task context configuration data: Task500ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core1;

/*! HAL task context configuration data: Task50ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core1;

/*! HAL task context configuration data: Task5ms_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core1;

/*! HAL task context configuration data: TaskInit_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core1;

/*! HAL task context configuration data: TaskSchM_Core1 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core1;

/*! HAL kernel stack configuration data: OsCore1_Kernel */
extern CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore1_Kernel;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL hook context configuration data: Os_CoreInitHook_OsCore2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Os_CoreInitHook_OsCore2;

/*! HAL ISR2 context configuration data: CounterIsr_SystemTimer_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_CounterIsr_SystemTimer_Core2;

/*! HAL ISR2 context configuration data: XSignalIsr_OsCore2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_XSignalIsr_OsCore2;

/*! HAL task context configuration data: IdleTask_OsCore2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_IdleTask_OsCore2;

/*! HAL task context configuration data: Task1000ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1000ms_Core2;

/*! HAL task context configuration data: Task100ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task100ms_Core2;

/*! HAL task context configuration data: Task10ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task10ms_Core2;

/*! HAL task context configuration data: Task1ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task1ms_Core2;

/*! HAL task context configuration data: Task200ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task200ms_Core2;

/*! HAL task context configuration data: Task20ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task20ms_Core2;

/*! HAL task context configuration data: Task500ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task500ms_Core2;

/*! HAL task context configuration data: Task50ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task50ms_Core2;

/*! HAL task context configuration data: Task5ms_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_Task5ms_Core2;

/*! HAL task context configuration data: TaskInit_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskInit_Core2;

/*! HAL task context configuration data: TaskSchM_Core2 */
extern CONST(Os_Hal_ContextConfigType, OS_CONST) OsCfg_Hal_Context_TaskSchM_Core2;

/*! HAL kernel stack configuration data: OsCore2_Kernel */
extern CONST(Os_Hal_ContextStackConfigType, OS_CONST) OsCfg_Hal_Stack_OsCore2_Kernel;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for HAL exception context. */
extern CONSTP2VAR(Os_ExceptionContextType, AUTOMATIC, OS_CONST)
  OsCfg_Hal_Context_ExceptionContextRef[OS_CFG_COREPHYSICALID_COUNT + 1];

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_HAL_CONTEXT_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Context_Lcfg.h
 *********************************************************************************************************************/
