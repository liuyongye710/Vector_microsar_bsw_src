/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: whole file
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration. The template code is
 *  incomplete and only intended for providing a signature and an empty implementation. It is neither intended nor
 *  qualified for use in series production without applying suitable quality measures. The template code must be
 *  completed as described in the instructions given within this file and/or in the TechnicalReference. The completed
 *  implementation must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before its use.
 *********************************************************************************************************************/

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
/**        \file  Appl_Etm.c
 *        \brief  Etm source file
 *
 *      \details  Demo application of the Etm (Ethernet Testability Module) module. This module implements the
 *                AUTOSAR Testability Protocol and Service Primitives protocol for interaction with external testers.
 *
 *********************************************************************************************************************/

#define APPL_ETM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Appl_Etm.h"
#include "Etm_Lcfg.h"
#include "ComM.h"
#include "TcpIp.h"
#include "TcpIp_Tcp.h"
#include "TcpIp_Lcfg.h"
#include "TcpIp_Priv.h"

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

uint16 ApplEtm_PendingCommandId = 0u;
uint16 ApplEtm_PendingCounter = 0u;
uint16 ApplEtm_LastCommandId = 0u;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
Etm_ResultIdType ApplEtm_HandleTcpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr);
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
Etm_ResultIdType ApplEtm_HandleDhcpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr);
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
Etm_ResultIdType ApplEtm_HandleArpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr);
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
Etm_ResultIdType ApplEtm_HandleEthServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr);
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
Etm_ResultIdType ApplEtm_HandleUserServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr);
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
# if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
Std_ReturnType ApplEtm_VGetTcpIpLocalAddrIdFromData(
  uint32 DataLength,
  uint8* DataPtr,
  uint8* TcpIpLocalAddrId);
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_HandleTcpServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_HandleTcpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE_TCP
#  error "Appl_Etm: ApplEtm_HandleTcpServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

#  if (ETM_TCP_ENABLED == STD_ON)
  switch(Pid)
  {
    case ETM_PID_TCP_SHUTDOWN:
      resultId = ETM_RID_E_NOK;
      if(DataLength >= 3u)
      {
        uint16 socketId;
        socketId  = (uint16)(((uint16)DataPtr[0u]) << 8u);
        socketId |= (uint16) ((uint16)DataPtr[1u]);

        (void)TcpIp_Close((TcpIp_SocketIdType)socketId, FALSE);

        resultId = ETM_RID_E_OK;
      }
      break;
    case 0xF5u: /* CANoe Service Primitive: TCP_GET_STATE */
      resultId = ETM_RID_E_NOK;
      if(DataLength >= 2u)
      {
        uint16 socketId;
        socketId  = (uint16)(((uint16)DataPtr[0u]) << 8u);
        socketId |= (uint16) ((uint16)DataPtr[1u]);

        switch(TcpIp_GetSockStateOfSocketTcpDyn(TCPIP_SOCKET_IDX_TO_TCP_IDX(TCPIP_SOCKET_ID_TO_IDX((TcpIp_SocketIdType)socketId))))
        {
          case TCPIP_TCP_SOCK_STATE_LISTEN:
            *ResponseBufferPtr = 0x01u;
            break;
          case TCPIP_TCP_SOCK_STATE_SYNSENT:
            *ResponseBufferPtr = 0x02u;
            break;
          case TCPIP_TCP_SOCK_STATE_SYNRCVD:
            *ResponseBufferPtr = 0x03u;
            break;
          case TCPIP_TCP_SOCK_STATE_ESTABLISHED:
            *ResponseBufferPtr = 0x04u;
            break;
          case TCPIP_TCP_SOCK_STATE_CLOSEWAIT:
            *ResponseBufferPtr = 0x05u;
            break;
          case TCPIP_TCP_SOCK_STATE_LASTACK:
            *ResponseBufferPtr = 0x08u;
            break;
          case TCPIP_TCP_SOCK_STATE_FINWAIT1:
            *ResponseBufferPtr = 0x06u;
            break;
          case TCPIP_TCP_SOCK_STATE_FINWAIT2:
            *ResponseBufferPtr = 0x09u;
            break;
          case TCPIP_TCP_SOCK_STATE_CLOSING:
            *ResponseBufferPtr = 0x07u;
            break;
          case TCPIP_TCP_SOCK_STATE_TIMEWAIT:
            *ResponseBufferPtr = 0x0Au;
            break;
          case TCPIP_TCP_SOCK_STATE_CLOSED:
            *ResponseBufferPtr = 0x00u;
            break;
          default:
            /* invalid */
            *ResponseBufferPtr = 0xFFu;
            break;
        }

        *ResponseBufferLength = 1u;
        resultId = ETM_RID_E_OK;
      }
      break;
    default:
      /* Unknown PID */
      break;
  }
