/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_Tx.c
 *        \brief  Ethernet controller transmit implementation
 *
 *      \details  Core part of the Ethernet controller driver transmit implementation.
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

/*lint -e438 */ /* Suppress ID438 because Config pointer only used in Post-Build Variant */
/*lint -e506 */ /* Suppress ID506 due to MD_MSR_14.1 */
/*lint -e537 */ /* Suppress ID537 due to MD_MSR_MemMap */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

#define ETH_30_TC3XX_TX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_Tx.h"
#include "Eth_30_Tc3xx_Tx_Int.h"
#include "Eth_30_Tc3xx_Int.h"
#include "EthIf_Cbk.h"
#include "Eth_30_Tc3xx_Cbk.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! \brief      Increments the free position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! \brief          Checks if transmission buffer provision can be processed
 *  \details        Function performs a pre-check if TX buffer provision is possible.
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in,out]  lenPtr   Buffer to determine the requested length and the actual needed length of the buffer:
 *                           [in]  Length of the buffer as requested by the upper layer
 *                           [out] Length of the buffer needed due to other constraints like insertion of switch
 *                                 management data by the EthSwt driver
 *  \return         TRUE  - TX Buffer provision is possible
 *  \return         FALSE - TX Buffer provision is not possible, operation failed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different Ethernet controllers
 *  \pre            -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk
 **********************************************************************************************************************/
/*! \brief          Performs a pre-preparation of the buffer that shall be provided to the upper layer
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the transmission buffer segment
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                              [out] Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (adaption of position could be needed due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Actual length of the buffer segment
 *                              [out] Available length of the buffer segment
 *                                    (adaption of the actual length could be needed due to insertion of an additional
 *                                     header between MAC addresses an Ether Type like in a EthSwt management use case)
 *  \return         TRUE  - TX Buffer pre preparation is OK
 *  \return         FALSE - TX pre preparation operation failed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if triggering of transmission of a Ethernet frame is possible
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the transmission buffer segment
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (position could be shifted due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *                              [out] Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Available length of the buffer segment
 *                                    (actual length could be decreased due to insertion of an additional
 *                                     header between MAC addresses an Ether Type like in a EthSwt management use case)
 *                              [out] Actual length of the buffer segment
 *  \return         TRUE  - Frame transmission allowed
 *  \return         FALSE - Frame transmission not allowed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! \brief      Finishes the transmission triggering of a Ethernet frame
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]  bufIdx   Identifier of the transmission buffer segment
 *              [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission buffer segments
 *  \pre        -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief          Provides a buffer that can be used to transmit a Ethernet frame
 *  \details        Function provides a buffer that can be used to transmit a Ethernet frame. The buffer is locked and
 *                  therefore protected against reuse until the transmission of the frame is confirmed after transmission
 *                  was triggered (Eth_Transmit() and consecutive Eth_TxConfirmation()) or buffer is intentionally released
 *                  by calling Eth_Transmit() with LenByte=0.
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]     bufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     bufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  lenBytePtr  Pointer to variable used to determine the requested and actually provided length of the
 *                              transmission buffer requested:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ProvideTxBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer
 **********************************************************************************************************************/
/*! \brief          Helper for ProvideTxBuffer
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]     bufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     bufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  lenBytePtr  Pointer to variable used to determine the requested and actually provided length of the
 *                              transmission buffer requested:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \param[in]      txBufferBusyIdx  Identifier of the buffer provided on successful buffer provision
 *                  [range: 0 <= txBufferBusyIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr,
              uint8                                                      txBufferBusyIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_VTransmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer with a specific source MAC
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header (using a specific source MAC address instead of the Ethernet controllers one) and triggers the
 *               transmission of the Ethernet frame.
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   frameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   txConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   lenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   physAddrDstPtr  Destination MAC address
 *  \param[in]   physAddrSrcPtr  Source MAC address
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_VTransmit(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          boolean                             txConfirmation,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrSrcPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit_ProcessValidFrame
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame
 *  \details     Function as helper for the frame transmission triggering
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   frameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   lenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   bufPtr          Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame with
 *                               a size of at least 60 Bytes.
 *  \param[in]   bufStartPtr     Pointer pointing to the destination MAC position of a IEEE conform Ethernet frame
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit_ProcessValidFrame(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufStartPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_TxConfirmation
 **********************************************************************************************************************/
