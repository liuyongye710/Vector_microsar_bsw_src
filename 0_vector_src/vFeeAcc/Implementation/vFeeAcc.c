/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  vFeeAcc.c
 *        \brief  FEE source file - implementation of API functions
 *
 *      \details  This module provides a Fee-like interface towards the MemIf. It uses the vMemAccM to synchronize
 *                the memory access, with other NV memory clients, such as OTA. After acquiring HW lock the request
 *                gets forwarded directly to the original FEE.
 *********************************************************************************************************************/
#define VFEEACC_IMPLEMENTATION_SOURCE

#include "Std_Types.h"
#include "vFeeAcc.h"
#include "vFeeAcc_PrivateCfg.h"
#include "vFeeAcc_Int.h"
#include "vFeeAcc_ForwardReq.h"
#include "vFeeAcc_PublicStates.h"

#if(VFEEACC_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
#endif


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of vFeeAcc header file */
#if (  (VFEEACC_SW_MAJOR_VERSION != (2u)) \
    || (VFEEACC_SW_MINOR_VERSION != (0u)) )
# error "Vendor specific version numbers of vFeeAcc.c  and vFeeAcc.h are inconsistent"
#endif

/* Check the version of the configuration header file */
/* Version 1.00.xx is still the correct version of the cfg file */
#if (  (VFEEACC_CFG_MAJOR_VERSION != (1u)) \
    || (VFEEACC_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of vFeeAcc.c and vFeeAcc_Cfg.h are inconsistent!"
#endif


#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vFeeAcc_CreateJobStruct()
 *********************************************************************************************************************/
/*!
 * \brief       Create a JobStruct
 * \details     Put individual parameters into a structure; serves as a "constructor". Just for convenience at,
 *              readability of, calling code.
 * \param[in]   BlockNumber   - Job's Requested Block Number (specific to actual FEE implementation)
 *              BlockOffset   - BlockOffset (specific to Request and FEE implementation; maybe any number)
 *              DataBufferPtr - Pointer Job's requested DataBuffer; validity depend on job and FEE implementation
 *              Length        - Length (specific to Request and FEE implementation; maybe any number)
 * \return      A structure containing given values (by Value!)
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 */
VFEEACC_INLINE_FUNC(vFeeAcc_jobType)
vFeeAcc_CreateJobStruct(uint16 BlockNumber, uint16 BlockOffset, vFeeAcc_ReqParamsPtrType DataBufferPtr, uint16 Length);


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vFeeAcc_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_Init(void)
{
  vFeeAcc_InitPublicFsm(&vFeeAcc_ModuleState);
}


/**********************************************************************************************************************
 *  vFeeAcc_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_Read(uint16 BlockNumber, uint16 BlockOffset, vFeeAcc_VarDataPtrType DataBufferPtr, uint16 Length)
{
  const vFeeAcc_RequestDescrType readDescr = {vFeeAcc_ForwardReadReq, VFEEACC_SID_READ};
  return vFeeAcc_SetupJobProc(&vFeeAcc_ModuleState,
                              readDescr,
                              vFeeAcc_CreateJobStruct(BlockNumber,
                                                      BlockOffset,
                                                      /* PRQA S 0315 1 */ /* MD_vFeeAcc_ImplicitConvToVoidPtrInternal */
                                                      DataBufferPtr,
                                                      Length));
}


/**********************************************************************************************************************
 *  vFeeAcc_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_Write(uint16 BlockNumber, vFeeAcc_VarDataPtrType DataBufferPtr)
{
  const vFeeAcc_RequestDescrType writeDescr = {vFeeAcc_ForwardWriteReq, VFEEACC_SID_WRITE};
  return vFeeAcc_SetupJobProc(&vFeeAcc_ModuleState,
                              writeDescr,
                              vFeeAcc_CreateJobStruct(BlockNumber,
                                                      0,
                                                      /* PRQA S 0315 1 */ /* MD_vFeeAcc_ImplicitConvToVoidPtrInternal */
                                                      DataBufferPtr,
                                                      0xFFFFu));
}


