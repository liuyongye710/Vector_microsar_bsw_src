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
/*!        \file  Fls_30_vMemAccM.c
 *        \brief  Fls_30_vMemAccM source file
 *
 *      \details  This is the implementation of the module Fls_30_vMemAccM
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fls_30_vMemAccM.h"
#include "Fls_30_vMemAccM_Job.h"
#include "Fls_30_vMemAccM_StateMachine.h"
#include "vMemAccM_Types.h"
#include "Fls_30_vMemAccM_Cbk.h"
#include "Fls_30_vMemAccM_Privates.h"

#if (FLS_30_VMEMACCM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Fls_30_vMemAccM header file */
#if (  (FLS_30_VMEMACCM_SW_MAJOR_VERSION != (6u)) \
    || (FLS_30_VMEMACCM_SW_MINOR_VERSION != (0u)) \
    || (FLS_30_VMEMACCM_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Fls_30_vMemAccM.c and Fls_30_vMemAccM.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (FLS_30_VMEMACCM_CFG_MAJOR_VERSION != (5u)) \
    || (FLS_30_VMEMACCM_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of Fls_30_vMemAccM.c and Fls_30_vMemAccM_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_LOCAL)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL static
#endif

#if !defined (FLS_30_VMEMACCM_LOCAL_INLINE)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL_INLINE LOCAL_INLINE
#endif


#define FLS_30_VMEMACCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
FLS_30_VMEMACCM_LOCAL boolean Fls_30_vMemAccM_IsModuleInitialized = FALSE;  /*!< Determines if the module is already initialized. Used for init check */
#endif
FLS_30_VMEMACCM_LOCAL MemIf_StatusType Fls_30_vMemAccM_ModuleStatus = MEMIF_UNINIT;    /*!< Status of the component. */

#define FLS_30_VMEMACCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define FLS_30_VMEMACCM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

FLS_30_VMEMACCM_LOCAL MemIf_JobResultType Fls_30_vMemAccM_ModuleJobResult; /*!< Job result of the component.*/

#define FLS_30_VMEMACCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_IsIdle
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the module is idle.
 * \details     -
 * \return      TRUE: module is idle, FALSE: module is busy.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \config      DET error detection is enabled
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_IsIdle(void);

/**********************************************************************************************************************
 * Fls_30_vMemAccM_IsValidPtr
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the given pointer is not null.
 * \details     -
 * \param[in]   toBeChecked: Pointer that shall be checked.
 * \return      TRUE: pointer is not null (i.e. valid), FALSE: pointer is null (i.e. not valid).
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \config      DET error detection is enabled
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_IsValidPtr(const void* toBeChecked);
#endif /* (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON) */


#if (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_FeeJobEndOrErrorNotification
 *********************************************************************************************************************/
/*!
 * \brief       Invoke Fee Notification function depending whether job was successful or failed.
 * \details     -
 * \pre         FEE notification enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FeeJobEndOrErrorNotification(void);
#endif /* (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON) */


/**********************************************************************************************************************
 * Fls_30_vMemAccM_ProcessAsyncRequest
 *********************************************************************************************************************/
/*!
 * \brief       Processes the given asynchronous request and does all the DET check.
 * \details     Implements the API pattern.
 * \param[in]     jobType of forwarded job
 * \param[in]     address of forwarded job
 * \param[in,out] addressPtr of forwarded job
 * \param[in]     length of forwarded job
 * \return      TRUE: job is accepted (all checks ok), FALSE: job is rejected (at least one check failed).
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_ProcessAsyncRequest
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_IsValidPtr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_IsValidPtr(const void* toBeChecked)
{
  return toBeChecked != NULL_PTR;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_IsIdle
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(boolean, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_IsIdle(void)
{
  return Fls_30_vMemAccM_ModuleStatus == MEMIF_IDLE;
}
#endif /* (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON) */


#if (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_FeeJobEndOrErrorNotification
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FeeJobEndOrErrorNotification(void)
{
  if(Fls_30_vMemAccM_Job_GetFinalJobResult() == MEMIF_JOB_OK)
  {
    FLS_30_VMEMACCM_FEE_JOB_END_NOTIFICATION();
  }
  else
  {
    FLS_30_VMEMACCM_FEE_JOB_ERROR_NOTIFICATION();
  }
}
#endif /* (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON) */


/**********************************************************************************************************************
 * Fls_30_vMemAccM_ProcessAsyncRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FLS_30_VMEMACCM_LOCAL_INLINE FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_ProcessAsyncRequest
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
)
{
  Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 detErrorId = FLS_30_VMEMACCM_E_NO_ERROR;

#if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
  if(Fls_30_vMemAccM_IsModuleInitialized == FALSE)
  {
    detErrorId = FLS_30_VMEMACCM_E_NOT_INITIALIZED;
  }
  else if(Fls_30_vMemAccM_IsIdle() == FALSE)
  {
    detErrorId = FLS_30_VMEMACCM_E_BUSY;
  }
# if(FLS_30_VMEMACCM_BLANK_CHECK_API == STD_ON)
  /* PRQA S 3415 1 */ /* MD_Fls_30_vMemAccM_SideEffects */
  else if((jobType != Fls_30_vMemAccM_Job_Erase) && (jobType != Fls_30_vMemAccM_Job_BlankCheck) && (Fls_30_vMemAccM_IsValidPtr(addressPtr) == FALSE)) /* PRQA S 0315 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */ /* SBSW_FLS_30_VMEMACCM_POINTERCHECK */
# else
  /* PRQA S 3415 1 */ /* MD_Fls_30_vMemAccM_SideEffects */
  else if((jobType != Fls_30_vMemAccM_Job_Erase) && (Fls_30_vMemAccM_IsValidPtr(addressPtr) == FALSE)) /* PRQA S 0315 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */ /* SBSW_FLS_30_VMEMACCM_POINTERCHECK */
# endif
  {
    detErrorId = FLS_30_VMEMACCM_E_PARAM_POINTER;
  }
  else
#endif
  {
    Fls_30_vMemAccM_ModuleStatus = MEMIF_BUSY;
    Fls_30_vMemAccM_ModuleJobResult = MEMIF_JOB_PENDING;
    Fls_30_vMemAccM_Job_RequestNewJob(jobType, address, addressPtr, length); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    Fls_30_vMemAccM_StateMachine_SetBusy();
    returnValue = E_OK;
  }

#if (FLS_30_VMEMACCM_DEV_ERROR_REPORT == STD_ON)
  if (detErrorId != FLS_30_VMEMACCM_E_NO_ERROR)
  {
    (void)Det_ReportError(FLS_30_VMEMACCM_MODULE_ID, FLS_30_VMEMACCM_INSTANCE_ID, jobType, detErrorId); /* PRQA S 4424 1 */ /* MD_Fls_30_vMemAccM_AsyncJobTypeToUint8 */
  }
#else
  FLS_30_VMEMACCM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
  return returnValue;
}



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Init(void)
{
  Fls_30_vMemAccM_ModuleStatus = MEMIF_IDLE;
  Fls_30_vMemAccM_ModuleJobResult = MEMIF_JOB_OK;
  Fls_30_vMemAccM_StateMachine_Init();
  Fls_30_vMemAccM_Job_Init();
  #if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
  Fls_30_vMemAccM_IsModuleInitialized = TRUE;
  #endif
}


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Read
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  uint8 *TargetAddressPtr, /* PRQA S 3673 1 */ /* MD_Fls_30_vMemAccM_IsNotConst */
  Fls_30_vMemAccM_LengthType Length
)
{
  return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_Read, SourceAddress, TargetAddressPtr, Length); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
} /* Fls_30_vMemAccM_Read() */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Write
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  const uint8 *SourceAddressPtr,
  Fls_30_vMemAccM_LengthType Length
)
{
  return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_Write, TargetAddress, SourceAddressPtr, Length); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
} /* Fls_30_vMemAccM_Write() */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Erase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Erase
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  Fls_30_vMemAccM_LengthType Length
)
{
 return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_Erase, TargetAddress, NULL_PTR, Length); /* SBSW_FLS_30_VMEMACCM_ERASE_BLANKCHECK_POINTER */
} /* Fls_30_vMemAccM_Erase() */


