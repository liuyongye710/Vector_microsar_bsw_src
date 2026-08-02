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
 *              File: Os_Hal_Interrupt_Lcfg.c
 *   Generation Time: 2020-07-28 17:15:44
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_INTERRUPT_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Interrupt_Lcfg.h"
#include "Os_Hal_Interrupt.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Core.h"


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

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL ISR configuration data: CanIsr_0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsr_0 =
{
  /* .Level          = */ 10,
  /* .Source         = */ 0x900UL,
  /* .CoreAssignment = */ 0
};

/*! HAL ISR configuration data: CounterIsr_SystemTimer_Core0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core0 =
{
  /* .Level          = */ 3,
  /* .Source         = */ 0x490UL,
  /* .CoreAssignment = */ 0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore0 =
{
  /* .Level          = */ 18,
  /* .Source         = */ 0x1000UL,
  /* .CoreAssignment = */ 0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore0 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore0,
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL ISR configuration data: Adc0Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc0Sr0_Isr =
{
  /* .Level          = */ 50,
  /* .Source         = */ 0x980UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc1Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc1Sr0_Isr =
{
  /* .Level          = */ 51,
  /* .Source         = */ 0x990UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc2Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc2Sr0_Isr =
{
  /* .Level          = */ 52,
  /* .Source         = */ 0x9a0UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc3Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc3Sr0_Isr =
{
  /* .Level          = */ 53,
  /* .Source         = */ 0x9b0UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc4Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc4Sr0_Isr =
{
  /* .Level          = */ 54,
  /* .Source         = */ 0x9c0UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc5Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc5Sr0_Isr =
{
  /* .Level          = */ 55,
  /* .Source         = */ 0x9d0UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Adc6Sr0_Isr */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Adc6Sr0_Isr =
{
  /* .Level          = */ 56,
  /* .Source         = */ 0x9e0UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: CounterIsr_SystemTimer_Core1 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core1 =
{
  /* .Level          = */ 3,
  /* .Source         = */ 0x498UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Isr_TIM02 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Isr_TIM02 =
{
  /* .Level          = */ 30,
  /* .Source         = */ 0x1788UL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: Isr_TIM03 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_Isr_TIM03 =
{
  /* .Level          = */ 31,
  /* .Source         = */ 0x178cUL,
  /* .CoreAssignment = */ 1
};

/*! HAL ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore1 =
{
  /* .Level          = */ 18,
  /* .Source         = */ 0x1020UL,
  /* .CoreAssignment = */ 1
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore1 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore1,
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_Core2 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_Core2 =
{
  /* .Level          = */ 3,
  /* .Source         = */ 0x4a0UL,
  /* .CoreAssignment = */ 2
};

/*! HAL ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore2 =
{
  /* .Level          = */ 18,
  /* .Source         = */ 0x1040UL,
  /* .CoreAssignment = */ 2
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore2 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore2,
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
 *  END OF FILE: Os_Hal_Interrupt_Lcfg.c
 *********************************************************************************************************************/
