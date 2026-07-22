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
/**        \file  Etm.c
 *        \brief  Etm source file
 *
 *      \details  Implementation of the Etm (Ethernet Testability Module) module. This module implements the
 *                AUTOSAR Testability Protocol and Service Primitives protocol for interaction with external testers.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define ETM_SOURCE

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/*lint -e506 */ /* Suppress ID506 due to MD_MSR_14.1 */

/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 2889 EOF */ /* MD_Etm_2889 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Etm.h"
#include "Etm_Lcfg.h"
#include "SchM_Etm.h"
#include "Appl_Etm.h"
#include "TcpIp.h"
#include "IpBase.h"
#include "IpBase_Sock.h"

#if (ETM_NVM_ENABELD == STD_ON)
# include "NvM.h"
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#if (ETM_IPV4_ENABLED == STD_ON)
# include "TcpIp_IcmpV4.h"
#endif /* (ETM_IPV4_ENABLED == STD_ON) */

#if (ETM_IPV6_ENABLED == STD_ON)
# include "TcpIp_IpV6_Priv.h"
#else
# include "TcpIp_Priv.h"
#endif /* (ETM_IPV6_ENABLED == STD_ON) */

#if (ETM_ETHIF_ENABLED == STD_ON)
# include "EthIf.h"
# include "Eth_Types.h"
#endif /* (ETM_ETHIF_ENABLED == STD_ON) */

#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
# include "ComM.h"
#endif /* (ETM_USE_ETH_PRIMITIVES == STD_ON) */

#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
# include "EthIf.h"
#endif /* (ETM_USE_PHY_PRIMITIVES == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Etm header file */
#if ( (ETM_SW_MAJOR_VERSION != (10u)) \
   || (ETM_SW_MINOR_VERSION != (0u)) \
   || (ETM_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Etm.c and Etm.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define ETM_CMD_CHAN_IDX_UDP_V4           0x00u /* Command channel UDPv4 connetcion */
#define ETM_CMD_CHAN_IDX_UDP_V6           0x01u /* Command channel UDPv6 connetcion */
#define ETM_CMD_CHAN_IDX_TCP_V4           0x02u /* Command channel TCPv4 listen port */
#define ETM_CMD_CHAN_IDX_TCP_V6           0x03u /* Command channel TCPv6 listen port */
#define ETM_CMD_CHAN_IDX_TCP_C4           0x04u /* Command channel TCPv4 connetcion */
#define ETM_CMD_CHAN_IDX_TCP_C6           0x05u /* Command channel TCPv6 connetcion */

#define ETM_DATA_LEN_ADDRESS_IPV4          4u /*  4 bytes --  32 bit */
#define ETM_DATA_LEN_ADDRESS_IPV6         16u /* 16 bytes -- 128 bit */

#define ETM_INTERFACE_MIN_LENGTH           4u

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS -- ETM LENGTH VALUES
 *********************************************************************************************************************/

/* ETM Header Format */
/*

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                               |E|             |    Service    |
   |           Service ID          |V|   Group ID  |  Primitive ID | --> SOME/IP: this field represent the MessageID (uint32) containing
   |             (SID)             |B|    (GID)    |     (PID)     |              the ServiceID (uint16) and the MethodID (uint16)
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   |                          Length (LEN)                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               | --> SOME/IP: this field represent the RequestID (uint32) containing
   |                           DON'T CARE                          |              the ClientID (uint16) and the SessionID (uint16)
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    Protocol   |   Interface   |               |               |
   |    Version    |    Version    |    Type ID    |   Result ID   |
   |    (0x01u)    |    (0x01u)    |     (TID)     |     (RID)     |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   |                         Payload (DAT)                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 */

#define ETM_HEADER_LENGTH                 16u
#define ETM_EVENT_LENGTH_FIX_PAYLOAD      24u /* Etm Fix Event Data Length of ReceiveAndForward and ListenAndAccept */
#define ETM_EVENT_LENGTH_FIX_MAX          (ETM_HEADER_LENGTH + ETM_EVENT_LENGTH_FIX_PAYLOAD)
#define ETM_MESSAGE_LENGTH_MAX            (ETM_EVENT_LENGTH_FIX_MAX + ETM_STUB_MAX_FORWARD_LENGTH)
#define ETM_MESSAGE_OFFSET_SID             0u
#define ETM_MESSAGE_OFFSET_EVB_GID         2u
#define ETM_MESSAGE_OFFSET_PID             3u
#define ETM_MESSAGE_OFFSET_LEN             4u
#define ETM_MESSAGE_OFFSET_PROTO_VER      12u
#define ETM_MESSAGE_OFFSET_IFACE_VER      13u
#define ETM_MESSAGE_OFFSET_TID            14u
#define ETM_MESSAGE_OFFSET_RID            15u
#define ETM_MESSAGE_OFFSET_DAT            16u

#if ( ETM_STUB_MAX_FORWARD_LENGTH <= (ETM_TCPIP_MIN_MMS - ETM_EVENT_LENGTH_FIX_MAX) )
# define ETM_STUB_MAX_FORWARD_LENGTH_CALCULATED   (ETM_STUB_MAX_FORWARD_LENGTH)
#else
# define ETM_STUB_MAX_FORWARD_LENGTH_CALCULATED   (ETM_TCPIP_MIN_MMS - ETM_EVENT_LENGTH_FIX_MAX)
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS -- ETM TYPE VALUES
 *********************************************************************************************************************/

/* TID */

typedef uint8 Etm_TypeIdType;
#if (ETM_STUB_PROTOCOL_VERSION <= 0x00000004uL) /* Version 0.4 */
# define ETM_TID_REQUEST                              0x00u
# define ETM_TID_RESPONSE                             0x08u
# define ETM_TID_EVENT                                0x02u
#else
# define ETM_TID_REQUEST                              0x00u
# define ETM_TID_RESPONSE                             0x80u
# define ETM_TID_EVENT                                0x02u /* EVB set to 1 */
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS -- ETM PAYLOAD DATA VALUES
 *********************************************************************************************************************/

#define ETM_APPL_RESPONSE_BUFFER_LENGTH         100u

#define ETM_UINT8_MASK_EVB_BIT                  0x80u   /* 1-Bit-Mask 1000.0000 */
#define ETM_UINT8_MASK_GID                      0x7Fu   /* 7-Bit-Mask 0111.1111 */
#define ETM_FORWARD_FOREVER                     0xFFFFu
#define ETM_PORT_ANY                            0xFFFFu

#define ETM_CONFIGURE_SOCKET_TTL_HOP_LIMIT      0x0000u
#define ETM_CONFIGURE_SOCKET_PRIORITY           0x0001u
#define ETM_CONFIGURE_SOCKET_DONT_FRAGMENT      0x0002u
#define ETM_CONFIGURE_SOCKET_TIMESTAMT_OPTION   0x0003u
#define ETM_CONFIGURE_SOCKET_TYPE_OF_SERVICE    0x0004u
#define ETM_CONFIGURE_SOCKET_MSS                0x0005u
#define ETM_CONFIGURE_SOCKET_NAGLE_ALGORITHM    0x0006u
#define ETM_CONFIGURE_SOCKET_UDP_CHECKSUM       0x0007u

#define ETM_PHY_TEST_MODE_NONE                  0x00u /* Normal operation */
#define ETM_PHY_TEST_MODE_1                     0x01u /* Test transmitter drop */
#define ETM_PHY_TEST_MODE_2                     0x02u /* Test master timing jitter */
#define ETM_PHY_TEST_MODE_3                     0x03u /* Test slave timing jitter */
#define ETM_PHY_TEST_MODE_4                     0x04u /* Test transmitter distortion */
#define ETM_PHY_TEST_MODE_5                     0x05u /* Test power spectral density */

#define ETM_PHY_TX_MODE_NORMAL                  0x00u /* Normal Operation */
#define ETM_PHY_TX_MODE_TX_OFF                  0x01u /* Transmitter disabled */
#define ETM_PHY_TX_MODE_SCRAMBLER_OFF           0x02u /* Scrambler disabled */

#define ETM_PHY_CABLE_DIAG_OK                   0x00u /* Cable diagnostic ok */
#define ETM_PHY_CABLE_DIAG_ERROR                0x01u /* Cable diagnostic failed */
#define ETM_PHY_CABLE_DIAG_SHORT                0x02u /* Short circuit detected */
#define ETM_PHY_CABLE_DIAG_OPEN                 0x03u /* Open circuit detected */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define ETM_MIN(a, b)                     (((a) <= (b)) ? (a) : (b))
#define ETM_MAX(a, b)                     (((a) <= (b)) ? (b) : (a))

/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define ETM_HTONL(a)                      IPBASE_HTON32(a)
#define ETM_HTONS(a)                      IPBASE_HTON16(a)
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) /* COV_ETM_BYTE_ORDER */
/* Host byte-order is big endian (network byte-order) */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
# define ETM_HTONS_UINT8(a)               ((uint16)(a))
#else
/* Host byte-order is little endian */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
# define ETM_HTONS_UINT8(a)               ((uint16)(((uint16)(a)) << 8u))
#endif

/* ----- ETM Check Conditions ----- */
/* PRQA S 3453 10 */ /* MD_MSR_FctLikeMacro */
#define ETM_COND_VALID_PTR(Pointer)              ( NULL_PTR != (Pointer) ) /* ETM_E_INV_POINTER */
#define ETM_COND_VALID_DOMAIN(SockAddrPtr)       ( (((ETM_P2V(TcpIp_SockAddrType))(SockAddrPtr))->domain == TCPIP_AF_INET) || \
                                                   (((ETM_P2V(TcpIp_SockAddrType))(SockAddrPtr))->domain == TCPIP_AF_INET6) ) /* ETM_E_INV_SOCK_ADDR_FAMILY */
#define ETM_COND_VALID_SOCKET_ID(SocketId)       ((uint16)ETM_TCPIP_MAX_TCP_SOCKET_ID > (uint16)(SocketId))      /* ETM_RID_E_ISD */
#define ETM_COND_VALID_UDP_SOCKET_ID(SocketId)   ((uint16)ETM_TCPIP_MAX_UDP_SOCKET_ID > (uint16)(SocketId))      /* ETM_RID_E_ISD */
#if (ETM_TCP_ENABLED == STD_ON)
# define ETM_COND_VALID_TCP_SOCKET_ID(SocketId)  ( ((uint16)ETM_TCPIP_MAX_TCP_SOCKET_ID >  (uint16)(SocketId)) && \
                                                   ((uint16)ETM_TCPIP_MAX_UDP_SOCKET_ID <= (uint16)(SocketId)) ) /* ETM_RID_E_ISD */
#else
# define ETM_COND_VALID_TCP_SOCKET_ID(SocketId)  ETM_COND_VALID_SOCKET_ID(SocketId)                              /* ETM_RID_E_ISD */
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES -- DEFINES
 *********************************************************************************************************************/

#if defined (TCPIP_SPECIAL_TCP_ACC_ENABLED)
# define ETM_SPECIAL_TCP_ACC_ENABLED TCPIP_SPECIAL_TCP_ACC_ENABLED
#else
# define ETM_SPECIAL_TCP_ACC_ENABLED STD_OFF
#endif

#if !defined (ETM_LOCAL)
# define ETM_LOCAL static
#endif

#if !defined (ETM_LOCAL_INLINE)
# define ETM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct
{
  uint16 Sid;               /* SID - ServiceId */
  boolean Evb;  /* 1 Bit */ /* EVB - EventBit */
  uint8 Gid;    /* 7 Bit */ /* GID - GroupId */
  uint8 Pid;                /* PID - SerivePrimitiveId */
  uint32 Len;               /* LEN - Length */
  uint8 ProtocolVersion;
  uint8 InterfaceVersion;
  uint8 Tid;                /* TID - TypeId */
  uint8 Rid;                /* RID - ResultId */
  uint16 PayloadLength;
  uint8 *Payload;           /* DAT */
  TcpIp_SocketIdType ReceivedSocketId;
  TcpIp_SockAddrInXType ReceivedRemoteAddress;
  boolean UsePhysAddr;      /* Answer service primitives via ethernet */
#if (ETM_ETHIF_ENABLED == STD_ON)
  uint8 ReceivedCtrlIdx;
  Eth_PhysAddrType ReceivedRemotePhysAddr;
#endif /* (ETM_ETHIF_ENABLED == STD_ON) */
} Etm_HeaderType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define ETM_START_SEC_VAR_CLEARED_8
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

ETM_LOCAL VAR(boolean, ETM_VAR_CLEARED) Etm_ModuleInitialized = FALSE;

#define ETM_STOP_SEC_VAR_CLEARED_8
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define ETM_START_SEC_VAR_NO_INIT_8
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

ETM_LOCAL VAR(boolean, ETM_VAR_NO_INIT) Etm_ModuleInitAll;
ETM_LOCAL VAR(boolean, ETM_VAR_NO_INIT) Etm_IpV4LinkAssigned;
ETM_LOCAL VAR(boolean, ETM_VAR_NO_INIT) Etm_IpV6LinkAssigned;
ETM_LOCAL VAR(boolean, ETM_VAR_NO_INIT) Etm_DataProcessingMode;

#if (ETM_NVM_ENABELD == STD_ON)
ETM_LOCAL VAR(boolean, ETM_VAR_NO_INIT) Etm_ProcessingStateChanged;
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
ETM_LOCAL VAR(uint8, ETM_VAR_NO_INIT) Etm_DhcpOptionCode;
#endif /* (ETM_USE_DHCP_PRIMITIVES == STD_ON) */

#define ETM_STOP_SEC_VAR_NO_INIT_8
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define ETM_START_SEC_VAR_NO_INIT_16
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

ETM_LOCAL VAR(uint16, ETM_VAR_NO_INIT) Etm_SendBufferLength;
ETM_LOCAL VAR(uint16, ETM_VAR_NO_INIT) Etm_EventDestSocketId;
ETM_LOCAL VAR(uint16, ETM_VAR_NO_INIT) Etm_CommandRetryCount;
ETM_LOCAL VAR(uint16, ETM_VAR_NO_INIT) Etm_SendDataCommandAlreadySend;

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
ETM_LOCAL VAR(uint16, ETM_VAR_NO_INIT) Etm_DhcpOptionLength;
#endif /* (ETM_USE_DHCP_PRIMITIVES == STD_ON) */

#define ETM_STOP_SEC_VAR_NO_INIT_16
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*****************************************************/

#define ETM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (ETM_NVM_ENABELD == STD_ON)
ETM_LOCAL VAR(uint8*,  ETM_VAR_NO_INIT) Etm_ProcessingStatePtr;
#endif /* (ETM_NVM_ENABELD == STD_ON) */

ETM_LOCAL VAR(TcpIp_SockAddrInXType, ETM_VAR_NO_INIT) Etm_EventDestAddr;
ETM_LOCAL VAR(Etm_HeaderType, ETM_VAR_NO_INIT) Etm_CommandHeader;
ETM_LOCAL VAR(uint8, ETM_VAR_NO_INIT) Etm_SendBuffer[ETM_MESSAGE_LENGTH_MAX];
ETM_LOCAL VAR(uint8, ETM_VAR_NO_INIT) Etm_CommandBuffer[ETM_STUB_MAX_COMMAND_SIZE];

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
ETM_LOCAL VAR(uint8, ETM_VAR_NO_INIT) Etm_ApplRespBuf[ETM_APPL_RESPONSE_BUFFER_LENGTH]; /* PRQA S 3218 */ /* MD_Etm_8.7_3218 */
#endif

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
ETM_LOCAL VAR(TcpIp_LocalAddrIdType, ETM_VAR_NO_INIT) Etm_DhcpLocalIpAddrId;
ETM_LOCAL VAR(uint8, ETM_VAR_NO_INIT) Etm_DhcpOptionBuf[ETM_DHCP_MAX_OPTION_LENGTH];
#endif /* (ETM_USE_DHCP_PRIMITIVES == STD_ON) */

#define ETM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define ETM_START_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Etm Helpers -- General */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VOpenCommandChannel(const uint8 ChannelIdx);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VCloseCommandChannel(const uint8 ChannelIdx);
ETM_LOCAL FUNC(uint8, ETM_CODE) Etm_VFindTestChannelIndex(const TcpIp_SocketIdType SocketId);
ETM_LOCAL FUNC(boolean, ETM_CODE) Etm_VTestChannelActive(const TcpIp_SocketIdType SocketId);
#if ((ETM_USE_ETH_PRIMITIVES == STD_ON) || (ETM_USE_PHY_PRIMITIVES == STD_ON) || (ETM_USE_DHCP_PRIMITIVES == STD_ON))
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetIndexFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2C(Etm_InterfaceType) Etm_Interfaces, uint8 InterfaceNumber, ETM_P2V(uint8) Index);
#endif
#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetTrcvIdxFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) TrcvIdx);
#endif
#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetComMIdentifierFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) ComMIdentifier);
#endif
#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetTcpIpLocalAddrIdFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) TcpIpLocalAddrId);
#endif
ETM_LOCAL FUNC(TcpIp_LocalAddrIdType, ETM_CODE) Etm_VGetLocAddrIdFromAddr(ETM_P2C(TcpIp_SockAddrType) Addr);

/* Etm Helpers -- General -- Buffer Handling */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VCheckLength(const uint32 TotalDataLength, const uint32 Offset, const uint32 LengthToReadOrWrite);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext8Bit(const uint8 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext16Bit(const uint16 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext32Bit(const uint32 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext8Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint8) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext16Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint16) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext32Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint32) ResultPtr);

