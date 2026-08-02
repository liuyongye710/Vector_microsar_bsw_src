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
/*!        \file TcpIp_Tls_Types.h
 *        \brief Transport Layer Security (TLS) types header file.
 *
 *      \details This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TLS_TYPES_H)
# define TCPIP_TLS_TYPES_H

# include "TcpIp_Cfg.h"
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#  include "TcpIp_Types.h"
#  include "Std_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

#  define TCPIP_TLS_UINT24_MAX 16777215u /* 2^24 -1 */

 /* ALERT DESCRIPTIONS */
 /* Alerts marked with and 'f' are FATALE errors */
typedef uint8 TcpIp_TlsAlertDescriptionType;
#  define TCPIP_TLS_ALERT_DESC_CLOSE_NOTIFY                0u /* close_notify */
#  define TCPIP_TLS_ALERT_DESC_UNEXP_MSG                  10u /* f, unexpected_message */
#  define TCPIP_TLS_ALERT_DESC_BAD_RECORD_MAC             20u /* f, bad_record_mac */
#  define TCPIP_TLS_ALERT_DESC_DECR_FAILED_RESERVED       21u /* decryption_failed_RESERVED - old */
#  define TCPIP_TLS_ALERT_DESC_RECORD_OVERFLOW            22u /* f, record_overflow */
#  define TCPIP_TLS_ALERT_DESC_DECOMP_FAILURE             30u /* f, decompression_failure */
#  define TCPIP_TLS_ALERT_DESC_HANDSHAKE_FAILURE          40u /* f, handshake_failure */
#  define TCPIP_TLS_ALERT_DESC_NO_CERT_RESERVED           41u /* no_certificate_RESERVED - old */
#  define TCPIP_TLS_ALERT_DESC_BAD_CERT                   42u /* bad_certificate */
#  define TCPIP_TLS_ALERT_DESC_UNSUP_CERT                 43u /* unsupported_certificate */
#  define TCPIP_TLS_ALERT_DESC_CERT_REVOKED               44u /* certificate_revoked */
#  define TCPIP_TLS_ALERT_DESC_CERT_EXPIRED               45u /* certificate_expired */
#  define TCPIP_TLS_ALERT_DESC_CERT_UNKNOWN               46u /* certificate_unknown */
#  define TCPIP_TLS_ALERT_DESC_ILLEGAL_PARAM              47u /* f, illegal_parameter */
#  define TCPIP_TLS_ALERT_DESC_UNKNOWN_CA                 48u /* f, unknown_ca */
#  define TCPIP_TLS_ALERT_DESC_ACCESS_DENIED              49u /* f, access_denied */
#  define TCPIP_TLS_ALERT_DESC_DECODE_ERROR               50u /* f, decode_error */
#  define TCPIP_TLS_ALERT_DESC_DECRYPT_ERROR              51u /* f, decrypt_error */
#  define TCPIP_TLS_ALERT_DESC_EXP_RESTR_FAILURE          60u /* export_restriction_RESERVED - old */
#  define TCPIP_TLS_ALERT_DESC_PROT_VERSION               70u /* f, protocol_version */
#  define TCPIP_TLS_ALERT_DESC_INSUF_SEC                  71u /* f, insufficient_security */
#  define TCPIP_TLS_ALERT_DESC_INT_ERROR                  80u /* f, internal_error */
#  define TCPIP_TLS_ALERT_DESC_USER_CANCELED              90u /* user_canceled */
#  define TCPIP_TLS_ALERT_DESC_NO_RENEGOT                100u /* no_renegotiation */
#  define TCPIP_TLS_ALERT_DESC_UNSUP_EXT                 110u /* f, unsupported_extension */
#  define TCPIP_TLS_ALERT_DESC_CERT_UNOBTAINABLE         111u /* f, certificate_unobtainable */
#  define TCPIP_TLS_ALERT_DESC_UNRECOGNIZED_NAME         112u /* f, unrecognized_name */
#  define TCPIP_TLS_ALERT_DESC_BAD_CERT_STATUS_RESP      113u /* f, bad_certificate_status_response */
#  define TCPIP_TLS_ALERT_DESC_BAD_CERT_HASH_VALUE       114u /* f, bad_certificate_hash_value */
#  define TCPIP_TLS_ALERT_DESC_UNKNOWN_PSK_IDENTITY      115u /* f, unknown_psk_identity */
#  define TCPIP_TLS_ALERT_UNSET                         0xffu /* */



