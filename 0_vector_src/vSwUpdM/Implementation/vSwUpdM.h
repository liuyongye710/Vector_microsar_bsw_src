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
/*!        \file  vSwUpdM.h
 *        \brief  vSwUpdM header file
 *      \details  Header file containing all public API declarations of Software Update Manager.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2017-12-06  visjhg  STORYC-3179   Implement initial version of Software Update Manager
 *  01.01.00  2018-01-19  visjhg  STORYC-3516   Memory Mapping from logical to virtual view
 *  01.02.00  2018-02-16  visjhg  STORYC-3855   Basic job processing / data buffering
 *                        visjhg  STORYC-3856   Memory access
 *  01.03.00  2018-04-26  visjhg  STORYC-3854   Bank switch
 *  02.00.00  2018-06-06  visjhg  STORYC-5612   Use additional generated configuration values
 *                        visjhg  ESCAN00099595 Set write address of memory fill and copy operations during init state
 *  02.01.00  2018-08-21  visjhg  ESCAN00099999 Postpone confirmation of ProvideStreamData until write is finished
 *                        visjhg  STORYC-5719   Resumable programming for controlled shutdown use-case
 *  02.01.01  2018-09-07  visjhg  STORYC-6418   Module synchronization
 *                        visjhg  STORYC-6419   Support for backup partition
 *                        visjhg  STORYC-6420   Support for partition groups
 *  02.01.02  2018-09-12  visjhg  ESCAN00100710 Delay persisting of segment information until execution of OpenSegment
 *  02.01.03  2018-09-21  visjhg  ESCAN00100821 Handling of dynamically sized segments for use-case where region
 *                                              only covers parts of the last memory sector
 *  03.00.00  2018-12-04  visjhg  STORYC-4635   Added GetOpenPartitionId to API
 *                        visjhg  STORYC-6612   Detect unexpected shutdown, resume interrupted operation on a
 *                                              per-module basis
 *                        visjhg  STORYC-7214   Reworked partition state handling:
 *                                              - Dedicated states for backup target and backup source
 *                                              - Partition can be in multiple states at once
 *                        visjhg  STORYC-5058   Propagate errors through job processing
 *                                              Additional specific error codes
 *  03.01.00  2019-02-15  visjhg  STORYC-6914   Service specific pre- and post-hook functions
 *                        visjhg  ESCAN00101595 Take over active partition revision to backup target
 *                        visjhg  ESCAN00101964 Init static segment ID in GetSegmentId* functions
 *                        visjhg  STORYC-4409   Support erase and write burst
 *                        visjhg  STORYC-7496   Refine failure handling
 *  03.01.01  2019-02-21  visjhg  ESCAN00102224 Persist "finalized" state of segments
 *  03.01.02  2019-02-22  visjhg  ESCAN00102238 Added explicit jobs for initialization and Start service
 *  03.02.00  2019-03-08  visjhg  STORYC-6428   Release for series production.
 *                        visjhg  ESCAN00102412 Align reserved start and end address of region to sector boundaries
 *  03.03.00  2019-04-12  visjhg  ESCAN00102764 Set type of internal segments to unused value.
 *                        visjhg  STORYC-6428   Extended component detail design.
 *  04.00.00  2019-07-03  visshs  STORY-10924   Add remote functionality
 *  04.00.01  2019-07-12  visshs  ESCAN00103700 Fixed handling of Resume Information on remote download
 *  04.01.00  2019-08-02  visrr   STORY-10922   Add verification service in vSwUpdM
 *  04.02.00  2019-08-23  visjhg  SWUP-442      Use vStreamProc for processing of input data streams.
 *                        visshs  SWUP-351      Add support for Pipelined Programming
 *                        visrr   SWUP-16       Add support for generic data processing (needed by diff update)
 *                        visrr   SWUP-514      Data processing rework
 *                        visrr   ESCAN00104048 Corrected vSwUpdM_ProcessModule pipe usage
 *                        visjhg  ESCAN00104053 Module cleanup: Always include triggering segment in erase.
 *                        visjhg  ESCAN00104065 Do not overwrite negative job result in ProcessStreamData job.
 *                        visjhg  SWUP-561      Remote download in combination with vStreamProc
 *                        visshs  SWUP-465      Add module verification service with vStreamProc
 *  04.03.00  2019-08-26  visjhg  ESCAN00104134 Do not finish ProcessStreamData job when input data is pending.
 *                        visjhg  ESCAN00104138 Leave processing loop in case of insufficient input/output.
 *  04.04.00  2019-11-22  visrr   SWUP-653      Added CDD for module processing.
 *                                              Added CDD for fine-grained resume.
 *                        visrr   ESCAN00104073 Added comparison of contents after module synchronization.
 *                        visrr   ESCAN00104312 Set revision to invalid value, when partition/module is invalidated.
 *                        visrr   ESCAN00104423 FinalizeSegment: Corrected resume information for hook restart action.
 *                        visjhg  ESCAN00104671 Enforce 32 bit alignment of write buffer.
 *                        visjhg  ESCAN00104768 Re-initialize processing node workspaces on implicit flush.
 *                        visjhg  ESCAN00105019 Pass data element count instead of byte length to vStreamProc APIs.
 *                        visshs  SWUP-195      Added CDD for remote functionality.
 *  04.05.00  2020-01-17  visjhg  SWUP-721      Added resume processing nodes.
 *                        visshs                Added process operations to allow shutdown and re-start of pipe processing.
 *                                              Added stream address to resume information (calculated depending on
 *                                              resume offset).
 *                                              Use pipes for copying and comparison during module synchronization.
 *                        visshs  SWUP-712      Support additional sub-scopes for module processing.
 *                        visjhg  SWUP-632      Added support for programming attempt counter (per module instance).
 *                        visjhg  ESCAN00105285 Use apparent write address to calculate resume address.
 *  04.06.00  2020-02-19  visshs  ESCAN00105394 vSwUpdM_Segment_IsSegmentIdAllowed is required for Det checks or
 *                                              Multiprocessor configurations.
 *                        visshs  ESCAN00105403 Introduce VSWUPDM_SUB_SCOPE_ATTRIBUTE_REMOTE_EXECUTION to describe
 *                                              remote execution of a pipe.
 *                        visshs  ESCAN00105478 Shutdown resets flag vSwUpdM_Remote_LocalInstanceIsMaster.
 *                        visshs  ESCAN00105480 Evaluated SuspendResponse in JobHandler_RemoteSuspendConfirmation().
 *                        visshs  ESCAN00105481 Fixed suspend reaction in JobHandler_RemoteTargetConfirmation().
 *                        visshs  ESCAN00105482 Evaluate response of RemoteProcessRequestInput to ensure
 *                                              synchronization between remote and local instance.
 *                        visjhg  ESCAN00105499 Directly persist programming attempts counters of regions in case
 *                                              of mismatch with module counter.
 *                        visjhg  ESCAN00105517 Corrected check whether output operation is available for pipe.
 *                        visshs  ESCAN00105542 Moved unlock to end of shutdown sequence.
 *                        visjhg  ESCAN00105611 Explicit casts from iteration types to ID types.
 *                        visshs  ESCAN00105675 Remote streams are cleared on service dispatcher finish.
 *  04.07.00  2020-11-20  visrr   SWUP-537      Update documentation in getter callouts.
 *                        visshs  ESCAN00106023 Fix FinalizeModule fails after a unintended reset.
 *                        visshs  ESCAN00106024 Fix OpenModule causes NULL-Pointer exception after aborted download.
 *                        visshs  ESCAN00106001 Removed unused variable vSwUpdM_BufferInfoCopyInputStream.
 *                        visshs  ESCAN00105959 Restrict availability of vSwUpdM_Segment_GetSegmentIdByStartAddress
 *                                              to multi-controller use case.
 *                        visshs  ESCAN00105960 Restrict availability of vSwUpdM_RemoteStream_List and
 *                                              vSwUpdM_RemoteLockIsGrantedTo to multi-controller use case.
 *                        visshs  ESCAN00106096 JobHandler_CompareModule must close module after use if it is opened
 *                                              implicitly.
 *                        visshs  ESCAN00106181 Evaluate source of Lock request before checking for errors.
 *                        visshk  SWUP-836      Split upper layer access, exec control and instance into separate
 *                                              multi units.
 *                        visshs  SWUP-821      Rework remote service processing / response aggregation.
 *                                              Add multi unit Grid.
 *                        visshs  SWUP-915      Reduce number of remote services.
 *                        visjhg  SWUP-1008     Added vSwUpdM_AddFinalizedSegment, vSwUpdM_IndicateWriteToModule and
 *                                              vSwUpdM_GetCheckpoint to API.
 *                        visrr   SWUP-937      Add vSwUpdM_GetCurrentPersistClientNode API.
 *                        visshs                Add persistor and bookkeeper multi units.
 *                        visshs  SWUP-940      Upgrade vSwUpdM to use interfaces of vRpcProxy 2.xx
 *                        visjhg  SWUP-1012     Support shutdown and re-start of pipe processing triggered by ProcessModule.
 *                                              Support remote service processing of ProcessModule.
 *  04.07.01  2021-02-12  visshs  ESCAN00108163 Fixed out-of-bounds access on RPC response reception.
 *                        visshs  ESCAN00108202 Fixed compiler warning: signed/unsigned conversion.
 *                        visshs  ESCAN00108280 Fixed compiler warning: possible loss of data.
 *                        visjhg  ESCAN00108133 Only persist segment count when value has changed.
 *                        visjhg  ESCAN00108143 Do not persist region erase address after each sector.
 *                        visrr   ESCAN00108361 Fixed mask handling in persistor server.
 *  04.07.02  2021-03-12  visshs  ESCAN00108432 Fixed wrong target reference for multi-node download stream.
 *                        visshs  ESCAN00108539 Moved remote Start() to main grid channel.
 *                        visshs  ESCAN00108541 Adjusted job priorities to fix blocking on RemoteUpdate calls during
 *                                              Shutdown.
 *                        visshs  ESCAN00108623 Fixed usage of datatype vRpcProxy_CTargetsIterType.
 *                        visshs  ESCAN00108570 Multi-Node: Use ServiceState RESUME for opening requests again on
 *                                              Resume() to enable tracking of pending responses after resume.
 *  05.00.00  2021-04-09  visshs  SWUP-1253     Rework of dispatcher.
 *                        visdlm  ESCAN00108963 Fixed wrong usage of Region handle by remote persist client.
 *                        visdlm  ESCAN00108962 Fixed job prioritization to avoid inconsistent region/module
 *                                              ProgrammingAttemptCtr values.
 *                        visdlm  SWUP-1305     Provided dedicated interface for dependent processing nodes.
 *                        visshs  SWUP-1233     Update to vStreamProc 2.00.00
 *  05.01.00  2021-07-16  visshs  SWUP-1300     Add BufferSize element to ProcessInfo structure.
 *                        visshs  SWUP-1367     Upgrade to vStreamProc 2.xx.xx (QM)
 *                        visshs  ESCAN00109686 [Multi-Node, RemoteBkPersistServer] DET: E_WRONG_PARAMETER is triggered.
 *                        visshs  ESCAN00109633 Callouts are called from inside Critical Section
 *  05.01.01  2021-11-30  visdlm  ESCAN00110832 Service ProcessStreamData causes DET error when downloading processed
 *                                              Data to the ECU.
 *********************************************************************************************************************/

