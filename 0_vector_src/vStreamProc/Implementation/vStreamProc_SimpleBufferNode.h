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
/*!        \file  vStreamProc_SimpleBufferNode.h
 *        \brief  vStreamProc Simple Buffer Storage Node Header File
 *
 *      \details  Header file of the vStreamProc Simple Buffer Storage Node module.
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
#if !defined (VSTREAMPROC_SIMPLEBUFFERNODE_H)
# define VSTREAMPROC_SIMPLEBUFFERNODE_H

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

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/******************************************************************************
 * Specialized workspace
 ******************************************************************************/
/******************************************************************************
 * This specialized workspace is inserted into the generic node structure's generic workspace.
 *
 *  |----------------------|
 *  | vStreamProc_NodeType |                        |-----------------------------|
 *  |    One2OneIndirectionWorkspaceIdxOfNode ----> | vStreamProc_StorageNodeType |                 |--------------------------------------|
 *  |----------------------|                        |    One2OneIndirectionWorkspaceIdxOfNode ----> | vStreamProc_StorageNodeWorkspaceType |
 *                                                  |-----------------------------|                 |--------------------------------------|
 ******************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSTREAMPROC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_Init
 **********************************************************************************************************************/
/*! \brief          Initializes a simple buffer storage node
 *  \details        -
 *  \param[in]      StorageNodeId   Id of a simple buffer storage node
 *  \return         E_OK             Initialization was successful
 *  \return         E_NOT_OK         Initialization failed due to invalid input data
 *  \pre            Must be called before call of any vStreamProc_StorageNode function
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Init(
  vStreamProc_StorageNodeIdType StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_Process
 **********************************************************************************************************************/
/*! \brief          Processes a simple buffer storage node.
 *  \details        The specialized node will be inferred from the generic node.
 *  \param[in]      StorageNodeId   Id of a simple buffer storage node
 *  \return         VSTREAMPROC_OK      ProcessFctOfNode has nothing to do and needs not be called again
 *  \return         VSTREAMPROC_PENDING   ProcessFctOfNode function should be called again due to pending actions
 *  \return         VSTREAMPROC_FAILED    ProcessFctOfNode failed due to invalid input data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Process(
  vStreamProc_StorageNodeIdType StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_Flush
 **********************************************************************************************************************/
/*! \brief          Flushes a simple buffer storage node
 *  \details        If there are callbacks registered to the passed storage node, these callback are issued.
 *                  Produce callbacks are called until enough input data was produced.
 *  \param[in]      StorageNodeId   Id of a simple buffer storage node
 *  \return         VSTREAMPROC_OK  FlushFctOfNode was successful and is finished
 *  \return         VSTREAMPROC_PENDING   FlushFctOfNode is not yet finished
 *  \return         VSTREAMPROC_FAILED    FlushFctOfNode failed due to invalid input data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_Flush(
  vStreamProc_StorageNodeIdType StorageNodeId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_AnnounceStream
 **********************************************************************************************************************/
/*! \brief          Announces a callback to produce data
 *  \details        The registered/announced callback is called as long as the passed Length amount of data 
 *                  is not completely produced. If the data is completely produced, the callback gets automatically
 *                  unregistered and is not called any more until a new announcement takes place.
 *  \param[in]      StorageNodeId   Id of a simple buffer storage node
 *  \param[in]      Length          Amount of data to be produced
 *  \param[in]      ProduceCbk      Callback function pointer
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_AnnounceStream(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_WriteInfo
 **********************************************************************************************************************/
/*! \brief          Get information about available storage.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a simple buffer storage node.
 *  \param[in]      WriteInfoPtr      Pointer to a write info structure. Parameter must not be NULL.
 *  \return         VSTREAMPROC_OK                  Information successfully provided.
 *  \return         VSTREAMPROC_FAILED              Request failed due to invalid input data.
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT  Requested minimum buffer length isn't available.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteInfo(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) WriteInfoPtr);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_WriteRequest
 **********************************************************************************************************************/
/*! \brief          Requests a write action.
 *  \details        Defragment the buffer if the write request does not fit into the buffer.
 *  \param[in]      StorageNodeId       Id of a simple buffer storage node.
 *  \param[in]      RequestBufferPtr    Pointer to a write request structure. Parameter must not be NULL.
 *  \return         VSTREAMPROC_OK                  Write request was accepted.
 *  \return         VSTREAMPROC_FAILED              Write request failed due to invalid input data.
 *  \return         VSTREAMPROC_INSUFFICIENT_INPUT  Requested minimum buffer length isn't available.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteRequest(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  P2VAR(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_DATA) RequestBufferPtr);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_WriteAck
 **********************************************************************************************************************/
