/***********************************************************************************************************************
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
/*!        \file  vSwUpdM_Types.h
 *        \brief  vSwUpdM types header file
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#ifndef VSWUPDM_TYPES_H
#define VSWUPDM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Compiler.h"
#include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (VSWUPDM_LOCAL) /* COV_MSR_COMPATIBILITY */
# define VSWUPDM_LOCAL            static
#endif

#if !defined (VSWUPDM_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
# define VSWUPDM_LOCAL_INLINE     LOCAL_INLINE
#endif

#define VSWUPDM_UNDEFINED_ADDRESS   0u
#define VSWUPDM_UNDEFINED_LENGTH    0u
#define VSWUPDM_MAX_ADDRESS         0xFFFFFFFFu
#define VSWUPDM_MAX_LENGTH          0xFFFFFFFFu

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 vSwUpdM_ServiceIdType;

typedef uint32  vSwUpdM_AddressType;
typedef uint32  vSwUpdM_LengthType;
typedef boolean vSwUpdM_SwappableType;
typedef boolean vSwUpdM_ValidType;
typedef boolean vSwUpdM_MandatoryType;
typedef uint8   vSwUpdM_StateType;
typedef uint8   vSwUpdM_UpdateStateType;
typedef uint8   vSwUpdM_EventType;
typedef uint8   vSwUpdM_DataType;
typedef uint32  vSwUpdM_AlignedDataType;
typedef P2VAR(vSwUpdM_DataType, AUTOMATIC, VSWUPDM_APPL_VAR)  vSwUpdM_VarDataPointerType;
typedef P2CONST(vSwUpdM_DataType, AUTOMATIC, VSWUPDM_APPL_CONST)  vSwUpdM_ConstDataPointerType;

/* Partition specific types */
typedef uint32  vSwUpdM_PartitionIdType;
typedef uint32  vSwUpdM_PartitionIdxType;
typedef uint32  vSwUpdM_PartitionHandleIdType;
typedef uint8   vSwUpdM_PartitionStateType;
typedef uint8   vSwUpdM_PartitionAddrAreaIdType;
typedef uint32  vSwUpdM_PartitionRevisionType;
typedef uint32  vSwUpdM_PartitionGroupIdType;

/* Module specific types */
typedef uint32  vSwUpdM_ModuleIdType;
typedef uint32  vSwUpdM_ModuleIdxType;
typedef uint32  vSwUpdM_ModuleHandleIdType;
typedef uint8   vSwUpdM_ModuleTypeType;
typedef uint8   vSwUpdM_ModuleStateType;
typedef uint32  vSwUpdM_ModuleRevisionType;
typedef uint32  vSwUpdM_ProgrammingAttemptsType;

/* Region specific types */
typedef uint32  vSwUpdM_RegionIdType;
typedef uint32  vSwUpdM_RegionIdxType;
typedef uint32  vSwUpdM_RegionHandleIdType;
typedef uint8   vSwUpdM_RegionStateType;

/* Segment specific types */
typedef uint32  vSwUpdM_SegmentIdValueType;
typedef struct
{
  vSwUpdM_SegmentIdValueType  StaticSegmentId;
  vSwUpdM_SegmentIdValueType  DynamicSegmentId;
} vSwUpdM_SegmentIdType;
typedef uint32  vSwUpdM_SegmentIdxType;
typedef uint32  vSwUpdM_SegmentHandleIdType;
typedef uint8   vSwUpdM_SegmentTypeType;
typedef uint8   vSwUpdM_SegmentStateType;
typedef boolean vSwUpdM_OverflowType;

typedef uint8   vSwUpdM_StreamStateType;

typedef uint8 vSwUpdM_LengthHandlingType;

/* Stream specific types */
typedef P2VAR(uint8, AUTOMATIC, VSWUPDM_VAR_NOINIT) vSwUpdM_StreamDataPtrType;
typedef uint32 vSwUpdM_StreamLengthType;

