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
/*!        \file  vSwUpdM_SrvcRouting_If.h
 *        \brief  vSwUpdM_SrvcRouting unit interface header file
 *      \details  Interface provided by the vSwUpdM_SrvcRouting unit.
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

#if !defined (VSWUPDM_SRVCROUTING_IF_H)
# define VSWUPDM_SRVCROUTING_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* SrvcRouting types header */
#include "vSwUpdM_SrvcRouting_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Services_If.h"

/* Other MultipleUnits used by SrvcRouting_If (Prefer smallest set required, i.e. prefer _Types over _If) */
#include "vSwUpdM_Grid_Types.h"

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
 *  vSwUpdM_SrvcRouting_Init
 *********************************************************************************************************************/
/*! \brief       Initialize data structures of SrvcRouting.
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_Init(void);

/**********************************************************************************************************************
 *  Std_ReturnType vSwUpdM_Dispatch()
 *********************************************************************************************************************/
/*! \brief       Spawns a job which iterates over the configured processing steps for a certain service.
 *  \details     The vSwUpdM uses a dispatcher scheme to execute different jobs as required to provide a service and/or
 *               trigger remote/local operation. This scheme uses a list of jobs that are spawned in a fixed order as
 *               defined for a certain service.
 *  \param[in]   ServiceId            Service that shall be performed.
 *  \param[in]   ServiceDispatchIndex Sequence that shall be executed.
 *  \param[in]   RemoteServiceIndex   RemoteService that shall be used triggered
 *  \param[in]   RemoteTargetGroup    Remote Targets for this service (if applicable. Otherwise use VSWUPDM_INVALID_NODE_GROUP)
 *  \param[in]   RemoteTarget         Remote Target for this service (if applicable. Otherwise use VSWUPDM_INVALID_NODE)
 *  \param[in]   Source               Node that is the source of the request (UL = LocalNode / Remote)
 *  \param[in]   EntityIds
 *  \return      E_OK On success.
 *  \return      else Spawn of job failed.

 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Dispatch(
  vSwUpdM_ServiceIdType         ServiceId,
  vSwUpdM_ExecCtrl_SequenceListIndexType ServiceDispatchIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_NodeGroupIterType     RemoteTargetGroup,
  vSwUpdM_NodeIterType          RemoteTarget,
  vSwUpdM_NodeIterType          Source,
  vSwUpdM_EntityIdsType         EntityIds);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_SRVCROUTING_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_SrvcRouting_If.h
 *********************************************************************************************************************/
