/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vSwUpdM_Priv.h
 *        \brief  vSwUpdM private declarations.
 *      \details  Header for vSwUpdM private declarations.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#ifndef VSWUPDM_PRIV_H
# define VSWUPDM_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM.h"
#include "vSwUpdM_Priv_Types.h"
#include "vSwUpdM_Queue.h"

#include "SchM_vSwUpdM.h"

#include "vSwUpdM_ProcNodeTypes.h"
#include "vSwUpdM_ExecCtrl_Impl.h"
#include "vSwUpdM_SrvcUpperLayer_If.h"

#include "vStreamProc.h"
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# include "vRpcProxy_vSwUpdM.h"
# include "vRpcProxy_Service.h"
#endif

#include "vSwUpdM_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * Internal comment removed.
 *
 *
 */
#define VSWUPDM_REMOTESTREAMHANDLE_SIZE 8u

/*!
 * Internal comment removed.
 *
 *
 */
#define VSWUPDM_REVISION_UPDATE_NONE          ((vSwUpdM_RevisionUpdateType)0x00u)
#define VSWUPDM_REVISION_UPDATE_TAKE_OVER     ((vSwUpdM_RevisionUpdateType)0x01u)
#define VSWUPDM_REVISION_UPDATE_INCREMENT     ((vSwUpdM_RevisionUpdateType)0x02u)
#define VSWUPDM_REVISION_UPDATE_SIZE          ((vSwUpdM_RevisionUpdateType)0x03u) /**< Number of entries */

