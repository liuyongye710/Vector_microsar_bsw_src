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
/*!        \file  vSwUpdM_ProcNodes.c
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

#define VSWUPDM_PROCNODES_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_ProcNodes.h"
#include "vSwUpdM_ProcNodeTypes.h"
#include "SchM_vSwUpdM.h"
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Range.h"
#include "vSwUpdM_ExecCtrl_Impl.h"

#include "vStreamProc.h"
#include "vStreamProc_Port.h"

#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 * PROCESSING NODE: PADDING
 *********************************************************************************************************************/

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_PaddingNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_Padding] =
{
  {vStreamProcConf_External_vSwUpdM_Padding_DataInputPort,     vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_Padding_EntitiesInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType},
  {vStreamProcConf_External_vSwUpdM_Padding_RangeInputPort,    vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType}
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_PaddingNodePortsConfig_OutputPortDatatype[vStreamProcConf_OutputPortCount_External_vSwUpdM_Padding] =
{
  {vStreamProcConf_External_vSwUpdM_Padding_DataOutputPort,            vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_Padding_AlignedRangeOutputPort,    vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType},
  {vStreamProcConf_External_vSwUpdM_Padding_ResultingRangesOutputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType}
};

/**********************************************************************************************************************
 * PROCESSING NODE: WRITE
 *********************************************************************************************************************/

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_WriteNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_Write] =
{
  {vStreamProcConf_External_vSwUpdM_Write_DataInputPort, vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_Write_EntitiesInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType},
  {vStreamProcConf_External_vSwUpdM_Write_RangeInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType}
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_WriteNodePortsConfig_OutputPortDatatype[vStreamProcConf_OutputPortCount_External_vSwUpdM_Write] =
{
  {vStreamProcConf_External_vSwUpdM_Write_ResultOutputPort, vStreamProcConf_vStreamProcDataType_Std_ReturnType }
};

/**********************************************************************************************************************
 * PROCESSING NODE: READ
 *********************************************************************************************************************/

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_ReadNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_Read] =
{
  {vStreamProcConf_External_vSwUpdM_Read_EntitiesInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType},
  {vStreamProcConf_External_vSwUpdM_Read_RangeInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType}
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_ReadNodePortsConfig_OutputPortDatatype[vStreamProcConf_OutputPortCount_External_vSwUpdM_Read] =
{
  {vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort, vStreamProcConf_vStreamProcDataType_uint8          },
  {vStreamProcConf_External_vSwUpdM_Read_DataOutputPort,        vStreamProcConf_vStreamProcDataType_uint8          },
  {vStreamProcConf_External_vSwUpdM_Read_ResultOutputPort,      vStreamProcConf_vStreamProcDataType_Std_ReturnType }
};

/**********************************************************************************************************************
 * PROCESSING NODE: TRACK COMPARE PROGRESS
 *********************************************************************************************************************/

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_TrackCompareProgressNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_TrackCompareProgress] =
{
  {vStreamProcConf_External_vSwUpdM_TrackCompareProgress_CountInputPort, vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_TrackCompareProgress_EntitiesInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType},
  {vStreamProcConf_External_vSwUpdM_TrackCompareProgress_RangeInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_RangeInfoType}
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_TrackCompareProgressNodePortsConfig_OutputPortDatatype[1u] =
{
  {0xFFu, vStreamProcConf_vStreamProcDataTypeCount} /* Dummy entry. */
};

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * PROCESSING NODE: REMOTE
 *********************************************************************************************************************/

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_RemoteNodePortsConfig_InputPortDatatype[vStreamProcConf_InputPortCount_External_vSwUpdM_Remote] =
{
  {vStreamProcConf_External_vSwUpdM_Remote_DataInputPort, vStreamProcConf_vStreamProcDataType_uint8},
  {vStreamProcConf_External_vSwUpdM_Remote_EntitiesInputPort, vStreamProcConf_vStreamProcDataType_vSwUpdM_EntityIdsType}
};

/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, VSWUPDM_CONST) vSwUpdM_ProcNodes_RemoteNodePortsConfig_OutputPortDatatype[vStreamProcConf_OutputPortCount_External_vSwUpdM_Remote] =
{
  {vStreamProcConf_External_vSwUpdM_Remote_ResultOutputPort, vStreamProcConf_vStreamProcDataType_Std_ReturnType }
};

#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_SerializeAddress
 **********************************************************************************************************************/
/*! \brief       Convert given integer value to big-endian byte array.
*   \details     -
 *  \param[in]   Count  Number of relevant bytes.
 *  \param[in]   Input  Input value.
 *  \param[out]  Buffer Pointer to output buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_SerializeAddress(
  vSwUpdM_LengthType Count,
  vSwUpdM_AddressType Input,
  vSwUpdM_VarDataPointerType Buffer);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_InitStep
 **********************************************************************************************************************/
/*! \brief       Do initial calculations on range input.
 *  \details     Calculate the length of padding in front of the payload data and store it in the workspace.
 *
 *               Provide Aligned Range output:
 *
 *               Input Range:           |<---------->|
 *               Alignment grid:   |      |      |      |
 *               Aligned Range:    |<--------------->|
 *               Padding Length:   |<-->|
 *
 *  \param[in]   NodeInfo                          The processing node information to operate on.
 *  \param[in]   Workspace                         The workspace of the processing node.
 *  \param[in]   Ports                             The structure for generalized port access.
 *  \return      VSTREAMPROC_OK                    Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_InitStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Padding
 **********************************************************************************************************************/
/*! \brief       Apply padding: Write PadLength fill-bytes to output port.
*   \details     -
 *  \param[in]   NodeInfo                          The processing node information to operate on.
 *  \param[in]   PadLength                         Number of bytes to write.
 *  \param[in]   Workspace                         The workspace of the processing node.
 *  \param[in]   Ports                             The structure for generalized port access.
 *  \return      VSTREAMPROC_OK                    Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Padding(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_LengthType PadLength,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Copy
 **********************************************************************************************************************/
/*! \brief       Copy input to output.
*   \details     -
 *  \param[in]   NodeInfo                          The processing node information to operate on.
 *  \param[in]   Length                            Number of bytes to copy.
 *  \param[in]   Workspace                         The workspace of the processing node.
 *  \param[in]   Ports                             The structure for generalized port access.
 *  \return      VSTREAMPROC_OK                    Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Copy(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
   P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_DATA) Length,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_FinalStep
 **********************************************************************************************************************/
/*! \brief       Do final calculations on range input.
 *  \details     Calculate the length of padding after the end of the payload data and store it in the workspace.
 *               The payload can be less than initially announced ("Dynamic Length"), therefore the TotalLength is
 *               used to count the real used space in the memory.
 *
 *               Provide Aligned Range Info output:
 *
 *               Input Range (Announced Range):          |<---------------...->|
 *               Payload:                                XXXXXXXXXXXXX
 *               Total Length (Really used Length): |----------------|
 *               Alignment grid:                    |      |      |      |
 *               Initial Padding:                   |<-->|
 *               Padding Length:                                     |<->|
 *               alignedRangeInfoWrite[0]:               |<----------|
 *               alignedRangeInfoWrite[1]:          |<-------------------|
 *
 *               HINT: the alignedRangeInfoWrite ranges are given in backward direction.
 *
 *  \param[in]   NodeInfo                          The processing node information to operate on.
 *  \param[in]   Workspace                         The workspace of the processing node.
 *  \param[in]   Ports                             The structure for generalized port access.
 *  \return      VSTREAMPROC_OK                    Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_FinalStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_InitialStep
 **********************************************************************************************************************/
 /*! \brief       Do inital steps.
 *   \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_InitialStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNode_SpawnJob
 **********************************************************************************************************************/
 /*! \brief       Spawn job and sets given attributes.
  *   \details     -
  *  \param[in]     JobType             Job to spawn
  *  \param[in]     Entities            Entities to be used by job.
  *  \param[in]     TargetAddress       TargetAddress to be used by job.
  *  \param[in]     InputBuffer         InputBuffer to be used by job.
  *  \param[in]     OutputBuffer        OutputBuffer to be used by job.
  *  \param[in]     ProcessingLength    ProcessingLength to be used by job.
  *  \param[in]     RemoteServiceIndex  RemoteServiceIndex to be used by job.
  *  \param[in]     RemoteTargetGroup   RemoteTargetGroup to be used by job.
  *  \param[in,out] LinkedResult        Provided buffer for job result.
  *  \return      E_OK                  Operation was successful.
  *  \return      E_NOT_OK              Else
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_SpawnJob(
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_EntityIdsReadStreamPtrType Entities,
  vSwUpdM_AddressType TargetAddress,
  vSwUpdM_DataReadStreamPtrType InputBuffer,
  vSwUpdM_DataStreamPtrType OutputBuffer,
  vSwUpdM_LengthType ProcessingLength,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_NodeGroupIterType RemoteTargetGroup,
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_TriggerJob
 **********************************************************************************************************************/
 /*! \brief       Prepare and spawn job to write data to memory.
  *   \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_EvaluateJobResult
 **********************************************************************************************************************/
 /*! \brief       Evaluate result of write job.
 *   \details     Consume input data and handle result of job.
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_DetermineRequestSizes
 **********************************************************************************************************************/
 /*! \brief       Calculate the required requests sizes for in-/output ports.
  *  \details     -
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \param[in]   AddrLenIsWritten                  The Address, Length is added before the output of the read data.
  *                                                 If this is not yet done, additional space is requested therefore.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_DetermineRequestSizes(
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports,
  boolean AddrLenIsWritten);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_ProvideRangeOutput
 **********************************************************************************************************************/
 /*! \brief       Serialize address and length into provided output buffer.
  *  \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \return      VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
  *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_ProvideRangeOutput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_TriggerJob
 **********************************************************************************************************************/
 /*! \brief       Prepare and spawn job to read memory.
  *   \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \return      VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
  *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_EvaluateJobResult
 **********************************************************************************************************************/
 /*! \brief       Evaluate result of read job.
  *   \details    Provide output data and handle result of job.
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_ProcessData
 **********************************************************************************************************************/
 /*! \brief       Sum up the input data count (address) and trigger persist if checkpoint is hit.
  *  \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_ProcessData(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_InitialStep
 **********************************************************************************************************************/
 /*! \brief       Store entities and range in workspace
  *  \details    -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_InitialStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_TriggerJob
 **********************************************************************************************************************/
 /*! \brief       Prepare and spawn a job to transmit data to remote node.
  *  \details    -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_EvaluateJobResult
 **********************************************************************************************************************/
 /*! \brief       Evaluate result returned by remote operation.
  *   \details    -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_PENDING               Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_ProcessData
 **********************************************************************************************************************/
 /*! \brief       Process read request.
  *  \details     -
  *  \param[in]   NodeInfo                          The processing node information to operate on.
  *  \param[in]   Ports                             The structure for generalized port access.
  *  \return      VSTREAMPROC_OK                    Operation was successful.
  *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
  *  \context     TASK
  *  \reentrant   TRUE
  *  \synchronous TRUE
  *  \pre         -
  **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_ProcessData(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports);

/***********************************************************************************************************************
 *  vSwUpdM_ProcNode_ResultOutput
 **********************************************************************************************************************/
