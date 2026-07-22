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
/*!        \file  vSwUpdM_Services_If.h
 *        \brief  vSwUpdM_Services interface header file
 *      \details  Interface provided by the vSwUpdM_Services subcomponent.
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

#if !defined (VSWUPDM_SERVICES_IF_H)
# define VSWUPDM_SERVICES_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Services types header */
#include "vSwUpdM_Services_Types.h"

/* Interface header of Component */
#include "vSwUpdM.h"

/* Other MultipleUnits used by Services_If (Prefer smallest set required, i.e. prefer _Types over _If) */
#include "vSwUpdM_Priv_Types.h"
#include "vSwUpdM_ExecCtrl_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_IsRequestResumePending()
 *********************************************************************************************************************/
/*! \brief       Check if a resume- request for a (suspended) service is expected.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_SrvcRouting_IsRequestResumePending(void);

/**********************************************************************************************************************
 * vSwUpdM_Internal_StartStream
 *********************************************************************************************************************/
/*! \brief      Initializes a download stream.
 *  \details     Notifies the vSwUpdM that a download sequence is started.
 *  \param[in]   StreamInfo    The information about the initialized download sequence.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A module has to be opened prior.
 *  \note        The length specified in StreamInfo is interpreted as not defined if set to 0 (VSWUPDM_UNDEFINED).
 *               Otherwise, it is expected that exactly this length is downloaded within the current download
 *               sequence.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_StartStream(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 * vSwUpdM_Internal_ProcessStreamData
 *********************************************************************************************************************/
/*! \brief      Notifies the vSwUpdM about new data.
 *  \details     Requests that the vSwUpdM collects the data from upper layer as soon as possible.
 *  \param[in]   StreamLength  The number of bytes currently available in the upper layer to download.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The requested data length is accepted.
 *  \return      E_NOT_OK      The requested data length is invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A stream has to be started prior.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ProcessStreamData(
  vSwUpdM_StreamLengthType StreamLength,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 * vSwUpdM_Internal_EndStream
 *********************************************************************************************************************/
/*! \brief       Ends a download sequence.
 *  \details     Notifies the vSwUpdM that a download sequence is ended.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The requested data length is accepted.
 *  \return      E_NOT_OK      The requested data length is invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A stream has to be started prior.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EndStream(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ValidatePartition()
 *********************************************************************************************************************/
/*! \brief       Validates the opened partition.
 *  \details     Sets the whole partition to valid.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         Allowed on inactive or backup target partition. All corresponding modules must also be valid.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ValidatePartition(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_InvalidatePartition()
 *********************************************************************************************************************/
/*! \brief       Invalidates the opened partition.
 *  \details     Sets the whole partition to invalid. Afterwards the whole partition has to be erased and re-written
 *               before activation is possible. Invalidates all corresponding modules.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_InvalidatePartition(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SyncPartition()
 *********************************************************************************************************************/
/*! \brief       Synchronizes the opened partitions.
 *  \details     Copies data from active and swappable partition to the opened partition.
 *               Typically the opened partition is either the inactive partition (take over modules which weren't updated)
 *               or the backup target (creation of backup of active software).
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SyncPartition(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CheckPartitionConsistency()
 *********************************************************************************************************************/
/*! \brief       Verify partition and checks the consistency of the opened partition.
 *  \details     A partition has to be consistent before it is swapped to active.
 *  \param[in]   ProcessInfo    Verify information.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \note        This check is only useful for inactive or backup partitions.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CheckPartitionConsistency(
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SwapActivePartition()
 *********************************************************************************************************************/
/*! \brief       Requests a swap from currently active partition to opened partition.
 *  \details     Module instances in opened partition will be active after next restart.
 *               The opened partition can be
 *               - The inactive partition: Activate newly updated software.
 *               - The backup source: Perform rollback to earlier software version.
 *               - The active partition: Early rollback, when activation was requested, but not performed yet.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SwapActivePartition(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_OpenPartition()
 *********************************************************************************************************************/
