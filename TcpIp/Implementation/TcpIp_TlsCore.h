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
/*!        \file  TcpIp_TlsCore.h
 *        \brief
 *
 *      \details This file is part of the TcpIp TLS submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/

#if !defined (TCPIP_TLSCORE_H)
# define TCPIP_TLSCORE_H

# include "TcpIp_Cfg.h"
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "Std_Types.h"
#  include "TcpIp_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* maybe in TcpIp_TlsPriv.h */

/* TLS PSK support switch */
#  define TCPIP_SUPPORT_TLSPSKCIPHER  STD_ON
#  define TCPIP_SUPPORT_TLSPSKCIPHER_ALERT STD_ON

/* TLS constant length information */
#  define TCPIP_TLS_RLHDRLEN                            5u /* Length of the record layer header */
#  define TCPIP_TLS_HSHDRLEN                            4u /* Length of the handshake header */
#  define TCPIP_TLS_HSLEN_LEN                           3u /* Length of the handshake header length field */
#  define TCPIP_TLS_CTLEN_LEN                           2u /* Length of the content type length field */
#  define TCPIP_TLS_CT_LEN                              1u /* Length of the content type */
#  define TCPIP_TLS_CT_ALERT_LEN                        2u /* Length of the alert type */
#  define TCPIP_TLS_CCSMSG_LEN                          1u /* Length of the change cipher spec message */
#  define TCPIP_TLS_RANDOM_LEN                         32u /* Length of the random value in the hello message */
#  define TCPIP_TLS_LABEL_CLIENT_FINISHED_LEN          15u /* Length of the client finished label within the finished message */
#  define TCPIP_TLS_LABEL_SERVER_FINISHED_LEN          15u /* Length of the server finished label within the finished message */
#  define TCPIP_TLS_LABEL_MASTER_SECRET_LEN            13u /* Length of the master secret label */
#  define TCPIP_TLS_LABEL_KEY_EXPENSION_LEN            13u /* Length of the key expansion */
#  define TCPIP_TLS_MASTER_SECRET_LEN                  48u /* Length of the master secret */
#  define TCPIP_TLS_RL_SEQUENCE_NUM_LEN                 8u /* Length of the sequence number inside the record layer header */
#  define TCPIP_TLS_PRF_COMBINED_LABEL_LEN_MAX        100u /* Length of the combined PRF label */
#  define TCPIP_TLS_HASH_SHA256_LEN                    32u /* Length of the SHA256 hash */
#  define TCPIP_TLS_HASH_SHA1_LEN                      20u /* Length of the SHA1 hash */
#  define TCPIP_TLS_CRYPTO_SEED_LEN                    20u /* Length of the Crypto seed */
#  define TCPIP_TLS_TLS_PADDING_BYTE_LEN                1u /* Length of the TLS Padding Byte */
#  define TCPIP_TLS_FINISHED_VERIFYDATA_LEN            12u /* Length of the Verify Data in Finished Message */
#  define TCPIP_TLS_AES128_GCM_AUTHTAG_LEN             16u /* Length of the authentication tag for Aes128 Gcm */
#  define TCPIP_TLS_MAC_LEN_MAX                        32u /* Maximum length of the MAC */
#  define TCPIP_TLS_FINISHED_MESSAGE_LEN               (TCPIP_TLS_FINISHED_VERIFYDATA_LEN + TCPIP_TLS_HSHDRLEN)

#  define TCPIP_TLS_PSK_MAX_KEY_LENGTH                  64u
#  define TCPIP_TLS_PSK_PMS_PSK_LEN_FIELD_LEN           2u /* Length of psk length field in psk premaster secret */
#  define TCPIP_TLS_PSK_PMS_OTHER_SECRET_LEN_FIELD_LEN  2u /* Length of other secret length field in psk premaster secret */
#  define TCPIP_TLS_PSK_PMS_OTHER_SECRET_PLAIN_PATTERN  0u /* Other secret of plain psk premaster secret consists of zero bytes */
#  define TCPIP_TLS_MAX_EXTENSION_LIST_LENGTH           64u/* Maximum length of the extension list in server or client hello message  */

/* TLS Key Block sizes - key mat size = 2*(HMAC + AES-KEY + AES-IV) */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_NULL_SHA1           40u          /* Length of the key block with an SHA1 hash eg 0002, C001 */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_NULL_SHA256         64u          /* eg 003B */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_AES128_SHA1         72u          /* 0..19: TX MAC; 20..39: RX MAC; 40..55: TX Key; 56..71: RX Key */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_AES128_SHA256       96u          /* 0..31: TX MAC; 32..63: RX MAC; 64..79: TX Key; 80..95: RX Key */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_AES128_GCM          (2*(16 + 4)) /* AES-KEY + SALT (The salt length (SecurityParameters.fixed_iv_length) is 4 octets.) */
#  define TCPIP_TLS_KEY_BLOCK_SIZE_UNSET               0u

#  define TCPIP_TLS_AES128_KEY_LEN                     16u /* Length of the AES128 key */
#  define TCPIP_TLS_AES_BLOCK_LEN                      16u /* Length of one AES block */
#  define TCPIP_TLS_AES128_IV_LEN                      16u /* The initialization vector (IV) always has the same length as the block */

/* TLS key sizes for AEAD Aes128 Gcm */
#  define TCPIP_TLS_AES128_GCM_KEY_LEN                 16u /* Length of the AES128 GCM key */
#  define TCPIP_TLS_AES128_GCM_BLOCK_LEN               16u /* Length of one AES block */
#  define TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN          4u /* The initialization vector (IV) for GCM is 4 bytes */
#  define TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN          8u /* Length of the explicit nonce for Aes128 Gcm */
#  define TCPIP_TLS_AES128_GCM_IV_LEN                  (TCPIP_TLS_AES128_GCM_IMPLICIT_IV_LEN + TCPIP_TLS_AES128_GCM_EXPLICIT_IV_LEN) /* Length of the total nonce for Aes128 Gcm */
#  define TCPIP_TLS_AES128_GCM_AADATA_LEN              13u /* Length of the additional authentication data for Aes128 Gcm */

/* Padding length */
#  define TCPIP_TLS_TLS_PADDING_LEN                     1u /* Length of padding bytes */

/* Additional authentication data offsets and lengths */
#  define TCPIP_TLS_ADD_SEQNUM_LEN                      TCPIP_TLS_RL_SEQUENCE_NUM_LEN  /* length of sequence number */
#  define TCPIP_TLS_ADD_TYPE_LEN                        1u  /* length of type */
#  define TCPIP_TLS_ADD_VER_LEN                         2u  /* length of version */
#  define TCPIP_TLS_ADD_LEN_LEN                         2u  /* length of content data len */