/* Data processing / stream specific types */
typedef uint8   vSwUpdM_ProcessingOperationType;
typedef uint8   vSwUpdM_ProcessIdType;
typedef uint8   vSwUpdM_ProcessHandleType;

/* Partition Types */
typedef struct vSwUpdM_PartitionInfoStruct
{
  vSwUpdM_PartitionIdType           Id;
  vSwUpdM_PartitionHandleIdType     HandleId;
  vSwUpdM_SwappableType             IsSwappable;
  vSwUpdM_PartitionStateType        State;
  vSwUpdM_ValidType                 IsValid;
  vSwUpdM_PartitionRevisionType     Revision;
  vSwUpdM_PartitionAddrAreaIdType   AddrAreaId;
} vSwUpdM_PartitionInfoType;

/* Module Types */
typedef struct vSwUpdM_ModuleInfoStruct
{
  vSwUpdM_ModuleIdType              Id;
  vSwUpdM_ModuleHandleIdType        HandleId;
  vSwUpdM_ModuleTypeType            Type;
  vSwUpdM_SwappableType             IsSwappable;
  vSwUpdM_MandatoryType             IsMandatory;
  vSwUpdM_ModuleStateType           State;
  vSwUpdM_ValidType                 IsValid;
  vSwUpdM_ModuleRevisionType        Revision;
  vSwUpdM_AddressType               MetaDataAddress;
  vSwUpdM_ProgrammingAttemptsType   ProgrammingAttempts;
  vSwUpdM_ProgrammingAttemptsType   MaxProgrammingAttempts;
} vSwUpdM_ModuleInfoType;

/* Region Types */
typedef struct vSwUpdM_RegionInfoStruct
{
  vSwUpdM_RegionHandleIdType        HandleId;
  vSwUpdM_AddressType               StartAddress;
  vSwUpdM_AddressType               EndAddress;
  vSwUpdM_AddressType               MaxAddress;
  vSwUpdM_LengthType                Length;
  vSwUpdM_LengthType                MaxLength;
  vSwUpdM_ModuleIdType              ModuleId;
  vSwUpdM_RegionStateType           State;
} vSwUpdM_RegionInfoType;

/* Segment Types */
typedef struct vSwUpdM_SegmentInfoStruct
{
  vSwUpdM_SegmentIdType             Id;
  vSwUpdM_SegmentTypeType           Type;
  vSwUpdM_AddressType               StartAddress;
  vSwUpdM_AddressType               EndAddress;
  vSwUpdM_AddressType               WriteAddress;
  vSwUpdM_LengthType                Length;
  vSwUpdM_LengthHandlingType        LengthHandling;
  vSwUpdM_SegmentStateType          State;
  vSwUpdM_OverflowType              IsOverflowable;
  vSwUpdM_RegionIdType              RegionId;
} vSwUpdM_SegmentInfoType;

typedef struct vSwUpdM_RemoteSegmentInfoStruct
{
  vSwUpdM_AddressType               StartAddress;
  vSwUpdM_LengthType                InitialLength;
  vSwUpdM_LengthHandlingType        LengthHandling;
  vSwUpdM_SegmentStateType          State;
  vSwUpdM_SegmentTypeType           Type;
  vSwUpdM_OverflowType              IsOverflowable;
} vSwUpdM_RemoteSegmentInfoType;

/* Stream Types */
typedef struct vSwUpdM_StreamInfoStruct
{
  vSwUpdM_StreamLengthType          InputLength;
  vSwUpdM_ProcessingOperationType   Operation;
} vSwUpdM_StreamInfoType;

typedef struct vSwUpdM_StreamDataInfoStruct
{
  vSwUpdM_StreamDataPtrType         DataPtr;
  vSwUpdM_StreamLengthType          Length;
  vSwUpdM_StreamLengthType          Offset;
} vSwUpdM_StreamDataInfoType;

typedef struct vSwUpdM_ProcessingInfoStruct
{
  vSwUpdM_ProcessingOperationType   Operation;
} vSwUpdM_ProcessingInfoType;

