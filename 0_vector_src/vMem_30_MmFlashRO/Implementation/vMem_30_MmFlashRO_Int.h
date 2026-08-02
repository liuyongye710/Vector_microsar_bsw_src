/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_MmFlashRO_Int.h
 *        \brief  vMem_30_MmFlashRO internal header file for declaration of vMem_30_MmFlashRO common API
 *
 *      \details  This file contains the declarations of the common vMem_30_MmFlashRO API Read, Write, Erase, IsBlank and GetJobResult.
 *                These API can be called via the FunctionPointerTable which is filled in the LowLevel part
 *                of the component.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_MMFLASHRO_INT_H)
# define VMEM_30_MMFLASHRO_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_MmFlashRO_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_MMFLASHRO_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vMem_30_MmFlashRO_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module vMem_30_MmFlashRO. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   ConfigPtr               Pointer to the configuration data.
 *  \pre         Interrupts are disabled.
 *  \pre         vMem_30_MmFlashRO_InitMemory has been called unless vMem_30_MmFlashRO_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_Init(vMem_30_MmFlashRO_ConfigPtrType ConfigPtr);

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Monitors and controls the continuous execution of the vMem_30_MmFlashRO handling.
 *  \details     -
 *  \param[in]   none.
 *  \param[out]  none.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_MainFunction(void);

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_Read()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to read data analogous to Fls.
 *  \details     vMem_30_MmFlashRO_Read() returns the requested data. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   SourceAddress       NV memory address to read from.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to be read.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_Read(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType SourceAddress,
  vMem_30_MmFlashRO_DataPtrType TargetAddressPtr,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_Write()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to write data to nv memory.
 *  \details     vMem_30_MmFlashRO_Write() writes data to nv memory. Parameter checks are done within core part. vMem_30_MmFlashRO may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   TargetAddress       NV memory address to write to.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to write to nv memory.
 *                                   Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to write.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_Write(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_ConstDataPtrType SourceAddressPtr,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_Erase()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to erase data from nv memory.
 *  \details     vMem_30_MmFlashRO_Erase() erases data from nv memory. Parameter checks are done within core part. vMem_30_MmFlashRO may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   TargetAddress       NV memory address to be erased.
 *  \param[in]   Length              Length in bytes to erase.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_Erase(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_IsBlank()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to check if a page is blank in nv memory.
 *  \details     vMem_30_MmFlashRO_IsBlank() checks if the page with the given address and length is blank, i.e valid to write to.
 *               Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance, must be valid.
 *  \param[in]   TargetAddress       Address of the flash page that is checked, must be valid.
 *  \param[in]   Length              Number of bytes to be checked (must be exactly the page size).
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_IsBlank(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_GetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_MmFlashRO_JobResultType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_GetJobResult(vMem_30_MmFlashRO_InstanceIdType InstanceId);

# define VMEM_30_MMFLASHRO_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_MMFLASHRO_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_MmFlashRO_Int.h
 *********************************************************************************************************************/
