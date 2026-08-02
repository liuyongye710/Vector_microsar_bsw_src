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
/*!        \file  vMem_30_Blocking.c
 *        \brief  vMem_30_Blocking source file
 *
 *      \details  See vMem_30_Blocking.h
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

#define VMEM_30_BLOCKING_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "vMem_30_Blocking.h"
#include "vMem_30_Blocking_PrivateCfg.h"
#include "vMem_30_Blocking_HwRequests.h"
#include "vMem_30_Blocking_Int.h"

#if (VMEM_30_BLOCKING_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif 

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of vMem header file */
#if (  (VMEM_30_BLOCKING_SW_MAJOR_VERSION != (3u)) \
    || (VMEM_30_BLOCKING_SW_MINOR_VERSION != (0u)) \
    || (VMEM_30_BLOCKING_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of vMem_30_Blocking.c and vMem_30_Blocking.h are inconsistent"
#endif

/* Check the version of vMemAccM_vMemApi file */
#if (  (VMEMACCM_VMEMAPI_MAJOR_VERSION != (4u)) \
    || (VMEMACCM_VMEMAPI_MINOR_VERSION != (0u)) )
# error "Version numbers of vMem.c and vMemAccM_vMemApi.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_BLOCKING_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_BLOCKING_LOCAL VAR(vMem_30_Blocking_HwLockParamsRefType, VMEM_30_BLOCKING_VAR) vMem_30_Blocking_CurrentLockOwner = NULL_PTR;

#define VMEM_30_BLOCKING_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Unique identifier of the vMem based on the below identifiers.
 * VMEMACCM_VMEMAPI_MAJOR_VERSION -> vMemAccM to vMem interface version
 * VMEM_30_BLOCKING_DRIVER_ID -> Generated specific vMem identifier (20 bits). */
#define VMEM_30_BLOCKING_UNIQUEID (uint32)(0u | (((uint32)VMEMACCM_VMEMAPI_MAJOR_VERSION) << 24u) | VMEM_30_BLOCKING_DRIVER_ID)

#define VMEM_30_BLOCKING_EXTENDED_FUNCTION_COUNT    1u
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VMEM_30_BLOCKING_START_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! The vMem footer will be placed at the end of the vMem (after the code, data, etc.) and marks the end of the driver. */
VMEM_30_BLOCKING_LOCAL CONST(uint32, AUTOMATIC) vMem_30_Blocking_Footer = VMEM_30_BLOCKING_UNIQUEID;

#define VMEM_30_BLOCKING_STOP_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VMEM_30_BLOCKING_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VMEM_30_BLOCKING_LOCAL CONST(vMemAccM_vMemHwSpecificFuncPtr, VMEM_30_BLOCKING_APPL_CONST) vMem_30_Blocking_HwSpecificFunctions[VMEM_30_BLOCKING_EXTENDED_FUNCTION_COUNT] =
{
  &vMem_30_Blocking_AcquireLock
};

#define VMEM_30_BLOCKING_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VMEM_30_BLOCKING_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Global API pointer table definition.
 * Provides the function entry points to vMemAccM */
CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_Blocking_FunctionPointerTable = {
  VMEM_30_BLOCKING_UNIQUEID,
  &vMem_30_Blocking_FunctionPointerTable.Header,
  &vMem_30_Blocking_Footer,
  {
    VMEM_30_BLOCKING_EXTENDED_FUNCTION_COUNT,
    vMem_30_Blocking_HwSpecificFunctions
  },
  &vMem_30_Blocking_Init,
  &vMem_30_Blocking_Read,
  &vMem_30_Blocking_Write,
  &vMem_30_Blocking_Erase,
  &vMem_30_Blocking_IsBlank,
  &vMem_30_Blocking_GetJobResult,
  &vMem_30_Blocking_MainFunction
};

#define VMEM_30_BLOCKING_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define VMEM_30_BLOCKING_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_Blocking_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Read(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType SourceAddress,
  vMem_30_Blocking_DataPtrType TargetAddressPtr, /* PRQA S 3673 */ /* MD_vMem_30_Blocking_Msg3673 */
  vMem_30_Blocking_LengthType Length
  )
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(SourceAddress);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(TargetAddressPtr);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(Length);
  
  return E_NOT_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Blocking_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Write(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_ConstDataPtrType SourceAddressPtr,
  vMem_30_Blocking_LengthType Length
  )
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(TargetAddress);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(SourceAddressPtr);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(Length);

  return E_NOT_OK;
}


/**********************************************************************************************************************
 *  vMem_30_Blocking_Erase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Erase(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_LengthType Length
  )
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(TargetAddress);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(Length);

  return E_NOT_OK;
}


/**********************************************************************************************************************
 *  vMem_30_Blocking_IsBlank()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_IsBlank(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_LengthType Length
  )
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(TargetAddress);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(Length);

  return E_NOT_OK;
} 

/**********************************************************************************************************************
 *  vMem_30_Blocking_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_Blocking_JobResultType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_GetJobResult(
  vMem_30_Blocking_InstanceIdType InstanceId)
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);
  return (vMem_30_Blocking_CurrentLockOwner == NULL_PTR) ?  VMEM_JOB_OK : VMEM_JOB_PENDING;
}

/***********************************************************************************************************************
 *  vMem_30_Blocking_AcquireLock
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_AcquireLock(
    vMemAccM_vMemInstanceIdType InstanceId, vMemAccM_vMemDataPtrType reqSpecificData, uint32 sizeOfData)
{
  uint8 retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal  */
  uint8 errorResult = VMEM_30_BLOCKING_E_NO_ERROR;
  