/*! \brief       Triggers the transmission confirmation of a previously transmitted Ethernet frame
 *  \details     Function triggers the transmission confirmation of a previously Ethernet frame transmitted and unlocks
 *               the buffer associated to the Ethernet frame so it is able to be used for frame transmission again.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx  Index of the Queue(DMA) to be processes. Set to invalid(ETH_30_TC3XX_INVALID_FIFO_IDX) in case
 *                        of VLAN-ID based frame queuing disabled.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_TxConfirmation(
  uint8 ctrlIdx,
  uint8 fifoIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType procPos;
  Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(descrRingIdx);
  procPos            = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
  /* #10 Increment current transmission position in TX descriptor ring */
  procPos++;

  /* #20 If the current read position in the TX descriptor ring is equal to the first invalid position */
  if (procPos >= (Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current read position in the TX descriptor ring to 0 to perform a wrap-around */
    procPos = 0u;
  }

  Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx, procPos);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncTxDescRingProcPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_FreePosOfTxDescrRingProcType freePos;
  Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(descrRingIdx);
  freePos            = Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(txDescrRingProcIdx);
  /* #10 Increment free position in TX descriptor ring */
  freePos++;

  /* #20 If the current free position in the TX descriptor ring is equal to the first invalid position */
  if (freePos >= (Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current free position in the TX descriptor ring to 0 to perform a wrap-around */
    freePos = 0u;
  }
  Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(txDescrRingProcIdx, freePos);                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncTxDescRingFreePos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for buffer length adaption */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for buffer length adaption */
    if (Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The result of the operation indicates an error */
      if (Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(ethSwtIfcIdx)(lenPtr) == E_NOT_OK)                             /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
      {
        /* #1210 Return that the TX buffer provision is not possible */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_IsTxBufProvisonPossible() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for TX frame preparation */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for TX frame preparation */
    if (Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The operation failed because the EthSwt driver interface returns E_NOT_OK */
      if (Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr) ==               /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
          E_NOT_OK)
      {
        /* #1210 Return that the pre-preparation of the Tx frame is not OK */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_PrePrepareTxFrame() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for TX frame processing */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for TX frame processing */
    if (Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The operation failed because the EthSwt driver interface returns E_NOT_OK */
      if (Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr) ==               /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
          E_NOT_OK)
      {
        /* #1210 Return that the frame transmission is not allowed */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_IsFrameTxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface to indicate finish of transmission */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface to indicate finish of transmission */
    if (Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx);                                 /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03 */
    }
  }
} /* Eth_30_Tc3xx_FinishFrameTx() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ProvideTxBuffer
 **********************************************************************************************************************/
/*! Internal comment removed.
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
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ProvideTxBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If TX buffer provision is possible */
  if (Eth_30_Tc3xx_IsTxBufProvisonPossible(ctrlIdx, lenBytePtr) == TRUE)                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    uint16 requestedLen;
    Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
    Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType maxTxBufferLen;

    txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
    maxTxBufferLen      = Eth_30_Tc3xx_GetMaxBufferLenOfTxBufferHandling(txBufferHandlingIdx);
    /* #110 If the maximum size of all available buffers is not big enough for the requested payload plus header and FCS
     *      (total frame length) */
    requestedLen = (*lenBytePtr) + ETH_30_TC3XX_HDR_LEN_BYTE;

    if (maxTxBufferLen < requestedLen)
    {
      /* #1110 The buffer provision fails */
      retVal = BUFREQ_E_OVFL;
    }
    /* #120 If at least one buffer is big enough for the requested total frame lenth */
    else
    {
      Eth_30_Tc3xx_TxBufferStateIterType txBufferStateIdx;
      Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType txBufferStateEndIdx;
      Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType txBufferStateStartIdx;

      /* #1210 Enter exclusive area (Reason: Consistency between found buffer and locked buffer indices) */
      Eth_30_Tc3xx_EnterExclusiveArea(DATA_MULTI_CORE); 

      txBufferStateStartIdx = Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(txBufferHandlingIdx);
      txBufferStateEndIdx   = Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(txBufferHandlingIdx);
      /* #1220 loop over all available transmission buffers */
      for (txBufferStateIdx = txBufferStateStartIdx; txBufferStateIdx < txBufferStateEndIdx; txBufferStateIdx++)
      {
        /* #12210 The current buffer is not in use (busy) and its size is big enough for the requested frame length */
        /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */
        if ((Eth_30_Tc3xx_IsBusyOfTxBufferState(txBufferStateIdx)   == FALSE) &&
            (Eth_30_Tc3xx_GetLengthOfTxBufferData(txBufferStateIdx) >= requestedLen))
        {
          /* #122110 Leave the loop */
          break;
        }
      }
      /* #1230 If a suitable buffer could be found in the previous loop */
      if ((txBufferStateIdx - txBufferStateStartIdx) < Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(txBufferHandlingIdx))
      {
        /* #12310 Call the internal interface to proceed the buffer provision for a valid buffer */
        retVal = Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
                  ctrlIdx, bufIdxPtr, bufPtr, lenBytePtr, (uint8)txBufferStateIdx);
      }
      /* #1240 If no suitable buffer could be found in the previous loop */
      else
      {
        /* #12410 Return that all big enough buffers are in use (busy) */
        retVal = BUFREQ_E_BUSY;
        /* #12420 Increment the measurement counter */
        Eth_30_Tc3xx_IncDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx);                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      }

      /* #1250 Leave exclusive area */
      Eth_30_Tc3xx_ExitExclusiveArea(DATA_MULTI_CORE); 
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_ProvideTxBuffer() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer
 **********************************************************************************************************************/
/*! Internal comment removed.
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
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr,
              uint8                                                      txBufferBusyIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_TxBufferIterType globalStartOffset;
  Eth_30_Tc3xx_StartPosOfTxBufferDataType localStartOffset;
  Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
  Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType txBufferEndIdx;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
  txBufferEndIdx      = Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(txBufferHandlingIdx);

  /* #10 Retrieve the index of the valid buffer to be provided to the caller */
  localStartOffset  = Eth_30_Tc3xx_GetStartPosOfTxBufferData(txBufferBusyIdx);
  globalStartOffset = (Eth_30_Tc3xx_TxBufferIterType) localStartOffset + 
                      (Eth_30_Tc3xx_TxBufferIterType) Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);

  /* #20 If the retrieved buffer index offset position has enough distance to the end index for a valid buffer */
  if ((globalStartOffset + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) < txBufferEndIdx)
  {
    Eth_30_Tc3xx_TxBufferPtrType bufAddrFrameType;
    Eth_30_Tc3xx_TxBufferIterType frameTypeOffset;
    Eth_30_Tc3xx_LengthOfTxBufferDataType lenByte;
    Eth_30_Tc3xx_LengthOfTxBufferDataType txBufferLength;

    frameTypeOffset = globalStartOffset + 
                      (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE;

    bufAddrFrameType = Eth_30_Tc3xx_GetAddrTxBuffer(frameTypeOffset);

    txBufferLength   = Eth_30_Tc3xx_GetLengthOfTxBufferData(txBufferBusyIdx);

    lenByte          = (Eth_30_Tc3xx_LengthOfTxBufferDataType)(txBufferLength -
                        ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE);

    /* #210 If the pre-preparation of the TX frame is OK */
    if (Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(ctrlIdx, txBufferBusyIdx, &bufAddrFrameType, &lenByte) == TRUE)         /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X */
    {
      /* #2110 Adjust the returned length to exclude the frame type length */
      lenByte -= ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE;
      /* #2120 If the modified length is valid */
      if ((globalStartOffset + lenByte) < txBufferEndIdx)
      {
        /* #21210 Adjust the returned buffer pointer to point at the start of the payload */
        (*bufPtr)  = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))&bufAddrFrameType[ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE];/* PRQA S 3305, 0310 1 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

        /* #21220 Set the buffers state to busy to lock it */
        Eth_30_Tc3xx_SetBusyOfTxBufferState(txBufferBusyIdx, TRUE);                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        /* #21230 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) 
        {
          /* #212310 Reset the global buffer state variable indicating if a timestamp is requested */
          Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(txBufferBusyIdx, FALSE);                                            /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        }
        /* #21240 Return the length, buffer pointer and buffer index to the caller */
        (*lenBytePtr) = lenByte;                                                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        /* PRQA S 3305, 0310 1 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */

        (*bufIdxPtr)  = txBufferBusyIdx;                                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        /* #21250 Return that the buffer provision was successful */
        retVal        = BUFREQ_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_VTransmit
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_VTransmit(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          boolean                             txConfirmation,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrSrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Consistency between transmitted and unlocked buffer indices and synchronization
   *                                   between hardware and software) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); 

  /* #20 If the buffer the transmission was requested for is locked which indicates that its provision was successful */
  if (Eth_30_Tc3xx_IsBusyOfTxBufferState(bufIdx) == TRUE)
  {
    /* #210 Retrieve the buffer offset and start pointer out of the buffer index parameter */
    Eth_30_Tc3xx_TxBufferIterType bufStartOffset;
    Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType txBufferEndIdx;
    Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
    Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType txBufferStartIdx;
    uint16 localLenByte;

    txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
    txBufferStartIdx    = Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);
    txBufferEndIdx      = Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(txBufferHandlingIdx);
    bufStartOffset      = (uint32)Eth_30_Tc3xx_GetStartPosOfTxBufferData(bufIdx) + txBufferStartIdx;
    localLenByte = lenByte;

    if ((bufStartOffset + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) < txBufferEndIdx )
    {
      uint8 physAddrPtrIterator;
      Eth_30_Tc3xx_TxBufferIterType bufSrcMacOffset;
      Eth_30_Tc3xx_TxBufferIterType bufDstMacOffset;
      Eth_30_Tc3xx_TxBufferIterType bufEtherTypeOffset;
      Eth_30_Tc3xx_TxBufferIterType macAddressIterator;
      uint8 const* bufStartPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufDstMacPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufSrcMacPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufEthTypePtr;

      bufDstMacOffset    = bufStartOffset;
      bufSrcMacOffset    = bufStartOffset + (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC;
      bufEtherTypeOffset = bufStartOffset + (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE;

      bufStartPtr        = Eth_30_Tc3xx_GetAddrTxBuffer(bufStartOffset);
      bufEthTypePtr      = Eth_30_Tc3xx_GetAddrTxBuffer(bufEtherTypeOffset);

      /* #220 If the transmission was requested for a zero length buffer indicating that only the buffer should be
       *      released */
      if (localLenByte == 0u)
      {
        /* #2210 Release the buffer so it can be provided again and return that the request was successful */
        Eth_30_Tc3xx_SetBusyOfTxBufferState(bufIdx, FALSE);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        retVal = E_OK;
      }
      /* #230 If the requested transmission length is greater than 0 indicating that a transmission shall be
       *      performed */
      else
      {
        /* #2310 Write source and destination MAC-address into the buffer */
        /* Assemble Ethernet Header */
        /* Physical destination address */
        physAddrPtrIterator = 0;
        for (macAddressIterator = bufDstMacOffset; macAddressIterator < bufSrcMacOffset; macAddressIterator++)
        {
          bufDstMacPtr  = Eth_30_Tc3xx_GetAddrTxBuffer(macAddressIterator);
          *bufDstMacPtr = physAddrDstPtr[physAddrPtrIterator];                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X */
          physAddrPtrIterator++;
        }
        /* Physical source address */
        physAddrPtrIterator = 0;
        for (macAddressIterator = bufSrcMacOffset; macAddressIterator < bufEtherTypeOffset; macAddressIterator++)
        {
          bufSrcMacPtr  = Eth_30_Tc3xx_GetAddrTxBuffer(macAddressIterator);
          *bufSrcMacPtr = physAddrSrcPtr[physAddrPtrIterator];                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X */
          physAddrPtrIterator++;
        }

        /* #2320 Write the frame type to the buffer */
        bufEthTypePtr[ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX] = (uint8)(frameType >> ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_RSHIFT);/* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS */
        bufEthTypePtr[ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX] = (uint8)frameType;                                           /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS */
        /* #2330 If frame transmission is allowed */
        if (Eth_30_Tc3xx_IsFrameTxAllowed(ctrlIdx, bufIdx, &bufEthTypePtr, &localLenByte) == TRUE)                            /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_PARAM_PASS_CSL0X */
        {
          /* #23310 If a upper layer TX-confirmation is requested */
          if (TRUE == txConfirmation)
          {
            /* #233110 Set the global state variable of the transmission buffer to indicate that a confirmation is
             *         pending */
            Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(bufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING);             /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
          }
          /* #23320 Call the internal interface to proceed the frame transmission for a valid frame */
          Eth_30_Tc3xx_VTransmit_ProcessValidFrame(ctrlIdx, bufIdx, frameType, localLenByte, bufEthTypePtr, bufStartPtr);     /* SBSW_ETH_30_TC3XX_INT_FCT_SHIFTED_LOCAL_BUF_PTR_WITH_LENGTH_PASS_SWT_IFC */
          /* #23330 Return that the request was successful */
          retVal = E_OK;
        }
      }
      /* #240 Perform finishing steps after transmission */
      Eth_30_Tc3xx_FinishFrameTx(ctrlIdx, bufIdx);
    }
  }
  /* #30 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); 

  return retVal;
} /* Eth_30_Tc3xx_Internal_VTransmit() */ /* PRQA S 6050, 6060, 6080 */ /* MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit_ProcessValidFrame
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 *
 */
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit_ProcessValidFrame(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufStartPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 vlanIdTxDescrRing = 0;
  Eth_30_Tc3xx_TxDescrIterType curPos;
  Eth_30_Tc3xx_TxDescrIterType globalDescrIdx;
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx;
  Eth_30_Tc3xx_VlanPrioTxDescrRingMapType vlanPrioTxDescrRing;
  Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType txDescrStartIdx;
  uint16 lenByteModified;
  Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType vlanIdTxDescrRingMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the descriptor ring index to match the queue the transmission shall be performed with in case of
   *     untagged traffic */
  globalDescrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  /* #20 Increase the passed length by the Ethernet frame header length */
  lenByteModified = lenByte + ETH_30_TC3XX_HDR_LEN_BYTE;

  /* #30 If Quality of Service is enabled */
  if (Eth_30_Tc3xx_IsQosEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType qosHandlingIdx = Eth_30_Tc3xx_GetQosHandlingIdxOfEthCtrl(ctrlIdx);
    /* #310 If the frame type indicates that the frame to be transmitted is a VLAN frame */
    if (frameType == ETH_30_TC3XX_VLAN_ETHER_TYPE)  
    {
      /* #3110 Retrieve the VLAN-priority of the frame */
      uint8 vlanPrio;
      Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType vlanPrioTxDescrRingMapStartIdx;

      vlanPrioTxDescrRingMapStartIdx = Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapStartIdxOfQosHandling(qosHandlingIdx);

      vlanPrio = (uint8)((bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET] & ETH_30_TC3XX_VLAN_PCP_BYTE_MASK) >>
                                 ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT);

      /* #3120 Retrieve the transmission queue and descriptor ring index a frame with the retrieved VLAN-priority shall
       *       be transmitted in */
      vlanPrioTxDescrRing = (Eth_30_Tc3xx_VlanPrioTxDescrRingMapType)(Eth_30_Tc3xx_GetVlanPrioTxDescrRingMap(((uint32)vlanPrioTxDescrRingMapStartIdx + (uint32)vlanPrio)));

      /* #3130 If the retrieved VLAN prio leads to a valid global descriptor ring index */
      if ((globalDescrRingIdx + vlanPrioTxDescrRing) < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx))
      {
        /* #31310 Overwrite the previously initialized descriptor ring index with the retrieved ring index */
        globalDescrRingIdx = (globalDescrRingIdx + vlanPrioTxDescrRing);
      }
    }
    else
    {
      /* #320 For untagged frames get configured queue and associated descriptor ring index */
      globalDescrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfQosHandling(qosHandlingIdx);
    }
  }
   /* #40 If VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType vlanIdBasesQueuingHandlingIdx = Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(ctrlIdx);
    /* #410 If the frame type indicates that the frame to be transmitted is a VLAN frame */
    if(frameType == ETH_30_TC3XX_VLAN_ETHER_TYPE)
    {
      uint16 vlanId;
      const Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapStartIdx = Eth_30_Tc3xx_GetVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
      const Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapEndIdx = Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);

      /* #4110 Retrieve the VLAN-ID of the frame */
      vlanId  = (uint16)(((uint16)bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET]) << 8u);
      vlanId |= (uint16)bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET + 1U];
      vlanId &= (uint16)ETH_30_TC3XX_VLAN_ID_BYTE_MASK;

      /* #4120 If exists, retrieve the descriptor ring index mapped for the frame with the retrieved VLAN-ID */
      for (vlanIdTxDescrRingMapIdx = vlanIdTxDescrRingMapStartIdx; vlanIdTxDescrRingMapIdx < vlanIdTxDescrRingMapEndIdx; vlanIdTxDescrRingMapIdx++)
      {
        if ( Eth_30_Tc3xx_GetVlanIdOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx) == vlanId )
        {
          vlanIdTxDescrRing = Eth_30_Tc3xx_GetQueueIndexOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx);
          break;
        }
      }

      if(vlanIdTxDescrRingMapIdx < Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx))
      {
        /* #41210 If the retrieved descriptor ring index leads to a valid global descriptor ring index */
        if ((globalDescrRingIdx + vlanIdTxDescrRing) < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx))
        {
          /* #412110 Overwrite the previously initialized descriptor ring index with the retrieved ring index */
          globalDescrRingIdx = (globalDescrRingIdx + vlanIdTxDescrRing);
        }
      }
      /* #4130 If no descriptor ring index mapping exists for the retrieved VLAN-ID */
      else
      {
        /* #41310 Use the descriptor ring index associated with untagged frames  */
        globalDescrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
      }
    }
    else
    {
      /* #420 For untagged frames get configured queue and associated descriptor ring index */
      globalDescrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
    }
  }
  /* #50 Retrieve the next free position in the descriptor ring used for this transmission */
  curPos          = Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(globalDescrRingIdx);
  txDescrStartIdx = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);

  /* #60 Calculate the global descriptor index out of the global start index and the current position in the ring */
  globalDescrIdx = curPos + txDescrStartIdx;

  /* #70 If the global index was calculated correctly and is within the correct range of the descriptor ring */
  if (globalDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(globalDescrRingIdx))
  {
    /* #710 Call the hardware dependent interface to prepare the free transmission descriptor for transmission */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
      ctrlIdx, globalDescrRingIdx, globalDescrIdx, bufIdx, lenByteModified, bufStartPtr);                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

    /* #720 Save the buffer mapped to the transmission descriptor */
    Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(globalDescrIdx, bufIdx);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

    /* #730 Indicate that the descriptor is ready for transmission in the corresponding global state variable */
    Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_READY);                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
    /* #740 TimeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #7410 If a timestamp is requested for the buffer to be transmitted */
      if (Eth_30_Tc3xx_IsTsRequestedOfTxBufferState(bufIdx) == TRUE)
      {
        /* #74110 Set up the time stamp context by saving the used descriptor ring index and descriptor position in the
         *        corresponding global variable */
        Eth_30_Tc3xx_SetRingIdxOfTxTsContext(bufIdx, (Eth_30_Tc3xx_RingIdxOfTxTsContextType)globalDescrRingIdx);                /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        Eth_30_Tc3xx_SetDescrIdxOfTxTsContext(bufIdx, (Eth_30_Tc3xx_DescrIdxOfTxTsContextType)curPos);                    /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

        /* #74120 Call the hardware dependent interface to prepare the transmission descriptor for timestamping */
        /*lint -e{522} */
        Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(ctrlIdx, globalDescrRingIdx, globalDescrIdx, bufIdx);
      }
    }
