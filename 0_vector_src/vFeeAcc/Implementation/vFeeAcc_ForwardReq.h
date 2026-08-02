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
 *         \file  vFeeAcc_ForwardReq.h
 *        \brief  Declares internal forwarding functions.
 *
 *      \details  These function serve as wrappers around actual FEE services, creating a unified interface for all
 *                requests. They can therefore also be used to distinguish different jobs, if necessary.
 *********************************************************************************************************************/

#ifndef VFEEACC_FORWARD_REQ_H
#define VFEEACC_FORWARD_REQ_H

#include "vFeeAcc_Types.h"
#include "vFeeAcc_Int.h"

#define VFEEACC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vFeeAcc_ForwardReadReq
 *********************************************************************************************************************/
/*!
 * \brief       Forwards read request to Fee.
 * \details     -
 * \param[in]   req - Request parameter structure, by value (copy)
 * \return      Returns whatever FEE request returns
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType) vFeeAcc_ForwardReadReq(vFeeAcc_FeeRequestParams req);

/**********************************************************************************************************************
 *  vFeeAcc_ForwardWriteReq
 *********************************************************************************************************************/
/*!
 * \brief       Forwards write request to Fee.
 * \details     -
 * \param[in]   req - Request parameter structure, by value (copy)
 * \return      Returns whatever FEE request returns
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType) vFeeAcc_ForwardWriteReq(vFeeAcc_FeeRequestParams req);

/**********************************************************************************************************************
 *  vFeeAcc_ForwardInvalidateReq
 *********************************************************************************************************************/
/*!
 * \brief       Forwards invalidate request to Fee.
 * \details     -
 * \param[in]   req - Request parameter structure, by value (copy)
 * \return      Returns whatever FEE request returns
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType) vFeeAcc_ForwardInvalidateReq(vFeeAcc_FeeRequestParams req);

/**********************************************************************************************************************
 *  vFeeAcc_ForwardEraseImmReq
 *********************************************************************************************************************/
/*!
 * \brief       Forwards eraseimm request to Fee.
 * \details     -
 * \param[in]   req - Request parameter structure, by value (copy)
 * \return      Returns whatever FEE request returns
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VFEEACC_INTERNAL_FUNC(Std_ReturnType) vFeeAcc_ForwardEraseImmReq(vFeeAcc_FeeRequestParams req);

#define VFEEACC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VFEEACC_FORWARD_REQ_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc_ForwardReq.h
 *********************************************************************************************************************/
