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
 *              File: Os_Task_Lcfg.h
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_TASK_LCFG_H)                                                        /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_TASK_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Task_Types.h"

/* Os kernel module dependencies */
# include "Os_Ioc_Types.h"
# include "Os_Lcfg.h"

/* Os hal dependencies */


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

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task configuration data: IdleTask_OsCore0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore0;

/*! Task configuration data: Task1000ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core0;

/*! Task configuration data: Task100ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core0;

/*! Task configuration data: Task10ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core0;

/*! Task configuration data: Task1ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core0;

/*! Task configuration data: Task200ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core0;

/*! Task configuration data: Task20ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core0;

/*! Task configuration data: Task500ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core0;

/*! Task configuration data: Task50ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core0;

/*! Task configuration data: Task5ms_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core0;

/*! Task configuration data: TaskInit_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core0;

/*! Task configuration data: TaskSchM_Core0 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core0;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task configuration data: IdleTask_OsCore1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore1;

/*! Task configuration data: Task1000ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core1;

/*! Task configuration data: Task100ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core1;

/*! Task configuration data: Task10ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core1;

/*! Task configuration data: Task1ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core1;

/*! Task configuration data: Task200ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core1;

/*! Task configuration data: Task20ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core1;

/*! Task configuration data: Task500ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core1;

/*! Task configuration data: Task50ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core1;

/*! Task configuration data: Task5ms_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core1;

/*! Task configuration data: TaskInit_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core1;

/*! Task configuration data: TaskSchM_Core1 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core1;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task configuration data: IdleTask_OsCore2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore2;

/*! Task configuration data: Task1000ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core2;

/*! Task configuration data: Task100ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core2;

/*! Task configuration data: Task10ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core2;

/*! Task configuration data: Task1ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core2;

/*! Task configuration data: Task200ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core2;

/*! Task configuration data: Task20ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core2;

/*! Task configuration data: Task500ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core2;

/*! Task configuration data: Task50ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core2;

/*! Task configuration data: Task5ms_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core2;

/*! Task configuration data: TaskInit_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core2;

/*! Task configuration data: TaskSchM_Core2 */
extern CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core2;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for tasks. */
extern CONSTP2CONST(Os_TaskConfigType, OS_CONST, OS_CONST) OsCfg_TaskRefs[OS_TASKID_COUNT + 1];

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TASK_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Task_Lcfg.h
 *********************************************************************************************************************/