#endif

    /* #750 Call the hardware dependent interface to prepare the transmission descriptor for IP checksum
      *       offloading if it is enabled */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(ctrlIdx, globalDescrRingIdx, globalDescrIdx);
    /* #760 Call the hardware dependent interface to prepare the transmission descriptor for protocol checksum
     *       offloading if it is enabled */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(ctrlIdx, globalDescrRingIdx, globalDescrIdx);
    /* #770 Synchronize the RAM and peripheral register access */
    Appl_Eth_30_Tc3xx_MemoryBarrier();

    /* #780 Call the hardware dependent interface to trigger the transmission and increment the position of the next
     *      free descriptor */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_TriggerTransmission(ctrlIdx, globalDescrRingIdx, globalDescrIdx);

    Eth_30_Tc3xx_IncTxDescRingFreePos(globalDescrRingIdx);

#ifdef ETH_TEST_SUITE_CODE /* COV_ETH_TEST_SUITE */
# ifndef _ETH_TEST_SUITE_CDK_RUN_ /* COV_ETH_TEST_SUITE */
  if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* Test code used for QoS/VLAN_ID based frame queueing reception queue tests */
      EthClient_TxQueueCounter[ctrlIdx][globalDescrRingIdx]++;
    }
# endif /* _ETH_TEST_SUITE_CDK_RUN_ */
#endif /* ETH_TEST_SUITE_CODE */
  }
} /* Eth_30_Tc3xx_VTransmit_ProcessValidFrame() */ /* PRQA S 6010, 6030, 6050, 6060 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_TxConfirmation
 **********************************************************************************************************************/
