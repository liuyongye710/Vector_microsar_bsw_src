/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: whole file
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration. The template code is
 *  incomplete and only intended for providing a signature and an empty implementation. It is neither intended nor
 *  qualified for use in series production without applying suitable quality measures. The template code must be
 *  completed as described in the instructions given within this file and/or in the TechnicalReference. The completed
 *  implementation must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before its use.
 *********************************************************************************************************************/

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
/*!        \file  _vSwUpdM_Appl.c
 *        \brief  vSwUpdM template source file
 *
 *      \details  Template to demonstrate the usage of the vSwUpdM callout functions.
 *                Must only be used for demonstration purposes.
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
 * In the following, a template implementation for a simple A/B/A swap OTA capable ECU is shown. The general idea is that
 * whatever information is provided by the vSwUpdM by means of a vSwUpdM_Appl_SetXXX function may later be retrieved by
 * the respective vSwUpdM_Appl_GetXXX function. It is not necessary to use the array structure used in this template.
 * Some information (such as module validity information) is to be share with the bootloader. Therefore, it typically
 * makes sense to store this information directly within the program flash. Some information is only needed by the
 * vSwUpdM. Some information is 'optional' in the sense that persisting that information across power cycles improves
 * the overall performance, but using static default values does not prevent a successful OTA download. Please refer to
 * the comments within the respective vSwUpdM_Appl_GetXXX/SetXXX functions and the vSwUpdM technical reference for more
 * information on the meaning of the respective element.
 *
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

#define VSWUPDM_APPL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_Appl.h"
#include "vSwUpdM_Cfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#ifndef VSWUPDM_DISABLE_APPL_ERROR_DIRECTIVE_FOR_COMPONENT_TEST_EXECUTION_AND_STATIC_CODE_ANALYSIS
# error "vSwUpdM_Appl.c: This file includes template code that must be completed and/or adapted during BSW integration."
#endif

/* CAUTION! Must be adapted by integrator: Required number of array entries must be adapted to actual configuration */

#define VSWUPDM_APPL_PARTITION_COUNT                          3u    /*! Number of configured partitions. */
#define VSWUPDM_APPL_MODULE_COUNT                             3u    /*! Number of vSwUpdM software modules (logical blocks) in each partition. */
#define VSWUPDM_APPL_REGION_COUNT                             3u    /*! Number of vSwUpdM memory regions in each partition. */
#define VSWUPDM_APPL_MAX_REGION_COUNT_PER_MODULE              1u    /*! Maximum number of memory regions per vSwUpdM software module. */
#define VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT                   16u   /*! Maximum number of segments that max be downloaded per software module (logical block). */
#define VSWUPDM_APPL_MAX_RESERVED_SEGMENT_COUNT_PER_MODULE    3u    /*! Maximum number of reserved segments (e.g. to store validity patterns) per vSwUpdM software module. */
/*! Maximum number of segment write addresses (including external segments and potential free segments after reserved segments and at beginning of each region). */
#define VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT \
  (VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT + VSWUPDM_APPL_MAX_RESERVED_SEGMENT_COUNT_PER_MODULE + VSWUPDM_APPL_MAX_REGION_COUNT_PER_MODULE)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
typedef enum
{
  VSWUPDM_APPL_WORKING_STEP_RESET_RESUME_INFO,
  VSWUPDM_APPL_WORKING_STEP_RESET_REGION_STATE,
  VSWUPDM_APPL_WORKING_STEP_RESET_SEGMENT_COUNT,
  VSWUPDM_APPL_WORKING_STEP_RESET_MODULE_STATE,
  VSWUPDM_APPL_WORKING_STEP_FINISH
} vSwUpdM_Appl_WorkingStepType;

typedef enum
{
  VSWUPDM_APPL_REPAIR_REASON_GET_REGION_STATE,
  VSWUPDM_APPL_REPAIR_REASON_GET_SEGMENT_INFO
} vSwUpdM_Appl_RepairReasonType;

typedef struct
{
  vSwUpdM_Appl_WorkingStepType  currentStep;
  vSwUpdM_Appl_WorkingStepType  nextStep;
  vSwUpdM_OpStatusType          wsOpStatus;
  Std_ReturnType                returnValue;
  vSwUpdM_RegionIdxType         regionIdx;
  uint32                        regionCount;
} vSwUpdM_Appl_ResetModuleWorkspaceType;
#endif

typedef enum
{
  VSWUPDM_APPL_GETTER_STATE_GET_VALUE,
#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
  VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR,
#endif
  VSWUPDM_APPL_GETTER_STATE_INIT_SEGMENT_INFO
}vSwUpdM_Appl_GetterStateType;

typedef enum
{
  VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_COUNT,
  VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_ATTRIBUTES,
  VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_WRITE_ADDRESS
} vSwUpdM_Appl_SegmentInitStepType;

typedef struct
{
  vSwUpdM_Appl_SegmentInitStepType  currentStep;
  vSwUpdM_Appl_SegmentInitStepType  nextStep;
  vSwUpdM_OpStatusType              wsOpStatus;
  vSwUpdM_SegmentIdxType            segmentIdx;
} vSwUpdM_Appl_InitSegmentWorkspaceType;

typedef struct
{
  vSwUpdM_PartitionIdType           partitionId;
  vSwUpdM_ModuleIdType              moduleId;
} vSwUpdM_Appl_SegmentCacheValidityType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* PRQA S 3218 TAG_vSwUpdM_3218_FileScope */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */

#define VSWUPDM_START_SEC_APPL_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VSWUPDM_LOCAL CONST(vSwUpdM_UpdateStateType, VSWUPDM_APPL_CONST)        vSwUpdM_Appl_DefaultUpdateState                                       = VSWUPDM_UPDATE_STATE_IDLE;
VSWUPDM_LOCAL CONST(vSwUpdM_PartitionStateType, VSWUPDM_APPL_CONST)     vSwUpdM_Appl_DefaultPartitionStates[VSWUPDM_APPL_PARTITION_COUNT]     = { VSWUPDM_PART_STATE_ACTIVE, VSWUPDM_PART_STATE_INACTIVE, VSWUPDM_PART_STATE_BACKUP_TARGET };
VSWUPDM_LOCAL CONST(vSwUpdM_ValidType, VSWUPDM_APPL_CONST)              vSwUpdM_Appl_DefaultPartitionValidities[VSWUPDM_APPL_PARTITION_COUNT] = { VSWUPDM_VALIDITY_VALID, VSWUPDM_VALIDITY_INVALID, VSWUPDM_VALIDITY_INVALID };
VSWUPDM_LOCAL CONST(vSwUpdM_PartitionRevisionType, VSWUPDM_APPL_CONST)  vSwUpdM_Appl_DefaultPartitionRevisions[VSWUPDM_APPL_PARTITION_COUNT]  = { 1u, 0u, 0u };

