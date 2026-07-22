/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL.c
 *        \brief  vMem_30_XXspi01 LowLevel source file
 *
 *      \details  See vMem_30_XXspi01_LL.h
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h"
#include "vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h"
#include "vMem_30_XXspi01_LL_InstanceInitializer.h"
#include "vMem_30_XXspi01_LL_InstanceModifier.h"
#include "vMem_30_XXspi01_LL.h"
#include "vMem_30_XXspi01_Cfg.h"
#include "vMem_30_XXspi01_LL_Cbk_Int.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  HARDWARE SOFTWARE INTERFACE (HSI)
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL static
#endif

/*! Internal state machine type to indicate the instance-specific job progress. */
typedef enum
{
  VMEM_30_XXSPI01_IDLE = 0,
  VMEM_30_XXSPI01_INIT_HW,
  VMEM_30_XXSPI01_EXECUTE_READ,
  VMEM_30_XXSPI01_EXECUTE_MODIFICATION,
  VMEM_30_XXSPI01_EXECUTE_BLANK_CHECK
} vMem_30_XXspi01_JobProgressType;

/*! Specifies the type of access to the external flash device. */
typedef enum
{
  VMEM_30_XXSPI01_READ_ACCESS = 0,
  VMEM_30_XXSPI01_WRITE_ACCESS,
  VMEM_30_XXSPI01_ERASE_ACCESS,
  VMEM_30_XXSPI01_BLANK_CHECK_ACCESS
} vMem_30_XXspi01_AccessType;