/*!
 * Internal comment removed.
 *
 *
 */
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_NONE                  ((vSwUpdM_SubScopeAttributeType)(0u))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS              ((vSwUpdM_SubScopeAttributeType)(1uL << 0uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED    ((vSwUpdM_SubScopeAttributeType)(1uL << 1uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_FREE    ((vSwUpdM_SubScopeAttributeType)(1uL << 2uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_PARTIAL_SEGMENT       ((vSwUpdM_SubScopeAttributeType)(1uL << 3uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE         ((vSwUpdM_SubScopeAttributeType)(1uL << 4uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_RESERVED_AREA         ((vSwUpdM_SubScopeAttributeType)(1uL << 5uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_SOURCE_ENTITES        ((vSwUpdM_SubScopeAttributeType)(1uL << 6uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_OPEN_SEGMENT          ((vSwUpdM_SubScopeAttributeType)(1uL << 7uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT         ((vSwUpdM_SubScopeAttributeType)(1uL << 8uL))
#define VSWUPDM_SUB_SCOPE_ATTRIBUTE_REMOTE_EXECUTION      ((vSwUpdM_SubScopeAttributeType)(1uL << 9uL))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#define VSWUPDM_ENTER_CRITICAL_SECTION()              SchM_Enter_vSwUpdM_VSWUPDM_EXCLUSIVE_AREA_0()
#define VSWUPDM_LEAVE_CRITICAL_SECTION()              SchM_Exit_vSwUpdM_VSWUPDM_EXCLUSIVE_AREA_0()

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct vSwUpdM_ProcessDataType_Tag
{
  P2CONST(vSwUpdM_ProcessConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessConfig;
  vSwUpdM_ProcessingOperationType   Operation;
  vSwUpdM_DataProcessesIterType     ProcessId;
  vSwUpdM_ProcessScopeType          Scope;
  vStreamProc_PipeIdType            PipeId;
  vSwUpdM_PipeStateType             PipeState;
  vSwUpdM_ProcNodeOperationType     ProcOperation;
  boolean                           PipeStarted;
  boolean                           HasOperationInput;
};

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_AlignedDataType, VSWUPDM_VAR_NOINIT) vSwUpdM_BufferWriteData[((vSwUpdM_GetMaxInputStreamSize() - 1u) / sizeof(vSwUpdM_AlignedDataType)) + 1u];

#define VSWUPDM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(uint8, VSWUPDM_APPL_DATA)                       vSwUpdM_InitState;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_StateType, VSWUPDM_APPL_DATA)           vSwUpdM_GlobalState;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_UpdateStateType, VSWUPDM_APPL_DATA)     vSwUpdM_UpdateState;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(boolean, VSWUPDM_APPL_DATA)                     vSwUpdM_ResumeInfoDirty;
extern VAR(boolean, VSWUPDM_APPL_DATA)                     vSwUpdM_PartitionAttributesDirty;

#define VSWUPDM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(boolean, VSWUPDM_VAR_NOINIT)     vSwUpdM_ImplicitModuleOpenFlag;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_ModulePendingAttributesType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ModulePendingAttributes;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_SegmentDynamicAttributesType, VSWUPDM_VAR_NOINIT)   vSwUpdM_SegmentPendingAttributes;
extern VAR(uint32, VSWUPDM_VAR_NOINIT)                                 vSwUpdM_SegmentPendingCount;

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_ExternalSegmentsQueue;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_EntityDataType, VSWUPDM_VAR_NOINIT)                 vSwUpdM_EntityData;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_InternalSegmentsQueue;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_VAR_NOINIT)         vSwUpdM_ResumeInfo;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_VAR_NOINIT)         vSwUpdM_PendingResumeInfo;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_PipelinedProgrammingType, VSWUPDM_VAR_NOINIT) vSwUpdM_PipelinedProgramming;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_RemoteStream_ListType, VSWUPDM_VAR_NOINIT) vSwUpdM_RemoteStream_List[VSWUPDM_REMOTESTREAMHANDLE_SIZE];
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_StreamDataType, VSWUPDM_VAR_NOINIT)     vSwUpdM_StreamData;

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoEraseRange;
extern VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoProcessInputStream;   /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
extern VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoCopyMemory;   /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
extern VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoWriteData;
extern VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoReadData;

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_AddressType, VSWUPDM_VAR_NOINIT)                    vSwUpdM_CheckpointAddress;
/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_ProcessInfoType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ProcessUserData; /**< This structure will be filled for every process call and keeps the data for later processing */
extern VAR(vSwUpdM_ProcessDataType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ProcessData;

/*!
 * Internal comment removed.
 *
 *
 */
extern VAR(vSwUpdM_NodeIterType, VSWUPDM_VAR_NOINIT)    vSwUpdM_RemoteLockIsGrantedTo;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3684 1 */ /* MD_vSwUpdM_Rule8.11_3684_ConfigStructure */
extern CONST(vSwUpdM_SubScopeDefinitionType, VSWUPDM_CONST) vSwUpdM_SubScopeDefinitions[];

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_Init_RemoteStream()
 *********************************************************************************************************************/
/*! \brief       Initialize remote stream data objects.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_RemoteStream(void);
#endif

/**********************************************************************************************************************
 *  vSwUpdM_Init_ResetStreamData()
 *********************************************************************************************************************/
/*! \brief       Resets volatile stream attributes to default values.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_ResetStreamData(void);

/**********************************************************************************************************************
 *  vSwUpdM_Init_InitStreamData()
 *********************************************************************************************************************/
/*! \brief       Initializes the stream data with default values.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitStreamData(void);

/**********************************************************************************************************************
 *  vSwUpdM_Init_InitProcessData()
 *********************************************************************************************************************/
/*! \brief       Initializes the data processing with default values.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitProcessData(void);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_CalculateStreamAddress()
 *********************************************************************************************************************/
/*! \brief       Determine resume stream address based on opened segment, operation mode etc.
 *  \details     Depending on the segments boundaries, the configured ResumeOffset is applied. The ResumeOffset
 *               is dependent on the operation mode which is used to write the given segment.
 *  \param[in]   Segment              Pointer to segment object.
 *  \param[in]   MemoryAddress        Actual memory write address which is currently processed by running operation.
 *  \param[out]  StreamAddress        Resulting StreamAddress.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_CalculateStreamAddress(
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) Segment,
  vSwUpdM_AddressType MemoryAddress,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) StreamAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Stream_Open()
 *********************************************************************************************************************/
/*! \brief       Open pipe for data stream processing
 *  \details     -
 *  \param[in]   SegmentId          ID of the segment which is currently processed.
 *  \param[in]   EntityIds          Entity IDs identifying the module currently processed.
 *                                  At least PartitionId and ModuleId must be set.
 *  \param[in]   InternalMode       Defines if local or remote stream processing is desired.
 *  \param[in]   ExternalOperation  Provide information on required data processing (aka "DFI") to pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Stream_Open(
  vSwUpdM_SegmentIdType SegmentId,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_TypeOfIntModeType InternalMode,
  vSwUpdM_ProcessingOperationType ExternalOperation);

/**********************************************************************************************************************
 *  vSwUpdM_Stream_Abort()
 *********************************************************************************************************************/
/*! \brief       Cleanup after aborted process stream
 *  \details     -
 *  \param[in,out] Job                Reference to parent Job.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Stream_Abort(vSwUpdM_JobPtrType Job);

/**********************************************************************************************************************
 *  vSwUpdM_Stream_CopyData()
 *********************************************************************************************************************/
/*! \brief       Copy data from UL to Stream Processor
 *  \details     -
 *  \param[in]     DataEntryPoint   EntryPoint for download data.
 *  \param[in]     ProcessingLength Pointer to current processing length, dependent on used input buffer and segmentation.
 *                                  Must not be a null pointer.
 *  \param[in,out] InputBuffer      Pointer to input buffer of active job. Must not be a null pointer.
 *  \return      E_OK                       All requested data successfully copied.
 *  \return      VSWUPDM_E_PENDING          Copy operation not finished yet. Retry on next job cycle.
 *  \return      VSWUPDM_E_CALLOUT_FAILED   Copy request to callout failed.
 *  \return      E_NOT_OK                   Any other error case.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Stream_CopyData(
  vStreamProc_EntryPointInfoPtrType DataEntryPoint,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessingLength,
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) InputBuffer);

/**********************************************************************************************************************
 *  vSwUpdM_Stream_Process()
 *********************************************************************************************************************/
/*! \brief       Trigger Stream Processor to process data
 *  \details     -
 *  \return      VSWUPDM_STREAMPROCRESULT_EMPTY     Input buffer should be empty now.
 *  \return      VSWUPDM_STREAMPROCRESULT_BLOCKED   Operation is blocked until resulting output data is consumed
 *                                                  or additional input data is provided.
 *  \return      VSWUPDM_STREAMPROCRESULT_PARTIALLY At least one free byte is available in input buffer.
 *  \return      VSWUPDM_STREAMPROCRESULT_FULL      Input buffer is full.
 *  \return      VSWUPDM_STREAMPROCRESULT_FAIL      Operation failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(vSwUpdM_StreamProcessResultType, VSWUPDM_CODE) vSwUpdM_Stream_Process(void);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_GetUsedBuffer()
 *********************************************************************************************************************/
/*! \brief       Get pointer to used buffer.
 *  \details     Return a pointer to the beginning of the used area in the buffer.
 *  \param[out]  BufferInfo     The buffer info referencing the data.
 *  \return      Pointer to the used area in the buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(vSwUpdM_VarDataPointerType, VSWUPDM_CODE) vSwUpdM_Buffer_GetUsedBuffer(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_GetFreeBuffer()
 *********************************************************************************************************************/
/*! \brief       Get pointer to free buffer.
 *  \details     Return a pointer to the beginning of free area in the buffer.
 *  \param[out]  BufferInfo     The buffer info referencing the data.
 *  \return      Pointer to the free area in the buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(vSwUpdM_VarDataPointerType, VSWUPDM_CODE) vSwUpdM_Buffer_GetFreeBuffer(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_ConsumeData()
 *********************************************************************************************************************/
/*! \brief       Indicate data is consumed from the referenced buffer.
 *  \details     Data is expected to be consumed from the beginning of the used area.
 *  \param[in,out] BufferInfo   The buffer info referencing the data.
 *  \return      E_OK         Requested length can be consumed.
 *  \return      E_NOT_OK     Requested length exceeds available data size.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_ConsumeData(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_MoveRemainder()
 *********************************************************************************************************************/
/*! \brief       Move any remaining data to the beginning of the referenced buffer.
 *  \details     -
 *  \param[in,out] BufferInfo   The buffer info referencing the data.
 *  \return      E_OK         Remainder successfully moved to beginning of buffer.
 *  \return      E_NOT_OK     Moving of remainder failed.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_MoveRemainder(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalEntryPoint()
 *********************************************************************************************************************/
/*! \brief       Provides the ID of the pipe entry point of the requested type.
 *  \details     Looks up configured entry point for the requested type of the pipe assigned to the given data process.
 *  \param[out]  EntryPointId   Pointer to the ID of the entry point. Must not be a null pointer.
 *  \param[in]   DataProcessId  The ID of the requested data process.
 *  \param[in]   Type           The requested type of the entry point.
 *  \return      E_OK           Valid entry point found for requested type.
 *  \return      E_NOT_OK       No entry point found for requested type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalEntryPoint(
  P2VAR(vStreamProc_EntryPointIdType, AUTOMATIC, VSWUPDM_APPL_VAR) EntryPointId,
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_HasInternalEntryPoint()
 *********************************************************************************************************************/
/*! \brief       Provide information if the pipe has an internal entry point of the requested type.
 *  \details     Checks for configured internal entry point of the requested type of the pipe assigned to the
 *               given data process.
 *  \param[in]   DataProcessId The ID of the requested data process.
 *  \param[in]   Type          The requested type of the entry point.
 *  \return      TRUE          Valid entry point found for requested type.
 *  \return      FALSE         No entry point found for requested type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_HasInternalEntryPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetEntryPoint()
 *********************************************************************************************************************/
/*! \brief       Get available buffer capacity and datatype of entry point.
 *  \details     -
 *  \param[in]   PipeId          ID of the pipe.
 *  \param[in]   EntryPointId    ID of the entry point.
 *  \param[out]  EntryPointInfos Structure providing access to buffer.
 *  \return      E_OK on success.
 *  \return      E_NOT_OK else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestEntryPoint()
 *********************************************************************************************************************/
/*! \brief       Requests access to an entry point of a pipe.
 *  \details     Prepare Entry-Point access.
 *               Request a buffer from vStreamProc.
 *  \param[in]   PipeId          ID of pipe.
 *  \param[in]   EntryPointId    ID of entry point.
 *  \param[in]   Length          Minimum size of requested buffer.
 *  \param[out]  EntryPointInfos Structure providing access to buffer.
 *  \return      E_OK     On success.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vSwUpdM_LengthType Length,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetLiteralReadBuffer()
 *********************************************************************************************************************/
/*! \brief       Check for appropriate exit point datatype and return uint8 pointer.
 *  \details     For remote transmission, all data pointers must be casted to byte pointers.
 *               HINT: This will (only) work for literal types. Non-literals like structs can not safely casted because
 *                     of potential different alignment requirements on the remote side.
 *  \param[in]   ExitPointInfo Structure providing access to buffer.
 *  \return      Pointer to buffer.
 *  \return      NULL_PTR if exit point has non-literal type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(vSwUpdM_DataReadStreamPtrType, VSWUPDM_CODE) vSwUpdM_Pipe_GetLiteralReadBuffer(vStreamProc_ExitPointInfoConstPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetLiteralWriteBuffer()
 *********************************************************************************************************************/
/*! \brief       Check for appropriate entry point datatype and return uint8 pointer.
 *  \details     For remote transmission, all data pointers must be casted to byte pointers.
 *               HINT: This will (only) work for literal types. Non-literals like structs can not safely casted because
 *                     of potential different alignment requirements on the remote side.
 *  \param[in]   EntryPointInfo Structure providing access to buffer.
 *  \return      Pointer to buffer.
 *  \return      NULL_PTR if exit point has non-literal type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(vSwUpdM_DataStreamPtrType, VSWUPDM_CODE) vSwUpdM_Pipe_GetLiteralWriteBuffer(vStreamProc_EntryPointInfoConstPtrType EntryPointInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestInternalEntryPoint()
 *********************************************************************************************************************/
/*! \brief       Requests access to an internal entry point of a pipe.
 *  \details     Internal inputs are maintained by the vSwUpdM and not provided to the UL. Their type is known to
 *               the vSwUpdM. The access is indirected by these type definitions.
 *               HINT: This is similar to vSwUpdM_Pipe_RequestEntryPoint() besides, this cross-checks the data type.
 *  \param[in]   DataProcessId   ID of (configured) data process.
 *  \param[in]   Type            Type of entry point.
 *  \param[in]   Length          Requested (minimum) length.
 *  \param[out]  EntryPointInfos Structure providing access to buffer.
 *  \return      E_OK     On success.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestInternalEntryPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vStreamProc_LengthType Length,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos
);
/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalExitPoint()
 *********************************************************************************************************************/
/*! \brief       Provides the ID of the pipe exit point of the requested type.
 *  \details     Looks up configured exit point for the requested type of the pipe assigned to the given data process.
 *  \param[out]  ExitPointId   Pointer to the ID of the exit point. Must not be a null pointer.
 *  \param[in]   DataProcessId The ID of the requested data process.
 *  \param[in]   Type          The requested type of the exit point.
 *  \return      E_OK          Valid exit point found for requested type.
 *  \return      E_NOT_OK      No exit point found for requested type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalExitPoint(
  P2VAR(vStreamProc_ExitPointIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ExitPointId,
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_HasInternalExitPoint()
 *********************************************************************************************************************/
/*! \brief       Provide information if the pipe has an internal exit point of the requested type.
 *  \details     Checks for configured internal exit point for the requested type of the pipe assigned to the
 *               given data process.
 *  \param[in]   DataProcessId  The ID of the requested data process.
 *  \param[in]   Type           The requested type of the exit point.
 *  \return      TRUE  Valid exit point found for requested type.
 *  \return      FALSE No exit point found for requested type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_HasInternalExitPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetSubScopeAttributes()
 *********************************************************************************************************************/
/*! \brief       Get attributes of a sub scope.
 *  \details     Search list of sub scope attribute definitions (vSwUpdM_SubScopeDefinitions) for a certain sub scope.
 *  \param[in]   SubScope for which attributes are to be found.
 *  \return      found attributes.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_SubScopeAttributeType, VSWUPDM_CODE) vSwUpdM_Pipe_GetSubScopeAttributes(
  vSwUpdM_SubScopeOfDataProcessesType SubScope);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_IsSubScopeAttributeSet()
 *********************************************************************************************************************/
/*! \brief       Check if an attribute is element of a set of attributes
 *  \details     -
 *  \param[in]   CurrentAttributes Set of attributes
 *  \param[in]   CheckAttribute    Attribute to check for existence in set of attributes.
 *  \return      TRUE  CheckAttributes is element of CurrentAttributes
 *  \return      FALSE CheckAttributes is not element of CurrentAttributes
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_IsSubScopeAttributeSet(
  vSwUpdM_SubScopeAttributeType CurrentAttributes,
  vSwUpdM_SubScopeAttributeType CheckAttribute);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_PrepareProcessData()
 *********************************************************************************************************************/
/*! \brief       Prepares the data processing with the given values.
 *  \details     -
 *  \param[in]   ProcessScope   The scope of the data process operation.
 *  \param[in]   ProcessId      The ID of the data process which identifies the processing pipe.
 *  \param[in]   ProcessScope   The configuration structure of the data process operation.
 *  \param[in]   ProcessInfo    Additional information for the data process.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Pipe_PrepareProcessData(
  vSwUpdM_ProcessScopeType ProcessScope,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessConfig,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_EvalProcessOperation()
 *********************************************************************************************************************/
/*! \brief       Determine the module state-specific processing operation mode.
 *  \details     -
 *  \param[in]   ProcessScope   The configuration structure of the data process operation.
 *  \param[in]   PartitionId    The ID of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId       The ID of the module whose state determines the processing operation.
 *  \return      VSWUPDM_PROC_NODE_OPERATION_START          (Fresh) start of processing.
 *               VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART  Clean restart of suspended processing.
 *               VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART  Dirty restart of interrupted processing.
 *               VSWUPDM_PROC_NODE_OPERATION_NONE           No processing necessary, previous operation finished.
 *               VSWUPDM_PROC_NODE_OPERATION_INVALID        Operation could not be determined, because module isn't in
 *                                                          a valid state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(vSwUpdM_ProcNodeOperationType, VSWUPDM_CODE) vSwUpdM_Pipe_EvalProcessOperation(
  P2CONST(vSwUpdM_ProcessConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessConfig,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteEntityIds()
 *********************************************************************************************************************/
/*! \brief       Pass given entity IDs to a processing pipe.
 *  \details     Uses the entry point associated with the given input type to pass the entity IDs to the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the entry point.
 *  \param[in]   EntityIds      Pointer to entity ID structure to be passed to the pipe.
 *  \return      E_OK           Entity IDs successfully passed to pipe.
 *  \return      E_NOT_OK       Entity IDs could not be passed to pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteEntityIds(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_EntityIdsReadStreamPtrType EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteRangeInfo()
 *********************************************************************************************************************/
/*! \brief       Pass given range information to a processing pipe.
 *  \details     Uses the entry point associated with the given input type to pass the range information to the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the entry point.
 *  \param[in]   RangeAddress   Start address of the range to be passed to the pipe.
 *  \param[in]   RangeLength    Length of the range to be passed to the pipe.
 *  \return      E_OK           Range information successfully passed to pipe.
 *  \return      E_NOT_OK       Range information could not be passed to pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteRangeInfo(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_AddressType RangeAddress,
  vSwUpdM_LengthType RangeLength);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteProcessOperation()
 *********************************************************************************************************************/
/*! \brief       Pass given process operation to a processing pipe.
 *  \details     Uses the entry point associated with the given input type to pass the process operation to the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the entry point.
 *  \param[in]   EntityIds      The process operation to be passed to the pipe.
 *  \return      E_OK           Process operation successfully passed to pipe.
 *  \return      E_NOT_OK       Process operation could not be passed to pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteProcessOperation(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_ProcNodeOperationType ProcOperation);

#if (VSWUPDM_EXTDATAINPUT == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteExtInputData()
 *********************************************************************************************************************/
/*! \brief       Add data to a pipe.
 *  \details     Request a buffer from StreamProc for data, put data into it and release buffer.
 *  \param[in]   PipeId       Pipe where to add data.
 *  \param[in]   ExtDataInput EntryPoint of pipe where to add data.
 *  \param[in]   DataPtr      Pointer to data.
 *  \param[in]   Length       Length of data.
 *  \return      E_OK         On success. (Length = 0 is also accepted)
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteExtInputData(
  vStreamProc_PipeIdType PipeId,
  vSwUpdM_ExtDataInputIterType ExtDataInput,
  vSwUpdM_ConstDataPointerType DataPtr,
  vSwUpdM_LengthType Length);
#endif

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetExitPoint()
 *********************************************************************************************************************/
/*! \brief       Prepare and get info of exit point.
 *  \details     -
 *  \param[in]   PipeId         ID of the pipe.
 *  \param[in]   ExitPointId    ID of the exit point.
 *  \param[in]   DataTypeId     Expected datatype of the exit point.
 *  \param[out]  ExitPointInfo  Reference to found exit point.
 *  \return      E_OK           Exit point successfully retrieved from pipe.
 *  \return      E_NOT_OK       Exit point could not be retrieved from pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType ExitPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestExitPoint()
 *********************************************************************************************************************/
/*! \brief       Prepare exit point and request data.
 *  \details     -
 *  \param[in]   PipeId         ID of the pipe.
 *  \param[in]   ExitPointId    ID of the exit point
 *  \param[in]   DataTypeId     Expectedd datatype of the exit point.
 *  \param[in]   Length         Length of requested data.
 *  \param[out]  ExitPointInfo  Reference to found exit point.
 *  \return      E_OK           Entry point successfully retrieved from pipe.
 *  \return      E_NOT_OK       Entry point could not be retrieved from pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType ExitPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType Length,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestInternalExitPoint()
 *********************************************************************************************************************/
/*! \brief       Request requested data from a processing pipe exit.
 *  \details     Uses the exit  point associated with the given output type to retrieve the entry from the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the exit point.
 *  \param[in]   Length         Minimal request length
 *  \param[out]  ExitPointInfo
 *  \return      E_OK           Entry successfully retrieved from pipe.
 *  \return      E_NOT_OK       Entry could not be retrieved from pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestInternalExitPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vStreamProc_LengthType Length,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadResult()
 *********************************************************************************************************************/
/*! \brief       Evaluate result of processing pipe.
 *  \details     Uses the exit point associated with the given output type to retrieve the result from the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the exit point.
 *  \return      VSWUPDM_E_STREAM_OPERATION_FAILED  No processing pipe result available.
 *  \return      else                               Result available at exit point of processing pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadResult(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadRange()
 *********************************************************************************************************************/
/*! \brief       Retrieve a range from a processing pipe.
 *  \details     Uses the exit point associated with the given output type to retrieve the range from the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the exit point.
 *  \param[in]   Length         The number of ranges to read.
 *  \param[out]  RangeInfo      Pointer to read ranges.
 *  \return      E_OK                               On success.
 *  \return      VSWUPDM_E_STREAM_OPERATION_FAILED  No processing pipe result available.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadRange( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vStreamProc_LengthType Length,
  vSwUpdM_RangeInfoStreamPtrType RangeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadProcessOperation()
 *********************************************************************************************************************/
/*! \brief       Retrieve process operation from a processing pipe.
 *  \details     Uses the exit point associated with the given output type to retrieve the process operation from
 *               the pipe.
 *  \param[in]   DataProcessId  The ID of the data process which identifies the processing pipe.
 *  \param[in]   Type           The type of the exit point.
 *  \param[out]  ProcOperation  Pointer to the retrieved process operation.
 *  \return      E_OK           Process operation successfully retrieved from pipe.
 *  \return      E_NOT_OK       Process operation could not be retrieved from pipe.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadProcessOperation(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vSwUpdM_ProcNodeOperationPtrType ProcOperation);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_Init_InitEntityData()
 *********************************************************************************************************************/
/*! \brief       Initializes the entity data with default values.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitEntityData(void);

/**********************************************************************************************************************
 *  vSwUpdM_Part_IsPartitionSwappable()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified partition is swappable.
 *  \details     -
 *  \param[in]   Id            The partition ID to be checked.
 *  \return      FALSE         The partition isn't swappable.
 *  \return      TRUE          The partition is swappable.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionSwappable(
  vSwUpdM_PartitionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleErasable()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified module is completely erasable.
 *  \details     -
 *  \param[in]   Id            The module id to be verified.
 *  \return      FALSE         At least one region assigned to the specified module is not erasable.
 *  \return      TRUE          The module is completely erasable.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleErasable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleReadable()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified module is completely erasable.
 *  \details     -
 *  \param[in]   Id            The module id to be verified.
 *  \return      FALSE         At least one region assigned to the specified module is not readable.
 *  \return      TRUE          The module is completely readable.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleReadable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleWritable()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified module is completely writable.
 *  \details     -
 *  \param[in]   Id            The module id to be verified.
 *  \return      FALSE         At least one region assigned to the specified module is not writable.
 *  \return      TRUE          The module is completely writable.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleWritable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetSegmentIdByRange()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     The segment is specified by a range.
 *  \param[out]  SegmentId     The id of the segment within the specified range.
 *  \param[in]   StartAddress  The start address of the range.
 *  \param[in]   Length        The length of the range.
 *  \param[in]   Queue         The segment queue which should be searched for a match.
 *  \return      E_OK          A single segment was found within the range.
 *  \return      E_NOT_OK      No or multiple segments were found within the range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetSegmentIdByRange(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  P2CONST(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_CONST) Queue);

/**********************************************************************************************************************
 *  vSwUpdM_Init_EntityIdsDefaults()
 *********************************************************************************************************************/
/*! \brief          Initializes an entity ID structure with default values.
 *  \details        -
 *  \param[in,out]  EntityIds   Pointer to entity ID structure to be initialized.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_EntityIdsDefaults(vSwUpdM_EntityIdsPtrType EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_Part_IsPartitionStateSet()
 *********************************************************************************************************************/
/*! \brief       Checks if the current partition state against a given value.
 *  \details     -
 *  \param[in]   CurrentState  The current partition state to be checked.
 *  \param[in]   CheckState    OR-combination of the partition state(s) to be checked against.
 *  \return      FALSE         The partition state doesn't match the given value.
 *  \return      TRUE          The partition state matches the given value.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionStateSet(
  vSwUpdM_PartitionStateType CurrentState,
  vSwUpdM_PartitionStateType CheckState);

/**********************************************************************************************************************
 *  vSwUpdM_Part_GetIdByState()
 *********************************************************************************************************************/
/*! \brief       Looks up the partition ID from the partition table for a given state.
 *  \details     -
 *  \param[out]  PartitionId          The ID of the partition matching the given state.
 *  \param[in]   PartitionState       The state of the partition which should be looked up.
 *  \return      E_OK                 Partition id could be retrieved.
 *  \return      else                 Partition id could not be retrieved.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_GetIdByState(
  P2VAR(vSwUpdM_PartitionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionId,
  vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_Module_InitRegions()
 *********************************************************************************************************************/
/*! \brief       Initialize regions of selected module.
 *  \details     Reads static regions of module and restores persisted region states.
 *               Part of operation performed in asynchronous job.
 *               Restore of persisted region states handled by (potentially asynchronous) user callout.
 *  \param[in]   Id                   The ID of the module whose regions should be initialized.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Initialization of regions successfully initiated.
 *  \return      else                 Initialization of regions could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_InitRegions(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_InitSegments()
 *********************************************************************************************************************/
/*! \brief       Initialize segments of opened module.
 *  \details     Reads static segments of module and restores persisted segment states when requested.
 *  \param[in]   RestoreSegments      TRUE Restore the persisted segment information.
 *                                    FALSE Initialize dynamic segment information with default values.
 *  \param[in]   InitStaticSegments   TRUE Initialize static segments of module.
 *                                    FALSE Skip initialization of static segments of module. Only create free segments
 *                                      for all regions of module.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Source               Source node of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Initialization of segments successfully initiated.
 *  \return      else                 Initialization of segments could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_InitSegments(
  vSwUpdM_RestoreSegmentsType RestoreSegments,
  boolean InitStaticSegments,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_OpenModule()
 *********************************************************************************************************************/
/*! \brief       Open the selected module.
 *  \details     Initializes the regions and segments of the requested module.
 *  \param[in]   Id                   The ID of the module which should be opened.
 *  \param[in]   RestoreSegments      TRUE Restore the persisted segment information.
 *                                    FALSE Initialize dynamic segment information with default values.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Source               Source node of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Opening of module successfully initiated.
 *  \return      else                 Opening of module could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_OpenModule(
  vSwUpdM_ModuleIdType Id,
  boolean RestoreSegments,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_CloseModule()
 *********************************************************************************************************************/
/*! \brief       Close the selected module.
 *  \details     -
 *  \param[in]   Id                   The ID of the module which should be closed.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Source               Source node of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Closing of module successfully initiated.
 *  \return      else                 Closing of module could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_CloseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_GetRelativePartitionIdxByPartition()
 *********************************************************************************************************************/
/*! \brief       Provides the relative partition index of the requested partition.
 *  \details     Returned index is the relative index of the partition within the partition group assigned to the module.
 *  \param[out]  RelativePartitionIdx   The relative index inside of the requested partition.
 *  \param[in]   ModuleId               The id of the requested module.
 *  \param[in]   PartitionId            The id of the requested partition.
 *  \return      E_NOT_OK               Partition isn't part of the partition group.
 *  \return      E_OK                   The operation succeeded; the data is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetRelativePartitionIdxByPartition(
  P2VAR(vSwUpdM_PartitionIdxType, AUTOMATIC, VSWUPDM_APPL_VAR) RelativePartitionIdx,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleInstantiatedInPartition()
 *********************************************************************************************************************/
/*! \brief       Check whether the requested module is instantiated in the requested partition.
 *  \details     -
 *  \param[in]   ModuleId         The id of the requested module.
 *  \param[in]   PartitionId      The id of the requested partition.
 *  \return      FALSE            Module isn't instantiated in partition.
 *  \return      TRUE             Module is instantiated in partition.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleInstantiatedInPartition(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_Module_EraseModule()
 *********************************************************************************************************************/
/*! \brief       Erase all regions of given module.
 *  \details     Actual operation performed in asynchronous job.
 *  \param[in]   Id                   The ID of the module which should be erased.
 *  \param[in]   Priority             The priority with which the job shall be spawned.
 *  \param[in]   UpdateResumeInfo     Select whether resume information shall be updated.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source instance of the erase request.
 *  \return      E_OK                 Erase of module successfully initiated.
 *  \return      else                 Erase of module could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_EraseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_QueuePrioType Priority,
  boolean UpdateResumeInfo,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_FinalizeModule()
 *********************************************************************************************************************/
/*! \brief       Triggers the finalization of the given module.
 *  \details     Actual operation performed in asynchronous job.
 *  \param[in]   Id                   The ID of the module which should be synchronized.
 *  \param[in]   Source               The SOurce of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Synchronization of module successfully initiated.
 *  \return      else                 Synchronization of module could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_FinalizeModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_SyncModule()
 *********************************************************************************************************************/
/*! \brief       Synchronize the given module.
 *  \details     Replaces the instance of the given module in the opened partition, with the one in from the active
 *               partition, when the latter is newer.
 *  \param[in]   ModuleId             The ID of the module which should be synchronized.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   UpdateResumeInfo     Select whether resume information shall be updated.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Synchronization of module successfully initiated.
 *  \return      else                 Synchronization of module could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_SyncModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  boolean UpdateResumeInfo,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_ProcessModule()
 *********************************************************************************************************************/
/*! \brief       Process the given module.
 *  \details     Triggers the data process set by the service function.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines module instance, priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   UpdateResumeInfo     Select whether resume information shall be updated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Module_ProcessModule(
  vSwUpdM_JobPtrType ParentJob,
  boolean UpdateResumeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Region_CheckProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief       Checks the programming attempts counter against the maximum allowed value.
 *  \details     Compares the programming attempts of the region instance against the configured maximum of the module
 *               the region is assigned to.
 *  \param[in]   ModuleId             The ID of the module the region is assigned to.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \return      E_OK                                     Maximum number of programming attempts not exceeded.
 *  \return      VSWUPDM_E_PROGRAMMING_ATTEMPTS_EXCEEDED  Maximum number of programming attempts exceeded.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_CheckProgrammingAttempts(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx);

/**********************************************************************************************************************
 *  vSwUpdM_Region_EraseRegion()
 *********************************************************************************************************************/
/*! \brief       Erase given region.
 *  \details     Actual operation performed in asynchronous job.
 *  \param[in]   EntityIds            Entity IDs identifying the region to be erased.
 *                                    At least PartitionId, ModuleId, RegionId and RegionIdx must be set.
 *  \param[in]   UpdateResumeInfo     Select whether resume information shall be updated.
 *  \param[in]   Operation            The operation type passed to the spawned job.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Erase of region successfully initiated.
 *  \return      else                 Erase of region could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_EraseRegion(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  boolean UpdateResumeInfo,
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_SearchQueueHandle()
 *********************************************************************************************************************/
/*! \brief       Searches segment in segment queue by StartAddress.
 *  \param[in]   QueueHandle  Segment queue to search.
 *  \param[in]   StartAddress Address to search for.
 *  \return      E_NOT_OK      Segment not found.
 *  \return      E_OK          Segment found.
 *  \details      -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_SearchQueueHandle(
  P2VAR(vSwUpdM_QueueHandleType, AUTOMATIC, VSWUPDM_APPL_VAR) QueueHandle,
  vSwUpdM_AddressType StartAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_SearchSegment()
 *********************************************************************************************************************/
/*! \brief       Search for existing segment.
 *  \details     The segment which lies at the requested address is provided.
 *  \param[out]  SegmentId     The ID of the segment at the requested address.
 *  \param[in]   StartAddress  The requested start address.
 *  \return      E_NOT_OK      No segment found at given address.
 *  \return      E_OK          Segment found at given address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_SearchSegment(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  vSwUpdM_AddressType StartAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_AddSegment()
 *********************************************************************************************************************/
/*! \brief       Adds a segment to the covering region corresponding to the specified range.
 *  \details     -
 *  \param[in,out] SegmentInfo The segment info containing the range of the segment.
 *  \param[in]   SegmentClass  The class of the segment.
 *               VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE to add a memory region.
 *               VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED to add a reserved area.
 *               VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED to add a segment for data to be updated.
 *               VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP is not allowed.
 *  \param[in]   RemoteUpdateRequired
 *  \return      E_OK          The creation succeeded.
 *  \return      E_NOT_OK      The creation failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  vSwUpdM_AlignGranularityType AlignGranularity,
  boolean RemoteUpdateRequired);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_ConcludeSegment()
 *********************************************************************************************************************/
/*! \brief       Conclude the writing to a segment by updating the covered range if necessary.
 *  \details     When the segment is of class "used" with dynamic length didn't use the complete available range,
 *               the unused area will be released as "free" again. Either by increasing an existing adjacent free
 *               segment or creating a new free segment. Finally the length and end address of the given segment will
 *               be trimmed according to the last written address.
 *  \param[in,out] Segment          The segment which shall be concluded.
 *  \param[in]   SucceedingAddress  The address directly behind the end of the segment, including any padding.
 *  \param[in]   WriteAddress       The address directly behind the last written data, excluding any padding.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_ConcludeSegment(
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_AddressType SucceedingAddress,
  vSwUpdM_AddressType WriteAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_OpenSegment()
 *********************************************************************************************************************/
/*! \brief       Opens the specified segment.
 *  \details     -
 *  \param[in]   Id                   The identifier of the segment.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Source               Source node of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_OpenSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_CloseSegment()
 *********************************************************************************************************************/
/*! \brief       Closes the specified segment.
 *  \details     -
 *  \param[in]   Id                   The identifier of the segment.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_CloseSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_GetAttributes()
 *********************************************************************************************************************/
/*! \brief       Returns the Attributes of a Module
 *  \details     -
 *  \param[out]  ModuleState    The state of the module instance in the requested partition.
 *  \param[in]   ModuleId       The id of the requested module.
 *  \param[in]   PartitionId    The id of the requested partition.
 *  \return      E_NOT_OK       Partition isn't part of the partition group assigned to the module.
 *  \return      E_OK           The operation succeeded; the data is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetAttributes(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_ModuleDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) Attributes);

/**********************************************************************************************************************
 *  vSwUpdM_Module_CheckProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief       Checks the programming attempts counter against the maximum allowed value.
 *  \details     Compares the programming attempts of the module instance against the configured maximum of the module.
 *  \param[in]   ModuleId             The id of the requested module.
 *  \param[in]   PartitionId          The id of the requested partition.
 *  \return      E_OK                                     Maximum number of programming attempts not exceeded.
 *  \return      VSWUPDM_E_PROGRAMMING_ATTEMPTS_EXCEEDED  Maximum number of programming attempts exceeded.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_CheckProgrammingAttempts(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_Region_GetRegionIdx()
 *********************************************************************************************************************/
/*! \brief       Returns the relative index of the given region id in the open module.
 *  \details     Requested region must be part of the currently opened module.
 *  \param[in]   Id                   The region id of the requested region.
 *  \return      VSWUPDM_INVALID_ID   No matching region was found.
 *  \return      Relative index of region in the open module.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(vSwUpdM_RegionIdxType, VSWUPDM_CODE) vSwUpdM_Region_GetRegionIdx(vSwUpdM_RegionIdType RegionId);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_IsSegmentWritable()
 *********************************************************************************************************************/
/*! \brief       Checks if the segment is in a valid state for writing to it.
 *  \details     Writing to segment is allowed when segment is either "erased" or "pending" and segment is clean.
 *               The latter applies when all previous write operations during this cycle were successful.
 *  \param[in]   Id            The segment id to be checked.
 *  \return      FALSE         Writing to segment isn't allowed.
 *  \return      TRUE          Writing to segment is allowed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentWritable(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetSegmentIdByStartAddress()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     The segment is specified by the StartAddress.
 *  \param[out]  SegmentId     The id of the segment within the specified range.
 *  \param[in]   StartAddress  The start address of the range.
 *  \param[in]   Queue         The segment queue which should be searched for a match.
 *  \return      E_OK          A single segment was found within the range.
 *  \return      E_NOT_OK      No segments were found within the range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetSegmentIdByStartAddress(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  P2CONST(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_CONST) Queue);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_General_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update and persist update state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout.
 *  \param[in]   State                The new global update state.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Update of update state could not be initiated.
 *  \return      else                 Update of update state successfully initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_General_UpdateState(
  vSwUpdM_UpdateStateType State,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Part_UpdateValid()
 *********************************************************************************************************************/
/*! \brief       Update and persist partition validity.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of validity handled by (potentially asynchronous) user callout. Volatile partition validity
 *               updated when finished successfully.
 *  \param[in]   Id                   The ID of the partition whose validity should be updated.
 *  \param[in]   State                The state of the partition whose validity should be updated.
 *  \param[in]   Valid                The new validity of the partition.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               The source node of the request.
 *  \return      E_OK                 Update of partition validity successfully initiated.
 *  \return      else                 Update of partition validity could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_UpdateValid(
  vSwUpdM_PartitionIdType Id,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_ValidType Valid,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Part_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update and persist partition state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile partition state
 *               updated when finished successfully.
 *  \param[in]   Id             The ID of the partition whose state should be updated.
 *  \param[in]   AffectedState  The (non-combined) state by which the partition whose state should be updated was opened.
 *  \param[in]   State          The new state of the partition.
 *  \return      E_OK           Update of partition state successfully initiated.
 *  \return      else           Update of partition state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_UpdateState(
  vSwUpdM_PartitionIdType Id,
  vSwUpdM_PartitionStateType AffectedState,
  vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_Module_GetProgrammingAttemptsByPartition()
 *********************************************************************************************************************/
/*! \brief       Provides the programming attempt counter of the module instance in the requested partition.
 *  \details     -
 *  \param[out]  ProgrammingAttempts  The programming attempt counter of the module instance in the requested partition.
 *  \param[in]   ModuleId             The id of the requested module.
 *  \param[in]   PartitionId          The id of the requested partition.
 *  \return      E_NOT_OK       Partition isn't part of the partition group assigned to the module.
 *  \return      E_OK           The operation succeeded; the data is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetProgrammingAttemptsByPartition(
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_Module_GetStateByPartition()
 *********************************************************************************************************************/
/*! \brief       Provides the state of the module instance in the requested partition.
 *  \details     -
 *  \param[out]  ModuleState    The state of the module instance in the requested partition.
 *  \param[in]   ModuleId       The id of the requested module.
 *  \param[in]   PartitionId    The id of the requested partition.
 *  \return      E_NOT_OK       Partition isn't part of the partition group assigned to the module.
 *  \return      E_OK           The operation succeeded; the data is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetStateByPartition(
  P2VAR(vSwUpdM_ModuleStateType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_Module_UpdateValid()
 *********************************************************************************************************************/
/*! \brief       Update and persist module validity.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of validity handled by (potentially asynchronous) user callout. Volatile module validity
 *               updated when finished successfully.
 *  \param[in]   PartitionState       The state of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose validity should be updated.
 *  \param[in]   Valid                The new validity of the partition.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Update of module validity successfully initiated.
 *  \return      else                 Update of module validity could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateValid(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ValidType Valid,
  vSwUpdM_RevisionUpdateType RevisionUpdate,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Module_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update module state.
 *  \details     Attributes of module will be marked "dirty" when any value was updated by the request.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose state should be updated.
 *  \param[in]   State                The updated module state to be set.
 *  \return      E_OK                 Update of module state successfully initiated.
 *  \return      else                 Update of module state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_Module_PersistState()
 *********************************************************************************************************************/
/*! \brief       Persist pending module state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile module state
 *               updated when finished successfully.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the module resides in.
 *  \param[in]   PartitionState       The state of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose state should be updated.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Persisting of module state successfully initiated.
 *  \return      else                 Persisting of module state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_UpdateAndPersistState()
 *********************************************************************************************************************/
/*! \brief       Update and persist module state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile module state
 *               updated when finished successfully.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the module resides in.
 *  \param[in]   PartitionState       The state of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose state should be updated.
 *  \param[in]   State                The updated module state to be set.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Update of module state successfully initiated.
 *  \return      else                 Update of module state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateAndPersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_PersistStateAndConfirm()
 *********************************************************************************************************************/
/*! \brief       Persist module state. Trigger a Confirmation if finished.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile module state
 *               updated when finished successfully.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the module resides in.
 *  \param[in]   PartitionState       The state of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose state should be updated.
 *  \param[in]   ConfirmationService  Defines which confirmation shall be sent.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Update of module state successfully initiated.
 *  \return      else                 Update of module state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PersistStateAndConfirm(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Module_UpdateProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief       Updates the programming attempts in the pending module attributes.
 *  \details     Prepares the pending attributes structure when necessary and marks them as dirty.
 *               Value will only be updated when it is larger than the current one.
 *  \param[in]   ProgrammingAttempts  The programming attempt counter.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the module resides in.
 *  \param[in]   ModuleId             The ID of the module whose state should be updated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateProgrammingAttempts(
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_Region_UpdateEraseAddress()
 *********************************************************************************************************************/
/*! \brief       Updates the erase address.
 *  \details     Prepares the pending attributes structure when necessary and marks them as dirty.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \param[in]   EraseAddress         The erase address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateEraseAddress(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_AddressType EraseAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Region_UpdateAndPersistState()
 *********************************************************************************************************************/
/*! \brief       Update and persist region state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile module state
 *               updated when finished successfully.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the region resides in.
 *  \param[in]   ModuleId             The ID of the module the region is assigned to.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \param[in]   State                The updated region state to be set.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Update of region state successfully initiated.
 *  \return      else                 Update of region state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_UpdateAndPersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_RegionStateType State,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Region_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update region state.
 *  \details     -
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \param[in]   State                The updated region state to be set.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateState(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_RegionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_Region_UpdateProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief       Updates the programming attempts in the pending region attributes.
 *  \details     Prepares the pending attributes structure when necessary and marks them as dirty.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \param[in]   ProgrammingAttempts  The programming attempt counter.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateProgrammingAttempts(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts);

/**********************************************************************************************************************
 *  vSwUpdM_Region_IncProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief       Increments the programming attempts by one.
 *  \details     Prepares the pending attributes structure when necessary and marks them as dirty.
 *               Updates the programming attempt counter of the module instance when necessary.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the region resides in.
 *  \param[in]   ModuleId             The ID of the module the region is assigned to.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \return      E_OK                 Programming attempt counter successfully incremented.
 *  \return      E_NOT_OK             Incrementing programming attempt counter failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_IncProgrammingAttempts(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update and persist segment state.
 *  \details     Updates the segment state and mark the attributes as dirty.
 *  \param[in,out]  Segment           The segment to be updated.
 *  \param[in]   State                The updated segment state to be set.
 *  \return      TRUE                 Segment attributes are dirty.
 *  \return      FALSE                Segment attributes are clean.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_UpdateState(
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_SegmentStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_UpdateAndPersistState()
 *********************************************************************************************************************/
/*! \brief       Update and persist segment state.
 *  \details     Enforces immediate persisting.
 *  \param[in]   SegmentId            The ID of the segment.
 *  \param[in]   State                The updated segment state to be set.
 *  \param[in]   Source               The Source of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Segment state successfully updated.
 *  \return      else                 Update of segment state failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_UpdateAndPersistState(
  vSwUpdM_SegmentIdType SegmentId,
  vSwUpdM_SegmentStateType State,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_UpdateAndPersistStateAndConfirm()
 *********************************************************************************************************************/
/*! \brief      Update and persist segment state and trigger a confirmation if update has finished.
 *  \details     Enforces immediate persisting.
 *  \param[in]   SegmentId            The ID of the segment.
 *  \param[in]   ConfirmationService  Confirmation service to be sent after update has finished.
 *  \param[in]   State                The updated segment state to be set.
 *  \param[in]   Source               The Source of the request.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Segment state successfully updated.
 *  \return      else                 Update of segment state failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_UpdateAndPersistStateAndConfirm(
  vSwUpdM_SegmentIdType SegmentId,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_SegmentStateType State,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetApparentAddress()
 *********************************************************************************************************************/
/*! \brief       Evaluate apparent address in context of segment.
 *  \details     The addresses referencing an internal segment structure take additional padding into account.
 *               This may cause confusion, when reporting back the information to the upper-layer, as the address
 *               may lay outside of the expected range.
 *               This function limits the reported address to the apparent size of the segment.
 *  \param[in]   Segment            Pointer to segment object.
 *  \param[in,out] ApparentAddress  Address which shall be limited to range of given segment.
 *  \param[in]   Overflow           Include address directly behind actual end address of segment in range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_GetApparentAddress(
  vSwUpdM_VarSegmentsPtrType Segment,  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ApparentAddress,
  boolean Overflow);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetApparentWriteAddress()
 *********************************************************************************************************************/
/*! \brief       Evaluate apparent write address of segment.
 *  \details     The write address stored in the internal segment structure takes additional padding into account.
 *               This may cause confusion, when reporting back the information to the upper-layer, as the address
 *               may lay outside of the expected range.
 *               This function limits the reported address to the apparent size of the segment.
 *  \param[in]   Segment          Pointer to segment object.
 *  \param[out]  WriteAddress     Resulting apparent write address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_GetApparentWriteAddress(
  vSwUpdM_VarSegmentsPtrType Segment,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) WriteAddress);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_ResetState()
 *********************************************************************************************************************/
/*! \brief       Reset resume information.
 *  \details     Resume information is reset to default state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_ResetState(void);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_IncreaseAddress()
 *********************************************************************************************************************/
/*! \brief      Increase Resume Address
 *  \details     Resume Address is increased by offset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_IncreaseAddress(
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_AddressType Offset);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_EvaluateEntityIds()
 *********************************************************************************************************************/
/*! \brief       Evaluate entity IDs based on current resume information.
 *  \details     Uses partition ID from resume information and looks for all other entities at resume address,
 *               if valid.
 *  \param[out]  EntityIds    Pointer to entity ID structure.
 *  \return      E_OK         Resume information is valid and entity IDs were evaluated.
 *  \return      E_NOT_OK     Resume information is not valid and entity IDs couldn't be evaluated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_EvaluateEntityIds(
  vSwUpdM_EntityIdsPtrType EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_CompareEntities()
 *********************************************************************************************************************/
/*! \brief       Compare given entities against entities addressed by resume information.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ResumeInfo_CompareEntities(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_InitState()
 *********************************************************************************************************************/
/*! \brief       Initialize resume information.
 *  \details     Used for setting initial values at start of a resumable operation.
 *  \param[in]   EntityIds        Entity IDs affected by the started operation.
 *  \param[in]   CurrentService   Service ID of started operation.
 *  \param[in]   Address          Address affected by running operation.
 *                                Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   IsAddressValid   TRUE Value given in Address is valid.
 *                                FALSE Value given in Address is irrelevant and won't be used.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_InitState(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_AddressType Address,
  vSwUpdM_ValidType IsAddressValid);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_UpdateWriteService()
 *********************************************************************************************************************/
/*! \brief       Initialize resume information for ProcessStreamData service.
 *  \details     Used for setting initial values at start of ProcessStreamData service, including all other services
 *               included in this step (StartStream, EndStream and FinalizeSegment).
 *  \param[in]   PartitionId    ID of used partition.
 *  \param[in]   Segment        The segment which is processed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateWriteService(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_ServiceIdType ServiceId);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_InitModuleService()
 *********************************************************************************************************************/
/*! \brief       Initialize resume information for module specific services.
 *  \details     Used for setting initial values at start of a resumable module operation.
 *  \param[in]   Id               The ID of the module.
 *  \param[in]   CurrentService   Service ID of started operation.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_InitModuleService(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType CurrentService);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_UpdateAndPersistState()
 *********************************************************************************************************************/
/*! \brief       Update and persist state of resume information.
 *  \details     Enforces immediate persisting.
 *  \param[in]   PartitionState       State of used partition.
 *                                    Pass VSWUPDM_PART_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   CurrentService       Service ID of current operation.
 *                                    Pass VSWUPDM_SID_NONE when value shouldn't be updated.
 *  \param[in]   ServiceState         Current state of running operation.
 *                                    Pass VSWUPDM_RESUME_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   MemoryAddress        Address in memory affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   StreamAddress        Address in data stream affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   TriggerAddress       Actual address which is currently processed by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   IsAddressValid       TRUE Value given in Address is valid.
 *                                    FALSE Value given in Address is irrelevant and won't be updated.
 *  \param[in]   Source               Source node of the request.
 *  \return      else                 Persisting of resume information could not be initiated.
 *  \return      E_OK                 Persisting of resume information successfully initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateAndPersistState(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm()
 *********************************************************************************************************************/
/*! \brief       Update and persist state of resume information.
 *  \details     Enforces immediate persisting.
 *  \param[in]   PartitionState       State of used partition.
 *                                    Pass VSWUPDM_PART_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   CurrentService       Service ID of current operation.
 *                                    Pass VSWUPDM_SID_NONE when value shouldn't be updated.
 *  \param[in]   ServiceState         Current state of running operation.
 *                                    Pass VSWUPDM_RESUME_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   MemoryAddress        Address in memory affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   StreamAddress        Address in data stream affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   TriggerAddress       Actual address which is currently processed by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   IsAddressValid       TRUE Value given in Address is valid.
 *                                    FALSE Value given in Address is irrelevant and won't be updated.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in]   Source               Source node of the request.
 *  \return      else                 Persisting of resume information could not be initiated.
 *  \return      E_OK                 Persisting of resume information successfully initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_PersistForNextCheckpoint()
 *********************************************************************************************************************/
/*! \brief       Update and persist resume information for next checkpoint.
 *  \details     Prepares the resume information for an unintended reset before the next checkpoint is reached.
 *  \param[in]   PartitionId    ID of used partition.
 *  \param[in]   SegmentId      ID of the segment which is currently processed.
 *  \param[in]   Address        The currently processed address.
 *  \param[in]   WritePending   Define whether request is triggered by a pending write operation or not:
 *                              TRUE: Pending write. Address represents the last written address.
 *                              FALSE: Write not pending. Address represents the next address to be written.
 *  \param[in]   Source         Source node of the request.
 *  \return      E_OK           Persisting of resume information successfully initiated.
 *  \return      else           Persisting of resume information could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistForNextCheckpoint(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_SegmentIdValueType SegmentId,
  vSwUpdM_AddressType Address,
  boolean WritePending,
  vSwUpdM_NodeIterType Source);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_General_UpdateGlobalState()
 *********************************************************************************************************************/
/*! \brief       Update the global state after job execution.
 *  \details     Prepare for next main function cycle or fall back any idle state if no more jobs are pending.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_UpdateGlobalState(void);

/**********************************************************************************************************************
 *  vSwUpdM_General_IsModuleInitialized()
 *********************************************************************************************************************/
/*! \brief       Checks if the vSwUpdM is completely initialized.
 *  \details     Initialization isn't finished after calling vSwUpdM_Init(). Instead additional asynchronous operations
 *               are necessary to initialize entity state.
 *  \return      FALSE         Module is not initialized yet.
 *  \return      TRUE          Module is already initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_General_IsModuleInitialized(void);

/**********************************************************************************************************************
 *  vSwUpdM_State_Suspend()
 *********************************************************************************************************************/
/*! \brief       Suspend all pending operations.
 *  \details     -
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Suspend of pending operations successfully initiated.
 *  \return      else                 Suspend of pending operations could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_State_Suspend(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_State_Resume()
 *********************************************************************************************************************/
/*! \brief       Suspend all pending operations.
 *  \details     -
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Suspend of pending operations successfully initiated.
 *  \return      else                 Suspend of pending operations could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_State_Resume(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Init_Start()
 *********************************************************************************************************************/
/*! \brief       Start initialization of component.
 *  \details     Initialize memory structure and spawn "init component" job.
 *               Actual operation performed in asynchronous job.
 *               Evaluation of states handled by (potentially asynchronous) user callouts.
 *  \return      E_OK                 Initialization successfully initiated.
 *  \return      else                 Initialization could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Init_Start(vSwUpdM_NodeIterType Source);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_General_HandleDetError()
 *********************************************************************************************************************/
/*! \brief       Handle DET error reporting.
 *  \details     Report any error to DET when development error reporting is enabled.
 *               Otherwise does nothing.
 *  \param[in]   ServiceId      The ID of the service function.
 *  \param[in]   ErrorId        The error code to be reported.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_HandleDetError(
  vSwUpdM_ServiceIdType ServiceId,
  vSwUpdM_ErrorCode ErrorId);

/**********************************************************************************************************************
 *  vSwUpdM_Part_IsPartitionHandleValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified partition handle is valid.
 *  \details     -
 *  \param[in]   Handle        The partition handle to be checked.
 *  \return      FALSE         The handle is invalid.
 *  \return      TRUE          The handle is valid.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionHandleValid(
  vSwUpdM_PartitionHandleIdType Handle);

/**********************************************************************************************************************
 *  vSwUpdM_Part_IsPartitionStateValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified partition state is valid.
 *  \details     -
 *  \param[in]   PartState     The partition state to be checked.
 *  \return      FALSE         The partition state is invalid.
 *  \return      TRUE          The partition state is valid.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionStateValid(
  vSwUpdM_PartitionStateType PartState);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleHandleValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified module handle id is valid.
 *  \details     -
 *  \param[in]   Handle        The module handle to be verified.
 *  \return      FALSE         Handle is invalid.
 *  \return      TRUE          Handle is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleHandleValid(vSwUpdM_ModuleHandleIdType Handle);

/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleIdValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified module id is valid.
 *  \details     -
 *  \param[in]   Id            The module id to be verified.
 *  \return      FALSE         Id is invalid.
 *  \return      TRUE          Id is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleIdValid(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Region_IsRegionHandleValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified region handle id is valid.
 *  \details     -
 *  \param[in]   Handle        The region handle id to be verified.
 *  \return      FALSE         Handle is invalid.
 *  \return      TRUE          Handle is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Region_IsRegionHandleValid(vSwUpdM_RegionHandleIdType Handle);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_IsSegmentIdAllowed()
 *********************************************************************************************************************/
/*! \brief       Checks if the operation on the specified segment id is allowed.
 *  \details     Segment id is allowed if either no segment is opened yet or the respective segment is already opened.
 *  \param[in]   Id            The segment id to be checked.
 *  \return      FALSE         Operation on segment is not allowed.
 *  \return      TRUE          Operation on segment is allowed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentIdAllowed(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 * vSwUpdM_General_CommonNegDetChecks()
 *********************************************************************************************************************/
/*! \brief       Perform most common DET checks.
 *  \details     Checks against negative initialization and entity states.
 *  \param[out]  ErrorId        VSWUPDM_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                              Error code          Otherwise.
 *  \param[in]   DetChecks      VSWUPDM_COMMON_DET_CHECK_INITIALIZED  Check that module is initialized.
 *                              VSWUPDM_COMMON_DET_CHECK_PARTITION    Perform all previous checks and
 *                                                                    check that a partition is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_MODULE       Perform all previous checks and
 *                                                                    check that a module is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_SEGMENT      Perform all previous checks and
 *                                                                    check that a segment is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_STREAM       Perform all previous checks and
 *                                                                    check that a stream was started.
 *  \param[in]   StateCheck     Select which component states are accepted.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_CommonNegDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks,
  vSwUpdM_StateCheckType StateCheck);

#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_Module_IsModuleIdAllowed()
 *********************************************************************************************************************/
/*! \brief       Checks if the operation on the specified module id is allowed.
 *  \details     Module id is allowed if either no module is opened yet or the respective module is already opened.
 *  \param[in]   Id            The module id to be checked.
 *  \return      FALSE         Operation on module is not allowed.
 *  \return      TRUE          Operation on module is allowed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleIdAllowed(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Region_IsRegionIdValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified region id is valid.
 *  \details     -
 *  \param[in]   Id            The region id to be verified.
 *  \return      FALSE         Id is invalid.
 *  \return      TRUE          Id is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Region_IsRegionIdValid(vSwUpdM_RegionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_IsSegmentIdValid()
 *********************************************************************************************************************/
/*! \brief       Checks if the specified segment id is valid.
 *  \details     -
 *  \param[in]   Id            The segment id to be verified.
 *  \return      FALSE         Handle is invalid.
 *  \return      TRUE          Handle is valid.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentIdValid(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 * vSwUpdM_General_ExtNegDetChecks()
 *********************************************************************************************************************/
/*! \brief       Perform most common DET checks.
 *  \details     Checks against negative initialization and entity states and whether source instance is valid.
 *  \param[out]  ErrorId        VSWUPDM_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                              Error code          Otherwise.
 *  \param[in]   DetChecks      VSWUPDM_COMMON_DET_CHECK_INITIALIZED  Check that module is initialized.
 *                              VSWUPDM_COMMON_DET_CHECK_PARTITION    Perform all previous checks and
 *                                                                    check that a partition is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_MODULE       Perform all previous checks and
 *                                                                    check that a module is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_SEGMENT      Perform all previous checks and
 *                                                                    check that a segment is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_STREAM       Perform all previous checks and
 *                                                                    check that a stream was started.
 *  \param[in]   StateCheck     Select which component states are accepted.
 *  \param[in]   Source         The source instance of the request.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_ExtNegDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks,
  vSwUpdM_StateCheckType StateCheck,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 * vSwUpdM_General_CommonPosDetChecks()
 *********************************************************************************************************************/
/*! \brief       Perform most common DET checks.
 *  \details     Checks against positive initialization and entity states.
 *  \param[out]  ErrorId        VSWUPDM_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                              Error code          Otherwise.
 *  \param[in]   DetChecks      VSWUPDM_COMMON_DET_CHECK_INITIALIZED  Check that module isn't initialized.
 *                              VSWUPDM_COMMON_DET_CHECK_STREAM       Check that no stream is pending.
 *                              VSWUPDM_COMMON_DET_CHECK_SEGMENT      Perform all previous checks and
 *                                                                    check that no segment is opened.
 *                              VSWUPDM_COMMON_DET_CHECK_MODULE       Perform all previous checks and
 *                                                                    check that no module is opened.
 *
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_CommonPosDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks);
#endif

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_PersistStateAndConfirm()
 *********************************************************************************************************************/
/*! \brief       Persist resume information.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of resume information handled by (potentially asynchronous) user callout.
 *  \param[in]   Source               Source node of the request.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed
 *  \return      E_OK                 Persisting of resume information successfully initiated.
 *  \return      else                 Persisting of resume information could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistStateAndConfirm(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ServiceIdType ConfirmationService);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_PersistState()
 *********************************************************************************************************************/
/*! \brief       Persist resume information.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of resume information handled by (potentially asynchronous) user callout.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Persisting of resume information successfully initiated.
 *  \return      else                 Persisting of resume information could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistState(
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Part_PersistState()
 *********************************************************************************************************************/
/*! \brief       Persist all pending partition states.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile partition state
 *               updated when finished successfully.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \return      E_OK                 Update of partition state successfully initiated.
 *  \return      else                 Update of partition state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_PersistState(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob);

/**********************************************************************************************************************
 *  vSwUpdM_Region_PersistState()
 *********************************************************************************************************************/
/*! \brief       Persist region state.
 *  \details     Actual operation performed in asynchronous job.
 *               Persisting of state handled by (potentially asynchronous) user callout. Volatile module state
 *               updated when finished successfully.
 *  \param[in]   PartitionId          The ID of the partition in which the instance of the region resides in.
 *  \param[in]   ModuleId             The ID of the module the region is assigned to.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Persisting of region state successfully initiated.
 *  \return      else                 Persisting of region state could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_PersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_BookkeeperHandler()
 *********************************************************************************************************************/
/*! \brief       Dispatches requested operation to Bookkeeper (Persistor).
 *  \details     Based on the given operation type, the associated data is stored.
 *  \param[in]   Operation    The requested operation.
 *  \param[in]   OpStatus     The current status of the operation.
 *  \param[in]   EntityIds    The IDs of the referenced entities. Used sub-set dependent on operation.
 *  \return      E_OK               Operation successfully finished.
 *  \return      E_NOT_OK           Operation failed.
 *  \return      VSWUPDM_E_PENDING  Operation started, but still pending
 *  \return      VSWUPDM_E_BUSY     Operation could not be started, retry later with status VSWUPDM_OP_STATUS_INITIAL
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BookkeeperHandler(
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_OpStatusType State,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_Job_TriggerBookkeeper()
 *********************************************************************************************************************/
/*! \brief       Trigger bookkeeper.
 *  \details     Performs an initial call to the bookkeeper handler. If this synchronous operation isn't immediately
 *               finished (indicated by a "pending" or "busy" state), a "wait for bookkeeper operation" job is spawned.
 *               This job will poll the bookkeeper handler until a final positive or negative result is reported.
 *  \param[in]   Operation            The requested operation.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to bookkeeper result.
 *  \param[in]   Priority             Priority of the wait job, in case it is spawned.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_TriggerBookkeeper(
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_JobPtrType ParentJob);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetRegionOwnerGroupIndex()
 *********************************************************************************************************************/
/*! \brief       Returns Instance Group of the owners of a region.
 *  \details     -
 *  \param[in]   Id Id of a Segment
 *  \result      Instance Group of region owners.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(vSwUpdM_NodeGroupOwnersIdxOfRegionType, VSWUPDM_CODE) vSwUpdM_Segment_GetRegionOwnerGroupIndex(
  vSwUpdM_SegmentIdType Id);

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_Range_EraseRange()
 *********************************************************************************************************************/
/*! \brief       Erase given memory range.
 *  \details     Actual operation performed in asynchronous job.
 *  \param[in]   PartitionState       The state of the partition which should be altered.
 *  \param[in]   StartAddress         The start address of the range which should be erased.
 *  \param[in]   Length               The length of the range  which should be erased.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Erase of range successfully initiated.
 *  \return      else                 Erase of range could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_EraseRange(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/*!
* Internal comment removed.
 *
 *
 *
 *
*/
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_RemoteEvalStreamDataRequest
 *********************************************************************************************************************/
/*! \brief       Evaluate possible responses to remote ProcessStreamData sequence.
 *  \details     Valid responses are CopyStreamData requests and confirmations of ProcessStreamData.
 *  \param[in]   RemoteTargetGroup  The remote target group of which responses are expected.
 *  \param[out]  RemoteService      The current grid service index.
 *  \param[out]  MinLength          The minimum length over all CopyStreamData requests.
 *  \return      Aggregated result over all responses
 *               - #VSWUPDM_E_REMOTE_SERVICE_TARGET_NOT_PROCESSING  No response expected from an instance in the group.
 *               - #VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE         Unexpected remote service received.
 *               - #E_OK                                            Positive result.
 *               - #VSWUPDM_E_PENDING                               Not all responses received yet. Operation is pending.
 *               - #VSWUPDM_E_SUSPENDED                             Operation was suspended.
 *               - else                                             First negative result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteEvalStreamDataRequest(
  vSwUpdM_NodeGroupIterType RemoteTargetGroup,
  P2VAR(vSwUpdM_GridSrvc_ServiceIdxType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteService,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_DATA) MinLength);

#endif /* (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) */

/*!
* Internal comment removed.
 *
 *
 *
 *
*/

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_GetCheckpointAddress()
 *********************************************************************************************************************/
/*! \brief       Get the address of the next checkpoint following the currently processed address.
 *  \details     -
 *  \param[out]  CheckpointAddress  Address of the next checkpoint following the given address.
 *  \param[in]   WriteAddress       The currently processed address.
 *  \param[in]   PartitionId        ID of used partition.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetCheckpointAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) CheckpointAddress,
  vSwUpdM_AddressType WriteAddress,
  vSwUpdM_PartitionIdType PartitionId);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_UpdateState()
 *********************************************************************************************************************/
/*! \brief       Update state of resume information.
 *  \details     Resume information will be marked "dirty" when any value was updated by the request.
 *  \param[in]   PartitionState       State of used partition.
 *                                    Pass VSWUPDM_PART_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   CurrentService       Service ID of current operation.
 *                                    Pass VSWUPDM_SID_NONE when value shouldn't be updated.
 *  \param[in]   ServiceState         Current state of running operation.
 *                                    Pass VSWUPDM_RESUME_STATE_UNDEFINED when value shouldn't be updated.
 *  \param[in]   MemoryAddress        Address in memory affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   StreamAddress        Address in data stream affected by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   TriggerAddress       Actual address which is currently processed by running operation.
 *                                    Will only be updated when parameter IsAddressValid is TRUE.
 *  \param[in]   IsAddressValid       TRUE Value given in Address is valid.
 *                                    FALSE Value given in Address is irrelevant and won't be updated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateState(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid);

/**************************************************************
 *  Memory Abstraction:
 *   - Buffer
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_Init()
 *********************************************************************************************************************/
/*! \brief       Initialize buffer info.
 *  \details     Assigns actual buffer and size.
 *  \param[out]  BufferInfo     The buffer info to be initialized.
 *  \param[in]   Buffer         Pointer to actual buffer.
 *  \param[in]   Size           The size of the buffer.
 *  \return      E_OK           Initialization of buffer info successful.
 *  \return      else           Initialization of buffer info failed.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_Init(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_VarDataPointerType Buffer,
   vSwUpdM_LengthType Size);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_AddData()
 *********************************************************************************************************************/
/*! \brief       Indicate data is added to the referenced buffer.
 *  \details     Data is expected to be added at the end of the used area/the beginning of the free area.
 *               Function should be called before actually adding any data to the free buffer area.
 *  \param[in,out] BufferInfo   The buffer info referencing the data.
 *  \return      E_NOT_OK     Data length to be added exceeds referenced buffer.
 *               E_OK         Requested data length can be added to referenced buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_AddData(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_InitAndAddData()
 *********************************************************************************************************************/
/*! \brief       Init and add data in one step.
 *  \details     -
 *  \param[in,out] Buffer   The buffer info referencing the data.
 *  \param[in]     Length   Size of the data.
 *  \param[in]     Data     data.
 *  \return      E_NOT_OK     Data length to be added exceeds referenced buffer.
 *               E_OK         Requested data length can be added to referenced buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_InitAndAddData(
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
  vSwUpdM_VarDataPointerType Data,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_Copy()
 *********************************************************************************************************************/
/*! \brief       Copy data from source to target buffer.
 *  \details     -
 *  \param[in]   SourceBuffer   The source buffer.
 *  \param[out]  TargetBuffer   The target buffer.
 *  \param[in]   Length         The length of the data to be copied.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Buffer_Copy(
  vSwUpdM_ConstDataPointerType SourceBuffer,
  vSwUpdM_VarDataPointerType TargetBuffer,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_Fill()
 *********************************************************************************************************************/
/*! \brief       Fill the buffer with a constant value.
 *  \details     -
 *  \param[out]  TargetBuffer   The target buffer.
 *  \param[in]   Value          The fill value.
 *  \param[in]   Length         The length of the data to be filled.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Buffer_Fill(
  vSwUpdM_VarDataPointerType TargetBuffer,
  vSwUpdM_DataType Value,
  vSwUpdM_LengthType Length);

/**************************************************************
 *  Memory Abstraction:
 *   - Segment
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Segment_UpdateWriteAddress()
 *********************************************************************************************************************/
/*! \brief       Update and persist segment state.
 *  \details     Updates the segment state and mark the attributes as dirty.
 *  \param[in,out]  Segment           The segment to be updated.
 *  \param[in]   WriteAddress         The updated write address to be set.
 *  \return      TRUE                 Segment write address is dirty.
 *  \return      FALSE                Segment write address is clean.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_UpdateWriteAddress(
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_AddressType WriteAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_PersistState()
 *********************************************************************************************************************/
/*! \brief       Persist segment states.
 *  \details     Loop over all segments and persist dynamic attributes and/or write address if marked as "dirty".
 *               Persisting of information handled by (potentially asynchronous) user callout.
 *  \param[in]   EntityIds            IDs of entities addressing current segment instances.
 *                                    This includes the PartitionId and ModuleId.
 *  \param[in]   ConfirmationService  Service ID passed to confirmation callout, after job finished.
 *                                    No confirmation will be issued when VSWUPDM_SID_NONE is passed.
 *  \param[in,out] ParentJob          Parent job of callout trigger job.
 *                                    Defines priority and confirmation service ID of callout trigger job.
 *                                    In addition child result attribute of parent job is linked to callout result.
 *  \param[in]   Source               Source node of the request.
 *  \return      E_OK                 Persisting of segment states successfully initiated.
 *  \return      else                 Persisting of segment states could not be initiated.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_PersistState(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_ServiceIdType ConfirmationService,
  boolean PersistCount,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_Init_RemoteStream
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_RemoteStream(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  uint32_least index;
  for (index = 0u; index < (uint32)VSWUPDM_REMOTESTREAMHANDLE_SIZE; index++)
  {
    vSwUpdM_RemoteStream_List[index].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
  }
} /* vSwUpdM_Init_RemoteStream */
#endif

/**********************************************************************************************************************
 * vSwUpdM_Init_ResetStreamData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_ResetStreamData(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Reset volatile stream attributes to default values. */
  vSwUpdM_StreamData.Length      = VSWUPDM_UNDEFINED_LENGTH;
  vSwUpdM_StreamData.MaxLength   = VSWUPDM_UNDEFINED_LENGTH;
  vSwUpdM_StreamData.Remainder   = VSWUPDM_UNDEFINED_LENGTH;
  vSwUpdM_StreamData.Operation   = VSWUPDM_STREAM_OPERATION_DEFAULT;
  vSwUpdM_StreamData.State       = VSWUPDM_STREAM_STATE_IDLE;
  vSwUpdM_StreamData.SegmentId   = VSWUPDM_INVALID_ID;
  vSwUpdM_StreamData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
  vSwUpdM_StreamData.PipeStarted = FALSE;
  vSwUpdM_StreamData.RestartHandling = FALSE;
} /* vSwUpdM_Init_ResetStreamData */

/**********************************************************************************************************************
 * vSwUpdM_Init_InitStreamData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitStreamData(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Set all stream attributes to default values. */
  vSwUpdM_Init_ResetStreamData();

  vSwUpdM_StreamData.PipeId     = vSwUpdM_GetPipeIdOfDataProcesses(vSwUpdMConf_vSwUpdMDataProcess_StreamData);

  (void)vSwUpdM_Pipe_GetInternalEntryPoint(&vSwUpdM_StreamData.PipeEntryPointData,      vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputData);
} /* vSwUpdM_Init_InitStreamData */

/**********************************************************************************************************************
 * vSwUpdM_Init_InitProcessData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitProcessData(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Set data process attributes to default values. */
  vSwUpdM_ProcessData.Operation   = VSTREAMPROC_NO_MODE;
  vSwUpdM_ProcessData.PipeState   = VSWUPDM_PIPE_STATE_IDLE;
  vSwUpdM_ProcessData.PipeStarted = FALSE;
} /* vSwUpdM_Init_InitProcessData */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_CalculateStreamAddress
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_CalculateStreamAddress( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) Segment,
  vSwUpdM_AddressType MemoryAddress,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) StreamAddress
  )
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_AddressType streamAddress = MemoryAddress;
  vSwUpdM_AddressType startAddress  = Segment->DynamicAttributesOfVarSegment.StartAddress;
  vSwUpdM_LengthType  resumeOffset  = Segment->DynamicAttributesOfVarSegment.ResumeOffset;

  /* #100 If a resume offset is required for the given segment: */
  if (resumeOffset > 0u)
  {
    /* #110 Calculate current number of payload bytes in segment. */
    vSwUpdM_LengthType length = 0u; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

    if (MemoryAddress >= startAddress)
    {
      length = MemoryAddress - startAddress;

      /* #120 Limit resume offset to segment start address. */
      if (length < resumeOffset)
      {
        streamAddress = startAddress;
      }
      else
      {
        streamAddress = MemoryAddress - resumeOffset;
      }
    }
  }
  /* #200 Otherwise: No resume offset. */

  *StreamAddress = streamAddress;
} /* vSwUpdM_ResumeInfo_CalculateStreamAddress */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetSubScopeAttributes()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_SubScopeAttributeType, VSWUPDM_CODE) vSwUpdM_Pipe_GetSubScopeAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SubScopeOfDataProcessesType SubScope)
{
  vSwUpdM_SubScopeAttributeType attributes = VSWUPDM_SUB_SCOPE_ATTRIBUTE_NONE;
  uint8_least                   index = 0u;

  /* #10 Loop over list of sub scope definitions. */
  do
  {
    /* #20 If matching sub scope is found: */
    if (vSwUpdM_SubScopeDefinitions[index].SubScope == SubScope)
    {
      /* #30 Return related attributes and finish search. */
      attributes = vSwUpdM_SubScopeDefinitions[index].Attributes;

      break;
    }
    index++;
  }
  while (vSwUpdM_SubScopeDefinitions[index].Attributes != VSWUPDM_SUB_SCOPE_ATTRIBUTE_NONE);

  return attributes;
} /* vSwUpdM_Pipe_GetSubScopeAttributes */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_IsSubScopeAttributeSet()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_IsSubScopeAttributeSet( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SubScopeAttributeType CurrentAttributes,
  vSwUpdM_SubScopeAttributeType CheckAttribute)
{
  Std_ReturnType retVal = FALSE;

  if ((CurrentAttributes & CheckAttribute) == CheckAttribute)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Pipe_IsSubScopeAttributeSet */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_PrepareProcessData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Pipe_PrepareProcessData(  /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ProcessScopeType ProcessScope,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessConfig,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Copy process data for later use into local work space. */
  vSwUpdM_ProcessUserData = *ProcessInfo;

  /* #20 Set internal job process data. */
  vSwUpdM_ProcessData.ProcessConfig = ProcessConfig;
  vSwUpdM_ProcessData.ProcessId     = ProcessId;
  vSwUpdM_ProcessData.Scope         = ProcessScope;
  vSwUpdM_ProcessData.PipeId        = vSwUpdM_GetPipeIdOfDataProcesses(ProcessId);
  vSwUpdM_ProcessData.ProcOperation = VSWUPDM_PROC_NODE_OPERATION_START;
} /* vSwUpdM_Pipe_PrepareProcessData */

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Init_InitEntityData
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitEntityData(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Set entity counts of partitions and modules to configured number. */
  vSwUpdM_EntityData.Count.PartitionCount             = vSwUpdM_GetStaticNumberOfPartitions();
  vSwUpdM_EntityData.Count.ModuleCount                = vSwUpdM_GetStaticNumberOfModules();
  /* #11 Set entity counts of regions and segments to zero. */
  vSwUpdM_EntityData.Count.RegionCount                = 0u;
  vSwUpdM_EntityData.Count.InternalSegmentCount       = 0u;
  vSwUpdM_EntityData.Count.ExternalSegmentCount       = 0u;
  vSwUpdM_EntityData.Count.WriteSegmentCount          = 0u;
  /* #12 Clear "dirty" flag of external segment count. */
  vSwUpdM_EntityData.Count.ExternalSegmentCountDirty  = FALSE;

  /* #20 Set all entity IDs to invalid value. */
  vSwUpdM_Init_EntityIdsDefaults(&vSwUpdM_EntityData.OpenIds);

  /* #30 Set all entity pointers to NULL pointers. */
  vSwUpdM_EntityData.OpenObjects.Partition  = NULL_PTR;
  vSwUpdM_EntityData.OpenObjects.Module     = NULL_PTR;
  vSwUpdM_EntityData.OpenObjects.Region     = NULL_PTR;
  vSwUpdM_EntityData.OpenObjects.Segment    = NULL_PTR;
} /* vSwUpdM_Init_InitEntityData */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleErasable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleErasable(vSwUpdM_ModuleIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (vSwUpdM_Module_IsModuleInstantiatedInPartition(Id, vSwUpdM_EntityData.OpenIds.PartitionId) == TRUE)
  {
    retVal = vSwUpdM_IsPartitionErasable(vSwUpdM_EntityData.OpenIds.PartitionState);
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleErasable */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleReadable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleReadable(vSwUpdM_ModuleIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (vSwUpdM_Module_IsModuleInstantiatedInPartition(Id, vSwUpdM_EntityData.OpenIds.PartitionId) == TRUE)
  {
    retVal = vSwUpdM_IsPartitionReadable(vSwUpdM_EntityData.OpenIds.PartitionState);
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleReadable */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleWritable(vSwUpdM_ModuleIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (vSwUpdM_Module_IsModuleInstantiatedInPartition(Id, vSwUpdM_EntityData.OpenIds.PartitionId) == TRUE)
  {
    retVal = vSwUpdM_IsPartitionWritable(vSwUpdM_EntityData.OpenIds.PartitionState);
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleWritable */

/**********************************************************************************************************************
 * vSwUpdM_Part_IsPartitionStateSet
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionStateSet( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_PartitionStateType CurrentState,
  vSwUpdM_PartitionStateType CheckState)
{
  Std_ReturnType retVal = FALSE;

  if ((CurrentState & CheckState) == CheckState)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Part_IsPartitionStateSet */

/**********************************************************************************************************************
 * vSwUpdM_Module_GetRelativePartitionIdxByPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetRelativePartitionIdxByPartition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_PartitionIdxType, AUTOMATIC, VSWUPDM_APPL_VAR) RelativePartitionIdx,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  Std_ReturnType            retVal = E_NOT_OK;
  vSwUpdM_VarModulesPtrType module = vSwUpdM_GetAddrVarModules(ModuleId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_PartitionIterType relativePartitionIdx;

  /* #10 Iterate over all partitions the module is assigned to */
  for (relativePartitionIdx = 0u; relativePartitionIdx < module->PartitionCountOfVarModules; relativePartitionIdx++)
  {
    /* #20 If partition ID matches given one */
    if (module->PartitionIdsOfVarModules[relativePartitionIdx] == PartitionId)
    {
      /* #30 Return partition ID and finish search. */
      *RelativePartitionIdx = (vSwUpdM_PartitionIdxType)relativePartitionIdx;
      retVal = E_OK;

      break;
    }
  }

  return retVal;
} /* vSwUpdM_Module_GetRelativePartitionIdxByPartition */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleInstantiatedInPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleInstantiatedInPartition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  boolean                   retVal = FALSE;
  vSwUpdM_PartitionIdxType  relativePartitionIdx;

  if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ModuleId, PartitionId) == E_OK)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleInstantiatedInPartition */

/**********************************************************************************************************************
 * vSwUpdM_Region_CheckProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_CheckProgrammingAttempts( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType  retVal = E_OK;

  if ( (vSwUpdM_GetProgrammingAttemptsOfModule(ModuleId) > 0u)
    && (vSwUpdM_GetVarRegions(RegionIdx).DynamicAttributesOfVarRegion.ProgrammingAttempts >= vSwUpdM_GetProgrammingAttemptsOfModule(ModuleId)) )
  {
    retVal = VSWUPDM_E_PROGRAMMING_ATTEMPTS_EXCEEDED;
  }

  return retVal;
} /* vSwUpdM_Region_CheckProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_Segment_SearchQueueHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_SearchQueueHandle( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_QueueHandleType, AUTOMATIC, VSWUPDM_APPL_VAR) QueueHandle,
  vSwUpdM_AddressType StartAddress)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarSegmentsIterType   segmentId;
  vSwUpdM_QueueHandleType       queueHandle;

  /* #10 Loop all internal segments, by iterating over queue, starting at first entry. */
  queueHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_InternalSegmentsQueue);

  do
  {
    segmentId = (vSwUpdM_VarSegmentsIterType)vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle);

    /* #20 If requested start address is located between reserved start and end addresses of the segment */
    if ( (vSwUpdM_GetVarSegments(segmentId).ReservedStartAddressOfVarSegments <= StartAddress)
      && (vSwUpdM_GetVarSegments(segmentId).ReservedEndAddressOfVarSegments >= StartAddress) )
    {
      /* #30 Return matching queue handle and finish search. */
      *QueueHandle = queueHandle;
      retVal = E_OK;

      break;
    }

    queueHandle = vSwUpdM_QueueGetEntry(&vSwUpdM_InternalSegmentsQueue, queueHandle).next;
  } while (queueHandle != VSWUPDM_QUEUE_HANDLE_HEAD_USED);

  return retVal;
} /* vSwUpdM_Segment_SearchQueueHandle */

/**********************************************************************************************************************
 * vSwUpdM_Segment_SearchSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_SearchSegment( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  vSwUpdM_AddressType StartAddress)
{
  Std_ReturnType          retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_QueueHandleType queueHandle = (vSwUpdM_QueueHandleType)0u; /* Initialization is only necessary to avoid MISRA false positive 2962. */

  if (vSwUpdM_Segment_SearchQueueHandle(&queueHandle, StartAddress) == E_OK)
  {
    /* #30 Return matching segment and finish search. */
    *SegmentId = (vSwUpdM_SegmentIdValueType)vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle);
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_Segment_SearchSegment */

/**********************************************************************************************************************
 * vSwUpdM_Segment_OpenSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_OpenSegment( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ------------------------------------------------- */
  vSwUpdM_JobPtrType spawnedJob;

  /* #10 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job to open segment, triggering persisting of segment attributes when necessary. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_OPEN_SEGMENT, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

  /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    spawnedJob->RemoteTargetGroup   = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);
    spawnedJob->EntityIds           = vSwUpdM_EntityData.OpenIds;
    spawnedJob->EntityIds.SegmentId = Id;
  }

  /* #40 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_Segment_OpenSegment */

/**********************************************************************************************************************
 * vSwUpdM_Segment_CloseSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_CloseSegment( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ------------------------------------------------- */
  vSwUpdM_JobPtrType spawnedJob;

  /* #10 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job to close segment, triggering persisting of segment attributes when necessary. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_CLOSE_SEGMENT, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

  /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    spawnedJob->RemoteTargetGroup   = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);
    spawnedJob->EntityIds           = vSwUpdM_EntityData.OpenIds;
    spawnedJob->EntityIds.SegmentId = Id;
  }

  /* #40 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_Segment_CloseSegment */

/**********************************************************************************************************************
 * vSwUpdM_Module_GetAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetAttributes( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_ModuleDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) Attributes)
{
  Std_ReturnType retVal;
  vSwUpdM_VarModulesPtrType   module = vSwUpdM_GetAddrVarModules(ModuleId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_PartitionIdxType    relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

  retVal = vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ModuleId, PartitionId);

  if(retVal == E_OK)
  {
    /* Return attributes of module instance addressed by partition index. */
    (*Attributes) = module->DynamicAttributesOfVarModules[relativePartitionIdx];
  }

  return retVal;
} /* vSwUpdM_Module_GetAttributes */

/**********************************************************************************************************************
 * vSwUpdM_Module_CheckProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_CheckProgrammingAttempts( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                  retVal          = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ProgrammingAttemptsType moduleAttempts  = 0u;

  retVal = vSwUpdM_Module_GetProgrammingAttemptsByPartition(&moduleAttempts, ModuleId, PartitionId);

  if (retVal == E_OK)
  {
    if ( (vSwUpdM_GetProgrammingAttemptsOfModule(ModuleId) > 0u)
      && (moduleAttempts >= vSwUpdM_GetProgrammingAttemptsOfModule(ModuleId)) )
    {
      retVal = VSWUPDM_E_PROGRAMMING_ATTEMPTS_EXCEEDED;
    }
  }

  return retVal;
} /* vSwUpdM_Module_CheckProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_Segment_IsSegmentWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentWritable(vSwUpdM_SegmentIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean                    retVal   = FALSE;
  vSwUpdM_VarSegmentsPtrType segment  = vSwUpdM_GetAddrVarSegments(Id.DynamicSegmentId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  switch (segment->DynamicAttributesOfVarSegment.State)
  {
    case VSWUPDM_SEGMENT_STATE_ERASED:
    case VSWUPDM_SEGMENT_STATE_PENDING:
    {
      retVal = segment->SegmentClean;
      break;
    }
    default:
    /* Otherwise: Report FALSE. */
    {
      break;
    }
  }

  return retVal;
} /* vSwUpdM_Segment_IsSegmentWritable */

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_General_UpdateState
 *********************************************************************************************************************/
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
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_General_UpdateState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_UpdateStateType State,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 If update state doesn't already match the requested state */
  if (vSwUpdM_UpdateState != State)
  {
    /* #20 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #21 Spawn job to persist changed update state. */
    (void)vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_HANDLE_UPDATE_STATE, VSWUPDM_JOB_OPERATION_HANDLE_UPDATE_STATE_SET, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

    /* #22 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      vSwUpdM_UpdateState = State;
    }

    /* #23 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  /* #30 Otherwise */
  else
  {
    /* #31 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer. */
    vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);
  }

  return retVal;
} /* vSwUpdM_General_UpdateState */

