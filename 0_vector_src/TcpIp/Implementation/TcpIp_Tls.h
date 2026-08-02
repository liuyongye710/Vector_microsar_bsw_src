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
/*!        \file  TcpIp_Tls.h
 *        \brief  Transport Layer Security (TLS) API functions implementation.
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TLS FUNCTION NAMING AND ABBREVIATION
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TLS public API function naming:
 *    TcpIp_Tls_<FunctionName>
 *    e.g.: TcpIp_Tls_RxIndication
 *
 * TLS internal function naming:
 *    TcpIp_Tls<Module><Submodule>_<FunctionName>
 *    e.g.: TcpIp_TlsCoreRl_TransmitFrame
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  Modules:    Submodules:    Description:
 *  -------------------------------------------------------------------------------------------------------------------
 *  Core        Crypto         All generic crypto relevant functions, like de/encryption.
 *  Core        Alert          Generic TLS alert handling
 *  Core        RxBufStruct    Receive Buffer struct, takes care of TcpIp Buffer wraparound
 *  Core        Buffer         TLS Buffer handling (RX and TX)
 *  Core        ConState       TLS Connection state handling
 *  Core        CtAd           TLS Content Type Application data
 *  Core        CtAl           TLS Content Type Alert
 *  Core        CtCcs          TLS Content Type Change Cipher Spec
 *  Core        CtHs           TLS Content Type Handshake
 *  Core        Ctx            TLS Low prio context handling
 *  Core        Error          TLS User error handling
 *  Core        Event          TLS Event handling
 *  Core        Ll             TLS LowerLayer, API between TCP and TLS
 *  Core        MainFunction   TLS Main function handling
 *  Core        Msa            TLS Master Secret Access
 *  Core        Rl             TLS Record Layer handling
 *  Core        State          TLS Generic state handling
 *  Core        Ul             TLS UpperLayer, API between TcpIp and TLS
 *
 * Client       Crypto         TLS Client generic crypto functions
 * Client       Ctx            TLS Client Low prio context handling
 * Client       HsStm          TLS Client Handshake state machine
 * Client       Msa            TLS Client Master Secret Access
 * Client       Msg            TLS Client Handshake Message handling and parsing
 * Client       Tx             TLS Client Transmission forwarding and handling
 *
 * Server       Crypto         TLS Server generic crypto functions
 * Server       Ctx            TLS Server Low prio context handling
 * Server       HsStm          TLS Server Handshake state machine
 * Server       Msa            TLS Server Master Secret Access
 * Server       Msg            TLS Server Handshake Message handling and parsing
 * Server       Tx             TLS Server Transmission forwarding and handling
 *
 *
 *              AAD            Additional Authenticated Data
 *
 *********************************************************************************************************************/



#if !defined (TCPIP_TLS_H)
# define TCPIP_TLS_H


# include "TcpIp_Cfg.h"
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "TcpIp_Lcfg.h"
#  include "Std_Types.h"
#  include "TcpIp.h"

#  include "TcpIp_Priv.h"
#  include "TcpIp_Priv_Types.h"
#  include "TcpIp_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* vendor and module identification */
#  define TCPIP_TLS_VINSTANCE_ID                             5u  /* 1=TcpIp, 2=IpV4, 3=IpV6, 4=DhcpV4Server, 5=Tls */

