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
 *              File: Os_Isr_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_ISR_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Isr_Lcfg.h"
#include "Os_Isr.h"

/* Os kernel module dependencies */
#include "Os_AccessCheck_Lcfg.h"
#include "Os_Application_Lcfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"
#include "Os_Counter_Lcfg.h"
#include "Os_MemoryProtection_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Thread.h"
#include "Os_Timer.h"
#include "Os_TimingProtection_Lcfg.h"
#include "Os_Trace_Lcfg.h"
#include "Os_XSignal_Lcfg.h"
#include "Os_XSignal.h"

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"
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

/*! Dynamic ISR data: CanIsr_0 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CanIsr_0_Dyn;

/*! Dynamic ISR data: CounterIsr_SystemTimer_Core0 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_Core0_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore0 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic ISR data: Adc0Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc0Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc1Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc1Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc2Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc2Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc3Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc3Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc4Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc4Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc5Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc5Sr0_Isr_Dyn;

/*! Dynamic ISR data: Adc6Sr0_Isr */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Adc6Sr0_Isr_Dyn;

/*! Dynamic ISR data: CounterIsr_SystemTimer_Core1 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_Core1_Dyn;

/*! Dynamic ISR data: Isr_TIM02 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Isr_TIM02_Dyn;

/*! Dynamic ISR data: Isr_TIM03 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_Isr_TIM03_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore1 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Dynamic ISR data: CounterIsr_SystemTimer_Core2 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_Core2_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore2 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore2_Dyn;

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

/*! ISR configuration data: CanIsr_0 */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_CanIsr_0 =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CanIsr_0,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore0_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CanIsr_0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_CanIsr_0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_CanIsr_0,
  /* .IsrId    = */ CanIsr_0
};
/*! ISR configuration data: CounterIsr_SystemTimer_Core0 */
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_Core0 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_Core0,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore0_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_Core0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core0,
  /* .IsrId    = */ CounterIsr_SystemTimer_Core0
},
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core0)
};
/*! ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0 =
{
  /* .Isr           = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore0_Isr_Level3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_XSignalIsr_OsCore0,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore0,
  /* .IsrId    = */ XSignalIsr_OsCore0
},
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore0_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore0_PortRefs,
  /* .RecvPortCount = */ OS_CFG_NUM_ISR_XSIGNALISR_OSCORE0_PORTS,
  /* .IntTrigger    = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore0
};
#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! ISR configuration data: Adc0Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc0Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc0Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level5_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc0Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc0Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc0Sr0_Isr,
  /* .IsrId    = */ Adc0Sr0_Isr
};
/*! ISR configuration data: Adc1Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc1Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc1Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level6_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc1Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc1Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc1Sr0_Isr,
  /* .IsrId    = */ Adc1Sr0_Isr
};
/*! ISR configuration data: Adc2Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc2Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc2Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level7_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc2Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc2Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc2Sr0_Isr,
  /* .IsrId    = */ Adc2Sr0_Isr
};
/*! ISR configuration data: Adc3Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc3Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc3Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level8_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc3Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc3Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc3Sr0_Isr,
  /* .IsrId    = */ Adc3Sr0_Isr
};
/*! ISR configuration data: Adc4Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc4Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc4Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level9_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc4Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc4Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc4Sr0_Isr,
  /* .IsrId    = */ Adc4Sr0_Isr
};
/*! ISR configuration data: Adc5Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc5Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc5Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level10_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc5Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc5Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc5Sr0_Isr,
  /* .IsrId    = */ Adc5Sr0_Isr
};
/*! ISR configuration data: Adc6Sr0_Isr */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Adc6Sr0_Isr =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Adc6Sr0_Isr,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level11_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Adc6Sr0_Isr_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Adc6Sr0_Isr,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Adc6Sr0_Isr,
  /* .IsrId    = */ Adc6Sr0_Isr
};
/*! ISR configuration data: CounterIsr_SystemTimer_Core1 */
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_Core1 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_Core1,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_Core1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core1,
  /* .IsrId    = */ CounterIsr_SystemTimer_Core1
},
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core1)
};
/*! ISR configuration data: Isr_TIM02 */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Isr_TIM02 =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Isr_TIM02,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level3_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Isr_TIM02_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Isr_TIM02,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Isr_TIM02,
  /* .IsrId    = */ Isr_TIM02
};
/*! ISR configuration data: Isr_TIM03 */
CONST(Os_IsrConfigType, OS_CONST) OsCfg_Isr_Isr_TIM03 =
{
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_Isr_TIM03,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level4_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_Isr_TIM03_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_OsApplication_Core1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_Isr_TIM03,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_Isr_TIM03,
  /* .IsrId    = */ Isr_TIM03
};
/*! ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1 =
{
  /* .Isr           = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_XSignalIsr_OsCore1,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore1,
  /* .IsrId    = */ XSignalIsr_OsCore1
},
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore1_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore1_PortRefs,
  /* .RecvPortCount = */ OS_CFG_NUM_ISR_XSIGNALISR_OSCORE1_PORTS,
  /* .IntTrigger    = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore1
};
#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! ISR configuration data: CounterIsr_SystemTimer_Core2 */
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_Core2 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_Core2,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore2_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_Core2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_CounterIsr_SystemTimer_Core2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core2,
  /* .IsrId    = */ CounterIsr_SystemTimer_Core2
},
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_Core2)
};
/*! ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2 =
{
  /* .Isr           = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore2_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ &OsCfg_Trace_XSignalIsr_OsCore2,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .HwConfig = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore2,
  /* .IsrId    = */ XSignalIsr_OsCore2
},
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore2_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore2_PortRefs,
  /* .RecvPortCount = */ OS_CFG_NUM_ISR_XSIGNALISR_OSCORE2_PORTS,
  /* .IntTrigger    = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore2
};
#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for category 2 ISRs. */
CONSTP2CONST(Os_IsrConfigType, OS_CONST, OS_CONST) OsCfg_IsrRefs[OS_ISRID_COUNT + 1] =
{
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc0Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc1Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc2Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc3Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc4Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc5Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Adc6Sr0_Isr),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_CanIsr_0),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_Core0),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_Core1),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_Core2),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Isr_TIM02),
  OS_ISR_CASTCONFIG_ISR_2_ISR(OsCfg_Isr_Isr_TIM03),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore0),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore1),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore2),
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
 *  END OF FILE: Os_Isr_Lcfg.c
 *********************************************************************************************************************/
