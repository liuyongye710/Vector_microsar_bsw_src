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
/*!     \file   TcpIp_TlsPriv.c
 *      \brief  Transport Layer Security (TLS) private functions implementation.
 *
 *    \details  This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#define TCPIP_TLS_PRIV_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "TcpIp_TlsPriv.h"
# include "TcpIp_Tls.h"
# include "TcpIp_TlsCore.h"
# include "TcpIp_Lcfg.h"

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
 *  LOCAL FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_AddHsHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_AddHsHdr(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsMsgHandshakeType, AUTOMATIC) HsType)
{
  /*         HS HEADER FORMAT
   *      +-------------------+
   *      | HS |      HS      |
   *      |TYPE|    LENGTH    |
   *      +-------------------+
   * BYTE   0    1    2    3
   */
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the handshake type to the first Byte of the TLS handshake header */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, HsType);

  /* Skipp the length information - this will be set later (see function TcpIp_TlsMsg_AddLenToHsHdr) */

  /* Increment the write index by the consumed length (4 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_HSHDRLEN);

} /* TcpIp_TlsMsg_AddHsHdr() */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_AddLenToHsHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_AddLenToHsHdr(
  TcpIp_TlsBufferTxIterType   HsHdrStartIdx,
  CONST(uint32, AUTOMATIC)    Length)
{

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the length into the buffer at the specific offset */
  IpBase_PutUint24(TcpIp_GetAddrTlsBufferTx(HsHdrStartIdx), TCPIP_TLS_HSHDRLEN_OFFSET, Length);

} /* TcpIp_TlsMsg_AddLenToHsHdr() */

/**********************************************************************************************************************
 *  HELLO MESSAGE HANDLING
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_AddSessionId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddSessionId(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Session Id not supported by this Implementation - Just set the length information to zero */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, 0);

  /* #20 Set the SessionId Start index */
  /* #30 Store the index of the SessionId - Index needed for possible master secret access */
/*
[REVIEW_G] c_accepted 16.00.00.2
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
    TcpIp_SetTlsBufferTxServerSessionIdIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx,
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
    TcpIp_SetServerHelloSessionIdLenOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, 0u); /* Session ID not supported, so length is always 0 */
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
    TcpIp_SetTlsBufferTxClientSessionIdIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
# endif

  /* Increment the write index by the consumed length (1 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_SESSIONIDLEN_LEN);

} /* TcpIp_TlsHelloMsg_AddSessionId() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_AddProtocolVersionNr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddProtocolVersionNr(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the major version (3) to the TLS TxBuffer at the current write position */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0,
                  TCPIP_TLS_PROTOCOL_MAJOR_VERSION_3);

  /* #20 Add the minor version (3) to the TLS TxBuffer at the current write position + 1 */
  IpBase_PutUint8(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 1,
                  TCPIP_TLS_PROTOCOL_MINOR_VERSION_3);

  /* Increment the write index by the consumed length (2 Byte) */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TCPIP_TLS_MAJORVERS_LEN + TCPIP_TLS_MINORVERS_LEN));

} /* TcpIp_TlsHelloMsg_AddProtocolVersionNr() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_AddRandomStructure
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructure(
  TcpIp_TlsConnectionIterType              TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Hello Random Structure Format - RFC 5246 7.4.1.2.Client Hello (is the same for Server Hello)
   * Byte 0 - 3  : GMT Unix Time stamp
   * Byte 4 - 33 : Random Bytes
   */

