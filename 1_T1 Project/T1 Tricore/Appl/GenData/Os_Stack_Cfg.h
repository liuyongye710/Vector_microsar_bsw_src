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
 *              File: Os_Stack_Cfg.h
 *   Generation Time: 2020-07-28 16:23:28
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_STACK_CFG_H)                                                        /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_STACK_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether stack monitoring is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_STACKMONITORING                  (STD_ON)

/*! Defines whether stack measurement is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_STACKMEASUREMENT                 (STD_OFF)

/* Configured stack sizes (Total: 46080 Byte) */
# define OS_CFG_SIZE_OSCORE0_INIT_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_ISR_CORE_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_KERNEL_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO100_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO4294967295_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO51_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO52_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO53_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO54_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO55_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO56_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO57_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO58_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE0_TASK_PRIO59_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_INIT_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_ISR_CORE_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_KERNEL_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO100_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO4294967295_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO51_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO52_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO53_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO54_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO55_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO56_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO57_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO58_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO59_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE1_TASK_PRIO90_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_INIT_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_ISR_CORE_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_KERNEL_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO100_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO4294967295_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO51_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO52_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO53_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO54_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO55_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO56_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO57_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO58_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO59_STACK     (1024UL)
# define OS_CFG_SIZE_OSCORE2_TASK_PRIO90_STACK     (1024UL)
# define OS_CFG_SIZE_TASKSCHM_CORE0_STACK     (1024UL)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_STACK_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Stack_Cfg.h
 *********************************************************************************************************************/
