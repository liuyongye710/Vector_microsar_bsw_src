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
/*!        \file  Eth_30_Vtt_LL_TimeSync.h
 *        \brief  Timer sub-module header of the Ethernet controller driver
 *
 *      \details  Provides access to the hardware timer related API of the Ethernet controller driver.
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_VTT_LL_TIME_SYNC_H)
# define ETH_30_VTT_LL_TIME_SYNC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Vtt_Int.h"

# if (ETH_30_VTT_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#  if !defined (ETH_30_VTT_LL_TIME_SYNC_LOCAL) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_VTT_LL_TIME_SYNC_LOCAL                              LOCAL
#  endif /* ETH_30_VTT_LL_TIME_SYNC_LOCAL */

#  if !defined (ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE                       LOCAL_INLINE
#  endif /* ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#  define ETH_30_VTT_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_StartTimesyncClock()
 *********************************************************************************************************************/
/*! \brief       Function for starting the timesync clock of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timesync clock shall be started
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \note        The time stamps from CANoe is the same as you can see in the CANoe Trace window.
 *               It starts with the value 0 when the measurement starts in CANoe. 
 *               So the TimesyncClock will start when the measurement starts. 
 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_StartTimesyncClock(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_CaptureHwTime
 **********************************************************************************************************************/
/*! \brief       Captures the hardware timer of the Ethernet controller and returns the time stamp
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[out]  timeStampPtr Time stamp captured
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \pre         -
 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_SetHwTime
 **********************************************************************************************************************/
