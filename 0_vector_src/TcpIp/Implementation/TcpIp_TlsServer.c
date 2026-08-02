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
/*!        \file  TcpIp_TlsServer.c
 *        \brief  Transport Layer Security (TLS) Server functions implementation.
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#define TCPIP_TLSSERVER_SOURCE
#include "TcpIp_Cfg.h"

#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "TcpIp_Lcfg.h"
#  include "TcpIp_Tls.h"
#  include "TcpIp_TlsServer.h"
#  include "TcpIp_TlsCore.h"
#  include "TcpIp_TlsPriv.h"
#  include "TcpIp_Tcp.h"
#  include "Csm.h"

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
#   if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_OFF)
#    include "KeyM.h"
#   endif
#  endif

#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
#   include "Det.h"
#  endif



/* Global review findings: */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Naming is wrong.The message is called "finished", not "finished". Rename all comments, variables and functions. VS-Regex: finished(?!ed) */
/* [REVIEW_c] comment visbdk: See TCPIP-5700. */
/* [REVIEW_c] accepted visal, visbdk 16.03.00.0 Statement: Story is implemented, OK. */
#  endif




/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#  define TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG 0x04u
#  define TCPIP_TLSSERVER_CERTLEN_LEN 3u
#  define TCPIP_TLSSERVER_CURVETYPE_LEN 1u
#  define TCPIP_TLSSERVER_CUVEID_LEN 2u
#  define TCPIP_TLSSERVER_PUPKEY_COMPRESSION_LEN 1u
#  define TCPIP_TLSSERVER_PUBKEY_NO_COMPRESSION_LEN 0u
#  define TCPIP_TLSSERVER_PUPKEYLEN_LEN 1u
#  define TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG_LEN 1u
#  define TCPIP_TLSSERVER_SIGNATUREALGO_ID_LEN 2u
#  define TCPIP_TLSSERVER_SIGNATURELEN_LEN 2u
#  define TCPIP_TLSSERVER_COMPMETH_LEN 1u
#  define TCPIP_TLSSERVER_COMPMETHLEN_LEN 1u

/* Length of Client/Server Finished length */
#  define TCPIP_TLS_LABEL_FINISHED_LEN 15u

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
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: There are no data prototypes, only function prototypes */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsServer_InitReadyToSendFlags
 *********************************************************************************************************************/
/*! \brief         Initialize the transmission trigger flags.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitReadyToSendFlags(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServer_InitHsMsgIndices
 *********************************************************************************************************************/
/*! \brief         Initialize the TLS handshake message indices.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitHsMsgIndices(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServer_InitHsLenInformation
 *********************************************************************************************************************/
/*! \brief         Initialize the TLS handshake message length information.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitHsLenInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServer_InitAsnycFlags
 *********************************************************************************************************************/
/*! \brief         Initialize the asynchronous trigger flags.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitAsnycFlags(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 *   TLS SERVER HANDSHAKE STATE MACHINE
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_PerformNextHsStep
 *********************************************************************************************************************/
/*! \brief         Main function to process the TLS handshake for the TLS-Server.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_PerformNextHsStep(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_ParseClientHello
 *********************************************************************************************************************/
/*! \brief         Extract and parse the content of the received ClientHello message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Rework the brief description. This function has nothing to do with the record layer. The same is valid for the next 3 functions. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientHello(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_ParseClientKeyExchange
 *********************************************************************************************************************/
/*! \brief         Extract and parse the content of the received ClientKeyExchange message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: See TcpIp_TlsServerHsStm_ParseClientHello */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_ParseClientCcs
 *********************************************************************************************************************/
/*! \brief         Extract and parse the content of the received Client ChangeCipherSpec message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: See TcpIp_TlsServerHsStm_ParseClientHello */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_ParseClientFinished
 *********************************************************************************************************************/
/*! \brief         Extract and parse the content of the received ClientFinished message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: See TcpIp_TlsServerHsStm_ParseClientHello */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerHello
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerHello message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerCertificate
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerCertificate message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerKeyExchange
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerKeyExchange message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerHelloDone
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerHelloDone message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerHelloDone(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_VerifyClientFinished
 *********************************************************************************************************************/
/*! \brief         Extract and verify the content of the received ClientFinished message.
 *  \details       -
 *  \param[in]     TlsConIdx     TLS connection index
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: The function is called Verify.. but the description only says Parse. Make this consistent. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_VerifyClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerCcs
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerChangeCipherSpec message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_SendServerFinished
 *********************************************************************************************************************/
/*! \brief         Prepare and trigger the transmission of the ServerFinished message.
 *  \details       Transmission is done in context of TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl()
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_FinalizeHandshake
 *********************************************************************************************************************/
/*! \brief         Finalize the TLS handshake for the TLS-Server and prepare TLS buffer for application data.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_FinalizeHandshake(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen
 *********************************************************************************************************************/
/*! \brief         Compare the received TLS message length with the expected one.
 *  \details       -
 *  \param[in]     MsgLen               Received message length
 *  \param[in]     ExpectedMsgLen       Expected message length
 *  \return        E_OK                 Length match
 *  \return        E_NOT_OK             Length mismatch
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: This function is reentrant. */
/* [REVIEW_c] resolved visbdk: Done, correct. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen(
  CONST(uint32, AUTOMATIC) MsgLen,
  CONST(uint32, AUTOMATIC) ExpectedMsgLen);

/**********************************************************************************************************************
 * TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation
 *********************************************************************************************************************/
/*! \brief         Handles error reporting during preparation of TLS handshake messages.
 *  \details       Generic function, which is called when an error occurs during the preparation of any handshake message
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: The function description is too generic. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS SERVER HANDSHAKE MESSAGE HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ExtractClientHelloInformation
 *********************************************************************************************************************/
/*! \brief         Extract and verify the information of the ClientHello message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Operation successful
 *  \return        E_NOT_OK                 Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientHelloInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ExtractClientKeyExchangeInformation
 *********************************************************************************************************************/
/*! \brief         Extract and verify the key information of the ClientKeyExchange message.
 *  \details       Depending on the selected key exchange, the ECC or PSK key information is extracted
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Operation successful
 *  \return        E_NOT_OK                 Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Question: Which information in the message is verified? */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientKeyExchangeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ExtractClientFinishedInformation
 *********************************************************************************************************************/
/*! \brief         Extract and verify the information of the ClientFinished message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Operation successful
 *  \return        E_NOT_OK                 Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientFinishedInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_CalcClientFinishedHash
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of the hash value of all received and transmitted TLS handshake messages.
 *  \details       The calculation of the hash is performed in the TcpIp_TlsServerCtx_AsyncHandler() background task.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_CalcClientFinishedVerifyData
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of the finished verify data via the TLS PRF.
 *  \details       The calculation of the hash is performed in the TcpIp_TlsServerCtx_AsyncHandler() background task.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_CalcClientFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_CompareFinishedVerifyData
 *********************************************************************************************************************/
/*! \brief         Compares the calculated finished verify data with the received one from the TLS-Client.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Both values match
 *  \return        E_NOT_OK                 Values do not match
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_CompareFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloGetCipherSuites
 *********************************************************************************************************************/
/*! \brief         Parse the received cipher suite list and search for matching one in configured TLS-Servers list.
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                           CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ClientHelloEndIdx        End index in the TLS RxBuffer of this message
 *  \return        E_OK                     Matching cipher suite found
 *  \return        E_NOT_OK                 Error during parsing or no matching cipher worker found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.02.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Return value E_NOT_OK is listed twice, combine them to one entry. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetCipherSuites(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) ClientHelloEndIdx );

/**********************************************************************************************************************
 * TcpIp_TlsMsg_SelectMatchingCompressionMethod
 *********************************************************************************************************************/
/*! \brief         Select matching local compression method.
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CompressionMethodLen     Length of the received compression method list
 *  \return        E_OK                     Matching compression method found
 *  \return        E_NOT_OK                 Error during parsing or no matching compression method found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.02.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Return value E_NOT_OK is listed twice, combine them to one entry. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_SelectMatchingCompressionMethod(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  CONST(uint8, AUTOMATIC)      CompressionMethodLen);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods
 *********************************************************************************************************************/
/*! \brief         Parse the received compression methods list and search for matching one in configured TLS-Servers list.
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HelloEndIdx              End index in the TLS RxBuffer of this message
 *  \return        E_OK                     Matching compression method found
 *  \return        E_NOT_OK                 Error during parsing or no matching compression method found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.02.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Return value E_NOT_OK is listed twice, combine them to one entry. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) HelloEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloGetExtensions
 *********************************************************************************************************************/
/*! \brief         Parse and verify the received TLS-Client extensions
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ClientHelloEndIdx        End index in the TLS RxBuffer of this message
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) ClientHelloEndIdx );

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions
 *********************************************************************************************************************/
/*! \brief         Parse and verify the received TLS-Client extensions list
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ExtensionsLen            Length of the received extensions list.
 *  \param[in]     HelloEndIdx              End index in the TLS RxBuffer of this message
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Description of parameter ExtensionsLen is missing. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16                      ExtensionsLen,
  TcpIp_TlsBufferRxIterType   HelloEndIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions
 *********************************************************************************************************************/
/*! \brief         Iterate over received TLS-Client extensions list and parse each extension
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ReceivedExtensionListPtr Pointer to the list of received client extensions
 *  \param[in]     ReceivedExtensionCnt     Number of received client extensions
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type server name indication.
 *  \details       -
 *  \param[in]     TlsConIdx                      TLS connection index
 *                                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ServerNameIndicationExtension  Extension of type server name indication
 *  \return        E_OK                           Operation successful
 *  \return        E_NOT_OK                       Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Description of parameter TlsConIdx is missing. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType ServerNameIndicationExtension);

/**********************************************************************************************************************
 *  TcpIp_TlsServertMsg_ClientHelloExtIsServerNameAcceptable
 *********************************************************************************************************************/
/*! \brief         Analyzes a received server name element. Only the format of the element is checked.
 *  \details       -
 *  \param[in]     TlsConIdx                     TLS connection index
 *                                               CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ServerNameStartIdx            Start Idx of the server name element
 *  \param[in]     ServerNameIndicationEndIdx    End Idx of the extension
 *  \param[out]    ServerNameLenPtr              Length of the server name element (including type field)
 *  \param[in,out] HostNameReceivedPtr           A name type 'host_name' already was received
 *  \return        E_OK                          Well formated server name element received
 *  \return        E_NOT_OK                      Received server name element is mis-formated or invalid
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.03.00.0
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsServerNameAcceptable(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType ServerNameStartIdx,
  TcpIp_TlsBufferRxIterType ServerNameIndicationEndIdx,
  TCPIP_P2V(uint16) ServerNameLenPtr,
  TCPIP_P2V(boolean) HostNameReceivedPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type trusted ca indication.
 *  \details       -
 *  \param[in]     TlsConIdx                     TLS connection index
 *                                                CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TrustedCaIndicationExtension  Extension of type trusted ca indication
 *  \return        E_OK                          Operation successful
 *  \return        E_NOT_OK                      Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Description of parameter TlsConIdx is missing. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType TrustedCaIndicationExtension);

/**********************************************************************************************************************
 * TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable
 *********************************************************************************************************************/
/*! \brief         Analyzes a received trusted authority element. Only the format of the element is checked.
 *  \details       -
 *  \param[in]     TrustedAuthorityStartIdx      Start Idx of the authority element
 *  \param[in]     TrustedCaIndicationEndIdx     End Idx of the extension
 *  \param[out]    TrustedAuthorityLenPtr        Length of the authority element (including type field)
 *  \return        E_OK                          Well formated authority element received
 *  \return        E_NOT_OK                      Received authority element is mis-formated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.01.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable(
  TcpIp_TlsBufferRxIterType TrustedAuthorityStartIdx,
  TcpIp_TlsBufferRxIterType TrustedCaIndicationEndIdx,
  TCPIP_P2V(uint16) TrustedAuthorityLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type certificate status request.
 *  \details       -
 *  \param[in]     TlsConIdx                           TLS connection index
 *                                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CertificateStatusRequestExtension   Extension of type certificate status request
 *  \return        E_OK                                Operation successful
 *  \return        E_NOT_OK                            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Description of parameter TlsConIdx is missing. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType CertificateStatusRequestExtension);

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHello_CheckOcspResponderIdList
 *********************************************************************************************************************/
/*! \brief         Analyzes the received responder id list.
 *  \details       -
 *  \param[in]     ResponderIdsListStartIdx      Start Idx of the responder id list
 *  \param[in]     CertStatusRequestEndIdx       End Idx of the extension
 *  \param[out]    TotalResponderIdListLenPtr    Length of the responder id list (including type field)
 *  \return        E_OK                          Well formated responder id list received
 *  \return        E_NOT_OK                      Received responder id list is mis-formated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.03.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHello_CheckOcspResponderIdList(
  TcpIp_TlsBufferRxIterType ResponderIdsListStartIdx,
  TcpIp_TlsBufferRxIterType CertStatusRequestEndIdx,
  TCPIP_P2V(uint16) TotalResponderIdListLenPtr);

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHello_CheckOcspRequestExtensions
 *********************************************************************************************************************/
/*! \brief         Analyzes the received request extensions.
 *  \details       -
 *  \param[in]     RequestExtensionsStartIdx     Start Idx of the request extensions
 *  \param[in]     CertStatusRequestEndIdx       End Idx of the extension
 *  \param[out]    TotalRequestExtensionsLenPtr  Length of the request extensions (including type field)
 *  \return        E_OK                          Well formated request extensions received
 *  \return        E_NOT_OK                      Received request extensions is mis-formated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.03.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHello_CheckOcspRequestExtensions(
  TcpIp_TlsBufferRxIterType RequestExtensionsStartIdx,
  TcpIp_TlsBufferRxIterType CertStatusRequestEndIdx,
  TCPIP_P2V(uint16) TotalRequestExtensionsLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type supported groups.
 *  \details       -
 *  \param[in]     TlsConIdx                 TLS connection index
 *                                            CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     SupportedGroupsExtension  Extension of type supported groups
 *  \return        E_OK                      Operation successful
 *  \return        E_NOT_OK                  Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType SupportedGroupsExtension);

/**********************************************************************************************************************
 * TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported
 *********************************************************************************************************************/
/*! \brief         Compares the given named curve against the configured supported elliptic curves.
 *  \details       Iterate over all configured TcpIpTlsHandshake for each cipher worker for the specific TLS connection
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     NamedCurve              Received named curve ID from the ClientHello extension.
 *  \return        E_OK                    Matching TlsHandshake configuration found.
 *  \return        E_NOT_OK                No matching TlsHandshake configuration found.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 NamedCurve);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats
 *********************************************************************************************************************/
/*! \brief         Parses a received TLS extension of the type EC point formats.
 *  \details       -
 *  \param[in]     TlsConIdx                    TLS connection index
 *                                              CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     EcPointFormatExtension       Extension of type EC point formats
 *  \return        E_OK                         Operation successful
 *  \return        E_NOT_OK                     Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Rename function and adapt description: format --> formats */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType EcPointFormatExtension);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms
 *********************************************************************************************************************/
/*! \brief         Parses an received TLS extension of the type signature algorithm.
 *  \details       -
 *  \param[in]     TlsConIdx                      TLS connection index
 *                                                 CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     SignatureAlgorithmsExtension   Extension of type signature algorithm
 *  \return        E_OK                           Operation successful
 *  \return        E_NOT_OK                       Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.02.00.0
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Description of parameter TlsConIdx is missing. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType SignatureAlgorithmsExtension);

/**********************************************************************************************************************
 * TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported
 *********************************************************************************************************************/
/*! \brief         Compares the given signature and hash algorithm ID against the configured supported algorithms.
 *  \details       Iterate over all configured TcpIpTlsHandshake for each cipher worker for the specific TLS connection.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     SignAndHashAlgId        Received signature and hash algorithm ID from the ClientHello extension
 *  \return        E_OK                    Matching TlsHandshake configuration found.
 *  \return        E_NOT_OK                No matching TlsHandshake configuration found.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.02.00.0
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 SignAndHashAlgId);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit
 *********************************************************************************************************************/
/*! \brief         Parse and verify the received record size limit extension from the ClienHello message
 *  \details       The received information will then be used to fragment the TX size of RL frames after the CCS message
 *  \param[in]     TlsConIdx                TLS connection index
 *                                           CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     RecordSizeLimitExtension Extension of type record size limit
 *  \return        E_OK                     Extension successfully parsed
 *  \return        E_NOT_OK                 Extension NOT successfully parsed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.02.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType RecordSizeLimitExtension);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation
 *********************************************************************************************************************/
/*! \brief         Parse and verify the received ECDH(E) and ECDSA information from the ClientKeyExchange message
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams
 *********************************************************************************************************************/
/*! \brief         Extract received Client key exchange parameter (Public key)
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of DH shared secret for ECC based key exchange.
 *  \details       Calculation is performed in background task TcpIp_TlsServerCtx_AsyncHandler().
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation
 *********************************************************************************************************************/
/*! \brief         Parse and verify the received PSK information from ClientKeyExchange message.
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams
 *********************************************************************************************************************/
/*! \brief         Extract received Client key exchange parameter (PSK Identity).
 *  \details       -
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                     Parsing successful
 *  \return        E_NOT_OK                 Error during parsing
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of TLS pre master secret for PSK based key exchange.
 *  \details       Calculation is performed in background task TcpIp_TlsServerCtx_AsyncHandler().
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON */

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of TLS master secret.
 *  \details       Calculation is performed in background task TcpIp_TlsServerCtx_AsyncHandler().
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_SelectMatchingCipher
 *********************************************************************************************************************/
/*! \brief         Select a suitable cipher worker for the offered cipher suite.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CipherSuiteLen          Length of the received cipher suite list
 *  \return        E_OK                    Suitable cipher worker selected
 *  \return        E_NOT_OK                No suitable cipher work found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_SelectMatchingCipherWorker(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) CipherSuiteLen);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite
 *********************************************************************************************************************/
/*! \brief         Compare received cipher suite against configured Server cipher suites.
 *  \details       -
 *  \param[in]     CipherListStartIdx      Start of the cipher suite within the TLS RxBuffer.
 *  \param[in]     CipherListLen           Length of the received cipher suite list
 *  \param[in]     CipherSuitePattern      Search pattern for the cipher suite (received client cipher suite)
 *  \return        E_OK                    Suitable cipher suite found
 *  \return        E_NOT_OK                No suitable cipher suite found
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite(
  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType CipherListStartIdx,
  CONST(uint16, AUTOMATIC) CipherListLen,
  CONST(TcpIp_CipherSuiteIdOfTlsCipherDefinitionType, AUTOMATIC) CipherSuitePattern);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_PrepareServerHello
 *********************************************************************************************************************/
/*! \brief         Build and prepare ServerHello message for transmitting.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Message prepared successfully
 *  \return        E_NOT_OK                Message preparation failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_PrepareServerCertificates
 *********************************************************************************************************************/
/*! \brief         Build and prepare ServerCertificate message for transmitting.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Message prepared successfully
 *  \return        E_NOT_OK                Message preparation failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_PrepareServerKeyExchange
 *********************************************************************************************************************/
/*! \brief         Build and prepare ServerKeyExchange message for transmitting.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Message prepared successfully
 *  \return        E_NOT_OK                Message preparation failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_PrepareServerHelloDone
 *********************************************************************************************************************/
/*! \brief         Build and prepare ServerHelloDone message for transmitting.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Message prepared successfully
 *  \return        E_NOT_OK                Message preparation failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerHelloDone(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_PrepareServerFinished
 *********************************************************************************************************************/
/*! \brief         Build and prepare ServerFinished message for transmitting.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Message prepared successfully
 *  \return        E_NOT_OK                Message preparation failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher
 *********************************************************************************************************************/
/*! \brief         Add the selected cipher suite to the TLS TxBuffer in the ServerHello message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Cipher suite added successfully
 *  \return        E_NOT_OK                Error during adding - no matching cipher found.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod
 *********************************************************************************************************************/
/*! \brief         Add the selected compression method to the TLS TxBuffer in the ServerHello message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerHelloAddServerExtensions
 *********************************************************************************************************************/
/*! \brief         Add the TLS-Server extensions to the TLS TxBuffer in the ServerHello message.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddServerExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit
 *********************************************************************************************************************/
/*! \brief         -
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates
 *********************************************************************************************************************/
/*! \brief         Add TLS-Server Certificate message structure and prepare the adding of the certificates.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Certificate added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_AddServerCertificatesAddLoadableCert
 *********************************************************************************************************************/
/*! \brief         Add the next certificate to the chain if available and applicable.
 *  \details       It is configurable if the root certificate is added to the certificate chain.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] NextCertIdPtr           ID of the certificate that shall be added next
 *  \param[out]    CopiedLenPtr            Number of bytes copied to the TLS TxBuffer
 *  \param[out]    StopAddingCertsPtr      All applicable certs have been added
 *  \return        E_OK                    Certificate added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.03.00.0
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddLoadableCert(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_CertificateIdType) NextCertIdPtr,
  TCPIP_P2V(uint32) CopiedLenPtr,
  TCPIP_P2V(boolean) StopAddingCertsPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain
 *********************************************************************************************************************/
/*! \brief         Iterate over all installed TLS-Server certificates and add each certificate to the TLS TxBuffer.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] CopiedLenPtr            Number of bytes copied to the TLS TxBuffer
 *  \return        E_OK                    Certificate chain added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert
 *********************************************************************************************************************/
/*! \brief        Add single certificate to the TLS TxBuffer.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] CopiedLenPtr            Number of bytes copied to the TLS TxBuffer
 *  \param[in]     CertId                  ID of the certificate which should be added
 *  \return        E_OK                    Certificate added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) CopiedLenPtr,
  CONST(TcpIp_CertificateIdType, AUTOMATIC) CertId);


/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureParams
 *********************************************************************************************************************/
/*! \brief         Add the TLS Signature structure to the TLS TxBuffer.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureParams(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeEncodeSignature
 *********************************************************************************************************************/
/*! \brief         Encode the generated signature into the used format.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeEncodeSignature(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_EncodeSecp256r1Signature
 *********************************************************************************************************************/
/*! \brief         Encode SECP256R1 based signatures into ASN1 format defined by RFC.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] ConsumedLenPtr          Number of consumed bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_EncodeSecp256r1Signature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) ConsumedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServer_AnalyzeSecp256KeyComponente
 *********************************************************************************************************************/
/*! \brief         Analyze the position of the first significant bit of the given key component and check if a
 *                 leading zero must be added
 *  \details       This function is only valid for SECP based ECC curves
 *  \param[in]     KeyPtr                  Pointer to the key which should be analyzed
 *  \param[in]     KeyLen                  Length of the key which should be analyzed
 *  \param[out]    NrLeadingZeroPtr        Number of leading zeros which must be added
 *                                          CONSTRAINT: [only valid if PrepandLeadingZero is set to TRUE]
 *  \param[out]    PrepandLeadingZero      TRUE if leading zeros must be added, FALSE if not
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Minor: Function and parameter description is missing */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_AnalyzeSecp256KeyComponente(
  TCPIP_P2C(uint8) KeyPtr,
  CONST(uint8, AUTOMATIC) KeyLen,
  TCPIP_P2V(uint8) NrLeadingZeroPtr,
  TCPIP_P2V(boolean) PrepandLeadingZero);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_EncodeEd25519Signature
 *********************************************************************************************************************/
/*! \brief         Encode ED25519 based signatures into format defined by RFC.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] ConsumedLenPtr          Number of consumed bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_EncodeEd25519Signature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) ConsumedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_GetLenOfPubKeyCompression
 *********************************************************************************************************************/
/*! \brief         Return the length of the compression flag for a given curve ID.
 *  \details       If curve does not use compression flag, this returns 0.
 *  \param[in]     CurveId                 ID of the used curve as specified by RFC.
 *  \return        uint8                   Length of the compression flag
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(uint8, TCPIP_CODE) TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of Diffie-Hellman public key (ECC based key exchange).
 *  \details       Calculation is performed in background task TcpIp_TlsServerCtx_AsyncHandler().
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddDiffieHellmanParams
 *********************************************************************************************************************/
/*! \brief         Add the TLS specific DH structure to the TLS TxBuffer.
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddDiffieHellmanParams(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature
 *********************************************************************************************************************/
/*! \brief         Trigger calculation of ECDSA signature for the generated public key (ECC based key exchange).
 *  \details       Calculation is performed in background task TcpIp_TlsServerCtx_AsyncHandler().
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams
 *********************************************************************************************************************/
/*! \brief         Add TLS specific ECDH(E) parameter to the TLS TxBuffer.
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint
 *********************************************************************************************************************/
/*! \brief         Add PSK Identity hint to the TLS TxBuffer.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    PSK Identity added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams
 *********************************************************************************************************************/
/*! \brief         Add PSK parameters to the ServerKeyExchange message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    PSK parameters added successfully
 *  \return        E_NOT_OK                Error during adding
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON */

