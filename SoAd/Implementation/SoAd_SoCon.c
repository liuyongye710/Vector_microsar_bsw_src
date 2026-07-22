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
/*!        \file  SoAd_SoCon.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component SoCon.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_SO_CON_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"
#include "SoAd_TimeoutList.h"
#include "SoAd_Util.h"
#include "SoAd_SoCon.h"
#include "SoAd_Tx.h"
#include "SoAd_Rx.h"
#include "SoAd_Anomaly.h"
#include "SoAd_GenTcpIpApi.h"
#include "SoAd_State_Int.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
#include "IpBase.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  SoAd_SoCon_UdpChangeParameter()
 *********************************************************************************************************************/
/*! \brief      Changes parameters on a UDP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdHandleSockets, DSGN-SoAdUdpRetry
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_UdpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterNoDelay()
 *********************************************************************************************************************/
/*! \brief      Changes no delay (Nagle algorithm) parameter on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted or not required.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterNoDelay(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterKeepAlive()
 *********************************************************************************************************************/
/*! \brief      Changes keep alive parameters on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change requests were accepted or not required.
 *  \return     E_NOT_OK        Parameter change requests were not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterKeepAlive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterTls()
 *********************************************************************************************************************/
/*! \brief      Changes TLS parameter on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted or not required.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterTls(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterMsl()
 *********************************************************************************************************************/
/*! \brief      Changes MSL parameter on a TCP socket via the Socket API.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \return     E_OK            Parameter change request was accepted or not required.
 *  \return     E_NOT_OK        Parameter change request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterMsl(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId);

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedCheckAcceptance()
 *********************************************************************************************************************/
/*! \brief      Checks connection acceptance on a socket connection on connection establishment on listen socket.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx        Partition index.
 *                                  [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketIdConnected   Connected socket identifier.
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Socket connection accepted connection establishment.
 *  \return     E_NOT_OK            Socket connection rejected connection establishment.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedCheckAcceptance(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr);

#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpClose()
 *********************************************************************************************************************/
/*! \brief      Handles UDP close event on socket.
 *  \details    -
 *  \param[in]  SockIdx      Module internal socket index.
 *                           [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx Partition index.
 *                           [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpClose(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpCloseAllSoCons()
 *********************************************************************************************************************/
/*! \brief      Closes all related socket connections on UDP close event on socket.
 *  \details    -
 *  \param[in]  SockIdx      Module internal socket index.
 *                           [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx Partition index.
 *                           [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpCloseAllSoCons(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpClose()
 *********************************************************************************************************************/
/*! \brief      Handles TCP close and reset event on socket.
 *  \details    -
 *  \param[in]  SockIdx      Module internal socket index.
 *                           [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx Partition index.
 *                           [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpClose(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpFinReceived()
 *********************************************************************************************************************/
/*! \brief      Handles TCP FIN received event on socket.
 *  \details    -
 *  \param[in]  SockIdx      Module internal socket index.
 *                           [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx Partition index.
 *                           [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket indexes, FALSE for same socket index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpFinReceived(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckStates()
 *********************************************************************************************************************/
/*! \brief      Checks socket connection state to indicate if remote address is allowed to be set.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK            States on socket connection allow to set remote address.
 *  \return     E_NOT_OK        States on socket connection do not allow to set remote address.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckStates(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckTxRxStates()
 *********************************************************************************************************************/
/*! \brief      Checks socket connection transmission and reception states to indicate if remote address is allowed to
 *              be set.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK            States on socket connection allow to set remote address.
 *  \return     E_NOT_OK        States on socket connection do not allow to set remote address.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckTxRxStates(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckAndSet()
 *********************************************************************************************************************/
/*! \brief      Checks a remote address and set it on a socket connection if remote address is valid.
 *  \details    Compares remote address to be set with all related local addresses and overwrites current remote
 *              address if remote address to be set is different to the local addresses.
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  RemoteAddrPtr   Pointer to remote address.
 *                              [Points to one of the following structs depending on configured IP address version
 *                              of parameter SoConIdx:
 *                                - SoAd_SockAddrInetType for IPv4
 *                                - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK            Remote address is valid and set.
 *  \return     E_NOT_OK        Remote address is not valid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckAndSet(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_ReconnectOnRemoteAddrChg()
 *********************************************************************************************************************/
/*! \brief      Checks if a change of the socket connection mode is required after (re)setting the remote address and
 *              sets the new state. The user is notified about the socket connection mode change.
 *  \details    Check if socket connection is online and shall be set to reconnect since the newly set remote address
 *              has wildcards. The state is set accordingly and the user is notified about the socket connection mode
 *              change.
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  AddEventOnChg   Flag to indicate if an event has to be added for further handling of the socket
 *                              connection after setting a remote address without wildcards.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ReconnectOnRemoteAddrChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean AddEventOnChg);

/**********************************************************************************************************************
 *  SoAd_SoCon_CompareToIpAddr()
 *********************************************************************************************************************/
/*! \brief        Compares an IP address to all local IP addresses on an IP controller/interface.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    PartitionIdx    Partition index.
 *                                [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]    IpAddrPtr       Pointer to IP address.
 *  \return       E_OK            IP address matches one of the local IP addresses.
 *  \return       E_NOT_OK        IP address does not match one of the local IP addresses.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different local IP addresses, FALSE for same local IP address.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CompareToIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrConstPtrType IpAddrPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrTcp()
 *********************************************************************************************************************/
/*! \brief      Sets the remote address on a TCP socket connection if setting unique remote address is used.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx        Partition index.
 *                                  [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Request was accepted.
 *  \return     E_NOT_OK            Request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrUdp()
 *********************************************************************************************************************/
/*! \brief      Sets the remote address on a UDP socket connection if setting unique remote address is used.
 *  \details    -
 *  \param[in]  SoConIdx            Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx        Partition index.
 *                                  [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  RemoteAddrPtr       Pointer to remote address.
 *                                  [Points to one of the following structs depending on configured IP address version
 *                                  of parameter SoConIdx:
 *                                    - SoAd_SockAddrInetType for IPv4
 *                                    - SoAd_SockAddrInet6Type for IPv6]
 *  \return     E_OK                Request was accepted.
 *  \return     E_NOT_OK            Request was not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpen()
 *********************************************************************************************************************/
/*! \brief      Performs open actions to open a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdAutomaticOpenAndClose, DSGN-SoAdOpenOnReception
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpenSocketForOpenOnReception()
 *********************************************************************************************************************/
/*! \brief      Performs open actions for a UDP socket to support socket connection open on reception.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_Open()
 *********************************************************************************************************************/
/*! \brief      Opens a socket connection and the related socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdHandleSockets
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Open(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK            Socket is opened or already assigned.
 *  \return     E_NOT_OK        Socket is not opened.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_AssignSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Assigns a socket for a UDP socket connection and updates the state.
 *  \details    -
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is opened or already assigned.
 *  \return     E_NOT_OK        Socket is not opened.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_AssignSocketUdp(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConUdp()
 *********************************************************************************************************************/
/*! \brief      Opens UDP socket connection if a socket is already assigned.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClient()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a TCP client socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned or is already connecting.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClient(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientGetAndConnect()
 *********************************************************************************************************************/
/*! \brief      Gets a socket for a TCP client socket connection and starts connecting to remote entity.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientGetAndConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType SockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientConnect()
 *********************************************************************************************************************/
/*! \brief      Starts connecting to remote entity on a socket for a TCP client socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SockIdx         Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is assigned and connects to remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServer()
 *********************************************************************************************************************/
/*! \brief      Opens a socket for a TCP server socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketTcpUsedOfSoConGrp(),
 *                              !SoAd_IsTcpInitiateOfSocketTcp()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned or is already listening.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServer(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerGetAndListen()
 *********************************************************************************************************************/
/*! \brief      Gets a socket for a TCP server socket connection and starts listening for connection attempts.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  ListenSockIdx   Module internal socket index of listen socket.
 *                              [range: ListenSockIdx < SoAd_GetSizeOfSocket()]
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerGetAndListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType ListenSockIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerListen()
 *********************************************************************************************************************/
/*! \brief      Starts listening for connection attempts on a socket for a TCP server.
 *  \details    -
 *  \param[in]  ListenSockIdx   Module internal socket index of listen socket.
 *                              [range: ListenSockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SocketId        Socket identifier.
 *  \param[in]  LocalPort       Local port.
 *  \return     E_OK            Socket is assigned and listens for connection attempts from remote entity.
 *  \return     E_NOT_OK        Socket is not assigned.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerListen(
  SoAd_SizeOfSocketType ListenSockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort);

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConTcp()
 *********************************************************************************************************************/
/*! \brief      Opens TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Close()
 *********************************************************************************************************************/
/*! \brief      Closes a socket connection and the related sockets.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Close(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSoCon()
 *********************************************************************************************************************/
/*! \brief      Closes a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocket()
 *********************************************************************************************************************/
/*! \brief      Closes socket connection related sockets.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  Abort           Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcp()
 *********************************************************************************************************************/
/*! \brief      Closes TCP socket connection related socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  Abort           Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcpListen()
 *********************************************************************************************************************/
/*! \brief      Closes TCP socket connection related listen socket if no other socket connection requires the socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  Abort           Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_TCP
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketUdp()
 *********************************************************************************************************************/
/*! \brief      Closes UDP socket connection related socket if no other socket connection requires the socket.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  Abort           Flag to close socket connection immediately.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetCloseMode()
 *********************************************************************************************************************/
/*! \brief        Resets close mode considering socket connection and socket states.
 *  \details      -
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    PartitionIdx    Partition index.
 *                                [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetCloseMode(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifySoConModeChg()
 *********************************************************************************************************************/
/*! \brief      Notifies users about a socket connection mode change.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  Mode            Socket connection mode.
 *                              [range: SOAD_SOCON_ONLINE, SOAD_SOCON_RECONNECT, SOAD_SOCON_OFFLINE]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdNotifySocketConnectionStateChange
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifySoConModeChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SoConModeType Mode);

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifyLocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*! \brief      Notifies users about a socket connection local IP address assignment change.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  State           State of IP address assignment.
 *                              [range: SOAD_IPADDR_STATE_ASSIGNED, SOAD_IPADDR_STATE_ONHOLD, SOAD_IPADDR_STATE_UNASSIGNED]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \trace      DSGN-SoAdNotifyLocalIpAddressAssignmentStateChange
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrStateType State);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetLocalPortDyn()
 *********************************************************************************************************************/
/*! \brief        Resets local port of a socket.
 *  \details      Considers that a local port is shared by multiple sockets/socket connections.
 *  \param[in]    SockIdx       Module internal socket index.
 *                              [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ResetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetSoCon()
 *********************************************************************************************************************/
/*! \brief      Resets socket connection specific properties.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  ResetRemAddr  Indicates if remote address shall be reset.
 *  \param[in]  ResetOpClSeq  Indicates if open/close sequence shall be reset.
 *  \param[in]  NormalClose   Indicates if socket connection is closed by normal close request.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean ResetRemAddr,
  boolean ResetOpClSeq,
  boolean NormalClose);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAndRcvRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets remote address and received remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAndRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \trace      DSGN-SoAdHandleRemoteAddressState
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetConfiguredRemAddr()
 *********************************************************************************************************************/
/*! \brief      Gets the configured remote address dependent of the domain type.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[out] RemAddrPtr    Pointer for storing of the configured remote address.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_GetConfiguredRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrInetXType, AUTOMATIC, SOAD_APPL_DATA) RemAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRcvRemAddr()
 *********************************************************************************************************************/
/*! \brief      Resets received remote address on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleReleaseRemAddr()
 *********************************************************************************************************************/
/*! \brief      Handles requests for the release of the remote address in main function context.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx  Partition index.
 *                            [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_HandleReleaseRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_TriggerAddressResolution()
 *********************************************************************************************************************/
/*! \brief        Triggers address resolution for a remote address on a socket connection (ARP/NDP).
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    PartitionIdx  Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_TriggerAddressResolution(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckForActiveOrPendingTransmit()
 *********************************************************************************************************************/
/*! \brief      Indicates if a transmission is active or pending on a socket connection.
 *  \details    Transmission of an nPdu can optionally be triggered immediately on call of this function to speed up
 *              the transmission.
 *  \param[in]  SoConIdx             Socket connection index.
 *                                   [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx         Partition index.
 *                                   [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  TransmitImmediately  Flag to indicate if transmission of nPdu shall be triggered immediately.
 *  \return     TRUE                 Transmission is active.
 *  \return     FALSE                No transmission is active.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_CheckForActiveOrPendingTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean TransmitImmediately);

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxRouteGrpActive()
 *********************************************************************************************************************/
/*! \brief      Indicates if a routing group transmission is active on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \return     TRUE            Transmission is active.
 *  \return     FALSE           No transmission is active.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxRouteGrpActive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdx()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PartitionIdx          Partition index.
 *                                    [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *                                    [Points to one of the following structs depending on configured IP address
 *                                    version of parameter SoConIdx:
 *                                      - SoAd_SockAddrInetType for IPv4
 *                                      - SoAd_SockAddrInet6Type for IPv6]
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);

#if ( SOAD_IPV6 == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection of type IPv6.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                                    SoAd_GetDomainOfLocalAddr() == SOAD_AF_INET6]
 *  \param[in]  PartitionIdx          Partition index.
 *                                    [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *  \config     SOAD_IPV6
 *********************************************************************************************************************/
/* PRQA S 779 3 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);
#endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4()
 *********************************************************************************************************************/
/*! \brief      Returns the best match algorithm priority of a socket connection of type IPv4.
 *  \details    -
 *  \param[in]  SoConIdx              Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                                    SoAd_GetDomainOfLocalAddr() == SOAD_AF_INET]
 *  \param[in]  PartitionIdx          Partition index.
 *                                    [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \param[in]  SockAddrPtr           Pointer to socket address used to perform best match algorithm.
 *  \return     Priority              Best match algorithm priority of socket connection.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
/* PRQA S 779 3 */ /* MD_MSR_Rule5.2 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrInetType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr);

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief      Sets the UDP alive supervision timeout on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketUdpUsedOfSoConGrp()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_SetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetUdpAliveTimeout()
 *********************************************************************************************************************/
/*! \brief      Resets the UDP alive supervision timeout on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon(),
 *                              SoAd_IsSocketUdpUsedOfSoConGrp()]
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  SoAd_SoCon_DecrementOpenSockets()
 *********************************************************************************************************************/