/*! \brief       Write a given Std_ReturnType to an output port defined by its symbolic name.
*   \details     -
 *  \param[in]   NodeInfo                          The processing node information to operate on.
 *  \param[in]   SymbolicNameOfOutputPort          References the output port.
 *  \param[in]   Result                            Data to write.
 *  \return      VSTREAMPROC_OK                    Operation was successful.
 *  \return      VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 *  \return      VSTREAMPROC_FAILED                Operation was unsuccessful.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_ResultOutput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_SerializeAddress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_SerializeAddress(
  vSwUpdM_LengthType Count,
  vSwUpdM_AddressType Input,
  vSwUpdM_VarDataPointerType Buffer)
{
  vSwUpdM_LengthType  index = Count;
  vSwUpdM_AddressType value = Input;

  /* #10 Loop relevant bytes. */
  while (index > 0u)
  {
    index--;

    /* #20 Store most significant byte first. */
    Buffer[index] = (vSwUpdM_DataType)(value & 0xFFu);

    /* #30 Shift in next byte. */
    value >>= 8u;
  }
} /* vSwUpdM_ProcNodeRead_SerializeAddress */

/**********************************************************************************************************************
 * vSwUpdM_ProcNode_IsInputDataAvailable
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ProcNode_IsInputDataAvailable(
  vStreamProc_InputPortInfoConstPtrType InputPortInfos,
  vStreamProc_InputPortIdType Count)
{
  vStreamProc_InputPortIdType i;
  boolean retVal = FALSE;

  for (i = 0u; i < Count; i++)
  {
    if (InputPortInfos[i].ReadRequest.StorageInfo.AvailableLength > 0u)
    {
      retVal = TRUE;
      break;
    }
  }

  return retVal;

} /* vSwUpdM_ProcNode_IsInputDataAvailable */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodePadding_InitStep
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
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_InitStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;
  vStreamProc_InputPortInfoPtrType entitiesInputPort = &Ports->InputPortInfos[Workspace->EntitiesInputPortId];
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[Workspace->RangeInputPortId];
  vStreamProc_OutputPortInfoPtrType alignedRangeOutputPort = &Ports->OutputPortInfos[Workspace->AlignedRangeOutputPortId];

  /* #10 Request expected minimum amount of data. */
  entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  alignedRangeOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;

  retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Get typed buffers. */
    /* PRQA S 0310, 3305 3 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
    vSwUpdM_PartitionIdType partitionId = (vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest))->PartitionId;
    vSwUpdM_RangeInfoReadStreamPtrType rangeInfo = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
    vSwUpdM_RangeInfoStreamPtrType alignedRangeInfo = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&alignedRangeOutputPort->WriteRequest);

    /* #30 Do work: */
    vSwUpdM_AddressType alignedAddress = rangeInfo->Address;

    /* #31 Align start address of range to page boundary. */
    if (vSwUpdM_Range_AlignAddress(&alignedAddress, partitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT, VSWUPDM_ALIGN_GRANULARITY_PAGE) == E_OK)
    {
      /* #32 Store Padding length in workspace. */
      Workspace->PadLength = rangeInfo->Address - alignedAddress;
    }

      /* #33 Output aligned range. */
      alignedRangeInfo->Address = alignedAddress;
      alignedRangeInfo->Length = rangeInfo->Length + Workspace->PadLength;

      /* #40 Release requested input buffers without consuming.
       *     Their content will be used again on Flush().
       */
      entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
      rangeInputPort->ReadRequest.StorageInfo.RequestLength = 0u;

      retVal = vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports);
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_InitStep */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_ProcessInternal
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_ProcessInternal(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal = VSTREAMPROC_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch (Workspace->State)
  {
    case VSWUPDM_PADDING_NODE_STATE_INITIAL:
    /* #10 Wait for any input data.
     *     If any data is received go to next state. Now the node can not be
     *     flushed without processing anymore.
     */
    {
      if (vSwUpdM_ProcNode_IsInputDataAvailable(
        Ports->InputPortInfos,
        Ports->InputPortCount) == TRUE)
      {
        Workspace->State = VSWUPDM_PADDING_NODE_STATE_WAIT_FOR_INPUTS;
        retVal = VSTREAMPROC_PENDING;
      }
      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_WAIT_FOR_INPUTS:
    {
      /* #20 Wait for input data and do initial step:
       *     Calculate the length of padding in front of the payload data,
       *     store it in the workspace and provide Aligned Range output.
       */
      if (vSwUpdM_ProcNodePadding_InitStep(NodeInfo, Workspace, Ports) == VSTREAMPROC_OK)
      {
        Workspace->State = VSWUPDM_PADDING_NODE_STATE_PADDING_START;
        retVal = VSTREAMPROC_PENDING;
      }
      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_PADDING_START:
    /* #30 Apply padding before payload data. */
    {
      if (Workspace->PadLength > 0u)
      {
        /* Apply padding: */
        retVal = vSwUpdM_ProcNodePadding_Padding(NodeInfo, Workspace->PadLength, Workspace, Ports);

        if (retVal == VSTREAMPROC_OK)
        {
          /* Remember that padding is done. */
          Workspace->PadLength = 0u;
          retVal = VSTREAMPROC_PENDING;
        }
      }
      else
      {
        /* No padding required. */
        Workspace->State = VSWUPDM_PADDING_NODE_STATE_COPY;
        retVal = VSTREAMPROC_PENDING;
      }
      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_COPY:
    /* #40 Copy payload data from input to output. */
    {
      vSwUpdM_LengthType length = 0u;
      retVal = vSwUpdM_ProcNodePadding_Copy(NodeInfo, &length, Workspace, Ports);

      /* Count number of copied bytes. */
      Workspace->TotalLength += length;
      break;
    }
    default:
    /* case VSWUPDM_PADDING_NODE_STATE_FINAL_STEP:
     * case VSWUPDM_PADDING_NODE_STATE_PADDING_END:
     * case VSWUPDM_PADDING_NODE_STATE_FINISHED:
     */
    {
      /* Nothing to do. */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_ProcessInternal */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_FlushInternal
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_FlushInternal(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 1 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Evaluate State: */
  switch (Workspace->State)
  {
    default:
    /* case VSWUPDM_PADDING_NODE_STATE_WAIT_FOR_INPUTS:
     * case VSWUPDM_PADDING_NODE_STATE_PADDING_START:
     * case VSWUPDM_PADDING_NODE_STATE_COPY:
     */
    /* #100 Default: Trigger normal processing operation. */
    {
      retVal = vSwUpdM_ProcNodePadding_ProcessInternal(NodeInfo, Workspace, Ports);

      if (retVal == VSTREAMPROC_OK)
      {
        Workspace->State = VSWUPDM_PADDING_NODE_STATE_FINAL_STEP;
        retVal = VSTREAMPROC_PENDING;
      }

      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_INITIAL:
    case VSWUPDM_PADDING_NODE_STATE_FINISHED:
    /* #200 On INITIAL or FINISHED state:
            Nothing to do to flush. */
    {
      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_FINAL_STEP:
    {
      retVal = vSwUpdM_ProcNodePadding_FinalStep(NodeInfo, Workspace, Ports);

      if (retVal == VSTREAMPROC_OK)
      {
        Workspace->State = VSWUPDM_PADDING_NODE_STATE_PADDING_END;
        retVal = VSTREAMPROC_PENDING;
      }
      break;
    }
    case VSWUPDM_PADDING_NODE_STATE_PADDING_END:
    /* #300 On state PADDING END:
     *      Apply padding at the end. */
    {
      if (Workspace->PadLength > 0u)
      {
        retVal = vSwUpdM_ProcNodePadding_Padding(NodeInfo, Workspace->PadLength, Workspace, Ports);
        if (retVal == VSTREAMPROC_OK)
        {
          /* Remember that padding is done. */
          Workspace->PadLength = 0u;
          Workspace->State = VSWUPDM_PADDING_NODE_STATE_FINISHED;
        }
      }
      break;
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_FlushInternal */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodePadding_Padding
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
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Padding(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_LengthType PadLength,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType  retVal;
  vStreamProc_OutputPortInfoPtrType dataOutputPort = &Ports->OutputPortInfos[Workspace->DataOutputPortId];

  /* #10 Request data output buffer of size PadLength. */
  dataOutputPort->WriteRequest.StorageInfo.RequestLength = PadLength;

  retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Get typed buffer. */
    vSwUpdM_DataStreamPtrType buffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataOutputPort->WriteRequest);

    /* #30 Apply padding by filling output buffer with pattern. */
    vSwUpdM_Buffer_Fill(buffer, vSwUpdM_GetFillByte(), PadLength);

    /* #40 Release buffer. */
    retVal = vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports);
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_Padding */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodePadding_Copy
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
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Copy(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
   P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_DATA) Length,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace, /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType  retVal = VSTREAMPROC_OK;
  vStreamProc_InputPortInfoPtrType dataInputPort = &Ports->InputPortInfos[Workspace->DataInputPortId];
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[Workspace->RangeInputPortId];
  vStreamProc_OutputPortInfoPtrType dataOutputPort = &Ports->OutputPortInfos[Workspace->DataOutputPortId];

  /* #10 Evaluate if any input data is available: */
  if (dataInputPort->ReadRequest.StorageInfo.AvailableLength == 0u)
  {
    /* No input data available: Node is idle. */
  }
  else
  {
    /* #20 Request (minimum) required amount of data. */
    dataInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
    rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
    dataOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;

    retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);

    if (retVal == VSTREAMPROC_OK)
    {
      vSwUpdM_LengthType length;

      /* #30 Get typed buffers. */
      /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      vSwUpdM_DataReadStreamPtrType readBuffer = vStreamProc_GetTypedReadRequestBuffer_uint8(&dataInputPort->ReadRequest);
      vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
      vSwUpdM_DataStreamPtrType writeBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataOutputPort->WriteRequest);

      /* #40 The smaller buffer determines the processing length. */
      length = VSWUPDM_PROCNODES_MIN(dataInputPort->ReadRequest.StorageInfo.AvailableLength, dataOutputPort->WriteRequest.StorageInfo.AvailableLength);

      if( length < dataInputPort->ReadRequest.StorageInfo.AvailableLength)
      {
        retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
      }

      /* #50 If length to be copied exceed announced length of range:
       *     Return error. */
      if ((Workspace->TotalLength + length) > (range->Length))
      {
        retVal = VSTREAMPROC_FAILED;
      }
      else
      {

        /* #60 Do work: Copy input to output. */
        vSwUpdM_Buffer_Copy(readBuffer, writeBuffer, length);

        /* #70 Return number of copied bytes. */
        (*Length) = length;

        /* #80 Acknowledge buffers.
         *     Do not Ack RangeInput, it will be consumed in FinalStep().
         */
        dataInputPort->ReadRequest.StorageInfo.RequestLength = length;
        rangeInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
        dataOutputPort->WriteRequest.StorageInfo.RequestLength = length;

        if(vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports) != VSTREAMPROC_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }


  return retVal;
} /* vSwUpdM_ProcNodePadding_Copy */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodePadding_FinalStep
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
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_FinalStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodePaddingWorkspacePtrType Workspace,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;
  vStreamProc_InputPortInfoPtrType entitiesInputPort = &Ports->InputPortInfos[Workspace->EntitiesInputPortId];
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[Workspace->RangeInputPortId];
  vStreamProc_OutputPortInfoPtrType resultingRangesOutputPort = &Ports->OutputPortInfos[Workspace->ResultingRangesOutputPortId];

  /* #10 Request expected minimum amount of data. */
  entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

  if (resultingRangesOutputPort->IsConnected == TRUE)
  {
    resultingRangesOutputPort->WriteRequest.StorageInfo.RequestLength = 2u;
  }
  else
  {
    resultingRangesOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;
  }

  retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);


  if (retVal == VSTREAMPROC_OK)
  {
    if (resultingRangesOutputPort->IsConnected == TRUE)
    {
      /* #20 Get typed buffers. */
      /* PRQA S 0310, 3305 3 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      vSwUpdM_PartitionIdType partitionId = (vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest))->PartitionId;
      vSwUpdM_RangeInfoReadStreamPtrType rangeInfo = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
      vSwUpdM_RangeInfoStreamPtrType alignedRangeInfoWrite = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&resultingRangesOutputPort->WriteRequest);

      /* #30 Do work:
       *     Calculate end address and padding. */
      vSwUpdM_AddressType endAddress = rangeInfo->Address + (Workspace->TotalLength - 1u);
      vSwUpdM_AddressType alignedAddress = endAddress;

      Workspace->PadLength = 0u;

      /* #31 Align end address to page boundary. */
      if (vSwUpdM_Range_AlignAddress(&alignedAddress, partitionId, VSWUPDM_ADDRESS_ALIGNMENT_BACK, VSWUPDM_ALIGN_GRANULARITY_PAGE) == E_OK)
      {
        /* #32 Calculate necessary padding at end of range. */
        Workspace->PadLength = alignedAddress - endAddress;

        /* Return aligned ranges. */
        /* #33 First range information holds address directly after last address with actual data
         *   and length of unpadded data. */
        alignedRangeInfoWrite[0u].Address = endAddress + 1u;
        alignedRangeInfoWrite[0u].Length = Workspace->TotalLength;
        /* #34 Second range information holds address directly after last padded address
         *   and length of data incl. trailing padding. */
        alignedRangeInfoWrite[1u].Address = alignedAddress + 1u;
        alignedRangeInfoWrite[1u].Length = Workspace->TotalLength + Workspace->PadLength;
      }
      else
      {
        retVal = VSTREAMPROC_FAILED;
      }
    }

    /* #40 Release buffers. */
    if (vSwUpdM_ProcNode_AcknowledgePorts(
      NodeInfo,
      Ports) != VSTREAMPROC_OK)
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_FinalStep */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeWrite_InitialStep
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
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_InitialStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo);

  /* #20 Request input and output port information. */
  vStreamProc_InputPortInfoPtrType entitiesInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_EntitiesInputPort];
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_RangeInputPort];
  vStreamProc_OutputPortInfoPtrType resultOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Write_ResultOutputPort];

  /* #30 Request entity, range and result ports. */
  entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  resultOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;

  retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #40 Get typed buffers. */
    /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
    vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);
    vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);

    /* #41 Store entities and range in workspace. */
    workspace->Entities = (*entities);
    workspace->Range = (*range);

    /* #42 Release buffers. */
    resultOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;

    retVal = vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    workspace->State = VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA;
    retVal = VSTREAMPROC_PENDING;
  }

  return retVal;
}
 /* vSwUpdM_ProcNodeWrite_InitialStep */

/**********************************************************************************************************************
 * vSwUpdM_ProcNode_SpawnJob
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
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_SpawnJob(
  vSwUpdM_JobTypeType JobType,
  vSwUpdM_EntityIdsReadStreamPtrType Entities,   /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
  vSwUpdM_AddressType TargetAddress,
  vSwUpdM_DataReadStreamPtrType InputBuffer,
  vSwUpdM_DataStreamPtrType OutputBuffer,
  vSwUpdM_LengthType ProcessingLength,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_NodeGroupIterType RemoteTargetGroup,
  P2VAR(vSwUpdM_LinkedResultType, AUTOMATIC, VSWUPDM_APPL_VAR) LinkedResult)
{
  Std_ReturnType      retVal;
  vSwUpdM_JobPtrType  spawnedJob;

  /* #10 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job to write data in write buffer. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, JobType, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, NULL_PTR, vSwUpdM_GetLocalNode());

  /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    /* #31 Pass entity IDs to write job and use target address to pass the current write address of the opened segment. */
    spawnedJob->EntityIds = (*Entities);
    spawnedJob->TargetAddress = TargetAddress;

    /* #32 Initialize write buffer to point to input and output data. */
    /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_WriteBufferConstCast */
    (void) vSwUpdM_Buffer_InitAndAddData(spawnedJob->InputBuffer, (vSwUpdM_VarDataPointerType)InputBuffer, ProcessingLength);

    if (spawnedJob->OutputBuffer != NULL_PTR)
    {
      /* #33 Initialize buffer information for output data, pointing to output buffer. */
      (void)vSwUpdM_Buffer_Init(spawnedJob->OutputBuffer, OutputBuffer, ProcessingLength);
    }

    spawnedJob->RemoteServiceIndex = RemoteServiceIndex;
    spawnedJob->RemoteTargetGroup = RemoteTargetGroup;

    /* #34 Set linked result of job to result in workspace. */
    vSwUpdM_Job_ResetLinkedResult(LinkedResult);
    vSwUpdM_Job_LinkResult(spawnedJob, LinkedResult);
  }

  /* #40 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}
/* vSwUpdM_ProcNode_SpawnJob */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeWrite_TriggerJob
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
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316, 3679 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr, MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vStreamProc_InputPortInfoPtrType dataInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_DataInputPort];

  /* #30 Get typed buffers. */
  vSwUpdM_DataReadStreamPtrType data = vStreamProc_GetTypedReadRequestBuffer_uint8(&Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_DataInputPort].ReadRequest);

  vSwUpdM_LengthType processingLength = dataInputPort->ReadRequest.StorageInfo.AvailableLength;

  /* #31 Calculate current address from range start address and total length from workspace. */
  vSwUpdM_AddressType address = workspace->Range.Address + workspace->TotalLength;

  /* #32 Limit processed input length to configured default segmentation. */
  processingLength = VSWUPDM_PROCNODES_MIN(processingLength, vSwUpdM_GetDefaultProcessingSegmentation());

  /* #33 Limit length of write operation to multiples of page size.
   *     If supported align length to burst boundaries, to increase chance that burst writes can be issued. */
  if (vSwUpdM_Range_TrimLength(&processingLength, workspace->Entities.PartitionId, address, VSWUPDM_ALIGN_GRANULARITY_PAGE, VSWUPDM_TRIM_TYPE_MAX) != E_OK)
  {
    retVal = VSTREAMPROC_FAILED;
  }

  /* #34 Check if there is any data to be written. */
  if (processingLength == 0u)
  {
    NodeInfo->InputPortResults[vStreamProcConf_External_vSwUpdM_Write_DataInputPort] = VSTREAMPROC_INSUFFICIENT_INPUT;

    /* This intentionally may overwrite an FAILED set as a result of a failed TrimLength(): */
    retVal = VSTREAMPROC_INSUFFICIENT_INPUT;
  }

  /* #40 Spawn job to write data in write buffer. */
  if (retVal == VSTREAMPROC_OK)
  {
    Std_ReturnType spawnResult = vSwUpdM_ProcNode_SpawnJob(
      VSWUPDM_JOB_TYPE_WRITE_DATA,
      &workspace->Entities,
      address,
      data,
      NULL_PTR,
      processingLength,
      VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED,
      VSWUPDM_INVALID_NODE_GROUP,
      &workspace->JobResult);

    if (spawnResult == E_OK)
    {
      retVal = VSTREAMPROC_PENDING;
      /* #41 Advance job state to wait for result of memory operation. */
      workspace->State = VSWUPDM_PROCNODESTATE_JOB_IS_PENDING;
      /* #42 Remember length of data to be written for later steps. */
      workspace->PendingLength = processingLength;
    }
    else
    {
      workspace->JobResult.Result = spawnResult;
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
}
/* vSwUpdM_ProcNodeWrite_TriggerJob */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeWrite_EvaluateJobResult
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
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;
  Std_ReturnType jobResult;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  vStreamProc_InputPortInfoPtrType dataInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_DataInputPort];

  /* #30 Evaluate result returned by write operation. */
  jobResult = vSwUpdM_Job_EvaluateResult(&workspace->JobResult);

  if (jobResult == E_OK)
  {
    /* #40 Consume input data. */
    workspace->TotalLength += workspace->PendingLength;
    dataInputPort->ReadRequest.StorageInfo.RequestLength = workspace->PendingLength;
    /* #50 If total written length covers complete requested range:
      *     Reset Node to initial state.
      */
    if (workspace->TotalLength >= workspace->Range.Length)
    {
      retVal = vSwUpdM_ProcNode_ResultOutput(NodeInfo, vStreamProcConf_External_vSwUpdM_Write_ResultOutputPort, jobResult);

      (void)vSwUpdM_ProcNodeWrite_Init(NodeInfo);
    }
    else
    {
      workspace->State = VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA;
      retVal = VSTREAMPROC_PENDING;
    }
  }
  else
  {
    /* #60 On negative result:
     *     Provide result to output port.
     *     Reset Node.
     *     return FAILED.
     */
    dataInputPort->ReadRequest.StorageInfo.RequestLength = 0u;

    (void)vSwUpdM_ProcNode_ResultOutput(NodeInfo, vStreamProcConf_External_vSwUpdM_Write_ResultOutputPort, jobResult);

    (void)vSwUpdM_ProcNodeWrite_Init(NodeInfo);

    retVal = VSTREAMPROC_FAILED;
  }



  return retVal;
}
/* vSwUpdM_ProcNodeWrite_EvaluateJobResult */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_DetermineRequestSizes
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
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_DetermineRequestSizes(
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports,
  boolean AddrLenIsWritten)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* #10 Request input and output port information. */
  vStreamProc_InputPortInfoPtrType rangeInputPort         = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_RangeInputPort];
  vStreamProc_InputPortInfoPtrType entitiesInputPort      = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_EntitiesInputPort];
  vStreamProc_OutputPortInfoPtrType addrLenDataOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort];
  vStreamProc_OutputPortInfoPtrType dataOutputPort        = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_DataOutputPort];
  vStreamProc_OutputPortInfoPtrType resultOutputPort      = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_ResultOutputPort];

  /* #20 Request minumum expected amount of data. */
  entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
  rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

  /* #30 If Read output is connected:
   *     Request it.*/
  if (dataOutputPort->IsConnected == TRUE)
  {
    dataOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;
  }

  /* #40 If AddrLen Output is connected:
   *     Request it. */
  if (addrLenDataOutputPort->IsConnected == TRUE)
  {
    if (AddrLenIsWritten == FALSE)
    {
      /* The Address, Length is added before the output of the read data.
        * This is done in one step, therefore enough space is required. */
      addrLenDataOutputPort->WriteRequest.StorageInfo.RequestLength = sizeof(vSwUpdM_AddressType) + sizeof(vSwUpdM_LengthType);
    }
    else
    {
      /* Otherwise:
        * At least one Byte must be available to execute a read. */
      addrLenDataOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;
    }
  }

  /* #50 At least one of both output ports must be connected. */
  if ((dataOutputPort->IsConnected == FALSE) && (addrLenDataOutputPort->IsConnected == FALSE))
  {
    retVal = VSTREAMPROC_FAILED;
  }

  /* #60 If Result output is connected:
   *     Request it. */
  if (resultOutputPort->IsConnected == TRUE)
  {
    resultOutputPort->WriteRequest.StorageInfo.RequestLength = 1u;
  }

  return retVal;
}
/* vSwUpdM_ProcNodeRead_DetermineRequestSizes */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_ProvideRangeOutput
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_ProvideRangeOutput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_RangeInputPort];
  vStreamProc_OutputPortInfoPtrType addrLenDataOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort];

 /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
  vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
  vSwUpdM_DataStreamPtrType addrLen = vStreamProc_GetTypedWriteRequestBuffer_uint8(&addrLenDataOutputPort->WriteRequest);

  vSwUpdM_ProcNodeRead_SerializeAddress(sizeof(vSwUpdM_AddressType), range->Address, addrLen);
  vSwUpdM_ProcNodeRead_SerializeAddress(sizeof(vSwUpdM_LengthType), range->Length, &addrLen[sizeof(vSwUpdM_AddressType)]);

  /* Update addrLen output port. */
  return vStreamProc_AcknowledgeOutputPort(NodeInfo, sizeof(vSwUpdM_AddressType) + sizeof(vSwUpdM_LengthType), FALSE, addrLenDataOutputPort);
}
/* vSwUpdM_ProcNodeRead_ProvideRangeOutput */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_TriggerJob
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
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadWorkspaceType(NodeInfo);

  /* #10 Request input and output port information. */
  vStreamProc_InputPortInfoPtrType rangeInputPort         = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_RangeInputPort];
  vStreamProc_InputPortInfoPtrType entitiesInputPort      = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_EntitiesInputPort];
  vStreamProc_OutputPortInfoPtrType addrLenDataOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort];
  vStreamProc_OutputPortInfoPtrType dataOutputPort        = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_DataOutputPort];
  vStreamProc_OutputPortInfoPtrType resultOutputPort      = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_ResultOutputPort];

  /* #20 Get typed buffers. */
  /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
  vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);
  vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);

  vSwUpdM_DataStreamPtrType outputBuffer = NULL_PTR;
  vSwUpdM_LengthType processingLength;

  /* #30 Determine processing length and select appropriate outputBuffer. */
  processingLength = range->Length - workspace->TotalLength;

  if (addrLenDataOutputPort->IsConnected == TRUE)
  {
    processingLength = VSWUPDM_PROCNODES_MIN(addrLenDataOutputPort->WriteRequest.StorageInfo.AvailableLength, processingLength);
    outputBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&addrLenDataOutputPort->WriteRequest);
  }

  if (dataOutputPort->IsConnected == TRUE)
  {
    processingLength = VSWUPDM_PROCNODES_MIN(dataOutputPort->WriteRequest.StorageInfo.AvailableLength, processingLength);

    /* If both outputs are connected, this one will be used for the ReadJob to output its data.
     * The other output will be filled later.
     */
    outputBuffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataOutputPort->WriteRequest);
  }

  /* #40 Limit read length to configured default segmentation. */
  processingLength = VSWUPDM_PROCNODES_MIN(processingLength, vSwUpdM_GetDefaultProcessingSegmentation());

  if (processingLength == 0u)
  {
    retVal = VSTREAMPROC_INSUFFICIENT_OUTPUT;
  }

  if (retVal == VSTREAMPROC_OK)
  {
    /* #50 Spawn job. */
    Std_ReturnType spawnResult = vSwUpdM_ProcNode_SpawnJob(
      VSWUPDM_JOB_TYPE_READ_DATA,
      entities,
      range->Address + workspace->TotalLength,
      NULL_PTR,
      outputBuffer,
      processingLength,
      VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED,
      VSWUPDM_INVALID_NODE_GROUP,
      &workspace->JobResult);

    if (spawnResult == E_OK)
    {
        /* #51 Remember length of data to be written for later steps. */
        workspace->PendingLength = processingLength;

        /* #52 Advance job state to wait for result of memory operation. */
        workspace->JobIsPending = TRUE;

        retVal = VSTREAMPROC_PENDING;

        /* Release inputs without consuming.
          * The requested output buffers are not acknowledged here intentionally. */
        entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
        rangeInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
        addrLenDataOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;
        addrLenDataOutputPort->WriteRequest.StorageInfo.ReleaseFlag = FALSE;
        dataOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;
        dataOutputPort->WriteRequest.StorageInfo.ReleaseFlag = FALSE;
        resultOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;
    }
    else /* #60 Otherwise: Report back error. */
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
}
/* vSwUpdM_ProcNodeRead_TriggerJob */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_ProcessData
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
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_ProcessData(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadWorkspaceType(NodeInfo);
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vStreamProc_OutputPortInfoPtrType addrLenDataOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort];

  /* #20 Request expected amount of data. */
  retVal = vSwUpdM_ProcNodeRead_DetermineRequestSizes(Ports, workspace->AddrLenIsWritten);

  if (retVal == VSTREAMPROC_OK)
  {
    retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    /* #30 If a read job is not yet started: */
    if (workspace->JobIsPending == FALSE)
    {
      /* #31 If addrLen output is connected:
       *     Write Addr, Len before payload data. */
      if ((addrLenDataOutputPort->IsConnected == TRUE) && (workspace->AddrLenIsWritten == FALSE))
      {
        retVal = vSwUpdM_ProcNodeRead_ProvideRangeOutput(NodeInfo, Ports);

        /* Remember that address and length are serialized into output buffer. */
        workspace->AddrLenIsWritten = TRUE;
      }

      /* #32 Spawn job to execute read. */
      if (retVal == VSTREAMPROC_OK)
      {
        retVal = vSwUpdM_ProcNodeRead_TriggerJob(NodeInfo, Ports);
      }
    }
    else /* #40 Otherwise:
          * Evaluate results. */
    {
      retVal = vSwUpdM_ProcNodeRead_EvaluateJobResult(NodeInfo, Ports);

    }
    /* Acknowledge the requested buffers. */
    if (vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports) != VSTREAMPROC_OK)
    {
      retVal = VSTREAMPROC_FAILED;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRead_EvaluateJobResult
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
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;
  Std_ReturnType jobResult;

  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadWorkspaceType(NodeInfo);

  /* #10 Request input and output port information. */
  vStreamProc_InputPortInfoPtrType rangeInputPort         = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_RangeInputPort];
  vStreamProc_InputPortInfoPtrType entitiesInputPort      = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Read_EntitiesInputPort];
  vStreamProc_OutputPortInfoPtrType addrLenDataOutputPort = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_AddrLenDataOutputPort];
  vStreamProc_OutputPortInfoPtrType dataOutputPort        = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_DataOutputPort];
  vStreamProc_OutputPortInfoPtrType resultOutputPort      = &Ports->OutputPortInfos[vStreamProcConf_External_vSwUpdM_Read_ResultOutputPort];

  /* Get typed buffer. */
  /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
  vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);

  /* #20 Evaluate result returned by read operation. */
  jobResult = vSwUpdM_Job_EvaluateResult(&workspace->JobResult);

  /* #30 output result. */
  if (resultOutputPort->IsConnected == TRUE)
  {
    vSwUpdM_ReturnStreamPtrType result = vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&resultOutputPort->WriteRequest);
    (*result) = jobResult;
  }

  /* #40 On success: */
  if (jobResult == E_OK)
  {
    vSwUpdM_LengthType pendingLength = workspace->PendingLength;

    /* #41 Update total length for next read. */
    workspace->TotalLength += pendingLength;

    /* #42 If both output ports are connected:
      *   Copy read data to second port as well. */
    if ((dataOutputPort->IsConnected == TRUE) && (addrLenDataOutputPort->IsConnected == TRUE))
    {
      vSwUpdM_DataStreamPtrType addrLen = vStreamProc_GetTypedWriteRequestBuffer_uint8(&addrLenDataOutputPort->WriteRequest);
      vSwUpdM_DataReadStreamPtrType data = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataOutputPort->WriteRequest);

      vSwUpdM_Buffer_Copy(data, addrLen, pendingLength);
    }

    if (addrLenDataOutputPort->IsConnected == TRUE)
    {
      addrLenDataOutputPort->WriteRequest.StorageInfo.RequestLength = pendingLength;
    }
    if (dataOutputPort->IsConnected == TRUE)
    {
      dataOutputPort->WriteRequest.StorageInfo.RequestLength = pendingLength;
    }

    /* #43 If total read length covers complete requested range:
     *     Got to initial state. */
    if (workspace->TotalLength >= range->Length)
    {
      (void)vSwUpdM_ProcNodeRead_Init(NodeInfo);
    }
    else
    {
      /* #44 Otherwise:
       *  Produce output data but do not provide result nor consume entities or range. */
      entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 0;
      rangeInputPort->ReadRequest.StorageInfo.RequestLength = 0;
      resultOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;

      workspace->JobIsPending = FALSE;
      retVal = VSTREAMPROC_PENDING;
    }
  }
  else /* #50 Otherwise: ReadJob has returned with an error. */
  {
    entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
    rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
    dataOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;
    addrLenDataOutputPort->WriteRequest.StorageInfo.RequestLength = 0u;

      /* #51 Report result. */

    /* #52 Reset Node to initial state. */
    (void)vSwUpdM_ProcNodeRead_Init(NodeInfo);

    retVal = VSTREAMPROC_FAILED;
  }

  return retVal;
}
/* vSwUpdM_ProcNodeRead_EvaluateJobResult */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeTrackCompareProgress_ProcessData
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
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_ProcessData(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeTrackCompareProgressWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeTrackCompareProgressWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  vStreamProc_InputPortInfoPtrType countInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_TrackCompareProgress_CountInputPort];
  vStreamProc_InputPortInfoPtrType entitiesInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_TrackCompareProgress_EntitiesInputPort];
  vStreamProc_InputPortInfoPtrType rangeInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_RangeInputPort];

  vSwUpdM_DataReadStreamPtrType      count = vStreamProc_GetTypedReadRequestBuffer_uint8(&countInputPort->ReadRequest);
  /* PRQA S 0310, 3305 2 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
  vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);
  vSwUpdM_RangeInfoReadStreamPtrType range = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&rangeInputPort->ReadRequest);

  vSwUpdM_VarSegmentsPtrType  segment = vSwUpdM_GetAddrVarSegments(entities->SegmentId.DynamicSegmentId);
  uint32_least                index;
  vSwUpdM_LengthType          totalCount = 0u;

  if (workspace->FirstCall == TRUE)
  {
    /* #30 Calculate length of leading data which was already compared on a previous cycle. */
    workspace->PendingLength = segment->WriteAddressOfVarSegments - range->Address;

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
    /* #40 If fine-grained resume is enabled:
     *   Search next checkpoint behind current segment (write) address. */
    vSwUpdM_ResumeInfo_GetCheckpointAddress(&workspace->CheckpointAddress, segment->WriteAddressOfVarSegments, entities->PartitionId);
