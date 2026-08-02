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
 *              File: Os_Task_Lcfg.c
 *   Generation Time: 2020-07-28 16:23:29
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_TASK_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Task_Lcfg.h"
#include "Os_Task.h"

/* Os kernel module dependencies */
#include "Os_AccessCheck_Lcfg.h"
#include "Os_Application_Lcfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"
#include "Os_Core.h"
#include "Os_Error.h"
#include "Os_Ioc.h"
#include "Os_Lcfg.h"
#include "Os_MemoryProtection_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Thread.h"
#include "Os_TimingProtection_Lcfg.h"
#include "Os_Trace_Lcfg.h"

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"


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

/*! Dynamic task data: IdleTask_OsCore0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore0_Dyn;

/*! Dynamic task data: Task1000ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1000ms_Core0_Dyn;

/*! Dynamic task data: Task100ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task100ms_Core0_Dyn;

/*! Dynamic task data: Task10ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task10ms_Core0_Dyn;

/*! Dynamic task data: Task1ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1ms_Core0_Dyn;

/*! Dynamic task data: Task200ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task200ms_Core0_Dyn;

/*! Dynamic task data: Task20ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task20ms_Core0_Dyn;

/*! Dynamic task data: Task500ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task500ms_Core0_Dyn;

/*! Dynamic task data: Task50ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task50ms_Core0_Dyn;

/*! Dynamic task data: Task5ms_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task5ms_Core0_Dyn;

/*! Dynamic task data: TaskInit_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskInit_Core0_Dyn;

/*! Dynamic task data: TaskSchM_Core0 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskSchM_Core0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic task data: IdleTask_OsCore1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore1_Dyn;

/*! Dynamic task data: Task1000ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1000ms_Core1_Dyn;

/*! Dynamic task data: Task100ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task100ms_Core1_Dyn;

/*! Dynamic task data: Task10ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task10ms_Core1_Dyn;

/*! Dynamic task data: Task1ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1ms_Core1_Dyn;

/*! Dynamic task data: Task200ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task200ms_Core1_Dyn;

/*! Dynamic task data: Task20ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task20ms_Core1_Dyn;

/*! Dynamic task data: Task500ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task500ms_Core1_Dyn;

/*! Dynamic task data: Task50ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task50ms_Core1_Dyn;

/*! Dynamic task data: Task5ms_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task5ms_Core1_Dyn;

/*! Dynamic task data: TaskInit_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskInit_Core1_Dyn;

/*! Dynamic task data: TaskSchM_Core1 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskSchM_Core1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic task data: IdleTask_OsCore2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_IdleTask_OsCore2_Dyn;

/*! Dynamic task data: Task1000ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1000ms_Core2_Dyn;

/*! Dynamic task data: Task100ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task100ms_Core2_Dyn;

/*! Dynamic task data: Task10ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task10ms_Core2_Dyn;

/*! Dynamic task data: Task1ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task1ms_Core2_Dyn;

/*! Dynamic task data: Task200ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task200ms_Core2_Dyn;

/*! Dynamic task data: Task20ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task20ms_Core2_Dyn;

/*! Dynamic task data: Task500ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task500ms_Core2_Dyn;

/*! Dynamic task data: Task50ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task50ms_Core2_Dyn;

/*! Dynamic task data: Task5ms_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_Task5ms_Core2_Dyn;

/*! Dynamic task data: TaskInit_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskInit_Core2_Dyn;

/*! Dynamic task data: TaskSchM_Core2 */
OS_LOCAL VAR(Os_TaskType, OS_VAR_NOINIT) OsCfg_Task_TaskSchM_Core2_Dyn;

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

