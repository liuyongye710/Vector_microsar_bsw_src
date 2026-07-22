/**********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXRam_DetChecks.h
 *        \brief  Header file for declaration of DET checks functions for vMem_30_XXRam.
 *      \details  Provides the declarations for DET check functions of API parameters. These checks may be useful for
 *                hardware specific services for all subcomponents of vMem_30_XXRam.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 **********************************************************************************************************************/
#if !defined (VMEM_30_XXRAM_DETCHECKS_H)
# define VMEM_30_XXRAM_DETCHECKS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXRam_IntShared.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
/*! Initialization state of the module */
# define VMEM_30_XXRAM_UNINIT                              (0x00u)
# define VMEM_30_XXRAM_INIT                                (0x01u)
#endif /* (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON) */
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXRAM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
extern VAR(uint8, VMEM_30_XXRAM_VAR_ZERO_INIT) vMem_30_XXRam_ModuleInitialized;
#endif /* (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON) */

#define VMEM_30_XXRAM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define VMEM_30_XXRAM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsInstanceIdValid()
 *********************************************************************************************************************/
/*!
 * \brief       Checks the passed instance id - not to be out of range.
 * \details     -
 * \param[in]   InstanceId       id equal to index of the related vMem_30_XXRam instance in configuration structure.
 * \return      TRUE; if the instance id is valid; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsInstanceIdValid(vMem_30_XXRam_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_XXRam_InstancePendingCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether the requested instance is in a pending state.
 * \details     Calls LowLevel GetJobResult service, to retrieve current state of vMem_30_XXRam instance.
 * \param[in]   InstanceId        Id of vMem_30_XXRam instance is passed on to LowLevel, must be valid.
 * \return      TRUE, if the instance is pending; FALSE otherwise
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InstancePendingCheck(vMem_30_XXRam_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAddressPageAligned()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed address is aligned to page size of the referenced sector.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to check.
 * \return      TRUE, if the address is page aligned; FALSE otherwise
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAddressPageAligned(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address);
/**********************************************************************************************************************
 *  vMem_30_XXRam_IsBlankLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks if the passed Length matches the configured pagesize of the sector referenced by the address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           Address of the page that the given length shall be checked for, must be valid.
 * \param[in]   Length            Length of the page in bytes.
 * \return      TRUE, if the Length matches the configured pagesize; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsBlankLengthCheck(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXRam_IsAddressSectorAligned()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed address is aligned to the sector size.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to check.
 * \return      TRUE, if the address is sector aligned; FALSE otherwise
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_IsAddressSectorAligned(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address);
/**********************************************************************************************************************
 *  vMem_30_XXRam_EraseLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length matches the sector size or the erase burst size of the sector
 *              referenced by passed address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to erase, must be valid.
 * \param[in]   Length            Length in bytes to erase.
 * \return      TRUE, if the Length matches the sector size or erase burst size; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_EraseLengthCheck(vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length);
/**********************************************************************************************************************
 *  vMem_30_XXRam_WriteLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length matches the page size or the write burst size of the sector
 *              referenced by passed address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to write to, must be valid.
 * \param[in]   Length            Length in bytes to write.
 * \return      TRUE, if the Length matches the page size or write burst size; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_WriteLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXRam_ReadLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length is valid, that is if it is contained in the same sector batch as the
 *              passed Address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to read from, must be valid.
 * \param[in]   Length            Length in bytes to read.
 * \return      E_OK, if the Length is valid; E_NOT_OK otherwise
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_ReadLengthCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address, vMem_30_XXRam_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXRam_ReadAddressCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether the passed address points to any configured sector.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXRam instance, must be valid.
 * \param[in]   Address           NV memory address to read from.
 * \return      TRUE, if the address is valid; FALSE otherwise
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_ReadAddressCheck(
  vMem_30_XXRam_InstanceIdType InstanceId, vMem_30_XXRam_AddressType Address);
/**********************************************************************************************************************
 *  vMem_30_XXRam_InitPendingCheck()
 *********************************************************************************************************************/
/*!
 * \brief       In case of re-initialization check that no instance is pending.
 * \details     -
 * \return      TRUE, if every vMem_30_XXRam instance is idle; FALSE otherwise.
 * \pre         VMEM_30_XXRAM_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(boolean, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InitPendingCheck(void);
#endif /* (VMEM_30_XXRAM_DEV_ERROR_DETECT == STD_ON) */

# define VMEM_30_XXRAM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXRAM_DETCHECKS_H */
/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXRam_DetChecks.h
 *********************************************************************************************************************/
