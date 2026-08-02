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
/*!        \file vStreamProc.c
 *        \brief  vStreamProc Source Code File
 *
 *      \details  Implementation of the vStreamProc module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the vStreamProc module. >> vStreamProc.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#define VSTREAMPROC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vStreamProc.h"
#include "vStreamProc_Pipe.h"

#if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of vStreamProc header file */
#if (  (VSTREAMPROC_SW_MAJOR_VERSION != (2u)) \
    || (VSTREAMPROC_SW_MINOR_VERSION != (1u)) \
    || (VSTREAMPROC_SW_PATCH_VERSION != (4u)) )
# error "Vendor specific version numbers of vStreamProc.c and vStreamProc.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (VSTREAMPROC_CFG_MAJOR_VERSION != (2u)) \
    || (VSTREAMPROC_CFG_MINOR_VERSION != (1u)) )
# error "Version numbers of vStreamProc.c and vStreamProc_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  MISRA & PClint
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#if !defined (VSTREAMPROC_LOCAL)
# define VSTREAMPROC_LOCAL static
#endif

#if !defined (VSTREAMPROC_LOCAL_INLINE)
# define VSTREAMPROC_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

#define VSTREAMPROC_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Initialization state of the module */
#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
VSTREAMPROC_LOCAL VAR(uint8, VSTREAMPROC_VAR_ZERO_INIT) vStreamProc_ModuleInitialized = VSTREAMPROC_UNINIT;
#endif