#  endif
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_HandleDhcpServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_HandleDhcpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE_DHCP
#  error "Appl_Etm: ApplEtm_HandleDhcpServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(Pid)
  {
    case ETM_PID_DHCP_INIT_DHCP_CLIENT:
      resultId = ETM_RID_E_NOK;
#  if (ETM_IPV4_ENABLED == STD_ON)
#   if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
      {
        TcpIp_LocalAddrIdType locAddrId;
        resultId = ETM_RID_E_NOK;

        if(ApplEtm_VGetTcpIpLocalAddrIdFromData(DataLength, DataPtr, &locAddrId) == E_OK)
        {
          /* Release the addresses first is for robustness reasons. */
          (void)TcpIp_ReleaseSpecificIpAddrAssignment(locAddrId, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL);
          (void)TcpIp_ReleaseSpecificIpAddrAssignment(locAddrId, TCPIP_IPADDR_ASSIGNMENT_DHCP);
          (void)TcpIp_RequestIpAddrAssignment(locAddrId, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL, NULL_PTR, 0u, NULL_PTR);
          if(TcpIp_RequestIpAddrAssignment(locAddrId, TCPIP_IPADDR_ASSIGNMENT_DHCP, NULL_PTR, 0u, NULL_PTR) == E_OK)
          {
            resultId = ETM_RID_E_OK;
          }
        }
      }
#   endif
#  endif
      break;
    case ETM_PID_DHCP_STOP_DHCP_CLIENT:
      resultId = ETM_RID_E_NOK;
#  if (ETM_IPV4_ENABLED == STD_ON)
#   if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
      {
        uint32_least idx;
        resultId = ETM_RID_E_OK;

        /* This is a temporary workaround to release all requested addresses. */
        for(idx = 0u; idx < ETM_NUMBER_DHCP_INTERFACES; idx++)
        {
          (void)TcpIp_ReleaseSpecificIpAddrAssignment(Etm_DhcpInterfaces[idx].Index, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL);
          if(TcpIp_ReleaseSpecificIpAddrAssignment(Etm_DhcpInterfaces[idx].Index, TCPIP_IPADDR_ASSIGNMENT_DHCP) == E_NOT_OK)
          {
            resultId = ETM_RID_E_NOK;
          }
        }
      }
#   endif
#  endif
      break;
    default:
      /* Unknown PID */
      break;
  }
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_HandleArpServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_HandleArpServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE_ARP
#  error "Appl_Etm: ApplEtm_HandleArpServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(Pid)
  {
    case 0xFFu: /* CANoe Service Primitive: ARP_CLEAR_CACHE */
      resultId = ETM_RID_E_NOK;
#  if ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4))
      if(TcpIp_ClearARCache((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4) == E_OK)
      {
        resultId = ETM_RID_E_OK;
      }
#  endif
      break;
    case 0xFDu: /* CANoe Service Primitive: ADD_STATIC_ARP_TABLE_ENTRY */
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;
      break;
    case 0xFCu: /* CANoe Service Primitive: DELETE_STATIC_ARP_TABLE_ENTRY */
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;
      break;
    case 0xFBu: /* CANoe Service Primitive: SET_TIMEOUT_FOR_DYNAMIC_ARP_TABLE */
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;
      break;
    case 0xFAu: /* CANoe Service Primitive: CLEAR_TIMEOUT_FOR_DYNAMIC_ARP_TABLE */
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;
      break;
    default:
      /* Unknown PID */
      break;
  }
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_HandleEthServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_HandleEthServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE_ETH
#  error "Appl_Etm: ApplEtm_HandleEthServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(Pid)
  {
    case ETM_PID_ETH_INTERFACE_UP:
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;

#  if ((ETM_IPV4_ENABLED == STD_ON) && (defined ETM_TCPIP_LOCAL_ADDRESS_IDV4))
      /* This is a temporary workaround to simulate an interface restart.
       * If the sequence 'interface down' 'interface up' occures the local addresses gets re-requested to simulate an interface restart.
       * Most tests use the preferred  sequence calling 'dhcp client init' before calling 'interface up'. */
      if(ApplEtm_LastCommandId == 0x0B01u)
      {
        /* Release the addresses first is for robustness reasons. */
        (void)TcpIp_ReleaseSpecificIpAddrAssignment((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL);
        (void)TcpIp_ReleaseSpecificIpAddrAssignment((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4, TCPIP_IPADDR_ASSIGNMENT_DHCP);
        /* Simulate an interface restart while re-requesting the local addresses. */
        (void)TcpIp_RequestIpAddrAssignment((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4, TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL, NULL_PTR, 0u, NULL_PTR);
        (void)TcpIp_RequestIpAddrAssignment((TcpIp_LocalAddrIdType)ETM_TCPIP_LOCAL_ADDRESS_IDV4, TCPIP_IPADDR_ASSIGNMENT_DHCP, NULL_PTR, 0u, NULL_PTR);
      }
#  endif

      break;
    case ETM_PID_ETH_INTERFACE_DOWN:
      /* Ignore this Service Primitive */
      resultId = ETM_RID_E_OK;
      break;
    default:
      /* Unknown PID */
      break;
  }
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_HandleUserServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_HandleUserServicePrimitive(
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE_USER
#  error "Appl_Etm: ApplEtm_HandleUserServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(Pid)
  {
#  if defined ETM_COMM_ETH_USER
    case 0xFFu: /* User PID */
      if(ApplEtm_PendingCommandId != 0u)
      {
        resultId = ETM_RID_E_PEN;
      }
      else
      {
        (void)ComM_RequestComMode((ComM_UserHandleType)ETM_COMM_ETH_USER, COMM_NO_COMMUNICATION);
        ApplEtm_PendingCommandId = 0x7FFFu; /* user defined reboot primitive */ /* GID: 0x7Fu, PID: 0xFFu */
        ApplEtm_PendingCounter = 20u; /* wait 20 main function cycles until com mode is requested in main function again */
        resultId = ETM_RID_E_OK;
      }
      break;
#  endif
    default:
      /* Unknown PID */
      break;
  }
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
# if (ETM_USE_DHCP_PRIMITIVES == STD_ON)
Std_ReturnType ApplEtm_VGetTcpIpLocalAddrIdFromData(
  uint32 DataLength,
  uint8* DataPtr,
  uint8* TcpIpLocalAddrId)
{
  Std_ReturnType Result;

  uint16 InterfaceNameLength = 0u;

  if(DataLength >= 2u)
  {
    Result = E_OK;
    InterfaceNameLength  = (uint16)(((uint16)DataPtr[0u]) << 8u);
    InterfaceNameLength |= (uint16) ((uint16)DataPtr[1u]);
  }

  if(Result == E_OK)
  {
    Result = E_NOT_OK;

    /* check interface min length */
    if(InterfaceNameLength > 4u)
    {
      uint16 Idx;
      uint16 IdxInterfaces;

      for(IdxInterfaces = 0u;
          IdxInterfaces < ETM_NUMBER_DHCP_INTERFACES;
          IdxInterfaces++)
      {
        boolean InterfaceFound = FALSE;

        /* check interface length */
        if(InterfaceNameLength == (Etm_DhcpInterfaces[IdxInterfaces].EndIdx - Etm_DhcpInterfaces[IdxInterfaces].StartIdx))
        {
          InterfaceFound = TRUE;

          for(Idx = 0u;
              Idx < (Etm_DhcpInterfaces[IdxInterfaces].EndIdx - Etm_DhcpInterfaces[IdxInterfaces].StartIdx);
              Idx++)
          {
            if(Etm_InterfaceNames[Idx + Etm_DhcpInterfaces[IdxInterfaces].StartIdx] != DataPtr[Idx + 2u /* text length field */])
            {
              InterfaceFound = FALSE;
              break;
            }
          }
        }

        if(InterfaceFound == TRUE)
        {
          *TcpIpLocalAddrId = Etm_DhcpInterfaces[IdxInterfaces].Index;
          Result = E_OK;
          break;
        }
      }
    }
  }

  return Result;
}
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETM_ENABLE_APPL_USER_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_UndefinedServicePrimitive()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_UndefinedServicePrimitive(
  uint16 Gid,
  uint16 Pid,
  uint32 DataLength,
  uint8* DataPtr,
  uint16* ResponseBufferLength,
  uint8* ResponseBufferPtr)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE
#  error "Appl_Etm: ApplEtm_UndefinedServicePrimitive() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;
  *ResponseBufferLength = 0u;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(Gid)
  {
    case ETM_GID_GENERAL:
      break;
    case ETM_GID_UDP:
      break;
    case ETM_GID_TCP:
      resultId = ApplEtm_HandleTcpServicePrimitive(Pid, DataLength, DataPtr, ResponseBufferLength, ResponseBufferPtr);
      break;
    case ETM_GID_ICMP:
      break;
    case ETM_GID_ICMPv6:
      break;
    case ETM_GID_IP:
      break;
    case ETM_GID_IPv6:
      break;
    case ETM_GID_DHCP:
      resultId = ApplEtm_HandleDhcpServicePrimitive(Pid, DataLength, DataPtr, ResponseBufferLength, ResponseBufferPtr);
      break;
    case ETM_GID_DHCPv6:
      break;
    case ETM_GID_ARP:
      resultId = ApplEtm_HandleArpServicePrimitive(Pid, DataLength, DataPtr, ResponseBufferLength, ResponseBufferPtr);
      break;
    case ETM_GID_NDP:
      break;
    case ETM_GID_ETH:
      resultId = ApplEtm_HandleEthServicePrimitive(Pid, DataLength, DataPtr, ResponseBufferLength, ResponseBufferPtr);
      break;
    case ETM_GID_PHY:
      break;
    case 0x7Fu: /* User GID */
      resultId = ApplEtm_HandleUserServicePrimitive(Pid, DataLength, DataPtr, ResponseBufferLength, ResponseBufferPtr);
      break;
    default:
      /* Unknown GID */
      /* May be a user defined service primitive */
      break;
  }

  ApplEtm_LastCommandId = (uint16)((uint16)(Gid << 8u) | Pid);
# endif

  return resultId;
}
#endif

#if (ETM_ENABLE_APPL_INIT_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_InitFunction()
 *********************************************************************************************************************/
void ApplEtm_InitFunction(void)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE
#  error "Appl_Etm: ApplEtm_InitFunction() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  ApplEtm_PendingCommandId = 0u;
  ApplEtm_PendingCounter = 0u;
  ApplEtm_LastCommandId = 0u;
# endif
}
#endif

#if (ETM_ENABLE_APPL_MAIN_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  ApplEtm_MainFunction()
 *********************************************************************************************************************/
Etm_ResultIdType ApplEtm_MainFunction(void)
{
# ifndef ETM_DISABLE_APPL_ERRORDIRECTIVE
#  error "Appl_Etm: ApplEtm_MainFunction() needs to be implemented! An example for the CANoe TC8 tests is given in the template."
# endif

  Etm_ResultIdType resultId = ETM_RID_E_NTF;

# if ETM_ENABLE_APPL_EXAMPLE_CODE
  // !!! EXAMPLE CODE !!! THIS IS A CANOE TC8 EXAMPLE INTEGRATION !!!

  switch(ApplEtm_PendingCommandId)
  {
#  if defined ETM_COMM_ETH_USER
    case 0x7FFFu: /* user defined reboot primitive */
      if(ApplEtm_PendingCounter > 0u)
      {
        ApplEtm_PendingCounter--;
        resultId = ETM_RID_E_PEN; /* as long as this function returns ETM_RID_E_PEN the Etm_MainFunction is paused */
      }
      else
      {
        (void)ComM_RequestComMode((ComM_UserHandleType)ETM_COMM_ETH_USER, COMM_FULL_COMMUNICATION);
        ApplEtm_PendingCommandId = 0u;
        ApplEtm_PendingCounter = 0u;
        resultId = ETM_RID_E_OK;
      }
      break;
#  endif
    default:
      /* Unknown CommandId */
      break;
  }
# endif

  return resultId;
}
#endif

/**********************************************************************************************************************
 *  END OF FILE: Appl_Etm.c
 *********************************************************************************************************************/