/*! Instance job type to group instance specific information. */
typedef struct
{
  vMem_30_XXspi01_DeviceIdType DeviceId;
  vMem_30_XXspi01_JobResultType JobResult;
  vMem_30_XXspi01_JobProgressType JobProgress;
  vMem_30_XXspi01_LengthType Length;
  boolean ProcessFlag;
} vMem_30_XXspi01_InstanceJobType;
typedef P2VAR(vMem_30_XXspi01_InstanceJobType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InstanceJobPtrType;

/*! Job parameters for backup purposes. */
typedef struct
{
  vMem_30_XXspi01_AddressType Address;
  vMem_30_XXspi01_ConstDataPtrType SourceAddressPtr;
  vMem_30_XXspi01_DataPtrType TargetAddressPtr;
  vMem_30_XXspi01_LengthType Length;
  vMem_30_XXspi01_AccessType AccessType;
} vMem_30_XXspi01_JobParamBackupType;
typedef P2VAR(vMem_30_XXspi01_JobParamBackupType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_JobParamBackupPtrType;

typedef P2CONST(vMem_30_XXspi01_JobParamBackupType, AUTOMATIC, VMEM_30_XXSPI01_CONST) vMem_30_XXspi01_ConstJobParamBackupPtrType;

/*! Function pointer for vMem_JobSucceeded(), vMem_JobFailed() and vMem_MemNotBlank(). */
typedef P2FUNC(void, AUTOMATIC, vMem_30_XXspi01_JobEndFuncType) (vMem_30_XXspi01_InstanceJobPtrType processedInstance);

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Contains instance specific status parameters like the JobResult, the JobProgress and the ProcessFlag. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_InstanceJobType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InstanceJobInfo[vMem_30_XXspi01_GetSizeOfvMemInstance()];

/*! Job parameters for backup purposes. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_JobParamBackupType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_JobParamBackup[vMem_30_XXspi01_GetSizeOfvMemInstance()]; /* PRQA S 3218 */ /* MD_vMem_30_XXspi01_FileScopeStatic */

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! BlankCheck Buffer which provides enough memory space for each vMemInstance to store the data of a whole page. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_BlankCheckBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_MAX_PAGE_SIZE];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLJobSucceeded()
 *********************************************************************************************************************/
/*! \brief        Resets the instance specific state machine and sets the instance's job result to OK.
 *  \details      -
 *  \param[in]    processedInstance      Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLJobSucceeded(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLJobFailed()
 *********************************************************************************************************************/
/*! \brief        Resets the instance specific state machine and sets the instance's job result to FAILED.
 *  \details      -
 *  \param[in]    processedInstance      Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLJobFailed(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLMemNotBlank()
 *********************************************************************************************************************/
/*! \brief        Resets the instance specific state machine and sets the instance's job result to MEM_NOT_BLANK.
 *  \details      -
 *  \param[in]    processedInstance      Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLMemNotBlank(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLStoreUserRequestedJob()
 *********************************************************************************************************************/
/*! \brief        Stores the passed job parameters to a local backup buffer.
 *  \details      This service is called right before the Hw initialization is executed. The previously
 *                received job parameters are stored until the Hw initialization is successfully finished.
 *  \param[in]    instanceId               ID and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    jobParametersPtr         Pointer to a set of necessary parameters, specifying the requested user job.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLStoreUserRequestedJob(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_JobParamBackupPtrType jobParametersPtr);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLTriggerUserRequestedJob()
 *********************************************************************************************************************/
/*! \brief        This function triggers the execution of the previously stored user job.
 *  \details      This function is called after an instance is successfully initialized. The previously stored
 *                user job parameters are passed to one of the service functions vMem_LLRead(), vMem_LLWrite()
 *                or vMem_LLErase() according to the job type.
 *  \param[in]    instanceId       ID and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLTriggerUserRequestedJob(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLInitiateHwInitialization()
 *********************************************************************************************************************/
/*! \brief        Prepares the component for the initial HW setup and triggers the initialization.
 *  \details      This function stores the passed parameters as a job backup and triggers the initialization of
 *                the requested instance.
 *  \param[in]    instanceId       ID and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    jobParamPtr      Pointer to a struct which contains all necessary job parameters of
 *                                 the previously requested job.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLInitiateHwInitialization(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_JobParamBackupPtrType jobParamPtr);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLTransmitReadSeq()
 *********************************************************************************************************************/
/*! \brief        Sets up the correct read sequence and triggers its transmission.
 *  \details      -
 *  \param[in]    instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    sourceAddress       NV memory address to read from, must be valid.
 *  \param[out]   targetAddressPtr    Application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]    length              Length in bytes to be read, must be valid.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLTransmitReadSeq(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_AddressType sourceAddress,
    vMem_30_XXspi01_SpiDataPtrType targetAddressPtr,
    vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLPerformBlankCheck()
 *********************************************************************************************************************/
/*! \brief       Compares the previously read page byte-wise with the instance specific erase value.
 *  \details     -
 *  \param[in]   instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLPerformBlankCheck(
    vMem_30_XXspi01_InstanceIdType instanceId);

/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLJobSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLJobSucceeded(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance)
{
  processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
} /* vMem_30_XXspi01_LLJobSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLJobFailed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLJobFailed(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance)
{
  processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (processedInstance->JobProgress == VMEM_30_XXSPI01_INIT_HW)
  {
    (void) Det_ReportRuntimeError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET,
        VMEM_30_XXSPI01_SID_MAIN_FUNCTION, VMEM_30_XXSPI01_RUNTIME_E_INITIALIZATION_FAILED);
  }
#endif
  processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
} /* vMem_30_XXspi01_LLJobFailed */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLMemNotBlank()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLMemNotBlank(
    vMem_30_XXspi01_InstanceJobPtrType processedInstance)
{
  processedInstance->JobResult = VMEM_MEM_NOT_BLANK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
} /* vMem_30_XXspi01_LLMemNotBlank */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLStoreUserRequestedJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLStoreUserRequestedJob(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_JobParamBackupPtrType jobParametersPtr) /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  vMem_30_XXspi01_JobParamBackupPtrType jobParamBackupPtr = &vMem_30_XXspi01_JobParamBackup[instanceId];

  jobParamBackupPtr->Address = jobParametersPtr->Address; /* SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob */
  jobParamBackupPtr->SourceAddressPtr = jobParametersPtr->SourceAddressPtr; /* SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob */
  jobParamBackupPtr->TargetAddressPtr = jobParametersPtr->TargetAddressPtr; /* SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob */
  jobParamBackupPtr->Length = jobParametersPtr->Length; /* SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob */
  jobParamBackupPtr->AccessType = jobParametersPtr->AccessType; /* SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob */
} /* vMem_30_XXspi01_LLStoreUserRequestedJob */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLTriggerUserRequestedJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLTriggerUserRequestedJob(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_ConstJobParamBackupPtrType jobParamBackupPtr = &vMem_30_XXspi01_JobParamBackup[instanceId];

  switch (jobParamBackupPtr->AccessType)
  {
  case VMEM_30_XXSPI01_ERASE_ACCESS:
    (void) vMem_30_XXspi01_LLErase(instanceId, jobParamBackupPtr->Address, jobParamBackupPtr->Length);
    break;
  case VMEM_30_XXSPI01_WRITE_ACCESS:
    (void) vMem_30_XXspi01_LLWrite(instanceId, /* SBSW_vMem_30_XXspi01_FunctionCallInLoadUserRequestedJob */
    jobParamBackupPtr->Address, jobParamBackupPtr->SourceAddressPtr, jobParamBackupPtr->Length);
    break;
  case VMEM_30_XXSPI01_READ_ACCESS:
    (void) vMem_30_XXspi01_LLRead(instanceId, /* SBSW_vMem_30_XXspi01_FunctionCallInLoadUserRequestedJob */
    jobParamBackupPtr->Address, jobParamBackupPtr->TargetAddressPtr, jobParamBackupPtr->Length);
    break;
  default: /* VMEM_30_XXSPI01_BLANK_CHECK_ACCESS */
    (void) vMem_30_XXspi01_LLIsBlank(instanceId, /* SBSW_vMem_30_XXspi01_FunctionCallInLoadUserRequestedJob */
    jobParamBackupPtr->Address, jobParamBackupPtr->Length);
    break;
  }
} /* vMem_30_XXspi01_LLTriggerUserRequestedJob */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLInitiateHwInitialization()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLInitiateHwInitialization(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_JobParamBackupPtrType jobParamPtr)
{
  vMem_30_XXspi01_LLStoreUserRequestedJob(instanceId, jobParamPtr); /* SBSW_vMem_30_XXspi01_FunctionCallStoreUserRequestedJob */
  vMem_30_XXspi01_LL_InstanceInitializer_InitInstance(instanceId);
} /* vMem_30_XXspi01_LLInitiateHwInitialization */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLTransmitReadSeq()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLTransmitReadSeq(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_AddressType sourceAddress,
    vMem_30_XXspi01_SpiDataPtrType targetAddressPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readSequencePtr;
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_InstanceJobInfo[instanceId].DeviceId;

  readSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence(instanceId, deviceId, sourceAddress,
      (vMem_30_XXspi01_SpiDataPtrType) targetAddressPtr, (vMem_30_XXspi01_SpiLengthType) length); /* PRQA S 0316 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */

  if(vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(instanceId, readSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LLJobFailed(&vMem_30_XXspi01_InstanceJobInfo[instanceId]); /* SBSW_vMem_30_XXspi01_FunctionCallJobFailed */
  }
} /* vMem_30_XXspi01_LLTransmitReadSeq */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLPerformBlankCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLPerformBlankCheck(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_JobEndFuncType jobEndFunc = vMem_30_XXspi01_LLJobSucceeded;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  vMem_30_XXspi01_ConstSpiDataPtrType blankCheckBuffer =
      (vMem_30_XXspi01_ConstSpiDataPtrType) vMem_30_XXspi01_BlankCheckBuffer[instanceId];
  vMem_30_XXspi01_EraseValueOfvMemDeviceConfigType eraseValue = vMem_30_XXspi01_LL_CfgDevice_GetEraseValue(
      processedInstance->DeviceId);
  vMem_30_XXspi01_LengthType bufferIterator;

  if(processedInstance->Length <= VMEM_30_XXSPI01_MAX_PAGE_SIZE)
  {
    for (bufferIterator = 0u; bufferIterator < processedInstance->Length; bufferIterator++)
    {
      if (blankCheckBuffer[bufferIterator] != (vMem_30_XXspi01_SpiDataType) eraseValue)
      {
        jobEndFunc = vMem_30_XXspi01_LLMemNotBlank;
      }
    }
  }
  else
  {
    jobEndFunc = vMem_30_XXspi01_LLJobFailed;
  }

  jobEndFunc(processedInstance); /* SBSW_vMem_30_XXspi01_FunctionPtrCallBlankCheck */
} /* vMem_30_XXspi01_LLPerformBlankCheck */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_JobSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_JobSucceeded(vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_LLJobSucceeded(&vMem_30_XXspi01_InstanceJobInfo[instanceId]); /* SBSW_vMem_30_XXspi01_FunctionCallJobSucceeded */
} /* vMem_30_XXspi01_LL_Cbk_JobSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_InitSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_InitSucceeded(vMem_30_XXspi01_InstanceIdType instanceId,
    vMem_30_XXspi01_DeviceIdType deviceId)
{
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  processedInstance->DeviceId = deviceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

  vMem_30_XXspi01_LLTriggerUserRequestedJob(instanceId);
} /* vMem_30_XXspi01_LL_Cbk_InitSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_JobFailed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_JobFailed(vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];

  vMem_30_XXspi01_LLJobFailed(processedInstance); /* SBSW_vMem_30_XXspi01_FunctionCallJobFailed */
} /* vMem_30_XXspi01_LL_Cbk_JobFailed */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLSeqEndNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLSeqEndNotification(vMem_30_XXspi01_InstanceIdType instanceId,
    Spi_SequenceType spiSeqId)
{
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];

  if (vMem_30_XXspi01_LL_SpiGetSequenceResult(spiSeqId) == SPI_SEQ_OK)
  {
    processedInstance->ProcessFlag = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
  }
  else
  {
    vMem_30_XXspi01_LLJobFailed(processedInstance); /* SBSW_vMem_30_XXspi01_FunctionCallJobFailed */
  }
} /* vMem_30_XXspi01_LLSeqEndNotification */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLRead()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLRead(
    vMem_30_XXspi01_InstanceIdType instanceId,
    vMem_30_XXspi01_AddressType sourceAddress,
    vMem_30_XXspi01_DataPtrType targetAddressPtr,
    vMem_30_XXspi01_LengthType length)
{
  vMem_30_XXspi01_AccessType requestedAccess = VMEM_30_XXSPI01_READ_ACCESS;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  vMem_30_XXspi01_JobParamBackupType jobParam;

  /* The JobResult must be initialized with VMEM_JOB_OK. */
  processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */

  if (vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(instanceId) == FALSE)
  {
    jobParam.Address = sourceAddress;
    jobParam.SourceAddressPtr = NULL_PTR;
    jobParam.TargetAddressPtr = targetAddressPtr;
    jobParam.Length = length;
    jobParam.AccessType = requestedAccess;

    /*
     * The order of setting the job specific parameters and calling the LLInitiateHwInitialization() is important,
     * because during the function call these job parameters can be overwritten.
     */
    processedInstance->JobProgress = VMEM_30_XXSPI01_INIT_HW; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLInitiateHwInitialization(instanceId, &jobParam); /* SBSW_vMem_30_XXspi01_FunctionCallInitiateHwInitialization */
  }
  else
  {
    processedInstance->JobProgress = VMEM_30_XXSPI01_EXECUTE_READ; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLTransmitReadSeq(instanceId, sourceAddress,
        (vMem_30_XXspi01_SpiDataPtrType) targetAddressPtr, (vMem_30_XXspi01_SpiLengthType) length); /* PRQA S 0316 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }

  return E_OK;
} /* vMem_30_XXspi01_LLRead */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLWrite()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLWrite(vMem_30_XXspi01_InstanceIdType instanceId,
    vMem_30_XXspi01_AddressType targetAddress, vMem_30_XXspi01_ConstDataPtrType sourceAddressPtr,
    vMem_30_XXspi01_LengthType length)
{
  vMem_30_XXspi01_AccessType requestedAccess = VMEM_30_XXSPI01_WRITE_ACCESS;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  vMem_30_XXspi01_JobParamBackupType jobParam;

  /* The JobResult must be initialized with VMEM_JOB_OK. */
  processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */

  if (vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(instanceId) == FALSE)
  {
    jobParam.Address = targetAddress;
    jobParam.SourceAddressPtr = sourceAddressPtr;
    jobParam.TargetAddressPtr = NULL_PTR;
    jobParam.Length = length;
    jobParam.AccessType = requestedAccess;

    /*
     * The order of setting the job specific parameters and calling the LLInitiateHwInitialization() is important,
     * because during the function call these job parameters can be overwritten.
     */
    processedInstance->JobProgress = VMEM_30_XXSPI01_INIT_HW; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLInitiateHwInitialization(instanceId, &jobParam); /* SBSW_vMem_30_XXspi01_FunctionCallInitiateHwInitialization */

  }
  else
  {
   /*
    * The order of setting the job specific parameters and calling the InstanceModifier_PerformWriteAccess() is important,
    * because during the function call these job parameters can be overwritten.
    */
    processedInstance->JobProgress = VMEM_30_XXSPI01_EXECUTE_MODIFICATION; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess(instanceId, processedInstance->DeviceId, targetAddress,
        (vMem_30_XXspi01_ConstSpiDataPtrType) sourceAddressPtr, (vMem_30_XXspi01_SpiLengthType) length); /* PRQA S 0316 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }

  return E_OK;
} /* vMem_30_XXspi01_LLWrite */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLErase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLErase(vMem_30_XXspi01_InstanceIdType instanceId,
    vMem_30_XXspi01_AddressType targetAddress, vMem_30_XXspi01_LengthType length)
{
  vMem_30_XXspi01_AccessType requestedAccess = VMEM_30_XXSPI01_ERASE_ACCESS;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  vMem_30_XXspi01_JobParamBackupType jobParam;

  /* The JobResult must be initialized with VMEM_JOB_OK. */
  processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */

  if (vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(instanceId) == FALSE)
  {
    jobParam.Address = targetAddress;
    jobParam.SourceAddressPtr = NULL_PTR;
    jobParam.TargetAddressPtr = NULL_PTR;
    jobParam.Length = length;
    jobParam.AccessType = requestedAccess;

    /*
     * The order of setting the job specific parameters and calling the LLInitiateHwInitialization() is important,
     * because during the function call these job parameters can be overwritten.
     */
    processedInstance->JobProgress = VMEM_30_XXSPI01_INIT_HW; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLInitiateHwInitialization(instanceId, &jobParam); /* SBSW_vMem_30_XXspi01_FunctionCallInitiateHwInitialization */
  }
  else
  {
    processedInstance->JobProgress = VMEM_30_XXSPI01_EXECUTE_MODIFICATION; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess(instanceId, processedInstance->DeviceId, targetAddress);
  }

  /* The passed Length parameter is currently not necessary, because only single physical sectors can be erased at once. */
  VMEM_30_XXSPI01_DUMMY_STATEMENT(length);

  return E_OK;
} /* vMem_30_XXspi01_LLErase */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsBlank
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsBlank(vMem_30_XXspi01_InstanceIdType instanceId,
    vMem_30_XXspi01_AddressType targetAddress, vMem_30_XXspi01_LengthType length)
{
  vMem_30_XXspi01_AccessType requestedAccess = VMEM_30_XXSPI01_BLANK_CHECK_ACCESS;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];
  vMem_30_XXspi01_JobParamBackupType jobParam;
  vMem_30_XXspi01_SpiDataPtrType blankCheckBuffer = vMem_30_XXspi01_BlankCheckBuffer[instanceId];

  /* The JobResult must be initialized with VMEM_JOB_OK. */
  processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */

  if (vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(instanceId) == FALSE)
  {
    jobParam.Address = targetAddress;
    jobParam.SourceAddressPtr = NULL_PTR;
    jobParam.TargetAddressPtr = NULL_PTR;
    jobParam.Length = length;
    jobParam.AccessType = requestedAccess;

    /*
     * The order of setting the job specific parameters and calling the LLInitiateHwInitialization() is important,
     * because during the function call these job parameters can be overwritten.
     */
    processedInstance->JobProgress = VMEM_30_XXSPI01_INIT_HW; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLInitiateHwInitialization(instanceId, &jobParam); /* SBSW_vMem_30_XXspi01_FunctionCallInitiateHwInitialization */

  }
  else
  {
    processedInstance->JobProgress = VMEM_30_XXSPI01_EXECUTE_BLANK_CHECK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->Length = length; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LLTransmitReadSeq(instanceId, targetAddress, blankCheckBuffer,
        (vMem_30_XXspi01_SpiLengthType) length); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }

  return E_OK;
} /* vMem_30_XXspi01_LLIsBlank */

/**********************************************************************************************************************
 * vMem_30_XXspi01_LLGetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_JobResultType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetJobResult(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  return vMem_30_XXspi01_InstanceJobInfo[instanceId].JobResult;
} /* vMem_30_XXspi01_LLGetJobResult */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLProcessing()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLProcessing(void)
{
  vMem_30_XXspi01_InstanceIdType instanceId;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance;

  for (instanceId = 0; instanceId < vMem_30_XXspi01_GetSizeOfvMemInstance(); instanceId++)
  {
    processedInstance = &vMem_30_XXspi01_InstanceJobInfo[instanceId];

    if (processedInstance->ProcessFlag == TRUE)
    {
      processedInstance->ProcessFlag = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */

      switch (processedInstance->JobProgress)
      {
      case VMEM_30_XXSPI01_INIT_HW:
        vMem_30_XXspi01_LL_InstanceInitializer_Processing(instanceId);
        break;
      case VMEM_30_XXSPI01_EXECUTE_READ:
        processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        break;
      case VMEM_30_XXSPI01_EXECUTE_MODIFICATION:
        vMem_30_XXspi01_LL_InstanceModifier_Processing(instanceId);
        break;
      case VMEM_30_XXSPI01_EXECUTE_BLANK_CHECK:
        vMem_30_XXspi01_LLPerformBlankCheck(instanceId);
        break;
      default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* VMEM_30_XXSPI01_IDLE */
        break;
      }
    }
  }
} /* vMem_30_XXspi01_LLProcessing */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLInit(void)
{
  vMem_30_XXspi01_InstanceIdType instanceId;

  for (instanceId = 0; instanceId < vMem_30_XXspi01_GetSizeOfvMemInstance(); instanceId++)
  {
    vMem_30_XXspi01_InstanceJobInfo[instanceId].DeviceId = 0; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
    vMem_30_XXspi01_InstanceJobInfo[instanceId].JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
    vMem_30_XXspi01_InstanceJobInfo[instanceId].JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
    vMem_30_XXspi01_InstanceJobInfo[instanceId].ProcessFlag = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
  }

  vMem_30_XXspi01_LL_InstanceInitializer_Init();

  return E_OK;
} /* vMem_30_XXspi01_LLInit */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLGetJedecId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_SpiDataPtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetJedecId(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  return vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation(instanceId);
} /* vMem_30_XXspi01_LLGetJedecId */

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_vMem_30_XXspi01_VoidPtrTypedPtr: rule 11.5
 Reason:     vMem accepts untyped void pointers in its hardware specific functionality, to provide a compatible
 interface for different hardware specific function implementations: one may get a structure of type A,
 the other of type B etc. With a void pointer interface the signature of all the functions keeps the same
 as can be used in one typed function pointer array.
 In the hardware specific functionality GetActiveAddressRegion the vMem performs a cast of the void pointer
 to a pointer to vMem_30_Tc3xxInf01_AddressRegionType, so it can write the currently active address region
 to the referenced object.
 The user of this functionality has to make sure, that the referenced object is of type
 vMem_30_Tc3xxInf01_AddressRegionType. During initialization the components calls its own service to get
 the active address region and for this performs a cast from a pointer to object type to a pointer to void.
 vMem also accepts void pointers for user buffers. During a write job vMem has to split the passed
 buffer into words. Therefore, the buffer is cast to a pointer of type uint32.
 Risk:       Possible mismatch of pointer type and given length parameter after cast of untyped void pointer.
 Prevention: Component tests ensures that the vMem accesses the referenced object correctly.

 MD_vMem_30_XXspi01_PtrCastLossOfConst: rule 11.5
 Reason:     Dangerous pointer cast results in loss of const qualification.
 Risk:       An element the pointer is pointing to can be manipulated without a const qualifier.
 Prevention: vMem ensures that the element the pointer is pointing to is never manipulated.

 MD_vMem_30_XXspi01_FileScopeStatic: rule 8.9
 Reason:     File scope static, 'vMem_30_XXspi01_JobParamBackup', is only accessed in one function.
 Risk:       The file scope of this variable is unnecessary large and it could be declared within the one
             and only function where it is used.
 Prevention: This issue only occurs in a specific configuration variant where the Spi_AsyncTransmit() API is disabled.
             In other configuration variants this variable is used in more than one function. Therefore, no prevention
             is required.
 */

/* SBSW_JUSTIFICATION_BEGIN

 \ID SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer
 \DESCRIPTION A function is called with a pointer to the buffer where the the content of a flash device register is
 stored. The instance index parameter is used to retrieve the pointer to the device specific buffer.
 \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing
 a valid instance index value. The indexed register buffer array is preallocated with sufficient
 memory for each configured flash device.

 \ID SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers
 \DESCRIPTION A function is called with a pointer that was passed down to the current function.
 \COUNTERMEASURE \N No countermeasure is necessary because the caller of the current function is responsible for providing
 a valid pointer that could be passed further down.

 \ID SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter
 \DESCRIPTION A function is called with a pointer.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the given instance index.
 The referenced structure array is preallocated with one entry for each configured flash device.
 The caller of the function is therefore responsible for providing a valid instance index value.
 In case the given parameter is the instance id instead of the index, the id is mapped the index
 and checked against the max value in advance.

 \ID SBSW_vMem_30_XXspi01_ExecuteSequence
 \DESCRIPTION The flash command sequence executor submodule is called with a pointer to the sequence that shall be
 executed.
 \COUNTERMEASURE \T The validity of the used pointer to the flash command sequence that is build by the flash command
 sequence builder is verified by the test cases TCASE-963427, TCASE-963429, TCASE-963432,
 TCASE-963433, TCASE-976015, TCASE-963434, TCASE-963435, TCASE-1053573, TCASE-1157941, TCASE-1157939,
 TCASE-1157940, TCASE-1157938, TCASE-1157937, TCASE-1158033 and TCASE-1158034.

 \ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter
 \DESCRIPTION A write access is made using a pointer to the flash device job management structure.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the given instance index.
 The referenced structure array is preallocated with one entry for each configured flash device.
 The caller of the function is therefore responsible for providing a valid instance index value.
 In case the given parameter is the instance id instead of the index, the id is mapped the index
 and checked against the max value in advance.

 \ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller
 \DESCRIPTION A write access is made using a pointer to the flash device job management structure.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by the caller of the function.
 The referenced structure array is preallocated with one entry for each configured flash device.
 The caller of the function is therefore responsible for providing a valid pointer element.

 \ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop
 \DESCRIPTION A write access is made using a pointer to the flash device job management structure.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the loop variable as
 index. The referenced structure array is preallocated with one entry for each configured flash
 device. The loop iterates over every configured device and therefore only provides valid indices.

 \ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop
 \DESCRIPTION A write access is made to the flash device job management structure array using the instance index.
 \COUNTERMEASURE \N No countermeasure is necessary because the array is accessed using a loop variable as index. The
 referenced structure array is preallocated with one entry for each configured flash device. The
 loop iterates over every configured device and therefore only provides valid indices.

 \ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter
 \DESCRIPTION A write access is made to the flash device job management structure array using the instance index.
 \COUNTERMEASURE \N No countermeasure is necessary because the array is accessed using the index of the flash device
 identified by the given instance id. Because the instance id is validated by the calling module,
 every given instance id could successfully be mapped to a valid index. The referenced structure
 array is preinitialized with one entry for each configured flash device.

 \ID SBSW_vMem_30_XXspi01_WriteToArrayStoreUserRequestedJob
 \DESCRIPTION A write access is made to an array using the InstanceId.
 \COUNTERMEASURE \N The instanceId is equal to the instance's index within the array vMemInstance[] and it is
 verified during the call of vMem_Read(), vMem_Write(), vMem_Erase() and vMem_IsBlank() that
 the value of the passed instanceId is smaller than the size if the array vMemInstance[].
 The array vMem_30_XXspi01_JobParamBackup[] has the same size as vMemInstance[] and each access with
 the instanceId is therefore valid.

 \ID SBSW_vMem_30_XXspi01_FunctionCallInLoadUserRequestedJob
 \DESCRIPTION A function is called with a buffer pointer which was previously stored in a global struct.
 It must be ensured that the pointer is valid and that the instanceId, which is used to access
 the struct, is the same as the instanceId that is used to store the pointer to the vMem_JobParamBackup[].
 \COUNTERMEASURE \N No countermeasure is necessary, because the pointer was previously stored within the struct
 vMem_JobParamBackup[] via the instanceId during the call of vMem_LLStoreUserRequestedJob().
 No further access happened to this pointer. Right after that the instance's jobProgress is set to VMEM_INIT_HW.
 The vMem_JobParamBackup[] is only accessed again via the instanceId as soon as the instance
 initialization is successfully finished, see vMem_30_XXspi01_LL_Cbk_JobSucceeded().
 The function vMem_LLLoadUserRequestedJob() is only called, if an instance's jobProgress is VMEM_INIT_HW.
 So it is ensured, that the vMem_JobParamBackup[] is only accessed where previously valid job parameters
 were stored.

 \ID SBSW_vMem_30_XXspi01_FunctionCallStoreUserRequestedJob
 \DESCRIPTION The function vMem_LLStoreUserRequestedJob() is called with a pointer parameter. It must be ensured
 that the pointer points to a valid struct.
 \COUNTERMEASURE \N No countermeasure is necessary, because the passed pointer points to a struct which was
 previously created either in vMem_LLErase(), vMem_LLRead(), vMem_LLWrite() or vMem_LLIsBlank(). The struct element
 does exist as long as the function vMem_LLStoreUserRequestedJob() is called.

 \ID SBSW_vMem_30_XXspi01_FunctionCallJobFailed
 \DESCRIPTION The function vMem_LLJobFailed() is called with a pointer to the processed instance structure.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the given instance index.
 The referenced structure array is preallocated with one entry for each configured flash device.
 The caller of the function is therefore responsible for providing a valid instance index value.
 In case the given parameter is the instance id instead of the index, the id is mapped the index
 and checked against the max value in advance.

 \ID SBSW_vMem_30_XXspi01_FunctionCallJobSucceeded
 \DESCRIPTION The function vMem_LLJobSucceeded() is called with a pointer to the processed instance structure.
 \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the given instance index.
 The referenced structure array is preallocated with one entry for each configured flash device.
 The caller of the function is therefore responsible for providing a valid instance index value.
 In case the given parameter is the instance id instead of the index, the id is mapped the index
 and checked against the max value in advance.

 \ID SBSW_vMem_30_XXspi01_FunctionCallInitiateHwInitialization
 \DESCRIPTION The function vMem_LLInitiateHwInitialization() is called with a pointer to a local job parameter structure.
 \COUNTERMEASURE \N No countermeasure is necessary. The job parameter structure is created within caller function
 vMem_LLErase(), vMem_LLWrite(), vMem_LLRead() or vMem_LLIsBlank() and is valid as long as vMem_LLInitiateHwInitialization()
 is called.

 \ID SBSW_vMem_30_XXspi01_FunctionPtrCallBlankCheck
 \DESCRIPTION The function pointer variable jobEndFunc is used to either call the vMem_LLJobSucceeded() or the vMem_LLMemNotBlank(). Both
 functions provide an identical interface.
 The jobEndFunc is initially setup with vMem_LLJobSucceeded(). If the previously read page is not blank, the vMem_LLMemNotBlank()
 is assigned to jobEndFunc before it is called. In every situation the variable jobEndFunc is a valid function pointer.
 \COUNTERMEASURE \N No countermeasure is required. The jobEndFunc function pointer variable is always valid.

 \ID SBSW_vMem_30_XXspi01_WriteToArrayJedecIdBufferPtr
 \DESCRIPTION A write access is made to an array using an index.
 \COUNTERMEASURE \R The for loop ensures that the used index never exceeds the size of the array jedecIdBufferPtr.

 SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

 Variant coverage:

 \ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

 END_COVERAGE_JUSTIFICATION
 */
/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL.c
 *********************************************************************************************************************/

