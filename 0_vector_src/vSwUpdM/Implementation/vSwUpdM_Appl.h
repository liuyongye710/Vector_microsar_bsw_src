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
/*!        \file  vSwUpdM_Appl.h
 *        \brief  vSwUpdM application callouts
 *      \details  Header for vSwUpdM callout functions.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(VSWUPDM_APPL_H)
#define VSWUPDM_APPL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! \mainpage General information for implementing vSwUpdM user callout functions
 *
 * The vSwUpdM needs to keep track of the state of the ECUs flash memory, the progress of a download and the validity
 * of the downloaded information. This information is structured as followed:
 *
 *  Dynamic vSwUpdM State:
 *      {
 *        Update State,
 *        Resume Information,
 *        For each partition:
 *             {
 *                Partition State,
 *                Partition Validity,
 *                Partition Revision Number
 *                For each vSwUpdM Software Module (logical block) within the partition:
 *                    {
 *                         Module State,
 *                         Module Validity,
 *                         Module Revision Number,
 *                         Module Programming Attempts
 *                         Count of segments in the Module,
 *                         For each external vSwUpdM Segment in the Module:
 *                             {
 *                                 Segment Attributes,
 *                             }
 *                         For each internal vSwUpdM Segment (including free memory areas) in the Module:
 *                             {
 *                                 Write Address
 *                             }
 *                    }
 *                For each vSwUpdM Memory Region within the partition:
 *                    {
 *                         Region State,
 *                         Region Programming Attempts
 *                         Erase Address,
 *                    }
 *             }
 *      }
 *
 * In the following, a template implementation for a simple A/B/A swap OTA capable ECU is shown.  It is not necessary
 * to use the array structure used in this template.
 * Some information (such as module validity information) needs to be shared with the bootloader. Therefore, it typically
 * makes sense to store this information directly within the program flash. Some information is only needed by the
 * vSwUpdM.
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_Init()
 *********************************************************************************************************************/
/*! \brief        Initialize user callouts.
 *  \details      Implementation of the vSwUpdM callout function issued during initialization.
 *  \param[in]    OpStatus   Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed Init callout. If there is a high risk that also a reset
 *                cannot resolve the reason, OTA updates will not longer possible.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_Init(vSwUpdM_OpStatusType OpStatus);

/*! \page UpdateState vSwUpdMState::UpdateState
 *
 * Purpose of this information:
 * ============================
 *
 * Allows the ECU application to keep track of what is happening within the OTA stack. Once the UpdateState reached
 * the "SWAP" state, the ECU application should store a flag in a reset save RAM variable and jump to the bootloader
 * to perform the swap of the "inactive" and "active" memory partition.
 *
 * Possible values and their meaning:
 * ==================================
 *
 * - #VSWUPDM_UPDATE_STATE_IDLE:     No software download / update is taking place.
 * - (#VSWUPDM_UPDATE_STATE_ACTIVE): Not used yet.
 * - #VSWUPDM_UPDATE_STATE_SWAP:     The software download / update completed in the inactive memory partition. It is now
 *                                   time to jump into the bootloader to perform the swap of those partitions and to start
 *                                   the new software image.
 *
 * When #vSwUpdM_Appl_GetUpdateState is executed:
 * =============================================
 *
 * - At initialization of the vSwUpdM.
 *
 * When #vSwUpdM_Appl_SetUpdateState() is executed:
 * ===============================================
 *
 * - Swap of active partition is requested (vSwUpdM_SwapActivePartition):
 *   - Activation of inactive partition.
 *   - Rollback to backup partition.
 *   - Early rollback to active partition.
 *
 * Suggested way of storing this information:
 * ==========================================
 *
 * - No need to persist this into non-volatile memory.
 * - Reset-Value shall be "IDLE".
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetUpdateState()
 *********************************************************************************************************************/
/*! \brief        Get the general update state.
 *  \details      Implementation of the vSwUpdM callout function to get general update state.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[out]   State             Update state.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \attention    The update state must be read unmodified. Just return the value provided by last
 *                vSwUpdM_Appl_SetUpdateState() call.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall be avoided since data reflects a RAM value and there is no reason for failure.
 *                Recommended handling if issues will be detected:
 *                - State shall be reported as #VSWUPDM_UPDATE_STATE_IDLE
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetUpdateState(
  vSwUpdM_OpStatusType OpStatus,
  P2VAR(vSwUpdM_UpdateStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetUpdateState()
 *********************************************************************************************************************/
