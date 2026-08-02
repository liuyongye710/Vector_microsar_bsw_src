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
/*!        \file  vMem_30_XXRam_DetChecks.c
 *        \brief  Source file containing Det check functions shared for vMem_30_XXRam.
 *
 *      \details  See vMem_30_XXRam_DetChecks.h
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXRam_DetChecks.h"
#include "vMem_30_XXRam_LL.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXRAM_DETCHECKS_LOCAL) /* COV_VMEM_30_XXRAM_COMPATIBILITY */
# define VMEM_30_XXRAM_DETCHECKS_LOCAL static
#endif

#if !defined (VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE) /* COV_VMEM_30_XXRAM_COMPATIBILITY */
# define VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXRAM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
VAR(uint8, VMEM_30_XXRAM_VAR_ZERO_INIT) vMem_30_XXRam_ModuleInitialized = VMEM_30_XXRAM_UNINIT;
#endif /* (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON) */

#define VMEM_30_XXRAM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXRAM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsSectorIndexValid()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed sector index is lower than the number of configured sectors for the
 *              referenced instance.
 * \details     Does not check whether the passed index is bigger than the lower sector index threshold of the referenced
 *              instance. Therefore, this local function shall only be used, when sector index is computed with
 *              function vMem_30_XXRam_GetSectorIndex.
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   SectorIndex       Index of the sector (batch) which shall be validated.
 * \return      TRUE; if the sector index is valid; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsSectorIndexValid(
  vMem_30_XXRam_InstanceIdType InstanceId, uint32 SectorIndex);

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAligned()
 *********************************************************************************************************************/