/**********************************************************************************************************************
 * vSwUpdM_Module_GetProgrammingAttemptsByPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetProgrammingAttemptsByPartition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  Std_ReturnType            retVal = E_NOT_OK;
  vSwUpdM_PartitionIdxType  relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

  /* #10 Evaluate relative partition index of given partition. */
  if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ModuleId, PartitionId) == E_OK)
  {
    /* #20 Return programming attempt counter of module instance addressed by partition index. */
    vSwUpdM_ProgrammingAttemptsType attempts = vSwUpdM_GetVarModules(ModuleId).DynamicAttributesOfVarModules[relativePartitionIdx].ProgrammingAttempts;

    *ProgrammingAttempts  = attempts;
    retVal                = E_OK;
  }

  return retVal;
} /* vSwUpdM_Module_GetProgrammingAttemptsByPartition */

/**********************************************************************************************************************
 * vSwUpdM_Module_GetStateByPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_GetStateByPartition( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2VAR(vSwUpdM_ModuleStateType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  Std_ReturnType            retVal = E_NOT_OK;
  vSwUpdM_PartitionIdxType  relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

  /* #10 Evaluate relative partition index of given partition. */
  if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ModuleId, PartitionId) == E_OK)
  {
    /* #20 Return state of module instance addressed by partition index. */
    vSwUpdM_ModuleStateType moduleState = vSwUpdM_GetVarModules(ModuleId).DynamicAttributesOfVarModules[relativePartitionIdx].State;

    *ModuleState  = moduleState;
    retVal        = E_OK;
  }

  return retVal;
} /* vSwUpdM_Module_GetStateByPartition */

