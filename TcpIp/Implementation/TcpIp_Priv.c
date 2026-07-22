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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_Priv.c
 *        \brief  Implementation of TcpIp Module - Internal Functions
 *
 *      \details  This file is part of the TcpIp module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp module. >> TcpIp.h
 *********************************************************************************************************************/


/* PRQA S 0828 EOF */ /* MD_MSR_1.1 */

#define TCPIP_PRIV_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp_Priv.h"
#include "TcpIp.h"

#include "IpBase.h"

#include "EthSM.h"

#if (TCPIP_SUPPORT_TCP == STD_ON)
# include "TcpIp_Tcp.h"
#endif

#include "TcpIp_Udp.h"

#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
# include "TcpIp_DhcpV4.h"
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# include "TcpIp_IpV4.h"
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# include "TcpIp_IpV6.h"
# include "TcpIp_IpV6_Priv.h"
#endif

#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
# include "TcpIp_TlsCore.h"
# include "TcpIp_Tls.h"
#endif

#include "TcpIp_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

/* Defines for the IPv4 pseudo header used by UDP and TCP. (see [IETF RFC768 Page 2] and [IETF RFC793 Page 17]) */
#define TCPIP_IPV4_PSEUDO_HDR_OFS_SRC_ADDR  0u
#define TCPIP_IPV4_PSEUDO_HDR_OFS_DST_ADDR  4u
#define TCPIP_IPV4_PSEUDO_HDR_OFS_RESERVED  8u
#define TCPIP_IPV4_PSEUDO_HDR_OFS_PROTOCOL  9u
#define TCPIP_IPV4_PSEUDO_HDR_OFS_LENGTH   10u
#define TCPIP_IPV4_PSEUDO_HDR_LEN          12u

#define TCPIP_IPV6_PSEUDO_HDR_OFS_SRC_ADDR  0u
#define TCPIP_IPV6_PSEUDO_HDR_OFS_DST_ADDR 16u
#define TCPIP_IPV6_PSEUDO_HDR_OFS_LENGTH   32u
#define TCPIP_IPV6_PSEUDO_HDR_OFS_RESERVED 36u
#define TCPIP_IPV6_PSEUDO_HDR_OFS_NEXT_HDR 39u
#define TCPIP_IPV6_PSEUDO_HDR_LEN          40u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 /* PRQA S 3453 5 */ /* MD_MSR_FctLikeMacro */
#define ETHSM_TCPIP_MODE_INDICATION(CtrlIdx, TcpIpState)      \
                                                                      (void)EthSM_TcpIpModeIndication((CtrlIdx), (TcpIpState))
/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
#define TCPIP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

VAR(TcpIp_TcpIpErrorType, TCPIP_VAR_NO_INIT) TcpIp_LastSockError;                                                       /* PRQA S 1514 */ /* MD_TCPIP_Rule8.9_1514_1533 */

#if (TCPIP_MULTICORE_SUPPORT_ENABLED == STD_ON)                                                                         /* COV_TCPIP_MULTICORE_SUPPORT_ALWAYS_ON */
TCPIP_LOCAL VAR(TcpIp_OsApplicationType, TCPIP_VAR_NO_INIT) TcpIp_MainApplicationId;
#endif

#define TCPIP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define TCPIP_START_SEC_VAR_NO_INIT_8
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_VENABLE_CANOE_WRITE_STRING == STD_ON)                                                                        /* COV_TCPIP_CANOE_DEBUG */
VAR(sint8, TCPIP_VAR_NO_INIT)                TcpIp_CanoeWriteStr[256];
#endif

#define TCPIP_STOP_SEC_VAR_NO_INIT_8
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define TCPIP_START_SEC_VAR_NO_INIT_16
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_SUPPORT_TCP == STD_ON)
VAR(uint16, TCPIP_VAR_NO_INIT)               TcpIp_Tcp_DynamicPortCount;
#endif
VAR(uint16, TCPIP_VAR_NO_INIT)               TcpIp_Udp_DynamicPortCount;

#define TCPIP_STOP_SEC_VAR_NO_INIT_16
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/* PRQA S 0759, 1533 2 */ /* MD_MSR_Union, MD_TCPIP_Rule8.9_1514_1533 */
CONST(IpBase_AddrIn6Type, TCPIP_CONST) TcpIp_IpV6AddrUnspecified =                                                      /* PRQA S 1514 */ /* MD_TCPIP_Rule8.9_1514_1533 */
{
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  }
};
#endif

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  TcpIp_VMatchLocalIpAddrIdAndPort()
 *********************************************************************************************************************/
/*! \brief         Checks if an IPv4/IPv6 address matches the LocalAddrIdx to which the socket is bound.
 *  \details       -
 *  \param[in]     SocketIdx          Index of a UDP or TCP socket.
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfSocketDyn()-1]
 *  \param[in]     RxSockLocAddrPtr:  Pointer to the socket address.
 *  \param[in]     LocalAddrIdx       Index of a local address.
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfLocalAddr()-1]
 *  \return        TRUE in case the LocalAddrIdx matches the locaAddrIdx of the bound socket, FALSE otherwise.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_VMatchLocalIpAddrIdAndPort(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx);

/* Doubly Linked List (DList) Data Structure */

/* DList raw functions */

/**********************************************************************************************************************
 *  TcpIp_DListRawAddAfter()
 *********************************************************************************************************************/
/*! \brief         Inserts a node into a node chain.
 *  \details       -
 *  \param[in,out] NodeSetPtr  Storage array of the elements of the node chain.
 *  \param[in,out] FirstIdxPtr Index of the first element of the node chain.
 *                             Set to NewIdx if element is new first element.
 *                             CONSTRAINT: Must be a valid index in array referenced by NodeSetPtr or
 *                                         TCPIP_DLIST_END_IDX if chain is empty.
 *  \param[in,out] LastIdxPtr  Index of the last element of the node chain.
 *                             Set to NewIdx if element is new last element.
 *                             CONSTRAINT: Must be a valid index in array referenced by NodeSetPtr or
 *                                         TCPIP_DLIST_END_IDX if chain is empty.
 *  \param[in]     NewIdx      Index of the new element that shall be inserted into the node chain.
 *                             CONSTRAINT: Must be a valid index in array referenced by NodeSetPtr.
 *  \param[in]     AfterIdx    Index of the predecessor of the newly inserted element.
 *                             CONSTRAINT: Must be a valid index in array referenced by NodeSetPtr.
 *                                         Must be an element in the virtual chain between *FirstIdxPtr and *LastIdxPtr
 *                                         or TCPIP_DLIST_END_IDX if new item shall be inserted at the beginning.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawAddAfter(
  TCPIP_P2V(TcpIp_DListNodeType)  NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   LastIdxPtr,
  TcpIp_DListIdxType              NewIdx,
  TcpIp_DListIdxType              AfterIdx);

/**********************************************************************************************************************
 *  TcpIp_DListRawAddRangeAfter()
 *********************************************************************************************************************/
/*! \brief         Inserts a node chain into another node chain.
 *  \details       -
 *  \param[in,out] NodeSetPtr    Storage array of the elements of the node chain.
 *  \param[in,out] FirstIdxPtr   Index of the first element of the node chain.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1] or TCPIP_DLIST_END_IDX.
 *  \param[out]    LastIdxPtr    Index of the last element of the node chain.
 *                               Updated with the index of the inserted element if it was appended to the list.
 *  \param[in]     NewStartIdx   Index of the first element of the node chain that shall be inserted.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1]
 *  \param[in]     NewEndIdx     Index of the last element of the node chain that shall be inserted.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1]
 *  \param[in]     AfterIdx      Index of the predecessor of the newly inserted node chain.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1] or TCPIP_DLIST_END_IDX.
 *                               If AfterIdx is TCPIP_DLIST_END_IDX the chain will be inserted at the beginning.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawAddRangeAfter(
  TCPIP_P2V(TcpIp_DListNodeType)  NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   LastIdxPtr,
  TcpIp_DListIdxType              NewStartIdx,
  TcpIp_DListIdxType              NewEndIdx,
  TcpIp_DListIdxType              AfterIdx);

/**********************************************************************************************************************
 *  TcpIp_DListRawRemove()
 *********************************************************************************************************************/
/*! \brief         Removes a node from a node chain.
 *  \details       -
 *  \param[in,out] NodeSetPtr    Storage array of the elements of the node chain.
 *  \param[out]    FirstIdxPtr   Index of the first element of the node chain.
 *                               Updated with the index of the first element that remains in list,
 *                               if the range was removed from beginning.
 *  \param[out]    LastIdxPtr    Index of the last element of the node chain.
 *                               Updated with the index of the last element that remains in list,
 *                               if the range was removed from end.
 *  \param[in]     RemIdx        Index of the element that shall be removed.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawRemove(
  TCPIP_P2V(TcpIp_DListNodeType)  NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   LastIdxPtr,
  TcpIp_DListIdxType              RemIdx);

/**********************************************************************************************************************
 *  TcpIp_DListRawRemoveRange()
 *********************************************************************************************************************/
/*! \brief         Removes a sub chain from a node chain.
 *  \details       -
 *  \param[in,out] NodeSetPtr    Storage array of the elements of the node chain.
 *  \param[out]    FirstIdxPtr   Index of the first element of the node chain.
 *                               Updated with the index of the first element that remains in list,
 *                               if the range was removed from beginning.
 *  \param[out]    LastIdxPtr    Index of the last element of the node chain.
 *                               Updated with the index of the last element that remains in list,
 *                               if the range was removed from end.
 *  \param[in]     RemStartIdx   Index of the first element that shall be removed.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1]
 *  \param[in]     RemEndIdx     Index of the last element that shall be removed.
 *                               CONSTRAINT: [0...<#Elements at NodeSetPtr>-1]
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DListRawRemoveRange(
  TCPIP_P2V(TcpIp_DListNodeType) NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  LastIdxPtr,
  TcpIp_DListIdxType             RemStartIdx,
  TcpIp_DListIdxType             RemEndIdx);

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_GetBaseStateIpV6Ctrl()
 *********************************************************************************************************************/
/*! \brief         Get the TcpIpState of the IPv6 ctrl
 *  \details       -
 *  \param[in]     IpV6State   The IPv6 ctrl State
 *  \return        The related TcpIpState for the IPv6 ctrl state
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_StateType, TCPIP_CODE) TcpIp_GetBaseStateIpV6Ctrl(
  TcpIp_StateType IpV6State);
# endif
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_GetBaseStateIpV4Ctrl()
 *********************************************************************************************************************/
/*! \brief         Get the TcpIpState of the IPv4 ctrl
 *  \details       -
 *  \param[in]     IpV4State   The IPv4 ctrl State
 *  \return        The related TcpIpState for the IPv4 ctrl state
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
FUNC(TcpIp_StateType, TCPIP_CODE) TcpIp_GetBaseStateIpV4Ctrl(
  TcpIp_StateType IpV4State);
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_VMatchLocalIpAddrIdAndPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_VMatchLocalIpAddrIdAndPort(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfLocalAddrType localAddrBindIdx = TcpIp_GetLocalAddrBindIdxOfSocketDyn(SocketIdx);
  boolean                   retVal = FALSE;
  uint8                     matchType;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return TRUE if socket is bound to the same address or to a fitting broadcast/All-Node. */
  if (TcpIp_VerifyAddrIdAcceptable(localAddrBindIdx, LocalAddrIdx, &matchType) == TRUE)                                 /* SBSW_TCPIP_PtrToLocalVariable */
  {
    /* #20 If IP address matches to bound IP address return TRUE if port is equal to the bound port of the socket. */
    retVal = IpBase_SockPortIsEqual(&TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->SockAddr, &RxSockLocAddrPtr->SockAddr); /* SBSW_TCPIP_SockPortIsEqual */
  }
  else
  {
    /* Socket is bound to invalid address. */
  }

  return retVal;
} /* TcpIp_VMatchLocalIpAddrIdAndPort() */

/**********************************************************************************************************************
 *  TcpIp_VRxUdpSockIdxIdent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_VRxUdpSockIdxIdent(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketIdx;
  TcpIp_SocketDynIterType socketIdxMatch = TCPIP_SOCKET_IDX_INV;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(RxSockLocAddrPtr != NULL_PTR);
  TCPIP_ASSERT(LocalAddrIdx < TcpIp_GetSizeOfLocalAddr());

  /* #10 Iterate over all UDP sockets. */
  for (socketIdx = 0; socketIdx < TcpIp_GetSizeOfSocketUdpDyn(); socketIdx++)
  {
    /* #20 Check if UDP socket is bound. */
    if (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx) == TCPIP_SOCK_CONN_LISTEN_ENABLED)
    {
      /* #30 Check if socket is bound to a LocalAddrId and a port that match the specified IP address and port. */
      if (TcpIp_VMatchLocalIpAddrIdAndPort(socketIdx, RxSockLocAddrPtr, LocalAddrIdx) == TRUE)                          /* SBSW_TCPIP_NonNullPtrParameter */
      {
        socketIdxMatch = socketIdx;
        break;
      }
    }
  }

  return socketIdxMatch;
}
/* PRQA L:CTRL_NEST_LIMIT */ /* MD_MSR_1.1_0715 */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VRxTcpSockIdxIdent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_VRxTcpSockIdxIdent(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketMatchIdx;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Search for a bound matching socket. */
  socketMatchIdx = TcpIp_SearchTcpComSocket(LocalAddrIdx, RxSockLocAddrPtr, RxSockRemAddrPtr);                          /* SBSW_TCPIP_CheckedPtrParameter */

  /* #20 If no bound socket is found, search for a fitting listen socket. */
  if (socketMatchIdx == TCPIP_SOCKET_IDX_INV)
  {
    socketMatchIdx = TcpIp_SearchTcpListenSocket(RxSockLocAddrPtr, LocalAddrIdx, TRUE);                                 /* SBSW_TCPIP_CheckedPtrParameter */
  }

  return socketMatchIdx;
}
#endif

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_SetLastSockError
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_SetLastSockError(TcpIp_TcpIpErrorType Error)
{
  /* #10 Store the given error code 'Error' in the error variable that can be read out by the application. */
  TcpIp_LastSockError = Error;
}
#endif

/**********************************************************************************************************************
 *  TcpIp_VInitSockets
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VInitSockets(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketDynType socketIdx;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_LastSockError = 0;
#if (TCPIP_MULTICORE_SUPPORT_ENABLED == STD_ON)                                                                         /* COV_TCPIP_MULTICORE_SUPPORT_ALWAYS_ON */
  /* Set the application calling init as the main application */
  TcpIp_MainApplicationId = GetApplicationID();
#endif

  /* #10 Iterate all configured sockets and call the internal initialization function for each socket. */
  for (socketIdx = 0; socketIdx < TcpIp_GetSizeOfSocketDyn(); socketIdx++)
  {
    TcpIp_VInitSocket(socketIdx);
  }
}