/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData
 *********************************************************************************************************************/
/*! \brief         Add calculated TLS finished verify data to the TLS ServerFinished message in the TLS TxBuffer.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_CalcSignatureOfPublicKey
 *********************************************************************************************************************/
/*! \brief         Prepare generation of the signature of the public key (ECDSA).
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcSignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx);
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#   endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey
 *********************************************************************************************************************/
/*! \brief         Generate the signature of the public key (ECDSA).
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                    Signature successfully generated
 *  \return        E_NOT_OK                Error during generation of signature
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_CalcServerFinishedHash
 *********************************************************************************************************************/
/*! \brief         Generate the finished hash of all received and transmitted TLS handshake messages (Server side).
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_CalcClientFinishedHash
 *********************************************************************************************************************/
 /*! \brief         Generate the finished hash of all received and transmitted TLS handshake messages (Client side).
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_CalcClientFinishedVerifyData
 *********************************************************************************************************************/
 /*! \brief        Generate the finished verify data via the TLS PRF.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcClientFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_CalcHsFinishedData
 *********************************************************************************************************************/
/*! \brief         Calculate the Verify data for Finished handshake message
 *  \details       Invokes the PRF operation to calculate Verify data for Finished message
 *  \param[in]     TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     FinishedMessageType Type of finished message
 *                                      TCPIP_TLS_MSG_HASH_SERVER_FINISHED
 *                                      TCPIP_TLS_MSG_HASH_CLIENT_FINISHED
 *  \param[out]    ResultPtr           Pointer to buffer where Verify Data shall be stored
 *                                      only valid if E_OK returned
 *  \return        E_OK                Result was calculated successfully
 *  \return        E_NOT_OK            Calculation was unsuccessful
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_CalcHsFinishedData(
  TcpIp_TlsConnectionIterType     TlsConIdx,
  TcpIp_TlsMessageFinishedType    FinishedMessageType,
  TCPIP_P2V(uint8)                ResultPtr);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_GenerateHsHash
 *********************************************************************************************************************/
/*! \brief         Calculate the Hash of all handshake messages until now
 *  \details       Generates Hash using all handshake messages exchanged till now
 *  \param[in]     TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     FinishedMessageType Type of finished message
 *                                      TCPIP_TLS_MSG_HASH_SERVER_FINISHED
 *                                      TCPIP_TLS_MSG_HASH_CLIENT_FINISHED
 *  \return        E_OK                Hash was calculated successfully
 *  \return        E_NOT_OK            Calculation of Hash was unsuccessful
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_GenerateHsHash(
  TcpIp_TlsConnectionIterType     TlsConIdx,
  TcpIp_TlsMessageFinishedType    FinishedMessageType);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.4 Statement: OK */
#  endif

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming
 *********************************************************************************************************************/
/*! \brief         Set all relevant CSM keys for AES-128-CBC streaming.
 *  \details       Keys are generated via TcpIp_TlsCoreCrypto_DeriveKeyBlock()
 *  \param[in]     TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                CSM keys set successfully
 *  \return        E_NOT_OK            CSM keys set unsuccessful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming
 *********************************************************************************************************************/
/*! \brief         Set all relevant CSM keys for AES-128-GCM streaming.
 *  \details       Keys are generated via TcpIp_TlsCoreCrypto_DeriveKeyBlock()
 *  \param[in]     TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                CSM keys set successfully
 *  \return        E_NOT_OK            CSM keys set unsuccessful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming
 *********************************************************************************************************************/
/*! \brief         Set all relevant CSM keys for NULL streaming.
 *  \details       Keys are generated via TcpIp_TlsCoreCrypto_DeriveKeyBlock()
 *  \param[in]     TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                CSM keys set successfully
 *  \return        E_NOT_OK            CSM keys set unsuccessful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  MSA - Master Secret Access
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer
 *********************************************************************************************************************/
/*! \brief          Add TLS-Server session ID to MSA Access buffer.
 *  \details        Only active if TcpIpTlsSupportMasterSecretAccess is enabled
 *  \param[in]      TlsConIdx           TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
* TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer
*********************************************************************************************************************/
/*! \brief          Add the received TLS-Client random to MSA Access buffer.
 *  \details        Only active if TcpIpTlsSupportMasterSecretAccess is enabled
 *  \param[in]      TlsConIdx           TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
*********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TLS SERVER IMPLEMENTATION
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServer_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections and initialize the submodules */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    if (TcpIp_GetModeOfTlsConnection(tlsConIdx) == TCPIP_TLS_SERVER)
    {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: All init functions are also called in TcpIp_TlsServer_ResetConnection. Maybe this function could be called here to avoid duplicated code. CROSSLINK001 */
/* [REVIEW_c] resolved visbdk: Done, change the code an call the reset function instead of all other functions */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Clarify question and remove / rework comment */
/* [REVIEW_c] resolved visbdk: Done, this is the correct place to set the initial server handshake state. removed comment. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
      /* Reset all submodules of this connection */
      TcpIp_TlsServer_ResetConnection(tlsConIdx);
    }
  }
} /* TcpIp_TlsServer_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_InitHsMsgIndices
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitHsMsgIndices(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the RX/TX messages indices */
  /* Initialize indices of received messages (RX) */
  TcpIp_SetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTHELLOIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTRANDOMIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferRxClientSessionIdIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTSESSIONIDIDXOFTLSSERVERBUFFERMGMT);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: It seams like there is no support for receiving an (empty) ClientCertificate message. Is that right? */
/* [REVIEW_c] resolved visbdk: Correct. Receiving such a message would lead into TLS-Alert */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTKEYEXCHANGEIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferRxClientKeyExchangePubKeyIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTKEYEXCHANGEPUBKEYIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferRxClientKeyExchangePubKeyLenIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTKEYEXCHANGEPUBKEYLENIDXOFTLSSERVERBUFFERMGMT);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: The next two variables should be named ClientFinished instead of ClientFinished */
/* [REVIEW_c] comment visbdk: See TCPIP-5700 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SetTlsBufferRxClientFinishedIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTFINISHEDIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferRxClientFinishedVerifyDataIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXCLIENTFINISHEDVERIFYDATAIDXOFTLSSERVERBUFFERMGMT);

  /* Initialize indices of transmitted messages (TX) */
  TcpIp_SetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERHELLOIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerRandomIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERRANDOMIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerSessionIdIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERSESSIONIDIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerCertificatesIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERCERTIFICATESIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerKeyExchangeIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERKEYEXCHANGEIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerKeyExchangeSignatureLenIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERKEYEXCHANGESIGNATURELENIDXOFTLSSERVERBUFFERMGMT);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: This variable should be named ServerHelloDone instead of ServerHelloDone */
/* [REVIEW_c] resolved visbdk: Will be done in TCPIP-5700 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SetTlsBufferTxServerHelloDoneIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERHELLODONEIDXOFTLSSERVERBUFFERMGMT);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: The next two variables should be named ServerFinished instead of ServerFinished */
/* [REVIEW_c] comment visbdk: See TCPIP-5700 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SetTlsBufferTxServerFinishedIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERFINISHEDIDXOFTLSSERVERBUFFERMGMT);
  TcpIp_SetTlsBufferTxServerFinishedVerifyDataIdxOfTlsServerBufferMgmt(
    tlsServerBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXSERVERFINISHEDVERIFYDATAIDXOFTLSSERVERBUFFERMGMT);

} /* TcpIp_TlsServer_InitHsMsgIndices() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_InitHsLenInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
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
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitHsLenInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the RX length information to zero */
  TcpIp_SetClientHelloLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetClientFinishedLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);

  /* #20 Set the TX length information to zero */
  TcpIp_SetServerHelloLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetServerCertificatesLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetServerKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetServerHelloDoneLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetServerFinishedLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
  TcpIp_SetServerHelloSessionIdLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u);
} /* TcpIp_TlsServer_InitHsLenInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_InitReadyToSendFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.00.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitReadyToSendFlags(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConnectionIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the ready to send flags */
  TcpIp_SetHelloReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetCertificateReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetKeyExchangeReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetHelloDoneReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetServerFinishedReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetChangeCipherSpecReadyToSendOfTlsServerConnection(tlsServerConnectionIdx, FALSE);

} /* TcpIp_TlsServer_InitReadyToSendFlags() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_InitAsnycFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
  */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_InitAsnycFlags(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConnectionIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the async calculation trigger flags */
  TcpIp_SetHsSignGenAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);


#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: Why do we need an async operation to verify the hash? It is only usage of Prf and a comparison. Are all calls to the PRF done in async context? */
/* [REVIEW_c] resolved visbdk: Seems legit, we should move the PRF (verifyData) into the mainfunction handling, not the async. TCPIP-6072 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SetCalcClientFinishedVerifyDataAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);

} /* TcpIp_TlsServer_InitAsnycFlags() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_ResetConnection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_ResetConnection(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Statement: Same as in TcpIp_TlsServer_Init. CROSSLINK001 */
/* [REVIEW_c] resolved visbdk: Done - see  TcpIp_TlsServer_Init */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* #10 Initialize the TLS handshake message indices */
  TcpIp_TlsServer_InitHsMsgIndices(TlsConIdx);

  /* #20 Initialize the TLS handshake length information */
  TcpIp_TlsServer_InitHsLenInformation(TlsConIdx);

  /* #30 Initialize the ready to send flags */
  TcpIp_TlsServer_InitReadyToSendFlags(TlsConIdx);

  /* #40 Initialize the async context flags */
  TcpIp_TlsServer_InitAsnycFlags(TlsConIdx);

  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_HELLO);

} /* TcpIp_TlsServer_ResetConnection() */

/**********************************************************************************************************************
 *   TLS SERVER ASYNC CONTEXT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_AsyncHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_AsyncHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConnectionIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the trigger for the different ASYNC operations and execute the operation if the trigger is set */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  /* Execute the signature generation operation if the corresponding trigger flag is set */
  if (TcpIp_IsHsSignGenAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx) == TRUE)
  {
    /* generate the Signature of the public key */
    TcpIp_TlsServerCtx_CalcSignatureOfPublicKey(TlsConIdx);
    TcpIp_SetHsSignGenAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  }
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
  /* Execute the finished hash operation if the corresponding trigger flag is set */
  if (TcpIp_IsCalcServerFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx) == TRUE)
  {
    /* Calculate the server finished data hash */
    TcpIp_TlsServerCtx_CalcServerFinishedHash(TlsConIdx);
    TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  }
  /* Execute the finished hash operation if the corresponding trigger flag is set */
  if (TcpIp_IsCalcClientFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx) == TRUE)
  {
    /* Calculate the hash till client finished */
    TcpIp_TlsServerCtx_CalcClientFinishedHash(TlsConIdx);
    TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  }
  /* Execute the finished verify operation if the corresponding trigger flag is set */
  if (TcpIp_IsCalcClientFinishedVerifyDataAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx) == TRUE)
  {
    /* Calculate the client finished verify data */
    TcpIp_TlsServerCtx_CalcClientFinishedVerifyData(TlsConIdx);
    TcpIp_SetCalcClientFinishedVerifyDataAsyncFlagOfTlsServerConnection(tlsServerConnectionIdx, FALSE);
  }
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Remove the following comment, it makes no sense. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
} /* TcpIp_TlsServerCtx_AsyncHandler() */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_CalcSignatureOfPublicKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcSignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the CSM job for the signature operation is configured */
  if (TcpIp_IsCsmJobIdKeyExchangeSignatureGenerateUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {

    /* #20 Generate the signature of the public key */
    if (TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey(TlsConIdx) == E_OK)
    {
      /* Signature generated - reset context state */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
    }
    else
    {
      /* #30 Generation of signature failed - handle error during processing */
      TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
        TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_SIGN_PUBKEY, TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED);
    }
  }
  else
  {
    /* #40 CSM job for signature operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }
} /* TcpIp_TlsServerCtx_CalcSignatureOfPublicKey() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TcpIp_TlsTemporarySignatureBufferStartIdxOfTlsConnectionType tmpSignatureBufferStartIdx
    = TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsTemporarySignatureBufferEndIdxOfTlsConnectionType tmpSignatureBufferEndIdx
    = TcpIp_GetTlsTemporarySignatureBufferEndIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsEllipticCurveIdType usedCurveId =
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx);

  uint32 signatureGenerateJobId
    = TcpIp_CsmJobId[TcpIp_GetCsmJobIdKeyExchangeSignatureGenerateIdxOfTlsHandshake(activeTlsHandshakeIdx)];

  /* The CSM does not support in place calculation for the signature generate operation
   - use local buffer for the CSM input */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: Why is a fixed size used for this buffer? Can't it be reduced depending on the used cipher / curve? */
/* [REVIEW_c] resolved visjer: Is now depending on the implemented/planned curves and the maximum public key length among all of them */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Don't use magic numbers for the buffer size. */
/* [REVIEW_c] resolved visjer: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* Size of the Buffer must be big enough to fit the ClientHello random, the ServerHello random */
  /* and the maximum length of the ServerKeyExchange parameter into it. */
  /* This maximum is reached when the public key length is at its maximum and when a compression length field exists */
  uint8 localDataToBeSignedBuf[TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN + TCPIP_TLSSERVER_CURVETYPE_LEN
    + TCPIP_TLSSERVER_CUVEID_LEN + TCPIP_TLSSERVER_PUPKEYLEN_LEN + TCPIP_TLSSERVER_PUPKEY_COMPRESSION_LEN
    + TCPIP_MAX_PUBKEY_LEN];

  /* Destination buffer for the CSM operation */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: Why do we need a temporary buffer? Can't we directly use the Tls TxBuffer? */
/* [REVIEW_c] resolved visbdk: There is a restriction for CSM in place calculation (only for ED as far as I remember), we need the separate buffer, See local comment at the buffer */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  TCPIP_P2V(uint8) generatedSignatureDestPtr = TcpIp_GetAddrTlsTemporarySignatureBuffer(tmpSignatureBufferStartIdx);
  uint32 generatedSignatureDestLen = (((uint32)tmpSignatureBufferEndIdx - tmpSignatureBufferStartIdx));

  Std_ReturnType csmRetVal;
  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* RFC8422 - 5.4. Server Key Exchange */
  /*  ServerKeyExchange.signed_params.sha_hash
          SHA(ClientHello.random + ServerHello.random + ServerKeyExchange.params) */

  /* Format of temporary input signature buffer:
  *                                 +-> clientRndDestPtr
  *                                /                   +-> serverRndDestPtr
  *                               /                   /                   +-> keyExchangeDestPtr
  *                              /                   /                   /
  * localDataToBeSignedBuf  : [ (ClientHello random)(ServerHello random)(ServerKeyExchange parameter) ]
  *                           \                                          \-----dhParameterLen------/  /
  *                            \----------------------------------+----------------------------------/
  *                                                               +---> dataToBeSignedLen
  */

  uint8 usedPublicKeyLen = ((TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(usedCurveId)
    + TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(usedCurveId)));

  uint32 dhParameterLen
    = ((uint32)usedPublicKeyLen + TCPIP_TLSSERVER_CURVETYPE_LEN + TCPIP_TLSSERVER_CUVEID_LEN + TCPIP_TLSSERVER_PUPKEYLEN_LEN);

  uint32 dataToBeSignedLen = (TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN + dhParameterLen);

  TCPIP_P2V(uint8) clientRndDestPtr   = &localDataToBeSignedBuf[0];
  TCPIP_P2V(uint8) serverRndDestPtr   = &localDataToBeSignedBuf[TCPIP_TLS_RNDLEN];
  TCPIP_P2V(uint8) keyExchangeDestPtr = &localDataToBeSignedBuf[TCPIP_TLS_RNDLEN + TCPIP_TLS_RNDLEN];

  /* #10 Generate linear input buffer with the server key exchange data to be signed */
  VStdMemCpy(clientRndDestPtr, TcpIp_GetAddrTlsBufferRx(                                                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)), TCPIP_TLS_RNDLEN);

  VStdMemCpy(serverRndDestPtr, TcpIp_GetAddrTlsBufferTx(                                                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetTlsBufferTxServerRandomIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)), TCPIP_TLS_RNDLEN);

  VStdMemCpy(keyExchangeDestPtr, TcpIp_GetAddrTlsBufferTx(                                                              /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetTlsBufferTxServerKeyExchangeParamsIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)), dhParameterLen);

  /* #20 Generate signature over linearized input data */
  csmRetVal = TCPIP_CSM_SignatureGenerate(signatureGenerateJobId, CRYPTO_OPERATIONMODE_SINGLECALL,
    clientRndDestPtr, dataToBeSignedLen, generatedSignatureDestPtr, &generatedSignatureDestLen);

  /* #30 Check the result of the CSM operation */
  /* The maximum length of the calculated (raw, without encoding) signature for ED25519 and SECP256 curve is 64Bytes */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, generatedSignatureDestLen, TCPIP_TLS_MAX_SIGNATURE_LEN,
        TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_SIGN_PUBKEY) == E_OK)
  {
    /* Signature successfully generated */
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsServerCtx_GenerateSignatureOfPublicKey() */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_CalcServerFinishedHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcServerFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 localErrorId = TCPIP_TLS_ERRORID_NOT_SET;                                                                      /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  uint8 finishedVerifyData[TCPIP_TLS_FINISHED_VERIFYDATA_LEN];
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the server finished hash which is needed for the finished verify data */
  if (TcpIp_TlsServerCrypto_GenerateHsHash(TlsConIdx, TCPIP_TLS_MSG_HASH_SERVER_FINISHED) == E_OK)
  {
    /* #20 Perform PRF on finished hash to calculate the finished verify data */
    if (TcpIp_TlsServerCrypto_CalcHsFinishedData(TlsConIdx, TCPIP_TLS_MSG_HASH_SERVER_FINISHED, finishedVerifyData) == E_OK)
    {
      /* #30 TLS verify finished data successfully calculated, now copy the finished verify data into the TLS TxBuffer */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
      /* [REVIEW_c] open visal 16.00.00.2 Question: Why are these assignments done in an extra "if" instead of doing it inside the above "if" where the retVal is set to E_OK? This would also avoid the useless init of the finished array. */
      /* [REVIEW_c] resolved visjer: Assignments are now included in the "if" where the retVal is set to E_OK and the finished array isn't initialized any more . */
      /* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
      TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
        = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

      TCPIP_P2V(uint8) tlsTxBufferFinishDestPtr = TcpIp_GetAddrTlsBufferTx(
        TcpIp_GetTlsBufferTxServerFinishedVerifyDataIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
      /* [REVIEW_c] open visal 16.00.00.2 Question: Why do we need a temp buffer, can't we directly use the TlsTxBuffer? */
      /* [REVIEW_c] resolved visbdk: Hmm, could be if we change the context of the PRF (see other finding). I added a note in the corresponding TCPIP-6072. */
      /* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    /* Copy the result into the TLS TxBuffer buffer */
      VStdMemCpy(tlsTxBufferFinishDestPtr, finishedVerifyData, TCPIP_TLS_FINISHED_VERIFYDATA_LEN);                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Calculation of finished verify data done - reset context state */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);

      retVal = E_OK;
    }
    else
    {
      /* Error - Calculation of finished verify data failed */
      localErrorId = TCPIP_TLS_ERRORID_CRYPTO_SERVERFINISHED_VERIFY_FAILED;
    }
  }
  else
  {
    /* Error - Calculation of finished hash failed */
    localErrorId = TCPIP_TLS_ERRORID_CRYPTO_SERVERFINISHED_HASH_FAILED;
  }

  if (retVal == E_NOT_OK)
  {
    /* #40 Handle error while async CSM processing */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
      TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_FINISHED_HASH, localErrorId);
  }
} /* TcpIp_TlsServerCtx_CalcServerFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_CalcClientFinishedHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the client finished hash */
  if (TcpIp_TlsServerCrypto_GenerateHsHash(TlsConIdx, TCPIP_TLS_MSG_HASH_CLIENT_FINISHED) == E_OK)
  {
    /* Calculation of finished hash done - reset context state */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
  }
  else
  {
    /* #20 Error - Calculation of client finished hash failed */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
      TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_CLIENTFINISHED_HASH, TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_HASH_FAILED);
  }
} /* TcpIp_TlsServerCtx_CalcClientFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCtx_CalcClientFinishedVerifyData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_CalcClientFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(uint8)  clientFinishedDestPtr =
    TcpIp_GetAddrTlsTemporaryFinishedBuffer(TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the client finished verify data  */
  if (TcpIp_TlsServerCrypto_CalcHsFinishedData(TlsConIdx,
        TCPIP_TLS_MSG_HASH_CLIENT_FINISHED, clientFinishedDestPtr) == E_OK)
  {
    /* Calculation of finished verify data done - reset context state */
    TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
  }
  else
  {
    /* #20 Error - Calculation of client finished hash failed */
    TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
      TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_CLIENTFINISHED_VERIFY, TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_VERIFY_FAILED);
  }
} /* TcpIp_TlsServerCtx_CalcClientFinishedVerifyData() */

/**********************************************************************************************************************
 *   TLS SERVER CRYPTO
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_GenerateHsHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_GenerateHsHash(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsMessageFinishedType FinishedMessageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TcpIp_TlsTemporaryFinishedBufferStartIdxOfTlsConnectionType tmpFinishedBufStartIdx
    = TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsTemporaryFinishedBufferEndIdxOfTlsConnectionType tmpFinishedBufEndIdx
    = TcpIp_GetTlsTemporaryFinishedBufferEndIdxOfTlsConnection(TlsConIdx);

  uint32 csmHashJobId = TcpIp_GetHashVerifyJobIdOfTlsHandshake(activeTlsHandshakeIdx);

  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the received and transmitted TLS handshake message for the hash calculation */

  /* Use the temporary buffer to store the hash value temporarily */
  TCPIP_P2V(uint8) hsHashDestPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(tmpFinishedBufStartIdx);
  uint32 hsHashDestSpace = (uint32)tmpFinishedBufEndIdx - tmpFinishedBufStartIdx;

  /* Pointer to the ClientHello message in the TLS RxBuffer */
  TCPIP_P2C(uint8) clientHelloPtr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));
  uint32 clientHelloLen = ((uint32)TcpIp_GetClientHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx) + TCPIP_TLS_HSHDRLEN);

  /* Pointer to the transmitted server messages, which are linearized in the TLS TxBuffer */
  /* Messages: ServerHello ServerCertificate ServerKeyExchange ServerHelloDone */
  TCPIP_P2C(uint8) serverTxPtr = TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

  /* Length of the transmitted server messages */
  /* If the messages are not sent (e.g. with PSK) the corresponding length is set to 0 */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: This length could also be calculated as (HelloDoneStartIdx - ServerHelloStartIdx + ServerHelloDoneLen). This would include future extensions like OCSP (not yet planned) and client authentication. */
