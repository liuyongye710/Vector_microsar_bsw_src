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
/*!        \file  vSwUpdM_ResumeProcNodes.c
 *        \brief  vSwUpdM processing nodes implementation source file
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

#define VSWUPDM_RESUMEPROCNODES_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_ResumeProcNodes.h"
#include "vSwUpdM_ResumeProcNodeTypes.h"
#include "SchM_vSwUpdM.h"
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Range.h"
#include "vSwUpdM_Appl.h"

#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

 /*!
 * Internal comment removed.
 *
 *
 */
#if defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ReadEncryptionIv) && defined(vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType)
# define VSWUPDM_RESUMEPROC_NODES_READ_ENCRYPTION_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_READ_ENCRYPTION_NODE STD_OFF
#endif

#if defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ReadDecryptionIv) && defined(vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType)
# define VSWUPDM_RESUMEPROC_NODES_READ_DECRYPTION_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_READ_DECRYPTION_NODE STD_OFF
#endif

#if ( defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ReadEncryptionIv) || defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ReadDecryptionIv) ) && defined(vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType)
# define VSWUPDM_RESUMEPROC_NODES_READ_CIPHER_IV_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_READ_CIPHER_IV_NODE STD_OFF
#endif

#if defined(vStreamProcConf_InputPortCount_External_vSwUpdM_EvalDecryptionIv) && defined(vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeEvalDecryptionIvWorkspaceType)
# define VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE STD_OFF
#endif

#if defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePassthrough)
# define VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE STD_OFF
#endif

#if defined(vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding)
# define VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE STD_OFF
#endif

#if ( (VSWUPDM_RESUMEPROC_NODES_READ_CIPHER_IV_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE == STD_ON))
# define VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING STD_ON
#else
# define VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING STD_OFF
#endif


/* ResumePadding Node */
#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE == STD_ON)

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding] =
{
  {vStreamProcConf_External_vSwUpdM_ResumePadding_DataInputPort,      vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_ResumePadding_EntitiesInputPort,  vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType},
  {vStreamProcConf_External_vSwUpdM_ResumePadding_OperationInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType},
  {vStreamProcConf_External_vSwUpdM_ResumePadding_RangeInputPort,     vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType},
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_OutputPortDatatype[vStreamProcConf_OutputPortCount_External_vSwUpdM_ResumePadding] =
{
  {vStreamProcConf_External_vSwUpdM_ResumePadding_AlignedRangeOutputPort,    vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType },
  {vStreamProcConf_External_vSwUpdM_ResumePadding_DataOutputPort,            vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_ResumePadding_OperationOutputPort,       vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType},
  {vStreamProcConf_External_vSwUpdM_ResumePadding_ResultingRangesOutputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType }
};
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_ResumeProcNode_ConsumeInput()
 *********************************************************************************************************************/
/*! \brief      Consumes all data from input port
 *  \details    The data is consumed but not written anywhere. This function discards the number of requested entries
 *              From the given input.
 *  \param[in]  NodeInfo                        Specifies the node.
 *  \param[in]  InputPortSymbolicName           Specifies the nodes port from where to consume.
 *  \param[in]  DataTypeId                      Expected DataTypeId of input.
 *  \param[in]  MinLength                       Minimal required length (can be zero to suppress INSUFFICIENT_INPUT)
 *  \param[in]  MaxLength                       Maximal length to consume (can be VSTREAMPROC_MAX_LENGTH to consume "all").
 *  \param[out] LengthOut                       Number of consumed entries.
 *  \return     VSTREAMPROC_OK                  Operation was successful.
 *  \return     VSTREAMPROC_INSUFFICIENT_INPUT  Requested minimum buffer length isn't available.
 *  \return     VSTREAMPROC_FAILED              Operation was unsuccessful.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \synchronousTRUE
 *  \pre           -
*********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeProcNode_ConsumeInput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType InputPortSymbolicName,
  vStreamProc_DataTypeIdType DataTypeId,
  vSwUpdM_LengthType MinLength,
  vSwUpdM_LengthType MaxLength,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_DATA) LengthOut);
#endif

#if  (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON)
 /**********************************************************************************************************************
 *  vSwUpdM_ResumeProcNode_Passthrough()
 *********************************************************************************************************************/
/*! \brief      Copies all data from input to output port.
 *  \details    -
 *  \param[in]  NodeInfo                        Specifies the node.
 *  \param[in]  InputPortSymbolicName           Specifies the nodes port from where to read.
 *  \param[in]  OutputPortSymbolicName          Specifies the nodes port where to write.
 *  \return     VSTREAMPROC_OK                  Operation was successful.
 *  \return     VSTREAMPROC_PENDING             There is still unconsumed data available.
 *  \return     VSTREAMPROC_INSUFFICIENT_OUTPUT Requested output buffer length isn't available.
 *  \return     VSTREAMPROC_FAILED              Operation was unsuccessful.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \synchronousTRUE
 *  \pre           -
*********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeProcNode_Passthrough(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType InputPortSymbolicName,
  vStreamProc_OutputPortSymbolicNameType OutputPortSymbolicName);
#endif

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadProcessOperation()
 *********************************************************************************************************************/
/*! \brief      Reads processOperation from an output port of a node.
 *  \details    -
 *  \param[in]  NodeInfo                        Specifies the node from where to read.
 *  \param[in]  OperationInputPort              Specifies the nodes port from where to read.
 *  \param[out] ProcessOperation                Read processOperation.
 *  \return     VSTREAMPROC_OK                  Operation was successful.
 *  \return     VSTREAMPROC_INSUFFICIENT_INPUT  Requested minimum buffer length isn't available.
 *  \return     VSTREAMPROC_FAILED              Operation was unsuccessful.
 *  \context    TASK
 *  \reentrant  TRUE
 *  \synchronousTRUE
 *  \pre           -
*********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadProcessOperation(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType OperationInputPort,
  vSwUpdM_ProcNodeOperationPtrType ProcessOperation);
#endif

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWriteProcessOperation()
 *********************************************************************************************************************/
/*! \brief       Writes the processOperation to an output of a node.
 *  \details     -
 *  \param[in]   NodeInfo                        Specifies the node where to write.
 *  \param[in]   OperationOutputPort             Specifies the nodes port from where to write.
 *  \param[in]   ProcessOperation                Value to write.
 *  \return      VSTREAMPROC_OK                  Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED              Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWriteProcessOperation(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPort,
  vSwUpdM_ProcNodeOperationType ProcessOperation);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeShutdownOperationDefaultHandler()
 *********************************************************************************************************************/
/*! \brief         Handles process operation in-/output.
 *  \details       Helper function to reduce complexity in individual nodes. Checks the process operation input for
 *                 shutdown request.
 *                 If received, outputs a response and sets node state to SHUTDOWN
 *  \param[in]     NodeInfo                         Specifies the node where to read process operation.
 *  \param[in]     OperationInputPortSymbolicName   Specifies the port where to read process operation.
 *  \param[in]     OperationOutputPortSymbolicName  Specifies the port where to write process operation.
 *  \param[in,out] State                            Pointer to current nodes state.
 *  \return        ProcNodeOperation read from input port.
 *                 If no data available, VSWUPDM_PROC_NODE_OPERATION_NONE is returned.
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vSwUpdM_ProcNodeOperationType, VSWUPDM_CODE) vSwUpdM_ProcNodeShutdownOperationDefaultHandler(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType  OperationInputPortSymbolicName,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPortSymbolicName,
  P2VAR(vSwUpdM_ResumeProcNodeStateType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_DATA) State);

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRestartOperationDefaultHandler()
 *********************************************************************************************************************/
/*! \brief       Handles processing of start/restart operation.
 *  \details     Helper function to reduce complexity in individual nodes. Evaluates the process operation for
 *               start/restart request.
 *               If received, outputs a response and sets node state to SHUTDOWN
 *  \param[in]   NodeInfo            Specifies the node where to write process operation.
 *  \param[in]   OperationOutputPort Symbolic name value of operation output port.
 *  \param[in]   Operation           Value of process operation.
 *  \param[out]  State               Pointer to current nodes state.
 *  \param[out]  RestartPending      TRUE: A restart is requested.
 *  \return      TRUE                Start/restart operation received.
 *  \return      FALSE               Start/restart operation not received yet.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ProcNodeRestartOperationDefaultHandler(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPort,
  vSwUpdM_ProcNodeOperationType Operation,
  vSwUpdM_ResumeProcNodeStatePtrType State,
  P2VAR(boolean, AUTOMATIC, VSWUPDM_APPL_VAR) RestartPending);
#endif /* VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ResumeProcNode_ConsumeInput
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeProcNode_ConsumeInput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType InputPortSymbolicName,
  vStreamProc_DataTypeIdType DataTypeId,
  vSwUpdM_LengthType MinLength,
  vSwUpdM_LengthType MaxLength,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_DATA) LengthOut)
{
  vStreamProc_ReturnType        retVal;

 /* #10 Prepare input. */
  vStreamProc_InputPortInfoType inputPortInfo;
  vStreamProc_LengthType        length = 0u;

  retVal = vStreamProc_PrepareInputPortInfo(NodeInfo, InputPortSymbolicName, &inputPortInfo);

  /* #20 Request data. */
  if (retVal == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_RequestInputPortData(NodeInfo, DataTypeId, MinLength, &inputPortInfo);
  }
  /* #30 If data available:
   *     Consume it. */
  if (retVal == VSTREAMPROC_OK)
  {
    if (inputPortInfo.ReadRequest.StorageInfo.AvailableLength > 0u)
    {
      if (inputPortInfo.ReadRequest.StorageInfo.AvailableLength < MaxLength)
      {
        length = inputPortInfo.ReadRequest.StorageInfo.AvailableLength;
      }
      else
      {
        length = MaxLength;
      }

      retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, length, TRUE, &inputPortInfo);
    }
  }

  if (LengthOut != NULL_PTR)
  {
    (*LengthOut = length);
  }

  return retVal;

  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_ResumeProcNode_ConsumeInput */