#endif
  }

  /* #50 Sum up all input counts. */
  for (index = 0u; index < countInputPort->ReadRequest.StorageInfo.AvailableLength; index++)
  {
    /* #51 The transferred value has an offset of 1 to use the available value range efficiently.
      * A value of 0 indicates a number of 1 bytes. Otherwise, a value of 0 would not make sense. */
    totalCount += (vSwUpdM_LengthType)count[index] + 1u;
  }

  /* #60 All available input data is consumed at this input. */
  countInputPort->ReadRequest.StorageInfo.RequestLength = countInputPort->ReadRequest.StorageInfo.AvailableLength;

  /* #70 Update total length in workspace. */
  workspace->TotalLength += totalCount;

  /* #80 If no leading data is left: */
  if (workspace->PendingLength < totalCount)
  {
    /* #81 Now the start of the uncompared data is reached. Update the WriteAddress from here. */
    workspace->UpdateWriteAddress = TRUE;

    /* #82 Clear remaining leading data length. */
    workspace->PendingLength = 0u;
  }
  /* #90 Otherwise: Decrement remaining leading data by total count. */
  else
  {
    workspace->PendingLength -= totalCount;
  }

  /* #100 If UpdateWriteAddress flag is set:
   *     Keep track of current address in segment (write) address. */
  if (workspace->UpdateWriteAddress == TRUE)
  {
    vSwUpdM_AddressType nextAddress = range->Address + workspace->TotalLength;

    (void)vSwUpdM_Segment_UpdateWriteAddress(segment, nextAddress);
  }
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
  /* #110 If fine-grained resume is enabled and comparison crossed the current checkpoint: */
  if ((workspace->TotalLength >= range->Length)  /* If complete announced range was compared */
    || (segment->WriteAddressOfVarSegments >= workspace->CheckpointAddress)) /* Or Checkpoint was hit: */
  {
      /* #111 Trigger persisting of address (located in current segment). */
    (void)vSwUpdM_Segment_PersistState(entities, VSWUPDM_SID_NONE, FALSE, NULL_PTR, vSwUpdM_GetLocalNode());
    /* #112 Search next checkpoint behind current segment (write) address. */
    vSwUpdM_ResumeInfo_GetCheckpointAddress(&workspace->CheckpointAddress, segment->WriteAddressOfVarSegments, entities->PartitionId);
  }
