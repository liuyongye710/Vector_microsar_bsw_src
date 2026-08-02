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
/*!        \file  TcpIp_Tls.c
 *        \brief  Transport Layer Security (TLS) main API source file.
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#define TCPIP_TLS_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "TcpIp_Lcfg.h"
# include "TcpIp_Tls.h"
# include "TcpIp_TlsCore.h"
# include "TcpIp_TlsServer.h"
# include "TcpIp_TlsClient.h"
# include "TcpIp.h"
# include "TcpIp_Tcp.h"

# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
# if !defined (TCPIP_LOCAL)
#  define TCPIP_LOCAL static
# endif

# if !defined (TCPIP_LOCAL_INLINE)
#  define TCPIP_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define TCPIP_START_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_Tls_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 No memory section to initialize - left blank intentionally */
} /* TcpIp_Tls_InitMemory() */

/**********************************************************************************************************************
 *  TcpIp_Tls_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_Init( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize sub-modules */
  TcpIp_TlsCore_Init();

/*
[REVIEW_G] c_accepted 16.00.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  TcpIp_TlsServer_Init();
# endif /* TCPIP_SUPPORT_ASRTLSSERVER == STD_ON */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  TcpIp_TlsClient_Init();
# endif /* TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON */

} /* TcpIp_Tls_Init() */

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionRx(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call main function for reception */
  TcpIp_TlsCoreMainFunction_Rx();
} /* TcpIp_Tls_MainFunctionRx() */

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionState(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call main function for states */
  TcpIp_TlsCoreMainFunction_State();
} /* TcpIp_Tls_MainFunctionState() */

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionTx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionTx(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call main function for transmission */
  TcpIp_TlsCoreMainFunction_Tx();
} /* TcpIp_Tls_MainFunctionTx() */

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionLowPrio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionLowPrio(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check initialization of the component. */
  if (TcpIp_State == TCPIP_STATE_UNINIT)
  {
    /* module is not initialized, so do nothing here but just return */
  }
  else
  {
    /* #20 Call low prio main function */
    TcpIp_TlsCoreMainFunction_LowPrio();
  }

} /* TcpIp_Tls_MainFunctionLowPrio() */

/**********************************************************************************************************************
 *  TcpIp_Tls_RxIndicaion
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_RxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DataPtr,
  uint16                       DataLen)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward the call to the internal TLS lower layer RxIndication */
  TcpIp_TlsCoreLl_RxIndication(SocketTcpIdx, DataPtr, DataLen);

} /* TcpIp_Tls_RxIndicaion() */

/**********************************************************************************************************************
 *  TcpIp_Tls_ChangeParameter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ChangeParameter(
  TcpIp_SizeOfSocketDynType    SocketIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());

  /* ----- Implementation ----------------------------------------------- */
  if (TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))
  {
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    /* #10 Forward the change parameter request to the TLS core unit */
    switch (OptName)
    {
      case TCPIP_PARAMID_TLS_CONNECTION_ASSIGNMENT:
      {
        retVal = TcpIp_TlsCore_ChangeParameter(socketTcpIdx, OptName, OptValPtr);
        break;
      }
      default:
      {
        /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
        /* #20 Report an error if necessary. */
        (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID,
          TCPIP_TLS_API_ID_TLS_CHANGE_PARAMETER, TCPIP_TLS_E_INV_ARG);
# endif /* TCPIP_DEV_ERROR_REPORT */
        break;
      }
    } /* switch() */
  }
  return retVal;
} /* TcpIp_Tls_ChangeParameter() */

/**********************************************************************************************************************
 *  TcpIp_Tls_AllocateConnection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_AllocateConnection(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_TlsConnectionDynIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the TLS connection exists and is free, and allocate it. */
  if ((TlsConIdx < TcpIp_GetSizeOfTlsConnection()) &&
      (TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx) == TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN))
  {
    /* The TLS connection is not yet in use, so it can be assigned to the socket. Set the socket index of the
    Tls-Connection to connected socket. */
    TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx, SocketIdx);
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_ALLOCATED);

    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report an error if necessary. */
  if (retVal != E_OK)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_ALLOCATE_CONNECTION, TCPIP_TLS_E_RESOURCE_IN_USE);
  }
# endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_Tls_FreeAllocatedConnection
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */

FUNC(void, TCPIP_CODE) TcpIp_Tls_FreeAllocatedConnection(
  TcpIp_TlsConnectionDynIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the TLS connection exists and free it. */
  if (TlsConIdx < TcpIp_GetSizeOfTlsConnection())
  {
    TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN);
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE);

    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report an error if necessary. */
  if (retVal != E_OK)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_DISALLOCATE_CONNECTION, TCPIP_TLS_E_NO_TLS_CONNECTION);
  }
# else
  TCPIP_DUMMY_STATEMENT(retVal);                                                                                        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif /* TCPIP_DEV_ERROR_REPORT */
}

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tls_BindAndListen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.00.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_BindAndListen(
  TcpIp_SocketDynIterType SocketIdx,
  uint16                  LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsListenerIterType nextFreeTlsListenerIdx;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the next free TLS-listener. */
  retVal = TcpIp_TlsListener_GetNextFreeListenerIndex(&nextFreeTlsListenerIdx);
  if (retVal == E_OK)
  {
    /* #20 Save the port and socket information in the TLS-listener. */
    TcpIp_SetSocketDynIdxOfTlsListener(nextFreeTlsListenerIdx, (TcpIp_SocketDynIdxOfTlsListenerType)SocketIdx);
    TcpIp_SetPortOfTlsListener(nextFreeTlsListenerIdx, LocalPort);
  }

  /* ----- Development Error Report ------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report an error if necessary. */
  if (retVal != E_OK)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_BIND_AND_LISTEN, TCPIP_TLS_E_NO_LISTENER);
  }
#  endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;

} /* TcpIp_Tls_BindAndListen() */

# endif /* TCPIP_SUPPORT_ASRTLSSERVER */

/**********************************************************************************************************************
 *  TcpIp_Tls_TcpIpEventCallout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_TcpIpEventCallout(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketDynIterType         SocketIdx,
  IpBase_TcpIpEventType           TcpIpEventType)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward the call to the TcpIp Event callout function */
  if ((SocketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig()) && (SocketIdx < TcpIp_GetSizeOfSocketDyn()))
  {
    TcpIp_TcpIpEventFunctions(SocketOwnerCfgIdx, SocketIdx, TcpIpEventType);
  }
  else
  {
    /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
    /* Report an error if necessary. */
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_TCPEVENT_CALLOUT, TCPIP_TLS_E_INV_ARG);
# endif /* TCPIP_DEV_ERROR_REPORT */
  }

} /* TcpIp_Tls_TcpIpEventCallout() */

/**********************************************************************************************************************
 *  TcpIp_Tls_CloseInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Tls_CloseInternal(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType socketIdx;

  /* ----- Implementation ----------------------------------------------- */
  socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);

  /* #10 Forward call to internal TCP */
  TcpIp_CloseTcpSocketFromTls(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), FALSE);

} /* TcpIp_Tls_CloseInternal() */

/**********************************************************************************************************************
 *  TcpIp_Tls_GetUserError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_Tls_STMIF */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetUserError(
  TcpIp_SocketIdType                     SocketId,
  TCPIP_P2V(TcpIp_TlsUserErrorType)      UserErrorMemoryPtr,
  TCPIP_P2V(uint32)                      NumOfUserErrorPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx = TcpIp_GetSizeOfTlsConnection();
  uint8                       errorId   = TCPIP_TLS_E_NO_ERROR;
  Std_ReturnType              retVal    = E_NOT_OK;

  /* Obtain the TLS connection for the given socket. */
  (void)TcpIp_SocketIdxToTlsConIdx(TCPIP_SOCKET_ID_TO_IDX(SocketId), &tlsConIdx);

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters. */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* Check parameter 'UserErrorMemoryPtr' */
  if (UserErrorMemoryPtr == NULL_PTR)
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  /* Check parameter 'NumOfUserErrorPtr' */
  else if ((NumOfUserErrorPtr == NULL_PTR) || (*NumOfUserErrorPtr == 0u))
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  /* Check parameter 'SocketId' */
  else if (!(TCPIP_SOCKET_ID_IS_VALID(SocketId) && TCPIP_SOCKET_IDX_IS_TCP(TCPIP_SOCKET_ID_TO_IDX(SocketId))))          /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    errorId = TCPIP_TLS_E_INV_ARG;
  }
  /* Check if there is a valid TLS connection for this socket. */
  else if (tlsConIdx >= TcpIp_GetSizeOfTlsConnection())
  {
    errorId = TCPIP_TLS_E_NO_TLS_CONNECTION;
  }
  else