#endif /* (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_ON) || (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON) */


#if  (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ResumeProcNode_Passthrough
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeProcNode_Passthrough(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType InputPortSymbolicName,
  vStreamProc_OutputPortSymbolicNameType OutputPortSymbolicName)
{
  vStreamProc_ReturnType        retVal;

  /* Requests for data input, output. */
  vStreamProc_InputPortInfoType  dataInputPortInfo;
  vStreamProc_OutputPortInfoType dataOutputPortInfo;

  /* Set symbolic names to Requests */
  dataInputPortInfo.SymbolicPortName = InputPortSymbolicName;
  dataOutputPortInfo.SymbolicPortName = OutputPortSymbolicName;

  /* #10 Prepare requests. */
  retVal = vStreamProc_PreparePortInfos(NodeInfo, &dataInputPortInfo, 1u, &dataOutputPortInfo, 1u);

  if (retVal == VSTREAMPROC_OK)
  {
    dataInputPortInfo.ReadRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_uint8;
    dataOutputPortInfo.WriteRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_uint8;

    retVal = vStreamProc_GetPortInfos(NodeInfo, &dataInputPortInfo, 1u, &dataOutputPortInfo, 1u);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Evaluate if any input data is available: */
    if (vSwUpdM_ProcNode_IsInputDataAvailable(&dataInputPortInfo, 1u) == FALSE)
    {
      /* No input data available: Node is idle. */
    }
    else
    {
      /* #30 Request minimal required amount of data. */
      dataInputPortInfo.ReadRequest.StorageInfo.RequestLength = 1u;
      dataOutputPortInfo.WriteRequest.StorageInfo.RequestLength = 1u;

      retVal = vStreamProc_RequestPortData(NodeInfo, &dataInputPortInfo, 1u, &dataOutputPortInfo, 1u);

      if (retVal == VSTREAMPROC_OK)
      {
        /* Get typed buffers */
        vSwUpdM_DataReadStreamPtrType  data = vStreamProc_GetTypedReadRequestBuffer_uint8(&dataInputPortInfo.ReadRequest);
        vSwUpdM_DataStreamPtrType dataOut = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataOutputPortInfo.WriteRequest);

        vSwUpdM_LengthType length = vSwUpdM_GetDefaultProcessingSegmentation();
        length = VSWUPDM_PROCNODES_MIN(length, dataInputPortInfo.ReadRequest.StorageInfo.AvailableLength);
        length = VSWUPDM_PROCNODES_MIN(length, dataOutputPortInfo.WriteRequest.StorageInfo.AvailableLength);

        if (length < dataInputPortInfo.ReadRequest.StorageInfo.AvailableLength)
        {
          retVal = VSTREAMPROC_PENDING;
        }

        /* #40 Copy data. */
        vSwUpdM_Buffer_Copy(data, dataOut, length);

        /* #50 Acknowledge buffers. */
        dataInputPortInfo.ReadRequest.StorageInfo.RequestLength = length;
        dataOutputPortInfo.WriteRequest.StorageInfo.RequestLength = length;

        if (vStreamProc_AcknowledgePorts(NodeInfo, &dataInputPortInfo, 1u, &dataOutputPortInfo, 1u) != VSTREAMPROC_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_ResumeProcNode_ConsumeInput */
#endif /* (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_ON) */

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ProcNodeReadProcessOperation
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadProcessOperation(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType OperationInputPort,
  vSwUpdM_ProcNodeOperationPtrType ProcessOperation)
{
  vStreamProc_ReturnType        retVal;
  vStreamProc_InputPortInfoType  operationInputPort;

  /* Prepare requests. */
  retVal = vStreamProc_PrepareInputPortInfo(NodeInfo, OperationInputPort, &operationInputPort);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #10 Check expected datatypes. */
    retVal = vStreamProc_GetInputPortInfo(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType, &operationInputPort);

    if (retVal == VSTREAMPROC_OK)
    {
      /* #20 Evaluate if any input data is available: */
      if ((operationInputPort.IsConnected == TRUE) && (operationInputPort.ReadRequest.StorageInfo.AvailableLength > 0u))
      {
        /* #30 Request Buffer. */
        retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType, 1u, &operationInputPort);

        if (retVal == VSTREAMPROC_OK)
        {
          /* #40 Read input port. */
          vSwUpdM_ProcNodeOperationReadPtrType buffer = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_ProcNodeOperationType(&operationInputPort.ReadRequest);

          (*ProcessOperation) = (*buffer);

          /* #50 Acknowledge input port. */
          retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, 1u, TRUE, &operationInputPort);
        }
      }
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodeReadProcessOperation */
#endif

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ProcNodeWriteProcessOperation
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWriteProcessOperation(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPort,
  vSwUpdM_ProcNodeOperationType ProcessOperation)
{
  vStreamProc_ReturnType        retVal;
  vStreamProc_OutputPortInfoType  operationOutputPort;

  /* #10 Prepare requests. */
  retVal = vStreamProc_PrepareOutputPortInfo(NodeInfo, OperationOutputPort, &operationOutputPort);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Check expected datatypes. */
    retVal = vStreamProc_GetOutputPortInfo(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType, &operationOutputPort);

    if (retVal == VSTREAMPROC_OK)
    {
      /* #30 Evaluate if output is connected and has some space available: */
      if ((operationOutputPort.IsConnected == TRUE) && (operationOutputPort.WriteRequest.StorageInfo.AvailableLength > 0u))
      {
        /* #40 Request Buffer. */
        retVal = vStreamProc_RequestOutputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_ProcNodeOperationType, 1u, &operationOutputPort);
        {
          if (retVal == VSTREAMPROC_OK)
          {
            /* #50 Write buffer. */
            vSwUpdM_ProcNodeOperationPtrType buffer = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_ProcNodeOperationType(&operationOutputPort.WriteRequest);

            (*buffer) = ProcessOperation;

            /* #60 Acknowledge buffer. */
            retVal = vStreamProc_AcknowledgeOutputPort(NodeInfo, 1u, TRUE, &operationOutputPort);
          }
        }
      }
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodeWriteProcessOperation */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeShutdownOperationDefaultHandler
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vSwUpdM_ProcNodeOperationType, VSWUPDM_CODE) vSwUpdM_ProcNodeShutdownOperationDefaultHandler(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_InputPortSymbolicNameType  OperationInputPortSymbolicName,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPortSymbolicName,
  P2VAR(vSwUpdM_ResumeProcNodeStateType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_DATA) State)
{
  vSwUpdM_ProcNodeOperationType operation = VSWUPDM_PROC_NODE_OPERATION_NONE;
  vSwUpdM_ResumeProcNodeStateType     state     = *State;

  /* #10 Read processOperation. */
  if (vSwUpdM_ProcNodeReadProcessOperation(NodeInfo, OperationInputPortSymbolicName, &operation) == VSTREAMPROC_OK)
  {
    if (operation == VSWUPDM_PROC_NODE_OPERATION_SHUTDOWN)
    {
      /* #11 Output response for shutdown. */
      if (vSwUpdM_ProcNodeWriteProcessOperation(NodeInfo, OperationOutputPortSymbolicName, VSWUPDM_PROC_NODE_OPERATION_SHUTDOWN) == VSTREAMPROC_OK)
      {
        /* #12 Set state to shutdown. */
        state = VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN;
      }
      else
      {
        state = VSWUPDM_RESUME_PROC_NODE_STATE_FAILED;
      }
    }
  }
  else
  {
    /* #20 On error:
     *   Set state to failed. */
    state = VSWUPDM_RESUME_PROC_NODE_STATE_FAILED;
  }

  *State = state;

  return operation;
} /* vSwUpdM_ProcNodeShutdownOperationDefaultHandler */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRestartOperationDefaultHandler
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ProcNodeRestartOperationDefaultHandler(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType OperationOutputPort,
  vSwUpdM_ProcNodeOperationType Operation,
  vSwUpdM_ResumeProcNodeStatePtrType State,
  P2VAR(boolean, AUTOMATIC, VSWUPDM_APPL_VAR) RestartPending)
{
  boolean                   retVal          = FALSE;
  vSwUpdM_ResumeProcNodeStateType state           = VSWUPDM_RESUME_PROC_NODE_STATE_FAILED;
  boolean                   restartPending  = FALSE;

  /* #100 Evaluate Operation: */
  switch (Operation)
  {
    case VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART:
    case VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART:
    /* #110 If restart requested:
     *   Output response and set flag for restart. */
    {
      if (vSwUpdM_ProcNodeWriteProcessOperation(NodeInfo, OperationOutputPort, VSWUPDM_PROC_NODE_OPERATION_START) == VSTREAMPROC_OK)
      {
        state           = VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION;
        restartPending  = TRUE;

        retVal = TRUE;
      }

      break;
    }
    case VSWUPDM_PROC_NODE_OPERATION_START:
    /* #120 If start requested:
     *   Output response and set flag for start. */
    {
      if (vSwUpdM_ProcNodeWriteProcessOperation(NodeInfo, OperationOutputPort, VSWUPDM_PROC_NODE_OPERATION_START) == VSTREAMPROC_OK)
      {
        state = VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION;

        retVal = TRUE;
      }

      break;
    }
    default:
    /* Otherwise: Do nothing */
    {
      state = *State;

      break;
    }
  }

  *State          = state;
  *RestartPending = restartPending;

  return retVal;
}/* vSwUpdM_ProcNodeRestartOperationDefaultHandler */
#endif /* VSWUPDM_RESUMEPROC_NODES_RESUME_HANDLING == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * PROCESSING NODE: READ CIPHER IV
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadEncryptionIv_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadEncryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  Std_ReturnType retVal;
#if (VSWUPDM_RESUMEPROC_NODES_READ_ENCRYPTION_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = E_NOT_OK;
#else
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadCipherIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Initialize state and reset flags in workspace. */
  workspace->CipherMode               = VSWUPMD_PROC_NODE_CIPHER_MODE_ENCRYPT;
  workspace->State                    = VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL;
  workspace->RestartPending           = FALSE;

  /* #30 Initialize input/output port references in workspace. */
  workspace->EntitiesInputPort        = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_EntitiesInputPort;
  workspace->OperationInputPort       = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_OperationInputPort;
  workspace->RangeInputPort           = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_RangeInputPort;

  workspace->OperationOutputPort      = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_OperationOutputPort;
  workspace->ResumeRangeOutputPort    = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_ResumeRangeOutputPort;
  workspace->RemainderRangeOutputPort = vStreamProcConf_External_vSwUpdM_ReadEncryptionIv_RemainderRangeOutputPort;

  retVal = E_OK;
#endif

  return retVal;
} /* vSwUpdM_ProcNodeReadEncryptionIv_Init */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadDecryptionIv_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadDecryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  Std_ReturnType retVal;

#if (VSWUPDM_RESUMEPROC_NODES_READ_DECRYPTION_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = E_NOT_OK;
#else
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadCipherIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize state and reset flags in workspace. */
  workspace->CipherMode               = VSWUPMD_PROC_NODE_CIPHER_MODE_DECRYPT;
  workspace->State                    = VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL;
  workspace->RestartPending           = FALSE;

  /* #30 Initialize input/output port references in workspace. */
  workspace->EntitiesInputPort        = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_EntitiesInputPort;
  workspace->OperationInputPort       = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_OperationInputPort;
  workspace->RangeInputPort           = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_RangeInputPort;

  workspace->OperationOutputPort      = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_OperationOutputPort;
  workspace->ResumeRangeOutputPort    = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_ResumeRangeOutputPort;
  workspace->RemainderRangeOutputPort = vStreamProcConf_External_vSwUpdM_ReadDecryptionIv_RemainderRangeOutputPort;

  retVal = E_OK;
  #endif

  return retVal;
} /* vSwUpdM_ProcNodeReadDecryptionIv_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadCipherIv_Process
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadCipherIv_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_PENDING;  /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

# if (VSWUPDM_RESUMEPROC_NODES_READ_CIPHER_IV_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = VSTREAMPROC_FAILED;
#else
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadCipherIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType(NodeInfo);

  /* Request inputs. */
  vStreamProc_InputPortInfoType     inputPortInfos[2u];
  /* Named pointers to list above. */
  vStreamProc_InputPortInfoPtrType  entitiesInputPort  = &inputPortInfos[0u];
  vStreamProc_InputPortInfoPtrType  rangeInputPort     = &inputPortInfos[1u];

  /* Request output. */
  vStreamProc_OutputPortInfoType    outputPortInfos[2u];
  vStreamProc_OutputPortInfoPtrType remainderRangeOutputPort = &outputPortInfos[0u];
  vStreamProc_OutputPortInfoPtrType resumeRangeOutputPort  = &outputPortInfos[1u];

  vSwUpdM_ProcNodeOperationType   operation;

  /* Set symbolic names to requests. */
  entitiesInputPort->SymbolicPortName        = workspace->EntitiesInputPort;
  rangeInputPort->SymbolicPortName           = workspace->RangeInputPort;

  remainderRangeOutputPort->SymbolicPortName = workspace->RemainderRangeOutputPort;
  resumeRangeOutputPort->SymbolicPortName    = workspace->ResumeRangeOutputPort;


  /* ----- Implementation ----------------------------------------------- */

  /* #100 Read processOperation. */
  operation = vSwUpdM_ProcNodeShutdownOperationDefaultHandler(NodeInfo, workspace->OperationInputPort, workspace->OperationOutputPort, &workspace->State);

  /* #200 Evaluate state. */
  switch (workspace->State)
  {
    case VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL:
    /* #400 On INITIAL state: */
    {
      /* #410 Handle start/restart request. */
      (void)vSwUpdM_ProcNodeRestartOperationDefaultHandler(NodeInfo, workspace->OperationOutputPort, operation, &workspace->State, &workspace->RestartPending);

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION:
    /* #500 On WAIT FOR PROCESS OPERATION state: */
    {
      /* #510 If PROCESS signal received:
 *        Go to next state. */
      if (operation == VSWUPDM_PROC_NODE_OPERATION_PROCESS)
      {
        workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS;
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS:
    /* #600 On WAIT FOR INPUT state: */
    {
      vSwUpdM_SegmentInfoType       segmentInfo = { 0 };
      vSwUpdM_LengthType            readLength  = 0u;
      vSwUpdM_LengthType            tail        = 0u; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
      vSwUpdM_LengthType            offset      = 0u;

      /* Prepare requests. */
      retVal = vStreamProc_PreparePortInfos(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), NULL_PTR, 0u);

      if (retVal == VSTREAMPROC_OK)
      {
        entitiesInputPort->ReadRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType;
        rangeInputPort->ReadRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType;

        retVal = vStreamProc_GetPortInfos(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), NULL_PTR, 0u);
      }

      if (retVal == VSTREAMPROC_OK)
      {
        /* Evaluate if any input data is available: */
        if (vSwUpdM_ProcNode_IsInputDataAvailable(inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos)) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
          rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

          /* Request Buffer */
          retVal = vStreamProc_RequestPortData(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), NULL_PTR, 0u);

          if (retVal == VSTREAMPROC_OK)
          {

            /* Get typed buffers. */
            /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);
            vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
            vSwUpdM_LengthType  writtenLength;
            uint32              blockCount;
            boolean             readAck = TRUE;

            /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            (void)vSwUpdM_GetSegmentInfo(&segmentInfo, entities->SegmentId);

            writtenLength = segmentInfo.WriteAddress - segmentInfo.StartAddress;
            blockCount = writtenLength / VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE;
            tail = writtenLength - (blockCount * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE);

            if (writtenLength >= VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE)
            {
              readLength = VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE;
              offset = readLength;
            }

            if (writtenLength >= (2u * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE))
            {
              offset = (2u * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE) - tail;
            }

            if ((workspace->RestartPending == TRUE)
              && (readLength > 0u))
            {

              Std_ReturnType      spawnResult;
              vSwUpdM_JobPtrType  spawnedJob;

              /* #631 Enter critical section to ensure exclusive access of state and job queue. */
              VSWUPDM_ENTER_CRITICAL_SECTION();

              /* #632 Spawn job to read data. */
              spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_READ_DATA, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, NULL_PTR, vSwUpdM_GetLocalNode());

              switch (spawnResult)
              {
                case E_OK:
                /* #633 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
                {
                  /* #634 Initialize virtual buffer to keep track of progress of read operation. */
                  /* #636 Pass length to be read as used space of the virtual input buffer of the read job. */
                  (void)vSwUpdM_Buffer_InitAndAddData(spawnedJob->InputBuffer, NULL_PTR, readLength);
                  /* #635 Initialize buffer information for output data, pointing to output buffer. */
                  (void)vSwUpdM_Buffer_Init(spawnedJob->OutputBuffer, workspace->InitVector, readLength);

                  /* #637 Pass open entity IDs to job.
                    *   Read data starting at calculated address. */
                  spawnedJob->EntityIds = *entities;
                  spawnedJob->TargetAddress = segmentInfo.WriteAddress - (VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE + tail);

                  /* #638 Set linked result of job to result in workspace. */
                  vSwUpdM_Job_ResetLinkedResult(&workspace->JobResult);
                  vSwUpdM_Job_LinkResult(spawnedJob, &workspace->JobResult);

                  /* #639 Advance state to wait for result of memory operation. */
                  workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_PENDING;
                  retVal = VSTREAMPROC_PENDING;

                  break;
                }
                case VSWUPDM_E_BUSY:
                /* #640 If job couldn't be spawned, because it is busy
                  *   Retry on next cycle. */
                {
                  readAck = FALSE;

                  break;
                }
                default:
                /* #650 Otherwise: Report back error. */
                {
                  retVal = VSTREAMPROC_FAILED;
                  break;
                }
              }

              /* #660 Leave critical section ensuring exclusive access of state and job queue. */
              VSWUPDM_LEAVE_CRITICAL_SECTION();
            }
            else
            {
              /* #670 Otherwise:
               *   Reset initialization vector and go to state FINISHED. */
              workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
              retVal = VSTREAMPROC_PENDING;

              if (workspace->CipherMode == VSWUPMD_PROC_NODE_CIPHER_MODE_ENCRYPT)
              {
                if (vSwUpdM_Appl_ResetEncryptionInitVector() != E_OK)
                {
                  retVal = VSTREAMPROC_FAILED;
                }
              }
              else
              {
                if(vSwUpdM_Appl_ResetDecryptionInitVector() != E_OK)
                {
                  retVal = VSTREAMPROC_FAILED;
                }
              }
            }

            /* #680 If no pending operation ongoing:
             *   Acknowledge inputs. */
            if (readAck == TRUE)
            {
              /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
              workspace->ResumeRangeInfo = (*range);

              workspace->ResumeRangeInfo.Address -= tail;
              workspace->ResumeRangeInfo.Length += tail;

              /* Only the length is used to transfer the offset value. The address is not yet used. */
              workspace->RemainderRangeInfo.Address = workspace->ResumeRangeInfo.Address - offset;
              workspace->RemainderRangeInfo.Length = offset;

              /* Acknowledge produced and consumed data */
              if (vStreamProc_AcknowledgePorts(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), NULL_PTR, 0u) != VSTREAMPROC_OK)
              {
                retVal = VSTREAMPROC_FAILED;
              }
            }
          }
        }
      }
      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_PENDING:
    /* #700 On PENDING state: */
    {
      /* #710 Evaluate result returned by read operation. */
      if (vSwUpdM_Job_EvaluateResult(&workspace->JobResult) == E_OK)
      {
        Std_ReturnType result;

        /* #720 If result available:
         *   Call user callout to set initialization vector and got to state FINISHED. */
        if (workspace->CipherMode == VSWUPMD_PROC_NODE_CIPHER_MODE_ENCRYPT)
        {
          result = vSwUpdM_Appl_SetEncryptionInitVector(workspace->InitVector, VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE);
        }
        else
        {
          result = vSwUpdM_Appl_SetDecryptionInitVector(workspace->InitVector, VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE);
        }

        if (result != E_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }

        workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
      }
      else
      {
        retVal = VSTREAMPROC_FAILED;
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED:
    /* #800 On FINISHED state: */
    {
      /* Prepare requests. */
      retVal = vStreamProc_PreparePortInfos(NodeInfo, NULL_PTR, 0u, outputPortInfos, VSWUPDM_ARRAY_SIZE(outputPortInfos));

      if (retVal == VSTREAMPROC_OK)
      {
        /* Check expected datatypes. */
        remainderRangeOutputPort->WriteRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType;
        resumeRangeOutputPort->WriteRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType;

        retVal = vStreamProc_GetPortInfos(NodeInfo, NULL_PTR, 0u, outputPortInfos, VSWUPDM_ARRAY_SIZE(outputPortInfos));
      }

      /* Request expected amount of data. */
      if (retVal == VSTREAMPROC_OK)
      {
        if (remainderRangeOutputPort->IsConnected == TRUE)
        {
          remainderRangeOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;
        }

        if (resumeRangeOutputPort->IsConnected == TRUE)
        {
          resumeRangeOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;
        }

        /* #830 If no output port connected:
         *   Return error. */
        if ((remainderRangeOutputPort->IsConnected == FALSE) && (resumeRangeOutputPort->IsConnected == FALSE))
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }

      if (retVal == VSTREAMPROC_OK)
      {
        /* Request Buffer */

        retVal = vStreamProc_RequestPortData(NodeInfo, NULL_PTR, 0u, outputPortInfos, VSWUPDM_ARRAY_SIZE(outputPortInfos));

        if (retVal == VSTREAMPROC_OK)
        {
          /* Get typed buffers. */
          /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
          vSwUpdM_RangeInfoStreamPtrType remainderRangeOutput = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&remainderRangeOutputPort->WriteRequest);
          vSwUpdM_RangeInfoStreamPtrType resumeRangeOutput = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&resumeRangeOutputPort->WriteRequest);

          if (remainderRangeOutputPort->IsConnected == TRUE)
          {
            (*remainderRangeOutput) = workspace->RemainderRangeInfo;
          }

          if (resumeRangeOutputPort->IsConnected == TRUE)
          {
            (*resumeRangeOutput) = workspace->ResumeRangeInfo;
          }

          /* Acknowledge produced data */
          retVal = vStreamProc_AcknowledgePorts(NodeInfo, NULL_PTR, 0u, outputPortInfos, VSWUPDM_ARRAY_SIZE(outputPortInfos));
        }
      }

      if (retVal == VSTREAMPROC_OK)
      {
        /* #843 Go to IDLE state. */
          workspace->State  = VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN;

      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN:
    /* #900 On SHUTDOWN state:
     *   Do nothing. */
    {
      retVal = VSTREAMPROC_OK;

      break;
    }
    default:
    {
      retVal = VSTREAMPROC_FAILED;

      break;
    }
  }
#endif

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_ProcNodeReadCipherIv_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeReadCipherIv_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeReadCipherIv_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;  /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

# if (VSWUPDM_RESUMEPROC_NODES_READ_CIPHER_IV_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = VSTREAMPROC_FAILED;
#else
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316, 3679 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr, MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ProcNodeReadCipherIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadCipherIvWorkspaceType(NodeInfo);
  /* ----- Implementation ----------------------------------------------- */

  /* #20 If state is not FINISHED:
   *      Trigger normal processing operation. */
  if (workspace->State != VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED)
  {
    retVal = vSwUpdM_ProcNodeReadCipherIv_Process(NodeInfo);
  }
#endif

  return retVal;
} /* vSwUpdM_ProcNodeReadCipherIv_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: EVAL ENCRYPTION IV
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  Std_ReturnType retVal;

#if (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = E_NOT_OK;
#else
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeEvalDecryptionIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeEvalDecryptionIvWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Initialize state and reset flags in workspace. */
  workspace->State          = VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL;
  workspace->RestartPending = FALSE;

  retVal = E_OK;