/*! Task configuration data: IdleTask_OsCore0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_IdleTask_OsCore0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 11UL,
  /* .TaskId                = */ IdleTask_OsCore0,
  /* .RunningPriority       = */ 11UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1000ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1000ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task1000ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio51,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1000ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1000ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 10UL,
  /* .TaskId                = */ Task1000ms_Core0,
  /* .RunningPriority       = */ 10UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task100ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task100ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task100ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio54,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task100ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task100ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 7UL,
  /* .TaskId                = */ Task100ms_Core0,
  /* .RunningPriority       = */ 7UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task10ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task10ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task10ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio57,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task10ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task10ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 4UL,
  /* .TaskId                = */ Task10ms_Core0,
  /* .RunningPriority       = */ 4UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task1ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio59,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 2UL,
  /* .TaskId                = */ Task1ms_Core0,
  /* .RunningPriority       = */ 2UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task200ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task200ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task200ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio53,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task200ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task200ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 8UL,
  /* .TaskId                = */ Task200ms_Core0,
  /* .RunningPriority       = */ 8UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task20ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task20ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task20ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio56,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task20ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task20ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 5UL,
  /* .TaskId                = */ Task20ms_Core0,
  /* .RunningPriority       = */ 5UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task500ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task500ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task500ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio52,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task500ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task500ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 9UL,
  /* .TaskId                = */ Task500ms_Core0,
  /* .RunningPriority       = */ 9UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task50ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task50ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task50ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio55,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task50ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task50ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 6UL,
  /* .TaskId                = */ Task50ms_Core0,
  /* .RunningPriority       = */ 6UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task5ms_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task5ms_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_Task5ms_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio58,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task5ms_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task5ms_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 3UL,
  /* .TaskId                = */ Task5ms_Core0,
  /* .RunningPriority       = */ 3UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskInit_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskInit_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_TaskInit_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Task_Prio100,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskInit_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskInit_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 0UL,
  /* .TaskId                = */ TaskInit_Core0,
  /* .RunningPriority       = */ 0UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskSchM_Core0 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core0 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskSchM_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_TaskSchM_Core0_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_TaskSchM_Core0,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskSchM_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskSchM_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 1UL,
  /* .TaskId                = */ TaskSchM_Core0,
  /* .RunningPriority       = */ 1UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ TRUE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task configuration data: IdleTask_OsCore1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_IdleTask_OsCore1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 11UL,
  /* .TaskId                = */ IdleTask_OsCore1,
  /* .RunningPriority       = */ 11UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1000ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1000ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task1000ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio51,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1000ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1000ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 10UL,
  /* .TaskId                = */ Task1000ms_Core1,
  /* .RunningPriority       = */ 10UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task100ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task100ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task100ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio54,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task100ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task100ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 7UL,
  /* .TaskId                = */ Task100ms_Core1,
  /* .RunningPriority       = */ 7UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task10ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task10ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task10ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio57,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task10ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task10ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 4UL,
  /* .TaskId                = */ Task10ms_Core1,
  /* .RunningPriority       = */ 4UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task1ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio59,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 2UL,
  /* .TaskId                = */ Task1ms_Core1,
  /* .RunningPriority       = */ 2UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task200ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task200ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task200ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio53,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task200ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task200ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 8UL,
  /* .TaskId                = */ Task200ms_Core1,
  /* .RunningPriority       = */ 8UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task20ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task20ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task20ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio56,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task20ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task20ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 5UL,
  /* .TaskId                = */ Task20ms_Core1,
  /* .RunningPriority       = */ 5UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task500ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task500ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task500ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio52,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task500ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task500ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 9UL,
  /* .TaskId                = */ Task500ms_Core1,
  /* .RunningPriority       = */ 9UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task50ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task50ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task50ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio55,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task50ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task50ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 6UL,
  /* .TaskId                = */ Task50ms_Core1,
  /* .RunningPriority       = */ 6UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task5ms_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task5ms_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_Task5ms_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio58,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task5ms_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task5ms_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 3UL,
  /* .TaskId                = */ Task5ms_Core1,
  /* .RunningPriority       = */ 3UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskInit_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskInit_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_TaskInit_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio100,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskInit_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskInit_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 0UL,
  /* .TaskId                = */ TaskInit_Core1,
  /* .RunningPriority       = */ 0UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskSchM_Core1 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core1 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskSchM_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_TaskSchM_Core1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Task_Prio90,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskSchM_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskSchM_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 1UL,
  /* .TaskId                = */ TaskSchM_Core1,
  /* .RunningPriority       = */ 1UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Task configuration data: IdleTask_OsCore2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_IdleTask_OsCore2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_IdleTask_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_IdleTask_OsCore2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio4294967295,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_IdleTask_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_IdleTask_OsCore2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 11UL,
  /* .TaskId                = */ IdleTask_OsCore2,
  /* .RunningPriority       = */ 11UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1000ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1000ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1000ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task1000ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio51,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1000ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1000ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 10UL,
  /* .TaskId                = */ Task1000ms_Core2,
  /* .RunningPriority       = */ 10UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task100ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task100ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task100ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task100ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio54,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task100ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task100ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 7UL,
  /* .TaskId                = */ Task100ms_Core2,
  /* .RunningPriority       = */ 7UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task10ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task10ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task10ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task10ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio57,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task10ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task10ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 4UL,
  /* .TaskId                = */ Task10ms_Core2,
  /* .RunningPriority       = */ 4UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task1ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task1ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task1ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task1ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio59,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task1ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task1ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 2UL,
  /* .TaskId                = */ Task1ms_Core2,
  /* .RunningPriority       = */ 2UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task200ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task200ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task200ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task200ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio53,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task200ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task200ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 8UL,
  /* .TaskId                = */ Task200ms_Core2,
  /* .RunningPriority       = */ 8UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task20ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task20ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task20ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task20ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio56,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task20ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task20ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 5UL,
  /* .TaskId                = */ Task20ms_Core2,
  /* .RunningPriority       = */ 5UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task500ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task500ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task500ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task500ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio52,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task500ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task500ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 9UL,
  /* .TaskId                = */ Task500ms_Core2,
  /* .RunningPriority       = */ 9UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task50ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task50ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task50ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task50ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio55,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task50ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task50ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 6UL,
  /* .TaskId                = */ Task50ms_Core2,
  /* .RunningPriority       = */ 6UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: Task5ms_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_Task5ms_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Task5ms_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_Task5ms_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio58,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_Task5ms_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Task5ms_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 3UL,
  /* .TaskId                = */ Task5ms_Core2,
  /* .RunningPriority       = */ 3UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskInit_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskInit_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskInit_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_TaskInit_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio100,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskInit_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskInit_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 0UL,
  /* .TaskId                = */ TaskInit_Core2,
  /* .RunningPriority       = */ 0UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_ANY,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

