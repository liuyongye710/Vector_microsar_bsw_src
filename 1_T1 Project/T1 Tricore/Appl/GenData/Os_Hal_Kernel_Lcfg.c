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
 *              File: Os_Hal_Kernel_Lcfg.c
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_KERNEL_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Kernel_Lcfg.h"

/* Os kernel module dependencies */
#include "Os_Common.h"
#include "Os_Core.h"
#include "Os_Spinlock_Lcfg.h"

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Core_Lcfg.h"


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

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for cores (sorted by logical ID). */
CONSTP2CONST(Os_CoreConfigType, OS_CONST, OS_CONST) OsCfg_CoreRefs[OS_COREID_COUNT + 1] =
{
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore0),
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore1),
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore2),
  NULL_PTR
};

/*! Object reference table for cores (sorted by physical ID). */
CONSTP2CONST(Os_CoreConfigType, OS_CONST, OS_CONST) OsCfg_CorePhysicalRefs[OS_CFG_COREPHYSICALID_COUNT + 1] =
{
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore0),
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore1),
  OS_CORE_CASTCONFIG_COREASR_2_CORE(OsCfg_Core_OsCore2),
  NULL_PTR
};

/*! Object reference table for HAL kernel stacks. */
CONSTP2CONST(Os_Hal_ContextStackConfigType, OS_CONST, OS_CONST) OsCfg_Stack_KernelStacks[OS_CFG_COREPHYSICALID_COUNT + 1] =
{
  &OsCfg_Hal_Stack_OsCore0_Kernel,
  &OsCfg_Hal_Stack_OsCore1_Kernel,
  &OsCfg_Hal_Stack_OsCore2_Kernel,
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
 *  END OF FILE: Os_Hal_Kernel_Lcfg.c
 *********************************************************************************************************************/
