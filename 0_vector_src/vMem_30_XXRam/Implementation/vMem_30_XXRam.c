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
/*!        \file  vMem_30_XXRam.c
 *        \brief  vMem_30_XXRam source file
 *
 *      \details  See vMem_30_XXRam.h
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

#define VMEM_30_XXRAM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXRam.h"
#include "vMem_30_XXRam_Int.h"
#include "vMem_30_XXRam_LL.h"
#include "vMem_30_XXRam_DetChecks.h"

#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of vMem_30_XXRam header file */
#if (  (VMEM_30_XXRAM_SW_MAJOR_VERSION != (2u)) \
    || (VMEM_30_XXRAM_SW_MINOR_VERSION != (1u)) \
    || (VMEM_30_XXRAM_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of vMem_30_XXRam.c and vMem_30_XXRam.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (VMEM_30_XXRAM_CFG_COMP_MAJOR_VERSION != (2u)) \
    || (VMEM_30_XXRAM_CFG_COMP_MINOR_VERSION != (1u)) )
# error "Version numbers of vMem_30_XXRam.c and vMem_30_XXRam_Cfg.h are inconsistent!"
#endif

/* Check the version of vMemAccM_vMemApi file */
#if (  (VMEMACCM_VMEMAPI_MAJOR_VERSION != (4u)) \
    || (VMEMACCM_VMEMAPI_MINOR_VERSION != (0u)) )
# error "Version numbers of vMem_30_XXRam.c and vMemAccM_vMemApi.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! The lower 20-bits of the generated identifier is the used as the unique driver identifier. */
# define VMEM_30_XXRAM_ID_MASK_VALUE  0x000FFFFFuL

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Unique identifier of the vMem based on the below identifiers.
 * VMEM_30_XXRAM_DRIVER_ID -> Unique vMem driver identifier. This value is generated.
 * VMEMACCM_VMEMAPI_MAJOR_VERSION -> vMemAccM to vMem interface version. */

# define VMEM_30_XXRAM_UNIQUEID (uint32)(0u | (((uint32)VMEMACCM_VMEMAPI_MAJOR_VERSION) << 24u) | (VMEM_30_XXRAM_DRIVER_ID & VMEM_30_XXRAM_ID_MASK_VALUE))


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VMEM_30_XXRAM_START_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! The vMem footer will be placed at the end of the vMem (after the code, data, etc.) and marks the end of the driver. */
CONST(uint32, AUTOMATIC) vMem_30_XXRam_Footer = VMEM_30_XXRAM_UNIQUEID;

#define VMEM_30_XXRAM_STOP_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VMEM_30_XXRAM_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table definition.
 * The vMem_30_XXRam hardware specific extended functionality is defined within LowLevel. */
CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_XXRam_FunctionPointerTable = {
  VMEM_30_XXRAM_UNIQUEID,
  &vMem_30_XXRam_FunctionPointerTable.Header,
  &vMem_30_XXRam_Footer,
  {
    VMEM_30_XXRAM_EXTENDED_FUNCTION_COUNT,
    VMEM_30_XXRAM_EXTENDED_FUNCTION_TABLE
  },
  &vMem_30_XXRam_Init,
  &vMem_30_XXRam_Read,
  &vMem_30_XXRam_Write,
  &vMem_30_XXRam_Erase,
  &vMem_30_XXRam_IsBlank,
  &vMem_30_XXRam_GetJobResult,
  &vMem_30_XXRam_MainFunction
};

