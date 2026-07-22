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
/*!        \file  Eth_30_Tc3xx_Rx.c
 *        \brief  Reception implementation
 *
 *      \details  Reception part of the Ethernet controller driver implementation.
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

#define ETH_30_TC3XX_RX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_Rx.h"
#include "Eth_30_Tc3xx_Rx_Int.h"
#include "Eth_30_Tc3xx_MacHdl_Int.h"
#include "Eth_30_Tc3xx_CtrlModeHdl_Int.h"
#include "Eth_30_Tc3xx_Int.h"
#include "EthIf_Cbk.h"
#include "Os.h"
#include "Eth_30_Tc3xx_Cbk.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 * DEFINE CHECKS
 *********************************************************************************************************************/

#if((ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX +0) < 1)
# error "The difference to the previous descriptor has to be defined for ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX!"
#endif

/**********************************************************************************************************************
 *  END OF DEFINE CHECKS
 *********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPE
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_CalculateReceiveDescrRingIdx
 **********************************************************************************************************************/
/*! \brief      Calculates the next descriptor ring index with a pending receive event.
 *  \details    -
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(ETH_30_TC3XX_INVALID_FIFO_IDX) in
 *                            case of VLAN-ID based frame queuing disabled.
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CalculateReceiveDescrRingIdx(
  uint8 ctrlIdx,
  uint8 fifoIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a reception descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the reception descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxDescrRingPrevPos
 **********************************************************************************************************************/
/*! \brief      Retrieves the index of the previous descriptor in the given ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the reception descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]  currDescrIdx  Identifier of the current reception descriptor ring position the previous position
 *              shall be retrieved for 
 *              [range: 0 <= currDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrIterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingPrevPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         currDescrIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if reception of an Ethernet frame is allowed
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the related RX buffer
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                              [out] Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (adaption of position could be needed due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Actual length of the Ethernet frame contained in the buffer
 *                              [out] Available length of the Ethernet frame contained in the buffer
 *                                    (adaption of the actual length of the Ethernet frame could be needed due to
 *                                     insertion of an additional header between MAC addresses an Ether Type like in
 *                                     a EthSwt management use case)
 *  \return         TRUE  - Frame reception allowed
 *  \return         FALSE - Frame reception not allowed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different reception buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! \brief         Finishes the reception of a Ethernet frame
 *  \details       -
 *  \param[in]     ctrlIdx  Identifier of the Ethernet controller
 *                 [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]     bufIdx   Identifier of the related RX buffer
 *                 [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \context       TASK|ISR1|ISR2
 *  \reentrant     TRUE for different transmission buffer segments
 *  \pre           -
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive_ProcessValidFrame
 **********************************************************************************************************************/
/*! \brief       Helper for reception of an valid Ethernet frame
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx  Identifier of the reception descriptor ring position
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[in]   bufIdx         Identifier of the related RX buffer
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive_ProcessValidFrame(
  uint8                                      ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent
 **********************************************************************************************************************/
/*! \brief       Helper to set reception events and optionally  retrieve the index of a reception ring in which the
 *               highest priority pending event occurred.
 *  \details     -
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  descrRingIdxPtr Pointer to the retrieved highest priority pending receive event descriptor ring index
 *  \param[in]   isClearRequired Indicates if the highest prio pending event's descriptor ring index should be cleared
 *                 TRUE - The highest prio pending event should be cleared
 *                 FALSE - The highest prio pending event should not be cleared
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) descrRingIdxPtr,
        boolean                      isClearRequired);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_Receive
 **********************************************************************************************************************/