/**********************************************************************************************************************
 *  TcpIp_VInitSocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VInitSocket(
  TcpIp_SocketDynIterType SocketIdx )
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_VDelSockAddrMapping(SocketIdx);
  /* #10 Initialize all admin data of the socket identified by the given socket index. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if (TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))
  {
    TcpIp_Tcp_VClearTxBuffer(TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx));
  }
  else
#endif
  {
    TcpIp_SetTxBufRequestedOfSocketDyn(SocketIdx, FALSE);                                                               /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  }

  TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_NONE);                                            /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(SocketIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN);                        /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_VPreconfigSocket(SocketIdx);
}

/**********************************************************************************************************************
 *  TcpIp_VDelSockAddrMapping
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
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_VDelSockAddrMapping(
  TcpIp_SocketDynIterType SocketIdx )
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_SOCKET_ID_IS_VALID(SocketIdx));

  /* #10 Clear sockets local and remote socket address value. */
  TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx)->sa_family = IPBASE_AF_UNSPEC;                                             /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->sa_family = IPBASE_AF_UNSPEC;                                             /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  (void)IpBase_CopyIpV6Addr(&TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx)->SockAddrIn6.sin6_addr, &TcpIp_IpV6AddrUnspecified);
  (void)IpBase_CopyIpV6Addr(&TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->SockAddrIn6.sin6_addr, &TcpIp_IpV6AddrUnspecified);
#else
  TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx)->SockAddrIn.sin_addr = TCPIP_INADDR_ANY;                                   /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->SockAddrIn.sin_addr = TCPIP_INADDR_ANY;                                   /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
#endif

  TcpIp_GetAddrRemSockOfSocketDyn(SocketIdx)->DomainAndPort.port = TCPIP_PORT_NOT_SET;                                  /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx)->DomainAndPort.port = TCPIP_PORT_NOT_SET;                                  /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

  /* #20 Clear socket owner and connection state. */
  TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(SocketIdx, TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN);                        /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_NONE);                                            /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

  /* #30 Reset TCP related parameters, if socket is a TCP socket. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if (TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))
  {
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    TcpIp_SetMaxNumListenSocketsOfSocketTcpDyn(socketTcpIdx, 0);                                                        /* SBSW_TCPIP_TcpIdxFromValidSocketIdx */
    TcpIp_SetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(socketTcpIdx,                                              /* SBSW_TCPIP_TcpIdxFromValidSocketIdx */
      TCPIP_NO_SOCKETTCPDYNMASTERLISTENSOCKETIDXOFSOCKETTCPDYN);
  }
#endif

  /* #40 Reset IP address binding to ANY. */
  /* Socket has ANY binding. This means use any IP on any controller for transmission */
  TcpIp_SetTxIpAddrIdxOfSocketDyn(     SocketIdx, TCPIP_IPVX_ADDR_IDX_ANY);                                             /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
  TcpIp_SetLocalAddrBindIdxOfSocketDyn(SocketIdx, TCPIP_LOCALADDRID_ANY);                                               /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

  /* #50 Reset socket specific parameters in IP submodules. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  IpV4_Ip_ResetSocket(SocketIdx);
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  IpV6_ResetSocket(SocketIdx);
#endif

#if (TCPIP_MULTICORE_SUPPORT_ENABLED == STD_ON)                                                                         /* COV_TCPIP_MULTICORE_SUPPORT_ALWAYS_ON */
  /* Reset all sockets to the main application */
  TcpIp_SetApplIdOfSocketDyn(SocketIdx, TcpIp_MainApplicationId);                                                       /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
#endif
} /* TcpIp_VDelSockAddrMapping() */

/**********************************************************************************************************************
 *  TcpIp_VSockIpAddrIsEqual
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VSockIpAddrIsEqual(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean match = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SockAPtr != NULL_PTR);
  TCPIP_ASSERT(SockBPtr != NULL_PTR);

  /* #10 Check the socket families to be equal (basic precondition for comparison). */
  if (SockAPtr->sa_family == SockBPtr->sa_family)
  {
    /* #20 Depending on the address family, compare address and port of the given sockets. */
    switch (SockAPtr->sa_family)
    {
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    case IPBASE_AF_INET:
    {
      match = (boolean)(SockAPtr->SockAddrIn.sin_addr == SockBPtr->SockAddrIn.sin_addr);                                /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    }
    break;
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    case IPBASE_AF_INET6:
    {
      /* PRQA S 4304 4 */ /* MD_MSR_AutosarBoolean */
      match = (boolean)(   (SockAPtr->SockAddrIn6.sin6_addr.addr32[0] == SockBPtr->SockAddrIn6.sin6_addr.addr32[0])
                        && (SockAPtr->SockAddrIn6.sin6_addr.addr32[1] == SockBPtr->SockAddrIn6.sin6_addr.addr32[1])
                        && (SockAPtr->SockAddrIn6.sin6_addr.addr32[2] == SockBPtr->SockAddrIn6.sin6_addr.addr32[2])
                        && (SockAPtr->SockAddrIn6.sin6_addr.addr32[3] == SockBPtr->SockAddrIn6.sin6_addr.addr32[3]));
    }
    break;
#endif
    default:
      /* No match: Leave match at value FALSE. */
      break;
    }
  }

  return match;
} /* TcpIp_VSockIpAddrIsEqual() */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockAddrIpAndPortIsEqual
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VSockAddrIpAndPortIsEqual(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean match = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SockAPtr != NULL_PTR);
  TCPIP_ASSERT(SockBPtr != NULL_PTR);
  /* #10 Compare ports. */
  if (SockAPtr->DomainAndPort.port == SockBPtr->DomainAndPort.port)
  {
    /* #20 Compare IP addresses. */
    match = TcpIp_VSockIpAddrIsEqual(SockAPtr, SockBPtr);                                                               /* SBSW_TCPIP_NonNullPtrParameter */
  }

  return match;
}

/**********************************************************************************************************************
 *  TcpIp_VNetAddrIsUnicast
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VNetAddrIsUnicast(
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine the domain of the socket address. */
  switch(SockAddrPtr->sa_family)
  {
# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
  case IPBASE_AF_INET:
    {
      /* #20 For an IPv4 socket address check the address to be valid, non-multicast and non-broadcast. */
      /* socket address struct is always filled in network byte order */
      TcpIp_NetAddrType SockNetAddr = SockAddrPtr->SockAddrIn.sin_addr;

      if( (0u != SockNetAddr) /* invalid global '0' address */ &&
          (!IPV4_ADDR_IS_MULTICAST(SockNetAddr)) /* multicast address */ &&
          (SockNetAddr != TCPIP_INADDR_BROADCAST) /* global broadcast */
          /* subnet broadcasts can not be detected here */ )
      {
        retVal = TRUE;
      }
      else
      {
        retVal = FALSE;
      }
      break;
    }
# endif
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  case IPBASE_AF_INET6:
    {
      /* #30 For an IPv6 socket address check the first byte of the address (in network byte order) to be non-0xff. */
      /* Read the first by of the address (network byte order). */
      P2CONST(uint8, AUTOMATIC, TCPIP_APPL_VAR) firstBytePtr = &SockAddrPtr->SockAddrIn6.sin6_addr.addr[0];
      if ((*firstBytePtr  != 0xFFu))
      {
        retVal = TRUE;
      }
      else
      {
        retVal = FALSE;
      }
      break;
    }
# endif
  default:
    {
      retVal = FALSE;  /* no valid domain type */
      break;
    }
  }

  return retVal;
} /* TcpIp_VNetAddrIsUnicast() */
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/**********************************************************************************************************************
 *  TcpIp_VCalcIpV4PseudoHdrChecksum
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint32, TCPIP_CODE) TcpIp_VCalcIpV4PseudoHdrChecksum(
  IpBase_AddrInType RemAddr,
  IpBase_AddrInType LocAddr,
  uint8             Protocol,
  uint16            ProtocolPayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             ipV4PseudoHdr[TCPIP_IPV4_PSEUDO_HDR_LEN];
  IpBase_AddrInType remIpAddrHbo = TCPIP_NTOHL(RemAddr);
  IpBase_AddrInType locIpAddrHbo = TCPIP_NTOHL(LocAddr);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Create IPv4 pseudo header. */
  TCPIP_PUT_UINT32(ipV4PseudoHdr, TCPIP_IPV4_PSEUDO_HDR_OFS_SRC_ADDR, remIpAddrHbo);                                    /* SBSW_TCPIP_ipVXPseudoHdrArray */
  TCPIP_PUT_UINT32(ipV4PseudoHdr, TCPIP_IPV4_PSEUDO_HDR_OFS_DST_ADDR, locIpAddrHbo);                                    /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV4PseudoHdr[TCPIP_IPV4_PSEUDO_HDR_OFS_RESERVED] = 0;                                                                /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV4PseudoHdr[TCPIP_IPV4_PSEUDO_HDR_OFS_PROTOCOL] = Protocol;                                                         /* SBSW_TCPIP_ipVXPseudoHdrArray */
  TCPIP_PUT_UINT16(ipV4PseudoHdr, TCPIP_IPV4_PSEUDO_HDR_OFS_LENGTH, ProtocolPayloadLen);                                /* SBSW_TCPIP_ipVXPseudoHdrArray */
  /* #20 Call IpBase_TcpIpChecksumAdd() and return not finalized checksum. */
  return IpBase_TcpIpChecksumAdd(&ipV4PseudoHdr[0], sizeof(ipV4PseudoHdr), 0, FALSE);                                   /* SBSW_TCPIP_ipVXPseudoHdrArray */
} /* TcpIp_VCalcIpV4PseudoHdrChecksum() */
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_VCalcIpV6PseudoHdrChecksum
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint32, TCPIP_CODE) TcpIp_VCalcIpV6PseudoHdrChecksum(
  TCPIP_P2C(IpBase_AddrIn6Type) RemAddrPtr,
  TCPIP_P2C(IpBase_AddrIn6Type) LocAddrPtr,
  uint8                         Protocol,
  uint16                        ProtocolPayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_LEN];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Create IPv6 pseudo header. */
  /* PRQA S 0315 2 */ /* MD_MSR_VStdLibCopy */
  IpBase_Copy(&ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_SRC_ADDR], &RemAddrPtr->addr[0], IPV6_ADDRESS_LEN_BYTE);         /* SBSW_TCPIP_ipVXPseudoHdrArray */
  IpBase_Copy(&ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_DST_ADDR], &LocAddrPtr->addr[0], IPV6_ADDRESS_LEN_BYTE);         /* SBSW_TCPIP_ipVXPseudoHdrArray */
  TCPIP_PUT_UINT32(ipV6PseudoHdr, TCPIP_IPV6_PSEUDO_HDR_OFS_LENGTH, ProtocolPayloadLen);                                /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_RESERVED]      = 0u;                                                          /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_RESERVED + 1u] = 0u;                                                          /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_RESERVED + 2u] = 0u;                                                          /* SBSW_TCPIP_ipVXPseudoHdrArray */
  ipV6PseudoHdr[TCPIP_IPV6_PSEUDO_HDR_OFS_NEXT_HDR] = Protocol;                                                         /* SBSW_TCPIP_ipVXPseudoHdrArray */

  /* #20 Call IpBase_TcpIpChecksumAdd() and return not finalized checksum. */
  return IpBase_TcpIpChecksumAdd(&ipV6PseudoHdr[0], sizeof(ipV6PseudoHdr), 0u, FALSE);                                  /* SBSW_TCPIP_ipVXPseudoHdrArray */
} /* TcpIp_VCalcIpV6PseudoHdrChecksum() */
#endif

/**********************************************************************************************************************
 *  TcpIp_VCalcPseudoHdrAndChecksum
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint16, TCPIP_CODE) TcpIp_VCalcPseudoHdrAndChecksum(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(uint8)                  DataPtr,
  uint16                            DataLen,
  uint8                             Protocol)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 checksum;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DataPtr != NULL_PTR);
  TCPIP_ASSERT(TCPIP_IS_ADDR_FAMILY_SUPPORTED(RxSockRemAddrPtr->sa_family) == TRUE);
  TCPIP_ASSERT(RxSockRemAddrPtr->sa_family == RxSockLocAddrPtr->sa_family);

  /* #10 Calculate the checksum of the IP specific pseudo header. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  if (IPBASE_AF_INET == RxSockRemAddrPtr->sa_family)
# endif
  {
    /* IpV4 */
    checksum = TcpIp_VCalcIpV4PseudoHdrChecksum(RxSockRemAddrPtr->SockAddrIn.sin_addr, RxSockLocAddrPtr->SockAddrIn.sin_addr, Protocol, DataLen);
  }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  else
# endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  {
    /* IpV6 */
    checksum = TcpIp_VCalcIpV6PseudoHdrChecksum(&RxSockRemAddrPtr->SockAddrIn6.sin6_addr, &RxSockLocAddrPtr->SockAddrIn6.sin6_addr, Protocol, DataLen);
  }
#endif

  /* #20 Add the checksum of the payload and finalize checksum to 16 bit value. */
  checksum = IpBase_TcpIpChecksumAdd(DataPtr, DataLen, checksum, TRUE);                                                 /* SBSW_TCPIP_NonNullPtrParameter */

  return (uint16)checksum;
}

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_VDuplicateAddrDetected
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VDuplicateAddrDetected(
  TcpIp_LocalAddrIdType   LocalAddrId,
  TCPIP_P2C(uint8)        SrcAddrPtr,
  TCPIP_P2C(uint8)        RemotePhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_PhysAddrType          LocalPhysAddr = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId));

  /* #10 Verify that RemotePhysAddrPtr does not match the physical address of this node. */
  if (TcpIp_GetPhysAddr(LocalAddrId, &LocalPhysAddr[0]) == E_OK)
  {
    if (TcpIp_CmpLLAddr(RemotePhysAddrPtr, LocalPhysAddr) == FALSE)
    {
# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
      TcpIp_SizeOfLocalAddrType localAddrIdx;
      localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

      /* #20 Verify that LocalAddrId references an IPv6 address. */
      if (TCPIP_LOCAL_ADDR_IDX_IS_IPV6(localAddrIdx))                                                                   /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */ /*lint !e506 */
# endif
      {
        TcpIp_SockAddrBaseType sockAddr;                                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
        /* PRQA S 0315 1 */ /* MD_MSR_VStdLibCopy */
        IPV6_ADDR_COPY(sockAddr.SockAddrIn6.sin6_addr.addr[0], *SrcAddrPtr);
        sockAddr.SockAddrIn6.sin6_port = TCPIP_PORT_ANY;
        sockAddr.SockAddrIn6.sin6_family = IPBASE_AF_INET6;

        /* #30 Inform upper layers about a DADCONFLICT, if callback is configured. */
        if (TcpIp_GetDuplicateAddrDetectionFctPtr() != NULL_PTR)
        {
          TcpIp_GetDuplicateAddrDetectionFctPtr()(LocalAddrId, (TCPIP_P2C(TcpIp_SockAddrType)) &sockAddr.TcpIpSockAddr, &LocalPhysAddr[0], RemotePhysAddrPtr);
          TCPIP_DUMMY_STATEMENT(sockAddr.SockAddrIn6);                                                                  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
        }
      }
    }
  }
} /* TcpIp_VDuplicateAddrDetected() */
#endif

 /**********************************************************************************************************************
 *  TcpIp_VPhysAddrTableChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VPhysAddrTableChg(
  uint8                             CtrlIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) IpAddrPtr,
  TCPIP_P2V(uint8)                  PhysAddrPtr,
  boolean                           Valid)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_PhysAddrConfigIterType physAddrConfigIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case UDP queue for address cache misses is configured, clear pending UDP retry elements for unresolved destinations. */
  if (Valid == FALSE)
  {
    TcpIp_Udp_CancelRetriesForDestination(CtrlIdx, IpAddrPtr);                                                          /* SBSW_TCPIP_NonNullPtrParameter */
  }

  /* #20 Inform upper layers about the change in the physical address resolution table. */
  for (physAddrConfigIdx = 0; physAddrConfigIdx < TcpIp_GetSizeOfPhysAddrConfig(); physAddrConfigIdx++)
  {
    TcpIp_PhysAddrTableChgCbkType funcPtr = TcpIp_GetChgFuncPtrOfPhysAddrConfig(physAddrConfigIdx);

    if (funcPtr != NULL_PTR)
    {
      funcPtr(CtrlIdx, &IpAddrPtr->TcpIpSockAddr, PhysAddrPtr, Valid);                                                  /* SBSW_TCPIP_ChgFuncPtrOfPhysAddrConfig */
    }
  }
} /* TcpIp_VPhysAddrTableChg() */

