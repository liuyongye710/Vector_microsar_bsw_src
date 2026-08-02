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
/*!       \file   vStreamProc_ProcessingNode_Trigger.c
 *        \brief  vStreamProc Trigger Processing Node Source Code File
 *
 *      \details  Implementation of the vStreamProc trigger processing node
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
#define VSTREAMPROC_PROCESSINGNODE_TRIGGER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_Trigger.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_TRIGGER_CONFIG == STD_ON)
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

#if !defined (VSTREAMPROC_LOCAL_INLINE)
# define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_GetMinMaxLength()
**********************************************************************************************************************/
/*! \brief      Gets minimum and maximum length of available input data
 *  \details    Function loops over all input ports and return minimum and maximum value of attached storage nodes.
 *  \param[in]  InputPortInfos    The input port information structures.
 *  \param[in]  InputPortCount    The number of input ports.
 *  \param[out] MinLength         The minimum length.
 *  \param[out] MaxLength         The maximum length.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_GetMinMaxLength(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MinLength,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MaxLength);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_GetMinMaxLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_GetMinMaxLength(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MinLength,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MaxLength)
{
  vStreamProc_LengthType      minLength = VSTREAMPROC_MAX_LENGTH;
  vStreamProc_LengthType      maxLength = 0u;
  vStreamProc_InputPortIdType inputInfoIndex;

  /* #10 Loop over all connected input ports and report minimum and maximum value. */
  for (inputInfoIndex = 0u; inputInfoIndex < InputPortCount; inputInfoIndex++)
  {
    vStreamProc_LengthType currentLength = InputPortInfos[inputInfoIndex].ReadRequest.StorageInfo.AvailableLength;

    if (InputPortInfos[inputInfoIndex].IsConnected == TRUE)
    {
      if (currentLength < minLength)
      {
        minLength = currentLength;
      }

      if (currentLength > maxLength)
      {
        maxLength = currentLength;
      }
    }
  }

  *MinLength = minLength;
  *MaxLength = maxLength;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */

  VSTREAMPROC_DUMMY_STATEMENT_CONST(NodeInfo);

  /* #10 No action, simply return E_OK. */
  return E_OK;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Process
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
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType            retVal = VSTREAMPROC_FAILED;

  vStreamProc_InputPortInfoType     inputPortInfos[vStreamProcConf_InputPortCount_Internal_TriggerNode];
  vStreamProc_InputPortIdType       inputPortCount  = NodeInfo->InputPortCount;
  vStreamProc_OutputPortInfoType    outputPortInfo;

  vStreamProc_LengthType minInputLength = VSTREAMPROC_MAX_LENGTH;
  vStreamProc_LengthType maxInputLength = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Evaluate minimum and maximum available length at all input ports:
   *  + No data is available at all: Processing is idle.
   *  + Only some ports have no data: Report insufficient input.
   *  + Data available for all ports: Process minimum length.
   */
  if (vStreamProc_PrepareAllPortInfos(NodeInfo, inputPortInfos, inputPortCount, &outputPortInfo, 1u) == VSTREAMPROC_OK)
  {
    if (vStreamProc_GetPortInfos(NodeInfo, inputPortInfos, inputPortCount, &outputPortInfo, 1u) == VSTREAMPROC_OK)
    {
      vStreamProc_ProcessingNode_Trigger_GetMinMaxLength(inputPortInfos, inputPortCount, &minInputLength, &maxInputLength);

      /* Maximum length only set when at least one port has data. */
      if (maxInputLength == 0u)
      {
        retVal = VSTREAMPROC_OK;
      }
      else if (minInputLength == 0u)
      {
        vStreamProc_InputPortIdType inputInfoIndex;

        retVal = VSTREAMPROC_INSUFFICIENT_INPUT;

        /* Set port specific result for all connected input ports without any data. */
        for (inputInfoIndex = 0u; inputInfoIndex < inputPortCount; inputInfoIndex++)
        {
          vStreamProc_InputPortInfoConstPtrType inputPortInfo = &inputPortInfos[inputInfoIndex];

          if ( (inputPortInfo->IsConnected == TRUE)
            && (inputPortInfo->ReadRequest.StorageInfo.AvailableLength == 0u) )
          {
            NodeInfo->InputPortResults[inputInfoIndex] = VSTREAMPROC_INSUFFICIENT_INPUT;
          }
        }
      }
      /* #20 Check if there is enough output data. */
      else
      {
        vStreamProc_LengthType availableOutput = outputPortInfo.WriteRequest.StorageInfo.AvailableLength;

        if (availableOutput < minInputLength)
        {
          /* Output buffer cannot hold all available input data and therefore amount must be reduced. */
          minInputLength = availableOutput;
        }

        /* In case output port can't hold any data: Report insufficient output. */
        if (minInputLength == 0u)
        {
          retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
          NodeInfo->OutputPortResults[vStreamProcConf_Internal_TriggerNode_ResultData] = VSTREAMPROC_INSUFFICIENT_OUTPUT;
        }
        else
        {
          retVal = VSTREAMPROC_PENDING;
        }
      }
    }
  }

  /* #30 Calculate result over all input data. */
  if (retVal == VSTREAMPROC_PENDING)
  {
    vStreamProc_StorageInfoPtrType  outputStorageInfo   = &outputPortInfo.WriteRequest.StorageInfo;
    vStreamProc_DataTypeIdType      referenceDataTypeId = outputStorageInfo->DataTypeInfo.Id;
    vStreamProc_InputPortIdType     inputInfoIndex;

    for (inputInfoIndex = 0u; inputInfoIndex < inputPortCount; inputInfoIndex++)
    {
      vStreamProc_StorageInfoPtrType inputStorageInfo = &inputPortInfos[inputInfoIndex].ReadRequest.StorageInfo;

      inputStorageInfo->RequestLength    = minInputLength;
      /* Ensure that all input ports have the same data type as the output. */
      inputStorageInfo->DataTypeInfo.Id  = referenceDataTypeId;
    }

    outputStorageInfo->RequestLength = minInputLength;

    retVal = vStreamProc_RequestPortData(NodeInfo, inputPortInfos, inputPortCount, &outputPortInfo, 1u);

    if (retVal == VSTREAMPROC_OK)
    {
      vStreamProc_StorageNodeBufferIterType dataIndex;
      P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) outputBuffer = outputPortInfo.WriteRequest.Buffer;
      /* Perform byte-wise operation. */
      vStreamProc_LengthType processingLength = minInputLength * outputStorageInfo->DataTypeInfo.Size;

      /* Set start value for AND operation. */
      for (dataIndex = 0u; dataIndex < processingLength; dataIndex++)
      {
        outputBuffer[dataIndex] = 0xFFu;
      }

      for (inputInfoIndex = 0u; inputInfoIndex < inputPortCount; inputInfoIndex++)
      {
        P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) inputBuffer = inputPortInfos[inputInfoIndex].ReadRequest.Buffer;

        for (dataIndex = 0; dataIndex < processingLength; dataIndex++)
        {
          outputBuffer[dataIndex] &= inputBuffer[dataIndex];
        }
      }

      /* #40 Acknowledge consumed and produced data. */
      retVal = vStreamProc_AcknowledgePorts(NodeInfo, inputPortInfos, inputPortCount, &outputPortInfo, 1u);
    }
  }

  if (retVal == VSTREAMPROC_OK)
  {
    if (maxInputLength > minInputLength)
    {
      retVal = VSTREAMPROC_PENDING;
    }
  }

  return retVal;
} /* PRQA S 6080, 6010, 6030 */ /* MD_MSR_STMIF, MD_MSR_STPTH, MD_MSR_STCYC */

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_Trigger_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_Trigger_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process any pending input. */
  retVal = vStreamProc_ProcessingNode_Trigger_Process(NodeInfo);

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_TRIGGER_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_Trigger.c
 *********************************************************************************************************************/