#if !defined(VSWUPDM_H)
#define VSWUPDM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "vSwUpdM_Cfg.h"
#include "vSwUpdM_Types.h"
#include "vSwUpdM_CfgTypes.h"

#include "vMemAccM.h"

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
#include "vRpcProxy.h"
#endif

#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
#include "Det.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
#define VSWUPDM_VENDOR_ID                             (30u)
#define VSWUPDM_MODULE_ID                             (255u)
#define VSWUPDM_INSTANCE_ID                           (uint8)(0x00u)

/* AUTOSAR Software Specification Version Information */
#define VSWUPDM_AR_MAJOR_VERSION                      (0x04u)
#define VSWUPDM_AR_MINOR_VERSION                      (0x00u)
#define VSWUPDM_AR_PATCH_VERSION                      (0x03u)

/* Component Version Information */
#define VSWUPDM_SW_MAJOR_VERSION                      (0x05u)
#define VSWUPDM_SW_MINOR_VERSION                      (0x01u)
#define VSWUPDM_SW_PATCH_VERSION                      (0x01u)

/* Init States */
#define VSWUPDM_INIT_STATE_UNINIT                     (0x00u)
#define VSWUPDM_INIT_STATE_PENDING                    (0x01u)
#define VSWUPDM_INIT_STATE_INITIALIZED                (0x02u)
#define VSWUPDM_INIT_STATE_FAILED                     (0x03u)

/* ----- API service IDs ----- */

#define VSWUPDM_SID_NONE                                (vSwUpdM_ServiceIdType)(0xFFu)

/*  - General */
#define VSWUPDM_SID_INIT_MEMORY                         (vSwUpdM_ServiceIdType)(0x00u)  /*!< Service ID: vSwUpdM_InitMemory() */
#define VSWUPDM_SID_INIT                                (vSwUpdM_ServiceIdType)(0x01u)  /*!< Service ID: vSwUpdM_Init() */
#define VSWUPDM_SID_DEINIT                              (vSwUpdM_ServiceIdType)(0x02u)  /*!< Service ID: vSwUpdM_DeInit() */
#define VSWUPDM_SID_GET_VERSION_INFO                    (vSwUpdM_ServiceIdType)(0x03u)  /*!< Service ID: vSwUpdM_GetVersionInfo() */
#define VSWUPDM_SID_MAIN_FUNCTION                       (vSwUpdM_ServiceIdType)(0x04u)  /*!< Service ID: vSwUpdM_MainFunction() */
#define VSWUPDM_SID_INIT_PROCESS_INFO                   (vSwUpdM_ServiceIdType)(0x05u)  /*!< Service ID: vSwUpdM_InitProcessInfo() */
#define VSWUPDM_SID_INIT_ENTITY_IDS                     (vSwUpdM_ServiceIdType)(0x06u)  /*!< Service ID: vSwUpdM_InitEntityIds() */

/*  - State */
#define VSWUPDM_SID_START                               (vSwUpdM_ServiceIdType)(0x10u)  /*!< Service ID: vSwUpdM_Start() */
#define VSWUPDM_SID_SHUTDOWN                            (vSwUpdM_ServiceIdType)(0x11u)  /*!< Service ID: vSwUpdM_Shutdown() */
#define VSWUPDM_SID_ABORT                               (vSwUpdM_ServiceIdType)(0x12u)  /*!< Service ID: vSwUpdM_Abort() */
#define VSWUPDM_SID_SUSPEND                             (vSwUpdM_ServiceIdType)(0x13u)  /*!< Service ID: vSwUpdM_Suspend() */
#define VSWUPDM_SID_RESUME                              (vSwUpdM_ServiceIdType)(0x14u)  /*!< Service ID: vSwUpdM_Resume() */
#define VSWUPDM_SID_GET_STATE                           (vSwUpdM_ServiceIdType)(0x15u)  /*!< Service ID: vSwUpdM_GetState() */
#define VSWUPDM_SID_GET_RESUME_INFO                     (vSwUpdM_ServiceIdType)(0x16u)  /*!< Service ID: vSwUpdM_GetResumeInfo() */
#define VSWUPDM_SID_GET_CHECKPOINT                      (vSwUpdM_ServiceIdType)(0x17u)  /*!< Service ID: vSwUpdM_GetCheckpoint() */

/*  - Partition */
#define VSWUPDM_SID_OPEN_PARTITION                      (vSwUpdM_ServiceIdType)(0x20u)  /*!< Service ID: vSwUpdM_OpenPartition() */
#define VSWUPDM_SID_VALIDATE_PARTITION                  (vSwUpdM_ServiceIdType)(0x21u)  /*!< Service ID: vSwUpdM_ValidatePartition() */
#define VSWUPDM_SID_INVALIDATE_PARTITION                (vSwUpdM_ServiceIdType)(0x22u)  /*!< Service ID: vSwUpdM_InvalidatePartition() */
#define VSWUPDM_SID_SYNC_PARTITION                      (vSwUpdM_ServiceIdType)(0x23u)  /*!< Service ID: vSwUpdM_SyncPartition() */
#define VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY         (vSwUpdM_ServiceIdType)(0x24u)  /*!< Service ID: vSwUpdM_CheckPartitionConsistency() */
#define VSWUPDM_SID_SWAP_ACTIVE_PARTITION               (vSwUpdM_ServiceIdType)(0x25u)  /*!< Service ID: vSwUpdM_SwapActivePartition() */
#define VSWUPDM_SID_GET_PARTITION_STATE_BY_HANDLE       (vSwUpdM_ServiceIdType)(0x26u)  /*!< Service ID: vSwUpdM_GetPartitionStateByHandle() */
#define VSWUPDM_SID_GET_OPEN_PARTITION_STATE            (vSwUpdM_ServiceIdType)(0x28u)  /*!< Service ID: vSwUpdM_GetOpenPartitionState() */
#define VSWUPDM_SID_GET_PARTITION_INFO                  (vSwUpdM_ServiceIdType)(0x29u)  /*!< Service ID: vSwUpdM_GetPartitionInfo() */
#define VSWUPDM_SID_IS_PARTITION_ERASABLE               (vSwUpdM_ServiceIdType)(0x2Au)  /*!< Service ID: vSwUpdM_IsPartitionErasable() */
#define VSWUPDM_SID_IS_PARTITION_READABLE               (vSwUpdM_ServiceIdType)(0x2Bu)  /*!< Service ID: vSwUpdM_IsPartitionReadable() */
#define VSWUPDM_SID_IS_PARTITION_WRITABLE               (vSwUpdM_ServiceIdType)(0x2Cu)  /*!< Service ID: vSwUpdM_IsPartitionWritable() */

/*  - Module */
#define VSWUPDM_SID_OPEN_MODULE                         (vSwUpdM_ServiceIdType)(0x30u)  /*!< Service ID: vSwUpdM_OpenModule() */
#define VSWUPDM_SID_CLOSE_MODULE                        (vSwUpdM_ServiceIdType)(0x31u)  /*!< Service ID: vSwUpdM_CloseModule() */
#define VSWUPDM_SID_ERASE_MODULE                        (vSwUpdM_ServiceIdType)(0x32u)  /*!< Service ID: vSwUpdM_EraseModule() */
#define VSWUPDM_SID_SYNC_MODULE                         (vSwUpdM_ServiceIdType)(0x33u)  /*!< Service ID: vSwUpdM_SyncModule() */
#define VSWUPDM_SID_VALIDATE_MODULE                     (vSwUpdM_ServiceIdType)(0x34u)  /*!< Service ID: vSwUpdM_ValidateModule() */
#define VSWUPDM_SID_INVALIDATE_MODULE                   (vSwUpdM_ServiceIdType)(0x35u)  /*!< Service ID: vSwUpdM_InvalidateModule() */
#define VSWUPDM_SID_GET_MODULE_ID_BY_HANDLE             (vSwUpdM_ServiceIdType)(0x36u)  /*!< Service ID: vSwUpdM_GetModuleIdByHandle() */
#define VSWUPDM_SID_GET_MODULE_ID_BY_RANGE              (vSwUpdM_ServiceIdType)(0x37u)  /*!< Service ID: vSwUpdM_GetModuleIdByRange() */
#define VSWUPDM_SID_GET_MODULE_INFO                     (vSwUpdM_ServiceIdType)(0x38u)  /*!< Service ID: vSwUpdM_GetModuleInfo() */
#define VSWUPDM_SID_GET_NUMBER_OF_MODULES               (vSwUpdM_ServiceIdType)(0x39u)  /*!< Service ID: vSwUpdM_GetNumberOfModules() */
#define VSWUPDM_SID_IS_MODULE_ERASABLE                  (vSwUpdM_ServiceIdType)(0x3Au)  /*!< Service ID: vSwUpdM_IsModuleErasable() */
#define VSWUPDM_SID_IS_MODULE_READABLE                  (vSwUpdM_ServiceIdType)(0x3Bu)  /*!< Service ID: vSwUpdM_IsModuleReadable() */
#define VSWUPDM_SID_IS_MODULE_WRITABLE                  (vSwUpdM_ServiceIdType)(0x3Cu)  /*!< Service ID: vSwUpdM_IsModuleWritable() */
#define VSWUPDM_SID_FINALIZE_MODULE                     (vSwUpdM_ServiceIdType)(0x3Du)  /*!< Service ID: vSwUpdM_FinalizeModule() */
#define VSWUPDM_SID_GET_OPEN_MODULE_ID                  (vSwUpdM_ServiceIdType)(0x3Fu)  /*!< Service ID: vSwUpdM_GetOpenModuleId() */
#define VSWUPDM_SID_UPDATE_MODULE_STATE                 (vSwUpdM_ServiceIdType)(0x90u)  /*!< Service ID: Remote Bookkeeper */
#define VSWUPDM_SID_UPDATE_MODULE_VALID                 (vSwUpdM_ServiceIdType)(0x91u)  /*!< Service ID: Remote Bookkeeper */
#define VSWUPDM_SID_UPDATE_MODULE_PROGRAMMING_ATTEMPTS  (vSwUpdM_ServiceIdType)(0x92u)  /*!< Service ID: Remote Bookkeeper */
#define VSWUPDM_SID_VERIFY_MODULE                       (vSwUpdM_ServiceIdType)(0x40u)  /*!< Service ID: vSwUpdM_VerifyModule() */
#define VSWUPDM_SID_PROCESS_MODULE                      (vSwUpdM_ServiceIdType)(0x41u)  /*!< Service ID: vSwUpdM_ProcessModule() */
#define VSWUPDM_SID_INDICATE_WRITE_TO_MODULE            (vSwUpdM_ServiceIdType)(0x42u)  /*!< Service ID: vSwUpdM_IndicateWriteToModule() */

