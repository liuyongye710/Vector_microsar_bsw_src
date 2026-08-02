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
/*!        \file  vMem_30_XXspi01_LL_InstanceModifier.c
 *        \brief  -
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_LL_INSTANCEMODIFIER

/*********************************************************************************************************************
 *  INLCUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_InstanceModifier.h"
#include "vMem_30_XXspi01_Cfg.h"
#include "vMem_30_XXspi01_LL_Cbk_Int.h"
#include "vMem_30_XXspi01_IntShared.h"
#include "vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h"
#include "vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h"
#include "vMem_30_XXspi01_LL_InstanceAccess_Shared.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined(VMEM_30_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
#define VMEM_30_XXSPI01_LOCAL static
#endif

/*! This enum defines the InstanceModifier's states. */
typedef enum
{
  VMEM_30_XXSPI01_INSTANCEMODIFIER_IDLE = 0,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_EXECUTE,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_PROGRESS,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_EXTENDED_PROGRESS_CHECK,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_WRITE_DISABLE,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_RESULT,
  VMEM_30_XXSPI01_INSTANCEMODIFIER_CLEAR_RESULT_REGISTER
} vMem_30_XXspi01_LL_InstanceModifier_ProgressType;

/*! Instance's write job type to group an instance's job parameters. */
typedef struct
{
  vMem_30_XXspi01_InstanceIdType InstanceId;
  vMem_30_XXspi01_DeviceIdType DeviceId;
  vMem_30_XXspi01_LL_InstanceModifier_ProgressType JobProgress;
  vMem_30_XXspi01_InstanceIdType AffectedSector; /*! Specifies the index of the sector which is affected by the operation according to the received target address. */
  vMem_30_XXspi01_SpiDataType ResultBitMask;
  boolean isExtendedProgressCheckFinish;
  boolean isResultCheckFinish;
  boolean isWriteDisableFinish;
  boolean isProgressCheckFinish;
  boolean isJobFailed;
  vMem_30_XXspi01_BusyCheckTimeoutThresholdOfvMemInstanceType BusyCheckTimeoutCounter;
} vMem_30_XXspi01_LL_InstanceModifier_InstanceJobType;

