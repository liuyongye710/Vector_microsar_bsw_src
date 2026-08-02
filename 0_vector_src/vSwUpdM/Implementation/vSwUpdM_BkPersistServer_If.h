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
/*!        \file  vSwUpdM_BkPersistServer_If.h
 *        \brief  vSwUpdM_BkPersistServer unit interface header file
 *      \details  Interface provided by the vSwUpdM_BkPersistServer unit.
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

#if !defined (VSWUPDM_BKPERSISTSERVER_IF_H)
# define VSWUPDM_BKPERSISTSERVER_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* BkPersistServer types header */
#include "vSwUpdM_BkPersistServer_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Bookkeeper_If.h"
#include "vSwUpdM_Priv.h"

/* Other MultipleUnits used by BkPersistServer_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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
 * vSwUpdM_BkPersistServer_InitMemory
 *********************************************************************************************************************/
/*! \brief       Initialize Persist server memory.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_InitMemory(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_Init
 *********************************************************************************************************************/
/*! \brief       Initialize Persist server.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_Init(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_GetCurrentClientNode
 *********************************************************************************************************************/
/*! \brief       Return current persist client node.
 *  \details     -
 *  \return      Current persist client node.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(vSwUpdM_NodeIterType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_GetCurrentClientNode(void);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_ExecCommand
 *********************************************************************************************************************/
/*! \brief       Enqueue Command request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   Command      (OPEN | CLOSE)
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_ExecCommand(
  vSwUpdM_NodeIterType SourceIndex,
  vSwUpdM_BkPersist_GenericServiceCommandType Command);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetGenericParameter
 *********************************************************************************************************************/
/*! \brief       Enqueue SetGenericParameter request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   Entities     Common entities parameter of request.
 *  \param[in]   ParamType    Type of request.
 *  \param[in]   GenericValue Generic parameter of request.
 *  \param[in]   SyncFlag     Sync parameter of request.
 *  \return      E_OK     On success.
 *  \return      E_NOT_OK Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetGenericParameter(
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType,
  vSwUpdM_BkPersist_GenericParameterType GenericValue,
  boolean SyncFlag);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetSegmentAttributes
 *********************************************************************************************************************/
/*! \brief       Enqueue SetSegmentAttributes request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   Entities     Common entities parameter of request.
 *  \param[in]   SegmentInfo  Segment info of segment for which the attributes shall be set.
 *  \param[in]   SyncFlag     Sync parameter of request.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetSegmentAttributes(
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  P2CONST(vSwUpdM_BkPersist_SegmentAttributesType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) SegmentInfo,
  boolean SyncFlag);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_SetResumeInfo
 *********************************************************************************************************************/
/*! \brief       Enqueue SetResumeInfo request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   ResumeInfo   Resume Info to be set.
 *  \param[in]   SyncFlag     Sync parameter of request.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_SetResumeInfo(
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VRPCPROXY_DATA) ResumeInfo,
  boolean SyncFlag);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetGenericParameter
 *********************************************************************************************************************/
/*! \brief       Enqueue GetGenericParameter request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   Entities     Common entities parameter of request.
 *  \param[in]   ParamType    Parameter type of request.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetGenericParameter(
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities,
  vSwUpdM_BkPersist_ParamType ParamType);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetSegmentAttributes
 *********************************************************************************************************************/
/*! \brief       Enqueue GetSegmentAttributes request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \param[in]   Entities     Common entities parameter of request.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetSegmentAttributes(
  vSwUpdM_NodeIterType SourceIndex,
  P2CONST(vSwUpdM_BkPersist_EntityType, AUTOMATIC, VSWUPDM_APPL_DATA) Entities);

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_RequestGetResumeInfo
 *********************************************************************************************************************/
/*! \brief       Enqueue GetResumeInfo request.
 *  \details     -
 *  \param[in]   SourceIndex  Source node, node which sends the request.
 *  \return      E_OK         On success.
 *  \return      E_NOT_OK     Else.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_BkPersistServer_RequestGetResumeInfo(
  vSwUpdM_NodeIterType SourceIndex);

/**********************************************************************************************************************
 *  Global Inline Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Global Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_BkPersistServer_Execute
 *********************************************************************************************************************/
/*! \brief       Schedule pending requests of PersistServer.
 *  \details     -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     BkPersistServer
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_BkPersistServer_Execute(void);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_BKPERSISTSERVER_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_BkPersistServer_If.h
 *********************************************************************************************************************/
