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
/*!        \file  vStreamProc_Port.h
 *        \brief  vStreamProc processing node header types header file
 *
 *      \details  Definition of all relevant types for vStreamProc processing nodes
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
#ifndef VSTREAMPROC_PORT_H
#define VSTREAMPROC_PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallReadInfoOfStorageNode(inStorageNodeIdx, storageInfo, outputPortIdx) \
    vStreamProc_GetReadInfoOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(inStorageNodeIdx))(inStorageNodeIdx, storageInfo, outputPortIdx)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallReadRequestOfStorageNode(inStorageNodeIdx, readRequestPtr, outputPortIdx) \
    vStreamProc_GetReadRequestOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(inStorageNodeIdx))(inStorageNodeIdx, readRequestPtr, outputPortIdx)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallReadAckOfStorageNode(inStorageNodeIdx, consumedLen, outputPortIdx) \
    vStreamProc_GetReadAckOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(inStorageNodeIdx))(inStorageNodeIdx, consumedLen, outputPortIdx)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallWriteInfoOfStorageNode(outStorageNodeIdx, storageInfo) \
    vStreamProc_GetWriteInfoOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(outStorageNodeIdx))(outStorageNodeIdx, storageInfo)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallWriteRequestOfStorageNode(outStorageNodeIdx, writeRequestPtr) \
    vStreamProc_GetWriteRequestOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(outStorageNodeIdx))(outStorageNodeIdx, writeRequestPtr)

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define vStreamProc_CallWriteAckOfStorageNode(outStorageNodeIdx, requestedLen) \
    vStreamProc_GetWriteAckOfStorageNodeDef(vStreamProc_GetStorageNodeDefIdxOfStorageNode(outStorageNodeIdx))(outStorageNodeIdx, requestedLen)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSTREAMPROC_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /*  MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_InitProcessingNodeInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize node information structure.
 * \details       -
 * \param[in]     ProcessingNodeId  Id of a processing node.
 * \param[out]    InputPortResults  Array for input port specific results.
 * \param[out]    OuputPortResults  Array for output port specific results.
 * \param[in]     NodeInfo          The processing node information to be initialized.
 * \pre           Arrays for port specific results must be big enough.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_InitProcessingNodeInfo(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_DATA) InputPortResults,
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_DATA) OutputPortResults,
  P2VAR(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetInputPortHandle()
 *********************************************************************************************************************/
/*!
 * \brief         Fetches the output port of a storage node that is connected to the passed named input port.
 * \details       Additionally evaluates whether an (optional) port is currently connected.
 * \param[in]     ProcessingNodeId          The processing node's ID.
 * \param[in]     SymbolicNameOfInputPort   A named input port of the processing node.
 * \param[out]    InputPortHandle           The port handle of the named input port.
 * \param[out]    IsConnected               TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK            If the passed symbolic port name could be resolved.
 * \return        VSTREAMPROC_FAILED        If the passed symbolic port name could not be resolved.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, AUTOMATIC) vStreamProc_GetInputPortHandle(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  vStreamProc_InputPortSymbolicNameType SymbolicNameOfInputPort,
  P2VAR(vStreamProc_InputPortHandleType, AUTOMATIC, VSTREAMPROC_APPL_DATA) InputPortHandle,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) IsConnected);

/**********************************************************************************************************************
 *  vStreamProc_GetOutputPortHandle()
 *********************************************************************************************************************/
/*!
 * \brief         Fetches the storage node that is connected to the passed named output port.
 * \details       Additionally evaluates whether an (optional) port is currently connected.
 * \param[in]     ProcessingNodeId          The processing node's ID.
 * \param[in]     SymbolicNameOfOutputPort  A named output port of the processing node.
 * \param[out]    OutputPortHandle          The port handle of the named output port.
 * \param[out]    IsConnected               TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK            If the passed symbolic port name could be resolved.
 * \return        VSTREAMPROC_FAILED        If the passed symbolic port name could not be resolved.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, AUTOMATIC) vStreamProc_GetOutputPortHandle(
  vStreamProc_ProcessingNodeIdType ProcessingNodeId,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  P2VAR(vStreamProc_OutputPortHandleType, AUTOMATIC, VSTREAMPROC_APPL_DATA) OutputPortHandle,
  P2VAR(boolean, AUTOMATIC, VSTREAMPROC_APPL_DATA) IsConnected);

/**********************************************************************************************************************
 *  vStreamProc_GetTypedWorkspaceOfProcessingNode()
 *********************************************************************************************************************/
