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
/*!        \file  Fls_30_vMemAccM_FlsAccessor.c
 *        \brief  Fls_30_vMemAccM fls accessor source file
 *
 *      \details  This is the implementation of the module Fls_30_vMemAccM_FlsAccessor
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_FLSACCESSOR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Fls_30_vMemAccM_FlsAccessor.h"
#include "Fls_30_vMemAccM_Cfg.h"
#include "Fls_30_vMemAccM_Privates.h"
#if (FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT == STD_ON)
# include "vstdlib.h"
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_LOCAL)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL static
#endif

#if !defined (FLS_30_VMEMACCM_LOCAL_INLINE)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_LOCAL_INLINE LOCAL_INLINE
#endif


#if (FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT == STD_ON)
# define FLS_30_VMEMACCM_START_SEC_VAR_NO_INIT_RAM_BUFFER
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

FLS_30_VMEMACCM_LOCAL uint8 Fls_30_vMemAccM_WriteAlignedBuffer[FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT_BUFFER_SIZE]; /* PRQA S 3218 */ /* MD_Fls_30_vMemAccM_DefinedOutsideBlockScope */

# define FLS_30_VMEMACCM_STOP_SEC_VAR_NO_INIT_RAM_BUFFER
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

# if (FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_PrepareBuffer
 *********************************************************************************************************************/
/*!
 * \brief       Copys as much bytes as possible from user buffer to internal buffer.
 * \details     -
 * \param[in]   addressPtr: user buffer which works as copy source.
 * \param[in]   length: Number of user bytes.
 * \return      number of bytes copied to the buffer.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 */
FUNC(Fls_30_vMemAccM_LengthType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_PrepareBuffer
(
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
);

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_PrepareBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Fls_30_vMemAccM_LengthType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_PrepareBuffer
(
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
)
{
  Fls_30_vMemAccM_LengthType processedLength = (length < FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT_BUFFER_SIZE) ? length : FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT_BUFFER_SIZE;
  /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
  VStdLib_MemCpy(Fls_30_vMemAccM_WriteAlignedBuffer, addressPtr, (VStdLib_CntType)processedLength); /* SBSW_FLS_30_VMEMACCM_INTERNALBUFFER */
  return processedLength;
}
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_RequestAsyncJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Fls_30_vMemAccM_LengthType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_RequestAsyncJob
(
  Fls_30_vMemAccM_AsyncJobType jobType,
  Fls_30_vMemAccM_AddressType address,
  const uint8 *addressPtr,
  Fls_30_vMemAccM_LengthType length
)
{
  Std_ReturnType reqAccepted;
  Fls_30_vMemAccM_LengthType processedLength = length;
  const uint8* ptr = addressPtr;

#if (FLS_30_VMEMACCM_WRITE_RAM_ALIGNMENT == STD_ON)
  if(jobType == Fls_30_vMemAccM_Job_Write)
  {
    processedLength = Fls_30_vMemAccM_FlsAccessor_PrepareBuffer(addressPtr, length);  /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    ptr = (const uint8*)&Fls_30_vMemAccM_WriteAlignedBuffer;
  }
#endif

  switch (jobType)
  {
  case Fls_30_vMemAccM_Job_Write:
  /* PRQA S 0315 1 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */
    reqAccepted = vMemAccM_Write(Fls_30_vMemAccM_TargetAddressAreaId, address, ptr, processedLength); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    break;
  case Fls_30_vMemAccM_Job_Read:
  /* PRQA S 0315 1 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */
    reqAccepted = vMemAccM_Read(Fls_30_vMemAccM_TargetAddressAreaId, address, (uint8 *)ptr, processedLength); /* PRQA S 0311 1 */ /* MD_Fls_30_vMemAccM_ConstCast */ /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    break;
  case Fls_30_vMemAccM_Job_Erase:
    reqAccepted = vMemAccM_Erase(Fls_30_vMemAccM_TargetAddressAreaId, address, processedLength);
    break;
#if(FLS_30_VMEMACCM_BLANK_CHECK_API == STD_ON)
  case Fls_30_vMemAccM_Job_BlankCheck:
    reqAccepted = vMemAccM_IsBlank(Fls_30_vMemAccM_TargetAddressAreaId, address, processedLength);
    break;
#endif
#if(FLS_30_VMEMACCM_READBLANK_API == STD_ON)
  case Fls_30_vMemAccM_Job_ReadBlank:
  /* PRQA S 0315 1 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */
    reqAccepted = vMemAccM_ReadBlank(Fls_30_vMemAccM_TargetAddressAreaId, address, (uint8 *)ptr, processedLength); /* PRQA S 0311 1 */ /* MD_Fls_30_vMemAccM_ConstCast */ /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    break;
#endif
#if(FLS_30_VMEMACCM_COMPARE_API == STD_ON)
  case Fls_30_vMemAccM_Job_Compare:
    /* PRQA S 0315 1 */ /* MD_Fls_30_vMemAccM_VoidPtrTypedPtr */
    reqAccepted = vMemAccM_Compare(Fls_30_vMemAccM_TargetAddressAreaId, address, ptr, processedLength); /* SBSW_FLS_30_VMEMACCM_USERPOINTER */
    break;
#endif
  default: /* Shall never be reached */
    reqAccepted = E_NOT_OK;
    break;
  }

  return (reqAccepted == E_OK) ? processedLength : 0u;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_ConvertJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_ConvertJobResult
(
  vMemAccM_JobResultType resultOfvMemAccMJob
)
{
  MemIf_JobResultType jobResult;

  switch (resultOfvMemAccMJob) {
      case VMEMACCM_JOB_OK:
      /* Intentional fall through */
      case VMEMACCM_READ_CORRECTED_ERRORS:
        jobResult = MEMIF_JOB_OK;
        break;
      case VMEMACCM_JOB_PENDING:
        jobResult = MEMIF_JOB_PENDING;
        break;
      case VMEMACCM_JOB_CANCELED:
        jobResult = MEMIF_JOB_CANCELED;
        break;
      case VMEMACCM_JOB_FAILED:
      /* Intentional fall through */
      case VMEMACCM_READ_UNCORRECTABLE_ERRORS:
        jobResult = MEMIF_JOB_FAILED;
        break;
      default: /* VMEMACCM_MEM_NOT_EQUAL, VMEMACCM_MEM_NOT_BLANK */
        jobResult = MEMIF_BLOCK_INCONSISTENT;
        break;
  }

  return jobResult;
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_GetJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_GetJobResult(void)
{
  vMemAccM_JobResultType resultOfvMemAccMJob = vMemAccM_GetJobResult(Fls_30_vMemAccM_TargetAddressAreaId);

  return Fls_30_vMemAccM_FlsAccessor_ConvertJobResult(resultOfvMemAccMJob);
}

/**********************************************************************************************************************
 * Fls_30_vMemAccM_FlsAccessor_Cancel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_FlsAccessor_Cancel(void)
{
  vMemAccM_Cancel(Fls_30_vMemAccM_TargetAddressAreaId);
}

#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM_FlsAccessor.c
 *********************************************************************************************************************/