typedef struct
{
  vSwUpdM_PartitionIdType    PartitionId;
  vSwUpdM_PartitionStateType PartitionState;
  vSwUpdM_PartitionIdxType   PartitionIdx; /**< Relative partition index inside partition group */
  vSwUpdM_ModuleIdType       ModuleId;
  vSwUpdM_RegionIdType       RegionId;
  vSwUpdM_RegionIdxType      RegionIdx;    /**< Relative region index inside module */
  vSwUpdM_SegmentIdType      SegmentId;
  vSwUpdM_SegmentIdxType     SegmentIdx;   /**< Relative segment index inside module */
} vSwUpdM_EntityIdsType;

typedef P2VAR(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_VAR)     vSwUpdM_EntityIdsPtrType;

typedef struct
{
  vSwUpdM_AddressType Address;
  vSwUpdM_LengthType  Length;
} vSwUpdM_RangeInfoType;

/* Process types */
typedef uint8  vSwUpdM_ProcessCountType;

typedef struct vSwUpdM_VarDataInfoStruct
{
  vSwUpdM_VarDataPointerType    DataPtr;
  vSwUpdM_LengthType            AvailableLength;    /**< Size of data in buffer. */
  vSwUpdM_LengthType            BufferSize;         /**< Size of buffer. */
}vSwUpdM_VarDataInfoType;

typedef struct vSwUpdM_ConstDataInfoStruct
{
  vSwUpdM_ConstDataPointerType  DataPtr;
  vSwUpdM_LengthType            Length;
}vSwUpdM_ConstDataInfoType;

typedef struct vSwUpdM_ProcessInfoStruct
{
  vSwUpdM_ProcessCountType                                             InputCount;
  vSwUpdM_ProcessCountType                                             OutputCount;
  vSwUpdM_ProcessingOperationType                                      Operation;
  P2CONST(vSwUpdM_ConstDataInfoType, AUTOMATIC, VSWUPDM_APPL_CONST)    InputData;
  P2VAR(vSwUpdM_VarDataInfoType, AUTOMATIC, VSWUPDM_APPL_VAR)          OutputData;
}vSwUpdM_ProcessInfoType;

typedef struct vSwUpdM_RemoteStreamInfoStruct
{
  vSwUpdM_ProcessCountType                                             InputCount;
  vSwUpdM_ProcessCountType                                             OutputCount;
  vSwUpdM_ProcessingOperationType                                      Operation;
  vSwUpdM_ProcessHandleType                                            Handle;
} vSwUpdM_RemoteProcessInfoType;

typedef enum
{
  vSwUpdM_ProcessScope_Segment,
  vSwUpdM_ProcessScope_Module,
  vSwUpdM_ProcessScope_Partition
}vSwUpdM_ProcessScopeType;

typedef enum
{
  vSwUpdM_ProcessSubScope_None,
  vSwUpdM_ProcessSubScope_SegmentListWritten
}vSwUpdM_ProcessSubScopeType;

typedef struct vSwUpdM_ProcessInternalInfoStruct
{
  uint8                                                                PipeId;
  vSwUpdM_ProcessingOperationType                                      Operation;
  vSwUpdM_ProcessScopeType                                             Scope;
  vSwUpdM_ProcessInfoType                                              ProcessInfo;
}vSwUpdM_ProcessInternalInfoType;

typedef enum
{
  VSWUPDM_ADDRESS_ALIGNMENT_FRONT,
  VSWUPDM_ADDRESS_ALIGNMENT_BACK
} vSwUpdM_AddressAlignmentType;

typedef enum
{
  VSWUPDM_ALIGN_GRANULARITY_NONE,
  VSWUPDM_ALIGN_GRANULARITY_PAGE,
  VSWUPDM_ALIGN_GRANULARITY_SECTOR
} vSwUpdM_AlignGranularityType;

