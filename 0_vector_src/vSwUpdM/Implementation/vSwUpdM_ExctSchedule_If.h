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
/*!        \file  vSwUpdM_ExctSchedule_If.h
 *        \brief  vSwUpdM_ExctSchedule unit interface header file
 *      \details  Interface provided by the vSwUpdM_ExctSchedule unit.
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

#if !defined (VSWUPDM_EXCTSCHEDULE_IF_H)
# define VSWUPDM_EXCTSCHEDULE_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* ExctSchedule types header */
#include "vSwUpdM_ExctSchedule_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_ExecCtrl_If.h"

/* Other MultipleUnits used by ExctSchedule_If (Prefer smallest set required, i.e. prefer _Types over _If) */
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

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_General_ConcludeJobProcessing()
 *********************************************************************************************************************/
/*! \brief       Conclude the processing of the active job.
 *  \details     Forward job phase, depending on result of operation.
 *               Handle finished or suspended job and trigger confirmation when applicable.
 *  \param[in,out] ActiveJob    Pointer to active job.
 *  \param[in]   ActiveState    The current processing state.
 *  \param[in]   JobStatus      The status returned by the active job.
 *  \param[in]   JobPhase       The current phase of the job execution.
 *  \param[in]   Result         The result of the job execution.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_ConcludeJobProcessing(
  vSwUpdM_JobPtrType ActiveJob,
  vSwUpdM_StateType ActiveState,
  vSwUpdM_JobStatusType JobStatus,
  vSwUpdM_JobPhaseType JobPhase,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_Job_HandleDefaultRetry()
 *********************************************************************************************************************/
/*! \brief       Default retry handling of jobs initiated by hook function.
 *  \details     Allow hook actions "retry" and "restart" with default granularity.
 *  \param[in]   ActiveJob            Pointer to active job.
 *  \return      VSWUPDM_JOB_STATUS_ACTIVE        Job operation active - re-execute in same main function cycle,
 *                                                unless higher priority job was spawned.
 *  \return      VSWUPDM_JOB_STATUS_PENDING       Job operation pending - re-execute on next main function cycle.
 *  \return      VSWUPDM_JOB_STATUS_FINISHED      Job operation finished - trigger confirmation if applicable and
 *                                                remove job from queue.
 *  \return      VSWUPDM_JOB_STATUS_SUSPENDED     Job operation suspended - trigger confirmation if applicable and
 *                                                move job to suspended queue.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_HandleDefaultRetry(vSwUpdM_JobPtrType ActiveJob);

/**********************************************************************************************************************
 *  vSwUpdM_Job_HandleWriteRetry()
 *********************************************************************************************************************/
/*! \brief       Handle retry of write jobs initiated by hook function.
 *  \details     The write related jobs share a common mechanism to handle retries requested by hook functions.
 *  \param[in]   ActiveJob            Pointer to active job.
 *  \param[in]   ResumeService        Service ID to be stored in resume information.
 *  \return      VSWUPDM_JOB_STATUS_ACTIVE        Job operation active - re-execute in same main function cycle,
 *                                                unless higher priority job was spawned.
 *  \return      VSWUPDM_JOB_STATUS_PENDING       Job operation pending - re-execute on next main function cycle.
 *  \return      VSWUPDM_JOB_STATUS_FINISHED      Job operation finished - trigger confirmation if applicable and
 *                                                remove job from queue.
 *  \return      VSWUPDM_JOB_STATUS_SUSPENDED     Job operation suspended - trigger confirmation if applicable and
 *                                                move job to suspended queue.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     job
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_HandleWriteRetry(
  vSwUpdM_JobPtrType ActiveJob,
  vSwUpdM_ServiceIdType ResumeService);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_RemoteWaitForResponsesGroup
 *********************************************************************************************************************/
/*! \brief       Wait for responses from a remote group of nodes.
 *  \details     Spawns a job (of high priority) that waits for responses from a group of nodes.
 *               It finishes when all nodes have responded. The responded Result value is propagated
 *               as the jobs result to the ParentJob.
 *  \param[in]   JobType            Job to spawn for waiting.
 *  \param[in]   SourceGroupIndex   The transmitting group for this response.
 *  \param[in]   RemoteServiceIndex Defines which remote service is expected.
 *  \param[in]   ParentJob        The result will be propagated to this job.
 *  \return      E_OK if job successfully spawned.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteWaitForResponsesGroup(
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_NodeGroupIterType SourceGroupIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_JobPtrType ParentJob);
#endif

/**********************************************************************************************************************
 *  vSwUpdM_RemoteService
 *********************************************************************************************************************/
/*! \brief       Triggers transmission of remote service and waits for the response.
 *  \details     Clears the response valid flags, spawns a job to wait for the response and triggers the transmission
 *               of the remote service.
 *  \param[in]   ServiceIndex    Service that shall be transmitted.
 *  \param[in]   ServiceState    Indicate if Service shall be triggered initially or resumed after a suspend.
 *  \param[in]   TargetGroup     TargetGroup for transmission.
 *  \param[in]   ParentJob       The result will be propagated to this job.
 *  \return      E_OK on success.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_NodeGroupIterType TargetGroup,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_StoreRemoteResumeService
 *********************************************************************************************************************/
/*! \brief       Store current remote service request for eventual retransmit in case of resume.
 *  \details     -
 *  \param[in]   ServiceIndex    Service that shall be transmitted.
 *  \param[in]   TargetGroup     TargetGroup for transmission.
 *  \param[in]   Target          Target (for legacy services).
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ExecCtrl_StoreRemoteResumeService(
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_NodeGroupIterType TargetGroup,
  vSwUpdM_NodeIterType Target);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_ClearRemoteResumeService
 *********************************************************************************************************************/
/*! \brief       Clear current remote service request, no retransmission required anymore.
 *  \details     -
 *  \param[in]   ServiceIndex    Service that shall be maintained.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ExecCtrl_ClearRemoteResumeService(vSwUpdM_GridSrvc_ServiceIdxType ServiceIdx);

/**********************************************************************************************************************
 *  vSwUpdM_ExecCtrl_TriggerRemoteResumeService
 *********************************************************************************************************************/
/*! \brief       Trigger transmission of stored remote service on resume.
 *  \details     -
 *  \return      E_OK     On success.
 *  \return      E_NOT_OK Otherwise.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ExecCtrl_TriggerRemoteResumeService(void);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_EXCTSCHEDULE_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ExctSchedule_If.h
 *********************************************************************************************************************/