/*! \brief        Set the general update state.
 *  \details      Implementation of the vSwUpdM callout function to set general update state.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    State             Update state.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \attention    The update state must be stored unmodified.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned since the value can be persisted in RAM.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetUpdateState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_UpdateStateType State,
  boolean SyncFlag);

/*! \page PartitionState vSwUpdMState::Partition::State
 *
 * Purpose of this information:
 * ============================
 *
 * The vSwUpdM needs to know, which of the configured partitions shall be used for which purpose. Therefore, at
 * initialization of the vSwUpdM it iterates through all configured partitions and queries the partition state.
 * Depending on the configuration of the hardware and the mapping of partitions to memory devices, this state may
 * either be static or needs to be derived dynamically from the current swap state / partition mapping.
 *
 * Possible values and their meaning:
 * ==================================
 *
 *                                        This state shall be returned for the partition...
 * - #VSWUPDM_PART_STATE_ACTIVE:               ... that is currently active. That is: the software stored in this
 *                                              partition is currently being executed. The software in that partition
 *                                              is assumed to be correctly validated and verified before.
 * - #VSWUPDM_PART_STATE_INACTIVE:             ... that shall be used to download a new version of the ECUs software to.
 * - #VSWUPDM_PART_STATE_BACKUP_TARGET:        ... that - before a swap of the inactive and active partition - shall be
 *                                              used to write a backup of the currently active partition to. If a
 *                                              hardware assisted A/B swap (memory remapping) is used, this state
 *                                              must not be used.
 * - #VSWUPDM_PART_STATE_BACKUP_SOURCE:        ... that - in case a rollback is necessary - shall be used to restore
 *                                              the previous version of the ECUs software. If a hardware assisted
 *                                              A/B swap (memory remapping) is used, this state must not be used.
 *                                              This flag shall be set only if the backup is valid.
 * - #VSWUPDM_PART_STATE_ACTIVATION_PENDING:   ... that shall become the new 'ACTIVE' partition after ECU restart (A/B).
 *                                              Or whose contents should be copied to the 'ACTIVE' partition (A/B/A).
 *
 * Certain OR-combinations of multiple of the states are possible. The allowed values depend on the specific use-case.
 * The following paragraph lists the valid combinations for the most common use-cases.
 *
 * Basic A/B (hardware assisted):
 * - #VSWUPDM_PART_STATE_ACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE | #VSWUPDM_PART_STATE_ACTIVATION_PENDING
 *
 * Extended A/B/A with static assignment of inactive and backup partition:
 * - #VSWUPDM_PART_STATE_ACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE | #VSWUPDM_PART_STATE_ACTIVATION_PENDING
 * - #VSWUPDM_PART_STATE_BACKUP_TARGET
 * - #VSWUPDM_PART_STATE_BACKUP_TARGET | #VSWUPDM_PART_STATE_BACKUP_SOURCE
 * - #VSWUPDM_PART_STATE_BACKUP_SOURCE | #VSWUPDM_PART_STATE_ACTIVATION_PENDING
 *
 * Extended A/B/A with dynamic assignment of inactive and backup partition:
 * - #VSWUPDM_PART_STATE_ACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE
 * - #VSWUPDM_PART_STATE_INACTIVE | #VSWUPDM_PART_STATE_ACTIVATION_PENDING
 * - #VSWUPDM_PART_STATE_BACKUP_TARGET
 * - #VSWUPDM_PART_STATE_BACKUP_TARGET | #VSWUPDM_PART_STATE_BACKUP_SOURCE
 * - #VSWUPDM_PART_STATE_BACKUP_SOURCE | #VSWUPDM_PART_STATE_ACTIVATION_PENDING (*)
 * - #VSWUPDM_PART_STATE_BACKUP_SOURCE | #VSWUPDM_PART_STATE_INACTIVE
 *
 * (*) May not be used, as it is interchangeable with 3).
 *
 * When #vSwUpdM_Appl_GetPartitionState() is executed:
 * ===================================================
 * - At initialization of the vSwUpdM.
 *
 * When #vSwUpdM_Appl_SetPartitionState() is executed:
 * ===================================================
 * - Swap of active partition is requested (vSwUpdM_SwapActivePartition):
 *   - Activation of inactive partition (2 -> 3).
 *   - Rollback to backup partition (5 -> 6, 7 -> 6 or 7 -> 3).
 *   - Early rollback to active partition (3 -> 2).
 * - Invalidation of inactive partition because of new download:
 *   - Backup source no longer valid (5 -> 4 or 7 -> 2).
 * - Successful creation of backup:
 *   - Backup target also becomes backup source (4 -> 5).
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Parts of the information may directly be retrieved from a hardware register (if supported by the hardware platform).
 * - Parts of the information may be hard-coded (in case of static assignment).
 * - Parts of the information may be stored in NVRAM (in case of dynamic assignment).
 * - Parts of the information may be stored in a dedicated program flash sector (typically pending activation).
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionState()
 *********************************************************************************************************************/
/*! \brief        Get state of given partition.
 *  \details      Implementation of the vSwUpdM callout function to get state of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[out]   State             State of the given partition.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there is
 *                no useful reaction possible to a failed Init callout. Obviously the application is running from
 *                somewhere. So it must be possible to detect the active partition anyhow. Either it's now possible
 *                to detect INACTIVE partition and BACKUP_TARGET or a default selection must be done.
 *                BACKUP_SOURCE flag indicate a valid backup and shall only be reported if all other states can be
 *                determined correctly. Issues in detecting states for invalid or backup partition shall lead to
 *                report safe/default states for all dependent information (Partition validity, Partition revision,
 *                Module *, region * and segment * (related to this partition) as well as resumeInfo)
 *                Recommended handling if issues will be detected:
 *                - State shall be reported as #VSWUPDM_PART_STATE_ACTIVE, #VSWUPDM_PART_STATE_INACTIVE or
 *                  #VSWUPDM_PART_STATE_BACKUP_TARGET only depending on partition
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionState()
 *********************************************************************************************************************/
