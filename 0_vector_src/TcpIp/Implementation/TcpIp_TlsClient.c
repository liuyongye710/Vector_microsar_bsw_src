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
/*!        \file  TcpIp_TlsClient.c
 *        \brief  Transport Layer Security (TLS) client functions implementation
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#define TCPIP_TLSCLIENT_SOURCE
#include "TcpIp_Cfg.h"

#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "TcpIp_Lcfg.h"
#  include "TcpIp_Tls.h"
#  include "TcpIp_TlsClient.h"
#  include "TcpIp_TlsCore.h"
#  include "TcpIp_TlsPriv.h"

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
#   include "KeyM.h"
#  endif

#  include "TcpIp_Tls_Cbk.h"

#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
#   include "Det.h"
#  endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#  define TCPIP_TLSCLIENT_COMPMETHLEN_LEN 1u
#  define TCPIP_TLSCLIENT_COMPMETH_LEN 1u

/* To check if TCP Ack has been sent */
#  define TCPIP_TLSCLIENT_TCPACKBIT 0x10u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#  if !defined (TCPIP_TLS_LOCAL)
#   define TCPIP_TLS_LOCAL static
#  endif

#  if !defined (TCPIP_TLS_LOCAL_INLINE)
#   define TCPIP_TLS_LOCAL_INLINE LOCAL_INLINE
#  endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  MSA - Master Secret Access
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer
 *********************************************************************************************************************/
/*! \brief         Copy the Server sessionId into the Client MSA_AccessBuffer
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer
 *********************************************************************************************************************/
/*! \brief         Copy the Client Random into the Client MSA_AccessBuffer
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_HandleErrorDuringPreparation
 *********************************************************************************************************************/
/*! \brief         Handle error during client handshake
 *  \details       Report user error and trigger alert if error occurs during handshake
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms
 *********************************************************************************************************************/
/*! \brief         Add the signature algorithms extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups
 *********************************************************************************************************************/
/*! \brief         Add supported groups extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat
 *********************************************************************************************************************/
/*! \brief         Add supported EC point format extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication
 *********************************************************************************************************************/
/*! \brief         Add trusted ca indication extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList
 *********************************************************************************************************************/
/*! \brief         Add list of trusted authorities to the TLS TxBuffer
 *  \details       -
 *  \param[in]     TlsConIdx                    TLS connection index
 *                                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TrustedAuthorityListStartIdx Start index of the Trusted Authority list
 *  \param[in,out] ConsumedLenPtr               Number of bytes which are consumed by this extension
 *  \return        E_OK                         Extension added
 *  \return        E_NOT_OK                     Extension could not be added
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TrustedAuthorityListStartIdx,
  TCPIP_P2V(uint16) ConsumedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest
 *********************************************************************************************************************/
/*! \brief         Add certificate status request extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent
 *********************************************************************************************************************/
/*! \brief         Check whether given extension has already been added to the client hello message
 *  \details       -
 *  \param[in]     ExtensionStartIdx       Start index of the extensions part of client hello
 *  \param[in]     ExtensionEndIdx         End index of the extensions part of client hello
 *  \param[in]     ExtensionValue          Value of the extension
 *  \return        TRUE                    Extension is present
 *  \return        FALSE                   Extension is not present
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent(
  TcpIp_TlsBufferTxIterType ExtensionStartIdx,
  TcpIp_TlsBufferTxIterType ExtensionEndIdx,
  uint16                    ExtensionValue);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloAddExtensionValue
 *********************************************************************************************************************/
/*! \brief         Add extension to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ExtensionValue          Extension value to be added
 *  \param[in]     ExtensionStartIdx       Start of the extension part of client hello message
 *  \param[in,out] ConsumedLenPtr          consumed bytes of the extension part of client hello message
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddExtensionValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16                      ExtensionValue,
  TcpIp_TlsBufferTxIterType   ExtensionStartIdx,
  TCPIP_P2V(uint16)           ConsumedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloAddClientExtensions
 *********************************************************************************************************************/
/*! \brief         Add client extensions to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddClientExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_PrepareClientHello
 *********************************************************************************************************************/
/*! \brief         Prepare the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientHello(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_SendClientHello
 *********************************************************************************************************************/
/*! \brief         Trigger transmission of client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientHello(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerHello
 *********************************************************************************************************************/
/*! \brief         Parse the received RL message with the server hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerHello
 *********************************************************************************************************************/
/*! \brief         Extract the server hello message and set next state of the client HS state machine
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                      Next state of the client HS state machine
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHello(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerHelloInformation
 *********************************************************************************************************************/
/*! \brief         Extraction the server hello information from the received RL message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHelloInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite
 *********************************************************************************************************************/
/*! \brief         Get the ciphersuite value from the server hello message
 *  \details       -
 *  \param[in]     TlsConIdx    TLS connection index
 *                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK         Operation successful
 *  \return        E_NOT_OK     Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference
 *********************************************************************************************************************/
/*! \brief         Select the handshake reference depending on the selected key exchange method
 *  \details       -
 *  \param[in]     TlsConIdx    TLS connection index
 *                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod
 *********************************************************************************************************************/
/*! \brief         Get compression method from the server hello message
 *  \details       -
 *  \param[in]     TlsConIdx    TLS connection index
 *                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK         Operation successful
 *  \return        E_NOT_OK     Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloAddCipherSuites
 *********************************************************************************************************************/
/*! \brief         Add the supported ciphersuites to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddCipherSuites(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod
 *********************************************************************************************************************/
/*! \brief         Add compression method to the client hello message
 *  \details       -
 *  \param[in]     TlsConIdx    TLS connection index
 *                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloGetExtensions
 *********************************************************************************************************************/
/*! \brief         Extract the extensions from the received server hello message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HelloEndIdx     End idx of the server hello message
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloGetExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType   HelloEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloCheckExtensions
 *********************************************************************************************************************/
/*! \brief         Checks all received server extension for plausibility and validity
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ExtensionsLen   Length of the extensions data
 *  \param[in]     HelloEndIdx     End idx of the server hello message
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseAndValidateExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16                      ExtensionsLen,
  TcpIp_TlsBufferRxIterType   HelloEndIdx);


/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions
 *********************************************************************************************************************/
/*! \brief         Compares the received server extensions again all transmitted client extensions
 *  \details       If received server extension is not contained in client list, return error
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ReceivedExtensionListPtr  Pointer to the list of received Server extensions
 *  \param[in]     ReceivedExtensionCnt      Number of received server extensions
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions
 *********************************************************************************************************************/
/*! \brief         Parse all received server extension depending on the extension type.
 *  \details       Forwards the extension to the specific parser, if extension is supported, otherwise return error
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ReceivedExtensionListPtr  Pointer to the list of received Server extensions
 *  \param[in]     ReceivedExtensionCnt      Number of received server extensions
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloParseExtensionEcPointFormat
 *********************************************************************************************************************/
/*! \brief         Parses an received TLS extension of the type ec_point_formats.
 *  \details       Compares the received extension data against the supported TLS client ones.
 *  \param[in]     EcPointFormatExtension       Extension of type ec point format
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseExtensionEcPointFormat(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType EcPointFormatExtension);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type certificate status request.
 *  \details       Compares the received extension data against the supported TLS client ones.
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertificateStatusRequest       Extension of type certificate status request
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType CertificateStatusRequest);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloCheckExtensions
 *********************************************************************************************************************/
/*! \brief         Check the extensions in the received server hello message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HelloEndIdx     End idx of the server hello message
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloCheckExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType   HelloEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloDetermineNextState
 *********************************************************************************************************************/
/*! \brief         Determine the next state in the server hello message processing
 *  \details       -
 *  \param[in]     TlsConIdx                   TLS connection index
 *                                             CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                Next state of the client HS state machine
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloDetermineNextState(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk
 *********************************************************************************************************************/
/*! \brief         Determine the next state in the server hello message processing for PSK identity
 *  \details       -
 *  \param[in]     TlsConIdx                       TLS connection index
 *                                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                    Next state of the client HS state machine
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification
 *********************************************************************************************************************/
/*! \brief         Extract certificates from server certificate message and trigger verification if possible
 *  \details       -
 *  \param[in]     TlsConIdx                       TLS connection index
 *                                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertStartIdx                    Start Idx of the certificate data
 *  \param[in]     NumCerts                        Number of certificates in cert chain
 *  \return        E_OK                            Operation successful
 *  \return        E_NOT_OK                        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification(
  TcpIp_TlsConnectionIterType         TlsConIdx,
  TcpIp_TlsBufferRxIterType           CertStartIdx,
  uint8                               NumCerts);

/**********************************************************************************************************************
 * TcpIp_TlsClientGetNumOfCertificates
 *********************************************************************************************************************/
/*! \brief         Obtain the number of certificates in the received certificate chain
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertStartIdx    Start Idx of the certificate data
 *  \param[in]     CertChainLen    Length of the certificate chain
 *  \param[out]    NumCertPtr      Number of certificates in the chain
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientGetNumOfCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      CertStartIdx,
  uint32                      CertChainLen,
  TCPIP_P2V(uint8)            NumCertPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractNextServerCertificate
 *********************************************************************************************************************/
/*! \brief         Extract the next server certificate from the given certificate index
 *  \details       -
 *  \param[in]     CertStartIdx         Read Idx of the Certificate data
 *  \param[out]    CertDataPtr          Pointer to Certificate data struct
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractNextServerCertificate(
  TcpIp_TlsBufferRxIterType           CertStartIdx,
  TCPIP_P2V(TcpIp_CertDataType)       CertDataPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo
 *********************************************************************************************************************/
/*! \brief         Load the server certificate into the KeyM certificate group
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     Certificate             Leaf certificate to be loaded
 *  \param[out]    CertGroupIdSelectedPtr  The certificate group to which cert was loaded to
 *                                         TCPIP_CERTGROUPID_INV if E_NOT_OK
 *  \param[out]    CertIdPtr               The certificate Id to which cert was loaded to
 *                                         TCPIP_CERTID_INV if E_NOT_OK
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  TCPIP_P2C(TcpIp_CertDataType)            Certificate,
  TCPIP_P2V(TcpIp_CertificateGroupIdType)  CertGroupIdSelectedPtr,
  TCPIP_P2V(TcpIp_CertificateIdType)       CertIdPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsUpdateOverallCertValidationResult
 *********************************************************************************************************************/
/*! \brief         Update the overall validation result of the received certificate chain
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    CertValidResultPtr      Overall validation result of certificate chain
 *                                         All certificates in chain are valid (TCPIP_TLS_VALIDATION_OK)
 *                                         At least one certificate in chain is invalid (TCPIP_TLS_VALIDATION_NOT_OK)
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsUpdateOverallCertValidationResult(
  TcpIp_TlsConnectionIterType                TlsConIdx,
  TCPIP_P2V(TcpIp_CertValidationResultType)  CertValidResultPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsGetAlertForBadCertificateChain
 *********************************************************************************************************************/
/*! \brief         Determine the correct alert description for the bad certificate chain
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    AlertDescriptionPtr     Alert description for the bad certificate chain
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForBadCertificateChain(
  TcpIp_TlsConnectionIterType                TlsConIdx,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType)   AlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsGetAlertForCertificateStatus
 *********************************************************************************************************************/
/*! \brief         Determine the correct alert description for the given certificate
 *  \details       -
 *  \param[in]     CertStatusIdx     Current index of the certificate.
 *  \return        TCPIP_TLS_ALERT_DESC_UNKNOWN_CA    Certificate is self-signed root
 *                 TCPIP_TLS_ALERT_DESC_CERT_EXPIRED  Certificate validity period check failed
 *                 TCPIP_TLS_ALERT_DESC_UNKNOWN_CA    Certificate contains invalid chain of trust
 *                 TCPIP_TLS_ALERT_DESC_CERT_REVOKED  Certificate is revoked
 *                 TCPIP_TLS_ALERT_DESC_BAD_CERT      Certificate is corrupted or signature validation fails
 *                 TCPIP_TLS_ALERT_UNSET              Certificate valid, no alert should be triggered
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForCertificateStatus(
  TcpIp_TlsCertValidationStatusDynIterType   CertStatusIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus
 *********************************************************************************************************************/
/*! \brief         Determine the correct alert description for the OCSP certificate status
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertStatusIdx            Current index of the certificate.
 *  \return        TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP  OCSP was requested by the TLS Client,
 *                                                            but no OCSP Certificate Status response received
 *                 TCPIP_TLS_ALERT_DESC_CERT_REVOKED          Certificate is revoked
 *                 TCPIP_TLS_ALERT_UNSET                      Certificate valid, no alert should be triggered
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsCertValidationStatusDynIterType CertStatusIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus
 *********************************************************************************************************************/
/*! \brief         Determine the correct alert description for the OCSP response status
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertStatusIdx            Current index of the certificate.
 *  \return        TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP  OCSP was requested by the TLS Client,
 *                                                            but no OCSP Certificate Status response received
 *                 TCPIP_TLS_ALERT_UNSET                      Certificate valid, no alert should be triggered
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsCertValidationStatusDynIterType CertStatusIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClient_TlsUpdateCertChainStatus
 *********************************************************************************************************************/
/*! \brief         Queries the KeyM for the current statuses of certificates in the certificate chain
 *  \details       -
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertStatusUpdateMode   Parameter to control which certificate status should be updated:
 *                                        TCPIP_TLS_UPDATE_CERT_MODE_CHAIN: Update certificate chain information.
 *                                        TCPIP_TLS_UPDATE_CERT_MODE_OCSP:  Update OCSP certificate status information.
 *  \return        E_OK                   Certificate chain is valid, certificate status updated
 *                 E_NOT_OK               Error occurred in KeyM operation, certificate status not updated
 *  \pre           Certificate chain validation must be already triggered
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClient_TlsUpdateCertChainStatus(
  TcpIp_TlsConnectionIterType           TlsConIdx,
  TcpIp_Tls_CertStatusUpdateModeType   CertStatusUpdateMode);

/**********************************************************************************************************************
* TcpIp_TlsClientHsStm_ParseServerCertificate
*********************************************************************************************************************/
/*! \brief         Parse the server certificate message
 *  \details       -
 *  \param[in]     TlsConIdx     TLS connection index
 *                               CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState
*********************************************************************************************************************/
/*! \brief         Determine the next valid TLS handshake state after the certificate message
 *  \details       This function can be called multiple times, when we do not received the next message and can not
 *                 determine the valid next state
 *  \param[in]     TlsConIdx     TLS connection index
 *                               CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr  Next state of the client HS state machine
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerCertificateInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server certificate information from the received RL frame
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                     Next state of the client HS state machine
 *  \return        E_OK                             Operation successful
 *  \return        E_NOT_OK                         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerCertificateInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain
 *********************************************************************************************************************/
/*! \brief         Process the certificate chain in the received server cert message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain(
  TcpIp_TlsConnectionIterType TlsConIdx);


/**********************************************************************************************************************
* TcpIp_TlsClientHsStm_ParseServerCertificateStatus
*********************************************************************************************************************/
/*! \brief         Parse the server certificate status message
 *  \details       -
 *  \param[in]     TlsConIdx     TLS connection index
 *                               CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server certificate information from the received RL frame
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                     Next state of the client HS state machine
 *  \return        E_OK                             Operation successful
 *  \return        E_NOT_OK                         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus
 *********************************************************************************************************************/
 /*! \brief         Extract the received Server certificate status information from the Tls RxBuffer
  *  \details       -
  *  \param[in]     TlsConIdx                        TLS connection index
  *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \return        E_OK                             Operation successful
  *  \return        E_NOT_OK                         Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation
 *********************************************************************************************************************/
 /*! \brief         Triggers the validation of the received OCSP status response
  *  \details       The actual validation is done in the low prio task of the TLS
  *  \param[in]     TlsConIdx                        TLS connection index
  *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus
 *********************************************************************************************************************/
/*! \brief         Update the certificate status with the result from the OCSP validation
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                             Operation successful
 *  \return        E_NOT_OK                         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult
 *********************************************************************************************************************/
/*! \brief         Read the OCSP status of the leaf certificate
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    LeafCertStatusResponsePtr        OCSP Status Response of the Leaf certificate
 *                                                  CONSTRAINT: not NULL_PTR
 *  \return        E_OK                             Leaf certificate status successfully read and stored in LeafCertStatusResponsePtr
 *  \return        E_NOT_OK                         Status of Leaf certificate could not be determined

 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_CP2V(TcpIp_CertificateStatusResponseType) LeafCertStatusResponsePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState
 *********************************************************************************************************************/
 /*! \brief         Determine the next valid TLS handshake state, depending on the selected key exchange method
  *  \details       -
  *  \param[in]     TlsConIdx                        TLS connection index
  *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[out]    NextStatePtr                     Next state of the client HS state machine
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerKeyExchange
 *********************************************************************************************************************/
/*! \brief         Parse the received server key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx        TLS connection index
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server key exchange information from the received message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                      Next state of the client HS state machine
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature
 *********************************************************************************************************************/
/*! \brief         Verify the server certificate signature
 *  \details       Use the generated key to verify the leaf certificate signature
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState
 *********************************************************************************************************************/
/*! \brief         Verify the server certificate signature
 *  \details       Use the generated key to verify the leaf certificate signature
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr                      Next state of the client HS state machine
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey
 *********************************************************************************************************************/
/*! \brief         Add the DH public key to the client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams
 *********************************************************************************************************************/
/*! \brief         Get server parameters from the server key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr        Next state of the client HS state machine
 *  \return        E_OK                Operation successful
 *  \return        E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk
 *********************************************************************************************************************/
/*! \brief         Get server parameters from the server key exchange message for PSK identity
 *  \details       -
 *  \param[in]     TlsConIdx        TLS connection index
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK             Operation successful
 *  \return        E_NOT_OK         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc
*********************************************************************************************************************/
/*! \brief         Get server parameters from the server key exchange message for ECC identity
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType
 *********************************************************************************************************************/
/*! \brief         Get the elliptic curve type from the server exchange message
 *  \details       -
 *  \param[in]     TlsConIdx        TLS connection index
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return         E_OK            Operation successful
 *  \return         E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId
 *********************************************************************************************************************/
/*! \brief         Obtain the elliptic curve Id of the server exchange message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey
 *********************************************************************************************************************/
/*! \brief         Obtain the public key from the received server key exchange
 *  \details       -
 *  \param[in]     TlsConIdx                  TLS connection index
 *                                            CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ServerKeyExchangeEndIdx    End Idx of the server key exchange message
 *  \return        E_OK                       Operation successful
 *  \return        E_NOT_OK                   Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  TcpIp_TlsBufferRxIterType    ServerKeyExchangeEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm
 *********************************************************************************************************************/
/*! \brief         Obtain signature algorithm from the received server key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature
 *********************************************************************************************************************/
/*! \brief         Extract the signature from the received server key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx                  TLS connection index
 *                                            CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ServerKeyExchangeEndIdx    End Idx of the server key exchange message
 *  \return        E_OK                       Operation successful
 *  \return        E_NOT_OK                   Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  TcpIp_TlsBufferRxIterType    ServerKeyExchangeEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId
 *********************************************************************************************************************/
/*! \brief         Validate the elliptic curve id in the received server key exchange message to be one of the
 *                 supported curves for this connection.
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CurveId         Elliptic curve id
 *  \return        E_OK            If suitable CipherWorker found
 *  \return        E_NOT_OK        If NO suitable CipherWorker found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsEllipticCurveIdType CurveId);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerCertificateRequest
 *********************************************************************************************************************/
/*! \brief         Parse the server hello done message
 *  \details       -
 *  \param[in]     TlsConIdx         TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificateRequest(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractCertificateRequestInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server certificate request information from the message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractCertificateRequestInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes
 *********************************************************************************************************************/
/*! \brief         Extract the certificate types information from the server certificate request message
 *  \details       This function does not provide any functionality since the TLS client does not support client auth.
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms
 *********************************************************************************************************************/
/*! \brief         Extract the signature hash algorithms from the server certificate request message
 *  \details       This function does not provide any functionality since the TLS client does not support client auth.
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames
 *********************************************************************************************************************/
/*! \brief         Extract the distinguished names from the server certificate request message
 *  \details       This function does not provide any functionality since the TLS client does not support client auth.
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON */

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerHelloDone
 *********************************************************************************************************************/
/*! \brief         Parse the server hello done message
 *  \details       -
 *  \param[in]     TlsConIdx         TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerHelloDone(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server hello done information from the message
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation(
  TcpIp_TlsConnectionIterType  TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_SendClientCertificate
 *********************************************************************************************************************/
/*! \brief         Trigger the transmission of client certificate message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientCertificate(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_PrepareClientCertificate
 *********************************************************************************************************************/
/*! \brief         Prepare the data structure of the client certificate message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientCertificateAddCertificates
 *********************************************************************************************************************/
/*! \brief         Add the configured certificates to the client certificate message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientCertificateAddCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON */

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_SendClientKeyExchange
 *********************************************************************************************************************/
/*! \brief         Trigger the transmission of client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientKeyExchange(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation
 *********************************************************************************************************************/
/*! \brief         Prepare the client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation(
  TcpIp_TlsConnectionIterType  TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams
*********************************************************************************************************************/
/*! \brief         Add the DH parameters into the client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams(
  TcpIp_TlsConnectionIterType  TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams
*********************************************************************************************************************/
/*! \brief         Add PSK parameters into the client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams(
    TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity
 *********************************************************************************************************************/
/*! \brief         Select the PSK identity for the client key exchange message
 *  \details       If no matching PSK identity found, use the default PSK identity
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity(
    TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints
 *********************************************************************************************************************/
/*! \brief         Check if received PSK hint is already known to the Tls client
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint
 *********************************************************************************************************************/
/*! \brief         Compare the received PSK hint with know PSK identities to the Tls client
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity
**********************************************************************************************************************/
/*! \brief         Add selected PSK identity to the client exchange message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity(
  TcpIp_TlsConnectionIterType  TlsConIdx);

/**********************************************************************************************************************
* TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength
**********************************************************************************************************************/
/*! \brief         Trigger transmission of client key exchange message
 *  \details       -
 *  \param[in]     TlsConIdx        TLS connection index
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    NextStatePtr     Next state of the client HS state machine
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
  TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength(
  TcpIp_TlsConnectionIterType         TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState)  NextStatePtr);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret
 *********************************************************************************************************************/
/*! \brief         Calculate the shared secret for the client key exchange
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret
 *********************************************************************************************************************/
/*! \brief         Calculate the PSK pre master secret for client key exchange
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret
 *********************************************************************************************************************/
/*! \brief         Calculate the master secret for the client key exchange
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature
 *********************************************************************************************************************/
/*! \brief         Decode the received signature
 *  \details       Depending on the ciphersuite perform decode operation
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    DecodedSignatureLenPtr            Length of the received signature
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            DecodedSignatureLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_DecodeSecp256r1Signature
 *********************************************************************************************************************/
/*! \brief         Decode the received Secp256 signature
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                             Operation successful
 *  \return        E_NOT_OK                         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_DecodeSecp256r1Signature(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_DecodeEd25519Signature
 *********************************************************************************************************************/
/*! \brief         Decode the received Ed25519 signature
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_DecodeEd25519Signature(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming
 *********************************************************************************************************************/
/*! \brief         Set the crypto keys for Aes128cbc streaming
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming
 *********************************************************************************************************************/
/*! \brief         Set the crypto keys for Aes128Gcm streaming
 *  \details       -
 *  \param[in]     TlsConIdx         TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK              Operation successful
 *  \return        E_NOT_OK          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming
 *********************************************************************************************************************/
/*! \brief         Set the crypto keys for NULL streaming
 *  \details       -
 *  \param[in]     TlsConIdx        TLS connection index
 *                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK             Operation successful
 *  \return        E_NOT_OK         Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_SendClientCcs
 *********************************************************************************************************************/
/*! \brief         Trigger transmission of CCs message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_SendClientFinished
 *********************************************************************************************************************/
/*! \brief         Send client finished message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_PrepareClientFinished
 *********************************************************************************************************************/
/*! \brief         Prepare the client finished message
 *  \details       -
 *  \param[in]     TlsConIdx                        TLS connection index
 *                                                  CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ClientFinishedAddClientFinishedData
 *********************************************************************************************************************/
/*! \brief         Add client finished data to the client finished message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientFinishedAddClientFinishedData(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerFinished
 *********************************************************************************************************************/
/*! \brief         Parse the received server finished message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_ExtractServerFinishedInformation
 *********************************************************************************************************************/
/*! \brief         Extract the server finished information from the server finished message
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerFinishedInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_CalcServerFinishedHash
 *********************************************************************************************************************/
/*! \brief         Calculate the server finished hash locally
 *  \details       Trigger async calculation of server finished hash
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_CalcServerFinishedVerifyData
 *********************************************************************************************************************/
/*! \brief         Calculate the server finished verify data
 *  \details       Trigger calculation of the server finished verify data
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_CalcServerFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientMsg_CompareFinishedVerifyData
 *********************************************************************************************************************/
/*! \brief         Compare the server finished verify data with locally calculated value
 *  \details       -
 *  \param[in]     TlsConIdx                         TLS connection index
 *                                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                              Operation successful
 *  \return        E_NOT_OK                          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_CompareFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_ParseServerCcs
 *********************************************************************************************************************/
/*! \brief         Parse the received server CCs message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_VerifyServerFinished
 *********************************************************************************************************************/
/*! \brief         Verify the server finished message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_VerifyServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsClientHsStm_FinalizeHandshake
 *********************************************************************************************************************/