typedef uint16 TcpIp_TlsFunctionIdType;
#  define TCPIP_TLS_FCTID_NOT_SET                                      0xFFFFu
/* CORE FUNCTION IDS 0x0000 -  */
/* MAIN FUNCTION IDS 0x0000 - 0x0100 */
#  define TCPIP_TLS_FCTID_INVALID_CONFIG                               0x0000u
#  define TCPIP_TLS_FCTID_CORE_MAINFCT_RXRL                            0x0001u
#  define TCPIP_TLS_FCTID_CORE_MAINFCT_RXHS                            0x0002u
#  define TCPIP_TLS_FCTID_CORE_MSA_READMASTERSECRET                    0x0003u
#  define TCPIP_TLS_FCTID_CORE_MAINFCT_CCS                             0x0004u
#  define TCPIP_TLS_FCTID_CORE_MAINFCT_AL                              0x0005u
/* RECORD LAYER FUNCTION IDS 0x0100 - 0x0200 */
#  define TCPIP_TLS_FCTID_CORE_RL_CHECKHDR                             0x0100u
#  define TCPIP_TLS_FCTID_CORE_RL_TRANSMIT                             0x0101u
#  define TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACADHS                       0x0102u
#  define TCPIP_TLS_FCTID_CORE_RL_VERIFYHMACAL                         0x0103u
#  define TCPIP_TLS_FCTID_CORE_RL_RXHSADDATA                           0x0104u
/* HANDSHAKE LAYER FUNCTION IDS 0x0200 - 0x0300 */
#  define TCPIP_TLS_FCTID_CORE_CTHS_CHECKFRAMETYPE                     0x0200u
#  define TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO               0x0201u
#  define TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_HS_MSG                    0x0202u
#  define TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_SERVERHELLO             0x0203u
#  define TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_HS_MSG                  0x0204u
#  define TCPIP_TLS_FCTID_SERVER_HSSTM_PREPARE_SERVERCERT_MSG          0x0205u
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_HS_MSG                    0x0206u
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PREPARE_CLIENTHELLO             0x0207u
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PREPARE_HS_MSG                  0x0208u
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLO               0x0209u
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERCERT                0x020Au
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERKEYEXCH             0x020Bu
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLODONE           0x020Cu
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERFINISHED            0x020Du
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_CLIENTKEYEXCHANGE         0x020Eu
#  define TCPIP_TLS_FCTID_CLIENT_HSSTM_RANDOM_NUM_GET_TIME             0x020Fu
/* SERVER ASYNC CTX FUNCTION IDs 0x0300 - 0x0400 */
#  define TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_SIGN_PUBKEY             0x0300u
#  define TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_FINISHED_HASH           0x0301u
#  define TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_CLIENTFINISHED_HASH     0x0302u
#  define TCPIP_TLS_FCTID_SERVER_ASYNCCTX_CALC_CLIENTFINISHED_VERIFY   0x0303u
/* CRYPTO FUNCTION IDs 0x0400 - 0x0500 */
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_PSHA256                     0x0400u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_CALC_HMAC                        0x0401u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_CLEARCSMKEY                      0x0402u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_GENERATEIVRANDOM                 0x0403u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_SETAESIVVALUE                    0x0404u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_CALCMASTERSECRET                 0x0405u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_DERIVEKEYBLOCK                   0x0406u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128CBC          0x0407u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTHMACPADDINGAES128CBC      0x0408u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_REDUCEKEY                        0x0409u
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_ENCRYPTADHSBUFAES128GCM          0x040Au
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_PSK_CALC_PREMASTERSECRET         0x040Bu
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_DECRYPTALBUFAES128CBC            0x040Cu
#  define TCPIP_TLS_FCTID_CORE_CRYPTO_DECRYPTALBUFAES128GCM            0x040Du
/* CRYPTO FUNCTION IDs SERVER 0x0500 - 0x0600 */
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYS                     0x0500u
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128CBC            0x0501u
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSNULL                 0x0502u
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_CALCHSFINISHEDHASH             0x0503u
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_CALCHSFINISHEDDATA             0x0504u
#  define TCPIP_TLS_FCTID_SERVER_CRYPTO_SETCSMKEYSAES128GCM            0x0505u
/* CRYPTO FUNCTION IDs CLIENT 0x0600 - 0x0700 */
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYS                     0x0600u
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAES128CBC            0x0601u
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSNULL                 0x0602u
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_CALCHSFINISHEDHASH             0x0603u
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_CALCHSFINISHEDDATA             0x0604u
#  define TCPIP_TLS_FCTID_CLIENT_CRYPTO_SETCSMKEYSAEAD128GCM           0x0605u
/* CLIENT ASYNC CTX FUNCTION IDs 0x700 - 0x0800 */
#  define TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_VERIFY_SIGN_PUBKEY           0x0700u
#  define TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_CLIENTFINISHED_HASH     0x0701u
#  define TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_SERVERFINISHED_HASH     0x0702u
#  define TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_CALC_SERVERFINISHED_VERIFY   0x0703u
#  define TCPIP_TLS_FCTID_CLIENT_ASYNCCTX_VALIDATE_CERT_STATUS         0x0704u
/* CORE ASYNC CTX FUNCTION IDs 0x0800 - 0x0900 */
#  define TCPIP_TLS_FCTID_CORE_ASYNCCTX_CALC_DH_PUBKEY                 0x0800u
#  define TCPIP_TLS_FCTID_CORE_ASYNCCTX_CALC_DH_SHAREDSECRET           0x0801u
#  define TCPIP_TLS_FCTID_CORE_ASYNCCTX_CALC_MASTERSECRET              0x0802u

