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
/*!        \file  vMem_30_XXspi01_LL_InstanceInitializer.h
 *        \brief  -
 *
 *      \details  The Hw initializer is responsible of initializing the underlying flash device.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MULTIPLE INCLUSION PROTECTION
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXSPI01_LL_INSTANCEINITIALIZER_H_)
# define VMEM_30_XXSPI01_LL_INSTANCEINITIALIZER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXspi01_LL_Types.h"

/*********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation()
 *********************************************************************************************************************/
/*! \brief        Returns a buffer pointer containing the read JEDEC ID of the passed instance.
 *  \details      -
 *  \param[in]    instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \return       buffer pointer containing the JEDEC ID.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_SpiDataPtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized()
 *********************************************************************************************************************/
/*! \brief        Indicates if the requested instance is already initialized or not.
 *  \details      -
 *  \param[in]    instanceId          ID and index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE                The instance is initialized.
 *  \return       FALSE               The instance is not yet initialized.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Init()
 *********************************************************************************************************************/
/*! \brief        Initializes all internal parameters of this sub-component Hw initializer.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Init(void);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitInstance()
 *********************************************************************************************************************/
/*! \brief        Triggers the Hw initialization for the passed instance.
 *  \details      -
 *  \param[in]    instanceId         ID and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  FALSE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitInstance(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Processing()
 *********************************************************************************************************************/
/*! \brief        This function is cyclically called. It's processing the instance-specific Hw initialization.
 *  \details      -
 *  \param[in]    instanceId         ID and index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Processing(
    vMem_30_XXspi01_InstanceIdType instanceId);

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_INSTANCEINITIALIZER_H_ */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceInitializer.h
 *********************************************************************************************************************/