/*! \brief         Finalize the Tls handshake
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_FinalizeHandshake(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_HandleErrorDuringPreparation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType        hsUserError;
  TcpIp_TlsAlertLevelType       alertLevel;
  TcpIp_TlsAlertDescriptionType alertDescription;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the corresponding error id and report the error to the user */
  hsUserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PREPARE_HS_MSG;
  hsUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTHSMSG;
  hsUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  TcpIp_TlsCoreError_ReportUserError(hsUserError);

  /* #20 Set the corresponding alert level and description and trigger the transmission of the occurred alert */
  alertLevel       = TCPIP_TLS_ALERT_LEVEL_FATAL;
  alertDescription = TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE;

  TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);

  /* Change the state to HANDSHAKE_ABORT */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

} /* TcpIp_TlsClientHsStm_HandleErrorDuringPreparation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add compression method length (1 Byte) to TLS TxBuffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),
                  0, TCPIP_TLSCLIENT_COMPMETHLEN_LEN);

  /* Increment the write index by the consumed length (1 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLSCLIENT_COMPMETHLEN_LEN);

  /* #20 The only supported compression method is "no_compression". Add compression method ('0' = no_compression) to TLS TxBuffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),
                  0, TCPIP_TLS_COMPRESSION_METHOD_NONE);

  /* Increment the write index by the consumed length (1 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLSCLIENT_COMPMETH_LEN);

} /* TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  TcpIp_SizeOfTlsBufferMgmtType    tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Extension index information */
  /* Supported Group Extension Format
   *       [ext Type][ext Len][supported Group Len][group 1]            [group n]
   * Byte: 0       1 2      3 4                  5 6      7             (x-1)  x
   *                                                \---consumedExtensionLen---/
  */
  TcpIp_TlsBufferTxIterType extTypeIdx               = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxIterType extLenIdx                = extTypeIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;
  TcpIp_TlsBufferTxIterType extSupportedGroupsLenIdx = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;
  TcpIp_TlsBufferTxIterType extGroupStartIdx         = extSupportedGroupsLenIdx + TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN;

  uint16 consumedExtensionLen = 0;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Write all available supported groups in the TLS TxBuffer */
  /* Iterate over all configured CipherWorker for this TLS connection */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);
    TcpIp_TlsHandshakeIndStartIdxOfTlsCipherWorkerType handshakeStartIdx
      = TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_TlsHandshakeIndEndIdxOfTlsCipherWorkerType handshakeEndIdx
      = TcpIp_GetTlsHandshakeIndEndIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_TlsHandshakeIndIterType handshakeIter;

    /* Iterate over all configured handshake for this CipherWorker */
    for (handshakeIter = handshakeStartIdx; handshakeIter < handshakeEndIdx; handshakeIter++)
    {
      /* Get the configured elliptic curve Id ( = value of this extension) */
      TcpIp_TlsHandshakeIterType tlsHandshakeIdx = TcpIp_GetTlsHandshakeInd(handshakeIter);
      TcpIp_TlsEllipticCurveIdType currentEllipticCurveId = TcpIp_GetEllipticCuveIdOfTlsHandshake(tlsHandshakeIdx);

      /* If the handshake is configured as PSK (curveId set to TCPIP_CURVE_ID_NO_CURVE) we should not add any extension value */
      if (currentEllipticCurveId != TCPIP_CURVE_ID_NO_CURVE)
      {
        /* Add the extension value considering duplicate value entries */
        TcpIp_TlsClientMsg_ClientHelloAddExtensionValue(TlsConIdx, (uint16)currentEllipticCurveId,
          extGroupStartIdx, &consumedExtensionLen);
      }
    }
  }

  /* #20 Check if there are extensions added and update the length information in the TLS TxBuffer */
  if (consumedExtensionLen != 0u)
  {
    /* #30 Set the extension type to TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS (0x00au) */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeIdx), 0, TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

    /* #40 Set extension supported group length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extSupportedGroupsLenIdx), 0, consumedExtensionLen);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN);

    /* #50 Set extension length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, consumedExtensionLen + TCPIP_TLS_EXTENSION_LENGTH_LEN);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);
  }
} /* TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  TcpIp_SizeOfTlsBufferMgmtType     tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Extension index information */
  /* Supported Signature Algorithm Extension Format
   *       [ext Type][ext Len][Signature Algorithm Len][algorithm 1]    [algorithm n]
   * Byte: 0       1 2      3 4                      5 6          7     (x-1)      x
   *                                                    \---consumedExtensionLen---/
  */
  TcpIp_TlsBufferTxIterType extTypeIdx                   = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxIterType extLenIdx                    = extTypeIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;
  TcpIp_TlsBufferTxIterType extSignatureAlgorithmsLenIdx = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;
  TcpIp_TlsBufferTxIterType extAlgorithmsStartIdx        = extSignatureAlgorithmsLenIdx + TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_LENGTH_LEN;

  uint16 consumedExtensionLen = 0;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Write all available signature algorithms in the TLS TxBuffer */
  /* Iterate over all configured CipherWorker for this TLS connection */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);
    TcpIp_TlsHandshakeIndStartIdxOfTlsCipherWorkerType handshakeStartIdx
      = TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_TlsHandshakeIndEndIdxOfTlsCipherWorkerType handshakeEndIdx
      = TcpIp_GetTlsHandshakeIndEndIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_TlsHandshakeIndIterType handshakeIter;

    /* Iterate over all configured handshake for this CipherWorker */
    for (handshakeIter = handshakeStartIdx; handshakeIter < handshakeEndIdx; handshakeIter++)
    {
      /* Get the configured signature algorithm ( = value of this extension) */
      TcpIp_TlsHandshakeIterType tlsHandshakeIdx = TcpIp_GetTlsHandshakeInd(handshakeIter);
      TcpIp_SignatureAlgorithmIdType currentSignatureAlgorithmId = TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(tlsHandshakeIdx);

      /* Add the extension value considering duplicate value entries */
      TcpIp_TlsClientMsg_ClientHelloAddExtensionValue(TlsConIdx, (uint16)currentSignatureAlgorithmId,
        extAlgorithmsStartIdx, &consumedExtensionLen);
    }
  }

  /* #20 Check if there are extensions added and update the length information in the TLS TxBuffer */
  if (consumedExtensionLen != 0u)
  {
    /* #30 Set the extension type to TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS (0x000d) */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeIdx), 0, TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

    /* #40 Set extension signature algorithms length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extSignatureAlgorithmsLenIdx), 0, consumedExtensionLen);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_LENGTH_LEN);

    /* #50 Set extension length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, consumedExtensionLen + TCPIP_TLS_EXTENSION_LENGTH_LEN);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);
  }
} /* TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms() */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType    tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Extension index information */

  /* Supported Point Formats Extension Format
                                  +----> Fixed length: (1)
                                 /                          +--->  Fixed value: uncompressed (0)
                                /                          /
   *       [ext Type][ext Len][EC Point Format Len][EC Point Format]
   * Byte: 0       1 2      3                    4                 5
   *                           \-------consumedExtensionLen--------/
  */
  TcpIp_TlsBufferTxIterType extTypeIdx               = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxIterType extLenIdx                = extTypeIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;
  TcpIp_TlsBufferTxIterType extEcPointFormatLenIdx   = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;

  uint16 consumedExtensionLen = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* Only add this specific extension if one of the referenced cipher worker is configured as ECC cipher worker */
  if (TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite(TlsConIdx) == TRUE)
  {
    /* Combine both fix parameter to uiint16 value */
    /* 0x0100 = [EC Point Format Len (0x01)][EC Point Format (0x00)] */
    uint16 fixedEcPointsFormatExtensionValue =
      ((uint16)TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_FIXED_LENGTH << 8) | TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_UNCOMPRESSED;

    /* #10 Add the extension value to the TxBuffer if TLS connection uses at least one ECC cipher suite */
    TcpIp_TlsClientMsg_ClientHelloAddExtensionValue(TlsConIdx, fixedEcPointsFormatExtensionValue,
      extEcPointFormatLenIdx, &consumedExtensionLen);

    /* #20 Set the extension type to TCPIP_TLS_EXTENSION_EC_POINT_FORMAT (0x000b) */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeIdx), 0, TCPIP_TLS_EXTENSION_EC_POINT_FORMAT);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

    /* #30 Set overall extension length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, consumedExtensionLen);
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);
  }

} /* TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 /* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType    tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Trusted CA Extension Format
   *                      +--> consumed Extension Length
   *                     /         +--> Trusted Authorities List Start Index
   *                    /         /      /--------Trusted Authorities List Length -------\
   *       [ext Type][ext Len][List Len][ID Type_1][SHA-1 Hash_1][ID Type_2][SHA-1 Hash_2] ...
   * Byte: 0       1 2      3 4       5          6  7         27                         /
   *                          \-----------------consumedExtensionLen--------------------/
   */

  TcpIp_TlsBufferTxIterType extTypeIdx = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxIterType extLenIdx  = extTypeIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;
  uint16 consumedExtensionLen          = 0u;

  TcpIp_TlsBufferTxIterType extTrustedAuthoritiesListStartIdx = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Only add this specific extension if one of the referenced cipher worker is configured as ECC cipher worker */
  if (TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite(TlsConIdx) == TRUE)
  {
    /* #20 Check if the extension is enabled on this TLS connection */
    if (TcpIp_IsTlsUseExtensionTrustedCaIndicationOfTlsConnection(TlsConIdx) == TRUE)
    {
      /* #30 Add the list of all trusted CAs (SHA1 hashes of installed root certificates) */
      if (TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList(TlsConIdx, extTrustedAuthoritiesListStartIdx,
            &consumedExtensionLen) == E_OK)
      {
        /* #40 Extension trusted CA indication added - update overall extension information */
        /* Increment the write index by the consumed extension length */
        TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, consumedExtensionLen);

        /* Set the extension type to TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION (0x0003) */
        IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeIdx), 0, TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION);
        TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

        /* Set overall extension length */
        IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, consumedExtensionLen);
        TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);
      }
      /* else - no need to trigger alert if something is wrong with the hash calculation. Continue with the TLS handshake */
    }
    /* else - Feature not enabled, nothing to do. */
  }
} /* TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList
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
 /* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TrustedAuthorityListStartIdx,
  TCPIP_P2V(uint16) ConsumedLenPtr)
{
  /* RFC6066 - 6. Trusted CA Indication */
  /*
   *   struct {
   *       TrustedAuthority trusted_authorities_list<0..2^16-1>;
   *   } TrustedAuthorities;
   *
   *   struct {
   *       IdentifierType cert_sha1_hash(3);
   *       cert_sha1_hash: SHA1Hash;
   *   } TrustedAuthority;
   */

  /* ----- Local Variables----------------------------------------------- */
  KeyM_CertificateStatusType currentCertificateStatus;

  TcpIp_TlsCertIdIssuerStartIdxOfTlsConnectionType tlsCertIdIssuerIter;
  TcpIp_TlsBufferTxIterType trustedAuthoritiesListLengthIdx = TrustedAuthorityListStartIdx;

  TcpIp_TlsBufferTxIterType trustedAuthoritiesListIter
    = trustedAuthoritiesListLengthIdx + TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 iterate over all referenced issuer certificate of this TLS connection (root certificates) */
  for (tlsCertIdIssuerIter = TcpIp_GetTlsCertIdIssuerStartIdxOfTlsConnection(TlsConIdx);
       tlsCertIdIssuerIter < TcpIp_GetTlsCertIdIssuerEndIdxOfTlsConnection(TlsConIdx);
       tlsCertIdIssuerIter++)
  {
    KeyM_CertificateIdType certId = TcpIp_GetTlsCertId(tlsCertIdIssuerIter);

    /* #20 Check the status of the current selected certificate */
    if (KeyM_CertGetStatus(certId, &currentCertificateStatus) == E_OK)
    {
      if ((currentCertificateStatus == KEYM_CERTIFICATE_PARSED_NOT_VALIDATED)
        || (currentCertificateStatus == KEYM_CERTIFICATE_VALID))
      {
        uint8 tmpSha1Hash[TCPIP_TLS_HASH_SHA1_LEN];
        uint32 tmpSha1HashLen = TCPIP_TLS_HASH_SHA1_LEN;
        /* #30 In case of an valid certificate status, try to get the calculated SHA1 hash for this certificate */
        if (KeyM_GetCertHash(certId, &tmpSha1Hash[0], &tmpSha1HashLen) == E_OK)
        {
          if (tmpSha1HashLen == TCPIP_TLS_HASH_SHA1_LEN)
          {
            /* #40 SHA1 hash for the current certificate is valid, add the hash to the TlsTxBuffer */
            /* Format of each trusted authority element: [IdentifierType][cert_sha1_hash] */

            /* Write the identifier type: cert_sha1_hash(3) to the TlsTxBuffer */
            IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(trustedAuthoritiesListIter), 0,
              TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_TYPE_CERT_SHA1_HASH);
            trustedAuthoritiesListIter++;

            /* Write the calculated SHA1 hash to the TlsTxBuffer */
            VStdMemCpy(TcpIp_GetAddrTlsBufferTx(trustedAuthoritiesListIter), &tmpSha1Hash[0], TCPIP_TLS_HASH_SHA1_LEN); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
            trustedAuthoritiesListIter += TCPIP_TLS_HASH_SHA1_LEN;

            retVal = E_OK;
          }
          else
          {
            /* #50 SHA1 hash for the current certificate is invalid, do not add this extension and skip further processing */
            retVal = E_NOT_OK;
            break;
          }
        }
        /* else - No need to cancel TLS handshake in case of E_NOT_OK from KeyM */
      }
      /* else - No need to cancel TLS handshake in case of invalid certificate status */
    }
  }

  /* At least one hash added - update overall length information */
  if (retVal == E_OK)
  {
    uint16 consumedTrustedAuthoritiesListLength
      = (uint16)(trustedAuthoritiesListIter - (trustedAuthoritiesListLengthIdx + TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN));

    /* Write the Trusted Authorities List Length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(trustedAuthoritiesListLengthIdx), 0,
      consumedTrustedAuthoritiesListLength);

    /* Set the consumed overall length */
    *ConsumedLenPtr = (consumedTrustedAuthoritiesListLength + TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN);
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ClientExtAddTrustedAuthoritiesList() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest
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
 */
 /* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType    tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Certificate Status request Extension Format
   *                                                                                 +-> list of OCSP responders that the client trusts (optional)
   *                      +--> consumed Extension Length                             /              +->  Length of request_extensions list
   *                     /         +--> Certificate status request type             /              /                       +-> OCSP request extensions (optional)
   *                    /         /                     +-> Responder list Length  /              /                       /
   *                   /         /                     /                          /              /                       /
   *       [ext Type][ext Len][CertStatusType][responder_id_list Len][responder_id 1]... [request_extensions Len] [request_extensions 1]...
   * Byte: 0       1 2      3               4 5                    6  7                   7                                            /
   *                          \---------------------------consumedExtensionLen--------------------------------------------------------/
   */

  TcpIp_TlsBufferTxIterType extTypeIdx = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxIterType extLenIdx = extTypeIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;
  uint16 consumedExtensionLen = 0u;

  TcpIp_TlsBufferTxIterType extCertificateStatusRequestStartIdx = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Only add this specific extension if one of the referenced cipher worker is configured as ECC cipher worker */
  if (TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite(TlsConIdx) == TRUE)
  {
    /* #20 Check if the extension is enabled on this TLS connection */
    if (TcpIp_IsTlsUseExtensionCertificateStatusRequestOfTlsConnection(TlsConIdx) == TRUE)
    {
      TcpIp_TlsCertValidationStatusDynStartIdxOfTlsConnectionType leafCertStatusIdx
        = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);

      /* RFC6066 - 8.  Certificate Status Request
       * Format of CertificateStatusType:
       * enum { ocsp(1), (255) } CertificateStatusType;
       */
      /* #30 Update CertificateStatusType with type OCSP */
      IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(extCertificateStatusRequestStartIdx), 0,
        TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_OCSP_TYPE);
      extCertificateStatusRequestStartIdx += TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN;
      consumedExtensionLen += TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN;

      /* RFC6066 - 8.  Certificate Status Request
       *   A zero-length "responder_id_list" sequence has the special meaning that the responders are implicitly known to the server.
       */
      /* #40 Update responder_id_list Len with 0 */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extCertificateStatusRequestStartIdx), 0, 0);
      extCertificateStatusRequestStartIdx += TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN;
      consumedExtensionLen += TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN;

      /* RFC6066 - 8.  Certificate Status Request
       *   A zero-length "request_extensions" value means that there are no extensions.
       */
      /* #50 Update request_extensions Len with 0 */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extCertificateStatusRequestStartIdx), 0, 0);
      consumedExtensionLen += TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_REQUEST_EXTENSIONS_LEN;

      /* #60 Extension Certificate Status Request - update overall extension information */
      /* Increment the write index by the consumed extension length */
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, consumedExtensionLen);

      /* Set the extension type to TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST (0x0005) */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeIdx), 0, TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST);
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

      /* Set overall extension length */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, consumedExtensionLen);
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);

      /* #70 Update mandatory extension information */
      /* This extensions is mandatory if it is enabled. Used later to check if we receive the extension from the Server. */
      /* Check if we received the extension from the server is done in TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions
       * Check if we should cancel the handshake is done in ServerHelloDone */
      TcpIp_SetMandatoryReceivedCertificateStatusRequestExtensionOfTlsConnectionDyn(TlsConIdx, TRUE);

      TcpIp_GetAddrTlsCertValidationStatusDyn(leafCertStatusIdx)->CertStatusResponse.OcspConnectionState
        = TCPIP_TLS_OCSP_CONNECTION_STATE_REQUESTED;
    }
    /* else - Feature not enabled, nothing to do. */
  }
} /* TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest() */
#  endif /*(TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloAddExtensionValue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddExtensionValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 ExtensionValue,
  TcpIp_TlsBufferTxIterType ExtensionStartIdx,
  TCPIP_P2V(uint16) ConsumedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check if this specific value is already present */
    TcpIp_TlsBufferTxIterType extensionEndIdx = (ExtensionStartIdx + *ConsumedLenPtr);
    if (TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent(ExtensionStartIdx, extensionEndIdx, ExtensionValue) == FALSE)
    {
    /* #20 If it is not present, add the extension value at the end of the list and update the consumed length information */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extensionEndIdx), 0, ExtensionValue);

      /* Increment the write index by the consumed length (2 Byte) */
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ELEMENT_LEN);
      *ConsumedLenPtr += TCPIP_TLS_EXTENSION_ELEMENT_LEN;
    }

} /* TcpIp_TlsClientMsg_ClientHelloAddExtensionValue() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent(
  TcpIp_TlsBufferTxIterType ExtensionStartIdx,
  TcpIp_TlsBufferTxIterType ExtensionEndIdx,
  uint16                    ExtensionValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean valueAlreadyPresent = FALSE;
  TcpIp_TlsBufferTxIterType extensionStartIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over TLS TxBuffer (beginning at StartIdx) and check if the given value is already added */
  for (extensionStartIdx = ExtensionStartIdx; extensionStartIdx < ExtensionEndIdx; extensionStartIdx += TCPIP_TLS_EXTENSION_ELEMENT_LEN)
  {
    uint16 alreadyAddedValue = IpBase_GetUint16(TcpIp_GetAddrTlsBufferTx(extensionStartIdx), 0);

    if (alreadyAddedValue == ExtensionValue)
    {
      valueAlreadyPresent = TRUE;
      break;
    }
  }
  return valueAlreadyPresent;
} /* TcpIp_TlsClientMsg_ClientHelloIsExtensionAlreadyPresent() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloAddClientExtensions
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddClientExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Store the extension length field write index for later usage */
  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType extensionLenStartIdx
    = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint16 extTotalLen;

  /* ----- Implementation ----------------------------------------------- */

  /* Store the start of the transmitted extensions (extension Len) - Used later to validate the received Server extensions */
  TcpIp_SetTlsBufferTxClientExtensionsIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* Skipp the write index for the extension length field (2 Byte), filled out later */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN);

  /* #10 Add supported groups extension - TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS */
  TcpIp_TlsClientMsg_ClientHelloExtAddSupportedGroups(TlsConIdx);

  /* #20 Add signature algorithms extension - TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS */
  TcpIp_TlsClientMsg_ClientHelloExtAddSignatureAlgorithms(TlsConIdx);

  /* #30 Add ec supported points format extension - TCPIP_TLS_EXTENSION_EC_SUPPORTED_POINT_FORMAT */
  TcpIp_TlsClientMsg_ClientHelloExtAddSupportedPointsFormat(TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  /* #40 Add trusted CA indication extension - TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION */
  TcpIp_TlsClientMsg_ClientExtAddTrustedCAIndication(TlsConIdx);

  /* #50 Add certificate status request extension - TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST */
  TcpIp_TlsClientMsg_ClientExtAddCertificateStatusRequest(TlsConIdx);

#  endif
  /* #60 Calculate and set overall extension length */
  extTotalLen = (uint16)(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) - extensionLenStartIdx
                 - TCPIP_TLS_EXTENSION_LENGTH_LEN);
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extensionLenStartIdx), 0, extTotalLen);

} /* TcpIp_TlsClientMsg_ClientHelloAddClientExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientHelloAddCipherSuites
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientHelloAddCipherSuites(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  TcpIp_SizeOfTlsBufferMgmtType    tlsBufferMgmtIdx    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint16                           cipherSuitesCnt     = 0u;
  uint16                           sizeCipherSuiteList;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured cipherWorker and write the configured cipher suites to the TLS TxBuffer */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx =
      TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_CipherSuiteIdOfTlsCipherDefinitionType cipherSuiteId =
      TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx); /* Cipher suite ID as hex value */
    uint32 cipherSuiteIdWriteOffset = (TCPIP_TLS_CIPHERSUITESLEN_LEN + (TCPIP_TLS_CIPHERSUITESLEN_LEN * (uint32)cipherSuitesCnt));

    /* Write the selected cipher suite to the TX buffer at the correct offset */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),
                     cipherSuiteIdWriteOffset, cipherSuiteId);

    /* Increment counter of cipher suites supported */
    cipherSuitesCnt++;
  }

  /* Calculate the size of the cipher suite list */
  sizeCipherSuiteList = (TCPIP_TLS_CIPHERSUITESLEN_LEN * cipherSuitesCnt);

  /* #20 Add the length of cipher suite list to the TLS TxBuffer */
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, sizeCipherSuiteList);

  /* Increment the write index by the consumed length  */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    (TCPIP_TLS_CIPHERSUITESLEN_LEN + (TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType)sizeCipherSuiteList));

} /* TcpIp_TlsClientMsg_ClientHelloAddCipherSuites() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_PrepareClientHello
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientHello(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIdxOfTlsConnectionType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint16 clientHelloLen;
  uint16 writableLength;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ClientHello message by adding all relevant message information */
  /* Set the start index of this message to the current write index */
  /* TlsBufferTxAdHsWriteIdx points to the next free index in the TLS TxBuffer. */
  TcpIp_SetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
       TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_CLIENTHELLO);

  TcpIp_TlsHelloMsg_AddProtocolVersionNr(TlsConIdx);

  retVal = TcpIp_TlsHelloMsg_AddRandomStructure(TlsConIdx);

  TcpIp_TlsHelloMsg_AddSessionId(TlsConIdx);

  TcpIp_TlsClientMsg_ClientHelloAddCipherSuites(TlsConIdx);

  TcpIp_TlsClientMsg_ClientHelloAddCompressionMethod(TlsConIdx);

  TcpIp_TlsClientMsg_ClientHelloAddClientExtensions(TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
  /* #20 Add the client random to the Msa_AccessBuffer if enabled */
  TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer(TlsConIdx);
#  endif

  /* #30 Write the length information into the HS Header (Message length = WriteIdx - ServerHelloStartIdx). */
  clientHelloLen = (uint16)(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
    - TcpIp_GetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) );
  TcpIp_SetClientHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, clientHelloLen);

  writableLength = clientHelloLen - TCPIP_TLS_HSHDRLEN;
  TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), (uint32)writableLength);

  return retVal;
} /* TcpIp_TlsClientMsg_PrepareClientHello() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_SendClientHello
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientHello(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Build the ClientHello message and fill the relevant information */
  retVal = TcpIp_TlsClientMsg_PrepareClientHello(TlsConIdx);

  /* #20 Check if the ClientHello preparation is completed */
  if (retVal == E_OK)
  {
    /* #30 Preparation was successful. Change the TLS-Handshake state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO and trigger the transmission */
    TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx =
      TcpIp_GetTlsClientConnectionIdxOfTlsConnection( TlsConIdx);

    /* ClientHello message is now ready to send, set the corresponding trigger */
    TcpIp_SetHelloReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, TRUE);

    /* Change the state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO */
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO);

  }
  else
  {
    /* #40 Preparation failed. Cancel the handshake. */
    TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(TlsConIdx);
  }

} /* TcpIp_TlsClientHsStm_SendClientHello() */

