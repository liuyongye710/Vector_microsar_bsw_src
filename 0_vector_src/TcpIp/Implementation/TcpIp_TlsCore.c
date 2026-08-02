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
/*!        \file  TcpIp_TlsCore.c
 *        \brief  Transport Layer Security (TLS) core functions implementation
 *      \details  This file implements the core routines of the TLS stack, which are used by both of the submodule,
 *                the TlsClient and the TlsServer. This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#define TCPIP_TLSCORE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Cfg.h"

#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# include "TcpIp_Tls.h"
# include "TcpIp_TlsCore.h"
# include "TcpIp_TlsPriv.h"

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  include "TcpIp_TlsServer.h"
# endif /* (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON) */
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
#  include "TcpIp_TlsClient.h"
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

# include "TcpIp_Types.h"
# include "TcpIp_Lcfg.h"
# include "TcpIp_Tcp.h"
# include "TcpIp_Tcp_Cbk.h"
# include "Csm.h"
# include "vstdlib.h"

# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif /* (TCPIP_DEV_ERROR_REPORT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define TCPIP_RX_INDICATION_LEN_MAX         (0xFFFFU)
# define TCPIP_TX_INDICATION_LEN_MAX         (0xFFFFU)
# define TCPIP_RX_BUF_SEG_SIZE_TOTAL               2U

 /* PRQA S 3453 3 */ /* MD_MSR_FctLikeMacro */
# define TCPIP_TLS_GET_AES128CBC_PADDING_LEN( AES_INPUT_LEN ) (((AES_INPUT_LEN % TCPIP_TLS_AES_BLOCK_LEN) == 0U) ? 0U : ((uint8)TCPIP_TLS_AES_BLOCK_LEN - (uint8)(AES_INPUT_LEN % TCPIP_TLS_AES_BLOCK_LEN)))
# define TCPIP_TLS_GET_AES128CBC_NROFFULLBLOCKS( BUF_INPUT_LEN) (((BUF_INPUT_LEN % TCPIP_TLS_AES_BLOCK_LEN) == 0U) ? 0U : (TCPIP_TLS_AES_BLOCK_LEN - (BUF_INPUT_LEN % TCPIP_TLS_AES_BLOCK_LEN) -1U))

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
# define TCPIP_START_SEC_VAR_CLEARED_8
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3218 3 */ /* MD_TCPIP_Rule8.9_3218 */
TCPIP_LOCAL CONST(uint8, TCPIP_VAR_CLEARED) TcpIp_Tls_Hs_MasterSecretLabel[] = "master secret";
TCPIP_LOCAL CONST(uint8, TCPIP_VAR_CLEARED) TcpIp_Tls_Hs_KeyExpansionLabel[] = "key expansion";


# define TCPIP_STOP_SEC_VAR_CLEARED_8
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
CONST(uint8, TCPIP_CONST) TcpIp_Tls_Hs_FinishedLabel[2][TCPIP_TLS_LABEL_FINISHED_LEN + 1u] = {
                              "server finished",
                              "client finished"};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define TCPIP_START_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TLS CORE UPPER LAYER (UL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreUl_RxIndication
 *********************************************************************************************************************/
/*! \brief         Forward the UpperLayer RxIndication to TcpIp in case of pending application data for the user
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr             Pointer to the data
 *  \param[in]     DataLen             Length of the data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_RxIndication(
  TcpIp_TlsConnectionIterType       TlsConIdx,
  TCPIP_P2V(uint8)                  DataPtr,
  uint32                            DataLenByte);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataIndirect
 *********************************************************************************************************************/
/*! \brief        Calculate data offsets and forwards the user copyTxData indirect call to the internal function
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     SourceDataLen      Size of buffer requested
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK               UpperLayer CopyTxDataIndirect successful
 *  \return        E_NOT_OK           UpperLayer CopyTxDataIndirect NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataIndirect(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      SourceDataLen,
  TcpIp_SizeOfSocketDynType   SocketIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataDirect
 *********************************************************************************************************************/
/*! \brief         Calculate data offsets and forwards the user copyTxData direct call to the internal function
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     SourceDataPtr      Pointer of the source data.
 *  \param[in]     SourceDataLen      Length of the source data.
 *  \return        E_OK               UpperLayer CopyTxDataDirect successful
 *  \return        E_NOT_OK           UpperLayer CopyTxDataDirect NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataDirect(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) SourceDataPtr,
  CONST(uint32, AUTOMATIC) SourceDataLen);


/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound
 *********************************************************************************************************************/
/*! \brief         Calls the configured UserCopyTxData function under consideration of TLS buffer wraparounds
 *  \details       -
 *  \param[in]     SocketTcpIdx       Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DstChunk1Ptr       Pointer to the first destination data.
 *  \param[in]     DstChunk1LenPtr    Length of the first destination data.
 *  \param[in]     DstChunk2Ptr       Pointer to the second destination data. NULL_PTR if not used
 *  \param[in]     DstChunk2LenPtr    Length of the second destination data. 0 if not used
 *  \param[in]     UseTlsCopyTxData   If TRUE the TLS internal CopyTxData function is called, otherwise the UpperLayer
 *  \return        E_OK               UpperLayer CopyTxDataIndirect successful
 *  \return        E_NOT_OK           UpperLayer CopyTxDataIndirect NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DstChunk1Ptr,
  TCPIP_P2V(uint32)            DstChunk1LenPtr,
  TCPIP_P2V(uint8)             DstChunk2Ptr,
  TCPIP_P2V(uint32)            DstChunk2LenPtr,
  CONST(boolean, AUTOMATIC)    UseTlsCopyTxData);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound
 *********************************************************************************************************************/
/*! \brief         Increment the TlsBuffer TX write index by the given value under consideration of buffer wraparounds
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     Value              Length of the source data
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_SizeOfTlsBufferTxType Value);

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsListener_Init
 *********************************************************************************************************************/
/*! \brief         Initialize all the configured TlsListeners and their values
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.7
*/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsListener_Init(void);
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Minor: Function is not local */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif

/**********************************************************************************************************************
 *  TcpIp_TlsListener_ResetListener
 *********************************************************************************************************************/
/*! \brief         Reset the given TlsListener to its default values after a reset
 *  \details       -
 *  \param[in]     TlsListener      TLS Listener index
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsListener_ResetListener(
  TcpIp_TlsListenerIterType TlsListener);

/**********************************************************************************************************************
 *  TcpIp_TlsListener_ForwardCloseToTlsConnection
 *********************************************************************************************************************/
/*! \brief         Finds the corresponding TLS connection and forwards the close call
 *  \details       -
 *  \param[in]     TlsListener  TLS Listener index
 *  \param[in]     Abort        TRUE: connection will immediately be terminated by sending a RST-Segment and releasing
 *                              all related resources.
 *                              FALSE: connection will be terminated after performing a regular connection termination
 *                              and releasing all related resources.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_open 16.01.00.4
*/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsListener_ForwardCloseToTlsConnection(
  TcpIp_TlsListenerIterType TlsListener,
  boolean Abort);
# endif /* (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON) */

/**********************************************************************************************************************
 *  TLS CORE CONTENT TYPE (CT)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_RxIndication
 *********************************************************************************************************************/
/*! \brief         Indicates a reception of new TLS handshake message
 *  \details       This function is called by the TLS RX record layer functions
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtHs_RxIndication(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_VerifyMsgCompleteness
 *********************************************************************************************************************/
/*! \brief         Peeks the length in the TLS handshake message and checks if the complete message is received
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HsMsgLenPtr        Length of the TLS handshake message
 *  \return        E_OK               TLS message verified successful
 *  \return        E_NOT_OK           TLS message verified NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_VerifyMsgCompleteness(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) HsMsgLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg
 *********************************************************************************************************************/
/*! \brief         Reads out the length of the TLS handshake message
 *  \details       This function is only called when we ensure that we received the complete length information
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HsMsgLenPtr        Length of the TLS handshake message
 *  \return        E_OK               Msg length was read sucessfully
 *  \return        E_NOT_OK           Msg length was not read because complete message not received
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) HsMsgLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler
 *********************************************************************************************************************/
/*! \brief         Validates the received TLS handshake message and forwards it.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HsMsgLen           Length of the TLS handshake message
 *  \return        E_OK               TLS message forwarded successful
 *  \return        E_NOT_OK           TLS message forwarded NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_ValidateTypeField
 *********************************************************************************************************************/
/*! \brief         Validates the TLS handshake type field.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     HsMsgLen           Length of the TLS handshake message
 *  \return        E_OK               TLS handshake message verified successful
 *  \return        E_NOT_OK           TLS handshake message verified NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateTypeField(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable
 *********************************************************************************************************************/
/*! \brief         Check if the current received TLS handshake message is receivable with the configured connection.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               TLS handshake message verified successful
 *  \return        E_NOT_OK           TLS handshake message verified NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType
 *********************************************************************************************************************/
/*! \brief         Validate the order of the current received TLS handshake message.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               TLS handshake message verified successful
 *  \return        E_NOT_OK           TLS handshake message verified NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_CheckForDuplicateMessages(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_CheckForDuplicateMessages
 *********************************************************************************************************************/
/*! \brief         Check if the read index of the received TLS handshake type is set to NO_VALUE
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               TLS handshake message NOT duplicated
 *  \return        E_NOT_OK           TLS handshake message duplicated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_UpdateTypeInformation
 *********************************************************************************************************************/
 /*! \brief         Update the Start index and length information of the received TLS handshake type
  *  \details       -
  *  \param[in]     TlsConIdx          TLS connection index
  *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[in]     HsMsgLen           Length of the TLS handshake message
  *  \return        E_OK               TLS Type information updated successful
  *  \return        E_NOT_OK           TLS Type information updated NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_UpdateTypeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame
 *********************************************************************************************************************/
/*! \brief         Validate the received HelloRequest frame
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtHs_HandleInvalidHsMessage
 *********************************************************************************************************************/
/*! \brief         Store an user error and trigger an alert if an invalid TLS handshake message is received
 *  \details       This function is only called if an invalid TLS handshake message is received during the TLS handshake
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtHs_HandleInvalidHsMessage(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE CHANGE CIPHER SPEC
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreCtCcs_ValidateAndForwardFrameToCCsHandler
 *********************************************************************************************************************/
/*! \brief         Verifies the received TLS CCS message and forward it
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               ChangeCipherSpec message verified successful
 *  \return        E_NOT_OK           ChangeCipherSpec message verified NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtCcs_ValidateAndForwardFrameToCCsHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage
 *********************************************************************************************************************/
/*! \brief         Store an user error and trigger an alert if an invalid TLS CCS message is received
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE CT APPLICATION DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAd_RxIndication
 *********************************************************************************************************************/
/*! \brief         Indicates an reception of new TLS application
 *  \details       This function is called by the TLS RX application data function
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAd_RxIndication(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAd_ForwardDataToAdHandler
 *********************************************************************************************************************/
/*! \brief         Checks the receive buffer and forward the TLS application data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               Application data forwarded successful
 *  \return        E_NOT_OK           Application data forwarded NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAd_ForwardDataToAdHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE CT ALERT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_RxIndication
 *********************************************************************************************************************/
/*! \brief         Indicates an reception of new TLS alert
 *  \details       This function is called by the TLS RX alert function
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_RxIndication(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer
 *********************************************************************************************************************/
/*! \brief         Forwards the received alert to the TLS TX buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     AlertLevel         TLS alert level
 *  \param[in]     AlertDescription   TLS alert description
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TcpIp_TlsAlertLevelType       AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_TxAlert
 *********************************************************************************************************************/
/*! \brief         Checks if new TLS alerts are stored in the TLS Tx buffer and forward them to the TLS record layer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_TxAlert(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler
 *********************************************************************************************************************/
/*! \brief         Checks for new received TLS alerts and forward them.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               Alert forwarded successful
 *  \return        E_NOT_OK           Alert forwarded NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_ParseReceivedAlert
 *********************************************************************************************************************/
/*! \brief         Parse new received TLS alerts
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_ParseReceivedAlert(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_CheckAlert
 *********************************************************************************************************************/
/*! \brief         Check the validity of the received Alert level and Alert description
 *  \details       -
 *  \param[in]     AlertLevel            AlertLevel which should be validated
 *  \param[in]     AlertDescription      AlertDescritpion which should be validated
 *  \return        E_OK                  If both parameter are valid
 *  \return        E_NOT_OK              If AlertLevel or AlertDescription is invalid
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAl_CheckAlert(
  TcpIp_TlsAlertLevelType AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_HandleAllOtherAlerts
 *********************************************************************************************************************/
/*! \brief         Generic TLS alert handler for received TLS alerts
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_HandleAllOtherAlerts(
  TcpIp_TlsConnectionIterType TlsConIdx);
/**********************************************************************************************************************
 * TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert
 *********************************************************************************************************************/
/*! \brief         TLS alert handler for CloseNotify alert
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE RECORD LAYER (RL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_Init
 *********************************************************************************************************************/
/*! \brief         Initialize the TLS record layer
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxIndication
 *********************************************************************************************************************/
/*! \brief         Indicates the reception of new TLS record layer frames.
 *  \details       This function is called by the TLS RX record layer function
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_RxIndication(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxConfirmation
 *********************************************************************************************************************/
/*! \brief         Forward the outstanding TxConfirmations to the UpperLayer
 *  \details       This function checks the number of bytes which have to be confirmed to the upper layer
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_TxConfirmation(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TransmitFrame
 *********************************************************************************************************************/
/*! \brief         transform a TLS content type (HS,AD,AL) into a TLS record layer frame and forwards to TcpIp
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentTypeTxStartIdx Start index of this frame
 *  \param[in]     PlaintextTxLen        Plain text length of this frame
 *  \param[in]     ContentType           ContentType of this frame
 *  \return        E_OK                  Transmit operation successful
 *  \return        E_NOT_OK              Transmit operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType ContentTypeTxStartIdx,
  TcpIp_SizeOfTlsBufferTxType PlaintextTxLen,
  CONST(uint8, AUTOMATIC)     ContentType);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_FragmentFrameAndTransmit
 *********************************************************************************************************************/
/*! \brief         If the given TLS content type has to be fragmented, forwards the parts to the
 *                 TcpIp_TlsCoreRl_TransmitFrame function.
 *  \details       -
 *  \param[in]     TlsConIdx      TLS connection index
 *                                CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TxStartIdx     Start index of the content in Tls buffer
 *  \param[in]     TxLen          Length of this content
 *  \param[in]     ContentType    ContentType (AD, HS)
 *  \return        E_OK           Transmit operation successful
 *  \return        E_NOT_OK       Transmit operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_FragmentFrameAndTransmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TxStartIdx,
  TcpIp_SizeOfTlsBufferTxType TxLen,
  CONST(uint8, AUTOMATIC) ContentType);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CheckTcpBuffer
 *********************************************************************************************************************/
/*! \brief         Check if there is enough space in the Tcp buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CipherTextTxLen    Length of the TLS Tx frame (excluding header length)
 *  \return        E_OK               Enough space available in Tcp buffer
 *  \return        E_NOT_OK           NOT enough space available in Tcp buffer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckTcpBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      CipherTextTxLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TransmitFrameHdr
 *********************************************************************************************************************/
/*! \brief         Transmit the TLS record layer header (5Bytes)
 *  \details       This function calls TcpIp_TcpTransmitInternal via direct data provision
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               Transmit operation successful
 *  \return        E_NOT_OK           Transmit operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrameHdr(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TransmitFrameCiphertext
 *********************************************************************************************************************/
/*! \brief         Trigger TCP transmission of the data in the TLS TX buffer
 *  \details       This function calls TcpIp_TcpTransmitInternal via indirect data provision
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               Transmit operation successful
 *  \return        E_NOT_OK           Transmit operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrameCiphertext(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend
 *********************************************************************************************************************/
/*! \brief         Calculates the length of TLS contentType under consideration of the selected cipher suite
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentTypeLen     Length of the contentType data without respecting the selected cipher
 *  \return        Calculated TLS ContentType length depending on the selected cipher
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) ContentTypeLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CalcHmacCipherDependend
 *********************************************************************************************************************/
/*! \brief         Perform the cipher dependent authentication (if any)
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TcpBufLength       TCP buffer length
 *  \return        E_OK               HMAC Operation successful
 *  \return        E_NOT_OK           HMAC Operation NOT successful
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 TcpBufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptCipherDependend
 *********************************************************************************************************************/
/*! \brief         Perform the cipher dependent encryption (if any)
 *  \details       -
 *  \param[in]     TlsConIdx            TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr               TcpIp Tx buffer
 *  \param[in]     BufLength            TcpIp Tx buffer size
 *  \return        BUFREQ_OK            Buffer request accomplished successful
 *  \return        BUFREQ_E_NOT_OK      Buffer request not successful. Buffer cannot be accessed
 *  \return        BUFREQ_E_BUSY        Temporarily no buffer available. It's up the requestor to retry request
 *                                      for a certain time
 *  \return        BUFREQ_E_OVFL        No Buffer of the required length can be provided.
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_ValidateFrameHdr
 *********************************************************************************************************************/
/*! \brief         Verify that the received TLS record layer header is correct
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TotDataLen            Total data length
 *  \param[in,out] RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ValidateFrameHdr(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 TotDataLen,
  TCPIP_P2V(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_ValidateRlFragmentLength
 *********************************************************************************************************************/
/*! \brief         Verify that the received RL frame is within correct fragment length
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[out]    RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ValidateRlFragmentLength(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_VerifyFrameCompleteness
 *********************************************************************************************************************/
/*! \brief         Verify that the received TLS record layer frame is complete
 *  \details       -
 *  \param[in] TotDataLen                Total data length
 *  \param[in,out] RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[in,out] RlHdrLenPtr           Pointer to the length information stored inside of the RL frame header
 *  \return        E_OK                  Operation successful
 *  \return        E_NOT_OK              Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyFrameCompleteness(
  uint32 TotDataLen,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(uint16) RlHdrLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CheckIfFrameIsReceivable
 *********************************************************************************************************************/
/*! \brief         Checks if the TLS stack is in the correct state to process the received TLS frame
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[in,out] RlAlertDescriptionPtr If operation fails, alert description is stored in this parameter
 *  \return        E_OK                  if the frame is receivable
 *  \return        E_NOT_OK              if the frame is NOT receivable
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckIfFrameIsReceivable(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_ForwardFrameToUpperLayer
 *********************************************************************************************************************/
/*! \brief         Forwards the received TLS record layer frame to the upper layer (AD,HS,AL)
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[in]     RlFrameLen            Length of the TLS record layer frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \return        E_OK                  Operation successful
 *  \return        E_NOT_OK              Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ForwardFrameToUpperLayer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_ParseAndValidateRlHdr
 *********************************************************************************************************************/
/*! \brief         Check the correctness of TLS record layer frame header fields
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] RlHdrPtr              Pointer to the RL header of the TLS record layer frame
 *  \param[in]     RlHdrLen              Length of the TLS record layer frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \return        E_OK                  Operation successful
 *  \return        E_NOT_OK              Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ParseAndValidateRlHdr(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  CONST(uint8, AUTOMATIC) RlHdrLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAndAuthFrame
 *********************************************************************************************************************/
/*! \brief         Forward the encrypted TLS record layer frame to decrypt and authentication functions
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     RlFrameLen         Length of the TLS record layer frame
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_DecryptAndAuthFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate
 *********************************************************************************************************************/
/*! \brief         Forward the encrypted TLS record layer frame to the cipher dependent decrypt and
 *                 authentication functions
 *  \details       Forward one TCP segment which contains the received encrypted TLS record layer frame
 *                 to the cipher dependent decrypt and authentication functions. This function may be called
 *                 twice for AdHs
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType            TLS ContentType of this frame
 *  \param[in]     DataPtr                TCP buffer segment which contains the TLS Rl frame
 *  \param[in]     DataLen                Data length of TCP buffer segment
 *  \param[in,out] RlAlertDescriptionPtr  If Operation fails, alert description is stored in this parameter
 *  \param[in]     CompleteRlFrameFlag    TRUE  A complete TLS Rl frame is available, Decryption is done.
 *                                        FALSE Only a partial TLS Rl frame is available. Decryption is not done.
 *  \return        E_OK                   Operation successful
 *  \return        E_NOT_OK               Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(uint8)                         DataPtr,
  uint16                                   DataLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr,
  boolean                                  CompleteRlFrameFlag);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptFrame
 *********************************************************************************************************************/
/*! \brief         Perform decryption of the data in the provided TCP buffer segment
 *  \details       Check the cipher and perform the decryption
 *  \param[in]     TlsConIdx            TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType          TLS ContentType of this frame
 *  \param[in]     DataPtr              TCP buffer segment which contains part of or complete TLS Rl frame
 *  \param[in]     DataLen              Data length of TCP buffer segment
 *  \param[in]     CompleteRlFrameFlag  TRUE  A complete TLS Rl frame is available, Decryption is done.
 *                                      FALSE Only a partial TLS Rl frame is available. Decryption is not done.
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherDecryptFrame(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(uint8)                         DataPtr,
  uint16                                   DataLen,
  boolean                                  CompleteRlFrameFlag);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherAuthenticateFrame
 *********************************************************************************************************************/
/*! \brief         Perform authentication of data
 *  \details       Check the cipher and perform the authentication
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType           TLS ContentType of this frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \return        E_OK                  Operation successful
 *  \return        E_NOT_OK              Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherAuthenticateFrame(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_HandleInvalidRlFrame
 *********************************************************************************************************************/
/*! \brief         Store user error and trigger alert in case of invalid TLS record layer frame
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     RlFrameLen         Length of the TLS record layer frame
 *  \param[in]     AlertDescription   Alert description which should be transmitted in the TLS alert message
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_HandleInvalidRlFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  TcpIp_TlsAlertDescriptionType AlertDescription);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptNull
 *********************************************************************************************************************/
/*! \brief         Decrypt TLS data using Null streaming mode
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
*  \param[in]     ContentType        TLS ContentType of this frame
*  \param[in]     DataPtr            Source data pointer
*  \param[in]     DataLen            Source data length
*  \return        E_OK               Operation successful
*  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherDecryptNull(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherAuthenticateSha
 *********************************************************************************************************************/
/*! \brief         Authenticate TLS data using SHA
 *  \details       -
 *  \param[in]     TlsConIdx             TLS connection index
 *                                       CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType           TLS ContentType of this frame
 *  \param[in,out] RlAlertDescriptionPtr If Operation fails, alert description is stored in this parameter
 *  \return        E_OK                  Operation successful
 *  \return        E_NOT_OK              Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherAuthenticateSha(
  TcpIp_TlsConnectionIterType               TlsConIdx,
  CONST(uint8, AUTOMATIC)                   ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType)  RlAlertDescriptionPtr);

/**********************************************************************************************************************
* TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming
 *********************************************************************************************************************/
/*! \brief         Decrypt TLS data using Aes128Cbc streaming mode
 *  \details       -
 *  \param[in]     TlsConIdx            TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType          TLS ContentType of this frame
 *  \param[in]     DataPtr              Source data pointer
 *  \param[in]     DataLen              Source data length
 *  \param[in]     CompleteRlFrameFlag  TRUE  A complete TLS Rl frame is available, Decryption is done.
 *                                      FALSE Only a partial TLS Rl frame is available. Decryption is not done.
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  CONST(uint8, AUTOMATIC)      ContentType,
  TCPIP_P2V(uint8)             DataPtr,
  uint16                       DataLen,
  boolean                      CompleteRlFrameFlag);

/**********************************************************************************************************************
* TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming
 *********************************************************************************************************************/
/*! \brief         Decrypt TLS data using Aes128Cbc streaming mode
 *  \details        -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType          TLS ContentType of this frame
 *  \param[in]     DataPtr              Source data pointer
 *  \param[in]     DataLen              Source data length
 *  \param[in]     CompleteRlFrameFlag  TRUE  A complete TLS Rl frame is available, Decryption is done.
 *                                      FALSE Only a partial TLS Rl frame is available. Decryption is not done.
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2V(uint8)            DataPtr,
  uint16                      DataLen,
  boolean                     CompleteRlFrameFlag);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment
 *********************************************************************************************************************/
/*! \brief         Check the input data length of the AES-128-CBC operation to its alignment of a multiple of the used block size
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataLen            Length of TCP buffer segment
 *  \return        E_OK               Data length aligned to the block size
 *  \return        E_NOT_OK           Data length NOT aligned to the block size
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 DataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc
 *********************************************************************************************************************/
/*! \brief         Decrypt a complete TLS frame using Aes128 Cbc
 *  \details       Decrypt a complete TLS frame that is present in the provided TCP buffer segments
 *                 using Aes128 Cbc streaming. This function can be called only once for a RL frame.
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in]     DataPtr            TCP buffer segment containing full or second part of TLS frame
 *  \param[in]     DataLen            Length of TCP buffer segment
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  uint8                        ContentType,
  TCPIP_P2C(uint8)             DataPtr,
  uint16                       DataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm
 *********************************************************************************************************************/
/*! \brief         Decrypt provided TLS data using Aes128 Cbc
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in]     DataPtr            Source data pointer
 *  \param[in]     DataLen            Source data length
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint8                       ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv
 *********************************************************************************************************************/
/*! \brief         Extract the IV from TCP buffer and set Csm keys for decryption.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TcpSeg1Ptr         Data pointer of the first TCP segment
 *  \param[in]     IvInTcpSeg1Len     Length of Iv in TCP segment 1
 *  \param[in]     TcpSeg2Ptr         Data pointer of the second TCP segment
 *                                    CONSTRAINT: [sizeof(TcpSeg1Ptr) + sizeof(TcpSeg2Ptr) >= TCPIP_TLS_AES128_IV_LEN]
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            TcpSeg1Ptr,
  uint16                      IvInTcpSeg1Len,
  TCPIP_P2C(uint8)            TcpSeg2Ptr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv
 *********************************************************************************************************************/
/*! \brief         Extract the AEAD Gcm IV from TCP buffer and set Csm keys for decryption
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TcpSeg1Ptr         Data pointer of the TCP segment 1
 *  \param[in]     IvInTcpSeg1Len     Length of Iv in TCP segment 1
 *  \param[in]     TcpSeg2Ptr         Data pointer of the TCP segment 2
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            TcpSeg1Ptr,
  uint16                      IvInTcpSeg1Len,
  TCPIP_P2C(uint8)            TcpSeg2Ptr);

/**********************************************************************************************************************
 * TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment
 *********************************************************************************************************************/
/*! \brief         Calculate teh size of the next available segment of the TLS Rx AdHs Buffer.
 *  \details       Depending on the readIdx and writeIdx, calculate size of next free segment of TLS Rx AdHs Buffer.
 *                 This is not the total free space in the circular buffer but from the WriteIdx either to the ReadIdx
 *                 or to the end of the circular buffer.
 *  \param[in]     TlsConIdx         TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        TlsSegLen         Size of the next free segment of TLS Rx AdHs buffer
 *  \pre           -
 *  \context       TASKTASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(uint32, TCPIP_CODE) TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer
 *********************************************************************************************************************/
/*! \brief         Check if Rl frame fits into Tls Rx buffer
 *  \details       -
 *  \param[in]     TlsConIdx         TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType       Type of Rl content
 *  \param[in]     RlFrameLen        Length of the Rl frame
 *  \return        TRUE              Rl frame fits in the Tls Rx buffer
 *  \return        FALSE             Rl frame does not fit in the Tls Rx buffer
 *  \pre           -
 *  \context       TASKTASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint8                       ContentType,
  uint16                      RlFrameLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyDataToRxBuf
 *********************************************************************************************************************/
/*! \brief         Forward the copy request depending on the given TLS content type
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in]     DataPtr            Source data pointer
 *  \param[in]     DataLen            Source data length
 *  \param[in,out] CopiedLenPtr       Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound
 *********************************************************************************************************************/
/*! \brief         Copy the date to the AD/HS RX buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Source data pointer
 *  \param[in]     DataLen            Source data length
 *  \param[in,out] CopiedLenPtr       Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyDataToRxBufCcs
 *********************************************************************************************************************/
/*! \brief         Copy the data to the CCS RX buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Source data pointer
 *  \param[in]     DataLen            Source data length
 *  \param[out]    CopiedLenPtr       Bytes copied to the TLS Ccs buffer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBufCcs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyDataToRxBufAl
 *********************************************************************************************************************/
/*! \brief         Copy the data to the AL RX buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Source data pointer
 *  \param[in]     DataLen            Source data length
 *  \param[out]    CopiedLenPtr       Bytes copied to the TLS Al buffer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc
 *********************************************************************************************************************/
/*! \brief         Aes128 Cbc encryption
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr              TcpIp Tx buffer pointer
 *  \param[in]     BufLength           TcpIp Tx buffer size
 *  \return        BUFREQ_OK           Buffer request accomplished successful
 *  \return        BUFREQ_E_NOT_OK     Buffer request not successful. Buffer cannot be accessed
 *  \return        BUFREQ_E_BUSY       Temporarily no buffer available. It's up the requestor to retry request for
 *                                     a certain time
 *  \return        BUFREQ_E_OVFL       No Buffer of the required length can be provided
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm
 *********************************************************************************************************************/
/*! \brief         Aes128 Gcm encryption and authentication
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr             TcpIp Tx buffer pointer
 *  \param[in]     BufLength          TcpIp Tx buffer size
 *  \return        BUFREQ_OK          Buffer request accomplished successful
 *  \return        BUFREQ_E_NOT_OK    Buffer request not successful. Buffer cannot be accessed
 *  \return        BUFREQ_E_BUSY      Temporarily no buffer available. It's up the requestor to retry request for
 *                                    a certain time
 *  \return        BUFREQ_E_OVFL      No Buffer of the required length can be provided
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptNull
 *********************************************************************************************************************/
/*! \brief         Null encryption
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr              TcpIp Tx buffer pointer
 *  \param[in,out] BufLength           TcpIp Tx buffer size
 *  \return        BUFREQ_OK           Buffer request accomplished successful
 *  \return        BUFREQ_E_NOT_OK     Buffer request not successful. Buffer cannot be accessed
 *  \return        BUFREQ_E_BUSY       Temporarily no buffer available. It's up the requestor to retry request for
 *                                     a certain time
 *  \return        BUFREQ_E_OVFL       No Buffer of the required length can be provided
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptNull(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode
 *********************************************************************************************************************/
/*! \brief         Null encryption streaming mode
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr              Tcp Tx buffer pointer
 *  \param[in,out] BufLength           Tcp Tx buffer size
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound
 *********************************************************************************************************************/
 /*! \brief         Copy the plaintext data from the TLS buffer to the provided TCP buffer segments.
  *  \details       -
  *  \param[in]     TlsConIdx           TLS connection index
  *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpSeg1Ptr          TCP Tx buffer segment 1 buffer
 *  \param[out]     TcpSeg1Len          TCP Tx buffer segment 1 length
 *  \param[out]     TcpSeg2Ptr          TCP Tx buffer segment 2 buffer
 *                                      CONSTRAINT: (Seg2Ptr != NULL_PTR)
 *  \param[out]     TcpSeg2Len          TCP Tx buffer segment 2 length
 *  \pre           Tcp content data is present in the Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  uint32                      TcpSeg1Len,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  uint32                      TcpSeg2Len);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyHmacToTxBuffer
 *********************************************************************************************************************/
/*! \brief         Copy the Mac into the TcpIp
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     Seg1Ptr             TcpIp Tx buffer segment 1
 *  \param[out]     Seg1Len             TcpIp Tx buffer segment 1 length
 *  \param[out]     Seg2Ptr             TcpIp Tx buffer segment 2 buffer
 *                                      CONSTRAINT: (Seg2Ptr != NULL_PTR)
 *  \pre           Mac is present in the Tls temp buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyHmacToTxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            Seg1Ptr,
  uint32                      Seg1Len,
  TCPIP_P2V(uint8)            Seg2Ptr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode
 *********************************************************************************************************************/
/*! \brief         Handles AesCbc128 encryption of content data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Pointer to the destination buffer
 *  \param[in]     BufLength          Length of the destination buffer
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode
 *********************************************************************************************************************/
/*! \brief         Handles AesCbc128 encryption of content data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Pointer to the destination buffer
 *  \param[in]     BufLength          Length of the destination buffer
 *  \return        E_OK               Operation successful
 *  \return        E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall
 *********************************************************************************************************************/
/*! \brief         AesCbc128 encryption of content data with TCP buffer wraparound
 *  \details       Handles AesCbc128 encryption of content data when there is TCP buffer wraparound
 *  \param[in]     TlsConIdx        TLS connection index
 *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    TcpSeg1Ptr       TCP segment 1 buffer
 *                                   CONSTRAINT: (TcpIpSeg1Ptr != NULL_PTR)
 *  \param[in]     TcpSeg1LenPtr    TCP segment 1 buffer size
 *  \param[out]    TcpSeg2Ptr       TCP segment 2 buffer
 *                                   CONSTRAINT: (TcpIpSeg2Ptr != NULL_PTR)
 *  \param[in]     TcpSeg2LenPtr    TCP segment 2 buffer size
 *  \return        E_OK              Operation successful
 *  \return        E_NOT_OK          Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  uint32                      TcpSeg1Len,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  uint32                      TcpSeg2Len);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound
 *********************************************************************************************************************/
 /*! \brief         AesGcm128 encryption of content data with TCP buffer wraparound
  *  \details       Handles AesGcm128 encryption of content data when there is TCP buffer wraparound
  *  \param[in]     TlsConIdx        TLS connection index
  *                                   CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[out]    TcpIpSeg1Ptr      Tcp first segment buffer
  *                                   CONSTRAINT: (TcpIpSeg1Ptr != NULL_PTR)
  *  \param[in]     TcpIpSeg1LenPtr   Tcp first segment buffer size
  *  \param[out]    TcpIpSeg2Ptr      Tcp second segment buffer
  *                                   CONSTRAINT: (TcpIpSeg2Ptr != NULL_PTR)
  *  \param[in]     TcpIpSeg2LenPtr   Tcp second segment buffer size
  *  \return        E_OK              Operation successful
  *  \return        E_NOT_OK          Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  uint32                      TcpIpSeg1Len,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  uint32                      TcpIpSeg2Len);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding
 *********************************************************************************************************************/
/*! \brief        Aes128 Cbc encryption of Mac and Padding
 *  \details      Performs Aes128 Cbc encryption of Mac and Padding into Tls temp buffer
 *                into the temp buffer
 *  \param[in]    TlsConIdx   TLS connection index
 *                            CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]   EncDataLen  Length of data which was encrypted
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
 *  \pre          Mac is already available in the Tls temp buffer
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32)           EncDataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall
 *********************************************************************************************************************/
/*! \brief        Aes128Cbc encryption with NO TcpIp wraparound
 *  \details      Performs Aes128Cbc encryption of content data, mac and padding
 *                when there is no TcpIp buffer wraparound
 *  \param[in]    TlsConIdx   TLS connection index
 *                             CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]   BufPtr      TcpIp destination buffer
 *                            If E_OK, it will contain encrypted message
 *  \param[in]    BufLength   Length of the provided TcpIp destination buffer
 *  \return         E_OK      Operation successful
 *  \return         E_NOT_OK  Operation NOT successful
 *  \pre          Content data is available in Tls Tx buffer
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall
 *********************************************************************************************************************/
/*! \brief        Aes128Gcm encryption with NO TcpIp wraparound
 *  \details      Performs Aes128Gcm encryption and authentication of content data
 *                when there is no TcpIp buffer wraparound
 *  \param[in]    TlsConIdx   TLS connection index
 *                             CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]   BufPtr      TcpIp destination buffer
 *                            If E_OK, it will contain encrypted message
 *  \param[in]    BufLength   Length of the provided TcpIp destination buffer
 *  \return       E_OK        Operation successful
 *  \return       E_NOT_OK    Operation NOT successful
 *  \pre          Content data is available in Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128 Cbc encryption of content with linear TcpIp buffer (NO wraparound)
  *  \details      his function handles Aes128 Cbc encryption of the Rl content data
  *                when the TcpIp buffer is linear
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr                 TcpIp buffer
 *  \param[in,out] AvailableBufferLenPtr  Size of TcpIp buffer
 *  \return        E_OK                   Operation successful
 *  \return        E_NOT_OK               Operation NOT successful
 *  \pre           Content data is available in Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128 Gcm encryption of content with linear TcpIp buffer (NO wraparound)
 *  \details       This function handles Aes128 Gcm encryption of the Rl content data
 *                 when the TcpIp buffer is linear
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    BufPtr                 TcpIp buffer
 *  \param[in,out] AvailableBufferLenPtr  Size of TcpIp buffer
 *  \param[out]    AuthTagPtr             Authentication tag buffer
 *  \param[in,out] AuthTagLenPtr          Length of Additional Tag buffer
 *  \return         E_OK                  Operation successful
 *  \return         E_NOT_OK              Operation NOT successful
 *  \pre           Content data is available in Tls Tx buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128 Cbc encryption of content with TcpIp wraparound
 *  \details       This function handles Aes128 Cbc encryption of the Rl content data
 *                 when the TcpIp buffer wraps around
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return         E_OK                Operation successful
 *  \return         E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound
 *********************************************************************************************************************/
/*! \brief          Aes128 Gcm encryption of content with TcpIp wraparound
 *  \details        This function handles Aes128 Gcm encryption of the Rl content data
 *                  when the TcpIp buffer wraps around
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \param[out]     AuthTagPtr          Authentication tag buffer
 *  \param[in,out]  AuthTagLenPtr       Length of Additional Tag buffer
 *  \return         E_OK                Operation successful
 *  \return         E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound
 *********************************************************************************************************************/
 /*! \brief          Aes128 Gcm encryption of AdHs with TCP wraparound
  *  \details        This function handles Aes128 Gcm encryption of the Rl AdHs data
  *                  when the TcpIp buffer wraps around
  *  \param[in]      TlsConIdx           TLS connection index
  *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
  *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
  *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
  *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
  *  \param[out]     AuthTagPtr          Authentication tag buffer
  *  \param[in,out]  AuthTagLenPtr       Length of Additional Tag buffer
  *  \return         E_OK                Operation successful
  *  \return         E_NOT_OK            Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHs
 *********************************************************************************************************************/
/*! \brief         Aes128 Cbc encryption of the AdHs content data
 *  \details       Performs Aes128 Cbc encryption of AdHs content data
 *                 in the Tls buffer into a linear Tcp buffer
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     BuffPtr                 Tcp linear buffer
 *  \param[in,out] AvailableBufferLenPtr   Size of buffer (at least size of content data)
 *                                            If E_OK, this ptr contains the num of bytes filled of the Tcp buffer
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs
 *********************************************************************************************************************/
/*! \brief         Aes128 Gcm encryption of the AdHs content data
 *  \details       Performs Aes128 Gcm encryption of AdHs content data
 *                 in the Tls buffer into a linear TcpIp buffer
 *  \param[in]     TlsConIdx               TLS connection index
 *                                         CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     BuffPtr                 TcpIp linear buffer
 *  \param[in,out] AvailableBufferLenPtr   Size of buffer (at least size of content data)
 *                                         If E_OK, this ptr contains the num of bytes filled of the TcpIp buffer
 *  \param[out]    AuthTagPtr              Authentication tag buffer
 *  \param[in,out] AuthTagLenPtr           Length of Additional Tag buffer
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAl
 *********************************************************************************************************************/
/*! \brief         Aes128 Cbc encryption of the Alert content data
 *  \details       Performs Aes128 Cbc encryption of Alert content data
 *                  in the Tls buffer into a linear TcpIp buffer
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      BufPtr                  TcpIp linear buffer
 *  \param[in,out]  AvailableBufferLenPtr   Size of buffer (at least size of content data)
 *                                          If E_OK, this ptr contains the num of bytes filled of the TcpIp buffer
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl
 *********************************************************************************************************************/
/*! \brief         Aes128 Gcm encryption of the Alert content data
 *  \details       Performs Aes128 Gcm encryption of Alert content data
 *                 in the Tls buffer into a linear TcpIp buffer
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     BuffPtr                 TcpIp linear buffer
 *  \param[in,out] AvailableBufferLenPtr   Size of buffer (at least size of content data)
 *                                          If E_OK, this ptr contains the num of bytes filled of the TcpIp buffer
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128 CBC encryption of the alert data
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpSeg1Ptr          TCP first segment buffer
 *  \param[in,out]  TcpSeg1LenPtr       TCP first segment buffer size
 *                                      If E_OK, contains the data size in TcpSeg1Ptr
 *  \param[out]     TcpSeg2Ptr          TCP second segment buffer
 *  \param[in,out]  TcpSeg2LenPtr       TCP second segment buffer size
 *                                      If E_OK, contains the data size in TcpSeg2Ptr
 *  \return         E_OK                Operation successful
 *  \return         E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128 GCM encryption of the alert data
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return         E_OK                Operation successful
 *  \return         E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCrypto_GenerateAesIv
 *********************************************************************************************************************/
/*! \brief         Generate AES initialization vector (IV)
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     AesIvPtr            Buffer where IV shall be stored
 *                                      CONSTRAINT Should be at least TCPIP_TLS_AES128_IV_LEN size
 *  \return         E_OK                Operation successful
 *  \return         E_NOT_OK            Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreCrypto_GenerateAesIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            AesIvPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData
 *********************************************************************************************************************/
/*! \brief         Generate AD data for AEAD with AES 128 GCM
 *  \details       -
 *  \param[in]      TlsSeqNum           Tls sequence number (64-bit)
 *  \param[in]      ContentLen          Length of content data
 *  \param[in]      Type                Type of data
 *  \param[out]     AddAuthDataPtr      Buffer to store additional auth data
 *                                      CONSTRAINT Should be at least TCPIP_TLS_AES128_GCM_AADATA_LEN size
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(
  uint64                      TlsSeqNum,
  uint16                      ContentLen,
  uint8                       Type,
  TCPIP_P2V(uint8)            AddAuthDataPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCrypto_SetAEADGcmIvValue
 *********************************************************************************************************************/
/*! \brief         Generate the Iv for Gcm and set the CSM key
 *  \details       -       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]    GcmEIvPtr           Buffer where the explicit IV shall be stored
 *                                     CONSTRAINT Should be at least TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN size
 *  \return         E_OK               Operation successful
 *  \return         E_NOT_OK           Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreCrypto_GenerateAEADGcmIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            GcmEIvPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt
 *********************************************************************************************************************/
/*! \brief         Encrypt the MAC and the padding and store it in the target buffer
 *  \details       Feed the Mac into the already running Aes128 Cbc streamer
 *  \param[in]     TlsConIdx                TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     BufPtr                  Target buffer (e.g. TCP buffer)
 *  \param[in,out]  AvailableBufferLenPtr   Size of TcpIp buffer
 *  \return         E_OK                    Operation successful
 *  \return         E_NOT_OK                Operation NOT successful
 *  \pre            Mac is available in Tls temp buffer
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  TCPIP_P2V(uint8)             BufPtr,
  TCPIP_P2V(uint32)            AvailableBufferLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv
 *********************************************************************************************************************/
/*! \brief          Iv generation and Aes128Cbc encryption with TcpIp wraparound
 *  \details        The function handles Iv generation and Aes128Cbc encryption
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpSeg1Ptr          TCP first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpSeg1LenPtr       TCP first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpSeg2Ptr          TCP second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpSeg2LenPtr       TCP second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv
 *********************************************************************************************************************/
/*! \brief          Iv generation Aes128Gcm with TcpIp wraparound
 *  \details        The function handles Iv generation for AEAD Aes128Gcm
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpSeg1Ptr          TCP first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpSeg1LenPtr       TCP first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpSeg2Ptr          TCP second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpSeg2LenPtr       TCP second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData
 *********************************************************************************************************************/
/*! \brief          Aes128Cbc encryption of content data with TcpIp wrap around
 *  \details        Handles Aes128Cbc encryption of content data when there is TcpIp wrap around
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData
 *********************************************************************************************************************/
/*! \brief          Aes128Gcm encryption of content data with TcpIp wrap around
 *  \details        Handles Aes128Gcm encryption of content data when there is TcpIp wrap around
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \param[out]     AuthTagPtr          Authentication tag buffer
 *                                      CONSTRAINT: Should have at least TCPIP_TLS_AES128_GCM_AUTHTAG_LEN size
 *  \param[in,out]  AuthTagLenPtr       Authentication tag buffer size
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound
 *********************************************************************************************************************/
/*! \brief          Aes128Cbc encryption of AdHs content for TcpIp wraparound
 *  \details        This functions handles Aes128Cbc encryption of AdHs content data when
 *                  there is TcpIp buffer wraparound
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound
 *********************************************************************************************************************/
/*! \brief         Aes128Cbc encryption of AdHs content with TcpIp wraparound and no Tls wraparound
 *  \details        Handles Aes128Cbc encryption of AdHs content when the
 *                  TcpIp wraps around and Tls buffer is linear
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound
 *********************************************************************************************************************/
/*! \brief          Aes128Cbc encryption of AdHs content with TcpIp and Tls wraparound
 *  \details        Handles Aes128Cbc encryption of AdHs content when the Tls and
 *                  TcpIp buffer wraps around
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
 *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
 *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
 *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
 *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
 *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
 *  \return        E_OK                 Operation successful
 *  \return        E_NOT_OK             Operation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1
 *********************************************************************************************************************/
 /*! \brief          Aes128Cbc encryption of AdHs content with TLS wraparound before or at TCP wraparound
  *  \details        Handles Aes128Cbc encryption of AdHs content when TLS wraps around before or at TCP wraparound
  *  \param[in]      TlsConIdx           TLS connection index
  *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
  *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
  *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
  *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
  *  \return        E_OK                 Operation successful
  *  \return        E_NOT_OK             Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2
 *********************************************************************************************************************/
 /*! \brief          Aes128Cbc encryption of AdHs content with TLS wraparound after TCP wraparound
  *  \details        Handles Aes128Cbc encryption of AdHs content when TLS wraps around after TCP wraparound
  *  \param[in]      TlsConIdx           TLS connection index
  *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[out]     TcpIpSeg1Ptr        TcpIp first segment buffer
  *                                      CONSTRAINT: TcpIpSeg1Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg1LenPtr     TcpIp first segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg1Ptr
  *  \param[out]     TcpIpSeg2Ptr        TcpIp second segment buffer
  *                                      CONSTRAINT: TcpIpSeg2Ptr != NULL_PTR
  *  \param[in,out]  TcpIpSeg2LenPtr     TcpIp second segment buffer size
  *                                      If E_OK, contains the data size in TcpIpSeg2Ptr
  *  \return        E_OK                 Operation successful
  *  \return        E_NOT_OK             Operation NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound
 *********************************************************************************************************************/
/*! \brief         Copy the Tx data from Tls buffer into destination TcpIp buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Provided destination buffer pointer
 *  \param[in]     CopyCnt            Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt);
/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound
 *********************************************************************************************************************/
/*! \brief         Copy the data from the AD/HS buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Provided destination buffer pointer
 *  \param[in]     CopyCnt            Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyFromTxBufferCcs
 *********************************************************************************************************************/
/*! \brief         Copy the data from the CCS buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Provided destination buffer pointer
 *  \param[in]     CopyCnt            Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferCcs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CopyFromTxBufferAl
 *********************************************************************************************************************/
/*! \brief         Copy the data from the AL buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] BufPtr             Provided destination buffer pointer
 *  \param[in]     CopyCnt            Number of copied bytes
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound
 *********************************************************************************************************************/
/*! \brief         Increment the AD/HS Tx Buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     Value              Length which should be incremented
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_SizeOfTlsBufferTxType Value);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound
 *********************************************************************************************************************/
/*! \brief         Increment the AD/HS Rx Buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     Length             Length which should be incremented
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 Length);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound
 *********************************************************************************************************************/
/*! \brief         Increment the Ul RxIndication index considering wraparound
 *  \details       This function will be called when Ul RxIndication is invoked for newly processed data in
 *                 in TLS Rx AdhHs buffer
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     Length             Length of data in TLS Rx AdHs buffer which has been forwarded to Ul
 *                                    CONSTRAINT: Should not be greater than size of the TLS Rx buffer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 Length);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcScenario1
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 1
 *  \details       Scenario 1: No TcpIp buffer wraparound, valid for application data or alert data
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in]     DataPtr            Data pointer of the first segment
 *  \param[in]     DataLen            Length of the first data segment
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 1
 *  \details       Scenario 1: No TcpIp buffer wraparound, valid for application data or alert data
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        TLS ContentType of this frame
 *  \param[in]     DataPtr            Data pointer of the first segment
 *  \param[in]     DataLen            Length of the first data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs
 *********************************************************************************************************************/
/*! \brief         Decrypt and copy the date to the TLS Rx Buffer in case of AES-128 CBC
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Data pointer of the first segment
 *  \param[in]     DataLen            Length of the first data segment
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs
 *********************************************************************************************************************/
/*! \brief         Decrypt and copy the date to the TLS Rx Buffer in case of AES-128-AEAD
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Data pointer of the first segment
 *  \param[in]     DataLen            Length of the first data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcScenario2
 *********************************************************************************************************************/
 /*! \brief        Handle Decryption with Buffer wraparound Scenario 2
  *  \details      Scenario 2: TcpIp buffer wraparound and no Tls buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2
 *********************************************************************************************************************/
/*! \brief         Handle AEAD Decryption with Buffer wraparound Scenario 2
 *  \details       Scenario 2: TcpIp buffer wraparound and no Tls buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcScenario3
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 3
 *  \details       Scenario 3: TcpIp buffer wraparound and Tls buffer wraparound after TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario3(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 3a
 *  \details       Scenario 3: TcpIp buffer wraparound and Tls buffer wraparound after TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 3b
 *  \details       Scenario 3: TcpIp buffer wraparound and Tls buffer wraparound after TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 3
 *  \details       Scenario 3: TcpIp buffer wraparound and Tls buffer wraparound after TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcScenario4
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 4
 *  \details       Scenario 4: TcpIp buffer wraparound and Tls buffer wraparound before TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario4(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4
 *********************************************************************************************************************/
/*! \brief         Handle Decryption with Buffer wraparound Scenario 4
 *  \details       Scenario 4: TcpIp buffer wraparound and Tls buffer wraparound before TcpIp buffer wraparound
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataSeg1Ptr        Data pointer of the first segment
 *  \param[in]     DataSeg1Len        Length of the first data segment
 *  \param[in]     DataSeg2Ptr        Data pointer of the second segment
 *  \param[in]     DataSeg2Len        Length of the second data segment
 *  \param[in]     AuthDataPtr        Pointer to the Authentication data
 *  \param[in]     AuthTagPtr         Length of the Authentication data
 *  \param[in]     CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl
 *********************************************************************************************************************/
/*! \brief         Decrypt and copy the data to the TLS Rx Buffer AL in case of AES-128 Cbc
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Pointer where the decrypted data is located
 *  \param[in]     DataLen            Length of the Data which should be decrypted
 *  \param[out]    CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl
 *********************************************************************************************************************/
/*! \brief         Decrypt and copy the date to the TLS Rx Buffer AL in case of AES-128-AEAD
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Pointer where the decrypted data is located
 *  \param[in]     DataLen            Length of the Data which should be decrypted
 *  \param[out]    AuthDataPtr        Authentication data buffer
 *  \param[out]    AuthTagPtr         Authentication Tag buffer
 *  \param[out]    CopiedLenPtr       Number of consumed bytes
 *  \return        E_OK               Decryption operation successful
 *  \return        E_NOT_OK           Decryption operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf
 *********************************************************************************************************************/
/*! \brief         Removes and checks the AES padding from the TLS Rx Buffer
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType        ContentType of this frame
 *  \param[in]     CopiedLenPtr       Updated copied length in TLS Rx buffer
 *  \return        E_OK               Padding bytes are valid and have been removed
 *  \return        E_NOT_OK           Padding bytes are not valid
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(uint16)       CopiedLenPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CheckPaddingLen
 *********************************************************************************************************************/
 /*! \brief         Checks it the amount of received padding bytes is not bigger than the whole message
  *  \details       -
  *  \param[in]     TlsConIdx          TLS connection index
  *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[in]     CopiedLenPtr       Updated copied length in TLS Rx buffer
  *  \param[in]     PaddingValue       The value of the padding byte
  *  \return        E_OK               The amount of received padding bytes is valid
  *  \return        E_NOT_OK           The amount of received padding bytes is not valid
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckPaddingLen(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf
 *********************************************************************************************************************/
 /*! \brief         Verifies and removes the padding bytes of the received AD or HS message
  *  \details       -
  *  \param[in]     TlsConIdx          TLS connection index
  *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[in]     CopiedLenPtr       Updated copied length in TLS Rx buffer
  *  \param[in]     PaddingValue       The value of the padding byte
  *  \return        E_OK               Padding bytes are valid and have been removed
  *  \return        E_NOT_OK           Padding bytes are not valid
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf
 *********************************************************************************************************************/
 /*! \brief         Verifies and removes padding bytes of the received AL message
  *  \details       -
  *  \param[in]     TlsConIdx          TLS connection index
  *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \param[in]     CopiedLenPtr       Updated copied length in TLS Rx buffer
  *  \param[in]     PaddingValue       The value of the padding byte
  *  \return        E_OK               Padding bytes are valid and have been removed
  *  \return        E_NOT_OK           Padding bytes are not valid
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyPadding
**********************************************************************************************************************/
/*! \brief         Check that all bytes of the padding have the same value.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     StartPtr           Pointer to the start of the padding
 *  \param[in]     PaddingLen         Length of the padding
 *  \param[in]     ReferenceValue     Reference value for all bytes of the padding
 *  \return        E_OK               Padding removed, all padding bytes are ok
 *  \return        E_NOT_OK           Padding removed, but padding byte check failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyPadding(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) StartPtr,
  uint8 PaddingLen,
  uint8 ReferenceValue);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_SetIvForDecryptCall
 *********************************************************************************************************************/
/*! \brief         Set the initialization vector (IV) for the AES operation
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     DataPtr            Pointer where the IV should be set
 *  \return        E_OK               IV set successful
 *  \return        E_NOT_OK           IV setting was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_SetIvForDecryptCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend
 *********************************************************************************************************************/
/*! \brief         Forwards the validation of the received HMAC to the cipher depended subfunctions
 *  \details       -
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType            ContentType of this frame
 *  \param[in,out] RlAlertDescriptionPtr  Pointer stores the information in case of error during validation
 *  \return        E_OK                   HMAC validation successful
 *  \return        E_NOT_OK               HMAC validation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_VerifyHmacAdHs
 *********************************************************************************************************************/
/*! \brief         Verify the received HMAC in case of a TLS AD or TLS HS data
 *  \details       -
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ContentType            ContentType of this frame
 *  \param[in,out] RlAlertDescriptionPtr  Pointer stores the information in case of error during validation
 *  \return        E_OK                   HMAC validation successful
 *  \return        E_NOT_OK               HMAC validation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_VerifyHmacAl
 *********************************************************************************************************************/
/*! \brief         Verify the received HMAC in case of a TLS AL
 *  \details       -
 *  \param[in]     TlsConIdx              TLS connection index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] RlAlertDescriptionPtr  Pointer stores the information in case of error during validation
 *  \return        E_OK                   HMAC validation successful
 *  \return        E_NOT_OK               HMAC validation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_FinalizeRxBuffer
 *********************************************************************************************************************/
/*! \brief         Forward the finalization of the RX buffer to the cipher depended subfunctions
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType );

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer
 *********************************************************************************************************************/
/*! \brief         Removes the received HMAC from the TLS Rx Buffer in case of TLS AD or TLS HS data
 *  \details       The HMAC should not be forwarded to the upper layer, therefore we can remove it from the buffer
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_FinalizeRxAlBuffer
 *********************************************************************************************************************/
/*! \brief          Removes the received HMAC from the TLS Rx Buffer in case of TLS AL data
 *  \details        The HMAC should not be forwarded to the upper layer, therefore we can remove it from the buffer
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxAlBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend
 **********************************************************************************************************************/
/*! \brief         Forward the calculation of the HMAC to the cipher dependent subfunctions
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               HMAC calculation successful
 *  \return        E_NOT_OK           HMAC calculation NOT successful
 *  \pre           -
 *  \context       TASK
 **********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CalcHmacShaAdHs
 *********************************************************************************************************************/
/*! \brief         Calculates the HMAC in case of SHA ciphersuite and TLS AD or TLS HS data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               HMAC calculation successful
 *  \return        E_NOT_OK           HMAC calculation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_CalcHmacShaAl
 *********************************************************************************************************************/
/*! \brief         Calculates the HMAC in case of SHA ciphersuite and TLS AL data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               HMAC calculation successful
 *  \return        E_NOT_OK           HMAC calculation NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaAl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_CoreRl_HandleErrorWhileTransmit
 *********************************************************************************************************************/
/*! \brief         Handles occurring errors during transmitting of a TLS record layer frame
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ErrorId            Error Id which should be reported
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_HandleErrorWhileTransmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsUserErrorIdType ErrorId);

/**********************************************************************************************************************
 *  TLS CORE BUFFER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_Init
 *********************************************************************************************************************/
/*! \brief         Initialize all TLS RX and TLS TX buffers
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);
/**********************************************************************************************************************
 * TcpIp_TlsCoreBufferStruct_Init
 *********************************************************************************************************************/
/*! \brief         Initialize all TLS BufferStruct.
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBufferStruct_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_Init()
**********************************************************************************************************************/
/*! \brief         Initializes a rx buffer struct.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE for different rx buffer structs, FALSE for same rx buffer struct.
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_Init(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_WriteSegment()
**********************************************************************************************************************/
/*! \brief         Writes segment to rx buffer struct to get a local image of the lower layer segmented TCP buffer.
 *  \details       Supports segments and merging if received data is located directly behind the previously received
 *                 segment (i.e. ring buffer logic).
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     SrcBufPtr            Pointer to linear source buffer.
 *  \param[in]     SrcBufLen            Length of linear source buffer.
 *  \return        E_OK                 Writing to rx buffer struct succeeded.
 *  \return        E_NOT_OK             Writing to rx buffer struct failed.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different rx buffer structs, FALSE for same rx buffer struct.
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_WriteSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) SrcBufPtr,
  uint16 SrcBufLen);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_WriteAdditionalSegment()
**********************************************************************************************************************/
/*! \brief         Writes additional segment to rx buffer struct.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     SrcBufPtr            Pointer to linear source buffer.
 *  \param[in]     SrcBufLen            Length of linear source buffer.
 *  \return        E_OK                 Writing to rx buffer struct succeeded.
 *  \return        E_NOT_OK             Writing to rx buffer struct failed.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different rx buffer structs, FALSE for same rx buffer struct.
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_WriteAdditionalSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) SrcBufPtr,
  uint16 SrcBufLen);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_CalculateNextSegment()
**********************************************************************************************************************/
/*! \brief         Calculates next segment depending on a segment index and level.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     SegmentIndex         Index of segment from which calculation starts.
 *  \param[in]     SegmentLvl           Fill level of rx buffer struct.
 *  \return        NextSegmentIndex     Calculated next index.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfRxBufStructSegType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_CalculateNextSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TcpIp_SizeOfRxBufStructSegType SegmentIndex,
  TcpIp_RxBufStructSegLvlOfRxBufStructMgtType SegmentLvl);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_GetTotLen()
**********************************************************************************************************************/
/*! \brief         Gets length of all segments in rx buffer struct starting at specified offset.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     BufSegOffset         Offset in rx buffer struct considering all segments.
 *  \return        TotalLen             Total length of all segments starting at specified offset.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_GetTotLen(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  uint32 BufSegOffset);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_Copy2Buf()
**********************************************************************************************************************/
/*! \brief         Copies segments of RX buffer struct to a provided buffer.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     BufPtr               Pointer to provided buffer.
 *  \param[in]     BufLen               Length of data to be copied to provided buffer.
 *  \param[in]     BufSegOffset         Offset in RX buffer struct considering all segments.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_Copy2Buf(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint32 BufLen,
  uint32 BufSegOffset);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_GetBufSegIdx()
**********************************************************************************************************************/
/*! \brief           Gets the buffer segment index and segment offset of an rx buffer struct considering a total offset
 *                   of rx buffer struct.
 *  \details         -
 *  \param[in]       TlsBufferMgmtIdx     TLS Buffer management index
 *                                        CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in,out]   OffsetPtr            Pointer to offset considering all segments which is overwritten by segment
 *                                        offset.
 *  \param[out]      BufSegIdxPtr         Pointer to buffer segment index.
 *  \pre             -
 *  \context         TASK
 *  \reentrant       FALSE
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_GetBufSegIdx(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint32) OffsetPtr,
  TCPIP_P2V(TcpIp_SizeOfRxBufStructSegType) BufSegIdxPtr);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxBufStruct_ReleaseSegment()
**********************************************************************************************************************/
/*! \brief         Releases a specified length of rx buffer struct.
 *  \details       -
 *  \param[in]     TlsBufferMgmtIdx     TLS Buffer management index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsBufferMgmt()-1]
 *  \param[in]     Len                  Length of data to be released.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     TRUE
**********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_ReleaseSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  uint32 Len);

/**********************************************************************************************************************
 *  TLS CORE STATES AND EVENTS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreEvent_TcpEventReset
 *********************************************************************************************************************/
/*! \brief         Main state handler for TCP reset events
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventReset(
TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreEvent_TcpEventClosed
 *********************************************************************************************************************/
/*! \brief         Main state handler for TCP closed events
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventClosed(
TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreEvent_TcpEventFinReceived
 *********************************************************************************************************************/
/*! \brief         Main state handler for TCP FIN received events
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventFinReceived(
TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
*  TLS CORE MAIN FUNCTIONS
*********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreState_ModuleHandler
 *********************************************************************************************************************/
/*! \brief         Main state handler for the TLS module
 *  \details       -
 *  \param[in]      TlsConIdx           TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_UserEventHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreState_HandshakeHandler
 *********************************************************************************************************************/
/*! \brief         Main handler for processing the TLS handshake state machine
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_HandshakeHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreState_TcpEventHandler
 *********************************************************************************************************************/
/*! \brief         Main handler for processing the TCP events
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_TcpEventHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_UserErrorHandler
 *********************************************************************************************************************/
/*! \brief         Main handler for processing the TLS User errors
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_UserErrorHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_UserErrorHandler
 *********************************************************************************************************************/
/*! \brief         Main handler for processing the TLS alert handling
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_AlertHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_ApplicationDataHandler
 *********************************************************************************************************************/
/*! \brief         Main handler for processing the TLS application data
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_ApplicationDataHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_CloseRequestedHandler
 *********************************************************************************************************************/
/*! \brief         Main connection state handler for processing the close requests
 *  \details       This processes the close request from TCP
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_TcpCloseRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);


/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_ServerResetRequestedHandler
 *********************************************************************************************************************/
/*! \brief         Main connection state handler for processing the reset requests
 *  \details       This processes the reset request from TCP
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_TcpResetRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_UserResetRequestedHandler
 *********************************************************************************************************************/
/*! \brief         Main connection state handler for processing the UpperLayer reset requests
 *  \details       This processes the reset request from the UpperLayer
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_UserResetRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);
/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_UserCloseRequestedHandler
 *********************************************************************************************************************/
/*! \brief         Main connection state handler for processing the UpperLayer close requests
 *  \details       This processes the close request from the UpperLayer
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_UserCloseRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxRl
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS record layer frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxRl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxCcs
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS CCS frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxHelloRequest
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS HelloRequest frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxHelloRequest(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxHs
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS handshake frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxHs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxAl
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS alert frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxAl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_RxAd
 *********************************************************************************************************************/
/*! \brief         Main function for processing the received TLS application data frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxAd(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_TxHs
 *********************************************************************************************************************/
/*! \brief         Main function for processing the transmittable TLS handshake frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxHs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_TxAl
 *********************************************************************************************************************/
/*! \brief         Main function for processing the transmittable TLS alert frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxAl(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_TxAd
 *********************************************************************************************************************/
/*! \brief         Main function for processing the transmittable TLS application data frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxAd(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreMainFunction_TxCcs
 *********************************************************************************************************************/
/*! \brief         Main function for processing the transmittable TLS CCS frames
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxCcs(
  TcpIp_TlsConnectionIterType TlsConIdx);

/***********************************************************************************************************************
 *  TLS CORE STATE AND EVENT
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  TLS ERROR
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_Init
 *********************************************************************************************************************/
/*! \brief         Initialize the TLS error handling
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
*  TcpIp_TlsCoreError_ClearUserError
*********************************************************************************************************************/
/*! \brief         Clear all reported user errors.
*  \details        -
*  \param[in]      TlsConIdx          TLS connection index
*                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
*********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_ClearUserError(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
*  TcpIp_TlsCoreError_UserErrorCallout
*********************************************************************************************************************/
/*! \brief        Notify Upper layer for the reported User errors that can be read.
*  \details       -
*  \param[in]     TlsConIdx          TLS connection index
*                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
*********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_UserErrorCallout(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE CHANGE PARAMETER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreChangeParameter_ConnectionAssignment
 *********************************************************************************************************************/
/*! \brief         Allocate a TLS connection for the given socket
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     TlsConIdxPtr         Option parameter
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreChangeParameter_ConnectionAssignment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             TlsConIdxPtr);

/**********************************************************************************************************************
 *  TLS CORE CRYPTO
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_PSha256
 **********************************************************************************************************************/
/*! \brief         function generating random value using HMAC with SHA256
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      ResultKeyIdPtr     CSM key where the output data shall be written to
 *  \param[in]      SecretKeyIdPtr     CSM key where the secret is stored
 *  \param[in]      SeedPtr            pointer to seed
 *  \param[in]      seedLen            length of seed
 *  \param[in]      ResultIsPrivate    TRUE: result key is private; FALSE: Result key is public
 *  \return         E_OK     if random could be generated
 *  \return         E_NOT_OK if random could NOT be generated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_PSha256(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) ResultKeyIdPtr,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) SecretKeyIdPtr,
  TCPIP_P2C(uint8) SeedPtr,
  uint16 SeedLen,
  boolean ResultIsPrivate);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcKeyBlock
 **********************************************************************************************************************/
/*! \brief         TLS crypto function to calculate the key block
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK               Key block was calculated successful
 *  \return        E_NOT_OK           Key block could NOT be calculated successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcKeyBlock(
  TcpIp_TlsConnectionIterType TlsConIdx);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_GenerateIvRandomValue
 **********************************************************************************************************************/
/*! \brief         TLS crypto function to generate the AES IV random value
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     IvPtr              Pointer to the IV
 *  \param[in]     IvLen              Length of the IV
 *  \return        E_OK               Random IV generation successful
 *  \return        E_NOT_OK           Random IV could NOT be generated successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_GenerateIvRandomValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) IvPtr,
  CONST(uint8, AUTOMATIC) IvLen);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_SetAesIvValue
 **********************************************************************************************************************/
/*! \brief         TLS crypto function to set the AES IV random value
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     IvKeyElementId     ElementId which should be set
 *  \param[in]     IvPtr              Pointer to the IV
 *  \param[in]     IvLen              Length of the IV
 *  \return        E_OK               IV was set successful
 *  \return        E_NOT_OK           IV could NOT be set successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_SetIvValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) IvKeyElementId,
  TCPIP_P2C(uint8) IvPtr,
  CONST(uint8, AUTOMATIC) IvLen);

/**********************************************************************************************************************
 *  TLS ALERT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreAlert_Init
 *********************************************************************************************************************/
/*! \brief         Initialization function for the TLS alert handling
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreAlert_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE LOWER LAYER (LL)
 *********************************************************************************************************************/

# define TCPIP_STOP_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define TCPIP_START_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TLS CORE UPPER LAYER (UL)
 *********************************************************************************************************************/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_TcpAccepted
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
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_TcpAccepted(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType         socketIdx             = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx     = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);
  TcpIp_SocketTcpDynIterType      socketTcpIdx          = TCPIP_SOCKET_IDX_TO_TCP_IDX(
    TcpIp_GetSocketDynListenIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_SocketTcpDynIterType      socketTcpIdxConnected = TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx);
  TCPIP_P2V(TcpIp_SockAddrType)   remoteSockAddrPtr     = &TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->TcpIpSockAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward call to TcpIp */
  TcpIp_Tcp_TlsAccepted(socketOwnerCfgIdx, socketTcpIdx, socketTcpIdxConnected, remoteSockAddrPtr);

} /* TcpIp_TlsCoreUl_TcpAccepted() */
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_TcpConnected
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_TcpConnected(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward call to TcpIp */
  TcpIp_Tcp_TlsConnected(socketIdx);

} /* TcpIp_TlsCoreUl_TcpConnected() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_RxIndication(
  TcpIp_TlsConnectionIterType       TlsConIdx,
  TCPIP_P2V(uint8)                  DataPtr,
  uint32                            DataLenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /*
     When this function is called, there is some new unforwarded data in TLS Rx AdHs buffer
           TLS Rx AdHs buffer
        [     xxxxxx*****      ]
              r     u    w

     Unforwarded data = (w -u)
     Data previously forwarded = (u - r)

     After function call, all new data in TLS Rx AdHs buffer has been forwarded
           TLS Rx AdHs buffer
        [     xxxxxxxxxxx      ]
              r         w
                        u
  */
  /* #10 Check if the number of bytes to be forwarded to Ul is smaller than the maximum RX-Indication length */
  if (DataLenByte <= TCPIP_RX_INDICATION_LEN_MAX)
  {
    /*#20 if so, forward the indication to UL (Socket owner) */
    TcpIp_RxIndicationFunctions(socketIdx, TcpIp_GetAddrRemSockOfSocketDyn(socketIdx), DataPtr, (uint16)DataLenByte);
    /* Increment the UlRxIndicationPos with the data that was forwarded */
    TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound(TlsConIdx, DataLenByte);
  }
  else
  {
    /* #30 otherwise, split the indication into multiple parts and forward the indication to UL (Socket owner) */
    uint16 rxConfLen;
    uint32 remainingRxConfLen = DataLenByte;
    /* Iterate over all given data */
    while (remainingRxConfLen > 0u)
    {
      if (remainingRxConfLen > TCPIP_RX_INDICATION_LEN_MAX)
      {
        rxConfLen = (uint16)TCPIP_RX_INDICATION_LEN_MAX;
      }
      else
      {
        rxConfLen = (uint16)remainingRxConfLen;
      }
      /* Forward indication to UL */
      TcpIp_RxIndicationFunctions(socketIdx, TcpIp_GetAddrRemSockOfSocketDyn(socketIdx), DataPtr, rxConfLen);

      /* Update the Ul RxIndication index with the rxConfLen */
      TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound(TlsConIdx, rxConfLen);

      /* #40 subtract the already confirmed data */
      remainingRxConfLen -= rxConfLen;
    } /* while */
  }
} /* TcpIp_TlsCoreUl_RxIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_Transmit
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_Transmit(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length,
  boolean                   ForceRetrieve)
{
/*
 * Concept:
 * The main usecase here is the application data, which should be transmitted. Therefore the user (socketOwner) can call
 * TcpIp_TcpTransmit either with a direct dataPtr, or with an NULL Ptr, so that the TcpIp calls the users configured
 * CopyTxData. In both ways, the Tls takes care of the wraparound in the TlsBufferTx. The transmission of the data will
 * then take place within the next main function of the Tls ( via TcpIp_TlsCoreMainFunction_TxAd()).
 */

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  Std_ReturnType retVal = E_NOT_OK;
  uint32 dynLength = Length;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the corresponding TLS-Connection index for this socket */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
    /* #20 Check if there is a TLS connection already established */
    if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
    {
      TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(tlsConIdx);
      /* Remaining space available in TLS Tx AdHs buffer */
      TcpIp_SizeOfTlsBufferTxType remainingSpaceInAdHsBuffer = (TcpIp_GetTlsBufferTxAdHsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx)
                                                                - TcpIp_GetAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

      /* #30 Enter critical section */
      TCPIP_VENTER_CRITICAL_SECTION();

# ifdef COMMENT_VECTOR  /* ESCAN00110353 - next check, impl version 15.06.00 */
# endif

      /* #40 Reduce datalength when not enough buffer is available and retrieve is not forced */
      /* Return E_NOT_OK when buffer is completely filled */
      if ((ForceRetrieve == FALSE)
        && (DataPtr == NULL_PTR)
        && (dynLength > remainingSpaceInAdHsBuffer)
        && (remainingSpaceInAdHsBuffer > 0u))
      {
        dynLength = remainingSpaceInAdHsBuffer;
      }

      /* #50 Check if we can accept the transmit request */
      if (   (dynLength <= remainingSpaceInAdHsBuffer)
          && (remainingSpaceInAdHsBuffer != 0u))
      {
        /* #60 Forward the data (direct/indirect) to CopyTxFunctions */
        if (DataPtr != NULL_PTR)
        {
          /* Forward the call to direct data provision function */
          TcpIp_TlsCoreUl_CopyTxDataDirect(tlsConIdx, DataPtr, dynLength);
          retVal = E_OK;
        }
        else
        {
          /* Forward the call to indirect data provision function */
          retVal = TcpIp_TlsCoreUl_CopyTxDataIndirect(tlsConIdx, dynLength, SocketIdx);
        }
      }
      else if ((remainingSpaceInAdHsBuffer == 0u) && (ForceRetrieve == FALSE))
      {
        /* if no Buffer is available the call was ok, but no data shall be copied. */
        retVal = E_OK;
      }
      else
      {
        /* Nothing to do */
      }

      /* #70 Leave critical section */
      TCPIP_VLEAVE_CRITICAL_SECTION();
    }
  }
  return retVal;
} /* TcpIp_TlsCoreUl_Transmit() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataDirect
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataDirect(
    TcpIp_TlsConnectionIterType TlsConIdx,
    TCPIP_P2C(uint8)            SourceDataPtr,
    CONST(uint32, AUTOMATIC)    SourceDataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType txBufferWriteIdx =
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsReadIdxOfTlsBufferMgmtDynType txBufferReadIdx =
    TcpIp_GetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the limitation of the call is the EndIdx or the ReadIdx */
  if (txBufferReadIdx <= txBufferWriteIdx)
  {
    /* #20 We can copy the data until the EndIdx. Check if we have to consider a wraparound of the TxBuffer */
    if ((txBufferWriteIdx + SourceDataLen) <= txBufferEndIdx)
    {
      TCPIP_P2V(uint8) txBufferDstPtr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
      /* #30 Data fits linearized into TxBuffer - 1 copy call */
      /* Before:
       *  W               W            W               W
       * [-------] or [-------] or [xxx----] or [---xxx-]
       *  R               R         R               R
       *
       * After:
       *      W              W            W      W
       * [****---] or [---***-] or [xxx***-] or [---xxx*]
       *  R               R         R               R
       */

      /* Since the data fits complete into the buffer, the range of the copy is the WriteIdx until DataLength. */
      VStdLib_MemCpy(txBufferDstPtr, SourceDataPtr, SourceDataLen);                                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    }
    else
    {
      TcpIp_SizeOfTlsBufferTxType remainingLenAtEnd;
      TcpIp_SizeOfTlsBufferTxType remainingLenAtStart;
      TCPIP_P2V(uint8) txBufferDstPtr;
      TCPIP_P2C(uint8) remainingSourceDataPtr;
      /* #40 Wraparound of TxBuffer - 2 copy calls */
      /* Before:
       *      W              W
       * [-------] or [---xxx-]
       *      R           R
       *
       * After:
       *    W            W
       * [**--***] or [**-xxx*]
       *      R           R
       */

      /* Since the data does not fit completely into the buffer behind the WriteIdx, we have to split the copy calls. */
      /* First call range is WriteIdx until EndIdx (Fill this part of the buffer completely) */
      txBufferDstPtr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
      remainingLenAtEnd = (txBufferEndIdx - txBufferWriteIdx);

      VStdLib_MemCpy(txBufferDstPtr, SourceDataPtr, remainingLenAtEnd);                                                 /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Second call range is StartIdx until remainingLenAtStart */
      txBufferDstPtr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
      remainingLenAtStart = ((TcpIp_SizeOfTlsBufferTxType)SourceDataLen - remainingLenAtEnd);
      remainingSourceDataPtr = &SourceDataPtr[remainingLenAtEnd];

      VStdLib_MemCpy(txBufferDstPtr, remainingSourceDataPtr, remainingLenAtStart);                                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    }
  }
  else /* txBufferReadIdx > txBufferWriteIdx */
  {
    /* #50 We can copy the data until the ReadIdx. No wraparound possible */
    TCPIP_P2V(uint8) txBufferDstPtr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
    /* No wraparound possible - linearized call until read index
     * Before:
     *  W              W
     * [----xxx] or [xx---xx]
     *      R             R
     *
     * After:
     *     W             W
     * [***-xxx] or [xx**-xx]
     *      R             R
     */

    /* Since the data fits completely into the buffer, the range of the copy is the WriteIdx to WriteIdx + DataLength. */
    VStdLib_MemCpy(txBufferDstPtr, SourceDataPtr, SourceDataLen);                                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }

  /* #60 Adjust the WriteIdx. This function will wraparound the WriteIdx if necessary. */
  TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound(TlsConIdx, (TcpIp_SizeOfTlsBufferTxType)SourceDataLen);

} /* TcpIp_TlsCoreUl_CopyTxDataDirect() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataIndirect
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataIndirect(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      SourceDataLen,
  TcpIp_SizeOfSocketDynType   SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType txBufferWriteIdx =
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsReadIdxOfTlsBufferMgmtDynType txBufferReadIdx =
    TcpIp_GetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Pointer to TLS segment 1 */
  TCPIP_P2V(uint8) tlsSeg1Ptr;
  /* Length of TLS segment 1 */
  uint32 tlsSeg1Len;
  /* Pointer to TLS segment 2 */
  TCPIP_P2V(uint8) tlsSeg2Ptr;
  /* Length of TLS segment 2 */
  uint32 tlsSeg2Len;

  TcpIp_SizeOfSocketTcpDynType  socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  if (txBufferReadIdx <= txBufferWriteIdx)
  {
    /* #10 Check if new data will cause TLS Tx buffer wraparound */
    if ((txBufferWriteIdx + SourceDataLen) <= txBufferEndIdx)
    {
      /* Data can be entirely copied into TLS segment 1 */
      tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
      tlsSeg1Len = SourceDataLen;
      /* No need for TLS segment 2 */
      tlsSeg2Ptr = NULL_PTR;
      tlsSeg2Len = 0;
      /* #20 Data fits linearized into TLS segment 1 - 1 copy call */
      /* Before:
       *  W               W            W               W
       * [-------] or [-------] or [xxx----] or [---xxx-]
       *  R               R         R               R
       *
       * After:
       *      W              W            W      W
       * [****---] or [---***-] or [xxx***-] or [---xxx*]
       *  R               R         R               R
       */

      /* Forward the call to the internal copy function */
      retVal = TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound(socketTcpIdx, tlsSeg1Ptr,
        &tlsSeg1Len, tlsSeg2Ptr, &tlsSeg2Len, FALSE);
    }
    else
    {
      /* #30 Wraparound of TxBuffer - 2 copy calls */
      /* Before:
       *      W              W
       * [-------] or [---xxx-]
       *      R           R
       *
       * After
       *    W            W
       * [**--***] or [**-xxx*]
       *      R           R
       */

      /* Ciphertext will be be copied to both TLS segment 1 and 2 */
      tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
      tlsSeg1Len = ((uint32)txBufferEndIdx - txBufferWriteIdx);

      /* Second call range is StartIdx until remaining data */
      tlsSeg2Len = ((TcpIp_SizeOfTlsBufferTxType)SourceDataLen - tlsSeg1Len);
      tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);;

      /* Forward the call to the internal copy function */
      retVal = TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound(socketTcpIdx, tlsSeg1Ptr,
        &tlsSeg1Len, tlsSeg2Ptr, &tlsSeg2Len, FALSE);
    }
  }
  else /* txBufferReadIdx > txBufferWriteIdx */
  {
    /* #40 Data fits linearized into TLS segment 1 - 1 copy call */
    tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(txBufferWriteIdx);
    tlsSeg1Len = SourceDataLen;
    tlsSeg2Ptr = NULL_PTR;
    tlsSeg2Len = 0;
    /* No wraparound possible - linearized call until read index
     * Before:
     *  W              W
     * [----xxx] or [xx---xx]
     *      R             R
     *
     * After
     *     W             W
     * [***-xxx] or [xx**-xx]
     *      R             R
     */

     /* Forward the call to the internal copy function */
    retVal = TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound(socketTcpIdx, tlsSeg1Ptr,
      &tlsSeg1Len, tlsSeg2Ptr, &tlsSeg2Len, FALSE);
  }

  /* #50 Adjust the WriteIdx. This function will wraparound the WriteIdx */
  if (retVal == E_OK)
  {
    TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound(TlsConIdx,
      (TcpIp_SizeOfTlsBufferTxType)(tlsSeg1Len + tlsSeg2Len));
  }

  return retVal;

} /* TcpIp_TlsCoreUl_CopyTxDataIndirect() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound()
 *********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* PRQA S 6060, 6080 1 */ /* MD_TcpIp_Tls_STPAR, MD_MSR_STMIF */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_CopyTxDataIndirectWithWraparound(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8)             DstChunk1Ptr,
  TCPIP_P2V(uint32)            DstChunk1LenPtr,
  TCPIP_P2V(uint8)             DstChunk2Ptr,
  TCPIP_P2V(uint32)            DstChunk2LenPtr,
  CONST(boolean, AUTOMATIC)    UseTlsCopyTxData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType            retVal       = E_NOT_OK;
  uint16                    dstChunk1Len = (uint16)*DstChunk1LenPtr;
  uint16                    dstChunk2Len = (uint16)*DstChunk2LenPtr;
  TcpIp_SizeOfSocketDynType socketIdx    = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
  uint16                    copyLen;

  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  /* ----- Implementation ----------------------------------------------- */
  copyLen = dstChunk1Len;

  /* #10 Copy first chunk of data at the end of buffer. */
  if (TcpIp_CopyTxDataFunctions(socketIdx, DstChunk1Ptr, &copyLen, UseTlsCopyTxData) == BUFREQ_OK)
  {
    /* #20 Update *LengthPtr if user provided less data. */
    if (copyLen < dstChunk1Len)
    {
      /* user provided less data than requested.
      -> data provision complete. */
      *DstChunk1LenPtr = copyLen;
      *DstChunk2LenPtr = 0u;
      retVal = E_OK;
    }
    else if (copyLen > dstChunk1Len)
    {
      /* user provided more data than requested. */
      retVal = E_NOT_OK;
    }
    /* #30 Copy second chunk at the beginning of buffer, if required. */
    else if (dstChunk2Len != 0u)
    {
      copyLen = dstChunk2Len;

      if (TcpIp_CopyTxDataFunctions(socketIdx, DstChunk2Ptr, &copyLen, UseTlsCopyTxData) == BUFREQ_OK)
      {
        if (copyLen <= dstChunk2Len)
        {
          /* #40 Update *DstChunk2LenPtr depending on bytes copied */
          *DstChunk2LenPtr = copyLen;
          retVal = E_OK;
        }
        else
        {
          /* user provided more data than requested */
          retVal = E_NOT_OK;
        }
      }
      /* else: user aborted transmit */
    }
    else
    {
      /* all data was provided in a single chunk. */
      *DstChunk2LenPtr = 0u;
      retVal = E_OK;
    }
  }
  /* else: user aborted transmit */

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_SizeOfTlsBufferTxType Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType txBufferWriteIdx =
    TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Adjust the AdHs Write index under consideration of wraparound at the end of the TxBuffer */
  if ((txBufferWriteIdx + Value) < txBufferEndIdx)
  {
    /* New Write index fits into the TxBuffer - Add the value */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, Value);
  }
  else if ((txBufferWriteIdx + Value) == txBufferEndIdx)
  {
    /* New Write index is exactly at the end of the buffer - Wraparound and set it to the start index */
    TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, txBufferStartIdx);
  }
  else /* (txBufferWriteIdx + Value) > txBufferEndIdx) */
  {
    /* New Write index must wraparound - calculate the new index at the start of the buffer */
    TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType remainingLenAtEnd = (txBufferEndIdx - txBufferWriteIdx);
    TcpIp_TlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDynType remainingLenAtBeginning = (Value - remainingLenAtEnd);
    /* Wraparound TLS Tx writeIdx */
    TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
                                                     TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    /* Increment Tx writeIdx by the remaining length */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, remainingLenAtBeginning);
  }

  /* #20 Adjust the Application data fill level by adding the copied bytes */
  TcpIp_AddAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, Value);

} /* TcpIp_TlsCoreUl_IncrementTlsBufferTxAdHsWriteIdxWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUl_Received
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_Received(
  TcpIp_SocketDynIterType    SocketIdx,
  uint32                     DataLenByte,
  TCPIP_P2V(uint8)           ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  uint8 errorId = TCPIP_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select the Tls connection of the socket, and update the Tls Ul read index if connection is established */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
    if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
    {
      TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(tlsConIdx);

      /* Check if the data length read by Ul fits the Tls buffer size */
      if (DataLenByte < TcpIp_GetTlsBufferRxAdHsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx))
      {
        /* Plaintext in the TLS Rx AdHs buffer has been read by UL, readIdx can be incremented with bytes consumed */
        TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound(tlsConIdx, DataLenByte);

        /* #20 Decrement the TLS Rx AdHs buffer fill level with the length consumed */
        if (TcpIp_GetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) > DataLenByte)
        {
          /* Decrement the Rx AdHs fill level since data has been consumed */
          TcpIp_SubAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_SizeOfTlsBufferTxType)DataLenByte);
        }
        else
        {
          /* Set Rx AdHs fill level to 0 since Ul has read more data that available */
          TcpIp_SetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
        }
      }
      else
      {
        /* otherwise, invalid function call */
        errorId = TCPIP_E_INV_ARG;
      }
    }
    else
    {
      /* otherwise, invalid function call */
      errorId = TCPIP_E_INV_ARG;
    }
  }

  /* Set the errorId */
  *ErrorIdPtr = errorId;
} /* TcpIp_TlsCoreUl_Received() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Connections and initialize the submodules */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    TcpIp_TlsCoreBufferStruct_Init(tlsConIdx);

    TcpIp_TlsCoreBuffer_Init(tlsConIdx);

    TcpIp_TlsCoreError_Init(tlsConIdx);

    TcpIp_TlsCoreAlert_Init(tlsConIdx);

    TcpIp_TlsCoreRl_Init(tlsConIdx);

    TcpIp_TlsCoreRxIndication_Init(tlsConIdx);

    TcpIp_TlsCoreCipher_Init(tlsConIdx);

    TcpIp_TlsCoreConnection_Init(tlsConIdx);

    TcpIp_TlsCore_InitAsnycFlags(tlsConIdx);

    TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx, TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN);
  }

  /* #20 Iterate over all configured CipherWorker and initialize the variable to the default values */
  for (tlsCipherWorkerIdx = 0; tlsCipherWorkerIdx < TcpIp_GetSizeOfTlsCipherWorker(); tlsCipherWorkerIdx++)
  {
    TcpIp_SetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(tlsCipherWorkerIdx,
      TCPIP_NO_TLSHANDSHAKEACTIVEIDXOFTLSCIPHERWORKERDYN);
  }

/*
[REVIEW_G] accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  /* #30 Initialize the global TLS-Listener */
  TcpIp_TlsListener_Init();
# endif

} /* TcpIp_TlsCore_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_InitAsnycFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_InitAsnycFlags(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the async context flags with the default values */
  TcpIp_SetDhPubKeyAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetDhSharedSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetPskPremasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
} /* TcpIp_TlsCore_InitAsnycFlags() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxIndication_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxIndication_Init(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize RX-Indication flags */
  TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetCcsRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetAlRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetAdRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx, 0u);

} /* TcpIp_TlsCoreRxIndication_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCipher_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCipher_Init(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize RX and TX ciphers selection */
  TcpIp_SetActiveCipherRxOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_NULL_WITH_NULL_NULL);
  TcpIp_SetActiveCipherTxOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_NULL_WITH_NULL_NULL);
  TcpIp_SetCcsReceivableOfTlsConnectionDyn(TlsConIdx, FALSE);

} /* TcpIp_TlsCoreCipher_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConnection_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConnection_Init(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize TLS-Connection variables */
  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_NO_ASYNC);

  /* Initialize the Listen Socket and mark TLS-Connection as unused */
  TcpIp_SetSocketDynListenIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNLISTENIDXOFTLSCONNECTIONDYN);
  TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN);
  TcpIp_SetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFTLSCONNECTIONDYN);

  /* Initialize the KeyBlock size information */
  TcpIp_SetKeyBlockSizeOfTlsConnectionDyn(TlsConIdx, 0);
  TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_INIT);

  /* Reset the Tls connection state variable */
  TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE);

  /* Reset the handshake sate machine TX trigger variable */
  TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

  /* Initialize the AES-128-CBC padding value */
  TcpIp_SetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx, 0u);

} /* TcpIp_TlsCoreConnection_Init() */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCore_RemoveLoadedCerts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_RemoveLoadedCerts(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCertValidationStatusDynIterType certStatusIdx;
  TcpIp_CertDataType dummyCert;
  uint8 zeroCert = 0u;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx) <= TcpIp_GetTlsCertValidationStatusDynEndIdxOfTlsConnection(TlsConIdx));

  /* Create a zero data cert */
  dummyCert.certData = &zeroCert;
  dummyCert.certDataLength = 0;

  /* #10 Clear all loaded certificates by loading zero data */
  for (certStatusIdx = TcpIp_GetTlsCertValidationStatusDynStartIdxOfTlsConnection(TlsConIdx); certStatusIdx < TcpIp_GetTlsCertValidationStatusDynValidEndIdxOfTlsConnectionDyn(TlsConIdx); certStatusIdx++)
  {
    (void)KeyM_SetCertificate(TcpIp_GetAddrTlsCertValidationStatusDyn(certStatusIdx)->CertId, (KeyM_CertDataType *)&dummyCert); /* PRQA S 0310 */ /* MD_TCPIP_Rule11.3_0310_3305_TcpIp_CertDataType */
  }
} /* TcpIp_TlsCore_RemoveLoadedCerts() */
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_ResetConnection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCore_ResetConnection(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset Connection variables depending on mode of this TLS-Connection */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
  {
    /* Mode == TCPIP_TLS_SERVER */
    TcpIp_TlsServer_ResetConnection(TlsConIdx);
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    /* Remove all loaded server certificates */
    TcpIp_TlsCore_RemoveLoadedCerts(TlsConIdx);
#  endif

    TcpIp_TlsClient_ResetConnection(TlsConIdx);
  }
# endif

  TcpIp_TlsCore_ResetConnectionVariables(TlsConIdx);
} /* TcpIp_TlsCore_ResetConnection() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_ResetConnectionVariables
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCore_ResetConnectionVariables(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the Tls core connection variables */
  TcpIp_TlsCoreBuffer_Init(TlsConIdx);

  TcpIp_TlsCoreBufferStruct_Init(TlsConIdx);

  TcpIp_TlsCoreAlert_Init(TlsConIdx);

  TcpIp_TlsCoreRl_Init(TlsConIdx);

  TcpIp_TlsCoreRxIndication_Init(TlsConIdx);

  TcpIp_TlsCoreCipher_Init(TlsConIdx);

  TcpIp_TlsCoreConnection_Init(TlsConIdx);

# if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
  TcpIp_TlsCoreMsa_ClearMasterSecretBuffer(TlsConIdx);
# endif

} /* TcpIp_TlsCore_ResetConnectionVariables() */

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TLS LISTENER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsListener_Init
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsListener_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsListenerIterType tlsListenerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Listener and initialize their values */
  for (tlsListenerIdx = 0; tlsListenerIdx < TcpIp_GetSizeOfTlsListener(); tlsListenerIdx++)
  {
    TcpIp_TlsListener_ResetListener(tlsListenerIdx);
  }
} /* TcpIp_TlsListener_Init() */

/**********************************************************************************************************************
*  TcpIp_TlsListener_ResetListener
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
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsListener_ResetListener(TcpIp_TlsListenerIterType TlsListener)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset TLS-Listener values */
  TcpIp_SetSocketDynIdxOfTlsListener(TlsListener, TCPIP_NO_SOCKETDYNIDXOFTLSLISTENER);
  TcpIp_SetPortOfTlsListener(TlsListener, TCPIP_PORT_ANY);

} /* TcpIp_TlsListener_ResetListener() */

/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetNextFreeListenerIndex
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsListener_GetNextFreeListenerIndex(
  TCPIP_P2V(TcpIp_TlsListenerIterType) TlsListenerPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsListenerIterType tlsListenerIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Listeners */
  for (tlsListenerIdx = 0; tlsListenerIdx < TcpIp_GetSizeOfTlsListener(); tlsListenerIdx++)
  {
    /* #20 Check if this TLS-Listener entry is free and return the index */
    if (TcpIp_GetSocketDynIdxOfTlsListener(tlsListenerIdx) == TCPIP_NO_SOCKETDYNIDXOFTLSLISTENER)
    {
      /* If so, save the index in the out parameter */
      *TlsListenerPtr = tlsListenerIdx;

      /* Set the return value to true */
      retVal = E_OK;

      /* And exit the loop */
      break;
    }
  }
  return retVal;
} /* TcpIp_TlsListener_GetNextFreeListenerIndex() */

/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx(
  TcpIp_SocketDynIterType              SocketIdx,
  TCPIP_P2V(TcpIp_TlsListenerIterType) TlsListenerPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsListenerIterType tlsListenerIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Listeners and search for matching TLS-Listener with given socket index */
  for (tlsListenerIdx = 0; tlsListenerIdx < TcpIp_GetSizeOfTlsListener(); tlsListenerIdx++)
  {
    /* Check if the given socket index match */
    if (TcpIp_GetSocketDynIdxOfTlsListener(tlsListenerIdx) == SocketIdx)
     {
      /* Return TLS-Listener instance */
      *TlsListenerPtr = tlsListenerIdx;
      retVal = E_OK;
      /* Exit the loop */
      break;
     }
  }
  return retVal;
} /* TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx() */
# endif /* TCPIP_SUPPORT_ASRTLSSERVER */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCore_GetNextFreeTlsClientConnection
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCore_GetNextFreeTlsClientConnection(
  TcpIp_SizeOfSocketDynType SocketIdx,
  uint16 RemotePort,
  TCPIP_P2V(TcpIp_TlsConnectionIterType)    TlsConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Iterate over all configured TLS-Connections */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Check if connection is configured as TLS-Client */
    if (TcpIp_GetModeOfTlsConnection(tlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* #30 Check if the remote port matches the configured port and return the next free TLS-Client Connection */
      if (RemotePort == TcpIp_GetPortOfTlsConnection(tlsConIdx))
      {
        /* Check if a socket is already connected on this connection */
        if (TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx) == TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN)
        {
          *TlsConIdxPtr = tlsConIdx;
          TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx, SocketIdx);
          TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_ALLOCATED);
          retVal = E_OK;
          /* Exit loop */
          break;
        }
      }
    }
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();

  return retVal;
} /* TcpIp_TlsCore_GetNextFreeTlsClientConnection() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort
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
FUNC(TcpIp_TlsConnectionIterType, TCPIP_CODE) TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort(
  CONST(uint16, AUTOMATIC) UsedPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections to find the first free TLS connection. */
  for (tlsConIdx = 0u; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Look for the TLS-Connection which is configured to use this port and is not in use. */
    if (TcpIp_GetPortOfTlsConnection(tlsConIdx) == UsedPort)
    {
      /* Check if the TLS-Connection is already in use */
      if (TcpIp_GetSocketDynListenIdxOfTlsConnectionDyn(tlsConIdx) != TCPIP_NO_SOCKETDYNLISTENIDXOFTLSCONNECTIONDYN)
      {
        /* This connection already is in use. */
      }
      else
      {
        /* #30 The TLS connection is not in use - return the current index and leave the for loop. */
        break;
      }
    }
  }

  return tlsConIdx;
} /* TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort() */

/**********************************************************************************************************************
 *  TcpIp_TlsListener_Close
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
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
FUNC(void, TCPIP_CODE) TcpIp_TlsListener_Close(
  TcpIp_SocketDynIterType SocketIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
  TcpIp_TlsListenerIterType tlsListener;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Identify the corresponding TLS-Listener by the given socket index */
  if (TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx(SocketIdx, &tlsListener) == E_OK)
  {
    /* #20 Forward the call to the specific TLS-Connection */
    TcpIp_TlsListener_ForwardCloseToTlsConnection(tlsListener, Abort);

    /* #30 Mark the TLS-Listener as unused */
    TcpIp_TlsListener_ResetListener(tlsListener);

    /* #40 Forward the close to the underlaying TCP socket */
    TcpIp_CloseTcpSocketFromTls(socketTcpIdx, Abort);
  }
  /* else - This can not happen. If there is a listen socket, then there must be a TlsListener */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: Rework comment.The word "could" is confusing here. Make clear that it is already checked that this is a listener socket, so there must be a listener. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
} /* TcpIp_TlsListener_Close() */


/**********************************************************************************************************************
 *  TcpIp_TlsListener_ForwardCloseToTlsConnection
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
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsListener_ForwardCloseToTlsConnection(
  TcpIp_TlsListenerIterType TlsListener,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  TcpIp_SocketDynIdxOfTlsListenerType tlsListenerListenSocket = TcpIp_GetSocketDynIdxOfTlsListener(TlsListener);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Connections */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    TcpIp_TlsConnectionState tlsConConnectionState = TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx);

    /* #20 Check if there is an active handshake ongoing on this specific TLS-Connection */
    if (tlsConConnectionState == TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE)
    {
       TcpIp_SocketDynListenIdxOfTlsConnectionDynType tlsConListenSocket
         = TcpIp_GetSocketDynListenIdxOfTlsConnectionDyn(tlsConIdx);

       /* #30 Check if this TLS-Connection is owned by the given TLS Listener and forward the close request to all ongoing TLS handshakes */
       if ((tlsConListenSocket == tlsListenerListenSocket))
       {
         /* Forward the close request for the ongoing TLS handshakes.
            Actual closing is done in main function context by TcpIp_TlsCoreConState_UserResetRequestedHandler */
         if (Abort == TRUE)
         {
           /* Immediately terminate the ongoing TLS handshakes by sending RST */
           TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CANCLED);
         }
         else
         {
           /* Gracefully terminate the ongoing TLS handshakes by sending FIN */
           TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CLOSED);
         }

         break;
       }
    }
  }
} /* TcpIp_TlsListener_ForwardCloseToTlsConnection() */
# endif /* TCPIP_SUPPORT_ASRTLSSERVER == STD_ON */

/**********************************************************************************************************************
 *  TcpIp_SocketIdxToTlsConIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SocketIdxToTlsConIdx(
  TcpIp_SocketDynIterType                SocketIdx,
  TCPIP_P2V(TcpIp_TlsConnectionIterType) TlsConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Connections and return the matching TLS-Connections to the given socket index */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* Search for the matching socket index */
    if (TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx) == SocketIdx)
    {
      /* If found, return the corresponding TLS-Connection index */
      *TlsConIdxPtr = tlsConIdx;

      retVal = E_OK;

      /* Exit the loop */
      break;
    }
  }

  return retVal;
} /* TcpIp_SocketIdxToTlsConIdx() */


/**********************************************************************************************************************
 *  TcpIp_TlsCore_ChangeParameter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCore_ChangeParameter(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward the change parameter request to the corresponding functions depending on the given OptName */
  switch (OptName)
  {
    case TCPIP_PARAMID_TLS_CONNECTION_ASSIGNMENT:
    {
      retVal = TcpIp_TlsCoreChangeParameter_ConnectionAssignment(SocketTcpIdx, OptValPtr);
      break;
    }
    default:                                                                                                              /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    {
      /* Default case left blank intentionally - Check is performed in caller function */
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsCore_ChangeParameter() */

/**********************************************************************************************************************
 *  TLS CORE CHANGE PARAMETER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreChangeParameter_ConnectionAssignment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreChangeParameter_ConnectionAssignment(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2C(uint8)             TlsConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
  /* AUTOSAR missed to specify (SWS_TcpIp) the type used for the TLS connection ID. We define it as uint16. */
  TcpIp_TlsConnectionDynIterType tlsConIdx = (TcpIp_TlsConnectionDynIterType)TCPIP_GET_UINT16_RAW(TlsConIdxPtr, 0u);

  /* #10 Allocate a TLS connection for the socket if possible (TlsConIdx exists, Tls connection not yet in use, ...) */
  if (TcpIp_Tls_AllocateConnection(socketIdx, tlsConIdx) == E_OK)
  {
    TcpIp_SetUseTlsOfSocketTcpDyn(SocketTcpIdx, TRUE);
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreChangeParameter_ConnectionAssignment() */

/**********************************************************************************************************************
 *  TLS CORE CONTENT TYPE (CT)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtHs_RxIndication(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Handshake RX-Indication */
  TcpIp_IncHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx);
} /* TcpIp_TlsCoreCtHs_RxIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_VerifyMsgCompleteness
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_VerifyMsgCompleteness(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) HsMsgLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAdHsWriteIdx
    = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxAdHsReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxAdHsStartIdx
    = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDynType currentHsEndIdx
    = TcpIp_GetTlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType currentMsgLenInBuffer = (rxAdHsWriteIdx - rxAdHsReadIdx);

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that we received at least 4 Bytes to peek the length of the received message */
  if (currentMsgLenInBuffer >= (TCPIP_TLS_HSLEN_LEN + TCPIP_TLS_CONTENT_LENGTH_OFFSET))
  {
    /* #20 Process the message if it is the first received message OR the processing of the last received message is done */
    if ((rxAdHsReadIdx == rxAdHsStartIdx) || (rxAdHsReadIdx == currentHsEndIdx))
    {
      /* Read the actual message size from the received HS message */
      retVal = TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg(TlsConIdx, HsMsgLenPtr);
    }
    /* else - nothing to do - leave retVal E_NOT_OK */
  }
  /* else - nothing to do - leave retVal E_NOT_OK */
  return retVal;
} /* TcpIp_TlsCoreCtHs_VerifyMsgCompleteness() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32) HsMsgLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAdHsWriteIdx
    = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxAdHsReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType currentDataLenInBuffer = (rxAdHsWriteIdx - rxAdHsReadIdx);
  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Peek the length of the received TLS-Handshake message */

  /* Peek the length of the current received handshake message */
  *HsMsgLenPtr = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx(rxAdHsReadIdx), TCPIP_TLS_CONTENT_LENGTH_OFFSET);

  /* #20 Check if we received the complete TLS-Handshake message */
  if (((uint32)currentDataLenInBuffer - (uint32)TCPIP_TLS_HSHDRLEN) >= *HsMsgLenPtr)
  {
    /* Complete message has been received */

    /* Update the current Hs message end index */
    TcpIp_SetTlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDynType)((uint32)rxAdHsReadIdx + TCPIP_TLS_HSHDRLEN + *HsMsgLenPtr));

    retVal = E_OK;
  }
  else
  {
    /* Handshake message only received partly */
    /* HsMsgLen is not used in any further context, but set it to zero. */
    *HsMsgLenPtr = 0u;
  }

  return retVal;
} /* TcpIp_TlsCoreCtHs_ReadMsgLenFromHsMsg() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Validate the received Handshake type and trigger the Handshake RX-Indication */
  if (TcpIp_TlsCoreCtHs_ValidateTypeField(TlsConIdx, HsMsgLen) == E_OK)
  {
    /* Valid type field received, so inform upper layer about new received HS message */
    TcpIp_TlsCoreCtHs_RxIndication(TlsConIdx);
    retVal = E_OK;
  }


  return retVal;
} /* TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_ValidateTypeField
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateTypeField(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received type is valid for the configured connection (Server/Client) */
  if (TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable(TlsConIdx) == E_OK)
  {
    /* #20 Check that the received type has not been received before */
    if (TcpIp_TlsCoreCtHs_CheckForDuplicateMessages(TlsConIdx) == E_OK)
    {
      /* #30 Check that the current Handshake type is in a valid order */
      if (TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType(TlsConIdx) == E_OK)
      {
        /* #40 Update the type information for the received message */
        if (TcpIp_TlsCoreCtHs_UpdateTypeInformation(TlsConIdx, HsMsgLen) == E_OK)
        {
          /* Increment read pointer by the 1 byte content type and by the 3 byte handshake type_len length */
          TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TCPIP_TLS_CT_LEN + TCPIP_TLS_HSLEN_LEN));

          /* #50 Handshake message processed, return E_OK */
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
} /* TcpIp_TlsCoreCtHs_ValidateTypeField() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxBufferReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  uint8 currentReceivedHsType = TcpIp_GetTlsBufferRx(rxBufferReadIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received TLS handshake type is valid for the configured connection (Server/Client) */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
  {
    /* Mode == TCPIP_TLS_SERVER */
    if (   (currentReceivedHsType == TCPIP_TLS_HSTYPE_CLIENTHELLO)
        || (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATE)  /* server or client certificate */
        || (currentReceivedHsType == TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE)
        || (currentReceivedHsType == TCPIP_TLS_HSTYPE_FINISHED))
    {
      /* #20 Valid type for TLS Server - return E_OK */
      retVal = E_OK;
    }
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    if (    (currentReceivedHsType == TCPIP_TLS_HSTYPE_HELLOREQUEST)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_SERVERHELLO)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATE)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_SERVERHELLODONE)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_FINISHED)
         || (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATESTATUS))
    {
      /* #30 Valid type for TLS Client - return E_OK */
      retVal = E_OK;
    }
  }
# endif

  if (retVal != E_OK)
  {
    /* In case of invalid or unknown type - report error */
    TcpIp_TlsUserErrorType hsTypeUserError;
    hsTypeUserError.FunctionId = TCPIP_TLS_FCTID_CORE_CTHS_CHECKFRAMETYPE;
    hsTypeUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTFRAMETYPE;
    hsTypeUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(hsTypeUserError);
  }

  return retVal;
} /* TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_CheckForDuplicateMessages
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6030, 6050 1 */ /* MD_TcpIp_Tls_STCYC, MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_CheckForDuplicateMessages(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
# endif

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxBufferReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  uint8 currentReceivedHsType = TcpIp_GetTlsBufferRx(rxBufferReadIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received TLS handshake type has not been received before */
  switch (currentReceivedHsType)
  {
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  case TCPIP_TLS_HSTYPE_CLIENTHELLO:
  {
    /* Check if the received message is the first received Client Hello */
    if (TcpIp_GetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXCLIENTHELLOIDXOFTLSSERVERBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_CLIENTHELLO */
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  case TCPIP_TLS_HSTYPE_SERVERHELLO:
  {
    /* Check if the received message is the first received Server Hello */
    if (TcpIp_GetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXSERVERHELLOIDXOFTLSCLIENTBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERHELLO */

  case TCPIP_TLS_HSTYPE_CERTIFICATE:
  {
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* Check if the received message is the first received Server Certificate */
      if (TcpIp_GetTlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
            == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESIDXOFTLSCLIENTBUFFERMGMT)
      {
        retVal = E_OK;
      }
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_CERTIFICATE */

  case TCPIP_TLS_HSTYPE_CERTIFICATESTATUS:
  {
    /* Check if the received message is the first received Certificate Status */
    if (TcpIp_GetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATESTATUSIDXOFTLSCLIENTBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* TCPIP_TLS_HSTYPE_CERTIFICATESTATUS */

  case TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE:
  {
    /* Check if the received message is the first received Server Key Exchange */
    if (TcpIp_GetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXSERVERKEYEXCHANGEIDXOFTLSCLIENTBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE */

  case TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST:
  {
    /* Check if the received message is the first received Certificate Request */
    if (TcpIp_GetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXSERVERCERTIFICATEREQUESTIDXOFTLSCLIENTBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST */

  case TCPIP_TLS_HSTYPE_SERVERHELLODONE:
  {
    /* Check if the received message is the first received Server Hello Done */
    if (TcpIp_GetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXSERVERHELLODONEIDXOFTLSCLIENTBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERHELLODONE */
# endif /* TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON */

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  case TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE:
  {
    /* Check if the received message is the first received Client Key Exchange */
    if (TcpIp_GetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)
          == TCPIP_NO_TLSBUFFERRXCLIENTKEYEXCHANGEIDXOFTLSSERVERBUFFERMGMT)
    {
      retVal = E_OK;
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE */
# endif

  case TCPIP_TLS_HSTYPE_FINISHED:
  {
    /* Server and client share the finished message - check which message is received */
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
    {
      /* Check if the received message is the first received Client Finished */
      if (TcpIp_GetTlsBufferRxClientFinishedIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)
            == TCPIP_NO_TLSBUFFERRXCLIENTFINISHEDIDXOFTLSSERVERBUFFERMGMT)
      {
        retVal = E_OK;
      }
    }
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* Check if the received message is the first received Server Finished */
      if (TcpIp_GetTlsBufferRxServerFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)
            == TCPIP_NO_TLSBUFFERRXSERVERFINISHEDIDXOFTLSCLIENTBUFFERMGMT)
      {
        retVal = E_OK;
      }
    }
# endif
    break;
  } /* case TCPIP_TLS_HSTYPE_FINISHED */

  default:
  {
    /* Invalid type is checked by function TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable */
    retVal = E_NOT_OK;
    break;
  }
  } /* switch */

  return retVal;
} /* TcpIp_TlsCoreCtHs_CheckForDuplicateMessages() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxBufferReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  uint8 currentReceivedHsType = TcpIp_GetTlsBufferRx(rxBufferReadIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the received TLS handshake type is in order to the last received type */
  if (   (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_MAX_LASTRECEIVEDHSTYPEOFTLSCONNECTIONDYN)   /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
      || (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) < currentReceivedHsType)                             /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
         /* Check If certificate verify was received as it may arrive out of order */
      || (   (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE)           /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATEVERIFY))
         /* Check If certificate status was received as it may arrive out of order due to higher handshake type number */
      || (   (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_HSTYPE_CERTIFICATESTATUS)           /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (currentReceivedHsType == TCPIP_TLS_HSTYPE_SERVERHELLODONE))
      /* Check If certificate status request was received as it may arrive out of order due to higher handshake type number */
      /* ECDH cipher: Last received type was CertificateStatus, then the Certificate Request message is received */
      || (   (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_HSTYPE_CERTIFICATESTATUS)           /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (currentReceivedHsType == TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST))

      /* ECDHE cipher: Last received type was CertificateStatus, then the ServerKeyExchange message is received */
      || (   (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_HSTYPE_CERTIFICATESTATUS)           /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (currentReceivedHsType == TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE))

     )
  {
    /* #20 message received in the correct order - return E_OK */
    retVal = E_OK;
  }
  else
  {
    /* #30 We received an invalid order of Handshake messages and we have to trigger a TLS alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreCtHs_ValidateOrderOfReceivedType() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_UpdateTypeInformation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6030, 6050 1 */ /* MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_UpdateTypeInformation(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) HsMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
    = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
    = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
# endif

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxBufferReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn( tlsBufferMgmtIdx);

  uint8 currentReceivedHsType = TcpIp_GetTlsBufferRx(rxBufferReadIdx);
  Std_ReturnType retVal       = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Start indices and length information for the given handshake type message */
  switch (currentReceivedHsType)
  {

/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  case TCPIP_TLS_HSTYPE_CLIENTHELLO:
  {
    TcpIp_SetTlsBufferRxClientHelloIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetClientHelloLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_CLIENTHELLO);
    break;
  } /* case TCPIP_TLS_HSTYPE_CLIENTHELLO */
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  case TCPIP_TLS_HSTYPE_SERVERHELLO:
  {
    TcpIp_SetTlsBufferRxServerHelloIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetServerHelloLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERHELLO);
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERHELLO */

  case TCPIP_TLS_HSTYPE_CERTIFICATE:
  {
    if(TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      TcpIp_SetTlsBufferRxServerCertificatesIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
      TcpIp_SetServerCertificatesLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
      TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_CERTIFICATE);
    }
    break;
  } /* case TCPIP_TLS_HSTYPE_CERTIFICATE */

  case TCPIP_TLS_HSTYPE_CERTIFICATESTATUS:
  {
    TcpIp_SetTlsBufferRxServerCertificateStatusIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetServerCertificateStatusLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_CERTIFICATESTATUS);
    break;
  } /* TCPIP_TLS_HSTYPE_CERTIFICATESTATUS */

  case TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE:
  {
    TcpIp_SetTlsBufferRxServerKeyExchangeIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetServerKeyExchangeLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE);
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE */

  case TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST:
  {
    TcpIp_SetTlsBufferRxServerCertificateRequestIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetServerCertificateRequestLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST);
    break;
  } /* case TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST */

  case TCPIP_TLS_HSTYPE_SERVERHELLODONE:
  {
    TcpIp_SetTlsBufferRxServerHelloDoneIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetServerHelloDoneLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_SERVERHELLODONE);
    break;
  } /* case TCPIP_TLS_HSTYPE_SERVERHELLODONE */
# endif /* TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON */

/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Minor: The message CertificateVerify is not in the list of receivable messages (because client authentication is not implemented), so this case must be removed here. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
  case TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE:
  {
    TcpIp_SetTlsBufferRxClientKeyExchangeIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, rxBufferReadIdx);
    TcpIp_SetClientKeyExchangeLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, (uint16)HsMsgLen);
    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE);
    break;
  } /* case TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE */
# endif

  case TCPIP_TLS_HSTYPE_FINISHED:
  {
    /* Server and client share the finished message - check which message is received */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
    {
      /* Update finished message information for server (received message = ClientFinished) */
      TcpIp_SetTlsBufferRxClientFinishedIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, rxBufferReadIdx);
      TcpIp_SetClientFinishedLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, (uint16)HsMsgLen);
    }
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* update finished information for client (received message = ServerFinished) */
      TcpIp_SetTlsBufferRxServerFinishedIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, rxBufferReadIdx);
      TcpIp_SetServerFinishedLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, (uint16)HsMsgLen);
    }
# endif

    TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_FINISHED);
    break;
  } /* case TCPIP_TLS_HSTYPE_FINISHED */

  default:
  {
    /* Invalid type is checked by function TcpIp_TlsCoreCtHs_CheckIfTypeIsReceivable */
    retVal = E_NOT_OK;
    break;
  }
  } /* switch */

  return retVal;
} /* TcpIp_TlsCoreCtHs_UpdateTypeInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAdHsWriteIdx
    = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxAdHsReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType currentMsgLenInBuffer;
  uint8 currentMsgHsTypeInBuffer;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  currentMsgLenInBuffer    = (rxAdHsWriteIdx - rxAdHsReadIdx);
  currentMsgHsTypeInBuffer = TcpIp_GetTlsBufferRx(rxAdHsReadIdx);
  /* #10 Compare the received handshake type and length to the expected HelloRequest information */
  if (currentMsgHsTypeInBuffer == TCPIP_TLS_HSTYPE_HELLOREQUEST)
  {
    if (currentMsgLenInBuffer == TCPIP_TLS_HELLOREQUEST_LEN)
    {
      /* Get the received length of the HelloRequest frame */
      uint32 receivedHelloRequestLength = IpBase_GetUint24(TcpIp_GetAddrTlsBufferRx(rxAdHsReadIdx),
        TCPIP_TLS_CONTENT_LENGTH_OFFSET);

      /* RFC5246 - 7.4.1.1.  Hello Request */
      /*  Structure of this message:
       *
       *  struct { } HelloRequest;
       *  This message contains no data, therefore the length MUST be zero
       */
      if (receivedHelloRequestLength == 0u)
      {
        /* #20 Valid HelloRequest message - return E_OK */
        retVal = E_OK;
      }
      else
      {
        /* else - invalid TLS HelloRequest frame - trigger alert */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
        /* return E_OK - we have to remove the received HelloRequest from the buffer and do not forward it to the upper layer */
        retVal = E_OK;
      }
    }
    else
    {
      /* else - invalid TLS HelloRequest frame - trigger alert */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      /* return E_OK - we have to remove the received HelloRequest from the buffer and do not forward it to the upper layer */
      retVal = E_OK;
    }
  } /* else - Not an TLS HelloRequest frame - do nothing */

  return retVal;
} /* TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtHs_HandleInvalidHsMessage
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtHs_HandleInvalidHsMessage(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType hsUserError;
  TcpIp_TlsAlertLevelType alertLevel;
  TcpIp_TlsAlertDescriptionType alertDescription;

  /* ----- Implementation ----------------------------------------------- */
  /* Set the corresponding error id */
  hsUserError.FunctionId = TCPIP_TLS_FCTID_CORE_MAINFCT_RXHS;
  hsUserError.UserErrorId = TCPIP_TLS_ERRORID_RXINCORRECTHSMESSAGE;
  hsUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  /* #10 Report the error to the user */
  TcpIp_TlsCoreError_ReportUserError(hsUserError);

  /* Set the corresponding alert level and description */
  alertLevel       = TCPIP_TLS_ALERT_LEVEL_FATAL;
  alertDescription = TCPIP_TLS_ALERT_DESC_UNEXP_MSG;

  /* #20 Trigger the transmission of the occurred alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);

} /* TcpIp_TlsCoreCtHs_HandleInvalidHsMessage() */

/**********************************************************************************************************************
 *  TLS CORE CT CHANGE CIPHER SPEC
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtCcs_ValidateAndForwardFrameToCCsHandler
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
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtCcs_ValidateAndForwardFrameToCCsHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
    = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx); /* Get the index of the current CipherDefiniton */

  TcpIp_CipherSuiteIdOfTlsCipherDefinitionType selectedCipherSuiteId
    = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx);   /* Get the corresponding Cipher Id (HexCode) */

  TcpIp_LastReceivedContentTypeOfTlsConnectionDynType lastReceivedContentType
    = TcpIp_GetLastReceivedContentTypeOfTlsConnectionDyn(TlsConIdx);


  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Only process messages if the received content type is CCs */
  if (lastReceivedContentType == TCPIP_TLS_CT_CCS)
  {
    uint8 ccsLen = (uint8)(TcpIp_GetTlsBufferRxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
      - TcpIp_GetTlsBufferRxCcsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* #10 Check if we have received some data in the CCS RX-Buffer */
    if (ccsLen == TCPIP_TLS_CCSMSG_LEN)
    {
      uint8 receivedCcsData = TcpIp_GetTlsBufferRx(TcpIp_GetTlsBufferRxCcsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

      /* #20 Check if the received data has the format of the CCS message */
      if (receivedCcsData == TCPIP_TLS_CHANGECIPHERSPEC)
      {
        /* #30 if so, check if we are allowed to received the CCS message */
        if (TcpIp_IsCcsReceivableOfTlsConnectionDyn(TlsConIdx) == TRUE)
        {
          /* #40 if so, check if the last received message is not the finished message */
          if (TcpIp_GetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_HSTYPE_FINISHED)
          {
            /* #50 if so, set CCS message RxIndication */
            TcpIp_SetCcsRxIndicationOfTlsConnectionDyn(TlsConIdx, TRUE);

            /* #60 Change the RX cipher spec to the negotiated cipher ID */
            TcpIp_SetActiveCipherRxOfTlsConnectionDyn(TlsConIdx, selectedCipherSuiteId);
            /* #70 Reset the RX RL Sequence Counter */
            TcpIp_SetRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx, 0u);

            /* reset the CCS write index */
            TcpIp_SetTlsBufferRxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TcpIp_GetTlsBufferRxCcsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
            retVal = E_OK;
          }
          else
          {
            /* #80 Trigger the transmission of the occurred alert */
            TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
          }
        }
        else
        {
          /* CCS message received in an invalid state (CCs not receivable) */
          TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage(TlsConIdx);
        }
      }
      else
      {
        /* Invalid CCS data received */
        TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
      }
    }
    else
    {
      /* Invalid CCS length received */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    }
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType alUserError;

  /* ----- Implementation ----------------------------------------------- */
  /* Set the corresponding error id */
  alUserError.FunctionId = TCPIP_TLS_FCTID_CORE_MAINFCT_CCS;
  alUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_CT;
  alUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  /* #10 Report the error to the user */
  TcpIp_TlsCoreError_ReportUserError(alUserError);

  /* #20 Trigger the transmission of the occurred alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);

} /* TcpIp_TlsCoreCtCcs_HandleInvalidCcsMessage() */

/**********************************************************************************************************************
 *  TLS CORE CT APPLICATION DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAd_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAd_RxIndication(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Application data RX-Indication */
  TcpIp_SetAdRxIndicationOfTlsConnectionDyn(TlsConIdx, TRUE);
} /* TcpIp_TlsCoreCtAd_RxIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAd_ForwardDataToAdHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAd_ForwardDataToAdHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType                       tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If there is new plaintext in TLS Rx AdHs buffer that has not been forwarded to Ul, trigger RxIndication */
  if (TcpIp_GetAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) != 0u)
  {
    /* Trigger the Ad RxIndicaiton */
    TcpIp_TlsCoreCtAd_RxIndication(TlsConIdx);
    retVal = E_OK;
  }
  return retVal;
} /* TcpIp_TlsCoreCtAd_ForwardDataToAdHandler() */

/**********************************************************************************************************************
 *  TLS CORE CT ALERT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_RxIndication(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Alert RX-Indication */
  TcpIp_SetAlRxIndicationOfTlsConnectionDyn(TlsConIdx, TRUE);
} /* TcpIp_TlsCoreCtAl_RxIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TcpIp_TlsAlertLevelType       AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx                 = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxAlWriteIdxOfTlsBufferMgmtDynType txAlWriteIdx =
               TcpIp_GetTlsBufferTxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the transmission of this alert */
  TcpIp_SetTxAlertTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);

  if ((AlertLevel == TCPIP_TLS_ALERT_LEVEL_WARNING) && (AlertDescription == TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY))
  {
    TcpIp_SetTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx, TRUE);
  }

  /* Write the AlertLevel into Alert TX-Buffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(txAlWriteIdx), TCPIP_TLS_ALERTLEVEL_OFFSET, AlertLevel);

  /* Write the Alert Description into Alert TX-Buffer */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(txAlWriteIdx), TCPIP_TLS_ALERTDESCRIPTION_OFFSET, AlertDescription);

} /* TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_TxAlert
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_TxAlert(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx
    = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAlWriteIdxOfTlsBufferMgmtDynType txAlWriteIdx
    = TcpIp_GetTlsBufferTxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAlStartIdxOfTlsBufferMgmtType txAlStartIdx
    = TcpIp_GetTlsBufferTxAlStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we are in a valid state to transmit the alert */
  if (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_CONNECTION_CLOSED)
  {
    /* #20 Forward the alert to the record layer and transmit the frame */
    if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, txAlWriteIdx, TCPIP_TLS_ALERT_MSG_LEN, TCPIP_TLS_CT_AL) == E_OK)
    {
      /* Close the Tcp socket from TLS - After transmitting TLS Alert no more data should be exchanged */
      TcpIp_Tls_CloseInternal(TlsConIdx);

      /* Reset the alert trigger and the alert write index, if transmission was successful */
      TcpIp_SetTlsBufferTxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, txAlStartIdx);
      TcpIp_SetTxAlertTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);

      /* #30 Change the TLS-Connection state to TCPIP_TLS_STATE_CONNECTION_CLOSING depending on connection mode (Server/Client) */
      /* With the final TcpEvent CLOSED this state is updated to TCPIP_TLS_STATE_CONNECTION_CLOSED (TcpIp_TlsCoreEvent_TcpEventClosed) */

      if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
      {
        /* TLS-Server */
        /* In case of an TLS-Server, the forwarding of the event to the upper layer depends on the current connection state */
        if (   (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
            || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT))
        {
          /* TLS connection established - the upper layer should be informed about the event */
           TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSING);
        }
        else
        {
          /* TLS handshake active - the upper layer MUST NOT be informed about the event */
          TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
            TCPIP_TLS_STATE_CONNECTION_CLOSING_WITHOUT_UPPERLAYER_EVENT_FORWARDING);
        }
      }
      else
      {
        /* TLS-Client */
        /* In case of an TLS-Client, the upper layer should be informed about the event */
        TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSING);
      }

      /* Reset the TxCloseNotifyTrigger. */
      if (TcpIp_IsTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx) == TRUE)
      {
        TcpIp_SetTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);
      }
    }

    /* If the transmit call return E_NOT_OK, we will try to transmit the alert in the next main function cycle again */
  }
} /* TcpIp_TlsCoreCtAl_TxAlert() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx                   = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType  rxAlReadIdx  = TcpIp_GetTlsBufferRxAlReadIdxOfTlsBufferMgmtDyn(
                                                                        tlsBufferMgmtIdx);
  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAlWriteIdx = TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(
                                                                        tlsBufferMgmtIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we have unprocessed Alert data and trigger the Alert Rx-Indication */
  if (rxAlReadIdx != rxAlWriteIdx)
  {
    /* Trigger the Al Rx-Indication */
    TcpIp_TlsCoreCtAl_RxIndication(TlsConIdx);

    retVal = E_OK;
  }
  return retVal;
} /* TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_ParseReceivedAlert
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_ParseReceivedAlert(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxAlBufferStartIdx
    = TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Get the received alert level from the TLS RxBuffer */
# ifdef C_REVIEW_VECTOR                                                                                                 /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Minor: Length check is missing, check that at least 2 bytes are available. */
/* [REVIEW_c] resolved visbdk: I think this is not needed here, since we know that the rxAlBuffer is 2 bytes (+ HMAC offset). */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
# endif
  uint8 alertLevel = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(rxAlBufferStartIdx), TCPIP_TLS_ALERTLEVEL_OFFSET);

  /* Get the received alert description from the TLS RxBuffer */
  uint8 alertDescription = IpBase_GetUint8(TcpIp_GetAddrTlsBufferRx(rxAlBufferStartIdx),
    TCPIP_TLS_ALERTDESCRIPTION_OFFSET);

  /* #10 Check if the received alert is valid and forward it to the internal processing */
  if (TcpIp_TlsCoreCtAl_CheckAlert(alertLevel, alertDescription) == E_OK )
  {
    /* Valid Alert received */
    /* #20 Check if the incoming alert is a Close_Notify alert */
    if ((alertLevel == TCPIP_TLS_ALERT_LEVEL_WARNING) && (alertDescription == TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY))
    {
      /* #30 If so, forward the alert to the Close_Notify handler */
      TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert(TlsConIdx);
    }
    else if (alertLevel == TCPIP_TLS_ALERT_LEVEL_WARNING)
    {
      /* We treat all incoming waring alerts as fatal */
      /* FIN is transmitted automatically when sending the Alert in TcpIp_TlsCoreMainFunction_TxAl */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_INT_ERROR);
    }
    else
    {
      /* #40 Otherwise, forward the alert to the generic alert handler */
      TcpIp_TlsCoreCtAl_HandleAllOtherAlerts(TlsConIdx);
    }

# ifdef C_REVIEW_VECTOR                                                                                                 /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.7 Question: What happens if we receive an alert message with 3 or 4 bytes? What if we receive two alerts in the same record layer message, like a warning and a fatal alert? */
/* [REVIEW_c] resolved visbdk: have to double check this (I added a note in the TCPIP-6028) but for my understanding this is not possible. The record layer checks the available buffer size and discards the message. So we can not reach this point with 2 alert messages in one RL. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
# endif
    /* Reset the write index because we processed this alert */
    TcpIp_SetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, rxAlBufferStartIdx);
  }
  else
  {
    /* invalid Alert received , respond with an decode_error alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
  }
} /* TcpIp_TlsCoreCtAl_ParseReceivedAlert() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_CheckAlert
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCtAl_CheckAlert(
  TcpIp_TlsAlertLevelType AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the AlertLevel */
  if ((AlertLevel == TCPIP_TLS_ALERT_LEVEL_WARNING) || (AlertLevel == TCPIP_TLS_ALERT_LEVEL_FATAL))
  {
    /* #20 Check the AlertDescription */
    switch (AlertDescription)
    {
      /* Fall through all possible valid Alert descriptions */
      case TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY:
      case TCPIP_TLS_ALERT_DESC_UNEXP_MSG:
      case TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC:
      case TCPIP_TLS_ALERT_DESC_DECR_FAILED_RESERVED:
      case TCPIP_TLS_ALERT_DESC_RECORD_OVERFLOW:
      case TCPIP_TLS_ALERT_DESC_DECOMP_FAILURE:
      case TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE:
      case TCPIP_TLS_ALERT_DESC_NO_CERT_RESERVED:
      case TCPIP_TLS_ALERT_DESC_BAD_CERT:
      case TCPIP_TLS_ALERT_DESC_UNSUP_CERT:
      case TCPIP_TLS_ALERT_DESC_CERT_REVOKED:
      case TCPIP_TLS_ALERT_DESC_CERT_EXPIRED:
      case TCPIP_TLS_ALERT_DESC_CERT_UNKNOWN:
      case TCPIP_TLS_ALERT_DESC_ILLEGAL_PARAM:
      case TCPIP_TLS_ALERT_DESC_UNKNOWN_CA:
      case TCPIP_TLS_ALERT_DESC_ACCESS_DENIED:
      case TCPIP_TLS_ALERT_DESC_DECODE_ERROR:
      case TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR:
      case TCPIP_TLS_ALERT_DESC_EXP_RESTR_FAILURE:
      case TCPIP_TLS_ALERT_DESC_PROT_VERSION:
      case TCPIP_TLS_ALERT_DESC_INSUF_SEC:
      case TCPIP_TLS_ALERT_DESC_INT_ERROR:
      case TCPIP_TLS_ALERT_DESC_USER_CANCELED:
      case TCPIP_TLS_ALERT_DESC_NO_RENEGOT:
      case TCPIP_TLS_ALERT_DESC_UNSUP_EXT:
      case TCPIP_TLS_ALERT_DESC_CERT_UNOBTAINABLE:
      case TCPIP_TLS_ALERT_DESC_UNRECOGNIZED_NAME:
      case TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP:
      case TCPIP_TLS_ALERT_DESC_BAD_CERT_HASH_VALUE:
      case TCPIP_TLS_ALERT_DESC_UNKNOWN_PSK_IDENTITY:
      {
        /* Valid Alert Description */
        retVal = E_OK;
        break;
      }

      default:
      {
        /* Invalid Alert Description */
        retVal = E_NOT_OK;
        break;
      }
    } /* switch */
  }
  else
  {
    /* Invalid AlertLeve - set retVal to E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreCtAl_CheckAlert() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the current connection state */
  if (   (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
      || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT))
  {
    /* #20 TLS connection is established and a valid CloseNotify is received. Respond with an CloseNotify alert */
    /* RFC5246 - 7.2.1.  Closure Alerts */
    /* The other party MUST respond with a close_notify alert of its own and close down the connection immediately,
     * discarding any pending writes. */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_WARNING, TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY);

    /* State TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT is used to transmit the CloseNoftify Alert (in MainFunction_TxAl).
     * After the transmit, the state is changed to CLOSE_REQUESTED, where the FIN is triggered. */
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT);
  }
  else
  {
    /* #30 TLS handshake is active - Receiving of CloseNotify is not allowed - Respond with TLS alert */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }

} /* TcpIp_TlsCoreCtAl_HandleCloseNotifyAlert() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtAl_HandleAllOtherAlerts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtAl_HandleAllOtherAlerts(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx);
  /* ----- Implementation ----------------------------------------------- */

  /* Only if the user is not already informed we should trigger the Event */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT))
  {
    /* Connection already closed on TCP side */

    /* #10 Inform the upper layer depending on the TLS connection mode and the state of the connection */
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* #20 TLS-Client - Gracefully close the TCP connection (FIN) */
      /* Event forwarding (FIN_RECEIVED, CLOSED) is done in TcpIp_TlsCoreConState_TcpCloseRequestedHandler() */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED);
    }
    else
    {
      /* #30 TLS-Server - Gracefully close the TCP connection (FIN) - Event forwarding is done depending on the current connection state */
      if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
      {
        /* TLS connection is established - UpperLayer should be informed */
        /* Manually trigger FIN_RECEIVED event, since the initial event is not directly forwarded by the TcpIP */
        TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);
        TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED);
      }
      else
      {
        /* TLS handshake is active - UpperLayer MUST NOT be informed */
        TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING);
      }
    }
  }
  else
  {
    /* Connection not yet closed on TCP side - trigger close from TLS */
    TcpIp_CloseTcpSocketFromTls(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), FALSE);
  }

} /* TcpIp_TlsCoreCtAl_HandleAllOtherAlerts() */

/**********************************************************************************************************************
 *  TLS CORE RECORD LAYER (RL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_Init(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsLengthOfTlsBufferMgmtType availableRxAdHsBufferSize =
    TcpIp_GetTlsBufferRxAdHsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialization of Record Layer values */
  /* RL TX Information */
  TcpIp_SetRlTxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0);
  TcpIp_SetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0);
  TcpIp_SetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0);
  TcpIp_SetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXRLSENDIDXOFTLSBUFFERMGMTDYN);

  /* RL RX Information */
  TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
          TCPIP_NO_TLSBUFFERRXRLFRAMESTARTIDXOFTLSBUFFERMGMTDYN);
  TcpIp_SetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0);

  /* RL Sequence counter */
  TcpIp_SetRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx, 0);
  TcpIp_SetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx, 0);

  /* The RxBufferSize can be larger then the maximum supported limit for this extension - The value is offered via the record_size_limit extension to the peer */
  if (availableRxAdHsBufferSize <= TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE)
  {
    /* RX Record size limit is set to the configured value (Available RxBuffer Size of this TLS connection) */
    TcpIp_SetRxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx, (uint16)availableRxAdHsBufferSize);
  }
  else
  {
    /* TLS1.2 maximum support 2^14 byte as record_size_limit extension */
    TcpIp_SetRxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE);
  }
  /* The active maximum RX size for one RL frame is set to the available RxBuffer size of this connection */
  TcpIp_SetActiveMaxRxRlSizeOfTlsConnectionDyn(TlsConIdx, availableRxAdHsBufferSize);

  /* TX Record size limit is initial set to 0 and then updated by the received extension during the TLS handshake */
  TcpIp_SetTxRecordSizeLimitOfTlsConnectionDyn(TlsConIdx, 0u);

  /* The active maximum TX size for one RL frame is set to the maximum defined value (2^14), which means that there is no limitation. */
  TcpIp_SetActiveMaxTxRlSizeOfTlsConnectionDyn(TlsConIdx,
    TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE);

  /* Reset the indication flag, which is used to determine if the extension is received from the peer connection */
  TcpIp_SetExtensionRecordSizeLimitReceivedOfTlsConnectionDyn(TlsConIdx, FALSE);

} /* TcpIp_TlsCoreRl_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAndAuthFrame
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAndAuthFrame(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint8)        BufPtr,
  uint16                  BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType           retVal = BUFREQ_E_NOT_OK;
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine the appropriate Tls connection and perform authentication and encryption */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
    /* Calculate the MAC for the Tx data in the Tls buffer and store in temp buffer */

    if (TcpIp_TlsCoreRl_CalcHmacCipherDependend(tlsConIdx, BufLength) == E_OK)
    {
      /* Perform encryption and copy to the provided TcpIp buffer */
      retVal = TcpIp_TlsCoreRl_EncryptCipherDependend(tlsConIdx, BufPtr, BufLength); /*lint !e655 */
    }
    else
    {
      /* retVal = BUFREQ_E_NOT_OK */
    }
  }
  else
  {
     /* Handling and reporting of errors (user error) during encryption is done in the subfunction - left blank intentionally */
  }

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAndAuthFrame() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptCipherDependend
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType               retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the active cipher, perform the encryption */
  switch (TcpIp_GetActiveCipherTxOfTlsConnectionDyn(TlsConIdx))
  {
  case TCPIP_TLS_NULL_WITH_NULL_NULL:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    {
      /* Null encryption */
      retVal = TcpIp_TlsCoreRl_TxCipherEncryptNull(TlsConIdx, BufPtr, BufLength);
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      /* Aes128 CBC encryption */
      retVal = TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc(TlsConIdx, BufPtr, BufLength);
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256:
    {
      /* Aes128 GCM encryption */
      retVal = TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm(TlsConIdx, BufPtr, BufLength);
      break;
    }
  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    break;
  } /* switch */

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptCipherDependend */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_RlTxFragmentLenOfTlsBufferMgmtDynType requestedRlTxLen = TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  /* Calculate the total size of the TCP buffer segments */
  uint32 totalTcpBufLen = (uint32)BufLength + (uint32)TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

  /* #10 Check if provided TCP buffer(s) has sufficient space and trigger Aes128 Cbc streaming */
  if (totalTcpBufLen < requestedRlTxLen)
  {
    /* The provided TCP buffer segment is not sufficient, store this buffer into DataSplit struct for next call */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = BufPtr;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = BufLength;
    retVal = BUFREQ_OK;
  }
  else
  {
    /* Sufficient TCP buffer available, trigger Aes128 Cbc streaming */
    if (TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode(TlsConIdx, BufPtr, BufLength) == E_OK)
    {
        retVal = BUFREQ_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAes128Cbc() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_RlTxFragmentLenOfTlsBufferMgmtDynType requestedRlTxLen =
         TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  /* Total size of the TCP buffer segments */
  uint32 totalTcpBufLen = (uint32)BufLength + (uint32)TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

  /* #10 Check if provided buffer(s) has sufficient space and trigger Aes128 Gcm streaming */
  if (totalTcpBufLen < requestedRlTxLen)
  {
    /* The provided TCP buffer segment is not sufficient, store this buffer into DataSplit struct for the next call */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = BufPtr;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = BufLength;
    retVal = BUFREQ_OK;
  }
  else
  {
    /* Sufficient TCP buffer available, trigger Aes128 Gcm streaming */
    if (TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode(TlsConIdx, BufPtr, BufLength) == E_OK)
    {
        retVal = BUFREQ_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherAEADEncryptandAes128Gcm() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptNull
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptNull(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType               tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_RlTxFragmentLenOfTlsBufferMgmtDynType requestedLen = TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Total length of the TCP buffer segments */
  uint32 totalTcpBufLen = (uint32)BufLength + (uint32)TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if provided buffer has sufficient space and trigger Null streaming */
  if (totalTcpBufLen < requestedLen)
  {
    /* Store provided buffer info into the Tx data split struct */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = BufPtr;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = BufLength;
  }
  else
  {
    /* Sufficient TCP buffer available, trigger Null streaming */
    TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode(TlsConIdx, BufPtr, BufLength);
  }

  return BUFREQ_OK;
} /* TcpIp_TlsCoreRl_TxCipherEncryptNull() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
   /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType            tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Length of the total plain text in TLS buffer */
  uint32  plainTextLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Pointer to TCP buffer segment 1 */
  TCPIP_P2V(uint8) seg1Ptr = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr;
  /* Length of TCP buffer segment 1 */
  uint16           seg1Len = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;
  /* Pointer to TCP buffer segment 2 */
  TCPIP_P2V(uint8) seg2Ptr = BufPtr;
  /* Length of the MAC */
  uint8  macLen = TcpIp_TlsCoreRl_GetTxCipherMacLen(TlsConIdx);
  /* Length of plaintext in TCP segment 1 */
  uint32 plainTextLenInSeg1;
  /* Length of plaintext in TCP segment 2 */
  uint32 plainTextLenInSeg2;

  /* ----- Implementation ----------------------------------------------- */
  /* Write data and MAC to the TCP buffer. Depending on existing data in the TCP buffer there are one or two segments
     of the buffer:
     [xxxxxx<  seg2  >xxxxxxx] There is one linear block of free buffer somewhere in the middle of the buffer.
     [< seg2 >xxxxxxx< seg1 >] There is free space at the end and at the beginning of the TCP (ring-)buffer.

     Pointer and length of TCP buffer seg1 are stored in the rTxDataSplit struct.
     Pointer and length of TCP buffer seg2 are given via the API parameters BufPtr and BufLength.
  */
  TCPIP_ASSERT((seg1Len + BufLength) >= (uint16)(plainTextLen + macLen));


  /* Calculate the lengths of the plaintext that will be copied into the TCP buffer segment(s) */
  if (plainTextLen > seg1Len)
  {
    /* Plaintext is split between the two segments (or entirely in segment 2) */
    plainTextLenInSeg1 = seg1Len;
    plainTextLenInSeg2 = plainTextLen - seg1Len;
  }
  else
  {
    /* Plaintext is entirely in segment 1 */
    plainTextLenInSeg1 = plainTextLen;
    plainTextLenInSeg2 = 0u;
  }

  /* #10 Copy the plaintext data from TLS buffer into the TCP buffer segment(s) */
  TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound(TlsConIdx, seg1Ptr, plainTextLenInSeg1, seg2Ptr, plainTextLenInSeg2);


  /* #20 Copy the Mac into the TCP buffer segment(s) if available */
  if (macLen > 0u)
  {
    /* Space remaining in TCP segment 1 after writing the plaintext */
    uint32 remainingLenInSeg1 = (plainTextLen < seg1Len) ? (seg1Len - plainTextLen) : 0u;
    /* Pointer to TCP segments to write the Mac */
    TCPIP_P2V(uint8) seg1MacPtr = NULL_PTR;
    TCPIP_P2V(uint8) seg2MacPtr;

    /* If there is space available in the first segment, and update the pointer */
    if ((seg1Ptr != NULL_PTR) && (remainingLenInSeg1 > 0u))
    {
      /* Update the TCP segment 1 pointer considering plaintext already copied */
      seg1MacPtr = &seg1Ptr[plainTextLenInSeg1];
    }

    /* Update the TCP segment 2 pointer considering plaintext already copied */
    seg2MacPtr = &seg2Ptr[plainTextLenInSeg2];

    /* Copy the Mac into the TCP buffer segment(s) */
    TcpIp_TlsCoreRl_CopyHmacToTxBuffer(TlsConIdx, seg1MacPtr, remainingLenInSeg1, seg2MacPtr);
  }

  /* Reset the wraparound DataSplit struct elements */
  if (seg1Ptr != NULL_PTR)
  {
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;
  }
  TCPIP_DUMMY_STATEMENT_CONST(BufLength);                                                                               /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
} /* TcpIp_TlsCoreRl_TxCipherEncryptNullStreamingMode() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  uint32                      TcpSeg1Len,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  uint32                      TcpSeg2Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Length of the total plain text in TLS buffer */
  uint32  plainTextLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If TCP segment 1 exists, and copy plain text to fill segment 1 */
  if (TcpSeg1Ptr != NULL_PTR)
  {
    /* Copy plaintext from TLS buffer into TCP segment 1, considering TLS buffer wraparound */
    TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound(TlsConIdx, TcpSeg1Ptr, (uint16)TcpSeg1Len);
  }

  /* #20 If more plaintext present in TLS buffer, and copy to segment 2 */
  if (plainTextLen > TcpSeg1Len)
  {
    /* Copy plaintext from TLS buffer into TCP segment 2, considering TLS buffer wraparound */
    TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound(TlsConIdx, TcpSeg2Ptr, (uint16)TcpSeg2Len);
  }
} /* TcpIp_TlsCoreRl_CopyPlainTextDataWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyHmacToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyHmacToTxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            Seg1Ptr,
  uint32                      Seg1Len,
  TCPIP_P2V(uint8)            Seg2Ptr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(
                                                                TlsConIdx);
  TCPIP_P2C(uint8) macPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx));
  uint8 macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy the Mac into the provided TCP buffer */

  /* The MAC might be split in the TCP buffer due to a buffer wraparound. */
  if (Seg1Ptr != NULL_PTR)
  {
    TCPIP_ASSERT(Seg1Len < macLen);

    /* Copy a part of the MAC into the first segment */
    VStdLib_MemCpy(Seg1Ptr, macPtr, Seg1Len);                                                                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    /* Copy a part of the MAC into the second segment */
    VStdLib_MemCpy(Seg2Ptr, &macPtr[Seg1Len], (macLen - Seg1Len));                                                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }
  else
  {
    /* Copy the MAC into the second segment */
    VStdLib_MemCpy(Seg2Ptr, macPtr, macLen);                                                                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }
} /* TcpIp_TlsCoreRl_CopyHmacToTxBuffer */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  uint32                      TcpSeg1Len,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  uint32                      TcpSeg2Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType              retVal = E_OK;
  TCPIP_P2V(uint8)            seg1Ptr = TcpSeg1Ptr;
  uint16                      seg1Len = (uint16)TcpSeg1Len;
  uint32                      availableSeg1Len = TcpSeg1Len;
  TCPIP_P2V(uint8)            seg2Ptr = TcpSeg2Ptr;
  uint32                      availableSeg2Len = TcpSeg2Len;
  uint32                      seg2Len = TcpSeg2Len;
  uint32                      copiedLen = 0u;
  uint8                       macLen = TcpIp_TlsCoreRl_GetTxCipherMacLen(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(seg1Len != 0u);
  TCPIP_ASSERT(seg1Ptr != NULL_PTR);
  TCPIP_ASSERT(seg2Len != 0u);
  TCPIP_ASSERT(seg2Ptr != NULL_PTR);

  /* #10 Generate Iv and copy into TCP buffer */
  if (TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv(TlsConIdx, seg1Ptr, &availableSeg1Len, seg2Ptr, &availableSeg2Len) == E_OK)
  {
    /* Update the segment buffers depending on data copied */
    seg1Ptr = &seg1Ptr[availableSeg1Len];
    availableSeg1Len = (seg1Len - availableSeg1Len);
    seg1Len = (uint16)availableSeg1Len;
    seg2Ptr = &seg2Ptr[availableSeg2Len];
    availableSeg2Len = (seg2Len - availableSeg2Len);
  }
  else
  {
    retVal = E_NOT_OK;
  }

  /* #20 Start Aes128 Cbc streaming of content data and copy into TCP buffer */
  if (TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData(TlsConIdx, seg1Ptr, &availableSeg1Len, seg2Ptr, &availableSeg2Len) == E_OK)
  {
    /* Update the segment buffers depending on data copied */
    seg1Ptr = &seg1Ptr[availableSeg1Len];
    availableSeg1Len = (seg1Len - availableSeg1Len);
    seg2Ptr = &seg2Ptr[availableSeg2Len];
  }
  else
  {
    retVal = E_NOT_OK;
  }

  /* #30 Encrypt the Mac and padding, copy into TCP buffer, and stop Aes128 Cbc streaming */
  if (TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding(TlsConIdx, &copiedLen) == E_OK)
  {
    /* Mac and padding is available in temp buffer */
    TCPIP_P2C(uint8) tmpBuffPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx)
                                    + macLen);

    if (availableSeg1Len > 0u)
    {
      /* Copy partially into first segment, if space available */
      VStdMemCpy(seg1Ptr, &tmpBuffPtr[0], availableSeg1Len);                                                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    }

    VStdMemCpy(seg2Ptr, &tmpBuffPtr[availableSeg1Len], (copiedLen - availableSeg1Len));                                 /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  uint32                      TcpIpSeg1Len,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  uint32                      TcpIpSeg2Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(uint8)            seg1Ptr = TcpIpSeg1Ptr;
  uint16                      seg1Len = (uint16)TcpIpSeg1Len;
  uint32                      availableSeg1Len = TcpIpSeg1Len;
  TCPIP_P2V(uint8)            seg2Ptr = TcpIpSeg2Ptr;
  uint32                      availableSeg2Len = TcpIpSeg2Len;
  uint32                      seg2Len = TcpIpSeg2Len;
  uint32                      authTagLen = TCPIP_TLS_AES128_GCM_AUTHTAG_LEN;
  uint8  authTag[TCPIP_TLS_AES128_GCM_AUTHTAG_LEN];
  Std_ReturnType  retVal;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(seg1Len != 0u);
  TCPIP_ASSERT(seg1Ptr != NULL_PTR);
  TCPIP_ASSERT(seg2Len != 0u);
  TCPIP_ASSERT(seg2Ptr != NULL_PTR);

  /* #10 Generate the Iv and copy into TcpIp buffer */
  retVal = TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv(TlsConIdx, seg1Ptr, &availableSeg1Len, seg2Ptr, &availableSeg2Len);

  if (retVal == E_OK)
  {
    /* Update the segment pointers depending on Iv copied */
    seg1Ptr = &seg1Ptr[availableSeg1Len];
    availableSeg1Len = (seg1Len - availableSeg1Len);
    seg1Len = (uint16)availableSeg1Len;
    seg2Ptr = &seg2Ptr[availableSeg2Len];
    availableSeg2Len = (seg2Len - availableSeg2Len);

    /* If TCP seg1 only contains IV, then seg1Len is 0 and seg1Ptr is not used below */
    /* #20 Encrypt the content data into the TCP buffer segment(s), and generate authentication tag */
    retVal = TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData(TlsConIdx, seg1Ptr, &availableSeg1Len, seg2Ptr, &availableSeg2Len, &authTag[0], &authTagLen);

    /* #30 Copy the authentication tag into TCP buffer segments */
    if (retVal == E_OK)
    {
      /* Check if there was space available in TCP seg1 */
      if (seg1Len != 0u)
      {
        /* Update the seg1Ptr to point to the start of authentication tag */
        seg1Ptr = &seg1Ptr[availableSeg1Len];
        availableSeg1Len = (seg1Len - availableSeg1Len);

        /* Copy authentication tag to the first segment, if space available */
        if (availableSeg1Len > 0u)
        {
          VStdMemCpy(seg1Ptr, &authTag[0], availableSeg1Len);                                                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        }
      }

      /* Update the seg2Ptr to point to the start of authentication tag and copy the (remaining) authentication tag  */
      seg2Ptr = &seg2Ptr[availableSeg2Len];
      VStdMemCpy(seg2Ptr, &authTag[availableSeg1Len], (TCPIP_TLS_AES128_GCM_AUTHTAG_LEN - availableSeg1Len));           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                    retVal;
  TcpIp_SizeOfTlsBufferMgmtType                     tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) <=
      (uint32)(TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen + BufLength));

  /* #10 Check if the Tcp buffer has wraparound and trigger Aes128 Cbc encryption */
  if (TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen == 0u)
  {
    /* Scenario 1: Encryption with no TCP buffer wrap around */
    retVal = TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall(TlsConIdx, BufPtr, BufLength);
  }
  else
  {
    /* Scenario 2: Encryption with TCP buffer wrap around */
    TCPIP_P2V(uint8) seg1Ptr = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr;
    uint32           seg1Len = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

    retVal = TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithMultiCall(TlsConIdx, seg1Ptr, seg1Len, BufPtr, BufLength);

    /* Reset the Data split struct */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcStreamingMode() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                    retVal;
  TcpIp_SizeOfTlsBufferMgmtType                     tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) <=
      (uint32)(TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen + BufLength));

  /* #10 Check if the TCP buffer has wraparound and trigger Aes128 Gcm encryption */
  if (TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen == 0u)
  {
    /* Scenario 1: Encryption with no TCP buffer wrap around */
    retVal = TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall(TlsConIdx, BufPtr, BufLength);
  }
  else
  {
    /* Scenario 2: Encryption with TCP buffer wrap around */
    TCPIP_P2V(uint8) seg1Ptr = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr;
    uint32           seg1Len = TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

    retVal = TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithTcpWraparound(TlsConIdx, seg1Ptr, seg1Len, BufPtr, BufLength);

    /* Reset the Data split struct */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmStreamingMode() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint32)           EncDataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType       retVal;
  uint8                macLen = TcpIp_TlsCoreRl_GetTxCipherMacLen(TlsConIdx);
  uint32               sizeOfTlsTempBuf = ((uint32)TcpIp_GetTlsTemporaryHmacBufferEndIdxOfTlsConnection(TlsConIdx)
    - TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx));
  /* Pointer to free space in the temporary buffer (after the unencrypted MAC) */
  TCPIP_P2V(uint8) tmpBuffPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx) + macLen);
  /* Length of space available in temporary buffer */
  uint32         tmpBufferLen = (sizeOfTlsTempBuf - macLen);
  /* Size of the ciphertext output buffer for encryption */
  uint32  ciphertextOutBufLen;
  /* Length of ciphertext in temporary buffer */
  uint32 ciphertextLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Encrypt the MAC and Padding and copy it into the temporary buffer */
  ciphertextOutBufLen = tmpBufferLen;
  retVal = TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt(TlsConIdx, &tmpBuffPtr[0], &ciphertextOutBufLen);
  /* Set the total ciphertext length in temporary buffer */
  ciphertextLen = ciphertextOutBufLen;
  /* Update the ciphertext length */
  *EncDataLen = ciphertextLen;

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPadding() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  /* Pointer to the TCP buffer segment */
  TCPIP_P2V(uint8) tcpSegPtr = BufPtr;
  /* Length of the TCP buffer segment */
  uint32 tcpSegLen  = BufLength;
  /* Length of the ciphertext output including Iv */
  uint32 ciphertextOutLen;
  /* Length of the TCP buffer for next operation */
  uint32 availableBufferLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate Iv and set the CSM Key */
  retVal = TcpIp_TlsCoreCrypto_GenerateAesIv(TlsConIdx, tcpSegPtr);
  /* Update length of Iv */
  ciphertextOutLen = TCPIP_TLS_AES128_IV_LEN;
  /* Reduce size of TCP segment with length of Iv */
  tcpSegLen -= TCPIP_TLS_AES128_IV_LEN;

  /* #20 Start Aes128 Cbc streaming of content data */
  availableBufferLen = tcpSegLen;
  retVal |= TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound(TlsConIdx, &tcpSegPtr[ciphertextOutLen],
                                                                    &availableBufferLen);
  /* Update length of ciphertext */
  ciphertextOutLen += availableBufferLen;
  /* Reduce size of TCP segment with length of ciphertext */
  tcpSegLen -= availableBufferLen;

  /* #30 Encrypt MAC and padding directly into the TCP buffer */
  availableBufferLen = tcpSegLen;
  retVal |= TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt(TlsConIdx, &tcpSegPtr[ciphertextOutLen],
                                                             &availableBufferLen);

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcWithSingleCall() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  uint16                      BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate IV and set the CSM Key */
  retVal = TcpIp_TlsCoreCrypto_GenerateAEADGcmIv(TlsConIdx, BufPtr);

  if (retVal == E_OK)
  {
    uint32 availableBufferLen;
    uint32 authTagOffset;
    uint32 contentTypeOffset;
    uint32 authTagLen = TCPIP_TLS_AES128_GCM_AUTHTAG_LEN;
    uint8  authTag[TCPIP_TLS_AES128_GCM_AUTHTAG_LEN];

    /* Update buffer offsets considering the IV length */
    availableBufferLen = (uint32)BufLength - TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;
    contentTypeOffset = TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;

    /* #20 Perform Aes128 Gcm encryption, generate authentication tag */
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound(TlsConIdx, &BufPtr[contentTypeOffset], &availableBufferLen, authTag, &authTagLen);

    if (retVal == E_OK)
    {
      authTagOffset = contentTypeOffset + availableBufferLen;

      /* #30 Copy the authentication tag into the TcpIp buffer */
      VStdMemCpy(&BufPtr[authTagOffset], authTag, authTagLen);                                                          /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Done, RL message completely inside TcpIpBuffer */
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherAEADEncryptAes128GcmWithSingleCall() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                 retVal = E_NOT_OK;
  uint8                          tmpAesIv[TCPIP_TLS_AES128_IV_LEN];

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT((*TcpSeg1LenPtr + *TcpSeg2LenPtr) >= TCPIP_TLS_AES128_IV_LEN);

  /* #10 Generate Aes Iv and set it to the CSM Key, and copy into the TcpIp buffer */
  if (TcpIp_TlsCoreCrypto_GenerateAesIv(TlsConIdx, tmpAesIv) == E_OK)
  {
    retVal = E_OK;

    /* Copy the generated Iv into TcpIpBuffer, considering TcpIp buffer wraparound */
    if (*TcpSeg1LenPtr < TCPIP_TLS_AES128_IV_LEN)
    {
      uint8 remainingIvInSeg2 = (uint8)(TCPIP_TLS_AES128_IV_LEN - *TcpSeg1LenPtr);

      /* If TcpIp buffer wraps around before Iv length, split and copy to TcpIp buffer */
      VStdMemCpy(TcpSeg1Ptr, &tmpAesIv[0], *TcpSeg1LenPtr);                                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(TcpSeg2Ptr, &tmpAesIv[*TcpSeg1LenPtr], remainingIvInSeg2);                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      *TcpSeg2LenPtr = remainingIvInSeg2;
    }
    else
    {
      /* If Iv fits into space before TcpIp buffer wraparound, copy directly */
      VStdMemCpy(TcpSeg1Ptr, &tmpAesIv[0], TCPIP_TLS_AES128_IV_LEN);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      *TcpSeg1LenPtr = TCPIP_TLS_AES128_IV_LEN;
      *TcpSeg2LenPtr = 0u;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherGenAndCopyAes128CbcIv */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                 retVal = E_NOT_OK;
  uint8                          tmpGcmIv[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN];

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT((*TcpSeg1LenPtr + *TcpSeg2LenPtr) >= TCPIP_TLS_AES128_IV_LEN);

  /* #10 Generate Gcm IV and set it to the CSM Key, and copy into the TcpIp buffer */
  if (TcpIp_TlsCoreCrypto_GenerateAEADGcmIv(TlsConIdx, &tmpGcmIv[0]) == E_OK)
  {
    retVal = E_OK;

    /* Copy the generated Iv into TcpIpBuffer, considering TcpIp buffer wraparound */
    if (*TcpSeg1LenPtr < TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN)
    {
      uint8 remainingIvInSeg2 = (uint8)(TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN - *TcpSeg1LenPtr);

      /* If TcpIp buffer wraps around before Iv length, split and copy to TcpIp buffer */
      VStdMemCpy(TcpSeg1Ptr, &tmpGcmIv[0], *TcpSeg1LenPtr);                                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(TcpSeg2Ptr, &tmpGcmIv[*TcpSeg1LenPtr], remainingIvInSeg2);                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      *TcpSeg2LenPtr = remainingIvInSeg2;
    }
    else
    {
      /* If Iv fits into space before TcpIp buffer wraparound, copy directly */
      VStdMemCpy(TcpSeg1Ptr, &tmpGcmIv[0], TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN);                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      *TcpSeg1LenPtr = TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;
      *TcpSeg2LenPtr = 0u;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherAEADGenAndCopyAes128GcmIv */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                 retVal;
  TcpIp_SizeOfTlsBufferMgmtType  tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32                         plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the provided buffer and start Aes128 Cbc streaming of content data */
  if (*TcpIpSeg1LenPtr == 0u)
  {
    /* Scenario 1: Encrypt the data into the second segment */
    retVal = TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound(TlsConIdx, TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
    *TcpIpSeg1LenPtr = 0u;
  }
  else if (*TcpIpSeg1LenPtr >= plaintextDataLen)
  {
    /* Scenario 2: Encrypt the data into the first segment */
    retVal = TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr);
    *TcpIpSeg2LenPtr = 0u;
  }
  else
  {
    /* Scenario 3: Encrypt the data into both segments */
    retVal = TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
               TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAes128CbcContentData */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                  retVal;
  TcpIp_SizeOfTlsBufferMgmtType   tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32                          plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the provided buffer and Aes128 Gcm encrypt the content data */
  if (*TcpIpSeg1LenPtr == 0u)
  {
    /* Scenario 1: Encrypt the data into the second segment */
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound(TlsConIdx, TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr,
               AuthTagLenPtr);
    *TcpIpSeg1LenPtr = 0u;
  }
  else if (*TcpIpSeg1LenPtr > (plaintextDataLen + TCPIP_TLS_AES128_BLOCKSIZE))
  {
    /* Scenario 2: Encrypt the data into the first segment */
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, AuthTagPtr,
               AuthTagLenPtr);
    *TcpIpSeg2LenPtr = 0u;
  }
  else /* if (*TcpIpSeg1LenPtr < (plaintextDataLen + TCPIP_TLS_AES128_BLOCKSIZE) */
  {
    /* Scenario 3: Encrypt the data into both the segments */
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
               TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr, AuthTagLenPtr);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_TxCipherEncryptAEADAes128GcmContentData */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                 csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType  tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                         encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx = TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(
                                                                  tlsBufferMgmtIdx);
  TCPIP_P2C(uint8)               plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32                         plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32                         availableSpaceSeg1 = *TcpIpSeg1LenPtr;
  uint32                         availableSpaceSeg2 = *TcpIpSeg2LenPtr;
  uint32                         contentDataOffset;
  uint32                         contentDataRemaining = plaintextDataLen;
  uint32                         encDataSeg1Offset;
  uint32                         encDataSeg2Offset = 0u;
  uint32                         seg2BufLen = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Encrypt the content data present in TLS buffer into the provided Tcp buffer segments */
  /* Encrypt plaintext in TLS Tx buffer that fits into the TCP segment 1 */
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, *TcpIpSeg1LenPtr, TcpIpSeg1Ptr, &availableSpaceSeg1);
  /* The variable availableSpaceSeg1 now contains the length of encrypted data generated so far. */
  contentDataOffset = *TcpIpSeg1LenPtr;
  contentDataRemaining -= *TcpIpSeg1LenPtr;
  encDataSeg1Offset = availableSpaceSeg1;
  availableSpaceSeg1 = *TcpIpSeg1LenPtr - availableSpaceSeg1;

  /* Encrypt 32 byte chunks of data until the first segment is filled or all content is consumed */
  while (   (availableSpaceSeg1 > 0u)
         && (contentDataRemaining > 0u))
  {
    uint8 tmpBuffer[TCPIP_TLS_AES128_BLOCKSIZE * 2u];
    uint8 tmpBufLen = (contentDataRemaining > (TCPIP_TLS_AES128_BLOCKSIZE * 2u)) ? (uint8)(TCPIP_TLS_AES128_BLOCKSIZE * 2u) : (uint8)contentDataRemaining;
    uint32 availableSpaceTmpBuf = TCPIP_TLS_AES128_BLOCKSIZE * 2u;

    /* Encrypt the data into a temp buffer */
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &plaintextDataPtr[contentDataOffset], tmpBufLen, &tmpBuffer[0], &availableSpaceTmpBuf);
    contentDataOffset += tmpBufLen;
    contentDataRemaining -= tmpBufLen;

    if (availableSpaceTmpBuf <= availableSpaceSeg1)
    {
      /* Copy the encrypted data into the first segment */
      VStdMemCpy(&TcpIpSeg1Ptr[encDataSeg1Offset], &tmpBuffer[0], availableSpaceTmpBuf);                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      encDataSeg1Offset += availableSpaceTmpBuf;
      availableSpaceSeg1 -= availableSpaceTmpBuf;
    }
    else
    {
      /* Copy the encrypted data into the two segments */
      VStdMemCpy(&TcpIpSeg1Ptr[encDataSeg1Offset], &tmpBuffer[0], availableSpaceSeg1);                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &tmpBuffer[availableSpaceSeg1], (availableSpaceTmpBuf - availableSpaceSeg1));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      availableSpaceSeg2 -= (availableSpaceTmpBuf - availableSpaceSeg1);
      encDataSeg2Offset = (availableSpaceTmpBuf - availableSpaceSeg1);
      seg2BufLen += (availableSpaceTmpBuf - availableSpaceSeg1);
      availableSpaceSeg1 = 0u;
    }
  }

  /* If more data is remaining, encrypt directly to the second segment */
  if (contentDataRemaining > 0u)
  {
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &plaintextDataPtr[contentDataOffset], contentDataRemaining, &TcpIpSeg2Ptr[encDataSeg2Offset], &availableSpaceSeg2);
    seg2BufLen += availableSpaceSeg2;
  }

  /* Update the actual buffer size of the segments */
  *TcpIpSeg1LenPtr -= availableSpaceSeg1;
  *TcpIpSeg2LenPtr = seg2BufLen;

  return csmRetVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithoutTlsWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithoutTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                        csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType                  tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                                          encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(
                                                                      activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx = TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(
                                                                      tlsBufferMgmtIdx);
  TCPIP_P2C(uint8)                             plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32                          plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32                                       availableSpaceSeg1 = *TcpIpSeg1LenPtr;
  uint32                                       availableSpaceSeg2 = *TcpIpSeg2LenPtr;
  uint32                                        contentDataOffset = 0u;
  uint32                                     contentDataRemaining = plaintextDataLen;
  uint32                                        encDataSeg1Offset = 0u;
  uint32                                        encDataSeg2Offset = 0u;
  uint32                                               seg2BufLen = 0u;
  boolean                                            finishedFlag = FALSE;
  uint64                                             seqNum = TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
  uint8                    addAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN];
  TCPIP_P2C(uint8)         addAuthDataPtr = addAuthData;
  uint32                   addAuthDataLen = TCPIP_TLS_AES128_GCM_AADATA_LEN;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the AAD and Aes 128 encrypt the content data into the two TcpIp segments */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(seqNum,
                                        (uint16)TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
                                        TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), addAuthData);

  /* Check if there is enough space in the first segment to start streaming */
  if (availableSpaceSeg1 > TCPIP_TLS_AES128_BLOCKSIZE)
  {
    /* Feed one block less to start streaming */
    uint32 seg1Len = *TcpIpSeg1LenPtr - TCPIP_TLS_AES128_BLOCKSIZE;

    /* Encrypt data which can fit into the first segment */
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, seg1Len,
      addAuthDataPtr, addAuthDataLen, TcpIpSeg1Ptr, &availableSpaceSeg1, AuthTagPtr, AuthTagLenPtr);
    contentDataOffset = seg1Len;
    contentDataRemaining -= seg1Len;
    encDataSeg1Offset = availableSpaceSeg1;
    availableSpaceSeg1 = *TcpIpSeg1LenPtr - availableSpaceSeg1;
    /* Aad has been loaded into Csm */
    addAuthDataPtr = NULL_PTR;
    addAuthDataLen = 0;
  }
  else
  {
    /* Start encryption without feeding in any plaintext */
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_START, NULL_PTR, 0u,
                                NULL_PTR, 0u, NULL_PTR, NULL_PTR, AuthTagPtr, AuthTagLenPtr);
  }

  /* Encrypt 32 byte chunks of data until the first segment is filled up or all plaintext has been consumed */
  do
  {
    uint8 tmpBuffer[(TCPIP_TLS_AES128_BLOCKSIZE * 4u)];
    uint8 tmpBufLen =   (contentDataRemaining > (TCPIP_TLS_AES128_BLOCKSIZE * 2u))
                      ? (uint8)(TCPIP_TLS_AES128_BLOCKSIZE * 2u)
                      : (uint8)contentDataRemaining;
    uint32 availableSpaceTmpBuf = (TCPIP_TLS_AES128_BLOCKSIZE * 4u);

    /* Check if all data has been consumed, and encrypt chunks of 32 bytes into temp buffer */
    if (contentDataRemaining > 0u)
    {
      csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &plaintextDataPtr[contentDataOffset],
        tmpBufLen, addAuthDataPtr, addAuthDataLen, &tmpBuffer[0], &availableSpaceTmpBuf, AuthTagPtr, AuthTagLenPtr);
      contentDataOffset += tmpBufLen;
      contentDataRemaining -= tmpBufLen;
      /* Aad has been loaded into Csm */
      addAuthDataPtr = NULL_PTR;
      addAuthDataLen = 0;
    }
    else
    {
      /* All plaintext has been consumed, stop streaming and extract the remaining ciphertext */
      csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, NULL_PTR, 0u,
                      &tmpBuffer[0], &availableSpaceTmpBuf, AuthTagPtr, AuthTagLenPtr);
      /* Set streaming finished flag */
      finishedFlag = TRUE;
    }

    /* Copy the encrypted data from temp buffer into the provided segments */
    if (availableSpaceTmpBuf <= availableSpaceSeg1)
    {
      VStdMemCpy(&TcpIpSeg1Ptr[encDataSeg1Offset], &tmpBuffer[0], availableSpaceTmpBuf);                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      encDataSeg1Offset += availableSpaceTmpBuf;
      availableSpaceSeg1 -= availableSpaceTmpBuf;
    }
    else
    {
      VStdMemCpy(&TcpIpSeg1Ptr[encDataSeg1Offset], &tmpBuffer[0], availableSpaceSeg1);                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &tmpBuffer[availableSpaceSeg1], (availableSpaceTmpBuf - availableSpaceSeg1));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      availableSpaceSeg2 -= (availableSpaceTmpBuf - availableSpaceSeg1);
      encDataSeg2Offset = (availableSpaceTmpBuf - availableSpaceSeg1);
      seg2BufLen += (availableSpaceTmpBuf - availableSpaceSeg1);
      availableSpaceSeg1 = 0u;
    }

    /* If streaming is complete, break */
  } while ((availableSpaceSeg1 > 0u) && (finishedFlag == FALSE));

  /* Encrypt rest of plaintext data if available, and stop streaming */
  if (contentDataRemaining > 0u)
  {
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      &plaintextDataPtr[contentDataOffset], contentDataRemaining, NULL_PTR, 0u, &TcpIpSeg2Ptr[encDataSeg2Offset],
      &availableSpaceSeg2, AuthTagPtr, AuthTagLenPtr);
    seg2BufLen += availableSpaceSeg2;
  }
  else if (finishedFlag == FALSE)
  {
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u,
      NULL_PTR, 0u, &TcpIpSeg2Ptr[encDataSeg2Offset], &availableSpaceSeg2, AuthTagPtr, AuthTagLenPtr);
    seg2BufLen += availableSpaceSeg2;
  }
  else
  {
    /* Streaming is finished, nothing to do */
  }

  /* Update the actual buffer size of the segments */
  *TcpIpSeg1LenPtr -= availableSpaceSeg1;
  *TcpIpSeg2LenPtr = seg2BufLen;

  return csmRetVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithoutTlsWraparound */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType  rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* Length of TLS segment 1 */
  uint32  tlsSeg1Len = ((uint32)txBufferEndIdx - rlSendIdx);
  Std_ReturnType csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on where the wraparound is, invoke the encrypt function */
  if (tlsSeg1Len <= *TcpIpSeg1LenPtr)
  {
    /* TLS wraparound before or at TCP wraparound */
    csmRetVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
      TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
  }
  else
  {
    /* TLS wraparound after TCP wraparound */
    csmRetVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
      TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
  }

  return csmRetVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6010, 6030, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                               csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType         tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                                          encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* Total size of plaintext remaining in TLS Tx buffer */
  uint32 plaintextRemainingLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Length of free space in TCP segment 1 */
  uint32 tcpSeg1Len = *TcpIpSeg1LenPtr;
  /* Length of free space in TCP segment 2 */
  uint32 tcpSeg2Len = *TcpIpSeg2LenPtr;
  /* Length of plaintext consumed from TLS buffer segment 2 */
  uint32 plaintextConsumedTlsSeg2Len = 0u;                                                                              /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  /* Length of ciphertext in TCP segment 1 */
  uint32 ciphertextInTcpSeg1Len = 0u;                                                                                   /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  /* Length of ciphertext in TCP segment 2 */
  uint32 ciphertextInTcpSeg2Len = 0u;
  /* Pointer to TLS Tx buffer segment 1 */
  TCPIP_P2C(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  /* Length of TLS segment 1 */
  uint32  tlsSeg1Len = ((uint32)txBufferEndIdx - rlSendIdx);
  /* Pointer to TLS Tx buffer segment 2 */
  TCPIP_P2C(uint8) tlsSeg2Ptr;
  /* Length of the output buffer for the next Csm encrypt call */
  uint32 ciphertextOutBufLen;

  /* ----- Implementation ----------------------------------------------- */
  /* TLS wraparound before or at TCP wraparound */
  TCPIP_ASSERT(tlsSeg1Len <= *TcpIpSeg1LenPtr);

  /* #10 If TLS wraparound is before or at TCP wraparound, start by consuming plaintext in TLS segment 1 into TCP segment 1 */
  ciphertextOutBufLen = tcpSeg1Len;
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, tlsSeg1Ptr, tlsSeg1Len,
    TcpIpSeg1Ptr, &ciphertextOutBufLen);
  /* Update size of plaintext remaining */
  plaintextRemainingLen -= tlsSeg1Len;
  /* Update length of ciphertext in TCP segment 1 */
  ciphertextInTcpSeg1Len = ciphertextOutBufLen;
  /* Update length of TCP segment 1 */
  tcpSeg1Len -= ciphertextOutBufLen;

  /* Wraparound TLS buffer since all plaintext in TLS segment 1 has been consumed */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
  /* No plaintext consumed from TLS segment 2 so far */
  plaintextConsumedTlsSeg2Len = 0;

  /* If there is more than 1 block of space in TCP segment 1, and there is more than 1 block of plaintext to encrypt,
     encrypt sufficient plaintext from TLS segment 2 so that only 1-2 block of space is left in TCP segment 1
   */
  if (   (tcpSeg1Len > TCPIP_TLS_AES128_BLOCKSIZE)
      && (plaintextRemainingLen > TCPIP_TLS_AES128_BLOCKSIZE))
  {
    /* Calculate plaintext to consume from TLS buffer segment 2 */
    uint32 bytesToConsume = (plaintextRemainingLen > tcpSeg1Len) ? tcpSeg1Len : plaintextRemainingLen;
    /* Consume one block less plaintext */
    bytesToConsume -= TCPIP_TLS_AES128_BLOCKSIZE;

    /* Encrypt plaintext in TLS segment 2 into remaining space in TCP segment 1 */
    ciphertextOutBufLen = tcpSeg1Len;
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg2Ptr[plaintextConsumedTlsSeg2Len],
      bytesToConsume, &TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &ciphertextOutBufLen);
    /* Update plaintext consumed from TLS segment 2 */
    plaintextConsumedTlsSeg2Len = bytesToConsume;
    /* Update total plaintext remaining */
    plaintextRemainingLen -= bytesToConsume;
    /* Update the offset of ciphertext in TCP segment 1 */
    ciphertextInTcpSeg1Len += ciphertextOutBufLen;
    /* Update length of TCP segment 1 */
    tcpSeg1Len -= ciphertextOutBufLen;
  }

  /* At this point, TCP segment 1 has 1 or 2 blocks of space remaining.
     Use temporary buffer to encrypt plaintext from TLS segment 2
     till TCP segment 1 is filled up.
   */
  while ((tcpSeg1Len > 0u)
    && (plaintextRemainingLen > 0u))
  {
    /* Temporary buffer to store ciphertext */
    uint8 tmpBuffer[TCPIP_TLS_MIN_BUFFER_SIZE];
    /* Length of temporary buffer */
    uint32 tmpBufferLen = TCPIP_TLS_MIN_BUFFER_SIZE;
    /* Plaintext to consume from TLS segment 2 */
    uint32 plaintextToConsume = (plaintextRemainingLen > TCPIP_TLS_MIN_BUFFER_SIZE)
      ? TCPIP_TLS_MIN_BUFFER_SIZE
      : plaintextRemainingLen;

    /* Encrypt plaintext in TLS segment 2 into temp buffer */
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg2Ptr[plaintextConsumedTlsSeg2Len],
      plaintextToConsume, tmpBuffer, &tmpBufferLen);
    /* Update plaintext consumed from TLS segment 2 */
    plaintextConsumedTlsSeg2Len += plaintextToConsume;
    /* Update plaintext remaining to be encrypted */
    plaintextRemainingLen -= plaintextToConsume;

    /* Copy ciphertext from temp buffer into TCP segments */
    if (tmpBufferLen <= tcpSeg1Len)
    {
      /* More space remaining in TCP segment 1, copy all plaintext directly to TCP segment 1 */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tmpBufferLen);                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update the offset of ciphertext in TCP segment 1 */
      ciphertextInTcpSeg1Len += tmpBufferLen;
      /* Update length of TCP segment 1 */
      tcpSeg1Len -= tmpBufferLen;
    }
    else
    {
      /* TCP segment 1 is almost full, split ciphertext into both TCP segments */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tcpSeg1Len);                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &tmpBuffer[tcpSeg1Len], (tmpBufferLen - tcpSeg1Len));                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update available space in TCP segment 2 */
      tcpSeg2Len -= (tmpBufferLen - tcpSeg1Len);
      /* Update size of plaintext in TCP segment 2 */
      ciphertextInTcpSeg2Len = (tmpBufferLen - tcpSeg1Len);
      /* TCP segment 1 is full, break the while loop */
      tcpSeg1Len = 0u;
    }
  } /* while */

  /* If more plaintext remaining, encrypt directly into TCP segment 2 */
  if (plaintextRemainingLen > 0u)
  {
    /* Encrypt remaining plaintext into TCP segment 2 */
    ciphertextOutBufLen = tcpSeg2Len;
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg2Ptr[plaintextConsumedTlsSeg2Len],
      plaintextRemainingLen, &TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &ciphertextOutBufLen);
    /* Update size of plaintext in TCP segment 2 */
    ciphertextInTcpSeg2Len += ciphertextOutBufLen;
  }

  /* Update the actual buffer size of the segments */
  *TcpIpSeg1LenPtr -= tcpSeg1Len;
  *TcpIpSeg2LenPtr = ciphertextInTcpSeg2Len;

  return csmRetVal; /*lint !e550 */
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario1 */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6010, 6030, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                               csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType         tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                                          encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx =
                                                         TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
                                                           TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferStartIdx =
                                                         TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* Length of plaintext in TLS Tx buffer */
  uint32 totalPlaintextRemainingLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Pointer to TLS Tx buffer segment 1 */
  TCPIP_P2C(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  /* Length of TLS segment 1 */
  uint32 tlsSeg1Len = ((uint32)txBufferEndIdx - rlSendIdx);
  /* Flag to indicate TLS wraparound */
  boolean switchTlswrapround = FALSE;
  /* Size of TCP segment 1 */
  uint32 tcpSeg1Len = *TcpIpSeg1LenPtr;
  /* Size of TCP segment 2 */
  uint32 tcpSeg2Len = *TcpIpSeg2LenPtr;
  /* Offset of plaintext consumed from TLS buffer segment */
  uint32 plaintextInTlsSegOffset = 0u;                                                                                  /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  /* Length of ciphertext in TCP segment 1 */
  uint32 ciphertextInTcpSeg1Len;
  /* Length of ciphertext in TCP segment 1 */
  uint32 ciphertextInTcpSeg2Len = 0u;
  /* Pointer to TLS Tx buffer segment 2 */
  TCPIP_P2C(uint8) tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
  /* Length of the ciphertext buffer for next Csm encrypt call */
  uint32             ciphertextOutBufLen;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(tlsSeg1Len > *TcpIpSeg1LenPtr);
  /* #10 TLS wraparound is after TCP wraparound, encrypt plaintext in TLS segment 1 that fits into TCP segment 1 */
  ciphertextOutBufLen = tcpSeg1Len;
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, tlsSeg1Ptr, *TcpIpSeg1LenPtr,
                TcpIpSeg1Ptr, &ciphertextOutBufLen);
  /* Update size of TLS segment 1 */
  tlsSeg1Len -= *TcpIpSeg1LenPtr;
  /* Update the length of plaintext data consumed from TLS segment 1 */
  plaintextInTlsSegOffset = *TcpIpSeg1LenPtr;
  /* Update plaintext remaining to be encrypted */
  totalPlaintextRemainingLen -= *TcpIpSeg1LenPtr;
  /* Update length of ciphertext in TCP segment 1 */
  ciphertextInTcpSeg1Len = ciphertextOutBufLen;
  /* Update length of TCP segment 1 */
  tcpSeg1Len -= ciphertextOutBufLen;

  /* At this point there is 1-2 blocks of space remaining in TCP segment 1
     Use temporary buffer to encrypt 4 blocks of plaintext until all space
     in TCP segment is filled
  */
  while (   (tcpSeg1Len > 0u)
         && (totalPlaintextRemainingLen > 0u))
  {
    /* Temporary buffer to encrypt plaintext from TLS buffer */
    uint8 tmpBuffer[TCPIP_TLS_AES128_BLOCKSIZE * 2u];
    /* Pointer to the corresponding TLS segment (1 or 2) */
    TCPIP_P2C(uint8) plaintextPtr;
    /* Length of plaintext to encrypt in next Csm call */
    uint32 plaintextLen;

    /* Determine the next TLS segment to extract plaintext from, depending on TLS wraparound */
    if ((switchTlswrapround == FALSE)
      && (tlsSeg1Len == 0u))
    {
      /* TLS buffer wraparound, extract plaintext from TLS segment 2 */
      /* Indicate TLS has wrapped around */
      switchTlswrapround = TRUE;
      /* Reset the plaintext offset for TLS segment 2 */
      plaintextInTlsSegOffset = 0;
      /* Start extracting plaintext from TLS segment 2 */
      plaintextPtr = &tlsSeg2Ptr[plaintextInTlsSegOffset];
    }
    else if (tlsSeg1Len != 0u)
    {
      /* Plaintext remaining before wraparound, extract plaintext from TLS segment 1 */
      plaintextPtr = &tlsSeg1Ptr[plaintextInTlsSegOffset];
    }
    else
    {
      /* Extract plaintext from TLS segment 2 */
      plaintextPtr = &tlsSeg2Ptr[plaintextInTlsSegOffset];
    }

    /* Calculate how much plaintext can be encrypted */
    if (tlsSeg1Len != 0u)
    {
      /* If plaintext remaining in TLS segment 1, consume it */
      plaintextLen =   (tlsSeg1Len > (TCPIP_TLS_AES128_BLOCKSIZE * 2u))
                  ? (TCPIP_TLS_AES128_BLOCKSIZE * 2u)
                  : tlsSeg1Len;
    }
    else
    {
      /* Plaintext in TLS segment 2, consume as much possible */
      plaintextLen =   (totalPlaintextRemainingLen > (TCPIP_TLS_AES128_BLOCKSIZE * 2u))
                  ? (TCPIP_TLS_AES128_BLOCKSIZE * 2u)
                  : totalPlaintextRemainingLen;
    }

    /* Encrypt plaintext from TLS segment 2 into temp buffer */
    ciphertextOutBufLen = TCPIP_TLS_AES128_BLOCKSIZE * 2u;
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, plaintextPtr,
                             plaintextLen, tmpBuffer, &ciphertextOutBufLen);
    /* Update size of ciphertext in TCP segment */
    plaintextInTlsSegOffset += plaintextLen;
    /* Update remaining plaintext to be consumed */
    totalPlaintextRemainingLen -= plaintextLen;

    /* Update the plaintext remaining in TLS segment 1 */
    if (tlsSeg1Len != 0u)
    {
      tlsSeg1Len -= plaintextLen;
    }

    /* Copy the encrypted data into the TcpIp segments, and update offsets */
    if (ciphertextOutBufLen <= tcpSeg1Len)
    {
      /* More space remaining in TCP segment 1, copy all plaintext directly to TCP segment 1 */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], ciphertextOutBufLen);                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update size of ciphertext in TCP segment 1 */
      ciphertextInTcpSeg1Len += ciphertextOutBufLen;
      tcpSeg1Len -= ciphertextOutBufLen;
    }
    else
    {
      /* TCP segment 1 is almost full, split ciphertext into both TCP segments */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tcpSeg1Len);                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &tmpBuffer[tcpSeg1Len], (ciphertextOutBufLen - tcpSeg1Len));                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      tcpSeg2Len -= (ciphertextOutBufLen - tcpSeg1Len);
      /* Update size of ciphertext in TCP segment 2 */
      ciphertextInTcpSeg2Len = (ciphertextOutBufLen - tcpSeg1Len);
      tcpSeg1Len = 0u;
    }
  } /* while */

  /* If plaintext remaining in TLS segment 1, encrypt directly into TCP segment 2 */
  if (tlsSeg1Len > 0u)
  {
    uint32 consumedBytes = tcpSeg2Len;
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg1Ptr[plaintextInTlsSegOffset],
                             tlsSeg1Len, &TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &consumedBytes);
    ciphertextInTcpSeg2Len += consumedBytes;
    totalPlaintextRemainingLen -= tlsSeg1Len;
    tcpSeg2Len -= consumedBytes;

    /* Wrap around Tls buffer */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
    plaintextInTlsSegOffset = 0u;
  }
  else if (switchTlswrapround == FALSE)
  {
    /* TLS buffer has wrapped around, point to TLS segment 2 */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
    plaintextInTlsSegOffset = 0u;
  }
  else
  {
   /* nothing to do - TLS buffer has already wrapped around */
  }

  /* Encrypt remaining plaintext in TLS segment 2, encrypt directly into TCP segment 2 */
  if (totalPlaintextRemainingLen > 0u)
  {
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg2Ptr[plaintextInTlsSegOffset],
                   totalPlaintextRemainingLen, &TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &tcpSeg2Len);
    ciphertextInTcpSeg2Len += tcpSeg2Len;
  }

  /* Update the actual buffer size of the segments */
  *TcpIpSeg1LenPtr -= tcpSeg1Len;
  *TcpIpSeg2LenPtr = ciphertextInTcpSeg2Len;

  return csmRetVal; /*lint !e550 */
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparoundScenario2 */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTlsWraparound
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
/* PRQA S 6010, 6030, 6050, 6060 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTlsWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                               csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType         tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* Total remaining plaintext in TLS buffer */
  uint32 plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Indicates if TLS buffer has wrapped around */
  boolean switchTlswrapround = FALSE;
  /* Actual length of TCP segment 1 */
  uint32 tcpSeg1Len = *TcpIpSeg1LenPtr;
  /* Actual length of TCP segment 2 */
  uint32 tcpSeg2Len = *TcpIpSeg2LenPtr;
  /* Plaintext consumed from TLS segment 1 */
  uint32 plaintextConsumedTlsSeg1Len = 0u;
  /* Pointer to TLS segment 1 */
  TCPIP_P2C(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  /* Pointer to TLS segment 2 */
  TCPIP_P2C(uint8) tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
  /* Length of ciphertext in TCP segment 1 */
  uint32 ciphertextInTcpSeg1Len = 0u;
  /* Length of ciphertext in TCP segment 2 */
  uint32 ciphertextInTcpSeg2Len = 0u;
  /* Length of TLS segment 1 */
  uint32 tlsSeg1Len = ((uint32)txBufferEndIdx - rlSendIdx);
  /* TLS sequence number */
  uint64 seqNum = TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
  /* Temporary buffer */
  uint8 tmpBuffer[TCPIP_TLS_MIN_BUFFER_SIZE];
  /* Temp buffer length */
  uint32 tmpBufLen;
  /* AAD buffer */
  uint8 aadAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN];
  /* Pointer to the AAD buffer */
  TCPIP_P2C(uint8)         aadAuthDataPtr = &aadAuthData[0];
  /* Expected length of AAD */
  uint32 aadAuthDataLen = TCPIP_TLS_AES128_GCM_AADATA_LEN;
  /* Length of the ciphertext output buffer for next Csm call */
  uint32 ciphertextOutBufLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the AAD */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(seqNum,
    (uint16)TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
    TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), aadAuthData);

  /* For Aes128 Gcm, the destination buffer should be at least one block more than the data buffer */

  /* #20 Start Aes128 Gcm streaming, and encrypt data before TLS wrap around if possible */
  if ((tlsSeg1Len + TCPIP_TLS_AES128_BLOCKSIZE) < tcpSeg1Len)
  {
    /* Encrypt all data before TLS wraparound */
    ciphertextOutBufLen = tcpSeg1Len;
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, tlsSeg1Ptr, tlsSeg1Len,
      aadAuthDataPtr, aadAuthDataLen, TcpIpSeg1Ptr, &ciphertextOutBufLen, AuthTagPtr, AuthTagLenPtr);
    /* Update total remaining plaintext in TLS buffer */
    plaintextDataLen -= tlsSeg1Len;
    /* Update length of ciphertext in TCP segment 1 */
    ciphertextInTcpSeg1Len = ciphertextOutBufLen;
    /* Update the actual free length of TCP segment 1 */
    tcpSeg1Len -= ciphertextOutBufLen;
    /* No more plaintext in TLS segment 1 */
    tlsSeg1Len = 0u;
    /* Aad has been loaded */
    aadAuthDataPtr = NULL_PTR;
    aadAuthDataLen = 0u;
  }
  else if (tcpSeg1Len > TCPIP_TLS_AES128_BLOCKSIZE)
  {
    /* Encrypt as much plaintext possible into the TCP segment 1 */
    ciphertextOutBufLen = tcpSeg1Len;
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, tlsSeg1Ptr,
      (tcpSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE), aadAuthDataPtr, aadAuthDataLen, TcpIpSeg1Ptr, &ciphertextOutBufLen,
      AuthTagPtr, AuthTagLenPtr);
    /* Update remaining plaintext in TLS segment 1 */
    tlsSeg1Len -= (tcpSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE);
    /* Update plaintext consumed in TLS segment 1 */
    plaintextConsumedTlsSeg1Len = (tcpSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE);
    /* Update total remaining plaintext in TLS buffer */
    plaintextDataLen -= (tcpSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE);
    /* Update length of ciphertext in TCP segment 1 */
    ciphertextInTcpSeg1Len = ciphertextOutBufLen;
    /* Update the actual free length of TCP segment 1 */
    tcpSeg1Len -= ciphertextOutBufLen;
    /* Aad has been loaded */
    aadAuthDataPtr = NULL_PTR;
    aadAuthDataLen = 0u;
  }
  else
  {
    /* Start streaming without feeding any data */
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_START, NULL_PTR, 0,
      NULL_PTR, 0u, NULL_PTR, NULL_PTR, AuthTagPtr, AuthTagLenPtr);
  }

  /* #30 For remaining space in TCP segment 1, encrypt 32 byte chunks of data until TCP
         segment 1 is filled or all plaintext is consumed */
  while ((tcpSeg1Len > 0u)
    && (plaintextDataLen > 0u))
  {
    /* Pointer to next plaintext buffer to consume */
    TCPIP_P2C(uint8) plaintextPtr;
    /* Size of temp buffer */
    uint32 availableSpaceTmpBuf = TCPIP_TLS_MIN_BUFFER_SIZE;

    /* Calculate how much content data can be consumed */
    if (tlsSeg1Len != 0u)
    {
      tmpBufLen =   (tlsSeg1Len > (TCPIP_TLS_AES128_BLOCKSIZE * 2u))
                  ? (uint8)(TCPIP_TLS_AES128_BLOCKSIZE * 2u)
                  : (uint8)tlsSeg1Len;
    }
    else
    {
      tmpBufLen =   (plaintextDataLen > (TCPIP_TLS_AES128_BLOCKSIZE * 2u))
                  ? (uint8)(TCPIP_TLS_AES128_BLOCKSIZE * 2u)
                  : (uint8)plaintextDataLen;
    }

    /* Wrap around TLS buffer and update plaintext pointer, if necessary */
    if (   (switchTlswrapround == FALSE)
        && (tlsSeg1Len == 0u))
    {
      /* Wrap around TLS buffer and use TLS segment 2 */
      switchTlswrapround = TRUE;
      plaintextConsumedTlsSeg1Len = 0u;
      /* Update the plaintext pointer to TLS segment 2 */
      plaintextPtr = &tlsSeg2Ptr[0];
    }
    else if (tlsSeg1Len != 0u)
    {
      /* Update the plaintext pointer in TLS segment 1 */
      plaintextPtr = &tlsSeg1Ptr[plaintextConsumedTlsSeg1Len];
    }
    else
    {
      /* Update the plaintext pointer in TLS segment 2 */
      plaintextPtr = &tlsSeg2Ptr[plaintextConsumedTlsSeg1Len];
    }

    /* Encrypt plaintext into temporary buffer and copy into TCP segments */
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, plaintextPtr,
      tmpBufLen, aadAuthDataPtr, aadAuthDataLen, tmpBuffer, &availableSpaceTmpBuf, AuthTagPtr, AuthTagLenPtr);
    /* Update plaintext consumed from current TLS segment */
    plaintextConsumedTlsSeg1Len += tmpBufLen;
    /* Update plaintext remaining to be encrypted */
    plaintextDataLen -= tmpBufLen;
    /* Aad has been loaded */
    aadAuthDataPtr = NULL_PTR;
    aadAuthDataLen = 0u;
    /* Update the plaintext remaining in TLS segment 1 */
    if (tlsSeg1Len != 0u)
    {
      tlsSeg1Len -= tmpBufLen;
    }

    /* Copy the encrypted data into the TcpIp segments, and update offsets */
    if (availableSpaceTmpBuf <= tcpSeg1Len)
    {
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], availableSpaceTmpBuf);                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update actual ciphertext length in TCP segment 1 */
      ciphertextInTcpSeg1Len += availableSpaceTmpBuf;
      /* Update actual free length of TCP segment 1 */
      tcpSeg1Len -= availableSpaceTmpBuf;
    }
    else
    {
      uint32 ciphertextStoredInTcpSeg2Len = (availableSpaceTmpBuf - tcpSeg1Len);
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tcpSeg1Len);                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &tmpBuffer[tcpSeg1Len], ciphertextStoredInTcpSeg2Len);                               /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update actual ciphertext length in TCP segment 2 */
      ciphertextInTcpSeg2Len = ciphertextStoredInTcpSeg2Len;
      /* Update actual free length in TCP segment 2 */
      tcpSeg2Len -= ciphertextStoredInTcpSeg2Len;
      /* Update actual ciphertext length in TCP segment 1 */
      ciphertextInTcpSeg1Len += tcpSeg1Len;
      /* TCP segment 1 is filled */
      tcpSeg1Len = 0u;
    }
  }

  /* #40 If plaintext remaining before TLS buffer wraparound, encrypt directly to the second segment */
  if (tlsSeg1Len > 0u)
  {
    uint32 consumedBytes = tcpSeg2Len;
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, &tlsSeg1Ptr[plaintextConsumedTlsSeg1Len],
      tlsSeg1Len, aadAuthDataPtr, aadAuthDataLen, &TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &consumedBytes, AuthTagPtr,
      AuthTagLenPtr);
    /* Update actual ciphertext length in TCP segment 2 */
    ciphertextInTcpSeg2Len += consumedBytes;
    /* Update total remaining plaintext in TLS buffer */
    plaintextDataLen -= tlsSeg1Len;
    /* Update actual size of TCP segment 1 */
    tcpSeg2Len -= consumedBytes;
    /* Aad has been loaded */
    aadAuthDataPtr = NULL_PTR;
    aadAuthDataLen = 0u;
    /* Wrap around Tls buffer */
    plaintextConsumedTlsSeg1Len = 0;
  }
  else if (switchTlswrapround == FALSE)
  {
    /* Wrap around Tls buffer */
    plaintextConsumedTlsSeg1Len = 0;
  }
  else
  {
   /* nothing to do */
  }

  /* Encrypt rest of data into second segment, and stop Aes128 Gcm streaming */
  if (plaintextDataLen > 0u)
  {
    /* Encrypt remaining plaintext in TLS segment 2 directly into TCP segment 1 */
    ciphertextOutBufLen = tcpSeg2Len;
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      &tlsSeg2Ptr[plaintextConsumedTlsSeg1Len], plaintextDataLen, aadAuthDataPtr, aadAuthDataLen,
      &TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &ciphertextOutBufLen, AuthTagPtr, AuthTagLenPtr);
    ciphertextInTcpSeg2Len += ciphertextOutBufLen;

  }
  else
  {
    /* If no plaintext remaining, only 1-2 blocks of ciphertext remaining to be flushed out
       Encrypt into temporary buffer and copy into TCP segments
     */
    tmpBufLen = TCPIP_TLS_AES128_BLOCKSIZE * 2u;
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, NULL_PTR, 0u, tmpBuffer,
      &tmpBufLen, AuthTagPtr, AuthTagLenPtr);

    /* Copy the ciphertext from temp buffer into TCP segments */
    if (tcpSeg1Len == 0u)
    {
      /* If no space in TCP segment 1, copy into TCP segment 2 */
      VStdMemCpy(&TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &tmpBuffer[0u], tmpBufLen);                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update actual ciphertext length in TCP segment 2 */
      ciphertextInTcpSeg2Len += tmpBufLen;
    }
    else if (tcpSeg1Len < tmpBufLen)
    {
      /* Copy into TCP segments 1 and 2 */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tcpSeg1Len);                                     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[ciphertextInTcpSeg2Len], &tmpBuffer[tcpSeg1Len], (tmpBufLen - tcpSeg1Len));              /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update actual ciphertext length in TCP segment 2 */
      ciphertextInTcpSeg2Len += (tmpBufLen - tcpSeg1Len);
      /* Update actual ciphertext length in TCP segment 1 */
      ciphertextInTcpSeg1Len += tcpSeg1Len;
    }
    else
    {
      /* If enough space in TCP segment 1, copy into TCP segment 1 */
      VStdMemCpy(&TcpIpSeg1Ptr[ciphertextInTcpSeg1Len], &tmpBuffer[0], tmpBufLen);                                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      /* Update actual ciphertext length in TCP segment 1 */
      ciphertextInTcpSeg1Len += tmpBufLen;
    }
  }

  /* Update the actual buffer size of the segments */
  *TcpIpSeg1LenPtr = ciphertextInTcpSeg1Len;
  *TcpIpSeg2LenPtr = ciphertextInTcpSeg2Len;

  return csmRetVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTlsWraparound */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                    retVal;
  Std_ReturnType                                    csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType                     tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType  rlSendIdx =
                                                      TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType    txBufferEndIdx =
                                                      TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  uint32                                            plaintextDataLen =
                                                      TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is Tls buffer wraparound and encrypt content into the TcpIp buffer segments */
  if ((rlSendIdx + plaintextDataLen) <= txBufferEndIdx)
  {
    csmRetVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithoutTlsWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
  }
  else
  {
    csmRetVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTlsWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr, TcpIpSeg2LenPtr);
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                           retVal;
  Std_ReturnType                                        csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType                     tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  uint32                                       plaintextDataLen =
    TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a Tls buffer wraparound and encrypt content into the TcpIp buffer segments */
  if ((rlSendIdx + plaintextDataLen) <= txBufferEndIdx)
  {
    csmRetVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithoutTlsWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
      TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr, AuthTagLenPtr);
  }
  else
  {
    csmRetVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTlsWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr,
      TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr, AuthTagLenPtr);
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* rlSendIdx is in the range of the complete TlsBufferTx */
  /* #10 Invoke the encrypt function depending on the type of Rl content */
  switch (TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
  case TCPIP_TLS_CT_HS:
  case TCPIP_TLS_CT_AD:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHsWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr,
      TcpIpSeg2LenPtr);
    break;
  } /* case TCPIP_TLS_CT_HS | TCPIP_TLS_CT_AD */
  case TCPIP_TLS_CT_AL:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr,
      TcpIpSeg2LenPtr);
    break;
  } /* case TCPIP_TLS_CT_AL */
  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
  /* Default case left blank intentionally */
  break;
  } /* switch */
  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* rlSendIdx is in the range of the complete TlsBufferTx */
  /* #10 Invoke the encrypt function depending on the type of Rl content */
  switch (TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
  case TCPIP_TLS_CT_HS:
  case TCPIP_TLS_CT_AD:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHsWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr, AuthTagLenPtr);
    break;
  }
  case TCPIP_TLS_CT_AL:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound(TlsConIdx, TcpIpSeg1Ptr, TcpIpSeg1LenPtr, TcpIpSeg2Ptr, TcpIpSeg2LenPtr, AuthTagPtr, AuthTagLenPtr);
    break;
  }
  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    break;
  } /* switch */
  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* rlSendIdx is in the range of the complete TlsBufferTx */
  /* #10 Invoke the encrypt function depending on the type of Rl content */
  switch (TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
    case TCPIP_TLS_CT_HS:
    case TCPIP_TLS_CT_AD:
    {
      retVal = TcpIp_TlsCoreRl_EncryptAes128CbcAdHs(TlsConIdx, BufPtr, AvailableBufferLenPtr);
      break;
    } /* case TCPIP_TLS_CT_HS | TCPIP_TLS_CT_AD */
    case TCPIP_TLS_CT_AL:
    {
      retVal = TcpIp_TlsCoreRl_EncryptAes128CbcAl(TlsConIdx, BufPtr, AvailableBufferLenPtr);
      break;
    } /* case TCPIP_TLS_CT_AL */
    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
  /* Default case left blank intentionally */
      break;
  } /* switch */
  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcContentDataWoWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* rlSendIdx is in the range of the complete TlsBufferTx */
  /* #10 Invoke the encrypt function depending on the type of Rl content */
  switch (TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
  case TCPIP_TLS_CT_HS:
  case TCPIP_TLS_CT_AD:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs(TlsConIdx, BufPtr, AvailableBufferLenPtr, AuthTagPtr, AuthTagLenPtr);
    break;
  } /* case TCPIP_TLS_CT_HS | TCPIP_TLS_CT_AD */
  case TCPIP_TLS_CT_AL:
  {
    retVal = TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl(TlsConIdx, BufPtr, AvailableBufferLenPtr, AuthTagPtr, AuthTagLenPtr);
    break;
  } /* case TCPIP_TLS_CT_AL */
  default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    break;
  } /* switch */
  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmContentDataWoWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAdHs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                                  retVal;
  TcpIp_SizeOfTlsBufferMgmtType         tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                                          encryptionJobId =TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx =
                                                         TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType   txBufferEndIdx =
                                                           TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferStartIdx =
                                                         TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TCPIP_P2C(uint8)                             plaintextDataPtr =
                                                         TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32                                       plaintextDataLen =
                                                         TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /*#10 Start Aes128 Cbc streaming, and encrypt data into linear TCP buffer considering TLS wraparound */
  if ((rlSendIdx + plaintextDataLen) <= txBufferEndIdx)
  {
    /* Scenario 1: No TLS buffer wraparound */
    csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, plaintextDataLen,
      BufPtr, AvailableBufferLenPtr);
  }
  else
  {
    /* Scenario 2: TLS buffer wraparound */
    uint32 dataLenAtEndOfTxBuf   = ((uint32)txBufferEndIdx - rlSendIdx);
    uint32 dataLenAtStartOfTxBuf = (plaintextDataLen - dataLenAtEndOfTxBuf);
    uint32 tmpAvailableBufferLen = *AvailableBufferLenPtr;
    uint32 encryptedDataOffset;

    /* Feed the data till wraparound */
    csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, dataLenAtEndOfTxBuf,
      BufPtr, AvailableBufferLenPtr);
    encryptedDataOffset    = *AvailableBufferLenPtr;
    tmpAvailableBufferLen -= encryptedDataOffset;

    /* Wraparound the TLS buffer */
    plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);

    /* Feed rest of content data */
    csmRetVal |= TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE, plaintextDataPtr, dataLenAtStartOfTxBuf,
      &BufPtr[encryptedDataOffset], &tmpAvailableBufferLen);

    /* Update the actual size of encrypted data */
    *AvailableBufferLenPtr = (tmpAvailableBufferLen + encryptedDataOffset);
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0,
    TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAdHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(
  uint64                      TlsSeqNum,
  uint16                      ContentLen,
  uint8                       Type,
  TCPIP_P2V(uint8)            AddAuthDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                         type = Type;
  uint16                        version = ((uint16)(TCPIP_TLS_RL_VERSMAJOR) << 8u) | (uint16)(TCPIP_TLS_RL_VERSMINOR);
  uint16                        length = TCPIP_HTONS(ContentLen);

  /* ----- Implementation ----------------------------------------------- */
  /* Structure of the additional authentication data is -
   * |Seq No(8)       |type (1)|version(2)|length (2)|
   */
  /* #10 Generate the additional auth data and copy into provided buffer */
  /* Copy the sequence number to the authdata */

  IpBase_PutUint64(AddAuthDataPtr, TCPIP_TLS_ADD_SEQNUM_OFFSET, TlsSeqNum);

  /* Copy the type to the authdata */
  VStdMemCpy(&AddAuthDataPtr[TCPIP_TLS_ADD_TYPE_OFFSET], &type, TCPIP_TLS_ADD_TYPE_LEN);                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* Copy the version to the authdata */
  VStdMemCpy(&AddAuthDataPtr[TCPIP_TLS_ADD_VER_OFFSET], &version, TCPIP_TLS_ADD_VER_LEN);                               /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* Copy the length to the authdata */
  VStdMemCpy(&AddAuthDataPtr[TCPIP_TLS_ADD_LEN_OFFSET], &length, TCPIP_TLS_ADD_LEN_LEN);                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

} /* TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                                          encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType      rlSendIdx = TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(
                                                                      tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx   = TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(
                                                                      tlsBufferMgmtIdx);
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferStartIdx = TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(
                                                                      tlsBufferMgmtIdx);
  TCPIP_P2C(uint8)               plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32                         plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint64                         seqNum = TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
  Std_ReturnType                 csmRetVal;
  uint8                          addAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the AAD */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(seqNum, (uint16)plaintextDataLen,
     TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), addAuthData);

  /*#20 Perform Aes128 Gcm encryption of data into linear TcpIp buffer considering Tls wraparound */
  if ((rlSendIdx + plaintextDataLen) <= txBufferEndIdx)
  {
    /* Scenario 1: No Tls buffer wraparound */
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_SINGLECALL, plaintextDataPtr, plaintextDataLen,
      addAuthData, TCPIP_TLS_AES128_GCM_AADATA_LEN, BufPtr, AvailableBufferLenPtr, AuthTagPtr, AuthTagLenPtr);
  }
  else
  {
    /* Scenario 2: Tls buffer wraparound */
    uint32 dataLenAtEndOfTxBuf = ((uint32)txBufferEndIdx - rlSendIdx);
    uint32 dataLenAtStartOfTxBuf = (plaintextDataLen - dataLenAtEndOfTxBuf);
    uint32 tmpAvailableBufferLen = *AvailableBufferLenPtr;

    uint32 encryptedDataOffset;

    /* Feed the data till wraparound */
    csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, dataLenAtEndOfTxBuf,
      addAuthData, TCPIP_TLS_AES128_GCM_AADATA_LEN, BufPtr, AvailableBufferLenPtr, AuthTagPtr, AuthTagLenPtr);
    encryptedDataOffset = *AvailableBufferLenPtr;
    tmpAvailableBufferLen -= encryptedDataOffset;

    /* Wraparound the Tls buffer */
    plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);

    /* Feed the rest of the data */
    csmRetVal |= TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      plaintextDataPtr, dataLenAtStartOfTxBuf, NULL_PTR, 0u, &BufPtr[encryptedDataOffset], &tmpAvailableBufferLen,
      AuthTagPtr, AuthTagLenPtr);

    /* Update the actual size of encrypted data buffer */
    *AvailableBufferLenPtr = (tmpAvailableBufferLen + encryptedDataOffset);
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128GCM);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAdHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  TCPIP_P2V(uint32) AvailableBufferLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                         encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Start of the rl frame in the TX Buffer */

  TCPIP_P2C(uint8) plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32 plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType retVal;
  Std_ReturnType csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Encrypt the data into the provided buffer and check the operation result */
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, plaintextDataLen,
                          BufPtr, AvailableBufferLenPtr);

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Start of the rl frame in the TX Buffer */
  uint64 seqNum = TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
  TCPIP_P2C(uint8) plainTextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32 plainTextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType retVal;
  Std_ReturnType csmRetVal;
  uint8 addAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate the AAD */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(seqNum, (uint16)plainTextDataLen,
      TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), &addAuthData[0]);

  /* #20 Encrypt the data into the provided buffer and check the operation result */
  csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_SINGLECALL, plainTextDataPtr, plainTextDataLen,
    &addAuthData[0], TCPIP_TLS_AES128_GCM_AADATA_LEN, BufPtr, AvailableBufferLenPtr, AuthTagPtr, AuthTagLenPtr);

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpSeg2LenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TCPIP_P2C(uint8) plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  uint32 plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32 cipherTextDataLen = TCPIP_TLS_MIN_BUFFER_SIZE;
  Std_ReturnType retVal;
  Std_ReturnType csmRetVal;
  /* Temporary buffer to store the alert ciphertext */
  uint8 cipherTextBuffer[TCPIP_TLS_MIN_BUFFER_SIZE];

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(plaintextDataLen <= (*TcpSeg1LenPtr + *TcpSeg2LenPtr));

  /* #10 Start Aes128 Cbc streaming and encrypt alert data into the temp buffer */
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_STREAMSTART, plaintextDataPtr, plaintextDataLen,
    &cipherTextBuffer[0], &cipherTextDataLen);

  if (csmRetVal == E_OK)
  {
    TCPIP_ASSERT(cipherTextDataLen <= (*TcpSeg1LenPtr + *TcpSeg2LenPtr));

    /* Check if the ciphertext fits directly into TCP segment 1 or needs to be split */
    if (*TcpSeg1LenPtr < cipherTextDataLen)
    {
      VStdMemCpy(&TcpSeg1Ptr[0], &cipherTextBuffer[0], *TcpSeg1LenPtr);                                                 /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpSeg2Ptr[0], &cipherTextBuffer[*TcpSeg1LenPtr], (cipherTextDataLen - *TcpSeg1LenPtr));              /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Update TCP segment 2 length with the bytes filled */
      *TcpSeg2LenPtr = (cipherTextDataLen - *TcpSeg1LenPtr);
    }
    else
    {
      VStdMemCpy(&TcpSeg1Ptr[0u], &cipherTextBuffer[0], cipherTextDataLen);                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Update TCP segment 1 length with the bytes filled, set TCP segment 2 length to 0 since it is not used */
      *TcpSeg1LenPtr = cipherTextDataLen;
      *TcpSeg2LenPtr = 0u;
    }
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcAlWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            TcpIpSeg1Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg1LenPtr,
  TCPIP_P2V(uint8)            TcpIpSeg2Ptr,
  TCPIP_P2V(uint32)           TcpIpSeg2LenPtr,
  TCPIP_P2V(uint8)            AuthTagPtr,
  TCPIP_P2V(uint32)           AuthTagLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Current sendIdx */
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* TLS Buffer containing plaintext data */
  TCPIP_P2C(uint8) plaintextDataPtr = TcpIp_GetAddrTlsBufferTx(rlSendIdx);
  /* Length of plaintext data */
  uint32 plaintextDataLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Length of the alert ciphertext buffer */
  uint32 cipherTextDataLen = TCPIP_TLS_MIN_BUFFER_SIZE;
  /* TLS sequence number which is used as explicit IV */
  uint64 seqNum = TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
  Std_ReturnType csmRetVal;
  /* Buffer to store AAD */
  uint8 addAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN];
  /* Buffer to store the alert ciphertext temporarily */
  uint8 cipherTextBuffer[TCPIP_TLS_MIN_BUFFER_SIZE];

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(plaintextDataLen <= (*TcpIpSeg1LenPtr + *TcpIpSeg2LenPtr));

  /* #10 Generate the additional authentication data */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(seqNum, (uint16)plaintextDataLen,
        TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx), addAuthData);

  /* #20 Start Aes128 Gcm streaming and encrypt alert data into the TcpIp segments */
  csmRetVal = TCPIP_CSM_AEADEncrypt(encryptionJobId, CRYPTO_OPERATIONMODE_SINGLECALL, plaintextDataPtr, plaintextDataLen,
            &addAuthData[0], TCPIP_TLS_AES128_GCM_AADATA_LEN, cipherTextBuffer, &cipherTextDataLen, AuthTagPtr, AuthTagLenPtr);

  if (csmRetVal == E_OK)
  {
    TCPIP_ASSERT(cipherTextDataLen <= (*TcpIpSeg1LenPtr + *TcpIpSeg2LenPtr));

    /* Check if the ciphertext fits directly into TCP segment 1 or needs to be split */
    if (*TcpIpSeg1LenPtr < cipherTextDataLen)
    {
      VStdMemCpy(&TcpIpSeg1Ptr[0], &cipherTextBuffer[0], *TcpIpSeg1LenPtr);                                             /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(&TcpIpSeg2Ptr[0], &cipherTextBuffer[*TcpIpSeg1LenPtr], (cipherTextDataLen - *TcpIpSeg1LenPtr));        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Update TCP segment 2 length with the bytes filled */
      *TcpIpSeg2LenPtr = (cipherTextDataLen - *TcpIpSeg1LenPtr);
    }
    else
    {
      VStdMemCpy(&TcpIpSeg1Ptr[0u], &cipherTextBuffer[0], cipherTextDataLen);                                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

      /* Update TCP segment 1 length with the bytes filled, set TCP segment 2 length to 0 since it is not used */
      *TcpIpSeg1LenPtr = cipherTextDataLen;
      *TcpIpSeg2LenPtr = 0u;
    }
  }

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAEADAes128GcmAlWithTcpWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_GenerateAesIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreCrypto_GenerateAesIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            AesIvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 encryptionKeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate a new random IV value and set the corresponding key element */
  if (TcpIp_TlsCoreCrypto_GenerateIvRandomValue(TlsConIdx, &AesIvPtr[0], TCPIP_TLS_AES128_IV_LEN) == E_OK)
  {
    if (TcpIp_TlsCoreCrypto_SetIvValue(TlsConIdx, encryptionKeyId, &AesIvPtr[0], TCPIP_TLS_AES128_IV_LEN) == E_OK)
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_GenerateAesIv() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_GenerateAEADGcmIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreCrypto_GenerateAEADGcmIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            GcmEIvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);
  TcpIp_TlsCsmKeyInfoType tmpKey; /* Temporary CSM key element */
  Std_ReturnType retVal;
  TcpIp_TlsCsmKeyInfoType txGcmIvKey;
  uint8 txSeqNumArray[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN];  /* tx sequence number is used as Explicit Iv (8 byte) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Load Iv (implicit Iv + explicit Iv) into the key element */

  /* Copy the tx sequence number to the explicitIv array. */
  IpBase_PutUint64(&txSeqNumArray[0], 0, TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx));

  /* Nonce for Gcm is 12 bytes and is constructed as
   * |Gcm Iv | Tls seq No.|
   * |0     3|4         11|
   */

  tmpKey.KeyId = TcpIp_GetHsTemporaryBufferKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  tmpKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  tmpKey.KeyLen = 0;

  /* Copy the sequence number as explicit Iv into the tmp key */
  retVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &tmpKey);
  retVal |= TCPIP_CSM_KeyElementSet(tmpKey.KeyId, tmpKey.KeyElementId, &txSeqNumArray[0], TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN);

  txGcmIvKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  txGcmIvKey.KeyElementId = CRYPTO_KE_CIPHER_IV;

  /* Copy explicit Iv (sequence no.) from tmp key into Gcm key and set key to valid */
  retVal |= TCPIP_CSM_KeyElementCopyPartial(
    tmpKey.KeyId,
    tmpKey.KeyElementId,
    0,
    TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN,
    TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN,
    txGcmIvKey.KeyId,
    txGcmIvKey.KeyElementId
  );

  retVal |= TCPIP_CSM_KeySetValid(txGcmIvKey.KeyId);

  /* #20 If key is valid, copy the explicit Iv into provided buffer */
  if (retVal == E_OK)
  {
    VStdMemCpy(&GcmEIvPtr[0], &txSeqNumArray[0], TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN);                                 /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  }
  else
  {
    /* if not successful, report user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_SETAESIVVALUE;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_SETAESIVVALUE_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_GenerateAEADGcmIv() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8)            BufPtr,
  TCPIP_P2V(uint32)           AvailableBufferLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType  activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TCPIP_P2C(uint8)               macPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx));
  uint8                          macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  uint32                          encryptionJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherEncryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  Std_ReturnType                  retVal;
  Std_ReturnType                  csmRetVal;

  /* Array to combine HMAC and padding. Has to fit for the max supported sizes. */
  uint8 macAndPadding[TCPIP_TLS_HASH_SHA256_LEN + TCPIP_TLS_AES128_BLOCKSIZE];
  uint8                           dataLen;  /* length of data in macAndPadding[] that shall be encrypted */
  TCPIP_P2V(uint8)                paddingPtr;
  /* Retrieve the AesCbc padding bytes length - always calculated to be from 0 to TCPIP_TLS_AES128_BLOCKSIZE */
  uint8                     aesPaddingByte;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Copy the HMAC to the local array. */
  VStdMemCpy(&macAndPadding[0], macPtr, macLen);                                                                        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  dataLen = macLen;


  /* #20 Write the TLS-Padding byte and the AES padding (PKSC7 Padding) into the local array. */

  /* Retrieve the AesCbc padding bytes length - always calculated to be from 0 to (TCPIP_TLS_AES128_BLOCKSIZE - 1) */
  aesPaddingByte  = TcpIp_GetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx);

  TCPIP_ASSERT(aesPaddingByte < TCPIP_TLS_AES128_BLOCKSIZE);

  paddingPtr = &macAndPadding[dataLen];

  /* Write the padding */
  VStdMemSet(paddingPtr, aesPaddingByte, ((VStdLib_CntType)aesPaddingByte + TCPIP_TLS_TLS_PADDING_LEN));                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
  dataLen += (uint8)(aesPaddingByte + TCPIP_TLS_TLS_PADDING_LEN);

  /* #30 Feed the MAC and the padding into the already running Aes128 CBC streaming, and finish the operation. */
  csmRetVal = TCPIP_CSM_Encrypt(encryptionJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
                          &macAndPadding[0], dataLen, BufPtr, AvailableBufferLenPtr);

  /* Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0u, 0u,
                                              TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTHMACPADDINGAES128CBC);

  return retVal;
} /* TcpIp_TlsCoreRl_EncryptAes128CbcMacAndPaddingInt() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Invoke the copy function depending on the Rl content type */
  switch (TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
    case TCPIP_TLS_CT_HS:
    case TCPIP_TLS_CT_AD:
    {
      TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound(TlsConIdx, BufPtr, CopyCnt);
      break;
    } /* case TCPIP_TLS_CT_HS | TCPIP_TLS_CT_AD */
    case TCPIP_TLS_CT_CCS:
    {
      TcpIp_TlsCoreRl_CopyFromTxBufferCcs(TlsConIdx, BufPtr, CopyCnt);
      break;
    } /* case TCPIP_TLS_CT_CCS */
    case TCPIP_TLS_CT_AL:
    {
      TcpIp_TlsCoreRl_CopyFromTxBufferAl(TlsConIdx, BufPtr, CopyCnt);
      break;
    } /* case TCPIP_TLS_CT_AL */
    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
      break;
  } /* switch */
} /* TcpIp_TlsCoreRl_CopyFromTxBufferWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Start of the rl frame in the TX Buffer */

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx); /* End of the complete TX Buffer */

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx); /* Start of the TX Buffer */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy requested data into provided buffer considering wraparound, and update Rl send Idx */
  if ((rlSendIdx + CopyCnt) < txBufferEndIdx)
  {
    /* Data lies linear in the TLS tx buffer without wrapping around */
    VStdMemCpy(BufPtr, TcpIp_GetAddrTlsBufferTx(rlSendIdx), CopyCnt);                                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    TcpIp_AddTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, CopyCnt);
  }
  else
  {
    /* Data in the TLS Tx buffer is either wrapped around or aligned to the end of the buffer (SendIdx == EndIdx) */
    uint32 firstCopyLen = ((uint32)txBufferEndIdx - rlSendIdx); /* first length to be copied */
    uint32 secondCopyLen = (CopyCnt - firstCopyLen); /* second length to be copied */

    VStdMemCpy(BufPtr, TcpIp_GetAddrTlsBufferTx(rlSendIdx), firstCopyLen);                                              /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(&BufPtr[firstCopyLen], TcpIp_GetAddrTlsBufferTx(txBufferStartIdx), secondCopyLen);                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    TcpIp_SetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (txBufferStartIdx + (uint16)secondCopyLen));
  }
} /* TcpIp_TlsCoreRl_CopyFromTxBufferAdHsWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyFromTxBufferCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferCcs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Start of the RL frame in the TX Buffer */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy Ccs data into provided buffer */
   VStdMemCpy(BufPtr, TcpIp_GetAddrTlsBufferTx(rlSendIdx), CopyCnt);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

} /* TcpIp_TlsCoreRl_CopyFromTxBufferCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CopyFromTxBufferAl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_CopyFromTxBufferAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint16 CopyCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
 TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType rlSendIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Start of the RL frame in the TX Buffer */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy alert data into provided buffer */
   VStdMemCpy(BufPtr, TcpIp_GetAddrTlsBufferTx(rlSendIdx), CopyCnt);                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
} /* TcpIp_TlsCoreRl_CopyFromTxBufferAl() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_SizeOfTlsBufferTxType Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsReadIdxOfTlsBufferMgmtDynType txAdHsReadIdx
    = TcpIp_GetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txAdHsEndIdx
    = TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txAdHsStartIdx
    = TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Adjust the AdHs Read Index under consideration of wraparound at the end of the TxBuffer */
  if ((txAdHsReadIdx + Value) < txAdHsEndIdx)
  {
    /* New Read index fits into the TxBuffer - Add the value */
    TcpIp_AddTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, Value);
  }
  else /* (txAdHsReadIdx + Value) >= txBufferEndIdx) */
  {
    /* New Read index must wraparound - calculate the new index at the start of the buffer */
    TcpIp_SizeOfTlsBufferTxType remainingLenAtEnd = (txAdHsEndIdx - txAdHsReadIdx);
    TcpIp_SizeOfTlsBufferTxType newReadIdx = (txAdHsStartIdx + (Value - remainingLenAtEnd));
    TcpIp_SetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, newReadIdx);
  }

  /* fillLevel should never be negative */
  TCPIP_ASSERT(((sint64)TcpIp_GetAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) - Value) >= 0u);

  /* #20 Adjust the Application data fill level by subtracting the copied bytes */
  TcpIp_SubAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, Value);

  TCPIP_VLEAVE_CRITICAL_SECTION();

} /* TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Variable to store the position of unforwarded data in TLS Rx AdHs buffer */
  TcpIp_TlsBufferRxUlRxIndIdxOfTlsBufferMgmtDynType ulRxIndIdx
    = TcpIp_GetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType rxAdHsEndIdx
    = TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxAdHsStartIdx
    = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update ulRxIndIdx with data forwarded considering buffer wraparound */
  if ((ulRxIndIdx + Length) < rxAdHsEndIdx)
  {
    TcpIp_SetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      ((TcpIp_TlsBufferRxUlRxIndIdxOfTlsBufferMgmtDynType)(ulRxIndIdx + Length)));
  }
  else /* if ((ulRxIndIdx + Length) >= rxAdHsEndIdx) */
  {
    /* Data is wrapped around, so recalculate new newulRxIndIdx */
    uint32 newulRxIndIdx = (Length - ((uint32)rxAdHsEndIdx - ulRxIndIdx));
    TcpIp_SetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      ((TcpIp_TlsBufferRxUlRxIndIdxOfTlsBufferMgmtDynType)(rxAdHsStartIdx + newulRxIndIdx)));
  }
} /* TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType rxAdHsReadIdx
    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType rxAdHsEndIdx
    = TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxAdHsStartIdx
    = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update Rx read index and current end index considering buffer wraparound */
  if ((rxAdHsReadIdx + Length) < rxAdHsEndIdx)
  {
    TcpIp_SetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      ((TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType)(rxAdHsReadIdx + Length)));
  }
  else
  {
    /* If wraparound, calculate the new length at the beginning of the buffer and wrap the buffer around */
    uint32 newStartOffset = (Length - ((uint32)rxAdHsEndIdx - rxAdHsReadIdx));

    TcpIp_SetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      ((TcpIp_TlsBufferRxAdHsReadIdxOfTlsBufferMgmtDynType)(rxAdHsStartIdx + newStartOffset)));

    /* [Sliding End Index]: (2) */
    /* The buffer at end of TLS Rx AdHs buffer has been consumed, slide back the current end index to end index */
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  }

} /* TcpIp_TlsCoreRl_IncrementRxAdHsReadIdxWithWraparound() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_Transmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TxStartIdx,
  TcpIp_SizeOfTlsBufferTxType TxLen,
  CONST(uint8, AUTOMATIC) ContentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ActiveMaxTxRlSizeOfTlsConnectionDynType activeMaxTxRlSize
    = TcpIp_GetActiveMaxTxRlSizeOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the transmitted length exceed the maximum supported record layer limit */
  /* This limit can be negotiated via the TLS extension in the hello messages */
  if (TxLen <= activeMaxTxRlSize)
  {
    /* #20 Frame fits into one record layer frame - start transmitting of single record layer frame */
    retVal = TcpIp_TlsCoreRl_TransmitFrame(TlsConIdx, TxStartIdx, TxLen, ContentType);
  }
  else
  {
    /* #30 Frame must be fragmented into multiple record layer frames */
    retVal = TcpIp_TlsCoreRl_FragmentFrameAndTransmit(TlsConIdx, TxStartIdx, TxLen, ContentType);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_Transmit() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TransmitFrame
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType ContentTypeTxStartIdx,
  TcpIp_SizeOfTlsBufferTxType PlaintextTxLen,
  CONST(uint8, AUTOMATIC) ContentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 encryptedTxFragLen;
  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  encryptedTxFragLen = TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend(TlsConIdx, (uint32)PlaintextTxLen);
  /* Set the total length requested for this transmit call */
  TcpIp_SetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, encryptedTxFragLen);
  /* Set the startIdx of the Tx data for this transmit call */
  TcpIp_SetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType)ContentTypeTxStartIdx);
  /* Set the content type for this transmit call */
  TcpIp_SetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, ContentType);
  /* Set the length of the data for this transmit call */
  TcpIp_SetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (uint32)PlaintextTxLen);

  /* #10 If enough space is available in TcpIp buffer, trigger transmission of RL header and data, and notify upper layer if successful */
  if (TcpIp_TlsCoreRl_CheckTcpBuffer(TlsConIdx, encryptedTxFragLen) == E_OK)
  {
    /* Trigger transmission of RL header and data frame */
    if (   (TcpIp_TlsCoreRl_TransmitFrameHdr(TlsConIdx) == E_OK)                                                        /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
        && (TcpIp_TlsCoreRl_TransmitFrameCiphertext(TlsConIdx) == E_OK))
    {
      /* Notify upper layer about transmitted data */
      TcpIp_TlsCoreRl_TxConfirmation(TlsConIdx);

      /* Increment the RL Sequence counter for the transmit direction */
      TcpIp_IncRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx);

      /* Reset the frame specific variables */
      TcpIp_SetRlTxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
      TcpIp_SetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
      TcpIp_SetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_NO_TLSBUFFERTXRLSENDIDXOFTLSBUFFERMGMTDYN);
      TcpIp_SetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
      TcpIp_SetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);

      retVal = E_OK;
    }
    else
    {

      /* Trigger Alert if tx fails */
      TcpIp_TlsCoreRl_HandleErrorWhileTransmit(TlsConIdx, (TcpIp_TlsUserErrorIdType)TCPIP_TLS_ERRORID_RL_TX_FAILED);
    }
  }
  else
  {
    /* Not enough space in TCP buffer, retry later */
  }


  return retVal;
} /* TcpIp_TlsCoreRl_TransmitFrame() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_FragmentFrameAndTransmit
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
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_FragmentFrameAndTransmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TxStartIdx,
  TcpIp_SizeOfTlsBufferTxType TxLen,
  CONST(uint8, AUTOMATIC) ContentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txAdHsStartIdx
    = TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txAdHsEndIdx
    = TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  TcpIp_SizeOfTlsBufferTxType txFragmentLen; /* Length of the current record layer fragment */
  TcpIp_SizeOfTlsBufferTxType totalTxLen = 0u; /* Total length of plaintext queued for Tx */
  TcpIp_TlsBufferTxIterType txFragmentStartIdx = TxStartIdx; /* Start index of the plaintext to be transmitted */

  TcpIp_ActiveMaxTxRlSizeOfTlsConnectionDynType activeMaxTxRlSize
    = TcpIp_GetActiveMaxTxRlSizeOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Repeatedly invoke the TcpIp_TlsCoreRl_TransmitFrame until all the plaintext has been queued for transmission */
  while (totalTxLen < TxLen)
  {
    /* #20 Calculate how much plaintext can fit into the current RL fragment */
    if ((TxLen - totalTxLen) < activeMaxTxRlSize)
    {
      /* If less than max fragment length of data left, update the tx fragment length */
      txFragmentLen = TxLen - totalTxLen;
    }
    else
    {
      /* Else transmit maximum fragment length */
      txFragmentLen = activeMaxTxRlSize;
    }

    /* #30 Send possible plaintext in the current RL frame */
    if (TcpIp_TlsCoreRl_TransmitFrame(TlsConIdx, txFragmentStartIdx, txFragmentLen, ContentType) == E_OK)
    {
      /* #40 If transmission successfully queued, point to the next data */
      if ((txFragmentStartIdx + txFragmentLen) <= txAdHsEndIdx)
      {
        txFragmentStartIdx += txFragmentLen;
      }
      else
      {
        txFragmentStartIdx = txAdHsStartIdx + txFragmentLen - (txAdHsEndIdx - txFragmentStartIdx);
      }

      /* Increment total length transmitted */
      totalTxLen += txFragmentLen;
    }
    else
    {
      /* #50 If transmission failed, break and return */
      retVal = E_NOT_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_FragmentFrameAndTransmit() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CheckTcpBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckTcpBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32                      CipherTextTxLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(
                                                TlsConIdx));
  TcpIp_SizeOfTcpTxBufferDescType tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(socketTcpIdx);
  TcpIp_SizeOfTcpTxBufferType     tcpTxBufferSize = TcpIp_GetTcpTxBufferLengthOfTcpTxBufferDesc(tcpTxBufferDescIdx);
  TcpIp_SizeOfTcpTxBufferType     tcpTxBufferFillLevel = TcpIp_GetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());
  TCPIP_ASSERT(tcpTxBufferSize >= tcpTxBufferFillLevel);

  /* #10 Check that the total ciphertext data fits into the remaining space in the TCP ring buffer. */
  if ((CipherTextTxLen + TCPIP_TLS_RLHDRLEN) <= (uint32)(tcpTxBufferSize - tcpTxBufferFillLevel))
  {
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_CheckTcpBuffer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_AddFrameHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrameHdr(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint8 rlHdr[TCPIP_TLS_RLHDRLEN];
  Std_ReturnType retVal                       = E_NOT_OK;
  uint16 recordLayerLen                       = (uint16)TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint8 contentType                           = TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Build the Rl header */

  /* Copy the Content Type of this frame */
  IpBase_PutUint8(&rlHdr[TCPIP_TLS_RLCT_OFFSET], 0, contentType);

  /* Copy the Major and Minor version number */
  IpBase_PutUint8(&rlHdr[TCPIP_TLS_RLVERSMAJOR_OFFSET], 0, TCPIP_TLS_RL_VERSMAJOR);
  IpBase_PutUint8(&rlHdr[TCPIP_TLS_RLVERSMINOR_OFFSET], 0, TCPIP_TLS_RL_VERSMINOR);

  /* Copy the length of this frame */
  IpBase_PutUint16(&rlHdr[TCPIP_TLS_RLLEN_OFFSET], 0, recordLayerLen );

  /* #20 Transmit the frame via direct data provision */
  if (   TcpIp_TcpTransmitInternal(TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx), &rlHdr[0], TCPIP_TLS_RLHDRLEN, FALSE)
      == E_OK)
  {
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_AddFrameHdr() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TransmitFrameCiphertext
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_TransmitFrameCiphertext(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 txLength = TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType retVal                       = E_NOT_OK;

  /* #10 Trigger TCP transmission of the data in the Tls buffer */
  if (TcpIp_TcpTransmitInternal(TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx), NULL_PTR, txLength, TRUE) == E_OK)
  {
    retVal = E_OK;
  }
  return retVal;
} /* TcpIp_TlsCoreRl_TransmitFrameCiphertext() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) ContentTypeLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 calculatedLen = 0;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Calculate tx length, including authentication and padding */
  switch (TcpIp_GetActiveCipherTxOfTlsConnectionDyn(TlsConIdx))
  {
    case TCPIP_TLS_NULL_WITH_NULL_NULL:
    {
      calculatedLen = ContentTypeLen;
      break;
    }
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
    case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
    {
      uint32 calcAesInputLen = (ContentTypeLen + TCPIP_TLS_HASH_SHA256_LEN + TCPIP_TLS_TLS_PADDING_BYTE_LEN);
      TcpIp_SetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_GET_AES128CBC_PADDING_LEN(calcAesInputLen));
      calculatedLen = (calcAesInputLen + TCPIP_TLS_AES128_IV_LEN + TcpIp_GetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx));
      break;
    }
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
    case TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256:
    {
      calculatedLen = (TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN + ContentTypeLen + TCPIP_TLS_AES128_GCM_AUTHTAG_LEN);
      break;
    }
    case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
    case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
    case TCPIP_TLS_PSK_WITH_NULL_SHA:
    {
      calculatedLen = (ContentTypeLen + TCPIP_TLS_HASH_SHA1_LEN);
      break;
    }
    case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    {
      calculatedLen = (ContentTypeLen + TCPIP_TLS_HASH_SHA256_LEN);
      break;
    }
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
    case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      uint32 calcAesInputLen = (ContentTypeLen + TCPIP_TLS_HASH_SHA1_LEN + TCPIP_TLS_TLS_PADDING_BYTE_LEN);

      TcpIp_SetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_GET_AES128CBC_PADDING_LEN(calcAesInputLen));
      calculatedLen = (calcAesInputLen + TCPIP_TLS_AES128_IV_LEN + TcpIp_GetAes128CbcPaddingByteOfTlsConnectionDyn(TlsConIdx));
      break;
    }
    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    {
      /* This case is never reached */
      break;
    }
  }

  return calculatedLen;
} /* TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_GetTxCipherMacLen
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(uint8, TCPIP_CODE) TcpIp_TlsCoreRl_GetTxCipherMacLen(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 macLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the active cipher and return the length of the Mac */
  switch (TcpIp_GetActiveCipherTxOfTlsConnectionDyn(TlsConIdx))
  {
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    {
      macLen = TCPIP_TLS_HASH_SHA256_LEN;
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      macLen = TCPIP_TLS_HASH_SHA1_LEN;
      break;
    }
  case TCPIP_TLS_NULL_WITH_NULL_NULL:
  default:
    {
      macLen = 0u;
      break;
    }
  }

  return macLen;
} /* TcpIp_TlsCoreRl_GetTxCipherMacLen() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcHmacCipherDependend
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacCipherDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 TcpBufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherDataType activeCipherIdx = TcpIp_GetActiveCipherTxOfTlsConnectionDyn(TlsConIdx);
  Std_ReturnType retVal = E_NOT_OK;
  boolean skipHmacCalculation;

  /* Check if HMAC calculation can be skipped. If the input data is split in two parts, the HMAC calculation can be done
  during the second call. */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_RlTxFragmentLenOfTlsBufferMgmtDynType requestedRlTxLen;
  uint32 totalTcpBufLen;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check if all input data is available to do the MAC calculation. */
  requestedRlTxLen = TcpIp_GetRlTxFragmentLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  totalTcpBufLen = (uint32)TcpBufLength + (uint32)TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;

  /* Check if provided TCP buffer(s) has sufficient space and trigger MAC calculation. */
  if (totalTcpBufLen < requestedRlTxLen)
  {
    /* This is the first part of a message split in the TLS TxBuffer, so the MAC calculation can be skipped. */
    skipHmacCalculation = TRUE;
  }
  else
  {
    skipHmacCalculation = FALSE;
  }

  /* #20 Invoke the appropriate MAC calculation function. */
  switch (TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode(activeCipherIdx))
  {
    case TCPIP_TLS_MSG_AUTH_MODE_NONE:
    {
      retVal = E_OK;
      break;
    }
    case TCPIP_TLS_MSG_AUTH_MODE_SHA1:
    case TCPIP_TLS_MSG_AUTH_MODE_SHA256:
    {
      if (skipHmacCalculation == FALSE)
      {
        retVal = TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend(TlsConIdx);
      }
      else
      {
        retVal = E_OK;
      }
      break;
    }
    default:    /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    {
      /* This case is never reached */
      break;
    }
  } /* switch */

  return retVal;
} /* TcpIp_TlsCoreRl_CalcHmacCipherDependend() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_RxIndication(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the Rx Indication flag to TRUE */
  TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, TRUE);
} /* TcpIp_TlsCoreRl_RxIndication() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_TxConfirmation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType       socketIdx        = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 contentTypeTxLen                        = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If connection is established, forward Tx confirmation to upper layer */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
  {
    /* Forward the Tx confirmation for the content data */
    if (contentTypeTxLen <= TCPIP_TX_INDICATION_LEN_MAX)
    {
      TcpIp_Tcp_TlsTxConfirmation(socketIdx, (uint16)contentTypeTxLen);
    }
    else
    {
      /* If content data has multiple parts, forward confirmation sufficient times to UL */
      uint16 txConfLen;
      uint32 remainingTxConfLen = contentTypeTxLen;
      /* Iterate over all given data */
      while (remainingTxConfLen > 0u)
      {
        if (remainingTxConfLen > TCPIP_TX_INDICATION_LEN_MAX)
        {
          txConfLen = (uint16)TCPIP_TX_INDICATION_LEN_MAX;
        }
        else
        {
          txConfLen = (uint16)remainingTxConfLen;
        }
        /* Forward indication to UL */
        TcpIp_Tcp_TlsTxConfirmation(socketIdx, (uint16)txConfLen);
        /* Subtract the already confirmed data */
        remainingTxConfLen -= txConfLen;
      }
    }
  }
} /* TcpIp_TlsCoreRl_TxConfirmation() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_ValidateFrameHdr
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ValidateFrameHdr(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint32 TotDataLen,
  TCPIP_P2V(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint8 rlHdrLen;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Validate the received Rl header and copy into Tls buffer */
  if (TotDataLen != 0u)
  {
    /* Check if a complete Rl header was received */
    if (TotDataLen >= TCPIP_TLS_RLHDRLEN)
    {
      rlHdrLen = TCPIP_TLS_RLHDRLEN;
      TcpIp_TlsCoreRxBufStruct_Copy2Buf(tlsBufferMgmtIdx, RlHdrPtr, rlHdrLen, 0);
    }
    else
    {
      /* There is something in the buffer, but smaller than the RL HDR. Check the first byte if it is a valid RL Frame */
      rlHdrLen = (uint8)TotDataLen;
      TcpIp_TlsCoreRxBufStruct_Copy2Buf(tlsBufferMgmtIdx, RlHdrPtr, rlHdrLen, 0);
    }

    /* Parse and validate the received Rl header */
    retVal = TcpIp_TlsCoreRl_ParseAndValidateRlHdr(TlsConIdx, RlHdrPtr, rlHdrLen, RlAlertDescriptionPtr);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_ValidateFrameHdr() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_ValidateRlFragmentLength
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ValidateRlFragmentLength(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* The maximum length of a plaintext RL fragment that can be received */
  TcpIp_SizeOfTlsBufferRxType activePlaintextMaxRxRlSize
    = TcpIp_GetActiveMaxRxRlSizeOfTlsConnectionDyn(TlsConIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Calculate maximum overall length which can be received. This contains the plaintext size plus the TLS overhead */
  uint32 maxRlFragmentLen = TcpIp_TlsCoreRl_CalcContentTypeLenCipherDependend(TlsConIdx, (uint32)activePlaintextMaxRxRlSize);

  /* Get the received record layer length from the header */
  uint16 rlFragmentLen = IpBase_GetUint16(RlHdrPtr, TCPIP_TLS_RLLEN_OFFSET);

  /* #10 Check if the received record layer frame fits in the maximum fragment length */
  if (rlFragmentLen <= maxRlFragmentLen)
  {
    /* #20 Frame fits, return E_OK */
    retVal = E_OK;
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_UNSET;
  }
  else
  {
    /* #30 Frame does not fit - return E_NOT_OK and trigger TLS alert */
    retVal = E_NOT_OK;

    /* RFC8449 - 4. The "record_size_limit" Extension
     *   A TLS endpoint that receives a record larger than its advertised limit MUST
     *   generate a fatal "record_overflow" alert;
     */
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_RECORD_OVERFLOW;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_ValidateRlFragmentLength() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyFrameCompleteness
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyFrameCompleteness(
  uint32 TotDataLen,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(uint16) RlHdrLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received the complete frame */
  *RlHdrLenPtr = IpBase_GetUint16(RlHdrPtr, TCPIP_TLS_RLLEN_OFFSET);

  if (TotDataLen >= (uint32)(TCPIP_TLS_RLHDRLEN + (uint32)(*RlHdrLenPtr)))
  {
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_VerifyFrameCompleteness() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CheckIfFrameIsReceivable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckIfFrameIsReceivable(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  TcpIp_TlsConnectionState currentConnectionState = TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Check if connection is in valid state to receive AD frame */
  if (RlHdrPtr[TCPIP_TLS_RLCT_OFFSET] == TCPIP_TLS_CT_AD)
  {
    switch (currentConnectionState)
    {
      /* If the connection is in state HS_ACTIVE we should not receive any TLS AD. Set the TLS Alert to 'unexpected_message' */
      case TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE:
      {
        *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_UNEXP_MSG;
        /* Frame not receivable */
        retVal = E_NOT_OK;
        break;
      }

      /* If the connection is in state ESTABLISHED or FINALIZING TLS handshake it is OK to receive TLS AD */
      case TCPIP_TLS_STATE_CONNECTION_ESTABLISHED:
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
      case TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING:
# endif
      {
        /* Frame receivable */
        retVal = E_OK;
        break;
      }

      /* If connection is in other states, nothing to do */
      default:
      {
        /* do nothing */
        break;
      }
    }
  }

  /* We know that the RL header is valid, so no additional checks needed here.
     All other CT can pass and retVal is set to E_OK */

  return retVal;
} /* TcpIp_TlsCoreRl_CheckIfFrameIsReceivable() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_ValidateAndForwardFrameToUpperLayer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ForwardFrameToUpperLayer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal                          = E_NOT_OK;
  uint8 contentType                              = RlHdrPtr[TCPIP_TLS_RLCT_OFFSET];
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the current frame fits into the TLS Rx buffer */
  if (TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer(TlsConIdx, contentType, RlFrameLen) == TRUE)
  {
    /* #20 Decrypt and authenticate the received Rl frame, trigger Ul RxIndication for Rl Frame if necessary */
    if (TcpIp_TlsCoreRl_DecryptAndAuthFrame(TlsConIdx, RlFrameLen, contentType, RlAlertDescriptionPtr) == E_OK)
    {
      TcpIp_SocketDynComIdxOfTlsConnectionDynType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
      /* Length of the plaintext in the TLS buffer */
      TcpIp_RlRxCopiedLenOfTlsBufferMgmtDynType plaintextLen = TcpIp_GetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

      /* Inform upper layer that a complete RL frame was received */
      TcpIp_TlsCoreRl_RxIndication(TlsConIdx);
      /* Release the TCP buffers of the processed Rl frame */
      TcpIp_TlsCoreRxBufStruct_ReleaseSegment(tlsBufferMgmtIdx, ((uint32)RlFrameLen + TCPIP_TLS_RLHDRLEN));
      /* Notify TCP that TLS has consumed the current Rl frame */
      TcpIp_Tcp_TlsReceived(socketIdx, (uint16)(RlFrameLen + TCPIP_TLS_RLHDRLEN));
      /* Increment the RX sequence counter */
      TcpIp_IncRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx);
      /* Increment the UlRxIndication level with new plaintext that was received */
      TcpIp_AddAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, plaintextLen);
      /* Increment the TLS Rx Ad fill level with new plaintext that was received */
      TcpIp_AddAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, plaintextLen);
      /* Reset the copied length since RxIndication has been triggered */
      TcpIp_SetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
      retVal = E_OK;
    }
  }
  else
  {
    /* Received frame fits not into the buffer - Set record layer alert description */
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_ValidateAndForwardFrameToUpperLayer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_ParseAndValidateRlHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6080 1 */ /* MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_ParseAndValidateRlHdr(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) RlHdrPtr,
  CONST(uint8, AUTOMATIC) RlHdrLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType rLHeaderUserError;
  uint8 contentType = RlHdrPtr[TCPIP_TLS_RLCT_OFFSET];
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* Prepare user error */
  rLHeaderUserError.FunctionId = TCPIP_TLS_FCTID_CORE_RL_CHECKHDR;
  rLHeaderUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);
  /* ErrorId will be set to the possible occurring errors */


  /* #10 Check the TLS content type of the received RL frame */
  if (    (contentType == TCPIP_TLS_CT_AD)
       || (contentType == TCPIP_TLS_CT_HS)
       || (contentType == TCPIP_TLS_CT_AL)
       || (contentType == TCPIP_TLS_CT_CCS))
  {
    /* #20 Check if we receive the 2 bytes version number */
    if (RlHdrLen > TCPIP_TLS_RLVERSMINOR_OFFSET)
    {
      /* #30 Check the TLS major version number (must match exactly with 0x03) */
      if (RlHdrPtr[TCPIP_TLS_RLVERSMAJOR_OFFSET] == TCPIP_TLS_RL_VERSMAJOR)
      {
        /* #40 Check the TLS minor version number depending on the TLS mode (Server/ Client) */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
        if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
        {
          /* Mode == TCPIP_TLS_SERVER */
          /* Server accept smaller minor version numbers only in ClientHello message */
          if (TcpIp_GetHandshakeStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_WAIT_FOR_CLIENT_HELLO)
          {
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: According to RFC 5246, section E.1, servers must accept any minor version number in the record layer header of a client hello, also bigger values than the own supported one. */
/* [REVIEW_c] comment visbdk: This means, this next check is not relevant and can be deleted? I think we have some TCASEs for this?!  */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Yes that is what this would mean. So this check and the above comment have to be adapted. */
/* [REVIEW_c] stored visal, visbdk: Will be implemented in TCPIP-6201. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
            if (RlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] <= TCPIP_TLS_RL_VERSMINOR)
            {
              retVal = E_OK;
            }
            else
            {
              /* TLS Server invalid minor version number */
              rLHeaderUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_MINORVERSNR;
              *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_PROT_VERSION;
            }
          }
          else
          {
            /* every other message than ClientHello must contain exactly the minor version number of 0x03 */
            if (RlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] == TCPIP_TLS_RL_VERSMINOR)
            {
              retVal = E_OK;
            }
            else
            {
              /* TLS Server invalid minor version number */
              rLHeaderUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_MINORVERSNR;
              *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_PROT_VERSION;
            }
          }
        }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
        else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
        {
          /* Mode == TCPIP_TLS_CLIENT */
          /* Client TLS minor version number must match exactly with 0x03 */
          if (RlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] == TCPIP_TLS_RL_VERSMINOR)
          {
            retVal = E_OK;
          }
          else
          {
            /* TLS Client invalid minor version number */
            rLHeaderUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_MINORVERSNR;
            *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_PROT_VERSION;
          }
        }
# endif

      }
      else
      {
        /* Received wrong major version, set errorId */
        rLHeaderUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_MAJORVERSNR;
        *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_PROT_VERSION;
      }
    }
    else
    {
      /* No full record layer header received */
      retVal = E_OK;
    }
  }
  else
  {
    /* Received wrong Content Type, set errorId */
    rLHeaderUserError.UserErrorId = TCPIP_TLS_ERRORID_RL_INCORRECT_CT;

    /* Set Alert to UNEXPECTED MESSAGE */
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
  }

  if (retVal != E_OK)
  {
    TcpIp_TlsCoreError_ReportUserError(rLHeaderUserError);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_ParseAndValidateRlHdr() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_DecryptAndAuthFrame
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_DecryptAndAuthFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                 retVal                 = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType  tlsBufferMgmtIdx       = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Variable to store the length of the Rl frame segment */
  uint16                         rxRlFrameSegLen        = RlFrameLen;
  /* Offset of the RL frame segment */
  uint16                         rxRlFrameSegOffset     = TCPIP_TLS_RLHDRLEN;
  /* Rx buffer segment index */
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx      = 0u;
  /* Flag to indicate if a complete Rl frame is available */
  boolean                        completeRlFrameFlag    = FALSE;
  /* Local variables to store TCP Rx buffer segment information */
  TCPIP_P2V(uint8)               bufSegPtr;
  /* Bytes to process from the current TCP Rx buffer segment */
  uint16                         bytesToCopy;
  uint32                         segOffset;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set start index of current record layer frame */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
                                                 TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
    TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
                                                 TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  }
  else if (ContentType ==  TCPIP_TLS_CT_CCS)
  {
    TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      TcpIp_GetTlsBufferRxCcsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  }
  else
  {
    /* This could not happen - left blank intentionally */
  }

  if (rxRlFrameSegLen != 0u)
  {
    /* #20 Decrypt and authenticate the current frame */
    while (rxRlFrameSegLen > 0u)
    {
      /* Set offset to the start of the TLS payload */
      segOffset = rxRlFrameSegOffset;

      /* Get index of TcpIp segment where current frame is available, considering offset */
      if (TcpIp_TlsCoreRxBufStruct_GetBufSegIdx(tlsBufferMgmtIdx, &segOffset, &rxBufStructSegIdx) == E_OK)
      {

        /* Extract the TCP segment */
        bufSegPtr = TcpIp_GetDataPtrOfRxBufStructSeg(rxBufStructSegIdx);
        bytesToCopy = (uint16)(TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx) - segOffset);

        /* Check if a complete TLS Rl frame is present in the current TCP segment */
        if (rxRlFrameSegLen < bytesToCopy)
        {
          /* Only forward the complete Rl frame */
          bytesToCopy = rxRlFrameSegLen;
        }

        /* Check if a whole Rl frame has been extracted */
        if (rxRlFrameSegLen == bytesToCopy)
        {
          /* Complete TLS Rl frame extracted, decryption and authentication can be completed in this call */
          completeRlFrameFlag = TRUE;
        }

        if (TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate(TlsConIdx, ContentType, &bufSegPtr[segOffset], bytesToCopy,
          RlAlertDescriptionPtr, completeRlFrameFlag) == E_OK)
        {
          rxRlFrameSegLen -= bytesToCopy;
          rxRlFrameSegOffset += bytesToCopy;
          retVal = E_OK;
        }
        else
        {
          rxRlFrameSegLen = 0;  /* Set to 0 as exit the while-loop. */
          retVal = E_NOT_OK;
        }
      }
      else
      {
        rxRlFrameSegLen = 0;  /* Set to 0 as exit the while-loop. */
        retVal = E_NOT_OK;
      }
    } /* while (rxRlFrameSegLen > 0u) */
  }
  else
  {
    /* Received zero length frame - Set record layer alert description */
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
  }
  /* Reset Rl frame start index */
  TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_NO_TLSBUFFERRXRLFRAMESTARTIDXOFTLSBUFFERMGMTDYN);

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAndAuthFrame() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(uint8)                         DataPtr,
  uint16                                   DataLen,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr,
  boolean                                  CompleteRlFrameFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Decrypt the TLS frame in the provided TCP buffer directly into the TLS buffer */
  retVal = TcpIp_TlsCoreRl_RxCipherDecryptFrame(TlsConIdx, ContentType, DataPtr, DataLen, CompleteRlFrameFlag);

  if (retVal == E_OK)
  {
    /* #20 If a complete TLS frame has been decrypted, trigger authentication of received data */
    if (CompleteRlFrameFlag == TRUE)
    {
      /* Perform authentication if this is the last call */
      retVal = TcpIp_TlsCoreRl_RxCipherAuthenticateFrame(TlsConIdx, ContentType, RlAlertDescriptionPtr);
    }
  }
  else
  {
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAndAuthenticate() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RxCipherDecryptFrame
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherDecryptFrame(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(uint8)                         DataPtr,
  uint16                                   DataLen,
  boolean                                  CompleteRlFrameFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_TlsCipherStreamingModeDataType activeStreamingMode =
    TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode(TcpIp_GetActiveCipherRxOfTlsConnectionDyn(TlsConIdx));

  /* ----- Implementation ----------------------------------------------- */
  if ((ContentType == TCPIP_TLS_CT_CCS) && (activeStreamingMode != TCPIP_TLS_STREAMING_MODE_NULL))
  {
    /* In this case a duplicated CCs message was received because an encrypted CCs message can only be received */
    /* after an earlier CCs message that indicated the switch to encrypted communication. */
    /* Therefore trigger an unexpected message alert. */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
  }
  else
  {
    /* #10 Depending on active cipher, decrypt the provided data into TLS buffer */
    switch (activeStreamingMode)
    {
    case TCPIP_TLS_STREAMING_MODE_NULL:
      {
        /* Data processing done by NULL cipher, also used for handshake messages */
        retVal = TcpIp_TlsCoreRl_RxCipherDecryptNull(TlsConIdx, ContentType, DataPtr, DataLen);
        break;
      } /* case Null streaming */
    case TCPIP_TLS_STREAMING_MODE_AES_128_CBC:
      {
        retVal = TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming(TlsConIdx, ContentType, DataPtr, DataLen, CompleteRlFrameFlag);
        break;
      } /* case Aes128Cbc streaming */
    case TCPIP_TLS_STREAMING_MODE_AES_128_GCM:
      {
        retVal = TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming(TlsConIdx, ContentType, DataPtr, DataLen, CompleteRlFrameFlag);
        break;
      } /* case Aes128Gcm streaming */
    default:
      {
        /* unsupported streaming mode */
        break;
      } /* default */
    } /* switch */
  }
  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptFrame */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RxCipherAuthenticateFrame
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_RxCipherAuthenticateFrame(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the active cipher, authenticate the data in the Tls buffer */
  switch (TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode(TcpIp_GetActiveCipherRxOfTlsConnectionDyn(TlsConIdx)))
  {
  case TCPIP_TLS_MSG_AUTH_MODE_SHA1:
  case TCPIP_TLS_MSG_AUTH_MODE_SHA256:
    {
      retVal = TcpIp_TlsCoreRl_RxCipherAuthenticateSha(TlsConIdx, ContentType, RlAlertDescriptionPtr);
      break;
    } /* case Sha authentication */
  case TCPIP_TLS_MSG_AUTH_MODE_NONE:
    {
      /* Nothing to do */
      retVal = E_OK;
      break;
    }
  default:
    {
      /* unsupported authentication mode */
      break;
    } /* default */
  } /* switch */

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptFrame */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_HandleInvalidRlFrame
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_HandleInvalidRlFrame(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint16, AUTOMATIC) RlFrameLen,
  TcpIp_TlsAlertDescriptionType AlertDescription)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_SocketDynComIdxOfTlsConnectionDynType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsUserErrorType        rlUserError;

  /* ----- Implementation ----------------------------------------------- */

  /* Set the corresponding error id */
  rlUserError.FunctionId = TCPIP_TLS_FCTID_CORE_MAINFCT_RXRL;
  rlUserError.UserErrorId = TCPIP_TLS_ERRORID_RXINCORRECTRLFRAME;
  rlUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  /* #10 Report the error to the user and trigger alert transmission */
  TcpIp_TlsCoreError_ReportUserError(rlUserError);

  /* Trigger the transmission of the occurred alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, AlertDescription);

  /* Release the buffers */
  TcpIp_TlsCoreRxBufStruct_ReleaseSegment(tlsBufferMgmtIdx, RlFrameLen);
  TcpIp_Tcp_TlsReceived(socketIdx, (uint16)(RlFrameLen ));

} /* TcpIp_TlsCoreRl_HandleInvalidRlFrame() */

/***********************************************************************************************************************
 *  TLS CORE RL - CIPHERS
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptNull
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptNull(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint16                        copiedLen = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy all data into Tls buffer */
  TcpIp_TlsCoreRl_CopyDataToRxBuf(TlsConIdx, ContentType, DataPtr, DataLen, &copiedLen);

  /* Set the Rx copiedLen to the total bytes copied so far into the TLS Rx buffer */
  TcpIp_AddRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, copiedLen);

  return E_OK;
} /*  TcpIp_TlsCoreRl_RxCipherDecryptNull() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherAuthenticateSha
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherAuthenticateSha(
  TcpIp_TlsConnectionIterType              TlsConIdx,
  CONST(uint8, AUTOMATIC)                  ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify the Mac of this frame and finalize the Rx buffer */
  retVal = TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend(TlsConIdx, ContentType, RlAlertDescriptionPtr);

  TcpIp_TlsCoreRl_FinalizeRxBuffer(TlsConIdx, ContentType);

  return retVal;
} /*  TcpIp_TlsCoreRl_RxCipherDecryptNull() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2V(uint8)            DataPtr,
  uint16                      DataLen,
  boolean                     CompleteRlFrameFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if complete TLS record layer frame is received */
  if (CompleteRlFrameFlag == FALSE)
  {
    /* #20 Only partial TLS record layer frame available, store the buffer information for next call */
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = DataPtr;
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = DataLen;
    retVal = E_OK;
  }
  else
  {
    /* This path is executed when a complete frame is received OR for the second call of an fragmented frame */
    /* Block size alignment must match with both data lengths */
    uint16 completeDataLen = (TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen + DataLen);

    /* #30 Record layer frame complete check AES-128-CBC block size alignment */
    if (TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment(TlsConIdx, completeDataLen) == E_OK)
    {
      /* #40 Record layer size is aligned - Perform AES-128-CBC decryption */
      retVal = TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc(TlsConIdx, ContentType, DataPtr, DataLen);
    }
    else
    {
      /* AES-128-CBC Block size mismatch - return E_NOT_OK and do not decrypt the data */
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcStreaming */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2V(uint8)            DataPtr,
  uint16                      DataLen,
  boolean                     CompleteRlFrameFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if complete TLS Rl frame received and start Aes128 Gcm decryption */
  if (CompleteRlFrameFlag == FALSE)
  {
    /* Only partial TLS Rl frame available, store the buffer information for next call */
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = DataPtr;
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = DataLen;
    retVal = E_OK;
  }
  else
  {
    /* If complete Rl frame available, perform Aes128 Gcm decryption */
    retVal = TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm(TlsConIdx, ContentType, DataPtr, DataLen);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmStreaming */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            TcpSeg1Ptr,
  uint16                      IvInTcpSeg1Len,
  TCPIP_P2C(uint8)            TcpSeg2Ptr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType    retVal;
  TCPIP_P2C(uint8)  pIVPtr;
  uint8             lenIVBytesInData = TCPIP_TLS_AES128_IV_LEN;
  uint8             tmpIV[TCPIP_TLS_AES128_IV_LEN];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the Iv from the data and set the Aes key element */
  if (IvInTcpSeg1Len == 0u)
  {
    /* Aes Iv is present in TCP segment 2 */
    pIVPtr = TcpSeg2Ptr;
  }
  else if (IvInTcpSeg1Len < TCPIP_TLS_AES128_IV_LEN)
  {
    /* Copy the Iv in seg1 and seg2 into temp buffer */
    VStdMemCpy(&tmpIV[0], TcpSeg1Ptr, IvInTcpSeg1Len);                                                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    lenIVBytesInData -= (uint8)IvInTcpSeg1Len;
    VStdMemCpy(&tmpIV[IvInTcpSeg1Len], TcpSeg2Ptr, lenIVBytesInData);                                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Aes Iv is present in tmpBuffer */
    pIVPtr = &tmpIV[0];
  }
  else /* (IvInTcpSeg2Len >= TCPIP_TLS_AES128_IV_LEN) */
  {
    TCPIP_ASSERT(TcpSeg1Ptr != NULL_PTR);
    /* Aes Iv is present in TCP segment 1 */
    pIVPtr = TcpSeg1Ptr;
  }

  /* Prepare the CSM and set the Iv into the Aes key element */
  retVal = TcpIp_TlsCoreRl_SetIvForDecryptCall(TlsConIdx, pIVPtr);

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            TcpSeg1Ptr,
  uint16                      IvInTcpSeg1Len,
  TCPIP_P2C(uint8)            TcpSeg2Ptr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType    retVal;
  TCPIP_P2C(uint8)  pExplicitIVPtr;
  uint8             lenIVBytesInData = TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;
  TcpIp_TlsCipherWorkerIterType  activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(
                                                                TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(
                                                       activeTlsCipherWorkerIdx);
  uint8             tempExplicitIV[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN];
  TcpIp_TlsCsmKeyInfoType rxGcmIvKey;
  TcpIp_TlsCsmKeyInfoType tmpKey; /* Temporary CSM key element */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the Iv from the provided TCP segments */
  if (IvInTcpSeg1Len == 0u)
  {
    /* IV is present in the data segment */
    pExplicitIVPtr = TcpSeg2Ptr;
  }
  else if (IvInTcpSeg1Len < TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN)
  {
    TCPIP_ASSERT(TcpSeg1Ptr != NULL_PTR);
    TCPIP_ASSERT(IvInTcpSeg1Len != 0u);

    /* Copy the IV data from seg1 into temp buffer */
    VStdMemCpy(&tempExplicitIV[0], TcpSeg1Ptr, IvInTcpSeg1Len);                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    lenIVBytesInData -= (uint8)IvInTcpSeg1Len;

    /* Copy the IV data from seg2 into temp buffer */
    VStdMemCpy(&tempExplicitIV[IvInTcpSeg1Len], TcpSeg2Ptr, lenIVBytesInData);                                          /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* IV is present in tempBuffer */
    pExplicitIVPtr = &tempExplicitIV[0];
  }
  else /* (IvInTcpSeg1Len == TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN) */
  {
    TCPIP_ASSERT(TcpSeg1Ptr != NULL_PTR);

    /* IV is present in seg1 */
    pExplicitIVPtr = TcpSeg1Ptr;
  }

  /* #20 Load Iv (implicit Iv + explicit Iv) into the key element */

  /* Nonce for Gcm is 12 bytes and is constructed as
   * |Gcm Iv | Tls seq No.|
   * |0     3|4         11|
   */
  tmpKey.KeyId = TcpIp_GetHsTemporaryBufferKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  tmpKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  tmpKey.KeyLen = 0;

  /* Copy the explicit Iv (sequence number) into the tmp key */
  retVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &tmpKey);
  retVal |= TCPIP_CSM_KeyElementSet(tmpKey.KeyId, tmpKey.KeyElementId, pExplicitIVPtr, TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN);

  rxGcmIvKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  rxGcmIvKey.KeyElementId = CRYPTO_KE_CIPHER_IV;

  /* Copy explicit Iv from temp key to Gcm decrypt key and set it valid. */
  retVal |= TCPIP_CSM_KeyElementCopyPartial(
    tmpKey.KeyId,
    tmpKey.KeyElementId,
    0,
    TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN,
    TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN,
    rxGcmIvKey.KeyId,
    rxGcmIvKey.KeyElementId
  );

  retVal |= TCPIP_CSM_KeySetValid(rxGcmIvKey.KeyId);
  if (retVal == E_NOT_OK)
  {
    /* If not successful, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_SETAESIVVALUE;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_SETAESIVVALUE_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* RFC3602 - The AES-CBC Cipher Algorithm
   * 2.4.  Block Size and Padding
   *
   * The AES uses a block size of sixteen octets (128 bits).
   *
   * Padding is required by the AES to maintain a 16-octet (128-bit)
   * blocksize.  Padding MUST be added, as specified in [ESP], such that
   * the data to be encrypted (which includes the ESP Pad Length and Next
   * Header fields) has a length that is a multiple of 16 octets. */

  /* Check the input data length of the AES-128-CBC operation to its alignment of a multiple of the used block size */
  if ((DataLen % TCPIP_TLS_AES_BLOCK_LEN) == 0u)
  {
    /* #10 Input data length aligned to the used block size - return E_OK */
    retVal = E_OK;
  }
  else
  {
    /* #20 Input data length not aligned - Trigger TLS alert and return E_NOT_OK */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcCheckBlocksizeAlignment() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc(
 TcpIp_TlsConnectionIterType TlsConIdx,
 uint8                       ContentType,
 TCPIP_P2C(uint8)            DataPtr,
 uint16                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                          retVal  = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Get size of the next available TLS Rx buffer segment */
  uint32                        nextFreeTlsSegLen = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Length of data processed so far */
  uint16                        copiedLen         = 0u;
  /* Pointer to TCP segment 1 */
  TCPIP_P2C(uint8)              tcpSeg1Ptr     = TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr;
  /* Variable to store length of TCP segment 1 */
  uint16                        tcpSeg1Len     = TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;
  /* Pointer to TCP segment 1 */
  TCPIP_P2C(uint8)              tcpSeg2Ptr = DataPtr;
  /* Variable to store length of TCP segment 2 */
  uint16                        tcpSeg2Len = DataLen;
  /* Variables to store length of Iv in TCP segment 1 */
  uint16                        ivInTcpSeg1Len;
  /* Variables to store length of Iv in TCP segment 2 */
  uint16                        ivInTcpSeg2Len;

  /* ----- Implementation ----------------------------------------------- */
  /* Handling of wraparound in TCP and TLS Rx buffers -
   * The buffer before and after wraparound are considered as two separate segments
   * TLS wraparound --> TlsSeg1 and TlsSeg2
   * TCP wraparound --> TcpSeg1 and TcpSeg2
   * It is ensured by the caller that sufficient space is available in TLS Rx buffer
   * to decrypt all the ciphertext in TCP buffer
   */

  /* #10 If the size of the frame is valid, decrypt the received frame */
  if ((tcpSeg1Len + tcpSeg2Len) > TCPIP_TLS_AES128_IV_LEN)
  {
    /* #20 Extract the Iv from the TCP buffer segment(s) and set AES key element */
    if (tcpSeg1Len < TCPIP_TLS_AES128_IV_LEN)
    {
      /* TCP segment 1 contains Iv */
      ivInTcpSeg1Len = tcpSeg1Len;
      /* Part of Iv is present in TCP segment 2 */
      ivInTcpSeg2Len = (uint8)(TCPIP_TLS_AES128_IV_LEN - tcpSeg1Len);
      /* No ciphertext present in TCP segment 1 */
      tcpSeg1Len = 0u;
    }
    else /* (tcpSeg1Len >= TCPIP_TLS_AES128_IV_LEN) */
    {
      /* Iv is completely in TCP segment 1 */
      ivInTcpSeg1Len = TCPIP_TLS_AES128_IV_LEN;
      /* No Iv in TCP segment 2 */
      ivInTcpSeg2Len = 0u;
      /* Update size of TCP segment 1 by decrementing Iv length */
      tcpSeg1Len -= TCPIP_TLS_AES128_IV_LEN;
    }

    /* Extract Iv from TCP segment(s) and set respective Aes Key element */
    retVal = TcpIp_TlsCoreRl_RxCipherDecryptAes128CbcSetIv(TlsConIdx, tcpSeg1Ptr, ivInTcpSeg1Len, tcpSeg2Ptr);

    if (retVal == E_OK)
    {
      /* #30 Perform Aes128 Cbc decryption of data considering wraparound of TCP and TLS buffer */
      if (tcpSeg1Len == 0u)
      {
        /* Scenario 1: No TCP buffer wraparound, only use case for alert message */
        retVal = TcpIp_TlsCoreRl_DecryptAes128CbcScenario1(TlsConIdx, ContentType, &tcpSeg2Ptr[ivInTcpSeg2Len],
          (tcpSeg2Len - ivInTcpSeg2Len), &copiedLen);
      }
      else if (nextFreeTlsSegLen >= ((uint32)tcpSeg1Len + tcpSeg2Len))
      {
        /* Scenario 2: TCP buffer wraparound and no TLS buffer wraparound */
        retVal = TcpIp_TlsCoreRl_DecryptAes128CbcScenario2(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_IV_LEN],
          tcpSeg1Len, &tcpSeg2Ptr[0], tcpSeg2Len, &copiedLen);
      }
      else if (nextFreeTlsSegLen >= tcpSeg1Len)
      {
        /* Scenario 3: TCP and TLS buffer wraparound, TLS buffer wraps around after TCP buffer wraparound */
        retVal = TcpIp_TlsCoreRl_DecryptAes128CbcScenario3(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_IV_LEN],
          tcpSeg1Len, &tcpSeg2Ptr[0], tcpSeg2Len, &copiedLen);
      }
      else /* (nextFreeTlsSegLen < tcpSeg1Len) */
      {
        /* Scenario 4: TCP and TLS buffer wraparound, TLS buffer wraps around before TCP buffer wraparound */
        retVal = TcpIp_TlsCoreRl_DecryptAes128CbcScenario4(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_IV_LEN],
          tcpSeg1Len, &tcpSeg2Ptr[0], tcpSeg2Len, &copiedLen);
      }

      /* Check CSM operation result before proceeding */
      if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, retVal, 0u, 0u, TCPIP_TLS_FCTID_CORE_RL_RXHSADDATA) == E_OK)
      {
        /* Remove padding from the decrypted data, and update the copied length */
        retVal = TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf(TlsConIdx, ContentType, &copiedLen);
        /* Set the Rx copiedLen to the total plaintext so far into the TLS Rx buffer */
        TcpIp_SetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, copiedLen);
      }
    }
  }

  /* Reset the DataSplit struct if necessary */
  if (TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen != 0u)
  {
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAes128Cbc */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm
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
/* PRQA S 6010, 6030, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint8                       ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Variable to store size of next available TLS Rx buffer segment to store plaintext output */
  uint32                        nextFreeTlsSegLen = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  uint16                        copiedLen = 0u;
  Std_ReturnType                retVal;
  /* Store pointer to TCP segment 1 */
  TCPIP_P2C(uint8)              tcpSeg1Ptr = TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr;
  /* Store length of TCP segment 1 */
  uint16                        tcpSeg1Len = TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen;
  /* Store pointer to TCP segment 2 */
  TCPIP_P2C(uint8)              tcpSeg2Ptr = DataPtr;
  /* Store length of TCP segment 2 */
  uint16                        tcpSeg2Len = DataLen;
  /* Local buffer to store AAD bytes */
  uint8                         addAuthData[TCPIP_TLS_AES128_GCM_AADATA_LEN] = { 0 };
  /* Local buffer to store authentication tag */
  uint8                         authTag[TCPIP_TLS_AES128_GCM_AUTHTAG_LEN] = { 0 };
  /* Length of the cipher text present in the TCP buffer segment 1 */
  uint16                        ciphertextInTcpSeg1Len;
  /* Length of the cipher text present in the TCP buffer segment 2 */
  uint16                        ciphertextInTcpSeg2Len;
  /* Length of the Iv present in the TCP buffer segment 1 */
  uint16                        ivInTcpSeg1Len;
  /* Length of the Iv present in the TCP buffer segment 2 */
  uint16                        ivInTcpSeg2Len;
  /* Total length of ciphertext in the TCP segment(s) */
  uint16                        contentLen = tcpSeg1Len + tcpSeg2Len - TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN - TCPIP_TLS_AES128_GCM_AUTHTAG_LEN;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract the Iv from the TCP segment(s), and set the Aes 128 Gcm key element */

  /* Determine how the Iv is stored between the two TCP segments */
  if (tcpSeg1Len < TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN)
  {
    /* Iv is split between TCP segment 1 and 2, update the necessary length offsets */
    ivInTcpSeg1Len = tcpSeg1Len;
    ivInTcpSeg2Len = TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN - (uint16)tcpSeg1Len;
    ciphertextInTcpSeg1Len = 0u;
  }
  else /* (tcpSeg1Len >= TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN) */
  {
    /* Iv is entirely in TCP segment 1, update the necessary length offsets */
    ivInTcpSeg1Len = TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;
    ivInTcpSeg2Len = 0u;
    ciphertextInTcpSeg1Len = tcpSeg1Len - TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN;
  }
  /* Extract Iv from TCP segment(s) and set into the respective GCM key element */
  retVal = TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128GcmSetIv(TlsConIdx, tcpSeg1Ptr, ivInTcpSeg1Len, tcpSeg2Ptr);

  /* #20 Generate AAD for the received TLS Rl frame */
  TcpIp_TlsCoreCrypto_AEADAes128GcmGenerateAAData(TcpIp_GetRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx), contentLen, ContentType, &addAuthData[0]);

  /* #30 Extract plaintext authentication tag from received TLS Rl frame */
  if (tcpSeg2Len < TCPIP_TLS_AES128_GCM_AUTHTAG_LEN)
  {
    /* Authentication tag is split between the two TCP segments */
    uint16 authTagLenInPart1 = (TCPIP_TLS_AES128_GCM_AUTHTAG_LEN - tcpSeg2Len);
    uint32 authTagOffsetInPart1 = ((uint32)tcpSeg1Len - authTagLenInPart1);

    /* Copy authentication tag in the two TCP segments into local auth buffer */
    VStdMemCpy(&authTag[0], &tcpSeg1Ptr[authTagOffsetInPart1], authTagLenInPart1);                                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(&authTag[authTagLenInPart1], &tcpSeg2Ptr[0], tcpSeg2Len);                                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Update the length of cipher text in the TCP buffer segment 1 */
    ciphertextInTcpSeg1Len -= authTagLenInPart1;
    /* There is no cipher text in the TCP buffer segment 2 */
    ciphertextInTcpSeg2Len = 0u;
  }
  else
  {
    /* Authentication tag is entirely in TCP segment 2 */
    /* Copy the authentication tag to the local buffer */
    VStdMemCpy(&authTag[0], &tcpSeg2Ptr[tcpSeg2Len - TCPIP_TLS_AES128_GCM_AUTHTAG_LEN], TCPIP_TLS_AES128_GCM_AUTHTAG_LEN); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Update the length of cipher text in the TCP buffer segment 2 */
    ciphertextInTcpSeg2Len = tcpSeg2Len - TCPIP_TLS_AES128_GCM_AUTHTAG_LEN;
  }

  /* #40 Wrap around TLS buffer here if current segment is insufficient to start decryption */
  /* [Sliding End Index]: (1) If there is insufficient space remaining in TLS Rx buffer
   * before wraparound, skip the few remaining bytes and wraparound
   */
  if (nextFreeTlsSegLen <= TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
                TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* Slide the frame start index if necessary */
    if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
    {
      TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    }

    /* Update the write index to the start of the TLS buffer */
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
          TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    /* Update size of next free TLS Rx buffer segment */
    nextFreeTlsSegLen = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  }

  /* #50 Perform Aes128 Gcm decryption of data considering wraparound of TcpIp and Tls buffer */
  if (ciphertextInTcpSeg2Len == 0u)
  {
    /* Scenario 1: No TCP buffer wraparound (ciphertext in TCP segment 1) */
    retVal |= TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1(TlsConIdx, ContentType,
       &tcpSeg1Ptr[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN], ciphertextInTcpSeg1Len, addAuthData, authTag, &copiedLen);
  }
  else if (ciphertextInTcpSeg1Len == 0u)
  {
    /* Scenario 1: No TCP buffer wraparound (ciphertext in TCP segment 2) */
    retVal |= TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1(TlsConIdx, ContentType, &tcpSeg2Ptr[ivInTcpSeg2Len],
       (ciphertextInTcpSeg2Len - ivInTcpSeg2Len), addAuthData, authTag, &copiedLen);
  }
  else if (nextFreeTlsSegLen >= ((uint32)ciphertextInTcpSeg1Len + ciphertextInTcpSeg2Len + TCPIP_TLS_AES128_BLOCKSIZE))
  {
    /* Scenario 2: TCP buffer wraparound and no TLS buffer wraparound */
    retVal |= TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN],
       ciphertextInTcpSeg1Len, &tcpSeg2Ptr[0], ciphertextInTcpSeg2Len, addAuthData, authTag, &copiedLen);
  }
  else if (nextFreeTlsSegLen >= ciphertextInTcpSeg1Len)
  {
    /* Scenario 3: TLS buffer wraparound after TCP buffer wraparound */
    retVal |= TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN],
       ciphertextInTcpSeg1Len, &tcpSeg2Ptr[0], ciphertextInTcpSeg2Len, addAuthData, authTag, &copiedLen);
  }
  else /* (nextFreeTlsSegLen < ciphertextInTcpSeg1Len) */
  {
    /* Scenario 4: TLS buffer wraparound before TCP buffer wraparound */
    retVal |= TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4(TlsConIdx, &tcpSeg1Ptr[TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN],
       ciphertextInTcpSeg1Len, &tcpSeg2Ptr[0], ciphertextInTcpSeg2Len, addAuthData, authTag, &copiedLen);
  }

  /* Check CSM operation result before proceeding */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, retVal, 0u, 0u, TCPIP_TLS_FCTID_CORE_RL_RXHSADDATA) == E_OK)
  {
    /* Set the Rx copiedLen to the total plaintext so far into the TLS Rx buffer */
    TcpIp_SetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, copiedLen);
  }

  /* Reset the DataSplit struct, if necessary */
  if (TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen != 0u)
  {
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RxCipherDecryptAEADAes128Gcm */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_CopyDataToRxBuf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy the received data into the corresponding Tls buffer */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    /* AdHs TLS Rx buffer can wraparound */
    TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound(TlsConIdx, DataPtr, DataLen, CopiedLenPtr);
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
    /* Alert TLS Rx buffer will not wraparound */
    TcpIp_TlsCoreRl_CopyDataToRxBufAl(TlsConIdx, DataPtr, DataLen, CopiedLenPtr);
  }
  else if (ContentType == TCPIP_TLS_CT_CCS)
  {
    /* Ccs TLS Rx buffer will not wraparound */
    TcpIp_TlsCoreRl_CopyDataToRxBufCcs(TlsConIdx, DataPtr, DataLen, CopiedLenPtr);
  }
  else
  {
   /* Nothing to do. This should never happen. ContentType check is done by Record Layer Rx functions. */
  }
} /* TcpIp_TlsCoreRl_CopyDataToRxBuf() */

/**********************************************************************************************************************
 *  TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(uint32, TCPIP_CODE) TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables----------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxIterType currEndIdx = TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferRxIterType writeIdx   = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  TcpIp_TlsBufferRxIterType readIdx    = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32 tlsSegLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on position of read and write index, calculate size of next free TLS Rx buffer segment */
  if (writeIdx < readIdx)
  {
    /* Calculate space till unread data */
    tlsSegLen = (uint32)readIdx - (uint32)writeIdx;
  }
  else
  {
    /* Calculate space till end of buffer */
    tlsSegLen = (uint32)currEndIdx - (uint32)writeIdx;
  }

  return tlsSegLen;
} /* TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint8                       ContentType,
  uint16                      RlFrameLen)
{
  /* ----- Local Variables----------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* Flag indicates if Rl frame fits */
  boolean fitFlag;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the content type, check if Rx buffer has sufficient space */
  switch (ContentType)
  {
    case TCPIP_TLS_CT_HS:
    case TCPIP_TLS_CT_AD:
    {
      /* Since AdHs buffer is ring buffer, calculate space available based on fill level */
      /* Calculate total free space available in TLS Rx AdHs buffer */
      TcpIp_TlsBufferRxIterType totalFreeSpace = (TcpIp_GetTlsBufferRxAdHsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx)
        - TcpIp_GetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

      /* If possible also request for 4 blocks of data more */
      if (totalFreeSpace > TCPIP_TLS_MIN_BUFFER_SIZE)
      {
        /* Decrement 4 block of size, since this is reserved for [Sliding End Index] */
        totalFreeSpace -= TCPIP_TLS_MIN_BUFFER_SIZE;
      }

      if (RlFrameLen <= totalFreeSpace)
      {
        fitFlag = TRUE;
      }
      else
      {
        fitFlag = FALSE;
      }
      break;
    }
    case TCPIP_TLS_CT_AL:
    {
      /* Alert buffer is linear and always overwritten so just check against whole buffer */
      if (RlFrameLen <= TcpIp_GetTlsBufferRxAlLengthOfTlsBufferMgmt(tlsBufferMgmtIdx))
      {
        fitFlag = TRUE;
      }
      else
      {
        fitFlag = FALSE;
      }
      break;
    }
    case TCPIP_TLS_CT_CCS:
    {
      /* Ccs buffer is linear and always overwritten so just check against whole buffer */
      if (RlFrameLen <= TcpIp_GetTlsBufferRxCcsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx))
      {
        fitFlag = TRUE;
      }
      else
      {
        fitFlag = FALSE;
      }
      break;
    }
    default:
    {
      /* Invalid content type */
      fitFlag = FALSE;
      break;
    }
  }

  return fitFlag;
} /* TcpIp_TlsCoreRl_RlFrameFitsInTlsRxBuffer */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* data copied into TLS buffer so far */
  uint16 copiedLen = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy the data from TCP buffer to the TLS Rx buffer, considering wraparound */
  do
  {
    /* Get size of next available linear buffer segment in TLS Rx buffer */
    /* Next free TLS segment could be larger than uint16 */
    uint32 nextFreeTlsSegLen = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
    /* Number of bytes to copy in this call */
    uint16 dataToCopyLen = (DataLen - copiedLen);

    /* Check how much data can be copied into the TLS Rx buffer */
    if (dataToCopyLen <= nextFreeTlsSegLen)
    {
      /* Data fits into the available space, copy and update the write index */
      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),
        &DataPtr[copiedLen], (uint32)dataToCopyLen);

      /* Update the WriteIdx and the copied data length */
      TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, dataToCopyLen);

      copiedLen += dataToCopyLen;
    }
    else
    {
      /* Buffer wraps around, so write only till the current end Idx */
      /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
      VStdMemCpy(TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), DataPtr,
        nextFreeTlsSegLen);

      /* Wrap around Tls buffer since all space till end has been written into */
      TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));

      /* Update copied length with the actual copied data. Rest of the data will be copied within the next function call */
      copiedLen += (uint16)nextFreeTlsSegLen;
    }
  } while (copiedLen < DataLen);

  /* Update the total copied length */
  *CopiedLenPtr = copiedLen;

} /* TcpIp_TlsCoreRl_CopyDataToTlsRxBufAdHsWithWraparound() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_CopyDataToRxBufCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBufCcs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Only one Ccs message is received and the Ccs buffer MUST be sufficient to store the complete message */
  TCPIP_ASSERT(DataLen <= TcpIp_GetTlsBufferRxCcsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx));

  /* #10 Copy data into Tls Ccs buffer */
  VStdMemCpy(TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), DataPtr, DataLen); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* Increment the Ccs writeIdx with data copied */
  TcpIp_AddTlsBufferRxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, DataLen);

  /* Update the copied length */
  *CopiedLenPtr = DataLen;

} /* TcpIp_TlsCoreRl_CopyDataToRxBufCcs() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_CopyDataToRxBufAl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE)  TcpIp_TlsCoreRl_CopyDataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr,
  uint16 DataLen,
  TCPIP_P2V(uint16) CopiedLenPtr)
{
   /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAlStartIdxOfTlsBufferMgmtType rxAlBufferStartIdx = TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(
                                                                          tlsBufferMgmtIdx);
  /* Alert buffer is not wrap around and is designed to store only 1 alert frame completely */
  TCPIP_ASSERT(DataLen <= (TcpIp_GetTlsBufferRxAlEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx) - TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx)));
  TCPIP_ASSERT(*CopiedLenPtr == 0);

  /* #10 Copy the alert message directly into the Tls alert buffer */
  /* This function is designed to hold only the last received Alert, so always write to start of the buffer */
  VStdMemCpy(TcpIp_GetAddrTlsBufferRx(rxAlBufferStartIdx), &DataPtr[0], DataLen);                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

  /* Update the Ccs writeIdx */
  TcpIp_AddTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, DataLen);

  /* Update copied length */
  *CopiedLenPtr = DataLen;
} /* TcpIp_TlsCoreRl_CopyDataToRxBufAl() */

 /**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcScenario1
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on content type, start Aes128 Cbc decryption of TLS frame in a single TCP buffer segment */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    retVal = TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs(TlsConIdx, DataPtr, DataLen, CopiedLenPtr);
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
    retVal = TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl(TlsConIdx, DataPtr, DataLen, CopiedLenPtr);
  }
  else
  {
  /* Should never happen. ContentType Check is done by Record Layer Rx functions */
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcScenario1() */

 /**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC)     ContentType,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on content type, start Aes128 Gcm decryption of data in linear TcpIp buffer */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    retVal = TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs(TlsConIdx, DataPtr, DataLen, AuthDataPtr, AuthTagPtr, CopiedLenPtr);
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
    retVal = TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl(TlsConIdx, DataPtr, DataLen, AuthDataPtr, AuthTagPtr, CopiedLenPtr);
  }
  else
  {
    /* Should never happen. ContentType Check is done by Record Layer Rx functions */
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario1() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcScenario4
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario4(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decrpytJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Variables to store size and pointer of TLS segment 1 */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variables to store size and pointer of TLS segment 2 */
  TCPIP_P2V(uint8)   tlsSeg2Ptr;
  uint32             tlsSeg2Len;
  /* Variable to store length of plaintext output */
  uint32             plaintextLen;
  /* Variable to store length of ciphertext consumed from TCP Segment 1 */
  uint32             ciphertextReadTcpSeg1;
  /* Variable to store size of plaintext output buffer (TLS segment) for CSM call */
  uint32             plaintextBufLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 4: TLS buffer wraparound before TCP buffer wraparound */
  TCPIP_ASSERT(tlsSeg1Len < DataSeg1Len);

  /* #10 Start Aes128 Cbc streaming, and decrypt TCP segment 1 that can fit into TLS segment 1 */
  plaintextBufLen = tlsSeg1Len;
  (void)TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_STREAMSTART, DataSeg1Ptr, tlsSeg1Len, tlsSeg1Ptr, &plaintextBufLen);
  /* Update the plaintext output size */
  plaintextLen = plaintextBufLen;

  /* Update size of ciphertext consumed */
  ciphertextReadTcpSeg1 = tlsSeg1Len;
  /* Update length of TLS segment 1 based on size of plaintext output */
  tlsSeg1Len -= plaintextBufLen;

  /* [Sliding End Index]: (1) If insufficient space remaining in TLS segment 1, skip the remaining space
   * and wraparound. It is ensured by caller that even after skipping these bytes, sufficient space is available
   * for the plaintext output
   */
  if (tlsSeg1Len <= TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    /* Update the Write Idx and shift the current End Idx */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextBufLen);
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
         TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* Shift frame StartIdx if necessary */
    if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
    {
      TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    }
  }

  /* #20 Wraparound TLS buffer and decrypt remaining ciphertext into TLS segment 2 */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));

  /* Get size and pointer of TLS segment 2 */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);

  /* Decrypt remaining ciphertext in TCP segment 1 into TLS segment 2 */
  plaintextBufLen = tlsSeg2Len;
  retVal = TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataSeg1Ptr[ciphertextReadTcpSeg1], (DataSeg1Len - ciphertextReadTcpSeg1),
    tlsSeg2Ptr, &plaintextBufLen);
  /* Update size of plaintext output */
  plaintextLen += plaintextBufLen;

  /* Update the WriteIdx with size of plaintext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextBufLen);
  /* Update TLS segment 2 pointer and size with size of plaintext output */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len -= plaintextBufLen;

  /* Decrypt ciphertext in TCP segment 2 into TLS segment 2 and stop Aes128 Cbc streaming */
  plaintextBufLen = tlsSeg2Len;
  retVal |= TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, DataSeg2Ptr,
                        DataSeg2Len, tlsSeg2Ptr, &plaintextBufLen);

  /* Update the WriteIdx with the size of plaintext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextBufLen);
  /* Update length of plaintext output */
  plaintextLen += plaintextBufLen;

  /* #30 Update copied length with total length of plaintext output */
  *CopiedLenPtr = (uint16)plaintextLen;

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcScenario4 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  Crypto_VerifyResultType verifyResult = CSM_E_VER_NOT_OK;
  uint32             decryptJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to TLS segment 1 */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                 tlsBufferMgmtIdx));
  /* Size of TLS segment 1 */
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Pointer to TLS Rx buffer segment 2 */
  TCPIP_P2V(uint8)   tlsSeg2Ptr;
  /* Size of TLS Rx buffer segment 2 */
  uint32             tlsSeg2Len;
  /* Variable to store total plaintext length */
  uint32             plaintextLen;
  /* Variable to track ciphertext consumed in TCP segment 1 */
  uint32             ciphertextCosumedTcpSeg1 = tlsSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE;
  /* Variable to store size of plaintext output buffer for Csm call */
  uint32             plaintextOutBufLen;

  /* Scenario 4: TLS buffer wraparound before TCP buffer wraparound */
  TCPIP_ASSERT(tlsSeg1Len < DataSeg1Len);

  /* #10 Start Aes128 Gcm streaming, and decrypt TCP segment 1 that can fit in TLS segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, DataSeg1Ptr,
                            ciphertextCosumedTcpSeg1, AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN,
                            AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, NULL_PTR);

  /* Update the Write Idx with length of plaintext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (uint16)plaintextOutBufLen);

  /* Update plaintext output */
  plaintextLen = plaintextOutBufLen;

  /* Update actual length of TLS segment 1 */
  tlsSeg1Len -= plaintextOutBufLen;

  /* [Sliding End Index]: (1) A this point we can be sure that <= TCPIP_TLS_MIN_BUFFER_SIZE space is
   * remaining in TLS segment 1. So skip the few remaining bytes and wraparound TLS Rx buffer
   */
  if (tlsSeg1Len <= TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    /* Shift the current End Idx */
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* Shift Start Idx if necessary */
    if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
    {
      TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    }
  }

  /* #20 Wrap around TLS buffer and decrypt remaining ciphertext in TCP segment 1 into TLS segment 2 */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (uint16)TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));

  /* Update the TLS Rx buffer segment 2 */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);

  /* Decrypt remaining ciphertext in TCP segment 1 into TLS segment 2 */
  plaintextOutBufLen = tlsSeg2Len;
  retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataSeg1Ptr[ciphertextCosumedTcpSeg1],
                            ((uint32)DataSeg1Len - ciphertextCosumedTcpSeg1), NULL_PTR, 0, AuthTagPtr,
                            TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg2Ptr, &plaintextOutBufLen, NULL_PTR);

  /* Update the WriteIdx with plaintext output length from last call */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);

  /* Update total plaintext output length */
  plaintextLen += plaintextOutBufLen;

  /* Update pointer to TLS segment 2 */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Update length of TLS segment 2 */
  tlsSeg2Len -= plaintextOutBufLen;

  /* #30 Decrypt TCP segment 2 into TLS segment 2 and stop Aes128 Gcm streaming */
  plaintextOutBufLen = tlsSeg2Len;
  retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, DataSeg2Ptr,
                            DataSeg2Len, NULL_PTR, 0, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg2Ptr,
                            &plaintextOutBufLen, &verifyResult);

  /* Update the WriteIdx with plaintext output length */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);

  /* Update total plaintext output length */
  plaintextLen += plaintextOutBufLen;

  /* #40 Update the copied length with the total plaintext output length */
  *CopiedLenPtr = (uint16)plaintextLen;

  /* Check if authentication tag was verified successfully */
  if (verifyResult != CSM_E_VER_OK)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario4 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcScenario3
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario3(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decrpytJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  uint32             bytesReadFromTcpSeg2 = 0;
  /* Variable to store TLS segment 1 pointer */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                  tlsBufferMgmtIdx));
  /* Variable to store TLS segment 1 length */
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variable to store TLS segment 2 pointer */
  TCPIP_P2V(uint8)   tlsSeg2Ptr;
  /* Variable to store TLS segment 2 length */
  uint32             tlsSeg2Len;
  /* Variable to track the length of the plaintext output buffer for next Csm call */
  uint32             plaintextOutBufLen;
  /* Total plaintext length */
  uint32             plaintextLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 3: TLS buffer wraparound after TCP buffer wraparound */
  TCPIP_ASSERT(DataSeg1Len < tlsSeg1Len);

  /* #10 Start Aes128 Cbc streaming, decrypt TCP segment 1 into TLS segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataSeg1Ptr[0], DataSeg1Len, tlsSeg1Ptr,
                       &plaintextOutBufLen);
  /* Updated the length of plaintext output */
  plaintextLen = plaintextOutBufLen;

  /* Update the writIdx with the size of plaintext output from previous call */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextOutBufLen);

  /* Update TLS segment 1 pointer and size with the length of plaintext output from previous call */
  tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg1Len -= plaintextOutBufLen;

  /* #20 If > 4 blocks of space remaining in TLS segment 1, decrypt ciphertext in TCP segment 2 into TLS segment 1 */
  if (tlsSeg1Len > TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    uint16 bytesToConsumeTcpSeg2;

    /* Calculate how much ciphertext can be decrypted into TLS segment 1 */
    if (((uint32)DataSeg2Len + TCPIP_TLS_AES128_BLOCKSIZE) <= tlsSeg1Len)
    {
      bytesToConsumeTcpSeg2 = DataSeg2Len;
    }
    else
    {
      bytesToConsumeTcpSeg2 = (uint16)tlsSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE;
    }

    /* Consume ciphertext from TCP segment 2 into TLS segment 1 */
    plaintextOutBufLen = tlsSeg1Len;
    retVal |= TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataSeg2Ptr[0], bytesToConsumeTcpSeg2, tlsSeg1Ptr,
                          &plaintextOutBufLen);
    /* */
    plaintextLen += plaintextOutBufLen;

    /* Update the available space and consumed bytes */
    bytesReadFromTcpSeg2 = bytesToConsumeTcpSeg2;
    tlsSeg1Len -= plaintextOutBufLen;

    /* Update the WriteIdx */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextOutBufLen);
  }

  /* [Sliding End Index]: (1) If there is less than a block of space remaining in TLS segment 1
   * skip this space and wraparound to the start of the TLS buffer, which has sufficient space
   * to accept remaining plaintext
   */
  /* #30 Shift the End Idx if there is still space remaining in TLS segment 1 */
  if (tlsSeg1Len <= TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
         TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* Shift StartIdx if necessary */
    if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
    {
      TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    }
  }

  /* #40 Wraparound TLS Rx buffer and decrypt remaining ciphertext in TCP segment 2 into TLS segment 2 */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  /* Update pointer and length of TLS segment 2 */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);

  /* Decrypt rest of data available in TCP segment 2 into TLS segment 2 and stop Aes128 Cbc streaming */
  plaintextOutBufLen = tlsSeg2Len;
  if (bytesReadFromTcpSeg2 < DataSeg2Len)
  {
    /* Feed the second segment of data and stop streaming */
    retVal |= TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataSeg2Ptr[bytesReadFromTcpSeg2],
                          (DataSeg2Len - bytesReadFromTcpSeg2), tlsSeg2Ptr, &plaintextOutBufLen);
  }
  else
  {
    /* Stop streaming if all data has already been consumed */
    retVal |= TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, tlsSeg2Ptr, &plaintextOutBufLen);
  }
  /* Update the total length of plaintext output */
  plaintextLen += plaintextOutBufLen;

  /* Update the WriteIdx with length of plaintext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextOutBufLen);
  /* Update total copied length */
  *CopiedLenPtr = (uint16)plaintextLen;

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcScenario3 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decryptJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to TLS Rx AdHs buffer segment 1 */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                 tlsBufferMgmtIdx));
  /* Size of TLS Rx AdHs buffer segment 1 */
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Ciphertext consumed so far from TCP segment 2 */
  uint32             ciphertextConsumedTcpSeg2 = 0u;
  /* Csm result */
  Crypto_VerifyResultType verifyResult = CSM_E_VER_NOT_OK;
  /* Pointer to TLS Rx AdHs buffer segment 2 */
  TCPIP_P2V(uint8)   tlsSeg2Ptr;
  /* Size of TLS Rx AdHs buffer segment 2 */
  uint32             tlsSeg2Len;
  /* Size of the plaintext output buffer for the next Csm call */
  uint32             plaintextOutBufLen;
  /* Total plaintext output length */
  uint32             plaintextLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 3a: Enough space available in next TLS segment to decrypt TCP segment 1 */
  /* Tls buffer wraparound occurs more than TCPIP_TLS_AES128_BLOCKSIZE bytes after TcpIp wraparound */
  TCPIP_ASSERT(((tlsSeg1Len - DataSeg1Len) > TCPIP_TLS_AES128_BLOCKSIZE));

  /* #10 Start Aes128 GCM streaming, and decrypt segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataSeg1Ptr[0], DataSeg1Len, AuthDataPtr,
    TCPIP_TLS_AES128_GCM_AADATA_LEN, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, NULL_PTR);

  /* Update actual size of TLS segment 1 and the total plaintext decrypted so far */
  tlsSeg1Len -= plaintextOutBufLen;
  plaintextLen = plaintextOutBufLen;

  /* #20 If possible, decrypt enough data from segment 2 until Tls buffer wraparound */
  if (tlsSeg1Len > (TCPIP_TLS_MIN_BUFFER_SIZE))
  {
    /* Ciphertext to consume from TCP segment 2 */
    uint16 ciphertextToConsumeTcpSeg2;

    /* Calculate ciphertext from TCP segment 2 that can fit into TLS segment 1 */
    if (DataSeg2Len <= tlsSeg1Len)
    {
      ciphertextToConsumeTcpSeg2 = DataSeg2Len - TCPIP_TLS_AES128_BLOCKSIZE;
    }
    else
    {
      ciphertextToConsumeTcpSeg2 = (uint16)(tlsSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE);
    }

    /* Decrypt ciphertext from TCP segment 2 into remaining space in TLS segment 1 */
    plaintextOutBufLen = tlsSeg1Len;
    retVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataSeg2Ptr[0], ciphertextToConsumeTcpSeg2, NULL_PTR, 0u,
      AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, &tlsSeg1Ptr[plaintextLen], &plaintextOutBufLen, NULL_PTR);

    /* Update ciphertext consumed from TCP segment 2 */
    ciphertextConsumedTcpSeg2 = ciphertextToConsumeTcpSeg2;
    /* Update TLS segment 1 length with total plaintext output buffer length */
    tlsSeg1Len -= plaintextOutBufLen;
    /* Update the plaintext output so far */
    plaintextLen += plaintextOutBufLen;
  }

  /* Update the WriteIdx with the total plaintext output so far */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextLen);

  /* [Sliding End Index]: (1) If less that 4 blocks of space, skip the few remaining space at the end of TLS buffer
      and wraparound to the start of the TLS buffer
   */
  if (tlsSeg1Len <= TCPIP_TLS_MIN_BUFFER_SIZE)
  {
    /* Set the current endIdx to the current writeIdx */
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
            TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
    /* Shift Start Idx if necessary */
    if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
    {
      TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    }
  }

  /* #30 Wrap around the TLS buffer, and decrypt remaining ciphertext into TLS segment 2 */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  /* Obtain the TLS segment 2 information */
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);

  /* Decrypt remaining ciphertext in TCP segment 2 into TLS segment 2 and stop Aes128 Gcm streaming */
  if (ciphertextConsumedTcpSeg2 < DataSeg2Len)
  {
    /* Decrypt ciphertext into TLS segment 2 */
    plaintextOutBufLen = tlsSeg2Len;
    retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      &DataSeg2Ptr[ciphertextConsumedTcpSeg2], (DataSeg2Len - ciphertextConsumedTcpSeg2), NULL_PTR, 0u, AuthTagPtr,
      TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg2Ptr, &plaintextOutBufLen, &verifyResult);
  }
  else
  {
    /* Stop streaming if all ciphertext has been decrypted */
    retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, NULL_PTR, 0u,
      AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg2Ptr, &plaintextOutBufLen, &verifyResult);
  }

  /* Update the WriteIdx and copied length */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);
  /* Update the total plaintext output so far */
  plaintextLen += plaintextOutBufLen;
  /* Update the total copied length */
  *CopiedLenPtr = (uint16)plaintextLen;

  /* Check if authentication tag was verified successfully */
  if (verifyResult != CSM_E_VER_OK)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Csm verify result */
  Crypto_VerifyResultType verifyResult = CSM_E_VER_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decryptJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to the TLS Rx AdHs buffer segment 1 */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                 tlsBufferMgmtIdx));
  /* Length of TLS Rx AdHs segment 1 */
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Pointer to TLS Rx AdHs buffer segment 2 */
  TCPIP_P2V(uint8)   tlsSeg2Ptr;
  /* Size of TLS Rx AdHs buffer segment 2 */
  uint32             tlsSeg2Len;
  /* Offset of plaintext output in TLS segment 2 */
  uint32 plaintextOffsetTlsSeg2;
  /* Total plaintext output length */
  uint32             plaintextOutputLen;
  /* Length of the plaintext output buffer for the next Csm call */
  uint32             plaintextOutBufLen;
  /* Function return value */
  Std_ReturnType     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 3b: Not enough space available in TLS segment 1 to decrypt TCP segment 1 */
  /* Tls buffer wraparound occurs less than TCPIP_TLS_AES128_BLOCKSIZE bytes after TcpIp wraparound */
  TCPIP_ASSERT((tlsSeg1Len - DataSeg1Len) <= TCPIP_TLS_AES128_BLOCKSIZE);

  /* #10 Start Aes128 Gcm streaming, and decrypt TCP segment 1 (- TCPIP_TLS_AES128_BLOCKSIZE) */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataSeg1Ptr[0],
    ((uint32)DataSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE), AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN, AuthTagPtr,
    TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, NULL_PTR);

  /* Update total plaintext output so far */
  plaintextOutputLen = plaintextOutBufLen;

  /* Update the write index with the plaintext output length */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
     (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);

  /* [Sliding End Index]: (1) */
  /* Shift the End Idx to the current write Idx since only a few bytes of space is remaining at the end */
  TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Shift Start Idx if necessary */
  if (   TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
      == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
  {
    TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  }

  /* #20 Wraparound TLS buffer and decrypt rest of ciphertext in TCP segment 1 into TLS buffer segment 2 */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
  tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg2Len = ((uint32)TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
                   - TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* Decrypt remaining ciphertext in TCP segment 1 into TLS segment 2 */
  plaintextOutBufLen = tlsSeg2Len;
  retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataSeg1Ptr[(DataSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE)],
    TCPIP_TLS_AES128_BLOCKSIZE, NULL_PTR, 0u, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg2Ptr, &plaintextOutBufLen,
    &verifyResult);

  /* Update the actual size of TLS segment 2 */
  tlsSeg2Len -= plaintextOutBufLen;
  /* Update the offset till plaintext output in TLS segment 2 */
  plaintextOffsetTlsSeg2 = plaintextOutBufLen;
  /* Update the total plaintext length */
  plaintextOutputLen += plaintextOutBufLen;

  /* #30 Decrypt ciphertext in TCP segment 2 into TLS segment 2, stop Aes128 Gcm streaming */
  plaintextOutBufLen = tlsSeg2Len;
  retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataSeg2Ptr[0],
    DataSeg2Len, NULL_PTR, 0u, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, &tlsSeg2Ptr[plaintextOffsetTlsSeg2], &plaintextOutBufLen, &verifyResult);

  /* Update the write index with the plaintext output length */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);
  /* Update total plaintext output length */
  plaintextOutputLen += plaintextOutBufLen;

  /* Update total copied length */
  *CopiedLenPtr = (uint16)plaintextOutputLen;

  /* Check if authentication tag was verified successfully */
  if (verifyResult != CSM_E_VER_OK)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Size of the next free TLS segment */
  uint32             nextFreeTlsSegLen = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 3: TLS buffer wraparound after TCP buffer wraparound */
  /* #10 Start Aes128 Gcm streaming, decrypt data in 2 TcpIp buffers into the Tls buffer, considering wraparound */
  if (nextFreeTlsSegLen > ((uint32)DataSeg1Len + TCPIP_TLS_AES128_BLOCKSIZE))
  {
    /* Scenario 3a: Enough space available in next TLS segment to decrypt TCP segment 1 */
    retVal = TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3a(TlsConIdx, DataSeg1Ptr, DataSeg1Len, DataSeg2Ptr, DataSeg2Len,
                  AuthDataPtr, AuthTagPtr, CopiedLenPtr);
  }
  else
  {
    /* Scenario 3b: Not enough space available in next TLS segment to decrypt TCP segment 1 */
    retVal = TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3b(TlsConIdx, DataSeg1Ptr, DataSeg1Len, DataSeg2Ptr, DataSeg2Len,
                 AuthDataPtr, AuthTagPtr, CopiedLenPtr);
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario3 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcScenario2
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decrpytJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Get the pointer and size of the next free TLS Rx buffer segment */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variable to track the length of the plaintext output buffer (TLS segment) for Csm call */
  uint32             plaintextOutBufLen;
  /* Variable to store total plaintext output length */
  uint16             plaintextLen;
  Std_ReturnType     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 2: TCP buffer wraparound and no TLS buffer wraparound */
  TCPIP_ASSERT(tlsSeg1Len >= (uint32)(DataSeg1Len + DataSeg2Len));

  /* #10 Start Aes128 Cbc streaming, decrypt ciphertext from TCP segment 1 into TLS segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_STREAMSTART, DataSeg1Ptr, DataSeg1Len, tlsSeg1Ptr, &plaintextOutBufLen);
  /* Update the copied length with the length of ciphertext output */
  plaintextLen = (uint16)plaintextOutBufLen;

  /* Update the Write Idx with the size of ciphertext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextOutBufLen);

  /* Update pointer and size of TLS Rx buffer segment 1 with plaintext output */
  tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  tlsSeg1Len -= (uint16)plaintextOutBufLen;

  /* #20 Decrypt TCP segment 2 into TLS segment 1, and stop Aes128 Cbc streaming */
  plaintextOutBufLen = tlsSeg1Len;
  retVal |= TCPIP_CSM_Decrypt(decrpytJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataSeg2Ptr[0],
                        DataSeg2Len, tlsSeg1Ptr, &plaintextOutBufLen);
  /* Update the copied length with the length of ciphertext output */
  plaintextLen += (uint16)plaintextOutBufLen;

  /* Update the Write Idx with the ciphertext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextOutBufLen);

  /* #30 Update the copied length with total ciphertext output */
  *CopiedLenPtr = plaintextLen;

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcScenario2 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataSeg1Ptr,
  uint16                      DataSeg1Len,
  TCPIP_P2C(uint8)            DataSeg2Ptr,
  uint16                      DataSeg2Len,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32             decryptJobId =  TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to TLS segment 1 */
  TCPIP_P2V(uint8)   tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                 tlsBufferMgmtIdx));
  /* Length of TLS segment 1 */
  uint32             tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variable to store authentication result */
  Crypto_VerifyResultType verifyResult = CSM_E_VER_NOT_OK;
  /* Variable to store the size of the output buffer passed to Csm call */
  uint32             plaintextOutBufLen;
  /* Total length of plaintext output */
  uint32             plaintextLen;
  Std_ReturnType     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 2: TCP buffer wraparound and no TLS buffer wraparound */
  /* #10 Start Aes128 Gcm streaming, and decrypt segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataSeg1Ptr[0], DataSeg1Len, AuthDataPtr,
                           TCPIP_TLS_AES128_GCM_AADATA_LEN, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr,
                           &plaintextOutBufLen, NULL_PTR);

  /* Update the plaintext output length */
  plaintextLen = plaintextOutBufLen;

  /* Update the WriteIdx with length of plaintext output */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (uint16)plaintextOutBufLen);
  /* Update the pointer and size of TLS segment 1 */
  tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Update actual size of TLS segment 1 */
  tlsSeg1Len -= plaintextOutBufLen;

  /* #20 Decrypt ciphertext from TCP segment 2 into TLS segment 1 */
  plaintextOutBufLen = tlsSeg1Len;
  retVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataSeg2Ptr[0],
                            DataSeg2Len, NULL_PTR, 0u, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr,
                            &plaintextOutBufLen, &verifyResult);

  /* Update writeIdx with length of plaintext out */
  TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (uint16)plaintextOutBufLen);

  /* Update the plaintext output length */
  plaintextLen += plaintextOutBufLen;

  *CopiedLenPtr = (uint16)plaintextLen;

  /* #30 Check if authentication tag was verified successfully */
  if (verifyResult != CSM_E_VER_OK)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmScenario2 */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType                csmRetVal;
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 decryptJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Variables to store the information of TLS segment 1 */
  TCPIP_P2V(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  uint32           tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variable to store the size of the plaintext output buffer for next Csm call */
  uint32 plaintextBufOutLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 1: No TCP buffer wraparound */
  /* #10 Considering TLS buffer wraparound, perform Aes128 Cbc decryption */
  /* Tls buffer has at least (N+1) blocks */
  if (((uint32)DataLen + TCPIP_TLS_AES128_BLOCKSIZE) <= tlsSeg1Len)                                                     /*lint !e574 */
  {
    /* #20 Enough space available in TLS segment 1, invoke single call Aes128 Cbc Decryption */
    plaintextBufOutLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_SINGLECALL, DataPtr, (uint32)DataLen, tlsSeg1Ptr, &plaintextBufOutLen);

    /* Update writeIdx with the length of plaintext output */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextBufOutLen);
  }
  /* Tls buffer has at least N blocks */
  else if ((uint32)DataLen <= tlsSeg1Len)                                                                               /*lint !e574 */
  {
    uint8   tempBuffer[2u * TCPIP_TLS_AES128_BLOCKSIZE];
    uint32  tempBufferLen = 2u * TCPIP_TLS_AES128_BLOCKSIZE;

    /* #30 If shortage of TCPIP_TLS_AES128_BLOCKSIZE, start Aes128 Cbc streaming, and decrypt data in TCP segment 1 into TLS segment 1 */
    plaintextBufOutLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, DataPtr, (uint32)DataLen, tlsSeg1Ptr, &plaintextBufOutLen);

    /* #40 Output any remaining plaintext into temporary buffer, and stop Aes128 Cbc streaming */
    /* Finish Aes128 Cbc streaming into tmp buffer */
    csmRetVal |= TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_FINISH, NULL_PTR, 0u, &tempBuffer[0], &tempBufferLen);

    /* If more plaintext is available, copy into TLS segment 1 */
    if (plaintextBufOutLen < (uint16) DataLen)
    {
      /* Copy the unaligned data from tempBuffer to the first segment of Tls buffer */
      VStdMemCpy(&tlsSeg1Ptr[plaintextBufOutLen], &tempBuffer[0], tempBufferLen);                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      plaintextBufOutLen += tempBufferLen;
    }

    /* Update writeIdx with the plaintext output length */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plaintextBufOutLen);
  }
  /* Tls buffer has at least (N - 1) blocks */
  else if (DataLen <= (tlsSeg1Len + TCPIP_TLS_AES128_BLOCKSIZE))
  {
    uint32           tempBufferLen = 2u * TCPIP_TLS_AES128_BLOCKSIZE;
    uint8            tempBuffer[2u * TCPIP_TLS_AES128_BLOCKSIZE];
    /* TLS wraparound will occur, so store information on TLS segment 2 */
    TCPIP_P2V(uint8) tlsSeg2Ptr;

    /* #50 Start Aes128 Cbc streaming, and consume ciphertext in TCP segment that fits into TLS buffer segment 1 */
    plaintextBufOutLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataPtr[0], tlsSeg1Len, tlsSeg1Ptr, &plaintextBufOutLen);

    /* #60 Decrypt remaining ciphertext in TCP segment 1 into tmp buffer, and stop Aes128 Cbc streaming */
    csmRetVal |= TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataPtr[tlsSeg1Len],
                             (DataLen - tlsSeg1Len), tempBuffer, &tempBufferLen);

    /* Update actual size of TLS segment 1 */
    tlsSeg1Len -= plaintextBufOutLen;

    /* Copy unaligned plaintext from tmp buffer into Tls buffer segment 1 */
    VStdMemCpy(&tlsSeg1Ptr[plaintextBufOutLen], &tempBuffer[0], tlsSeg1Len);                                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* #70 Wraparound TLS buffer and decrypt rest of ciphertext into TLS segment 2 */
    /* Update writeIdx to the start of TLS buffer */
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));

    /* Update the pointer and size of TLS segment 2, which is guaranteed to have sufficient space */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* Copy rest of plaintext from tmp buffer into TLS segment 2 */
    VStdMemCpy(tlsSeg2Ptr, &tempBuffer[tlsSeg1Len], (tempBufferLen - tlsSeg1Len));                                      /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Update writeIdx with size of plaintext copied to TLS segment 2 */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)(tempBufferLen - tlsSeg1Len));
  }
  /* Tls buffer has less than (N - 1) blocks */
  else  /* (DataLen  > (tlsSeg1Len + TCPIP_TLS_AES128_BLOCKSIZE)) */
  {
    /* Temporary buffer */
    uint8            tempBuffer[2u * TCPIP_TLS_AES128_BLOCKSIZE];
    uint32           tempBufferLen = 2u * TCPIP_TLS_AES128_BLOCKSIZE;
    /* TLS wraparound will occur, so store information on TLS segment 2 */
    TCPIP_P2V(uint8) tlsSeg2Ptr;
    uint32           tlsSeg2Len;
    /* Variable to store the ciphertext consumed so far */
    uint32           ciphertextConsumedLen;
    /* Variable to track size of plaintext in TL:S segment 2 */
    uint32           plainTextInSeg2Len;

    /* #80 If shortage of > 2*TCPIP_TLS_AES128_BLOCKSIZE, start Aes128 Cbc streaming, and feed ciphertext that fits in TLS Rx buffer segment 1 */
    plaintextBufOutLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataPtr[0], tlsSeg1Len, tlsSeg1Ptr, &plaintextBufOutLen);

    /* Update consumed ciphertext length */
    ciphertextConsumedLen = tlsSeg1Len;
    /* Update the actual size of TLS segment 1 based on length of plaintext output */
    tlsSeg1Len -= plaintextBufOutLen;

    /* #90 Decrypt one block of ciphertext into tmp buffer and copy into TLS segment 1 */
    csmRetVal |= TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE, &DataPtr[ciphertextConsumedLen], TCPIP_TLS_AES128_BLOCKSIZE, &tempBuffer[0], &tempBufferLen);
    ciphertextConsumedLen += TCPIP_TLS_AES128_BLOCKSIZE;

    /* Copy the plaintext in tmp buffer into space available in TLS segment 1 */
    VStdMemCpy(&tlsSeg1Ptr[plaintextBufOutLen], &tempBuffer[0], tlsSeg1Len);                                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* #100 Wraparound TLS buffer and decrypt remaining ciphertext into TLS segment 2 */
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
    /* Update pointer and size of TLS segment 2 */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
    tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
    /* Update actual plaintext copied into TLS segment 2 */
    plainTextInSeg2Len = (tempBufferLen - tlsSeg1Len);

    /* Copy rest of plaintext in tmp buffer to the start of Tls buffer */
    VStdMemCpy(tlsSeg2Ptr, &tempBuffer[tlsSeg1Len], plainTextInSeg2Len);                                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    /* Update the actual length of TCP segment 2 */
    tlsSeg2Len -= plainTextInSeg2Len;

    /* #110 Decrypt remaining ciphertext, and stop Aes128 Cbc streaming */
    plaintextBufOutLen = tlsSeg2Len;
    csmRetVal |= TCPIP_CSM_Decrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, &DataPtr[ciphertextConsumedLen],
                             (DataLen - (ciphertextConsumedLen)), &tlsSeg2Ptr[plainTextInSeg2Len], &plaintextBufOutLen);
    /* Update actual plaintext copied into TLS segment 2 */
    plainTextInSeg2Len += plaintextBufOutLen;

    /* Update the writeIdx with the plaintext length in TLS segment 2 */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType) plainTextInSeg2Len);
  }

  /* Check CSM operation result */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_RL_RXHSADDATA) == E_OK)
  {
    /* Update the copied length if the decryption was successful */
    *CopiedLenPtr = DataLen;
  }

  return csmRetVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAdHs */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs
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
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                        decryptJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to store TLS Rx buffer segment 1 */
  TCPIP_P2V(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Length of TLS Rx buffer segment 1 */
  uint32           tlsSeg1Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);
  /* Variable to store Csm verification result */
  Crypto_VerifyResultType       verifyResult = CSM_E_VER_NOT_OK;
  /* Variable to store Csm return value */
  Std_ReturnType                csmRetVal;
  /* Variable to store the size of the plaintext output buffer for next Csm call (TLS Rx buffer) */
  uint32  plaintextOutBufLen;

  /* ----- Implementation ----------------------------------------------- */
  /* Scenario 1: No TCP buffer wraparound */
  /* #10 Considering TLS wraparound, perform Aes128 Gcm decryption */
  /* Tls buffer has at least (N+1) blocks */
  if (((uint32)DataLen + TCPIP_TLS_AES128_BLOCKSIZE) <= tlsSeg1Len)                                                     /*lint !e574 */
  {
    /* Scenario 1a: Sufficient space in TLS segment 1 */

    /* #20 If enough space in TLS segment 1, invoke single call Aes128 Gcm Decryption */
    plaintextOutBufLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_SINGLECALL, DataPtr,
                   (uint32)DataLen, AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN, AuthTagPtr,
                   TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, &verifyResult);

    /* Update the WriteIdx with length of plaintext output */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);
  }
  /* Tls buffer has at least N blocks */
  else if ((uint32)DataLen <= tlsSeg1Len)                                                                               /*lint !e574 */
  {
    /* Scenario 1b: TLS segment 1 is short of <=TCPIP_TLS_AES128_BLOCKSIZE */
    /* Temporary buffer to store unaligned plaintext */
    uint8   tempBuffer[TCPIP_TLS_MIN_BUFFER_SIZE];
    uint32  tempBufferLen = TCPIP_TLS_MIN_BUFFER_SIZE;

    /* #30 If short of one block, start Gcm streaming, and feed ciphertext that can fit in TLS segment 1 */
    plaintextOutBufLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, DataPtr, ((uint32)DataLen - TCPIP_TLS_AES128_BLOCKSIZE), AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN,
      AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, &verifyResult);

    /* #40 Decrypt remaining block of ciphertext into temp buffer, and stop Aes128 Gcm streaming */
    csmRetVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      &DataPtr[((uint32)DataLen - TCPIP_TLS_AES128_BLOCKSIZE)], TCPIP_TLS_AES128_BLOCKSIZE, NULL_PTR, 0u, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN,
      &tempBuffer[0], &tempBufferLen, &verifyResult);

    /* Copy plaintext in temp buffer into TLS segment 1 */
    VStdMemCpy(&tlsSeg1Ptr[plaintextOutBufLen], &tempBuffer[0], tempBufferLen);                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Update plaintext output length with length of temp buffer */
    plaintextOutBufLen += tempBufferLen;

    /* Update the WriteIdx with total plaintext output length */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);
  }
  /* Tls buffer < N blocks */
  else  /* (DataLen > tlsSeg1Len) */
  {
    /* Scenario 1c: TLS buffer wraparound */
    /* Variable to store how much ciphertext has been consumed so far */
    uint32           ciphertextConsumed;
    /* Pointer to the TLS segment 2 */
    TCPIP_P2V(uint8) tlsSeg2Ptr;
    /* Variable to store length of TLS segment 2 */
    uint32           tlsSeg2Len;

    /* calling function ensures that there is sufficient TLS buffer space here */
    TCPIP_ASSERT(tlsSeg1Len > TCPIP_TLS_MIN_BUFFER_SIZE);

    /* #50 If TLS wraparound, start Aes128Gcm streaming, and decrypt ciphertext that fits into TLS segment 1 */
    plaintextOutBufLen = tlsSeg1Len;
    csmRetVal = TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_STREAMSTART, &DataPtr[0],
      (tlsSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE), AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN,
      AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, tlsSeg1Ptr, &plaintextOutBufLen, &verifyResult);

    /* Update ciphertext consumed */
    ciphertextConsumed = tlsSeg1Len - TCPIP_TLS_AES128_BLOCKSIZE;
    /* Update actual remaining size of TLS segment 1 */
    tlsSeg1Len -= plaintextOutBufLen;

    /* Update the writeIdx with the total plaintext output length  */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);

    /* [Sliding End Index]: (1) If there is still space remaining in TLS segment 1
     * slide the endIdx to skip these remaining space and wraparound to
     * TLS segment 2
     */
    if (tlsSeg1Len > 0u)
    {
      TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
        TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

      /* Slide the frame start index if necessary */
      if (TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)
        == TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx))
      {
        TcpIp_SetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
          TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx));
      }
    }

    /* Wraparound TLS buffer and decrypt remaining ciphertext into TLS segment 2 */
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx)));
    /* Update pointer and length for TLS segment 2 */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
    tlsSeg2Len = TcpIp_Tls_GetTlsBufferRxAdHsSizeOfNextFreeSegment(TlsConIdx);

    /* Decrypt remaining ciphertext into TLS segment 2, and stop Aes128 Gcm streaming */
    plaintextOutBufLen = tlsSeg2Len;
    csmRetVal |= TCPIP_CSM_AEADDecrypt(decryptJobId, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
      &DataPtr[ciphertextConsumed], ((uint32)DataLen - ciphertextConsumed), NULL_PTR, 0u, AuthTagPtr, TCPIP_TLS_AES128_GCM_AUTHTAG_LEN,
      &tlsSeg2Ptr[0], &plaintextOutBufLen, &verifyResult);

    /* Update the writeIdx with the total plaintext output length  */
    TcpIp_AddTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
      (TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType)plaintextOutBufLen);
  }

  /* Check if authentication was successful and set the retVal */
  if (verifyResult != CSM_E_VER_OK)
  {
    csmRetVal = E_NOT_OK;
  }

  /* #60 Check CSM operation result */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0u, 0u, TCPIP_TLS_FCTID_CORE_RL_RXHSADDATA) == E_OK)
  {
    /* Update copied length with total plaintext output (we know its always data length) */
    *CopiedLenPtr = DataLen;
  }

  return csmRetVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128GcmDataToRxBufAdHs */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType  activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32                               deJobId =
                         TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Total available space in the TLS Rx Al buffer */
  uint32                        availableSpace = TcpIp_GetTlsBufferRxAlLengthOfTlsBufferMgmt(tlsBufferMgmtIdx);
  TCPIP_P2V(uint8)              decryptDestPtr =
                           TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Decrypt the data in the provided buffer into the TLS Rx Alert buffer using Aes128Cbc */
  csmRetVal = TCPIP_CSM_Decrypt(deJobId, CRYPTO_OPERATIONMODE_SINGLECALL, DataPtr, (uint32)DataLen, decryptDestPtr, &availableSpace);

  /* Update the WriteIdx and the copied data length */
  TcpIp_AddTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, DataLen);

  /* Update the copied length */
  *CopiedLenPtr = DataLen;

  (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_DECRYPTALBUFAES128CBC);

  return csmRetVal;
} /* TcpIp_TlsCoreRl_DecryptAes128CbcDataToRxBufAl() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8)            DataPtr,
  uint16                      DataLen,
  TCPIP_P2C(uint8)            AuthDataPtr,
  TCPIP_P2C(uint8)            AuthTagPtr,
  TCPIP_P2V(uint16)           CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                csmRetVal;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32                        availableSpace = ((uint32)TcpIp_GetTlsBufferRxAlEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx)
                                                  - TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  Crypto_VerifyResultType       verifyResult = CSM_E_VER_NOT_OK;
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType  activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
  uint32 deJobId = TcpIp_CsmJobId[TcpIp_GetCsmJobIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  TCPIP_P2V(uint8) decryptDestPtr = TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(
    tlsBufferMgmtIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If sufficient space available, decrypt data in provided buffer */
  /* Invoke the AEAD Decrypt function */
  csmRetVal = TCPIP_CSM_AEADDecrypt(deJobId, CRYPTO_OPERATIONMODE_SINGLECALL, &DataPtr[0],
    (uint32)DataLen, AuthDataPtr, TCPIP_TLS_AES128_GCM_AADATA_LEN, AuthTagPtr,
    TCPIP_TLS_AES128_GCM_AUTHTAG_LEN, decryptDestPtr, &availableSpace, &verifyResult);

  /* Length of plaintext will be always equal to ciphertext. So update the WriteIdx to ciphertext length */
  TcpIp_AddTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, DataLen);

  *CopiedLenPtr = DataLen;

  (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0u, 0u, TCPIP_TLS_FCTID_CORE_CRYPTO_DECRYPTALBUFAES128GCM);

  return csmRetVal;
} /* TcpIp_TlsCoreRl_DecryptAEADAes128DataToRxBufAl() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_SetIvForDecryptCall
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_SetIvForDecryptCall(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) DataPtr)
{
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);
   uint32 deKeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdCipherDecryptIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
   Std_ReturnType retVal = E_NOT_OK;

   /* #10 Write the decrypt key element with the provided key data and set it valid. */
   if (TCPIP_CSM_KeyElementSet(deKeyId, CRYPTO_KE_CIPHER_IV, DataPtr, TCPIP_TLS_AES128_IV_LEN) == E_OK)
   {
     if (TCPIP_CSM_KeySetValid(deKeyId) == E_OK)
     {
       retVal = E_OK;
     }
   }


   return retVal;
} /* TcpIp_TlsCoreRl_SetIvForDecryptCall() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(uint16) CopiedLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal                          = E_NOT_OK;
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on content type, remove padding bytes in Tls Rx buffer. */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType writeIdxWithPadding = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                                tlsBufferMgmtIdx);
    /* Variable to store the value of the padding bytes in the frame. */
    uint8 paddingValue = TcpIp_GetTlsBufferRx(writeIdxWithPadding - 1u);

    /* Check if the amount of padding bytes is not bigger than the whole received message. */
    retVal = TcpIp_TlsCoreRl_CheckPaddingLen(TlsConIdx, CopiedLenPtr, paddingValue);

    if (retVal == E_OK)
    {
      /* Verify and remove the padding bytes. */
      retVal = TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf(TlsConIdx, CopiedLenPtr, paddingValue);
    }
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
    TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType writeIdxWithPadding = TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(
                                                                                tlsBufferMgmtIdx);
    /* Variable to store the value of the padding bytes in the frame */
    uint8 paddingValue = TcpIp_GetTlsBufferRx(writeIdxWithPadding - 1u);

    /* Check if the amount of padding bytes is not bigger than the whole received message. */
    retVal = TcpIp_TlsCoreRl_CheckPaddingLen(TlsConIdx, CopiedLenPtr, paddingValue);

    if (retVal == E_OK)
    {
      /* Verify and remove the padding bytes. */
      retVal = TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf(TlsConIdx, CopiedLenPtr, paddingValue);
    }
  }
  else
  {
    /* (ContentType == TCPIP_TLS_CT_CCS) */
    /* nothing to do */
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_RemoveAndCheckPaddingFromRxBuf() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_CheckPaddingLen
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CheckPaddingLen(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  /* Count of padding bytes */
  uint8 numPaddingBytes = (PaddingValue + 1u);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the amount of padding bytes is not bigger than the whole received message. */
  if (numPaddingBytes > *CopiedLenPtr)
  {
    /* Set the copiedLen to 0 and set an alert because the value of the padding bytes is invalid. */
    *CopiedLenPtr = 0u;
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_CheckPaddingLen() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
  /* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 numPaddingBytes                                                      = (PaddingValue + 1u);
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx                             = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType writeIdxWithPadding    = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
    tlsBufferMgmtIdx);
  /* Minimum index position that causes TLS buffer wraparound of padding */
  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType writeIdxWithPaddingMin = (TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(
    tlsBufferMgmtIdx) + numPaddingBytes);
  /* Value to store the write index without padding */
  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType writeIdxWithoutPadding;

  /* ----- Implementation ----------------------------------------------- */
  /* Remove the padding bytes from the Rx buffer, considering TlS wraparound */
  /* #10 Check if the padding bytes are wrapped around or linear. */
  if (writeIdxWithPadding >= writeIdxWithPaddingMin)
  {
    /* Padding lies linear in the TLS buffer. */
    /* Recalculate the writeIdx with size of padding bytes */
    writeIdxWithoutPadding = (TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) - numPaddingBytes);

    /* Check if all padding bytes have the correct (same) value. */
    retVal = TcpIp_TlsCoreRl_VerifyPadding(TlsConIdx, TcpIp_GetAddrTlsBufferRx(writeIdxWithoutPadding),
      (uint8)(writeIdxWithPadding - writeIdxWithoutPadding), PaddingValue);

    /* Clear the padding bytes from the TLS Rx buffer */
    TcpIp_TlsCoreBuffer_ClearRxBuffer(writeIdxWithoutPadding, writeIdxWithPadding);
  }
  else /* (writeIdxWithPadding < writeIdxWithPaddingMin) */
  {
    /* Start of the Rx buffer */
    TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxBufferStartIdx
      = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
    /* Current end of the Rx buffer */
    TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxBufferCurrentEndIdx
      = TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
    /* Variable to count padding bytes after wraparound */
    uint16 paddingBytesAfterWraparound = (uint16)(writeIdxWithPadding - rxBufferStartIdx);
    /* Variable to count padding bytes before wraparound */
    uint16 paddingBytesBeforeWraparound = numPaddingBytes - paddingBytesAfterWraparound;

    /* Recalculate the writeIdx without padding */
    writeIdxWithoutPadding = rxBufferCurrentEndIdx - paddingBytesBeforeWraparound;

    /* Check if all padding bytes have the correct (same) value. */
    /* Check the first part. */
    retVal = TcpIp_TlsCoreRl_VerifyPadding(TlsConIdx, TcpIp_GetAddrTlsBufferRx(writeIdxWithoutPadding),
      (uint8)(rxBufferCurrentEndIdx - writeIdxWithoutPadding), PaddingValue);
    /* Check the second part. ORing the result is ok because it can only be E_OK or E_NOT_OK. */
    retVal |= TcpIp_TlsCoreRl_VerifyPadding(TlsConIdx, TcpIp_GetAddrTlsBufferRx(rxBufferStartIdx),
      (uint8)(writeIdxWithPadding - rxBufferStartIdx), PaddingValue);

    /* Clear padding bytes before wraparound */
    TcpIp_TlsCoreBuffer_ClearRxBuffer(writeIdxWithoutPadding, rxBufferCurrentEndIdx);

    /* Clear remaining padding bytes after wraparound */
    TcpIp_TlsCoreBuffer_ClearRxBuffer(rxBufferStartIdx, writeIdxWithPadding);
  }

  /* Update the recalculated writeIdx */
  TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, writeIdxWithoutPadding);

  /* Update the copied length */
  *CopiedLenPtr -= numPaddingBytes;

  return retVal;
} /* TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAdHsBuf() */

/**********************************************************************************************************************
 *   TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE)  TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint16) CopiedLenPtr,
  uint8 PaddingValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 numPaddingBytes                                                 = (PaddingValue + 1u);
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx                        = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsBufferRxAlWriteIdxOfTlsBufferMgmtDynType writeIdxWithPadding = TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(
    tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Recalculate the writeIdx without padding */
  TcpIp_TlsBufferRxAlWriteIdxOfTlsBufferMgmtDynType writeIdxWithoutPadding =
    (TcpIp_GetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) - numPaddingBytes);

  /* #10 Verify and remove the padding bytes. */
  /* Check if all padding bytes have the correct (same) value. */
  retVal = TcpIp_TlsCoreRl_VerifyPadding(TlsConIdx, TcpIp_GetAddrTlsBufferRx(writeIdxWithoutPadding),
    (uint8)(writeIdxWithPadding - writeIdxWithoutPadding), PaddingValue);

  /* Clear the padding bytes in TLS buffer */
  TcpIp_TlsCoreBuffer_ClearRxBuffer(writeIdxWithoutPadding, writeIdxWithPadding);
  /* Update the recalculated writeIdx */
  TcpIp_SetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, writeIdxWithoutPadding);
  /* Update the copied length */
  *CopiedLenPtr -= numPaddingBytes;

  return retVal;
} /* TcpIp_TlsCoreRl_RemoveAndVerifyPaddingFromAlBuf() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyPadding
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyPadding(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(uint8) StartPtr,
  uint8 PaddingLen,
  uint8 ReferenceValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least checkIdx;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if all padding bytes have the correct (same) value. */
  for (checkIdx = 0; checkIdx < PaddingLen; checkIdx++)
  {
    if (StartPtr[checkIdx] != ReferenceValue)
    {
      /* The padding is invalid */
      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC);
      retVal = E_NOT_OK;
      break;  /* leave the for-loop */
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  uint8  macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  uint16 rlFrameLen = TcpIp_GetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Complete received Length of this frame */

  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* Check the input data for the HMAC verification */
  if (rlFrameLen >= macLen)
  {
    /* #10 Depending on content type, verify Mac */
    if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
    {
      /* HMAC and data is in the AdHs Rx buffer */
      retVal = TcpIp_TlsCoreRl_VerifyHmacAdHs(TlsConIdx, ContentType, RlAlertDescriptionPtr);
    }
    else if (ContentType == TCPIP_TLS_CT_AL)
    {
      /* HMAC and data is in the Al Rx buffer */
      retVal = TcpIp_TlsCoreRl_VerifyHmacAl(TlsConIdx, RlAlertDescriptionPtr);
    }
    else if (ContentType == TCPIP_TLS_CT_CCS)
    {
      /* CCs message does not have any HMAC - just return at this point */
    }
    else
    {
      /* else - Should never happen. ContentType Check is done by Record Layer Rx functions */
    }
  }
  else
  {
    /* invalid length detected - set alert description */
    if (ContentType == TCPIP_TLS_CT_CCS)
    {
      /* In this case a duplicated CCs message was received because an encrypted CCs message can only be received */
      /* after an earlier CCs message that indicated the switch to encrypted communication. */
      /* Furthermore the Record Layer frame length of a CCs message (1 byte) is always smaller than a HMAC length. */
      /* Therefore set an unexpected message alert description. */
      *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_UNEXP_MSG;
    }
    else
    {
      /* In all other cases a decode error alert description is fitting. */
      *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
    }
  }

  return retVal;
} /* TcpIp_TlsCoreRl_VerifyHmacContentTypeDependend() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyHmacAdHs()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn( TlsConIdx);

  uint32 csmJobIdVerify = TcpIp_CsmJobId[TcpIp_GetCsmJobIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];

  TcpIp_TlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDynType rlFrameStartIdx =
    TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Index where this current frame is located */

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType rxBufferEndIdx =
    TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* End of the complete RX Buffer */

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxBufferStartIdx =
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx); /* Start of the Rx Buffer */

  uint8               macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  uint32              macLenBit = ((uint32)macLen * 8u);
  TCPIP_P2C(uint8)    macPtr; /* Location of the MAC inside the RxBuffer */
  uint16              rlFrameLen = TcpIp_GetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Complete received Length of this frame */
  uint16              dataLen = (rlFrameLen - macLen); /* Length of the content type data (either HS, or AD) */
  TCPIP_P2C(uint8)    dataPtr = TcpIp_GetAddrTlsBufferRx(rlFrameStartIdx);  /* location of the data inside the Rx Buffer */
  /* local array that contains the sequence counter and the record layer header */
  uint8               tmpSeqCounterAndRlHdr[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN];
  TCPIP_P2V(uint8)    seqCounterPtr = &tmpSeqCounterAndRlHdr[0];
  TCPIP_P2V(uint8)    rlHdrPtr      = &tmpSeqCounterAndRlHdr[TCPIP_TLS_RL_SEQUENCE_NUM_LEN];

  uint8 tmpMacBuffer[TCPIP_TLS_MAC_LEN_MAX]; /* Temporary buffer to linearize the MAC (CASE 2) */

  Crypto_VerifyResultType csmResult = CSM_E_VER_NOT_OK; /* Information about the verification of the MAC */
  Std_ReturnType          csmRetVal;
  Std_ReturnType retVal = E_NOT_OK;


  /* ----- Implementation ----------------------------------------------- */
  /* ----- GENERIC PART ----- */
  /* It does not matter in which constellation the data are in the rx buffer, these two CSM update are necessary for both */

  /* #10 Start the HMAC generation and feed the sequence number and the record layer header as first input. */
  /* Copy the rx sequence number to a local byte array. */
  IpBase_PutUint64(seqCounterPtr, 0, TcpIp_GetRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx));


  /* Build the RL Header into the local byte array. */
  rlHdrPtr[TCPIP_TLS_RLCT_OFFSET]        = ContentType;
  rlHdrPtr[TCPIP_TLS_RLVERSMAJOR_OFFSET] = TCPIP_TLS_RL_VERSMAJOR;
  rlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] = TCPIP_TLS_RL_VERSMINOR;
  IpBase_PutUint16(&rlHdrPtr[TCPIP_TLS_RLLENHIGH_OFFSET], 0, dataLen);

  /* Start the MAC generation */
  csmRetVal = TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_STREAMSTART, &tmpSeqCounterAndRlHdr[0],
                            (TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN), NULL_PTR, 0, NULL_PTR);

  /* #20 Depending on TLS buffer wraparound, decrypt MAC and stop MAC streaming */
  if ((rlFrameStartIdx + rlFrameLen) < rxBufferEndIdx)
  {
    /* CASE 1: No TLS buffer wraparound for DATA and MAC

                 RL-START-IDX                      END-IDX
                     V                               V
         +-------------------------------------------+
         |           +------------+                  |
         |           |  DATA  |MAC|                  |
         |           +------------+                  |
         +-------------------------------------------+
                     \---COPIED---/
    */
    /* Set the MAC source pointer */
    macPtr = TcpIp_GetAddrTlsBufferRx(rlFrameStartIdx + dataLen);

    /* Update and finish the MAC generation and validation and feed the data and the mac */
    csmRetVal |= TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, dataPtr,
                               dataLen, macPtr, macLenBit, &csmResult);
  }
  else if ((rlFrameStartIdx + dataLen) < rxBufferEndIdx)
  {
    /* CASE 2: TLS buffer wraparound for only for MAC
                                               MAC1-IDX
                                                ^
                                                |
         MAC2-IDX                  RL-START-IDX |  END-IDX
         V                             V        V    V
         +-------------------------------------------+
         |~---+                        +------------~|
         |MAC2|                        |  DATA  |MAC1|
         |~---+                        +------------~|
         +-------------------------------------------+
         -----/                        \----COPIED----
    */
    /* ----- Local Variables ---------------------------------------------- */
    TcpIp_TlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDynType macPart1StartIdx = (rlFrameStartIdx + dataLen);
    uint16 macPart1Len = (uint16)(rxBufferEndIdx - macPart1StartIdx);
    uint16 macPart2Len = ((uint16)macLen - macPart1Len);

    /* ----- Implementation ----------------------------------------------- */
    /* Linearize the mac */
    VStdMemCpy(&tmpMacBuffer[0], TcpIp_GetAddrTlsBufferRx(macPart1StartIdx), macPart1Len);                              /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(&tmpMacBuffer[macPart1Len], TcpIp_GetAddrTlsBufferRx(rxBufferStartIdx), macPart2Len);                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* Set the MAC source pointer */
    macPtr = &tmpMacBuffer[0];

    /* Update and finish the MAC generation and validation and feed the data and the mac */
    csmRetVal |= TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, dataPtr,
                               dataLen, macPtr, macLenBit, &csmResult);


  }
  else if ((rlFrameStartIdx + dataLen ) == rxBufferEndIdx)
  {
    /* CASE 3: No TLS buffer wraparound for DATA and MAC, but MAC is after TLS wraparound
         MAC-IDX                   RL-START-IDX    END-IDX
         V                             V             V
         +-------------------------------------------+
         |~---+                        +------------~|
         |MAC |                        |  DATA       |
         |~---+                        +------------~|
         +-------------------------------------------+
         -----/                        \----COPIED----
    */
    /* Set the MAC source pointer */
    macPtr = TcpIp_GetAddrTlsBufferRx(rxBufferStartIdx);

    /* Update and finish the MAC generation and validation and feed the data and the mac */
    csmRetVal |= TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, dataPtr,
                               dataLen, macPtr, macLenBit, &csmResult);
  }
  else
  {
    /* CASE 4: TLS wraparound for DATA and MAC is after wraparound
                                     DATA1-IDX
                                        V
      DATA2-IDX   MAC-IDX           RL-START-IDX    END-IDX
          V       V                     V             V
          +-------------------------------------------+
          |~----------+                 +------------~|
          | DATA2 |MAC|                 |  DATA1      |
          |~----------+                 +------------~|
          +-------------------------------------------+
          ------------/                 \----COPIED----
    */
    /* ----- Local Variables ---------------------------------------------- */
    TCPIP_P2C(uint8) dataPart1Ptr = dataPtr;
    uint32           dataPart1Len = ((uint32)rxBufferEndIdx - rlFrameStartIdx);
    TCPIP_P2C(uint8) dataPart2Ptr = TcpIp_GetAddrTlsBufferRx(rxBufferStartIdx);
    uint32           dataPart2Len = (dataLen - dataPart1Len);

    /* ----- Implementation ----------------------------------------------- */
    /* Set the MAC source pointer */
    macPtr = TcpIp_GetAddrTlsBufferRx(rxBufferStartIdx + (TcpIp_TlsBufferRxIterType)dataPart2Len);

    /* Update the MAC generation and feed the first data part */
    csmRetVal |= TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_UPDATE, dataPart1Ptr, dataPart1Len, NULL_PTR, 0,
                               NULL_PTR);

    /* Update and finish the MAC generation and validation and feed the second data part and the mac */
    csmRetVal |= TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH, dataPart2Ptr,
                               dataPart2Len, macPtr, macLenBit, &csmResult);
  }

  /* Check result of the CSM operation and report user error if necessary */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACADHS) == E_OK)
  {
    if (csmResult == CSM_E_VER_OK)
    {
      /* HMAC verification OK - return E_OK and accept the frame */
      retVal = E_OK;
    }
    else
    {
      /* HMAC verification failed - report error to user and set alert description */
      TcpIp_TlsUserErrorType userError;

      userError.FunctionId  = TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACADHS;
      userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_MACVERIFY_FAILED;
      userError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(userError);

      *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC;
    }
  }
  else
  {
    /* CSM Operation failed - report error to user and set alert description */
    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_INT_ERROR;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_VerifyHmacAdHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_VerifyHmacAl()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_VerifyHmacAl(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsAlertDescriptionType) RlAlertDescriptionPtr)
{
 /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx         = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  uint32 csmJobIdVerify = TcpIp_CsmJobId[TcpIp_GetCsmJobIdHmacVerifyIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];

  uint8  macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  uint32 macLenBit = ((uint32) macLen * 8u);
  TCPIP_P2C(uint8) macPtr; /* Location of the MAC inside the RxBuffer */
  uint16 rlFrameLen = TcpIp_GetRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Complete received Length of this frame */
  uint16 dataLen = (rlFrameLen - macLen); /* Length of the content type data (AL) */

  TcpIp_TlsBufferRxAlStartIdxOfTlsBufferMgmtType  rlFrameStartIdx
    = TcpIp_GetTlsBufferRxRlFrameStartIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  TCPIP_P2C(uint8) dataPtr = TcpIp_GetAddrTlsBufferRx(rlFrameStartIdx);  /* location of the data inside the Rx Buffer */
  /* local array that contains the sequence counter, the record layer header and the alert data */
  uint8            tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN + TCPIP_TLS_CT_ALERT_LEN];
  const uint32     tmpLocalArrayLen = TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN + TCPIP_TLS_CT_ALERT_LEN;
  TCPIP_P2C(uint8) tmpLocalArrayPtr = &tmpLocalArray[0];  /* pointer to complete array */
  TCPIP_P2V(uint8) seqCounterPtr    = &tmpLocalArray[0];  /* sequence counter */
  TCPIP_P2V(uint8) rlHdrPtr         = &tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN];  /* record layer header */
  TCPIP_P2V(uint8) alertDataPtr     = &tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN];  /* alert data */

  Crypto_VerifyResultType csmResult = CSM_E_VER_NOT_OK; /* Information about the verification of the MAC */
  Std_ReturnType          csmRetVal;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if (dataLen == TCPIP_TLS_CT_ALERT_LEN)
  {
    /* #10 Copy the rx sequence number into tmpLocalArray. */
    IpBase_PutUint64(seqCounterPtr, 0, TcpIp_GetRlRxSequenceCounterOfTlsConnectionDyn(TlsConIdx));

    /* #20 Build the record layer header into tmpLocalArray. */
    rlHdrPtr[TCPIP_TLS_RLCT_OFFSET]        = TCPIP_TLS_CT_AL;
    rlHdrPtr[TCPIP_TLS_RLVERSMAJOR_OFFSET] = TCPIP_TLS_RL_VERSMAJOR;
    rlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] = TCPIP_TLS_RL_VERSMINOR;
    IpBase_PutUint16(&rlHdrPtr[TCPIP_TLS_RLLENHIGH_OFFSET], 0, dataLen);

    /* #30 Copy the alert data into tmpLocalArray. */
    alertDataPtr[0] = dataPtr[0];
    alertDataPtr[1] = dataPtr[1];

    /* #40 Execute the MAC generation and validation and compare with the received MAC. */
    /* Set the MAC source pointer */
    macPtr = TcpIp_GetAddrTlsBufferRx(rlFrameStartIdx + dataLen);

    /* Execute verification */
    csmRetVal = TCPIP_CSM_MacVerify(csmJobIdVerify, CRYPTO_OPERATIONMODE_SINGLECALL, tmpLocalArrayPtr,
      tmpLocalArrayLen, macPtr, macLenBit, &csmResult);

    /* Check result of the CSM operation and report user error if necessary */
    if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACAL) == E_OK)
    {
      if (csmResult == CSM_E_VER_OK)
      {
        /* Verification passed - return E_OK */
        retVal = E_OK;
      }
      else
      {
        /* If not so, report the user error */
        TcpIp_TlsUserErrorType userError;

        userError.FunctionId = TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACAL;
        userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_MACVERIFY_FAILED;
        userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

        TcpIp_TlsCoreError_ReportUserError(userError);

        *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC;
      }
    }
    else
    {
      /* CSM Operation failed - report error to user and set alert description */
      *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_INT_ERROR;
    }
  }
  else
  {
    /* invalid alert message length */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACAL;
    userError.UserErrorId = TCPIP_TLS_ERRORID_ALERT_LENGTH_INVALID;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);

    *RlAlertDescriptionPtr = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_VerifyHmacAl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_FinalizeRxBuffer()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint8, AUTOMATIC) ContentType)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the content type, finalize the Tls buffer */
  if ((ContentType == TCPIP_TLS_CT_HS) || (ContentType == TCPIP_TLS_CT_AD))
  {
    TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer(TlsConIdx);
  }
  else if (ContentType == TCPIP_TLS_CT_AL)
  {
   TcpIp_TlsCoreRl_FinalizeRxAlBuffer(TlsConIdx);
  }
  else if (ContentType == TCPIP_TLS_CT_CCS)
  {
    /* CCS Message does not contain any HMAC or removable overhead. Nothing to do - left blank intentionally */
  }
  else
  {
    /* Should never happen. ContentType Check is done by Record Layer Rx functions */
  }

} /* TcpIp_TlsCoreRl_FinalizeRxBuffer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType rxBufferEndIdx =
      TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* End of the complete RX Buffer */

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxBufferStartIdx =
    TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx); /* Start of the Rx Buffer */

  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxBufferWriteIdx =
    TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx); /* Current write index */

  uint8 macLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Considering Tls buffer wraparound, clear the MAC from the Rx buffer */
  if ((rxBufferStartIdx + macLen) <= rxBufferWriteIdx)
  {
    /* MAC and data are linearized, just remove the MAC from the RX Buffer */
    TcpIp_TlsCoreBuffer_ClearRxBuffer((rxBufferWriteIdx - (uint16)macLen), rxBufferWriteIdx);
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (rxBufferWriteIdx - macLen));
  }
  else
  {
    /* MAC wrap around */
    uint8 macLenPart2 = (uint8)(rxBufferWriteIdx - rxBufferStartIdx); /* Part at the beginning of the buffer */
    uint8 macLenPart1 = (macLen - macLenPart2); /* Part in the End of the buffer */

    /* Adjust the write index */
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (rxBufferEndIdx - macLenPart1));

    /* Remove the MAC from the RX Buffer */
    /* The local variables still contain the 'old' indices, so they can be used to clear the buffer. */
    /* clear part 1 (at the end of the rx buffer) */
    TcpIp_TlsCoreBuffer_ClearRxBuffer((rxBufferEndIdx - macLenPart1), rxBufferEndIdx);
    /* clear part 2 (at the beginning of the rx buffer) */
    TcpIp_TlsCoreBuffer_ClearRxBuffer(rxBufferStartIdx, rxBufferWriteIdx);
  }

  /* Decrement the size of MAC from the total copied length of current Rl frame */
  TcpIp_SubRlRxCopiedLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, macLen);
} /* TcpIp_TlsCoreRl_FinalizeRxAdHsBuffer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_FinalizeRxAlBuffer()
**********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_FinalizeRxAlBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType rxAlBufferStartIdx =
    TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx); /* Start of the Rx Buffer */

  /* #10 Update the Write Idx of the alert buffer */
  TcpIp_SetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (rxAlBufferStartIdx + TCPIP_TLS_CT_ALERT_LEN));

} /* TcpIp_TlsCoreRl_FinalizeRxAlBuffer() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType  tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint8                          contentType = TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on content type, calculate the Mac */
  if ((contentType == TCPIP_TLS_CT_HS) || (contentType == TCPIP_TLS_CT_AD))
  {
    /* HMAC and data is in the AdHs */
    retVal = TcpIp_TlsCoreRl_CalcHmacShaAdHs(TlsConIdx);
  }
  else if (contentType == TCPIP_TLS_CT_AL)
  {
    /* HMAC and data is in the Al */
    retVal = TcpIp_TlsCoreRl_CalcHmacShaAl(TlsConIdx);
  }
  else
  {
    /* Should never happen. ContentType Check is done by Record Layer Rx functions */
  }

  return retVal;
} /* TcpIp_TlsCoreRl_CalcHmacShaContentTypeDependend() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcHmacShaAdHs
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaAdHs(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(
                                                               TlsConIdx);
  /* Pointer to store Mac in temporary buffer */
  TCPIP_P2V(uint8)              macOutPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(
                                                                           TlsConIdx));
  /* Length of the buffer to store Mac output */
  uint32                        macOutLen = (uint32)TcpIp_GetTlsTemporaryHmacBufferEndIdxOfTlsConnection(TlsConIdx)
                                         - TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx);
  /* Length of plaintext for the current RL frame */
  uint32                        plaintextLen = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* Expected length of Mac */
  uint32                        expectedMacLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);
  /* Start Idx of Rl frame in TLS Tx buffer which should be transmitted */
  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType txRlFrameStartIdx =
    TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  /* End of the complete TLS Tx Buffer */
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType txBufferEndIdx =
    TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);
  /* Start Idx of the TLS Tx Buffer */
  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType txBufferStartIdx =
    TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(tlsBufferMgmtIdx);

  /* local array that contains the sequence counter and the record layer header */
  uint8               tmpSeqCounterAndRlHdr[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN];
  TCPIP_P2V(uint8)    seqCounterPtr = &tmpSeqCounterAndRlHdr[0];  /* sequence counter */
  TCPIP_P2V(uint8)    rlHdrPtr      = &tmpSeqCounterAndRlHdr[TCPIP_TLS_RL_SEQUENCE_NUM_LEN];  /* record layer header */
  uint32           csmJobIdMacGenerate = TcpIp_CsmJobId[TcpIp_GetCsmJobIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];
  /* Pointer to plaintext in TLS segment 1 */
  TCPIP_P2C(uint8) tlsSeg1Ptr = TcpIp_GetAddrTlsBufferTx(txRlFrameStartIdx);
  /* Length of plaintext in TLS segment 1 */
  uint32           tlsSeg1Len = plaintextLen;
  /* Function return value */
  Std_ReturnType   retVal;
  /* Csm call return value */
  Std_ReturnType   csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start the HMAC generation and feed the sequence number and the record layer header as first input. */
  /* Copy the rx sequence number to a local byte array. */
  IpBase_PutUint64(seqCounterPtr, 0, TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx));

  /* Build the RL Header into the local byte array. */
  rlHdrPtr[TCPIP_TLS_RLCT_OFFSET] = TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  rlHdrPtr[TCPIP_TLS_RLVERSMAJOR_OFFSET] = TCPIP_TLS_RL_VERSMAJOR;
  rlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] = TCPIP_TLS_RL_VERSMINOR;
  IpBase_PutUint16(&rlHdrPtr[TCPIP_TLS_RLLENHIGH_OFFSET], 0, (uint16)plaintextLen);

  /* Start the MAC generation */
  csmRetVal = TCPIP_CSM_MacGenerate(csmJobIdMacGenerate, CRYPTO_OPERATIONMODE_STREAMSTART, &tmpSeqCounterAndRlHdr[0],
                              (TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN), NULL_PTR, NULL_PTR);

  /* #20 Considering Tls wraparound, feed the MAC and stop MAC generation */
  if ((txRlFrameStartIdx + plaintextLen) <= txBufferEndIdx)
  {
    /* Generate MAC for plaintext in TLS segment 1 */
    csmRetVal |= TCPIP_CSM_MacGenerate(csmJobIdMacGenerate, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
                                 tlsSeg1Ptr, tlsSeg1Len, macOutPtr, &macOutLen);
  }
  else
  {
    /* Part of plaintext is present in TLS segment 2 */
    /* Pointer to plaintext in TLS segment 2 */
    TCPIP_P2C(uint8) tlsSeg2Ptr;
    /* Length of plaintext in TLS segment 2 */
    uint32 tlsSeg2Len;

    /* Calculate length of plaintext in TLS segment 1 */
    tlsSeg1Len = ((uint32)txBufferEndIdx - txRlFrameStartIdx);
    /* Calculate length of plaintext in TLS segment 2 */
    tlsSeg2Ptr = TcpIp_GetAddrTlsBufferTx(txBufferStartIdx);
    tlsSeg2Len = (plaintextLen - tlsSeg1Len);

    /* Generate Mac for plaintext in TLS segment 1  */
    csmRetVal |= TCPIP_CSM_MacGenerate(csmJobIdMacGenerate, CRYPTO_OPERATIONMODE_UPDATE, tlsSeg1Ptr, tlsSeg1Len,
                                 NULL_PTR, NULL_PTR);
    /* Update and Finish the Mac generation for plaintext in TLS segment 2 */
    csmRetVal |= TCPIP_CSM_MacGenerate(csmJobIdMacGenerate, CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH,
                                 tlsSeg2Ptr, tlsSeg2Len, macOutPtr, &macOutLen);
  }

  /* Check if the result of the CSM operation and the expected length match */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, macOutLen, expectedMacLen,
                                              TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_HMAC);

  return retVal;
} /* TcpIp_TlsCoreRl_CalcHmacShaAdHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_CalcHmacShaAl
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_CalcHmacShaAl(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType  tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TCPIP_P2V(uint8) macDestPtr = TcpIp_GetAddrTlsTemporaryHmacBuffer(TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx));
  uint32 macLen = (uint32)TcpIp_GetTlsTemporaryHmacBufferEndIdxOfTlsConnection(TlsConIdx)
    - TcpIp_GetTlsTemporaryHmacBufferStartIdxOfTlsConnection(TlsConIdx);

  uint8 contentType     = TcpIp_GetRlTxContentTypeOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32 txLen          = TcpIp_GetRlTxContentTypeLenOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
  uint32 expectedMacLen = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  TcpIp_TlsBufferTxRlSendIdxOfTlsBufferMgmtDynType txRlFrameStartIdx
    = TcpIp_GetTlsBufferTxRlSendIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

  /* local array that contains the sequence counter, the record layer header and the alert data */
  uint8            tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN + TCPIP_TLS_CT_ALERT_LEN];
  const uint32     tmpLocalArrayLen = TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN + TCPIP_TLS_CT_ALERT_LEN;
  TCPIP_P2C(uint8) tmpLocalArrayPtr = &tmpLocalArray[0];  /* pointer to complete array */
  TCPIP_P2V(uint8) seqCounterPtr    = &tmpLocalArray[0];  /* sequence counter */
  TCPIP_P2V(uint8) rlHdrPtr         = &tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN];  /* record layer header */
  TCPIP_P2V(uint8) alertDataPtr     = &tmpLocalArray[TCPIP_TLS_RL_SEQUENCE_NUM_LEN + TCPIP_TLS_RLHDRLEN];  /* alert data */

  uint32                         csmJobIdMacGenerate
    = TcpIp_CsmJobId[TcpIp_GetCsmJobIdHmacGenerateIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx)];

  TCPIP_P2C(uint8)               dataPart1Ptr = TcpIp_GetAddrTlsBufferTx(txRlFrameStartIdx);
  Std_ReturnType                 retVal;
  Std_ReturnType                 csmRetVal;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(txLen == TCPIP_TLS_CT_ALERT_LEN);

  /* #10 Copy sequence number, RL header and alert data to prepare the MAC generation. */
  /* Copy the tx sequence number into tmpLocalArray. */
  IpBase_PutUint64(seqCounterPtr, 0, TcpIp_GetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx));

  /* Build the record layer header into tmpLocalArray. */
  rlHdrPtr[TCPIP_TLS_RLCT_OFFSET] = contentType;
  rlHdrPtr[TCPIP_TLS_RLVERSMAJOR_OFFSET] = TCPIP_TLS_RL_VERSMAJOR;
  rlHdrPtr[TCPIP_TLS_RLVERSMINOR_OFFSET] = TCPIP_TLS_RL_VERSMINOR;
  IpBase_PutUint16(&rlHdrPtr[TCPIP_TLS_RLLENHIGH_OFFSET], 0, (uint16)txLen);

  /* Copy the alert data into tmpLocalArray. */
  alertDataPtr[0] = dataPart1Ptr[0];
  alertDataPtr[1] = dataPart1Ptr[1];

  /* #20 Use all merged data for the MAC generation. */
  csmRetVal = TCPIP_CSM_MacGenerate(csmJobIdMacGenerate, CRYPTO_OPERATIONMODE_SINGLECALL,
    tmpLocalArrayPtr, tmpLocalArrayLen, macDestPtr, &macLen);

  /* Check result of CSM operation, and report user error if necessary */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, macLen, expectedMacLen, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_HMAC)
    == E_OK)
  {
    retVal = E_OK;
  }
  else
  {
    /* if not successful, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_HMAC;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_CALCHMAC_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreRl_CalcHmacShaAl() */

/**********************************************************************************************************************
 *  TcpIp_CoreRl_HandleErrorWhileTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRl_HandleErrorWhileTransmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsUserErrorIdType ErrorId)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType userError;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Error ID and report user error */
  userError.FunctionId = TCPIP_TLS_FCTID_CORE_RL_TRANSMIT;
  userError.UserErrorId = ErrorId;
  userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  TcpIp_TlsCoreError_ReportUserError(userError);

} /* TcpIp_CoreRl_HandleErrorWhileTransmit() */

/**********************************************************************************************************************
 *  TLS CORE BUFFER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_Init(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all buffer related variables */
  /* RX Buffer read/write index */
  {
    TcpIp_TlsBufferRxAdHsStartIdxOfTlsBufferMgmtType RxAdHsStartIdx = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);
    TcpIp_TlsBufferRxAlStartIdxOfTlsBufferMgmtType RxAlStartIdx     = TcpIp_GetTlsBufferRxAlStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);
    TcpIp_TlsBufferRxCcsStartIdxOfTlsBufferMgmtType RxCcsStartIdx   = TcpIp_GetTlsBufferRxCcsStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);
    TcpIp_TlsBufferRxAdHsEndIdxOfTlsBufferMgmtType RxAdHsEndIdx     = TcpIp_GetTlsBufferRxAdHsEndIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);

    TcpIp_SetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAdHsStartIdx);
    TcpIp_SetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAdHsStartIdx);
    TcpIp_SetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAdHsStartIdx);
    TcpIp_SetTlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAdHsStartIdx);
    /* Initialize the current end idx to the actual end idx */
    /* [Sliding End Index]: TLS Rx buffer is a circular buffer. The CSM module decrypts ciphertext
     * directly into the TLS Rx buffer during TLS Rx handling. However, CSM does not support the buffer wraparound,
     * and always expects sufficient output buffer space to decrypt.
     * In certain scenarios, the space available at the end of the TLS Rx buffer is too small to pass to CSM.
     * To avoid such cases, the endIdx of the TLS Rx buffer is implemented as a sliding endIdx.
     R - ReadIdx
     W - WriteIdx
     E - EndIdx
     C - CurrEndIdx
     S = E - W

                                          C <---- CurrEndIdx same as EndIdx
                                  W       E
     -----------------------------v-------v
     |          TLS Rx Buffer             |
     --------------------------------------

     During decryption of received TLS AdHs frame:

     (1) If S < TCPIP_TLS_MIN_BUFFER_SIZE, slide CurrEndIdx

                                  C <-------- Slide the CurrEndIdx to skip using S
                                  W        E
     -----------------------------v        v
     |          TLS Rx Buffer     |xxxxxxxx|
     ------------------------------<   S   >

     Tls now considered the sliding CurrEndIdx as the end of buffer and wrapsaround.
                                  C
          W                       |        E
     -----v-----------------------v        v
     |          TLS Rx Buffer     |xxxxxxxx|
     ------------------------------

     (2) Once data has been read by UL, the CurrEndIdx is slid back to EndIdx, and full buffer is available again
          R                               C
          W                               E
     -----v-------------------------------v
     |          TLS Rx Buffer             |
     -------------------------------------
     */
    TcpIp_SetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAdHsEndIdx);
    /* Initialize the Rx Read and Write index to 0 */
    TcpIp_SetTlsBufferRxAlReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAlStartIdx);
    TcpIp_SetTlsBufferRxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxAlStartIdx);

    TcpIp_SetTlsBufferRxCcsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxCcsStartIdx);
    TcpIp_SetTlsBufferRxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, RxCcsStartIdx);

    /* Initialize the Rx Data Split struct */
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrRxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;

    /* Initialize the fill levels */
    TcpIp_SetAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
    TcpIp_SetAdRxFillLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
  }

  /* TX Buffer read/write index */
  {
    TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType TxAdHsStartIdx = TcpIp_GetTlsBufferTxAdHsStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);
    TcpIp_TlsBufferTxAlStartIdxOfTlsBufferMgmtType TxAlStartIdx     = TcpIp_GetTlsBufferTxAlStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);
    TcpIp_TlsBufferTxCcsStartIdxOfTlsBufferMgmtType TxCcsStartIdx   = TcpIp_GetTlsBufferTxCcsStartIdxOfTlsBufferMgmt(
                                                                        tlsBufferMgmtIdx);

    /* Initialize the Tx Read and Write index to 0 */
    TcpIp_SetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxAdHsStartIdx);
    TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxAdHsStartIdx);

    TcpIp_SetTlsBufferTxAlReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxAlStartIdx);
    TcpIp_SetTlsBufferTxAlWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxAlStartIdx);

    TcpIp_SetTlsBufferTxCcsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxCcsStartIdx);
    TcpIp_SetTlsBufferTxCcsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TxCcsStartIdx);

    /* Initialize the Tx Data Split struct */
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataPtr = NULL_PTR;
    TcpIp_GetAddrTxDataSplitOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)->DataLen = 0u;

    /* Initialize the fill levels */
    TcpIp_SetAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, 0u);
  }

  TcpIp_SetLastReceivedHsTypeOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_HSTYPE_INVALID);

} /* TcpIp_TlsCoreBuffer_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_ClearTxBuffer()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_ClearTxBuffer(
  CONST(TcpIp_TlsBufferTxIterType, AUTOMATIC) StartIdx,
  CONST(TcpIp_TlsBufferTxIterType, AUTOMATIC) EndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferTxIterType clearLen;
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(StartIdx < TcpIp_GetSizeOfTlsBufferTx());
  TCPIP_ASSERT(EndIdx   < TcpIp_GetSizeOfTlsBufferTx());
  TCPIP_ASSERT(StartIdx <= EndIdx);

  clearLen = (EndIdx - StartIdx);
  /* #10 Clear the buffer from the beginning of the passed start index with the passed length */
  VStdLib_MemClr(TcpIp_GetAddrTlsBufferTx(StartIdx), clearLen);                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

} /* TcpIp_TlsCoreBuffer_ClearTxBuffer() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_ClearRxBuffer()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_ClearRxBuffer(
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) StartIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) EndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferRxIterType clearLen;
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(StartIdx < TcpIp_GetSizeOfTlsBufferRx());
  TCPIP_ASSERT(EndIdx   < TcpIp_GetSizeOfTlsBufferRx());
  TCPIP_ASSERT(StartIdx <= EndIdx);

  clearLen = (EndIdx - StartIdx);
  /* #10 Clear the buffer from the beginning of the passed start index with the passed length */
  VStdLib_MemClr(TcpIp_GetAddrTlsBufferRx(StartIdx), clearLen);                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
} /* TcpIp_TlsCoreBuffer_ClearRxBuffer() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_GetAvailableTxBufferSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
*/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreBuffer_GetAvailableTxBufferSize(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint32) AvailableTxBufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a valid TLS connection for this socket. */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# ifdef C_REVIEW_VECTOR                                                                                                 /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Question: Should we restrict this API to only be called after the handshake is finished? */
/* [REVIEW_c] comment visbdk: I think (at least for the client) this could also be useful during HS (so that the upper layer can prepare the first transmit?!  */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK. */
# endif
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
    TcpIp_TlsListenerIterType tlsListenerIdx;
    boolean isTlsListenSocket = FALSE;

#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Question: Would it be easier only to check if the socket state is LISTEN? Do we need to find the listener? */
/* [REVIEW_c] comment visbdk: Don't think so, because even if the socket is in LISTEN, we have to check the port and if it uses TLS. Result in the same number of statements */
/* [REVIEW_c] open visal 16.01.00.7 Question: But in function TcpIp_Tcp_GetAvailableTxBufferSize (that calls this function) we already check that TLS is used. So we could skip the for-loop. Right? */
/* [REVIEW_c] resolved visbdk: I don't see the additional check in the caller function. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK, calling function has been reworked lately. */
#  endif
    /* #20 Check if a listener is assigned to this socket. */
    /* Iterate over all configured TLS-Listeners */
    for (tlsListenerIdx = 0; tlsListenerIdx < TcpIp_GetSizeOfTlsListener(); tlsListenerIdx++)
    {
      /* Check if this TLS-Listener entry is free and return the index */
      if (TcpIp_GetSocketDynIdxOfTlsListener(tlsListenerIdx) == SocketIdx)
      {
        /* The socket is used as a listener, so there are no buffers assigned to this socket. */
        isTlsListenSocket = TRUE;
        break;
      }
    }

    if (isTlsListenSocket == TRUE)
    {
      /* #30 If the socket is a listen socket, no tx buffer is available. */
      *AvailableTxBufferSizePtr = 0u;
    }
    else
# endif
    {
      /* #40 If the socket is a client socket or a socket derived from a listen socket, read the available buffer size. */
      TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx;
      TcpIp_SizeOfTlsBufferTxType   remainingSpaceInAdHsBuffer;  /* Remaining space available in TLS Tx AdHs buffer */

      tlsBufferMgmtIdx           = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(tlsConIdx);
      remainingSpaceInAdHsBuffer = (TcpIp_GetTlsBufferTxAdHsLengthOfTlsBufferMgmt(tlsBufferMgmtIdx)
                                   - TcpIp_GetAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

# ifdef C_REVIEW_VECTOR                                                                                                 /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Question: What do we want to check with this useless assertion? */
/* [REVIEW_c] resolved visbdk: Correct, removed the assertion */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
# endif

      *AvailableTxBufferSizePtr = (uint32)remainingSpaceInAdHsBuffer;
    }

    retVal = E_OK;
  }
  else
  {
    /* There is no TLS connection for this socket. */
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsCoreBufferStruct_Init
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBufferStruct_Init(TcpIp_TlsConnectionIterType TlsConIdx)
{
   TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

   /* #10 Initialize the Rx buffer structures */
   TcpIp_TlsCoreRxBufStruct_Init(tlsBufferMgmtIdx);

} /* TcpIp_TlsCoreBufferStruct_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_Init()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_Init(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfRxBufStructMgtType rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize buffer struct. */
  TcpIp_SetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt, TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(
                                                               TlsBufferMgmtIdx));
  TcpIp_SetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt, 0u);

  /* #20 Initialize each buffer segment. */
  for (rxBufStructSegIdx = TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
       rxBufStructSegIdx < TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
       rxBufStructSegIdx++)
  {
    TcpIp_SetDataPtrOfRxBufStructSeg(rxBufStructSegIdx, NULL_PTR);
  }

} /* TcpIp_TlsCore_RxBufStruct_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_WriteSegment()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_WriteSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) SrcBufPtr,
  uint16 SrcBufLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* Optional indirection: Refer to parameter value range in function description. */
  TcpIp_SizeOfRxBufStructMgtType rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx = TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt);
  Std_ReturnType                 retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if new data is available. */
  if (SrcBufLen > 0u)
  {
    /* #20 Write first buffer struct segment if struct is empty. */
    if (TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt) == 0u)
    {
      TcpIp_SetLenOfRxBufStructSeg(rxBufStructSegIdx, SrcBufLen);
      TcpIp_SetDataPtrOfRxBufStructSeg(rxBufStructSegIdx, SrcBufPtr);
      TcpIp_IncRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);

      retVal = E_OK;
    }
    /* #30 Write additional segment otherwise. */
    else
    {
      retVal = TcpIp_TlsCoreRxBufStruct_WriteAdditionalSegment(TlsBufferMgmtIdx, SrcBufPtr, SrcBufLen);
    }
  }
  /* #40 Succeed call without any further action otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCore_RxBufStruct_WriteSegment() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_WriteAdditionalSegment()
**********************************************************************************************************************/
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_WriteAdditionalSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) SrcBufPtr,
  uint16 SrcBufLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2C(uint8)                             bufSegPtr;
  /* Optional indirection: Refer to parameter value range in function description. */
  TcpIp_SizeOfRxBufStructMgtType               rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_SizeOfRxBufStructSegType               lastRxBufStructSegIdx;
  TcpIp_SizeOfRxBufStructSegType               writeRxBufStructSegIdx;
  TcpIp_RxBufStructSegLvlOfRxBufStructMgtType  lastLvl;
  Std_ReturnType                               retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate index of last segment. */
  lastLvl = (TcpIp_RxBufStructSegLvlOfRxBufStructMgtType)(TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt) - 1u);
  lastRxBufStructSegIdx = TcpIp_TlsCoreRxBufStruct_CalculateNextSegment(TlsBufferMgmtIdx, TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt),
    lastLvl);
  bufSegPtr = TcpIp_GetDataPtrOfRxBufStructSeg(lastRxBufStructSegIdx);

  /* #20 Ignore adding segment if function is called with last segment (used to continue reception in main context). */
  if (&SrcBufPtr[0] == &bufSegPtr[0u])
  {
    retVal = E_OK;
  }
  /* #30 Check if new segment is in same memory segment like last segment otherwise. */
  else if (&SrcBufPtr[0] == &bufSegPtr[TcpIp_GetLenOfRxBufStructSeg(lastRxBufStructSegIdx)])
  {
    /* #40 Update length of last segment. */
    TcpIp_SetLenOfRxBufStructSeg(lastRxBufStructSegIdx, TcpIp_GetLenOfRxBufStructSeg(lastRxBufStructSegIdx) + SrcBufLen);

    retVal = E_OK;
  }
  /* #50 Check if struct size is sufficient for new segment otherwise. */

  else if (TCPIP_RX_BUF_SEG_SIZE_TOTAL > TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt))
  {
    /* #60 Get next segment. */
    writeRxBufStructSegIdx = TcpIp_TlsCoreRxBufStruct_CalculateNextSegment(TlsBufferMgmtIdx,
      TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt),
      TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt));

    /* #70 Write new segment. */
    TcpIp_SetLenOfRxBufStructSeg(writeRxBufStructSegIdx, SrcBufLen);
    TcpIp_SetDataPtrOfRxBufStructSeg(writeRxBufStructSegIdx, SrcBufPtr);
    TcpIp_IncRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);

    retVal = E_OK;
  }
  /* #80 Reject request otherwise. */
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCore_RxBufStruct_WriteAdditionalSegment() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_CalculateNextSegment()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfRxBufStructSegType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_CalculateNextSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TcpIp_SizeOfRxBufStructSegType SegmentIndex,
  TcpIp_RxBufStructSegLvlOfRxBufStructMgtType SegmentLvl)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfRxBufStructSegType NextSegmentIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate next segment index if struct wraps around. */
  if ((SegmentIndex + SegmentLvl) >= TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx))
  {
    NextSegmentIndex = (TcpIp_SizeOfRxBufStructSegType)(TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(TlsBufferMgmtIdx) +
      (SegmentLvl - (TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx) - SegmentIndex)));
  }
  /* #20 Calculate next segment index if struct does not wrap around otherwise. */
  else
  {
    NextSegmentIndex = (TcpIp_SizeOfRxBufStructSegType)(SegmentIndex + SegmentLvl);
  }

  return NextSegmentIndex;
} /* TcpIp_TlsCore_RxBufStruct_CalculateNextSegment() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_GetTotLen()
**********************************************************************************************************************/
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
TCPIP_LOCAL_INLINE FUNC(uint32, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_GetTotLen(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  uint32 BufSegOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                         localBufSegOffset = BufSegOffset;
  uint32                         totalLen = 0u;
  TcpIp_RxBufStructSegIterType   bufSegIter;
  TcpIp_SizeOfRxBufStructMgtType rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx = TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments to get the segment of the specified offset. */
  for (bufSegIter = 0u;
       bufSegIter < TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);
       bufSegIter++)
  {
    /* #20 Check if offset is in next buffer segment. */
    if (localBufSegOffset >= TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx))
    {
      /* #30 Decrement offset by length of current segment. */
      localBufSegOffset -= TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx);
    }
    /* #40 Consider current buffer segment otherwise. */
    else
    {
      /* #50 Increment total length. */
      totalLen += (uint32)(TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx) - localBufSegOffset);

      /* #60 Set offset to zero to increment total length by whole segment length of next segments. */
      localBufSegOffset = 0u;
    }

    /* #70 Calculate next segment index considering buffer struct wrap around. */
    if ((rxBufStructSegIdx + 1u) == TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx))
    {
      rxBufStructSegIdx = TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
    }
    else
    {
      rxBufStructSegIdx++;
    }
  }

  return totalLen;
} /* TcpIp_TlsCore_RxBufStruct_GetTotLen() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_Copy2Buf()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_Copy2Buf(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint8) BufPtr,
  uint32 BufLen,
  uint32 BufSegOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2C(uint8)               bufSegPtr;
  uint32                         localBufLen = BufLen;
  uint32                         localBufSegOffset = BufSegOffset;
  uint32                         bytesToCopy;
  uint32                         bytesCopied = 0u;
  uint32                         segOffset;
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate until all data is copied to provided buffer. */
  while (localBufLen > 0u)
  {
    /* #20 Get index of segment from which shall be copied considering offset. */
    segOffset = localBufSegOffset;
    (void)TcpIp_TlsCoreRxBufStruct_GetBufSegIdx(TlsBufferMgmtIdx, &segOffset, &rxBufStructSegIdx);

    /* #30 Calculate available data length of segment. */
    bytesToCopy = (uint32)(TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx) - segOffset);

    /* #40 Calculate data length to be copied for this segment. */
    if (localBufLen < bytesToCopy)
    {
      bytesToCopy = localBufLen;
    }

    /* #50 Copy data from current segment to provided buffer. */
    bufSegPtr = TcpIp_GetDataPtrOfRxBufStructSeg(rxBufStructSegIdx);
    VStdMemCpy(&BufPtr[bytesCopied], &bufSegPtr[segOffset], bytesToCopy);                                               /* PRQA S 315 */ /* MD_MSR_VStdLibCopy */
    localBufLen -= bytesToCopy;
    bytesCopied += bytesToCopy;
    localBufSegOffset += bytesToCopy;
  }
} /* TcpIp_TlsCore_RxBufStruct_Copy2Buf() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_GetBufSegIdx()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_GetBufSegIdx(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  TCPIP_P2V(uint32) OffsetPtr,
  TCPIP_P2V(TcpIp_SizeOfRxBufStructSegType) BufSegIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                         offset = *OffsetPtr;
  TcpIp_RxBufStructSegIterType   bufSegIter;
  TcpIp_SizeOfRxBufStructMgtType rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_SizeOfRxBufStructSegType rxBufStructSegIdx = TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt);
  Std_ReturnType                 retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments to get the segment of the specified offset. */
  for (bufSegIter = 0u;
       bufSegIter < TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);
       bufSegIter++)
  {
    /* #20 Check if offset is in next buffer segment. */
    if (offset >= TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx))
    {
      /* #30 Decrement offset by length of current segment. */
      offset -= TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx);

      /* #40 Calculate next segment index considering buffer struct wrap around. */
      if ((rxBufStructSegIdx + 1u) == TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx))
      {
        rxBufStructSegIdx = TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
      }
      else
      {
        rxBufStructSegIdx++;
      }
    }
    /* #50 Return current index otherwise. */
    else
    {
      *BufSegIdxPtr = rxBufStructSegIdx;
      *OffsetPtr = offset;
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsCore_RxBufStruct_GetBufSegIdx() */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_RxBufStruct_ReleaseSegment()
**********************************************************************************************************************/
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
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxBufStruct_ReleaseSegment(
  TcpIp_SizeOfTlsBufferMgmtType TlsBufferMgmtIdx,
  uint32 Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(uint8)                             bufSegPtr;
  uint32                                       localLen = Len;
  TcpIp_RxBufStructSegIterType                 bufSegIter;
  /* Optional indirection: Refer to parameter value range in function description. */
  TcpIp_SizeOfRxBufStructMgtType               rxBufStructMgt = TcpIp_GetRxBufStructMgtIdxOfTlsBufferMgmt(TlsBufferMgmtIdx);
  TcpIp_RxBufStructSegLvlOfRxBufStructMgtType  bufSegLvl = TcpIp_GetRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);
  TcpIp_SizeOfRxBufStructSegType               rxBufStructSegIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all segments. */
  for (bufSegIter = 0u; bufSegIter < bufSegLvl; bufSegIter++)
  {
    rxBufStructSegIdx = TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt);
    bufSegPtr = TcpIp_GetDataPtrOfRxBufStructSeg(rxBufStructSegIdx);

    /* #20 Release in current segment and stop iteration if segment length is bigger than length to be released. */
    if (localLen < TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx))
    {
      TcpIp_SetLenOfRxBufStructSeg(rxBufStructSegIdx, (TcpIp_LenOfRxBufStructSegType)(
        TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx) - localLen));
      TcpIp_SetDataPtrOfRxBufStructSeg(rxBufStructSegIdx, &bufSegPtr[localLen]);

      break;
    }
    /* #30 Release segment completely otherwise. */
    else
    {
      /* #40 Reset segment length and decrement length to be released. */
      localLen -= TcpIp_GetLenOfRxBufStructSeg(rxBufStructSegIdx);
      TcpIp_SetLenOfRxBufStructSeg(rxBufStructSegIdx, 0u);
      TcpIp_DecRxBufStructSegLvlOfRxBufStructMgt(rxBufStructMgt);

      /* #50 Calculate next segment index considering buffer struct wrap around. */
      if ((rxBufStructSegIdx + 1u) == TcpIp_GetRxBufStructSegEndIdxOfTlsBufferMgmt(TlsBufferMgmtIdx))
      {
        TcpIp_SetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt, TcpIp_GetRxBufStructSegStartIdxOfTlsBufferMgmt(
                                                                      TlsBufferMgmtIdx));
      }
      else
      {
        TcpIp_SetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt, (TcpIp_RxBufStructSegIdxOfRxBufStructMgtType)
          (TcpIp_GetRxBufStructSegIdxOfRxBufStructMgt(rxBufStructMgt) + 1u));
      }
    }
  }
} /* TcpIp_TlsCore_RxBufStruct_ReleaseSegment() */

/**********************************************************************************************************************
 *  TLS CORE MAIN FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_Rx
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_Rx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections reception of TLS protocol */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Handles reception of record layer */
    TcpIp_TlsCoreMainFunction_RxRl(tlsConIdx);

    /* #30 Check if the TLS connection is not in state inactive */
    if (TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) != TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE)
    {
      /* #40 Handles reception of change cipher spec */
      TcpIp_TlsCoreMainFunction_RxCcs(tlsConIdx);
      /* #50 Handles reception of helloRequest messages */
      TcpIp_TlsCoreMainFunction_RxHelloRequest(tlsConIdx);

      /* #60 Handles reception of handshake */
      TcpIp_TlsCoreMainFunction_RxHs(tlsConIdx);

      /* #70 Handles reception of alerts */
      TcpIp_TlsCoreMainFunction_RxAl(tlsConIdx);

      /* #80 Handles reception of application data */
      TcpIp_TlsCoreMainFunction_RxAd(tlsConIdx);
    }
  }
} /* TcpIp_TlsCoreMainFunction_Rx() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_State
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
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_State(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections and handle TLS substates */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Handle User events */
    TcpIp_TlsCoreState_UserEventHandler(tlsConIdx);

    /* #30 Handle TCP events */
    TcpIp_TlsCoreState_TcpEventHandler(tlsConIdx);

    /* #40 Handle TLS Handshake related states */
    TcpIp_TlsCoreState_HandshakeHandler(tlsConIdx);

    /* #50 Handle TLS User error related states */
    TcpIp_TlsCoreState_UserErrorHandler(tlsConIdx);

    /* #60 Handle TLS Alert related states */
    TcpIp_TlsCoreState_AlertHandler(tlsConIdx);

    /* #70 Handle TLS Application data states */
    TcpIp_TlsCoreState_ApplicationDataHandler(tlsConIdx);
  }
} /* TcpIp_TlsCoreMainFunction_State() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_Tx
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
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_Tx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS-Connections and handle transmission of TLS protocol */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Check if the TLS connection is not in state inactive */
    if (TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) != TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE)
    {
      /* #30 Handles transmission of alert frames */
      TcpIp_TlsCoreMainFunction_TxAl(tlsConIdx);

      /* #40 Handles transmission of handshake frames */
      TcpIp_TlsCoreMainFunction_TxHs(tlsConIdx);

      /* #50 Handles transmission of application data frames */
      TcpIp_TlsCoreMainFunction_TxAd(tlsConIdx);

      /* #60 Handles transmission of ChangeCipherSpec frames */
      TcpIp_TlsCoreMainFunction_TxCcs(tlsConIdx);
    }
  }
} /* TcpIp_TlsCoreMainFunction_Tx() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_LowPrio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_LowPrio(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured TLS connections and handle low prio context */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* Invoke Core async context handler */
    TcpIp_TlsCoreCtx_AsyncHandler(tlsConIdx);

/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(tlsConIdx) == TCPIP_TLS_SERVER)
#  endif
    {
      /* Mode == TCPIP_TLS_SERVER */
      /* Invoke Server async context handler */
      TcpIp_TlsServerCtx_AsyncHandler(tlsConIdx);
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      /* Invoke Client async context handler */
      TcpIp_TlsClientCtx_AsyncHandler(tlsConIdx);
    }
# endif
  }
} /* TcpIp_TlsCoreMainFunction_LowPrio() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_AsyncHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_AsyncHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */

  /* #10 Invoke async handlers if flag has been triggered */
# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
  /* If triggered, calculate Diffie-Hellman public key and reset the flag */
  if (TcpIp_IsDhPubKeyAsyncFlagOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey(TlsConIdx);
    TcpIp_SetDhPubKeyAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  }

  /* If triggered, calculate Diffie-Hellman shared secret and reset the flag */
  if (TcpIp_IsDhSharedSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    boolean dhPreconditionFullfilled = FALSE;                                                                           /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */

/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#   if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#   endif
    {
      /* Mode == TCPIP_TLS_SERVER */
      /* In case of an TLS-Server, no additional preconditions must be checked */
      dhPreconditionFullfilled = TRUE;
    }
#   if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#   endif
#  endif
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      /* In case of an TLS-Client and the ECDH key exchange we must check the status of the received server certificate,
         that contains the public key which is needed for the next calculation */
      if (TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx) == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH)
      {
        /* [HS Server Certificate Chain Handling StM] Cert chain processing is completed, proceed with further steps */
        if (TcpIp_GetHsCertStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CERTCHAIN_COMPLETE)
        {

          dhPreconditionFullfilled = TRUE;
        }
        /* else - received Server certificate is not ready. Wait for next cycle */
      }
      else
      {
        /* All other key exchange methods - no further preconditions */
        dhPreconditionFullfilled = TRUE;
      }
    }
#  endif

    /* Calculate the DH shared secret if the precondition is fulfilled */
    if (dhPreconditionFullfilled == TRUE)                                                                               /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
    {
      TcpIp_TlsCoreCtx_CalcDhSharedSecret(TlsConIdx);
      TcpIp_SetDhSharedSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
    }
    /* else - wait for next cycle */
  }

# endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

# if ((TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON))
  /* If triggered, calculate premaster secret using PSK and reset the flag */
  if (TcpIp_IsPskPremasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    TcpIp_TlsCoreCtx_CalcPskPremasterSecret(TlsConIdx);
    TcpIp_SetPskPremasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
# endif /* (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON) */

  /* If triggered, calculate the Master Secret and reset the flag */
  if (TcpIp_IsCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    TcpIp_TlsCoreCtx_CalcMasterSecret(TlsConIdx);
    TcpIp_SetCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
} /* TcpIp_TlsCoreCtx_AsyncHandler() */

# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, TCPIP_CODE) TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 lenRetVal = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the length of the specific public key value depending on the given Curve ID */
  switch (CurveId)
  {
    case TCPIP_CURVE_ID_SECP256R1: {
      lenRetVal = TCPIP_CURVE_ID_SECP256R1_PUBKEY_LEN;
      break;
    } /* case TCPIP_CURVE_ID_SECP256R1 */
    case TCPIP_CURVE_ID_SECP384R1: {
      lenRetVal = TCPIP_CURVE_ID_SECP384R1_PUBKEY_LEN;
      break;
    } /* case TCPIP_CURVE_ID_SECP384R1 */
    case TCPIP_CURVE_ID_SECP521R1: {
      lenRetVal = TCPIP_CURVE_ID_SECP521R1_PUBKEY_LEN;
      break;
    } /* case TCPIP_CURVE_ID_SECP521R1 */
    case TCPIP_CURVE_ID_X25519: {
      lenRetVal = TCPIP_CURVE_ID_X25519_PUBKEY_LEN;
      break;
    } /* case TCPIP_CURVE_ID_X25519 */
    case TCPIP_CURVE_ID_X448: {
      lenRetVal = TCPIP_CURVE_ID_X448_PUBKEY_LEN;
      break;
    } /* case TCPIP_CURVE_ID_X448 */
    default: {                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      break;
    } /* default */
  } /* switch */

  return lenRetVal;
} /* TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey
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
 *
 *
 */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STPAR */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));

  Std_ReturnType retVal = E_NOT_OK;
  uint16 localErrorId = TCPIP_TLS_ERRORID_NOT_SET;                                                                      /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the Csm key for the Key Exchange operation is configured */
  if (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {
    uint32 keyExchangePubKeyLen;
    uint32 keyExchangeCsmKey = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeIdxOfTlsHandshake(activeTlsHandshakeIdx)];

    /* #20 Get the available space in the TX buffer */
    keyExchangePubKeyLen = ((uint32)TcpIp_GetTlsBufferTxAdHsEndIdxOfTlsBufferMgmt(tlsBufferMgmtIdx) -
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));

    /* #30 Set the current key valid */
    if (TCPIP_CSM_KeySetValid(keyExchangeCsmKey) == E_OK)
    {
      /* #40 Calculate the Diffie-Hellman public key and write it directly into the TX buffer */
      if (TCPIP_CSM_KeyExchangeCalcPubVal(keyExchangeCsmKey,
        TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)),
        &keyExchangePubKeyLen) == E_OK)
      {
        /* #50 CSM call OK, check the length of the new calculated public key to match the expected key length for the used curve */
        if (keyExchangePubKeyLen == TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)))
        {
          /* Increment the write index by the consumed length  */
          TcpIp_SetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
            TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) + ((uint16)keyExchangePubKeyLen));

          /* #60 key have the expected length */
          retVal = E_OK;
        }
        else
        {
          /* #70 Error Public key length mismatch */
          localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_LEN_MISMATCH;
        }
      }
      else
      {
        /* #80 Error Crypto CSM call failed */
        localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED;
      }
    }
    else
    {
      /* #90 Error Crypt CSM Key set valid failed */
      localErrorId = TCPIP_TLS_ERRORID_CRYPTO_SET_VALID_FAILED;
    }

    /* #100 If all sub-functions returned E_OK */
    if (retVal == E_OK)
    {
      /* #110 Set the async state to DONE */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
    }
    else
    {
      /* #120 otherwise, handles error while async CSM processing */
      TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_CORE_ASYNCCTX_CALC_DH_PUBKEY, localErrorId);
    }
  }
  else
  {
    /* #130 Csm Key for KeyExchange operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }
} /* TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_CalcDhSharedSecret
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
/* PRQA S 6010, 6030, 6050 1 */ /* MD_TcpIp_Tls_STPTH, MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcDhSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  uint32           keyExchangeCsmKey;
  TCPIP_P2C(uint8) publicKeyPtr;
  uint32           publicKeyLen;
  uint8            ecdhPubKeyBuf[TCPIP_TLS_MAX_SIGNATURE_LEN] = { 0 };
  uint32           ecdhPubKeyBufLen   = TCPIP_TLS_MAX_SIGNATURE_LEN;
  uint16           localErrorId       = TCPIP_TLS_ERRORID_NOT_SET;                                                      /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  Std_ReturnType   retVal             = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Check if the necessary key for the DH operation is configured */
  if (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE )
  {
    keyExchangeCsmKey = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeIdxOfTlsHandshake(activeTlsHandshakeIdx)];

/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#   if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#   endif
    {
      /* Mode == TCPIP_TLS_SERVER */
      TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

      /* #10 Set public key pointer and length of the public key to the received client key */
      /* Pointer to the Client public key which is located in the RX Buffer */
      publicKeyPtr = TcpIp_GetAddrTlsBufferRx(
        TcpIp_GetTlsBufferRxClientKeyExchangePubKeyIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx));

      publicKeyLen = (TcpIp_GetTlsBufferRx(
        TcpIp_GetTlsBufferRxClientKeyExchangePubKeyLenIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)));

      /* #20 in case of ECDH key exchange extract the private server key from the certificate */
      if (TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx) == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH)
      {
        /* Private key of server certificate is stored within the signature generate key */
        uint32 serverPrivKeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeSignatureGenerateIdxOfTlsHandshake(activeTlsHandshakeIdx)];

        /* We copy the private key of the server, which is used instead of an ephemeral key, into the key exchange key element. */
        retVal = TCPIP_CSM_KeyElementCopyPartial(serverPrivKeyId, CRYPTO_KE_SIGNATURE_KEY,
          0u, 0u, TCPIP_TLS_KEYEXCH_ECC_PRIVKEYLEN, keyExchangeCsmKey, CRYPTO_KE_KEYEXCHANGE_PRIVKEY);
      }
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: Add better (more detailed) description. For ECDHE, the ephemeral key already is generated into the keyExchange key and therefore does not have to be copied any more. */
/* [REVIEW_c] resolved visbdk: Added comment. */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#   endif
      /* ECDHE key exchange: Ephemeral key already is generated into the keyExchange key and therefore does not have to be copied any more */
    }
#   if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#   endif
#  endif
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      uint32 rxServerPubKey;

      /* #30 Set public key pointer and length of the public key depending on the selected key exchange method */
      if (TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx)
           == TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH)
      {
        /* ECDH Key exchange */
        /* in case of an ECDH cipher suite, the received server certificate contains the public key of the server */
        rxServerPubKey = TcpIp_CsmKeyId[
          TcpIp_GetCsmKeyIdKeyExchangeSignatureVerifyIdxOfTlsHandshake(activeTlsHandshakeIdx)];

        /* copy the key from the server certificate to the key element of the key exchange key */
        retVal = TCPIP_CSM_KeyElementGet(rxServerPubKey, CRYPTO_KE_CERTIFICATE_SUBJECT_PUBLIC_KEY,
          &ecdhPubKeyBuf[0], &ecdhPubKeyBufLen);

        publicKeyPtr = &ecdhPubKeyBuf[0];
        publicKeyLen = ecdhPubKeyBufLen;

        if (TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx) == TCPIP_CURVE_ID_SECP256R1)
        {
          /* In case of ECDH with SECP256 we have to add +1 to the size of the public key (compression flag) */
          publicKeyLen += TCPIP_TLS_KEYEXCH_COMPFLAGLEN;
        }
      }
      else
      {
        /* ECDHE key exchange */
        TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

        /* #40 Set public key pointer and key length to the server key received in the ServerKeyExchange message. */
        /* Pointer to the Server public key which is located in the RX Buffer */
        publicKeyPtr = TcpIp_GetAddrTlsBufferRx(
          TcpIp_GetTlsBufferRxServerKeyExchangePubKeyIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx));

        /* Public key length is checked in function TcpIp_TlsClientMsg_ServerKeyExchangeMsgGetPubKey() against its boundaries */
        publicKeyLen = (TcpIp_GetTlsBufferRx(
          TcpIp_GetTlsBufferRxServerKeyExchangePubKeyLenIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)));
      }
    }
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: This else path should not be necessary. Either server or client is always enabled. */
/* [REVIEW_c] rejected visbdk: In case of TLS-Server=ON and TLS-Client= OFF this is needed, otherwise the two parameters are not used and result in MISRA warnings */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
#  else
    TCPIP_DUMMY_STATEMENT(ecdhPubKeyBuf[0]);                                                                            /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
    TCPIP_DUMMY_STATEMENT_CONST(ecdhPubKeyBufLen);                                                                      /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif

    /* #50 Check if the compression flag is present in the message */
    if (TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
      TcpIp_GetEllipticCuveIdOfTlsHandshake(activeTlsHandshakeIdx)) == TRUE)
    {
      publicKeyLen -= TCPIP_TLS_KEYEXCH_COMPFLAGLEN;
    }


    /* #60 Forward the public key to the CSM to calculate the Diffie-Hellman shared secret */
    if ( retVal == E_OK)
    {
      retVal = E_NOT_OK;
      /* Set the current key valid */
      if (TCPIP_CSM_KeySetValid(keyExchangeCsmKey) == E_OK)
      {
        /* Calculate the Diffie-Hellman shared secret  */
        if (TCPIP_CSM_KeyExchangeCalcSecret(keyExchangeCsmKey, publicKeyPtr, publicKeyLen) == E_OK)
        {
          retVal = E_OK;
        }
        else
        {
          /* Error crypto CSM call failed */
          localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED;
        }
      }
      else
      {
        /* Error Crypt CSM Key set valid failed */
        localErrorId = TCPIP_TLS_ERRORID_CRYPTO_SET_VALID_FAILED;
      }
    }
    else
    {
      /* Error crypto CSM call failed in prepared keys */
      localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED;
    }


    if (retVal == E_OK)
    {
      /* Set the async state to DONE */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
    }
    else
    {
      /* otherwise, handles error while async CSM processing */
      TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx,
        TCPIP_TLS_FCTID_CORE_ASYNCCTX_CALC_DH_SHAREDSECRET, localErrorId);
    }
  }
  else
  {
    /* CSM Key for DH operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }

} /* TcpIp_TlsCoreCtx_CalcDhSharedSecret() */

# endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
# if ((TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON))
/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_CalcPskPremasterSecret
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
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcPskPremasterSecret(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* General structure of PSK premaster secrets (PMS) */
  /*        ----------------------------------------------------------------
   *        | uint16 M | other_secret (M bytes) | uint16 N | PSK (N bytes) |
   *        ----------------------------------------------------------------
   *        |<--             PMS First Part             -->|
   *        |<--             PMS                                         -->|
   * In the following the array "pmsFirstPart" holds all fields except the PSK field
   */

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsPskIdentityActiveIdxOfTlsConnectionDynType activeTlsPskIdentityIdx =
      TcpIp_GetTlsPskIdentityActiveIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(
                                                         TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_PskKeyLengthOfTlsPskIdentityType pskKeyLength = TcpIp_GetPskKeyLengthOfTlsPskIdentity(activeTlsPskIdentityIdx);
  TcpIp_TlsCsmKeyInfoType pmsKey;
  TcpIp_TlsCsmKeyInfoType pskKey;

  /* The preMasterSecretPart1Buffer takes two 2 byte length fields and M bytes for other_secret. For key exchange method
     PSK (plain) other_secret has the same length as the preshared key, for others it would be shorter than the PSK. */
  uint8 pmsFirstPart[TCPIP_TLS_PSK_PMS_OTHER_SECRET_LEN_FIELD_LEN + TCPIP_TLS_PSK_PMS_PSK_LEN_FIELD_LEN
                     + TCPIP_TLS_PSK_MAX_KEY_LENGTH];
  TCPIP_P2V(uint8) pmsFirstPartPtr = &pmsFirstPart[0];
  uint8 pmsFirstPartLength; /* length depends on active PSK cipher suite */

  uint16 localErrorId = TCPIP_TLS_ERRORID_NOT_SET;                                                                      /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the necessary key for the PSK PreMasterSecret operation is configured */
  if (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {
    /*#20 Retrieve preshared key from active PSK Identity */
    pskKey.KeyId = TcpIp_GetPskCsmKeyIdOfTlsPskIdentity(activeTlsPskIdentityIdx);
    pskKey.KeyElementId = CRYPTO_KE_CIPHER_KEY;
    pskKey.KeyLen = (uint32)pskKeyLength;

    /* #30 Get the key for premaster secret calculation */
    pmsKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeIdxOfTlsHandshake(activeTlsHandshakeIdx)];
    pmsKey.KeyElementId = CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE;

    /* #40 Depending on the key exchange method, build the first part of the PMS */

    {
      /* For plain PSK, structure of premaster secret  with PSK key length N bytes:
       * -----------------------------------------------------------
       * | uint16 N       | N zero octets | uint16 N |   N octets  |
       * | oth_secret_len |  other_secret |  psk_len |     psk     |
       * -----------------------------------------------------------
       * |<--            PMS First Part           -->|
       * |<--            PMS                                    -->|
       */

       /* For Plain psk, build the first part of the PMS as described above */

       /* For plain psk, length of other_secret is same as psk length */
      pmsFirstPartLength = TCPIP_TLS_PSK_PMS_OTHER_SECRET_LEN_FIELD_LEN + pskKeyLength + TCPIP_TLS_PSK_PMS_PSK_LEN_FIELD_LEN;


    /* Set length field of other secret */
      IpBase_PutUint16(pmsFirstPartPtr, 0, (uint16)pskKey.KeyLen);

      /* Set psk_len bytes of zero as other_secret */
      VStdMemSet(&pmsFirstPartPtr[TCPIP_TLS_PSK_PMS_OTHER_SECRET_LEN_FIELD_LEN],                                        /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TCPIP_TLS_PSK_PMS_OTHER_SECRET_PLAIN_PATTERN, pskKeyLength);

      /* Set length field of psk (psk_len) */
      IpBase_PutUint16(pmsFirstPartPtr, (TCPIP_TLS_PSK_PMS_OTHER_SECRET_LEN_FIELD_LEN + pskKey.KeyLen), (uint16)pskKey.KeyLen);

    }

    /* #50 Set other secret followed by psk into the pms key, and set to valid */
    if (TCPIP_CSM_KeyElementSet(pmsKey.KeyId, pmsKey.KeyElementId, pmsFirstPartPtr, pmsFirstPartLength) == E_OK)
    {
      /* Copy psk into pms key element */
      if (TCPIP_CSM_KeyElementCopyPartial(pskKey.KeyId, pskKey.KeyElementId, 0, pmsFirstPartLength, pskKey.KeyLen, pmsKey.KeyId,
        pmsKey.KeyElementId)
        == E_OK)
      {
        /* Set Csm Key of pms to valid */
        if (TCPIP_CSM_KeySetValid(pmsKey.KeyId) == E_OK)
        {
          retVal = E_OK;
        }
        else
        {
          /* Error SetValid */
          localErrorId = TCPIP_TLS_ERRORID_CRYPTO_SET_VALID_FAILED;
        }
      }
      else
      {
        /* Error Copy Partial */
        localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_KEYELEMENTCOPYPARTIAL_FAILED;
      }
    }
    else
    {
      /* Error KeyElement Set */
      localErrorId = TCPIP_TLS_ERRORID_CRYPTO_CSM_KEYELEMENTSET_FAILED;
    }

    /* #60 Set Async state to DONE if all sub-functions returned E_OK */
    if (retVal == E_OK)
    {
      /* Set the async state to DONE */
      TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
    }
    else
    {
      /* otherwise, handles error while async CSM processing */
      TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_CORE_CRYPTO_PSK_CALC_PREMASTERSECRET,
        localErrorId);
    }
  }
  else
  {
    /* #70 CSM Key for PSK PreMasterSecret operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }
} /* TcpIp_TlsCoreCtx_CalcPskPremasterSecret() */
# endif /* (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_CalcMasterSecret
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
/* PRQA S 6030, 6050 1 */ /* MD_TcpIp_Tls_STCYC, MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcMasterSecret(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 State machine for key material calculation */
  while (TcpIp_GetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE)
  {
    switch (TcpIp_GetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx))
    {
      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_INIT:
      {
        /* #20 In INIT state, move to the next state depending on the key exchange method */
        TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

        switch (keyExchangeMethod)
        {
# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
          /* ECDH(E) methods */
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
          case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
          {
            TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_REDUCE_SHARED_KEY);
            break;
          }
# endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
          /* PSK method */
          case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
          {
            TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_CALC_MASTER_SECRET);
            break;
          }
          /* Unsupported method */
          default:
          {
            /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the
            active cipher suite received in the server_hello message. */
            break;
          }
        }  /* switch (keyExchangeMethod) */

        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_INIT */

# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_REDUCE_SHARED_KEY:
      {
        /* #30 In REDUCE_SHARED_KEY state, for ECDH(E), calculate the reduced shared key */
        if (TcpIp_TlsCoreCrypto_ReduceSharedKey(TlsConIdx) == E_OK)
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_CALC_MASTER_SECRET);
        }
        else
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT);
        }
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_REDUCE_SHARED_KEY */
# endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_CALC_MASTER_SECRET:
      {
        /* #40 In CALC_MASTER_SECRET state, Calculate the master secret */
        if (TcpIp_TlsCoreCrypto_CalcMasterSecret(TlsConIdx) == E_OK)
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DERIVE_KEY_BLOCK);
        }
        else
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT);
        }
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_CALC_MASTER_SECRET */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DERIVE_KEY_BLOCK:
      {
        /* #50 In DERIVE_KEY_BLOCK state, derive the key block */
        if (TcpIp_TlsCoreCrypto_DeriveKeyBlock(TlsConIdx) == E_OK)
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_SET_CSM_KEYS);
        }
        else
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT);
        }
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DERIVE_KEY_BLOCK */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_SET_CSM_KEYS:
      {
        /* #60 In SET_CSM_KEYS state, set the Csm key elements */
        if (TcpIp_TlsCoreCrypto_SetCsmKeys(TlsConIdx) == E_OK)
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_FINALIZE);
        }
        else
        {
          TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT);
        }
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_SET_CSM_KEYS */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_FINALIZE:
      {
        /* #70 In MATERIAL_FINALIZE state, finalize the state machine handling */
        /* reset the Async trigger flag */
        TcpIp_SetCalcMasterSecretAsyncFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
        /* Set the async state to DONE */
        TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);
        TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE);
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_FINALIZE */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT:
      {
        /* #80 If MATERIAL_ABORT state is hit, abort the handshake */
        /* User error has already been reported, just trigger handshake abort */
        TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(TlsConIdx, TCPIP_TLS_FCTID_NOT_SET, TCPIP_TLS_ERRORID_NOT_SET);
        TcpIp_SetCalcKeyMaterialStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE);
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT */

      case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE:
      {
        /* #90 DONE state, exit state machine */
        break;
      } /* case TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE */
      default:
      {
        /* do nothing - unreachable code */
        break;
      }
    } /* switch() */
  } /* while() */
} /* TcpIp_TlsCoreCtx_CalcMasterSecret() */

/**********************************************************************************************************************
 *  TLS CORE MAIN FUNCTION RX
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxRl
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
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxRl(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 totDataLen;  /* Stores the length information over all received data stored in RxBufStruct */
  uint16 expectedRlLen = 0; /* Stores the length information peeked from RL-Header */
  uint8  rlHdr[TCPIP_TLS_RLHDRLEN]; /* Filled with the received RL-Header */
  TcpIp_TlsAlertDescriptionType rlAlertDescription = TCPIP_TLS_ALERT_UNSET;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that we are in the correct state to process the RL frame */
  if (   ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_STATE_CONNECTION_CLOSING)
      && (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)))                       /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {
    totDataLen = TcpIp_TlsCoreRxBufStruct_GetTotLen(tlsBufferMgmtIdx, 0u);

    if (totDataLen != 0u)
    {
      /* #20 Check the received RL header (or header part) if it is valid */
      /* This function peeks the received bytes of the RL header and sets the AlertDescription if it is not valid. */
      /* If we do not received the complete RL header so far, this function simply returns E_OK and we wait until the next cycle */
      if (   (TcpIp_TlsCoreRl_ValidateFrameHdr(TlsConIdx, totDataLen, &rlHdr[0], &rlAlertDescription) == E_OK)          /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
          && (TcpIp_TlsCoreRl_ValidateRlFragmentLength(TlsConIdx, &rlHdr[0], &rlAlertDescription) == E_OK))
      {
        /* #30 If we receive an valid TLS RL header, check that we received the full RL frame and the TLS connection is in the correct state */
        Std_ReturnType retVal = TcpIp_TlsCoreRl_CheckIfFrameIsReceivable(TlsConIdx, &rlHdr[0], &rlAlertDescription);

        if ( (TcpIp_TlsCoreRl_VerifyFrameCompleteness(totDataLen, &rlHdr[0], &expectedRlLen) == E_OK) && (retVal == E_OK) )
        {
          /* #40 If we receive the full TLS frame, validate the frame and forward to upper layer (AD, HS, AL, CCS) */
          if (TcpIp_TlsCoreRl_ForwardFrameToUpperLayer(TlsConIdx, &rlHdr[0], expectedRlLen, &rlAlertDescription) == E_OK)
          {
            /* #50 Successfully forwarded the frame to the upper layer */
            TcpIp_SetLastReceivedContentTypeOfTlsConnectionDyn(TlsConIdx, rlHdr[TCPIP_TLS_RLCT_OFFSET]);
          }
          else
          {
            /* #60 otherwise handle reception of a invalid RL frame include the complete HDR */
            TcpIp_TlsCoreRl_HandleInvalidRlFrame(TlsConIdx, (expectedRlLen + TCPIP_TLS_RLHDRLEN), rlAlertDescription);
          }
        }
        else
        {
          /* #70 otherwise do nothing and wait for the next cycle */
        }
      }
      /* #80 Trigger alert in case of an invalid RL Frame HDR */
      if (rlAlertDescription != TCPIP_TLS_ALERT_UNSET)
      {
        TcpIp_TlsCoreRl_HandleInvalidRlFrame(TlsConIdx, (uint16)totDataLen, rlAlertDescription);
      }
    }
  }
} /* TcpIp_TlsCoreMainFunction_RxRl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxCcs(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that we are in the correct state to receive the CCS message */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE))
  {
    if ((TcpIp_IsRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx) == TRUE))
    {
      /* #20 Check if we can forward the CCS message to the upper layer */
      if (TcpIp_TlsCoreCtCcs_ValidateAndForwardFrameToCCsHandler(TlsConIdx) == E_OK)
      {
        /* #30 if so, we processed this messaged so reset the RL RxIndication flag */
        TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
      }
    }
  }
} /* TcpIp_TlsCoreMainFunction_RxCcs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxHelloRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxHelloRequest(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reception of HelloRequest is possible in all connection states */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) != TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE)
  {
    /* #20 Check if a unprocessed record layer frame is present */
    if ((TcpIp_IsRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx) == TRUE))
    {
      /* Only process the frame if it is the content type handshake */
      if (  (TcpIp_GetLastReceivedContentTypeOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CT_HS)
        /* AND  we do not process any handshake messages at the moment
         *     (because then the read index is pointing to an not processed index). We can not receive RL frames in this state of processing.
         *     OR the handshake is already finished
         */
           && ((TcpIp_GetHsRxIndicationCntOfTlsConnectionDyn(TlsConIdx) == 0u) || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
         )
      {
        /* #30 Validate the possible HelloRequest frame and forward it to server/client specific handling */
        if (TcpIp_TlsCoreCtHs_ValidateHelloRequestFrame(TlsConIdx) == E_OK)
        {
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
          if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
          {
            /* Mode == TCPIP_TLS_SERVER */
            /* TLS Server should never receive this message - trigger alert */
            TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_UNEXP_MSG);
          }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
          else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
          {
            /* Mode == TCPIP_TLS_CLIENT */
            /* RFC5246 - 7.4.1.1.  Hello Request */
            /*     This message will be ignored by the client if the client is
             *     currently negotiating a session.  This message MAY be ignored by
             *     the client if it does not wish to renegotiate a session, or the
             *     client may, if it wishes, respond with a no_renegotiation alert.
             */

            TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

             /* Increment read pointer by the 1 byte content type and by the 3 byte handshake type_len length */
            TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
              (TCPIP_TLS_CT_LEN + TCPIP_TLS_HSLEN_LEN));

            /* Update the current handshake message end index */
            TcpIp_SetTlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx,
              (TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)));

            /* If we receive the HelloRequest frame during application data, skip the data for the upper layer */
            if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
            {
              /* This is only relevant after the TLS handshake, since the UlRxIndIdx is automatically updated at the end of the handshake. */
              TcpIp_TlsCoreRl_IncrementUlRxIndIdxWithWraparound(TlsConIdx,
                (TCPIP_TLS_CT_LEN + TCPIP_TLS_HSLEN_LEN));
            }

            /* #40 if so, we processed this messaged so reset the RL RxIndication flag */
            TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
          }
# endif
        }
      }
    }
  }
} /* TcpIp_TlsCoreMainFunction_RxHelloRequest() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxHs
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
/* PRQA S 6050, 6080 1 */ /* MD_TcpIp_Tls_STCAL, MD_TcpIp_Tls_STMIF */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxHs(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 expectedHsMsgLen = 0; /* Holds the message length information peeked from HS-Header */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process Rx HS function only if the current connection is in an active HS state */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE))
  {
    /* #20 Check if there is an async operation pending */
                                                                                                                        /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    if (   (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CTX_ASYNC_PENDING)
        /* [HS Server Certificate Chain Handling StM] Only handle reception if certificate processing is not in progress */
        && (TcpIp_GetHsCertStateOfTlsConnectionDyn(TlsConIdx) != TCPIP_TLS_CERTCHAIN_IN_PROGRESS))
    {
      /* #30 Check if we received at least one record layer frame or the last frame is not completely parsed */
      if (TcpIp_IsRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx) == TRUE)
      {
        /* All conditions are valid, we can now try to process the message */
        /* #40 Check that we received the complete message - will return E_NOT_OK if message is not received completely */
        if (TcpIp_TlsCoreCtHs_VerifyMsgCompleteness(TlsConIdx, &expectedHsMsgLen) == E_OK)
        {
          /* Message is received completely */
          /* #50 Check if we can forward the complete message to HS state machine */
          if (TcpIp_TlsCoreCtHs_ValidateAndForwardMessageToHsHandler(TlsConIdx, expectedHsMsgLen) == E_OK)
          {
            TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAdHsWriteIdx
              = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
            TcpIp_TlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDynType currentHsMsgEndIdx
              = TcpIp_GetTlsBufferRxAdHsCurrHsMsgEndIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

            /* #60 Only if we processed the complete RL-Frame (which could contain multiple HS messages) we
                   reset the RL RxIndication flag */
            /* If there are any further messages contained in this RL-Frame the currentHsMsgEndIdx is smaller then the WriteIdx */
            if (currentHsMsgEndIdx >= rxAdHsWriteIdx)
            {
              /* There are no further messages in this RL-Frame so we can reset the trigger */
              TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
            }
          }
          else
          {
            /* #70 In case we received an invalid HS message, report the error to the user */
            TcpIp_TlsCoreCtHs_HandleInvalidHsMessage(TlsConIdx);
          }
        } /* else - no complete message received - nothing to do */
      } /* else - no record layer frame received - nothing to do */
    } /* else - async operation pending - nothing to do */
  } /* else - no handshake active on this connection - nothing to do */

} /* TcpIp_TlsCoreMainFunction_RxHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxAl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxAl(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process Rx AL function only if the current connection is in an active HS state or the TLS-Connections is established */
  if (  (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE)                 /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
     || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
  {
    if ((TcpIp_IsRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx) == TRUE))
    {
      /* #20 Check if we can forward the alert to the upper layer */
      if (TcpIp_TlsCoreCtAl_ForwardAlertToAlHandler(TlsConIdx) == E_OK)
      {
        /* #30 if so, we forward this message to the AL handler so reset the RL RxIndication flag */
        TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
      }
      else
      {
        /* #40 otherwise, no alert message received  - do nothing */
      }
    }
  }
} /* TcpIp_TlsCoreMainFunction_RxAl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_RxAd
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_RxAd(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the connection is established (Handshake done)  */
  if (   (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx) == TRUE))
  {
    /* #20 if so, forward the data to the upper layer */
    if (TcpIp_TlsCoreCtAd_ForwardDataToAdHandler(TlsConIdx) == E_OK)
    {
      /* #30 We processed this messaged so reset the RL RxIndication flag */
      TcpIp_SetRlRxIndicationFlagOfTlsConnectionDyn(TlsConIdx, FALSE);
    }
    else
    {
      /* otherwise - no AD data received - do nothing */
    }
  }
} /* TcpIp_TlsCoreMainFunction_RxAd() */

/**********************************************************************************************************************
 *  TLS CORE MAIN FUNCTION TX
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_TxHs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxHs(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process TX function only if we are in an active TLS handshake state */
  if (   ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE)
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
      /* HS finalizing is also an active Hs state */
      || ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING)   /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
# endif
    )
  {
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
    {
      /* Connection is configured as TLS Server */
      /* #20 Forward processing of TX messages to TLS Server */
      TcpIp_TlsServerTx_ForwardProcessedHsMsgToRl(TlsConIdx);
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Connection is configured as TLS Client */
      /* #30 Forward processing of TX messages to TLS Client */
      TcpIp_TlsClientTx_ForwardProcessedHsMsgToRl(TlsConIdx);
    }
# endif
  }
} /* TcpIp_TlsCoreMainFunction_TxHs() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_TxAl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxAl(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_TlsConnectionState activeConnectionState = TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process TX Alert function if the current Tls connection is in a valid state */
  if (   (TcpIp_IsTxAlertTriggerOfTlsConnectionDyn(TlsConIdx) == TRUE)
      && (  /* Alert can be triggered when connection is established */
              ((activeConnectionState == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
           /* Alert can be triggered when Hs is active */
           || (activeConnectionState == TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE))
            /* Alert can be triggered when TLS connection is waiting to close */
           || (activeConnectionState == TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT)))
  {
    /* Forward the TX to the internal function */
    TcpIp_TlsCoreCtAl_TxAlert(TlsConIdx);
  }
} /* TcpIp_TlsCoreMainFunction_TxAl() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_TxAd
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxAd(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the state of the TLS connection */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
  {
    TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
    TcpIp_TlsBufferTxAdHsReadIdxOfTlsBufferMgmtDynType txAdHsReadIdx
      = TcpIp_GetTlsBufferTxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

    TcpIp_SizeOfTlsBufferTxType applicationDataFillLvl = TcpIp_GetAdTxFillLevelOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);

    /* #20 if the TLS connection is established, check if there is new data to be transmitted */

    if (applicationDataFillLvl != 0u)
    {
      /* #30 If there is data in the transmit buffer, forward the data to the record layer */
      if (TcpIp_TlsCoreRl_Transmit(TlsConIdx, txAdHsReadIdx, applicationDataFillLvl, TCPIP_TLS_CT_AD) == E_OK)
      {
        /* #40 Increment the ReadIdx of the TX Buffer under consideration of the wraparound */
        TcpIp_TlsCoreRl_IncrementTlsBufferTxAdHsReadIdxWithWraparound(TlsConIdx, applicationDataFillLvl);
      }
    }
    /* #50 else - otherwise no AD data to transmit */
  }
  /* #60  else - otherwise no connection is established, nothing to do */
} /* TcpIp_TlsCoreMainFunction_TxAd() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_TxCcs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_TxCcs(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Depending on the type of connection, trigger sending of CCS message */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
  {
    /* Mode == TCPIP_TLS_SERVER */
    TcpIp_TlsServerConnectionIterType tlsServerConIdx = TcpIp_GetTlsServerConnectionIdxOfTlsConnection(TlsConIdx);

    /* Trigger sending CCS, if the flag is set */
    if (TcpIp_IsChangeCipherSpecReadyToSendOfTlsServerConnection(tlsServerConIdx) == TRUE)
    {
      TcpIp_TlsServerTx_SendChangeCipherSpec(TlsConIdx);
      /* Reset the Sequence counter */
      TcpIp_SetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx, 0);
    }
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    TcpIp_TlsClientConnectionIterType tlsClientConIdx = TcpIp_GetTlsClientConnectionIdxOfTlsConnection(TlsConIdx);

    /* Trigger sending CCS, if the flag is set */
    if (TcpIp_IsChangeCipherSpecReadyToSendOfTlsClientConnection(tlsClientConIdx) == TRUE)
    {
      TcpIp_TlsClientTx_SendChangeCipherSpec(TlsConIdx);
      /* Reset the Sequence counter */
      TcpIp_SetRlTxSequenceCounterOfTlsConnectionDyn(TlsConIdx, 0);
    }
  }
# endif
} /* TcpIp_TlsCoreMainFunction_TxCcs() */

/**********************************************************************************************************************
 *  TLS CORE STATES AND EVENTS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreEvent_TcpIpEventForwarding
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpIpEventForwarding(
  TcpIp_SocketDynIterType SocketIdx,
  IpBase_TcpIpEventType   Event)
{
  /* ----- Local Variables ---------------------------------------------- */
   TcpIp_TlsConnectionIterType tlsConIdx = TcpIp_GetSizeOfTlsConnection();

  /* ----- Implementation ----------------------------------------------- */
  /* This function only "stores" the received Events. The handling is done in TcpIp_TlsCore_MainFunction_State */
  /* #10 Set the given TCP Event in the corresponding TLS connection identified by the given socket ID */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
    switch(Event)
    {
     case IPBASE_TCP_EVENT_RESET:
     {
       TcpIp_TlsCoreEvent_TcpEventReset(tlsConIdx);
       break;
     } /* case IPBASE_TCP_EVENT_RESET */

     case IPBASE_TCP_EVENT_CLOSED:
     {
       TcpIp_TlsCoreEvent_TcpEventClosed(tlsConIdx);
       break;
     } /* case IPBASE_TCP_EVENT_CLOSED */

     case IPBASE_TCP_EVENT_FIN_RECEIVED:
     {
       TcpIp_TlsCoreEvent_TcpEventFinReceived(tlsConIdx);
       break;
     } /* case IPBASE_TCP_EVENT_FIN_RECEIVED */

     default:
     {
       /* do nothing */
       break;
     } /* default */
    } /* switch() */
  }
} /* TcpIp_TlsCoreEvent_TcpIpEventForwarding() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreEvent_TcpEventReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventReset(
TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the socket owner triggered a TCP RST (TcpIp_Close with Abort set to TRUE) and change the state */
  if (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_USER_RESET_WAIT)
  {
    /* In the state USER_RESET_WAIT the user is already informed about the received RST, therefore set the state to inactive */
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE);
  }
  else
  {
    /* else, we received and RST which must be processed */
    /* Check the mode of the TLS connection */
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* TLS-Client - The RST can be forwarded to the upper layer */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED);
    }
    else
    {
      /* TLS-Server - The RST can only be forwarded if the TLS connection is established */
      if (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
      {
        /* TLS connection established - Inform upper layer over RST */
        TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED);
      }
      else
      {
        /* TLS handshake active - Do not inform upper layer over RST */
        TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
          TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING);
      }
    }
  }
} /* TcpIp_TlsCoreEvent_TcpEventReset() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreEvent_TcpEventClosed
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventClosed(
TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType         socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 TLS received CLOSED event from TcpIp - Forward the event depending on the connection mode and state (Server/Client) */
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
  {
    /* TLS-Server */

    if (    (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE)
         || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING)
         || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_CLOSING_WITHOUT_UPPERLAYER_EVENT_FORWARDING)
         || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING)
         || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CLOSED))
    {
      /* TLS handshake is active - Upper layer MUST not be informed about received CLOSED event */
      /* Silently discard the event */
    }
    else
    {
      /* TLS connection is established - Upper layer should be informed about received CLOSED event */
      TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_CLOSED);
    }
  }
  else
  {
    /* TLS-Client - Upper layer should be informed about received CLOSED event */
    TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_CLOSED);
  }


  /* #20 TLS connection is CLOSED - Reset the connection and mark it as unused */
  TcpIp_TlsCore_ResetConnection(TlsConIdx);

  /* Mark the TLS Connection as unused */
  TcpIp_SetSocketDynListenIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNLISTENIDXOFTLSCONNECTIONDYN);
  TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN);

  /* Set the state to CLOSED */
  TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSED);

  TCPIP_VLEAVE_CRITICAL_SECTION();

} /* TcpIp_TlsCoreEvent_TcpEventClosed() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreEvent_TcpEventFinReceived
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpEventFinReceived(
TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType  socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 TLS-Server/TLS-Client connection is already established - User should decide how to proceed */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
  {
    /* TLS connections is already established, the user should decide how to proceed (either trigger FIN or RST) */
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT);
  }
  /* #20 TLS-Server/TLS-Client connection is already waiting for user action */
  else if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT))
  {
    /* This state could be reached when we received a CloseNotify alert - Do nothing just wait */
  }
  /* #30 TLS-Server/TLS-Client handshake is active */
  else
  {
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
    {
      /* TLS-Server during handshake - Close the TCP connection, but do NOT inform the upper layer */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
        TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING);
    }
    else
    {
      /* TLS-Client during handshake - Close the TCP connection, and inform the upper layer */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
        TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED);
    }
  }


  /* #40 Check if the received FIN event should be forwarded to the upper layer */
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
  {
    if (  (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)
       || (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT))
    {
      /* TLS Server should forward the event only if the connection is established */
      TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);
    }
    /* else - TLS handshake on Server active - Do not forward the event */
  }
  else
  {
    /* TLS Client should forward the event */
    TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);
  }

} /* TcpIp_TlsCoreEvent_TcpEventFinReceived() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreEvent_TcpIpEventClose
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpIpEventClose(
  TcpIp_SocketDynIterType SocketIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* Enter critical section */
  TCPIP_VENTER_CRITICAL_SECTION();


  {
    TcpIp_TlsConnectionIterType tlsConIdx;
    /* The actual closing of the connection is done within TcpIp_TlsCoreState_<>EventHandler() */
    /* #10 The close request is on an active socket, check if there is an active TLS connection and update the TLS state */
    if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
    {
      if (Abort == TRUE)
      {
        /* User wants so send RST */
        TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_USER_RESET_REQUESTED);
      }
      else
      {
        /* Check the current status of the TLS connection */
        if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ESTABLISHED)           /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          || (TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) == TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT))
        {
          /* TLS handshake is already done - we should trigger the CloseNotify */
          /* Triggers CloseNotify */
          TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx,
            TCPIP_TLS_STATE_CONNECTION_CLOSE_WITH_CLOSENOTIFY_REQUESTED);
        }
        else
        {
          /* TLS connection is during TLS handshake - no CloseNotify is sent */
          /* Triggers gracefully TCP Close */
          TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx,
            TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED);
        }

      }
    }
  }
  /* Leave critical section */
  TCPIP_VLEAVE_CRITICAL_SECTION();

} /* TcpIp_TlsCoreEvent_TcpIpEventClose() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_ModuleHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_UserEventHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* User<EVENT>Handler:  Handles events which are triggered from UpperLayer (User) */
  /* Tcp<EVENT>Handler:   Handles events which are triggered from LowerLayer (Tcp) */

  /* #10 Handle User close requests */
  TcpIp_TlsCoreConState_UserCloseRequestedHandler(TlsConIdx);

  /* #20 Handle User reset requests */
  TcpIp_TlsCoreConState_UserResetRequestedHandler(TlsConIdx);
} /* TcpIp_TlsCoreState_ModuleHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_HandshakeHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_HandshakeHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Process the TLS handshake state machine depending on the TLS-Connection Mode (Server/Client) */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
  {
    /* Connection is configured as TLS-Server */
    TcpIp_TlsServer_ProcessHandshake(TlsConIdx);
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Connection is configured as TLS-Client */
    TcpIp_TlsClient_ProcessHandshake(TlsConIdx);
  }
# endif
} /* TcpIp_TlsCoreState_HandshakeHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_TcpEventHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_TcpEventHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* User<EVENT>Handler:  Handles events which are triggered from UpperLayer (User) */
  /* Tcp<EVENT>Handler:   Handles events which are triggered from LowerLayer (Tcp) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle TCP close requests */
  TcpIp_TlsCoreConState_TcpCloseRequestedHandler(TlsConIdx);

  /* #20 Handle TCP reset requests */
  TcpIp_TlsCoreConState_TcpResetRequestedHandler(TlsConIdx);

} /* TcpIp_TlsCoreState_TcpEventHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_UserErrorHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_UserErrorHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorBufferWriteIdxOfTlsConnectionDynType tlsUserErrorBufferWriteIdx =
                                                       TcpIp_GetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TlsUserErrorBufferStartIdxOfTlsConnectionType tlsUserErrorBufferStartIdx =
                                                       TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Notify upper layer if user error buffer is not empty. */
  if (tlsUserErrorBufferWriteIdx != tlsUserErrorBufferStartIdx)
  {
    TcpIp_TlsCoreError_UserErrorCallout(TlsConIdx);
  }
} /* TcpIp_TlsCoreState_UserErrorHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_AlertHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_AlertHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we received an Alert */
  if (TcpIp_IsAlRxIndicationOfTlsConnectionDyn(TlsConIdx) == TRUE)
  {
    /* #20 if so, parse the Alert content */
    TcpIp_TlsCoreCtAl_ParseReceivedAlert(TlsConIdx);

    /* #30 Reset the AL RxIndication */
    TcpIp_SetAlRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
} /* TcpIp_TlsCoreState_AlertHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreState_ApplicationDataHandler
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreState_ApplicationDataHandler(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  /* Write index of the TLS Rx AdHs buffer */
  TcpIp_TlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDynType rxAdHsWriteIdx  = TcpIp_GetTlsBufferRxAdHsWriteIdxOfTlsBufferMgmtDyn(
                                                                          tlsBufferMgmtIdx);
  /* End index of the TLS Rx AdHs buffer */
  TcpIp_TlsBufferTxAdHsEndIdxOfTlsBufferMgmtType rxAdHsEndIdx = TcpIp_GetTlsBufferRxAdHsCurrEndIdxOfTlsBufferMgmtDyn(
                                                                  tlsBufferMgmtIdx);
  /* Start index of the TLS Rx AdHs buffer */
  TcpIp_TlsBufferTxAdHsStartIdxOfTlsBufferMgmtType rxAdHsStartIdx = TcpIp_GetTlsBufferRxAdHsStartIdxOfTlsBufferMgmt(
                                                                      tlsBufferMgmtIdx);
  /* Position of unforwarded data in TLS Rx AdHs buffer */
  TcpIp_TlsBufferRxUlRxIndIdxOfTlsBufferMgmtDynType rxUlRxIndIdx = TcpIp_GetTlsBufferRxUlRxIndIdxOfTlsBufferMgmtDyn(
                                                                               tlsBufferMgmtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if this TLS connection is already established */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ESTABLISHED))
  {
    /* #20 Check if there is new data in TLS Rx AdHs buffer to forward to Ul */
    /* this flag is only set if the UL Rxindication fill level is not 0 */
    if (TcpIp_IsAdRxIndicationOfTlsConnectionDyn(TlsConIdx) == TRUE)
    {
      /* TLS Ad RxIndication flag is set - This means there is new unforwarded data in the TLS Rx AdHs buffer */
      /* #30 Depending on the UlRxIndication index, forward unforwarded data to the upper layer */
      if (rxUlRxIndIdx < rxAdHsWriteIdx)
      {
        /* Data is linearized in the TLS Rx AdHs buffer, trigger Ul RxIndication call */
        uint32 unforwardedDataLen = ((uint32)rxAdHsWriteIdx - rxUlRxIndIdx);
        TcpIp_TlsCoreUl_RxIndication(TlsConIdx, TcpIp_GetAddrTlsBufferRx(rxUlRxIndIdx), unforwardedDataLen);

        /* Decrement RxIndication fill level with the total length of forwarded data */
        TcpIp_SubAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_SizeOfTlsBufferTxType)unforwardedDataLen);
      }
      else /* (rxUlRxIndIdx > rxAdHsWriteIdx) */
      {
        /* Data in Tls Rx AdHs buffer has wrapped around, trigger Ul RxIndication calls */
        uint32 unforwardedDataLenAtBufferEnd = ((uint32)rxAdHsEndIdx - rxUlRxIndIdx);
        uint32 unforwardedDataLenAtBufferFront = ((uint32)rxAdHsWriteIdx - rxAdHsStartIdx);

        /* Invoked UL Rx indication for data at the end, if present */
        if (unforwardedDataLenAtBufferEnd != 0u)
        {
          TcpIp_TlsCoreUl_RxIndication(TlsConIdx, TcpIp_GetAddrTlsBufferRx(rxUlRxIndIdx), (TcpIp_SizeOfTlsBufferTxType)unforwardedDataLenAtBufferEnd);
        }

        /* Invoked UL Rx indication for data at the beginning, if present */
        if (unforwardedDataLenAtBufferFront != 0u)
        {
          TcpIp_TlsCoreUl_RxIndication(TlsConIdx, TcpIp_GetAddrTlsBufferRx(rxAdHsStartIdx), unforwardedDataLenAtBufferFront);
        }

        /* Decrement RxIndication fill level with the total length of forwarded data */
        TcpIp_SubAdUlRxIndLvlOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TcpIp_SizeOfTlsBufferTxType)(unforwardedDataLenAtBufferEnd + unforwardedDataLenAtBufferFront));
      }
      /* Set Ad RxIndication flag to false, since all new data has been forwarded to Ul */
      TcpIp_SetAdRxIndicationOfTlsConnectionDyn(TlsConIdx, FALSE);
    }
  }
} /* TcpIp_TlsCoreState_ApplicationDataHandler() */

/**********************************************************************************************************************
 *  TLS CONNECTION STATE HANDLER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_CloseRequestedHandler
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_TcpCloseRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 TLS connection closing WITH upper layer information */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED))
  {
    /* #20 Check if there is any async operation pending and handle the close request */
    if (   (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC)                            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE))
    {

      /* Call close for corresponding underlying TCP socket */
      TcpIp_Tls_CloseInternal(TlsConIdx);

      /* Reset of the connection is done when the CLOSED event is received */
      /* Finally set the connection state to CLOSING */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSING);
    }
    else
    {
      /* #30 An async operation is pending, wait for this function to finish */
    }
  }

  /* #40 TLS connection closing WITHOUT upper layer information (TLS-Server during handshake) */
  else if (    (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx))
            == (TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING))
  {
    /* #50 Check if there is any async operation pending and handle the close request */
    if (    (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC)                           /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
         || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE))
    {

      /* Call close for corresponding underlying TCP socket */
      TcpIp_Tls_CloseInternal(TlsConIdx);

      /* Finally set the connection state to CLOSING but do not forward the Event to the upper layer */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx,
        TCPIP_TLS_STATE_CONNECTION_CLOSING_WITHOUT_UPPERLAYER_EVENT_FORWARDING);
    }
    else
    {
      /* #60 An async operation is pending, wait for this function to finish */
    }
  }
  else
  {
    /* nothing to do - left blank intentionally */
  }
} /* TcpIp_TlsCoreConState_CloseRequestedHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_TcpResetRequestedHandler
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_TcpResetRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is any async operation pending */
  if (   (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC)                              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE))
  {
    /* #20 No async operation pending - process the RST */

    /* #30 Check if the RST event should be forwarded to the upper layer */
    if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED))
    {
      /* #40 Upper layer should be informed - Reset the connection, trigger event callout function and set the connection state to CLOSED */
      TcpIp_SizeOfSocketDynType socketIdx = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);
      TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfTlsConnectionDyn(TlsConIdx);

      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSED);

      /* Reset the TLS connection */
      TcpIp_TlsCore_ResetConnection(TlsConIdx);

      /* Inform <UpperLayer> Socket Owner over RST event */
      TcpIp_Tls_TcpIpEventCallout(socketOwnerCfgIdx, socketIdx, IPBASE_TCP_EVENT_RESET);
    }
    else if (   (TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx))
             == (TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING))
    {
      /* #50 Upper layer should NOT be informed (TLS-Server during handshake) - Reset the connection and set the connection state to CLOSED */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSED);

      /* Reset the TLS connection */
      TcpIp_TlsCore_ResetConnection(TlsConIdx);
    }
    else
    {
      /* nothing to do - left blank intentionally */
    }
  } /* else - Async operation pending. Do nothing, just wait one cycle */
} /* TcpIp_TlsCoreConState_ServerResetRequestedHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_UserResetRequestedHandler
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
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_UserResetRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynComIdxOfTlsConnectionDynType socketIdx
    = TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is any async operation pending */
  if (   (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_NO_ASYNC)                              /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      || (TcpIp_GetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx) == TCPIP_TLS_CTX_DONE))
  {
    /* #20 No async operation pending - process the User RST */

    /* #30 Check if the upper layer (User) wants to RST the connection */
    /* TcpIp_Close(Abort=TRUE) on active TLS connection, either TLS-Server or TLS-Client */
    if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_USER_RESET_REQUESTED))
    {
      /* #40 Handle upper layer (User) RST on active TLS connection, reset the TLS connection and close the TCP socket */
      /* We have to wait until the RST is sent (and then get informed by Tcp) via event forwarding */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_USER_RESET_WAIT);

      TcpIp_TlsCore_ResetConnection(TlsConIdx);
      TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(TlsConIdx, TCPIP_NO_SOCKETDYNCOMIDXOFTLSCONNECTIONDYN);

      /* TLS connection already reset, so TCP will handle the RST and forward the event to the upper layer */
      TcpIp_CloseTcpSocketFromTls(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), TRUE);
    }

    /* #50 Process forwarding of TLS handshake cancellation (RST) from TLS-Listener */
    /* TcpIp_Close(Abort=TRUE) on active TLS handshake, TLS-Server */
    else if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CANCLED))
    {
      /* #60 TLS handshake active - Close the TCP socket with RST */
      TcpIp_CloseTcpSocketFromTls(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), TRUE);
    }
    /* #70 Process forwarding of TLS handshake closing (FIN) from TLS-Listener */
    /* TcpIp_Close(Abort=FALSE) on active TLS handshake, TLS-Server */
    else if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CLOSED))
    {
      /* #80 TLS handshake active - Close the TCP socket with FIN */
      TcpIp_CloseTcpSocketFromTls(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx), FALSE);
    }
    else
    {
      /* nothing to do - left blank intentionally */
    }
  } /* else - Async operation pending. Do nothing, just wait one cycle */
} /* TcpIp_TlsCoreConState_UserResetRequestedHandler() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConState_UserCloseRequestedHandler
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConState_UserCloseRequestedHandler(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if we should trigger the transmit of the CloseNotify */
  if ((TcpIp_GetConnectionStateOfTlsConnectionDyn(TlsConIdx)) == (TCPIP_TLS_STATE_CONNECTION_CLOSE_WITH_CLOSENOTIFY_REQUESTED))
  {
    /* #20 Trigger a CloseNotify alert and set the connection state to TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_WARNING, TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY);

    /* State TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT is used to transmit the CloseNoftify Alert (in MainFunction_TxAl).
       After the transmit, the state is changed to CLOSE_REQUESTED, where the FIN is triggered. */
    TcpIp_SetConnectionStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT);
  }

} /* TcpIp_TlsCoreConState_UserCloseRequestedHandler() */

/**********************************************************************************************************************
 *  TLS CORE ERROR
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_Init(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call function to clear User error buffer. */
  TcpIp_TlsCoreError_ClearUserError(TlsConIdx);

} /* TcpIp_TlsCoreError_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_ReportUserError
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
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_ReportUserError(
  CONST(TcpIp_TlsUserErrorType, AUTOMATIC) UserError)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section */
  TCPIP_VENTER_CRITICAL_SECTION();

  tlsConIdx = TCPIP_TLS_CONNECTION_ID_TO_IDX(UserError.TlsConId);
  /* #20 Verify if User Error Reporting is configured. */
  if (TcpIp_GetTlsUserErrorCalloutFunctionOfTlsConfig(TCPIP_TLSCONFIG_IDX) != NULL_PTR)
  {
    /* #30 Verify if buffer is full. */
    if (   TcpIp_GetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(tlsConIdx)
        == TcpIp_GetTlsUserErrorBufferEndIdxOfTlsConnection(tlsConIdx))
    {
      /* Error buffer is full, just return */
    }
    /* #40 Otherwise: Write User error into Buffer. */
    else
    {
      TcpIp_SetTlsUserErrorBuffer(TcpIp_GetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(tlsConIdx), UserError);
      TcpIp_IncTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(tlsConIdx);
      CANOE_WRITE_STRING_3("[User Error Report] FunctionId: 0x%x - ErrorId: 0x%x - TlsConIdx: %d", UserError.FunctionId,
                           UserError.UserErrorId, TCPIP_TLS_CONNECTION_ID_TO_IDX(UserError.TlsConId));
    }
  }

  /* #50 Leave critical section */
  TCPIP_VLEAVE_CRITICAL_SECTION();

} /* TcpIp_TlsCoreError_ReportUserError() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_GetUserError
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreError_GetUserError(
  TcpIp_TlsConnectionIterType        TlsConIdx,
  TCPIP_P2V(TcpIp_TlsUserErrorType)  UserErrorMemoryPtr,
  TCPIP_P2V(uint32)                  NumOfUserErrorPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorBufferIterType errorBufferIdx;
  TcpIp_TlsUserErrorBufferIterType writeErrorBufferIdx = 0;
  uint32 userErrorsToBeRead;
  TCPIP_P2C(TcpIp_TlsUserErrorType) userErrorBufferPtr;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify if user error reporting is configured. */
  if (TcpIp_GetTlsUserErrorCalloutFunctionOfTlsConfig(TCPIP_TLSCONFIG_IDX) != NULL_PTR)
  {
    /* #20 Calculate length of buffer. */
    userErrorsToBeRead = ((uint32)TcpIp_GetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(TlsConIdx)
      - TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx));
    /* #30 Verify the number of user error entries that should be read. */
    if (*NumOfUserErrorPtr < userErrorsToBeRead)
    {
      /* Only a part of the user errors can be read, since not enough buffer is provided by the requester. */
      userErrorsToBeRead = *NumOfUserErrorPtr;
    }
    else
    {
      *NumOfUserErrorPtr = userErrorsToBeRead;
    }
    /* #40 Write User error entries into the given user buffer. */
    for (errorBufferIdx = TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx);
         errorBufferIdx < (TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx) + userErrorsToBeRead);
         errorBufferIdx++)
    {
      userErrorBufferPtr = TcpIp_GetAddrTlsUserErrorBuffer(errorBufferIdx);

      UserErrorMemoryPtr[writeErrorBufferIdx].FunctionId = userErrorBufferPtr->FunctionId;
      UserErrorMemoryPtr[writeErrorBufferIdx].UserErrorId = userErrorBufferPtr->UserErrorId;
      writeErrorBufferIdx++;
    }
    /* #50 Clear the whole buffer. */
    TcpIp_TlsCoreError_ClearUserError(TlsConIdx);
    retVal = E_OK;
  }


  return retVal;
} /* TcpIp_TlsCoreError_GetUserError() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_ClearUserError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_ClearUserError(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorBufferPtrType userErrorEntryPtr;
  TcpIp_TlsUserErrorBufferIterType errorBufferIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over whole user error buffer and clear each element of the buffer. */
  for (errorBufferIdx = TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx);
       errorBufferIdx < TcpIp_GetTlsUserErrorBufferEndIdxOfTlsConnection(TlsConIdx);
       errorBufferIdx++)
  {
    userErrorEntryPtr = TcpIp_GetAddrTlsUserErrorBuffer(errorBufferIdx);

    userErrorEntryPtr->FunctionId = 0;
    userErrorEntryPtr->UserErrorId = 0;
  }
  /* #20 Clear Write index of User error buffer. */
  TcpIp_SetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(TlsConIdx, TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx));
} /* TcpIp_TlsCoreError_ClearUserError() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_UserErrorCallout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_UserErrorCallout(TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorCalloutFunctionType funcPtr;
  TcpIp_SizeOfTlsUserErrorBufferType userErrorCnt;

  /* ----- Implementation ----------------------------------------------- */
  funcPtr = TcpIp_GetTlsUserErrorCalloutFunctionOfTlsConfig(TCPIP_TLSCONFIG_IDX);

  /* #10 Calculate the number of user error entries saved in user error buffer. */
  userErrorCnt = (TcpIp_GetTlsUserErrorBufferWriteIdxOfTlsConnectionDyn(TlsConIdx)
                  - TcpIp_GetTlsUserErrorBufferStartIdxOfTlsConnection(TlsConIdx));
  /* #20 Notify upper layer to read user errors saved in user error buffer, if callout is configured. */
  if (funcPtr != NULL_PTR)
  {
    funcPtr((uint32) TlsConIdx, userErrorCnt);
  }
} /* TcpIp_TlsCoreError_UserErrorCallout() */

/**********************************************************************************************************************
 *  TLS CORE CRYPTO
 *********************************************************************************************************************/
# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
*  TcpIp_TlsCoreCrypto_ReduceSharedKey
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_ReduceSharedKey(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_TlsCsmKeyInfoType tmpKey; /* Temporary CSM key element */
  TcpIp_TlsCsmKeyInfoType pmsKey; /* Pre-master secret CSM key element (DH-Shared Value) */
  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the necessary keys for the MasterSecret operation are configured */
  if (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {
    tmpKey.KeyId        = TcpIp_GetHsTemporaryBufferKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
    tmpKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
    tmpKey.KeyLen       = 0;

    pmsKey.KeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeIdxOfTlsHandshake(activeTlsHandshakeIdx)];
    pmsKey.KeyElementId = CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE;
    pmsKey.KeyLen       = TCPIP_TLS_PREMASTERSECRET_COORDINATE_SIZE;

    /* Reduce Key */
    /* Clear dummy buffer, set one dummy byte to reduce the length (CSM cannot delete a key) */

    csmRetVal = TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, &tmpKey);
    /* Copy pre-master-secret to the dummy buffer */
    csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(pmsKey.KeyId, pmsKey.KeyElementId, 0, 0, pmsKey.KeyLen, tmpKey.KeyId, tmpKey.KeyElementId);
    csmRetVal |= TCPIP_CSM_KeySetValid(tmpKey.KeyId);

    /* Copy back the reduced key */
    csmRetVal |= TCPIP_CSM_KeyElementCopy(tmpKey.KeyId, tmpKey.KeyElementId, pmsKey.KeyId, pmsKey.KeyElementId);
    csmRetVal |= TCPIP_CSM_KeySetValid(pmsKey.KeyId);

    /* #20 Check if the result of the CSM operation is E_OK */
    retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_REDUCEKEY);

    if (retVal != E_OK)
    {
      /* #30 if not so, report the user error */
      TcpIp_TlsUserErrorType userError;

      userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_REDUCEKEY;
      userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_REDUCESHAREDKEY_FAILED;
      userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(userError);
    }
  }
  else
  {
    /* #40 CSM Key for ReduceKey operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
    retVal = E_NOT_OK;
  }
  return retVal;
} /* TcpIp_TlsCoreCrypto_ReduceSharedKey() */
# endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcMasterSecret
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_TlsCsmKeyInfoType msKey; /* Master secret CSM key element */
  TcpIp_TlsCsmKeyInfoType pmsKey; /* Premaster secret CSM key element (DH-Shared Value) */
  uint8  seed[2u * TCPIP_TLS_RANDOM_LEN] = { 0 };
  uint8  seedLen = 2u * TCPIP_TLS_RANDOM_LEN;
  Std_ReturnType prfRetVal;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the necessary keys for the MasterSecret operation are configured */
  if (   (TcpIp_IsCsmKeyIdMasterSecretUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
      && (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx)   == TRUE))                              /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
  {

    msKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdMasterSecretIdxOfTlsHandshake(activeTlsHandshakeIdx)];
    msKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
    msKey.KeyLen = TCPIP_TLS_MASTER_SECRET_LEN;

    pmsKey.KeyId =  TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdKeyExchangeIdxOfTlsHandshake(activeTlsHandshakeIdx)];
    pmsKey.KeyElementId = CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE;


    /* #20 Copy client and server random into one array (seed) */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
    {
      /* Mode == TCPIP_TLS_SERVER */
      TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

      VStdMemCpy(&seed[0], TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)),/* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TCPIP_TLS_RANDOM_LEN);
      VStdMemCpy(&seed[TCPIP_TLS_RANDOM_LEN],                                                                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxServerRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

      VStdMemCpy(&seed[0], TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)),/* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TCPIP_TLS_RANDOM_LEN);
      VStdMemCpy(&seed[TCPIP_TLS_RANDOM_LEN],                                                                           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxServerRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);
    }
# endif

    /* Invoke the crypto PRF function to generate the master secret */
    prfRetVal = TcpIp_TlsCoreCrypto_Prf(TlsConIdx, &msKey, &pmsKey, &TcpIp_Tls_Hs_MasterSecretLabel[0], &seed[0],
      TCPIP_TLS_LABEL_MASTER_SECRET_LEN, seedLen, TRUE);

    /* #30 Check if the result of the CSM operation is E_OK */
    retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, prfRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALCMASTERSECRET);

    if (retVal != E_OK)
    {
      /* #40 if not so, report the user error */
      TcpIp_TlsUserErrorType userError;

      userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_CALCMASTERSECRET;
      userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_CALCMASTERSECRET_FAILED;
      userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(userError);
    }
  }
  else
  {
    /* #50 CSM Key for MasterSecret operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_CalcMasterSecret() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_DeriveKeyBlock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_DeriveKeyBlock(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the necessary KeyBlock size for this TLS-Connection */
  csmRetVal = TcpIp_TlsCoreCrypto_CalcKeyBlockSize(TlsConIdx);

  /* #20 Calculate the KeyBlock for this TLS-Connection */
  if (csmRetVal == E_OK)
  {
    csmRetVal = TcpIp_TlsCoreCrypto_CalcKeyBlock(TlsConIdx);
  }

  /* #30 Check the result of the CSM operation */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_DERIVEKEYBLOCK);

  return retVal;
} /* TcpIp_TlsCoreCrypto_DeriveKeyBlock() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_SetCsmKeys
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the configuration of the necessary CSM keys and CSM jobs is valid */
  if (TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration(TlsConIdx) == E_OK)
  {
    /* #20 If the configuration is valid, set the CSM Keys depending on the TLS-Connection mode (Server/Client) */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
    {
      /* Connection is configured as TLS-Server */
      retVal = TcpIp_TlsServerCrypto_SetCsmKeys(TlsConIdx);
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Connection is configured as TLS-Client */
      retVal = TcpIp_TlsClientCrypto_SetCsmKeys(TlsConIdx);
    }
# endif
  }
  else
  {
    /* #30 Handle invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
  }
  return retVal;
} /* TcpIp_TlsCoreCrypto_SetCsmKeys() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherStreamingModeDataType selectedStreamingMode = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(TlsConIdx);

  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx
    = TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx);

  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the connection generic CSM Keys */
  if ((TcpIp_IsCsmKeyIdMasterSecretUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)                                   /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    && (TcpIp_IsCsmKeyIdKeyExchangeUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE))
  {
    /* Generic CSM Keys are valid */
    retVal = E_OK;
  }

  if (retVal == E_OK)
  {
    /* #20 Check streaming depended CSM Key and CSM Jobs */
    switch (selectedStreamingMode)
    {
      case TCPIP_TLS_STREAMING_MODE_AES_128_CBC:
      {
        /* X_WITH_AES_128_CBC_SHAX
             TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
             TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
             TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
             TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
        */
        /* Check necessary CSM Key configuration */
        if ((TcpIp_IsCsmKeyIdHmacGenerateUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)   == TRUE)                     /* PRQA S 3415 8 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TcpIp_IsCsmKeyIdHmacVerifyUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)    == TRUE)
          && (TcpIp_IsCsmKeyIdCipherEncryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          && (TcpIp_IsCsmKeyIdCipherDecryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          /* Check necessary CSM Job configuration */
          && (TcpIp_IsCsmJobIdHmacGenerateUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)  == TRUE)
          && (TcpIp_IsCsmJobIdHmacVerifyUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)    == TRUE)
          && (TcpIp_IsCsmJobIdCipherEncryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          && (TcpIp_IsCsmJobIdCipherDecryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE))
        {
          retVal = E_OK;
        }
        break;
      } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

      case TCPIP_TLS_STREAMING_MODE_AES_128_GCM:
      {

        /* X_WITH_AES_128_GCM_SHAX
             TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA
             TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
             TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA
             TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
        */
        /* Check necessary CSM Key configuration */
        if ((TcpIp_IsCsmKeyIdCipherEncryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)  == TRUE)                     /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TcpIp_IsCsmKeyIdCipherDecryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          /* Check necessary CSM Job configuration */
          && (TcpIp_IsCsmJobIdCipherEncryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          && (TcpIp_IsCsmJobIdCipherDecryptUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE))
        {
          retVal = E_OK;
        }
        break;
      } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

      case TCPIP_TLS_STREAMING_MODE_NULL:
      {
        /* X_WITH_NULL_SHAX
             TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA
        */
        /* Check necessary CSM Key configuration */
        if ((TcpIp_IsCsmKeyIdHmacGenerateUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)  == TRUE)                      /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
          && (TcpIp_IsCsmKeyIdHmacVerifyUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)   == TRUE)
          /* Check necessary CSM Job configuration */
          && (TcpIp_IsCsmJobIdHmacGenerateUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx) == TRUE)
          && (TcpIp_IsCsmJobIdHmacVerifyUsedOfTlsCipherWorker(activeTlsCipherWorkerIdx)   == TRUE))
        {
          retVal = E_OK;
        }
        break;
      } /* case TCPIP_TLS_STREAMING_MODE_NULL */
      default:                                                                                                             /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
      {
        /* Default case left blank intentionally */
        break;
      }
    } /* switch */
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcKeyBlockSize
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcKeyBlockSize(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIterType activeTlsCipherWorkerIdx
    = TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsCipherStreamingModeDataType activeStreamingMode
    = TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(TlsConIdx);

  TcpIp_CipherMacKeyLengthOfTlsCipherWorkerType activeMacLength = TcpIp_GetCipherMacKeyLengthOfTlsCipherWorker(
        activeTlsCipherWorkerIdx);

  uint32 keyBlockSize   = TCPIP_TLS_KEY_BLOCK_SIZE_UNSET;                                                               /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the KeyBlock size depending on the active streaming mode of the connection */
  switch (activeStreamingMode)
  {
    case TCPIP_TLS_STREAMING_MODE_AES_128_CBC:
    {
      /* X_WITH_AES_128_CBC_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
      */
      if (activeMacLength == TCPIP_TLS_HASH_SHA256_LEN)
      {
        /* KeyBlock:
           * -  0..31: TX MAC
           * - 32..63: RX MAC
           * - 64..79: TX Key
           * - 80..95: RX Key
        */
        keyBlockSize = TCPIP_TLS_KEY_BLOCK_SIZE_AES128_SHA256;
        retVal = E_OK;
      }
      else
      {
        /* KeyBlock:
           * -  0..19: TX MAC
           * - 20..39: RX MAC
           * - 40..55: TX Key
           * - 56..71: RX Key
        */
        keyBlockSize = TCPIP_TLS_KEY_BLOCK_SIZE_AES128_SHA1;
        retVal = E_OK;
      }
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_CBC */

    case TCPIP_TLS_STREAMING_MODE_AES_128_GCM:
    {
      /* X_WITH_AES_128_GCM_SHAX
           TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
           TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA
           TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
      */
      {
        /* KeyBlock:
           * - 0..15: TX Key
           * - 16..31: RX Key
           * - 32..35: TX IV
           * - 36..39: RX IV
        */
        keyBlockSize = TCPIP_TLS_KEY_BLOCK_SIZE_AES128_GCM;
        retVal = E_OK;
      }

      break;
    } /* case TCPIP_TLS_STREAMING_MODE_AES_128_GCM */

    case TCPIP_TLS_STREAMING_MODE_NULL:
    {
      /* X_WITH_NULL_SHAX
           TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA
      */
      if (activeMacLength == TCPIP_TLS_HASH_SHA256_LEN)
      {
        /* KeyBlock:
           * -  0..31: TX MAC
           * - 32..63: RX MAC
        */
        keyBlockSize = TCPIP_TLS_KEY_BLOCK_SIZE_NULL_SHA256;
        retVal = E_OK;
      }
      else
      {
        /* KeyBlock:
           * -  0..19: TX MAC
           * - 20..39: RX MAC
        */
        keyBlockSize = TCPIP_TLS_KEY_BLOCK_SIZE_NULL_SHA1;
        retVal = E_OK;
      }
      break;
    } /* case TCPIP_TLS_STREAMING_MODE_NULL */

    default:                                                                                                           /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* Default case left blank intentionally */
    break;

  } /* switch */

  /* #20 Check if there was an error during the calculation */
  if (retVal != E_NOT_OK)
  {
    /* #30 if not safe the actual key block length */
    TcpIp_SetKeyBlockSizeOfTlsConnectionDyn(TlsConIdx, keyBlockSize);
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_CalcKeyBlockSize() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_Prf
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6060 1 */ /* MD_TcpIp_Tls_STPAR */
 FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_Prf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) ResultKeyIdPtr,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) SecretKeyIdPtr,
  TCPIP_P2C(uint8) LabelPtr,
  TCPIP_P2C(uint8) SeedPtr,
  uint8 LabelLen,
  uint8 SeedLen,
  boolean ResultIsPrivate)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 combinedLabel_Array[TCPIP_TLS_PRF_COMBINED_LABEL_LEN_MAX];
  uint8 combinedLabelLen = LabelLen + SeedLen;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Combine the label and seed, and invoke the pseudo-random function */
  if (combinedLabelLen > 0u)
  {
    VStdMemCpy(combinedLabel_Array, LabelPtr, LabelLen);                                                                /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    VStdMemCpy(&combinedLabel_Array[LabelLen], SeedPtr, SeedLen);                                                       /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

    /* PRF = P_SHA256(S, Label + seed) */
    retVal = TcpIp_TlsCoreCrypto_PSha256(TlsConIdx, ResultKeyIdPtr, SecretKeyIdPtr, &combinedLabel_Array[0],
               combinedLabelLen, ResultIsPrivate);
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_PSha256
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
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STPAR, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_PSha256(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) ResultKeyIdPtr,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) SecretKeyIdPtr,
  TCPIP_P2C(uint8) SeedPtr,
  uint16 SeedLen,
  boolean ResultIsPrivate)
{
  /* RFC5246 - Section 5.  HMAC and the Pseudorandom Function
   *
   *  In this section, we define one PRF, based on HMAC. This PRF with the
   *  SHA-256 hash function is used for all cipher suites, therefore P_hash() is P_SHA256().
   *
   *  P_hash(secret, seed) =   HMAC_hash(secret, A(1) + seed) +
   *                           HMAC_hash(secret, A(2) + seed) +
   *                           HMAC_hash(secret, A(3) + seed) + ...      (referenced as outer hash)
   *
   *  where + indicates concatenation.
   *
   *  A() is defined as:
   *
   *    A(0) = seed
   *    A(i) = HMAC_hash(secret, A(i-1))     (referenced as inner hash)
   */

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));


  uint32 keyElementIdInput   = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 keyElementIdOutput  = TcpIp_GetPrfValueOutputKeyElemendIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 keyElementIdActive  = TcpIp_GetPrfValueActiveKeyElemendIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 keyElementIdPassive = TcpIp_GetPrfValuePassiveKeyElemendIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 keyIdPrfSecret      = TcpIp_GetPrfSecreteKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  uint32 jobIdHmacGenerate;
  uint32 keyIdHmacGenerate;

  /* API TCPIP_CSM_MacGenerate() has a DET check on the in and out parameters, because it is specified by AUTOSAR.
   * However this check does not make sense in case the buffer is redirected to a key. Because of that a dummy
   * byte has to be provided.
   */
  uint8 dummyBuffer     = 0u;
  uint32 dummyBufferLen = 1u;
  boolean loopEnd       = FALSE;
  uint16 fillLevel      = 0u;
  Std_ReturnType csmRetVal;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Set the HMAC job/keys depending on the privacy of the result */
  if (ResultIsPrivate == TRUE)
  {
    /* Private result is used for calculation of MasterSecret and derivation of KeyBlock */
    jobIdHmacGenerate = TcpIp_GetPrfMacGeneratePrivateJobIdOfTlsHandshake(activeTlsHandshakeIdx);
    keyIdHmacGenerate = TcpIp_GetPrfMacCalculationPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  }
  else
  {
    /* Public result is used for calculation of FinishedMessages during TLS handshake */
    jobIdHmacGenerate = TcpIp_GetPrfMacGeneratePublicJobIdOfTlsHandshake(activeTlsHandshakeIdx);
    keyIdHmacGenerate = TcpIp_GetPrfMacCalculationPublicKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
  }

  /* Reset ResultKeyIdPtr, required because TCPIP_CSM_KeyElementCopyPartial does not shorten the length of the destination
   * key, it can only increment it. In case of multiple calculation with results having different lengths,
   * this is mandatory.
   */
  (void)TcpIp_TlsCoreCrypto_ClearCsmKey(TlsConIdx, ResultKeyIdPtr);

  /* Copy secret to the secret key */
  csmRetVal  = TCPIP_CSM_KeyElementCopy(SecretKeyIdPtr->KeyId, SecretKeyIdPtr->KeyElementId, keyIdPrfSecret, CRYPTO_KE_MAC_KEY);
  csmRetVal |= TCPIP_CSM_KeySetValid(keyIdPrfSecret);
  (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256);


  /* #20 Prepare A(0) with the seed */
  /* copy seed to the input key */
  {
    csmRetVal = TCPIP_CSM_KeyElementSet(keyIdHmacGenerate, keyElementIdInput, SeedPtr, SeedLen);
    csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
    (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256);
  } /* End of A(0) */

  /* #30 First run to calculate A(1) */
  /* init, update and finalize inner hash */
  {
    /* Generate HMAC to KeyIdOutput */
    csmRetVal  = TCPIP_CSM_MacGenerate(jobIdHmacGenerate, CRYPTO_OPERATIONMODE_SINGLECALL, &dummyBuffer, 0, &dummyBuffer, &dummyBufferLen);
    csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);

    /* Copy KeyIdOutput to keyIdActive */
    csmRetVal |= TCPIP_CSM_KeyElementCopy(keyIdHmacGenerate, keyElementIdOutput, keyIdHmacGenerate, keyElementIdActive);
    csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
    (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256);
  } /* End of A(1) */

  /* #40 Iterate until the required quantity of data is produced (fillLevel reached required KeyLen) */
  while(fillLevel < ResultKeyIdPtr->KeyLen)
  {
    /* #50 Switch active and passive elements - required for CSM redirect feature */
    {
      /* Switch keyIds */
      uint32 tmpKeyId     = keyElementIdActive;
      keyElementIdActive  = keyElementIdPassive;
      keyElementIdPassive = tmpKeyId;
    }

    /* #60 Init, update and finalize outer hash */
    {
      uint32 hsTempKeyId          = TcpIp_GetHsTemporaryBufferKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
      uint32 hsCommonKeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
      /* Using the redirection feature the HMAC has to be calculated within a single call, therefore the keyIdPassive
       * and the seed have to be copied to one input buffer.
       */
      csmRetVal  = TCPIP_CSM_KeyElementCopy(keyIdHmacGenerate, keyElementIdPassive, keyIdHmacGenerate,
                     keyElementIdInput);
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
      /* Set the seed to the CSM. CSM does not support a partially set, therefore it has to be set to a temporary key first */
      csmRetVal |= TCPIP_CSM_KeyElementSet(hsTempKeyId, hsCommonKeyElementId, SeedPtr, SeedLen);
      csmRetVal |= TCPIP_CSM_KeySetValid(hsTempKeyId);
      /* Copy seed to the input buffer after keyIdPassive */
      csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(hsTempKeyId, hsCommonKeyElementId, 0, TCPIP_TLS_HASH_SHA256_LEN, SeedLen,
                      keyIdHmacGenerate, keyElementIdInput );
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
      /* Generate HMAC to KeyIdOutput using CSM redirection feature */
      csmRetVal |= TCPIP_CSM_MacGenerate(jobIdHmacGenerate, CRYPTO_OPERATIONMODE_SINGLECALL, &dummyBuffer, 0, &dummyBuffer,
                     &dummyBufferLen);
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
    } /* End of outer hash */

    /* #70 Update the result pointer with the calculated values */
    /* write hash directly into ResultKeyIdPtr */
    {
      if (((uint32)fillLevel + TCPIP_TLS_HASH_SHA256_LEN) <= ResultKeyIdPtr->KeyLen)
      {
        /* Copy complete key */
        csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyIdHmacGenerate, keyElementIdOutput, 0, fillLevel,
          TCPIP_TLS_HASH_SHA256_LEN, ResultKeyIdPtr->KeyId, ResultKeyIdPtr->KeyElementId);
        csmRetVal |= TCPIP_CSM_KeySetValid(ResultKeyIdPtr->KeyId);
      }
      else
      {
        /* Copy only the last chunk */
        csmRetVal |= TCPIP_CSM_KeyElementCopyPartial(keyIdHmacGenerate, keyElementIdOutput, 0, fillLevel,
          (ResultKeyIdPtr->KeyLen - fillLevel), ResultKeyIdPtr->KeyId, ResultKeyIdPtr->KeyElementId);
        csmRetVal |= TCPIP_CSM_KeySetValid(ResultKeyIdPtr->KeyId);
        loopEnd = TRUE;
      }
      (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256);
    } /* End of result pointer update */

    /* #80 Check if we have to calculate another round A(i-1) */
    if (loopEnd == FALSE)
    {
      /* init, update and finalize inner hash for next run of the loop */
      /* Copy keyIdPassive to the input buffer  */
      csmRetVal  = TCPIP_CSM_KeyElementCopy(keyIdHmacGenerate, keyElementIdPassive, keyIdHmacGenerate, keyElementIdInput);
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
      /* Generate HMAC to KeyIdOutput: A(i-1) using CSM redirection feature */
      csmRetVal |= TCPIP_CSM_MacGenerate(jobIdHmacGenerate, CRYPTO_OPERATIONMODE_SINGLECALL, &dummyBuffer, 0, &dummyBuffer,
                     &dummyBufferLen);
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);

      /* Copy result to active buffer */
      csmRetVal |= TCPIP_CSM_KeyElementCopy(keyIdHmacGenerate, keyElementIdOutput, keyIdHmacGenerate, keyElementIdActive);
      csmRetVal |= TCPIP_CSM_KeySetValid(keyIdHmacGenerate);
      (void)TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256);
    }

    /* #90 Update the fill level by the consumed bytes */
    fillLevel += TCPIP_TLS_HASH_SHA256_LEN;

  } /* while() */

  return csmRetVal;
}

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcKeyBlock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 6050, 6060 1 */ /* MD_TcpIp_Tls_STPAR, MD_TcpIp_Tls_STCAL */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcKeyBlock(
  TcpIp_TlsConnectionIterType TlsConIdx )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 seed[2u * TCPIP_TLS_RANDOM_LEN];
  TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
    TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx));
  TcpIp_TlsCsmKeyInfoType msKey;
  TcpIp_TlsCsmKeyInfoType keyBlockKey;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /*
  RFC5246 6.3.  Key Calculation
  key_block = PRF( SecurityParameters.master_secret,
                   "key expansion",
                   SecurityParameters.server_random + SecurityParameters.client_random );
  */
  /* #10 Check if the necessary key for the CalKeyBlock operation is configured */
  if (TcpIp_IsCsmKeyIdMasterSecretUsedOfTlsHandshake(activeTlsHandshakeIdx) == TRUE)
  {
    msKey.KeyId = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdMasterSecretIdxOfTlsHandshake(activeTlsHandshakeIdx)];
    msKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
    msKey.KeyLen = TCPIP_TLS_MASTER_SECRET_LEN;

    keyBlockKey.KeyId = TcpIp_GetPrfResultPrivateKeyIdOfTlsHandshake(activeTlsHandshakeIdx);
    keyBlockKey.KeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
    keyBlockKey.KeyLen = TcpIp_GetKeyBlockSizeOfTlsConnectionDyn(TlsConIdx);

    /* #20 Copy server and client random into one array */
/*
[REVIEW_G] c_accepted 16.01.00.1
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
    {
      /* Mode == TCPIP_TLS_SERVER */
      TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx
        = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);

      VStdMemCpy((&seed[0]), TcpIp_GetAddrTlsBufferTx(                                                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetTlsBufferTxServerRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);
      VStdMemCpy((&seed[TCPIP_TLS_RANDOM_LEN]), TcpIp_GetAddrTlsBufferRx(                                               /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx
        = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);

      VStdMemCpy((&seed[0]), TcpIp_GetAddrTlsBufferRx(                                                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetTlsBufferRxServerRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);

      VStdMemCpy((&seed[TCPIP_TLS_RANDOM_LEN]), TcpIp_GetAddrTlsBufferTx(                                               /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx)),
        TCPIP_TLS_RANDOM_LEN);
    }
# endif

    /* #30 Calculate key block content */
    retVal = TcpIp_TlsCoreCrypto_Prf(TlsConIdx, &keyBlockKey, &msKey, (const uint8*)&TcpIp_Tls_Hs_KeyExpansionLabel[0],
      &seed[0], TCPIP_TLS_LABEL_KEY_EXPENSION_LEN, (2u * TCPIP_TLS_RANDOM_LEN), TRUE);

  }
  else
  {
    /* #40 CSM Key for CalKeyBlock operation is not configured - invalid configuration */
    TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(TlsConIdx);
    retVal = E_NOT_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_ClearCsmKey
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_ClearCsmKey(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) KeyPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;
  uint8 dummyBuffer = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear the given CSM Key */
  /* Set first byte of the key to 0. This is required because TCPIP_CSM_KeyElementCopyPartial does not shorten the
  *  length of the destination key, it can only increment it.
  */
  csmRetVal  = TCPIP_CSM_KeyElementSet(KeyPtr->KeyId, KeyPtr->KeyElementId, &dummyBuffer, 1);
  csmRetVal |= TCPIP_CSM_KeySetValid(KeyPtr->KeyId);

  /* #20 Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_CLEARCSMKEY);

  if (retVal != E_OK)
  {
    /* #30 if not so, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_CLEARCSMKEY;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_CLEARCSMKEY_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);
    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_ClearCsmKey() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_GenerateIvRandomValue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_GenerateIvRandomValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(uint8) IvPtr,
  CONST(uint8, AUTOMATIC) IvLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 tlsRandomJobId = TcpIp_GetTlsRandomGenerateCsmJobId();
  uint32 tmpIvLen = IvLen;
  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Generate a random value with the given length */
  csmRetVal = TCPIP_CSM_RandomGenerate(tlsRandomJobId, IvPtr, &tmpIvLen);

  /* #20 Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, tmpIvLen, IvLen, TCPIP_TLS_FCTID_CORE_CRYPTO_GENERATEIVRANDOM);

  if (retVal != E_OK)
  {
    /* #30 if not so, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_GENERATEIVRANDOM;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_GENERATEIVRANDOM_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;

} /* TcpIp_TlsCoreCrypto_GenerateIvRandomValue() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_SetAesIvValue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_SetIvValue(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(uint32, AUTOMATIC) IvKeyElementId,
  TCPIP_P2C(uint8) IvPtr,
  CONST(uint8, AUTOMATIC) IvLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType csmRetVal;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the given IV to the given CSM Key */
  csmRetVal  = TCPIP_CSM_KeyElementSet(IvKeyElementId, CRYPTO_KE_CIPHER_IV, IvPtr, (uint32)IvLen);
  csmRetVal |= TCPIP_CSM_KeySetValid(IvKeyElementId);

  /* #20 Check if the result of the CSM operation is E_OK */
  retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, 0, 0, TCPIP_TLS_FCTID_CORE_CRYPTO_SETAESIVVALUE);

  if (retVal != E_OK)
  {
    /* #30 if not so, report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = TCPIP_TLS_FCTID_CORE_CRYPTO_SETAESIVVALUE;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_SETAESIVVALUE_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_SetIvValue() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CheckCsmResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CheckCsmResult(
  TcpIp_TlsConnectionIterType TlsConIdx,
  Std_ReturnType CsmRetVal,
  uint32 CsmResultLength,
  uint32 ExpectedResultLength,
  TcpIp_TlsFunctionIdType ApiId)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorIdType errorID = TCPIP_TLS_ERRORID_NOT_SET;                                                         /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check CSM return value and set the errorId */
  if (CsmRetVal == E_OK)
  {
    /* if E_OK, check if the CSM Call return length is the expected length */
    if (CsmResultLength == ExpectedResultLength)
    {
      /* Set retVal to E_OK */
      retVal = E_OK;
    }
    else
    {
      /* set the user error code to length mismatch */
      errorID = TCPIP_TLS_ERRORID_CRYPTO_CSM_LEN_MISMATCH;
    }
  }
  else
  {
    /* set the user error code to call failed */
    errorID = TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED;
  }

  /* #20 Report user error if necessary */
  if (retVal != E_OK)
  {
    /* report the user error */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = ApiId;
    userError.UserErrorId = errorID;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsCoreCrypto_CheckCsmResult() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_HandleInvalidConfiguration
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType invalidCfgUserError;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger an 'internal' alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_INT_ERROR);

  /* #20 Report the error to the user */
  invalidCfgUserError.FunctionId = TCPIP_TLS_FCTID_INVALID_CONFIG;
  invalidCfgUserError.UserErrorId = TCPIP_TLS_ERRORID_INVALID_CONFIG;
  invalidCfgUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  TcpIp_TlsCoreError_ReportUserError(invalidCfgUserError);


  /* #30 Change the state to TLS handshake abort */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

  /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report a DET error if configured. */
  (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID,
    TCPIP_TLS_API_ID_TLS_INV_CONFIG, TCPIP_TLS_E_INV_CONFIG);
# endif

} /* TcpIp_TlsCoreCrypto_HandleInvalidConfiguration() */

/**********************************************************************************************************************
 *  TLS CORE ALERT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreAlert_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCoreAlert_Init(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the Alert layer */
  TcpIp_SetTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);
  TcpIp_SetTxAlertTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);
} /* TcpIp_TlsCoreAlert_Init() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreAlert_Set
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreAlert_Set(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TcpIp_TlsAlertLevelType       AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TxAlertTriggerOfTlsConnectionDynType alertTrigger             = TcpIp_IsTxAlertTriggerOfTlsConnectionDyn(TlsConIdx);
  TcpIp_TxCloseNotifyTriggerOfTlsConnectionDynType closeNotifyTrigger = TcpIp_IsTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Check if there is a current alert set, and if it can be over written. */
  if ((alertTrigger == TRUE) && (closeNotifyTrigger == TRUE))
  {
    /* #20 if so (CloseNotify), overwrite the alert with the new one */
    TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer(TlsConIdx, AlertLevel, AlertDescription);
  }
  else if (alertTrigger == FALSE)
  {
    /* #30 no alert is set, forward the current one to RL */
    TcpIp_TlsCoreCtAl_ForwardAlertToTxBuffer(TlsConIdx, AlertLevel, AlertDescription);

    /* #40 Reset CloseNotify trigger, because after this alert the connection is closed and the CloseNotify will not be sent */
    TcpIp_SetTxCloseNotifyTriggerOfTlsConnectionDyn(TlsConIdx, FALSE);
  }
  else /* alertTrigger == TRUE */
  {
    /* There is already an alert set, so reject this one */
  }

  TCPIP_VLEAVE_CRITICAL_SECTION();
} /* TcpIp_TlsCoreAlert_Init() */

/**********************************************************************************************************************
 *  TLS CORE LOWER LAYER (LL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreLl_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreLl_RxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16           DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = TCPIP_TLS_E_NO_ERROR;

  TcpIp_TlsConnectionIterType tlsConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the corresponding TLS-Connection index to the given TCP socket */
  if (TcpIp_SocketIdxToTlsConIdx(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx), &tlsConIdx) == E_OK)
  {
    TcpIp_TlsBufferMgmtIdxOfTlsConnectionType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(tlsConIdx);

    /* #20 Add the data to the RxBufStruct of this TLS-Connection */
    if (TcpIp_TlsCoreRxBufStruct_WriteSegment(tlsBufferMgmtIdx, DataPtr, DataLen) == E_NOT_OK)
    {
      errorId = TCPIP_TLS_E_NO_BUF;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report an error if necessary. */
  if (errorId != TCPIP_TLS_E_NO_ERROR)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_RX_INDICATION, errorId);
  }
# else
  TCPIP_DUMMY_STATEMENT(errorId);                                                                                       /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif /* TCPIP_DEV_ERROR_REPORT */
} /* TcpIp_TlsCoreLl_RxIndication() */

# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreLl_TcpAccepted
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreLl_TcpAccepted(
  TcpIp_SocketTcpDynIterType      SocketTcpIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdxConnected)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsListenerIterType tlsListener;
  TcpIp_SizeOfSocketDynType socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Get the TLS-Listener corresponding to the SocketIdx */
  retVal = TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx(socketIdx, &tlsListener);
  if (retVal == E_OK)
  {
    TcpIp_TlsConnectionIterType tlsConIdx;

    /* Reset the return value */
    retVal = E_NOT_OK;

    /* #20 Iterate over all TLS connections to check if there is already a connection assigned to this socket. */
    for (tlsConIdx = 0u; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
    {
      if (TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx) == socketIdx)
      {
        /* Found a connection that was dynamically assigned to the socket using TcpIp_ChangeParameter. */
        break;
      }
    }

    /* #30 No dynamically assigned TLS connection found - get the next free TLS connection used by the given port */
    if (tlsConIdx >= TcpIp_GetSizeOfTlsConnection())
    {
      /* Get the used port and forward it to the search function for the next free TLS connection */
      uint16 usedPort = TcpIp_GetPortOfTlsListener(tlsListener);

      tlsConIdx = TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort(usedPort);
    }

    /* #40 If there is a connection assigned for this socket (dynamic port assigned) or a free TLS connection with the pre-configured port was found, prepare parameters. */
    if (tlsConIdx < TcpIp_GetSizeOfTlsConnection())
    {
      TcpIp_SocketOwnerConfigIdxOfSocketDynType socketOwnerCfgIdx
        = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

      TcpIp_SizeOfSocketDynType comSocketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdxConnected);

      /* Set the Listen and Communication Socket inside the found TLS-Connection */
      TcpIp_SetSocketDynListenIdxOfTlsConnectionDyn(tlsConIdx, socketIdx);
      TcpIp_SetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx, comSocketIdx);
      /* Set the socket owner index of this connection */
      TcpIp_SetSocketOwnerConfigIdxOfTlsConnectionDyn(tlsConIdx, socketOwnerCfgIdx);
      /* Set the Connection State for this connection */
      TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE);

      retVal = E_OK;
    }
  }
  TCPIP_VLEAVE_CRITICAL_SECTION();

  /* ----- Development Error Report ------------------------------------- */
#  if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report an error if necessary. */
  if (retVal != E_OK)
  {
    (void)Det_ReportError(TCPIP_MODULE_ID, TCPIP_TLS_VINSTANCE_ID, TCPIP_TLS_API_ID_TLS_ACCEPTED, TCPIP_TLS_E_NO_LISTENER);
  }
#  endif /* TCPIP_DEV_ERROR_REPORT */
  return retVal;
} /* TcpIp_TlsCoreLl_TcpAccepted() */
# endif

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreLl_TcpConnected
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreLl_TcpConnected(
  TcpIp_SizeOfSocketDynType      SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketOwnerConfigIdxOfSocketDynType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);
  TcpIp_TlsConnectionIterType tlsConIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all client connections and find the one that is assigned to the current socket. There always is a connection that is assigned. */
  /* Iterate over all configured TLS-Connections */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* Check if connection is configured as TLS-Client */
    if (TcpIp_GetModeOfTlsConnection(tlsConIdx) == TCPIP_TLS_CLIENT)
    {
      /* Check if the connection is already assigned to the current socket. */
      if (TcpIp_GetSocketDynComIdxOfTlsConnectionDyn(tlsConIdx) == SocketIdx)
      {
        /* OK, matching connection found */
        retVal = E_OK;
        break;  /* stop the for-loop */
      }
    }
  }

  /* #20 Fully allocate the connection to the socket if a matching connection was found. */
  if (retVal == E_OK)
  {
    /* Set the socket owner index of this connection */
    TcpIp_SetSocketOwnerConfigIdxOfTlsConnectionDyn(tlsConIdx, socketOwnerCfgIdx);
    /* Set the Connection State for this connection */
    TcpIp_SetConnectionStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE);
    /* Set the TLS Handshake State for this connection */
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(tlsConIdx, TCPIP_TLS_STATE_SEND_CLIENT_HELLO);
    /* Set the Transmission Required flag */
    TcpIp_SetHsStmTxTriggerOfTlsConnectionDyn(tlsConIdx, TRUE);

    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreLl_TcpConnected() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
/**********************************************************************************************************************
 *  TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 FunctionId,
  uint16 ErrorId)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsAlertLevelType alertLevel;
  TcpIp_TlsAlertDescriptionType alertDescription;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Report the error to the user, if set */
  if (ErrorId != TCPIP_TLS_ERRORID_NOT_SET)
  {
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = FunctionId;
    userError.UserErrorId = ErrorId;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  /* #20 Set the corresponding alert level and description */
  alertLevel = TCPIP_TLS_ALERT_LEVEL_FATAL;
  alertDescription = TCPIP_TLS_ALERT_DESC_INT_ERROR;

  /* #30 Trigger the transmission of the occurred alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);

  /* #40 Change the state to HANDSHAKE_ABORT */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

  TcpIp_SetHsAsyncCtxStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_CTX_DONE);

} /* TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing() */


/**********************************************************************************************************************
 *  TLS CORE UTIL  (HELPER FUNCTIONS)
 *********************************************************************************************************************/
# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean CurveUsedCompressionFlag;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the curve ID and return TRUE if the compression flag is used */
  switch (CurveId)
  {
    case TCPIP_CURVE_ID_SECP521R1:
    case TCPIP_CURVE_ID_SECP384R1:
    case TCPIP_CURVE_ID_SECP256R1:
    {
      CurveUsedCompressionFlag = TRUE;
      break;
    } /* case TCPIP_CURVE_ID_SECP521R1 | TCPIP_CURVE_ID_SECP384R1 | TCPIP_CURVE_ID_SECP256R1 */

    case TCPIP_CURVE_ID_X448:
    case TCPIP_CURVE_ID_X25519:
    {
      CurveUsedCompressionFlag = FALSE;
      break;
    } /* case TCPIP_CURVE_ID_X25519 | TCPIP_CURVE_ID_X448 */

    default:
    {
      CurveUsedCompressionFlag = FALSE;
      break;
    } /* default */
  } /* switch */
  return CurveUsedCompressionFlag;
} /* TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve() */
# endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/***********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode
 **********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(TcpIp_TlsCipherStreamingModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode(
  TcpIp_TlsCipherDataType ActiveCipher)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherStreamingModeDataType streamingMode;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the active cipher and return the active streaming mode */
  switch (ActiveCipher)
  {
  case TCPIP_TLS_NULL_WITH_NULL_NULL:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    {
      streamingMode = TCPIP_TLS_STREAMING_MODE_NULL;
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      streamingMode = TCPIP_TLS_STREAMING_MODE_AES_128_CBC;
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256:
    {
      streamingMode = TCPIP_TLS_STREAMING_MODE_AES_128_GCM;
      break;
    }
  default:
    {
      streamingMode = TCPIP_TLS_STREAMING_MODE_INVALID;
      break;
    }
  }

  return streamingMode;
} /* TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode() */

/***********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode
 **********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(TcpIp_TlsMessageAuthenticationModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode(
  TcpIp_TlsCipherDataType ActiveCipher)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsMessageAuthenticationModeDataType authMode;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the active cipher and return the active authentication mode */
  switch (ActiveCipher)
  {
  case TCPIP_TLS_NULL_WITH_NULL_NULL:
    {
      authMode = TCPIP_TLS_MSG_AUTH_MODE_NONE;
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
  case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    {
      authMode = TCPIP_TLS_MSG_AUTH_MODE_SHA256;
      break;
    }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
  case TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256:
  {
    /* For AEAD cipher suites, authentication is performed along with encryption */
    authMode = TCPIP_TLS_MSG_AUTH_MODE_NONE;
    break;
  }
  case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
  case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
  case TCPIP_TLS_PSK_WITH_NULL_SHA:
  case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      authMode = TCPIP_TLS_MSG_AUTH_MODE_SHA1;
      break;
    }
  default:
    {
      /* Unknown cipher suite */
      authMode = TCPIP_TLS_MSG_AUTH_MODE_INVALID;
      break;
    }
  }

  return authMode;
} /* TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_TlsCipherStreamingModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(
  TcpIp_TlsConnectionIterType       TlsConIdx)
{
  /* #10 Return the streaming mode of the selected cipher on this TLS connection */
  return TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode(
           TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(
             TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(
               TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx))));

} /* TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificKeyExchangeMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_TlsKeyExchangeMethodDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificKeyExchangeMethod(
  TcpIp_TlsCipherDataType ActiveCipher)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsKeyExchangeMethodDataType keyExchangeMethod;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the active cipher and return the active streaming mode */
  switch (ActiveCipher)
  {
# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
    case TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
    case TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA:
    {
      keyExchangeMethod = TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE;
      break;
    }
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
    case TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
    case TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA:
    {
      keyExchangeMethod = TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH;
      break;
    }
# endif
    case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256:
    case TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256:
    case TCPIP_TLS_PSK_WITH_NULL_SHA:
    case TCPIP_TLS_PSK_WITH_NULL_SHA256:
    case TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA:
    {
      keyExchangeMethod = TCPIP_TLS_KEYEXCHANGE_METHOD_PSK;
      break;
    }
    default:
    {
      /* Invalid key exchange method. This can never happen, a valid key exchange method has been chosen with the active
      cipher suite received in the server_hello message. */
      keyExchangeMethod = TCPIP_TLS_KEYEXCHANGE_METHOD_INVALID;
      break;
    }
  }

  return keyExchangeMethod;

} /* TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificKeyExchangeMethod() */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_TlsKeyExchangeMethodDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(
  TcpIp_TlsConnectionIterType       TlsConIdx)
{
  /* #10 Extract and return the cipher suite selected for the connection */
  return TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificKeyExchangeMethod(
           TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(
             TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(
               TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx))));

} /* TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod() */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;
  boolean connectionUseEccCipherSuite = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured CipherWorker for this TLS connection and check if it uses ECC cipher suites */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIterType tlsCipherWorkerIdx = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx =
      TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(tlsCipherWorkerIdx);

    if (TcpIp_IsCipherSuiteUsePskOfTlsCipherDefinition(tlsCipherDefinitionIdx) == FALSE)
    {
      /* At least one cipherworker does not use PSK - therefore it must use ECC */
      connectionUseEccCipherSuite = TRUE;
      break;
    }
  }
  return connectionUseEccCipherSuite;
} /* TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_CheckAndGetRootCertificateId
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUtil_CheckAndGetRootCertificateId(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2V(uint16)             CertIdPtr                                                                               /* PRQA S 3673 */ /* MD_TCPIP_Rule8.13_CfgSpecific */
)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the TLS connection uses a TLS client. */
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)
  {
    TcpIp_TlsKeyExchangeMethodDataType keyExchange =
      TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(TlsConIdx);

    /* #20 Check which key exchange algortihm is used and return the certificate ID. */
    switch (keyExchange)
    {
      case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH:
      case TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE:
      {
        retVal = TcpIp_TlsClient_GetRootCertificateId(TlsConIdx, CertIdPtr);
        break;
      }

      case TCPIP_TLS_KEYEXCHANGE_METHOD_PSK:
      default:
      {
        /* Nothing to do here. Return E_NOT_OK because the selected key exchange algorithm
         * does not supported certificates. */
        break;
      }
    }
  }
  else
  {
    /* Nothing to do here. The API call is not supported for TLS Server. Return E_NOT_OK. */
  }
# else
TCPIP_DUMMY_STATEMENT_CONST(TlsConIdx);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
TCPIP_DUMMY_STATEMENT_CONST(CertIdPtr);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
  return retVal;
}


# if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  MSA - Master Secret Access
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreMsa_ClearMasterSecretBuffer()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_Tls_STCAL */
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMsa_ClearMasterSecretBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear Session ID and Client Random */
/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.1 Improve: There is no need to differ between client and server here. The access buffers are already common for client and server. */
/* [REVIEW_c] resolved visbdk: Correct, removed the precompile switch */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif

  VStdLib_MemClr(TcpIp_GetAddrTlsClientRandomAccessBuffer(                                                            /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetTlsClientRandomAccessBufferStartIdxOfTlsConnection(TlsConIdx)), TCPIP_TLS_RANDOM_LEN);

  VStdLib_MemClr(TcpIp_GetAddrTlsClientSessionIdAccessBuffer(                                                         /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    TcpIp_GetTlsClientSessionIdAccessBufferStartIdxOfTlsConnection(TlsConIdx)), TcpIp_GetClientSessionIdAccessBufferLenOfTlsConnectionDyn(TlsConIdx));

  TcpIp_SetClientSessionIdAccessBufferLenOfTlsConnectionDyn(TlsConIdx, 0u);

} /* TcpIp_TlsCoreMsa_ClearMasterSecretBuffer() */


/**********************************************************************************************************************
 *  TcpIp_TlsCoreMsa_ReadHandshakeParameter
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreMsa_ReadHandshakeParameter(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint8)        MasterSecretPtr,
  TCPIP_P2V(uint8)        ClientRandomPtr,
  TCPIP_P2V(uint8)        SessionIdPtr,
  TCPIP_P2V(uint8)        SessionIdLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a valid TLS connection for this socket. */
  if (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
  {
    /* #20 Read the Master Secret from CSM */
    {
      TcpIp_TlsHandshakeIterType activeTlsHandshakeIdx =
        TcpIp_GetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(tlsConIdx));
      uint32 masterSecretKeyId        = TcpIp_CsmKeyId[TcpIp_GetCsmKeyIdMasterSecretIdxOfTlsHandshake(activeTlsHandshakeIdx)];
      uint32 masterSecretKeyElementId = TcpIp_GetHsCommonKeyElementIdOfTlsHandshake(activeTlsHandshakeIdx);
      uint32 masterSecretLen          = TCPIP_TLS_MASTER_SECRET_LEN;
      Std_ReturnType csmRetVal;

      /* Get the Master Secret Key from the CSM */
      csmRetVal = TCPIP_CSM_KeyElementGet(masterSecretKeyId, masterSecretKeyElementId, MasterSecretPtr, &masterSecretLen);
      /* Check if the length of the read key match */
      retVal = TcpIp_TlsCoreCrypto_CheckCsmResult(tlsConIdx, csmRetVal, masterSecretLen, TCPIP_TLS_MASTER_SECRET_LEN,
                  TCPIP_TLS_FCTID_CORE_MSA_READMASTERSECRET);

    }
    /* #30 Copy Client Random to user buffer, if buffer is valid. */
    if (ClientRandomPtr != NULL_PTR)
    {
      VStdMemCpy(&ClientRandomPtr[0],                                                                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
        TcpIp_GetAddrTlsClientRandomAccessBuffer(TcpIp_GetTlsClientRandomAccessBufferStartIdxOfTlsConnection(tlsConIdx)),
        TCPIP_TLS_RANDOM_LEN);
    }
    /* #40 Copy received Session Id and Session Id length to user buffer. */
    if ((SessionIdPtr != NULL_PTR) && (SessionIdLenPtr != NULL_PTR))
    {
      uint8 sessionIdAccessBufferLen = TcpIp_GetClientSessionIdAccessBufferLenOfTlsConnectionDyn(tlsConIdx);

      /* Check if the provided buffer is sufficient to store the session id */
      if (*SessionIdLenPtr >= sessionIdAccessBufferLen)
      {
        VStdMemCpy(&SessionIdPtr[0],                                                                                    /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
          TcpIp_GetAddrTlsClientSessionIdAccessBuffer(TcpIp_GetTlsClientSessionIdAccessBufferStartIdxOfTlsConnection(tlsConIdx)),
          sessionIdAccessBufferLen);
        /* Update the actual length of the received Session Id. */
        *SessionIdLenPtr = sessionIdAccessBufferLen;
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }
  else
  {
    /* #50 otherwise, no valid TLS connection could be found. */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsCoreMsa_ReadHandshakeParameter() */

# endif /* (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON) */


# define TCPIP_STOP_SEC_CODE
# include "TcpIp_MemMap.h"                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 *********************************************************************************************************************/
#endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsCore.c
 *********************************************************************************************************************/
