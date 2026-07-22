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
/*!        \file  vStreamProc_SimpleBufferNode.c
 *        \brief  vStreamProc Pipe Simple Buffer Node Source Code File
 *
 *      \details  Implementation of the vStreamProc simple buffer storage node
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vStreamProc.h.
 *********************************************************************************************************************/
#define VSTREAMPROC_SIMPLEBUFFERNODE_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc.h"
#include "vStreamProc_SimpleBufferNode.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  MISRA & PClint
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define VSTREAMPROC_ADD_CONSUMED_AND_AVAILABLE_LENGTH(currentInfoId) \
  (vStreamProc_GetConsumedLengthOfStorageNodeBufferInfo(currentInfoId) + vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(currentInfoId))


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

#define VSTREAMPROC_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_DataAvailableCallout
 **********************************************************************************************************************/
/*! \brief          Iterate over all Output Ports and inform all subscribers of available data.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_DataAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_StreamAvailableCallout
 **********************************************************************************************************************/
/*! \brief          Iterate over all subscribers and inform them about available data stream.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_StreamAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_StorageAvailableCallout
 **********************************************************************************************************************/
/*! \brief          Iterate over all subscribers and inform them about available storage.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_StorageAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_Defragment
 **********************************************************************************************************************/
/*! \brief          Copy data from the end and overwrite consumed data to increase the available length
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \param[in]      ForceDefragment   TRUe enforces defragmentation, even if conditions aren't met
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          CREQ-205148
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_Defragment(
  vStreamProc_StorageNodeIterType StorageNodeId,
  boolean ForceDefragment);

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_ReadDataAllPorts
 **********************************************************************************************************************/
/*! \brief          Calls every consumer to read data from the buffer.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_ReadDataAllPorts(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_StorageNode_TriggerProduceCallback
 **********************************************************************************************************************/