#define VSTREAMPROC_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define VSTREAMPROC_START_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  vStreamProc_DetChecksPipe
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for pipe APIs.
 * \details       Includes check for opened pipe.
 *                Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksPipe(
  vStreamProc_PipeIdType PipeId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksEntryPoint
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on an entry point.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     EntryPointId    Id of an entry point of the desired pipe
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksEntryPointInfo
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on an entry point info structures.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     EntryPointInfo  Pointer to entry point information structure.
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoConstPtrType EntryPointInfo,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksExitPoint
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on an exit point.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     ExitPointId     Id of an exit point of the desired pipe
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointIdType ExitPointId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksExitPointInfo
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on an exit point info structures.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     ExitPointInfo   Pointer to exit point information structure.
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoConstPtrType ExitPointInfo,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksAccessPointInfos
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on multiple access point info structures.
 * \details       Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     EntryPointInfos Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount Number of entry point information structures.
 * \param[in]     ExitPointInfos  Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount  Number of exit point information structures.
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksAccessPointInfos(
  vStreamProc_EntryPointInfoConstPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoConstPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);

/**********************************************************************************************************************
 *  vStreamProc_DetChecksAccessPointIds
 *********************************************************************************************************************/
/*!
 * \brief         Performs common DET checks for APIs operating on multiple access point info structures.
 * \details       Includes check of access point IDs.
 *                Return code and ErrorId output parameter contain the same value.
 * \param[in]     PipeId          Id of the desired pipe.
 * \param[in]     EntryPointInfos Entry point information structures. NULL_PTR if not used.
 * \param[in]     EntryPointCount Number of entry point information structures.
 * \param[in]     ExitPointInfos  Exit point information structures. NULL_PTR if not used.
 * \param[in]     ExitPointCount  Number of exit point information structures.
 * \param[out]    ErrorId         VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                                DET error code          Otherwise.
 * \return        VSTREAMPROC_E_NO_ERROR  No error, all preconditions are fulfilled.
 *                DET error code          Otherwise.
 * \pre           -
 * \context       TASK|ISR
 * \reentrant     TRUE
 * \synchronous   TRUE
 *********************************************************************************************************************/
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksAccessPointIds(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  vStreamProc_DetChecksPipe
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksPipe(
  vStreamProc_PipeIdType PipeId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Check initialization state of the component. */
  if (vStreamProc_ModuleInitialized != (uint8)VSTREAMPROC_INIT)
  {
    errorID = VSTREAMPROC_E_UNINIT;
  }
  /* Check if pipe is unavailable. */
  else if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Ensure that the pipe is open. */
  else if (vStreamProc_GetPipeState(PipeId) != VSTREAMPROC_OPENED_PIPESTATE)
  {
    errorID = VSTREAMPROC_E_PIPE_STATE;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksEntryPoint
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* #10 Check plausibility of all input parameters. */
  /* Perform common DET checks for pipe APIs. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if EntryPointId is an invalid ID. */
  else if (EntryPointId >= vStreamProc_GetEntryPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksEntryPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoConstPtrType EntryPointInfo,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Perform common DET checks for pipe APIs. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if EntryPointInfo is a null pointer. */
  else if (EntryPointInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Check if EntryPointId is an invalid ID. */
  else if (EntryPointInfo->EntryPointId >= vStreamProc_GetEntryPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksExitPoint
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointIdType ExitPointId,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Perform common DET checks for pipe APIs. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if ExitPointId is an invalid ID. */
  else if (ExitPointId >= vStreamProc_GetExitPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksExitPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointInfoConstPtrType ExitPointInfo,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Perform common DET checks for pipe APIs. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if ExitPointInfo is a null pointer. */
  else if (ExitPointInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Check if ExitPointId is an invalid ID. */
  else if (ExitPointInfo->ExitPointId >= vStreamProc_GetExitPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksAccessPointInfos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksAccessPointInfos(
  vStreamProc_EntryPointInfoConstPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoConstPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Check if EntryPointInfo is a null pointer, while count is greater than zero. */
  if ( (EntryPointInfos == NULL_PTR) && (EntryPointCount > 0u) )
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Check if ExitPointInfo is a null pointer, while count is greater than zero. */
  else if ( (ExitPointInfos == NULL_PTR) && (ExitPointCount > 0u) )
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
}

/***********************************************************************************************************************
 *  vStreamProc_DetChecksAccessPointIds
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VSTREAMPROC_LOCAL FUNC(uint8, VSTREAMPROC_CODE) vStreamProc_DetChecksAccessPointIds(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount,
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_DATA) ErrorId)
{
  uint8 errorID;

  /* #10 Check plausibility of all input parameters. */
  /* Perform common DET checks for pipe APIs. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Perform common DET checks for APIs operating on multiple access point info structures. */
  else if (vStreamProc_DetChecksAccessPointInfos(EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check access point IDs for invalid values. */
  else if (vStreamProc_Pipe_DetChecksAccessPointInfos(PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  {
    /* Default to no error. */
    errorID = VSTREAMPROC_E_NO_ERROR;
  }

  *ErrorId = errorID;

  return errorID;
} /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * vStreamProc_InitMemory
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_InitMemory(void)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Initialize global state variables. */
#if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  vStreamProc_ModuleInitialized = VSTREAMPROC_UNINIT;
#endif
}

/**********************************************************************************************************************
 * vStreamProc_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_Init(
  P2CONST(vStreamProc_ConfigType, AUTOMATIC, VSTREAMPROC_PBCFG) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  VSTREAMPROC_DUMMY_STATEMENT(ConfigPtr);                                                                               /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component. */
  if (vStreamProc_ModuleInitialized == (uint8)VSTREAMPROC_INIT)
  {
    errorID = VSTREAMPROC_E_ALREADY_INITIALIZED;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    vStreamProc_PipeIterType pipeId;

    /* #20 Initialize pipe state to default value ("uninitialized"). */
    for (pipeId = 0u; pipeId < vStreamProc_GetSizeOfPipeState(); pipeId++)
    {
      vStreamProc_SetPipeState(pipeId, VSTREAMPROC_UNINIT_PIPESTATE);
    }

# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
    /* #30 Module is now initialized. */
    vStreamProc_ModuleInitialized = (uint8)VSTREAMPROC_INIT;
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_INIT, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */
}

/***********************************************************************************************************************
 *  vStreamProc_InitPipe
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_InitPipe(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check initialization state of the component. */
  if (vStreamProc_ModuleInitialized != (uint8)VSTREAMPROC_INIT)
  {
    errorID = VSTREAMPROC_E_UNINIT;
  }
  /* Check if pipe is unavailable. */
  else if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize the pipe. */
    retVal = vStreamProc_Pipe_Init((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_INIT_PIPE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

#if (VSTREAMPROC_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  vStreamProc_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTREAMPROC_CODE) vStreamProc_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, VSTREAMPROC_APPL_VAR) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if VersionInfoPtr is a NullPointer. */
  if (VersionInfoPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Copy version information. */
    VersionInfoPtr->vendorID = (uint16)VSTREAMPROC_VENDOR_ID;
    VersionInfoPtr->moduleID = (uint16)VSTREAMPROC_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)VSTREAMPROC_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)VSTREAMPROC_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)VSTREAMPROC_SW_PATCH_VERSION;
  }


  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_VERSION_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */
}
#endif /* (VSTREAMPROC_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
 *  vStreamProc_Open
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Open(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check initialization state of the component. */
  if (vStreamProc_ModuleInitialized != (uint8)VSTREAMPROC_INIT)
  {
    errorID = VSTREAMPROC_E_UNINIT;
  }
  /* Check if pipe is unavailable. */
  else if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check that the pipe is not opened yet. */
  else if (vStreamProc_GetPipeState(PipeId) != VSTREAMPROC_CLOSED_PIPESTATE)
  {
    errorID = VSTREAMPROC_E_PIPE_STATE;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Open the passed pipe. */
    retVal = vStreamProc_Pipe_Open((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_OPEN, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Close
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_Close(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Close the passed pipe. */
    retVal = vStreamProc_Pipe_Close((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_CLOSE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Process
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Process(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Route process request to passed pipe. */
    retVal = vStreamProc_Pipe_Process((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_PROCESS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_Flush
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_Flush(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Flush the passed pipe. */
    retVal = vStreamProc_Pipe_Flush((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET, VSTREAMPROC_API_ID_FLUSH, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_SetMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_SetMode(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeIdType, AUTOMATIC) PipeModeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if passed mode is invalid */
  else if ( (PipeModeId >= vStreamProc_GetSizeOfMode()) && (PipeModeId != VSTREAMPROC_NO_MODE) )
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue set mode request to passed pipe. */
    retVal = vStreamProc_Pipe_SetMode((vStreamProc_PipeIterType)PipeId, (vStreamProc_ModeIterType)PipeModeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_SET_MODE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetModeByHandle
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ModeIdType, VSTREAMPROC_CODE) vStreamProc_GetModeByHandle(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ModeHandleIdType, AUTOMATIC) HandleId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;
  vStreamProc_ModeIdType    modeId = VSTREAMPROC_NO_MODE;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if pipe is unavailable */
  if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Search for the matching mode handle. */
    if ( vStreamProc_HasMode()
      && (HandleId != VSTREAMPROC_NO_HANDLEOFMODE) )
    {
      vStreamProc_ModeIterType  modeIdx;

      for ( modeIdx = vStreamProc_GetModeStartIdxOfPipe(PipeId);
            modeIdx < vStreamProc_GetModeEndIdxOfPipe(PipeId);
            modeIdx++ )
      {
        if (vStreamProc_GetHandleOfMode(modeIdx) == HandleId)
        {
          modeId = (vStreamProc_ModeIdType)modeIdx;

          break;
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_MODE_BY_HANDLE, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return modeId;
}

/***********************************************************************************************************************
 *  vStreamProc_AnnounceStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_AnnounceStream(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_EntryPointIdType, AUTOMATIC) EntryPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ProduceCallbackType, AUTOMATIC) ProduceCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksEntryPoint(PipeId, EntryPointId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check passed callback is a null pointer.
   * Hint: NULL_PTR cannot be used here, as data pointer shouldn't be casted to function pointer. */
  else if (ProduceCbk == (vStreamProc_ProduceCallbackType)0)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue announce stream request to passed pipe. */
    retVal = vStreamProc_Pipe_AnnounceStream((vStreamProc_PipeIterType)PipeId, (vStreamProc_EntryPointIterType)EntryPointId, Length, ProduceCbk);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_ANNOUNCE_STREAM, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_PrepareEntryPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointIdType EntryPointId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if pipe is unavailable. */
  if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check if EntryPointId is an invalid ID. */
  else if (EntryPointId >= vStreamProc_GetEntryPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check if EntryPointInfo is a null pointer. */
  else if (EntryPointInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set ID in info structure. */
    EntryPointInfo->EntryPointId = EntryPointId;

    /* #30 Issue prepare request to passed pipe. */
    retVal = vStreamProc_Pipe_PrepareEntryPointInfo(PipeId, EntryPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_PREPARE_ENTRY_POINT_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetEntryPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetEntryPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksEntryPointInfo(PipeId, EntryPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if DataTypeId is an invalid ID. */
  else if (DataTypeId >= vStreamProcConf_vStreamProcDataTypeCount)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set data type in info structure. */
    EntryPointInfo->WriteRequest.StorageInfo.DataTypeInfo.Id = DataTypeId;

    /* #30 Issue getter request to passed pipe. */
    retVal = vStreamProc_Pipe_GetEntryPointInfo((vStreamProc_PipeIterType)PipeId, EntryPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_ENTRY_POINT_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_RequestEntryPointData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestEntryPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksEntryPointInfo(PipeId, EntryPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if DataTypeId is an invalid ID. */
  else if (DataTypeId >= vStreamProcConf_vStreamProcDataTypeCount)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set data type and request length in info structure. */
    EntryPointInfo->WriteRequest.StorageInfo.DataTypeInfo.Id  = DataTypeId;
    EntryPointInfo->WriteRequest.StorageInfo.RequestLength    = RequestLength;

    /* #30 Issue request to passed pipe. */
    retVal = vStreamProc_Pipe_RequestEntryPointData((vStreamProc_PipeIterType)PipeId, EntryPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_REQUEST_ENTRY_POINT_DATA, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetWriteRequestBuffer
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR), VSTREAMPROC_CODE) vStreamProc_GetWriteRequestBuffer(
  P2CONST(vStreamProc_WriteRequestType, AUTOMATIC, VSTREAMPROC_APPL_CONST) RequestBufferPtr,
  vStreamProc_DataTypeIdType DataTypeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                                         errorID = VSTREAMPROC_E_NO_ERROR;
  P2VAR(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) buffer  = NULL_PTR;                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if RequestBufferPtr is a null pointer. */
  if (RequestBufferPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Compare data type of request against expected one. */
  else if (RequestBufferPtr->StorageInfo.DataTypeInfo.Id != DataTypeId)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return buffer pointer of request. */
    buffer = RequestBufferPtr->Buffer;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_WRITE_REQUEST_BUFFER, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(DataTypeId);                                                                              /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return buffer;
}

/***********************************************************************************************************************
 *  vStreamProc_AcknowledgeEntryPoint
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeEntryPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_LengthType ProducedLength,
  boolean ReleaseFlag,
  vStreamProc_EntryPointInfoPtrType EntryPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksEntryPointInfo(PipeId, EntryPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set request length and release flag in info structure. */
    EntryPointInfo->WriteRequest.StorageInfo.RequestLength  = ProducedLength;
    EntryPointInfo->WriteRequest.StorageInfo.ReleaseFlag    = ReleaseFlag;

    /* #30 Issue acknowledge request to passed pipe. */
    retVal = vStreamProc_Pipe_AcknowledgeEntryPoint((vStreamProc_PipeIterType)PipeId, EntryPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_ACKNOWLEDGE_ENTRY_POINT, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_RequestStream
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestStream(
  CONST(vStreamProc_PipeIdType, AUTOMATIC) PipeId,
  CONST(vStreamProc_ExitPointIdType, AUTOMATIC) ExitPointId,
  CONST(vStreamProc_LengthType, AUTOMATIC) Length,
  VAR(vStreamProc_ConsumeCallbackType, AUTOMATIC) ConsumeCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;                                                                                     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksExitPoint(PipeId, ExitPointId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check passed callback is a null pointer.
   * Hint: NULL_PTR cannot be used here, as data pointer shouldn't be casted to function pointer. */
  else if (ConsumeCbk == (vStreamProc_ConsumeCallbackType)0)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue stream request to passed pipe. */
    retVal = vStreamProc_Pipe_RequestStream((vStreamProc_PipeIterType)PipeId, (vStreamProc_ExitPointIterType)ExitPointId, Length, ConsumeCbk);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_REQUEST_STREAM, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_PrepareExitPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_ExitPointIdType ExitPointId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if pipe is unavailable. */
  if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check if ExitPointId is an invalid ID. */
  else if (ExitPointId >= vStreamProc_GetExitPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check if ExitPointInfo is a null pointer. */
  else if (ExitPointInfo == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set ID in info structure. */
    ExitPointInfo->ExitPointId = ExitPointId;

    /* #30 Issue prepare request to passed pipe. */
    retVal = vStreamProc_Pipe_PrepareExitPointInfo(PipeId, ExitPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_PREPARE_EXIT_POINT_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetExitPointInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetExitPointInfo(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksExitPointInfo(PipeId, ExitPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if DataTypeId is an invalid ID. */
  else if (DataTypeId >= vStreamProcConf_vStreamProcDataTypeCount)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set data type in info structure. */
    ExitPointInfo->ReadRequest.StorageInfo.DataTypeInfo.Id = DataTypeId;

    /* #30 Issue getter request to passed pipe. */
    retVal = vStreamProc_Pipe_GetExitPointInfo((vStreamProc_PipeIterType)PipeId, ExitPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_EXIT_POINT_INFO, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_RequestExitPointData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestExitPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_DataTypeIdType DataTypeId,
  vStreamProc_LengthType RequestLength,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksExitPointInfo(PipeId, ExitPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* Check if DataTypeId is an invalid ID. */
  else if (DataTypeId >= vStreamProcConf_vStreamProcDataTypeCount)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set data type and request length in info structure. */
    ExitPointInfo->ReadRequest.StorageInfo.DataTypeInfo.Id  = DataTypeId;
    ExitPointInfo->ReadRequest.StorageInfo.RequestLength    = RequestLength;

    /* #30 Issue request to passed pipe. */
    retVal = vStreamProc_Pipe_RequestExitPointData((vStreamProc_PipeIterType)PipeId, ExitPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_REQUEST_EXIT_POINT_DATA, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetReadRequestBuffer
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR), VSTREAMPROC_CODE) vStreamProc_GetReadRequestBuffer(
  P2CONST(vStreamProc_ReadRequestType, AUTOMATIC, VSTREAMPROC_APPL_VAR) RequestBufferPtr,
  vStreamProc_DataTypeIdType DataTypeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                                           errorID = VSTREAMPROC_E_NO_ERROR;
  P2CONST(uint8, AUTOMATIC, VSTREAMPROC_APPL_VAR) buffer  = NULL_PTR;                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if RequestBufferPtr is a null pointer. */
  if (RequestBufferPtr == NULL_PTR)
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER;
  }
  /* Compare data type of request against expected one. */
  else if (RequestBufferPtr->StorageInfo.DataTypeInfo.Id != DataTypeId)
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return buffer pointer of request. */
    buffer = RequestBufferPtr->Buffer;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_READ_REQUEST_BUFFER, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(DataTypeId);                                                                              /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return buffer;
}

/***********************************************************************************************************************
 *  vStreamProc_AcknowledgeExitPoint
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeExitPoint(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_LengthType ConsumedLength,
  boolean ReleaseFlag,
  vStreamProc_ExitPointInfoPtrType ExitPointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksExitPointInfo(PipeId, ExitPointInfo, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set request length and release flag in info structure. */
    ExitPointInfo->ReadRequest.StorageInfo.RequestLength  = ConsumedLength;
    ExitPointInfo->ReadRequest.StorageInfo.ReleaseFlag    = ReleaseFlag;

    /* #30 Issue acknowledge request to passed pipe. */
    retVal = vStreamProc_Pipe_AcknowledgeExitPoint((vStreamProc_PipeIterType)PipeId, ExitPointInfo);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_ACKNOWLEDGE_EXIT_POINT, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_PrepareAccessPointInfos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if pipe is unavailable. */
  if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check access point info structures. */
  else if (vStreamProc_DetChecksAccessPointInfos(EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue prepare request to passed pipe. */
    retVal = vStreamProc_Pipe_PrepareAccessPointInfos((vStreamProc_PipeIterType)PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_PREPARE_ACCESS_POINT_INFOS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_PrepareAllAccessPointInfos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_PrepareAllAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  /* Check if pipe is unavailable */
  if (PipeId >= vStreamProc_GetSizeOfPipe())
  {
    errorID = VSTREAMPROC_E_ID_PARAM;
  }
  /* Check that entry point count matches actual count of pipe. */
  else if (EntryPointCount != vStreamProc_GetEntryPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER_SIZE;
  }
  /* Check that exit point count matches actual count of pipe. */
  else if (ExitPointCount != vStreamProc_GetExitPointLengthOfPipe(PipeId))
  {
    errorID = VSTREAMPROC_E_PARAM_POINTER_SIZE;
  }
  /* Check access point info structures. */
  else if (vStreamProc_DetChecksAccessPointInfos(EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue prepare request to passed pipe. */
    retVal = vStreamProc_Pipe_PrepareAllAccessPointInfos(PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_PREPARE_ALL_ACCESS_POINT_INFOS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_GetAccessPointInfos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_GetAccessPointInfos(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksAccessPointIds(PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue getter request to passed pipe. */
    retVal = vStreamProc_Pipe_GetAccessPointInfos((vStreamProc_PipeIterType)PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_GET_ACCESS_POINT_INFOS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_RequestAccessPointData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_RequestAccessPointData(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_EntryPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_ExitPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksAccessPointIds(PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue request to passed pipe. */
    retVal = vStreamProc_Pipe_RequestAccessPointData((vStreamProc_PipeIterType)PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_REQUEST_ACCESS_POINT_DATA, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_AcknowledgeAccessPoints
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_AcknowledgeAccessPoints(
  vStreamProc_PipeIdType PipeId,
  vStreamProc_EntryPointInfoPtrType EntryPointInfos,
  vStreamProc_ExitPointIdType EntryPointCount,
  vStreamProc_ExitPointInfoPtrType ExitPointInfos,
  vStreamProc_EntryPointIdType ExitPointCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksAccessPointIds(PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue acknowledge request to passed pipe. */
    retVal = vStreamProc_Pipe_AcknowledgeAccessPoints((vStreamProc_PipeIterType)PipeId, EntryPointInfos, EntryPointCount, ExitPointInfos, ExitPointCount);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_ACKNOWLEDGE_ACCESS_POINTS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

/***********************************************************************************************************************
 *  vStreamProc_ReleaseAllAccessPoints
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vStreamProc_ReturnType, VSTREAMPROC_CODE) vStreamProc_ReleaseAllAccessPoints(
  vStreamProc_PipeIdType PipeId)
{
  /* ----- Local Variables ---------------------------------------------- */
  vStreamProc_ReturnType retVal = VSTREAMPROC_FAILED;                                                                   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorID = VSTREAMPROC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of all input parameters. */
  if (vStreamProc_DetChecksPipe(PipeId, &errorID) != VSTREAMPROC_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
# endif /* VSTREAMPROC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Issue release request to passed pipe. */
    retVal = vStreamProc_Pipe_ReleaseAllAccessPoints((vStreamProc_PipeIterType)PipeId);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTREAMPROC_DEV_ERROR_REPORT == STD_ON)
  if (errorID != VSTREAMPROC_E_NO_ERROR)
  {
    (void)Det_ReportError(
      VSTREAMPROC_MODULE_ID, VSTREAMPROC_INSTANCE_ID_DET,
      VSTREAMPROC_API_ID_RELEASE_ALL_ACCESS_POINTS, errorID);
  }
# else
  VSTREAMPROC_DUMMY_STATEMENT(errorID);                                                                                 /* PRQA S 2983,3112 */ /* MD_MSR_DummyStmt */
# endif /* VSTREAMPROC_DEV_ERROR_REPORT */

  return retVal;
}

#define VSTREAMPROC_STOP_SEC_CODE
#include "MemMap.h"                                                                                                     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  MISRA
 *********************************************************************************************************************/
/* Justification for module specific MISRA deviations:

MD_vStreamProc_Rule11.3_0310_3305_CastPtrDiffObj:
Reason:     Cast is necessary to convert generic byte buffer pointer to type-specific pointer.
Risk:       Alignment issues may occur.
Prevention: Access function compare expected type against type of generated buffer.

MD_vStreamProc_Rule11.4_0316_CastPtrVoidPtrObj:
Reason:     Cast is necessary to convert generic workspace/configuration to specific workspace/configuration.
Risk:       Alignment issues may occur.
Prevention: Covered by code review.

MD_vStreamProc_Dir1.1_0314_CastPtrObjPtrVoid:
Reason:     Cast is necessary to convert generic workspace/configuration to specific workspace/configuration.
Risk:       Alignment issues may occur.
Prevention: Covered by code review.

MD_vStreamProc_Rule8.13_3673_NonConstPtrParam:
Reason:     Function shares it signature with a set of similar functions. All of those are accessed through a function
            pointer look-up table.
            As some of those functions modify the value, the parameter cannot be a 'pointer to const'.
Risk:       No risk.
Prevention: No prevention necessary.

MD_vStreamProc_Rule2.2_2981_2892_RedundantInitialization:
Reason:     Variable is initialized with a default value, although will be overwritten with another value
            for all cases where it is actually used.
            This is done to prevent compiler warnings about the use of possibly uninitialized variables.
Risk:       No risk.
Prevention: No prevention necessary.

*/

/**********************************************************************************************************************
*  END OF FILE: vStreamProc.c
*********************************************************************************************************************/