/*! \brief        Set state of given partition.
 *  \details      Implementation of the vSwUpdM callout function to Set state of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    State             State of the given partition.
 *  \param[in]    Mask              Bitmask on State.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_PartitionStateType Mask,
  boolean SyncFlag);

/*! \page PartitionValidity vSwUpdMState::Partition::Validity
 *
 * Purpose of this information:
 * ============================
 * Keeping track of the validity of the whole partition. A partition is invalid as soon as it was modified. Before
 * a partition is set valid, all modules within the partition should be validated and their consistency should have
 * been checked. The bootloader will only jump into the application if the "active" partition has been validated.
 *
 * Possible values and their meaning:
 * ==================================
 * - #VSWUPDM_VALIDITY_INVALID:    The partition was modified or not yet validated.
 * - #VSWUPDM_VALIDITY_VALID:      The partition has been validated and not modified afterwards.
 *
 * When the #vSwUpdM_Appl_GetPartitionValid function is executed:
 * ==============================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetPartitionValid function is executed:
 * ==============================================================
 * - A partition is set invalid on explicit request.
 * - A partition is set invalid as soon as it is changed.
 * - A partition is set valid only after all modules have been validated and checked for consistency.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Validity pattern in program flash. This information is shared with the bootloader.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionValid()
 *********************************************************************************************************************/
/*! \brief        Get validity of given partition.
 *  \details      Implementation of the vSwUpdM callout function to get validity of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[out]   Valid             Validity of the given partition.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
*                 is no useful reaction possible to a failed Init callout. If a value is not readable or corrupted:
 *                The active partition is running and must be therefore valid. Inactive and backup target shall fall
 *                back to invalid.
 *                Recommended handling if issues will be detected:
 *                - "Valid" shall be reported as #VSWUPDM_VALIDITY_VALID for active and #VSWUPDM_VALIDITY_INVALID for
 *                  other partitions
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_ValidType, AUTOMATIC, VSWUPDM_APPL_VAR) Valid);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionValid()
 *********************************************************************************************************************/
/*! \brief        Set validity of given partition.
 *  \details      Implementation of the vSwUpdM callout function to set validity of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    Valid             Validity of the given partition.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ValidType Valid,
  boolean SyncFlag);

/*! \page PartitionRevision vSwUpdMState::Partition::Revision
 *
 * Purpose of this information:
 * ============================
 * For information purposes only. Currently not used by vSwUpdM directly.
 * Reflects the order and/or number of modifications.
 *
 * Possible values and their meaning:
 * ==================================
 * Number of type vSwUpdM_PartitionRevisionType. A higher number corresponds to "more recently modified".
 *
 * When the #vSwUpdM_Appl_GetPartitionRevision function is executed:
 * =================================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetPartitionRevision function is executed:
 * =================================================================
 * - During validation of vSwUpdM Partition.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Storage is optional.
 * - Location depends on intended usage scenario:
 *   - Shared with the bootloader: Directly within the program flash.
 *   - Only used during OTA download: May be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionRevision()
 *********************************************************************************************************************/
/*! \brief        Get revision of given partition.
 *  \details      Implementation of the vSwUpdM callout function to get revision of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[out]   Revision          Revision of the given partition.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout. Revision numbers will only be requested for
 *                valid partitions.
 *                Dependent on your use case it may be possible to calculate the revision number based on other information,
 *                instead of storing it explicitly.
 *                Recommended handling if issues will be detected:
 *                - Report  all Revision of active partition as 1 and all others as VSWUPDM_INVALID_REVISION
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_PartitionRevisionType, AUTOMATIC, VSWUPDM_APPL_VAR) Revision);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionRevision()
 *********************************************************************************************************************/
/*! \brief        Set revision of given partition.
 *  \details      Implementation of the vSwUpdM callout function to set revision of given partition.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    Revision          Revision of the given partition.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionRevisionType Revision,
  boolean SyncFlag);

/*! \page PartitionRevision vSwUpdMState::Partition::Module::State
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM needs to keep track of the memory state associated with the vSwUpdM module. It is important to keep
 * track of which actions have already been performed and which operations are pending on the respective vSwUpdM
 * modules. Persisting this information is required to safely allow resuming a download across multiple power cycles.
 *
 * Possible values and their meaning:
 * ==================================
 * - #VSWUPDM_MODULE_STATE_UNDEFINED:        State of module not known, e.g. before first OTA download.
 * - #VSWUPDM_MODULE_STATE_ERASED:           The complete module is erased
 * - #VSWUPDM_MODULE_STATE_ERASE_PENDING:    The module is currently being erased / queued to be erased
 * - #VSWUPDM_MODULE_STATE_DIRTY:            The module is currently written, but the exact state of the memory is not known.
 *                                           When the download is interrupted in this state, a recovery will be initiated.
 *                                           Typically this involves an implicit re-erasing of (parts of) the module and
 *                                           requesting parts of the data again.
 * - #VSWUPDM_MODULE_STATE_RESTART:          Hook requested a restart on module granularity. This will force erase of
 *                                           module after restart.
 * - #VSWUPDM_MODULE_STATE_CLEAN:            The module is currently written and the exact state of the memory is known.
 *                                           When restarting on the next power cycle, the download can continue directly after
 *                                           the last page, which was programmed completely.
 * - #VSWUPDM_MODULE_STATE_SYNC_DIRTY:       Same as 'dirty', but during module synchronization.
 * - #VSWUPDM_MODULE_STATE_SYNC_CLEAN:       Same as 'clean', but during module synchronization.
 * - #VSWUPDM_MODULE_STATE_SYNC_FINISHED:    Module synchronization has been 'finished' and comparison of copied content is
 *                                           not yet started.
 * - #VSWUPDM_MODULE_STATE_COMPARE_PENDING:  The module is currently being compared.
 * - #VSWUPDM_MODULE_STATE_FINALIZED:        The vSwUpdM module has been 'finalized' and does not allow for any operation
 *                                           except verification of the module or erasing the whole module again.
 * - #VSWUPDM_MODULE_STATE_VERIFIED:         The vSwUpdM module has been 'verified' and does not allow for any operation
 *                                           except erasing the whole module again.
 *
 * When the #vSwUpdM_Appl_GetModuleState function is executed:
 * ===========================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetModuleState function is executed:
 * ===========================================================
 * - Frequently during software download sequence.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The module state is changed frequently during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleState()
 *********************************************************************************************************************/