/* Etm Helpers -- Message Handling */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntDataPtr(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint8*) ResultPtrPtr, ETM_P2V(uint16) ResultLengthPtr, const boolean CopyData);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntAddr(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(TcpIp_SockAddrType) ResultPtr, ETM_P2V(uint16) ResultLengthPtr /* can be used to calculate data offset for next parameter access */);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntIfNameLengthAndIgnoreData(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint16) ResultLengthPtr /* can be used to calculate data offset for next parameter access */);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderSid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint16) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderEvb(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(boolean) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderGid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderPid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderLen(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint32) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderTid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderRid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetSidInBuffer(const uint16 Sid, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetEvbInBuffer(const boolean Evb, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetGidInBuffer(const uint8 Gid, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetPidInBuffer(const uint8 Pid, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetLenInBuffer(const uint32 Len, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetTidInBuffer(const Etm_TypeIdType Tid, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetRidInBuffer(const Etm_ResultIdType Rid, ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetVersionsInBuffer(ETM_P2V(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VParseHeader(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(Etm_HeaderType) ResultPtr);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendMessage(ETM_P2C(Etm_HeaderType) Header, const Etm_TypeIdType Tid, const Etm_ResultIdType Rid, ETM_P2C(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendResponse(ETM_P2C(Etm_HeaderType) Header, const Etm_ResultIdType Rid, ETM_P2C(uint8) DataPtr, const uint32 DataLength);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendResponseWithoutPayload(ETM_P2C(Etm_HeaderType) Header, const Etm_ResultIdType Rid);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendEvent(ETM_P2V(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessEtmCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessGerneralCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessUdpCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessTcpCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIcmpV4Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIcmpV6Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIpV4Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIpV6Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessDhcpV4Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessDhcpV6Commands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessArpCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessNdpCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessEthCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessPhyCommands(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessUndefindedServicePrimitives(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSaveCommand(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) DataPtr, const uint32 DataPtrLength);

/* Etm Helpers -- Command Handling -- Group: GENERAL */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralGetVersion(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralStartTest(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralEndTest(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: UDP */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpCloseSocket(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpCreateAndBind(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpSendData(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpReceiveAndForward(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpConfigureSocket(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpShutdown(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: TCP */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpCloseSocket(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpCreateAndBind(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpSendData(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpReceiveAndForward(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpListenAndAccept(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpConnect(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpConfigureSocket(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpShutdown(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: IPv4 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv4StaticAddress(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv4StaticRoute(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: IPv6 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv6StaticAddress(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv6StaticRoute(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: DHCPv4 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpClientInit(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpClientStop(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpSetOption(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: DHCPv6 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpClientInit(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpClientStop(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpSetOption(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: ICMPv4 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VICMPv4EchoRequest(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: ICMPv6 */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VICMPv6EchoRequest(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: NDP */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VNdpClearCache(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: ETH */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VEthInterfaceUp(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VEthInterfaceDown(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Group: PHY */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhyReadSignalQuality(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhyReadDiagResult(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhySetPhyTestMode(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhySetPhyTxMode(ETM_P2C(Etm_HeaderType) Header);

/* Etm Helpers -- Command Handling -- Common APIs */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiCloseSocket(ETM_P2C(Etm_HeaderType) Header, const TcpIp_SocketIdType SocketId, const boolean Abort);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiCreateAndBind(ETM_P2C(Etm_HeaderType) Header, const TcpIp_ProtocolType Protocol);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiSendData(ETM_P2C(Etm_HeaderType) Header, const TcpIp_ProtocolType Protocol, const TcpIp_SocketIdType SocketId, const uint16 TotalLength, ETM_P2C(TcpIp_SockAddrType) DestinationAddressPtr, const uint16 DataLength);
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VApiSendDataPending(void);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiReceiveAndForward(ETM_P2C(Etm_HeaderType) Header, const TcpIp_ProtocolType Protocol);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiConfigureSocket(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiShutdown(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiStaticAddress(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiStaticRoute(ETM_P2C(Etm_HeaderType) Header);
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiEchoRequest(ETM_P2C(Etm_HeaderType) Header);
#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiInterface(ETM_P2C(Etm_HeaderType) Header, const uint8 Mode);
#endif

/* Etm Helpers -- NVM */
#if (ETM_NVM_ENABELD == STD_ON)
ETM_LOCAL FUNC(void, ETM_CODE) Etm_NvmSaveProcessingState(void);
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#define ETM_STOP_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#define ETM_START_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  ETM HELPERS -- GENERAL
 *********************************************************************************************************************/

/* PRQA S 6010, 6030 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VOpenCommandChannel(const uint8 ChannelIdx)
{
  Std_ReturnType result = E_OK;
  /* PRQA S 2981 2 */ /* MD_Etm_2981 */
  TcpIp_ProtocolType TmpProtocol = 0u;
  TcpIp_DomainType TmpDomain = TCPIP_AF_UNDEFINED;

  switch(ChannelIdx)
  {
    case ETM_CMD_CHAN_IDX_UDP_V4:
      TmpProtocol = (TcpIp_ProtocolType)TCPIP_SOCK_PROT_UDP;
      TmpDomain = (TcpIp_DomainType)TCPIP_AF_INET;
      break;
    case ETM_CMD_CHAN_IDX_UDP_V6:
      TmpProtocol = (TcpIp_ProtocolType)TCPIP_SOCK_PROT_UDP;
      TmpDomain = (TcpIp_DomainType)TCPIP_AF_INET6;
      break;
    case ETM_CMD_CHAN_IDX_TCP_V4:
      TmpProtocol = (TcpIp_ProtocolType)TCPIP_SOCK_PROT_TCP;
      TmpDomain = (TcpIp_DomainType)TCPIP_AF_INET;
      break;
    case ETM_CMD_CHAN_IDX_TCP_V6:
      TmpProtocol = (TcpIp_ProtocolType)TCPIP_SOCK_PROT_TCP;
      TmpDomain = (TcpIp_DomainType)TCPIP_AF_INET6;
      break;
    default:
      result = E_NOT_OK;
      break;
  }

  while(result == E_OK)
  {
    switch(Etm_CommandChannels[ChannelIdx].ChannelState)
    {
    case ETM_CMD_CHAN_DO_GETSOCKET:
      /* TCP & UDP */
      {
        result = TcpIp_EtmGetSocket(TmpDomain, TmpProtocol, &(Etm_CommandChannels[ChannelIdx].SocketId));

        if(result == E_OK)
        {
          Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_DO_BIND;
        }
      }
      break;
    case ETM_CMD_CHAN_DO_BIND:
      /* TCP & UDP */
      {
        uint16 ListenPort = ETM_STUB_LISTEN_PORT;

        TcpIp_LocalAddrIdType TmpLocAddrId = (TcpIp_LocalAddrIdType)TCPIP_LOCALADDRID_INV; /* PRQA S 2981 */ /* MD_Etm_2981 */

#if ((ETM_IPV6_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6))
        if(TmpDomain == TCPIP_AF_INET6)
        {
          TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6;
        }
#endif /* ((ETM_IPV6_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6)) */
#if ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4))
        if(TmpDomain == TCPIP_AF_INET)
        {
          TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4;
        }
#endif /* ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4)) */

        result = TcpIp_Bind(Etm_CommandChannels[ChannelIdx].SocketId, TmpLocAddrId, &ListenPort);

        if(result == E_OK)
        {
          if(TmpProtocol == TCPIP_SOCK_PROT_UDP)
          {
            /* UDP */
            Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_ACTIVE;
          }
          else
          {
            /* TCP */
            Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_DO_RX_BUFFER;
          }
        }
      }
      break;
    case ETM_CMD_CHAN_DO_RX_BUFFER:
      /* TCP only */
      {
        uint32 tmpBufSizeRx = ETM_TCPIP_BUFFER_SIZE_TCP_RX_CMD;

        result = TcpIp_ChangeParameter(Etm_CommandChannels[ChannelIdx].SocketId, TCPIP_PARAMID_TCP_RXWND_MAX, (ETM_P2V(uint8))&tmpBufSizeRx); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_Api */

        if(result == E_OK)
        {
          Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_DO_TX_BUFFER;
        }
      }
      break;
    case ETM_CMD_CHAN_DO_TX_BUFFER:
      /* TCP only */
      {
        uint32 tmpBufSizeTx = ETM_TCPIP_BUFFER_SIZE_TCP_TX_CMD;

        result = TcpIp_ChangeParameter(Etm_CommandChannels[ChannelIdx].SocketId, TCPIP_PARAMID_V_TCP_TXBUFSIZE, (ETM_P2V(uint8))&tmpBufSizeTx); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_Api */

        if(result == E_OK)
        {
          Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_DO_LISTEN;
        }
      }
      break;
    case ETM_CMD_CHAN_DO_LISTEN:
      /* TCP only */
      {
#if (ETM_TCP_ENABLED == STD_ON)
        result = TcpIp_TcpListen(Etm_CommandChannels[ChannelIdx].SocketId, 1u);

        if(result == E_OK)
        {
          Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_ACTIVE;
        }
#else
        Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_INACTIVE;
#endif
      }
      break;
    case ETM_CMD_CHAN_INACTIVE: /* fall through */
    case ETM_CMD_CHAN_ACTIVE:   /* fall through */
    default:
      /* nothing to do -- channel is active or not used (inactive) */
      result = E_NOT_OK;
      break;
    }
  }
} /* Etm_VOpenCommandChannel() */

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VCloseCommandChannel(const uint8 ChannelIdx)
{
  if((ChannelIdx < ETM_CHANNELS_COMMAND) && (Etm_CommandChannels[ChannelIdx].SocketId != ETM_INV_SOCKET_ID))
  {
    (void)TcpIp_Close(Etm_CommandChannels[ChannelIdx].SocketId, TRUE);
    Etm_CommandChannels[ChannelIdx].SocketId = ETM_INV_SOCKET_ID;
    Etm_CommandChannels[ChannelIdx].ChannelState = ETM_CMD_CHAN_DO_GETSOCKET;
  }
}

ETM_LOCAL FUNC(uint8, ETM_CODE) Etm_VFindTestChannelIndex(const TcpIp_SocketIdType SocketId)
{
  uint8 Result = ETM_INV_SOCKET_ID;
  uint8 Index;

  for(Index = 0u;
      Index < ETM_CHANNELS_TEST;
      Index++)
  {
    if(Etm_TestChannels[Index].SocketId == SocketId)
    {
      Result = Index;
      break;
    }
  }

  return Result;
}

ETM_LOCAL FUNC(boolean, ETM_CODE) Etm_VTestChannelActive(const TcpIp_SocketIdType SocketId)
{
  return (boolean)(Etm_VFindTestChannelIndex(SocketId) != ETM_INV_SOCKET_ID);
}

#if ((ETM_USE_ETH_PRIMITIVES == STD_ON) || (ETM_USE_PHY_PRIMITIVES == STD_ON) || (ETM_USE_DHCP_PRIMITIVES == STD_ON))
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetIndexFromHeader(
  ETM_P2C(Etm_HeaderType) Header,
  ETM_P2C(Etm_InterfaceType) Etm_Interfaces,
  uint8 InterfaceNumber,
  ETM_P2V(uint8) Index)
{
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;

  Result = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);

  if(Result == E_OK)
  {
    Result = E_NOT_OK;

    /* check interface min length */
    if(InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH)
    {
      uint16 Idx;
      uint16 IdxInterfaces;

      for(IdxInterfaces = 0u;
          IdxInterfaces < InterfaceNumber;
          IdxInterfaces++)
      {
        boolean InterfaceFound = FALSE;

        /* check interface length */
        if(InterfaceNameLength == (Etm_Interfaces[IdxInterfaces].EndIdx - Etm_Interfaces[IdxInterfaces].StartIdx))
        {
          InterfaceFound = TRUE;

          for(Idx = 0u;
              Idx < (Etm_Interfaces[IdxInterfaces].EndIdx - Etm_Interfaces[IdxInterfaces].StartIdx);
              Idx++)
          {
            if(Etm_InterfaceNames[Idx + Etm_Interfaces[IdxInterfaces].StartIdx] != Header->Payload[Idx + 2u /* text length field */])
            {
              InterfaceFound = FALSE;
              break;
            }
          }
        }

        if(InterfaceFound == TRUE)
        {
          *Index = Etm_Interfaces[IdxInterfaces].Index;
          Result = E_OK;
          break;
        }
      }
    }
  }

  return Result;
}
#endif

#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetTrcvIdxFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) TrcvIdx)
{
  return Etm_VGetIndexFromHeader(Header, Etm_PhyInterfaces, ETM_NUMBER_PHY_INTERFACES, TrcvIdx);
}
#endif

#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetComMIdentifierFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) ComMIdentifier)
{
  return Etm_VGetIndexFromHeader(Header, Etm_EthInterfaces, ETM_NUMBER_ETH_INTERFACES, ComMIdentifier);
}
#endif

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetTcpIpLocalAddrIdFromHeader(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) TcpIpLocalAddrId)
{
  return Etm_VGetIndexFromHeader(Header, Etm_DhcpInterfaces, ETM_NUMBER_DHCP_INTERFACES, TcpIpLocalAddrId);
}
#endif

/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
ETM_LOCAL FUNC(TcpIp_LocalAddrIdType, ETM_CODE) Etm_VGetLocAddrIdFromAddr(ETM_P2C(TcpIp_SockAddrType) Addr)
{
  TcpIp_LocalAddrIdType TmpLocAddrId = TCPIP_LOCALADDRID_INV;
  TcpIp_SockAddrInXType IpAddress = { 0u };
  TcpIp_SockAddrInXType DefaultRouter = { 0u };
  uint8 Netmask[ETM_DATA_LEN_ADDRESS_IPV6] = { 0u };

  TcpIp_DomainType Domain = Addr->domain;

  if(Domain == TCPIP_AF_INET6)
  {
#if (ETM_IPV6_ENABLED == STD_ON)
    IpAddress.sin6_family = TCPIP_AF_INET6;

# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6_MULTI)
    if(IPV6_ADDR_IS_MULTICAST(((ETM_P2C(TcpIp_SockAddrInet6Type))Addr)[0u]) /* IP=MULTI */) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6_MULTI;
    }
    else
# endif
# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6_ANY)
    /* Compare Addr to IpAddress who is initializes with zeros (any address) */
    if(TRUE == TcpIp_VSockIpAddrIsEqual((ETM_P2C(TcpIp_SockAddrBaseType))&IpAddress, (ETM_P2C(TcpIp_SockAddrBaseType))Addr) /* IP=ANY */) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6_ANY;
    }
    else
# endif
# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6)
    /* PRQA S 3415 2 */ /* MD_Etm_12.4_3415_Side */
    if((E_OK == TcpIp_GetIpAddr((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6, (ETM_P2V(TcpIp_SockAddrType))&IpAddress, &Netmask[0u], (ETM_P2V(TcpIp_SockAddrType))&DefaultRouter)) && /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      (TRUE == TcpIp_VSockIpAddrIsEqual((ETM_P2C(TcpIp_SockAddrBaseType))&IpAddress, (ETM_P2C(TcpIp_SockAddrBaseType))Addr) /* IP=LOCAL */)) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6;
    }
    else
# endif
    {
# if ((defined ETM_TCPIP_LOCAL_ADDRESS_IDV6) && (ETM_TCPIP_LOCAL_ADDRESS_USE_DEFAULT == STD_ON))
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6;
# else
      TmpLocAddrId = (TcpIp_LocalAddrIdType)TCPIP_LOCALADDRID_INV;
# endif
    }
#endif /* (ETM_IPV6_ENABLED == STD_ON) */
  }
  else if(Domain == TCPIP_AF_INET)
  {
#if (ETM_IPV4_ENABLED == STD_ON)
    ((ETM_P2V(TcpIp_SockAddrType))&IpAddress)->domain = TCPIP_AF_INET; /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4_MULTI)
    if(IPV4_ADDR_IS_MULTICAST(((ETM_P2C(TcpIp_SockAddrInetType))Addr)->addr[0u]) /* IP=MULTI */) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4_MULTI;
    }
    else
# endif
# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4_ANY)
    /* Compare Addr to IpAddress who is initializes with zeros (any address) */
    if(TRUE == TcpIp_VSockIpAddrIsEqual((ETM_P2C(TcpIp_SockAddrBaseType))&IpAddress, (ETM_P2C(TcpIp_SockAddrBaseType))Addr) /* IP=ANY */) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4_ANY;
    }
    else
# endif
# if (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4)
    /* PRQA S 3415 2 */ /* MD_Etm_12.4_3415_Side */
    if((E_OK == TcpIp_GetIpAddr((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4, (ETM_P2V(TcpIp_SockAddrType))&IpAddress, &Netmask[0u], (ETM_P2V(TcpIp_SockAddrType))&DefaultRouter)) && /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      (TRUE == TcpIp_VSockIpAddrIsEqual((ETM_P2C(TcpIp_SockAddrBaseType))&IpAddress, (ETM_P2C(TcpIp_SockAddrBaseType))Addr) /* IP=LOCAL */)) /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
    {
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4;
    }
    else
# endif
    {
# if ((defined ETM_TCPIP_LOCAL_ADDRESS_IDV4) && (ETM_TCPIP_LOCAL_ADDRESS_USE_DEFAULT == STD_ON))
      TmpLocAddrId = (TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4;
# else
      TmpLocAddrId = (TcpIp_LocalAddrIdType)TCPIP_LOCALADDRID_INV;
# endif
    }
#endif /* (ETM_IPV4_ENABLED == STD_ON) */
  }
  else
  {
    /* MISRA */
  }

  return TmpLocAddrId;
}

/**********************************************************************************************************************
 *  ETM HELPERS -- GENERAL -- BUFFER HANDLING
 *********************************************************************************************************************/

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VCheckLength(const uint32 TotalDataLength, const uint32 Offset, const uint32 LengthToReadOrWrite)
{
  return (Std_ReturnType)((TotalDataLength >= (Offset + LengthToReadOrWrite)) ? E_OK : E_NOT_OK);
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext8Bit(const uint8 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength)
{
  Std_ReturnType Result = Etm_VCheckLength(ResultDataLength, Offset, 1u); /* Check data length to write */

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultDataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(Result == E_OK)
  {
    ResultDataPtr[Offset] = Data;
  }

  return Result;
} /* Etm_VSetNext8Bit() */

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext16Bit(const uint16 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength)
{
  Std_ReturnType Result = Etm_VCheckLength(ResultDataLength, Offset, 2u); /* Check data length to write */

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultDataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(Result == E_OK)
  {
    ResultDataPtr[Offset     ] = (uint8)(Data >> 8u);
    ResultDataPtr[Offset + 1u] = (uint8)(Data);
  }

  return Result;
} /* Etm_VSetNext16Bit() */

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetNext32Bit(const uint32 Data, const uint32 Offset, ETM_P2V(uint8) ResultDataPtr, const uint32 ResultDataLength)
{
  Std_ReturnType Result = Etm_VCheckLength(ResultDataLength, Offset, 4u); /* Check data length to write */

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultDataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(Result == E_OK)
  {
    ResultDataPtr[Offset     ] = (uint8)(Data >> 24u);
    ResultDataPtr[Offset + 1u] = (uint8)(Data >> 16u);
    ResultDataPtr[Offset + 2u] = (uint8)(Data >> 8u);
    ResultDataPtr[Offset + 3u] = (uint8)(Data);
  }

  return Result;
} /* Etm_VSetNext32Bit() */

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext8Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint8) ResultPtr)
{
  Std_ReturnType Result;

  const uint16 ConstLength = 1u;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  Result = Etm_VCheckLength(DataLength, Offset, ConstLength); /* Check data length to read */

  if(Result == E_OK)
  {
    *ResultPtr = DataPtr[Offset];
  }

  return Result;
} /* Etm_VGetNext8Bit() */

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext16Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint16) ResultPtr)
{
  Std_ReturnType Result;

  const uint16 ConstLength = 2u;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  Result = Etm_VCheckLength(DataLength, Offset, ConstLength); /* Check data length to read */

  if(Result == E_OK)
  {
    *ResultPtr  = (uint16)(((uint16)DataPtr[Offset     ]) << 8u);
    *ResultPtr |= (uint16) ((uint16)DataPtr[Offset + 1u]);
  }

  return Result;
} /* Etm_VGetNext16Bit() */

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetNext32Bit(ETM_P2C(uint8) DataPtr, const uint32 DataLength, const uint32 Offset, ETM_P2V(uint32) ResultPtr)
{
  Std_ReturnType Result;

  const uint16 ConstLength = 4u;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  Result = Etm_VCheckLength(DataLength, Offset, ConstLength); /* Check data length to read */

  if(Result == E_OK)
  {
    *ResultPtr  = (uint32)(((uint32)DataPtr[Offset     ]) << 24u);
    *ResultPtr |= (uint32)(((uint32)DataPtr[Offset + 1u]) << 16u);
    *ResultPtr |= (uint32)(((uint32)DataPtr[Offset + 2u]) << 8u);
    *ResultPtr |= (uint32) ((uint32)DataPtr[Offset + 3u]);
  }

  return Result;
} /* Etm_VGetNext32Bit() */

/**********************************************************************************************************************
 *  ETM HELPERS -- MESSAGE HANDLING
 *********************************************************************************************************************/

/* PRQA S 6060 1 */ /* MD_MSR_STPAR */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntDataPtr(
  ETM_P2C(uint8) DataPtr,
  const uint32 DataLength,
  const uint32 Offset,
  ETM_P2V(uint8*) ResultPtrPtr,
  ETM_P2V(uint16) ResultLengthPtr, /* in: length of provided buffer, out: length of copied data */
  const boolean CopyData)
{
  Std_ReturnType Result;

  uint16 Index;
  uint16 ResultLength = 0u;

  Result = Etm_VGetNext16Bit(DataPtr, DataLength, Offset, &ResultLength);

  if((Result == E_OK) &&
    ((Offset + 2u /* uint16 length */ + ResultLength) <= DataLength))
  {
    if(CopyData == TRUE)
    {
      if(ResultLength <= *ResultLengthPtr) /* check target array length */
      {
        for(Index = 0u;
            Index < ResultLength;
            Index++)
        {
          (*ResultPtrPtr)[Index] = DataPtr[Offset + 2u /* uint16 length */ + Index];
        }

        *ResultLengthPtr = ResultLength;
        Result = E_OK;
      }
      else
      {
        Result = E_NOT_OK;
      }
    }
    else
    {
      *ResultPtrPtr = (ETM_P2V(uint8))&DataPtr[Offset + 2u /* uint16 length */]; /* PRQA S 0311 */ /* MD_Etm_11.4_0311_Const */
      *ResultLengthPtr = ResultLength;
      Result = E_OK;
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntAddr(
  ETM_P2C(uint8) DataPtr,
  const uint32 DataLength,
  const uint32 Offset,
  ETM_P2V(TcpIp_SockAddrType) ResultPtr,
  ETM_P2V(uint16) ResultLengthPtr /* can be used to calculate data offset for next parameter access */)
{
  Std_ReturnType Result;

  uint16 ResultLength = 16u;
  /* PRQA S 0310, 3305 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
  uint8 *AddrDataPtr = ((ETM_P2V(uint8))&(((ETM_P2V(TcpIp_SockAddrInet6Type))ResultPtr)->addr)); /*lint !e545 */

  Result = Etm_VGetVIntDataPtr(DataPtr, DataLength, Offset, &AddrDataPtr, &ResultLength, TRUE);
  *ResultLengthPtr = ResultLength;

  if(Result == E_OK)
  {
    if(ResultLength == ETM_DATA_LEN_ADDRESS_IPV4)
    {
      ResultPtr->domain = TCPIP_AF_INET;
    }
    else if(ResultLength == ETM_DATA_LEN_ADDRESS_IPV6)
    {
      ResultPtr->domain = TCPIP_AF_INET6;
    }
    else
    {
      Result = E_NOT_OK;
    }
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetVIntIfNameLengthAndIgnoreData(
  ETM_P2C(uint8) DataPtr,
  const uint32 DataLength,
  const uint32 Offset,
  ETM_P2V(uint16) ResultLengthPtr /* can be used to calculate data offset for next parameter access */)
{
  Std_ReturnType Result;

  uint8 TmpData = 0u;
  uint8 *TmpDataPtr = &TmpData;
  uint16 TmpDataLength = 0u;

  Result = Etm_VGetVIntDataPtr(DataPtr, DataLength, Offset, &TmpDataPtr, &TmpDataLength, FALSE);
  *ResultLengthPtr = TmpDataLength;

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderSid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint16) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= (ETM_MESSAGE_OFFSET_SID + 2u /* DataSize */))
  {
    Result = Etm_VGetNext16Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_SID, ResultPtr);
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderEvb(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(boolean) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= (ETM_MESSAGE_OFFSET_EVB_GID + 1u /* DataSize */))
  {
    Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_EVB_GID, (ETM_P2V(uint8))ResultPtr);
  }

  *ResultPtr = (boolean)((*((ETM_P2V(uint8))ResultPtr) & ETM_UINT8_MASK_EVB_BIT) > 1u); /* only TRUE if EVB==1 */

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderGid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= (ETM_MESSAGE_OFFSET_EVB_GID + 1u /* DataSize */))
  {
    Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_EVB_GID, ResultPtr);
  }

  *ResultPtr = (uint8)(*ResultPtr & ETM_UINT8_MASK_GID);

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderPid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= (ETM_MESSAGE_OFFSET_PID + 1u /* DataSize */))
  {
    Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_PID, ResultPtr);
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderLen(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint32) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= (ETM_MESSAGE_OFFSET_LEN + 4u /* DataSize */))
  {
    Result = Etm_VGetNext32Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_LEN, ResultPtr);
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderTid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr)
{
  Std_ReturnType Result;
  uint32 LenField = 0u;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  Result = Etm_VGetHeaderLen(DataPtr, DataLength, &LenField);

  if((Result == E_OK) && (LenField >= 7u /* necessary data size to cover TID field */))
  {
    if(DataLength >= (ETM_MESSAGE_OFFSET_TID + 1u /* DataSize */))
    {
      Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_TID, ResultPtr);
    }
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VGetHeaderRid(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(uint8) ResultPtr)
{
  Std_ReturnType Result;
  uint32 LenField = 0u;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  Result = Etm_VGetHeaderLen(DataPtr, DataLength, &LenField);

  if((Result == E_OK) && (LenField >= 8u /* necessary data size to cover RID field */))
  {
    if(DataLength >= (ETM_MESSAGE_OFFSET_RID + 1u /* DataSize */))
    {
      Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_RID, ResultPtr);
    }
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetSidInBuffer(const uint16 Sid, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  return Etm_VSetNext16Bit(Sid, ETM_MESSAGE_OFFSET_SID, DataPtr, DataLength);
}

/* PRQA S 3673 1 */ /* MD_Etm_16.7_3673 */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetEvbInBuffer(const boolean Evb, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  Std_ReturnType Result;

#if (ETM_STUB_PROTOCOL_VERSION >= 0x00000006uL) /* Version 0.6 */
  {
    uint8 TmpData = 0u;

    Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_EVB_GID, &TmpData);

    /* Read GID (7-Bit) from buffer and merge with EVB (1-Bit) to uint8 */
    TmpData = (uint8)((TmpData & ETM_UINT8_MASK_GID) | (uint8)((uint8)Evb << 7u));

    if(Result == E_OK)
    {
      Result = Etm_VSetNext8Bit(TmpData, ETM_MESSAGE_OFFSET_EVB_GID, DataPtr, DataLength);
    }
  }
#else
  Result = E_OK;
  ETM_DUMMY_STATEMENT_CONST(Evb);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETM_DUMMY_STATEMENT_CONST(DataPtr);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETM_DUMMY_STATEMENT_CONST(DataLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetGidInBuffer(const uint8 Gid, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  Std_ReturnType Result;
  uint8 TmpData = 0u;

  Result = Etm_VGetNext8Bit(DataPtr, DataLength, ETM_MESSAGE_OFFSET_EVB_GID, &TmpData);

  /* Read EVB (1-Bit) from buffer and merge with GID (7-Bit) to uint8 */
  TmpData = (uint8)((TmpData & ETM_UINT8_MASK_EVB_BIT) | (Gid & ETM_UINT8_MASK_GID));

  if(Result == E_OK)
  {
    Result = Etm_VSetNext8Bit(TmpData, ETM_MESSAGE_OFFSET_EVB_GID, DataPtr, DataLength);
  }

  return Result;
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetPidInBuffer(const uint8 Pid, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  return Etm_VSetNext8Bit(Pid, ETM_MESSAGE_OFFSET_PID, DataPtr, DataLength);
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetLenInBuffer(const uint32 Len, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  return Etm_VSetNext32Bit(Len, ETM_MESSAGE_OFFSET_LEN, DataPtr, DataLength);
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetTidInBuffer(const Etm_TypeIdType Tid, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  return Etm_VSetNext8Bit((uint8)Tid, ETM_MESSAGE_OFFSET_TID, DataPtr, DataLength);
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetRidInBuffer(const Etm_ResultIdType Rid, ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  return Etm_VSetNext8Bit((uint8)Rid, ETM_MESSAGE_OFFSET_RID, DataPtr, DataLength);
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSetVersionsInBuffer(ETM_P2V(uint8) DataPtr, const uint32 DataLength)
{
  Std_ReturnType Result;

  Result  = Etm_VSetNext8Bit(ETM_SOMEIP_PROTOCOL_VERSION, ETM_MESSAGE_OFFSET_PROTO_VER, DataPtr, DataLength);
  Result |= Etm_VSetNext8Bit(ETM_SOMEIP_INTERFACE_VERSION, ETM_MESSAGE_OFFSET_IFACE_VER, DataPtr, DataLength);

  return Result;
}

/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VParseHeader(ETM_P2C(uint8) DataPtr, const uint32 DataLength, ETM_P2V(Etm_HeaderType) ResultPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  Etm_CheckDetErrorReturnValue(ETM_COND_VALID_PTR(ResultPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER, E_NOT_OK);
  /* ------------------------------------------------- */

  if(DataLength >= ETM_HEADER_LENGTH)
  {
    Result  = Etm_VGetHeaderSid(DataPtr, DataLength, &(ResultPtr->Sid));
    Result |= Etm_VGetHeaderEvb(DataPtr, DataLength, &(ResultPtr->Evb));
    Result |= Etm_VGetHeaderGid(DataPtr, DataLength, &(ResultPtr->Gid));
    Result |= Etm_VGetHeaderPid(DataPtr, DataLength, &(ResultPtr->Pid));
    Result |= Etm_VGetHeaderLen(DataPtr, DataLength, &(ResultPtr->Len));
    Result |= Etm_VGetHeaderTid(DataPtr, DataLength, &(ResultPtr->Tid));
    Result |= Etm_VGetHeaderRid(DataPtr, DataLength, &(ResultPtr->Rid));

    ResultPtr->ProtocolVersion = ETM_SOMEIP_PROTOCOL_VERSION;
    ResultPtr->InterfaceVersion = ETM_SOMEIP_INTERFACE_VERSION;
    ResultPtr->PayloadLength = (uint16)((ResultPtr->Len >= 8u) ? (ResultPtr->Len - 8u) : 0u);
    ResultPtr->Payload = (ETM_P2V(uint8))&DataPtr[ETM_MESSAGE_OFFSET_DAT]; /* PRQA S 0311 */ /* MD_Etm_11.4_0311_Const */
  }

  return Result;
}

/* PRQA S 6030, 6050, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendMessage(
  ETM_P2C(Etm_HeaderType) Header,
  const Etm_TypeIdType Tid,
  const Etm_ResultIdType Rid,
  ETM_P2C(uint8) DataPtr,
  const uint32 DataLength)
{
  Std_ReturnType Result;

  uint32 Index;
  uint16 FullMessageLength;

  if(DataLength == 0u)
  {
    if(Etm_SendBufferLength == 0u)
    {
      Etm_SendBufferLength = ETM_HEADER_LENGTH;
    }
    FullMessageLength = Etm_SendBufferLength;
  }
  else
  {
    FullMessageLength = (uint16)(ETM_HEADER_LENGTH + DataLength);
  }

  Result  = Etm_VSetSidInBuffer(ETM_STUB_SERVICE_ID, Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetEvbInBuffer((boolean)(Tid == ETM_TID_EVENT) /* Set EVB regarding to TID */, Etm_SendBuffer, FullMessageLength); /* PRQA S 2985 */ /* MD_Etm_2985 */
  Result |= Etm_VSetGidInBuffer(Header->Gid, Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetPidInBuffer(Header->Pid, Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetLenInBuffer(((uint32)FullMessageLength - (uint32)8u /* some fields not coverd by LEN */), Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetTidInBuffer(Tid, Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetRidInBuffer(Rid, Etm_SendBuffer, FullMessageLength);
  Result |= Etm_VSetVersionsInBuffer(Etm_SendBuffer, FullMessageLength);

  if((Result == E_OK) &&
    (FullMessageLength <= ETM_MESSAGE_LENGTH_MAX))
  {
    if(DataPtr != NULL_PTR)
    {
      for(Index = 0u;
          Index < (uint16)(FullMessageLength - ETM_MESSAGE_OFFSET_DAT);
          Index++)
      {
        Etm_SendBuffer[ETM_MESSAGE_OFFSET_DAT + Index] = DataPtr[Index];
      }
    }

#if (ETM_TCP_ENABLED == STD_ON)
    if((Header->UsePhysAddr == FALSE) && ETM_COND_VALID_TCP_SOCKET_ID(Header->ReceivedSocketId))
    {
      if(E_OK == TcpIp_TcpTransmit(Header->ReceivedSocketId, Etm_SendBuffer, FullMessageLength, FALSE))
      {
        Etm_SendBufferLength = 0u;
      }
      return;
    }
    else
#endif
    if((Header->UsePhysAddr == FALSE) && ETM_COND_VALID_UDP_SOCKET_ID(Header->ReceivedSocketId))
    {
      if(TCPIP_OK == TcpIp_UdpTransmit(Header->ReceivedSocketId, Etm_SendBuffer, (ETM_P2V(TcpIp_SockAddrType))&(Header->ReceivedRemoteAddress), FullMessageLength)) /* PRQA S 0310, 0311 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_11.4_0311_Const */
      {
        Etm_SendBufferLength = 0u;
      }
      return;
    }
    else
#if (ETM_ETHIF_ENABLED == STD_ON)
    if((Header->UsePhysAddr == TRUE) &&
       (Header->ReceivedSocketId == 0u) &&
      ((Header->ReceivedRemotePhysAddr[0u] != 0u) ||
       (Header->ReceivedRemotePhysAddr[1u] != 0u) ||
       (Header->ReceivedRemotePhysAddr[2u] != 0u) ||
       (Header->ReceivedRemotePhysAddr[3u] != 0u) ||
       (Header->ReceivedRemotePhysAddr[4u] != 0u) ||
       (Header->ReceivedRemotePhysAddr[5u] != 0u)))
    {
      uint8 TmpBufIdx = 0u;
      uint16 TmpBufLen = (uint16)((DataLength == 0u) ? (18u /* ETH */ + ETM_HEADER_LENGTH /* ETM */ + 1u /* DATA */) : (18u /* ETH */ + ETM_HEADER_LENGTH /* ETM */ + DataLength /* DATA */));
      uint16 BufLenParam = TmpBufLen;
      Eth_DataType *TmpBufPtr;
      if(BUFREQ_OK == EthIf_ProvideTxBuffer(Header->ReceivedCtrlIdx, ETM_ETHIF_FRAME_TYPE, 0u, &TmpBufIdx, &TmpBufPtr, &BufLenParam))
      {
        if(BufLenParam >= TmpBufLen)
        {
          /* PRQA S 0310, 0314 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy */
          VStdLib_MemCpy((ETM_P2V(void))TmpBufPtr, (ETM_P2C(void))Etm_SendBuffer, TmpBufLen);
          Etm_SendBufferLength = 0u;
          (void)EthIf_Transmit(Header->ReceivedCtrlIdx, TmpBufIdx, ETM_ETHIF_FRAME_TYPE, FALSE, TmpBufLen, (ETM_P2V(uint8))&(Header->ReceivedRemotePhysAddr)); /*lint !e545 */ /* PRQA S 0310, 0311 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_11.4_0311_Const */
        }
      }
    }
    else
#endif /* (ETM_ETHIF_ENABLED == STD_ON) */
    {
      /* MISRA */
    }
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendResponse(ETM_P2C(Etm_HeaderType) Header, const Etm_ResultIdType Rid, ETM_P2C(uint8) DataPtr, const uint32 DataLength)
{
  Etm_VSendMessage(Header, ETM_TID_RESPONSE, Rid, DataPtr, DataLength);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendResponseWithoutPayload(ETM_P2C(Etm_HeaderType) Header, const Etm_ResultIdType Rid)
{
  Etm_VSendMessage(Header, ETM_TID_RESPONSE, Rid, NULL_PTR, 0u);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VSendEvent(ETM_P2V(Etm_HeaderType) Header)
{
  Header->ReceivedSocketId = (TcpIp_SocketIdType)Etm_EventDestSocketId;
  (void)IpBase_CopySockAddr((ETM_P2V(IpBase_SockAddrType))&(Header->ReceivedRemoteAddress), (ETM_P2C(IpBase_SockAddrType))&Etm_EventDestAddr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  Etm_VSendMessage(Header, ETM_TID_EVENT, ETM_RID_E_OK, NULL_PTR, 0u);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING
 *********************************************************************************************************************/

/* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessEtmCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Gid)
  {
  case ETM_GID_GENERAL:
    Etm_VProcessGerneralCommands(Header);
    break;
  case ETM_GID_UDP:
    Etm_VProcessUdpCommands(Header);
    break;
  case ETM_GID_TCP:
    Etm_VProcessTcpCommands(Header);
    break;
  case ETM_GID_ICMP:
    Etm_VProcessIcmpV4Commands(Header);
    break;
  case ETM_GID_ICMPv6:
    Etm_VProcessIcmpV6Commands(Header);
    break;
  case ETM_GID_IP:
    Etm_VProcessIpV4Commands(Header);
    break;
  case ETM_GID_IPv6:
    Etm_VProcessIpV6Commands(Header);
    break;
  case ETM_GID_DHCP:
    Etm_VProcessDhcpV4Commands(Header);
    break;
  case ETM_GID_DHCPv6:
    Etm_VProcessDhcpV6Commands(Header);
    break;
  case ETM_GID_ARP:
    Etm_VProcessArpCommands(Header);
    break;
  case ETM_GID_NDP:
    Etm_VProcessNdpCommands(Header);
    break;
  case ETM_GID_ETH:
    Etm_VProcessEthCommands(Header);
    break;
  case ETM_GID_PHY:
    Etm_VProcessPhyCommands(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessGerneralCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_GET_VERSION:
    Etm_VGeneralGetVersion(Header);
    break;
  case ETM_PID_START_TEST:
    Etm_VGeneralStartTest(Header);
    break;
  case ETM_PID_END_TEST:
    Etm_VGeneralEndTest(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessUdpCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_UDP_CLOSE_SOCKET:
    Etm_VUdpCloseSocket(Header);
    break;
  case ETM_PID_UDP_CREATE_AND_BIND:
    Etm_VUdpCreateAndBind(Header);
    break;
  case ETM_PID_UDP_SEND_DATA:
    Etm_VUdpSendData(Header);
    break;
  case ETM_PID_UDP_RECEIVE_AND_FORWARD:
    Etm_VUdpReceiveAndForward(Header);
    break;
  case ETM_PID_UDP_CONFIGURE_SOCKET:
    Etm_VUdpConfigureSocket(Header);
    break;
  case ETM_PID_UDP_SHUTDOWN:
    Etm_VUdpShutdown(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessTcpCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_TCP_CLOSE_SOCKET:
    Etm_VTcpCloseSocket(Header);
    break;
  case ETM_PID_TCP_CREATE_AND_BIND:
    Etm_VTcpCreateAndBind(Header);
    break;
  case ETM_PID_TCP_SEND_DATA:
    Etm_VTcpSendData(Header);
    break;
  case ETM_PID_TCP_RECEIVE_AND_FORWARD:
    Etm_VTcpReceiveAndForward(Header);
    break;
  case ETM_PID_TCP_LISTEN_AND_ACCEPT:
    Etm_VTcpListenAndAccept(Header);
    break;
  case ETM_PID_TCP_CONNECT:
    Etm_VTcpConnect(Header);
    break;
  case ETM_PID_TCP_CONFIGURE_SOCKET:
    Etm_VTcpConfigureSocket(Header);
    break;
  case ETM_PID_TCP_SHUTDOWN:
    Etm_VTcpShutdown(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIcmpV4Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_ICMP_ECHO_REQUEST:
    Etm_VICMPv4EchoRequest(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIcmpV6Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_ICMP_ECHO_REQUEST:
    Etm_VICMPv6EchoRequest(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIpV4Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_IP_STATIC_ADDRESS:
    Etm_VIPv4StaticAddress(Header);
    break;
  case ETM_PID_IP_STATIC_ROUTE:
    Etm_VIPv4StaticRoute(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessIpV6Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_IPV6_STATIC_ADDRESS:
    Etm_VIPv6StaticAddress(Header);
    break;
  case ETM_PID_IPV6_STATIC_ROUTE:
    Etm_VIPv6StaticRoute(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessDhcpV4Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_DHCP_INIT_DHCP_CLIENT:
    Etm_VDHCPv4DhcpClientInit(Header);
    break;
  case ETM_PID_DHCP_STOP_DHCP_CLIENT:
    Etm_VDHCPv4DhcpClientStop(Header);
    break;
  case ETM_PID_DHCP_SET_DHCP_OPTION:
    Etm_VDHCPv4DhcpSetOption(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessDhcpV6Commands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_DHCPV6_INIT_DHCP_CLIENT:
    Etm_VDHCPv6DhcpClientInit(Header);
    break;
  case ETM_PID_DHCPV6_STOP_DHCP_CLIENT:
    Etm_VDHCPv6DhcpClientStop(Header);
    break;
  case ETM_PID_DHCPV6_SET_DHCP_OPTION:
    Etm_VDHCPv6DhcpSetOption(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessArpCommands(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessNdpCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_NDP_CLEAR_CACHE:
    Etm_VNdpClearCache(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessEthCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_ETH_INTERFACE_UP:
    Etm_VEthInterfaceUp(Header);
    break;
  case ETM_PID_ETH_INTERFACE_DOWN:
    Etm_VEthInterfaceDown(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessPhyCommands(ETM_P2C(Etm_HeaderType) Header)
{
  switch(Header->Pid)
  {
  case ETM_PID_PHY_READ_SIGNAL_QUALITY:
    Etm_VPhyReadSignalQuality(Header);
    break;
  case ETM_PID_PHY_READ_DIAG_RESULT:
    Etm_VPhyReadDiagResult(Header);
    break;
  case ETM_PID_PHY_ACTIVATE_TEST_MODE:
    Etm_VPhySetPhyTestMode(Header);
    break;
  case ETM_PID_PHY_SET_PHY_TX_MODE:
    Etm_VPhySetPhyTxMode(Header);
    break;
  default:
    Etm_VProcessUndefindedServicePrimitives(Header);
    break;
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VProcessUndefindedServicePrimitives(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
  uint16 ApplRespBufLen = ETM_APPL_RESPONSE_BUFFER_LENGTH;
  Etm_ResultIdType rid = ApplEtm_UndefinedServicePrimitive(Header->Gid, Header->Pid, Header->PayloadLength, Header->Payload, &ApplRespBufLen, Etm_ApplRespBuf);
  if(ApplRespBufLen > ETM_APPL_RESPONSE_BUFFER_LENGTH)
  {
    /* ignore payload if user return invalid payload length */
    ApplRespBufLen = 0u;
  }
  Etm_VSendResponse(Header, rid, Etm_ApplRespBuf, ApplRespBufLen);
#else
  Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_NTF);
#endif
}

ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VSaveCommand(ETM_P2C(Etm_HeaderType) Header, ETM_P2V(uint8) DataPtr, const uint32 DataPtrLength)
{
  Std_ReturnType Result = E_NOT_OK;

  if(Header->PayloadLength <= DataPtrLength)
  {
    Etm_CommandHeader = *Header;
    Etm_CommandHeader.Payload = DataPtr;
    /* PRQA S 0310, 0314 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy */
    VStdLib_MemCpy((ETM_P2V(void))DataPtr, (ETM_P2C(void))(Header->Payload), Header->PayloadLength);
    Result = E_OK;
  }

  return Result;
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: GENERAL
 *********************************************************************************************************************/

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralGetVersion(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_STUB_PROTOCOL_VERSION <= 0x00000100uL) /* Version 1.0 */
  uint8 TmpData[4u]; /* Etm Protocol Version */
  uint16 EtmProtocolVersion = (uint16)ETM_STUB_PROTOCOL_VERSION;

  /* Etm Protocol Version - Major */
  TmpData[0u] = 0u;
  TmpData[1u] = ((uint8)(EtmProtocolVersion >> 8u));
  /* Etm Protocol Version - Minor */
  TmpData[2u] = 0u;
  TmpData[3u] = ((uint8)(EtmProtocolVersion));

  Etm_VSendResponse(Header, ETM_RID_E_OK, TmpData, 4u);
#else
  uint8 TmpData[6u]; /* Etm Protocol Version */
  uint32 EtmProtocolVersion = (uint32)ETM_STUB_PROTOCOL_VERSION;

  /* Etm Protocol Version - Major Version Number */
  TmpData[0u] = 0u;
  TmpData[1u] = ((uint8)(EtmProtocolVersion >> 16u));
  /* Etm Protocol Version - Minor Version Number */
  TmpData[2u] = 0u;
  TmpData[3u] = ((uint8)(EtmProtocolVersion >> 8u));
  /* Etm Protocol Version - Patch Version Number */
  TmpData[4u] = 0u;
  TmpData[5u] = ((uint8)(EtmProtocolVersion));

  Etm_VSendResponse(Header, ETM_RID_E_OK, TmpData, 6u);
#endif
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralStartTest(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
  Etm_DhcpOptionCode = 0u;
  Etm_DhcpOptionLength = 0u;
  Etm_DhcpLocalIpAddrId = 0u;
#endif

  Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_OK);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VGeneralEndTest(ETM_P2C(Etm_HeaderType) Header)
{
  uint8 Index;

  ((ETM_P2V(TcpIp_SockAddrType))&Etm_EventDestAddr)->domain = TCPIP_AF_UNDEFINED; /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Etm_EventDestSocketId = ETM_INV_SOCKET_ID;

  Etm_CommandRetryCount = 0u;

  Etm_DataProcessingMode = FALSE;

  for(Index = 0u;
      Index < ETM_CHANNELS_TEST;
      Index++)
  {
    if(Etm_TestChannels[Index].SocketId != ETM_INV_SOCKET_ID)
    {
      if((Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V4].SocketId) &&
         (Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V6].SocketId) &&
         (Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V4].SocketId) &&
         (Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V6].SocketId) &&
         (Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C4].SocketId) &&
         (Etm_TestChannels[Index].SocketId != Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C6].SocketId))
      {
        /* close test channel only */
        (void)TcpIp_Close(Etm_TestChannels[Index].SocketId, TRUE);
      }

      Etm_TestChannels[Index].SocketId = ETM_INV_SOCKET_ID;
      Etm_TestChannels[Index].RecvFwdActive = FALSE;
      Etm_TestChannels[Index].RecvFwdDropCount = 0u;
      Etm_TestChannels[Index].RecvFwdMaxForward = 0u;
      Etm_TestChannels[Index].RecvFwdMaxLength = 0u;
    }
  }

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
  Etm_DhcpOptionCode = 0u;
  Etm_DhcpOptionLength = 0u;
  Etm_DhcpLocalIpAddrId = 0u;
#endif

  Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_OK);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: UDP
 *********************************************************************************************************************/

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpCloseSocket(ETM_P2C(Etm_HeaderType) Header)
{
  uint16 TmpSocketId = 0u;
  const boolean Abort = TRUE;

  if(Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId) == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_UDP_SOCKET_ID(TmpSocketId))
    {
      Etm_VApiCloseSocket(Header, (TcpIp_SocketIdType)TmpSocketId, Abort);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpCreateAndBind(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiCreateAndBind(Header, TCPIP_SOCK_PROT_UDP);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpSendData(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 TotalLength = 0u;
  uint16 TmpDestAddrLength = 0u;
  TcpIp_SockAddrInXType TmpDestAddr = { 0u };

  uint8 TmpData = 0u;
  uint8 *TmpDataPtr = &TmpData;
  uint16 TmpDataLength = 0u;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &TotalLength);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 4u, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Result |= Etm_VGetVIntAddr(Header->Payload, Header->PayloadLength, 6u, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, &TmpDestAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, ((uint32)6u + (uint32)2u /* uint16 length */ + (uint32)TmpDestAddrLength), &TmpDataPtr, &TmpDataLength, FALSE);

  ((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port = ETM_HTONS(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_UDP_SOCKET_ID(TmpSocketId))
    {
      Etm_VApiSendData(Header, TCPIP_SOCK_PROT_UDP, (TcpIp_SocketIdType)TmpSocketId, TotalLength, (ETM_P2C(TcpIp_SockAddrType))&TmpDestAddr, TmpDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpReceiveAndForward(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiReceiveAndForward(Header, TCPIP_SOCK_PROT_UDP);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpConfigureSocket(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiConfigureSocket(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VUdpShutdown(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiShutdown(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: TCP
 *********************************************************************************************************************/

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpCloseSocket(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  boolean Abort = TRUE;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, 2u, (ETM_P2V(uint8))&Abort);

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_TCP_SOCKET_ID(TmpSocketId))
    {
      Etm_VApiCloseSocket(Header, (TcpIp_SocketIdType)TmpSocketId, Abort);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpCreateAndBind(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiCreateAndBind(Header, TCPIP_SOCK_PROT_TCP);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpSendData(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 TotalLength = 0u;
#if (ETM_STUB_PROTOCOL_VERSION >= 0x00010200uL) /* Version 1.2.0 */
  uint8 TcpFlags = 0u;
#endif

  uint8 TmpData = 0u;
  uint8 *TmpDataPtr = &TmpData;
  uint16 TmpDataLength = 0u;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &TotalLength);
#if (ETM_STUB_PROTOCOL_VERSION >= 0x00010200uL) /* Version 1.2.0 */
  Result |= Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, 4u, &TcpFlags);
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, 5u, &TmpDataPtr, &TmpDataLength, FALSE);
#else
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, 4u, &TmpDataPtr, &TmpDataLength, FALSE);
#endif

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_TCP_SOCKET_ID(TmpSocketId))
    {
      Etm_VApiSendData(Header, TCPIP_SOCK_PROT_TCP, (TcpIp_SocketIdType)TmpSocketId, TotalLength, NULL_PTR, TmpDataLength);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpReceiveAndForward(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiReceiveAndForward(Header, TCPIP_SOCK_PROT_TCP);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpListenAndAccept(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 MaxConnections = 0u;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &MaxConnections);

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_TCP_SOCKET_ID(TmpSocketId))
    {
#if (ETM_TCP_ENABLED == STD_ON)
      /* Check for free tcp sockets */
      /* Check number of possible connections and check number of configured connection limit */
      if((MaxConnections < ETM_TCPIP_NUM_TCP_SOCKETS) && (MaxConnections <= ETM_CHANNELS_TEST_TCP))
      {
        Result = TcpIp_TcpListen((TcpIp_SocketIdType)TmpSocketId, MaxConnections);
      }
      else
      {
        Result = E_NOT_OK;
      }
#else
      Result = E_NOT_OK;
#endif

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpConnect(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 DestAddrLength = 0u;
  TcpIp_SockAddrInXType TmpDestAddr = { 0u };

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Result |= Etm_VGetVIntAddr(Header->Payload, Header->PayloadLength, 4u, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, &DestAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  ((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port = ETM_HTONS(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_TCP_SOCKET_ID(TmpSocketId))
    {
#if (ETM_TCP_ENABLED == STD_ON)
      Result = TcpIp_TcpConnect((TcpIp_SocketIdType)TmpSocketId, (ETM_P2C(TcpIp_SockAddrType))&TmpDestAddr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
#else
      Result = E_NOT_OK;
#endif

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpConfigureSocket(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiConfigureSocket(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VTcpShutdown(ETM_P2C(Etm_HeaderType) Header)
{
  /* TCP and UDP handling is the same so move parameter handling to function call */
  Etm_VApiShutdown(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: IPv4
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv4StaticAddress(ETM_P2C(Etm_HeaderType) Header)
{
  /* IPv4 and IPv6 handling is the same so move parameter handling to function call */
  Etm_VApiStaticAddress(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv4StaticRoute(ETM_P2C(Etm_HeaderType) Header)
{
  /* IPv4 and IPv6 handling is the same so move parameter handling to function call */
  Etm_VApiStaticRoute(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: IPv6
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv6StaticAddress(ETM_P2C(Etm_HeaderType) Header)
{
  /* IPv4 and IPv6 handling is the same so move parameter handling to function call */
  Etm_VApiStaticAddress(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VIPv6StaticRoute(ETM_P2C(Etm_HeaderType) Header)
{
  /* IPv4 and IPv6 handling is the same so move parameter handling to function call */
  Etm_VApiStaticRoute(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: DHCPv4
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpClientInit(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpClientStop(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv4DhcpSetOption(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint16 DhcpOptionLength = ETM_DHCP_MAX_OPTION_LENGTH;
  uint8 TcpIpLocalAddrId = 0u;
  uint8 DhcpOptionCode = 0u;
  uint32 Offset = 0u;
  uint8 Index;

  uint8 TmpData[ETM_DHCP_MAX_OPTION_LENGTH] = { 0u };
  uint8 *TmpDataPtr = TmpData;

  Result  = Etm_VGetVIntIfNameLengthAndIgnoreData(Header->Payload, Header->PayloadLength, Offset, &InterfaceNameLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Offset  = ((uint32)2u /* uint16 length */ + (uint32)InterfaceNameLength);
  Result |= Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, Offset, &DhcpOptionCode);
  Offset += ((uint32)1u /* uint8 length */);
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, Offset, &TmpDataPtr, &DhcpOptionLength, TRUE);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) &&
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */ + 1u /* option code */ + 2u /* option length field */ + DhcpOptionLength)))
  {
    if(Etm_VGetTcpIpLocalAddrIdFromHeader(Header, &TcpIpLocalAddrId) == E_OK)
    {
      boolean interfaceFound = FALSE;
      boolean optionProhibited = FALSE;
      Result = E_NOT_OK;

      for(Index = 0u;
          Index < ETM_NUMBER_DHCP_INTERFACES;
          Index++)
      {
        if(Etm_DhcpInterfaces[Index].Index == TcpIpLocalAddrId)
        {
          interfaceFound = TRUE;
          break;
        }
      }

      for(Index = 0u;
          Index < ETM_DHCP_MAX_OPTIONS_BLACKLIST;
          Index++)
      {
        if(Etm_DhcpOptionsBlacklist[Index] == DhcpOptionCode)
        {
          optionProhibited = TRUE;
          Result = E_OK; /* return E_OK so that test case will not be abort if option is not supported */
          break;
        }
      }

      if((interfaceFound == TRUE) && (optionProhibited == FALSE))
      {
        Etm_DhcpOptionCode = DhcpOptionCode;
        Etm_DhcpOptionLength = DhcpOptionLength;
        Etm_DhcpLocalIpAddrId = TcpIpLocalAddrId;
        /* PRQA S 0310, 0314 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy */
        VStdLib_MemCpy((ETM_P2V(void))Etm_DhcpOptionBuf, (ETM_P2C(void))TmpDataPtr, DhcpOptionLength);
        Result = E_OK;
      }

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: DHCPv6
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpClientInit(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpClientStop(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VDHCPv6DhcpSetOption(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: ICMPv4
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VICMPv4EchoRequest(ETM_P2C(Etm_HeaderType) Header)
{
  /* ICMPv4 and ICMPv6 handling is the same so move parameter handling to function call */
  Etm_VApiEchoRequest(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: ICMPv6
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VICMPv6EchoRequest(ETM_P2C(Etm_HeaderType) Header)
{
  /* ICMPv4 and ICMPv6 handling is the same so move parameter handling to function call */
  Etm_VApiEchoRequest(Header);
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: NDP
 *********************************************************************************************************************/

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VNdpClearCache(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_IPV6_ENABLED == STD_ON)
  Std_ReturnType Result = TcpIp_ClearARCache((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV6);
  Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
#else
  Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_NOK);
#endif
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: ETH
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VEthInterfaceUp(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
  /* UP and DOWN handling is the same so move parameter handling to function call */
  Etm_VApiInterface(Header, COMM_FULL_COMMUNICATION);
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VEthInterfaceDown(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
  /* UP and DOWN handling is the same so move parameter handling to function call */
  Etm_VApiInterface(Header, COMM_NO_COMMUNICATION);
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- GROUP: PHY
 *********************************************************************************************************************/
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhyReadSignalQuality(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint8 TrcvIdx = 0u;

  uint8 ResultData;
  const uint16 ResultDataLength = 1u;

  Result = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) &&
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */)))
  {
    if(Etm_VGetTrcvIdxFromHeader(Header, &TrcvIdx) == E_OK)
    {
      EthIf_SignalQualityResultType SignalQualityStruct = { 0u, 0u, 0u };

      Result = EthIf_GetTrcvSignalQuality(TrcvIdx, &SignalQualityStruct);
      ResultData = (uint8)SignalQualityStruct.ActualSignalQuality;

      Etm_VSendResponse(Header, (Etm_ResultIdType)Result, &ResultData, ResultDataLength);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhyReadDiagResult(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint8 TrcvIdx = 0u;

  uint8 ResultData;
  const uint16 ResultDataLength = 1u;

  Result = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) &&
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */)))
  {
    if(Etm_VGetTrcvIdxFromHeader(Header, &TrcvIdx) == E_OK)
    {
      EthTrcv_CableDiagResultType CableDiagnosticsResult = 0u;

      Result = EthIf_GetCableDiagnosticsResult(TrcvIdx, &CableDiagnosticsResult);

      switch(CableDiagnosticsResult)
      {
      case ETHTRCV_CABLEDIAG_OK:
        ResultData = ETM_PHY_CABLE_DIAG_OK;
        break;
      case ETHTRCV_CABLEDIAG_SHORT:
        ResultData = ETM_PHY_CABLE_DIAG_SHORT;
        break;
      case ETHTRCV_CABLEDIAG_OPEN:
        ResultData = ETM_PHY_CABLE_DIAG_OPEN;
        break;
      case ETHTRCV_CABLEDIAG_ERROR: /* fall through */
      default:
        ResultData = ETM_PHY_CABLE_DIAG_ERROR;
        break;
      }

      Etm_VSendResponse(Header, (Etm_ResultIdType)Result, &ResultData, ResultDataLength);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhySetPhyTestMode(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint8 TestModeTmp = 0u;
  uint8 TrcvIdx = 0u;

  (void)Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);
  Result = Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, (uint32)Header->PayloadLength - 1u, &TestModeTmp);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) && /* PRQA S 2995 */ /* MD_Etm_2995 */
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */ + 1u /* test mode */)))
  {
    if(Etm_VGetTrcvIdxFromHeader(Header, &TrcvIdx) == E_OK)
    {
      EthTrcv_PhyTestModeType TestMode;

      switch(TestModeTmp)
      {
      case ETHTRCV_PHYTESTMODE_1:
        TestMode = ETM_PHY_TEST_MODE_1;
        break;
      case ETHTRCV_PHYTESTMODE_2:
        TestMode = ETM_PHY_TEST_MODE_2;
        break;
      case ETHTRCV_PHYTESTMODE_3:
        TestMode = ETM_PHY_TEST_MODE_3;
        break;
      case ETHTRCV_PHYTESTMODE_4:
        TestMode = ETM_PHY_TEST_MODE_4;
        break;
      case ETHTRCV_PHYTESTMODE_5:
        TestMode = ETM_PHY_TEST_MODE_5;
        break;
      case ETHTRCV_PHYTESTMODE_NONE: /* fall through */
      default:
        TestMode = ETM_PHY_TEST_MODE_NONE;
        break;
      }

      Result = EthIf_SetPhyTestMode(TrcvIdx, TestMode);

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VPhySetPhyTxMode(ETM_P2C(Etm_HeaderType) Header)
{
#if (ETM_USE_PHY_PRIMITIVES == STD_ON)
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint8 TxModeTmp = 0u;
  uint8 TrcvIdx = 0u;

  (void)Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);
  Result = Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, (uint32)Header->PayloadLength - 1u, &TxModeTmp);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) && /* PRQA S 2995 */ /* MD_Etm_2995 */
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */ + 1u /* tx mode */)))
  {
    if(Etm_VGetTrcvIdxFromHeader(Header, &TrcvIdx) == E_OK)
    {
      EthTrcv_PhyTxModeType TxMode;

      switch(TxModeTmp)
      {
      case ETHTRCV_PHYTXMODE_TX_OFF:
        TxMode = ETM_PHY_TX_MODE_TX_OFF;
        break;
      case ETHTRCV_PHYTXMODE_SCRAMBLER_OFF:
        TxMode = ETM_PHY_TX_MODE_SCRAMBLER_OFF;
        break;
      case ETHTRCV_PHYTXMODE_NORMAL: /* fall through */
      default:
        TxMode = ETM_PHY_TX_MODE_NORMAL;
        break;
      }

      Result = EthIf_SetPhyTxMode(TrcvIdx, TxMode);

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
#else
  Etm_VProcessUndefindedServicePrimitives(Header);
#endif
}

/**********************************************************************************************************************
 *  ETM HELPERS -- COMMAND HANDLING -- COMMON APIS
 *********************************************************************************************************************/

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiCloseSocket(ETM_P2C(Etm_HeaderType) Header, const TcpIp_SocketIdType SocketId, const boolean Abort)
{
  Std_ReturnType Result;

  if((SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V4].SocketId) ||
     (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V6].SocketId) ||
     (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V4].SocketId) ||
     (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V6].SocketId) ||
     (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C4].SocketId) ||
     (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C6].SocketId))
  {
    /* do not close command channel */
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
  }
  else
  {
#if (ETM_TCPIP_ERRORS_ENABLED == STD_ON)
    TcpIp_SetLastSockError(0u /* no error */);
#endif

    Result = TcpIp_Close(SocketId, Abort);

#if (ETM_TCPIP_ERRORS_ENABLED == STD_ON)
    if(TcpIp_LastSockError != 0u /* no error */)
    {
      Result = E_NOT_OK;
    }
#endif

    Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
  }
}

/* PRQA S 6050, 6080 1 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiCreateAndBind(ETM_P2C(Etm_HeaderType) Header, const TcpIp_ProtocolType Protocol)
{
  Std_ReturnType Result;

  uint16 ResultData = ETM_HTONS_UINT8(ETM_INV_SOCKET_ID);
  uint16 LocAddrLength = 0u;
  const uint16 ResultDataLength = 2u;

  boolean DoBind = TRUE;
  TcpIp_SockAddrInXType TmpLocAddr = { 0u };

  Result  = Etm_VGetNext8Bit(Header->Payload, Header->PayloadLength, 0u, (ETM_P2V(uint8))&DoBind);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 1u, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpLocAddr)->port)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Result |= Etm_VGetVIntAddr(Header->Payload, Header->PayloadLength, 3u, (ETM_P2V(TcpIp_SockAddrType))&TmpLocAddr, &LocAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  /* htons (byte order) is called during bind call */

  if(Result == E_OK)
  {
    uint8 TestChannelIndex = Etm_VFindTestChannelIndex(ETM_INV_SOCKET_ID);

    if(TestChannelIndex != ETM_INV_SOCKET_ID)
    {
      Result = TcpIp_EtmGetSocket(((ETM_P2C(TcpIp_SockAddrType))&TmpLocAddr)->domain, Protocol, &(Etm_TestChannels[TestChannelIndex].SocketId)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      ResultData = ETM_HTONS_UINT8(Etm_TestChannels[TestChannelIndex].SocketId);
    }
    else
    {
      Result = E_NOT_OK;
    }

    if((Result == E_OK) && (TestChannelIndex != ETM_INV_SOCKET_ID)) /* PRQA S 2995 */ /* MD_Etm_2995 */
    {
      if(Protocol == TCPIP_SOCK_PROT_TCP)
      {
        uint32 tmpBufSizeRx = ETM_TCPIP_BUFFER_SIZE_TCP_RX;
        uint32 tmpBufSizeTx = ETM_TCPIP_BUFFER_SIZE_TCP_TX;

        Result  = TcpIp_ChangeParameter(Etm_TestChannels[TestChannelIndex].SocketId, TCPIP_PARAMID_TCP_RXWND_MAX, (ETM_P2V(uint8))&tmpBufSizeRx);   /* PRQA S 0310, 2842 */ /* MD_Etm_11.4_0310_Api, MD_Etm_21.1_2842 */
        Result |= TcpIp_ChangeParameter(Etm_TestChannels[TestChannelIndex].SocketId, TCPIP_PARAMID_V_TCP_TXBUFSIZE, (ETM_P2V(uint8))&tmpBufSizeTx); /* PRQA S 0310, 2842 */ /* MD_Etm_11.4_0310_Api, MD_Etm_21.1_2842 */
      }

      if(Result == E_OK)
      {
        if((DoBind == TRUE) || (Protocol == TCPIP_SOCK_PROT_TCP))
        {
          TcpIp_LocalAddrIdType TmpLocAddrId = Etm_VGetLocAddrIdFromAddr((ETM_P2C(TcpIp_SockAddrType))&TmpLocAddr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

          if( ((ETM_P2C(TcpIp_SockAddrInetType))&TmpLocAddr)->port == ETM_PORT_ANY) /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
          {
            ((ETM_P2V(TcpIp_SockAddrInetType))&TmpLocAddr)->port = TCPIP_PORT_ANY; /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
          }

          Result = TcpIp_Bind(Etm_TestChannels[TestChannelIndex].SocketId, TmpLocAddrId, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpLocAddr)->port)); /* PRQA S 0310, 2842 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_21.1_2842 */
        }

        if(Result == E_OK)
        {
          Etm_VSendResponse(Header, ETM_RID_E_OK, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
        }
        else
        {
          Etm_VSendResponse(Header, ETM_RID_E_UBS, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
        }
      }
      else
      {
        Etm_VSendResponse(Header, ETM_RID_E_ISB, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
      }
    }
    else
    {
      Etm_VSendResponse(Header, ETM_RID_E_UCS, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
    }
  }
  else
  {
    Etm_VSendResponse(Header, ETM_RID_E_INV, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
  }
}

/* PRQA S 6060, 6080 1 */ /* MD_MSR_STPAR, MD_MSR_STMIF */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiSendData(
  ETM_P2C(Etm_HeaderType) Header,
  const TcpIp_ProtocolType Protocol,
  const TcpIp_SocketIdType SocketId,
  const uint16 TotalLength,
  ETM_P2C(TcpIp_SockAddrType) DestinationAddressPtr,
  const uint16 DataLength)
{
  Std_ReturnType Result = E_NOT_OK;

  uint16 TmpLengthToTransmit = ETM_MAX(TotalLength, DataLength);
  uint16 TmpLengthToTransmitNow;

#if (ETM_TCP_ENABLED == STD_OFF)
  ETM_DUMMY_STATEMENT_CONST(Protocol); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  if(Etm_CommandRetryCount > 0u)
  {
    do
    {
      Result = Etm_VApiSendDataPending();
    }
    while((Etm_CommandRetryCount > 0u) && (Result == E_OK)); /* reset of Etm_CommandRetryCount is done in Etm_CopyTxData() */
  }
  else if((Etm_VTestChannelActive(SocketId) == TRUE) && ETM_COND_VALID_SOCKET_ID(SocketId))
  {
    if(E_OK == Etm_VSaveCommand(Header, Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE))
    {
#if (ETM_TCP_ENABLED == STD_ON)
      if(Protocol == TCPIP_SOCK_PROT_TCP)
      {
        TmpLengthToTransmitNow = ETM_MIN(TmpLengthToTransmit, ETM_TCPIP_BUFFER_SIZE_TCP_TX);
      }
      else
#endif
      {
        TmpLengthToTransmitNow = ETM_MIN(TmpLengthToTransmit, ETM_TCPIP_MIN_MMS);
      }

      if(TmpLengthToTransmit == TmpLengthToTransmitNow)
      { /* Send data directly at once */

#if (ETM_TCP_ENABLED == STD_ON)
        if(Protocol == TCPIP_SOCK_PROT_TCP)
        {
          Result = TcpIp_TcpTransmit(SocketId, NULL_PTR, TmpLengthToTransmitNow, TRUE);
        }
        else
#endif
        {
          if(TCPIP_OK == TcpIp_UdpTransmit(SocketId, NULL_PTR, (ETM_P2V(TcpIp_SockAddrType))DestinationAddressPtr, TmpLengthToTransmitNow)) /* PRQA S 0311 */ /* MD_Etm_11.4_0311_Const */
          {
            Result = E_OK;
          }
          else
          {
            Result = E_NOT_OK;
          }
        }
      }
      else
      { /* Send data in the next main functions */
        Etm_CommandRetryCount = 1;
        Etm_SendDataCommandAlreadySend = 0u;
        Result = E_OK;
      }
    }

    Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
  }
}

/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
ETM_LOCAL FUNC(Std_ReturnType, ETM_CODE) Etm_VApiSendDataPending(void)
{
  uint16 TmpSocketId = 0u;
  Std_ReturnType Result = Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 0u, &TmpSocketId);

  if(Result == E_OK) /* PRQA S 2991, 2995 */ /* MD_Etm_2991, MD_Etm_2995 */
  {
    if(Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE)
    {
      uint16 TotalLength = 0u;
      uint16 TmpDestAddrLength = 0u;
      TcpIp_SockAddrInXType TmpDestAddr = { 0u };

      uint8 TmpData = 0u;
      uint8 *TmpDataPtr = &TmpData;
      uint16 TmpDataLength = 0u;

      if(ETM_COND_VALID_UDP_SOCKET_ID(TmpSocketId))
      { /* Send UDP data */
        (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 2u, &TotalLength);
        (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 4u, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
        Result  = Etm_VGetVIntAddr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 6u, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, &TmpDestAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
        Result |= Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, ((uint32)6u + (uint32)2u /* uint16 length */ + (uint32)TmpDestAddrLength), &TmpDataPtr, &TmpDataLength, FALSE);

        ((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port = ETM_HTONS(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

        if(Result == E_OK)
        {
          uint16 TmpLength;
          /* max length (overall) who should be send */
          TmpLength = ETM_MAX(TotalLength, TmpDataLength);
          /* max length (overall)  who must/could be send now */
          TmpLength = ETM_MIN((uint16)(TmpLength - Etm_SendDataCommandAlreadySend), ETM_TCPIP_MIN_MMS);

          if(TCPIP_OK == TcpIp_UdpTransmit((TcpIp_SocketIdType)TmpSocketId, NULL_PTR, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, TmpLength)) /* PRQA S 0310, 0311 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_11.4_0311_Const */
          {
            Result = E_OK;
          }
          else
          {
            Result = E_NOT_OK;
          }
        }
      }
      else
      { /* Send TCP data */
        (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 2u, &TotalLength);
#if (ETM_STUB_PROTOCOL_VERSION >= 0x00010200uL) /* Version 1.2.0 */
        Result = Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 5u, &TmpDataPtr, &TmpDataLength, FALSE);
#else
        Result = Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 4u, &TmpDataPtr, &TmpDataLength, FALSE);
#endif

        if(Result == E_OK)
        {
#if (ETM_TCP_ENABLED == STD_ON)
          uint16 TmpLength;
          /* max length (overall) who should be send */
          TmpLength = ETM_MAX(TotalLength, TmpDataLength);
          /* max length (overall)  who must/could be send now */
          TmpLength = ETM_MIN((uint16)(TmpLength - Etm_SendDataCommandAlreadySend), ETM_TCPIP_BUFFER_SIZE_TCP_TX);

          if(E_OK == TcpIp_TcpTransmit((TcpIp_SocketIdType)TmpSocketId, NULL_PTR, TmpLength, TRUE))
          {
            Result = E_OK;
          }
          else
          {
            Result = E_NOT_OK;
          }
#else
          /* Transmission failed */
          /* No TCP configured */
          Etm_CommandRetryCount = 0u;
          Etm_SendDataCommandAlreadySend = 0u;
          Result = E_NOT_OK;
#endif
        }
      }
    }
    else
    {
      /* Transmission failed */
      /* TestChannel (Socket) closed - abort transmission */
      Etm_CommandRetryCount = 0u;
      Etm_SendDataCommandAlreadySend = 0u;
      Result = E_NOT_OK;
    }
  }

  return Result;
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiReceiveAndForward(ETM_P2C(Etm_HeaderType) Header, const TcpIp_ProtocolType Protocol)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 MaxForward = 0u;
  uint16 MaxLength = 0u;

  uint16 ResultData = 0u;
  const uint16 ResultDataLength = 2u;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &MaxForward);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 4u, &MaxLength);

  if((Result == E_OK) &&
    ((Protocol == TCPIP_SOCK_PROT_UDP) || (Protocol == TCPIP_SOCK_PROT_TCP)))
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) &&
      (((Protocol == TCPIP_SOCK_PROT_UDP) && (ETM_COND_VALID_UDP_SOCKET_ID(TmpSocketId))) ||
       ((Protocol == TCPIP_SOCK_PROT_TCP) && (ETM_COND_VALID_TCP_SOCKET_ID(TmpSocketId)))))
    {
      uint8 TestChannelIndex = Etm_VFindTestChannelIndex((TcpIp_SocketIdType)TmpSocketId);

      if(TestChannelIndex != ETM_INV_SOCKET_ID)
      {
        ResultData = ETM_HTONS((uint16)Etm_TestChannels[TestChannelIndex].RecvFwdDropCount);

#if (ETM_TCP_ENABLED == STD_ON)
        if(Protocol == TCPIP_SOCK_PROT_TCP)
        {
          Result = TcpIp_TcpReceived((TcpIp_SocketIdType)TmpSocketId, ResultData);
        }
        else
#endif
        {
          Result = E_OK;
        }

        /*
         * Etm_TestChannels[TestChannelIndex].RecvFwdMaxForward
         * Due to the reason that it is not possible to forward a received full sized tcp or udp package back to the tester the forwardeed/mirrowed payload is cut off.
         * In addition to a full sized 1500 byte received tcp or udp package an extra etm event header is added and so it is not possible to forward all of the received
         * data. Etm cut off the data to fit in an 'general sized' package that mean: etm substract all the maximum header sizes (eth,ipv4,ipv6,tcp,udp,etm) from the
         * full mtu size - this is a 'general size' used for the payload size. Etm cut off the forwarded payload to a minimal/maximum size fitting for all configurations
         * so it does not matter if the package is forwarded with ipv4 over udp or with ipv6 over tcp. See the 'fullLen' field in the generated Event massege to see if
         * the whole data is received.
         */
        Etm_TestChannels[TestChannelIndex].RecvFwdActive = TRUE;
        Etm_TestChannels[TestChannelIndex].RecvFwdMaxForward = ETM_MIN(MaxForward, ETM_STUB_MAX_FORWARD_LENGTH_CALCULATED);
        Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength = MaxLength;
        Etm_TestChannels[TestChannelIndex].RecvFwdDropCount = 0u;
      }
      else
      {
        Result = E_NOT_OK;
      }

      Etm_VSendResponse(Header, (Etm_ResultIdType)Result, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
    }
    else
    {
      Etm_VSendResponse(Header, ETM_RID_E_ISD, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
    }
  }
  else
  {
    Etm_VSendResponse(Header, ETM_RID_E_INV, (ETM_P2C(uint8))&ResultData, ResultDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_BufPtr */
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiConfigureSocket(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpSocketId = 0u;
  uint16 ParamId = 0u;
  TcpIp_ParamIdType ParamIdTcpIp = 0u; /* PRQA S 2981 */ /* MD_Etm_2981 */

  uint8 TmpData = 0u;
  uint8 *TmpDataPtr = &TmpData;
  uint16 TmpDataLength = 0u;

  Result  = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &TmpSocketId);
  Result |= Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 2u, &ParamId);
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, 4u, &TmpDataPtr, &TmpDataLength, FALSE);

  if(Result == E_OK)
  {
    /* ParamId mapping */
    switch(ParamId)
    {
    case ETM_CONFIGURE_SOCKET_TTL_HOP_LIMIT:
      ParamIdTcpIp = TCPIP_PARAMID_TTL;
      break;
    case ETM_CONFIGURE_SOCKET_NAGLE_ALGORITHM:
      ParamIdTcpIp = TCPIP_PARAMID_TCP_NAGLE;
      break;
    case ETM_CONFIGURE_SOCKET_PRIORITY:
      ParamIdTcpIp = TCPIP_PARAMID_V_IPV6_TRAFFIC_CLASS;
      break;
    case ETM_CONFIGURE_SOCKET_TYPE_OF_SERVICE:
      ParamIdTcpIp = TCPIP_PARAMID_V_IPV4_TYPE_OF_SERVICE;
      break;
    case ETM_CONFIGURE_SOCKET_DONT_FRAGMENT:    /* fall through */ /* The MICROSAR TcpIp is not able to set/modify this values. */
    case ETM_CONFIGURE_SOCKET_TIMESTAMT_OPTION: /* fall through */ /* The MICROSAR TcpIp is not able to set/modify this values. */
    case ETM_CONFIGURE_SOCKET_MSS:              /* fall through */ /* The MICROSAR TcpIp is not able to set/modify this values. Workaround: declare MSS during TCP handshake. */
    case ETM_CONFIGURE_SOCKET_UDP_CHECKSUM:     /* fall through */ /* The MICROSAR TcpIp is not able to set/modify this values. */
    default:
      Result = E_NOT_OK;
      break;
    }
  }

  if(Result == E_OK)
  {
    if((Etm_VTestChannelActive((TcpIp_SocketIdType)TmpSocketId) == TRUE) && ETM_COND_VALID_SOCKET_ID(TmpSocketId))
    {
      Result = TcpIp_ChangeParameter((TcpIp_SocketIdType)TmpSocketId, ParamIdTcpIp, TmpDataPtr);

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_ISD);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiShutdown(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiStaticAddress(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiStaticRoute(ETM_P2C(Etm_HeaderType) Header)
{
  Etm_VProcessUndefindedServicePrimitives(Header);
}

/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiEchoRequest(ETM_P2C(Etm_HeaderType) Header)
{
  Std_ReturnType Result;

  uint16 TmpDestAddrLength = 0u;
  TcpIp_SockAddrInXType TmpDestAddr = { 0u };
  uint32 Offset = 0u;

  uint8 TmpData = 0u;
  uint8 *TmpDataPtr = &TmpData;
  uint16 TmpDataLength = 0u;

  Result  = Etm_VGetVIntIfNameLengthAndIgnoreData(Header->Payload, Header->PayloadLength, Offset, &TmpDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Offset  = ((uint32)2u /* uint16 length */ + (uint32)TmpDataLength);
  Result |= Etm_VGetVIntAddr(Header->Payload, Header->PayloadLength, Offset, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, &TmpDestAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
  Offset += ((uint32)2u /* uint16 length */ + (uint32)TmpDestAddrLength);
  Result |= Etm_VGetVIntDataPtr(Header->Payload, Header->PayloadLength, Offset, &TmpDataPtr, &TmpDataLength, FALSE);

  if(Result == E_OK)
  {
    if(ETM_COND_VALID_DOMAIN(&TmpDestAddr)) /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
    {
      TcpIp_LocalAddrIdType TmpLocAddrId = Etm_VGetLocAddrIdFromAddr((ETM_P2C(TcpIp_SockAddrType))&TmpDestAddr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

      if(((ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr)->domain == TCPIP_AF_INET) /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      {
#if (ETM_IPV4_ENABLED == STD_ON)
        Result = IpV4_Icmp_SendEcho(TmpLocAddrId, ((ETM_P2V(IpBase_SockAddrInType))&TmpDestAddr)->sin_addr, (ETM_P2C(uint8))TmpDataPtr, TmpDataLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
#else
        Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_NOK);
        Etm_CommandRetryCount = 1u;
        Result = E_NOT_OK;
#endif
      }
      else
      {
#if (ETM_IPV6_ENABLED == STD_ON)
        Result = TcpIp_IcmpV6Transmit(TmpLocAddrId, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, IpV6_GetCurrentHopLimit(ETM_TCPIP_IPV6_CTRLIDX), 128u /* IPV6_ICMP_MSG_TYPE_ECHO_REQ */, 0u, TmpDataLength, TmpDataPtr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
#else
        Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_NOK);
        Etm_CommandRetryCount = 1u;
        Result = E_NOT_OK;
#endif
      }

      if(Etm_CommandRetryCount == 0u)
      {
        if(Result != E_OK)
        {
          Etm_CommandRetryCount = 3u; /* retry 3 times due to address resolution */
          Result = Etm_VSaveCommand(Header, Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE); /* async processing is triggered */
        }

        Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
      }
      else
      {
        Etm_CommandRetryCount--;

        if(Result == E_OK)
        {
          Etm_CommandRetryCount = 0u;
        }
      }
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}

#if (ETM_USE_ETH_PRIMITIVES == STD_ON)
ETM_LOCAL FUNC(void, ETM_CODE) Etm_VApiInterface(ETM_P2C(Etm_HeaderType) Header, const uint8 Mode)
{
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;
  uint8 ComMIdentifier = 0u;

  Result = Etm_VGetNext16Bit(Header->Payload, Header->PayloadLength, 0u, &InterfaceNameLength);

  if((Result == E_OK) && (InterfaceNameLength > ETM_INTERFACE_MIN_LENGTH) &&
     (Header->PayloadLength == (InterfaceNameLength + 2u /* text length field */)))
  {
    if(Etm_VGetComMIdentifierFromHeader(Header, &ComMIdentifier) == E_OK)
    {
      Result = ComM_RequestComMode(ComMIdentifier, Mode);

      Etm_VSendResponseWithoutPayload(Header, (Etm_ResultIdType)Result);
    }
    else
    {
      Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_IIF);
    }
  }
  else
  {
    Etm_VSendResponseWithoutPayload(Header, ETM_RID_E_INV);
  }
}
#endif

/**********************************************************************************************************************
 *  ETM HELPERS -- NVM
 *********************************************************************************************************************/

#if (ETM_NVM_ENABELD == STD_ON)
ETM_LOCAL FUNC(void, ETM_CODE) Etm_NvmSaveProcessingState(void)
{
  uint8 NvMStatus = NVM_REQ_PENDING;
  (void)NvM_GetErrorStatus((NvM_BlockIdType)ETM_NVM_BLOCK_ID, &NvMStatus);

  if(NVM_REQ_PENDING != NvMStatus)
  {
    if(E_OK == NvM_SetRamBlockStatus((NvM_BlockIdType)ETM_NVM_BLOCK_ID, TRUE))
    {
      Etm_ProcessingStateChanged = FALSE;
    }
  }
}
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#define ETM_STOP_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#define ETM_START_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Etm_InitMemory()
 *********************************************************************************************************************/
/*! \brief        Function for *_INIT_*-variable initialization
 *  \details      Service to initialize module global variables at power up. This function initializes the
 *                variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \param        void none
 *  \return       none
 *  \pre          Module is uninitialized.
 *  \context      TASK
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_InitMemory(void)
{
  Etm_ModuleInitialized = FALSE;
} /* Etm_InitMemory() */

/**********************************************************************************************************************
 *  Etm_Init()
 *********************************************************************************************************************/
/*! \brief        Initialization function
 *  \details      This function initializes the module Etm. It initializes all variables and sets the module state to
 *                initialized.
 *  \param[in]    ConfigPtr Configuration structure for initializing the module.
 *  \return       none
 *  \pre          Interrupts are disabled.
 *  \pre          Module is uninitialized.
 *  \pre          Etm_InitMemory has been called unless Etm_ModuleInitialized is initialized by start-up code.
 *  \context      TASK
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *  \note         Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_Init(ETM_P2C(Etm_ConfigType) ConfigPtr)
{
  uint8 Index;

  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnVoid(Etm_ModuleInitialized == FALSE, ETM_SID_INIT, ETM_E_ALREADY_INITIALIZED);
  /* ------------------------------------------------- */

  ETM_DUMMY_STATEMENT_CONST(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  ((ETM_P2V(TcpIp_SockAddrType))&Etm_EventDestAddr)->domain = TCPIP_AF_UNDEFINED; /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

  Etm_SendBufferLength = 0u;
  Etm_EventDestSocketId = ETM_INV_SOCKET_ID;
  Etm_CommandRetryCount = 0u;
  Etm_SendDataCommandAlreadySend = 0u;

  Etm_ModuleInitAll = FALSE;
  Etm_IpV4LinkAssigned = FALSE;
  Etm_IpV6LinkAssigned = FALSE;
  Etm_DataProcessingMode = FALSE;

#if (ETM_NVM_ENABELD == STD_ON)
  Etm_ProcessingStateChanged = FALSE;
  Etm_ProcessingStatePtr = &Etm_NvmBlock_Ram;
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
  Etm_DhcpOptionCode = 0u;
  Etm_DhcpOptionLength = 0u;
  Etm_DhcpLocalIpAddrId = 0u;
#endif /* (ETM_USE_DHCP_PRIMITIVES == STD_ON) */

  /* Init command channel data */
  for(Index = 0u;
      Index < ETM_CHANNELS_COMMAND;
      Index++)
  {
    Etm_CommandChannels[Index].SocketId     = Etm_CommandChannelsConst[Index].SocketId;
    Etm_CommandChannels[Index].ChannelState = Etm_CommandChannelsConst[Index].ChannelState;
  }

  /* Init test channel data */
  for(Index = 0u;
      Index < ETM_CHANNELS_TEST;
      Index++)
  {
    Etm_TestChannels[Index].SocketId          = ETM_INV_SOCKET_ID;
    Etm_TestChannels[Index].RecvFwdActive     = FALSE;
    Etm_TestChannels[Index].RecvFwdDropCount  = 0u;
    Etm_TestChannels[Index].RecvFwdMaxForward = 0u;
    Etm_TestChannels[Index].RecvFwdMaxLength  = 0u;
  }

#if (ETM_ENABLE_APPL_INIT_FUNCTION == STD_ON)
  ApplEtm_InitFunction();
#endif

  Etm_ModuleInitialized = TRUE;
} /* Etm_Init() */

#if (ETM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Etm_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief        Returns the version information
 *  \details      Etm_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]   VersionInfoPtr Pointer to where to store the version information. Parameter must not be NULL.
 *  \return       none
 *  \pre          none
 *  \context      TASK
 *  \reentrant    Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_GetVersionInfo(ETM_P2V(Std_VersionInfoType) VersionInfoPtr)
{
  /* ----- Development Error Checks ------------------ */
  Etm_CheckDetErrorReturnVoid(NULL_PTR != VersionInfoPtr, ETM_SID_GET_VERSION_INFO, ETM_E_NULL_POINTER);
  /* ------------------------------------------------- */

  VersionInfoPtr->vendorID = (ETM_VENDOR_ID);
  VersionInfoPtr->moduleID = (ETM_MODULE_ID);
  VersionInfoPtr->sw_major_version = (ETM_SW_MAJOR_VERSION);
  VersionInfoPtr->sw_minor_version = (ETM_SW_MINOR_VERSION);
  VersionInfoPtr->sw_patch_version = (ETM_SW_PATCH_VERSION);
} /* Etm_GetVersionInfo() */
#endif /* (ETM_VERSION_INFO_API == STD_ON) */

#if (ETM_NVM_ENABELD == STD_ON)
/**********************************************************************************************************************
 *  Etm_ActivateProcessing()
 *********************************************************************************************************************/
/*! \brief        Activates the Service Primitive and command processing
 *  \details      Etm_ActivateProcessing() starts the message procesing.
 *                This service can, for example, be triggered by a diagnostic message.
 *  \param        void none
 *  \return       none
 *  \pre          none
 *  \context      TASK
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_ActivateProcessing(void)
{
  if(Etm_ModuleInitialized != TRUE)
  {
    Etm_ReportDetError(ETM_SID_ACTIVATE_PROCESSING, ETM_E_NOT_INITIALIZED);
    return;
  }

  *Etm_ProcessingStatePtr = ETM_PROCESSING_ACTIVE;
  Etm_ProcessingStateChanged = TRUE;
  Etm_NvmSaveProcessingState();
}
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#if (ETM_NVM_ENABELD == STD_ON)
/**********************************************************************************************************************
 *  Etm_DeactivateProcessing()
 *********************************************************************************************************************/
/*! \brief        Deactivates the Service Primitive and command processing
 *  \details      Etm_DeactivateProcessing() stops the message procesing.
 *                This service can, for example, be triggered by a diagnostic message.
 *  \param        void none
 *  \return       none
 *  \pre          none
 *  \context      TASK
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_DeactivateProcessing(void)
{
  if(Etm_ModuleInitialized != TRUE)
  {
    Etm_ReportDetError(ETM_SID_DEACTIVATE_PROCESSING, ETM_E_NOT_INITIALIZED);
    return;
  }

  *Etm_ProcessingStatePtr = ETM_PROCESSING_INACTIVE;
  Etm_ProcessingStateChanged = TRUE;
  Etm_NvmSaveProcessingState();
}
#endif /* (ETM_NVM_ENABELD == STD_ON) */

/**********************************************************************************************************************
 *  Etm_MainFunction()
 *********************************************************************************************************************/
/*! \brief        Schedules the Etm module. (Entry point for scheduling)
 *  \param        void none
 *  \return       none
 *  \pre          Module is uninitialized.
 *  \context      TASK
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
/* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
FUNC(void, ETM_CODE) Etm_MainFunction(void)
{
  if(Etm_ModuleInitialized != TRUE)
  {
    Etm_ReportDetError(ETM_SID_MAIN_FUNCTION, ETM_E_NOT_INITIALIZED);
    return;
  }

#if (ETM_NVM_ENABELD == STD_ON)
  if(TRUE == Etm_ProcessingStateChanged)
  {
    Etm_NvmSaveProcessingState();
  }

  if(ETM_PROCESSING_ACTIVE != *Etm_ProcessingStatePtr)
  {
    return;
  }
#endif /* (ETM_NVM_ENABELD == STD_ON) */

#if (ETM_ENABLE_APPL_MAIN_FUNCTION == STD_ON)
  if(ApplEtm_MainFunction() == ETM_RID_E_PEN)
  {
    return;
  }
#endif

  if(Etm_CommandRetryCount > 0u)
  {
    Etm_VProcessEtmCommands(&Etm_CommandHeader);
  }

  if(Etm_ModuleInitAll == FALSE)
  {
    /* Init ETMv4 */
    if(Etm_IpV4LinkAssigned == TRUE)
    {
      Etm_VOpenCommandChannel(ETM_CMD_CHAN_IDX_UDP_V4);
      Etm_VOpenCommandChannel(ETM_CMD_CHAN_IDX_TCP_V4);
    }

    /* Init ETMv6 */
    if(Etm_IpV6LinkAssigned == TRUE)
    {
      Etm_VOpenCommandChannel(ETM_CMD_CHAN_IDX_UDP_V6);
      Etm_VOpenCommandChannel(ETM_CMD_CHAN_IDX_TCP_V6);
    }

    if(((Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V4].ChannelState == ETM_CMD_CHAN_INACTIVE) /* NOT USED */ ||
        (Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V4].ChannelState == ETM_CMD_CHAN_ACTIVE)   /* READY */ ) &&
       ((Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V6].ChannelState == ETM_CMD_CHAN_INACTIVE) /* NOT USED */ ||
        (Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V6].ChannelState == ETM_CMD_CHAN_ACTIVE)   /* READY */ ) &&
       ((Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V4].ChannelState == ETM_CMD_CHAN_INACTIVE) /* NOT USED */ ||
        (Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V4].ChannelState == ETM_CMD_CHAN_ACTIVE)   /* READY */ ) &&
       ((Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V6].ChannelState == ETM_CMD_CHAN_INACTIVE) /* NOT USED */ ||
        (Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V6].ChannelState == ETM_CMD_CHAN_ACTIVE)   /* READY */))
    {
      /* All channels active or not used (inactive) */
      Etm_ModuleInitAll = TRUE;
    }

    return;
  }
} /* Etm_MainFunction() */

/**********************************************************************************************************************
 *  Etm_RxIndication()
 *********************************************************************************************************************/
/*! \brief        The TCP/IP stack calls this function after the reception of data on a socket.
 *  \param[in]    SocketId        Socket identifier of the related local socket resource.
 *  \param[in]    RemoteAddrPtr   Pointer to memory containing IP address and port of the remote host which sent the data.
 *  \param[in]    BufPtr          Pointer to the received data.
 *  \param[in]    BufLength       Data length of the received TCP segment or UDP datagram.
 *  \return       none
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Reentrant for different SocketIds. Non reentrant for the same SocketId.
 *  \synchronous  Synchronous.
 *  \warning      The frame buffer has to be released later.
 *********************************************************************************************************************/
/* PRQA S 6010, 6030, 6050, 6080 1 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
FUNC(void, ETM_CODE) Etm_RxIndication(
  TcpIp_SocketIdType SocketId,
  ETM_P2V(TcpIp_SockAddrType) RemoteAddrPtr, /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
  ETM_P2V(uint8) BufPtr,                     /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
  uint16 BufLength)
{
#if (ETM_NVM_ENABELD == STD_ON)
  if(ETM_PROCESSING_ACTIVE != *Etm_ProcessingStatePtr)
  {
    return;
  }
  else
#endif /* (ETM_NVM_ENABELD == STD_ON) */
  {
    /* ----- Development Error Checks ------------------ */
    Etm_CheckDetErrorReturnVoid(ETM_COND_VALID_PTR(BufPtr), ETM_SID_RX_INDICATION, ETM_E_INV_POINTER);
    Etm_CheckDetErrorReturnVoid(ETM_COND_VALID_PTR(RemoteAddrPtr), ETM_SID_RX_INDICATION, ETM_E_INV_POINTER);
    Etm_CheckDetErrorReturnVoid(ETM_COND_VALID_DOMAIN(RemoteAddrPtr), ETM_SID_RX_INDICATION, ETM_E_INV_SOCK_ADDR_FAMILY);
    /* ------------------------------------------------- */

    if((SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V4].SocketId) ||
       (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_UDP_V6].SocketId) ||
       (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C4].SocketId) ||
       (SocketId == Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C6].SocketId))
    {
      uint16 ReceivedSid = 0u;
      Etm_HeaderType ReceivedHeader = { 0u };
      (void)Etm_VGetNext16Bit(BufPtr, BufLength, ETM_MESSAGE_OFFSET_SID, &ReceivedSid);

      if(ReceivedSid == ETM_STUB_SERVICE_ID)
      {
        ReceivedHeader.UsePhysAddr = FALSE;
        ReceivedHeader.ReceivedSocketId = SocketId;
        (void)IpBase_CopySockAddr((ETM_P2V(IpBase_SockAddrType))&(ReceivedHeader.ReceivedRemoteAddress), (ETM_P2C(IpBase_SockAddrType))RemoteAddrPtr); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

        if(E_OK == Etm_VParseHeader(BufPtr, BufLength, &ReceivedHeader))
        {
          if(Etm_CommandRetryCount > 0u)
          {
            if((ReceivedHeader.Gid == ETM_GID_GENERAL) && (ReceivedHeader.Pid == ETM_PID_END_TEST))
            {
              Etm_VGeneralEndTest(&ReceivedHeader);
            }
            else
            {
              Etm_VSendResponseWithoutPayload(&ReceivedHeader, ETM_RID_E_PEN);
            }
          }
          else
          {
            Etm_DataProcessingMode = TRUE;
            Etm_EventDestSocketId = SocketId;
            (void)IpBase_CopySockAddr((ETM_P2V(IpBase_SockAddrType))&Etm_EventDestAddr, (ETM_P2C(IpBase_SockAddrType))&(ReceivedHeader.ReceivedRemoteAddress)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */

            Etm_VProcessEtmCommands(&ReceivedHeader);
          }
        }
        else
        {
          Etm_VSendResponseWithoutPayload(&ReceivedHeader, ETM_RID_E_NOK);
        }

        return;
      }
    }

    /* ETM Handling */
    if(Etm_DataProcessingMode == TRUE)
    {
      const uint8 TestChannelIndex = Etm_VFindTestChannelIndex(SocketId);

      if((TestChannelIndex != ETM_INV_SOCKET_ID) && ETM_COND_VALID_SOCKET_ID(SocketId))
      {
        /* channel found and valid */

        if(Etm_TestChannels[TestChannelIndex].RecvFwdActive == TRUE)
        {
          /* data sould be forwarded */

          Etm_HeaderType EventHeader;
          uint16 ForwardLength = ETM_MIN(BufLength, Etm_TestChannels[TestChannelIndex].RecvFwdMaxForward);

          if(Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength != ETM_FORWARD_FOREVER)
          {
            if(BufLength >= Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength)
            {
              ForwardLength = ETM_MIN(Etm_TestChannels[TestChannelIndex].RecvFwdMaxForward, Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength);

              Etm_TestChannels[TestChannelIndex].RecvFwdActive = FALSE;
              Etm_TestChannels[TestChannelIndex].RecvFwdDropCount = (uint32)((uint32)BufLength - (uint32)(Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength));
              Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength = 0u;
            }
            else
            {
              Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength -= BufLength;
            }
          }

#if (ETM_TCP_ENABLED == STD_ON)
          if(ETM_COND_VALID_TCP_SOCKET_ID(Etm_TestChannels[TestChannelIndex].SocketId))
          {
            /* consume 'all' received data. subtract dropcount (sould be zero) in case maxlength is reached */
            (void)TcpIp_TcpReceived(SocketId, (uint32)(BufLength - Etm_TestChannels[TestChannelIndex].RecvFwdDropCount));

            /* Build Event Header */
            EventHeader.Gid = ETM_GID_TCP;
            EventHeader.Pid = ETM_PID_TCP_RECEIVE_AND_FORWARD;
            EventHeader.UsePhysAddr = FALSE;
          }
          else
#endif
          {
            /* Build Event Header */
            EventHeader.Gid = ETM_GID_UDP;
            EventHeader.Pid = ETM_PID_UDP_RECEIVE_AND_FORWARD;
            EventHeader.UsePhysAddr = FALSE;
          }

          /* Set Event Payload */
          {
            uint16 Index = ETM_HEADER_LENGTH;
            const uint16 AddressLength = ((RemoteAddrPtr->domain == TCPIP_AF_INET6) ? ETM_DATA_LEN_ADDRESS_IPV6 : ETM_DATA_LEN_ADDRESS_IPV4);

            (void)Etm_VSetNext16Bit(BufLength, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX);
            Index += 2u;

#if (ETM_TCP_ENABLED == STD_ON)
            if(ETM_COND_VALID_UDP_SOCKET_ID(SocketId))
#endif
            {
              (void)Etm_VSetNext16Bit(ETM_HTONS(((ETM_P2C(TcpIp_SockAddrInetType))RemoteAddrPtr)->port), Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX); /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
              Index += 2u;
              (void)Etm_VSetNext16Bit(AddressLength, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX);
              Index += 2u;
              /* PRQA S 0310, 0314, 3305 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy, MD_Etm_3305 */
              VStdLib_MemCpy((ETM_P2V(void))&Etm_SendBuffer[Index], (ETM_P2C(void))&(((ETM_P2C(TcpIp_SockAddrInet6Type))RemoteAddrPtr)->addr), AddressLength); /*lint !e545 */
              Index += AddressLength;
            }

            (void)Etm_VSetNext16Bit(ForwardLength, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX);
            Index += 2u;
            /* PRQA S 0310, 0314 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy */
            VStdLib_MemCpy((ETM_P2V(void))&Etm_SendBuffer[Index], (ETM_P2C(void))BufPtr, ForwardLength);
            Index += ForwardLength;
            Etm_SendBufferLength = Index;

            /* Send Event */
            Etm_VSendEvent(&EventHeader);
          }
        }
        else
        {
          /* data sould not be forwarded */

          Etm_TestChannels[TestChannelIndex].RecvFwdDropCount += BufLength;
        }
      }

      return;
    }
  }
} /* Etm_RxIndication() */

/**********************************************************************************************************************
 *  Etm_EthIf_RxIndication()
 *********************************************************************************************************************/
/*! \brief        Indicates the reception of an Ethernet frame.
 *  \param[in]    CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface.
 *  \param[in]    FrameType     Frame type of received Ethernet frame.
 *  \param[in]    IsBroadcast   Parameter to indicate a broadcast frame.
 *  \param[in]    PhysAddrPtr   Pointer to Physical source address (MAC address in network byte order) of received Ethernet frame.
 *  \param[in]    DataPtr       Pointer to payload of the received Ethernet frame (i.e. Ethernet header is not provided).
 *  \param[in]    LenByte       Length of received data.
 *  \return       none
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Don't care.
 *  \synchronous  --
 *********************************************************************************************************************/
/* PRQA S 6030, 6060, 6080 1 */ /* MD_MSR_STCYC, MD_MSR_STPAR, MD_MSR_STMIF */
FUNC(void, ETM_CODE) Etm_EthIf_RxIndication(
  uint8 CtrlIdx,
  Eth_FrameType FrameType,
  boolean IsBroadcast,
  ETM_P2V(uint8) PhysAddrPtr, /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
  ETM_P2V(uint8) DataPtr,     /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
  uint16 LenByte)
{
#if (ETM_NVM_ENABELD == STD_ON)
  if(ETM_PROCESSING_ACTIVE != *Etm_ProcessingStatePtr)
  {
    return;
  }
  else
#endif /* (ETM_NVM_ENABELD == STD_ON) */
  {
#if (ETM_ETHIF_ENABLED == STD_ON)
    /* ----- Development Error Checks ------------------ */
    Etm_CheckDetErrorReturnVoid(ETM_COND_VALID_PTR(PhysAddrPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER);
    Etm_CheckDetErrorReturnVoid(ETM_COND_VALID_PTR(DataPtr), ETM_SID_INTERNAL_FUNCTION, ETM_E_INV_POINTER);
    /* ------------------------------------------------- */

    if(FrameType == ETM_ETHIF_FRAME_TYPE)
    {
      uint16 ReceivedSid = 0u;
      Etm_HeaderType ReceivedHeader = { 0u };
      (void)Etm_VGetNext16Bit(DataPtr, LenByte, ETM_MESSAGE_OFFSET_SID, &ReceivedSid);

      if(ReceivedSid == ETM_STUB_SERVICE_ID)
      {
        ReceivedHeader.UsePhysAddr = TRUE;
        ReceivedHeader.ReceivedSocketId = 0u;
        ReceivedHeader.ReceivedCtrlIdx = CtrlIdx;
        /* PRQA S 0310, 0314 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy */
        VStdLib_MemCpy((ETM_P2V(void))&(ReceivedHeader.ReceivedRemotePhysAddr), (ETM_P2C(void))PhysAddrPtr, ETH_PHYS_ADDR_LEN_BYTE); /*lint !e545 */

        if(E_OK == Etm_VParseHeader(DataPtr, LenByte, &ReceivedHeader))
        {
          if(Etm_CommandRetryCount > 0u)
          {
            if((ReceivedHeader.Gid == ETM_GID_GENERAL) && (ReceivedHeader.Pid == ETM_PID_END_TEST))
            {
              Etm_VGeneralEndTest(&ReceivedHeader);
            }
            else
            {
              Etm_VSendResponseWithoutPayload(&ReceivedHeader, ETM_RID_E_PEN);
            }
          }
          else
          {
            Etm_DataProcessingMode = TRUE;
            Etm_VProcessEtmCommands(&ReceivedHeader);
          }
        }
        else
        {
          Etm_VSendResponseWithoutPayload(&ReceivedHeader, ETM_RID_E_NOK);
        }

        return;
      }
    }

    ETM_DUMMY_STATEMENT_CONST(IsBroadcast); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#else
    ETM_DUMMY_STATEMENT_CONST(CtrlIdx);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    ETM_DUMMY_STATEMENT_CONST(FrameType);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    ETM_DUMMY_STATEMENT_CONST(IsBroadcast); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    ETM_DUMMY_STATEMENT_CONST(PhysAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    ETM_DUMMY_STATEMENT_CONST(DataPtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
    ETM_DUMMY_STATEMENT_CONST(LenByte);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* (ETM_ETHIF_ENABLED == STD_ON) */
  }
} /* Etm_EthIf_RxIndication() */

/**********************************************************************************************************************
 *  Etm_TcpAccepted()
 *********************************************************************************************************************/
/*! \brief        This function gets called if the stack put a socket into the listen mode before (as server) and a peer
 *                connected to it (as client).
 *  \details      The TCP/IP stack calls this function after a socket was set into the listen state with TcpIp_TcpListen()
 *                and a TCP connection is requested by the peer.
 *  \param[in]    SocketId            Socket identifier of the related local socket resource which has been used at TcpIp_Bind().
 *  \param[in]    SocketIdConnected   Socket identifier of the local socket resource used for the established connection.
 *  \param[in]    RemoteAddrPtr       IP address and port of the remote host.
 *  \return       E_OK                Accepts the established connection.
 *  \return       E_NOT_OK            Refuses the established connection, TcpIp stack shall close the connection.
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETM_CODE) Etm_TcpAccepted(
  TcpIp_SocketIdType SocketId,
  TcpIp_SocketIdType SocketIdConnected,
  ETM_P2V(TcpIp_SockAddrType) RemoteAddrPtr) /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
{
#if (ETM_SPECIAL_TCP_ACC_ENABLED != STD_ON)
  (void)Etm_TcpPreAccepted(SocketId, SocketIdConnected, RemoteAddrPtr);
#endif /* (ETM_SPECIAL_TCP_ACC_ENABLED != STD_ON) */

  if(Etm_DataProcessingMode == TRUE)
  {
    /* Etm_TcpPreAccepted allready called */

    const uint8 TestChannelIndexA = Etm_VFindTestChannelIndex(SocketId);
    const uint8 TestChannelIndexB = Etm_VFindTestChannelIndex(SocketIdConnected);

    if((TestChannelIndexA != ETM_INV_SOCKET_ID) && (TestChannelIndexB != ETM_INV_SOCKET_ID))
    {
      uint16 Index = ETM_HEADER_LENGTH;
      const uint16 AddressLength = ((RemoteAddrPtr->domain == TCPIP_AF_INET6) ? ETM_DATA_LEN_ADDRESS_IPV6 : ETM_DATA_LEN_ADDRESS_IPV4);

      /* Build Event Header */
      Etm_HeaderType EventHeader;
      EventHeader.Gid = ETM_GID_TCP;
      EventHeader.Pid = ETM_PID_TCP_LISTEN_AND_ACCEPT;
      EventHeader.UsePhysAddr = FALSE;

      /* Set Event Payload */
      (void)Etm_VSetNext16Bit(SocketId, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX);
      Index += 2u;
      (void)Etm_VSetNext16Bit(SocketIdConnected, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX);
      Index += 2u;
      (void)Etm_VSetNext16Bit(ETM_HTONS(((ETM_P2C(TcpIp_SockAddrInetType))RemoteAddrPtr)->port), Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX); /* PRQA S 0310, 3305 */ /* MD_Etm_11.4_0310_AddrPtr, MD_Etm_3305 */
      Index += 2u;
      (void)Etm_VSetNext16Bit(AddressLength, Index, Etm_SendBuffer, ETM_MESSAGE_LENGTH_MAX); /* Set vint length */
      Index += 2u;
      /* PRQA S 0310, 0314, 3305 1 */ /* MD_Etm_11.4_0310_AddrPtr, MD_MSR_VStdLibCopy, MD_Etm_3305 */
      VStdLib_MemCpy((ETM_P2V(void))&Etm_SendBuffer[Index], (ETM_P2C(void))&(((ETM_P2C(TcpIp_SockAddrInet6Type))RemoteAddrPtr)->addr), AddressLength); /*lint !e545 */
      Index += AddressLength;
      Etm_SendBufferLength = Index;

      /* Send Event */
      Etm_VSendEvent(&EventHeader);
    }
  }

  return E_OK;
}

/**********************************************************************************************************************
 *  Etm_TcpPreAccepted()
 *********************************************************************************************************************/
/*! \brief        This function is similar to 'Etm_TcpAccepted'.
 *  \details      This function is similar to 'Etm_TcpAccepted'. This function is called right after receiving a
 *                'SYN' on a TCP listen socket and reports the listen socket ID and the ID of the socket that will
 *                accept the connection request. These sockets are the same ones that are reported in the offical call
 *                'Etm_TcpAccepted' later on. The reported socket IDs may only be used for analysis purposes,
 *                the accepting socket may not be used in any way before it is fully connected (reported by call of
 *                'Etm_TcpAccepted'). This function is needed if the socket IDs are needed in the TCP states
 *                SYN-RECV or SYN-SEND.
 *  \param[in]    SocketId            Socket identifier of the related local socket resource which has been used at TcpIp_Bind().
 *  \param[in]    SocketIdConnected   Socket identifier of the local socket resource used for the established connection.
 *  \param[in]    RemoteAddrPtr       IP address and port of the remote host.
 *  \return       E_OK                Return always E_OK.
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETM_CODE) Etm_TcpPreAccepted(
  TcpIp_SocketIdType SocketId,
  TcpIp_SocketIdType SocketIdConnected,
  ETM_P2V(TcpIp_SockAddrType) RemoteAddrPtr) /* PRQA S 3673 */ /* MD_Etm_16.7_3673 */
{
  ETM_DUMMY_STATEMENT_CONST(RemoteAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */

  if(Etm_DataProcessingMode == TRUE)
  {
    const uint8 TestChannelIndex = Etm_VFindTestChannelIndex(SocketId);

    if(TestChannelIndex != ETM_INV_SOCKET_ID)
    {
      const uint8 TestChannelIndexUsed = Etm_VFindTestChannelIndex(SocketIdConnected); /* socketid not yet indexed */
      const uint8 TestChannelIndexFree = Etm_VFindTestChannelIndex(ETM_INV_SOCKET_ID); /* free index present */

      if((TestChannelIndexUsed == ETM_INV_SOCKET_ID) && (TestChannelIndexFree != ETM_INV_SOCKET_ID))
      {
        Etm_TestChannels[TestChannelIndexFree].SocketId = SocketIdConnected;
      }
    }
  }
  else if(Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V4].SocketId == SocketId)
  {
    Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C4].SocketId = SocketIdConnected;
  }
  else if(Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_V6].SocketId == SocketId)
  {
    Etm_CommandChannels[ETM_CMD_CHAN_IDX_TCP_C6].SocketId = SocketIdConnected;
  }
  else
  {
    /* MISRA */
  }

  return E_OK;
}

/**********************************************************************************************************************
 *  Etm_TcpConnected()
 *********************************************************************************************************************/
/*! \brief        This function gets called if the stack initiated a TCP connection before (as client) and the peer
 *                (the server) acknowledged the connection set up.
 *  \details      The TCP/IP stack calls this function after a socket was requested to connect with TcpIp_TcpConnect()
 *                and a TCP connection is confirmed by the peer. The parameter value of SocketId equals the SocketId
 *                value of the preceeding TcpIp_TcpConnect() call.
 *  \param[in]    SocketId    Socket identifier of the related local socket resource.
 *  \return       none
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_TcpConnected(
  TcpIp_SocketIdType SocketId)
{
  ETM_DUMMY_STATEMENT_CONST(SocketId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
}

/**********************************************************************************************************************
 *  Etm_TcpIpEvent()
 *********************************************************************************************************************/
/*! \brief        This function gets called if the stack encounters a condition described by the values in TcpIpEvent.
 *  \param[in]    SocketId    Socket identifier of the related local socket resource.
 *  \param[in]    Event       This parameter contains a description of the event just encountered.
 *  \return       none
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
/* PRQA S 6030 1 */ /* MD_MSR_STCYC */
FUNC(void, ETM_CODE) Etm_TcpIpEvent(
  TcpIp_SocketIdType SocketId,
  IpBase_TcpIpEventType Event)
{
  switch(Event)
  {
  case TCPIP_TCP_CLOSED: /* IPBASE_TCP_EVENT_CLOSED */
    {
      uint8 TestChannelIndex = Etm_VFindTestChannelIndex(SocketId);

      if(TestChannelIndex != ETM_INV_SOCKET_ID)
      {
        Etm_TestChannels[TestChannelIndex].SocketId = ETM_INV_SOCKET_ID;
        Etm_TestChannels[TestChannelIndex].RecvFwdActive = FALSE;
        Etm_TestChannels[TestChannelIndex].RecvFwdDropCount = 0u;
        Etm_TestChannels[TestChannelIndex].RecvFwdMaxForward = 0u;
        Etm_TestChannels[TestChannelIndex].RecvFwdMaxLength = 0u;
      }
    }
    break;
  case TCPIP_TCP_FIN_RECEIVED: /* fall through */ /* IPBASE_TCP_EVENT_FIN_RECEIVED */
  case TCPIP_TCP_RESET:        /* fall through */ /* IPBASE_TCP_EVENT_RESET */
  default:
    {
      /* do nothing */
    }
    break;
  }
} /* Etm_TcpIpEvent() */

/**********************************************************************************************************************
 *  Etm_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief        This function gets called by the TCP/IP stack if an IP address assignment changes
 *                (i.e. new address assigned or assigned address becomes invalid).
 *  \param[in]    LocalIpAddrId   IP address Identifier, representing an IP address specified in the TcpIp module
 *                                configuraiton (e.g. static IPv4 address on EthIf controller 0).
 *  \param[in]    State           State of IP address assignment.
 *  \return       none
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_LocalIpAddrAssignmentChg(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  TcpIp_IpAddrStateType State)
{
#if ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4))
  /* ETMv4 */
  if(LocalIpAddrId == ETM_TCPIP_LOCAL_ADDRESS_IDV4)
  {
    switch(State)
    {
      case TCPIP_IPADDR_STATE_ASSIGNED:
        Etm_IpV4LinkAssigned = TRUE;
        break;
      case TCPIP_IPADDR_STATE_UNASSIGNED:
        Etm_DataProcessingMode = FALSE;
        Etm_IpV4LinkAssigned = FALSE;
        Etm_ModuleInitAll = FALSE;

        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_UDP_V4);
        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_TCP_V4);
        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_TCP_C4);
        break;
      default: /* TCPIP_IPADDR_STATE_ONHOLD */
        /* ignore TCPIP_IPADDR_STATE_ONHOLD */
        break;
    }
  }
#endif /* ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4)) */

#if ((ETM_IPV6_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6))
  /* ETMv6 */
  if(LocalIpAddrId == ETM_TCPIP_LOCAL_ADDRESS_IDV6)
  {
    switch(State)
    {
      case TCPIP_IPADDR_STATE_ASSIGNED:
        Etm_IpV6LinkAssigned = TRUE;
        break;
      case TCPIP_IPADDR_STATE_UNASSIGNED:
        Etm_DataProcessingMode = FALSE;
        Etm_IpV6LinkAssigned = FALSE;
        Etm_ModuleInitAll = FALSE;

        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_UDP_V6);
        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_TCP_V6);
        Etm_VCloseCommandChannel(ETM_CMD_CHAN_IDX_TCP_C6);
        break;
      default: /* TCPIP_IPADDR_STATE_ONHOLD */
        /* ignore TCPIP_IPADDR_STATE_ONHOLD */
        break;
    }
  }
#endif /* ((ETM_IPV6_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV6)) */
}

/**********************************************************************************************************************
 *  Etm_CopyTxData()
 *********************************************************************************************************************/
/*! \brief        This function requests to copy data for transmission to the buffer indicated. This call is triggered
 *                by TcpIp_Transmit(). Note: The call to Etm_CopyTxData() may happen in the context of TcpIp_Transmit().
 *  \param[in]    SocketId          Socket identifier of the related local socket resource.
 *  \param[in]    BufPtr            Pointer to buffer for transmission data.
 *  \param[in]    BufLength         Length of provided data buffer.
 *  \return       BUFREQ_OK         Data has been copied to the transmit buffer completely as requested.
 *  \return       BUFREQ_E_NOT_OK   Data has not been copied. Request failed. (No further action for TcpIp required.
 *                                  Later the upper layer might either close the socket or retry the transmit request)
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, ETM_CODE) Etm_CopyTxData(
  TcpIp_SocketIdType SocketId,
  ETM_P2V(uint8) BufPtr,
  uint16 BufLength)
{
  uint16 TmpSocketId = 0u;

  BufReq_ReturnType Result = BUFREQ_E_NOT_OK;
  Std_ReturnType ResultStd = Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 0u, &TmpSocketId);

  if((ResultStd == E_OK) && (SocketId == TmpSocketId)) /* PRQA S 2995 */ /* MD_MSR_ConstantCondition */
  {
    uint16 TotalLength = 0u;
    uint16 TmpDestAddrLength = 0u;
    TcpIp_SockAddrInXType TmpDestAddr = { 0u };

    uint8 TmpData = 0u;
    uint8 *TmpDataPtr = &TmpData;
    uint16 TmpDataLength = 0u;

    if(ETM_COND_VALID_UDP_SOCKET_ID(TmpSocketId))
    { /* Copy UDP data */
      (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 2u, &TotalLength);
      (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 4u, &(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port)); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      ResultStd  = Etm_VGetVIntAddr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 6u, (ETM_P2V(TcpIp_SockAddrType))&TmpDestAddr, &TmpDestAddrLength); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
      ResultStd |= Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, ((uint32)6u + (uint32)2u /* uint16 length */ + (uint32)TmpDestAddrLength), &TmpDataPtr, &TmpDataLength, FALSE);

      ((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port = ETM_HTONS(((ETM_P2V(TcpIp_SockAddrInetType))&TmpDestAddr)->port); /* PRQA S 0310 */ /* MD_Etm_11.4_0310_AddrPtr */
    }
    else
    { /* Copy TCP data */
      (void)Etm_VGetNext16Bit(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 2u, &TotalLength);
#if (ETM_STUB_PROTOCOL_VERSION >= 0x00010200uL) /* Version 1.2.0 */
      ResultStd = Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 5u, &TmpDataPtr, &TmpDataLength, FALSE);
#else
      ResultStd = Etm_VGetVIntDataPtr(Etm_CommandBuffer, ETM_STUB_MAX_COMMAND_SIZE, 4u, &TmpDataPtr, &TmpDataLength, FALSE);
#endif
    }

    if((ResultStd == E_OK) &&
       (TmpDataLength != 0u) /* there are data to transmit */)
    {
      uint16 Index;
      uint16 TmpCopyPatternStartPosition = Etm_SendDataCommandAlreadySend % TmpDataLength;

      for(Index = 0u;
          Index < BufLength;
          Index++)
      {
        BufPtr[Index] = TmpDataPtr[(TmpCopyPatternStartPosition + Index) % TmpDataLength];
      }

      Etm_SendDataCommandAlreadySend += Index;

      if(ETM_MAX(TotalLength, TmpDataLength) <= Etm_SendDataCommandAlreadySend)
      { /* Transmission completed --> all data send */
        Etm_CommandRetryCount = 0u;
        Etm_SendDataCommandAlreadySend = 0u;
      }

      Result = BUFREQ_OK;
    }
  }

  return Result;
}

/**********************************************************************************************************************
 *  Etm_DhcpEvent()
 *********************************************************************************************************************/
/*! \brief        Indicates reception of a DHCP option or that a DHCP message will be sent.
 *  \details      -
 *  \param[in]    LocalIpAddrId   Local IP address identifier.
 *  \param[in]    Event           Indicates the received message type or the message type who will be sent.
 *  \pre          Module is initialized.
 *  \context      INTERRUPT
 *  \reentrant    Non Reentrant.
 *  \synchronous  Synchronous.
 *********************************************************************************************************************/
FUNC(void, ETM_CODE) Etm_DhcpEvent(
  TcpIp_LocalAddrIdType LocalIpAddrId,
  TcpIp_DhcpEventType Event)
{
#if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
  if(Etm_DhcpOptionCode != 0u)
  {
    if(Etm_DhcpLocalIpAddrId == LocalIpAddrId)
    {
      if((Event == TCPIP_DHCP_EVENT_TX_DISCOVER_SOLICIT) ||
         (Event == TCPIP_DHCP_EVENT_TX_REQUEST))
      {
        (void)TcpIp_DhcpWriteOption(LocalIpAddrId, Etm_DhcpOptionCode, (uint8)Etm_DhcpOptionLength, (ETM_P2C(uint8))Etm_DhcpOptionBuf);
      }
    }
  }
#else
  ETM_DUMMY_STATEMENT_CONST(LocalIpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETM_DUMMY_STATEMENT_CONST(Event);         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif
}

#define ETM_STOP_SEC_CODE
#include "Etm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/

/* Justification for module-specific MISRA deviations:

  MD_Etm_8.7_3218:
    Reason:     Static variable is only to be used in one function.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_11.4_0310_AddrPtr:
    Reason:     TcpIp_SockAddrType includes address family to differ between IPv4 and IPv6. The corresponding
                structs also start with the family field so casting is possible.
    Risk:       Casing from IpBase_SockAddrInType or IpBase_SockAddrIn6Type to TcpIp_SockAddrType is allowed. Cast
                from TcpIp_SockAddrType to IpBase_SockAddrInType or IpBase_SockAddrIn6Type is possible if the address
                family field is evaluated. The corresponding struct IpBase_SockAddrInType or IpBase_SockAddrIn6Type
                has the port field on the same position so port can accesed without casting.
    Prevention: Code inspection.

  MD_Etm_11.4_0310_BufPtr:
    Reason:     Cast from uint32/(uint16) to uint8 for easer access to byte fields.
    Risk:       Depending on the buffer, an unaligned memory exception may occur on certain platforms.
    Prevention: Buffers passed to the function need to be 4/(2) byte aligned.

  MD_Etm_11.4_0310_Api:
    Reason:     Cast parameter to uint8 pointer used by API.
    Risk:       Cast to different object pointer type.
    Prevention: Code inspection.

  MD_Etm_12.4_3415_Side:
    Reason:     Second statement is only needed when first statement is true. The side effect is for local usage only (if both statements are true).
    Risk:       Undefined behavior in relation to the evaluation.
    Prevention: Code inspection.

  MD_Etm_16.7_3673:
    Reason:     Function prototype needs to be similar to specified AUTOSAR API of calling module.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_19.11_3332:
    Reason:     Usage of undefined macro (only in some configuration variants).
    Risk:       No functional risk.
    Prevention: Code inspection. Check if macro is defined before usage.

  MD_Etm_18.4_0759:
    Reason:     Usage of union type is used to save IPv6 address. Data can accessed as uint8(byte)/uint32 array.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_3305:
    Reason:     The different socket address types do all base on the same stucture, the allignment should always be the same so that mapping from one type to an other one should not be a problem.
    Risk:       Only casting between different variants of the socket type is allowed.
    Prevention: Code inspection.

  MD_Etm_21.1_2842:
    Reason:     Array Index is calculated automatically and is cecked befor usage.
    Risk:       Undefinded memory operation results in undefined behavior.
    Prevention: Code inspection.

  MD_Etm_2889:
    Reason:     Old api pattern.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_2981:
    Reason:     Redundant initialisation will force Misra or compiler warnings.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_2995:
    Reason:     Constant boolean value will force Misra or compiler warnings.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_2991:
    Reason:     The if-statement is needed to check whether the previous function call returned E_OK. Depending on
                the variant, this statement might be always true but is needed for other variants.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_2985:
    Reason:     The statement is needed in some variants. Depending on the variant, the value of the result is always
                that of the left-hand operand.
    Risk:       No functional risk.
    Prevention: Code inspection.

  MD_Etm_ObjectOnlyAccessedOnce:
    Reason:     There are generated structures and arrays which are sometimes only accessed by one function, in
                either the translation unit where they are defined or in another translation unit. We have generated
                and manually written source code and separate code and data structures. Due to preprocessing variants
                the above situation can occur.
    Risk:       It isn't clear which code and data structures belong together.
    Prevention: Code inspection.

 */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETM_BYTE_ORDER
  \ACCEPT XF
  \REASON Only little endian byte-order is tested.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: Etm.c
 *********************************************************************************************************************/