/* ----- API service IDs ----- */
#  define TCPIP_TLS_API_ID_RX_INDICATION                   (0x10u) /*!< Service ID: TcpIp_Tls_RxIndication() */
#  define TCPIP_TLS_API_ID_TLS_BIND_AND_LISTEN             (0x11u) /*!< Service ID: TcpIp_Tls_BindAndListen() */
#  define TCPIP_TLS_API_ID_TLS_ACCEPTED                    (0x12u) /*!< Service ID: TcpIp_Tls_Accepted() */
#  define TCPIP_TLS_API_ID_TLS_CONNECTED                   (0x13u) /*!< Service ID: TcpIp_Tls_Connected() */
#  define TCPIP_TLS_API_ID_TLS_GET_USER_ERROR              (0x14u) /*!< Service ID: TcpIp_Tls_GetUserError() */
#  define TCPIP_TLS_API_ID_TLS_GET_MASTER_SECRET           (0x15u) /*!< Service ID: TcpIp_Tls_GetMasterSecret() */
#  define TCPIP_TLS_API_ID_TLS_INV_CONFIG                  (0x16u) /*!< Service ID: TcpIp_TlsCoreCrypto_HandleInvalidConfiguration() */
#  define TCPIP_TLS_API_ID_TLS_ALLOCATE_CONNECTION         (0x17u) /*!< Service ID: TcpIp_Tls_AllocateConnection() */
#  define TCPIP_TLS_API_ID_TLS_TCPEVENT_CALLOUT            (0x18u) /*!< Service ID: TcpIp_Tls_TcpIpEventCallout() */
#  define TCPIP_TLS_API_ID_TLS_DISALLOCATE_CONNECTION      (0x19u) /*!< Service ID: TcpIp_Tls_FreeAllocatedConnection() */
#  define TCPIP_TLS_API_ID_TLS_SERVICE_CERTIFIATE          (0x20u) /*!< Service ID: TcpIp_Tls_ServiceChainCertificate() */
#  define TCPIP_TLS_API_ID_TLS_ROOT_CERTIFIATE             (0x21u) /*!< Service ID: TcpIp_Tls_ServiceRootCertificate() */
#  define TCPIP_TLS_API_ID_TLS_CHANGE_PARAMETER            (0x22u) /*!< Service ID: TcpIp_Tls_ChangeParameter() */
#  define TCPIP_TLS_API_ID_TLS_GET_ROOT_CERTIFIATE_ID      (0x23u) /*!< Service ID: TcpIp_Tls_GetRootCertificateId() */

/* ----- General Error codes ----- */
#  define TCPIP_TLS_E_NO_ERROR                          (0x00u) /*!< used to check if no error occurred - use a value unequal to any error code */
#  define TCPIP_TLS_E_ERROR                             (0x01u) /*!< Error code: Generic error */
#  define TCPIP_TLS_E_PARAM_POINTER                     (0x02u) /*!< Error code: API service called with NULL pointer */
#  define TCPIP_TLS_E_INV_ARG                           (0x03u) /*!< Error code: API service called with invalid argument */
#  define TCPIP_TLS_E_NO_BUF                            (0x04u) /*!< Error code: No free buffer */
#  define TCPIP_TLS_E_NO_LISTENER                       (0x05u) /*!< Error code: No free TLS listener */
#  define TCPIP_TLS_E_NO_TLS_CONNECTION                 (0x06u) /*!< Error code: No TLS connection found */
#  define TCPIP_TLS_E_INV_CONFIG                        (0x07u) /*!< Error code: Invalid configuration during runtime detected */
#  define TCPIP_TLS_E_RESOURCE_IN_USE                   (0x08u) /*!< Error code: Requested resource is already in use */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define TCPIP_START_SEC_CODE
#  include "TcpIp_MemMap.h"

/**********************************************************************************************************************
 *  TcpIp_Tls_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Initialization for *_INIT_*-variables
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_InitMemory(void);

/**********************************************************************************************************************
 * TcpIp_Tls_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     Service to initialize the module TcpIp_Tls. It initializes all variables and sets the module state to
 *               initialized.
 *  \pre         Module is uninitialized.
 *  \pre         TcpIp_Tls_InitMemory has been called unless TcpIp_Tls_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_Init( void );

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionRx
 *********************************************************************************************************************/
/*! \brief          Handles reception of data and forwards it to the TLS.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MultiPartitionMainFunctionRx which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionRx(void);

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionState
 *********************************************************************************************************************/
/*! \brief          Performs pending state changes of the TLS.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MultiPartitionMainFunctionState() which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionState(void);

/**********************************************************************************************************************
 *  TcpIp_Tls_MainFunctionTx
 *********************************************************************************************************************/
/*! \brief          Handles transmission of data and forwards it to the TLS.
 *  \details        -
 *  \pre            -
 *  \context        TASK (Called by TcpIp_MultiPartitionMainFunctionTx which is called cyclically by schedule manager)
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_MainFunctionTx(void);

/**********************************************************************************************************************
 * TcpIp_Tls_RxIndicaion
 *********************************************************************************************************************/
/*! \brief         Informs TLS about the of a reception of data.
 *  \details       -
 *  \param[in]     SocketTcpIdx      Index of a TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     DataPtr           Payload of the data received.
 *  \param[in]     DataLenByte       Payload length of the data received.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_RxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DataPtr,
  uint16                       DataLen);

/**********************************************************************************************************************
 *  TcpIp_Tls_ChangeParameter
 *********************************************************************************************************************/
