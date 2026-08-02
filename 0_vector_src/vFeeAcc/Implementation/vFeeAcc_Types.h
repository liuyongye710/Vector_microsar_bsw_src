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
 *         \file  vFeeAcc_Types.h
 *        \brief  Module's public type definitions and macros
 *
 *      \details  -
 *********************************************************************************************************************/
#ifndef VFEEACC_TYPES_H
#  define VFEEACC_TYPES_H

#  include "Std_Types.h"
#  include "MemIf_Types.h"

#  define VFEEACC_MODULE_ID (0xFFu) /*!< AUTOSAR Module ID; this is a CDD, not a FEE! */
#  define VFEEACC_INSTANCE_ID (0u)

/**** Error Codes in Development-Mode ******************************************************************************/
/* AUTOSAR 4 development error codes */
#  define VFEEACC_E_NO_ERROR (0x00u)
#  define VFEEACC_E_UNINIT (0x01u)
#  define VFEEACC_E_INVALID_DATA_POINTER (0x04u)
#  define VFEEACC_E_BUSY (0x06u)
#  define VFEEACC_E_INVALID_FUNCTION_POINTER (0x80u)

/**** Fee Service Identification ************************************************************************************/
#  define VFEEACC_SID_INIT (0x00u)
#  define VFEEACC_SID_SET_MODE (0x01u)
#  define VFEEACC_SID_READ (0x02u)
#  define VFEEACC_SID_WRITE (0x03u)
#  define VFEEACC_SID_CANCEL (0x04u)
#  define VFEEACC_SID_GET_STATUS (0x05u)
#  define VFEEACC_SID_GET_JOB_RESULT (0x06u)
#  define VFEEACC_SID_INVALIDATE_BLOCK (0x07u)
#  define VFEEACC_SID_GET_VERSION_INFO (0x08u)
#  define VFEEACC_SID_ERASE_IMMEDIATE_BLOCK (0x09u)
#  define VFEEACC_SID_JOB_END_NOTIFICATION (0x10u)
#  define VFEEACC_SID_JOB_ERROR_NOTIFICATION (0x11u)
#  define VFEEACC_SID_MAINFUNCTION (0x12u)
#  define VFEEACC_SID_CUSTOM_REQUEST (0x80u)

typedef P2VAR(Std_VersionInfoType, AUTOMATIC, VFEEACC_APPL_DATA) vFeeAcc_VersionInfoPtrType;
typedef P2VAR(uint8, AUTOMATIC, VFEEACC_APPL_DATA) vFeeAcc_VarDataPtrType;
typedef P2VAR(void, AUTOMATIC, VFEEACC_APPL_DATA) vFeeAcc_ReqParamsPtrType;

/*! Structure to gather parameters to be passed to FEE. A particular request might not need all of them;
    Non-standard requests, with additional parameters, shall pass them via data Ptr */
typedef struct vFeeAcc_FeeRequestParams_s
{
  vFeeAcc_ReqParamsPtrType dataPtr;
  uint16                   blockNumber;
  uint16                   blockOffset;
  uint16                   reqLength;
} vFeeAcc_FeeRequestParams;

/**********************************************************************************************************************
 *  vFeeAcc_CustomRequestCbkType()
 *********************************************************************************************************************/
/*!
 * \brief       Function pointer type describing a request forwarder to underlying FEE.
 * \details     For standard AUTOSAR requests, they are implemented in this module; a user may provide an own callback,
 *              and pass it to vFeeAcc_CustomRequest.
 * \param[in]   req - Request parameter structure, by value (copy)
 * \return      Returns whatever FEE request returns
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
typedef P2FUNC(Std_ReturnType, VFEEACC_APPL_CODE, vFeeAcc_CustomRequestCbkType)(vFeeAcc_FeeRequestParams customParams);

#endif /* VFEEACC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_Types.h
 *********************************************************************************************************************/