/*! Internal comment removed.
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
ETH_30_TC3XX_TX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_TxConfirmation(
  uint8 ctrlIdx,
  uint8 fifoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the frame transmission interrupt is disabled */
  if (Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
  {
    /* #110 Set pending transmission events in the software if they are pending on the hardware */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_SetTxEvents(ctrlIdx);
  }
  /* #20 Check if VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #210 Assign the fifoIdx to descriptor ring index if it is in the valid range */
    if (fifoIdx < (Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)))
    {
      descrRingIdx = fifoIdx;
    }
  }
  else
  {
    /* #220 Retrieve the descriptor ring index of the highest priority transmission queue with a pending event */
    descrRingIdx = Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(ctrlIdx);
  }

  /* #30 If a descriptor ring with a pending reception event could be retrieved */
  if (descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
  {
    Eth_30_Tc3xx_TxDescrIterType globalDescrIdx;
    Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType curDescrPos;
    Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType txDescrStartIdx;
    Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;
    Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx;

    /* #310 Retrieve the last processed descriptor index */
    globalDescrRingIdx = (uint8_least)descrRingIdx + (uint8_least)Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
    txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(globalDescrRingIdx);
    txDescrStartIdx    = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);
    curDescrPos        = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);

    globalDescrIdx = (Eth_30_Tc3xx_TxDescrIterType)txDescrStartIdx + (Eth_30_Tc3xx_TxDescrIterType)curDescrPos;
    /* #320 Enter exclusive area (Reason: Hardware and software synchronization)  */
    Eth_30_Tc3xx_EnterExclusiveArea(DATA); 

    /* #330 Repeat while the currently checked descriptor is owned by the driver, indicating that the hardware
     *      processing is finished */
    /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */ /*lint -e{522} */
    while ((Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalDescrIdx) == TRUE) &&
           (Eth_30_Tc3xx_GetTxReadyOfTxDescrState(globalDescrIdx) == ETH_30_TC3XX_DESCRIPTOR_READY)      &&
           (globalDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(globalDescrRingIdx)))
    {
      Eth_30_Tc3xx_MappedBufferOfTxDescrStateType relatedBufIdx;
      /* #3310 Retrieve the mapped buffer of the currently checked descriptor */
      relatedBufIdx = Eth_30_Tc3xx_GetMappedBufferOfTxDescrState(globalDescrIdx);

      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED);                         /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

      /* #3320 If the upper layer requested to be notified about the finished transmission */
      if (Eth_30_Tc3xx_GetUlTxConfStateOfTxBufferState(relatedBufIdx) == ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING)
      {
        Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType       txConfCallout;
        Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType rxTxCalloutsIdx;

        rxTxCalloutsIdx = Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(ctrlIdx);
        txConfCallout   = Eth_30_Tc3xx_GetTxConfirmationCalloutOfRxTxNotificationCallouts(rxTxCalloutsIdx);

        /* #33210 Leave the exclusive area for data consistency for the upper layer call to be performed next */
        Eth_30_Tc3xx_ExitExclusiveArea(DATA); 

        /* #33220 If no user callout was configured to be called instead of the EthIf_TxConfirmation */
        if (txConfCallout == NULL_PTR)
        {
          /* #332210 Call the EthIf TxConfirmation */
          EthIf_TxConfirmation(Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx), relatedBufIdx);                          /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
        }
        /* #33230 If a user callout was configured to be called instead of the EthIf TxConfirmation */
        else
        {
          /* #332310 Call the user callout */
          txConfCallout(Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx), relatedBufIdx);                                  /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL03 */ /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
        }

        /* #33240 Enter the exclusive area for data consistency again (Reason: Hardware and software synchronization) */
        Eth_30_Tc3xx_EnterExclusiveArea(DATA); 

        Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(relatedBufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);      /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */
      }

      /* #3330 If TimeSync is enabled */
