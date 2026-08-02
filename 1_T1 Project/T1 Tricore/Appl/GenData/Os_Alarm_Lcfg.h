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
 *              File: Os_Alarm_Lcfg.h
 *   Generation Time: 2020-07-28 16:23:22
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_ALARM_LCFG_H)                                                       /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_ALARM_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Alarm_Types.h"

/* Os kernel module dependencies */
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

/*! Alarm configuration data: Rte_Al_TE2_TaskSchM_Core0_0_10ms */
extern CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_10ms;

/*! Alarm configuration data: Rte_Al_TE2_TaskSchM_Core0_0_20ms */
extern CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_TaskSchM_Core0_0_20ms;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1000ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable100ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable10ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable1ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable200ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable20ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable500ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable50ms_Core0;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core0_Runnable5ms_Core0;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Alarm configuration data: Rte_Al_TE2_EcuM_EcuM_MainFunction */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_EcuM_EcuM_MainFunction;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1000ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable100ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable10ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable1ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable200ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable20ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable500ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable50ms_Core1;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core1_Runnable5ms_Core1;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Alarm configuration data: Rte_Al_TE3_EcuM_EcuM_MainFunction */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE3_EcuM_EcuM_MainFunction;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1000ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable100ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable10ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable1ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable200ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable20ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable500ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable50ms_Core2;

/*! Alarm configuration data: Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2 */
extern CONST(Os_AlarmActivateTaskConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_CpAp_FAWDemo_Core2_Runnable5ms_Core2;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for alarms. */
extern CONSTP2CONST(Os_AlarmConfigType, OS_CONST, OS_CONST) OsCfg_AlarmRefs[OS_ALARMID_COUNT + 1];

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_ALARM_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Alarm_Lcfg.h
 *********************************************************************************************************************/
