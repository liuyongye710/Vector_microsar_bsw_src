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
/*!     \file  TcpIp_TlsPriv.h
 *      \brief Transport Layer Security (TLS) private functions implementation.
 *
 *   \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TLS_PRIV_H)
# define TCPIP_TLS_PRIV_H

# include "TcpIp_Cfg.h"
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "TcpIp_Lcfg.h"
#  include "TcpIp_Tls.h"
#  include "TcpIp_TlsCore.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#  define TCPIP_TLS_CONNECTION_ID_TO_IDX(TLS_CONNECTION_ID)   ((TcpIp_SizeOfTlsConnectionType)(TLS_CONNECTION_ID))
#  define TCPIP_TLS_CONNECTION_IDX_TO_ID(TLS_CONNECTION_IDX)  ((TcpIp_TlsConnectionIdType)(TLS_CONNECTION_IDX))

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{

  uint16 Type;                          /* Extension type */
  uint16 Length;                        /* Extension length */
  TcpIp_TlsBufferRxIterType StartIdx;   /* Extension Start index to the TlsRxBuffer */

} TcpIp_TlsExtensionType; /* Used as internal interpretation of the received Tls Extensions */


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * TcpIp_TlsMsg_AddHsHdr
 *********************************************************************************************************************/
/*! \brief         Writes the TLS handshake type to the start of the transmittable TLS handshake message
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      HsType                  Type of handshake message
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_AddHsHdr(
  TcpIp_TlsConnectionIterType                 TlsConIdx,
  CONST(TcpIp_TlsMsgHandshakeType, AUTOMATIC) HsType);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_AddProtocolVersionNr
 *********************************************************************************************************************/
/*! \brief         Writes the TLS major and TLS minor version number to the TLS handshake header
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddProtocolVersionNr(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_AddRandomStructure
 *********************************************************************************************************************/
/*! \brief         Write the TLS HelloMessage random structure to the transmittable TLS handshake message
 *  \details       Generates random value to be used for Hello handshake message
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Operation successful
 *  \return        E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructure(
  TcpIp_TlsConnectionIterType              TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_AddRandomStructureGetTime
 *********************************************************************************************************************/
/*! \brief         Add the TLS UNIX time stamp to the TLS HelloMessage random structure.
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructureGetTime(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_AddRandomStructureGetRandom
 *********************************************************************************************************************/
/*! \brief         Generate and add the random value to the TLS HelloMessage random structure
 *  \details       -
 *  \param[in]      TlsConIdx                   TLS connection index
 *                                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                         Operation successful
 *  \return        E_NOT_OK                     Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructureGetRandom(
  TcpIp_TlsConnectionIterType              TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_AddSessionId
 *********************************************************************************************************************/
/*! \brief         Add the SessionID to the TLS HelloMessage random structure
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddSessionId(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_ExtractReceivedExtensions
 *********************************************************************************************************************/
/*! \brief         Extract all received hello extension from TLS-RxBuffer into separated list
 *  \details       -
 *  \param[in]     TlsConIdx       TLS connection index
 *                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ExtensionsLen   Length of the extensions data
 *  \param[in]     HelloEndIdx     End idx of the hello message
 *  \param[in]     ReceivedExtensionListPtr  Pointer to the list of received hello extensions
 *  \param[in,out] ReceivedExtensionCntPtr   Number of received hello extensions
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_ExtractReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 ExtensionsLen,
  TcpIp_TlsBufferRxIterType HelloEndIdx,
  TCPIP_P2V(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  TCPIP_P2V(uint8) ReceivedExtensionCntPtr);

/**********************************************************************************************************************
 * TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions
 *********************************************************************************************************************/
/*! \brief         Checks the list of received hello extensions for duplicated entries
 *  \details       -
 *  \param[in]     ReceivedExtensionListPtr  Pointer to the list of received hello extensions
 *  \param[in]     ReceivedExtensionCnt      Number of received hello extensions
 *  \return        E_OK            Operation successful
 *  \return        E_NOT_OK        Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions(
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_AddLenToHsHdr
 *********************************************************************************************************************/
/*! \brief         Update the TLS handshake header with the given length information
 *  \details       -
 *  \param[in]     Length                   Length information which should be written to the TLS handshake header
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_AddLenToHsHdr(
  TcpIp_TlsBufferTxIterType   HsHdrStartIdx,
  CONST(uint32, AUTOMATIC)    Length);

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsHs_CheckExpectedMsgLen
 *********************************************************************************************************************/