/*
[REVIEW_G] c_accepted 16.01.00.7
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/

/* Write index is pointing to the location within the TxBuffer where the random value is stored */
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
  {
    /* Mode == TCPIP_TLS_SERVER */
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: I'm confused. Isn't the server random provided here? Same issue for the client. */
/* [REVIEW_c] resolved visbdk: Comments are incorrect. I changed them.  */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
    /* Update the TLS-Server TX random index (Location in the TxBuffer where the random value is stored) */
    TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
    TcpIp_SetTlsBufferTxServerRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx,
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    /* Update the TLS-Client TX random index (Location in the TxBuffer where the random value is stored) */
    TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
    TcpIp_SetTlsBufferTxClientRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
# endif

  /* #10 Add the GMT Unix userTimeStamp stamp (Byte 0-3) */
  TcpIp_TlsHelloMsg_AddRandomStructureGetTime(TlsConIdx);

  /* #20 Add the random value (Byte 4-32) */
  retVal = TcpIp_TlsHelloMsg_AddRandomStructureGetRandom(TlsConIdx);                                                    /* PRQA S 2986 */ /* MD_TCPIP_Rule2.2_2986 */

  return retVal;
} /* TcpIp_TlsHelloMsg_AddRandomStructure() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_AddRandomStructureGetTime
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
FUNC(void, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructureGetTime(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint32 userTimeStamp = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a GetTimeCallout function is configured for this connection. */
  if (TcpIp_GetTimeCalloutFuncOfTlsConnection(TlsConIdx) != NULL_PTR)
  {
    TcpIp_TlsGetTimeCalloutFunctionType timeCalloutFunction;
    timeCalloutFunction = TcpIp_GetTimeCalloutFuncOfTlsConnection(TlsConIdx);

    /* #20 Get the userTimeStamp provided by the callout function. If it failed set the userTimeStamp to 0 for
       further processing and report the error. */
    if (timeCalloutFunction(&userTimeStamp) == E_NOT_OK)
    {
      /* Report the error to the user. */
      TcpIp_TlsUserErrorType userError;
      userError.FunctionId = TCPIP_TLS_FCTID_CLIENT_HSSTM_RANDOM_NUM_GET_TIME;
      userError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECT_TIME;
      userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(userError);

      /* If the callout function returns an error, reset the userTimeStamp to 0 and continue the handshake. */
      userTimeStamp = 0u;
    }
  }

  /* #30 Write the provided times to the next 4 Bytes. */
  IpBase_PutUint32(TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0, userTimeStamp);

  /* #40 Increment the write index by the consumed length (4 Byte). */
  TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TCPIP_TLS_UNIXTIMESTAMP_LEN));

} /* TcpIp_TlsHelloMsg_AddRandomStructureGetTime() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_AddRandomStructureGetRandom
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_AddRandomStructureGetRandom(
  TcpIp_TlsConnectionIterType              TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType                csmRetVal;
  uint32                        requiredRndLen;
  TcpIp_TlsFunctionIdType       apiId;

  Std_ReturnType                retVal           = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select the function Id depending on the connection mode. */