#endif

  if (workspace->TotalLength < range->Length)
  {
    /* Do not consume Entities and Range yet. */
    entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
    rangeInputPort->ReadRequest.StorageInfo.RequestLength = 0u;
  }
  else
  {
    /* #120 Now the node is able to consume another range. */
    (void)vSwUpdM_ProcNodeTrackCompareProgress_Init(NodeInfo);
  }

  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
}
/* vSwUpdM_ProcNodeTrackCompareProgress_ProcessData */

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRemote_InitialStep
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
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_InitialStep(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports)
{
  vStreamProc_ReturnType retVal;
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  vStreamProc_InputPortInfoPtrType entitiesInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Remote_EntitiesInputPort];

  /* #30 Request Entity and Result Ports */
  entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

  retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, Ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* Get typed buffers. */
    /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
    vSwUpdM_EntityIdsReadStreamPtrType entities = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_EntityIdsType(&entitiesInputPort->ReadRequest);

    /* #40 Store entities and range in workspace. */
    workspace->Entities = (*entities);

    /* #50 Acknowledge entities. */
    retVal = vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, Ports);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    workspace->State = VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA;
    retVal = VSTREAMPROC_PENDING;
  }

  return retVal;
}
/* vSwUpdM_ProcNodeRemote_InitialStep */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRemote_TriggerJob
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
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_TriggerJob(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */)
{
  vStreamProc_ReturnType retVal;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  /* PRQA S 3679 1 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vStreamProc_InputPortInfoPtrType dataInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Remote_DataInputPort];

  /* Get typed buffers. */
  vSwUpdM_DataReadStreamPtrType data = vStreamProc_GetTypedReadRequestBuffer_uint8(&dataInputPort->ReadRequest);

  /* #30 Limit processed input length to configured remote segmentation. */
  vSwUpdM_LengthType processingLength = VSWUPDM_PROCNODES_MIN(dataInputPort->ReadRequest.StorageInfo.AvailableLength, vSwUpdM_GetRemoteProcessingSegmentation());

  vSwUpdM_RegionIdxType regionIdx = vSwUpdM_GetVarSegments(workspace->Entities.SegmentId.DynamicSegmentId).RegionIdxOfVarSegments;
  Std_ReturnType spawnResult = vSwUpdM_ProcNode_SpawnJob(
    VSWUPDM_JOB_TYPE_REMOTE_PROCESS_STREAM_DATA,
    &workspace->Entities,
    0u,
    (vSwUpdM_VarDataPointerType)data, /* PRQA S 0311 1 */ /* MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues */
    NULL_PTR,
    processingLength,
    VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA,
    vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(regionIdx).RegionIDOfVarRegions),
    &workspace->JobResult);

  if (spawnResult == E_OK)
  {
    /* #40 Advance job state to wait for result of memory operation. */
    workspace->State = VSWUPDM_PROCNODESTATE_JOB_IS_PENDING;

    /* #50 Remember length of data to be written for later steps. */
    workspace->PendingLength = processingLength;

    retVal = VSTREAMPROC_PENDING;
  }
  else
  {
    workspace->JobResult.Result = spawnResult;
    retVal = VSTREAMPROC_FAILED;
  }
  return retVal;
}
/* vSwUpdM_ProcNodeRemote_TriggerJob */