/*! \brief         Public API for the TLS change parameter options
 *  \details       -
 *  \param[in]     SocketIdx            Index of a TCP socket
 *                                      CONSTRAINT:  [0..TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     OptName              Option name.  Valid option identifiers are:
 *                                        TCPIP_PARAMID_TLS_CONNECTION_ASSIGNMENT
 *  \param[in]     OptValPtr            Option parameter
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE for different SocketIdx.
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ChangeParameter(
  TcpIp_SizeOfSocketDynType    SocketIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr);

/**********************************************************************************************************************
 *  TcpIp_Tls_AllocateConnection
 *********************************************************************************************************************/
/*! \brief          Allocates a TLS connection to the TCP socket.
 *  \details        This is kind of a reservation of the connection. At this point of time it is not known if the socket
 *                  shall be used as a client or as a server. Later the connection will be fully configured for its
 *                  usage.
 *  \param[in]      SocketIdx           Index of a TCP socket.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      TlsConIdx           Index of the requested TLS connection
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_AllocateConnection(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TcpIp_TlsConnectionDynIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_Tls_FreeAllocatedConnection
 *********************************************************************************************************************/
/*! \brief          Remove the allocated status of a TLS connection
 *  \details        This API is used when the TLS connection is bound to an socket, but not used and the connection
 *                  will be closed. This happens between the TCP handshake and the TLS handshake.
 *  \param[in]      TlsConIdx          Index of the requested TLS connection
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_FreeAllocatedConnection(
  TcpIp_TlsConnectionDynIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 * TcpIp_Tls_BindAndListen
 *********************************************************************************************************************/
/*! \brief          Binds a TCP socket to a local TLS resource and set TLS-Connection into listen mode.
 *  \details        Get the next free TLS listener and set its runtime parameters. Checking the maximum number of
 *                  connections for a server is not necessary, this is already done in TCP.
 *  \param[in]      SocketIdx          Index of a TCP socket.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]      LocalPort          Local port to which the socket shall be bound.
 *  \return         E_OK               The request has been accepted.
 *  \return         E_NOT_OK           The request has not been accepted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different SocketIdx.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.03.00.0
*/
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Port parameter differs in naming between function and description. Also check the parameter description text. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_BindAndListen(
  TcpIp_SocketDynIterType SocketIdx,
  uint16                  LocalPort);
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER == STD_ON */

/**********************************************************************************************************************
 * TcpIp_Tls_TcpIpEventCallout
 *********************************************************************************************************************/
/*! \brief         Forward all occurred Events to the TCP layer.
 *  \details       -
 *  \param[in]     SocketOwnerCfgIdx Index of a socket owner.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketOwnerConfig()-1]
 *  \param[in]     SocketIdx         Index of the TCP/UDP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     TcpIpEventType    Status event that occurred in the connection related to the given socket.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_TcpIpEventCallout(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketDynIterType         SocketIdx,
  IpBase_TcpIpEventType           TcpIpEventType);

/**********************************************************************************************************************
 * TcpIp_Tls_CloseInternal
 *********************************************************************************************************************/
/*! \brief         Forward the Close request to the TCP layer.
 *  \details       -
 *  \param[in]     TlsConIdx         Tls connection Index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_Tls_CloseInternal(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_Tls_GetUserError
 *********************************************************************************************************************/
/*! \brief         User can read errors, occurred due to invalid packet reception.
 *  \details       -
 *  \param[in]     SocketId            Socket identifier of the related local socket resource.
 *  \param[in,out] UserErrorMemoryPtr  Pointer to the user buffer, where user error entries shall be stored.
 *  \param[in,out] NumOfUserError      Number of user errors upper layer wants to read.
 *  \return        E_OK                if reading is successful.
 *                 E_NOT_OK            error
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetUserError(
  TcpIp_SocketIdType                     SocketId,
  TCPIP_P2V(TcpIp_TlsUserErrorType)      UserErrorMemoryPtr,
  TCPIP_P2V(uint32)                      NumOfUserErrorPtr);

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 * TcpIp_Tls_GetMasterSecret
 *********************************************************************************************************************/