/*!
 * \brief         Get the pointer to the workspace of a processing node.
 * \details       Returns the pointer to the workspace, while performing a DET check against the
 *                expected workspace type.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     WorkspaceTypeId   Id of the expected workspace type.
 * \return        Pointer to workspace  DET check enabled and workspace type matches or DET checks disabled.
 * \return        NULL_PTR              DET check enabled and workspace type doesn't match.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_GenericNodeWorkspaceType, VSTREAMPROC_CODE) vStreamProc_GetTypedWorkspaceOfProcessingNode(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_WorkspaceTypeIdType WorkspaceTypeId);

/**********************************************************************************************************************
 *  vStreamProc_GetTypedConfigOfProcessingNode()
 *********************************************************************************************************************/
/*!
 * \brief         Get the pointer to the configuration of a processing node.
 * \details       Returns the pointer to the configuration, while performing a DET check against the
 *                expected configuration type.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     ConfigTypeId      Id of the expected configuration type.
 * \return        Pointer to configuration  DET check enabled and configuration type matches or DET checks disabled.
 * \return        NULL_PTR                  DET check enabled and configuration type doesn't match.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_GenericNodeConfigType, VSTREAMPROC_CODE) vStreamProc_GetTypedConfigOfProcessingNode(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_ConfigTypeIdType ConfigTypeId);

/**********************************************************************************************************************
 *  vStreamProc_PrepareInputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize input port information structure.
 * \details       -
 * \param[in]     ProcNodeInfo              The processing node information to operate on.
 * \param[in]     SymbolicNameOfInputPort   A named input port of the processing node.
 * \param[out]    InputPortInfo             Pointer to input port information structure.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Id     Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - ReadRequest.StorageInfo.DataTypeInfo.Size   Set to zero.
 *                - ReadRequest.StorageInfo.AvailableLength     Set to zero.
 *                - ReadRequest.StorageInfo.RequestLength       Set to zero.
 *                - ReadRequest.StorageInfo.ReleaseFlag         Set to TRUE.
 *                - ReadRequest.Buffer                          Set to NULL_PTR.
 *                - PortHandle                                  Set to handle matching the named input port.
 *                - SymbolicPortName                            Set to passed symbolic name value.
 *                - IsConnected                                 TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortSymbolicNameType SymbolicNameOfInputPort,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetInputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe input port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 *                                  vStreamProcConf_vStreamProcDataType_Undefined if no specific data type is expected.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetInputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_RequestInputPortData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a read action.
 * \details       This call does not read any data from the buffer. It rather provides pointer and length information. 
 *                The application then has to do the data reading based on this information. If data is available, the 
 *                provided pointer does not change until a read acknowledge is issued. Defragmentation may be blocked 
 *                due to a pending read request. A read request that indicates data must always be acknowledged to release
 *                the defragmentation lock.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 * \param[in]     RequestLength     Requested minimum buffer length.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - ReadRequest.StorageInfo.AvailableLength     Available buffer length.
 *                  - ReadRequest.StorageInfo.RequestLength       Requested minimum buffer length.
 *                  - ReadRequest.Buffer                          Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestInputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeInputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a read action.
 * \details       The processing node shall have issued a read request which then can be acknowledge by calling this 
 *                function. Therefore, the amount of consumed data must be provided. By acknowledging a read request
 *                a possible defragmentation lock is being released.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     ConsumedLength    The amount of consumed data which needs to be acknowledged.
 * \param[in]     ReleaseFlag       Flag to control release of storage lock.
 *                - TRUE: Release storage lock.
 *                - FALSE: Keep storage locked.
 * \param[in,out] InputPortInfo     Pointer to input port information structure.
 *                - Input
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
 *                  - PortHandle                                  Handle of an input port of the processing node.
 *                  - SymbolicPortName                            Named input port of the processing node.
 *                - Output
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Id     Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - ReadRequest.StorageInfo.DataTypeInfo.Size   Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - ReadRequest.StorageInfo.AvailableLength     Updated available buffer length.
 *                                                                Zero if storage lock was released.
 *                  - ReadRequest.StorageInfo.RequestLength       Passed produced length value.
 *                                                                Zero if storage lock was released.
 *                  - ReadRequest.StorageInfo.ReleaseFlag         Passed release flag value.
 *                  - ReadRequest.Buffer                          Updated pointer to available buffer.
 *                                                                NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeInputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_LengthType ConsumedLength,
  boolean ReleaseFlag,
  vStreamProc_InputPortInfoPtrType InputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_PrepareOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize output port information structure.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     SymbolicNameOfOutputPort  A named output port of the processing node.
 * \param[out]    OutputPortInfo            Pointer to output port information structure.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Id    Set to vStreamProcConf_vStreamProcDataType_Undefined.
 *                - WriteRequest.StorageInfo.DataTypeInfo.Size  Set to zero.
 *                - WriteRequest.StorageInfo.AvailableLength    Set to zero.
 *                - WriteRequest.StorageInfo.RequestLength      Set to zero.
 *                - WriteRequest.StorageInfo.ReleaseFlag        Set to TRUE.
 *                - WriteRequest.Buffer                         Set to NULL_PTR.
 *                - PortHandle                                  Set to handle matching the named output port.
 *                - SymbolicPortName                            Set to passed symbolic name value.
 *                - IsConnected                                 TRUE if port is connected, FALSE otherwise.
 * \return        VSTREAMPROC_OK      Operation was successful.
 * \return        VSTREAMPROC_FAILED  Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_OutputPortSymbolicNameType SymbolicNameOfOutputPort,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_GetOutputPortInfo()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about a pipe output port.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 *                                  vStreamProcConf_vStreamProcDataType_Undefined if no specific data type is expected.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetOutputPortInfo(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_RequestOutputPortData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests a write action.
 * \details       This call does not write any data to a buffer. It rather provides the pointer and length information
 *                to the application. The application can then write its data to the provided pointer while the 
 *                maximum data amount is limited by the provided available length.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     DataTypeId        Id of the expected data type of the storage node connected to the access point.
 * \param[in]     RequestLength     Requested minimum buffer length.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the port.
 *                  - WriteRequest.StorageInfo.AvailableLength    Available buffer length.
 *                  - WriteRequest.StorageInfo.RequestLength      Requested minimum buffer length.
 *                  - WriteRequest.Buffer                         Pointer to available buffer.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   Requested minimum buffer length isn't available.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestOutputPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgeOutputPort()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges a write action.
 * \details       The processing node shall have requested a write request which then can be acknowledge by calling 
 *                this function. The write request only provides a maximum amount of data to be produced, but it does
 *                not specify a precise amount of data which shall be produced. Therefore, the amount of produced
 *                data must be provided by calling this function.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in]     ProducedLength    The amount of produced data which needs to be acknowledged.
 * \param[in]     ReleaseFlag       Flag to control release of storage lock.
 *                - TRUE: Release storage lock.
 *                - FALSE: Keep storage locked.
 * \param[in,out] OutputPortInfo    Pointer to output port information structure.
 *                - Input
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the expected data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only required when storage lock is kept.
 *                  - PortHandle                                  Handle of an output port of the processing node.
 *                  - SymbolicPortName                            Named output port of the processing node.
 *                - Output
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Id    Id of the actual data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.DataTypeInfo.Size  Byte size of data type of the storage node
 *                                                                connected to the access point.
 *                                                                Only set when storage lock is kept.
 *                  - WriteRequest.StorageInfo.AvailableLength  Updated available buffer length.
 *                                                              Zero if storage lock was released.
 *                  - WriteRequest.StorageInfo.RequestLength      Passed produced length value.
 *                                                                Zero if storage lock was released.
 *                  - WriteRequest.StorageInfo.ReleaseFlag        Passed release flag value.
 *                  - WriteRequest.Buffer                       Updated pointer to available buffer.
 *                                                              NULL_PTR if storage lock was released.
 * \return        VSTREAMPROC_OK                    Operation was successful.
 * \return        VSTREAMPROC_FAILED                Operation was unsuccessful.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeOutputPort(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_LengthType ProducedLength,
  boolean ReleaseFlag,
  vStreamProc_OutputPortInfoPtrType OutputPortInfo);

/**********************************************************************************************************************
 *  vStreamProc_PreparePortInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize multiple port information structures.
 * \details       See #vStreamProc_PrepareInputPortInfo and #vStreamProc_PrepareOutputPortInfo for details.
 * \param[in]     ProcNodeInfo          The processing node information to operate on.
 * \param[in,out] InputPortInfo         Input port information structures. NULL_PTR if not used.
 *                - Input
 *                  - SymbolicPortName  A named input port of the processing node.
 *                - Output              See #vStreamProc_PrepareInputPortInfo.
 * \param[in]     InputPortCount        Number of input port information structures.
 * \param[in,out] OutputPortInfo        Output port information structures. NULL_PTR if not used.
 *                - Input
 *                  - SymbolicPortName  A named output port of the processing node.
 *                - Output              See #vStreamProc_PrepareOutputPortInfo.
 * \param[in]     OutputPortCount       Number of output port information structures.
 * \return        VSTREAMPROC_FAILED    Operation failed for at least one port.
 * \return        VSTREAMPROC_OK        Operation was successful for all ports.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PreparePortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_PrepareAllPortInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Initialize information structures for all ports of a pipe.
 * \details       See #vStreamProc_PrepareInputPortInfo and #vStreamProc_PrepareOutputPortInfo for details.
 * \param[in]     ProcNodeInfo          The processing node information to operate on.
 * \param[out]    InputPortInfo         Input port information structures. NULL_PTR if not used.
 *                - SymbolicPortName    Set to value matching the index.
 *                - <Other members>     See #vStreamProc_PrepareInputPortInfo.
 * \param[in]     InputPortCount        Number of input port information structures.
 * \param[out]    OutputPortInfo        Output port information structures. NULL_PTR if not used.
 *                - SymbolicPortName    Set to value matching the index.
 *                - <Other members>     See #vStreamProc_PrepareOutputPortInfo.
 * \param[in]     OutputPortCount       Number of output port information structures.
 * \return        VSTREAMPROC_FAILED    Operation failed for at least one port.
 * \return        VSTREAMPROC_OK        Operation was successful for all ports.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAllPortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_GetPortInfos()
 *********************************************************************************************************************/