/*! \brief       Opens the specified partition.
 *  \details     All following operations to modules, regions, segments and ranges are based on the opened partition.
 *  \param[in]   State         The state of the partition to be opened.
 *  \param[in]   Source        The source node of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         All operations on the prior opened partitions must be finished.
 *  \note        There is always an open partition, therefore there is no API for closing a partition. The closing is
 *               performed implicitly during opening a new partition.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenPartition(
  vSwUpdM_PartitionStateType State,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_OpenModule()
 *********************************************************************************************************************/
/*! \brief       Opens the specified module.
 *  \details     Notify the vSwUpdM to which module the following region, segment and stream specific commands
 *               are assigned to.
 *  \param[in]   Id            The module to be opened.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         All modules must be closed.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CloseModule()
 *********************************************************************************************************************/
/*! \brief      Closes the specified module.
 *  \details     After closing write access to this module is not allowed anymore.
 *  \param[in]   Id            The identifier of the module.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         The specified module has to be opened prior. All requests on this module have to be finished prior.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CloseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ValidateModule()
 *********************************************************************************************************************/
/*! \brief      Validates the specified module.
 *  \details     Sets the module to valid.
 *  \param[in]   Id            The module to be validated.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ValidateModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_InvalidateModule()
 *********************************************************************************************************************/
/*! \brief      Invalidates the specified module.
 *  \details     An invalidated module must be erased and re-written before using again.
 *  \param[in]   Id            The module to be invalidated.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_InvalidateModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_EraseModule()
 *********************************************************************************************************************/
/*! \brief      Erases memory of all regions mapped to the specified module.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EraseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_FinalizeModule()
 *********************************************************************************************************************/
/*! \brief      Finalize module by filling all memory not written yet with pattern.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_FinalizeModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_VerifyModule()
 *********************************************************************************************************************/
/*! \brief      Verify module by triggering verification actions and collect results.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \param[in]   ProcessInfo   Verify information.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_VerifyModule(
  vSwUpdM_ModuleIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ProcessModule()
 *********************************************************************************************************************/
/*! \brief      Cause spawning a job, which processing a stream processor pipe of scope module.
 *  \details     -
 *  \param[in]   ModuleId      The id of the module.
 *  \param[in]   ProcessId     The id of the process (refers to a stream processor pipe).
 *  \param[in]   ProcessInfo   Additional information for the process.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          Process successfully finished.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ProcessModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SyncModule()
 *********************************************************************************************************************/
/*! \brief      Synchronizes the specified module.
 *  \details     The content of the active module is copied to the instance in the opened partition.
 *  \param[in]   Id            The module to be synchronized.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SyncModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_IndicateWriteToModule()
 *********************************************************************************************************************/
/*! \brief       Indicate that the module contents are going to be modified outside of the normal update sequence.
 *  \details     State of module and all of the assigned regions is changed from "erased" to "clean".
 *  \param[in]   ModuleId      The id of the module.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         Module and assigned regions are either in state "erased" or "clean".
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_IndicateWriteToModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_Start()
 *********************************************************************************************************************/
/*! \brief      Request the start of the download sequence.
 *  \details     Confirmation will be issued as soon as background initialization is finished and download sequence
 *               can begin.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Start(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 * vSwUpdM_Internal_Shutdown
 *********************************************************************************************************************/
/*! \brief      Suspend the download sequence and persist current state.
 *  \details     After restart, either after a reset or re-issuing vSwUpdM_Start(), the download can be resumed at the
 *               current position, e.g. last written memory page.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Shutdown(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 * vSwUpdM_Internal_Suspend
 *********************************************************************************************************************/
/*! \brief       Suspends a currently active download sequence.
 *  \details     The operation can be resumed later. The suspended state isn't persisted to resume after a reset, but
 *               a shutdown can be requested while being suspended.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         An operation must be pending or vSwUpdM must be idle.
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Suspend(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_EraseRegion()
 *********************************************************************************************************************/
/*! \brief      Erases memory of all segments mapped to the specified region.
 *  \details     The region is identified by the specified handle id.
 *  \param[in]   Id            The identifier of the region.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EraseRegion(
  vSwUpdM_RegionIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_OpenSegment()
 *********************************************************************************************************************/
/*! \brief      Opens the specified segment.
 *  \details     An opened segment can be written to.
 *  \param[in]   Id            The identifier of the segment.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CloseSegment()
 *********************************************************************************************************************/
