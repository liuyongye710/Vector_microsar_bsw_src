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
/*!        \file  TcpIp_TlsServer.h
 *        \brief  Transport Layer Security (TLS) server functions implementation.
 *
 *      \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TLSSERVER_H)
# define TCPIP_TLSSERVER_H
# include "TcpIp_Cfg.h"

# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#   include "TcpIp_Lcfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#   define TCPIP_TLS_CIPHERLENLEN 2u
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Add comment that this means that at least one cipher suite id has to be received. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
#   define TCPIP_TLS_MINCIPHERLEN 2u  /* At least one cipher suite ID must be received, therefore the min length is 2 bytes */

#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Major: The min length is wrong. Missing elements: 1 byte session id length, 2 byte compression methods length and compression null. Why is there no test case? */
/* [REVIEW_c] resolved visbdk: Done. TCASE see TCASE-1462826 */
/* [REVIEW_c] open visal 16.01.00.7 Minor: The length is still wrong, since the last element that is added is incorrect (and has value 0). */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.02.00.0 Statement: OK */
#   endif
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.0 Improve: Add comment that describes the content in text form. 4 bytes header, 2 bytes version info, ... */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
/* Minimum ClientHello length: 2 bytes version info, 32 bytes random value, 4 byte cipher suite info, 1 byte session id length, 2 bytes compression method info */
#   define TCPIP_TLS_MIN_CLIENTHELLO_MSGLEN ( TCPIP_TLS_VERSLEN + TCPIP_TLS_RNDLEN + TCPIP_TLS_CIPHERLENLEN \
                                           + TCPIP_TLS_MINCIPHERLEN + TCPIP_TLS_SESSIONIDLEN_LEN + TCPIP_TLSSERVER_COMPMETHLEN_LEN + TCPIP_TLS_COMPMETHLEN_LEN)

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
 * TcpIp_TlsServer_Init
 *********************************************************************************************************************/
/*!  \brief        Initialize the TLS-Server submodule.
 *  \details       -
 *  \param[in]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_Init(void);

/**********************************************************************************************************************
 * TcpIp_TlsServer_ResetConnection
 *********************************************************************************************************************/
/*! \brief         Reset the TLS-Server connection.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_ResetConnection(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerCtx_AsyncHandler
 *********************************************************************************************************************/
/*! \brief         Handle asynchronous context operations for TLS-Server.
 *  \details       Calculates all time consuming operation if the corresponding flags are set
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServerCtx_AsyncHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerCrypto_SetCsmKeys
 *********************************************************************************************************************/
/*! \brief         Set all relevant CSM keys for the crypto operation within the TLS-Server.
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsServerCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServer_ProcessHandshake
 *********************************************************************************************************************/
/*! \brief         Process the TLS-Server handshake state machine.
 *  \details       Executes the TLS-Server handshake state machine, if all conditions are fulfilled.
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServer_ProcessHandshake(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl
 *********************************************************************************************************************/
/*! \brief         Forward the processed TLS handshake message to the record layer for transmission.
 *  \details       Forwards the specific TLS-Server handshake messages to the record layer if the message is ready
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl
 *********************************************************************************************************************/
/*! \brief         Transmit the TLS-Server ChangeCipherSpec message
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsServerTx_SendChangeCipherSpec(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  endif /* (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON) */
# endif /* (TCPIP_SUPPORT_ASRTLSS == STD_ON) */
#endif /* TCPIP_TLSSERVER_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsServer.h
 *********************************************************************************************************************/