/**********************************************************************************************************************
 * vSwUpdM_Module_PersistState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* #10 Trigger persisting of any pending state. */
  return vSwUpdM_Module_PersistStateAndConfirm(PartitionId, PartitionState, ModuleId, VSWUPDM_SID_NONE, ParentJob, Source);
}

/**********************************************************************************************************************
 * vSwUpdM_Module_UpdateAndPersistState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateAndPersistState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 Update module state with given value. */
  retVal = vSwUpdM_Module_UpdateState(PartitionId, ModuleId, State);

  if (retVal == E_OK)
  {
    /* #20 Trigger persisting of updated state. */
    retVal = vSwUpdM_Module_PersistState(PartitionId, PartitionState, ModuleId, ParentJob, Source);
  }

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR  */
} /* vSwUpdM_Module_UpdateAndPersistState */

/**********************************************************************************************************************
 * vSwUpdM_Segment_UpdateState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_UpdateState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_SegmentStateType State)
{
  /* #10 If given state doesn't match the current segment state */
  if (Segment->DynamicAttributesOfVarSegment.State != State)
  {
    /* #20 Update segment state with given value and mark attributes as dirty. */
    Segment->DynamicAttributesOfVarSegment.State  = State;
    Segment->AttributesDirty                      = TRUE;
  }

  return Segment->AttributesDirty;
} /* vSwUpdM_Segment_UpdateState */

