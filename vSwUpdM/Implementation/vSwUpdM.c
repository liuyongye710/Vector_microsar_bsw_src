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
/*!        \file  vSwUpdM.c
 *        \brief  vSwUpdM source file
 *      \details  Main source file for Software Update Manager.
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

#define VSWUPDM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "SchM_vSwUpdM.h"
#include "vSwUpdM_ExecCtrl_Impl.h"
#include "vSwUpdM_Grid_Impl.h"
#include "vSwUpdM_Services_Impl.h"
#include "vSwUpdM_SrvcRouting_If.h"
#include "vSwUpdM_BkPersistServer_Impl.h"
#include "vSwUpdM_BkPersistClient_If.h"
#include "vSwUpdM_Priv.h"
#include "vSwUpdM_Queue.h"
#include "vSwUpdM_Range.h"
#include "vSwUpdM_Appl.h"
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# include "vRpcProxy_vSwUpdM.h"
# include "vRpcProxy_Service.h"
#endif

#include "vStreamProc.h"
#include "vSwUpdM_ProcNodeTypes.h"

#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if ((VSWUPDM_SW_MAJOR_VERSION != (0x05)) || (VSWUPDM_SW_MINOR_VERSION != (0x01)) || (VSWUPDM_SW_PATCH_VERSION != (0x01)))
# error "Vendor specific version numbers of vSwUpdM.c and vSwUpdM.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((VSWUPDM_AR_MAJOR_VERSION != (0x04)) || (VSWUPDM_AR_MINOR_VERSION != (0x00)) || (VSWUPDM_AR_PATCH_VERSION != (0x03)))
# error "AUTOSAR Specification Version numbers of vSwUpdM.c and vSwUpdM.h are inconsistent!"
#endif

/* Check versions of all included header files */
#if ((VSWUPDM_CFG_MAJOR_VERSION != (0x05)) || (VSWUPDM_CFG_MINOR_VERSION != (0x01)))
# error "Version numbers of vSwUpdM.c and vSwUpdM_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/*! Align address to front of range defined by bitmask (must be 2^n - 1, e.g. 0x00FF).
  E.g. 0x123 with a mask of 0xFF will return 0x100. */
#define VSWUPDM_ALIGN_ADDRESS_FRONT(address, mask)    (((address) | (mask)) ^ (mask))
/*! Align address to end of range defined by bitmask (must be 2^n - 1, e.g. 0x00FF).
  E.g. 0x123 with a mask of 0xFF will return 0x1FF. */
#define VSWUPDM_ALIGN_ADDRESS_END(address, mask)      ((address) | (mask))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**************************************************************
 *  General:
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Init_CreatePartitionStructure()
 *********************************************************************************************************************/
/*! \brief       Sets up the initial partition structure.
 *  \details     Reads static partition configuration.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreatePartitionStructure(void);

/**********************************************************************************************************************
 *  vSwUpdM_Init_CreateModuleStructure()
 *********************************************************************************************************************/
/*! \brief       Sets up the initial module structure.
 *  \details     Reads static module configuration.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreateModuleStructure(void);

/**********************************************************************************************************************
 *  vSwUpdM_Init_CreateMemoryStructure()
 *********************************************************************************************************************/
/*! \brief       Sets up the initial memory structure.
 *  \details     Resets all opened entities, reads static partition and module configuration and initializes all queue
 *               and job objects.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreateMemoryStructure(void);

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_GetSegmentCandidate()
 *********************************************************************************************************************/
/*! \brief       Search potential segment candidate for resuming of interrupted operation.
 *  \details     Return first external segment in sector containing the given address.
 *               Address within the segment where operation needs to be resumed is returned too.
 *  \param[out]  SegmentId          ID of the first external segment.
 *  \param[out]  ResumeAddress      Address within the segment where operation needs to be resumed.
 *  \param[in]   Address            Address affected by running operation.
 *  \return      E_OK               At least one external segment was found within the sector.
 *  \return      E_NOT_OK           No external segments was found within the sector.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetSegmentCandidate(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  vSwUpdM_AddressType Address);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_EvalSegmentCandidate()
 *********************************************************************************************************************/
/*! \brief       Evaluate potential segment candidate for resuming of interrupted operation.
 *  \details     Search segment candidate for given address and compare against current first affected external segment.
 *               Update if found segment was added earlier.
 *  \param[in,out]  FirstSegmentId    ID of the first affected external segment.
 *  \param[out]  ResumeAddress        Address within the segment where operation needs to be resumed.
 *  \param[in]   Address              Address affected by running operation.
 *  \return      TRUE                 First affected segment was changed.
 *  \return      FALSE                First affected segment stayed the same.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ResumeInfo_EvalSegmentCandidate(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) FirstSegmentId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  vSwUpdM_AddressType Address);

/**********************************************************************************************************************
 *  vSwUpdM_ResumeInfo_GetResumeAddress()
 *********************************************************************************************************************/
/*! \brief       Get the resume address based on the given segment and checkpoint.
 *  \details     Determine the address where the current operation needs to be resumed when it is interrupted.
 *  \param[out]  ResumeAddress      Address within the segment where operation needs to be resumed.
 *  \param[out]  ResumeSegmentId    ID of the segment where the operation needs to be resumed.
 *  \param[in]   SegmentId          ID of the segment which is currently processed.
 *  \param[in]   CheckpointAddress  Address of the next checkpoint following the currently processed address.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetResumeAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeSegmentId,
  vSwUpdM_SegmentIdValueType SegmentId,
  vSwUpdM_AddressType CheckpointAddress);

#endif

/**************************************************************
 *  Memory Abstraction:
 *   - Partition
 **************************************************************/

/**************************************************************
 *  Memory Abstraction:
 *   - Module
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Module_PreparePendingAttributes()
 *********************************************************************************************************************/
/*! \brief       Prepares the pending attributes structure.
 *  \details     Structure holds values which need to be persisted.
 *               Preparation creates a copy of the current module attributes, unless the attributes are already
 *               marked as dirty.
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
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PreparePendingAttributes(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId);

/**************************************************************
 *  Memory Abstraction:
 *   - Region
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Region_PreparePendingAttributes()
 *********************************************************************************************************************/
/*! \brief       Prepares the pending attributes structure.
 *  \details     Structure holds values which need to be persisted.
 *               Preparation creates a copy of the current region attributes, unless the attributes are already
 *               marked as dirty.
 *  \param[in]   RegionIdx            The relative index of the region inside the module it is assigned to.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_PreparePendingAttributes(
  vSwUpdM_RegionIdxType RegionIdx);

/**********************************************************************************************************************
 *  vSwUpdM_Region_UpdateSegmentStates()
 *********************************************************************************************************************/
/*! \brief       Update state of segments within the given region.
 *  \details     State of free and reserved segments within the given region are updated to given value.
 *  \param[in]   Region         Pointer to region structure.
 *  \param[in]   SegmentState   The state which should be applied to the segments.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateSegmentStates(
  P2CONST(vSwUpdM_VarRegionsType, AUTOMATIC, VSWUPDM_APPL_CONST) Region,
  vSwUpdM_SegmentStateType SegmentState);

/**************************************************************
 *  Memory Abstraction:
 *   - Segment
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Segment_PrepareAddressInfo()
 *********************************************************************************************************************/
/*! \brief       Prepare address information of segment.
 *  \details     Calculate missing value, when either only length or end address is given.
 *               Verify that values of length, end address and length handling are consistent.
 *  \param[in,out] SegmentInfo  The segment information to be prepared.
 *  \return      E_NOT_OK      Segment information is inconsistent.
 *  \return      E_OK          Segment information is consistent and prepared for further processing.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_PrepareAddressInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_IsAddAllowed()
 *********************************************************************************************************************/
/*! \brief       Verifies whether a new segment is allowed to be added.
 *  \details     Attributes of existing segment restricts the type of segment which can be added.
 *  \param[out]  TrailingSegmentClass   The class of trailing segment to be added in case the new segments doesn't use
 *                                      all available space.
 *  \param[in]   ActiveSegment          The active segment at the start address of the segment to be added.
 *  \param[in]   SegmentClass           The class of the segment to be added.
 *  \param[in]   StartAddress           The start address of the segment to be added.
 *  \return      FALSE                  Adding of segment isn't allowed.
 *  \return      TRUE                   Adding of segment is allowed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsAddAllowed(
  P2VAR(vSwUpdM_ClassOfVarSegmentsType, AUTOMATIC, VSWUPDM_APPL_VAR) TrailingSegmentClass,
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) ActiveSegment,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  vSwUpdM_AddressType StartAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_IsDuplicate()
 *********************************************************************************************************************/
/*! \brief       Checks if a new requested segment duplicates a existing segment.
 *  \details     -
 *  \param[in]   SegmentInfo   SegmentInfo of new segment.
 *  \param[in]   SegmentClass  SegmentClass of new segment.
 *  \param[in]   ActiveSegment Existing segment.
 *  \return      FALSE         New segment is not a duplicate.
 *  \return      TRUE          New segment is a duplicate.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsDuplicate(
  P2CONST(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) ActiveSegment);

/**********************************************************************************************************************
 *  vSwUpdM_Segment_GetFirstExternalSegmentInRange()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     Searches for the external segment in the given range, which was added first.
 *  \param[out]  SegmentId     The id of the first external segment within the specified range.
 *  \param[in]   StartAddress  The start address of the range.
 *  \param[in]   Length        The length of the range.
     *  \return      E_OK          At least one external segment was found within the range.
     *  \return      E_NOT_OK      No external segments was found within the range.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetFirstExternalSegmentInRange(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_AddressType EndAddress);

/**************************************************************
 *  Memory Abstraction:
 *   - Range
 **************************************************************/

/**************************************************************
 *  Memory Abstraction:
 *   - Buffer
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Buffer_CopyRemainder()
 *********************************************************************************************************************/
/*! \brief       Copy any remaining data from source to target buffer.
 *  \details     Data is copied from used area of source buffer to free area of target buffer.
 *  \param[in]   SourceBufferInfo   The buffer info referencing the source buffer.
 *  \param[in,out] TargetBufferInfo The buffer info referencing the target buffer.
 *  \return      E_OK         Remainder successfully copied from source to target buffer.
 *  \return      E_NOT_OK     Remaining data in source buffer exceeds available free space in target buffer.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     buffer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_CopyRemainder(
   P2CONST(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SourceBufferInfo,
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) TargetBufferInfo);

/**************************************************************
 *  Pipe handling
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalModeIdByType()
 *********************************************************************************************************************/
/*! \brief       Evaluate pipe mode configured for the given internal mode of the data process.
 *  \details     -
 *  \param[in]   DataProcessId  The ID of the requested data process.
 *  \param[in]   Type           The requested internal mode type.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(vStreamProc_ModeIdType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalModeIdByType(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_TypeOfIntModeType Type);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_UseConfiguredSettings()
 *********************************************************************************************************************/
/*! \brief       Helper function to apply configured settings for given mode to data process handling.
 *  \details     Applies ResumeOffset and ExplicitRestartHandling to affected segment.
 *  \param[in]   ExternalModeIndex
 *  \param[in]   Segment
 *  \param[in]   EntityIds Common structure containing entity information for the current request.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Pipe_UseConfiguredSettings(
  vSwUpdM_ExternalModeIterType ExternalModeIndex,
  vSwUpdM_VarSegmentsPtrType Segment,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds);

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode()
 *********************************************************************************************************************/
/*! \brief       Selects Mode definition for given Data Process by vStreamProc Mode.
 *  \details     This function loops over all (vSwUpdM) Modes until the right (vStreamProc) Mode is found.
 *  \param[in]   DataProcessId     Specified Data Process.
 *  \param[in]   ModeId            vStreamProc Mode to search for
 *  \param[out]  ExternalModeIndex Index of found Mode.
 *  \return E_OK     On success.
 *  \return E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     pipe
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode(
  vSwUpdM_DataProcessesIterType DataProcessId,
  CONST(vStreamProc_ModeIdType, AUTOMATIC) ModeId,
  P2VAR(vSwUpdM_ExternalModeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) ExternalModeIndex);

/**************************************************************
 *  Remote
 **************************************************************/

/**************************************************************
 *  Internal API:
 * - Stream
 **************************************************************/

/**************************************************************
 *  Service Dispatching
 **************************************************************/

/**************************************************************
 *  Callout handling
 **************************************************************/

/**************************************************************
 *  Job handling
 **************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_AlignedDataType, VSWUPDM_VAR_NOINIT) vSwUpdM_BufferWriteData[((vSwUpdM_GetMaxInputStreamSize() - 1u) / sizeof(vSwUpdM_AlignedDataType)) + 1u];

#define VSWUPDM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
VAR(boolean, VSWUPDM_VAR_NOINIT)     vSwUpdM_ImplicitModuleOpenFlag;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_EntityDataType, VSWUPDM_VAR_NOINIT)                 vSwUpdM_EntityData;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_VAR_NOINIT)         vSwUpdM_ResumeInfo;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_VAR_NOINIT)         vSwUpdM_PendingResumeInfo;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_AddressType, VSWUPDM_VAR_NOINIT)                    vSwUpdM_CheckpointAddress;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_ModulePendingAttributesType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ModulePendingAttributes;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_SegmentDynamicAttributesType, VSWUPDM_VAR_NOINIT)   vSwUpdM_SegmentPendingAttributes;
VAR(uint32, VSWUPDM_VAR_NOINIT)                                 vSwUpdM_SegmentPendingCount;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_ExternalSegmentsQueue;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_QueueType, VSWUPDM_VAR_NOINIT)          vSwUpdM_InternalSegmentsQueue;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoEraseRange;
VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoProcessInputStream;   /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoCopyMemory;   /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoWriteData;
VAR(vSwUpdM_BufferInfoType, VSWUPDM_VAR_NOINIT)     vSwUpdM_BufferInfoReadData;

/* PRQA S 3218 3 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_ProcessInfoType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ProcessUserData; /**< This structure will be filled for every process call and keeps the data for later processing */
VAR(vSwUpdM_ProcessDataType, VSWUPDM_VAR_NOINIT)    vSwUpdM_ProcessData;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_StreamDataType, VSWUPDM_VAR_NOINIT)     vSwUpdM_StreamData;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_PipelinedProgrammingType, VSWUPDM_VAR_NOINIT) vSwUpdM_PipelinedProgramming;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_RemoteStream_ListType, VSWUPDM_VAR_NOINIT) vSwUpdM_RemoteStream_List[VSWUPDM_REMOTESTREAMHANDLE_SIZE];
/* PRQA S 3218 2 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
/* If the local node is a slave, it has granted the lock to the master. */
VAR(vSwUpdM_NodeIterType, VSWUPDM_VAR_NOINIT)    vSwUpdM_RemoteLockIsGrantedTo;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * Internal comment removed.
 *
 *
 */
VAR(uint8, VSWUPDM_APPL_DATA)                       vSwUpdM_InitState                 = VSWUPDM_INIT_STATE_UNINIT;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_StateType, VSWUPDM_APPL_DATA)           vSwUpdM_GlobalState               = VSWUPDM_STATE_IDLE;

/*!
 * Internal comment removed.
 *
 *
 */
VAR(vSwUpdM_UpdateStateType, VSWUPDM_APPL_DATA)     vSwUpdM_UpdateState               = VSWUPDM_UPDATE_STATE_UNDEFINED;
/*!
 * Internal comment removed.
 *
 *
 */
VAR(boolean, VSWUPDM_APPL_DATA)                     vSwUpdM_ResumeInfoDirty           = FALSE;
VAR(boolean, VSWUPDM_APPL_DATA)                     vSwUpdM_PartitionAttributesDirty  = FALSE;

#define VSWUPDM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(vSwUpdM_SubScopeDefinitionType, VSWUPDM_CONST) vSwUpdM_SubScopeDefinitions[] =
{
  {
    vSwUpdMConf_vSwUpdMSubScope_SegmentListWritten,
      VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_REMOTE_EXECUTION
  },
  {
    vSwUpdMConf_vSwUpdMSubScope_SegmentListSyncCopy,
      VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_FREE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PARTIAL_SEGMENT
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_RESERVED_AREA
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SOURCE_ENTITES
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_OPEN_SEGMENT
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT
  },
  {
    vSwUpdMConf_vSwUpdMSubScope_SegmentListSyncCompare,
      VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_FREE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PARTIAL_SEGMENT
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_RESERVED_AREA
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SOURCE_ENTITES
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_FLUSH_SEGMENT
  },
  {
    vSwUpdMConf_vSwUpdMSubScope_SegmentListFullModule,
      VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENTS
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_USED
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_SEGMENT_CLASS_FREE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_PROVIDE_RANGE
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_RESERVED_AREA
    | VSWUPDM_SUB_SCOPE_ATTRIBUTE_REMOTE_EXECUTION
  },
  {
    0xFFu,
    VSWUPDM_SUB_SCOPE_ATTRIBUTE_NONE
  }
};

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSWUPDM_USE_INIT_POINTER == STD_ON)
P2CONST(vSwUpdM_ConfigType, VSWUPDM_VAR_NOINIT, VSWUPDM_INIT_DATA) vSwUpdM_ConfigDataPtr;
#endif

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**************************************************************
 *  Memory Abstraction:
 *   - General
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Init_CreatePartitionStructure
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreatePartitionStructure(void)
{
  vSwUpdM_PartitionIterType       partitionId;
  vSwUpdM_VarPartitionsPtrType    partition;

  /* #10 For all configured partitions */
  for (partitionId = 0; partitionId < vSwUpdM_GetStaticNumberOfPartitions(); partitionId++)
  {
    partition = vSwUpdM_GetAddrVarPartitions(partitionId);

    /* #20 Assign configured values to variable representation. */
    partition->HandleIDOfVarPartitions                    = vSwUpdM_GetPartitionHandleOfPartition(partitionId);
    partition->AddrAreaIdOfPartitions                     = vSwUpdM_GetAddrAreaIdOfPartition(partitionId);
    /* #30 Evaluate swappable attribute, which is dependent on other configuration aspects. */
    partition->SwappableOfVarPartitions                   = vSwUpdM_Part_IsPartitionSwappable((vSwUpdM_PartitionIdType)partitionId);
    /* #40 Initialize dynamic attributes and mark as non-dirty. */
    partition->DynamicAttributesOfVarPartitions.Revision  = 0u;
    partition->DynamicAttributesOfVarPartitions.State     = VSWUPDM_PART_STATE_UNDEFINED;
    partition->DynamicAttributesOfVarPartitions.IsValid   = VSWUPDM_VALIDITY_INVALID;
    partition->PendingAttributesOfVarPartitions           = partition->DynamicAttributesOfVarPartitions;
    partition->AffectedState                              = VSWUPDM_PART_STATE_UNDEFINED;
    partition->AttributesDirty                            = FALSE;
  }
} /* vSwUpdM_Init_CreatePartitionStructure */

/**********************************************************************************************************************
 * vSwUpdM_Init_CreateModuleStructure
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
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreateModuleStructure(void)
{
  vSwUpdM_ModuleIterType              moduleId;
  vSwUpdM_VarModulesPtrType module;

  /* #10 For all modules */
  for (moduleId = 0u; moduleId < vSwUpdM_GetStaticNumberOfModules(); moduleId++)
  {
    vSwUpdM_PartitionGroupIterType      partitionGroupId;
    uint32                              partitionCount;
    vSwUpdM_PartitionIterType           partitionIdx;
    vSwUpdM_HandleIDOfVarPartitionsType relativePartitionIdx;

    /* #20 Assign configured values to variable representation. */
    module = vSwUpdM_GetAddrVarModules(moduleId);

    module->HandleIDOfVarModules        = vSwUpdM_GetModuleHandleOfModule(moduleId);
    module->MandatoryOfVarModules       = vSwUpdM_IsMandatoryOfModule(moduleId);    /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
    module->MetaDataAddressOfVarModules = vSwUpdM_GetMetaDataAddressOfModule(moduleId);
    module->TypeOfVarModules            = vSwUpdM_GetModuleTypeOfModule(moduleId);

    /* #21 Evaluate and assign partition group related values. */
    partitionGroupId  = vSwUpdM_GetPartitionGroupIdxOfModule(moduleId);
    partitionCount    = vSwUpdM_GetNumPartitionOfPartitionGroup(partitionGroupId);
    partitionIdx      = vSwUpdM_GetPartitionGroupIdxOfPartitionGroup(partitionGroupId);

    module->PartitionGroupIdOfVarModules  = (vSwUpdM_PartitionGroupIdType)partitionGroupId;
    module->PartitionCountOfVarModules    = partitionCount;

    /* #30 If number of partitions in partition group assigned to module is greater as one */
    if (partitionCount > 1u)
    {
      /* #31 Mark module as swappable. */
      module->SwappableOfVarModules = TRUE;
    }
    /* #32 Otherwise */
    else
    {
      /* #33 Mark module as non-swappable. */
      module->SwappableOfVarModules = FALSE;
    }

    /* #40 For all partition in partition group assigned to module */
    for (relativePartitionIdx = 0u; relativePartitionIdx < partitionCount; relativePartitionIdx++)
    {
      /* #41 Initialize attributes of specific module instance in partition. */
      vSwUpdM_PartitionIterType partitionId = vSwUpdM_GetPartitionOfPartitionGroup2Partition(partitionIdx + relativePartitionIdx);
      P2VAR(vSwUpdM_ModuleDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) attributes = &module->DynamicAttributesOfVarModules[relativePartitionIdx];

      /* #42 Assign partition ID. */
      module->PartitionIdsOfVarModules[relativePartitionIdx] = (vSwUpdM_PartitionIdType)partitionId;

      /* #43 Set attributes to default values. */
      attributes->Revision            = 0u;
      attributes->State               = VSWUPDM_MODULE_STATE_UNDEFINED;
      attributes->IsValid             = VSWUPDM_VALIDITY_INVALID;
      attributes->ProgrammingAttempts = 0u;
    }

    /* #50 Set partition ID of unused entries to invalid value. */
    for (; relativePartitionIdx < VSWUPDM_ARRAY_SIZE(module->PartitionIdsOfVarModules); relativePartitionIdx++)
    {
      module->PartitionIdsOfVarModules[relativePartitionIdx] = VSWUPDM_INVALID_ID;
    }
  }
} /* vSwUpdM_Init_CreateModuleStructure */

/**********************************************************************************************************************
 * vSwUpdM_Init_CreateMemoryStructure
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_CreateMemoryStructure(void)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Reset resume information. */
  vSwUpdM_ResumeInfo_ResetState();

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_Init_RemoteStream();
#endif

  /* #20 Initialize entity, stream data and pipelined programming. */
  vSwUpdM_Init_InitEntityData();
  vSwUpdM_Init_InitStreamData();
  vSwUpdM_Init_InitProcessData();
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
  vSwUpdM_Init_InitPipelinedProgramming();
#endif

  /* #30 Create partition and module structures. */
  vSwUpdM_Init_CreatePartitionStructure();
  vSwUpdM_Init_CreateModuleStructure();
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Init_CreateMemoryStructure */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Init_Start
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Init_Start(vSwUpdM_NodeIterType Source)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32 i;

  /* #10 Create memory structure in RAM. */
  vSwUpdM_Init_CreateMemoryStructure();
  /* #20 Reset initialization and job processing states. */
  if (vSwUpdM_GlobalState != VSWUPDM_STATE_SHUT_DOWN)
  {
    vSwUpdM_RemoteLockIsGrantedTo = VSWUPDM_INVALID_NODE;
    for (i = 0; i < vSwUpdM_GetSizeOfNode(); i++)
    {
      vSwUpdM_SetLockedOfVarNode(i, FALSE);
      vSwUpdM_SetResponseValidOfVarNode(i, FALSE);
      vSwUpdM_SetResponseProcessingOfVarNode(i, FALSE);
    }

    vSwUpdM_GridChannel_Init();
    vSwUpdM_GridNode_Init();
    vSwUpdM_GridSrvc_Init();
    vSwUpdM_SrvcRouting_Init();

    vSwUpdM_Bookkeeper_Init();
  }

  vSwUpdM_InitState   = VSWUPDM_INIT_STATE_PENDING;
  vSwUpdM_GlobalState = VSWUPDM_STATE_IDLE;

  /* #30 Setup job objects. */
  vSwUpdM_Init_SetupJobs();

  /* Because the call of vSwUpdM_Init_Start() is already encapsulated in critical section checks,
   * a critical section is not required here to protect the access on the job queue.*/

  /* #40 Spawn job to initialize component, by evaluating persisted states from previous cycles. */
  (void)vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_INIT_COMPONENT, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, NULL_PTR, Source);

  return retVal;

  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Init_Start */