VSWUPDM_LOCAL CONST(vSwUpdM_ModuleStateType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultModuleStates[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT] =
{
  { VSWUPDM_MODULE_STATE_VERIFIED, VSWUPDM_MODULE_STATE_VERIFIED, VSWUPDM_MODULE_STATE_VERIFIED },
  { VSWUPDM_MODULE_STATE_UNDEFINED, VSWUPDM_MODULE_STATE_UNDEFINED, VSWUPDM_MODULE_STATE_UNDEFINED },
  { VSWUPDM_MODULE_STATE_UNDEFINED, VSWUPDM_MODULE_STATE_UNDEFINED, VSWUPDM_MODULE_STATE_UNDEFINED }
};

VSWUPDM_LOCAL CONST(vSwUpdM_ValidType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultModuleValidities[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT] =
{
  { VSWUPDM_VALIDITY_VALID, VSWUPDM_VALIDITY_VALID, VSWUPDM_VALIDITY_VALID },
  { VSWUPDM_VALIDITY_INVALID, VSWUPDM_VALIDITY_INVALID, VSWUPDM_VALIDITY_INVALID },
  { VSWUPDM_VALIDITY_INVALID, VSWUPDM_VALIDITY_INVALID, VSWUPDM_VALIDITY_INVALID }
};

VSWUPDM_LOCAL CONST(vSwUpdM_ModuleRevisionType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultModuleRevisions[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT] =
{
  { 1u, 1u, 1u },
  { 0u, 0u, 0u },
  { 0u, 0u, 0u }
};

VSWUPDM_LOCAL CONST(vSwUpdM_ProgrammingAttemptsType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultModuleProgrammingAttempts[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT] =
{
  { 1u, 1u, 1u },
  { 0u, 0u, 0u },
  { 0u, 0u, 0u }
};

VSWUPDM_LOCAL CONST(vSwUpdM_RegionStateType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultRegionStates[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_REGION_COUNT] =
{
  { VSWUPDM_REGION_STATE_FINALIZED, VSWUPDM_REGION_STATE_FINALIZED, VSWUPDM_REGION_STATE_FINALIZED },
  { VSWUPDM_REGION_STATE_UNDEFINED, VSWUPDM_REGION_STATE_UNDEFINED, VSWUPDM_REGION_STATE_UNDEFINED },
  { VSWUPDM_REGION_STATE_UNDEFINED, VSWUPDM_REGION_STATE_UNDEFINED, VSWUPDM_REGION_STATE_UNDEFINED }
};

VSWUPDM_LOCAL CONST(vSwUpdM_ProgrammingAttemptsType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultRegionProgrammingAttempts[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_REGION_COUNT] =
{
  { 1u, 1u, 1u },
  { 0u, 0u, 0u },
  { 0u, 0u, 0u }
};

VSWUPDM_LOCAL CONST(vSwUpdM_AddressType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultRegionEraseAddresses[VSWUPDM_APPL_REGION_COUNT] = { 0u };

VSWUPDM_LOCAL CONST(vSwUpdM_SegmentDynamicAttributesType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultSegmentAttributes[VSWUPDM_APPL_MODULE_COUNT][VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT] =
{
  { 0u }
};  /* PRQA S 0686 */ /* MD_vSwUpdM_Appl_Rule9.3_0686_DefaultInitialization */

VSWUPDM_LOCAL CONST(vSwUpdM_AddressType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultSegmentWriteAddresses[VSWUPDM_APPL_MODULE_COUNT][VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT] =
{
  { 0u }
};  /* PRQA S 0686 */ /* MD_vSwUpdM_Appl_Rule9.3_0686_DefaultInitialization */

VSWUPDM_LOCAL CONST(uint32, VSWUPDM_APPL_CONST)                  vSwUpdM_Appl_DefaultSegmentCount         = 0u;
VSWUPDM_LOCAL CONST(vSwUpdM_PartitionIdType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultSegmentPartitionId   = VSWUPDM_INVALID_ID;
VSWUPDM_LOCAL CONST(vSwUpdM_ModuleIdType, VSWUPDM_APPL_CONST)    vSwUpdM_Appl_DefaultSegmentModuleId      = VSWUPDM_INVALID_ID;

VSWUPDM_LOCAL CONST(vSwUpdM_PartitionIdType, VSWUPDM_APPL_CONST) vSwUpdM_Appl_DefaultResumePartitionId    = VSWUPDM_INVALID_ID;
VSWUPDM_LOCAL CONST(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_APPL_CONST)  vSwUpdM_Appl_DefaultResumeInfo   = { {0u, 0u, VSWUPDM_PART_STATE_UNDEFINED, VSWUPDM_SID_NONE, VSWUPDM_RESUME_STATE_UNDEFINED, FALSE}, 0u };

#define VSWUPDM_STOP_SEC_APPL_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VSWUPDM_START_SEC_APPL_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VSWUPDM_LOCAL VAR(vSwUpdM_UpdateStateType, VSWUPDM_APPL_VAR)                vSwUpdM_Appl_UpdateState;
VSWUPDM_LOCAL VAR(vSwUpdM_Appl_GetterStateType, VSWUPDM_APPL_VAR)           vSwUpdM_Appl_GetterState;

/*
 * -= Start NV emulation =-
 * ------------------------
 * The following data shall be persisted in NVM and not RAM. RAM solution is just an example and shall emulate NVM data for some simple tests without any reset.
 * vSwUpdM expects that data is persisted in NVM when setter callout returns with E_OK. This is very important for e.g. unintended resets in combination with download resume feature.
 */
VSWUPDM_LOCAL VAR(vSwUpdM_PartitionStateType, VSWUPDM_APPL_VAR)             vSwUpdM_Appl_PartitionStates[VSWUPDM_APPL_PARTITION_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_ValidType, VSWUPDM_APPL_VAR)                      vSwUpdM_Appl_PartitionValidities[VSWUPDM_APPL_PARTITION_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_PartitionRevisionType, VSWUPDM_APPL_VAR)          vSwUpdM_Appl_PartitionRevisions[VSWUPDM_APPL_PARTITION_COUNT];

VSWUPDM_LOCAL VAR(vSwUpdM_ModuleStateType, VSWUPDM_APPL_VAR)                vSwUpdM_Appl_ModuleStates[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_ValidType, VSWUPDM_APPL_VAR)                      vSwUpdM_Appl_ModuleValidities[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_ModuleRevisionType, VSWUPDM_APPL_VAR)             vSwUpdM_Appl_ModuleRevisions[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_ProgrammingAttemptsType, VSWUPDM_APPL_VAR)        vSwUpdM_Appl_ModuleProgrammingAttempts[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT];

VSWUPDM_LOCAL VAR(vSwUpdM_RegionStateType, VSWUPDM_APPL_VAR)                vSwUpdM_Appl_RegionStates[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_REGION_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_ProgrammingAttemptsType, VSWUPDM_APPL_VAR)        vSwUpdM_Appl_RegionProgrammingAttempts[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_REGION_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_AddressType, VSWUPDM_APPL_VAR)                    vSwUpdM_Appl_RegionEraseAddresses[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_REGION_COUNT];

VSWUPDM_LOCAL VAR(vSwUpdM_SegmentDynamicAttributesType, VSWUPDM_APPL_VAR)   vSwUpdM_Appl_SegmentAttributes[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT][VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_AddressType, VSWUPDM_APPL_VAR)                    vSwUpdM_Appl_SegmentWriteAddresses[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT][VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT];
VSWUPDM_LOCAL VAR(uint32, VSWUPDM_APPL_VAR)                                 vSwUpdM_Appl_SegmentCount[VSWUPDM_APPL_PARTITION_COUNT][VSWUPDM_APPL_MODULE_COUNT];

VSWUPDM_LOCAL VAR(vSwUpdM_ExtendedResumeInfoType, VSWUPDM_APPL_VAR)         vSwUpdM_Appl_ResumeInfo;
/* -= End NV emulation =- */

/*
 * -= Start RAM cache for module relevant segment data =-
 * ------------------------------------------------------
 * The following data will be initialized on every implicit or explicit opening of a module. It's a RAM cache, which will be set up in vSwUpdM_Appl_GetRegionState by
 * calling vSwUpdM_Appl_InitSegmentInfo. This handling ensures that all NVM read access issues will not issue negative results during further sequence and segment
 * getter functions will not cause bad results in further program flow.
 */
VSWUPDM_LOCAL VAR(uint32, VSWUPDM_APPL_VAR)                                 vSwUpdM_Appl_Cache_SegmentCount;
VSWUPDM_LOCAL VAR(vSwUpdM_SegmentDynamicAttributesType, VSWUPDM_APPL_VAR)   vSwUpdM_Appl_Cache_SegmentAttributes[VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT];
VSWUPDM_LOCAL VAR(vSwUpdM_AddressType, VSWUPDM_APPL_VAR)                    vSwUpdM_Appl_Cache_SegmentWriteAddresses[VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT];
/* -= End RAM Cache for module relevant segment data =- */

/* Remember module instance, whose attributes are currently cached. */
VSWUPDM_LOCAL VAR(vSwUpdM_Appl_SegmentCacheValidityType, VSWUPDM_APPL_VAR)  vSwUpdM_Appl_Cache_ValidityInfo;

VSWUPDM_LOCAL VAR(vSwUpdM_OpStatusType, VSWUPDM_APPL_VAR)                   vSwUpdM_Appl_InitSegmentInfo_Status;
VSWUPDM_LOCAL VAR(vSwUpdM_Appl_InitSegmentWorkspaceType, VSWUPDM_APPL_VAR)  vSwUpdM_Appl_InitSegmentInfo_Workspace;

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
VSWUPDM_LOCAL VAR(vSwUpdM_OpStatusType, VSWUPDM_APPL_VAR)                   vSwUpdM_Appl_ResetModule_Status;
VSWUPDM_LOCAL VAR(vSwUpdM_Appl_ResetModuleWorkspaceType, VSWUPDM_APPL_VAR)  vSwUpdM_Appl_ResetModule_Workspace;
VSWUPDM_LOCAL VAR(vSwUpdM_Appl_RepairReasonType, VSWUPDM_APPL_VAR)          vSwUpdM_Appl_GetRegionRepairReason;
#endif

#define VSWUPDM_STOP_SEC_APPL_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:TAG_vSwUpdM_3218_FileScope */
/**********************************************************************************************************************
*  LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************************/
#define VSWUPDM_START_SEC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
/**********************************************************************************************************************
 *  vSwUpdM_Appl_ResetModule()
 *********************************************************************************************************************/
/*! \brief        Reset all relevant NV values of given module.
 *  \details      -
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *  \pre          -
 *  \remark       This function shall only be called by following "getter" functions:
 *                #vSwUpdM_Appl_GetRegionState
 *                #vSwUpdM_Appl_GetRegionEraseAddress
 *                #vSwUpdM_Appl_GetSegmentCount
 *                #vSwUpdM_Appl_GetSegmentAttributes
 *                #vSwUpdM_Appl_GetSegmentWriteAddress
 *                The function itself calls only "setter" API. The implementation is not protected against recursive
 *                calls. Please check that the called "setter" functions don't call any of the above "getter" functions
 *                or implement a protection against recursive calls.
 *                Please keep in mind that any repair measure sequence can be interrupted by unintended reset.
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetModule(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId);
#endif

/**********************************************************************************************************************
 *  vSwUpdM_Appl_InitSegmentInfo()
 *********************************************************************************************************************/
/*! \brief        Initialize segment information for one module in RAM.
 *  \details      -
 *  \param[in]    OpStatus          Current state of operation:
 *                                  - #VSWUPDM_OP_STATUS_INITIAL: Initial call, trigger operation
 *                                  - #VSWUPDM_OP_STATUS_PENDING: Current operation is pending
 *                                  - #VSWUPDM_OP_STATUS_FINAL: Final call, perform clean-up (not used yet)
 *                                  - #VSWUPDM_OP_STATUS_CANCEL: Cancel pending operation (not used yet)
 *  \param[in]    PartitionId       Identifier of the partition.
 *  \param[in]    ModuleId          Identifier of the module.
 *  \return       Return value shall represent the current state of intended operation requested by this function.
 *                Any other value than the mentioned return values will be treated like #E_NOT_OK.
 *                - #E_OK              Operation successfully finished.
 *                - #E_NOT_OK          Operation failed.
 *                - #VSWUPDM_E_PENDING Operation started, but still pending
 *                - #VSWUPDM_E_BUSY    Operation could not be started, retry later with status #VSWUPDM_OP_STATUS_INITIAL
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *  \pre          -
 *  \remark       This function shall only be called by vSwUpdM_Appl_GetRegionState.
 *                The function itself calls only "getter" API. The implementation is not protected against recursive
 *                calls.
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_InitSegmentInfo(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
/**********************************************************************************************************************
 *  vSwUpdM_Appl_ResetModule()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetModule(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId)
{
  Std_ReturnType retVal = VSWUPDM_E_PENDING;
  Std_ReturnType tmpRetVal = VSWUPDM_E_PENDING;

  if (OpStatus == VSWUPDM_OP_STATUS_INITIAL)
  {
    vSwUpdM_Appl_ResetModule_Workspace.currentStep = VSWUPDM_APPL_WORKING_STEP_RESET_REGION_STATE;
    vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus  = VSWUPDM_OP_STATUS_INITIAL;
    vSwUpdM_Appl_ResetModule_Workspace.returnValue = E_OK;
    vSwUpdM_Appl_ResetModule_Workspace.regionIdx   = 0u;

    if (vSwUpdM_GetNumberOfRegionsOfModule(&(vSwUpdM_Appl_ResetModule_Workspace.regionCount), ModuleId) != E_OK)
    {
      /* Region count couldn't be evaluated. Continue with 0. Remember bad result. */
      vSwUpdM_Appl_ResetModule_Workspace.regionCount = 0u;
      vSwUpdM_Appl_ResetModule_Workspace.returnValue = E_NOT_OK;
    }
  }
  else
  {
    switch (vSwUpdM_Appl_ResetModule_Workspace.currentStep)
    {
      /* 1. Reset Region related information by setting all region states of module to undefined. */
      case VSWUPDM_APPL_WORKING_STEP_RESET_REGION_STATE:
      {
        vSwUpdM_Appl_ResetModule_Workspace.nextStep = VSWUPDM_APPL_WORKING_STEP_RESET_MODULE_STATE;

        if (vSwUpdM_Appl_ResetModule_Workspace.regionCount == 0u)
        {
          tmpRetVal = E_OK; /* This will force next step. */
        }
        else
        {
          if (vSwUpdM_Appl_ResetModule_Workspace.regionIdx < vSwUpdM_Appl_ResetModule_Workspace.regionCount)
          {
            vSwUpdM_RegionIdType regionId;

            if (vSwUpdM_GetRegionIdOfModuleByIndex(&regionId, ModuleId, vSwUpdM_Appl_ResetModule_Workspace.regionIdx) == E_OK)
            {
              tmpRetVal = vSwUpdM_Appl_SetRegionState(vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus, PartitionId, ModuleId, regionId, VSWUPDM_REGION_STATE_UNDEFINED, TRUE);
            }
            else
            {
              tmpRetVal = E_NOT_OK;
            }
          }
        }
        break;
      }
      /* 2. Reset module state to #VSWUPDM_MODULE_STATE_UNDEFINED. */
      case VSWUPDM_APPL_WORKING_STEP_RESET_MODULE_STATE:
      {
        vSwUpdM_Appl_ResetModule_Workspace.nextStep = VSWUPDM_APPL_WORKING_STEP_RESET_SEGMENT_COUNT;
        tmpRetVal = vSwUpdM_Appl_SetModuleState(vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus, PartitionId, ModuleId, VSWUPDM_MODULE_STATE_UNDEFINED, TRUE);
        break;
      }
      /* 3. Reset segment information by setting segment count to 0. */
      case VSWUPDM_APPL_WORKING_STEP_RESET_SEGMENT_COUNT:
      {
        vSwUpdM_Appl_ResetModule_Workspace.nextStep = VSWUPDM_APPL_WORKING_STEP_RESET_RESUME_INFO;
        tmpRetVal = vSwUpdM_Appl_SetSegmentCount(vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus, PartitionId, ModuleId, 0u, TRUE);
        break;
      }
      /* 4. ResumeInfo must be reset to cancel all possible resume actions. */
      case VSWUPDM_APPL_WORKING_STEP_RESET_RESUME_INFO:
      {
        vSwUpdM_Appl_ResetModule_Workspace.nextStep = VSWUPDM_APPL_WORKING_STEP_FINISH;
        tmpRetVal = vSwUpdM_Appl_SetResumeInfo(vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus, &vSwUpdM_Appl_DefaultResumeInfo, TRUE);
        break;
      }
      /* 5. Send final response. */
      case VSWUPDM_APPL_WORKING_STEP_FINISH:
      {
        /* Report overall result. */
        retVal = vSwUpdM_Appl_ResetModule_Workspace.returnValue;
        break;
      }
      default:
      {
        /*
         * Shall never happen. Possible useful actions:
         *  - Call DET to detect the state during development
         *  - Reinitialize work space and restart actions
         */
        retVal = E_NOT_OK; /* Avoid calling of this function endlessly. */
        break;
      }
    }

    /* Evaluate tmpRetVal: */
    switch (tmpRetVal)
    {
      case VSWUPDM_E_BUSY:
      {
        /* Stay in current state and wait for ready. */
        break;
      }
      case VSWUPDM_E_PENDING:
      {
        /* Wait for final result. */
        vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus = VSWUPDM_OP_STATUS_PENDING;
        break;
      }
      /* Final result in tmpRetVal. */
      default:
      {
        /*
         * tmpRetVal == E_OK         Everything is fine
         * tmpRetVal == E_NOT_OK     Setting new NV value failed, assuming that "getter" can detect the issue for
         *                           sure and will report default values by itself on next call. So continue anyway.
         */
        /* Reset local state machine for each step. */
        vSwUpdM_Appl_ResetModule_Workspace.wsOpStatus = VSWUPDM_OP_STATUS_INITIAL;

        /* Switch to next state. */
        if (vSwUpdM_Appl_ResetModule_Workspace.regionIdx >= vSwUpdM_Appl_ResetModule_Workspace.regionCount)
        {
          /* Enter next state */
          vSwUpdM_Appl_ResetModule_Workspace.currentStep = vSwUpdM_Appl_ResetModule_Workspace.nextStep;
        }
        else
        {
          /* Loop through regions before entering next state. */
          vSwUpdM_Appl_ResetModule_Workspace.regionIdx++;
        }

        if (tmpRetVal != E_OK)
        {
          /* Remember illegal retVal values and E_NOT_OK as final result. */
          vSwUpdM_Appl_ResetModule_Workspace.returnValue = E_NOT_OK;
        }
        break;
      }
    }
  }

  return retVal;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
}
#endif

 /**********************************************************************************************************************
 *  vSwUpdM_Appl_InitSegmentInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */

VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_InitSegmentInfo(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId)
{
  Std_ReturnType retVal = VSWUPDM_E_PENDING;
  Std_ReturnType tmpRetVal = VSWUPDM_E_PENDING;

  if (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
  {
    if (OpStatus == VSWUPDM_OP_STATUS_INITIAL)
    {
      /* Initial local states on first call. */
      vSwUpdM_Appl_InitSegmentInfo_Workspace.currentStep = VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_COUNT;
      vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus = VSWUPDM_OP_STATUS_INITIAL;
      vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx = 0u;
    }
    else
    {
      switch (vSwUpdM_Appl_InitSegmentInfo_Workspace.currentStep)
      {
        /* 1. Get segment count to know how many segments need to be initialized. */
        case VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_COUNT:
        {
          vSwUpdM_Appl_InitSegmentInfo_Workspace.nextStep = VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_ATTRIBUTES;
          tmpRetVal = vSwUpdM_Appl_GetSegmentCount(vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus, PartitionId, ModuleId, &vSwUpdM_Appl_Cache_SegmentCount);

          break;
        }
        /* 2. Read Segment attributes for current segment index. */
        case VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_ATTRIBUTES:
        {
          vSwUpdM_Appl_InitSegmentInfo_Workspace.nextStep = VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_WRITE_ADDRESS;
          tmpRetVal = vSwUpdM_Appl_GetSegmentAttributes(vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus, PartitionId, ModuleId, vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx,
                                                        &vSwUpdM_Appl_Cache_SegmentAttributes[vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx]);
          break;
        }
        /* 3. Read Segment write address for current segment index. */
        case VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_WRITE_ADDRESS:
        {
          vSwUpdM_Appl_InitSegmentInfo_Workspace.nextStep = VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_ATTRIBUTES;
          tmpRetVal = vSwUpdM_Appl_GetSegmentWriteAddress(vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus, PartitionId, ModuleId, vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx,
                                                          &vSwUpdM_Appl_Cache_SegmentWriteAddresses[vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx]);
          break;
        }
        default:
          /*
           * Shall never happen. Possible useful actions:
           * - Call DET to detect the state during development
           * - Reinitialize work space and restart actions
           */
          retVal = E_NOT_OK; /* Avoid calling of this function endlessly. */
          break;
      }

      /* Evaluate tmpRetVal: */
      switch (tmpRetVal)
      {
        case VSWUPDM_E_BUSY:
        {
          /* Stay in current state and wait for ready. */
          retVal = VSWUPDM_E_BUSY;
          break;
        }
        case VSWUPDM_E_PENDING:
        {
          /* Wait for final result. */
          vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus = VSWUPDM_OP_STATUS_PENDING;
          break;
        }
        /* Final result in tmpRetVal. */
        default:
        {
          /*
           * tmpRetVal == E_OK         Everything is fine
           * tmpRetVal != E_OK         Report observed issue.
           */

          /* Reset local state machine for each step. */
          vSwUpdM_Appl_InitSegmentInfo_Workspace.wsOpStatus = VSWUPDM_OP_STATUS_INITIAL;

          /* Switch to next state. */
          if (vSwUpdM_Appl_InitSegmentInfo_Workspace.currentStep == VSWUPDM_APPL_SEGMENT_INIT_STEP_INIT_SEGMENT_WRITE_ADDRESS)
          {
            /* Loop through segments before entering next state. */
            vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx++;
          }

          if (vSwUpdM_Appl_InitSegmentInfo_Workspace.segmentIdx < vSwUpdM_Appl_Cache_SegmentCount)
          {
            /* Enter next state */
            vSwUpdM_Appl_InitSegmentInfo_Workspace.currentStep = vSwUpdM_Appl_InitSegmentInfo_Workspace.nextStep;
          }
          else
          {
            /* Reaching this state without any errors means that everything went fine. */
            retVal = E_OK;
          }

          if (tmpRetVal != E_OK)
          {
            /* Report E_NOT_OK as final result. */
            retVal = E_NOT_OK;
          }

          break;
        }
      }
    }
  }
  else
  {
    /* Shall never be reached - Code was written to avoid MISRA warnings. */
    retVal = E_NOT_OK;
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  vSwUpdM_Appl_Init
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Perform necessary initializations.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_Init(vSwUpdM_OpStatusType OpStatus)
{
  vSwUpdM_PartitionIdType partitionId;
  vSwUpdM_ModuleIdType    moduleId;
  vSwUpdM_RegionIdType    regionId;
  vSwUpdM_SegmentIdxType  segmentIdx;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_Appl_UpdateState                      = vSwUpdM_Appl_DefaultUpdateState;
  vSwUpdM_Appl_Cache_ValidityInfo.moduleId      = VSWUPDM_INVALID_ID;
  vSwUpdM_Appl_Cache_ValidityInfo.partitionId   = VSWUPDM_INVALID_ID;

  for (partitionId = 0u; partitionId < VSWUPDM_APPL_PARTITION_COUNT; partitionId++)
  {
    vSwUpdM_Appl_PartitionStates[partitionId]     = vSwUpdM_Appl_DefaultPartitionStates[partitionId];
    vSwUpdM_Appl_PartitionValidities[partitionId] = vSwUpdM_Appl_DefaultPartitionValidities[partitionId];
    vSwUpdM_Appl_PartitionRevisions[partitionId]  = vSwUpdM_Appl_DefaultPartitionRevisions[partitionId];

    for (moduleId = 0u; moduleId < VSWUPDM_APPL_MODULE_COUNT; moduleId++)
    {
      vSwUpdM_Appl_ModuleStates[partitionId][moduleId]      = vSwUpdM_Appl_DefaultModuleStates[partitionId][moduleId];
      vSwUpdM_Appl_ModuleValidities[partitionId][moduleId]  = vSwUpdM_Appl_DefaultModuleValidities[partitionId][moduleId];
      vSwUpdM_Appl_ModuleRevisions[partitionId][moduleId]   = vSwUpdM_Appl_DefaultModuleRevisions[partitionId][moduleId];

      vSwUpdM_Appl_SegmentCount[partitionId][moduleId] = vSwUpdM_Appl_DefaultSegmentCount;
      for (segmentIdx = 0u; segmentIdx < VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT; segmentIdx++)
      {
        vSwUpdM_Appl_SegmentAttributes[partitionId][moduleId][segmentIdx] = vSwUpdM_Appl_DefaultSegmentAttributes[moduleId][segmentIdx];
      }
      for (segmentIdx = 0u; segmentIdx < VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT; segmentIdx++)
      {
        vSwUpdM_Appl_SegmentWriteAddresses[partitionId][moduleId][segmentIdx] = vSwUpdM_Appl_DefaultSegmentWriteAddresses[moduleId][segmentIdx];
      }
    }

    for (regionId = 0u; regionId < VSWUPDM_APPL_REGION_COUNT; regionId++)
    {
      vSwUpdM_Appl_RegionStates[partitionId][regionId] = vSwUpdM_Appl_DefaultRegionStates[partitionId][regionId];
      vSwUpdM_Appl_RegionEraseAddresses[partitionId][regionId] = vSwUpdM_Appl_DefaultRegionEraseAddresses[regionId];
    }
  }

  vSwUpdM_Appl_ResumeInfo         = vSwUpdM_Appl_DefaultResumeInfo;

  return E_OK;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetUpdateState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read persisted update state.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetUpdateState(
  vSwUpdM_OpStatusType OpStatus,
  P2VAR(vSwUpdM_UpdateStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State)
{
  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  *State = vSwUpdM_Appl_UpdateState;

  return E_OK;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetUpdateState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist update state.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetUpdateState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_UpdateStateType State,
  boolean SyncFlag)
{
  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_Appl_UpdateState = State;

  return E_OK;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read persisted partition state from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    *State = vSwUpdM_Appl_PartitionStates[PartitionId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist partition state in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_PartitionStateType Mask,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Mask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    vSwUpdM_Appl_PartitionStates[PartitionId] = State;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionValid
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read partition validity from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_ValidType, AUTOMATIC, VSWUPDM_APPL_VAR) Valid)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    *Valid = vSwUpdM_Appl_PartitionValidities[PartitionId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionValid
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist partition validity in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ValidType Valid,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Valid); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    vSwUpdM_Appl_PartitionValidities[PartitionId] = Valid;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetPartitionRevision
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read partition revision from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetPartitionRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  P2VAR(vSwUpdM_PartitionRevisionType, AUTOMATIC, VSWUPDM_APPL_VAR) Revision)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    *Revision = vSwUpdM_Appl_PartitionRevisions[PartitionId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetPartitionRevision
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist partition revision in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetPartitionRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_PartitionRevisionType Revision,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Revision); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
  {
    vSwUpdM_Appl_PartitionRevisions[PartitionId] = Revision;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read module state from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ModuleStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    *State = vSwUpdM_Appl_ModuleStates[PartitionId][ModuleId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist module state in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleStateType State,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    vSwUpdM_Appl_ModuleStates[PartitionId][ModuleId] = State;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleValid
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read module validity from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ValidType, AUTOMATIC, VSWUPDM_APPL_VAR) Valid)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    *Valid = vSwUpdM_Appl_ModuleValidities[PartitionId][ModuleId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleValid
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist module validity in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleValid(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ValidType Valid,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Valid); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    vSwUpdM_Appl_ModuleValidities[PartitionId][ModuleId] = Valid;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleRevision
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read module revision from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ModuleRevisionType, AUTOMATIC, VSWUPDM_APPL_VAR) Revision)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    *Revision = vSwUpdM_Appl_ModuleRevisions[PartitionId][ModuleId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleRevision
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist module revision in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleRevision(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ModuleRevisionType Revision,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Revision); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    vSwUpdM_Appl_ModuleRevisions[PartitionId][ModuleId] = Revision;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetModuleProgrammingAttempts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read module programming attempts counter from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetModuleProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    *ProgrammingAttempts = vSwUpdM_Appl_ModuleProgrammingAttempts[PartitionId][ModuleId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetModuleProgrammingAttempts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist module programming attempts counter in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetModuleProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ProgrammingAttempts); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    vSwUpdM_Appl_ModuleProgrammingAttempts[PartitionId][ModuleId] = ProgrammingAttempts;
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read region state from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_RegionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) State)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (OpStatus == VSWUPDM_OP_STATUS_INITIAL)
  {
#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
    /* (Re-)Initialize operation state of ResetModule function for first call. */
    vSwUpdM_Appl_ResetModule_Status = VSWUPDM_OP_STATUS_INITIAL;
    /* If repair measures will be performed the default reason is this getter function. */
    vSwUpdM_Appl_GetRegionRepairReason = VSWUPDM_APPL_REPAIR_REASON_GET_REGION_STATE;
#endif
    /* Initialize getter action */
    vSwUpdM_Appl_GetterState = VSWUPDM_APPL_GETTER_STATE_GET_VALUE;
    /* (Re-)Initialize operation state of InitSegmentInfo function for first call. */
    vSwUpdM_Appl_InitSegmentInfo_Status = VSWUPDM_OP_STATUS_INITIAL;
  }

  switch (vSwUpdM_Appl_GetterState)
  {
    case VSWUPDM_APPL_GETTER_STATE_GET_VALUE:
    {
      if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
        && (RegionId < VSWUPDM_APPL_REGION_COUNT) )
      {
        *State = vSwUpdM_Appl_RegionStates[PartitionId][RegionId];
        result = E_OK;
      }

      if (result == E_OK)
      {
        /* Initialize segment information in cache in case that reading region state works without issues
           and cache is not already initialized for this module. */
        if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId != ModuleId)
          || (vSwUpdM_Appl_Cache_ValidityInfo.partitionId != PartitionId) )
        {
          vSwUpdM_Appl_GetterState = VSWUPDM_APPL_GETTER_STATE_INIT_SEGMENT_INFO;
          result = VSWUPDM_E_PENDING;
        }
      }

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
      /* In case of error start repair sequence. */
      if (result == E_NOT_OK)
      {
        /*
         * Possible root causes for failing getting RegionState:
         * - Permanent issue (will raise now and in future): ECU must be replaced. No actions will help.
         * - Temporary issue, possible actions:
         *      1. Maybe there are ways to detect and fix the root cause.
         *          --> Customers responsibility, because project specific.
         *      2. Repeat single action several times (assuming race conditions are changing states).
         *          --> Customers responsibility, because project specific.
         *      3. Repeat sequences (Try to go back to known good state and repeat).
         *          --> Following implementation provides example code resetting all relevant module states to default.
         */
        vSwUpdM_Appl_GetterState = VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR;
        result = VSWUPDM_E_PENDING;
      }
#endif
      break;
    }
#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
    case VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR:
    {
      /*
       * A Region is part of a Module. In case the state of a single region is unknown it's recommended to fall back
       * to default state for the whole module. The following actions shall ensure that the affected module goes back to its
       * default state.
       */
      result = vSwUpdM_Appl_ResetModule(vSwUpdM_Appl_ResetModule_Status, PartitionId, ModuleId);

      /* Remain in current state if VSWUPDM_E_BUSY was returned. */
      if (result != VSWUPDM_E_BUSY)
      {
        /* Otherwise, ensure that vSwUpdM_Appl_ResetModule is called with VSWUPDM_OP_STATUS_INITIAL only once. */
        vSwUpdM_Appl_ResetModule_Status = VSWUPDM_OP_STATUS_PENDING;

        /* Report VSWUPDM_REGION_STATE_UNDEFINED after repairing module states. This value should also be in NV memory. */
        *State = VSWUPDM_REGION_STATE_UNDEFINED;

        /* Remap final responses after vSwUpdM_Appl_ResetModule returned with final response. */
        if (result != VSWUPDM_E_PENDING)
        {
          if (vSwUpdM_Appl_GetRegionRepairReason == VSWUPDM_APPL_REPAIR_REASON_GET_SEGMENT_INFO)
          {
            /* A failed GetRegionState call shall always cause E_OK if the reason is one of the segment getter functions. */
            result = E_OK;
          }
          else
          {
            /* A failed GetRegionState call shall always cause E_NOT_OK if the reason is the region state NV value. */
            result = E_NOT_OK;
          }
        }
      }

      break;
    }
#endif
    case VSWUPDM_APPL_GETTER_STATE_INIT_SEGMENT_INFO:
    {
      result = vSwUpdM_Appl_InitSegmentInfo(vSwUpdM_Appl_InitSegmentInfo_Status, PartitionId, ModuleId);

      /* Remain in current state if VSWUPDM_E_BUSY was returned. */
       /* PRQA S 2991, 2995 1 */ /* MD_vSwUpdM_Appl_Rule13.7_2991_2995_ExampleCode */
      if (result != VSWUPDM_E_BUSY)
      {
        /* Otherwise, ensure that vSwUpdM_Appl_InitSegmentInfo is called with VSWUPDM_OP_STATUS_INITIAL only once. */
        vSwUpdM_Appl_InitSegmentInfo_Status = VSWUPDM_OP_STATUS_PENDING;
      }

      /* If result is not OK there is an issue with segment getter function. Repair actions needs to be done. */
      if (result == E_NOT_OK)
      {
        /* Indicate that segment information in cache are not valid. */
        vSwUpdM_Appl_Cache_ValidityInfo.moduleId      = VSWUPDM_INVALID_ID;
        vSwUpdM_Appl_Cache_ValidityInfo.partitionId   = VSWUPDM_INVALID_ID;

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
        /* Execute standard repair measures for whole module. This also reset region state. */
        vSwUpdM_Appl_GetterState = VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR;
        /* If repair measures are triggered by issues with segment getter functions, remember the reason. */
        vSwUpdM_Appl_GetRegionRepairReason = VSWUPDM_APPL_REPAIR_REASON_GET_SEGMENT_INFO;
        result = VSWUPDM_E_PENDING;
#endif
      }

      /* Remember that segment information cache is valid for this module and partition. */
      if (result == E_OK)
      {
        vSwUpdM_Appl_Cache_ValidityInfo.moduleId      = ModuleId;
        vSwUpdM_Appl_Cache_ValidityInfo.partitionId   = PartitionId;

        /* Return final state together with final response. */
        *State = vSwUpdM_Appl_RegionStates[PartitionId][RegionId];
      }

      break;
    }
    default:
    {
      /*
       * Shall never happen. Possible useful actions:
       *- Call DET to detect the state during development
       *- Reinitialize work space and restart actions
       */
      result = E_NOT_OK; /* Avoid calling of this function endlessly. */
      break;
    }
  }


  return result;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionState
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist region state in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionState(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_RegionStateType State,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (RegionId < VSWUPDM_APPL_REGION_COUNT) )
  {
    vSwUpdM_Appl_RegionStates[PartitionId][RegionId] = State;
    result = E_OK;
  }

  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionProgrammingAttempts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read region programming attempts counter from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_ProgrammingAttemptsType, AUTOMATIC, VSWUPDM_APPL_VAR) ProgrammingAttempts)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (RegionId < VSWUPDM_APPL_REGION_COUNT) )
  {
    *ProgrammingAttempts = vSwUpdM_Appl_RegionProgrammingAttempts[PartitionId][RegionId];
    result = E_OK;
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionProgrammingAttempts
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist region programming attempts counter in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionProgrammingAttempts(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ProgrammingAttempts); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (RegionId < VSWUPDM_APPL_REGION_COUNT) )
  {
    vSwUpdM_Appl_RegionProgrammingAttempts[PartitionId][RegionId] = ProgrammingAttempts;
    result = E_OK;
  }

  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetRegionEraseAddress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read region erase address from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetRegionEraseAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) EraseAddress)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(EraseAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
  if (OpStatus == VSWUPDM_OP_STATUS_INITIAL)
  {
    /* (Re-)Initialize operation state of ResetModule function for first call. */
    vSwUpdM_Appl_ResetModule_Status = VSWUPDM_OP_STATUS_INITIAL;
    /* Initialize getter action */
    vSwUpdM_Appl_GetterState        = VSWUPDM_APPL_GETTER_STATE_GET_VALUE;
  }

  switch (vSwUpdM_Appl_GetterState)
  {
    case VSWUPDM_APPL_GETTER_STATE_GET_VALUE:
    {
#endif
      if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
        && (RegionId < VSWUPDM_APPL_REGION_COUNT) )
      {
        *EraseAddress = vSwUpdM_Appl_RegionEraseAddresses[PartitionId][RegionId];
        result = E_OK;
      }
#if defined( VSWUPDM_APPL_ENABLE_RESET_MODULE_STATES_EXAMPLE )
      /* In case of error start repair sequence. */
      if (result == E_NOT_OK)
      {
        /*
         * Possible root causes for failing getting RegionEraseAddresses:
         * - Permanent issue (will raise now and in future): ECU must be replaced. No actions will help.
         * - Temporary issue, possible actions:
         * 1. Maybe there are ways to detect and fix the root cause..
         * --> customers responsibility, because project specific.
         * 2. Repeat single action several times (assuming race conditions are changing states)
         * --> customers responsibility, because project specific.
         * 3. Repeat sequences (Try to go back to known good state and repeat)
         * --> Following implementation provides example code resetting all relevant module states to default.
         */
        vSwUpdM_Appl_GetterState = VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR;
        result = VSWUPDM_E_PENDING;
      }
      break;
    }
    case VSWUPDM_APPL_GETTER_STATE_EXECUTE_REPAIR:
    {
      /*
       * A Region is part of a Module. In case RegionEraseAddresses are unknown it's recommended to fall back
       * to default state for the whole module. The following actions shall ensure that the affected module goes back to its
       * default state.
       */
      result = vSwUpdM_Appl_ResetModule(vSwUpdM_Appl_ResetModule_Status, PartitionId, ModuleId);

      /* Ensure that vSwUpdM_Appl_ResetModule is called with VSWUPDM_OP_STATUS_INITIAL only once. */
      vSwUpdM_Appl_ResetModule_Status = VSWUPDM_OP_STATUS_PENDING;

      /*
       * If vSwUpdM_Appl_ResetModule returns success: Report E_NOT_OK since the state of region is UNDEFINED
       * and therefore all erase addresses are undefined, too.
       */
      if (result == E_OK)
      {
        result = E_NOT_OK;
      }

      break;
    }
    default:
    {
      /*
       * Shall never happen. Possible useful actions:
       * - Call DET to detect the state during development
       * - Reinitialize work space and restart actions
       */
      result = E_NOT_OK; /* Avoid calling of this function endlessly. */
      break;
    }
  }
#endif

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetRegionEraseAddress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist region erase addresses in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetRegionEraseAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_RegionIdType RegionId,
  vSwUpdM_AddressType EraseAddress,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(RegionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(EraseAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if (RegionId < VSWUPDM_APPL_REGION_COUNT)
  {
    vSwUpdM_Appl_RegionEraseAddresses[PartitionId][RegionId] = EraseAddress;
    result = E_OK;
  }

  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentCount
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read segment count from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 *              This function shall be called by GetRegionState callout via vSwUpdM_Appl_InitSegmentInfo to access
 *              NV values. All other calls report cache values. All recommended repair actions are handled
 *              in vSwUpdM_Appl_GetRegionState.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentCount(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentCount)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentCount); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT) )
  {
    result = E_OK;

    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId))
    {
      /* In case that the value is already in cache, take it from there. */
      *SegmentCount = vSwUpdM_Appl_Cache_SegmentCount;
    }
    else
    {
      /* Otherwise read it directly from NV. */
      *SegmentCount = vSwUpdM_Appl_SegmentCount[PartitionId][ModuleId];
    }
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentCount
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist segment count in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentCount(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 SegmentCount,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentCount); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
    && (SegmentCount < VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT) )
  {
    vSwUpdM_Appl_SegmentCount[PartitionId][ModuleId] = SegmentCount;
    result = E_OK;

    /* Update cache if cache is affected. */
    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId) )
    {
      /* PRQA S 2991, 2995 1 */ /* MD_vSwUpdM_Appl_Rule13.7_2991_2995_ExampleCode */
      if (result == E_OK)
      {
        vSwUpdM_Appl_Cache_SegmentCount = SegmentCount;
      }
      else
      {
        /* Invalidate cache in case of error. */
        /* PRQA S 2880 1 */ /* MD_vSwUpdM_Appl_Rule2.1_2880_ExampleCode */
        vSwUpdM_Appl_Cache_ValidityInfo.moduleId    = VSWUPDM_INVALID_ID;
        vSwUpdM_Appl_Cache_ValidityInfo.partitionId = VSWUPDM_INVALID_ID;
      }
    }
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentAttributes
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read segment attributes from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 *              This function shall be called by GetRegionState callout via vSwUpdM_Appl_InitSegmentInfo to access
 *              NV values. All other calls report cache values. All recommended repair actions are handled
 *              in vSwUpdM_Appl_GetRegionState.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentAttributes(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2VAR(vSwUpdM_SegmentDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentAttributes); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
    && (SegmentIdx < VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT) )
  {
    result = E_OK;

    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId) )
    {
      /* In case that the value is already in cache, take it from there. */
      *SegmentAttributes = vSwUpdM_Appl_Cache_SegmentAttributes[SegmentIdx];
    }
    else
    {
      /* Otherwise read it directly from NV. */
      *SegmentAttributes = vSwUpdM_Appl_SegmentAttributes[PartitionId][ModuleId][SegmentIdx];
    }
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentAttributes
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist segment attributes in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentAttributes(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2CONST(vSwUpdM_SegmentDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentAttributes,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentAttributes); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
    && (SegmentIdx < VSWUPDM_APPL_EXTERNAL_SEGMENT_COUNT) )
  {
    vSwUpdM_Appl_SegmentAttributes[PartitionId][ModuleId][SegmentIdx]  = *SegmentAttributes;
    result = E_OK;

    /* Update cache if cache is affected. */
    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId) )
    {
      /* PRQA S 2991, 2995 1 */ /* MD_vSwUpdM_Appl_Rule13.7_2991_2995_ExampleCode */
      if (result == E_OK)
      {
        vSwUpdM_Appl_Cache_SegmentAttributes[SegmentIdx] = *SegmentAttributes;
      }
      else
      {
        /* Invalidate cache in case of error. */
        /* PRQA S 2880 1 */ /* MD_vSwUpdM_Appl_Rule2.1_2880_ExampleCode */
        vSwUpdM_Appl_Cache_ValidityInfo.moduleId    = VSWUPDM_INVALID_ID;
        vSwUpdM_Appl_Cache_ValidityInfo.partitionId = VSWUPDM_INVALID_ID;
      }
    }
  }

  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetSegmentWriteAddress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read segment write addresses from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 *              This function shall be called by GetRegionState callout via vSwUpdM_Appl_InitSegmentInfo to access
 *              NV values. All other calls report cache values. All recommended repair actions are handled
 *              in vSwUpdM_Appl_GetRegionState.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetSegmentWriteAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) WriteAddress)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(WriteAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
    && (SegmentIdx < VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT) )
  {
    result = E_OK;

    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId) )
    {
      /* In case that the value is already in cache, take it from there. */
      *WriteAddress = vSwUpdM_Appl_Cache_SegmentWriteAddresses[SegmentIdx];
    }
    else
    {
      /* Otherwise read it directly from NV. */
      *WriteAddress = vSwUpdM_Appl_SegmentWriteAddresses[PartitionId][ModuleId][SegmentIdx];
    }
  }

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetSegmentWriteAddress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist segment write addresses in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetSegmentWriteAddress(
  vSwUpdM_OpStatusType OpStatus,
  vSwUpdM_PartitionIdType PartitionId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentIdxType SegmentIdx,
  vSwUpdM_AddressType  WriteAddress,
  boolean SyncFlag)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(PartitionId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SegmentIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(WriteAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  if ( (PartitionId < VSWUPDM_APPL_PARTITION_COUNT)
    && (ModuleId < VSWUPDM_APPL_MODULE_COUNT)
    && (SegmentIdx < VSWUPDM_APPL_SEGMENT_WRITE_ADDRESS_COUNT) )
  {
    vSwUpdM_Appl_SegmentWriteAddresses[PartitionId][ModuleId][SegmentIdx]  = WriteAddress;
    result = E_OK;

    /* Update cache if cache is affected. */
    if ( (vSwUpdM_Appl_Cache_ValidityInfo.moduleId == ModuleId)
      && (vSwUpdM_Appl_Cache_ValidityInfo.partitionId == PartitionId) )
    {
      /* PRQA S 2991, 2995 1 */ /* MD_vSwUpdM_Appl_Rule13.7_2991_2995_ExampleCode */
      if (result == E_OK)
      {
        vSwUpdM_Appl_Cache_SegmentWriteAddresses[SegmentIdx] = WriteAddress;
      }
      else
      {
        /* Invalidate cache in case of error. */
        /* PRQA S 2880 1 */ /* MD_vSwUpdM_Appl_Rule2.1_2880_ExampleCode */
        vSwUpdM_Appl_Cache_ValidityInfo.moduleId    = VSWUPDM_INVALID_ID;
        vSwUpdM_Appl_Cache_ValidityInfo.partitionId = VSWUPDM_INVALID_ID;
      }
    }
  }

  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_GetResumeInfo
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Read resume information from non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_GetResumeInfo(
  vSwUpdM_OpStatusType OpStatus,
  P2VAR(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo)
{
  Std_ReturnType result = E_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ResumeInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  *ResumeInfo = vSwUpdM_Appl_ResumeInfo;

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetResumeInfo
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Persist resume information in non-volatile memory.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetResumeInfo(
  vSwUpdM_OpStatusType OpStatus,
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ResumeInfo,
  boolean SyncFlag)
{
  Std_ReturnType result = E_OK;

  VSWUPDM_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(ResumeInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(SyncFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_Appl_ResumeInfo = *ResumeInfo;

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_ResetDecryptionInitVector
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Reset decryption initialization vector.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetDecryptionInitVector(void)
{
  Std_ReturnType result = E_OK;

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetDecryptionInitVector
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Set decryption initialization vector.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetDecryptionInitVector(
  vSwUpdM_ConstDataPointerType IvData,
  vSwUpdM_LengthType IvSize)
{
  Std_ReturnType result = E_OK;

  VSWUPDM_DUMMY_STATEMENT(IvData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(IvSize); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_ResetEncryptionInitVector
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Reset encryption initialization vector.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_ResetEncryptionInitVector(void)
{
  Std_ReturnType result = E_OK;

  return result;
}

/***********************************************************************************************************************
 *  vSwUpdM_Appl_SetEncryptionInitVector
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 * \attention   Must be adapted by integrator: Set encryption initialization vector.
 * \remark      Please consult header file and TechnicalReference_vSwUpdM for detailed information.
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Appl_SetEncryptionInitVector(
  vSwUpdM_ConstDataPointerType IvData,
  vSwUpdM_LengthType IvSize)
{
  Std_ReturnType result = E_OK;

  VSWUPDM_DUMMY_STATEMENT(IvData); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(IvSize); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return result;
}

#define VSWUPDM_STOP_SEC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:

  MD_vSwUpdM_Appl_Rule9.3_0686_DefaultInitialization:
    Reason:     Initialization to default value is done on purpose.
    Risk:       Unexpected behavior of component because of values returned by user callouts.
    Prevention: Template code must be adapted to actual configuration.

  MD_vSwUpdM_Appl_Rule13.7_2991_2995_ExampleCode:
    Reason:     Example code contains more error handling than detection. However, when the code is adapted by the
                customer, more errors might occur, and the example code shows that this requires to be handled.
    Risk:       Compiler warnings may occur.
    Prevention: Template code needs to be adapted. Errors must be either detected and handled, or unnecessary handling
                must be removed.

  MD_vSwUpdM_Appl_Rule2.1_2880_ExampleCode:
    Reason:     Example code contains more error handling than detection. However, when the code is adapted by the
                customer, more errors might occur, and the example code shows how it could be handled.
    Risk:       Compiler warnings may occur.
    Prevention: Template code needs to be adapted. Errors must be either detected and handled, or unnecessary handling
                must be removed.

*/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Appl.c
 *********************************************************************************************************************/