/* [REVIEW_c] rejected visbdk: Dont like it */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  uint32 serverTxLen = ((uint32)TcpIp_GetServerHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)
    + (uint32)TcpIp_GetServerCertificatesLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)
    + (uint32)TcpIp_GetServerKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)
    + (uint32)TcpIp_GetServerHelloDoneLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

  /* Pointer to the received client messages, which are linearized in the TLS RxBuffer */
  TCPIP_P2C(uint8) clientRxPtr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));
  uint32 clientRxLen;

  /* Calculate the length of the clientRx part */
  if (FinishedMessageType == TCPIP_TLS_MSG_HASH_SERVER_FINISHED)
  {
    /* Length of the received client key exchange and client finished for server finished hash generation */
    clientRxLen = ((uint32)TcpIp_GetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx) + TCPIP_TLS_HSHDRLEN
      + ((uint32)TcpIp_GetClientFinishedLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx) + TCPIP_TLS_HSHDRLEN));
  }
  else /* FinishedMessageType == TCPIP_TLS_MSG_HASH_CLIENT_FINISHED */
  {
    /* Length of the received client key exchange for Client finished hash generation */
    clientRxLen = ((uint32)TcpIp_GetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx) + TCPIP_TLS_HSHDRLEN);
  }


  /* #20 Calculate the handshake hash */
  /* Begin the hash with the clientHello message */
  csmRetVal = TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_START | CRYPTO_OPERATIONMODE_UPDATE,
    clientHelloPtr, clientHelloLen, NULL_PTR, NULL_PTR);

  /* Update the hash with the server messages */
  csmRetVal |= TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_UPDATE, serverTxPtr, serverTxLen,
    NULL_PTR, NULL_PTR);

  /* Update and finalize the hash with the client messages */
  csmRetVal |= TCPIP_CSM_Hash(csmHashJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
    clientRxPtr, clientRxLen, hsHashDestPtr, &hsHashDestSpace);

  /* Check if the CSM operation succeed */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal,
    hsHashDestSpace, TCPIP_TLS_HASH_SHA256_LEN, TCPIP_TLS_FCTID_SERVER_CRYPTO_CALCHSFINISHEDHASH);

  return retVal;
} /* TcpIp_TlsServerCrypto_GenerateHsHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_CalcHsFinishedData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_CalcHsFinishedData(
  TcpIp_TlsConnectionIterType    TlsConIdx,
  TcpIp_TlsMessageFinishedType   FinishedMessageType,
  TCPIP_P2V(uint8)               ResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TCPIP_P2C(uint8) labelPtr  = &TcpIp_Tls_Hs_FinishedLabel[FinishedMessageType][0];

  TCPIP_P2C(uint8) seedPtr   = TcpIp_GetAddrTlsTemporaryFinishedBuffer(
    TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  TcpIp_TlsCsmKeyInfoType msKey;
  TcpIp_TlsCsmKeyInfoType resultKey;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Retrieve master shared secret to local key element */
  msKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdMasterSecretIdxOfTlsHandshake(activeTlsHandshakeIdx)];
  msKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  msKey.KeyLen       = TCPIP_TLS_MASTER_SECRET_LEN;

  /* Retrieve Prf result key (contains result of verify data) to local key element */
  resultKey.KeyId        = TcpIp_GetPrfResultPublicKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  resultKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  resultKey.KeyLen       = TCPIP_TLS_FINISHED_VERIFYDATA_LEN;

  /* #10 Calculate the TLS handshake finished data using the PRF with the hash, master secret and label */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Do not use defines without TCPIP prefix. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Don't use a magic number as length value. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  if (TcpIp_TlsCoreCrypto_Prf(TlsConIdx, &resultKey, &msKey, labelPtr, seedPtr, TCPIP_TLS_LABEL_FINISHED_LEN,
        TCPIP_TLS_HASH_SHA256_LEN, FALSE) == E_OK)
  {
    /* #20 Write the calculated finished data (stored in CSM Key) into destination buffer */
    Std_ReturnType csmRetVal;
    uint32 tmpLen = resultKey.KeyLen;
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Dereferencing ResultPtr is not necessary, pointer can be used directly. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    csmRetVal = TCPIP_CSM_KeyElementGet( resultKey.KeyId, resultKey.KeyElementId, ResultPtr, &tmpLen);

    /* Check if the CSM operation succeed */
    /* User error handling is done outside of this function */
   retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, tmpLen, resultKey.KeyLen,
     TCPIP_TLS_FCTID_SERVER_CRYPTO_CALCHSFINISHEDDATA);
  }

  return retVal;
} /* TcpIp_TlsServerCrypto_CalcHsFinishedData() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_SetCsmKeys
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherStreamingModeDataType selectedStreamingMode
    = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select the active streaming method of the used cipher suite */
  switch (selectedStreamingMode)
  {
    case TCPIP_TLS_STREAMING_MODE_AES_128_CBC:
    {
      /* #20 Set CSM keys for AES-128-CBC streaming method */
      /* X_WITH_AES_128_CBC_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
      */
      retVal = TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

    case TCPIP_TLS_STREAMING_MODE_AES_128_GCM:
    {
      /* #30 Set CSM keys for AES-128-GCM streaming method */
      /* X_WITH_AES_128_GCM_SHAX
           TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
           TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
      */
      retVal = TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_GCM */

    case TCPIP_TLS_STREAMING_MODE_NULL:
    {
      /* #40 Set CSM keys for NULL streaming method */
      /* X_WITH_NULL_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA
      */
      retVal = TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming(TlsConIdx);
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_NULL */

    default:                                                                                                            /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
    {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Add a comment that the default path is never used since a valid mode was set earlier in the handshake. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
      /* Default path is never used since a valid mode was set earlier in the handshake - left blank intentionally */
      break;
    } /* default */

  } /* switch */

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Adapt comment. This is also E_NOT_OK if setting the keys failed. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* #50 Report error in case of invalid active streaming method or setting of CSM keys failed */
  if ( retVal != E_OK)
  {
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId  = TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYS;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_SETCSMKEYS_FAILED;
    userError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsServerCrypto_SetCsmKeys() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);

  TcpIp_TlsCsmKeyInfoType keyBlockKey;
  TcpIp_TlsCsmKeyInfoType txHMacShaKey;

  Std_ReturnType csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Generated keyBlock is the source for all the relevant keys */
  keyBlockKey.KeyId        = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);

  /* #10 Set CSM keys for TX MAC operations - used during transmit of TLS messages */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: Why is TcpIp_CsmKeyId not modeled as a CSL variable? How do we assure that we do not have an out-of-bounds access? How many elements exist in this array? */
/* [REVIEW_c] resolved visbdk: There is some kind of concept for those Csm arrays, (also see TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration), we can clarify the details via phone */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  txHMacShaKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  txHMacShaKey.KeyLen       = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal  = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txHMacShaKey);
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId, txHMacShaKey.KeyLen,
    0, txHMacShaKey.KeyLen, txHMacShaKey.KeyId, txHMacShaKey.KeyElementId);

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
  {
    TcpIp_TlsCsmKeyInfoType rxHMacShaKey;

    (void)TCPIP_CSM_KeySetValid(txHMacShaKey.KeyId);

    /* #20 Set CSM keys for RX MAC operations - used during reception of TLS messages */
    rxHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
    rxHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
    rxHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

    csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxHMacShaKey);
    csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId, 0, 0,
      rxHMacShaKey.KeyLen, rxHMacShaKey.KeyId, rxHMacShaKey.KeyElementId);

    if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
    {
      TcpIp_TlsCsmKeyInfoType txAesKey;

      (void)TCPIP_CSM_KeySetValid(rxHMacShaKey.KeyId);

      /* #30 Set CSM keys for TX AES operations - used during transmit of TLS messages */
      txAesKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
      txAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
      txAesKey.KeyLen = TCPIP_TLS_AES128_KEY_LEN;

      csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txAesKey);
      csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId,
        txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen + txAesKey.KeyLen, 0, txAesKey.KeyLen, txAesKey.KeyId, txAesKey.KeyElementId);

      if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
      {
        TcpIp_TlsCsmKeyInfoType rxAesKey;

        (void)TCPIP_CSM_KeySetValid(txAesKey.KeyId);

        /* #40 Set CSM keys for RX AES operations - used during reception of TLS messages */
        rxAesKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
        rxAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
        rxAesKey.KeyLen = TCPIP_TLS_AES128_KEY_LEN;

        csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxAesKey);
        csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId,
          txHMacShaKey.KeyLen + rxHMacShaKey.KeyLen, 0, rxAesKey.KeyLen, rxAesKey.KeyId, rxAesKey.KeyElementId);

        if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128CBC) == E_OK)
        {
          (void)TCPIP_CSM_KeySetValid(rxAesKey.KeyId);
        }
      }
    }
  }

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: If setting one key fails, the others still will be set. This is not necessary, stop processing after first error. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  return csmRetVal;
} /* TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
  */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);

  TcpIp_TlsCsmKeyInfoType keyBlockKey;
  TcpIp_TlsCsmKeyInfoType txAesKey;

  Std_ReturnType csmRetVal;
  /* ----- Implementation ----------------------------------------------- */
  /* Generated keyBlock is the source for all the relevant keys */
  keyBlockKey.KeyId = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);


  /* For Aes128Gcm the key block is parsed as below
   *  0..15  Client encrypt key
   *  16..31 Server encrypt key
   *  32..35 Client Iv
   *  36..40 Server Iv
   */

  /* #10 Set CSM keys for TX AES operations - used during transmit of TLS messages */
  txAesKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
  txAesKey.KeyLen       = TCPIP_TLS_AES128_GCM_KEY_LEN;

  csmRetVal  = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txAesKey);
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial( keyBlockKey.KeyId, keyBlockKey.KeyElementId, txAesKey.KeyLen, 0,
    txAesKey.KeyLen, txAesKey.KeyId, txAesKey.KeyElementId );

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128GCM) == E_OK)
  {
    TcpIp_TlsCsmKeyInfoType rxAesKey;

    (void)TCPIP_CSM_KeySetValid(txAesKey.KeyId);

    /* #20 Set CSM keys for RX AES operations - used during reception of TLS messages */
    rxAesKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
    rxAesKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
    rxAesKey.KeyLen       = TCPIP_TLS_AES128_KEY_LEN;

    csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxAesKey);
    csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId, 0, 0,
      rxAesKey.KeyLen, rxAesKey.KeyId, rxAesKey.KeyElementId);

    if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128GCM) == E_OK)
    {
      TcpIp_TlsCsmKeyInfoType txHMacShaKey;
      TcpIp_TlsCsmKeyInfoType rxHMacShaKey;

      (void)TCPIP_CSM_KeySetValid(rxAesKey.KeyId);

      /* #30 Set CSM keys for TX IV */
      txHMacShaKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
      txHMacShaKey.KeyElementId = CRYPTO_KE_CIPHER_IV;
      txHMacShaKey.KeyLen       = TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN;

      csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txHMacShaKey);
      csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId,
        rxAesKey.KeyLen + txAesKey.KeyLen + txHMacShaKey.KeyLen, 0, txHMacShaKey.KeyLen, txHMacShaKey.KeyId, txHMacShaKey.KeyElementId);

      if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128GCM) == E_OK)
      {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
        /* [REVIEW_c] open visal 16.00.00.2 Question: Is it not allowed to set the key valid or is it not necessary? Rework description to make this clear. Why is it not necessary? */
        /* [REVIEW_c] resolved visbdk: IV is used internally in the CSM for the first "round" of the AES and therefore automatically set valid when starting the AES  */
        /* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
        /* IV value does not have to be set valid in CSM, because it is automatically set valid on the first round of AES operation - do nothing */
      }

      /* #40 Set CSM keys for RX IV */
      rxHMacShaKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
      rxHMacShaKey.KeyElementId = CRYPTO_KE_CIPHER_IV;
      rxHMacShaKey.KeyLen       = TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN;

      csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxHMacShaKey);
      csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId,
        rxAesKey.KeyLen + txAesKey.KeyLen, 0, rxHMacShaKey.KeyLen, rxHMacShaKey.KeyId, rxHMacShaKey.KeyElementId);

      if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128GCM) == E_OK)
      {
        /* IV value does not have to be set valid in CSM, because it is automatically set valid on the first round of AES operation - do nothing */
      }
    }
  }
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Same as in TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming, setting keys can be stopped after first error. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  return csmRetVal;
} /* TcpIp_TlsServerCrypto_SetCsmKeysAes128GcmStreaming() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);

  TcpIp_TlsCsmKeyInfoType keyBlockKey;
  TcpIp_TlsCsmKeyInfoType txHMacShaKey;
  TcpIp_TlsCsmKeyInfoType rxHMacShaKey;
  Std_ReturnType csmRetVal;
  /* ----- Implementation ----------------------------------------------- */
  /* Generated keyBlock is the source for all the relevant keys */
  keyBlockKey.KeyId        = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);

  /* #10 Set CSM keys for TX MAC operations - used during transmit of TLS messages */
  txHMacShaKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
  txHMacShaKey.KeyLen       = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  csmRetVal  = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &txHMacShaKey);
  csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId, txHMacShaKey.KeyLen, 0,
    txHMacShaKey.KeyLen, txHMacShaKey.KeyId, txHMacShaKey.KeyElementId);

  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSNULL) == E_OK)
  {
    (void)TCPIP_CSM_KeySetValid(txHMacShaKey.KeyId);

    /* #20 Set CSM keys for RX MAC operations - used during reception of TLS messages */
    rxHMacShaKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
    rxHMacShaKey.KeyElementId = CRYPTO_KE_MAC_KEY;
    rxHMacShaKey.KeyLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

    csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &rxHMacShaKey);
    csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyBlockKey.KeyId, keyBlockKey.KeyElementId, 0, 0,
      rxHMacShaKey.KeyLen, rxHMacShaKey.KeyId, rxHMacShaKey.KeyElementId);

    if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSNULL) == E_OK)
    {
      (void)TCPIP_CSM_KeySetValid(rxHMacShaKey.KeyId);
    }
  }

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Same as in TcpIp_TlsServerCrypto_SetCsmKeysAes128CbcStreaming, setting keys can be stopped after first error. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  return csmRetVal;
} /* TcpIp_TlsServerCrypto_SetCsmKeysNullStreaming() */

/**********************************************************************************************************************
 *   TLS SERVER TX RECORD LAYER FORWARDING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6010, 6030, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsServerConnectionIterType tlsServerConIdx     = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ServerHello message is transmittable and forward it to the record layer */
  if (TcpIp_IsHelloReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      TcpIp_GetServerHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetHelloReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);
    }
  }

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: If a RlTransmit failed, it should not be tried to send the following messages. */
/* [REVIEW_c] resolved visbdk: Done, is also relevant for the TLS-Client. Created a story for this: TCPIP-6087 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* #20 Check if the ServerCertificate message is transmittable and forward it to the record layer */
  if (TcpIp_IsCertificateReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxServerCertificatesIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      TcpIp_GetServerCertificatesLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetCertificateReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);
    }
  }

  /* #30 Check if the ServerKeyExchange message is transmittable and forward it to the record layer */
  if (TcpIp_IsKeyExchangeReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxServerKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      TcpIp_GetServerKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetKeyExchangeReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);
    }
  }

  /* #40 Check if the ServerHelloDone message is transmittable and forward it to the record layer */
  if (TcpIp_IsHelloDoneReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxServerHelloDoneIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      TcpIp_GetServerHelloDoneLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetHelloDoneReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);
    }
  }

  /* #50 Check if the ServerFinished message is transmittable and forward it to the record layer */
  if (TcpIp_IsServerFinishedReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
  {
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, TcpIp_GetTlsBufferTxServerFinishedIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      TcpIp_GetServerFinishedLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx), TCPIP_TLS_CT_HS) == E_OK)
    {
      /* Reset the TX indication flag for this message */
      TcpIp_SetServerFinishedReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);
    }
  }

} /* TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerTx_SendChangeCipherSpec
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsServerTx_SendChangeCipherSpec(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxCcsStartIdxOfTlsBufferMgmtType ccsStartIdx
    = TcpIp_GetTlsBufferTxCcsStartIdxOfTlsBufferMgmt(tlsBufMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the TLS CCS payload (0x01) into the TLS Tx CCS Buffer */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Statement: I would prefer simply to write 1 byte without using an IpBase FUCTION. This is some overhead. */
/* [REVIEW_c] rejected visbdk: All access to the TxBuffer is performed via the Put/Get functions. Compiler will/should reduce the overhead */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Use a local variable instead of using TcpIp_GetTlsBufferTxCcsStartIdxOfTlsBufferMgmt(tlsBufMgmtIdx) twice. This would be more readable. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(ccsStartIdx), 0, TCPIP_TLS_CHANGECIPHERSPEC);

  /* #20 Transmit the frame via the TLS record layer */
  if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, ccsStartIdx, TCPIP_TLS_CCSMSG_LEN, TCPIP_TLS_CT_CCS) == E_OK)
  {
    TcpIp_TlsServerConnectionIterType tlsServerConIdx = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

    TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx
      = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

    /* Get the index of the current CipherDefiniton */
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
      = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);

    /* Get the corresponding Cipher Id (HexCode) */
    TcpIp_CipherSuiteIdOfTlsCipherDefinitionType selectedCipherSuiteId
      = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx);

    /* Reset the Transmit Flag */
    TcpIp_SetChangeCipherSpecReadyToSendOfTlsServerConnection(tlsServerConIdx, FALSE);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Rework the comment. There is no if any more, the CCS message has been sent when this line is reached. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    /* #30 Update the active cipher for the TX direction */
    TcpIp_SetActiveCipherTxOfTlsConnectionDyn(TlsConIdx, selectedCipherSuiteId);
  }
} /* TcpIp_TlsServerTx_SendChangeCipherSpec() */