/*
[REVIEW_G] c_accepted 16.00.00.2
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
    apiId = TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_SERVERHELLO;
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    apiId = TCPIP_TLS_FCTID_CLIENT_HSSTM_PREPARE_CLIENTHELLO;
  }
# endif

  /* Set the required size of random value field */
  requiredRndLen = TCPIP_TLS_HSRANDOM_LEN;

  /* #20 Generate the random value and place it inside the TLS TxBuffer */
  csmRetVal = TCPIP_CSM_RandomGenerate(TcpIp_GetTlsRandomGenerateCsmJobId(),
    TcpIp_GetAddrTlsBufferTx(TcpIp_GetTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), &requiredRndLen);

  /* #30 Check the return value from the CSM call and the length of the generated random value */
  if (TcpIp_TlsCoreCrypto_CheckCsmResult(TlsConIdx, csmRetVal, requiredRndLen, TCPIP_TLS_HSRANDOM_LEN, apiId) == E_OK)
  {
    /* Random value successfully generated so increment the write index by the consumed length (28 Byte) */
    TcpIp_AddTlsBufferTxAdHsWriteIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TCPIP_TLS_HSRANDOM_LEN));

    retVal = E_OK;
  }
  else
  {
    /* CSM random generation failed, report error to the user */
    TcpIp_TlsUserErrorType userError;

    userError.FunctionId = apiId;
    userError.UserErrorId = TCPIP_TLS_ERRORID_CRYPTO_RANDOMGENERATE_FAILED;
    userError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(userError);
  }

  return retVal;
} /* TcpIp_TlsHelloMsg_AddRandomStructureGetRandom() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_ExtractReceivedExtensions
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_ExtractReceivedExtensions(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 ExtensionsLen,
  TcpIp_TlsBufferRxIterType HelloEndIdx,
  TCPIP_P2V(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  TCPIP_P2V(uint8) ReceivedExtensionCntPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint16 consumedExtensionLen = 0u;
  uint8 extensionListIter = 0u;
  Std_ReturnType retVal = E_NOT_OK;
  boolean stopProcessing = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over the TLS-RxBuffer until all extensions are consumed */
  while ((consumedExtensionLen < ExtensionsLen) && (stopProcessing != TRUE))
  {
    /* #20 Check if there is enough space in the list to add the next extension */
    if (extensionListIter < TCPIP_TLS_MAX_EXTENSION_LIST_LENGTH)
    {
      /* Check that we receive at least 4 bytes ( 2 bytes extension type + 2 bytes extension length) */
      if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),
           (TCPIP_TLS_EXTENSION_ID_LEN + TCPIP_TLS_EXTENSION_LIST_LEN), HelloEndIdx))
      {
        /* #30 Add current extension to the list of all received extensions */
        /* Read Extension Type */
        ReceivedExtensionListPtr[extensionListIter].Type = IpBase_GetUint16(
          TcpIp_GetAddrTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0u);
        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_ID_LEN);
        consumedExtensionLen += TCPIP_TLS_EXTENSION_ID_LEN;

        /* Read Extension Len */
        ReceivedExtensionListPtr[extensionListIter].Length = IpBase_GetUint16(TcpIp_GetAddrTlsBufferRx(
          TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx)), 0u);
        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_EXTENSION_LIST_LEN);
        consumedExtensionLen += TCPIP_TLS_EXTENSION_LIST_LEN;

        /* Read Extension Data */
        ReceivedExtensionListPtr[extensionListIter].StartIdx = TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx);
        TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, ReceivedExtensionListPtr[extensionListIter].Length);
        consumedExtensionLen += ReceivedExtensionListPtr[extensionListIter].Length;

        /* Check that the received length of this extension is still in range of the Hello message */
        /* Start index of the extension + length of the extension must be smaller or equal the HelloMessage end index */
        if (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(ReceivedExtensionListPtr[extensionListIter].StartIdx,                       /* PRQA S 2995 2 */ /* MD_TcpIp_Tls_2995 */
          ReceivedExtensionListPtr[extensionListIter].Length, HelloEndIdx))
        {
          extensionListIter++;
        }
        else
        {
          /* Not sufficient space in buffer - skip the processing and return E_NOT_OK */
          stopProcessing = TRUE;
        }
      }
      else
      {
        /* Not sufficient space in buffer - skip the processing and return E_NOT_OK */
        stopProcessing = TRUE;
      }
    }
    else
    {
      /* Not enough space in extension list - skip the processing and return E_NOT_OK */
      stopProcessing = TRUE;
    }
  }

  /* Check if all extension data is consumed */
  if (ExtensionsLen != consumedExtensionLen)
  {
    /* #40 If there is unprocessed data or an invalid extension length - return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  else
  {
    /* #50 Update the counter of the overall received extensions */
    *ReceivedExtensionCntPtr = extensionListIter;
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsHelloMsg_ExtractReceivedExtensions() */

/**********************************************************************************************************************
 *  TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions(
  TCPIP_P2C(TcpIp_TlsExtensionType) ReceivedExtensionListPtr,
  uint8 ReceivedExtensionCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 firstExtensionIter;
  uint8 secondExtensionIter;

  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare each element of the received extension list again each other */
  for (firstExtensionIter = 0u; firstExtensionIter < ReceivedExtensionCnt; firstExtensionIter++)
  {
    for (secondExtensionIter = firstExtensionIter + 1u; secondExtensionIter < ReceivedExtensionCnt; secondExtensionIter++)
    {
      /* Check if we receive the same extension type twice */
      /* No additional need to check the length or data of the extension */
      if (ReceivedExtensionListPtr[firstExtensionIter].Type == ReceivedExtensionListPtr[secondExtensionIter].Type)
      {
        /* #20 If same extension type is received twice - set retVal to E_NOT_OK */
        retVal = E_NOT_OK;
      }
    }
  }

  return retVal;
} /* TcpIp_TlsHelloMsg_CheckDuplicatedReceivedExtensions() */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsHs_CheckExpectedMsgLen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsHs_CheckExpectedMsgLen(
  CONST(uint32, AUTOMATIC) MsgLen,
  CONST(uint32, AUTOMATIC) ExpectedMsgLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that the received message length has the minimum expected message length */
  if (MsgLen >= ExpectedMsgLen)
  {
   retVal = E_OK;
  }
  else
  {
    /* #20 otherwise, nothing to do - error handling in caller function */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* TcpIp_TlsHs_CheckExpectedMsgLen() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsHsStm_ErrorHandlingAndStateTransition
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsHsStm_ErrorHandlingAndStateTransition(
  TcpIp_TlsConnectionIterType      TlsConIdx,
  Std_ReturnType                   IntRetVal,
  TcpIp_TlsHandshakeState          NextHsState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the parameter IntRetVal indicates an occurred error */
  if (IntRetVal == E_OK)
  {
    /* #20 Parameter indicates no error in previous function, set the TLS handshake state to the next state */
    TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, NextHsState);
  }
  else
  {
    /* #30 Parameter indicates an error in previous function, report the error and trigger the transmit of a TLS alert */
    TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(TlsConIdx);
  }
} /* TcpIp_TlsHsStm_ErrorHandlingAndStateTransition() */

/**********************************************************************************************************************
 *  TcpIp_TlsHsStm_HandlesUnexpectedHsInformation
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
FUNC(void, TCPIP_CODE) TcpIp_TlsHsStm_HandlesUnexpectedHsInformation(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
   /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsUserErrorType hsUserError;
  TcpIp_TlsAlertLevelType alertLevel;
  TcpIp_TlsAlertDescriptionType alertDescription;

  /* ----- Implementation ----------------------------------------------- */

   /* #10 set the corresponding error id */
/*
[REVIEW_G] c_accepted 16.00.00.2
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
    hsUserError.FunctionId  = TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_HS_MSG;
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    hsUserError.FunctionId  = TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_HS_MSG;
  }
# endif

  hsUserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTHSMSG;
  hsUserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

  /* #20 Report the error to the user */
  TcpIp_TlsCoreError_ReportUserError(hsUserError);

  /* #30 Set the corresponding alert level and description */
  alertLevel       = TCPIP_TLS_ALERT_LEVEL_FATAL;
  alertDescription = TCPIP_TLS_ALERT_DESC_DECODE_ERROR;

  /* #40 Trigger the transmission of the occurred alert */
  TcpIp_TlsCoreAlert_Set(TlsConIdx, alertLevel, alertDescription);

  /* #50 Change the state to HANDSHAKE_ABORT */
  TcpIp_SetHandshakeStateOfTlsConnectionDyn(TlsConIdx, TCPIP_TLS_STATE_HANDSHAKE_ABORT);

} /* TcpIp_TlsHsStm_HandlesUnexpectedHsInformation() */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_HelloMsgGetVersionNr
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetVersionNr(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx  = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  uint8                         rcvdMajorVersNr;
  uint8                         rcvdMinorVersNr;
  TcpIp_TlsUserErrorIdType      internalUserError = TCPIP_TLS_ERRORID_NOT_SET;                                          /* PRQA S 2981 */ /* MD_TCPIP_Rule2.2_RedundantAssignment */
  Std_ReturnType                retVal            = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the received version numbers of the client_hello message */
  rcvdMajorVersNr = TcpIp_GetTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Let the read index point to the minor version */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_MAJORVERS_LEN);

  rcvdMinorVersNr = TcpIp_GetTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  /* Let the read index point to the next field */
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_MINORVERS_LEN);

  /* RFC5246 p. 87 - E.1.  Compatibility with TLS 1.0/1.1 and SSL 3.0 */
  /* #20 Check that the received major version number matches */
  if (rcvdMajorVersNr == TCPIP_TLS_PROTOCOL_MAJOR_VERSION_3)
  {
    /* #30 If the major Version number matches, check that the received minor version number matches */
/*
[REVIEW_G] c_accepted 16.01.00.7
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
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: We don't receive a server minor version but the client one. Same issue for the client path. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
      /* Received TLS-Client minor version number MUST at least support our minor number */
      if (rcvdMinorVersNr >= TCPIP_TLS_PROTOCOL_MINOR_VERSION_3)
      {
        /* Version numbers OK, reset the error value */
        retVal = E_OK;
      }
      else
      {
        /* Received minor version number does NOT match with our minor number, set user error */
        internalUserError = TCPIP_TLS_ERRORID_CTHS_INCORRECTMINORVERSION;
      }
    }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
    {
      /* Mode == TCPIP_TLS_CLIENT */
      /* Received TLS-Server minor version number MUST at exactly support our minor version */
      if (rcvdMinorVersNr == TCPIP_TLS_PROTOCOL_MINOR_VERSION_3)
      {
        /* Version numbers OK, reset the error value */
        retVal = E_OK;
      }
      else
      {
        /* Received minor version number does NOT match with our minor number, set user error */
        internalUserError = TCPIP_TLS_ERRORID_CTHS_INCORRECTMINORVERSION;
      }
    }