/*! \brief      Decrements the number of open sockets.
 *  \details    -
 *  \param[in]  InstanceIdx     Instance index.
 *  \param[in]  PartitionIdx    Partition index.
 *                              [range: PartitionIdx < size of SoAd_PCPartitionConfig]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_DecrementOpenSockets(
  SoAd_SizeOfInstanceType InstanceIdx,
  SoAd_PartitionConfigIdxType PartitionIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_SoCon_UdpChangeParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_UdpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType  soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType           retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set frame priority. */
  if ( SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx, PartitionIdx) != SOAD_NO_FRAMEPRIORITYOFSOCONGRP )
  {
    uint8 framePriority = SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx, PartitionIdx);

    retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_FRAMEPRIO, &framePriority);                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #20 Set UDP Tx request list size. */
  if ( SoAd_IsImmedIfTxConfOfSocketUdp(socketUdpIdx, PartitionIdx) )
  {
    uint8 udpTxReqListSize = SoAd_GetImmedIfTxConfListSizeOfSocketUdp(socketUdpIdx, PartitionIdx);

    retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_UDP_TXREQLISTSIZE, &udpTxReqListSize);               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #30 Set UDP Tx retry list size (number of Eth Tx buffers used in case of physical address miss). */
  if ( SoAd_IsRetryEnabledOfTcpIpCtrl(SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx, PartitionIdx), PartitionIdx) )
  {
    uint8 udpTxRetryListSize = SoAd_GetRetryQueueLimitOfSocketUdp(socketUdpIdx, PartitionIdx);

    retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_UDP_TXRETRYLISTSIZE, &udpTxRetryListSize);           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #40 Enable/Disable UDP checksum if UDP checksum shall be changed for the socket. */
  if ( SoAd_IsChecksumChangeEnabledOfSocketUdp(socketUdpIdx, PartitionIdx) )
  {
    boolean checksumEnabled = (boolean)SoAd_IsChecksumEnabledOfSocketUdp(socketUdpIdx, PartitionIdx);

    retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_UDP_CHECKSUM, SOAD_A_P2VAR(uint8)&checksumEnabled);  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_SoCon_UdpChangeParameter() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterNoDelay()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterNoDelay(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch ( SoAd_GetTcpNoDelayOfSocketTcp(socketTcpIdx, PartitionIdx) )
  {
    /* #10 Change parameter if no delay (Nagle algorithm) is enabled. */
    case SOAD_TCP_NO_DELAY_ENABLED:
    {
      uint8 value = 0x00u;

      retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_NAGLE, &value);                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
    /* #20 Change parameter if no delay (Nagle algorithm) is disabled. */
    case SOAD_TCP_NO_DELAY_DISABLED:
    {
      uint8 value = 0x01u;

      retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_NAGLE, &value);                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
    /* #30 Do not change parameter if no delay (Nagle algorithm) is not configured. */
    default:
    { /* SOAD_TCP_NO_DELAY_NOT_SPECIFIED */
      /* nothing to do */
      break;
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterNoDelay() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterKeepAlive()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterKeepAlive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if keep alive is enabled globally. */
  if ( SoAd_IsTcpKeepAliveGloballyEnabled(0u) )
  {
    boolean tcpKeepAlive = (boolean)SoAd_IsTcpKeepAliveOfSocketTcp(socketTcpIdx, PartitionIdx);

    /* #100 Enable/Disable keep alive. */
    retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_KEEPALIVE,                                        /* SBSW_SOAD_CAST_POINTER_FORWARD */
      SOAD_A_P2VAR(uint8)&tcpKeepAlive);

    /* #101 Check if keep alive could be set. */
    if ( (retVal == E_OK) && (tcpKeepAlive == TRUE) )
    {
      uint32 tcpKeepAliveTime = SoAd_GetTcpKeepAliveTimeOfSocketTcp(socketTcpIdx, PartitionIdx);
      uint32 tcpKeepAliveInterval = SoAd_GetTcpKeepAliveIntervalOfSocketTcp(socketTcpIdx, PartitionIdx);
      uint16 tcpKeepAliveProbesMax = SoAd_GetTcpKeepAliveProbesMaxOfSocketTcp(socketTcpIdx, PartitionIdx);

      /* #1010 Set keep alive time. */
      if ( tcpKeepAliveTime != SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP )
      {
        retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_KEEPALIVE_TIME,                               /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveTime); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
      /* #1011 Set keep alive maximum probes. */
      if ( tcpKeepAliveProbesMax != SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP )
      {
        retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_KEEPALIVE_PROBES_MAX,                        /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveProbesMax); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
      /* #1012 Set keep alive interval. */
      if ( tcpKeepAliveInterval != SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP )
      {
        retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_KEEPALIVE_INTERVAL,                          /* SBSW_SOAD_CAST_POINTER_FORWARD */
          SOAD_A_P2VAR(uint8)&tcpKeepAliveInterval); /* PRQA S 310 */ /* MD_SoAd_PointerCastOnParam */
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterKeepAlive() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterTls()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterTls(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx,
    PartitionIdx), PartitionIdx);
  uint16                    tcpTlsConId = SoAd_GetTcpTlsConIdOfSocketTcp(socketTcpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection references a TLS connection. */
  if ( tcpTlsConId != SOAD_NO_TCPTLSCONIDOFSOCKETTCP )
  {
    /* #100 Set TLS connection identifer. */
    retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TLS_CONNECTION_ASSIGNMENT, (uint8*)&tcpTlsConId);     /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterTls() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameterMsl()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameterMsl(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx,
    PartitionIdx), PartitionIdx);
  uint32                    tcpMslValue = SoAd_GetTcpMslOfSocketTcp(socketTcpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket uses a specific MSL value. */
  if ( tcpMslValue != SOAD_NO_TCPMSLOFSOCKETTCP )
  {
    /* #100 Set MSL value. */
    retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_MSL, (uint8*)&tcpMslValue);                       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_SoCon_TcpChangeParameterMsl() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedCheckAcceptance()
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
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedCheckAcceptance(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType   sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket connection related socket state is closed. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    retVal = E_OK;

    /* #200 Assign socket identifier to module internal socket index. */
    SoAd_SetSocketIdOfSocketDyn(sockIdx, SocketIdConnected, PartitionIdx);                                             /* SBSW_SOAD_CSL02_CSL05 */

    /* #201 Update remote address on socket connection. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx),    /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
      RemoteAddrPtr);
    SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SOAD_SOCON_IP_SET_PORT_SET, PartitionIdx);                             /* SBSW_SOAD_PARAMETER_IDX */

    /* #202 Set socket and socket connection state. */
    SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_ESTABLISHED, PartitionIdx);                                      /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_Util_FetchAddU32(SoAd_GetAddrOpenSocksOfInstanceDyn(instanceIdx, PartitionIdx), SOAD_INC_DEC_BY_ONE);         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE, PartitionIdx);                                                 /* SBSW_SOAD_PARAMETER_IDX */

    /* #203 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #204 Notify user about state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));

    /* #205 Check if socket connection has a SocketRoute. */
    if ( SoAd_GetSocketRouteStartIdxOfSoCon(SoConIdx, PartitionIdx) != SoAd_GetSocketRouteEndIdxOfSoCon(SoConIdx,
        PartitionIdx) )
    {
      /* #2050 Try to start TP reception if required. */
      if ( SoAd_Rx_TpStartOfReception(SoConIdx, PartitionIdx) == E_NOT_OK )
      {
        retVal = E_NOT_OK;
      }
    }
  }
  /* #21 Otherwise leave critical section. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_TcpAcceptedCheckAcceptance() */

#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpClose()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpClose(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent inconsistencies in socket and socket connection states. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Reset map of module internal socket index to socket identifier. */
  SoAd_SetSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */

  /* #30 Check if socket is not yet in closed state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #40 Decrement number of open sockets. */
    SoAd_SoCon_DecrementOpenSockets(instanceIdx, PartitionIdx);

    /* #50 Set socket state. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSED, PartitionIdx);                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #60 Reset map of module internal socket index to active transmitting socket connection. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSoCon(PartitionIdx), PartitionIdx);                     /* SBSW_SOAD_PARAMETER_IDX */

    /* #70 Reset local port to the configured value. */
    SoAd_SoCon_ResetLocalPortDyn(SockIdx, PartitionIdx);

    /* #80 Close all related socket connections. */
    SoAd_SoCon_EventUdpCloseAllSoCons(SockIdx, PartitionIdx);
  }

  /* #90 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_EventUdpClose() */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventUdpCloseAllSoCons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventUdpCloseAllSoCons(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType      soConIter;
  SoAd_SizeOfSoConGrpType soConGrpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all related socket connection to close them. */
  for ( soConIter = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
    soConIter < SoAd_GetSoConEndIdxOfSocket(SockIdx, PartitionIdx);
    soConIter++ )
  {
    /* #20 Check if socket connection is not closed. */
    if ( SoAd_GetModeOfSoConDyn(soConIter, PartitionIdx) != SOAD_SOCON_OFFLINE )
    {
      /* #30 Set close mode to indicate that socket is closed. */
      SoAd_SoCon_SetCloseMode((SoAd_SizeOfSoConType)soConIter, PartitionIdx, SOAD_CLOSE_SOCKET);

      /* #40 Set event to handle socket connection state in main function. */
      soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIter, PartitionIdx);
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, (SoAd_SizeOfSoConType)soConIter,
        SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
    }
  }
} /* SoAd_SoCon_EventUdpCloseAllSoCons() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpClose()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpClose(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent inconsistencies in socket and socket connection states. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Reset map of module internal socket index to socket identifier. */
  SoAd_SetSocketIdOfSocketDyn(SockIdx, SOAD_INV_SOCKET_ID, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */

  /* #30 Check if socket is not yet in closed state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #40 Decrement number of open sockets. */
    SoAd_SoCon_DecrementOpenSockets(instanceIdx, PartitionIdx);

    /* #50 Set socket state. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSED, PartitionIdx);                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #60 Reset map of module internal socket index to active transmitting socket connection. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(SockIdx, SoAd_GetSizeOfSoCon(PartitionIdx), PartitionIdx);                     /* SBSW_SOAD_PARAMETER_IDX */

    /* #70 Reset local port to the configured value. */
    SoAd_SoCon_ResetLocalPortDyn(SockIdx, PartitionIdx);

    /* #80 Check if socket is no listen socket. */
    if ( SockIdx != SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx) )
    {
      /* #800 Set close mode to indicate that socket is closing and shall be reconnected in case of client socket. */
      if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
      {
        SoAd_SoCon_SetCloseMode(soConIdx, PartitionIdx, SOAD_CLOSE_SOCKET_RECONNECT);
      }
      /* #801 Set close mode to indicate that socket is closing otherwise. */
      else
      {
        SoAd_SoCon_SetCloseMode(soConIdx, PartitionIdx, SOAD_CLOSE_SOCKET);
      }

      /* #802 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx, instanceIdx, PartitionIdx);
    }
    /* #81 Set event to handle state in main function for all socket connections related to listen socket otherwise. */
    else
    {
      SoAd_SoConIterType soConIter;

      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(SockIdx, PartitionIdx);
        soConIter++ )
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, (SoAd_SizeOfSoConType)soConIter, instanceIdx,
          PartitionIdx);
      }
    }
  }

  /* #90 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_EventTcpClose() */

/**********************************************************************************************************************
 *  SoAd_SoCon_EventTcpFinReceived()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_EventTcpFinReceived(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx);
  SoAd_SocketIdType       socketId = SoAd_GetSocketIdOfSocketDyn(SockIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to check socket identifier validity and the socket state. */
  SOAD_BEGIN_CRITICAL_SECTION();

  if ( SoAd_GetStateOfSocketDyn(SockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Set close mode to indicate that socket is closing and shall be reconnected in case of client socket. */
    if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
    {
      SoAd_SoCon_SetCloseMode(soConIdx, PartitionIdx, SOAD_CLOSE_SOCKET_RECONNECT);
    }
    /* #21 Set close mode to indicate that socket is closing otherwise. */
    else
    {
      SoAd_SoCon_SetCloseMode(soConIdx, PartitionIdx, SOAD_CLOSE_SOCKET);
    }

    /* #30 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx, SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx,
        PartitionIdx), PartitionIdx);

    /* #40 Set socket to closing. */
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CLOSING, PartitionIdx);                                          /* SBSW_SOAD_PARAMETER_IDX */

    /* #50 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #60 Close socket.*/
    (void)SoAd_TcpIpApiClose(socketId, FALSE);
  }
  else
  {
    /* #70 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_EventTcpFinReceived() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckStates(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is not offline in case of TCP (if enabled). */
  if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_OFFLINE) &&
    SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) )
  {
    retVal = E_NOT_OK;
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Check if any reception or transmission is active or pending otherwise. */
  {
    retVal = SoAd_SoCon_SetRemoteAddrCheckTxRxStates(SoConIdx, PartitionIdx);
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddrCheckStates() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckTxRxStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckTxRxStates(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any transmission is active or pending. */
  if ( SoAd_SoCon_CheckForActiveOrPendingTransmit(SoConIdx, PartitionIdx, FALSE) == TRUE )
  {
    retVal = E_NOT_OK;
  }

  /* #20 Check if TP reception is active. */
  if ( SoAd_IsRxMgtUsedOfSoCon(SoConIdx, PartitionIdx) )
  {
    if ( SoAd_GetSocketRouteDestIdxOfRxMgt(SoAd_GetRxMgtIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) !=
      SoAd_GetSizeOfSocketRouteDest(PartitionIdx) )
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddrCheckTxRxStates() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddrCheckAndSet()
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
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddrCheckAndSet(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare remote address to corresponding local IP addresses to prevent setting local IP address as remote. */
  /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
  if ( SoAd_SoCon_CompareToIpAddr(SoConIdx, PartitionIdx, (SOAD_A_P2CONST(SoAd_SockAddrInetXType)RemoteAddrPtr)->addr) /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_FORWARD */
    == E_NOT_OK)
  {
    boolean addrIsAny = FALSE;
    boolean portIsAny = FALSE;

    /* #20 Enter critical section to prevent that remote address is set in other context. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Copy remote address to local struct. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx),    /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
      RemoteAddrPtr);

    /* #40 Set remote address state considering wildcards in remote address to be set. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CheckForWildcards(RemoteAddrPtr, &addrIsAny, &portIsAny);                                                /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    if ( addrIsAny == TRUE )
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_IPADDR), PartitionIdx);
    }
    else
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SOAD_SOCON_IP_SET_PORT_ANY & SOAD_SOCON_MASK_IPADDR), PartitionIdx);
    }
    if ( portIsAny == TRUE )
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) |
          (SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_PORT)), PartitionIdx);
    }
    else
    {
      SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx,                                                                      /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_RemAddrStateType)(SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) |
          (SOAD_SOCON_IP_SET_PORT_SET & SOAD_SOCON_MASK_PORT)), PartitionIdx);
    }

    /* #50 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddrCheckAndSet() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ReconnectOnRemoteAddrChg()
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
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ReconnectOnRemoteAddrChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean AddEventOnChg)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  boolean                 hasSoConModeChanged = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket connection state is set in other context. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket connection is online and shall be set to reconnect since remote address has wildcards. */
  if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_ONLINE) &&
    ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
  {
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */
    hasSoConModeChanged = TRUE;
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  /* #40 Notify about changed socket conenction mode if required. */
  if ( hasSoConModeChanged == TRUE )
  {
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SOAD_SOCON_RECONNECT);
  }
  /* #41 Check if remote address is set to set event to handle socket connection in main function if requested
   *     otherwise. */
  else if ( (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_IP_SET_PORT_SET) &&
    (AddEventOnChg == TRUE) )
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
  }
  else
  {
    /* Nothing to do. */
  }
} /* SoAd_SoCon_ReconnectOnRemoteAddrChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CompareToIpAddr()
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CompareToIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrConstPtrType IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType               soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType              localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_LocalAddrByTcpIpCtrlIndIterType  tcpIpCtrlIndIter;
  SoAd_SizeOfTcpIpCtrlType              tcpIpCtrlIdx = SoAd_GetTcpIpCtrlIdxOfLocalAddr(localAddrIdx, PartitionIdx);
  Std_ReturnType                        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses of the TcpIp controller. */
  for ( tcpIpCtrlIndIter = SoAd_GetLocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl(tcpIpCtrlIdx, PartitionIdx);
    tcpIpCtrlIndIter < SoAd_GetLocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl(tcpIpCtrlIdx, PartitionIdx);
    tcpIpCtrlIndIter++ )
  {
    SoAd_SizeOfLocalAddrType  localAddrIdxTmp = SoAd_GetLocalAddrByTcpIpCtrlInd(tcpIpCtrlIndIter, PartitionIdx);
    SoAd_SockAddrInetXType    localIpAddr;
    SoAd_SockAddrInetXType    defaultRouter;
    uint8                     netmask;

    /* #100 Get local IP address from TcpIp. */
    /* PRQA S 310 5 */ /* MD_SoAd_PointerCastOnStruct */
    if ( E_OK == SoAd_TcpIpApiGetIpAddr(                                                                               /* SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD */
        SoAd_GetAddrIdOfLocalAddr(localAddrIdxTmp, PartitionIdx),
        (P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC))&localIpAddr,
        &netmask,
        (P2VAR(SoAd_SockAddrType, AUTOMATIC, AUTOMATIC))&defaultRouter) )
    {
      /* #1000 Compare IP address to local IP address. */
      if ( E_OK == SoAd_Util_CompareIpAddr(                                                                            /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
          SoAd_GetDomainOfLocalAddr(localAddrIdxTmp, PartitionIdx),
          localIpAddr.addr,
          IpAddrPtr,
          FALSE) )
      {
        /* #10000 Stop iteration if a local IP address matches. */
        retVal = E_OK;
        break;
      }
    }
    /* #101 Ignore local IP address if call to TcpIp failed. */
    else
    {
      /* nothing to do */
    }
  }

  return retVal;
} /* SoAd_SoCon_CompareToIpAddr() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set remote address if valid. */
  if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, PartitionIdx, RemoteAddrPtr) == E_OK )                            /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx, 
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddrTcp() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddrUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddrUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set remote address if valid. */
  if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, PartitionIdx, RemoteAddrPtr) == E_OK )                            /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #20 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddrUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpen()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if module is initialized and not in shutdown state. */
  if ( SoAd_State_GetState() == SOAD_STATE_INIT )
  {
    /* #20 Check if socket connection has automatic setup, is in reconnect state or is requested to be opened. */
    if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(soConGrpIdx, PartitionIdx) ||
      (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_RECONNECT) ||
      (SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx) > 0u) )
    {
      /* #200 Check if socket connection is not online yet and IP address is assigned. */
      if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_ONLINE) &&
        (SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx, PartitionIdx) == SOAD_IPADDR_STATE_ASSIGNED) )
      {
        /* #201 Try to open socket connection. */
        SoAd_SoCon_Open(SoConIdx, PartitionIdx);
      }
    }
    /* #21 Check if socket shall be opened to enable socket connection open on reception otherwise. */
    else
    {
      SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(SoConIdx, PartitionIdx);
    }
  }
} /* SoAd_SoCon_CheckAndOpen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndOpenSocketForOpenOnReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CheckAndOpenSocketForOpenOnReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP is assigned, socket is not yet opened and protocol type is UDP. */
  if ( (SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx, PartitionIdx) == SOAD_IPADDR_STATE_ASSIGNED) &&
    (SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED) &&
    SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
  {
    /* #20 Check if message acceptance filter is enabled and UDP listen only is disabled. */
    if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(soConGrpIdx, PartitionIdx) &&
      !SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
    {
      /* #30 Check if configured remote address contains wildcards. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY) &&
        ((SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
      {
        /* #40 Try to open socket and indicate to retry in next main function if no socket can be assigned. */
        if ( SoAd_SoCon_OpenSocketUdp(SoConIdx, PartitionIdx) == E_NOT_OK )
        {
          SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
            SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
        }
      }
    }
  }
} /* SoAd_SoCon_CheckAndOpenSocketForOpenOnReception() */