/**********************************************************************************************************************
 * vSwUpdM_Segment_UpdateAndPersistState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_UpdateAndPersistState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SegmentIdType SegmentId,
  vSwUpdM_SegmentStateType State,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  return vSwUpdM_Segment_UpdateAndPersistStateAndConfirm(SegmentId, VSWUPDM_SID_NONE, State, Source, ParentJob);
} /* vSwUpdM_Segment_UpdateAndPersistState */

/**********************************************************************************************************************
 * vSwUpdM_Segment_UpdateAndPersistStateAndConfirm
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_UpdateAndPersistStateAndConfirm( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_SegmentIdType SegmentId,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_SegmentStateType State,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)

{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType              retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarSegmentsPtrType  segment;

  segment = vSwUpdM_GetAddrVarSegments(SegmentId.DynamicSegmentId);

  if (vSwUpdM_Segment_UpdateState(segment, State) == TRUE)
  {
    vSwUpdM_EntityIdsType entityIds;

    /* #40 Trigger persisting of updated state. */
    entityIds           = vSwUpdM_EntityData.OpenIds;
    entityIds.SegmentId = SegmentId;

    retVal = vSwUpdM_Segment_PersistState(&entityIds, ConfirmationService, FALSE, ParentJob, Source);
  }
  else
  {
    vSwUpdM_UlConfirmation(ConfirmationService, Source, E_OK);
  }

  return retVal;
} /* vSwUpdM_Segment_UpdateAndPersistStateAndConfirm */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_ResetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_ResetState(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  vSwUpdM_ResumeInfo.ResumeInfo.PartitionState   = VSWUPDM_PART_STATE_UNDEFINED;
  vSwUpdM_ResumeInfo.ResumeInfo.CurrentService   = VSWUPDM_SID_NONE;
  vSwUpdM_ResumeInfo.ResumeInfo.ServiceState     = VSWUPDM_RESUME_STATE_UNDEFINED;
  vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress    = 0u;
  vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress    = 0u;
  vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid   = FALSE;
  vSwUpdM_ResumeInfo.TriggerAddress = 0u;

  vSwUpdM_CheckpointAddress           = VSWUPDM_MAX_ADDRESS;
} /* vSwUpdM_ResumeInfo_ResetState */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_IncreaseAddress
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_IncreaseAddress( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_AddressType Offset)
{
  vSwUpdM_AddressType lastAddress = ParentJob->TargetAddress + (Offset - 1u);

  /* #100 Update target address for next write. */
  ParentJob->TargetAddress = lastAddress + 1u;

  /* #200 If a segment is opened: */
  if (ParentJob->EntityIds.SegmentId.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount)
  {
    vSwUpdM_VarSegmentsPtrType  segment;
    vSwUpdM_AddressType streamAddress;

    segment = vSwUpdM_GetAddrVarSegments(ParentJob->EntityIds.SegmentId.DynamicSegmentId);

    /* #210 Update write address of segment. */
    (void)vSwUpdM_Segment_UpdateWriteAddress(segment, ParentJob->TargetAddress);

    /* #220 If resume info shall be updated by job */
    if (ParentJob->UpdateResumeInfo == TRUE)
    {
      /* #221 Determine apparent resume address, which doesn't include any padding. */
      vSwUpdM_Segment_GetApparentAddress(segment, &lastAddress, FALSE);

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
      /* #222 Fine-Grained Resume: If Checkpoint hit,
       *      Persist current state. */
      if (ParentJob->TargetAddress == vSwUpdM_CheckpointAddress)
      {
        (void)vSwUpdM_ResumeInfo_PersistForNextCheckpoint(ParentJob->EntityIds.PartitionId, ParentJob->EntityIds.PartitionState, ParentJob->EntityIds.SegmentId.DynamicSegmentId, lastAddress, TRUE, ParentJob->Source);
        (void)vSwUpdM_Segment_PersistState(&ParentJob->EntityIds, VSWUPDM_SID_NONE, FALSE, NULL_PTR, ParentJob->Source);
      }
#endif

      /* #223 Always point to next address in data stream. */
      vSwUpdM_ResumeInfo_CalculateStreamAddress(segment, lastAddress + 1u, &streamAddress);

      /* #224 Update resume information to indicate that service is pending, using the apparent resume address, while taking over the service ID. */
      vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_PENDING, lastAddress, streamAddress, lastAddress, TRUE);
    }
  }
} /* vSwUpdM_ResumeInfo_IncreaseAddress */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_EvaluateEntityIds
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_EvaluateEntityIds( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_EntityIdsPtrType EntityIds)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Initialize entity IDs with default values. */
  vSwUpdM_Init_EntityIdsDefaults(EntityIds);

  /* #20 If valid service ID and state is set in resume information */
  if ( (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService != VSWUPDM_SID_NONE)
    && (vSwUpdM_ResumeInfo.ResumeInfo.ServiceState != VSWUPDM_RESUME_STATE_UNDEFINED) )
  {
    /* #30 Assign partition ID stored in resume information to entity IDs. */
    EntityIds->PartitionState = vSwUpdM_ResumeInfo.ResumeInfo.PartitionState;
    (void)vSwUpdM_Part_GetIdByState(&EntityIds->PartitionId, EntityIds->PartitionState);

    /* #100 If address in resume information is marked valid */
    if (vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid == TRUE)
    {
      vSwUpdM_ModuleIdType  moduleId;
      vSwUpdM_RegionIdType  regionId;
      vSwUpdM_SegmentIdType segmentId;

      /* #110 Search for module at trigger address and assign it to entity IDs if found. */
      if (vSwUpdM_GetModuleIdByRange(&moduleId, vSwUpdM_ResumeInfo.TriggerAddress, 1u) == E_OK)
      {
        EntityIds->ModuleId = moduleId;
      }

      /* #120 Search for module at trigger address and assign it to entity IDs if found. */
      if (vSwUpdM_GetRegionIdByRange(&regionId, vSwUpdM_ResumeInfo.TriggerAddress, 1u) == E_OK)
      {
        EntityIds->RegionId = regionId;
      }

      /* #130 Search for module at trigger address and assign it to entity IDs if found. */
      if(vSwUpdM_GetSegmentIdByRange(&segmentId, vSwUpdM_ResumeInfo.TriggerAddress, 1u) == E_OK)
      {
        EntityIds->SegmentId = segmentId;
      }
    }

    /* #200 Entity IDs successfully evaluated. */
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_ResumeInfo_EvaluateEntityIds */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_CompareEntities
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ResumeInfo_CompareEntities( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds)
{
  boolean               infoChanged = FALSE;
  vSwUpdM_EntityIdsType currentEntityIds;

  /* #10 Evaluate entity IDs based on current resume information. */
  if (vSwUpdM_ResumeInfo_EvaluateEntityIds(&currentEntityIds) == E_OK)
  {
    /* #20 If partition ID in resume information differs from given one
     *  Difference found. */
    if (currentEntityIds.PartitionId != EntityIds->PartitionId)
    {
      infoChanged = TRUE;
    }

    /* #30 If both module ID in resume information and given entity IDs are valid and both differ
     *  Difference found. */
    if ( (currentEntityIds.ModuleId != VSWUPDM_INVALID_ID)
      && (EntityIds->ModuleId != VSWUPDM_INVALID_ID)
      && (currentEntityIds.ModuleId != EntityIds->ModuleId) )
    {
      infoChanged = TRUE;
    }

    /* #40 If both region ID in resume information and given entity IDs are valid and both differ
     *  Difference found. */
    if ( (currentEntityIds.RegionId != VSWUPDM_INVALID_ID)
      && (EntityIds->RegionId != VSWUPDM_INVALID_ID)
      && (currentEntityIds.RegionId != EntityIds->RegionId) )
    {
      infoChanged = TRUE;
    }

    /* #50 If both dynamic segment ID in resume information and given entity IDs are valid and both differ
     *  Difference found. */
    if ( (currentEntityIds.SegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
      && (EntityIds->SegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
      && (currentEntityIds.SegmentId.DynamicSegmentId != EntityIds->SegmentId.DynamicSegmentId) )
    {
      infoChanged = TRUE;
    }
  }
  /* #100 Otherwise
   *   Difference found. */
  else
  {
    infoChanged = TRUE;
  }

  return infoChanged;
} /* vSwUpdM_ResumeInfo_CompareEntities */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_InitState
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_InitState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_AddressType Address,
  vSwUpdM_ValidType IsAddressValid)
{
  boolean infoChanged = FALSE;

  /* #10 If service ID in resume information differs from given one
   *   Resume information needs to be updated. */
  if (CurrentService != vSwUpdM_ResumeInfo.ResumeInfo.CurrentService)
  {
    infoChanged = TRUE;
  }

  /* #20 If entity IDs from resume information differ from given ones
   *   Resume information needs to be updated. */
  if (vSwUpdM_ResumeInfo_CompareEntities(EntityIds) == TRUE)
  {
    infoChanged = TRUE;
  }

  /* #30 Update resume information with given information if necessary. */
  if (infoChanged == TRUE)
  {
    vSwUpdM_ResumeInfo_UpdateState(EntityIds->PartitionState, CurrentService, VSWUPDM_RESUME_STATE_STARTED, Address, Address, Address, IsAddressValid);
  }
} /* vSwUpdM_ResumeInfo_InitState */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_UpdateWriteService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateWriteService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_ServiceIdType ServiceId)
{
  vSwUpdM_AddressType         resumeAddress;
  vSwUpdM_ResumeStateType     resumeState;
  vSwUpdM_AddressType         streamAddress;

  /* #10 Update resume information for any service which writes to memory, using apparent write address of given segment. */
  vSwUpdM_Segment_GetApparentWriteAddress(Segment, &resumeAddress);

  /* #20 Always point to next address in data stream. */
  vSwUpdM_ResumeInfo_CalculateStreamAddress(Segment, resumeAddress, &streamAddress);

  /* #30 Set resume state to "started" when write address is equal to start address of segment. */
  if (resumeAddress == Segment->DynamicAttributesOfVarSegment.StartAddress)
  {
    resumeState = VSWUPDM_RESUME_STATE_STARTED;
  }
  else
  {
  /* #40 Set to "pending" otherwise. */
    resumeState = VSWUPDM_RESUME_STATE_PENDING;
    resumeAddress--;
  }

  vSwUpdM_ResumeInfo_UpdateState(PartitionState, ServiceId, resumeState, resumeAddress, streamAddress, resumeAddress, TRUE);
} /* vSwUpdM_ResumeInfo_UpdateWriteService */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_InitModuleService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_InitModuleService( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType CurrentService)
{
  vSwUpdM_EntityIdsType entityIds;
  vSwUpdM_AddressType   startAddress;

  entityIds           = vSwUpdM_EntityData.OpenIds;
  entityIds.ModuleId  = Id;
  startAddress        = vSwUpdM_GetStartAddressOfRegion(vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(Id)));

  vSwUpdM_ResumeInfo_InitState(&entityIds, CurrentService, startAddress, TRUE);
} /* vSwUpdM_ResumeInfo_InitModuleService */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_UpdateAndPersistState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateAndPersistState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */

  return vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm(PartitionState, CurrentService, ServiceState, MemoryAddress, StreamAddress, TriggerAddress, IsAddressValid, VSWUPDM_SID_NONE, Source);
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_ResumeInfo_UpdateAndPersistState */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType  retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 Update resume information with given values. */
  vSwUpdM_ResumeInfo_UpdateState(PartitionState, CurrentService, ServiceState, MemoryAddress, StreamAddress, TriggerAddress, IsAddressValid);

  /* #20 Trigger persisting of resume information. */
  retVal = vSwUpdM_ResumeInfo_PersistStateAndConfirm(Source, ConfirmationService);

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm */

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_General_UpdateGlobalState
 *********************************************************************************************************************/
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
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_UpdateGlobalState(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* #10 If no further job is pending */
  if (vSwUpdM_ExctSchedule_IsSlotFree() == TRUE)
  {
    /* #20 Update global state: */
    switch (vSwUpdM_GlobalState)
    {
      case (VSWUPDM_STATE_ACTIVE):
      /* #21 In active state
       *   Fall back to idle state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_IDLE;
        break;
      }
      case (VSWUPDM_STATE_SUSPENDING):
      /* #22 In suspending state
       *   Switch to suspended state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_SUSPENDED;
        break;
      }
      case (VSWUPDM_STATE_SHUT_DOWN_PENDING):
      /* #23 In shut down pending state
       *   Switch to shut down state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_SHUT_DOWN;
        break;
      }
      default:
      /* #24 Otherwise
       *   State remains unchanged. */
      {
        break;
      }
    }
  }
  /* #30 Otherwise */
  else
  {
    /* #40 Update global state: */
    switch (vSwUpdM_GlobalState)
    {
      case (VSWUPDM_STATE_ACTIVE):
      /* #41 In active state
       *   Fall back to pending state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_PENDING;
        break;
      }
      case (VSWUPDM_STATE_SUSPENDING):
      /* #42 In suspending state
       *   Switch to suspend pending state. */
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_SUSPEND_PENDING;
        break;
      }
      default:
      /* #43 Otherwise
       *   State remains unchanged. */
      {
        break;
      }
    }
  }
} /* vSwUpdM_General_UpdateGlobalState */