#  define TCPIP_TLS_ADD_SEQNUM_OFFSET                   0u  /* Offset for sequence number */
#  define TCPIP_TLS_ADD_TYPE_OFFSET                     (TCPIP_TLS_ADD_SEQNUM_OFFSET + 8u) /* offset for type */
#  define TCPIP_TLS_ADD_VER_OFFSET                      (TCPIP_TLS_ADD_TYPE_OFFSET + 1u) /* offset for version */
#  define TCPIP_TLS_ADD_LEN_OFFSET                      (TCPIP_TLS_ADD_VER_OFFSET + 2u) /* offset for length */

/* Offsets within the record layer header */
#  define TCPIP_TLS_RLLEN_OFFSET                        3u /* Offset to the length information */
#  define TCPIP_TLS_RLCT_OFFSET                         0u /* Offset to the content type information */
#  define TCPIP_TLS_RLVERSMAJOR_OFFSET                  1u /* Offset to the major version information */
#  define TCPIP_TLS_RLVERSMINOR_OFFSET                  2u /* Offset to the minor version information */
#  define TCPIP_TLS_RLLENHIGH_OFFSET                    3u /* Offset to the length (high byte) information */
#  define TCPIP_TLS_RLLENLOW_OFFSET                     4u /* Offset to the length (low byte) information */

/* Offsets within the Content type Handshake header */
#  define TCPIP_TLS_HSHDRLEN_OFFSET                     1u /* Offset to the length information */

/* Offsets within the content type alert */
#  define TCPIP_TLS_ALERTLEVEL_OFFSET                   0u /* Offset to the Alert level */
#  define TCPIP_TLS_ALERTDESCRIPTION_OFFSET             1u /* Offset to the Alert description */

#  define TCPIP_TLS_CONTENT_TYPE_OFFSET                      0u /* Offset to the content type */
#  define TCPIP_TLS_CONTENT_LENGTH_OFFSET                    1u /* Offset to the content type length information */

#  define TCPIP_TLS_CHANGECIPHERSPEC                 0x01u /* Content of the change cipher spec message */

/* TLS content types - RFC 5246 - Appendix A.1. Protocol Data Structures and Constant Values */
#  define TCPIP_TLS_CT_CCS                            0x14u /* TLS content type Change Cipher Spec (CCS) */
#  define TCPIP_TLS_CT_AL                             0x15u /* TLS content type Alert (AL) */
#  define TCPIP_TLS_CT_HS                             0x16u /* TLS content type Handshake (HS) */
#  define TCPIP_TLS_CT_AD                             0x17u /* TLS content type Application Data (AD) */

/* Maximum length of TLS header fields in a TLS Rl frame */
#  define TCPIP_TLS_RL_FIELDS_LEN_MAX                 (TCPIP_TLS_RLHDRLEN + TCPIP_TLS_AES128_IV_LEN +\
                                                       TCPIP_TLS_MAC_LEN_MAX + TCPIP_TLS_TLS_PADDING_BYTE_LEN +\
                                                       TCPIP_TLS_AES_BLOCK_LEN)

typedef uint8 TcpIp_TlsMsgHandshakeType;
#  define TCPIP_TLS_HSTYPE_HELLOREQUEST                  0u /* TLS handshake type HelloRequest */
#  define TCPIP_TLS_HSTYPE_CLIENTHELLO                   1u /* TLS handshake type ClientHello */
#  define TCPIP_TLS_HSTYPE_SERVERHELLO                   2u /* TLS handshake type ServerHello */
#  define TCPIP_TLS_HSTYPE_CERTIFICATE                  11u /* TLS handshake type ServerCertificate */
#  define TCPIP_TLS_HSTYPE_SERVERKEYEXCHANGE            12u /* TLS handshake type ServerKeyExchange */
#  define TCPIP_TLS_HSTYPE_CERTIFICATEREQUEST           13u /* TLS handshake type CertificateRequest */
#  define TCPIP_TLS_HSTYPE_SERVERHELLODONE              14u /* TLS handshake type ServerHelloDone */
#  define TCPIP_TLS_HSTYPE_CERTIFICATEVERIFY            15u /* TLS handshake type CerficateVerify */
#  define TCPIP_TLS_HSTYPE_CLIENTKEYEXCHANGE            16u /* TLS handshake type ClientKeyExchange */
#  define TCPIP_TLS_HSTYPE_FINISHED                     20u /* TLS handshake type HsFinished */
#  define TCPIP_TLS_HSTYPE_CERTIFICATESTATUS            22u /* TLS handshake type CertificateStatus */
#  define TCPIP_TLS_HSTYPE_INVALID                    0xffu

/* TLS Supported major and minor version numbers */
#  define TCPIP_TLS_RL_VERSMAJOR                      0x03u
#  define TCPIP_TLS_RL_VERSMINOR                      0x03u

/* ALERT PROTOCOL - RFC5246 #Section-7.2 */
#  define TCPIP_TLS_ALERT_MSG_LEN                        2u
/* ALERT LEVEL */
typedef uint8 TcpIp_TlsAlertLevelType;
#  define TCPIP_TLS_ALERT_LEVEL_WARNING               0x01u
#  define TCPIP_TLS_ALERT_LEVEL_FATAL                 0x02u

/* Global Handshake macros */
#  define TCPIP_TLS_PROTOCOL_MAJOR_VERSION_3                            0x03u
#  define TCPIP_TLS_PROTOCOL_MINOR_VERSION_3                            0x03u
#  define TCPIP_TLS_COMPRESSION_METHOD_NONE                             0x00u
#  define TCPIP_TLS_CURVETYPE_NAMED_CURVE                               0x03u

/* Supported TLS Extensions */
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_INDICATION                  0x0000u
#  define TCPIP_TLS_EXTENSION_SUPPORTED_GROUPS                        0x000Au
#  define TCPIP_TLS_EXTENSION_EC_POINT_FORMAT                         0x000Bu
#  define TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS                    0x000Du
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION                   0x0003u
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST              0x0005u
#  define TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT                       0x001Cu

#  define TCPIP_TLS_PUBKEY_COMPRESSION_FLAG                             0x04u

#  define TCPIP_TLS_HSRANDOM_LEN                                                     28u
#  define TCPIP_TLS_SERVERHELLORANDOM_LEN                                            28u
#  define TCPIP_TLS_SERVERHELLODONE_LEN                                               0u

#  define TCPIP_TLS_MAJORVERS_LEN                                                     1u
#  define TCPIP_TLS_MINORVERS_LEN                                                     1u
#  define TCPIP_TLS_SESSIONIDLEN_LEN                                                  1u
#  define TCPIP_TLS_SESSIONIDMAX_LEN                                                 32u
#  define TCPIP_TLS_CIPHERSUITESLEN_LEN                                               2u
#  define TCPIP_TLS_COMPMETHLEN_LEN                                                   1u