/*! \brief      Closes the specified segment.
 *  \details     After closing write access to this segment is not allowed anymore.
 *  \param[in]   Id            The identifier of the segment.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CloseSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_AddSegment()
 *********************************************************************************************************************/
/*! \brief      Adds a segment to the covering region corresponding to the specified range.
 *  \details     -
 *  \param[in,out] SegmentInfo The segment info containing the range of the segment.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The creation succeeded.
 *  \return      E_NOT_OK      The creation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
/* NOTE: Pointer class referenced by P2VAR macro should be VSWUPDM_APPL_VAR. */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_AddFinalizedSegment()
 *********************************************************************************************************************/
/*! \brief       Adds a segment to the covering region corresponding to the specified range.
 *  \details     Segment will be added in state "finalized".
 *  \param[in,out] SegmentInfo The segment info containing the range of the segment.
 *  \return      E_OK          The creation succeeded.
 *  \return      E_NOT_OK      The creation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module and region to which the segment is added must be in state "clean".
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_AddFinalizedSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_FinalizeSegment()
 *********************************************************************************************************************/
/*! \brief      Finalize segment by writing any remainder.
 *  \details     -
 *  \param[in]   Id            The id of the segment.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_FinalizeSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_VerifySegment()
 *********************************************************************************************************************/
/*! \brief      Verify segment by triggering verification actions and collect results.
 *  \details     The segment is identified by the specified handle id.
 *  \param[in]   Id            The id of the segment.
 *  \param[in]   ProcessInfo   Verify information.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_VerifySegment(vSwUpdM_SegmentIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ClearSegmentsOfModule()
 *********************************************************************************************************************/
/*! \brief      Clears content of all segments assigned to the specified module.
 *  \details     -
 *  \param[in]   ModuleId      The module id of which all segments are cleared.
 *  \param[in]   Source        The source of the request.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ClearSegmentsOfModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_RemoteCallPostHandler()
 *********************************************************************************************************************/
/*! \brief       Handles the results of a remote request.
 *  \details     Transmits a immediate response on a remote request if required.
 *               A immediate response is required if
 *                 (A) the initial request could not processed because of a wrong parameter value or invalid state
 *                 (B) the processing of the request will not trigger a response.
 *               If the source of the initial request is unknown, no response is sent.
 *  \param[in]   Result               Result of the processing of the initial request
 *  \param[in]   SourceIndex          Source of the initial request
 *  \param[in]   NegativeResponseOnly TRUE  = Case (A) only transmit a response if Result is not E_OK.
 *                                    FALSE = Case (B) always transmit a response.
 *  \param[in]   ServiceIndex         The service for which a response shall be sent.
 *  \param[in]   SourceIndexIsValid   Source of the initial request is known (TRUE) or unknown (FALSE).
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteCallPostHandler(
  Std_ReturnType Result,
  vSwUpdM_NodeIterType SourceIndex,
  boolean NegativeResponseOnly,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  boolean SourceIndexIsValid);

/**********************************************************************************************************************
 *  vSwUpdM_Init_InitPipelinedProgramming()
 *********************************************************************************************************************/
/*! \brief       Initializes the pipelined programming with default values.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Init_InitPipelinedProgramming(void);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_GetNumberOfPendingResponses()
 *********************************************************************************************************************/
/*! \brief       Get the number of pending responses.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(uint8, VSWUPDM_CODE) vSwUpdM_SrvcRouting_GetNumberOfPendingResponses(void);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_StartStream
 *********************************************************************************************************************/
/*! \brief vRpcProxy receive callout function for StartStream call.
 *  \details     -
 *  \param[in]   Source        Stream source node index.
 *  \param[in]   ServiceState  Scheduling state of service.
 *  \param[in]   StreamInfo    Stream meta data.
 *  \return      E_OK          Stream was started successfully.
 *  \return      E_NOT_OK      Stream was not started.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_StartStream(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_DATA)StreamInfo);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteProcessStreamData
 *********************************************************************************************************************/
/*! \brief Handle ProcessStreamData remote call.
 *  \details     -
 *  \param[in]   Source        Stream source node index.
 *  \param[in]   ServiceState  Indicates if service is triggered initially or shall be resumed.
 *  \param[in]   StreamLength  Length of stream.
 *  \return      E_OK          Stream was started successfully.
 *  \return      else          Stream was not started.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteProcessStreamData(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_LengthType StreamLength);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData
 *********************************************************************************************************************/
