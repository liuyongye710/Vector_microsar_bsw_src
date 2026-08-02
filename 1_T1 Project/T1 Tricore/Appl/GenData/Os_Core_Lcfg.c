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
 *              File: Os_Core_Lcfg.c
 *   Generation Time: 2020-07-28 16:23:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_CORE_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Core_Cfg.h"
#include "Os_Core_Lcfg.h"
#include "Os_Core.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Barrier_Lcfg.h"
#include "Os_Common.h"
#include "Os_Hook.h"
#include "Os_Ioc_Lcfg.h"
#include "Os_MemoryProtection_Lcfg.h"
#include "Os_Resource_Lcfg.h"
#include "Os_Scheduler_Lcfg.h"
#include "Os_Spinlock_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Task_Lcfg.h"
#include "Os_TimingProtection_Lcfg.h"
#include "Os_Trace_Lcfg.h"
#include "Os.h"

/* Os hal dependencies */
#include "Os_Hal_Core_Cfg.h"
#include "Os_Hal_Core_Lcfg.h"
#include "Os_Hal_Kernel_Lcfg.h"


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

#define OS_START_SEC_CORESTATUS_CORE0_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core status: OsCore0 */
OS_LOCAL VAR(Os_CoreAsrStatusType, OS_VAR_NOINIT) OsCfg_Core_OsCore0_Status_Dyn;

#define OS_STOP_SEC_CORESTATUS_CORE0_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Thread class data for: OsCore0 */
OS_LOCAL VAR(Os_ThreadClassType, OS_VAR_NOINIT) OsCfg_Core_OsCore0_ThreadClass;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core status: OsCore1 */
OS_LOCAL VAR(Os_CoreAsrStatusType, OS_VAR_NOINIT) OsCfg_Core_OsCore1_Status_Dyn;

#define OS_STOP_SEC_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Thread class data for: OsCore1 */
OS_LOCAL VAR(Os_ThreadClassType, OS_VAR_NOINIT) OsCfg_Core_OsCore1_ThreadClass;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORESTATUS_CORE2_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core status: OsCore2 */
OS_LOCAL VAR(Os_CoreAsrStatusType, OS_VAR_NOINIT) OsCfg_Core_OsCore2_Status_Dyn;

#define OS_STOP_SEC_CORESTATUS_CORE2_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Thread class data for: OsCore2 */
OS_LOCAL VAR(Os_ThreadClassType, OS_VAR_NOINIT) OsCfg_Core_OsCore2_ThreadClass;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core boot barrier: OsCore0 */
OS_LOCAL VAR(Os_CoreBootBarrierType, OS_VAR_NOINIT) OsCfg_Core_OsCore0_BootBarrier_Dyn;

/*! Dynamic core boot barrier: OsCore1 */
OS_LOCAL VAR(Os_CoreBootBarrierType, OS_VAR_NOINIT) OsCfg_Core_OsCore1_BootBarrier_Dyn;

/*! Dynamic core boot barrier: OsCore2 */
OS_LOCAL VAR(Os_CoreBootBarrierType, OS_VAR_NOINIT) OsCfg_Core_OsCore2_BootBarrier_Dyn;

#define OS_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core data: OsCore0 */
VAR(Os_CoreAsrType, OS_VAR_NOINIT) OsCfg_Core_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core data: OsCore1 */
VAR(Os_CoreAsrType, OS_VAR_NOINIT) OsCfg_Core_OsCore1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic core data: OsCore2 */
VAR(Os_CoreAsrType, OS_VAR_NOINIT) OsCfg_Core_OsCore2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for core hooks: OsCore0 */
OS_LOCAL CONST(Os_HookConfigRefType, OS_CONST) OsCfg_Core_OsCore0_HookRefs[OS_CFG_NUM_CORE_OSCORE0_HOOKS + 1] =
{
  OS_HOOK_CASTCONFIG_STATUSHOOK_2_HOOK(OsCfg_Hook_Os_CoreInitHook_OsCore0),
  NULL_PTR
};

