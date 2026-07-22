/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_Cbk_Int.h
 *        \brief  -
 *
 *      \details  Defines vMem_30_XXspi01_LL callbacks for internal notification about finished jobs.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LL_CBK_INT_H)
# define VMEM_30_XXSPI01_LL_CBK_INT_H

/*********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_Types.h"

/*********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLSeqEndNotification()
 *********************************************************************************************************************/
/*! \brief        Callback service to notify the vMem module about a finished sequence.
 *  \details      -
 *  \param[in]    instanceId      Id and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    spiSeqId        Id of the corresponding SPI sequence.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLSeqEndNotification(vMem_30_XXspi01_InstanceIdType instanceId,
    Spi_SequenceType spiSeqId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_JobSucceeded()
 *********************************************************************************************************************/
/*! \brief        Notifies the vMem_30_XXspi01_LL about a successfully finished job.
 *  \details      -
 *  \param[in]    instanceId       Id and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_JobSucceeded(vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_InitSucceeded()
 *********************************************************************************************************************/
/*! \brief        Notifies the vMem_30_XXspi01_LL about a successfully initialized instance.
 *  \details      -
 *  \param[in]    instanceId       Id and index of the related vMem_30_XXspi01 instance.
 *  \param[in]    deviceId         Index of the related device information.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_InitSucceeded(vMem_30_XXspi01_InstanceIdType instanceId, vMem_30_XXspi01_DeviceIdType deviceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_Cbk_JobFailed()
 *********************************************************************************************************************/
/*! \brief        Notifies the vMem_30_XXspi01_LL about a failed job.
 *  \details      -
 *  \param[in]    instanceId       Id and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_Cbk_JobFailed(vMem_30_XXspi01_InstanceIdType instanceId);

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_CBK_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_Types.h
 *********************************************************************************************************************/