/**********************************************************************************************************************
 * vSwUpdM_General_CommonNegDetChecks()
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
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_CommonNegDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks,
  vSwUpdM_StateCheckType StateCheck)
{
  /* #10 Default to no error. */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* #20 Check for pending stream if requested. */
  if ( (DetChecks >= VSWUPDM_COMMON_DET_CHECK_STREAM)
    && (vSwUpdM_StreamData.State == VSWUPDM_STREAM_STATE_IDLE) )
  {
    errorId = VSWUPDM_E_NO_STREAM_STARTED;  /* PRQA S 2982 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  }

  /* #30 Check for open segment if requested. */
  if ( (DetChecks >= VSWUPDM_COMMON_DET_CHECK_SEGMENT)
    && (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId == VSWUPDM_INVALID_ID) )
  {
    errorId = VSWUPDM_E_NO_SEGMENT_OPENED;
  }

  /* #40 Check for open module if requested. */
  if ( (DetChecks >= VSWUPDM_COMMON_DET_CHECK_MODULE)
    && (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID) )
  {
    errorId = VSWUPDM_E_NO_MODULE_OPENED;
  }

  /* #50 Check for open partition if requested. */
  if ( (DetChecks >= VSWUPDM_COMMON_DET_CHECK_PARTITION)
    && (vSwUpdM_EntityData.OpenIds.PartitionId == VSWUPDM_INVALID_ID) )
  {
    errorId = VSWUPDM_E_NO_PARTITION_OPENED;
  }

  /* #60 Check for idle operation state if requested. */
  switch (StateCheck)
  {
    case VSWUPDM_STATE_CHECK_IDLE:
    {
      if (vSwUpdM_GlobalState != VSWUPDM_STATE_IDLE)
      {
        errorId = VSWUPDM_E_NOT_IDLE;
      }

      break;
    }
    case VSWUPDM_STATE_CHECK_PIPELINED:
    {
      switch (vSwUpdM_GlobalState)
      {
        case VSWUPDM_STATE_IDLE:
        {
          break;
        }
#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
        case VSWUPDM_STATE_ACTIVE:
        case VSWUPDM_STATE_PENDING:
        {
          if (vSwUpdM_PipelinedProgramming.State != VSWUPDM_PIPELINED_STATE_PENDING)
          {
            errorId = VSWUPDM_E_NOT_IDLE;
          }

          break;
        }
#endif
        default:
        {
          errorId = VSWUPDM_E_NOT_IDLE;
          break;
        }
      }

      break;
    }
    case VSWUPDM_STATE_CHECK_NONE:
    default:
    /* Otherwise: Global state don't care */
    {
      break;
    }
  }

  /* #70 Check initialization state of component. */
  if (vSwUpdM_General_IsModuleInitialized() == FALSE)
  {
    errorId = VSWUPDM_E_NOT_INITIALIZED;
  }

  /* #80 Report any error in both output parameter and result. */
  *ErrorId = errorId;

  return errorId;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_General_CommonNegDetChecks */

#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_General_ExtNegDetChecks()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_ExtNegDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks,
  vSwUpdM_StateCheckType StateCheck,
  vSwUpdM_NodeIterType Source)
{
  vSwUpdM_ErrorCode errorId;

  /* #10 Perform most common DET checks. */
  errorId = vSwUpdM_General_CommonNegDetChecks(&errorId, DetChecks, StateCheck);

  /* #20 If no error was detected yet, check whether source node exceeds valid range. */
  if ( (errorId == VSWUPDM_E_NO_ERROR)
    && (Source >= vSwUpdM_GetSizeOfNode()) )
  {
    errorId = VSWUPDM_E_OUT_OF_RANGE;
  }

  /* #30 Report any error in both output parameter and result. */
  *ErrorId = errorId;

  return errorId;
} /* vSwUpdM_General_ExtNegDetChecks */

/**********************************************************************************************************************
 * vSwUpdM_General_CommonPosDetChecks()
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
FUNC(vSwUpdM_ErrorCode, VSWUPDM_CODE) vSwUpdM_General_CommonPosDetChecks(
  P2VAR(vSwUpdM_ErrorCode, AUTOMATIC, VSWUPDM_APPL_VAR) ErrorId,
  vSwUpdM_CommonDetCheckType DetChecks)
{
  /* #10 Default to no error. */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* #100 If initialization state shall be checked */
  if (DetChecks == VSWUPDM_COMMON_DET_CHECK_INITIALIZED)
  {
    /* #110 Check initialization state of component. */
    if (vSwUpdM_General_IsModuleInitialized() == TRUE)
    {
      errorId = VSWUPDM_E_ALREADY_INITIALIZED;
    }
  }
  /* #200 Otherwise */
  else
  {
    /* #210 Check for open module if requested. */
    if ( (DetChecks <= VSWUPDM_COMMON_DET_CHECK_MODULE)
      && (vSwUpdM_EntityData.OpenIds.ModuleId != VSWUPDM_INVALID_ID) )
    {
      errorId = VSWUPDM_E_MODULE_STILL_OPENED;
    }

    /* #220 Check for open segment if requested. */
    if ( (DetChecks <= VSWUPDM_COMMON_DET_CHECK_SEGMENT)
      && (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID) )
    {
      errorId = VSWUPDM_E_SEGMENT_STILL_OPENED;
    }

    /* #230 Check for pending stream if requested. */
    if ( (DetChecks <= VSWUPDM_COMMON_DET_CHECK_STREAM)
      && (vSwUpdM_StreamData.State != VSWUPDM_STREAM_STATE_IDLE) )
    {
      errorId = VSWUPDM_E_STREAM_PENDING;
    }
  }

  /* #240 Report any error in both output parameter and result. */
  *ErrorId = errorId;

  return errorId;
} /* vSwUpdM_General_CommonPosDetChecks */
#endif

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_GetSegmentCandidate
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
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetSegmentCandidate(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  vSwUpdM_AddressType Address)
{
  Std_ReturnType              retVal              = E_NOT_OK;
  vSwUpdM_AddressType         sectorStartAddress  = Address;
  vSwUpdM_AddressType         sectorEndAddress    = Address;
  vSwUpdM_AddressType         resumeAddress;
  vSwUpdM_SegmentIdValueType  segmentId;

  /* #10 Evaluate start and end address of sector (in opened partition) affected by given address. */
  (void)vSwUpdM_Range_AlignAddress(&sectorStartAddress, vSwUpdM_EntityData.OpenIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT,  VSWUPDM_ALIGN_GRANULARITY_SECTOR);
  (void)vSwUpdM_Range_AlignAddress(&sectorEndAddress,   vSwUpdM_EntityData.OpenIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_BACK,   VSWUPDM_ALIGN_GRANULARITY_SECTOR);

  /* #100 Determine the first external segment which is affected by erasing the sector.
   *   If any is affected */
  if (vSwUpdM_Segment_GetFirstExternalSegmentInRange(&segmentId, sectorStartAddress, sectorEndAddress) == E_OK)
  {
    /* #110 The resume address is the start address of the segment, when starting within the sector.
     *   Otherwise it is the start address of the sector. */
    resumeAddress = vSwUpdM_GetVarSegments(segmentId).DynamicAttributesOfVarSegment.StartAddress;
    if (resumeAddress < sectorStartAddress)
    {
      resumeAddress = sectorStartAddress;
    }

    /* #120 Return ID of segment candidate and resume address. */
    *SegmentId      = segmentId;
    *ResumeAddress  = resumeAddress;

    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_ResumeInfo_GetSegmentCandidate */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_EvalSegmentCandidate
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
 */
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_ResumeInfo_EvalSegmentCandidate(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) FirstSegmentId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  vSwUpdM_AddressType Address)
{
  boolean                     changed         = FALSE;
  vSwUpdM_SegmentIdValueType  firstSegmentId  = *FirstSegmentId;
  vSwUpdM_AddressType         resumeAddress   = *ResumeAddress;
  vSwUpdM_SegmentIdValueType  segmentIdCandidate;
  vSwUpdM_AddressType         addressCandidate;

  /* #100 Evaluate potential segment candidate for requested address. */
  if (vSwUpdM_ResumeInfo_GetSegmentCandidate(&segmentIdCandidate, &addressCandidate, Address) == E_OK)
  {
    /* #110 If no segment was found yet or the potential candidate was added before the current one */
    if ( (firstSegmentId == VSWUPDM_INVALID_ID)
      || (vSwUpdM_GetVarSegments(segmentIdCandidate).ExternalSegmentIdx < vSwUpdM_GetVarSegments(firstSegmentId).ExternalSegmentIdx) )
    {
      /* #111 Take over potential segment candidate and remember that value was changed. */
      firstSegmentId  = segmentIdCandidate;
      resumeAddress   = addressCandidate;
      changed         = TRUE;
    }
    /* #120 Otherwise, if this is the same candidate as before, but the resume address is smaller */
    else
    {
      if ( (segmentIdCandidate == firstSegmentId)
      && (addressCandidate < resumeAddress) )
      {
        /* #121 Take over new resume address and remember that value was changed. */
        resumeAddress   = addressCandidate;
        changed         = TRUE;
      }
    }
  }

  /* #200 Return ID of current segment candidate and resume address. */
  *FirstSegmentId = firstSegmentId;
  *ResumeAddress  = resumeAddress;

  return changed;
} /* vSwUpdM_ResumeInfo_EvalSegmentCandidate */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_GetResumeAddress
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
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetResumeAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeAddress,
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeSegmentId,
  vSwUpdM_SegmentIdValueType SegmentId,
  vSwUpdM_AddressType CheckpointAddress)
{
  Std_ReturnType              retVal            = E_NOT_OK;
  vSwUpdM_VarSegmentsPtrType  segment           = vSwUpdM_GetAddrVarSegments(SegmentId);
  vSwUpdM_AddressType         checkpointAddress = CheckpointAddress;
  vSwUpdM_SegmentIdValueType  firstSegmentId    = SegmentId;
  boolean                     changed           = FALSE;
  vSwUpdM_AddressType         resumeAddress;
  vSwUpdM_AddressType         endAddress;

  /* #10 Unless the checkpoint is located at the very start of the address space
   *   Use address just before checkpoint. */
  if (checkpointAddress > 0u)
  {
    checkpointAddress--;
  }

  /* #20 Unintended interruption of writing to the given segment affects everything up to
   *   the reserved end address of the segment or the address just before the next checkpoint,
   *   whichever comes first. */
  endAddress = segment->ReservedEndAddressOfVarSegments;
  if (checkpointAddress < endAddress)
  {
    endAddress = checkpointAddress;
  }

  /* #30 Evaluate the first segment affected by erasing the sector at the current write address. */
  vSwUpdM_Segment_GetApparentWriteAddress(segment, &resumeAddress);
  if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, resumeAddress) == TRUE)
  {
    changed = TRUE;
  }

  /* #40 Evaluate the first segment affected by erasing the sector at the end of the potentially affected range. */
  if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, endAddress) == TRUE)
  {
    changed = TRUE;
  }

  /* #100 While the potential segment candidate has changed */
  while (changed == TRUE)
  {
    vSwUpdM_VarSegmentsIterType segmentIdx;

    changed = FALSE;
    segment = vSwUpdM_GetAddrVarSegments(firstSegmentId);

    /* #110 Evaluate the first segment affected by erasing the sector at the current resume address. */
    if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, resumeAddress) == TRUE)
    {
      changed = TRUE;
    }

    /* #120 If segment is already partially written
     *   Evaluate the first segment affected by erasing the sector at the last written address. */
    if (segment->WriteAddressOfVarSegments > segment->ReservedStartAddressOfVarSegments)
    {
      if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, (segment->WriteAddressOfVarSegments - 1u)) == TRUE)
      {
        changed = TRUE;
      }
    }

    /* #200 Iterate over all segments which were added after the first affected segment. */
    for (segmentIdx = ((vSwUpdM_VarSegmentsIterType)segment->ExternalSegmentIdx + 1u); segmentIdx < vSwUpdM_EntityData.Count.ExternalSegmentCount; segmentIdx++)
    {
      vSwUpdM_SegmentIdType segmentId;

      if (vSwUpdM_GetSegmentIdOfModuleByIndex(&segmentId, vSwUpdM_EntityData.OpenIds.ModuleId, (uint32)segmentIdx) == E_OK)
      {
        segment = vSwUpdM_GetAddrVarSegments(segmentId.DynamicSegmentId);

        /* #210 Evaluate the first segment affected by erasing the sector at the reserved start address of the current segment. */
        if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, segment->ReservedStartAddressOfVarSegments) == TRUE)
        {
          changed = TRUE;
        }

        /* #220 If segment is already partially written
         *   Evaluate the first segment affected by erasing the sector at the last written address of the current segment. */
        if (segment->WriteAddressOfVarSegments > segment->ReservedStartAddressOfVarSegments)
        {
          if (vSwUpdM_ResumeInfo_EvalSegmentCandidate(&firstSegmentId, &resumeAddress, (segment->WriteAddressOfVarSegments - 1u)) == TRUE)
          {
            changed = TRUE;
          }
        }
      }
    }
  }

  /* #300 Return the evaluated resume address and first affected segment. */
  *ResumeAddress    = resumeAddress;
  *ResumeSegmentId  = firstSegmentId;

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_ResumeInfo_GetResumeAddress */
#endif

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_GetCheckpointAddress
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_GetCheckpointAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) CheckpointAddress,
  vSwUpdM_AddressType WriteAddress,
  vSwUpdM_PartitionIdType PartitionId)
{
  /* #10 Default to maximum address value when no checkpoint could be found. */
  vSwUpdM_AddressType checkpointAddress = VSWUPDM_MAX_ADDRESS;

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
  vSwUpdM_CheckpointAddressesIterType  checkpointIdx;

  /* #100 Iterate over all checkpoints of the requested partition. */
  for (checkpointIdx = vSwUpdM_GetCheckpointAddressesStartIdxOfPartition(PartitionId); checkpointIdx < vSwUpdM_GetCheckpointAddressesEndIdxOfPartition(PartitionId); checkpointIdx++)
  {
    /* #110 If current checkpoint is located behind the given write address. */
    if (vSwUpdM_GetCheckpointAddresses(checkpointIdx) > WriteAddress)
    {
      /* #111 Relevant checkpoint found: Finish search. */
      checkpointAddress = vSwUpdM_GetCheckpointAddresses(checkpointIdx);

      break;
    }
  }
#else
  VSWUPDM_DUMMY_STATEMENT(WriteAddress);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  *CheckpointAddress = checkpointAddress;
} /* vSwUpdM_ResumeInfo_GetCheckpointAddress */

