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
 *         \file  vFeeAcc.h
 *        \brief  Module's API declaration
 *
 *      \details  This module provides a Fee-like interface towards the MemIf. It uses the vMemAccM to synchronize
 *                the memory access, with other NV memory clients, such as OTA. After acquiring HW lock the request
 *                gets forwarded directly to the original FEE.
 *********************************************************************************************************************/

 /*--------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *--------------------------------------------------------------------------------------------------------------------
 *  Version     Date        Author      Change Id      Description
 * -------------------------------------------------------------------------------------------------------------------
 *  1.00.00     2019-03-01  virck      STORY-10831    Initial version
 *  1.00.01     2019-05-27  virbka     STORY-12362    vFeeAcc: Testing Improvements
 *  2.00.00     2020-11-02  virjwa     MWDG-3974      vFeeAcc: Support Fee BUSY_INTERNAL state
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#ifndef VFEEACC_H
#  define VFEEACC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#  include "Std_Types.h"
#  include "vFeeAcc_Types.h"
#  include "vFeeAcc_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#  define VFEEACC_VENDOR_ID (30u)

#  define VFEEACC_AR_RELEASE_MAJOR_VERSION (4u)
#  define VFEEACC_AR_RELEASE_MINOR_VERSION (0u)
#  define VFEEACC_AR_RELEASE_REVISION_VERSION (3u)

#  define VFEEACC_SW_MAJOR_VERSION (2u)
#  define VFEEACC_SW_MINOR_VERSION (0u)
#  define VFEEACC_SW_PATCH_VERSION (0u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#  define VFEEACC_START_SEC_CODE
#  include "MemMap.h"

/**********************************************************************************************************************
 *  vFeeAcc_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes the vFeeAcc module.
 * \details    Initializes internal component parameter in order to prepare module for successful job processing.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-107316
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_Init(void);

/**********************************************************************************************************************
 *  vFeeAcc_Read()
 *********************************************************************************************************************/
/*!
 * \brief      Reads Length bytes of block BlockNumber at offset BlockOffset into the buffer DataBufferPtr.
 * \details    Will be forwarded "as is is" to real FEE, when lock was acquired.
 * \param[in]  BlockNumber
 * \param[in]  BlockOffset - read offset within block
 * \param[in]  DataBufferPtr
 * \param[in]  Length of read job
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_Read(uint16 BlockNumber, uint16 BlockOffset, vFeeAcc_VarDataPtrType DataBufferPtr, uint16 Length);

/**********************************************************************************************************************
 *  vFeeAcc_Write()
 *********************************************************************************************************************/
/*!
 * \brief      Writes the contents of the DataBufferPtr to the block BlockNumber.
 * \details    Will be forwarded "as is is" to real FEE, when lock was acquired.
 * \param[in]  BlockNumber
 * \param[in]  DataBufferPtr
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_Write(uint16 BlockNumber, vFeeAcc_VarDataPtrType DataBufferPtr);

/**********************************************************************************************************************
 *  vFeeAcc_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Invalidates the block BlockNumber.
 * \details    Will be forwarded "as is is" to real FEE, when lock was acquired.
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_InvalidateBlock(uint16 BlockNumber);

/**********************************************************************************************************************
 *  vFeeAcc_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Erases the block BlockNumber.
 * \details    Will be forwarded "as is is" to real FEE, when lock was acquired.
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_EraseImmediateBlock(uint16 BlockNumber);

/**********************************************************************************************************************
 * vFeeAcc_CustomFeeRequest()
 *
 *********************************************************************************************************************/
/*!
 * \brief      Service to forward a custom (non-AUTOSAR) request to FEE.
 * \details    Given Callback is responsible to call FEE, once lock was acquired;
 *             Caller and Callback must agree about valid parameters; this service just forwards them.
 *             Parameters are same as Fee_Read (but different order!) + Callback
 *             Whether they preserve their meaning is up to the Callback function.
 * \param[in]  BlockNumber - will be passed unchanged to cbk
 * \param[in]  Cbk - Callback that actually issues the request
 * \param[in]  BlockOffset - Ideally, the block offset, but actually just an uint16 parameter to be forwarded to cbk
 * \param[in]  Length      - Ideally, the desired length, but actually just another uint16 parameter
 * \param[in]  customParamsPtr - additional parameter data to be handled by cbk
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC(Std_ReturnType, VFEEACC_CODE)
vFeeAcc_CustomFeeRequest(uint16                       BlockNumber,
                         vFeeAcc_CustomRequestCbkType Cbk,
                         uint16                       BlockOffset,
                         uint16                       Length,
                         vFeeAcc_ReqParamsPtrType     customParamsPtr);


/**********************************************************************************************************************
 *  vFeeAcc_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Request to Cancels the ongoing asynchronous operation.
 * \details    Forwards to FEE, only if necessary
 * \pre        -
 * \post       vFee_GetStatus() == MEMIF_IDLE
 * \post       vFee_GetJobResult == MEMIF_JOB_CANCELED
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
  */
FUNC(void, VFEEACC_CODE)
vFeeAcc_Cancel(void);

/**********************************************************************************************************************
 *  vFeeAcc_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Service to return the status.
 * \details    Returns current status of vFeeAcc (which may differ from underlying FEE's status!).
 * \return     Status of FEE module.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, VFEEACC_CODE)
vFeeAcc_GetStatus(void);

/**********************************************************************************************************************
 *  vFeeAcc_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Service to return the job result.
 * \details    Returns most recent request result (or pending); may differ from underlying FEE's result.
 * \return     Job result of FEE module.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, VFEEACC_CODE)
vFeeAcc_GetJobResult(void);

#  if(VFEEACC_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vFeeAcc_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * \brief      Service to get the version information of FEE module.
 * \details    Stores version information, i.e. Module Id, Vendor Id, Vendor specific version numbers,
 *             to structure pointed by VersionInfoPtr.
 * \param[in]  VersionInfoPtr
 * \pre        GetVersionInfo API is enabled via pre-compile switch.
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-107318
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_GetVersionInfo(vFeeAcc_VersionInfoPtrType VersionInfoPtr);
#  endif

/**********************************************************************************************************************
 *  vFeeAcc_SetMode()
 *********************************************************************************************************************/
/*!
 * \brief      Sets the mode (FAST/SLOW).
 * \details    This call will be (silently) ignored; it does nothing.
 * \param[in]  Mode
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_SetMode(MemIf_ModeType Mode);

/**********************************************************************************************************************
 *  vFeeAcc_MainFunction()
 *********************************************************************************************************************/
/*!
 * \brief      Service to handle the requested jobs and the internal management operations.
 * \details    -
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace DSGN-vFeeAcc22811
 */
FUNC(void, VFEEACC_CODE)
vFeeAcc_MainFunction(void);

#  define VFEEACC_STOP_SEC_CODE
#  include "MemMap.h"

#endif /* VFEEACC_H */

/**********************************************************************************************************************
 *  END OF FILE: vFeeAcc.h
 *********************************************************************************************************************/