/**********************************************************************************************************************
 * vSwUpdM_ProcNodeRemote_EvaluateJobResult
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
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_EvaluateJobResult(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */)
{
  vStreamProc_ReturnType retVal;
  Std_ReturnType jobResult;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);

  /* #20 Request input port information. */
  vStreamProc_InputPortInfoPtrType dataInputPort = &Ports->InputPortInfos[vStreamProcConf_External_vSwUpdM_Remote_DataInputPort];

  /* #30 Evaluate result returned by write operation. */
  jobResult = vSwUpdM_Job_EvaluateResult(&workspace->JobResult);

  if (jobResult == E_OK)
  {
    dataInputPort->ReadRequest.StorageInfo.RequestLength = workspace->PendingLength;
    workspace->State = VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA;
    retVal = VSTREAMPROC_PENDING;

  }
  else
  {
    /* #40 On error:
     * Return error. */
    dataInputPort->ReadRequest.StorageInfo.RequestLength = 0u;

    (void) vSwUpdM_ProcNode_ResultOutput(NodeInfo, vStreamProcConf_External_vSwUpdM_Remote_ResultOutputPort, jobResult);

    retVal = VSTREAMPROC_FAILED;
  }

  return retVal;
}
/* vSwUpdM_ProcNodeRemote_EvaluateJobResult */
#endif

