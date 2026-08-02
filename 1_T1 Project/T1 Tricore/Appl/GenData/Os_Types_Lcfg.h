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
 *              File: Os_Types_Lcfg.h
 *   Generation Time: 2020-07-28 17:15:45
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_TYPES_LCFG_H)                                                       /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_TYPES_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* OS-Application identifiers. */
#define OsApplication_Core0 OsApplication_Core0
#define OsApplication_Core1 OsApplication_Core1
#define OsApplication_Core2 OsApplication_Core2
#define SystemApplication_OsCore0 SystemApplication_OsCore0
#define SystemApplication_OsCore1 SystemApplication_OsCore1
#define SystemApplication_OsCore2 SystemApplication_OsCore2

/* Trusted function identifiers. */

/* Non-trusted function identifiers. */

/* Fast trusted function identifiers. */

/* Task identifiers. */
#define IdleTask_OsCore0 IdleTask_OsCore0
#define IdleTask_OsCore1 IdleTask_OsCore1
#define IdleTask_OsCore2 IdleTask_OsCore2
#define Task1000ms_Core0 Task1000ms_Core0
#define Task1000ms_Core1 Task1000ms_Core1
#define Task1000ms_Core2 Task1000ms_Core2
#define Task100ms_Core0 Task100ms_Core0
#define Task100ms_Core1 Task100ms_Core1
#define Task100ms_Core2 Task100ms_Core2
#define Task10ms_Core0 Task10ms_Core0
#define Task10ms_Core1 Task10ms_Core1
#define Task10ms_Core2 Task10ms_Core2
#define Task1ms_Core0 Task1ms_Core0
#define Task1ms_Core1 Task1ms_Core1
#define Task1ms_Core2 Task1ms_Core2
#define Task200ms_Core0 Task200ms_Core0
#define Task200ms_Core1 Task200ms_Core1
#define Task200ms_Core2 Task200ms_Core2
#define Task20ms_Core0 Task20ms_Core0
#define Task20ms_Core1 Task20ms_Core1
#define Task20ms_Core2 Task20ms_Core2
#define Task500ms_Core0 Task500ms_Core0
#define Task500ms_Core1 Task500ms_Core1
#define Task500ms_Core2 Task500ms_Core2
#define Task50ms_Core0 Task50ms_Core0
#define Task50ms_Core1 Task50ms_Core1
#define Task50ms_Core2 Task50ms_Core2
#define Task5ms_Core0 Task5ms_Core0
#define Task5ms_Core1 Task5ms_Core1
#define Task5ms_Core2 Task5ms_Core2
#define TaskInit_Core0 TaskInit_Core0
#define TaskInit_Core1 TaskInit_Core1
#define TaskInit_Core2 TaskInit_Core2
#define TaskSchM_Core0 TaskSchM_Core0
#define TaskSchM_Core1 TaskSchM_Core1
#define TaskSchM_Core2 TaskSchM_Core2

/* Category 2 ISR identifiers. */
#define Adc0Sr0_Isr Adc0Sr0_Isr
#define Adc1Sr0_Isr Adc1Sr0_Isr
#define Adc2Sr0_Isr Adc2Sr0_Isr
#define Adc3Sr0_Isr Adc3Sr0_Isr
#define Adc4Sr0_Isr Adc4Sr0_Isr
#define Adc5Sr0_Isr Adc5Sr0_Isr
#define Adc6Sr0_Isr Adc6Sr0_Isr
#define CanIsr_0 CanIsr_0
#define CounterIsr_SystemTimer_Core0 CounterIsr_SystemTimer_Core0
#define CounterIsr_SystemTimer_Core1 CounterIsr_SystemTimer_Core1
#define CounterIsr_SystemTimer_Core2 CounterIsr_SystemTimer_Core2
#define Isr_TIM02 Isr_TIM02
#define Isr_TIM03 Isr_TIM03
#define XSignalIsr_OsCore0 XSignalIsr_OsCore0
#define XSignalIsr_OsCore1 XSignalIsr_OsCore1
#define XSignalIsr_OsCore2 XSignalIsr_OsCore2

