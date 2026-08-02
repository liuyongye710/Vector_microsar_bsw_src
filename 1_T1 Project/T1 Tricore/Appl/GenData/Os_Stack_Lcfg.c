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
 *              File: Os_Stack_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:45
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_STACK_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Stack_Cfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Stack.h"

/* Os kernel module dependencies */

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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define OS_START_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core init stack: OsCore0_Init */
/* User: [OsCore0, Os_CoreInitHook_OsCore0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Init_Dyn, OS_CFG_SIZE_OSCORE0_INIT_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ISR core global stack: OsCore0_Isr_Core */
/* User: [CanIsr_0, CounterIsr_SystemTimer_Core0, XSignalIsr_OsCore0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE0_ISR_CORE_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core kernel stack: OsCore0_Kernel */
/* User: [OsCore0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Kernel_Dyn, OS_CFG_SIZE_OSCORE0_KERNEL_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio100 */
/* User: [TaskInit_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio100_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO100_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio4294967295 */
/* User: [IdleTask_OsCore0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO4294967295_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio51 */
/* User: [Task1000ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio51_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO51_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio52 */
/* User: [Task500ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio52_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO52_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio53 */
/* User: [Task200ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio53_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO53_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio54 */
/* User: [Task100ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio54_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO54_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio55 */
/* User: [Task50ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio55_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO55_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio56 */
/* User: [Task20ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio56_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO56_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio57 */
/* User: [Task10ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio57_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO57_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio58 */
/* User: [Task5ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio58_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO58_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE0_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore0_Task_Prio59 */
/* User: [Task1ms_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore0_Task_Prio59_Dyn, OS_CFG_SIZE_OSCORE0_TASK_PRIO59_STACK);

#define OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core init stack: OsCore1_Init */
/* User: [OsCore1, Os_CoreInitHook_OsCore1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Init_Dyn, OS_CFG_SIZE_OSCORE1_INIT_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ISR core global stack: OsCore1_Isr_Core */
/* User: [Adc0Sr0_Isr, Adc1Sr0_Isr, Adc2Sr0_Isr, Adc3Sr0_Isr, Adc4Sr0_Isr, Adc5Sr0_Isr, Adc6Sr0_Isr, CounterIsr_SystemTimer_Core1, Isr_TIM02, Isr_TIM03, XSignalIsr_OsCore1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE1_ISR_CORE_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core kernel stack: OsCore1_Kernel */
/* User: [OsCore1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Kernel_Dyn, OS_CFG_SIZE_OSCORE1_KERNEL_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio100 */
/* User: [TaskInit_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio100_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO100_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio4294967295 */
/* User: [IdleTask_OsCore1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO4294967295_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio51 */
/* User: [Task1000ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio51_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO51_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio52 */
/* User: [Task500ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio52_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO52_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio53 */
/* User: [Task200ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio53_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO53_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio54 */
/* User: [Task100ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio54_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO54_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio55 */
/* User: [Task50ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio55_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO55_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio56 */
/* User: [Task20ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio56_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO56_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio57 */
/* User: [Task10ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio57_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO57_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio58 */
/* User: [Task5ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio58_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO58_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio59 */
/* User: [Task1ms_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio59_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO59_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore1_Task_Prio90 */
/* User: [TaskSchM_Core1] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore1_Task_Prio90_Dyn, OS_CFG_SIZE_OSCORE1_TASK_PRIO90_STACK);

#define OS_STOP_SEC_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core init stack: OsCore2_Init */
/* User: [OsCore2, Os_CoreInitHook_OsCore2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Init_Dyn, OS_CFG_SIZE_OSCORE2_INIT_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_INIT_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ISR core global stack: OsCore2_Isr_Core */
/* User: [CounterIsr_SystemTimer_Core2, XSignalIsr_OsCore2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Isr_Core_Dyn, OS_CFG_SIZE_OSCORE2_ISR_CORE_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_ISR_CORE_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Core kernel stack: OsCore2_Kernel */
/* User: [OsCore2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Kernel_Dyn, OS_CFG_SIZE_OSCORE2_KERNEL_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_KERNEL_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio100 */
/* User: [TaskInit_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio100_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO100_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO100_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio4294967295 */
/* User: [IdleTask_OsCore2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO4294967295_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio51 */
/* User: [Task1000ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio51_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO51_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO51_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio52 */
/* User: [Task500ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio52_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO52_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO52_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio53 */
/* User: [Task200ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio53_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO53_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO53_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio54 */
/* User: [Task100ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio54_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO54_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO54_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio55 */
/* User: [Task50ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio55_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO55_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO55_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio56 */
/* User: [Task20ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio56_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO56_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO56_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio57 */
/* User: [Task10ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio57_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO57_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO57_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio58 */
/* User: [Task5ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio58_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO58_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO58_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio59 */
/* User: [Task1ms_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio59_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO59_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO59_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_OSCORE2_TASK_PRIO90_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: OsCore2_Task_Prio90 */
/* User: [TaskSchM_Core2] */
OS_STACK_DECLARE(OsCfg_Stack_OsCore2_Task_Prio90_Dyn, OS_CFG_SIZE_OSCORE2_TASK_PRIO90_STACK);

