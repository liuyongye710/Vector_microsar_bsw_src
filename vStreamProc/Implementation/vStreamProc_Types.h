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
/*!        \file  vStreamProc_Types.h
 *        \brief  vStreamProc types header file
 *
 *      \details  Definition of all relevant types for vStreamProc
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
#ifndef VSTREAMPROC_TYPES_H
#define VSTREAMPROC_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* State value for workspaces with state */
#define VSTREAMPROC_WS_STATE_UNDEFINED            0xFFu
#define VSTREAMPROC_WS_STATE_INITIALIZED          0x01u /**< Shall be set at end of <ProcNode>_Init function */
#define VSTREAMPROC_WS_STATE_PROCESSING           0x02u /**< Shall be set in <ProcNode>_Process function, after all INIT/FIRST CALL actions are done. */

#define VSTREAMPROC_MAX_LENGTH                    0xFFFFFFFFu

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#define VSTREAMPROC_NO_METASTATE        VSTREAMPROC_NO_METASTATESTARTIDXOFPIPE
#define VSTREAMPROC_NO_MODE             VSTREAMPROC_NO_MODESTARTIDXOFPIPE
#define VSTREAMPROC_NO_NAMEDINPUTPORT   VSTREAMPROC_NO_PROCNODE_STORAGEOUTPUTPORTSINPUTPORTDYNIDXOFNAMEDINPUTPORTS2ACTUALPORTS
#define VSTREAMPROC_NO_NAMEDOUTPUTPORT  VSTREAMPROC_NO_STORAGENODEIDXOFNAMEDOUTPUTPORTS2ACTUALPORTS

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Note: Sorted by increasing "severity". */
typedef enum
{
  VSTREAMPROC_OK,
  VSTREAMPROC_PENDING,
  VSTREAMPROC_INSUFFICIENT_INPUT,
  VSTREAMPROC_INSUFFICIENT_OUTPUT,
  VSTREAMPROC_FAILED
} vStreamProc_ReturnType;

typedef uint32 vStreamProc_NodeIdType;
typedef uint32 vStreamProc_ProcessingNodeIdType;
typedef uint32 vStreamProc_SliceHandleType;
typedef uint32 vStreamProc_StorageNodeIdType;
typedef uint32 vStreamProc_OutputPortIdType;
typedef uint32 vStreamProc_InputPortIdType;
typedef uint32 vStreamProc_OutputPortSymbolicNameType;
typedef uint32 vStreamProc_InputPortSymbolicNameType;
typedef uint32 vStreamProc_SchedulerIdType;
typedef uint32 vStreamProc_PipeIdType;
typedef uint32 vStreamProc_EntryPointIdType;
typedef uint32 vStreamProc_ExitPointIdType;
typedef uint32 vStreamProc_ModeIdType;
typedef uint32 vStreamProc_ModeHandleIdType;
typedef uint32 vStreamProc_DataTypeIdType;
typedef uint32 vStreamProc_WorkspaceTypeIdType;
typedef uint32 vStreamProc_ConfigTypeIdType;

typedef uint32 vStreamProc_LengthType;
typedef boolean vStreamProc_OutputActivationType;
typedef void * vStreamProc_GenericNodeWorkspaceType;
typedef const void * vStreamProc_GenericNodeConfigType;

typedef struct
{
  vStreamProc_LengthType      Size;
  vStreamProc_DataTypeIdType  Id;
} vStreamProc_DataTypeInfoType;

typedef struct
{
  vStreamProc_StorageNodeIdType   StorageNodeId;
  vStreamProc_OutputPortIdType    OutputPortId;
} vStreamProc_InputPortHandleType;

typedef vStreamProc_StorageNodeIdType vStreamProc_OutputPortHandleType;

typedef struct
{
  vStreamProc_DataTypeInfoType  DataTypeInfo;
  vStreamProc_LengthType        AvailableLength;
  vStreamProc_LengthType        RequestLength;
  boolean                       ReleaseFlag;
} vStreamProc_StorageInfoType;