/*! Value based type definition for vSwUpdM_HandleIDOfVarModules */
typedef uint16 vSwUpdM_HandleIDOfVarModulesType;

/*! Value based type definition for vSwUpdM_MandatoryOfVarModules */
typedef boolean vSwUpdM_MandatoryOfVarModulesType;

/*! Value based type definition for vSwUpdM_MetaDataAddressOfVarModules */
typedef uint32 vSwUpdM_MetaDataAddressOfVarModulesType;

/*! Value based type definition for vSwUpdM_StateOfVarModules */
typedef uint8 vSwUpdM_StateOfVarModulesType;

/*! Value based type definition for vSwUpdM_SwappableOfVarModules */
typedef boolean vSwUpdM_SwappableOfVarModulesType;

/*! Value based type definition for vSwUpdM_TypeOfVarModules */
typedef uint8 vSwUpdM_TypeOfVarModulesType;

/*! Value based type definition for vSwUpdM_ValidOfVarModules */
typedef boolean vSwUpdM_ValidOfVarModulesType;

typedef uint32 vSwUpdM_RevisionOfVarModulesType;

/*! Value based type definition for vSwUpdM_HandleIDOfVarPartitions */
typedef uint16 vSwUpdM_HandleIDOfVarPartitionsType;

/*! Value based type definition for vSwUpdM_StateOfVarPartitions */
typedef uint8 vSwUpdM_StateOfVarPartitionsType;

/*! Value based type definition for vSwUpdM_SwappableOfVarPartitions */
typedef boolean vSwUpdM_SwappableOfVarPartitionsType;

/*! Value based type definition for vSwUpdM_ValidOfVarPartitions */
typedef boolean vSwUpdM_ValidOfVarPartitionsType;

/*! Value based type definition for vSwUpdM_AddrAreaIdOfVarPartitions */
typedef uint8 vSwUpdM_AddrAreaIdOfVarPartitionsType;

typedef uint32 vSwUpdM_RevisionOfVarPartitionsType;

typedef uint32 vSwUpdM_PartitionGroupIdOfVarPartitionsType;

/*! Value based type definition for vSwUpdM_EndAddressOfVarRegions */
typedef uint32 vSwUpdM_EndAddressOfVarRegionsType;

/*! Value based type definition for vSwUpdM_HandleIDOfVarRegions */
typedef uint16 vSwUpdM_HandleIDOfVarRegionsType;

/*! Value based type definition for vSwUpdM_LengthOfVarRegions */
typedef uint32 vSwUpdM_LengthOfVarRegionsType;

/*! Value based type definition for vSwUpdM_ReservedStartAddressOfVarRegion */
typedef uint32 vSwUpdM_ReservedStartAddressOfVarRegionsType;

/*! Value based type definition for vSwUpdM_ReservedEndAddressOfVarRegions */
typedef uint32 vSwUpdM_ReservedEndAddressOfVarRegionsType;

/*! Value based type definition for vSwUpdM_ModuleIDOfVarRegions */
typedef uint16 vSwUpdM_ModuleIDOfVarRegionsType;

/*! Value based type definition for vSwUpdM_StartAddressOfVarRegions */
typedef uint32 vSwUpdM_StartAddressOfVarRegionsType;

/*! Value based type definition for vSwUpdM_ValidOfVarRegions */
typedef uint8 vSwUpdM_StateOfVarRegionsType;

/*! Value based type definition for vSwUpdM_HandleIDOfVarSegments */
typedef uint32 vSwUpdM_HandleIDOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_IsOverflowableOfVarSegments */
typedef boolean vSwUpdM_IsOverflowableOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_LengthOfVarSegments */
typedef uint32 vSwUpdM_LengthOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_StartAddressOfVarSegments */
typedef uint32 vSwUpdM_StartAddressOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_EndAddressOfVarSegments */
typedef uint32 vSwUpdM_EndAddressOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_MaxAddressOfVarSegments */
typedef uint32 vSwUpdM_MaxAddressOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_MaxLengthOfVarSegments */
typedef uint32 vSwUpdM_MaxLengthOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_StateOfVarSegments */
typedef uint8 vSwUpdM_StateOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_ValidOfVarSegments */
typedef boolean vSwUpdM_ValidOfVarSegmentsType;

