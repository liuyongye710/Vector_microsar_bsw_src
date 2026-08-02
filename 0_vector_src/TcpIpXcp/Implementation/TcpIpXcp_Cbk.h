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
 *         File:  TcpIpXcp_Cbk.h
 *    Component:  TcpIpXcp Callback Header
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Callback header of the XCP on TcpIp Transport Layer
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

#if (!defined TCPIPXCP_CBK_H_)
# define TCPIPXCP_CBK_H_

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "ComStack_Types.h"            /* Include standard types */
#include "TcpIpXcp_Cfg.h"
#if ( TCPIPXCP_MODE_CHG_API == STD_ON ) /* COV_TCPIPXCP_UNSUPPORTED_FEATURE */
#include "SoAd.h"
#endif

/**************************************************************************************************
* Prototypes of callback functions
**************************************************************************************************/

#define TCPIPXCP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Xcp_SoAdRxIndication()
 *********************************************************************************************************************/
/*! \brief       RxIndication function of XCP transport layer
 *  \details     Every time the XCP Transport Layer receives a XCP CTO Packet this function has to be called. 
 *  \param[in]   RxPduId                 The XCP pdu id.
 *  \param[in]   PduInfoPtr              pointer of received XCP command, must not be NULL_PTR.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) Xcp_SoAdRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, TCPIPXCP_APPL_DATA) PduInfoPtr);

/**********************************************************************************************************************
 *  Xcp_SoAdTxConfirmation()
 *********************************************************************************************************************/
/*! \brief       TxConfirmation function of XCP transport layer
 *  \details     Xcp_SoAdTxConfirmation confirmes the successful transmission of the previous message.
 *               Xcp_SoAdTxConfirmation transmits pending data acquisition messages.
 *  \param[in]   CanTxPduId              PDU id of the message.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) Xcp_SoAdTxConfirmation(PduIdType TxPduId);

#if ( TCPIPXCP_MODE_CHG_API == STD_ON ) /* COV_TCPIPXCP_UNSUPPORTED_FEATURE */
/**********************************************************************************************************************
 *  Xcp_SoConModeChg()
 *********************************************************************************************************************/
/*! \brief       Informs the transport layer about connection changes.
 *  \details     -
 *  \param[in]   SoConId                 Id of the connection.
 *  \param[in]   Mode                    The change state of the connection.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if TCPIPXCP_MODE_CHG_API == STD_ON.
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) Xcp_SoConModeChg(SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode);
#endif

#define TCPIPXCP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
  /* TCPIPXCP_CBK_H_ */
