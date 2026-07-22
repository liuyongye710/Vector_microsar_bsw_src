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
/*!       \file   vStreamProc_ProcessingNode_ByteCompare.c
 *        \brief  vStreamProc Byte Compare Processing Node Source Code File
 *
 *      \details  Implementation of the vStreamProc byte compare processing node
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
#define VSTREAMPROC_PROCESSINGNODE_BYTE_COMPARE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_ProcessingNode_ByteCompare.h"
#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_CONFIG == STD_ON)
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (VSTREAMPROC_LOCAL)
#  define VSTREAMPROC_LOCAL static
# endif

# if !defined (VSTREAMPROC_LOCAL_INLINE)
#  define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
# endif

# define  VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT8    0x100u
# define  VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT16   0x10000u
# define  VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT32   VSTREAMPROC_MAX_LENGTH

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

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
 *  vStreamProc_ProcessingNode_ByteCompare_GetMinMaxLength()
 **********************************************************************************************************************/
/*! \brief      Get minimum and maximum length of available input data.
 *  \details    Function loops over all input ports and return minimum and maximum value of attached storage nodes.
 *  \param[in]  ConnectedInputPortInfos The input port information structures.
 *  \param[in]  ConnectedInputPortCount The number of input ports.
 *  \param[out] MinLength               The minimum length.
 *  \param[out] MaxLength               The maximum length.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetMinMaxLength(
  vStreamProc_InputPortInfoConstPtrType ConnectedInputPortInfos,
  vStreamProc_InputPortIdType ConnectedInputPortCount,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MinLength,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MaxLength);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_GetConnectedInputPortInfos()
 **********************************************************************************************************************/
/*! \brief      Get a list of only the connected input ports from all input ports.
 *  \details    Function loops over all input ports and returns the ones that are connected.
 *              It further checks whether all use the same, predefined literal data type.
 *  \param[in]  InputPortInfos          The input port information structures.
 *  \param[in]  InputPortCount          The number of input ports.
 *  \param[out] ConnectedInputPortInfos Input port information structures of only the connected ports.
 *  \param[out] ConnectedInputPortCount The number of connected input ports.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \pre        -
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetConnectedInputPortInfos(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_InputPortInfoPtrType ConnectedInputPortInfos,
  P2VAR(vStreamProc_InputPortIdType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ConnectedInputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue()
 *********************************************************************************************************************/
/*!
 * \brief         Get maximum value which can be represented by a single count entry.
 * \details       -
 * \param[in]     DataTypeId      The data type of the count output port.
 * \return        Maximum value of a single count entry   Data type is supported.
 * \return        Zero                                    Data type isn't supported.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_LengthType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue(
  vStreamProc_DataTypeIdType DataTypeId);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_ReportCount()
 *********************************************************************************************************************/
/*!
 * \brief         Write given length into one or more entries of count output.
 * \details       Write is skipped if count output port isn't connected.
 * \param[in]     NodeInfo              The processing node information to operate on.
 * \param[in]     CountPortInfo         The prepared information structure of the count output port.
 * \param[in]     ProcessedLength       The length to be written to the count output.
 * \return        VSTREAMPROC_OK        Operation succeeded.
 * \return        VSTREAMPROC_FAILED    Operation failed.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_ReportCount(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  vStreamProc_OutputPortInfoPtrType CountPortInfo,
  vStreamProc_LengthType ProcessedLength);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_ReportResult()
 *********************************************************************************************************************/
/*!
 * \brief         Report result of byte compare.
 * \details       -
 * \param[in]     NodeInfo                          The processing node information to operate on.
 * \param[in]     Result                            The result to be reported.
 * \return        VSTREAMPROC_OK                    Operation succeeded.
 * \return        VSTREAMPROC_FAILED                Operation failed.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Not enough buffer available to report result.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_ReportResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_Compare()
 *********************************************************************************************************************/