/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerHello
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx =
    TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloIdxOfTlsClientBufferMgmtType serverHelloIdx =
    TcpIp_GetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a message with the HS Type ServerHello was received */
  if (serverHelloIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLOIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_HANDSHAKE_INIT;
    Std_ReturnType retVal;

    /* Reset the handshake state machine trigger */
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* #20 if so, try to extract the ServerHello message */
    retVal = TcpIp_TlsClientMsg_ExtractServerHello(TlsConIdx, &nextState);

    if (retVal == E_OK)
    {
      /* #30 Message parsed successfully - check if the parsing is completely done and change the state */
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_WAIT_CYCLE)
      {
        /* Next logical HS message not received yet, wait one cycle and try again */
        /* Reset wait cycle for next iteration */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
      }
      else
      {
        /* #40 Parsing completely done. Change the state depending on the receive message and the key exchange */
        /* next state is: TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE || TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE || TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);

        /* we successfully processed this RL message, so decrement the counter */
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }
    }
    else
    {
      /* #50 Parsing failed. Cancel the handshake. */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #60 otherwise, we received an unexpected message - Trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }

} /* TcpIp_TlsClientHsStm_ParseServerHello() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ExtractServerHello
*********************************************************************************************************************/
/*!-
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the message parts until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_DONE)/* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Handshake is not aborted due to processing error */
         && (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_HANDSHAKE_ABORT)
             /* Next state could not be determine (missing next HS message) - Wait cycle */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_WAIT_CYCLE)
             /* Error during parsing - abort next steps */
         && (retVal == E_OK))
    {
    /* Get the current sub state of the extraction */
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO:
      {
        /* Extract ServerHello Information */
        retVal = TcpIp_TlsClientMsg_ExtractServerHelloInformation(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
              TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_STATE_CHANGE);
        break;
      } /* TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_STATE_CHANGE:
      {
        /* This state could be a WAIT_CYCLE if the next logical TLS message is not received yet */
        /* Next state of HS depends on selected cipher and received message */
        TcpIp_TlsClientMsg_ServerHelloDetermineNextState(TlsConIdx, NextStatePtr);
        break;
      } /* TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_STATE_CHANGE */

      default:                                                                                                          /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        break;
      } /* default */

    } /* switch */
  } /* while */
  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerHello() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractServerHelloInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHelloInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloIdxOfTlsClientBufferMgmtType serverHelloStartIdx
    = TcpIp_GetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerHelloLenOfTlsClientBufferMgmtType serverHelloLen
    = TcpIp_GetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  TcpIp_TlsBufferRxServerHelloIdxOfTlsClientBufferMgmtType serverHelloEndIdx
    = (serverHelloStartIdx + TCPIP_TLS_HSHDRLEN + serverHelloLen); /* End index of the received ServerHello message - Need for in range checks inside the parser */

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received the absolute minimum length for this type of message and parse all information within the ServerHello message */
  if (TcpIp_TlsHs_CheckExpectedMsgLen(serverHelloLen, TCPIP_TLS_MIN_SERVERHELLO_MSGLEN) == E_OK)
  {
    /* Parse the TLS-Handshake major and minor TLS-Version */
    retVal = TcpIp_TlsMsg_HelloMsgGetVersionNr(TlsConIdx);

    if (retVal == E_OK)
    {
      /* Parse the received ClientHello random number */
      TcpIp_TlsMsg_HelloMsgGetRandom(TlsConIdx);

      /* Parse received session ID (sessions not supported by this implementation) */
      retVal = TcpIp_TlsMsg_HelloMsgGetSessionId(TlsConIdx, serverHelloEndIdx);
    }

    if (retVal == E_OK)
    {
      /* Parse received cipher suite */
      retVal = TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite(TlsConIdx);
    }

    if (retVal == E_OK)
    {
      /* Parse the received compression methods */
      retVal = TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod(TlsConIdx);
    }

    if (retVal == E_OK)
    {
      /* Parse the received ServerHello extensions, if present */
      retVal = TcpIp_TlsClientMsg_ServerHelloGetExtensions(TlsConIdx, serverHelloEndIdx);
    }

    if (retVal == E_OK)
    {
      /* Check if there is some more information in the buffer */
      retVal = TcpIp_TlsMsg_CheckMsgForRemainingData(TlsConIdx, serverHelloEndIdx);
    }

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
    /* #20 Add SessionId and SessionId length to Msa_AccessBuffer if enabled */
    TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer(TlsConIdx);
#  endif
  }
  else
  {
    /* #30 otherwise, we do not receive the ServerHello message with the min required length. Report an User Error */
    TcpIp_TlsUserErrorType serverHelloUserError;
    serverHelloUserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLO;
    serverHelloUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN;
    serverHelloUserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    /* Report the error to the user */
    TcpIp_TlsCoreError_ReportUserError(serverHelloUserError);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerHelloInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx      = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType                retVal                = E_NOT_OK;
  uint16                        cipherSuiteSelected;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the received cipher suite */
  cipherSuiteSelected = IpBase_GetUint16(
    TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);
  /* And increment the read index by the length of the cipher suite length field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CIPHERSUITESLEN_LEN);

  /* #20 Check if we received a matching CipherSuite and select the corresponding CipherWorker as active one */
  if (TcpIp_TlsMsg_SelectMatchingCipherSuiteId(TlsConIdx, cipherSuiteSelected) == E_OK)
  {
    /* #30 Select the active handshake reference if we found a matching cipherWorker */
    TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference(TlsConIdx);

    retVal = E_OK;
  }
  else
  {
    /* #40 If there is no matching cipher suite, report an error to the user */
    TcpIp_TlsUserErrorType userError;
    userError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLO;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_NOMATCHINGCIPHER;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_INSUF_SEC);
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloMsgGetCipherSuite() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod =
    TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select the corresponding handshake reference, depending on the selected key exchange method */
  switch (keyExchangeMethod)
  {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
    case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
    {
      /* There is no support for multiple HS references in case of ECDH or PSK - select the default (first) handshake reference */
      TcpIp_TlsMsg_SelectDefaultHandshakeReference(TlsConIdx);
      break;
    }
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:

    {
      /* Selection of correct TlsHandshake container depending on the received curve in the KeyExchange message
         is done in TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId() */
      break;
    }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
    default:
    {
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      break;
    }
  }  /* switch (keyExchangeMethod) */

} /* TcpIp_TlsClientMsg_ServerHelloMsgSelectHandshakeReference() */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx   = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType                retVal             = E_OK;
  uint16                        compMethodSelected;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the received compression method */
  compMethodSelected = IpBase_GetUint8(
    TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  /* and increment the read index by the length of the compression method field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_COMPMETHLEN_LEN);

  /* #10 Check if the received compression method is valid. Only 'no_compression (0)' method is supported */
  if(compMethodSelected != TCPIP_TLS_COMPRESSION_METHOD_NONE)
  {
    /* #20 otherwise, incorrect compression method received - Report an error to the user */
    TcpIp_TlsUserErrorType userError;
    userError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLO;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCOMPMETHOD;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloMsgGetCompressionMethod */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloGetExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloGetExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType  HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType currentRxAdHsBufReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received TLS Hello-Extensions and parse them */
  if (currentRxAdHsBufReadIdx == HelloEndIdx)
  {
    /* No extensions have been detected */
    retVal = E_OK;
  }
  else
  {
    /* Extensions present, parse them */
    retVal = TcpIp_TlsClientMsg_ServerHelloCheckExtensions(TlsConIdx, HelloEndIdx);
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloGetExtensions() */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloCheckExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloCheckExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType   HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType currentRxAdHsReadIdx = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType                retVal;
  uint16                        extensionsLen;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Extract the length of the extensions field */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(currentRxAdHsReadIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN, HelloEndIdx))
  {
    extensionsLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(currentRxAdHsReadIdx), 0);
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN);

    /* #20 If extensions present, process each extension iteratively */
    if (extensionsLen != 0u)
    {
      /* Iterate over the extension data and extract extension(s) */
      retVal = TcpIp_TlsClientMsg_ServerHelloParseAndValidateExtensions(TlsConIdx, extensionsLen, HelloEndIdx);
    }
    else
    {
      /* No extensions present, return E_OK */
      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloCheckExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloParseAndValidateExtensions
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
 */
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050, MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseAndValidateExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16                      ExtensionsLen,
  TcpIp_TlsBufferRxIterType   HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsExtensionType listOfReceivedExtensions[TCPIP_TLS_MAX_EXTENSION_LIST_LENGTH] = { 0 };
  uint8 overallNumberOfReceivedExtensions = 0u;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received extension length is in range of the TLS RxBuffer */
   if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
     (TcpIp_TlsBufferRxIterType)ExtensionsLen, HelloEndIdx))
   {
     /* #20 Iterate over the extension data and extract each extension into overall list of received extensions */
     if (TcpIp_TlsHelloMsg_ExtractReceivedExtensions(TlsConIdx, ExtensionsLen, HelloEndIdx,
           &listOfReceivedExtensions[0], &overallNumberOfReceivedExtensions)== E_OK)
     {
       /* #30 Check for duplicated received extensions */
       if (TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions(&listOfReceivedExtensions[0],
             overallNumberOfReceivedExtensions) == E_OK)
       {
         /* #40 Compare received extensions with the sent one in the ClientHello message */
         if (TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions(TlsConIdx, &listOfReceivedExtensions[0],
               overallNumberOfReceivedExtensions) == E_OK)
         {
           /* #50 Parse received extensions */
           if (TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions(TlsConIdx, &listOfReceivedExtensions[0],
                 overallNumberOfReceivedExtensions) == E_OK)
           {
             /* #60 All extension fully validated and parsed - return E_OK */
             /* Note: At this point we do not check if we receive all mandatory extension.
              * This is done in the context of the ServerHelloDone (due to the Validation callback to the upper layer) */
             retVal = E_OK;
           }
         }
         else
         {
           /* Unknown received extension - Trigger alert */
           TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNSUP_EXT);
         }
       }
       else
       {
         /* Duplicated received extension - Trigger alert */
         TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
       }
     }
     else
     {
       /* Invalid formatted received extension - Trigger alert */
       TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
     }
   }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloParseAndValidateExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxClientExtensionsIdxOfTlsClientBufferMgmtType transmittedExtensionLengthIdx =
    TcpIp_GetTlsBufferTxClientExtensionsIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferTxClientExtensionsIdxOfTlsClientBufferMgmtType transmittedExtensionStartIdx =
    transmittedExtensionLengthIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;

  uint8 rxExtensionIter;
  uint16 transmittedExtensionTotalLength;

  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* RFC3456 - 2.3. Hello Extensions */
  /* If a client receives an extension type in ServerHello that it did not
     request in the associated ClientHello, it MUST abort the handshake */

  /*
  *   Extension Layout in Tls TxBuffer:
  *
  *         (fix) +-> transmittedExtensionLengthIdx
  *              /     (change per iteration:)
  *             /            +-> currentTransmittedExtensionType
  *            /            /          +-> currentTransmittedExtensionLength
  *           /            /          /
  *          [FullExtLen] [extType_1][extLen_1][extData_1] [extType_2][extLen_2][extData_2] ...
  *   Bytes:      2           2          2         n           2         2          n
  *   Iter:               ^
  *                       |
  *                       +---> txExtensionOffsetIter
  */

  transmittedExtensionTotalLength = IpBase_GetUint16(TcpIp_GetAddrTlsBufferTx(transmittedExtensionLengthIdx), 0);

  /* #10 Iterate over all received server extensions */
  for (rxExtensionIter = 0; rxExtensionIter < ReceivedExtensionCnt; rxExtensionIter++)
  {
    /* Reset Iter and flag per round */
    uint16 txExtensionOffsetIter = 0u;
    boolean isRxExtensionPresentInTxExtensions = FALSE;

    /* Get the next received extension type */
    uint16 currentReceivedExtensionType = ReceivedExtensionListPtr[rxExtensionIter].Type;

    /* #20 Iterate over all transmitted client extension */
    while (txExtensionOffsetIter < transmittedExtensionTotalLength)
    {
      /* Extract the type of the iterated transmitted extension */
      uint16 currentTransmittedExtensionType = IpBase_GetUint16(TcpIp_GetAddrTlsBufferTx(
        transmittedExtensionStartIdx + txExtensionOffsetIter), 0);

      /* Extract the length of the iterated transmitted extension */
      uint16 currentTransmittedExtensionLength = IpBase_GetUint16(TcpIp_GetAddrTlsBufferTx(
        transmittedExtensionStartIdx + TCPIP_TLS_EXTENSION_TYPE_LEN + txExtensionOffsetIter), 0);

      /* Increment the iterator by the consumed type length (2 bytes) */
      txExtensionOffsetIter += TCPIP_TLS_EXTENSION_TYPE_LEN;
      /* Increment the iterator by the consumed length field length (2 bytes) */
      txExtensionOffsetIter += TCPIP_TLS_EXTENSION_LENGTH_LEN;
      /* Increment the iterator by the consumed data length (n bytes ) */
      txExtensionOffsetIter += currentTransmittedExtensionLength;
      /* next round of loop the txExtensionOffsetIter is directing to the next transmitted extension type */

      /* #30 Compare the current received extension against the transmitted extension */
      /* Compare extension type */
      if (currentReceivedExtensionType == currentTransmittedExtensionType)
      {
        /* #40 Extension is present in transmitted ClientHello message */
        isRxExtensionPresentInTxExtensions = TRUE;
        /* Skip all other transmitted extension and continue with the next received one */
        break;
      }
    }

    if (isRxExtensionPresentInTxExtensions == FALSE)
    {
      /* #50 if one received extension is not present - return E_NOT_OK */
      retVal = E_NOT_OK;
      /* Since one received Extension is NOT present in the transmitted extensions, we can skip the others at this point */
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloCompareAgainstTransmittedExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions
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
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 rxExtensionIter;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all received server extensions */
  for (rxExtensionIter = 0u; rxExtensionIter < ReceivedExtensionCnt; rxExtensionIter++)
  {
    /* Get the next received extension type and parse it depending on the type */
    uint16 currentReceivedExtensionType = ReceivedExtensionListPtr[rxExtensionIter].Type;

    switch (currentReceivedExtensionType)
    {
      case TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS:
      {
        /* RFC8422 - 5.2.  Server Hello Extension

           RFC defines only one ec extension which MUST be received by the client which is ec_point_Formats (11).
           Therefore the elliptic_curves(10) Supported Elliptic Curves Extension is not allowed to be sent by the server */

        /* #20 In case of extension type elliptic_curves(10) - return E_NOT_OK */
        retVal = E_NOT_OK;
        break;
      }
      case TCPIP_TLS_EXTENSION_EC_POINT_FORMAT:
      {
        /* #30 In case of extension type ec_point_formats(11) - forward to specific parser */
        retVal = TcpIp_TlsClientMsg_ServerHelloParseExtensionEcPointFormat(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS:
      {

        /* RFC5246 - 7.4.1.4.1.  Signature Algorithms
           RFC8422 - 5.1.3.  The signature_algorithms Extension and EdDSA

           Servers MUST NOT send this extension. */

        /* #40 In case of extension type signature_algorithms(13) - return E_NOT_OK */
        retVal = E_NOT_OK;
        break;
      }

      case TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST:
      {
        /* #50 In case of extension type certificate_status_request(5) - forward to specific parser */
        retVal = TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }


      default:
      {
        retVal = E_NOT_OK;
        break;
      }
    }

    /* #60 if parsing of one extension fails - trigger alert and return E_NOT_OK */
    if (retVal != E_OK)
    {
      /* Unknown received extension - Trigger alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNSUP_EXT);

      /* Skip parsing of all other received extensions */
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloParseReceivedExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloParseExtensionEcPointFormat
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseExtensionEcPointFormat(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType EcPointFormatExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 ecPointFormatIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* RFC8422 - 5.2.  Server Hello Extension ec_point_Formats (11)(Supported Point Formats Extension)

    The server's Supported Point Formats Extension has the same structure
    as the client's Supported Point Formats Extension (see
    Section 5.1.2).  Items in ec_point_format_list here are ordered
    according to the server's preference (favorite choice first).  Note
    that the server MAY include items that were not found in the client's
    list.  However, without extensions, this specification allows exactly
    one point format, so there is not really any opportunity for
    mismatches.

  */
  /* Supported Point Formats Extension Format
                                +----> Length
                               /                          +--->  ordered values
                              /                          /
  *       [ext Type][ext Len][EC Point Format Len][EC Point Format_1][EC Point Format_2]...
  * Byte: 0       1 2      3                    4                   5                  6
  */
  uint8 ecPointFormatLen = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(EcPointFormatExtension.StartIdx), 0);

  /* #10 Process received list only if the length match */
  if (   ( ecPointFormatLen != 0u) /* We MUST received at least one point format */
      && ((ecPointFormatLen + TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_LENGTH_LEN) == (uint8)EcPointFormatExtension.Length))
  {
    /* #20 Iterate over (possible) list of received ec Point formats and check if it contains the UNCOMPRESSED format */
    for (ecPointFormatIter = 0u; ecPointFormatIter < ecPointFormatLen; ecPointFormatIter++)
    {
      uint8 ecPointFormat = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
        EcPointFormatExtension.StartIdx + TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_FIXED_LENGTH + ecPointFormatIter), 0);

      /* TLS-Client only support uncompressed formats */
      if (ecPointFormat == TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_UNCOMPRESSED)
      {
        /* #30 List contains uncompressed formats - skip all other items in list and return E_OK */
        retVal = E_OK;
        break;
      }
    }
  }
  else
  {
    /* #40 Received length mismatch - report TLS-Alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType CertificateStatusRequest)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* RFC6066 - 8.  Certificate Status Request
       If a server returns a "CertificateStatus" message, then the server MUST have included an
       extension of type "status_request" with empty "extension_data" in the extended server hello. */

  /* #10 Check the received extension type and length */
  if (    (CertificateStatusRequest.Type == TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST)
       && (CertificateStatusRequest.Length == 0u))
  {
    /* Mandatory extension certificate status request received - reset the flag */
    TcpIp_SetMandatoryReceivedCertificateStatusRequestExtensionOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* The client expects a ServerCertficateStatus message after the certificate - used during HsStm state */
    TcpIp_SetExpectServerCertificateStatusMessageOfTlsConnectionDyn(TlsConIdx, TRUE);

    retVal = E_OK;
  }
  /* received Type already checked by caller function */

  return retVal;
} /* TcpIp_TlsClientMsg_ServerHelloParseExtensionCertificateStatusRequest() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloDetermineNextState
 *********************************************************************************************************************/
/*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloDetermineNextState(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod
    = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine next handshake state depending on key exchange mode */
  switch (keyExchangeMethod)
  {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
      /* #20 in case of ECDHE or ECDH we expect a Server Certificate. */
      *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE;

      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
        TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_DONE);
      break;
    }
#  endif
    case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
    {
      /* #30 in case of PSK, we have to switch the state depending on the received next server message */
      TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk(TlsConIdx, NextStatePtr);
      break;
    }
    default:
    {
      /* #40 otherwise, invalid key exchange method. */
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      break;
    }
  }  /* switch (keyExchangeMethod) */

} /* TcpIp_TlsClientMsg_ServerHelloDetermineNextState() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk
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
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeIdx
    = TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmtType serverCertificateIdx
    =TcpIp_GetTlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneIdx
    = TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Reset the context state - in case we did not receive the next message, this will be overwritten to WAIT_CYCLE */
  /* If the next message is received, we must reset it to NO_ASYNC */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 check if we already receive the next messages (ServerKeyExchange or ServerHelloDone or ServerCertificate)
         and set the next TLS-Handshake state */
  if (serverCertificateIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESIDXOFTLSCLIENTBUFFERMGMT)
  {
    /* #20 if a ServerCertificate message is received we have to trigger a TLS alert because PSK do not support
           Certificate handling */

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);

    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

  }
  else if (   (serverKeyExchangeIdx == TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
           && (serverHelloDoneIdx   == TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT))
  {
    /* #30 if no message is received yet, wait until next main function */
    /* Neither the ServerCertificate, ServerKeyExchange message nor the ServerHelloDone message are received,
     *  so we can not determine the next state.
     * Wait until next main function cycle to determine next state */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
  }
  else if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
  {
    /* #40 if we receive a ServerKeyExchange (PSK hint), so we have to process this message */
    *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE;

    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
      TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_DONE);
  }
  else /* No ServerKeyExchange but ServerHelloDone */
  {
    /* #50 We receive at least a ServerHelloDone, so next state is TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE */
    *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE;

    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
      TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_DONE);
  }
} /* TcpIp_TlsClientMsg_ServerHelloDetermineNextStatePsk() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerCertificate
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmtType serverCertificateIdx =
    TcpIp_GetTlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a message with the TLS-Handshake type ServerCertificate */
  if (serverCertificateIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_HANDSHAKE_INIT;
    Std_ReturnType retVal;

    /* #20 if so, extract the information inside the server certificate message */
    retVal = TcpIp_TlsClientMsg_ExtractServerCertificateInformation(TlsConIdx, &nextState);

    /* #30 Check return value from extract function and switch to next state */
    if (retVal == E_OK)
    {
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_WAIT_CYCLE)
      {
        /* Next logical HS message not received yet, wait one cycle and try again */
        /* Reset wait cycle for next iteration */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
      }
      else
      {
        /* The certificate chain is read from the certificate message and verified by the KeyM. */

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }

    }
    else
    {
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #40 otherwise, we received an unexpected message. Trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerCertificate() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractServerCertificateInformation
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
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerCertificateInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the message ServerCertificate until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE)  /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            /* Handshake is not aborted due to processing error */
         && (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_HANDSHAKE_ABORT)
            /* Async operation is pending */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
            /* Next state could not be determine (missing next HS message) - Wait cycle */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_WAIT_CYCLE)
            /* Error during parsing - abort next steps */
         && (retVal == E_OK))
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE:
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_LOADCERTS:
      {
        /* #20 Extract the certificates from the received chain, store them in the KeyM, and trigger KeyM to verify the cert group */
        retVal = TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_CHECK);
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_CHECK:
      {
        /* #30 Periodically check if KeyM has finished the cert chain validation */
        if (KeyM_Cert_IsBusy() == TRUE)
        {
          /* The KeyM is still busy to process the cert chain validation */
          /* do nothing, just wait for next main function */
          TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
        }
        else
        {
          /* The cert chain validation has been finished by the KeyM. Now check the result and calculate an overall status. */
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_STATUS);
        }
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_STATUS:
      {
        /* #40 The cert chain validation has been finished by the KeyM. Now check the result and calculate an overall status. */
       retVal =  TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup(TlsConIdx);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DETERMINE_NEXT_STATE);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DETERMINE_NEXT_STATE:
      {
        /* #50 Determine the next valid TLS handshake state */
        /* This state could be a WAIT_CYCLE if the next logical TLS message is not received yet */
        TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState(TlsConIdx, NextStatePtr);
        break;
      }

      default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        break;
      } /* default */
    } /* switch() */

  } /* while() */

  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerCertificateInformation() */


