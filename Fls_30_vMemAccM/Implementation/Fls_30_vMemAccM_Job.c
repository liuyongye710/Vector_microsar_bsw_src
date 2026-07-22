/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Fls_30_vMemAccM_Job.c
 *        \brief  Fls_30_vMemAccM job source file
 *
 *      \details  This is the implementation of the module Fls_30_vMemAccM_Job
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_JOB_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fls_30_vMemAccM_Job.h"
#include "Fls_30_vMemAccM_FlsAccessor.h"


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_LOCAL)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL static
#endif

#if !defined (FLS_30_VMEMACCM_LOCAL_INLINE)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL_INLINE LOCAL_INLINE
#endif


typedef struct
{
  Fls_30_vMemAccM_AsyncJobType jobType;   /*!< Type of request. All following params are only valid, if jobType is not None */
  Fls_30_vMemAccM_AddressType address;    /*!< Address of the next processing step */
  Fls_30_vMemAccM_LengthType length;      /*!< Remaining length */
  const uint8* userPointer;               /*!< User pointer of the next processing step. In case the request has no ptr, this will be NULL */
  MemIf_JobResultType currentStepResult;  /*!< Result of the latest step of this job. This is NOT the job result from upper layers point of view */
} Fls_30_vMemAccM_JobData;                /*!< Structure to hold data of a job */


# define FLS_30_VMEMACCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

FLS_30_VMEMACCM_LOCAL Fls_30_vMemAccM_JobData Fls_30_vMemAccM_CurrentJob;    /*!< Job that is currently processed */

# define FLS_30_VMEMACCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_Init(void)
{
  Fls_30_vMemAccM_CurrentJob.jobType = Fls_30_vMemAccM_Job_NoJob;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_RequestNewJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_RequestNewJob
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
)
{
  Fls_30_vMemAccM_CurrentJob.jobType = jobType;
  Fls_30_vMemAccM_CurrentJob.address = address;
  Fls_30_vMemAccM_CurrentJob.userPointer = addressPtr;
  Fls_30_vMemAccM_CurrentJob.length = length;
  Fls_30_vMemAccM_CurrentJob.currentStepResult = MEMIF_JOB_PENDING;
}                                                                  

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_IsJobFinished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_IsJobFinished(void)
{
  return (Fls_30_vMemAccM_CurrentJob.currentStepResult == MEMIF_JOB_FAILED) || (Fls_30_vMemAccM_CurrentJob.length == 0u);
}

#if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_IsCurrentStepStillRunning
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_IsCurrentStepStillRunning(void)
{

  Fls_30_vMemAccM_CurrentJob.currentStepResult = Fls_30_vMemAccM_FlsAccessor_GetJobResult();
  return Fls_30_vMemAccM_CurrentJob.currentStepResult == MEMIF_JOB_PENDING;
}
#else
/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_SetCurrentStepResult
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_SetCurrentStepResult(vMemAccM_JobResultType resultOfvMemAccMJob)
{
  Fls_30_vMemAccM_CurrentJob.currentStepResult = Fls_30_vMemAccM_FlsAccessor_ConvertJobResult(resultOfvMemAccMJob);
}
#endif /* (FLS_30_VMEMACCM_POLLING_MODE == STD_ON) */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_GetFinalJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_GetFinalJobResult(void)
{
  return Fls_30_vMemAccM_CurrentJob.currentStepResult;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_ProcessNextJobStep
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_ProcessNextJobStep(void)
{
  boolean ret;

  Fls_30_vMemAccM_LengthType processedLength = Fls_30_vMemAccM_FlsAccessor_RequestAsyncJob(
          Fls_30_vMemAccM_CurrentJob.jobType,
          Fls_30_vMemAccM_CurrentJob.address,
          Fls_30_vMemAccM_CurrentJob.userPointer, /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
          Fls_30_vMemAccM_CurrentJob.length);

  if(processedLength == 0u)
  {
    Fls_30_vMemAccM_CurrentJob.currentStepResult = MEMIF_JOB_FAILED;
    ret = FALSE;
  }
  else
  {
    Fls_30_vMemAccM_CurrentJob.currentStepResult = MEMIF_JOB_PENDING;

    Fls_30_vMemAccM_CurrentJob.address += processedLength;
    if (Fls_30_vMemAccM_CurrentJob.userPointer != NULL_PTR)
    {
      Fls_30_vMemAccM_CurrentJob.userPointer = &Fls_30_vMemAccM_CurrentJob.userPointer[processedLength];
    }
    Fls_30_vMemAccM_CurrentJob.length -= processedLength;

    ret = TRUE;
  }

  return ret;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Job_Cancel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Job_Cancel(void)
{
  if(Fls_30_vMemAccM_FlsAccessor_GetJobResult() == MEMIF_JOB_PENDING)
  {
    Fls_30_vMemAccM_FlsAccessor_Cancel();
  }
  Fls_30_vMemAccM_CurrentJob.jobType = Fls_30_vMemAccM_Job_NoJob;
}

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_Job.c
 *********************************************************************************************************************/
