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
/*!        \file  vSwUpdM_BkPersistClient_If.h
 *        \brief  vSwUpdM_BkPersistClient unit interface header file
 *      \details  Interface provided by the vSwUpdM_BkPersistClient unit.
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

#if !defined (VSWUPDM_BKPERSISTCLIENT_IF_H)
# define VSWUPDM_BKPERSISTCLIENT_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* BkPersistClient types header */
#include "vSwUpdM_BkPersistClient_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Bookkeeper_If.h"

/* Other MultipleUnits used by BkPersistClient_If (Prefer smallest set required, i.e. prefer _Types over _If) */
#include "vSwUpdM_CfgTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
#define VSWUPDM_BKPERISTCLIENT_PERSISTSERVERGROUPREMOTEINDEX 0u

 /**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
  vSwUpdM_BkPersist_GenericServiceCommandType   Command;
  vSwUpdM_GridSrvc_ServiceIdxType               ServiceIndex;
  vSwUpdM_BkPersist_ParamType                   ParamType;
  vSwUpdM_NodeGroupIterType                     TargetGroup;
  vSwUpdM_BkPersist_RequestStateType            State;
  vSwUpdM_BkPersist_EntityType                  Entities;
  boolean                                       SyncFlag;
  vSwUpdM_BkPersist_SizeOfParameterType         ResponseSize;
  vSwUpdM_BkPersist_SizeOfParameterType         RequestSize;
  vSwUpdM_PartitionStateMasksIterType           RemainingMultiReq;
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR)      ResponseBuffer;
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR)      RequestParam;
}vSwUpdM_BkPersistClient_RequestType;

typedef P2VAR(vSwUpdM_BkPersistClient_RequestType, AUTOMATIC, VSWUPDM_VAR_NOINIT) vSwUpdM_BkPersistClient_RequestPtrType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern VAR(vSwUpdM_PartitionStateType, VSWUPDM_VAR_NOINIT)              vSwUpdM_BkPersistClient_LastPartitionStateResult;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VSWUPDM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Global Inline Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse
 *********************************************************************************************************************/
/*! \brief       Store response value in prepared buffer.
 *  \details     -
 *  \param[in]   GenericValue   Generic parameter of response.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetGenericParameterResponse(vSwUpdM_BkPersist_GenericParameterType GenericValue);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse
 *********************************************************************************************************************/
/*! \brief       Store response value in prepared buffer.
 *  \details     -
 *  \param[in]   SegmentAttributes   Value to be stored.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetSegmentAttributesResponse(P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentAttributes);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse
 *********************************************************************************************************************/
/*! \brief       Store response value in prepared buffer.
 *  \details     -
 *  \param[in]   ResumeInfo   Value to be stored.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_StoreGetResumeInfoResponse(P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo);

/**********************************************************************************************************************
 *  Global Functions
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_GetActiveRequest
 *********************************************************************************************************************/
/*! \brief       Returns pointer to top entry in request queue.
 *  \details     -
 *  \return      Pointer to top entry in request queue (= Active request).
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(vSwUpdM_BkPersistClient_RequestPtrType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_GetActiveRequest(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Init
 *********************************************************************************************************************/
/*! \brief       Initialize BkPersistClient.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Init(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Set
 *********************************************************************************************************************/
/*! \brief       Trigger Set request for given entity.
 *  \details     -
 *  \param[in]   Entities         Defines entity instance.
 *  \param[in]   ParamType        Defines entity type.
 *  \param[in]   ParameterSize    Size of input parameter in bytes.
 *  \param[in]   Parameter        Value to set.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Set(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Get
 *********************************************************************************************************************/
/*! \brief       Trigger Get request for given entity.
 *  \details     -
 *  \param[in]   Entities         Defines entity instance.
 *  \param[in]   ParamType        Defines entity type.
 *  \param[in]   ResponseSize     Size of output parameter in bytes.
 *  \param[in]   ResponseBuffer   Pointer to provided buffer for result
 *  \return      E_OK             On success.
 *  \return      E_NOT_OK         Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Get(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_CONST) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ResponseSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) ResponseBuffer);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Open
 *********************************************************************************************************************/
/*! \brief       Transmit Open command to PersistServer.
 *  \details     To initialize the connection to the PersistServer the Open() command is transmitted.
 *  \param[in]   TargetGroup  Node group, which shall receive the request.
 *  \return      E_OK         on success.
 *  \return      E_NOT_OK     otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Open(vSwUpdM_NodeGroupIterType TargetGroup);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Close
 *********************************************************************************************************************/
/*! \brief       Transmit Close command to PersistServer.
 *  \details     To deinitialize the connection to the PersistServer the Close() command is transmitted.
 *  \param[in]   TargetGroup  Node group, which shall receive the request.
 *  \return      E_OK         on success.
 *  \return      E_NOT_OK     otherwise.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Close(vSwUpdM_NodeGroupIterType TargetGroup);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Execute
 *********************************************************************************************************************/
/*! \brief       Poll for pending responses.
 *  \details     -
 *  \return      Current state of client or pending request(s).
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(vSwUpdM_BkPersist_RequestStateType, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Execute(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistClient_Sync
 *********************************************************************************************************************/
/*! \brief       Trigger Sync request.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistClient
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistClient_Sync(void);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BKPERSISTCLIENT_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_BkPersistClient_If.h
 *********************************************************************************************************************/
