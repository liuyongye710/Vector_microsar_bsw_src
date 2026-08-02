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
/*!        \file  vSwUpdM_ExecCtrl_If.h
 *        \brief  vSwUpdM_ExecCtrl interface header file
 *      \details  Interface provided by the vSwUpdM_ExecCtrl subcomponent.
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

#if !defined (VSWUPDM_EXECCTRL_IF_H)
# define VSWUPDM_EXECCTRL_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExecCtrl types header */
#include "vSwUpdM_ExecCtrl_Types.h"

/* Other MultipleUnits used by ExecCtrl_If (Prefer smallest set required, i.e. prefer _Types over _If) */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/*! Job handler function signature. */
#define VSWUPDM_JOB_HANDLER_SIG(name)   FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) name( \
  vSwUpdM_StateType   ActiveState,                                                      \
  vSwUpdM_JobPtrType  ActiveJob,                                                        \
  vSwUpdM_LengthType  ProcessingLength )

/*! Job handler function declaration. */
#define VSWUPDM_JOB_HANDLER(name)       VSWUPDM_LOCAL VSWUPDM_JOB_HANDLER_SIG(name)
#define VSWUPDM_SUB_JOB_HANDLER(name)   VSWUPDM_LOCAL_INLINE VSWUPDM_JOB_HANDLER_SIG(name)

/*! Dummy statements for job handler function. */
#define VSWUPDM_DUMMY_STATEMENTS_JOB_HANDLER()  \
  VSWUPDM_DUMMY_STATEMENT(ActiveState);         \
  VSWUPDM_DUMMY_STATEMENT(ActiveJob);           \
  VSWUPDM_DUMMY_STATEMENT(ProcessingLength);

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Pointer to job handler */
typedef VSWUPDM_JOB_HANDLER_SIG((*vSwUpdM_JobHandlerType));

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_ExctSchedule_IsSlotFree()
 *********************************************************************************************************************/
/*! \brief       Determine whether a scheduling slot is free.
 *  \details     -
 *  \return      TRUE if slot is free, FALSE otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExctSchedule
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_StdReturnType, VSWUPDM_CODE) vSwUpdM_ExctSchedule_IsSlotFree(void);

/**********************************************************************************************************************
 *  vSwUpdM_ExctSchedule_IsJobRunningInSlot()
 *********************************************************************************************************************/
/*! \brief       Determine whether a certain job is running in a scheduling slot.
 *  \details     -
 *  \return      TRUE if slot is free, FALSE otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     ExctSchedule
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_StdReturnType, VSWUPDM_CODE) vSwUpdM_ExctSchedule_IsJobRunningInSlot(
  vSwUpdM_JobTypeType JobType);

/**********************************************************************************************************************
 *  vSwUpdM_Job_Spawn()
 *********************************************************************************************************************/
/*! \brief       Spawn job of given job type.
 *  \details     Insert job associated with given type into job queue. Only one job of each type can be active at a time.
 *  \param[out]  Result               E_OK: Job successfully spawned.
 *                                    E_NOT_OK: Job could not be spawned, because of an error.
 *                                    VSWUPDM_E_BUSY: Job could not be spawned,
 *                                      because a job of the requested type is already active.
 *  \param[in]   JobType              Type of job to be spawned.
 *  \param[in]   Operation               Type of operation which job should execute.
 *  \param[in]   Priority             Priority of job.
 *                                    Set to default value of job type when VSWUPDM_JOB_PRIO_DEFAULT is passed.
 *                                    Actual value otherwise.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      Pointer to spawned job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(vSwUpdM_JobPtrType, VSWUPDM_CODE) vSwUpdM_Job_Spawn(
  P2VAR(Std_ReturnType, AUTOMATIC, VSWUPDM_APPL_VAR) Result,
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_QueuePrioType Priority,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Job_LinkResult()
 *********************************************************************************************************************/
/*! \brief       Link result of job to external value.
 *  \details     Result of job is mirrored into linked external value.
 *  \param[in]   Job              Pointer to job.
 *  \param[in,out] LinkedResult   Pointer to external value which shall be linked to job result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_LinkResult(
  vSwUpdM_JobPtrType Job,
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult);

/**********************************************************************************************************************
 *  vSwUpdM_Job_ResetLinkedResult()
 *********************************************************************************************************************/
/*! \brief       Reset linked result to default values.
 *  \details     -
 *  \param[in,out]  Linked result    Pointer to linked result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_ResetLinkedResult(
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult);

/**********************************************************************************************************************
 *  vSwUpdM_Job_EvaluateResult()
 *********************************************************************************************************************/
/*! \brief       Evaluate child result.
 *  \details     Form aggregated result, based on whether child is valid and/or expected.
 *  \param[in,out]  Linked result    Pointer to linked result.
 *  \return      Child result value                     Child result valid.
 *  \return      VSWUPDM_E_JOB_INVALID_CHILD_RESULT     Child result expected, but no valid result available.
 *  \return      E_OK                                   No child result expected and none available.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Job_EvaluateResult(
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult);

/**********************************************************************************************************************
 *  vSwUpdM_Job_SetChildResult()
 *********************************************************************************************************************/
/*! \brief       Set child result of job to given values and mark valid.
 *  \details     -
 *  \param[in,out]  Job             Pointer to job.
 *  \param[in]   Result             Result to be set.
 *  \param[in]   TargetAddress      Target address to be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetChildResult(
  vSwUpdM_JobPtrType Job,
  Std_ReturnType Result,
  vSwUpdM_AddressType TargetAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Job_SetChildResultAndConfirm()
 *********************************************************************************************************************/
/*! \brief       Update child result of job and issue confirmation to upper-layer.
 *  \details     -
 *  \param[in,out]  Job               Pointer to job.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Result               Result to be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Job_SetChildResultAndConfirm(
  vSwUpdM_JobPtrType Job,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ServiceIdType ConfirmationService,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_Init_SetupJobs()
 *********************************************************************************************************************/
/*! \brief       Sets up the job processing.
 *  \details     Initializes all queue and job objects.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_SetupJobs(void);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXECCTRL_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExecCtrl_If.h
 *********************************************************************************************************************/
