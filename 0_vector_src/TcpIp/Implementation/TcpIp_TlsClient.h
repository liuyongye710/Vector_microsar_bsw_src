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
/*!        \file  TcpIp_TlsClient.h
 *        \brief  Transport Layer Security (TLS) client functions implementation.
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TLSCLIENT_H)
# define TCPIP_TLSCLIENT_H

# include "TcpIp_Cfg.h"

# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#   include "TcpIp_Lcfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 /* Minimum ServerHello length: 2 bytes version info, 32 bytes random value, 2 byte cipher suite info, 1 byte session id length, 1 bytes compression method info */
#   define TCPIP_TLS_MIN_SERVERHELLO_MSGLEN ( TCPIP_TLS_MAJORVERS_LEN + TCPIP_TLS_MINORVERS_LEN + TCPIP_TLS_RNDLEN \
                                          + TCPIP_TLS_SESSIONIDLEN_LEN\
                                          + TCPIP_TLS_CIPHERLENLEN + TCPIP_TLS_COMPMETHLEN_LEN)

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
/**********************************************************************************************************************
 * TcpIp_TlsClient_Init
 *********************************************************************************************************************/
/*! \brief         Initializes Tls Client
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_Init(void);

/**********************************************************************************************************************
 * TcpIp_TlsClient_InitHsMsgIndices
 *********************************************************************************************************************/
/*! \brief         Initialize the message indices for the TLS client
 *  \details       Sets all relevant TLS client indices to their NO values
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitHsMsgIndices(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_InitAsnycFlags
 *********************************************************************************************************************/
/*! \brief         Initialize the Async flags for TLS client
 *  \details       Sets all TLS client trigger flags for the async context calculation to FALSE
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitAsnycFlags(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_InitHsLenInformation
 *********************************************************************************************************************/
/*! \brief         Initialize handshake length parameters for TLS client
 *  \details       Sets all TLS client length information of the received handshake messages to zero
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitHsLenInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_InitReadyToSendFlags
 *********************************************************************************************************************/
/*! \brief         Initialize Ready to send flags for TLS client
 *  \details       Sets all TLS client trigger flags for the handshake transmit to FALSE
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitReadyToSendFlags(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_ResetCertChainStates
 *********************************************************************************************************************/
/*! \brief         Reset the TLS certificate chain struct and states
 *  \details       Sets all TLS client certificate information to their default values
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ResetCertChainStates(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_ResetConnection
 *********************************************************************************************************************/
/*! \brief         Reset the TLS connection
 *  \details       Calls the init function for all related TLS submodules (e.g reset of length information)
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ResetConnection(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_GetRootCertificateId
 *********************************************************************************************************************/
 /*! \brief         Provides the ID of the used root certificate.
  *  \details       -
  *  \param[in]     TlsConIdx         Tls connection Index
  *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *                                   CONSTRAINT: Mode = TCPIP_TLS_CLIENT
  *  \param[out]    CertIdPtr         Pointer to return the root certificate ID.
  *  \return        E_OK              A root certificate was found. Returned value in CertIdPtr is valid.
  *                 E_NOT_OK          No root certificate was found. Returned value in CertIdPtr is invalid.
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  ********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClient_GetRootCertificateId(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2V(uint16)             CertIdPtr);

/**********************************************************************************************************************
 *   TLS CLIENT TX RECORD LAYER FORWARDING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl
 *********************************************************************************************************************/
/*! \brief         Forward the processed Hs message to the record layer for transmission
 *  \details       Forwards the specific TLS client handshake messages to the record layer if the message is ready to
 *                 transmit
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *   TLS CLIENT HANDSHAKE STATE MACHINE
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_PerformNextHsStep
 *********************************************************************************************************************/
/*! \brief         Perform the next HS processing step
 *  \details       Main TLS client handshake state machine handling
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_PerformNextHsStep(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_ProcessHandshake
 *********************************************************************************************************************/
/*! \brief         Process the TLS handshake state machine
 *  \details       Executes the TLS client handshake state machine, if all conditions are fulfilled.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ProcessHandshake(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsCertChainTriggerValidationCallback
 *********************************************************************************************************************/
/*! \brief         Notify the socket owner about the certificate chain validation result and update state
 *  \details       After this function call, certificate chain validation is complete
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     AllowOverrule           Allow the socket owner to overrule the validation result
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsCertChainTriggerValidationCallback(
  TcpIp_TlsConnectionIterType TlsConIdx,
  boolean AllowOverrule);

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_AsyncHandler
 *********************************************************************************************************************/
/*! \brief         Handle async context operations for Tls client
 *  \details       Calculates all time consuming operation if the corresponding flags are set
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_AsyncHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

#   if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup
 *********************************************************************************************************************/
/*! \brief         Verify the  certificate group that was loaded into KeyM
 *  \details       The server certificate chain is loaded into the KeyM certificate group
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \return        E_OK              Verifying the cert group succeeded.
  *                 E_NOT_OK          Verifying the cert group failed.
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_ValidateCertificateStatus
 *********************************************************************************************************************/
/*! \brief          Validate the received OCSP certificate status request
 *  \details        Triggered from TLS handshake state machine during parsing of ServerCertificateStatus request
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_ValidateCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_VerifySignatureOfPublicKey
 *********************************************************************************************************************/
/*! \brief         Verify signature of the server key exchange public key received
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_VerifySignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx);
#   endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_CalcClientFinishedHash
 *********************************************************************************************************************/
/*! \brief         Calculate the client finished hash
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_SetCsmKeys
 *********************************************************************************************************************/
/*! \brief         Set the encryption and hash generation Csm keys for the selected ciphersuite
 *  \details       The keys are derived from the calculated key block
 *  \param[in]     TlsConIdx            TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientTx_SendChangeCipherSpec
 *********************************************************************************************************************/
/*! \brief         Trigger transmission of client CCs message
 *  \details       Forwards the TLS ChangeCipherSpec message to the record layer
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientTx_SendChangeCipherSpec(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen
 *********************************************************************************************************************/
/*! \brief        Depending on the selected cipher, calculate the length of the received server Hs messages
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        serverRxLen             Calculated server hs message length
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint32, TCPIP_CODE) TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen(
  TcpIp_TlsConnectionIterType     TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_GenerateHsHash
 *********************************************************************************************************************/
/*! \brief         Generate the hash of all handshake messages
 *  \details       The hash generated is used in the HS finished message
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     FinishedMessageType       Type of finished message (Server / client)
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_GenerateHsHash(
 TcpIp_TlsConnectionIterType      TlsConIdx,
  TcpIp_TlsMessageFinishedType    FinishedMessageType);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_CalcHsFinishedData
 *********************************************************************************************************************/
/*! \brief         Calculated the Hs finished data for client/server
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     FinishedMessageType       Type of finished message (Server / client)
 *  \param[out]    ResultPtr               Buffer to store the calculated hash
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_CalcHsFinishedData(
  TcpIp_TlsConnectionIterType    TlsConIdx,
  TcpIp_TlsMessageFinishedType   FinishedMessageType,
  TCPIP_P2V(uint8)               ResultPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_CalcServerFinishedHash
 *********************************************************************************************************************/
/*! \brief         Calculate the server finished hash
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCtx_CalcServerFinishedVerifyData
 *********************************************************************************************************************/
/*! \brief         Calculate the server finished verify data at Tls client side
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcServerFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif

# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
#endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsClient.h
 *********************************************************************************************************************/