/* Alarm identifiers. */
#define Rte_Al_TE2_EcuM_EcuM_MainFunction Rte_Al_TE2_EcuM_EcuM_MainFunction
#define Rte_Al_TE2_TaskSchM_Core0_0_10ms Rte_Al_TE2_TaskSchM_Core0_0_10ms
#define Rte_Al_TE2_TaskSchM_Core0_0_20ms Rte_Al_TE2_TaskSchM_Core0_0_20ms
#define Rte_Al_TE3_EcuM_EcuM_MainFunction Rte_Al_TE3_EcuM_EcuM_MainFunction
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2
#define Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2

/* Counter identifiers. */
#define SystemTimer_Core0 SystemTimer_Core0
#define SystemTimer_Core1 SystemTimer_Core1
#define SystemTimer_Core2 SystemTimer_Core2

/* ScheduleTable identifiers. */

/* Resource identifiers. */
#define RES_SCHEDULER_OsCore0 RES_SCHEDULER_OsCore0
#define RES_SCHEDULER_OsCore1 RES_SCHEDULER_OsCore1
#define RES_SCHEDULER_OsCore2 RES_SCHEDULER_OsCore2

/* Spinlock identifiers. */

/* Peripheral identifiers. */

/* Barrier identifiers. */

/* Trace thread identifiers (Tasks and ISRs inclusive system objects). */
#define Os_TraceId_IdleTask_OsCore0 Os_TraceId_IdleTask_OsCore0
#define Os_TraceId_IdleTask_OsCore1 Os_TraceId_IdleTask_OsCore1
#define Os_TraceId_IdleTask_OsCore2 Os_TraceId_IdleTask_OsCore2
#define Os_TraceId_Task1000ms_Core0 Os_TraceId_Task1000ms_Core0
#define Os_TraceId_Task1000ms_Core1 Os_TraceId_Task1000ms_Core1
#define Os_TraceId_Task1000ms_Core2 Os_TraceId_Task1000ms_Core2
#define Os_TraceId_Task100ms_Core0 Os_TraceId_Task100ms_Core0
#define Os_TraceId_Task100ms_Core1 Os_TraceId_Task100ms_Core1
#define Os_TraceId_Task100ms_Core2 Os_TraceId_Task100ms_Core2
#define Os_TraceId_Task10ms_Core0 Os_TraceId_Task10ms_Core0
#define Os_TraceId_Task10ms_Core1 Os_TraceId_Task10ms_Core1
#define Os_TraceId_Task10ms_Core2 Os_TraceId_Task10ms_Core2
#define Os_TraceId_Task1ms_Core0 Os_TraceId_Task1ms_Core0
#define Os_TraceId_Task1ms_Core1 Os_TraceId_Task1ms_Core1
#define Os_TraceId_Task1ms_Core2 Os_TraceId_Task1ms_Core2
#define Os_TraceId_Task200ms_Core0 Os_TraceId_Task200ms_Core0
#define Os_TraceId_Task200ms_Core1 Os_TraceId_Task200ms_Core1
#define Os_TraceId_Task200ms_Core2 Os_TraceId_Task200ms_Core2
#define Os_TraceId_Task20ms_Core0 Os_TraceId_Task20ms_Core0
#define Os_TraceId_Task20ms_Core1 Os_TraceId_Task20ms_Core1
#define Os_TraceId_Task20ms_Core2 Os_TraceId_Task20ms_Core2
#define Os_TraceId_Task500ms_Core0 Os_TraceId_Task500ms_Core0
#define Os_TraceId_Task500ms_Core1 Os_TraceId_Task500ms_Core1
#define Os_TraceId_Task500ms_Core2 Os_TraceId_Task500ms_Core2
#define Os_TraceId_Task50ms_Core0 Os_TraceId_Task50ms_Core0
#define Os_TraceId_Task50ms_Core1 Os_TraceId_Task50ms_Core1
#define Os_TraceId_Task50ms_Core2 Os_TraceId_Task50ms_Core2
#define Os_TraceId_Task5ms_Core0 Os_TraceId_Task5ms_Core0
#define Os_TraceId_Task5ms_Core1 Os_TraceId_Task5ms_Core1
#define Os_TraceId_Task5ms_Core2 Os_TraceId_Task5ms_Core2
#define Os_TraceId_TaskInit_Core0 Os_TraceId_TaskInit_Core0
#define Os_TraceId_TaskInit_Core1 Os_TraceId_TaskInit_Core1
#define Os_TraceId_TaskInit_Core2 Os_TraceId_TaskInit_Core2
#define Os_TraceId_TaskSchM_Core0 Os_TraceId_TaskSchM_Core0
#define Os_TraceId_TaskSchM_Core1 Os_TraceId_TaskSchM_Core1
#define Os_TraceId_TaskSchM_Core2 Os_TraceId_TaskSchM_Core2
#define Os_TraceId_Adc0Sr0_Isr Os_TraceId_Adc0Sr0_Isr
#define Os_TraceId_Adc1Sr0_Isr Os_TraceId_Adc1Sr0_Isr
#define Os_TraceId_Adc2Sr0_Isr Os_TraceId_Adc2Sr0_Isr
#define Os_TraceId_Adc3Sr0_Isr Os_TraceId_Adc3Sr0_Isr
#define Os_TraceId_Adc4Sr0_Isr Os_TraceId_Adc4Sr0_Isr
#define Os_TraceId_Adc5Sr0_Isr Os_TraceId_Adc5Sr0_Isr
#define Os_TraceId_Adc6Sr0_Isr Os_TraceId_Adc6Sr0_Isr
#define Os_TraceId_CanIsr_0 Os_TraceId_CanIsr_0
#define Os_TraceId_CounterIsr_SystemTimer_Core0 Os_TraceId_CounterIsr_SystemTimer_Core0
#define Os_TraceId_CounterIsr_SystemTimer_Core1 Os_TraceId_CounterIsr_SystemTimer_Core1
#define Os_TraceId_CounterIsr_SystemTimer_Core2 Os_TraceId_CounterIsr_SystemTimer_Core2
#define Os_TraceId_Isr_TIM02 Os_TraceId_Isr_TIM02
#define Os_TraceId_Isr_TIM03 Os_TraceId_Isr_TIM03
#define Os_TraceId_XSignalIsr_OsCore0 Os_TraceId_XSignalIsr_OsCore0
#define Os_TraceId_XSignalIsr_OsCore1 Os_TraceId_XSignalIsr_OsCore1
#define Os_TraceId_XSignalIsr_OsCore2 Os_TraceId_XSignalIsr_OsCore2