/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_UpdateState
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
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_ResumeInfo_UpdateState(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ServiceIdType CurrentService,
  vSwUpdM_ResumeStateType ServiceState,
  vSwUpdM_AddressType MemoryAddress,
  vSwUpdM_AddressType StreamAddress,
  vSwUpdM_AddressType TriggerAddress,
  vSwUpdM_ValidType IsAddressValid)
{
  /* ----- Local Variables ------------------------------------------------ */
#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
  vSwUpdM_AddressType triggerAddress  = TriggerAddress;
#else
  /* Ignore trigger address when fine-grained resume is disabled.
   * Prevents unnecessary update of resume information without providing any informational value. */
  vSwUpdM_AddressType triggerAddress  = MemoryAddress;
#endif
  boolean resumeInfoDirty             = FALSE;

  VSWUPDM_DUMMY_STATEMENT(TriggerAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If valid service ID is given and it doesn't match the current value in the resume information
   *   Update value and mark resume information as "dirty". */
  if ( (CurrentService != VSWUPDM_SID_NONE)
    && (CurrentService != vSwUpdM_ResumeInfo.ResumeInfo.CurrentService) )
  {
    vSwUpdM_ResumeInfo.ResumeInfo.CurrentService = CurrentService;
    resumeInfoDirty                   = TRUE;
  }

  /* #100 If valid service ID is present in resume information. */
  if (vSwUpdM_ResumeInfo.ResumeInfo.CurrentService != VSWUPDM_SID_NONE)
  {
    if ( (PartitionState != VSWUPDM_PART_STATE_UNDEFINED)
      && (PartitionState != vSwUpdM_ResumeInfo.ResumeInfo.PartitionState) )
    {
      vSwUpdM_ResumeInfo.ResumeInfo.PartitionState = PartitionState;
      resumeInfoDirty                   = TRUE;
    }

    /* #120 If valid service state is given and it doesn't match the current value in the resume information
     *   Update value and mark resume information as "dirty". */
    if ( (ServiceState != VSWUPDM_RESUME_STATE_UNDEFINED)
      && (ServiceState != vSwUpdM_ResumeInfo.ResumeInfo.ServiceState) )
    {
      vSwUpdM_ResumeInfo.ResumeInfo.ServiceState = ServiceState;
      resumeInfoDirty                 = TRUE;
    }

    /* #130 If valid address is given and it doesn't match the current value in the resume information
     *   Update value and mark resume information as "dirty". */
    if (IsAddressValid == TRUE)
    {
      if (MemoryAddress != vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress)
      {
        vSwUpdM_ResumeInfo.ResumeInfo.MemoryAddress  = MemoryAddress;
        resumeInfoDirty             = TRUE;
      }

      if (StreamAddress != vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress)
      {
        vSwUpdM_ResumeInfo.ResumeInfo.StreamAddress = StreamAddress;
        resumeInfoDirty = TRUE;
      }

      if (triggerAddress != vSwUpdM_ResumeInfo.TriggerAddress)
      {
        vSwUpdM_ResumeInfo.TriggerAddress = triggerAddress;
        resumeInfoDirty                   = TRUE;
      }
    }

    /* #140 If given doesn't match the current value of the address validity flag in the resume information
     *   Update value and mark resume information as "dirty". */
    if (IsAddressValid != vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid)
    {
      vSwUpdM_ResumeInfo.ResumeInfo.IsAddressValid = IsAddressValid;
      resumeInfoDirty                   = TRUE;
    }
  }

  if (resumeInfoDirty == TRUE)
  {
    vSwUpdM_ResumeInfoDirty = TRUE;
  }
  /* PRQA S 6010, 6030, 6060 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STPAR */
} /* vSwUpdM_ResumeInfo_UpdateState */

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_ResumeInfo_PersistForNextCheckpoint
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ResumeInfo_PersistForNextCheckpoint(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_SegmentIdValueType SegmentId,
  vSwUpdM_AddressType Address,
  boolean WritePending,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType              retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_SegmentIdValueType  resumeSegmentId;
  vSwUpdM_VarSegmentsPtrType  resumeSegment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_ServiceIdType       resumeService = vSwUpdM_ResumeInfo.ResumeInfo.CurrentService;
  vSwUpdM_AddressType         resumeAddress = Address;
  vSwUpdM_AddressType         streamAddress;

  /* #10 If triggered by a pending write operation
   *   Increment address by one. */
  if (WritePending == TRUE)
  {
    resumeAddress++;
  }

  /* #20 Search next checkpoint behind current address. */
  vSwUpdM_ResumeInfo_GetCheckpointAddress(&vSwUpdM_CheckpointAddress, resumeAddress, PartitionId);
  /* #30 Evaluate resume address and first affected segment for given segment and checkpoint. */
  (void)vSwUpdM_ResumeInfo_GetResumeAddress(&resumeAddress, &resumeSegmentId, SegmentId, vSwUpdM_CheckpointAddress);

  resumeSegment = vSwUpdM_GetAddrVarSegments(resumeSegmentId);

  /* #40 If first affected segment holds actual data and resuming would erase parts of the data already written
   *   Update sequence has to roll-back to service ProcessStreamData to re-request data. */
  if ( (resumeSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
    && (resumeAddress < resumeSegment->WriteAddressOfVarSegments) )
  {
    resumeService = VSWUPDM_SID_PROCESS_STREAM_DATA;
  }

  /* #50 Always point to next address in data stream. */
  (void)vSwUpdM_ResumeInfo_CalculateStreamAddress(resumeSegment, resumeAddress, &streamAddress);

  /* #60 Update resume information with changed values and trigger persisting. */
  retVal = vSwUpdM_ResumeInfo_UpdateAndPersistState(PartitionState, resumeService, VSWUPDM_RESUME_STATE_ACTIVE, resumeAddress, streamAddress, Address, TRUE, Source);

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_ResumeInfo_PersistForNextCheckpoint */
#endif

/**********************************************************************************************************************
 * vSwUpdM_Stream_Open
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Stream_Open(
  vSwUpdM_SegmentIdType SegmentId,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_TypeOfIntModeType InternalMode,
  vSwUpdM_ProcessingOperationType ExternalOperation)
{
  Std_ReturnType                retVal = E_OK;
  vSwUpdM_VarSegmentsPtrType    segment = vSwUpdM_GetAddrVarSegments(SegmentId.DynamicSegmentId);

  /* #10 If previously processed segment doesn't match the requested one
   *   or no segment was processed before */
  if (vSwUpdM_StreamData.SegmentId != SegmentId.DynamicSegmentId)
  {
    /* #11 Initialize the pipe used for the processing of the input data stream. */
    retVal = vStreamProc_InitPipe(vSwUpdM_StreamData.PipeId);
  }

  /* #20 Open the pipe used for the processing of the input data stream. */
  if (retVal == E_OK)
  {
    retVal = vStreamProc_Open(vSwUpdM_StreamData.PipeId);
  }

  /* #100 If previously processed segment doesn't match the requested one
   *   or no segment was processed before */
  if (vSwUpdM_StreamData.SegmentId != SegmentId.DynamicSegmentId)
  {
    vSwUpdM_ExternalModeIterType externalModeIndex = VSWUPDM_NO_EXTDATAINPUTSTARTIDXOFDATAPROCESSES;
    vStreamProc_ModeIdType extPipeMode = VSTREAMPROC_NO_MODE; /* PRQA S 2981 */ /* MD_MSR_RetVal */

    if (retVal == E_OK)
    {
      vStreamProc_ModeIdType intPipeMode = vSwUpdM_Pipe_GetInternalModeIdByType(vSwUpdMConf_vSwUpdMDataProcess_StreamData, InternalMode);

      /* #110 Set pipe mode based on the internal mode. */
      if (vStreamProc_SetMode(vSwUpdM_StreamData.PipeId, intPipeMode) != E_OK)
      {
        retVal = VSWUPDM_E_INVALID_STREAM_OPERATION;
      }
    }

    if (retVal == E_OK)
    {
      extPipeMode = vStreamProc_GetModeByHandle(vSwUpdM_StreamData.PipeId, ExternalOperation);

      /* #120 Search configured vSwUpdM settings for this mode. */
      retVal = vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode(vSwUpdMConf_vSwUpdMDataProcess_StreamData, extPipeMode, &externalModeIndex);

      if (retVal == E_OK)
      {
        /* #130 Set pipe mode based on the external operation. */
        if (vStreamProc_SetMode(vSwUpdM_StreamData.PipeId, extPipeMode) != E_OK)
        {
          retVal = VSWUPDM_E_INVALID_STREAM_OPERATION;
        }
      }

    }

    if (retVal == E_OK)
    {
      vSwUpdM_AddressType apparentWriteAddress;

      /* #140 If found: Use configured settings. */
      vSwUpdM_Pipe_UseConfiguredSettings(externalModeIndex, segment, EntityIds);

      /* #150 Get write address of the current segment. */
      vSwUpdM_Segment_GetApparentWriteAddress(segment, &apparentWriteAddress);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      /* If a data stream is dedicated for the local node, ranges must be provided to the pipe.
       * A remote-only stream will not consume these ranges.
       */
      if (InternalMode == (vSwUpdM_TypeOfIntModeType)vSwUpdMConf_vSwUpdMModeType_Local)
#endif
      {
        /* #160 Pass current write address and length till end of segment to pipe. */
        retVal = vSwUpdM_Pipe_WriteRangeInfo(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputRange, apparentWriteAddress, (segment->EndAddressOfVarSegments - apparentWriteAddress) + 1u);
      }
    }

    if (retVal == E_OK)
    {
      vSwUpdM_EntityIdsType entityIds;

      entityIds = *EntityIds;
      entityIds.SegmentId = SegmentId;

      /* #170 Pass given entity IDs, including current segment ID to pipe. */
      retVal = vSwUpdM_Pipe_WriteEntityIds(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputEntities, &entityIds);
    }
  }

  if (retVal == E_OK)
  {
    if (vSwUpdM_Pipe_HasInternalEntryPoint(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputOperation) == TRUE)
    {

      /* #200 If operation port is available,
        * and operation port must be fed: */
      if (vSwUpdM_StreamData.RestartHandling == TRUE)
      {
        vSwUpdM_ProcNodeOperationType procOperation = VSWUPDM_PROC_NODE_OPERATION_START;

        if (segment->WriteAddressOfVarSegments > segment->ReservedStartAddressOfVarSegments)
        {
          procOperation = VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART;
        }

        /* #210 Set operation of pipe. */
        retVal = vSwUpdM_Pipe_WriteProcessOperation(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataInputType_InputOperation, procOperation);

        vSwUpdM_StreamData.PipeStarted = TRUE;
      }
    }
  }

  /* #300 If pipe operations were successful so far
   *   Remember currently processed segment ID. */
  if (retVal == E_OK)
  {
    vSwUpdM_StreamData.SegmentId  = SegmentId.DynamicSegmentId;
    vSwUpdM_StreamData.PipeState  = VSWUPDM_PIPE_STATE_PROCESSING;
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Stream_Open */

/**********************************************************************************************************************
 * vSwUpdM_Stream_Abort
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Stream_Abort(vSwUpdM_JobPtrType Job)
{
  /* #10 Change state of opened module to "undefined". */
  (void)vSwUpdM_Module_UpdateAndPersistState(Job->EntityIds.PartitionId, Job->EntityIds.PartitionState, Job->EntityIds.ModuleId, VSWUPDM_MODULE_STATE_UNDEFINED, Job, Job->Source);
  /* #20 Update resume information: Set state to "failed" and invalidate resume address. */
  vSwUpdM_ResumeInfo_UpdateState(VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_FAILED, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, VSWUPDM_UNDEFINED_ADDRESS, FALSE);
} /* vSwUpdM_Stream_Abort */

/**********************************************************************************************************************
 * vSwUpdM_Stream_CopyData
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Stream_CopyData(
  vStreamProc_EntryPointInfoPtrType DataEntryPoint,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessingLength,
  P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) InputBuffer)
{
  Std_ReturnType                retVal = E_NOT_OK;
  vSwUpdM_StreamDataInfoType    streamData;
  vSwUpdM_StreamLengthType      availableLength;

  /* #10 Initialize parameter structure for copy callout.
   *   Provide pointer to free area of output buffer.
   *   Segment copying into smaller chunks, determined by processing length.
   *   Offset into input stream determined by position of virtual input buffer. */
  streamData.DataPtr = vStreamProc_GetTypedWriteRequestBuffer_uint8(&DataEntryPoint->WriteRequest);
  streamData.Length  = *ProcessingLength;
  streamData.Offset  = InputBuffer->Position;

  availableLength = 0u;

  /* #100 Call copy callout and evaluate result. */
  switch (UL_vSwUpdMCopyStreamData(&streamData, &availableLength))
  {
    case BUFREQ_OK:
    /* #110 If copy request was successful */
    {
      /* #111 Acknowledge data written to the pipe entry point. */
      vSwUpdM_StreamLengthType storageAvalailableLength = DataEntryPoint->WriteRequest.StorageInfo.AvailableLength;

      if (vStreamProc_AcknowledgeEntryPoint(
          vSwUpdM_GetPipeIdOfDataProcesses(vSwUpdMConf_vSwUpdMDataProcess_StreamData),
          streamData.Length,
          TRUE,
          DataEntryPoint) == VSTREAMPROC_OK)
      {
        /* #112 Consume copied length from virtual input buffer. */
        (void)vSwUpdM_Buffer_ConsumeData(InputBuffer, streamData.Length);

        /* #113 Report back length which was actually copied. */
        *ProcessingLength = streamData.Length;

        /* #114 If either output buffer is completely filled or input data stream was completely consumed
         *   Report success. */
        if ( (storageAvalailableLength == streamData.Length)
          || (InputBuffer->Used == 0u) )
        {
          retVal = E_OK;
        }
        /* #115 Otherwise: Continue copying in next job cycle. */
        else
        {
          retVal = VSWUPDM_E_PENDING;
        }
      }

      break;
    }
    case BUFREQ_E_BUSY:
    /* #120 If copy request couldn't be fulfilled temporarily */
    {
      /* #121 Acknowledge zero bytes to release write lock.
       *   Retry copying in next job cycle. */
       if (vStreamProc_AcknowledgeEntryPoint(
          vSwUpdM_GetPipeIdOfDataProcesses(vSwUpdMConf_vSwUpdMDataProcess_StreamData),
          0u,
          TRUE,
          DataEntryPoint) == VSTREAMPROC_OK)
      {
        retVal = VSWUPDM_E_PENDING;
      }

      break;
    }
    case BUFREQ_E_NOT_OK:
    case BUFREQ_E_OVFL:
    default:
    /* #130 If copy request failed, requested length couldn't be provided or otherwise
      *   Report failed callout in job result. */
    {
      retVal = VSWUPDM_E_CALLOUT_FAILED;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_Stream_CopyData */

/**********************************************************************************************************************
 * vSwUpdM_Stream_Process
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
 */
FUNC(vSwUpdM_StreamProcessResultType, VSWUPDM_CODE) vSwUpdM_Stream_Process(void)
{
  vSwUpdM_StreamProcessResultType retVal        = VSWUPDM_STREAMPROCRESULT_FAIL; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 Trigger processing of stream data pipe and evaluate result. */
  vStreamProc_ReturnType          pipeResult    = vStreamProc_Process(vSwUpdM_StreamData.PipeId);

  if ( (pipeResult == VSTREAMPROC_OK)
    || (pipeResult == VSTREAMPROC_PENDING) )
  {
    /* #20 Get operation response from pipe, if available. */
    if (vSwUpdM_StreamData.PipeStarted == TRUE)
    {
      if (vSwUpdM_Pipe_HasInternalExitPoint(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputOperation) == TRUE)
      {
        vSwUpdM_ProcNodeOperationType procOperation;

        if (vSwUpdM_Pipe_ReadProcessOperation(vSwUpdMConf_vSwUpdMDataProcess_StreamData, vSwUpdMConf_vSwUpdMDataOutputType_OutputOperation, &procOperation) == E_OK)
        {
          if (procOperation == VSWUPDM_PROC_NODE_OPERATION_START)
          {
            /* #30 If response received, signalize operation PROCESS to pipe. */
            if (vSwUpdM_Pipe_WriteProcessOperation(vSwUpdMConf_vSwUpdMDataProcess_StreamData,
              vSwUpdMConf_vSwUpdMDataInputType_InputOperation, VSWUPDM_PROC_NODE_OPERATION_PROCESS) != E_OK)
            {
              pipeResult = VSTREAMPROC_FAILED;
            }

            vSwUpdM_StreamData.PipeStarted = FALSE;
          }
        }
      }
    }
  }

  switch (pipeResult)
  {
    case VSTREAMPROC_OK:
    /* #100 If idle operation is supported */
    {
      if (vSwUpdM_StreamData.PipeStarted == TRUE)
      {
        /* Operation START is never received from pipe. */
        retVal = VSWUPDM_STREAMPROCRESULT_FAIL;
      }
      else
      {
        /* #110 Storage node attached to entry point should be empty now. */
        retVal = VSWUPDM_STREAMPROCRESULT_EMPTY;
      }
      break;
    }
    case VSTREAMPROC_INSUFFICIENT_OUTPUT:
    case VSTREAMPROC_INSUFFICIENT_INPUT:
    /* #200 If insufficient output (at exit point) or insufficient input (at entry point) is reported */
    {
      /* #210 Operation is blocked until resulting output data is consumed or additional input data is provided. */
      retVal = VSWUPDM_STREAMPROCRESULT_BLOCKED;

      break;
    }
    case VSTREAMPROC_PENDING:
    /* #300 If pending operation is reported */
    {
      vStreamProc_EntryPointInfoType streamDataEntryPointInfo;

      /* #330 Check available buffer capacity at stream data entry point. */
      pipeResult = vStreamProc_PrepareEntryPointInfo(vSwUpdM_StreamData.PipeId, vSwUpdM_StreamData.PipeEntryPointData, &streamDataEntryPointInfo);

      if (pipeResult == VSTREAMPROC_OK)
      {
        pipeResult = vStreamProc_GetEntryPointInfo(vSwUpdM_StreamData.PipeId, vStreamProcConf_vStreamProcDataType_uint8, &streamDataEntryPointInfo);
      }

      /* #340 If buffer capacity could be successfully evaluated */
      if (pipeResult == VSTREAMPROC_OK)
      {
        /* #341 If at least one free byte is available
         *   Report a partially free input buffer. */
        if (streamDataEntryPointInfo.WriteRequest.StorageInfo.AvailableLength > 0u)
        {
          retVal = VSWUPDM_STREAMPROCRESULT_PARTIALLY;
        }
        /* #342 Otherwise
         *   Report a full input buffer. */
        else
        {
          retVal = VSWUPDM_STREAMPROCRESULT_FULL;
        }
      }
      /* #350 Otherwise: Report error. */
      else
      {
        retVal = VSWUPDM_STREAMPROCRESULT_FAIL;
      }

      break;
    }
    case VSTREAMPROC_FAILED:
    default:
    /* #400 Otherwise: Processing unexpectedly finished or reported a failed operation.
     *   Report error. */
    {
      retVal = VSWUPDM_STREAMPROCRESULT_FAIL;
      break;
    }
  }

  return retVal;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_Stream_Process */

/**********************************************************************************************************************
 * vSwUpdM_Pipe_GetEntryPoint
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check available buffer capacity at stream data entry point. */
  if (vStreamProc_PrepareEntryPointInfo(PipeId, EntryPointId, EntryPointInfos) == VSTREAMPROC_OK)
  {
    /* #20 Get expected datatype. */
    if (vStreamProc_GetEntryPointInfo(PipeId, DataTypeId, EntryPointInfos) == VSTREAMPROC_OK)
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_GetEntryPoint */

/**********************************************************************************************************************
 * vSwUpdM_Pipe_RequestEntryPoint
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vSwUpdM_LengthType Length,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Prepare Entry-Point access. */
  if(vSwUpdM_Pipe_GetEntryPoint(PipeId, EntryPointId, DataTypeId, EntryPointInfos) == E_OK)
  {
    /* #20 Request a buffer of Length from vStreamProc. */
    EntryPointInfos->WriteRequest.StorageInfo.RequestLength = Length;

    if (vStreamProc_RequestEntryPointData(PipeId, EntryPointInfos->WriteRequest.StorageInfo.DataTypeInfo.Id, Length, EntryPointInfos) == VSTREAMPROC_OK)
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_RequestEntryPoint */

/**********************************************************************************************************************
 * vSwUpdM_Pipe_GetLiteralReadBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(vSwUpdM_DataReadStreamPtrType, VSWUPDM_CODE) vSwUpdM_Pipe_GetLiteralReadBuffer(vStreamProc_ExitPointInfoConstPtrType ExitPointInfo)
{
  vSwUpdM_DataReadStreamPtrType retVal;

  switch (ExitPointInfo->ReadRequest.StorageInfo.DataTypeInfo.Id)
  {
    case vStreamProcConf_vStreamProcDataType_Std_ReturnType:
    {
      retVal = (vSwUpdM_DataReadStreamPtrType) vStreamProc_GetTypedReadRequestBuffer_Std_ReturnType(&ExitPointInfo->ReadRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint8:
    {
      retVal = (vSwUpdM_DataReadStreamPtrType) vStreamProc_GetTypedReadRequestBuffer_uint8(&ExitPointInfo->ReadRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint16:
    {
      /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      retVal = (vSwUpdM_DataReadStreamPtrType) vStreamProc_GetTypedReadRequestBuffer_uint16(&ExitPointInfo->ReadRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint32:
    {
      /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      retVal = (vSwUpdM_DataReadStreamPtrType) vStreamProc_GetTypedReadRequestBuffer_uint32(&ExitPointInfo->ReadRequest);
      break;
    }
    default:
    {
      /* Unsupported datatype */
      retVal = NULL_PTR;
      break;
    }
  }
   return retVal;
} /* vSwUpdM_Pipe_GetLiteralReadBuffer */

/**********************************************************************************************************************
 * vSwUpdM_Pipe_GetLiteralWriteBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(vSwUpdM_DataStreamPtrType, VSWUPDM_CODE) vSwUpdM_Pipe_GetLiteralWriteBuffer(vStreamProc_EntryPointInfoConstPtrType EntryPointInfo)
{
  vSwUpdM_DataStreamPtrType retVal;

  switch (EntryPointInfo->WriteRequest.StorageInfo.DataTypeInfo.Id)
  {
    case vStreamProcConf_vStreamProcDataType_Std_ReturnType:
    {
      retVal = (vSwUpdM_DataStreamPtrType) vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&EntryPointInfo->WriteRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint8:
    {
      retVal = (vSwUpdM_DataStreamPtrType) vStreamProc_GetTypedWriteRequestBuffer_uint8(&EntryPointInfo->WriteRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint16:
    {
      /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      retVal = (vSwUpdM_DataStreamPtrType) vStreamProc_GetTypedWriteRequestBuffer_uint16(&EntryPointInfo->WriteRequest);
      break;
    }
    case vStreamProcConf_vStreamProcDataType_uint32:
    {
      /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      retVal = (vSwUpdM_DataStreamPtrType) vStreamProc_GetTypedWriteRequestBuffer_uint32(&EntryPointInfo->WriteRequest);
      break;
    }
    default:
    {
      /* Unsupported datatype */
      retVal = NULL_PTR;
      break;
    }
  }
   return retVal;
} /* vSwUpdM_Pipe_GetLiteralWriteBuffer */

#if (VSWUPDM_EXTDATAINPUT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_Pipe_WriteExtInputData
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
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteExtInputData(
  vStreamProc_PipeIdType PipeId,
  vSwUpdM_ExtDataInputIterType ExtDataInput,
  vSwUpdM_ConstDataPointerType DataPtr,
  vSwUpdM_LengthType Length)
{
  Std_ReturnType retVal = E_OK;

  /* #10 If any data was provided: */
  if (Length > 0u)
  {
    vStreamProc_EntryPointInfoType dataEntryPointInfo;

    /* #20 Request a buffer of Length from StreamProc for selected input. */
    retVal = vSwUpdM_Pipe_RequestEntryPoint(PipeId, vSwUpdM_GetEntryPointIdOfExtDataInput(ExtDataInput), vStreamProcConf_vStreamProcDataType_Undefined, Length, &dataEntryPointInfo);

    /* #30 Check for appropriate type. */
    if (retVal == E_OK)
    {
      vSwUpdM_DataStreamPtrType buffer = NULL_PTR;
      switch (dataEntryPointInfo.WriteRequest.StorageInfo.DataTypeInfo.Id)
      {
        case vStreamProcConf_vStreamProcDataType_uint8:
        {
          buffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataEntryPointInfo.WriteRequest);
          break;
        }
        case vStreamProcConf_vStreamProcDataType_Std_ReturnType:
        {
          buffer = vStreamProc_GetTypedWriteRequestBuffer_Std_ReturnType(&dataEntryPointInfo.WriteRequest);
          break;
        }
        default:
        {
          /* External Inputs can only be uint8 (or Std_ReturnType) because the RemoteStreams can only handle byte data. */
          break;
        }
      }

      if(buffer != NULL_PTR)
      {
        /* #40 Copy data into buffer
         *     and acknowledge data. */

        vSwUpdM_Buffer_Copy(DataPtr, buffer, Length);

        if (vStreamProc_AcknowledgeEntryPoint(PipeId, Length, TRUE, &dataEntryPointInfo) != VSTREAMPROC_OK)
        {
          retVal = VSWUPDM_E_INV_CONFIG;
        }
      }
      else
      {
        retVal = VSWUPDM_E_INV_CONFIG;
      }
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_WriteExtInputData */
#endif

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_State_Suspend
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_State_Suspend(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Enter critical section to ensure exclusive access of state. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #100 Evaluate current processing state */
  switch (vSwUpdM_GlobalState)
  {
    case VSWUPDM_STATE_IDLE:
    case VSWUPDM_STATE_ACTIVE:
    case VSWUPDM_STATE_PENDING:
    /* #110 If idle or any operation is active or pending */
    {
      /* #111 Spawn job to wait for suspending of all pending jobs. */
      (void) vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_SUSPEND, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

      /* #112 Update processing state to indicate pending suspend. */
      if (retVal == E_OK)
      {
        vSwUpdM_GlobalState = VSWUPDM_STATE_SUSPEND_PENDING;
      }

      break;
    }
    case VSWUPDM_STATE_SUSPENDED:
    /* #120 If job processing is already suspended */
    {
      /* #121 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
      vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);

      break;
    }
    case VSWUPDM_STATE_SUSPEND_PENDING:
    /* #130 If suspending of pending job is already pending, nothing to be done. */
    {
      break;
    }
    default:
    /* #140 Otherwise: Report error because of invalid state. */
    {
      retVal = E_NOT_OK;
      break;
    }
  }

  /* #200 Leave critical section to ensure exclusive access of state. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_State_Suspend */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_State_Resume
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_State_Resume(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Enter critical section to ensure exclusive access of state. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Leave suspended state and resume normal job operation. */
  vSwUpdM_GlobalState = VSWUPDM_STATE_IDLE;

  /* #30 Spawn job to resume suspended jobs. */
  (void) vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_RESUME, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

  /* #40 Leave critical section to ensure exclusive access of state. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_State_Suspend */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Init_EntityIdsDefaults
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_EntityIdsDefaults(vSwUpdM_EntityIdsPtrType EntityIds)
{
  EntityIds->PartitionId                = VSWUPDM_INVALID_ID;
  EntityIds->PartitionIdx               = VSWUPDM_INVALID_ID;
  EntityIds->PartitionState             = VSWUPDM_PART_STATE_UNDEFINED;
  EntityIds->ModuleId                   = VSWUPDM_INVALID_ID;
  EntityIds->RegionId                   = VSWUPDM_INVALID_ID;
  EntityIds->RegionIdx                  = VSWUPDM_INVALID_ID;
  EntityIds->SegmentId.DynamicSegmentId = VSWUPDM_INVALID_ID;
  EntityIds->SegmentId.StaticSegmentId  = VSWUPDM_INVALID_ID;
  EntityIds->SegmentIdx                 = VSWUPDM_INVALID_ID;
} /* vSwUpdM_InitEntityIds */

/**************************************************************
 *  Memory Abstraction:
 *   - Partition
 **************************************************************/

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Part_IsPartitionSwappable
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
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Part_IsPartitionSwappable(
  vSwUpdM_PartitionIdType Id)
{
  Std_ReturnType retVal = FALSE;
  vSwUpdM_PartitionGroupIterType  partitionGroupId;

  /* #100 For all configured partition groups */
  for (partitionGroupId = 0u; partitionGroupId < vSwUpdM_GetConfiguredNumPartitionGroups(); partitionGroupId++)
  {
    vSwUpdM_PartitionIterType partitionCount = vSwUpdM_GetNumPartitionOfPartitionGroup(partitionGroupId);;

#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
    if (partitionCount > 3u)
    {
      partitionCount = 3u;
      vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT, VSWUPDM_E_OUT_OF_RANGE);
    }
#endif

    /* #110 If partition group contains more than one partition */
    if (partitionCount > 1u)
    {
      vSwUpdM_PartitionIterType relativePartitionIdx;
      vSwUpdM_PartitionIterType partitionIdx = vSwUpdM_GetPartitionGroupIdxOfPartitionGroup(partitionGroupId);

      /* #120 Iterate over all partitions assigned to partition group. */
      for (relativePartitionIdx = 0u; relativePartitionIdx < partitionCount; relativePartitionIdx++)
      {
        /* #130 If requested partition is contained in partition group
         *   Partition is swappable. */
        if (vSwUpdM_GetPartitionOfPartitionGroup2Partition(partitionIdx + relativePartitionIdx) == Id)
        {
          retVal = TRUE;

          break;
        }
      }
    }
  }

  return retVal;
} /* vSwUpdM_Part_IsPartitionSwappable */

/**********************************************************************************************************************
 * vSwUpdM_Part_UpdateValid
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_UpdateValid(
  vSwUpdM_PartitionIdType Id,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_ValidType Valid,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ValidType             currentValidity;
  vSwUpdM_VarPartitionsPtrType  partition;
  P2VAR(vSwUpdM_PartitionDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR)  attributes;

  /* #10 Enter critical section to ensure exclusive access of partition states. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 If attributes of partition are already marked dirty, use pending attribute values.
   * Otherwise: Use original attribute values. */
  partition   = vSwUpdM_GetAddrVarPartitions(Id);
  attributes  = &partition->PendingAttributesOfVarPartitions;

  if (partition->AttributesDirty == FALSE)
  {
    *attributes = partition->DynamicAttributesOfVarPartitions;
  }

  currentValidity = attributes->IsValid;

  /* #30 Leave critical section ensuring exclusive access of partition states. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  /* #40 If given validity doesn't match the current partition validity */
  if (currentValidity != Valid)
  {
    /* #100 Enter critical section to ensure exclusive access of partition states. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    if (partition->AffectedState == VSWUPDM_PART_STATE_UNDEFINED)
    {
      partition->AffectedState = State;
    }
    else
    {
      if (partition->AffectedState != State)
      {
        retVal = E_NOT_OK;
      }
    }

    if (retVal == E_OK)
    {
      /* #110 Update partition validity in attributes with given value.
       * Mark attributes of individual partition as dirty and remember that at least one partition must be persisted. */
      attributes->IsValid = Valid;
      partition->AttributesDirty = TRUE;

      vSwUpdM_PartitionAttributesDirty = TRUE;

      /* #200 When requested to be validated, partition was successfully updated.
       *   Update revision accordingly. */
      if (Valid == VSWUPDM_VALIDITY_VALID)
      {
        vSwUpdM_PartitionRevisionType currentRevision = 0u;

        /* #210 If partition is swappable */
        if (partition->SwappableOfVarPartitions == TRUE)
        {
          /* #220 If partition is the backup target
           *   Take over revision of active partition. */
          if (vSwUpdM_Part_IsPartitionStateSet(attributes->State, VSWUPDM_PART_STATE_BACKUP_TARGET) == TRUE)
          {
            vSwUpdM_PartitionIdType activePartitionId;

            if (vSwUpdM_Part_GetIdByState(&activePartitionId, VSWUPDM_PART_STATE_ACTIVE) == E_OK)
            {
              currentRevision = vSwUpdM_GetVarPartitions(activePartitionId).DynamicAttributesOfVarPartitions.Revision;
            }
            else
            {
              retVal = E_NOT_OK;
            }
          }
          /* #230 Otherwise */
          else
          {
            vSwUpdM_PartitionGroupIterType  partitionGroupId;

            /* #240 For all partition groups */
            for (partitionGroupId = 0u; partitionGroupId < vSwUpdM_GetConfiguredNumPartitionGroups(); partitionGroupId++)
            {
              vSwUpdM_NumPartitionOfPartitionGroupType  partitionCount;
              vSwUpdM_PartitionIterType                 partitionIdx;
              vSwUpdM_PartitionIterType                 relativePartitionIdx;

              partitionCount  = vSwUpdM_GetNumPartitionOfPartitionGroup(partitionGroupId);
              partitionIdx    = vSwUpdM_GetPartitionGroupIdxOfPartitionGroup(partitionGroupId);

              /* #250 If partition is part of partition group */
              for (relativePartitionIdx = 0u; relativePartitionIdx < partitionCount; relativePartitionIdx++)
              {
                if (vSwUpdM_GetPartitionOfPartitionGroup2Partition(partitionIdx + relativePartitionIdx) == Id)
                {
                  break;
                }
              }

              if (relativePartitionIdx < partitionCount)
              {
                /* #260 Iterate over all members of partition group and find highest revision. */
                for (relativePartitionIdx = 0u; relativePartitionIdx < partitionCount; relativePartitionIdx++)
                {
                  vSwUpdM_PartitionRevisionType partitionRevision =
                    vSwUpdM_GetVarPartitions(vSwUpdM_GetPartitionOfPartitionGroup2Partition(partitionIdx + relativePartitionIdx)).DynamicAttributesOfVarPartitions.Revision;

                  if ( (partitionRevision != VSWUPDM_INVALID_REVISION)
                    && (partitionRevision > currentRevision) )
                  {
                    currentRevision = partitionRevision;
                  }
                }
              }
            }

            /* #270 Increment revision by one. */
            currentRevision++;
          }
        }
        /* #280 Otherwise: Use existing revision of partition and increment by one. */
        else
        {
          if (attributes->Revision != VSWUPDM_INVALID_REVISION)
          {
            currentRevision = attributes->Revision + 1u;
          }
        }

        /* #290 Update revision in attributes. */
        attributes->Revision = currentRevision;
      }
      /* #300 Otherwise, if partition shall be invalidated */
      else
      {
        /* #310 If partition is the inactive partition, a new update is prepared. */
        if (vSwUpdM_Part_IsPartitionStateSet(attributes->State, VSWUPDM_PART_STATE_INACTIVE) == TRUE)
        {
          /* #320 Existing backup source no longer applicable.
           *   Clear "backup source" from partition state. */
          vSwUpdM_PartitionIdType backupPartitionId;

          if (vSwUpdM_Part_GetIdByState(&backupPartitionId, VSWUPDM_PART_STATE_BACKUP_SOURCE) == E_OK)
          {
            retVal = vSwUpdM_Part_UpdateState(backupPartitionId, VSWUPDM_PART_STATE_BACKUP_SOURCE, (vSwUpdM_GetVarPartitions(backupPartitionId).DynamicAttributesOfVarPartitions.State ^ VSWUPDM_PART_STATE_BACKUP_SOURCE));
          }
        }
      }
    }

    /* #400 If result is positive so far */
    if (retVal == E_OK)
    {
      vSwUpdM_JobPtrType  spawnedJob;
      vSwUpdM_JobTypeType jobType;

      /* #410 Spawn job to handle persisting of updated validity of partition.
       *   Job type is dependent on whether partition shall be validated or invalidated. */
      if (Valid == VSWUPDM_VALIDITY_VALID)
      {
        jobType = VSWUPDM_JOB_TYPE_VALIDATE_PARTITION_LOCAL;
      }
      else
      {
        jobType = VSWUPDM_JOB_TYPE_INVALIDATE_PARTITION_LOCAL;
      }

      spawnedJob = vSwUpdM_Job_Spawn(&retVal, jobType, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ParentJob, Source);

      /* #420 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);
        spawnedJob->EntityIds.PartitionId = Id;
        spawnedJob->EntityIds.PartitionState = State;
      }
    }

    /* #500 Leave critical section ensuring exclusive access of partition states. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Part_UpdateValid */

/**********************************************************************************************************************
 * vSwUpdM_Part_UpdateState
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_UpdateState(
  vSwUpdM_PartitionIdType Id,
  vSwUpdM_PartitionStateType AffectedState,
  vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarPartitionsPtrType  partition;
  P2VAR(vSwUpdM_PartitionDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR)  attributes;

  /* #10 Enter critical section to ensure exclusive access of partition states. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 If attributes of partition are already marked dirty, use pending attribute values.
   * Otherwise: Use original attribute values. */
  partition   = vSwUpdM_GetAddrVarPartitions(Id);
  attributes  = &partition->PendingAttributesOfVarPartitions;

  if (partition->AttributesDirty == FALSE)
  {
    *attributes = partition->DynamicAttributesOfVarPartitions;
  }

  /* #30 If given state doesn't match the current value of the partition */
  if (attributes->State != State)
  {
    if (partition->AffectedState == VSWUPDM_PART_STATE_UNDEFINED)
    {
      partition->AffectedState = AffectedState;
    }
    else
    {
      if (partition->AffectedState != AffectedState)
      {
        retVal = E_NOT_OK;
      }
    }

    if (retVal == E_OK)
    {
      /* #31 Update partition state in attributes with given value.
       * Mark attributes of individual partition as dirty and remember that at least one partition must be persisted. */
      attributes->State                 = State;
      partition->AttributesDirty        = TRUE;

      vSwUpdM_PartitionAttributesDirty  = TRUE;
    }
  }

  /* #40 Leave critical section ensuring exclusive access of partition states. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_Part_UpdateState */

/**********************************************************************************************************************
 * vSwUpdM_Part_PersistState
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_PersistState(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 If at least the attributes of one partition are marked dirty */
  if (vSwUpdM_PartitionAttributesDirty == TRUE)
  {
    vSwUpdM_JobPtrType spawnedJob;

    /* #20 Enter critical section to ensure exclusive access of partition states and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #30 Spawn job to persist attributes of all partitions which are marked dirty. */
    spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PERSIST_PARTITION_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, ParentJob->Source);

    /* #40 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);

      vSwUpdM_PartitionAttributesDirty = FALSE;
    }

    /* #50 Leave critical section ensuring exclusive access of partition states and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  /* #100 Otherwise */
  else
  {
    /* #110 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
    vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, ParentJob->Source, ConfirmationService, retVal);
  }

  return retVal;
} /* vSwUpdM_Part_PersistState */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Part_GetIdByState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Part_GetIdByState(
  P2VAR(vSwUpdM_PartitionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionId,
  vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vSwUpdM_PartitionIterType partitionId;

  /* #100 Iterate over all partitions */
  for (partitionId = 0u; partitionId < vSwUpdM_EntityData.Count.PartitionCount; partitionId++)
  {
    /* #110 If state of partition matches the requested one */
    if (vSwUpdM_Part_IsPartitionStateSet(vSwUpdM_GetVarPartitions(partitionId).DynamicAttributesOfVarPartitions.State, State) == TRUE)
    {
      /* #120 Return current partition ID. */
      *PartitionId = (vSwUpdM_PartitionIdType)partitionId;
      retVal = E_OK;

      break;
    }
  }

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Part_GetIdByState */

/**************************************************************
 *  Memory Abstraction:
 *   - Module
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Module_InitRegions
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_InitRegions(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType              retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarRegionsIterType  regionIdx;
  vSwUpdM_JobPtrType          spawnedJob;

  /* #10 Set region count for given module ID. */
  vSwUpdM_EntityData.Count.RegionCount = vSwUpdM_GetNRegionsOfModule(Id);

  /* #20 For all regions assigned to module */
  for (regionIdx = 0u; regionIdx < vSwUpdM_EntityData.Count.RegionCount; regionIdx++)
  {
    vSwUpdM_RegionIterType    staticRegionId;
    vSwUpdM_VarRegionsPtrType region;

    staticRegionId = vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(Id) + regionIdx);
    region = vSwUpdM_GetAddrVarRegions(regionIdx);

    /* #30 Assign configured values to variable representation. */
    region->RegionIDOfVarRegions                              = (vSwUpdM_RegionIdType)staticRegionId;
    region->ModuleIDOfVarRegions                              = vSwUpdM_GetModuleIdxOfRegion(staticRegionId);
    region->StartAddressOfVarRegions                          = vSwUpdM_GetStartAddressOfRegion(staticRegionId);
    region->LengthOfVarRegions                                = vSwUpdM_GetLengthOfRegion(staticRegionId);
    region->EndAddressOfVarRegions                            = vSwUpdM_GetStartAddressOfRegion(staticRegionId) + ((vSwUpdM_AddressType)vSwUpdM_GetLengthOfRegion(staticRegionId) - 1u);
    region->HandleIDOfVarRegions                              = vSwUpdM_GetRegionHandleOfRegion(staticRegionId);
    /* #40 Initialize dynamic attributes and mark as non-dirty. */
    region->DynamicAttributesOfVarRegion.ProgrammingAttempts  = 0u;
    region->DynamicAttributesOfVarRegion.State                = VSWUPDM_REGION_STATE_UNDEFINED;
    region->PendingAttributesOfVarRegion                      = region->DynamicAttributesOfVarRegion;
    region->EraseAddressOfVarRegion                           = region->StartAddressOfVarRegions;
    region->EraseAddressDirty                                 = FALSE;
    region->AttributesDirty                                   = FALSE;

    /* #50 Reserve complete sectors for region, by aligning reserved start/end addresses to sectors boundaries. */
    region->ReservedStartAddressOfVarRegions  = region->StartAddressOfVarRegions;
    region->ReservedEndAddressOfVarRegions    = region->EndAddressOfVarRegions;
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(staticRegionId)))
#endif
    {
      (void)vSwUpdM_Range_AlignAddress(&region->ReservedStartAddressOfVarRegions, ParentJob->EntityIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT, VSWUPDM_ALIGN_GRANULARITY_SECTOR);
      (void)vSwUpdM_Range_AlignAddress(&region->ReservedEndAddressOfVarRegions, ParentJob->EntityIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_BACK, VSWUPDM_ALIGN_GRANULARITY_SECTOR);
    }
  }

  /* #100 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #110 Spawn job to restore persisted dynamic attributes. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_INIT_REGIONS, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, ParentJob->Source);

  /* #120 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    spawnedJob->EntityIds = ParentJob->EntityIds;
  }

  /* #130 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_Module_InitRegions */

/**********************************************************************************************************************
 * vSwUpdM_Module_InitSegments
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_InitSegments(
  vSwUpdM_RestoreSegmentsType RestoreSegments,
  boolean InitStaticSegments,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType              retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarRegionsIterType  regionIdx;
  vSwUpdM_VarRegionsPtrType   region; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
  vSwUpdM_VarSegmentsPtrType  segment;
  vSwUpdM_SegmentInfoType     segmentInfo;
#if (VSWUPDM_SEGMENT == STD_ON)
  vSwUpdM_SegmentIterType     staticSegmentId;
#endif
  vSwUpdM_QueueHandleType     queueHandle;

  VSWUPDM_DUMMY_STATEMENT(InitStaticSegments); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Reset segment related entity data to default values. */
  vSwUpdM_EntityData.Count.ExternalSegmentCount         = 0u;
  /* HINT: Function is used by ClearSegmentsOfModule service to reset the segment count.
   *  Thus the "dirty" flag is set here, to trigger the persisting of the updated value.
   *  When existing segments are restored though, the flag is reset (in vSwUpdM_JobHandler_InitSegments). */
  vSwUpdM_EntityData.Count.ExternalSegmentCountDirty    = TRUE;
  vSwUpdM_EntityData.Count.InternalSegmentCount         = 1u;
  vSwUpdM_EntityData.Count.WriteSegmentCount            = vSwUpdM_EntityData.Count.RegionCount;
  vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId = VSWUPDM_INVALID_ID;
  vSwUpdM_EntityData.OpenIds.SegmentId.StaticSegmentId  = VSWUPDM_INVALID_ID;
  vSwUpdM_EntityData.OpenObjects.Segment                = NULL_PTR;

  /* #20 Initialize queues for external/internal representation of segments. */
  vSwUpdM_QueueInit(&vSwUpdM_ExternalSegmentsQueue, vSwUpdM_VarExternalSegmentsQueue, vSwUpdM_GetSizeOfVarExternalSegmentsQueue(), VSWUPDM_QUEUE_PRIO_ORDER_ASC, VSWUPDM_QUEUE_ENTITY_HANDLE_NONE, 0u);
  vSwUpdM_QueueInit(&vSwUpdM_InternalSegmentsQueue, vSwUpdM_VarInternalSegmentsQueue, vSwUpdM_GetSizeOfVarInternalSegmentsQueue(), VSWUPDM_QUEUE_PRIO_ORDER_ASC, 0u, 1u);

  /* #30 Setup initial internal gap segment to cover the complete address space. */
  queueHandle = vSwUpdM_QueuePrioInsert(&vSwUpdM_InternalSegmentsQueue, 0u);

  segment = vSwUpdM_GetAddrVarSegments(vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle));

  segment->DynamicAttributesOfVarSegment.StartAddress       = 0u;
  segment->DynamicAttributesOfVarSegment.InitialLength      = 0u;
  segment->DynamicAttributesOfVarSegment.LengthHandling     = VSWUPDM_LENGTH_HANDLING_DYNAMIC;
  segment->DynamicAttributesOfVarSegment.State              = VSWUPDM_SEGMENT_STATE_UNDEFINED;
  segment->DynamicAttributesOfVarSegment.ResumeOffset       = 0u;
  segment->RealLength                                       = 0u;
  segment->WriteAddressOfVarSegments                        = 0u;
  segment->EndAddressOfVarSegments                          = VSWUPDM_MAX_ADDRESS;
  segment->InitialEndAddressOfVarSegments                   = VSWUPDM_MAX_ADDRESS;
  segment->ReservedStartAddressOfVarSegments                = 0u;
  segment->ReservedEndAddressOfVarSegments                  = VSWUPDM_MAX_ADDRESS;
  segment->TypeOfVarSegments                                = VSWUPDM_NO_SEGMENTTYPEOFSEGMENT;
  segment->ClassOfVarSegments                               = VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP;
  segment->RegionIdxOfVarSegments                           = VSWUPDM_INVALID_ID;
  segment->WriteSegmentIdx                                  = VSWUPDM_INVALID_ID;
  segment->ExternalSegmentIdx                               = VSWUPDM_INVALID_ID;
  segment->AttributesDirty                                  = FALSE;
  segment->WriteAddressDirty                                = FALSE;
  segment->RemoteDirty                                      = FALSE;
  segment->SegmentClean                                     = TRUE;

  /* #100 For all regions of open module */
  for (regionIdx = 0u; regionIdx < vSwUpdM_EntityData.Count.RegionCount; regionIdx++)
  {
    vSwUpdM_SegmentStateType segmentState;
    vSwUpdM_AlignGranularityType alignGranularity = VSWUPDM_ALIGN_GRANULARITY_SECTOR;

    region = vSwUpdM_GetAddrVarRegions(regionIdx);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(region->RegionIDOfVarRegions)))
    {
      alignGranularity = VSWUPDM_ALIGN_GRANULARITY_NONE;
    }
#endif

    /* #110 Set default segment state based on region state */
    switch (region->DynamicAttributesOfVarRegion.State)
    {
      case VSWUPDM_REGION_STATE_ERASED:
      /* #111 Set to "erased" when region is "erased". */
      {
        segmentState = VSWUPDM_SEGMENT_STATE_ERASED;
        break;
      }
      case VSWUPDM_REGION_STATE_CLEAN:
      /* #112 Set to "pending" when region is "clean". */
      {
        segmentState = VSWUPDM_SEGMENT_STATE_PENDING;
        break;
      }
      case VSWUPDM_REGION_STATE_FINALIZED:
      /* #113 Set to "finalized" when region is "finalized". */
      {
        segmentState = VSWUPDM_SEGMENT_STATE_FINALIZED;
        break;
      }
      case VSWUPDM_REGION_STATE_UNDEFINED:
      case VSWUPDM_REGION_STATE_ERASE_PENDING:
      case VSWUPDM_REGION_STATE_DIRTY:
      default:
      /* #114 Otherwise: Set to "undefined". */
      {
        segmentState = VSWUPDM_SEGMENT_STATE_UNDEFINED;
        break;
      }
    }

    /* #120 Add an internal free segment covering the configured area of the region. */
    (void)vSwUpdM_InitSegmentInfo(&segmentInfo);

    segmentInfo.StartAddress    = region->StartAddressOfVarRegions;
    segmentInfo.Length          = region->LengthOfVarRegions;
    segmentInfo.LengthHandling  = VSWUPDM_LENGTH_HANDLING_DYNAMIC;
    segmentInfo.Type            = VSWUPDM_NO_SEGMENTTYPEOFSEGMENT;
    segmentInfo.State           = segmentState;

    retVal  =  vSwUpdM_Segment_AddSegment(&segmentInfo, VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE, alignGranularity, FALSE);

    if (retVal == E_OK)
    {
      vSwUpdM_VarSegmentsPtrType localSegment = vSwUpdM_GetAddrVarSegments(segmentInfo.Id.DynamicSegmentId);

      /* #130 Assign relative region index inside of module to added segment. */
      localSegment->RegionIdxOfVarSegments     = (vSwUpdM_RegionIdxType)regionIdx;
      localSegment->WriteSegmentIdx            = (vSwUpdM_RegionIdxType)regionIdx;
    }
    else
    {
      break;
    }
  }

#if (VSWUPDM_SEGMENT == STD_ON)
  /* #200 If result if positive so far and static segment shall be initialized */
  if ( (retVal == E_OK)
    && (InitStaticSegments == TRUE) )
  {
    /* #210 For all regions of open module */
    for (regionIdx = 0u; regionIdx < vSwUpdM_EntityData.Count.RegionCount; regionIdx++)
    {
      vSwUpdM_RegionIterType maxRegionId;
      vSwUpdM_RegionIterType staticRegionId;
      vSwUpdM_AlignGranularityType alignGranularity = VSWUPDM_ALIGN_GRANULARITY_PAGE;

      region          = vSwUpdM_GetAddrVarRegions(regionIdx);
      staticRegionId  = (vSwUpdM_RegionIterType)region->RegionIDOfVarRegions;
      maxRegionId     = (vSwUpdM_SegmentIterType)vSwUpdM_GetSegmentIdxOfRegion(staticRegionId) + (vSwUpdM_SegmentIterType)vSwUpdM_GetNumSegmentsOfRegion(staticRegionId);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(region->RegionIDOfVarRegions)))
      {
        alignGranularity = VSWUPDM_ALIGN_GRANULARITY_NONE;
      }
#endif

      /* #220 Iterate over all configured static segments assigned to region. */
      for (staticSegmentId = vSwUpdM_GetSegmentIdxOfRegion(staticRegionId); staticSegmentId < maxRegionId; staticSegmentId++)
      {
        /* #230 Add an internal reserved segment covering the configured area of the static segment. */
        (void)vSwUpdM_InitSegmentInfo(&segmentInfo);

        segmentInfo.Id.StaticSegmentId  = (vSwUpdM_SegmentIdValueType)staticSegmentId;
        segmentInfo.StartAddress        = vSwUpdM_GetStartAddressOfSegment(staticSegmentId);
        segmentInfo.Length              = vSwUpdM_GetLengthOfSegment(staticSegmentId);
        segmentInfo.LengthHandling      = VSWUPDM_LENGTH_HANDLING_FIXED;

        /* #240 Assign segment type if configured. */
# if (VSWUPDM_SEGMENTTYPEUSEDOFSEGMENT == STD_ON)
        if (vSwUpdM_IsSegmentTypeUsedOfSegment(staticSegmentId))
        {
          segmentInfo.Type = vSwUpdM_GetSegmentTypeOfSegment(staticSegmentId);
        }
        else
# endif
        {
          segmentInfo.Type = VSWUPDM_NO_SEGMENTTYPEOFSEGMENT;
        }

        retVal = vSwUpdM_Segment_AddSegment(&segmentInfo, VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED, alignGranularity, FALSE);

        if (retVal != E_OK)
        {
          break;
        }
      }

      if (retVal != E_OK)
      {
        break;
      }
    }
  }
#endif

  /* #300 If result if positive so far */
  if (retVal == E_OK)
  {
    P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) entityIds;

    if (ParentJob != NULL_PTR)
    {
      entityIds = &ParentJob->EntityIds;
    }
    else
    {
      entityIds = &vSwUpdM_EntityData.OpenIds;
    }

    /* #310 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #320 If persisted dynamic segment shall be restored */
    if (RestoreSegments != VSWUPDM_RESTORE_SEGMENTS_NONE)
    {
      vSwUpdM_JobPtrType spawnedJob;
      vSwUpdM_JobOperationType operation;

      /* #330 Check whether only the dynamic segment, which was added first shall be restored. */
      switch (RestoreSegments)
      {
        case VSWUPDM_RESTORE_SEGMENTS_FIRST:
        {
          operation = VSWUPDM_JOB_OPERATION_INIT_SEGMENTS_FIRST_SEGMENT;
          break;
        }
        case VSWUPDM_RESTORE_SEGMENTS_KEEP_STATE:
        {
          operation = VSWUPDM_JOB_OPERATION_INIT_SEGMENTS_KEEP_STATE;
          break;
        }
        default:
        {
          operation = VSWUPDM_JOB_OPERATION_DEFAULT;
          break;
        }
      }

      /* #340 Spawn job to restore persisted dynamic segments. */
      spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_INIT_SEGMENTS, operation, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

      /* #350 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        spawnedJob->EntityIds = *entityIds;
      }
    }
    /* #360 Otherwise: Clear any persisted segment information.
     *  Trigger persisting of dynamic segment count (equals zero) and write addresses of free segments. */
    else
    {
      retVal = vSwUpdM_Segment_PersistState(entityIds, ConfirmationService, TRUE, ParentJob, Source);
    }

    /* #370 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_Module_InitSegments */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Module_OpenModule
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_OpenModule(
  vSwUpdM_ModuleIdType Id,
  boolean RestoreSegments,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ------------------------------------------------- */
  /* #10 If requested module is already open */
  if (vSwUpdM_EntityData.OpenIds.ModuleId == Id)
  {
    /* #20 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
    retVal = E_OK;
    vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);
  }
  /* #100 Otherwise, if no module is opened yet */
  else if (vSwUpdM_EntityData.OpenIds.ModuleId == VSWUPDM_INVALID_ID)
  {
    /* #110 If module ID is valid */
    if (vSwUpdM_Module_IsModuleIdValid(Id) == TRUE)
    {
      vSwUpdM_JobOperationType operation = VSWUPDM_JOB_OPERATION_DEFAULT;
      vSwUpdM_JobPtrType spawnedJob;

      /* #120 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #130 Check whether dynamic segments of module shall be restored. */
      if (RestoreSegments == TRUE)
      {
        operation = VSWUPDM_JOB_OPERATION_OPEN_MODULE_RESTORE_SEGMENTS;
      }

      /* #140 Spawn job to restore persisted module attributes. */
      spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_OPEN_MODULE_LOCAL, operation, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

      /* #150 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        spawnedJob->EntityIds = vSwUpdM_EntityData.OpenIds;
        spawnedJob->EntityIds.ModuleId = Id;
      }

      /* #160 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }
  else
  /* #200 Otherwise: Not allowed, report error. */
  {
  }

  return retVal;
} /* vSwUpdM_Module_OpenModule */

/**********************************************************************************************************************
 * vSwUpdM_Module_CloseModule
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_CloseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ------------------------------------------------- */
  /* #10 If requested module is open */
  if (vSwUpdM_EntityData.OpenIds.ModuleId == Id)
  {
    vSwUpdM_JobPtrType spawnedJob;

    /* #20 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #30 Spawn job to persist module attributes and close module. */
    spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_CLOSE_MODULE_LOCAL, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

    /* #40 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      spawnedJob->EntityIds = vSwUpdM_EntityData.OpenIds;
    }

    /* Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  /* #100 Otherwise: Not allowed, report error. */

  return retVal;
} /* vSwUpdM_Module_CloseModule */

/**********************************************************************************************************************
 * vSwUpdM_Module_PreparePendingAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PreparePendingAttributes(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_PartitionIdType PartitionId)
{
  Std_ReturnType            retVal = E_OK;

  /* #10 If pending attributes aren't marked as dirty yet */
  if (vSwUpdM_ModulePendingAttributes.AttributesDirty == FALSE)
  {
    /* #20 Copy dynamic attributes of module instance into pending attributes. */
    retVal= vSwUpdM_Module_GetAttributes(ModuleId, PartitionId, &vSwUpdM_ModulePendingAttributes.Attributes);
  }

  return retVal;
} /* vSwUpdM_Module_PreparePendingAttributes */

/**********************************************************************************************************************
 * vSwUpdM_Module_UpdateValid
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateValid(
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ValidType Valid,
  vSwUpdM_RevisionUpdateType RevisionUpdate,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                      retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_PartitionIdType             partitionId;

  if(vSwUpdM_Part_GetIdByState(&partitionId, PartitionState) == E_OK)
  {
    /* #10 Prepare the pending attributes of the module instance. */
    if (vSwUpdM_Module_PreparePendingAttributes(ModuleId, partitionId) == E_OK)
    {
      vSwUpdM_ModuleRevisionType  currentRevision   = 0u;
      vSwUpdM_VarModulesPtrType   module = vSwUpdM_GetAddrVarModules(ModuleId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

      /* #20 If module is swappable */
      if (module->SwappableOfVarModules == TRUE)
      {
        vSwUpdM_PartitionIdType activePartitionId;

        /* #21 Use revision of module instance in active partition. */
        if (vSwUpdM_Part_GetIdByState(&activePartitionId, VSWUPDM_PART_STATE_ACTIVE) == E_OK)
        {
          vSwUpdM_PartitionIdxType relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

          if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, ModuleId, activePartitionId) == E_OK)
          {
            currentRevision = module->DynamicAttributesOfVarModules[relativePartitionIdx].Revision;
            retVal          = E_OK;
          }
        }
      }
      /* #30 Otherwise: */
      else
      {
        /* #31 Use existing revision of from module attributes, unless it is invalid. */
        if (vSwUpdM_ModulePendingAttributes.Attributes.Revision != VSWUPDM_INVALID_REVISION)
        {
          currentRevision = vSwUpdM_ModulePendingAttributes.Attributes.Revision;
        }

        retVal = E_OK;
      }

      /* #100 If result if positive so far */
      if (retVal == E_OK)
      {
        /* #110 If given validity doesn't match the current module instance validity */
        if (vSwUpdM_ModulePendingAttributes.Attributes.IsValid != Valid)
        {
          /* #120 If module shall be invalidated */
          if (Valid == VSWUPDM_VALIDITY_INVALID)
          {
            /* #121 Trigger invalidation of given partition. */
            retVal = vSwUpdM_Part_UpdateValid(partitionId, PartitionState, VSWUPDM_VALIDITY_INVALID, ParentJob, Source);

            /* #122 Set state of module instance to "undefined". */
            vSwUpdM_ModulePendingAttributes.Attributes.State = VSWUPDM_MODULE_STATE_UNDEFINED;
          }
          /* #130 Otherwise, if module shall be validated */
          else
          {
            /* #131 If module was not successfully verified before
             *   Precondition not fulfilled, report error. */
            if (vSwUpdM_ModulePendingAttributes.Attributes.State != VSWUPDM_MODULE_STATE_VERIFIED)
            {
              retVal = E_NOT_OK;
            }
          }

          /* #199 If result is positive so far: */
          if (retVal == E_OK)
          {
            vSwUpdM_JobTypeType jobType;
            vSwUpdM_JobPtrType  spawnedJob;

            /* #200 Update revision based on given update method. */
            switch (RevisionUpdate)
            {
              case VSWUPDM_REVISION_UPDATE_TAKE_OVER:
              /* #201 Take over unaltered value, when requested. */
              {
                vSwUpdM_ModulePendingAttributes.Attributes.Revision = currentRevision;

                break;
              }
              case VSWUPDM_REVISION_UPDATE_INCREMENT:
              /* #202 Increment value by one, when requested. */
              {
                vSwUpdM_ModulePendingAttributes.Attributes.Revision = currentRevision + 1u;

                break;
              }
              default:
              /* #203 Otherwise: Leave original value unchanged. */
              {
                break;
              }
            }

            /* #210 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #220 Spawn job to handle persisting of updated validity and state of module instance.
             *    Job type is dependent on whether module shall be validated or invalidated. */
            if (Valid == VSWUPDM_VALIDITY_VALID)
            {
              jobType = VSWUPDM_JOB_TYPE_VALIDATE_MODULE_INTERNAL;
            }
            else
            {
              jobType = VSWUPDM_JOB_TYPE_INVALIDATE_MODULE_INTERNAL;
            }

            spawnedJob = vSwUpdM_Job_Spawn(&retVal, jobType, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

            /* #230 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
            if (retVal == E_OK)
            {
              vSwUpdM_ModulePendingAttributes.Attributes.IsValid  = Valid;
              vSwUpdM_ModulePendingAttributes.RevisionUpdate      = RevisionUpdate;
              vSwUpdM_ModulePendingAttributes.AttributesDirty     = TRUE;

              vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);
              spawnedJob->EntityIds.PartitionId = partitionId;
              spawnedJob->EntityIds.PartitionState = PartitionState;
              spawnedJob->EntityIds.ModuleId    = ModuleId;
            }

            /* #240 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
          }
        }
        /* #300 Otherwise */
        else
        {
          /* #310 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
          vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);
        }
      }
    }
  }

  /* #400 Otherwise: No instance of module in given partition.
   *   Report error. */

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6060, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */
} /* vSwUpdM_Module_UpdateValid */

/**********************************************************************************************************************
 * vSwUpdM_Module_UpdateState
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 Enter critical section to ensure exclusive access of state. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Prepare the pending attributes of the module instance. */
  retVal = vSwUpdM_Module_PreparePendingAttributes(ModuleId, PartitionId);

  /* #30 If given state doesn't match the current module instance state
   *   Update state and mark module attributes as dirty. */
  if ( (retVal == E_OK)
    && (vSwUpdM_ModulePendingAttributes.Attributes.State != State) )
  {
    vSwUpdM_ModulePendingAttributes.Attributes.State  = State;
    vSwUpdM_ModulePendingAttributes.AttributesDirty   = TRUE;
  }

  /* #40 Leave critical section ensuring exclusive access of state. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
} /* vSwUpdM_Module_UpdateState */

/**********************************************************************************************************************
 * vSwUpdM_Module_PersistStateAndConfirm
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_PersistStateAndConfirm(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 If the attributes of the module are marked dirty */
  if (vSwUpdM_ModulePendingAttributes.AttributesDirty == TRUE)
  {
    vSwUpdM_JobPtrType spawnedJob;

    /* #20 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #30 Spawn job to handle persisting of updated state of module instance. */
    spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PERSIST_MODULE_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

    /* #40 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);

      spawnedJob->EntityIds.PartitionId    = PartitionId;
      spawnedJob->EntityIds.PartitionState = PartitionState;
      spawnedJob->EntityIds.ModuleId       = ModuleId;
    }

    /* #50 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  /* #100 Otherwise */
  else
  {
    /* #110 Update result of potential parent job. */
    vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);
  }

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR  */
} /* vSwUpdM_Module_PersistStateAndConfirm */

/**********************************************************************************************************************
 * vSwUpdM_Module_UpdateProgrammingAttempts
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_UpdateProgrammingAttempts(
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId)
{
  Std_ReturnType            retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* #10 Prepare the pending attributes of the module instance. */
  retVal = vSwUpdM_Module_PreparePendingAttributes(ModuleId, PartitionId);

  if (retVal == E_OK)
  {
    /* #20 If current programming attempt counter of module instance is smaller than given value */
    if (vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts < ProgrammingAttempts)
    {
      /* #30 Set programming attempt counter in pending attributes. */
      vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts  = ProgrammingAttempts;
      /* #31 Mark pending attributes as dirty. */
      vSwUpdM_ModulePendingAttributes.AttributesDirty                 = TRUE;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_Module_EraseModule
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_EraseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_QueuePrioType Priority,
  boolean UpdateResumeInfo,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                  retVal          = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean                         updateResult    = TRUE;
  vSwUpdM_ModuleStateType         moduleState;

  /* #10 Evaluate state of module instance in given partition. */
  retVal = vSwUpdM_Module_GetStateByPartition(&moduleState, Id, ParentJob->EntityIds.PartitionId);

  if (retVal == E_OK)
  {
    /* #20 If module isn't already erased */
    if (moduleState != VSWUPDM_MODULE_STATE_ERASED)
    {
      /* #21 Check whether programming attempts are exceeded. */
      retVal = vSwUpdM_Module_CheckProgrammingAttempts(Id, ParentJob->EntityIds.PartitionId);

      if (retVal == E_OK)
      {
        vSwUpdM_JobPtrType spawnedJob;

        updateResult = FALSE;

        /* #30 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #40 Spawn job to erase module instance. */
        spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_ERASE_MODULE_LOCAL, VSWUPDM_JOB_OPERATION_DEFAULT, Priority, VSWUPDM_SID_NONE, ParentJob, Source);

        /* #50 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (retVal == E_OK)
        {
          spawnedJob->EntityIds = ParentJob->EntityIds;
          spawnedJob->EntityIds.ModuleId = Id;
          spawnedJob->UpdateResumeInfo = UpdateResumeInfo;
        }

        /* #60 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }
  }

  /* #100 Update result of potential parent job when necessary. */
  if (updateResult == TRUE)
  {
    vSwUpdM_Job_SetChildResult(ParentJob, retVal, VSWUPDM_UNDEFINED_ADDRESS);
  }

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR  */
} /* vSwUpdM_Module_EraseModule */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Module_FinalizeModule
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_FinalizeModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  vSwUpdM_ModuleStateType moduleState;
  Std_ReturnType retVal = E_NOT_OK;

  /* #100 Evaluate state of module instance in opened partition. */
  if (vSwUpdM_Module_GetStateByPartition(&moduleState, Id, vSwUpdM_EntityData.OpenIds.PartitionId) == E_OK)
  {
    /* #110 If module is already finalized, nothing to be done. */
    if (moduleState == VSWUPDM_MODULE_STATE_FINALIZED)
    {
      retVal = E_OK;
    }
    /* #200 Otherwise */
    else
    {
      vSwUpdM_JobPtrType spawnedJob;

      /* #210 Initialize resume information for FinalizeModule service. */
      vSwUpdM_ResumeInfo_InitModuleService(Id, VSWUPDM_SID_FINALIZE_MODULE);

      /* #220 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #230 Spawn job to finalize module */
      spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_FINALIZE_MODULE_LOCAL, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ParentJob, Source);

      /* #240 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        /* #241 Pass open entity IDs to job  to job, overwriting module ID with requested one. */
        spawnedJob->EntityIds           = vSwUpdM_EntityData.OpenIds;
        spawnedJob->EntityIds.ModuleId  = Id;
      }
      /* #250 If spawning of job failed
       *   Reset resume information */
      else
      {
        vSwUpdM_ResumeInfo_ResetState();
      }

      /* #260 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_Module_FinalizeModule */

/**********************************************************************************************************************
 * vSwUpdM_Module_SyncModule
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Module_SyncModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_ServiceIdType ConfirmationService,
  boolean UpdateResumeInfo,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarModulesPtrType module = vSwUpdM_GetAddrVarModules(Id); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  /* #10 If module is swappable */
  if (module->SwappableOfVarModules == TRUE)
  {
    /* #20 Use opened partition as target. */
    vSwUpdM_PartitionIdType   targetPartitionId   = vSwUpdM_EntityData.OpenIds.PartitionId;
    vSwUpdM_PartitionIdType   sourcePartitionId;

    /* #30 Use active partition as source. */
    retVal = vSwUpdM_Part_GetIdByState(&sourcePartitionId, VSWUPDM_PART_STATE_ACTIVE);

    /* #40 If source and target aren't the same */
    if ( (retVal == E_OK)
      && (sourcePartitionId != targetPartitionId) )
    {
      vSwUpdM_PartitionIdxType  sourceIndex = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */
      vSwUpdM_PartitionIdxType  targetIndex = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

      /* #50 Evaluate attributes of source and target instances of module. */
      if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&sourceIndex, Id, sourcePartitionId) != E_OK)
      {
        retVal = E_NOT_OK;
      }

      if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&targetIndex, Id, targetPartitionId) != E_OK)
      {
        retVal = E_NOT_OK;
      }

      if (retVal == E_OK)
      {
        vSwUpdM_ModuleDynamicAttributesType sourceAttributes;
        vSwUpdM_ModuleDynamicAttributesType targetAttributes;

        sourceAttributes = module->DynamicAttributesOfVarModules[sourceIndex];
        targetAttributes = module->DynamicAttributesOfVarModules[targetIndex];

        /* #60 Synchronization only applicable if source instance is valid
         *   and either target is invalid or is an older revision as the source. */
        if ( (sourceAttributes.IsValid == TRUE)
          && ( (targetAttributes.IsValid == FALSE)
            || (targetAttributes.Revision < sourceAttributes.Revision) ) )
        {
          vSwUpdM_JobPtrType spawnedJob;

          /* #70 Enter critical section to ensure exclusive access of state and job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          /* #80 Spawn job to synchronize module instance. */
          spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_SYNC_MODULE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

          /* #90 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
          if (retVal == E_OK)
          {
            spawnedJob->EntityIds           = vSwUpdM_EntityData.OpenIds;
            spawnedJob->EntityIds.ModuleId  = Id;
            spawnedJob->UpdateResumeInfo    = UpdateResumeInfo;
          }

          /* #100 Leave critical section ensuring exclusive access of state and job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();

        }
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_Module_SyncModule */

/**********************************************************************************************************************
 *  vSwUpdM_Module_ProcessModule()
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
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Module_ProcessModule(
  vSwUpdM_JobPtrType ParentJob,
  boolean UpdateResumeInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    result          = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean           updateResult    = TRUE;

  /* ----- Implementation ------------------------------------------------- */

  /* #110 Determine the module state-specific processing operation mode. */
  vSwUpdM_ModuleIdType          moduleId      = ParentJob->EntityIds.ModuleId;
  vSwUpdM_ProcNodeOperationType procOperation = vSwUpdM_Pipe_EvalProcessOperation(vSwUpdM_ProcessData.ProcessConfig,
    ParentJob->EntityIds.PartitionId, moduleId);

  switch (procOperation)
  {
    case VSWUPDM_PROC_NODE_OPERATION_START:
    case VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART:
    case VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART:
    /* #120 If module is in a valid state for processing */
    {
# if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
      vSwUpdM_NodeGroupIterType groupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId);

      /* #130 If local node doesn't own the processed entity */
      if (vSwUpdM_GridNode_IsNodeContainedInNodeGroup(groupIndex, vSwUpdM_GetLocalNode()) == FALSE)
      {
        vSwUpdM_ProcessCountType i;

        result = E_OK;

        /* #131 Link provided output buffers to remote stream for results of verification. */
        for (i = 0u; i < vSwUpdM_ProcessUserData.OutputCount; i++)
        {
          vSwUpdM_RemoteStreamHandleType handle;
          vSwUpdM_NodeIterType sourceIndex;

          /* Even if a owner group is used here - this need to be a group of size 1 (one target). A stream can have only one source (here: the owner of a module). */
          sourceIndex = vSwUpdM_GetNodeGroup2NodeInd(vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(groupIndex));
          handle = vSwUpdM_ProcessUserData.InputCount + i;

          if (vSwUpdM_ProcessUserData.OutputData[i].BufferSize > 0u)
          {
            result = vSwUpdM_RemoteStreamPrepareRx(handle, vSwUpdM_ProcessUserData.OutputData[i].DataPtr, vSwUpdM_ProcessUserData.OutputData[i].BufferSize, sourceIndex);
          }
        }
      }
      else
# endif
      {
        vSwUpdM_JobPtrType spawnedJob;

        updateResult = FALSE;

        /* #140 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #150 Spawn job to access pipe in a common way. */
        spawnedJob = vSwUpdM_Job_Spawn(&result, VSWUPDM_JOB_TYPE_PROCESS_ENTITY, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ParentJob, ParentJob->Source);

        /* #160 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (result == E_OK)
        {
          /* #161 Pass entity IDs and resume info update flag. */
          spawnedJob->EntityIds         = ParentJob->EntityIds;
          spawnedJob->UpdateResumeInfo  = UpdateResumeInfo;

          /* #162 Set processing operation mode. */
          vSwUpdM_ProcessData.ProcOperation = procOperation;
        }

        /* #170 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }

      break;
    }
    case VSWUPDM_PROC_NODE_OPERATION_NONE:
    /* #200 If module processing is already finished, nothing to be done. */
    {
      result = E_OK;
      break;
    }
    default:
    /* #210 Otherwise: Report error. */
    {
      break;
    }
  }

  /* #300 Update child result of given parent job, if no processing was triggered. */
  if (updateResult == TRUE)
  {
    vSwUpdM_Job_SetChildResult(ParentJob, result, VSWUPDM_UNDEFINED_ADDRESS);
  }
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vSwUpdM_Module_ProcessModule */

/**************************************************************
 *  Memory Abstraction:
 *   - Region
 **************************************************************/

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Region_GetRegionIdx
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vSwUpdM_RegionIdxType, VSWUPDM_CODE) vSwUpdM_Region_GetRegionIdx(vSwUpdM_RegionIdType RegionId)
{
  vSwUpdM_RegionIdxType result = VSWUPDM_INVALID_ID;
  vSwUpdM_RegionIdxType regionIdx;

  /* #10 For all regions */
  for (regionIdx = 0u; regionIdx < vSwUpdM_EntityData.Count.RegionCount; regionIdx++)
  {
    /* #20 If ID of region matches given value */
    if (vSwUpdM_GetVarRegions(regionIdx).RegionIDOfVarRegions == RegionId)
    {
      /* #30 Return region index and finish search. */
      result = regionIdx;
      break;
    }
  }

  return result;
} /* vSwUpdM_Region_GetRegionIdx */

/**********************************************************************************************************************
 * vSwUpdM_Region_UpdateState
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateState(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_RegionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(RegionIdx);

  /* #10 If given state doesn't match the current region instance state */
  if (region->DynamicAttributesOfVarRegion.State != State)
  {
    /* #20 Prepare pending attributes of region. */
    vSwUpdM_Region_PreparePendingAttributes(RegionIdx);

    /* #30 Set programming attempt counter in pending attributes. */
    region->PendingAttributesOfVarRegion.State  = State;
    /* #40 Mark pending attributes as dirty. */
    region->AttributesDirty                     = TRUE;
  }
} /* vSwUpdM_Region_UpdateState */

/**********************************************************************************************************************
 * vSwUpdM_Region_UpdateAndPersistState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_UpdateAndPersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_RegionStateType State,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vSwUpdM_Region_UpdateState(RegionIdx, State);
  retVal = vSwUpdM_Region_PersistState(PartitionId, ModuleId, RegionIdx, VSWUPDM_SID_NONE, ParentJob, Source);

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR  */
} /* vSwUpdM_Region_UpdateAndPersistState */

/**********************************************************************************************************************
 * vSwUpdM_Region_PersistState
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_PersistState(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType            retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(RegionIdx); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  /* #10 If attributes of current region are marked dirty */
  if (region->AttributesDirty == TRUE)
  {
    vSwUpdM_RegionStateType state     = region->PendingAttributesOfVarRegion.State;
    vSwUpdM_QueuePrioType   jobPrio   = (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT;
    vSwUpdM_JobPtrType      spawnedJob;

    /* #20 If region state is set to "erased"
     *   Use lower job priority, to persist segment states first. */
    if (state == VSWUPDM_REGION_STATE_ERASED)
    {
      jobPrio = (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_PERSIST_REGION_STATE_LOW;
    }

    /* #30 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #40 Spawn job to handle persisting of updated state and/or erase address of region instance. */
    spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PERSIST_REGION_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, jobPrio, ConfirmationService, ParentJob, Source);

    /* #50 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
    if (retVal == E_OK)
    {
      vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);
      spawnedJob->EntityIds.PartitionId = PartitionId;
      spawnedJob->EntityIds.ModuleId    = ModuleId;
      spawnedJob->EntityIds.RegionIdx   = RegionIdx;
      spawnedJob->EntityIds.RegionId    = vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(ModuleId) + RegionIdx);

      /* #60 If region state is set to "erased" */
      if (state == VSWUPDM_REGION_STATE_ERASED)
      {
        /* #61 Set state of all segments contained in given region to "erased". */
        vSwUpdM_Region_UpdateSegmentStates(region, VSWUPDM_SEGMENT_STATE_ERASED);

        /* #62 Trigger persisting of all updated segment states.
         *   Do not enforce persisting of segment count. */
        (void)vSwUpdM_Segment_PersistState(&spawnedJob->EntityIds, VSWUPDM_SID_NONE, FALSE, spawnedJob, Source);
      }
    }

    /* #70 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }
  /* #100 Otherwise */
  else
  {
    /* #110 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
    vSwUpdM_Job_SetChildResultAndConfirm(ParentJob, Source, ConfirmationService, retVal);
  }

  return retVal;
  /* PRQA S 6050, 6060 1 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
} /* vSwUpdM_Region_PersistState */

/**********************************************************************************************************************
 * vSwUpdM_Region_PreparePendingAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_PreparePendingAttributes(
  vSwUpdM_RegionIdxType RegionIdx)
{
  vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(RegionIdx);

  /* #10 If pending attributes aren't marked as dirty yet */
  if (region->AttributesDirty == FALSE)
  {
    /* #20 Copy dynamic attributes of region instance into pending attributes. */
    region->PendingAttributesOfVarRegion = region->DynamicAttributesOfVarRegion;
  }
}

/**********************************************************************************************************************
 * vSwUpdM_Region_UpdateProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateProgrammingAttempts(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts)
{
  vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(RegionIdx);

  /* #10 Prepare pending attributes with attributes of region instance. */
  vSwUpdM_Region_PreparePendingAttributes(RegionIdx);

  /* #20 Set programming attempt counter in pending attributes. */
  region->PendingAttributesOfVarRegion.ProgrammingAttempts  = ProgrammingAttempts;
  /* #30 Mark pending attributes as dirty. */
  region->AttributesDirty                                   = TRUE;
}

/**********************************************************************************************************************
 * vSwUpdM_Region_IncProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_IncProgrammingAttempts(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdxType RegionIdx)
{
  Std_ReturnType                  retVal              = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 Increment current programming attempt counter of region instance by one. */
  vSwUpdM_ProgrammingAttemptsType programmingAttempts = vSwUpdM_GetVarRegions(RegionIdx).DynamicAttributesOfVarRegion.ProgrammingAttempts + 1u;

  /* #20 Update programming attempt counter of module instance if necessary. */
  retVal = vSwUpdM_Module_UpdateProgrammingAttempts(programmingAttempts, PartitionId, ModuleId);

  if (retVal == E_OK)
  {
    /* #30 Update programming attempt counter of region instance. */
    vSwUpdM_Region_UpdateProgrammingAttempts(RegionIdx, programmingAttempts);
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_Region_UpdateEraseAddress
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */

FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateEraseAddress(
  vSwUpdM_RegionIdxType RegionIdx,
  vSwUpdM_AddressType EraseAddress)
{
  vSwUpdM_VarRegionsPtrType region = vSwUpdM_GetAddrVarRegions(RegionIdx);

  /* #10 Prepare pending attributes with attributes of region instance. */
  vSwUpdM_Region_PreparePendingAttributes(RegionIdx);

  /* #20 Set erase address of region and mark it as dirty. */
  region->EraseAddressOfVarRegion = EraseAddress;
  region->EraseAddressDirty       = TRUE;
  /* #30 Mark pending attributes as dirty. */
  region->AttributesDirty         = TRUE;
}

/**********************************************************************************************************************
 * vSwUpdM_Region_EraseRegion
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Region_EraseRegion(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  boolean UpdateResumeInfo,
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_NodeIterType Source,
  vSwUpdM_JobPtrType ParentJob)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType  retVal        = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean         updateResult  = TRUE;

  /* ----- Implementation ------------------------------------------------- */
  /* #10 Evaluate state of region instance in opened module/partition.
   *   If region isn't erased yet */
  if (vSwUpdM_GetVarRegions(EntityIds->RegionIdx).DynamicAttributesOfVarRegion.State != VSWUPDM_REGION_STATE_ERASED)
  {
    /* #11 Check whether programming attempts are exceeded. */
    retVal = vSwUpdM_Region_CheckProgrammingAttempts(EntityIds->ModuleId, EntityIds->RegionIdx);

    if (retVal == E_OK)
    {
      vSwUpdM_JobPtrType    spawnedJob;
      vSwUpdM_QueuePrioType prio = (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT;

      updateResult = FALSE;

      /* #20 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #30 If parent job is given, use a higher priority then it.
        * Otherwise, use default priority for erase region job. */
      if (ParentJob != NULL_PTR)
      {
        prio = ParentJob->CurrentPrio + 1u;
      }

      /* #40 Spawn job to erase region instance. */
      spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_ERASE_REGION, Operation, prio, VSWUPDM_SID_NONE, ParentJob, Source);

      /* #50 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        /* #51 Pass entity IDs to erase region job. */
        spawnedJob->EntityIds           = *EntityIds;
        spawnedJob->UpdateResumeInfo    = UpdateResumeInfo;
      }

      /* #60 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* #100 Update result of potential parent job when necessary. */
  if (updateResult == TRUE)
  {
    vSwUpdM_Job_SetChildResult(ParentJob, retVal, VSWUPDM_UNDEFINED_ADDRESS);
  }

  return retVal;
} /* vSwUpdM_Region_EraseRegion */

/**********************************************************************************************************************
 * vSwUpdM_Region_UpdateSegmentStates
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
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Region_UpdateSegmentStates(
  P2CONST(vSwUpdM_VarRegionsType, AUTOMATIC, VSWUPDM_APPL_CONST) Region,
  vSwUpdM_SegmentStateType SegmentState)
{
  vSwUpdM_AddressType   address;
  vSwUpdM_SegmentIdType segmentId = VSWUPDM_SEGMENT_ID_DEFAULT;

  /* #10 Iterate over all segments which are part of the current region,
    *   beginning at the (reserved) start address of the region. */
  address = Region->ReservedStartAddressOfVarRegions;

  /* #20 While the (reserved) end address of the region isn't reached */
  while (address < Region->ReservedEndAddressOfVarRegions)
  {
    vSwUpdM_VarSegmentsPtrType segment;

    /* #30 Search segment at current address. */
    if (vSwUpdM_Segment_SearchSegment(&segmentId.DynamicSegmentId, address) == E_OK)
    {
      segment = vSwUpdM_GetAddrVarSegments(segmentId.DynamicSegmentId); /* PRQA S 2853, 2933 */ /* MD_vSwUpdM_2853_InitializationChecked, MD_vSwUpdM_2933_PointerCalculatedFromCheckedInitialization */

      /* #40 If segment isn't a reserved segment (so free or used) */
      if (segment->ClassOfVarSegments != VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED)
      {
        /* #41 Reset write address of segment to point to reserved start address. */
        (void)vSwUpdM_Segment_UpdateWriteAddress(segment, segment->ReservedStartAddressOfVarSegments);

        /* #42 Update state of segment to "erased". */
        (void)vSwUpdM_Segment_UpdateState(segment, SegmentState);
      }

      /* #50 Set current address to reserved end address of current segment. */
      address = segment->ReservedEndAddressOfVarSegments;
    }
    else
    {
      address = Region->ReservedEndAddressOfVarRegions;
    }

    /* #51 Unless the end of the address range was reached
      *   Increment current address by one to point behind current segment. */
    if (address < VSWUPDM_MAX_ADDRESS)
    {
      address++;
    }
  }
} /* vSwUpdM_Region_UpdateSegmentStates */

/**************************************************************
 *  Memory Abstraction:
 *   - Segment
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Segment_PrepareAddressInfo
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
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_PrepareAddressInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo)
{
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ------------------------------------------------- */
  /* #10 If the end address of given segment information is undefined,
   *   while the length is defined */
  if (SegmentInfo->EndAddress == VSWUPDM_UNDEFINED_ADDRESS)
  {
    if (SegmentInfo->Length != VSWUPDM_UNDEFINED_LENGTH)
    {
      /* #20 Calculate end address from sum of start address and length subtracted by one. */
      SegmentInfo->EndAddress = SegmentInfo->StartAddress + (SegmentInfo->Length - 1u);
    }
  }
  /* #100 Otherwise */
  else
  {
    /* #110 If the length of given segment is undefined,
     *   while the end address is at bigger or equal to the start address */
    if ( (SegmentInfo->Length == VSWUPDM_UNDEFINED_LENGTH)
      && (SegmentInfo->EndAddress >= SegmentInfo->StartAddress) )
    {
      /* #120 Calculate length from subtracting start address from end address and adding one. */
      SegmentInfo->Length = (SegmentInfo->EndAddress - SegmentInfo->StartAddress) + 1u;
    }
  }

  /* #200 If fixed length handling is requested */
  if (SegmentInfo->LengthHandling == VSWUPDM_LENGTH_HANDLING_FIXED)
  {
    /* #210 If end address is undefined, value is out of range. */
    if (SegmentInfo->EndAddress == VSWUPDM_UNDEFINED_ADDRESS)
    {
      retVal = VSWUPDM_E_OUT_OF_RANGE;
    }
    /* #220 Otherwise, if end address is smaller then start address, values are out of range. */
    else if (SegmentInfo->EndAddress < SegmentInfo->StartAddress)
    {
      retVal = VSWUPDM_E_OUT_OF_RANGE;
    }
    /* #230 Otherwise, if range defined by end address and start address doesn't match given or calculated length,
     *   values are out of range. */
    else if (((SegmentInfo->EndAddress - SegmentInfo->StartAddress) + 1u) != SegmentInfo->Length)
    {
      retVal = VSWUPDM_E_OUT_OF_RANGE;
    }
    /* #240 Otherwise: Segment information is well-formed. */
    else
    {
      retVal = E_OK;
    }
  }
  /* #300 Otherwise (dynamic length handling is requested) */
  else /* LengthHandling == VSWUPDM_LENGTH_HANDLING_DYNAMIC */
  {
    if ( (SegmentInfo->EndAddress != VSWUPDM_UNDEFINED_ADDRESS)
      && (SegmentInfo->EndAddress < SegmentInfo->StartAddress) )
    {
      retVal = VSWUPDM_E_OUT_OF_RANGE;
    }
    else
    {
      /* #310 Segment information is well-formed. */
      retVal = E_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Segment_PrepareAddressInfo */

/**********************************************************************************************************************
 * vSwUpdM_Segment_IsAddAllowed
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
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsAddAllowed(
  P2VAR(vSwUpdM_ClassOfVarSegmentsType, AUTOMATIC, VSWUPDM_APPL_VAR) TrailingSegmentClass,
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) ActiveSegment,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  vSwUpdM_AddressType StartAddress)
{
  boolean                         allowed               = FALSE;
  vSwUpdM_ClassOfVarSegmentsType  trailingSegmentClass  = VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED;

  /* #10 Evaluate class of existing segment */
  switch (ActiveSegment->ClassOfVarSegments)
  {
    case VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP:
    /* #100 If segment represents a gap between regions */
    {
      /* #110 Determine whether segment to be added is allowed, based on given segment class. */
      switch (SegmentClass)
      {
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
        /* #120 If segment shall be a free memory area within a region */
        {
          /* #121 Adding new segment is allowed, create trailing gap segment when necessary. */
          allowed = TRUE;
          trailingSegmentClass = VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP;

          break;
        }
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
        /* #130 If any other segment class is given
         *   Adding new segment isn't allowed. */
        {
          break;
        }
        default:
        /* #140 Otherwise: Unknown segment class, report error. */
        {
          break;
        }
      }

      break;
    }
    case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
    /* #200 If segment is a free memory area within a region */
    {
      /* #210 Determine whether segment to be added is allowed, based on given segment class. */
      switch (SegmentClass)
      {
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
        /* #220 If segment shall be a gap between regions or a free memory area within a region
         *   Adding new segment isn't allowed. */
        {
          break;
        }
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
        /* #230 If segment shall be used for updated data within a region or a reserved memory area within a region */
        {
          /* #231 Adding new segment is allowed, create trailing free segment when necessary. */
          allowed = TRUE;
          trailingSegmentClass = VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE;

          break;
        }
        default:
        /* #240 Otherwise: Unknown segment class, report error. */
        {
          break;
        }
      }

      break;
    }
    case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
    /* #300 If segment is used for updated data to be programmed within a region (visible as external dynamic segment) */
    {
      /* #310 Determine whether segment to be added is allowed, based on given segment class. */
      switch (SegmentClass)
      {
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP:
        /* #320 If segment shall be a gap between regions
         *   Adding new segment isn't allowed. */
        {
          break;
        }
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
        case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
        /* #330 If segment shall be a free memory area, used for updated data or a reserved memory area within a region */
        {
          /* #340 If existing segment has fixed length and thus cannot be truncated */
          if (ActiveSegment->DynamicAttributesOfVarSegment.LengthHandling == VSWUPDM_LENGTH_HANDLING_FIXED)
          {
            /* #341 Adding new segment isn't allowed. */
          }
          /* #350 Otherwise, if reserved area of existing segment starts at same address */
          else if (ActiveSegment->ReservedStartAddressOfVarSegments == StartAddress)
          {
            /* #351 Adding new segment isn't allowed. */
          }
          /* #360 Otherwise, if existing segment (with dynamic length is already written beyond requested start address and thus cannot be truncated */
          else if (ActiveSegment->WriteAddressOfVarSegments > StartAddress)
          {
            /* #361 Adding new segment isn't allowed. */
          }
          /* #370 Otherwise */
          else
          {
            /* #371 Adding new segment is allowed, create trailing free segment when necessary. */
            allowed = TRUE;
            trailingSegmentClass = VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE;
          }

          break;
        }
        default:
        /* #380 Otherwise: Unknown segment class, report error. */
        {
          /* Error: Unknown segment class */
          break;
        }
      }

      break;
    }
    case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
    /* #400 If segment is a reserved memory area within a region, defined by a configured static segment */
    {
      /* #410 No other segment allowed in this area, report error. */
      break;
    }
    default:
    /* #500 Otherwise: Unknown segment class, report error. */
    {
      break;
    }
  }

  /* #600 Report back class to be used for potential trailing segment. */
  *TrailingSegmentClass = trailingSegmentClass;

  return allowed;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_Segment_IsAddAllowed */

/**********************************************************************************************************************
 * vSwUpdM_Segment_IsDuplicate
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
VSWUPDM_LOCAL FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_IsDuplicate(
  P2CONST(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  P2CONST(vSwUpdM_VarSegmentsType, AUTOMATIC, VSWUPDM_APPL_CONST) ActiveSegment)
{
  boolean retVal = FALSE;

  /* #10 If all of the following conditions apply:
   *   * Segment class indicates new segment shall be used for updated data.
   *   * Existing segment is segment used for updated data.
   *   * Existing segment is still in erased state.
   *   * Start address of new segment is equal to start address of existing segment. */
  if ( (SegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
    && (ActiveSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
    && (ActiveSegment->DynamicAttributesOfVarSegment.State == VSWUPDM_SEGMENT_STATE_ERASED)
    && (SegmentInfo->StartAddress == ActiveSegment->DynamicAttributesOfVarSegment.StartAddress) )
  {
    /* #20 If end address of new segment is equal to end address of existing segment
     *   consider new segment to be a duplicate of existing one. */
    if (SegmentInfo->EndAddress == ActiveSegment->EndAddressOfVarSegments)
    {
      retVal = TRUE;
    }
    /* #30 Otherwise: */
    else
    {
      /* #40 If dynamic length handling is requested for new segment
       *   and end address of new segment is greater or equal to end address of existing segment
       *   consider new segment to be a duplicate of existing one. */
      if ( (SegmentInfo->LengthHandling == VSWUPDM_LENGTH_HANDLING_DYNAMIC)
        && (SegmentInfo->EndAddress >= ActiveSegment->EndAddressOfVarSegments) )
      {
        retVal = TRUE;
      }
    }
  }

  return retVal;
} /* vSwUpdM_Segment_IsDuplicate */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Segment_AddSegment
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
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_ClassOfVarSegmentsType SegmentClass,
  vSwUpdM_AlignGranularityType AlignGranularity,
  boolean RemoteUpdateRequired)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                retVal            = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_SegmentIdValueType    segmentId         = VSWUPDM_INVALID_ID;
  vSwUpdM_AddressType           startAddress;
  vSwUpdM_AddressType           endAddress;
  vSwUpdM_SegmentInfoType       localSegmentInfo;

  VSWUPDM_DUMMY_STATEMENT(RemoteUpdateRequired); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ------------------------------------------------- */
  /* #10 Operate on local copy of given segment info. */
  localSegmentInfo  = *SegmentInfo;
  startAddress      = localSegmentInfo.StartAddress;

  /* #20 If new segment shall be used for update data within a region
   *   and maximum number of dynamic external segments is already used */
  if ( (SegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
    && (vSwUpdM_EntityData.Count.ExternalSegmentCount >= vSwUpdM_GetDynamicNumberOfSegments()) )
  {
    /* #21 Report error, number of allowed segments exceeded. */
    retVal = VSWUPDM_E_SEGMENTS_EXCEEDED;
  }
  /* #22 Otherwise, prepare the given segment info for further evaluation. */
  else
  {
    retVal = vSwUpdM_Segment_PrepareAddressInfo(&localSegmentInfo);
  }

  /* #30 If result if positive so far */
  if (retVal == E_OK)
  {
    /* #32 Search for the existing segment at the aligned start address. */
    retVal = vSwUpdM_Segment_SearchSegment(&segmentId, startAddress);
  }

  /* #40 If a valid existing segment was found */
  if (retVal == E_OK)
  {
    vSwUpdM_VarSegmentsPtrType    activeSegment;
    vSwUpdM_AddressType           rangeStart;
    vSwUpdM_AddressType           rangeEnd;
    vSwUpdM_AddressType           initialEnd;
    vSwUpdM_AddressType           reservedEnd;
    vSwUpdM_AlignGranularityType  alignGranularity = AlignGranularity;

    retVal = E_NOT_OK;

    activeSegment = vSwUpdM_GetAddrVarSegments(segmentId);

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    if (activeSegment->RegionIdxOfVarSegments != VSWUPDM_INVALID_ID)
    {
      if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(activeSegment->RegionIdxOfVarSegments).RegionIDOfVarRegions)))
      {
        alignGranularity = VSWUPDM_ALIGN_GRANULARITY_NONE;
      }
    }
#endif

    /* #31 Align requested start address to front of the given device granularity,
     *   as this is included in the memory to be reserved for the segment. */
    (void)vSwUpdM_Range_AlignAddress(&startAddress, vSwUpdM_EntityData.OpenIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_FRONT, alignGranularity);

    /* #100 Allowed address range for new segment defaults to range occupied to existing segment,
     *   excluding any reserved areas at the start and end. */
    rangeStart    = activeSegment->DynamicAttributesOfVarSegment.StartAddress;
    rangeEnd      = activeSegment->EndAddressOfVarSegments;
    initialEnd    = activeSegment->InitialEndAddressOfVarSegments;
    reservedEnd   = activeSegment->ReservedEndAddressOfVarSegments;

    /* #110 If end address of requested segment is undefined and dynamic length handling is requested */
    if ( (localSegmentInfo.EndAddress == VSWUPDM_UNDEFINED_LENGTH)
      && (localSegmentInfo.LengthHandling == VSWUPDM_LENGTH_HANDLING_DYNAMIC) )
    {
      /* #111 Inherit reserved end address from existing segment. */
      endAddress = reservedEnd;

      /* #120 If requested segment shall be a free memory area
       *   and existing segment is a memory used for updated data */
      if ( (SegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
        && (activeSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED) )
      {
        /* #121 Limit range of new segment to initial end address of existing segment.
         *   Required to prevent false merging of separated free segments, when used segment is concluded. */
        localSegmentInfo.EndAddress = initialEnd;
        rangeEnd                    = initialEnd;
      }
      /* #130 Otherwise */
      else
      {
        /* #131 Limit range of new segment to end address of existing segment. */
        localSegmentInfo.EndAddress = rangeEnd;
      }
    }
    /* #140 Otherwise */
    else
    {
      /* #141 Use given value as actual end address. */
      endAddress = localSegmentInfo.EndAddress;
    }

    if (vSwUpdM_Segment_IsDuplicate(&localSegmentInfo, SegmentClass, activeSegment) == TRUE)
    {
      localSegmentInfo.Id.DynamicSegmentId = segmentId;
      retVal = vSwUpdM_GetSegmentInfo(SegmentInfo, localSegmentInfo.Id);
    }
    else
    {
      /* #150 Align actual end address to end of the given device granularity,
       *   as this is included in the memory to be reserved for the segment. */
      (void)vSwUpdM_Range_AlignAddress(&endAddress, vSwUpdM_EntityData.OpenIds.PartitionId, VSWUPDM_ADDRESS_ALIGNMENT_BACK, alignGranularity);

      /* #160 Verify that requested segment is completely located within the allowed address range. */
      if (localSegmentInfo.EndAddress <= rangeEnd)
      {
        vSwUpdM_ClassOfVarSegmentsType trailingSegmentClass;
        /* #170 Verify that the requested segment is allowed to be added, based on the existing segment. */
        boolean allowed = vSwUpdM_Segment_IsAddAllowed(&trailingSegmentClass, activeSegment, SegmentClass, startAddress);

        if (allowed == TRUE)
        {
          vSwUpdM_QueueHandleType     queueHandle;
          /* #200 New segment is always part of same region as existing one and typically inherits its state as well. */
          vSwUpdM_RegionIdxType       regionIdx           = activeSegment->RegionIdxOfVarSegments;
          vSwUpdM_SegmentStateType    segmentState        = activeSegment->DynamicAttributesOfVarSegment.State;
          vSwUpdM_SegmentIdxType      writeSegmentIdx     = vSwUpdM_EntityData.Count.WriteSegmentCount;
          vSwUpdM_SegmentIdxType      externalSegmentIdx  = vSwUpdM_EntityData.Count.ExternalSegmentCount;
          boolean                     remoteUpdateRequired  = FALSE;

          retVal = E_OK;

          /* #210 If the current segment is partially written ('pending'), the new segment will be in state 'erased' instead. */
          if (segmentState == VSWUPDM_SEGMENT_STATE_PENDING)
          {
            segmentState = VSWUPDM_SEGMENT_STATE_ERASED;
          }

          /* #300 If the reserved area of the requested segment doesn't coincide with the beginning of the existing segment */
          if (rangeStart != startAddress)
          {
            /* #310 Truncate the existing segment, so that it ends just before the reserved start address of the new segment. */
            activeSegment->EndAddressOfVarSegments          = startAddress - 1u;
            activeSegment->InitialEndAddressOfVarSegments   = startAddress - 1u;
            activeSegment->ReservedEndAddressOfVarSegments  = activeSegment->EndAddressOfVarSegments;

            /* #320 If the start address of the existing segment is smaller than the reserved start address of the requested segment */
            if (rangeStart < startAddress)
            {
              /* #321 The requested segment doesn't occupy the complete range (excluding reserved areas) of the existing segment.
               *   Recalculate length of existing segment to match the updated range. */
              activeSegment->RealLength = startAddress - rangeStart;
            }
            /* #330 Otherwise */
            else
            {
              /* #331 The requested segment occupies the complete range (excluding reserved areas) of the existing segment.
               *   The existing segment thus only consists of reserved areas.
               *   Update the start address to point behind the end address and set the length to zero. */
              activeSegment->DynamicAttributesOfVarSegment.StartAddress = startAddress;
              activeSegment->RealLength                                 = 0u;
            }

            if (SegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
            {
              writeSegmentIdx = activeSegment->WriteSegmentIdx;
            }

            /* #340 Add entry for new segment to internal segments queue, using reserved start address as priority. */
            queueHandle   = vSwUpdM_QueuePrioInsert(&vSwUpdM_InternalSegmentsQueue, startAddress);
            segmentId     = vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle);
            activeSegment = vSwUpdM_GetAddrVarSegments(segmentId);

            /* #350 Increment internal segment count to include newly added segment. */
            vSwUpdM_EntityData.Count.InternalSegmentCount++;
          }
          /* #380 Otherwise */
          else
          {
            /* #381 Re-use existing segment entry */
          }

          switch (SegmentClass)
          {
            case VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED:
            case VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED:
            /* #360 If a matching segment is added ('used' or 'reserved') */
            {
              /* #361 Increment count of segments which will be written during update and thus the write address needs to be tracked. */
              vSwUpdM_EntityData.Count.WriteSegmentCount++;
              break;
            }
            case VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE:
            default:
            /* #370 Otherwise, write address not tracked. */
            {
              break;
            }
          }

          /* #400 If the requested segment is used for update data */
          if (SegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
          {
            /* #410 Increment count of dynamic external segments. */
            vSwUpdM_EntityData.Count.ExternalSegmentCount++;

            /* #420 Insert requested segment into external segments queue, using external segment index as priority.
             *   Required to keep track of order in which external segments are created. */
            queueHandle = vSwUpdM_QueuePrioInsert(&vSwUpdM_ExternalSegmentsQueue, externalSegmentIdx);
            vSwUpdM_QueueSetEntityHandle(&vSwUpdM_ExternalSegmentsQueue, queueHandle, segmentId);

            /* #430 Assign external index to segment. */
            activeSegment->ExternalSegmentIdx = externalSegmentIdx;
          }
          /* #440 Otherwise, set external index of segment to invalid value. */
          else
          {
            activeSegment->ExternalSegmentIdx = VSWUPDM_INVALID_ID;
          }

          /* #450 Set write address to (reserved) start address. */
          localSegmentInfo.WriteAddress = startAddress;

          /* #460 If state of segment isn't given, but shall be detected automatically
           *   Inherit state of segment from existing segment */
          if (localSegmentInfo.State == VSWUPDM_SEGMENT_STATE_AUTODETECT)
          {
            localSegmentInfo.State = segmentState;
          }

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
          if (vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
          {
            vSwUpdM_NodeGroupOwnersIdxOfRegionType nodeGroupIdx = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(regionIdx).RegionIDOfVarRegions);
            /* Local instance has the lock (= is the master) */
            /* Region is remote if Group is > 1 OR does not contain local node. */
            if ((vSwUpdM_GetNNodesOfNodeGroup(nodeGroupIdx) > 1u) || (!vSwUpdM_IsWithLocalNodeOfNodeGroup(nodeGroupIdx)))
            {
            /* Region is remote */
              remoteUpdateRequired = RemoteUpdateRequired;
            }
          }
#endif

          /* #500 Assign all attributes of segment, marking both the attributes and write address as dirty. */
          activeSegment->DynamicAttributesOfVarSegment.StartAddress       = localSegmentInfo.StartAddress;
          activeSegment->DynamicAttributesOfVarSegment.InitialLength      = localSegmentInfo.Length;
          activeSegment->DynamicAttributesOfVarSegment.LengthHandling     = localSegmentInfo.LengthHandling;
          activeSegment->DynamicAttributesOfVarSegment.State              = localSegmentInfo.State;
          activeSegment->DynamicAttributesOfVarSegment.ResumeOffset       = 0u;
          activeSegment->WriteAddressOfVarSegments                        = localSegmentInfo.WriteAddress;
          activeSegment->RealLength                                       = (localSegmentInfo.EndAddress - localSegmentInfo.StartAddress) + 1u;
          activeSegment->EndAddressOfVarSegments                          = localSegmentInfo.EndAddress;
          activeSegment->ReservedStartAddressOfVarSegments                = startAddress;
          activeSegment->ReservedEndAddressOfVarSegments                  = endAddress;
          activeSegment->TypeOfVarSegments                                = localSegmentInfo.Type;
          activeSegment->ClassOfVarSegments                               = SegmentClass;
          activeSegment->HandleIDOfVarSegments                            = (vSwUpdM_HandleIDOfVarSegmentsType)localSegmentInfo.Id.StaticSegmentId;
          activeSegment->RegionIdxOfVarSegments                           = regionIdx;
          activeSegment->AttributesDirty                                  = TRUE;
          activeSegment->WriteAddressDirty                                = TRUE;
          activeSegment->RemoteDirty                                      = remoteUpdateRequired;
          activeSegment->SegmentClean                                     = TRUE;

          /* #510 Assign the index of all writable segments, required for persisting of the write address. */
          activeSegment->WriteSegmentIdx  = writeSegmentIdx;

          /* #530 Update given segment information with actual values, including ID and (apparent) write address. */
          localSegmentInfo.Id.DynamicSegmentId  = segmentId;
          vSwUpdM_Segment_GetApparentWriteAddress(activeSegment, &localSegmentInfo.WriteAddress);
          *SegmentInfo                          = localSegmentInfo;

          /* #600 If the reserved end address of the original segment doesn't coincide with the reserved end address of the requested segment,
           *   the requested segment doesn't use the available range completely. */
          if (reservedEnd != endAddress)
          {
            vSwUpdM_VarSegmentsPtrType trailingSegment;

            /* #610 Update the initial start address of the added segment to match the end address. */
            activeSegment->InitialEndAddressOfVarSegments = localSegmentInfo.EndAddress;

            /* #620 Add an additional trailing segment to occupy the unused range, starting directly behind the reserved end address. */
            rangeStart = endAddress + 1u;

            queueHandle   = vSwUpdM_QueuePrioInsert(&vSwUpdM_InternalSegmentsQueue, rangeStart);
            trailingSegment = vSwUpdM_GetAddrVarSegments(vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle));
            vSwUpdM_EntityData.Count.InternalSegmentCount++;

            /* #630 Assign all attributes of trailing segment.
             *   Attributes won't be persisted, but write address is.
             *   Thus the latter are marked as dirty */
            trailingSegment->WriteAddressOfVarSegments                        = rangeStart;
            trailingSegment->DynamicAttributesOfVarSegment.StartAddress       = rangeStart;
            trailingSegment->DynamicAttributesOfVarSegment.InitialLength      = ((initialEnd - rangeStart) + 1u);
            trailingSegment->DynamicAttributesOfVarSegment.LengthHandling     = VSWUPDM_LENGTH_HANDLING_DYNAMIC;
            trailingSegment->DynamicAttributesOfVarSegment.State              = segmentState;
            trailingSegment->DynamicAttributesOfVarSegment.ResumeOffset       = 0u;
            trailingSegment->RealLength                                       = ((rangeEnd - rangeStart) + 1u);
            trailingSegment->ReservedStartAddressOfVarSegments                = rangeStart;
            trailingSegment->ReservedEndAddressOfVarSegments                  = reservedEnd;
            trailingSegment->EndAddressOfVarSegments                          = rangeEnd;
            trailingSegment->InitialEndAddressOfVarSegments                   = initialEnd;
            trailingSegment->TypeOfVarSegments                                = VSWUPDM_NO_SEGMENTTYPEOFSEGMENT;
            trailingSegment->ClassOfVarSegments                               = trailingSegmentClass;
            trailingSegment->AttributesDirty                                  = FALSE;
            trailingSegment->ExternalSegmentIdx                               = VSWUPDM_INVALID_ID;
            trailingSegment->WriteAddressDirty                                = FALSE;

            /* #640 If trailing segment is a free memory area */
            if (trailingSegmentClass == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
            {
              /* #641 Assign region index and write segment. */
              trailingSegment->RegionIdxOfVarSegments = regionIdx;
              trailingSegment->WriteSegmentIdx        = activeSegment->WriteSegmentIdx;
            }
            /* #650 Otherwise */
            else
            {
              /* #651 Set region index and write index to invalid values. */
              trailingSegment->RegionIdxOfVarSegments = VSWUPDM_INVALID_ID;
              trailingSegment->WriteSegmentIdx        = VSWUPDM_INVALID_ID;
            }
          }
          /* #700 Otherwise */
          else
          {
            /* #710 Inherit initial end address from original segment. */
            activeSegment->InitialEndAddressOfVarSegments = initialEnd;
          }
        }
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Segment_AddSegment */

/**********************************************************************************************************************
 * vSwUpdM_Segment_ConcludeSegment
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
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_ConcludeSegment(
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_AddressType SucceedingAddress,
  vSwUpdM_AddressType WriteAddress)
{
  /* #10 If the allocated range of the given 'used' segment with dynamic length wasn't completely used. */
  if ( (Segment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
    && (Segment->DynamicAttributesOfVarSegment.LengthHandling == VSWUPDM_LENGTH_HANDLING_DYNAMIC)
    && (WriteAddress <= Segment->EndAddressOfVarSegments) )
  {
    boolean mergeSegments = FALSE;
    vSwUpdM_VarSegmentsPtrType nextSegment = NULL_PTR; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

    /* #20 If given segment doesn't end at the very end of address area. */
    if (Segment->ReservedEndAddressOfVarSegments < VSWUPDM_MAX_ADDRESS)
    {
      vSwUpdM_SegmentIdValueType  nextSegmentId;

      /* #30 Search the segment directly adjacent to the given segment. */
      if (vSwUpdM_Segment_SearchSegment(&nextSegmentId, Segment->ReservedEndAddressOfVarSegments + 1u) == E_OK)
      {
        nextSegment = vSwUpdM_GetAddrVarSegments(nextSegmentId);

        /* #40 If the found segment is a free memory area and nothing was written to it yet. */
        if ( (nextSegment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE)
          && (nextSegment->WriteAddressOfVarSegments == nextSegment->ReservedStartAddressOfVarSegments) )
        {
          /* #50 Unused area released by concluding the given segment shall be merged with adjacent segment. */
          mergeSegments = TRUE;
        }
      }
    }

    /* #100 If unused area shall be merged with adjacent segment. */
    if (mergeSegments == TRUE)
    {
      /* #110 Update start addresses and length of adjacent segment to include released memory, according to given succeeding address.
       *   Mark segment attributes as dirty. */
      nextSegment->ReservedStartAddressOfVarSegments          = SucceedingAddress;
      nextSegment->DynamicAttributesOfVarSegment.StartAddress = SucceedingAddress;
      nextSegment->RealLength                                 = (nextSegment->EndAddressOfVarSegments - SucceedingAddress) + 1u;
      nextSegment->AttributesDirty                            = TRUE;
      /* #120 Update write address to point to new start address. */
      (void)vSwUpdM_Segment_UpdateWriteAddress(nextSegment, SucceedingAddress);
    }
    /* #200 Otherwise */
    else
    {
      vSwUpdM_SegmentInfoType freeSegment;

      (void)vSwUpdM_InitSegmentInfo(&freeSegment);

      /* #220 If there is any unused memory in the given segment, taking the reserved area into account. */
      if (Segment->ReservedEndAddressOfVarSegments != (SucceedingAddress - 1u))
      {
        vSwUpdM_AlignGranularityType alignGranularity = VSWUPDM_ALIGN_GRANULARITY_PAGE;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
        if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(Segment->RegionIdxOfVarSegments).RegionIDOfVarRegions)))
        {
          alignGranularity = VSWUPDM_ALIGN_GRANULARITY_NONE;
        }
#endif

        /* #230 Create a new page aligned free segment, with dynamic length, covering the unused area, according to the given succeeding address. */
        freeSegment.StartAddress    = SucceedingAddress;
        freeSegment.LengthHandling  = VSWUPDM_LENGTH_HANDLING_DYNAMIC;
        freeSegment.State           = VSWUPDM_SEGMENT_STATE_AUTODETECT;

        (void)vSwUpdM_Segment_AddSegment(&freeSegment, VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE, alignGranularity, FALSE);
      }

      /* #240 Update to initial end address of given segment to be equal to the actual write address. */
      Segment->InitialEndAddressOfVarSegments = WriteAddress - 1u;
    }

    /* #250 Update end address and length of given segment to match downloaded data. */
    Segment->EndAddressOfVarSegments                      = WriteAddress - 1u;
    Segment->RealLength                                   = WriteAddress - Segment->DynamicAttributesOfVarSegment.StartAddress;
    Segment->ReservedEndAddressOfVarSegments              = SucceedingAddress - 1u;
    Segment->DynamicAttributesOfVarSegment.InitialLength  = Segment->RealLength;
    /* #260 Mark attributes of given segment as dirty. */
    Segment->AttributesDirty                              = TRUE;
  }
} /* vSwUpdM_Segment_ConcludeSegment */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Segment_GetSegmentIdByRange
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetSegmentIdByRange(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  P2CONST(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_CONST) Queue)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_QueueHandleType       queueHandle;

  /* #10 Iterate over all entries of given segment queue. */
  for ( queueHandle = vSwUpdM_QueueGetFirstUsedHandle(Queue);
        queueHandle != VSWUPDM_QUEUE_HANDLE_HEAD_USED;
        queueHandle = vSwUpdM_QueueGetEntry(Queue, queueHandle).next )
  {
    vSwUpdM_VarSegmentsIterType   segmentId =(vSwUpdM_VarSegmentsIterType)vSwUpdM_QueueGetEntry(Queue, queueHandle).entity;
    vSwUpdM_VarSegmentsPtrType    segment   = vSwUpdM_GetAddrVarSegments(segmentId); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
    vSwUpdM_RangeCheckType        rangeCheck;

    /* #20 Test the range given by start address and length against the range covered by the segment, excluding any reserved ares. */
    rangeCheck = vSwUpdM_Range_CheckAgainstRange(
      StartAddress, Length, segment->DynamicAttributesOfVarSegment.StartAddress, segment->RealLength);

    /* #30 If ranges at least overlap */
    if (rangeCheck != VSWUPDM_RANGE_CHECK_MISMATCH)
    {
      /* #40 If given range is completely contained within segment. */
      if (rangeCheck == VSWUPDM_RANGE_CHECK_CONTAINED)
      {
        /* #50 Return found segment. */
        SegmentId->DynamicSegmentId = (vSwUpdM_SegmentIdValueType)segmentId;
        SegmentId->StaticSegmentId  = segment->HandleIDOfVarSegments;

        retVal = E_OK;
      }

      /* #60 Ranges at least overlapped, no need to search further. */
      break;
    }
  }

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Segment_GetSegmentIdByRange */

/**********************************************************************************************************************
 * vSwUpdM_Segment_GetSegmentIdByStartAddress
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
 */
/* PRQA S 3219 1 */ /* MD_MSR_Unreachable */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetSegmentIdByStartAddress(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  P2CONST(vSwUpdM_QueueType, AUTOMATIC, VSWUPDM_APPL_CONST) Queue)
{
  return vSwUpdM_Segment_GetSegmentIdByRange(SegmentId, StartAddress, 0u, Queue);
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Segment_GetSegmentIdByStartAddress */

#if (VSWUPDM_FINE_GRAINED_RESUME == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_Segment_GetFirstExternalSegmentInRange
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
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_GetFirstExternalSegmentInRange(
  P2VAR(vSwUpdM_SegmentIdValueType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_AddressType EndAddress)
{
  Std_ReturnType              retVal              = E_NOT_OK;
  vSwUpdM_SegmentIdxType      externalSegmentIdx  = VSWUPDM_INVALID_ID;
  vSwUpdM_SegmentIdValueType  firstSegmentId      = VSWUPDM_INVALID_ID;
  /* #10 Iterate over all segments which are part of the current region,
   *   beginning at the (original) start address of the region. */
  vSwUpdM_AddressType         address             = StartAddress;

  /* #20 While the (original) end address of the region isn't reached */
  while (address < EndAddress)
  {
    vSwUpdM_SegmentIdValueType  segmentId = VSWUPDM_INVALID_ID;
    vSwUpdM_VarSegmentsPtrType  segment; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

    /* #30 Search segment at current address. */
    if (vSwUpdM_Segment_SearchSegment(&segmentId, address) == E_OK)
    {
      segment = vSwUpdM_GetAddrVarSegments(segmentId);

      /* #40 If segment is used segment */
      if ((segment->ClassOfVarSegments == VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED)
        && (segment->WriteAddressOfVarSegments > StartAddress))
      {
        if ((externalSegmentIdx == VSWUPDM_INVALID_ID)
          || (segment->ExternalSegmentIdx < externalSegmentIdx))
        {
          externalSegmentIdx = segment->ExternalSegmentIdx;
          firstSegmentId = segmentId;
          retVal = E_OK;
        }
      }

      /* #50 Set current address to reserved end address of current segment. */
      address = segment->ReservedEndAddressOfVarSegments;
    }
    else
    {
      address = EndAddress;
    }

    /* #60 Unless the end of the address range was reached
     *   Increment current address by one to point behind current segment. */
    if (address < VSWUPDM_MAX_ADDRESS)
    {
      address++;
    }
  }

  *SegmentId = firstSegmentId;

  return retVal;
} /* vSwUpdM_Segment_GetFirstExternalSegmentInRange */
#endif

/**********************************************************************************************************************
 * vSwUpdM_Segment_PersistState
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Segment_PersistState(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_ServiceIdType ConfirmationService,
  boolean PersistCount,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_JobPtrType spawnedJob;

  /* #10 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job to persist any segment attributes and write addresses marked as dirty. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PERSIST_SEGMENT_STATE, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ConfirmationService, ParentJob, Source);

  /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    spawnedJob->EntityIds = *EntityIds;

    /* #40 If segment count shall be persisted and has changed */
    if ( (PersistCount == TRUE)
      && (vSwUpdM_EntityData.Count.ExternalSegmentCountDirty == TRUE) )
    {
      /* #50 Spawn job to persist current segment count. */
      spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PERSIST_SEGMENT_COUNT, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_NONE, ParentJob, Source);

      /* #60 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (retVal == E_OK)
      {
        spawnedJob->EntityIds = *EntityIds;
      }
    }
  }

  /* #70 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_Segment_PersistState */

/**********************************************************************************************************************
 * vSwUpdM_Segment_UpdateWriteAddress
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Segment_UpdateWriteAddress(
  vSwUpdM_VarSegmentsPtrType Segment,
  vSwUpdM_AddressType WriteAddress)
{
  /* #10 If given address doesn't match the current write address */
  if (Segment->WriteAddressOfVarSegments != WriteAddress)
  {
    /* #20 Update segment write address with given value and mark it as dirty. */
    Segment->WriteAddressOfVarSegments  = WriteAddress;
    Segment->WriteAddressDirty          = TRUE;
  }

  return Segment->WriteAddressDirty;
} /* vSwUpdM_Segment_UpdateWriteAddress */

/**********************************************************************************************************************
 * vSwUpdM_Segment_GetApparentAddress
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
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_GetApparentAddress(
  vSwUpdM_VarSegmentsPtrType Segment,  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) ApparentAddress,
  boolean Overflow)
{
  vSwUpdM_AddressType apparentAddress;
  vSwUpdM_AddressType startAddress;
  vSwUpdM_AddressType endAddress;

  apparentAddress = *ApparentAddress;
  startAddress    = Segment->DynamicAttributesOfVarSegment.StartAddress;
  endAddress      = Segment->EndAddressOfVarSegments;

  /* #10 If given address is smaller than start address of given segment. */
  if (apparentAddress < startAddress)
  {
    /* #11 Report start address as apparent address. */
    apparentAddress = startAddress;
  }
  /* #20 If given address is bigger than end address of given segment.  */
  else if (apparentAddress > endAddress)
  {
    /* #21 Report end address as apparent address. */
    apparentAddress = endAddress;

    /* #22 If overflow flag is set, increment apparent address by one. */
    if (Overflow == TRUE)
    {
      apparentAddress++;
    }
  }
  /* #30 Otherwise */
  else
  {
    /* #31 Address already has correct value. */
  }

  *ApparentAddress = apparentAddress;
} /* vSwUpdM_Segment_GetApparentAddress */

/**********************************************************************************************************************
 * vSwUpdM_Segment_GetApparentWriteAddress
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
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Segment_GetApparentWriteAddress(
  vSwUpdM_VarSegmentsPtrType Segment,  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) WriteAddress)
{
  *WriteAddress = Segment->WriteAddressOfVarSegments;
  vSwUpdM_Segment_GetApparentAddress(Segment, WriteAddress, TRUE);
} /* vSwUpdM_Segment_GetApparentWriteAddress */

/**********************************************************************************************************************
 * vSwUpdM_Segment_GetRegionOwnerGroupIndex
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_NodeGroupOwnersIdxOfRegionType, VSWUPDM_CODE) vSwUpdM_Segment_GetRegionOwnerGroupIndex(vSwUpdM_SegmentIdType Id)
{
  vSwUpdM_NodeGroupOwnersIdxOfRegionType  regionOwnerGroupIndex;
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
  vSwUpdM_RegionIdxType                       regionIdx;

  regionIdx             = vSwUpdM_GetVarSegments(Id.DynamicSegmentId).RegionIdxOfVarSegments;
  regionOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(regionIdx).RegionIDOfVarRegions);
#else
  VSWUPDM_DUMMY_STATEMENT(Id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  regionOwnerGroupIndex = vSwUpdM_GetBroadcastGroup();
#endif

  return regionOwnerGroupIndex;
} /* vSwUpdM_Segment_GetRegionOwnerGroupIndex */

/**************************************************************
 *  Memory Abstraction:
 *   - Range
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Range_EraseRange
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
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Range_EraseRange(
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType PartitionState,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length,
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_JobPtrType ParentJob,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType        retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_QueuePrioType prio    = (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT;
  vSwUpdM_JobPtrType    spawnedJob;

  /* ----- Implementation ------------------------------------------------- */
  /* #10 If parent job is given, use a higher priority then it.
   *   Otherwise, use default priority for erase range job. */
  if (ParentJob != NULL_PTR)
  {
    prio = ParentJob->CurrentPrio + 1u;
  }

  /* #20 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #30 Spawn job to erase range in opened partition. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_ERASE_RANGE, VSWUPDM_JOB_OPERATION_DEFAULT, prio, ConfirmationService, ParentJob, Source);

  /* #40 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    vSwUpdM_Init_EntityIdsDefaults(&spawnedJob->EntityIds);
    spawnedJob->EntityIds.PartitionId  = PartitionId;
    spawnedJob->EntityIds.PartitionState = PartitionState;
    spawnedJob->TargetAddress          = StartAddress;

    (void)vSwUpdM_Buffer_InitAndAddData(&vSwUpdM_BufferInfoEraseRange, NULL_PTR, Length);
  }

  /* #50 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_Range_EraseRange */

/**************************************************************
 *  Memory Abstraction:
 *   - Buffer
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Buffer_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_Init(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_VarDataPointerType Buffer,
   vSwUpdM_LengthType Size)
{
   BufferInfo->Buffer   = Buffer;
   BufferInfo->Position = 0u;
   BufferInfo->Size     = Size;
   BufferInfo->Free     = Size;
   BufferInfo->Used     = 0u;

   return E_OK;
} /* vSwUpdM_Buffer_Init */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_GetUsedBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_VarDataPointerType, VSWUPDM_CODE) vSwUpdM_Buffer_GetUsedBuffer(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
   return &BufferInfo->Buffer[BufferInfo->Position];
} /* vSwUpdM_Buffer_GetUsedBuffer */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_GetFreeBuffer
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vSwUpdM_VarDataPointerType, VSWUPDM_CODE) vSwUpdM_Buffer_GetFreeBuffer(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo) /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
   return &BufferInfo->Buffer[BufferInfo->Position + BufferInfo->Used];
} /* vSwUpdM_Buffer_GetFreeBuffer */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_AddData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_AddData(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_LengthType Length)
{
   Std_ReturnType result = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

   /* #10 If buffer has enough free space to fit requested length */
   if (Length <= BufferInfo->Free)
   {
     /* #20 Increase available data and decrease free space by given length. */
      BufferInfo->Used += Length;
      BufferInfo->Free -= Length;

      /* #30 Report success. */
      result = E_OK;
   }

   return result;
} /* vSwUpdM_Buffer_AddData */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_InitAndAddData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_InitAndAddData(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) Buffer,
   vSwUpdM_VarDataPointerType Data,
     vSwUpdM_LengthType Length)
{

  (void) vSwUpdM_Buffer_Init(Buffer, Data, Length);
  return vSwUpdM_Buffer_AddData(Buffer, Length);
} /* vSwUpdM_Buffer_InitAndAddData */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_ConsumeData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_ConsumeData(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo,
   vSwUpdM_LengthType Length)
{
   Std_ReturnType result = E_NOT_OK;

   /* #10 If the requested length doesn't exceed the available data hold by the buffer */
   if (Length <= BufferInfo->Used)
   {
       /* #20 Forward current position and decrement available data by given length. */
      BufferInfo->Position += Length;
      BufferInfo->Used     -= Length;

      result = E_OK;
   }

   return result;
} /* vSwUpdM_Buffer_ConsumeData */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_CopyRemainder
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_CopyRemainder(
   P2CONST(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SourceBufferInfo, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) TargetBufferInfo)
{
   Std_ReturnType result = E_NOT_OK;
   vSwUpdM_ConstDataPointerType sourceBuffer;
   vSwUpdM_VarDataPointerType targetBuffer;
   vSwUpdM_LengthType length;

   length = SourceBufferInfo->Used;

   /* #10 If given target buffer has enough free space to hold remaining data from given source buffer */
   if (length <= TargetBufferInfo->Free)
   {
      /* #20 Copy remaining data from given source buffer to beginning of free space of given target buffer. */
      sourceBuffer = &SourceBufferInfo->Buffer[SourceBufferInfo->Position];
      targetBuffer = &TargetBufferInfo->Buffer[TargetBufferInfo->Position];

      vSwUpdM_Buffer_Copy(sourceBuffer, targetBuffer, length);

      /* #30 Update available data length of given target buffer. */
      (void)vSwUpdM_Buffer_AddData(TargetBufferInfo, length);

      result = E_OK;
   }

   return result;
} /* vSwUpdM_Buffer_CopyRemainder */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_MoveRemainder
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Buffer_MoveRemainder(
   P2VAR(vSwUpdM_BufferInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BufferInfo)
{
   vSwUpdM_BufferInfoType tempBufferInfo;

   /* #10 Clone given buffer information. */
   tempBufferInfo = *BufferInfo;
   /* #20 Clear complete buffer, by re-initializing given buffer info. */
   (void)vSwUpdM_Buffer_Init(BufferInfo, BufferInfo->Buffer, BufferInfo->Size);

   /* #30 Copy remainder to beginning of buffer. */
   return vSwUpdM_Buffer_CopyRemainder(&tempBufferInfo, BufferInfo);
} /* vSwUpdM_Buffer_MoveRemainder */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_Copy
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Buffer_Copy(
  vSwUpdM_ConstDataPointerType SourceBuffer,
  vSwUpdM_VarDataPointerType TargetBuffer,
  vSwUpdM_LengthType Length)
{
  vSwUpdM_LengthType index;

  for (index = 0u; index < Length; index++)
  {
    TargetBuffer[index] = SourceBuffer[index];
  }
} /* vSwUpdM_Buffer_Copy */

/**********************************************************************************************************************
 * vSwUpdM_Buffer_Fill
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Buffer_Fill(
  vSwUpdM_VarDataPointerType TargetBuffer,
  vSwUpdM_DataType Value,
  vSwUpdM_LengthType Length)
{
  vSwUpdM_LengthType index;

  for (index = 0u; index < Length; index++)
  {
    TargetBuffer[index] = Value;
  }
} /* vSwUpdM_Buffer_Fill */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalEntryPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalEntryPoint(
  P2VAR(vStreamProc_EntryPointIdType, AUTOMATIC, VSWUPDM_APPL_VAR) EntryPointId,
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type)
{
  Std_ReturnType                retVal = E_NOT_OK;
  vStreamProc_EntryPointIdType entryPoint = vSwUpdM_GetEntryPointIdOfIntDataInput(vSwUpdM_GetIntDataInputStartIdxOfDataProcesses(DataProcessId) + Type);

    if (entryPoint != VSWUPDM_NO_ENTRYPOINTIDOFINTDATAINPUT)
    {
      (*EntryPointId) = entryPoint;
      retVal = E_OK;
    }

  return retVal;
} /* vSwUpdM_Pipe_GetInternalEntryPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_HasInternalEntryPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_HasInternalEntryPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type)
{
  boolean                retVal = FALSE;
  vStreamProc_EntryPointIdType entryPointId;

  if (vSwUpdM_Pipe_GetInternalEntryPoint(&entryPointId, DataProcessId, Type) == E_OK)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Pipe_HasInternalEntryPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestInternalEntryPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestInternalEntryPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vStreamProc_LengthType Length,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos)
{
  Std_ReturnType retVal;

  EntryPointInfos->EntryPointId = VSWUPDM_NO_ENTRYPOINTIDOFEXTDATAINPUT;

  /* #10 Get vStreamProc EntryPoint. */
  retVal = vSwUpdM_Pipe_GetInternalEntryPoint(&EntryPointInfos->EntryPointId, DataProcessId, Type);

  /* #20 Request EntryPoint. */
  if (retVal == E_OK)
  {
    retVal = vSwUpdM_Pipe_RequestEntryPoint(
      vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId),
      EntryPointInfos->EntryPointId,
      vSwUpdM_GetStreamProcDataTypeRefOfDataInputType(Type),
      Length,
      EntryPointInfos);
  }

  return retVal;
} /* vSwUpdM_Pipe_RequestInternalEntryPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalExitPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalExitPoint(
  P2VAR(vStreamProc_ExitPointIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ExitPointId,
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type)
{
  Std_ReturnType                retVal = E_NOT_OK;
  vStreamProc_ExitPointIdType exitPoint = vSwUpdM_GetExitPointIdOfIntDataOutput(vSwUpdM_GetIntDataOutputStartIdxOfDataProcesses(DataProcessId) + Type);

    if (exitPoint != VSWUPDM_NO_EXITPOINTIDOFINTDATAOUTPUT)
    {
      (*ExitPointId) = exitPoint;
      retVal = E_OK;
    }

  return retVal;
} /* vSwUpdM_Pipe_GetInternalExitPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_HasInternalExitPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_Pipe_HasInternalExitPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type)
{
  boolean                retVal = FALSE;
  vStreamProc_ExitPointIdType exitPointId;

  if (vSwUpdM_Pipe_GetInternalExitPoint(&exitPointId, DataProcessId, Type) == E_OK)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vSwUpdM_Pipe_HasInternalExitPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_EvalProcessOperation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vSwUpdM_ProcNodeOperationType, VSWUPDM_CODE) vSwUpdM_Pipe_EvalProcessOperation(
  P2CONST(vSwUpdM_ProcessConfigType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessConfig,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId)
{
  vSwUpdM_ProcNodeOperationType procOperation = VSWUPDM_PROC_NODE_OPERATION_INVALID;
  vSwUpdM_ModuleStateType       moduleState;

  /* #100 Evaluate state of module instance in given partition. */
  if (vSwUpdM_Module_GetStateByPartition(&moduleState, ModuleId, PartitionId) == E_OK)
  {
    /* #110 Determine the module state-specific processing operation mode.
     *   Use "START" as default value, if none are configured. */
    if (ProcessConfig->OpSelectCount == 0u)
    {
      procOperation = VSWUPDM_PROC_NODE_OPERATION_START;
    }
    else
    {
      uint8_least selectionIndex;

      for (selectionIndex = 0u; selectionIndex < ProcessConfig->OpSelectCount; selectionIndex++)
      {
        if (ProcessConfig->OpSelect[selectionIndex].ModuleState == moduleState)
        {
          procOperation = ProcessConfig->OpSelect[selectionIndex].ProcOperation;

          break;
        }
      }
    }
  }

  return procOperation;
}

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetExitPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType ExitPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  Std_ReturnType retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;

  if (vStreamProc_PrepareExitPointInfo(PipeId, ExitPointId, ExitPointInfo) == VSTREAMPROC_OK)
  {
    if (vStreamProc_GetExitPointInfo(PipeId, DataTypeId, ExitPointInfo) == VSTREAMPROC_OK)
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_GetExitPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestExitPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType ExitPointId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType Length,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  Std_ReturnType retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;

  /* #10 Prepare and get info of exit point. */
  if (vSwUpdM_Pipe_GetExitPoint(PipeId, ExitPointId, DataTypeId, ExitPointInfo) == E_OK)
  {
    /* #20 Check data availability. */
    if (ExitPointInfo->ReadRequest.StorageInfo.AvailableLength >= Length)
    {
      ExitPointInfo->ReadRequest.StorageInfo.RequestLength = Length;

      /* #30 Request data. */
      if (vStreamProc_RequestExitPointData(PipeId,  ExitPointInfo->ReadRequest.StorageInfo.DataTypeInfo.Id, ExitPointInfo->ReadRequest.StorageInfo.RequestLength, ExitPointInfo) == VSTREAMPROC_OK)
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_RequestExitPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_RequestInternalExitPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_RequestInternalExitPoint(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vStreamProc_LengthType Length,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  vStreamProc_EntryPointIdType  exitPointId = 0u;

  Std_ReturnType retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;

  /* #10 Get vStreamProc ExitPoint referred by vSwUpdM pipe config. */
  if (vSwUpdM_Pipe_GetInternalExitPoint(&exitPointId,  DataProcessId, Type) == E_OK)
  {
    /* #20 Request exit point. */
    retVal = vSwUpdM_Pipe_RequestExitPoint(
      vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId),
      exitPointId,
      vSwUpdM_GetStreamProcDataTypeRefOfDataOutputType(Type),
      Length,
      ExitPointInfo);
  }

  return retVal;
} /* vSwUpdM_Pipe_RequestInternalExitPoint */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadResult()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadResult( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type)
{
  vStreamProc_ExitPointInfoType exitPointInfo;
  Std_ReturnType retVal;

  /* #10 Get vStreamProc ExitPoint referred by vSwUpdM pipe config and request it. */
  retVal = vSwUpdM_Pipe_RequestInternalExitPoint(DataProcessId, Type, 1u, &exitPointInfo);

  if (retVal == E_OK)
  {
    /* #20 Get data from exit and acknowledge buffer. */
    P2CONST(Std_ReturnType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR) result = vStreamProc_GetTypedReadRequestBuffer_Std_ReturnType(&exitPointInfo.ReadRequest);

    if (vStreamProc_AcknowledgeExitPoint(vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId), exitPointInfo.ReadRequest.StorageInfo.RequestLength, TRUE, &exitPointInfo) == VSTREAMPROC_OK)
    {
      retVal = (*result);
    }
    else
    {
      retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_ReadResult */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadRange()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadRange( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vStreamProc_LengthType Length,
  vSwUpdM_RangeInfoStreamPtrType RangeInfo)
{
  vStreamProc_ExitPointInfoType exitPointInfo;
  Std_ReturnType retVal;
  uint8_least index;

  /* #10 Get vStreamProc ExitPoint referred by vSwUpdM pipe config and request it. */
  retVal = vSwUpdM_Pipe_RequestInternalExitPoint(DataProcessId, Type, Length, &exitPointInfo);

  if (retVal == E_OK)
  {
    /* #20 Get data from exit and acknowledge buffer. */
    for (index = 0u; index < Length; index++)
    {
      /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
      vSwUpdM_RangeInfoReadStreamPtrType buffer = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_RangeInfoType(&exitPointInfo.ReadRequest);
      RangeInfo[index] = buffer[index];
    }

    if (vStreamProc_AcknowledgeExitPoint(vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId), exitPointInfo.ReadRequest.StorageInfo.RequestLength, TRUE, &exitPointInfo) == VSTREAMPROC_OK)
    {
      retVal = E_OK;
    }
    else
    {
      retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_ReadRange */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_ReadProcessOperation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_ReadProcessOperation( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataOutputTypeIterType Type,
  vSwUpdM_ProcNodeOperationPtrType ProcOperation)
{
  vStreamProc_ExitPointInfoType exitPointInfo;
  Std_ReturnType retVal;

  /* #10 Get vStreamProc ExitPoint referred by vSwUpdM pipe config and request it. */
  retVal = vSwUpdM_Pipe_RequestInternalExitPoint(DataProcessId, Type, 1u, &exitPointInfo);

  if (retVal == E_OK)
  {
    /* #20 Get data from exit and acknowledge buffer. */
    P2CONST(vSwUpdM_ProcNodeOperationType, AUTOMATIC, VSWUPDM_APPL_VSTREAMPROC_VAR) buffer = vStreamProc_GetTypedReadRequestBuffer_vSwUpdM_ProcNodeOperationType(&exitPointInfo.ReadRequest);
    (*ProcOperation) = (*buffer);

    if (vStreamProc_AcknowledgeExitPoint(vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId), exitPointInfo.ReadRequest.StorageInfo.RequestLength, TRUE, &exitPointInfo) == VSTREAMPROC_OK)
    {
      retVal = E_OK;
    }
    else
    {
      retVal = VSWUPDM_E_STREAM_OPERATION_FAILED;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_ReadProcessOperation */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetInternalModeIdByType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(vStreamProc_ModeIdType, VSWUPDM_CODE) vSwUpdM_Pipe_GetInternalModeIdByType(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_TypeOfIntModeType Type)
{
  vStreamProc_ModeIdType        modeId = VSTREAMPROC_NO_MODE;
  vSwUpdM_IntDataOutputIterType index;

  for (index = vSwUpdM_GetIntModeStartIdxOfDataProcesses(DataProcessId); index < vSwUpdM_GetIntModeEndIdxOfDataProcesses(DataProcessId); index++)
  {
    if (vSwUpdM_GetTypeOfIntMode(index) == Type)
    {
      modeId = vSwUpdM_GetModeIdOfIntMode(index);

      break;
    }
  }

  return modeId;
} /* vSwUpdM_Pipe_GetInternalModeIdByType */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_UseConfiguredSettings
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_Pipe_UseConfiguredSettings(
 vSwUpdM_ExternalModeIterType ExternalModeIndex,
  vSwUpdM_VarSegmentsPtrType Segment,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds)
{
  vSwUpdM_LengthType           resumeOffset;

  resumeOffset = vSwUpdM_GetExternalModeResumeOffsetOfExternalMode(ExternalModeIndex);

  if (vSwUpdM_IsExternalModeExplicitRestartHandlingRequiredOfExternalMode(ExternalModeIndex) &&
      vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(EntityIds->ModuleId)))
  {
    vSwUpdM_StreamData.RestartHandling = TRUE;
  }

  if (Segment->DynamicAttributesOfVarSegment.ResumeOffset != resumeOffset)
  {
    Segment->DynamicAttributesOfVarSegment.ResumeOffset = resumeOffset;
    Segment->AttributesDirty = TRUE;
  }
} /* vSwUpdM_Pipe_UseConfiguredSettings */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode(
  vSwUpdM_DataProcessesIterType DataProcessId,
  CONST(vStreamProc_ModeIdType, AUTOMATIC) ModeId,
  P2VAR(vSwUpdM_ExternalModeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) ExternalModeIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  vSwUpdM_ExternalModeIterType externalModeIndex;

  for (externalModeIndex = vSwUpdM_GetExternalModeStartIdxOfDataProcesses(DataProcessId);
        externalModeIndex < vSwUpdM_GetExternalModeEndIdxOfDataProcesses(DataProcessId);
        externalModeIndex++)
  {
    if (ModeId == vSwUpdM_GetExternalModeIdOfExternalMode(externalModeIndex))
    {
      (*ExternalModeIndex) = externalModeIndex;
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_GetExtModeIndexByStreamProcMode */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteEntityIds()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteEntityIds(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_EntityIdsReadStreamPtrType EntityIds)
{
  Std_ReturnType retVal;
  vStreamProc_EntryPointInfoType entityEntryInfo;

  /* #10 Request EntityIds entry point. */
  retVal = vSwUpdM_Pipe_RequestInternalEntryPoint(DataProcessId, Type, 1u, &entityEntryInfo);

  if (retVal == E_OK)
  {
    /* #20 Write EntityIds into entry point. */
    /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
    vSwUpdM_EntityIdsPtrType entityIdsBuffer = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_EntityIdsType(&entityEntryInfo.WriteRequest);
    (*entityIdsBuffer) = (*EntityIds);

    /* #30 Acknowledge write. */
    if (vStreamProc_AcknowledgeEntryPoint(
      vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId),
      1u,
      TRUE,
      &entityEntryInfo) != VSTREAMPROC_OK)
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_WriteEntityIds */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteRangeInfo()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteRangeInfo(
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_AddressType RangeAddress,
  vSwUpdM_LengthType RangeLength)
{
  Std_ReturnType retVal;
  vSwUpdM_RangeInfoType rangeInfo;
  vStreamProc_EntryPointInfoType rangeEntryInfo;

  rangeInfo.Address = RangeAddress;
  rangeInfo.Length  = RangeLength;

  /* #10 Request Range entry point. */
  retVal = vSwUpdM_Pipe_RequestInternalEntryPoint(DataProcessId, Type, 1u, &rangeEntryInfo);

  if (retVal == E_OK)
  {
    /* #20 Write range into entry point. */
    /* PRQA S 0310, 3305 1 */ /* MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType */
    vSwUpdM_RangeInfoStreamPtrType rangeInfoBuffer = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_RangeInfoType(&rangeEntryInfo.WriteRequest);
    (*rangeInfoBuffer) = rangeInfo;

    /* #30 Acknowledge write. */
    if (vStreamProc_AcknowledgeEntryPoint(
      vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId),
      1u,
      TRUE,
      &rangeEntryInfo) != VSTREAMPROC_OK)
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_WriteRangeInfo */

/**********************************************************************************************************************
 *  vSwUpdM_Pipe_WriteProcessOperation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Pipe_WriteProcessOperation( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_DataProcessesIterType DataProcessId,
  vSwUpdM_DataInputTypeIterType Type,
  vSwUpdM_ProcNodeOperationType ProcOperation)
{
  Std_ReturnType retVal;
  vStreamProc_EntryPointInfoType operationEntryInfo;

  /* #10 Request Operation entry point. */
  retVal = vSwUpdM_Pipe_RequestInternalEntryPoint(DataProcessId, Type, 1u, &operationEntryInfo);

  if (retVal == E_OK)
  {
    /* #20 Write operation into entry point. */
    vSwUpdM_ProcNodeOperationPtrType operationInfoBuffer = vStreamProc_GetTypedWriteRequestBuffer_vSwUpdM_ProcNodeOperationType(&operationEntryInfo.WriteRequest);
    (*operationInfoBuffer) = ProcOperation;

    /* #30 Acknowledge write. */
    if (vStreamProc_AcknowledgeEntryPoint(
      vSwUpdM_GetPipeIdOfDataProcesses(DataProcessId),
      1u,
      TRUE,
      &operationEntryInfo) != VSTREAMPROC_OK)
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* vSwUpdM_Pipe_WriteProcessOperation */

/**************************************************************
 *  Remote Node Handling
 **************************************************************/

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)

/**********************************************************************************************************************
 * vSwUpdM_RemoteEvalStreamDataRequest
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
 *
 *
 */
FUNC(Std_ReturnType, AUTOMATIC) vSwUpdM_RemoteEvalStreamDataRequest(
  vSwUpdM_NodeGroupIterType RemoteTargetGroup,
  P2VAR(vSwUpdM_GridSrvc_ServiceIdxType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteService,
  P2VAR(vSwUpdM_LengthType, AUTOMATIC, VSWUPDM_APPL_DATA) MinLength)
{
  Std_ReturnType                            retVal            = E_OK;
  uint32                                    nResponses        = 0u;
  Std_ReturnType                            aggregatedResult  = E_OK;
  vSwUpdM_GridSrvc_ServiceIdxType           remoteService     = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
  vSwUpdM_LengthType                        minLength         = VSWUPDM_MAX_LENGTH;
  vSwUpdM_NodeGroup2NodeIndIterType sourceIndIndex;

  /* #100 Iterate over all nodes in given remote target group. */
  for ( sourceIndIndex = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(RemoteTargetGroup);
        sourceIndIndex < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(RemoteTargetGroup);
        sourceIndIndex++ )
  {
    vSwUpdM_NodeIterType sourceIndex = vSwUpdM_GetNodeGroup2NodeInd(sourceIndIndex);

    /* #110 If this entry is the local node
     *   Increment number of responses. */
    if ((vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode() == sourceIndex)
    {
      nResponses++;
    }
    else
    {
      /* #120 If at least one slave has not yet responded
       *   Abort loop. */
      if (!vSwUpdM_IsResponseValidOfVarNode(sourceIndex))
      {
        break;
      }

      /* #130 Report error if no response was expected from current node. */
      if (!vSwUpdM_IsResponseProcessingOfVarNode(sourceIndex))
      {
        retVal = VSWUPDM_E_REMOTE_SERVICE_TARGET_NOT_PROCESSING;
      }
      else
      {
        vSwUpdM_GridSrvc_ServiceIdxType currentService = (vSwUpdM_GridSrvc_ServiceIdxType)  vSwUpdM_GetServiceIdOfResponseOfVarNode(sourceIndex); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */

        /* #140 All responses must refer to the same remote service. */
        if ( (remoteService == VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED)
          || (remoteService == currentService) )
        {
          remoteService = currentService;
        }
        else
        {
          retVal = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;
        }

        /* #150 Evaluation of request is service specific. */
        switch (currentService)
        {
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA:
          /* #200 If response to ProcessStreamData was received. */
          {
            Std_ReturnType currentResult = vSwUpdM_GetResultOfResponseOfVarNode(sourceIndex);

            switch (currentResult)
            {
              case E_OK:
              /* #210 Positive result doesn't change aggregated result. */
              {
                break;
              }
              case VSWUPDM_E_SUSPENDED:
              /* #220 Result indicating suspended operation overrules positive overall result. */
              {
                if (aggregatedResult == E_OK)
                {
                  aggregatedResult = VSWUPDM_E_SUSPENDED;
                }

                break;
              }
              default:
              /* #230 Report first negative result. */
              {
                switch (aggregatedResult)
                {
                  case E_OK:
                  case VSWUPDM_E_SUSPENDED:
                  {
                    aggregatedResult = currentResult;
                    break;
                  }
                  default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
                  {
                    break;
                  }
                }

                break;
              }
            }

            break;
          }
          case VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA:
          /* #300 If CopyStreamData request was received. */
          {
            /* #310 Evaluate minimum length requested by all nodes. */
            if (vSwUpdM_GetLengthOfResponseOfVarNode(sourceIndex) < minLength)
            {
              minLength = vSwUpdM_GetLengthOfResponseOfVarNode(sourceIndex);
            }

            break;
          }
          default:
          /* #400 Otherwise: Report error. */
          {
            retVal = VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE;

            break;
          }
        }

        /* #500 Increment number of responses if no error was detected. */
        if (retVal == E_OK)
        {
          vSwUpdM_SetResponseProcessingOfVarNode(sourceIndex, FALSE);
          nResponses++;
        }
      }
    }
  }

  /* #600 If all slaves have sent a valid response */
  if (retVal == E_OK)
  {
    if (nResponses == vSwUpdM_GetNNodesOfNodeGroup(RemoteTargetGroup))
    {
      /* #610 Conclude response processing. */
      if (aggregatedResult == VSWUPDM_E_SUSPENDED)
      {
        vSwUpdM_RemoteConcludeResponses(RemoteTargetGroup, TRUE);
      }
      else
      {
        vSwUpdM_RemoteConcludeResponses(RemoteTargetGroup, FALSE);
      }

      /* #611 Return aggregated result. */
      retVal          = aggregatedResult;
      *RemoteService  = remoteService;
      *MinLength      = minLength;
    }
    /* #620 Otherwise: Indicate pending operation. */
    else
    {
      retVal = VSWUPDM_E_PENDING;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_RemoteEvalStreamDataRequest */
#endif /* VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON */

/**************************************************************
 *  Internal API:
 * - Stream
 **************************************************************/

/**************************************************************
 *  Service Dispatching
 **************************************************************/
/**************************************************************
 *  Callout handling
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BookkeeperHandler
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BookkeeperHandler(
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_OpStatusType State,
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds)
{
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType persistResult = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean suppress = FALSE;

  if (Operation == VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CALLOUT_INIT)
  {
    result = vSwUpdM_Appl_Init(State);
  }
  else
  {
    /* #20 If this is the initial request: */
    if (State == VSWUPDM_OP_STATUS_INITIAL)
    {
      /* #100 Check owner of entity for module and region set-requests.
       *      Requests for remote entities shall be suppressed.
       */

      switch (Operation)
      {
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_STATE:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_VALID:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_REVISION:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_PROGRAMMING_ATTEMPTS:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_ATTRIBUTES:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_WRITE_ADDRESS:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_COUNT:
        {
          /* If the local node is not a owner of the given module:
           * Suppress Set() request. */
          if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfModule(EntityIds->ModuleId)))
          {
            suppress = TRUE;
          }

          break;
        }
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_STATE:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_PROGRAMMING_ATTEMPTS:
        case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_ERASE_ADDRESS:
        {
          /* If the local node is not a owner of the given region:
           * Suppress Set() request. */
          if (!vSwUpdM_IsWithLocalNodeOfNodeGroup(vSwUpdM_GetNodeGroupOwnersIdxOfRegion(EntityIds->RegionId)))
          {
            suppress = TRUE;
          }

          break;
        }
        default:
        {
          suppress = FALSE;
          break;
        }
      }

      /* #200 If setter request shall be suppressed, skip further processing and return OK */
      if (suppress == TRUE)
      {
        result = E_OK;
      }
      else
      /* #300 Else: */
      {
        /* #310 Execute operation. */
        switch (Operation)
        {
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE:
          /* #410 If no operation is requested, nothing to be done. */
          {
            /* result = E_OK; */
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_OPEN_LOCAL:
          /* #420 Open bookeeper connection (local). */
          {
            persistResult = vSwUpdM_Bookkeeper_Open(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupLocal(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX));
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_OPEN:
          /* #430 Open bookeeper connection (remote). */
          {
            persistResult = vSwUpdM_Bookkeeper_Open(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupRemote(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX));
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CLOSE_LOCAL:
          /* #440 Close bookeeper connection (local). */
          {
            persistResult = vSwUpdM_Bookkeeper_Close(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupLocal(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX));
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_CLOSE:
          /* #450 Close bookeeper connection (remote). */
          {
            persistResult = vSwUpdM_Bookkeeper_Close(vSwUpdM_GetNodeGroupIdxOfAllPersistorServerGroupRemote(VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX));
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_UPDATE_STATE:
          /* #460 Trigger bookkeeper to get the update state, if requested. */
          {
            /* PRQA S 0315 2 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE,
                                                   sizeof(vSwUpdM_UpdateState), &vSwUpdM_UpdateState);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_UPDATE_STATE:
          /* #470 Trigger bookkeeper to set the update state, if requested. */
          {
            /* PRQA S 0315 1 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE, sizeof(vSwUpdM_UpdateState), &vSwUpdM_UpdateState);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_STATE:
          /* #480 Trigger bookkeeper to get the state of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
          persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE,
                                                 sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.State),
                                                 &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_STATE:
          /* #490 Trigger bookkeeper to set the state of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE,
                                                   sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.State),
                                                   &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_VALID:
          /* #500 Trigger bookkeeper to get the validity of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY,
                                                   sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.IsValid),
                                                   &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.IsValid);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_VALID:
          /* #510 Trigger bookkeeper to set the validity of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY,
                                                   sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.IsValid),
                                                   &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.IsValid);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_PARTITION_REVISION:
          /* #520 Trigger bookkeeper to get the revision of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION,
                                                   sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.Revision),
                                                   &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).DynamicAttributesOfVarPartitions.Revision);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_PARTITION_REVISION:
          /* #530 Trigger bookkeeper to set the revision of the given partition, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION,
                                                   sizeof(vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.Revision),
                                                   &vSwUpdM_GetVarPartitions(EntityIds->PartitionId).PendingAttributesOfVarPartitions.Revision);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_STATE:
          /* #540 Trigger bookkeeper to get the state of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_STATE,
                                                   sizeof(vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].State),
                                                   &vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_STATE:
          /* #550 Trigger bookkeeper to set the state of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_STATE,
                                                   sizeof(vSwUpdM_ModulePendingAttributes.Attributes.State),
                                                   &vSwUpdM_ModulePendingAttributes.Attributes.State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_VALID:
          /* #560 Trigger bookkeeper to get the validity of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY,
                                                   sizeof(vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].IsValid),
                                                   &vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].IsValid);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_VALID:
          /* #570 Trigger bookkeeper to set the validity of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY,
                                                   sizeof(vSwUpdM_ModulePendingAttributes.Attributes.IsValid),
                                                   &vSwUpdM_ModulePendingAttributes.Attributes.IsValid);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_REVISION:
          /* #580 Trigger bookkeeper to get the revision of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION,
                                                   sizeof(vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].Revision),
                                                   &vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].Revision);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_REVISION:
          /* #590 Trigger bookkeeper to set the revision of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION,
                                                   sizeof(vSwUpdM_ModulePendingAttributes.Attributes.Revision),
                                                   &vSwUpdM_ModulePendingAttributes.Attributes.Revision);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_MODULE_PROGRAMMING_ATTEMPTS:
          /* #600 Trigger bookkeeper to get the programming attempt counter of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS,
                                                   sizeof(vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].ProgrammingAttempts),
                                                   &vSwUpdM_GetVarModules(EntityIds->ModuleId).DynamicAttributesOfVarModules[EntityIds->PartitionIdx].ProgrammingAttempts);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_MODULE_PROGRAMMING_ATTEMPTS:
          /* #610 Trigger bookkeeper to set the programming attempt counter of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS,
                                                   sizeof(vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts),
                                                   &vSwUpdM_ModulePendingAttributes.Attributes.ProgrammingAttempts);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_STATE:
          /* #620 Trigger bookkeeper to get the state of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_STATE,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).DynamicAttributesOfVarRegion.State),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).DynamicAttributesOfVarRegion.State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_STATE:
          /* #630 Trigger bookkeeper to set the state of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_STATE,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.State),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.State);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_PROGRAMMING_ATTEMPTS:
          /* #640 Trigger bookkeeper to get the programming attempt counter of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).DynamicAttributesOfVarRegion.ProgrammingAttempts),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).DynamicAttributesOfVarRegion.ProgrammingAttempts);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_PROGRAMMING_ATTEMPTS:
          /* #650 Trigger bookkeeper to set the programming attempt counter of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.ProgrammingAttempts),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).PendingAttributesOfVarRegion.ProgrammingAttempts);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_REGION_ERASE_ADDRESS:
          /* #660 Trigger bookkeeper to get the erase address of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).EraseAddressOfVarRegion),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).EraseAddressOfVarRegion);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_REGION_ERASE_ADDRESS:
          /* #670 Trigger bookkeeper to set the erase address of the given region instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS,
                                                   sizeof(vSwUpdM_GetVarRegions(EntityIds->RegionIdx).EraseAddressOfVarRegion),
                                                   &vSwUpdM_GetVarRegions(EntityIds->RegionIdx).EraseAddressOfVarRegion);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_COUNT:
          /* #680 Trigger bookkeeper to get the segment count of the given module instance, if requested. */
          {
            /* PRQA S 0315 2 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT,
                                                   sizeof(vSwUpdM_SegmentPendingCount), &vSwUpdM_SegmentPendingCount);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_COUNT:
          /* #690 Trigger bookkeeper to set the segment count of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT,
                                                   sizeof(vSwUpdM_EntityData.Count.ExternalSegmentCount),
                                                   &vSwUpdM_EntityData.Count.ExternalSegmentCount);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_ATTRIBUTES:
          /* #700 Trigger bookkeeper to get the attributes of the given segment of the given module instance, if requested. */
          {
            /* PRQA S 0315 2 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES,
                                                   sizeof(vSwUpdM_SegmentPendingAttributes), &vSwUpdM_SegmentPendingAttributes);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_ATTRIBUTES:
          /* #710 Trigger bookkeeper to set the attributes of the given segment of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES,
                                                   sizeof(vSwUpdM_SegmentPendingAttributes),
                                                   &vSwUpdM_SegmentPendingAttributes);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_SEGMENT_WRITE_ADDRESS:
          /* #720 Trigger bookkeeper to get the write address of the given segment of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS,
                                                   sizeof(vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteAddressOfVarSegments),
                                                   &vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteAddressOfVarSegments);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_WRITE_ADDRESS:
          /* #730 Trigger bookkeeper to set the write address of the given segment of the given module instance, if requested. */
          {
            /* PRQA S 0315 3 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS,
                                                   sizeof(vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteAddressOfVarSegments),
                                                   &vSwUpdM_GetVarSegments(EntityIds->SegmentId.DynamicSegmentId).WriteAddressOfVarSegments);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_GET_RESUME_INFO:
          /* #740 Trigger bookkeeper to get the resume information, if requested. */
          {
            /* PRQA S 0315 2 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Get(EntityIds, VSWUPDM_BKPERSIST_PARAM_RESUME_INFO,
                                                   sizeof(vSwUpdM_ResumeInfo), &vSwUpdM_ResumeInfo);
            break;
          }
          case VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_RESUME_INFO:
          /* #750 Trigger bookkeeper to set the resume information, if requested. */
          {
            /* PRQA S 0315 2 */ /* MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr */
            persistResult = vSwUpdM_Bookkeeper_Set(EntityIds, VSWUPDM_BKPERSIST_PARAM_RESUME_INFO,
                                                   sizeof(vSwUpdM_PendingResumeInfo), &vSwUpdM_PendingResumeInfo);
            break;
          }
          default:
          /* #800 Otherwise: Unknown operation, report error. */
          {
            /* result = E_NOT_OK; */

            break;
          }
        }

        /* #900 Cause initial persist scheduler call (if necessary) and trigger sync. */
        if (persistResult == E_OK)
        {
          (void)vSwUpdM_Bookkeeper_ClientExecute();
          /* #910 Force sync. */
          vSwUpdM_Bookkeeper_Sync();
          result = VSWUPDM_E_PENDING;
        }
        else
        {
          /* persistResult can be E_NOT_OK because: */
          if (Operation == VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_NONE)
          {
            /* .. nothing was done and it still has the initial value. */
            result = E_OK;
          }
          else
          {
            /* .. result was negative. */
            result = E_NOT_OK;
          }
        }
      }
    }
    else
    /* #1000 Else:
     *      Schedule request.*/
    {
      /* #1010 Wait for operation to be finished. */
      result = vSwUpdM_Bookkeeper_ClientExecute();
    }
  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_BookkeeperHandler */

/*!
 * Internal comment removed.
 *
 *
 */
/**********************************************************************************************************************
 * vSwUpdM_Job_TriggerBookkeeper
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
 */
FUNC(vSwUpdM_JobStatusType, VSWUPDM_CODE) vSwUpdM_Job_TriggerBookkeeper(
  vSwUpdM_JobOperationType Operation,
  vSwUpdM_JobPtrType ParentJob)
{
  vSwUpdM_JobStatusType retVal          = VSWUPDM_JOB_STATUS_ACTIVE;
  vSwUpdM_JobStateType  bookkeeperState = VSWUPDM_JOB_STATE_FINAL;
  Std_ReturnType        bookkeeperResult = E_OK;
  boolean               executeCallout  = TRUE;

  if ( (Operation == VSWUPDM_JOB_OPERATION_WAIT_BOOKKEEPER_SET_SEGMENT_ATTRIBUTES)
    && (ParentJob->EntityIds.SegmentIdx == VSWUPDM_INVALID_ID) )
  {
    executeCallout = FALSE;
  }

  if (executeCallout == TRUE)
  {
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# if (VSWUPDM_LOCALINSTANCE_ACTS_AS_SLAVE == STD_ON)
    /* If addressed via remote interface */
    if (vSwUpdM_Grid_LocalNodeIsChild() == TRUE)
    {
      /* Transmit to Bookkeeper of the initial request */
      if (E_OK != vSwUpdM_RemoteBookkeeperRequest(vSwUpdM_RemoteLockIsGrantedTo, Operation, &ParentJob->EntityIds, ParentJob))
      {
        bookkeeperResult = E_NOT_OK;
      }
    }

    if (bookkeeperResult == E_OK)
# endif
#endif
    {
      /* #10 Initial trigger for bookkeeper. */
      bookkeeperResult = vSwUpdM_BookkeeperHandler(Operation, VSWUPDM_OP_STATUS_INITIAL, &ParentJob->EntityIds);
    }
  }

  /* #20 Evaluate result. */
  switch (bookkeeperResult)
  {
    case VSWUPDM_E_PENDING:
    /* #21 If callout accepted request, but the result is pending, set state for next call to "pending". */
    {
      bookkeeperState = VSWUPDM_JOB_STATE_PENDING;

      break;
    }
    case VSWUPDM_E_BUSY:
    /* #22 If callout didn't accept the request yet, because it is busy, set state for next call to "initial". */
    {
      bookkeeperState = VSWUPDM_JOB_STATE_INITIAL;

      break;
    }
    default:
    /* #30 Otherwise */
    {
      /* #31 If bookkeeper returned any other negative result, overwrite result with "callout failed" error. */
      if (bookkeeperResult != E_OK)
      {
        bookkeeperResult = VSWUPDM_E_CALLOUT_FAILED;
      }

      /* #32 Update child result of parent job. */
      vSwUpdM_Job_SetChildResult(ParentJob, bookkeeperResult, VSWUPDM_UNDEFINED_ADDRESS);

      break;
    }
  }

  /* #100 Evaluate state of bookkeeper operation. */
  switch (bookkeeperState)
  {
    case VSWUPDM_JOB_STATE_INITIAL:
    case VSWUPDM_JOB_STATE_PENDING:
    /* #110 If operation wasn't started yet or is still pending */
    {
      vSwUpdM_JobPtrType    spawnedJob;
      Std_ReturnType        spawnResult;

      /* #120 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #130 Spawn job to wait for bookkeeper operation to finish. */
      spawnedJob = vSwUpdM_Job_Spawn(&spawnResult, VSWUPDM_JOB_TYPE_WAIT_FOR_BOOKKEEPER_OPERATION, Operation, ParentJob->CurrentPrio + 1u, VSWUPDM_SID_NONE, ParentJob, ParentJob->Source);

      /* #140 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
      if (spawnResult == E_OK)
      {
        spawnedJob->EntityIds = ParentJob->EntityIds;
        spawnedJob->State     = bookkeeperState;

        retVal = VSWUPDM_JOB_STATUS_PENDING;
      }

      /* #150 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      break;
    }
    default:
    /* #200 Otherwise: Nothing more to do, as bookkeeper already finished on first call. */
    {
      break;
    }
  }

  return retVal;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_Job_TriggerBookkeeper */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

  MD_vSwUpdM_Rule11.3_0310_3305_PipeAccessBufferType:
    Reason:     Cast is necessary to convert generic byte buffer pointer to type-specific pointer.
    Risk:       Alignment issues may occur.
    Prevention: Access function compare expected type against type of generated buffer. Internal buffer handling
                inside of vStreamProc ensures correct alignment.

  MD_vSwUpdM_Rule11.5_0311_RemoteBufferConstConfigValues:
    Reason:     Constant configuration values are passed to the remote node. Constant data is handled
                the same way as runtime data.
    Risk:       No risk (data has to be loaded to RAM buffer anyway for transmission).
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule11.5_0311_WriteBufferConstCast:
    Reason:     Input data for write (or remote write) operation is passed to the processing job. The job handling
                does not differ between input (const) and output buffers, therefore, a cast to non-cast is required.
    Risk:       Data could be altered unexpectedly.
    Prevention: The written data is verified after a successful download.

  MD_vSwUpdM_Dir1.1_0315_TypedPtrVoidPtr:
    Reason:     vMemAccM functions expect untyped void pointers for user buffers.
    Risk:       No risk. Underlying uint8 pointer type is known.
    Prevention: Component tests ensures that the vMemAccM forwards and accesses the RAM buffers correctly.

  MD_vSwUpdM_Rule11.5_0316_VoidPtrTypedPtr:
    Reason:     External processing nodes use void pointers to provide buffer space.
    Risk:       No risk. Underlying uint8 pointer type is known.
    Prevention: Component tests ensures that the RAM buffers are correctly accessed.

  MD_vSwUpdM_Rule11.5_0316_PersistCastPtrVoidPtrObj:
    Reason:     PersistClient uses generic interface for different datatypes.
    Risk:       No risk. Underlying pointer type is known.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule2.1_3219_PublicInline:
    Reason:     A unit provides a functionality to be inlined in the using code.
                This is done to help the compiler produce efficient code while functionality is properly mapped.
                Not all provided inline functionality is necessarily used where the interface is included.
    Risk:       No risk, because inline functionality does not produce object code when it is not invoked.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule10.5_4304_PassingBooleanValue:
    Reason:     A boolean expression is passed through a function interface as a parameter or return value.
                So the result is cast to a numeric value.
    Risk:       The cast of a boolean to a numeric value is implementation defined, so the passed value could be misinterpreted.
    Prevention: Review of affected code parts.

  MD_vSwUpdM_Rule10.5_4342_EnumParameterCast:
    Reason:     An internally used index is defined as enum type. The value of the index is passed via a remote
                communication interface. It is casted to a integral data type for transmission and back again
                on the remote side.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization:
    Reason:     Variable is initialized with a default value, although will be overwritten with another value
                for all cases where it is actually used.
                This is done to prevent compiler warnings about the use of possibly uninitialized variables.
    Risk:       Risk of misinterpretation of erroneous values, e.g. by range overflow.
    Prevention: Value is checked for validity.

  MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse:
    Reason:     Condition is always true or false. Function used to evaluate condition is currently hard-coded to
                a specific value.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule8.9_3218_FileScope:
    Reason:     The local variables and constants buffers of this module are kept at a central location for a better
                overview and maintenance.
    Risk:       Scope is larger than required (whole file instead of one function). Some other function could access
                the variable or constant.
    Prevention: Restrict the functionality in this module to the intended purpose. Don't add functions which shall not
                be able to access the local data buffers.

  MD_vSwUpdM_Rule8.11_3684_ConfigStructure:
    Reason:     The unspecific declaration has been used to ease manual configuration. Entries can be added to or
                removed from the configuration structure without having to adapt the number of entries afterwards.
    Risk:       Out-of-bounds access.
    Prevention: Actual number of entries is provided as automatically calculated constant value, or the array
                contains an end marker to allow a safe search.

  MD_vSwUpdM_Rule8.12_0724_EnumCountEqualsInvalid:
    Reason:     An enumerated type shall contain values for "ZERO" and "COUNT" in order to properly iterate all values.
                It shall further contain an explicit value for "INVALID". Because "COUNT" is not a valid value as well,
                "COUNT" and "INVALID" are represented by the same numeric value, while there is a semantic difference
                when used.
    Risk:       Values are used incorrectly or misinterpreted.
    Prevention: Naming has been chosen to avoid unclear use. "ZERO" and "COUNT" are for iteration purpose, while
                "INVALID" stands for "not a valid value". This results in a clear code semantics.

  MD_vSwUpdM_Rule18.1_2841_DereferenceOfInvalidPointerPostbuildStuctures:
    Reason:     To enable Postbuild Configuration, arrays of variable sizes - including size zero - are required here.
                Depending on the configuration, appropriate data structures and access macros are generated.
    Risk:       Potential out-of-bounds access on wrong usage.
    Prevention: Assertions check for invalid indices, usage is reviewed thoroughly.

  MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter:
    Reason:     A pointer parameter is not qualified as pointer-to-const although the value is not modified.
                The interface belongs to a group of interfaces (unit), where some do modify the value.
                In order to provide a unique interface throughout a unit, none of the pointers are const qualified.
    Risk:       Less precision in describing access rights on interface level may lead to incorrect use of the parameters.
    Prevention: The interface design documents allowed parameter usage in the code. Review and test are done against this
                documentation.

  MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData:
    Reason:     A pointer is not qualified as pointer-to-const although the value is not modified.
                The data that is pointed to is modifiable and public, so a modification would be permitted.
                Declaring a pointer-to-const would reduce maintainability as it would reject intended data modification.
    Risk:       Data is modified accidentally.
    Prevention: Modification of the data is allowed if intended. The intention of added and existing code parts will be
                reviewed.

  MD_vSwUpdM_2853_InitializationChecked:
    Reason:     A value is initialized by a subroutine through pointer. Only if return value indicates that
                this was successful, the value is further used. The message is a false positive.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_2933_PointerCalculatedFromCheckedInitialization:
    Reason:     A value that was initialized by a subroutine through pointer is used to calculate a pointer to
                an array element. Although the return value of the initialization was checked, the analysis suspects
                an invalid calculation of the pointer. The message is a false positive.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_2963_InitializationChecked:
    Reason:     The value is initialized by a subroutine through pointer. Return value was checked to ensure initialization
                was performed. The message is a false positive.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule10.1_4527_EnumLoop:
    Reason:     A loop handles all valid values of an enumerated type.
    Risk:       Values outside the enum scope are calculated.
    Prevention: The enumerated type contains additional values for "ZERO" and "COUNT", which are used for loop
                control. All values in between are consecutive.

  MD_vSwUpdM_Rule2.1_3219_PublicInline:
    Reason:     A unit provides a functionality to be inlined in the using code.
                This is done to help the compiler produce efficient code while functionality is properly mapped.
                Not all provided inline functionality is necessarily used where the interface is included.
    Risk:       No risk, because inline functionality does not produce object code when it is not invoked.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule2.1_3219_RpcProxyRedirect:
    Reason:     A unit provides a functionality to be used depending on selected configuration
                This is done to provide a complete interface for unit testing.
    Risk:       No risk, because unused functions will be optimized away by the linker or will be at least not used.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization:
    Reason:     Variable is initialized with a default value, although will be overwritten with another value
                for all cases where it is actually used.
                This is done to prevent compiler warnings about the use of possibly uninitialized variables.
    Risk:       No risk.
    Prevention: No prevention necessary.

  MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast:
    Reason:     For efficient handling of RPC, the parameters are propagated encapsulated in a struct. On access,
                they are unpacked (cast to original type) again. This allows to handle different kind of
                parameter sets to be handled by the same functions.
    Risk:       Different data type might be used for packing/unpacking.
    Prevention: The data type is checked (Assertion) before unpacking. The struct contains a member identifying
                the used data type.
*/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM.c
 *********************************************************************************************************************/