/*  - Region */
#define VSWUPDM_SID_ERASE_REGION                        (vSwUpdM_ServiceIdType)(0x50u)  /*!< Service ID: vSwUpdM_EraseRegion() */
#define VSWUPDM_SID_GET_REGION_ID_BY_HANDLE             (vSwUpdM_ServiceIdType)(0x51u)  /*!< Service ID: vSwUpdM_GetRegionIdByHandle() */
#define VSWUPDM_SID_GET_REGION_ID_BY_RANGE              (vSwUpdM_ServiceIdType)(0x52u)  /*!< Service ID: vSwUpdM_GetRegionIdByRange() */
#define VSWUPDM_SID_GET_REGION_ID_OF_MODULE_BY_INDEX    (vSwUpdM_ServiceIdType)(0x53u)  /*!< Service ID: vSwUpdM_GetRegionIdOfModuleByIndex() */
#define VSWUPDM_SID_GET_REGION_INFO                     (vSwUpdM_ServiceIdType)(0x54u)  /*!< Service ID: vSwUpdM_GetRegionInfo() */
#define VSWUPDM_SID_IS_REGION_ERASABLE                  (vSwUpdM_ServiceIdType)(0x55u)  /*!< Service ID: vSwUpdM_IsRegionErasable() */
#define VSWUPDM_SID_IS_REGION_READABLE                  (vSwUpdM_ServiceIdType)(0x56u)  /*!< Service ID: vSwUpdM_IsRegionReadable() */
#define VSWUPDM_SID_IS_REGION_WRITABLE                  (vSwUpdM_ServiceIdType)(0x57u)  /*!< Service ID: vSwUpdM_IsRegionWritable() */
#define VSWUPDM_SID_GET_NUMBER_OF_REGIONS_OF_MODULE     (vSwUpdM_ServiceIdType)(0x58u)  /*!< Service ID: vSwUpdM_GetNumberOfRegionssOfModule() */
#define VSWUPDM_SID_UPDATE_REGION_STATE                 (vSwUpdM_ServiceIdType)(0x93u)  /*!< Service ID: Remote Bookkeeper */
#define VSWUPDM_SID_UPDATE_REGION_PROGRAMMING_ATTEMPTS  (vSwUpdM_ServiceIdType)(0x94u)  /*!< Service ID: Remote Bookkeeper */

/*  - Segment */
#define VSWUPDM_SID_OPEN_SEGMENT                        (vSwUpdM_ServiceIdType)(0x60u)  /*!< Service ID: vSwUpdM_OpenSegment() */
#define VSWUPDM_SID_CLOSE_SEGMENT                       (vSwUpdM_ServiceIdType)(0x61u)  /*!< Service ID: vSwUpdM_CloseSegment() */
#define VSWUPDM_SID_ADD_SEGMENT                         (vSwUpdM_ServiceIdType)(0x62u)  /*!< Service ID: vSwUpdM_AddSegment() */
#define VSWUPDM_SID_CLEAR_SEGMENTS_OF_MODULE            (vSwUpdM_ServiceIdType)(0x63u)  /*!< Service ID: vSwUpdM_ClearSegmentsOfModule() */
#define VSWUPDM_SID_GET_NUMBER_OF_SEGMENTS_OF_MODULE    (vSwUpdM_ServiceIdType)(0x64u)  /*!< Service ID: vSwUpdM_GetNumberOfSegmentsOfModule() */
#define VSWUPDM_SID_GET_SEGMENT_ID_BY_RANGE             (vSwUpdM_ServiceIdType)(0x65u)  /*!< Service ID: vSwUpdM_GetSegmentIdByRange() */
#define VSWUPDM_SID_GET_SEGMENT_ID_OF_MODULE_BY_INDEX   (vSwUpdM_ServiceIdType)(0x66u)  /*!< Service ID: vSwUpdM_GetSegmentIdOfModuleByIndex() */
#define VSWUPDM_SID_GET_SEGMENT_ID_OF_MODULE_BY_TYPE    (vSwUpdM_ServiceIdType)(0x67u)  /*!< Service ID: vSwUpdM_GetSegmentIdOfModuleByType() */
#define VSWUPDM_SID_GET_SEGMENT_INFO                    (vSwUpdM_ServiceIdType)(0x68u)  /*!< Service ID: vSwUpdM_GetSegmentInfo() */
#define VSWUPDM_SID_INIT_SEGMENT_INFO                   (vSwUpdM_ServiceIdType)(0x69u)  /*!< Service ID: vSwUpdM_InitSegmentInfo() */
#define VSWUPDM_SID_FINALIZE_SEGMENT                    (vSwUpdM_ServiceIdType)(0x6Au)  /*!< Service ID: vSwUpdM_FinalizeSegment() */
#define VSWUPDM_SID_GET_OPEN_SEGMENT_ID                 (vSwUpdM_ServiceIdType)(0x6Bu)  /*!< Service ID: vSwUpdM_GetOpenSegmentId() */
#define VSWUPDM_SID_VERIFY_SEGMENT                      (vSwUpdM_ServiceIdType)(0x6Cu)  /*!< Service ID: vSwUpdM_VerifySegment() */
#define VSWUPDM_SID_ADD_FINALIZED_SEGMENT               (vSwUpdM_ServiceIdType)(0x6Du)  /*!< Service ID: vSwUpdM_AddFinalizedSegment() */
#define VSWUPDM_SID_UPDATE_SEGMENT_ATTRIBUTES           (vSwUpdM_ServiceIdType)(0x95u)  /*!< Service ID: Remote Bookkeeper */
#define VSWUPDM_SID_CONCLUDE_SEGMENT                    (vSwUpdM_ServiceIdType)(0x96u)  /*!< Service ID: Remote Callout */
#define VSWUPDM_SID_UPDATE_RESUME_INFO                  (vSwUpdM_ServiceIdType)(0x98u)  /*!< Service ID: Remote Bookkeeper */

/*  - Range */
#define VSWUPDM_SID_ERASE_RANGE                         (vSwUpdM_ServiceIdType)(0x70u)  /*!< Service ID: vSwUpdM_EraseRange() */
#define VSWUPDM_SID_READ_RANGE                          (vSwUpdM_ServiceIdType)(0x71u)  /*!< Service ID: vSwUpdM_ReadRange() */
#define VSWUPDM_SID_WRITE_RANGE                         (vSwUpdM_ServiceIdType)(0x72u)  /*!< Service ID: vSwUpdM_WriteRange() */
#define VSWUPDM_SID_IS_RANGE_ERASABLE                   (vSwUpdM_ServiceIdType)(0x73u)  /*!< Service ID: vSwUpdM_IsRangeErasable() */
#define VSWUPDM_SID_IS_RANGE_READABLE                   (vSwUpdM_ServiceIdType)(0x74u)  /*!< Service ID: vSwUpdM_IsRangeReadable() */
#define VSWUPDM_SID_IS_RANGE_WRITABLE                   (vSwUpdM_ServiceIdType)(0x75u)  /*!< Service ID: vSwUpdM_IsRangeWritable() */
#define VSWUPDM_SID_ALIGN_ADDRESS                       (vSwUpdM_ServiceIdType)(0x76u)  /*!< Service ID: vSwUpdM_AlignAddress() */
#define VSWUPDM_SID_GET_PADDING_VALUE                   (vSwUpdM_ServiceIdType)(0x77u)  /*!< Service ID: vSwUpdM_GetPaddingValue() */

/*  - Stream */
#define VSWUPDM_SID_START_STREAM                        (vSwUpdM_ServiceIdType)(0x80u)  /*!< Service ID: vSwUpdM_StartStream() */
#define VSWUPDM_SID_PROCESS_STREAM_DATA                 (vSwUpdM_ServiceIdType)(0x81u)  /*!< Service ID: vSwUpdM_ProcessStreamData() */
#define VSWUPDM_SID_END_STREAM                          (vSwUpdM_ServiceIdType)(0x82u)  /*!< Service ID: vSwUpdM_EndStream() */
#define VSWUPDM_SID_INIT_STREAM_INFO                    (vSwUpdM_ServiceIdType)(0x83u)  /*!< Service ID: vSwUpdM_InitStreamInfo() */
#define VSWUPDM_SID_SWITCH_STREAM_CONTEXT               (vSwUpdM_ServiceIdType)(0x84u)  /*!< Service ID: vSwUpdM_SwitchStreamContext() */
#define VSWUPDM_SID_COPY_STREAM_DATA                    (vSwUpdM_ServiceIdType)(0x85u)  /*!< Service ID: Callout <UL>_CddOsoh_vSwUpdMCopyStreamData() */
#define VSWUPDM_SID_REQUEST_PROCESS_INFO                (vSwUpdM_ServiceIdType)(0x97u)  /*!< Service ID: Remote Callout */

/* ----- Error codes ----- */
#define VSWUPDM_E_NO_ERROR                              (vSwUpdM_ErrorCode)(0xFFu)  /*!< No error */
#define VSWUPDM_E_INV_POINTER                           (vSwUpdM_ErrorCode)(0x01u)  /*!< Invalid pointer */
#define VSWUPDM_E_INV_CONFIG                            (vSwUpdM_ErrorCode)(0x02u)  /*!< Error code: API service called with wrong parameter; Due to wrong configuration. */
#define VSWUPDM_E_WRONG_PARAMETER                       (vSwUpdM_ErrorCode)(0x03u)  /*!< Error code: API service called with wrong parameter; Due to wrong parameter. */
#define VSWUPDM_E_NOT_INITIALIZED                       (vSwUpdM_ErrorCode)(0x04u)  /*!< Error code: API service used without module initialization. */
#define VSWUPDM_E_ALREADY_INITIALIZED                   (vSwUpdM_ErrorCode)(0x05u)  /*!< Error code: The service is called while the module is already initialized. */
#define VSWUPDM_E_OUT_OF_RANGE                          (vSwUpdM_ErrorCode)(0x06u)  /*!< Error code: API service called with an invalid address. */
#define VSWUPDM_E_INV_RANGE                             (vSwUpdM_ErrorCode)(0x07u)  /*!< Error code: API service called to access invalid range. */
#define VSWUPDM_E_RANGE_NOT_ERASABLE                    (vSwUpdM_ErrorCode)(0x08u)  /*!< Error code: API service called to erase invalid range. */
#define VSWUPDM_E_RANGE_NOT_READABLE                    (vSwUpdM_ErrorCode)(0x09u)  /*!< Error code: API service called to read invalid range. */
#define VSWUPDM_E_RANGE_NOT_WRITABLE                    (vSwUpdM_ErrorCode)(0x0Au)  /*!< Error code: API service called to write invalid range. */
#define VSWUPDM_E_NO_PARTITION_OPENED                   (vSwUpdM_ErrorCode)(0x0Bu)  /*!< Error code: API service called without partition being opened. */
#define VSWUPDM_E_NO_MODULE_OPENED                      (vSwUpdM_ErrorCode)(0x0Cu)  /*!< Error code: API service called without module being opened. */
#define VSWUPDM_E_NO_SEGMENT_OPENED                     (vSwUpdM_ErrorCode)(0x0Du)  /*!< Error code: API service called without segment being opened. */
#define VSWUPDM_E_NO_STREAM_STARTED                     (vSwUpdM_ErrorCode)(0x0Eu)  /*!< Error code: API service called without stream being started. */
#define VSWUPDM_E_NOT_IDLE                              (vSwUpdM_ErrorCode)(0x0Fu)  /*!< Error code: API service called while module isn't idle. */
#define VSWUPDM_E_MODULE_NOT_ERASED                     (vSwUpdM_ErrorCode)(0x10u)  /*!< Error code: API service called without module being erased before. */
#define VSWUPDM_E_MODULE_STILL_OPENED                   (vSwUpdM_ErrorCode)(0x11u)  /*!< Error code: API service called while a module is still opened. */
#define VSWUPDM_E_SEGMENT_STILL_OPENED                  (vSwUpdM_ErrorCode)(0x12u)  /*!< Error code: API service called while a segment is still opened. */
#define VSWUPDM_E_STREAM_PENDING                        (vSwUpdM_ErrorCode)(0x13u)  /*!< Error code: API service called while a stream is still pending. */
#define VSWUPDM_E_INV_OPERATION_STATE                   (vSwUpdM_ErrorCode)(0x14u)  /*!< Error code: API service called while component is in an invalid operation state. */