/**********************************************************************************************************************
 *   TLS SERVER HANDSHAKE STATE MACHINE
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServer_ProcessHandshake
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_ProcessHandshake(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the current connection is in an active HS state */
  if (   ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE))            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING)))
  {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Question: When can this state occur? When the server is about to calc the content for its FINIALIZED, the ASYNC flag probably also is set. */
/* [REVIEW_c] resolved visbdk: This state is set when we "start" parsing the finished message. At this point we can not change the connection state to ASYNC (because there is no async) and we can not set it to "DONE". But at this point it is also allowed to receive application data from the client (because he is already finished with the HS). Therefore this extra state */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    /* #20 Check that there is no async operation in process */
    if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
    {
      /* #30 Check if we have at least one trigger to process the HS */
              /* Next state is a TX state */
      if (   (TcpIp_IsHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx) == TRUE)                                              /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
              /* AsnycCtx operation is done, continue HS */
          || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE)
              /* Unprocessed HS messaged in the buffer */
          || (TcpIp_GetHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx) != 0u))
      {
        /* #40 Perform the next Step within the current HS flow */
        TcpIp_TlsServerHsStm_PerformNextHsStep(TlsConIdx);

      } /* else - otherwise do nothing */
    } /* else - otherwise do nothing */
  } /* else - otherwise do nothing */

} /* TcpIp_TlsServer_ProcessHandshake() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_PerfomNextHsStep
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_PerformNextHsStep(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process the TLS-Server handshake depending on the current sate */
  switch (TCPIP_TLS_GET_HS_STATE(TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)))
  {
    case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_HELLO:
    {
      TcpIp_TlsServerHsStm_ParseClientHello(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_HELLO:
    {
      TcpIp_TlsServerHsStm_SendServerHello(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_CERTIFICATE:
    {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      TcpIp_TlsServerHsStm_SendServerCertificate(TlsConIdx);
#  endif
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE:
    {
      TcpIp_TlsServerHsStm_SendServerKeyExchange(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE:
    {
      TcpIp_TlsServerHsStm_SendServerHelloDone(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE:
    {
      TcpIp_TlsServerHsStm_ParseClientKeyExchange(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_CCS:
    {
      TcpIp_TlsServerHsStm_ParseClientCcs(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED:
    {
      TcpIp_TlsServerHsStm_VerifyClientFinished(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_CCS:
    {
      TcpIp_TlsServerHsStm_SendServerCcs(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_SEND_SERVER_FINISHED:
    {
      TcpIp_TlsServerHsStm_SendServerFinished(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_HANDSHAKE_DONE:
    {
      TcpIp_TlsServerHsStm_FinalizeHandshake(TlsConIdx);
      break;
    }

    case TCPIP_TLS_STATE_HANDSHAKE_ABORT:
    {
      /* Nothing to do here */                                                                                         /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      break;
    }

    default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
    {
      /* Default case left blank intentionally */
      TCPIP_ASSERT_UNREACHABLE();
      break;
    } /* default */
  } /* switch() */

} /* TcpIp_TlsServerHsStm_PerfomNextHsStep() */

/**********************************************************************************************************************
*  TcpIp_TlsServerHsStm_ParseClientHello
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
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientHello(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType clientHelloIdx =
    TcpIp_GetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  TcpIp_ClientHelloLenOfTlsServerBufferMgmtType clientHelloLen
    = TcpIp_GetClientHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a message with the TLS-Handshake type ClientHello */
  if (clientHelloIdx != TCPIP_NO_TLSBUFFERRXCLIENTHELLOIDXOFTLSSERVERBUFFERMGMT)
  {
    /* #20 Check if we received the absolute minimum length for this type of message and forward the message to the specific parser */
    if (TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen(clientHelloLen, TCPIP_TLS_MIN_CLIENTHELLO_MSGLEN) == E_OK)
    {
      /* Extract the information inside the ClientHello message */
      retVal = TcpIp_TlsServerMsg_ExtractClientHelloInformation(TlsConIdx);

      /* #30 Check return value of extract function and switch to next state */
      TcpIp_TlsHsStm_ErrorHandlingAndStateTransition(TlsConIdx, retVal, TCPIP_TLS_STATE_SEND_SERVER_HELLO);

      /* Message processed, decrement the handshake RX indication counter by one */
      TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);

      /* Next state is a transmitting state (either send the ServerHello message or Abort state) so trigger the processing */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
  /* [REVIEW_c] open visal 16.00.00.2 Major: HsStmTxTriggerOfTlsConnectionDyn is never initialized. */
  /* [REVIEW_c] resolved visbdk: Done - See ESCAN00111435 fix in TcpIp_TlsCoreConnection_Init() */
  /* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
    }
    else
    {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
  /* [REVIEW_c] open visal 16.01.00.0 Improve: Add comment that an alert will be triggered. I hope that there will be an alert! */
  /* [REVIEW_c] resolved visbdk: See other finding. Changed the Impl */
  /* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      /* #40 else - length mismatch report an error to the user and trigger TLS-Alert */
      TcpIp_TlsUserErrorType clientHelloUserError;
      clientHelloUserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO;
      clientHelloUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN;
      clientHelloUserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(clientHelloUserError);

      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Move all further handling into the if-path. This should not be executed in case an error occurred. */
/* [REVIEW_c] comment visbdk: The alert is set due to the retVal of E_NOT_OK and the function "TcpIp_TlsHsStm_ErrorHandlingAndStateTransition" */
/* [REVIEW_c] comment visbdk: Nevertheless, Changed the Impl to a much cleaner way and add some additional Alert function  */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  }
  else
  {
  /* #50 otherwise, we received an unexpected message. Trigger the alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsServerHsStm_ParseClientHello() */

/**********************************************************************************************************************
*  TcpIp_TlsServerHsStm_ParseClientKeyExchange
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
      = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmtType clientKeyExchangeIdx =
      TcpIp_GetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a message with the TLS-Handshake type ClientKeyExchange */
  if (clientKeyExchangeIdx != TCPIP_NO_TLSBUFFERRXCLIENTKEYEXCHANGEIDXOFTLSSERVERBUFFERMGMT)
  {
    /* Reset the TX trigger */
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* #20 Forward the message to the specific parser */
    retVal = TcpIp_TlsServerMsg_ExtractClientKeyExchangeInformation(TlsConIdx);

    if (retVal == E_OK)
    {
      /* #30 Message parsed successfully - check if the parsing is completely done and change the state */
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else
      {
        /* #40 Parsing completely done. Change the state to TCPIP_TLS_STATE_WAIT_FOR_CLIENT_CCS */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_CCS);
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }
    }
    else
    {
      /* #50 Message parsing failed - handle error */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #60 otherwise, we received an unexpected message. Trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsServerHsStm_ParseClientKeyExchange() */

/**********************************************************************************************************************
*  TcpIp_TlsServerHsStm_ParseClientCcs
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientCcs(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received CCS message is valid */
  if (TcpIp_IsCcsRxIndicationOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    /* #20 Received CCS message is valid - next state is the parsing of the ClientFinished message */
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED);

    /* Lock the reception of a new CCS message after this point */
    TcpIp_SetCcsReceivableOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* Reset the CCS Rx Indication because we processed this message */
    TcpIp_SetCcsRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);

    /* #30 Check if the record_size_limit extension is enabled and the server received an offer from the client (via ClientHello message) */
    if (   (TcpIp_IsTlsUseExtensionRecordSizeLimitOfTlsConnection(TlsConIdx) == TRUE)
        && (TcpIp_IsExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx) == TRUE))
    {
      /* #40 Extension record size limit enabled, update the TX size */
      /* RFC8449 - 4.  The "record_size_limit" Extension
       *   This value is used to limit the size of records that are created when encoding application data
       *   and the protected handshake message into records. */
      TcpIp_SetActiveMaxTxRlSizeOfTlsConnectionDyn(TlsConIdx,
        TcpIp_GetTxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx));
    }
  }
  else
  {
    /* #50 Received CCS message is invalid - Trigger the transmission of the TLS alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsServerHsStm_ParseClientCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_ParseClientFinished
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerHsStm_ParseClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Prepare the message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_DONE)     /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is trigged (performed in lowPrio task) - leave this context */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Error during processing of the data - skip further data handling */
         && (retVal == E_OK))
  {

    /* Get the sub state of the TLS message parser */
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED:
      {
        /* #20 Extract the verify data value from the message */
        retVal = TcpIp_TlsServerMsg_ExtractClientFinishedInformation(TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Set next state only if preceding function call was OK. */
/* [REVIEW_c] resolved visbdk: Done via retVal check in while */
/* [REVIEW_c] open visal 16.03.00.0 Improve: No, I mean the result of TcpIp_TlsServerMsg_ExtractClientFinishedInformation. */
/* [REVIEW_c] resolved visbdk: Added additional comment, just like in the other states */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
        /* Error handling is done via return value in while condition - prepare next state transition */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_HASH);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_HASH:
      {
        /* #30 Trigger the calculation of finished hash */
        TcpIp_TlsServerMsg_CalcClientFinishedHash(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_FINISHED);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_FINISHED:
      {
        /* #40 Trigger calculation of the finished verify data via the PRF */
        TcpIp_TlsServerMsg_CalcClientFinishedVerifyData(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_VERIFY);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_VERIFY:
      {
        /* #50 Compare the calculated finished verify data with the received one */
        retVal = TcpIp_TlsServerMsg_CompareFinishedVerifyData(TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Set next state only if preceding function call was OK. */
/* [REVIEW_c] resolved visbdk: Done via retVal check in while */
/* [REVIEW_c] accepted visal 16.03.00.0 Improve: Processing is stopped in while-loop, but the handshake state is still already changed before that check. */
#  endif
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_DONE);
        break;
      }

      default:                                                                                                          /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      } /* default */
    } /* switch */
  } /* while */

  return retVal;
} /* TcpIp_TlsServerHsStm_ParseClientFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerHello
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: Something is strange with the whole CDD. This sounds more like receiving a message than sending one. */
/* [REVIEW_c] resolved visbdk: Reworked CDD */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Reset the TX trigger for the next state machine cycle */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Forward the message to the specific ServerHello preparation handler */
  retVal = TcpIp_TlsServerMsg_PrepareServerHello(TlsConIdx);

  if (retVal == E_OK)
  {

    TcpIp_TlsServerConnectionIterType tlsServerConIdx
      = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

    TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod
      = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

    TcpIp_SetHelloReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);

    /* #20 Message prepared successfully - Determine next state depending on key exchange mode */
    switch (keyExchangeMethod)
    {
      case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
      {
        /* #30 PSK based key exchange - Check if PSK hint should be transmitted and set the corresponding state */
        if (TcpIp_IsPskIdentityHintUsedOfTlsPskIdentity(TcpIp_GetTlsPskIdentityDefaultIdxOfTlsConnection(TlsConIdx)))
        {
          /* If default PSK identity is set, send PSK hint in server key exchange message */
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE);
        }
        else
        {
          /* No PSK identity is set - next state is ServerHelloDone */
          TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE);
        }
        break;
      }
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
      case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
      {
        /* #40 ECC based key exchange - transition to state TCPIP_TLS_STATE_SEND_SERVER_CERTIFICATE */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_CERTIFICATE);
        break;
      }
#  endif
      default:
      {
        /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the
        active cipher suite selected after receiving the client_hello message. */
        break;
      }
    } /* switch (keyExchangeMethod) */

    /* Next state is a transmitting state (either send the ServerHello message or Abort state) so trigger the processing */
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  }
  else
  {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: What can be the error reason? Should we send an "internal error" alert? */
/* [REVIEW_c] resolved visbdk: This is called when the preparation of the ServerHello failed - Alert is already set within the functions */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    /* #50 Message preparation failed - report error and trigger TLS-Alert */
    TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation(TlsConIdx);
  }
} /* TcpIp_TlsServerHsStm_SendServerHello() */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerCertificate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerCertificate(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Reset the TX trigger */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: It is not really a parser if it composes a message, right? */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
  /* #10 Forward the message to the specific composer */
  retVal = TcpIp_TlsServerMsg_PrepareServerCertificates(TlsConIdx);

  if (retVal == E_OK)
  {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Rework CDD comment, nothing is parsed here. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
    /* #20 Message composing successfully - Determine next state depending on key exchange mode */
    TcpIp_TlsServerConnectionIterType tlsServerConIdx
      = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

    TcpIp_SetCertificateReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);

    /* Determine next TLS handshake based on key exchange */
    if (TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx) == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH)
    {
      /* in case of an ECDH cipher, no key exchange message will be sent, so next state is HelloDone */
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE);
    }
    else /* TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE */
    {
      /* in case of an ECDHE cipher, key exchange message will be sent */
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE);
    }

    /* Next state is a transmitting state (either send the ServerKeyExchange/ServerHelloDone message or Abort state) so trigger the processing */
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  }
  else
  {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: CDD: Nothing has been parsed! Rework comment. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
    /* #30 Message composing failed - handle error */
    TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation(TlsConIdx);
  }
} /* TcpIp_TlsServerHsStm_SendServerCertificate() */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerKeyExchange
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Reset the TX trigger */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Rework all CDD comments in this function, there is no parser. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
  /* #10 Forward the message to the specific composer */
  retVal = TcpIp_TlsServerMsg_PrepareServerKeyExchange(TlsConIdx);

  if (retVal == E_OK)                                                                                                   /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
  {
    /* #20 Message composing successfully - check if the parsing is completely done and change the state */
    if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
    {
      /* Async operation pending, nothing to do - just leave the function */
    }
    else
    {
      /* #30 Parsing completely done. Change the state to TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE */
      TcpIp_TlsServerConnectionIterType tlsServerConIdx
        = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

      TcpIp_SetKeyExchangeReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);
      TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE);

      /* Next state is a transmitting state (either send the ServerHelloDone message or Abort state) so trigger the processing */
      TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
    }

  }
  else
  {
    /* #40 Message composing failed - handle error */
    TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation(TlsConIdx);
  }
} /* TcpIp_TlsServerHsStm_SendServerKeyExchange() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerHelloDone
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerHelloDone(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
/* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Reset the TX trigger */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Forward the message to the specific preparation function */
  TcpIp_TlsServerMsg_PrepareServerHelloDone(TlsConIdx);

  TcpIp_SetHelloDoneReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Next state is parsing Client key exchange */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE);

} /* TcpIp_TlsServerHsStm_SendServerHelloDone() */


/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_VerifyClientFinished
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
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_VerifyClientFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxClientFinishedIdxOfTlsServerBufferMgmtType clientFinishedIdx =
    TcpIp_GetTlsBufferRxClientFinishedIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received a message with the TLS-Handshake type ClientFinished */
  if (clientFinishedIdx != TCPIP_NO_TLSBUFFERRXCLIENTFINISHEDIDXOFTLSSERVERBUFFERMGMT)
  {
    /* #20 Forward the message to the specific parser */
    retVal = TcpIp_TlsServerHsStm_ParseClientFinished(TlsConIdx);

    if (retVal == E_OK)
    {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
  /* [REVIEW_c] open visal 16.01.00.0 Improve: The next comment is kind of confusing. parsing successful - check if parsing is done? */
  /* [REVIEW_c] resolved visbdk: Done */
  /* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      /* #30 Check if the message parsing is completely done and change the state accordingly */
      if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
      {
        /* Async operation pending, nothing to do - just leave the function */
      }
      else
      {
        /* #40 Parsing completely done. Change the state to TCPIP_TLS_STATE_SEND_SERVER_CCS */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_CCS);
        TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
        TcpIp_DecHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
      }
    }
    else
    {
      /* #50 Message parsing failed - handle error */
      TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
    }
  }
  else
  {
    /* #60 otherwise, we received an unexpected message. Trigger the alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
} /* TcpIp_TlsServerHsStm_VerifyClientFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerCcs(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the transmission of the TLS-Server CCS message */
  TcpIp_SetChangeCipherSpecReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Next state is send ServerFinished message */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_FINISHED);

  /* #20 Check if the record_size_limit extension is enabled and the server received an offer from the client (via ClientHello message) */
  if (   (TcpIp_IsTlsUseExtensionRecordSizeLimitOfTlsConnection(TlsConIdx) == TRUE)
      && (TcpIp_IsExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx) == TRUE))
  {
    /* #30 Update RX size - After this point we should only receive messages smaller than the offered value (via ServerHello message) */
    TcpIp_SetActiveMaxRxRlSizeOfTlsConnectionDyn(TlsConIdx,
      TcpIp_GetRxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx));
  }
} /* TcpIp_TlsServerHsStm_SendServerCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_SendServerFinished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_SendServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* #10 Forward the message to the specific preparation function */
  TcpIp_TlsServerMsg_PrepareServerFinished(TlsConIdx);

  /* #20 Message prepared successfully - check if the parsing is completely done and change the state */
  if (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_ASYNC_PENDING)
  {
    /* Async operation pending, nothing to do - just leave the function */
  }
  else
  {
    /* #30 Preparation completely done - Change the state to Finalize TLS handshake */
    TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
      = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

    TcpIp_TlsServerConnectionIterType tlsServerConIdx
      = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

    /* Trigger the transmission of the TLS-Server finished message */
    TcpIp_SetServerFinishedReadyToSendOfTlsServerConnection(tlsServerConIdx, TRUE);

    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_DONE);
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING);

    /* Reset UlRxIndication level here since we now accept application data */
    TcpIp_SetAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufMgmtIdx, 0u);
    /* Reset TLS Rx Ad fill level here since we now accept application data */
    TcpIp_SetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufMgmtIdx, 0u);
  }

} /* TcpIp_TlsServerHsStm_SendServerFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_FinalizeHandshake
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_FinalizeHandshake(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: Is it assured that the server finished message is already forwarded to TCP so that the buffer is completely available? */
/* [REVIEW_c] comment visbdk: Stored - Created TCPIP-6303 and we will analyze this (this will maybe lead to an ES-CAN) */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* The TX Read index is not used during handshake, so set it to the current position of the write index */
  TcpIp_SetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 Clear the TLS TxBuffer if configured */
  if (TcpIp_IsTlsClearBufferAfterHandshakeOfTlsConfig(TCPIP_TLSCONFIG_IDX) == TRUE)
  {
    /* Clear the handshake data in the TxBuffer from StartIdx to ReadIdx */
    TcpIp_TlsCoreBuffer_ClearTxBuffer(TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufMgmtIdx),
      TcpIp_GetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));
  }

  /* #20 Clear the TLS RxBuffer if configured */
  if (TcpIp_IsTlsClearBufferAfterHandshakeOfTlsConfig(TCPIP_TLSCONFIG_IDX) == TRUE)
  {
    /* Clear the handshake data in the RxBuffer from StartIdx to ReadIdx */
    TcpIp_TlsCoreBuffer_ClearRxBuffer(TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufMgmtIdx),
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));
  }

  /* Set the UpperLayer RX indication index to the current read index */
  TcpIp_SetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* Switch the state from FINALIZING to ESTABLISHED */
  TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_ESTABLISHED);

  /* #30 Notify Upper layer via TcpAccepted callback over the established TLS connection */
  TcpIp_TlsCoreUl_TcpAccepted(TlsConIdx);

} /* TcpIp_TlsServerHsStm_FinalizeHandshake() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Change function name to reflect that the minimum length is checked. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen(
  CONST(uint32, AUTOMATIC) MsgLen,
  CONST(uint32, AUTOMATIC) ExpectedMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the received message length against the minimum expected message length */
  if (MsgLen >= ExpectedMsgLen)
  {
    /* Length check OK */
   retVal = E_OK;
  }
  else
  {
    /* Length mismatch - return E_NOT_OK */
  }

  return retVal;
} /* TcpIp_TlsServerHsStm_VerifyExpectedMinimumMsgLen() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType hsUserError;
  TcpIp_TlsAlertLevelType alertLevel;
  TcpIp_TlsAlertDescriptionType alertDescription;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Prepare the user error and report it */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: Why is this only a generic function id and not specific for the three calls of this function? */
/* [REVIEW_c] resolved visbdk: Good point, but, this function is called on the "highest" level when an error occurs. So I think there is no need for the extra parameter  */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  hsUserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_HS_MSG;
  hsUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTHSMSG;
  hsUserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  TcpIp_TlsCoreError_ReportUserError(hsUserError);

  /* #20 Prepare the TLS alert and trigger the transmission of it */
  alertLevel       = TCPIP_TLS_ALERT_LEVEL_FATAL;
  alertDescription = TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE;

  TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);

  /* #30 Change the TLS connection state to HANDSHAKE_ABORT */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

} /* TcpIp_TlsServerHsStm_HandlesErrorDuringPreparation() */

/**********************************************************************************************************************
 *  TLS SERVER HANDSHAKE MESSAGE HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ExtractClientHelloInformation
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
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientHelloInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Index of the Start of the ClientHello message */
  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType clientHelloStartIdx =
    TcpIp_GetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  /* Length of the received ClientHello message */
  TcpIp_ClientHelloLenOfTlsServerBufferMgmtType clientHelloLen =
    TcpIp_GetClientHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  /* End index of the received ClientHello message - Need for in range checks inside the parser */
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) clientHelloEndIdx
    = clientHelloStartIdx + TCPIP_TLS_HSHDRLEN + clientHelloLen;

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Validate the HS major and minor TLS version */
  retVal = TcpIp_TlsMsg_HelloMsgGetVersionNr(TlsConIdx);

  if (retVal == E_OK)
  {
    /* #20 Store the received ClientHello random number */
    TcpIp_TlsMsg_HelloMsgGetRandom(TlsConIdx);

    /* #30 Get received session ID (sessions not supported by this implementation) */
    retVal = TcpIp_TlsMsg_HelloMsgGetSessionId(TlsConIdx, clientHelloEndIdx);
  }

  if (retVal == E_OK)
  {
    /* #40 Select a matching cipher suite for this connection */
    retVal = TcpIp_TlsServerMsg_ClientHelloGetCipherSuites(TlsConIdx, clientHelloEndIdx);
  }

  if (retVal == E_OK)
  {
    /* #50 Parse the received Compression Methods */
    retVal = TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods(TlsConIdx, clientHelloEndIdx);
  }

  if (retVal == E_OK)
  {
    /* #60 Parse the received ClientHello extensions */
    retVal = TcpIp_TlsServerMsg_ClientHelloGetExtensions(TlsConIdx, clientHelloEndIdx);
  }

  if (retVal == E_OK)
  {
    /* #70 Check if there is some more unparsed information in the buffer */
    retVal = TcpIp_TlsMsg_CheckMsgForRemainingData(TlsConIdx, clientHelloEndIdx);
  }

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
  /* #80 Add the client random to the Msa_AccessBuffer if enabled */
  if (retVal == E_OK)
  {
    TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer(TlsConIdx);
  }
#  endif

  return retVal;
} /* TcpIp_TlsServerMsg_ExtractClientHelloInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ExtractClientKeyExchangeInformation
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientKeyExchangeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: CDD comment: The function does not prepare a message.... */
/* [REVIEW_c] resolved visbdk: Copy and paste issue - Fixed the CDD */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* #10 Parse the ClientKeyExchange message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)  != TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_DONE)/* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is triggered in one of the sub states, switch to lowPrio context - leave this function */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Error during parsing - abort next steps */
         && (retVal == E_OK) )
  {
    /* Sub-state machine for ClientKeyExchange message */
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE:
      {
        /* #20 Select next sub state depending on selected key exchange */
        TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod;
        TcpIp_TlsHandshakeState nextState = TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE;

        /* At this point its OK to receive the CCS message */
        TcpIp_SetCcsReceivableOfTlsConnectionDyn(TlsConIdx, TRUE);

        keyExchangeMethod = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

        switch (keyExchangeMethod)
        {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
          {
            /* ECC based key exchange - Next sub state is processing of ECC parameter */
            nextState = TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS;
            break;
          }
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
          case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
          {
            /* PSK based key exchange - Next state is processing of PSK parameter */
            nextState = TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS;
            break;
          }
#  endif
          default:
          {
            /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the
            active cipher suite selected after receiving the client_hello message. */
            break;
          }
        }  /* switch (keyExchangeMethod) */

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, nextState);

          break;
      } /* case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS:
      {
        /* #30 Processing of ECC parameter */
        retVal = TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation(TlsConIdx);
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Only switch to next state if function returns E_OK. */
/* [REVIEW_c] comment visbdk: Unnecessary, because if retVal = E_NOT_OK the while loop is stopped and the sate not relevant any more */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Add a comment to explain why this state can always be set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
        /* Error handling is done via return value in while condition - prepare next state transition */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET);
        break;
      }
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS:
      {
        /* #40 Processing of PSK parameter */
        retVal = TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation(TlsConIdx);
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Only switch to next state if function returns E_OK. */
/* [REVIEW_c] comment visbdk: Unnecessary, because if retVal = E_NOT_OK the while loop is stopped and the sate not relevant any more */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Add a comment to explain why this state can always be set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
        /* Error handling is done via return value in while condition - prepare next state transition */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET);
        break;
      }
