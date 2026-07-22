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
/*!        \file  vMem_30_Blocking_Int.h
 *        \brief  vMem internal header file for declaration of vMem common API
 *
 *      \details  This file contains the declarations of the common vMem API Read, Write, Erase, IsBlank and 
                  GetJobResult, as well as the declaration of vMem_30_AcquireLock, which is a "Hw Specific function". 
                  Declaration for dummy initialization and dummy main function are also provided.
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_BLOCKING_INT_H)
# define VMEM_30_BLOCKING_INT_H

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_BLOCKING_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_Blocking_Read()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to read data analogous to Fls.
 *  \details     vMem_30_Blocking_Write() immediately rejects any read request.
 *  \param[in]   InstanceId          ID of the related vMem instance.
 *  \param[in]   SourceAddress       NV memory address to read from.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to.
 *  \param[in]   Length              Length to be read.
 *  \return      Always E_NOT_OK, indicating that the request was rejected.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-187392
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Read(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType SourceAddress,
  vMem_30_Blocking_DataPtrType TargetAddressPtr,
  vMem_30_Blocking_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Blocking_Write()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to write data to nv memory.
 *  \details     vMem_30_Blocking_Write() immediately rejects any write request.
 *  \param[in]   InstanceId          ID of the related vMem instance.
 *  \param[in]   TargetAddress       NV memory address to write to.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to write to nv memory.
 *  \param[in]   Length              Length to write.
 *  \return      Always E_NOT_OK, indicating that the request was rejected.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-187392
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Write(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_ConstDataPtrType SourceAddressPtr,
  vMem_30_Blocking_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Blocking_Erase()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to erase data from nv memory.
 *  \details     vMem_30_Blocking_Write() immediately rejects any erase request.
 *  \param[in]   InstanceId          ID of the related vMem instance.
 *  \param[in]   TargetAddress       NV memory address to be erased.
 *  \param[in]   Length              Length to erase.
 *  \return      Always E_NOT_OK, indicating that the request was rejected.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-187392
 **********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Erase(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_IsBlank()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to check if a page is blank in nv memory.
 *  \details     vMem_30_Blocking_IsBlank() rejects any isBlank request.
 *  \param[in]   InstanceId          ID of the related vMem instance, must be valid.
 *  \param[in]   TargetAddress       Address of the flash page that is checked, must be valid.
 *  \param[in]   Length              Number of bytes to be checked (must be exactly the page size).
 *  \return      Always E_NOT_OK, indicating that the request was rejected.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-187392
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_IsBlank(
  vMem_30_Blocking_InstanceIdType InstanceId,
  vMem_30_Blocking_AddressType TargetAddress,
  vMem_30_Blocking_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Blocking_GetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem instance. (Actually don't care/ not checked, since this
 *                                   component ALWAYS affects all memory drivers and instances. Thus, it can only have
 *                                   one instance.)
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_Blocking_JobResultType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_GetJobResult(vMem_30_Blocking_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_Blocking_AcquireLock()
 *********************************************************************************************************************/
/*! \brief       Internal generic asynchronous service request handler.
 *  \details     Rejects all requests, if DET checks passed
 *  \param[in]    InstanceId - not used
 *  \param[out]  reqSpecificData - points to a valid struct vMem_30_Blocking_HwLockParams_s (which may be uninitialized)
 *  \param[in]    sizeOfData - size of reqSpecificData structure. Must be sizeof(struct vMem_30_Blocking_HwLockParams_s)
 *  \return      E_OK, if currently IDLE (unlocked), otherwise E_NOT_OK.
 *  \pre         -
 *  \post        retVal == E_OK => GetStatus(<anyID>) == JOB_PENDING && reqSpecificData.LockState == LOCKED
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace CREQ-188023
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_AcquireLock(
    vMemAccM_vMemInstanceIdType InstanceId, vMemAccM_vMemDataPtrType reqSpecificData, uint32 sizeOfData);
      
/**********************************************************************************************************************
 *  vMem_30_Blocking_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Dummy function acting as a main function, actually doing nothing.
 *  \details     This dummy function is needed for the interface to vMemAccM (via function pointer table)
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_MainFunction(void);

/**********************************************************************************************************************
 *  vMem_30_Blocking_Init()
 *********************************************************************************************************************/
/*! \brief       Dummy function acting as a init function, actually doing nothing.
 *  \details     This dummy function is needed for the interface to vMemAccM (via function pointer table)
 *  \param[in]   ConfigPtr - will neither be read nor written, just not used
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-298941
 *********************************************************************************************************************/
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_Init(vMem_30_Blocking_ConfigPtrType ConfigPtr);

# define VMEM_30_BLOCKING_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_BLOCKING_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Blocking_Int.h
 *********************************************************************************************************************/
