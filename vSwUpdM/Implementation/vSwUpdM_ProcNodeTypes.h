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
/*!       \file  vSwUpdM_ProcNodeTypes.h
 *        \brief  vSwUpdM processing nodes type definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *********************************************************************************************************************/
#if !defined (VSWUPDM_PROCNODETYPES_H)
# define VSWUPDM_PROCNODETYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc_Types.h"
#include "vSwUpdM_Types.h"
#include "vSwUpdM_ExctJob_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define VSWUPDM_PROC_NODE_OPERATION_NONE            (vSwUpdM_ProcNodeOperationType)(0x00u)
#define VSWUPDM_PROC_NODE_OPERATION_START           (vSwUpdM_ProcNodeOperationType)(0x01u)
#define VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART   (vSwUpdM_ProcNodeOperationType)(0x02u)
#define VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART   (vSwUpdM_ProcNodeOperationType)(0x03u)
#define VSWUPDM_PROC_NODE_OPERATION_PROCESS         (vSwUpdM_ProcNodeOperationType)(0x04u)
#define VSWUPDM_PROC_NODE_OPERATION_SHUTDOWN        (vSwUpdM_ProcNodeOperationType)(0x05u)
#define VSWUPDM_PROC_NODE_OPERATION_INVALID         (vSwUpdM_ProcNodeOperationType)(0xFFu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Pointer to vStreamProc memory. */
typedef P2VAR(vSwUpdM_RangeInfoType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)           vSwUpdM_RangeInfoStreamPtrType;
typedef P2CONST(vSwUpdM_RangeInfoType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)         vSwUpdM_RangeInfoReadStreamPtrType;

typedef P2VAR(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)           vSwUpdM_EntityIdsStreamPtrType;
typedef P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)         vSwUpdM_EntityIdsReadStreamPtrType;


typedef P2VAR(Std_ReturnType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)                  vSwUpdM_ReturnStreamPtrType;
typedef P2CONST(Std_ReturnType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)                vSwUpdM_ReturnReadStreamPtrType;

typedef uint8                                                                           vSwUpdM_ProcNodeOperationType;
typedef P2VAR(vSwUpdM_ProcNodeOperationType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)   vSwUpdM_ProcNodeOperationPtrType;
typedef P2CONST(vSwUpdM_ProcNodeOperationType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR) vSwUpdM_ProcNodeOperationReadPtrType;

typedef P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)                           vSwUpdM_DataStreamPtrType;
typedef P2CONST(uint8, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR)                         vSwUpdM_DataReadStreamPtrType;

/* Node states */
typedef enum
{
  VSWUPDM_PROCNODESTATE_INITIAL,
  VSWUPDM_PROCNODESTATE_WAIT_FOR_INPUT_DATA,
  VSWUPDM_PROCNODESTATE_INITIAL_STEP,
  VSWUPDM_PROCNODESTATE_JOB_IS_PENDING
} vSwUpdM_ProcNodeStateType;

typedef enum
{
  VSWUPDM_PADDING_NODE_STATE_INITIAL,
  VSWUPDM_PADDING_NODE_STATE_WAIT_FOR_INPUTS,
  VSWUPDM_PADDING_NODE_STATE_PADDING_START,
  VSWUPDM_PADDING_NODE_STATE_COPY,
  VSWUPDM_PADDING_NODE_STATE_FINAL_STEP,
  VSWUPDM_PADDING_NODE_STATE_PADDING_END,
  VSWUPDM_PADDING_NODE_STATE_FINISHED
} vSwUpdM_PaddingNodeStateType;

typedef P2CONST(vStreamProc_DataTypeIdType, AUTOMATIC, VSWUPDM_APPL_CONST) vStreamProc_DataTypeIdPtrType;

/******************************************************************************/
/* Struct types for generic input/output handling                             */
/******************************************************************************/

typedef struct
{
  vStreamProc_InputPortIdType PortId;
  vStreamProc_DataTypeIdType  PortType;
}vSwUpdM_ProcNodesInputPortsDatatypeConfigType;
typedef P2CONST(vSwUpdM_ProcNodesInputPortsDatatypeConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) vSwUpdM_ProcNodesInputPortsDatatypeConfigPtrType;

typedef struct
{
  vStreamProc_OutputPortIdType PortId;
  vStreamProc_DataTypeIdType   PortType;
}vSwUpdM_ProcNodesOutputPortsDatatypeConfigType;
typedef P2CONST(vSwUpdM_ProcNodesOutputPortsDatatypeConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) vSwUpdM_ProcNodesOutputPortsDatatypeConfigPtrType;

typedef struct
{
  vStreamProc_InputPortInfoPtrType                  InputPortInfos;
  vSwUpdM_ProcNodesInputPortsDatatypeConfigPtrType  InputPortDatatypes;
  vStreamProc_InputPortIdType                       InputPortCount;
  vStreamProc_OutputPortInfoPtrType                 OutputPortInfos;
  vSwUpdM_ProcNodesOutputPortsDatatypeConfigPtrType OutputPortDatatypes;
  vStreamProc_OutputPortIdType                      OutputPortCount;
} vSwUpdM_ProcNodesPortsCollectionType;
typedef P2CONST(vSwUpdM_ProcNodesPortsCollectionType, AUTOMATIC, VSWUPDM_APPL_CONST) vSwUpdM_ProcNodesPortsCollectionPtrType;