/**********************************************************************************************************************
 * vSwUpdM_ProcNode_ResultOutput
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_ResultOutput(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  Std_ReturnType Result)
{
  vStreamProc_ReturnType retVal;
  vStreamProc_OutputPortInfoType resultOutputPort;

  retVal = vStreamProc_PrepareOutputPortInfo(NodeInfo, SymbolicNameOfOutputPort, &resultOutputPort);

  if (retVal == VSTREAMPROC_OK)
  {
    retVal = vStreamProc_RequestOutputPortData(NodeInfo, vStreamProcConf_vStreamProcDataType_Std_ReturnType, 1u, &resultOutputPort);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    vSwUpdM_ReturnStreamPtrType result = vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&resultOutputPort.WriteRequest);

    (*result) = Result;

    resultOutputPort.WriteRequest.StorageInfo.RequestLength = 1u;

    retVal = vStreamProc_AcknowledgeOutputPort(NodeInfo, 1u, TRUE, &resultOutputPort);
  }

  return retVal;

} /* vSwUpdM_ProcNode_ResultOutput */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * vSwUpdM_ProcNode_PreparePorts
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_PreparePorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */)
{
  vStreamProc_InputPortIdType inputPortIter;
  vStreamProc_OutputPortIdType outputPortIter;
  vStreamProc_ReturnType retVal;

  /* #10 Prepare all ports. */
  retVal = vStreamProc_PrepareAllPortInfos(
    NodeInfo,
    Ports->InputPortInfos,
    Ports->InputPortCount,
    Ports->OutputPortInfos,
    Ports->OutputPortCount);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Prepare all input data types. */
    for (inputPortIter = 0; inputPortIter < Ports->InputPortCount; inputPortIter++)
    {
      vStreamProc_InputPortIdType PortId   = Ports->InputPortDatatypes[inputPortIter].PortId;
      vStreamProc_DataTypeIdType  PortType = Ports->InputPortDatatypes[inputPortIter].PortType;
      Ports->InputPortInfos[PortId].ReadRequest.StorageInfo.DataTypeInfo.Id = PortType;
    }

    /* #30 Prepare all output data types. */
    for (outputPortIter = 0; outputPortIter < Ports->OutputPortCount; outputPortIter++)
    {
      vStreamProc_OutputPortIdType PortId   = Ports->OutputPortDatatypes[outputPortIter].PortId;
      vStreamProc_DataTypeIdType   PortType = Ports->OutputPortDatatypes[outputPortIter].PortType;
      Ports->OutputPortInfos[PortId].WriteRequest.StorageInfo.DataTypeInfo.Id = PortType;
    }

    /* #40 Check data types */
    retVal = vStreamProc_GetPortInfos(
      NodeInfo,
      Ports->InputPortInfos,
      Ports->InputPortCount,
      Ports->OutputPortInfos,
      Ports->OutputPortCount);
  }

  return retVal;
}
/* vSwUpdM_ProcNode_PreparePorts */