/*! Value based type definition for vSwUpdM_TypeOfVarSegments */
typedef uint8 vSwUpdM_TypeOfVarSegmentsType;

typedef enum
{
  VSWUPDM_CLASS_OF_VAR_SEGMENTS_GAP,
  VSWUPDM_CLASS_OF_VAR_SEGMENTS_FREE,
  VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED,
  VSWUPDM_CLASS_OF_VAR_SEGMENTS_RESERVED
} vSwUpdM_ClassOfVarSegmentsType;

typedef vSwUpdM_LengthHandlingType vSwUpdM_LengthHandlingOfVarSegmentsType;

typedef uint8 vSwUpdM_RevisionUpdateType;

typedef struct
{
  vSwUpdM_ModuleStateType           State;      /**< The state of this module. */
  vSwUpdM_ValidType                 IsValid;    /**< Is this entry valid. */
  vSwUpdM_ModuleRevisionType        Revision;
  vSwUpdM_ProgrammingAttemptsType   ProgrammingAttempts;
} vSwUpdM_ModuleDynamicAttributesType;

typedef struct
{
  vSwUpdM_ModuleDynamicAttributesType   Attributes;
  vSwUpdM_RevisionUpdateType            RevisionUpdate;
  boolean                               AttributesDirty;
} vSwUpdM_ModulePendingAttributesType;

/*! Type used in vSwUpdM_VarModules. */
typedef struct svSwUpdM_VarModulesType
{
  vSwUpdM_MetaDataAddressOfVarModulesType MetaDataAddressOfVarModules;  /**< The Meta Data Address of the module. */
  vSwUpdM_HandleIDOfVarModulesType        HandleIDOfVarModules;         /**< Handle ID of the module. */
  vSwUpdM_MandatoryOfVarModulesType       MandatoryOfVarModules;        /**< Is this module mandatory. */
  vSwUpdM_SwappableOfVarModulesType       SwappableOfVarModules;        /**< Is this module swappable. */
  vSwUpdM_TypeOfVarModulesType            TypeOfVarModules;             /**< The type of the module. */
  /* Can currently be either '1' (non-swappable), '2' (swappable) or '3' (swappable with backup). */
  vSwUpdM_PartitionIdType                 PartitionCountOfVarModules;
  vSwUpdM_PartitionIdType                 PartitionIdsOfVarModules[3];
  vSwUpdM_ModuleDynamicAttributesType     DynamicAttributesOfVarModules[3];
  vSwUpdM_PartitionGroupIdType            PartitionGroupIdOfVarModules;
} vSwUpdM_VarModulesType;

typedef struct
{
  vSwUpdM_PartitionStateType        State;
  vSwUpdM_ValidType                 IsValid;
  vSwUpdM_PartitionRevisionType     Revision;
} vSwUpdM_PartitionDynamicAttributesType;

/*! Type used in vSwUpdM_VarPartitions. */
typedef struct svSwUpdM_VarPartitionsType
{
  vSwUpdM_HandleIDOfVarPartitionsType           HandleIDOfVarPartitions;  /**< Handle ID of the partition. */
  vSwUpdM_SwappableOfVarPartitionsType          SwappableOfVarPartitions;  /**< Is this partition swappable. */
  vSwUpdM_AddrAreaIdOfVarPartitionsType         AddrAreaIdOfPartitions;
  vSwUpdM_PartitionDynamicAttributesType        DynamicAttributesOfVarPartitions;
  vSwUpdM_PartitionDynamicAttributesType        PendingAttributesOfVarPartitions;
  vSwUpdM_PartitionStateType                    AffectedState;
  boolean                                       AttributesDirty;
} vSwUpdM_VarPartitionsType;