#  endif
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET:
      {
        /* #50 Trigger calculation of Master secrete */
        /* This operation is time consuming and thus is calculated in the lowPrio (async) task.
           Trigger the calculation, leaf this context and return if the operation is done */
        TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC:
      {
        /* #60 Asynchronous validation performed, reset the connection state */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_DONE);
        break;
      }

      default:                                                                                                         /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch() */
  } /* while() */
  return retVal;
}
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_DONE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
            /* Async operation is triggered in one of the sub states, switch to lowPrio context - leave this function */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
            /* Error during parsing - abort next steps */
        && (retVal == E_OK))
  {
    /* Sub-state machine for Client key exchange message */
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS:
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_GET_PARAMS:
      {
        /* #20 Parse the received ECC Client parameter */
        retVal = TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams(TlsConIdx);
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Only enhance state if function returned E_OK. */
/* [REVIEW_c] comment visbdk: Unnecessary, because if retVal = E_NOT_OK the while loop is stopped and the sate not relevant any more */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Add a comment to explain why this state can always be set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
        /* Error handling is done via return value in while condition - prepare next state transition */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_CALC_DH_SHARED_SECRET);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_CALC_DH_SHARED_SECRET:
      {
        /* #30 Trigger the calculation of the DH shared secret */
        TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret(TlsConIdx);
        /* This operation is time consuming and thus is calculated in the lowPrio (async) task.
           Trigger the calculation, leave this context and return if the operation is done */
        break;
      }

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Question: Describe what this case is for. When will we reach this state, and what will be done next? */
/* [REVIEW_c] resolved visbdk: State is not needed anymore - deleted it. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
      default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch() */
  } /* while() */

  return retVal;
} /* TcpIp_TlsServerMsg_ClientKeyExchangeGetEcdheEcdsaInformation */
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_open 16.00.00.x PSK
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the message until we are done AND no Async context needs to be computed */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Question: Is it necessary to repeat the same state checks as in the calling function? */
/* [REVIEW_c] resolved visbdk: Yes, otherwise we will end up in an endless loop in this while */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_DONE) /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is triggered in one of the sub states, switch to lowPrio context - leave this function */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Error during parsing - abort next steps */
         && (retVal == E_OK))
  {
    /* Sub-state machine for Client key exchange message */
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS:
      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_GET_PARAMS:
      {
        /* #20 Parse the received PSK parameter */
        retVal = TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams(TlsConIdx);
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Only enhance state if function returned E_OK. */
/* [REVIEW_c] comment visbdk: Unnecessary, because if retVal = E_NOT_OK the while loop is stopped and the sate not relevant any more */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Add a comment to explain why this state can always be set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
        /* Error handling is done via return value in while condition - prepare next state transition */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_CALC_PREMASTER_SECRET);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_CALC_PREMASTER_SECRET:
      {
        /* #30 Trigger the calculation of the PSK premaster secret */
        /* This operation is time consuming and thus is calculated in the lowPrio (async) task.
           Trigger the calculation, leaf this context and return if the operation is done */
        TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_DONE);
        break;
      }

      case TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_DONE:
      {
        break;
      }

      default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch() */
  } /* while() */

  return retVal;
} /* TcpIp_TlsServerMsg_ClientKeyExchangeGetPskInformation */
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON */
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ExtractClientFinishedInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ExtractClientFinishedInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxClientFinishedVerifyDataIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx);

  /* rxClientFinishedVerifyDataIdx is pointing to the start of the message, therefore -1 is pointing to the length at the beginning */
  uint8 rxClientFinishedVerifyDataLen = TcpIp_GetTlsBufferRx(rxClientFinishedVerifyDataIdx - 1u);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the received Client finished verify data length against the expected one */
  if (rxClientFinishedVerifyDataLen == TCPIP_TLS_FINISHED_VERIFYDATA_LEN)
  {
    /* #20 Received length match - store the index of the finished verify data */
    /* Save the position of the received ClientFinishedVerifyData */
    TcpIp_SetTlsBufferRxClientFinishedVerifyDataIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
      rxClientFinishedVerifyDataIdx);

    /* Increment the Rx buffer ReadIdx by the length of the VerifyData (12Byte) */
    TcpIp_SetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
      rxClientFinishedVerifyDataIdx + TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

    retVal = E_OK;
  }
  else
  {
    /* #30 else - Received length mismatch - Report the error to the user and trigger TLS alert */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERFINISHED;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    /* Trigger alert TCPIP_TLS_ALERT_DESC_DECODE_ERROR in case of invalid length */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ExtractClientFinishedInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_CalcClientFinishedHash
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_CalcClientFinishedHash(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcClientFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_CalcClientFinishedHash() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_CalcClientFinishedVerifyData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_CalcClientFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcClientFinishedVerifyDataAsyncFlagOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_CalcClientFinishedVerifyData() */


/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_CompareFinishedVerifyData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
  */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_CompareFinishedVerifyData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Calculated data is present in Temp buffer */
  TCPIP_P2C(uint8) calculatedVerifyDataPtr = TcpIp_GetAddrTlsTemporaryFinishedBuffer(
    TcpIp_GetTlsTemporaryFinishedBufferStartIdxOfTlsConnection(TlsConIdx));

  TCPIP_P2C(uint8) receivedVerifyDataPtr = TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxClientFinishedVerifyDataIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

  /* #10 Compare the calculated and received TLS finished verify data */
  if (IpBase_StrCmpLen(receivedVerifyDataPtr, calculatedVerifyDataPtr, TCPIP_TLS_FINISHED_VERIFYDATA_LEN) == E_OK)
  {
    /* #20 Values match - return E_OK */
    retVal = E_OK;
  }
  else
  {
    /* #30 Value mismatch - Report an error to the user and trigger TLS alert */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERFINISHED;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTVERIFYDATA;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR);
  }
  return retVal;
} /* TcpIp_TlsServerMsg_CompareFinishedVerifyData() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloGetCipherSuites
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetCipherSuites(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) ClientHelloEndIdx )
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the received cipher suite list length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Minor: Check that 2 bytes are available before reading the 2 bytes length field. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),                 /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        TCPIP_TLS_CIPHERSUITESLEN_LEN, ClientHelloEndIdx))
  {
    /* Get the length of the received cipher suite list */
    uint16 cipherSuitesLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u);

    /* Maintain AdHs read index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use "Add" macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_CIPHERSUITESLEN_LEN);

    /* see RFC5246 - A.5.  The Cipher Suite */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: (cipherSuitesLen >= 2u) would be more readable. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Question: What is a CipherSuite pair? Rework the comment to be more clear. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    if ((cipherSuitesLen >= 2u) /* Cipher suite ID contains minimum of 2 bytes */                                       /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* and the length information is send pairwise, so the length must be even */
      && ((cipherSuitesLen % 2u) == 0u)
      /* Check the range */
      && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(                                                                              /* PRQA S 2995 2 */ /* MD_TcpIp_Tls_2995 */
        TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx), cipherSuitesLen, ClientHelloEndIdx)))
    {
      /* #20 Cipher suite list length match - Search for a matching cipher worker which suits this connection */
      retVal = TcpIp_TlsServerMsg_SelectMatchingCipherWorker(TlsConIdx, cipherSuitesLen);

      /* Maintain AdHs read index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use "Add" macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, cipherSuitesLen);
    } /* Range check failed. E_NOT_OK */
  } /* Overall range check failed. E_NOT_OK */

  /* #30 Received cipher suite list length mismatch - Report an error to the user and trigger TLS alert */
  if (retVal != E_OK)
  {
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCIPHERLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloGetCipherSuites() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the received compression method length */
  /* Get the length of the received compression method list */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Minor: Check that 1 byte is available before reading the compression methods length field. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),                 /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        TCPIP_TLS_COMPMETHLEN_LEN, HelloEndIdx))
  {
    uint8 receivedCompressionMethodsLen = IpBase_GetUint8(
      TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u);

    /* Maintain AdHs read index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_COMPMETHLEN_LEN);

    /* Accordingly to RFC5246: At least one compression method must be received */
    if ((receivedCompressionMethodsLen >= 1u)
      /* Range check */
      && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),             /* PRQA S 3415, 2995 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly, MD_TcpIp_Tls_2995 */
        receivedCompressionMethodsLen, HelloEndIdx)))
    {
      /* #20 Received compression method length match - Select matching local compression method */
      retVal = TcpIp_TlsMsg_SelectMatchingCompressionMethod(TlsConIdx, receivedCompressionMethodsLen);

      /* Maintain AdHs read index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, receivedCompressionMethodsLen);
    } /* Range check failed. E_NOT_OK */
  } /* Overall range check failed. E_NOT_OK */

  /* #30 Received compression method length mismatch - Report an error to the user and trigger TLS-Alert */
  if (retVal != E_OK)
  {
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_USERERROR_PARSEHELLO(TlsConIdx);
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTCOMPRESSIONLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Set TLS alert here because detailed error condition is known here. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloGetCompressionMethods() */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_SelectMatchingCompressionMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_SelectMatchingCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     CompressionMethodLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint8_least compressionMethodIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all received compression methods and check if we receive at least one supported compression method */
  for (compressionMethodIter = 0; compressionMethodIter < CompressionMethodLen; compressionMethodIter++)
  {
    uint8 receivedCompressionMethod = TcpIp_GetTlsBufferRx(
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + compressionMethodIter);

    /* #20 Compare received compression method with the supported one NONE(0x00) */
    /* Accordingly to RFC5246 - Section 7.4.1.2 Client Hello at least the NONE method must be supported */
    if (receivedCompressionMethod == TCPIP_TLS_COMPRESSION_METHOD_NONE)
    {
      /* Valid compression method received - return E_OK and skip further processing */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsMsg_SelectMatchingCompressionMethod() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloGetExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloGetExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) ClientHelloEndIdx )
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the received extensions list length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Minor: Add check that at least 2 bytes are available for reading. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  /* #20 Check if we received TLS Hello-Extensions and parse them */

  if (TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) == ClientHelloEndIdx)
  {
    /* No extensions have been detected */
    retVal = E_OK;
  }
  else
  {
    /* Extensions present, parse them */
    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),
         TCPIP_TLS_EXTENSION_LENGTH_LEN, ClientHelloEndIdx))
    {
      uint16 extensionsLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
        TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u);

      /* Maintain AdHs read index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN);

      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),             /* PRQA S 2995 2 */ /* MD_TcpIp_Tls_2995 */
            extensionsLen, ClientHelloEndIdx))
      {
        /* #30 Forward all received extensions to the specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions(TlsConIdx,
          extensionsLen, ClientHelloEndIdx);
      } /* Range check extension length */
    } /* Range check overall extension length */
  }
  /* #40 Extensions list length mismatch - Report an error to the user and trigger TLS-Alert */
  if (retVal != E_OK)
  {
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTEXTENSIONSLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Set alert here since detailed error information is available here. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloGetExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16                      ExtensionsLen,
  TcpIp_TlsBufferRxIterType   HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsExtensionType listOfReceivedExtensions[TCPIP_TLS_MAX_EXTENSION_LIST_LENGTH] = { 0 };
  uint8 overallNumberOfReceivedExtensions = 0u;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Improve: This check is already done in the calling function. Please verify that I'm right. */
/* [REVIEW_c] resolved visbdk: Correct, removed the check. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  /* #10 Iterate over the extension data and extract each extension into overall list of received extensions */
  if (TcpIp_TlsHelloMsg_ExtractReceivedExtensions(TlsConIdx, ExtensionsLen, HelloEndIdx,
        &listOfReceivedExtensions[0], &overallNumberOfReceivedExtensions) == E_OK)
  {
    /* #20 Check for duplicated received extensions */
    if (TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions(&listOfReceivedExtensions[0],
          overallNumberOfReceivedExtensions) == E_OK)
    {
      /* #30 Parse received extensions */
      if (TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions(TlsConIdx, &listOfReceivedExtensions[0],                /* PRQA S 2991, 2995 2 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
            overallNumberOfReceivedExtensions) == E_OK)
      {
        /* #40 All extension fully validated and parsed - return E_OK */
        retVal = E_OK;
      }
      /* else - TLS-Alert handling is done in the context of the extension parser */
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

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Set specific alert in each else-path (some are missing). If all alerts are the same, setting the alert can be done at the end of this function. */
/* [REVIEW_c] resolved visbdk: Done, added also a new comment in the "missing" else path */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseAndValidateExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions
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
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 rxExtensionIter;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all received client extensions */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Cancel the for-loop when the return value is not OK. */
/* [REVIEW_c] resolved visbdk: Done, see end of for-loop  */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  for (rxExtensionIter = 0u; rxExtensionIter < ReceivedExtensionCnt; rxExtensionIter++)
  {
    /* Get the next received extension type and parse it depending on the type */
    uint16 currentReceivedExtensionType = ReceivedExtensionListPtr[rxExtensionIter].Type;

    switch (currentReceivedExtensionType)
    {
      case TCPIP_TLS_EXTENSION_SERVER_NAME_INDICATION:
      {
        /* #20 In case of extension type server_name_indication (0) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION:
      {
        /* #30 In case of extension type trusted_ca_keys (3) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST:
      {
        /* #40 In case of extension type status_request (5) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS:
      {
        /* #50 In case of extension type supported_groups (10) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_EC_POINT_FORMAT:
      {
        /* #60 In case of extension type ec_point_formats(11) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }
      case TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS:
      {
        /* #70 In case of extension type signature_algorithms (13) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }

      case TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT:
      {
        /* #80 In case of extension type record_size_limit (28) - forward to specific parser */
        retVal = TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit(TlsConIdx,
          ReceivedExtensionListPtr[rxExtensionIter]);
        break;
      }

      default:
      {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Don't call a function but simply skip this extension. The length is already checked. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
        /* #90 In case of unknown extension type - Skip extension processing */
        break;
      }
    }

    /* Stop processing in case of occurred error during parsing of received extensions */
    if (retVal != E_OK)
    {
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseReceivedExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsRxLengthChecks_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType ServerNameIndicationExtension)
{
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Not yet implemented, story is planned. Will be reviewed later. */
/* [REVIEW_c] resolved visal: Implemented */
/* [REVIEW_c] accepted visal, visbdk 16.03.00.0 Statement: Impl done and OK. */
#  endif

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extServerNameListLenIdx = ServerNameIndicationExtension.StartIdx;
  uint16 overallExtLength = ServerNameIndicationExtension.Length;
  TcpIp_TlsBufferRxIterType extServerNameIndicationEndIdx = extServerNameListLenIdx + overallExtLength;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* Server Name Indication Extension Format (RFC 6066)
   *
   *
   *                             -> extServerNameListLenIdx
   *                            /                     -> extServerNameStartIdx
   *                           /                     /
   *       [ext Type][ext Len][Server Name List Len][name 1]             [name n]
   * Byte: 0       1 2      3 4                   5 6                    (x-1) x
   *                                                 \---consumedExtensionLen---/
   *                           \---overallExtLength-----------------------------/
   */

  /* Range check before read out the received Server Name List length (2Bytes) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extServerNameListLenIdx,
        TCPIP_TLS_EXTENSION_SERVER_NAME_LIST_LENGTH_LEN, extServerNameIndicationEndIdx))
  {
    /* #10 Get the length of the received Server Name Indication list and check against the overall length. */
    uint16 receivedServerNameListLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extServerNameListLenIdx), 0u);

    if (overallExtLength == (receivedServerNameListLen + TCPIP_TLS_EXTENSION_SERVER_NAME_LIST_LENGTH_LEN))
    {
      TcpIp_TlsBufferRxIterType extServerNameStartIdx
        = extServerNameListLenIdx + TCPIP_TLS_EXTENSION_SERVER_NAME_LIST_LENGTH_LEN;

      /* #20 Check the length of the received Server Name Indication list for plausibility. */
      /* RFC 6066 - 3.  Server Name Indication */
      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extServerNameStartIdx, receivedServerNameListLen, extServerNameIndicationEndIdx))/* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
      {
        TcpIp_TlsBufferRxIterType extServerNameEndIdx = extServerNameStartIdx + receivedServerNameListLen;
        TcpIp_TlsBufferRxIterType extServerNameIter;
        uint16 remainingLen;
        boolean hostNameReceived = FALSE;

        /* #30 Iterate over all received Server Names and check their format to be valid. */
        /* The server name list must contain at least one element. */
        extServerNameIter = extServerNameStartIdx;
        retVal = E_OK;
        remainingLen = receivedServerNameListLen;

        while (   (extServerNameIter < extServerNameEndIdx)
               && (retVal == E_OK)
               && (remainingLen >= TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN)
               && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extServerNameIter, TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
                     extServerNameIndicationEndIdx)))
        {
          uint16 serverNameLen;  /* Length of the server name element (including type field)  */

          retVal = TcpIp_TlsServertMsg_ClientHelloExtIsServerNameAcceptable(TlsConIdx, extServerNameIter,
                     extServerNameIndicationEndIdx, &serverNameLen, &hostNameReceived);
          if (retVal == E_OK)
          {
            /* Increase the position by the length of the server name element. */
            extServerNameIter += (TcpIp_TlsBufferRxIterType)serverNameLen;
            /* Reduce the remaining length for all received server names. */
            remainingLen     -= serverNameLen;
          }
        }  /* while */

        if ((retVal != E_OK) || (remainingLen != 0u) || (extServerNameStartIdx == extServerNameEndIdx))
        {
          /* Format error found in this extension - report error and trigger TLS alert */
          /* There may not be any remaining data in the extension that can not be assigned to a server name, and the
          list of server names may not be empty. */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
        }
      }
      else
      {
        /* Received Server Name Indication length mismatch - report error and trigger TLS alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* Overall received length mismatch - report error and trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionServerNameIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsServertMsg_ClientHelloExtIsServerNameAcceptable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsServerNameAcceptable(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferRxIterType ServerNameStartIdx,
  TcpIp_TlsBufferRxIterType ServerNameIndicationEndIdx,
  TCPIP_P2V(uint16) ServerNameLenPtr,
  TCPIP_P2V(boolean) HostNameReceivedPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2C(uint8) serverNamePtr = TcpIp_GetAddrTlsBufferRx(ServerNameStartIdx);
  uint8  nameType;  /* Type of the name element */
  uint16 nameLen;   /* Length of the name element (without its length field) */
  TcpIp_TlsBufferRxIterType nameStringStartIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* RFC 6066 defines only one valid name type for server name elements. For this type 'host_name' the name must have a
     length of at least 1 byte.
     Other name types are currently unknown, but their value also must start with a 2 byte length field. These other
     name types shall be ignored by this implementation. */

  /* #10 Read the name type and name length. */
  /* The calling function already checked the availability of the 1 byte for the type and the 2 bytes for the length field. */
  nameType = IpBase_GetUint8(serverNamePtr, 0u);
  nameLen  = IpBase_GetUint16(serverNamePtr, TCPIP_TLS_EXTENSION_SERVER_NAME_NAME_TYPE_LEN);

  /* #20 Check that the name fits into the extension. */
  nameStringStartIdx = ServerNameStartIdx + TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN;
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(nameStringStartIdx, nameLen, ServerNameIndicationEndIdx))
  {
    /* The name fits into the extension */

    /* #30 Analyze the server name element, depending on its type. */
    switch (nameType)
    {
      case TCPIP_TLS_EXTENSION_SERVER_NAME_TYPE_HOST_NAME:
      {
        /* This is the only supported kind of server name, but the name will be ignored. It is only checked that the length of the name is at least 1. */

        if (   (nameLen >= TCPIP_TLS_EXTENSION_SERVER_NAME_HOST_NAME_MIN_LEN)
            && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(nameStringStartIdx, nameLen, ServerNameIndicationEndIdx)))              /* PRQA S 2995 */ /* MD_TcpIp_Tls_2995 */
        {
          /* host name format is OK */
          *ServerNameLenPtr = (TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN + nameLen);

          /* #40 Ensure that host name element is only received once. */
          if (*HostNameReceivedPtr == FALSE)
          {
            /* received first server name of type 'host_name' */
            *HostNameReceivedPtr = TRUE;
            retVal = E_OK;
          }
          else
          {
            /* Error, host name received more than once. */
            TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_ILLEGAL_PARAM);
          }
        }
        else
        {
          /* error, the host name format is not OK */
        }
        break;
      }
      default:
      {
        /* Unknown name type. The general format (according to RFC 6066) is OK, no further checks are applied. */
        /* For unknown name types it is not checked that they are only received once. */
        *ServerNameLenPtr = (TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN + nameLen);
        retVal = E_OK;
        break;
      }
    }  /* switch */
  }
  else
  {
    /* Error, the name does not fit into the extension */
  }

  return retVal;
}  /* TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable */


/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType TrustedCaIndicationExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extTrustedCaIndicationLenIdx = TrustedCaIndicationExtension.StartIdx;
  uint16 overallExtLength = TrustedCaIndicationExtension.Length;
  TcpIp_TlsBufferRxIterType extTrustedCaIndicationEndIdx = extTrustedCaIndicationLenIdx + overallExtLength;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* Trusted CA Indication Extension Format
   *
   *
   *                             -> extTrustedCaIndicationLenIdx
   *                            /                          -> extTrustedCaStartIdx
   *                           /                          /
   *       [ext Type][ext Len][Trusted CA Indication Len][hash 1]             [hash n]
   * Byte: 0       1 2      3 4                        5 6    25              (x-1) x
   *                                                      \---consumedExtensionLen---/
   */

  /* Range check before read out the received Trusted CA Indication length (2Bytes) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extTrustedCaIndicationLenIdx,
        TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN, extTrustedCaIndicationEndIdx))
  {
    /* #10 Get the length of the received Trusted CA Indication list and check against the overall length */
    uint16 receivedTrustedCaIndicationLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extTrustedCaIndicationLenIdx), 0u);

    if (overallExtLength == (receivedTrustedCaIndicationLen + TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN))
    {
      TcpIp_TlsBufferRxIterType extTrustedCaStartIdx
        = extTrustedCaIndicationLenIdx + TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN;

      /* #20 Check the length of the received Trusted CA Indication list for plausibility */
      /* RFC 6066 - 6.  Trusted CA Indication */
      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extTrustedCaStartIdx, receivedTrustedCaIndicationLen, extTrustedCaIndicationEndIdx))/* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
      {
        TcpIp_TlsBufferRxIterType extTrustedCaEndIdx = extTrustedCaStartIdx + receivedTrustedCaIndicationLen;
        TcpIp_TlsBufferRxIterType extTrustedCaIter;
        uint16 remainingLen;

        /* #30 Iterate over all received Trusted Authorities and check their format to be valid */
        extTrustedCaIter = extTrustedCaStartIdx;
        retVal = E_OK;
        remainingLen = receivedTrustedCaIndicationLen;

        while (   (extTrustedCaIter < extTrustedCaEndIdx)
               && (retVal == E_OK)
               && (remainingLen >= TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN)
               && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extTrustedCaIter, TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
                     extTrustedCaIndicationEndIdx)))
        {
          uint16 trustedAuthorityLen;
          retVal = TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable(extTrustedCaIter,
                     extTrustedCaIndicationEndIdx, &trustedAuthorityLen);
          if (retVal == E_OK)
          {
            /* Increase the position by the length of the trusted authority element. */
            extTrustedCaIter += (TcpIp_TlsBufferRxIterType)trustedAuthorityLen;
            /* Reduce the remaining length for all received trusted authorities. */
            remainingLen     -= trustedAuthorityLen;
          }
        }  /* while */

        if (retVal != E_OK)
        {
          /* Format error found in this extension - report error and trigger TLS alert */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
        }
      }
      else
      {
        /* Received Trusted CA Indication length mismatch - report error and trigger TLS alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* Overall received length mismatch - report error and trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }

  return retVal;

} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionTrustedCaIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable(
  TcpIp_TlsBufferRxIterType TrustedAuthorityStartIdx,
  TcpIp_TlsBufferRxIterType TrustedCaIndicationEndIdx,
  TCPIP_P2V(uint16) TrustedAuthorityLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2C(uint8) trustedAuthorityPtr = TcpIp_GetAddrTlsBufferRx(TrustedAuthorityStartIdx);
  uint8  identifierType;
  uint16 identifierLen = 0;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Analyze the trusted authority element, depending on its type. */

  /* Get the received Trusted Authority element type. */
  /* The availability of the 1 byte for the authority type is assured in the calling function. */
  identifierType = IpBase_GetUint8(trustedAuthorityPtr, 0u);

  /* Proceed depending on the type of the trusted authority. */
  switch (identifierType)
  {
    case TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_PRE_AGREED:
    {
      /* Pre-agreed trusted authorities */
      /* identifierLen already is set to 0 */
      break;
    }
    case TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_KEY_SHA1_HASH:
    {
      /* Hash of the public key */
      identifierLen = TCPIP_TLS_HASH_SHA1_LEN;
      /* This kind of trusted authority hint is not supported and will be ignored. */
      break;
    }
    case TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_X509_NAME:
    {
      /* Distinguished name */
      TcpIp_TlsBufferRxIterType distinguishedNameStartIdx = TrustedAuthorityStartIdx + TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN;

      /* This kind of trusted authority hint is not supported and will be ignored. Only the length of the whole
      distinguished name is checked to be valid. */

      /* Check if at least 2 bytes for the length field are available */
      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(distinguishedNameStartIdx,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
          TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_LENGTH_LEN, TrustedCaIndicationEndIdx))
      {
        identifierLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(distinguishedNameStartIdx), 0u)
                        + TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_LENGTH_LEN;

        /* Check that distinguished name is at least 1 byte long. */
        if (identifierLen < (TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_LENGTH_LEN + TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_MIN_LEN))
        {
          retVal = E_NOT_OK;
        }
      }
      else
      {
        /* error, the length field does not fit into the received extension */
        retVal = E_NOT_OK;
      }
      break;
    }
    case TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_CERT_SHA1_HASH:
    {
      /* Hash of the complete certificate */
      identifierLen = TCPIP_TLS_HASH_SHA1_LEN;

      /* This is the only kind of trusted authority hints we want to accept. Implementing this feature is not
      yet planned, so this trusted authority hint will be ignored. */
      break;
    }
    default:
    {
      /* error, invalid type */
      retVal = E_NOT_OK;
      break;
    }
  }

  /* #20 Check that the length of the trusted authority element is not too big. */
  if ((retVal == E_OK)
    && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE((TrustedAuthorityStartIdx + TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN),           /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
      identifierLen, TrustedCaIndicationEndIdx)))
  {
    /* OK, length of the TrustedAuthority fits into the received extension */
    /* #30 Set the trusted authority length if the element has a valid format. */
    *TrustedAuthorityLenPtr = (TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN + identifierLen);
  }
  else
  {
    /* error, length of the TrustedAuthority does not fit into the received extension */
    retVal = E_NOT_OK;
  }

  return retVal;
}  /* TcpIp_TlsServertMsg_ClientHelloExtIsTrustedAuthorityAcceptable */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType CertificateStatusRequestExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extCertStatusTypeIdx = CertificateStatusRequestExtension.StartIdx;
  uint16 overallExtLength = CertificateStatusRequestExtension.Length;
  TcpIp_TlsBufferRxIterType extCertStatusRequestEndIdx = extCertStatusTypeIdx + overallExtLength;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* Certificate Status Request Extension Format
   *
   *
   *                              +-> extCertStatusTypeIdx
   *                             /                 +-> extResponderIdListIdx
   *                            /                 /                  +-> extRequestExtensionsIdx
   *                           /                 /                  /
   *       [ext Type][ext Len][Cert Status Type][Responder ID List][Request Extensions]
   * Byte: 0       1 2      3 4                 5                   m
   * OCSP:                                      [OCSP StatusRequest                   ]
   */

  /* Range check before read out the received Cert Status Type (1 Byte) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extCertStatusTypeIdx,
        TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN, extCertStatusRequestEndIdx))
  {
    /* #10 Get the type of the received Cert Status Request. */
    uint8 receivedCertStatusType = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(extCertStatusTypeIdx), 0u);


    /* Check request type */
    switch (receivedCertStatusType)
    {
      case TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_OCSP_TYPE:
      {
        /* #20 Check the responder id list. */

        TcpIp_TlsBufferRxIterType extResponderIdListIdx  /* start index of the responder id list */
          = extCertStatusTypeIdx + TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN;
        uint16 totalResponderIdListLen;  /* length of the responder id list, including length field */

        retVal = TcpIp_TlsServerMsg_ClientHello_CheckOcspResponderIdList(extResponderIdListIdx,
                   extCertStatusRequestEndIdx, &totalResponderIdListLen);
        if (retVal == E_OK)
        {
          TcpIp_TlsBufferRxIterType extRequestExtensionsIdx = extResponderIdListIdx + totalResponderIdListLen;

          /* #30 Check the request extensions (can be an empty element). */
          uint16 totalRequestExtensionsLen;  /* length of the request extensions, including length field */
          retVal = TcpIp_TlsServerMsg_ClientHello_CheckOcspRequestExtensions(extRequestExtensionsIdx,
                     extCertStatusRequestEndIdx, &totalRequestExtensionsLen);
          if (   (retVal == E_OK)
              && ((TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN + totalResponderIdListLen
                   + totalRequestExtensionsLen) == overallExtLength))
          {
            /* The extension is well formated. */
            /* retVal is already set to E_OK. */
          }
          else
          {
            /* Error when processing the request extensions, or there are some bytes remaining after the request
            extensions. */
            retVal = E_NOT_OK;
          }
        }
        else
        {
          /* Error when processing the responder id list */
        }
        break;
      }
      default:
      {
        /* Error, not supported status type */
        break;
      }
    }  /* switch */
  }
  else
  {
    /* Error, extension is too short for the type field. */
  }

  if (retVal != E_OK)
  {
    /* Error when processing the extension, set an alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionCertificateStatusRequest() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHello_CheckOcspResponderIdList
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsRxLengthChecks_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHello_CheckOcspResponderIdList(
  TcpIp_TlsBufferRxIterType ResponderIdsListStartIdx,
  TcpIp_TlsBufferRxIterType CertStatusRequestEndIdx,
  TCPIP_P2V(uint16) TotalResponderIdListLenPtr)
{
  /* Analyze OCSP Status Request responder ID list */

  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* Certificate Status request Extension Format
   *                                             +-> ResponderIdsListStartIdx: total length of all responder IDs
   *                                            /                      +-> list of OCSP responders that the client trusts (optional)
   *                                           /                      /
   *       [ext Type][ext Len][ CertStatusType][responder_id_list Len][responder_id 1]... [request_extensions]
   * Byte: 0       1 2      3               4 5                    6  7                   m
   *                                                                 [id_len][id    ]
   *                                                                  \       \-> extResponderIdContentIdx: responder id
   *                                                                   \-> extResponderIdLenIdx: responder id len
   */

  /* #10 Check the responder id list overall length. */
  /* Check that 2 bytes for the responder id list length are available */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(ResponderIdsListStartIdx,
    TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN, CertStatusRequestEndIdx))
  {
    uint16 extResponderIdListLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(ResponderIdsListStartIdx), 0u);
    TcpIp_TlsBufferRxIterType extResponderIdLenIdx = ResponderIdsListStartIdx
      + TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN;
    uint16 totalResponderIdListLen = TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN;

    /* Check that the list of responder ids fits into the extension */
    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extResponderIdLenIdx,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
      extResponderIdListLen, CertStatusRequestEndIdx))
    {
      /* #20 Process the responder id list if it is not empty. */
      if (extResponderIdListLen != 0u)
      {
        uint16 remainingListLen = extResponderIdListLen;
        Std_ReturnType innerRetVal = E_OK;

        /* #30 Iterate over all responder ids that are contained in the list. */
        while (   (remainingListLen >= TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_TOTAL_MIN_LEN)
               && (innerRetVal == E_OK))
        {
          /* #40 Check the length of each responder id element. */
          /* Check length of list element, minimum 2 bytes length field and 1 byte responder id */
          if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extResponderIdLenIdx,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
            TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_TOTAL_MIN_LEN, CertStatusRequestEndIdx))
          {
            uint16 extResponderIdLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extResponderIdLenIdx), 0u);

            /* Check each responder id to have a valid length (min length is 1 byte) and to fit into the responder ID
            list. */
            if (   (extResponderIdLen >= TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_MIN_LEN)
                && ((extResponderIdLen + TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LEN_LEN)
                    <= remainingListLen))
            {
              /* OK! Responder ID has a valid format and fits into the extension. */
              /* Currently no further processing of the ID is done, only skip the ID. */
              uint16 responderIdElementLen = (TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LEN_LEN
                                              + extResponderIdLen);
              remainingListLen     -= responderIdElementLen;
              extResponderIdLenIdx += (TcpIp_TlsBufferRxIterType)(responderIdElementLen);
            }
            else
            {
              /* Format error, responder id is too short or does not fit into the extension */
              innerRetVal = E_NOT_OK;
            }
          }
          else
          {
            /* Format error, responder id minimum length does not fit into the extension */
            innerRetVal = E_NOT_OK;
          }
        }  /* while */

        /* #50 Check the overall result of processing all responder id elements. */
        if ((innerRetVal == E_NOT_OK) || (remainingListLen != 0u))
        {
          /* Error, stop processing the extension */
        }
        else
        {
          /* OK. Processing the list of responder IDs succeeded. */
          totalResponderIdListLen += extResponderIdListLen;
          *TotalResponderIdListLenPtr = totalResponderIdListLen;
          retVal = E_OK;
        }
      }
      else
      {
        /* OK. The responder id list is empty. */
        *TotalResponderIdListLenPtr = totalResponderIdListLen;
        retVal = E_OK;
      }
    }
    else
    {
      /* Format error, responder id list content does not fit into the extension */
    }
  }
  else
  {
    /* Format error, responder id list length field does not fit into the extension */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHello_CheckOcspRequestExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHello_CheckOcspRequestExtensions(
  TcpIp_TlsBufferRxIterType RequestExtensionsStartIdx,
  TcpIp_TlsBufferRxIterType CertStatusRequestEndIdx,
  TCPIP_P2V(uint16) TotalRequestExtensionsLenPtr)
{
  /* Analyze OCSP Request Extensions */

  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* Certificate Status request Extension Format
   *                                                               +-> Request Extensions
   *                                                              /
   *       [ext Type][ext Len][CertStatusType][responder_id_list][request_extensions]
   * Byte: 0       1 2      3 4               5                  m
   *                                                             [ext_len][ext      ]
   *                                                              \        \-> extRequestExtensionsIdx: request extensions
   *                                                               \-> RequestExtensionsStartIdx: request extensions len
   */

  /* #10 Check the request extensions overall length. */
  /* Check that 2 bytes for the request extensions length are available */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(RequestExtensionsStartIdx,
    TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_REQUEST_EXTENSIONS_LEN, CertStatusRequestEndIdx))
  {
    uint16 extRequestExtensionsLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(RequestExtensionsStartIdx), 0u);
    TcpIp_TlsBufferRxIterType extRequestExtensionsIdx = RequestExtensionsStartIdx
      + TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_REQUEST_EXTENSIONS_LEN;

    /* #20 Check that the request extensions content fits into the extension. */
    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extRequestExtensionsIdx,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
      extRequestExtensionsLen, CertStatusRequestEndIdx))
    {
      /* The content of the request extensions fits into the extension. */
      /* #30 Ignore the content of the request extensions, only their length is evaluated. */
      *TotalRequestExtensionsLenPtr = (TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_REQUEST_EXTENSIONS_LEN
                                       + extRequestExtensionsLen);
      retVal = E_OK;
    }
    else
    {
      /* Format error, request extensions content does not fit into the extension */
    }
  }
  else
  {
    /* Format error, request extensions do not fit into the extension */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups
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
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType SupportedGroupsExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extSupportedGroupsLenIdx = SupportedGroupsExtension.StartIdx;
  uint16 overallExtLength = SupportedGroupsExtension.Length;
  TcpIp_TlsBufferRxIterType extSupportedGroupsEndIdx = extSupportedGroupsLenIdx + overallExtLength;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* Supported Group Extension Format
   *
   *
   *                             -> extSupportedGroupsLenIdx
   *                            /                    -> extGroupStartIdx
   *                           /                    /
   *       [ext Type][ext Len][supported Group Len][group 1]            [group n]
   * Byte: 0       1 2      3 4                  5 6      7             (x-1)  x
   *                                                \---consumedExtensionLen---/
   */

  /* Range check before read out the received supported groups length (2Bytes) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extSupportedGroupsLenIdx,
        TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN, extSupportedGroupsEndIdx))
  {
    /* #10 Get the length of the received supported groups list and check against the overall length */
    uint16 receivedSupportedGroupsLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extSupportedGroupsLenIdx), 0u);

    if (overallExtLength == (receivedSupportedGroupsLen + TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN))
    {
      TcpIp_TlsBufferRxIterType extGroupStartIdx
        = extSupportedGroupsLenIdx + TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN;

      /* #20 Check the length of the received supported groups list for plausibility */
      /* RFC 8422 - 5.1.1.  Supported Elliptic Curves Extension */
      if ((receivedSupportedGroupsLen >= 2u) /* List must include at least one group */
        /* and the length information is sent pairwise, so the length must be even */
        && ((receivedSupportedGroupsLen % 2u) == 0u)
        /* Range check (received list length) */
        && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extGroupStartIdx, receivedSupportedGroupsLen, extSupportedGroupsEndIdx)))   /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
      {
        TcpIp_TlsBufferRxIterType extGroupEndIdx = extGroupStartIdx + receivedSupportedGroupsLen;
        TcpIp_TlsBufferRxIterType extGroupIter;
        /* #30 Iterate over all received supported groups and compare it to servers capabilities */
        for (extGroupIter = extGroupStartIdx; extGroupIter < extGroupEndIdx; extGroupIter += 2u)
        {
          /* Get the next received supported group (named curve ID) from the list */
          uint16 receivedNamedCurveId = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extGroupIter), 0u);

          /* #40 Check if the current named curve ID is supported by the TLS-Server */
          /* Compares this entry against the configures TcpIpTlsHandshake worker */
          if (TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported(TlsConIdx,
                receivedNamedCurveId) == E_OK)
          {
            /* #50 Received namedCurveId supported by the TLS-Server - Skip processing of further entries in the list and return E_OK */
            retVal = E_OK;
            break;
          }
        }

        if (retVal != E_OK)
        {
          /* #60 No suitable TcpIpTlsHandshake configured - report error and trigger TLS alert */
          /* RFC8422 - 5.1.  Client Hello Extensions (Actions of the receiver:)
           *   ... this may result in a fatal handshake failure alert due to the lack of common cipher suites. */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE);
        }
      }
      else
      {
        /* #70 received supported group length mismatch - report error and trigger TLS alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* #80 overall received length mismatch - report error and trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionSupportedGroups() */

/**********************************************************************************************************************
 *  TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 NamedCurve)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured cipher worker for this TLS connection */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);

    TcpIp_TlsHandshakeIndIterType handshakeIter;

    /* #20 Iterate over all configured handshake for this cipher worker */
    for (handshakeIter = TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
         handshakeIter < TcpIp_GetTlsHandshakeIndEndIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
         handshakeIter++)
    {
      /* Get the configured elliptic curve ID (named curve ID) */
      TcpIp_TlsHandshakeIterType tlsHandshakeIdx = TcpIp_GetTlsHandshakeInd(handshakeIter);
      TcpIp_TlsEllipticCurveIdType configuredEllipticCurveId = TcpIp_GetEllipticCuveIdOfTlsHandshake(tlsHandshakeIdx);

      /* #30 Check if the configured supported elliptic curve for this handshake worker matches with the given one */
      if (configuredEllipticCurveId == NamedCurve)
      {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: The adjective capable can only be used as "capable of". Rework the comment. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
        /* #40 Configured Handshake reference can support the given named curve ID - Skip all other handshake references */
        retVal = E_OK;
        break;
      }
    } /* Handshake loop */

    /* Previous handshake reference already match - Skip all other cipherWorker */
    if (retVal == E_OK)
    {
      break;
    }

  } /* CipherWorker loop */

  return retVal;
} /* TcpIp_TlsServertMsg_ClientHelloExtIsNamedCurveSupported() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType EcPointFormatExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extEcPointFormatsLenIdx = EcPointFormatExtension.StartIdx;
  uint16 overallExtLength = EcPointFormatExtension.Length;
  TcpIp_TlsBufferRxIterType extEcPointFormatsEndIdx = extEcPointFormatsLenIdx + overallExtLength;

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* EC Point Format Extension Format
   *
   *
   *                             -> extEcPointFormatsLenIdx
   *                            /                               -> extEcPointFormatsStartIdx
   *                           /                               /
   *       [ext Type][ext Len][supported EC point formats len][format 1]          [format n]
   * Byte: 0       1 2      3 4                               5                   x
   *                                                           \---consumedExtensionLen---/
   */

  /* Range check before read out the received EC point formats length (1Bytes) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extEcPointFormatsLenIdx,
    TCPIP_TLS_EXTENSION_EC_POINT_FORMATS_LENGTH_LEN, extEcPointFormatsEndIdx))
  {
    /* #10 Get the length of the received EC point formats list and check against the overall length */
    uint8 receivedEcPointFormatsLen = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(extEcPointFormatsLenIdx), 0u);

    if (overallExtLength == ((uint16)receivedEcPointFormatsLen + TCPIP_TLS_EXTENSION_EC_POINT_FORMATS_LENGTH_LEN))
    {
      TcpIp_TlsBufferRxIterType extEcPointFormatStartIdx
        = extEcPointFormatsLenIdx + TCPIP_TLS_EXTENSION_EC_POINT_FORMATS_LENGTH_LEN;

      /* #20 Check the length of the received EC point formats list for plausibility */
      /* RFC 8422 - 5.1.2.  Supported Point Formats Extension */
      if ((receivedEcPointFormatsLen >= 1u) /* List must include at least one EC point format */
        /* Range check (received list length) */
        && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extEcPointFormatStartIdx, receivedEcPointFormatsLen, extEcPointFormatsEndIdx)))/* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
      {
        TcpIp_TlsBufferRxIterType extEcPointFormatEndIdx = extEcPointFormatStartIdx + receivedEcPointFormatsLen;
        TcpIp_TlsBufferRxIterType extEcPointFormatIter;

        /* #30 Iterate over all received EC point formats and compare them to servers capabilities */
        for (extEcPointFormatIter = extEcPointFormatStartIdx; extEcPointFormatIter < extEcPointFormatEndIdx; extEcPointFormatIter++)
        {
          /* Get the next received EC point format from the list */
          uint8 receivedEcPointFormat = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(extEcPointFormatIter), 0u);

          /* #40 Check if the current EC point format is supported by the TLS server */
          /* "uncompressed" is the only format supported by the server */
          if (receivedEcPointFormat == TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_UNCOMPRESSED)
          {
            /* #50 Received EC point format is supported by the TLS server - Skip processing of further entries in the list and return E_OK */
            retVal = E_OK;
            break;
          }
        }

        if (retVal != E_OK)
        {
          /* #60 No suitable EC point format received - report error and trigger TLS alert */
          /* RFC8422 - 5.1.2.  Supported Point Formats Extension
           *   If the client sends the extension and the extension does not contain
           *   the uncompressed point format, ... , then the server MUST abort the handshake and
           *   return an illegal_parameter alert. */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_ILLEGAL_PARAM);
        }
      }
      else
      {
        /* #70 received EC point formats length mismatch - report error and trigger TLS alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* #80 overall received length mismatch - report error and trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }
  else
  {
    /* The extension it too short to contain the minimum length of 1 byte (for the extension's length field). */
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionEcPointFormats() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms
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
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_TlsStatemachine_STMIF_6080 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType SignatureAlgorithmsExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType extSignatureAlgorithmsLenIdx = SignatureAlgorithmsExtension.StartIdx;
  uint16 overallExtLength = SignatureAlgorithmsExtension.Length;
  TcpIp_TlsBufferRxIterType extSignatureAlgorithmsEndIdx = extSignatureAlgorithmsLenIdx + overallExtLength;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Extension index information */
  /* Signature Algorithms Extension Format
   *
   *
   *                             -> extSignatureAlgorithmsLenIdx
   *                            /                         -> extSignatureAlgorithmStartIdx
   *                           /                         /
   *       [ext Type][ext Len][Signature Algorithms Len][group 1]            [group n]
   * Byte: 0       1 2      3 4                       5 6      7             (x-1)  x
   *                                                     \---consumedExtensionLen---/
   */

  /* Range check before read out the received supported groups length (2Bytes) */
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extSignatureAlgorithmsLenIdx,
        TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN, extSignatureAlgorithmsEndIdx))
  {
    /* #10 Get the length of the received Signature Algorithms list and check against the overall length */
    uint16 receivedSignatureAlgorithmsLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extSignatureAlgorithmsLenIdx), 0u);

    if (overallExtLength == (receivedSignatureAlgorithmsLen + TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_LENGTH_LEN))
    {
      TcpIp_TlsBufferRxIterType extSignatureAlgorithmStartIdx
        = extSignatureAlgorithmsLenIdx + TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_LENGTH_LEN;

      /* #20 Check the length of the received Signature Algorithms list for plausibility */
      /* RFC 5246 - 7.4.1.4.1.  Signature Algorithms */
      if ( /* List must include at least one signature and hash algorithm pair */
           (receivedSignatureAlgorithmsLen >= TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_ALG_ID_LEN)
        /* and the length information is sent pairwise, so the length must be even */
        && ((receivedSignatureAlgorithmsLen % TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_ALG_ID_LEN) == 0u)
        /* Range check (received list length) */
        && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(extSignatureAlgorithmStartIdx, receivedSignatureAlgorithmsLen,  /* PRQA S 2995 1 */ /* MD_TcpIp_Tls_2995 */
            extSignatureAlgorithmsEndIdx)))
      {
        TcpIp_TlsBufferRxIterType extSignatureAlgorithmEndIdx = extSignatureAlgorithmStartIdx + receivedSignatureAlgorithmsLen;
        TcpIp_TlsBufferRxIterType extSignatureAlgorithmIter;

        /* #30 Iterate over all received supported groups and compare it to servers capabilities */
        for (extSignatureAlgorithmIter = extSignatureAlgorithmStartIdx;
             extSignatureAlgorithmIter < extSignatureAlgorithmEndIdx;
             extSignatureAlgorithmIter += TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_ALG_ID_LEN)
        {
          /* Get the next received Signature And Hash Algorithm ID from the list */
          uint16 receivedSignAndHashAlgId = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(extSignatureAlgorithmIter), 0u);
          uint8  receivedSignatureAlgorithm = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(extSignatureAlgorithmIter),
                   TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_SIGNATURE_OFFSET);

          /* #40 Check if the current Signature Algorithm ID is supported by the TLS-Server */
          /* Compares this entry against the configures TcpIpTlsHandshake worker */
          if (TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported(TlsConIdx,
              receivedSignAndHashAlgId) == E_OK)
          {
            /* #50 Received Signature Algorithm Id supported by the TLS-Server - Skip processing of further entries in the list and return E_OK */
            retVal = E_OK;
            /* don't stop but proceed with the further elements */
          }

          /* #60 Check that the received signature algorithm is not 'anonymous' */
          if (receivedSignatureAlgorithm == TCPIP_TLS_SIGNATURE_ALGO_ANONYMOUS)
          {
            /* Error, signature algorithm was received what is not allowed */
            TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
            retVal = E_NOT_OK;  /* reset return value to NOT OK */
            break;  /* stop the for-loop since */
          }
        }

        if (retVal != E_OK)
        {
          /* #70 No suitable TcpIpTlsHandshake configured - report error and trigger TLS alert */
          /* RFC5246 - 7.2.2.  Error Alerts
           * ... sender was unable to negotiate an acceptable set of security parameters given the options available. */
          TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE);
        }
      }
      else
      {
        /* #80 Received Signature Algorithm length mismatch - report error and trigger TLS alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* #90 Overall received length mismatch - report error and trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }

  return retVal;

} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionSignatureAlgorithms() */

/**********************************************************************************************************************
 *  TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 SignAndHashAlgId)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured cipher worker for this TLS connection */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);

    TcpIp_TlsHandshakeIndIterType handshakeIter;

    /* #20 Iterate over all configured handshake for this cipher worker */
    for (handshakeIter = TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
         handshakeIter < TcpIp_GetTlsHandshakeIndEndIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
         handshakeIter++)
    {
      /* Get the configured signature and hash algorithm ID */
      TcpIp_TlsHandshakeIterType tlsHandshakeIdx = TcpIp_GetTlsHandshakeInd(handshakeIter);
      TcpIp_SignatureAlgorithmIdType configuredSignatureAlgorithmId = TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(tlsHandshakeIdx);

      /* #30 Check if the configured supported signature and hash algorithm ID for this handshake worker matches with the given one */
      if ((uint16)configuredSignatureAlgorithmId == SignAndHashAlgId)
      {
        /* #40 Configured Handshake supports the given signature and hash algorithm ID - Skip all other handshake references */
        retVal = E_OK;
        break;
      }
    } /* Handshake loop */

    /* Previous handshake reference already match - Skip all other cipherWorkers */
    if (retVal == E_OK)
    {
      break;
    }

  } /* CipherWorker loop */

  return retVal;
} /* TcpIp_TlsServertMsg_ClientHelloExtIsSignAndHashAlgSupported() */


#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Remove this function since it does not do anything. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsExtensionType RecordSizeLimitExtension)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* RFC8449 Record Size Limit Extension for TLS
  * "record_size_limit" Extension Format:
  *
  *                      +--> (fixed) Extension Length
  *                     /         +--> RlSizeLimit Start Index
  *                    /         /
  *       [ext Type] [ext Len] [RL size limit]
  * Byte: 0        1 2       3 4             5
  *
  * Record Size Limit: Maximum record size that an endpoint is willing to receive (in Bytes).
  *                    Received value effects maximum Tx record size limit
  */
  TcpIp_TlsBufferRxIterType extRecordSizeLimitEndIdx
    = RecordSizeLimitExtension.StartIdx + RecordSizeLimitExtension.Length;

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the received length of the extension with the expected one (2 Byte fixed value) */
  if (RecordSizeLimitExtension.Length == TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_VALUE_LEN)
  {
    /* Check if we received enough byte to read out the value (2 bytes) */
    if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(RecordSizeLimitExtension.StartIdx,                                              /* PRQA S 2995 2 */ /* MD_TcpIp_Tls_2995 */
          TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_FIXED_LEN, extRecordSizeLimitEndIdx))
    {
      /* Get the offered value from the TLS-Client */
      uint16 receivedRecordSizeLimit = IpBase_GetUint16(
        TcpIp_GetAddrTlsBufferRx(RecordSizeLimitExtension.StartIdx), 0u);

      /* #20 Compare the received record size limit with the minimum defined value (64 Bytes) */
      if (receivedRecordSizeLimit >= TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MIN_VALUE)
      {
        /* #30 Compare the received record size limit with the maximum defined value (2^14 Bytes) */
        if (receivedRecordSizeLimit <= TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE)
        {

          /* #40 Extension successfully received - Update Tx information and return E_OK */
          TcpIp_SetTxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx, receivedRecordSizeLimit);

          /* Set Flag which is used to reply to this extension within the ServerHello message */
          TcpIp_SetExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx, TRUE);

          retVal = E_OK;
        }
        else
        {
          /* #50 Client offers more than 2^14 bytes - Set Tx information to maximum supported value */
          /* RFC8449 - 4.  The "record_size_limit" Extension
           *   For TLS 1.2 and earlier, that limit is 2^14 octets.  TLS 1.3 uses a limit of
           *   2 ^ 14 + 1 octets.Higher values are currently reserved for future
           *   versions of the protocol that may allow larger records; an endpoint
           *   MUST NOT send a value higher than the protocol - defined maximum record
           *   size unless explicitly allowed by such a future version or extension.
           *   A server MUST NOT enforce this restriction; a client might advertise
           *   a higher limit that is enabled by an extension or version the server
           *   does not understand.
           */

          /* Set TX limit to maximum supported value (2^14) */
          TcpIp_SetTxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE);

          /* Set Flag which is used to reply to this extension within the ServerHello message */
          TcpIp_SetExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx, TRUE);

          retVal = E_OK;
        }
      }
      else
      {
        /* #60 Lower record size limit value mismatch - trigger TLS alert */
        /* RFC8449 - 4.  The "record_size_limit" Extension
         *    Endpoints MUST NOT send a "record_size_limit" extension with a value
         *    smaller than 64.  An endpoint MUST treat receipt of a smaller value
         *    as a fatal error and generate an "illegal_parameter" alert.
         */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_ILLEGAL_PARAM);
      }
    }
    else
    {
      /* #70 Received record size limit length mismatch - trigger TLS alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }
  else
  {
    /* #80 Received record size limit length mismatch - trigger TLS alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientHelloParseExtensionRecordSizeLimit() */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_MSR_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  TcpIp_TlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmtType clientKeyExchangeStartIdx
    = TcpIp_GetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  TcpIp_TlsEllipticCurveIdType activeCurveId = TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx);
  /* Length of the received Client KeyExchange  message */
  TcpIp_ClientHelloLenOfTlsServerBufferMgmtType clientKeyExchangeLen
    = TcpIp_GetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  /* End index of the received ClientHello message - Need for in range checks inside the parser */
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) clientKeyExchangeEndIdx
    = clientKeyExchangeStartIdx + TCPIP_TLS_HSHDRLEN + clientKeyExchangeLen;

  CONST(uint8, AUTOMATIC) expectedPublicKeyLen =
    ( TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(activeCurveId) + TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(activeCurveId) );

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the received public key with the expected length */
  /* Get the length of the received public key */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Minor: Missing length check. Check presence of 1 byte before reading it. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),
        TCPIP_TLSSERVER_PUPKEYLEN_LEN, clientKeyExchangeEndIdx))
  {
    uint8 receivedClientPublicKeyLen = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u);

    /* Check the length of the received public key */
    if (expectedPublicKeyLen == receivedClientPublicKeyLen)
    {
      /* #20 Received public key length match - Range check */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Don't map receivedClientPublicKeyLen to uint16 but to a generated type. */
/* [REVIEW_c] resolved visbdk: This could lead to MISRA warnings on customer side, if he enables the data size optimization, because then the comparison in the IN_RANGE macro would be wrong  */
/* [REVIEW_c] open visal 16.03.00.0 Improve: I still don't understand why mapping the variable to TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType would cause a problem. Let's have a phone call for that. */
/* [REVIEW_c] resolved visjer: receivedClientPublicKeyLen is now mapped to TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType instead of uint16 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),             /* PRQA S 2995 2 */ /* MD_TcpIp_Tls_2995 */
           ((TcpIp_TlsBufferRxIterType)receivedClientPublicKeyLen + TCPIP_TLSSERVER_PUPKEYLEN_LEN), clientKeyExchangeEndIdx))
      {
        uint8 clientPublicCompFlagLen = TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(activeCurveId);

        if ((receivedClientPublicKeyLen - clientPublicCompFlagLen) == TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(activeCurveId))
        {
          /* #30 set Len indirection only if length is valid  */
          TcpIp_SetTlsBufferRxClientKeyExchangePubKeyLenIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
            TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

          /* Maintain AdHs read index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of Get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
          TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
            TCPIP_TLSSERVER_PUPKEYLEN_LEN);

          /* #40 Check if the public key is compressed and compare the received compression flag with the expected one */
          if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(activeCurveId) == TRUE)
          {
            /* compressed public key format (SECP256) */
            /* Get the compression flag of the received public key */
            uint8 receivedClientCompressionFlag = IpBase_GetUint8(
              TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u);

            /* Maintain AdHs read index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of Get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
            TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
              TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG_LEN);

            /* Only supported compression flag is 0x04 */
            if (receivedClientCompressionFlag == TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG)
            {
              /* #50 Valid (compressed) public key received - Store the index to the start of the public key and return E_OK */
              TcpIp_SetTlsBufferRxClientKeyExchangePubKeyIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
                TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

              /* Maintain AdHs read index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of Get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
              TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
                ((TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType)receivedClientPublicKeyLen - TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG_LEN));

              retVal = E_OK;
            }
          }
          else
          {
            /* else - uncompressed public key format (ED25519) */
            /* #60 Valid (uncompressed) public key received - Store the index to the start of the public key and return E_OK */
            TcpIp_SetTlsBufferRxClientKeyExchangePubKeyIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
              TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

            /* Maintain AdHs read index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of Get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
            TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, receivedClientPublicKeyLen);

            retVal = E_OK;
          }
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
          /* [REVIEW_c] open visal 16.01.00.0 Improve: Enhance comment. received key length does not meet expectations. */
          /* [REVIEW_c] resolved visbdk: Done */
          /* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
        } /* else - Received key length does not meet expectations. E_NOT_OK */
      } /* else - Range check failed. E_NOT_OK */
    } /* else - Length mismatch. E_NOT_OK */
  } /* else - Range check failed. E_NOT_OK */

  if (retVal != E_OK)
  {
    /* Parsing of received public key failed - Report error to user and trigger TLS alert */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_CLIENTKEYEXCHANGE;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTPUBKEYLEN;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ClientKeyExchangeGetClientParams() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetDhSharedSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ClientKeyExchangeCalcSharedSecret() */
#  endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams
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
/*
[REVIEW_G] c_open 16.00.00.x PSK
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmtType clientKeyExchangeStartIdx
    = TcpIp_GetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  /* Length of the received ClientKeyExchange  message */
  TcpIp_ClientHelloLenOfTlsServerBufferMgmtType clientKeyExchangeLen = TcpIp_GetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  /* End index of the received ClientKeyExchange message - Need for in range checks inside the parser */
  CONST(TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType, AUTOMATIC) clientKeyExchangeEndIdx
    = clientKeyExchangeStartIdx + TCPIP_TLS_HSHDRLEN + clientKeyExchangeLen;
  boolean  matchingPskIdentityFound = FALSE;

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */

  /* Get the length of the received PSK identity ... */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Minor: Missing length check. Check presence of 2 bytes before reading them. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),
        TCPIP_TLS_KEYEXCH_PSKIDLEN, clientKeyExchangeEndIdx))
  {
  uint16 clientPskIdentityLen = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
    TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0);

  /* Maintain AdHs read index by incrementing the consumed length */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_KEYEXCH_PSKIDLEN);

  /* #10 Compare the received PSK identity length and check the range */
  if (   (clientPskIdentityLen <= TCPIP_TLS_KEYEXCH_PSKIDMAXLEN)
      && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx),             /* PRQA S 2995, 3415 */ /* MD_TcpIp_Tls_2995, MD_TCPIP_Rule13.5_3415_CslReadOnly */
             clientPskIdentityLen, clientKeyExchangeEndIdx)))
  {
    TcpIp_TlsPskIdentityIndStartIdxOfTlsConnectionType tlsPskIdentityIndStartIdx
      = TcpIp_GetTlsPskIdentityIndStartIdxOfTlsConnection(TlsConIdx);

    TcpIp_TlsPskIdentityIndEndIdxOfTlsConnectionType tlsPskIdentityIndEndIdx
      = TcpIp_GetTlsPskIdentityIndEndIdxOfTlsConnection(TlsConIdx);

    TcpIp_TlsPskIdentityIndIterType tlsPskIdentityIter;

    uint8 receivedClientPskIdentityString[TCPIP_TLS_KEYEXCH_PSKIDMAXLEN];
    VStdMemClr(receivedClientPskIdentityString, TCPIP_TLS_KEYEXCH_PSKIDMAXLEN);                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* #20 Get the received PSK identity string from the TLS RxBuffer */
    VStdMemCpy(receivedClientPskIdentityString, TcpIp_GetAddrTlsBufferRx(                                               /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), clientPskIdentityLen);

    /* Maintain AdHs read index by incrementing the consumed length */
    TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, clientPskIdentityLen);

    /* #30 Iterate over all configured PSK Identities and compare the received PSK Identity with the configured one */
    for (tlsPskIdentityIter = tlsPskIdentityIndStartIdx; tlsPskIdentityIter < tlsPskIdentityIndEndIdx; tlsPskIdentityIter++)
    {
      TcpIp_TlsPskIdentityIndType tlsPskIdentity
        = TcpIp_GetTlsPskIdentityInd(tlsPskIdentityIter);

      TcpIp_PskIdentityLengthOfTlsPskIdentityType pskIdentityLength
        = TcpIp_GetPskIdentityLengthOfTlsPskIdentity(tlsPskIdentity);

      /* If the string length matches to the received PSK Identity length */
      if (clientPskIdentityLen == pskIdentityLength)
      {
        uint8 pskIdentityStringIter;
        TcpIp_PskIdentityPtrType pskIdentityofTlsConPtr
          = TcpIp_GetAddrPskIdentity(TcpIp_GetPskIdentityStartIdxOfTlsPskIdentity(tlsPskIdentity));

        matchingPskIdentityFound = TRUE;

        /* then compare the strings character by character */
        for (pskIdentityStringIter = 0; pskIdentityStringIter < clientPskIdentityLen; pskIdentityStringIter++)
        {
          if (receivedClientPskIdentityString[pskIdentityStringIter] != pskIdentityofTlsConPtr[pskIdentityStringIter])
          {
            matchingPskIdentityFound = FALSE;
            /* If the characters do not match discard the current PSK and continue with the next in list */
            break;
          }
        }
      }

      /* #40 Check if a matching PSK identity found and mark this PSK identity as active for the current TLS connection */
      if (matchingPskIdentityFound == TRUE)
      {
        TcpIp_SetTlsPskIdentityActiveIdxOfTlsConnectionDyn(TlsConIdx, tlsPskIdentity);
        /* Skip further processing of other PSK identities */
        break;
      }
    }

    retVal = E_OK;
  }

  /* #50 Trigger alert in case of no matching PSK Identity */
  if (matchingPskIdentityFound == FALSE)
  {
    TcpIp_TlsAlertLevelType alertLevel;
    TcpIp_TlsAlertDescriptionType alertDescription;

    alertLevel = TCPIP_TLS_ALERT_LEVEL_FATAL;

#   if (TCPIP_SUPPORT_TLSPSKCIPHER_ALERT == STD_ON)
    alertDescription = TCPIP_TLS_ALERT_DESC_UNKNOWN_PSK_IDENTITY;
#   else
    alertDescription = TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR;
#   endif /* (Tcpip_Support_TlsPskCipher_Alert) */

    TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);
  }
  }
  return retVal;
} /* TcpIp_TlsServerMsg_ClientKeyExchangeGetPskParams */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_open 16.00.00.x PSK
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetPskPremasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ClientKeyExchangeCalcPskPremasterSecret */