#endif

  return retVal;
} /* vSwUpdM_ProcNodeEvalDecryptionIv_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Process
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
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_PENDING; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

#if (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = VSTREAMPROC_FAILED;
#else
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeEvalDecryptionIvWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeEvalDecryptionIvWorkspaceType(NodeInfo);

  vSwUpdM_ProcNodeOperationType   operation;

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Read processOperation. */
  operation = vSwUpdM_ProcNodeShutdownOperationDefaultHandler(NodeInfo, vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_OperationInputPort, vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_OperationOutputPort, &workspace->State);


  /* #200 Evaluate state. */
  switch (workspace->State)
  {
    case VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL:
    /* #400 On INITIAL state: */
    {
      /* #410 Handle start/restart request. */
      if ( (vSwUpdM_ProcNodeRestartOperationDefaultHandler(NodeInfo, vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_OperationOutputPort, operation, &workspace->State, &workspace->RestartPending) == TRUE)
      /* #420 If no restart is required
       *   Reset initialization vector. */
        && (workspace->RestartPending == FALSE) )
      {
        if (vSwUpdM_Appl_ResetDecryptionInitVector() != E_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION:
    /* #500 On WAIT FOR PROCESS OPERATION state: */
    {
      /* #510 If PROCESS signal received:
       *   Go to next state. */
      if (operation == VSWUPDM_PROC_NODE_OPERATION_PROCESS)
      {
        workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_PENDING;
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_PENDING:
    /* #600 On WAIT FOR INPUT state: */
    {
      /* #610 Request Entities and Range inputs. */
      vStreamProc_InputPortInfoType  inputPortInfos[3u];

      /* Named pointers to list above. */
      vStreamProc_InputPortInfoPtrType  dataInputPortInfo      = &inputPortInfos[0u];
      vStreamProc_InputPortInfoPtrType  entitiesInputPortInfo  = &inputPortInfos[1u];
      vStreamProc_InputPortInfoPtrType  rangeInputPortInfo     = &inputPortInfos[2u];

      vStreamProc_OutputPortInfoType remainderRangeOutputPortInfo;

      /* Set symbolic names to Requests. */
      dataInputPortInfo->SymbolicPortName = vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_DataInputPort;
      entitiesInputPortInfo->SymbolicPortName = vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_EntityIdsInputPort;
      rangeInputPortInfo->SymbolicPortName = vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_RangeInputPort;
      remainderRangeOutputPortInfo.SymbolicPortName = vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_RemainderRangeOutputPort;

      /* Prepare requests. */
      retVal = vStreamProc_PreparePortInfos(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), &remainderRangeOutputPortInfo, 1u);

      if (retVal == VSTREAMPROC_OK)
      {
        dataInputPortInfo->ReadRequest.StorageInfo.DataTypeInfo.Id      = vStreamProcConf_vStreamProcDataType_uint8;
        entitiesInputPortInfo->ReadRequest.StorageInfo.DataTypeInfo.Id  = vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType;
        rangeInputPortInfo->ReadRequest.StorageInfo.DataTypeInfo.Id     = vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType;

        remainderRangeOutputPortInfo.WriteRequest.StorageInfo.DataTypeInfo.Id = vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType;

        retVal = vStreamProc_GetPortInfos(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), &remainderRangeOutputPortInfo, 1u);
      }

      if (retVal == VSTREAMPROC_OK)
      {
        /* #620 Evaluate if any input data is available: */
        if (vSwUpdM_ProcNode_IsInputDataAvailable(inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos)) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          /* #630: Request expected amount of data. */
          dataInputPortInfo->ReadRequest.StorageInfo.RequestLength = 1u;
          entitiesInputPortInfo->ReadRequest.StorageInfo.RequestLength = 1u;
          rangeInputPortInfo->ReadRequest.StorageInfo.RequestLength = 1u;

          remainderRangeOutputPortInfo.WriteRequest.StorageInfo.RequestLength = 1u;

          /* Request Buffer. */
          retVal = vStreamProc_RequestPortData(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), &remainderRangeOutputPortInfo, 1u);

          if (retVal == VSTREAMPROC_OK)
          {
            /* Get typed buffers. */
            /* PRQA S 0310, 3305 4 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            vSwUpdM_DataReadStreamPtrType data = vStreamProc_GetTypedReadRequestBuffer_uint8(&dataInputPortInfo->ReadRequest);
            vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPortInfo->ReadRequest);
            vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPortInfo->ReadRequest);
            vSwUpdM_RangeInfoStreamPtrType remainderRange = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&remainderRangeOutputPortInfo.WriteRequest);

            vSwUpdM_SegmentInfoType segmentInfo;
            vSwUpdM_LengthType      writtenLength;
            vSwUpdM_RangeInfoType   rangeInfo;

            /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            (void)vSwUpdM_GetSegmentInfo(&segmentInfo, entities->SegmentId);

            writtenLength = segmentInfo.WriteAddress - segmentInfo.StartAddress;

            rangeInfo = (*range);

            /* #640 If restart is pending:
             *   Calculate offset to initialization vector. */
            if (workspace->RestartPending == TRUE)
            {
              vSwUpdM_LengthType  ivOffset = 0u;
              vSwUpdM_LengthType  ivLength = 0u;

              if (writtenLength >= (2u * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE))
              {
                uint32 blockCount = writtenLength / VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE;

                ivOffset = ((blockCount + 1u) * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE) - writtenLength;
                ivLength = VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE + ivOffset;
              }
              else
              {
                if (writtenLength >= VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE)
                {
                  /* IV located at beginning of data. */
                  ivLength = VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE;
                }
              }

              /* #650 If expected amount of data is read: */
              if (dataInputPortInfo->ReadRequest.StorageInfo.AvailableLength >= ivLength)
              {
                /* #651 If enough data available to extract initialization vector:
                 *   Call callout to store initialization vector. */
                if (ivLength > 0u)
                {
                  if (vSwUpdM_Appl_SetDecryptionInitVector(&data[ivOffset], VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE) != E_OK)
                  {
                    retVal = VSTREAMPROC_FAILED;
                  }
                }
                else
                {
                  /* #652 Otherwise:
                   *   Call callout to set default initialization vector. */
                  if (vSwUpdM_Appl_ResetDecryptionInitVector() != E_OK)
                  {
                    retVal = VSTREAMPROC_FAILED;
                  }
                }

                if (retVal == VSTREAMPROC_OK)
                {
                  remainderRange->Address = rangeInfo.Address - ivLength;
                  remainderRange->Length = ivLength;

                  dataInputPortInfo->ReadRequest.StorageInfo.RequestLength = dataInputPortInfo->ReadRequest.StorageInfo.AvailableLength;

                  workspace->RestartPending = FALSE;
                  workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
                }
              }
              else
              {
                retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
              }
            }
            else
            {
              /* #660 Otherwise:
               *   Pass-through of range. */
              remainderRange->Address = rangeInfo.Address;
              remainderRange->Length = rangeInfo.Length;

              dataInputPortInfo->ReadRequest.StorageInfo.RequestLength = dataInputPortInfo->ReadRequest.StorageInfo.AvailableLength;

              workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
            }

            /* Acknowledge produced and consumed data */
            if (vStreamProc_AcknowledgePorts(NodeInfo, inputPortInfos, VSWUPDM_ARRAY_SIZE(inputPortInfos), &remainderRangeOutputPortInfo, 1u) != VSTREAMPROC_OK)
            {
              retVal = VSTREAMPROC_FAILED;
            }
          }
        }
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED:
    /* #700 On FINISHED state: */
    {
      /* #710 Consume data input. */
      retVal = vSwUpdM_ResumeProcNode_ConsumeInput(
        NodeInfo,
        vStreamProcConf_External_vSwUpdM_EvalDecryptionIv_DataInputPort,
        vStreamProcConf_vStreamProcDataType_uint8,
        0u,
        VSTREAMPROC_MAX_LENGTH,
        NULL_PTR);

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN:
    /* #800 On SHUTDOWN state:
     *   Do nothing. */
    {
      retVal = VSTREAMPROC_OK;

      break;
    }
    default:
    {
      retVal = VSTREAMPROC_FAILED;

      break;
    }
  }
#endif

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_ProcNodeEvalDecryptionIv_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeEvalDecryptionIv_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeEvalDecryptionIv_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if (VSWUPDM_RESUMEPROC_NODES_EVAL_DECYPTION_IV_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = VSTREAMPROC_FAILED;
#else
  /* #10 Trigger normal processing operation. */
  retVal = vSwUpdM_ProcNodeEvalDecryptionIv_Process(NodeInfo);
#endif

  return retVal;
} /* vSwUpdM_ProcNodeEvalDecryptionIv_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: PASS-THROUGH
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  Std_ReturnType retVal;

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = E_NOT_OK;
#else
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeResumePassthroughWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeResumePassthroughWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize state and reset flags in workspace. */
  workspace->State          = VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL;
  workspace->RestartPending = FALSE;
  retVal = E_OK;
#endif

  return retVal;
} /* vSwUpdM_ProcNodeResumePassthrough_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Process
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_PENDING; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  retVal = VSTREAMPROC_FAILED;
#else
   /* #10 Infer the specialized workspace from the processing node. */
   /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeResumePassthroughWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeResumePassthroughWorkspaceType(NodeInfo);
  vSwUpdM_ProcNodeOperationType   operation;

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Read processOperation. */
  operation = vSwUpdM_ProcNodeShutdownOperationDefaultHandler(NodeInfo, vStreamProcConf_External_vSwUpdM_ResumePassthrough_OperationInputPort, vStreamProcConf_External_vSwUpdM_ResumePassthrough_OperationOutputPort, &workspace->State);

  /* #30 Evaluate state. */
  switch (workspace->State)
  {
    case VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL:
    /* #100 On INITIAL state: */
    {
      /* #110 Handle start/restart request. */
      (void)vSwUpdM_ProcNodeRestartOperationDefaultHandler(NodeInfo, vStreamProcConf_External_vSwUpdM_ResumePassthrough_OperationOutputPort, operation, &workspace->State, &workspace->RestartPending);

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION:
    /* #200 On WAIT FOR PROCESS OPERATION state: */
    {
      /* #210 If PROCESS signal received:
       *      Go to next state. */
      if (operation == VSWUPDM_PROC_NODE_OPERATION_PROCESS)
      {
        workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS;
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS:
    /* #300 On WAIT FOR INPUT state: */
    {
      /* #310 Request Range input. */
      vStreamProc_InputPortInfoType  rangeInputPortInfo;

      /* Prepare request */
      retVal = vStreamProc_PrepareInputPortInfo(NodeInfo, vStreamProcConf_External_vSwUpdM_ResumePassthrough_RemainderRangeInputPort, &rangeInputPortInfo);

      if (retVal == VSTREAMPROC_OK)
      {
        retVal = vStreamProc_GetInputPortInfo(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType, &rangeInputPortInfo);
      }

      if (retVal == VSTREAMPROC_OK)
      {
        /* #320 Evaluate if any input data is available: */
        if (vSwUpdM_ProcNode_IsInputDataAvailable(&rangeInputPortInfo, 1u) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          /* Request Buffer */
          retVal = vStreamProc_RequestInputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType, 1u, &rangeInputPortInfo);

          if (retVal == VSTREAMPROC_OK)
          {
            /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPortInfo.ReadRequest);

            /* #321 Store length in workspace. */
            workspace->Remainder = range->Length;
            workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_PENDING;

            retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, 1u, TRUE, &rangeInputPortInfo);
            if (retVal == VSTREAMPROC_OK)
            {
              retVal = VSTREAMPROC_PENDING;
            }
          }
        }
      }
      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_PENDING:
    /* #400 On PENDING state: */
    {
      /* #410 If Restart is Pending:
       *      Consume superfluous input data. */
      if (workspace->RestartPending == TRUE)
      {
        if (workspace->Remainder > 0u)
        {
          vSwUpdM_LengthType consumed;

          retVal = vSwUpdM_ResumeProcNode_ConsumeInput(
            NodeInfo,
            vStreamProcConf_External_vSwUpdM_ResumePassthrough_DataInputPort,
            vStreamProcConf_vStreamProcDataType_uint8,
            1u,
            workspace->Remainder,
            &consumed);

          if (retVal == VSTREAMPROC_OK)
          {
            workspace->Remainder -= consumed;
          }
        }
        if (workspace->Remainder == 0u)
        {
          workspace->RestartPending = FALSE;
        }
      }
       /* #420 If no restart pending (anymore):
        *      Copy input to output. */
      if (workspace->RestartPending == FALSE)
      {
        retVal = vSwUpdM_ResumeProcNode_Passthrough(
            NodeInfo,
            vStreamProcConf_External_vSwUpdM_ResumePassthrough_DataInputPort,
            vStreamProcConf_External_vSwUpdM_ResumePassthrough_DataOutputPort);
      }

      break;
    }
    case VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN:
    /* #500 On SHUTDOWN state:
     *   Do nothing. */
    {
      retVal = VSTREAMPROC_OK;

      break;
    }
    default:
    {
      retVal = VSTREAMPROC_FAILED;

      break;
    }
  }
#endif

  return retVal;

  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_ProcNodeResumePassthrough_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePassthrough_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePassthrough_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PASSTHROUGH_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = VSTREAMPROC_FAILED;
#else
  /* #10 Trigger normal processing operation. */
  retVal = vSwUpdM_ProcNodeResumePassthrough_Process(NodeInfo);
#endif

  return retVal;
} /* vSwUpdM_ProcNodeResumePassthrough_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: PADDING (RESUME)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  Std_ReturnType retVal;
#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = E_NOT_OK;
#else
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeResumePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeResumePaddingWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Initialize flag for first call and reset total length in workspace. */
  workspace->PaddingNodeWorkspace.State = VSWUPDM_PADDING_NODE_STATE_INITIAL;
  workspace->PaddingNodeWorkspace.TotalLength = 0u;

  /* #30 Initialize input/output port references in workspace. */
  workspace->PaddingNodeWorkspace.DataInputPortId =             vStreamProcConf_External_vSwUpdM_ResumePadding_DataInputPort;
  workspace->PaddingNodeWorkspace.EntitiesInputPortId =         vStreamProcConf_External_vSwUpdM_ResumePadding_EntitiesInputPort;
  workspace->PaddingNodeWorkspace.AlignedRangeOutputPortId =    vStreamProcConf_External_vSwUpdM_ResumePadding_AlignedRangeOutputPort;
  workspace->PaddingNodeWorkspace.DataOutputPortId =            vStreamProcConf_External_vSwUpdM_ResumePadding_DataOutputPort;
  workspace->PaddingNodeWorkspace.RangeInputPortId =            vStreamProcConf_External_vSwUpdM_ResumePadding_RangeInputPort;
  workspace->PaddingNodeWorkspace.ResultingRangesOutputPortId = vStreamProcConf_External_vSwUpdM_ResumePadding_ResultingRangesOutputPort;

  workspace->OperationInputPort             = vStreamProcConf_External_vSwUpdM_ResumePadding_OperationInputPort;
  workspace->OperationOutputPort            = vStreamProcConf_External_vSwUpdM_ResumePadding_OperationOutputPort;

  /* #40 Initialize state and reset flags in workspace. */
  workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL;
  workspace->RestartPending = FALSE;

  retVal = E_OK;
#endif
  return retVal;
} /* vSwUpdM_ProcNodeResumePadding_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Process
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_PENDING; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal =  VSTREAMPROC_FAILED;
#else
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeResumePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeResumePaddingWorkspaceType(NodeInfo);
  vSwUpdM_ProcNodeOperationType   operation;
  vStreamProc_InputPortInfoPtrType dataInputPort;
  vStreamProc_InputPortInfoPtrType entitiesInputPort;

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_ResumePadding];

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding,
    NULL_PTR,
    vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_ResumePadding
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* #20 Request input port information. */
  entitiesInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_ResumePadding_EntitiesInputPort];
  dataInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_ResumePadding_DataInputPort];

  /* ----- Implementation ----------------------------------------------- */

  retVal = vSwUpdM_ProcNode_PreparePorts(
    NodeInfo,
    &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #30 Read processOperation. */
    operation = vSwUpdM_ProcNodeShutdownOperationDefaultHandler(NodeInfo, workspace->OperationInputPort, workspace->OperationOutputPort, &workspace->State);

    /* #40 Evaluate state. */
    switch (workspace->State)
    {
      case VSWUPDM_RESUME_PROC_NODE_STATE_INITIAL:
      /* #100 On INITIAL state: */
      {
        /* #110 Handle start/restart request. */
        (void)vSwUpdM_ProcNodeRestartOperationDefaultHandler(NodeInfo, workspace->OperationOutputPort, operation, &workspace->State, &workspace->RestartPending);

        break;
      }
      case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_PROCESS_OPERATION:
      /* #200 On WAIT FOR PROCESS OPERATION state: */
      {
        /* #210 If PROCESS signal received: */
        if (operation == VSWUPDM_PROC_NODE_OPERATION_PROCESS)
        {
          /* #211 If restart is pending:
           *   Go to state WAIT FOR INPUTS. */
          if (workspace->RestartPending == TRUE)
          {
            workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS;
          }
          else
          {
            /* #212 Otherwise: go to state FINISHED. */
            workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
          }
          retVal = VSTREAMPROC_PENDING;
        }

        break;
      }
      case VSWUPDM_RESUME_PROC_NODE_STATE_WAIT_FOR_INPUTS:
      /* #300 On WAIT FOR INPUT state: */
      {
        /* #310 Evaluate if any input data is available: */
        if (vSwUpdM_ProcNode_IsInputDataAvailable(entitiesInputPort, 1u) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

          /* Request Buffer */
          retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, &ports);

          if (retVal == VSTREAMPROC_OK)
          {
            vSwUpdM_SegmentInfoType                   segmentInfo;
            vSwUpdM_LengthType                        writtenLength;
            uint32                                    blockCount;
            /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
            vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);

            (void)vSwUpdM_GetSegmentInfo(&segmentInfo, entities->SegmentId);

            writtenLength = segmentInfo.WriteAddress - segmentInfo.StartAddress;
            blockCount = writtenLength / VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE;

            /* #320 Store data in Workspace. */
            workspace->Remainder = writtenLength - (blockCount * VSWUPDM_PROC_NODE_RESUME_BLOCK_SIZE);
            workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_PENDING;

            retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, 0u, TRUE, entitiesInputPort);
          }
        }

        break;
      }
      case VSWUPDM_RESUME_PROC_NODE_STATE_PENDING:
      /* #400 On PENDING state: */
      {
        if (dataInputPort->ReadRequest.StorageInfo.AvailableLength > 0u)
        {
          /* #410 Read input data, count and discard it. */

          /* Request Buffer */
          dataInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

          /* Request Buffer */
          retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, &ports);

          if (retVal == VSTREAMPROC_OK)
          {
            vSwUpdM_LengthType consumedLength = dataInputPort->ReadRequest.StorageInfo.AvailableLength;

            if (consumedLength > workspace->Remainder)
            {
              consumedLength = workspace->Remainder;
            }

            workspace->Remainder -= consumedLength;

            retVal = vStreamProc_AcknowledgeInputPort(NodeInfo, consumedLength, TRUE, dataInputPort);
          }
        }

        if (retVal == VSTREAMPROC_OK)
        {
          /* #420 If end of written data reached goto state FINISHED. */
          if (workspace->Remainder == 0u)
          {
            workspace->RestartPending = FALSE;
            workspace->State = VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED;
            retVal = VSTREAMPROC_PENDING;
          }
        }

        break;
      }
      case VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED:
      /* #500 On FINISHED state: */
      {
        /* #510 Do padding. */
        retVal = vSwUpdM_ProcNodePadding_ProcessInternal(NodeInfo, &workspace->PaddingNodeWorkspace, &ports);

        break;
      }
      case VSWUPDM_RESUME_PROC_NODE_STATE_SHUTDOWN:
      /* #600 On SHUTDOWN state:
       *      Do nothing. */
      {
        retVal = VSTREAMPROC_OK;

        break;
      }
      default:
      {
        retVal = VSTREAMPROC_FAILED;

        break;
      }
    }
  }

