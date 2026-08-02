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
/*!        \file  vSwUpdM_Services.c
 *        \brief  vSwUpdM_Services source file
 *      \details  Implementation of the vSwUpdM_Services subcomponent.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main header file vSwUpdM.h.
 *********************************************************************************************************************/

#define VSWUPDM_SERVICES_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* Services implementation header */
#include "vSwUpdM_Services_Impl.h"

/* Implementation headers of all contained Units */
#include "vSwUpdM_SrvcLocal_Impl.h"
#include "vSwUpdM_SrvcRouting_Impl.h"
#include "vSwUpdM_SrvcUpperLayer_Impl.h"

/* Other MultipleUnits used by Services (Prefer smallest set required, i.e. prefer _Types over _If over _Impl) */
#include "vSwUpdM_Grid_Impl.h"
#include "vSwUpdM_Range.h"
#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
# include "vRpcProxy_vSwUpdM.h"
# include "vRpcProxy_Service.h"
#endif /* (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) */

#include "vSwUpdM_Lcfg.h"

#include "vSwUpdM_DevError_Impl.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
  vSwUpdM_NodeIterType RequestOrigin;                       /**< Source of the request */
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex;             /**< ServiceIndex of the Request */
  boolean IsOccupied;                                       /**< This buffer entry is in use */
  Std_ReturnType Result;                                    /**< Result for given request */
  vSwUpdM_GridRpc_ServiceExecutionStateType ExecutionState; /**< PENDING flag for request */
} vSwUpdM_SrvcRouting_RxChannelType;

typedef P2VAR(vSwUpdM_SrvcRouting_RxChannelType, AUTOMATIC, VSWUPDM_APPL_VAR) vSwUpdM_SrvcRouting_RxChannelPtrType;

/* Named indices for RxChannels. The order defines which responses are processed with high/low priority.
 * Suspend, Maintenance responses have lowest priority to ensure correct order of responses in any case.
 */
typedef enum
{
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO, /* PRQA S 0724 */ /* MD_vSwUpdM_Rule8.12_0724_EnumCountEqualsInvalid */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_LEGACY = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO, /**< Highest priority for Response transmission. */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_SUSPEND,
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAINTENANCE, /**< Lowest priority for Response transmission. */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT, /* PRQA S 0724 */ /* MD_vSwUpdM_Rule8.12_0724_EnumCountEqualsInvalid */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT
}vSwUpdM_SrvcRouting_RxChannelIndexType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VSWUPDM_LOCAL CONST(vSwUpdM_SrvcRouting_RxChannelIndexType, VSWUPDM_CONST) vSwUpdM_SrvcRouting_RxChannelIndex[VSWUPDM_GRIDSRVC_SERVICEIDX_COUNT] =    /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
  /* Maintenance Channel */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAINTENANCE,  /* VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAINTENANCE,  /* VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAINTENANCE,  /* VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK */

  /* Suspend Channel */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_SUSPEND,      /* VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_SUSPEND,      /* VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME */

  /* Main Channel */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_START */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT */

  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT */

  /* Bookkeeper */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_GENERIC_PARAMETER */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_SEGMENT_ATTRIBUTES */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_SET_RESUME_INFO */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_GENERIC_PARAMETER */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_SEGMENT_ATTRIBUTES */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_GET_RESUME_INFO */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_BK_EXEC_COMMAND */

  /* Legacy Services */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* SWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_LEGACY,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_RESPONSE_COPY_STREAM_DATA */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UPDATE,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONFIRMATION */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_UNUSED,       /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN,         /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_REQUEST */
  VSWUPDM_SRVCROUTING_RXCHANNELINDEX_MAIN          /* VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_START */
};

/*! Configuration of module state-dependent startup operation modes for VerifyModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessOpSelectType, AUTOMATIC) vSwUpdM_ProcessOpSelect_VerifyModule[] =
{
  { VSWUPDM_MODULE_STATE_FINALIZED,   VSWUPDM_PROC_NODE_OPERATION_START },
  { VSWUPDM_MODULE_STATE_VERIFIED,    VSWUPDM_PROC_NODE_OPERATION_NONE  }
};

/*! Configuration for VerifyModule data process. */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessConfigType, AUTOMATIC) vSwUpdM_ProcessConfig_VerifyModule =  /* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
  {
    { VSWUPDM_MODULE_STATE_UNDEFINED, TRUE },
    { VSWUPDM_MODULE_STATE_UNDEFINED, TRUE },
    { VSWUPDM_MODULE_STATE_VERIFIED,  TRUE },
  },
  vSwUpdM_ProcessOpSelect_VerifyModule,
  VSWUPDM_ARRAY_SIZE(vSwUpdM_ProcessOpSelect_VerifyModule)
};

/*! Configuration of module state-dependent startup operation modes for ProcessModule data process(es). */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessOpSelectType, AUTOMATIC) vSwUpdM_ProcessOpSelect_ProcessModule[] =
{
  { VSWUPDM_MODULE_STATE_VERIFIED,          VSWUPDM_PROC_NODE_OPERATION_START         },
  { VSWUPDM_MODULE_STATE_PROCESS_STARTED,   VSWUPDM_PROC_NODE_OPERATION_START         },
  { VSWUPDM_MODULE_STATE_PROCESS_DIRTY,     VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART },
  { VSWUPDM_MODULE_STATE_PROCESS_CLEAN,     VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART },
  { VSWUPDM_MODULE_STATE_PROCESS_FINISHED,  VSWUPDM_PROC_NODE_OPERATION_NONE          }
};

/*! Configuration for ProcessModule data process(es). */
VSWUPDM_LOCAL CONST(vSwUpdM_ProcessConfigType, AUTOMATIC) vSwUpdM_ProcessConfig_ProcessModule = /* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
{
  {
    { VSWUPDM_MODULE_STATE_PROCESS_STARTED,   TRUE },
    { VSWUPDM_MODULE_STATE_PROCESS_DIRTY,     TRUE },
    { VSWUPDM_MODULE_STATE_PROCESS_FINISHED,  TRUE },
  },
  vSwUpdM_ProcessOpSelect_ProcessModule,
  VSWUPDM_ARRAY_SIZE(vSwUpdM_ProcessOpSelect_ProcessModule)
};

#define VSWUPDM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VSWUPDM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Buffer for preparing response data and track PENDING state. */
VSWUPDM_LOCAL VAR(vSwUpdM_SrvcRouting_RxChannelType, VSWUPDM_APPL_DATA) vSwUpdM_SrvcRouting_RxChannel[VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT]; /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
/* Index for Round-Robin scheme for ResponsePending triggers. */
VSWUPDM_LOCAL VAR(vSwUpdM_SrvcRouting_RxChannelIndexType, VSWUPDM_APPL_DATA) vSwUpdM_SrvcRouting_CurrentRxChannelIndex; /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
/* Number of pending responses. */
VAR(uint8, VSWUPDM_APPL_DATA) vSwUpdM_SrvcRouting_NumberOfPendingResponses; /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */

/* Stores last suspended request to allow checking re-request on resume. */
/* PRQA S 3218 1 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */
VSWUPDM_LOCAL VAR(vSwUpdM_GridSrvc_ServiceIdxType, VSWUPDM_VAR_NOINIT) vSwUpdM_SrvcRouting_RemoteResumeService; /* PRQA S 3218 */ /* MD_vSwUpdM_Rule8.9_3218_FileScope */

#define VSWUPDM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VSWUPDM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vSwUpdM_RemoteTransmitResponse
 *********************************************************************************************************************/
/*! \brief       Transmits a Confirmation service for a service
 *  \details     Maps the Confirmation Service ID to the related Remote Service ID and triggers transmission of
 *               a RemoteConfirmation message.
 *  \param[in]   ConfirmationService The SID of the service to be confirmed.
 *  \param[in]   Source              Source of the remote request to be confirmed.
 *  \param[in]   Result              Result of the processing of the remote request to be confirmed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteTransmitResponse(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_OpenRxChannel
 *********************************************************************************************************************/
/*! \brief       Registers a buffer for preparing final and "pending" responses for a request.
 *  \details     If a request is received and accepted for processing, this function acquires the buffer for the
 *               response and enables the transmission of "pending" responses until a final response.
 *  \param[in]   RequestOrigin  Origin of Request.
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_OpenRxChannel(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_ResultIndicaton
 *********************************************************************************************************************/
/*! \brief       Registers the result of a request for response transmission.
 *  \details     After a request has processed, the result shall be sent via a response message. This function registers
 *               the result and the response will be sent asynchronously.
 *  \param[in]   RequestOrigin  Origin of Request.
 *  \param[in]   ServiceIndex   Service index of given service.
 *  \param[in]   Result         Indicated result.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ResultIndicaton(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_TransmitFinalResponses
 *********************************************************************************************************************/
/*! \brief       Transmit final responses.
 *  \details     Transmits (based on a priority based scheme) the available final responses.
 *               One response is sent per cycle.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_TransmitFinalResponses(void);

/**********************************************************************************************************************
 *  vSwUpdM_SrvcRouting_TransmitPendingResponses
 *********************************************************************************************************************/
/*! \brief       Trigger Pending signal to vRpcProxy for pending requests.
 *  \details     Pending signals are triggered in a round-robin scheme.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_TransmitPendingResponses(void);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteCheckLock()
 *********************************************************************************************************************/
/*! \brief       Check if Source has the lock on the local node.
 *  \details     Used in slave role. Checks if the master Source is allowed to access the local node (= slave).
 *  \param[in]   Source                       Source of the request.
 *  \return      VSWUPDM_E_RESPONSE_PRIVILEGE Source does not have the lock and is therefore not allowed to perform actions
 *                                            on the local node.
 *  \return      E_OK                         Source has the lock.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteCheckLock(vSwUpdM_NodeIterType Source);

/**********************************************************************************************************************
 *  vSwUpdM_RemoteStreamCheckPreconditions
 *********************************************************************************************************************/