/*! \brief Handle RemoteResponseCopyStreamData remote call.
 *  \details     -
 *  \param[in]   Source               Stream source node index.
 *  \param[in]   StreamBuffer         Pointer to stream data.
 *  \param[in]   StreamBuffer_Length  Size of stream buffer.
 *  \param[in]   AvailableLength      Amount of data in stream.
 *  \return      E_OK                 Copied stream data successfully.
 *  \return      else                 Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData(
  vSwUpdM_NodeIterType Source,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  vSwUpdM_LengthType StreamBuffer_Length,
  vSwUpdM_LengthType AvailableLength);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamStart
 *********************************************************************************************************************/
/*! \brief Handle RemoteStreamStart remote call.
 *  \details     -
 *  \param[in]   sourceHandleId  Source of the request.
 *  \param[in]   ProcessHandle   Handle of DataProcess.
 *  \param[in]   Handle          Handle of RemoteStream.
 *  \param[in]   AvailableLength Available length of data.
 *  \return      E_OK            Stream started successfully.
 *  \return      else            Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamStart(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_LengthType AvailableLength);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamCopy
 *********************************************************************************************************************/
/*! \brief Handle remote RemoteStreamCopy call.
 *  \details     -
 *  \param[in]   Source               The source node of the request.
 *  \param[in]   ProcessHandle        Handle of DataProcess.
 *  \param[in]   Handle               Handle of RemoteStream.
 *  \param[in]   StreamBuffer         Buffer containing data.
 *  \param[in]   StreamBuffer_Length  length of data.
 *  \param[in]   Result               Result of previous request.
 *  \return      E_OK                 Copied stream data successfully.
 *  \return      else                 Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamCopy(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  vSwUpdM_LengthType StreamBuffer_Length,
  Std_ReturnType Result);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamRequest
 *********************************************************************************************************************/
/*! \brief Handle remote RemoteStreamRequest request.
 *  \details     -
 *  \param[in]   Source          Source of the request.
 *  \param[in]   ProcessHandle   Handle of DataProcess.
 *  \param[in]   Handle          Handle of RemoteStream.
 *  \param[in]   Result          Result of previous request.
 *  \param[in]   BufferSize      Available buffer size on receives side.
 *  \return      E_OK            Copied stream data successfully.
 *  \return      else            Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamRequest(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  Std_ReturnType Result,
  vSwUpdM_LengthType BufferSize);

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamEnd
 *********************************************************************************************************************/
/*! \brief Handle RemoteStreamEnd request.
 *  \details     -
 *  \param[in]   Source         Source of the request.
 *  \param[in]   ProcessHandle  Handle of DataProcess.
 *  \param[in]   Handle         Handle of RemoteStream.
 *  \param[in]   Result         Result of previous request.
 *  \return      E_OK           Successfully finished.
 *  \return      else           Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamEnd(
    vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  Std_ReturnType Result);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_AddSegment
 *********************************************************************************************************************/
/*! \brief Handle AddSegment request.
 *  \details     -
 *  \param[in]   Source             The source node of the request.
 *  \param[in]   ServiceState       Scheduling state of service.
 *  \param[in]   RemoteSegmentInfo  Packed segment info from remote transmission.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_AddSegment(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteSegmentInfo);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_ProcessModuleService
 *********************************************************************************************************************/