#define VMEM_30_XXRAM_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define VMEM_30_XXRAM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  vMem_30_XXRam_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_Read(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType SourceAddress,
  vMem_30_XXRam_DataPtrType TargetAddressPtr,
  vMem_30_XXRam_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else if (vMem_30_XXRam_IsInstanceIdValid(InstanceId) == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXRam_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXRAM_E_PENDING;
  }
  else if (TargetAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_POINTER;
  }
  else if(vMem_30_XXRam_ReadAddressCheck(InstanceId, SourceAddress) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXRam_ReadLengthCheck(InstanceId, SourceAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXRam_LLRead(InstanceId, SourceAddress, TargetAddressPtr, Length); /* SBSW_vMem_30_XXRam_UserPointer */
  }
  
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_READ, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXRam_Read() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vMem_30_XXRam_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_Write(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_ConstDataPtrType SourceAddressPtr,
  vMem_30_XXRam_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else if (vMem_30_XXRam_IsInstanceIdValid(InstanceId) == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXRam_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXRAM_E_PENDING;
  }
  else if (SourceAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_POINTER;
  }
  else if(vMem_30_XXRam_IsAddressPageAligned(InstanceId, TargetAddress) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXRam_WriteLengthCheck(InstanceId, TargetAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXRam_LLWrite(InstanceId, TargetAddress, SourceAddressPtr, Length); /* SBSW_vMem_30_XXRam_UserPointer */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_WRITE, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXRam_Write() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  vMem_30_XXRam_Erase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_Erase(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else if (vMem_30_XXRam_IsInstanceIdValid(InstanceId) == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXRam_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXRAM_E_PENDING;
  }
  else if(vMem_30_XXRam_IsAddressSectorAligned(InstanceId, TargetAddress) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXRam_EraseLengthCheck(InstanceId, TargetAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXRam_LLErase(InstanceId, TargetAddress, Length);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_ERASE, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXRam_Erase() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsBlank()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsBlank(
  vMem_30_XXRam_InstanceIdType InstanceId,
  vMem_30_XXRam_AddressType TargetAddress,
  vMem_30_XXRam_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else if (vMem_30_XXRam_IsInstanceIdValid(InstanceId) == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXRam_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXRAM_E_PENDING;
  }
  else if(vMem_30_XXRam_IsAddressPageAligned(InstanceId, TargetAddress) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXRam_IsBlankLengthCheck(InstanceId, TargetAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXRAM_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXRam_LLIsBlank(InstanceId, TargetAddress, Length);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_IS_BLANK, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXRam_IsBlank() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vMem_30_XXRam_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vMem_30_XXRam_JobResultType, VMEM_30_XXRAM_CODE) vMem_30_XXRam_GetJobResult(
  vMem_30_XXRam_InstanceIdType InstanceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  vMem_30_XXRam_JobResultType jobResult = VMEM_JOB_FAILED; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else if (vMem_30_XXRam_IsInstanceIdValid(InstanceId) == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_INSTANCE_ID;
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
    jobResult = vMem_30_XXRam_LLGetJobResult(InstanceId);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_GET_JOB_RESULT, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return jobResult;
} /* vMem_30_XXRam_GetJobResult() */



/**********************************************************************************************************************
 *  vMem_30_XXRam_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  vMem_30_XXRam_ModuleInitialized = VMEM_30_XXRAM_UNINIT;
#endif
}  /* vMem_30_XXRam_InitMemory() */


/**********************************************************************************************************************
 *  vMem_30_XXRam_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_Init(vMem_30_XXRam_ConfigPtrType ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_XXRam_InitPendingCheck() == FALSE)
  {
    errorId = VMEM_30_XXRAM_E_PENDING;
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
  /* Do not use the ConfigPtr, simply ignore the parameter (vMem_30_XXRam is not post build capable yet). */
    if (vMem_30_XXRam_LLInit() == E_NOT_OK)
    {
      errorId = VMEM_30_XXRAM_E_INITIALIZATION_FAILED;
    }
  }
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  if (errorId == VMEM_30_XXRAM_E_NO_ERROR)
  {
    vMem_30_XXRam_ModuleInitialized = VMEM_30_XXRAM_INIT;
  }
#endif
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  else
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_INIT, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif
  VMEM_30_XXRAM_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
} /* vMem_30_XXRam_Init() */


/***********************************************************************************************************************
 *  vMem_30_XXRam_MainFunction
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXRam_ModuleInitialized == VMEM_30_XXRAM_UNINIT)
  {
    errorId = VMEM_30_XXRAM_E_UNINIT;
  }
  else
#endif
  {
    vMem_30_XXRam_LLProcessing();
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_MAIN_FUNCTION, errorId);
  }
#else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* vMem_30_XXRam_MainFunction */


#if (VMEM_30_XXRAM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXRam_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_XXRAM_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXRAM_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = VMEM_30_XXRAM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID = (VMEM_30_XXRAM_VENDOR_ID); /* SBSW_vMem_30_XXRam_UserPointer */
    VersionInfo->moduleID = (VMEM_30_XXRAM_MODULE_ID); /* SBSW_vMem_30_XXRam_UserPointer */
    VersionInfo->sw_major_version = (VMEM_30_XXRAM_SW_MAJOR_VERSION); /* SBSW_vMem_30_XXRam_UserPointer */
    VersionInfo->sw_minor_version = (VMEM_30_XXRAM_SW_MINOR_VERSION); /* SBSW_vMem_30_XXRam_UserPointer */
    VersionInfo->sw_patch_version = (VMEM_30_XXRAM_SW_PATCH_VERSION); /* SBSW_vMem_30_XXRam_UserPointer */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VMEM_30_XXRAM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXRAM_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXRAM_MODULE_ID, VMEM_30_XXRAM_INSTANCE_ID_DET, VMEM_30_XXRAM_SID_GET_VERSION_INFO, errorId);
  }
# else
  VMEM_30_XXRAM_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
# endif
}
#endif


#define VMEM_30_XXRAM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Module specific MISRA deviations:

MD_CRC_2.1_StaticFunctionNotUsed:
    Reason: This inline functions are defined as a utility functionality and shall be accessible by each translation
            unit of the component. In some cases this functionality might not be used. This is not a problem as the
            compiler will optimize this code away in this case.
    Risk: No risk.
    Prevention: A compile switch could be introduced.
    
MD_VMEM_30_XXRAM_CORE_13.5_queries:
     Reason: Functions at right hand of || or && are defined to have no side-effects. Therefore it is intended to omit
             unnecessary calls. Avoiding this deviation would degrade code structure without benefits (nesting of
             IF-clauses).
     Risk: A function HAS side effects, leading to unexpected behavior, if call is omitted.
     Prevention: Review; make sure, that these functions do not change any global value,
                 and that they do not access "volatile" values.

*/


/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_vMem_30_XXRam_UserPointer
 \DESCRIPTION Pointer write access or function call: vMem_30_XXRam gets a pointer to write information to. vMem_30_XXRam expects the pointer to be typed
              correctly and will use it, if it is != NULL_PTR. vMem_30_XXRam writes to the pointer or forwards it to another component internal function.
 \COUNTERMEASURE \R vMem_30_XXRam checks the passed pointer to be != NULL_PTR. User is responsible for pointer correctness.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_XXRAM_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

\ID COV_VMEM_30_XXRAM_UTILITYCODE_UNUSED
 \ACCEPT X
 \REASON vMem_core is the hardware independent base (and template) for all hardware dependent versions. It provides a
         header file vMem_IntShared.h with shared utility code that may be used from all subcomponents of vMem. The
         core variant uses this code only for development error checks and therefore is not used in some configuration
         variants at all.

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXRam.c
 *********************************************************************************************************************/