/*! \brief         Compares the actual message length with the expected message length
 *  \details       -
 *  \param[in]     MsgLen                   Actual message length
 *  \param[in]     ExpectedMsgLen           Expected message length
 *  \return        E_OK                     if MsgLen is equal to ExpectedMsgLen
 *  \return        E_NOT_OK                 if MsgLen is NOT equal to ExpectedMsgLen
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHs_CheckExpectedMsgLen(
  CONST(uint32, AUTOMATIC) MsgLen,
  CONST(uint32, AUTOMATIC) ExpectedMsgLen);
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsHsStm_ErrorHandlingAndStateTransition
 *********************************************************************************************************************/
/*! \brief         Change the state of the TLS state machine depending on the given internal function return value
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     IntRetVal               Return value of previous called internal function, either E_OK or E_NOT_OK
 *  \param[in]     NextHsState             Next state of TLS state machine if IntRetVal is E_OK
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsHsStm_ErrorHandlingAndStateTransition(
  TcpIp_TlsConnectionIterType      TlsConIdx,
  Std_ReturnType                   IntRetVal,
  TcpIp_TlsHandshakeState          NextHsState);

/**********************************************************************************************************************
 * TcpIp_TlsHsStm_HandlesUnexpectedHsInformation
 *********************************************************************************************************************/
/*! \brief         Handles unexpected TLS handshake information during TLS handshake
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_HelloMsgGetVersionNr
 *********************************************************************************************************************/
/*! \brief         Checks the received TLS major and TLS minor version number
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     if correct version numbers received
 *  \return        E_NOT_OK                 if incorrect version numbers received
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetVersionNr(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_HelloMsgGetRandom
 *********************************************************************************************************************/
/*! \brief         Checks the received random data within the TLS handshake HelloMessage
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      HelloEndIdx             End index of the random data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetRandom(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_HelloMsgGetSessionId
 *********************************************************************************************************************/
/*! \brief         Checks the received sessionId data within the TLS handshake HelloMessage
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      HelloEndIdx             End index of the random data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetSessionId(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) HelloEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_SelectMatchingCipherSuiteId
 *********************************************************************************************************************/
/*! \brief         Checks the receives CipherSuite list and store the matching one as active for this TLS connection
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CipherSuiteSelected      ID of the selected ciphersuite
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_SelectMatchingCipherSuiteId(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_CipherSuiteIdOfTlsCipherDefinitionType, AUTOMATIC) CipherSuiteSelected);


/**********************************************************************************************************************
 * TcpIp_TlsMsg_SelectDefaultHandshakeReference
 *********************************************************************************************************************/
/*! \brief         Select the first handshake reference as active one
 *  \details       The first handshake reference is only used in case of ECDH or PSK. In case of ECDHE the selection is
 *                 performed via the received curve type.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_SelectDefaultHandshakeReference(
  TcpIp_TlsConnectionIterType  TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)

/**********************************************************************************************************************
 * TcpIp_TlsMsg_SelectDefaultPskIdentity
 *********************************************************************************************************************/
/*! \brief         Select the configured default PSK identity as active
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_SelectDefaultPskIdentity(
  TcpIp_TlsConnectionIterType  TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
/**********************************************************************************************************************
 * TcpIp_TlsMsg_CheckMsgForRemainingData
 *********************************************************************************************************************/
/*! \brief         Checks if there are remaining data in the received TLS handshake message
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      HelloEndIdx             End index of the random data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_CheckMsgForRemainingData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) HelloEndIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/***********************************************************************************************************************
 *  TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature
 **********************************************************************************************************************/
/*! \brief       Remove all BER-coding from an ECDSA signature
 *  \details     -
 *  \param[in]   SignInputPtr        Pointer to the BER encoded signature
 *  \param[in]   SignInputLen        Length of the BER encoded signature
 *  \param[in]   SignCoordinateSize  Length of one coordinate element
 *  \param[out]  SignOutputPtr       Pointer to the buffer where the processed signature shall be stored
 *  \return      E_OK               Successful
 *               E_NOT_OK           Failed
 *  \pre         The buffer provided to SignOutputPtr must have a minimum length of 2 * SignCoordinateSize
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 **********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature(
  TCPIP_P2C(uint8) SignInputPtr,
  uint32 SignInputLen,
  uint8 SignCoordinateSize,
  TCPIP_P2V(uint8) SignOutputPtr);

#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
#endif /* TCPIP_TLS_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsClient.h
 *********************************************************************************************************************/