/*! \brief          Triggers Producer to write data to the buffer.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a storage node
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_TriggerProduceCallback(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Init(
  vStreamProc_StorageNodeIdType StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_StorageOutputPortIterType outputPortIdx;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize consumed length and available length */
  vStreamProc_SetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId, 0);
  vStreamProc_SetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId,
    vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId));
  vStreamProc_SetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId, 0);

  /* #20 Initialize callbacks */
  vStreamProc_SetProduceCbkOfStorageNodeBufferInfo(StorageNodeId, NULL_PTR);

  /* #30 Initialize lock count */
  vStreamProc_SetRequestLockCntOfStorageNodeBufferInfo(StorageNodeId, 0);

  /* #40 Initialize write lock */
  vStreamProc_SetWriteRequestLockOfStorageNodeBufferInfo(StorageNodeId, FALSE);

  /* #50 Iterate over all output ports and initialize associated information */
  for ( outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
        outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
        outputPortIdx++ )
  {
    vStreamProc_SetConsumeCbkOfStorageOutputPortInfo(outputPortIdx, NULL_PTR);
    vStreamProc_SetConsumeLenOfStorageOutputPortInfo(outputPortIdx, 0);
    vStreamProc_SetRequestedConsumeLenOfStorageOutputPortInfo(outputPortIdx, 0);
    vStreamProc_SetReadRequestLockOfStorageOutputPortInfo(outputPortIdx, FALSE);
    vStreamProc_SetActiveInformationOfStorageOutputPortInfo(outputPortIdx, FALSE);
  }

  return retVal;
}
/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_Process
 **********************************************************************************************************************/
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
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Process(
  vStreamProc_StorageNodeIdType StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;
  vStreamProc_StorageOutputPortIterType outputPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if free data in the buffer is available to write data. */
  if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) != 0u)
  {
    /* #20 Trigger produce callback if one is registered. */
    if (vStreamProc_GetProduceCbkOfStorageNodeBufferInfo(StorageNodeId) != NULL_PTR)
    {
      vStreamProc_StorageNode_TriggerProduceCallback((vStreamProc_StorageNodeIterType)StorageNodeId);

      /* #30 De-register callback if all data was produced. */
      if (vStreamProc_GetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId) == 0u)
      {
        vStreamProc_SetProduceCbkOfStorageNodeBufferInfo(StorageNodeId, NULL_PTR);
      }
      /* #40 Otherwise, report PENDING if more data is available. */
      else
      {
        if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) != 0u)
        {
          retVal = VSTREAMPROC_PENDING;
        }
      }
    }
  }

  /* #50 Trigger consume callbacks. */
  vStreamProc_StorageNode_ReadDataAllPorts((vStreamProc_StorageNodeIterType)StorageNodeId);

  /* #60 Report PENDING, if there is data available which should be fetched via callbacks. */
  for ( outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
        outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
        outputPortIdx++ )
  {
    if ( (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx))
      && (vStreamProc_GetConsumeCbkOfStorageOutputPortInfo(outputPortIdx) != NULL_PTR) )
    {
      vStreamProc_LengthType availableReadLen =
        ( vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
        - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) )
        - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx);

      if (availableReadLen != 0u)
      {
        retVal = VSTREAMPROC_PENDING;
        break;
      }
    }
  }

  /* #70 Defragment buffer. */
  vStreamProc_StorageNode_Defragment((vStreamProc_StorageNodeIterType)StorageNodeId, FALSE);

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_SimpleBufferNode_Flush
**********************************************************************************************************************/
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
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Flush(
  vStreamProc_StorageNodeIdType StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;
  vStreamProc_StorageOutputPortIterType outputPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If a produce callback is registered: */
  if (vStreamProc_GetProduceCbkOfStorageNodeBufferInfo(StorageNodeId) != NULL_PTR)
  {
    retVal = VSTREAMPROC_PENDING;

    /* #20 Report PENDING if there is no free buffer available. */
    if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) != 0u)
    {
      /* #30 Otherwise: Trigger produce callback. */
      vStreamProc_StorageNode_TriggerProduceCallback((vStreamProc_StorageNodeIterType)StorageNodeId);

      /* #40 De-register callback if all data was produced. */
      if (vStreamProc_GetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId) == 0u)
      {
        vStreamProc_SetProduceCbkOfStorageNodeBufferInfo(StorageNodeId, NULL_PTR);
        retVal = VSTREAMPROC_OK;
      }
      /* #50 Otherwise, report PENDING. */
    }
  }

  /* #60 Trigger consume callbacks. */
  vStreamProc_StorageNode_ReadDataAllPorts((vStreamProc_StorageNodeIterType)StorageNodeId);

  /* #70 Report PENDING, if there is data available which should be fetched via callbacks. */
  for ( outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
        outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
        outputPortIdx++)
  {
    if ( (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx))
      && (vStreamProc_GetConsumeCbkOfStorageOutputPortInfo(outputPortIdx) != NULL_PTR) )
    {
      vStreamProc_LengthType availableReadLen = (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
                                               - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
                                               - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx);

      if (availableReadLen != 0u)
      {
        retVal = VSTREAMPROC_PENDING;
        break;
      }
    }
  }

  /* #80 Defragment buffer. */
  vStreamProc_StorageNode_Defragment((vStreamProc_StorageNodeIterType)StorageNodeId, FALSE);

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_AnnounceStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_AnnounceStream(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add Producer-Callback and RequestedProduceLen to passed storage node */
  vStreamProc_SetProduceCbkOfStorageNodeBufferInfo(StorageNodeId, ProduceCbk);
  vStreamProc_SetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId, Length);

  /* #20 Check if input buffer length fits into output buffer */
  if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) < Length)
  {
    /* #30 The buffer should only be defragmented if the resulting memory area is big enough to store the request */
    if (VSTREAMPROC_ADD_CONSUMED_AND_AVAILABLE_LENGTH(StorageNodeId) >= Length)
    {
      /* Defragment Buffer */
      vStreamProc_StorageNode_Defragment((vStreamProc_StorageNodeIterType)StorageNodeId, TRUE);
    }
  }

  /* #40 Issue the storage node's associated stream announced callout */
  vStreamProc_StorageNode_StreamAvailableCallout((vStreamProc_StorageNodeIterType)StorageNodeId);
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_WriteInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteInfo(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) WriteInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if RequestBufferPtr is a null pointer */
  if (WriteInfoPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    vStreamProc_LengthType  requestLength = WriteInfoPtr->RequestLength;
    vStreamProc_LengthType  availableLen;

    if (vStreamProc_GetRequestLockCntOfStorageNodeBufferInfo(StorageNodeId) == 0u)
    {
      availableLen  = VSTREAMPROC_ADD_CONSUMED_AND_AVAILABLE_LENGTH(StorageNodeId);
    }
    else
    {
      availableLen  = vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId);
    }

    /* #20 Update the user request with information */
    WriteInfoPtr->AvailableLength     = availableLen;
    WriteInfoPtr->DataTypeInfo.Id     = vStreamProc_GetDataElementTypeOfStorageNode(StorageNodeId);
    WriteInfoPtr->DataTypeInfo.Size   = vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

    /* #30 Report insufficient input if requested length cannot be provided. */
    if (availableLen >= requestLength)
    {
      retVal = VSTREAMPROC_OK;
    }
    else
    {
      retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_WRITE_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_WriteRequest
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteRequest(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  P2VAR(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_DATA) RequestBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if RequestBufferPtr is a null pointer */
  if (RequestBufferPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    vStreamProc_StorageInfoPtrType  storageInfo   = &RequestBufferPtr->StorageInfo;
    vStreamProc_LengthType          requestLength = storageInfo->RequestLength;
    vStreamProc_LengthType          availableLen  = vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId);

    retVal = VSTREAMPROC_OK;

    /* #20 Check if input buffer length fits into output buffer. */
    if (availableLen < requestLength)
    {
      /* #30 The buffer should only be defragmented if the resulting memory area is big enough to store the request */
      if (VSTREAMPROC_ADD_CONSUMED_AND_AVAILABLE_LENGTH(StorageNodeId) >= requestLength)
      {
        /* Defragment Buffer */
        vStreamProc_StorageNode_Defragment((vStreamProc_StorageNodeIterType)StorageNodeId, TRUE);
        availableLen = vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId);
      }
    }

    if (availableLen < requestLength)
    {
      retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
    }

    /* #40 Update the user request with information */
    storageInfo->AvailableLength    = availableLen;
    storageInfo->DataTypeInfo.Id    = vStreamProc_GetDataElementTypeOfStorageNode(StorageNodeId);
    storageInfo->DataTypeInfo.Size  = vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

    if ( (retVal == VSTREAMPROC_OK)
      && (availableLen != 0u) )
    {
      /* Use data element size to calculate byte offset into buffer. */
      vStreamProc_LengthType byteOffset = (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId) - availableLen)
        * vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);
      RequestBufferPtr->Buffer = &vStreamProc_GetStorageNodeBufferOfStorageNode(StorageNodeId)[byteOffset];

      /* Engage write lock. */
      if (vStreamProc_IsWriteRequestLockOfStorageNodeBufferInfo(StorageNodeId) == FALSE)                                /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
      {
        vStreamProc_SetWriteRequestLockOfStorageNodeBufferInfo(StorageNodeId, TRUE);
        vStreamProc_IncRequestLockCntOfStorageNodeBufferInfo(StorageNodeId);
      }
    }
    else
    {
      RequestBufferPtr->Buffer = NULL_PTR;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_WRITE_REQUEST, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_SimpleBufferNode_WriteAck
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteAck(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) ProducedLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if ProducedLen is greater than the TotalBufferLen */
  if (ProducedLen > vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
  {
    errorID = VSTREAMPROC_E_PARAM_SIZE;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #20 Update the workspace information. */
    vStreamProc_SetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId,
      vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) - ProducedLen);

    /* #30 Check if data was produced. */
    if (ProducedLen != 0u)
    {
      /* #40 Trigger data available callout. */
      vStreamProc_StorageNode_DataAvailableCallout((vStreamProc_StorageNodeIterType)StorageNodeId);
    }

    /* Release write lock. */
    if (vStreamProc_IsWriteRequestLockOfStorageNodeBufferInfo(StorageNodeId) == TRUE)                                   /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
    {
      vStreamProc_SetWriteRequestLockOfStorageNodeBufferInfo(StorageNodeId, FALSE);
      vStreamProc_DecRequestLockCntOfStorageNodeBufferInfo(StorageNodeId);
    }

    retVal = VSTREAMPROC_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_WRITE_ACK, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_RequestStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_RequestStream(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  CONST(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add consumer callback to storage node workspace */
  if (vStreamProc_GetPortScopeOfStorageOutputPort(OutputPortId) == VSTREAMPROC_EXTERNAL_PORTSCOPEOFSTORAGEOUTPUTPORT)
  {
    if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(OutputPortId) == TRUE)                                   /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
    {
      vStreamProc_SetConsumeCbkOfStorageOutputPortInfo(OutputPortId, ConsumeCbk);
      vStreamProc_SetRequestedConsumeLenOfStorageOutputPortInfo(OutputPortId, Length);

      vStreamProc_StorageNode_StreamAvailableCallout((vStreamProc_StorageNodeIterType)StorageNodeId);

      retVal = E_OK;
    }
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_ReadInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadInfo(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ReadInfoPtr,
  vStreamProc_OutputPortIdType OutputPortId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters */
  /* Check if RequestBufferPtr is a null pointer */
  if (ReadInfoPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;

    /* #20 Check if the output port is active */
    if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(OutputPortId) == TRUE)                                   /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
    {
      /* Only active consumers are allowed to read data  */
      vStreamProc_LengthType  requestLength     = ReadInfoPtr->RequestLength;
      vStreamProc_LengthType  availableDataLen  = vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
        - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)
        - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId);

      /* #30 Fill the user request with appropriate information */
      ReadInfoPtr->AvailableLength    = availableDataLen;
      ReadInfoPtr->DataTypeInfo.Id    = vStreamProc_GetDataElementTypeOfStorageNode(StorageNodeId);
      ReadInfoPtr->DataTypeInfo.Size  = vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

      /* #40 Report insufficient output if requested length cannot be provided. */
      if (availableDataLen >= requestLength)
      {
        retVal = VSTREAMPROC_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_READ_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_ReadRequest
 **********************************************************************************************************************/
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
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadRequest(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  P2VAR(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_DATA) RequestBufferPtr,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  /* Check if RequestBufferPtr is a null pointer */
  if (RequestBufferPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    vStreamProc_StorageInfoPtrType storageInfo = &RequestBufferPtr->StorageInfo;

    retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;

    RequestBufferPtr->Buffer        = NULL_PTR;
    storageInfo->AvailableLength    = 0u;
    storageInfo->DataTypeInfo.Id    = vStreamProc_GetDataElementTypeOfStorageNode(StorageNodeId);
    storageInfo->DataTypeInfo.Size  = vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

    /* #20 If the output port is active: */
    if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(OutputPortId) == TRUE)                                   /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
    {
      /* Only active consumers are allowed to read data */

      /* #30 Fill the user request with available data length. */
      storageInfo->AvailableLength  = vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
        - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)
        - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId);

      /* #40 Report insufficient output if requested length cannot be provided. Otherwise: */
      if (storageInfo->AvailableLength >= storageInfo->RequestLength)
      {
        /* Use data element size to calculate byte offset into buffer. */
        vStreamProc_LengthType byteOffset = vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId)
          * vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

        /* #50 Fill the user request with a pointer to the data buffer. */
        RequestBufferPtr->Buffer      = &vStreamProc_GetStorageNodeBufferOfStorageNode(StorageNodeId)[byteOffset];

        /* #60 Lock the buffer based on the current output port if it is not locked yet and data is available. */
        if ( (vStreamProc_IsReadRequestLockOfStorageOutputPortInfo(OutputPortId) == FALSE)                              /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
          && (storageInfo->AvailableLength != 0u) )
        {
          vStreamProc_SetReadRequestLockOfStorageOutputPortInfo(OutputPortId, TRUE);
          vStreamProc_IncRequestLockCntOfStorageNodeBufferInfo(StorageNodeId);
        }

        retVal = VSTREAMPROC_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_READ_REQUEST, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_SimpleBufferNode_ReadAck
**********************************************************************************************************************/
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
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadAck(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) ConsumedLen,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_StorageOutputPortIterType outputPortIdx;
  vStreamProc_LengthType minConsumedLen;
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters */
  /* Check if ConsumedLen is greater than the TotalBufferLen */
  if (ConsumedLen > (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
        - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)
        - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId)))
  {
    errorID = VSTREAMPROC_E_PARAM_SIZE;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = VSTREAMPROC_OK;

    /* #20 Update new consumed length for current consumer */
    vStreamProc_SetConsumeLenOfStorageOutputPortInfo(OutputPortId,
      vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId) + ConsumedLen);
    minConsumedLen = vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId);

    /* #30 Find the smallest consumer length over all consumers */
    for (outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
         outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
         outputPortIdx++)
    {
      if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx)
            && (vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx) < minConsumedLen))
      {
        minConsumedLen = vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx);
      }
    }

    /* #40 Set smallest consumer length for Storage-Node */
    vStreamProc_SetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId, minConsumedLen);

    /* #50 Release the lock based on the current output port */
    if (vStreamProc_IsReadRequestLockOfStorageOutputPortInfo(OutputPortId))
    {
      vStreamProc_SetReadRequestLockOfStorageOutputPortInfo(OutputPortId, FALSE);
      vStreamProc_DecRequestLockCntOfStorageNodeBufferInfo(StorageNodeId);
    }

    /* #60 Defragment Buffer */
    vStreamProc_StorageNode_Defragment((vStreamProc_StorageNodeIterType)StorageNodeId, FALSE);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_READ_ACK, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
