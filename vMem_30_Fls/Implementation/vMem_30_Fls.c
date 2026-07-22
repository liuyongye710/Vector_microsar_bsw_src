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
/*!        \file  vMem_30_Fls.c
 *        \brief  vMem_30_Fls source file
 *
 *      \details  The vMem_30_Fls is a component which provides the declaration of functions and function pointer table.
 *                This component is a wrapper which just forwards requests to corresponding Flash driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_FLS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "vMem_30_Fls.h"

#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of vMem_30_Fls header file */
#if (  (VMEM_30_FLS_SW_MAJOR_VERSION != (3u)) \
    || (VMEM_30_FLS_SW_MINOR_VERSION != (0u)) \
    || (VMEM_30_FLS_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of vMem_30_Fls.c and vMem_30_Fls.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (VMEM_30_FLS_CFG_COMP_MAJOR_VERSION != (3u)) \
    || (VMEM_30_FLS_CFG_COMP_MINOR_VERSION != (0u)) )
# error "Version numbers of vMem_30_Fls.c and vMem_30_Fls_Lcfg.h are inconsistent!"
#endif

/* Check the version of vMemAccM_vMemApi file */
#if (  (VMEMACCM_VMEMAPI_MAJOR_VERSION != (4u)) \
    || (VMEMACCM_VMEMAPI_MINOR_VERSION != (0u)) )
# error "Version numbers of vMem.c and vMemAccM_vMemApi.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_30_FLS_LOCAL)/* COV_VMEM30FLS_COMPATIBILITY */
# define VMEM_30_FLS_LOCAL static
#endif

#if !defined (VMEM_30_FLS_LOCAL_INLINE)/* COV_VMEM30FLS_COMPATIBILITY */
# define VMEM_30_FLS_LOCAL_INLINE LOCAL_INLINE
#endif

typedef enum
{
  VMEM_30_FLS_WRITE_JOB,
  VMEM_30_FLS_READ_JOB,
  VMEM_30_FLS_ERASE_JOB,
  VMEM_30_FLS_ISBLANK_JOB
} vMem_30_Fls_CurrentJobType;  /* Indicates which job shall be performed next. */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Holds for each instance (FLS) the type information about current processing job. */
VMEM_30_FLS_LOCAL VAR(vMem_30_Fls_CurrentJobType, VMEM_30_FLS_VAR_ZERO_INIT) vMem_30_Fls_CurrentJob[VMEM_30_FLS_NUMBER_OF_INSTANCES];

#define VMEM_30_FLS_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Unique identifier of the vMem based on the below identifiers.
 * VMEMACCM_VMEMAPI_MAJOR_VERSION -> vMemAccM to vMem interface version
 * VMEM_30_FLS_DRIVER_ID -> Generated specific vMem identifier (20 bits). */
#define VMEM_30_FLS_UNIQUEID (uint32)(0u | (((uint32)VMEMACCM_VMEMAPI_MAJOR_VERSION) << 24u) | VMEM_30_FLS_DRIVER_ID)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! The vMem footer will be placed at the end of the vMem (after the code, data, etc.) and marks the end of the driver. */
VMEM_30_FLS_LOCAL CONST(uint32, AUTOMATIC) vMem_30_Fls_Footer = VMEM_30_FLS_UNIQUEID;

#define VMEM_30_FLS_STOP_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_Fls_Read()
 *********************************************************************************************************************/
/*! \brief       Forwards the service to underlying Fls driver to read data.
 *  \details     vMem_30_Fls_Read()  returns the requested data
 *  \param[in]   InstanceId          Id of the instance the job shall be executed for.
 *  \param[in]   SourceAddress       physical device address where read from nv memory starts.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to read into.
 *  \param[in]   Length              number of Bytes to be read.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise. 
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Read(
    vMem_30_Fls_InstanceIdType InstanceId,
    vMem_30_Fls_AddressType SourceAddress,
    vMem_30_Fls_DataPtrType TargetAddressPtr,
    vMem_30_Fls_LengthType Length
  );


/**********************************************************************************************************************
 *  vMem_30_Fls_Write()
 *********************************************************************************************************************/
/*! \brief       Forwards the service to write data, to underlying Fls driver.
 *  \details     vMem_30_Fls_Write() write data to nv memory.
 *  \param[in]   InstanceId          Id of the instance the job shall be executed for.
 *  \param[in]   TargetAddress       physical device address where write starts in nv memory.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to be written.
 *  \param[in]   Length              number of Bytes to be written into nv memory.
 *  \param[out]  none.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Write(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_ConstDataPtrType SourceAddressPtr,
  vMem_30_Fls_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Fls_Erase()
 *********************************************************************************************************************/
