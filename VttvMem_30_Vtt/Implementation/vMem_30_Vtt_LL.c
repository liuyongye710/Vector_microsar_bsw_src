/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_Vtt_LL.c
 *        \brief  vMem_30_Vtt LowLevel source file
 *
 *      \details  See vMem_30_Vtt_LL.h
 *
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_VTT_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_Vtt_LL.h"
#include "vMem_30_Vtt_IntShared.h"
#include "vMem_30_Vtt_DetChecks.h"
#include "VttCntrl_vMem.h"

#if (VMEM_30_VTT_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_30_VTT_LOCAL) /* COV_VMEM_30_VTT_COMPATIBILITY */
# define VMEM_30_VTT_LOCAL static
#endif

#if !defined (VMEM_30_VTT_LOCAL_INLINE) /* COV_VMEM_30_VTT_COMPATIBILITY */
# define VMEM_30_VTT_LOCAL_INLINE LOCAL_INLINE
#endif

typedef enum
{
    VMEM_30_VTT_NO_JOB = 0, /*!< Nothing to do, no job requested. */
    VMEM_30_VTT_READ_JOB, /*!< Read job requested. */
    VMEM_30_VTT_WRITE_JOB, /*!< Write job requested. */
    VMEM_30_VTT_ERASE_JOB, /*!< Erase job requested. */
    VMEM_30_VTT_BLANKCHECK_JOB /*!< BlankCheck job requested. */
} vMem_30_Vtt_JobType; /*!< Indicates which asynchronous job shall be performed next. */

typedef struct 
{
    vMem_30_Vtt_AddressType Address; /*!< Address in the NV memory which shall be processed. */
    vMem_30_Vtt_LengthType Length; /*!< Length of the data in byte. */
    vMem_30_Vtt_ConstDataPtrType WritePointer; /*!< This pointer references the user buffer which shall be written to the NV memory.*/
    vMem_30_Vtt_DataPtrType ReadPointer; /*!< This pointer references the user buffer which shall be filled with the data in the NV memory. */
} vMem_30_Vtt_JobDataType; /*!< Stores information about current job */


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define VMEM_30_VTT_START_SEC_VAR_NO_INIT_32
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Contains the result of the instance depending job. */
VMEM_30_VTT_LOCAL VAR(vMem_30_Vtt_JobResultType, VMEM_30_VTT_VAR) vMem_30_Vtt_JobResult[vMem_30_Vtt_GetSizeOfvMemInstance()]; 

/*! Contains the job type of the instance depending job. */
VMEM_30_VTT_LOCAL VAR(vMem_30_Vtt_JobType, VMEM_30_VTT_VAR)       vMem_30_Vtt_Job[vMem_30_Vtt_GetSizeOfvMemInstance()];

#define VMEM_30_VTT_STOP_SEC_VAR_NO_INIT_32
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define VMEM_30_VTT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Contains all data which are necessary to process the job, one for each instance. */
VMEM_30_VTT_LOCAL VAR(vMem_30_Vtt_JobDataType, VMEM_30_VTT_VAR)   vMem_30_Vtt_JobData[vMem_30_Vtt_GetSizeOfvMemInstance()];

#define VMEM_30_VTT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_VTT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessReadJob()
 *********************************************************************************************************************/
/*! \brief       Processes the read job.
 *  \details     vMem_30_Vtt_LLProcessReadJob reads the requested data into the given buffer, by using the corresponding
 *               function of VttCntrl.
 *  \param[in]   instanceId    ID and index of the related vMem_30_Vtt instance.
 *  \param[out]  none
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessReadJob(vMem_30_Vtt_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessWriteJob()
 *********************************************************************************************************************/
/*! \brief       Processes the write job.
 *  \details     vMem_30_Vtt_LLProcessWriteJob writes the data in the given buffer, by using the corresponding
 *               function of VttCntrl.
 *  \param[in]   instanceId    ID and index of the related vMem_30_Vtt instance.
 *  \param[out]  none
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessWriteJob(vMem_30_Vtt_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessEraseJob()
 *********************************************************************************************************************/
/*! \brief       Processes the Erase job.
 *  \details     vMem_30_Vtt_LLProcessEraseJob erases data in the flash by writing the VMEM_30_VTT_ERASE_VALUE into it.
 *               It uses the write function from VttCntrl.
 *  \param[in]   instanceId    ID and index of the related vMem_30_Vtt instance.
 *  \param[out]  none
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessEraseJob(vMem_30_Vtt_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessBlankCheckJob()
 *********************************************************************************************************************/