typedef struct
{
  vSwUpdM_RegionStateType           State;
  vSwUpdM_ProgrammingAttemptsType   ProgrammingAttempts;
} vSwUpdM_RegionDynamicAttributesType;

/*! Type used in vSwUpdM_VarRegions. */
typedef struct svSwUpdM_VarRegionsType
{
  vSwUpdM_RegionIdType                          RegionIDOfVarRegions;
  vSwUpdM_EndAddressOfVarRegionsType            EndAddressOfVarRegions;  /**< The end address of the region. */
  vSwUpdM_LengthOfVarRegionsType                LengthOfVarRegions;  /**< The length address of the region. */
  vSwUpdM_ReservedStartAddressOfVarRegionsType  ReservedStartAddressOfVarRegions;
  vSwUpdM_ReservedEndAddressOfVarRegionsType    ReservedEndAddressOfVarRegions;
  vSwUpdM_StartAddressOfVarRegionsType          StartAddressOfVarRegions;  /**< The start address of the region. */
  vSwUpdM_HandleIDOfVarRegionsType              HandleIDOfVarRegions;  /**< Handle ID of the region. */
  vSwUpdM_ModuleIDOfVarRegionsType              ModuleIDOfVarRegions;  /**< The module ID of the region. */
  vSwUpdM_RegionDynamicAttributesType           DynamicAttributesOfVarRegion;
  vSwUpdM_RegionDynamicAttributesType           PendingAttributesOfVarRegion;
  vSwUpdM_AddressType                           EraseAddressOfVarRegion;
  boolean                                       EraseAddressDirty;
  boolean                                       AttributesDirty;
} vSwUpdM_VarRegionsType;

typedef struct
{
  vSwUpdM_AddressType         StartAddress;
  vSwUpdM_LengthType          InitialLength;
  vSwUpdM_LengthHandlingType  LengthHandling;
  vSwUpdM_SegmentStateType    State;
  vSwUpdM_LengthType          ResumeOffset;
} vSwUpdM_SegmentDynamicAttributesType;

/*! Type used in vSwUpdM_VarSegments. */
typedef struct svSwUpdM_VarSegmentsType
{
  vSwUpdM_EndAddressOfVarSegmentsType       EndAddressOfVarSegments;  /**< The end address of the segment. */
  vSwUpdM_EndAddressOfVarSegmentsType       InitialEndAddressOfVarSegments;  /**< The initial end address of the segment. */
  vSwUpdM_AddressType                       WriteAddressOfVarSegments;
  vSwUpdM_StartAddressOfVarSegmentsType     ReservedStartAddressOfVarSegments;  /**< The start address of the segment. */
  vSwUpdM_EndAddressOfVarSegmentsType       ReservedEndAddressOfVarSegments;  /**< The end address of the segment. */
  vSwUpdM_HandleIDOfVarSegmentsType         HandleIDOfVarSegments;  /**< Handle ID of the segment. */
  vSwUpdM_RegionIdxType                     RegionIdxOfVarSegments;  /**< Region index of the segment. */
  vSwUpdM_IsOverflowableOfVarSegmentsType   IsOverflowableOfVarSegments;  /**< Is this module overflow-able. */
  vSwUpdM_TypeOfVarSegmentsType             TypeOfVarSegments;  /**< The type of the segment. */
  vSwUpdM_ClassOfVarSegmentsType            ClassOfVarSegments; /**< The class of the segment. */
  vSwUpdM_ValidOfVarSegmentsType            ValidOfVarSegments;  /**< Is this entry valid. */
  vSwUpdM_SegmentDynamicAttributesType      DynamicAttributesOfVarSegment;
  vSwUpdM_LengthType                        RealLength;
  vSwUpdM_SegmentIdxType                    WriteSegmentIdx;
  vSwUpdM_SegmentIdxType                    ExternalSegmentIdx;
  boolean                                   AttributesDirty;
  boolean                                   WriteAddressDirty;
  boolean                                   RemoteDirty;
  boolean                                   SegmentClean;
} vSwUpdM_VarSegmentsType;