# endif
  }
  else
  {
    /* Received major version number does NOT match with our major number, set user error */
    internalUserError = TCPIP_TLS_ERRORID_CTHS_INCORRECTMAJORVERSION;
  }

  /* #40 in case of an mismatch with the version numbers, report an error to the user and trigger an TLS alert */
  if (retVal != E_OK)
  {

    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_USERERROR_PARSEHELLO(TlsConIdx);
    UserError.UserErrorId = internalUserError;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);

    /* Trigger alert protocol_version in case of invalid version numbers */
    TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_PROT_VERSION);
  }

  return retVal;
} /* TcpIp_TlsMsg_HelloMsgGetVersionNr() */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_HelloMsgGetRandom
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetRandom(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsBufferMgmtDynIterType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the start index of the received random value, depending on the connection mode (Server/Client) */

/*
[REVIEW_G] c_accepted 16.00.00.2
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
    TcpIp_SetTlsBufferRxClientRandomIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  {
    /* Mode == TCPIP_TLS_CLIENT */
    TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
    TcpIp_SetTlsBufferRxServerRandomIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx,
      TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  }
# endif

  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, (TCPIP_TLS_HSRANDOM_LEN + TCPIP_TLS_UNIXTIMESTAMP_LEN));

} /* TcpIp_TlsMsg_HelloMsgGetRandom() */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_HelloMsgGetSessionId
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
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_HelloMsgGetSessionId(
  TcpIp_TlsConnectionIterType  TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;
  uint8 sessionIdLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 ReadIdx points to the SessionIdLen field */
  sessionIdLen = TcpIp_GetTlsBufferRx(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
  TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, TCPIP_TLS_SESSIONIDLEN_LEN);

  /* #20 Check if we received a Session ID (Length > 0) */
  if (sessionIdLen > 0u)
  {
    /* #30 Check the max length of the received session id, and check that the received session length is in range of the TLS RxBuffer */
    if (   (sessionIdLen <= TCPIP_TLS_SESSIONIDMAX_LEN)
        && (TCPIP_TLS_RXBUFFER_ISIDXINRANGE(TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx),        /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
                                            (TcpIp_TlsBufferRxIterType)sessionIdLen, HelloEndIdx)))
    {
      /* #40 Store the start index of the received Session Id depending on the connection mode */
/*
[REVIEW_G] c_accepted 16.00.00.2
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
# if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
      if (TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_SERVER)
#  endif
      {
        /* Tls Server - Store the start index of the received client session ID */
        TcpIp_TlsServerBufferMgmtIterType tlsServerBufferMgmtIdx = TcpIp_GetTlsServerBufferMgmtIdxOfTlsConnection(TlsConIdx);
        TcpIp_SetTlsBufferRxClientSessionIdIdxOfTlsServerBufferMgmt(tlsServerBufferMgmtIdx, TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
      }
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
      else
#  endif
# endif
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
      {
        /* Tls Client - Store the start index of the received server session ID */
        TcpIp_TlsClientBufferMgmtIterType tlsClientBufferMgmtIdx = TcpIp_GetTlsClientBufferMgmtIdxOfTlsConnection(TlsConIdx);
        TcpIp_SetTlsBufferRxServerSessionIdIdxOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx));
        TcpIp_SetServerHelloSessionIdLenOfTlsClientBufferMgmt(tlsClientBufferMgmtIdx, sessionIdLen);
      }