/*! \brief       Processes the BlankCheck job.
 *  \details     vMem_30_Vtt_LLProcessBlankCheckJob checks if the given flash area is blank.
 *  \param[in]   instanceId    ID and index of the related vMem_30_Vtt instance.
 *  \param[out]  none
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessBlankCheckJob(vMem_30_Vtt_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_Vtt_IsMemoryErased()
 *********************************************************************************************************************/
/*! \brief       Checks if the given flash area is erased.
 *  \details     vMem_30_Vtt_IsMemoryErased reads the data from flash and compares it with the VMEM_30_VTT_ERASE_VALUE. 
 *               It uses the read function from VttCntrl.
 *  \param[in]   Address    StartAddress of the memory that is checked
 *  \param[in]   Length     Number of bytes to be checked
 *  \param[out]  TRUE, if the memory is ERASED; FALSE, otherwise
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_VTT_LOCAL FUNC(boolean, VMEM_30_VTT_CODE) vMem_30_Vtt_IsMemoryErased(
  vMem_30_Vtt_AddressType Address, vMem_30_Vtt_LengthType Length);


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_Vtt_LLRead
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLRead(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType SourceAddress,
  vMem_30_Vtt_DataPtrType TargetAddressPtr,
  vMem_30_Vtt_LengthType Length)
{
    vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_PENDING;
    vMem_30_Vtt_Job[InstanceId] = VMEM_30_VTT_READ_JOB;

    vMem_30_Vtt_JobData[InstanceId].Address = SourceAddress - VMEM_30_VTT_ADDRESS_OFFSET; /* PRQA S 2985 */ /* MD_vMem_30_Vtt_OperationMayBeRedundant */
    vMem_30_Vtt_JobData[InstanceId].ReadPointer = TargetAddressPtr;
    vMem_30_Vtt_JobData[InstanceId].WritePointer = NULL_PTR;
    vMem_30_Vtt_JobData[InstanceId].Length = Length;
    return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLWrite(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_ConstDataPtrType SourceAddressPtr,
  vMem_30_Vtt_LengthType Length)
{
    /* ----- Local Variables ---------------------------------------------- */
    uint8 errorId = VMEM_30_VTT_E_NO_ERROR;
    Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

    /* ----- Development Error Checks ------------------------------------- */
    /* InstanceIds -> Ids correspond to index, is ensured by ComStackValidation Validator. */
    if(( vMem_30_Vtt_GetOverwriteDetectionOfvMemInstance(InstanceId) == TRUE) &&
       (vMem_30_Vtt_IsMemoryErased((TargetAddress - VMEM_30_VTT_ADDRESS_OFFSET), Length) == FALSE) /* PRQA S 2985, 3415 */ /* MD_vMem_30_Vtt_OperationMayBeRedundant, MD_VMEM_30_VTT_13.5_queries */
      )
    {   
        /* Related to AUTOSAR FLS_E_VERIFY_ERASE_FAILED error in flash driver use case (SWS_Fls_00055) */
        errorId = VMEM_30_VTT_E_OVERWRITE_DETECTED;
        vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_FAILED;  /* Job shall explicitly fail. */
    }
    else
    {
        vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_PENDING;
        vMem_30_Vtt_Job[InstanceId] = VMEM_30_VTT_WRITE_JOB;

        vMem_30_Vtt_JobData[InstanceId].Address = TargetAddress - VMEM_30_VTT_ADDRESS_OFFSET; /* PRQA S 2985 */ /* MD_vMem_30_Vtt_OperationMayBeRedundant */
        vMem_30_Vtt_JobData[InstanceId].ReadPointer = NULL_PTR;
        vMem_30_Vtt_JobData[InstanceId].WritePointer = SourceAddressPtr;
        vMem_30_Vtt_JobData[InstanceId].Length = Length;

        retVal = E_OK;
    }
    /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_VTT_DEV_ERROR_REPORT == STD_ON)
    if (errorId != VMEM_30_VTT_E_NO_ERROR)
    {
        (void)Det_ReportError(VMEM_30_VTT_MODULE_ID, VMEM_30_VTT_INSTANCE_ID_DET, VMEM_30_VTT_SID_WRITE, errorId);
    }
