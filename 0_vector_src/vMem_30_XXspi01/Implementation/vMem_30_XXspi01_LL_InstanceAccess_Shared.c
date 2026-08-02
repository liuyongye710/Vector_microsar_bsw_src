/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_InstanceAccess_Shared.c
 *        \brief  -
 *      \details  -
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_LL_INSTANCEACCESS_SHARED

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_InstanceAccess_Shared.h"

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(
    vMem_30_XXspi01_DeviceIdType deviceId, vMem_30_XXspi01_ConstSpiDataPtrType registerBuffer)
{
  /* #10 In the default case, the devices doesn't have dummy cycles configured for reading a register.
   * In this case the register content is in the first received byte of the buffer. */
  vMem_30_XXspi01_SpiDataType registerContent = registerBuffer[0];

  vMem_30_XXspi01_ReadRegisterDummyCyclesOfvMemDeviceConfigType dummyCycles = vMem_30_XXspi01_LL_CfgDevice_GetReadRegisterDummyCycles(deviceId);

  /* #20 If the given device has one ore more dummy cycles configured, the register content is reconstructed from the given buffer. */
  if (dummyCycles > 0u)
  {
    /* The register content could be split over two bytes. The content of the first affected byte is shifted left by the amount of dummy cycles.
     * The lower part of the register content that is contained in the succeeding byte of the buffer is shifted right by the amount between the
     * dummy cycles and the next upper byte boundary. Both values are merged to reconstruct the original register value. */
    registerContent = (registerBuffer[dummyCycles >> 3u] << (dummyCycles % 8u))
        | (registerBuffer[(dummyCycles >> 3u) + 1u] >> (8u - (dummyCycles % 8u)));
  }

  return registerContent;
} /* vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent */

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceAccess_Shared.c
 *********************************************************************************************************************/
