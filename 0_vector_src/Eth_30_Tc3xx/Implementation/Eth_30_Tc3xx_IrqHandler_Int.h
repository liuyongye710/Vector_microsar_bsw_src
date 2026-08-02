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
/*!        \file  Eth_30_Tc3xx_IrqHandler_Int.h
 *        \brief  Inline implementation of private Ethernet controller interrupt handler part
 *
 *      \details  Provides access to the private interrupt handler related inlined API of the Ethernet controller driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

/* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */


#if !defined (ETH_30_TC3XX_IRQ_HANDLER_INT_H)
# define ETH_30_TC3XX_IRQ_HANDLER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_IrqHandler_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_IrqHandler_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETH_30_TC3XX_IRQ_HANDLER_INT_MAX_EVENT_FLAG_IDX              (15u)
/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr)
{
  uint8 descrRingIdx;
  uint16 bitMask = 0;

  /* #10 Get the highest priority pending event in the given events variable */
  descrRingIdx = Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(eventsPtr, &bitMask);                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */

  /* #20 Clear the pending event if one is found */
  if(descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
  {
    Eth_30_Tc3xx_ClearPendingEventDescrRing(eventsPtr, bitMask);                                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }

  return descrRingIdx;
} /* Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) bitMaskPtr)
{
  sint8_least flagIdx;
  uint8 descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* #10 Iterate over all flag positions in the eventsPtr bit-vector */
  for( flagIdx = (sint8_least)ETH_30_TC3XX_IRQ_HANDLER_INT_MAX_EVENT_FLAG_IDX; flagIdx >= 0; flagIdx-- )
  {
    uint16 bitMask = (uint16)((uint32)1u << (uint32)(sint32)flagIdx);

    /* #110 If an event is pending at the currently checked flag position */
    if( ((*eventsPtr) & bitMask) != 0u )
    {
      /* #1110 Calculate the corresponding descriptor ring index which is the index of the highest priority queue
       *       with a pending event */
      descrRingIdx = (uint8)flagIdx;
      *bitMaskPtr = bitMask;                                                                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      break;
    }
  }

  return descrRingIdx;
} /* Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ClearPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ClearPendingEventDescrRing(
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) eventsPtr,
        uint16                        bitMask)
{
  (*eventsPtr) = (uint16)((uint32)(*eventsPtr) & (uint32)(~(uint32)bitMask));                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
} /* Eth_30_Tc3xx_ClearPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetRxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxEvent(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_RxDescrRingProcIterType descrRingIdx)
{
  /* #10 Use the value of the descriptor ring index parameter to calculate the bit-position to set in the RX events
   *     bit vector and perform the setting */
  Eth_30_Tc3xx_SetPendingRxEventsOfEthCtrlState(ctrlIdx, Eth_30_Tc3xx_GetPendingRxEventsOfEthCtrlState(ctrlIdx) |         /* SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02 */
                                              (Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType)(1uL << descrRingIdx));
} /* Eth_30_Tc3xx_SetRxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx)
{
  /* #10 Retrieve the descriptor ring index for the pending reception event with the highest priority and clear the
   *     event */
  return Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing(                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02 */
      Eth_30_Tc3xx_GetAddrPendingRxEventsOfEthCtrlState(ctrlIdx));
} /* Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx)
{
  uint8 descrRingIdx;
  uint16 bitMask = 0;

  /* #10 Retrieve the descriptor ring index for the pending reception event with the highest priority */
  descrRingIdx = Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(
        Eth_30_Tc3xx_GetAddrPendingRxEventsOfEthCtrlState(ctrlIdx), &bitMask);                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02 */

  return descrRingIdx;
    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02 */
} /* Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetTxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxEvent(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx)
{
  /* #10 Use the value of the descriptor ring index parameter to calculate the bit-position to set in the TX events
   *     bit vector and perform the setting */
  Eth_30_Tc3xx_SetPendingTxEventsOfEthCtrlState(ctrlIdx, Eth_30_Tc3xx_GetPendingTxEventsOfEthCtrlState(ctrlIdx) |         /* SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02 */
                                              (Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType)(1uL << descrRingIdx));
} /* Eth_30_Tc3xx_SetTxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(
  uint8 ctrlIdx)
{
  /* #10 Retrieve the descriptor ring index for the pending transmission event with the highest priority */
  return Eth_30_Tc3xx_GetAndClearHighestPrioPendingEventDescrRing(Eth_30_Tc3xx_GetAddrPendingTxEventsOfEthCtrlState(ctrlIdx));    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02 */
} /* Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_IRQ_HANDLER_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_IrqHandler_Int.h
 *********************************************************************************************************************/