/**********************************************************************************************************************
 *  SoAd_SoCon_Open()
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
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Open(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Handle socket connection open sequence for TCP (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
  {
    /* #20 Handle socket connection open sequence for TCP client. */
    if ( SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
    {
      /* #200 Open TCP client socket. */
      if ( SoAd_SoCon_OpenSocketTcpClient(SoConIdx, PartitionIdx) == E_OK )
      {
        /* #2000 Handle TCP socket connection state for TCP client. */
        SoAd_SoCon_OpenSoConTcp(SoConIdx, PartitionIdx);
      }
    }
    /* #30 Handle socket connection open sequence for TCP server. */
    else
    {
      /* #300 Open TCP server (i.e. listen) socket. */
      if ( SoAd_SoCon_OpenSocketTcpServer(SoConIdx, PartitionIdx) == E_OK )
      {
        /* #3000 Handle TCP socket connection state for TCP server. */
        SoAd_SoCon_OpenSoConTcp(SoConIdx, PartitionIdx);
      }
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #40 Handle socket connection open sequence for UDP (if enabled). */
  {
    /* #400 Open UDP socket. */
    if ( SoAd_SoCon_OpenSocketUdp(SoConIdx, PartitionIdx) == E_OK )
    {
      /* #4000 Open UDP socket connection. */
      SoAd_SoCon_OpenSoConUdp(SoConIdx, PartitionIdx);
    }
  }
} /* SoAd_SoCon_Open() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketUdp()
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
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no socket is assigned. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Get socket. */
    if ( SoAd_TcpIpApiSoAdGetSocket(SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx), SOAD_IPPROTO_UDP, &socketId)/* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      == E_OK )
    {
      SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(sockIdx, PartitionIdx));

      /* #30 Set socket identifier before it may be reset due to interrupts. */
      SoAd_SetSocketIdOfSocketDyn(sockIdx, socketId, PartitionIdx);                                                    /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Bind socket. */
      if ( SoAd_TcpIpApiBind(socketId,
          SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx), &localPort) == E_OK )                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      {
        /* #50 Change parameter on socket. */
        /* Socket is bound before changing the socket parameter to enable the TcpIp to reject changing parameter
         * depending on controller specific configuration. */
        if ( SoAd_SoCon_UdpChangeParameter(SoConIdx, PartitionIdx, socketId) == E_OK )
        {
          /* #60 Assign socket and update state. */
          retVal = SoAd_SoCon_AssignSocketUdp(sockIdx, PartitionIdx, localPort);
        }
      }

      /* #70 Close socket if any error occurred. */
      if ( retVal == E_NOT_OK )
      {
        (void)SoAd_TcpIpApiClose(socketId, FALSE);
      }
    }
  }
  else
  {
    retVal = E_OK;
  }

  /* #80 If no socket is assigned set event to handle socket connection state in main function again. */
  if ( retVal == E_NOT_OK )
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_AssignSocketUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_AssignSocketUdp(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket state is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Assign socket and update local port and state in case of a valid socket identifier. */
  if ( SoAd_GetSocketIdOfSocketDyn(SockIdx, PartitionIdx) != SOAD_INV_SOCKET_ID )
  {
    SoAd_SoCon_SetLocalPortDyn(SockIdx, PartitionIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
    SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_ESTABLISHED, PartitionIdx);                                      /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_Util_FetchAddU32(SoAd_GetAddrOpenSocksOfInstanceDyn(instanceIdx, PartitionIdx), SOAD_INC_DEC_BY_ONE);         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

    retVal = E_OK;
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_AssignSocketUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConUdp()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address is set or UDP listen only is configured. */
  if ( (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_IP_SET_PORT_SET) ||
    SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
  {
    /* #20 Set socket connection to online. */
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE, PartitionIdx);                                                 /* SBSW_SOAD_PARAMETER_IDX */

    /* #30 Trigger address resolution if remote address is set. */
    if ( SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_IP_SET_PORT_SET )
    {
      SoAd_SoCon_TriggerAddressResolution(SoConIdx, PartitionIdx);
    }

    /* #40 Notify user about socket connection state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));

    /* #50 Start TP sessions by calling StartOfReception if required. */
    (void)SoAd_Rx_TpStartOfReception(SoConIdx, PartitionIdx);
  }
  /* #11 Set socket connection state to reconnect and notify user about state change (if not done before) otherwise. */
  else
  {
    if ( SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_RECONNECT )
    {
      SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT, PartitionIdx);                                            /* SBSW_SOAD_PARAMETER_IDX */

      SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));
    }
  }
} /* SoAd_SoCon_OpenSoConUdp() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClient()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClient(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType   sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no socket is assigned and remote address is set. */
  if ( (SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED) &&
    (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_IP_SET_PORT_SET) )
  {
    /* #20 Try to get and connect socket. */
    retVal = SoAd_SoCon_OpenSocketTcpClientGetAndConnect(SoConIdx, PartitionIdx, sockIdx);

    /* #30 If no socket is assigned set event to handle socket connection state in main function again. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
        SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClient() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientGetAndConnect()
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
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientGetAndConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get socket. */
  if ( SoAd_TcpIpApiSoAdGetSocket(SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx), SOAD_IPPROTO_TCP, &socketId)  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    == E_OK )
  {
    /* #20 Change parameter on socket. */
    if ( SoAd_SoCon_TcpChangeParameter(SoConIdx, PartitionIdx, socketId) == E_OK )
    {
      SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(SockIdx, PartitionIdx));

      /* #30 Set socket identifier before it may be reset due to interrupts. */
      SoAd_SetSocketIdOfSocketDyn(SockIdx, socketId, PartitionIdx);                                                    /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Bind socket. */
      if ( SoAd_TcpIpApiBind(socketId, SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx), &localPort) == E_OK )    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      {
        /* #50 Start connect and assign socket. */
        retVal = SoAd_SoCon_OpenSocketTcpClientConnect(SoConIdx, PartitionIdx, SockIdx, socketId, localPort);
      }
    }

    /* #60 Close socket if any error occurred. */
    if ( retVal == E_NOT_OK )
    {
      (void)SoAd_TcpIpApiClose(socketId, FALSE);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClientGetAndConnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpClientConnect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpClientConnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType SockIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start connect. */
  /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
  if ( SoAd_TcpIpApiTcpConnect(SocketId,                                                                               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02 */
    SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx)) == E_OK )
  {
    /* #20 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Assign socket and update local port and state in case of a valid socket identifier. */
    if ( SoAd_GetSocketIdOfSocketDyn(SockIdx, PartitionIdx) != SOAD_INV_SOCKET_ID )
    {
      SoAd_SoCon_SetLocalPortDyn(SockIdx, PartitionIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
      SoAd_SetStateOfSocketDyn(SockIdx, SOAD_SOCK_STATE_CONNECT, PartitionIdx);                                        /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_Util_FetchAddU32(SoAd_GetAddrOpenSocksOfInstanceDyn(instanceIdx, PartitionIdx), SOAD_INC_DEC_BY_ONE);       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      retVal = E_OK;
    }

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpClientConnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServer(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
  SoAd_SizeOfSocketType   listenSockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no listen socket is assigned. */
  if ( SoAd_GetStateOfSocketDyn(listenSockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Try to get socket and start listening. */
    retVal = SoAd_SoCon_OpenSocketTcpServerGetAndListen(SoConIdx, PartitionIdx, listenSockIdx);

    /* #30 If no socket is assigned set event to handle socket connection state in main function again. */
    if ( retVal == E_NOT_OK )
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
        SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServer() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerGetAndListen()
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
/* PRQA S 6050 1 */ /* MD_MSR_STCAL */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerGetAndListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SizeOfSocketType ListenSockIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIdType         socketId = SOAD_INV_SOCKET_ID;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get socket. */
  if ( SoAd_TcpIpApiSoAdGetSocket(SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx), SOAD_IPPROTO_TCP, &socketId)  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    == E_OK )
  {
    /* #20 Change parameter on socket. */
    if ( SoAd_SoCon_TcpChangeParameter(SoConIdx, PartitionIdx, socketId) == E_OK )
    {
      SoAd_PortType localPort = (SoAd_PortType)IPBASE_HTON16(SoAd_SoCon_GetLocalPortDyn(ListenSockIdx, PartitionIdx));

      /* #30 Set socket identifier before it may be reset due to interrupts. */
      SoAd_SetSocketIdOfSocketDyn(ListenSockIdx, socketId, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Bind socket. */
      if ( SoAd_TcpIpApiBind(socketId, SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx), &localPort) == E_OK )    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      {
        /* #50 Start listen and assign socket. */
        retVal = SoAd_SoCon_OpenSocketTcpServerListen(ListenSockIdx, PartitionIdx, socketId, localPort);
      }
    }

    /* #60 Close socket if any error occurred. */
    if ( retVal == E_NOT_OK )
    {
      (void)SoAd_TcpIpApiClose(socketId, FALSE);
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServerGetAndListen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSocketTcpServerListen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSocketTcpServerListen(
  SoAd_SizeOfSocketType ListenSockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConStartIdxOfSocket(ListenSockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start listen. */
  /* PRQA S 4391 2 */ /* MD_SoAd_GenericWiderTypeCast */
  if ( SoAd_TcpIpApiTcpListen(SocketId,
      (uint16)(SoAd_GetSoConEndIdxOfSocket(ListenSockIdx, PartitionIdx) - SoAd_GetSoConStartIdxOfSocket(ListenSockIdx,
        PartitionIdx))) == E_OK )
  {
    /* #20 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Assign socket and update local port and state in case of a valid socket identifier. */
    if ( SoAd_GetSocketIdOfSocketDyn(ListenSockIdx, PartitionIdx) != SOAD_INV_SOCKET_ID )
    {
      SoAd_SoCon_SetLocalPortDyn(ListenSockIdx, PartitionIdx, (SoAd_PortType)IPBASE_HTON16(LocalPort));
      SoAd_SetStateOfSocketDyn(ListenSockIdx, SOAD_SOCK_STATE_LISTEN, PartitionIdx);                                   /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_Util_FetchAddU32(SoAd_GetAddrOpenSocksOfInstanceDyn(instanceIdx, PartitionIdx), SOAD_INC_DEC_BY_ONE);       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      retVal = E_OK;
    }

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }

  return retVal;
} /* SoAd_SoCon_OpenSocketTcpServerListen() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_OpenSoConTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection is already set to reconnect. */
  if ( SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_RECONNECT )
  {
    /* #20 Set socket connection to reconnect. */
    SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */

    /* #30 Notify user about socket connection state change. */
    SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));
  }
} /* SoAd_SoCon_OpenSoConTcp() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Close()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_Close(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SoConModeType      newSoConState;
  boolean                 abortFlag = (boolean)SoAd_IsAbortOfSoConDyn(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check that no transmission is active for the socket connection. */
  if ( !SoAd_IsTxActiveOfSoConDyn(SoConIdx, PartitionIdx) )
  {
    /* #20 Get expected socket connection state after closing. */
    switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx, PartitionIdx) )
    {
      case SOAD_CLOSE_OFFLINE_RESET:
      case SOAD_CLOSE_OFFLINE:
      case SOAD_CLOSE_SOCKET:
      {
        newSoConState = SOAD_SOCON_OFFLINE;
        break;
      }
      default: /* SOAD_CLOSE_RECONNECT || SOAD_CLOSE_SOCKET_RECONNECT */
      {
        newSoConState = SOAD_SOCON_RECONNECT;
        break;
      }
    }

    /* #30 Check if expected socket connection state after closing is different to the current state. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != newSoConState )
    {
      /* #40 Set new socket connection state. */
      SoAd_SetModeOfSoConDyn(SoConIdx, newSoConState, PartitionIdx);                                                   /* SBSW_SOAD_PARAMETER_IDX */

      /* #50 Close socket connection. */
      SoAd_SoCon_CloseSoCon(SoConIdx, PartitionIdx);

      /* #60 Notify user about socket connection state change. */
      SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));
    }

    /* #70 Close related sockets. */
    SoAd_SoCon_CloseSocket(SoConIdx, PartitionIdx, abortFlag);

    /* #80 Reset socket connection close mode. */
    SoAd_SoCon_ResetCloseMode(SoConIdx, PartitionIdx);
  }
  /* #90 Set event to handle socket connection state in main function. */
  SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
    SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
} /* SoAd_SoCon_Close() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSoCon()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle socket connection close dependent on close mode. */
  switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx, PartitionIdx) )
  {
    /* #100 Check if socket connection shall be closed by normal close request. */
    case SOAD_CLOSE_OFFLINE:
    {
      /* #1000 Reset structs, remote address and terminate active TP sessions. */
      SoAd_SoCon_ResetSoCon(SoConIdx, PartitionIdx, TRUE, FALSE, TRUE);
      break;
    }
    /* #101 Check if socket connection shall be closed by special request (shutdown, API call failed, config issue). */
    case SOAD_CLOSE_OFFLINE_RESET:
    {
      /* #1010 Reset structs, remote address, open/close sequence and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, PartitionIdx, TRUE, TRUE, FALSE);
      break;
    }
#if ( SOAD_TCP == STD_ON )
    /* #102 Check if socket connection shall be closed by socket close and TcpInitiate is true (if TCP is enabled). */
    case SOAD_CLOSE_SOCKET_RECONNECT:
    {
      /* #1020 Reset structs and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, PartitionIdx, FALSE, FALSE, FALSE);
      break;
    }
#endif /* SOAD_TCP == STD_ON */
    /* #103 Close socket connection if socket is closed or requested to be reconnected otherwise. */
    default: /* SOAD_CLOSE_SOCKET || SOAD_CLOSE_RECONNECT */
    {
      /* #1030 Reset structs, remote address and terminate active TP sessions negatively. */
      SoAd_SoCon_ResetSoCon(SoConIdx, PartitionIdx, TRUE, FALSE, FALSE);
      break;
    }
  }
} /* SoAd_SoCon_CloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocket()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocket(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket is of type TCP. */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) )
  {
    /* #100 Close socket. */
    SoAd_SoCon_CloseSocketTcp(SoConIdx, PartitionIdx, Abort);

    /* #101 Handle listen socket close. */
    SoAd_SoCon_CloseSocketTcpListen(SoConIdx, PartitionIdx, Abort);
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Handle close if socket is of type UDP. */
  {
    SoAd_SoCon_CloseSocketUdp(SoConIdx, PartitionIdx, Abort);
  }

  /* #30 Reset number of data to be skipped on reception. */
  SoAd_SetSkipBytesOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx), 0u, PartitionIdx);                    /* SBSW_SOAD_PARAMETER_IDX */

} /* SoAd_SoCon_CloseSocket() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcp()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SocketIdType     socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that socket state is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Ignore close if socket is already closed. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED )
  {
    /* #200 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #21 Wait for socket close if socket is closing. */
  else if ( SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSING )
  {
    /* #210 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #22 Set socket to closing and call close service otherwise. */
  else
  {
    SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_CLOSING, PartitionIdx);                                          /* SBSW_SOAD_CSL02_CSL05 */

    /* #220 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #221 Close socket. */
    (void)SoAd_TcpIpApiClose(socketId, Abort);
  }
} /* SoAd_SoCon_CloseSocketTcp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketTcpListen()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketTcpListen(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType   sockIdx;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SocketIdType       socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is a server socket. */
  if ( !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
  {
    /* #20 Get listen socket. */
    sockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
    socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx, PartitionIdx);

    /* #30 Enter critical section to prevent that socket state is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #40 Check if listen socket is in close or closing state. */
    if ( (SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSED) &&
      (SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSING) )
    {
      /* #50 Iterate over all socket connections of socket connection group. */
      SoAd_SoConIterType  soConIter;
      boolean             listenSocketRequired = FALSE;

      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(sockIdx, PartitionIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(sockIdx, PartitionIdx);
        soConIter++ )
      {
        /* #60 Check if socket connection still requires a listen socket. */
        if ( SoAd_GetModeOfSoConDyn(soConIter, PartitionIdx) != SOAD_SOCON_OFFLINE )
        {
          listenSocketRequired = TRUE;
          break;
        }
      }

      /* #70 Handle closing of the socket if no socket connection requires a listen socket. */
      if ( (listenSocketRequired == FALSE) )
      {
        SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_CLOSING, PartitionIdx);                                      /* SBSW_SOAD_CSL02_CSL05 */
        
        /* #700 Leave critical section and call close service. */
        SOAD_END_CRITICAL_SECTION();

        /* #701 Close socket. */
        (void)SoAd_TcpIpApiClose(socketId, Abort);
      }
      /* #71 Otherwise leave critical section. */
      else
      {
        SOAD_END_CRITICAL_SECTION();
      }
    }
    /* #41 Otherwise leave critical section. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }
  }
} /* SoAd_SoCon_CloseSocketTcpListen() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseSocketUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_CloseSocketUdp(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SoConIterType    soConIter;
  SoAd_SocketIdType     socketId = SoAd_GetSocketIdOfSocketDyn(sockIdx, PartitionIdx);
  boolean               socketRequired = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is not yet closed. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) != SOAD_SOCK_STATE_CLOSED )
  {
    /* #20 Iterate over all socket connections of socket connection group. */
    for ( soConIter = SoAd_GetSoConStartIdxOfSocket(sockIdx, PartitionIdx);
      soConIter < SoAd_GetSoConEndIdxOfSocket(sockIdx, PartitionIdx);
      soConIter++ )
    {
      /* #30 Check if socket connection still requires the shared socket. */
      if ( SoAd_GetModeOfSoConDyn(soConIter, PartitionIdx) != SOAD_SOCON_OFFLINE )
      {
        socketRequired = TRUE;
        break;
      }
    }

    /* #40 Close socket if shared socket is not required anymore and socket identifier is valid. */
    if ( (socketRequired == FALSE) && (socketId != SOAD_INV_SOCKET_ID) )
    {
      (void)SoAd_TcpIpApiClose(socketId, Abort);
    }
  }
} /* SoAd_SoCon_CloseSocketUdp() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetCloseMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetCloseMode(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSocketType   sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
#endif /* SOAD_TCP == STD_ON */
  SoAd_SoConModeType      newSoConMode;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that close mode is overwritten by any function call. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Get expected socket connection mode after closing. */
  switch ( SoAd_GetCloseModeOfSoConDyn(SoConIdx, PartitionIdx) )
  {
    case SOAD_CLOSE_OFFLINE_RESET:
    case SOAD_CLOSE_OFFLINE:
    case SOAD_CLOSE_SOCKET:
    {
      newSoConMode = SOAD_SOCON_OFFLINE;
      break;
    }
    default: /* SOAD_CLOSE_RECONNECT || SOAD_CLOSE_SOCKET_RECONNECT */
    {
      newSoConMode = SOAD_SOCON_RECONNECT;
      break;
    }
  }

  /* #30 Reset close mode if socket connection is in expected mode and socket is closed in case of TCP. */
  if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) == newSoConMode)