#if(FLS_30_VMEMACCM_COMPARE_API == STD_ON)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Compare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Compare
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  const uint8 *TargetAddressPtr,
  Fls_30_vMemAccM_LengthType Length
)
{
  return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_Compare, SourceAddress, TargetAddressPtr, Length); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
} /* Fls_30_vMemAccM_Compare() */
#endif


#if(FLS_30_VMEMACCM_BLANK_CHECK_API == STD_ON)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_BlankCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_BlankCheck
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  Fls_30_vMemAccM_LengthType Length
)
{
  return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_BlankCheck, TargetAddress, NULL_PTR, Length); /* SBSW_FLS_30_VMEMACCM_ERASE_BLANKCHECK_POINTER */
} /* Fls_30_vMemAccM_BlankCheck() */
#endif


#if(FLS_30_VMEMACCM_READBLANK_API == STD_ON)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_ReadBlank()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_ReadBlank
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  uint8 *TargetAddressPtr,  /* PRQA S 3673 1 */ /* MD_Fls_30_vMemAccM_IsNotConst */
  Fls_30_vMemAccM_LengthType Length
)
{
  return Fls_30_vMemAccM_ProcessAsyncRequest(Fls_30_vMemAccM_Job_ReadBlank, SourceAddress, TargetAddressPtr, Length); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
} /* Fls_30_vMemAccM_ReadBlank() */
#endif


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Cancel (void)
{
  Fls_30_vMemAccM_ModuleStatus = MEMIF_IDLE;
  if(Fls_30_vMemAccM_ModuleJobResult == MEMIF_JOB_PENDING)
  {
    Fls_30_vMemAccM_ModuleJobResult = MEMIF_JOB_CANCELED;
  }
  Fls_30_vMemAccM_Job_Cancel();
  Fls_30_vMemAccM_StateMachine_Init();
# if (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON)
  FLS_30_VMEMACCM_FEE_JOB_ERROR_NOTIFICATION();
#endif
} /* Fls_30_vMemAccM_Cancel() */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetJobResult(void)
{
  return Fls_30_vMemAccM_ModuleJobResult;
} /* Fls_30_vMemAccM_GetJobResult() */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetStatus(void)
{
  return Fls_30_vMemAccM_ModuleStatus;
} /* Fls_30_vMemAccM_GetStatus() */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_SetMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_SetMode (MemIf_ModeType Mode)
{
  FLS_30_VMEMACCM_DUMMY_STATEMENT(Mode); /* PRQA S 3112, 1338, 2983 */ /* MD_MSR_DummyStmt */
} /* Fls_30_vMemAccM_SetMode() */


