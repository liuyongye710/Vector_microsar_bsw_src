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
/*!        \file  Fls_30_vMemAccM_Job.h
 *        \brief  Fls_30_vMemAccM job header file
 *
 *      \details  Abstract job structure and offer an interface to read and write from job structures.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_JOB_H)
# define FLS_30_VMEMACCM_JOB_H

#include "Fls_30_vMemAccM.h"
#include "vMemAccM_Types.h"

typedef enum 
{
    Fls_30_vMemAccM_Job_Read = FLS_30_VMEMACCM_SID_READ,
    Fls_30_vMemAccM_Job_Write = FLS_30_VMEMACCM_SID_WRITE,
    Fls_30_vMemAccM_Job_Erase = FLS_30_VMEMACCM_SID_ERASE,
    Fls_30_vMemAccM_Job_Compare = FLS_30_VMEMACCM_SID_COMPARE,
    Fls_30_vMemAccM_Job_BlankCheck = FLS_30_VMEMACCM_SID_BLANKCHECK, 
    Fls_30_vMemAccM_Job_ReadBlank = FLS_30_VMEMACCM_SID_READBLANK,
    Fls_30_vMemAccM_Job_NoJob
} Fls_30_vMemAccM_AsyncJobType; /*!< Enumeration to distinguish different async jobs, names are self explaining */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_Init
 *********************************************************************************************************************/
/*!
 * \brief       Initializes this submodule by setting local variables to their default values.
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_Init(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_RequestNewJob
 *********************************************************************************************************************/
/*!
 * \brief       Create job object to start the job later in the next main function cycle.
 * \details     Stores parameters of the job that will be started soon.
 * \param[in]     jobType: type of the job to start,
 * \param[in]     address: target address
 * \param[in,out] addressPtr: target pointer
 * \param[in]     length: target length
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_RequestNewJob
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_IsJobFinished
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the current job (i.e. the whole job requested from user) is finished.
 * \details     -
 * \return      TRUE: job still finished FALSE: job still running.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_IsJobFinished(void);


# if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_IsCurrentStepStillRunning
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the current hardware step (i.e. job requested from FlsAccessor) is still running
 *              and sets the current job result.
 * \details     JobResult is retrieved via calling GetJobResult from vMemAccM.
 * \return      TRUE: job still running; FALSE: job finished.
 * \pre         POLLING Mode is enabled, Job step is finished.
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_IsCurrentStepStillRunning(void);
# else
/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_SetCurrentStepResult
 *********************************************************************************************************************/
 /*!
  * \brief       Set the current step result of the job that is currently processed.
  * \details     JobResult is retrieved via job end notification invoked by vMemAccM.
  * \param[in]   resultOfvMemAccMJob: result received from notification invoked by vMemAccM
  * \pre         CALLBACK Mode is enabled, Job step is finished.
  * \context     TASK
  * \reentrant   TRUE
  * \synchronous TRUE
  */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_SetCurrentStepResult(vMemAccM_JobResultType resultOfvMemAccMJob);
# endif /* (FLS_30_VMEMACCM_POLLING_MODE == STD_ON) */


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_GetFinalJobResult
 *********************************************************************************************************************/
/*!
 * \brief       Returns the result of the job (over all steps) that is currently processed.
 * \details     -
 * \return      Result of the job.
 * \pre         Job is finished.
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_GetFinalJobResult(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_ProcessNextJobStep
 *********************************************************************************************************************/
/*!
 * \brief       Processes the next step of the job, requests job from lower layer and sets job progress.
 * \details     -
 * \return      TRUE: The job has been accepted; FALSE: The job has been rejected
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_ProcessNextJobStep(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_Cancel
 *********************************************************************************************************************/
/*!
 * \brief       Cancels an job, either only requested or already ongoing.
 * \details     Forwards the cancel request to vMemAccM, if a job is currently running on it and cancels internal state machine
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_Cancel(void);


#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#endif /* FLS_30_VMEMACCM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_Job.h
 *********************************************************************************************************************/