/*! \brief        Get state of given module.
 *  \details      Implementation of the vSwUpdM callout function to get state of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[out]   State             State of the given module instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout.
 *                Recommended handling if issues will be detected:
 *                - For mandatory modules in active partition report state as #VSWUPDM_MODULE_STATE_VERIFIED and for
 *                  all other modules as #VSWUPDM_MODULE_STATE_UNDEFINED
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ModuleStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleState()
 *********************************************************************************************************************/
/*! \brief        Set state of given module.
 *  \details      Implementation of the vSwUpdM callout function to set state of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    State             State of the given module instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State,
  boolean SyncFlag);

/*! \page ModuleValidity vSwUpdMState::Partition::Module::Validity
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM needs to remember if a vSwUpdM module has been validated correctly. This information is shared with the
 * bootloader. The bootloader will only start execution of the ECUs software if all vSwUpdM modules in the active
 * partition have been marked valid.
 *
 * Possible values and their meaning:
 * ==================================
 * - #VSWUPDM_VALIDITY_INVALID:    The module was modified or not yet validated.
 * - #VSWUPDM_VALIDITY_VALID:      The module has been validated and not modified afterwards.
 *
 * When the #vSwUpdM_Appl_GetModuleValid function is executed:
 * ===========================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetModuleValid function is executed:
 * ===========================================================
 * - The module is set valid only once per download sequence after all necessary validations have been performed
 * - The module is set invalid as soon as a valid module is modified (e.g. erased) or explicitly invalidated.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Directly within the program flash, so that the information may easily be shared with the bootloader.
 * - A possible way of storing this information is to configure a static segment in the vSwUpdM (this will not be
 *   accessible by the tester) and use this segment to store a validity pattern.
 * - In special cases (for instance if there is only one module in the partition), it might be optional to persist
 *   this information into non-volatile memory (if it can be derived from other validity or status information that
 *   is persisted).
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleValid()
 *********************************************************************************************************************/
/*! \brief        Get validity of given module.
 *  \details      Implementation of the vSwUpdM callout function to get validity of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[out]   Valid             Validity of the given module instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout. If a value is not readable or corrupted:
 *                Mandatory modules in active partition must be valid, because the application is running from there.
 *                Optional modules and modules in inactive and backup partition shall fall back to invalid.
 *                Recommended handling if issues will be detected:
 *                - Report mandatory module validity in active partition as VSWUPDM_VALIDITY_VALID
 *                  and all others as VSWUPDM_VALIDITY_INVALID
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ValidType, AUTOMATIC, VSWUPDM_APPL_VAR) Valid);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleValid()
 *********************************************************************************************************************/
/*! \brief        Set validity of given module.
 *  \details      Implementation of the vSwUpdM callout function to set validity of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    Valid             Validity of the given module instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ValidType Valid,
  boolean SyncFlag);

/*! \page ModuleRevision vSwUpdMState::Partition::Module::Revision
 *
 * Purpose of this information:
 * ============================
 * The revision number is used to allow a "smart" implementation for synchronizing partitions. Modules that have not
 * been changed in the partition do not need to be erased and copied again. This not only speeds up creating backup
 * partitions and preparing the new software image in case of partial downloads, it also allows reducing the number of
 * (unnecessary) erase/write cycles.
 *
 * Possible values and their meaning:
 * ==================================
 * Number of type vSwUpdM_ModuleRevisionType. A higher number corresponds to "more recently modified".
 *
 * When the #vSwUpdM_Appl_GetModuleRevision function is executed:
 * ==============================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetModuleRevision function is executed:
 * ==============================================================
 * - During validation of a vSwUpdM Module (could be implicitly during synchronization).
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Directly within the program flash, so that the information may easily be shared with the bootloader.
 * - A possible way of storing this information is to configure a static segment in the vSwUpdM (this will not be
 *   accessible by the tester) and use this segment to store the revision number together with a validity pattern.
 *   Note: The revision number is updated during validation the vSwUpdM module. That is: a static segment used to store
 *   the information would have been erased earlier, as erasing of the module is mandatory before download.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleRevision()
 *********************************************************************************************************************/
/*! \brief        Get revision of given module.
 *  \details      Implementation of the vSwUpdM callout function to get revision of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[out]   Revision          Revision of the given module instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout. Revision numbers will only be requested for
 *                valid modules.
 *                Dependent on your use case it may be possible to calculate the revision number based on other information,
 *                instead of storing it explicitly.
 *                Recommended handling if issues will be detected:
 *                - Report  all Revisions of modules in active partition as 1 and all others as VSWUPDM_INVALID_REVISION
 *                - ResumeInfo shall be set to default values (#vSwUpdM_Appl_DefaultResumeInfo)
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ModuleRevisionType, AUTOMATIC, VSWUPDM_APPL_VAR) Revision);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleRevision()
 *********************************************************************************************************************/