#if (FLS_30_VMEMACCM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_30_VMEMACCM_APPL_VAR) versionInfo)
{
    uint8 detErrorId = FLS_30_VMEMACCM_E_NO_ERROR;

#if (FLS_30_VMEMACCM_DEV_ERROR_DETECT == STD_ON)
    if (Fls_30_vMemAccM_IsValidPtr(versionInfo) == FALSE) /* PRQA S 0315 1 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */ /* SBSW_FLS_30_VMEMACCM_POINTERCHECK */
    {
        detErrorId = FLS_30_VMEMACCM_E_PARAM_POINTER;
    }
    else
#endif
    {
        versionInfo->vendorID = (FLS_30_VMEMACCM_VENDOR_ID); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
        versionInfo->moduleID = (FLS_30_VMEMACCM_MODULE_ID); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
        versionInfo->sw_major_version = (FLS_30_VMEMACCM_SW_MAJOR_VERSION); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
        versionInfo->sw_minor_version = (FLS_30_VMEMACCM_SW_MINOR_VERSION); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
        versionInfo->sw_patch_version = (FLS_30_VMEMACCM_SW_PATCH_VERSION); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    }

#if (FLS_30_VMEMACCM_DEV_ERROR_REPORT == STD_ON)
    if (detErrorId != FLS_30_VMEMACCM_E_NO_ERROR)
    {
        (void)Det_ReportError(FLS_30_VMEMACCM_MODULE_ID, FLS_30_VMEMACCM_INSTANCE_ID, FLS_30_VMEMACCM_SID_GET_VERSION_INFO, detErrorId);
    }
#else
    FLS_30_VMEMACCM_DUMMY_STATEMENT(detErrorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}
#endif /* (FLS_30_VMEMACCM_VERSION_INFO_API == STD_ON) */


/**********************************************************************************************************************
 *  Fls_30_vMemAccM_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_MainFunction(void)
{
#if (FLS_30_VMEMACCM_POLLING_MODE == STD_ON)
  /* Busy state machine means StatePrepareNextvMemAccMJob is set, therefore a job (step) is open or has to be finished.
   * No endless loop possible as within this state always a transition to a follower state is happening.
   */
  do
  {
    Fls_30_vMemAccM_StateMachine_ExecuteState();
  } while(Fls_30_vMemAccM_StateMachine_IsBusy() == TRUE);
#else
  /* Within callback mode the StatePrepareNextvMemAccMJob is set within the job end notification, therefore a second cycle
   * is not necessary here */
  Fls_30_vMemAccM_StateMachine_ExecuteState();
#endif

  if((Fls_30_vMemAccM_StateMachine_IsIdle() == TRUE) && (Fls_30_vMemAccM_ModuleStatus != MEMIF_IDLE))
  {
    Fls_30_vMemAccM_ModuleStatus = MEMIF_IDLE;
    Fls_30_vMemAccM_ModuleJobResult = Fls_30_vMemAccM_Job_GetFinalJobResult();

#if (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON)
    Fls_30_vMemAccM_FeeJobEndOrErrorNotification();
#endif /* (FLS_30_VMEMACCM_FEE_NOTIFICATION == STD_ON) */
  }
}