#define VSWUPDM_E_PENDING                               (Std_ReturnType)(0x02u)     /*!< Result is pending */
#define VSWUPDM_E_BUSY                                  (Std_ReturnType)(0x03u)     /*!< Callee is currently busy, retry later */
#define VSWUPDM_E_SUSPENDED                             (Std_ReturnType)(0x04u)     /*!< Operation is suspended. Used for upper-layer confirmation function. */

#define VSWUPDM_E_INV_STATE                               (Std_ReturnType)(0x10u)
#define VSWUPDM_E_MEM_UNMAPPED                            (Std_ReturnType)(0x11u)
#define VSWUPDM_E_MEM_UNALIGNED_ADDRESS                   (Std_ReturnType)(0x12u)
#define VSWUPDM_E_MEM_UNALIGNED_LENGTH                    (Std_ReturnType)(0x13u)
#define VSWUPDM_E_MEM_FAILED                              (Std_ReturnType)(0x14u)
#define VSWUPDM_E_MEM_READ                                (Std_ReturnType)(0x15u)
#define VSWUPDM_E_MEM_READ_CORRECTED_ERRORS               (Std_ReturnType)(0x16u)
#define VSWUPDM_E_MEM_READ_UNCORRECTABLE_ERRORS           (Std_ReturnType)(0x17u)
#define VSWUPDM_E_MEM_WRITE                               (Std_ReturnType)(0x18u)
#define VSWUPDM_E_MEM_ERASE                               (Std_ReturnType)(0x19u)
#define VSWUPDM_E_CALLOUT_FAILED                          (Std_ReturnType)(0x1Au)
#define VSWUPDM_E_HOOK_FAILED                             (Std_ReturnType)(0x1Bu)
#define VSWUPDM_E_HOOK_UNSUPPORTED_ACTION                 (Std_ReturnType)(0x1Cu)
#define VSWUPDM_E_SEGMENTS_EXCEEDED                       (Std_ReturnType)(0x1Du)
#define VSWUPDM_E_JOB_INVALID_CHILD_RESULT                (Std_ReturnType)(0x1Eu)
#define VSWUPDM_E_JOB_CHILD_RESULT_NOT_EVALUATED          (Std_ReturnType)(0x1Fu)
#define VSWUPDM_E_INIT_FAILED                             (Std_ReturnType)(0x20u)
#define VSWUPDM_E_INVALID_SEGMENT_STATE                   (Std_ReturnType)(0x21u)
#define VSWUPDM_E_INVALID_STREAM_STATE                    (Std_ReturnType)(0x22u)
#define VSWUPDM_E_INVALID_STREAM_OPERATION                (Std_ReturnType)(0x23u)
#define VSWUPDM_E_REMOTE_RESPONSE_WRONG_SERVICE           (Std_ReturnType)(0x26u)
#define VSWUPDM_E_REMOTE_CHECK_PARTITION_FAILED           (Std_ReturnType)(0x28u)
#define VSWUPDM_E_STREAM_OPERATION_FAILED                 (Std_ReturnType)(0x29u)
#define VSWUPDM_E_REMOTE_VALIDATE_PARTITION_FAILED        (Std_ReturnType)(0x2Au)
#define VSWUPDM_E_COMPARE_FAILED                          (Std_ReturnType)(0x2Bu)
#define VSWUPDM_E_REMOTE_INVALIDATE_PARTITION_FAILED      (Std_ReturnType)(0x2Cu)
#define VSWUPDM_E_REMOTE_SYNC_PARTITION_FAILED            (Std_ReturnType)(0x2Du)
#define VSWUPDM_E_RESPONSE_ALREADY_LOCKED                 (Std_ReturnType)(0x2Eu)
#define VSWUPDM_E_RESPONSE_UNKNOWN_SOURCE                 (Std_ReturnType)(0x2Fu)
#define VSWUPDM_E_RESPONSE_PRIVILEGE                      (Std_ReturnType)(0x30u)
#define VSWUPDM_E_REMOTE_SWAP_PARTITION_FAILED            (Std_ReturnType)(0x31u)
#define VSWUPDM_E_REMOTE_SUSPEND_FAILED                   (Std_ReturnType)(0x33u)
#define VSWUPDM_E_REMOTE_RESUME_FAILED                    (Std_ReturnType)(0x34u)
#define VSWUPDM_E_REMOTE_OPEN_MODULE_FAILED               (Std_ReturnType)(0x35u)
#define VSWUPDM_E_REMOTE_CLOSE_MODULE_FAILED              (Std_ReturnType)(0x36u)
#define VSWUPDM_E_REMOTE_FINALIZE_MODULE_FAILED           (Std_ReturnType)(0x37u)
#define VSWUPDM_E_REMOTE_SYNC_MODULE_FAILED               (Std_ReturnType)(0x38u)
#define VSWUPDM_E_REMOTE_START_FAILED                     (Std_ReturnType)(0x39u)
#define VSWUPDM_E_REMOTE_VALIDATE_MODULE_FAILED           (Std_ReturnType)(0x3Au)
#define VSWUPDM_E_REMOTE_INVALIDATE_MODULE_FAILED         (Std_ReturnType)(0x3Bu)
#define VSWUPDM_E_REMOTE_ERASE_REGION_FAILED              (Std_ReturnType)(0x3Cu)
#define VSWUPDM_E_REMOTE_ADD_SEGMENT_FAILED               (Std_ReturnType)(0x3Du)
#define VSWUPDM_E_REMOTE_OPEN_SEGMENT_FAILED              (Std_ReturnType)(0x3Eu)
#define VSWUPDM_E_REMOTE_CLOSE_SEGMENT_FAILED             (Std_ReturnType)(0x3Fu)
#define VSWUPDM_E_REMOTE_CLEAR_SEGMENTS_OF_MODULE_FAILED  (Std_ReturnType)(0x40u)
#define VSWUPDM_E_REMOTE_FINALIZE_SEGMENT_FAILED          (Std_ReturnType)(0x41u)
#define VSWUPDM_E_REMOTE_SERVICE_TARGET_NOT_PROCESSING    (Std_ReturnType)(0x42u)
#define VSWUPDM_E_REMOTE_SERVICE_TARGET_PROCESSING        (Std_ReturnType)(0x43u)
#define VSWUPDM_E_REMOTE_START_STREAM_FAILED              (Std_ReturnType)(0x44u)
#define VSWUPDM_E_REMOTE_ENUM_CONVERSION_FAILED           (Std_ReturnType)(0x45u)
#define VSWUPDM_E_REMOTE_CONFIRMATION_TX_FAILED           (Std_ReturnType)(0x46u)
#define VSWUPDM_E_REMOTE_WRONG_PIPE                       (Std_ReturnType)(0x47u)
#define VSWUPDM_E_REMOTE_PIPE_NUMBER_OF_INPUTS            (Std_ReturnType)(0x48u)
#define VSWUPDM_E_REMOTE_SERVICE_FAILED                   (Std_ReturnType)(0x49u)
#define VSWUPDM_E_REMOTE_LOCAL_TX_TP_ERROR                (Std_ReturnType)(0x4Au)
#define VSWUPDM_E_REMOTE_NEGATIVE_ACK                     (Std_ReturnType)(0x4Bu)
#define VSWUPDM_E_REMOTE_ACK_TIMEOUT                      (Std_ReturnType)(0x4Cu)
#define VSWUPDM_E_PROGRAMMING_ATTEMPTS_EXCEEDED           (Std_ReturnType)(0x4Du)
#define VSWUPDM_E_REMOTE_ERASE_MODULE_FAILED              (Std_ReturnType)(0x4Eu)
#define VSWUPDM_E_REMOTE_OPEN_PARTITION_FAILED            (Std_ReturnType)(0x4Fu)
#define VSWUPDM_E_REMOTE_VERIFY_MODULE_FAILED             (Std_ReturnType)(0x50u)
#define VSWUPDM_E_REMOTE_VERIFY_SEGMENT_FAILED            (Std_ReturnType)(0x51u)
#define VSWUPDM_E_REMOTE_REQUEST_PROCESS_INFO             (Std_ReturnType)(0x52u)
#define VSWUPDM_E_REMOTE_CONCLUDE_SEGMENT                 (Std_ReturnType)(0x53u)
#define VSWUPDM_E_REMOTE_STREAM_SEMAPHOR                  (Std_ReturnType)(0x54u)
#define VSWUPDM_E_REMOTE_LOCK_FAILED                      (Std_ReturnType)(0x55u)
#define VSWUPDM_E_REMOTE_UNLOCK_FAILED                    (Std_ReturnType)(0x56u)
#define VSWUPDM_E_REMOTE_END_STREAM_FAILED                (Std_ReturnType)(0x57u)
#define VSWUPDM_E_REMOTE_STREAM_FAILED                    (Std_ReturnType)(0x58u)
#define VSWUPDM_E_REMOTE_INDICATE_WRITE_TO_MODULE_FAILED  (Std_ReturnType)(0x59u)
#define VSWUPDM_E_REMOTE_RESPONSE_TIMEOUT                 (Std_ReturnType)(0x60u)
#define VSWUPDM_E_REMOTE_PROCESS_MODULE_FAILED            (Std_ReturnType)(0x61u)

/* vSwUpdM_PartitionStateType */
#define VSWUPDM_PART_STATE_UNDEFINED              (vSwUpdM_PartitionStateType)(0x00u)     /*!< Partition State: Undefined */
#define VSWUPDM_PART_STATE_ACTIVE                 (vSwUpdM_PartitionStateType)(1u << 0u)  /*!< Partition State: Active */
#define VSWUPDM_PART_STATE_INACTIVE               (vSwUpdM_PartitionStateType)(1u << 1u)  /*!< Partition State: Inactive */
#define VSWUPDM_PART_STATE_BACKUP_TARGET          (vSwUpdM_PartitionStateType)(1u << 2u)  /*!< Partition State: Backup target */
#define VSWUPDM_PART_STATE_BACKUP_SOURCE          (vSwUpdM_PartitionStateType)(1u << 3u)  /*!< Partition State: Backup source */
#define VSWUPDM_PART_STATE_ACTIVATION_PENDING     (vSwUpdM_PartitionStateType)(1u << 4u)  /*!< Partition State: Activation pending */

