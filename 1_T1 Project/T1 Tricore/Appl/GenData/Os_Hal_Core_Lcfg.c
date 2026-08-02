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
 *              File: Os_Hal_Core_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_CORE_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Core_Lcfg.h"
#include "Os_Hal_Core.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Entry_Lcfg.h"
#include "Os_Hal_Interrupt_Lcfg.h"
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

#define OS_START_SEC_CORE0_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic core to thread data: OsCore0 */
OS_LOCAL VAR(Os_Hal_Core2ThreadType, OS_VAR_NOINIT_FAST) OsCfg_Hal_Core2Thread_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic core to thread data: OsCore1 */
OS_LOCAL VAR(Os_Hal_Core2ThreadType, OS_VAR_NOINIT_FAST) OsCfg_Hal_Core2Thread_OsCore1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL dynamic core to thread data: OsCore2 */
OS_LOCAL VAR(Os_Hal_Core2ThreadType, OS_VAR_NOINIT_FAST) OsCfg_Hal_Core2Thread_OsCore2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL core initialized interrupt sources: OsCore0 */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_Core_OsCore0_InterruptSourceRefs[OS_CFG_NUM_CORE_OSCORE0_INTERRUPTSOURCEREFS + 1] =
{
  /* No core exclusive interrupt sources to be initialized by OsCore0. */
  NULL_PTR
};


/*! HAL core configuration data: OsCore0 */
CONST(Os_Hal_CoreConfigType, OS_CONST) OsCfg_Hal_Core_OsCore0 =
{
  /* .CoreId                  = */ 0, /* Physical id of OsCore0 */
  /* .ProgramCounterRegister  = */ 0,
  /* .StartLabelAddress       = */ 0,
  /* .DBGSRRegister           = */ 0,
  /* .SYSCONRegister          = */ 0
}
;

/*! HAL AUTOSAR core configuration data: OsCore0 */
CONST(Os_Hal_CoreAsrConfigType, OS_CONST) OsCfg_Hal_CoreAsr_OsCore0 =
{
  /* .CoreId        = */ 0, /* This is the logical id of the core */
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL core initialized interrupt sources: OsCore1 */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_Core_OsCore1_InterruptSourceRefs[OS_CFG_NUM_CORE_OSCORE1_INTERRUPTSOURCEREFS + 1] =
{
  /* No core exclusive interrupt sources to be initialized by OsCore1. */
  NULL_PTR
};


/*! HAL core configuration data: OsCore1 */
CONST(Os_Hal_CoreConfigType, OS_CONST) OsCfg_Hal_Core_OsCore1 =
{
  /* .CoreId                  = */ 1, /* Physical id of OsCore1 */
  /* .ProgramCounterRegister  = */ OS_HAL_CORE1_PC,
  /* .StartLabelAddress       = */ (uint32)&(_start_tc1), /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .DBGSRRegister           = */ OS_HAL_CORE1_DBGSR,
  /* .SYSCONRegister          = */ OS_HAL_CORE1_SYSCON
}
;

/*! HAL AUTOSAR core configuration data: OsCore1 */
CONST(Os_Hal_CoreAsrConfigType, OS_CONST) OsCfg_Hal_CoreAsr_OsCore1 =
{
  /* .CoreId        = */ 1, /* This is the logical id of the core */
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL core initialized interrupt sources: OsCore2 */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_Core_OsCore2_InterruptSourceRefs[OS_CFG_NUM_CORE_OSCORE2_INTERRUPTSOURCEREFS + 1] =
{
  /* No core exclusive interrupt sources to be initialized by OsCore2. */
  NULL_PTR
};


/*! HAL core configuration data: OsCore2 */
CONST(Os_Hal_CoreConfigType, OS_CONST) OsCfg_Hal_Core_OsCore2 =
{
  /* .CoreId                  = */ 2, /* Physical id of OsCore2 */
  /* .ProgramCounterRegister  = */ OS_HAL_CORE2_PC,
  /* .StartLabelAddress       = */ (uint32)&(_start_tc2), /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  /* .DBGSRRegister           = */ OS_HAL_CORE2_DBGSR,
  /* .SYSCONRegister          = */ OS_HAL_CORE2_SYSCON
}
;

/*! HAL AUTOSAR core configuration data: OsCore2 */
CONST(Os_Hal_CoreAsrConfigType, OS_CONST) OsCfg_Hal_CoreAsr_OsCore2 =
{
  /* .CoreId        = */ 2, /* This is the logical id of the core */
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL core to thread configuration data. */
CONST(Os_Hal_Core2ThreadConfigType, OS_CONST) OsCfg_Hal_Core2Thread =
{
  /* .Core2Thread = */
  {
    &OsCfg_Hal_Core2Thread_OsCore0_Dyn, /* OS_CORE_ID_0 */
    &OsCfg_Hal_Core2Thread_OsCore1_Dyn, /* OS_CORE_ID_1 */
    &OsCfg_Hal_Core2Thread_OsCore2_Dyn, /* OS_CORE_ID_2 */
  }
};

/*! HAL system configuration data. */
CONST(Os_Hal_SystemConfigType, OS_CONST) OsCfg_Hal_System =
0;

/*! Interrupt sources which are initialized by the hardware init core. */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_System_InterruptSourceRefs[OS_CFG_NUM_SYSTEM_INTERRUPTSOURCEREFS + 1] =
{
  &OsCfg_Hal_IntIsr_Adc0Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc1Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc2Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc3Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc4Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc5Sr0_Isr,
  &OsCfg_Hal_IntIsr_Adc6Sr0_Isr,
  &OsCfg_Hal_IntIsr_CanIsr_0,
  &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core0,
  &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core1,
  &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core2,
  &OsCfg_Hal_IntIsr_Isr_TIM02,
  &OsCfg_Hal_IntIsr_Isr_TIM03,
  &OsCfg_Hal_IntIsr_XSignalIsr_OsCore0,
  &OsCfg_Hal_IntIsr_XSignalIsr_OsCore1,
  &OsCfg_Hal_IntIsr_XSignalIsr_OsCore2,
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
 *  END OF FILE: Os_Hal_Core_Lcfg.c
 *********************************************************************************************************************/