#if ( SOAD_TCP == STD_ON )
    && (SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx, PartitionIdx)
      || (SoAd_GetStateOfSocketDyn(sockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED))
#endif /* SOAD_TCP == STD_ON */
    )
  {
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_NONE, PartitionIdx);                                              /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_SoCon_ResetCloseMode() */

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifySoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifySoConModeChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SoConModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConModeChgCbkIndIterType soConModeChgCbkIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call all socket connection related socket connection mode change notifications. */
  for ( soConModeChgCbkIndIter = SoAd_GetSoConModeChgCbkIndStartIdxOfSoCon(SoConIdx, PartitionIdx);
    soConModeChgCbkIndIter < SoAd_GetSoConModeChgCbkIndEndIdxOfSoCon(SoConIdx, PartitionIdx);
    soConModeChgCbkIndIter++ )
  {
    if ( SoAd_GetSoConModeChgCbk(SoAd_GetSoConModeChgCbkInd(soConModeChgCbkIndIter)) != NULL_PTR )
    {
      SoAd_GetSoConModeChgCbk(SoAd_GetSoConModeChgCbkInd(soConModeChgCbkIndIter))(                                     /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetSoConIdOfSoCon(SoConIdx, PartitionIdx), Mode);
    }
  }
} /* SoAd_SoCon_NotifySoConModeChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_NotifyLocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalIpAddrAssignmentChgCbkIndIterType localIpAddrAssignmentChgCbkIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call all socket connection related socket connection local IP address assignment change notifications. */
  for ( localIpAddrAssignmentChgCbkIndIter = SoAd_GetLocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon(SoConIdx,
      PartitionIdx);
    localIpAddrAssignmentChgCbkIndIter < SoAd_GetLocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon(SoConIdx, PartitionIdx);
    localIpAddrAssignmentChgCbkIndIter++ )
  {
    if ( SoAd_GetLocalIpAddrAssignmentChgCbk(SoAd_GetLocalIpAddrAssignmentChgCbkInd(
          localIpAddrAssignmentChgCbkIndIter)) != NULL_PTR )
    {
      SoAd_GetLocalIpAddrAssignmentChgCbk(SoAd_GetLocalIpAddrAssignmentChgCbkInd(localIpAddrAssignmentChgCbkIndIter))( /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetSoConIdOfSoCon(SoConIdx, PartitionIdx), State);
    }
  }
} /* SoAd_SoCon_NotifyLocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetLocalPortDyn()
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
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ResetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Reset local port on listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
  {
    /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
    SoAd_SizeOfSocketType grpSockIdx = SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
    SoAd_SoConIterType    soConIter;
    SoAd_ReturnType       retVal = E_OK;

    /* #100 Check if listen socket is closed. */
    if ( SoAd_GetStateOfSocketDyn(grpSockIdx, PartitionIdx) == SOAD_SOCK_STATE_CLOSED )
    {
      /* #1000 Check if all data sockets are closed and indicate that local port cannot be reset if not. */
      for ( soConIter = SoAd_GetSoConStartIdxOfSocket(grpSockIdx, PartitionIdx);
        soConIter < SoAd_GetSoConEndIdxOfSocket(grpSockIdx, PartitionIdx);
        soConIter++ )
      {
        if ( SoAd_GetStateOfSocketDyn(SoAd_GetSocketIdxOfSoCon(soConIter, PartitionIdx), PartitionIdx) !=
          SOAD_SOCK_STATE_CLOSED )
        {
          retVal = E_NOT_OK;
          break;
        }
      }
    }
    /* #101 Indicate that local port cannot be reset otherwise. */
    else
    {
      retVal = E_NOT_OK;
    }

    /* #102 Reset local port on listen socket to configured value if all sockets are closed. */
    if ( retVal == E_OK )
    {
      SoAd_SetLocalPortOfSocketDyn(grpSockIdx, SoAd_GetLocalPortOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);  /* SBSW_SOAD_OPTIONAL_CSL03_CSL05 */
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Reset local port on data socket to configured value otherwise. */
  {
    SoAd_SetLocalPortOfSocketDyn(SockIdx, SoAd_GetLocalPortOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);       /* SBSW_SOAD_PARAMETER_IDX */
  }
} /* SoAd_SoCon_ResetLocalPortDyn() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetSoCon()
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
/* PRQA S 3206 5 */ /* MD_SoAd_UnusedParameter */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean ResetRemAddr,
  boolean ResetOpClSeq,
  boolean NormalClose)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset remote address if required. */
#if ( SOAD_TCP == STD_ON )
  if ( ResetRemAddr == TRUE )
#else
  SOAD_DUMMY_STATEMENT(ResetRemAddr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_TCP == STD_ON */
  {
    SoAd_SoCon_ResetRemAndRcvRemAddr(SoConIdx, PartitionIdx);
  }

  /* #20 Reset open/close sequence if required. */
  if ( ResetOpClSeq == TRUE )
  {
    SoAd_SetOpenCloseCounterOfSoConDyn(SoConIdx, 0u, PartitionIdx);                                                    /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* #30 Reset abort flag. */
  SoAd_SetAbortOfSoConDyn(SoConIdx, FALSE, PartitionIdx);                                                              /* SBSW_SOAD_PARAMETER_IDX */

  /* #40 Terminate active transmissions. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx, PartitionIdx) )
  {
    SoAd_Tx_TerminateTransmit(SoConIdx, PartitionIdx);
  }

  /* #50 Terminate active receptions. */
  if ( SoAd_IsRxMgtUsedOfSoCon(SoConIdx, PartitionIdx) )
  {
    SoAd_Rx_TerminateReceive(SoConIdx, PartitionIdx, NormalClose);
  }

  /* #60 Reset alive supervision timeout. */
#if ( SOAD_TCP == STD_ON )
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx)
        > 0u )
    {
      SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx, instanceIdx, PartitionIdx);
    }
  }
} /* SoAd_SoCon_ResetSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAndRcvRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAndRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset remote address. */
  SoAd_SoCon_ResetRemAddr(SoConIdx, PartitionIdx);

  /* #20 Reset received remote address (if enabled). */
  SoAd_SoCon_ResetRcvRemAddr(SoConIdx, PartitionIdx);
} /* SoAd_SoCon_ResetRemAndRcvRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType sockAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the configured remote address. */
  SoAd_SoCon_GetConfiguredRemAddr(SoConIdx, PartitionIdx, &sockAddr);                                                  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

  /* #20 Reset remote address to configured remote address. */
  /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx),      /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
    SOAD_A_P2CONST(SoAd_SockAddrType)&sockAddr);

  /* #30 Reset remote address state to configured remote address state. */
  SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx), PartitionIdx);      /* SBSW_SOAD_PARAMETER_IDX */

  /* #40 Reset remote address release flag. */
  SoAd_SetRemAddrReleaseOfSoConDyn(SoConIdx, SOAD_RELEASE_NONE, PartitionIdx);                                         /* SBSW_SOAD_PARAMETER_IDX */
} /* SoAd_SoCon_ResetRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetConfiguredRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_GetConfiguredRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrInetXType, AUTOMATIC, SOAD_APPL_DATA) RemAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_IPV6 == STD_ON )
  SoAd_SizeOfSoConGrpType        soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType       localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_RemAddrIpV6IdxOfSoConType ipV6AddrIdx;
  SoAd_IpAddrInet6Type           remAddrIpV6; /* PRQA S 759 1 */ /* MD_MSR_Union */
#endif /* SOAD_IPV6 == STD_ON */
  SoAd_RemAddrIpV4IdxOfSoConType ipV4AddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store the configured remote address to the pointer value. */
#if ( SOAD_IPV6 == STD_ON )
  if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx) == SOAD_AF_INET6 )
  {
    ipV6AddrIdx = SoAd_GetRemAddrIpV6IdxOfSoCon(SoConIdx, PartitionIdx);
    remAddrIpV6 = SoAd_GetAddrOfRemAddrIpV6(ipV6AddrIdx, PartitionIdx);

    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    RemAddrPtr->domain   = SOAD_AF_INET6;                                                                              /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->port     = SoAd_GetPortOfRemAddrIpV6(SoAd_GetRemAddrIpV6IdxOfSoCon(SoConIdx, PartitionIdx),            /* SBSW_SOAD_POINTER_WRITE */
      PartitionIdx);
    RemAddrPtr->addr[0u] = remAddrIpV6.addr32[0u];                                                                     /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->addr[1u] = remAddrIpV6.addr32[1u];                                                                     /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->addr[2u] = remAddrIpV6.addr32[2u];                                                                     /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->addr[3u] = remAddrIpV6.addr32[3u];                                                                     /* SBSW_SOAD_POINTER_WRITE */
  }
  else