/**********************************************************************************************************************
 *  TcpIp_TlsClientGetNumOfCertificates
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientGetNumOfCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      CertStartIdx,
  uint32                      CertChainLen,
  TCPIP_P2V(uint8)            NumCertPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          numCert     = 0u;
  uint32         certBytes   = 0u;
  uint32         certReadIdx = CertStartIdx;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_SizeOfTlsClientBufferMgmtType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType tlsBufferRxAdHsEndIdx
    = TcpIp_GetTlsBufferRxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Traverse through the received chain and count number of certificates */
  while (certBytes < CertChainLen)
  {
    /* Extract length of the current certificate */
    /* Check if the length of the certificate length fits into the TLS RxBuffer */
    if (   TCPIP_TLS_RXBUFFER_ISIDXINRANGE(certReadIdx,
             TCPIP_TLS_CERT_LEN,
             tlsBufferRxAdHsEndIdx)
      /* Check that the received certificate length is greater then the expected length */
        && (TcpIp_GetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
           >= (certBytes + TCPIP_TLS_CERT_LEN + TCPIP_TLS_CERT_LEN + TCPIP_TLS_HSHDRLEN)))
    {
      uint32 certLength = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx((uint16)certReadIdx), 0);
      /* Increase by length of the current certificate */
      certBytes += certLength + TCPIP_TLS_CERT_LEN;
      /* Increment read index by size of certificate and the length of certLen field */
      certReadIdx += certLength + TCPIP_TLS_CERT_LEN;
      numCert++;
    }
    else
    {
      break;
    }
  }

  if ((CertChainLen == 0u) || (certBytes != CertChainLen))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
    *NumCertPtr = numCert;
  }

  return retVal;
} /* TcpIp_TlsClientGetNumOfCertificates */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_SizeOfTlsClientBufferMgmtType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType tlsBufferRxAdHsEndIdx
    = TcpIp_GetTlsBufferRxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  Std_ReturnType retVal = E_NOT_OK;
  uint32 certificatesLength;
  uint8 numCerts = 0;

  /* ----- Implementation ----------------------------------------------- */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
        TCPIP_TLS_CERTSLEN_LEN, tlsBufferRxAdHsEndIdx)
     && (TcpIp_GetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) >= (TCPIP_TLS_CERT_LEN + TCPIP_TLS_HSHDRLEN)))
  {
    /* Read the length of the certificate chain */
    certificatesLength = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx(
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CERTSLEN_LEN);

    /* Check whether the length of the certificate chain and the length of the length field add up to the length of the messsage */
    if (   (certificatesLength + TCPIP_TLS_CERT_LEN)
        == TcpIp_GetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx))
    {
      /* #10 Get number of received certificates and extract the certificate data */
      if (TcpIp_TlsClientGetNumOfCertificates(TlsConIdx, TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
            certificatesLength, &numCerts) == E_OK)
      {
        /* Extract the certificates from the received chain and store them in the KeyM */
        retVal = TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification(TlsConIdx,
          TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), numCerts);

        /* #20 Update the read index */
        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (uint16)certificatesLength);
      }
    }
  }

  if(retVal != E_OK)
  {
    /* #30 Extraction of server certificates failed, report user error */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERCERT;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTHSMSG;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    /* Trigger alert protocol_version in case of invalid length of certificate */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertMsgProcessCertChain */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification(
  TcpIp_TlsConnectionIterType         TlsConIdx,
  TcpIp_TlsBufferRxIterType           CertStartIdx,
  uint8                               NumCerts)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType certReadIdx = CertStartIdx;
  Std_ReturnType retVal = E_NOT_OK;
  uint8                     certIter;
  TcpIp_TlsCertValidationStatusDynStartIdxOfTlsConnectionType certStatusIdx
                                               = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ---------------------------------------------- */
  TCPIP_ASSERT(NumCerts <= (TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx) - TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx)));

  /* #10 Iterate through all the certificates in the received chain */
  for (certIter = 0; certIter < NumCerts; certIter++)
  {
    uint32                   certLength = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx(certReadIdx), 0);
    TcpIp_CertDataType       certData;
    TcpIp_CertificateIdType  certId = TCPIP_CERTID_INV;

    /* #20 Extract the current certificate information */
    TcpIp_TlsClientMsg_ExtractNextServerCertificate(certReadIdx, &certData);

    /* #30 Check if the cert groupId has been set */
    if (TcpIp_GetHsCertGroupIdOfTlsConnectionDyn(TlsConIdx) == TCPIP_CERTGROUPID_INV)
    {
      TcpIp_CertificateGroupIdType groupId = TCPIP_CERTGROUPID_INV;

      /* #40 Determine the remote certificate group Id and set the leaf certificate Id */
      if (TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo(TlsConIdx, &certData, &groupId, &certId) == E_OK)
      {
        retVal = E_OK;

        /* #50 Set the GroupId and leaf certId for the current Handshake */
        TcpIp_SetHsCertGroupIdOfTlsConnectionDyn(TlsConIdx, groupId);
        TcpIp_SetHsLeafCertIdOfTlsConnectionDyn(TlsConIdx, certId);
      }
      else
      {
        /* #60 No valid certificate group available */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* #70 Remote certificate group Id is known, set the intermediate certificate if available */
      if (KeyM_SetCertificateInGroup(TcpIp_GetHsCertGroupIdOfTlsConnectionDyn(TlsConIdx), certData.certData, certData.certDataLength, &certId) == E_OK)
      {
        /* Certificate loaded successfully, continue loading next certificate */
        retVal = E_OK;
      }
      else
      {
        /* Certificate could not be loaded successfully */
        retVal = E_NOT_OK;
      }
    }
    /* Break if error occurred. */
    if (retVal == E_NOT_OK)
    {
      break;
    }

    /* Certificate has been loaded, update the cert struct with the certificate Id */
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertId = certId;

    /* Increment the cert status idx and the valid Idx */
    certStatusIdx++;

    /* Increment readIdx */
    certReadIdx += (TcpIp_TlsBufferRxIterType) certLength + TCPIP_TLS_CERT_LEN;
  }

  /* Update the valid end idx of the cert chain struct to last certificate loaded */
  TcpIp_SetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx, certStatusIdx);

  /* #80 If all certificates were successfully extracted and loaded, trigger verification of the leaf certificate */
  if (retVal == E_OK)
  {
    if (KeyM_VerifyGroup(TcpIp_GetHsCertGroupIdOfTlsConnectionDyn(TlsConIdx)) == E_OK)
    {
      /* Update Hs certificate state to in progress */
      /* [HS Server Certificate Chain Handling StM] Certificates loaded successfully and verification triggered  */
      TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_IN_PROGRESS);
    }
    else
    {
      /* Verification failed - one reason may be Root or intermediate certificate not found, or KeyM is busy */
      /* Update Hs certificate state to finished as no further certificate processing will be done */
      /* [HS Server Certificate Chain Handling StM] Certificates loaded successfully and but verification failed */
      TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_VERIFY_FAILED);

      /* Trigger alert. Either no matching root cert was found, or cert chain is not consistent in itself. */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNKNOWN_CA);

      /* Update status for certificate chain. Ignore return value because we know that the chain is invalid and the
         handshake will be canceled anyway. */
      (void)TcpIp_TlsClient_TlsUpdateCertChainStatus(TlsConIdx, TCPIP_TLS_UPDATE_CERT_MODE_CHAIN);

      TcpIp_SetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_VALIDATION_NOT_OK);

      /* Issue validation callback */
      TcpIp_TlsClient_TlsCertChainTriggerValidationCallback(TlsConIdx, FALSE);

      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertMsgParseAndTriggerVerification */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractNextServerCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractNextServerCertificate(
  TcpIp_TlsBufferRxIterType           CertStartIdx,
  TCPIP_P2V(TcpIp_CertDataType)       CertDataPtr
  )
{
  /* ----- Implementation ---------------------------------------------- */
  /* #10 Load the certificate into the KeyM struct */
  CertDataPtr->certDataLength = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx(CertStartIdx), 0);
  CertDataPtr->certData       = TcpIp_GetAddrTlsBufferRx(CertStartIdx + TCPIP_TLS_CERT_LEN);
} /* TcpIp_TlsClientMsg_ExtractNextServerCertificate */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  TCPIP_P2C(TcpIp_CertDataType)            Certificate,
  TCPIP_P2V(TcpIp_CertificateGroupIdType)  CertGroupIdSelectedPtr,
  TCPIP_P2V(TcpIp_CertificateIdType)       CertIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                      retVal = E_NOT_OK;
  TcpIp_CertificateGroupIdType        groupId;
  TcpIp_CertificateIdType             certId;
  TcpIp_TlsRemoteKeyMCertInfoIterType tlsRemoteKeyMCertInfoIdx;

  /* ----- Implementation ---------------------------------------------- */
  /* #10 Iterate over all certInfos attached to the connection */
  for (tlsRemoteKeyMCertInfoIdx = TcpIp_GetTlsRemoteKeyMCertInfoStartIdxOfTlsConnection(TlsConIdx);
       tlsRemoteKeyMCertInfoIdx < TcpIp_GetTlsRemoteKeyMCertInfoEndIdxOfTlsConnection(TlsConIdx);
       tlsRemoteKeyMCertInfoIdx++)
  {
    groupId = TcpIp_GetCertGroupIdOfTlsRemoteKeyMCertInfo(tlsRemoteKeyMCertInfoIdx);
    /* #20 Try setting the received certificate into the group */
    if (KeyM_SetCertificateInGroup(groupId, Certificate->certData, Certificate->certDataLength, &certId) == E_OK)
    {
      /* #30 If setting successful, return groupId and certId */
      retVal = E_OK;
      *CertGroupIdSelectedPtr = groupId;
      *CertIdPtr              = certId;
      break;
    }
  }

  /* #40 Set the certId and groupId to invalid if retVal is not set */
  if (retVal == E_NOT_OK)
  {
    *CertGroupIdSelectedPtr = TCPIP_CERTGROUPID_INV;
    *CertIdPtr              = TCPIP_CERTID_INV;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_LoadLeafCertAndUpdateCertInfo */

/**********************************************************************************************************************
*  TcpIp_TlsClient_TlsUpdateOverallCertValidationResult
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsUpdateOverallCertValidationResult(
  TcpIp_TlsConnectionIterType                TlsConIdx,
  TCPIP_P2V(TcpIp_CertValidationResultType)  CertValidResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Number of invalid certificates in the certificate chain */
  uint8 invalidCertCnt = 0u;
  /* Iterator for certificate status struct */
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;
  boolean selfSignedRootPresent = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx)
    <= TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx));

  /* Overall validation result is unknown at this point */
  *CertValidResultPtr = TCPIP_TLS_VALIDATION_UNKNOWN;

  /* #10 Iterate over all the certificate status and provide an overall validation result */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);
       certStatusIdx < TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx);
       certStatusIdx++)
  {
    /* Check if any received certificate is a self-signed root */
    if (TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->IsSelfSigned == TRUE)
    {
      selfSignedRootPresent = TRUE;
    }

    /* Process the current certificate status */
    switch (TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatus)
    {
      case KEYM_CERTIFICATE_VALID:
      {
        /* This status implies certificate is valid */
        break;
      }
      case KEYM_CERTIFICATE_PARSED_NOT_VALIDATED:
      {
        /* Certificate is not validated. Probably this is because an other one is recognized as not valid, and the
        further certificates were not processed any more. At least one other certificate will have a more 'advanced' state. */
        break;
      }
      case KEYM_CERTIFICATE_INVALID:
      case KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL:
      case KEYM_E_CERTIFICATE_SIGNATURE_FAIL:
      case KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST:
      case KEYM_E_CERTIFICATE_INVALID_TYPE:
      case KEYM_E_CERTIFICATE_INVALID_FORMAT:
      case KEYM_E_CERTIFICATE_INVALID_CONTENT:
      case KEYM_E_CERTIFICATE_REVOKED:
      default:
      {
        /* These status implies certificate is invalid */
        invalidCertCnt++;
        break;
      }
    } /* switch() */
  } /* for() */

  /* #20 Determine overall validation status */
  if ((invalidCertCnt != 0u) || (selfSignedRootPresent == TRUE))
  {
    /* If invalid certificates present or self-signed root is present, fail the validation */
    *CertValidResultPtr = TCPIP_TLS_VALIDATION_NOT_OK;
  }
  else
  {
    *CertValidResultPtr = TCPIP_TLS_VALIDATION_OK;
  }

} /* TcpIp_TlsClient_TlsUpdateOverallCertValidationResult() */


/**********************************************************************************************************************
 *  TcpIp_TlsClient_TlsGetAlertForBadCertificateChain
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForBadCertificateChain(
  TcpIp_TlsConnectionIterType                TlsConIdx,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType)   AlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Iterator for certificate status struct */
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;
  TcpIp_TlsAlertDescriptionType  alert = TCPIP_TLS_ALERT_UNSET;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx)
    <= TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx));

  /* #10 Iterate over all the certificate status and determine an alert description */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);
       certStatusIdx < TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx);
       certStatusIdx++)
  {
    /* #20 Determine alert for certificate status */
    alert = TcpIp_TlsClient_TlsGetAlertForCertificateStatus(certStatusIdx);

    /* #30 Determine alert for OCSP certificate status */
    if (alert == TCPIP_TLS_ALERT_UNSET)
    {
      alert = TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus(TlsConIdx, certStatusIdx);
    }

    /* #40 Determine alert for OCSP response status */
    if (alert == TCPIP_TLS_ALERT_UNSET)
    {
      alert = TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus(TlsConIdx, certStatusIdx);
    }

    /* If a valid alert set, stop processing further */
    if (alert != TCPIP_TLS_ALERT_UNSET)
    {
      break;
    }
  } /* for() */

  /* #50 Check if an alert has been set and update the AlertDescriptionPtr */
  if (alert == TCPIP_TLS_ALERT_UNSET)
  {
    *AlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_CERT_UNKNOWN;
  }
  else
  {
    *AlertDescriptionPtr = alert;
  }
} /* TcpIp_TlsClient_TlsGetAlertForBadCertificateChain() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_TlsGetAlertForCertificateStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*/
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForCertificateStatus(
  TcpIp_TlsCertValidationStatusDynIterType   CertStatusIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsAlertDescriptionType localAlert = TCPIP_TLS_ALERT_UNSET;

  TCPIP_P2C(TcpIp_CertValidationStatusType) currentCertStatusPtr
    = TcpIp_GetAddrTlsCertValidationStatusDyn(CertStatusIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine alert for certificate status */
  /* Check if any received certificate is a self-signed root */
  if (currentCertStatusPtr->IsSelfSigned == TRUE)
  {
    /* Since self-signed root is present, alert is unkown_ca */
    localAlert = TCPIP_TLS_ALERT_DESC_UNKNOWN_CA;
  }
  else
  {
    /* For other certificates process the certificate status */
    switch (currentCertStatusPtr->CertStatus)
    {
      case KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL:
      {
        /* Validity period check failed, alert is certificate_expired */
        localAlert = TCPIP_TLS_ALERT_DESC_CERT_EXPIRED;
        break;
      }
      case KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST:
      {
        /* Invalid chain of trust, alert is unknown_ca */
        localAlert = TCPIP_TLS_ALERT_DESC_UNKNOWN_CA;
        break;
      }
      case KEYM_E_CERTIFICATE_REVOKED:
      {
        /* Certificate has been revoked, alert is certificate_revoked */
        localAlert = TCPIP_TLS_ALERT_DESC_CERT_REVOKED;
        break;
      }
      case KEYM_E_CERTIFICATE_SIGNATURE_FAIL:
      case KEYM_E_CERTIFICATE_INVALID_TYPE:
      case KEYM_E_CERTIFICATE_INVALID_FORMAT:
      case KEYM_E_CERTIFICATE_INVALID_CONTENT:
      {
        /* Certificate is corrupt or signature verification failed , alert is bad_certificate */
        localAlert = TCPIP_TLS_ALERT_DESC_BAD_CERT;
        break;
      }
      case KEYM_CERTIFICATE_INVALID:
      default:
      {
        /* Cannot decide alert using this status, continue and check next certificate status */
        localAlert = TCPIP_TLS_ALERT_UNSET;
        break;
      }
    } /* switch() */
  }
  return localAlert;
} /* TcpIp_TlsClient_TlsGetAlertForCertificateStatus() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsCertValidationStatusDynIterType CertStatusIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsAlertDescriptionType localAlert = TCPIP_TLS_ALERT_UNSET;

  TCPIP_P2C(TcpIp_CertValidationStatusType) currentCertStatusPtr
    = TcpIp_GetAddrTlsCertValidationStatusDyn(CertStatusIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Certificate Status Request feature is enabled */
  if (TcpIp_IsTlsUseExtensionCertificateStatusRequestOfTlsConnection(TlsConIdx) == TRUE)
  {
    /* #20 OCSP enabled, determine the alert description for the given certificate */
    if (currentCertStatusPtr->CertStatusResponse.OcspConnectionState == TCPIP_TLS_OCSP_CONNECTION_STATE_REQUESTED)
    {
      /* OCSP was requested by the TLS Client, but no OCSP Certificate Status response received */
      localAlert = TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP;
    }

    if (currentCertStatusPtr->CertStatusResponse.OcspConnectionState == TCPIP_TLS_OCSP_CONNECTION_STATE_STATUS_RECEIVED)
    {
      /* OCSP Certificate Status response received, check the state of the certificate */
      switch (currentCertStatusPtr->CertStatusResponse.OcspCertStatus)
      {
        case KEYM_E_CERTIFICATE_REVOKED:
        {
          /* Certificate is revoked via OCSP */
          localAlert = TCPIP_TLS_ALERT_DESC_CERT_REVOKED;
          break;
        }
        default:
        {
          /* No reason for alert, continue */
          localAlert = TCPIP_TLS_ALERT_UNSET;
          break;
        }
      } /* switch */
    } /* else - No OCSP response received, nothing to do */
  } /* else - OCSP not enabled, nothing to do */

  return localAlert;
} /* TcpIp_TlsClient_TlsGetAlertForOcspCertificateStatus() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(TcpIp_TlsAlertDescriptionType, TCPIP_CODE) TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsCertValidationStatusDynIterType CertStatusIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsAlertDescriptionType localAlert = TCPIP_TLS_ALERT_UNSET;

  TCPIP_P2C(TcpIp_CertValidationStatusType) currentCertStatusPtr
    = TcpIp_GetAddrTlsCertValidationStatusDyn(CertStatusIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Certificate Status Request feature is enabled */
  if (TcpIp_IsTlsUseExtensionCertificateStatusRequestOfTlsConnection(TlsConIdx) == TRUE)
  {
    /* #20 OCSP enabled, check if the OCSP Certificate Status is received */
    if (currentCertStatusPtr->CertStatusResponse.OcspConnectionState == TCPIP_TLS_OCSP_CONNECTION_STATE_STATUS_RECEIVED)
    {
      /* #30 Valid OCSP Response received, check the OCSP response status and determine the alert description for the given certificate */
      switch (currentCertStatusPtr->CertStatusResponse.OcspResponseStatus)
      {
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_MALFORMEDREQUEST:
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_INTERNALERROR:
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_TRYLATER:
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_SIGREQUIRED:
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_UNAUTHORIZED:
        case TCPIP_TLS_OCSP_RESPONSE_STATUS_INVALID:

        {
          /* Certificate is revoked via OCSP */
          localAlert = TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP;
          break;
        }
        default:
        {
          /* TCPIP_TLS_OCSP_RESPONSE_STATUS_SUCCESSFUL */
          /* No reason for alert, continue and check next certificate status */
          localAlert = TCPIP_TLS_ALERT_UNSET;
          break;
        }
      } /* switch */
    } /* else - No OCSP response received, nothing to do */
  } /* else - OCSP not enabled, nothing to do */

  return localAlert;
} /* TcpIp_TlsClient_TlsGetAlertForOcspResponseStatus() */

/**********************************************************************************************************************
*  TcpIp_TlsClient_TlsUpdateCertChainStatus
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
*/
/* PRQA S 6030, 6050, 6080 1 */ /* MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClient_TlsUpdateCertChainStatus(
  TcpIp_TlsConnectionIterType           TlsConIdx,
  TcpIp_Tls_CertStatusUpdateModeType   CertStatusUpdateMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_CertificateIdType issuerCertId;
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;

  TcpIp_CertificateIdType leafCertId
    = TcpIp_GetHsLeafCertIdOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal = E_OK;

  TCPIP_ASSERT(TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx)
    <= TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all the received certificates and update the current status */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);
       certStatusIdx < TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx);
       certStatusIdx++)
  {
    /* Pointer to the certificate status struct */
    TCPIP_P2V(TcpIp_CertValidationStatusType)  certStatusPtr = TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx);

    if (CertStatusUpdateMode == TCPIP_TLS_UPDATE_CERT_MODE_CHAIN)
    {
      /* #20 Retrieve the current KeyM status of the certificate */
      if (KeyM_CertGetStatus(certStatusPtr->CertId, &(certStatusPtr->CertStatus)) != E_OK)
      {
        certStatusPtr->CertStatus = KEYM_CERTIFICATE_NOT_AVAILABLE;
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* #30 Check if the Certificate Status Request feature is enabled */
      if (TcpIp_IsTlsUseExtensionCertificateStatusRequestOfTlsConnection(TlsConIdx) == TRUE)
      {
        /* OCSP is currently only implemented for leaf server certificate (RFC6066 TLS Single Certificate Status Request) */
        if (certStatusPtr->CertId == leafCertId)
        {
          /* #40 OCSP enabled, check if the OCSP Certificate Status is received */
          if (certStatusPtr->CertStatusResponse.OcspConnectionState == TCPIP_TLS_OCSP_CONNECTION_STATE_STATUS_RECEIVED)
          {
            /* #50 Update OCSP information which are then provided to upper layer via validation callback */
            TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
              = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

            TcpIp_ReceivedOcspResponseStatusOfTlsClientConnectionType receivedOcspResonseStatus
              = TcpIp_GetReceivedOcspResponseStatusOfTlsClientConnection(tlsClientConnectionIdx);

            /* Retrieve the current KeyM OCSP status of the certificate */
            if (KeyM_CertGetStatus(certStatusPtr->CertId, &(certStatusPtr->CertStatusResponse.OcspCertStatus)) != E_OK)
            {
              certStatusPtr->CertStatusResponse.OcspCertStatus = KEYM_CERTIFICATE_NOT_AVAILABLE;
              retVal = E_NOT_OK;
            }
            /* Update OCSP Response Status information for Leaf certificate */
            certStatusPtr->CertStatusResponse.OcspResponseStatus = receivedOcspResonseStatus;

          } /* else - No OCSP response received, nothing to do */
        } /* else - other then leaf certificate, nothing to do */
      } /* else - OCSP not enabled, nothing to do */
    }

    /* #60 Check if the current certificate is a self-signed root certificate */
    if (KeyM_GetIssuerCertId(certStatusPtr->CertId, &issuerCertId) == E_OK)
    {
      if (issuerCertId == certStatusPtr->CertId)
      {
        certStatusPtr->IsSelfSigned = TRUE;
      }
    }
    else
    {
      /* Trigger alert. Either no matching root cert was found, or cert chain is not consistent in itself. */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNKNOWN_CA);

      retVal = E_NOT_OK;
    }

    /* Break execution in case of failure */
    if (retVal == E_NOT_OK)
    {
      /* Reset the certificate status since it could not be set successfully */
      certStatusPtr->IsSelfSigned = FALSE;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsClient_TlsUpdateCertChainStatus() */

/**********************************************************************************************************************
*  TcpIp_TlsClient_TlsCertChainTriggerValidationCallback
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_TlsCertChainTriggerValidationCallback(
  TcpIp_TlsConnectionIterType                 TlsConIdx,
  boolean AllowOverrule)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Socket owner */
  TcpIp_SizeOfSocketOwnerConfigType  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx);

  /* Socket Id */
  TcpIp_SocketIdType  socketId = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);

  /* Number of certificates in the received chain */
  TcpIp_SizeOfTlsCertValidationStatusDynType  numCerts =
    TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx) - TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);

  /* Overall Validation result of the certificate chain */
  TcpIp_CertValidationResultType  validationResult = TcpIp_GetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx);

  /* Start Idx of the certificate status structure */
  TcpIp_TlsCertValidationStatusDynIterType certStatusStartIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If configured, notify socket owner about the certificate validation result. The socket owner can change the validation result. */
  if (TcpIp_GetTlsValidationResultFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
  {
    TcpIp_GetTlsValidationResultFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId,                                 /* SBSW_TCPIP_SocketOwnerFuncPtr_2 */
      numCerts, TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusStartIdx), &validationResult);
  }

  /* #20 Check if the socket owner overruled the result even if it was not allowed. */
  if ((AllowOverrule == FALSE) && (validationResult == TCPIP_TLS_VALIDATION_OK))
  {
    /* When overruling is not allowed, the result must always stay NOT_OK. Reset the result to NOT_OK. */
    validationResult = TCPIP_TLS_VALIDATION_NOT_OK;
  }

  /* #30 Check the validation result and proceed with finalizing handshake */
  if (validationResult == TCPIP_TLS_VALIDATION_OK)
  {
    /* #40 If certificate validation done successfully, set state to complete */
    /* [HS Server Certificate Chain Handling StM] Certificate has been validated successfully, all steps are complete */
    TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_COMPLETE);
  }
  else
  {
    TcpIp_TlsAlertLevelType  alertLevel;
    TcpIp_TlsAlertDescriptionType  alertDescription;

    /* #50 If certificate validation was unsuccessful, reset state to INIT */
    /* [HS Server Certificate Chain Handling StM] Certificate not validated successfully, reset StM */
    TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_INIT);

    /* Alert level is always set to fatal */
    alertLevel = TCPIP_TLS_ALERT_LEVEL_FATAL;
    /* Determine the appropriate alert description */
    TcpIp_TlsClient_TlsGetAlertForBadCertificateChain(TlsConIdx, &alertDescription);

    /* Trigger the transmission of the occurred alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);
  }
} /* TcpIp_TlsClient_TlsCertChainTriggerValidationCallback() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
 /* PRQA S 6050, 6080 1 */ /* MD_TcpIp_STCAL_CslAccess, MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmtType serverCertificateStatusIdx =
    TcpIp_GetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneIdx
    = TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertificateRequestIdx
    = TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeIdx
    = TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsKeyExchangeMethodDataType keyExchange =
    TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* Reset the context state - in case we did not receive the next message, this will be overwritten to WAIT_CYCLE */
  /* If the next message is received, we must reset it to NO_ASYNC */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Update the next valid TLS handshake state, depending on the active key exchange method and the received messages */
  /* This function can be called multiple times, when we do not received the next message and can not determine the valid
     next state */
  switch (keyExchange)
  {
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
      /* #20 Key exchange ECDH -> Next state could be ServerCertificateStatus or ServerHelloDone */
      if (serverCertificateStatusIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerCertificateStatus received - next state is parsing of ServerCertificateStatus */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE);
      }
      else if (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerCertificateRequest received - next state is parsing of ServerCertificateRequest */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_REQUEST;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE);
      }
      else if (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerHelloDone received and no ServerCertificateStatus - next state is parsing of ServerHelloDone */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE);
      }
      else /* if (   (serverCertificateStatusIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
                  && (serverHelloDoneIdx == TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
                  && (serverCertificateRequestIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)) */
      {
        /* ECDH - We MUST not receive a Server KeyExchange message */
        /* None of the expected messages received. Check next invalid message */
        if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
        {
          /* Invalid handshake messages received - trigger alert */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);
        }
        else
        {
          /* ServerCertificateStatus and ServerHelloDone not received yet.
           * Wait until next main function cycle to determine next state */
          TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
        }
      }

      break;
    } /* TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH */

    default:
    {
      /* #30 Key exchange ECDHE -> Next state could be ServerCertificateStatus or ServerKeyExchange */
      if (serverCertificateStatusIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerCertificateStatus received - next state is parsing of ServerCertificateStatus */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE);
      }
      else if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerKeyExchange received and no ServerCertificateStatus - next state is parsing of ServerKeyExchange */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE);
      }

      else /*  (serverCertificateStatusIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
            && (serverKeyExchangeIdx == TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
            && (serverCertificateRequestIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)) */
      {
        /* None of the expected messages received. Check next invalid message */
        if (   (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
            /* ECDHE - we MUST not receive  the Server CertificateRequest message before the Server KeyExchange message */
            || (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT))
        {
          /* Invalid order of handshake messages received - trigger alert */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);
        }
        else
        {
          /* ServerCertificateStatus and ServerKeyExchange not received yet.
           * Wait until next main function cycle to determine next state */
          TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
        }

      }
      break;
    } /* TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE */
  }

} /* TcpIp_TlsClientMsg_ServerCertificateDetermineNextHsState() */