/* TLS Extension static length and type information */
#  define TCPIP_TLS_EXTENSION_LENGTH_LEN                                              2u
#  define TCPIP_TLS_EXTENSION_ID_LEN                                                  2u
#  define TCPIP_TLS_EXTENSION_TYPE_LEN                                                2u
#  define TCPIP_TLS_EXTENSIONDATALEN_LEN                                              2u
#  define TCPIP_TLS_EXTENSION_LIST_LEN                                                2u
#  define TCPIP_TLS_EXTENSION_SUPPORTED_GROUP_LENGTH_LEN                              2u
#  define TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_LENGTH_LEN                         2u
#  define TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_SIGNATURE_OFFSET                   1u
#  define TCPIP_TLS_EXTENSION_SIGNATURE_ALGORITHMS_ALG_ID_LEN                         2u
#  define TCPIP_TLS_EXTENSION_EC_POINT_FORMATS_LENGTH_LEN                             1u
#  define TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_FIXED_LENGTH                            1u
#  define TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_LENGTH_LEN                              1u
#  define TCPIP_TLS_EXTENSION_EC_POINT_FORMAT_UNCOMPRESSED                            0u
/* RFC 6066 - 3.  Server Name Indication */
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_LIST_LENGTH_LEN                             2u
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_NAME_TYPE_LEN                               1u
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_NAME_LEN_LEN                                2u
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_SERVER_NAME_MIN_LEN  (TCPIP_TLS_EXTENSION_SERVER_NAME_NAME_TYPE_LEN + TCPIP_TLS_EXTENSION_SERVER_NAME_NAME_LEN_LEN)
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_TYPE_HOST_NAME                              0u
#  define TCPIP_TLS_EXTENSION_SERVER_NAME_HOST_NAME_MIN_LEN                           1u
/* RFC 6066 - 6.  Trusted CA Indication */
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_LIST_LEN                          2u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_TYPE_CERT_SHA1_HASH               3u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_INDICATION_TYPE_LEN                          1u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_PRE_AGREED                              0u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_KEY_SHA1_HASH                           1u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_X509_NAME                               2u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_CERT_SHA1_HASH                          3u
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_TYPE_LEN                                     1u  /* length of the type field */
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_LENGTH_LEN                                2u  /* length of distinguished name length field */
#  define TCPIP_TLS_EXTENSION_TRUSTED_CA_DN_MIN_LEN                                   1u  /* distinguished name must be at least 1 byte */
/* RFC 6066 - 8.  Certificate Status Request */
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_OCSP_TYPE                    1u
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_TYPE_LEN                     1u
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LIST_LEN        2u  /* length of the length field of the responder id list */
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LEN_LEN         2u  /* length of the length field of a responder id */
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_MIN_LEN         1u
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_TOTAL_MIN_LEN  (TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_LEN_LEN + TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_RESPONDER_ID_MIN_LEN)
#  define TCPIP_TLS_EXTENSION_CERTIFICATE_STATUS_REQUEST_REQUEST_EXTENSIONS_LEN       2u  /* length of the length field of the request extensions */
#  define TCPIP_TLS_EXTENSION_ELEMENT_LEN                                             2u
#  define TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_FIXED_LEN                             2u
#  define TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_VALUE_LEN                             2u
#  define TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MIN_VALUE                            64u
#  define TCPIP_TLS_EXTENSION_RECORD_SIZE_LIMIT_MAX_VALUE                            16384u /* 2^14 as defined per RFC 8449 */

/* Hello message information */
#  define TCPIP_TLS_UNIXTIMESTAMP_LEN                                                 4u
#  define TCPIP_TLS_VERSLEN                                                           2u
#  define TCPIP_TLS_RNDLEN                                                           32u
#  define TCPIP_TLS_CIPHERLENLEN                                                      2u

/* Certificate message information */
#  define TCPIP_TLS_CERTSLEN_LEN                                                      3u
#  define TCPIP_TLS_CERT_LEN                                                          3u

/* Certificate status request information */
#  define TCPIP_TLS_CERTSTATUS_REQUESTTYPE_LEN                                        1u
#  define TCPIP_TLS_CERTSTATUS_REQUESTTYPE_OCSP                                       1u
#  define TCPIP_TLS_CERTSTATUS_OCSPRESPONSE_LEN                                       3u

/* Certificate request information */
#  define TCPIP_TLS_CERTREQUEST_CERTTYPESLENGTH_LEN                                   1u
#  define TCPIP_TLS_CERTREQUEST_SIGNATUREHASHALGORITHMSLENGTH_LEN                     2u
#  define TCPIP_TLS_CERTREQUEST_DISTINGUISHEDNAMESLENGTH_LEN                          2u

/* ECC Key Exchange information */
#  define TCPIP_TLS_KEYEXCH_CURVETYPELEN                                              1u
#  define TCPIP_TLS_KEYEXCH_CURVENAMELEN                                              2u
#  define TCPIP_TLS_KEYEXCH_PUBKEYLEN                                                 1u
#  define TCPIP_TLS_KEYEXCH_COMPFLAGLEN                                               1u
#  define TCPIP_TLS_KEYEXCH_SIGALGOHASHLEN                                            1u
#  define TCPIP_TLS_KEYEXCH_SIGALGOSIGNLEN                                            1u
#  define TCPIP_TLS_KEYEXCH_SIGLENLEN                                                 2u
#  define TCPIP_TLS_KEYEXCH_PARAMETERLEN (TCPIP_TLS_KEYEXCH_CURVETYPELEN + TCPIP_TLS_KEYEXCH_CURVENAMELEN + TCPIP_TLS_KEYEXCH_PUBKEYLEN)
#  define TCPIP_TLS_KEYEXCH_ECC_PRIVKEYLEN                                           32u

/* PSK Key Exchange information */
#  define TCPIP_TLS_KEYEXCH_PSKIDLEN                                                 2u
#  define TCPIP_TLS_KEYEXCH_PSKIDMAXLEN                                            128u
#  define TCPIP_TLS_KEYEXCH_PSKIDHINTLEN                                             2u
#  define TCPIP_TLS_KEYEXCH_PSKIDHINTMAXLEN                                        128u

/* HelloDone information */
#  define TCPIP_TLS_HELLODONE_LEN                                         1u
#  define TCPIP_TLS_HELLOREQUEST_LEN                                      4u

/* Length of Client/Server Finished length */
#  define TCPIP_TLS_LABEL_FINISHED_LEN                                         15u

#  define TCPIP_CERTGROUPID_INV                                      0xFFFFu
#  define TCPIP_CERTID_INV                                           0xFFFFu

#  define TCPIP_TLSCONFIG_IDX                                             0u
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_FctLikeMacro */
#  define TCPIP_TLS_RXBUFFER_ISIDXINRANGE(READIDX, IDXOFFSET, ENDIDX)  ((((READIDX) + (IDXOFFSET)) <= (ENDIDX))\
                                            && ((ENDIDX) < TcpIp_GetSizeOfTlsBufferRx() ))

#  define TCPIP_TLS_USERERROR_PARSEHELLO(TlsConIdx)                    ((TcpIp_GetModeOfTlsConnection(TlsConIdx) == TCPIP_TLS_CLIENT)?\
                                                                      TCPIP_TLS_FCTID_CLIENT_HSSTM_PARSE_SERVERHELLO:TCPIP_TLS_FCTID_SERVER_HSSTM_PARSE_CLIENTHELLO)