#define VSWUPDM_VALIDITY_INVALID          FALSE
#define VSWUPDM_VALIDITY_VALID            TRUE

#define VSWUPDM_MAX_NUMBER_OF_PARTITIONS  (vSwUpdM_GetStaticNumberOfPartitions() + vSwUpdM_GetDynamicNumberOfPartitions())
#define VSWUPDM_MAX_NUMBER_OF_MODULES     (vSwUpdM_GetStaticNumberOfModules() + vSwUpdM_GetDynamicNumberOfModules())
#define VSWUPDM_MAX_NUMBER_OF_REGIONS     (vSwUpdM_GetStaticNumberOfRegions() + vSwUpdM_GetDynamicNumberOfRegions())
#define VSWUPDM_MAX_NUMBER_OF_SEGMENTS    (vSwUpdM_GetStaticNumberOfSegments() + vSwUpdM_GetDynamicNumberOfSegments())

/* vSwUpdM_StateType */
#define VSWUPDM_STATE_INIT_PENDING        (vSwUpdM_StateType)(0x00u)
#define VSWUPDM_STATE_IDLE                (vSwUpdM_StateType)(0x01u)
#define VSWUPDM_STATE_ACTIVE              (vSwUpdM_StateType)(0x02u)
#define VSWUPDM_STATE_PENDING             (vSwUpdM_StateType)(0x03u)
#define VSWUPDM_STATE_SUSPEND_PENDING     (vSwUpdM_StateType)(0x04u)
#define VSWUPDM_STATE_SUSPENDED           (vSwUpdM_StateType)(0x05u)
#define VSWUPDM_STATE_SUSPENDING          (vSwUpdM_StateType)(0x06u)
#define VSWUPDM_STATE_SHUT_DOWN_PENDING   (vSwUpdM_StateType)(0x07u)
#define VSWUPDM_STATE_SHUT_DOWN           (vSwUpdM_StateType)(0x08u)

/* vSwUpdM_UpdateStateType */
#define VSWUPDM_UPDATE_STATE_UNDEFINED    (vSwUpdM_StateType)(0x00u)
#define VSWUPDM_UPDATE_STATE_IDLE         (vSwUpdM_StateType)(0x01u)
#define VSWUPDM_UPDATE_STATE_ACTIVE       (vSwUpdM_StateType)(0x02u)
#define VSWUPDM_UPDATE_STATE_SWAP         (vSwUpdM_StateType)(0x03u)

/* vSwUpdM_ResumeStateType */
#define VSWUPDM_RESUME_STATE_UNDEFINED    (vSwUpdM_StateType)(0x00u)
#define VSWUPDM_RESUME_STATE_STARTED      (vSwUpdM_StateType)(0x01u)
#define VSWUPDM_RESUME_STATE_PENDING      (vSwUpdM_StateType)(0x02u)
#define VSWUPDM_RESUME_STATE_ACTIVE       (vSwUpdM_StateType)(0x03u)
#define VSWUPDM_RESUME_STATE_FINISHED     (vSwUpdM_StateType)(0x04u)
#define VSWUPDM_RESUME_STATE_FAILED       (vSwUpdM_StateType)(0x05u)

/* vSwUpdM_ModuleStateType */
#define VSWUPDM_MODULE_STATE_UNDEFINED          (vSwUpdM_ModuleStateType)(0x00u)
#define VSWUPDM_MODULE_STATE_ERASED             (vSwUpdM_ModuleStateType)(0x01u)
#define VSWUPDM_MODULE_STATE_ERASE_PENDING      (vSwUpdM_ModuleStateType)(0x02u)
#define VSWUPDM_MODULE_STATE_DIRTY              (vSwUpdM_ModuleStateType)(0x03u)
#define VSWUPDM_MODULE_STATE_RESTART            (vSwUpdM_ModuleStateType)(0x04u)
#define VSWUPDM_MODULE_STATE_CLEAN              (vSwUpdM_ModuleStateType)(0x05u)
#define VSWUPDM_MODULE_STATE_SYNC_DIRTY         (vSwUpdM_ModuleStateType)(0x06u)
#define VSWUPDM_MODULE_STATE_SYNC_CLEAN         (vSwUpdM_ModuleStateType)(0x07u)
#define VSWUPDM_MODULE_STATE_SYNC_FINISHED      (vSwUpdM_ModuleStateType)(0x08u)
#define VSWUPDM_MODULE_STATE_COMPARE_PENDING    (vSwUpdM_ModuleStateType)(0x09u)
#define VSWUPDM_MODULE_STATE_FINALIZED          (vSwUpdM_ModuleStateType)(0x0Au)
#define VSWUPDM_MODULE_STATE_VERIFIED           (vSwUpdM_ModuleStateType)(0x0Bu)
#define VSWUPDM_MODULE_STATE_PROCESS_STARTED    (vSwUpdM_ModuleStateType)(0x0Cu)
#define VSWUPDM_MODULE_STATE_PROCESS_DIRTY      (vSwUpdM_ModuleStateType)(0x0Du)
#define VSWUPDM_MODULE_STATE_PROCESS_CLEAN      (vSwUpdM_ModuleStateType)(0x0Eu)
#define VSWUPDM_MODULE_STATE_PROCESS_FINISHED   (vSwUpdM_ModuleStateType)(0x0Fu)

/* vSwUpdM_RegionStateType */
#define VSWUPDM_REGION_STATE_UNDEFINED      (vSwUpdM_RegionStateType)(0x00u)
#define VSWUPDM_REGION_STATE_ERASED         (vSwUpdM_RegionStateType)(0x01u)
#define VSWUPDM_REGION_STATE_ERASE_PENDING  (vSwUpdM_RegionStateType)(0x02u)
#define VSWUPDM_REGION_STATE_DIRTY          (vSwUpdM_RegionStateType)(0x03u)
#define VSWUPDM_REGION_STATE_CLEAN          (vSwUpdM_RegionStateType)(0x04u)
#define VSWUPDM_REGION_STATE_FINALIZED      (vSwUpdM_RegionStateType)(0x05u)

/* vSwUpdM_SegmentStateType */
#define VSWUPDM_SEGMENT_STATE_UNDEFINED     (vSwUpdM_SegmentStateType)(0x00u)
#define VSWUPDM_SEGMENT_STATE_ERASED        (vSwUpdM_SegmentStateType)(0x01u)
#define VSWUPDM_SEGMENT_STATE_PENDING       (vSwUpdM_SegmentStateType)(0x02u)
#define VSWUPDM_SEGMENT_STATE_FINALIZED     (vSwUpdM_SegmentStateType)(0x03u)
#define VSWUPDM_SEGMENT_STATE_AUTODETECT    (vSwUpdM_SegmentStateType)(0x04u)
#define VSWUPDM_SEGMENT_STATE_VERIFIED      (vSwUpdM_SegmentStateType)(0x05u)

/* vSwUpdM_StreamStateType */
#define VSWUPDM_STREAM_STATE_IDLE           (vSwUpdM_SegmentStateType)(0x00u)
#define VSWUPDM_STREAM_STATE_PENDING        (vSwUpdM_SegmentStateType)(0x01u)

#define VSWUPDM_INVALID_REVISION            (0xFFFFFFFFu)

/* Invalid identifier for partitions, modules, regions and segments */
#define VSWUPDM_INVALID_ID                  (0xFFFFFFFFu)

#define VSWUPDM_SEGMENT_TYPE_UNUSED         (0x00u)
#define VSWUPDM_SEGMENT_TYPE_FREE           (0x01u)
#define VSWUPDM_SEGMENT_TYPE_RESERVED       (0x02u)

#define VSWUPDM_PARTITION_ID_DEFAULT        VSWUPDM_INVALID_ID
#define VSWUPDM_MODULE_ID_DEFAULT           VSWUPDM_INVALID_ID
#define VSWUPDM_REGION_ID_DEFAULT           VSWUPDM_INVALID_ID
#define VSWUPDM_SEGMENT_ID_DEFAULT          { VSWUPDM_INVALID_ID, VSWUPDM_INVALID_ID }

#define VSWUPDM_STREAM_OPERATION_DEFAULT    0u  /* MODE UNPROCESSED */

#define VSWUPDM_LENGTH_HANDLING_FIXED       ((vSwUpdM_LengthHandlingType)0x00u)
#define VSWUPDM_LENGTH_HANDLING_DYNAMIC     ((vSwUpdM_LengthHandlingType)0x01u)

/* clang-format on */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#if (VSWUPDM_DEV_ERROR_REPORT == STD_ON)
# if !defined vSwUpdM_DetReportError
#  define vSwUpdM_DetReportError(api, err) \
  (void)Det_ReportError(VSWUPDM_MODULE_ID, VSWUPDM_INSTANCE_ID, (api), (err))
# endif
#else
# if !defined vSwUpdM_DetReportError
#  define vSwUpdM_DetReportError(api, err)
# endif
/* PRQA L:FUNCTIONLIKEMACRO */ /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 vSwUpdM_ErrorCode;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * Internal comment removed.
 *
 *
 */
#if (VSWUPDM_USE_INIT_POINTER == STD_ON)
extern P2CONST(vSwUpdM_ConfigType, VSWUPDM_VAR_NOINIT, VSWUPDM_INIT_DATA) vSwUpdM_ConfigDataPtr;
#endif

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**************************************************************
 *  Memory Abstraction:
 *   - Logical View
 *      - Stream
 **************************************************************/
/**********************************************************************************************************************
 *  vSwUpdM_StartStream()
 *********************************************************************************************************************/
/*! \brief       Initializes a download stream.
 *  \details     Notifies the vSwUpdM that a download sequence is started.
 *  \param[in]   StreamInfo    The information about the initialized download sequence.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A module has to be opened prior.
 *  \note        The length specified in StreamInfo is interpreted as not defined if set to 0 (VSWUPDM_UNDEFINED).
 *               Otherwise, it is expected that exactly this length is downloaded within the current download
 *               sequence.
 *  \ingroup     stream
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_StartStream(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ProcessStreamData()
 *********************************************************************************************************************/
/*! \brief       Notifies the vSwUpdM about new data.
 *  \details     Requests that the vSwUpdM collects the data from upper layer as soon as possible.
 *  \param[in]   StreamLength  The number of bytes currently available in the upper layer to download.
 *  \return      E_OK          The requested data length is accepted.
 *  \return      E_NOT_OK      The requested data length is invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A stream has to be started prior.
 *  \ingroup     stream
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcessStreamData(vSwUpdM_StreamLengthType StreamLength);

/**********************************************************************************************************************
 *  vSwUpdM_EndStream()
 *********************************************************************************************************************/
/*! \brief       Ends a download sequence.
 *  \details     Notifies the vSwUpdM that a download sequence is ended.
 *  \return      E_OK          The requested data length is accepted.
 *  \return      E_NOT_OK      The requested data length is invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A stream has to be started prior.
 *  \ingroup     stream
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EndStream(void);

/**********************************************************************************************************************
 *  vSwUpdM_InitStreamInfo()
 *********************************************************************************************************************/