/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerCertificateStatus
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
 */
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_STCAL_CslAccess, MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmtType serverCertificateStatusdx =
    TcpIp_GetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a message with the TLS-Handshake type ServerCertificate */
  if (serverCertificateStatusdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_HANDSHAKE_INIT;
    Std_ReturnType retVal;

    /* #20 if so, extract the information inside the server certificate message */
    retVal = TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation(TlsConIdx, &nextState);

    /* #30 Check if the parsing of the message was successful */
    if (retVal == E_OK)
    {
      /* #40 Message parsed successfully - check if the parsing is completely done and change the state */
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_WAIT_CYCLE)
      {
        /* Next logical HS message not received yet, wait one cycle and try again */
        /* Reset wait cycle for next iteration */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
      }
      else
      {
        /* #50 Parsing completely done. Change the state depending on key exchange and received messages */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }
    }
    else
    {
      /* #60 Parsing failed. Cancel the handshake. */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #70 otherwise, we received an unexpected message. Trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerCertificateStatus() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the message information until we are done, the handshake must be aborted, or the context should be switched */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)  != TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE)/* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Handshake is not aborted due to processing error */
         && (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_HANDSHAKE_ABORT)
             /* Async operation is pending */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Next state could not be determine (missing next HS message) - Wait cycle */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_WAIT_CYCLE)
             /* Error during parsing - abort next steps */
         && (retVal == E_OK))
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS:
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_GET_CERT_STATUS:
      {
        /* #20 Extract the received server certificate status information */
        retVal = TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus(TlsConIdx);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_TRIGGER_OCSP_VALIDATION);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_GET_CERT_STATUS */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_TRIGGER_OCSP_VALIDATION:
      {
        /* This operation is time consuming and thus is calculated in the lowPrio (async) task (TcpIp_TlsClientCtx_AsyncHandler).
           Trigger the calculation, leaf this context and return if the operation is done */
        /* #30 All information is parsed correctly, trigger the validation of the received OCSP response */
        TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation(TlsConIdx);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_UPDATE_CERT_STATUS);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_TRIGGER_OCSP_VALIDATION */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_UPDATE_CERT_STATUS:
      {
        /* #40 Validation of OCSP response performed - update the certificate status */
        retVal = TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus(TlsConIdx);

        /* Asynchronous validation performed, reset the connection state */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DETERMINE_NEXT_STATE);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_UPDATE_CERT_STATUS */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DETERMINE_NEXT_STATE:
      {
        /* This state could be a WAIT_CYCLE if the next logical TLS message is not received yet */
        TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState(TlsConIdx, NextStatePtr);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DETERMINE_NEXT_STATE */

      default: /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */                                                             /* COV_TCPIP_MISRA */
      {
        break;
      } /* default */

    } /* switch() */
  } /* while() */
  return retVal;

} /* TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx =
    TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType certStatusEndIdx =
    (TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) + TcpIp_GetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  uint32 expectedCertStatusLength
    = ((uint32)TcpIp_GetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) - TCPIP_TLS_HSHDRLEN);

  TcpIp_ExpectServerCertificateStatusMessageOfTlsConnectionDynType receivedServerCertStatusRequestExtension =
    TcpIp_IsExpectServerCertificateStatusMessageOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  if (receivedServerCertStatusRequestExtension == TRUE)
  {
    /* Check that we receive at least 4 byte to read out the certificate status information */
    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
      (TCPIP_TLS_CERTSTATUS_REQUESTTYPE_LEN + TCPIP_TLS_CERTSTATUS_OCSPRESPONSE_LEN),
      certStatusEndIdx))
    {
      uint8 receivedCertStatusType;
      uint32 receivedCertStatusLength;

      /* #10 Get received certificate status request type */
      receivedCertStatusType = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
        TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CERTSTATUS_REQUESTTYPE_LEN);

      /* #20 Get received certificate status request length */
      receivedCertStatusLength = IpBase_GetUint24(
        TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CERTSTATUS_OCSPRESPONSE_LEN);

      /* #30 Validate the received certificate status information */
      if (   (receivedCertStatusType == TCPIP_TLS_CERTSTATUS_REQUESTTYPE_OCSP)
          && (receivedCertStatusLength > 0u)
          && (receivedCertStatusLength == expectedCertStatusLength))
      {
        TcpIp_TlsCertValidationStatusDynStartIdxOfTlsConnectionType leafCertStatusIdx
          = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);

        TcpIp_SetServerCertStatusOcspResponseLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, receivedCertStatusLength);

        /* #40 Get the received certificate status OCSP response */
        /* Used in TcpIp_TlsClientCtx_ValidateCertificateStatus() */
        TcpIp_SetTlsBufferRxServerCertStatusOcspResponseIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
          TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
          (TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType)receivedCertStatusLength);

        /*#50 Update OCSP connection status and set the OCSP mode */
        /* We did receive the OCSP Certificate status response */
        TcpIp_GetAddrTlsCertValidationStatusDyn(leafCertStatusIdx)->CertStatusResponse.OcspConnectionState
          = TCPIP_TLS_OCSP_CONNECTION_STATE_STATUS_RECEIVED;

        /* Currently only RFC6066 TLS Single Certificate Status Request is supported */
        TcpIp_GetAddrTlsCertValidationStatusDyn(leafCertStatusIdx)->CertStatusResponse.OcspMode
          = TCPIP_TLS_OCSP_MODE_SINGLE;

        retVal = E_OK;

      }
    }
  }
  else
  {
    /* RFC6066 - 8 Certificate Status Request
     *   If a server returns a "CertificateStatus" message, then the server MUST have included an
     *   extension of type "status_request" with empty "extension_data" in the extended server hello.
     */
    /* #60 RFC violation - no status_request extension received in ServerHello - trigger Alert */
    /* User is informed via Validation callback later in the ServerHelloDone state */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertStatusGetCertStatus() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the validation of the received OCSP response in the asynchronous task */
  /* Validation performed in TcpIp_TlsClientCtx_ValidateCertificateStatus() */
  TcpIp_SetCertificateStatusOcspValidationAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ServerCertStatusTriggerOcspValidation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the certificate chain status with the OCSP result */
  if (TcpIp_TlsClient_TlsUpdateCertChainStatus(TlsConIdx,
        TCPIP_TLS_UPDATE_CERT_MODE_OCSP) == E_OK)
  {
    TcpIp_CertificateStatusResponseType leafCertificateOcspStatus;
    leafCertificateOcspStatus.OcspCertStatus     = KEYM_E_KEY_CERT_INVALID;
    leafCertificateOcspStatus.OcspMode           = TCPIP_TLS_OCSP_MODE_NONE;
    leafCertificateOcspStatus.OcspResponseStatus = TCPIP_TLS_OCSP_RESPONSE_STATUS_INVALID;


    /* #20 Read the OCSP status of the leaf certificate */
    if (TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult(TlsConIdx, &leafCertificateOcspStatus) == E_OK)
    {
      /* #30 Check if the response status was successful and update the overall validation result */
      if (leafCertificateOcspStatus.OcspResponseStatus == TCPIP_TLS_OCSP_RESPONSE_STATUS_SUCCESSFUL)
      {
        /* Update the overall validation result only if the certificate is revoked */
        if (leafCertificateOcspStatus.OcspCertStatus == KEYM_E_CERTIFICATE_REVOKED)
        {
          /* #40 Leaf certificate is revoked - Update the overall validation result */
          TcpIp_SetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_VALIDATION_NOT_OK);
        }
        else
        {
          /* Certificate is valid, do not set the validation status and return */
          retVal = E_OK;
        }
      }
      else
      {
        /* #50 Received OCSP response was not successful - Update the overall validation result */
        TcpIp_SetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_VALIDATION_NOT_OK);
      }
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertStatusUpdateCertStatus() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_CP2V(TcpIp_CertificateStatusResponseType) LeafCertStatusResponsePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_CertificateIdType leafCertId
    = TcpIp_GetHsLeafCertIdOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all received server certificates and read out the status of the leaf certificate */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);
       certStatusIdx < TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx);
       certStatusIdx++)
  {
    /* Pointer to the certificate status struct */
    TCPIP_P2C(TcpIp_CertValidationStatusType) certStatusPtr = TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx);

    if (certStatusPtr->CertId == leafCertId)
    {
      /* Leaf certificate found, store the OCSP status and indicate the caller function a successful read out */
      *LeafCertStatusResponsePtr = certStatusPtr->CertStatusResponse;

      retVal = E_OK;
      break;
    }
  }
  /* #20 else - no leaf certificate found. return E_NOT_OK */

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertStatusGetLeafOcspResult() */

/**********************************************************************************************************************
*  TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneIdx
    = TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertificateRequestIdx
    = TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeIdx
    = TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsKeyExchangeMethodDataType keyExchange =
    TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);


  /* ----- Implementation ----------------------------------------------- */

  /* Reset the context state - in case we did not receive the next message, this will be overwritten to WAIT_CYCLE */
  /* If the next message is received, we must reset it to NO_ASYNC */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Update the next valid TLS handshake state, depending on the active key exchange method and the received messages */
  /* This function can be called multiple times, when we do not received the next message and can not determine the valid
     next state */

  switch (keyExchange)
  {
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
      /* #20 Key exchange ECDH - Next state could be ServerCertificateRequest or ServerHelloDone */
      if (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerCertificateRequest received - next state is parsing of ServerCertificateRequest */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_REQUEST;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE);

      }
      else if (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerHelloDone received and no ServerCertificateStatus - next state is parsing of ServerHelloDone */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE);

      }
      else /* if (   (serverHelloDoneIdx == TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
                  && (serverCertificateRequestIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)) */
      {
        /* ServerCertificateStatus and ServerHelloDone not received yet.
         * Wait until next main function cycle to determine next state */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
      }

      break;
    } /* TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH */

    default:
    {
      /* #30 Key exchange ECDHE - Next state could be ServerKeyExchange or CertificateStatusRequest */
      if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* ServerKeyExchange received and no ServerCertificateRequest - next state is parsing of ServerKeyExchange */
        *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE;
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE);

      }
      else /*  (serverKeyExchangeIdx == TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
            && (serverCertificateRequestIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)) */
      {
        /* None of the expected messages received. Check next invalid message */
        if (   (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
            /* ECDHE - We MUST not receive the Server CertificateRequest message before the Server KeyExchange message */
            ||(serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT))
        {
          /* Invalid order of handshake messages received - trigger alert */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);
        }
        else
        {
          /* ServerCertificateStatus and ServerKeyExchange not received yet.
           * Wait until next main function cycle to determine next state */
          TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
        }
      }
      break;
    } /* TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE */
  }

} /* TcpIp_TlsClientMsg_ServerCertStatusDetermineNextHsState() */
#  endif /* (TCPIP_SUPPORT_ALSTLS_ECC == STD_ON ) */
/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_ParseServerKeyExchange
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx =
    TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeIdx =
    TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a handshake message with the type ServerKeyExchange */
  if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_HANDSHAKE_INIT;
    Std_ReturnType retVal;

    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* #20 ServerKeyExchange message received - forward the message to the parser to extract the contained information */
    retVal = TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation(TlsConIdx, &nextState);

    /* #30 Check if the parsing of the message was successful */
    if (retVal == E_OK)
    {
      /* #40 Message parsed successfully - check if the parsing is completely done and change the state */
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_WAIT_CYCLE)
      {
        /* Next logical HS message not received yet, wait one cycle and try again */
        /* Reset wait cycle for next iteration */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
      }
      else
      {
        /* #50 Parsing completely done. Change the state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }
    }
    else
    {
      /* #60 Parsing failed. Cancel the handshake. */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #70 otherwise, we received an unexpected message, trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerKeyExchange() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the message information until we are done, the handshake must be aborted, or the context should be switched */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Handshake is not aborted due to processing error */
         && (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_HANDSHAKE_ABORT)
             /* Async operation is pending */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Next state could not be determine (missing next HS message) - Wait cycle */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_WAIT_CYCLE)
             /* Error during parsing - abort next steps */
         && (retVal == E_OK))
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE:
      {
        TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE;

        /* #20 Call the subfunction to parse the received ServerKeyExchange parameters depending on the selected key exchange method */
        retVal = TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams(TlsConIdx, &nextState);
        /* Depending on keyExchange Method, next state is: TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_VERIFY_SIGNATURE | TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_GET_CLIENT_PARAMS */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_VERIFY_SIGNATURE:
      {
        /* This operation is time consuming and thus is calculated in the lowPrio (async) task.
           Trigger the calculation, leaf this context and return if the operation is done */

        /* #30 Parse the received signature */
        TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_WAIT_FOR_ASYNC);

        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_VERIFY_SIGNATURE */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_WAIT_FOR_ASYNC:
      {
        /* #40 Parsing of ServerKeyExchange message done */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE);
        break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_WAIT_FOR_ASYNC */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

      case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE:
      {
        TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState(TlsConIdx, NextStatePtr);
        /* This state could be a WAIT_CYCLE if the next logical TLS message is not received yet */
        break;
      } /* TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE */

      default: /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */                                                             /* COV_TCPIP_MISRA */
      {
        break;
      } /* default */

    } /* switch() */
  } /* while() */

  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerKeyExchangeInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 get the current key exchange method and get the server parameter depending on the key exchange mode */
  switch (keyExchangeMethod)
  {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
      /* In case of ECC, get the ECC server parameter */
      retVal = TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc(TlsConIdx);
      *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_VERIFY_SIGNATURE;
      break;
    }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
    case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
    {
      /* In case of PSK, get the PSK server parameter */
      retVal = TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk(TlsConIdx);
      *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE;
      break;
    }
    default:
    {
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      break;
    }
  }  /* switch (keyExchangeMethod) */

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParams() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchgStartIdx =
    TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerKeyExchangeLenOfTlsClientBufferMgmtType serverKeyExchangeLen =
    TcpIp_GetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeEndIdx
    = serverKeyExchgStartIdx + TCPIP_TLS_HSHDRLEN + serverKeyExchangeLen; /* End index of the received Server key exchange message - Need for in range checks inside the parser */

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Parse the received ServerKeyExchange message */
  /* Parse the Curve Info Type */
  retVal = TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType(TlsConIdx);

  /* Parse the Curve Info Id */
  retVal |= TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId(TlsConIdx);

  /* Parse the Public Key */
  retVal |= TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey(TlsConIdx, serverKeyExchangeEndIdx);

  /* Parse the Signature Algorithm */
  retVal |= TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm(TlsConIdx);

  /* Parse the Signature */
  retVal |= TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature(TlsConIdx, serverKeyExchangeEndIdx);

  /* Check if there is some more information in the buffer */
  retVal |= TcpIp_TlsMsg_CheckMsgForRemainingData(TlsConIdx, serverKeyExchangeEndIdx);

  return retVal;

} /* TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsEcc() */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk
 *********************************************************************************************************************/
/*!
  * Internal comment removed.
 *
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint16 expectedServerKeyExchangeLength
    = TcpIp_GetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType tlsBufferRxAdHsReadIdx;
  uint16 receivedPskHintLen;

  Std_ReturnType retVal     = E_NOT_OK;
  TcpIp_TlsUserErrorIdType localErrorId = TCPIP_TLS_ERRORID_NOT_SET;
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the Index to the start of the PSK Parameter */
  TcpIp_SetTlsBufferRxServerKeyExchangePskParamIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  tlsBufferRxAdHsReadIdx = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* Get the received PSK hint length */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(tlsBufferRxAdHsReadIdx,                                                           /* PRQA S 2995 3 */ /* MD_TcpIp_Tls_2995 */
      TCPIP_TLS_KEYEXCH_PSKIDLEN,
     (tlsBufferRxAdHsReadIdx + TCPIP_TLS_KEYEXCH_PSKIDLEN)))
  {
    receivedPskHintLen =
      IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

    /* and increment the read index by the length of the PSK-Hint length field */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_PSKIDLEN);

    /* Check that the received PSK length matches the expected one */
    if ((receivedPskHintLen + TCPIP_TLS_KEYEXCH_PSKIDLEN) == expectedServerKeyExchangeLength)
    {
      /* #10 Check the length of the received PSK-Hint and store the information */
      /* If a PskHint with the length 0 is received, we do not send an alert or close the connection since the RFC is not
         clear on this point. The ServerKeyExchange message is ignored but part of the TLS handshake */
      if (receivedPskHintLen <= TCPIP_TLS_KEYEXCH_PSKIDHINTMAXLEN)
      {
        /* #20 A valid PSK hint length was received, store the information */
        /* Set the received Length */
        TcpIp_SetServerKeyExchangePskHintLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, receivedPskHintLen);

        /* Set the start index of the received PSK-Hint */
        TcpIp_SetTlsBufferRxServerKeyExchangePskHintIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
          TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

        tlsBufferRxAdHsReadIdx = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

        if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(tlsBufferRxAdHsReadIdx,                                                       /* PRQA S 2995 3 */ /* MD_TcpIp_Tls_2995 */
          receivedPskHintLen,
          (tlsBufferRxAdHsReadIdx + receivedPskHintLen)))
        {
          /* and increment the read index by the length of the PSK-Hint field */
          TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, receivedPskHintLen);
          retVal = E_OK;
        }
        else
        {
          /* The received PSK length is not in range of the TLS buffer (malformed KeyExchange message) */
          localErrorId = TCPIP_TLS_ERRORID_CTHS_PSKHINTNOTINRANGE;
        }
      }
      else
      {
        /* An to large PSK hint length was received, report an error to the user */
        localErrorId = TCPIP_TLS_ERRORID_CTHS_PSKHINTTOLARGE;
      }
    }
    else
    {
      /* An incorrect PSK hint length was received, report an error to the user */
      localErrorId = TCPIP_TLS_ERRORID_CTHS_PSKHINTMSGINVALIDLENGTH;
    }
  }
  else
  {
    /* The received PSK length is not in range of the TLS buffer (malformed KeyExchange message) */
    localErrorId = TCPIP_TLS_ERRORID_CTHS_PSKHINTNOTINRANGE;
  }

  /* #30 Report error to user, error ID was set */
  if ( localErrorId != TCPIP_TLS_ERRORID_NOT_SET)
  {
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = localErrorId;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeGetServerParamsPsk() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal = E_OK;
  uint8 curveType;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetTlsBufferRxServerKeyExchangeParamsIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* Get the received curve type  */
  curveType = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  /* Increment the read index by the length of the curve type field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_CURVETYPELEN);

  /* #10 Check if the received curveType is supported. Only 'named_curve(0x03)' is supported */
  if (curveType != TCPIP_TLS_CURVETYPE_NAMED_CURVE)
  {
    /* Incorrect curve type received - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCURVEINFO;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveType */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;
  TcpIp_TlsEllipticCurveIdType curveId;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the received curve ID */
  curveId = IpBase_GetUint16(
    TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  /* And increment the read index by the length of the curve ID field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_CURVENAMELEN);

  /* #10  Check if the curve ID is supported */
  retVal = TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId(TlsConIdx, curveId);

  if (retVal != E_OK)
  {
    /* Incorrect curve ID received - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCURVEINFO;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetCurveId() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  TcpIp_TlsEllipticCurveIdType CurveId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsHandshakeIndStartIdxOfTlsCipherWorkerType handshakeStartIdx
    = TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  TcpIp_TlsHandshakeIndEndIdxOfTlsCipherWorkerType handshakeEndIdx
    = TcpIp_GetTlsHandshakeIndEndIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  TcpIp_TlsHandshakeIndIterType handshakeIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate through all available handshakes for this TLS-Connection */
  for (handshakeIter = handshakeStartIdx; handshakeIter < handshakeEndIdx; handshakeIter++)
  {
    TcpIp_TlsHandshakeIterType tlsHandshakeIdx = TcpIp_GetTlsHandshakeInd(handshakeIter);

    /* #20 If a handshake with matching curve is found, mark the CipherWorker as active */
    if (CurveId == TcpIp_GetEllipticCuveIdOfTlsHandshake(tlsHandshakeIdx))
    {
      TcpIp_SetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx, (uint8) tlsHandshakeIdx);
      TcpIp_SetEllipticCurveIdOfTlsConnectionDyn(TlsConIdx, CurveId);
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgValidateCurveId */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey
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
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType   ServerKeyExchangeEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  Std_ReturnType retVal = E_OK;
  uint8          receivedServerPubKeyLen;
  uint8          expectedPubKeyLen;

  /* ----- Implementation ----------------------------------------------- */

  if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
  {
    /* expected length of public key contains one further byte for compression flag */
    expectedPubKeyLen = (TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(
      TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx))) + 1u;
  }
  else
  {
    /* expected length of public key does not contain any further bytes */
    expectedPubKeyLen = (TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(
      TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)));
  }

  /* #10 Get the received public key length and compare it to the expected key length */
  receivedServerPubKeyLen = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  if (receivedServerPubKeyLen == expectedPubKeyLen)
  {
    /* Set the index to the start of the public key length */
    TcpIp_SetTlsBufferRxServerKeyExchangePubKeyLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* and increment the read index by the length of the public key length field */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_PUBKEYLEN);

    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
      (TcpIp_TlsBufferRxIterType)receivedServerPubKeyLen, ServerKeyExchangeEndIdx))
    {
    /* #20 Check if we expect a compression flag for this received public key */
      if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
      {
        /* #30 if so, read and compare the compression flag of public key with the expected compression flag */
        uint8 receivedCompressionFlag = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
          TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

        if (receivedCompressionFlag != TCPIP_TLS_PUBKEY_COMPRESSION_FLAG)
        {
          /* invalid compression flag received */
          retVal = E_NOT_OK;
        }

        receivedServerPubKeyLen -= TCPIP_TLS_KEYEXCH_COMPFLAGLEN;

        /* Increment the write index by the consumed length (1 Byte) */
        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_COMPFLAGLEN);
      }

      /* Set the index to the start of the public key (including compression flag if present) */
      TcpIp_SetTlsBufferRxServerKeyExchangePubKeyIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

      /* and increment the read index by the length of the public key field */
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, receivedServerPubKeyLen);
    }
  }
  /* #40 Check if the public key was extracted properly */
  if (retVal != E_OK)
  {
    /* #50 Incorrect curve Id received - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTPUBKEYLEN;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_SignatureAlgorithmIdType expectedSigHashAlgoId
    = TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint16 receivedSigHashAlgoId;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the received signature Hash + algorithm ID */
  receivedSigHashAlgoId = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  /* and increment the read index by the length of the signature algorithm signature field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    (TCPIP_TLS_KEYEXCH_SIGALGOSIGNLEN + TCPIP_TLS_KEYEXCH_SIGALGOHASHLEN));

  /* #10 Check if the received signature algorithm matches the expected one */
  if (receivedSigHashAlgoId != (uint16)expectedSigHashAlgoId)
  {
    /* #20 Incorrect hash algorithm Id received - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCURVEINFO;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignAlgorithm */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType   ServerKeyExchangeEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;
  uint16          serverSignLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the received signature length */
  serverSignLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0);

  /* Set the index to the start of the signature length */
  TcpIp_SetTlsBufferRxServerKeyExchangeSignatureLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* And increment the read index by the length of the signature length field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_SIGLENLEN);

  /* #10 Check if the received signature length is in range */
  /* Validation of signature length is performed later */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
        (TcpIp_TlsBufferRxIterType)serverSignLen, ServerKeyExchangeEndIdx))
  {
    /* Set the index to the start of the signature */
    TcpIp_SetTlsBufferRxServerKeyExchangeSignatureIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* and increment the read index by the length of the signature field */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, serverSignLen);

    retVal = E_OK;
  }

  /* Check if the signature was extracted properly */
  if (retVal != E_OK)
  {
    /* Incorrect curve Id received - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTSIGNLEN;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetSignature */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the calculation of the job in the async context handler and change the handshake state to ASYNC_PENDING */
  TcpIp_SetHsVerifySignatureAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, TRUE);

  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ServerKeyExchangeVerifySignature() */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
  TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState(
    TcpIp_TlsConnectionIterType TlsConIdx,
    TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneIdx
    = TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertificateRequestIdx
    = TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* Reset the context state - in case we did not receive the next message, this will be overwritten to WAIT_CYCLE */
  /* If the next message is received, we must reset it to NO_ASYNC */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Update the next valid TLS handshake state, depending on the active key exchange method and the received messages */
  /* This function can be called multiple times, when we do not received the next message and can not determine the valid
     next state */
  /* #20 ServerHelloDone has been received, notify the certificate chain validation result to user */
  if (   (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE)
      || (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH))
  {
    /* Next state could be ServerCertificateRequest or ServerHelloDone */
    if (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
    {
      /* ServerCertificateRequest received - next state is parsing of ServerCertificateRequest */
      *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_REQUEST;
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE);
    }
    else if (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
    {
      /* ServerHelloDone received and no ServerCertificateStatus - next state is parsing of ServerHelloDone */
      *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE;
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE);
    }
    else /* if (   (serverHelloDoneIdx == TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
                && (serverCertificateRequestIdx == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)) */
    {
      /* ServerCertificateStatus and ServerHelloDone not received yet.
       * Wait until next main function cycle to determine next state */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_WAIT_CYCLE);
    }
  }
  else
  {
    /* key exchange is PSK, next state must be ServerHelloDone */
    *NextStatePtr = TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE;
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE);
  }

} /* TcpIp_TlsClientMsg_ServerKeyExchangeDetermineNextHsState() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_ParseServerCertificateRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCertificateRequest(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx =
    TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertificateRequestIdx =
    TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the CertificateRequest message is received and forward it to the parser */
  if (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
  {
    Std_ReturnType retVal;

    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* Forward message to parser */
    retVal = TcpIp_TlsClientMsg_ExtractCertificateRequestInformation(TlsConIdx);

    if (retVal == E_OK)
    {
      /* #20 Extraction was successful. Change the state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE */
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE);
      TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
    }
    else
    {
      /* #30 Extraction failed. Cancel the handshake. */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #40 otherwise, we received an unexpected message, trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerCertificateRequest() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractCertificateRequestInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractCertificateRequestInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestStartIdx =
    TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerCertificateRequestLenOfTlsClientBufferMgmtType serverCertRequestLen =
    TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestEndIdx
    = (serverCertRequestStartIdx  + TCPIP_TLS_HSHDRLEN + serverCertRequestLen);

  Std_ReturnType retVal = E_NOT_OK;

  /* minimum expected length contained in certificate request message */
  const TcpIp_TlsBufferRxIterType certReqMinimalLength =
    (TCPIP_TLS_CERTREQUEST_CERTTYPESLENGTH_LEN + TCPIP_TLS_CERTREQUEST_SIGNATUREHASHALGORITHMSLENGTH_LEN
      + TCPIP_TLS_CERTREQUEST_DISTINGUISHEDNAMESLENGTH_LEN);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the minimum expected length of the received certificate request message and extract the information */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(serverCertRequestStartIdx,
        certReqMinimalLength, serverCertRequestEndIdx))
  {
    /* Extract certificate types information */
    retVal = TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes(TlsConIdx);

    /* Extract signature and hash algorithm information */
    retVal |= TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms(TlsConIdx);

    /* Extract distinguished names information */
    retVal |= TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames(TlsConIdx);

    /* Check that all data is consumed */
    retVal |= TcpIp_TlsMsg_CheckMsgForRemainingData(TlsConIdx, serverCertRequestEndIdx);
  }
  /* else - alert is triggered in outer function */

  return retVal;
} /* TcpIp_TlsClientMsg_ExtractCertificateRequestInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType certTypesListStartIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestStartIdx =
    TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerCertificateRequestLenOfTlsClientBufferMgmtType serverCertRequestLen =
    TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestEndIdx
    = (serverCertRequestStartIdx + TCPIP_TLS_HSHDRLEN + serverCertRequestLen);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Since the TLS client does not support client authentication, this function does not provide any functionality,
     but reads the received values and check the provided length information for plausibility. */

  /* Format RFC5246 - 7.4.4.  Certificate Request */
  /*   ClientCertificateType certificate_types<1..2^8-1>;
   *
   *   +---> certTypesListStartIdx
   *  /
   * [Certificate Types Count]   [CertType_0]   [CertType_1] ...
   *      ^                      \_____________________________/
   *      |                                      |
   *      +--> receivedDistinguishedNamesListLength <------+
   */

  /* #10 Get the length of the received certificate types list */
  uint8 receivedCertTypeListLength = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(certTypesListStartIdx), 0);
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CERTREQUEST_CERTTYPESLENGTH_LEN);

  /* #20 Check if the received certificate types list is plausible and skip processing of the certificate types */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(certTypesListStartIdx, receivedCertTypeListLength, serverCertRequestEndIdx))
  {
    /* Skip processing of received certificate types */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, receivedCertTypeListLength);
    if (receivedCertTypeListLength >= 1u)
    {
      /* The message must contain at least one certificate type */
      retVal = E_OK;
    }
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertRequestMsgGetCertTypes() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType signatureHashAlgoListStartIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestStartIdx =
    TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerCertificateRequestLenOfTlsClientBufferMgmtType serverCertRequestLen =
    TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestEndIdx
    = (serverCertRequestStartIdx + TCPIP_TLS_HSHDRLEN + serverCertRequestLen);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Since the TLS client does not support client authentication, this function does not provide any functionality,
     but reads the received values and check the provided length information for plausibility. */

  /* Format RFC5246 - 7.4.4.  Certificate Request
   *  SignatureAndHashAlgorithm supported_signature_algorithms<2^16-1>;
   *
   *   +---> signatureHashAlgoListStartIdx                +--> 2 Bytes (Hash - Signatures)
   *  /                                                  /
   * [Signature Hash Algorithms Length] [Algorithm_0] [Algorithm_1] ...
   *      ^                             \_____________________________/
   *      |                                               |
   *      +--> receivedDistinguishedNamesListLength <------+
   */

  /* Get the length of the received certificate types list */
  uint16 receivedSignatureHashAlgoListLength = IpBase_GetUint16(
    TcpIp_GetAddrTlsBufferRx(signatureHashAlgoListStartIdx), 0);

  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TCPIP_TLS_CERTREQUEST_SIGNATUREHASHALGORITHMSLENGTH_LEN);

  /* #10 Check if the received signature hash algorithms list is plausible and skip processing of the algorithms */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(signatureHashAlgoListStartIdx,
        receivedSignatureHashAlgoListLength, serverCertRequestEndIdx))
  {
    /* Skip processing of received algorithms */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, receivedSignatureHashAlgoListLength);

    if (   (receivedSignatureHashAlgoListLength >= 2u)
        && ((receivedSignatureHashAlgoListLength % 2u) == 0u))
    {
      /* The message must contain at least one signature hash algorithm */
      retVal = E_OK;
    }
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertRequestMsgGetSignatureHashAlgorithms() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType distinguishedNamesListStartIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestStartIdx =
    TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_ServerCertificateRequestLenOfTlsClientBufferMgmtType serverCertRequestLen =
    TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertRequestEndIdx
    = (serverCertRequestStartIdx + TCPIP_TLS_HSHDRLEN + serverCertRequestLen);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Since the TLS client does not support client authentication, this function does not provide any functionality,
     but reads the received values and check the provided length information for plausibility. */

  /* Format RFC5246 - 7.4.4.  Certificate Request
   *   opaque DistinguishedName<1..2^16-1>;
   *   DistinguishedName certificate_authorities<0..2^16-1>;
   *
   *   +---> distinguishedNamesListStartIdx
   *  /
   * [Distinguished Names Length] [DER certificate Authority_1] [DER certificate Authority_2]...
   *      ^                       \________(optional)__________________________________________/
   *      |                                               |
   *      +--> receivedDistinguishedNamesListLength <-----+
   */

  /* Get the length of the received distinguished names list */
  uint16 receivedDistinguishedNamesListLength = IpBase_GetUint16(
    TcpIp_GetAddrTlsBufferRx(distinguishedNamesListStartIdx), 0);

  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TCPIP_TLS_CERTREQUEST_DISTINGUISHEDNAMESLENGTH_LEN);

  /* #10 Check if the received distinguished names list is plausible and skip processing of certificate authorities */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(distinguishedNamesListStartIdx,
        receivedDistinguishedNamesListLength, serverCertRequestEndIdx))
  {
    /* Skip processing of received certificate authorities */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, receivedDistinguishedNamesListLength);

    /* The distinguished names is optional, no need for further checks */
    retVal = E_OK;
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertRequestMsgGetDistinguishedNames() */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerHelloDone
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerHelloDone(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneIdx =
    TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  TcpIp_TlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmtType serverCertificateRequestIdx
    = TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

  Std_ReturnType IntFctRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a handshake message with the handshake type ServerHelloDone */
  if (serverHelloDoneIdx != TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE; /* default, even for PSK use case */

    /* #20 if so, extract the information inside the server hello done message */
    IntFctRetVal = TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation(TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    /* #30 ServerHelloDone has been received, notify the certificate chain validation result to user */
    if (   (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE)
        || (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH))
    {
      TcpIp_TlsClient_TlsCertChainTriggerValidationCallback(TlsConIdx, TRUE);

      /* #40 Determine next TLS client state, depending on the received messages (ClientCertificate or ClientKeyExchange) */
      if (serverCertificateRequestIdx != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* TLS client received certificate request message - Next state is SendClientCertificate */
        nextState = TCPIP_TLS_STATE_SEND_CLIENT_CERTIFICATE;
      }
      /* else - next state is default state (TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE) */

    }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
    /* #50 Check return value from extract function and switch to next state */
    TcpIp_TlsHsStm_ErrorHandlingAndStateTransition(TlsConIdx, IntFctRetVal, nextState);
    TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
  }
  else
  {
    /* #60 otherwise, we receive an unexpected message, trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerHelloDone */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType serverHelloDoneStartIdx =
    TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* Length of the received Server Hello done message */
  TcpIp_ServerHelloDoneLenOfTlsClientBufferMgmtType serverHelloDoneLen =
    TcpIp_GetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  /* End index of the received Server Hello done message - Need for in range checks inside the parser */
  CONST(TcpIp_TlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmtType, AUTOMATIC) serverHelloDoneEndIdx
    = serverHelloDoneStartIdx + TCPIP_TLS_HSHDRLEN + serverHelloDoneLen;

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that the expected length of the ServerHelloDone message (0 byte) was received */
  if (serverHelloDoneLen == TCPIP_TLS_SERVERHELLODONE_LEN)
  {
    /* #20 Check if there is some more information in the buffer */
    retVal = TcpIp_TlsMsg_CheckMsgForRemainingData(TlsConIdx, serverHelloDoneEndIdx);
  }
  else
  {
    /* #30 If an invalid length of the ServerHelloDone message was received, trigger an alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerHelloDoneInformation */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_SendClientCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Prepare the ClientKeyExchange message */
  retVal = TcpIp_TlsClientMsg_PrepareClientCertificate(TlsConIdx);

  /* #20 Check the result of the preparation of the ClientKeyExchange message */
  if (retVal == E_OK)                                                                                                   /* PRQA S 2991, 2995 */ /* MD_TcpIp_Tls_2991_2995 */
  {
   /* #30 Preparation was successful. Change the state to TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE */
   TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

   TcpIp_SetClientCertificateReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
   TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE);
   TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  }
  else
  {
    /* #40 Preparation failed. Cancel the handshake. */
    TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(TlsConIdx);
  }
} /* TcpIp_TlsClientHsStm_SendClientCertificate() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_PrepareClientCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIdxOfTlsConnectionType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint16 clientCertificateLen;
  uint16 writableLength;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ClientHello message by adding all relevant message information */
  TcpIp_SetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* Add generic handshake header */
  TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_CERTIFICATE);

  /* Add the certificates, if configured */
  TcpIp_TlsClientMsg_ClientCertificateAddCertificates(TlsConIdx);

  /* #20 Write the length information into the HS Header (Message length = WriteIdx - ServerHelloStartIdx). */
  clientCertificateLen = (uint16)(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
    - TcpIp_GetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  TcpIp_SetClientCertificateLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, clientCertificateLen);

  writableLength = clientCertificateLen - TCPIP_TLS_HSHDRLEN;
  TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), (uint32)writableLength);

  return E_OK;
} /* TcpIp_TlsClientMsg_PrepareClientCertificate() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientCertificateAddCertificates
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientCertificateAddCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType certificateStartIdx
    = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  const uint32 zeroCertificateLength = 0;
  /* ----- Implementation ----------------------------------------------- */
  /* RFC5246 - 7.4.6 Client Certificate
   *   If no suitable certificate is available, the client MUST send a
   *   certificate message containing no certificates.
   *   That is, the certificate_list structure has a length of zero.
   */

  /* #10 TLS Client does not support client authentication. Add zero length according to RFC to the certificate message */
  IpBase_PutUint24(TcpIp_GetAddrTlsBufferTx(certificateStartIdx), 0, zeroCertificateLength);

  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_CERTSLEN_LEN);

} /* TcpIp_TlsClientMsg_ClientCertificateAddCertificates() */