#  define TCPIP_TLS_GET_HS_STATE(STATE)                                ( (uint16)STATE & 0xFF00u )
#  define TCPIP_TLS_GET_HS_SUB_STATE(STATE)                            ( (uint16)STATE & 0xFFF0u )

#  define TCPIP_TLS_HANDSHAKE_ID_IS_VALID(HS_ID)   ((HS_ID)  < TcpIp_GetSizeOfTlsHandshake())

/* PRQA L:FctLikeMacros */
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#  ifdef C_REVIEW_VECTOR                                                                                                /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Question: Do we really need an extern declaration here? */
/* [REVIEW_c] comment visbdk: I've got some compiler warnings without extern, because the definition of this object is in the c code.  */
/* [REVIEW_c] open visal 16.01.00.7 Improve: Then we probably have an issue with the include structure. As far as I understand extern declarations are only needed if the corresponding header file is not included. */
/* [REVIEW_c] resolved visbdk: Double checked with vispcn - Seems fine so (same pattern as the ComStackLib) */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#  endif
extern CONST(uint8, TCPIP_CONST) TcpIp_Tls_Hs_FinishedLabel[2][TCPIP_TLS_LABEL_FINISHED_LEN + 1u];

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding cipher mode of an given CipherSuite
 *  \details       -
 *  \param[in]     ActiveCipher                       Active Cipher Suite Id
 *  \return        TCPIP_TLS_STREAMING_MODE_INVALID         If no valid active cipher is found
 *  \return        TCPIP_TLS_STREAMING_MODE_AES_128_CBC     For all _AES_128_CBC cipher
 *  \return        TCPIP_TLS_STREAMING_MODE_NULL            For all _NULL cipher
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_TlsCipherStreamingModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificStreamingMode(
  TcpIp_TlsCipherDataType ActiveCipher);

/**********************************************************************************************************************
 * TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode
 *********************************************************************************************************************/
/*! \brief         Returns the authentication mode of the active ciphersuite
 *  \details       -
 *  \param[in]     ActiveCipher                 Active Cipher Suite Id
 *  \return        TCPIP_TLS_MSG_AUTH_MODE_NONE       If no authentication mode
 *  \return        TCPIP_TLS_MSG_AUTH_MODE_SHA256     Sha256 mode
 *  \return        TCPIP_TLS_MSG_AUTH_MODE_SHA1       Sha1 mode
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_TlsMessageAuthenticationModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificAuthenticationMode(
  TcpIp_TlsCipherDataType ActiveCipher);

/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_GetTxCipherMacLen
 *********************************************************************************************************************/
/*! \brief         Returns the length of the MAC for the active cipher
  *  \details      -
  *  \param[in]    TlsConIdx           TLS connection index
  *                                    CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \return       Length of the TX Cipher Mac
  *  \pre          -
  *  \context      TASK|ISR2
  *  \reentrant    FALSE
  *  \synchronous  TRUE
  *********************************************************************************************************************/
FUNC(uint8, TCPIP_CODE) TcpIp_TlsCoreRl_GetTxCipherMacLen(
  TcpIp_TlsConnectionIterType TlsConIdx);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding cipher mode of the selected CipherSuite for the given TlsConIdx
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        TCPIP_TLS_STREAMING_MODE_INVALID         If no valid active cipher is found
 *  \return        TCPIP_TLS_STREAMING_MODE_AES_128_CBC     For all _AES_128_CBC cipher
 *  \return        TCPIP_TLS_STREAMING_MODE_NULL            For all _NULL cipher
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_TlsCipherStreamingModeDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode(
  TcpIp_TlsConnectionIterType       TlsConIdx);

/***********************************************************************************************************************
 *  TcpIp_GetKeyExchangeMethodeOfActiveCipher
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding key exchange of the active CipherSuite
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ActiveCipher        Active cipher which should be used to determine the key exchange method
*  \return         TCPIP_TLS_KEYEXCHANGE_METHOD_ECDHE   For ECDHE key exchange
*  \return         TCPIP_TLS_KEYEXCHANGE_METHOD_ECDH    For ECDH key exchange
*  \return         TCPIP_TLS_KEYEXCHANGE_METHOD_PSK     For PSK key exchange
*  \return         TCPIP_TLS_KEYEXCHANGE_METHOD_INVALID If no valid key exchange method is found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_TlsKeyExchangeMethodDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnActiveCipherSpecificKeyExchangeMethod(
  TcpIp_TlsCipherDataType ActiveCipher);

/***********************************************************************************************************************
 *  TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificStreamingMode
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding cipher mode of the selected CipherSuite for the given TlsConIdx
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        TCPIP_TLS_STREAMING_MODE_INVALID         If no valid active cipher is found
 *  \return        TCPIP_TLS_STREAMING_MODE_AES_128_CBC     For all _AES_128_CBC cipher
 *  \return        TCPIP_TLS_STREAMING_MODE_NULL            For all _NULL cipher
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_TlsKeyExchangeMethodDataType, TCPIP_CODE) TcpIp_TlsCoreUtil_ReturnSelectedCipherSpecificKeyExchangeMethod(
  TcpIp_TlsConnectionIterType       TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreUtil_CheckAndGetRootCertificateId
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
  *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUtil_CheckAndGetRootCertificateId(
  TcpIp_TlsConnectionIterType   TlsConIdx,
  TCPIP_P2V(uint16)             CertIdPtr
);

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite
 *********************************************************************************************************************/
 /*! \brief         Checks if the given TLS connection uses at least one ECC cipher suite
  *  \details       -
  *  \param[in]      TlsConIdx               TLS connection index
  *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
  *  \return        TRUE                     if TlsConIdx is using at least one ECC cipher suite
  *  \return        FALSE                    if TlsConIdx is NOT using ECC cipher suite
  *  \pre           -
  *  \context       TASK
  *  \reentrant     FALSE
  *  \synchronous   TRUE
  *********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreUtil_ConnectionUseEccCipherSuite(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_SocketIdxToTlsConIdx
 *********************************************************************************************************************/
/*! \brief         Returns the matching TLS connections index to the given socket index
 *  \details       -
 *  \param[in]     SocketIdx            Socket identifier of the related local socket resource.
 *  \param[in,out] TlsConIdxPtr         Pointer of the TLS Connection index of the corresponding socket
 *  \return        E_OK                 If TLS connection successful mapped to socket index
 *  \return        E_NOT_OK             If TLS connection could NOT mapped to socket index
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SocketIdxToTlsConIdx(
  TcpIp_SocketDynIterType                SocketIdx,
  TCPIP_P2V(TcpIp_TlsConnectionIterType) TlsConIdxPtr);

/**********************************************************************************************************************
 *  TcpIp_TlsCore_ChangeParameter
 *********************************************************************************************************************/
