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
/**        \file  Etm_Types.h
 *        \brief  Etm header file
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

#if !defined (ETM_TYPES_H)
# define ETM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "Etm_Cfg.h"
# include "TcpIp_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define ETM_P2V(ptrtype)   P2VAR  (ptrtype, AUTOMATIC, ETM_APPL_VAR)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define ETM_P2C(ptrtype)   P2CONST(ptrtype, AUTOMATIC, ETM_APPL_DATA) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* GID */ /* 7 Bit */
# define ETM_GID_GENERAL                   0x00u
# define ETM_GID_UDP                       0x01u
# define ETM_GID_TCP                       0x02u
# define ETM_GID_ICMP                      0x03u
# define ETM_GID_ICMPv6                    0x04u
# define ETM_GID_IP                        0x05u
# define ETM_GID_IPv6                      0x06u
# define ETM_GID_DHCP                      0x07u
# define ETM_GID_DHCPv6                    0x08u
# define ETM_GID_ARP                       0x09u
# define ETM_GID_NDP                       0x0Au
# define ETM_GID_ETH                       0x0Bu
# define ETM_GID_PHY                       0x0Cu

/* PIDs with (GID == 0x00u) */
# if (ETM_STUB_PROTOCOL_VERSION <= 0x00000005uL) /* Version 0.5 */
#  define ETM_PID_GET_VERSION              0x00u
#  define ETM_PID_START_TEST               0x01u
#  define ETM_PID_END_TEST                 0x02u
# else
#  define ETM_PID_GET_VERSION              0x01u
#  define ETM_PID_START_TEST               0x02u
#  define ETM_PID_END_TEST                 0x03u
# endif

/* PIDs with (GID == 0x01u) */
# if (ETM_STUB_PROTOCOL_VERSION <= 0x00000005uL) /* Version 0.5 */
#  define ETM_PID_UDP_CLOSE_SOCKET         0x03u /* mandatory */
#  define ETM_PID_UDP_CREATE_AND_BIND      0x04u /* mandatory */
#  define ETM_PID_UDP_SEND_DATA            0x05u /* mandatory */
#  define ETM_PID_UDP_RECEIVE_AND_FORWARD  0x06u /* mandatory */
#  define ETM_PID_UDP_CONFIGURE_SOCKET     0x09u /* mandatory */
#  define ETM_PID_UDP_SHUTDOWN             0x0Au /* extension */
# else
#  define ETM_PID_UDP_CLOSE_SOCKET         0x00u /* mandatory */
#  define ETM_PID_UDP_CREATE_AND_BIND      0x01u /* mandatory */
#  define ETM_PID_UDP_SEND_DATA            0x02u /* mandatory */
#  define ETM_PID_UDP_RECEIVE_AND_FORWARD  0x03u /* mandatory */
#  define ETM_PID_UDP_CONFIGURE_SOCKET     0x06u /* mandatory */
#  define ETM_PID_UDP_SHUTDOWN             0x07u /* extension */
# endif

/* PIDs with (GID == 0x02u) */
# if (ETM_STUB_PROTOCOL_VERSION <= 0x00000005uL) /* Version 0.5 */
#  define ETM_PID_TCP_CLOSE_SOCKET         0x03u /* mandatory */
#  define ETM_PID_TCP_CREATE_AND_BIND      0x04u /* mandatory */
#  define ETM_PID_TCP_SEND_DATA            0x05u /* mandatory */
#  define ETM_PID_TCP_RECEIVE_AND_FORWARD  0x06u /* mandatory */
#  define ETM_PID_TCP_LISTEN_AND_ACCEPT    0x07u /* mandatory */
#  define ETM_PID_TCP_CONNECT              0x08u /* mandatory */
#  define ETM_PID_TCP_CONFIGURE_SOCKET     0x09u /* mandatory */
#  define ETM_PID_TCP_SHUTDOWN             0x0Au /* extension */
# else
#  define ETM_PID_TCP_CLOSE_SOCKET         0x00u /* mandatory */
#  define ETM_PID_TCP_CREATE_AND_BIND      0x01u /* mandatory */
#  define ETM_PID_TCP_SEND_DATA            0x02u /* mandatory */
#  define ETM_PID_TCP_RECEIVE_AND_FORWARD  0x03u /* mandatory */
#  define ETM_PID_TCP_LISTEN_AND_ACCEPT    0x04u /* mandatory */
#  define ETM_PID_TCP_CONNECT              0x05u /* mandatory */
#  define ETM_PID_TCP_CONFIGURE_SOCKET     0x06u /* mandatory */
#  define ETM_PID_TCP_SHUTDOWN             0x07u /* extension */
# endif

/* PIDs with (GID == 0x03u) */
# define ETM_PID_ICMP_ECHO_REQUEST         0x00u /* extension */

/* PIDs with (GID == 0x04u) */
# define ETM_PID_ICMPV6_ECHO_REQUEST       0x00u /* extension */

/* PIDs with (GID == 0x05u) */
# define ETM_PID_IP_STATIC_ADDRESS         0x00u /* extension */
# define ETM_PID_IP_STATIC_ROUTE           0x01u /* extension */

/* PIDs with (GID == 0x06u) */
# define ETM_PID_IPV6_STATIC_ADDRESS       0x00u /* extension */
# define ETM_PID_IPV6_STATIC_ROUTE         0x01u /* extension */