/*! \brief        Set revision of given module.
 *  \details      Implementation of the vSwUpdM callout function to set revision of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    Revision          Revision of the given module instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleRevisionType Revision,
  boolean SyncFlag);

/*! \page ModuleProgrammingAttempts vSwUpdMState::Partition::Module::ProgrammingAttempts
 *
 * Purpose of this information:
 * ============================
 * The programming attempts counter is used to keep track of the number of programming cycles (erase and write) performed
 * on a module instance. The counter for the module is equal to the maximum value of all regions of the module.
 * If the value exceeds the configured maximum value, any request to erase parts of the module will be refused.
 * Thus no further updates of the specific module instance are possible.
 * The main purpose of this restriction is to ensure that the number of programming cycles doesn't exceed the guaranteed
 * cycle count of the used memory device (e.g. flash).
 *
 * Possible values and their meaning:
 * ==================================
 * Number of type vSwUpdM_ProgrammingAttemptType. Represents the number of programming cycles.
 *
 * When the #vSwUpdM_Appl_GetModuleProgrammingAttempts function is executed:
 * ==============================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetModuleProgrammingAttempts function is executed:
 * ==============================================================
 * - After finishing an erase operation within one region during software download sequence.
 *   Erase operation could be explicitly triggered  by an erase service (e.g. EraseModule) or implicitly (e.g. during
 *   module synchronization or clean-up after an unintended reset.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Storage is optional, when no tracking of programming attempts per module instance is required.
 * - The programming attempts counter changes during a download and should thus be stored in NVRAM.
 * - This information is commonly shared with the bootloader.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief        Get programming attempts counter of given module.
 *  \details      Implementation of the vSwUpdM callout function to get programming attempts counter of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId           Identifier of the partition.
 *  \param[in]    ModuleId              Identifier of the module.
 *  \param[out]   ProgrammingAttempts   Programming attempts counter of the given module instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout.
 *                Recommended handling if issues will be detected:
 *                - Report maximum value of programming attempts of all regions of the module.
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief        Set programming attempts counter of given module.
 *  \details      Implementation of the vSwUpdM callout function to set programming attempts counter of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId           Identifier of the partition.
 *  \param[in]    ModuleId              Identifier of the module.
 *  \param[in]    ProgrammingAttempts   Programming attempts counter of the given module instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  boolean SyncFlag);

/*! \page RegionState vSwUpdMState::Partition::Region::State
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM needs to keep track of the memory state associated with the different memory regions. It is important to
 * keep track of which actions have already been performed and which operations are pending on the respective vSwUpdM
 * modules. Persisting this information is required to safely allow resuming a download across multiple power cycles.
 *
 * Possible values and their meaning:
 * ==================================
 *
 * - #VSWUPDM_REGION_STATE_UNDEFINED:      State of region not known, e.g. before first OTA download.
 * - #VSWUPDM_REGION_STATE_ERASED:         The whole memory region is erased.
 * - #VSWUPDM_REGION_STATE_ERASE_PENDING:  The memory region is currently being erased.
 * - #VSWUPDM_REGION_STATE_DIRTY:          There was at least one write access to this memory region after it was erased.
 * - #VSWUPDM_REGION_STATE_FINALIZED:      The memory region was finalized and no more write access is allowed.
 *
 * When the #vSwUpdM_Appl_GetRegionState function is executed:
 * ===========================================================
 * - When opening a vSwUpdM module.
 *   Different operations trigger the opening of a module:
 *    - Erasing of the module.
 *    - Download of the module.
 *    - Finalization of the module.
 *    - Synchronization of the module / a partition.
 *
 * When the #vSwUpdM_Appl_SetRegionState function is executed:
 * ===========================================================
 * - Frequently during software download sequence.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The region state is changed frequently during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionState()
 *********************************************************************************************************************/
/*! \brief        Get state of given region.
 *  \details      Implementation of the vSwUpdM callout function to get state of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    RegionId          Identifier of the region.
 *  \param[out]   State             State of the given region instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK without any repairing actions may lead to a permanently disabled update
 *                functionality. An error is forwarded to the upper layer, but this does not result in any further
 *                useful repair measures. Thus, such have to be carried out in this callout.
 *                Recommended handling if issues will be detected:
 *                - Obvious actions like repeating NV read operation or restoring the value somehow are not part
 *                  of this template, because they're project specific.
 *                - An example for repair measures is provided by defining
 *                  #VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE - this will reset all module internal NV
 *                  values by setting resume information, region state(s), segment count and module state to their
 *                  default states.
 *                  This repair measure together with an #E_NOT_OK as return value will lead to a update failure.
 *                  Any update retry will use those repaired NV values for this module, which again represent
 *                  a consistent state.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_RegionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionState()
 *********************************************************************************************************************/
