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
/*!        \file  vMem_30_XXspi01_LL_InstanceModifier.h
 *        \brief  -
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MULTIPLE INCLUSION PROTECTION
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXSPI01_LL_INSTANCEMODIFIER_H_)
# define VMEM_30_XXSPI01_LL_INSTANCEMODIFIER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_Types.h"

/*********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess()
 *********************************************************************************************************************/
/*! \brief        Builds and transmits the Spi sequence to perform a memory write access at the external flash device.
 *  \details      -
 *  \param[in]    instanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \param[in]    deviceId            ID and index of the related device information.
 *  \param[in]    targetAddress       NV memory address to write to, must be valid.
 *  \param[in]    sourceAddressPtr    Application pointer to buffer with data to write to nv memory.
 *                                   Must stay valid until job is completed.
 *  \param[in]    Length              Length in bytes to write, must be valid.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_PerformWriteAccess(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_AddressType targetAddress,
    vMem_30_XXspi01_ConstSpiDataPtrType sourceAddressPtr, vMem_30_XXspi01_LengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess()
 *********************************************************************************************************************/
/*! \brief        Builds and transmits the Spi sequence to perform a memory erase access at the external flash device.
 *  \details      -
 *  \param[in]    instanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \param[in]    deviceId            ID and index of the related device information.
 *  \param[in]    targetAddress       NV memory address to be erased, must be valid.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_PerformEraseAccess(
    vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_AddressType targetAddress);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceModifier_Processing()
 *********************************************************************************************************************/
/*! \brief        Processes the write operation for the requested instance.
 *  \details      -
 *  \param[in]    instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceModifier_Processing(
    vMem_30_XXspi01_InstanceIdType instanceId);

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_INSTANCEMODIFIER_H_ */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceModifier.h
 *********************************************************************************************************************/