typedef uint16 TcpIp_TlsUserErrorIdType;
/* GENERIC ERROR IDS 0x0000 - 0x0100 */
#  define TCPIP_TLS_ERRORID_INVALID_CONFIG                             0x0000u
#  define TCPIP_TLS_ERRORID_NOSPACEINBUF                               0x0001u
/* RECORD LAYER ERROR IDS 0x0100 - 0x0200 */
#  define TCPIP_TLS_ERRORID_RXINCORRECTRLFRAME                         0x0100u
#  define TCPIP_TLS_ERRORID_RL_INCORRECT_CT                            0x0101u
#  define TCPIP_TLS_ERRORID_RL_INCORRECT_MAJORVERSNR                   0x0102u
#  define TCPIP_TLS_ERRORID_RL_INCORRECT_MINORVERSNR                   0x0103u
#  define TCPIP_TLS_ERRORID_RL_TXHDR_FAILED                            0x0104u
#  define TCPIP_TLS_ERRORID_RL_CALCHMAC_FAILED                         0x0105u
#  define TCPIP_TLS_ERRORID_RL_TX_FAILED                               0x0106u
/* HANDSHAKE ERROR IDS 0x0200 - 0x0300 */
#  define TCPIP_TLS_ERRORID_RXINCORRECTHSMESSAGE                       0x0200u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTFRAMETYPE                    0x0201u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTMAJORVERSION                 0x0202u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTMINORVERSION                 0x0203u
#  define TCPIP_TLS_ERRORID_CTHS_UNEXPECTEDMSGLEN                      0x0204u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTHSMSG                        0x0205u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTSESSIONID                    0x0206u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTCIPHERLEN                    0x0207u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTCOMPRESSIONLEN               0x0208u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTEXTENSIONSLEN                0x0209u
#  define TCPIP_TLS_ERRORID_CTHS_NOMATCHINGCIPHER                      0x020Au
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTCOMPMETHOD                   0x020Bu
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTCURVEINFO                    0x020Cu
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTPUBKEYLEN                    0x020Du
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTSIGNLEN                      0x020Eu
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECTVERIFYDATA                   0x020Fu
#  define TCPIP_TLS_ERRORID_CTHS_NOPSKIDENTITYFOUND                    0x0210u
#  define TCPIP_TLS_ERRORID_CTHS_NOVALIDCIPHERFOUND                    0x0211u
#  define TCPIP_TLS_ERRORID_CTHS_PSKHINTTOLARGE                        0x0212u
#  define TCPIP_TLS_ERRORID_CTHS_PSKHINTNOTINRANGE                     0x0213u
#  define TCPIP_TLS_ERRORID_CTHS_PSKHINTMSGINVALIDLENGTH               0x0214u
#  define TCPIP_TLS_ERRORID_CTHS_INCORRECT_TIME                        0x0215u

/* APPLICATION DATA ERROR IDS 0x0300 - 0x0400 */
/* HEARTBEAT ERROR IDS 0x0500 - 0x05FF */
/* ALERT ERROR IDS 0x0600 - 0x06FF */
#  define TCPIP_TLS_ERRORID_ALERT_LENGTH_INVALID                       0x0600u
/* CRYPTO ERROR IDS 0x0700 - 0x0800 */
#  define TCPIP_TLS_ERRORID_CRYPTO_SET_VALID_FAILED                    0x0700u
#  define TCPIP_TLS_ERRORID_CRYPTO_CSM_CALL_FAILED                     0x0701u
#  define TCPIP_TLS_ERRORID_CRYPTO_CSM_LEN_MISMATCH                    0x0702u
#  define TCPIP_TLS_ERRORID_CRYPTO_CSM_CALC_PRF_FAILED                 0x0703u
#  define TCPIP_TLS_ERRORID_CRYPTO_REDUCESHAREDKEY_FAILED              0x0704u
#  define TCPIP_TLS_ERRORID_CRYPTO_CALCMASTERSECRET_FAILED             0x0705u
#  define TCPIP_TLS_ERRORID_CRYPTO_DERIVEKEYBLOCK_FAILED               0x0706u
#  define TCPIP_TLS_ERRORID_CRYPTO_SERVERFINISHED_HASH_FAILED          0x0707u
#  define TCPIP_TLS_ERRORID_CRYPTO_SERVERFINISHED_VERIFY_FAILED        0x0708u
#  define TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_HASH_FAILED          0x0709u
#  define TCPIP_TLS_ERRORID_CRYPTO_CLIENTFINISHED_VERIFY_FAILED        0x070Au
#  define TCPIP_TLS_ERRORID_CRYPTO_SETCSMKEYS_FAILED                   0x070Bu
#  define TCPIP_TLS_ERRORID_CRYPTO_CALCHMAC_FAILED                     0x070Cu
#  define TCPIP_TLS_ERRORID_CRYPTO_CLEARCSMKEY_FAILED                  0x070Du
#  define TCPIP_TLS_ERRORID_CRYPTO_GENERATEIVRANDOM_FAILED             0x070Eu
#  define TCPIP_TLS_ERRORID_CRYPTO_SETAESIVVALUE_FAILED                0x070Fu
#  define TCPIP_TLS_ERRORID_CRYPTO_DERIVEKEYS_FAILED                   0x0710u
#  define TCPIP_TLS_ERRORID_CRYPTO_RANDOMGENERATE_FAILED               0x0711u
#  define TCPIP_TLS_ERRORID_CRYPTO_ENCRYPTION_FAILED                   0x0712u
#  define TCPIP_TLS_ERRORID_CRYPTO_MACVERIFY_FAILED                    0x0713u
#  define TCPIP_TLS_ERRORID_CRYPTO_REDUCEKEY_FAILED                    0x0714u
#  define TCPIP_TLS_ERRORID_CRYPTO_GENERATESIGNATURE_FAILED            0x0715u
#  define TCPIP_TLS_ERRORID_CRYPTO_CSM_KEYELEMENTSET_FAILED            0x0716u
#  define TCPIP_TLS_ERRORID_CRYPTO_CSM_KEYELEMENTCOPYPARTIAL_FAILED    0x0717u
/* KEYM ERROR IDS 0x0900 - 0x0A00 */
#  define TCPIP_TLS_ERRORID_KEYM_GETCERTIFICATE_FAILED                 0x0900u
#  define TCPIP_TLS_ERRORID_KEYM_INVALIDCERTSTATUS                     0x0901u
#  define TCPIP_TLS_ERRORID_KEYM_GETCERTIFICATESTATUS_FAILED           0x0902u
#  define TCPIP_TLS_ERRORID_KEYM_SERVICE_OCSP_FAILED                   0x0903u
#  define TCPIP_TLS_ERRORID_KEYM_INVALIDOCSPSTATUS                     0x0904u