typedef P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)      vStreamProc_StorageInfoPtrType;
typedef P2CONST(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)    vStreamProc_StorageInfoConstPtrType;

typedef struct
{
  vStreamProc_StorageInfoType                       StorageInfo;
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR)   Buffer;
} vStreamProc_ReadRequestType;

typedef struct
{
  vStreamProc_StorageInfoType                       StorageInfo;
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR)     Buffer;
} vStreamProc_WriteRequestType;

typedef struct
{
  vStreamProc_GenericNodeWorkspaceType  Pointer;
  vStreamProc_WorkspaceTypeIdType       TypeId;
} vStreamProc_WorkspaceInfoType;

typedef struct
{
  vStreamProc_GenericNodeConfigType   Pointer;
  vStreamProc_ConfigTypeIdType        TypeId;
} vStreamProc_ConfigInfoType;

typedef struct
{
  vStreamProc_WorkspaceInfoType     WorkspaceInfo;
  vStreamProc_ConfigInfoType        ConfigInfo;
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR)  InputPortResults;
  P2VAR(vStreamProc_ReturnType, AUTOMATIC, VSTREAMPROC_APPL_VAR)  OutputPortResults;
  vStreamProc_ProcessingNodeIdType  ProcessingNodeId;
  vStreamProc_SliceHandleType       SliceHandle;
  vStreamProc_InputPortIdType       InputPortCount;
  vStreamProc_OutputPortIdType      OutputPortCount;
} vStreamProc_ProcessingNodeInfoType;

typedef struct
{
  vStreamProc_ReadRequestType             ReadRequest;
  vStreamProc_InputPortHandleType         PortHandle;
  vStreamProc_InputPortSymbolicNameType   SymbolicPortName;
  boolean                                 IsConnected;
} vStreamProc_InputPortInfoType;

typedef P2VAR(vStreamProc_InputPortInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)      vStreamProc_InputPortInfoPtrType;
typedef P2CONST(vStreamProc_InputPortInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)    vStreamProc_InputPortInfoConstPtrType;

typedef struct
{
  vStreamProc_WriteRequestType            WriteRequest;
  vStreamProc_OutputPortHandleType        PortHandle;
  vStreamProc_OutputPortSymbolicNameType  SymbolicPortName;
  boolean                                 IsConnected;
} vStreamProc_OutputPortInfoType;

typedef P2VAR(vStreamProc_OutputPortInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)     vStreamProc_OutputPortInfoPtrType;
typedef P2CONST(vStreamProc_OutputPortInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)   vStreamProc_OutputPortInfoConstPtrType;

typedef struct
{
  vStreamProc_WriteRequestType      WriteRequest;   /*!< The write request. */
  vStreamProc_EntryPointIdType      EntryPointId;   /*!< The entry point ID. */
} vStreamProc_EntryPointInfoType;

typedef P2VAR(vStreamProc_EntryPointInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)     vStreamProc_EntryPointInfoPtrType;
typedef P2CONST(vStreamProc_EntryPointInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)   vStreamProc_EntryPointInfoConstPtrType;

typedef struct
{
  vStreamProc_ReadRequestType       ReadRequest;
  vStreamProc_ExitPointIdType       ExitPointId;
} vStreamProc_ExitPointInfoType;

typedef P2VAR(vStreamProc_ExitPointInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)      vStreamProc_ExitPointInfoPtrType;
typedef P2CONST(vStreamProc_ExitPointInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA)    vStreamProc_ExitPointInfoConstPtrType;

/**********************************************************************************************************************
 * NODE SPECIFIC TYPES
 *********************************************************************************************************************/


/* Processing node specific function pointer */
typedef P2FUNC(Std_ReturnType, VSTREAMPROC_CODE, vStreamProc_ProcessingNode_InitFctPtrType)(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_ProcessingNode_ProcessFctPtrType)(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_ProcessingNode_FlushFctPtrType)(
  P2CONST(vStreamProc_ProcessingNodeInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) NodeInfo);