/**********************************************************************************************************************
 *  vFeeAcc_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_InvalidateBlock(uint16 BlockNumber)
{
  const vFeeAcc_RequestDescrType invalidateDescr = {vFeeAcc_ForwardInvalidateReq, VFEEACC_SID_INVALIDATE_BLOCK};
  return vFeeAcc_SetupJobProc(
      &vFeeAcc_ModuleState, invalidateDescr, vFeeAcc_CreateJobStruct(BlockNumber, 0, NULL_PTR, 0xFFFFu));
}


/**********************************************************************************************************************
 *  vFeeAcc_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_EraseImmediateBlock(uint16 BlockNumber)
{
  const vFeeAcc_RequestDescrType eraseDescr = {vFeeAcc_ForwardEraseImmReq, VFEEACC_SID_ERASE_IMMEDIATE_BLOCK};
  return vFeeAcc_SetupJobProc(
      &vFeeAcc_ModuleState, eraseDescr, vFeeAcc_CreateJobStruct(BlockNumber, 0, NULL_PTR, 0xFFFFu));
}


/**********************************************************************************************************************
 *  vFeeAcc_CustomFeeRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_CustomFeeRequest(uint16                       BlockNumber,
                         vFeeAcc_CustomRequestCbkType Cbk,
                         uint16                       BlockOffset,
                         uint16                       Length,
                         vFeeAcc_ReqParamsPtrType     customParamsPtr)
{
  uint8 retVal;

#if(VFEEACC_DEV_ERROR_DETECT == STD_ON)
  /* Adhering to that API "pattern" would complicate the code and break existing concepts! */
  if(Cbk == NULL_PTR)
  {
    vFeeAcc_ReportErrorToDet(VFEEACC_SID_CUSTOM_REQUEST, VFEEACC_E_INVALID_FUNCTION_POINTER);
    retVal = E_NOT_OK;
  }
  else
#endif
  {
    vFeeAcc_RequestDescrType reqFuncDescr = {NULL_PTR, VFEEACC_SID_CUSTOM_REQUEST};
    reqFuncDescr.requestFunc = Cbk; /* cannot be set in initializer; limitation of ISO C90 */
    retVal = vFeeAcc_SetupJobProc(
        &vFeeAcc_ModuleState, reqFuncDescr, vFeeAcc_CreateJobStruct(BlockNumber, BlockOffset, customParamsPtr, Length));
  }

  return retVal;
}


/**********************************************************************************************************************
 *  vFeeAcc_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_Cancel(void)
{
  vFeeAcc_CancelProc(&vFeeAcc_ModuleState);
}


/**********************************************************************************************************************
 *  vFeeAcc_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, VFEEACC_CODE)
vFeeAcc_GetStatus(void)
{
  return vFeeAcc_GetStatusProc(&vFeeAcc_ModuleState);
}


/**********************************************************************************************************************
 *  vFeeAcc_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, VFEEACC_CODE)
vFeeAcc_GetJobResult(void)
{
  return vFeeAcc_GetJobResultProc(&vFeeAcc_ModuleState);
}


#if(VFEEACC_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vFeeAcc_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_GetVersionInfo(vFeeAcc_VersionInfoPtrType VersionInfoPtr)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  uint8 errorId = VFEEACC_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
#  if(VFEEACC_DEV_ERROR_DETECT == STD_ON)

  /* ----- VERSION POINTER CHECK ------------------------------------------------------------------------*/
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = VFEEACC_E_INVALID_DATA_POINTER;
  }
  else

#  endif /* VFEEACC_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ------------------------------------------------------------------------------*/

    VersionInfoPtr->vendorID = VFEEACC_VENDOR_ID;
    VersionInfoPtr->moduleID = VFEEACC_MODULE_ID;

    VersionInfoPtr->sw_major_version = VFEEACC_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = VFEEACC_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = VFEEACC_SW_PATCH_VERSION;
  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
#  if(VFEEACC_DEV_ERROR_REPORT == STD_ON)
  if(errorId != VFEEACC_E_NO_ERROR)
  {
    vFeeAcc_ReportErrorToDet(VFEEACC_SID_GET_VERSION_INFO, errorId);
  }
#  else
  VFEEACC_DUMMY_STATEMENT(errorId); 
#  endif
}
#endif /* VFEEACC_VERSION_INFO_API */