/*! \brief       Initialize stream info with default values.
 *  \details     It is recommended to call this API before calling vSwUpdM_StartStream.
 *  \param[out]  StreamInfo    The information of the stream.
 *  \return      E_OK          The initialization succeeded.
 *  \return      E_NOT_OK      The StreamInfo pointer was invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     stream
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitStreamInfo(
  P2VAR(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo);

/**********************************************************************************************************************
 *  vSwUpdM_SwitchStreamContext()
 *********************************************************************************************************************/
/*! \brief       Switches the stream context.
 *  \details     -
 *  \param[in]   StreamInfo    The updated information about the download sequence.
 *  \return      E_OK          The stream information could be updated.
 *  \return      E_NOT_OK      The stream information could not be updated.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         A stream sequence has to be active.
 *  \ingroup     stream
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SwitchStreamContext(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo);

/**************************************************************
 *  Memory Abstraction:
 *   - Logical View
 *      - State
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_Start()
 *********************************************************************************************************************/
/*! \brief       Request the start of the download sequence.
 *  \details     Confirmation will be issued as soon as background initialization is finished and download sequence
 *               can begin.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Start(void);

/**********************************************************************************************************************
 *  vSwUpdM_Shutdown()
 *********************************************************************************************************************/
/*! \brief       Suspend the download sequence and persist current state.
 *  \details     After restart, either after a reset or re-issuing vSwUpdM_Start(), the download can be resumed at the
 *               current position, e.g. last written memory page.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Shutdown(void);

/**********************************************************************************************************************
 *  vSwUpdM_Abort()
 *********************************************************************************************************************/
/*! \brief       Aborts the current download sequence.
 *  \details     In case any operation is pending, e.g. a write access, it is stopped without the possibility to resume
 *               after restart.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Abort(void);

/**********************************************************************************************************************
 *  vSwUpdM_Suspend()
 *********************************************************************************************************************/
/*! \brief       Suspends a currently active download sequence.
 *  \details     The operation can be resumed later. The suspended state isn't persisted to resume after a reset, but
 *               a shutdown can be requested while being suspended.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         An operation must be pending or vSwUpdM must be idle.
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Suspend(void);

/**********************************************************************************************************************
 *  vSwUpdM_Resume()
 *********************************************************************************************************************/
/*! \brief       Resumes a suspended download sequence.
 *  \details     The operation will continue from the suspended state.
 *  \return      E_OK          The operation succeeded; the pending operation will be resumed.
 *  \return      E_NOT_OK      The operation failed; the resume request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         A pending operation has to be suspended prior.
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Resume(void);

/**********************************************************************************************************************
 *  vSwUpdM_GetState()
 *********************************************************************************************************************/
/*! \brief       Returns the state of the vSwUpdM.
 *  \details     The global state is returned.
 *  \param[out]  State          VSWUPDM_STATE_INIT_PENDING          Initialization of vSwUpdM in progress.
 *                              VSWUPDM_STATE_IDLE                  vSwUpdM is idle, no operation is pending.
 *                              VSWUPDM_STATE_ACTIVE                A pending operation is processed.
 *                              VSWUPDM_STATE_PENDING               An operation is pending.
 *                              VSWUPDM_STATE_SUSPEND_PENDING       A suspend request is pending.
 *                              VSWUPDM_STATE_SUSPENDED             A pending operation was suspended.
 *                              VSWUPDM_STATE_SUSPENDING            A pending operation is suspending.
 *                              VSWUPDM_STATE_SHUT_DOWN_PENDING     A shutdown request is pending.
 *                              VSWUPDM_STATE_SHUT_DOWN             vSwUpdM was shut down.
 *  \return      E_OK           The state could be successfully returned.
 *  \return      E_NOT_OK       The request failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetState(P2VAR(vSwUpdM_StateType, AUTOMATIC, VSWUPDM_APPL_VAR) State);

/**********************************************************************************************************************
 *  vSwUpdM_GetResumeInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the resume information of the vSwUpdM.
 *  \details     The resume information is returned.
 *  \param[out]  ResumeInfo     The resume information
 *  \return      E_OK           The resume information could be successfully returned.
 *  \return      E_NOT_OK       The request failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetResumeInfo(P2VAR(vSwUpdM_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_GetCheckpoint()
 *********************************************************************************************************************/
/*! \brief       Returns the address of the next checkpoint after the given address.
 *  \details     Checkpoints are used to persist the information necessary to resume an operation after an unintended reset.
 *               The checkpoint is evaluated for the currently opened partition.
 *  \param[out]  Checkpoint   The address of the checkpoint.
 *                            Maximum address value if no further checkpoint is configured after given address.
 *  \param[in]   Address      The address which is currently processed.
 *  \return      E_OK         The checkpoint address could be successfully evaluated.
 *  \return      E_NOT_OK     The request failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         A partition must be opened.
 *  \ingroup     state
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetCheckpoint(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) Checkpoint,
  vSwUpdM_AddressType Address);

/**************************************************************
 *  Memory Abstraction:
 *   - Partitions
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_ValidatePartition()
 *********************************************************************************************************************/
/*! \brief       Validates the opened partition.
 *  \details     Sets the whole partition to valid.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         Allowed on inactive or backup target partition. All corresponding modules must also be valid.
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ValidatePartition(void);

/**********************************************************************************************************************
 *  vSwUpdM_InvalidatePartition()
 *********************************************************************************************************************/
/*! \brief       Invalidates the opened partition.
 *  \details     Sets the whole partition to invalid. Afterwards the whole partition has to be erased and re-written
 *               before activation is possible. Invalidates all corresponding modules.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InvalidatePartition(void);

/**********************************************************************************************************************
 *  vSwUpdM_SyncPartition()
 *********************************************************************************************************************/
/*! \brief       Synchronizes the opened partitions.
 *  \details     Copies data from active and swappable partition to the opened partition.
 *               Typically the opened partition is either the inactive partition (take over modules which weren't updated)
 *               or the backup target (creation of backup of active software).
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SyncPartition(void);

/**********************************************************************************************************************
 *  vSwUpdM_CheckPartitionConsistency()
 *********************************************************************************************************************/
/*! \brief       Verify partition and checks the consistency of the opened partition.
 *  \details     A partition has to be consistent before it is swapped to active.
 *  \param[in]   ProcessInfo   Pointer to the processing information structure.
 *               - InputCount                                  Number of input data buffers.
 *               - OutputCount                                 Number of output data buffers.
 *               - Operation                                   Determines actual pipe mode.
 *               - InputData->DataPtr                          Pointer to the data buffer provided by user.
 *               - InputData->Length                           Total buffer size provided by user.
 *               - OutputData->DataPtr                         Pointer to the data buffer provided by the user.
 *               - OutputData->AvailableLength                 Length of data that was actually provided by vSwUpdM.
 *               - OutputData->BufferSize                      Total buffer size provided by user.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \note        This check is only useful for inactive or backup partitions.
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CheckPartitionConsistency(P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_SwapActivePartition()
 *********************************************************************************************************************/
/*! \brief       Requests a swap from currently active partition to opened partition.
 *  \details     Module instances in opened partition will be active after next restart.
 *               The opened partition can be
 *               - The inactive partition: Activate newly updated software.
 *               - The backup source: Perform rollback to earlier software version.
 *               - The active partition: Early rollback, when activation was requested, but not performed yet.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SwapActivePartition(void);

/**********************************************************************************************************************
 *  vSwUpdM_OpenPartition()
 *********************************************************************************************************************/
/*! \brief       Opens the specified partition.
 *  \details     All following operations to modules, regions, segments and ranges are based on the opened partition.
 *  \param[in]   State         The state of the partition to be opened.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         All operations on the prior opened partitions must be finished.
 *  \note        There is always an open partition, therefore there is no API for closing a partition. The closing is
 *               performed implicitly during opening a new partition.
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenPartition(vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_GetPartitionStateByHandle()
 *********************************************************************************************************************/
/*! \brief       Returns the partition specific information.
 *  \details     Get the partition identifier based on the given handle.
 *  \param[out]  PartitionState Identifier of the partition.
 *  \param[in]   HandleId      The handle id of the partition.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetPartitionStateByHandle(
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionState,
  vSwUpdM_PartitionHandleIdType HandleId);

/**********************************************************************************************************************
 * vSwUpdM_GetOpenPartitionState
 **********************************************************************************************************************/
/*! \brief       Returns the partition specific information.
 *  \details     Returns the identifier of partition, which is currently opened.
 *  \param[out]  PartitionState State of the partition.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenPartitionState(
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionState);

/**********************************************************************************************************************
 *  vSwUpdM_GetPartitionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the partition specific information.
 *  \details     Returns the information of specified id.
 *  \param[out]  PartitionInfo Infos of the partition.
 *  \param[in]   State         The state of the partition.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetPartitionInfo(
  P2VAR(vSwUpdM_PartitionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionInfo,
  vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_IsPartitionErasable()
 *********************************************************************************************************************/
/*! \brief       Indicates if partition is erasable.
 *  \details     -
 *  \param[in]   State         The state of the partition.
 *  \return      FALSE         The complete partition or parts of it aren't erasable.
 *  \return      TRUE          The complete partition is erasable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionErasable(vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_IsPartitionReadable()
 *********************************************************************************************************************/
/*! \brief       Indicates if partition is readable.
 *  \details     -
 *  \param[in]   State         The state of the partition.
 *  \return      FALSE         At least one byte of the partition is not readable.
 *  \return      TRUE          The complete partition is readable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionReadable(vSwUpdM_PartitionStateType State);

/**********************************************************************************************************************
 *  vSwUpdM_IsPartitionWritable()
 *********************************************************************************************************************/
/*! \brief       Indicates if partition is writable.
 *  \details     -
 *  \param[in]   State         The state of the partition.
 *  \return      FALSE         The complete partition or parts of it aren't writable.
 *  \return      TRUE          The complete partition is writable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionWritable(vSwUpdM_PartitionStateType State);

/**************************************************************
 *  Memory Abstraction:
 *   - Module
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_OpenModule()
 *********************************************************************************************************************/
/*! \brief       Opens the specified module.
 *  \details     Notify the vSwUpdM to which module the following region, segment and stream specific commands
 *               are assigned to.
 *  \param[in]   Id            The module to be opened.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         All modules must be closed.
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_CloseModule()
 *********************************************************************************************************************/
/*! \brief       Closes the specified module.
 *  \details     After closing write access to this module is not allowed anymore.
 *  \param[in]   Id            The identifier of the module.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         The specified module has to be opened prior. All requests on this module have to be finished prior.
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CloseModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_ValidateModule()
 *********************************************************************************************************************/
/*! \brief       Validates the specified module.
 *  \details     Sets the module to valid.
 *  \param[in]   Id            The module to be validated.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ValidateModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_InvalidateModule()
 *********************************************************************************************************************/
/*! \brief       Invalidates the specified module.
 *  \details     An invalidated module must be erased and re-written before using again.
 *  \param[in]   Id            The module to be invalidated.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InvalidateModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_EraseModule()
 *********************************************************************************************************************/
/*! \brief       Erases memory of all regions mapped to the specified module.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_FinalizeModule()
 *********************************************************************************************************************/