/*!
 * \brief         Compare all other input ports to the reference data.
 * \details       -
 * \param[in]     NodeInfo                   The processing node information to operate on.
 * \param[in]     MinInputLength             The number of bytes to be compared.
 * \param[in]     ConnectedInputPortInfos    The input port information structures.
 * \param[in]     ConnectedInputPortCount    The number of input ports.
 * \return        E_OK              All inputs successfully compared.
 * \return        E_NOT_OK          Mismatch of input contents or input could not be read.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_Compare(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  vStreamProc_LengthType MinInputLength,
  vStreamProc_InputPortInfoPtrType ConnectedInputPortInfos,
  vStreamProc_InputPortIdType ConnectedInputPortCount);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_GetMinMaxLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(void, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetMinMaxLength(
  vStreamProc_InputPortInfoConstPtrType ConnectedInputPortInfos,
  vStreamProc_InputPortIdType ConnectedInputPortCount,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MinLength,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_DATA) MaxLength)
{
  vStreamProc_LengthType      minLength = VSTREAMPROC_MAX_LENGTH;
  vStreamProc_LengthType      maxLength = 0u;
  vStreamProc_InputPortIdType inputInfoIndex;

  /* #10 Loop over all connected input ports and report minimum and maximum value. */
  for (inputInfoIndex = 0u; inputInfoIndex < ConnectedInputPortCount; inputInfoIndex++)
  {
    vStreamProc_LengthType currentLength = ConnectedInputPortInfos[inputInfoIndex].ReadRequest.StorageInfo.AvailableLength;

    if (currentLength < minLength)
    {
      minLength = currentLength;
    }

    if (currentLength > maxLength)
    {
      maxLength = currentLength;
    }
  }

  *MinLength = minLength;
  *MaxLength = maxLength;
}