/**********************************************************************************************************************
 *  vFeeAcc_SetMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_SetMode(MemIf_ModeType Mode)
{
  VFEEACC_DUMMY_STATEMENT(Mode);
}


/**********************************************************************************************************************
 *  vFeeAcc_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_MainFunction(void)
{
  vFeeAcc_MainProc(&vFeeAcc_ModuleState);
}


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vFeeAcc_CreateJobStruct()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INLINE_FUNC(vFeeAcc_jobType)
vFeeAcc_CreateJobStruct(uint16 BlockNumber, uint16 BlockOffset, vFeeAcc_ReqParamsPtrType DataBufferPtr, uint16 Length)
{
  vFeeAcc_jobType retVal;
  retVal.blockNumber = BlockNumber;
  retVal.blockOffset = BlockOffset;
  retVal.dataPtr = DataBufferPtr;
  retVal.reqLength = Length;

  return retVal;
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_vFeeAcc_ImplicitConvToVoidPtrInternal: Dir 1.1
 Reason:      Addresses internal storage; related to MD_vFeeAcc_VoidPtrToTypePtr.
              It seems to be a false positive: This conversion is well specified; it does not involve implementation
              specific behavior. This message does not have anything to do with Dir-1.1!
              Explicit conversion would cause a QAC message as well - it is unavoidable.
              Nevertheless it might help to spot a risk (see below).
 Risk:        Later usage might cast back to an inappropriate type; both sided might (inadvertently) disagree on type.
              This may cause undefined behavior.
 Prevention:  Both cast directions must match. Review and Component tests are sufficient here.

 MD_vFeeAcc_ImplicitConvToVoidPtrExternal: Dir 1.1
 Reason:      Addresses conversion to void* in a function call (external API).
              Seems to be a false positive: This conversion is well specified; it does not involve implementation
              implementation specific behavior. This message does not have anything to do with Dir-1.1!
              Explicit conversion would cause a QAC message as well - it is unavoidable.
              Nevertheless it might help to spot a risk (see below).
 Risk:        Later usage might cast back to an inappropriate type; both sided might (inadvertently) disagree on type.
              This may cause undefined behavior.
 Prevention:  At caller site, we only use the type, the callee expects (then it is responsible); review.

 MD_vFeeAcc_UnsuedFunction: rule 2.1
 Reason:      Static function in Header file; these functions are intended to be inline'd in files they are used.
              This shall aid compiler doing compile-time optimizations.
 Risk:        None.
 Prevention:  None.

 MD_vFeeAcc_GlobalStaticConst: rule 8.9
  Reason:     Constants are accessed from one function only, but they are generated. Therefore they must be put
              into a separate (generated) file. To aid compilers in compile-time optimizations, they where not
              defined in a separate compilation unit, but in the header.
              Using (typed) constants instead of macros increases type-safety.
  Risk:       None.
  Prevention: None.
 


  MD_vFeeAcc_GlobalStaticGenConst: rule 8.9
  Reason:     Constants are accessed from one function only, but MemMap concept prevents from defining static data
              at block scope; MemMap sections must not be nested. Furthermore it eases testing.
  Risk:       None.
  Prevention: None.

  MD_vFeeAcc_StateFileScopeStatic: rule 8.9
  Reason:     The variable must be declared file scope static because the memory needs to be allocated permanently
              and not temporarily on the stack.
  Risk:       No risk.
  Prevention: No prevention.


  MD_vFeeAcc_CtxParamCouldBeConst: rule 8.13
  Reason:     Functions follow a common (internal API); and by intention they are allowed to modify the parameter
              ctx. Even, if they don't, the parameter must not be const, because pointers of matching types,
              as defined by the internal API, are required.
  Risk:       No risk.
  Prevention  None.

  MD_vFeeAcc_VoidPtrToTypePtr: rule 11.5
  Reason:     Cast from "pointer to void" to "pointer to object type", is necessary due to generic internal
              storage of Data Pointers passed via API, due to generic API vFeeAcc_CustomFeeRequest.
              The cast is done, when forwarding an AUTOSAR-specified request to FEE; in that case the pointer
              gets converted back to its original type. Since this original type is uint8, the conversion is
              always defined and safe.
  Risk:       None.
  Prevention: None.

  MD_vFeeAcc_PointerWithGreaterLifetime: rule 18.6
  Reason:     Set the current user job to a dummy job objects. This dummy job object holds a function pointer and that's
              why this rule is hurt. However, this function object will never be used and the public state is also Idle.
              Hence, there is no problem in the greater lifetime of the pointer.
  Risk:       None.
  Prevention: None.
*/

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc.c
 *********************************************************************************************************************/