/**********************************************************************************************************************
 *  TcpIp_RxIndicationFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_RxIndicationFunctions(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2V(TcpIp_SockAddrBaseType) RemoteSockAddrPtr,
  TCPIP_P2V(uint8)                  DataPtr,
  uint16                            DataLenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx          < TcpIp_GetSizeOfSocketDyn());
  TCPIP_ASSERT(RemoteSockAddrPtr != NULL_PTR);
  TCPIP_ASSERT(DataPtr           != NULL_PTR);

  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);

  if (socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig())
  {
    TcpIp_SocketIdType socketId = TCPIP_SOCKET_IDX_TO_ID(SocketIdx);

    /* #10 In case the index is valid, inform upper layers about the finalization of the reception on the given socket. */
    if (TcpIp_GetRxIndicationFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
    {
      TcpIp_GetRxIndicationFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId,                                      /* SBSW_TCPIP_SocketOwnerFuncPtr */
        &RemoteSockAddrPtr->TcpIpSockAddr, DataPtr, DataLenByte);
    }
    else
    {
      /* #20 Issue a DET error in case the mandatory callback to do that is not configured. */
      /* ERROR: Callback is mandatory. */
      TcpIp_CallDetReportError(TCPIP_API_ID_CBK_RX_INDICATION, TCPIP_E_CBK_REQUIRED);
    }
  }
  else
  {
    TCPIP_ASSERT_UNREACHABLE();
  }
}

/**********************************************************************************************************************
 *  TcpIp_TxConfirmationFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TxConfirmationFunctions(
  TcpIp_SocketDynIterType       SocketIdx,
  uint16                        DataLenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());

  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);

  if (socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig())
  {
    TcpIp_SocketIdType socketId = TCPIP_SOCKET_IDX_TO_ID(SocketIdx);

    /* #10 Inform the socket owner about the amount of transmitted data, if callback is configured. */
    if (TcpIp_GetTxConfirmationFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
    {
      TcpIp_GetTxConfirmationFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId, DataLenByte);                      /* SBSW_TCPIP_SocketOwnerFuncPtr */
    }
  }
  else
  {
    TCPIP_ASSERT_UNREACHABLE();
  }
}

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_TcpAcceptedFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_TcpAcceptedFunctions(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdx,
  TcpIp_SocketTcpDynIterType      SocketTcpIdxConnected,
  TCPIP_P2V(TcpIp_SockAddrType)   RemoteSockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType     retVal = E_NOT_OK;
  TcpIp_SocketIdType socketId;
  TcpIp_SocketIdType socketIdConnected;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketOwnerCfgIdx     < TcpIp_GetSizeOfSocketOwnerConfig());
  TCPIP_ASSERT(SocketTcpIdx          < TcpIp_GetSizeOfSocketTcpDyn());
  TCPIP_ASSERT(SocketTcpIdxConnected < TcpIp_GetSizeOfSocketTcpDyn());
  TCPIP_ASSERT(RemoteSockAddrPtr != NULL_PTR);

  socketId          = TCPIP_SOCKET_IDX_TO_ID(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx));
  socketIdConnected = TCPIP_SOCKET_IDX_TO_ID(TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdxConnected));

# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
/*
[REVIEW_G] c_accepted 16.03.00.0
[REVIEW_G] f_open 16.00.00.x
[REVIEW_G] t_open 16.00.00.x
[REVIEW_G] p_open 16.00.00.x
*/
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON )
  /* If the socket is assigned to a TLS connection, forward the call to the TLS core. */
  if (TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    retVal = TcpIp_TlsCoreLl_TcpAccepted(SocketTcpIdx, SocketTcpIdxConnected);
  }
  else
#  endif
# endif
  {
# ifdef C_REVIEW_VECTOR                                                                                                 /* COV_TCPIP_C_COMMENT_VECTOR */
/* [REVIEW_c] open visal 16.00.00.2 Improve: Maybe this check can be done in the "Listen" function, as we do it in "Connect". CROSSLINK002 */
/* [REVIEW_c] stored visal, visbdk: Will be implemented in TCPIP-6199. */
/* [REVIEW_c] accepted visal 16.03.00.0 Statement: OK */
# endif
    /* #10 In case the index is valid and a callout is configured for that user, inform the socket user about the acceptance of the socket. */
    if (TcpIp_GetTcpAcceptedFuncPtrOfSocketOwnerConfig(SocketOwnerCfgIdx) != NULL_PTR)
    {
      retVal = TcpIp_GetTcpAcceptedFuncPtrOfSocketOwnerConfig(SocketOwnerCfgIdx)(socketId, socketIdConnected,           /* SBSW_TCPIP_SocketOwnerFuncPtr_2 */
        RemoteSockAddrPtr);
    }
    /* #20 Otherwise issue a DET error. */
    else
    {
      /* ERROR: Callback is mandatory. */
      TcpIp_CallDetReportError(TCPIP_API_ID_CBK_TCP_ACCEPTED, TCPIP_E_CBK_REQUIRED);
    }
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_TcpConnectedFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TcpConnectedFunctions(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx;
  TcpIp_SocketDynIterType           socketIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);

  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
#  if (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON)
  /* Check if socket supports Tls */
  if(TcpIp_IsUseTlsOfSocketTcpDyn(SocketTcpIdx) == TRUE)
  {
    /* Tcp connection has been made, trigger TLS client handshake */
    if (TcpIp_TlsCoreLl_TcpConnected((TcpIp_SizeOfSocketDynType)socketIdx) == E_NOT_OK)
    {
      /* Tls Client is unavailable, Report connection failure */
      TcpIp_CallDetReportError(TCPIP_API_ID_CBK_TCP_CONNECTED, TCPIP_E_TLS_ERROR);
    }
  }
  else
#  endif /* (TCPIP_SUPPORT_ASRTLSCLIENT == STD_ON) */
# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
  {
    /* The socketOwnerCfgIdx can be assumed to be valid since it was already checked when calling TcpConnect. */
    TcpIp_SocketIdType socketId = TCPIP_SOCKET_IDX_TO_ID(socketIdx);

    /* #10 Inform the socket user about the connection of the socket. */
    TcpIp_GetTcpConnectedFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId);                                       /* SBSW_TCPIP_SocketOwnerFuncPtr */
  }
}
#endif

/**********************************************************************************************************************
 *  TcpIp_TcpIpEventFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_TcpIpEventFunctions(
  TcpIp_SocketOwnerConfigIterType SocketOwnerCfgIdx,
  TcpIp_SocketDynIterType         SocketIdx,
  IpBase_TcpIpEventType           EventType)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig());
  TCPIP_ASSERT(SocketIdx         < TcpIp_GetSizeOfSocketDyn());

  /* #10 In case a callout is configured for that user, inform the socket user about the TCP event related to that socket. */
  if (TcpIp_GetTcpIpEventFuncPtrOfSocketOwnerConfig(SocketOwnerCfgIdx) != NULL_PTR)
  {
    TcpIp_GetTcpIpEventFuncPtrOfSocketOwnerConfig(SocketOwnerCfgIdx)(TCPIP_SOCKET_IDX_TO_ID(SocketIdx), EventType);     /* SBSW_TCPIP_SocketOwnerFuncPtr_2 */
  }
  else
  {
    /* #20 Otherwise issue a DET error. */
    /* ERROR: Callback is mandatory. */
    TcpIp_CallDetReportError(TCPIP_API_ID_CBK_TCP_IP_EVENT, TCPIP_E_CBK_REQUIRED);
  }
}

/**********************************************************************************************************************
 *  TcpIp_CopyTxDataFunctions
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
FUNC(BufReq_ReturnType, TCPIP_CODE) TcpIp_CopyTxDataFunctions(
  TcpIp_SizeOfSocketDynType SocketIdx,
  TCPIP_P2V(uint8)          BufferPtr,
  TCPIP_P2V(uint16)         BufferLenBytePtr,
  boolean                   UseTlsCopyTxData)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType                 retVal            = BUFREQ_E_NOT_OK;
  TcpIp_SizeOfSocketOwnerConfigType socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(SocketIdx);

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx         < TcpIp_GetSizeOfSocketDyn());
  TCPIP_ASSERT(BufferPtr         != NULL_PTR);
  TCPIP_ASSERT(BufferLenBytePtr  != NULL_PTR);

  {
#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
    TcpIp_SizeOfSocketTcpDynType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

    /* #10 Check if the function is called by the Tls record layer */
    if((UseTlsCopyTxData == TRUE) && (TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE))                              /* PRQA S 3415 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
    {
      /* #20 if so, forward the call to the Tls record layer. */
      retVal = TcpIp_TlsCoreRl_EncryptAndAuthFrame(SocketIdx, BufferPtr, *BufferLenBytePtr);
    }
    else
      /* #30 otherwise, the call comes from the socket owner, so call the socketOwner configured CopyTxDataFct. */
#else
    TCPIP_DUMMY_STATEMENT_CONST(UseTlsCopyTxData);                                                                      /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
    {
      if(socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig())
      {
        TcpIp_SocketIdType socketId = TCPIP_SOCKET_IDX_TO_ID(SocketIdx);

        /* #40 Call extended CopyTxData callback of socket owner, if configured. */
        if(TcpIp_GetCopyTxDataDynFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
        {
          retVal = TcpIp_GetCopyTxDataDynFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId, BufferPtr, BufferLenBytePtr); /* SBSW_TCPIP_SocketOwnerFuncPtr */
        }
        /* #50 Otherwise: Call AUTOSAR CopyTxData callback of socket owner, if configured. */
        else if(TcpIp_GetCopyTxDataFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx) != NULL_PTR)
        {
          retVal = TcpIp_GetCopyTxDataFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx)(socketId, BufferPtr, *BufferLenBytePtr); /* SBSW_TCPIP_SocketOwnerFuncPtr */
        }
        /* #60 Otherwise: Report an error to the Det. */
        else
        {
          /* ERROR: Callback is mandatory. */
          TcpIp_CallDetReportError(TCPIP_API_ID_CBK_COPY_TX_DATA, TCPIP_E_CBK_REQUIRED);
        }
      }
      else
      {
        TCPIP_ASSERT_UNREACHABLE();
      }
    }
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_LocalIpAssignmentChgFunctions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_LocalIpAssignmentChgFunctions(
  TcpIp_LocalAddrIterType LocalAddrIdx,
  TcpIp_IpAddrStateType   AddrState)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrIdx < TcpIp_GetSizeOfLocalAddr());
  /* #10 Notify all socket owners about changed IP address assignment, if callbacks are configured. */
  for (socketOwnerCfgIdx = 0; socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig(); socketOwnerCfgIdx++)
  {
    TcpIp_SocketOwnerLocalIpAddrAssignmentChgType callbackFuncPtr = TcpIp_GetLocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx);

    if (callbackFuncPtr != NULL_PTR)
    {
      callbackFuncPtr(TCPIP_LOCAL_ADDR_IDX_TO_ID(LocalAddrIdx), AddrState);                                             /* SBSW_TCPIP_SocketOwnerFuncPtr */
    }
  }
}

/**********************************************************************************************************************
 *  TcpIp_VIpTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_ReturnType, TCPIP_CODE) TcpIp_VIpTransmit(
  TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescPtr,
  uint16                                     IpPayloadLen,
  uint8                                      IpProtocol,
  uint8                                      UlTxReqIdx,
  uint8                                      Flags)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_ReturnType retVal;
  boolean          txConfirmation      = (boolean)((Flags & TCPIP_V_IP_TRANSMIT_FLAG_TX_CONFIRMATION) != 0u);           /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  boolean          retryOnPhysAddrMiss = (boolean)((Flags & TCPIP_V_IP_TRANSMIT_FLAG_RETRY_ON_PHYS_ADDR_MISS) != 0u);   /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TCPIP_IS_ADDR_FAMILY_SUPPORTED(IpTxReqDescPtr->AddressFamily));

  /* #10 Determine IP version (address family) of IP TX request descriptior and forward call to IPv4/IPv6 submodule. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  if (IpTxReqDescPtr->AddressFamily == IPBASE_AF_INET)
# endif
  {
    retVal = IpV4_Ip_Transmit(IpTxReqDescPtr, IpPayloadLen, IpProtocol, txConfirmation,                                 /* SBSW_TCPIP_NonNullPtrParameter */
               UlTxReqIdx, retryOnPhysAddrMiss);
  }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  else
# endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  {
    retVal = IpV6_Transmit(IpTxReqDescPtr->SockIdx, IpTxReqDescPtr, IpProtocol, IpPayloadLen, txConfirmation,           /* SBSW_TCPIP_NonNullPtrParameter */
               UlTxReqIdx, retryOnPhysAddrMiss);
  }
#endif

  return retVal;
} /* TcpIp_VIpTransmit() */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockTcpStateChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
 /* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_VSockTcpStateChg(
  TcpIp_SocketDynIterType         SocketIdx,
  TcpIp_SocketOwnerConfigIterType FormerSocketOwnerCfgIdx,
  TcpIp_StateType                 State,
  boolean                         SocketUsesTls)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
  TcpIp_TlsConnectionIterType tlsConIdx;
# else
  /* Parameter 'SocketUsesTls' is only used if TLS is enabled. */
  TCPIP_DUMMY_STATEMENT_CONST(SocketUsesTls);                                                                           /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx < TcpIp_GetSizeOfSocketDyn());
  TCPIP_ASSERT(TCPIP_SOCKET_IDX_IS_TCP(SocketIdx));

  /* #10 Set the state of the given Socket depending on the occurred event and forward the event */
  switch(State)
  {
  case TCPIP_TCP_STATE_CONN_ESTAB:
    TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_ACTIVE);                                        /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    break;

  case TCPIP_TCP_STATE_CONNECTED:
    TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_ACTIVE);                                        /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    TcpIp_TcpConnectedFunctions(TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx));
    break;

  case TCPIP_TCP_STATE_CLOSED:
    TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_NONE);                                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
    /* Check if the socket uses TLS and a corresponding TLS connection is assigned */
    if (   (SocketUsesTls == TRUE)                                                                                      /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
        && (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK))
    {
      /* Let TLS handle the CLOSE event for socket which uses TLS */
      TcpIp_TlsCoreEvent_TcpIpEventForwarding(SocketIdx, IPBASE_TCP_EVENT_CLOSED);
    }
    else