#if (FLS_30_VMEMACCM_POLLING_MODE == STD_OFF)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_JobNotification
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_JobNotification
(
  vMemAccM_AddressAreaIdType AddressAreaId,
  vMemAccM_JobResultType Result
)
{
  if (AddressAreaId == Fls_30_vMemAccM_TargetAddressAreaId)
  {
    Fls_30_vMemAccM_Job_SetCurrentStepResult(Result);
    if (Result != VMEMACCM_JOB_CANCELED)
    {
      Fls_30_vMemAccM_StateMachine_SetBusy();
      Fls_30_vMemAccM_MainFunction();
    }
  }
}
#endif  /* (FLS_30_VMEMACCM_POLLING_MODE == STD_OFF) */

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */



/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Fls_30_vMemAccM_VoidPtrTypedPtr: rule 1.1
  Reason:     vMemAccM accepts untyped void pointers for user buffers. The Fls_30_vMemAccM accepts uint8 pointer since all of
              its interface must have the same signature as the AUTOSAR Fls.
              The Fls_30_vMemAccM merely forwards the uint8 pointer as a void pointer to the vMemAccM.
  Risk:       No risk.
  Prevention: Component tests ensures that the Fls_30_vMemAccM forwards the buffers correctly.

MD_Fls_30_vMemAccM_IsNotConst: rule 8.13
  Reason:     We store user buffer ptr as const uint8 in internal job structure. However, for Read requests we will cast const away later.
              It just looks like it might be const but it is not. We want to show that to the user by not making it const.
  Risk:       No risk.
  Prevention: No prevention.

MD_Fls_30_vMemAccM_ConstCast: rule 11.8
  Reason:     We store user buffer ptr as const uint8 in internal job structure. However, for Read requests we have to cast const away again.
              The original pointer has never been const anyway. We only do the cast for Read requests.
  Risk:       No risk.
  Prevention: Review.

MD_Fls_30_vMemAccM_AsyncJobTypeToUint8: rule 10.3
  Reason:     Use function Fls_30_vMemAccM_ProcessAsyncRequest to reduce code duplication. In order to avoid arguments that are almost the same (jobtype and API Id),
              we just use the jobType to get the API id out of it. The jobType enumeration is defined by using the correct Ids.
  Risk:       No risk.
  Prevention: Review.

 MD_Fls_30_vMemAccM_DefinedOutsideBlockScope: rule 8.9
  Reason:     Internal buffer is used only by Fls_30_vMemAccM_Write but defined outside the block scope. The internal buffer is only
              used in case RAM alignment of user buffers is required. In that case, the internal buffer has to be located in a special MemMap
              section and, therefore, cannot be defined at block scope of Fls_30_vMemAccM_Write.
  Risk:       No risk.
  Prevention: No prevention.

MD_Fls_30_vMemAccM_SideEffects: rule 13.5
  Reason:     The left hand operands of the expression checks that meaningful pointer is available.
              The right hand operand is then a function which only checks this parameter if available. This function has no side-effects.
  Risk:       No risk.
  Prevention: No prevention.

*/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_FLS_30_VMEMACCM_USERPOINTER
 \DESCRIPTION     Function call or write access with pointer as parameter (address pointer)
 \COUNTERMEASURE  \N The pointer is given by the user and is just forwarded to the underlying module. The user has to ensure that a
                     valid pointer is given.

\ID SBSW_FLS_30_VMEMACCM_POINTERCHECK
 \DESCRIPTION     Function call with pointer which will only be checked if it is not NULL by the called function. No write access!
 \COUNTERMEASURE  \N Can easily be checked by review.

\ID SBSW_FLS_30_VMEMACCM_ERASE_BLANKCHECK_POINTER
 \DESCRIPTION     Job Processing needs an user pointer as argument, but Erase and BlankCheck do not have one. We take NULL_PTR, but promise
                  to never write to it in case of Erase or BlankCheck Job.
 \COUNTERMEASURE  \N Can easily be checked by review.


\ID SBSW_FLS_30_VMEMACCM_INTERNALBUFFER
 \DESCRIPTION     Function call with locally defined pointer as parameter (address pointer). Length for copy operation is runtime checked.
 \COUNTERMEASURE  \N The pointer is defined locally, therefore valid, and is just forwarded to vStdLib. Length for copy operation
                  is runtime checked.

\ID SBSW_FLS_30_VMEMACCM_FUNCTIONPOINTER
 \DESCRIPTION     Use function pointer to execute the function of the next state and get rid of mapping from enum to function.
 \COUNTERMEASURE  \N Compiler assures that the functions behind the pointer really exist. Otherwise, it won't compile.

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* START_COVERAGE_JUSTIFICATION
\ID COV_FLS_30_VMEMACCM_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY
END_COVERAGE_JUSTIFICATION */


/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM.c
 *********************************************************************************************************************/