/* Trace spinlock identifiers (All spinlocks inclusive system objects). */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! OS-Application identifiers. */
typedef enum
{
  OsApplication_Core0 = 0, /* 0x00000001 */
  OsApplication_Core1 = 1, /* 0x00000002 */
  OsApplication_Core2 = 2, /* 0x00000004 */
  SystemApplication_OsCore0 = 3, /* 0x00000008 */
  SystemApplication_OsCore1 = 4, /* 0x00000010 */
  SystemApplication_OsCore2 = 5, /* 0x00000020 */
  OS_APPID_COUNT = 6,
  INVALID_OSAPPLICATION = OS_APPID_COUNT
} ApplicationType;

/*! Trusted function identifiers. */
typedef enum
{
  OS_TRUSTEDFUNCTIONID_COUNT = 0
} TrustedFunctionIndexType;

/*! Non-trusted function identifiers. */
typedef enum
{
  OS_NONTRUSTEDFUNCTIONID_COUNT = 0
} Os_NonTrustedFunctionIndexType;

/*! Fast trusted function identifiers. */
typedef enum
{
  OS_FASTTRUSTEDFUNCTIONID_COUNT = 0
} Os_FastTrustedFunctionIndexType;

/*! Task identifiers. */
typedef enum
{
  IdleTask_OsCore0 = 0,
  IdleTask_OsCore1 = 1,
  IdleTask_OsCore2 = 2,
  Task1000ms_Core0 = 3,
  Task1000ms_Core1 = 4,
  Task1000ms_Core2 = 5,
  Task100ms_Core0 = 6,
  Task100ms_Core1 = 7,
  Task100ms_Core2 = 8,
  Task10ms_Core0 = 9,
  Task10ms_Core1 = 10,
  Task10ms_Core2 = 11,
  Task1ms_Core0 = 12,
  Task1ms_Core1 = 13,
  Task1ms_Core2 = 14,
  Task200ms_Core0 = 15,
  Task200ms_Core1 = 16,
  Task200ms_Core2 = 17,
  Task20ms_Core0 = 18,
  Task20ms_Core1 = 19,
  Task20ms_Core2 = 20,
  Task500ms_Core0 = 21,
  Task500ms_Core1 = 22,
  Task500ms_Core2 = 23,
  Task50ms_Core0 = 24,
  Task50ms_Core1 = 25,
  Task50ms_Core2 = 26,
  Task5ms_Core0 = 27,
  Task5ms_Core1 = 28,
  Task5ms_Core2 = 29,
  TaskInit_Core0 = 30,
  TaskInit_Core1 = 31,
  TaskInit_Core2 = 32,
  TaskSchM_Core0 = 33,
  TaskSchM_Core1 = 34,
  TaskSchM_Core2 = 35,
  OS_TASKID_COUNT = 36,
  INVALID_TASK = OS_TASKID_COUNT
} TaskType;