/*! \brief        Set state of given region.
 *  \details      Implementation of the vSwUpdM callout function to set state of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    RegionId          Identifier of the region.
 *  \param[in]    State             State of the given region instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_RegionStateType State,
  boolean SyncFlag);

/*! \page RegionProgrammingAttempts vSwUpdMState::Partition::Region::ProgrammingAttempts
 *
 * Purpose of this information:
 * ============================
 * The programming attempts counter is used to keep track of the number of programming cycles (erase and write) performed
 * on a region instance.
 * If the value exceeds the configured maximum value, any request to erase parts of the region will be refused.
 * Thus no further updates of the specific module instance are possible.
 * The main purpose of this restriction is to ensure that the number of programming cycles doesn't exceed the guaranteed
 * cycle count of the used memory device (e.g. flash).
 *
 * Possible values and their meaning:
 * ==================================
 * Number of type vSwUpdM_ProgrammingAttemptType. Represents the number of programming cycles.
 *
 * When the #vSwUpdM_Appl_GetModuleProgrammingAttempts function is executed:
 * ==============================================================
 * - When opening a vSwUpdM module.
 *
 * When the #vSwUpdM_Appl_SetModuleProgrammingAttempts function is executed:
 * ==============================================================
 * - After finishing an erase operation within the region during software download sequence.
 *   Erase operation could be explicitly triggered  by an erase service (e.g. EraseModule) or implicitly (e.g. during
 *   module synchronization or clean-up after an unintended reset.
 *
 * Suggested way of storing this information:
 * ==========================================
 * - Storage is optional, when no tracking of programming attempts per module instance is required.
 * - The programming attempts counter changes during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief        Get programming attempts counter of given region.
 *  \details      Implementation of the vSwUpdM callout function to get programming attempts counter of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId           Identifier of the partition.
 *  \param[in]    ModuleId              Identifier of the module.
 *  \param[in]    RegionId              Identifier of the region.
 *  \param[out]   ProgrammingAttempts   Programming attempts counter of the given region instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed read callout.
 *                - Report value of programming attempts of the module to which the regions belongs.
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionProgrammingAttempts()
 *********************************************************************************************************************/
/*! \brief        Set programming attempts counter of given region.
 *  \details      Implementation of the vSwUpdM callout function to set programming attempts counter of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId           Identifier of the partition.
 *  \param[in]    ModuleId              Identifier of the module.
 *  \param[in]    RegionId              Identifier of the region.
 *  \param[in]    ProgrammingAttempts   Programming attempts counter of the given region instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  boolean SyncFlag);

/*! \page RegionState vSwUpdMState::Partition::Region::EraseAddress
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM needs to keep track of the memory state associated with the different memory regions. It is important to
 * keep track of which parts of the memory are "erased" and which parts of the memory are "written". Persisting this
 * information is required to safely allow resuming a download across multiple power cycles.
 *
 * Possible values and their meaning:
 * ==================================
 * Next address in the memory region which is going to be erased.
 * The part of the region in front of this address was already successfully erased.
 *
 * When the #vSwUpdM_Appl_GetRegionEraseAddress function is executed:
 * ==================================================================
 * - When opening a vSwUpdM module.
 *   For additional information, see vSwUpdMState::Partition::Region::State.
 *
 * When the #vSwUpdM_Appl_SetRegionEraseAddress function is executed:
 * ==================================================================
 * - Frequently during software download sequence
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The erase address is changed frequently during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionEraseAddress()
 *********************************************************************************************************************/
/*! \brief        Get erase address of given region.
 *  \details      Implementation of the vSwUpdM callout function to get erase address of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    RegionId          Identifier of the region.
 *  \param[out]   EraseAddress      Erase address of the given region instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK without any repairing actions may lead to a permanently disabled update
 *                functionality. An error is forwarded to the upper layer, but this does not result in any further
 *                useful repair measures. Thus, such have to be carried out in this callout.
 *                Recommended handling if issues will be detected:
 *                - Obvious actions like repeating NV read operation or restoring the value somehow are not part
 *                  of this template, because they're project specific.
 *                - An example for repair measures is provided by defining
 *                  #VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE - this will reset all module internal NV
 *                  values by setting resume information, region state(s), segment count and module state to their
 *                  default states.
 *                  This repair measure together with an #E_NOT_OK as return value will lead to a update failure.
 *                  Any update retry will use those repaired NV values for this module, which again represent
 *                  a consistent state.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionEraseAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) EraseAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionEraseAddress()
 *********************************************************************************************************************/
/*! \brief        Set erase address of given region.
 *  \details      Implementation of the vSwUpdM callout function to set erase address of given region instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    RegionId          Identifier of the region.
 *  \param[in]    EraseAddress      Erase address of the given region instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionEraseAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_AddressType EraseAddress,
  boolean SyncFlag);

/*! \page SegmentCount vSwUpdMState::Partition::Module::SegmentCount
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM uses "download segments" to keep track of which parts of the memory are already programmed. For each
 * downloaded segment, a new entry is added that needs to be persisted in NVRAM. This variable is used to persist the
 * number of those entries.
 *
 * Possible values and their meaning:
 * ==================================
 * Number of downloaded segments in this vSwUpdM Module.
 *
 * When the #vSwUpdM_Appl_GetSegmentCount function is executed:
 * ============================================================
 * - When opening a vSwUpdM module.
 *   For additional information, see vSwUpdMState::Partition::Region::State.
 *
 * When the #vSwUpdM_Appl_SetSegmentCount function is executed:
 * ============================================================
 * - During software download sequence
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The number of segments changes during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentCount()
 *********************************************************************************************************************/