#  endif /* TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON */
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ClientKeyExchangeCalcMasterSecret() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_SelectMatchingCipher
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_SelectMatchingCipherWorker(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) CipherSuiteLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured cipherWorker and get the configured cipher suite ID */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIndType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);

    /* Get the index of the current CipherDefiniton */
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
      = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(tlsCipherWorkerIdx);

    /* Get the corresponding CipherId (HexCode) */
    TcpIp_CipherSuiteIdOfTlsCipherDefinitionType cipherSuiteId
      = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx);

    /* #20 Iterate over received cipher list from the TLS-Client and compare it to the current configured cipher suite ID */
    if (TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite(
         TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx), CipherSuiteLen, cipherSuiteId) == E_OK)
    {
      /* #30 Found a matching cipher between TLS-Server and TLS-Client - Mark this cipher worker as active and return E_OK */
      TcpIp_SetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx, tlsCipherWorkerIdx);

      /* Set the Index of the Handshake reference which is used on this connection */
      TcpIp_TlsMsg_SelectDefaultHandshakeReference(TlsConIdx);

      retVal = E_OK;

      /* Skip further processing of other cipher worker */
      break;
    } /* else - No matching cipher worker found. E_NOT_OK */
  }

  if (retVal != E_OK)
  {
    /* #40 No matching cipher worker found - Report an error to the user and trigger TLS alert */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO;
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_NOMATCHINGCIPHER;
    UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_INSUF_SEC);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsServerMsg_SelectMatchingCipher() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite(
  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType CipherListStartIdx,
  CONST(uint16, AUTOMATIC) CipherListLen,
  CONST(TcpIp_CipherSuiteIdOfTlsCipherDefinitionType, AUTOMATIC) CipherSuitePattern)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType cipherListStartIdIdx = CipherListStartIdx;
  TcpIp_TlsBufferRxClientHelloIdxOfTlsServerBufferMgmtType cipherListEndIdx = CipherListStartIdx + CipherListLen;

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 iterate over the complete received Client cipher suite list */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use define instead of magic number 2. Also adjust the comment. */
/* [REVIEW_c] resolved visbdk: I think with the comment above the for loop this is clear.  */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* Each cipher suite contains two Byte, so increment by 2 */
  for (; cipherListStartIdIdx < cipherListEndIdx; cipherListStartIdIdx += TCPIP_TLS_CIPHER_SUITE_LEN)
  {
    /* #20 get the cipher suite id from the list */
    uint16 clientCipherSuite = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(cipherListStartIdIdx), 0u);

    /* #30 compare if this cipher suite matches with the server side */
    if (clientCipherSuite == CipherSuitePattern)
    {
      /* #40 matching cipher, break the loop at this point */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsServerMsg_SearchCipherListForMatchingCipherSuite() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_PrepareServerHello
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerHello(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 serverHelloLen;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Store the start index of this message to the current write index - used to add the length information after the data is added */
  TcpIp_SetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 ServerHello message - Add generic TLS handshake header type */
  TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERHELLO);

  /* #20 ServerHello message - Add generic supported protocol version */
  TcpIp_TlsHelloMsg_AddProtocolVersionNr(TlsConIdx);

  /* #30 ServerHello message - Add random structure */
  retVal = TcpIp_TlsHelloMsg_AddRandomStructure(TlsConIdx);

  if (retVal == E_OK)
  {
    /* #40 ServerHello message - Add TLS session ID */
    TcpIp_TlsHelloMsg_AddSessionId(TlsConIdx);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: This section can be combined with the previous one, since the retVal not has changed. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

    /* #50 ServerHello message - Add selected cipher suite */
    retVal = TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher(TlsConIdx);

    /* #60 ServerHello message - Add supported compression method */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Maybe this section also can be combined with the previous session, if the previous function call is reworked to be a void-function. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod(TlsConIdx);

    /* #70 ServerHello message - Add supported extensions */
    TcpIp_TlsServerMsg_ServerHelloAddServerExtensions(TlsConIdx);

    /* #80 ServerHello message - Update the overall length information in the TLS handshake header */
    /* Write the length information into the HS Header: Message length = WriteIdx - ServerHelloStartIdx */
    serverHelloLen = ((uint32)TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)
      - TcpIp_GetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

    TcpIp_SetServerHelloLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx, (uint16)serverHelloLen);

    TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxServerHelloIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      (serverHelloLen - TCPIP_TLS_HSHDRLEN));

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
    /* [REVIEW_c] open visal 16.01.00.2 Improve: This copy function should be moved to the previous if-section, since it should only be called if everything was OK. */
    /* [REVIEW_c] resolved visbdk: Done */
    /* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
  /* #90 in case of enabled Master Secrete Access, copy the generated Session ID to the access buffer */
    TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer(TlsConIdx);
#  endif

  }

  return retVal;
} /* TcpIp_TlsServerMsg_PrepareServerHello() */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_PrepareServerCertificates
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: There are only 3 real function calls, so the standard CSL justification can be used. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx           = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Store the start index of this message to the current write index - used to add the length information after the data is added */
  TcpIp_SetTlsBufferTxServerCertificatesIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 ServerCertificate message - Add generic TLS handshake header type */
  TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_CERTIFICATE);

  /* #20 ServerCertificate message - Add installed Server certificates */
  retVal = TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates(TlsConIdx);

  if (retVal == E_OK)
  {
    /* #30 ServerCertificate message - Update the overall length information in the TLS handshake header */
    uint32 serverCertificateLen = ((uint32)TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)
      - TcpIp_GetTlsBufferTxServerCertificatesIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

    TcpIp_SetServerCertificatesLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx, (uint16)serverCertificateLen);

    TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxServerCertificatesIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
      (serverCertificateLen - TCPIP_TLS_HSHDRLEN));
  }

  return retVal;
} /* TcpIp_TlsServerMsg_PrepareServerCertificates() */
#  endif
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_PrepareServerKeyExchange
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerKeyExchange(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx           = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ServerKeyExchange message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)  != TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_DONE)    /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is trigged (performed in lowPrio task) - leave this context */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
             /* Error during processing of the data - skip further data handling */
         && (retVal == E_OK))                                                                                           /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
  {
    /* Processing of sub states for ServerKeyExchange message */
    switch (TCPIP_TLS_GET_HS_SUB_STATE(TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)))
    {
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE:
      {
        TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod
          = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

        /* Store the start index of this message to the current write index - used to add the length information after the data is added */
        TcpIp_SetTlsBufferTxServerKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
          TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

        /* #20 ServerKeyExchange message - Add generic TLS handshake header type */
        TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE);

        /* Calculate next state, depending on the selected key exchange */
        switch (keyExchangeMethod)
        {
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: ECDH should never be valid here, since ServerKeyExchange is not used for ECDH. */
/* [REVIEW_c] resolved visbdk: Correct, I removed ECDH (also checked the coverage, was never true for ECDH) */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
          {
            /* ECC based key exchange - next state: Add ECC parameter */
            TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
              TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS);
            break;
          }
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
          case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
          {
            /* PSK based key exchange - next state: Add PSK parameter */
            TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
              TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_PSK_PARAMS);
            break;
          }
#  endif
          default:
          {
            /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the
            active cipher suite selected after receiving the client_hello message. */
            break;
          }
        }  /* switch (keyExchangeMethod) */

        break;
      } /* case  TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_HDR */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS:
      {
        /* #30 ServerKeyExchange message - Add ECDH(E) parameter */
        TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams(TlsConIdx);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_PSK_PARAMS:
      {
        /* #40 ServerKeyExchange message - Add PSK parameter */
        retVal = TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams(TlsConIdx);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }
#  endif
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_TRIGGER_TX:
      {
        /* #50 ServerKeyExchange message - Update the overall length information in the TLS handshake header */
        uint32 serverKeyExchangeLen = ((uint32)TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)
          - TcpIp_GetTlsBufferTxServerKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

        TcpIp_SetServerKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx, (uint16)serverKeyExchangeLen);

        TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxServerKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
          (serverKeyExchangeLen - TCPIP_TLS_HSHDRLEN));

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_DONE);
        break;
      }

      default:                                                                                                         /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch () */
  } /* while () */

  return retVal;
} /* TcpIp_TlsServerMsg_PrepareServerKeyExchange() */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ServerKeyExchange ECDHE parameter until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_TRIGGER_TX)/* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is trigged (performed in lowPrio task) - leave this context */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING))
  {

    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS:
      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_ADD_DH:
      {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Maybe rework the comment to make more clear that the ephemeral key shall be added / calculated. */
/* [REVIEW_c] resolved visbdk: Done, changed also comment30 */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
        /* #20 ServerKeyExchange message (ECDHE part) - Add Diffie Hellman parameter and trigger ephemeral key calculation */
        TcpIp_TlsServerMsg_ServerKeyExchangeAddDiffieHellmanParams(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_ADD_SIGNATURE);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }

      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_ADD_SIGNATURE:
      {
        /* #30 ServerKeyExchange message (ECDHE part) - Add Signature parameter and trigger signature calculation */
        TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureParams(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_DECODE_SIGNATURE);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }

      case TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_DECODE_SIGNATURE:
      {
        /* #40 ServerKeyExchange message (ECDHE part) - Encode Signature */
        TcpIp_TlsServerMsg_ServerKeyExchangeEncodeSignature(TlsConIdx);
        /* State TRIGGER_TX means this part of the message is done with processing */
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_TRIGGER_TX);
        break;
      }

      default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch () */
  } /* while () */

} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddEcdheParams() */
#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_open 16.00.00.x PSK
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add PSK identity hint for plain PSK server key exchange */
  retVal = TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint(TlsConIdx);

  /* State TRIGGER_TX means this part of the message is done with processing */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx,
    TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_TRIGGER_TX);

  return retVal;
} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddPskParams() */
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON */
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_PrepareServerHelloDone
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerHelloDone(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Store the start index of this message to the current write index - used to add the length information after the data is added */
  TcpIp_SetTlsBufferTxServerHelloDoneIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 ServerHelloDone message - Add generic TLS handshake header type */
  TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERHELLODONE);

  /* #20 ServerHelloDone message - Update the overall length information in the TLS handshake header */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: serverHelloDoneLen is a constant value, so it could be set directly. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif

  TcpIp_SetServerHelloDoneLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    (TCPIP_TLS_SERVERHELLODONE_LEN + TCPIP_TLS_HSHDRLEN));

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: The length that shall be added here is constant = 1, this can be expressed easier. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxServerHelloDoneIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
    TCPIP_TLS_SERVERHELLODONE_LEN);

} /* TcpIp_TlsServerMsg_PrepareServerHelloDone() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_PrepareServerFinished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_TlsStatemachine_STCAL_6050 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_PrepareServerFinished(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the ServerFinished message until we are done AND no Async context needs to be computed */
  while (   (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx)  != TCPIP_TLS_STATE_SEND_SERVER_FINISHED_DONE)        /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
             /* Async operation is trigged (performed in lowPrio task) - leave this context */
         && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING) )
  {
    switch (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_SEND_SERVER_FINISHED:
      {
        /* Store the start index of this message to the current write index - used to add the length information after the data is added */
        TcpIp_SetTlsBufferTxServerFinishedIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
          TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

        /* #20 ServerFinished message - Add generic TLS handshake header type */
        TcpIp_TlsMsg_AddHsHdr(TlsConIdx, TCPIP_TLS_HSTYPE_FINISHED);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_FINISHED_CALC_HASH);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: The "break" could be omitted since we always go to the next case. Add a comment for that. */
/* [REVIEW_c] rejected visbdk: Correct, but then I have to add an MISRA warning for switch/case fall through */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
        break;
      }

      case TCPIP_TLS_STATE_SEND_SERVER_FINISHED_CALC_HASH:
      {
        /* #30 ServerFinished message - Add the calculated server finished data */
        TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData(TlsConIdx);
        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_FINISHED_TRIGGER_TX);
        /* This operation is processed within the lowPrio function, which means that we are leaving
           this context and return when the operation is DONE */
        break;
      }

      case TCPIP_TLS_STATE_SEND_SERVER_FINISHED_TRIGGER_TX:
      {
        /* #40 ServerFinished message - Update the overall length information in the TLS handshake header */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: serverFinishedLen is constant (=4+12) and could be set without reading these two indices. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use the generated type TcpIp_ServerFinishedLenOfTlsServerBufferMgmtType instead of uint16. */
/* [REVIEW_c] resolved visbdk: Done, because define is used now */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
        TcpIp_SetServerFinishedLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx, TCPIP_TLS_FINISHED_MESSAGE_LEN);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use define for the FINISHED length instead of calculating it. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#  endif
        TcpIp_TlsMsg_AddLenToHsHdr(TcpIp_GetTlsBufferTxServerFinishedIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx),
          TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

        TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_SEND_SERVER_FINISHED_DONE);
        break;
      }

      default:                                                                                                          /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
      {
        /* Default case left blank intentionally */
        TCPIP_ASSERT_UNREACHABLE();
        break;
      }

    } /* switch () */
  } /* while ( ) */

} /* TcpIp_TlsServerMsg_PrepareServerFinished() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: I'm wondering if we really have to check the existence of a cipher suite here. Didn't we already do that when analyzing the received ClientHello? */
/* [REVIEW_c] resolved visbdk: Correct, this could not happen - I will not remove the check since "defensive" programming */
/* [REVIEW_c] open visal 16.03.00.0 Improve: Defensive programming is ok, but this check is duplicated. When making the component SAFE this will cause problems. */
/* [REVIEW_c] resolved visbdk: Correct, but if I remove the check, we will also have to ensure (at safe) that the index is valid. So either, write an TCASE (when the if condition is there) or make an more complex analysis. I will let the check an we add (at safe) an unit test).  */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  /* #10 Check if we found a matching cipher suite */
  /* Selection is performed during parsing of ClientHello message */
  if(activeTlsCipherWorkerIdx != TCPIP_NO_TLSCIPHERWORKERACTIVEIDXOFTLSCONNECTIONDYN)
  {
    /* Get the index of the current CipherDefiniton */
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
      = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);

    /* Get the corresponding Cipher Id (HexCode) */
    TcpIp_CipherSuiteIdOfTlsCipherDefinitionType cipherSuiteId
      = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx);

    /* #20 Write the selected cipher suite to the TLS TxBuffer for transmitting */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0, cipherSuiteId);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is updated but the write index. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    /* Maintain AdHs write index by incrementing the consumed length */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_CIPHERSUITESLEN_LEN);

    retVal = E_OK;
  }
  else
  {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Probably this path is obsolete (see previous finding). Otherwise setting an alert would be good. */
/* [REVIEW_c] resolved visbdk: correct, removed this error reporting since we never reach this point */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
    /* This could never happen due to previous checks - left blank intentionally */
  }

  return retVal;
} /* TcpIp_TlsServerMsg_ServerHelloAddSelectedCipher() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the supported compression method to the TLS TxBuffer for transmitting */
  /* Only the compression method NONE is supported by this implementation */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)),
    0u, TCPIP_TLS_COMPRESSION_METHOD_NONE);

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is updated but the write index. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  /* Maintain AdHs write index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_COMPMETH_LEN);

} /* TcpIp_TlsServerMsg_ServerHelloAddCompressionMethod() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerHelloAddServerExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloAddServerExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Implement this function, or state that no extension shall be sent, and eventually make it a void-function. */
/* [REVIEW_c] resolved visbdk: Obsolete, this API does now contain functionality. Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Store the extension length field write index for later usage */
  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType extensionLenStartIdx
    = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  uint16 extTotalLen;


  /* RFC5246 7.4.1.4.  Hello Extensions Format
   *
   *                      +--> overall (consumed) Extensions Length (extTotalLen)
   *                     /       +--> Extension Start Index
   *                    /       /
   *       [extensions length] [extension Type 1] [extension Data 1] [extension Type 2] [extension Data 2]  ...
   * Byte: 0                 1 2                3 4                                                           /
   *                           \-------------------------(extTotalLen)---------------------------------------/
   *
   * extensions length - Overall length of all added extension list.
   * extension type - identifies the particular extension type.
   * extension data - contains information specific to the particular extension type.
   */

  /* ----- Implementation ----------------------------------------------- */
  /* Skipp the write index for the extension length field (2 Byte), filled out later */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN);

  /* #10 Add record_size_limit(28) Extension - RFC8449 */
  TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit(TlsConIdx);

  /* #20 Calculate and set overall extension length */
  extTotalLen = (uint16)(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) - extensionLenStartIdx
    - TCPIP_TLS_EXTENSION_LENGTH_LEN);

  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extensionLenStartIdx), 0, extTotalLen);

} /* TcpIp_TlsServerMsg_ServerHelloAddServerExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
  */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

 /* RFC8449 Record Size Limit Extension for TLS
  * "record_size_limit" Extension Format:
  *
  *                      +--> (fixed) Extension Length
  *                     /         +--> RlSizeLimit Start Index
  *                    /         /
  *       [ext Type] [ext Len] [RL size limit]
  * Byte: 0        1 2       3 4             5
  *
  * Record Size Limit: Maximum record size that an endpoint is willing to receive (in Bytes)
  *                    Configuration parameter: TcpIpTlsMaxFragmentLength
  */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the extension is enabled for this TLS connection */
  if (TcpIp_IsTlsUseExtensionRecordSizeLimitOfTlsConnection(TlsConIdx) == TRUE)
  {
    /* #20 Check if the extension is received from the TLS-Client in the ClientHello message */
    if (TcpIp_IsExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx) == TRUE)
    {
      TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

      TcpIp_RxRecordSizeLimitOfTlsConnectionDynType availableRxBufferSize
        = TcpIp_GetRxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx);

      TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType extTypeStartIdx
        = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

      TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType extLenIdx
        = extTypeStartIdx + TCPIP_TLS_EXTENSION_TYPE_LEN;

      TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType rlSizeLimitStartIdx
        = extLenIdx + TCPIP_TLS_EXTENSION_LENGTH_LEN;

      /* #30 Extension enabled for this TLS connection - Write configured information into ServerHello message */
      /* Set the extension type to TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT (0x001C) */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extTypeStartIdx), 0, TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT);
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_TYPE_LEN);

      /* Set the fixed extension length (2 byte) */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(extLenIdx), 0, TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_FIXED_LEN);
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_LENGTH_LEN);

      /* Set the configured record size limit value */
      IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(rlSizeLimitStartIdx), 0, availableRxBufferSize);
      TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_VALUE_LEN);

    } /* else- Extension is not received from the TLS-Client. Do nothing */
  } /* else - Extension is not enabled. Do nothing. */
} /* TcpIp_TlsServerMsg_ServerHelloExtAddRecordSizeLimit() */
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates(
  TcpIp_TlsConnectionIterType TlsConIdx)
{

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType certificateLengthIdx;
  uint32 totalCertsLen  = 0;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Store the current write index, which is the index where the complete certificate
     length should be placed after adding the certificates */
  certificateLengthIdx = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is updated but the write index. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* Maintain AdHs write index by incrementing the consumed length */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_CERTLEN_LEN);

  /* #10 Iterate over all configured server certificates in the chain and add the installed certificates into the TLS TxBuffer for transmitting */
  retVal = TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain(TlsConIdx, &totalCertsLen);

  /* #20 Write the total length of all added server certificates */
  IpBase_PutUint24(TcpIp_GetAddrTlsBufferTx(certificateLengthIdx), 0, totalCertsLen);

  return retVal;
} /* TcpIp_TlsServerMsg_ServerCertificateAddServerCertificates() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6080 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsLocalKeyMCertInfoIterType tlsLocalKeyMCertInfo;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured local certificates to find the first available server (leaf) certificate. */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: How is it selected what kind of certificates will be loaded? Will this loop find only certs of the correct / desired type? */
/* [REVIEW_c] comment visal: Only the (first) configured certificate of the connection will be used. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  for (tlsLocalKeyMCertInfo = TcpIp_GetTlsLocalKeyMCertInfoStartIdxOfTlsConnection(TlsConIdx);
       tlsLocalKeyMCertInfo < TcpIp_GetTlsLocalKeyMCertInfoEndIdxOfTlsConnection(TlsConIdx);
       tlsLocalKeyMCertInfo++)
  {
    KeyM_CertificateStatusType certStatus;
    TcpIp_CertificateIdType nextCertId = TcpIp_GetLeafCertIdOfTlsLocalKeyMCertInfo(tlsLocalKeyMCertInfo);
    boolean stopAddingCerts = FALSE;  /* Stop adding further certs to the cert chain, don't even add the current one. */

    /* #20 Check if the server certificate is available. */
    if ((KeyM_CertGetStatus(nextCertId, &certStatus) == E_OK) && (certStatus != KEYM_CERTIFICATE_NOT_AVAILABLE))
    {
      retVal = E_OK;

      /* #30 Load all available certificates into the chain (starting with the leaf cert). Including the root cert depends on the configuration. */
      while ((retVal == E_OK) && (stopAddingCerts == FALSE))
      {
        /* Add the current cert to the chain if applicable */
        retVal = TcpIp_TlsServerMsg_AddServerCertificatesAddLoadableCert(
          TlsConIdx, &nextCertId, CopiedLenPtr, &stopAddingCerts);
      }  /* while-loop */

      /* #40 All certificates loaded, break the for-loop */
      break;
    }
    else
    {
      /* KeyM_CertGetStatus() failed (which never occurs when using correct input parameters),
         or the certificate is configured but no content is available (e.g. no cert is loaded). */
    }
  }

  return retVal;
} /* TcpIp_TlsServerMsg_AddServerCertificatesAddCertChain */


