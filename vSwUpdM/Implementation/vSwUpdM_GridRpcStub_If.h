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
/*!        \file  vSwUpdM_GridRpcStub_If.h
 *        \brief  vSwUpdM_GridRpcStub unit interface header file
 *      \details  Interface provided by the vSwUpdM_GridRpcStub unit.
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

#if !defined (VSWUPDM_GRIDRPCSTUB_IF_H)
# define VSWUPDM_GRIDRPCSTUB_IF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* GridRpcStub types header */
#include "vSwUpdM_GridRpcStub_Types.h"

/* Interface header of containing MultipleUnit */
#include "vSwUpdM_Grid_If.h"

/* Other MultipleUnits used by GridRpcStub_If (Prefer smallest set required, i.e. prefer _Types over _If) */

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
 * vSwUpdM_GridRpcStub_RemoteProcedureCall
 *********************************************************************************************************************/
/*! \brief       Fan-out for configured vRpcProxy services calls.
 *  \details     Calls the vRpc_<Service>_TargetGroup() function associated with the Service. The associated parameters
 *               are extracted from the Parameter structure.
 *  \param[in]   Destination       Target(s) for Remote Service.
 *  \param[in]   ServiceIndex      Service index of the requested service.
 *  \param[in]   Parameter         Used to determine parameters for remote service.
 *  \return      E_OK Transmission successful forwarded to vRpcProxy
 *  \return      else Transmission failed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GridRpcStub_RemoteProcedureCall(
  vSwUpdM_NodeGroupIterType Destination,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  vSwUpdM_GridSrvc_ServiceClassBasePtrType Parameter);

# define VSWUPDM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VSWUPDM_GRIDRPCSTUB_IF_H */

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_GridRpcStub_If.h
 *********************************************************************************************************************/
