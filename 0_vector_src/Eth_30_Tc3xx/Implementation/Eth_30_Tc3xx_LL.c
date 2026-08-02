/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_LL.c
 *        \brief  Lower Layer source file of Ethernet Driver
 *
 *      \details  Implementation of lower layer part of Ethernet driver.
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
#define ETH_30_TC3XX_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_LL_Int.h"
#include "Eth_30_Tc3xx_LL.h"
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_LL_CtrlModeHdl_Int.h"
#include "Eth_30_Tc3xx_LL_CtrlModeHdl.h"
#include "Eth_30_Tc3xx_LL_IrqHandler_Int.h"
#include "Eth_30_Tc3xx_LL_IrqHandler.h"
#include "Eth_30_Tc3xx_LL_MacHdl_Int.h"
#include "Eth_30_Tc3xx_LL_MacHdl.h"
#include "Eth_30_Tc3xx_LL_MiiAccess_Int.h"
#include "Eth_30_Tc3xx_LL_MiiAccess.h"
#include "Eth_30_Tc3xx_LL_Rx_Int.h"
#include "Eth_30_Tc3xx_LL_Rx.h"
#include "Eth_30_Tc3xx_LL_Statistics_Int.h"
#include "Eth_30_Tc3xx_LL_Tx_Int.h"
#include "Eth_30_Tc3xx_LL_Tx.h"
#include "Eth_30_Tc3xx_LL_TimeSync_Int.h"
#include "Eth_30_Tc3xx_LL_TimeSync.h"
#include "Eth_30_Tc3xx_LL_TrafficHandling_Int.h"
#include "Eth_30_Tc3xx_LL_TrafficHandling.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function with related register address and queue index */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ0, ETH_30_TC3XX_REG_OFFS_DMA_CH0_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ0Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ0, ETH_30_TC3XX_REG_OFFS_DMA_CH0_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ0Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ1, ETH_30_TC3XX_REG_OFFS_DMA_CH1_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ1Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ1, ETH_30_TC3XX_REG_OFFS_DMA_CH1_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ1Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ2, ETH_30_TC3XX_REG_OFFS_DMA_CH2_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ2Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ2, ETH_30_TC3XX_REG_OFFS_DMA_CH2_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ2Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ3, ETH_30_TC3XX_REG_OFFS_DMA_CH3_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ3Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ3, ETH_30_TC3XX_REG_OFFS_DMA_CH3_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ3Rx() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_ArmPpsEventOnTime
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ArmPpsEventOnTime(
    uint8 CtrlIdx,
    P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;
  boolean        trgtbusy;

  uint8          localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl() )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( TimestampPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    if(Eth_30_Tc3xx_IsArmPpsOnTimeEnabledOfEthCtrlTc3xx(localCtrlIdx) == TRUE)
    {
      /* 10 Check target time register busy bit */
      trgtbusy = Eth_30_Tc3xx_Reg_IsBitMaskSet(localCtrlIdx,
                  ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_NANOSECONDS,
                      ETH_30_TC3XX_REG_OFFS_MAC_PPS_NANOSECOND_TRGTBUSY0);

      /* #20 Check the range of nanosecond and value of seconds. */
      if ((TimestampPtr->secondsHi == ETH_30_TC3XX_PPS_TIME_SECONDS_HI) &&
          (TimestampPtr->nanoseconds <= ETH_30_TC3XX_PPS_TIME_NANOSECONDS_RANGE) && (!trgtbusy))
      {
        /* #210 Program the start time value in the PPS timer registers. */
        Eth_30_Tc3xx_Reg_Write(localCtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_SECONDS,
            TimestampPtr->seconds);
        Eth_30_Tc3xx_Reg_Write(localCtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_NANOSECONDS,
            TimestampPtr->nanoseconds);

        /* Width and interval of PPS signal output is configured in the initial configuration of MAC */

        /* #220 Set the Pps control register for single pulse generation. */
        Eth_30_Tc3xx_Reg_SetBitMask(localCtrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG,
            ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG_PPSCMD);

        retVal = E_OK;
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_ARM_PPS_EVENT_ON_TIME, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

 /**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL.c
 *********************************************************************************************************************/