# endif
    {
      /* Socket does not use TLS or Socket is used by TLS-Listener */
      TcpIp_TcpIpEventFunctions(FormerSocketOwnerCfgIdx, SocketIdx, IPBASE_TCP_EVENT_CLOSED);
    }
    break;

  case TCPIP_TCP_STATE_RESET:
    TcpIp_SetListenActiveConnStatOfSocketDyn(SocketIdx, TCPIP_SOCK_CONN_NONE);                                          /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
    /* TLS only wants the information if the TCP connection is established. */
    /* TLS state is set in Ll_TcpConnected (after TCP handshake) to HS_ACTIVE */

    /* Check if the socket uses TLS and the TLS connections is in state active */
    if (   (SocketUsesTls == TRUE)                                                                                      /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
        && (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK))
    {
      /* Check if the TLS connection is already allocated to any socket */
      if (TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) == TCPIP_TLS_STATE_CONNECTION_ALLOCATED)
      {
        /* TLS connection is allocated, but not used yet. Reset the connection and let TCP handle the event */
        TcpIp_Tls_FreeAllocatedConnection(tlsConIdx);
      }

      if(TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) != TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE)
      {
        /* Let the TLS process the event only if the assigned TLS connections is active */
        TcpIp_TlsCoreEvent_TcpIpEventForwarding(SocketIdx, IPBASE_TCP_EVENT_RESET);
      }
      else
      {
        /* TLS is not active yet, let TcpIp handle the event */
        TcpIp_TcpIpEventFunctions(FormerSocketOwnerCfgIdx, SocketIdx, IPBASE_TCP_EVENT_RESET);
      }
    }
    else
      /* TLS connection is not used on this socket or socket is used by TLS-Listener - let TcpIp handle the event */
# endif
    {
      TcpIp_TcpIpEventFunctions(FormerSocketOwnerCfgIdx, SocketIdx, IPBASE_TCP_EVENT_RESET);
    }
    break;

  case TCPIP_TCP_STATE_CONN_REQ_REC:
    /* always accept the incoming connection, do not forward callback to upper layers */
    break;

  case TCPIP_TCP_STATE_FIN_REC:
    /* remote side starts to close the connection */
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
    if (SocketUsesTls == TRUE)
    {
      TcpIp_TlsCoreEvent_TcpIpEventForwarding(SocketIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);
    }
    else
# endif
    {
      TcpIp_TcpIpEventFunctions(FormerSocketOwnerCfgIdx, SocketIdx, IPBASE_TCP_EVENT_FIN_RECEIVED);
    }
    break;
  case TCPIP_TCP_STATE_CONN_CLOSING:
    /* No action to be done */
    break;

  default:
    /* should not happen - all other states are invalid */
    break;
  } /* switch */
}
#endif /* (TCPIP_SUPPORT_TCP == STD_ON) */

/**********************************************************************************************************************
 *  TcpIp_VSockTxConfirmation
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
FUNC(void, TCPIP_CODE) TcpIp_VSockTxConfirmation(
  TcpIp_SocketDynIterType SocketIdx,
  uint32                  DataLenByte)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketIdx      < TcpIp_GetSizeOfSocketDyn());


  /* #10 Update/decrease the internal buffer fill level according to the number of bytes confirmed. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if(TCPIP_SOCKET_IDX_IS_TCP(SocketIdx))
  {
    TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);
    TcpIp_TcpTxBufferDescIterType tcpTxBufferDescIdx = TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(socketTcpIdx);

    TCPIP_VENTER_CRITICAL_SECTION();

    TCPIP_ASSERT(tcpTxBufferDescIdx < TcpIp_GetSizeOfTcpTxBufferDesc());

    if(DataLenByte > 0u)
    {
      TCPIP_ASSERT(DataLenByte <= TcpIp_GetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx));

      TcpIp_SubFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, (TcpIp_SizeOfTcpTxBufferType)DataLenByte);             /* SBSW_TCPIP_tcpTxBufferDescIdx */
    }
    else
    {
      /* negative TxConfirmation */
      TcpIp_SetFillLevelOfTcpTxBufferDescDyn(tcpTxBufferDescIdx, 0);                                                    /* SBSW_TCPIP_tcpTxBufferDescIdx */
    }

    TCPIP_VLEAVE_CRITICAL_SECTION();
  }
#endif

  {
#if (TCPIP_SUPPORT_ASRTLS == STD_ON )                                                                                   /* COV_MSR_UNSUPPORTED */
    /* #20 Check if the given socket is used by TLS */
    if((TCPIP_SOCKET_IDX_IS_TCP(SocketIdx) == TRUE)                                                                     /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
      && (TcpIp_IsUseTlsOfSocketTcpDyn(TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx)) == TRUE))
    {
      /* #30 If the socket is used by TLS, skip the forwarding of the TxConfirmation. This will be done by the TLS stack. */


    }
    else
#endif
    {
      /* #40 Socket is not used by TLS, proceed with the TxConfirmation forwarding to the socket owner */
      /* #50 Confirm the overall length in chunks of at maximum 0xffff bytes. */
      if(DataLenByte <= TCPIP_TX_CONF_LEN_MAX)
      {
        /* forward confirmation to UL: */
        TcpIp_TxConfirmationFunctions(SocketIdx, (uint16)DataLenByte);
      }
      else
      {
        uint16 txConfLen;
        uint32 remainingTxConfLen = DataLenByte;
        while(remainingTxConfLen > 0u)
        {
          /* forward confirmation to UL: */
          if(remainingTxConfLen > TCPIP_TX_CONF_LEN_MAX)
          {
            txConfLen = (uint16)TCPIP_TX_CONF_LEN_MAX;
          }
          else
          {
            txConfLen = (uint16)remainingTxConfLen;
          }
          TcpIp_TxConfirmationFunctions(SocketIdx, txConfLen);
          remainingTxConfLen -= txConfLen;
        }
      }
    }
  }
} /* TcpIp_VSockTxConfirmation() */

/**********************************************************************************************************************
 *  TcpIp_Cbk_VLocalIpAssignmentChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VLocalIpAssignmentChg(
  TcpIp_LocalAddrIterType LocalAddrIdx,
  TcpIp_IpAddrStateType   State)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrIdx < TcpIp_GetSizeOfLocalAddr());

  /* #10 Store the new state of the given local address index. */
  TcpIp_SetAssignmentStateOfLocalAddr(LocalAddrIdx, State);                                                             /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */

  /* #20 Reset the affected IP controller in case the new state is 'unassigned'. */
  if(TCPIP_IPADDR_STATE_UNASSIGNED == State)
  {
    TcpIp_VRstCtrl(LocalAddrIdx);
  }

  /* #30 Forward notification to upper layer via configured callbacks. */
  TcpIp_LocalIpAssignmentChgFunctions(LocalAddrIdx, State); /*lint !e522 */ /* Function may have no side-effects depending on configuration. */
} /* TcpIp_Cbk_VLocalIpAssignmentChg() */

/**********************************************************************************************************************
 *  TcpIp_Cbk_VPathMtuChg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VPathMtuChg(
  uint8                             CtrlIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) SockAddrPtr,
  uint16                            PathMtuSize)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SockAddrPtr != NULL_PTR);
  TCPIP_ASSERT(CtrlIdx <= TcpIp_GetSizeOfEthIfCtrl());                                                                  /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  TCPIP_DUMMY_STATEMENT_CONST(CtrlIdx);                                                                                 /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

#if (TCPIP_SUPPORT_TCP == STD_ON)
  /* #10 Forward path-MTU callback to TCP submodule in case it is configured. */
  TcpIp_Tcp_CbkPathMtuChg(SockAddrPtr, PathMtuSize);                                                                    /* SBSW_TCPIP_NonNullPtrParameter */
#else
  TCPIP_DUMMY_STATEMENT_CONST(SockAddrPtr);                                                                             /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  TCPIP_DUMMY_STATEMENT_CONST(PathMtuSize);                                                                             /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

} /* TcpIp_Cbk_VPathMtuChg() */

/**********************************************************************************************************************
 *  TcpIp_Cbk_VAddrResTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_Cbk_VAddrResTimeout(
  TCPIP_P2C(TcpIp_SockAddrBaseType) DestAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DestAddrPtr != NULL_PTR);

  /* #10 Forward the timeout event to the TCP subcomponent in case it is configured. */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  /* check all sockets in TCP */
  TcpIp_Tcp_VAddrResTimeout(DestAddrPtr);                                                                               /* SBSW_TCPIP_NonNullPtrParameter */
#else
  TCPIP_DUMMY_STATEMENT_CONST(DestAddrPtr);                                                                             /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

  /* Forwarding the timeout event to the UDP subcomponent is not required because UDP is 'fire and forget'. */
}

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VSockTcpStateChgAccepted
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VSockTcpStateChgAccepted(
  TcpIp_SocketTcpDynIterType SocketTcpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                  retVal = E_NOT_OK;
  TcpIp_SocketTcpDynIterType      listenSocketTcpIdx;
  TcpIp_SocketDynIterType         socketIdx;
  TcpIp_SocketOwnerConfigIterType socketOwnerCfgIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(SocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());

  socketIdx = TCPIP_TCP_IDX_TO_SOCKET_IDX(SocketTcpIdx);
  socketOwnerCfgIdx = TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(socketIdx);

  if (socketOwnerCfgIdx < TcpIp_GetSizeOfSocketOwnerConfig())
  {
    /* #10 Accept the new TCP connection on the derived socket identified by SocketIdx. */
    /* 'SocketIdx' is the new derived socket that is used for the TCP connection (not the listen socket!) */
    listenSocketTcpIdx = TcpIp_GetSocketTcpDynMasterListenSocketIdxOfSocketTcpDyn(SocketTcpIdx);
    TcpIp_SetListenActiveConnStatOfSocketDyn(socketIdx, TCPIP_SOCK_CONN_ACTIVE);                                        /* SBSW_TCPIP_SocketIdxFromValidTcpIdx */

    /* #20 Inform the upper layers about the new, accepted, TCP connection. */
    TCPIP_ASSERT(listenSocketTcpIdx < TcpIp_GetSizeOfSocketTcpDyn());
    retVal = TcpIp_TcpAcceptedFunctions(socketOwnerCfgIdx, listenSocketTcpIdx, SocketTcpIdx,                            /* SBSW_TCPIP_TcpAcceptedFunctions */
                                        &TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->TcpIpSockAddr);
  }
  else
  {
    TCPIP_ASSERT_UNREACHABLE();
  }

  return retVal;
} /* TcpIp_VSockTcpStateChgAccepted() */
#endif
/* (STD_ON == TCPIP_SUPPORT_TCP) */

/**********************************************************************************************************************
 *  TcpIp_VIpTransmitCancel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VIpTransmitCancel(
    TCPIP_P2C(TcpIp_IpTxRequestDescriptorType) IpTxReqDescrPtr,
    uint8                                      UlTxReqTabIdx,
    uint8                                      IpProtocol)
{
  /* ----- Implementation ----------------------------------------------- */
  /* TxConfirmation is always set to 'FALSE' */
  TCPIP_ASSERT(TCPIP_IS_ADDR_FAMILY_SUPPORTED(IpTxReqDescrPtr->AddressFamily));

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
/* Parameter 'IpProtocol' is only used if IPv4 is enabled. */
#else
  TCPIP_DUMMY_STATEMENT_CONST(IpProtocol);                                                                              /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  /* #10 Forward call to particular IpV4 or IpV6 subcomponent, based on the domain. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  if (IpTxReqDescrPtr->AddressFamily == IPBASE_AF_INET)
# endif
  {
    /* IpV4 destination address is set to '0' since it is not used in IpV4 for this usecase */
    (void)IpV4_Ip_Transmit(IpTxReqDescrPtr, 0, IpProtocol, FALSE, UlTxReqTabIdx, FALSE);                                /* SBSW_TCPIP_NonNullPtrParameter */
  }
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  else
# endif
#endif
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  {
    TCPIP_DUMMY_STATEMENT_CONST(UlTxReqTabIdx);                                                                         /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

    IpV6_CancelTransmit(IpTxReqDescrPtr);
  }
#endif
} /* TcpIp_VIpTransmitCancel() */

/**********************************************************************************************************************
 *  TcpIp_VRstCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_VRstCtrl(TcpIp_LocalAddrIterType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketDynIterType socketIdx;
#if (TCPIP_SUPPORT_TCP == STD_ON)
  TcpIp_SockAddrBaseType sockAddr;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
#endif

  /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_TCP == STD_ON)
    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
  IpBase_Fill((TCPIP_P2V(void))&sockAddr, 0u, sizeof(TcpIp_SockAddrBaseType));                                          /* SBSW_TCPIP_PointerCombinationSizeof */

  (void)TcpIp_GetIpAddr(TCPIP_LOCAL_ADDR_IDX_TO_ID(LocalAddrIdx), &sockAddr.TcpIpSockAddr, NULL_PTR, NULL_PTR);         /* SBSW_TCPIP_GetIpAddr */
#endif
  /* #10 Check all sockets that are bound to the given local address id whether they are in state 'listen' or 'connected'. */
  for (socketIdx = 0; socketIdx < TcpIp_GetSizeOfSocketDyn(); socketIdx++)
  {
    boolean initSocket = FALSE;
    /* Process if the socket is bound to the LocalAddrId. */
    if (TcpIp_GetLocalAddrBindIdxOfSocketDyn(socketIdx) == LocalAddrIdx)
    {
      /* #20 In case the socket is in the desired state, reset the socket, according to its associated protocol, TCP or UDP. */
      switch (TcpIp_GetListenActiveConnStatOfSocketDyn(socketIdx))
      {
      case TCPIP_SOCK_CONN_LISTEN_ENABLED:
#if (TCPIP_SUPPORT_TCP == STD_ON)
        if (TCPIP_SOCKET_IDX_IS_TCP(socketIdx))
        {
          /* Reset the TCP socket */
          TcpIp_VRstCtrl_TcpListen(socketIdx);
        }
        else
#endif
        {
          TcpIp_Udp_ResetSocket(socketIdx);
        }

        initSocket = TRUE;
      break;

#if (TCPIP_SUPPORT_TCP == STD_ON)
      case TCPIP_SOCK_CONN_ACTIVE:
        if (TcpIp_VSockIpAddrIsEqual(TcpIp_GetAddrLocSockOfSocketDyn(socketIdx), &sockAddr) == TRUE)                    /* SBSW_TCPIP_VSockIpAddrIsEqual */
        {
          /* TCP Socket. */
          TcpIp_Tcp_ResetSocket(TCPIP_SOCKET_IDX_TO_TCP_IDX(socketIdx));                                                /* PRQA S 2896 */ /* MD_TCPIP_2896 */
          initSocket = TRUE;
        }
        break;
#endif

      default:
        /* Socket not bound or established. -> Nothing to do. */
        break;
      }
      /* #30 In case the socket was reset, initialize its admin data. */
      if (initSocket == TRUE)
      {
        TcpIp_VInitSocket(socketIdx);
      }
    }
  }
} /* TcpIp_VRstCtrl() */


/**********************************************************************************************************************
 *  TcpIp_VRstCtrl_TcpListen
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#if (TCPIP_SUPPORT_TCP == STD_ON)
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_VRstCtrl_TcpListen(
  TcpIp_SocketDynIterType SocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SocketTcpDynIterType socketTcpIdx = TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx);

  /* ----- Implementation ----------------------------------------------- */
