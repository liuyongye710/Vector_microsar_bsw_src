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
 *         \file  vFeeAcc_Int.h
 *        \brief  misc. internal definitions and declarations
 *
 *      \details  These definitions are commonly needed by all sub-components' implementations and
 *                their respective headers.
 *********************************************************************************************************************/
#ifndef VFEEACC_INT_H
#  define VFEEACC_INT_H

#  include "Std_Types.h"
#  include "vFeeAcc_Types.h"

#  if !defined(VFEEACC_LOCAL) /* COV_VFEEACC_COMPATIBILITY */
#    define VFEEACC_LOCAL static
#  endif

#  if !defined(VFEEACC_LOCAL_INLINE) /* COV_VFEEACC_COMPATIBILITY */
#    define VFEEACC_LOCAL_INLINE LOCAL_INLINE
#  endif

/* Get the compiler abstraction macros consistent, and save typing */
#  define VFEEACC_INTERNAL_FUNC(rettype) FUNC(rettype, VFEEACC_PRIVATE_CODE) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define VFEEACC_INLINE_FUNC(rettype) VFEEACC_LOCAL_INLINE VFEEACC_INTERNAL_FUNC(rettype) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define VFEEACC_P2INTERNAL_FUNC(rettype, name) P2FUNC(rettype, VFEEACC_PRIVATE_CODE, name) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

typedef P2CONST(struct vFeeAcc_RequestParams_s, AUTOMATIC, VFEEACC_PRIVATE_DATA) vFeeAcc_FeeRequestParams_ConstPtr;
typedef P2VAR(struct vFeeAcc_RequestParams_s, AUTOMATIC, VFEEACC_PRIVATE_DATA) vFeeAcc_FeeRequestParams_VarPtr;

/*! Structure to associate a forwarding function with a Service ID - needed for error reporting only,
 *  But the overhead in memory (and code) is small enough to avoid additional complexity that would be caused
 *  by adding pre-processor switches */
typedef struct vFeeAcc_tagRequestDescrType
{
  vFeeAcc_CustomRequestCbkType requestFunc;
  uint8                        ApiId;
} vFeeAcc_RequestDescrType;

/*! Structure that associates the request (forwarding function) with its parameters (to be forwarded to FEE) */
struct vFeeAcc_RequestParams_s
{
  vFeeAcc_RequestDescrType requestDescr;
  vFeeAcc_FeeRequestParams reqParams;
};

#endif /* VFEEACC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_Int.h
 *********************************************************************************************************************/
