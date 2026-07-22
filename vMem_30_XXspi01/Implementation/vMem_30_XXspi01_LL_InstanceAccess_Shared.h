/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_InstanceAccess_Shared.h
 *        \brief  Internally shared vMem_30_XXspi01 functionality for instance access purposes.
 *      \details  This file contains functionality that is shared by different submodules of the component for instance
 *                access purposes.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXSPI01_LL_INSTANCEACCESS_SHARED_H)
# define VMEM_30_XXSPI01_LL_INSTANCEACCESS_SHARED_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXspi01_LL_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent()
 *********************************************************************************************************************/
/*! \brief        Gets the content of the register that was read out by a previous command sequence.
 *  \details      The result that was transmitted by the device is cleaned from any dummy cycles and then returned
 *                to the caller.
 *  \param[in]    deviceId            ID and index of the related device information.
 *  \param[in]    registerBuffer      Pointer to the buffer where the received register content is stored.
 *  \return       Content of the register with respect to the configured dummy cycles.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(
    vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_ConstSpiDataPtrType registerBuffer);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_INSTANCEACCESS_SHARED_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceAccess_Shared.h
 *********************************************************************************************************************/