*  vStreamProc_SimpleBufferNode_SetActivationSignal
**********************************************************************************************************************/
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
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_SetActivationSignal(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId,
  CONST(vStreamProc_OutputActivationType, AUTOMATIC) ActivationSignalValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check if the activation signal is going to be changed */
  /* HINT: There is no GetActiveInformation(), so we have to "cast" ActivationSignalValue to a boolean expression first. */
  if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(OutputPortId) != (ActivationSignalValue == TRUE) )
  {
    vStreamProc_LengthType currentWriteIndex = (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
      - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId));
    if (ActivationSignalValue == TRUE)
    {
      /* #20 When the output port gets activated adjust its consumer information
        *      The consumer can not read old data, only new data is provided to the new consumer
        */
      vStreamProc_SetConsumeLenOfStorageOutputPortInfo(OutputPortId, currentWriteIndex);

      retVal = E_OK;
    }
    else
    {
      /* #30 When the output port gets deactivated make sure that all data is consumed and no lock is set */
      if ( (vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId) != currentWriteIndex)
        || vStreamProc_IsReadRequestLockOfStorageOutputPortInfo(OutputPortId) )
      {
#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
        /* Error: there is data available which is not consumed yet */
        (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_SET_MODE, VSTREAMPROC_E_INVALID_META_STATE_SWITCHING);
#endif /* VSTREAMPROC_DEV_ERROR_REPORT */
      }
      else
      {
        retVal = E_OK;
      }
    }

    if (retVal == E_OK)
    {
      /* #40 Change the signal value */
      vStreamProc_SetActiveInformationOfStorageOutputPortInfo(OutputPortId, ActivationSignalValue);
    }
  }
  else
  {
    /* Nothing to do */
    retVal = E_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  vStreamProc_StorageNode_DataAvailableCallout
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_DataAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_StorageOutputPortIterType outputPortIdx;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Iterate over all Output Ports and inform all subscribers of available data */
  for (outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
       outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
       outputPortIdx++)
  {
    if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx))
    {
      vStreamProc_GetDataAvailableCalloutOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(StorageNodeId))(
        (vStreamProc_OutputPortIdType)outputPortIdx, vStreamProc_GetSchedulerIdxOfStorageNode(StorageNodeId));

      if (vStreamProc_GetConsumeCbkOfStorageOutputPortInfo(outputPortIdx) != NULL_PTR)
      {
        vStreamProc_StorageNode_StreamAvailableCallout(StorageNodeId);
      }
    }
  }
}