/*! \brief       Finalize module by filling all memory not written yet with pattern.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_FinalizeModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_VerifyModule()
 *********************************************************************************************************************/
/*! \brief       Verify module by triggering verification actions and collect results.
 *  \details     The module is identified by the specified handle id.
 *  \param[in]   Id            The id of the module.
 *  \param[in]   ProcessInfo   Pointer to the processing information structure.
 *               - InputCount                                  Number of input data buffers.
 *               - OutputCount                                 Number of output data buffers.
 *               - Operation                                   Determines actual pipe mode.
 *               - InputData->DataPtr                          Pointer to the data buffer provided by user.
 *               - InputData->Length                           Total buffer size provided by user.
 *               - OutputData->DataPtr                         Pointer to the data buffer provided by the user.
 *               - OutputData->AvailableLength                 Length of data that was actually provided by vSwUpdM.
 *               - OutputData->BufferSize                      Total buffer size provided by user.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_VerifyModule(vSwUpdM_ModuleIdType Id, P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_SyncModule()
 *********************************************************************************************************************/
/*! \brief       Synchronizes the specified module.
 *  \details     The content of the active module is copied to the instance in the opened partition.
 *  \param[in]   Id            The module to be synchronized.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SyncModule(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_GetModuleIdByHandle()
 *********************************************************************************************************************/
/*! \brief         Returns the module specific identifier.
 *  \details       The module is identified by the specified handle id.
 *  \param[out]    ModuleId      Id of the module.
 *  \param[in]     HandleId      The handle id of the module.
 *  \return        E_OK          The operation succeeded; the data could be returned.
 *  \return        E_NOT_OK      The operation failed; the request was rejected.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleIdByHandle(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId,
  vSwUpdM_ModuleHandleIdType HandleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetModuleIdByRange()
 *********************************************************************************************************************/
/*! \brief         Returns the module specific identifier.
 *  \details       The module is identified by the specified address range.
 *  \param[out]    ModuleId      Id of the module.
 *  \param[in]     StartAddress  The start address of the memory range to identify the module.
 *  \param[in]     Length        The length of the memory range to identify the module.
 *  \return        E_OK          The operation succeeded; the data could be returned.
 *  \return        E_NOT_OK      The operation failed; the request was rejected.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleIdByRange(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 * vSwUpdM_GetOpenModuleId
 **********************************************************************************************************************/
/*! \brief       Returns the module specific information.
 *  \details     Returns the identifier of module, which is currently opened.
 *  \param[out]  ModuleId      Identifier of the module.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenModuleId(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetModuleInfo()
 *********************************************************************************************************************/
/*! \brief         Returns the module specific information.
 *  \details       The module is identified by the specified id.
 *  \param[out]    ModuleInfo    Infos of the module.
 *  \param[in]     Id            The id of the module.
 *  \return        E_OK          The operation succeeded; the data could be returned.
 *  \return        E_NOT_OK      The operation failed; the request was rejected.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleInfo(
  P2VAR(vSwUpdM_ModuleInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleInfo,
  vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_GetNumberOfModules()
 *********************************************************************************************************************/
/*! \brief         Returns the number of configured modules.
 *  \details       -
 *  \param[out]    The number of modules.
 *  \return        E_OK          The operation succeeded; the data could be returned.
 *  \return        E_NOT_OK      The operation failed; the request was rejected.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfModules(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfModules);

/**********************************************************************************************************************
 *  vSwUpdM_IsModuleErasable()
 *********************************************************************************************************************/
/*! \brief       Indicates if module is erasable.
 *  \details     -
 *  \param[in]   Id            The id of the module.
 *  \return      FALSE         The complete module or parts of it aren't erasable.
 *  \return      TRUE          The complete module is erasable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleErasable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_IsModuleReadable()
 *********************************************************************************************************************/
/*! \brief       Indicates if module is readable.
 *  \details     -
 *  \param[in]   Id            The id of the module.
 *  \return      FALSE         At least one byte of the module is not readable.
 *  \return      TRUE          The complete module is readable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleReadable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_IsModuleWritable()
 *********************************************************************************************************************/
/*! \brief       Indicates if module is writable.
 *  \details     -
 *  \param[in]   Id            The id of the module.
 *  \return      FALSE         The complete module or parts of it aren't writable.
 *  \return      TRUE          The complete module is writable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleWritable(vSwUpdM_ModuleIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_ProcessModule()
 *********************************************************************************************************************/
/*! \brief       Cause spawning a job, which processing a stream processor pipe of scope module.
 *  \details     -
 *  \param[in]   ModuleId      The id of the module.
 *  \param[in]   ProcessId     The id of the process (refers to a stream processor pipe).
 *  \param[in]   ProcessInfo   Pointer to the processing information structure.
 *               - InputCount                                  Number of input data buffers.
 *               - OutputCount                                 Number of output data buffers.
 *               - Operation                                   Determines actual pipe mode.
 *               - InputData->DataPtr                          Pointer to the data buffer provided by user.
 *               - InputData->Length                           Total buffer size provided by user.
 *               - OutputData->DataPtr                         Pointer to the data buffer provided by the user.
 *               - OutputData->AvailableLength                 Length of data that was actually provided by vSwUpdM.
 *               - OutputData->BufferSize                      Total buffer size provided by user.
 *  \return      E_OK          Process successfully finished.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcessModule(vSwUpdM_ModuleIdType ModuleId, vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_IndicateWriteToModule()
 *********************************************************************************************************************/
/*! \brief       Indicate that the module contents are going to be modified outside of the normal update sequence.
 *  \details     State of module and all of the assigned regions is changed from "erased" to "clean".
 *  \param[in]   ModuleId      The id of the module.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         Module and assigned regions are either in state "erased" or "clean".
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_IndicateWriteToModule(vSwUpdM_ModuleIdType ModuleId);

/**************************************************************
 *  Memory Abstraction:
 *   - Region
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_EraseRegion()
 *********************************************************************************************************************/
/*! \brief       Erases memory of all segments mapped to the specified region.
 *  \details     The region is identified by the specified handle id.
 *  \param[in]   Id            The identifier of the region.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseRegion(vSwUpdM_RegionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_GetNumberOfRegionsOfModule()
 *********************************************************************************************************************/
/*! \brief       Returns the number of all regions assigned to the specified module.
 *  \details     -
 *  \param[out]  NumberOfRegions  The number of regions assigned to the specified module.
 *  \param[in]   ModuleId         The module id of which the number of segments is requested.
 *  \return      E_OK             The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK         The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfRegionsOfModule(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfRegions,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetRegionIdByHandle()
 *********************************************************************************************************************/
/*! \brief       Returns the region specific identifier.
 *  \details     The region is identified by the specified handle id.
 *  \param[out]  RegionId      Id of the region.
 *  \param[in]   HandleId      The id of the region.
 *  \return      E_OK          The operation succeeded; the handle was valid.
 *  \return      E_NOT_OK      The operation failed; the handle was invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdByHandle(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_RegionHandleIdType HandleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetRegionIdByRange()
 *********************************************************************************************************************/
/*! \brief       Returns the region specific identifier.
 *  \details     The region is identified corresponding to the specified memory range.
 *  \param[out]  RegionId      Id of the region laying within the specified memory range.
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      E_OK          The operation succeeded; the specified range was valid.
 *  \return      E_NOT_OK      The operation failed; the specified range was invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdByRange(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_GetRegionIdOfModuleByIndex()
 *********************************************************************************************************************/
/*! \brief       Returns the region specific identifier.
 *  \details     Expects a valid module id and the index of a corresponding region.
 *  \param[out]  RegionId      Id of the region.
 *  \param[in]   ModuleId      The module id.
 *  \param[in]   Index         The index of the region corresponding to the specified module.
 *  \return      E_OK          A valid region id could be returned.
 *  \return      E_NOT_OK      No valid region found.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdOfModuleByIndex(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 Index);

/**********************************************************************************************************************
 *  vSwUpdM_GetRegionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the region specific information.
 *  \details     The region is identified corresponding to the specified identifier.
 *  \param[out]  RegionInfo    Infos of the region.
 *  \param[in]   Id            The identifier of the region.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionInfo(
  P2VAR(vSwUpdM_RegionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionInfo,
  vSwUpdM_RegionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_IsRegionErasable()
 *********************************************************************************************************************/
/*! \brief       Indicates if region is erasable.
 *  \details     -
 *  \param[in]   Id            The identifier of the region.
 *  \return      FALSE         The complete region or parts of it aren't erasable.
 *  \return      TRUE          The complete region is erasable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionErasable(vSwUpdM_RegionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_IsRegionReadable()
 *********************************************************************************************************************/
/*! \brief       Indicates if region is readable.
 *  \details     -
 *  \param[in]   Id            The identifier of the region.
 *  \param[in]   Length        The length of the region.
 *  \return      FALSE         At least one byte of the region is not readable.
 *  \return      TRUE          The complete region is readable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionReadable(vSwUpdM_RegionIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_IsRegionWritable()
 *********************************************************************************************************************/
/*! \brief       Indicates if region is writable.
 *  \details     -
 *  \param[in]   Id            The identifier of the region.
 *  \return      FALSE         The complete region or parts of it aren't writable.
 *  \return      TRUE          The complete region is writable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     region
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionWritable(vSwUpdM_RegionIdType Id);

/**************************************************************
 *  Memory Abstraction:
 *   - Segment
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_OpenSegment()
 *********************************************************************************************************************/
/*! \brief       Opens the specified segment.
 *  \details     An opened segment can be written to.
 *  \param[in]   Id            The identifier of the segment.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenSegment(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_CloseSegment()
 *********************************************************************************************************************/
/*! \brief       Closes the specified segment.
 *  \details     After closing write access to this segment is not allowed anymore.
 *  \param[in]   Id            The identifier of the segment.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CloseSegment(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_AddSegment()
 *********************************************************************************************************************/
/*! \brief       Adds a segment to the covering region corresponding to the specified range.
 *  \details     -
 *  \param[in,out] SegmentInfo The segment info containing the range of the segment.
 *  \return      E_OK          The creation succeeded.
 *  \return      E_NOT_OK      The creation failed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo);

/**********************************************************************************************************************
 *  vSwUpdM_AddFinalizedSegment()
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AddFinalizedSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo);

/**********************************************************************************************************************
 *  vSwUpdM_FinalizeSegment()
 *********************************************************************************************************************/
/*! \brief       Finalize segment by writing any remainder.
 *  \details     -
 *  \param[in]   Id            The id of the segment.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_FinalizeSegment(vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
*  vSwUpdM_VerifySegment()
*********************************************************************************************************************/
/*! \brief       Verify segment by triggering verification actions and collect results.
 *  \details     The segment is identified by the specified handle id.
 *  \param[in]   Id            The id of the segment.
 *  \param[in]   ProcessInfo   Pointer to the processing information structure.
 *               - InputCount                                  Number of input data buffers.
 *               - OutputCount                                 Number of output data buffers.
 *               - Operation                                   Determines actual pipe mode.
 *               - InputData->DataPtr                          Pointer to the data buffer provided by user.
 *               - InputData->Length                           Total buffer size provided by user.
 *               - OutputData->DataPtr                         Pointer to the data buffer provided by the user.
 *               - OutputData->AvailableLength                 Length of data that was actually provided by vSwUpdM.
 *               - OutputData->BufferSize                      Total buffer size provided by user.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     module
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_VerifySegment(vSwUpdM_SegmentIdType Id, P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_ClearSegmentsOfModule()
 *********************************************************************************************************************/