/*! \brief         Forward the ChangeParameter call to the specific option handler
 *  \details       -
 *  \param[in]     SocketTcpIdx         Index of a TCP socket
 *                                      CONSTRAINT:  [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     OptName              Option name.  Valid option identifiers are:
 *                                        TCPIP_PARAMID_TLS_CONNECTION_ASSIGNMENT
 *  \param[in]     OptValPtr            Option parameter
 *  \return         E_OK                The request has been accepted.
 *  \return         E_NOT_OK            The request has not been accepted.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCore_ChangeParameter(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  uint8                        OptName,
  TCPIP_P2C(uint8)             OptValPtr);

/**********************************************************************************************************************
 *  TCPIP TLS INIT FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCore_Init
 *********************************************************************************************************************/
/*! \brief         Initialize the TLS core component
 *  \details       Iterate over all configured connections and initialize all subcomponents and the TLS Listener
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_Init(void);

/**********************************************************************************************************************
 *  TcpIp_TlsCore_InitAsnycFlags
 *********************************************************************************************************************/
/*! \brief         Initialize the Rx Indications
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_InitAsnycFlags(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRxIndication_Init
 *********************************************************************************************************************/
/*! \brief         Initialize the Rx Indications
 *  \details       -
 *  \param[in]     TlsConIdx          TLS connection index
                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreRxIndication_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCipher_Init
 *********************************************************************************************************************/
/*! \brief         Initialize the Cipher worker and ciphers
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCipher_Init(TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreConnection_Init
 *********************************************************************************************************************/
/*! \brief         Initialize all TLS connection related variables
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCoreConnection_Init(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
#   if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
* TcpIp_TlsCore_RemoveLoadedCerts
*********************************************************************************************************************/
/*! \brief         Removes all loaded certificates from KeyM
 *  \details       Called by TLS client to delete the processed server certificates
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCore_RemoveLoadedCerts(
  TcpIp_TlsConnectionIterType TlsConIdx);
#   endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCore_ResetConnection
 *********************************************************************************************************************/
/*! \brief         Reset either the Server or Client relevant part and also the all connection variables
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_TlsCore_ResetConnection(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCore_ResetConnectionVariables
 *********************************************************************************************************************/
/*! \brief         Reset all connection relevant variables
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_TlsCore_ResetConnectionVariables(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TCPIP TLS LISTENER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetNextFreeListenerIndex
 *********************************************************************************************************************/
/*! \brief         Search for the next free TLS Listener
 *  \details       Iterate over all configured Listener and search for the next free entry, which is stored in the Ptr
 *  \param[out]    TlsListenerPtr      Next free TLS Listener
 *  \return        E_OK                If a free TLS Listener is found
 *  \return        E_NOT_OK            If no free TLS Listener is found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsListener_GetNextFreeListenerIndex(
  TCPIP_P2V(TcpIp_TlsListenerIterType) TlsListenerPtr);

/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding TLS Listener which is used by the given socket index
 *  \details       -
 *  \param[in]     SocketIdx           Socket identifier of the related local socket resource.
 *  \param[out]    TlsListenerPtr      Corresponding TLS Listener by the given socket index
 *  \return        E_OK                If corresponding TLS Listener to the given socket is found
 *  \return        E_NOT_OK            If no corresponding TLS Listener to the given socket is found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.03.00.0
*/
#   ifdef C_REVIEW_VECTOR                                                                                               /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.01.00.4 Improve: Description of OK and NOT_OK is wrong, this is not about a free listener. */
/* [REVIEW_c] resolved visbdk: Done */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
#   endif
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsListener_GetTlsListenerUsedBySocketIdx(
  TcpIp_SocketDynIterType              SocketIdx,
  TCPIP_P2V(TcpIp_TlsListenerIterType) TlsListenerPtr);
#  endif /* TCPIP_SUPPORT_ASRTLSSERVER == STD_ON */

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsCore_GetNextFreeTlsClientConnection
 *********************************************************************************************************************/
/*! \brief         Returns the corresponding TLS Connection assigned to this socket.
 *  \details       There always is a connection that is assigned to the socket.
 *  \param[in]     SocketIdx           Socket identifier of the related local socket resource.
 *  \param[in]     RemotePort          Remote port of the given socket.
 *  \param[out]    TlsConIdxPtr        Holds the next free TLS Connection Index
 *  \return        E_OK                Free TLS Client connection is found
 *  \return        E_NOT_OK            No free TLS Client connection is found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCore_GetNextFreeTlsClientConnection(
  TcpIp_SizeOfSocketDynType SocketIdx,
  uint16 RemotePort,
  TCPIP_P2V(TcpIp_TlsConnectionIterType) TlsConIdxPtr);
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort
 *********************************************************************************************************************/
/*! \brief         Returns the next available TLS Connection index which is configured for the given port.
 *  \details       -
 *  \param[in]     UsedPort            Port which is used to identify the TLS connection
 *  \return        tlsConIdx           Valid if a free TLS connection is found
 *  \return        tlsConIdx           Invalid (TcpIp_GetSizeOfTlsConnection()) if no free TLS connection is found
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
/*
[REVIEW_G] t_accepted 16.01.00.4
*/
FUNC(TcpIp_TlsConnectionIterType, TCPIP_CODE)  TcpIp_TlsListener_GetNextFreeTlsConnectionUsedByPort(
  CONST(uint16, AUTOMATIC) UsedPort);

/**********************************************************************************************************************
 *  TcpIp_TlsListener_Close
 *********************************************************************************************************************/
/*! \brief         Forwards the close call to the TLS connection.
 *  \details       This function is called when TcpIp_Close is called on a TLS Listen socket.
 *  \param[in]     SocketIdx    Socket identifier of the related local socket resource.
 *  \param[in]     Abort        TRUE: connection will immediately be terminated by sending a RST-Segment and releasing
 *                              all related resources.
 *                              FALSE: connection will be terminated after performing a regular connection termination
 *                              and releasing all related resources.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsListener_Close(
  TcpIp_SocketDynIterType SocketIdx,
  boolean Abort);
#  endif
/**********************************************************************************************************************
 *  TLS CORE UPPER LAYER (UL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreUl_Transmit
 *********************************************************************************************************************/
/*! \brief         Forwards the TcpIp_Transmit call to the TLS stack
 *  \details       -
 *  \param[in]     SocketIdx          Index of a TCP socket
 *                                    CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataPtr            Pointer of the source data.
 *  \param[in]     Length             Length of the source data.
 *  \param[in]     ForceRetrieve      The TCP force retrieve flag.
 *  \return        E_OK               Transmit request was accepted
 *  \return        E_NOT_OK           Transmit request was NOT accepted
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreUl_Transmit(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2C(uint8)          DataPtr,
  uint32                    Length,
  boolean                   ForceRetrieve);

/**********************************************************************************************************************
 * TcpIp_TlsCoreUl_Received
 *********************************************************************************************************************/