#  define TCPIP_TLS_ERRORID_NOT_SET                                    0xFFFFu

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
typedef struct
{
  uint32 KeyId; /* KeyId of the CsmKey */
  uint32 KeyElementId; /* KeyElementId of the crypto driver CryptoKeyElement */
  uint32 KeyLen;
} TcpIp_TlsCsmKeyInfoType;

typedef struct
{
  uint8* DataPtr; /* Pointer to the DataPtr of the first segment */
  uint16 DataLen; /* Length of the DataPtr of the first segment */
} TcpIp_TlsDataSplitType;

typedef TCPIP_P2V(uint8) TcpIp_TlsServerCertPtrType;

#  define TCPIP_TLS_CSM_INV_KEY_ID 0xFFFFFFFF
#  define TCPIP_TLS_CSM_INV_JOB_ID 0xFFFFFFFF

typedef void(*TcpIp_TlsGetRandomArrayType)(uint8* DestDataPtr, uint16 DestLen);

typedef struct
{
  TcpIp_TlsFunctionIdType FunctionId;    /* Identifies the function from which the error was reported */
  TcpIp_TlsUserErrorIdType UserErrorId;  /* Identifies the type of error */
  TcpIp_TlsConnectionIdType TlsConId;    /* Current connection on which the error occurred */
} TcpIp_TlsUserErrorType;                /* Used to report errors within the TLS module */

/* User callout function for TLS errors */
typedef void(*TcpIp_TlsUserErrorCalloutFunctionType)(uint32 TlsConIdx, uint32 UserErrorCnt);

/* Start of AsrTls types */


/* BER types tag values */
#  define TCPIP_BER_SEQUENCE          0x10u
#  define TCPIP_BER_INTEGER           0x02u

/* AsrTls Server/Client modes for the connection */
typedef enum  eTcpIp_TlsConnectionMode
{
  TCPIP_TLS_SERVER,
  TCPIP_TLS_CLIENT
} TcpIp_TlsConnectionMode; /* Used to determine the mode of the connection */

/* AsrTls states for the connection */
typedef enum  eTcpIp_TlsConnectionState
{
  TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE = 0u,
  TCPIP_TLS_STATE_CONNECTION_HS_ACTIVE,                                                             /* TLS Handshake is in progress */
  TCPIP_TLS_STATE_CONNECTION_SERVER_HS_FINALIZING,                                                  /* (For TlsServer) TLS Client Finished generating and parsing is under process, but TLS application data could be received */
  TCPIP_TLS_STATE_CONNECTION_ESTABLISHED,                                                           /* Handshake is complete, TLS connection is established */
  TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED,                                                   /* TLS received the TCP event RST and the processing of this RST is requested */
  TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING,               /* Same as TCPIP_TLS_STATE_CONNECTION_TCP_RESET_REQUESTED but without forwarding the events to the upper layer (TLS-Server connection during HS) */
  TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED,                                        /* TLS should close the TCP connection gracefully - triggers FIN on TCP level */
  TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED_WITHOUT_UPPERLAYER_EVENT_FORWARDING,    /* Same as TCPIP_TLS_STATE_CONNECTION_GRACEFULLY_TCP_CLOSE_REQUESTED but without forwarding the events to the upper layer (TLS-Server connection during HS) */
  TCPIP_TLS_STATE_CONNECTION_CLOSING,                                                               /* TLS Close requested and TLS connection is closing */
  TCPIP_TLS_STATE_CONNECTION_CLOSING_WITHOUT_UPPERLAYER_EVENT_FORWARDING,                           /* Same as TCPIP_TLS_STATE_CONNECTION_CLOSING but without forwarding the events to the upper layer (TLS-Server connection during HS) */
  TCPIP_TLS_STATE_CONNECTION_CLOSED,                                                                /* TLS connection is closed */
  TCPIP_TLS_STATE_CONNECTION_CLOSE_WAIT,                                                            /* TCP FIN received and TLS connection is waiting for user to decide how to close (TcpIp_Close()) */
  TCPIP_TLS_STATE_CONNECTION_CLOSE_WITH_CLOSENOTIFY_REQUESTED,                                      /* TLS connection should close by sending the CloseNotify alert */
  TCPIP_TLS_STATE_CONNECTION_CLOSENOTIFY_WAIT,                                                      /* TLS connection waits until requested transmit of CloseNotify is processed */
  TCPIP_TLS_STATE_CONNECTION_USER_RESET_REQUESTED,                                                  /* User called TcpIp_Close with Abort=TRUE - triggers RST on TCP level */
  TCPIP_TLS_STATE_CONNECTION_USER_RESET_WAIT,                                                       /* TLS connection waits until requested transmit of RST is processed */
  TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CANCLED,                                                     /* Active TLS handshake should be canceled (Tls-Listener closed with Abort = TRUE) */
  TCPIP_TLS_STATE_CONNECTION_ACTIVE_HS_CLOSED,                                                      /* Active TLS handshake should be closed (Tls-Listener closed with Abort = FALSE) */
  TCPIP_TLS_STATE_CONNECTION_ALLOCATED                                                              /* TLS connection is assigned to TCP socket, but TCP connection is not yet established */
} TcpIp_TlsConnectionState; /* States of the TLS connection */