/**********************************************************************************************************************
 * vSwUpdM_ProcNode_RequestPorts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_RequestPorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  return vStreamProc_RequestPortData(
    NodeInfo,
    Ports->InputPortInfos,
    Ports->InputPortCount,
    Ports->OutputPortInfos,
    Ports->OutputPortCount);
}
/* vSwUpdM_ProcNode_RequestPorts */

/**********************************************************************************************************************
 * vSwUpdM_ProcNode_AcknowledgePorts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNode_AcknowledgePorts(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo,
  vSwUpdM_ProcNodesPortsCollectionPtrType Ports) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  return vStreamProc_AcknowledgePorts(
    NodeInfo,
    Ports->InputPortInfos,
    Ports->InputPortCount,
    Ports->OutputPortInfos,
    Ports->OutputPortCount);
}
/* vSwUpdM_ProcNode_RequestPorts */

/**********************************************************************************************************************
 * PROCESSING NODE: PADDING
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodePaddingWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize flag for first call and reset total length in workspace. */
  workspace->State = VSWUPDM_PADDING_NODE_STATE_INITIAL;
  workspace->TotalLength = 0u;

  /* #30 Initialize input/output port references in workspace. */
  workspace->DataInputPortId =             vStreamProcConf_External_vSwUpdM_Padding_DataInputPort;
  workspace->EntitiesInputPortId =         vStreamProcConf_External_vSwUpdM_Padding_EntitiesInputPort;
  workspace->RangeInputPortId =            vStreamProcConf_External_vSwUpdM_Padding_RangeInputPort;
  workspace->AlignedRangeOutputPortId =    vStreamProcConf_External_vSwUpdM_Padding_AlignedRangeOutputPort;
  workspace->DataOutputPortId =            vStreamProcConf_External_vSwUpdM_Padding_DataOutputPort;
  workspace->ResultingRangesOutputPortId = vStreamProcConf_External_vSwUpdM_Padding_ResultingRangesOutputPort;

  return E_OK;
} /* vSwUpdM_ProcNodePadding_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType  retVal;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316, 3679 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr, MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ProcNodePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodePaddingWorkspaceType(NodeInfo);

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_Padding];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_Padding];

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_PaddingNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_Padding,
    NULL_PTR,
    vSwUpdM_ProcNodes_PaddingNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_Padding
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Prepare inputs and outputs. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
    NodeInfo,
    &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #30 Call internal function. */
    retVal = vSwUpdM_ProcNodePadding_ProcessInternal(NodeInfo, workspace, &ports);
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodePadding_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodePadding_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodePaddingWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodePaddingWorkspaceType(NodeInfo);

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_Padding];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_Padding];

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_PaddingNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_Padding,
    NULL_PTR,
    vSwUpdM_ProcNodes_PaddingNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_Padding
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Prepare inputs and outputs. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
  NodeInfo,
  &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #30 Call internal function. */
    retVal = vSwUpdM_ProcNodePadding_FlushInternal(NodeInfo, workspace, &ports);
  }

  return retVal;
} /* vSwUpdM_ProcNodePadding_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: WRITE
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize state and reset total length in workspace. */
  workspace->State = VSWUPDM_PROCNODESTATE_INITIAL;
  workspace->TotalLength  = 0u;

  /* #30 Reset job result in workspace. */
  vSwUpdM_Job_ResetLinkedResult(&workspace->JobResult);

  return E_OK;
} /* vSwUpdM_ProcNodeWrite_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Process
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
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
 /* ----- Local Variables ---------------------------------------------- */
    /* PRQA S 3679 2 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vStreamProc_ReturnType retVal = VSTREAMPROC_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vStreamProc_InputPortInfoPtrType dataInputPort;

  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_Write];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_Write];

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_WriteNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_Write,
    NULL_PTR,
    vSwUpdM_ProcNodes_WriteNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_Write
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* #20 Request input port information. */
  dataInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_DataInputPort];

  /* ----- Implementation ----------------------------------------------- */
  /* #30 Prepare requests. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
    NodeInfo,
    &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #100 Evaluate State. */
    switch (workspace->State)
    {
      case VSWUPDM_PROCNODESTATE_INITIAL:
      /* #110 Wait for any input data.
       *      If any data is received go to next state. Now the node can not be
       *      flushed without processing anymore.
       */
      {
        if (vSwUpdM_ProcNode_IsInputDataAvailable(
          ports.InputPortInfos,
          ports.InputPortCount) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          workspace->State = VSWUPDM_PROCNODESTATE_INITIAL_STEP;
          retVal = VSTREAMPROC_PENDING;
        }
        break;
      }
      case VSWUPDM_PROCNODESTATE_INITIAL_STEP:
      /* #120 Wait for input data and do initial step:
       *     Read Entities and Range input into workspace.
       */
      {
        retVal = vSwUpdM_ProcNodeWrite_InitialStep(NodeInfo, &ports);
        break;
      }
      case VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA:
      /*   #130 If data available: */
      {
        if (dataInputPort->ReadRequest.StorageInfo.AvailableLength > 0u)
        {
          /* #131 Request input data. */
          dataInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
          retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, &ports);

          /* #132 Trigger job. */
          if (retVal == VSTREAMPROC_OK)
          {
            retVal = vSwUpdM_ProcNodeWrite_TriggerJob(NodeInfo, &ports);
          }
        }
        else
        {
          retVal = VSTREAMPROC_OK;
        }
        break;
      }
      case VSWUPDM_PROCNODESTATE_JOB_IS_PENDING:
      /* #140 Evaluate job result. */
      {
        retVal = vSwUpdM_ProcNodeWrite_EvaluateJobResult(NodeInfo, &ports);

        /* #141 Acknowledge input data. */
        if (vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, &ports) != VSTREAMPROC_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }

        break;
      }
      default:
      {
        retVal = VSTREAMPROC_FAILED;
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_ProcNodeWrite_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeWrite_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeWrite_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeWriteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeWriteWorkspaceType(NodeInfo);
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* #10 Trigger normal processing operation. */
  if (workspace->State != VSWUPDM_PROCNODESTATE_INITIAL)
  {
    retVal = vSwUpdM_ProcNodeWrite_Process(NodeInfo);
  }

  if (retVal == VSTREAMPROC_OK)
  {
    if (workspace->State == VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA)
    {
      Std_ReturnType jobResult;

      /* #20 Evaluate result returned by write operation. */
      jobResult = vSwUpdM_Job_EvaluateResult(&workspace->JobResult);

      retVal = vSwUpdM_ProcNode_ResultOutput(NodeInfo, vStreamProcConf_External_vSwUpdM_Write_ResultOutputPort, jobResult);

      /* #30 Reset Node to initial state. */
      (void)vSwUpdM_ProcNodeWrite_Init(NodeInfo);
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodeWrite_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: READ
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeReadWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeReadWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize flags and reset total length in workspace. */
  workspace->JobIsPending = FALSE;
  workspace->AddrLenIsWritten = FALSE;
  workspace->TotalLength  = 0u;

  /* #30 Reset job result in workspace. */
  vSwUpdM_Job_ResetLinkedResult(&workspace->JobResult);

  return E_OK;
} /* vSwUpdM_ProcNodeRead_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;   /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_Read];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_Read];
  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_ReadNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_Read,
    NULL_PTR,
    vSwUpdM_ProcNodes_ReadNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_Read
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Prepare requests. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
    NodeInfo,
    &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #20 Evaluate if any input data is available: */
    if (vSwUpdM_ProcNode_IsInputDataAvailable(ports.InputPortInfos, ports.InputPortCount) == FALSE)
    {
      /* No input data available: Node is idle. */
    }
    else
    {
      /* #30 Process read request. */
      retVal = vSwUpdM_ProcNodeRead_ProcessData(NodeInfo, &ports);
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodeRead_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRead_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRead_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;  /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Trigger normal processing operation. */
  retVal = vSwUpdM_ProcNodeRead_Process(NodeInfo);

  return retVal;
} /* vSwUpdM_ProcNodeRead_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: TRACK COMPARE PROGRESS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeTrackCompareProgressWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeTrackCompareProgressWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize state and reset total length in workspace. */
  workspace->FirstCall          = TRUE;
  workspace->UpdateWriteAddress = 0u;
  workspace->TotalLength  = 0u;

  return E_OK;
} /* vSwUpdM_ProcNodeTrackCompareProgress_Init */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Process
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 1 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vStreamProc_ReturnType retVal = VSTREAMPROC_PENDING;

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_TrackCompareProgress];
  vStreamProc_InputPortInfoPtrType countInputPort;
  vStreamProc_InputPortInfoPtrType entitiesInputPort;
  vStreamProc_InputPortInfoPtrType rangeInputPort;

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_TrackCompareProgressNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_TrackCompareProgress,
    NULL_PTR,
    vSwUpdM_ProcNodes_TrackCompareProgressNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_TrackCompareProgress
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = NULL_PTR;

  /* #10 Request input and output port information. */
  countInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_TrackCompareProgress_CountInputPort];
  entitiesInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_TrackCompareProgress_EntitiesInputPort];
  rangeInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_Write_RangeInputPort];

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Prepare requests. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
    NodeInfo,
    &ports);

  if (retVal == VSTREAMPROC_OK)
  {
   /* #30 Evaluate if any input data is available: */
    if (vSwUpdM_ProcNode_IsInputDataAvailable(ports.InputPortInfos, ports.InputPortCount) == FALSE)
    {
      /* #31 No input data available: Node is idle. */
    }
    else
    {
      /* #40 Request expected amount of data. */
      countInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
      entitiesInputPort->ReadRequest.StorageInfo.RequestLength = 1u;
      rangeInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

      retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, &ports);

      if (retVal == VSTREAMPROC_OK)
      {
        /* #50 Do processing. */
        vSwUpdM_ProcNodeTrackCompareProgress_ProcessData(NodeInfo, &ports);

        if (vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, &ports) != VSTREAMPROC_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
      }
    }
  }

  return retVal;

} /* vSwUpdM_ProcNodeTrackCompareProgress_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeTrackCompareProgress_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeTrackCompareProgress_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
    /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;  /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  /* ----- Implementation ----------------------------------------------- */
  retVal = vSwUpdM_ProcNodeTrackCompareProgress_Process(NodeInfo);

  return retVal;
} /* vSwUpdM_ProcNodeTrackCompareProgress_Flush */

