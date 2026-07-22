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
/*!        \file  vSwUpdM_Services_Types.h
 *        \brief  vSwUpdM_Services types header file
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

#if !defined (VSWUPDM_SERVICES_TYPES_H)
#define VSWUPDM_SERVICES_TYPES_H

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "ComStack_Types.h"

/* Types header of Component */
#include "vSwUpdM_Types.h"

/* Other MultipleUnit's Type Headers used by Services_Types */
#include "vSwUpdM_ProcNodeTypes.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
typedef struct
{
  vSwUpdM_ModuleStateType   ModuleState;          /**< The new module state to be forwarded to. */
  boolean                   UpdateResumeInfo;     /**< Determines whether resume info shall be updated too. */
} vSwUpdM_ProcessStateForwardEntryType;

/*! Type for configuration of module state forwarding during data processes. */
typedef struct
{
  vSwUpdM_ProcessStateForwardEntryType  Initial;  /**< Module state set when operation is initialized. */
  vSwUpdM_ProcessStateForwardEntryType  Pending;  /**< Module state set when operation is started. */
  vSwUpdM_ProcessStateForwardEntryType  Final;    /**< Module state set when operation is finished. */
} vSwUpdM_ProcessStateForwardType;

/*! Type for configuration of module state-dependent startup operation modes of data processes. */
typedef struct
{
  vSwUpdM_ModuleStateType         ModuleState;    /**< The module state determining the operation mode. */
  vSwUpdM_ProcNodeOperationType   ProcOperation;  /**< The startup operation mode to be used. */
} vSwUpdM_ProcessOpSelectType;

/*! Type for configuration of data processes. */
typedef struct
{
  vSwUpdM_ProcessStateForwardType                                       StateForward;   /**< Configuration of module state forwarding during data processes. */
  P2CONST(vSwUpdM_ProcessOpSelectType, AUTOMATIC, VSWUPDM_APPL_CONST)   OpSelect;       /**< Configuration of module state-dependent startup operation modes of data processes. */
  uint8                                                                 OpSelectCount;  /**< Number of entries in OpSelect. */
} vSwUpdM_ProcessConfigType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif  /* VSWUPDM_SERVICES_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Services_Types.h
 **********************************************************************************************************************/