#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON */
/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_SendClientKeyExchange
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Prepare the ClientKeyExchange message */
  TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation(TlsConIdx);

  /* #20 Check the state of the preparation of the ClientKeyExchange message */
  if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC)
  {
    /* #30 Preparation was successfully performed. Change the state to TCPIP_TLS_STATE_SEND_CLIENT_CCS */
    TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
      = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

    /* Next state is a transmitting state (either send the ClientCCs message or Abort state) so trigger the processing */
    TcpIp_SetKeyExchangeReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_CCS);
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  }
  else if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
  {
    /* #40 Preparation not done yet, an async operation is pending. Nothing to do, just leave the function. */
  }
  else
  {
    /* #50 Preparation failed. Cancel the handshake. */
    TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(TlsConIdx);
  }
} /* TcpIp_TlsClientHsStm_SendClientKeyExchange() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation
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
 */
/* PRQA S 6030, 6050 1 */ /* MD_TcpIp_Tls_STCYC, MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ClientKeyExchange message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_DONE)     /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is triggerd in one of the sub states, switch to lowPrio context - leave this function */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING))
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE:
      {
        TcpIp_TlsKeyExchangeMethodDataType  keyExchangeMethod
          = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

        /* Set the start index of this message to the current write index */
        TcpIp_SetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
          TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

        /* #20 Add the generic TLS-Handshake header */
        TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE);

        /* #30 Select the next state depending on the key exchange method  */
        switch (keyExchangeMethod)
        {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
          {
            /* in case of ECDHE or ECDH we have to add the DH parameter */
            TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_DH);
            break;
          }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
          case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
          {
            /* in case of PSK we have to add the PSK Identity */
            TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_PSK_ID);
            break;
          }
          default:
          {
            /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the
            active cipher suite received in the server_hello message. */
            break;
          }
        }  /* switch (keyExchangeMethod) */

        break;
      } /* case  TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_HDR */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_DH:
      {
        /* #40 Add the Diffie-Hellman parameter and key */
        TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_MSG_LENGTH);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_DH */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_PSK_ID:
      {
        /* #50 Add the PSK parameter and identity */
        TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_MSG_LENGTH);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_PSK ID */

      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_MSG_LENGTH:
      {
        TcpIp_TlsHandshakeState nextKeyExchangeState = TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_DONE;
        /* #60 Prepare the transmit of the ClientKeyExchange message */
        TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength(TlsConIdx, &nextKeyExchangeState);
        /* Change State transition depending on key exchange method. */
        /* TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET | TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_PSK_SHARED_SECRET */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextKeyExchangeState);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_MSG_LENGTH */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET:
      {
        /* #70 Calculate the TLS shared secret */
        TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_PSK_SHARED_SECRET:
      {
        /* #80 Calculate the TLS premaster secret for active PSK-Identity */
        TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_PSK_SHARED_SECRET */

      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET:
      {
        /* #90 Calculate the TLS master secret */
        TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET */

      case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC:
      {
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_DONE);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC */

      default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
      break;

    } /* switch () */
  } /* while () */

} /* TcpIp_TlsClientMsg_PrepareClientKeyExchangeAndTriggerSecretCalculation() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams
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
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  uint8 publicKeyLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Save the current Write index for Key Exchange parameter (needed for signature generation) */
  TcpIp_SetTlsBufferTxClientKeyExchangePubKeyIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* #10 Get the length of the calculated Public key, depended on the current selected curve  */
  publicKeyLen = TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx));

  /* Check if the compression flag is required */
  if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
  {
    publicKeyLen += TCPIP_TLS_KEYEXCH_COMPFLAGLEN;
  }

  /* #20 Write the Length of the PublicKey in the TLS TxBuffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, publicKeyLen);

  /* Increment the write index by the consumed length (1 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_PUBKEYLEN);

  /* #30 Check if the compression flag is required */
  if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
  {
    /* #40 if so, write the compression flag */
    IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, TCPIP_TLS_PUBKEY_COMPRESSION_FLAG);

    /* Increment the write index by the consumed length (1 Byte) */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_COMPFLAGLEN);
  }

  /* #50 Call the internal function to write the generated DH public key in the TLS TxBuffer */
  TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey(TlsConIdx);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeAddDiffieHellmanParams() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetDhPubKeyAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeAddDhPubKey() */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams
 *********************************************************************************************************************/
/*!
  * Internal comment removed.
 *
 *
 *
  */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams(
  TcpIp_TlsConnectionIterType  TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select a matching PSK-Identity, depending on received PSK-hint */
  TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity(TlsConIdx);

  /* #20 Add the selected PSK-Identity to the ClientKeyExchange PSK parameter */
  TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity(TlsConIdx);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeAddPskParams() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity(
  TcpIp_TlsConnectionIterType  TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we have received a PSK Hint matching one of the known PSK Hints. */
  /* returns E_NOT_OK in case no matching PSK-Hint was received */
  if (TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints(TlsConIdx) == E_NOT_OK)
  {
    /* #20 otherwise, if no PSK-Hint matches, select the default PSK Identity */
    TcpIp_TlsMsg_SelectDefaultPskIdentity(TlsConIdx);
  }
  /* else - matching PSK hint was selected by caller function */

} /* TcpIp_TlsClientMsg_ClientKeyExchangSelectPskIdentity() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints(
  TcpIp_TlsConnectionIterType  TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_ServerKeyExchangePskHintLenOfTlsClientBufferMgmtType receivedPskHintLeng
    = TcpIp_GetServerKeyExchangePskHintLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a PSK-Hint and compare the actual hint content */
  if (receivedPskHintLeng != 0u)
  {
    retVal = TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint(TlsConIdx);
  }
  else
  {
    /* No PSK-Hint received, return E_NOT_OK. Outer function will selected the default PSK-Identity. */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ClientKeyExchangeCheckPskHints() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint(
  TcpIp_TlsConnectionIterType  TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_ServerKeyExchangePskHintLenOfTlsClientBufferMgmtType receivedPskHintLeng
    = TcpIp_GetServerKeyExchangePskHintLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  TcpIp_TlsPskIdentityIndStartIdxOfTlsConnectionType pskIdentityIndStartIdx
    = TcpIp_GetTlsPskIdentityIndStartIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsPskIdentityIndEndIdxOfTlsConnectionType pskIdentityIndEndIdx
    = TcpIp_GetTlsPskIdentityIndEndIdxOfTlsConnection(TlsConIdx);

  TCPIP_P2C(uint8) receivedHintPtr
    = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerKeyExchangePskHintIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  TcpIp_TlsPskIdentityIndIterType pskIdentityIndIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured PSK-Identities */
  for (pskIdentityIndIter = pskIdentityIndStartIdx; pskIdentityIndIter < pskIdentityIndEndIdx; pskIdentityIndIter++)
  {
    TcpIp_TlsPskIdentityIndType tlsPskIdentity = TcpIp_GetTlsPskIdentityInd(pskIdentityIndIter);
    TcpIp_PskIdentityHintLengthOfTlsPskIdentityType configuredPskHintLen = TcpIp_GetPskIdentityHintLengthOfTlsPskIdentity(tlsPskIdentity);
    /* #20 Check if the received Length match with the configured of the current PSK-Identity */
    if (receivedPskHintLeng == configuredPskHintLen)
    {
      TCPIP_P2C(uint8) iterPskHintPtr = TcpIp_GetAddrPskIdentityHint(tlsPskIdentity);
      /* #30 Compare the actual PSK-Hint if it matches */
      if (IpBase_StrCmpLen(receivedHintPtr, iterPskHintPtr, receivedPskHintLeng) == E_OK)
      {
        /* #40 Set this PSK-Identity as active one */
        TcpIp_SetTlsPskIdentityActiveIdxOfTlsConnectionDyn(TlsConIdx, tlsPskIdentity);
        retVal = E_OK;
        break; /* skip all other comparisons */
      }
    }
  }
  return retVal;
} /* TcpIp_TlsClientMsg_ClientKeyExchangeCompareReceivedPskHint() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity(
  TcpIp_TlsConnectionIterType  TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferMgmtIdxOfTlsConnectionType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsPskIdentityActiveIdxOfTlsConnectionDynType activeTlsPskIdentityIdx
    = TcpIp_GetTlsPskIdentityActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_PskIdentityLengthOfTlsPskIdentityType pskIdentityLen;
  TcpIp_TlsPskIdentityIndType tlsPskIdentity;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the length of the PSK-Identity */
  pskIdentityLen = TcpIp_GetPskIdentityLengthOfTlsPskIdentity(activeTlsPskIdentityIdx);

  /* #10 Write the Length of the PSK-Identity into the TLS TxBuffer */
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, pskIdentityLen);

  /* Increment the write index by the consumed length (2 Bytes) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_KEYEXCH_PSKIDLEN);

  /* Get the indirection to the PSK Identity */
  tlsPskIdentity = TcpIp_GetTlsPskIdentityInd(activeTlsPskIdentityIdx);

  /* #20 Write the PSK Identity string into the TLS TxBuffer */
  VStdMemCpy(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetAddrPskIdentity(TcpIp_GetPskIdentityStartIdxOfTlsPskIdentity(tlsPskIdentity)), pskIdentityLen);

  /* Increment the write index by the consumed length (pskIdentityLen) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, pskIdentityLen);

} /* TcpIp_TlsClientMsg_ClientKeyExchangAddSelectedPskIdentity() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  TCPIP_P2V(TcpIp_TlsHandshakeState) NextStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 clientKeyExchangeLen;
  TcpIp_SizeOfTlsBufferMgmtType        tlsBufferMgmtIdx       = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType    tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsKeyExchangeMethodDataType   keyExchangeMethod      = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Calculate the length information: Message length = WriteIdx - ServerCertStartIdx */
  clientKeyExchangeLen = ((uint32)TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
    - TcpIp_GetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));
  TcpIp_SetClientKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)clientKeyExchangeLen);

  /* #10 Write the message length into the HS-Header */
  TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
    (clientKeyExchangeLen - TCPIP_TLS_HSHDRLEN));

  /* #20 Change the next handshake state depending on the  key exchange method */
  switch (keyExchangeMethod)
  {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
    /* in case of ECDHE or ECDH we have to calculate the DH shared secret */
      *NextStatePtr = TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET;
      break;
    }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
    case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
    {
      /* in case of PSK we have to calculate the PSK shared secret */
      *NextStatePtr = TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_PSK_SHARED_SECRET;
      break;
    }
    default:
    {
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      break;
    }
  }  /* switch (keyExchangeMethod) */

} /* TcpIp_TlsClientMsg_ClientKeyExchangeAddMessageLength() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the calculation of the job in the async context handler and set the state to ASYNC_PENDING */
  TcpIp_SetDhSharedSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeCalcSharedSecret() */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the calculation of the job in the async context handler and set the state to ASYNC_PENDING */
  TcpIp_SetPskPremasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeCalcPskPremasterSecret() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the calculation of the job in the async context handler and set the state to ASYNC_PENDING */
  TcpIp_SetCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_ClientKeyExchangeCalcMasterSecret() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_SendClientCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientCcs(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the transmission of the CCS message and change the TLS handshake state to TCPIP_TLS_STATE_SEND_CLIENT_FINISHED */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  TcpIp_SetChangeCipherSpecReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_FINISHED);

} /* TcpIp_TlsClientHsStm_SendClientCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections and initialize the submodules */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    if (TcpIp_GetModeOfTlsConnection(tlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* Initialize the handshake message indices */
      TcpIp_TlsClient_InitHsMsgIndices(tlsConIdx);

      /* Initialize the handshake length information */
      TcpIp_TlsClient_InitHsLenInformation(tlsConIdx);

      /* Initialize the ready to send flags */
      TcpIp_TlsClient_InitReadyToSendFlags(tlsConIdx);

      /* Initialize the async context flags */
      TcpIp_TlsClient_InitAsnycFlags(tlsConIdx);

      /* Initialize handshake state, the state shall be updated next when TCP connect is called */
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_INIT);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      /* Initialize the process state of the remote certificate chain */
      TcpIp_SetHsCertStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_CERTCHAIN_INIT);

      TcpIp_TlsClient_ResetCertChainStates(tlsConIdx);

#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
    }
  }

} /* TcpIp_TlsClient_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_InitHsMsgIndices
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitHsMsgIndices(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Init RX handshake Indices */
  TcpIp_SetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERHELLOIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERRANDOMIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerSessionIdIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERSESSIONIDIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerKeyExchangePskParamIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEPSKPARAMIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerKeyExchangePskHintIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEPSKHINTIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerKeyExchangeSignatureLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGESIGNATURELENIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERFINISHEDIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferRxServerFinishedVerifyDataIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERRXSERVERFINISHEDVERIFYDATAIDXOFTLSCLIENTBUFFERMGMT);

  /* #20 Init TX handshake Indices */
  TcpIp_SetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTHELLOIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTRANDOMIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientSessionIdIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTSESSIONIDIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTCERTIFICATEIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientKeyExchangePubKeyIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTKEYEXCHANGEPUBKEYIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientKeyExchangePubKeyLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTKEYEXCHANGEPUBKEYLENIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTFINISHEDIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientFinishedVerifyDataIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTFINISHEDVERIFYDATAIDXOFTLSCLIENTBUFFERMGMT);
  TcpIp_SetTlsBufferTxClientExtensionsIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TCPIP_NO_TLSBUFFERTXCLIENTEXTENSIONSIDXOFTLSCLIENTBUFFERMGMT);

} /* TcpIp_TlsClient_InitHsMsgIndices() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_InitAsnycFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitAsnycFlags(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the TLS Client Async trigger flags */
  TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetCalcServerFinishedVerifyDataAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetHsVerifyCertGroupAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetHsVerifySignatureAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetCertificateStatusOcspValidationAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
} /* TcpIp_TlsClient_InitAsnycFlags() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_InitHsLenInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitHsLenInformation(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the TX length information to zero */
  TcpIp_SetClientHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetClientCertificateLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetClientKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetClientFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);

  /* #20 Initialize the RX length information to zero */
  TcpIp_SetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerCertStatusOcspResponseLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerHelloSessionIdLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);
  TcpIp_SetServerKeyExchangePskHintLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, 0);

} /* TcpIp_TlsClient_InitHsLenInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_InitReadyToSendFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_InitReadyToSendFlags(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the TLS-Client ReadyTosSend flags */
  TcpIp_SetHelloReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetClientCertificateReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetKeyExchangeReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetClientFinishedReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetChangeCipherSpecReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  TcpIp_SetClientFinishedReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);

} /* TcpIp_TlsClient_InitReadyToSendFlags() */

/**********************************************************************************************************************
 *   TLS CLIENT HS TRIGGER SM
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6010, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STMIF */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ClientHello message is transmittable and forward it to the record layer */
  if (TcpIp_IsHelloReadyToSendOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
          TcpIp_GetClientHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetHelloReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
    }
  }
  /* #20 Check if the ClientCertificate message is transmittable and forward it to the record layer */
  if (TcpIp_IsClientCertificateReadyToSendOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
          TcpIp_GetClientCertificateLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetClientCertificateReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
    }
  }
  /* #30 Check if the ClientKeyExchange message is transmittable and forward it to the record layer */
  if (TcpIp_IsKeyExchangeReadyToSendOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
          TcpIp_GetClientKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetKeyExchangeReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
    }
  }
  /* #40 Check if the ClientFinished message is transmittable and forward it to the record layer */
  if (TcpIp_IsClientFinishedReadyToSendOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxClientFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
          TcpIp_GetClientFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetClientFinishedReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
    }
  }
} /* TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl() */