/*! \brief       Check preconditions for remote stream.
 *  \details     -
 *  \param[in]   Source               Stream source node index.
 *  \param[in]   ProcessHandle        Handle of DataProcess.
 *  \param[in]   Handle               Stream handle.
 *  \param[in]   ExpectedStreamState  Expected stream state.
 *  \return      E_OK                 Preconditions successfully checked.
 *  \return      E_NOT_OK             Preconditions not fulfilled.
 *  \return      VSWUPDM_E_INV_STATE  Invalid state detected.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     remote
 *********************************************************************************************************************/
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamCheckPreconditions(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_RemoteStream_StateType ExpectedStreamState);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 * vSwUpdM_RemoteTransmitResponse
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_RemoteTransmitResponse(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  Std_ReturnType Result)
{
  vSwUpdM_GridSrvc_ServiceIdxType remoteServiceIndex = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;
  uint8_least index = 0u;

  /*#10 Get RemoteServiceId by vSwUpdM ServiceId. */
  do
  {
    if (vSwUpdM_RemoteServiceDefinitions[index].ApiServiceId == ConfirmationService)
    {
      remoteServiceIndex = vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex;
      break;
    }
    index++;
  } while (vSwUpdM_RemoteServiceDefinitions[index].RemoteServiceIndex != VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED);

  if (remoteServiceIndex != VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED)
  {
    /* #20 Transmit Confirmation for the commanded service. */
    vSwUpdM_SrvcRouting_ResultIndicaton(Source, remoteServiceIndex, Result);
  }
  else
  {
    errorId = VSWUPDM_E_INV_STATE;
  }

  vSwUpdM_General_HandleDetError(ConfirmationService, errorId);
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
}/* vSwUpdM_RemoteTransmitResponse */
#endif

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_OpenRxChannel
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_OpenRxChannel(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  vSwUpdM_SrvcRouting_RxChannelIndexType responseBufferIndex = vSwUpdM_SrvcRouting_RxChannelIndex[ServiceIndex];
  vSwUpdM_SrvcRouting_RxChannelPtrType   rxChannel = &vSwUpdM_SrvcRouting_RxChannel[responseBufferIndex];

  vSwUpdM_DevError_Assert((rxChannel->IsOccupied == FALSE), VSWUPDM_DEVERROR_ASSERT_32); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Open a Rx Channel, set ServiceIndex and Origin. */
  rxChannel->RequestOrigin  = RequestOrigin;
  rxChannel->ServiceIndex   = ServiceIndex;
  rxChannel->ExecutionState = VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING;
  rxChannel->IsOccupied     = TRUE;
} /* vSwUpdM_SrvcRouting_OpenRxChannel */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_ResultIndicaton
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ResultIndicaton(
  vSwUpdM_NodeIterType RequestOrigin,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  Std_ReturnType Result)
{
  vSwUpdM_SrvcRouting_RxChannelIndexType responseBufferIndex = vSwUpdM_SrvcRouting_RxChannelIndex[ServiceIndex];
  vSwUpdM_SrvcRouting_RxChannelPtrType   rxChannel = &vSwUpdM_SrvcRouting_RxChannel[responseBufferIndex];

  vSwUpdM_DevError_Assert(vSwUpdM_InitState != VSWUPDM_INIT_STATE_UNINIT, VSWUPDM_DEVERROR_ASSERT_38); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  vSwUpdM_DevError_Assert(responseBufferIndex < VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT, VSWUPDM_DEVERROR_ASSERT_37); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  vSwUpdM_DevError_Assert(((rxChannel->RequestOrigin == RequestOrigin) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
                        && (rxChannel->ServiceIndex  == ServiceIndex)), VSWUPDM_DEVERROR_ASSERT_33); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  vSwUpdM_DevError_Assert(((rxChannel->IsOccupied == TRUE)), VSWUPDM_DEVERROR_ASSERT_46); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  VSWUPDM_DUMMY_STATEMENT(RequestOrigin);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Set RxChannel result. */
  rxChannel->Result         = Result;
  rxChannel->ExecutionState = VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED;
  vSwUpdM_SrvcRouting_NumberOfPendingResponses++;

  /* Store suspended response for check on Resume(). */
  if (Result == VSWUPDM_E_SUSPENDED)
  {
    vSwUpdM_DevError_Assert(vSwUpdM_SrvcRouting_IsRequestResumePending() == FALSE, VSWUPDM_DEVERROR_ASSERT_53); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    vSwUpdM_SrvcRouting_RemoteResumeService = rxChannel->ServiceIndex;
  }

} /* vSwUpdM_SrvcRouting_ResultIndicaton */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_TransmitFinalResponses
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_TransmitFinalResponses(void)
{
  vSwUpdM_SrvcRouting_RxChannelIndexType index;
  Std_ReturnType result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  vSwUpdM_DevError_Assert(vSwUpdM_InitState != VSWUPDM_INIT_STATE_UNINIT, VSWUPDM_DEVERROR_ASSERT_39); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 For each RxChannel: */
  for (index = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO; index < VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT; index++) /* PRQA S 4527 1 */ /* MD_vSwUpdM_Rule10.1_4527_EnumLoop */
  {
    vSwUpdM_SrvcRouting_RxChannelPtrType rxChannel = &vSwUpdM_SrvcRouting_RxChannel[index];

    /* #20 Check if final response available: */
    if ((rxChannel->IsOccupied == TRUE)
     && (rxChannel->ExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED))
    {
      /* #30 Transmit Response. */
      vSwUpdM_GridRpc_ComplexResponseClassSimpleType response;
      vSwUpdM_GridRpc_InitComplexResponseClassSimpleType(rxChannel->ServiceIndex, vSwUpdM_SrvcRouting_RxChannel[index].Result, &response);
      result = vSwUpdM_GridRpc_TransmitResponse(rxChannel->RequestOrigin, VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_FINISHED,
                                                (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType)&response); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */

      /* #31 On success:
       *     Free RxChannel. */
      if (result == E_OK)
      {
        rxChannel->IsOccupied = FALSE;

        vSwUpdM_DevError_Assert(vSwUpdM_SrvcRouting_NumberOfPendingResponses > 0u, VSWUPDM_DEVERROR_ASSERT_36); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
        vSwUpdM_SrvcRouting_NumberOfPendingResponses--;
      }
      /* #32 Abort loop. Only one transmission at a time.*/
      break;
    }
  }
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_SrvcRouting_TransmitFinalResponses */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_TransmitPendingResponses
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_TransmitPendingResponses(void)
{
  vSwUpdM_SrvcRouting_RxChannelPtrType rxChannel = &vSwUpdM_SrvcRouting_RxChannel[vSwUpdM_SrvcRouting_CurrentRxChannelIndex]; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */

  vSwUpdM_DevError_Assert(vSwUpdM_InitState != VSWUPDM_INIT_STATE_UNINIT, VSWUPDM_DEVERROR_ASSERT_40); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* #10 Apply Round-Robin scheme:
   *     If current RxChannel is occupied: */
  if ((rxChannel->IsOccupied     == TRUE)
   && (rxChannel->ExecutionState == VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING))
  {
    /* #20 Trigger Pending signal. */
    vSwUpdM_GridRpc_ComplexResponseClassSimpleType response;
    vSwUpdM_GridRpc_InitComplexResponseClassSimpleType(rxChannel->ServiceIndex,
                                                       rxChannel->Result, &response);
    /* The result is ignored here. If transmitting the PENDING fails, the next PENDING for this RxChannel will be triggered after RXCHANNELINDEX_COUNT cycles.
     * This ensures that one clogged channel does not affect the others, each RxChannel gets an attempt every RXCHANNELINDEX_COUNT cycles.
     */
    (void) vSwUpdM_GridRpc_TransmitResponse(rxChannel->RequestOrigin,
                                            VSWUPDM_GRIDRPC_SERVICEXECUTIONSTATE_PENDING,
                                            (vSwUpdM_GridRpc_ComplexResponseClassBasePtrType) &response); /* PRQA S 0310 */ /* MD_vSwUpdM_Rule11.3_0310_ServiceParameterCast */
  }
  /* #30 Switch to next RxChannel. */
  vSwUpdM_SrvcRouting_CurrentRxChannelIndex++;  /* PRQA S 4527 1 */ /* MD_vSwUpdM_Rule10.1_4527_EnumLoop */

  /* Limit CurrentRxCHannelIndex to valid range. */
  if (vSwUpdM_SrvcRouting_CurrentRxChannelIndex == VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT)
  {
    vSwUpdM_SrvcRouting_CurrentRxChannelIndex = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO;
  }
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_SrvcRouting_TransmitPendingResponses */

/**********************************************************************************************************************
 * vSwUpdM_RemoteCheckLock
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteCheckLock(vSwUpdM_NodeIterType Source)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Check if the requester has the lock. */
  if (vSwUpdM_RemoteLockIsGrantedTo != Source)
  {
    /* The requester has no lock. */
    retVal = VSWUPDM_E_RESPONSE_PRIVILEGE;
  }

  return retVal;
}/* vSwUpdM_RemoteCheckLock */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_HandleServiceState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_HandleServiceState(vSwUpdM_ExctSchedule_ServiceStateType ServiceState, vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* #10 Check if ServiceState is RESUME and if so, if this service is expected to get resumed. */
  if (ServiceState == VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RESUME)
  {
    if (vSwUpdM_SrvcRouting_RemoteResumeService == ServiceIndex)
    {
      vSwUpdM_SrvcRouting_RemoteResumeService = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* vSwUpdM_SrvcRouting_HandleServiceState */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_MainChannelServicePreparation
 *********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 /*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL_INLINE FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_MainChannelServicePreparation(vSwUpdM_NodeIterType Source, vSwUpdM_ExctSchedule_ServiceStateType ServiceState, vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check Lock: */
  if (vSwUpdM_RemoteCheckLock(Source) == E_OK)
  {
    /* #20 Check ServiceState: */
    if (vSwUpdM_SrvcRouting_HandleServiceState(ServiceState, ServiceIndex) == E_OK)
    {
      /* #30 Acquire response buffer. */
      vSwUpdM_SrvcRouting_OpenRxChannel(Source, ServiceIndex);

      /* #40 If request is not a RESUME request:
       *     Request is processed regularly.
       */
      if (ServiceState == VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN)
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* vSwUpdM_SrvcRouting_MainChannelServicePreparation */


/**********************************************************************************************************************
 * vSwUpdM_RemoteStreamCheckPreconditions
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSWUPDM_LOCAL FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_RemoteStreamCheckPreconditions(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_RemoteStream_StateType ExpectedStreamState)
{
  Std_ReturnType result = E_OK;

  /* #10 Check if ProcessHandle is the handle of the active data process. */
  if ((!vSwUpdM_IsProcessHandleUsedOfDataProcesses(vSwUpdM_ProcessData.ProcessId))
    || (ProcessHandle != vSwUpdM_GetProcessHandleOfDataProcesses(vSwUpdM_ProcessData.ProcessId)))
  {
    result = E_NOT_OK;
  }

  /* #20 Check if stream's Handle is in the range of the configured streams. */
  if (result == E_OK)
  {
    if (Handle >= (vSwUpdM_RemoteStreamHandleType)VSWUPDM_REMOTESTREAMHANDLE_SIZE)
    {
      result = E_NOT_OK;
    }
  }

  /* #30 Check if the source fits to the stream's configured source or target settings. */
  if (result == E_OK)
  {
    if (vSwUpdM_RemoteStream_List[Handle].Source == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
    {
      if (vSwUpdM_RemoteStream_List[Handle].Target != Source)
      {
        result = E_NOT_OK;
      }
    }
    else if (vSwUpdM_RemoteStream_List[Handle].Target == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
    {
      if (vSwUpdM_RemoteStream_List[Handle].Source != Source)
      {
        result = E_NOT_OK;
      }
    }
    else
    {
      result = VSWUPDM_E_INV_STATE;
    }
  }

  /* #40 Check if the stream is in a state where this request is expected. */
  if (result == E_OK)
  {
    if (vSwUpdM_RemoteStream_List[Handle].State != ExpectedStreamState)
    {
      result = E_NOT_OK;
    }
  }

  return result;
  /* PRQA S 6010, 6030, 6060 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STPAR */
} /* vSwUpdM_RemoteStreamCheckPreconditions */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_Init(void)
{
  vSwUpdM_SrvcRouting_RxChannelIndexType index;

  /* #10 Initialize RxChannels. */
  for (index = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO; index < VSWUPDM_SRVCROUTING_RXCHANNELINDEX_COUNT; index++) /* PRQA S 4527 1 */ /* MD_vSwUpdM_Rule10.1_4527_EnumLoop */
  {
    vSwUpdM_SrvcRouting_RxChannel[index].IsOccupied = FALSE;
  }
  vSwUpdM_SrvcRouting_CurrentRxChannelIndex = VSWUPDM_SRVCROUTING_RXCHANNELINDEX_ZERO;
  vSwUpdM_SrvcRouting_NumberOfPendingResponses = 0u;

  vSwUpdM_SrvcRouting_RemoteResumeService = VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED;
} /* vSwUpdM_SrvcRouting_Init */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_HandleRxChannels
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_HandleRxChannels(void)
{
  /* #10 Transmit available final responses regarding RxChannels priorities. */
  vSwUpdM_SrvcRouting_TransmitFinalResponses();

  /* #20 Trigger pending responses in Round-Robin scheme. */
  vSwUpdM_SrvcRouting_TransmitPendingResponses();
} /* vSwUpdM_SrvcRouting_HandleRxChannels */

/**********************************************************************************************************************
 * vSwUpdM_UlConfirmation
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_UlConfirmation(
  vSwUpdM_ServiceIdType ConfirmationService,
  vSwUpdM_NodeIterType Source,
  Std_ReturnType Result)
{
  VSWUPDM_DUMMY_STATEMENT(Source); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 If a valid service ID is given: */
  if (ConfirmationService != VSWUPDM_SID_NONE)
  {

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON)
    /* #11 If the origin of the request is a remote parent node:
     *     Transmit remote response. */
    if(Source != (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
    {

      vSwUpdM_RemoteTransmitResponse(ConfirmationService, Source, Result);
    }
    else
#endif
    {
      /* #12 Else:
       *     call upper-layer confirmation function with given result. */
      UL_vSwUpdMConfirmation(ConfirmationService, Result);
    }
  }
} /* vSwUpdM_UlConfirmation */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_IsRequestResumePending
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_SrvcRouting_IsRequestResumePending(void)
{
  boolean retVal;
  /* #10 Evaluate vSwUpdM_SrvcRouting_RemoteResumeService. */
  if (vSwUpdM_SrvcRouting_RemoteResumeService == VSWUPDM_GRIDSRVC_SERVICEIDX_UNDEFINED)
  {
    retVal = FALSE;
  }
  else
  {
    retVal = TRUE;
  }

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_Internal_StartStream
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_StartStream(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a segment is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no data stream is pending. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check parameter "StreamInfo". */
  if (StreamInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    boolean explicitRestartHandling = FALSE;
    vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_EntityData.OpenObjects.Segment;
    retVal = E_OK; /* PRQA S 2982 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Set meta-state as default to "local". */
      vSwUpdM_TypeOfIntModeType  internalMode = vSwUpdMConf_vSwUpdMModeType_Local;

#if (VSWUPDM_MULTICONTROLLER_SUPPORT == STD_ON) && (VSWUPDM_LOCALINSTANCE_ACTS_AS_MASTER == STD_ON)
      /* #110 If local node is the parent and region is remote,
       *   Set meta-state to "remote". */
      if(vSwUpdM_Grid_LocalNodeIsParent() == TRUE)
      {
        vSwUpdM_NodeGroupOwnersIdxOfRegionType nodeGroupIdx = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(vSwUpdM_GetVarRegions(segment->RegionIdxOfVarSegments).RegionIDOfVarRegions);
        /* Region is remote if Group is > 1 OR does not contain local node. */
        if ((vSwUpdM_GetNNodesOfNodeGroup(nodeGroupIdx) > 1u) || (!vSwUpdM_IsWithLocalNodeOfNodeGroup(nodeGroupIdx)))
        {
          internalMode = vSwUpdMConf_vSwUpdMModeType_Remote;
        }
      }
#endif

      /* #120 Open pipe for data stream processing. */
      retVal = vSwUpdM_Stream_Open(vSwUpdM_EntityData.OpenIds.SegmentId, &vSwUpdM_EntityData.OpenIds, internalMode, StreamInfo->Operation);
    }

    if (retVal == E_OK)
    {
      /* #130 Initialize resume information for ProcessStreamData sequence. */
      vSwUpdM_ResumeInfo_UpdateWriteService(vSwUpdM_EntityData.OpenIds.PartitionState, segment, VSWUPDM_SID_PROCESS_STREAM_DATA);

      /* #140 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #150 Trigger dispatching of job(s) to start the data stream. */
      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_START_STREAM, VSWUPDM_EXECCTRL_SEQUENCEIDX_START_STREAM, VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM,
                                vSwUpdM_Segment_GetRegionOwnerGroupIndex(vSwUpdM_EntityData.OpenIds.SegmentId),
                                VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);

      if (retVal == E_OK)
      {
        /* #151 Update global stream data information. */
        vSwUpdM_StreamData.Length = 0u;
        vSwUpdM_StreamData.MaxLength = StreamInfo->InputLength;
        vSwUpdM_StreamData.Remainder = StreamInfo->InputLength;
        vSwUpdM_StreamData.Operation = StreamInfo->Operation;
        vSwUpdM_StreamData.State = VSWUPDM_STREAM_STATE_PENDING;
        vSwUpdM_StreamData.RestartHandling = explicitRestartHandling;
      }
      /* #160 If spawning of job failed
        *   Reset resume information */
      else
      {
        vSwUpdM_ResumeInfo_ResetState();
      }

      /* #170 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_START_STREAM, errorId);

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 2 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_StartStream */

/**********************************************************************************************************************
 * vSwUpdM_Internal_ProcessStreamData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ProcessStreamData(
  vSwUpdM_StreamLengthType StreamLength,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType   retVal   = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a data stream is pending, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM, VSWUPDM_STATE_CHECK_PIPELINED, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_VarSegmentsPtrType  segment = vSwUpdM_EntityData.OpenObjects.Segment;

      /* #100 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 If stream defined a maximum input length */
      if (vSwUpdM_StreamData.MaxLength != VSWUPDM_UNDEFINED_LENGTH)
      {
        /* #111 Verify that provided input length doesn't exceed the remainder of the data stream.
         * Otherwise: Update remainder. */
        if (StreamLength > vSwUpdM_StreamData.Remainder)
        {
          retVal = VSWUPDM_E_INVALID_STREAM_STATE;
        }
        else
        {
          vSwUpdM_StreamData.Remainder -= StreamLength;
        }
      }

#if (VSWUPDM_PIPELINED_PROGRAMMING == STD_ON)
      /* #200 Evaluate possible pending pipelined operation result. */
      switch (vSwUpdM_PipelinedProgramming.State)
      {
        /* #210 If pipelined operation is idle or has finished */
        case VSWUPDM_PIPELINED_STATE_IDLE:
        case VSWUPDM_PIPELINED_STATE_DONE:
        {
          /* #211 Reset pipelined operation to idle. */
          vSwUpdM_PipelinedProgramming.State = VSWUPDM_PIPELINED_STATE_IDLE;

          /* #212 Report potential failed pipelined operation. */
          if (vSwUpdM_PipelinedProgramming.PreviousWriteResult != E_OK)
          {
            retVal = vSwUpdM_PipelinedProgramming.PreviousWriteResult;
          }

          break;
        }
        default:
        /* #220 Otherwise: Nothing to do. */
        {
          break;
        }
      }
#endif /* VSWUPDM_PIPELINED_PROGRAMMING == STD_ON */

      if (retVal == E_OK)
      {
        vSwUpdM_JobPtrType spawnedJob;

        /* #300 Initialize resume information for ProcessStreamData sequence. */
        vSwUpdM_ResumeInfo_UpdateWriteService(vSwUpdM_EntityData.OpenIds.PartitionState, segment, VSWUPDM_SID_PROCESS_STREAM_DATA);

        /* #310 Spawn job to process provided stream data. */
        spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_PROCESS_STREAM_DATA, VSWUPDM_JOB_OPERATION_DEFAULT,
                                       (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_PROCESS_STREAM_DATA, NULL_PTR, Source);

        /* #320 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (retVal == E_OK)
        {
          /* #321 Update global stream data information with provided length. */
          vSwUpdM_StreamData.Length += StreamLength;

          /* #322 Pass open entity IDs to job. */
          spawnedJob->EntityIds = vSwUpdM_EntityData.OpenIds;

          /* #323 Pass length to be processed as used space of the virtual input buffer of the job. */
          (void) vSwUpdM_Buffer_InitAndAddData(spawnedJob->InputBuffer, NULL_PTR, StreamLength);
        }
        /* #330 If spawning of job failed
         *   Reset resume information */
        else
        {
          vSwUpdM_ResumeInfo_ResetState();
        }
      }

      /* #400 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_PROCESS_STREAM_DATA, errorId);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Internal_ProcessStreamData */

/**********************************************************************************************************************
 * vSwUpdM_Internal_EndStream
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EndStream(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a data stream is pending, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM, VSWUPDM_STATE_CHECK_PIPELINED, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {

      /* #110 If stream defined a maximum input length */
      if (vSwUpdM_StreamData.MaxLength != VSWUPDM_UNDEFINED_LENGTH)
      {
        /* #111 Verify that all announced data was provided. */
        if (vSwUpdM_StreamData.Remainder != 0u)
        {
          retVal = E_NOT_OK;
        }
      }

      if (retVal == E_OK)
      {
        /* PRQA S 3679 2 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
        vSwUpdM_VarSegmentsPtrType varSegment = vSwUpdM_GetAddrVarSegments(vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId);
        vSwUpdM_VarRegionsPtrType  varRegion = vSwUpdM_GetAddrVarRegions(varSegment->RegionIdxOfVarSegments);

        /* #120 Initialize resume information for ProcessStreamData sequence. */
        vSwUpdM_ResumeInfo_UpdateWriteService(vSwUpdM_EntityData.OpenIds.PartitionState,
                                              vSwUpdM_EntityData.OpenObjects.Segment, VSWUPDM_SID_PROCESS_STREAM_DATA);

        /* #130 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #140 Trigger dispatching of job(s) to end the current data stream. */
        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_END_STREAM, VSWUPDM_EXECCTRL_SEQUENCEIDX_END_STREAM, VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM,
                                  vSwUpdM_GetNodeGroupOwnersIdxOfRegion(varRegion->RegionIDOfVarRegions),
                                  VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);

        if (retVal == E_OK)
        {
          /* #150 Set state of global stream data information to idle. */
          vSwUpdM_StreamData.State = VSWUPDM_STREAM_STATE_IDLE;
        }
        /* #160 If spawning of job failed
         *   Reset resume information */
        else
        {
          vSwUpdM_ResumeInfo_ResetState();
        }

        /* #170 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_END_STREAM, errorId);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Internal_EndStream */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ValidatePartition()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ValidatePartition(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Trigger dispatching of job(s) to validate the currently opened partition. */
      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_VALIDATE_PARTITION, VSWUPDM_EXECCTRL_SEQUENCEIDX_VALIDATE_PARTITION, VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID,
                                vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_VALIDATE_PARTITION, errorId);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Internal_ValidatePartition */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ValidatePartition()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_InvalidatePartition(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Trigger dispatching of job(s) to invalidate the currently opened partition. */
      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_INVALIDATE_PARTITION, VSWUPDM_EXECCTRL_SEQUENCEIDX_INVALIDATE_PARTITION, VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID, vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INVALIDATE_PARTITION, errorId);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Internal_InvalidatePartition */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SyncPartition()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SyncPartition(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Trigger dispatching of job(s) to sync to the currently opened partition. */
      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_SYNC_PARTITION, VSWUPDM_EXECCTRL_SEQUENCEIDX_SYNC_PARTITION, VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION,
                                vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_SYNC_PARTITION, errorId);

  return retVal;
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vSwUpdM_Internal_SyncPartition */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CheckPartitionConsistency()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CheckPartitionConsistency(
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(ProcessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check ProcessInfo for validity. */
  if (ProcessInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  {
  /* ----- Implementation ------------------------------------------------- */
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Trigger dispatching of job(s) to check the consistency of the currently opened partition. */
      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY, VSWUPDM_EXECCTRL_SEQUENCEIDX_CHECK_PARTITION_CONSISTENCY, VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION,
                                vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_CHECK_PARTITION_CONSISTENCY, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Internal_CheckPartitionConsistency */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SwapActivePartition()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SwapActivePartition(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 If opened partition is swappable and is marked as valid */
      if ((vSwUpdM_EntityData.OpenObjects.Partition->SwappableOfVarPartitions == TRUE)   /* PRQA S 4558 2 */ /* MD_MSR_AutosarBoolean */
        && (vSwUpdM_EntityData.OpenObjects.Partition->DynamicAttributesOfVarPartitions.IsValid == TRUE))   /* PRQA S 4558 2 */ /* MD_MSR_AutosarBoolean */
      {
        /* #110 Trigger dispatching of job(s) to swap to the currently opened partition. */
        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_SWAP_ACTIVE_PARTITION, VSWUPDM_EXECCTRL_SEQUENCEIDX_SWAP_ACTIVE_PARTITION, VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION,
                                  vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_SWAP_ACTIVE_PARTITION, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Internal_SwapActivePartition */

/**********************************************************************************************************************
 * vSwUpdM_Internal_OpenPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenPartition(
  vSwUpdM_PartitionStateType State,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal   = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId  = VSWUPDM_E_NO_ERROR;
  vSwUpdM_PartitionIdType id = VSWUPDM_INVALID_ID;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and initialized. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no module is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
   else
  /* #30 Check that partition ID is valid. */
  if (vSwUpdM_Part_IsPartitionStateValid(State) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      retVal = vSwUpdM_Part_GetIdByState(&id, State);
    }

    if(retVal == E_OK)
    {
      /* #100 If requested partition isn't opened yet */
      if (vSwUpdM_EntityData.OpenIds.PartitionId != id)
      {
        /* #110 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #120 Set ID and state of opened partition and point to partition in entity data structure. */
        vSwUpdM_EntityData.OpenIds.PartitionId    = id;
        vSwUpdM_EntityData.OpenIds.PartitionState = State;
        vSwUpdM_EntityData.OpenObjects.Partition  = vSwUpdM_GetAddrVarPartitions(id);

        /* #130 Trigger dispatching of job(s) to open the requested partition. */
        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_OPEN_PARTITION, VSWUPDM_EXECCTRL_SEQUENCEIDX_OPEN_PARTITION, VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION,
                                  vSwUpdM_GetBroadcastGroup(), VSWUPDM_GRIDNODE_INVALID_NODE, Source, vSwUpdM_EntityData.OpenIds);

        /* #140 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
      /* #200 Otherwise, nothing to be done.
       *   Directly issue confirmation to upper-layer. */
      else
      {
        vSwUpdM_UlConfirmation(VSWUPDM_SID_OPEN_PARTITION, Source, E_OK);
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_OPEN_PARTITION, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_OpenPartition */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_OpenModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #30 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #-- Otherwise: */
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 If requested module is already opened
       *   Directly issue confirmation to upper-layer. */
      if (vSwUpdM_EntityData.OpenIds.ModuleId == Id)
      {
        retVal = E_OK;
        vSwUpdM_UlConfirmation(VSWUPDM_SID_OPEN_MODULE, Source, retVal);
      }
      /* #110 Otherwise */
      else
      {
        vSwUpdM_EntityIdsType entityIds;

        /* #120 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #130 Trigger dispatching of job(s) to open the requested module. */
        entityIds           = vSwUpdM_EntityData.OpenIds;
        entityIds.ModuleId  = Id;

        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_OPEN_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_OPEN_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE,
                                  vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

        /* #140 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_OPEN_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_OpenModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CloseModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CloseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Ensure that requested module is opened. */
      if (vSwUpdM_EntityData.OpenIds.ModuleId == Id)
      {
        vSwUpdM_EntityIdsType entityIds;

        /* #110 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #120 Trigger dispatching of job(s) to close the requested module. */
        entityIds          = vSwUpdM_EntityData.OpenIds;
        entityIds.ModuleId = Id;

        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_CLOSE_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_CLOSE_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE,
                                  vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

        /* #130 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_CLOSE_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_CloseModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ValidateModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ValidateModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #30 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_ModuleDynamicAttributesType currentAttributes = { 0 };

      /* #100 Enter critical section to ensure exclusive access of module attributes. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      retVal = vSwUpdM_Module_GetAttributes(Id, vSwUpdM_EntityData.OpenIds.PartitionId, &currentAttributes);

      /* #110 Leave critical section ensuring exclusive access of module attributes. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();

      if (retVal == E_OK)
      {
        /* #120 If given validity doesn't match the current module instance validity */
        if (currentAttributes.IsValid != VSWUPDM_VALIDITY_VALID)
        {
          /* #130 If module was not successfully verified before
           *   Precondition not fulfilled, report error. */
          if (currentAttributes.State != VSWUPDM_MODULE_STATE_VERIFIED)
          {
            retVal = E_NOT_OK;
          }

          if (retVal == E_OK)
          {
            vSwUpdM_EntityIdsType entityIds;

            /* #200 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #210 Trigger dispatching of job(s) to validate the requested module. */
            entityIds          = vSwUpdM_EntityData.OpenIds;
            entityIds.ModuleId = Id;

            retVal = vSwUpdM_Dispatch(VSWUPDM_SID_VALIDATE_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_VALIDATE_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE,
                                      vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

            /* #220 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
          }
        }
        /* #300 Otherwise */
        else
        {
          /* #310 Update result of potential parent job and directly issue potential (positive) confirmation to upper-layer */
          vSwUpdM_Job_SetChildResultAndConfirm(NULL_PTR, Source, VSWUPDM_SID_VALIDATE_MODULE, retVal);
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_VALIDATE_MODULE, errorId);

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_ValidateModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_InvalidateModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_InvalidateModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #30 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_EntityIdsType entityIds;

      /* #100 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 trigger dispatching of job(s) to invalidate the requested module. */
      entityIds          = vSwUpdM_EntityData.OpenIds;
      entityIds.ModuleId = Id;

      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_INVALIDATE_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_INVALIDATE_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE,
                                vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

      /* #120 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INVALIDATE_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_InvalidateModule */

/**********************************************************************************************************************
 * vSwUpdM_Internal_EraseModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EraseModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_ModuleStateType moduleState;

      moduleState = VSWUPDM_MODULE_STATE_UNDEFINED;

      /* #100 Evaluate state of module instance in opened partition. */
      retVal = vSwUpdM_Module_GetStateByPartition(&moduleState, Id, vSwUpdM_EntityData.OpenIds.PartitionId);

      if (retVal == E_OK)
      {
        /* #110 If module is already erased, nothing to be done. */
        if (moduleState == VSWUPDM_MODULE_STATE_ERASED)
        {
            /* #111 Directly issue confirmation to upper-layer. */
            retVal = E_OK;
            vSwUpdM_UlConfirmation(VSWUPDM_SID_ERASE_MODULE, Source, retVal);
        }
        /* #200 Otherwise */
        else
        {
          /* #201 Check whether programming attempts are exceeded. */
          retVal = vSwUpdM_Module_CheckProgrammingAttempts(Id, vSwUpdM_EntityData.OpenIds.PartitionId);

          if (retVal == E_OK)
          {
            vSwUpdM_EntityIdsType entityIds;

            /* #210 Initialize resume information for EraseModule service. */
            vSwUpdM_ResumeInfo_InitModuleService(Id, VSWUPDM_SID_ERASE_MODULE);

            /* #220 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #230 Trigger dispatching of job(s) to validate the requested module. */
            entityIds = vSwUpdM_EntityData.OpenIds;
            entityIds.ModuleId = Id;

            retVal = vSwUpdM_Dispatch(VSWUPDM_SID_ERASE_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_ERASE_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE,
                                      vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

            /* #240 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();

            /* #250 If dispatching of job(s) failed
             *   Reset resume information. */
            if (retVal != E_OK)
            {
              vSwUpdM_ResumeInfo_ResetState();
            }
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ERASE_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_EraseModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_FinalizeModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_FinalizeModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 If requested module is instantiated in opened partition */
      if (vSwUpdM_Module_IsModuleInstantiatedInPartition(Id, vSwUpdM_EntityData.OpenIds.PartitionId) == TRUE)
      {
        vSwUpdM_EntityIdsType entityIds;

        /* #110 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #120 Trigger dispatching of job(s) to finalize the requested module. */
        entityIds          = vSwUpdM_EntityData.OpenIds;
        entityIds.ModuleId = Id;

        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_FINALIZE_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_FINALIZE_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE, vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

        /* #130 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_FINALIZE_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_FinalizeModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_VerifyModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_VerifyModule(
  vSwUpdM_ModuleIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(ProcessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #50 Check ProcessInfo for validity. */
  if (ProcessInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_ModuleStateType moduleState;

      /* #100 Check that module is in state FINALIZED. */
      retVal = vSwUpdM_Module_GetStateByPartition(&moduleState, Id, vSwUpdM_EntityData.OpenIds.PartitionId);

      if (retVal == E_OK)
      {
        if (moduleState != VSWUPDM_MODULE_STATE_FINALIZED)
        {
          retVal = E_NOT_OK;
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
          errorId = VSWUPDM_E_INV_OPERATION_STATE;
#endif
        }
      }

      if (retVal == E_OK)
      {
        vSwUpdM_EntityIdsType         entityIds;

        /* #110 If verify module pipe is configured: */
#if (VSWUPDM_EXISTS_VERIFY_MODULE_TYPEOFDATAPROCESSES == STD_ON)
        vSwUpdM_DataProcessesIterType processId;

        /* #120 Look for pipe of correct type. */
        for (processId = 0; processId < vSwUpdM_GetSizeOfDataProcesses(); processId++)
        {
          if (vSwUpdM_GetTypeOfDataProcesses(processId) == VSWUPDM_VERIFY_MODULE_TYPEOFDATAPROCESSES)
          {
            break;
          }
        }

        if (processId >= vSwUpdM_GetSizeOfDataProcesses())
        {
          retVal = E_NOT_OK;
        }
        else
        {
          retVal = E_OK;
        }

        if (retVal == E_OK)
#endif
        {
          vSwUpdM_ProcessCountType index;
          /* Trigger the initialization of the AvailableLength only if current processing is triggered by the local node.
             In case of a remote node OutputData is a NULL_PTR. */
          if (Source == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
          {
            /* #130 Initialize AvailableLength for every output buffer. */
            for (index = 0u; index < ProcessInfo->OutputCount; index++)
            {
              ProcessInfo->OutputData[index].AvailableLength = 0u;
            }
          }

          /* #140 Enter critical section to ensure exclusive access of state and job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          entityIds = vSwUpdM_EntityData.OpenIds;
          entityIds.ModuleId = Id;

          /* #150 Trigger dispatching of job(s) to verify the requested module. */
          retVal = vSwUpdM_Dispatch(VSWUPDM_SID_VERIFY_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_VERIFY_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE,
                                    vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

#if (VSWUPDM_EXISTS_VERIFY_MODULE_TYPEOFDATAPROCESSES == STD_ON)
          /* #160 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
          if (retVal == E_OK)
          {
            /* Remember verify parameters. */
            vSwUpdM_Pipe_PrepareProcessData(vSwUpdM_ProcessScope_Module, (vSwUpdM_ProcessIdType)processId, &vSwUpdM_ProcessConfig_VerifyModule, ProcessInfo);
          }
#endif

          /* #170 Leave critical section ensuring exclusive access of state and job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_VERIFY_MODULE, errorId);

  return retVal;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_VerifyModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ProcessModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ProcessModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(ModuleId) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #50 Check that ProcessInfo is provided. */
  if (ProcessInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
#if (VSWUPDM_EXISTS_PROCESS_MODULE_TYPEOFDATAPROCESSES == STD_ON)
  else
  /* #60 Check that process ID is valid. */
  if (ProcessId >= vSwUpdM_GetSizeOfDataProcesses())
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
#endif
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Determine the module state-specific processing operation mode. */
      vSwUpdM_ProcNodeOperationType procOperation = vSwUpdM_Pipe_EvalProcessOperation(&vSwUpdM_ProcessConfig_ProcessModule,
        vSwUpdM_EntityData.OpenIds.PartitionId, ModuleId);

      switch (procOperation)
      {
        case VSWUPDM_PROC_NODE_OPERATION_START:
        case VSWUPDM_PROC_NODE_OPERATION_CLEAN_RESTART:
        case VSWUPDM_PROC_NODE_OPERATION_DIRTY_RESTART:
        /* #200 If module is in a valid state for processing. */
        {
          vSwUpdM_EntityIdsType entityIds;
          vSwUpdM_ProcessCountType index;

          /* Trigger the initialization of the AvailableLength only if current processing is triggered by the local node.
             In case of a remote node OutputData is a NULL_PTR. */
          if (Source == (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
          {
            /* #210 Initialize AvailableLength for every output buffer. */
            for (index = 0u; index < ProcessInfo->OutputCount; index++)
            {
              ProcessInfo->OutputData[index].AvailableLength = 0u;
            }
          }

          /* #220 Initialize resume information for ProcessModule service. */
          vSwUpdM_ResumeInfo_InitModuleService(ModuleId, VSWUPDM_SID_PROCESS_MODULE);

          /* #230 Enter critical section to ensure exclusive access of state and job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          entityIds = vSwUpdM_EntityData.OpenIds;
          entityIds.ModuleId = ModuleId;

          /* #240 Trigger dispatching of job(s) to verify the requested module. */
          retVal = vSwUpdM_Dispatch(VSWUPDM_SID_PROCESS_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_PROCESS_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE,
                                    vSwUpdM_GetNodeGroupOwnersIdxOfModule(ModuleId), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

          /* #250 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
          if (retVal == E_OK)
          {
            /* Remember data process parameters. */
            vSwUpdM_Pipe_PrepareProcessData(vSwUpdM_ProcessScope_Module, ProcessId, &vSwUpdM_ProcessConfig_ProcessModule, ProcessInfo);
          }
          /* #260 If spawning of job failed
           *   Reset resume information. */
          else
          {
            vSwUpdM_ResumeInfo_ResetState();
          }

          /* #270 Leave critical section ensuring exclusive access of state and job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();

          break;
        }
        case VSWUPDM_PROC_NODE_OPERATION_NONE:
        /* #300 If module processing is already finished, nothing to be done. */
        {
          /* #310 Directly issue confirmation to upper-layer. */
          vSwUpdM_UlConfirmation(VSWUPDM_SID_PROCESS_MODULE, Source, E_OK);
          retVal = E_OK;
          break;
        }
        default:
        /* #400 Otherwise: Report error. */
        {
          break;
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_PROCESS_MODULE, errorId);

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_ProcessModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_SyncModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_SyncModule(
  vSwUpdM_ModuleIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #30 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_EntityIdsType entityIds;

      /* #110 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #120 Trigger dispatching of job(s) to synchronize the content of the requested module instance
       *   in the active partition to the instance in the opened partition. */
      entityIds = vSwUpdM_EntityData.OpenIds;
      entityIds.ModuleId = Id;

      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_SYNC_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_SYNC_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE,
                                vSwUpdM_GetNodeGroupOwnersIdxOfModule(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

      /* #130 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_SYNC_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_SyncModule */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_IndicateWriteToModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_IndicateWriteToModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that module ID is allowed. */
  if (vSwUpdM_Module_IsModuleIdAllowed(ModuleId) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_ModuleStateType moduleState;

      /* #100 Evaluate state of module instance in opened partition. */
      if (vSwUpdM_Module_GetStateByPartition(&moduleState, ModuleId, vSwUpdM_EntityData.OpenIds.PartitionId) == E_OK)
      {
        switch (moduleState)
        {
          case VSWUPDM_MODULE_STATE_ERASED:
          case VSWUPDM_MODULE_STATE_CLEAN:
          /* #110 If module state is "erased" or "clean" */
          {
            vSwUpdM_EntityIdsType entityIds;

            /* #120 Enter critical section to ensure exclusive access of state and job queue. */
            VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #130 Trigger dispatching of job(s) to update module and region states of the requested module instance. */
            entityIds          = vSwUpdM_EntityData.OpenIds;
            entityIds.ModuleId = ModuleId;

            retVal = vSwUpdM_Dispatch(VSWUPDM_SID_INDICATE_WRITE_TO_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_INDICATE_WRITE_TO_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE,
                                      vSwUpdM_GetNodeGroupOwnersIdxOfModule(ModuleId), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

            /* #140 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();

            break;
          }
          default:
          /* #200 Otherwise: Report error. */
          {
            retVal = E_NOT_OK;

            break;
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INDICATE_WRITE_TO_MODULE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_IndicateWriteToModule */

/**********************************************************************************************************************
 * vSwUpdM_Internal_Start
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Start(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that source node doesn't exceeds valid range. */
  if (Source >= vSwUpdM_GetSizeOfNode())
  {
    errorId = VSWUPDM_E_OUT_OF_RANGE;
  }
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_StateType state = VSWUPDM_STATE_IDLE;

      retVal = E_OK;

      /* #100 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 If component was previously shut down.
       *   Trigger reinitialization. */
      if (vSwUpdM_GlobalState == VSWUPDM_STATE_SHUT_DOWN)
      {
        retVal = vSwUpdM_Init_Start(Source);
      }

      if (retVal == E_OK)
      {
        retVal = vSwUpdM_GetState(&state);
      }

      if (retVal == E_OK)
      {
        /* #120 Evaluate current operation state. */
        switch (state)
        {
          case VSWUPDM_STATE_INIT_PENDING:
          case VSWUPDM_STATE_IDLE:
          /* #130 If initialization is pending or component is idle. */
          {
             /* #131 Enter critical section to ensure exclusive access of state and job queue. */
             VSWUPDM_ENTER_CRITICAL_SECTION();

            /* #132 Spawn job to wait until component is initialized. */
            (void)vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_START, VSWUPDM_JOB_OPERATION_DEFAULT, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_START, NULL_PTR, Source);

            /* #133 Leave critical section ensuring exclusive access of state and job queue. */
            VSWUPDM_LEAVE_CRITICAL_SECTION();
            break;
          }
          default:
          /* #140 Otherwise: Invalid state. */
          {
            errorId = VSWUPDM_E_INV_OPERATION_STATE;
            retVal  = E_NOT_OK;

            break;
          }
        }
      }

      /* #150 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_START, errorId);

  return retVal;
} /* vSwUpdM_Internal_Start */

/**********************************************************************************************************************
 * vSwUpdM_Internal_Shutdown
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Shutdown(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized or initialization is pending. */
  if (((vSwUpdM_InitState == VSWUPDM_INIT_STATE_UNINIT) || (vSwUpdM_InitState == VSWUPDM_INIT_STATE_PENDING))
    && (vSwUpdM_GlobalState == VSWUPDM_STATE_IDLE))
  {
    errorId = VSWUPDM_E_NOT_INITIALIZED;
  }
  /* #20 Check that source node doesn't exceeds valid range. */
  else
  if (Source >= vSwUpdM_GetSizeOfNode())
  {
    errorId = VSWUPDM_E_OUT_OF_RANGE;
  }
  else  /* #-- Otherwise: */
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_JobOperationType operation = VSWUPDM_JOB_OPERATION_DEFAULT;

      /* #100 Enter critical section to ensure exclusive access of state. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 Evaluate global state */
      switch (vSwUpdM_GlobalState)
      {
        case VSWUPDM_STATE_SUSPEND_PENDING:
        case VSWUPDM_STATE_SUSPENDING:
        /* #120 If suspend is pending or in progress
         *   Nothing to be done. */
        {
          break;
        }
        case VSWUPDM_STATE_SUSPENDED:
        /* #130 If job processing is already suspended
         *   Leave suspended state and change to idle state.
         *   Necessary for execution of shutdown job. */
        {
          vSwUpdM_GlobalState = VSWUPDM_STATE_IDLE;
          break;
        }
        case VSWUPDM_STATE_SHUT_DOWN:
        case VSWUPDM_STATE_SHUT_DOWN_PENDING:
        /* #140 If shutdown is pending or component is already shut down
         *   Invalid state. */
        {
          errorId = VSWUPDM_E_INV_OPERATION_STATE;
          break;
        }
        default:
        /* #150 Otherwise, in normal operation state.
         *   Request suspend of operation. */
        {
          operation = VSWUPDM_JOB_OPERATION_SHUTDOWN_SUSPEND;
          break;
        }
      }

      if (errorId == VSWUPDM_E_NO_ERROR)
      {
        /* #200 Spawn job to shut down component. */
        (void)vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_SHUTDOWN, operation, (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_SHUTDOWN, NULL_PTR, Source);
      }
      else
      {
        retVal = E_NOT_OK;
      }

      /* #210 Leave critical section to ensure exclusive access of state. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_SHUTDOWN, errorId);

  return retVal;
} /* vSwUpdM_Internal_Shutdown */

/**********************************************************************************************************************
 * vSwUpdM_Internal_Suspend
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_Suspend(vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that shutdown isn't pending and component isn't shut down. */
  if ((vSwUpdM_GlobalState == VSWUPDM_STATE_SHUT_DOWN_PENDING)
    || (vSwUpdM_GlobalState == VSWUPDM_STATE_SHUT_DOWN))
  {
    errorId = VSWUPDM_E_INV_OPERATION_STATE;
  }
  /* #20 Check that source node doesn't exceeds valid range. */
  else
  if (Source >= vSwUpdM_GetSizeOfNode())
  {
    errorId = VSWUPDM_E_OUT_OF_RANGE;
  }
  else
  /* #-- Otherwise: */
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    if (vSwUpdM_RemoteLockIsGrantedTo == VSWUPDM_INVALID_NODE)
    {
      /* If not yet locked, suspend of local node is allowed. */
      retVal = E_OK;
    }
    else
    {
      retVal = vSwUpdM_RemoteCheckLock(Source);
    }

    if (retVal == E_OK)
    {
      /* #100 Trigger suspending of pending operations. */
      retVal = vSwUpdM_State_Suspend(VSWUPDM_SID_SUSPEND, NULL_PTR, Source);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_SUSPEND, errorId);

  return retVal;
} /* vSwUpdM_Internal_Suspend */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_EraseRegion()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_EraseRegion(
  vSwUpdM_RegionIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that region ID is valid. */
  if (vSwUpdM_Region_IsRegionIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_RegionIdxType regionIdx = vSwUpdM_Region_GetRegionIdx(Id);

      /* #100 Verify that region is assigned to opened module */
      if (regionIdx == VSWUPDM_INVALID_ID)
      {
        errorId = VSWUPDM_E_WRONG_PARAMETER;
        retVal = E_NOT_OK;
      }
      /* #110 Evaluate state of region instance in opened module/partition.
       *   If region is already erased */
      else if (vSwUpdM_GetVarRegions(regionIdx).DynamicAttributesOfVarRegion.State == VSWUPDM_REGION_STATE_ERASED)
      {
        /* #111 Directly issue confirmation to upper-layer. */
        retVal = E_OK;
        vSwUpdM_UlConfirmation(VSWUPDM_SID_ERASE_REGION, Source, retVal);
      }
      else
      {
        /* #120 Check whether programming attempts are exceeded. */
        retVal = vSwUpdM_Region_CheckProgrammingAttempts(vSwUpdM_EntityData.OpenIds.ModuleId, regionIdx);

        if (retVal == E_OK)
        {
          vSwUpdM_EntityIdsType entityIds;

          /* #130 Enter critical section to ensure exclusive access of state and job queue. */
          VSWUPDM_ENTER_CRITICAL_SECTION();

          /* #140 Trigger dispatching of job(s) to erase the requested region. */
          entityIds           = vSwUpdM_EntityData.OpenIds;
          entityIds.RegionId  = Id;
          entityIds.RegionIdx = regionIdx;

          retVal = vSwUpdM_Dispatch(VSWUPDM_SID_ERASE_REGION, VSWUPDM_EXECCTRL_SEQUENCEIDX_ERASE_REGION, VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION,
                                    vSwUpdM_GetNodeGroupOwnersIdxOfRegion(Id), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

          /* #150 Leave critical section ensuring exclusive access of state and job queue. */
          VSWUPDM_LEAVE_CRITICAL_SECTION();
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ERASE_REGION, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_EraseRegion */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_OpenSegment()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_OpenSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no segment is opened. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that segment ID is valid. */
  if (vSwUpdM_Segment_IsSegmentIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Check whether writing to currently opened segment is allowed. */
      if (vSwUpdM_Segment_IsSegmentWritable(Id) == TRUE)
      {
        retVal = E_OK;
      }
      else
      {
        retVal = VSWUPDM_E_INVALID_SEGMENT_STATE;
      }

      if (retVal == E_OK)
      {
        vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);

        vSwUpdM_EntityIdsType entityIds;

        /* #110 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #120 Trigger dispatching of job(s) to open the requested segment. */
        entityIds           = vSwUpdM_EntityData.OpenIds;
        entityIds.SegmentId = Id;

        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_OPEN_SEGMENT, VSWUPDM_EXECCTRL_SEQUENCEIDX_OPEN_SEGMENT, VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT,
                                  regionOwnerGroupIndex, VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

        /* #130 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_OPEN_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_OpenSegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_CloseSegment()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_CloseSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a segment is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_SEGMENT, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no data stream is pending. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that segment ID is valid. */
  if (vSwUpdM_Segment_IsSegmentIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that requested segment is opened. */
  if (vSwUpdM_EntityData.OpenIds.SegmentId.DynamicSegmentId != Id.DynamicSegmentId)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);
      vSwUpdM_EntityIdsType entityIds;

      /* #100 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 Trigger dispatching of job(s) to close the requested segment. */
      entityIds = vSwUpdM_EntityData.OpenIds;
      entityIds.SegmentId = Id;

      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_CLOSE_SEGMENT, VSWUPDM_EXECCTRL_SEQUENCEIDX_CLOSE_SEGMENT, VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT,
                                regionOwnerGroupIndex, VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

      /* #120 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_CLOSE_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_CloseSegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_AddSegment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(Source); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check parameter "SegmentInfo". */
  if (SegmentInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Verify that write address contains undefined value. */
      if (SegmentInfo->WriteAddress == VSWUPDM_UNDEFINED_ADDRESS)
      {
        /* #110 Automatically detect state of segment. */
        SegmentInfo->State = VSWUPDM_SEGMENT_STATE_AUTODETECT;

        /* #120 Create a new page aligned used segment. */
        retVal = vSwUpdM_Segment_AddSegment(SegmentInfo, VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED, VSWUPDM_ALIGN_GRANULARITY_PAGE, TRUE);

        /* #130 Mark external segment count as "dirty". */
        if (retVal == E_OK)
        {
          vSwUpdM_EntityData.Count.ExternalSegmentCountDirty = TRUE;
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ADD_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Internal_AddSegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_AddFinalizedSegment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_AddFinalizedSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check parameter "SegmentInfo". */
  if (SegmentInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_ModuleStateType moduleState = VSWUPDM_MODULE_STATE_UNDEFINED;
      vSwUpdM_RegionStateType regionState = VSWUPDM_REGION_STATE_UNDEFINED;

      /* #100 Check that module and region affected by segment are both in state "clean". */
      retVal = vSwUpdM_Module_GetStateByPartition(&moduleState, vSwUpdM_EntityData.OpenIds.ModuleId, vSwUpdM_EntityData.OpenIds.PartitionId);

      if (retVal == E_OK)
      {
        vSwUpdM_RegionIdType regionId;

        retVal = vSwUpdM_GetRegionIdByRange(&regionId, SegmentInfo->StartAddress, 1u);

        if (retVal == E_OK)
        {
          regionState = vSwUpdM_GetVarRegions(vSwUpdM_Region_GetRegionIdx(regionId)).DynamicAttributesOfVarRegion.State;
        }
      }

      if ( (moduleState != VSWUPDM_MODULE_STATE_CLEAN)
        || (regionState != VSWUPDM_REGION_STATE_CLEAN) )
      {
        retVal = VSWUPDM_E_INVALID_SEGMENT_STATE;
      }

      if (retVal == E_OK)
      {
        /* #110 Automatically detect state of segment. */
        SegmentInfo->State = VSWUPDM_SEGMENT_STATE_AUTODETECT;

        /* #120 Create a new page aligned used segment. */
        retVal = vSwUpdM_Segment_AddSegment(SegmentInfo, VSWUPDM_CLASS_OF_VAR_SEGMENTS_USED, VSWUPDM_ALIGN_GRANULARITY_PAGE, TRUE);
      }

      /* #130 Adding a finalized segment is only allowed for erased memory. */
      if (retVal == E_OK)
      {
        /* #131 Mark external segment count as "dirty". */
        vSwUpdM_EntityData.Count.ExternalSegmentCountDirty = TRUE;

        if (SegmentInfo->State != VSWUPDM_SEGMENT_STATE_ERASED)
        {
          retVal = VSWUPDM_E_INVALID_SEGMENT_STATE;
        }
      }

      if (retVal == E_OK)
      {
        vSwUpdM_VarSegmentsPtrType  segment      = vSwUpdM_GetAddrVarSegments(SegmentInfo->Id.DynamicSegmentId);
        vSwUpdM_AddressType         writeAddress = segment->ReservedEndAddressOfVarSegments + 1u;

        /* #140 Conclude and finalize segment, with write address pointing directly behind end address. */
        (void)vSwUpdM_Segment_UpdateWriteAddress(segment, writeAddress);
        vSwUpdM_Segment_ConcludeSegment(segment, writeAddress, segment->EndAddressOfVarSegments + 1u);
        (void)vSwUpdM_Segment_UpdateState(segment, VSWUPDM_SEGMENT_STATE_FINALIZED);

        /* #150 Update passed segment information with resulting segment attributes. */
        retVal = vSwUpdM_GetSegmentInfo(SegmentInfo, SegmentInfo->Id);
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ADD_FINALIZED_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_AddFinalizedSegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_FinalizeSegment()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_FinalizeSegment(
  vSwUpdM_SegmentIdType Id,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no data stream is pending. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that segment ID is valid. */
  if (vSwUpdM_Segment_IsSegmentIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that segment ID is allowed. */
  if (vSwUpdM_Segment_IsSegmentIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {

    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      /* #100 Check whether writing to currently opened segment is allowed. */
      if (vSwUpdM_Segment_IsSegmentWritable(Id) == TRUE)
      {
        retVal = E_OK;
      }
      else
      {
        retVal = VSWUPDM_E_INVALID_SEGMENT_STATE;
      }

      if (retVal == E_OK)
      {
        vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);
        vSwUpdM_EntityIdsType entityIds;

        /* #110 Initialize resume information for ProcessStreamData sequence. */
        vSwUpdM_ResumeInfo_UpdateWriteService(vSwUpdM_EntityData.OpenIds.PartitionState,
                                              vSwUpdM_GetAddrVarSegments(Id.DynamicSegmentId), VSWUPDM_SID_PROCESS_STREAM_DATA);

        /* #120 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #130 Trigger dispatching of job(s) to finalize the requested segment. */
        entityIds = vSwUpdM_EntityData.OpenIds;
        entityIds.SegmentId = Id;

        retVal = vSwUpdM_Dispatch(VSWUPDM_SID_FINALIZE_SEGMENT, VSWUPDM_EXECCTRL_SEQUENCEIDX_FINALIZE_SEGMENT, VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT,
                                  regionOwnerGroupIndex, VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

        /* #140 Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_FINALIZE_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_Internal_FinalizeSegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_VerifySegment()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_VerifySegment(
  vSwUpdM_SegmentIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(ProcessInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Source); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a module is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that no data stream is pending. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_STREAM) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #30 Check that segment ID is valid. */
  if (vSwUpdM_Segment_IsSegmentIdValid(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #40 Check that segment ID is allowed. */
  if (vSwUpdM_Segment_IsSegmentIdAllowed(Id) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
#if (VSWUPDM_EXISTS_VERIFY_SEGMENT_TYPEOFDATAPROCESSES == STD_ON)
# error "Verify Segment feature with configured pipe is not yet supported"
#else
      /* #100 Check that segment is in state "finalized". */
      if (vSwUpdM_GetAddrVarSegments(Id.DynamicSegmentId)->DynamicAttributesOfVarSegment.State != VSWUPDM_SEGMENT_STATE_FINALIZED)
      {
        retVal = E_NOT_OK;
      }
#endif
    }

    /* PRQA S 2992, 2996 1 */ /*  MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
    if (retVal == E_OK)
    {
      vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex = vSwUpdM_Segment_GetRegionOwnerGroupIndex(Id);
      vSwUpdM_EntityIdsType entityIds;

      /* #110 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #120 Trigger dispatching of job(s) to open the requested partition. */
      entityIds           = vSwUpdM_EntityData.OpenIds;
      entityIds.SegmentId = Id;

      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_VERIFY_SEGMENT, VSWUPDM_EXECCTRL_SEQUENCEIDX_VERIFY_SEGMENT, VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT,
                                regionOwnerGroupIndex, VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

      /* #130 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_VERIFY_SEGMENT, errorId);

  return retVal;
  /* PRQA S 6080, 6050 1 */ /* MD_MSR_STMIF, MD_MSR_STCAL */
} /* vSwUpdM_Internal_VerifySegment */

/**********************************************************************************************************************
 *  vSwUpdM_Internal_ClearSegmentsOfModule()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Internal_ClearSegmentsOfModule(
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_NodeIterType Source)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_ExtNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE, Source) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
  /* #30 Check that requested module is opened. */
  if (vSwUpdM_EntityData.OpenIds.ModuleId != ModuleId)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #99 Check that lock is granted to the given source node. */
    retVal = vSwUpdM_RemoteCheckLock(Source);

    if (retVal == E_OK)
    {
      vSwUpdM_EntityIdsType entityIds;

      /* #100 Enter critical section to ensure exclusive access of state and job queue. */
      VSWUPDM_ENTER_CRITICAL_SECTION();

      /* #110 Trigger dispatching of job(s) to open the requested partition. */
      entityIds          = vSwUpdM_EntityData.OpenIds;
      entityIds.ModuleId = ModuleId;

      retVal = vSwUpdM_Dispatch(VSWUPDM_SID_CLEAR_SEGMENTS_OF_MODULE, VSWUPDM_EXECCTRL_SEQUENCEIDX_CLEAR_SEGMENTS_OF_MODULE, VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE,
                                vSwUpdM_GetNodeGroupOwnersIdxOfModule(ModuleId), VSWUPDM_GRIDNODE_INVALID_NODE, Source, entityIds);

      /* #120 Leave critical section ensuring exclusive access of state and job queue. */
      VSWUPDM_LEAVE_CRITICAL_SECTION();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_CLEAR_SEGMENTS_OF_MODULE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_Internal_ClearSegmentsOfModule */

/**********************************************************************************************************************
 *  vSwUpdM_Dispatch()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Dispatch(
  vSwUpdM_ServiceIdType         ServiceId,
  vSwUpdM_ExecCtrl_SequenceListIndexType ServiceDispatchIndex,
  vSwUpdM_GridSrvc_ServiceIdxType RemoteServiceIndex,
  vSwUpdM_NodeGroupIterType     RemoteTargetGroup,
  vSwUpdM_NodeIterType          RemoteTarget,
  vSwUpdM_NodeIterType          Source,
  vSwUpdM_EntityIdsType         EntityIds)
{
  vSwUpdM_JobPtrType spawnedJob;
  Std_ReturnType retVal;

  /* #10 Enter critical section to ensure exclusive access of state and job queue. */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  /* #20 Spawn job which triggers processing steps of a service. */
  spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_SERVICE_DISPATCHER, VSWUPDM_JOB_OPERATION_DEFAULT,
                                 (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, ServiceId, NULL_PTR, Source);

  /* #30 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
  if (retVal == E_OK)
  {
    /* #40 Pass open entity IDs etc. to job. */
    spawnedJob->EntityIds = EntityIds;
    spawnedJob->RemoteTargetGroup = RemoteTargetGroup;
    spawnedJob->RemoteTarget = RemoteTarget;
    spawnedJob->Source = Source;
    spawnedJob->RemoteServiceIndex = RemoteServiceIndex;
    spawnedJob->SequenceIdx = ServiceDispatchIndex;
  }

  /* #50 Leave critical section ensuring exclusive access of state and job queue. */
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  return retVal;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_Dispatch */

/**********************************************************************************************************************
 * vSwUpdM_InitMemory
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_InitMemory(void)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #10 Initialize global state variables. */
  vSwUpdM_InitState                               = VSWUPDM_INIT_STATE_UNINIT;
  vSwUpdM_GlobalState                             = VSWUPDM_STATE_IDLE;
  vSwUpdM_UpdateState                             = VSWUPDM_UPDATE_STATE_UNDEFINED;
  vSwUpdM_ResumeInfoDirty                         = FALSE;
  vSwUpdM_PartitionAttributesDirty                = FALSE;
  vSwUpdM_ModulePendingAttributes.AttributesDirty = FALSE;
  vSwUpdM_ImplicitModuleOpenFlag                  = FALSE;

  vSwUpdM_Bookkeeper_InitMemory();

} /* vSwUpdM_InitMemory */

/**********************************************************************************************************************
 * vSwUpdM_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_Init(P2CONST(vSwUpdM_ConfigType, AUTOMATIC, VSWUPDM_PBCFG) ConfigPtr)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT_CONST(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component isn't initialized yet. */
  if (vSwUpdM_General_CommonPosDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
#if (VSWUPDM_USE_INIT_POINTER == STD_ON)
  /* #20 Check parameter "ConfigPtr" (if configured). */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
#if (VSWUPDM_USE_INIT_POINTER == STD_ON)
    vSwUpdM_ConfigDataPtr = ConfigPtr;
#endif

    /* #100 Enter critical section to ensure exclusive access of state and job queue. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #110 Trigger background initialization of component. */
    (void)vSwUpdM_Init_Start(vSwUpdM_GetLocalNode());

    /* #120 Leave critical section ensuring exclusive access of state and job queue. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT, errorId);
} /* vSwUpdM_Init */

/**********************************************************************************************************************
 * vSwUpdM_DeInit
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_DeInit(void)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
  /* #-- If vSwUpdM is not initialized, report an error. */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check that component is idle or was previously shut down. */
  if ( (vSwUpdM_GlobalState != VSWUPDM_STATE_IDLE)
    && (vSwUpdM_GlobalState != VSWUPDM_STATE_SHUT_DOWN) )
  {
    errorId = VSWUPDM_E_NOT_IDLE;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Reset initialization state. */
    vSwUpdM_InitState = VSWUPDM_INIT_STATE_UNINIT;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_DEINIT, errorId);
} /* vSwUpdM_DeInit */

#if (VSWUPDM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vSwUpdM_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
# if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "VersionInfo". */
  if (VersionInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
# endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Set the version information. */
    VersionInfo->vendorID         = (VSWUPDM_VENDOR_ID);
    VersionInfo->moduleID         = (VSWUPDM_MODULE_ID);
    VersionInfo->sw_major_version = (VSWUPDM_SW_MAJOR_VERSION);
    VersionInfo->sw_minor_version = (VSWUPDM_SW_MINOR_VERSION);
    VersionInfo->sw_patch_version = (VSWUPDM_SW_PATCH_VERSION);
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_VERSION_INFO, errorId);
} /* vSwUpdM_GetVersionInfo */
#endif /* (VSWUPDM_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  vSwUpdM_InitProcessInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitProcessInfo(
  P2VAR(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ProcessInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "ProcessInfo". */
  if (ProcessInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Initialize passed process information structure with default values. */
    ProcessInfo->InputCount  = 0u;
    ProcessInfo->OutputCount = 0u;
    ProcessInfo->Operation   = VSTREAMPROC_NO_METASTATE;
    ProcessInfo->InputData   = NULL_PTR;
    ProcessInfo->OutputData  = NULL_PTR;

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT_PROCESS_INFO, errorId);

  return retVal;
} /* vSwUpdM_InitProcessInfo */

/**********************************************************************************************************************
 * vSwUpdM_InitEntityIds
 **********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitEntityIds(vSwUpdM_EntityIdsPtrType EntityIds)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "EntityIds". */
  if (EntityIds == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Call internal function to initialize given entity IDs with default values. */
    vSwUpdM_Init_EntityIdsDefaults(EntityIds);

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT_ENTITY_IDS, errorId);

  return retVal;
} /* vSwUpdM_InitEntityIds */

/**************************************************************
 *  Memory Abstraction:
 *   - Logical View
 *     - Stream
 **************************************************************/
/**********************************************************************************************************************
 * vSwUpdM_StartStream
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_StartStream(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_StartStream(StreamInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_StartStream */

/**********************************************************************************************************************
 * vSwUpdM_ProcessStreamData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcessStreamData(vSwUpdM_StreamLengthType StreamLength)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_ProcessStreamData(StreamLength, vSwUpdM_GetLocalNode());
} /* vSwUpdM_ProcessStreamData */

/**********************************************************************************************************************
 * vSwUpdM_EndStream
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EndStream(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_EndStream(vSwUpdM_GetLocalNode());
} /* vSwUpdM_EndStream */

/**********************************************************************************************************************
 * vSwUpdM_InitStreamInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitStreamInfo(
  P2VAR(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) StreamInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "StreamInfo". */
  if (StreamInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Initialize given stream information structure with default values. */
    StreamInfo->InputLength = VSWUPDM_UNDEFINED_LENGTH;
    StreamInfo->Operation = VSWUPDM_STREAM_OPERATION_DEFAULT;

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT_STREAM_INFO, errorId);

  return retVal;
} /* vSwUpdM_InitStreamInfo */

/**********************************************************************************************************************
 * vSwUpdM_SwitchStreamContext
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SwitchStreamContext(
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) StreamInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  VSWUPDM_DUMMY_STATEMENT_CONST(StreamInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */

  /* ----- Implementation ------------------------------------------------- */
  /* #10 Service not supported yet, report error. */
  /* ----- Development Error Report --------------------------------------- */

  return E_NOT_OK;
} /* vSwUpdM_SwitchStreamContext */

/**************************************************************
 *  Memory Abstraction:
 *   - Logical View
 *     - State
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_Start
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Start(void)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */

  /* ----- Implementation ------------------------------------------------- */
  VSWUPDM_ENTER_CRITICAL_SECTION();

  if (vSwUpdM_RemoteLockIsGrantedTo != (vSwUpdM_NodeIterType)vSwUpdM_GetLocalNode())
  {
    if (vSwUpdM_RemoteLockIsGrantedTo == VSWUPDM_INVALID_NODE)
    {
      /* The local node is not locked by a remote master - lock it by itself */
      vSwUpdM_RemoteLockIsGrantedTo = vSwUpdM_GetLocalNode();
      /* The local node is not locked by itself - vSwUpdM_Start() was allowed. */
      retVal = E_OK;
    }
    else
    {
      retVal = VSWUPDM_E_RESPONSE_PRIVILEGE;
    }
  }
  else
  {
    /* The local node is already locked by itself */
    retVal = E_OK;
  }
  VSWUPDM_LEAVE_CRITICAL_SECTION();

  if (retVal == E_OK)
  {
    /* #10 Call matching internal function for external service and return result. */
    retVal = vSwUpdM_Internal_Start(vSwUpdM_GetLocalNode());
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_START, errorId);

  return retVal;
} /* vSwUpdM_Start */

/**********************************************************************************************************************
 * vSwUpdM_Shutdown
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Shutdown(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_Shutdown(vSwUpdM_GetLocalNode());
} /* vSwUpdM_Shutdown */

/**********************************************************************************************************************
 * vSwUpdM_Abort
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Abort(void)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Service not supported yet, report error. */
    retVal = E_NOT_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ABORT, errorId);

  return retVal;
} /* vSwUpdM_Abort */

/**********************************************************************************************************************
 * vSwUpdM_Suspend
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Suspend(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_Suspend(vSwUpdM_GetLocalNode());
} /* vSwUpdM_Suspend */

/**********************************************************************************************************************
 * vSwUpdM_Resume
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_Resume(void)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that operation was suspended before. */
  if (vSwUpdM_GlobalState != VSWUPDM_STATE_SUSPENDED)
  {
    errorId = VSWUPDM_E_INV_OPERATION_STATE;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
  /* #100 Spawn job to resume suspended jobs. */
    retVal = vSwUpdM_State_Resume(VSWUPDM_SID_NONE, NULL_PTR, vSwUpdM_GetLocalNode());
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_RESUME, errorId);

  return retVal;
} /* vSwUpdM_Resume */

/**********************************************************************************************************************
 * vSwUpdM_GetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetState(P2VAR(vSwUpdM_StateType, AUTOMATIC, VSWUPDM_APPL_VAR) State)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "State". */
  if (State == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    vSwUpdM_StateType state = vSwUpdM_GlobalState;

    /* #100 If component isn't initialized yet */
    if ((vSwUpdM_InitState == VSWUPDM_INIT_STATE_UNINIT) || (vSwUpdM_InitState == VSWUPDM_INIT_STATE_PENDING))
    {
      switch (state)
      {
      case VSWUPDM_STATE_SUSPEND_PENDING:
      case VSWUPDM_STATE_SUSPENDED:
      case VSWUPDM_STATE_SUSPENDING:
      case VSWUPDM_STATE_SHUT_DOWN_PENDING:
      case VSWUPDM_STATE_SHUT_DOWN:
        /* #110 If suspend or shutdown is pending or finished
         *   Report unmodified global operation state. */
      {
        break;
      }
      default:
        /* #120 Otherwise
         *   Report pending initialization. */
      {
        state = VSWUPDM_STATE_INIT_PENDING;
        break;
      }
      }
    }

    /* As long as there are pending responses, do not enter IDLE state. */
    if ((state == VSWUPDM_STATE_IDLE) || (state == VSWUPDM_STATE_SUSPENDED) || (state == VSWUPDM_STATE_SHUT_DOWN))
    {
      if (vSwUpdM_SrvcRouting_GetNumberOfPendingResponses() > 0u)
      {
        state = VSWUPDM_STATE_PENDING;
      }
    }

    /* #130 Otherwise
     *   Report unmodified global operation state. */

    *State = state;
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_STATE, errorId);

  return retVal;
} /* vSwUpdM_GetState */

/**********************************************************************************************************************
 * vSwUpdM_GetResumeInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetResumeInfo(P2VAR(vSwUpdM_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ResumeInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check parameter "ResumeInfo". */
  if (ResumeInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Return resume information. */
    *ResumeInfo = vSwUpdM_ResumeInfo.ResumeInfo;

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_RESUME_INFO, errorId);

  return retVal;
} /* vSwUpdM_GetResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_GetCheckpoint
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetCheckpoint(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_VAR) Checkpoint,
  vSwUpdM_AddressType Address)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check parameter "Checkpoint". */
  if (Checkpoint == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
  /* #-- Otherwise: */
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Get the address of the next checkpoint. */
    vSwUpdM_ResumeInfo_GetCheckpointAddress(Checkpoint, Address, vSwUpdM_EntityData.OpenIds.PartitionId);

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_CHECKPOINT, errorId);

  return retVal;
} /* vSwUpdM_GetCheckpoint */

/**************************************************************
 *  Memory Abstraction:
 *   - Partitions
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_ValidatePartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ValidatePartition(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_ValidatePartition(vSwUpdM_GetLocalNode());
} /* vSwUpdM_ValidatePartition */

/**********************************************************************************************************************
 * vSwUpdM_InvalidatePartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InvalidatePartition(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_InvalidatePartition(vSwUpdM_GetLocalNode());
} /* vSwUpdM_InvalidatePartition */

/**********************************************************************************************************************
 * vSwUpdM_SyncPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SyncPartition(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_SyncPartition(vSwUpdM_GetLocalNode());
} /* vSwUpdM_SyncPartition */

/**********************************************************************************************************************
 * vSwUpdM_CheckPartitionConsistency
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CheckPartitionConsistency(P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_CheckPartitionConsistency(ProcessInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_CheckPartitionConsistency */

/**********************************************************************************************************************
 * vSwUpdM_SwapActivePartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SwapActivePartition(void)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_SwapActivePartition(vSwUpdM_GetLocalNode());
} /* vSwUpdM_SwapActivePartition */

/**********************************************************************************************************************
 * vSwUpdM_OpenPartition
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenPartition(vSwUpdM_PartitionStateType State)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_OpenPartition(State, vSwUpdM_GetLocalNode());
} /* vSwUpdM_OpenPartition */

/**********************************************************************************************************************
 * vSwUpdM_GetPartitionStateByHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetPartitionStateByHandle(
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionState,
  vSwUpdM_PartitionHandleIdType HandleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "PartitionState". */
    if (PartitionState == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
    else
      /* #30 Check that partition handle is valid. */
      if (vSwUpdM_Part_IsPartitionHandleValid(HandleId) == FALSE)
      {
        errorId = VSWUPDM_E_WRONG_PARAMETER;
      }
  /* #-- Otherwise: */
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        vSwUpdM_PartitionIterType partitionId;

        /* #100 Iterate over all static partitions. */
        for (partitionId = 0u; partitionId < vSwUpdM_GetStaticNumberOfPartitions(); partitionId++)
        {
          /* #110 If handle is configured for current partition and handle matches given one */
          if ((vSwUpdM_IsPartitionHandleUsedOfPartition(partitionId))
            && (vSwUpdM_GetPartitionHandleOfPartition(partitionId) == HandleId))
          {
            /* #120 Return current partition State. */
            (*PartitionState) = vSwUpdM_GetVarPartitions(partitionId).DynamicAttributesOfVarPartitions.State;
            retVal = E_OK;

            break;
          }
        }
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_PARTITION_STATE_BY_HANDLE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetPartitionStateByHandle */

/**********************************************************************************************************************
 * vSwUpdM_GetOpenPartitionState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenPartitionState(
  P2VAR(vSwUpdM_PartitionStateType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionState)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "PartitionId". */
    if (PartitionState == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_PartitionStateType partitionState;

      /* #100 If a partition is opened, return State of opened partition. Otherwise, return E_NOT_OK */
      partitionState = vSwUpdM_EntityData.OpenIds.PartitionState;
      *PartitionState = partitionState;

      retVal = E_OK;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_OPEN_PARTITION_STATE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetOpenPartitionState */

/**********************************************************************************************************************
 * vSwUpdM_GetPartitionInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetPartitionInfo(
  P2VAR(vSwUpdM_PartitionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) PartitionInfo,
  vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;
  vSwUpdM_PartitionIdType id;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "PartitionInfo". */
    if (PartitionInfo == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
    else
      /* #30 Check that partition ID is valid. */
      if (vSwUpdM_Part_IsPartitionStateValid(State) != TRUE)    /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
      {
        errorId = VSWUPDM_E_WRONG_PARAMETER;
      }
  /* #-- Otherwise: */
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        /* #100 Return configured values of requested partition. */
        retVal = vSwUpdM_Part_GetIdByState(&id, State);

        if (E_OK == retVal)
        {
          PartitionInfo->Id = id;
          PartitionInfo->HandleId = vSwUpdM_GetPartitionHandleOfPartition(id);
          PartitionInfo->AddrAreaId = vSwUpdM_GetAddrAreaIdOfPartition(id);

          /* #200 If component is initialized */
          if (vSwUpdM_General_IsModuleInitialized() == TRUE)
          {
            vSwUpdM_VarPartitionsPtrType partition; /* PRQA S 3679 */ /* MD_vSwUpdM_Rule8.13_3679_PointerToModifiableData */
            P2CONST(vSwUpdM_PartitionDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_VAR) attributes;

            partition = vSwUpdM_GetAddrVarPartitions(id);
            attributes = &partition->DynamicAttributesOfVarPartitions;

            /* #210 Return dynamic attributes of requested partition. */
            PartitionInfo->State = attributes->State;
            PartitionInfo->IsValid = attributes->IsValid;
            PartitionInfo->Revision = attributes->Revision;
            /* #211 Return swappable attribute, which is dependent on other configuration aspects. */
            PartitionInfo->IsSwappable = partition->SwappableOfVarPartitions;
          }
          /* #220 Otherwise */
          else
          {
            /* #230 Return default values for dynamic attributes of requested partition. */
            PartitionInfo->State = VSWUPDM_PART_STATE_UNDEFINED;
            PartitionInfo->IsValid = VSWUPDM_VALIDITY_INVALID;
            PartitionInfo->Revision = 0u;
            /* #231 Evaluate swappable attribute, which is dependent on other configuration aspects. */
            PartitionInfo->IsSwappable = vSwUpdM_Part_IsPartitionSwappable(id);
          }

          retVal = E_OK;
        }
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_PARTITION_INFO, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetPartitionInfo */

/**********************************************************************************************************************
 * vSwUpdM_IsPartitionErasable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionErasable(vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that partition ID is valid. */
    if (vSwUpdM_Part_IsPartitionStateValid(State) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100  If requested partition is the inactive partition or the backup target:
       *      Partition is erasable.
       */
      if ((State == VSWUPDM_PART_STATE_INACTIVE) || (State == VSWUPDM_PART_STATE_BACKUP_TARGET))
      {
        retVal = TRUE;
      }
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_PARTITION_ERASABLE, errorId);

  return retVal;
} /* vSwUpdM_IsPartitionErasable */

/**********************************************************************************************************************
 * vSwUpdM_IsPartitionReadable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionReadable(vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that partition ID is valid. */
    if (vSwUpdM_Part_IsPartitionStateValid(State) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 All partitions are readable. */
      retVal = TRUE;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_PARTITION_READABLE, errorId);

  return retVal;
} /* vSwUpdM_IsPartitionReadable */

/**********************************************************************************************************************
 * vSwUpdM_IsPartitionWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsPartitionWritable(vSwUpdM_PartitionStateType State)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that partition ID is valid. */
    if (vSwUpdM_Part_IsPartitionStateValid(State) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 If requested partition is erasable
       *   Partition is writable as well. */
      retVal = vSwUpdM_IsPartitionErasable(State);
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_PARTITION_WRITABLE, errorId);

  return retVal;
} /* vSwUpdM_IsPartitionWritable */

/**************************************************************
 *  Memory Abstraction:
 *   - Module
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_OpenModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_OpenModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_OpenModule */

/**********************************************************************************************************************
 * vSwUpdM_CloseModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CloseModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_CloseModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_CloseModule */

/**********************************************************************************************************************
 * vSwUpdM_ValidateModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ValidateModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_ValidateModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_ValidateModule */

/**********************************************************************************************************************
 * vSwUpdM_InvalidateModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InvalidateModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_InvalidateModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_InvalidateModule */

/**********************************************************************************************************************
 * vSwUpdM_EraseModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_EraseModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_EraseModule */

/**********************************************************************************************************************
 * vSwUpdM_FinalizeModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_FinalizeModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_FinalizeModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_FinalizeModule */

/**********************************************************************************************************************
 * vSwUpdM_VerifyModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_VerifyModule(
  vSwUpdM_ModuleIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_VerifyModule(Id, ProcessInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_VerifyModule */

/**********************************************************************************************************************
 * vSwUpdM_SyncModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SyncModule(vSwUpdM_ModuleIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_SyncModule(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_SyncModule */

/**********************************************************************************************************************
 * vSwUpdM_GetModuleIdByHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleIdByHandle(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId,
  vSwUpdM_ModuleHandleIdType HandleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "ModuleId". */
  if (ModuleId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that module handle is valid. */
    if (vSwUpdM_Module_IsModuleHandleValid(HandleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_ModuleIterType moduleId;

      /* #100 Iterate over all static modules. */
      for (moduleId = 0u; moduleId < vSwUpdM_GetStaticNumberOfModules(); moduleId++)
      {
        /* #110 If handle is configured for current module and handle matches given one */
        if ((vSwUpdM_IsModuleHandleUsedOfModule(moduleId))
          && (vSwUpdM_GetModuleHandleOfModule(moduleId) == HandleId))
        {
          /* #120 Return current module ID. */
          *ModuleId = (vSwUpdM_ModuleIdType)moduleId;
          retVal = E_OK;

          break;
        }
      }
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_MODULE_ID_BY_HANDLE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetModuleIdByHandle */

/**********************************************************************************************************************
 * vSwUpdM_GetModuleIdByRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleIdByRange(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "ModuleId". */
  if (ModuleId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    vSwUpdM_RegionIdType regionId;
    vSwUpdM_LengthType length;

    length = Length;
    /* #100 If length is greater zero, decrement length to calculate last address in range.
     *   Special case of zero length indicates that only address is relevant. */
    if (length > 0u)
    {
      length--;
    }

    /* #110 If a valid region is located at the given start address */
    if (vSwUpdM_GetRegionIdByRange(&regionId, StartAddress, 1u) == E_OK)
    {
      vSwUpdM_ModuleIdType firstModuleId = vSwUpdM_GetModuleIdxOfRegion(regionId);

      /* #120 If a valid region is located at the last address of the given range */
      if (vSwUpdM_GetRegionIdByRange(&regionId, StartAddress + length, 1u) == E_OK)
      {
        vSwUpdM_ModuleIdType secondModuleId = vSwUpdM_GetModuleIdxOfRegion(regionId);

        /* #130 If both regions are assigned to the same module */
        if (firstModuleId == secondModuleId)
        {
          /* #140 Return the module ID. */
          *ModuleId = firstModuleId;
          retVal = E_OK;
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_MODULE_ID_BY_RANGE, errorId);

  return retVal;
} /* vSwUpdM_GetModuleIdByRange */

/**********************************************************************************************************************
 * vSwUpdM_GetOpenModuleId
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenModuleId(
  P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "ModuleId". */
    if (ModuleId == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_ModuleIdType moduleId;

      /* #100 If a module is opened
       *   Return ID of opened module.
       * Otherwise, return invalid ID value. */
      moduleId = vSwUpdM_EntityData.OpenIds.ModuleId;
      *ModuleId = moduleId;

      retVal = E_OK;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_OPEN_MODULE_ID, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetOpenModuleId */

/**********************************************************************************************************************
 * vSwUpdM_GetModuleInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetModuleInfo(
  P2VAR(vSwUpdM_ModuleInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) ModuleInfo,
  vSwUpdM_ModuleIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that module ID is valid. */
  if (vSwUpdM_Module_IsModuleIdValid(Id) != TRUE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
    /* #20 Check parameter "ModuleInfo". */
    if (ModuleInfo == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Return configured values of requested module. */
      ModuleInfo->Id = Id;
      ModuleInfo->HandleId = vSwUpdM_GetModuleHandleOfModule(Id);
      ModuleInfo->Type = vSwUpdM_GetModuleTypeOfModule(Id);
      ModuleInfo->IsMandatory = vSwUpdM_IsMandatoryOfModule(Id);    /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
      ModuleInfo->MetaDataAddress = vSwUpdM_GetMetaDataAddressOfModule(Id);
      ModuleInfo->MaxProgrammingAttempts = vSwUpdM_GetProgrammingAttemptsOfModule(Id);

      /* #110 If partition group assigned to module contains more than one partition
       *   Module is swappable. */
      if (vSwUpdM_GetNumPartitionOfPartitionGroup(vSwUpdM_GetPartitionGroupIdxOfModule(Id)) > 1u)
      {
        ModuleInfo->IsSwappable = TRUE;
      }
      /* #120 Otherwise
       *   Module is non-swappable */
      else
      {
        ModuleInfo->IsSwappable = FALSE;
      }

      /* #200 If component is initialized and a partition is opened */
      if ((vSwUpdM_General_IsModuleInitialized() == TRUE)
        && (vSwUpdM_EntityData.OpenIds.PartitionId != VSWUPDM_INVALID_ID))
      {
        vSwUpdM_PartitionIdxType  relativePartitionIdx = 0u; /* Redundant initialization to prevent non suppress able PRQA message 2963. */

        /* #210 If the requested module is instantiated in the opened partition */
        if (vSwUpdM_Module_GetRelativePartitionIdxByPartition(&relativePartitionIdx, Id, vSwUpdM_EntityData.OpenIds.PartitionId) == E_OK)
        {
          P2CONST(vSwUpdM_ModuleDynamicAttributesType, AUTOMATIC, VSWUPDM_APPL_DATA) attributes;

          attributes = &vSwUpdM_GetVarModules(Id).DynamicAttributesOfVarModules[relativePartitionIdx];

          /* #220 Return dynamic attributes of requested module instance. */
          ModuleInfo->State = attributes->State;
          ModuleInfo->IsValid = attributes->IsValid;
          ModuleInfo->Revision = attributes->Revision;
          ModuleInfo->ProgrammingAttempts = attributes->ProgrammingAttempts;

          retVal = E_OK;
        }
        /* #230 Otherwise, return negative result. */
      }
      /* #240 Otherwise */
      else
      {
        /* #250 Return default values for dynamic attributes of requested module instance. */
        ModuleInfo->State = VSWUPDM_MODULE_STATE_UNDEFINED;
        ModuleInfo->IsValid = VSWUPDM_VALIDITY_INVALID;
        ModuleInfo->Revision = 0u;
        ModuleInfo->ProgrammingAttempts = ModuleInfo->MaxProgrammingAttempts;

        retVal = E_OK;
      }
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_MODULE_INFO, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetModuleInfo */

/**********************************************************************************************************************
 * vSwUpdM_GetNumberOfModules
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfModules(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfModules)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "NumberOfModules". */
  if (NumberOfModules == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Return configured number of modules. */
    *NumberOfModules = vSwUpdM_GetStaticNumberOfModules();

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_NUMBER_OF_MODULES, errorId);

  return retVal;
} /* vSwUpdM_GetNumberOfModules */

/**********************************************************************************************************************
 * vSwUpdM_IsModuleErasable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleErasable(vSwUpdM_ModuleIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Evaluate whether module is erasable. */
      retVal = vSwUpdM_Module_IsModuleErasable(Id);
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_MODULE_ERASABLE, errorId);

  return retVal;
} /* vSwUpdM_IsModuleErasable */

/**********************************************************************************************************************
 * vSwUpdM_IsModuleReadable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleReadable(vSwUpdM_ModuleIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Evaluate whether module is readable. */
      retVal = vSwUpdM_Module_IsModuleReadable(Id);
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_MODULE_READABLE, errorId);

  return retVal;
} /* vSwUpdM_IsModuleReadable */

/**********************************************************************************************************************
 * vSwUpdM_IsModuleWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsModuleWritable(vSwUpdM_ModuleIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Evaluate whether module is writable. */
      retVal = vSwUpdM_Module_IsModuleWritable(Id);
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_MODULE_WRITABLE, errorId);

  return retVal;
} /* vSwUpdM_IsModuleWritable */

/**********************************************************************************************************************
 * vSwUpdM_ProcessModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ProcessModule(
  vSwUpdM_ModuleIdType ModuleId, vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_ProcessModule(ModuleId, ProcessId, ProcessInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_ProcessModule */

/**********************************************************************************************************************
 * vSwUpdM_IndicateWriteToModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_IndicateWriteToModule(
  vSwUpdM_ModuleIdType ModuleId)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_IndicateWriteToModule(ModuleId, vSwUpdM_GetLocalNode());
} /* vSwUpdM_IndicateWriteToModule */

/**************************************************************
 *  Memory Abstraction:
 *   - Region
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_EraseRegion
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseRegion(vSwUpdM_RegionIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_EraseRegion(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_EraseRegion */

/**********************************************************************************************************************
 * vSwUpdM_GetNumberOfRegionsOfModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfRegionsOfModule(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfRegions,
  vSwUpdM_ModuleIdType ModuleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "NumberOfRegions". */
  if (NumberOfRegions == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Return configured number of regions of given module. */
      *NumberOfRegions = vSwUpdM_GetNRegionsOfModule(ModuleId);

      retVal = E_OK;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_NUMBER_OF_REGIONS_OF_MODULE, errorId);

  return retVal;
} /* vSwUpdM_GetNumberOfRegionsOfModule */

/**********************************************************************************************************************
 * vSwUpdM_GetRegionIdByHandle
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdByHandle(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_RegionHandleIdType HandleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "RegionId". */
  if (RegionId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that region handle is valid. */
    if (vSwUpdM_Region_IsRegionHandleValid(HandleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_RegionIterType regionId;

      /* #100 Iterate over all static regions. */
      for (regionId = 0u; regionId < vSwUpdM_GetStaticNumberOfRegions(); regionId++)
      {
        /* #110 If handle is configured for current region and handle matches given one */
        if ((vSwUpdM_IsRegionHandleUsedOfRegion(regionId))
          && (vSwUpdM_GetRegionHandleOfRegion(regionId) == HandleId))
        {
          /* #120 Return current region ID. */
          *RegionId = (vSwUpdM_RegionIdType)regionId;
          retVal = E_OK;

          break;
        }
      }
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_REGION_ID_BY_HANDLE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetRegionIdByHandle */

/**********************************************************************************************************************
 * vSwUpdM_GetRegionIdByRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdByRange(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "RegionId". */
  if (RegionId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    vSwUpdM_RegionIterType regionId;

    /* #100 Iterate over all static regions. */
    for (regionId = 0u; regionId < vSwUpdM_GetStaticNumberOfRegions(); regionId++)
    {
      /* #110 Check requested range against current region. */
      vSwUpdM_RangeCheckType rangeCheck = vSwUpdM_Range_CheckAgainstRange(
        StartAddress, Length, vSwUpdM_GetStartAddressOfRegion(regionId), vSwUpdM_GetLengthOfRegion(regionId));

      /* #120 If ranges at least overlaps region */
      if (rangeCheck != VSWUPDM_RANGE_CHECK_MISMATCH)
      {
        /* #130 If range is completely contained within current region */
        if (rangeCheck == VSWUPDM_RANGE_CHECK_CONTAINED)
        {
          /* #140 Return current region ID. */
          *RegionId = (vSwUpdM_RegionIdType)regionId;
          retVal = E_OK;
        }

        /* #150 Ranges at least overlapped, no need to search further. */
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_REGION_ID_BY_RANGE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetRegionIdByRange */

/**********************************************************************************************************************
 * vSwUpdM_GetRegionIdOfModuleByIndex
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionIdOfModuleByIndex(
  P2VAR(vSwUpdM_RegionIdType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 Index)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "RegionId". */
  if (RegionId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 If given index is smaller than number of regions assigned to the given module */
      if (Index < vSwUpdM_GetNRegionsOfModule(ModuleId))
      {
        /* #110 Return ID of matching region. */
        *RegionId = vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(ModuleId) + Index);
        retVal = E_OK;
      }
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_REGION_ID_OF_MODULE_BY_INDEX, errorId);

  return retVal;
} /* vSwUpdM_GetRegionIdOfModuleByIndex */

/**********************************************************************************************************************
 * vSwUpdM_GetRegionInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetRegionInfo(
  P2VAR(vSwUpdM_RegionInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) RegionInfo,
  vSwUpdM_RegionIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that region ID is valid. */
  if (vSwUpdM_Region_IsRegionIdValid(Id) != TRUE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
    /* #20 Check parameter "RegionInfo". */
    if (RegionInfo == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Return configured values of requested region. */
      RegionInfo->HandleId = vSwUpdM_GetRegionHandleOfRegion(Id);
      RegionInfo->StartAddress = vSwUpdM_GetStartAddressOfRegion(Id);
      RegionInfo->Length = vSwUpdM_GetLengthOfRegion(Id);
      RegionInfo->MaxLength = RegionInfo->Length;
      RegionInfo->ModuleId = vSwUpdM_GetModuleIdxOfRegion(Id);

      /* #110 Calculate end address. */
      RegionInfo->EndAddress = RegionInfo->StartAddress + (RegionInfo->Length - 1u);
      RegionInfo->MaxAddress = RegionInfo->EndAddress;

      /* #120 Initialize attributes dependent on other configuration aspect with default values. */
      RegionInfo->State = VSWUPDM_REGION_STATE_UNDEFINED;

      /* #200 If component is initialized and both a partition and a module are opened */
      if ((vSwUpdM_General_IsModuleInitialized() == TRUE)
        && (vSwUpdM_EntityData.OpenIds.PartitionId != VSWUPDM_INVALID_ID)
        && (vSwUpdM_EntityData.OpenIds.ModuleId != VSWUPDM_INVALID_ID))
      {
        vSwUpdM_RegionIdxType regionIdx = vSwUpdM_Region_GetRegionIdx(Id);

        /* #210 If region is assigned to opened module
         *   Return dynamic state of requested region instance. */
        if (regionIdx != VSWUPDM_INVALID_ID)
        {
          RegionInfo->State = vSwUpdM_GetVarRegions(Id).DynamicAttributesOfVarRegion.State;
        }
      }

      retVal = E_OK;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_REGION_INFO, errorId);

  return retVal;
} /* vSwUpdM_GetRegionInfo */

/**********************************************************************************************************************
 * vSwUpdM_IsRegionErasable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionErasable(vSwUpdM_RegionIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that region ID is valid. */
    if (vSwUpdM_Region_IsRegionIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Region instance is erasable, when assigned module instance is erasable. */
      retVal = vSwUpdM_Module_IsModuleErasable(vSwUpdM_GetModuleIdxOfRegion(Id));
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_REGION_ERASABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRegionErasable */

/**********************************************************************************************************************
 * vSwUpdM_IsRegionReadable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionReadable(vSwUpdM_RegionIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that region ID is valid. */
    if (vSwUpdM_Region_IsRegionIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Region instance is readable, when assigned module instance is readable. */
      retVal = vSwUpdM_Module_IsModuleReadable(vSwUpdM_GetModuleIdxOfRegion(Id));
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_REGION_READABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRegionReadable */

/**********************************************************************************************************************
 * vSwUpdM_IsRegionWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRegionWritable(vSwUpdM_RegionIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that region ID is valid. */
    if (vSwUpdM_Region_IsRegionIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Region instance is writable, when assigned module instance is writable. */
      retVal = vSwUpdM_Module_IsModuleWritable(vSwUpdM_GetModuleIdxOfRegion(Id));
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_REGION_WRITABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRegionWritable */

/**************************************************************
 *  Memory Abstraction:
 *   - Segment
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_OpenSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_OpenSegment(vSwUpdM_SegmentIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_OpenSegment(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_OpenSegment */

/**********************************************************************************************************************
 * vSwUpdM_CloseSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_CloseSegment(vSwUpdM_SegmentIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_CloseSegment(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_CloseSegment */

/**********************************************************************************************************************
 * vSwUpdM_AddSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AddSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) SegmentInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_AddSegment(SegmentInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_AddSegment */

/**********************************************************************************************************************
 * vSwUpdM_AddFinalizedSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AddFinalizedSegment(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_AddFinalizedSegment(SegmentInfo, vSwUpdM_GetLocalNode());
} /* vSwUpdM_AddSegment */

/**********************************************************************************************************************
 * vSwUpdM_FinalizeSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_FinalizeSegment(vSwUpdM_SegmentIdType Id)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_FinalizeSegment(Id, vSwUpdM_GetLocalNode());
} /* vSwUpdM_FinalizeSegment */

/**********************************************************************************************************************
 * vSwUpdM_VerifySegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_VerifySegment(
  vSwUpdM_SegmentIdType Id,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_CONST) ProcessInfo)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_VerifySegment(Id, ProcessInfo, vSwUpdM_GetLocalNode());
}

/**********************************************************************************************************************
 * vSwUpdM_ClearSegmentsOfModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ClearSegmentsOfModule(vSwUpdM_ModuleIdType ModuleId)
{
  /* #10 Call matching internal function for external service and return result. */
  return vSwUpdM_Internal_ClearSegmentsOfModule(ModuleId, vSwUpdM_GetLocalNode());
} /* vSwUpdM_ClearSegmentsOfModule */

/**********************************************************************************************************************
 * vSwUpdM_GetNumberOfSegmentsOfModule
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetNumberOfSegmentsOfModule(
  P2VAR(uint32, AUTOMATIC, VSWUPDM_APPL_VAR) NumberOfSegments,
  vSwUpdM_ModuleIdType ModuleId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(ModuleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a module is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
    else
      /* #30 Check parameter "NumberOfSegments". */
      if (NumberOfSegments == NULL_PTR)
      {
        errorId = VSWUPDM_E_INV_POINTER;
      }
  /* #-- Otherwise: */
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        /* #100 Return number of dynamic segment of opened module. */
        *NumberOfSegments = vSwUpdM_EntityData.Count.ExternalSegmentCount;

        retVal = E_OK;
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_NUMBER_OF_SEGMENTS_OF_MODULE, errorId);

  return retVal;
} /* vSwUpdM_GetNumberOfSegmentsOfModule */

/**********************************************************************************************************************
 * vSwUpdM_GetSegmentIdByRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdByRange(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "SegmentId". */
  if (SegmentId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 If component is initialized and both a partition and a module are opened */
    if ((vSwUpdM_General_IsModuleInitialized() == TRUE)
      && (vSwUpdM_EntityData.OpenIds.PartitionId != VSWUPDM_INVALID_ID)
      && (vSwUpdM_EntityData.OpenIds.ModuleId != VSWUPDM_INVALID_ID))
    {
      /* #110 Search for dynamic segment using given range. */
      retVal = vSwUpdM_Segment_GetSegmentIdByRange(SegmentId, StartAddress, Length, &vSwUpdM_ExternalSegmentsQueue);
    }

#if (VSWUPDM_SEGMENT == STD_ON)
    /* #200 If no dynamic segment was found and static segments are configured */
    if (retVal != E_OK)
    {
      vSwUpdM_SegmentIterType staticSegmentId;

      /* #210 Iterate over all static segments. */
      for (staticSegmentId = 0u; staticSegmentId < vSwUpdM_GetStaticNumberOfSegments(); staticSegmentId++)
      {
        /* #220 Check requested range against current segment. */
        vSwUpdM_RangeCheckType rangeCheck = vSwUpdM_Range_CheckAgainstRange(
          StartAddress, Length, vSwUpdM_GetStartAddressOfSegment(staticSegmentId), vSwUpdM_GetLengthOfSegment(staticSegmentId));

        /* #230 If ranges at least overlaps segment */
        if (rangeCheck != VSWUPDM_RANGE_CHECK_MISMATCH)
        {
          /* #240 If range is completely contained within current segment */
          if (rangeCheck == VSWUPDM_RANGE_CHECK_CONTAINED)
          {
            /* #250 Return current (static) segment ID. */
            SegmentId->StaticSegmentId = (vSwUpdM_SegmentIdValueType)staticSegmentId;
            SegmentId->DynamicSegmentId = VSWUPDM_INVALID_ID;

            retVal = E_OK;
          }

          /* #260 Ranges at least overlapped, no need to search further. */
          break;
        }
      }
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_SEGMENT_ID_BY_RANGE, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetSegmentIdByRange */

/**********************************************************************************************************************
 * vSwUpdM_GetSegmentIdOfModuleByIndex
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdOfModuleByIndex(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId,
  vSwUpdM_ModuleIdType ModuleId,
  uint32 Index)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a module is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
    else
      /* #30 Check parameter "SegmentId". */
      if (SegmentId == NULL_PTR)
      {
        errorId = VSWUPDM_E_INV_POINTER;
      }
  /* #-- Otherwise: */
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        /* #100 If given module is currently opened
         *   and given index is smaller than number of dynamic segment of the module */
        if ((vSwUpdM_EntityData.OpenIds.ModuleId == ModuleId)
          && (Index < vSwUpdM_EntityData.Count.ExternalSegmentCount))
        {
          vSwUpdM_VarExternalSegmentsQueueIterType index;
          vSwUpdM_QueueHandleType queueHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_ExternalSegmentsQueue);
          vSwUpdM_SegmentIdValueType segmentId;

          /* #110 Get index-th entry in external segments queue (sorted by order of creation). */
          for (index = 1u; index <= Index; index++)
          {
            queueHandle = vSwUpdM_QueueGetEntry(&vSwUpdM_ExternalSegmentsQueue, queueHandle).next;
          }

          /* #120 Return ID of segment associated the queue entry. */
          segmentId = vSwUpdM_QueueGetEntityHandle(&vSwUpdM_ExternalSegmentsQueue, queueHandle);
          SegmentId->DynamicSegmentId = segmentId;
          SegmentId->StaticSegmentId = vSwUpdM_GetVarSegments(segmentId).HandleIDOfVarSegments;

          retVal = E_OK;
        }
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_SEGMENT_ID_OF_MODULE_BY_INDEX, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetSegmentIdOfModuleByIndex */

/**********************************************************************************************************************
 * vSwUpdM_GetSegmentIdOfModuleByType
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentIdOfModuleByType(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR)SegmentId,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_SegmentTypeType SegmentType)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "SegmentId". */
  if (SegmentId == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that module ID is valid. */
    if (vSwUpdM_Module_IsModuleIdValid(ModuleId) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 If component is initialized and given module is currently opened */
      if ((vSwUpdM_General_IsModuleInitialized() == TRUE)
        && (vSwUpdM_EntityData.OpenIds.ModuleId == ModuleId))
      {
        vSwUpdM_SegmentIdValueType segmentId;
        vSwUpdM_QueueHandleType queueHandle = vSwUpdM_QueueGetFirstUsedHandle(&vSwUpdM_InternalSegmentsQueue);

        /* #110 Loop internal segments */
        do
        {
          segmentId = vSwUpdM_QueueGetEntityHandle(&vSwUpdM_InternalSegmentsQueue, queueHandle);

          /* #120 If type of current segment matches the given one */
          if (vSwUpdM_GetVarSegments(segmentId).TypeOfVarSegments == SegmentType)
          {
            /* #130 Return the ID of the current segment. */
            SegmentId->DynamicSegmentId = segmentId;
            SegmentId->StaticSegmentId = vSwUpdM_GetVarSegments(segmentId).HandleIDOfVarSegments;

            retVal = E_OK;

            /* #140 Finish search. */
            break;
          }

          queueHandle = vSwUpdM_QueueGetEntry(&vSwUpdM_InternalSegmentsQueue, queueHandle).next;
        } while (queueHandle != VSWUPDM_QUEUE_HANDLE_HEAD_USED);
      }
#if (VSWUPDM_SEGMENT == STD_ON) && \
    (VSWUPDM_SEGMENTTYPEUSEDOFSEGMENT == STD_ON)
      /* #200 Otherwise, if static segments are configured */
      else
      {
        vSwUpdM_RegionIterType  regionIdx;
        vSwUpdM_RegionIterType  regionCount = vSwUpdM_GetNRegionsOfModule(ModuleId);

        /* #210 Iterate over all regions assigned to given module. */
        for (regionIdx = 0u; regionIdx < regionCount; regionIdx++)
        {
          vSwUpdM_SegmentIterType staticSegmentId;
          vSwUpdM_RegionIterType  staticRegionId = vSwUpdM_GetRegionIdxOfModule2Region(vSwUpdM_GetModule2RegionIdxOfModule(ModuleId) + regionIdx);
          vSwUpdM_SegmentIterType maxSegmentId = (vSwUpdM_SegmentIterType)vSwUpdM_GetSegmentIdxOfRegion(staticRegionId)
            + (vSwUpdM_SegmentIterType)vSwUpdM_GetNumSegmentsOfRegion(staticRegionId);

          /* #220 Iterate over all static segments assigned to current region. */
          for (staticSegmentId = vSwUpdM_GetSegmentIdxOfRegion(staticRegionId); staticSegmentId < maxSegmentId; staticSegmentId++)
          {
            /* #230 If type is configured for current segment and types matches given one */
            if ((vSwUpdM_IsSegmentTypeUsedOfSegment(staticSegmentId))
              && (vSwUpdM_GetSegmentTypeOfSegment(staticSegmentId) == SegmentType))
            {
              /* #231 Return (static) ID of current segment. */
              SegmentId->DynamicSegmentId = VSWUPDM_INVALID_ID;
              SegmentId->StaticSegmentId = (vSwUpdM_SegmentIdValueType)staticSegmentId;

              retVal = E_OK;

              break;
            }
          }

          /* #240 If segment was found
           *   Finish search. */
          if (retVal == E_OK)
          {
            break;
          }
        }
      }
#endif
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_SEGMENT_ID_OF_MODULE_BY_TYPE, errorId);

  return retVal;
  /* PRQA S 6030, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
} /* vSwUpdM_GetSegmentIdOfModuleByType */

/**********************************************************************************************************************
 * vSwUpdM_GetOpenSegmentId
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetOpenSegmentId(
  P2VAR(vSwUpdM_SegmentIdType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentId)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a module is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "SegmentId". */
    if (SegmentId == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_SegmentIdType segmentId;

      /* #100 If a segment is opened
       *   Return ID of opened segment.
       * Otherwise, return invalid ID value. */
      segmentId = vSwUpdM_EntityData.OpenIds.SegmentId;
      *SegmentId = segmentId;

      retVal = E_OK;
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_OPEN_SEGMENT_ID, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetOpenSegmentId */

/**********************************************************************************************************************
 * vSwUpdM_GetSegmentInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_GetSegmentInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo,
  vSwUpdM_SegmentIdType Id)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "SegmentInfo". */
  if (SegmentInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
    /* #20 Check that segment ID is valid. */
    if (vSwUpdM_Segment_IsSegmentIdValid(Id) == FALSE)
    {
      errorId = VSWUPDM_E_WRONG_PARAMETER;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      vSwUpdM_ErrorCode          dummyError;
      vSwUpdM_SegmentIdValueType segmentId;

      /* #100 If module is opened and dynamic segment ID is within the range of internal segments */
      if ((vSwUpdM_General_CommonNegDetChecks(&dummyError, VSWUPDM_COMMON_DET_CHECK_MODULE, VSWUPDM_STATE_CHECK_NONE) == VSWUPDM_E_NO_ERROR)
        && (Id.DynamicSegmentId < vSwUpdM_EntityData.Count.InternalSegmentCount))
      {
        vSwUpdM_VarSegmentsPtrType segment;

        /* #110 Get segment associated with given dynamic segment ID. */
        segmentId = Id.DynamicSegmentId;
        segment = vSwUpdM_GetAddrVarSegments(segmentId);

#if (VSWUPDM_SEGMENT == STD_ON)
        /* #120 If static segments are configured
         *   Verify that the static ID of the dynamic segment is either invalid or matches the given one. */
        if ((Id.StaticSegmentId == VSWUPDM_INVALID_ID)
          || (Id.StaticSegmentId == segment->HandleIDOfVarSegments))
#endif
        {
          /* #130 Return information of current dynamic segment. */
          SegmentInfo->Id.StaticSegmentId = segment->HandleIDOfVarSegments;
          SegmentInfo->Id.DynamicSegmentId = segmentId;
          SegmentInfo->Type = segment->TypeOfVarSegments;
          SegmentInfo->StartAddress = segment->DynamicAttributesOfVarSegment.StartAddress;
          SegmentInfo->EndAddress = segment->EndAddressOfVarSegments;
          SegmentInfo->Length = segment->RealLength;
          SegmentInfo->LengthHandling = segment->DynamicAttributesOfVarSegment.LengthHandling;
          SegmentInfo->State = segment->DynamicAttributesOfVarSegment.State;
          SegmentInfo->IsOverflowable = segment->IsOverflowableOfVarSegments;
          SegmentInfo->RegionId = vSwUpdM_GetVarRegions(segment->RegionIdxOfVarSegments).RegionIDOfVarRegions;
          /* #140 Return apparent write address instead of actual one. */
          vSwUpdM_Segment_GetApparentWriteAddress(segment, &SegmentInfo->WriteAddress);

          retVal = E_OK;
        }
      }
#if (VSWUPDM_SEGMENT == STD_ON)
      /* #200 If static segments are configured and static segment ID is within the range of static segments */
      else if (Id.StaticSegmentId < vSwUpdM_GetStaticNumberOfSegments())
      {
        vSwUpdM_RegionIdType regionId;

        segmentId = Id.StaticSegmentId;

        /* #210 Return configured information of current static segment. */
        SegmentInfo->Id.StaticSegmentId = segmentId;
        SegmentInfo->Id.DynamicSegmentId = VSWUPDM_INVALID_ID;
        SegmentInfo->Type = vSwUpdM_GetSegmentTypeOfSegment(segmentId);
        SegmentInfo->StartAddress = vSwUpdM_GetStartAddressOfSegment(segmentId);
        SegmentInfo->Length = vSwUpdM_GetLengthOfSegment(segmentId);

        /* #220 Calculate end address. */
        SegmentInfo->EndAddress = ((vSwUpdM_AddressType)vSwUpdM_GetStartAddressOfSegment(segmentId) + (vSwUpdM_AddressType)vSwUpdM_GetLengthOfSegment(segmentId)) - 1u;

        /* #230 Initialize dynamic attributes with default values. */
        SegmentInfo->WriteAddress = VSWUPDM_UNDEFINED_ADDRESS;
        SegmentInfo->LengthHandling = VSWUPDM_LENGTH_HANDLING_FIXED;
        SegmentInfo->IsOverflowable = FALSE;
        SegmentInfo->State = VSWUPDM_SEGMENT_STATE_UNDEFINED;

        /* #240 Search region to which segment assigned. */
        if (vSwUpdM_GetRegionIdByRange(&regionId, SegmentInfo->StartAddress, SegmentInfo->Length) == E_OK)
        {
          SegmentInfo->RegionId = regionId; /* PRQA S 2963 */ /* MD_vSwUpdM_2963_InitializationChecked */

          retVal = E_OK;
        }
      }
      else
      {
      }
#endif
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_SEGMENT_INFO, errorId);

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_GetSegmentInfo */

/**********************************************************************************************************************
 * vSwUpdM_InitSegmentInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_InitSegmentInfo(
  P2VAR(vSwUpdM_SegmentInfoType, AUTOMATIC, VSWUPDM_APPL_VAR) SegmentInfo)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "SegmentInfo". */
  if (SegmentInfo == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Initialize given segment information structure with default values. */
    SegmentInfo->Id.DynamicSegmentId = VSWUPDM_INVALID_ID;
    SegmentInfo->Id.StaticSegmentId = VSWUPDM_INVALID_ID;
    SegmentInfo->Type = VSWUPDM_NO_SEGMENTTYPEOFSEGMENT;
    SegmentInfo->StartAddress = VSWUPDM_UNDEFINED_ADDRESS;
    SegmentInfo->EndAddress = VSWUPDM_UNDEFINED_ADDRESS;
    SegmentInfo->WriteAddress = VSWUPDM_UNDEFINED_ADDRESS;
    SegmentInfo->Length = VSWUPDM_UNDEFINED_LENGTH;
    SegmentInfo->LengthHandling = VSWUPDM_LENGTH_HANDLING_DYNAMIC;
    SegmentInfo->State = VSWUPDM_SEGMENT_STATE_UNDEFINED;
    SegmentInfo->IsOverflowable = FALSE;
    SegmentInfo->RegionId = VSWUPDM_INVALID_ID;

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_INIT_SEGMENT_INFO, errorId);

  return retVal;
} /* vSwUpdM_InitSegmentInfo */

/**************************************************************
 *  Memory Abstraction:
 *   - Memory Range
 **************************************************************/

/**********************************************************************************************************************
 * vSwUpdM_EraseRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_EraseRange(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check that range is mapped in memory. */
    if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
    {
      errorId = VSWUPDM_E_INV_RANGE;
    }
  /* #-- Otherwise: */
    else
#endif
      /* ----- Implementation ------------------------------------------------- */
    {
      /* #100 Trigger erase of given range. */
      retVal = vSwUpdM_Range_EraseRange(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_EntityData.OpenIds.PartitionState,
                                        StartAddress, Length, VSWUPDM_SID_ERASE_RANGE, NULL_PTR, vSwUpdM_GetLocalNode());
    }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ERASE_RANGE, errorId);

  return retVal;
} /* vSwUpdM_EraseRange */

/**********************************************************************************************************************
 * vSwUpdM_ReadRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_ReadRange(
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) TargetBuffer,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "TargetBuffer". */
    if (TargetBuffer == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
    else
      /* #30 Check that range is mapped in memory. */
      if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
      {
        errorId = VSWUPDM_E_INV_RANGE;
      }
  /* #-- Otherwise: */
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        vSwUpdM_JobPtrType spawnedJob;
        vSwUpdM_NodeIterType source = vSwUpdM_GetLocalNode();

        /* #100 Enter critical section to ensure exclusive access of state and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #110 Spawn job to read requested data. */
        spawnedJob = vSwUpdM_Job_Spawn(&retVal, VSWUPDM_JOB_TYPE_READ_DATA, VSWUPDM_JOB_OPERATION_DEFAULT,
                                       (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_READ_RANGE, NULL_PTR, source);

        /* #120 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (retVal == E_OK)
        {
          /* #130 Initialize virtual buffer to keep track of progress of read operation
           *      Pass length to be read as used space of the virtual input buffer of the read job. */
          (void) vSwUpdM_Buffer_InitAndAddData(&vSwUpdM_BufferInfoReadData, NULL_PTR, Length);
          /* #140 Initialize buffer information for output data, pointing to given target buffer.
           *   Note: Read job is linked to buffer information also used for write buffer. */
          (void)vSwUpdM_Buffer_Init(&vSwUpdM_BufferInfoWriteData, TargetBuffer, Length);

          /* #160 Pass open entity IDs to job.
           *   Read data starting at given start address. */
          spawnedJob->EntityIds = vSwUpdM_EntityData.OpenIds;
          spawnedJob->TargetAddress = StartAddress;
        }

        /* Leave critical section ensuring exclusive access of state and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_READ_RANGE, errorId);

  return retVal;
  /* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_ReadRange */

/**********************************************************************************************************************
 * vSwUpdM_WriteRange
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_WriteRange(
  P2CONST(uint8, AUTOMATIC, VSWUPDM_APPL_CONST) SourceBuffer,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(SourceBuffer); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(StartAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is idle and a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_IDLE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
    /* #20 Check parameter "SourceBuffer". */
    if (SourceBuffer == NULL_PTR)
    {
      errorId = VSWUPDM_E_INV_POINTER;
    }
    else
      /* #30 Check that range is mapped in memory. */
      if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
      {
        errorId = VSWUPDM_E_INV_RANGE;
      }
      else
#endif
        /* ----- Implementation ------------------------------------------------- */
      {
        /* #100 Service currently not supported, return error. */
        retVal = E_NOT_OK;
      }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_WRITE_RANGE, errorId);

  return retVal;
} /* vSwUpdM_WriteRange */

/**********************************************************************************************************************
 * vSwUpdM_IsRangeErasable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeErasable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(StartAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Verify that range is mapped in memory. */
    if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
    {
      errorId = VSWUPDM_E_INV_RANGE;
    }
    else
    {
      /* #110 Range is erasable when opened partition is erasable. */
      retVal = vSwUpdM_IsPartitionErasable(vSwUpdM_EntityData.OpenIds.PartitionState);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_RANGE_ERASABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRangeErasable */

/**********************************************************************************************************************
 * vSwUpdM_IsRangeReadable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeReadable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(StartAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Verify that range is mapped in memory. */
    if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
    {
      errorId = VSWUPDM_E_INV_RANGE;
    }
    else
    {
      /* #110 Range is readable when opened partition is readable. */
      retVal = vSwUpdM_IsPartitionReadable(vSwUpdM_EntityData.OpenIds.PartitionState);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_RANGE_READABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRangeReadable */

/**********************************************************************************************************************
 * vSwUpdM_IsRangeWritable
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(boolean, VSWUPDM_CODE) vSwUpdM_IsRangeWritable(
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_LengthType Length)
{
  /* ----- Local Variables ------------------------------------------------ */
  boolean           retVal = FALSE;
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  VSWUPDM_DUMMY_STATEMENT(StartAddress); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  VSWUPDM_DUMMY_STATEMENT(Length); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that a partition is opened, including all preconditions. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_PARTITION, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  /* #-- Otherwise: */
  else
#endif
    /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Verify that range is mapped in memory. */
    if (vSwUpdM_Range_IsRangeValid(vSwUpdM_EntityData.OpenIds.PartitionId, StartAddress, Length) == FALSE)
    {
      errorId = VSWUPDM_E_INV_RANGE;
    }
    /* #110 Ranges aren't writable. */
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_IS_RANGE_WRITABLE, errorId);

  return retVal;
} /* vSwUpdM_IsRangeWritable */

/**********************************************************************************************************************
 * vSwUpdM_AlignAddress
 **********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_AlignAddress(
  P2VAR(vSwUpdM_AddressType, AUTOMATIC, VSWUPDM_APPL_CONST) Address,
  vSwUpdM_PartitionStateType State,
  vSwUpdM_AddressAlignmentType Alignment,
  vSwUpdM_AlignGranularityType Granularity)
{
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;
  vSwUpdM_PartitionIdType id;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that component is initialized. */
  if (vSwUpdM_General_CommonNegDetChecks(&errorId, VSWUPDM_COMMON_DET_CHECK_INITIALIZED, VSWUPDM_STATE_CHECK_NONE) != VSWUPDM_E_NO_ERROR)
  {
    /* Error ID already set by check function. */
  }
  else
  /* #20 Check parameter "Address". */
  if (Address == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  else
  /* #30 Check that partition ID is valid. */
  if (vSwUpdM_Part_IsPartitionStateValid(State) == FALSE)
  {
    errorId = VSWUPDM_E_WRONG_PARAMETER;
  }
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Return configured values of requested partition. */
    retVal = vSwUpdM_Part_GetIdByState(&id, State);

    if (retVal == E_OK)
    {
      /* #200 Call internal function to align address to memory device constraints. */
      retVal = vSwUpdM_Range_AlignAddress(Address, id, Alignment, Granularity);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_ALIGN_ADDRESS, errorId);

  return retVal;
} /* vSwUpdM_AlignAddress */

/**********************************************************************************************************************
 * vSwUpdM_GetPaddingValue
 **********************************************************************************************************************/
 /*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE)vSwUpdM_GetPaddingValue(vSwUpdM_VarDataPointerType PaddingValue)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  vSwUpdM_ErrorCode errorId = VSWUPDM_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (VSWUPDM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter "PaddingValue". */
  if (PaddingValue == NULL_PTR)
  {
    errorId = VSWUPDM_E_INV_POINTER;
  }
  /* #-- Otherwise: */
  else
#endif
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #100 Call internal function to get configured padding value. */
    *PaddingValue = (vSwUpdM_DataType)vSwUpdM_GetFillByte();

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
  vSwUpdM_General_HandleDetError(VSWUPDM_SID_GET_PADDING_VALUE, errorId);

  return retVal;
}

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteCallPostHandler
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteCallPostHandler(
  Std_ReturnType Result,
  vSwUpdM_NodeIterType SourceIndex,
  boolean NegativeResponseOnly,
  vSwUpdM_GridSrvc_ServiceIdxType ServiceIndex,
  boolean SourceIndexIsValid)
{
  boolean txResponse = FALSE;

  /* #10 If a negative response is required in case of a negative Result */
  if (NegativeResponseOnly == TRUE)
  {
    if (Result != E_OK)
    {
      /* # 20 A response shall be sent. */
      txResponse = TRUE;
    }
  }
  else /*#30 Otherwise a response shall be sent independent of Result. */
  {
    txResponse = TRUE;
  }

  /* #40 If source of initial request is not known, suppress sending of a response. */
  if (SourceIndexIsValid == FALSE)
  {
    txResponse = FALSE;
  }

  /* #50 Send response if requested. */
  if (txResponse == TRUE)
  {
    vSwUpdM_SrvcRouting_ResultIndicaton(SourceIndex, ServiceIndex, Result);
  }

} /* vSwUpdM_SrvcRouting_RemoteCallPostHandler */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_StartStream
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_StartStream(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2CONST(vSwUpdM_StreamInfoType, AUTOMATIC, VSWUPDM_APPL_DATA)StreamInfo)
{
  Std_ReturnType result = E_NOT_OK;

  VSWUPDM_DUMMY_STATEMENT(ServiceState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Do general checks and prepare service processing. */
  if(vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM) == E_OK)
  {
    /* #20 Call internal function to start stream. */
    result = vSwUpdM_Internal_StartStream(StreamInfo, Source);

    /* #30 In case of failure transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_START_STREAM, TRUE);
  }

  return result;
} /* vSwUpdM_SrvcRouting_StartStream */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteProcessStreamData
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteProcessStreamData(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_LengthType StreamLength
)
{
  Std_ReturnType result = E_NOT_OK;

  /* #10 Do general checks and prepare service processing. */
  if(vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA) == E_OK)
  {
    /* #20 Call internal function to process stream data. */
    result = vSwUpdM_Internal_ProcessStreamData(StreamLength, Source);

    /* #30 In case of failure transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PROCESS_STREAM_DATA, TRUE);
  }

  return result;
} /* vSwUpdM_SrvcRouting_RemoteProcessStreamData */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData
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
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData(
  vSwUpdM_NodeIterType Source,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  vSwUpdM_LengthType StreamBuffer_Length,
  vSwUpdM_LengthType AvailableLength)
{
  Std_ReturnType                result = E_NOT_OK;
  Std_ReturnType                streamResult;


  VSWUPDM_DUMMY_STATEMENT(AvailableLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Check Lock. */
  if (vSwUpdM_RemoteCheckLock(Source) == E_OK)
  {
    /* #20 Request buffer from vStreamProc. */
    vStreamProc_EntryPointInfoType dataEntryPointInfo;

    streamResult = vSwUpdM_Pipe_RequestEntryPoint(vSwUpdM_StreamData.PipeId, vSwUpdM_StreamData.PipeEntryPointData, vStreamProcConf_vStreamProcDataType_uint8, StreamBuffer_Length, &dataEntryPointInfo);

    if (streamResult != E_OK)
    {
      /* #30 If buffer request failed, set error. */
      result = VSWUPDM_E_STREAM_OPERATION_FAILED;
    }
    else
    {
      /* #40 Otherwise: Copy Buffer. */
      vSwUpdM_DataStreamPtrType buffer = vStreamProc_GetTypedWriteRequestBuffer_uint8(&dataEntryPointInfo.WriteRequest);
      vSwUpdM_Buffer_Copy(StreamBuffer, buffer, StreamBuffer_Length);

      /* HINT: The data is acknowledged in VSWUPDM_JOB_STATE_PROCESS_STREAM_EVALUATE_REMOTE_COPY. */

      result = E_OK;
    }

    /* #50 Store response for further processing. */
    vSwUpdM_SetServiceIdOfResponseOfVarNode(Source, (uint8)VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_COPY_STREAM_DATA);
    vSwUpdM_SetResultOfResponseOfVarNode(Source, result);
    vSwUpdM_SetLengthOfResponseOfVarNode(Source, StreamBuffer_Length);
    vSwUpdM_SetResponseValidOfVarNode(Source, TRUE);
  }

  return result;
} /* vSwUpdM_SrvcRouting_RemoteResponseCopyStreamData */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamStart
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamStart(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  vSwUpdM_LengthType AvailableLength)
{
  Std_ReturnType            result;

  /* #10 Check plausibility of input parameters. */
  result = vSwUpdM_RemoteStreamCheckPreconditions(Source, ProcessHandle, Handle, VSWUPDM_REMOTESTREAMSTATE_RX_PREPARED);

  /* #20 Check if requested buffer size exceeds available buffer size */
  if (result == E_OK)
  {
    if (AvailableLength > vSwUpdM_RemoteStream_List[Handle].BufferSize)
    {
      result = E_NOT_OK;
    }
  }

  /* #30 If everything is fine, */
  if (result == E_OK)
  {
    /* #40 Prepare request for data transmission. */
    vSwUpdM_RemoteStream_List[Handle].AvailableLength = AvailableLength;
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_RX_COPY_RESPOND;
  }

  /* # 50 In case of failure transmit negative response immediately. */
  vSwUpdM_RemoteStreamCallPostHandler(result, Source, ProcessHandle, Handle, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END);

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRouting_RemoteStreamStart */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamCopy
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamCopy(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  P2VAR(uint8, AUTOMATIC, VSWUPDM_APPL_VAR) StreamBuffer, /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
  vSwUpdM_LengthType StreamBuffer_Length,
  Std_ReturnType Result)
{
  /* INTERNAL_COMMENT_10 */
  Std_ReturnType result = E_NOT_OK;

  /* #10 Propagate negative Result response:
   *     Set stream state to FAIL to signalize to the initiator of the transmission that the transmission failed.
   */
  if (Result != E_OK)
  {
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_FAIL;
  }
  else
  {
    /* #20 Check plausibility of input parameters. */
    result = vSwUpdM_RemoteStreamCheckPreconditions(Source, ProcessHandle, Handle, VSWUPDM_REMOTESTREAMSTATE_RX_COPY);

    /* #30 Check if received number of bytes does not exceed the expectation. */
    if (result == E_OK)
    {
      if ((StreamBuffer_Length + vSwUpdM_RemoteStream_List[Handle].Offset) > vSwUpdM_RemoteStream_List[Handle].BufferSize)
      {
        result = E_NOT_OK;
      }
    }

    if (result == E_OK)
    {
      /* #40 Consume received data. */
      vSwUpdM_Buffer_Copy(StreamBuffer, &vSwUpdM_RemoteStream_List[Handle].Buffer[vSwUpdM_RemoteStream_List[Handle].Offset], StreamBuffer_Length);
      vSwUpdM_RemoteStream_List[Handle].Offset += StreamBuffer_Length;

      /* #50 If all expected data is received */
      if (vSwUpdM_RemoteStream_List[Handle].Offset == vSwUpdM_RemoteStream_List[Handle].AvailableLength)
      {
        /* #60 Stream shall be ended now */
        vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_RX_TRANSMIT_END;
      }
      else
      {
        /* #70 Next bunch of data shall be requested. */
        vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_RX_COPY_RESPOND;
      }
    }

    /* #80 In case of failure transmit negative response immediately. */
    vSwUpdM_RemoteStreamCallPostHandler(result, Source, ProcessHandle, Handle, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_END);
  }

  return result;
  /* PRQA S 6010, 6030, 6060 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC,  MD_MSR_STPAR */
} /* vSwUpdM_SrvcRouting_RemoteStreamCopy */

/**********************************************************************************************************************
 vSwUpdM_SrvcRouting_RemoteStreamRequest
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamRequest(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  Std_ReturnType Result,
  vSwUpdM_LengthType BufferSize)
{
  Std_ReturnType            result;

  /* #10 Check plausibility of input parameters. */
  result = vSwUpdM_RemoteStreamCheckPreconditions(Source, ProcessHandle, Handle, VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE);

  /* #20 Propagate Result.*/
  if (Result != E_OK)
  {
    result = Result;
  }

  /* #30 If everything is fine, */
  if (result == E_OK)
  {
    /* #40 Prepare transmission of data. */
    vSwUpdM_RemoteStream_List[Handle].BufferSize = BufferSize;
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_TX_RESPONSE_TRANSMIT;
  }

  /* #50 In case of failure transmit negative response immediately. */
  vSwUpdM_RemoteStreamCallPostHandler(result, Source, ProcessHandle, Handle, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_STREAM_COPY);

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRouting_RemoteStreamRequest */

/**********************************************************************************************************************
 vSwUpdM_SrvcRoutingRemoteStreamEnd
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteStreamEnd(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ProcessHandleOfDataProcessesType ProcessHandle,
  vSwUpdM_RemoteStreamHandleType Handle,
  Std_ReturnType Result)
{
  Std_ReturnType            result;

  /* #10 Check plausibility of input parameters. */
  result = vSwUpdM_RemoteStreamCheckPreconditions(Source, ProcessHandle, Handle, VSWUPDM_REMOTESTREAMSTATE_TX_WAIT_END);

  /* #20 Propagate negative result. */
  if (Result != E_OK)
  {
    result = Result;
  }

  /* #30 Check if stream is completed. */
  if (result == E_OK)
  {
    if (vSwUpdM_RemoteStream_List[Handle].Offset != vSwUpdM_RemoteStream_List[Handle].AvailableLength)
    {
      result = E_NOT_OK;
    }
  }

  /* #40 If successful */
  if (result == E_OK)
  {
    /* #50 Set stream state to IDLE. */
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_IDLE;
  }
  else
  {
    /* #60 Otherwise set stream state to FAIL to signalize to the initiator of the transmission that the transmission failed. */
    vSwUpdM_RemoteStream_List[Handle].State = VSWUPDM_REMOTESTREAMSTATE_FAIL;
  }

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRoutingRemoteStreamEnd */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_AddSegment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_AddSegment(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteSegmentInfo)
{
  Std_ReturnType result = E_NOT_OK;
  vSwUpdM_SegmentInfoType segmentInfo;

  VSWUPDM_DUMMY_STATEMENT(ServiceState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Do general checks and prepare service processing. */
  if(vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT) == E_OK)
  {
    (void)vSwUpdM_InitSegmentInfo(&segmentInfo);

    segmentInfo.StartAddress = RemoteSegmentInfo->StartAddress;
    segmentInfo.Length = RemoteSegmentInfo->InitialLength;
    segmentInfo.LengthHandling = RemoteSegmentInfo->LengthHandling;
    segmentInfo.Type = RemoteSegmentInfo->Type;
    segmentInfo.IsOverflowable = RemoteSegmentInfo->IsOverflowable;

    if (RemoteSegmentInfo->State == VSWUPDM_SEGMENT_STATE_FINALIZED)
    {
      result = vSwUpdM_Internal_AddFinalizedSegment(&segmentInfo, Source);
    }
    else
    {
      /* #30 Call internal function to add a segment. */
      result = vSwUpdM_Internal_AddSegment(&segmentInfo, Source);
    }

    /* #40 In case of failure transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, VSWUPDM_GRIDSRVC_SERVICEIDX_ADD_SEGMENT, TRUE);
  }

  return result;
} /* vSwUpdM_SrvcRouting_AddSegment */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_ProcessModuleService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ProcessModuleService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_ModuleIdType ModuleId,
  vSwUpdM_ProcessIdType ProcessId,
  P2CONST(vSwUpdM_ProcessInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) ProcessInfo)
{

  Std_ReturnType result = E_NOT_OK;
  Std_ReturnType preconditions;

  /* #10 Do general checks and prepare service processing. */

  preconditions = vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service);

  /* #20 If service is valid, call internal function: */
  if (preconditions == E_OK)
  {
    switch (Service)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_MODULE:
      {
        result = vSwUpdM_Internal_VerifyModule(ModuleId, ProcessInfo, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_PROCESS_MODULE:
      {
        result = vSwUpdM_Internal_ProcessModule(ModuleId, ProcessId, ProcessInfo, Source);
        break;
      }
      default:
      {
        /* Invalid service. */
        vSwUpdM_DevError_AssertFail(VSWUPDM_DEVERROR_ASSERT_54); /* PRQA S 4304, 2996 */ /* MD_MSR_AutosarBoolean, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
        break;
      }
    }
    /* #30 Transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }


  return result;
  /* PRQA S 6060 1 */ /* MD_MSR_STPAR */
} /* vSwUpdM_SrvcRouting_ProcessModuleService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleState(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ModuleStateType State)
{
  Std_ReturnType           result;
  vSwUpdM_ModuleIdType     moduleId = VSWUPDM_INVALID_ID;
  boolean immediateConfirmation = TRUE;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE);

  /* #20 Get ModuleId. */
  result = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHandle);

  if (result == E_OK)
  {
    vSwUpdM_NodeGroupOwnersIdxOfModuleType moduleOwnerGroupIndex;
    moduleOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId);

    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(moduleOwnerGroupIndex))
    {
      /* A module is either remote _or_ local, shared modules are not yet supported. */
      result = E_NOT_OK;
    }
  }

  /* #30 If all inputs are valid.*/
  if (result == E_OK)
  {
    /* #40 Update module state with given value. */
    result = vSwUpdM_Module_UpdateState(vSwUpdM_EntityData.OpenIds.PartitionId, moduleId, (vSwUpdM_ModuleStateType)State);

    if (result == E_OK)
    {
      /* #50 Trigger persisting of updated state. */
      result = vSwUpdM_Module_PersistStateAndConfirm(vSwUpdM_EntityData.OpenIds.PartitionId,
                                                     vSwUpdM_EntityData.OpenIds.PartitionState,
                                                     moduleId, VSWUPDM_SID_UPDATE_MODULE_STATE, NULL_PTR, Source);
    }

    immediateConfirmation = FALSE;
  }

  /* #60 In case of failure transmit negative response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_STATE, immediateConfirmation);

  return result;
  /* PRQA S 6010 1 */ /* MD_MSR_STPTH */
} /* vSwUpdM_SrvcRouting_RemoteUpdateModuleState */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleValid
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleValid(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ValidType Validity,
  vSwUpdM_RevisionUpdateType RevisionUpdate)
{
  Std_ReturnType             result;
  vSwUpdM_ModuleIdType       moduleId       = VSWUPDM_INVALID_ID;
  vSwUpdM_ValidType          validity;
  vSwUpdM_ModuleStateType    moduleState;
  vSwUpdM_RevisionUpdateType revisionUpdate = VSWUPDM_REVISION_UPDATE_NONE; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID);

  /* #20 Get ModuleId. */
  result = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHandle);

  if (RevisionUpdate < (uint32)VSWUPDM_REVISION_UPDATE_SIZE)
  {
    revisionUpdate = RevisionUpdate;
  }
  else
  {
    result = VSWUPDM_E_REMOTE_ENUM_CONVERSION_FAILED;
  }

  if (result == E_OK)
  {
    result = vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, vSwUpdM_EntityData.OpenIds.PartitionId);
  }

  if (result == E_OK)
  {
    vSwUpdM_NodeGroupOwnersIdxOfModuleType moduleOwnerGroupIndex;
    moduleOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId);

    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(moduleOwnerGroupIndex))
    {
      /* A module is either remote _or_ local, shared modules are not yet supported. */
      result = E_NOT_OK;
    }
  }

  /* #30 If all inputs are valid. */
  if (result == E_OK)
  {
    if (((boolean)Validity) == TRUE)
    {
      validity = VSWUPDM_VALIDITY_VALID;
    }
    else
    {
      validity = VSWUPDM_VALIDITY_INVALID;
    }

    /* #40 Call internal function to update module validity. */
    result = vSwUpdM_Module_UpdateValid(vSwUpdM_EntityData.OpenIds.PartitionState, moduleId, validity,
                                        revisionUpdate, VSWUPDM_SID_UPDATE_MODULE_VALID, Source, NULL_PTR);
  }

  /* #50 In case of failure transmit negative response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_VALID, TRUE);

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRouting_RemoteUpdateModuleValid */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ModuleHandleIdType ModuleHandle,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts)
{
  Std_ReturnType           result;
  vSwUpdM_ModuleIdType     moduleId = VSWUPDM_INVALID_ID;
  vSwUpdM_ModuleStateType  moduleState;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS);

  /* #20 Get ModuleId. */
  result = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHandle);

  if (result == E_OK)
  {
    result = vSwUpdM_Module_GetStateByPartition(&moduleState, moduleId, vSwUpdM_EntityData.OpenIds.PartitionId);
  }

  if (result == E_OK)
  {
    vSwUpdM_NodeGroupOwnersIdxOfModuleType moduleOwnerGroupIndex;
    moduleOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfModule(moduleId);

    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(moduleOwnerGroupIndex))
    {
      /* A module is either remote _or_ local, shared modules are not yet supported. */
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
  /* #30 Call internal function to update module programming attempts counter. */
    result = vSwUpdM_Module_UpdateProgrammingAttempts(ProgrammingAttempts, vSwUpdM_EntityData.OpenIds.PartitionId, moduleId);
  }

  /* #40 Transmit response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_MODULE_PROGRAMMING_ATTEMPTS, TRUE);

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRouting_RemoteUpdateModuleProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateRegionState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateRegionState(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_RegionHandleIdType RegionHandle,
  vSwUpdM_RegionStateType State)
{
  Std_ReturnType result;
  vSwUpdM_RegionIdxType regionIdx = VSWUPDM_INVALID_ID; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vSwUpdM_ModuleIdType regionId = VSWUPDM_INVALID_ID;
  boolean immediateConfirmation = TRUE;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE);

  /* #20 Check plausibility of input parameters. */
  result = vSwUpdM_GetRegionIdByHandle(&regionId, RegionHandle);

  if (result == E_OK)
  {
    vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex;
    regionOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(regionId);

    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(regionOwnerGroupIndex))
    {
      /* A region is either remote _or_ local, shared regions are not yet supported. */
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    regionIdx = vSwUpdM_Region_GetRegionIdx(regionId);

    /* #30 If all inputs are valid. */
    if (regionIdx != VSWUPDM_INVALID_ID)
    {
      /* #40 Call internal function to update region state. */
      vSwUpdM_Region_UpdateState(regionIdx, (vSwUpdM_RegionStateType)State);
      (void)vSwUpdM_Region_PersistState(vSwUpdM_EntityData.OpenIds.PartitionId, vSwUpdM_GetModuleIdxOfRegion(regionId),
                                        regionIdx, VSWUPDM_SID_UPDATE_REGION_STATE, NULL_PTR, Source);
      /* Suppress immediate response in good-case. */
      immediateConfirmation = FALSE;
    }
    else
    {
      /* Region is not present - nothing to do here. Transmit positive response immediately. */
    }
  }
  /* #50 Transmit response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_STATE, immediateConfirmation);

  return result;
  /* PRQA S 6010 1 */ /* MD_MSR_STPTH */
} /* vSwUpdM_SrvcRouting_RemoteUpdateRegionState */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_RegionHandleIdType RegionHandle,
  vSwUpdM_ProgrammingAttemptsType ProgrammingAttempts)
{
  Std_ReturnType result;
  vSwUpdM_RegionIdxType regionIdx = VSWUPDM_INVALID_ID; /* PRQA S 2981 */ /* MD_vSwUpdM_Rule2.2_2981_2892_RedundantInitialization */
  vSwUpdM_ModuleIdType regionId = VSWUPDM_INVALID_ID;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS);

  result = vSwUpdM_GetRegionIdByHandle(&regionId, RegionHandle);

  if (result == E_OK)
  {
    vSwUpdM_NodeGroupOwnersIdxOfRegionType regionOwnerGroupIndex;
    regionOwnerGroupIndex = vSwUpdM_GetNodeGroupOwnersIdxOfRegion(regionId);

    if (vSwUpdM_IsWithLocalNodeOfNodeGroup(regionOwnerGroupIndex))
    {
      /* A region is either remote _or_ local, shared regions are not yet supported. */
      result = E_NOT_OK;
    }
  }

  if (result == E_OK)
  {
    regionIdx = vSwUpdM_Region_GetRegionIdx(regionId);

    /* #20 If all inputs are valid. */
    if (regionIdx != VSWUPDM_INVALID_ID)
    {
      /* #30 Call internal function to update region programming attempts counter. */
      vSwUpdM_Region_UpdateProgrammingAttempts(regionIdx, ProgrammingAttempts);
    }
    else
    {
      /* Region is not present - nothing to do here. Transmit positive response immediately. */
    }
  }

  /* #50 Transmit response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_REGION_PROGRAMMING_ATTEMPTS, TRUE);

  return result;
  /* PRQA S 6010 1 */ /* MD_MSR_STPTH */
} /* vSwUpdM_SrvcRouting_RemoteUpdateRegionProgrammingAttempts */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes(
  vSwUpdM_NodeIterType Source,
  P2CONST(vSwUpdM_RemoteSegmentInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) RemoteSegmentInfo,
  vSwUpdM_SegmentStateType State)
{
  Std_ReturnType             result;
  vSwUpdM_SegmentIdValueType segmentIdValue = VSWUPDM_INVALID_ID;
  vSwUpdM_SegmentIdType      segmentId;

  result = vSwUpdM_Segment_SearchSegment(&segmentIdValue, RemoteSegmentInfo->StartAddress);

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES);

  /* #20 If all inputs are valid. */
  if (result == E_OK)
  {
    /* #30 Call internal function to update segments. */
    segmentId.DynamicSegmentId = segmentIdValue;
    (void)vSwUpdM_Segment_UpdateAndPersistStateAndConfirm(segmentId, VSWUPDM_SID_UPDATE_SEGMENT_ATTRIBUTES, (vSwUpdM_SegmentStateType)State, Source, NULL_PTR);
  }

  /* #40 In case of failure, transmit negative response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_SEGMENT_ATTRIBUTES, TRUE);

  return result;
} /* vSwUpdM_SrvcRouting_RemoteUpdateSegmentAttributes */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo(
  vSwUpdM_NodeIterType Source,
  P2CONST(vSwUpdM_BkPersist_ResumeInfoType, AUTOMATIC, VSWUPDM_APPL_DATA) ResumeInfo)
{
  Std_ReturnType result;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO);

  /* #20 Call internal function to update ResumeInfo. */
  result = vSwUpdM_ResumeInfo_UpdateAndPersistStateAndConfirm(ResumeInfo->PartitionState, ResumeInfo->CurrentService, ResumeInfo->ServiceState, ResumeInfo->MemoryAddress, ResumeInfo->StreamAddress, ResumeInfo->TriggerAddress, ResumeInfo->IsAddressValid, VSWUPDM_SID_UPDATE_RESUME_INFO, Source);

  /* #30 In case of failure, transmit negative response immediately. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_PERSIST_RESUME_INFO, TRUE);

  return result;
} /* vSwUpdM_SrvcRouting_RemoteUpdateResumeInfo */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteProcessRequestInput
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteProcessRequestInput(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_ProcessHandleOfDataProcessesType DataProcessHandle,
  uint8 InputIndex)
{
  Std_ReturnType                result;
  vSwUpdM_JobPtrType            spawnedJob;
  vSwUpdM_DataProcessesIterType processId = 0u;

  result = vSwUpdM_GetProcessIdByProcessHandle(DataProcessHandle, &processId);

  if (vSwUpdM_SrvcRouting_HandleServiceState(ServiceState, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO) == E_OK)
  {
    /* #10 Acquire response buffer. */
    vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO);

    /* #20 If service is initially announced: */
    if (ServiceState == VSWUPDM_EXCTSCHEDULE_SERVICESTATE_RUN)
    {

      if (result == E_OK)
      {
        if (vSwUpdM_ProcessData.ProcessId != processId)
        {
          result = VSWUPDM_E_REMOTE_WRONG_PIPE;
        }
      }

      if (result == E_OK)
      {
        if (InputIndex > vSwUpdM_ProcessUserData.InputCount)
        {
          result = VSWUPDM_E_REMOTE_PIPE_NUMBER_OF_INPUTS;
        }
      }
      /* #30 If all inputs are valid. */
      if (result == E_OK)
      {
        /* #40 Enter critical section to ensure exclusive access of partition states and job queue. */
        VSWUPDM_ENTER_CRITICAL_SECTION();

        /* #50 spawn job to stream input data to remote. */
        spawnedJob = vSwUpdM_Job_Spawn(&result, VSWUPDM_JOB_TYPE_REMOTE_PROCESS_INFO, VSWUPDM_JOB_OPERATION_DEFAULT,
          (vSwUpdM_QueuePrioType)VSWUPDM_JOB_PRIO_DEFAULT, VSWUPDM_SID_REQUEST_PROCESS_INFO, NULL_PTR, Source);

        /* #60 Job attributes are safe to be modified when job was successfully spawned and access is still protected by critical section. */
        if (result == E_OK)
        {
          spawnedJob->Count = InputIndex;
          spawnedJob->RemoteTarget = Source;
        }

        /* #70 Leave critical section ensuring exclusive access of partition states and job queue. */
        VSWUPDM_LEAVE_CRITICAL_SECTION();
      }

      /* #80 In case of failure, transmit negative response immediately. */
      vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_REQUEST_PROCESS_INFO, TRUE);
    }
  }

  return result;
  /* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
} /* vSwUpdM_SrvcRouting_RemoteProcessRequestInput */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RemoteConcludeSegment
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RemoteConcludeSegment(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_AddressType StartAddress,
  vSwUpdM_AddressType WriteAddress)
{
  Std_ReturnType        result;
  vSwUpdM_SegmentIdType segmentId = VSWUPDM_SEGMENT_ID_DEFAULT;

  /* #10 Acquire response buffer. */
  vSwUpdM_SrvcRouting_OpenRxChannel(Source, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT);

  /* #20 Check if StartAddress is valid. */
  result = vSwUpdM_Segment_GetSegmentIdByStartAddress(&segmentId, StartAddress, &vSwUpdM_ExternalSegmentsQueue);

  if (result == E_OK)
  {
    vSwUpdM_VarSegmentsPtrType segment = vSwUpdM_GetAddrVarSegments(segmentId.DynamicSegmentId);

    if (vSwUpdM_Segment_IsSegmentIdAllowed(segmentId) != TRUE)
    {
      result = E_NOT_OK;
    }
    else if (vSwUpdM_Range_IsAddressInRange(WriteAddress, segment->DynamicAttributesOfVarSegment.StartAddress, (segment->RealLength + 1u)) != TRUE)
    {
      result = E_NOT_OK;
    }
    else
    {
      /* #30 Forward call to internal function. */
      vSwUpdM_Segment_ConcludeSegment(segment, WriteAddress, WriteAddress);
    }
  }

  /* #40 Transmit response. */
  vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, VSWUPDM_GRIDSRVC_SERVICEIDX_LEGACY_CONCLUDE_SEGMENT, TRUE);

  return result;

  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_RemoteConcludeSegment */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_GenericService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_GenericService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service)
{
  Std_ReturnType result = E_NOT_OK;
  Std_ReturnType preconditions;

  /* #10 Do general checks and prepare service processing. */
  preconditions = vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service);

  /* #20 If service is valid:
   * call internal function. */
  if (preconditions == E_OK)
  {
    switch (Service)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_START:
      {
        result = vSwUpdM_Internal_Start(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_END_STREAM:
      {
        result = vSwUpdM_Internal_EndStream(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CHECK_PARTITION:
      {
        result = vSwUpdM_Internal_CheckPartitionConsistency(&vSwUpdM_ProcessUserData, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_VALID:
      {
        result = vSwUpdM_Internal_ValidatePartition(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SET_PARTITION_INVALID:
      {
        result = vSwUpdM_Internal_InvalidatePartition(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_PARTITION:
      {
        result = vSwUpdM_Internal_SyncPartition(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SWAP_PARTITION:
      {
        result = vSwUpdM_Internal_SwapActivePartition(Source);
        break;
      }
      default:
      {
        /* Invalid service. */
        vSwUpdM_DevError_AssertFail(VSWUPDM_DEVERROR_ASSERT_55); /* PRQA S 4304, 2996 */ /* MD_MSR_AutosarBoolean, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
        break;
      }
    }

    /* #30 Transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_GenericService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_PartitionService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_PartitionService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_PartitionStateType PartitionState)
{
  Std_ReturnType                  result       = E_NOT_OK;

  /* #10 Do general checks and prepare service processing. */
  if (Service == VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_PARTITION)
  {
    if(vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service) == E_OK)
    {
      /* #20 Forward call to internal function. */
      result = vSwUpdM_Internal_OpenPartition(PartitionState, Source);

      /* #30 Transmit negative response immediately. */
      vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
    }
  }

  return result;
} /* vSwUpdM_SrvcRouting_PartitionService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_ModuleService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_ModuleService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_ModuleIdType ModuleId)
{
  Std_ReturnType result = E_NOT_OK;
  Std_ReturnType preconditions;

  /* #10 Do general checks and prepare service processing. */
  preconditions = vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service);

  /* #20 If service is valid:
   * call internal function. */
  if (preconditions == E_OK)
  {
    switch (Service)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_MODULE:
      {
        result = vSwUpdM_Internal_OpenModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_MODULE:
      {
        result = vSwUpdM_Internal_CloseModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_MODULE:
      {
        result = vSwUpdM_Internal_EraseModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_MODULE:
      {
        result = vSwUpdM_Internal_FinalizeModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SYNC_MODULE:
      {
        result = vSwUpdM_Internal_SyncModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_VALIDATE_MODULE:
      {
        result = vSwUpdM_Internal_ValidateModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_INVALIDATE_MODULE:
      {
        result = vSwUpdM_Internal_InvalidateModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLEAR_SEGMENTS_OF_MODULE:
      {
        result = vSwUpdM_Internal_ClearSegmentsOfModule(ModuleId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_INDICATE_WRITE_TO_MODULE:
      {
        result = vSwUpdM_Internal_IndicateWriteToModule(ModuleId, Source);
        break;
      }
      default:
      {
        /* Invalid service. */
        vSwUpdM_DevError_AssertFail(VSWUPDM_DEVERROR_ASSERT_56); /* PRQA S 4304, 2996 */ /* MD_MSR_AutosarBoolean, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
        break;
      }
    }

    /* #30 Transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */

  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_ModuleService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_RegionService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_RegionService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_RegionIdType RegionId)
{
  Std_ReturnType           result = E_NOT_OK;

  /* #10 Do general checks and prepare service processing. */
  if (Service == VSWUPDM_GRIDSRVC_SERVICEIDX_ERASE_REGION)
  {
    if(vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service) == E_OK)
    {
      /* #20 Forward call to internal function. */
      result = vSwUpdM_Internal_EraseRegion(RegionId, Source);

      /* #30 Transmit negative response immediately. */
      vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
    }
  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_RegionService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_SegmentService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_SegmentService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service,
  vSwUpdM_SegmentIdType SegmentId)
{
  Std_ReturnType result = E_NOT_OK;
  Std_ReturnType preconditions;

  /* #10 Do general checks and prepare service processing. */
  preconditions = vSwUpdM_SrvcRouting_MainChannelServicePreparation(Source, ServiceState, Service);

  /* #20 If service is valid:
   *     call internal function. */
  if(preconditions == E_OK)
  {
    switch (Service)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_OPEN_SEGMENT:
      {
        result = vSwUpdM_Internal_OpenSegment(SegmentId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_CLOSE_SEGMENT:
      {
        result = vSwUpdM_Internal_CloseSegment(SegmentId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_FINALIZE_SEGMENT:
      {
        result = vSwUpdM_Internal_FinalizeSegment(SegmentId, Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_VERIFY_SEGMENT:
      {
        /* Only basic implementation supported yet: Call is forwarded
          * But no processInfo is provided etc. */
        (void)vSwUpdM_InitProcessInfo(&vSwUpdM_ProcessUserData);
        result = vSwUpdM_Internal_VerifySegment(SegmentId, &vSwUpdM_ProcessUserData, Source);
        break;
      }
      default:
      {
        /* Invalid Service. */
        vSwUpdM_DevError_AssertFail(VSWUPDM_DEVERROR_ASSERT_57); /* PRQA S 4304, 2996 */ /* MD_MSR_AutosarBoolean, MD_vSwUpdM_Rule14.3_2991_2992_2995_2996_Rule2.2_AlwaysTrueFalse */
        break;
      }
    }

    /* #30 Transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, Service, TRUE); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_SegmentService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_MaintenanceService
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_MaintenanceService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_ExctSchedule_ServiceStateType ServiceState,
  vSwUpdM_GridSrvc_ServiceIdxType Service)
{
  boolean immediateConfirmation = TRUE;
  Std_ReturnType result = E_NOT_OK;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = Service;

  VSWUPDM_DUMMY_STATEMENT(ServiceState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #100 If service is LOCK: */
  if (serviceIndex == VSWUPDM_GRIDSRVC_SERVICEIDX_LOCK)
  {
    /* #120 Acquire response buffer. */
    vSwUpdM_SrvcRouting_OpenRxChannel(Source, serviceIndex);

    /* #130 Enter critical section to ensure exclusive access on lock. */
    VSWUPDM_ENTER_CRITICAL_SECTION();

    /* #132 Check if lock is in unlocked state. */
    if (vSwUpdM_RemoteLockIsGrantedTo != VSWUPDM_INVALID_NODE)
    {
      /* Send negative response */
      result = VSWUPDM_E_RESPONSE_ALREADY_LOCKED;
    }
    /* #133 Check if source is allowed to be a master. */
    else if (!vSwUpdM_IsMasterAllowedOfNode(Source))
    {
      /* Send negative response */
      result = VSWUPDM_E_RESPONSE_PRIVILEGE;
    }
    else
    {
      /* #134 Grant lock to the requester. */
      result = E_OK;
      vSwUpdM_RemoteLockIsGrantedTo = Source;
    }

    /* #140 Leave critical section ensuring exclusive access on lock. */
    VSWUPDM_LEAVE_CRITICAL_SECTION();

    /* #150 Transmit response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, FALSE, serviceIndex, immediateConfirmation); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }
  else
  {
    /* #200 If lock is already granted: */
    if (vSwUpdM_RemoteCheckLock(Source) == E_OK)
    {

      /* #220 Evaluate service: */
      switch (serviceIndex)
      {
        case VSWUPDM_GRIDSRVC_SERVICEIDX_UNLOCK:
        {
        /* #222 UNLOCK Service:
         *      Call internal function to trigger Shutdown.*/
          vSwUpdM_SrvcRouting_OpenRxChannel(Source, serviceIndex);
          result = vSwUpdM_Internal_Shutdown(Source);
          break;
        }
        default:
        /* case VSWUPDM_GRIDSRVC_SERVICEIDX_SHUTDOWN: */
        /* #223 SHUTDOWN Service:
         *      Call internal function to trigger Shutdown.*/
        {
          immediateConfirmation = FALSE;
          break;
        }
      }

      /* #300 Transmit negative response immediately. */
      vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, serviceIndex, immediateConfirmation); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
    }
  }

  return result;
/* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_MaitenanceService */

/**********************************************************************************************************************
 * vSwUpdM_SrvcRouting_SuspendService
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VSWUPDM_CODE) vSwUpdM_SrvcRouting_SuspendService(
  vSwUpdM_NodeIterType Source,
  vSwUpdM_GridSrvc_ServiceIdxType Service)
{
  Std_ReturnType           result = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  boolean                  immediateConfirmation = TRUE;
  vSwUpdM_GridSrvc_ServiceIdxType serviceIndex = Service;

  /* #10 Check Lock. */
  if (vSwUpdM_RemoteCheckLock(Source) == E_OK)
  {

    /* #30 Depending on requested Service: */
    switch (serviceIndex)
    {
      case VSWUPDM_GRIDSRVC_SERVICEIDX_SUSPEND:
      /* #100 SUSPEND requested: */
      {
        /* #110 Call internal function to suspend. */
        vSwUpdM_SrvcRouting_OpenRxChannel(Source, serviceIndex);
        result = vSwUpdM_Internal_Suspend(Source);
        break;
      }
      case VSWUPDM_GRIDSRVC_SERVICEIDX_RESUME:
      /* #200 SUSPEND requested: */
      {
        /* #210 Call internal function to resume. */
        vSwUpdM_SrvcRouting_OpenRxChannel(Source, serviceIndex);
        result = vSwUpdM_State_Resume(VSWUPDM_SID_RESUME, NULL_PTR, Source);
        break;
      }
      default:
      {
        immediateConfirmation = FALSE;
        break;
      }
    }

    /* #300 Transmit negative response immediately. */
    vSwUpdM_SrvcRouting_RemoteCallPostHandler(result, Source, TRUE, serviceIndex, immediateConfirmation); /* PRQA S 4342 */ /* MD_vSwUpdM_Rule10.5_4342_EnumParameterCast */
  }

  return result;
  /* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
} /* vSwUpdM_SrvcRouting_SuspendService */

#define VSWUPDM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: vSwUpdM_Services.c
 *********************************************************************************************************************/