/*! \brief       Forwards the service to erase data, to underlying Fls driver.
 *  \details     vMem_30_Fls_Erase() erases data from nv memory.
 *  \param[in]   InstanceId          Id of the instance the job shall be executed for.
 *  \param[in]   TargetAddress       physical device address where erase starts in nv memory.
 *  \param[in]   Length              number of Bytes to be erased.
 *  \param[out]  none.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise. 
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Erase(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_LengthType Length
  );
  
/**********************************************************************************************************************
 *  vMem_30_Fls_IsBlank()
 *********************************************************************************************************************/
/*! \brief       Forwards the service to check the passed address space to be blank, to underlying Fls driver.
 *  \details     vMem_30_Fls_IsBlank() checks the passed address space to be blank.
 *  \param[in]   InstanceId            Id of the instance the job shall be executed for.
 *  \param[in]   TargetAddress         physical device address where blankCheck starts in nv memory.
 *  \param[in]   Length                number of Bytes to be blank checked.
 *  \param[out]  none.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise. 
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_IsBlank(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_Fls_GetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job from each instance, as long as no new job is accepted.
 *  \details     -
 *  \param[in]   InstanceId          Id of the instance the job shall be executed for.
 *  \return      VMEM_JOB_OK = 0, VMEM_JOB_PENDING, VMEM_JOB_FAILED, VMEM_MEM_NOT_BLANK
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(vMem_30_Fls_JobResultType, VMEM_30_FLS_CODE) vMem_30_Fls_GetJobResult(vMem_30_Fls_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_Fls_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Dummy function acting as a main function, actually doing nothing.
 *  \details     This dummy function is needed for the interface to vMemAccM (via function pointer table). The 
 *               vMem_30_Fls has no functionality which must be processed in the main function. The main function of
 *               the underlying Fls driver is triggered by the scheduler. So the vMem_30_Fls must not forward the call
 *               of the main function. 
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_MainFunction(void);

/**********************************************************************************************************************
 *  vMem_30_Fls_Init()
 *********************************************************************************************************************/
/*! \brief       Dummy function acting as a init function, actually doing nothing.
 *  \details     This dummy function is needed for the interface to vMemAccM (via function pointer table). The 
 *               vMem_30_Fls has no variables which must be initialized. The init function of the underlying Fls driver
 *               is called by the Ecu. So the vMem_30_Fls must not forward the call of the init function.
 *  \param[in]   ConfigPtr - will neither be read nor written, just not used
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-299720
 *********************************************************************************************************************/
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_Init(vMem_30_Fls_ConfigPtrType ConfigPtr);

/**********************************************************************************************************************
 *  vMem_30_Fls_InstanceIdtoArrayIndex()
 *********************************************************************************************************************/
/*! \brief       Returns the array index of the struct element belonging to the given InstanceID.
 *  \details     -
 *  \param[in]   InstanceId          Id of the instance.
 *  \return      Array Index.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_FLS_LOCAL FUNC(uint32, VMEM_30_FLS_CODE) vMem_30_Fls_InstanceIdtoArrayIndex (vMem_30_Fls_InstanceIdType InstanceId);


#if (VMEM_30_FLS_DEV_ERROR_DETECT== STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Fls_IsInstanceIndexValid()
 *********************************************************************************************************************/
/*!
 * \brief       Checks the passed instance index to exist (not to be out of range).
 * \details     -
 * \param[in]   InstanceId
 * \return      TRUE; if the index is valid; FALSE otherwise.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
VMEM_30_FLS_LOCAL_INLINE FUNC(boolean, VMEM_30_FLS_CODE) vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdType InstanceIndex);
#endif


#define VMEM_30_FLS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_Fls_FunctionPointerTable = {
  VMEM_30_FLS_UNIQUEID,
  &vMem_30_Fls_FunctionPointerTable.Header,
  &vMem_30_Fls_Footer,
  {
    0,
    NULL_PTR
  },
  &vMem_30_Fls_Init,
  &vMem_30_Fls_Read,
  &vMem_30_Fls_Write,
  &vMem_30_Fls_Erase,
  &vMem_30_Fls_IsBlank,
  &vMem_30_Fls_GetJobResult,
  &vMem_30_Fls_MainFunction
};

#define VMEM_30_FLS_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */



/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


/**********************************************************************************************************************
 *  vMem_30_Fls_InstanceIdtoArrayIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(uint32, VMEM_30_FLS_CODE) vMem_30_Fls_InstanceIdtoArrayIndex (vMem_30_Fls_InstanceIdType InstanceId)
{
  /* Default: set out of range value. */
  uint32 retVal = vMem_30_Fls_GetSizeOfvMemInstance();
  uint32 i;
  for(i = 0; i < vMem_30_Fls_GetSizeOfvMemInstance(); i++)
  {
    if(vMem_30_Fls_Services[i].InstID == InstanceId)
    {
      retVal = i;
      break;
    }
  }
  return retVal;
}

