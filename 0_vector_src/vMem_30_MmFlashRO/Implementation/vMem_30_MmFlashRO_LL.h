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
/*!        \file  vMem_30_MmFlashRO_LL.h
 *        \brief  vMem_30_MmFlashRO LowLevel header file
 *
 *      \details  The vMem_30_MmFlashRO LowLevel subcomponent implements a memory mapped read access to the Flash.
 *                It performs the actual access of the NV device. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_MMFLASHRO_LL_H)
# define VMEM_30_MMFLASHRO_LL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_MmFlashRO_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*!< Number of extended hardware specific functionality. This equals the size of the array of hardware specific functions. */
# define VMEM_30_MMFLASHRO_EXTENDED_FUNCTION_COUNT    0u
/*!< Define for the table of hardware specific functionality. */
# define VMEM_30_MMFLASHRO_EXTENDED_FUNCTION_TABLE    NULL_PTR


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_MMFLASHRO_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLRead()
 *********************************************************************************************************************/
/*! \brief       Synchronous service to read data using memcpy.
 *  \details     vMem_30_MmFlashRO_LLRead() returns the requested data. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance, must be valid.
 *  \param[in]   SourceAddress       NV memory address to read from, must be valid.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to be read, must be valid.
 *  \return      E_OK job accepted, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLRead(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType SourceAddress,
  vMem_30_MmFlashRO_DataPtrType TargetAddressPtr,
  vMem_30_MmFlashRO_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLWrite()
 *********************************************************************************************************************/
/*! \brief       Returns E_NOT_OK. No write functionality implemented.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   TargetAddress       NV memory address to write to.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to write to nv memory.
 *  \param[in]   Length              Length in bytes to write.
 *  \return      E_NOT_OK.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLWrite(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_ConstDataPtrType SourceAddressPtr,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLErase()
 *********************************************************************************************************************/
/*! \brief       Returns E_NOT_OK. No erase functionality implemented.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   TargetAddress       NV memory address to be erased.
 *  \param[in]   Length              Length in bytes to erase.
 *  \return      E_NOT_OK.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLErase(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLIsBlank()
 *********************************************************************************************************************/
/*! \brief       Returns E_NOT_OK. No isblank functionality implemented.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance.
 *  \param[in]   TargetAddress       Address of the flash page that is checked.
 *  \param[in]   Length              Number of bytes to be checked.
 *  \return      E_NOT_OK.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLIsBlank(
  vMem_30_MmFlashRO_InstanceIdType InstanceId,
  vMem_30_MmFlashRO_AddressType TargetAddress,
  vMem_30_MmFlashRO_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLGetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last read job.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_MmFlashRO instance, must be valid.
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_MmFlashRO_JobResultType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLGetJobResult(vMem_30_MmFlashRO_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLProcessing()
 *********************************************************************************************************************/
/*! \brief       No state machine Processing. Only here for compatibility reasons.
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLProcessing(void);

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_LLInit()
 *********************************************************************************************************************/
/*! \brief       Job result is set to initial state: VMEM_JOB_OK.
 *  \details     -
 *  \return      E_OK initialization successful, E_NOT_OK initialization failed.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_LLInit(void);

# define VMEM_30_MMFLASHRO_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_MMFLASHRO_LL_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_MmFlashRO_LL.h
 *********************************************************************************************************************/