#define OS_STOP_SEC_STACK_OSCORE2_TASK_PRIO90_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_STACK_TASKSCHM_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Shared Task stack: TaskSchM_Core0 */
/* User: [TaskSchM_Core0] */
OS_STACK_DECLARE(OsCfg_Stack_TaskSchM_Core0_Dyn, OS_CFG_SIZE_TASKSCHM_CORE0_STACK);

#define OS_STOP_SEC_STACK_TASKSCHM_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_Stacks.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Stack configuration data: OsCore0_Init */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Init =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Init_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Init_Dyn)
};

/*! Stack configuration data: OsCore0_Isr_Core */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Isr_Core =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Isr_Core_Dyn)
};

/*! Stack configuration data: OsCore0_Kernel */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Kernel =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Kernel_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio100 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio100 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio100_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio100_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio4294967295 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio4294967295 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio4294967295_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio51 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio51 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio51_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio51_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio52 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio52 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio52_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio52_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio53 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio53 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio53_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio53_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio54 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio54 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio54_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio54_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio55 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio55 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio55_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio56 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio56 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio56_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio56_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio57 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio57 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio57_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio57_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio58 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio58 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio58_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio58_Dyn)
};

/*! Stack configuration data: OsCore0_Task_Prio59 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore0_Task_Prio59 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore0_Task_Prio59_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Task_Prio59_Dyn)
};

/*! Stack configuration data: TaskSchM_Core0 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_TaskSchM_Core0 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_TaskSchM_Core0_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_TaskSchM_Core0_Dyn)
};


#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Stack configuration data: OsCore1_Init */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Init =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Init_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Init_Dyn)
};

/*! Stack configuration data: OsCore1_Isr_Core */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Isr_Core =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Isr_Core_Dyn)
};

/*! Stack configuration data: OsCore1_Kernel */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Kernel =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Kernel_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio100 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio100 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio100_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio100_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio4294967295 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio4294967295 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio4294967295_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio51 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio51 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio51_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio51_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio52 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio52 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio52_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio52_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio53 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio53 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio53_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio53_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio54 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio54 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio54_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio55 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio55 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio55_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio55_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio56 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio56 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio56_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio56_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio57 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio57 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio57_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio57_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio58 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio58 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio58_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio58_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio59 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio59 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio59_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio59_Dyn)
};

/*! Stack configuration data: OsCore1_Task_Prio90 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore1_Task_Prio90 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore1_Task_Prio90_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore1_Task_Prio90_Dyn)
};


#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Stack configuration data: OsCore2_Init */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Init =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Init_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Init_Dyn)
};

/*! Stack configuration data: OsCore2_Isr_Core */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Isr_Core =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Isr_Core_Dyn)
};

/*! Stack configuration data: OsCore2_Kernel */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Kernel =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Kernel_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio100 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio100 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio100_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio100_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio4294967295 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio4294967295 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio4294967295_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio51 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio51 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio51_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio51_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio52 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio52 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio52_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio52_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio53 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio53 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio53_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio54 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio54 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio54_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio54_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio55 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio55 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio55_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio55_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio56 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio56 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio56_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio56_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio57 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio57 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio57_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio57_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio58 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio58 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio58_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio58_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio59 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio59 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio59_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio59_Dyn)
};

/*! Stack configuration data: OsCore2_Task_Prio90 */
CONST(Os_StackConfigType, OS_CONST) OsCfg_Stack_OsCore2_Task_Prio90 =
{
  /* .LowAddress  = */ OS_STACK_GETLOWADDRESS(OsCfg_Stack_OsCore2_Task_Prio90_Dyn),
  /* .HighAddress = */ OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore2_Task_Prio90_Dyn)
};


#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
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
 *  END OF FILE: Os_Stack_Lcfg.c
 *********************************************************************************************************************/