#endif /* SOAD_IPV6 == STD_ON */
  {
    ipV4AddrIdx = SoAd_GetRemAddrIpV4IdxOfSoCon(SoConIdx, PartitionIdx);

    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    RemAddrPtr->domain   = SOAD_AF_INET;                                                                               /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->port     = SoAd_GetPortOfRemAddrIpV4(ipV4AddrIdx, PartitionIdx);                                       /* SBSW_SOAD_POINTER_WRITE */
    RemAddrPtr->addr[0u] = SoAd_GetAddrOfRemAddrIpV4(ipV4AddrIdx, PartitionIdx);                                       /* SBSW_SOAD_POINTER_WRITE */
  }
} /* SoAd_SoCon_GetConfiguredRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetRcvRemAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetRcvRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType  rcvRemAddr;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_DomainType         domainLocalAddr = SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx,
    PartitionIdx), PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if received remote address is configured. */
  if ( SoAd_IsRcvRemAddrUsedOfSoCon(SoConIdx, PartitionIdx) )
  {
    /* #20 Reset received remote address. */
    /* PRQA S 2983 2 */ /* MD_SoAd_UsageNotDetected */
    rcvRemAddr.domain = domainLocalAddr;
    rcvRemAddr.port = SOAD_PORT_ANY;
#if ( SOAD_IPV6 == STD_ON )
    if ( domainLocalAddr == SOAD_AF_INET6 )
    {
      rcvRemAddr.addr[0u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[1u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[2u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[3u] = SOAD_IP6ADDR_ANY;                                                                          /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
    else
#endif /* SOAD_IPV6 == STD_ON */
    {
      rcvRemAddr.addr[0u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
#if ( SOAD_IPV6 == STD_ON )
      rcvRemAddr.addr[1u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[2u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      rcvRemAddr.addr[3u] = SOAD_IPADDR_ANY;                                                                           /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
#endif /* SOAD_IPV6 == STD_ON */
    }

    SoAd_SetRcvRemAddr(SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx, PartitionIdx), rcvRemAddr, PartitionIdx);                /* SBSW_SOAD_OPTIONAL_CHECKED_CSL03_CSL05 */
  }
} /* SoAd_SoCon_ResetRcvRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleReleaseRemAddr()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_HandleReleaseRemAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_RemAddrReleaseStateType remAddrReleaseState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that remote address release state is set in other context. */
  SOAD_BEGIN_CRITICAL_SECTION();

  remAddrReleaseState = SoAd_GetRemAddrReleaseOfSoConDyn(SoConIdx, PartitionIdx);

  /* #20 Try to release remote address if requested. */
  if ( remAddrReleaseState != SOAD_RELEASE_NONE )
  {
    /* #30 Reset remote address release state.*/
    SoAd_SetRemAddrReleaseOfSoConDyn(SoConIdx, SOAD_RELEASE_NONE, PartitionIdx);                                       /* SBSW_SOAD_INDEX_BY_FUNCTION */

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #50 Try to release remote address if requested. */
    if ( remAddrReleaseState == SOAD_RELEASE_REM_ADDR )
    {
      SoAd_SoCon_ReleaseRemoteAddr(SoConIdx, PartitionIdx, FALSE, FALSE);
    }
    /* #51 Try to force release remote address if requested otherwise. */
    else
    {
      SoAd_SoCon_ReleaseRemoteAddr(SoConIdx, PartitionIdx, TRUE, FALSE);
    }
  }
  /* #21 Leave critical section otherwise. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_HandleReleaseRemAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TriggerAddressResolution()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_TriggerAddressResolution(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any Tx PDU is configured for the socket connection. */
  if ( SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(SoConIdx, PartitionIdx) !=
    SoAd_GetPduRouteDestBySoConIndEndIdxOfSoCon(SoConIdx, PartitionIdx))
  {
    uint8 ctrlIdx = 0u;
    uint8 physAddr[6u] = { 0u, 0u, 0u, 0u, 0u, 0u };

    /* #20 Get the corresponding Ethernet interface controller index. */
    if ( SoAd_TcpIpApiGetCtrlIdx(SoAd_GetAddrIdOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        SoConIdx, PartitionIdx), PartitionIdx), PartitionIdx), &ctrlIdx) == E_OK )
    {
      /* #30 Trigger address resolution by getting remote physical address for the Ethernet interface controller. */
      /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
      (void)SoAd_TcpIpApiGetRemotePhysAddr(ctrlIdx,                                                                    /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
        SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx), &physAddr[0], TRUE);
    }
  }
} /* SoAd_SoCon_TriggerAddressResolution() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckForActiveOrPendingTransmit()
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
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_CheckForActiveOrPendingTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean TransmitImmediately)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  boolean                 isTxActive;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that indicators for active transmission are accessed in other context. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check for pending IF/TP transmission. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx, PartitionIdx) &&
    (SoAd_GetPduRouteDestIdxOfTxMgt(SoAd_GetTxMgtIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) !=
      SoAd_GetSizeOfPduRouteDest(PartitionIdx)) )
  {
    isTxActive = TRUE;
  }
  /* #30 Check for pending nPdu transmission. */
  else if ( SoAd_IsNPduUdpTxUsedOfSoCon(SoConIdx, PartitionIdx) &&
    (SoAd_GetTotalLenOfNPduUdpTxDyn(SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) > 0u) )
  {
    /* #300 Update timeout to send nPdu immediately in next main function if requested. */
    if ( TransmitImmediately == TRUE )
    {
      (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx, PartitionIdx),
        1u, instanceIdx, PartitionIdx);
    }

    isTxActive = TRUE;
  }
  /* #40 Check for pending routing group transmission. */
  else if ( SoAd_SoCon_IsTxRouteGrpActive(SoConIdx, PartitionIdx) == TRUE )
  {
    isTxActive = TRUE;
  }
  /* #50 Indicate that no transmission is active otherwise. */
  else
  {
    isTxActive = FALSE;
  }
  /* #60 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return isTxActive;
} /* SoAd_SoCon_CheckForActiveOrPendingTransmit() */

/**********************************************************************************************************************
 *  SoAd_SoCon_IsTxRouteGrpActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(boolean, SOAD_CODE) SoAd_SoCon_IsTxRouteGrpActive(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestBySoConIndIterType         pduRouteDestBySoConIndIter;
  SoAd_RouteGrpSoConByPduRouteDestIndIterType routeGrpSoConByPduRouteDestIndIter;
  SoAd_SizeOfPduRouteDestType                 pduRouteDestIdx;
  SoAd_SizeOfRouteGrpSoConType                routeGrpSoConIdx;
  boolean                                     isTxActive = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all PduRouteDests. */
  for ( pduRouteDestBySoConIndIter = SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(SoConIdx, PartitionIdx);
    pduRouteDestBySoConIndIter < SoAd_GetPduRouteDestBySoConIndEndIdxOfSoCon(SoConIdx, PartitionIdx);
    pduRouteDestBySoConIndIter++ )
  {
    pduRouteDestIdx = SoAd_GetPduRouteDestBySoConInd(pduRouteDestBySoConIndIter, PartitionIdx);

    /* #20 Iterate over all PduRouteDest related routing group states. */
    for ( routeGrpSoConByPduRouteDestIndIter =
        SoAd_GetRouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest(pduRouteDestIdx, PartitionIdx);
      routeGrpSoConByPduRouteDestIndIter <
        SoAd_GetRouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest(pduRouteDestIdx, PartitionIdx);
      routeGrpSoConByPduRouteDestIndIter++ )
    {
      routeGrpSoConIdx = SoAd_GetRouteGrpSoConByPduRouteDestInd(routeGrpSoConByPduRouteDestIndIter, PartitionIdx);

      /* #30 Check if routing group transmission is active. */
      if ( SoAd_IsTriggerOfRouteGrpSoConDyn(routeGrpSoConIdx, PartitionIdx) )
      {
        /* #40 Return that transmission is active. */
        isTxActive = TRUE;
        break;
      }
    }
    if ( isTxActive == TRUE )
    {
      break;
    }
  }

  return isTxActive;
} /* SoAd_SoCon_IsTxRouteGrpActive() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_BestMatchPrioType bestMachPrio = SOAD_BEST_MATCH_NONE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address has no "not set" values. */
  if ( (SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_NOT) == 0u )
  {
#if ( SOAD_IPV6 == STD_ON )
    /* #20 Check remote address in case of IPv6 (if enabled). */
    if ( SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx),
      PartitionIdx), PartitionIdx) == SOAD_AF_INET6 )
    {
      /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
      bestMachPrio = SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(SoConIdx, PartitionIdx,
        SOAD_A_P2CONST(SoAd_SockAddrInet6Type)SockAddrPtr);                                                            /* SBSW_SOAD_POINTER_FORWARD */
    }
    else