/*! Object reference table for core applications: OsCore0 */
OS_LOCAL CONST(Os_AppConfigRefType, OS_CONST) OsCfg_Core_OsCore0_AppRefs[OS_CFG_NUM_CORE_OSCORE0_APPS + 1] =
{
  (Os_AppConfigRefType) &OsCfg_App_OsApplication_Core0,
  NULL_PTR
};

/*! Object reference table for core IOC communications: OsCore0 */
OS_LOCAL CONST(Os_IocConfigRefType, OS_CONST) OsCfg_Core_OsCore0_IocRefs[OS_CFG_NUM_CORE_OSCORE0_IOCS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core barriers: OsCore0 */
OS_LOCAL CONST(Os_BarrierBaseConfigRefType, OS_CONST) OsCfg_Core_OsCore0_BarrierRefs[OS_CFG_NUM_BARRIERS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core resources: OsCore0 */
OS_LOCAL CONST(Os_ResourceConfigRefType, OS_CONST) OsCfg_Core_OsCore0_ResourceRefs[OS_CFG_NUM_CORE_OSCORE0_RESOURCES + 1] =
{
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore0),
  NULL_PTR
};

/*! Object reference table for core stacks: OsCore0 */
OS_LOCAL CONST(Os_StackConfigRefType, OS_CONST) OsCfg_Core_OsCore0_StackRefs[OS_CFG_NUM_CORE_OSCORE0_STACKS + 1] =
{
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Init,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Isr_Core,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Kernel,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio100,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio4294967295,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio51,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio52,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio53,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio54,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio55,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio56,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio57,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio58,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore0_Task_Prio59,
  (Os_StackConfigRefType) &OsCfg_Stack_TaskSchM_Core0,
  NULL_PTR
};

/*! Core configuration data: OsCore0 */
CONST(Os_CoreAsrConfigType, OS_CONST) OsCfg_Core_OsCore0 =
{
  /* .Core              = */
  {
    /* .Status               = */ OS_CORE_CASTSTATUS_COREASRSTATUS_2_CORESTATUS(OsCfg_Core_OsCore0_Status_Dyn),
    /* .HwConfig             = */ &OsCfg_Hal_Core_OsCore0,
    /* .InterruptSourceRefs  = */ OsCfg_Hal_Core_OsCore0_InterruptSourceRefs,
    /* .InterruptSourceCount = */ OS_CFG_NUM_CORE_OSCORE0_INTERRUPTSOURCEREFS,
    /* .Id                   = */ OS_CORE_ID_0,
    /* .IsAsrCore            = */ TRUE,
    /* .IsAutostart          = */ TRUE,
    /* .IsMasterStartAllowed = */ TRUE,
    /* .HasPrivilegedHardwareAccess = */ TRUE
  },
  /* .Dyn               = */ &OsCfg_Core_OsCore0_Dyn,
  /* .Scheduler         = */ &OsCfg_Scheduler_OsCore0,
  /* .IdleTask          = */ &OsCfg_Task_IdleTask_OsCore0,
  /* .KernelApp         = */ &OsCfg_App_SystemApplication_OsCore0,
  /* .KernelStack       = */ &OsCfg_Stack_OsCore0_Kernel,
  /* .PreStartTask      = */ NULL_PTR,
  /* .StartupHookRef    = */ NULL_PTR,
  /* .ShutdownHookRef   = */ NULL_PTR,
  /* .ErrorHookRef      = */ NULL_PTR,
  /* .ProtectionHookRef = */ NULL_PTR,
  /* .InitHookRef       = */ &OsCfg_Hook_Os_CoreInitHook_OsCore0,
  /* .HookRefs          = */ OsCfg_Core_OsCore0_HookRefs,
  /* .HookCount         = */ OS_CFG_NUM_CORE_OSCORE0_HOOKS,
  /* .AppRefs           = */ OsCfg_Core_OsCore0_AppRefs,
  /* .AppCount          = */ OS_CFG_NUM_CORE_OSCORE0_APPS,
  /* .ResourceRefs      = */ OsCfg_Core_OsCore0_ResourceRefs,
  /* .ResourceCount     = */ OS_CFG_NUM_CORE_OSCORE0_RESOURCES,
  /* .HwConfig          = */ &OsCfg_Hal_CoreAsr_OsCore0,
  /* .MemoryProtection  = */ NULL_PTR,
  /* .OsMpAccessRights  = */ NULL_PTR,
  /* .TimingProtection  = */ NULL_PTR,
  /* .StackRefs         = */ OsCfg_Core_OsCore0_StackRefs,
  /* .StackCount        = */ OS_CFG_NUM_CORE_OSCORE0_STACKS,
  /* .CoreIdx           = */ OS_COREASRCOREIDX_0,
  /* .XSignal           = */ &OsCfg_XSig_OsCore0,
  /* .IocRefs           = */ OsCfg_Core_OsCore0_IocRefs,
  /* .IocCount          = */ OS_CFG_NUM_CORE_OSCORE0_IOCS,
  /* .Trace             = */ NULL_PTR,
  /* .Barrier           = */ &OsCfg_Barrier_OsCore0,
  /* .BarrierRefs       = */ OsCfg_Core_OsCore0_BarrierRefs,
  /* .BarrierCount      = */ OS_CFG_NUM_BARRIERS,
  /* .ThreadClass       = */ &OsCfg_Core_OsCore0_ThreadClass
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for core hooks: OsCore1 */
OS_LOCAL CONST(Os_HookConfigRefType, OS_CONST) OsCfg_Core_OsCore1_HookRefs[OS_CFG_NUM_CORE_OSCORE1_HOOKS + 1] =
{
  OS_HOOK_CASTCONFIG_STATUSHOOK_2_HOOK(OsCfg_Hook_Os_CoreInitHook_OsCore1),
  NULL_PTR
};

/*! Object reference table for core applications: OsCore1 */
OS_LOCAL CONST(Os_AppConfigRefType, OS_CONST) OsCfg_Core_OsCore1_AppRefs[OS_CFG_NUM_CORE_OSCORE1_APPS + 1] =
{
  (Os_AppConfigRefType) &OsCfg_App_OsApplication_Core1,
  NULL_PTR
};

/*! Object reference table for core IOC communications: OsCore1 */
OS_LOCAL CONST(Os_IocConfigRefType, OS_CONST) OsCfg_Core_OsCore1_IocRefs[OS_CFG_NUM_CORE_OSCORE1_IOCS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core barriers: OsCore1 */
OS_LOCAL CONST(Os_BarrierBaseConfigRefType, OS_CONST) OsCfg_Core_OsCore1_BarrierRefs[OS_CFG_NUM_BARRIERS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core resources: OsCore1 */
OS_LOCAL CONST(Os_ResourceConfigRefType, OS_CONST) OsCfg_Core_OsCore1_ResourceRefs[OS_CFG_NUM_CORE_OSCORE1_RESOURCES + 1] =
{
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore1),
  NULL_PTR
};

/*! Object reference table for core stacks: OsCore1 */
OS_LOCAL CONST(Os_StackConfigRefType, OS_CONST) OsCfg_Core_OsCore1_StackRefs[OS_CFG_NUM_CORE_OSCORE1_STACKS + 1] =
{
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Init,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Isr_Core,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Kernel,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio100,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio4294967295,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio51,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio52,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio53,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio54,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio55,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio56,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio57,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio58,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio59,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore1_Task_Prio90,
  NULL_PTR
};

/*! Core configuration data: OsCore1 */
CONST(Os_CoreAsrConfigType, OS_CONST) OsCfg_Core_OsCore1 =
{
  /* .Core              = */
  {
    /* .Status               = */ OS_CORE_CASTSTATUS_COREASRSTATUS_2_CORESTATUS(OsCfg_Core_OsCore1_Status_Dyn),
    /* .HwConfig             = */ &OsCfg_Hal_Core_OsCore1,
    /* .InterruptSourceRefs  = */ OsCfg_Hal_Core_OsCore1_InterruptSourceRefs,
    /* .InterruptSourceCount = */ OS_CFG_NUM_CORE_OSCORE1_INTERRUPTSOURCEREFS,
    /* .Id                   = */ OS_CORE_ID_1,
    /* .IsAsrCore            = */ TRUE,
    /* .IsAutostart          = */ FALSE,
    /* .IsMasterStartAllowed = */ FALSE,
    /* .HasPrivilegedHardwareAccess = */ FALSE
  },
  /* .Dyn               = */ &OsCfg_Core_OsCore1_Dyn,
  /* .Scheduler         = */ &OsCfg_Scheduler_OsCore1,
  /* .IdleTask          = */ &OsCfg_Task_IdleTask_OsCore1,
  /* .KernelApp         = */ &OsCfg_App_SystemApplication_OsCore1,
  /* .KernelStack       = */ &OsCfg_Stack_OsCore1_Kernel,
  /* .PreStartTask      = */ NULL_PTR,
  /* .StartupHookRef    = */ NULL_PTR,
  /* .ShutdownHookRef   = */ NULL_PTR,
  /* .ErrorHookRef      = */ NULL_PTR,
  /* .ProtectionHookRef = */ NULL_PTR,
  /* .InitHookRef       = */ &OsCfg_Hook_Os_CoreInitHook_OsCore1,
  /* .HookRefs          = */ OsCfg_Core_OsCore1_HookRefs,
  /* .HookCount         = */ OS_CFG_NUM_CORE_OSCORE1_HOOKS,
  /* .AppRefs           = */ OsCfg_Core_OsCore1_AppRefs,
  /* .AppCount          = */ OS_CFG_NUM_CORE_OSCORE1_APPS,
  /* .ResourceRefs      = */ OsCfg_Core_OsCore1_ResourceRefs,
  /* .ResourceCount     = */ OS_CFG_NUM_CORE_OSCORE1_RESOURCES,
  /* .HwConfig          = */ &OsCfg_Hal_CoreAsr_OsCore1,
  /* .MemoryProtection  = */ NULL_PTR,
  /* .OsMpAccessRights  = */ NULL_PTR,
  /* .TimingProtection  = */ NULL_PTR,
  /* .StackRefs         = */ OsCfg_Core_OsCore1_StackRefs,
  /* .StackCount        = */ OS_CFG_NUM_CORE_OSCORE1_STACKS,
  /* .CoreIdx           = */ OS_COREASRCOREIDX_1,
  /* .XSignal           = */ &OsCfg_XSig_OsCore1,
  /* .IocRefs           = */ OsCfg_Core_OsCore1_IocRefs,
  /* .IocCount          = */ OS_CFG_NUM_CORE_OSCORE1_IOCS,
  /* .Trace             = */ NULL_PTR,
  /* .Barrier           = */ &OsCfg_Barrier_OsCore1,
  /* .BarrierRefs       = */ OsCfg_Core_OsCore1_BarrierRefs,
  /* .BarrierCount      = */ OS_CFG_NUM_BARRIERS,
  /* .ThreadClass       = */ &OsCfg_Core_OsCore1_ThreadClass
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for core hooks: OsCore2 */
OS_LOCAL CONST(Os_HookConfigRefType, OS_CONST) OsCfg_Core_OsCore2_HookRefs[OS_CFG_NUM_CORE_OSCORE2_HOOKS + 1] =
{
  OS_HOOK_CASTCONFIG_STATUSHOOK_2_HOOK(OsCfg_Hook_Os_CoreInitHook_OsCore2),
  NULL_PTR
};

/*! Object reference table for core applications: OsCore2 */
OS_LOCAL CONST(Os_AppConfigRefType, OS_CONST) OsCfg_Core_OsCore2_AppRefs[OS_CFG_NUM_CORE_OSCORE2_APPS + 1] =
{
  (Os_AppConfigRefType) &OsCfg_App_OsApplication_Core2,
  NULL_PTR
};

/*! Object reference table for core IOC communications: OsCore2 */
OS_LOCAL CONST(Os_IocConfigRefType, OS_CONST) OsCfg_Core_OsCore2_IocRefs[OS_CFG_NUM_CORE_OSCORE2_IOCS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core barriers: OsCore2 */
OS_LOCAL CONST(Os_BarrierBaseConfigRefType, OS_CONST) OsCfg_Core_OsCore2_BarrierRefs[OS_CFG_NUM_BARRIERS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core resources: OsCore2 */
OS_LOCAL CONST(Os_ResourceConfigRefType, OS_CONST) OsCfg_Core_OsCore2_ResourceRefs[OS_CFG_NUM_CORE_OSCORE2_RESOURCES + 1] =
{
  OS_RESOURCE_CASTCONFIG_RESOURCE_2_RESOURCE(OsCfg_Resource_RES_SCHEDULER_OsCore2),
  NULL_PTR
};

/*! Object reference table for core stacks: OsCore2 */
OS_LOCAL CONST(Os_StackConfigRefType, OS_CONST) OsCfg_Core_OsCore2_StackRefs[OS_CFG_NUM_CORE_OSCORE2_STACKS + 1] =
{
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Init,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Isr_Core,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Kernel,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio100,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio4294967295,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio51,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio52,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio53,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio54,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio55,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio56,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio57,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio58,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio59,
  (Os_StackConfigRefType) &OsCfg_Stack_OsCore2_Task_Prio90,
  NULL_PTR
};

/*! Core configuration data: OsCore2 */
CONST(Os_CoreAsrConfigType, OS_CONST) OsCfg_Core_OsCore2 =
{
  /* .Core              = */
  {
    /* .Status               = */ OS_CORE_CASTSTATUS_COREASRSTATUS_2_CORESTATUS(OsCfg_Core_OsCore2_Status_Dyn),
    /* .HwConfig             = */ &OsCfg_Hal_Core_OsCore2,
    /* .InterruptSourceRefs  = */ OsCfg_Hal_Core_OsCore2_InterruptSourceRefs,
    /* .InterruptSourceCount = */ OS_CFG_NUM_CORE_OSCORE2_INTERRUPTSOURCEREFS,
    /* .Id                   = */ OS_CORE_ID_2,
    /* .IsAsrCore            = */ TRUE,
    /* .IsAutostart          = */ FALSE,
    /* .IsMasterStartAllowed = */ FALSE,
    /* .HasPrivilegedHardwareAccess = */ FALSE
  },
  /* .Dyn               = */ &OsCfg_Core_OsCore2_Dyn,
  /* .Scheduler         = */ &OsCfg_Scheduler_OsCore2,
  /* .IdleTask          = */ &OsCfg_Task_IdleTask_OsCore2,
  /* .KernelApp         = */ &OsCfg_App_SystemApplication_OsCore2,
  /* .KernelStack       = */ &OsCfg_Stack_OsCore2_Kernel,
  /* .PreStartTask      = */ NULL_PTR,
  /* .StartupHookRef    = */ NULL_PTR,
  /* .ShutdownHookRef   = */ NULL_PTR,
  /* .ErrorHookRef      = */ NULL_PTR,
  /* .ProtectionHookRef = */ NULL_PTR,
  /* .InitHookRef       = */ &OsCfg_Hook_Os_CoreInitHook_OsCore2,
  /* .HookRefs          = */ OsCfg_Core_OsCore2_HookRefs,
  /* .HookCount         = */ OS_CFG_NUM_CORE_OSCORE2_HOOKS,
  /* .AppRefs           = */ OsCfg_Core_OsCore2_AppRefs,
  /* .AppCount          = */ OS_CFG_NUM_CORE_OSCORE2_APPS,
  /* .ResourceRefs      = */ OsCfg_Core_OsCore2_ResourceRefs,
  /* .ResourceCount     = */ OS_CFG_NUM_CORE_OSCORE2_RESOURCES,
  /* .HwConfig          = */ &OsCfg_Hal_CoreAsr_OsCore2,
  /* .MemoryProtection  = */ NULL_PTR,
  /* .OsMpAccessRights  = */ NULL_PTR,
  /* .TimingProtection  = */ NULL_PTR,
  /* .StackRefs         = */ OsCfg_Core_OsCore2_StackRefs,
  /* .StackCount        = */ OS_CFG_NUM_CORE_OSCORE2_STACKS,
  /* .CoreIdx           = */ OS_COREASRCOREIDX_2,
  /* .XSignal           = */ &OsCfg_XSig_OsCore2,
  /* .IocRefs           = */ OsCfg_Core_OsCore2_IocRefs,
  /* .IocCount          = */ OS_CFG_NUM_CORE_OSCORE2_IOCS,
  /* .Trace             = */ NULL_PTR,
  /* .Barrier           = */ &OsCfg_Barrier_OsCore2,
  /* .BarrierRefs       = */ OsCfg_Core_OsCore2_BarrierRefs,
  /* .BarrierCount      = */ OS_CFG_NUM_BARRIERS,
  /* .ThreadClass       = */ &OsCfg_Core_OsCore2_ThreadClass
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for system spinlocks. */
OS_LOCAL CONST(Os_SpinlockConfigRefType, OS_CONST) OsCfg_SystemSpinlockRefs[OS_CFG_NUM_SYSTEM_SPINLOCKS + 1] =
{
  NULL_PTR
};

/*! Object reference table for core boot barriers. */
CONSTP2VAR(Os_CoreBootBarrierType, AUTOMATIC, OS_CONST) OsCfg_CoreBootBarrierRefs[OS_COREID_COUNT + 1] =
{
  &OsCfg_Core_OsCore0_BootBarrier_Dyn,
  &OsCfg_Core_OsCore1_BootBarrier_Dyn,
  &OsCfg_Core_OsCore2_BootBarrier_Dyn,
  NULL_PTR
};

/*! System configuration data. */
CONST(Os_SystemConfigType, OS_CONST) OsCfg_System =
{
  /* .VersionInfo      = */
  {
    /* .vendorID         = */ OS_VENDOR_ID,
    /* .moduleID         = */ OS_MODULE_ID,
    /* .sw_major_version = */ OS_SW_MAJOR_VERSION,
    /* .sw_minor_version = */ OS_SW_MINOR_VERSION,
    /* .sw_patch_version = */ OS_SW_PATCH_VERSION
  },
  /* .NumberOfAsrCores = */ OS_COREASRCOREIDX_COUNT,
  /* .SpinlockRefs     = */ OsCfg_SystemSpinlockRefs,
  /* .SpinlockCount    = */ OS_CFG_NUM_SYSTEM_SPINLOCKS,
  /* .HwConfig         = */ &OsCfg_Hal_System,
  /* .MemoryProtection = */ NULL_PTR,
  /* .InterruptSourceRefs  = */ OsCfg_Hal_System_InterruptSourceRefs,
  /* .InterruptSourceCount = */ OS_CFG_NUM_SYSTEM_INTERRUPTSOURCEREFS,
  /* .Core2Thread      = */ &OsCfg_Hal_Core2Thread
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
 *  END OF FILE: Os_Core_Lcfg.c
 *********************************************************************************************************************/