# endif /* TCPIP_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to internal TLS function to read out the stored TLS user errors and report them to the user */
    retVal = TcpIp_TlsCoreError_GetUserError(tlsConIdx, UserErrorMemoryPtr, NumOfUserErrorPtr);
  }

  /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_GET_USER_ERROR, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);                                                                                       /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
} /* TcpIp_Tls_GetUserError() */


# if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tls_GetMasterSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetMasterSecret(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   MasterSecretPtr,
  TCPIP_P2V(uint8)   ClientRandomPtr,
  TCPIP_P2V(uint8)   SessionIdPtr,
  TCPIP_P2V(uint8)   SessionIdLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8          errorId = TCPIP_TLS_E_NO_ERROR;
  Std_ReturnType retVal  = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters. */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* Check parameter 'SocketId' */
  if (!(TCPIP_SOCKET_ID_IS_VALID(SocketId) && TCPIP_SOCKET_IDX_IS_TCP(TCPIP_SOCKET_ID_TO_IDX(SocketId))))               /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    errorId = TCPIP_TLS_E_INV_ARG;
  }
  /* Check parameter 'MasterSecretPtr' */
  else if (MasterSecretPtr == NULL_PTR)
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  /* Call the function */
  else
#  endif /* TCPIP_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to internal TLS function */
    retVal = TcpIp_TlsCoreMsa_ReadHandshakeParameter(TCPIP_SOCKET_ID_TO_IDX(SocketId), MasterSecretPtr, ClientRandomPtr, SessionIdPtr, SessionIdLenPtr);
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_GET_MASTER_SECRET, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT(errorId);                                                                                       /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
} /* TcpIp_Tls_GetMasterSecret() */
# endif /* TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS */

# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_Tls_ServiceChainCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ServiceChainCertificate(
  TcpIp_TlsConnectionIterType               TlsConIdx,
  TCPIP_P2C(uint8)                          CertNamePtr,
  uint32                                    CertNameLength,
  TCPIP_P2C(TcpIp_CertDataType)             CertDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8          errorId = TCPIP_TLS_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  if (   (TlsConIdx >= TcpIp_GetSizeOfTlsConnection())                                                                  /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetModeOfTlsConnection(TlsConIdx) != TCPIP_TLS_SERVER)
      || (CertNameLength == 0u))
  {
    errorId = TCPIP_TLS_E_INV_ARG;
  }
  /* Check input certificate parameters */
  else if (   (CertNamePtr == NULL_PTR)
           || (CertDataPtr == NULL_PTR))
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  else
#  endif /* TCPIP_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
/*
[REVIEW_G] c_accepted 16.00.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
    TcpIp_CertificateIdType certId;

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Rework comment, something like: Check if given CertName is configured, and write cert data into the found cert key. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
    /* #20 Check if given certificate name is configured, and write certificate data into the found KeyM key */
    if (KeyM_Cert_SearchCert(CertNamePtr, CertNameLength, &certId) == TRUE)
    {
      retVal = KeyM_SetCertificate(certId, (const KeyM_CertDataType *)CertDataPtr);                                     /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_TcpIp_CertDataType */
    }
    else
    {
      retVal = E_NOT_OK;
    }
#  else
    TCPIP_DUMMY_STATEMENT_CONST(CertNamePtr);                                                                           /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
    TCPIP_DUMMY_STATEMENT_CONST(CertNameLength);                                                                        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
    TCPIP_DUMMY_STATEMENT_CONST(CertDataPtr);                                                                           /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_SERVICE_CERTIFIATE, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT_CONST(errorId);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  TCPIP_DUMMY_STATEMENT_CONST(TlsConIdx);                                                                               /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
} /* TcpIp_Tls_ServiceChainCertificate */

/**********************************************************************************************************************
 *  TcpIp_Tls_ServiceRootCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ServiceRootCertificate(
  TcpIp_TlsConnectionIterType               TlsConIdx,
  TCPIP_P2C(uint8)                          CertNamePtr,
  uint32                                    CertNameLength,
  TCPIP_P2C(TcpIp_CertDataType)             CertDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8          errorId = TCPIP_TLS_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters */
#  if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  if (   (TlsConIdx >= TcpIp_GetSizeOfTlsConnection())                                                                  /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetModeOfTlsConnection(TlsConIdx) != TCPIP_TLS_CLIENT)
      || (CertNameLength == 0u))
  {
    errorId = TCPIP_TLS_E_INV_ARG;
  }
  /* Check input certificate parameters */
  else if (   (CertNamePtr == NULL_PTR)
           || (CertDataPtr == NULL_PTR))
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  else
#  endif /* TCPIP_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    /* Mode == TCPIP_TLS_CLIENT */
    TcpIp_CertificateIdType certId;

    /* #20 Check if this certificate can be loaded and load it into the KeyM */
    if (KeyM_Cert_SearchCert(CertNamePtr, CertNameLength, &certId) == TRUE)
    {
      retVal = KeyM_SetCertificate(certId, (const KeyM_CertDataType *)CertDataPtr);                                     /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_TcpIp_CertDataType */
    }
    else
    {
      retVal = E_NOT_OK;
    }
#  else
    TCPIP_DUMMY_STATEMENT_CONST(CertNamePtr);                                                                           /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
    TCPIP_DUMMY_STATEMENT_CONST(CertNameLength);                                                                        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
    TCPIP_DUMMY_STATEMENT_CONST(CertDataPtr);                                                                           /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_ROOT_CERTIFIATE, errorId);
  }
#  else
  TCPIP_DUMMY_STATEMENT_CONST(errorId);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  TCPIP_DUMMY_STATEMENT_CONST(TlsConIdx);                                                                               /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
} /* TcpIp_Tls_ServiceRootCertificate */


# endif /* TCPIP_SUPPORT_ASRTLS_ECC */

/**********************************************************************************************************************
 *  TcpIp_Tls_GetRootCertificateId
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetRootCertificateId(
  TcpIp_SocketIdType            SocketId,
  TCPIP_P2V(uint16)             CertIdPtr
)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId                         = TCPIP_TLS_E_NO_ERROR;
  Std_ReturnType retVal                 = E_NOT_OK;
  TcpIp_TlsConnectionIterType tlsConIdx = TcpIp_GetSizeOfTlsConnection();

  /* Obtain the TLS connection for the given socket. */
  (void)TcpIp_SocketIdxToTlsConIdx(TCPIP_SOCKET_ID_TO_IDX(SocketId), &tlsConIdx);

  /* ----- Development Error Checks ------------------------------------- */
/* #10 Check input parameters */
# if (TCPIP_DEV_ERROR_DETECT == STD_ON)
  /* Check parameter 'SocketId' */
  if (!(TCPIP_SOCKET_ID_IS_VALID(SocketId) && TCPIP_SOCKET_IDX_IS_TCP(TCPIP_SOCKET_ID_TO_IDX(SocketId))))               /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    errorId = TCPIP_TLS_E_INV_ARG;
  }
  /* Check parameter 'CertIdPtr' */
  else if (CertIdPtr == NULL_PTR)
  {
    errorId = TCPIP_TLS_E_PARAM_POINTER;
  }
  /* Check if there is a valid TLS connection for this socket. */
  else if (tlsConIdx >= TcpIp_GetSizeOfTlsConnection())
  {
    errorId = TCPIP_TLS_E_NO_TLS_CONNECTION;
  }
  else
# endif /* TCPIP_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to internal TLS function */
    retVal = TcpIp_TlsCoreUtil_CheckAndGetRootCertificateId(tlsConIdx, CertIdPtr);
  }
  /* ----- Development Error Report --------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_GET_ROOT_CERTIFIATE_ID, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT_CONST(errorId);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  TCPIP_DUMMY_STATEMENT_CONST(SocketId);                                                                                /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif /* TCPIP_DEV_ERROR_REPORT */

  return retVal;
}

# define TCPIP_STOP_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 *********************************************************************************************************************/