/*! \brief        Get segment count of given module.
 *  \details      Implementation of the vSwUpdM callout function to get segment count of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[out]   SegmentCount      Segment count of the given module instance.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK without any repairing actions may lead to a permanently disabled update
 *                functionality. An error is forwarded to the upper layer, but this does not result in any further
 *                useful repair measures. Thus, such have to be carried out in this callout.
 *                Recommended handling if issues will be detected:
 *                - Obvious actions like repeating NV read operation or restoring the value somehow are not part
 *                  of this template, because they're project specific.
 *                - An example for repair measures is provided by defining
 *                  #VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE - this will reset all module internal NV
 *                  values by setting resume information, region state(s), segment count and module state to their
 *                  default states.
 *                  This repair measure together with an #E_NOT_OK as return value will lead to a update failure.
 *                  Any update retry will use those repaired NV values for this module, which again represent
 *                  a consistent state.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentCount(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentCount);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentCount()
 *********************************************************************************************************************/
/*! \brief        Set segment count of given module.
 *  \details      Implementation of the vSwUpdM callout function to set segment count of given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    SegmentCount      Segment count of the given module instance.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentCount(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 SegmentCount,
  boolean SyncFlag);

/*! \page SegmentAttributes vSwUpdMState::Partition::Module::Segment::Attributes
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM uses "download segments" to keep track of which parts of the memory are already programmed. For each
 * downloaded segment, a new entry is added that needs to be persisted in NVRAM. Each segment has dynamic attributes
 * that change during the software download sequence.
 *
 * Possible values and their meaning:
 * ==================================
 * Dynamic attributes associated with a vSwUpdM segment (e.g. memory range and state).
 *
 * When the #vSwUpdM_Appl_GetSegmentAttributes function is executed:
 * =================================================================
 * - When opening a vSwUpdM module.
 *   For additional information, see vSwUpdMState::Partition::Region::State.
 *
 * When the #vSwUpdM_Appl_SetSegmentAttributes function is executed:
 * =================================================================
 * - During software download sequence
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The dynamic segment attributes change during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentAttributes()
 *********************************************************************************************************************/
/*! \brief        Get attributes of given segment.
 *  \details      Implementation of the vSwUpdM callout function to get attributes of segment in given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    SegmentIdx        Index of (external) segment in given module index.
 *  \param[out]   SegmentAttributes Segment attributes of the given segment.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK without any repairing actions may lead to a permanently disabled update
 *                functionality. An error is forwarded to the upper layer, but this does not result in any further
 *                useful repair measures. Thus, such have to be carried out in this callout.
 *                Recommended handling if issues will be detected:
 *                - Obvious actions like repeating NV read operation or restoring the value somehow are not part
 *                  of this template, because they're project specific.
 *                - An example for repair measures is provided by defining
 *                  #VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE - this will reset all module internal NV
 *                  values by setting resume information, region state(s), segment count and module state to their
 *                  default states.
 *                  This repair measure together with an #E_NOT_OK as return value will lead to a update failure.
 *                  Any update retry will use those repaired NV values for this module, which again represent
 *                  a consistent state.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentAttributes(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2VAR(vSwUpdM_SegmentDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentAttributes()
 *********************************************************************************************************************/
/*! \brief        Set attributes of given segment.
 *  \details      Implementation of the vSwUpdM callout function to set attributes of segment in given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    SegmentIdx        Index of (external) segment in given module index.
 *  \param[in]    SegmentAttributes Segment attributes of the given segment.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentAttributes(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2CONST(vSwUpdM_SegmentDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  boolean SyncFlag);

/*! \page SegmentWriteAddress vSwUpdMState::Partition::Module::Segment::WriteAddress
 *
 * Purpose of this information:
 * ============================
 * The vSwUpdM uses "download segments" to keep track of which parts of the memory are already programmed. For each
 * downloaded segment, a new entry is added that needs to be persisted in NVRAM. Each segment, the vSwUpdM needs to
 * remember the last written address, in order to be able to resume a download across multiple power cycles.
 *
 * Possible values and their meaning:
 * ==================================
 * Next address in the download segment which is going to be written.
 * The part of the segment in front of this address is known to be successfully written.
 *
 * When the #vSwUpdM_Appl_GetSegmentWriteAddress function is executed:
 * ===================================================================
 * - When opening a vSwUpdM module.
 *   For additional information, see vSwUpdMState::Partition::Region::State.
 *
 * When the #vSwUpdM_Appl_SetSegmentWriteAddress function is executed:
 * ===================================================================
 * - During software download sequence
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The segment write address changes during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentWriteAddress()
 *********************************************************************************************************************/
/*! \brief        Get write address of given segment.
 *  \details      Implementation of the vSwUpdM callout function to get write address of segment in given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    SegmentIdx        Index of (internal) segment in given module index.
 *  \param[out]   WriteAddress      Write address of the given segment.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK without any repairing actions may lead to a permanently disabled update
 *                functionality. An error is forwarded to the upper layer, but this does not result in any further
 *                useful repair measures. Thus, such have to be carried out in this callout.
 *                Recommended handling if issues will be detected:
 *                - Obvious actions like repeating NV read operation or restoring the value somehow are not part
 *                  of this template, because they're project specific.
 *                - An example for repair measures is provided by defining
 *                  #VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE - this will reset all module internal NV
 *                  values by setting resume information, region state(s), segment count and module state to their
 *                  default states.
 *                  This repair measure together with an #E_NOT_OK as return value will lead to a update failure.
 *                  Any update retry will use those repaired NV values for this module, which again represent
 *                  a consistent state.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentWriteAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) WriteAddress);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentWriteAddress()
 *********************************************************************************************************************/
