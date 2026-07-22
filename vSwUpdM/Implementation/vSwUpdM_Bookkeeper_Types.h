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
/*!        \file  vSwUpdM_Bookkeeper_Types.h
 *        \brief  vSwUpdM_Bookkeeper types header file
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_BOOKKEEPER_TYPES_H)
#define VSWUPDM_BOOKKEEPER_TYPES_H

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "ComStack_Types.h"

/* Other MultipleUnit's Type Headers used by Bookkeeper_Types */
#include "vSwUpdM_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

typedef enum
{
  VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN = 0u,
  VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE,
  VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET,
  VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET,

  VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_COUNT
}vSwUpdM_BkPersist_GenericServiceCommandType;

typedef enum
{
  VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE,
  VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE,
  VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY,
  VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION,
  VSWUPDM_BKPERSIST_PARAM_MODULE_STATE,
  VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY,
  VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION,
  VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS,
  VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT,
  VSWUPDM_BKPERSIST_PARAM_REGION_STATE,
  VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS,
  VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS,
  VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES,
  VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS,
  VSWUPDM_BKPERSIST_PARAM_RESUME_INFO,

  VSWUPDM_BKPERSIST_PARAM_COUNT,
  VSWUPDM_BKPERSIST_PARAM_NONE = 0xFFu
} vSwUpdM_BkPersist_ParamType;

typedef struct
{
  vSwUpdM_PartitionIdType     PartitionId;
  vSwUpdM_ModuleIdType        ModuleId;
  vSwUpdM_RegionIdType        RegionId;
  vSwUpdM_SegmentIdxType      SegmentIdx;
  vSwUpdM_PartitionStateType  PartitionStateChangeMask;
}vSwUpdM_BkPersist_EntityType; /*!< API parameter between local instance and persistor. */

typedef struct
{
  vSwUpdM_PartitionHandleIdType PartitionHandle;
  vSwUpdM_ModuleHandleIdType    ModuleHandle;
  vSwUpdM_RegionHandleIdType    RegionHandle;
  vSwUpdM_SegmentIdxType        SegmentIdx;
  vSwUpdM_PartitionStateType    PartitionStateChangeMask;
}vSwUpdM_BkPersist_EntityHandleType; /*!< API parameter between persistor and grid. */

typedef enum
{
  VSWUPDM_BKPERSIST_REQUESTSTATE_WAIT_RESPONSE,  /*!< Transmission requested, in progress or finished. Response not yet available. */
  VSWUPDM_BKPERSIST_REQUESTSTATE_IDLE,           /*!< Request entry is empty. */
  VSWUPDM_BKPERSIST_REQUESTSTATE_READY,          /*!< Ready for transmission. */
  VSWUPDM_BKPERSIST_REQUESTSTATE_DELAYED,        /*!< State of setter request with SyncFlag set to FALSE. Waiting for transition to IDLE. */
  VSWUPDM_BKPERSIST_REQUESTSTATE_FAILED          /*!< Response indicate an error. Waiting to inform caller about the issue. */
} vSwUpdM_BkPersist_RequestStateType;

typedef struct
{
  vSwUpdM_AddressType         StreamAddress;
  vSwUpdM_AddressType         MemoryAddress;
  vSwUpdM_PartitionStateType  PartitionState;
  vSwUpdM_ServiceIdType       CurrentService;
  vSwUpdM_ResumeStateType     ServiceState;
  vSwUpdM_ValidType           IsAddressValid;
  vSwUpdM_AddressType         TriggerAddress;
} vSwUpdM_BkPersist_ResumeInfoType;

typedef vSwUpdM_SegmentDynamicAttributesType  vSwUpdM_BkPersist_SegmentAttributesType;
typedef uint8                                 vSwUpdM_BkPersist_SizeOfParameterType;

typedef uint32                                vSwUpdM_BkPersist_GenericParameterType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif  /* VSWUPDM_BOOKKEEPER_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Bookkeeper_Types.h
 **********************************************************************************************************************/
