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
/*!        \file  vSwUpdM_Bookkeeper_If.h
 *        \brief  vSwUpdM_Bookkeeper interface header file
 *      \details  Interface provided by the vSwUpdM_Bookkeeper subcomponent.
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

#if !defined (VSWUPDM_BOOKKEEPER_IF_H)
# define VSWUPDM_BOOKKEEPER_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Bookkeeper types header */
# include "vSwUpdM_Bookkeeper_Types.h"

/* Other MultipleUnits used by Bookkeeper_If (Prefer smallest set required, i.e. prefer _Types over _If) */
# include "vSwUpdM_CfgTypes.h"

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
 * vSwUpdM_Bookkeeper_InitMemory
 *********************************************************************************************************************/
/*! \brief       Initialize Bookkeeper sub component.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_InitMemory(void);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Init
 *********************************************************************************************************************/
/*! \brief       Initialize Bookkeeper sub component.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Init(void);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Set
 *********************************************************************************************************************/
/*! \brief       Request to set a value by bookkeeper.
 *  \details     -
 *  \param[in]   EntityIds      Common structure containing entity information for the current request.
 *  \param[in]   ParamType      Type of request.
 *  \param[in]   ParameterSize  Size of input parameter in bytes.
 *  \param[in]   Parameter      Points to value, which shall be set.
 *  \return      E_OK           Request was accepted.
 *  \return      E_NOT_OK       Request was rejected.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Bookkeeper needs to be initialized.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Set(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Get
 *********************************************************************************************************************/
/*! \brief       Request to get a value from bookkeeper.
 *  \details     -
 *  \param[in]   EntityIds      Common structure containing entity information for the current request.
 *  \param[in]   ParamType      Type of request.
 *  \param[in]   ParameterSize  Size of output parameter in bytes.
 *  \param[out]  Parameter      Points to value, which shall be get.
 *  \return      E_OK           Request was accepted.
 *  \return      E_NOT_OK       Request was rejected.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Bookkeeper needs to be initialized.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Get(
  P2CONST(vSwUpdM_EntityIdsType, AUTOMATIC, VSWUPDM_APPL_CONST) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_SizeOfParameterType ParameterSize,
  P2VAR(void, AUTOMATIC, VSWUPDM_APPL_VAR) Parameter);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Open
 *********************************************************************************************************************/
/*! \brief       Transmit Open() command to PersistServer.
 *  \details     -
 *  \param[in]   TargetGroup Node group, which shall receive the request.
 *  \return      E_OK        Request was accepted.
 *  \return      E_NOT_OK    Request was rejected.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Bookkeeper needs to be initialized.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Open(vSwUpdM_NodeGroupIterType TargetGroup);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Close
 *********************************************************************************************************************/
/*! \brief       Transmit Close() command to PersistServer.
 *  \details     -
 *  \param[in]   TargetGroup Node group, which shall receive the request.
 *  \return      E_OK        Request was accepted.
 *  \return      E_NOT_OK    Request was rejected.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Bookkeeper needs to be initialized.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Close(vSwUpdM_NodeGroupIterType TargetGroup);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ServerExecute
 *********************************************************************************************************************/
/*! \brief       Execute Bookkeeper server jobs.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ServerExecute(void);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_GetIdsByHandles
 *********************************************************************************************************************/
/*! \brief       Translate Entity Handles to Entity Ids.
 *  \details     -
 *  \param[in]   HandleEntities   Entity structure containing handles only.
 *  \param[out]  IdEntities       Entity structure with IDs only.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/

FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetIdsByHandles(
  P2CONST(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) HandleEntities,
  P2VAR(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) IdEntities);

/**********************************************************************************************************************
 *  Global Inline Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_GetHandlesByIds
 *********************************************************************************************************************/
/*! \brief       Translate Entity Ids Handles to Entity Handles.
 *  \details     -
 *  \param[in]   IdEntities       Entity structure with IDs only.
 *  \param[out]  HandleEntities   Entity structure containing handles only.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetHandlesByIds(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) IdEntities,
  P2VAR(vSwUpdM_BkPersist_EntityHandleType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) HandleEntities);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo
 *********************************************************************************************************************/
/*! \brief       Convert ExtendedResumeInfo structure to BkResumeInfo structure
 *  \details     Remote transmission via vRpcProxy needs structures to be flattened.
 *  \param[in]   ExtendedResumeInfo   Resume info, which shall be converted.
 *  \param[out]  BkResumeInfo         Converted resume info.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ConvertExtended2BkResumeInfo(
  P2VAR(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BkResumeInfo,
  P2CONST(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ExtendedResumeInfo);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo
 *********************************************************************************************************************/
/*! \brief       Convert BkResumeInfo structure to ExtendedResumeInfo structure
 *  \details     -
 *  \param[in]   BkResumeInfo         Resume info, which shall be converted.
 *  \param[out]  ExtendedResumeInfo   Converted resume info.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ConvertBk2ExtendedResumeInfo(
  P2VAR(vSwUpdM_ExtendedResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ExtendedResumeInfo,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) BkResumeInfo);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_Sync
 *********************************************************************************************************************/
/*! \brief       Force synchronization of pending data.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(void, VSWUPDM_CODE) vSwUpdM_Bookkeeper_Sync(void);

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_ClientExecute
 *********************************************************************************************************************/
/*! \brief       Call handler function for BkPersistClient.
 *  \details     -
 *  \return      Current state of client or pending request(s).
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_ClientExecute(void);

/**********************************************************************************************************************
 *  Global Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity
 *********************************************************************************************************************/
/*! \brief       Return the owner of the entity selected by EntityId andParamType. Returns E_NOT_OK if no owner is specified.
 *  \details     -
 *  \param[in]   EntityIds
 *  \param[in]   ParamType
 *  \param[out]  OwnerGroup of entity.
 *  \return      E_OK     if specified entity has a dedicated owner.
 *  \return      E_NOT_OK else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     Bookkeeper
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Bookkeeper_GetOwnerGroupOfEntity(
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_VAR) EntityIds,
  vSwUpdM_BkPersist_ParamType ParamType,
  P2VAR(vSwUpdM_NodeGroupIterType, AUTOMATIC, VSWUPDM_APPL_VAR) OwnerGroup);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BOOKKEEPER_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Bookkeeper_If.h
 *********************************************************************************************************************/