/*! \brief       Triggers the reception of an Ethernet frame
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(ETH_30_TC3XX_INVALID_FIFO_IDX) in
 *                            case of VLAN-ID based frame queuing disabled.
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
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_Receive(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive(
        uint8                                   CtrlIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) RxStatusPtr)
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
  else if (RxStatusPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to receive a frame */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_Receive(localCtrlIdx, ETH_30_TC3XX_INVALID_FIFO_IDX, RxStatusPtr);                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_Receive(localCtrlIdx, RxStatusPtr);                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_RECEIVE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_Receive */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Eth_30_Tc3xx_CalculateReceiveDescrRingIdx
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CalculateReceiveDescrRingIdx(
    uint8 ctrlIdx,
    uint8 fifoIdx)
{
  uint8 descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* #10 Check if VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #110 Assign the fifoIdx to descriptor ring index only if it is in the valid range */
    if (fifoIdx < (Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)))
    {
      descrRingIdx = fifoIdx;
    }
  }
  else
  {
    /* #120 Check for a new event in all reception rings and clear it if one is found */
    Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(ctrlIdx, &descrRingIdx, TRUE);                                                 /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  }

  return descrRingIdx;
}

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType procPos;
  Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType rxDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(descrRingIdx);
  procPos            = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx);
  /* #10 Increment current read position in RX descriptor ring */
  procPos++;

  /* #20 If the current read position in the RX descriptor ring is equal to the first invalid position */
  if (procPos >= (Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current read position in the RX descriptor ring to 0 to perform a wrap-around */
    procPos = 0u;
  }

  Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx, procPos);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncRxDescrRingProcPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxDescrRingPrevPos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrIterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingPrevPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         currDescrIdx)
{
  Eth_30_Tc3xx_RxDescrIterType prevDescrIdx;
  Eth_30_Tc3xx_SegNumOfRxBufferHandlingType numOfSegments;
  Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType numOfDescr;
  Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType rxDescEndIdx;

  rxDescEndIdx   = Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(descrRingIdx);

  numOfDescr     = Eth_30_Tc3xx_GetDescrNumOfRxBufferHandling(descrRingIdx);
  numOfSegments  = Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx);

  /* #10 If there are additional descriptors configured that are not mapped to buffers, e.g. link descriptors */
  if(numOfDescr > numOfSegments)
  {
    /* #110 Calculate the actual end of the descriptor ring by subtracting the number of additional descriptors */
    rxDescEndIdx = rxDescEndIdx - (Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType)(numOfDescr - numOfSegments);
  }

  /* #20 Calculate the previous descriptor index */
  prevDescrIdx = ((currDescrIdx + rxDescEndIdx) - (uint8)ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX) % rxDescEndIdx;

  return prevDescrIdx;
} /* Eth_30_Tc3xx_GetRxDescrRingPrevPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
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
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for RX frame processing */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    boolean isMgmtFrameOnly = TRUE;

    /* #110 Perform the call of the EthSwt driver interface for RX frame processing */
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #120 If the operation performed by the EthSwt driver interface fails */
    if (Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      if (Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr, &isMgmtFrameOnly)/* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_AND_STACK_REF_PASS */
          == E_NOT_OK)
      {
        /* #1210 Return that the fram reception is not allowed */
        result = FALSE;
      }
      /* #130 If the operation performed by the EthSwt driver interface is successful */
      else
      {
        /* #1310 If the EthSwt driver signals that frame shall not be received by stack (EthSwt management frame only) */
        if (isMgmtFrameOnly == TRUE)
        {
          /* #13110 Return that the fram reception is not allowed */
          result = FALSE;
        }
      }
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsFrameRxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface to indicate the end of reception */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface to indicate the end of reception */
    if (Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx);                                 /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03 */
    }
  }
} /* Eth_30_Tc3xx_FinishFrameRx() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_Receive
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
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_Receive(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 descrRingIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Synchronization of hardware and software) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA_MULTI_CORE); 

  (*rxStatusPtr) = ETH_NOT_RECEIVED;                                                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Calculate the next pending Rx Descriptor */
  descrRingIdx = Eth_30_Tc3xx_CalculateReceiveDescrRingIdx(ctrlIdx, fifoIdx);

  /* #30 If a descriptor ring with a pending reception event could be retrieved */
  if (descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
  {
    /* #310 Retrieve the next descriptor to be processed in the ring and the mapped buffer */
    Eth_30_Tc3xx_RxDescrIterType prevDescrIdx;
    Eth_30_Tc3xx_RxDescrIterType globalRxDescrIdx;
    Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx;
    Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx;
    Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType rxDescRingStartPos;
    Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType rxDescRingLocalProcPos;

    globalDescrRingIdx     = (uint8_least)descrRingIdx + Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
    rxDescRingStartPos     = Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(globalDescrRingIdx);
    rxDescRingLocalProcPos = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(globalDescrRingIdx);
    globalRxDescrIdx       = (uint8_least)rxDescRingStartPos + (uint8_least)rxDescRingLocalProcPos;

    /* #320 If the retrieved rx descriptor index is valid for the descriptor ring */
    if (globalRxDescrIdx < Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(globalDescrRingIdx))
    {
      bufIdx = Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(globalRxDescrIdx);

      /* #3210 If the retrieved buffer index is valid  */
      if (bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(globalDescrRingIdx))
      {
        /* #32110 Synchronize the RAM and peripheral register access */
        Appl_Eth_30_Tc3xx_MemoryBarrier();
        /* #32120 If the hardware is finished with processing the descriptor holding the frame to be received */
        /*lint -e{522} */
        if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == TRUE)
        {
          prevDescrIdx = Eth_30_Tc3xx_GetRxDescrRingPrevPos(globalDescrRingIdx, globalRxDescrIdx);

          /* #321210 If there is no error flag set in the descriptor status flags */
          /*lint -e{522} */
          if (Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == FALSE)
          {
            /* #3212110 Call the internal interface to proceed with a valid frame reception */
            Eth_30_Tc3xx_Receive_ProcessValidFrame(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx, bufIdx);
          }
          /* #321220 If an error flag is set in the descriptor status flags */
          else
          {
            /* #3212210 Discard the frame because it is invalid */
          }
          /* #321230 If the previous descriptor of the one currently operated is also still owned by the driver
           *         which means that all buffers in the currently processed ring are blocked by the software */
          if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, prevDescrIdx) == TRUE)
          {
            /* #3212310  Increment the warning counter */
            Eth_30_Tc3xx_IncWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

            /* #3212320 If a callout is configured to be notified when the reception buffers are all in use */
            if(Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(0) != NULL_PTR)
            {
              /* #32123210 Call the configured callout to notify the user that all reception buffers are in use in the
               *           currently processed buffer ring */
              Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(0)(ctrlIdx, descrRingIdx);                                /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
            }
          }
          /* #321240 Recharge the current descriptor so that the next frame can be received in it */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RechargeRxDescriptor(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx);

          /* #321250 Adapt the descriptor ring after descriptor processing has been finished */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx);

          /* #321260 Increment the position of the current descriptor to check if already more data is available */
          Eth_30_Tc3xx_IncRxDescrRingProcPos(globalDescrRingIdx);

          /* #321270 Perform additional hardware dependent steps to rearm the MAC for further reception */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RearmMacForReception(ctrlIdx, globalDescrRingIdx);

          /* Frames may have been lost because of a buffer overflow or unavailable buffers.
          Nevertheless no error is returned to the EthIf.
          Otherwise congestion could happen in polling mode because ETH_RECEIVED_MORE_DATA_AVAILABLE  can not be
          returned to the EthIf anymore and a maximum of one frame per mainfunction can be processed. */
          rxDescRingLocalProcPos = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(globalDescrRingIdx);
          globalRxDescrIdx       = (uint8_least)rxDescRingStartPos + (uint8_least)rxDescRingLocalProcPos;
          /* No check of globalRxDescrIdx necessary, as the CurProcPos is calculated and checked for wrap-around during 
           * Eth_30_Tc3xx_IncRxDescrRingProcPos(globalDescrRingIdx). Eth_30_Tc3xx_LL_RearmMacForReception should not
           * change the CurProcPos.
           */

          /* #321280 If the next descriptor is also already processed by the DMA and holding frame data */
          /*lint -e{522} */
          if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == TRUE)
          {
            /* #3212810 Set another reception event on the corresponding descriptor ring and set the reception status
             *          to indicate that more data is available on the current reception queue only when VLAN-ID based
             *          frame queuing in not enabled since there is no need for explicit event when VLAN-ID based frame
             *          queuing is enabled */ 
            if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
            {
              Eth_30_Tc3xx_SetRxEvent(ctrlIdx, descrRingIdx);
            }

            (*rxStatusPtr) = ETH_RECEIVED_MORE_DATA_AVAILABLE;                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
          }
          /* #321290 If the next descriptor is not processed yet by the DMA */
          else
          {
            /* #3212910 Check for other reception rings only when VLAN-ID based frame queuing is not enabled */
            if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
            {
              Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(ctrlIdx, &descrRingIdx, FALSE);                          /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */

              if(descrRingIdx == ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
              {
                /* #32129110 Set the reception status to indicate that the reception has successfully finished */
                (*rxStatusPtr) = ETH_RECEIVED;                                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
              }
              /* #3212920 If there was a event in any other reception ring and the rx-interrupt is disabled */
              else
              {
                /* #32129210 Set the reception status to indicate that more data is available */
                (*rxStatusPtr) = ETH_RECEIVED_MORE_DATA_AVAILABLE;                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
              }
            }
            else
            {
              (*rxStatusPtr) = ETH_RECEIVED;                                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
            }
          }
        }
        /* #32130 If the hardware is not yet finished with processing the descriptor holding the frame to be received */
        else
        {
          /* #321310 Set the reception status to indicate that the reception has failed */
          (*rxStatusPtr) = ETH_NOT_RECEIVED;                                                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        }
      }
    }
  }
  /* #40 Leave the exclusive area for data consistency */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA_MULTI_CORE); 
} /* Eth_30_Tc3xx_Internal_Receive() */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive_ProcessValidFrame
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
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive_ProcessValidFrame(
  uint8                                      ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_RxBufferIterType bufferOffsetStart;
  Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType rxBufferAlignedSegSize;
  Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType rxBufferEndIdx;
  Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType rxBufferStartIdx;

  /* ----- Implementation ----------------------------------------------- */
  rxBufferAlignedSegSize = Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(descrRingIdx);
  rxBufferStartIdx       = Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(descrRingIdx);
  rxBufferEndIdx         = Eth_30_Tc3xx_GetRxBufferEndIdxOfRxBufferHandling(descrRingIdx);

  bufferOffsetStart      = (uint16_least)rxBufferStartIdx + ((uint16_least)bufIdx * (uint16_least)rxBufferAlignedSegSize);
  /* #10 If the end-index of reception buffer and the retrieved buffer start index are
   *     at least one minimum frame size apart */
  if ((bufferOffsetStart + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) <= rxBufferEndIdx)
  {
    uint16 lenByte;
    boolean isBroadcast;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetDstMac;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetSrcMac;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetEtherType;
    uint8 const* bufPtrDstMac;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtrSrcMac;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtrEtherType;

    bufferOffsetDstMac    = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST;
    bufferOffsetSrcMac    = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC;
    bufferOffsetEtherType = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE;
    /* #110 Extract the received frame's length from the corresponding descriptor */
    /*lint -e{522} */
    lenByte = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(ctrlIdx, descrRingIdx, descrIdx);

    /* #120 Retrieve pointers to the positions of source and destination MAC address, the Ethernet type field and the
     *      payload data */
    bufPtrDstMac    = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetDstMac);
    bufPtrSrcMac    = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetSrcMac);
    bufPtrEtherType = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetEtherType);

    /* #130 Check whether the received frame is a broadcast */
    isBroadcast = Eth_30_Tc3xx_IsBroadcast(bufPtrDstMac);                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_PASS_CSL0X */

    lenByte -= ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE;

    /* #140 If the reception of the frame is allowed */
    if (Eth_30_Tc3xx_IsFrameRxAllowed(ctrlIdx, (Eth_BufIdxType)bufIdx, &bufPtrEtherType, &lenByte) == TRUE)              /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X */
    {
      /* #1410 If the returned buffer length of the switch management interface is valid for a frame holding a payload */
      if ((bufferOffsetStart + lenByte) < rxBufferEndIdx)
      {
        uint16 frameType;
        P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC)            bufPtrData;
        Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType         rxIndCallout;
        Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType rxTxCalloutsIdx;

        /* #14310 Retrieve the frame type */
        frameType  = (uint16)((uint16)bufPtrEtherType[ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX]
                                                   << ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_LSHIFT);
        frameType |=          (uint16)bufPtrEtherType[ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX];

        /* #14320 retrieve a pointer to the payload of the frame */
        /* PRQA S 3305, 0310 1 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
        bufPtrData = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))(&bufPtrEtherType[ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE]);

        /* #14330 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) 
        {
          Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType procPos;
          Eth_30_Tc3xx_RxDescrRingProcIterType rxDescrRingProcIdx;
          Eth_30_Tc3xx_RxTsContextStackPosType rxTsContextStackPos;
          Eth_30_Tc3xx_RxTsContextStackIterType rxTsContextStackIdx;
          Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType rxTsContextEndIdx;
          Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType rxTsContextStackStartIdx;

          rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(descrRingIdx);
          procPos            = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx);

          /* #143310 Increment the reception timestamp context stack position and save descriptor and ring index in the
           *         global context variable */
          Eth_30_Tc3xx_IncRxTsContextStackPos(ctrlIdx);                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

          rxTsContextStackPos      = Eth_30_Tc3xx_GetRxTsContextStackPos(ctrlIdx);
          rxTsContextStackStartIdx = Eth_30_Tc3xx_GetRxTsContextStackStartIdxOfTsHandling(ctrlIdx);
          rxTsContextEndIdx        = Eth_30_Tc3xx_GetRxTsContextStackEndIdxOfTsHandling(ctrlIdx);
          rxTsContextStackIdx      = (uint8_least)rxTsContextStackStartIdx + (uint8_least)rxTsContextStackPos;

          if (rxTsContextStackIdx < rxTsContextEndIdx)
          {
            Eth_30_Tc3xx_SetRingIdxOfRxTsContextStack(rxTsContextStackIdx,                                               /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK */
                (Eth_30_Tc3xx_RingIdxOfRxTsContextStackType)descrRingIdx);
            Eth_30_Tc3xx_SetDescrIdxOfRxTsContextStack(rxTsContextStackIdx, procPos);                                    /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK */
          }
        }

        rxTxCalloutsIdx = Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(ctrlIdx);
        rxIndCallout    = Eth_30_Tc3xx_GetRxIndicationCalloutOfRxTxNotificationCallouts(rxTxCalloutsIdx);
        /* #14340 Leave the exclusive area for data consistency for the upper layer call to be performed next */
        Eth_30_Tc3xx_ExitExclusiveArea(DATA); 

