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
/*!        \file  Eth_30_Vtt_IrqHandler_Int.h
 *        \brief  Private header file of IRQ sub-module.
 *
 *      \details  -
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Vtt.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Vtt.h
 *********************************************************************************************************************/

/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_VTT_IRQ_HANDLER_INT_H)
# define ETH_30_VTT_IRQ_HANDLER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Vtt_LL_IrqHandler.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined(ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE                        LOCAL_INLINE
# endif /* ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE */

# define ETH_30_VTT_IRQ_HANDLER_INT_MAX_EVENT_FLAG_IDX               (15u)
/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

# define ETH_30_VTT_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the descriptor ring related to the highest priority event pending and clears the event
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the descriptor ring related to the highest priority event pending
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \param[out]   bitMaskPtr    Bit mask that can be used to clear the event
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetHighestPrioPendingEventDescrRing(
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) bitMaskPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_ClearPendingEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Clears the event in the given events variable according to the given bit mask
 *  \details      -
 *  \param[in]    eventsPtr     Bit mask having bits set representing an event
 *  \param[out]   bitMaskPtr    Bit mask that to clear the event
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \synchronous  TRUE
 *  \pre          -
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_ClearPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
        uint16                        bitMask);

/**********************************************************************************************************************
 *  Eth_30_Vtt_SetRxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an RX event for the given reception descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller.
 *                              [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx  Identifier of the reception descriptor ring of the Ethernet controller with index
 *                              ctrlIdx (local index).
 *                              [range: 0 <= (descrdescrRingIdx -
 *                              Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                              Eth_30_Vtt_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                              Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_SetRxEvent(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_RxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the reception descriptor ring related to the highest priority RX event pending and clears
 *                the event
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value. (local descriptor ring index)
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Vtt_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the reception descriptor ring related to the highest priority RX event pending.
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value. (local descriptor ring index)
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Vtt_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Vtt_SetTxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an TX event for the given transmission descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx  Identifier of the transmission descriptor ring of the Ethernet controller with index
 *                              ctrlIdx (local index).
 *                              [range: 0 <= (descrdescrRingIdx -
 *                              Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                              Eth_30_Vtt_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                              Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_SetTxEvent(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_TxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the transmission descriptor ring related to the highest priority TX event pending and clears
*                 the event
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return       Descriptor ring with the highest priority event, if no event is pending -> invalid descriptor ring
 *                value.
 *                [valid range: 0 <= (descrdescrRingIdx -
 *                Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)) <= descrdescrRingIdx <
 *                Eth_30_Vtt_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) -
 *                Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)]
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingTxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/***********************************************************************************************************************
 *  Eth_30_Vtt_ReceiveFifo
 **********************************************************************************************************************/
/*! \brief       Wrapper function to Eth_30_Vtt_Internal_Receive
 *  \details     When VLAN-ID based frame queuing is enabled, we need do retain the DMA index on which the interrupt
 *               is triggered so that only the core specific to the DMA will process the received frame. However
 *               Eth_30_Vtt_Receive doesn't allow to pass the DMA index. Hence this wrapper function is used
 *               to call the Eth_30_Vtt_Internal_Receive directly along with the DMA index.
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(0xFF) in case of VLAN-ID based
 *                            frame queuing disabled.
 *  \param[out]  rxStatusPtr  Indicates the result of the reception trigger:
 *                            ETH_RECEIVED - Ethernet frame was received and no more frames are waiting to be received
 *                            ETH_NOT_RECEIVED - No Ethernet frame was received because non was waiting to be received
 *                            ETH_RECEIVED_MORE_DATA_AVAILABLE - Ethernet frame was received and at least one more
 *                                                               frame is waiting to be received
 *                            ETH_RECEIVED_FRAMES_LOST - will currently not reported
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_ReceiveFifo(
        uint8                                   CtrlIdx,
        uint8                                   FifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) RxStatusPtr);

/***********************************************************************************************************************
 *  Eth_30_Vtt_TxConfirmationFifo
 **********************************************************************************************************************/