/* Storage node specific function pointer */
typedef P2FUNC(Std_ReturnType, VSTREAMPROC_CODE, vStreamProc_InitFctPtrType)(
  vStreamProc_StorageNodeIdType StorageNodeId);

typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_ProcessFctPtrType)(
  vStreamProc_StorageNodeIdType StorageNodeId);

typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_FlushFctPtrType)(
  vStreamProc_StorageNodeIdType StorageNodeId);

/* Data access function pointer */
typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_ProduceDataFctPtrType)(
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) Buffer,
  CONST(vStreamProc_LengthType, AUTOMATIC)  AvailableLen,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_VAR) ProducedLen);
typedef vStreamProc_ProduceDataFctPtrType vStreamProc_ProduceCallbackType;

typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_ConsumeDataFctPtrType)(
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR)  Buffer,
  CONST(vStreamProc_LengthType, AUTOMATIC)  AvailableLen,
  P2VAR(vStreamProc_LengthType, AUTOMATIC, VSTREAMPROC_APPL_VAR) ConsumedLen);
typedef vStreamProc_ConsumeDataFctPtrType vStreamProc_ConsumeCallbackType;


/* Storage node data provisioning function pointer */
typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_InputPort_AnnounceStreamFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceDataFctPtrType, AUTOMATIC) ProduceCbk);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_InputPort_WriteInfoFctPtrType)(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) WriteInfoPtr);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_InputPort_WriteRequestFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  P2VAR(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) RequestBufferPtr);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_InputPort_WriteAckFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeId,
  CONST(vStreamProc_LengthType, AUTOMATIC) ProducedLen);


/* Storage node data consumption function pointer */
typedef P2FUNC(Std_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPort_RequestStreamFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeIdx,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  CONST(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortIdx);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPort_ReadInfoFctPtrType)(
  vStreamProc_StorageNodeIdType StorageNodeId,
  P2VAR(vStreamProc_StorageInfoType, AUTOMATIC, VSTREAMPROC_APPL_DATA) ReadInfoPtr,
  vStreamProc_OutputPortIdType OutputPortId);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPort_ReadRequestFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeIdx,
  P2VAR(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) RequestBufferPtr,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortIdx);
typedef P2FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPort_ReadAckFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeIdx,
  CONST(vStreamProc_LengthType, AUTOMATIC) ConsumedLen,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortIdx);

/* Storage node info function pointer */
typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_StorageInfo_StreamAvailableFctPtrType)(
  CONST(vStreamProc_NodeIdType, AUTOMATIC) GenericNodeIdx,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerIdx);

typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_StorageInfo_DataAvailableFctPtrType)(
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortIdx,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerIdx);

typedef P2FUNC(void, VSTREAMPROC_CODE, vStreamProc_StorageInfo_StorageAvailableFctPtrType)(
  CONST(vStreamProc_InputPortIdType, AUTOMATIC) InputPortIdx,
  CONST(vStreamProc_SchedulerIdType, AUTOMATIC) SchedulerIdx);

typedef P2FUNC(boolean, VSTREAMPROC_CODE, vStreamProc_StorageInfo_IsEmptyFctPtr)(
  vStreamProc_StorageNodeIdType StorageNodeIdx,
  vStreamProc_OutputPortIdType OutputPortIdx);

/* Storage node output port function pointer */
typedef P2FUNC(Std_ReturnType, VSTREAMPROC_CODE, vStreamProc_OutputPort_SetActivationSignalFctPtrType)(
  CONST(vStreamProc_StorageNodeIdType, AUTOMATIC) StorageNodeIdx,
  CONST(vStreamProc_OutputPortIdType, AUTOMATIC) OutputPortIdx,
  CONST(vStreamProc_OutputActivationType, AUTOMATIC) ActivationSignalValue);


#endif /* VSTREAMPROC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vStreamProc_Types.h
 *********************************************************************************************************************/