typedef P2VAR(vMem_30_XXspi01_LL_InstanceModifier_InstanceJobType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType;

/*********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* According to [SWS_Spi_00355] and [SWS_Spi_00437] each of these data buffers must be 32 bit aligned. Therefore, the size is initialized with VMEM_30_XXSPI01_32BIT_ALIGNMENT (4u). */
/*! Defines a buffer for each configured flash device to store the content of read device registers. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_LL_InstanceModifier_InstanceJobType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[vMem_30_XXspi01_GetSizeOfvMemInstance()];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded()
 *********************************************************************************************************************/
/*! \brief        Resets the instance specific state machine and notifies the vMem_LL about the successfully finished
 erase operation.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_JobFailed()
 *********************************************************************************************************************/
/*! \brief        Resets the instance specific state machine and notifies the vMem_LL about the failed erase operation.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_JobFailed(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady()
 *********************************************************************************************************************/
/*! \brief        Checks if the memory device is ready to accept further requests.
 *  \details      -
 *  \param[in]   instanceId           ID and index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The device is ready.
 *  \return       FALSE             - The device is busy.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded()
 *********************************************************************************************************************/
/*! \brief        Checks if the extended progress check indicates that the external device is ready
 *                to accept further requests.
 *  \details      This extended progress check is an optionally configurable feature. There are devices
 *                with two BUSY flags. The extended progress check checks the additional BUSY flag.
 *  \param[in]   instanceId           ID and index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The device is ready.
 *  \return       FALSE             - The device is busy.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded()
 *********************************************************************************************************************/
/*! \brief        Checks if the write/erase error flag is set.
 *  \details      If the write/erase error flag is set the previously performed operation is failed.
 *  \param[in]   instanceId           ID and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    resultBitMask
 *  \return       TRUE              - The operation was successful.
 *  \return       FALSE             - The operation failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_SpiDataType resultBitMask);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read status register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read extended progress check register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read result register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck()
 *********************************************************************************************************************/
/*! \brief        Checks if any further optionally configured, instance-specific checks must be performed.
 *  \details      If configured, this function triggers the instance-specific extended progress check, or the result check.
 *                Otherwise the job is finished.
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckProgress()
 *********************************************************************************************************************/
/*! \brief        Checks the current write progress after the device's status register has been read.
 *  \details      Checks the previously read device's BUSY flag and triggers any further optionally configured
 *                progress check. If the device is still busy, the status register is read once again.
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckProgress(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgressState()
 *********************************************************************************************************************/
/*! \brief        Checks if the instance-specific extended progress check was successful and initializes the next
 *                progress step.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgress(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckResult()
 *********************************************************************************************************************/
/*! \brief        Checks if the instance-specific result check was successful.
 *  \details      If the result check was successful, the job is finished. Otherwise the result check register
 *                must be cleared.
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckResult(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "clear result register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_WriteDisable()
 *********************************************************************************************************************/
/*! \brief        Sets up the "Write Disable" - sequence and triggers its transmission.
 *  \details      -
 *  \param[in]    processedModifierInstance           Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_WriteDisable(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance);

/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  vMem_30_XXspi01_LL_Cbk_JobSucceeded(processedModifierInstance->InstanceId);
} /* vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_JobFailed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_JobFailed(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  vMem_30_XXspi01_LL_Cbk_JobFailed(processedModifierInstance->InstanceId);
} /* vMem_30_XXspi01_LL_InstanceModifier_JobFailed */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  boolean retVal = FALSE;
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId].DeviceId;

  if ((vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[instanceId])
      & vMem_30_XXspi01_LL_CfgDevice_GetStatusRegBusyFlagBitMask(deviceId)) == 0x00u) /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded()
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
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  boolean retVal;
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId].DeviceId;
  vMem_30_XXspi01_SpiDataType registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[instanceId]);

  /*
   * In general, the BUSY flag of the "Extended progress check" register is inverted. That means '0' is BUSY and '1' is IDLE.
   */
  if ((registerContent & vMem_30_XXspi01_LL_CfgDevice_GetExtendedProgressCheckRegBusyFlagBitMask(deviceId))
      == vMem_30_XXspi01_LL_CfgDevice_GetExtendedProgressCheckRegBusyFlagBitMask(deviceId))
  {
    retVal = TRUE;
  }
  else
  {
    retVal = FALSE;
  }

  return retVal;
} /* vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_SpiDataType resultBitMask)
{
  boolean retVal = FALSE;

  if ((vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId].DeviceId,
      vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[instanceId]) & resultBitMask) == 0x00u) /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType sequencePtr;

  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence(processedModifierInstance->InstanceId,
      processedModifierInstance->DeviceId, processedModifierInstance->AffectedSector,
      vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[processedModifierInstance->InstanceId],
      vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(processedModifierInstance->DeviceId)); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_PROGRESS; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, sequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType sequencePtr;

  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence(
      processedModifierInstance->InstanceId, processedModifierInstance->DeviceId,
      processedModifierInstance->AffectedSector,
      vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[processedModifierInstance->InstanceId],
      vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(processedModifierInstance->DeviceId)); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_EXTENDED_PROGRESS_CHECK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, sequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType sequencePtr;

  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence(processedModifierInstance->InstanceId,
      processedModifierInstance->DeviceId, processedModifierInstance->AffectedSector,
      vMem_30_XXspi01_LL_InstanceModifier_RegisterDataBuffers[processedModifierInstance->InstanceId],
      vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(processedModifierInstance->DeviceId)); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_RESULT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, sequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck()
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
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  /*
   * Result Check: The result check is the first optional check to be executed. If enabled, the result check is
   * executed right before and right after the progress check.
   */
  if ((processedModifierInstance->isJobFailed == FALSE)
      && (vMem_30_XXspi01_LL_CfgDevice_IsResultCheckEnabled(processedModifierInstance->DeviceId))
      && (processedModifierInstance->isResultCheckFinish == FALSE))
  {
    vMem_30_XXspi01_LL_InstanceModifier_ReadResultRegister(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  /*
   * Progress Check: The progress check is the only mandatory check. The progress check is repeated until either the external device is idle
   * or until the configured timeout threshold expires.
   */
  else if ((processedModifierInstance->isJobFailed == FALSE)
      && (processedModifierInstance->isProgressCheckFinish == FALSE))
  {
    vMem_30_XXspi01_LL_InstanceModifier_ReadStatusRegister(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  /*
   * Extended Progress Check: The extended progress check is an optional check which is executed after the progress check indicates that the external
   * device is idle.
   */
  else if ((processedModifierInstance->isJobFailed == FALSE)
      && (vMem_30_XXspi01_LL_CfgDevice_IsExtendedProgressCheckEnabled(processedModifierInstance->DeviceId))
      && (processedModifierInstance->isExtendedProgressCheckFinish == FALSE))
  {
    processedModifierInstance->BusyCheckTimeoutCounter = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
        vMem_30_XXspi01_LL_CfgInstance_GetBusyCheckTimeoutThreshold(processedModifierInstance->InstanceId);
    vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  /*
   * Write Disable: The write disable is an optional command execution. If enabled, write disable must be executed in any case at the end of any access
   * to the external device. Even if the access fails.
   */
  else if (vMem_30_XXspi01_LL_CfgDevice_IsWriteDisableCmdEnabled(processedModifierInstance->DeviceId)
      && (processedModifierInstance->isWriteDisableFinish == FALSE))
  {
    vMem_30_XXspi01_LL_InstanceModifier_WriteDisable(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  /* Job failed. */
  else if(processedModifierInstance->isJobFailed == TRUE)
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  /* Job succeeded. */
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobSucceeded(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckProgress()
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
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckProgress(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  if (vMem_30_XXspi01_LL_InstanceModifier_IsDeviceReady(processedModifierInstance->InstanceId) == TRUE)
  {
    processedModifierInstance->isProgressCheckFinish = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    processedModifierInstance->isResultCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    processedModifierInstance->BusyCheckTimeoutCounter =  /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
        vMem_30_XXspi01_LL_CfgInstance_GetBusyCheckTimeoutThreshold(processedModifierInstance->InstanceId);
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    processedModifierInstance->BusyCheckTimeoutCounter--; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    if (processedModifierInstance->BusyCheckTimeoutCounter > 0u)
    {
      processedModifierInstance->isResultCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
      processedModifierInstance->isProgressCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    }
    else
    {
      processedModifierInstance->isJobFailed = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    }

    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_CheckProgress */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgress()
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
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgress(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  if (vMem_30_XXspi01_LL_InstanceModifier_IsExtendedProgressCheckSucceeded(
      processedModifierInstance->InstanceId) == TRUE)
  {
    processedModifierInstance->BusyCheckTimeoutCounter = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
        vMem_30_XXspi01_LL_CfgInstance_GetBusyCheckTimeoutThreshold(processedModifierInstance->InstanceId);
    processedModifierInstance->isExtendedProgressCheckFinish = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    processedModifierInstance->BusyCheckTimeoutCounter--; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    if (processedModifierInstance->BusyCheckTimeoutCounter > 0u)
    {
      vMem_30_XXspi01_LL_InstanceModifier_ReadExtendedProgressCheckRegister(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
    else
    {
      processedModifierInstance->isJobFailed = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
      vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgress */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_CheckResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_CheckResult(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  processedModifierInstance->isResultCheckFinish = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

  if (vMem_30_XXspi01_LL_InstanceModifier_IsOperationSucceeded(processedModifierInstance->InstanceId,
      processedModifierInstance->ResultBitMask) == TRUE)
  {
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    processedModifierInstance->isJobFailed = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_CheckResult */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType sequencePtr;

  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence(
      processedModifierInstance->InstanceId, processedModifierInstance->DeviceId);

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_CLEAR_RESULT_REGISTER; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, sequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_ClearResultRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_WriteDisable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_WriteDisable(
    vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType writeDisableSequencePtr;

  writeDisableSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDisableSequence(
      processedModifierInstance->InstanceId, processedModifierInstance->DeviceId); /* PRQA S 0316, 0311 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr, MD_vMem_30_XXspi01_PtrCastLossOfConst */

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(writeDisableSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->isWriteDisableFinish = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_WRITE_DISABLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, writeDisableSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_WriteDisable */

/*********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_AddressType targetAddress,
    vMem_30_XXspi01_ConstSpiDataPtrType sourceAddressPtr, vMem_30_XXspi01_LengthType length)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType writeSequencePtr;
  vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance =
      &vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId];

  writeSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence(instanceId, deviceId, targetAddress,
      (vMem_30_XXspi01_SpiDataPtrType) sourceAddressPtr, (vMem_30_XXspi01_SpiLengthType) length); /* PRQA S 0316, 0311 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr, MD_vMem_30_XXspi01_PtrCastLossOfConst */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(writeSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->InstanceId = instanceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->DeviceId = deviceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->ResultBitMask = (vMem_30_XXspi01_SpiDataType)vMem_30_XXspi01_LL_CfgDevice_GetResultRegProgramErrorBitMask( /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        deviceId);
    processedModifierInstance->AffectedSector = vMem_30_XXspi01_GetSectorIndex(instanceId, targetAddress); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_EXECUTE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isExtendedProgressCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isResultCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isWriteDisableFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isProgressCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isJobFailed = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->BusyCheckTimeoutCounter = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        vMem_30_XXspi01_LL_CfgInstance_GetBusyCheckTimeoutThreshold(instanceId);

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, writeSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId,
    vMem_30_XXspi01_AddressType targetAddress)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType eraseSequencePtr;
  vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance =
      &vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId];

  processedModifierInstance->AffectedSector = vMem_30_XXspi01_GetSectorIndex(instanceId, targetAddress); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */

  if (vMem_30_XXspi01_LL_CfgSector_GetSectorClass(processedModifierInstance->AffectedSector)
      == VMEM_30_XXSPI01_STANDARD_SIZED_SECTOR)
  {
    eraseSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence(instanceId, deviceId, targetAddress);
  }
  else
  {
    eraseSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetSmallSectorEraseSequence(instanceId, deviceId,
        targetAddress);
  }

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(eraseSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedModifierInstance->InstanceId = instanceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->DeviceId = deviceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->ResultBitMask =
        (vMem_30_XXspi01_SpiDataType) vMem_30_XXspi01_LL_CfgDevice_GetResultRegEraseErrorBitMask( /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        deviceId);
    processedModifierInstance->JobProgress = VMEM_30_XXSPI01_INSTANCEMODIFIER_EXECUTE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isExtendedProgressCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isResultCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isWriteDisableFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isProgressCheckFinish = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->isJobFailed = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedModifierInstance->BusyCheckTimeoutCounter = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        vMem_30_XXspi01_LL_CfgInstance_GetBusyCheckTimeoutThreshold(instanceId);

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedModifierInstance->InstanceId, eraseSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceModifier_JobFailed(processedModifierInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_Processing()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_Processing(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_LL_InstanceModifier_InstanceJobPtrType processedModifierInstance =
      &vMem_30_XXspi01_LL_InstanceModifier_InstanceJobInfo[instanceId];

  switch (processedModifierInstance->JobProgress)
  {
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_EXECUTE:
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_PROGRESS:
    vMem_30_XXspi01_LL_InstanceModifier_CheckProgress(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_EXTENDED_PROGRESS_CHECK:
    vMem_30_XXspi01_LL_InstanceModifier_CheckExtendedProgress(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_CHECK_RESULT:
    vMem_30_XXspi01_LL_InstanceModifier_CheckResult(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_CLEAR_RESULT_REGISTER:
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEMODIFIER_WRITE_DISABLE:
    vMem_30_XXspi01_LL_InstanceModifier_TriggerNextProgressCheck(processedModifierInstance); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    break;
  default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* VMEM_30_XXSPI01_INSTANCEMODIFIER_IDLE */
    break;
  }
} /* vMem_30_XXspi01_LL_InstanceModifier_Processing */

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceModifier.c
 *********************************************************************************************************************/
