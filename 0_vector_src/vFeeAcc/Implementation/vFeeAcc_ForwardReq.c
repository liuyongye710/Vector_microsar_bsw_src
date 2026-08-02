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
 *         \file  vFeeAcc_ForwardReq.c
 *        \brief  Implements the unified forwarding wrappers.
 *
 *      \details  -
 *********************************************************************************************************************/
#define VFEEACC_FORWARD_REQ_SOURCE

#include "vFeeAcc_ForwardReq.h"
#include "vFeeAcc_FeeCfg.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_ForwardReadReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_ForwardReadReq(vFeeAcc_FeeRequestParams req)
{
  return VFEEACC_Fee_Read(req.blockNumber,
                          req.blockOffset,
                          (vFeeAcc_VarDataPtrType)(req.dataPtr), /* PRQA S 0316 */ /* MD_vFeeAcc_VoidPtrToTypePtr */
                          req.reqLength);
}

/**********************************************************************************************************************
 *  vFeeAcc_ForwardWriteReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_ForwardWriteReq(vFeeAcc_FeeRequestParams req)
{
  /* PRQA S 0316 1 */ /* MD_vFeeAcc_VoidPtrToTypePtr */
  return VFEEACC_Fee_Write(req.blockNumber, (vFeeAcc_VarDataPtrType)(req.dataPtr));
}

/**********************************************************************************************************************
 *  vFeeAcc_ForwardInvalidateReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_ForwardInvalidateReq(vFeeAcc_FeeRequestParams req)
{
  return VFEEACC_Fee_InvalidateBlock(req.blockNumber);
}

/**********************************************************************************************************************
 *  vFeeAcc_ForwardEraseImmReq
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType)
vFeeAcc_ForwardEraseImmReq(vFeeAcc_FeeRequestParams req)
{
  return VFEEACC_Fee_EraseImmediateBlock(req.blockNumber);
}

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_ForwardReq.c
 *********************************************************************************************************************/