#if (VMEM_30_BLOCKING_DEV_ERROR_DETECT == STD_ON)
  if(reqSpecificData == NULL_PTR) 
  {
    errorResult = VMEM_30_BLOCKING_E_PARAM_POINTER;
  }
  else if(sizeOfData != sizeof(struct vMem_30_Blocking_HwLockParams_s))
  {
    errorResult = VMEM_30_BLOCKING_E_PARAM_LENGTH;
  }
  else if(vMem_30_Blocking_CurrentLockOwner != NULL_PTR)
  {
    errorResult = VMEM_30_BLOCKING_E_PENDING;
  }
  else
#endif
  {
    vMem_30_Blocking_CurrentLockOwner = (vMem_30_Blocking_HwLockParamsRefType)reqSpecificData; /* PRQA S 0316 */ /* MD_vMem_30_Blocking_Msg0316 */
    vMem_30_Blocking_CurrentLockOwner->LockState = VMEM_30_BLOCKING_LOCKED;
    
    retVal = E_OK;
  }

#if(VMEM_30_BLOCKING_DEV_ERROR_REPORT == STD_ON)
  if(errorResult != VMEM_30_BLOCKING_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_BLOCKING_MODULE_ID, VMEM_30_BLOCKING_INSTANCE_ID_DET, VMEM_30_BLOCKING_SID_ACQUIRE_LOCK, errorResult);
  }
#else
  VMEM_30_BLOCKING_DUMMY_STATEMENT(errorResult);
  VMEM_30_BLOCKING_DUMMY_STATEMENT(sizeOfData);
#endif

  VMEM_30_BLOCKING_DUMMY_STATEMENT(InstanceId);

  return retVal;
}

/***********************************************************************************************************************
 *  vMem_30_Blocking_ReleaseLock
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_ReleaseLock(vMem_30_Blocking_HwLockParamsRefType lockParams)
{
  uint8 retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal  */
  uint8 errorResult = VMEM_30_BLOCKING_E_NO_ERROR;

#if(VMEM_30_BLOCKING_DEV_ERROR_DETECT == STD_ON)
  if(lockParams == NULL_PTR)
  {
    errorResult = VMEM_30_BLOCKING_E_PARAM_POINTER;
  }
  else if(lockParams != vMem_30_Blocking_CurrentLockOwner)
  {
    errorResult = VMEM_30_BLOCKING_E_NOT_LOCK_OWNER;
  }
  else
#endif
  {
    vMem_30_Blocking_CurrentLockOwner = NULL_PTR;
    lockParams->LockState = VMEM_30_BLOCKING_UNLOCKED;
    
    retVal = E_OK;
  }

#if(VMEM_30_BLOCKING_DEV_ERROR_REPORT == STD_ON)
  if (errorResult != VMEM_30_BLOCKING_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_BLOCKING_MODULE_ID, VMEM_30_BLOCKING_INSTANCE_ID_DET, VMEM_30_BLOCKING_SID_RELEASE_LOCK, errorResult);
  }
#else 
  VMEM_30_BLOCKING_DUMMY_STATEMENT(errorResult);
#endif

  return retVal;
}

#if (VMEM_30_BLOCKING_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Blocking_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_GetVersionInfo(vMem_30_Blocking_VersionInfoPtrType VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_BLOCKING_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (VMEM_30_BLOCKING_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = VMEM_30_BLOCKING_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID = (VMEM_30_BLOCKING_VENDOR_ID);
    VersionInfo->moduleID = (VMEM_30_BLOCKING_MODULE_ID); 
    VersionInfo->sw_major_version = (VMEM_30_BLOCKING_SW_MAJOR_VERSION); 
    VersionInfo->sw_minor_version = (VMEM_30_BLOCKING_SW_MINOR_VERSION); 
    VersionInfo->sw_patch_version = (VMEM_30_BLOCKING_SW_PATCH_VERSION); 
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VMEM_30_BLOCKING_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_BLOCKING_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_BLOCKING_MODULE_ID, VMEM_30_BLOCKING_INSTANCE_ID_DET, VMEM_30_BLOCKING_SID_GET_VERSION_INFO, errorId);
  }
# else
  VMEM_30_BLOCKING_DUMMY_STATEMENT(errorId);
# endif
}
#endif


/**********************************************************************************************************************
 *  vMem_30_Blocking_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_MainFunction(void)
{

} 

/**********************************************************************************************************************
 *  vMem_30_Blocking_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Init(vMem_30_Blocking_ConfigPtrType ConfigPtr)
{
  VMEM_30_BLOCKING_DUMMY_STATEMENT(ConfigPtr);
} 

#define VMEM_30_BLOCKING_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
  MD_vMem_30_Blocking_Msg3673: rule 8.13
  Reason:     API is defined by vMemAccM; usually, the pointee will be changed, therefore it is non-const.
              Only this component does not modify data.
  Risk:       None.
  Prevention: None.

  MD_vMem_30_Blocking_Msg0316: rule 11.5
  Reason:     Cast from "pointer to void" to "pointer to object type", is necessary due to the generic API.
              It shall be possible to cover different use cases via this API, which includes very different parameter sets.
  Risk:       User passes unexpected type; conversion and dereferencing might lead to undefined behavior.
  Prevention: User of this specific service (that is a client of vMemAccM) has to ensure that expected type and
              length arguments are passed (TechRef). Length parameter is being checked for correct (exact) size.
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Blocking.c
 *********************************************************************************************************************/