# if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                   /* COV_MSR_UNSUPPORTED */
  TcpIp_TlsConnectionIterType tlsConIdx;

  /* #10 Reset the listen socket, depending on the TLS usage. */

  /* Check if the socket uses TLS and the TLS connections is in state active */
  if ((TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)                                                              /* PRQA S 3415 3 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
    && (TcpIp_SocketIdxToTlsConIdx(SocketIdx, &tlsConIdx) == E_OK)
    && (TcpIp_GetConnectionStateOfTlsConnectionDyn(tlsConIdx) != TCPIP_TLS_STATE_CONNECTION_HS_INACTIVE))
  {
    /* TLS connection active - Let the TLS process the close. */
    TcpIp_TlsCoreEvent_TcpIpEventClose(SocketIdx, TRUE);
  }
#  if (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON)
  /* if-section copied from TcpIp_Close() */
  else if ((TcpIp_IsUseTlsOfSocketTcpDyn(socketTcpIdx) == TRUE)                                                         /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_ReadOnly */
    && (TcpIp_GetSockStateOfSocketTcpDyn(socketTcpIdx) == TCPIP_TCP_SOCK_STATE_LISTEN))
  {
    /* Reset the TCP socket and the TLS listener */
    TcpIp_TlsListener_Close(SocketIdx, TRUE);
  }
  else
#  endif /* (TCPIP_SUPPORT_ASRTLSSERVER == STD_ON) */
# endif /* (TCPIP_SUPPORT_ASRTLS == STD_ON) */
  {
    /* Reset the TCP socket */
    TcpIp_Tcp_ResetSocket(socketTcpIdx);
  }
}
#endif /* (TCPIP_SUPPORT_TCP == STD_ON) */


/**********************************************************************************************************************
 *  TcpIp_DListRawAddAfter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawAddAfter(
  TCPIP_P2V(TcpIp_DListNodeType)  NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   LastIdxPtr,
  TcpIp_DListIdxType              NewIdx,
  TcpIp_DListIdxType              AfterIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(NodeSetPtr  != NULL_PTR);
  TCPIP_ASSERT(FirstIdxPtr != NULL_PTR);
  TCPIP_ASSERT(LastIdxPtr  != NULL_PTR);

  NodeSetPtr[NewIdx].PrevIdx = AfterIdx;                                                                                /* SBSW_TCPIP_DList_NodeArrayIdx */

  /* #10 Insert the new node at the desired position, in case the index to insert the new node after is not the last element. */
  if (TCPIP_DLIST_END_IDX != AfterIdx)
  {
    /* insert after existing node */
    NodeSetPtr[NewIdx].NextIdx = NodeSetPtr[AfterIdx].NextIdx;                                                          /* SBSW_TCPIP_DList_NodeArrayIdx */
    NodeSetPtr[AfterIdx].NextIdx = NewIdx;                                                                              /* SBSW_TCPIP_DList_NodeArrayOrEndIdx */
  }
  /* #20 Otherwise insert the new node as the first element. */
  else
  {
    NodeSetPtr[NewIdx].NextIdx = (*FirstIdxPtr);                                                                        /* SBSW_TCPIP_DList_NodeArrayIdx */
    (*FirstIdxPtr) = NewIdx;                                                                                            /* SBSW_TCPIP_NonNullPtrParameter */
  }

  /* #30 Complete the linkage of the new node, depending on the node being the last node or not. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[NewIdx].NextIdx)
  {
    /* new node is not last node */
    NodeSetPtr[NodeSetPtr[NewIdx].NextIdx].PrevIdx = NewIdx;                                                            /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  else
  {
    /* new node is last node */
    (*LastIdxPtr) = NewIdx;                                                                                             /* SBSW_TCPIP_NonNullPtrParameter */
  }

} /* TcpIp_DListRawAddAfter() */

/**********************************************************************************************************************
 *  TcpIp_DListRawAddRangeAfter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 6060 1 */ /* MD_MSR_STPAR */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawAddRangeAfter(
  TCPIP_P2V(TcpIp_DListNodeType) NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  LastIdxPtr,
  TcpIp_DListIdxType             NewStartIdx,
  TcpIp_DListIdxType             NewEndIdx,
  TcpIp_DListIdxType             AfterIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(NodeSetPtr  != NULL_PTR);
  TCPIP_ASSERT(FirstIdxPtr != NULL_PTR);
  TCPIP_ASSERT(LastIdxPtr  != NULL_PTR);

  NodeSetPtr[NewStartIdx].PrevIdx = AfterIdx;                                                                           /* SBSW_TCPIP_DList_NodeArrayIdx */

  /* #10 Insert the new node-range at the desired position, in case the index to insert the new node-range after is not the last element. */
  if (TCPIP_DLIST_END_IDX != AfterIdx)
  {
    /* insert after existing node */
    NodeSetPtr[NewEndIdx].NextIdx = NodeSetPtr[AfterIdx].NextIdx;                                                       /* SBSW_TCPIP_DList_NodeArrayIdx */
    NodeSetPtr[AfterIdx].NextIdx  = NewStartIdx;                                                                        /* SBSW_TCPIP_DList_NodeArrayOrEndIdx */
  }
  /* #20 Otherwise insert the new node-range at the beginning. */
  else
  {
    /* insert as first node */
    NodeSetPtr[NewEndIdx].NextIdx = (*FirstIdxPtr);                                                                     /* SBSW_TCPIP_DList_NodeArrayIdx */
    (*FirstIdxPtr) = NewStartIdx;                                                                                       /* SBSW_TCPIP_NonNullPtrParameter */
  }

  /* #30 Complete the linkage of the new node-range, depending on the node-range being at the end or not. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[NewEndIdx].NextIdx)
  {
    /* new node is not last node */
    NodeSetPtr[NodeSetPtr[NewEndIdx].NextIdx].PrevIdx = NewEndIdx;                                                      /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  else
  {
    /* new node is last node */
    (*LastIdxPtr) = NewEndIdx;                                                                                          /* SBSW_TCPIP_NonNullPtrParameter */
  }

} /* TcpIp_DListRawAddRangeAfter() */

/**********************************************************************************************************************
 *  TcpIp_DListRawRemove()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DListRawRemove(
  TCPIP_P2V(TcpIp_DListNodeType)  NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)   LastIdxPtr,
  TcpIp_DListIdxType              RemIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(NodeSetPtr     != NULL_PTR);
  TCPIP_ASSERT(FirstIdxPtr    != NULL_PTR);
  TCPIP_ASSERT(LastIdxPtr     != NULL_PTR);
  TCPIP_ASSERT((*FirstIdxPtr) != TCPIP_DLIST_END_IDX);
  TCPIP_ASSERT((*LastIdxPtr)  != TCPIP_DLIST_END_IDX);
  TCPIP_ASSERT(RemIdx         != TCPIP_DLIST_END_IDX);

  /* #10 Remove the node to be removed from the its position, in case the index to remove the node is not the last element. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[RemIdx].PrevIdx)
  {
    /* node is not first node */
    NodeSetPtr[NodeSetPtr[RemIdx].PrevIdx].NextIdx = NodeSetPtr[RemIdx].NextIdx;                                        /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  /* #20 Otherwise remove the desired node at the beginning. */
  else
  {
    /* remove first node */
    (*FirstIdxPtr) = NodeSetPtr[RemIdx].NextIdx;                                                                        /* SBSW_TCPIP_NonNullPtrParameter */
  }

  /* #30 Re-link the remaining nodes, depending on whether the deleted node was placed at the end or not. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[RemIdx].NextIdx)
  {
    /* node is not last node */
    NodeSetPtr[NodeSetPtr[RemIdx].NextIdx].PrevIdx = NodeSetPtr[RemIdx].PrevIdx;                                        /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  else
  {
    /* remove last node */
    (*LastIdxPtr) = NodeSetPtr[RemIdx].PrevIdx;                                                                         /* SBSW_TCPIP_NonNullPtrParameter */
  }

  NodeSetPtr[RemIdx].PrevIdx = TCPIP_DLIST_END_IDX;                                                                     /* SBSW_TCPIP_DList_NodeArrayIdx */
  NodeSetPtr[RemIdx].NextIdx = TCPIP_DLIST_END_IDX;                                                                     /* SBSW_TCPIP_DList_NodeArrayIdx */

} /* TcpIp_DListRawRemove() */

/**********************************************************************************************************************
 *  TcpIp_DListRawRemoveRange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DListRawRemoveRange(
  TCPIP_P2V(TcpIp_DListNodeType) NodeSetPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  FirstIdxPtr,
  TCPIP_P2V(TcpIp_DListIdxType)  LastIdxPtr,
  TcpIp_DListIdxType             RemStartIdx,
  TcpIp_DListIdxType             RemEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_DListIdxType entryIdx;
  uint8              chainLength = 1;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(NodeSetPtr  != NULL_PTR);
  TCPIP_ASSERT(FirstIdxPtr != NULL_PTR);
  TCPIP_ASSERT(LastIdxPtr  != NULL_PTR);
  /* count number of elements in chain */
  entryIdx = RemStartIdx;

  while (RemEndIdx != entryIdx)
  {
    chainLength++;
    TCPIP_ASSERT_MSG(chainLength > 0, "DList chain length overflow detected!");
    entryIdx = NodeSetPtr[entryIdx].NextIdx;
    TCPIP_ASSERT(!(entryIdx == TCPIP_DLIST_END_IDX) && (RemEndIdx != TCPIP_DLIST_END_IDX));
  }

  /* #10 Remove the node-range to be removed from the its position, in case the starting index of the node-range to remove is not the last element. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[RemStartIdx].PrevIdx)
  {
    /* node is not first node */
    NodeSetPtr[NodeSetPtr[RemStartIdx].PrevIdx].NextIdx = NodeSetPtr[RemEndIdx].NextIdx;                                /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  /* #20 Otherwise remove the desired node at the beginning. */
  else
  {
    /* remove first node */
    (*FirstIdxPtr) = NodeSetPtr[RemEndIdx].NextIdx;                                                                     /* SBSW_TCPIP_NonNullPtrParameter */
  }

  /* #30 Re-link the remaining nodes, depending on whether the deleted node was placed at the end or not. */
  if (TCPIP_DLIST_END_IDX != NodeSetPtr[RemEndIdx].NextIdx)
  {
    /* node is not last node */
    NodeSetPtr[NodeSetPtr[RemEndIdx].NextIdx].PrevIdx = NodeSetPtr[RemStartIdx].PrevIdx;                                /* SBSW_TCPIP_DList_PrevOrNextIdx */
  }
  else
  {
    /* remove last node */
    (*LastIdxPtr) = NodeSetPtr[RemStartIdx].PrevIdx;                                                                    /* SBSW_TCPIP_NonNullPtrParameter */
  }

  NodeSetPtr[RemStartIdx].PrevIdx = TCPIP_DLIST_END_IDX;                                                                /* SBSW_TCPIP_DList_NodeArrayIdx */
  NodeSetPtr[RemEndIdx].NextIdx   = TCPIP_DLIST_END_IDX;                                                                /* SBSW_TCPIP_DList_NodeArrayIdx */

  return chainLength;
} /* TcpIp_DListRawRemoveRange() */

/**********************************************************************************************************************
 *  TcpIp_DListInitDesc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DListInitDesc(
  TCPIP_P2V(TcpIp_DListDescType) DescPtr,
  TCPIP_P2V(TcpIp_DListNodeType) NodePtr,
  uint8                          NodeCount)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Assign node list referenced by 'NodePtr' to the descriptor. */
  DescPtr->NodePtr = NodePtr;                                                                                           /* SBSW_TCPIP_NonNullPtrParameter */

  TCPIP_ASSERT(DescPtr != NULL_PTR);
  TCPIP_ASSERT(((NodeCount > 0) && (NodePtr != NULL_PTR)) || ((NodeCount == 0u) && (NodePtr == NULL_PTR)));

  /* #20 Let 'FirstFreeIdx' and 'LastFreeIdx' of descriptor point to the chain, if it contains at least one element. */
  if (NodeCount > 0u)
  {
    uint8_least dataIdx;

    DescPtr->FirstFreeIdx = 0;                                                                                          /* SBSW_TCPIP_NonNullPtrParameter */
    DescPtr->LastFreeIdx  = (TcpIp_DListIdxType)(NodeCount - 1u);                                                       /* SBSW_TCPIP_NonNullPtrParameter */

    /* #30 Iterate over the elements and create a doubly-linked chain. */
    for (dataIdx = 0; dataIdx < NodeCount; dataIdx++)
    {
      if (dataIdx > DescPtr->FirstFreeIdx)
      {
        NodePtr[dataIdx].PrevIdx = (TcpIp_DListIdxType)(dataIdx - 1u);                                                  /* SBSW_TCPIP_DList_InitDesc */
      }
      else
      {
        NodePtr[dataIdx].PrevIdx = TCPIP_DLIST_END_IDX;                                                                 /* SBSW_TCPIP_DList_InitDesc */
      }

      if (dataIdx < DescPtr->LastFreeIdx)
      {
        NodePtr[dataIdx].NextIdx = (TcpIp_DListIdxType)(dataIdx + 1u);                                                  /* SBSW_TCPIP_DList_InitDesc */
      }
      else
      {
        NodePtr[dataIdx].NextIdx = TCPIP_DLIST_END_IDX;                                                                 /* SBSW_TCPIP_DList_InitDesc */
      }
    }
  }
  /* #40 Otherwise: Mark 'FirstFreeIdx' and 'LastFreeIdx' of descriptor as invalid. */
  else
  {
    DescPtr->FirstFreeIdx = TCPIP_DLIST_END_IDX;                                                                        /* SBSW_TCPIP_NonNullPtrParameter */
    DescPtr->LastFreeIdx  = TCPIP_DLIST_END_IDX;                                                                        /* SBSW_TCPIP_NonNullPtrParameter */
  }

  DescPtr->ElementFreeCount  = NodeCount;                                                                               /* SBSW_TCPIP_NonNullPtrParameter */
  DescPtr->ElementTotalCount = NodeCount;                                                                               /* SBSW_TCPIP_NonNullPtrParameter */
} /* TcpIp_DListInitDesc() */

/**********************************************************************************************************************
 *  TcpIp_DListInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DListInit(
  TCPIP_P2V(TcpIp_DListType)     ListPtr,
  TCPIP_P2V(TcpIp_DListDescType) DescPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(ListPtr != NULL_PTR);
  TCPIP_ASSERT(DescPtr != NULL_PTR);
  /* #10 Connect a list instance to a descriptor and mark the list as empty. */
  ListPtr->DescPtr      = DescPtr;                                                                                      /* SBSW_TCPIP_NonNullPtrParameter */
  ListPtr->FirstIdx     = TCPIP_DLIST_END_IDX;                                                                          /* SBSW_TCPIP_NonNullPtrParameter */
  ListPtr->LastIdx      = TCPIP_DLIST_END_IDX;                                                                          /* SBSW_TCPIP_NonNullPtrParameter */
  ListPtr->ElementCount = 0;                                                                                            /* SBSW_TCPIP_NonNullPtrParameter */

} /* TcpIp_DListInit() */