#else
    VMEM_30_VTT_DUMMY_STATEMENT(errorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

    return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLErase
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLErase(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_LengthType Length)
{
    vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_PENDING;
    vMem_30_Vtt_Job[InstanceId] = VMEM_30_VTT_ERASE_JOB;

    vMem_30_Vtt_JobData[InstanceId].Address = TargetAddress - VMEM_30_VTT_ADDRESS_OFFSET; /* PRQA S 2985 */ /* MD_vMem_30_Vtt_OperationMayBeRedundant */
    vMem_30_Vtt_JobData[InstanceId].Length = Length;
    
    return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLIsBlank
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLIsBlank(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_AddressType TargetAddress,
  vMem_30_Vtt_LengthType Length)
{
    vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_PENDING;
    vMem_30_Vtt_Job[InstanceId] = VMEM_30_VTT_BLANKCHECK_JOB;
    vMem_30_Vtt_JobData[InstanceId].Address = TargetAddress - VMEM_30_VTT_ADDRESS_OFFSET; /* PRQA S 2985 */ /* MD_vMem_30_Vtt_OperationMayBeRedundant */
    vMem_30_Vtt_JobData[InstanceId].Length = Length;

    return E_OK;
}

/**********************************************************************************************************************
 * vMem_30_Vtt_LLGetJobResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_Vtt_JobResultType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLGetJobResult(
    vMem_30_Vtt_InstanceIdType InstanceId)
{
    return vMem_30_Vtt_JobResult[InstanceId];
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessing(void)
{
    vMem_30_Vtt_InstanceIdType instanceId;
    for (instanceId = 0; instanceId < vMem_30_Vtt_GetSizeOfvMemInstance(); instanceId++)
    {
        switch (vMem_30_Vtt_Job[instanceId])
        {
            case VMEM_30_VTT_READ_JOB:
                vMem_30_Vtt_LLProcessReadJob(instanceId);
                break;
            case VMEM_30_VTT_WRITE_JOB:
                vMem_30_Vtt_LLProcessWriteJob(instanceId);
                break;
            case VMEM_30_VTT_ERASE_JOB:
                vMem_30_Vtt_LLProcessEraseJob(instanceId);
                break;
            case VMEM_30_VTT_BLANKCHECK_JOB:
                vMem_30_Vtt_LLProcessBlankCheckJob(instanceId);
                break;
            default: /* VMEM_30_VTT_NO_JOB */ 
                break;
        }
        vMem_30_Vtt_Job[instanceId] = VMEM_30_VTT_NO_JOB;
     }
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessReadJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessReadJob(
    vMem_30_Vtt_InstanceIdType instanceId)
{
    vMem_30_Vtt_LengthType index;

    for(index = 0; index < vMem_30_Vtt_JobData[instanceId].Length; index++)
    {
        uint8 value = VttvMem_Read(vMem_30_Vtt_JobData[instanceId].Address + index);
        ((uint8*) vMem_30_Vtt_JobData[instanceId].ReadPointer)[index] = value; /* PRQA S 0316 */ /* MD_vMem_30_Vtt_VoidPtrTypedPtr */
    }

    vMem_30_Vtt_JobResult[instanceId] = VMEM_JOB_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessWriteJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessWriteJob(
    vMem_30_Vtt_InstanceIdType instanceId)
{
    vMem_30_Vtt_LengthType index;

    for(index = 0; index < vMem_30_Vtt_JobData[instanceId].Length; index++)
    {
        uint8 value = ((const uint8*) vMem_30_Vtt_JobData[instanceId].WritePointer)[index]; /* PRQA S 0316 */ /* MD_vMem_30_Vtt_VoidPtrTypedPtr */
        VttvMem_Write(vMem_30_Vtt_JobData[instanceId].Address + index, value);
    }

    vMem_30_Vtt_JobResult[instanceId] = VMEM_JOB_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessEraseJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessEraseJob(
    vMem_30_Vtt_InstanceIdType instanceId)
{
    vMem_30_Vtt_LengthType index;

    for(index = 0; index < vMem_30_Vtt_JobData[instanceId].Length; index++)
    {
        VttvMem_Write(vMem_30_Vtt_JobData[instanceId].Address + index, VMEM_30_VTT_ERASE_VALUE);
    }

    vMem_30_Vtt_JobResult[instanceId] = VMEM_JOB_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLProcessBlankCheckJob
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_VTT_LOCAL FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_LLProcessBlankCheckJob(
    vMem_30_Vtt_InstanceIdType instanceId)
{
    vMem_30_Vtt_JobResult[instanceId] = VMEM_JOB_OK;

    if(vMem_30_Vtt_IsMemoryErased(vMem_30_Vtt_JobData[instanceId].Address, vMem_30_Vtt_JobData[instanceId].Length) == FALSE)
    {
        vMem_30_Vtt_JobResult[instanceId] = VMEM_MEM_NOT_BLANK;
    }
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_IsMemoryErased
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_VTT_LOCAL FUNC(boolean, VMEM_30_VTT_CODE) vMem_30_Vtt_IsMemoryErased(
  vMem_30_Vtt_AddressType Address, vMem_30_Vtt_LengthType Length)
{
    boolean retVal = TRUE;
    vMem_30_Vtt_LengthType index;

    for(index = 0; index < Length; index++)
    {
        uint8 value = VttvMem_Read(Address + index);

        if(value != VMEM_30_VTT_ERASE_VALUE)
        {
            retVal = FALSE;
            break;
        }
    }
    
    return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLInit(void)
{
    vMem_30_Vtt_InstanceIdType instanceId;

    for (instanceId = 0; instanceId < vMem_30_Vtt_GetSizeOfvMemInstance(); instanceId++)
    {
      vMem_30_Vtt_JobResult[instanceId] = VMEM_JOB_OK;
      vMem_30_Vtt_Job[instanceId]   = VMEM_30_VTT_NO_JOB;

      vMem_30_Vtt_JobData[instanceId].Address = 0u;
      vMem_30_Vtt_JobData[instanceId].ReadPointer = NULL_PTR;
      vMem_30_Vtt_JobData[instanceId].WritePointer = NULL_PTR;
      vMem_30_Vtt_JobData[instanceId].Length = 0u;
    }
    return E_OK;
}

/**********************************************************************************************************************
 *  vMem_30_Vtt_LLHwSpecific
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_VTT_CODE) vMem_30_Vtt_LLHwSpecific(
  vMem_30_Vtt_InstanceIdType InstanceId,
  vMem_30_Vtt_DataPtrType ReqSpecificData, /* PRQA S 3673 */ /* MD_vMem_30_Vtt_NotUsedPointer */
  uint32 SizeOfData
  )
{

    VMEM_30_VTT_DUMMY_STATEMENT(ReqSpecificData);
    VMEM_30_VTT_DUMMY_STATEMENT(SizeOfData);

    vMem_30_Vtt_JobResult[InstanceId] = VMEM_JOB_OK;
    return E_OK;
}

#define VMEM_30_VTT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* Justification for module-specific MISRA deviations:
    MD_vMem_30_Vtt_VoidPtrTypedPtr: rule 11.5
    Reason:     vMem accepts untyped void pointers in its hardware specific functionality, to provide a compatible
                interface for different hardware specific function implementations: One may get a structure of type A,
                the other of type B etc. With a void pointer interface the signature of all the functions keeps the same
                as can be used in one typed function pointer array.
                The user of this functionality has to make sure, that the referenced object is of type
                uint8. And the length must be given in units of uint8.
    Risk:       Possible mismatch of pointer type and given length parameter after cast of untyped void pointer.
    Prevention: Component tests ensures that the vMem_30_Eep accesses the referenced object correctly. 

    MD_CRC_2.1_StaticFunctionNotUsed:
    Reason: These inline functions are defined as a utility functionality and shall be accessible by each translation
            unit of the component. In some cases this functionality might not be used. This is not a problem as the
            compiler will optimize this code away in this case.
    Risk: No risk.
    Prevention: A compile switch could be introduced.

    MD_vMem_30_Vtt_NotUsedPointer: rule8.13
    Reason: Hardware specific request is defined to have a non constant data pointer parameter. But within vMem_30_Vtt 
            hardware specific functions are only implemented as dummy functions. So they do not change the data which is 
            referenced by the pointer.
    Risk: No risk.
    Prevention: No prevention.

    MD_vMem_30_Vtt_OperationMayBeRedundant: rule2.2
    Reason: The address offset given through the configuration may be 0. Should the value be 0, the operation is redundant
            but will not cause any harm or risk.
    Risk: No risk.
    Prevention: No prevention.

    MD_VMEM_30_VTT_13.5_queries:
    Reason: Functions at right hand of || or && are defined to have no side-effects. Therefore it is intended to omit
            unnecessary calls. Avoiding this deviation would degrade code structure without benefits (nesting of
             IF-clauses).
    Risk: A function HAS side effects, leading to unexpected behavior, if call is omitted.
    Prevention: Review; make sure, that these functions do not change any global value,
                and that they do not access "volatile" values.
*/

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_VTT_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Vtt_LL.c
 *********************************************************************************************************************/