/******************************************************************************/
/* Named input/ output ports types                                            */
/******************************************************************************/

typedef struct
{
  vStreamProc_InputPortInfoPtrType  DataInputPort;
  vStreamProc_InputPortInfoPtrType  EntitiesInputPort;
  vStreamProc_InputPortInfoPtrType  RangeInputPort;
  vStreamProc_OutputPortInfoPtrType DataOutputPort;
  vStreamProc_OutputPortInfoPtrType AlignedRangeOutputPort;
  vStreamProc_OutputPortInfoPtrType ResultingRangesOutputPort;
} vSwUpdM_ProcNodes_PaddingNodeNamedPortsType;

typedef P2CONST(vSwUpdM_ProcNodes_PaddingNodeNamedPortsType, AUTOMATIC, VSWUPDM_APPL_CONST) vSwUpdM_ProcNodes_PaddingNodeNamedPortsPtrType;

typedef struct
{
  vStreamProc_InputPortInfoPtrType  DataInputPort;
  vStreamProc_InputPortInfoPtrType  EntitiesInputPort;
  vStreamProc_InputPortInfoPtrType  RangeInputPort;
  vStreamProc_OutputPortInfoPtrType ResultOutputPort;
} vSwUpdM_ProcNodes_WriteNodeNamedPortsType;

typedef struct
{
  vStreamProc_InputPortInfoPtrType  EntitiesInputPort;
  vStreamProc_InputPortInfoPtrType  RangeInputPort;
  vStreamProc_OutputPortInfoPtrType AddrLenDataOutputPort;
  vStreamProc_OutputPortInfoPtrType DataOutputPort;
  vStreamProc_OutputPortInfoPtrType ResultOutputPort;
} vSwUpdM_ProcNodes_ReadNodeRequestsType;

typedef struct
{
  vStreamProc_InputPortInfoPtrType  CountInputPort;
  vStreamProc_InputPortInfoPtrType  EntitiesInputPort;
  vStreamProc_InputPortInfoPtrType  RangeInputPort;
} vSwUpdM_ProcNodes_TrackCompareProgressNodeNamedPortsType;


typedef struct
{
  vStreamProc_InputPortInfoPtrType  DataInputPort;
  vStreamProc_InputPortInfoPtrType  EntitiesInputPort;
  vStreamProc_OutputPortInfoPtrType ResultOutputPort;
}vSwUpdM_ProcNodes_RemoteNodeNamedPortsType;


/******************************************************************************/
/* Specialized workspace                                                     */
/******************************************************************************/

typedef struct
{
  vSwUpdM_LengthType                             TotalLength;
  vSwUpdM_LengthType                             PadLength;
  vSwUpdM_PaddingNodeStateType                   State;
  vStreamProc_InputPortIdType                    DataInputPortId;
  vStreamProc_InputPortIdType                    EntitiesInputPortId;
  vStreamProc_InputPortIdType                    RangeInputPortId;
  vStreamProc_OutputPortIdType                   DataOutputPortId;
  vStreamProc_OutputPortIdType                   AlignedRangeOutputPortId;
  vStreamProc_OutputPortIdType                   ResultingRangesOutputPortId;
} vSwUpdM_ProcNodePaddingWorkspaceType;

typedef P2VAR(vSwUpdM_ProcNodePaddingWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR)              vSwUpdM_ProcNodePaddingWorkspacePtrType;

typedef struct
{
  vSwUpdM_LengthType        PendingLength;
  vSwUpdM_LengthType        TotalLength;
  vSwUpdM_LinkedResultType  JobResult;

  vSwUpdM_ProcNodeStateType State;
  vSwUpdM_EntityIdsType Entities;
  vSwUpdM_RangeInfoType Range;
} vSwUpdM_ProcNodeWriteWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeWriteWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR)                vSwUpdM_ProcNodeWriteWorkspacePtrType;

typedef struct
{
  vSwUpdM_LengthType        PendingLength;
  vSwUpdM_LengthType        TotalLength;
  vSwUpdM_LinkedResultType  JobResult;

  boolean                   JobIsPending;
  boolean                   AddrLenIsWritten;
} vSwUpdM_ProcNodeReadWorkspaceType;

typedef P2VAR(vSwUpdM_ProcNodeReadWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR)                 vSwUpdM_ProcNodeReadWorkspacePtrType;

typedef struct
{
  vSwUpdM_LengthType        PendingLength;
  vSwUpdM_LengthType        TotalLength;
  vSwUpdM_LinkedResultType  JobResult;

  vSwUpdM_ProcNodeStateType State;
  vSwUpdM_EntityIdsType Entities;
}vSwUpdM_ProcNodeRemoteWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeRemoteWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR)               vSwUpdM_ProcNodeRemoteWorkspacePtrType;

typedef struct
{
  vSwUpdM_LengthType        PendingLength;
  vSwUpdM_LengthType        TotalLength;

  boolean                   FirstCall;
  boolean                   UpdateWriteAddress;
  vSwUpdM_AddressType       CheckpointAddress;
} vSwUpdM_ProcNodeTrackCompareProgressWorkspaceType;
typedef P2VAR(vSwUpdM_ProcNodeTrackCompareProgressWorkspaceType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_ProcNodeTrackCompareProgressWorkspacePtrType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* VSWUPDM_PROCNODETYPES_H */

/**********************************************************************************************************************
*  END OF FILE: vSwUpdM_ProcNodeTypes.h
*********************************************************************************************************************/