/*! \brief         User can read Master Secret Key, Client Random Number and Session Id.
 *  \details       -
 *  \param[in]     SocketId           Socket identifier of the related local socket resource.
 *  \param[out]    MasterSecretPtr    Pointer to the user buffer, where Master Secret Key shall be stored.
 *                                    CONSTRAINT: The pointed user buffer must have the size TCPIP_TLS_MASTER_SECRET_LEN.
 *  \param[out]    ClientRandomPtr    Pointer to the user buffer, where Client Random Number shall be stored.
 *                                    If Pointer is set to NULL_PTR information shall not be read.
 *                                    CONSTRAINT: The pointed user buffer must have the size TCPIP_TLS_RANDOM_LEN.
 *  \param[out]    SessionIdPtr       Pointer to the user buffer, where Session Id shall be stored.
 *                                    If Pointer is set to NULL_PTR information shall not be read.
 *                                    CONSTRAINT: The pointed user buffer must have the size TCPIP_TLS_SESSIONIDMAX_LEN.
 *  \param[out]    SessionIdLenPtr    Pointer to the Session Id length.
 *  \return        E_OK               If reading was successful.
 *                 E_NOT_OK           If SocketId was invalid or CSM call failed.
 *  \pre           TLS-Connection on this socket must be in the state >= TCPIP_TLS_STATE_CONNECTION_ESTABLISHED
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetMasterSecret(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint8)   MasterSecretPtr,
  TCPIP_P2V(uint8)   ClientRandomPtr,
  TCPIP_P2V(uint8)   SessionIdPtr,
  TCPIP_P2V(uint8)   SessionIdLenPtr);
#  endif /* (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON) */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_Tls_ServiceRootCertificate
 *********************************************************************************************************************/
/*! \brief         Set the Root Certificate which will be used for TLS handshake
 *  \details       This API is only invoked for TLS Client connections
 *  \param[in]     TlsConIdx         Tls connection Index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *                                   CONSTRAINT: Mode = TCPIP_TLS_CLIENT
 *  \param[in]     CertNamePtr       Name of the root certificate to load
 *  \param[in]     CertNameLength    Length of the name field
 *  \param[in]     CertDataPtr       Certificate data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ServiceRootCertificate(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2C(uint8)              CertNamePtr,
  uint32                        CertNameLength,
  TCPIP_P2C(TcpIp_CertDataType) CertDataPtr);

/**********************************************************************************************************************
 * TcpIp_Tls_ServiceChainCertificate
 *********************************************************************************************************************/
/*! \brief         This API is used to set the Server certificates to send during TLS handshake
 *  \details       This API is only invoked for TLS Server connections
 *  \param[in]     TlsConIdx         Tls connection Index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *                                   CONSTRAINT: Mode = TCPIP_TLS_SERVER
 *  \param[in]     CertNamePtr       Name of the root certificate to load
 *  \param[in]     CertNameLength    Length of the name field
 *  \param[in]     CertDataPtr       Certificate data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_ServiceChainCertificate(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2C(uint8)              CertNamePtr,
  uint32                        CertNameLength,
  TCPIP_P2C(TcpIp_CertDataType) CertDataPtr);


#  endif /* TCPIP_SUPPORT_ASRTLS_ECC */
/**********************************************************************************************************************
 * TcpIp_Tls_GetRootCertificateId
 *********************************************************************************************************************/
 /*! \brief         Provides the ID of the used root certificate.
  *  \details       This API is only invoked for TLS Client connections
  *  \param[in]     SocketId          Socket identifier of the related local socket resource.
  *                                   CONSTRAINT: Mode = TCPIP_TLS_CLIENT
  *  \param[out]    CertIdPtr         Pointer to return the root certificate ID.
  *  \return        E_OK              A root certificate was found. Returned value in CertIdPtr is valid.
  *                 E_NOT_OK          No root certificate was found. Returned value in CertIdPtr is invalid.
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_Tls_GetRootCertificateId(
  TcpIp_SocketIdType SocketId,
  TCPIP_P2V(uint16)  CertIdPtr
);

#  define TCPIP_STOP_SEC_CODE
#  include "TcpIp_MemMap.h"

/**********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 *********************************************************************************************************************/
# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
#endif /* TCPIP_TLS_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Tls.h
 *********************************************************************************************************************/