/**********************************************************************************************************************
 *  TcpIp_DListAddElement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DListAddElement(
  TCPIP_P2V(TcpIp_DListType)    DListPtr,
  TcpIp_DListIdxType            AfterIdx,
  TCPIP_P2V(TcpIp_DListIdxType) NewIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DListPtr != NULL_PTR);
  TCPIP_ASSERT((AfterIdx == TCPIP_DLIST_END_IDX) || (AfterIdx < DListPtr->DescPtr->ElementTotalCount));

  TCPIP_VENTER_CRITICAL_SECTION();

  /* #10 Check if free list contains elements. */
  if (DListPtr->DescPtr->FirstFreeIdx != TCPIP_DLIST_END_IDX)
  {
    /* #20 Remove an element from the free list. */
    TcpIp_DListIdxType newIdx = DListPtr->DescPtr->FirstFreeIdx;
    TcpIp_DListRawRemove(DListPtr->DescPtr->NodePtr, &DListPtr->DescPtr->FirstFreeIdx, &DListPtr->DescPtr->LastFreeIdx, /* SBSW_TCPIP_DListRawFunctionCall */
      newIdx);
    DListPtr->DescPtr->ElementFreeCount--;                                                                              /* SBSW_TCPIP_NonNullPtrParameter */

    /* #30 Insert element into the target list at the specified position. */
    TcpIp_DListRawAddAfter(DListPtr->DescPtr->NodePtr, &DListPtr->FirstIdx, &DListPtr->LastIdx, newIdx, AfterIdx);      /* SBSW_TCPIP_DListRawFunctionCall */
    DListPtr->ElementCount++;                                                                                           /* SBSW_TCPIP_NonNullPtrParameter */
    (*NewIdxPtr) = newIdx;                                                                                              /* SBSW_TCPIP_NonNullPtrParameter */

    retVal = E_OK;
  }
  /* #40 Otherwise: Return negative result. */
  else
  {
    /* no free elements */
    /* leave retVal on value E_NOT_OK */
  }
  TCPIP_VLEAVE_CRITICAL_SECTION();

  return retVal;
} /* TcpIp_DListAddElement() */

/**********************************************************************************************************************
 *  TcpIp_DListRemoveElementRange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DListRemoveElementRange(
  TCPIP_P2V(TcpIp_DListType) DListPtr,
  TcpIp_DListIdxType         RemStartIdx,
  TcpIp_DListIdxType         RemEndIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 chainLength;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DListPtr != NULL_PTR);
  TCPIP_ASSERT(DListPtr->ElementCount > 0u);
  TCPIP_ASSERT(RemStartIdx < DListPtr->DescPtr->ElementTotalCount);
  TCPIP_ASSERT(RemEndIdx   < DListPtr->DescPtr->ElementTotalCount);

  /* #10 Remove given subchain from the list. */
  chainLength = TcpIp_DListRawRemoveRange(DListPtr->DescPtr->NodePtr, &DListPtr->FirstIdx, &DListPtr->LastIdx,          /* SBSW_TCPIP_DListRawFunctionCall */
    RemStartIdx, RemEndIdx);
  TCPIP_ASSERT(DListPtr->ElementCount >= chainLength);
  DListPtr->ElementCount -= chainLength;                                                                                /* SBSW_TCPIP_NonNullPtrParameter */

  /* #20 Append removed subchain to free list. */
  TcpIp_DListRawAddRangeAfter(DListPtr->DescPtr->NodePtr, &DListPtr->DescPtr->FirstFreeIdx,                             /* SBSW_TCPIP_DListRawFunctionCall */
    &DListPtr->DescPtr->LastFreeIdx, RemStartIdx, RemEndIdx, DListPtr->DescPtr->FirstFreeIdx);
  DListPtr->DescPtr->ElementFreeCount += chainLength;                                                                   /* SBSW_TCPIP_NonNullPtrParameter */

  TCPIP_ASSERT(DListPtr->DescPtr->ElementFreeCount <= DListPtr->DescPtr->ElementTotalCount);
} /* TcpIp_DListRemoveElementRange() */

/**********************************************************************************************************************
 *  TcpIp_DListRemoveElement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DListRemoveElement(
  TCPIP_P2V(TcpIp_DListType) DListPtr,
  TcpIp_DListIdxType         RemIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DListPtr != NULL_PTR);
  TCPIP_ASSERT(DListPtr->ElementCount > 0u);
  TCPIP_ASSERT(RemIdx < DListPtr->DescPtr->ElementTotalCount);

  TCPIP_VENTER_MC_ALWAYS_CRITICAL_SECTION();  /* lock cross core interrupts */
  /* #10 Remove element from list. */
  TcpIp_DListRawRemove(DListPtr->DescPtr->NodePtr, &DListPtr->FirstIdx, &DListPtr->LastIdx, RemIdx);                    /* SBSW_TCPIP_DListRawFunctionCall */
  TCPIP_ASSERT(DListPtr->ElementCount > 0u);
  DListPtr->ElementCount--;                                                                                             /* SBSW_TCPIP_NonNullPtrParameter */

  /* #20 Append removed element to the free list. */
  TcpIp_DListRawAddAfter(DListPtr->DescPtr->NodePtr, &DListPtr->DescPtr->FirstFreeIdx, &DListPtr->DescPtr->LastFreeIdx, /* SBSW_TCPIP_DListRawFunctionCall */
    RemIdx, DListPtr->DescPtr->FirstFreeIdx);
  DListPtr->DescPtr->ElementFreeCount++;                                                                                /* SBSW_TCPIP_NonNullPtrParameter */

  TCPIP_VLEAVE_MC_ALWAYS_CRITICAL_SECTION();
  TCPIP_ASSERT(DListPtr->DescPtr->ElementFreeCount <= DListPtr->DescPtr->ElementTotalCount);
} /* TcpIp_DListRemoveElement() */

/**********************************************************************************************************************
 *  TcpIp_DListClear()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DListClear(
  TCPIP_P2V(TcpIp_DListType) DListPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DListPtr != NULL_PTR);

  TCPIP_VENTER_MC_ALWAYS_CRITICAL_SECTION();  /* lock cross core interrupts */

  /* #10 Move all elements from the list to the free list, if the list is not already empty. */
  if (!TCPIP_DLIST_IS_EMPTY(*DListPtr))
  {
    TCPIP_ASSERT(DListPtr->ElementCount > 0u);
    TcpIp_DListRemoveElementRange(DListPtr, DListPtr->FirstIdx, DListPtr->LastIdx);                                     /* SBSW_TCPIP_DListRawFunctionCall */
  }
  else
  {
    TCPIP_ASSERT(DListPtr->ElementCount == 0u);
  }
  TCPIP_VLEAVE_MC_ALWAYS_CRITICAL_SECTION();

} /* TcpIp_DListClear() */

/**********************************************************************************************************************
 *  TcpIp_CmpLLAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_CmpLLAddr(
  TCPIP_P2C(uint8) LLAddr1Ptr,
  TCPIP_P2C(uint8) LLAddr2Ptr)
{
  boolean retVal;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LLAddr1Ptr != NULL_PTR);
  TCPIP_ASSERT(LLAddr2Ptr != NULL_PTR);
  /* #10 Return TRUE if and only if all 6 bytes of the two link layer addresses are equal */
  /* start by comparing last byte because this byte is most likely to differ. */
  retVal =  (   (LLAddr1Ptr[5] == LLAddr2Ptr[5])
          && (LLAddr1Ptr[4] == LLAddr2Ptr[4])
          && (LLAddr1Ptr[3] == LLAddr2Ptr[3])
          && (LLAddr1Ptr[2] == LLAddr2Ptr[2])
          && (LLAddr1Ptr[1] == LLAddr2Ptr[1])
          && (LLAddr1Ptr[0] == LLAddr2Ptr[0]))? TRUE: FALSE;

  return retVal;
} /* TcpIp_CmpLLAddr() */

/**********************************************************************************************************************
 *  TcpIp_VIsPortAndAddrUsedBySocket
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VIsPortAndAddrUsedBySocket(
  uint16                    Port,
  TcpIp_LocalAddrIterType   LocalAddrIdx,
  TcpIp_SocketDynIterType   SocketStartIdx,
  TcpIp_SocketDynIterType   SocketEndIdx,
  TcpIp_SocketDynIterType   SocketIgnoreIdx)
{
  boolean matchFound = FALSE;
  TcpIp_SocketDynIterType iterSocketIdx;

  uint16 portNbo = TCPIP_HTONS(Port);

  /* #10 Iterate over the provided socket range and check if any active socket uses the specified port and address.
         (SocketIgnoreIdx is ignored) */
  for (iterSocketIdx = SocketStartIdx; iterSocketIdx < SocketEndIdx; iterSocketIdx++)
  {
    if (   (iterSocketIdx != SocketIgnoreIdx)                                                                           /* PRQA S 3415 4 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetListenActiveConnStatOfSocketDyn(iterSocketIdx) != TCPIP_SOCK_CONN_NONE)
        && (TcpIp_GetAddrLocSockOfSocketDyn(iterSocketIdx)->DomainAndPort.port == portNbo)
        && (TcpIp_GetLocalAddrBindIdxOfSocketDyn(iterSocketIdx) == LocalAddrIdx))
    {
      matchFound = TRUE;
      break;
    }
  }

  return matchFound;
}

/**********************************************************************************************************************
 *  TcpIp_VFindUnusedDynamicPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint16, TCPIP_CODE) TcpIp_VFindUnusedDynamicPort(
  uint8                     Protocol,
  TcpIp_LocalAddrIterType   LocalAddrIdx,
  TcpIp_SocketDynIterType   SocketStartIdx,
  TcpIp_SocketDynIterType   SocketEndIdx,
  TcpIp_SocketDynIterType   SocketIgnoreIdx)
{
  uint16 portUnused = TCPIP_PORT_NOT_SET;

  TcpIp_SocketDynIterType iterationCount;
  TcpIp_SocketDynIterType iterationCountMax = SocketEndIdx - SocketStartIdx;

  /* #10 Try up to socketCount times to find a dynamic port number that is not used by other sockets. */
  for (iterationCount = 0; iterationCount < iterationCountMax; iterationCount++)
  {
    uint16 portCandidate = TcpIp_VGetNextDynamicPort(Protocol);

    if (TcpIp_VIsPortAndAddrUsedBySocket(portCandidate, LocalAddrIdx, SocketStartIdx, SocketEndIdx, SocketIgnoreIdx) == FALSE)
    {
      /* OK: Found usable dynamic port. */
      portUnused = portCandidate;
      break;
    }
  }

  return portUnused;
}

/**********************************************************************************************************************
 *  TcpIp_VGetNextDynamicPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint16, TCPIP_CODE) TcpIp_VGetNextDynamicPort(uint8 Protocol)
{
  /* ----- Local Variables ---------------------------------------------- */
  TCPIP_P2V(uint16) counterVarPtr;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT((Protocol == TCPIP_PROTOCOL_UDP) || (Protocol == TCPIP_PROTOCOL_TCP));

  TCPIP_VENTER_MC_ALWAYS_CRITICAL_SECTION();  /* lock cross core interrupts */
  /* #10 Determine dynamic port counter based on protocol (UDP/TCP). */
#if (TCPIP_SUPPORT_TCP == STD_ON)
  if (Protocol == TCPIP_PROTOCOL_TCP)
  {
    counterVarPtr = &TcpIp_Tcp_DynamicPortCount;
  }
  else
#else
  TCPIP_DUMMY_STATEMENT_CONST(Protocol);                                                                                /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  {
    counterVarPtr = &TcpIp_Udp_DynamicPortCount;
  }

  /* #20 Increment counter variable and handle the overflow. */
  if (*counterVarPtr < TCPIP_DYNAMIC_PORT_COUNT)
  {
    (*counterVarPtr)++;                                                                                                 /* SBSW_TCPIP_counterVarPtr */
  }
  else
  {
    (*counterVarPtr) = 0;                                                                                               /* SBSW_TCPIP_counterVarPtr */
  }
  TCPIP_VLEAVE_MC_ALWAYS_CRITICAL_SECTION();

  return (TCPIP_DYNAMIC_PORT_START + (*counterVarPtr));
}

/**********************************************************************************************************************
 *  TcpIp_VSetSocketSpecificFramePriority
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VSetSocketSpecificFramePriority(
  TcpIp_SocketDynIterType SocketIdx,
  uint8                   Value)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward call to IpV4 and/or IpV6 submodule, depending on configuration. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  retVal |= IpV4_Ip_SetEthIfFramePrio(SocketIdx, Value);                                                                /* PRQA S 2986 */ /* MD_TCPIP_Rule2.2_2986 */
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  retVal |= IpV6_SetEthIfFramePrio(SocketIdx, Value);                                                                   /* PRQA S 2986 */ /* MD_TCPIP_Rule2.2_2986 */
#endif

  return retVal;
} /* TcpIp_VSetSocketSpecificFramePriority() */

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VGetSocketSpecificFramePriority
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_VGetSocketSpecificFramePriority(
  TcpIp_SocketDynIterType           SocketIdx,
  TCPIP_P2V(uint8)                  Priority)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 ethFramePrio = IP_MAX_ETHIF_FRAME_PRIO;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read EthIfFramePrio from IpV4 and/or IpV6 submodule, depending on configuration. */
# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
  TcpIp_IpV4SocketDynIterType ipV4SocketIdx = SocketIdx;
  if ((IPV4_IP_TRANSFER_BLOCK_FLAG_ETHIF_FRAME_PRIO & TcpIp_GetTransferBlockOfIpV4SocketDyn(ipV4SocketIdx).Flags) != 0u)
  {
    ethFramePrio = TcpIp_GetTransferBlockOfIpV4SocketDyn(ipV4SocketIdx).EthIfFramePrio;
    retVal = E_OK;
  }
# endif
  if (ethFramePrio == IP_MAX_ETHIF_FRAME_PRIO)                                                                          /* PRQA S 2991, 2995 */ /* MD_TCPIP_Rule14.3_2741_2742_2991_2992_2995_2996 */
  {
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
    TcpIp_IpV6SocketDynIterType ipV6SocketIdx = SocketIdx;
    if ((IPV6_SOCKET_DATA_FLAG_ETHIF_FRAME_PRIO & TcpIp_GetFlagsOfIpV6SocketDyn(ipV6SocketIdx)) != 0u)
    {
      ethFramePrio = TcpIp_GetEthIfFramePrioOfIpV6SocketDyn(ipV6SocketIdx);
      retVal = E_OK;
    }
# endif
  }
  *Priority = ethFramePrio;                                                                                             /* SBSW_TCPIP_FUNC_PARAM_PTR_UPDATE */
  return retVal;
} /* TcpIp_VGetSocketSpecificFramePriority() */

/**********************************************************************************************************************
 *  TcpIp_VCopySocketSpecificFramePriority
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VCopySocketSpecificFramePriority(
  TcpIp_SocketDynIterType      SocketIdx,
  TcpIp_SocketDynIterType      ListenSocketIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 priority;
 /* ----- Implementation ----------------------------------------------- */
  /* #10 Read EthFramePrio from IpV4/IpV6 module depending on configuration. */
  retVal = TcpIp_VGetSocketSpecificFramePriority(ListenSocketIdx, &priority);                                           /* SBSW_TCPIP_UPDATE_VARIABLE */
  /* #20 If reading is successful, write it to the new created(duplicate) socket. */
  if (retVal == E_OK)
  {
    (void) TcpIp_VSetSocketSpecificFramePriority(SocketIdx, priority);
  }
} /* TcpIp_VCopySocketSpecificFramePriority() */
#endif