/*! \brief         Forwards the TcpIp_TcpReceived call to the TLS stack
 *  \details       -
 *  \param[in]     SocketIdx             Socket identifier of the related local socket resource.
 *  \param[in]     DataLenByte           Received data byte length
 *  \param[out]    ErrorIdPtr           TCPIP_E_NO_ERROR    ReadIdx updated successfully
 *                                      TCPIP_E_INV_ARG     Function called with invalid parameters
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_Received(
  TcpIp_SocketDynIterType    SocketIdx,
  uint32                     DataLenByte,
  TCPIP_P2V(uint8)           ErrorIdPtr);

/**********************************************************************************************************************
 * TcpIp_TlsCoreUl_TcpAccepted
 *********************************************************************************************************************/
/*! \brief         Forwards the TcpIp_TcpAccepted call to the TLS stack
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_TcpAccepted(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 * TcpIp_TlsCoreUl_TcpConnected
 *********************************************************************************************************************/
/*! \brief         Forwards the TcpIp_TcpConnected call to the TLS stack
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreUl_TcpConnected(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TLS CORE RECORD LAYER (RL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreRl_EncryptAndAuthFrame
 *********************************************************************************************************************/
/*! \brief          Perform encryption and authentication of TCP frame
 *  \details        This function encrypts and authenticates the content data present in the Tls buffer
 *  \param[in]      SocketId          Socket identifier of the related local socket resource.
 *  \param[in]      BufPtr            TCP buffer pointer
 *  \param[in]      BufLength         TCP buffer size
 *  \return         BUFREQ_OK         Data was encrypted and authenticated successfully
 *  \return         BUFREQ_E_NOT_OK   Data was not successfully processed
 *  \pre            Raw TCP message is present in the Tls Tx buffer
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_EncryptAndAuthFrame(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint8)        BufPtr,
  uint16                  BufLength);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreRl_Transmit
 *********************************************************************************************************************/
/*! \brief         Forwards the transmit request to the TLS record layer
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     TxStartIdx          Start index within the TlsTxBuffer of the transmittable frame
 *  \param[in]     TxLen               Length of the transmittable frame
 *  \param[in]     ContentType         TLS content type of the transmittable frame
 *  \return        E_OK                Transmit request of frame was accepted
 *  \return        E_NOT_OK            Transmit request of frame was not accepted
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreRl_Transmit(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsBufferTxIterType TxStartIdx,
  TcpIp_SizeOfTlsBufferTxType TxLen,
  CONST(uint8, AUTOMATIC) ContentType);

/**********************************************************************************************************************
 *  TLS CORE BUFFER
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_ClearTxBuffer
 *********************************************************************************************************************/
/*! \brief         Clears the TLS Tx buffer in the given range
 *  \details       -
 *  \param[in]     StartIdx   Start index within the TX buffer
 *  \param[in]     EndIdx     End index within the TX buffer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_ClearTxBuffer(
  CONST(TcpIp_TlsBufferTxIterType, AUTOMATIC) StartIdx,
  CONST(TcpIp_TlsBufferTxIterType, AUTOMATIC) EndIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_ClearRxBuffer
 *********************************************************************************************************************/
/*! \brief         Clears the TLS Rx buffer in the given range
 *  \details       -
 *  \param[in]     StartIdx   Start index within the RX buffer
 *  \param[in]     EndIdx     End index within the RX buffer
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreBuffer_ClearRxBuffer(
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) StartIdx,
  CONST(TcpIp_TlsBufferRxIterType, AUTOMATIC) EndIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreBuffer_GetAvailableTxBufferSize
 *********************************************************************************************************************/
/*! \brief          Read the available size of the TLS tx buffer.
 *  \details        Returns the available size of the TLS tx buffer (= buffer size - fill level).
 *                  If this is a listen socket, no buffer size can be read so the size is 0.
 *  \param[in]      SocketIdx                  socket index
 *  \param[out]     AvailableTxBufferSizePtr   Returns the free space in the tx buffer.
 *  \return         E_OK                       The available size could be read successfully.
 *  \return         E_NOT_OK                   Reading was not successful.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreBuffer_GetAvailableTxBufferSize(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint32) AvailableTxBufferSizePtr);

/**********************************************************************************************************************
 *  TLS CORE MAIN FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_Rx
 *********************************************************************************************************************/
/*! \brief         Processes all received data and forwards information to upper layers
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_Rx(void);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_State
 *********************************************************************************************************************/
/*! \brief         Performs all state and timing specific actions
 *  \details       Performs all processing of the TLS handshakes states, the heartbeat handling,
 *                 the error and alert handling as well as the TcpIp Event handling
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_State(void);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_Tx
 *********************************************************************************************************************/
/*! \brief         Processes all pending transmit requests from the upper layers and transmits the data
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_Tx(void);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreMainFunction_LowPrio
 *********************************************************************************************************************/
/*! \brief         Processes all time consuming operation in the background context
 *  \details       -
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMainFunction_LowPrio(void);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCtx_AsyncHandler
 *********************************************************************************************************************/
/*! \brief         Asynchronous handler of TLS Core subcomponent
 *  \details       -
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_AsyncHandler(
  TcpIp_TlsConnectionIterType TlsConIdx);

/***********************************************************************************************************************
 *  TCPIP TLS CORE STATE AND EVENT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreEvent_TcpIpEventForwarding
 *********************************************************************************************************************/
/*! \brief         Forwards all occurred TCP events to the TLS stack
 *  \details       -
 *  \param[in]     SocketIdx      Socket identifier of the related local socket resource.
 *  \param[in]     Event          Occurred TCP event
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpIpEventForwarding(
  TcpIp_SocketDynIterType SocketIdx,
  IpBase_TcpIpEventType   Event);

/**********************************************************************************************************************
 * TcpIp_TlsCoreEvent_TcpIpEventClose
 *********************************************************************************************************************/
/*! \brief         Forwards the TcpIp event CLOSE to the TLS stack
 *  \details       -
 *  \param[in]      SocketId Socket handle identifying the local socket resource.
 *  \param[in]      Abort    TRUE: connection will immediately be terminated
 *                           FALSE: connection will be terminated after performing a regular connection termination
 *                           handshake and releasing all related resources.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreEvent_TcpIpEventClose(
  TcpIp_SocketDynIterType SocketIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  TCPIP TLS ERROR
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_ReportUserError
 *********************************************************************************************************************/
/*! \brief         User errors will be stored into the user error buffer as soon as invalid packet is received.
 *  \details       -
 *  \param[in]     UserError           Combined information about the occurring error.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreError_ReportUserError(
  CONST(TcpIp_TlsUserErrorType, AUTOMATIC) UserError);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreError_GetUserError
 *********************************************************************************************************************/
