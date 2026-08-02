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
/*!        \file  vMem_30_XXRam_LL.c
 *        \brief  vMem_30_XXRam LowLevel source file
 *
 *      \details  See vMem_30_XXRam_LL.h
 *
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_XXRAM_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXRam_LL.h"
#include "vMem_30_XXRam_IntShared.h"

#include "vstdlib.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXRAM_LOCAL) /* COV_VMEM_30_XXRAM_COMPATIBILITY */
# define VMEM_30_XXRAM_LOCAL static
#endif

#if !defined (VMEM_30_XXRAM_LOCAL_INLINE) /* COV_VMEM_30_XXRAM_COMPATIBILITY */
# define VMEM_30_XXRAM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXRAM_START_SEC_VAR_INIT_32
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_XXRAM_LOCAL vMem_30_XXRam_JobResultType vMem_30_XXRam_currentJobResult = VMEM_JOB_FAILED; /*!< Stores the current job result */

#define VMEM_30_XXRAM_STOP_SEC_VAR_INIT_32
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXRAM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


 /**********************************************************************************************************************
 *  vMem_30_XXRam_LL_GetCurrentDataPointer()
 *********************************************************************************************************************/
 /*!
 * \brief       Based on input address determines the pointer to target data.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           Address, which shall be translated to a pointer to target data.
 * \return      Pointer to target data.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXRAM_LOCAL_INLINE FUNC(vMem_30_XXRam_DataPtrType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LL_GetCurrentDataPointer(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address);

/**********************************************************************************************************************
*  LOCAL FUNCTIONS
*********************************************************************************************************************/

/**********************************************************************************************************************
*  vMem_30_XXRam_LL_GetCurrentDataPointer()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
VMEM_30_XXRAM_LOCAL_INLINE FUNC(vMem_30_XXRam_DataPtrType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LL_GetCurrentDataPointer(
  vMem_30_XXRam_InstanceIdType InstanceId, 
  vMem_30_XXRam_AddressType Address)
{
#if(VMEM_30_XXRAM_USE_INTERNAL_RAMBUFFER_API == STD_ON)
  /* We already know that the passed address is valid. */
  uint32 sectorIndex = vMem_30_XXRam_GetSectorIndex(InstanceId, Address);
  uint32 addressOffset = Address - vMem_30_XXRam_GetStartAddressOfMemSector(sectorIndex);
  uint8* currentBuffer_Ptr = vMem_30_XXRam_GetRamBufferPtrOfMemSector(sectorIndex);
  /* PRQA S 0314 1 */ /* MD_vMem_30_XXRam_ObjectToVoidPtrVStdLib */
  vMem_30_XXRam_DataPtrType DataBufferPtr = (void*)(&currentBuffer_Ptr[addressOffset]);
#else
  vMem_30_XXRam_DataPtrType DataBufferPtr = (void*)Address; /* PRQA S 0326 */ /* MD_vMem_30_XXRam_IntegralTypeToVoidPtrVStdLib */
  VMEM_30_XXRAM_DUMMY_STATEMENT(InstanceId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
  return(DataBufferPtr);
}/* vMem_30_XXRam_LL_GetCurrentDataPointer */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXRam_LLRead
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLRead(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType SourceAddress,
  vMem_30_XXRam_DataPtrType TargetAddressPtr,
  vMem_30_XXRam_LengthType Length)
{
  VStdLib_MemCpy(TargetAddressPtr, (const void*) vMem_30_XXRam_LL_GetCurrentDataPointer(InstanceId, SourceAddress), (VStdLib_CntType)Length);

  vMem_30_XXRam_currentJobResult = VMEM_JOB_OK;
  return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_LLWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLWrite(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_ConstDataPtrType SourceAddressPtr,
  vMem_30_XXRam_LengthType Length)
{
  VStdLib_MemCpy(vMem_30_XXRam_LL_GetCurrentDataPointer(InstanceId, TargetAddress), SourceAddressPtr, (VStdLib_CntType)Length);

  vMem_30_XXRam_currentJobResult = VMEM_JOB_OK;
  return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_LLErase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLErase(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_LengthType Length)
{
  VStdLib_MemSet(vMem_30_XXRam_LL_GetCurrentDataPointer(InstanceId, TargetAddress), VMEM_30_XXRAM_ERASEDVALUE, (VStdLib_CntType)Length);
 
  vMem_30_XXRam_currentJobResult = VMEM_JOB_OK;
  return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_LLIsBlank
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLIsBlank(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_LengthType Length)
{
  boolean isErased = TRUE;
  uint32 idx;

  for (idx = 0; (isErased == TRUE) && (idx < Length); idx++)
  {
    /* PRQA S 0316 1 */ /* MD_vMem_30_XXRam_VoidPtrToObject */
    isErased = (((uint8*)vMem_30_XXRam_LL_GetCurrentDataPointer(InstanceId, TargetAddress))[idx] == VMEM_30_XXRAM_ERASEDVALUE);
  }

  if(isErased == TRUE)
  {
    vMem_30_XXRam_currentJobResult = VMEM_JOB_OK;
  }
  else
  {
    vMem_30_XXRam_currentJobResult = VMEM_MEM_NOT_BLANK;
  }

  return E_OK;
}

/**********************************************************************************************************************
 * vMem_30_XXRam_LLGetJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXRam_JobResultType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLGetJobResult(
    vMem_30_XXRam_InstanceIdType InstanceId)
{
  VMEM_30_XXRAM_DUMMY_STATEMENT(InstanceId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return vMem_30_XXRam_currentJobResult;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_LLProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLProcessing(void)
{
  return;
}

/**********************************************************************************************************************
 *  vMem_30_XXRam_LLInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_LLInit(void)
{
  vMem_30_XXRam_currentJobResult = VMEM_JOB_OK;
  return E_OK;
}

#define VMEM_30_XXRAM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

  MD_vMem_30_XXRam_VoidPtrToObject: rule 11.5
    Reason:     vMem_30_XXRam accesses RAM directly to check for erased value at a specific address. This check requires
                a cast between a void pointer type to an uint8 pointer.
    Risk:       No risk.
    Prevention: No prevention.

  MD_vMem_30_XXRam_IntegralTypeToVoidPtrVStdLib: rule 11.6
    Reason:     vMem_30_XXRam uses the VStdLib functionality to copy values to/set values in RAM. As the VStdLib_MemCpy
                and VStdLib_MemSet expect void pointers for source and destination, a cast between integral type representing
                target address and void pointer is needed.
    Risk:       No risk.
    Prevention: No prevention.

   MD_vMem_30_XXRam_ObjectToVoidPtrVStdLib: rule 11.5
    Reason:     vMem_30_XXRam uses the VStdLib functionality to copy values to/set values in RAM. As the VStdLib_MemCpy
                and VStdLib_MemSet expect void pointers for source and destination, a cast between object type representing
                an RAM buffer and void pointer is needed.
    Risk:       No risk.
    Prevention: No prevention.

*/


/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXRam_LL.c
 *********************************************************************************************************************/