/**********************************************************************************************************************
 * vSwUpdM_General_IsModuleInitialized
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_General_IsModuleInitialized(void) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  boolean retVal = FALSE;

  if (vSwUpdM_InitState == VSWUPDM_INIT_STATE_INITIALIZED)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_General_IsModuleInitialized */

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  vSwUpdM_General_HandleDetError()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_General_HandleDetError( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_ServiceIdType ServiceId,
  vSwUpdM_ErrorCode ErrorId)
{
#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
  if (ErrorId != VSWUPDM_E_NO_ERROR)
  {
    vSwUpdM_DetReportError(ServiceId, ErrorId);
  }
#else
  VSWUPDM_DUMMY_STATEMENT(ServiceId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* vSwUpdM_General_HandleDetError */

/**********************************************************************************************************************
 * vSwUpdM_Part_IsPartitionHandleValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionHandleValid(vSwUpdM_PartitionHandleIdType Handle)  /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (Handle < VSWUPDM_NO_PARTITIONHANDLEOFPARTITION)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Part_IsPartitionHandleValid */

/**********************************************************************************************************************
 * vSwUpdM_Part_IsPartitionStateValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionStateValid(vSwUpdM_PartitionStateType PartState) /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
  Std_ReturnType retVal = FALSE;

  /* #10 Check given partition state. */
  switch (PartState)
  {
    case VSWUPDM_PART_STATE_ACTIVE:
    case VSWUPDM_PART_STATE_INACTIVE:
    case VSWUPDM_PART_STATE_BACKUP_TARGET:
    case VSWUPDM_PART_STATE_BACKUP_SOURCE:
    case VSWUPDM_PART_STATE_ACTIVATION_PENDING:
    /* #20 State contained in list all known partition states: State is valid. */
    {
      retVal = TRUE;
      break;
    }
    default:
    /* #30 Otherwise: State is invalid. */
    {
      break;
    }
  }

  return retVal;
} /* vSwUpdM_Part_IsPartitionStateValid */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleHandleValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleHandleValid(vSwUpdM_ModuleHandleIdType Handle)  /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (Handle < VSWUPDM_NO_MODULEHANDLEOFMODULE)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleHandleValid */

/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleIdValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleIdValid(vSwUpdM_ModuleIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (Id < vSwUpdM_GetStaticNumberOfModules())
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleIdValid */

/**********************************************************************************************************************
 * vSwUpdM_Region_IsRegionHandleValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Region_IsRegionHandleValid(vSwUpdM_RegionHandleIdType Handle)  /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (Handle < VSWUPDM_NO_REGIONHANDLEOFREGION)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Region_IsRegionHandleValid */

 /**********************************************************************************************************************
 * vSwUpdM_Segment_IsSegmentIdAllowed
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentIdAllowed(vSwUpdM_SegmentIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if ( (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId == VSWUPDM_INVALID_ID)
    || (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId == Id.DynamicSegmentId) )
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Segment_IsSegmentIdAllowed */

#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_Module_IsModuleIdAllowed
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Module_IsModuleIdAllowed(vSwUpdM_ModuleIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if ( (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
    || (vSwUpdM_EntityData.OpenIds.ModuleId == Id) )
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Module_IsModuleIdAllowed */

/**********************************************************************************************************************
 * vSwUpdM_Region_IsRegionIdValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Region_IsRegionIdValid(vSwUpdM_RegionIdType Id) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean retVal = FALSE;

  /* ----- Implementation ------------------------------------------------- */
  if (Id < vSwUpdM_GetStaticNumberOfRegions())
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Region_IsRegionIdValid */

/**********************************************************************************************************************
 * vSwUpdM_Segment_IsSegmentIdValid
 *********************************************************************************************************************/
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
VSWUPDM_LOCAL_INLINE FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsSegmentIdValid(vSwUpdM_SegmentIdType Id) /* PRQA S 3219 */ /* MD_MSR_Unreachable */
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;
  vSwUpdM_ErrorCode errorId;

  /* ----- Implementation ------------------------------------------------- */
  /* #10 If module is opened and dynamic segment ID is within the range of internal segments */
  if ( (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_NONE) == VSWUPDM_E_NO_ERROR)
    && (Id.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount) )
  {
    /* #20 If static segments are configured
     *  Verify that given static segment ID is either invalid or matches the value assigned to the dynamic segment. */
#if (VSWUPDM_SEGMENT == STD_ON)
    if ( (Id.StaticSegmentId == VSWUPDM_INVALID_ID)
      || (Id.StaticSegmentId == vSwUpdM_GetVarSegments(Id.DynamicSegmentId).HandleIDOfVarSegments) )
#endif
    {
      /* #30 Given segment ID is valid. */
      retVal = TRUE;
    }
  }
  /* #100 If static segments are configured
   *   Verify that given static segment ID is within range of configured static segments */
#if (VSWUPDM_SEGMENT == STD_ON)
  else if (Id.StaticSegmentId < vSwUpdM_GetStaticNumberOfSegments())
  {
    /* #110 Given segment ID is valid. */
    retVal = TRUE;
  }
  /* #200 Otherwise: Invalid segment ID. */
  else
  {
  }
#endif

  return retVal;
} /* vSwUpdM_Segment_IsSegmentIdValid */
#endif

/*!
 * Internal comment removed.
 *
 *
 *
 *
 */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_PersistStateAndConfirm
 *********************************************************************************************************************/
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
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistStateAndConfirm(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ServiceIdType ConfirmationService) /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 If changed resume information wasn't persisted yet (marked "dirty") */
  if (vSwUpdM_ResumeInfoDirty == TRUE)
  {
    /* #20 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #30 Spawn asynchronous job to persist resume information. */
    (void)vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_HANDLE_RESUME_INFO, VSWUPDM_JOB_OPERATION_HANDLE_RESUME_INFO_SET, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, NULL_PTR, Source);

    /* #40 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      vSwUpdM_ResumeInfoDirty   = FALSE;
      vSwUpdM_PendingResumeInfo = vSwUpdM_ResumeInfo;
    }

    /* #50 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  else
  {
    /* #60 Otherwise:
     * Immediately trigger positive response. */
     vSwUpdM_UlConfirmation(ConfirmationService, Source, E_OK);
  }

  return retVal;
} /* vSwUpdM_ResumeInfo_PersistStateAndConfirm */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_PersistState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistState( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType Source)
{
  return vSwUpdM_ResumeInfo_PersistStateAndConfirm(Source, VSWUPDM_SID_NONE);
} /* vSwUpdM_ResumeInfo_PersistState */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Priv.h
 *********************************************************************************************************************/