typedef uint16 TcpIp_TlsEllipticCurveIdType;
#  define TCPIP_CURVE_ID_NO_CURVE   0x0000u  /* ( 0) */
#  define TCPIP_CURVE_ID_SECP256R1  0x0017u  /* (23) */
#  define TCPIP_CURVE_ID_SECP384R1  0x0018u  /* (24) */
#  define TCPIP_CURVE_ID_SECP521R1  0x0019u  /* (25) */
#  define TCPIP_CURVE_ID_X25519     0x001Du  /* (29) */
#  define TCPIP_CURVE_ID_X448       0x001Eu  /* (30) */


typedef enum  eTcpIp_TlsClientHsTriggerState
{
  TCPIP_TLS_CLIENTHSTRIGGER_INIT = 0u,
  TCPIP_TLS_CLIENTHSTRIGGER_TCPACK_SENDING,
  TCPIP_TLS_CLIENTHSTRIGGER_TCPACK_SENT,
  TCPIP_TLS_CLIENTHSTRIGGER_ACTIVE,
  TCPIP_TLS_CLIENTHSTRIGGER_TRIGGERED
} TcpIp_TlsClientHsTriggerStateType; /* Used to trigger the Tls client handshake hello */

typedef enum  eTcpIp_TlsCertState
{
  TCPIP_TLS_CERT_EMPTY = 0,             /**< Certificate data is not available */
  TCPIP_TLS_CERT_READY_TO_LOAD,         /**< Certificate data is ready to load */
  TCPIP_TLS_CERT_PARSE_IN_PROGRESS,     /**< Certificate data is being parsed */
  TCPIP_TLS_CERT_PARSED,                /**< Certificate data has been parsed */
  TCPIP_TLS_CERT_VERIFY_IN_PROGRESS,    /**< Certificate data is being verified */
  TCPIP_TLS_CERT_VERIFIED,              /**< Certificate data is verified */
  TCPIP_TLS_CERT_INVALID                /**< Certificate data is invalid */
} TcpIp_TlsCertStateType; /* Used to handle the Tls certificate verification state */

/* Status of Server certificate chain validation */
typedef enum  eTcpIp_TlsCertChainState
{
  TCPIP_TLS_CERTCHAIN_INIT = 0u,      /**< Certificate chain init state */
  TCPIP_TLS_CERTCHAIN_IN_PROGRESS,     /**< Certificate chain is parsed and verification is in progress */
  TCPIP_TLS_CERTCHAIN_VERIFY_FAILED,   /**< Certificate chain verification has failed but validation is in progress */
  TCPIP_TLS_CERTCHAIN_FINISHED,        /**< Certificate chain validation is finished */
  TCPIP_TLS_CERTCHAIN_COMPLETE,        /**< Certificate chain processing is complete */
  TCPIP_TLS_CERTCHAIN_INVALID          /**< Invalid state of certificate chain */
} TcpIp_TlsCertChainStateType; /* Used to determine the states of certificate chain processing */



typedef enum eTcpIp_Tls_CertStatusUpdateMode
{
  TCPIP_TLS_UPDATE_CERT_MODE_OCSP = 0u,
  TCPIP_TLS_UPDATE_CERT_MODE_CHAIN
} TcpIp_Tls_CertStatusUpdateModeType;


/* Certificate Group Identifier */
typedef uint16 TcpIp_CertificateGroupIdType;

typedef struct
{
  uint32 certDataLength;
  TCPIP_P2C(uint8) certData;
} TcpIp_CertDataType;

/* ECC private key lengths (RFC5114) */
#  define TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN 32u
#  define TCPIP_CURVE_ID_SECP384R1_PRIVKEY_LEN 48u
#  define TCPIP_CURVE_ID_SECP521R1_PRIVKEY_LEN 65u

/* ECC public key lengths (RFC5114, RFC7748) */
#  define TCPIP_CURVE_ID_SECP256R1_PUBKEY_LEN (TCPIP_CURVE_ID_SECP256R1_PRIVKEY_LEN + 32u)
#  define TCPIP_CURVE_ID_SECP384R1_PUBKEY_LEN (TCPIP_CURVE_ID_SECP384R1_PRIVKEY_LEN + 48u)
#  define TCPIP_CURVE_ID_SECP521R1_PUBKEY_LEN (TCPIP_CURVE_ID_SECP521R1_PRIVKEY_LEN + 65u)
#  define TCPIP_CURVE_ID_X25519_PUBKEY_LEN    32u
#  define TCPIP_CURVE_ID_X448_PUBKEY_LEN      56u
/* Maximum public key length, has to be examined whether an adjustment is needed if a new curve is introduced */
#  define TCPIP_MAX_PUBKEY_LEN                TCPIP_CURVE_ID_SECP521R1_PUBKEY_LEN

/* ECC shared value (Diffie-Hellman output) lengths (RFC5114, RFC7748 ) */
#  define TCPIP_CURVE_ID_SECP256R1_SHAREDKEY_LEN  32u
#  define TCPIP_CURVE_ID_SECP384R1_SHAREDKEY_LEN  48u
#  define TCPIP_CURVE_ID_SECP521R1_SHAREDKEY_LEN  65u
#  define TCPIP_CURVE_ID_X25519_SHAREDKEY_LEN     32u
#  define TCPIP_CURVE_ID_X448_SHAREDKEY_LEN       56u