/*!
 * \brief         Get information about multiple pipe ports.
 * \details       See #vStreamProc_GetInputPortInfo and #vStreamProc_GetOutputPortInfo for details.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfos    Input port information structures. NULL_PTR if not used.
 * \param[in]     InputPortCount    Number of input port information structures.
 * \param[in,out] OutputPortInfos   Output port information structures. NULL_PTR if not used.
 * \param[in]     OutputPortCount   Number of output port information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetPortInfos(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_RequestPortData()
 *********************************************************************************************************************/
/*!
 * \brief         Requests multiple read and write actions.
 * \details       See #vStreamProc_RequestOutputPortData and #vStreamProc_RequestInputPortData for details.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfos    Input port information structures. NULL_PTR if not used.
 * \param[in]     InputPortCount    Number of input port information structures.
 * \param[in,out] OutputPortInfos   Output port information structures. NULL_PTR if not used.
 * \param[in]     OutputPortCount   Number of output port information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_INSUFFICIENT_OUTPUT   At least one port cannot provide the requested minimum storage.
 * \return        VSTREAMPROC_INSUFFICIENT_INPUT    At least one port cannot provide the requested minimum data.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestPortData(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_AcknowledgePorts()
 *********************************************************************************************************************/
/*!
 * \brief         Acknowledges multiple read and write actions.
 * \details       See #vStreamProc_AcknowledgeInputPort and #vStreamProc_AcknowledgeOutputPort for details.
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \param[in,out] InputPortInfos   Input port information structures. NULL_PTR if not used.
 * \param[in]     InputPortCount    Number of input port information structures.
 * \param[in,out] OutputPortInfos   Output port information structures. NULL_PTR if not used.
 * \param[in]     OutputPortCount   Number of output port information structures.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgePorts(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo,
  vStreamProc_InputPortInfoPtrType InputPortInfos,
  vStreamProc_InputPortIdType InputPortCount,
  vStreamProc_OutputPortInfoPtrType OutputPortInfos,
  vStreamProc_OutputPortIdType OutputPortCount);

/**********************************************************************************************************************
 *  vStreamProc_ReleaseAllPorts()
 *********************************************************************************************************************/
/*!
 * \brief         Releases storage lock of all ports.
 * \details       -
 * \param[in]     ProcNodeInfo      The processing node information to operate on.
 * \return        VSTREAMPROC_FAILED                Operation failed for at least one port.
 * \return        VSTREAMPROC_OK                    Operation was successful for all ports.
 * \pre           The pipe is open.
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ReleaseAllPorts(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ProcNodeInfo);

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_Port.h
 *********************************************************************************************************************/