/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_AddServerCertificatesAddLoadableCert
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddLoadableCert(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_CertificateIdType) NextCertIdPtr,
  TCPIP_P2V(uint32) CopiedLenPtr,
  TCPIP_P2V(boolean) StopAddingCertsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_CertificateIdType currCertId;
  boolean addLastCert = FALSE;
  boolean stopAddingCerts = FALSE;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  currCertId = *NextCertIdPtr;
  *NextCertIdPtr = TCPIP_CERTID_INV;  /* Reset id of the next cert */

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
  /* [REVIEW_c] open visal 16.01.00.2 Question: What happens if we have a cert chain installed without a matching root (we don't need a root)? Is then the last cert skipped? */
  /* [REVIEW_c] resolved visal: Code reworked. Only root certs are skipped. */
  /* [REVIEW_c] accepted visal, visbdk 16.03.00.0 Statement: Implemented in TCPIP-5967. OK. */
#   endif

  /* #10 Check if an issuing certificate is available or if the current certificate is a self-signed certificate. */
  if (KeyM_GetIssuerCertId(currCertId, NextCertIdPtr) != E_OK)
  {
    /* No issuing certificate is available. Stop adding further certificates to the cert chain. */

    addLastCert = TRUE;  /* This is the last cert that can be added to the cert chain. */
  }
  else
  {
    /* The issuing cert is available. */

    /* #20 Check if the current certificate is a self-signed certificate. */
    if (currCertId == *NextCertIdPtr)
    {
      /* The current cert is a self-signed root cert. */

      /* Check if the root cert shall be added to the cert chain */
      if (TcpIp_IsIncludeRootCertificateOfTlsConnection(TlsConIdx) == FALSE)
      {
        /* Root certs shall not be added to the cert chain, so stop adding certs now. The current cert is not added to the cert chain. */
        stopAddingCerts = TRUE;
      }
      else
      {
        /* The current cert (root cert) shall be added to the cert chain */
        addLastCert = TRUE;  /* This is the last cert we can add to the cert chain. */
      }
    }
  }

  /* #30 Add the current certificate if it is allowed. */
  if (stopAddingCerts == FALSE)
  {
    /* Add the current certificate */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
    /* [REVIEW_c] open visal 16.01.00.2 Improve: Processing is not stopped when retVal is not OK. */
    /* [REVIEW_c] resolved visal: Done */
    /* [REVIEW_c] accepted visal, visbdk 16.03.00.0 Statement: Implemented in TCPIP-5967. OK. */
#   endif
    if (TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert(TlsConIdx, CopiedLenPtr, currCertId) != E_OK)
    {
      /* Error, the current cert could not be added to the cert chain for some reason. Cancel the processing here. */
      stopAddingCerts = TRUE;
      retVal = E_NOT_OK;

      /* Set alert INTERNAL_ERROR (a user error is already reported in TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert). */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_INT_ERROR);
    }
  }

  /* #40 Stop adding further certs if the current cert was the last one to add. */
  if (addLastCert == TRUE)
  {
    /* Our last cert was added, now stop this process. */
    stopAddingCerts = TRUE;
  }

  *StopAddingCertsPtr = stopAddingCerts;
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) CopiedLenPtr,
  CONST(TcpIp_CertificateIdType, AUTOMATIC) CertId)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType certLenIdx;
  TcpIp_CertDataType  serverCert;

  uint32 availableSpaceInTxBuf = ((uint32)TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufMgmtIdx) -
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  Std_ReturnType  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Store the write index where the certificate length should be placed */
  certLenIdx = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  /* Maintain AdHs read write by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_CERTLEN_LEN);

  /* Prepare the internal struct for the KeyM call */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Minor: availableSpaceInTxBuf includes the 3 bytes length field, this must be subtracted. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
  serverCert.certDataLength = availableSpaceInTxBuf - TCPIP_TLSSERVER_CERTLEN_LEN;
  serverCert.certData = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 Retrieve the current certificate from the KeyM and store it into the TLS TxBuffer for transmitting. */
  if (KeyM_GetCertificate(CertId, ( KeyM_CertDataType *)&serverCert) == E_OK)                                           /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_TcpIp_CertDataType */
  {
    /* #20 Certificate successfully retrieved from KeyM - Update length information and return E_OK. */
    /* Increment the total length by the certificate length and by the length of the CertLenfield (3Byte) */
    *CopiedLenPtr += (serverCert.certDataLength + TCPIP_TLSSERVER_CERTLEN_LEN);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: This can be combined with the previous +=. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif

    /* Write the length of this certificates at the saved index */
    IpBase_PutUint24(TcpIp_GetAddrTlsBufferTx(certLenIdx), 0u, serverCert.certDataLength);

    /* Maintain AdHs write index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Use CSL add macro instead of get and set. Maybe all occurrences of "Maintain" should be checked. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, (uint16)serverCert.certDataLength);

    retVal = E_OK;
  }
  else
  {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Rework comment, it is not really understandable. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
    /* #30 Certificate could not be retrieved from KeyM - Report user error and return E_NOT_OK. */
    TcpIp_TlsUserErrorType  userError;
    userError.UserErrorId = TCPIP_TLS_ERRORID_KEYM_GETCERTIFICATE_FAILED;
    userError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);
    userError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_SERVERCERT_MSG;

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsServerMsg_AddServerCertificatesAddSingleCert() */


/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeAddDhStructure
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
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddDiffieHellmanParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
   TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
     = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
     TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

   uint8 publicKeyLen;
   uint8 publicKeyCompressionLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Store the current write index for Key Exchange parameter (needed for signature generation) */
  TcpIp_SetTlsBufferTxServerKeyExchangeParamsIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* #10 Write the Curve type (named curve) into the TLS TxBuffer for transmitting */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u, TCPIP_TLS_CURVETYPE_NAMED_CURVE);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  /* Maintain AdHs write index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Use CSL add macro instead of get and set, for all following updates of the write idx. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_CURVETYPE_LEN);

  /* #20 Write the configured named curve ID into the TLS TxBuffer for transmitting */
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u,
      TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx));

  /* Maintain AdHs write index by incrementing the consumed length */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_CUVEID_LEN);

  /* Get the length of the Public key, depended on the current selected curve */
  publicKeyLen = TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx));

  /* Get the length of the optional compression flag. If no compression is used, publicKeyCompressionLen is 0u */
  publicKeyCompressionLen = TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx));

  /* #30 Write the Length of the generated public key into the TLS TxBuffer for transmitting */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u, (publicKeyLen + publicKeyCompressionLen));

  /* Maintain AdHs write index by incrementing the consumed length */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_PUPKEYLEN_LEN);

  /* #40 Write the compression flag of the public key if the curve uses one into the TLS TxBuffer for transmitting */
  if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
    TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
  {
    /* Curve uses compression flag - Generated public key only contains the raw data.
       Write the compression flag of public key (04) in front of the key */
    IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0u, TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG);

    /* Maintain AdHs write index by incrementing the consumed length */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_PUPKEY_COMPRESSION_FLAG_LEN);
  }

  /* #50 Write the generated DH public key into the TLS TxBuffer for transmitting */
  TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey(TlsConIdx);

} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddDhStructure() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureStructure
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureParams(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* The previous async crypto operation is done, so reset the flag */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Write the configured named curve ID into the TLS TxBuffer for transmitting */
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx)), 0,
      (uint16)TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(activeTlsHandshakeIdx));

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  /* Maintain AdHs write index by incrementing the consumed length */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Use CSL add macro instead of get and set, for all following updates of the write idx. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_SIGNATUREALGO_ID_LEN);

  /* Save the current write index to mark the position where the signature length should be placed. */
  /* The actual length is calculated and set inside the async context */
  TcpIp_SetTlsBufferTxServerKeyExchangeSignatureLenIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  /* Maintain AdHs write index by incrementing the consumed length */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLSSERVER_SIGNATURELEN_LEN);

  /* #20 Write the generated signature into the TLS TxBuffer for transmitting */
  TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature(TlsConIdx);
} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddSignatureStructure() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeDecodeSignature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeEncodeSignature(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsHandshakeActiveIdxOfTlsCipherWorkerDynType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  uint8 consumedLen = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* The previous async crypto operation is done, so reset the flag */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* #10 Forward the encoding of the generated signature to the curve specific encoder function */
  switch (TcpIp_GetSignatureAlgorithmIdOfTlsHandshake(activeTlsHandshakeIdx))
  {
    case TCPIP_SIG_ALGO_ID_ECDSA_SECP256R1_SHA256:
    {
      /* Encoding for SECP256R1 based signatures */
      TcpIp_TlsServerMsg_EncodeSecp256r1Signature(TlsConIdx, &consumedLen);
      break;
    }

    case TCPIP_SIG_ALGO_ID_ECDSA_ED25519_INTRINSIC:
    {
      /* Encoding for ED25519 based signatures */
      TcpIp_TlsServerMsg_EncodeEd25519Signature(TlsConIdx, &consumedLen);
      break;
    }

    default:                                                                                                            /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
    {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Add comment that this default case is never reached because a valid / supported algorithm was already chosen before. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
      /* Not (yet) supported algorithms:
      - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA256
      - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA384
      - TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA512
      - TCPIP_SIG_ALGO_ID_ECDSA_SECP384R1_SHA384
      - TCPIP_SIG_ALGO_ID_ECDSA_SECP521R1_SHA512
      - TCPIP_SIG_ALGO_ID_ECDSA_ED448_INTRINSIC
      - ...
      */

      /* Default case is never reached because a valid / supported algorithm was already chosen before  - left blank intentionally */
      TCPIP_ASSERT_UNREACHABLE();
      break;
    }

  } /* switch */

  /* #20 Update the length of the encoded signature */
  IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(
    TcpIp_GetTlsBufferTxServerKeyExchangeSignatureLenIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx)), 0u, consumedLen);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* Maintain AdHs write index by incrementing the consumed length */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, consumedLen );

} /* TcpIp_TlsServerMsg_ServerKeyExchangeDecodeSignature() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_EncodeSecp256r1Signature
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
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_EncodeSecp256r1Signature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) ConsumedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */


  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Rename variables. _NumLeadingZeros would be better understandable. And a description: Number of leading zeros that have to be removed for the BER encoding. */
/* [REVIEW_c] resolved visbdk: Done. Note, this function will be completely reworked within the mentioned tasks */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* Number of leading zeros that have to be removed for the BER encoding */
  uint8 r_NumLeadingZeros;
  uint8 s_NumLeadingZeros;
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Naming is confusing. You can not append data in front of something, this is prepending. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  boolean r_PrependLeadingZero;
  boolean s_PrependLeadingZero;

  TCPIP_P2C(uint8) r_Ptr = TcpIp_GetAddrTlsTemporarySignatureBuffer(
    TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx));

  TCPIP_P2C(uint8) s_Ptr = TcpIp_GetAddrTlsTemporarySignatureBuffer(
    TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx) + TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN);

  TCPIP_P2V(uint8) r_TypePtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 2u);
  TCPIP_P2V(uint8) r_LenPtr  = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 3u);
  TCPIP_P2V(uint8) r_DestPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 4u);
  TCPIP_P2V(uint8) s_TypePtr;
  TCPIP_P2V(uint8) s_LenPtr;
  TCPIP_P2V(uint8) s_DestPtr;
  TCPIP_P2V(uint8) Asn1Sig_TypePtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) );
  TCPIP_P2V(uint8) Ans1Sig_LenPtr  = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 1u);

  uint8 r_Asn1Len;
  uint8 s_Asn1Len;
  uint8 Asn1Sig_Len;

  /* ----- Implementation ----------------------------------------------- */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Add some sentences describing what shall be done in this function. Format generated by lib, manual BER encoding, ... Rework all comments to be better understandable. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* #10 Process r value of SECP256 based signature */
  /* Write ASN1 type of r value */
  IpBase_PutUint8(r_TypePtr, 0, TCPIP_TLS_ASN1TAG_INTEGER_ID);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Add comment like: Analyze the position of the first significant bit. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
  /* #20 Analyze the position of the first significant bit of the r value and check if a leading zero must be added */
  TcpIp_TlsServer_AnalyzeSecp256KeyComponente(r_Ptr,
    TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN, &r_NumLeadingZeros, &r_PrependLeadingZero);

  r_Asn1Len = TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN - r_NumLeadingZeros;

  if (r_PrependLeadingZero == TRUE)
  {
    /* #30 Add leading zero to r value of encoded SECP256 based signature and copy the actual r value */
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Maybe we can use &r_DestPtr[0] as we do in the else-path. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
    /* Write leading zero */
    IpBase_PutUint8(&r_DestPtr[0], 0u, 0x00u);

    /* Copy r value behind leading zero */
    VStdMemCpy(&r_DestPtr[1], &r_Ptr[r_NumLeadingZeros], r_Asn1Len);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Due to the leading zero, key size is increased by one byte */
    r_Asn1Len += 1u;
  }
  else
  {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Question: Does MemCpy accept length 0? This could be if the key is (probably defective) all zero. */
/* [REVIEW_c] resolved visbdk: I've added this question to the mentioned task. We can add an additional ceedling tcase for this. */
/* [REVIEW_c] open visal 16.03.00.0 Question: Which mentioned task? */
/* [REVIEW_c] stored visal: Will be handled in TCPIP-4495. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
    /* #40 No leading zero must be added, directly copy the r value of the SECP256 based key */
    VStdMemCpy(&r_DestPtr[0], &r_Ptr[r_NumLeadingZeros], r_Asn1Len);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

  /* #50 Write the overall length of the r value */
  IpBase_PutUint8(r_LenPtr, 0u, r_Asn1Len);

  /* #60 Process s value of SECP256 based signature */
  /* Calculate the Destination of s */
  s_TypePtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 4u + r_Asn1Len );
  s_LenPtr  = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 4u + r_Asn1Len + 1u );
  s_DestPtr = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx) + 4u + r_Asn1Len + 1u + 1u );

  /* Write ASN1 type of s value */
  IpBase_PutUint8(s_TypePtr, 0, TCPIP_TLS_ASN1TAG_INTEGER_ID);

  /* #70 Analyze the position of the first significant bit of the s value and check if a leading zero must be added */
  TcpIp_TlsServer_AnalyzeSecp256KeyComponente(s_Ptr,
    TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN, &s_NumLeadingZeros, &s_PrependLeadingZero);

  s_Asn1Len = TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN - s_NumLeadingZeros;
  if (s_PrependLeadingZero == TRUE)
  {
    /* #80 Add leading zero to s value of encoded SECP256 based signature and copy the actual s value */
    /* Write leading zero */
    IpBase_PutUint8(s_DestPtr, 0u, 0x00u);

    /* Copy s value behind leading zero */
    VStdMemCpy(&s_DestPtr[1], &s_Ptr[s_NumLeadingZeros], s_Asn1Len);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Due to the leading zero, key size is increased by one byte */
    s_Asn1Len += 1u;
  }
  else
  {
    /* #90 No leading zero must be added, directly copy the s value of the SECP256 based key */
    VStdMemCpy(&s_DestPtr[0], &s_Ptr[s_NumLeadingZeros], s_Asn1Len);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

  /* #100 Write the overall length of the s value */
  IpBase_PutUint8(s_LenPtr, 0, s_Asn1Len);

  /* #110 Update general signature ASN1 tags and complete length of encoded signature */
  /* Write Type of ASN1 signature */
  IpBase_PutUint8(Asn1Sig_TypePtr, 0, TCPIP_TLS_ASN1TAG_SEQUENCE_ID);

  /* Write signature length */
  Asn1Sig_Len = r_Asn1Len + s_Asn1Len + 4u; /* 4 = r_type, r_len, s_type, s_len */
  IpBase_PutUint8(Ans1Sig_LenPtr, 0, Asn1Sig_Len);

  *ConsumedLenPtr = Asn1Sig_Len + 2u;

} /* TcpIp_TlsServerMsg_EncodeSecp256r1Signature() */

/**********************************************************************************************************************
 *  TcpIp_TlsServer_AnalyzeSecp256KeyComponente
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.02.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Function name could be: AnalyzeSecpKeyComponente. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServer_AnalyzeSecp256KeyComponente(
  TCPIP_P2C(uint8) KeyPtr,
  CONST(uint8, AUTOMATIC) KeyLen,
  TCPIP_P2V(uint8) NrLeadingZeroPtr,
  TCPIP_P2V(boolean) PrepandLeadingZero)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least keyIter;

  /* ----- Implementation ----------------------------------------------- */
  *NrLeadingZeroPtr   = 0u;
  *PrepandLeadingZero = FALSE;

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: This CDD is no design but a very detailed implementation instruction. Reduce the complexity of the CDD. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
  /* #10 Iterate over the complete key and count the number of leading zeros which must be prepended */
  for (keyIter = 0u; keyIter < KeyLen; keyIter++)
  {
    /* Check if the current Byte is not zero */
    if (KeyPtr[keyIter] != 0x00u)
    {
      /* Check if the current Byte is greater than 127 (0x7F) */
      if (KeyPtr[keyIter] > 0x7Fu)
      {
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not append, but prepend. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
        /* Inform the caller that he has to prepend a leading zero */
        *PrepandLeadingZero = TRUE;
      }
      /* Skip the processing */
      break;
    }
    /* Increment the number of leading zeros */
    (*NrLeadingZeroPtr)++;
  }
} /* TcpIp_TlsServer_AnalyzeSecp256KeyComponente() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_EncodeEd25519Signature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_EncodeEd25519Signature(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) ConsumedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TCPIP_P2V(uint8) signatureDestPtr
    = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

  TCPIP_P2C(uint8) signatureSrcPtr
    = TcpIp_GetAddrTlsTemporarySignatureBuffer(TcpIp_GetTlsTemporarySignatureBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 ED25519 based signatures are not ASN1 encoded - copy the generated signature into the TLS TxBuffer for transmitting */
  VStdMemCpy(signatureDestPtr, signatureSrcPtr, TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN);                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* Update the consumed length information */
  *ConsumedLenPtr += TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN;

} /* TcpIp_TlsServerMsg_EncodeEd25519Signature() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_GetLenOfPubKeyCompression
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(uint8, TCPIP_CODE) TcpIp_TlsServerMsg_GetLenOfPubKeyCompression(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 lenRetVal = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the length of the curve specific public key compression flag */
  /* Will return length 0 in case of no compression flag */
  switch (CurveId)
  {
    case TCPIP_CURVE_ID_SECP521R1:
    case TCPIP_CURVE_ID_SECP384R1:
    case TCPIP_CURVE_ID_SECP256R1:
    {
      /* SECP based curved - Compression flag used */
      lenRetVal = TCPIP_TLSSERVER_PUPKEY_COMPRESSION_LEN;
      break;
    } /* case TCPIP_CURVE_ID_SECP521R1 | TCPIP_CURVE_ID_SECP384R1 | TCPIP_CURVE_ID_SECP256R1 */

    case TCPIP_CURVE_ID_X448:
    case TCPIP_CURVE_ID_X25519:
    {
      /* ED based curve - No compression flag used */
      lenRetVal = TCPIP_TLSSERVER_PUBKEY_NO_COMPRESSION_LEN;
      break;
    } /* case TCPIP_CURVE_ID_X25519 | TCPIP_CURVE_ID_X448 */

    default:                                                                                                            /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */ /* COV_TCPIP_MISRA */
    {
      /* Default case left blank intentionally */
      TCPIP_ASSERT_UNREACHABLE();
      break;
    }

  } /* switch */

  return lenRetVal;
} /* TcpIp_TlsServerMsg_GetLenOfPubKeyCompression() */

/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetDhPubKeyAsyncFlagOfTlsConnectionDyn(TlsConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddDhPubKey() */


/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerConnectionIterType tlsServerConIdx = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetHsSignGenAsyncFlagOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ServerKeyExchangeAddSignature() */

#  endif
#  if (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
[REVIEW_G] c_open 16.00.00.x PSK
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_SizeOfTlsBufferTxType tlsBufferTxAdHsWriteIdx
    = TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx);

  TcpIp_TlsPskIdentityDefaultIdxOfTlsConnectionType defaultTlsPskIdentityIdx
    = TcpIp_GetTlsPskIdentityDefaultIdxOfTlsConnection(TlsConIdx);

  TcpIp_PskIdentityHintLengthOfTlsPskIdentityType tlsPskIdentityHintLen
    = TcpIp_GetPskIdentityHintLengthOfTlsPskIdentity(defaultTlsPskIdentityIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the PSK identity hint against the maximum supported hint length */
  if (tlsPskIdentityHintLen < TCPIP_TLS_KEYEXCH_PSKIDHINTMAXLEN)
  {
    /* #20 PSK identity hint length match - add the PSK hint to the TLS TxBuffer for transmitting */
    TcpIp_SizeOfPskIdentityHintType defaultPskIdentityHintStartIdx
      = TcpIp_GetPskIdentityHintStartIdxOfTlsPskIdentity(defaultTlsPskIdentityIdx);

    /* Write the Length of the PSK Identity Hint length */
    IpBase_PutUint16(TcpIp_GetAddrTlsBufferTx(tlsBufferTxAdHsWriteIdx), 0, tlsPskIdentityHintLen);

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
    /* Maintain AdHs write index by incrementing the consumed length */
    TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
      tlsBufferTxAdHsWriteIdx + TCPIP_TLS_KEYEXCH_PSKIDHINTLEN);

    /* #30 Write the PSK Identity Hint string */
    VStdMemCpy(TcpIp_GetAddrTlsBufferTx(tlsBufferTxAdHsWriteIdx),                                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      TcpIp_GetAddrPskIdentityHint(defaultPskIdentityHintStartIdx), tlsPskIdentityHintLen);

    /* Maintain AdHs read index by incrementing the consumed length */
    TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx,
      tlsBufferTxAdHsWriteIdx + tlsPskIdentityHintLen);

    retVal = E_OK;
  }
  else
  {
    /* #40 else - PSK hint length mismatch - return E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
}/* TcpIp_TlsServerMsg_ServerKeyExchangeAddPskIdentityHint() */
#  endif
/**********************************************************************************************************************
 *  TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
 /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsServerConnectionIterType tlsServerConIdx
    = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* Store the position of the verify data (will be set inside the async context function) */
  TcpIp_SetTlsBufferTxServerFinishedVerifyDataIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx,
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx));

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.2 Improve: Not the read index is maintained but the write index. Fix in all following occurrences. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  /* Maintain AdHs write index by incrementing the consumed length */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Use CSL add macro instead of get and set. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufMgmtIdx, TCPIP_TLS_FINISHED_VERIFYDATA_LEN);

  /* #10 Handles synchronous CSM call and trigger the calculation of the job in the async context handler */
  TcpIp_SetCalcServerFinishedHashAsyncFlagOfTlsServerConnection(tlsServerConIdx, TRUE);

  /* Set the TLS connection state to ASYNC_PENDING */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_ASYNC_PENDING);

} /* TcpIp_TlsServerMsg_ServerFinishedAddServerFinishedData() */

#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  MSA - Master Secret Access
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  uint8 sessionIdLen
    = TcpIp_GetServerHelloSessionIdLenOfTlsServerBufferMgmt(tlsServerBufMgmtIdx);

  TCPIP_P2C(uint8) sessionIdSrcPtr
    = TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxServerSessionIdIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

  TCPIP_P2V(uint8) sessionIdDstPtr
    = TcpIp_GetAddrTlsClientSessionIdAccessBuffer(TcpIp_GetTlsClientSessionIdAccessBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make transmitted sessionID accessible for MSA readout */
  /* Set the actual received SessionID length and copy the sessionID to the MSA_AccessBuffer */
  TcpIp_SetClientSessionIdAccessBufferLenOfTlsConnectionDyn(TlsConIdx, sessionIdLen);
  if (sessionIdLen != 0u)
  {
    /* Copy from the SessionId start IDX (inside of the TLS TX-Buffer) to the AccessBuffer */
    VStdMemCpy(sessionIdDstPtr, sessionIdSrcPtr, sessionIdLen);                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

} /* TcpIp_TlsServerMsa_AddServerSessionIdToAccessBuffer() */

/**********************************************************************************************************************
* TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
[REVIEW_G] c_accepted 16.01.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TCPIP_P2C(uint8) clientRndSrcPtr
    = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(tlsServerBufMgmtIdx));

  TCPIP_P2V(uint8) clientRndDstPtr
    = TcpIp_GetAddrTlsClientRandomAccessBuffer(TcpIp_GetTlsClientRandomAccessBufferStartIdxOfTlsConnection(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Make received ClientRandom value accessible for MSA readout */
  /* Copy random value (stored inside of TLS RxBuffer) to the AccessBuffer */
  VStdMemCpy(clientRndDstPtr, clientRndSrcPtr, TCPIP_TLS_RANDOM_LEN);                                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

} /* TcpIp_TlsServerMsa_AddClientRandomToAccessBuffer() */

#  endif /* (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON) */

/**********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 *********************************************************************************************************************/

# endif /* (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON) */
#endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsServer.c
 *********************************************************************************************************************/
