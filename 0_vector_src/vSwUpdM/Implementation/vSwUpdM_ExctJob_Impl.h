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
/*!        \file  vSwUpdM_ExctJob_Impl.h
 *        \brief  vSwUpdM_ExctJob implementation header file
 *      \details  vSwUpdM_ExctJob subcomponent public inline implementations.
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

#if !defined (VSWUPDM_EXCTJOB_IMPL_H)
# define VSWUPDM_EXCTJOB_IMPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExctJob interface header */
#include "vSwUpdM_ExctJob_If.h"

/* Implementation header of containing MultipleUnit */
#include "vSwUpdM_ExecCtrl_Impl.h"

/* Other MultipleUnits used by ExctJob_Impl (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Queue.h"

#include "vSwUpdM_Lcfg.h"

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

extern VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_SuspendedJobQueue;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_Job_InitVolatileAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_InitVolatileAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobTypeType JobType)
{
  /* #10 Initialize job attributes with default values. */
  vSwUpdM_Jobs[JobType].State              = VSWUPDM_JOB_STATE_INITIAL;
  vSwUpdM_Jobs[JobType].Result             = E_OK;
  vSwUpdM_Jobs[JobType].PendingLength      = VSWUPDM_UNDEFINED_LENGTH;
  vSwUpdM_Jobs[JobType].LinkedResult       = NULL_PTR;
  vSwUpdM_Jobs[JobType].UpdateResumeInfo   = TRUE;
  vSwUpdM_Jobs[JobType].HookAction         = VSWUPDM_HOOK_ACTION_DEFAULT;
  vSwUpdM_Jobs[JobType].RetryCount         = 0u;
  vSwUpdM_Jobs[JobType].RetryGranularity   = VSWUPDM_RETRY_GRANULARITY_DEFAULT;
  vSwUpdM_Jobs[JobType].Phase              = VSWUPDM_JOB_PHASE_PRE_HOOK;
  vSwUpdM_Jobs[JobType].RemoteServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
  vSwUpdM_Jobs[JobType].RemoteTargetGroup  = VSWUPDM_INVALID_NODE_GROUP;
  vSwUpdM_Jobs[JobType].RemoteTarget       = VSWUPDM_INVALID_NODE;
  vSwUpdM_Jobs[JobType].SequenceIdx        = VSWUPDM_EXECCTRL_SEQUENCEIDX_INVALID;

  /* #20 Reset child result. */
  vSwUpdM_Job_ResetLinkedResult(&vSwUpdM_Jobs[JobType].ChildResult);
} /* vSwUpdM_Job_InitVolatileAttributes */

/**********************************************************************************************************************
 * vSwUpdM_Job_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_Init( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_ServiceIdType ServiceId,
  vSwUpdM_QueuePrioType Priority,
  boolean Suspendable)
{
  /* #10 Initialize non-compound members with default values. */
  vSwUpdM_Jobs[JobType].Operation           = VSWUPDM_JOB_OPERATION_DEFAULT;
  vSwUpdM_Jobs[JobType].CurrentPrio         = (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT;
  vSwUpdM_Jobs[JobType].Segmentation        = VSWUPDM_UNDEFINED_LENGTH;
  vSwUpdM_Jobs[JobType].QueueHandle         = (vSwUpdM_QueueHandleType)VSWUPDM_QUEUE_HANDLE_NONE;
  vSwUpdM_Jobs[JobType].TargetAddress       = VSWUPDM_UNDEFINED_ADDRESS;
  vSwUpdM_Jobs[JobType].InputBuffer         = NULL_PTR;
  vSwUpdM_Jobs[JobType].OutputBuffer        = NULL_PTR;
  vSwUpdM_Jobs[JobType].ConfirmationService = VSWUPDM_SID_NONE;
  vSwUpdM_Jobs[JobType].PreHookFct          = NULL_PTR;
  vSwUpdM_Jobs[JobType].PostHookFct         = NULL_PTR;
  /* #20 Initialize job attributes with default values. */
  vSwUpdM_Job_InitVolatileAttributes(JobType);

  /* #30 Assign job specific members passed in parameters. */
  vSwUpdM_Jobs[JobType].Type                = JobType;
  vSwUpdM_Jobs[JobType].DefaultPrio         = Priority;
  vSwUpdM_Jobs[JobType].ServiceId           = ServiceId;
  vSwUpdM_Jobs[JobType].Suspendable         = Suspendable;

  /* #40 Initialize entity IDs with default values. */
  vSwUpdM_Init_EntityIdsDefaults(&vSwUpdM_Jobs[JobType].EntityIds);
} /* vSwUpdM_Job_Init */

/**********************************************************************************************************************
 * vSwUpdM_Job_LinkParentJobResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_LinkParentJobResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType Job,
  vSwUpdM_JobPtrType ParentJob)
{
  if (ParentJob != NULL_PTR)
  {
    vSwUpdM_Job_LinkResult(Job, &ParentJob->ChildResult);
  }
} /* vSwUpdM_JobHandler_LinkParentJobResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_SetLinkedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetLinkedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult,
  Std_ReturnType Result,
  vSwUpdM_AddressType TargetAddress)
{
  /* #10 If linked result is passed */
  if (LinkedResult != NULL_PTR)
  {
    /* #20 If linked result wasn't set yet (not valid) or doesn't hold an error (is OK or suspended) */
    if ( (LinkedResult->Valid == FALSE)
      || (LinkedResult->Result == E_OK)
      || (LinkedResult->Result == VSWUPDM_E_SUSPENDED) )
    {
      /* #30 Assign passed result and target address to linked result and set valid. */
      LinkedResult->Result        = Result;
      LinkedResult->TargetAddress = TargetAddress;
      LinkedResult->Valid         = TRUE;
    }
  }
} /* vSwUpdM_JobHandler_SetLinkedResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_UpdateLinkedResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_UpdateLinkedResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType Job) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  vSwUpdM_Job_SetLinkedResult(Job->LinkedResult, Job->Result, Job->TargetAddress);
} /* vSwUpdM_JobHandler_UpdateLinkedResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_ResetChildResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ResetChildResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType Job)
{
  vSwUpdM_Job_ResetLinkedResult(&Job->ChildResult);
} /* vSwUpdM_JobHandler_ResetChildResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_ApplyChildResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ApplyChildResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType Job,
  boolean ApplyAddress)
{
  /* #10 If child result of passed job is valid */
  if (Job->ChildResult.Valid == TRUE)
  {
    /* #20 Assign value of child result to job result. */
    Job->Result = Job->ChildResult.Result;

    /* #30 If address shall be applied, assign target address of child result to job target address. */
    if (ApplyAddress == TRUE)
    {
      Job->TargetAddress = Job->ChildResult.TargetAddress;
    }

    /* #40 Reset child result. */
    vSwUpdM_Job_ResetChildResult(Job);
  }
} /* vSwUpdM_JobHandler_ApplyChildResult */

/**********************************************************************************************************************
 * vSwUpdM_Job_EvaluateChildResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateChildResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType Job)
{
  return vSwUpdM_Job_EvaluateResult(&Job->ChildResult);
} /* vSwUpdM_JobHandler_EvaluateChildResult */

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXCTJOB_IMPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExctJob_Impl.h
 *********************************************************************************************************************/