# endif

      /* #50 Session ID not supported by this implementation - skip the actual session ID length in the received buffer */
      TcpIp_AddTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx, sessionIdLen);
      retVal = E_OK;
    }
    else
    {
      /* #60 Report an error to the user */
      TcpIp_TlsUserErrorType UserError;
      UserError.FunctionId  = TCPIP_TLS_USERERROR_PARSEHELLO(TlsConIdx);
      UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_INCORRECTSESSIONID;
      UserError.TlsConId    = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

      TcpIp_TlsCoreError_ReportUserError(UserError);

      TcpIp_TlsCoreAlert_Set(TlsConIdx, TCPIP_TLS_ALERT_LEVEL_FATAL, TCPIP_TLS_ALERT_DESC_DECODE_ERROR);

      retVal = E_NOT_OK;
    }
  }
  else
  {
    /* #70 SessionIdLen == 0 - No session Id received */
    retVal = E_OK;
  }

  return retVal;
} /* TcpIp_TlsMsg_HelloMsgGetSessionId() */
# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsMsg_SelectMatchingCipherSuiteId
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_SelectMatchingCipherSuiteId(
  TcpIp_TlsConnectionIterType                                    TlsConIdx,
  CONST(TcpIp_CipherSuiteIdOfTlsCipherDefinitionType, AUTOMATIC) CipherSuiteSelected)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_TlsCipherWorkerIndIterType cipherWorkerIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured cipher workers and check if their cipher suite matches with the given one */
  for (cipherWorkerIter = TcpIp_GetTlsCipherWorkerIndStartIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter < TcpIp_GetTlsCipherWorkerIndEndIdxOfTlsConnection(TlsConIdx);
       cipherWorkerIter++)
  {
    TcpIp_TlsCipherWorkerIndType tlsCipherWorkerIdx
      = TcpIp_GetTlsCipherWorkerInd(cipherWorkerIter);
    TcpIp_TlsCipherDefinitionIdxOfTlsCipherWorkerType tlsCipherDefinitionIdx
      = TcpIp_GetTlsCipherDefinitionIdxOfTlsCipherWorker(tlsCipherWorkerIdx);
    TcpIp_CipherSuiteIdOfTlsCipherDefinitionType cipherSuiteId
      = TcpIp_GetCipherSuiteIdOfTlsCipherDefinition(tlsCipherDefinitionIdx);

    if (cipherSuiteId == CipherSuiteSelected)
    {
      /* #20 If the cipher suite matches, set the active cipher suite index to the current cipher worker */
      TcpIp_SetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx, tlsCipherWorkerIdx);
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* TcpIp_TlsMsg_SelectMatchingCipherSuiteId() */

# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */


/**********************************************************************************************************************
 *  TcpIp_TlsMsg_SelectDefaultHandshakeReference
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_SelectDefaultHandshakeReference(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsCipherWorkerActiveIdxOfTlsConnectionDynType activeTlsCipherWorkerIdx =
    TcpIp_GetTlsCipherWorkerActiveIdxOfTlsConnectionDyn(TlsConIdx);

  TcpIp_TlsHandshakeIndStartIdxOfTlsCipherWorkerType handshakeStartIndIdx =
    TcpIp_GetTlsHandshakeIndStartIdxOfTlsCipherWorker(activeTlsCipherWorkerIdx);

  TcpIp_TlsHandshakeIndType handshakeStartIdx = TcpIp_GetTlsHandshakeInd(handshakeStartIndIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Select the handshake start index as active one */
  TcpIp_SetTlsHandshakeActiveIdxOfTlsCipherWorkerDyn(activeTlsCipherWorkerIdx, handshakeStartIdx);

} /* TcpIp_TlsMsg_SelectDefaultHandshakeReference() */