#endif /* SOAD_IPV6 == STD_ON */
    /* #30 Check remote address in case of IPv4. */
    {
      /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
      bestMachPrio = SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(SoConIdx, PartitionIdx,
        SOAD_A_P2CONST(SoAd_SockAddrInetType)SockAddrPtr);                                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdx() */

#if ( SOAD_IPV6 == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 310, 3305 4 */ /* MD_SoAd_PointerCastOnStruct */
  uint8_least             addrIdx;
  uint16                  dynPort = SockAddrPtr->port;
  SoAd_BestMatchPrioType  bestMachPrio = SOAD_BEST_MATCH_NONE;
  boolean                 ipIsEqual = TRUE;
  boolean                 ipIsWildcard = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address is equal. */
  for ( addrIdx = 0u; addrIdx < SOAD_IPV6_ADDR_LEN_32; addrIdx++ )
  {
    /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
    if ( SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[addrIdx] != SockAddrPtr->addr[addrIdx] )
    {
      ipIsEqual = FALSE;
      break;
    }
  }

  /* #20 Check if IP address is wildcard. */
  for ( addrIdx = 0u; addrIdx < SOAD_IPV6_ADDR_LEN_32; addrIdx++ )
  {
    if ( SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[addrIdx] != SOAD_IP6ADDR_ANY )
    {
      ipIsWildcard = FALSE;
      break;
    }
  }

  /* #30 Calculate best match priority. */
  if ( (ipIsEqual == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH;
  }
  else if ( (ipIsEqual == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_ANY;
  }
  else if ( (ipIsWildcard == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_MATCH;
  }
  else if ( (ipIsWildcard == TRUE) && (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_ANY;
  }
  else
  {
    /* Nothing to do. */
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdxV6() */
#endif /* SOAD_IPV6 == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_BestMatchPrioType, SOAD_CODE) SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrInetType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 310, 3305 2 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_IpAddrInetType     dynAddr = SockAddrPtr->addr[0];
  SoAd_PortType           dynPort = SockAddrPtr->port;
  SoAd_BestMatchPrioType  bestMachPrio = SOAD_BEST_MATCH_NONE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate best match priority. */
  if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[0] == dynAddr) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[0] == dynAddr) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == SOAD_PORT_ANY) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_MATCH_PORT_ANY;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[0] == SOAD_IPADDR_ANY) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == dynPort) )
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_MATCH;
  }
  else if ( (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).addr[0] == SOAD_IPADDR_ANY) &&
    (SoAd_GetRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx).port == SOAD_PORT_ANY))
  {
    bestMachPrio = SOAD_BEST_MATCH_IP_ANY_PORT_ANY;
  }
  else
  {
    /* Nothing to do. */
  }

  return bestMachPrio;
} /* SoAd_SoCon_GetBestMatchPrioOfSoConIdxV4() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUdpAliveTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_SetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType  soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType  instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if alive supervision timeout is configured. */
  if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx, PartitionIdx) != 0u )
  {
    /* #20 Set alive supervision timeout. */
    (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx,
      SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx, PartitionIdx), instanceIdx, PartitionIdx);
  }
} /* SoAd_SoCon_SetUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ResetUdpAliveTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_ResetUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType  soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType  instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if alive supervision timeout is configured. */
  if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx, PartitionIdx) != 0u )
  {
    /* #20 Remove alive supervision timeout from timeout list. */
    SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx, instanceIdx, PartitionIdx);
  }
} /* SoAd_SoCon_ResetUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_DecrementOpenSockets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_SoCon_DecrementOpenSockets(
  SoAd_SizeOfInstanceType InstanceIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if at least one socket is opened. */
  if ( SoAd_Util_LoadU32(SoAd_GetAddrOpenSocksOfInstanceDyn(InstanceIdx, PartitionIdx)) > 0u )                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* #20 Decrement number of open sockets. */
    SoAd_Util_FetchSubU32(SoAd_GetAddrOpenSocksOfInstanceDyn(InstanceIdx, PartitionIdx), SOAD_INC_DEC_BY_ONE);         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }
} /* SoAd_SoCon_DecrementOpenSockets() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_SoCon_InitLocalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_InitLocalAddr(
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_LocalAddrIterType localAddrIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all local addresses. */
  for ( localAddrIter = 0u; localAddrIter < SoAd_GetSizeOfLocalAddr(PartitionIdx); localAddrIter++ )
  {
    /* #20 Initialize IP address assignment state. */
    SoAd_SetIpAddrStateOfLocalAddrDyn(localAddrIter, SOAD_IPADDR_STATE_UNASSIGNED, PartitionIdx);                      /* SBSW_SOAD_CSL02_CSL05 */
  }
} /* SoAd_SoCon_InitLocalAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_InitSoCon()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSoCon(
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType soConIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connection indexes. */
  for ( soConIter = 0u; soConIter < SoAd_GetSizeOfSoCon(PartitionIdx); soConIter++ )
  {
    /* #20 Initialize general struct elements. */
    SoAd_SetModeOfSoConDyn(soConIter, SOAD_SOCON_OFFLINE, PartitionIdx);                                               /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetTxActiveOfSoConDyn(soConIter, FALSE, PartitionIdx);                                                        /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetAbortOfSoConDyn(soConIter, FALSE, PartitionIdx);                                                           /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetCloseModeOfSoConDyn(soConIter, SOAD_CLOSE_NONE, PartitionIdx);                                             /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetOpenCloseCounterOfSoConDyn(soConIter, 0u, PartitionIdx);                                                   /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetRemAddrReleaseOfSoConDyn(soConIter, SOAD_RELEASE_NONE, PartitionIdx);                                      /* SBSW_SOAD_CSL02_CSL05 */

    SoAd_SoCon_ResetRemAndRcvRemAddr((SoAd_SizeOfSoConType)soConIter, PartitionIdx);

    /* #30 Initialize tx struct elements. */
    SoAd_Tx_InitSoCon((SoAd_SizeOfSoConType)soConIter, PartitionIdx);

    /* #40 Initialize rx struct elements. */
    SoAd_Rx_InitSoCon((SoAd_SizeOfSoConType)soConIter, PartitionIdx);
  }
} /* SoAd_SoCon_InitSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_InitSocket()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_InitSocket(
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType      sockIter;
  SoAd_InstanceDynIterType instDynIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all module internal socket indexes. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(PartitionIdx); sockIter++ )
  {
    /* #20 Initialize general struct elements. */
    SoAd_SetStateOfSocketDyn(sockIter, SOAD_SOCK_STATE_CLOSED, PartitionIdx);                                          /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SetSocketIdOfSocketDyn(sockIter, SOAD_INV_SOCKET_ID, PartitionIdx);                                           /* SBSW_SOAD_CSL02_CSL05 */
    SoAd_SoCon_ResetLocalPortDyn((SoAd_SizeOfSocketType)sockIter, PartitionIdx);

    /* #30 Initialize tx struct elements. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIter, SoAd_GetSizeOfSoCon(PartitionIdx), PartitionIdx);                    /* SBSW_SOAD_CSL02_CSL05 */

    /* #40 Initialize rx struct elements. */
    SoAd_SetSkipBytesOfSocketDyn(sockIter, 0u, PartitionIdx);                                                          /* SBSW_SOAD_CSL02_CSL05 */
  }

  /* #50 Initialize the number of open sockets. */
  for ( instDynIter = 0; instDynIter < SoAd_GetSizeOfInstanceDyn(PartitionIdx); instDynIter++ )
  {
    SoAd_Util_StoreU32(SoAd_GetAddrOpenSocksOfInstanceDyn(instDynIter, PartitionIdx), 0u, TRUE);                       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }
} /* SoAd_SoCon_InitSocket() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSockIdxBySocketId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSockIdxBySocketId(
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SizeOfSocketType, AUTOMATIC, SOAD_APPL_DATA) SockIdxPtr,
  P2VAR(SoAd_PartitionConfigIdxType, AUTOMATIC, SOAD_APPL_DATA) PartitionIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketIterType               sockIter;
  SoAd_PartitionIdentifiersIterType partitionIdentifierIter;
#if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
  ApplicationType                   osApplicationId = (ApplicationType)GetApplicationID();
#endif /* SOAD_MULTI_PARTITION == STD_ON */
  SoAd_PartitionConfigIdxType       partitionIdx;
  Std_ReturnType                    retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  for ( partitionIdentifierIter = 0u; partitionIdentifierIter < SoAd_GetSizeOfPartitionIdentifiers();
    partitionIdentifierIter++ )
  {
    partitionIdx = SoAd_GetPCPartitionConfigIdxOfPartitionIdentifiers(partitionIdentifierIter);
#if ( SOAD_MULTI_PARTITION == STD_ON ) /* COV_SOAD_QM_FEATURE_MULTI_PARTITION */
    if ( SoAd_GetOsApplicationIdOfPartition(0u, partitionIdx) == osApplicationId )
#endif /* SOAD_MULTI_PARTITION == STD_ON */
    {
      /* #10 Iterate over all socket indexes. */
      for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(partitionIdx); sockIter++ )
      {
        /* #20 Check if specified socket identifier is related to the socket index. */
        if ( SocketId == SoAd_GetSocketIdOfSocketDyn(sockIter, partitionIdx) )
        {
          /* #30 Return socket index and stop iteration. */
          *SockIdxPtr = (SoAd_SizeOfSocketType)sockIter;                                                               /* SBSW_SOAD_POINTER_WRITE */
          *PartitionIdxPtr = partitionIdx;                                                                             /* SBSW_SOAD_POINTER_WRITE */
          retVal = E_OK;
          break;
        }
      }
      if ( retVal == E_OK )
      {
        break;
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_GetSockIdxBySocketId() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAccepted()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAccepted(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketIdConnected,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConType  soConIdxAccepted = SoAd_GetSizeOfSoCon(PartitionIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check listen socket state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx, PartitionIdx) == SOAD_SOCK_STATE_LISTEN )
  {
    /* #20 Check if a suitable socket connection can be found. */
    if ( SoAd_SoCon_TcpAcceptedGetSoConIdx(soConIdx, PartitionIdx, RemoteAddrPtr, &soConIdxAccepted) == E_OK )         /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Check if socket connection accepts connection. */
      retVal = SoAd_SoCon_TcpAcceptedCheckAcceptance(soConIdxAccepted, PartitionIdx, SocketIdConnected, RemoteAddrPtr);/* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #21 Increment dropped TCP connection counter and report the corresponding security event (as configured)
     *     otherwise. */
    else
    {
# if ( (SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON) || (SOAD_SECURITY_EVENT_REPORTING == STD_ON) )
      SoAd_Anomaly_Report(SOAD_MEAS_DROP_TCP_CONNECTION, PartitionIdx);
# endif /* (SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON) || (SOAD_SECURITY_EVENT_REPORTING == STD_ON) */
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpAccepted() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpAcceptedGetSoConIdx()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpAcceptedGetSoConIdx(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemoteAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdxListSize = 0u;
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check is message acceptance filter is enabled. */
  if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(soConGrpIdx, PartitionIdx) )
  {
    /* #100 Enter critical section to prevent that socket connections of group changes states or remote address. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #101 Check if best match algortihm can find a suitable socket connection. */
    if ( SoAd_SoCon_GetSoConIdxListByBestMatchAlg(SoConIdx, PartitionIdx, SOAD_SOCON_FILTER_ON_OFF, RemoteAddrPtr,     /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      &soConIdxListSize) == E_OK )
    {
      /* #102 Return first matching socket connection. */
      *SoConIdxPtr = SoAd_GetSoConIdxOfBestMatchSoConIdxList(SoAd_GetBestMatchSoConIdxListStartIdxOfInstance(          /* SBSW_SOAD_POINTER_WRITE */
        instanceIdx, PartitionIdx), PartitionIdx);

      retVal = E_OK;
    }

    /* #104 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
  /* #11 Check acceptance on single socket connection otherwise. */
  else
  {
    /* #110 Check socket connection state. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_SOCON_RECONNECT )
    {
      *SoConIdxPtr = SoConIdx;                                                                                         /* SBSW_SOAD_POINTER_WRITE */

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_TcpAcceptedGetSoConIdx() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpConnected()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_TcpConnected(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSocketType sockIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket is in connected state. */
  if ( SoAd_GetStateOfSocketDyn(SockIdx, PartitionIdx) == SOAD_SOCK_STATE_CONNECT )
  {
    /* #200 Check if socket connection is still requested to be opened. */
    if ( (SoAd_GetOpenCloseCounterOfSoConDyn(soConIdx, PartitionIdx) > 0u) ||
      SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx, PartitionIdx), PartitionIdx) )
    {
      /* #2000 Check if socket connection mode is not online. */
      if ( SoAd_GetModeOfSoConDyn(soConIdx, PartitionIdx) != SOAD_SOCON_ONLINE )
      {
        /* #20000 Change socket state and socket connection mode. */
        sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx, PartitionIdx);
        SoAd_SetStateOfSocketDyn(sockIdx, SOAD_SOCK_STATE_ESTABLISHED, PartitionIdx);                                  /* SBSW_SOAD_CSL02_CSL05 */
        SoAd_SetModeOfSoConDyn(soConIdx, SOAD_SOCON_ONLINE, PartitionIdx);                                             /* SBSW_SOAD_PARAMETER_IDX */

        /* #20001 Leave critical section. */
        SOAD_END_CRITICAL_SECTION();

        /* #20002 Notify user about state change. */
        SoAd_SoCon_NotifySoConModeChg(soConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(soConIdx, PartitionIdx));

        /* #20003 Try to start TP reception if required. */
        (void)SoAd_Rx_TpStartOfReception(soConIdx, PartitionIdx);
      }
      /* #2001 Otherwise leave critical section. */
      else
      {
        SOAD_END_CRITICAL_SECTION();
      }
    }
    /* #210 Otherwise leave critical section. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }
  }
  /* #21 Otherwise leave critical section. */
  else
  {
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_TcpConnected() */

/**********************************************************************************************************************
 *  SoAd_SoCon_TcpChangeParameter()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_TcpChangeParameter(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfSocketTcpType  socketTcpIdx = SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  uint32                    tcpTxBufMin = SoAd_GetTcpTxBufMinOfSocketTcp(socketTcpIdx, PartitionIdx);
  uint32                    tcpRxBufMin = SoAd_GetTcpRxBufMinOfSocketTcp(socketTcpIdx, PartitionIdx);
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set frame priority. */
  if ( SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx, PartitionIdx) != SOAD_NO_FRAMEPRIORITYOFSOCONGRP )
  {
    uint8 framePriority = SoAd_GetFramePriorityOfSoConGrp(soConGrpIdx, PartitionIdx);

    retVal = SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_FRAMEPRIO, &framePriority);                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  }

  /* #20 Set rx buffer size. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnParam */
  retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_RXWND_MAX, (uint8*)&tcpRxBufMin);                  /* SBSW_SOAD_CAST_POINTER_FORWARD */

  /* #30 Set tx buffer size. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnParam */
  retVal |= SoAd_TcpIpApiChangeParameter(SocketId, SOAD_PARAMID_TCP_TXWND_MAX, (uint8*)&tcpTxBufMin);                  /* SBSW_SOAD_CAST_POINTER_FORWARD */

  /* #40 Set no delay (Nagle algorithm). */
  retVal |= SoAd_SoCon_TcpChangeParameterNoDelay(SoConIdx, PartitionIdx, SocketId);

  /* #50 Set keep alive. */
  retVal |= SoAd_SoCon_TcpChangeParameterKeepAlive(SoConIdx, PartitionIdx, SocketId);

  /* #60 Set TLS. */
  retVal |= SoAd_SoCon_TcpChangeParameterTls(SoConIdx, PartitionIdx, SocketId);

  /* #70 Set MSL. */
  retVal |= SoAd_SoCon_TcpChangeParameterMsl(SoConIdx, PartitionIdx, SocketId);

  return retVal;
} /* SoAd_SoCon_TcpChangeParameter() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_SoCon_Event()
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
/* PRQA S 3206 3 */ /* MD_SoAd_UnusedParameter */
FUNC(void, SOAD_CODE) SoAd_SoCon_Event(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_EventType Event)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Handle socket dependent of Event type (if TCP is enabled). */
  switch ( Event )
  {
    /* #100 Handle event of UDP close. */
    case SOAD_UDP_CLOSED:
    {
      SoAd_SoCon_EventUdpClose(SockIdx, PartitionIdx);
      break;
    }
    /* #101 Handle event of TCP close or reset. */
    case SOAD_TCP_RESET:
    case SOAD_TCP_CLOSED:
    {
      SoAd_SoCon_EventTcpClose(SockIdx, PartitionIdx);
      break;
    }
    /* #102 Handle event of TCP FIN received. */
    case SOAD_TCP_FIN_RECEIVED:
    {
      SoAd_SoCon_EventTcpFinReceived(SockIdx, PartitionIdx);
      break;
    }
    /* #103 Ignore event of TLS handshake succeeded. */
    default:
    { /* SOAD_TLS_HANDSHAKE_SUCCEEDED */
      break;
    }
  }
#else
  /* #11 Handle event of UDP close (otherwise). */
  SoAd_SoCon_EventUdpClose(SockIdx, PartitionIdx);

  SOAD_DUMMY_STATEMENT(Event); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_TCP == STD_ON */
} /* SoAd_SoCon_Event() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection states allow to set remote address and if no release is pending. */
  if ( (SoAd_SoCon_SetRemoteAddrCheckStates(SoConIdx, PartitionIdx) == E_OK) && 
    (SoAd_GetRemAddrReleaseOfSoConDyn(SoConIdx, PartitionIdx) == SOAD_RELEASE_NONE) )
  {
    /* #20 Check and set remote address if valid. */
    if ( SoAd_SoCon_SetRemoteAddrCheckAndSet(SoConIdx, PartitionIdx, RemoteAddrPtr) == E_OK )                          /* SBSW_SOAD_POINTER_FORWARD */
    {
      /* #30 Check and perform mode change of the socket connection if required. */
      SoAd_SoCon_ReconnectOnRemoteAddrChg(SoConIdx, PartitionIdx, TRUE);

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_SetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetUniqueRemoteAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_SetUniqueRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSoConType    assignedSoConIdx;
  SoAd_SizeOfSoConType    bestMatchListSize = 0u;
  boolean                 ipAddrIsAny = FALSE;
  boolean                 portIsAny = FALSE;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that remote address is set in other context. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if remote address contains wildcards. */
  SoAd_Util_CheckForWildcards(RemoteAddrPtr, &ipAddrIsAny, &portIsAny);                                                /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  if ( (ipAddrIsAny == FALSE) && (portIsAny == FALSE) )
  {
    /* #30 Get socket connection using best match algorithm. */
    if ( SoAd_SoCon_GetSoConIdxListByBestMatchAlg(SoConIdx, PartitionIdx, SOAD_SOCON_FILTER_DISABLED, RemoteAddrPtr,   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      &bestMatchListSize) == E_OK )
    {
      assignedSoConIdx = SoAd_GetSoConIdxOfBestMatchSoConIdxList(SoAd_GetBestMatchSoConIdxListStartIdxOfInstance(
        instanceIdx, PartitionIdx), PartitionIdx);

      /* #40 Check if requested remote address is already set on the socket connection. */
      if ( SoAd_GetRemAddrStateDynOfSoConDyn(assignedSoConIdx, PartitionIdx) == SOAD_SOCON_IP_SET_PORT_SET )
      {
        /* #400 Remove alive supervision timeout from timeout list if configured and running. */
#if ( SOAD_TCP == STD_ON )
        if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(assignedSoConIdx, PartitionIdx), PartitionIdx) )
#endif /* SOAD_TCP == STD_ON */
        {
          SoAd_SoCon_ResetUdpAliveTimeout(assignedSoConIdx, PartitionIdx);
        }

        retVal = E_OK;
      }
      else
#if ( SOAD_TCP == STD_ON )
      /* #41 Handle setting remote address on TCP socket otherwise (if enabled). */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(assignedSoConIdx, PartitionIdx), PartitionIdx) )
      {
        retVal = SoAd_SoCon_SetUniqueRemoteAddrTcp(assignedSoConIdx, PartitionIdx, RemoteAddrPtr);                     /* SBSW_SOAD_POINTER_FORWARD */
      }
      else
#endif /* SOAD_TCP == STD_ON */
      /* #42 Handle setting remote address on UDP socket otherwise. */
      {
        retVal = SoAd_SoCon_SetUniqueRemoteAddrUdp(assignedSoConIdx, PartitionIdx, RemoteAddrPtr);                     /* SBSW_SOAD_POINTER_FORWARD */
      }

      /* #50 Return socket connection if found by best match algorithm and it is valid to set. */
      if ( retVal == E_OK )
      {
        *AssignedSoConIdPtr = SoAd_GetSoConIdOfSoCon(assignedSoConIdx, PartitionIdx);                                  /* SBSW_SOAD_POINTER_WRITE */
      }
    }
  }

  /* #60 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_SetUniqueRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_ReleaseRemoteAddr()
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
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_ReleaseRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean ForceRelease,
  boolean AddEventOnChg)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  boolean                 releaseTriggered = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if socket connection transmission and reception states allow to release remote address. */
  if ( SoAd_SoCon_SetRemoteAddrCheckTxRxStates(SoConIdx, PartitionIdx) == E_OK )
  {
#if ( SOAD_TCP == STD_ON )
    /* #200 Check if socket connection is not offline in case of TCP (if enabled). */
    if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_OFFLINE) &&
      SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
    {
      /* #2000 Force release if requested. */
      if ( ForceRelease == TRUE )
      {
        /* #20000 Reset the remote address if the connection is not online and the socket is not yet connecting. */
        if ( (SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_ONLINE) &&
          (SoAd_GetStateOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx), PartitionIdx) >
            SOAD_SOCK_STATE_CONNECT) )
        {
          SoAd_SoCon_ResetRemAddr(SoConIdx, PartitionIdx);
        }
        /* #20001 Handle the release of the remote address in the next main funtion cycle otherwise. */
        else
        {
          /* #200010 Set close mode reconnect and the force remote address release state. */
          SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_RECONNECT, PartitionIdx);                                   /* SBSW_SOAD_PARAMETER_IDX */
          SoAd_SetRemAddrReleaseOfSoConDyn(SoConIdx, SOAD_RELEASE_REM_ADDR_FORCE, PartitionIdx);                       /* SBSW_SOAD_PARAMETER_IDX */
        }

        /* #20002 Leave critical section. */
        SOAD_END_CRITICAL_SECTION();

        /* #20003 Add an event to the queue to handle the state change (and release) in the main function. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
          SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

        releaseTriggered = TRUE;
      }
    }
    /* #201 Release the remote address otherwise. */
    else
