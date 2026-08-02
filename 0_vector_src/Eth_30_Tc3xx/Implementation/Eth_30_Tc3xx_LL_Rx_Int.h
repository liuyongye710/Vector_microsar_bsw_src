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
/*!        \file  Eth_30_Tc3xx_LL_Rx_Int.h
 *        \brief  Lower layer reception private header file
 *
 *      \details  Private inline implementations of lower layer reception part of component.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/
#if !defined (ETH_30_TC3XX_LL_RX_INT_H)
# define ETH_30_TC3XX_LL_RX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Rx_Ifc_Int.h"
# include "Eth_30_Tc3xx_LL_CtrlModeHdl_Int.h"
# include "Eth_30_Tc3xx_IrqHandler_Int.h"
# include "Eth_30_Tc3xx_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# define ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX                    (2u)

# define ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE                             (2u)
# define ETH_30_TC3XX_USED_FCS_LEN_BYTE                               (0u)
# define ETH_30_TC3XX_FCS_LEN_BYTE                                    (4u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Return status of OWN bit in Rx descriptor */
  return (boolean)((ETH_30_TC3XX_RX3_DESC_OWN &
           Eth_30_Tc3xx_GetAddrRxDescr(globalDescrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX]) == 0uL);

} /* Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsErrorInRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx)
{
  boolean errorInDescriptor;
  uint16 FrameLen = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx);
  CONSTP2CONST(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxDescPtr = Eth_30_Tc3xx_GetAddrRxDescr(globalDescrIdx);

  /* #10 Check whether descriptor was split into more than one descriptor (FD+LD not set, e.g. because frame is larger
   *     than the default HW limit of 1518/1522(VLAN tagged) bytes for normal frames or a configured lower limit in
   *     the DMA_CHi_RX_CONTROL register) or error flags are set */
  if(((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_FD)   == 0uL) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_LD)   == 0uL) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_ES)   != 0uL) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_CTXT) != 0uL))
  {
    errorInDescriptor = TRUE;
  }
  /* #20 Check whether received frame size exceeds configured frame size because of buffer alignment and size
   *     requirements (e.g. DMA_CHi_RX_CONTROL register with fields RBSZ_13_y and RBSZ_x_0 the actual buffer size in
   *     the memory can be larger so these frames have to blocked by software!) */
  else if((FrameLen + ETH_30_TC3XX_FCS_LEN_BYTE)
  /* FCS not copied to memory / included in FrameLen therefore adding constant FCS length value here! */
                   > ( Eth_30_Tc3xx_GetMaxFrameSizeOfRxBufferHandling(globalDescrRingIdx)))
  {
    errorInDescriptor = TRUE;
  }
  else
  {
    errorInDescriptor = FALSE;
  }

  return errorInDescriptor;
} /* Eth_30_Tc3xx_LL_IsErrorInRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetRxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents(
  uint8 ctrlIdx)
{
  /* #10 Trigger Rx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsRxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetRxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx)
{
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx;

  /* #10 Retrieve the mapped buffer of the descriptor to be recharged */
  bufIdx = Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(globalDescrIdx);

  /* #20 Recharge the descriptor by initializing it */
  Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx, bufIdx);
} /* Eth_30_Tc3xx_LL_RechargeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset;

  if(globalDescrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
  }
  else if(globalDescrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
  }
  else if(globalDescrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
  }

  /* #10 Set tail pointer to next descriptor depending on current descrRingIdx */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)
  Eth_30_Tc3xx_GetAddrRxDescr(globalDescrIdx));
} /* Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         globalDescrIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(globalDescrRingIdx); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */

  /* #10 Extract length of a received frame from a descriptor */
  return (uint16)(Eth_30_Tc3xx_GetAddrRxDescr(globalDescrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX] &
                    ETH_30_TC3XX_RX3_DESC_FL_MASK);
} /* Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_RxDescrRingProcIterType descrRingCount;
  boolean isRxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (descrRingCount = (Eth_30_Tc3xx_RxDescrRingProcIterType)Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); descrRingCount > Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx); descrRingCount--)
  {
    uint8 queueIdx = (uint8)(descrRingCount - 1u);

    /* #110 If any checked RX queue has pending RX frames */
    if (Eth_30_Tc3xx_LL_IsRxQueuePending(ctrlIdx, queueIdx) == TRUE)
    {
      /* #1110 Return that a RX event is pending */
      isRxPend = TRUE;
    }
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    Eth_30_Tc3xx_RxDescrRingProcIterType globalDescrRingIdx)
{
  boolean isRxPend = FALSE;
  Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType curRxDescrIdx = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(globalDescrRingIdx)
                                               + Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(globalDescrRingIdx);

  /* #10 Check if next descriptor to process is passed to driver already */
  if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, curRxDescrIdx) == TRUE)
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor only when VLAN-ID based frame queuing is disabled because,
     *      when VLAN-ID based frame queuing is enabled, the DMA Idx is retained and the only the corresponding
     *      descriptor ring is processed and not based on Rx event. */
    if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
    {
      Eth_30_Tc3xx_SetRxEvent(ctrlIdx, (uint8)globalDescrRingIdx);
    }
    isRxPend = TRUE;
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxQueuePending() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_RX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32_least hwLoopTimeout;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ0 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ1 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ2 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ3 = 0;

  for(hwLoopTimeout = 0u; hwLoopTimeout < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); hwLoopTimeout++)
  {
    /* #10 Read all used MTL_RXQi_DEBUG registers (default RXQ0, with QoS all available) */
    regValRxQ0 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_DEBUG);
    if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      regValRxQ1 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_DEBUG);
      if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED)
      {
        regValRxQ2 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_DEBUG);
      }
      if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED)
      {
        regValRxQ3 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_DEBUG);
      }
    }

    /* #20 Check the appropriate bits if data in Rx FIFO is transferred to system memory */
    if(((regValRxQ0 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ1 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ2 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ3 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY))
    {
      /* #210 Set return value to E_OK if data is transferred to system memory,
              otherwise check again if timeout cycle counter not exceeded */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_RX_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Rx_Int.h
 *********************************************************************************************************************/
