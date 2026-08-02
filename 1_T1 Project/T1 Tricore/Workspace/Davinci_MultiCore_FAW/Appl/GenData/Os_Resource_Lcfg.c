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
 *              File: Os_Resource_Lcfg.c
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_RESOURCE_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Resource_Lcfg.h"
#include "Os_Resource.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"

/* Os hal dependencies */
#include "Os_Hal_Interrupt_Lcfg.h"


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

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic resource data: RES_SCHEDULER_OsCore0 */
OS_LOCAL VAR(Os_ResourceType, OS_VAR_NOINIT) OsCfg_Resource_RES_SCHEDULER_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic resource data: RES_SCHEDULER_OsCore1 */
OS_LOCAL VAR(Os_ResourceType, OS_VAR_NOINIT) OsCfg_Resource_RES_SCHEDULER_OsCore1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic resource data: RES_SCHEDULER_OsCore2 */
OS_LOCAL VAR(Os_ResourceType, OS_VAR_NOINIT) OsCfg_Resource_RES_SCHEDULER_OsCore2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Resource configuration data: RES_SCHEDULER_OsCore0 */
CONST(Os_ResourceConfigType, OS_CONST) OsCfg_Resource_RES_SCHEDULER_OsCore0 =
{
  /* .Lock            = */
  {
    /* .Dyn                   = */ OS_RESOURCE_CASTDYN_RESOURCE_2_LOCK(OsCfg_Resource_RES_SCHEDULER_OsCore0_Dyn),
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .Type                  = */ OS_LOCKTYPE_RESOURCE_STANDARD
  },
  /* .Core            = */ &OsCfg_Core_OsCore0,
  /* .ResourceId      = */ RES_SCHEDULER_OsCore0,
  /* .CeilingPriority = */ 0
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Resource configuration data: RES_SCHEDULER_OsCore1 */
CONST(Os_ResourceConfigType, OS_CONST) OsCfg_Resource_RES_SCHEDULER_OsCore1 =
{
  /* .Lock            = */
  {
    /* .Dyn                   = */ OS_RESOURCE_CASTDYN_RESOURCE_2_LOCK(OsCfg_Resource_RES_SCHEDULER_OsCore1_Dyn),
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .Type                  = */ OS_LOCKTYPE_RESOURCE_STANDARD
  },
  /* .Core            = */ &OsCfg_Core_OsCore1,
  /* .ResourceId      = */ RES_SCHEDULER_OsCore1,
  /* .CeilingPriority = */ 0
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Resource configuration data: RES_SCHEDULER_OsCore2 */
CONST(Os_ResourceConfigType, OS_CONST) OsCfg_Resource_RES_SCHEDULER_OsCore2 =
{
  /* .Lock            = */
  {
    /* .Dyn                   = */ OS_RESOURCE_CASTDYN_RESOURCE_2_LOCK(OsCfg_Resource_RES_SCHEDULER_OsCore2_Dyn),
    /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
    /* .Type                  = */ OS_LOCKTYPE_RESOURCE_STANDARD
  },
  /* .Core            = */ &OsCfg_Core_OsCore2,
  /* .ResourceId      = */ RES_SCHEDULER_OsCore2,
  /* .CeilingPriority = */ 0
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for resources. */
CONSTP2CONST(Os_ResourceConfigType, OS_CONST, OS_CONST) OsCfg_ResourceRefs[OS_RESOURCEID_COUNT + 1] =
{
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore0),
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore1),
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore2),
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
 *  END OF FILE: Os_Resource_Lcfg.c
 *********************************************************************************************************************/