/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRAC2004_PES.pdf'

   Justification for module-specific MISRA deviations:

   module global deviations -> see file TcpIp.c

   TLS-specific deviations:

   MD_TcpIp_TlsStatemachine_STCAL_6050: Number of distinct function calls too high (HIS: STCAL = 0..7)
     Reason:     Number of distinct function calls is too high due to the number of different states which are needed to process the TLS message/state.
                 Splitting the state machine into multiple state machines to reduce the number of function calls does affect the readability and understanding of the code.
                 The individual sub-states of the state machine delegate the processing to separate functions, which ensures that the state machines are implemented in a clear and readable manner.
     Risk:       Using to many distinct functions does affect readability and complexity of the code.
     Prevention: Covered by code review and state machine documented in design.

   MD_TcpIp_TlsStatemachine_STMIF_6080: Number of maximum nesting of control structures defined by HIS shall be in range 0..4
     Reason:     Number of maximum nesting control structures is too high due to the parsing of many different elements within one context of the processing of an TLS message/state.
                 Within a message processing chain, many different events have to be considered, which leads to an increased number of logically related nesting control structures.
                 Splitting the nesting control structures would make the logical processing and parsing of the TLS messages/states unnecessarily complicated.
     Risk:       Using to many nesting control structures does affect readability and complexity of the code.
     Prevention: Covered by code review and well documented implementation.

   MD_TcpIp_TlsRxLengthChecks_STMIF: Number of maximum nesting of control structures defined by HIS shall be in range 0..4
     Reason:     Number of maximum nesting control structures is too high due to many different length checks that have
                 to be done for received messages.
                 Often length checks even need two steps, first check that the length field is available in the message,
                 and second read the length an check that this length is available in the message.
                 Splitting the nesting control structures would make the logical processing and parsing of the TLS
                 messages unnecessarily complicated and less readable.
     Risk:       Using to many nesting control structures does affect readability and complexity of the code.
     Prevention: Covered by code review and well documented implementation.

   MD_TcpIp_Tls_STCAL: Number of distinct function calls too high (HIS: STCAL = 0..7)
     Reason:     Number of distinct function calls is only too high due to development and will be change with further refactoring of the function.
     Risk:       Using to many distinct functions does affect readability and complexity of the code.
     Prevention: Covered by code review.

   MD_TcpIp_Tls_STPTH: Estimated static path count defined by HIS shall be in range 1..80
     Reason:     Number of static path is only too high due to development and will be change with further refactoring of the function.
     Risk:       Using to many static path does affect readability and complexity of the code.
     Prevention: Covered by code review.

   MD_TcpIp_Tls_STCYC: Cyclomatic complexity defined by HIS shall be in range 1..10
     Reason:     Cyclomatic complexity is only too high due to development and will be change with further refactoring of the function.
     Risk:       To high cyclomatic complexity does affect readability and complexity of the code.
     Prevention: Covered by code review.

   MD_TcpIp_Tls_STMIF: Number maximum nesting of control structures defined by HIS shall be in range 0..4
     Reason:     Number of maximum nesting control structures is only too high due to development and will be change with further refactoring of the function.
     Risk:       Using to many nesting control structures does affect readability and complexity of the code.
     Prevention: Covered by code review.

   MD_TcpIp_Tls_STPAR: Number of function parameters defined by HIS shall be in range 0..5
     Reason:     Number of function parameters is only too high due to development and will be change with further refactoring of the function.
     Risk:       Using to many function parameters does affect readability and complexity of the code.
     Prevention: Covered by code review.

   MD_TCPIP_Rule2.2_RedundantAssignment: This initialization is redundant. The value of this object is never used before being modified.
     Reason:     Uninitialized assignment may cause compiler warnings.
     Risk:       None.
     Prevention: Covered by code review.

   MD_TCPIP_Rule11.3_0310_3305_TcpIp_CertDataType: Casting to different object pointer type.
     Reason:     Casting from TcpIp_CertDataType to KeyM_CertDataType type to support PSK without KeyM integration.
     Risk:       None.
     Prevention: Covered by code review.

   MD_TcpIp_Tls_2995: The result of this logical operation is always 'true'.
     Reason:     Using macro for range check of received length information, where the third argument is always checked
                 against the TcpIp_GetSizeOfTlsBufferRx(), and therefore the evaluation of the term is redundant. This
                 causes MISRA warnings when checking multiple length information in a row.
     Risk:       None
     Prevention: Covered by code review.

   MD_TcpIp_Tls_2991_2995: The value/result of this expression/logical operation is always 'true'.
     Reason:     Some API patterns have already been applied, although the functionality will only be
     implemented in a future version. This increases the readability of the code in the appropriate places
     Risk:       None
     Prevention: Covered by code review.

*/

/**********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 *********************************************************************************************************************/

#endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Tls.c
 *********************************************************************************************************************/