/*! \brief Handle ProcessModuleService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Scheduling state of service.
 *  \param[in]   Service            ID of the specific service.
 *  \param[in]   ModuleId           ID of module.
 *  \param[in]   ProcessId          ID of requested data process.
 *  \param[in]   ProcessInfo        Processing meta information.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ProcessModuleService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) ProcessInfo);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleState
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateModuleState request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ModuleHandle       Handle of module.
 *  \param[in]   State              Module state
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleState(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ModuleStateType State);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleValid
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateModuleValid request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ModuleHandle       Handle of module.
 *  \param[in]   Validity           Module validity.
 *  \param[in]   RevisionUpdate     Indicate how the revision update shall be handled.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleValid(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ValidType Validity,
  vSwUpdM_RevisionUpdateType RevisionUpdate);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateModuleProgrammingAttempts request.
 *  \details     -
 *  \param[in]   Source              Node index of source of the request.
 *  \param[in]   ModuleHandle        Handle of module.
 *  \param[in]   ProgrammingAttempts Number of programming attempts.
 *  \return      E_OK                Successfully finished.
 *  \return      else                Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateRegionState
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateRegionState request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   RegionHandle       Handle of region.
 *  \param[in]   State              New region state.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateRegionState(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_RegionHandleIdType RegionHandle,
  vSwUpdM_RegionStateType State);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateRegionProgrammingAttempts request.
 *  \details     -
 *  \param[in]   Source              Node index of source of the request.
 *  \param[in]   RegionHandle        Handle of region.
 *  \param[in]   ProgrammingAttempts Number of programming attempts.
 *  \return      E_OK                Successfully finished.
 *  \return      else                Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_RegionHandleIdType RegionHandle,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateSegmentAttributes request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   RemoteSegmentInfo  Info of remote segment.
 *  \param[in]   State              New state attributes.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes(
  vSwUpdM_NodeIterType Source,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteSegmentInfo,
  vSwUpdM_SegmentStateType State);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo
 *********************************************************************************************************************/
/*! \brief Handle remote UpdateResumeInfo request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ResumeInfo         Remote value of ResumeInfo.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo(
  vSwUpdM_NodeIterType Source,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) ResumeInfo);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteProcessRequestInput
 *********************************************************************************************************************/
/*! \brief Handle remote ProcessRequestInput request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Indicates if service is triggered initially or shall be resumed.
 *  \param[in]   DataProcessHandle  The handle identifying the data process.
 *  \param[in]   InputIndex         vSwUpdM_ProcessUserData index.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteProcessRequestInput(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_ProcessHandleOfDataProcessesType DataProcessHandle,
  uint8 InputIndex);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteConcludeSegment
 *********************************************************************************************************************/
/*! \brief Handle remote ConcludeSegment request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   StartAddress       The start address of the segment.
 *  \param[in]   WriteAddress       The write address of the segment.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteConcludeSegment(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_AddressType WriteAddress);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_GenericService
 *********************************************************************************************************************/
/*! \brief Handle GenericService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter.
 *  \param[in]   Service            Incoming parameter.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_GenericService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_PartitionService
 *********************************************************************************************************************/
/*! \brief Handle PartitionService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter.
 *  \param[in]   Service            Incoming parameter.
 *  \param[in]   PartitionState     State of used partition.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_PartitionService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_PartitionStateType PartitionState);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_ModuleService
 *********************************************************************************************************************/
/*! \brief Handle ModuleService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter
 *  \param[in]   Service            Incoming parameter
 *  \param[in]   ModuleId           Id of module.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ModuleService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RegionService
 *********************************************************************************************************************/
/*! \brief Handle RegionService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter
 *  \param[in]   Service            Incoming parameter
 *  \param[in]   RegionId           Id of region.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RegionService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_RegionIdType RegionId);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_SegmentService
 *********************************************************************************************************************/
/*! \brief Handle SegmentService request.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter
 *  \param[in]   Service            Incoming parameter
 *  \param[in]   SegmentId          Id of segment.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_SegmentService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_SegmentIdType SegmentId);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_MaintenanceService
 *********************************************************************************************************************/
/*! \brief vRpcProxy receive callout function for MaintenanceService call.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   ServiceState       Incoming parameter
 *  \param[in]   Service            Incoming parameter
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_MaintenanceService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service);

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_SuspendService
 *********************************************************************************************************************/
/*! \brief vRpcProxy receive callout function for SuspendService call.
 *  \details     -
 *  \param[in]   Source             Node index of source of the request.
 *  \param[in]   Service            The service, which shall be suspended.
 *  \return      E_OK               Successfully finished.
 *  \return      else               Issues detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_SuspendService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_GridSrvc_ServiceIdxType Service);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_HandleRxChannels
 *********************************************************************************************************************/
/*! \brief       Transmits all pending responses; If a request is still processing a "pending" trigger is sent.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_HandleRxChannels(void);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_SERVICES_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Services_If.h
 *********************************************************************************************************************/