/*! \brief         Reported user errors can be read by the user and stored into the given user buffer.
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in,out] UserErrorMemoryPtr  Pointer to the user buffer, where user error entries will be stored.
 *  \param[in,out] NumOfUserErrorPtr   Number of user errors upper layer wants to read.
 *  \return        E_OK                if reading of user error was successful.
 *                 E_NOT_OK            if reading of user error was NOT successful
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreError_GetUserError(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2V(TcpIp_TlsUserErrorType) UserErrorMemoryPtr,
  TCPIP_P2V(uint32) NumOfUserErrorPtr);

/**********************************************************************************************************************
 *  TCPIP TLS CRYPTO
 *********************************************************************************************************************/
#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
*  TcpIp_TlsCoreCrypto_ReduceSharedKey
*********************************************************************************************************************/
/*! \brief         Reduce the key shared key to the needed size
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                if operation was successful
 *  \return        E_NOT_OK            if operation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_ReduceSharedKey(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcMasterSecret
 *********************************************************************************************************************/
/*! \brief         Calculated the TLS Master secret for this TLS Connection
 *  \details       Depending on the selected key exchange method, the shared value (output of the DH operation) must be
 *                 reduced to 32 byte size. This API handles this with the CSM copy partial operation.
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                if the calculation succeeded
 *  \return        E_NOT_OK            if the calculation was NOT successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_ReduceSharedKey
 *********************************************************************************************************************/
/*! \brief         Derive the crypto key block material for this TLS Connection
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                if the key block could be derived
 *  \return        E_NOT_OK            if the key block could not be derived
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_DeriveKeyBlock(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_SetCsmKeys
 *********************************************************************************************************************/
/*! \brief         Set the CSM keys for HMAC and AES operations
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                if the key could be set
 *  \return        E_NOT_OK            if the key could not be set
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_SetCsmKeys(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration
 *********************************************************************************************************************/
/*! \brief         Checks if all necessary keys for the selected cipher are configured.
 *  \details       This function adds a runtime check to the optional CSM parameter for the different CipherSuites.
 *                 In case of an invalid configured CSM key or job, the access to the element must be restricted.
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                If the necessary keys and jobs are configured correctly.
 *  \return        E_NOT_OK            If the necessary keys and jobs are NOT configured correctly.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CheckCsmKeyConfiguration(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_ClearCsmKey
 *********************************************************************************************************************/
/*! \brief         Clears the given Key within the CSM
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     KeyPtr              Pointer to the CMS Key which should be cleared
 *  \return        E_OK                if the key could be cleared
 *  \return        E_NOT_OK            otherwise
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_ClearCsmKey(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) KeyPtr);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CalcKeyBlockSize
 *********************************************************************************************************************/
/*! \brief         Calculate the key block size depending on the selected cipher suite
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \return        E_OK                if the key block size is calculated correctly
 *  \return        E_NOT_OK            otherwise
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CalcKeyBlockSize(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_CheckCsmResult
 *********************************************************************************************************************/
/*! \brief         Checks the return value and result length of a CSM call
 *  \details       In case the check fails errors are thrown and connection may be closed.
 *                 In case the result was not relevant set the values to 0.
 *  \param[in]     TlsConIdx            TLS connection index
 *                                      CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     CsmRetVal            Return value of the CSM call
 *  \param[in]     CsmResultLength      Result length of the CSM call
 *  \param[in]     ExpectedResultLength Expected length of result
 *  \param[in]     ApiId                API in which the CSM call has been made
 *  \param[in]     ErrorId              ErrorId in which the CSM call has been made
 *  \return        E_OK                 If CsmRetVal is set to E_OK and the length match
 *  \return        E_NOT_OK             If either the CsmRetVal is E_NOT or the length does not match
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_CheckCsmResult(
  TcpIp_TlsConnectionIterType TlsConIdx,
  Std_ReturnType CsmRetVal,
  uint32 CsmResultLength,
  uint32 ExpectedResultLength,
  TcpIp_TlsFunctionIdType ApiId);

/**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_Prf
 *********************************************************************************************************************/
/*! \brief         Pseudo Random Function
 *  \details       Calculates a pseudo random value array to the provided target buffer using the provided seed
 *                 and secret
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     ResultKeyIdPtr      CSM key where the output data shall be written to
 *  \param[in]     SecretKeyIdPtr      CSM key where the secret is stored
 *  \param[in]     LabelPtr            pointer to label
 *  \param[in]     SeedPtr             pointer to seed
 *  \param[in]     LabelLen            length of label
 *  \param[in]     SeedLen             length of seed
 *  \param[in]     ResultIsPrivate     TRUE: result key is private; FALSE: Result key is public
 *  \return        E_OK                if random could be generated
 *  \return        E_NOT_OK            if random could not be generated
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
 FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreCrypto_Prf(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) ResultKeyIdPtr,
  TCPIP_P2C(TcpIp_TlsCsmKeyInfoType) SecretKeyIdPtr,
  TCPIP_P2C(uint8) LabelPtr,
  TCPIP_P2C(uint8) SeedPtr,
  uint8 LabelLen,
  uint8 SeedLen,
  boolean ResultIsPrivate);

 /**********************************************************************************************************************
 *  TcpIp_TlsCoreCrypto_HandleInvalidConfiguration
 *********************************************************************************************************************/
/*! \brief         This function is called if an invalid or missing configuration is detected during runtime.
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCrypto_HandleInvalidConfiguration(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TPCIP TLS ALERT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TcpIp_TlsCoreAlert_Set
 *********************************************************************************************************************/
/*! \brief         Set, prepare and trigger the Alert on the given TLS Connection
 *  \details       -
 *  \param[in]     TlsConIdx           TLS connection index
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]     AlertLevel          Alert Level according to RFC5246
 *  \param[in]     AlertDescription    Alert Description according to RFC5246
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreAlert_Set(
  TcpIp_TlsConnectionIterType TlsConIdx,
  TcpIp_TlsAlertLevelType AlertLevel,
  TcpIp_TlsAlertDescriptionType AlertDescription);

/**********************************************************************************************************************
 *  TCPIP TLS CORE LOWER LAYER (LL)
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * TcpIp_TlsCoreLl_RxIndication
 *********************************************************************************************************************/
/*! \brief         Write the data segment into the buffer struct management
 *  \details       -
 *  \param[in]     SocketTcpIdx        Index of a TCP socket
 *                                     CONSTRAINT: [0..TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     DataPtr             Pointer to the data
 *  \param[in]     DataLen             Length of the data
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreLl_RxIndication(
  TcpIp_SizeOfSocketTcpDynType SocketTcpIdx,
  TCPIP_P2V(uint8) DataPtr,
  uint16           DataLen);

/**********************************************************************************************************************
 * TcpIp_TlsCoreLl_TcpAccepted
 *********************************************************************************************************************/