/***********************************************************************************************************************
*  vStreamProc_StorageNode_StreamAvailableCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_StreamAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Inform the subscriber of an available stream */
  vStreamProc_GetStreamAvailableCalloutOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(StorageNodeId))(
    vStreamProc_GetNodeIdxOfStorageNode(StorageNodeId),
    vStreamProc_GetSchedulerIdxOfStorageNode(StorageNodeId));
}

/***********************************************************************************************************************
*  vStreamProc_StorageNode_StorageAvailableCallout
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_StorageAvailableCallout(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_StorageInputPortIterType  storageInputPortId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Inform all subscribers of available storage. */
  for ( storageInputPortId = vStreamProc_GetStorageInputPortStartIdxOfStorageNode(StorageNodeId);
        storageInputPortId < vStreamProc_GetStorageInputPortEndIdxOfStorageNode(StorageNodeId);
        storageInputPortId++ )
  {
    vStreamProc_GetStorageAvailableCalloutOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(StorageNodeId))(
      (vStreamProc_InputPortIdType)storageInputPortId,
      vStreamProc_GetSchedulerIdxOfStorageNode(StorageNodeId));
  }

  if (vStreamProc_GetProduceCbkOfStorageNodeBufferInfo(StorageNodeId) != NULL_PTR)
  {
    vStreamProc_StorageNode_StreamAvailableCallout(StorageNodeId);
  }
}