/*! \brief       Clears content of all segments assigned to the specified module.
 *  \details     -
 *  \param[in]   ModuleId      The module id of which all segments are cleared.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ClearSegmentsOfModule(vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetNumberOfSegmentsOfModule()
 *********************************************************************************************************************/
/*! \brief       Returns the number of all segments assigned to the specified module.
 *  \details     -
 *  \param[out]  NumberOfSegments   The number of segments assigned to the specified module.
 *  \param[in]   ModuleId           The module id of which the number of segments is requested.
 *  \return      E_OK               The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK           The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfSegmentsOfModule(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfSegments,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  vSwUpdM_GetSegmentIdByRange()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     The segment is specified by a range.
 *  \param[out]  SegmentId     The id of the segment within the specified range.
 *  \param[in]   StartAddress  The start address of the range.
 *  \param[in]   Length        The length of the range.
 *  \return      E_OK          A single segment was found within the range.
 *  \return      E_NOT_OK      No or multiple segments were found within the range.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdByRange(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_GetSegmentIdOfModuleByIndex()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     Expects a valid module id and the index of a corresponding segment.
 *  \param[out]  SegmentId     The segment identifier containing the range of the segment.
 *  \param[in]   ModuleId      The module id.
 *  \param[in]   Index         The index of the segment corresponding to the specified module.
 *  \return      E_OK          A valid segment id could be returned.
 *  \return      E_NOT_OK      No valid segment founds.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdOfModuleByIndex(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 Index);

/**********************************************************************************************************************
 *  vSwUpdM_GetSegmentIdOfModuleByType()
 *********************************************************************************************************************/
/*! \brief       Returns the segment identifier.
 *  \details     Expects a valid module id and the segment type of a corresponding segment.
 *  \param[out]  SegmentId     The segment identifier containing the range of the segment.
 *  \param[in]   ModuleId      The module id.
 *  \param[in]   SegmentType   The segment type.
 *  \return      E_OK          A valid segment id could be returned.
 *  \return      E_NOT_OK      No valid segment founds.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdOfModuleByType(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentTypeType SegmentType);

/**********************************************************************************************************************
 * vSwUpdM_GetOpenSegmentId
 **********************************************************************************************************************/
/*! \brief       Returns the segment specific information.
 *  \details     Returns the identifier of segment, which is currently opened.
 *  \param[out]  SegmentId     Identifier of the segment.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     partition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenSegmentId(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId);

/**********************************************************************************************************************
 *  vSwUpdM_GetSegmentInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the information of the specified segment.
 *  \details     -
 *  \param[out]  SegmentInfo   The info of the specified segment.
 *  \param[in]   Id            The id of the segment.
 *  \return      E_OK          The operation succeeded; the data could be returned.
 *  \return      E_NOT_OK      The operation failed; the request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_SegmentIdType Id);

/**********************************************************************************************************************
 *  vSwUpdM_InitSegmentInfo()
 *********************************************************************************************************************/
/*! \brief       Initialize segment info with default values.
 *  \details     It is recommended to call this API before calling vSwUpdM_AddSegment.
 *  \param[out]  SegmentInfo   The information of the segment.
 *  \return      E_OK          The initialization succeeded.
 *  \return      E_NOT_OK      The SegmentInfo pointer was invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     segment
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitSegmentInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo);

/**************************************************************
 *  Memory Abstraction:
 *   - Memory Range
 **************************************************************/

/**********************************************************************************************************************
 *  vSwUpdM_EraseRange()
 *********************************************************************************************************************/
/*! \brief       Erases the memory within a specific memory range.
 *  \details     -
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseRange(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_ReadRange()
 *********************************************************************************************************************/
/*! \brief       Reads in the data within memory range.
 *  \details     Copies the memory data to a buffer provided by upper layer.
 *  \param[out]  TargetBuffer  The target buffer to where the data is copied.
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      E_OK          The operation succeeded; the service request was successfully forwarded.
 *  \return      else          The operation failed; the service request was rejected.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ReadRange(
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) TargetBuffer,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_WriteRange()
 *********************************************************************************************************************/
/*! \brief       Writes data into the memory range.
 *  \details     Writes the data from the given buffer to the memory range.
 *  \param[out]  SourceBuffer  The source buffer containing the data to be written in the range.
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      E_NOT_OK      Service currently not supported, always returns error.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_WriteRange(
  P2CONST(uint8, AUTOMATIC, VSWUPDM_APPL_CONST) SourceBuffer,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_IsRangeErasable()
 *********************************************************************************************************************/
/*! \brief       Indicates if memory range is erasable.
 *  \details     -
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      FALSE         The complete memory range or parts of it aren't erasable.
 *  \return      TRUE          The complete memory range is erasable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeErasable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_IsRangeReadable()
 *********************************************************************************************************************/
/*! \brief       Indicates if memory range is readable.
 *  \details     -
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      FALSE         At least one byte of the range is not readable.
 *  \return      TRUE          The complete memory range is readable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeReadable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_IsRangeWritable()
 *********************************************************************************************************************/
/*! \brief       Indicates if memory range is writable.
 *  \details     -
 *  \param[in]   StartAddress  The start address of the memory range.
 *  \param[in]   Length        The length of the memory range.
 *  \return      FALSE         The complete memory or parts of it aren't writable.
 *  \return      TRUE          The complete memory range is writable.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeWritable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length);

/**********************************************************************************************************************
 *  vSwUpdM_AlignAddress()
 *********************************************************************************************************************/
 /*! \brief       Align address to memory device constraints.
 *  \details     -
 *  \param[in,out] Address     Input: The address to be aligned. Output: The aligned address.
 *  \param[in]   State         The state of the partition.
 *  \param[in]   Alignment     VSWUPDM_ADDRESS_ALIGNMENT_FRONT:
 *                             Align address to front of range defined by device constraint.
 *                             VSWUPDM_ADDRESS_ALIGNMENT_BACK:
 *                             Align address to end of range defined by device constraint.
 *  \param[in]   Granularity   VSWUPDM_ALIGN_GRANULARITY_PAGE:
 *                             Align address to page size of device.
 *                             VSWUPDM_ALIGN_GRANULARITY_SECTOR:
 *                             Align address to sector size of device.
 *  \return      E_OK          Address successfully aligned.
 *  \return      else          Alignment of address failed, e.g. because no device mapped to it.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     range
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AlignAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_CONST) Address,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_AddressAlignmentType Alignment,
  vSwUpdM_AlignGranularityType Granularity);

/**********************************************************************************************************************
 *  vSwUpdM_GetPaddingValue()
 *********************************************************************************************************************/
 /*! \brief       Returns the configured padding value.
  *  \details     -
  *  \param[out]  PaddingValue  Pointer to where to store the padding value.
  *  \return      E_OK          Returning the PaddingValue succeeded.
  *  \return      E_NOT_OK      The PaddingValue pointer was invalid.
  *  \context     TASK
  *  \reentrant   FALSE
  *  \synchronous TRUE
  *  \pre         -
  *  \ingroup     range
  *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE)vSwUpdM_GetPaddingValue(vSwUpdM_VarDataPointerType PaddingValue);

/*
 *  General APIs
 */

/**********************************************************************************************************************
 *  vSwUpdM_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Pre-initializes the vSwUpdM.
 *  \details     Initialization of data which has to be available before vSwUpdM_Init.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_InitMemory(void);

/**********************************************************************************************************************
 *  vSwUpdM_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes the vSwUpdM.
 *  \details     -
 *  \param[in]   ConfigPtr               Pointer to the configuration data.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Component isn't initialized yet.
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init(P2CONST(vSwUpdM_ConfigType, AUTOMATIC, VSWUPDM_PBCFG) ConfigPtr);

/**********************************************************************************************************************
 *  vSwUpdM_DeInit()
 *********************************************************************************************************************/
/*! \brief       De-initializes the vSwUpdM.
 *  \details     Sets the vSwUpdM to a valid and stable state.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Component was successfully initialized before.
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_DeInit(void);

#if (VSWUPDM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) VersionInfo);
#endif /* (VSWUPDM_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  vSwUpdM_GetCurrentPersistClientNode()
 *********************************************************************************************************************/
/*! \brief       Returns the node, which is linked with the current user callout request.
 *  \details     In multiple node configurations where one node have to persist data not only for itself, this API
 *               will returns the node ID which is linked with the current callout request.
 *  \param[out]  Node         Node ID of node linked with the current callout request.
 *  \return      E_OK         Node value is valid.
 *  \return      E_NOT_OK     Node value is invalid. Function was called in wrong context.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     general
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetCurrentPersistClientNode(P2VAR(vSwUpdM_NodeIterType, AUTOMATIC, VSWUPDM_APPL_VAR) Node);

/**********************************************************************************************************************
 *  vSwUpdM_MainFunction
 *********************************************************************************************************************/
/*!
 * \fn           void vSwUpdM_MainFunction(void)
 * \brief        Monitors and controls the continuous execution of the vSwUpdM state handling.
 * \details      Function prototype declared by SchM.
 * \pre          Component is completely initialized or initialization is pending.
 * \context      TASK|ISR
 * \reentrant    FALSE
 * \synchronous  TRUE
 * \ingroup      general
 *********************************************************************************************************************/
/* FUNC(void, VSWUPDM_CODE) vSwUpdM_MainFunction(void); */

/**********************************************************************************************************************
 *  vSwUpdM_InitProcessInfo()
 *********************************************************************************************************************/
/*! \brief       Initialize verify info with default values.
 *  \details     It is recommended to call this API before calling vSwUpdM_Process* or vSwUpdM_Verify*.
 *  \param[out]  ProcessInfo   Pointer to the processing information structure.
 *               - InputCount                                  Set to zero.
 *               - OutputCount                                 Set to zero.
 *               - Operation                                   Set to VSTREAMPROC_NO_METASTATE.
 *               - InputData                                   Set to NULL_PTR.
 *               - OutputData                                  Set to NULL_PTR.
 *  \return      E_OK          The initialization succeeded.
 *  \return      E_NOT_OK      The ProcessInfo pointer was invalid.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     process
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitProcessInfo(P2VAR(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo);

/**********************************************************************************************************************
 *  vSwUpdM_InitEntityIds()
 *********************************************************************************************************************/
 /*! \brief       Initialize entity IDs with default values.
  *  \details     -
  *  \param[out]  EntityIds     Pointer to entity ID structure.
  *  \return      E_OK          The initialization succeeded.
  *  \return      E_NOT_OK      The EntityIds pointer was invalid.
  *  \context     TASK|ISR2
  *  \reentrant   FALSE
  *  \synchronous TRUE
  *  \pre         -
  *  \ingroup     general
  *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitEntityIds(vSwUpdM_EntityIdsPtrType EntityIds);

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM.h
 *********************************************************************************************************************/