#endif
  return retVal;

  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STCYC */
} /* vSwUpdM_ProcNodeResumePadding_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeResumePadding_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeResumePadding_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;  /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

#if (VSWUPDM_RESUMEPROC_NODES_RESUME_PADDING_NODE == STD_OFF)
  VSWUPDM_DUMMY_STATEMENT(NodeInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = VSTREAMPROC_FAILED;
#else
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeResumePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeResumePaddingWorkspaceType(NodeInfo);

  /* #20 Call Process routine until state is FINISHED. */
  if (workspace->State != VSWUPDM_RESUME_PROC_NODE_STATE_FINISHED)
  {
    retVal = vSwUpdM_ProcNodeResumePadding_Process(NodeInfo);
  }
  else
  {
    vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding];
    vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_ResumePadding];

    vSwUpdM_ProcNodesPortsCollectionType ports =
    {
      NULL_PTR,
      vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_InputPortDatatype,
      vStreamProcConf_InputPortCount_External_vSwUpdM_ResumePadding,
      NULL_PTR,
      vSwUpdM_ProcNodes_ResumePaddingNodePortsConfig_OutputPortDatatype,
      vStreamProcConf_OutputPortCount_External_vSwUpdM_ResumePadding
    };
    ports.InputPortInfos = inputPortInfos;
    ports.OutputPortInfos = outputPortInfos;

    /* #30 Otherwise:
     *     Use Flush() routine from padding node. */
    retVal = vSwUpdM_ProcNode_PreparePorts(
      NodeInfo,
      &ports);

    if (retVal == VSTREAMPROC_OK)
    {
      retVal = vSwUpdM_ProcNodePadding_FlushInternal(NodeInfo, &workspace->PaddingNodeWorkspace, &ports);
    }
  }

#endif

  return retVal;

} /* vSwUpdM_ProcNodePadding_Flush */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ResumeProcNodes.c
 *********************************************************************************************************************/
