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
/*!        \file  vMem_30_Vtt_Int.h
 *        \brief  vMem_30_Vtt internal header file for declaration of vMem_30_Vtt common API
 *
 *      \details  This file contains the declarations of the common vMem_30_Vtt API Read, Write, Erase, IsBlank and GetJobResult.
 *                These API can be called via the FunctionPointerTable which is filled in the LowLevel part
 *                of the component.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_VTT_INT_H)
# define VMEM_30_VTT_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_Vtt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_VTT_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * vMem_30_Vtt_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module vMem_30_Vtt. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   ConfigPtr               Pointer to the configuration data.
 *  \pre         Interrupts are disabled.
 *  \pre         vMem_30_Vtt_InitMemory has been called unless vMem_30_Vtt_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_Init(vMem_30_Vtt_ConfigPtrType ConfigPtr);

/**********************************************************************************************************************
 *  vMem_30_Vtt_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Monitors and controls the continuous execution of the vMem_30_Vtt handling.
 *  \details     -
 *  \param[in]   none.
 *  \param[out]  none.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_MainFunction(void);

/**********************************************************************************************************************
 *  vMem_30_Vtt_Read()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to read data analogous to Fls.
 *  \details     vMem_30_Vtt_Read() returns the requested data. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_Vtt instance.
 *  \param[in]   SourceAddress       NV memory address to read from.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to be read.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_Read(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType SourceAddress,
  vMem_30_Vtt_DataPtrType TargetAddressPtr,
  vMem_30_Vtt_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Vtt_Write()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to write data to nv memory.
 *  \details     vMem_30_Vtt_Write() writes data to nv memory. Parameter checks are done within core part. vMem_30_Vtt may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_Vtt instance.
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
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_Write(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_ConstDataPtrType SourceAddressPtr,
  vMem_30_Vtt_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Vtt_Erase()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to erase data from nv memory.
 *  \details     vMem_30_Vtt_Erase() erases data from nv memory. Parameter checks are done within core part. vMem_30_Vtt may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_Vtt instance.
 *  \param[in]   TargetAddress       NV memory address to be erased.
 *  \param[in]   Length              Length in bytes to erase.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_Erase(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Vtt_IsBlank()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to check if a page is blank in nv memory.
 *  \details     vMem_30_Vtt_IsBlank() checks if the page with the given address and length is blank, i.e valid to write to.
 *               Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_Vtt instance, must be valid.
 *  \param[in]   TargetAddress       Address of the flash page that is checked, must be valid.
 *  \param[in]   Length              Number of bytes to be checked (must be exactly the page size).
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_IsBlank(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Vtt_GetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_Vtt instance.
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_Vtt_JobResultType, VMEM_30_VTT_CODE) vMem_30_Vtt_GetJobResult(vMem_30_Vtt_InstanceIdType InstanceId);

# define VMEM_30_VTT_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_VTT_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Vtt_Int.h
 *********************************************************************************************************************/