# if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsMsg_SelectDefaultPskIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TlsMsg_SelectDefaultPskIdentity(
  TcpIp_TlsConnectionIterType TlsConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsPskIdentityDefaultIdxOfTlsConnectionType tlsPskIdentityDefaultIdx = TcpIp_GetTlsPskIdentityDefaultIdxOfTlsConnection(TlsConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the configured default PSK Identity as active */
  TcpIp_SetTlsPskIdentityActiveIdxOfTlsConnectionDyn(TlsConIdx, tlsPskIdentityDefaultIdx);


} /* TcpIp_TlsMsg_SelectDefaultPskIdentity() */
# endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsMsg_CheckMsgForRemainingData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_CheckMsgForRemainingData(
  TcpIp_TlsConnectionIterType TlsConIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC)  HelloEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfTlsBufferMgmtType tlsBufferMgmtIdx = TcpIp_GetTlsBufferMgmtIdxOfTlsConnection(TlsConIdx);
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the current read position is equal to the end position */
  if (TcpIp_GetTlsBufferRxAdHsReadIdxOfTlsBufferMgmtDyn(tlsBufferMgmtIdx) == HelloEndIdx)
  {
    /* #20 when the indexes are equal, there is no remaining data. Return E_OK */
    retVal = E_OK;
  }
  else
  {
    /* #30 If the indexes are not equal there is remaining data - Report an error to the user */
    TcpIp_TlsUserErrorType UserError;
    UserError.FunctionId = TCPIP_TLS_USERERROR_PARSEHELLO(TlsConIdx);
    UserError.UserErrorId = TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN;
    UserError.TlsConId = TCPIP_TLS_CONNECTION_IDX_TO_ID(TlsConIdx);

    TcpIp_TlsCoreError_ReportUserError(UserError);
    retVal = E_NOT_OK;
  }
  return retVal;
} /* TcpIp_TlsMsg_CheckMsgForRemainingData() */