/**********************************************************************************************************************
 *   TLS CLIENT HANDSHAKE STATE MACHINE
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsClient_ProcessHandshake
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ProcessHandshake(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the current connection is in an active HS state */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE))
  {
    /* #20 Check that there is no async operation in process */
    if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
    {
      /* #30 Check if we have at least one trigger to process the HS */
      if (   (TcpIp_IsHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx) == TRUE)          /* Next state is a TX state */      /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE)  /* AsnycCtx operation is done, continue HS */
          || (TcpIp_GetHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx) != 0u))                     /* unprocessed HS messaged in the buffer */
      {
        /* #40 Perform the next Step within the current HS flow */
        TcpIp_TlsClientHsStm_PerformNextHsStep(TlsConIdx);
      } /* else, do nothing */
    } /* else, do nothing */
  } /* else, do nothing */
} /* TcpIp_TlsClient_ProcessHandshake() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_PerformNextHsStep
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_TcpIp_TlsStatemachine_STCAL_6050 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_PerformNextHsStep(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process the TLS-CLient Handshake depending on the current sate */
  uint16 hsState = TCPIP_TLS_GET_HS_STATE(TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx));
  switch ((TcpIp_TlsHandshakeState)hsState)
  {
    case TCPIP_TLS_STATE_SEND_CLIENT_HELLO:
    {
      TcpIp_TlsClientHsStm_SendClientHello(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO:
    {
      TcpIp_TlsClientHsStm_ParseServerHello(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE:
    {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      TcpIp_TlsClientHsStm_ParseServerCertificate(TlsConIdx);
#  endif
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS:
    {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      TcpIp_TlsClientHsStm_ParseServerCertificateStatus(TlsConIdx);
#  endif
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE:
    {
      TcpIp_TlsClientHsStm_ParseServerKeyExchange(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_REQUEST:
    {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      TcpIp_TlsClientHsStm_ParseServerCertificateRequest(TlsConIdx);
#  endif
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE:
    {
      TcpIp_TlsClientHsStm_ParseServerHelloDone(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_SEND_CLIENT_CERTIFICATE:
    {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      TcpIp_TlsClientHsStm_SendClientCertificate(TlsConIdx);
#  endif
      break;
    }
    case TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE:
    {
      TcpIp_TlsClientHsStm_SendClientKeyExchange(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_SEND_CLIENT_CCS:
    {
      TcpIp_TlsClientHsStm_SendClientCcs(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED:
    {
      TcpIp_TlsClientHsStm_SendClientFinished(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_CCS:
    {
      TcpIp_TlsClientHsStm_ParseServerCcs(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED:
    {
      TcpIp_TlsClientHsStm_VerifyServerFinished(TlsConIdx);
      break;
    }
    case TCPIP_TLS_STATE_HANDSHAKE_DONE:
    {
      TcpIp_TlsClientHsStm_FinalizeHandshake(TlsConIdx);
      break;
    }
    default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
    {
      break;
    } /* default */
  } /* switch() */
} /* TcpIp_TlsClientHsStm_PerformNextHsStep() */

/**********************************************************************************************************************
 *   TLS CLIENT ASYNC CONTEXT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_AsyncHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6010, 6050, 6080 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_TlsStatemachine_STCAL_6050, MD_TcpIp_TlsStatemachine_STMIF_6080 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_AsyncHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the trigger for the different ASYNC operations and execute the operation if the trigger is set */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  /* Check if the certificate status response validation async context flag is TRUE */
  if (TcpIp_IsCertificateStatusOcspValidationAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    TcpIp_TlsClientCtx_ValidateCertificateStatus(TlsConIdx);
  }

  /* Check if the Signature verification async context flag is TRUE */
  if (TcpIp_IsHsVerifySignatureAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    /* Only perform signature verification if certificate has been validated successfully */
    /* [HS Server Certificate Chain Handling StM] Certificate verification finished, signatures are available */
    if (TcpIp_GetHsCertStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CERTCHAIN_FINISHED)
    {
      /* If the certificate chain is validated successfully, verify the signature of the public key */
      TcpIp_TlsClientCtx_VerifySignatureOfPublicKey(TlsConIdx);
      TcpIp_SetHsVerifySignatureAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
    }
  }
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

  /* Check if the Client finished hash async context flag is TRUE and calculate the Client Finished data */
  if (TcpIp_IsCalcClientFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    TcpIp_TlsClientCtx_CalcClientFinishedHash(TlsConIdx);
    TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  }

  /* Check if the Server Finished async context flag is TRUE and calculate the Server Finished data */
  if (TcpIp_IsCalcServerFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    TcpIp_TlsClientCtx_CalcServerFinishedHash(TlsConIdx);
    TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  }

  /* Check if the Server Finished async context flag is TRUE and calculate the Client Finished Verify data */
  if (TcpIp_IsCalcServerFinishedVerifyDataAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx) == TRUE)
  {
    TcpIp_TlsClientCtx_CalcServerFinishedVerifyData(TlsConIdx);
    TcpIp_SetCalcServerFinishedVerifyDataAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
  }
} /* TcpIp_TlsServerCtx_AsyncHandler() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup
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
 */
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050, MD_TcpIp_TlsStatemachine_STMIF_6080 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConIdx = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the KeyM status of each certificate */
  if (TcpIp_TlsClient_TlsUpdateCertChainStatus(TlsConIdx, TCPIP_TLS_UPDATE_CERT_MODE_CHAIN) == E_OK)
  {
    TcpIp_CertValidationResultType result;

    /* #20 Try to obtain overall validation result and update states */
    TcpIp_TlsClient_TlsUpdateOverallCertValidationResult(TlsConIdx, &result);

    /* Store the certificate status for invoking validation callback to upper layer later */
    TcpIp_SetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx, result);

    /* Set certificate chain validation state to finished */
    /* [HS Server Certificate Chain Handling StM] Certificate verification is finished */
    TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_FINISHED);

    /* Set the async flag to false */
    TcpIp_SetHsVerifyCertGroupAsyncFlagOfTlsClientConnection(tlsClientConIdx, FALSE);

    /* Set the async state to DONE */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);

    /* #30 Check if the overall validation result is OK or NOT_OK. */
    if (result == TCPIP_TLS_VALIDATION_NOT_OK)
    {
      /* The overall result is NOT_OK.
         Find out if we can allow the upper layer to overrule this result, or if the handshake has to be canceled
         here.

         The only (negative) condition we can allow to be overruled is a good cert chain with a self-signed root. In
         all other cases the handshake shall be canceled immediately.
      */

      TcpIp_TlsAlertDescriptionType alertDescription;
      boolean cancelHandshake = TRUE;

      TcpIp_TlsClient_TlsGetAlertForBadCertificateChain(TlsConIdx, &alertDescription);

      /* #40 Check if the handshake shall be canceled immediately or later when processing ServerHelloDone. */
      /* If we have a valid cert chain but with an unknown CA, we continue with the handshake. Later when processing
         the ServerHelloDone message the handshake will be canceled if the socket owner does not overrule this
         decision in the validation callback (if configured). In all other cases the handshake is canceled here
         immediately. */
      if (alertDescription == TCPIP_TLS_ALERT_DESC_UNKNOWN_CA)
      {
        TcpIp_TlsCertValidationStatusDynIterType lastCertStatusIdx;  /* status index of the last received cert in the cert chain */
        boolean lastCertIsSelfSigned;

        lastCertStatusIdx = (TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx) - 1u);
        lastCertIsSelfSigned = TcpIp_GetAddrTlsCertValidationStatusDyn(lastCertStatusIdx)->IsSelfSigned;

        if (lastCertIsSelfSigned == TRUE)
        {
          /* ok, this is an acceptable condition. Validation callback will be called when processing HelloDone. */
          cancelHandshake = FALSE;
        }
      }

      if (cancelHandshake == TRUE)
      {
        /* #50 The handshake has to be canceled immediately. Call validation callback to provide details to the socket owner. */
        TcpIp_TlsClient_TlsCertChainTriggerValidationCallback(TlsConIdx, FALSE);
      }
    }

    retVal = E_OK;
  }
  else
  {
    /* #60 TlsUpdateCertChainStatus failed, something is wrong with the certificates. Cancel the handshake. */

    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ServerCertMsgVerifyCertificateGroup */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_ValidateCertificateStatus
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_ValidateCertificateStatus(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint32 ocspResponseLength
    = TcpIp_GetServerCertStatusOcspResponseLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_TlsBufferRxIterType ocspResponseStartIdx
    = TcpIp_GetTlsBufferRxServerCertStatusOcspResponseIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  TcpIp_CertificateIdType leafCertId
    = TcpIp_GetHsLeafCertIdOfTlsConnectionDyn(TlsConIdx);

  KeyM_CertificateStatusType leafCertStatus;

  uint8 ocspResult;
  uint32 ocspResultLength = 1u;

  /* KeyM API needs a certificate name, which is not used within the API. Use some dummy value to satisfy API */
  CONST(uint8, AUTOMATIC) defaultName[8] = { "Default" };
  uint32 defaultNameLength = 7u;

  TcpIp_TlsUserErrorIdType internalErrorId = TCPIP_TLS_ERRORID_NOT_SET;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the status of the received leaf server certificate */
  if (KeyM_CertGetStatus(leafCertId, &leafCertStatus) == E_OK)
  {
    /* #20 Check that the leaf server certificate is in a valid state to process the OCSP response */
    if ((leafCertStatus == KEYM_CERTIFICATE_VALID) || (leafCertStatus == KEYM_CERTIFICATE_PARSED_NOT_VALIDATED))
    {
      /* Pointer to the received OCSP response within the TLS RxBuffer */
      TCPIP_P2C(uint8) ocspResponsePtr = TcpIp_GetAddrTlsBufferRx(ocspResponseStartIdx);

      /* #30 Process the received OCSP response */
      if (KeyM_ServiceCertificate(KEYM_SERVICE_CERT_STATUS_OCSP, &defaultName[0], defaultNameLength,
            ocspResponsePtr, ocspResponseLength, &ocspResult, ocspResultLength) == E_OK)
      {
        /* The actual status of the certificate is updated in the next step during
           TcpIp_TlsClientMsg_ExtractServerCertificateStatusInformation */

        /* #40 OCSP response successful validated - update the OCSP information and reset the asynchronous status */
        TcpIp_SetReceivedOcspResponseStatusOfTlsClientConnection(tlsClientConnectionIdx, ocspResult);
        TcpIp_SetCertificateStatusOcspValidationAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, FALSE);
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);


  /* #50 In case of any occurred error, update the error ID */
      }
      else
      {
        /* Processing of OCSP response failed - KeyM call failed */
        internalErrorId = TCPIP_TLS_ERRORID_KEYM_SERVICE_OCSP_FAILED;
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP);
      }
    }
    else
    {
      /* Leaf certificate status invalid */
      internalErrorId = TCPIP_TLS_ERRORID_KEYM_INVALIDCERTSTATUS;
    }
  }
  else
  {
    /* Get status of Leaf certificate failed - KeyM call failed */
    internalErrorId = TCPIP_TLS_ERRORID_KEYM_GETCERTIFICATESTATUS_FAILED;
  }

  /* #60 Report an error to the user when the error ID is set */
  if (internalErrorId != TCPIP_TLS_ERRORID_NOT_SET)
  {
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
      TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_VALIDATE_CERT_STATUS, internalErrorId);
  }

} /* TcpIp_TlsClientCtx_ValidateCertificateStatus() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_VerifySignatureOfPublicKey
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
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_VerifySignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TcpIp_TlsTemporarySignatureBufferStartIdxOfTlsConnectionType tlsTmpSignStartIdx =
  TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx);

  /* Retrieve the Server public key (+ Compression length) length */
  /* Public key length is checked in function TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey against its boundaries */
  uint8                   serverPubKeyParamLen = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerKeyExchangePubKeyLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), 0);

  /* Calculate size of the DH parameter */
  CONST(uint8, AUTOMATIC) dhParamLen = (serverPubKeyParamLen + TCPIP_TLS_KEYEXCH_PARAMETERLEN);
  /* Calculate the total data length for signature verification */
  VAR(uint8, AUTOMATIC)   signDataLen = (dhParamLen + TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN);
  uint8                   compFlagLen = 0;
  uint32                  signatureVerifyJobId;
  Std_ReturnType          csmRetVal;
  uint8                   serverSignLen;
  Crypto_VerifyResultType verifyResult;


  /*                                           +--> clientRndDestPtr = signDataPtr
                                               |               +--> serverRndDestPtr
                                               |               |               +--> serverKeyExchParamPtr
                                               v               v               v
   TemporarySignatureBuffer [ decoded signature | Client random | Server random | KeyExchange parameter ]
                            \                   \                                                      /
                             \                   \-----> CSM data to be verified                 <----/

   decode signature length: TCPIP_TLS_MAX_SIGNATURE_LEN
   Random length:           TCPIP_TLS_RNDLEN
   KeyExchange length:      TCPIP_TLS_KEYEXCH_PARAMETERLEN = TCPIP_TLS_KEYEXCH_CURVETYPELEN + TCPIP_TLS_KEYEXCH_CURVENAMELEN + TCPIP_TLS_KEYEXCH_PUBKEYLEN;
  */


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the CSM Job for Signature verify operation (optional parameter) is configured */
  if (TcpIp_IsCsmJobIdKeyExchangeSignatureVerifyUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {
    /* CSM Job is configured, get the JobId */
    signatureVerifyJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdKeyExchangeSignatureVerifyIdxOfTlsHandshake(activeTlsHandshakeIdx)];

    /* #20 Decode the signature if necessary and store in Temp buffer */
    if (TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature(TlsConIdx, &serverSignLen) == E_OK)
    {
      /* Helper pointers to the destination inside the tmpSignatureVerifyBuf */

      TCPIP_P2V(uint8) clientRndDestPtr      = TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx + serverSignLen);
      TCPIP_P2V(uint8) serverRndDestPtr      = TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx + serverSignLen + TCPIP_TLS_RNDLEN);
      TCPIP_P2V(uint8) serverKeyExchParamPtr = TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx + serverSignLen + TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN);
      TCPIP_P2V(uint8) serverKeyExchPubKeyParamPtr;
      TCPIP_P2C(uint8) signDataPtr;

      /* #30 Check if the compression flag is used and update the values within the temporary buffer */
      if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
      {
        /* Compression flag is used, write the values to the temporary buffer */
        TCPIP_P2V(uint8) serverKeyExchCompFlagPtr = TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx + serverSignLen + TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN + TCPIP_TLS_KEYEXCH_PARAMETERLEN);

        *serverKeyExchCompFlagPtr = TCPIP_TLS_PUBKEY_COMPRESSION_FLAG;
        compFlagLen               = TCPIP_TLS_KEYEXCH_COMPFLAGLEN;
      }

      /* update the pointer to the received server key exchange public key */
      serverKeyExchPubKeyParamPtr = TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx + serverSignLen + TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN + TCPIP_TLS_KEYEXCH_PARAMETERLEN + compFlagLen);

      /* #40 Build the data to be verified */
      /* RFC8422 - ServerKeyExchange.signed_params.sha_hash
              SHA(ClientHello.random + ServerHello.random +
                                     ServerKeyExchange.params); */ /* RFC8422 - 5.4. Server Key Exchange */
      VStdMemCpy(clientRndDestPtr, TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), TCPIP_TLS_RNDLEN); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(serverRndDestPtr, TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), TCPIP_TLS_RNDLEN); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(serverKeyExchParamPtr, TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerKeyExchangeParamsIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), TCPIP_TLS_KEYEXCH_PARAMETERLEN); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(serverKeyExchPubKeyParamPtr, TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerKeyExchangePubKeyIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), ((uint32)serverPubKeyParamLen - compFlagLen)); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* The sign data starts form the client random data */
      signDataPtr = clientRndDestPtr;

      /* #50 Call Csm Verify Signature for the server key exchange public key */
      csmRetVal = TCPIP_CSM_SignatureVerify(signatureVerifyJobId, CRYPTO_OPERATIONMODE_SINGLECALL,
        /* Pointer to the server key exchange data to be verified */
        signDataPtr, signDataLen,
        /* Pointer to the server key exchange signature */
        TcpIp_GetAddrTlsTemporarySignatureBuffer(tlsTmpSignStartIdx), serverSignLen,
        &verifyResult);


      /* #60 Check the signature verification result */
      if ((TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0,
                                              TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_VERIFY_SIGN_PUBKEY) == E_OK)
        && (verifyResult == E_OK))
      {

        /* #70 Set the async state to DONE */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
      }
      else
      {

        /* #80 handles error while async CSM processing */
        TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
          TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_VERIFY_SIGN_PUBKEY, TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED);

      }
    }
    else
    {
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }

  }
  else
  {
    /* #90 In case of an invalid configuration, report an error */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }

} /* TcpIp_TlsClientCtx_VerifySignatureOfPublicKey() */


/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            DecodedSignatureLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* if we reach this point the previous async crypto operation is done, so reset the flag */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Decode the signature based on the curve type */
  switch (TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(activeTlsHandshakeIdx))
  {
    case TCPIP_SIG_ALGO_ID_ECDSA_SECP256R1_SHA256:
    {
      *DecodedSignatureLenPtr = TCPIP_CURVE_ID_SECP256R1_SIGNATURE_LEN;
      retVal = TcpIp_TlsClientMsg_DecodeSecp256r1Signature(TlsConIdx);
      break;
    } /* case TCPIP_SIG_ALGO_ID_ECDSA_SECP256R1_SHA256 */
    case TCPIP_SIG_ALGO_ID_ECDSA_ED25519_INTRINSIC:
    {
      *DecodedSignatureLenPtr = TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN;
      retVal = TcpIp_TlsClientMsg_DecodeEd25519Signature(TlsConIdx);
      break;
    } /* case TCPIP_SIG_ALGO_ID_ECDSA_ED25519_INTRINSIC */

    default: /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */                                                               /* COV_TCPIP_MISRA */
    {
      /* Not (yet) supported algorithm
        - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA256
        - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA384
        - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA512
        - TCPIP_SIG_ALGO_ID_ECDSA_SECP384R1_SHA384
        - TCPIP_SIG_ALGO_ID_ECDSA_SECP521R1_SHA512
        - TCPIP_SIG_ALGO_ID_ECDSA_ED448_INTRINSIC
        - ...
      */
      break;
    }
  } /* switch */

  return retVal;
} /* TcpIp_TlsClientMsg_ClientKeyExchangeDecodeSignature() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_DecodeSecp256r1Signature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_DecodeSecp256r1Signature(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(uint8) decodedSignaturePtr;
  TCPIP_P2C(uint8) receivedSignatureSrcPtr;
  uint32 receivedSignatureLen;
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the length of the received signature */
  receivedSignatureLen = (uint32)IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerKeyExchangeSignatureLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), 0);

  /* Destination of decoded signature */
  decodedSignaturePtr = TcpIp_GetAddrTlsTemporarySignatureBuffer(
    TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx));

  /* Pointer to the signature in the TLS RxBuffer */
  receivedSignatureSrcPtr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerKeyExchangeSignatureIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  /* #20 Decode the received signature (remove BER encoding) */
  if (receivedSignatureLen != 0u)
  {
    if (TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature(receivedSignatureSrcPtr, receivedSignatureLen,
      TCPIP_CURVE_ID_SECP256R1_SIGN_BERELEM_LEN, decodedSignaturePtr) == E_OK)
    {
      /* Signature successfully decoded */
      retVal = E_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsClientMsg_DecodeSecp256r1Signature */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_DecodeEd25519Signature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_DecodeEd25519Signature(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TCPIP_P2V(uint8) d_Ptr = TcpIp_GetAddrTlsTemporarySignatureBuffer(
    TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx));

  TCPIP_P2C(uint8) s_Ptr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerKeyExchangeSignatureIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  uint16 receivedSignatureLen;
  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */

  /* #10 Get and check the length of the received signature */
  receivedSignatureLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerKeyExchangeSignatureLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)), 0);

  if (receivedSignatureLen == TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN)
  {
    /* #20 Copy the signature element directly into temp buffer since there is no actual decoding */
    VStdMemCpy(d_Ptr, s_Ptr, TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN);                                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsClientMsg_DecodeEd25519Signature */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_SetCsmKeys
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherStreamingModeDataType selectedStreamingMode = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the CSM keys depending on the active streaming mode of the connection */
  switch (selectedStreamingMode)
  {
    case TCPIP_TLS_STREAMING_MODE_AES_128_CBC:
    {
      /* #20 and the active MAC mode of the cipherworker */
      /* X_WITH_AES_128_CBC_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
      */
      retVal = TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

    case TCPIP_TLS_STREAMING_MODE_AES_128_GCM:
    {
      /* #30 and the active MAC mode of the cipherworker */
      /* X_WITH_AES_128_GCM_SHAX
           TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
           TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
      */
      retVal = TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

    case TCPIP_TLS_STREAMING_MODE_NULL:
    {
      /* X_WITH_NULL_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA
      */
      retVal = TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_NULL */
    default:                                                                                                             /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    {
      /* Default case left blank intentionally */
      break;
    }
  } /* switch */

  if (retVal != E_OK)
  {
    /* #40 if not so, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYS;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_SETCSMKEYS_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsClientCrypto_SetCsmKeys() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);
  TcpIp_TlsCsmKeyInfoType       keyBlockKey;
  TcpIp_TlsCsmKeyInfoType       txHMacShaKey;
  TcpIp_TlsCsmKeyInfoType       rxHMacShaKey;
  TcpIp_TlsCsmKeyInfoType       rxAesKey;
  TcpIp_TlsCsmKeyInfoType       txAesKey;
  Std_ReturnType              csmRetVal;
  /* ----- Implementation ----------------------------------------------- */
  keyBlockKey.KeyId        = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  /* keyBlockKey.KeyLen       = TcpIp_GetKeyBlockSizeOfTlsConnectionDyn(TlsConIdx); */

  /* Copy mac keys (for tx and rx) */
  /* #10 Set the TX MAC key */
  txHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  txHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txHMacShaKey);
  /* Tx MAC key --> [0...txHMacShaKey.KeyLen] (0, 0, txHMacShaKey.KeyLen) */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    0,
    0,
    txHMacShaKey.KeyLen,
    txHMacShaKey.KeyId,
    txHMacShaKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txHMacShaKey.KeyId);
  }

  /* #20 Set the RX MAC key */
  rxHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  rxHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxHMacShaKey);
  /* Rx MAC key --> [txHMacShaKey.KeyLen...(txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen)]
   * (txHMacShaKey.KeyLen, 0, rxHMacShaKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txHMacShaKey.KeyLen,
    0,
    rxHMacShaKey.KeyLen,
    rxHMacShaKey.KeyId,
    rxHMacShaKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(rxHMacShaKey.KeyId);
  }

  /* #30 Set the TX AES key */
  txAesKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
  txAesKey.KeyLen = TCPIP_TLS_AES128_KEY_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txAesKey);
  /* Tx Encrypt key --> [(txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen)...(txAesKey.KeyLen + txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen)]
   * (txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen, 0, txAesKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen,
    0,
    txAesKey.KeyLen,
    txAesKey.KeyId,
    txAesKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txAesKey.KeyId);
  }

  /* #40 Set the RX AES key */
  rxAesKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
  rxAesKey.KeyLen = TCPIP_TLS_AES128_KEY_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxAesKey);
  /* Rx Encrypt key --> [(txAesKey.KeyLen + txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen)....(txAesKey.KeyLen + rxAesKey.KeyLen + txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen)]
   * (txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen + txAesKey.KeyLen, 0, rxAesKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen + txAesKey.KeyLen,
    0,
    rxAesKey.KeyLen,
    rxAesKey.KeyId,
    rxAesKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(rxAesKey.KeyId);
  }

  return csmRetVal;
} /* TcpIp_TlsClientCrypto_SetCsmKeysAes128CbcStreaming() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);
  TcpIp_TlsCsmKeyInfoType       keyBlockKey;
  TcpIp_TlsCsmKeyInfoType       txGcmIvKey;
  TcpIp_TlsCsmKeyInfoType       rxGcmIvKey;
  TcpIp_TlsCsmKeyInfoType       rxAesKey;
  TcpIp_TlsCsmKeyInfoType       txAesKey;
  Std_ReturnType              csmRetVal;
  /* ----- Implementation ----------------------------------------------- */
  keyBlockKey.KeyId = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  /* keyBlockKey.KeyLen = TcpIp_GetKeyBlockSizeOfTlsConnectionDyn(TlsConIdx); */

  /* For Aes128Gcm the key block is parsed as below
   *  0..15  Tx encrypt key
   *  16..31 Rx encrypt key
   *  32..35 Client Iv
   *  36..40 Server Iv
   */
  /* #10 Set the TX AES key */
  txAesKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
  txAesKey.KeyLen = TCPIP_TLS_AES128_GCM_KEY_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txAesKey);
  /* Tx Encrypt key --> [0...(txAesKey.KeyLen)]
   * (0, 0, txAesKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    0,
    0,
    txAesKey.KeyLen,
    txAesKey.KeyId,
    txAesKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAEAD128GCM) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txAesKey.KeyId);
  }

  /* #20 Set the RX AES key */
  rxAesKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
  rxAesKey.KeyLen       = TCPIP_TLS_AES128_GCM_KEY_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxAesKey);
  /* Rx Encrypt key --> [(txAesKey.KeyLen)....(txAesKey.KeyLen + rxAesKey.KeyLen)]
   * (txHMacShaKey.KeyLen, 0, rxAesKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txAesKey.KeyLen,
    0,
    rxAesKey.KeyLen,
    rxAesKey.KeyId,
    rxAesKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAEAD128GCM) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(rxAesKey.KeyId);
  }

  /* #30 Set the TX GCM Iv key */
  txGcmIvKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txGcmIvKey.KeyElementId = CRYPTO_KE_CIPHER_IV;
  txGcmIvKey.KeyLen       = TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txGcmIvKey);
  /* Rx Encrypt key --> [(txAesKey.KeyLen + rxAesKey.KeyLen)....(txAesKey.KeyLen + rxAesKey.KeyLen + txGcmIvKey.KeyLen)]
   * (txAesKey.KeyLen + rxAesKey.KeyLen, 0, txGcmIvKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txAesKey.KeyLen + rxAesKey.KeyLen,
    0,
    txGcmIvKey.KeyLen,
    txGcmIvKey.KeyId,
    txGcmIvKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAEAD128GCM) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txGcmIvKey.KeyId);
  }

  /* #40 Set the RX GCM Iv key */
  rxGcmIvKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxGcmIvKey.KeyElementId = CRYPTO_KE_CIPHER_IV;
  rxGcmIvKey.KeyLen       = TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN;

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxGcmIvKey);
  /* Rx Encrypt key --> [(txAesKey.KeyLen + rxAesKey.KeyLen + txGcmIvKey.KeyLen)....(txAesKey.KeyLen + rxAesKey.KeyLen + txGcmIvKey.KeyLen + rxGcmIvKey.KeyLen)]
   * (txAesKey.KeyLen + rxAesKey.KeyLen + txGcmIvKey.KeyLen, 0, rxGcmIvKey.KeyLen)
   */
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txAesKey.KeyLen + rxAesKey.KeyLen + txGcmIvKey.KeyLen,
    0,
    rxGcmIvKey.KeyLen,
    rxGcmIvKey.KeyId,
    rxGcmIvKey.KeyElementId
  );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAEAD128GCM) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txGcmIvKey.KeyId);
  }

  return csmRetVal;
} /* TcpIp_TlsClientCrypto_SetCsmKeysAes128GcmStreaming() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);
  TcpIp_TlsCsmKeyInfoType       keyBlockKey;
  TcpIp_TlsCsmKeyInfoType       txHMacShaKey;
  TcpIp_TlsCsmKeyInfoType       rxHMacShaKey;
  Std_ReturnType              csmRetVal;
  /* ----- Implementation ----------------------------------------------- */
  keyBlockKey.KeyId        = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);

  /* Copy mac keys (for tx and rx) */
  /* #10 Set the TX MAC key */
  txHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  txHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txHMacShaKey);
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    0,
    0,
    txHMacShaKey.KeyLen,
    txHMacShaKey.KeyId,
    txHMacShaKey.KeyElementId
  );
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSNULL) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txHMacShaKey.KeyId);
  }

  /* #20 Set the RX MAC key */
  rxHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  rxHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxHMacShaKey);
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(
    keyBlockKey.KeyId,
    keyBlockKey.KeyElementId,
    txHMacShaKey.KeyLen,
    0,
    rxHMacShaKey.KeyLen,
    rxHMacShaKey.KeyId,
    rxHMacShaKey.KeyElementId
  );
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSNULL) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(rxHMacShaKey.KeyId);
  }

  return csmRetVal;
} /* TcpIp_TlsClientCrypto_SetCsmKeysNullStreaming() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientTx_SendChangeCipherSpec
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STMIF */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientTx_SendChangeCipherSpec(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
    = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  TcpIp_CipherSuiteIdOfTlsCipherDefinitionType selectedCipherSuiteId
    = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx); /* Get the corresponding Cipher Id (HexCode) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the payload (0x01) to the write index of the TLS TX CCS Buffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxCcsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx)), 0,
                    TCPIP_TLS_CHANGECIPHERSPEC);

  /* #20 Transmit the frame */
  if (TcpIp_TlsCoreRl_Transmit(TlsConIdx,
    TcpIp_GetTlsBufferTxCcsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx), TCPIP_TLS_CCSMSG_LEN, TCPIP_TLS_CT_CCS) == E_OK)
  {
    /* Reset the Transmit Flag */
    TcpIp_SetChangeCipherSpecReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, FALSE);

    /* Note, there is no need to increment the write index here, since this is the only CCS message */
    TcpIp_SetActiveCipherTxOfTlsConnectionDyn(TlsConIdx, selectedCipherSuiteId);
  }

} /* TcpIp_TlsClientTx_SendChangeCipherSpec() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_SendClientFinished
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_SendClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Prepare the ClientFinished message */
  TcpIp_TlsClientMsg_PrepareClientFinished(TlsConIdx);

  /* #20 Check the result of the preparation of the ClientFinished message. */
  if ((TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC))
  {
    /* #30 Preparation was successful. Change the state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_CCS */
    TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);
    TcpIp_SetClientFinishedReadyToSendOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_CCS);
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
  else if ((TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING))
  {
    /* #40 Preparation was not successful, an async operation is pending. Nothing to do, just leave the function. */
  }
  else
  {
    /* #50 Preparation failed. Cancel the handshake. */
    TcpIp_TlsClientHsStm_HandleErrorDuringPreparation(TlsConIdx);
  }

} /* TcpIp_TlsClientHsStm_SendClientFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_PrepareClientFinished
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
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_PrepareClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType     tlsBufferMgmtIdx       = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ClientFinished message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_DONE)         /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING))
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED:
      case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_ADD_HDR:
      {
        /* Set the start index of this message to the current write index */
        TcpIp_SetTlsBufferTxClientFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
            TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

        /* #20 Add the generic handshake header */
        TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_FINISHED);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_CALC_HASH);
        break;
      } /* case  TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_ADD_HDR */

      case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_CALC_HASH:
      {
        /* #30 Add the Finished Data */
        TcpIp_TlsClientMsg_ClientFinishedAddClientFinishedData(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_TRIGGER_TX);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_CALC_HASH */

      case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_TRIGGER_TX:
      {

        TcpIp_SetClientFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
          (TCPIP_TLS_FINISHED_VERIFYDATA_LEN + TCPIP_TLS_HSHDRLEN));

        /* #40 Write the length of the ClientFinished (12 byte) into the HS-Header */
        TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxClientFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx),
          TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

        /* #50 Enable the reception of a CCS message */
        TcpIp_SetCcsReceivableOfTlsConnectionDyn(TlsConIdx, TRUE);
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_DONE);
        break;
      } /* case TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_TRIGGER_TX */

      default:                                                                                                         /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      /* Default case left blank intentionally */
        break;
    } /* switch () */
  } /* while ( ) */

} /* TcpIp_TlsClientMsg_PrepareClientFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ClientFinishedAddClientFinishedData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_ClientFinishedAddClientFinishedData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);


  /* ----- Implementation ----------------------------------------------- */
  /* Save the position of the verify data (will be set inside the async context function) */
  TcpIp_SetTlsBufferTxClientFinishedVerifyDataIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* Increment the write index by the consumed length (12 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsClientConnection(tlsClientConnectionIdx, TRUE);
  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

}

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_CalcClientFinishedHash
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
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal       = E_NOT_OK;
  uint16         localErrorId = TCPIP_TLS_ERRORID_NOT_SET;                                                              /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  uint8          calcVerifyData[TCPIP_TLS_FINISHED_VERIFYDATA_LEN] = { 0 };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the hash which is needed for the finished data */
  if (TcpIp_TlsClientCrypto_GenerateHsHash(TlsConIdx, TCPIP_TLS_MSG_HASH_CLIENT_FINISHED) == E_OK)
  {
    /* #20 If it is successful, calculate the finished data and store it directly into Tx buffer */
    if (TcpIp_TlsClientCrypto_CalcHsFinishedData(TlsConIdx, TCPIP_TLS_MSG_HASH_CLIENT_FINISHED, calcVerifyData) == E_OK)
    {
      TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
        = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

      TCPIP_P2V(uint8) targetPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientFinishedVerifyDataIdxOfTlsClientBufferMgmt(
        tlsClientBufferMgmtIdx));

      VStdMemCpy(targetPtr, calcVerifyData, TCPIP_TLS_FINISHED_VERIFYDATA_LEN);                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);

      /* No error set */
      retVal = E_OK;
    }
    else
    {
      /* Error derive key block failed */
      localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_VERIFY_FAILED;
    }
  }
  else
  {
    /* Error derive key block failed */
    localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_HASH_FAILED;
  }

  /* #30 If all sub-functions returned E_OK */
  if (retVal != E_OK)
  {
    /* #40 Copy the result into the TLS temp buffer and set the state to ASYNC_DONE */

    /* Set the async state to DONE */
    /* #50 otherwise, handles error while async CSM processing */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_CLIENTFINISHED_HASH,
                                                    localErrorId);
  }
} /* TcpIp_TlsClientCtx_CalcClientFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(uint32, TCPIP_CODE) TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen(
  TcpIp_TlsConnectionIterType     TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32                               serverRxLen            = 0u;
  TcpIp_TlsKeyExchangeMethodDataType   keyExchangeMethod      = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the selected cipher, calculate the length of the received server Hs messages */
  switch (keyExchangeMethod)
  {
    case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
    {
      TcpIp_TlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmtType serverKeyExchangeIdx =
              TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

      /* Check if we received a ServerKeyExchange Message (PSK-Hint) */
      if (serverKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
      {
        serverRxLen = ((uint32)TcpIp_GetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
          + TcpIp_GetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
          + TcpIp_GetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN);
      }
      else
      {
        /* Otherwise, plain PSK */
        serverRxLen = ((uint32)TcpIp_GetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
          + TcpIp_GetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN);
      }
      break;
    }
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
    {
      serverRxLen = ((uint32)TcpIp_GetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
        + TcpIp_GetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
        + TcpIp_GetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN);

      if (TcpIp_GetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
            != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* Add length of received Server Certificate status message */
        serverRxLen += ((uint32)TcpIp_GetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          + TCPIP_TLS_HSHDRLEN);
      }

      if (TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
        != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* Add length of received Server Certificate Request message */
        serverRxLen += ((uint32)TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          + TCPIP_TLS_HSHDRLEN);
      }

      break;
    }
    case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
    {
      serverRxLen = ((uint32)TcpIp_GetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
        + TcpIp_GetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
        + TcpIp_GetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN
        + TcpIp_GetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx) + TCPIP_TLS_HSHDRLEN);

      if (TcpIp_GetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
        != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* Add length of received Server Certificate status message */
        serverRxLen += ((uint32)TcpIp_GetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          + TCPIP_TLS_HSHDRLEN);
      }

      if (TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
        != TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
      {
        /* Add length of received Server Certificate Request message */
        serverRxLen += ((uint32)TcpIp_GetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          + TCPIP_TLS_HSHDRLEN);
      }

      break;
    }
#  endif
    default:
    {
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      break;
    }
  }

  return serverRxLen;
} /* TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_GenerateHsHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_GenerateHsHash(
  TcpIp_TlsConnectionIterType     TlsConIdx,
  TcpIp_TlsMessageFinishedType    FinishedMessageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType csmRetVal;
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  uint32 csmHashJobId = TcpIp_GetHashVerifyJobIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 expectedHashLen = TCPIP_TLS_HASH_SHA256_LEN;
  uint32 clientHelloLen;
  uint32 clientTxLen;
  uint32 serverRxLen;
  TCPIP_P2C(uint8) clientHelloPtr;
  TCPIP_P2C(uint8) clientTxPtr;
  TCPIP_P2C(uint8) serverRxPtr;
  /* Hash shall be stored into the Tls temp buffer and used to generate the finished data */
  TCPIP_P2V(uint8) hsHashDestPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));
  uint32 hsHashDestSpace = TcpIp_GetTlsTemporaryFinishedBufferEndIdxOfTlsConnection(TlsConIdx)
                           - (uint32)TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx);

  /* Calculate Hash over
   *  ClientHello + ClientKeyExchange (+ ClientFinished)
   *  ServerHello (+ ServerCertificate + ServerKeyExchange) + ServerHelloDone
   */

  /* #10 Get buffer pointer to the transmitted Client Hello message to be used for hash generation */
  clientHelloPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));
  clientHelloLen = TcpIp_GetClientHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  /* #20 Get buffer pointer to the received server handshake messages to be used for hash generation */
  serverRxPtr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));
  serverRxLen = TcpIp_TlsClientCrypto_CalculateReceivedServerHsMsgLen(TlsConIdx);

  /* #30 Set the start of the hash for the transmit buffer, depending on the transmitted messages */
  if (TcpIp_GetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
        != TCPIP_NO_TLSBUFFERTXCLIENTCERTIFICATEIDXOFTLSCLIENTBUFFERMGMT)
  {
    /* Certificate message transmitted, start of TX buffer is the Client Certificate message */
    clientTxPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientCertificateIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));
  }
  else
  {
    /* No Certificate message transmitted, start of TX buffer is the Client Key Exchange message */
    clientTxPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));
  }

  /* Depending on Client hash / Server hash, also consider the Client finished message length */
  if (FinishedMessageType == TCPIP_TLS_MSG_HASH_SERVER_FINISHED)
  {
    /* For server finished, consider till client finished message */
    clientTxLen = (uint32)TcpIp_GetClientKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
                  + TcpIp_GetClientFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  }
  else /* FinishedMessageType == TCPIP_TLS_MSG_HASH_CLIENT_FINISHED */
  {
    /* For client finished, only consider till client key exchange message */
    clientTxLen = TcpIp_GetClientKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  }

  /* This length is 0, if no certificate message is transmitted */
  clientTxLen += TcpIp_GetClientCertificateLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);


  /* ----- Implementation ----------------------------------------------- */
  /* #40 Start hash generation and consume all the handshake message data (excluding CCS) */
  csmRetVal = TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_START | CRYPTO_OPERATIONMODE_UPDATE, clientHelloPtr,
                       clientHelloLen, NULL_PTR, NULL_PTR);
  csmRetVal |= TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_UPDATE, serverRxPtr, serverRxLen, NULL_PTR,
                        NULL_PTR);
  csmRetVal |= TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, clientTxPtr,
                        clientTxLen, hsHashDestPtr, &hsHashDestSpace);

  /* Check if the CSM operation succeeded */
  (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, hsHashDestSpace, expectedHashLen,
                                           TCPIP_TLS_FCTID_CLIENT_CRYPTO_CALCHSFINISHEDHASH);
  /* User error handling is done outside of this function */

  return csmRetVal;
} /* TcpIp_TlsClientCrypto_GenerateHsHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCrypto_CalcHsFinishedData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientCrypto_CalcHsFinishedData(
  TcpIp_TlsConnectionIterType    TlsConIdx,
  TcpIp_TlsMessageFinishedType   FinishedMessageType,
  TCPIP_P2V(uint8)               ResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TCPIP_P2C(uint8) labelPtr = &TcpIp_Tls_Hs_FinishedLabel[FinishedMessageType][0];
  TCPIP_P2C(uint8) seedPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  TcpIp_TlsCsmKeyInfoType msKey;
  TcpIp_TlsCsmKeyInfoType resultKey;
  Std_ReturnType        csmRetVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Retrieve master shared secret to local key element */
  msKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdMasterSecretIdxOfTlsHandshake(activeTlsHandshakeIdx)];
  msKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  msKey.KeyLen       = TCPIP_TLS_MASTER_SECRET_LEN;

  /* Retrieve Prf result key (contains result of verify data) to local key element */
  resultKey.KeyId        = TcpIp_GetPrfResultPublicKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  resultKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  resultKey.KeyLen       = TCPIP_TLS_FINISHED_VERIFYDATA_LEN;

  /* #10 Calculate the Prf using the Hash, Master secret and label */
  if (   TcpIp_TlsCoreCrypto_Prf(TlsConIdx, &resultKey, &msKey, labelPtr, seedPtr, TCPIP_TLS_LABEL_FINISHED_LEN, 32u, FALSE)
      == E_OK)
  {
    /* #20 Write the calculated finished data (stored in CSM Key) into destination buffer */
    uint32 tmpLen = resultKey.KeyLen;
    csmRetVal = TCPIP_CSM_KeyElementGet(resultKey.KeyId, resultKey.KeyElementId, &ResultPtr[0], &tmpLen);

    /* #30 Check if the CSM operation succeeded */
    (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, tmpLen, resultKey.KeyLen,
            TCPIP_TLS_FCTID_CLIENT_CRYPTO_CALCHSFINISHEDDATA);
    /* User error handling is done outside of this function */
  }

  return csmRetVal;
} /* TcpIp_TlsClientCrypto_CalcHsFinishedData() */