/* ECDSA Signature lengths (RFC5114, RFC7748 ) */
#  define TCPIP_CURVE_ID_SECP256R1_SIGNATURE_LEN        64u
#  define TCPIP_CURVE_ID_SECP256R1_SIGN_BERELEM_LEN     32u
#  define TCPIP_CURVE_ID_SECP256R1_SIGNATURE_LEN        64u
#  define TCPIP_CURVE_ID_ED25519_SIGNATURE_LEN          64u
#  define TCPIP_TLS_MAX_SIGNATURE_LEN                   TCPIP_CURVE_ID_SECP256R1_SIGNATURE_LEN


#  define TCPIP_TLS_ASN1_SIG_TYPE_LEN      1u
#  define TCPIP_TLS_ASN1TAG_INTEGER_ID   0x02
#  define TCPIP_TLS_ASN1TAG_SEQUENCE_ID  0x30

#  define TCPIP_TLS_PREMASTERSECRET_COORDINATE_SIZE 32u

/* AES128 specific macros */
#  define TCPIP_TLS_AES128_BLOCKSIZE     16u

/* Minimum size of Tls buffer required to start streaming */
#  define TCPIP_TLS_MIN_BUFFER_SIZE      (4u * TCPIP_TLS_AES128_BLOCKSIZE)

typedef enum e_TcpIp_SignatureAlgorithmIdType
{
  TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA256        = 0x0401,
  TCPIP_SIG_ALGO_ID_ECDSA_SECP256R1_SHA256  = 0x0403,
  TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA384        = 0x0501,
  TCPIP_SIG_ALGO_ID_ECDSA_SECP384R1_SHA384  = 0x0503,
  TCPIP_SIG_ALGO_ID_RSA_PKCS1_SHA512        = 0x0601,
  TCPIP_SIG_ALGO_ID_ECDSA_SECP521R1_SHA512  = 0x0603,
  TCPIP_SIG_ALGO_ID_ECDSA_ED25519_INTRINSIC = 0x0807,
  TCPIP_SIG_ALGO_ID_ECDSA_ED448_INTRINSIC   = 0x0808
}TcpIp_SignatureAlgorithmIdType;

#  define TCPIP_TLS_SIGNATURE_ALGO_ANONYMOUS   0u
#  define TCPIP_TLS_SIGNATURE_ALGO_RSA         1u
#  define TCPIP_TLS_SIGNATURE_ALGO_DSA         2u
#  define TCPIP_TLS_SIGNATURE_ALGO_ECDSA       3u

/* For further information on the context handling within the TLS see TLS EAP Design. */
typedef enum e_TcpIp_AsyncCtxStateType
{
  TCPIP_TLS_CTX_NO_ASYNC      = 0u, /* No async/LowPrio operation active */
  TCPIP_TLS_CTX_DONE          = 1u, /* Async/LowPrio operation done - Used in context of TcpIp_TlsCoreMainFunction_LowPrio (time consuming operation) and TcpIp_TlsCoreMainFunction_State (wait cycle) */
  TCPIP_TLS_CTX_ASYNC_PENDING = 3u, /* Async/LowPrio operation pending (LowPrioTask active) - Used in context of TcpIp_TlsCoreMainFunction_State */
  TCPIP_TLS_CTX_WAIT_CYCLE    = 4u  /* Wait cycle - Used if next logical TLS message not received yet - Used in context of TcpIp_TlsCoreMainFunction_State */
} TcpIp_AsyncCtxStateType;


typedef uint16 TcpIp_TlsHandshakeState;
#  define TCPIP_TLS_STATE_HANDSHAKE_INIT                                                                        0x0000u  /* Initial connection state after reset */

/* TLS HelloMessage states */
#  define TCPIP_TLS_STATE_SEND_CLIENT_HELLO                                                                     0x1000u  /* Client: Connection state while sending Client_Hello */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_HELLO                                                                 0x1100u  /* Server: Connection state while waiting for incoming Client_Hello message */
#  define TCPIP_TLS_STATE_SEND_SERVER_HELLO                                                                     0x1200u  /* Server: Connection state while sending Server_Hello */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO                                                                 0x1300u  /* Client: Connection state while waiting for incoming Server_Hello message */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION                                             0x1301u  /* Client: Sub state of ServerHello - extract the received server hello information */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_STATE_CHANGE                                0x1302u  /* Client: Sub state of ServerHello - determine next state */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_EXTRACT_INFORMATION_DONE                                        0x13FFu  /* Client: Sub state of ServerHello - all Sub state finished */

/* TLS CertificateMessage states */
#  define TCPIP_TLS_STATE_SEND_SERVER_CERTIFICATE                                                               0x1400u  /* Server: Connection state while sending Server_Certificate */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE                                                           0x1500u  /* Client: Connection state while waiting for incoming Server_Certificate message */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_LOADCERTS                                                 0x1501u  /* Client: Sub state of ServerCertificate - setting certificates into KeyM certs */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_CHECK                                         0x1502u  /* Client: Sub state of ServerCertificate - check if KeyM has finished the cert chain validation */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_VERIFYGROUP_STATUS                                        0x1503u  /* Client: Sub state of ServerCertificate - calc cert and cert chain status */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DETERMINE_NEXT_STATE                                      0x1504u  /* Client: Sub state of ServerCertificate - determine next state */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_DONE                                                      0x15FFu  /* Client: Connection state server certificates processing done */