#if (VMEM_30_FLS_DEV_ERROR_DETECT== STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Fls_IsInstanceIndexValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_FLS_LOCAL_INLINE FUNC(boolean, VMEM_30_FLS_CODE) vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdType InstanceIndex)
{
  return (boolean)(InstanceIndex < vMem_30_Fls_GetSizeOfvMemInstance()); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
}
#endif

/**********************************************************************************************************************
 *  vMem_30_Fls_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Read(
    vMem_30_Fls_InstanceIdType InstanceId,
    vMem_30_Fls_AddressType SourceAddress,
    vMem_30_Fls_DataPtrType TargetAddressPtr,
    vMem_30_Fls_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_FLS_E_NO_ERROR; /* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_vMem_30_Fls_APIPattern */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_FLS_E_PARAM_INSTANCE_ID; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else if (TargetAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_FLS_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    vMem_30_Fls_CurrentJob[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)] = VMEM_30_FLS_READ_JOB;   /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */

    retVal = vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].Read(SourceAddress, (uint8*) TargetAddressPtr, Length); /* PRQA S 0316, 2843 */ /* MD_vMem_30_Fls_VoidPtrTypedPtr, MD_vMem_30_Fls_SuspiciousPointer */
  }
  
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_READ, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_Fls_Read() */


/**********************************************************************************************************************
 *  vMem_30_Fls_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Write(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_ConstDataPtrType SourceAddressPtr,
  vMem_30_Fls_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  uint8 errorId = VMEM_30_FLS_E_NO_ERROR; /* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_vMem_30_Fls_APIPattern */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_FLS_E_PARAM_INSTANCE_ID; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else if (SourceAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_FLS_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    vMem_30_Fls_CurrentJob[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)] = VMEM_30_FLS_WRITE_JOB; /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */

    retVal = vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].Write(TargetAddress, (const uint8*)SourceAddressPtr, Length); /* PRQA S 0316, 2843 */ /* MD_vMem_30_Fls_VoidPtrTypedPtr, MD_vMem_30_Fls_SuspiciousPointer */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_WRITE, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_Fls_Write() */


/**********************************************************************************************************************
 *  vMem_30_Fls_Erase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_Erase(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  uint8 errorId = VMEM_30_FLS_E_NO_ERROR; /* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_vMem_30_Fls_APIPattern */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_FLS_E_PARAM_INSTANCE_ID; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
    vMem_30_Fls_CurrentJob[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)] = VMEM_30_FLS_ERASE_JOB; /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */

    retVal = vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].Erase(TargetAddress, Length); /* PRQA S 2983, 2843 */ /* MD_vMem_30_Fls_APIPattern, MD_vMem_30_Fls_SuspiciousPointer */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_ERASE, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_Fls_Erase() */


/**********************************************************************************************************************
 *  vMem_30_Fls_IsBlank()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(Std_ReturnType, VMEM_30_FLS_CODE) vMem_30_Fls_IsBlank(
  vMem_30_Fls_InstanceIdType InstanceId,
  vMem_30_Fls_AddressType TargetAddress,
  vMem_30_Fls_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  uint8 errorId = VMEM_30_FLS_E_NO_ERROR; /* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_vMem_30_Fls_APIPattern */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_FLS_E_PARAM_INSTANCE_ID; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    vMem_30_Fls_CurrentJob[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)] = VMEM_30_FLS_ISBLANK_JOB; /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */

    /* In case the underlying FLS driver does not offer the BlankCheck API, return E_NOT_OK */
    if(vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].BlankCheck != NULL_PTR)  /* PRQA S 2983, 2843 */ /* MD_vMem_30_Fls_APIPattern, MD_vMem_30_Fls_SuspiciousPointer */
    {
      retVal = vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].BlankCheck(TargetAddress, Length);  /* PRQA S 2983, 2843 */ /* MD_vMem_30_Fls_APIPattern, MD_vMem_30_Fls_SuspiciousPointer */
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_BLANK_CHECK, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_Fls_IsBlank() */