#endif /* SOAD_TCP == STD_ON */
    {
      /* #2010 Reset the remote address. */
      SoAd_SoCon_ResetRemAddr(SoConIdx, PartitionIdx);

      /* #2011 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      /* #2012 Check and perform mode change of the socket connection if required. */
      SoAd_SoCon_ReconnectOnRemoteAddrChg(SoConIdx, PartitionIdx, AddEventOnChg);

      releaseTriggered = TRUE;
    }
  }

  /* #30 Check if release was not yet triggered. */
  if ( releaseTriggered == FALSE )
  {
    /* #300 Set force remote address release state in case the release is forced or was forced already. */
    if ( (ForceRelease == TRUE) || (SoAd_GetRemAddrReleaseOfSoConDyn(SoConIdx, PartitionIdx) ==
        SOAD_RELEASE_REM_ADDR_FORCE) )
    {
      SoAd_SetRemAddrReleaseOfSoConDyn(SoConIdx, SOAD_RELEASE_REM_ADDR_FORCE, PartitionIdx);                           /* SBSW_SOAD_PARAMETER_IDX */
    }
    /* #301 Set remote address release state otherwise. */
    else
    {
      SoAd_SetRemAddrReleaseOfSoConDyn(SoConIdx, SOAD_RELEASE_REM_ADDR, PartitionIdx);                                 /* SBSW_SOAD_PARAMETER_IDX */
    }

    /* #302 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();

    /* #303 Add an event to the queue to handle the release in the main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
  }
} /* SoAd_SoCon_ReleaseRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckRemoteAddrRelease()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckRemoteAddrRelease(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType               cfgRemAddr;
  SOAD_P2CONST(SoAd_SockAddrInetXType) currentRemAddrPtr = SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx, PartitionIdx);
  Std_ReturnType                       retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the configured remote address. */
  SoAd_SoCon_GetConfiguredRemAddr(SoConIdx, PartitionIdx, &cfgRemAddr);                                                /* SBSW_SOAD_CONST_POINTER_FORWARD */

  /* #20 Check if the currently set remote address (IP address and port) is equal to the configured one. */
  if ( SoAd_Util_CompareIpAddr(cfgRemAddr.domain, cfgRemAddr.addr, currentRemAddrPtr->addr, FALSE) == E_OK )           /* SBSW_SOAD_CONST_POINTER_FORWARD */
  {
    if ( cfgRemAddr.port == currentRemAddrPtr->port )
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_SoCon_CheckRemoteAddrRelease() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestOpenSoCon()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestOpenSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and open close counter wraps around. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if open close counter can handle new request. */
  if ( SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx) < SOAD_INV_BUF_IDX_32 )
  {
    /* #30 Increment counter. */
    SoAd_IncOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx);                                                        /* SBSW_SOAD_PARAMETER_IDX */

    /* #40 Set event to handle socket connection state in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
      SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

    retVal = E_OK;
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_RequestOpenSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestCloseSoCon()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestCloseSoCon(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and open close counter wraps around. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if open close counter can handle new request. */
  if ( SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx) > 0u )
  {
    /* #200 Decrement counter. */
    SoAd_DecOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx);                                                        /* SBSW_SOAD_PARAMETER_IDX */

    retVal = E_OK;
  }

  /* #30 Check if open close counter is 0 or 'Abort' flag is set. */
  if ( (SoAd_GetOpenCloseCounterOfSoConDyn(SoConIdx, PartitionIdx) == 0u) || (Abort == TRUE) )
  {
    /* #40 Check if socket connection is not yet offline. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx) != SOAD_SOCON_OFFLINE )
    {
      /* #50 Set flags to close socket connection in main function. */
      if ( Abort == TRUE )
      {
        SoAd_SetAbortOfSoConDyn(SoConIdx, TRUE, PartitionIdx);                                                         /* SBSW_SOAD_PARAMETER_IDX */
      }
      SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE, PartitionIdx);                                         /* SBSW_SOAD_PARAMETER_IDX */

      /* #60 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
        SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
    }

    /* #70 Reset open close counter to 0. */
    SoAd_SetOpenCloseCounterOfSoConDyn(SoConIdx, 0u, PartitionIdx);                                                    /* SBSW_SOAD_PARAMETER_IDX */

    retVal = E_OK;
  }

  /* #80 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_RequestCloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetCloseMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_SetCloseMode(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  uint8 CloseMode)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if new close mode has higher priority than current close mode. */
  if ( CloseMode > SoAd_GetCloseModeOfSoConDyn(SoConIdx, PartitionIdx) )
  {
    /* #20 Set close mode to requested close mode. */
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, CloseMode, PartitionIdx);                                                    /* SBSW_SOAD_PARAMETER_IDX */
  }
} /* SoAd_SoCon_SetCloseMode() */

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleSoConStates()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleSoConStates(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueStateSoConIterType eventQueueStateSoConIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_SO_CON_STATE, InstMapIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueStateSoConIter = 0u;
    eventQueueStateSoConIter < elementNumToHandle;
    eventQueueStateSoConIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_SO_CON_STATE, InstMapIdx, &handleIdx) == E_OK )               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      SoAd_SizeOfSoConType        soConIdx = (SoAd_SizeOfSoConType)handleIdx;
      SoAd_PartitionConfigIdxType partitionIdx =
        SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx);

      /* #30 Check for a request for the release of the remote address and handle it. */
      SoAd_SoCon_HandleReleaseRemAddr(soConIdx, partitionIdx);

      /* #40 Check and try to open socket connection if no socket connection close is requested. */
      if ( SoAd_GetCloseModeOfSoConDyn(soConIdx, partitionIdx) == SOAD_CLOSE_NONE )
      {
        SoAd_SoCon_CheckAndOpen(soConIdx, partitionIdx);
      }
      /* #41 Close socket connection otherwise. */
      else
      {
        SoAd_SoCon_Close(soConIdx, partitionIdx);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_SoCon_HandleSoConStates() */

/**********************************************************************************************************************
 *  SoAd_SoCon_Reconnect()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_Reconnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if automatic setup is enabled. */
  if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(soConGrpIdx, PartitionIdx) )
  {
    /* #20 Check if keep online is not enabled. */
    if ( !SoAd_IsSockAutoSoConSetupKeepOnlineOfSoConGrp(soConGrpIdx, PartitionIdx) )
    {
      /* #30 Check if remote address contains wildcards. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_ANY) != 0u )
      {
        /* #40 Reset remote address and received remote address. */
        SoAd_SoCon_ResetRemAndRcvRemAddr(SoConIdx, PartitionIdx);

        /* #50 Set socket connection to reconnect. */
        SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_RECONNECT, PartitionIdx);                                          /* SBSW_SOAD_PARAMETER_IDX */

        /* #60 Set event to handle socket connection state in main function. */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
          SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

        /* #70 Notify user about socket connection state change. */
        SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SoAd_GetModeOfSoConDyn(SoConIdx, PartitionIdx));
      }
    }
  }
} /* SoAd_SoCon_Reconnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestReconnect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_RequestReconnect(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket connection has automatic setup enabled. */
  if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(soConGrpIdx, PartitionIdx) )
  {
    /* #20 Check if keep online is not enabled. */
    if ( !SoAd_IsSockAutoSoConSetupKeepOnlineOfSoConGrp(soConGrpIdx, PartitionIdx) )
    {
      /* #30 Check if no not set values and wildcards are configured for remote address. */
      if ( (SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY) &&
        ((SoAd_GetRemAddrStateOfSoCon(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_ANY) != 0u) )
      {
        /* #40 Set socket connection to reconnect in next main function. */
        SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_RECONNECT, PartitionIdx);                                     /* SBSW_SOAD_PARAMETER_IDX */
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx,
          SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
      }
    }
  }
} /* SoAd_SoCon_RequestReconnect() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSockets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_CloseAllSockets(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_MULTI_INSTANCE == STD_ON )
  SoAd_SizeOfInstanceType     instanceIdx = SoAd_GetPartitionSpecificInstanceIdxOfInstanceMap(InstMapIdx);
  SoAd_SizeOfSoConGrpType     soConGrpIdx;
#endif /* SOAD_MULTI_INSTANCE == STD_ON */
  SoAd_PartitionConfigIdxType partitionIdx = SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx);
  SoAd_SocketIterType         sockIter;
  SoAd_SocketIdType           socketId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all sockets of the current partition. */
  for ( sockIter = 0u; sockIter < SoAd_GetSizeOfSocket(partitionIdx); sockIter++ )
  {
    /* #20 Check if socket belongs to the current instance. */
#if ( SOAD_MULTI_INSTANCE == STD_ON )
    soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIter, partitionIdx), partitionIdx);

    if ( SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, partitionIdx) == instanceIdx )
#endif /* SOAD_MULTI_INSTANCE == STD_ON */
    {
      socketId = SoAd_GetSocketIdOfSocketDyn(sockIter, partitionIdx);

      /* #30 Check if socket is not closed. */
      if ( SoAd_GetStateOfSocketDyn(sockIter, partitionIdx) != SOAD_SOCK_STATE_CLOSED )
      {
        /* #40 Close socket. */
        (void)SoAd_TcpIpApiClose(socketId, TRUE);
      }
    }
  }
} /* SoAd_SoCon_CloseAllSockets() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CloseAllSoCons()
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
/* PRQA S 6080 1 */ /* MD_MSR_STMIF */
FUNC(boolean, SOAD_CODE) SoAd_SoCon_CloseAllSoCons(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_MULTI_INSTANCE == STD_ON )
  SoAd_SizeOfInstanceType     instanceIdx = SoAd_GetPartitionSpecificInstanceIdxOfInstanceMap(InstMapIdx);
#endif /* SOAD_MULTI_INSTANCE == STD_ON */
  SoAd_PartitionConfigIdxType partitionIdx = SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx);
  SoAd_SoConIterType          soConIter;
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_SizeOfSoConGrpType     soConGrpIdx;
  boolean                     allSoConsClosed = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connections. */
  for ( soConIter = 0u; soConIter < SoAd_GetSizeOfSoCon(partitionIdx); soConIter++ )
  {
    soConIdx = (SoAd_SizeOfSoConType)soConIter;
    soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx, partitionIdx);

    /* #20 Check if socket connection belongs to the current instance. */
#if ( SOAD_MULTI_INSTANCE == STD_ON )
    if ( SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, partitionIdx) == instanceIdx )
#endif /* SOAD_MULTI_INSTANCE == STD_ON */
    {
      /* #30 Check if socket connection is not offline or data socket is not closed (i.e. close mode is not reset). */
      if ( (SoAd_GetModeOfSoConDyn(soConIdx, partitionIdx) != SOAD_SOCON_OFFLINE) ||
        (SoAd_GetCloseModeOfSoConDyn(soConIdx, partitionIdx) != SOAD_CLOSE_NONE) )
      {
        /* #40 Indicate that not all socket connections are closed. */
        allSoConsClosed = FALSE;

        /* #50 Check if socket connection is not requested to be closed. */
        if ( SoAd_GetCloseModeOfSoConDyn(soConIdx, partitionIdx) == SOAD_CLOSE_NONE )
        {
          /* #60 Check if no transmission nor reception is active on socket connection (if enabled). */
          if ( SoAd_SoCon_CheckForActiveOrPendingTransmit(soConIdx, partitionIdx, TRUE) == FALSE )
          {
            /* #70 Close socket connection in main function. */
            SoAd_SetCloseModeOfSoConDyn(soConIdx, SOAD_CLOSE_OFFLINE_RESET, partitionIdx);                             /* SBSW_SOAD_CSL02_CSL05 */
            SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx,
              SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, partitionIdx), partitionIdx);
          }
        }
      }
    }
  }

  return allSoConsClosed;
} /* SoAd_SoCon_CloseAllSoCons() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetSoConIdxListByBestMatchAlg()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_GetSoConIdxListByBestMatchAlg(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_SoConModeFilterType SoConModeFilter,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) SockAddrPtr,
  P2VAR(SoAd_SizeOfSoConType, AUTOMATIC, SOAD_APPL_DATA) SoConIdxListSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType                   soConIter;
  SoAd_SizeOfSoConType                 soConIdxTmp;
  SoAd_SizeOfSoConType                 soConIdxListSize = 0u;
  SoAd_SizeOfSoConGrpType              soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType              instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfBestMatchSoConIdxListType bestMatchSoConIdxListStartIdx = SoAd_GetBestMatchSoConIdxListStartIdxOfInstance(
    instanceIdx, PartitionIdx);
  SoAd_SizeOfBestMatchSoConIdxListType bestMatchSoConIdxListEndIdx = SoAd_GetBestMatchSoConIdxListEndIdxOfInstance(
    instanceIdx, PartitionIdx);
  SoAd_BestMatchPrioType               bestMatchPrio = SOAD_BEST_MATCH_NONE;
  SoAd_BestMatchPrioType               bestMatchPrioTmp;
  Std_ReturnType                       retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all socket connection of the socket connection group identified by parameter SoConIdx. */
  for ( soConIter = SoAd_GetSoConStartIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
    soConIter < SoAd_GetSoConEndIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
    soConIter++ )
  {
    /* #20 Check if socket connection filter is disabled or socket connection state is according to the filter rule. */
#if ( SOAD_TCP == STD_ON )
    if ( (SoConModeFilter == SOAD_SOCON_FILTER_DISABLED) ||
      (SoAd_GetModeOfSoConDyn(soConIter, PartitionIdx) == SOAD_SOCON_RECONNECT) )
#else
    SOAD_DUMMY_STATEMENT(SoConModeFilter); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_TCP == STD_ON */
    {
      soConIdxTmp = (SoAd_SizeOfSoConType)soConIter;

      /* #30 Get best match priority of current socket connection. */
      bestMatchPrioTmp = SoAd_SoCon_GetBestMatchPrioOfSoConIdx(soConIdxTmp, PartitionIdx, SockAddrPtr);                /* SBSW_SOAD_POINTER_FORWARD */

      /* #40 Store current socket connection if best match priority is higher than the highest priority up to now. */
      if ( bestMatchPrioTmp > bestMatchPrio )
      {
        bestMatchPrio = bestMatchPrioTmp;
        SoAd_SetSoConIdxOfBestMatchSoConIdxList(bestMatchSoConIdxListStartIdx, soConIdxTmp, PartitionIdx);             /* SBSW_SOAD_CSL02_CSL05 */
        soConIdxListSize = 1u;

        retVal = E_OK;

        /* #400 Stop iteration if best match with highest priority has been found (i.e. IP and port match). */
        if ( bestMatchPrio == SOAD_BEST_MATCH_IP_MATCH_PORT_MATCH )
        {
          break;
        }
      }
      /* #41 Store current socket connection additionally if best match priority is equal to the highest and the best
       *     match socket connection index list index is valid. */
      else if ( (bestMatchPrioTmp == bestMatchPrio) &&
        ((bestMatchSoConIdxListStartIdx + soConIdxListSize) < bestMatchSoConIdxListEndIdx) )
      {
        SoAd_SetSoConIdxOfBestMatchSoConIdxList(bestMatchSoConIdxListStartIdx + soConIdxListSize, soConIdxTmp,         /* SBSW_SOAD_CALCULATED_CHECKED_CSL03_CSL05 */
          PartitionIdx);
        soConIdxListSize++;
      }
      /* #42 Continue without any action if best match priority is lower than the highest priority up to now. */
      else
      {
        /* Nothing to do. */
      }
    }
  }

  /* #50 Return the length of the socket connection index list with the highest priorities. */
  *SoConIdxListSizePtr = soConIdxListSize;                                                                             /* SBSW_SOAD_POINTER_WRITE */

  return retVal;
} /* SoAd_SoCon_GetSoConIdxListByBestMatchAlg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_OpenSoConOnReception()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_OpenSoConOnReception(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is of type UDP (if TCP is enabled). */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    /* #20 Check if message acceptance filter is enabled. */
    if ( SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(soConGrpIdx, PartitionIdx) )
    {
      /* #30 Check if UDP listen only is disabled. */
      if ( !SoAd_IsUdpListenOnlyOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
      {
        /* #40 Check if remote is set but contains wildcards. */
        if ( ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_ANY) > 0u) &&
          ((SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) & SOAD_SOCON_MASK_NOT) == 0u) )
        {
          /* #50 Enter critical section to prevent that remote address or alive timeout is set in other context. */
          SOAD_BEGIN_CRITICAL_SECTION();

          /* #60 Update remote address. */
          /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
          SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx,             /* SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD */
            PartitionIdx), RemoteAddrPtr);
          SoAd_SetRemAddrStateDynOfSoConDyn(SoConIdx, SOAD_SOCON_IP_SET_PORT_SET, PartitionIdx);                       /* SBSW_SOAD_PARAMETER_IDX */

          /* #70 Set socket connection to online. */
          SoAd_SetModeOfSoConDyn(SoConIdx, SOAD_SOCON_ONLINE, PartitionIdx);                                           /* SBSW_SOAD_PARAMETER_IDX */

          /* #80 Set alive supervision timeout. */
          SoAd_SoCon_SetUdpAliveTimeout(SoConIdx, PartitionIdx);

          /* #90 Leave critical section. */
          SOAD_END_CRITICAL_SECTION();

          /* #100 Notify user about state change. */
          SoAd_SoCon_NotifySoConModeChg(SoConIdx, PartitionIdx, SOAD_SOCON_ONLINE);

          /* #110 Start TP reception if required and succeeds. */
          retVal = SoAd_Rx_TpStartOfReception(SoConIdx, PartitionIdx);
        }
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_OpenSoConOnReception() */