/**********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_GetConnectedInputPortInfos()
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
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetConnectedInputPortInfos(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_InputPortInfoPtrType ConnectedInputPortInfos,
  P2VAR(vStreamProc_InputPortIdType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ConnectedInputPortCount)
{
  vStreamProc_ReturnType      retVal = VSTREAMPROC_OK;
  vStreamProc_InputPortIdType inputInfoIndex;
  vStreamProc_InputPortIdType connectedInputInfoIndex = 0u;
  /* Port 0 is a required input port, so we can access DataTypeInfo.Id without IsConnected check. */
  vStreamProc_DataTypeIdType  inputDataType = InputPortInfos[0u].ReadRequest.StorageInfo.DataTypeInfo.Id;

  /* #10 Loop over all input ports. */
  for (inputInfoIndex = 0u; inputInfoIndex < InputPortCount; inputInfoIndex++)
  {
    /* #20 If the port is connected. */
    if (InputPortInfos[inputInfoIndex].IsConnected == TRUE)
    {
      /* #30 Copy structure to the list of connected ports. */
      ConnectedInputPortInfos[connectedInputInfoIndex] = InputPortInfos[inputInfoIndex];
      connectedInputInfoIndex++;

      /* #40 Check for data type consistency. */
      if (InputPortInfos[inputInfoIndex].ReadRequest.StorageInfo.DataTypeInfo.Id != inputDataType)
      {
        retVal = VSTREAMPROC_FAILED;
        break;
      }
    }
  }

  /* #50 Check that data type is in list of known literal types. */
  switch (inputDataType)
  {
    case vStreamProcConf_vStreamProcDataType_Std_ReturnType:
    case vStreamProcConf_vStreamProcDataType_uint8:
    case vStreamProcConf_vStreamProcDataType_uint16:
    case vStreamProcConf_vStreamProcDataType_uint32:
      break;
    default:
      retVal = VSTREAMPROC_FAILED;
      break;
  }

  *ConnectedInputPortCount = connectedInputInfoIndex;
  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_LengthType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue(
  vStreamProc_DataTypeIdType DataTypeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_LengthType maxCountValue;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Evaluate maximum value which can be represented by the given data type. */
  switch (DataTypeId)
  {
    case vStreamProcConf_vStreamProcDataType_uint8:
    {
      maxCountValue = VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT8;

      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint16:
    {
      maxCountValue = VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT16;

      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint32:
    {
      maxCountValue = VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_COUNT_MAX_UINT32;

      break;
    }
    default:
    {
      maxCountValue = 0u;

      break;
    }
  }

  return maxCountValue;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_ReportCount
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_ReportCount(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  vStreamProc_OutputPortInfoPtrType CountPortInfo,
  vStreamProc_LengthType ProcessedLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check whether optional count output port is connected. */
  if (CountPortInfo->IsConnected == TRUE)
  {
    if (vStreamProc_RequestPortData(NodeInfo, NULL_PTR, 0u, CountPortInfo, 1u) == VSTREAMPROC_OK)
    {
      vStreamProc_LengthType                numProducedValues = 0u;
      vStreamProc_LengthType                remainingLength   = ProcessedLength;
      P2CONST(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeRequest =
        &CountPortInfo->WriteRequest;
      vStreamProc_LengthType                maxCountValue   =
        vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue(writeRequest->StorageInfo.DataTypeInfo.Id);

      /* #20 Produce as many count values of max. value as required for the compared length. */
      while (remainingLength > 0u)
      {
        vStreamProc_LengthType countValue;

        /* Single produced count value is limited according to data type. */
        if (remainingLength > maxCountValue)
        {
          /* To reach maximum value a 1 must be subtracted. */
          countValue      = maxCountValue - 1u;
          remainingLength -= maxCountValue;
        }
        else
        {
          countValue      = remainingLength - 1u;
          remainingLength = 0u;
        }

        /* Store single count value in buffer typed according to data type. */
        switch (writeRequest->StorageInfo.DataTypeInfo.Id)
        {
          case vStreamProcConf_vStreamProcDataType_uint8:
          {
            P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(writeRequest);

            writeBuffer[numProducedValues] = (uint8)(countValue);

            break;
          }
          case vStreamProcConf_vStreamProcDataType_uint16:
          {
            /* PRQA S 0310,3305 1 */ /* MD_vStreamProc_Rule11.3_0310_3305_CastPtrDiffObj */
            P2VAR(uint16, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint16(writeRequest);

            writeBuffer[numProducedValues] = (uint16)(countValue);

            break;
          }
          case vStreamProcConf_vStreamProcDataType_uint32:
          {
            /* PRQA S 0310,3305 1 */ /* MD_vStreamProc_Rule11.3_0310_3305_CastPtrDiffObj */
            P2VAR(uint32, AUTOMATIC, VSTREAMPROC_APPL_VAR) writeBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint32(writeRequest);

            writeBuffer[numProducedValues] = (uint32)(countValue);

            break;
          }
          default:
          {
            /* Can never be reached. */
            break;
          }
        }

        numProducedValues++;
      }

      if (vStreamProc_AcknowledgeOutputPort(NodeInfo, numProducedValues, TRUE, CountPortInfo) == VSTREAMPROC_OK)
      {
        retVal = VSTREAMPROC_OK;
      }
    }
  }
  else
  {
    retVal = VSTREAMPROC_OK;
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_ReportResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_ReportResult(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  Std_ReturnType Result)
{
  vStreamProc_ReturnType         retVal;
  vStreamProc_OutputPortInfoType resultPortInfo;

  retVal = vStreamProc_PrepareOutputPortInfo(NodeInfo, vStreamProcConf_Internal_ByteCompareNode_ResultData, &resultPortInfo);

  /* #10 Report result of byte compare. */
  if (retVal == VSTREAMPROC_OK)
  {
    /* Report "insufficient data" when no data is available by requesting a single entry. */
    retVal = vStreamProc_RequestOutputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_Std_ReturnType, 1u, &resultPortInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    P2VAR(Std_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR) resultBuffer =
      vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&resultPortInfo.WriteRequest);

    resultBuffer[0u] = Result;

    retVal = vStreamProc_AcknowledgeOutputPort(NodeInfo, 1u, TRUE, &resultPortInfo);
  }

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_Compare
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_Compare(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo,
  vStreamProc_LengthType MinInputLength,
  vStreamProc_InputPortInfoPtrType ConnectedInputPortInfos,
  vStreamProc_InputPortIdType ConnectedInputPortCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if (vStreamProc_RequestPortData(NodeInfo, ConnectedInputPortInfos, ConnectedInputPortCount, NULL_PTR, 0u) == VSTREAMPROC_OK)
  {
    vStreamProc_InputPortIdType inputInfoIndex;
    P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) referenceBuffer;
    vStreamProc_LengthType dataTypeSize;

    /* #10 Data of first connected input port is the reference data. */
    referenceBuffer = ConnectedInputPortInfos[0u].ReadRequest.Buffer;
    dataTypeSize = ConnectedInputPortInfos[0u].ReadRequest.StorageInfo.DataTypeInfo.Size;

    retVal = E_OK;

    ConnectedInputPortInfos[0u].ReadRequest.StorageInfo.RequestLength = MinInputLength;

    /* #20 Compare all other connected input ports to the reference data. */
    for (inputInfoIndex = 1u; inputInfoIndex < ConnectedInputPortCount; inputInfoIndex++)
    {
      vStreamProc_StorageNodeBufferIterType           currentBufferOffset;
      vStreamProc_LengthType                          compareLength = MinInputLength * dataTypeSize;
      P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) buffer = ConnectedInputPortInfos[inputInfoIndex].ReadRequest.Buffer;

      for (currentBufferOffset = 0u; currentBufferOffset < compareLength; currentBufferOffset++)
      {
        /* Compare the data bytes */
        if (referenceBuffer[currentBufferOffset] != buffer[currentBufferOffset])
        {
          /* Break any operation when mismatch was detected */
          retVal = E_NOT_OK;

          break;
        }
      }

      ConnectedInputPortInfos[inputInfoIndex].ReadRequest.StorageInfo.RequestLength = MinInputLength;

      /* #30 Leave the loop if an error occurred. */
      if (retVal != E_OK)
      {
        break;
      }
    }

    if (retVal == E_OK)
    {
      if (vStreamProc_AcknowledgePorts(NodeInfo, ConnectedInputPortInfos, ConnectedInputPortCount, NULL_PTR, 0u) != VSTREAMPROC_OK)
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      (void)vStreamProc_ReleaseAllPorts(NodeInfo);
    }
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_Init(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Fetch and initialize the workspace. */
  /* PRQA S 0316 2 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  P2VAR(vStreamProc_ByteCompare_ResultType, AUTOMATIC, VSTREAMPROC_APPL_VAR) byteCompareResult
    = vStreamProc_GetTypedWorkspaceOfProcessingNode_ByteCompare_ResultType(NodeInfo);

  *byteCompareResult = E_OK;

  return E_OK;
}

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_Process
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
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_Process(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType            retVal = VSTREAMPROC_FAILED;

  vStreamProc_InputPortInfoType     inputPortInfos[vStreamProcConf_InputPortCount_Internal_ByteCompareNode];
  vStreamProc_OutputPortInfoType    outputPortInfos[vStreamProcConf_OutputPortCount_Internal_ByteCompareNode];
  vStreamProc_OutputPortInfoPtrType countPortInfo   = &outputPortInfos[vStreamProcConf_Internal_ByteCompareNode_ComparedCount];

  vStreamProc_InputPortIdType       inputPortCount  = NodeInfo->InputPortCount;
  vStreamProc_OutputPortIdType      outputPortCount = NodeInfo->OutputPortCount;

  vStreamProc_InputPortInfoType     connectedInputPortInfos[vStreamProcConf_InputPortCount_Internal_ByteCompareNode];
  vStreamProc_InputPortIdType       connectedInputPortCount = 0u;

  /* PRQA S 0316 4 */ /* MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj */
  P2CONST(vStreamProc_ProcessingNode_ByteCompare_ConfigType, AUTOMATIC, VSTREAMPROC_APPL_CONST) specializedCfgPtr
    = vStreamProc_GetTypedConfigOfProcessingNode_ByteCompare_Config(NodeInfo);

  vStreamProc_LengthType            minInputLength  = VSTREAMPROC_MAX_LENGTH;
  vStreamProc_LengthType            maxInputLength  = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Evaluate minimum and maximum available length at all input ports:
   *  + No data is available at all: Processing is idle.
   *  + Only some ports have no data: Report insufficient input.
   *  + Data available for all ports: Compare minimum length.
   */
  if (vStreamProc_PrepareAllPortInfos(NodeInfo, inputPortInfos, inputPortCount, outputPortInfos, outputPortCount) == VSTREAMPROC_OK)
  {
    if (vStreamProc_GetPortInfos(NodeInfo, inputPortInfos, inputPortCount, countPortInfo, 1u) == VSTREAMPROC_OK)
    {
      if (vStreamProc_ProcessingNode_ByteCompare_GetConnectedInputPortInfos(inputPortInfos, inputPortCount, connectedInputPortInfos, &connectedInputPortCount) == VSTREAMPROC_OK)
      {
        vStreamProc_ProcessingNode_ByteCompare_GetMinMaxLength(connectedInputPortInfos, connectedInputPortCount, &minInputLength, &maxInputLength);

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
          for (inputInfoIndex = 0u; inputInfoIndex < connectedInputPortCount; inputInfoIndex++)
          {
            vStreamProc_InputPortInfoConstPtrType inputPortInfo = &connectedInputPortInfos[inputInfoIndex];

            if (inputPortInfo->ReadRequest.StorageInfo.AvailableLength == 0u)
            {
              NodeInfo->InputPortResults[inputPortInfo->SymbolicPortName] = VSTREAMPROC_INSUFFICIENT_INPUT;
            }
          }
        }
        else
        {
          retVal = VSTREAMPROC_PENDING;
        }
      }
    }
  }

  /* #20 Check optional output for compare count:
   *  + Connected and no buffer available: Report insufficient output.
   *  + Connected and buffer available: Limit comparison length to maximum countable value.
   */
  if (retVal == VSTREAMPROC_PENDING)
  {
    vStreamProc_StorageInfoConstPtrType countStorageInfo = &countPortInfo->WriteRequest.StorageInfo;

    if (countPortInfo->IsConnected == TRUE)
    {
      if (countStorageInfo->AvailableLength == 0u)
      {
        retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
        NodeInfo->OutputPortResults[vStreamProcConf_Internal_ByteCompareNode_ComparedCount] = VSTREAMPROC_INSUFFICIENT_OUTPUT;
      }
      else
      {
        vStreamProc_LengthType maxCountValue
          = vStreamProc_ProcessingNode_ByteCompare_GetMaxCountValue(countStorageInfo->DataTypeInfo.Id);

        if (maxCountValue > 0u)
        {
          vStreamProc_LengthType maxCountLength;

          if ((VSTREAMPROC_MAX_LENGTH / maxCountValue) > countStorageInfo->AvailableLength)
          {
            /* Initialize variable with maximum value supported by count output buffer */
            maxCountLength = maxCountValue * countStorageInfo->AvailableLength;
          }
          else
          {
            maxCountLength = VSTREAMPROC_MAX_LENGTH;
          }

          /* Restrict to maximum compare length */
          if (maxCountLength < minInputLength)
          {
            minInputLength = maxCountLength;
          }
        }
        else
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }

  /* #30 Compare available data at all input ports. */
  if (retVal == VSTREAMPROC_PENDING)
  {
    /* Restrict to maximum configured compare length. */
    if (specializedCfgPtr->BytesToCompareOfProcessingNode_ByteCompare_Config < minInputLength)
    {
      minInputLength = specializedCfgPtr->BytesToCompareOfProcessingNode_ByteCompare_Config;
    }

    if (vStreamProc_ProcessingNode_ByteCompare_Compare(NodeInfo, minInputLength, connectedInputPortInfos, connectedInputPortCount) == E_OK)
    {
      retVal = vStreamProc_ProcessingNode_ByteCompare_ReportCount(NodeInfo, countPortInfo, minInputLength);

      /* Only return idle result if all input data could be consumed. */
      if ( (retVal == VSTREAMPROC_OK)
        && (maxInputLength > minInputLength) )
      {
        retVal = VSTREAMPROC_PENDING;
      }
    }
    else
    {
      /* #40 Report negative result if comparison failed. */
      (void)vStreamProc_ProcessingNode_ByteCompare_ReportResult(NodeInfo, E_NOT_OK);
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
} /* PRQA S 6080, 6050, 6010, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCAL, MD_MSR_STPTH, MD_MSR_STCYC */

/***********************************************************************************************************************
 *  vStreamProc_ProcessingNode_ByteCompare_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ProcessingNode_ByteCompare_Flush(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process any remaining inputs. */
  retVal = vStreamProc_ProcessingNode_ByteCompare_Process(NodeInfo);

  /* #20 Report result if all inputs were consumed. */
  if (retVal == VSTREAMPROC_OK)
  {
    /* Note: Negative result set in process function. */
    retVal = vStreamProc_ProcessingNode_ByteCompare_ReportResult(NodeInfo, E_OK);
  }

  return retVal;
}

# define VSTREAMPROC_STOP_SEC_CODE
# include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (VSTREAMPROC_PROCESSINGNODE_BYTECOMPARE_CONFIG == STD_ON) */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:
 */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_ProcessingNode_ByteCompare.c
 *********************************************************************************************************************/
