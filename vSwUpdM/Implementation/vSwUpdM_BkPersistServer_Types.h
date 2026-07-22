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
/*!        \file  vSwUpdM_BkPersistServer_Types.h
 *        \brief  vSwUpdM_BkPersistServer types header file
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#if !defined (VSWUPDM_BKPERSISTSERVER_TYPES_H)
#define VSWUPDM_BKPERSISTSERVER_TYPES_H

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "ComStack_Types.h"

/* Types header of containing MultipleUnit */
#include "vSwUpdM_Bookkeeper_Types.h"
#include "vSwUpdM_Grid_Types.h"

/* Other MultipleUnit's Type Headers used by Bookkeeper_Types */

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
  VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE,              /* < Slot is empty. */
  VSWUPDM_BKPERSISTSERVER_SLOTSTATE_ENQUEUED,          /* < Slot is occupied and waiting for processing. */
  VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING,        /* < Slot is processing. */
  VSWUPDM_BKPERSISTSERVER_SLOTSTATE_TRANSMIT_RESPONSE  /* < Processing is done, transmit response. */
} vSwUpdM_BkPersistServer_SlotStateType;

typedef struct vSwUpdM_BkPersistServer_VarSlotType_tag vSwUpdM_BkPersistServer_VarSlotType;
typedef P2VAR(vSwUpdM_BkPersistServer_VarSlotType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_BkPersistServer_VarSlotPtrType;
typedef uint8_least vSwUpdM_BkPersistServer_MasksIterType;

struct vSwUpdM_BkPersistServer_VarSlotType_tag
{
  vSwUpdM_BkPersist_GenericServiceCommandType Command;
  vSwUpdM_BkPersist_ParamType                 ParamType;
  vSwUpdM_BkPersist_EntityType                Entities;
  vSwUpdM_GridSrvc_ServiceIdxType             ServiceIndex;

  /* Depending on the request type only one of these is used: */
  union
  { /* PRQA S 0750 */  /* MD_CSL_Union */
    vSwUpdM_BkPersist_GenericParameterType    GenericValue;
    vSwUpdM_BkPersist_ResumeInfoType          ResumeInfo;
    vSwUpdM_BkPersist_SegmentAttributesType   SegmentInfo;
  }Buffer;

  boolean                                     SyncFlag;
  Std_ReturnType                              Result;

  vSwUpdM_BkPersistServer_SlotStateType       State;
  vSwUpdM_OpStatusType                        OpStatus;
  vSwUpdM_BkPersistServer_MasksIterType       MaskIdx;
  boolean                                     IsOpen;
};
/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif  /* VSWUPDM_BKPERSISTSERVER_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: vSwUpdM_BkPersistServer_Types.h
 **********************************************************************************************************************/