/*! \brief       Wrapper function to Eth_30_Vtt_Internal_TxConfirmation
 *  \details     When VLAN-ID based frame queuing is enabled, we need do retain the DMA index on which the interrupt
 *               is triggered so that only the core specific to the DMA will process the received frame. However
 *               Eth_30_Vtt_TxConfirmation doesn't allow to pass the DMA index. Hence this wrapper function is used
 *               to call the Eth_30_Vtt_Internal_Receive directly along with the DMA index.
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(0xFF) in case of VLAN-ID based
 *                            frame queuing disabled.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_TxConfirmationFifo(
        uint8                                   CtrlIdx,
        uint8                                   FifoIdx);

# ifndef ETH_30_VTT_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr)
{
  uint8 descrRingIdx;
  uint16 bitMask = 0;

  /* #10 Get the highest priority pending event in the given events variable */
  descrRingIdx = Eth_30_Vtt_GetHighestPrioPendingEventDescrRing(eventsPtr, &bitMask);                                  /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */

  /* #20 Clear the pending event if one is found */
  if(descrRingIdx != ETH_30_VTT_UNDEFINED_DESCRIPTOR_RING)
  {
    Eth_30_Vtt_ClearPendingEventDescrRing(eventsPtr, bitMask);                                                           /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_PASS */
  }

  return descrRingIdx;
} /* Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetHighestPrioPendingEventDescrRing(
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) bitMaskPtr)
{
  sint8_least flagIdx;
  uint8 descrRingIdx = ETH_30_VTT_UNDEFINED_DESCRIPTOR_RING;

  /* #10 Iterate over all flag positions in the eventsPtr bit-vector */
  for( flagIdx = ETH_30_VTT_IRQ_HANDLER_INT_MAX_EVENT_FLAG_IDX; flagIdx >= 0; flagIdx-- )
  {
    uint16 bitMask = (uint16)((uint32)1u << (uint32)(sint32)flagIdx);

    /* #110 If an event is pending at the currently checked flag position */
    if( ((*eventsPtr) & bitMask) != 0u )
    {
      /* #1110 Calculate the corresponding descriptor ring index which is the index of the highest priority queue
       *       with a pending event */
      descrRingIdx = (uint8)flagIdx;
      *bitMaskPtr = bitMask;                                                                                            /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_WRITE */
      break;
    }
  }

  return descrRingIdx;
} /* Eth_30_Vtt_GetHighestPrioPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_ClearPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_ClearPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
        uint16                        bitMask)
{
  (*eventsPtr) = (uint16)((uint32)(*eventsPtr) & (uint32)(~(uint32)bitMask));                                           /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_WRITE */
} /* Eth_30_Vtt_ClearPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_SetRxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_SetRxEvent(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_RxDescrRingProcIterType descrRingIdx)
{
  /* #10 Use the value of the descriptor ring index parameter to calculate the bit-position to set in the RX events
   *     bit vector and perform the setting */
  Eth_30_Vtt_SetPendingRxEventsOfEthCtrlState(ctrlIdx, Eth_30_Vtt_GetPendingRxEventsOfEthCtrlState(ctrlIdx) |         /* SBSW_ETH_30_VTT_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02 */
                                              (Eth_30_Vtt_PendingRxEventsOfEthCtrlStateType)(1u << descrRingIdx));
} /* Eth_30_Vtt_SetRxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx)
{
  /* #10 Retrieve the descriptor ring index for the pending reception event with the highest priority and clear the
   *     event */
  return Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing(                                                       /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_PASS_CSL02 */
      Eth_30_Vtt_GetAddrPendingRxEventsOfEthCtrlState(ctrlIdx));
} /* Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx)
{
  uint8 descrRingIdx;
  uint16 bitMask = 0;

  /* #10 Retrieve the descriptor ring index for the pending reception event with the highest priority */
  descrRingIdx = Eth_30_Vtt_GetHighestPrioPendingEventDescrRing(                                                       /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_PASS_CSL02 */
        Eth_30_Vtt_GetAddrPendingRxEventsOfEthCtrlState(ctrlIdx), &bitMask);

  return descrRingIdx;
} /* Eth_30_Vtt_GetHighestPrioPendingRxEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_SetTxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_SetTxEvent(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_TxDescrRingProcIterType descrRingIdx)
{
  /* #10 Use the value of the descriptor ring index parameter to calculate the bit-position to set in the TX events
   *     bit vector and perform the setting */
  Eth_30_Vtt_SetPendingTxEventsOfEthCtrlState(ctrlIdx, Eth_30_Vtt_GetPendingTxEventsOfEthCtrlState(ctrlIdx) |         /* SBSW_ETH_30_VTT_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02 */
                                              (Eth_30_Vtt_PendingTxEventsOfEthCtrlStateType)(1u << descrRingIdx));
} /* Eth_30_Vtt_SetTxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_GetAndClearHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_VTT_CODE) Eth_30_Vtt_GetAndClearHighestPrioPendingTxEventDescrRing(
  uint8 ctrlIdx)
{
  /* #10 Retrieve the descriptor ring index for the pending transmission event with the highest priority */
  return Eth_30_Vtt_GetAndClearHighestPrioPendingEventDescrRing(Eth_30_Vtt_GetAddrPendingTxEventsOfEthCtrlState(ctrlIdx));    /* SBSW_ETH_30_VTT_INT_FCT_PARAM_PTR_PASS_CSL02 */
} /* Eth_30_Vtt_GetAndClearHighestPrioPendingTxEventDescrRing() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Vtt_ProcessIsr
 **********************************************************************************************************************/
/*! \brief        Processes the interrupt events of a specific interrupt service routine
 *  \details      Function processes the interrupt event handler functions of a specific interrupt service routine.
 *                Additionally - if enabled during configuration - pre- and post-ISR-User-Functions are processed too.
 *  \param[in]    ctrlIdx    Module local identifier of the controller
 *  \param[in]    isrIdx     Interrupt service routine identifier
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE for different interrupt service routines
 *  \pre          -
 **********************************************************************************************************************/
FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_ProcessIsr(
  uint8 ctrlIdx,
  uint8 isrIdx);

# endif /* ETH_30_VTT_UNIT_TEST */

# define ETH_30_VTT_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_VTT_IRQ_HANDLER_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_IrqHandler_Int.h
 *********************************************************************************************************************/