/***********************************************************************************************************************
*  vStreamProc_StorageNode_Defragment
**********************************************************************************************************************/
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
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_Defragment(
  vStreamProc_StorageNodeIterType StorageNodeId,
  boolean ForceDefragment)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_StorageOutputPortIterType outputPortIdx;
  vStreamProc_StorageNodeBufferIterType targetIdx;
  vStreamProc_StorageNodeBufferIterType upperBufferBoundary;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Defragmentation should be executed only if:
   *      No read operation is pending (buffer is locked) and
   *      Any data was consumed and
   *      the remaining amount of free memory is smaller than the configured threshold or size of the data elements
   *      or
   *      All data was consumed
   *      or
   *      Enforced by caller
   */
  if (vStreamProc_GetRequestLockCntOfStorageNodeBufferInfo(StorageNodeId) == 0u)
  {
    boolean performDefrag = FALSE;

    if (vStreamProc_GetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId) != 0u)
    {
      performDefrag = ForceDefragment;

      if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) < vStreamProc_GetDefragmentThresholdOfStorageNode(StorageNodeId))
      {
        performDefrag = TRUE;
      }
      else
      {
        if (VSTREAMPROC_ADD_CONSUMED_AND_AVAILABLE_LENGTH(StorageNodeId) == vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId))
        {
          performDefrag = TRUE;
        }
      }
    }

    if (performDefrag == TRUE)
    {
      vStreamProc_StorageNodeBufferType     buffer    = vStreamProc_GetStorageNodeBufferOfStorageNode(StorageNodeId);
      vStreamProc_StorageNodeBufferIterType sourceIdx =
        (vStreamProc_StorageNodeBufferIterType)vStreamProc_GetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId);

      /* #20 Copy data from the end and overwrite consumed data */
      upperBufferBoundary = ((vStreamProc_StorageNodeBufferIterType)(vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
        - sourceIdx
        - (vStreamProc_StorageNodeBufferIterType)vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
        * (vStreamProc_StorageNodeBufferIterType)vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId));

      /* Convert element index to byte index. */
      sourceIdx *= (vStreamProc_StorageNodeBufferIterType)vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

      for (targetIdx = 0u; targetIdx < upperBufferBoundary; targetIdx++)
      {
        buffer[targetIdx] = buffer[sourceIdx];
        /* Delete copied data */
        buffer[sourceIdx] = 0u;

        sourceIdx++;
      }

      /* #30 Update storage Workspaces after defragment */
      for ( outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
            outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
            outputPortIdx++ )
      {
        if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx) == TRUE)                              /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
        {
          vStreamProc_SetConsumeLenOfStorageOutputPortInfo(outputPortIdx,
            vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx)
            - vStreamProc_GetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId));
        }
      }

      vStreamProc_SetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId,
        vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)
        + vStreamProc_GetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId));

      vStreamProc_SetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId, 0u);

      /* #40 Inform subscribers of available storage. */
      vStreamProc_StorageNode_StorageAvailableCallout(StorageNodeId);
    }
  }
}