/* TLS CertificateStatus state */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS                                                    0x1600u  /* Client: Connection state while waiting for incoming */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_GET_CERT_STATUS                                    0x1601u  /* Client: Sub state of CeritificateStatus */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_TRIGGER_OCSP_VALIDATION                            0x1602u  /* Client: Sub state of CeritificateStatus */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_UPDATE_CERT_STATUS                                 0x1603u  /* Client: Sub state of CeritificateStatus */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DETERMINE_NEXT_STATE                               0x1604u  /* Client: Sub state of CeritificateStatus */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_STATUS_DONE                                               0x16FFu  /* Client: */

/* TLS KeyExchangeMessage states */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE                                                              0x1700u  /* Server: Connection state while sending Server_Key_Exchange */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_HDR                                                      0x1710u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS                                             0x1720u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_ADD_DH                                      0x1721u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_ADD_SIGNATURE                               0x1722u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_DECODE_SIGNATURE                            0x1723u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_ECDHE_PARAMS_DONE                                        0x172Fu  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_PSK_PARAMS                                               0x1730u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_PSK_PARAMS_ADD_IDENTITY_HINT                             0x1731u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_ADD_PSK_PARAMS_DONE                                          0x173Fu  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_TRIGGER_TX                                                   0x1740u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_KEY_EXCHANGE_DONE                                                         0x17FFu  /* Server: */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE                                                          0x1800u  /* Client: Connection state while waiting for incoming Server_Key_Exchange message */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_GET_SERVER_PARAMS                                        0x1801u  /* Client: get parameters from server key exchange */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_VERIFY_SIGNATURE                                         0x1802u  /* Client: validate signature */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_WAIT_FOR_ASYNC                                           0x1803u  /* Client: Wait for async operations */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DETERMINE_NEXT_STATE                                     0x1804u  /* Client: */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_KEY_EXCHANGE_DONE                                                     0x18FFu  /* Client: move to next state */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CERTIFICATE_REQUEST                                                   0x1900u  /* Client: */

#  define TCPIP_TLS_STATE_SEND_SERVER_HELLO_DONE                                                                0x2000u  /* Server: Connection state while sending Hello_Done */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_HELLO_DONE                                                            0x2100u  /* Client: Connection state while waiting for incoming Hello_Done message */

#  define TCPIP_TLS_STATE_SEND_CLIENT_CERTIFICATE                                                               0x2200u   /* Client: */

#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE                                                              0x2300u  /* Client: Connection state while sending Client_Key_Exchange */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_DH                                                       0x2301u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_PSK_ID                                                   0x2306u  /* Client */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_ADD_MSG_LENGTH                                               0x2302u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET                                        0x2303u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_PSK_SHARED_SECRET                                       0x2307u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET                                           0x2304u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC                                               0x2305u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_KEY_EXCHANGE_DONE                                                         0x23FFu  /* Client: */

#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE                                                          0x2400u  /* Server: Connection state while waiting for incoming Client_Key_Exchange message */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_GET_CLIENT_PARAMS                                        0x2401u  /* only used if PSK not supported */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_CALC_DH_SHARED_SECRET                                    0x2402u  /* only used if PSK not supported */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS                        0x2410u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_GET_PARAMS             0x2411u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_CALC_DH_SHARED_SECRET  0x2412u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_ECDHE_ECDSA_CLIENT_PARAMS_DONE                   0x241Fu
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS                                0x2420u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_GET_PARAMS                     0x2421u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_CALC_PREMASTER_SECRET          0x2422u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_PROCESS_PSK_CLIENT_PARAMS_DONE                           0x242Fu
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_CALC_MASTER_SECRET                                       0x2430u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_WAIT_FOR_ASNYC                                           0x2440u
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_KEY_EXCHANGE_DONE                                                     0x24FFu

#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_CCS                                                                   0x2500u  /* */
#  define TCPIP_TLS_STATE_SEND_CLIENT_CCS                                                                       0x2600u  /* */
/* TLS ClientFinishedMessage states */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED                                                                  0x2700u  /* Client: Connection state while sending Client_Finished */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_ADD_HDR                                                          0x2701u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_CALC_HASH                                                        0x2702u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_CALC_FINISHED                                                    0x2703u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_TRIGGER_TX                                                       0x2704u  /* Client: */
#  define TCPIP_TLS_STATE_SEND_CLIENT_FINISHED_DONE                                                             0x27FFu  /* Client: */

#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED                                                              0x2800u  /* Server: Connection state while waiting for incoming Client_Finished message */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_GET_CLIENT_PARAMS                                            0x2801u  /* Server: Extract the Verify data */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_HASH                                                    0x2802u  /* Server: Calculate the Hash */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_CALC_FINISHED                                                0x2803u  /* Server: Calculate the Verify data */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_VERIFY                                                       0x2804u  /* Server: Compare the data */
#  define TCPIP_TLS_STATE_WAIT_FOR_CLIENT_FINISHED_DONE                                                         0x28FFu  /* Server: Move to next step */

#  define TCPIP_TLS_STATE_SEND_SERVER_CCS                                                                       0x2900u  /* */
/* TLS ServerFinishedMessage states */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED                                                                  0x3000u  /* Server: Connection state while sending Server_Finished */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED_ADD_HDR                                                          0x3001u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED_CALC_HASH                                                        0x3002u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED_CALC_FINISHED                                                    0x3003u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED_TRIGGER_TX                                                       0x3004u  /* Server: */
#  define TCPIP_TLS_STATE_SEND_SERVER_FINISHED_DONE                                                             0x30FFu  /* Server: */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_CCS                                                                   0x3100u  /* Server: Wait for server Ccs message */