/*! \brief       Sets the hardware and software part of the timer to the given time
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   timeStampPtr Time to set
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different Ethernet controllers
 *  \pre         Exclusive area for hardware timer (EXCLUSIVE_AREA_TIME) entered
 *  \note        The time stamps from CANoe is the same as you can see in the CANoe Trace window.
 *               It starts with the value 0 when the measurement starts in CANoe.
 *               A reset while the measurement is in progress is not possible.
 **********************************************************************************************************************/
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_SetHwTime(
          uint8                                    ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_GetTxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the TX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   ringIdx    Identifier of the TX descriptor ring
 *               [range: 0 <= ringIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx   Identifier of the TX descriptor within the ring
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \param[out]  timeStampPtr Transmission time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different TX descriptor
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_GetTxTimeStamp(
        uint8                                                       ctrlIdx,
        Eth_30_Vtt_RingIdxOfTxTsContextType                         ringIdx,
        Eth_30_Vtt_DescrIdxOfTxTsContextType                        descrIdx,
  P2VAR(Eth_TimeStampType,                    AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_GetRxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the RX time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   ringIdx    Identifier of the RX descriptor ring
 *               [range: 0 <= ringIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx   Identifier of the RX descriptor within the ring
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \param[out]  timeStampPtr  Reception time stamp
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different RX descriptor
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_GetRxTimeStamp(
        uint8                                                            ctrlIdx,
        Eth_30_Vtt_RingIdxOfRxTsContextStackType                         ringIdx,
        Eth_30_Vtt_DescrIdxOfRxTsContextStackType                        descrIdx,
  P2VAR(Eth_TimeStampType,                         AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
*  Eth_30_Vtt_LL_SendSingleFrame
**********************************************************************************************************************/
/*! \brief      Send a single frame
*  \details     Send a single frame, in order to make the VttCntrl can update the recent time stamping. Because the 
*               VttCntrl can update the time stamping only during receiving or sending a frame.
*  \param[in]   uint16       The length of the data to be sent
*  \context     ANY
*  \synchronous FALSE
*  \reentrant   TRUE
*  \pre         -
**********************************************************************************************************************/
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SendSingleFrame(
  uint16 DataLen);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITONS
 *********************************************************************************************************************/

#  ifndef ETH_30_VTT_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_TimeSync_StartTimesyncClock
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_StartTimesyncClock(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_TimeSync_StartTimesyncClock() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_CaptureHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint16 DataLen = 6u;

  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Get the hardware time */
  if (Eth_30_Vtt_LL_SendSingleFrame(DataLen) == E_OK)
  {
    if (VttEth_GetHwTime(timeStampPtr) == E_OK) 
	{
	  retVal = E_OK;
	};
  }
  return retVal;
} /* Eth_30_Vtt_LL_TimeSync_CaptureHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_SetHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_SetHwTime(
         uint8                                     ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(timeStampPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  retVal = E_OK;
  return retVal;
} /* Eth_30_Vtt_LL_TimeSync_SetHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_GetTxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_GetTxTimeStamp(
        uint8                                                       ctrlIdx,
        Eth_30_Vtt_RingIdxOfTxTsContextType                         ringIdx,
        Eth_30_Vtt_DescrIdxOfTxTsContextType                        descrIdx,
  P2VAR(Eth_TimeStampType,                    AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Vtt_TxDescrPtrType txDescPtr = Eth_30_Vtt_GetAddrTxDescr(descrIdx);
  ETH_30_VTT_DUMMY_STATEMENT(ringIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  if (VttEth_IsCANoeTimerOK() == E_OK) 
  {
    /* #10 Get the time stamp in rx descriptor */
    timeStampPtr->nanoseconds = txDescPtr->nanoseconds;
    timeStampPtr->seconds = txDescPtr->seconds;
    timeStampPtr->secondsHi = txDescPtr->secondsHi;
    retVal = E_OK;
  }

  return retVal;
} /* Eth_30_Vtt_LL_TimeSync_GetTxTimeStamp() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_TimeSync_GetRxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TimeSync_GetRxTimeStamp(
        uint8                                                            ctrlIdx,
        Eth_30_Vtt_RingIdxOfRxTsContextStackType                         ringIdx,
        Eth_30_Vtt_DescrIdxOfRxTsContextStackType                        descrIdx,
  P2VAR(Eth_TimeStampType,                         AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Vtt_RxDescrPtrType rxDescPtr = Eth_30_Vtt_GetAddrRxDescr(descrIdx);
  ETH_30_VTT_DUMMY_STATEMENT(ringIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  if (VttEth_IsCANoeTimerOK() == E_OK) 
  {
    /* #10 Get the time stamp in rx descriptor */
    timeStampPtr->nanoseconds = rxDescPtr->nanoseconds;
    timeStampPtr->seconds = rxDescPtr->seconds;
    timeStampPtr->secondsHi = rxDescPtr->secondsHi;
    retVal = E_OK;
  }

  return retVal;
} /* Eth_30_Vtt_LL_TimeSync_GetRxTimeStamp() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_LL_SendSingleFrame
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SendSingleFrame(uint16 DataLen)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint16 Idx;
  uint8 BufIdx;
  uint8 *u8BufPtr = NULL_PTR;
  Eth_DataType *BufPtr = NULL_PTR;
  uint16 LenByte = DataLen;
  uint8 testerAddr[6] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };

  /* #10 Provide the tx buffer */
  Eth_30_Vtt_ProvideTxBuffer(0, &BufIdx, &BufPtr, &LenByte);

  u8BufPtr = (uint8 *)BufPtr;
  for (Idx = 0; Idx < LenByte; Idx++)
  {
	  u8BufPtr[Idx] = 0u; /* The whole buffer is initialized to zero */
  }

  /* #20 Send a single frame */
  retVal = Eth_30_Vtt_Transmit(0, BufIdx, LenByte, 1, DataLen, testerAddr);

  if (E_OK != retVal)
  {
	  Eth_30_Vtt_Transmit(0, BufIdx, 0, 1, 0, testerAddr); /* release provided buffer */
  }

  return retVal;
} /* Eth_30_Vtt_LL_SendSingleFrame() */

#  endif /* ETH_30_VTT_UNIT_TEST */

#  define ETH_30_VTT_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_VTT_ENABLE_TIMESYNC */

#endif /* ETH_30_VTT_LL_TIME_SYNC_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL_TimeSync.h
 *********************************************************************************************************************/