#ifdef ETH_TEST_SUITE_CODE /* COV_ETH_TEST_SUITE */
# ifndef _ETH_TEST_SUITE_CDK_RUN_ /* COV_ETH_TEST_SUITE */
        if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
        {
          /* Test code used for QoS/VLAN_ID based frame queuing reception queue tests */
          EthClient_RxQueueCounter[ctrlIdx][descrRingIdx]++;
        }
# endif /* _ETH_TEST_SUITE_CDK_RUN_ */
#endif /* ETH_TEST_SUITE_CODE */

        /* #14350 If no user callout to be called instead of the Rx-Indication is configured */
        if (rxIndCallout == NULL_PTR)
        {
          /* #143510 Call the EthIf Rx-Indication */
          EthIf_RxIndication(                                                                                           /* SBSW_ETH_30_TC3XX_PUB_FCT_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC */
              Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx),                                                           /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
              frameType,
              isBroadcast,
              bufPtrSrcMac,
              bufPtrData,
              (uint16)(lenByte - ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE));
        }
        /* #14360 If a user callout to be called instead of the Rx-Indication is configured */
        else
        {
          /* #143610 Call the user callout */
          rxIndCallout(                                                                                                 /* SBSW_ETH_30_TC3XX_OPT_API_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC_CSL03 */
              Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx),                                                           /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
              frameType,
              isBroadcast,
              bufPtrSrcMac,
              bufPtrData,
              (uint16)(lenByte - ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE));
        }
        /* #14370 Enter the exclusive area for data consistency again (Reason: Hardware and software synchronization) */
        Eth_30_Tc3xx_EnterExclusiveArea(DATA); 

        /* #14380 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) 
        {
          /* #143810 Decrement the current reception timestamp context stack position */
          Eth_30_Tc3xx_DecRxTsContextStackPos(ctrlIdx);                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        }
      }
    }
    /* #150 Finish the frame reception */
    Eth_30_Tc3xx_FinishFrameRx(ctrlIdx, (Eth_BufIdxType)bufIdx);
  }
} /* Eth_30_Tc3xx_Receive_ProcessValidFrame() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent
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
 */