/***********************************************************************************************************************
*  vStreamProc_StorageNode_ReadDataAllPorts
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_ReadDataAllPorts(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_StorageOutputPortIterType outputPortIdx;
  vStreamProc_LengthType                minConsumedLen  = VSTREAMPROC_MAX_LENGTH;
  boolean                               lengthValid     = FALSE;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Iterate over all consumer and call callback to read data from the buffer */
  for (outputPortIdx = vStreamProc_GetStorageOutputPortStartIdxOfStorageNode(StorageNodeId);
       outputPortIdx < vStreamProc_GetStorageOutputPortEndIdxOfStorageNode(StorageNodeId);
       outputPortIdx++)
  {
    if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(outputPortIdx) == TRUE)                                  /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
    {
      if (vStreamProc_GetConsumeCbkOfStorageOutputPortInfo(outputPortIdx) != NULL_PTR)
      {
        /* Check if buffer is not empty */
        if ( (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId) - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)) != 0u )
        {
          vStreamProc_LengthType consumedLen  = 0u;
          /* Use data element size to calculate byte offset into buffer. */
          vStreamProc_LengthType byteOffset   = vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx)
            * vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

          /* Call callback */
          vStreamProc_GetConsumeCbkOfStorageOutputPortInfo(outputPortIdx)(
            &vStreamProc_GetStorageNodeBufferOfStorageNode(StorageNodeId)[byteOffset],
            (((vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
                - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
                - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx))),
            &consumedLen);

          /* Consumed length is given in number of data elements. Calculate byte length. */
          consumedLen *= vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

          /* Check modified callback parameter */