/**********************************************************************************************************************
 *  SoAd_SoCon_HandleUdpAliveTimeout()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_HandleUdpAliveTimeout(
  SoAd_SizeOfInstanceMapType InstMapIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                      elementIdx = 0u;
  uint32                      handleIdx = SOAD_INV_BUF_IDX_16;
  SoAd_SizeOfSoConType        soConIdx;
  SoAd_PartitionConfigIdxType partitionIdx = SoAd_GetPartitionSpecificInstancePartitionIdxOfInstanceMap(InstMapIdx);
  SoAd_SizeOfInstanceType     instanceIdx = SoAd_GetPartitionSpecificInstanceIdxOfInstanceMap(InstMapIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all timeouts in this main function cycle. */
  while ( SoAd_TimeoutList_CheckElements(SOAD_TIMEOUT_LIST_UDP_ALIVE, &elementIdx, &handleIdx, InstMapIdx) == E_OK )   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
     soConIdx = (SoAd_SizeOfSoConType)handleIdx;

    /* #20 Enter critical section to prevent that close mode is overwritten by any function call. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Check if socket connection is online and socket connection is not requested to be closed. */
    if ( (SoAd_GetModeOfSoConDyn(soConIdx, partitionIdx) == SOAD_SOCON_ONLINE) &&
      (SoAd_GetCloseModeOfSoConDyn(soConIdx, partitionIdx) == SOAD_CLOSE_NONE) )
    {
      /* #300 Request socket connection to be reconnected. */
      SoAd_SetCloseModeOfSoConDyn(soConIdx, SOAD_CLOSE_RECONNECT, partitionIdx);                                       /* SBSW_SOAD_INDEX_BY_FUNCTION */

      /* #301 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      /* #302 Set an event to handle socket connection reconnect in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx, instanceIdx, partitionIdx);
    }
    /* #31 Leave critical section otherwise. */
    else
    {
      SOAD_END_CRITICAL_SECTION();
    }

    /* #40 Remove timeout from list. */
    SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, soConIdx, instanceIdx, partitionIdx);
  }
} /* SoAd_SoCon_HandleUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateUdpAliveTimeout()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateUdpAliveTimeout(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                   tmpCnt = 0u;
  SoAd_SizeOfSoConGrpType  soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfInstanceType  instanceIdx = SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSocketUdpType socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Check if socket connection is of type UDP (if TCP is enabled). */
  if ( SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) )
#endif /* SOAD_TCP == STD_ON */
  {
    /* #20 Check if timeout is configured. */
    if ( SoAd_GetAliveTimeoutMaxCntOfSocketUdp(socketUdpIdx, PartitionIdx) != 0u )
    {
      /* #30 Enter critical section to prevent that timeout update process is interrupted. */
      SOAD_BEGIN_CRITICAL_SECTION();

      /* #40 Check if timeout is already running. */
      if ( SoAd_TimeoutList_GetCurrentTimeout(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx, &tmpCnt,                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
           SoAd_GetCounterOfInstanceDyn(instanceIdx, PartitionIdx), PartitionIdx) == E_OK )
      {
        /* #50 Update timeout. */
        (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_UDP_ALIVE, SoConIdx, SoAd_GetAliveTimeoutMaxCntOfSocketUdp(
            socketUdpIdx, PartitionIdx), instanceIdx, PartitionIdx);
      }

      /* #60 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();
    }
  }
} /* SoAd_SoCon_UpdateUdpAliveTimeout() */

/**********************************************************************************************************************
 *  SoAd_SoCon_UpdateRcvRemoteAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_UpdateRcvRemoteAddress(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRcvRemAddrType rcvRemAddrIdx = SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if to get received remote address is configured. */
  if ( SoAd_IsRcvRemAddrUsedOfSoCon(SoConIdx, PartitionIdx) )
  {
    /* #20 Enter critical section to prevent that received remote address buffer is read while modification. */
    SOAD_BEGIN_CRITICAL_SECTION();

    /* #30 Copy remote address to received remote address buffer. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx, PartitionIdx),         /* SBSW_SOAD_VARIABLE_POINTER_CSL03_CSL05_AND_CONST_POINTER_FORWARD */
      RemoteAddrPtr);

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION();
  }
} /* SoAd_SoCon_UpdateRcvRemoteAddress() */

#if ( (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) )
/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetLocalSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) LocalSockAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType    dummyDefaultRouter = { 0 };
  uint8                     dummyNetmask = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward request to TcpIp to get local IP address from TcpIp module. */
  /* PRQA S 310 2 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_SoCon_GetIpAddr(SoConIdx, PartitionIdx, LocalSockAddrPtr, &dummyNetmask,                                        /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    SOAD_A_P2VAR(SoAd_SockAddrType)&dummyDefaultRouter);
} /* SoAd_SoCon_GetLocalSockAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteSockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteSockAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_DATA) RemSockAddrPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy current remote address. */
  /* PRQA S 310 3 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(RemSockAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx,   /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
      PartitionIdx));
} /* SoAd_SoCon_GetRemoteSockAddr() */
#endif /* (SOAD_TCP == STD_ON) && (SOAD_VERIFYRXPDUCBK == STD_ON) */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetIpAddr()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetIpAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get local IP address from TcpIp module. */
  if ( SoAd_TcpIpApiGetIpAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx),                                   /* SBSW_SOAD_POINTER_FORWARD */
      LocalAddrPtr,
      NetmaskPtr,
      DefaultRouterPtr) == E_NOT_OK )
  {
    /* #100 Use wildcard IP address if call to TcpIp module fails. */
    /* PRQA S 310, 3305 12 */ /* MD_SoAd_PointerCastOnStruct */
#if ( SOAD_IPV6 == STD_ON )
    if ( SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx) == SOAD_AF_INET6 )
    {
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[0u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[1u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[2u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
      ((SoAd_SockAddrInet6Type*)LocalAddrPtr)->addr[3u] = SOAD_IP6ADDR_ANY;                                            /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
    else
#endif /* SOAD_IPV6 == STD_ON */
    {
      ((SoAd_SockAddrInetType*)LocalAddrPtr)->addr[0u] = SOAD_IPADDR_ANY;                                              /* SBSW_SOAD_EXPECTED_SIZE_WRITE */
    }
  }

  /* #11 Get port from local data structure. */
  /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
  ((SoAd_SockAddrInetXType*)LocalAddrPtr)->port = SoAd_SoCon_GetLocalPortDyn(sockIdx, PartitionIdx);                   /* SBSW_SOAD_POINTER_WRITE */
} /* SoAd_SoCon_GetIpAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if remote address is set and contains at least wildcards. */
  if ( SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx) <= SOAD_SOCON_IP_ANY_PORT_ANY )
  {
    /* #20 Copy remote address to provided struct. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx,      /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
      PartitionIdx));

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_SoCon_CheckAndGetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetRemoteAddrState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_GetRemoteAddrState(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrStatePtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return remote address state. */
  *RemAddrStatePtr = SoAd_GetRemAddrStateDynOfSoConDyn(SoConIdx, PartitionIdx);                                        /* SBSW_SOAD_POINTER_WRITE */

  /* #20 Copy remote address to provided struct. */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx,        /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02 */
    PartitionIdx));
} /* SoAd_SoCon_GetRemoteAddrState() */

/**********************************************************************************************************************
 *  SoAd_SoCon_CheckAndGetRcvRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_CheckAndGetRcvRemoteAddr(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRcvRemAddrType rcvRemAddrIdx = SoAd_GetRcvRemAddrIdxOfSoCon(SoConIdx, PartitionIdx);
  boolean                   ipAddrIsAny = FALSE;
  boolean                   portIsAny = FALSE;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that a reception interrupts and address becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if address is set and has no wildcards (i.e. received something from a remote entity). */
  /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
  SoAd_Util_CheckForWildcards(SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx, PartitionIdx),    /* SBSW_SOAD_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD */
    &ipAddrIsAny, &portIsAny);
  if ( (ipAddrIsAny != TRUE) && (portIsAny != TRUE) )
  {
    /* #30 Return received remote address. */
    /* PRQA S 310 1 */ /* MD_SoAd_PointerCastOnStruct */
    SoAd_Util_CopySockAddr(IpAddrPtr, SOAD_A_P2CONST(SoAd_SockAddrType)SoAd_GetAddrRcvRemAddr(rcvRemAddrIdx,           /* SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD */
        PartitionIdx));

    retVal = E_OK;
  }

  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_SoCon_CheckAndGetRcvRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_SoCon_RequestIpAddrAssignment()
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
/* PRQA S 6060 1 */ /* MD_MSR_STPAR */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SoCon_RequestIpAddrAssignment(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SockAddrInetXType    localIpAddr;
  SoAd_SockAddrInetXType    defaultRouter;
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(SoConIdx, PartitionIdx);
  SoAd_SizeOfLocalAddrType  localAddrIdx = SoAd_GetLocalAddrIdxOfSoConGrp(soConGrpIdx, PartitionIdx);
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx, PartitionIdx);
  uint8                     dummyNetmask;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Do not forward IP address request to TcpIp module if same static IP address is requested. */
  if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
  {
    /* #100 Check if IP address is unassigned. */
    if ( SoAd_GetIpAddrStateOfLocalAddrDyn(localAddrIdx, PartitionIdx) != SOAD_IPADDR_STATE_UNASSIGNED )
    {
      /* #1000 Retrieve local IP address. */
      /* PRQA S 310 4 */ /* MD_SoAd_PointerCastOnStruct */
      if ( SoAd_TcpIpApiGetIpAddr(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx),                               /* SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD */
          SOAD_A_P2VAR(SoAd_SockAddrType)&localIpAddr,
          &dummyNetmask,
          SOAD_A_P2VAR(SoAd_SockAddrType)&defaultRouter) == E_OK )
      {
        /* #10000 Compare new IP address to local IP address. */
        /* PRQA S 310, 3305 3 */ /* MD_SoAd_PointerCastOnStruct */
        if ( SoAd_Util_CompareIpAddr(SoAd_GetDomainOfLocalAddr(localAddrIdx, PartitionIdx),                            /* SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_AND_CONST_POINTER_FORWARD */
            localIpAddr.addr,
            (SOAD_A_P2VAR(SoAd_SockAddrInetXType)LocalIpAddrPtr)->addr,
            FALSE) == E_OK )
        {
          retVal = E_OK;
        }
      }
    }
  }
  /* #11 Forward request to TcpIp module otherwise. */
  if ( retVal == E_NOT_OK )
  {
    retVal = SoAd_TcpIpApiRequestIpAddrAssignment(SoAd_GetAddrIdOfLocalAddr(localAddrIdx, PartitionIdx), Type,         /* SBSW_SOAD_POINTER_FORWARD */
      LocalIpAddrPtr, Netmask, DefaultRouterPtr);
  }

  /* #20 Update local port of local static IP address if request was successful. */
  if ( retVal == E_OK )
  {
    if ( Type == SOAD_IPADDR_ASSIGNMENT_STATIC )
    {
      if ( SoAd_SoCon_GetLocalPortDyn(sockIdx, PartitionIdx) == SOAD_PORT_ANY )
      {
        /* PRQA S 310, 3305 1 */ /* MD_SoAd_PointerCastOnStruct */
        SoAd_SoCon_SetLocalPortDyn(sockIdx, PartitionIdx, ((SoAd_SockAddrInetXType*)LocalIpAddrPtr)->port);
      }
    }
  }

  return retVal;
} /* SoAd_SoCon_RequestIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_SoCon_LocalIpAddrAssignmentChg()
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
FUNC(void, SOAD_CODE) SoAd_SoCon_LocalIpAddrAssignmentChg(
  SoAd_SizeOfLocalAddrType LocalAddrIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIterType      soConIter;
  SoAd_SoConGrpIterType   soConGrpIter;
  SoAd_SizeOfSoConType    soConIdx;
  SoAd_SizeOfSoConGrpType soConGrpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set local address state. */
  SoAd_SetIpAddrStateOfLocalAddrDyn(LocalAddrIdx, State, PartitionIdx);                                                /* SBSW_SOAD_PARAMETER_IDX */

  /* #20 Iterate over all socket connection groups which are related to the local address. */
  for ( soConGrpIter = SoAd_GetSoConGrpStartIdxOfLocalAddr(LocalAddrIdx, PartitionIdx); soConGrpIter <
    SoAd_GetSoConGrpEndIdxOfLocalAddr(LocalAddrIdx, PartitionIdx); soConGrpIter++ )
  {
    /* #30 Iterate over all socket connections which are related to the socket connection group. */
    for ( soConIter = SoAd_GetSoConStartIdxOfSoConGrp(soConGrpIter, PartitionIdx); soConIter <
      SoAd_GetSoConEndIdxOfSoConGrp(soConGrpIter, PartitionIdx); soConIter++ )
    {
      soConIdx = (SoAd_SizeOfSoConType)soConIter;
      soConGrpIdx = (SoAd_SizeOfSoConGrpType)soConGrpIter;

      /* #40 Notify user about IP address state change on socket connection. */
      SoAd_SoCon_NotifyLocalIpAddrAssignmentChg(soConIdx, PartitionIdx, State);

      /* #50 Set event to handle socket connection state in main function. */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, soConIdx,
        SoAd_GetInstanceIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);

#if ( SOAD_TCP == STD_ON )
      /* #60 Overwrite close mode to prevent that socket connection is opened automatically on IP reassignment. */
      if ( SoAd_GetCloseModeOfSoConDyn(soConIdx, PartitionIdx) == SOAD_CLOSE_SOCKET_RECONNECT )
      {
        SOAD_BEGIN_CRITICAL_SECTION();

        SoAd_SoCon_SetCloseMode(soConIdx, PartitionIdx, SOAD_CLOSE_SOCKET);

        SOAD_END_CRITICAL_SECTION();
      }
#endif /* SOAD_TCP == STD_ON */
    }
  }
} /* SoAd_SoCon_LocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_SoCon_GetLocalPortDyn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(SoAd_PortType, SOAD_CODE) SoAd_SoCon_GetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PortType           localPort;
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx, PartitionIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Return local port of listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
  {
    localPort = SoAd_GetLocalPortOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx);
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Return local port of data socket otherwise. */
  {
    localPort = SoAd_GetLocalPortOfSocketDyn(SockIdx, PartitionIdx);
  }

  return localPort;
} /* SoAd_SoCon_GetLocalPortDyn() */

/**********************************************************************************************************************
 *  SoAd_SoCon_SetLocalPortDyn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_SoCon_SetLocalPortDyn(
  SoAd_SizeOfSocketType SockIdx,
  SoAd_PartitionConfigIdxType PartitionIdx,
  SoAd_PortType LocalPort)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  SoAd_SizeOfSoConType    soConStartIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx, PartitionIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConStartIdx, PartitionIdx);
#endif /* SOAD_TCP == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
  /* #10 Set local port on listen socket in case of TCP server socket (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(soConGrpIdx, PartitionIdx) &&
    !SoAd_IsTcpInitiateOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(soConGrpIdx, PartitionIdx), PartitionIdx) )
  {
    /* Optional indirection: Refer to Safe BSW assumption SoConGrp -> Socket. */
    SoAd_SetLocalPortOfSocketDyn(SoAd_GetSocketIdxOfSoConGrp(soConGrpIdx, PartitionIdx), LocalPort, PartitionIdx);     /* SBSW_SOAD_OPTIONAL_CSL03_CSL05 */
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Set local port on data socket otherwise. */
  {
    SoAd_SetLocalPortOfSocketDyn(SockIdx, LocalPort, PartitionIdx);                                                    /* SBSW_SOAD_CSL02_CSL05 */
  }
} /* SoAd_SoCon_SetLocalPortDyn() */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_SoCon.c
 *********************************************************************************************************************/