/*! \brief        Set write address of given segment.
 *  \details      Implementation of the vSwUpdM callout function to set write address of segment in given module instance.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \param[in]    SegmentIdx        Index of (internal) segment in given module index.
 *  \param[in]    WriteAddress      Write address of the given segment.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentWriteAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  vSwUpdM_AddressType  WriteAddress,
  boolean SyncFlag);

/*! \page ResumeInfo vSwUpdMState::ResumeInfo
 *
 * Purpose of this information:
 * ============================
 * In order to be able to resume a download across multiple power cycles, the vSwUpdM needs to know which operation
 * it was executing and at which state that operation was aborted.
 *
 * Possible values and their meaning:
 * ==================================
 * Internal information required to resume an aborted operation.
 *
 * When the #vSwUpdM_Appl_GetResumeInfo function is executed:
 * ==========================================================
 * - At initialization of the vSwUpdM.
 *
 * When the #vSwUpdM_Appl_SetResumeInfo function is executed:
 * ==========================================================
 * - Frequently during software download sequence
 *
 * Suggested way of storing this information:
 * ==========================================
 * - The resume information is updated many times during a download and should thus be stored in NVRAM.
 *
 */

/**********************************************************************************************************************
 *  vSwUpdM_Appl_GetResumeInfo()
 *********************************************************************************************************************/
/*! \brief        Get resume information.
 *  \details      Implementation of the vSwUpdM callout function to get resume information.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[out]   ResumeInfo        Resume information.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       #E_NOT_OK Shall never be returned. Reason: This error will be forwarded to upper layer, but there
 *                is no useful reaction possible to a failed resume callout. Report that there is no resume
 *                information instead
 *                Recommended handling if issues will be detected:
 *                - Fill ResumeInfo with default values (#vSwUpdM_Appl_DefaultResumeInfo):
 *                  ResumeInfo->PartitionId      = #VSWUPDM_INVALID_ID;
 *                  ResumeInfo->CurrentService   = #VSWUPDM_SID_NONE;
 *                  ResumeInfo->ServiceState     = #VSWUPDM_RESUME_STATE_UNDEFINED;
 *                  ResumeInfo->StreamAddress    = 0u;
 *                  ResumeInfo->MemoryAddress    = 0u;
 *                  ResumeInfo->IsAddressValid   = #FALSE;
 *                  TriggerAddress               = 0u;
 *                - return value shall be #E_OK
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetResumeInfo(
  vSwUpdM_OpStatusType OpStatus,
  P2VAR(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetResumeInfo()
 *********************************************************************************************************************/
/*! \brief        Set resume information.
 *  \details      Implementation of the vSwUpdM callout function to set resume information.
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    ResumeInfo        Resume information.
 *  \param[in]    SyncFlag          Write required.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort. Getter function must be able to detect the issue.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetResumeInfo(
  vSwUpdM_OpStatusType OpStatus,
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ResumeInfo,
  boolean SyncFlag);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_ResetDecryptionInitVector()
 *********************************************************************************************************************/
/*! \brief        Reset the decryption initialization vector.
 *  \details      Implementation of the vSwUpdM callout function to reset the initialization vector used by the
 *                decryption to its default value.
 *                Typically achieved by calls to CSM APIs Csm_KeyElementSet and Csm_KeySetValid, using matching
 *                key ID and key element identifier (e.g. CRYPTO_KE_CIPHER_IV).
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetDecryptionInitVector(void);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetDecryptionInitVector()
 *********************************************************************************************************************/
/*! \brief        Set the decryption initialization vector.
 *  \details      Implementation of the vSwUpdM callout function to set the initialization vector used by the decryption
 *                to the passed value.
 *                Typically achieved by calls to CSM APIs Csm_KeyElementSet and Csm_KeySetValid, using matching
 *                key ID and key element identifier (e.g. CRYPTO_KE_CIPHER_IV).
 *  \param[in]    IvData          The value of the initialization vector.
 *  \param[in]    IvSize          The size of the initialization vector.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetDecryptionInitVector(
  vSwUpdM_ConstDataPointerType IvData,
  vSwUpdM_LengthType IvSize);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_ResetEncryptionInitVector()
 *********************************************************************************************************************/
/*! \brief        Reset the encryption initialization vector.
 *  \details      Implementation of the vSwUpdM callout function to reset the initialization vector used by the
 *                encryption to its default value.
 *                Typically achieved by calls to CSM APIs Csm_KeyElementSet and Csm_KeySetValid, using matching
 *                key ID and key element identifier (e.g. CRYPTO_KE_CIPHER_IV).
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetEncryptionInitVector(void);

/**********************************************************************************************************************
 *  vSwUpdM_Appl_SetEncryptionInitVector()
 *********************************************************************************************************************/
/*! \brief        Set the encryption initialization vector.
 *  \details      Implementation of the vSwUpdM callout function to set the initialization vector used by the encryption
 *                to the passed value.
 *                Typically achieved by calls to CSM APIs Csm_KeyElementSet and Csm_KeySetValid, using matching
 *                key ID and key element identifier (e.g. CRYPTO_KE_CIPHER_IV).
 *  \param[in]    IvData          The value of the initialization vector.
 *  \param[in]    IvSize          The size of the initialization vector.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \remark       Returning #E_NOT_OK will cause forwarding the error to upper layer, which shall lead to an
 *                update sequence abort.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetEncryptionInitVector(
  vSwUpdM_ConstDataPointerType IvData,
  vSwUpdM_LengthType IvSize);

#define VSWUPDM_STOP_SEC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_APPL_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Appl.h
 *********************************************************************************************************************/
