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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TcpIpXcp_Types.h
 *    Component:  TcpIpXcp Types Header
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implementation of XCP over TcpIp based on Vector AUTOSAR Stack
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

#if (!defined TCPIPXCP_TYPES_H_)
# define TCPIPXCP_TYPES_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "SoAd_Types.h"

/**********************************************************************************************************************
 *  Type definitions
 *********************************************************************************************************************/
#define TCPIPXCP_PROTOCOL_UDP 0
#define TCPIPXCP_PROTOCOL_TCP 1

 /* Keyword macros */
# if !defined (STATIC) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
#  define STATIC static
# endif

# if !defined (INLINE) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
#  define INLINE
# endif

# if !defined (LOCAL_INLINE) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
#  define LOCAL_INLINE INLINE STATIC
# endif

# if !defined (TCPIPXCP_LOCAL) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
#  define TCPIPXCP_LOCAL STATIC
# endif

# if !defined (TCPIPXCP_LOCAL_INLINE) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
#  define TCPIPXCP_LOCAL_INLINE LOCAL_INLINE
# endif



typedef uint16 TcpIpXcp_TimeoutTimerType;

typedef enum
{
  TCPIPXCP_SET_OFFLINE = 0, /*<! TcpIpXcp is set to offline mode and can not send frames. */
  TCPIPXCP_SET_ONLINE /*<! TcpIpXcp is set to online mode, frame transmission is resumed. */
} TcpIpXcp_PduSetModeType;

typedef struct
{
  PduIdType RxPduId; /*<! The id of the received frame. */
  PduIdType SoAdTxPduId; /*<! The id of the frame to transmit. */
  PduIdType TxConfPduId; /*<! The id of the tx confirmation. */
  SoAd_SoConIdType SoConId; /*<! The socket connection id. */
} TcpIpXcp_XcpPduType;

typedef struct
{
  P2CONST(TcpIpXcp_XcpPduType, TYPEDEF, TCPIPXCP_PBCFG) TcpIpXcp_XcpPduPtr;
} TcpIpXcp_ConfigType;


#endif
  /* TCPIPXCP_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TcpIpXcp_Types.h
 *********************************************************************************************************************/
