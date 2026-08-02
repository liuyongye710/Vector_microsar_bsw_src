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
/*!        \file  vSwUpdM_BkPersistServer.c
 *        \brief  vSwUpdM Bookkeeper Persistor server source file
 *      \details  Implementation of the vSwUpdM_BkPersistServer subcomponent.
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

#define VSWUPDM_BKPERSISTSERVER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vSwUpdM_Bookkeeper_Types.h"
#include "vSwUpdM_BkPersistServer_Impl.h"
#include "vSwUpdM_Appl.h"
#include "vSwUpdM_Grid_Impl.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Used to store current source node to provide this on demand to customer (via getter API). */
VSWUPDM_LOCAL VAR(vSwUpdM_NodeIterType, VSWUPDM_VAR_NOINIT)             vSwUpdM_BkCurrentPersistorNode;

/*! Actively scheduled slot. */
VSWUPDM_LOCAL VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_ActiveSlot;
/*! Index for Round-Robin scheme. */
VSWUPDM_LOCAL VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_ResponseSlot;

/*! Init Flag */
VSWUPDM_LOCAL VAR(boolean, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_InitFlag;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(boolean, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_EventPending;
VAR(boolean, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistServer_IsActive;

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_CheckEntities
 *********************************************************************************************************************/
/*! \brief       Check if provided entities are valid.
 *  \details     -
 *  \param[in]   ParamType    Type of parameter.
 *  \param[in]   Entities     Entities to be checked.
 *  \return      E_OK         if entities are valid.
 *  \return      E_NOT_OK     else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_CheckEntities(
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_CheckPrecondition
 *********************************************************************************************************************/
/*! \brief       Check for eventual preconditions.
 *  \details     -
 *  \param[in]   Slot         RX slot, which shall be checked.
 *  \return      E_OK         if preconditions are met.
 *  \return      E_NOT_OK     else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_CheckPrecondition(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecCallout
 *********************************************************************************************************************/
/*! \brief       Call appropriate callout, as indicated by the request, processed in slot.
 *  \details     -
 *  \param[in]   SlotIndex RX slot, which shall be processed.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecCallout(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_EvalCalloutResult
 *********************************************************************************************************************/
/*! \brief       Evaluate callout return value into PersistServer Slot state.
 *  \details     -
 *  \param[in]   SlotIndex Index of Rx slot which shall be processed.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_EvalCalloutResult(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_PostHandler
 *********************************************************************************************************************/
/*! \brief       Set states etc. as a consequence of a successful request.
 *  \details     Set Slot->IsOpen after successful Open() request, reset it on Close().
 *  \param[in]   Slot   RX slot, which shall be processed.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_PostHandler(vSwUpdM_BkPersistServer_VarSlotPtrType Slot);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_TransmitGetResponse
 *********************************************************************************************************************/
/*! \brief       Transmit response for Get request.
 *  \details     -
 *  \param[in]   SlotIndex              RX slot, which shall be processed.
 *  \param[in]   ServiceExecutionState  State of service execution.
 *  \return      E_OK on success.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_TransmitGetResponse(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_TransmitResponse
 *********************************************************************************************************************/
/*! \brief       Transmit response for request.
 *  \details     -
 *  \param[in]   SlotIndex              RX slot, which shall be processed.
 *  \param[in]   ServiceExecutionState  State of service execution.
 *  \return      E_OK on success.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_TransmitResponse(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecGetCallout
 *********************************************************************************************************************/
/*! \brief          Call getter callout and collect result based on ParamType.
 *  \details        -
 *  \param[in,out]  Slot            Reference to request including all required parameters (also return values).
 *  \return         E_OK            Getter callout returned E_OK.
 *  \return         E_NOT_OK        Illegal Slot->ParamType or Getter callout returned E_NOT_OK
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecGetCallout(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecSetCallout
 *********************************************************************************************************************/
/*! \brief          Call setter callout and collect result based on ParamType.
 *  \details        -
 *  \param[in,out]  Slot            Reference to request including all required parameters (also return values).
 *  \return         E_OK            Setter callout returned E_OK.
 *  \return         E_NOT_OK        Illegal Slot->ParamType or Setter callout returned E_NOT_OK
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecSetCallout(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetSlot
 *********************************************************************************************************************/
/*! \brief          Helper function, set slot values.
 *  \details        -
 *  \param[in]      Slot                Pointer to slot structure.
 *  \param[in]      ServiceIndex        Bookkeeper service request (type of service, i.e. GetResumeInfo)
 *  \param[in]      Command             Type of command (getter/setter)
 *  \param[in]      Entities            Parameter of request
 *  \param[in]      ParamType           Type of request
 *  \param[in]      GenericValue        Additional non common parameter (i.e. set prog attempts -> ProgAttempts)
 *  \param[in]      SegmentAttributes   Parameter of request.
 *  \param[in]      ResumeInfo          Parameter of request.
 *  \param[in]      SyncFlag            Flag indicates whether a NvM synchronization is required or not.
 *  \return         E_OK on success.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetSlot(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo,
  boolean SyncFlag);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_EnqueueRequest
 *********************************************************************************************************************/
/*! \brief          General reception function, which enqueue the current request into its slot.
 *  \details        -
 *  \param[in]      SourceIndex         Source node, node which sends the request.
 *  \param[in]      ServiceIndex        Bookkeeper service request (type of service, i.e. GetResumeInfo).
 *  \param[in]      Command             Type of command (getter/setter).
 *  \param[in]      Entities            Parameter of request.
 *  \param[in]      ParamType           Type of request.
 *  \param[in]      GenericValue        Additional non common parameter (i.e. set programming attempts -> ProgAttempts).
 *  \param[in]      SegmentAttributes   Parameter of request.
 *  \param[in]      ResumeInfo          Parameter of request.
 *  \param[in]      SyncFlag            Flag indicates whether a NvM synchronization is required or not.
 *  \return         E_OK on success.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *  \ingroup        BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_EnqueueRequest(
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo,
  boolean SyncFlag);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetSlotByNode
 *********************************************************************************************************************/
/*! \brief       Get PersistServer Slot associated with given node.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[out]  SlotIndex    Slot, associated with SourceIndex.
 *  \return      E_OK         If a slot is found for SourceIndex.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetSlotByNode(
  vSwUpdM_NodeIterType SourceIndex,
  P2VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SlotIndex);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_IsRequestAccepted
 *********************************************************************************************************************/
/*! \brief       Check source of request and therefore if the request can be accepted or not.
 *  \details     -
 *  \param[in]   SourceIndex    Node index of received request.
 *  \param[in]   Command        Necessary for command based requests (OPEN | CLOSE).
 *  \param[in]   ParamType      Parameter type of request.
 *  \param[in]   Entities       Parameter of request.
 *  \return      E_OK if request is accepted.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_IsRequestAccepted(
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_NextSlot
 *********************************************************************************************************************/
/*! \brief       Set SlotIndex to next active slot.
 *  \details     Iterates over configured slots, starting from SlotIndex until a non-IDLE slot is found.
 *  \param[in,out] SlotIndex to adjust.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_NextSlot(P2VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SlotIndex);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ProcessEvents
 *********************************************************************************************************************/
/*! \brief       Handle  (asynchronous) request events.
 *  \details     Sets PersistServer to active state if requests are pending, 
 *               Switches processing to next slot if slot gets IDLE
 *               Disables processing if no active slot is left.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ProcessEvents(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_HandleActiveSlot
 *********************************************************************************************************************/
/*! \brief       Process active slot.
 *  \details     Call callout function repeatedly (if required), trigger transmission of responses.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_HandleActiveSlot(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetSlotPtr
 *********************************************************************************************************************/
/*! \brief       Get pointer to slot structure.
 *  \details     -
 *  \param[in]   SlotIndex Index of slot.
 *  \return      Pointer to slot structure.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistServer_VarSlotPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetCurrentClientNode
 *********************************************************************************************************************/
/*! \brief       Set current persist client node.
 *  \details     -
 *  \param[in]   Node to be set.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_NodeIterType Node);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_CheckEntities
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
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_CheckEntities(    /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities)
{
  Std_ReturnType retVal = E_OK;

  /* #100 Evaluate ParamType: */
  switch (ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
    /* #110 Segment data:
     *      Expect valid Ids for Segment, Module and Partition. */
    {
      if ( (Entities->SegmentIdx == VSWUPDM_INVALID_ID)
        || (Entities->ModuleId == VSWUPDM_INVALID_ID)
        || (Entities->PartitionId == VSWUPDM_INVALID_ID))
      {
        retVal = E_NOT_OK;
      }
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
    case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
    /* #120 Region data:
     *      Expect valid Ids for Region, Module and Partition. */
    {
      if ( (Entities->RegionId == VSWUPDM_INVALID_ID)
        || (Entities->ModuleId == VSWUPDM_INVALID_ID)
        || (Entities->PartitionId == VSWUPDM_INVALID_ID)
        )
      {
        retVal = E_NOT_OK;
      }
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
    case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
    /* #130 Module data:
     *      Expect valid Ids for Module and Partition. */
    {
      if ( (Entities->ModuleId == VSWUPDM_INVALID_ID)
        || (Entities->PartitionId == VSWUPDM_INVALID_ID)
        )
      {
        retVal = E_NOT_OK;
      }
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE:
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY:
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION:
    /* #140 Partition data:
     *      Expect valid Ids for Partition. */
    {
      if (Entities->PartitionId == VSWUPDM_INVALID_ID)
      {
        retVal = E_NOT_OK;
      }
      break;
    }
    default:
    /* case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE: */
    /* case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO: */
    {
      /* Nothing to check. */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_BkPersistServer_CheckEntities */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_CheckPrecondition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_CheckPrecondition(     /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot)    /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Slot->Command)
  {
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN:
    {
      /* No preconditions - re-opening is allowed. */
      break;
    }
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE:
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET:
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET:
    {
      if (Slot->IsOpen == TRUE)
      {
        retVal = E_OK;
      }
      else
      {
        retVal = E_NOT_OK;
      }
      break;
    }
    default:
    {
      /* Reject invalid Command. */
/*!
 * Internal comment removed.
 *
 *
 */
      retVal = E_NOT_OK;
      break;
    }
  }

  return retVal;
} /* vSwUpdM_BkPersistServer_CheckPrecondition */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_EvalCalloutResult
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_EvalCalloutResult(       /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex)
{
  vSwUpdM_BkPersistServer_VarSlotPtrType slot =  vSwUpdM_BkPersistServer_GetSlotPtr(SlotIndex);

  switch (slot->Result)
  {
    default:
    /* On E_OK or any error:
     * Transmit Response */
    {
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_TRANSMIT_RESPONSE;
      break;
    }
    case VSWUPDM_E_PENDING:
    {
      slot->OpStatus = VSWUPDM_OP_STATUS_PENDING;
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING;
      break;
    }
    case VSWUPDM_E_BUSY:
    {
      slot->OpStatus = VSWUPDM_OP_STATUS_INITIAL;
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING;
      break;
    }
  }
} /* vSwUpdM_BkPersistServer_EvalCalloutResult */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_PostHandler
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_PostHandler(vSwUpdM_BkPersistServer_VarSlotPtrType Slot)        /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  if (Slot->Result == E_OK)
  {
    switch (Slot->Command)
    {
      case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN:
      {
        Slot->IsOpen = TRUE;
        break;
      }
      case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE:
      {
        Slot->IsOpen = FALSE;
        break;
      }
      default:
      {
        /* Nothing to do. */
        break;
      }
    }
  }
} /* vSwUpdM_BkPersistServer_PostHandler */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_TransmitGetResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_TransmitGetResponse(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState)      /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
{
  Std_ReturnType retVal;
  vSwUpdM_BkPersistServer_VarSlotPtrType slot = vSwUpdM_BkPersistServer_GetSlotPtr(SlotIndex); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  switch (slot->ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    {
      vSwUpdM_GridRpc_ComplexResponseClassBkGetSegmentAttributesType response;
      vSwUpdM_GridRpc_InitComplexResponseClassBkGetSegmentAttributesType(slot->ServiceIndex, slot->Result, &slot->Buffer.SegmentInfo, &response);
      retVal =  vSwUpdM_GridRpc_TransmitResponse(vSwUpdM_GetNodeIdxOfPersistServer_Slots(SlotIndex), ServiceExecutionState, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &response);              /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
    {
      vSwUpdM_GridRpc_ComplexResponseClassBkGetResumeInfoType response;
      vSwUpdM_GridRpc_InitComplexResponseClassBkGetResumeInfoType(slot->ServiceIndex, slot->Result, &slot->Buffer.ResumeInfo, &response);
      retVal =  vSwUpdM_GridRpc_TransmitResponse(vSwUpdM_GetNodeIdxOfPersistServer_Slots(SlotIndex), ServiceExecutionState, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &response);              /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    default:   /* Generic Get */
    {
      vSwUpdM_GridRpc_ComplexResponseClassBkGetGenericType response;
      vSwUpdM_GridRpc_InitComplexResponseClassBkGetGenericType(slot->ServiceIndex, slot->Result, slot->Buffer.GenericValue, &response);
      retVal =  vSwUpdM_GridRpc_TransmitResponse(vSwUpdM_GetNodeIdxOfPersistServer_Slots(SlotIndex), ServiceExecutionState, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &response);              /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_BkPersistServer_TransmitGetResponse */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_TransmitResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_TransmitResponse( /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex,
  vSwUpdM_GridRpc_ServiceExecutionStateType ServiceExecutionState)
{
  Std_ReturnType retVal = E_OK;
  vSwUpdM_BkPersistServer_VarSlotPtrType slot = vSwUpdM_BkPersistServer_GetSlotPtr(SlotIndex); /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  switch (slot->Command)
  {
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET:
    {
      retVal = vSwUpdM_BkPersistServer_TransmitGetResponse(SlotIndex, ServiceExecutionState);
      break;
    }
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET:
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN:
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE:
    {
      vSwUpdM_GridRpc_ComplexResponseClassSimpleType response;
      vSwUpdM_GridRpc_InitComplexResponseClassSimpleType(slot->ServiceIndex, slot->Result, &response);
      retVal = vSwUpdM_GridRpc_TransmitResponse(vSwUpdM_GetNodeIdxOfPersistServer_Slots(SlotIndex), ServiceExecutionState, (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &response); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
      break;
    }
    default:
    {
      /* Do not reply to invalid requests. */
      break;
    }
  }

  return retVal;
} /* vSwUpdM_BkPersistServerTransmitResponse */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecGetCallout
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecGetCallout(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot)
{
  Std_ReturnType calloutResult = E_NOT_OK;

  switch (Slot->ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE:
    {
      vSwUpdM_UpdateStateType updateState;

      calloutResult = vSwUpdM_Appl_GetUpdateState(Slot->OpStatus, &updateState);
      Slot->Buffer.GenericValue = updateState;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE:
    {
      vSwUpdM_PartitionStateType partitionState;

      calloutResult = vSwUpdM_Appl_GetPartitionState(Slot->OpStatus, Slot->Entities.PartitionId, &partitionState);
      Slot->Buffer.GenericValue = partitionState;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY:
    {
      vSwUpdM_ValidType partitionValidity;

      calloutResult = vSwUpdM_Appl_GetPartitionValid(Slot->OpStatus, Slot->Entities.PartitionId, &partitionValidity);
      Slot->Buffer.GenericValue = partitionValidity;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION:
    {
      vSwUpdM_PartitionRevisionType partitionRevision;

      calloutResult = vSwUpdM_Appl_GetPartitionRevision(Slot->OpStatus, Slot->Entities.PartitionId, &partitionRevision);
      Slot->Buffer.GenericValue = partitionRevision;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
    {
      vSwUpdM_ModuleStateType moduleState;

      calloutResult = vSwUpdM_Appl_GetModuleState(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, &moduleState);
      Slot->Buffer.GenericValue = moduleState;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
    {
      vSwUpdM_ValidType moduleValidity;

      calloutResult = vSwUpdM_Appl_GetModuleValid(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, &moduleValidity);
      Slot->Buffer.GenericValue = moduleValidity;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
    {
      vSwUpdM_ModuleRevisionType moduleRevision;

      calloutResult = vSwUpdM_Appl_GetModuleRevision(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, &moduleRevision);
      Slot->Buffer.GenericValue = moduleRevision;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
    {
      vSwUpdM_ProgrammingAttemptsType programmingAttempts;

      calloutResult = vSwUpdM_Appl_GetModuleProgrammingAttempts(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, &programmingAttempts);
      Slot->Buffer.GenericValue = programmingAttempts;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
    {
      uint32 segmentCount;

      calloutResult = vSwUpdM_Appl_GetSegmentCount(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, &segmentCount);
      Slot->Buffer.GenericValue = segmentCount;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
    {
      vSwUpdM_RegionStateType regionState;

      calloutResult = vSwUpdM_Appl_GetRegionState(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, &regionState);
      Slot->Buffer.GenericValue = regionState;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
    {
      vSwUpdM_ProgrammingAttemptsType programmingAttempts;

      calloutResult = vSwUpdM_Appl_GetRegionProgrammingAttempts(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, &programmingAttempts);
      Slot->Buffer.GenericValue = programmingAttempts;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
    {
      vSwUpdM_AddressType eraseAddr;

      calloutResult = vSwUpdM_Appl_GetRegionEraseAddress(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, &eraseAddr);
      Slot->Buffer.GenericValue = eraseAddr;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    {
      calloutResult = vSwUpdM_Appl_GetSegmentAttributes(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId,
                                                        Slot->Entities.SegmentIdx, &Slot->Buffer.SegmentInfo);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
    {
      vSwUpdM_AddressType writeAddr;

      calloutResult = vSwUpdM_Appl_GetSegmentWriteAddress(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.SegmentIdx, &writeAddr);
      Slot->Buffer.GenericValue = writeAddr;
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
    {
      vSwUpdM_ExtendedResumeInfoType extendedResumeInfo;
      calloutResult = vSwUpdM_Appl_GetResumeInfo(Slot->OpStatus, &extendedResumeInfo);
      vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo(&Slot->Buffer.ResumeInfo, &extendedResumeInfo);
      break;
    }
    default:
    {
      /* Reject invalid PARAM */
      break;
    }
  }

  return calloutResult;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_BkPersistServer_ExecGetCallout */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecSetCallout
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecSetCallout(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot)  /* PRQA S 3673 */ /* MD_vSwUpdM_Rule8.13_3673_PointerToConstParameter */
{
  Std_ReturnType calloutResult = E_NOT_OK;

  switch (Slot->ParamType)
  {
    case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE:
    {
      calloutResult = vSwUpdM_Appl_SetUpdateState(Slot->OpStatus, (vSwUpdM_UpdateStateType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE:
    {
      vSwUpdM_PartitionStateMasksIterType maskEndIdx;
      vSwUpdM_PartitionStateType          currentMask, changedBits;

      maskEndIdx  = vSwUpdM_GetPartitionStateMasksEndIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Slot->Entities.PartitionId));
      currentMask = vSwUpdM_GetPartitionStateBitmaskOfPartitionStateMasks(Slot->MaskIdx);
      changedBits = Slot->Entities.PartitionStateChangeMask & currentMask;

      /* Check if callout needs to be called. */
      if (changedBits != 0u)
      {
        calloutResult = vSwUpdM_Appl_SetPartitionState(Slot->OpStatus, Slot->Entities.PartitionId, ((vSwUpdM_PartitionStateType) Slot->Buffer.GenericValue & currentMask),
                                                       currentMask, Slot->SyncFlag);
      }
      else
      {
        calloutResult = E_OK;
      }

      if (calloutResult == E_OK)
      {
        /* Current mask was successfully processed - search next mask, which must be processed. */
        Slot->MaskIdx += 1u;

        for(; Slot->MaskIdx < maskEndIdx; Slot->MaskIdx++)
        {
          if ((Slot->Entities.PartitionStateChangeMask & vSwUpdM_GetPartitionStateBitmaskOfPartitionStateMasks(Slot->MaskIdx)) != 0u)
          {
            break;
          }
        }

        /* If such a mask exist convert final callout result into an intermediate one. */
        if (Slot->MaskIdx < maskEndIdx)
        {
          calloutResult = VSWUPDM_E_BUSY; /* Setting partition state is still ongoing. */
        }
      }

      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY:
    {
      calloutResult = vSwUpdM_Appl_SetPartitionValid(Slot->OpStatus, Slot->Entities.PartitionId, (vSwUpdM_ValidType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION:
    {
      calloutResult = vSwUpdM_Appl_SetPartitionRevision(Slot->OpStatus, Slot->Entities.PartitionId, (vSwUpdM_PartitionRevisionType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
    {
      calloutResult = vSwUpdM_Appl_SetModuleState(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, (vSwUpdM_ModuleStateType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
    {
      calloutResult = vSwUpdM_Appl_SetModuleValid(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, (vSwUpdM_ValidType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
    {
      calloutResult = vSwUpdM_Appl_SetModuleRevision(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, (vSwUpdM_ModuleRevisionType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
    {
      calloutResult = vSwUpdM_Appl_SetModuleProgrammingAttempts(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, (vSwUpdM_ProgrammingAttemptsType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
    {
      calloutResult = vSwUpdM_Appl_SetSegmentCount(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, (uint32) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
    {
      calloutResult = vSwUpdM_Appl_SetRegionState(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, (vSwUpdM_RegionStateType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
    {
      calloutResult = vSwUpdM_Appl_SetRegionProgrammingAttempts(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, (vSwUpdM_ProgrammingAttemptsType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
    {
      calloutResult = vSwUpdM_Appl_SetRegionEraseAddress(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.RegionId, (vSwUpdM_AddressType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
    {
      calloutResult = vSwUpdM_Appl_SetSegmentAttributes(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.SegmentIdx, (vSwUpdM_SegmentDynamicAttributesType*) &Slot->Buffer.SegmentInfo, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
    {
      calloutResult = vSwUpdM_Appl_SetSegmentWriteAddress(Slot->OpStatus, Slot->Entities.PartitionId, Slot->Entities.ModuleId, Slot->Entities.SegmentIdx, (vSwUpdM_AddressType) Slot->Buffer.GenericValue, Slot->SyncFlag);
      break;
    }
    case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
    {
      vSwUpdM_ExtendedResumeInfoType extendedResumeInfo;
      vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo(&extendedResumeInfo, &Slot->Buffer.ResumeInfo);
      calloutResult = vSwUpdM_Appl_SetResumeInfo(Slot->OpStatus, &extendedResumeInfo, Slot->SyncFlag);
      break;
    }
    default:
    {
      /* Reject invalid PARAM */
      break;
    }
  }

  return calloutResult;
  /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
} /* vSwUpdM_BkPersistServer_ExecSetCallout */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecCallout
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
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
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecCallout(
  vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex)
{
  Std_ReturnType calloutResult;
  vSwUpdM_NodeGroupIterType ownerGroup;
  vSwUpdM_BkPersistServer_VarSlotPtrType slot = vSwUpdM_BkPersistServer_GetSlotPtr(SlotIndex);

  /* #100 Make source node available for callout by vSwUpdM_GetCurrentPersistClientNode API. */

  /* #110 If the entity has a dedicated owner:
   *     Provide the entity owner (instead of the request source). */
  if (vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity(&slot->Entities, slot->ParamType, &ownerGroup) == E_OK)
  {
    vSwUpdM_DevError_Assert((vSwUpdM_GetNNodesOfNodeGroup(ownerGroup) == 1u), VSWUPDM_DEVERROR_ASSERT_44); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

    /* #111 Get first (and only) owner group member. */
    vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_GetNodeGroup2NodeInd(vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(ownerGroup)));
  }
  else
  {
    /* #112 Otherwise: provide request source. */
    vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_GetNodeIdxOfPersistServer_Slots(SlotIndex));
  }

  /* #200 Call callout function. */
  switch (slot->Command)
  {
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN:
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE:
    {
      calloutResult = E_OK;
      break;
    }
    case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET:
    {
      calloutResult = vSwUpdM_BkPersistServer_ExecGetCallout(slot);
      break;
    }
    default:
    /* case VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET: */
    {
      calloutResult = vSwUpdM_BkPersistServer_ExecSetCallout(slot);
      break;
    }
  }

  /* #300 Reset source note to an invalid value. */
  vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_GetSizeOfNode());

  return calloutResult;
} /* vSwUpdM_BkPersistServer_ExecCallout */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetSlot
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetSlot(
  vSwUpdM_BkPersistServer_VarSlotPtrType Slot,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo,
  boolean SyncFlag)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* HINT: No protection by a critical setion is required here, because: 
   *       - The same source is not allowed to transmit a second request before
   *         a previous request is responded.
   *       - Each source has a dedicated slot.
   *       => Otherwise the access on Slot->State would need a Critical Section.
   */

  /* PRQA S 2841 TAG_SlotPointerAccess */ /* MD_vSwUpdM_Rule18.1_2841_DereferenceOfInvalidPointerPostbuildStuctures */
  if (Slot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE)
  {
    retVal = E_OK;

    Slot->Command = Command;

    if (Entities != NULL_PTR)
    {
      Slot->Entities = (*Entities);
    }

    Slot->ParamType = ParamType;

    if (SegmentAttributes != NULL_PTR)
    {
      Slot->Buffer.SegmentInfo = *SegmentAttributes;
    }
    else if (ResumeInfo != NULL_PTR)
    {
      Slot->Buffer.ResumeInfo = *ResumeInfo;
    }
    else
    {
      Slot->Buffer.GenericValue = GenericValue;
    }

    Slot->ServiceIndex = ServiceIndex;
    Slot->SyncFlag     = SyncFlag;

    Slot->OpStatus     = VSWUPDM_OP_STATUS_INITIAL;
    Slot->MaskIdx      = vSwUpdM_GetPartitionStateMasksStartIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Slot->Entities.PartitionId));
    Slot->State        = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_ENQUEUED;

    /* New enqueued slot requires processing. */
    vSwUpdM_BkPersistServer_EventPending = TRUE;
  }
  /* PRQA L:TAG_SlotPointerAccess */

  return retVal;

  /* PRQA S 6010, 6060 1 */ /* MD_MSR_STPTH, MD_MSR_STPAR */
} /* vSwUpdM_BkPersistServer_SetSlot */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_EnqueueRequest
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_EnqueueRequest(
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentAttributes,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo,
  boolean SyncFlag)
{
  /* #100 Select appropriate slot. */
  vSwUpdM_BkPersistServer_VarSlotsIterType slotIndex;
  vSwUpdM_BkPersistServer_VarSlotPtrType slot;
  Std_ReturnType retVal = E_NOT_OK;

  if (vSwUpdM_BkPersistServer_GetSlotByNode(SourceIndex, &slotIndex) == E_OK)
  {
    slot = vSwUpdM_BkPersistServer_GetSlotPtr(slotIndex);

    /* #110 If request fits configuration:
            Copy data to slot structure. */
    if (vSwUpdM_BkPersistServer_IsRequestAccepted(SourceIndex, Command, ParamType, Entities) == E_OK)
    {
      /* PRQA S 2841 1 */ /* MD_vSwUpdM_Rule18.1_2841_DereferenceOfInvalidPointerPostbuildStuctures */
      retVal = vSwUpdM_BkPersistServer_SetSlot(slot, ServiceIndex, Command, Entities, ParamType, GenericValue, SegmentAttributes, ResumeInfo, SyncFlag);
    }
  }
  return retVal;

  /* PRQA S 6010, 6060 1 */ /* MD_MSR_STPTH, MD_MSR_STPAR */
} /* vSwUpdM_BkPersistServer_EnqueueRequest */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetSlotByNode
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetSlotByNode(
  vSwUpdM_NodeIterType SourceIndex,
  P2VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SlotIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  vSwUpdM_PersistServer_SlotsIterType slotIndex = vSwUpdM_GetSizeOfPersistServer_Slots(); /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  boolean hasPersistServer = (boolean) vSwUpdM_HasPersistServer_Slots(); /* PRQA S 2981, 2995, 4304 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_MSR_AutosarBoolean */

  if (hasPersistServer == TRUE) /* PRQA S 2991, 2995 */ /* MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
  {
    /* Abort condition (index + 1 <= size) is equivalent to (index < size).
     * But does not cause a compiler warning if size is zero. */
    for (slotIndex = 0u; (slotIndex + 1u) <= vSwUpdM_GetSizeOfPersistServer_Slots(); slotIndex++)
    {
      /* PRQA S 2841 1 */ /* MD_vSwUpdM_Rule18.1_2841_DereferenceOfInvalidPointerPostbuildStuctures */
      if (SourceIndex == vSwUpdM_GetNodeIdxOfPersistServer_Slots(slotIndex))
      {
        retVal = E_OK;
        break;
      }
    }
  }

  (*SlotIndex) = (vSwUpdM_BkPersistServer_VarSlotsIterType) slotIndex;

  return retVal;
} /* vSwUpdM_BkPersistServer_GetSlotByNode */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_IsRequestAccepted
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_IsRequestAccepted(
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command,
  vSwUpdM_BkPersist_ParamType ParamType,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities)
{
  Std_ReturnType            retVal = E_NOT_OK;
  vSwUpdM_NodeGroupIterType nodeGroup = vSwUpdM_GetSizeOfNodeGroup();
  boolean                   checkSourceNode = TRUE;

  if (vSwUpdM_BkPersistServer_InitFlag == TRUE)
  {

    if (vSwUpdM_BkPersistServer_CheckEntities(ParamType, Entities) == E_OK)
    {
      /* #10 Determine configured client nodeGroup for given ParamType. */
      switch (ParamType)
      {
        case VSWUPDM_BKPERSIST_PARAM_NONE:
        {
          if ((Command == VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_OPEN)
            || (Command == VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_CLOSE))
          {
            /* All nodes that have a "slot" (checked prior to this) are allowed to OPEN/CLOSE.
             * There are no further restrictions apply for OPEN/CLOSE requests. */
            checkSourceNode = FALSE;
          }
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_UPDATE_STATE:
        {
          nodeGroup = vSwUpdM_GetNodeGroupServerUpdateState();
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_PARTITION_STATE:
        {
          vSwUpdM_PartitionStateMasksIterType maskIdx;
          vSwUpdM_NodeIterType nodeIdx;

          /* Check all node groups referenced by each mask .. */
          for (maskIdx = vSwUpdM_GetPartitionStateMasksStartIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Entities->PartitionId));
            maskIdx < vSwUpdM_GetPartitionStateMasksEndIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Entities->PartitionId));
            maskIdx++)
          {
            /* .. And check each node of found node group if it matches sourceIndex. */
            for (nodeIdx = vSwUpdM_GetNodeGroup2NodeIndStartIdxOfNodeGroup(vSwUpdM_GetNodeGroupPartitionStateIdxOfPartitionStateMasks(maskIdx));
              nodeIdx < vSwUpdM_GetNodeGroup2NodeIndEndIdxOfNodeGroup(vSwUpdM_GetNodeGroupPartitionStateIdxOfPartitionStateMasks(maskIdx));
              nodeIdx++)
            {
              if (vSwUpdM_GetNodeGroup2NodeInd(nodeIdx) == SourceIndex)
              {
                /* Request can be accepted since there is at least one mask, which refer sourceIndex as member of referenced client group. */
                nodeGroup = vSwUpdM_GetNodeGroupPartitionStateIdxOfPartitionStateMasks(maskIdx);
                break;
              }
            }
          }
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_PARTITION_VALIDITY:
        {
          nodeGroup = vSwUpdM_GetNodeGroupPartitionValidityIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Entities->PartitionId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_PARTITION_REVISION:
        {
          nodeGroup = vSwUpdM_GetNodeGroupPartitionRevisionIdxOfBKPartitionNodeGroupReference(vSwUpdM_GetBKPartitionNodeGroupReferenceServerIdxOfPartition(Entities->PartitionId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_MODULE_STATE:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleStateIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_MODULE_VALIDITY:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleValidityIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_MODULE_REVISION:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleRevisionIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_MODULE_PROGRAMMING_ATTEMPTS:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleProgrammingAttemptsIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_MODULE_SEGMENT_COUNT:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_REGION_STATE:
        {
          nodeGroup = vSwUpdM_GetNodeGroupRegionStateIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceServerIdxOfRegion(Entities->RegionId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_REGION_PROGRAMMING_ATTEMPTS:
        {
          nodeGroup = vSwUpdM_GetNodeGroupRegionProgrammingAttemptsIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceServerIdxOfRegion(Entities->RegionId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_REGION_ERASE_ADDRESS:
        {
          nodeGroup = vSwUpdM_GetNodeGroupRegionEraseAddressIdxOfBKRegionNodeGroupReference(vSwUpdM_GetBKRegionNodeGroupReferenceServerIdxOfRegion(Entities->RegionId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_SEGMENT_WRITE_ADDRESS:
        {
          nodeGroup = vSwUpdM_GetNodeGroupModuleSegmentDataIdxOfBKModuleNodeGroupReference(vSwUpdM_GetBKModuleNodeGroupReferenceServerIdxOfModule(Entities->ModuleId));
          break;
        }
        case VSWUPDM_BKPERSIST_PARAM_RESUME_INFO:
        {
          nodeGroup = vSwUpdM_GetNodeGroupServerResumeInfo();
          break;
        }
        default:
        /* Nothing to do since was already initialized to illegal value. */
        {
          break;
        }
      }

      /* #20 Check if sourceIndex is part of nodeGroup */
      if (checkSourceNode == TRUE)
      {
        if (nodeGroup < vSwUpdM_GetSizeOfNodeGroup())
        {
          if (vSwUpdM_GridNode_IsNodeContainedInNodeGroup(nodeGroup, SourceIndex) == TRUE)
          {
            /* Request can be accepted since there is at least one mask, which refer sourceIndex as member of referenced client group. */
            retVal = E_OK;
          }
        }
      }
      else
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
  /* PRQA S 6010, 6030, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCYC */
} /* vSwUpdM_BkPersistServer_IsRequestAccepted */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_NextSlot
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_NextSlot(P2VAR(vSwUpdM_BkPersistServer_VarSlotsIterType, AUTOMATIC, VSWUPDM_APPL_VAR) SlotIndex)
{
  vSwUpdM_BkPersistServer_VarSlotsIterType slotCount;
  vSwUpdM_BkPersistServer_VarSlotPtrType slot;  /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  /* Abort condition (index + 1 <= size) is equivalent to (index < size).
    * But does not cause a compiler warning if size is zero. */
  for (slotCount = 0u; (slotCount + 1u) <= vSwUpdM_GetSizeOfBkPersistServer_VarSlots(); slotCount++)
  {
    (*SlotIndex)++;
    if ((*SlotIndex) == vSwUpdM_GetSizeOfBkPersistServer_VarSlots())
    {
      (*SlotIndex) = 0u;
    }

    slot = vSwUpdM_BkPersistServer_GetSlotPtr(*SlotIndex);

    if (slot->State != VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE)
    {
      break;
    }
  }
} /* vSwUpdM_BkPersistServer_NextSlot */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ProcessEvents
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ProcessEvents(void)
{
  /* #10 If Request was received (asynchronously):
   *     Set BkPersistServer to active state.
   */
  if (vSwUpdM_BkPersistServer_EventPending == TRUE)
  {
    vSwUpdM_BkPersistServer_EventPending = FALSE;
    vSwUpdM_BkPersistServer_IsActive = TRUE;
  }

  /* #20 If BkPersistServer is active: */
  if (vSwUpdM_BkPersistServer_IsActive == TRUE)
  {
    /* #21 If active request has become IDLE:
     *     Schedule processing of next slot. */
    if (vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_ActiveSlot)->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE)
    {
      vSwUpdM_BkPersistServer_NextSlot(&vSwUpdM_BkPersistServer_ActiveSlot);
    }

    /* #22 If no active slot is left: 
     *       Set BkPersistServer to inactive state.
     */
    if (vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_ActiveSlot)->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE)
    {
      vSwUpdM_BkPersistServer_IsActive = FALSE;
    }
  }
} /* vSwUpdM_BkPersistServer_ProcessEvents */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_HandleActiveSlot
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
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_HandleActiveSlot(void)
{
  /* #10 For active slot. */
  vSwUpdM_BkPersistServer_VarSlotPtrType slot = vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_ActiveSlot);

  /* #20 If active slot is just enqueued:
    *     Check precondition. */
  if (slot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_ENQUEUED)
  {
    slot->Result = vSwUpdM_BkPersistServer_CheckPrecondition(slot);

    /* #21 If request is not allowed:
     *     Send negative response immediately. */
    if (slot->Result == E_OK)
    {
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING;
    }
    else
    {
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_TRANSMIT_RESPONSE;
    }
  }
   
  /* #30 If request in active slot is accepted:
   *     Call callout.*/
  if (slot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING)
  {
    slot->Result = vSwUpdM_BkPersistServer_ExecCallout(vSwUpdM_BkPersistServer_ActiveSlot);
    vSwUpdM_BkPersistServer_EvalCalloutResult(vSwUpdM_BkPersistServer_ActiveSlot);
  }
   
  /* #40 If active slot is ready for response transmission:
   *     Transmit response. */
  if (slot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_TRANSMIT_RESPONSE)
  {
    /* #41 If response transmitted:
      *     Set slot to IDLE. */
    if (vSwUpdM_BkPersistServer_TransmitResponse(vSwUpdM_BkPersistServer_ActiveSlot, VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED) == E_OK)
    {
      vSwUpdM_BkPersistServer_PostHandler(slot);
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE;
    }
  }
  else
  /* #50 Otherwise:
   *     Transmit a "pending" response. */
  {
    vSwUpdM_BkPersistServer_VarSlotPtrType responseSlot; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

    /* #51 Prepare transmission of the pending response for the next slot. */
    vSwUpdM_BkPersistServer_NextSlot(&vSwUpdM_BkPersistServer_ResponseSlot);
    responseSlot = vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_ResponseSlot);
   
    if (    (responseSlot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_ENQUEUED)
         || (responseSlot->State == VSWUPDM_BKPERSISTSERVER_SLOTSTATE_PROCESSING))
    {
      /* #52 If the transmission of the pending response fails, ignore this (it will be retried after N cycles again). */
      (void)vSwUpdM_BkPersistServer_TransmitResponse(vSwUpdM_BkPersistServer_ResponseSlot, VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING);
    }
  }
} /* vSwUpdM_BkPersistServer_HandleActiveSlot */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetSlotPtr
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(vSwUpdM_BkPersistServer_VarSlotPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetSlotPtr(vSwUpdM_BkPersistServer_VarSlotsIterType SlotIndex)
{
  vSwUpdM_BkPersistServer_VarSlotPtrType retVal;

  /* In case vSwUpdM_BkPersistServer_VarSlots has zero entries (= Generator produces NULL_PTR access), SlotIndex is not
   * evaluated by vSwUpdM_GetAddrBkPersistServer_VarSlots(). To avoid compiler warnings, a dummy statement is required
   * here. */
  VSWUPDM_DUMMY_STATEMENT(SlotIndex);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  vSwUpdM_DevError_Assert((vSwUpdM_HasBkPersistServer_VarSlots()), VSWUPDM_DEVERROR_ASSERT_45); /* PRQA S 2995, 4304 */ /*  MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_MSR_AutosarBoolean */
  retVal = vSwUpdM_GetAddrBkPersistServer_VarSlots(SlotIndex);

  return retVal;
} /* vSwUpdM_BkPersistServer_GetSlotPtr */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetCurrentClientNode
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_NodeIterType Node)
{
  vSwUpdM_BkCurrentPersistorNode = Node;
} /* vSwUpdM_BkPersistServer_SetCurrentClientNode */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_InitMemory
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_InitMemory(void)
{
  /* Init() is not yet done */
  vSwUpdM_BkPersistServer_InitFlag = FALSE;
} /* vSwUpdM_BkPersistServer_InitMemory */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_Init(void)
{
  vSwUpdM_BkPersistServer_VarSlotsIterType slotIndex = vSwUpdM_GetSizeOfBkPersistServer_VarSlots(); /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vSwUpdM_BkPersistServer_VarSlotPtrType slot;
  boolean hasPersistServer = (boolean) vSwUpdM_HasBkPersistServer_VarSlots(); /* PRQA S 2981, 2995, 4304 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_MSR_AutosarBoolean */

  if (hasPersistServer == TRUE) /* PRQA S 2991, 2995 */ /* MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
  {
    /* Abort condition (index + 1 <= size) is equivalent to (index < size).
     * But does not cause a compiler warning if size is zero. */
    for (slotIndex = 0u; (slotIndex + 1u) <= vSwUpdM_GetSizeOfBkPersistServer_VarSlots(); slotIndex++)
    {
      slot = vSwUpdM_BkPersistServer_GetSlotPtr(slotIndex);

      /* PRQA S 2841 1 */ /* MD_vSwUpdM_Rule18.1_2841_DereferenceOfInvalidPointerPostbuildStuctures */
      slot->State = VSWUPDM_BKPERSISTSERVER_SLOTSTATE_IDLE;
    }
  }

  vSwUpdM_BkPersistServer_ActiveSlot = 0u;
  vSwUpdM_BkPersistServer_ResponseSlot = 0u;
  vSwUpdM_BkPersistServer_EventPending = FALSE;
  vSwUpdM_BkPersistServer_IsActive = FALSE;

  /* Initialize current persistor node with invalid value */
  vSwUpdM_BkPersistServer_SetCurrentClientNode(vSwUpdM_GetSizeOfNode());

  /* Init() is done */
  vSwUpdM_BkPersistServer_InitFlag = TRUE;
} /* vSwUpdM_BkPersistServer_Init */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetCurrentClientNode
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(vSwUpdM_NodeIterType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetCurrentClientNode(void)
{
  return vSwUpdM_BkCurrentPersistorNode;
} /* vSwUpdM_BkPersistServer_GetCurrentClientNode */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetGenericParameter
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetGenericParameter(      /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  boolean SyncFlag)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                          /*!< SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER, /*!< ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET,          /*!< Command: Requested Action */
    Entities,                                             /*!< Entities: Entities for this request. */
    ParamType,                                            /*!< ParamType: Which parameter is addressed by this request. */
    GenericValue,                                         /*!< GenericValue: Value to set to given parameter. */
    NULL_PTR,                                             /*!< SegmentInfo: Segmentinfo to set. */
    NULL_PTR,                                             /*!< ResumeInfo: ResumeInfo to set. */
    SyncFlag                                              /*!< SyncFlag: NvM sync point reached. */
    );

  return retVal;
} /* vSwUpdM_BkPersistServer_SetGenericParameter */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetSegmentAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetSegmentAttributes(      /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentInfo,
  boolean SyncFlag)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                               /* < SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES,     /* < ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET,                      /* < Command: Requested Action */
    Entities,                                                  /* < Entities: Entities for this request. */
    VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES,                       /* < ParamType: Which parameter is addressed by this request. */
    0u,                                                        /* < GenericValue: Value to set to given parameter. */
    SegmentInfo,                                               /* < SegmentInfo: Segmentinfo to set. */
    NULL_PTR,                                                  /* < ResumeInfo: ResumeInfo to set. */
    SyncFlag
  );

  return retVal;
} /* vSwUpdM_BkPersistServer_SetSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetResumeInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetResumeInfo(          /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) ResumeInfo,
  boolean SyncFlag)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                               /*!< SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO,            /*!< ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_SET,               /*!< Command: Requested Action */
    NULL_PTR,                                                  /*!< Entities: Entities for this request. */
    VSWUPDM_BKPERSIST_PARAM_RESUME_INFO,                       /*!< ParamType: Which parameter is addressed by this request. */
    0u,                                                        /*!< GenericValue: Value to set to given parameter. */
    NULL_PTR,                                                  /*!< SegmentInfo: Segmentinfo to set. */
    ResumeInfo,                                                /*!< ResumeInfo: ResumeInfo to set. */
    SyncFlag                                                   /*!< SyncFlag: NvM sync point reached. */
  );

  return retVal;
} /* vSwUpdM_BkPersistServer_SetResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecCommand
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecCommand(      /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (Command < VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_COUNT)
  {
    retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
      SourceIndex,                                  /*!< SourceIndex: Source of Request. */
      VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND,  /*!< ServiceIndex: GridSrvc Request that triggered this service. */
      Command,                                      /*!< Command: Requested Action */
      NULL_PTR,                                     /*!< Entities: Entities for this request. */
      VSWUPDM_BKPERSIST_PARAM_NONE,                 /*!< ParamType: Which parameter is addressed by this request. */
      0u,                                           /*!< GenericValue: Value to set to given parameter. */
      NULL_PTR,                                     /*!< SegmentInfo: Segment info to set. */
      NULL_PTR,                                     /*!< ResumeInfo: ResumeInfo to set. */
      FALSE                                         /*!< SyncFlag: NvM sync point reached. */
    );
  }

  return retVal;
} /* vSwUpdM_BkPersistServer_ExecCommand */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetGenericParameter
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetGenericParameter(      /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                               /*!< SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER,      /*!< ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET,               /*!< Command: Requested Action */
    Entities,                                                  /*!< Entities: Entities for this request. */
    ParamType,                                                 /*!< ParamType: Which parameter is addressed by this request. */
    0u,                                                        /*!< GenericValue: Value to set to given parameter. */
    NULL_PTR,                                                  /*!< SegmentInfo: Segment info to set. */
    NULL_PTR,                                                  /*!< ResumeInfo: ResumeInfo to set. */
    FALSE                                                      /*!< SyncFlag: NvM sync point reached. */
  );

  return retVal;
} /* vSwUpdM_BkPersistServer_RequestGetGenericParameter */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetSegmentAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetSegmentAttributes(       /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                               /* < SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES,     /* < ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET,                      /* < Command: Requested Action */
    Entities,                                                  /* < Entities: Entities for this request. */
    VSWUPDM_BKPERSIST_PARAM_SEGMENT_ATTRIBUTES,                       /* < ParamType: Which parameter is addressed by this request. */
    0u,                                                        /* < GenericValue: Value to set to given parameter. */
    NULL_PTR,                                                  /* < SegmentInfo: Segment info to set. */
    NULL_PTR,                                                  /* < ResumeInfo: ResumeInfo to set. */
    FALSE                                                      /* < SyncFlag: NvM sync point reached. */
  );

  return retVal;
} /* vSwUpdM_BkPersistServer_RequestGetSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetResumeInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetResumeInfo(           /* PRQA S 3219 */ /* MD_vSwUpdM_Rule2.1_3219_PublicInline */
  vSwUpdM_NodeIterType SourceIndex)
{
  Std_ReturnType retVal;

  retVal = vSwUpdM_BkPersistServer_EnqueueRequest(
    SourceIndex,                                               /*!< SourceIndex: Source of Request. */
    VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO,            /*!< ServiceIndex: GridSrvc Request that triggered this service. */
    VSWUPDM_BKPERSIST_GENERICSERVICECOMMAND_GET,               /*!< Command: Requested Action */
    NULL_PTR,                                                  /*!< Entities: Entities for this request. */
    VSWUPDM_BKPERSIST_PARAM_RESUME_INFO,                       /*!< ParamType: Which parameter is addressed by this request. */
    0u,                                                        /*!< GenericValue: Value to set to given parameter. */
    NULL_PTR,                                                  /*!< SegmentInfo: Segment info to set. */
    NULL_PTR,                                                  /*!< ResumeInfo: ResumeInfo to set. */
    FALSE                                                      /*!< SyncFlag: NvM sync point reached. */
  );

  return retVal;
} /* vSwUpdM_BkPersistServer_RequestGetResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_Execute
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_Execute(void)
{
  /* #10 Handle asynchronous events. */
  vSwUpdM_BkPersistServer_ProcessEvents();

  /* #20 Process active slot. */
  if (vSwUpdM_BkPersistServer_IsActive == TRUE)
  {
    vSwUpdM_BkPersistServer_HandleActiveSlot();
  }
} /* vSwUpdM_BkPersistServer_Execute */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Bookkeeper.c
 *********************************************************************************************************************/