/**********************************************************************************************************************
 *  TcpIp_VIpV4NetmaskToCidr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint8, TCPIP_CODE) TcpIp_VIpV4NetmaskToCidr(IpBase_AddrInType IpV4Netmask)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Count number of least significant bits that are zero. */
  uint8  shiftCnt       = 0u;
  uint32 netmaskShifted = TCPIP_HTONL(IpV4Netmask);

  /* ----- Implementation ----------------------------------------------- */
  while ((shiftCnt < 32u) && ((netmaskShifted & 0x01u) == 0u))
  {
    netmaskShifted = netmaskShifted >> 1;
    shiftCnt++;
  }

  /* #20 Calculate number of of bits that are set. */
  return (uint8)(32u - shiftCnt);
} /* TcpIp_VIpV4NetmaskToCidr() */

#if (TCPIP_SUPPORT_ASRTLS == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  TcpIp_VIsPortUsedByAsrTls
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VIsPortUsedByAsrTls(
  uint16                    Port,
  TcpIp_TlsConnectionMode   Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_TlsConnectionIterType tlsConIdx;
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Iterate over all configured TLS connections. */
  for (tlsConIdx = 0; tlsConIdx < TcpIp_GetSizeOfTlsConnection(); tlsConIdx++)
  {
    /* #20 Check if the configured port is equivalent to the given Port */
    if (   (TcpIp_GetPortOfTlsConnection(tlsConIdx) == Port)                                                            /* PRQA S 3415 2 */ /* MD_TCPIP_Rule13.5_3415_CslReadOnly */
        && (TcpIp_GetModeOfTlsConnection(tlsConIdx) == Mode))
    {
      /* #30 if valid, return TRUE and exit the loop */
      retVal = TRUE;
      break;
    }
  }

  return retVal;
} /* TcpIp_VIsPortUsedByAsrTls() */
#endif

#if (TCPIP_SUPPORT_MEASUREMENT_DATA == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_VIncMeasurementDataCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 6030, 6050 1 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_VIncMeasurementDataCounter(
  TcpIp_MeasurementIdxType  MeasurementIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 measurementDataCnt;
  TCPIP_VENTER_MC_ALWAYS_CRITICAL_SECTION();  /* lock cross core interrupts */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Increment the measurement data counter only, if it is not going to overflow. */
  switch (MeasurementIdx)
  {
# if (TCPIP_SUPPORT_TCP == STD_ON)
  case TCPIP_MEAS_DROP_TCP:
    measurementDataCnt = TcpIp_GetDroppedTcpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedTcpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                           /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

  case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_TX_BUFFER:
    measurementDataCnt = TcpIp_GetDroppedTcpPacketsInsuffTxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedTcpPacketsInsuffTxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

  case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TCP_RX_BUFFER:
    measurementDataCnt = TcpIp_GetDroppedTcpPacketsInsuffRxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedTcpPacketsInsuffRxBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;
# endif

  case TCPIP_MEAS_DROP_UDP:
    measurementDataCnt = TcpIp_GetDroppedUdpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedUdpPacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                           /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

  case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER4:
    measurementDataCnt = TcpIp_GetDroppedVndrLayer4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedVndrLayer4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                    /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

# if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                     /* COV_TCPIP_IPV4_ALWAYS_ON */
  case TCPIP_MEAS_DROP_IPV4:
    measurementDataCnt = TcpIp_GetDroppedIpV4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedIpV4PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                          /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

  case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_IPV4_FRAGMENT_RX_BUFFER:
    measurementDataCnt = TcpIp_GetDroppedIpV4PacketsInsuffReassemblyBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedIpV4PacketsInsuffReassemblyBufOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                       /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;
# endif

# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  case TCPIP_MEAS_DROP_IPV6:
    measurementDataCnt = TcpIp_GetDroppedIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                          /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;

  case TCPIP_MEAS_VENDOR_SPECIFIC_DROP_LAYER3_IPV6:
    measurementDataCnt = TcpIp_GetDroppedVndrIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);
    if (measurementDataCnt < TCPIP_MEASUREMENTDATA_MAX)
    {
      TcpIp_IncDroppedVndrIpV6PacketsOfMeasurementData(TCPIP_MEASUREMENTDATA_IDX);                                      /* SBSW_TCPIP_MEASUREMENTDATA_IDX */
    }
    break;
# endif

  default:
    /* Unknown measurement data index. Nothing to do. */
    break;
  }
  TCPIP_VLEAVE_MC_ALWAYS_CRITICAL_SECTION();
} /* TcpIp_VIncMeasurementDataCounter() */
#endif

/**********************************************************************************************************************
 *  TcpIp_ReportSecurityEvent()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
FUNC(void, TCPIP_CODE) TcpIp_ReportSecurityEvent(
  TcpIp_SecurityEventIdType SecurityEventId)
{
#if (TCPIP_SUPPORT_SECURITY_EVENT_REPORTING == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  IdsM_SecurityEventIdType idsmSecurityEventId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Map the internal TcpIp security event to the configured IdsM security event. */
  switch(SecurityEventId)
  {
    case TCPIP_SECURITY_EVENT_ARP_IP_ADDR_CONFLICT:
      idsmSecurityEventId = TcpIp_GetARP_IP_ADDR_CONFLICTOfIdsmEvent(TCPIP_IDSMEVENT_IDX);
      break;

    case TCPIP_SECURITY_EVENT_INV_IPV4_ADDR:
      idsmSecurityEventId = TcpIp_GetDROP_INV_IPV4_ADDROfIdsmEvent(TCPIP_IDSMEVENT_IDX);
      break;

    case TCPIP_SECURITY_EVENT_INV_IPV6_ADDR:
      idsmSecurityEventId = TcpIp_GetDROP_INV_IPV6_ADDROfIdsmEvent(TCPIP_IDSMEVENT_IDX);
      break;

    case TCPIP_SECURITY_EVENT_INV_PORT_TCP:
      idsmSecurityEventId = TcpIp_GetDROP_INV_PORT_TCPOfIdsmEvent(TCPIP_IDSMEVENT_IDX);
      break;

    case TCPIP_SECURITY_EVENT_INV_PORT_UDP:
      idsmSecurityEventId = TcpIp_GetDROP_INV_PORT_UDPOfIdsmEvent(TCPIP_IDSMEVENT_IDX);
      break;

    default:
      /* Unknown security event. */
      idsmSecurityEventId = TCPIP_INV_IDSM_ID;
      break;
  }

  /* #20 Check if the corresponding security event is configured. */
  if (idsmSecurityEventId != TCPIP_INV_IDSM_ID)
  {
    /* #30 Report the security event to the IdsM. */
    IdsM_SetSecurityEvent(idsmSecurityEventId);
  }
#else
  TCPIP_DUMMY_STATEMENT_CONST(SecurityEventId);                                                                         /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
 * TcpIp_VRequestComModeInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_VRequestComModeInternal(
  uint8                               CtrlIdx,
  CONST(TcpIp_StateType, TCPIP_CONST) CtrlState)
{

  /* ----- Implementation ----------------------------------------------- */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  /* #10 Forward the request to the IpV4 layer. */
  IpV4_ComModeChgInternal(CtrlIdx, CtrlState);
#endif

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  /* #20 Forward the request to the IpV6 layer. */
  IpV6_ComModeChgInternal(CtrlIdx, CtrlState);
#endif

} /* TcpIp_VRequestComModeInternal() */

#if ((TCPIP_SUPPORT_DHCPV4 == STD_ON) || (TCPIP_SUPPORT_DHCPV6 == STD_ON))                                              /* COV_TCPIP_DHCPv6_SUPPORT_ALWAYS_OFF */
/**********************************************************************************************************************
 * TcpIp_VGetRandomValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint32, TCPIP_CODE) TcpIp_VGetRandomValue(
  uint32 MinValue,
  uint32 MaxValue)
{
  uint32 ValueRange;
  uint32 RndValue;

  /* #10 Generate random value */
  if (MinValue < MaxValue)
  {
    ValueRange = (MaxValue - MinValue) + 1u;

    if (ValueRange <= 0xFFFFU)
    {
      /* 16bit random number [0..0xFFFF] is sufficient */
      RndValue = (uint32)(TcpIp_GetRandomNumber());                                                                     /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
    }
    else
    {
      /* create 32bit random number [0..0xFFFFFFFF] by combining two 16bit random numbers */
      RndValue = (uint32)(((uint32)(TcpIp_GetRandomNumber()) << 16) | (uint32)(TcpIp_GetRandomNumber()));               /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */ /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
    }

    RndValue %= ValueRange;
  }
  else
  {
    RndValue = 0;
  }

  return MinValue + RndValue;

} /* End of TcpIp_VGetRandomValue() */
#endif

/**********************************************************************************************************************
 * TcpIp_LocalAddrIdxIsOnHold()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_LocalAddrIdxIsOnHold(
  TcpIp_LocalAddrIterType LocalAddrIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Test IPv4 addresse if given address is an IPv4 address and if this ctrl is in state OnHold. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
  if (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(LocalAddrIdx) == TRUE)
  {
    TcpIp_LocalAddrV4IterType localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LocalAddrIdx);
    TcpIp_IpV4CtrlDynIterType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);
    if (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) == IPV4_IP_ONHOLD)
    {
      retVal = TRUE;
    }
    else
    {
      retVal = FALSE;
    }
  }
#endif
  /* #20 Test IPv6 addresse if given address is an IPv6 address and if this ctrl is in state OnHold. */
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
  if (TCPIP_LOCAL_ADDR_IDX_IS_IPV6(LocalAddrIdx) == TRUE)
  {
    TcpIp_LocalAddrV6IterType localAddrV6Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV6(LocalAddrIdx);
    TcpIp_IpV6CtrlDynIterType ipV6CtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(localAddrV6Idx);
    if (TcpIp_GetCtrlStateOfIpV6CtrlDyn(ipV6CtrlIdx) == IPV6_CTRL_STATE_ONHOLD)
    {
      retVal = TRUE;
    }
    else
    {
      retVal = FALSE;
    }
  }
#endif
  return retVal;
} /* TcpIp_LocalAddrIdxIsOnHold */

/**********************************************************************************************************************
 * TcpIp_SocketIsOnHold()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_SocketIsOnHold(
  TcpIp_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify if the local addr of the socket is in state OnHold. */
  if (SocketId < TcpIp_GetSizeOfSocketDyn())
  {
    TcpIp_SocketDynIterType socketIdx = TCPIP_SOCKET_ID_TO_IDX(SocketId);
    TcpIp_LocalAddrIterType localAddrIdx = TcpIp_GetLocalAddrBindIdxOfSocketDyn(socketIdx);
    retVal = TcpIp_LocalAddrIdxIsOnHold(localAddrIdx);
  }
  return retVal;
} /* TcpIp_SocketIsOnHold */

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * TcpIp_GetBaseStateIpV6Ctrl()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_StateType, TCPIP_CODE) TcpIp_GetBaseStateIpV6Ctrl(
  TcpIp_StateType IpV6State)
{
  TcpIp_StateType retVal = TCPIP_STATE_OFFLINE;
  /* #10 Get the TcpIp_State that is related to the IPv6 ctrl state. */
  switch (IpV6State)
  {
  case IPV6_CTRL_STATE_UNINIT:
  case IPV6_CTRL_STATE_INIT:
  case IPV6_CTRL_STATE_LINK_READY:
    retVal = TCPIP_STATE_OFFLINE;
    break;
  case IPV6_CTRL_STATE_LLADDR_READY:
  case IPV6_CTRL_STATE_GBLADDR_READY:
    retVal = TCPIP_STATE_ONLINE;
    break;
  case IPV6_CTRL_STATE_ONHOLD:
    retVal = TCPIP_STATE_ONHOLD;
    break;
  default:                                                                                                              /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* ERROR: This state should not be reached. */
    TCPIP_ASSERT_UNREACHABLE();
    break;
  }
  return retVal;
}
# endif
#endif

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 * TcpIp_GetBaseStateIpV4Ctrl()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(TcpIp_StateType, TCPIP_CODE) TcpIp_GetBaseStateIpV4Ctrl(
  TcpIp_StateType IpV4State)
{
  TcpIp_StateType retVal = TCPIP_STATE_OFFLINE;
  /* #10 Get the TcpIp_State that is related to the IPv4 ctrl state. */
  switch (IpV4State)
  {
  case IPV4_IP_OFFLINE:
  case IPV4_IP_ONLINE_PASSIVE:
    retVal = TCPIP_STATE_OFFLINE;
    break;
  case IPV4_IP_ONLINE_ACTIVE:
    retVal = TCPIP_STATE_ONLINE;
    break;
  case IPV4_IP_ONHOLD:
    retVal = TCPIP_STATE_ONHOLD;
    break;
  default:                                                                                                              /* PRQA S 2016 3 */ /* MD_MSR_EmptyClause */
    /* ERROR: This state should not be reached. */
    TCPIP_ASSERT_UNREACHABLE();
    break;
  }
  return retVal;
}
# endif
#endif

/**********************************************************************************************************************
 * TcpIp_ChangeCtrlStateNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* PRQA S 6050 1 */ /* MD_TcpIp_STCAL_CslAccess */
FUNC(void, TCPIP_CODE) TcpIp_ChangeCtrlStateNotification(
  uint8 EthIfCtrlIdx,
  TcpIp_StateType TcpIpState)
{
  TcpIp_StateType nextState = TcpIpState;

#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
# if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                     /* COV_MSR_UNSUPPORTED */
  /* #10 For dual stack get the relevant state */
  if (   (TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE)
      && (TcpIp_IsIpV6CtrlUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE))
  {
    /* Get the TcpIp_State of the IPv4 and IPv6 ctrl. */
    TcpIp_StateType stateIpV6 = TcpIp_GetBaseStateIpV6Ctrl(TcpIp_GetCtrlStateOfIpV6CtrlDyn(TcpIp_GetIpV6CtrlIdxOfEthIfCtrl(EthIfCtrlIdx)));
    TcpIp_StateType stateIpV4 = TcpIp_GetBaseStateIpV4Ctrl(TcpIp_GetStateOfIpV4CtrlDyn(TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(EthIfCtrlIdx)));

    /* Select state with the highest priority (Online > OnHold > Offline) */
    if (stateIpV6 > stateIpV4)
    {
      nextState = stateIpV6;
    }
    else
    {
      nextState = stateIpV4;
    }
  }
# endif
#endif
  /* #20 If the state was updated, notify the EthSm */
  if (TcpIp_GetStateOfEthIfCtrlDyn(EthIfCtrlIdx) != nextState)
  {
    TcpIp_SetStateOfEthIfCtrlDyn(EthIfCtrlIdx, nextState);                                                              /* SBSW_TCPIP_CSL_IDX_FROM_CALLER */
    (void)ETHSM_TCPIP_MODE_INDICATION(EthIfCtrlIdx, nextState);
  }

}