/*! Task configuration data: TaskSchM_Core2 */
CONST(Os_TaskConfigType, OS_CONST) OsCfg_Task_TaskSchM_Core2 =
{
  /* .Thread                = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_TaskSchM_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_TaskSchM_Core2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Task_Prio90,
    /* .Dyn                   = */ OS_TASK_CASTDYN_TASK_2_THREAD(OsCfg_Task_TaskSchM_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_TaskSchM_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_TASK,
    /* .PreThreadHook         = */ &Os_TaskCallPreTaskHook,
    /* .InitDuringStartUp     = */ TRUE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HomePriority          = */ 1UL,
  /* .TaskId                = */ TaskSchM_Core2,
  /* .RunningPriority       = */ 1UL,
  /* .MaxActivations        = */ 1UL,
  /* .AutostartModes        = */ OS_APPMODE_NONE,
  /* .AccessingApplications = */ (OS_APPID2MASK(OsApplication_Core0)
        | OS_APPID2MASK(OsApplication_Core1)
        | OS_APPID2MASK(OsApplication_Core2)
        | OS_APPID2MASK(SystemApplication_OsCore0)
        | OS_APPID2MASK(SystemApplication_OsCore1)
        | OS_APPID2MASK(SystemApplication_OsCore2)),
  /* .IsExtended            = */ FALSE,
  /* .StackSharing          = */ OS_TASKSCHEDULE_ALLOWED
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for tasks. */
CONSTP2CONST(Os_TaskConfigType, OS_CONST, OS_CONST) OsCfg_TaskRefs[OS_TASKID_COUNT + 1] =
{
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_IdleTask_OsCore2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1000ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1000ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1000ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task100ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task100ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task100ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task10ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task10ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task10ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task1ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task200ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task200ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task200ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task20ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task20ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task20ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task500ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task500ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task500ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task50ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task50ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task50ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task5ms_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task5ms_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_Task5ms_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskInit_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskInit_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskInit_Core2),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskSchM_Core0),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskSchM_Core1),
  OS_TASK_CASTCONFIG_TASK_2_TASK(OsCfg_Task_TaskSchM_Core2),
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
 *  END OF FILE: Os_Task_Lcfg.c
 *********************************************************************************************************************/