typedef enum
{
  VSWUPDM_OP_STATUS_INITIAL,
  VSWUPDM_OP_STATUS_PENDING,
  VSWUPDM_OP_STATUS_FINAL,
  VSWUPDM_OP_STATUS_CANCEL
} vSwUpdM_OpStatusType;

typedef enum
{
  VSWUPDM_HOOK_ACTION_DEFAULT,
  VSWUPDM_HOOK_ACTION_CONTINUE,
  VSWUPDM_HOOK_ACTION_ABORT,
  VSWUPDM_HOOK_ACTION_SKIP,
  VSWUPDM_HOOK_ACTION_RETRY,
  VSWUPDM_HOOK_ACTION_RESTART
} vSwUpdM_HookActionType;

typedef enum
{
  VSWUPDM_RETRY_GRANULARITY_DEFAULT,
  VSWUPDM_RETRY_GRANULARITY_OPERATION,
  VSWUPDM_RETRY_GRANULARITY_PAGE,
  VSWUPDM_RETRY_GRANULARITY_SECTOR,
  VSWUPDM_RETRY_GRANULARITY_REGION,
  VSWUPDM_RETRY_GRANULARITY_MODULE
} vSwUpdM_RetryGranularity;

typedef uint32  vSwUpdM_RetryCountType;

typedef enum
{
  VSWUPDM_HOOK_TYPE_NONE,
  VSWUPDM_HOOK_TYPE_PRE,
  VSWUPDM_HOOK_TYPE_POST
} vSwUpdM_HookTypeType;

typedef struct
{
  vSwUpdM_ServiceIdType     ServiceId;
  vSwUpdM_HookTypeType      HookType;
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds;
  vSwUpdM_AddressType       TargetAddress;
  vSwUpdM_LengthType        ProcessingLength;
  vSwUpdM_RetryCountType    RetryCount;
} vSwUpdM_HookInfoType;

typedef struct
{
  Std_ReturnType            Result;
  vSwUpdM_HookActionType    HookAction;
  vSwUpdM_RetryGranularity  RetryGranularity;
} vSwUpdM_HookResultType;

typedef uint8 vSwUpdM_ResumeStateType;

typedef struct
{
  vSwUpdM_AddressType         StreamAddress;
  vSwUpdM_AddressType         MemoryAddress;
  vSwUpdM_PartitionStateType  PartitionState;
  vSwUpdM_ServiceIdType       CurrentService;
  vSwUpdM_ResumeStateType     ServiceState;
  vSwUpdM_ValidType           IsAddressValid;
} vSwUpdM_ResumeInfoType;

typedef struct
{
  vSwUpdM_ResumeInfoType      ResumeInfo;
  vSwUpdM_AddressType         TriggerAddress;
} vSwUpdM_ExtendedResumeInfoType;

/**************************************************************
 *  Queue handling
 **************************************************************/

/*! Handle for queue entry. */
typedef uint32      vSwUpdM_QueueHandleType;
typedef uint32      vSwUpdM_QueuePrioType;
typedef uint32      vSwUpdM_EntityHandleType;

typedef enum
{
  VSWUPDM_QUEUE_ENTRY_STATE_FREE,
  VSWUPDM_QUEUE_ENTRY_STATE_USED
} vSwUpdM_QueueEntryStateType;

/*! Queue entry. */
typedef struct
{
  vSwUpdM_QueuePrioType         prio;    /**< Entry priority */
  vSwUpdM_QueueEntryStateType   state;
  vSwUpdM_QueueHandleType       prev;    /**< Handle of previous queue entry */
  vSwUpdM_QueueHandleType       next;    /**< Handle of next queue entry */
  vSwUpdM_EntityHandleType      entity;  /**< Associated entity handle / index */
} vSwUpdM_QueueEntryType;

#endif /* VSWUPDM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Types.h
 *********************************************************************************************************************/