/* PIDs with (GID == 0x07u) */
# define ETM_PID_DHCP_INIT_DHCP_CLIENT     0x00u /* extension */
# define ETM_PID_DHCP_STOP_DHCP_CLIENT     0x01u /* extension */
# define ETM_PID_DHCP_SET_DHCP_OPTION      0x02u /* extension */

/* PIDs with (GID == 0x08u) */
# define ETM_PID_DHCPV6_INIT_DHCP_CLIENT   0x00u /* extension */
# define ETM_PID_DHCPV6_STOP_DHCP_CLIENT   0x01u /* extension */
# define ETM_PID_DHCPV6_SET_DHCP_OPTION    0x02u /* extension */

/* PIDs with (GID == 0x0Au) */
# define ETM_PID_NDP_CLEAR_CACHE           0xFFu

/* PIDs with (GID == 0x0Bu) */
# define ETM_PID_ETH_INTERFACE_UP          0x00u /* extension */
# define ETM_PID_ETH_INTERFACE_DOWN        0x01u /* extension */

/* PIDs with (GID == 0x0Cu) */
# define ETM_PID_PHY_READ_SIGNAL_QUALITY   0x00u /* extension */
# define ETM_PID_PHY_READ_DIAG_RESULT      0x01u /* extension */
# define ETM_PID_PHY_ACTIVATE_TEST_MODE    0x02u /* extension */
# define ETM_PID_PHY_SET_PHY_TX_MODE       0x03u /* extension */

typedef uint8 Etm_ResultIdType;
/* Standard Results */
# define ETM_RID_E_OK       0x00u /* E_OK */
# define ETM_RID_E_NOK      0x01u /* E_NOT_OK */
/* Testability Specific Results */
# define ETM_RID_E_NTF      0xFFu /* Service Primitive not found */
# define ETM_RID_E_PEN      0xFEu /* Service Primitive pending */
# define ETM_RID_E_ISB      0xFDu /* Insuffizient buffer size */
# define ETM_RID_E_INV      0xFCu /* Invalid input or parameter */
/* Service Primitive Specific Results */
# define ETM_RID_E_ISD      0xEFu /* Invalid SocketId */
# define ETM_RID_E_UCS      0xEEu /* Unable to create socket or no free socket */
# define ETM_RID_E_UBS      0xEDu /* Unable to bind socket, port taken */
# define ETM_RID_E_IIF      0xECu /* Invalid network or virtual interface */
# define ETM_RID_E_TCP_PNA  0xEBu /* TCP error: "precedence not allowed" */
# define ETM_RID_E_TCP_FSU  0xEAu /* TCP error: "foreign socket unspecified" */
# define ETM_RID_E_TCP_ILP  0xE9u /* TCP error: "connection illegal for this process */
# define ETM_RID_E_TCP_INR  0xE8u /* TCP error: "insufficient resources" */
# define ETM_RID_E_TCP_CAE  0xE7u /* TCP error: "connection already exists" */
# define ETM_RID_E_TCP_COC  0xE6u /* TCP error: "connection closing" */
# define ETM_RID_E_TCP_CNE  0xE5u /* TCP error: "connection does not exist" */
# define ETM_RID_E_TCP_CRE  0xE4u /* TCP error: "connection reset" */
# define ETM_RID_E_TCP_CAT  0xE3u /* TCP error: "connection aborted due to user */
# define ETM_RID_E_TCP_COR  0xE2u /* TCP error: "connection refused" */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/****************************************************************************************************
 *  ENUMS
 ****************************************************************************************************/

typedef enum
{
  ETM_CMD_CHAN_INACTIVE      = 0u,  /* CHANNEL IS DEACTIVATED AND IS NOT USED !!! */
  ETM_CMD_CHAN_DO_GETSOCKET  = 1u,  /* Call GetSocket next */
  ETM_CMD_CHAN_DO_BIND       = 2u,  /* Call Bind next */
  ETM_CMD_CHAN_DO_LISTEN     = 3u,  /* Call Listen next (TCP ONLY) */
  ETM_CMD_CHAN_DO_RX_BUFFER  = 4u,  /* Call ChangeParameter next (TCP ONLY) */
  ETM_CMD_CHAN_DO_TX_BUFFER  = 5u,  /* Call ChangeParameter next (TCP ONLY) */
  ETM_CMD_CHAN_ACTIVE        = 6u   /* CHANNEL IS READY TO USE */
} Etm_CmdChanStateType;

/****************************************************************************************************
 *  TYPES
 ****************************************************************************************************/

typedef uint8 *Etm_ConfigType;

typedef struct
{
  TcpIp_SocketIdType SocketId;
  Etm_CmdChanStateType ChannelState;
} Etm_CommandSocketType;

typedef struct
{
  TcpIp_SocketIdType SocketId;
  boolean RecvFwdActive;
  uint32 RecvFwdDropCount;
  uint16 RecvFwdMaxForward;
  uint16 RecvFwdMaxLength;
} Etm_TestSocketType;

typedef struct
{
  uint16 StartIdx;
  uint16 EndIdx; /* StartIdx and EndIdx is the position and length of the interface identifier within the byte array Etm_InterfaceNames[] */
  uint8 Index; /* Index is either a ComM UserIdentifier within Etm_EthInterfaces[] or an EthTrcv TrcvIdx within Etm_PhyInterfaces[] */
} Etm_InterfaceType;

#endif /* ETM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Etm_Types.h
 *********************************************************************************************************************/
