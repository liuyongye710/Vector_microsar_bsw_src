/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Vtt_LL_IrqHandler.c
 *        \brief  Lower layer implementation of interrupt handler
 *
 *      \details  Implementation of lower layer part of the interrupt handler.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Vtt_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Vtt_LL.h
 *********************************************************************************************************************/

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

#define ETH_30_VTT_LL_IRQ_HANDLER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Vtt_IrqHandler_Int.h"
#include "Eth_30_Vtt_LL.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETH_30_VTT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  Eth_30_Vtt_RxIrqHandler
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_RxIrqHandler(
  uint8 CtrlIdx)
{
  Eth_RxStatusType RxStatus;
  /* #10 RX on Q0 */
  do
  {
	Eth_30_Vtt_LL_SetRxEvents(CtrlIdx);
	if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE) 
	{
		Eth_30_Vtt_Receive(CtrlIdx, &RxStatus);
	}
	else 
	{
		Eth_30_Vtt_ReceiveFifo(CtrlIdx, 0u, &RxStatus);
	}
  }
  while(RxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE);
} /* Eth_30_Vtt_RxIrqHandler() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_RxIrqHandlerQ1
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_RxIrqHandlerQ1(
  uint8 CtrlIdx)
{
  Eth_RxStatusType RxStatus;
  /* #10 RX on Q1 */
  do
  {
	Eth_30_Vtt_LL_SetRxEvents(CtrlIdx);
	if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE) 
	{
		Eth_30_Vtt_Receive(CtrlIdx, &RxStatus);
	}
	else 
	{
		Eth_30_Vtt_ReceiveFifo(CtrlIdx, 1u, &RxStatus);
	}
  }
  while(RxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE);
} /* Eth_30_Vtt_RxIrqHandlerQ1() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_RxIrqHandlerQ2
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_RxIrqHandlerQ2(
  uint8 CtrlIdx)
{
  Eth_RxStatusType RxStatus;
  /* #10 RX on Q2 */
  do
  {
	Eth_30_Vtt_LL_SetRxEvents(CtrlIdx);
	if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE) 
	{
		Eth_30_Vtt_Receive(CtrlIdx, &RxStatus);
	}
	else 
	{
		Eth_30_Vtt_ReceiveFifo(CtrlIdx, 2u, &RxStatus);
	}
  }
  while(RxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE);
} /* Eth_30_Vtt_RxIrqHandlerQ2() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_RxIrqHandlerQ3
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_RxIrqHandlerQ3(
  uint8 CtrlIdx)
{
  Eth_RxStatusType RxStatus;
  /* #10 RX on Q3 */
  do
  {
	Eth_30_Vtt_LL_SetRxEvents(CtrlIdx);
	if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE) 
	{
		Eth_30_Vtt_Receive(CtrlIdx, &RxStatus);
	}
	else 
	{
		Eth_30_Vtt_ReceiveFifo(CtrlIdx, 3u, &RxStatus);
	}
  }
  while(RxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE);
} /* Eth_30_Vtt_RxIrqHandlerQ1() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_TxIrqHandler
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_TxIrqHandler(
  uint8 CtrlIdx)
{
  /* #10 TX on Q0 */
  Eth_30_Vtt_LL_SetTxEvents(CtrlIdx);
  if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE)
  {
    Eth_30_Vtt_TxConfirmation(CtrlIdx);
  }
  else
  {
    Eth_30_Vtt_TxConfirmationFifo(CtrlIdx, 0u);
  }
} /* Eth_30_Vtt_TxIrqHandler() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_TxIrqHandlerQ1
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_TxIrqHandlerQ1(
  uint8 CtrlIdx)
{
  /* #10 TX on Q1 */
  Eth_30_Vtt_LL_SetTxEvents(CtrlIdx);
  if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE)
  {
    Eth_30_Vtt_TxConfirmation(CtrlIdx);
  }
  else
  {
    Eth_30_Vtt_TxConfirmationFifo(CtrlIdx, 1u);
  }
} /* Eth_30_Vtt_TxIrqHandlerQ1() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_TxIrqHandlerQ2
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_TxIrqHandlerQ2(
  uint8 CtrlIdx)
{
  /* #10 TX on Q2 */
  Eth_30_Vtt_LL_SetTxEvents(CtrlIdx);
  if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE)
  {
    Eth_30_Vtt_TxConfirmation(CtrlIdx);
  }
  else
  {
    Eth_30_Vtt_TxConfirmationFifo(CtrlIdx, 2u);
  }
} /* Eth_30_Vtt_TxIrqHandlerQ2() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_TxIrqHandlerQ3
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_TxIrqHandlerQ3(
  uint8 CtrlIdx)
{
  /* #10 TX on Q3 */
  Eth_30_Vtt_LL_SetTxEvents(CtrlIdx);
  if (Eth_30_Vtt_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(CtrlIdx) == FALSE)
  {
    Eth_30_Vtt_TxConfirmation(CtrlIdx);
  }
  else
  {
    Eth_30_Vtt_TxConfirmationFifo(CtrlIdx, 3u);
  }
} /* Eth_30_Vtt_TxIrqHandlerQ1() */

#define ETH_30_VTT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL_IrqHandler.c
 *********************************************************************************************************************/