#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED                                                              0x3200u  /* Client: Connection state while waiting for incoming Server_Finished message */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_GET_CLIENT_PARAMS                                            0x3201u  /* Client: Extract the Verify data */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_HASH                                                    0x3202u  /* Client: Calculate the Hash */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_CALC_FINISHED                                                0x3203u  /* Client: Calculate the Verify data */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_VERIFY                                                       0x3204u  /* Client: Compare the data */
#  define TCPIP_TLS_STATE_WAIT_FOR_SERVER_FINISHED_DONE                                                         0x32FFu  /* Client: Move to next step */

#  define TCPIP_TLS_STATE_HANDSHAKE_DONE                                                                        0xFE00u  /* Connection state when handshake performed successfully */
#  define TCPIP_TLS_STATE_HANDSHAKE_ABORT                                                                       0xFF00u  /* Connection state when handshake failed */


typedef enum eTcpIp_TlsCalcKeyMaterialState
{
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_INIT               = 0x0u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_REDUCE_SHARED_KEY  = 0x1u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_CALC_MASTER_SECRET = 0x2u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DERIVE_KEY_BLOCK   = 0x3u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_SET_CSM_KEYS       = 0x4u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_FINALIZE           = 0x5u,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_DONE               = 0xEu,
  TCPIP_TLS_STATE_CALC_KEY_MATERIAL_ABORT              = 0xFu
} TcpIp_TlsCalcKeyMaterialState; /* Used to determine the active state of the TLS key material calculation */

typedef P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) TcpIp_TlsDataPtrType; /* Used in RxBufStruct as data pointer Type */

/* Use IANA names */
typedef uint16 TcpIp_TlsCipherDataType;
#  define TCPIP_TLS_CIPHER_SUITE_LEN                         2u
/* COMMON */
#  define TCPIP_TLS_NULL_WITH_NULL_NULL                 0x0000u /* Used during HS */
#  define TCPIP_TLS_CIPHER_INVALID                      0xFFFFu /* INVALID */

/* ECDHE_ECDSA */
#  define TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 0xC023u
#  define TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA    0xc009u
#  define TCPIP_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 0xC02Bu
#  define TCPIP_TLS_ECDHE_ECDSA_WITH_NULL_SHA           0xC006u

/* ECDH_ECDSA */
#  define TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256  0xC025u
#  define TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA     0xC004u
#  define TCPIP_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256  0xC02Du
#  define TCPIP_TLS_ECDH_ECDSA_WITH_NULL_SHA            0xC001u

/* PSK */
#  define TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA256         0x00AEu
#  define TCPIP_TLS_PSK_WITH_AES_128_CBC_SHA            0x008Cu
#  define TCPIP_TLS_PSK_WITH_AES_128_GCM_SHA256         0x00A8u
#  define TCPIP_TLS_PSK_WITH_NULL_SHA                   0x002Cu
#  define TCPIP_TLS_PSK_WITH_NULL_SHA256                0x00B0u


#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Defines like in the next 3 types could start their valid values with 1 and use 0 as the invalid value. Maybe this could help to find not initialized variables. */
/* [REVIEW_c] comment visbdk: Don't think so, because these values are only used in the switch case condition */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
typedef uint8 TcpIp_TlsCipherStreamingModeDataType;
#  define TCPIP_TLS_STREAMING_MODE_NULL                      0u
#  define TCPIP_TLS_STREAMING_MODE_AES_128_CBC               1u
#  define TCPIP_TLS_STREAMING_MODE_AES_128_GCM               2u
#  define TCPIP_TLS_STREAMING_MODE_AES_256_GCM               3u
#  define TCPIP_TLS_STREAMING_MODE_CHACHA20_POLY1305         4u
#  define TCPIP_TLS_STREAMING_MODE_INVALID                0xffu

typedef uint8 TcpIp_TlsKeyExchangeMethodDataType;
#  define TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE                 0u
#  define TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH                  1u
#  define TCPIP_TLS_KEYEXCHANGE_METHOD_RSA                   2u
#  define TCPIP_TLS_KEYEXCHANGE_METHOD_PSK                   3u
#  define TCPIP_TLS_KEYEXCHANGE_METHOD_INVALID            0xffu

typedef uint8 TcpIp_TlsMessageAuthenticationModeDataType;
#  define TCPIP_TLS_MSG_AUTH_MODE_NONE                       0u
#  define TCPIP_TLS_MSG_AUTH_MODE_SHA1                       1u
#  define TCPIP_TLS_MSG_AUTH_MODE_SHA256                     2u
#  define TCPIP_TLS_MSG_AUTH_MODE_SHA384                     3u
#  define TCPIP_TLS_MSG_AUTH_MODE_INVALID                 0xffu

typedef uint8 TcpIp_TlsMessageFinishedType;
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Add a note that these enum values may not be changed / have to be zero-based because they are used to access the array TcpIp_Tls_Hs_FinishedLabel. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.01.00.7 Statement: OK */
#  endif
/* Index defines are used to access the array TcpIp_Tls_Hs_FinishedLabel - Do not change the order */
#  define TCPIP_TLS_MSG_HASH_SERVER_FINISHED                0u
#  define TCPIP_TLS_MSG_HASH_CLIENT_FINISHED                1u

/* User callout function for TLS get time */
typedef Std_ReturnType (*TcpIp_TlsGetTimeCalloutFunctionType)(TCPIP_CP2V(uint32) GmtUnixTime);




/* End of AsrTls types */
/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
#endif /* TCPIP_TLS_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: TcpIp_Tls_Types.h
 **********************************************************************************************************************/