/*! \brief         Informs TLS layers about a new socket connection on a listen socket.
 *  \details       Set the Listen and Communication socket on the TLS-Connection and triggers the start of the TLS-HS.
 *  \param[in]     SocketTcpIdx          Index of a TCP socket that is in state listen.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \param[in]     SocketTcpIdxConnected Index of a newly allocated TCP socket that represents the accepted connection.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK                  Upper layer has accepted the new connection.
 *  \return        E_NOT_OK              Upper layer has rejected the new connection.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreLl_TcpAccepted(
  TcpIp_SocketTcpDynIterType      SocketTcpIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdxConnected);

#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsCoreLl_TcpConnected
 *********************************************************************************************************************/
/*! \brief         Informs TLS layers about the "connect" event on a socket.
 *  \details       Set the Communication socket on the next available TLS-Client Connection and triggers the TLS-HS.
 *  \param[in]     SocketIdx         Index of a TCP socket.
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfSocketTcpDyn()-1]
 *  \return        E_OK              Upper layer has accepted the new connection.
 *  \return        E_NOT_OK          Upper layer has rejected the new connection.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreLl_TcpConnected(
  TcpIp_SizeOfSocketDynType SocketIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
 * TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve
 *********************************************************************************************************************/
/*! \brief         Checks if the compression flag of the public key of the given curve is expected
 *  \details       -
 *  \param[in]     CurveId   RFC Curve identifier
 *  \return        TRUE if the compression flag is expected, otherwise FALSE
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(boolean, TCPIP_CODE) TcpIp_TlsCoreUtil_CheckPublicKeyCompressionFlagOfEllipticCurve(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey
 *********************************************************************************************************************/
/*! \brief         Returns the length of the public key of the given curve
 *  \details       -
 *  \param[in]     CurveId   RFC Curve identifier
 *  \return        Length of the public key, 0 if curve ID is not supported.
 *  \pre           -
 *  \context       TASK|ISR
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(uint8, TCPIP_CODE) TcpIp_TlsMsg_GetLenOfCurveSpecificPubKey(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId);

/**********************************************************************************************************************
 * TcpIp_TlsMsg_GetLenOfCurveSpecificDhSharedKey
 *********************************************************************************************************************/
/*! \brief         Returns the length of the shared key of the given curve
 *  \details       -
 *  \param[in]     CurveId RFC Curve identifier
 *  \return        Length of the shared key, 0 if curve ID is not supported.
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(uint8, TCPIP_CODE) TcpIp_TlsMsg_GetLenOfCurveSpecificDhSharedKey(
  CONST(TcpIp_TlsEllipticCurveIdType, AUTOMATIC) CurveId);
#  endif
/**********************************************************************************************************************
 * TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncCsmJob
 *********************************************************************************************************************/
/*! \brief          Handles occurring errors during an asynchronous processing
 *  \details        -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \param[in]      FunctionId              FunctionId of function which triggers error
 *  \param[in]      ErrorId                 Error Id of occurred error
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsAsyncCtx_HandlesErrorDuringAsyncJobProcessing(
  TcpIp_TlsConnectionIterType TlsConIdx,
  uint16 FunctionId,
  uint16 ErrorId);

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey
 *********************************************************************************************************************/
/*! \brief          Asynchronous handler for calculation the Diffie-Hellman public key
 *  \details        -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcDiffieHellmanPublicKey(
  TcpIp_TlsConnectionIterType TlsConIdx);

#  if (TCPIP_SUPPORT_ASRTLS_ECC == STD_ON)
/**********************************************************************************************************************
* TcpIp_TlsCoreCtx_CalcDhSharedSecret
*********************************************************************************************************************/
/*! \brief         Asynchronous handler for calculation the Diffie-Hellman shared secret
 *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcDhSharedSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* TCPIP_SUPPORT_ASRTLS_ECC == STD_ON) */

#  if ((TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON))
/**********************************************************************************************************************
 * TcpIp_TlsCoreCtx_CalcPskPremasterSecret
 *********************************************************************************************************************/
/*! \brief         Asynchronous handler for calculation the TLS pre master secret
 *  \details       -
 *  \param[in]     TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcPskPremasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);
#  endif /* (TCPIP_SUPPORT_ASRTLSSERVER_PSK == STD_ON) || (TCPIP_SUPPORT_ASRTLSCLIENT_PSK == STD_ON) */

/**********************************************************************************************************************
 * TcpIp_TlsCoreCtx_CalcMasterSecret
 *********************************************************************************************************************/
 /*! \brief         Asynchronous handler for calculation the TLS master secret
  *  \details       -
 *  \param[in]      TlsConIdx               TLS connection index
 *                                          CONSTRAINT: [0..TcpIp_GetSizeOfTlsConnection()-1]
 *  \pre           -
 *  \context       TASK (only called in the context of the TLS background task TcpIp_Tls_MainFunctionLowPrio())
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreCtx_CalcMasterSecret(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
 *  TCPIP TLS CORE MASTER SECRET ACCESS (MSA)
 *********************************************************************************************************************/
#  if (TCPIP_SUPPORT_ASRTLS_MASTER_SECRET_ACCESS == STD_ON)
/**********************************************************************************************************************
*  TcpIp_TlsCoreMsa_ClearMasterSecretBuffer
*********************************************************************************************************************/
/*! \brief        Clear the buffer, used to read the Client random and Session id.
*  \details       -
*  \param[in]     TlsConIdx
*  \pre           -
*  \context       TASK
*  \reentrant     FALSE
*  \synchronous   TRUE
*********************************************************************************************************************/
FUNC(void, TCPIP_CODE) TcpIp_TlsCoreMsa_ClearMasterSecretBuffer(
  TcpIp_TlsConnectionIterType TlsConIdx);

/**********************************************************************************************************************
* TcpIp_TlsCoreMsa_ReadHandshakeParameter
*********************************************************************************************************************/
/*! \brief        User can read Master Secret Key, Client Random number and Session Id.
*  \details       -
*  \param[in]     SocketIdx          Socket identifier of the related local socket resource.
*  \param[in,out] MasterSecretPtr    Pointer to the user buffer, where Master Secret Key shall be stored.
*  \param[in,out] ClientRandomPtr    Pointer to the user buffer, where Client Random Number shall be stored.
*  \param[in,out] SessionIdPtr       Pointer to the user buffer, whereSession Id shall be stored.
*  \param[in,out] SessionIdLenPtr    Pointer to the Session Id Length.
*  \return        E_OK               if reading is successful.
*                 E_NOT_OK           Problem occurred at CSM during reading of master secret.
*  \pre           -
*  \context       TASK
*  \reentrant     FALSE
*  \synchronous   TRUE
*********************************************************************************************************************/
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TlsCoreMsa_ReadHandshakeParameter(
  TcpIp_SocketDynIterType SocketIdx,
  TCPIP_P2V(uint8)        MasterSecretPtr,
  TCPIP_P2V(uint8)        ClientRandomPtr,
  TCPIP_P2V(uint8)        SessionIdPtr,
  TCPIP_P2V(uint8)        SessionIdLenPtr);
#  endif


# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
#endif /* TCPIP_TLSCORE_H */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_TlsCore.h
 *********************************************************************************************************************/
