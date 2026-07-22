/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_ExecCtrl_Impl.h
 *        \brief  vSwUpdM_ExecCtrl implementation header file
 *      \details  vSwUpdM_ExecCtrl subcomponent public inline implementations.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_EXECCTRL_IMPL_H)
# define VSWUPDM_EXECCTRL_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExecCtrl interface header */
#include "vSwUpdM_ExecCtrl_If.h"

/* Other MultipleUnits used by ExecCtrl_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Queue.h"

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
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(vSwUpdM_JobType, VSWUPDM_VAR_NOINIT)            vSwUpdM_Jobs[VSWUPDM_JOB_TYPE_COUNT];
extern VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_JobQueue;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_ExctSchedule_IsSlotFree()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_StdReturnType, VSWUPDM_CODE) vSwUpdM_ExctSchedule_IsSlotFree(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /*!
   * Internal comment removed.
 *
 *
   */
  return (vSwUpdM_StdReturnType)(vSwUpdM_QueueIsEmpty(&vSwUpdM_JobQueue)); /* PRQA S 4304 */ /* MD_vSwUpdM_Rule10.5_4304_PassingBooleanValue */
}

/**********************************************************************************************************************
 *  vSwUpdM_ExctSchedule_IsJobRunningInSlot()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_StdReturnType, VSWUPDM_CODE) vSwUpdM_ExctSchedule_IsJobRunningInSlot( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobTypeType JobType)
{
  /*!
   * Internal comment removed.
 *
 *
   */
  return (vSwUpdM_StdReturnType)(vSwUpdM_Jobs[JobType].QueueHandle != (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE); /* PRQA S 4304 */ /* MD_vSwUpdM_Rule10.5_4304_PassingBooleanValue */
}

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXECCTRL_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExecCtrl_Impl.h
 *********************************************************************************************************************/