#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
          if (  (vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx) + consumedLen
                  + vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
              > vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId))
          {
            (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_PROCESS, VSTREAMPROC_E_PARAM_SIZE);
          }
          else
#endif /* VSTREAMPROC_DEV_ERROR_REPORT */
          {
            /* Update consumedLen of ExitPort */
            vStreamProc_SetConsumeLenOfStorageOutputPortInfo(outputPortIdx,
              vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx) + consumedLen);
          }
#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
          if (vStreamProc_GetRequestedConsumeLenOfStorageOutputPortInfo(outputPortIdx) < consumedLen)
          {
            (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_PROCESS, VSTREAMPROC_E_PARAM_SIZE);
          }
          else
#endif /* VSTREAMPROC_DEV_ERROR_REPORT */
          {
            /* Update requested consumedLen of ExitPort */
            vStreamProc_SetRequestedConsumeLenOfStorageOutputPortInfo(outputPortIdx,
              vStreamProc_GetRequestedConsumeLenOfStorageOutputPortInfo(outputPortIdx) - consumedLen);

            /* #20 Check if all data is consumed */
            if (vStreamProc_GetRequestedConsumeLenOfStorageOutputPortInfo(outputPortIdx) == 0u)
            {
              vStreamProc_SetConsumeCbkOfStorageOutputPortInfo(outputPortIdx, NULL_PTR);
            }
          }
        }
      }

      /* #30 Find the smallest consumer length over all consumers */
      if (vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx) < minConsumedLen)
      {
        minConsumedLen  = vStreamProc_GetConsumeLenOfStorageOutputPortInfo(outputPortIdx);
        lengthValid     = TRUE;
      }
    }
  }

  /* #40 Set smallest consumer length for the Storage-Node */
  if (lengthValid == TRUE)
  {
    vStreamProc_SetConsumedLengthOfStorageNodeBufferInfo(StorageNodeId, minConsumedLen);
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
*  vStreamProc_StorageNode_TriggerProduceCallback
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_StorageNode_TriggerProduceCallback(
  CONST(vStreamProc_StorageNodeIterType, AUTOMATIC) StorageNodeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_LengthType producedLen  = 0;
  /* Use data element size to calculate byte offset into buffer. */
  vStreamProc_LengthType byteOffset   = ( (vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
    - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId))
    * vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId) );

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Trigger produce callback */
  vStreamProc_GetProduceCbkOfStorageNodeBufferInfo(StorageNodeId)(
    &vStreamProc_GetStorageNodeBufferOfStorageNode(StorageNodeId)[byteOffset],
    (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) / vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId)), &producedLen);

  /* Produced length is given in number of data elements. Calculate byte length.*/
  producedLen *= vStreamProc_GetDataElementSizeOfStorageNode(StorageNodeId);

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) < producedLen)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_PROCESS, VSTREAMPROC_E_PARAM_SIZE);
  }
  else if (vStreamProc_GetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId) < producedLen)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_PROCESS, VSTREAMPROC_E_PARAM_SIZE);
  }
  else