/*! Category 2 ISR identifiers. */
typedef enum
{
  Adc0Sr0_Isr = 0,
  Adc1Sr0_Isr = 1,
  Adc2Sr0_Isr = 2,
  Adc3Sr0_Isr = 3,
  Adc4Sr0_Isr = 4,
  Adc5Sr0_Isr = 5,
  Adc6Sr0_Isr = 6,
  CanIsr_0 = 7,
  CounterIsr_SystemTimer_Core0 = 8,
  CounterIsr_SystemTimer_Core1 = 9,
  CounterIsr_SystemTimer_Core2 = 10,
  Isr_TIM02 = 11,
  Isr_TIM03 = 12,
  XSignalIsr_OsCore0 = 13,
  XSignalIsr_OsCore1 = 14,
  XSignalIsr_OsCore2 = 15,
  OS_ISRID_COUNT = 16,
  INVALID_ISR = OS_ISRID_COUNT
} ISRType;

/*! Alarm identifiers. */
typedef enum
{
  Rte_Al_TE2_EcuM_EcuM_MainFunction = 0,
  Rte_Al_TE2_TaskSchM_Core0_0_10ms = 1,
  Rte_Al_TE2_TaskSchM_Core0_0_20ms = 2,
  Rte_Al_TE3_EcuM_EcuM_MainFunction = 3,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 = 4,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 = 5,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 = 6,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 = 7,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 = 8,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 = 9,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 = 10,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 = 11,
  Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 = 12,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 = 13,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 = 14,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 = 15,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 = 16,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 = 17,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 = 18,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 = 19,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 = 20,
  Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 = 21,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 = 22,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 = 23,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 = 24,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 = 25,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 = 26,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 = 27,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 = 28,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 = 29,
  Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 = 30,
  OS_ALARMID_COUNT = 31
} AlarmType;

/*! Counter identifiers. */
typedef enum
{
  SystemTimer_Core0 = 0,
  SystemTimer_Core1 = 1,
  SystemTimer_Core2 = 2,
  OS_COUNTERID_COUNT = 3
} CounterType;

/*! ScheduleTable identifiers. */
typedef enum
{
  OS_SCHTID_COUNT = 0
} ScheduleTableType;

/*! Resource identifiers. */
typedef enum
{
  RES_SCHEDULER_OsCore0 = 0,
  RES_SCHEDULER_OsCore1 = 1,
  RES_SCHEDULER_OsCore2 = 2,
  OS_RESOURCEID_COUNT = 3
} ResourceType;

/*! Spinlock identifiers. */
typedef enum
{
  OS_SPINLOCKID_COUNT = 0,
  INVALID_SPINLOCK = OS_SPINLOCKID_COUNT
} SpinlockIdType;

/*! Peripheral identifiers. */
typedef enum
{
  OS_PERIPHERALID_COUNT = 0
} Os_PeripheralIdType;

/*! Barrier identifiers. */
typedef enum
{
  OS_BARRIERID_COUNT = 0
} Os_BarrierIdType;