ETH_30_TC3XX_RX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) descrRingIdxPtr,
        boolean                      isClearRequired)
{
  /* #10 If the reception interrupt is disabled */
  if (Eth_30_Tc3xx_IsRxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
  {
    /* #110 Set pending reception events in the software if they are pending on the hardware */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_SetRxEvents(ctrlIdx);
  }

  /* #20 If the caller requests that a check for and clear the highest priority reception event is made */
  if(isClearRequired == TRUE)
  {
    /* #210 Check for the highest priority reception event and clear it*/
    *descrRingIdxPtr = Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing(ctrlIdx);                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 If no clear is required */
  else
  {
    /* #310 Only check for an occured event */
    *descrRingIdxPtr = Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(ctrlIdx);                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
} /* Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ReceiveFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReceiveFifo(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(ctrlIdx); /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

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
  else if (rxStatusPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (fifoIdx >= Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrl(localCtrlIdx))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  /* No explicit check is added to prevent the below DET check when VLAN-ID based frame queuing is disabled because this
   * function is called only when the VLAN-ID based frame queuing is enabled */
  else if (Eth_30_Tc3xx_GetRxQueueIdxCoreIdMap(Eth_30_Tc3xx_GetRxQueueIdxCoreIdMapStartIdxOfEthCtrl(localCtrlIdx) + 
                                               fifoIdx) != (Eth_30_Tc3xx_RxQueueIdxCoreIdMapType) GetCoreID())
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call internal receive Confirmation with passed fifoIdx */
    Eth_30_Tc3xx_Internal_Receive(localCtrlIdx, fifoIdx, rxStatusPtr);                                /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, ctrlIdx, ETH_30_TC3XX_SID_RECEIVE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_ReceiveFifo */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Rx.c
 *********************************************************************************************************************/