/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerFinished
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
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerFinished(
   TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxServerFinishedIdxOfTlsClientBufferMgmtType serverFinishedIdx =
    TcpIp_GetTlsBufferRxServerFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  Std_ReturnType retVal = E_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a handshake message with the type ServerFinished */
  if (serverFinishedIdx != TCPIP_NO_TLSBUFFERRXSERVERFINISHEDIDXOFTLSCLIENTBUFFERMGMT)
  {
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* #20 Extract the ServerFinished message until we are done AND no Async context needs to be computed */
    while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_DONE)   /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
               /* Async operation is trigged (performed in lowPrio task - leave this context */
           && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
               /* Error during processing of the data - skip further data handling */
           && (retVal == E_OK))
    {
      switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
      {
        case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED:
        {
          /* #30 Extract the Verify Data value from the message */
          retVal = TcpIp_TlsClientMsg_ExtractServerFinishedInformation(TlsConIdx);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_HASH);
          break;
        }

        case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_HASH:
        {
          /* #40 Trigger calculation of Hash */
          TcpIp_TlsClientMsg_CalcServerFinishedHash(TlsConIdx);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_FINISHED);

          /* This operation is processed within the lowPrio function, which means that we are leaving
             this context and return when the operation is DONE */
          break;
        }

        case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_FINISHED:
        {
          /* #50 Trigger calculation of PRF value from the hash */
          TcpIp_TlsClientMsg_CalcServerFinishedVerifyData(TlsConIdx);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_VERIFY);

          /* This operation is processed within the lowPrio function, which means that we are leaving
             this context and return when the operation is DONE */
          break;
        }

        case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_VERIFY:
        {
          /* #60 Compare the calculated and received value */
          retVal = TcpIp_TlsClientMsg_CompareFinishedVerifyData(TlsConIdx);
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_DONE);
          break;
        }

        case TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_DONE:
        {
          /* #70 Client finished message has been verified, move to next step */
          break;
        }

        default:                                                                                                         /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
        /* Default case left blank intentionally */
          break;
      }
    }
  }
  else
  {
    /* #80 otherwise, we receive an unexpected message, so trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }

  return retVal;
} /* TcpIp_TlsClientHsStm_ParseServerFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_ExtractServerFinishedInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_ExtractServerFinishedInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxServerFinishedVerifyDataIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxServerFinishedIdxOfTlsClientBufferMgmtType rxServerFinishedStartIdx
    = TcpIp_GetTlsBufferRxServerFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* rxServerFinishedStartIdx is pointing to the start of the received ServerFinished message, therefore offset of 1 byte is pointing to the 24 byte length */
  uint32 rxServerFinishedVerifyDataLen = IpBase_GetUint24(
    TcpIp_GetAddrTlsBufferRx(rxServerFinishedStartIdx), TCPIP_TLS_CONTENT_LENGTH_OFFSET);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received 12 bytes of data (Finished message length) and store the information */
  if (rxServerFinishedVerifyDataLen == TCPIP_TLS_FINISHED_VERIFYDATA_LEN)
  {
    /* Save the position of the received ClientFinishedVerifyData */
    TcpIp_SetTlsBufferRxServerFinishedVerifyDataIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxServerFinishedVerifyDataIdx);

    /* Increment the Rx buffer ReadIdx by the length of the VerifyData (12Byte) */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

    retVal = E_OK;
  }
  else
  {
    /* If an error occurs report the error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERFINISHED;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    /* #20 Trigger alert TCPIP_TLS_ALERT_DESC_DECODE_ERROR in case of invalid length */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }

  return retVal;
} /* TcpIp_TlsClientMsg_ExtractServerFinishedInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_CalcServerFinishedHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsClientConnection(
    TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx), TRUE);
  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_CalcServerFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_CalcServerFinishedVerifyData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsg_CalcServerFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcServerFinishedVerifyDataAsyncFlagOfTlsClientConnection(
    TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx), TRUE);
  /* Set the state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsClientMsg_CalcServerFinishedVerifyData() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientMsg_CompareFinishedVerifyData
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClientMsg_CompareFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Calculated data is present in Temp buffer */
  TCPIP_P2C(uint8) calcVerifyDataPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(
    TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  TCPIP_P2C(uint8) rxVerifyDataPtr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxServerFinishedVerifyDataIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  /* #10 Compare the calculated finished value and the received finished value */
  if (IpBase_StrCmpLen(rxVerifyDataPtr, calcVerifyDataPtr, TCPIP_TLS_FINISHED_VERIFYDATA_LEN) == E_OK)
  {
    retVal = E_OK;
  }
  else
  {
    /* If an error occurs report the error to the user */
    TcpIp_TlsUserErrorType userError;
    userError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERFINISHED;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTVERIFYDATA;
    userError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);

    /* #20 Trigger alert TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR in case of invalid length */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR);

    retVal = E_NOT_OK;
  }
  return retVal;
} /* TcpIp_TlsClientMsg_CompareFinishedVerifyData */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_CalcServerFinishedHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the hash which is needed for the finished data */
  if (TcpIp_TlsClientCrypto_GenerateHsHash(TlsConIdx, TCPIP_TLS_MSG_HASH_SERVER_FINISHED) == E_OK)
  {
    /* #20 If the operation was successful, set the async state to DONE */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
  }
  else
  {
    /* #30 if the operation was not successful, handle the error while an ongoing async CSM processing */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_SERVERFINISHED_HASH,
      TCPIP_TLS_ERRORID_CRYPTO_SERVERFINISHED_HASH_FAILED);
  }

} /* TcpIp_TlsClientCtx_CalcServerFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientCtx_CalcServerFinishedVerifyData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsClientCtx_CalcServerFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Pointer to the temporary buffer that stores the verify data */
  TCPIP_P2V(uint8) targetPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(
    TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the finished data, store it in temp buffer and update the state */
  if (TcpIp_TlsClientCrypto_CalcHsFinishedData(TlsConIdx, TCPIP_TLS_MSG_HASH_SERVER_FINISHED, targetPtr) == E_OK)
  {

    /* Set the async state to DONE */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
  }
  else
  {
    /* #20 Error during calculation of finished data. Report error to the user */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_SERVERFINISHED_VERIFY,
      TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_VERIFY_FAILED);
  }

} /* TcpIp_TlsClientCtx_CalcServerFinishedVerifyData() */

/**********************************************************************************************************************
*  TcpIp_TlsClientHsStm_ParseServerCcs
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_ParseServerCcs(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a CCS message */
  if (TcpIp_IsCcsRxIndicationOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    /* #20 Change the state to TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED */
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED);
    TcpIp_SetCcsRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
    /* #30 Lock the reception of a new CCS message after this point */
    TcpIp_SetCcsReceivableOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
  else
  {
    /* #40 Trigger the transmission of the occurred alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsClientHsStm_ParseServerCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_VerifyServerFinished
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
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_VerifyServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Parse and verify the Server Finished message */
  retVal = TcpIp_TlsClientHsStm_ParseServerFinished(TlsConIdx);

  /* #20 Check the result of the ServerFinished parsing */
  if (retVal == E_OK)
  {
    /* #30 Message successfully parsed - Check if there are async operation pending */
    if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
    {
      /* #40 Async operation is pending. Nothing to do, just leave the function. */
    }
    else
    {
      /* #50 No async operation pending. Change the state to TCPIP_TLS_STATE_HANDSHAKE_DONE */
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_DONE);
      TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
    }
  }
  else
  {
    /* #60 Parsing failed. Cancel the handshake. */
    TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
  }

} /* TcpIp_TlsClientHsStm_VerifyServerFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsClientHsStm_FinalizeHandshake
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientHsStm_FinalizeHandshake(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If configured, overwrite all data in the TLS TxBuffer with zeros (from start index to current write position) */
  /* The TX Read index is not used during handshake, so set it to the current position of the Write index */
  TcpIp_SetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  if (TcpIp_IsTlsClearBufferAfterHandshakeOfTlsConfig(TCPIP_TLSCONFIG_IDX) == TRUE)
  {
    TcpIp_TlsCoreBuffer_ClearTxBuffer(TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx),
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
  /* #20 If configured, overwrite all data in the TLS RxBuffer with zeros (from start index to current read position) */
  /* The Rx Write index is not used during handshake, so set it to the current position of the read index */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));

  if (TcpIp_IsTlsClearBufferAfterHandshakeOfTlsConfig(TCPIP_TLSCONFIG_IDX) == TRUE)
  {
    TcpIp_TlsCoreBuffer_ClearRxBuffer(TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx),
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
  /* Reset both RxBuffer read indexes to the buffer start index. */
  /* Reset the readIdx to current writeIdx */
  TcpIp_SetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Reset the readIdx to current writeIdx */
  TcpIp_SetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Reset UlRxIndication level */
  TcpIp_SetAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
  /* Reset TLS Rx Ad fill level */
  TcpIp_SetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);

  /* #30 Set the connection state to established and inform the upper layer via the TcpConnected callout */
  TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_ESTABLISHED);

  TcpIp_TlsCoreUl_TcpConnected(TlsConIdx);


} /* TcpIp_TlsClientHsStm_FinalizeHandshake() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsClient_ResetCertChainStates
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ResetCertChainStates(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;

  TcpIp_TlsClientConnectionIterType tlsClientConnectionIdx
    = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear all certificate statuses */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx);
       certStatusIdx < TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx);
       certStatusIdx++)
  {
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertId         = TCPIP_CERTID_INV;
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatus     = KEYM_CERTIFICATE_NOT_AVAILABLE;
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->IsSelfSigned   = FALSE;

    /* Ocsp information */
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatusResponse.OcspCertStatus = KEYM_CERTIFICATE_NOT_AVAILABLE;
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatusResponse.OcspMode = TCPIP_TLS_OCSP_MODE_NONE;
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatusResponse.OcspResponseStatus = TCPIP_TLS_OCSP_RESPONSE_STATUS_INVALID;
    TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertStatusResponse.OcspConnectionState = TCPIP_TLS_OCSP_CONNECTION_STATE_INACTIVE;
  }

  /* Reset the groupId for the connection */
  TcpIp_SetHsCertGroupIdOfTlsConnectionDyn(TlsConIdx, TCPIP_CERTGROUPID_INV);

  /* Reset the leaf cert Id */
  TcpIp_SetHsLeafCertIdOfTlsConnectionDyn(TlsConIdx, TCPIP_CERTID_INV);

  /* Reset overall validation result */
  TcpIp_SetTlsCertValidationResultOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_VALIDATION_UNKNOWN);

  /* Reset the valid end idx of the certificate chain struct */
  TcpIp_SetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx,
    TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx));

  /* Initialize the process state of the remote certificate chain */
  /* [HS Server Certificate Chain Handling StM] Init state, no certificates received */
  TcpIp_SetHsCertStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CERTCHAIN_INIT);

  /* Reset OCSP values */
  TcpIp_SetReceivedOcspResponseStatusOfTlsClientConnection(tlsClientConnectionIdx, TCPIP_TLS_OCSP_RESPONSE_STATUS_INVALID);

  TcpIp_SetMandatoryReceivedCertificateStatusRequestExtensionOfTlsConnectionDyn(TlsConIdx, FALSE);

  TcpIp_SetExpectServerCertificateStatusMessageOfTlsConnectionDyn(TlsConIdx, FALSE);


} /* TcpIp_TlsClient_ResetCertChainStates */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_ResetConnection
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
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsClient_ResetConnection(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* #10 Initialize the handshake message indices */
  TcpIp_TlsClient_InitHsMsgIndices(TlsConIdx);

  /* #20 Initialize the handshake length information */
  TcpIp_TlsClient_InitHsLenInformation(TlsConIdx);

  /* #30 Initialize the ready to send flags */
  TcpIp_TlsClient_InitReadyToSendFlags(TlsConIdx);

  /* #40 Initialize the async context flags */
  TcpIp_TlsClient_InitAsnycFlags(TlsConIdx);

  /* #50 Initialize the core async context flags */
  TcpIp_TlsCore_InitAsnycFlags(TlsConIdx);

  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_HELLO);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  /* #60 Reset the certificate information for the handshake */
  {
    TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod
      = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

    if (   (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE)
        || (keyExchangeMethod == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH))
    {
      TcpIp_TlsCore_RemoveLoadedCerts(TlsConIdx);
      TcpIp_TlsClient_ResetCertChainStates(TlsConIdx);
    }
  }
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

} /* TcpIp_TlsClient_ResetConnection() */

/**********************************************************************************************************************
 *  TcpIp_TlsClient_GetRootCertificateId
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsClient_GetRootCertificateId(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2V(uint16)             CertIdPtr                                                                               /* PRQA S 3673 */ /* MD_TCPIP_Rule8.13_CfgSpecific */
)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  KeyM_CertificateIdType issuerCertId;
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;
  TCPIP_P2C(TcpIp_CertValidationStatusType) certStatusPtr;

  *CertIdPtr = TCPIP_CERTID_INV;

  /* ----- Implementation ----------------------------------------------- */
  /* Get the ID of the last certificate in the received chain. */
  certStatusIdx = TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx) - 1u;
  certStatusPtr = TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx);

  /* #10 Check if the certificate is self signed. */
  if (certStatusPtr->IsSelfSigned == FALSE)
  {
    /* #20 Check if the certificate is valid and return the ID of the issuer certificate. */
    if ((certStatusPtr->CertStatus == KEYM_CERTIFICATE_VALID))
    {
      retVal = KeyM_GetIssuerCertId(certStatusPtr->CertId, &issuerCertId);

      *CertIdPtr = issuerCertId;
    }
    else
    {
      /* Nothing to do here. Return E_NOT_OK and set CertIdPtr to TCPIP_CERTID_INV. */
    }
  }
  else
  {
    /* Nothing to do here. Return E_NOT_OK and set CertIdPtr to TCPIP_CERTID_INV. */
  }
#  else
   TCPIP_DUMMY_STATEMENT_CONST(TlsConIdx);                                                                              /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
   TCPIP_DUMMY_STATEMENT_CONST(CertIdPtr);                                                                              /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
  return retVal;
}

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  MSA - Master Secret Access
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint8 sessionIdLen = TcpIp_GetServerHelloSessionIdLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx);
  TCPIP_P2C(uint8) sessionIdSrcPtr
    = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerSessionIdIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  TCPIP_P2V(uint8) sessionIdDstPtr
    = TcpIp_GetAddrTlsClientSessionIdAccessBuffer(TcpIp_GetTlsClientSessionIdAccessBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make received sessionID accessible for MSA readout */
  /* Set the actual received SessionID length and copy the sessionID to the MSA_AccessBuffer */
  TcpIp_SetClientSessionIdAccessBufferLenOfTlsConnectionDyn(TlsConIdx, sessionIdLen);
  if (sessionIdLen != 0u)
  {
    /* Copy from the SessionId start IDX (inside of the TLS RX-Buffer) to the AccessBuffer */
    VStdMemCpy(sessionIdDstPtr, sessionIdSrcPtr, sessionIdLen);                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }
} /* TcpIp_TlsClientMsa_AddServerSessionIdToAccessBuffer() */

/**********************************************************************************************************************
 * TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TCPIP_P2C(uint8) clientRndSrcPtr
    = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

  TCPIP_P2V(uint8) clientRndDstPtr
    = TcpIp_GetAddrTlsClientRandomAccessBuffer(TcpIp_GetTlsClientRandomAccessBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make received ClientRandom value accessible for MSA readout */
  /* Copy random value (stored inside of TLS TxBuffer) to the AccessBuffer */
  VStdMemCpy(clientRndDstPtr, clientRndSrcPtr, TCPIP_TLS_RANDOM_LEN);                                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

} /* TcpIp_TlsClientMsa_AddClientRandomToAccessBuffer() */
#  endif

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/

# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
#endif /*(TCPIP_SUPPORT_ASRTLS == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsClient.c
 *********************************************************************************************************************/