/*! Trace thread identifiers (Tasks and ISRs inclusive system objects). */
typedef enum
{
  Os_TraceId_IdleTask_OsCore0 = 0,
  Os_TraceId_IdleTask_OsCore1 = 1,
  Os_TraceId_IdleTask_OsCore2 = 2,
  Os_TraceId_Task1000ms_Core0 = 3,
  Os_TraceId_Task1000ms_Core1 = 4,
  Os_TraceId_Task1000ms_Core2 = 5,
  Os_TraceId_Task100ms_Core0 = 6,
  Os_TraceId_Task100ms_Core1 = 7,
  Os_TraceId_Task100ms_Core2 = 8,
  Os_TraceId_Task10ms_Core0 = 9,
  Os_TraceId_Task10ms_Core1 = 10,
  Os_TraceId_Task10ms_Core2 = 11,
  Os_TraceId_Task1ms_Core0 = 12,
  Os_TraceId_Task1ms_Core1 = 13,
  Os_TraceId_Task1ms_Core2 = 14,
  Os_TraceId_Task200ms_Core0 = 15,
  Os_TraceId_Task200ms_Core1 = 16,
  Os_TraceId_Task200ms_Core2 = 17,
  Os_TraceId_Task20ms_Core0 = 18,
  Os_TraceId_Task20ms_Core1 = 19,
  Os_TraceId_Task20ms_Core2 = 20,
  Os_TraceId_Task500ms_Core0 = 21,
  Os_TraceId_Task500ms_Core1 = 22,
  Os_TraceId_Task500ms_Core2 = 23,
  Os_TraceId_Task50ms_Core0 = 24,
  Os_TraceId_Task50ms_Core1 = 25,
  Os_TraceId_Task50ms_Core2 = 26,
  Os_TraceId_Task5ms_Core0 = 27,
  Os_TraceId_Task5ms_Core1 = 28,
  Os_TraceId_Task5ms_Core2 = 29,
  Os_TraceId_TaskInit_Core0 = 30,
  Os_TraceId_TaskInit_Core1 = 31,
  Os_TraceId_TaskInit_Core2 = 32,
  Os_TraceId_TaskSchM_Core0 = 33,
  Os_TraceId_TaskSchM_Core1 = 34,
  Os_TraceId_TaskSchM_Core2 = 35,
  Os_TraceId_Adc0Sr0_Isr = 36,
  Os_TraceId_Adc1Sr0_Isr = 37,
  Os_TraceId_Adc2Sr0_Isr = 38,
  Os_TraceId_Adc3Sr0_Isr = 39,
  Os_TraceId_Adc4Sr0_Isr = 40,
  Os_TraceId_Adc5Sr0_Isr = 41,
  Os_TraceId_Adc6Sr0_Isr = 42,
  Os_TraceId_CanIsr_0 = 43,
  Os_TraceId_CounterIsr_SystemTimer_Core0 = 44,
  Os_TraceId_CounterIsr_SystemTimer_Core1 = 45,
  Os_TraceId_CounterIsr_SystemTimer_Core2 = 46,
  Os_TraceId_Isr_TIM02 = 47,
  Os_TraceId_Isr_TIM03 = 48,
  Os_TraceId_XSignalIsr_OsCore0 = 49,
  Os_TraceId_XSignalIsr_OsCore1 = 50,
  Os_TraceId_XSignalIsr_OsCore2 = 51,
  OS_TRACE_THREADID_COUNT = 52,
  OS_TRACE_INVALID_THREAD = OS_TRACE_THREADID_COUNT + 1
} Os_TraceThreadIdType;

/*! Trace spinlock identifiers (All spinlocks inclusive system objects). */
typedef enum
{
  OS_TRACE_NUMBER_OF_CONFIGURED_SPINLOCKS = OS_SPINLOCKID_COUNT,
  OS_TRACE_NUMBER_OF_ALL_SPINLOCKS = OS_SPINLOCKID_COUNT + 0,
  OS_TRACE_INVALID_SPINLOCK = OS_TRACE_NUMBER_OF_ALL_SPINLOCKS + 1
} Os_TraceSpinlockIdType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TYPES_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Types_Lcfg.h
 *********************************************************************************************************************/