/**********************************************************************************************************************
 * PROCESSING NODE: REMOTE
 *********************************************************************************************************************/

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Init(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Infer the specialized workspace from the processing node. */
    /* PRQA S 0316 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Initialize state. */
  workspace->State = VSWUPDM_PROCNODESTATE_INITIAL;

  /* #30 Reset job result in workspace. */
  vSwUpdM_Job_ResetLinkedResult(&workspace->JobResult);

  return E_OK;
} /* vSwUpdM_ProcNodeRemote_Init */

/***********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Process
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
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Process(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal;
  /* #10 Infer the specialized workspace from the processing node. */
  /* PRQA S 0316, 3679 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr, MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);

  vStreamProc_InputPortInfoType    inputPortInfos[vStreamProcConf_InputPortCount_External_vSwUpdM_Remote];
  vStreamProc_OutputPortInfoType   outputPortInfos[vStreamProcConf_OutputPortCount_External_vSwUpdM_Remote];
  vStreamProc_InputPortInfoPtrType dataInputPort;

  vSwUpdM_ProcNodesPortsCollectionType ports =
  {
    NULL_PTR,
    vSwUpdM_ProcNodes_RemoteNodePortsConfig_InputPortDatatype,
    vStreamProcConf_InputPortCount_External_vSwUpdM_Remote,
    NULL_PTR,
    vSwUpdM_ProcNodes_RemoteNodePortsConfig_OutputPortDatatype,
    vStreamProcConf_OutputPortCount_External_vSwUpdM_Remote
  };
  ports.InputPortInfos = inputPortInfos;
  ports.OutputPortInfos = outputPortInfos;

  /* #20 Request input port information. */
  dataInputPort = &ports.InputPortInfos[vStreamProcConf_External_vSwUpdM_Remote_DataInputPort];

  /* ----- Implementation ----------------------------------------------- */
  /* #30 Prepare requests. */
  retVal = vSwUpdM_ProcNode_PreparePorts(
  NodeInfo,
  &ports);

  if (retVal == VSTREAMPROC_OK)
  {
    /* #100 Evaluate State. */
    switch (workspace->State)
    {
      case VSWUPDM_PROCNODESTATE_INITIAL:
      {
        /* #110 Wait for any input data.
         *      If any data is received go to next state. Now the node can not be
         *      flushed without processing anymore.
         */
        if (vSwUpdM_ProcNode_IsInputDataAvailable(
          ports.InputPortInfos,
          ports.InputPortCount) == FALSE)
        {
          /* No input data available: Node is idle. */
        }
        else
        {
          workspace->State = VSWUPDM_PROCNODESTATE_INITIAL_STEP;
          retVal = VSTREAMPROC_PENDING;
        }
        break;
      }
      case VSWUPDM_PROCNODESTATE_INITIAL_STEP:
      /* #120 Wait for input data and do initial step:
       *          Read Entities and Range input into workspace.
       */
      {
        retVal = vSwUpdM_ProcNodeRemote_InitialStep(NodeInfo, &ports);
        break;
      }
      case VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA:
      {
        /* #130 If data available:
         *      Trigger job.
         */
        if (dataInputPort->ReadRequest.StorageInfo.AvailableLength > 0u)
        {
          /* Request expected minimum amount of data. */
          dataInputPort->ReadRequest.StorageInfo.RequestLength = 1u;

          retVal = vSwUpdM_ProcNode_RequestPorts(NodeInfo, &ports);

          if (retVal == VSTREAMPROC_OK)
          {
            retVal = vSwUpdM_ProcNodeRemote_TriggerJob(NodeInfo, &ports);

            /* Requested port is intentionally not acknowledged here.
             * The job will use the provided data buffer in the background.
             */
          }
        }
        break;
      }
      case VSWUPDM_PROCNODESTATE_JOB_IS_PENDING:
      /* #140 Evaluate job result. */
      {
        retVal = vSwUpdM_ProcNodeRemote_EvaluateJobResult(NodeInfo, &ports);

        if (vSwUpdM_ProcNode_AcknowledgePorts(NodeInfo, &ports) != VSTREAMPROC_OK)
        {
          retVal = VSTREAMPROC_FAILED;
        }
        break;
      }
      default:
      {
        retVal = VSTREAMPROC_FAILED;

        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_ProcNodeRemote_Process */

/**********************************************************************************************************************
 *  vSwUpdM_ProcNodeRemote_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcNodeRemote_Flush(
  vSwUpdM_ProcNodeInfoPtrType NodeInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 0316, 3679 1 */ /* MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr, MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ProcNodeRemoteWorkspacePtrType workspace = vStreamProc_GetTypedWorkspaceOfProcessingNode_vSwUpdM_ProcNodeRemoteWorkspaceType(NodeInfo);
  vStreamProc_ReturnType retVal = VSTREAMPROC_OK;

  /* #10 Trigger normal processing operation. */
  if (workspace->State != VSWUPDM_PROCNODESTATE_INITIAL)
  {
    retVal = vSwUpdM_ProcNodeRemote_Process(NodeInfo);
  }
  else
  {
    if (workspace->State == VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA)
    {
      Std_ReturnType jobResult;

      /* #20 Evaluate result returned by write operation. */
      jobResult = vSwUpdM_Job_EvaluateResult(&workspace->JobResult);

      retVal = vSwUpdM_ProcNode_ResultOutput(NodeInfo, vStreamProcConf_External_vSwUpdM_Remote_ResultOutputPort, jobResult);

      /* #30 Reset Node to initial state. */
      (void) vSwUpdM_ProcNodeRemote_Init(NodeInfo);
    }
  }

  return retVal;
} /* vSwUpdM_ProcNodeRemote_Flush */
#endif

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_ProcNodes.c
 *********************************************************************************************************************/