#if (TCPIP_SUPPORT_TCP == STD_ON)
/**********************************************************************************************************************
 * TcpIp_SearchTcpListenSocket()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_SearchTcpListenSocket(
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  boolean                           AcceptAnyIp
)
{
  TcpIp_SocketDynIterType iterSocketIdx;
  TcpIp_SocketDynIterType matchSocketIdx = TcpIp_GetSizeOfSocketDyn();
  uint8 bestMatch = TCPIP_ADDR_MATCH_NONE;

  /* #10 Iterate over all listen TCP sockets and match IP address and Port information. */
  for (iterSocketIdx = TcpIp_GetSizeOfSocketUdpDyn(); iterSocketIdx < TcpIp_GetSizeOfSocketDyn(); iterSocketIdx++)
  {
    /* #20 Verify that socket is in state Listen. */
    if (TcpIp_GetListenActiveConnStatOfSocketDyn(iterSocketIdx) == TCPIP_SOCK_CONN_LISTEN_ENABLED)
    {
      /* #30 Verify the port. */
      TcpIp_SizeOfLocalAddrType localAddrBindIdx = TcpIp_GetLocalAddrBindIdxOfSocketDyn(iterSocketIdx);
      if (IpBase_SockPortIsEqual(&TcpIp_GetAddrLocSockOfSocketDyn(iterSocketIdx)->SockAddr, &RxSockLocAddrPtr->SockAddr) == TRUE)/* SBSW_TCPIP_SockPortIsEqual */
      {
        uint8 match;
        /* #40 Verify IP. */
        if (localAddrBindIdx == LocalAddrIdx)
        {
          /* #50 Exact match found. */
          matchSocketIdx = iterSocketIdx;

          /* No better match is possible, break loop. */
          break;
        }
        else if (   (TcpIp_VerifyAddrIdAcceptable(localAddrBindIdx, LocalAddrIdx, &match) == TRUE)                      /* SBSW_TCPIP_PtrToLocalVariable */
                 && (AcceptAnyIp == TRUE))
        {
          /* #60 AnyIP or Broadcast/AllNode match found. */
          if (match < bestMatch)
          {
            bestMatch = match;
            matchSocketIdx = iterSocketIdx;
          }
          /* Do not break, a better match is possible. */
        }
        else
        {
          /* Socket do not match. */
        }
      }
    }
  }
  return matchSocketIdx;
}

/**********************************************************************************************************************
 * TcpIp_SearchTcpComSocket()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(TcpIp_SocketDynIterType, TCPIP_CODE) TcpIp_SearchTcpComSocket(
  TcpIp_LocalAddrIterType           LocalAddrIdx,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockLocAddrPtr,
  TCPIP_P2C(TcpIp_SockAddrBaseType) RxSockRemAddrPtr
)
{
  TcpIp_SocketDynIterType iterSocketIdx;

  /* #10 Iterate over all TCP sockets and match IP address and Port information. */
  for (iterSocketIdx = TcpIp_GetSizeOfSocketUdpDyn(); iterSocketIdx < TcpIp_GetSizeOfSocketDyn(); iterSocketIdx++)
  {
    if (   (TcpIp_GetListenActiveConnStatOfSocketDyn(iterSocketIdx) == TCPIP_SOCK_CONN_LISTEN_ENABLED)
        || (TcpIp_GetListenActiveConnStatOfSocketDyn(iterSocketIdx) == TCPIP_SOCK_CONN_ACTIVE))
    {
      /* #20 Remote IP address and Port match. */
      if (TcpIp_VSockAddrIpAndPortIsEqual(TcpIp_GetAddrRemSockOfSocketDyn(iterSocketIdx), RxSockRemAddrPtr) == TRUE)    /* SBSW_TCPIP_VSockAddrIpAndPortIsEqual */
      {
        /* #30 Local Port match. */
        /* Do not also test for the IP of the socket, because for not connected socket that will be set later. */
        if(TcpIp_GetAddrLocSockOfSocketDyn(iterSocketIdx)->DomainAndPort.port == RxSockLocAddrPtr->DomainAndPort.port)
        {
          /* #40 Verify that local address (and indirect that VLAN) match. */
          if (TcpIp_GetLocalAddrBindIdxOfSocketDyn(iterSocketIdx) == LocalAddrIdx)
          {
            /* #50 Local Remote IP address, Port and VLAN fits. */
            break;
          }
        }
      }
    }
  }
  return iterSocketIdx;
}
#endif

/**********************************************************************************************************************
 * TcpIp_VerifyAddrIdAcceptable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_VerifyAddrIdAcceptable(
  TcpIp_LocalAddrIterType   BindLocalAddrIdx,
  TcpIp_LocalAddrIterType   RecvLocalAddrIdx,
  TCPIP_P2V(uint8)          MatchType)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for bound to ANY-IP. */
  if (BindLocalAddrIdx == TCPIP_LOCALADDRID_ANY)
  {
    *MatchType = TCPIP_ADDR_MATCH_ANYIP;                                                                                /* SBSW_TCPIP_NonNullPtrParameter */
    retVal = TRUE;
  }
  else
  {
    /* #20 Else check for IPv4 addresses. */
#if (TCPIP_SUPPORT_IPV4 == STD_ON)                                                                                      /* COV_TCPIP_IPV4_ALWAYS_ON */
    if (   (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(BindLocalAddrIdx) == TRUE)
        && (TCPIP_LOCAL_ADDR_IDX_IS_IPV4(RecvLocalAddrIdx) == TRUE))
    {
      retVal = IpV4_Ip_IsAddrIdxAcceptable(TCPIP_LOCAL_ADDR_IDX_TO_IPV4(BindLocalAddrIdx),
                                           TCPIP_LOCAL_ADDR_IDX_TO_IPV4(RecvLocalAddrIdx), MatchType);                  /* SBSW_TCPIP_NonNullPtrParameter */
    }
#endif

    /* #30 And check for IPv6 addresses. */
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    if (   (TCPIP_LOCAL_ADDR_IDX_IS_IPV6(BindLocalAddrIdx) == TRUE)
        && (TCPIP_LOCAL_ADDR_IDX_IS_IPV6(RecvLocalAddrIdx) == TRUE))
    {
      retVal = IpV6_IsAddrIdAcceptable(TCPIP_LOCAL_ADDR_IDX_TO_IPV6(BindLocalAddrIdx),
                                       TCPIP_LOCAL_ADDR_IDX_TO_IPV6(RecvLocalAddrIdx), MatchType);                      /* SBSW_TCPIP_NonNullPtrParameter */
    }
#endif
  }
  return retVal;
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"                                                                                               /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

   MD_TCPIP_Rule8.9_1514_1533: An object should be defined at block scope if its identifier only appears in a single function
   Reason:     Some objects are defined keeping in mind future modifications and usage
   Risk:       None.
   Prevention: Covered by code review.
 */

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_TcpIdxFromValidSocketIdx
    \DESCRIPTION       Access of SocketTcp(Dyn)[] array using TCP socket index which is derived from generic (UDP/TCP) socket index using the
                       macro TCPIP_SOCKET_IDX_TO_TCP_IDX(SocketIdx). -> SocketTcpIdx == SocketIdx - TcpIp_GetSizeOfSocketUdpDyn().
                       1: The caller ensures that SocketIdx is valid (SocketIdx < TcpIp_GetSizeOfSocketDyn())
                       2: TcpIp_GetSizeOfSocketDyn() = TcpIp_GetSizeOfSocketUdpDyn() + TcpIp_GetSizeOfSocketTcpDyn()
                       3: SocketIdx is checked to be a TCP socket: TCPIP_SOCKET_IDX_IS_TCP(SocketIdx) -> SocketIdx >= TcpIp_GetSizeOfSocketUdpDyn()
    \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_ipVXPseudoHdrArray
    \DESCRIPTION       Access/usage of uint8 array on the stack that has a fixed size.
                       A pointer to the array is passed to subfunctions or elements are accessed by an index.
    \COUNTERMEASURE \N All index and length values are constants that do not exceed the array size.

  \ID SBSW_TCPIP_PointerCombinationSizeof
    \DESCRIPTION       A pointer to a variable as well as the length are passed to a subfunction.
    \COUNTERMEASURE \N The length/size of the variable is calculated via the sizeof() opertor and always matches the variable size.

  \ID SBSW_TCPIP_ChgFuncPtrOfPhysAddrConfig
    \DESCRIPTION       1: A function pointer is called.
                          The function pointer is read from a ComStackLib array using TcpIp_GetChgFuncPtrOfPhysAddrConfig(physAddrConfigIdx).
                          Variable physAddrConfigIdx is always in range [0..TcpIp_GetSizeOfPhysAddrConfig()-1].
                          The generator ensures that the pointer is valid or NULL_PTR if no callback is configured.
                          A check for funcPtr != NULL_PTR ensures that the function is only called if configured.
                       2: Arguments IpAddrPtr and PhysAddrPtr are derived from unmodified pointer parameters.
    \COUNTERMEASURE \N 1: Qualified use-case CSL01 of ComStackLib.
                       2: The caller ensures that all pointer parameters are valid.

  \ID SBSW_TCPIP_SocketOwnerFuncPtr
    \DESCRIPTION       A function pointer is called that is retrieved from the configuration via TcpIp_Get*FuncPtrOfSocketOwnerConfig(socketOwnerCfgIdx).
                       The generator ensures that the pointer references a valid function or is NULL_PTR.
                       The pointers passed to the called function are not modified.
    \COUNTERMEASURE \R A runtime check ensures that socketOwnerCfgIdx is in valid range by using the TcpIp_GetSizeOf...() function.
                       -> Qualified use-case CSL01 of ComStackLib
                       A check against funcPtr != NULL_PTR ensures that the function is only called if configured.
                       The caller ensures that all pointer parameters are valid.

  \ID SBSW_TCPIP_SocketOwnerFuncPtr_2
    \DESCRIPTION       A function pointer is called that is retrieved from the configuration via TcpIp_Get*FuncPtrOfSocketOwnerConfig(SocketOwnerCfgIdx).
                       The generator ensures that the pointer references a valid function or is NULL_PTR.
                       The pointers passed to the called function are not modified.

    \COUNTERMEASURE \R The caller ensures that SocketOwnerCfgIdx is in valid range by using the TcpIp_GetSizeOf...() function.
                       -> Qualified use-case CSL01 of ComStackLib
                       A check against funcPtr != NULL_PTR ensures that the function is only called if configured.
                       The caller ensures that all pointer parameters are valid.

  \ID SBSW_TCPIP_DList_NodeArrayIdx
    \DESCRIPTION       An index parameter is used to access a DList nodes array (NodeSetPtr).
    \COUNTERMEASURE \N The caller ensures that the node index is inside the bounds of the array referenced by NodeSetPtr.

  \ID SBSW_TCPIP_DList_NodeArrayOrEndIdx
    \DESCRIPTION       An index parameter is used to access a DList nodes array (NodeSetPtr).
                       The index parameter may have the special value TCPIP_DLIST_END_IDX.
    \COUNTERMEASURE \R The caller ensures that the node index is inside the bounds of the array referenced by NodeSetPtr or has the value TCPIP_DLIST_END_IDX.
                       A runtime check ensures that the index is only used if it is valid.

  \ID SBSW_TCPIP_DList_PrevOrNextIdx
    \DESCRIPTION       An index read from an existing list node is used to access a DList nodes array (NodeSetPtr).
                       The index references the valid predecessor/successor of a node or is TCPIP_DLIST_END_IDX if this is the first/last node.
    \COUNTERMEASURE \R A runtime check ensures that the index is only used if it is valid.

  \ID SBSW_TCPIP_DList_NodeArrayIdx_Iterate
    \DESCRIPTION       An index parameter is used to access a DList nodes array (NodeSetPtr).
                       The index value is updated by the index of the predecessor/successor during iteration.
    \COUNTERMEASURE \N The caller ensures that the node index is inside the bounds of the array referenced by NodeSetPtr.

  \ID SBSW_TCPIP_DList_InitDesc
    \DESCRIPTION       Iteration over array referenced by parameter NodePtr from 0 to NodeCount-1.
    \COUNTERMEASURE \N The caller ensures that the parameter NodePtr points to an array of size NodeCount.

  \ID SBSW_TCPIP_counterVarPtr
    \DESCRIPTION       Write access to a pointer which references a global variable.
    \COUNTERMEASURE \N The pointer always points to valid global variable TcpIp_Tcp_DynamicPortCount or TcpIp_Udp_DynamicPortCount.

  \ID SBSW_TCPIP_DListRawFunctionCall
    \DESCRIPTION       Helper function TcpIp_DListRaw*() is called in order to manipulate a linked list.
                       The pointers are all derived from a DList instance that was initialized by TcpIp_DListInit() and
                       only modified by one of the following functions which preserve integrity of the list:
                       - TcpIp_DListAddElement
                       - TcpIp_DListRemoveElement
                       - TcpIp_DListRemoveElementRange
                       - TcpIp_DListClear
    \COUNTERMEASURE \N The caller ensures that DListPtr references an initialized list which references an
                       initialized list descriptor.

  \ID SBSW_TCPIP_SockPortIsEqual
    \DESCRIPTION       1: Argument &TcpIp_GetAddrLocSockOfSocketDyn(SocketIdx) references element at SocketIdx in a ComStackLib array.
                       2: Argument &RxSockLocAddrPtr->SockAddr is derived from an unmodified pointer parameter.
    \COUNTERMEASURE \N 1: The caller ensures that SocketIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                          Qualified use-case CSL01 of ComStackLib.
                       2: The caller ensures that RxSockLocAddrPtr points to valid data.

  \ID SBSW_TCPIP_VSockAddrIpAndPortIsEqual
    \DESCRIPTION       1: Argument TcpIp_GetAddrLocSockOfSocketDyn(iterSocketIdx) references element at index socketIterIdx in a ComStackLib array.
                       2: Parameter RxSock*AddrPtr is passed unmodified to subroutine.
    \COUNTERMEASURE \R 1: A runtime check ensures socketIterIdx < TcpIp_GetSizeOfSocketDyn().
                          Qualified use-case CSL01 of ComStackLib.
                       2: The caller ensures that RxSock*AddrPtr points to valid data.

  \ID SBSW_TCPIP_tcpTxBufferDescIdx
    \DESCRIPTION       ComStackLib array TcpTxBufferDescDyn is accessed with index tcpTxBufferDescIdx.
                       Value of tcpTxBufferDescIdx is retrieved by TcpIp_GetTcpTxBufferDescIdxOfSocketTcpDyn(socketTcpIdx).
                       Value of socketTcpIdx is derived from valid SocketIdx only if the socket references a TCP socket.
    \COUNTERMEASURE \N The caller ensures that SocketIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_TcpAcceptedFunctions
    \DESCRIPTION       Argumment &TcpIp_GetAddrRemSockOfSocketDyn(socketIdx)->TcpIpSockAddr points to element at index
                       socketIdx in a ComStackLib array.
                       The value of socketIdx is derived from the parameter SocketTcpIdx via the macro TCPIP_TCP_IDX_TO_SOCKET_IDX.
    \COUNTERMEASURE \N The caller ensures that SocketIdx is within the valid range by using the TcpIp_GetSizeOf...() function.
                       Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_TCPIP_VSockIpAddrIsEqual
    \DESCRIPTION       1: Argument TcpIp_GetAddrLocSockOfSocketDyn(socketIdx) points to element at index socketIdx
                          in a ComStackLib array.
                          The value socketIdx is updated in a loop and checked to be < TcpIp_GetSizeOfSocketDyn().
                       2: Argument &sockAddr points to a local (stack) variable.
    \COUNTERMEASURE \N 1: Qualified use-case CSL01 of ComStackLib.
                       2: The pointer points to valid memory (stack).


   SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Priv.c
 *********************************************************************************************************************/