# if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/***********************************************************************************************************************
 *  TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature
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
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature(
  TCPIP_P2C(uint8) SignInputPtr,
  uint32 SignInputLen,
  uint8 SignCoordinateSize,
  TCPIP_P2V(uint8) SignOutputPtr)
{
  /* format of the encoded signature:
     || Type | Length | Type(r) | Length(r) | (r-parameter) | Type(s) | Length(s) | (s-parameter) ||
     ||  1   |   1    |    1    |     1     |    rLength    |    1    |     1     |    sLength    ||
     Each type and length field has a size of 1byte. In the code below values for the position of parameter size and
     value are calculated accordingly:
      sLengthOffset fixed part: 2bytes global type and length field
                                + 2bytes r-parameter type and length field + 1byte s-parameter type field = 5bytes
      sValueOffset  fixed part: 2bytes global type and length field
                                + 2 times 2bytes type and length field for the signature parameters = 6bytes
      rValueOffset  fixed part: 2bytes global type and length field + 2bytes s-parameter type and length field = 4bytes
   */

  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8  rLength;
  uint8  sLength;
  const uint8 *signRPtr;
  const uint8 *signSPtr;
  /* signature value is BER encoded */
  /* zero byte will be added in case first byte >= 0x80, leading zero bytes will be deleted in case of 9 consecutive 0-Bits */
  /* do some manual BER decoding */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the given data can contain a BER encoded signature (basic check) */
  if(   (SignInputLen > 4u)  /* two times a 2 byte type and length field */
     && (SignInputPtr[0u] == 0x30u) /* sequence */
     && (SignInputPtr[1u] <= 0x46u) /* maximum signature size for secp256r1sequence (each coordinate with 33 byte) */
     && (SignInputPtr[1u] >= 0x06u) /* minimum signature size for secp256r1sequence (each coordinate with only one byte) */
    /* SignInputPtr[1u] is the signature total length. Our implementation only supports the curve secp256r1, so the
       encoded length information never is too big for one byte. The r and s lengths are taken into account later. */
     && (SignInputPtr[2u] == 0x02u)) /* integer */
  {
    /* #20 Read r length and check total length */
    rLength = SignInputPtr[3];
    if(   (rLength > 0u) && (rLength <= (SignCoordinateSize + 1u))  /* valid range for r length */
       && (SignInputLen >= ((uint32) 4u + rLength + 2u + 1u))  /* s-parameter needs at least one byte */
       && (SignInputPtr[4u + rLength] == 0x02u))      /* type of s-value must be an integer */
    {
      uint32 rValueOffset;
      uint32 sLengthOffset = (uint32) 4u + rLength + 1u;  /* description for fix part see above */
      uint32 sValueOffset  = (uint32) 4u + rLength + 2u;  /* description for fix part see above */
      sLength = SignInputPtr[sLengthOffset];

      /* #30 Get r and s value pointers and lengths. Start with part s because rLength may be manipulated afterwards */

      /* Check the lengths of r and s to be in their limits */
      /* rLength range is already checked */
      if ((sLength <= (SignCoordinateSize + 1u)) && (sLength > 0u)
        && ((sValueOffset + sLength) == SignInputLen)) /* s-parameter has to fit into the signature */
      {
        /* #40 Determine the length and position of the signature parameter s */
        /* if first byte is 0, reduce parameter length and inc value offset */
        if (SignInputPtr[sValueOffset] == 0u)
        {
          sValueOffset++;
          sLength--;
        }
        signSPtr = &SignInputPtr[sValueOffset];

        /* #50 Determine the length and position of the signature parameter r */
        rValueOffset  = 4u;  /* description for fix value see above */
        /* if first byte is 0, reduce parameter length and inc value offset */
        if (SignInputPtr[rValueOffset] == 0u)
        {
          rValueOffset++;
          rLength--;
        }
        signRPtr = &SignInputPtr[rValueOffset];

        /* #60 Fill r and s parameter of the output signature */
        /* If the input signature was well formated, rLength and sLength will always be smaller or equal to 32 bytes. */
        if ((rLength <= SignCoordinateSize) && (sLength <= SignCoordinateSize))  /* Check the lengths of r and s to be in their limits */
        {
          /* fill start of signature parameters with zero bytes if necessary */
          VStdMemSet(&SignOutputPtr[0u], 0u, (SignCoordinateSize - (uint32)rLength));                                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
          VStdMemSet(&SignOutputPtr[SignCoordinateSize], 0u, (SignCoordinateSize - (uint32)sLength));                   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

          /* copy the value of the signature parameters */
          VStdMemCpy(&SignOutputPtr[SignCoordinateSize - rLength], signRPtr, rLength);                                  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
          VStdMemCpy(&SignOutputPtr[SignCoordinateSize + (SignCoordinateSize - sLength)], signSPtr, sLength);           /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */

          retVal = E_OK;
        }
      }
    }
  }
  return retVal;
} /* TcpIp_TlsMsg_DecodeBerEncodedEcdsaSignature() */

# endif /* (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 *********************************************************************************************************************/
#endif /*(TCPIP_SUPPORT_ASRTLS == STD_ON) */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsPriv.c
 *********************************************************************************************************************/
