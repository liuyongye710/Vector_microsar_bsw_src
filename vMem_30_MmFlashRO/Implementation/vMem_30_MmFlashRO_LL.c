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
/*!        \file  vMem_30_MmFlashRO_LL.c
 *        \brief  vMem_30_MmFlashRO LowLevel source file
 *
 *      \details  See vMem_30_MmFlashRO_LL.h
 *
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_MMFLASHRO_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_MmFlashRO_LL.h"
#include "vMem_30_MmFlashRO_Cfg.h"

#include "vstdlib.h"

#if (VMEM_30_MMFLASHRO_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_30_MMFLASHRO_LOCAL) /* COV_VMEM_30_MMFLASHRO_COMPATIBILITY */
# define VMEM_30_MMFLASHRO_LOCAL static
#endif

#if !defined (VMEM_30_MMFLASHRO_LOCAL_INLINE) /* COV_VMEM_30_MMFLASHRO_COMPATIBILITY */
# define VMEM_30_MMFLASHRO_LOCAL_INLINE LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_MMFLASHRO_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!< Stores the current job result. */
VMEM_30_MMFLASHRO_LOCAL VAR(vMem_30_MmFlashRO_JobResultType, VMEM_30_MMFLASHRO_VAR_NOINIT) vMem_30_MmFlashRO_CurrentJobResult;

#define VMEM_30_MMFLASHRO_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
 
#define VMEM_30_MMFLASHRO_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLRead
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLRead(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType SourceAddress,
  vMem_30_MmFlashRO_DataPtrType TargetAddressPtr,
  vMem_30_MmFlashRO_LengthType Length)
{
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(InstanceId);  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  vMem_30_MmFlashRO_CurrentJobResult = VMEM_JOB_PENDING;
  
  /* PRQA S 0326 1 */ /* MD_vMem_30_MmFlashRO_FlashReadAccess */
  VStdLib_MemCpy(TargetAddressPtr, (vMem_30_MmFlashRO_DataPtrType) SourceAddress, Length);
  
  vMem_30_MmFlashRO_CurrentJobResult = VMEM_JOB_OK;

  return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLWrite(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_ConstDataPtrType SourceAddressPtr,
  vMem_30_MmFlashRO_LengthType Length)
{
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(InstanceId);          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(TargetAddress);       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(SourceAddressPtr);    /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(Length);              /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  
#if (VMEM_30_MMFLASHRO_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(VMEM_30_MMFLASHRO_MODULE_ID, VMEM_30_MMFLASHRO_INSTANCE_ID_DET, VMEM_30_MMFLASHRO_SID_WRITE, VMEM_30_MMFLASHRO_E_WRITECALL);
#endif

  return E_NOT_OK;
}

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLErase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLErase(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length)
{
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(InstanceId);      /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(TargetAddress);   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(Length);          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

#if (VMEM_30_MMFLASHRO_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(VMEM_30_MMFLASHRO_MODULE_ID, VMEM_30_MMFLASHRO_INSTANCE_ID_DET, VMEM_30_MMFLASHRO_SID_ERASE, VMEM_30_MMFLASHRO_E_ERASECALL);
#endif

  return E_NOT_OK;
}

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLIsBlank
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLIsBlank(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length)
{
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(InstanceId);    /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(TargetAddress); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(Length);        /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

#if (VMEM_30_MMFLASHRO_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(VMEM_30_MMFLASHRO_MODULE_ID, VMEM_30_MMFLASHRO_INSTANCE_ID_DET, VMEM_30_MMFLASHRO_SID_IS_BLANK, VMEM_30_MMFLASHRO_E_ISBLANKCALL);
#endif

  return E_NOT_OK;
}

/**********************************************************************************************************************
 * vMem_30_MmFlashRO_LLGetJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_MmFlashRO_JobResultType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLGetJobResult(
    vMem_30_MmFlashRO_InstanceIdType InstanceId)
{
  VMEM_30_MMFLASHRO_DUMMY_STATEMENT(InstanceId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return vMem_30_MmFlashRO_CurrentJobResult;
}

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLProcessing(void)
{
}

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLInit(void)
{
  vMem_30_MmFlashRO_CurrentJobResult = VMEM_JOB_OK;
  return E_OK;
}

#define VMEM_30_MMFLASHRO_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

  MD_vMem_30_MmFlashRO_FlashReadAccess: rule 11.6
    Reason:     vMem_30_MmFlashRO uses the VStdLib functionality to read memory mapped from flash.
                As the VStdLib_MemCpy expect void pointers for source and destination, a cast between integral type
                representing source address and void pointer is needed.
    Risk:       No risk.
    Prevention: No prevention.

*/

/* START_COVERAGE_JUSTIFICATION
Variant coverage:

\ID COV_VMEM_30_MMFLASHRO_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_MmFlashRO_LL.c
 *********************************************************************************************************************/

