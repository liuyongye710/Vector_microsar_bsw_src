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
 *              File: Os_Trace_Lcfg.h
 *   Generation Time: 2020-07-28 17:15:45
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_TRACE_LCFG_H)                                                       /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_TRACE_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Trace_Types.h"

/* Os kernel module dependencies */

/* Os hal dependencies */

/* User file includes */
# include "T1_Microsar.h"


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

# define OS_START_SEC_PUBLIC_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define OS_STOP_SEC_PUBLIC_CORE0_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_PUBLIC_CORE1_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define OS_STOP_SEC_PUBLIC_CORE1_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_PUBLIC_CORE2_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define OS_STOP_SEC_PUBLIC_CORE2_VAR_NOINIT_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Trace configuration data: IdleTask_OsCore0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore0;

/*! Trace configuration data: IdleTask_OsCore1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore1;

/*! Trace configuration data: IdleTask_OsCore2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_IdleTask_OsCore2;

/*! Trace configuration data: Task1000ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core0;

/*! Trace configuration data: Task1000ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core1;

/*! Trace configuration data: Task1000ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1000ms_Core2;

/*! Trace configuration data: Task100ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core0;

/*! Trace configuration data: Task100ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core1;

/*! Trace configuration data: Task100ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task100ms_Core2;

/*! Trace configuration data: Task10ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core0;

/*! Trace configuration data: Task10ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core1;

/*! Trace configuration data: Task10ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task10ms_Core2;

/*! Trace configuration data: Task1ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core0;

/*! Trace configuration data: Task1ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core1;

/*! Trace configuration data: Task1ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task1ms_Core2;

/*! Trace configuration data: Task200ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core0;

/*! Trace configuration data: Task200ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core1;

/*! Trace configuration data: Task200ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task200ms_Core2;

/*! Trace configuration data: Task20ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core0;

/*! Trace configuration data: Task20ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core1;

/*! Trace configuration data: Task20ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task20ms_Core2;

/*! Trace configuration data: Task500ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core0;

/*! Trace configuration data: Task500ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core1;

/*! Trace configuration data: Task500ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task500ms_Core2;

/*! Trace configuration data: Task50ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core0;

/*! Trace configuration data: Task50ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core1;

/*! Trace configuration data: Task50ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task50ms_Core2;

/*! Trace configuration data: Task5ms_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core0;

/*! Trace configuration data: Task5ms_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core1;

/*! Trace configuration data: Task5ms_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Task5ms_Core2;

/*! Trace configuration data: TaskInit_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core0;

/*! Trace configuration data: TaskInit_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core1;

/*! Trace configuration data: TaskInit_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskInit_Core2;

/*! Trace configuration data: TaskSchM_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core0;

/*! Trace configuration data: TaskSchM_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core1;

/*! Trace configuration data: TaskSchM_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_TaskSchM_Core2;

/*! Trace configuration data: Adc0Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc0Sr0_Isr;

/*! Trace configuration data: Adc1Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc1Sr0_Isr;

/*! Trace configuration data: Adc2Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc2Sr0_Isr;

/*! Trace configuration data: Adc3Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc3Sr0_Isr;

/*! Trace configuration data: Adc4Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc4Sr0_Isr;

/*! Trace configuration data: Adc5Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc5Sr0_Isr;

/*! Trace configuration data: Adc6Sr0_Isr */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Adc6Sr0_Isr;

/*! Trace configuration data: CanIsr_0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CanIsr_0;

/*! Trace configuration data: CounterIsr_SystemTimer_Core0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core0;

/*! Trace configuration data: CounterIsr_SystemTimer_Core1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core1;

/*! Trace configuration data: CounterIsr_SystemTimer_Core2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_CounterIsr_SystemTimer_Core2;

/*! Trace configuration data: Isr_TIM02 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Isr_TIM02;

/*! Trace configuration data: Isr_TIM03 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_Isr_TIM03;

/*! Trace configuration data: XSignalIsr_OsCore0 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore0;

/*! Trace configuration data: XSignalIsr_OsCore1 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore1;

/*! Trace configuration data: XSignalIsr_OsCore2 */
extern CONST(Os_TraceThreadConfigType, OS_CONST) OsCfg_Trace_XSignalIsr_OsCore2;

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TRACE_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Trace_Lcfg.h
 *********************************************************************************************************************/