/*! \brief          Acknowledges a write action.
 *  \details        Issuing a write request does only provide a buffer pointer and maximum length information.
 *                  The data must be then copied externally and acknowledged afterwards by calling this function.
 *  \param[in]      StorageNodeId   Id of a simple buffer storage node.
 *  \param[in]      ProducedLen     Amount of data that was produced
 *  \return         VSTREAMPROC_OK      Write acknowledge was accepted.
 *  \return         VSTREAMPROC_FAILED  Write acknowledge failed due to invalid input data.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_WriteAck(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) ProducedLen);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_RequestStream
 **********************************************************************************************************************/
/*! \brief          Requests a stream.
 *  \details        This function registers a callback function that is called if the storage node has data available.
 *  \param[in]      StorageNodeId     Id of a simple buffer storage node
 *  \param[in]      Length            Length of the data to be consumed
 *  \param[in]      ConsumeCbk        Callback function pointer
 *  \param[in]      OutputPortId      Id of the associated output port
 *  \return         E_OK              Request stream was accepted
 *  \return         E_NOT_OK          Request stream failed due to invalid input data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_RequestStream(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  CONST(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_ReadInfo
 **********************************************************************************************************************/
/*! \brief          Get information about available data.
 *  \details        -
 *  \param[in]      StorageNodeId     Id of a simple buffer storage node.
 *  \param[in]      ReadInfoPtr       Pointer to a read info structure. Parameter must not be NULL.
 *  \param[in]      OutputPortId      Id of the associated output port
 *  \return         VSTREAMPROC_OK                  Information successfully provided.
 *  \return         VSTREAMPROC_FAILED              Request failed due to invalid input data.
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT Requested minimum buffer length isn't available.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadInfo(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ReadInfoPtr,
  vStreamProc_OutputPortIdType OutputPortId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_ReadRequest
 **********************************************************************************************************************/
/*! \brief          Requests a read action.
 *  \details        Returns the buffer and the available length to read data.
 *  \param[in]      StorageNodeId      Id of a simple buffer storage node.
 *  \param[in,out]  RequestBufferPtr   Pointer to a read request structure. Parameter must not be NULL.
 *  \param[in]      OutputPortId       Id of the associated output port.
 *  \return         VSTREAMPROC_OK                  Read request was accepted.
 *  \return         VSTREAMPROC_FAILED              Read request failed due to invalid input data.
 *  \return         VSTREAMPROC_INSUFFICIENT_OUTPUT Requested minimum buffer length isn't available.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadRequest(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  P2VAR(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_DATA) RequestBufferPtr,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_ReadAck
 **********************************************************************************************************************/
/*! \brief          Acknowledges a read action.
 *  \details        Issuing a read request does only provide a buffer pointer and an available length information.
 *                  The data must be then handled externally and acknowledged afterwards by calling this function.
 *  \param[in]      StorageNodeId       Id of a simple buffer storage node.
 *  \param[in]      ConsumedLen         Consumed data length.
 *  \param[in]      OutputPortId        Id of the associated output port.
 *  \return         VSTREAMPROC_OK      Read acknowledge was accepted.
 *  \return         VSTREAMPROC_FAILED  Read acknowledge failed due to invalid input data or no consumer was found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_ReadAck(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) ConsumedLen,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_SetActivationSignal
 **********************************************************************************************************************/
/*! \brief          Manipulates the activation of an output port
 *  \details        The output port can the activated or deactivated. The consumer will be also informed.
 *  \param[in]      StorageNodeId           Id of a simple buffer storage node
 *  \param[in]      OutputPortId            Id of the associated output port
 *  \param[in]      ActivationSignalValue   Activation to set the output port to
 *  \return         E_OK                    Output port was set to passed activation level
 *  \return         E_NOT_OK                Operation failed due to invalid input data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_SetActivationSignal(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortId,
  CONST(vStreamProc_OutputActivationType, AUTOMATIC) ActivationSignalValue);

/**********************************************************************************************************************
 *  vStreamProc_SimpleBufferNode_IsEmpty
 **********************************************************************************************************************/
/*! \brief        Verifies if the passed output port is empty.
 *  \details      Port is empty, if either no data is present or all available data was consumed.
 *  \param[in]    StorageNodeId   Id of a simple buffer storage node.
 *  \param[in]    OutputPortId    Id of the associated output port.
 *  \return       TRUE            The output port is empty/completely consumed.
 *  \return       FALSE           The output port is not empty.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(boolean, VSTREAMPROC_CODE) vStreamProc_SimpleBufferNode_IsEmpty(
  vStreamProc_StorageNodeIdType StorageNodeId,
  vStreamProc_OutputPortIdType OutputPortId);

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSTREAMPROC_SIMPLEBUFFERNODE_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_SimpleBufferNode.h
 *********************************************************************************************************************/