#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
      if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
      {
        /* #33310 Reset the buffer state variable indicating if a timestamp is requested */
        Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(relatedBufIdx, (boolean)ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);                /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */

        /* #33320 Call the hardware dependent interface to reset the timestamp in the transmission descriptor */
        /*lint -e{522} */
        Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx);
      }
#endif

      /* #3340 Release the mapped buffer so it can be used for transmission again */
      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);                           /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */
      Eth_30_Tc3xx_SetBusyOfTxBufferState(relatedBufIdx, FALSE);                                                         /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */
      Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(globalDescrIdx, 0);                                                     /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

      /* #3350 Recharge the transmission descriptor so it can be used for transmission again */
      Eth_30_Tc3xx_LL_RechargeTxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx);

      /* #3360 Increment the descriptor index to check the next descriptor */
      Eth_30_Tc3xx_IncTxDescRingProcPos(globalDescrRingIdx);
      curDescrPos = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
      globalDescrIdx = (Eth_30_Tc3xx_TxDescrIterType)txDescrStartIdx + (Eth_30_Tc3xx_TxDescrIterType)curDescrPos;
      
      /* #3370 In polling mode */
      if (Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
      {
        /* #33710 If the currently checked ring is finished processing */
        if(Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalDescrIdx) == FALSE)
        {
          /* #337110 Check for events of other queues */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_SetTxEvents(ctrlIdx);
          descrRingIdx = Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(ctrlIdx);

          /* #337120 If another event has occurred */
          if(descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
          {
            /* #3371210 Calculate the indices of the descriptor to be checked */
            globalDescrRingIdx = descrRingIdx + Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
            txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(globalDescrRingIdx);
            txDescrStartIdx    = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);
            curDescrPos        = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
            globalDescrIdx     = (Eth_30_Tc3xx_TxDescrIterType) txDescrStartIdx + 
                                 (Eth_30_Tc3xx_TxDescrIterType) curDescrPos;
          }
          /* #337130 Otherwise */
          else
          {
            /* #3371310 Leave the loop */
            break;
          }
        }
      }
    }
    /* #340 Leave the exclusive area for data consistency */
    Eth_30_Tc3xx_ExitExclusiveArea(DATA); 
  }
} /* Eth_30_Tc3xx_Internal_TxConfirmation() */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer(
              uint8                                                      CtrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) BufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (BufIdxPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (BufPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (LenBytePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to provide a transmission buffer */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ProvideTxBuffer(localCtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ProvideTxBuffer(localCtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);                   /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_PROVIDE_TX_BUFFER, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ProvideTxBuffer */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Transmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Transmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
  Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType activeMacAddrStartIdx;

  activeMacAddrStartIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(localCtrlIdx);
  /* #10 Call Eth_30_Tc3xx_VTransmit() function with the ECUs own source MAC address as PhysAddrSrcPtr parameter */
  /* no transformation between local and global controller index necessary */
  return Eth_30_Tc3xx_VTransmit(CtrlIdx,                                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_AND_CSL_PTR_PASS */
                               BufIdx,
                               FrameType,
                               TxConfirmation,
                               LenByte,
                               PhysAddrPtr, /* PRQA S 0310 1 */ /* MD_Eth_30_Tc3xx_0310 */
                               (const uint8*)Eth_30_Tc3xx_GetAddrActiveMacAddress(activeMacAddrStartIdx)); /*lint !e545 */
} /* Eth_30_Tc3xx_Transmit */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit(
          uint8                               CtrlIdx,
          uint8                               BufIdx,
          Eth_FrameType                       FrameType,
          boolean                             TxConfirmation,
          uint16                              LenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrSrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* When VLAN-ID based frame queuing is enabled, there is no DET check implemented to check if this function is called
   * on the correct core. This is because, at this point we only have the buffer index reference and it will be
   * too complex to retrieve the mapped core ID from the buffer index, which will break the DET patter. The transmission
   * of the frame on correct core is ensured by the DET check implemented in Eth_30_Tc3xx_TxConfirmationFifo api   */


  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
  else if (BufIdx >= Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(localCtrlIdx)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (LenByte > (Eth_30_Tc3xx_GetLengthOfTxBufferData(BufIdx) -
                        (ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  else if (PhysAddrDstPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (PhysAddrSrcPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to transmit a frame */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_VTransmit(
        localCtrlIdx, BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrDstPtr, PhysAddrSrcPtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_VTransmit(
        localCtrlIdx, BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrDstPtr, PhysAddrSrcPtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */

  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_TRANSMIT, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_VTransmit */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmation
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmation(
  uint8 CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to confirm a frame transmission */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_TxConfirmation(localCtrlIdx, ETH_30_TC3XX_INVALID_FIFO_IDX);
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_TxConfirmation(localCtrlIdx);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_TX_CONFIRMATION, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_TxConfirmation */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmationFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmationFifo(
  uint8 ctrlIdx,
  uint8 fifoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(ctrlIdx); /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  Eth_30_Tc3xx_TxQueueIdxCoreIdMapStartIdxOfEthCtrlType queueIdxCoreIdMapStartIdx =
          Eth_30_Tc3xx_GetTxQueueIdxCoreIdMapStartIdxOfEthCtrl(localCtrlIdx);
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (fifoIdx >= Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrl(localCtrlIdx))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  /* No explicit check is added to prevent the below DET check when VLAN-ID based frame queuing is disabled because this
   * function is called only when the VLAN-ID based frame queuing is enabled */
  else if (Eth_30_Tc3xx_GetTxQueueIdxCoreIdMap(queueIdxCoreIdMapStartIdx + fifoIdx) != 
           (Eth_30_Tc3xx_TxQueueIdxCoreIdMapType) GetCoreID())
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* #20 Call internal Tx Confirmation with passed fifoIdx */
    Eth_30_Tc3xx_Internal_TxConfirmation(localCtrlIdx, fifoIdx);
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, ctrlIdx, ETH_30_TC3XX_SID_TX_CONFIRMATION, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_TxConfirmationFifo */ /* PRQA S 6050, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Tx.c
 *********************************************************************************************************************/