/**********************************************************************************************************************
 *  vMem_30_Fls_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_FLS_LOCAL FUNC(vMem_30_Fls_JobResultType, VMEM_30_FLS_CODE) vMem_30_Fls_GetJobResult(
    vMem_30_Fls_InstanceIdType InstanceId
    )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_FLS_E_NO_ERROR; /* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */
  vMem_30_Fls_JobResultType jobResult = VMEM_JOB_FAILED;  /* PRQA S 2981 */ /* MD_vMem_30_Fls_APIPattern */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_Fls_IsInstanceIndexValid(vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_FLS_E_PARAM_INSTANCE_ID; /* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
  switch (vMem_30_Fls_Services[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)].GetJobResult())  /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */
  {
       case MEMIF_JOB_OK:
         jobResult = VMEM_JOB_OK;
         break;
       case MEMIF_JOB_FAILED:
         jobResult = VMEM_JOB_FAILED;
         break;
       case MEMIF_JOB_PENDING:
         jobResult = VMEM_JOB_PENDING;
         break;
       case MEMIF_BLOCK_INCONSISTENT:
         if( vMem_30_Fls_CurrentJob[vMem_30_Fls_InstanceIdtoArrayIndex(InstanceId)] == VMEM_30_FLS_ISBLANK_JOB){ /* PRQA S 2843 */ /* MD_vMem_30_Fls_SuspiciousPointer */
           jobResult = VMEM_MEM_NOT_BLANK;
         } else {
           jobResult = VMEM_JOB_FAILED;
         }
         break;
       default: /* MEMIF_JOB_CANCELED, MEMIF_BLOCK_INVALID */
         jobResult = VMEM_JOB_FAILED;
         break;
         /*
          * currently not used in wrapper mode:
          * - VMEM_30_FLS_READ_CORRECTED_ERRORS
          * - VMEM_30_FLS_READ_UNCORRECTABLE_ERRORS
          */
  }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_GET_JOB_RESULT, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
  return jobResult;
} /* vMem_30_Fls_GetJobResult() */

/**********************************************************************************************************************
 *  vMem_30_Fls_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_MainFunction(void)
{

} 

/**********************************************************************************************************************
 *  vMem_30_Fls_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_Init(vMem_30_Fls_ConfigPtrType ConfigPtr)
{
  VMEM_30_FLS_DUMMY_STATEMENT(ConfigPtr);
} 






/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/* vMem_30_Fls is just a wrapper for following services: Read, Write, Erase, GetJobResult.
 * It provides an initialization service and a main function which have no functionality implemented to be compatible 
 * with the other vMems. 
 */

#if (VMEM_30_FLS_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Fls_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_FLS_APPL_VAR) versionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_FLS_E_NO_ERROR;/* PRQA S 2981, 3205 */ /* MD_vMem_30_Fls_APIPattern */

#if (VMEM_30_FLS_DEV_ERROR_DETECT == STD_ON)
  
  /* ----- Development Error Checks ------------------------------------- */
  if (versionInfo == NULL_PTR)
  {
    errorId = VMEM_30_FLS_E_PARAM_POINTER;/* PRQA S 2983 */ /* MD_vMem_30_Fls_APIPattern */
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    versionInfo->vendorID = (VMEM_30_FLS_VENDOR_ID);
    versionInfo->moduleID = (VMEM_30_FLS_MODULE_ID);
    versionInfo->sw_major_version = (VMEM_30_FLS_SW_MAJOR_VERSION);
    versionInfo->sw_minor_version = (VMEM_30_FLS_SW_MINOR_VERSION);
    versionInfo->sw_patch_version = (VMEM_30_FLS_SW_PATCH_VERSION);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_FLS_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_FLS_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_FLS_MODULE_ID, VMEM_30_FLS_INSTANCE_ID_DET, VMEM_30_FLS_SID_GET_VERSION_INFO, errorId);
  }
#else
  VMEM_30_FLS_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}
#endif


#define VMEM_30_FLS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */



/* START_COVERAGE_JUSTIFICATION

Code coverage:

  \ID COV_VMEM30FLS_DUMMY_STMT
    \ACCEPT TX
    \ACCEPT TF tf tf tx tf tf tf
    \REASON Dummy statement is always activated in the test suite to avoid compiler and MISRA warnings.
END_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM30FLS_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

COV_JUSTIFICATION_END */

/* Justification for module-specific MISRA deviations:

MD_vMem_30_Fls_APIPattern: rule 2.2
    Reason: SafeBSW requires the "API pattern" implementation, which leads to this MISRA issue: redundant assignment and initialization.
            Unused errorId will be solved by DUMMY_STATEMENT. The API pattern also requires single point of return - with disabled
            parameter checks the return value variable will never be used before modified.
    Risk: No risk.
    Prevention: Not possible, API pattern mandatory in SafeBSW.

MD_vMem_30_Fls_VoidPtrTypedPtr: rule 1.1, 11.5
    Reason:     vMem_30_Fls accepts untyped void pointers for user buffers. vMem_30_Fls passed void pointer to uint8 pointer, because it is required from underlying FLS driver.
    Risk:       No risk.
    Prevention: Component tests ensures that the vMemAccM forwards and accesses the RAM buffers correctly.

MD_vMem_30_Fls_SuspiciousPointer: rule 1.3, 21.18, dir 4.1
    Reason:     The Api gets the InstanceId which is used to calculate the array index. It is possible that the 
                calculated index exceeds the range of the array.
    Risk:       No risk.
    Prevention: The array index is checked before an array access occurs. 
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Fls.c
 *********************************************************************************************************************/