/*!
 * \brief       Checks the passed value to be aligned to passed alignment.
 * \details     -
 * \param[in]   Value           Value that shall be verified, e.g. NV memory address.
 * \param[in]   Alignment       Specified alignment, e.g. sector size.
 * \return      TRUE, if the value is aligned; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAligned(
  uint32 Value, uint32 Alignment);

/**********************************************************************************************************************
*  vMem_30_XXRam_GetRemainingSectorBatchLength()
*********************************************************************************************************************/
/*!
* \brief       Calculate the remaining sector batch length, started from given address to end-address of sector batch.
* \details     -
* \param[in]   SectorIndex       Index of the sector (batch) which shall be validated.
* \param[in]   Address           NV memory address
* \return      uint32            calculated remaining sector batch length
* \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
* \context     TASK
* \reentrant   FALSE
* \synchronous TRUE
*/
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(uint32, VMEM_30_XXRAM_CODE) vMem_30_XXRam_GetRemainingSectorBatchLength(
uint32 SectorIndex, vMem_30_XXRam_AddressType Address);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsSectorIndexValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsSectorIndexValid(vMem_30_XXRam_InstanceIdType InstanceId, uint32 SectorIndex)
{

  /* By now it has already been checked, that InstanceId is valid. */
  return (SectorIndex < vMem_30_XXRam_GetMemSectorEndIdxOfvMemInstance(InstanceId)) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_GetRemainingSectorBatchLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(uint32, VMEM_30_XXRAM_CODE) vMem_30_XXRam_GetRemainingSectorBatchLength(
  uint32 SectorIndex, vMem_30_XXRam_AddressType Address)
{
  uint32 remainingSectorBatchLength = (((vMem_30_XXRam_AddressType)vMem_30_XXRam_GetSectorSizeOfMemSector(SectorIndex) * (vMem_30_XXRam_AddressType)vMem_30_XXRam_GetNrOfSectorsOfMemSector(SectorIndex))
    - (Address - vMem_30_XXRam_GetStartAddressOfMemSector(SectorIndex)));
  return (remainingSectorBatchLength);
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXRAM_DETCHECKS_LOCAL_INLINE FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAligned(uint32 Value, uint32 Alignment)
{
  return ((Value % Alignment) == 0u) ? TRUE : FALSE;
}


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsInstanceIdValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsInstanceIdValid(vMem_30_XXRam_InstanceIdType InstanceId)
{
   return (InstanceId < vMem_30_XXRam_GetSizeOfvMemInstance()) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_InstancePendingCheck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InstancePendingCheck(vMem_30_XXRam_InstanceIdType InstanceId)
{
  return (vMem_30_XXRam_LLGetJobResult(InstanceId) == VMEM_JOB_PENDING) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAddressPageAligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAddressPageAligned(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address)
{
  boolean retVal = FALSE;
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  if(vMem_30_XXRam_IsSectorIndexValid(InstanceId, sectorIndex) == TRUE)
  {
    /* StartAddress of SectorBatch is not always aligned to PageSize. Take offset into account for alignment check. */
    retVal = vMem_30_XXRam_IsAligned(Address - vMem_30_XXRam_GetStartAddressOfMemSector(sectorIndex), vMem_30_XXRam_GetPageSizeOfMemSector(sectorIndex));
  }

  return retVal;
}
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsBlankLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsBlankLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length)
{
  /* Note: We already know that the passed address is valid. */
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  return (Length == vMem_30_XXRam_GetPageSizeOfMemSector(sectorIndex)) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAddressSectorAligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAddressSectorAligned(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address)
{
  boolean retVal = FALSE;
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  if(vMem_30_XXRam_IsSectorIndexValid(InstanceId, sectorIndex) == TRUE)
  {
    /* StartAddress of SectorBatch is not always aligned to SectorSize. Take offset into account for alignment check. */
    retVal = vMem_30_XXRam_IsAligned(Address - vMem_30_XXRam_GetStartAddressOfMemSector(sectorIndex), vMem_30_XXRam_GetSectorSizeOfMemSector(sectorIndex));
  }

  return retVal;
}
/**********************************************************************************************************************
 *  vMem_30_XXRam_EraseLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_EraseLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length)
{
  /* Note: We already know that the passed address is valid.
   * If burst is not enabled, generated erase burst size equals sector size. */
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  return ((Length == vMem_30_XXRam_GetSectorSizeOfMemSector(sectorIndex)) ||
                   ((Length == vMem_30_XXRam_GetEraseBurstSizeOfMemSector(sectorIndex)) &&
                    (Length <= vMem_30_XXRam_GetRemainingSectorBatchLength(sectorIndex, Address)) /* PRQA S 3415 */ /* MD_VMEM_30_XXRAM_CORE_13.5_queries */
                   )
         ) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_WriteLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_WriteLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length)
{
  /* Note: We already know that the passed address is valid.
   * If burst is not enabled, generated write burst size equals page size. */
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  return ((Length == vMem_30_XXRam_GetPageSizeOfMemSector(sectorIndex)) ||
                   ((Length == vMem_30_XXRam_GetWriteBurstSizeOfMemSector(sectorIndex)) &&
                    (Length <= vMem_30_XXRam_GetRemainingSectorBatchLength(sectorIndex, Address)) /* PRQA S 3415 */ /* MD_VMEM_30_XXRAM_CORE_13.5_queries */
                   )
         ) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_ReadLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_ReadLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length)
{
  /* We already know that the passed address is valid. */
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  /* The passed Length has to point to the same sector batch as the address itself. */
  return (Length <= vMem_30_XXRam_GetRemainingSectorBatchLength(sectorIndex, Address)) ? TRUE : FALSE;

}
/**********************************************************************************************************************
 *  vMem_30_XXRam_ReadAddressCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_ReadAddressCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address)
{
  return vMem_30_XXRam_IsSectorIndexValid(InstanceId, vMem_30_XXRam_GetSectorIndex(InstanceId, Address));
}
/**********************************************************************************************************************
 *  vMem_30_XXRam_InitPendingCheck()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InitPendingCheck(void)
{
  boolean retVal = TRUE;
  uint32 instanceIndex;
  if(vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_INIT)
  {
    for(instanceIndex = 0; instanceIndex < vMem_30_XXRam_GetSizeOfvMemInstanceOfPCConfig(); instanceIndex++)
    {
      if(vMem_30_XXRam_InstancePendingCheck(instanceIndex) == TRUE)
      {
        retVal = FALSE;
        break;
      }
    }
  }
  return retVal;
}

#endif /* (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON) */


#define VMEM_30_XXRAM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXRam_DetChecks.c
 *********************************************************************************************************************/