#endif /* VSTREAMPROC_DEV_ERROR_REPORT */
  {
    /* #20 Check if new data is available and inform the consumer */
    if (producedLen != 0u)
    {
      vStreamProc_SetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId,
        vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId) - producedLen);

      vStreamProc_SetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId,
        vStreamProc_GetRequestedProduceLengthOfStorageNodeBufferInfo(StorageNodeId) - producedLen);

      vStreamProc_StorageNode_DataAvailableCallout(StorageNodeId);
    }
  }
}

/***********************************************************************************************************************
*  vStreamProc_SimpleBufferNode_IsEmpty
**********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
FUNC(boolean, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_IsEmpty(
  vStreamProc_StorageNodeIdType StorageNodeId,
  vStreamProc_OutputPortIdType OutputPortId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the output port is active */
  if (vStreamProc_IsActiveInformationOfStorageOutputPortInfo(OutputPortId) == TRUE)                                     /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    vStreamProc_LengthType  availableDataLen = vStreamProc_GetStorageNodeBufferLengthOfStorageNode(StorageNodeId)
      - vStreamProc_GetAvailableLengthOfStorageNodeBufferInfo(StorageNodeId)
      - vStreamProc_GetConsumeLenOfStorageOutputPortInfo(OutputPortId);

    /* #20 Port is not empty if data is remaining. */
    if (availableDataLen > 0u)
    {
      retVal = FALSE;
    }
  }

  return retVal;
}

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_SimpleBufferNode.c
 *********************************************************************************************************************/
