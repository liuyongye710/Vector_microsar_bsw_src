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
/*       \file    vFotaH_Cbk.h
 *       \brief   vFotaH callback header file
 *
 *       \details -
 *
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to vFotaH.h.
 **********************************************************************************************************************/

#ifndef VFOTAH_CBK_H
#define VFOTAH_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vFotaH.h"
#include "vSwUpdM.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  vFotaH_vSwUpdMConfirmation()
 *********************************************************************************************************************/
/*! \brief        Confirms the last request to vSwUpdM.
 *  \details      This API is always called after asynchronous request in vSwUpdM.
 *  \param[in]    ConfirmedServiceId  The vSwUpdM service id for which the confirmation occurred.
 *  \param[in]    Result              Indicates if the request was successful.
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \pre          -
 *  \ingroup      callback
 *********************************************************************************************************************/
extern FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMConfirmation(
  vSwUpdM_ServiceIdType ConfirmedServiceId,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vFotaH_vSwUpdMCopyStreamData()
 *********************************************************************************************************************/
/*! \brief         Copies received data from DCM to vSwUpdM.
 *  \details       This API is called by vSwUpdM after call to vSwUpdM_ProcessStreamData.
 *  \param[in]     Info               The destination buffer and its length to which the download data is copied.
 *  \param[out]    AvailableDataPtr   The available data in the source buffer after current copy execution.
 *  \return        BUFREQ_E_OK        The copying succeeded.
 *  \return        BUFREQ_E_NOT_OK    The copying of data failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       callback
 *********************************************************************************************************************/
extern FUNC(BufReq_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMCopyStreamData(
  P2CONST(vSwUpdM_StreamDataInfoType, AUTOMATIC, VFOTAH_APPL_CONST) Info,
  P2VAR(vSwUpdM_StreamLengthType, AUTOMATIC, VFOTAH_APPL_DATA) AvailableDataPtr);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#endif /* VFOTAH_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Cbk.h
 *********************************************************************************************************************/
