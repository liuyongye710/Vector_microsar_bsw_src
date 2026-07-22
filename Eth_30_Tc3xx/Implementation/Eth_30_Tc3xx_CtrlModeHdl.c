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
/*!        \file  Eth_30_Tc3xx_CtrlModeHdl.c
 *        \brief  Controller mode handling implementation of Ethernet controller driver
 *
 *      \details  Controller mode handling implementation of the Ethernet controller driver.
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

#define ETH_30_TC3XX_CTRL_MODE_HDL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_CtrlModeHdl.h"
#include "Eth_30_Tc3xx_CtrlModeHdl_Int.h"
#include "Eth_30_Tc3xx_TimeSync_Int.h"
#include "Eth_30_Tc3xx_LL_MacHdl_Int.h"
#include "Eth_30_Tc3xx_LL_Statistics_Int.h"
#include "Eth_30_Tc3xx_LL_TimeSync_Int.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
 **********************************************************************************************************************/
/*! \brief      Initializes the transmission and reception buffers, descriptors and structures
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context    TASK
 *  \reentrant  TRUE for different Ethernet controllers
 *  \pre        -
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes an Ethernet controller
 *  \details     Function initializes a Ethernet controller and the related variables
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   cfgIdx   Identifier of the configuration (only 0 supported)
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ControllerInit(
  uint8 ctrlIdx,
  uint8 cfgIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ValidControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes a successfully reset Ethernet controller
 *  \details     Function performs the initialization steps for a successfully reset Ethernet controller and the
 *               corresponding variables so it is possible to set it in operation afterwards.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ValidControllerInit(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetControllerMode
 **********************************************************************************************************************/
/*! \brief       Sets the operation mode of an Ethernet controller
 *  \details     Function sets the operation mode of the Ethernet controller so it is either turned off (no frame
 *               reception and transmission) or turned on (frames can be transmitted and received).
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ctrlMode  Operation mode that shall be applied:
 *                         ETH_MODE_DOWN - Ethernet controller shall be turned off
 *                         ETH_MODE_ACTIVE - Ethernet controller shall be turned on
 *  \return      E_NOT_OK - Operation mode couldn't be applied
 *  \return      E_OK - Operation mode successfully applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetControllerMode(
  uint8        ctrlIdx,
  Eth_ModeType ctrlMode);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetControllerMode
 **********************************************************************************************************************/
/*! \brief       Retrieves the current operation mode of an Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  ctrlModePtr  Operation mode retrieved
 *  \return      E_NOT_OK - Retrieval of operation mode failed
 *  \return      E_OK - Operation mode successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetControllerMode(
        uint8                               ctrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) ctrlModePtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ControllerInit
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
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ControllerInit(
  uint8 ctrlIdx,
  uint8 cfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* PRQA S 2982 */ /* MD_Eth_30_Tc3xx_2982 */
  Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType hwLoopTimeout = 0;
  Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType userPreCtrlInitCalloutFctPtr;
  Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType userPostCtrlInitCalloutFctPtr;

  ETH_30_TC3XX_DUMMY_STATEMENT(cfgIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If a user callout to be executed before the actions in Eth_ControllerInit are performed is configured */
  userPreCtrlInitCalloutFctPtr = Eth_30_Tc3xx_GetPreInitUserCalloutOfUserInitCallouts(0);
  if (userPreCtrlInitCalloutFctPtr != NULL_PTR)
  {
    /* #110 Call the configured user function */
    userPreCtrlInitCalloutFctPtr(ctrlIdx);                                                                              /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
  }

  /* #20 Perform hardware configuration which needs to be done before MAC reset */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_PreResetMac(ctrlIdx);

  /* #30 Call the hardware dependent interface to perform a soft reset */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ResetMac(ctrlIdx);

  /* #40 While the soft-reset is not finished yet */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsResetMacFinished(ctrlIdx) == FALSE)
  {
    /* #410 If the timeout for the soft-reset has occurred */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #4110 If configured, report the error E_ACCESS to the DEM and return with E_NOT_OK from Eth_ControllerInit */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
      break;
    }
    /* #420 Otherwise the timeout has not yet occurred, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #50 If the previously performed software reset was successful */
  if (retVal == E_OK)
  {
    /* #510 Call the internal interface to proceed with the controller initialization after software reset */
    retVal = Eth_30_Tc3xx_Internal_ValidControllerInit(ctrlIdx);
  }
  /* #60 If a user callout to be executed after the actions in Eth_ControllerInit are performed is configured */
  userPostCtrlInitCalloutFctPtr = Eth_30_Tc3xx_GetPostInitUserCalloutOfUserInitCallouts(0);
  if (userPostCtrlInitCalloutFctPtr != NULL_PTR)
  {
    /* #610 Call the configured user function */
    userPostCtrlInitCalloutFctPtr(ctrlIdx);                                                                             /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_ControllerInit() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ValidControllerInit
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
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ValidControllerInit(
  uint8 ctrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* PRQA S 2982 */ /* MD_Eth_30_Tc3xx_2982 */
  Eth_30_Tc3xx_RegDataIterType regDataIdx;
  Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType activeMacAddrStartIdx;

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
  Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the global mode variable */
  Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ETH_MODE_DOWN);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

  /* #20 Loop over all registers to be initialized or configured */
  for (regDataIdx = Eth_30_Tc3xx_GetRegDataStartIdxOfEthCtrl(ctrlIdx);
       regDataIdx < Eth_30_Tc3xx_GetRegDataEndIdxOfEthCtrl(ctrlIdx);
       regDataIdx++)
  {
    /* #210 Initialize the register*/
    Eth_30_Tc3xx_Reg_Initialize(ctrlIdx, Eth_30_Tc3xx_GetOffsetOfRegData(regDataIdx),
                                     Eth_30_Tc3xx_GetValueOfRegData(regDataIdx), 
                                     Eth_30_Tc3xx_GetAccessModeOfRegData(regDataIdx));
  }

  /* #30 Initialize the pending RX and TX frame event state variables */
  Eth_30_Tc3xx_SetPendingTxEventsOfEthCtrlState(ctrlIdx, 0);                                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
  Eth_30_Tc3xx_SetPendingRxEventsOfEthCtrlState(ctrlIdx, 0);                                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

  /* #40 Call the internal interface to Initialize all buffers and descriptors */
  Eth_30_Tc3xx_InitBuffersAndDescriptors(ctrlIdx);

  activeMacAddrStartIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
  /* #50 Call the hardware dependent interface to write the configured MAC address to the MAC address registers */
  /* PRQA S 0310 1 */ /* MD_Eth_30_Tc3xx_0310 */ /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMacAddressToRegister(ctrlIdx,                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_GEN_PTR_PASS_CSL03 */
      (const uint8*)Eth_30_Tc3xx_GetAddrActiveMacAddress(activeMacAddrStartIdx));

  /* #60 Call the hardware dependent interface to reset the frame counters */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ResetCounters(ctrlIdx);

#if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
  (void)Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);
#endif

#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
  /* #70 If TimeSync is enabled */
  if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #710 Initialize the TimeSync settings */
    Eth_30_Tc3xx_SetRxTsContextStackPos(ctrlIdx, ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS);                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
    retVal |= Eth_30_Tc3xx_TimeSync_Init(ctrlIdx); /* PRQA S 2986 */ /* MD_Eth_30_Tc3xx_2986 */
  }
#endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
  /* #80 Loop over all multicast bucket counters */
  for (multicastBucketCountersIdx = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
       multicastBucketCountersIdx < Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
       multicastBucketCountersIdx++)
  {
    /* #810 Set the current multicast bucket counter to its initial value */
    Eth_30_Tc3xx_SetMulticastBucketCounters(multicastBucketCountersIdx, 0);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }
  /* #90 Set the promiscuous mode counter to its initial value */
  Eth_30_Tc3xx_SetPromiscuousModeCounter(ctrlIdx, 0);                                                                    /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

  retVal |= Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(ctrlIdx); /* PRQA S 2986 */ /* MD_MSR_RetVal */

  return retVal;
} /* Eth_30_Tc3xx_Internal_ValidControllerInit() */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetControllerMode
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
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetControllerMode(
  uint8        ctrlIdx,
  Eth_ModeType ctrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the mode the controller should be set to is ACTIVE */
  if (ctrlMode == ETH_MODE_ACTIVE)
  {
    /* #110 Call the hardware dependent interface to enable the MAC */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_EnableMac(ctrlIdx);

    /* #120 If the activation of the MAC did not finish correctly */
    /*lint -e{522} */
    if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == FALSE)
    {
      /* #1210 If configured, report the error code E_ACCESS to the DEM and return E_NOT_OK */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
    }
    else
    {
      retVal = E_OK;
    }
#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
    /* #130 If TimeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #1310 Start the time synchronization clock */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock(ctrlIdx);
    }
#endif
  }
  /* #20 If the mode the controller should be set to is DOWN */
  else
  {
    /* #210 Call the hardware dependent interface to disable the MAC */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_DisableMac(ctrlIdx);
    /* #220 Shutting down he MAC did not finish correctly */
    /*lint -e{522} */
    if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
    {
      /* #2210 If configured, report the error code E_ACCESS to the DEM and return E_NOT_OK */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
    }
    else
    {
      retVal = E_OK;
    }
  }
  if (retVal == E_OK)
  {
    /*#30 Update the global mode variable if the function was successfully executed */ 
    Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ctrlMode);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_SetControllerMode */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetControllerMode(
        uint8                               ctrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) ctrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the hardware returns that the MAC is enabled */
  /*lint -e{522} */
  if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
  {
    /* #110 Report the mode of the controller to be ACTIVE */
    (*ctrlModePtr) = ETH_MODE_ACTIVE;                                                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #20 If the hardware returns that the MAC is disabled */
  else
  {
    /* #210 Report the mode of the controller to be DOWN */
    (*ctrlModePtr) = ETH_MODE_DOWN;                                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetControllerMode */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
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
 */
ETH_30_TC3XX_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_TxDescrHandlingIterType  txDescrHandlingIdx;
  Eth_30_Tc3xx_RxDescrHandlingIterType  rxDescrHandlingIdx;
  Eth_30_Tc3xx_TxBufferStateIterType    txBufferStateIdx;
  Eth_30_Tc3xx_TxBufferHandlingIterType txBufferHandlingIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop over all TX descriptor rings */
  for (txDescrHandlingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx++)
  {
    Eth_30_Tc3xx_TxDescrIterType         txDescrIdx;
    Eth_30_Tc3xx_TxDescrRingProcIterType txDescrRingProcIdx;

    /* #110 Loop over all TX descriptors in the current ring */
    for (txDescrIdx = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(txDescrHandlingIdx);
         txDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(txDescrHandlingIdx);
         txDescrIdx++)
    {
      /* #1110 Initialize the current TX descriptor */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_InitializeTxDescriptor(ctrlIdx, txDescrHandlingIdx, txDescrIdx);
      /* same number of elements */
      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(txDescrIdx, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);                               /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    }

    /* #120 Set the state variable for the ring position for the current TX descriptor ring the initial value */
    txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(txDescrHandlingIdx);
    Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(txDescrRingProcIdx, 0);                                                     /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx, 0);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }
  /* #20 Loop over all RX descriptor rings */
  for (rxDescrHandlingIdx = Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       rxDescrHandlingIdx  < Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
       rxDescrHandlingIdx++)
  {
    Eth_30_Tc3xx_RxDescrIterType                rxDescrIdx;
    Eth_30_Tc3xx_RxDescrRingProcIterType        rxDescrRingProcIdx;
    Eth_30_Tc3xx_SegNumOfRxBufferHandlingType   segNumOfRxBufferHandling;
    Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufferIdx = 0;

    segNumOfRxBufferHandling = Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(rxDescrHandlingIdx);

    /* #210 Loop over all RX descriptors in the current ring */
    for (rxDescrIdx = Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(rxDescrHandlingIdx);
         rxDescrIdx < Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(rxDescrHandlingIdx);
         rxDescrIdx++)
    {
      /* #2110 Initialize the current RX descriptor */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, rxDescrHandlingIdx, rxDescrIdx, rxBufferIdx);

      /* #2120 Set the global state variables for the current RX descriptor to map descriptors and buffers */
      if (rxBufferIdx < segNumOfRxBufferHandling)
      {
        Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(rxDescrIdx, rxBufferIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
      }
      else
      {
        Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(rxDescrIdx, ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED);         /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
      }
      rxBufferIdx++;
    }
    /* #220 Set the state variable for the ring position for the current RX descriptor ring to the initial value */
    rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(rxDescrHandlingIdx);
    Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx, 0);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }

  /* #30 Loop over all transmission buffers */
  txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
  for (txBufferStateIdx = Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(txBufferHandlingIdx);
       txBufferStateIdx < Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(txBufferHandlingIdx);
       txBufferStateIdx++)
  {
    /* #310 Initialize the buffer busy state of the current transmission buffer */
    Eth_30_Tc3xx_SetBusyOfTxBufferState(txBufferStateIdx, FALSE);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    /* #320 Initialize the upper layer confirmation state of the current transmission buffer */
    Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(txBufferStateIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);      /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

    /* #330 If timeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #3310 Initialize the state variable indicating if a time stamp is requested for the current transmission
       *       buffer */
      Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(txBufferStateIdx,                                                       /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
                                                (Eth_30_Tc3xx_TsRequestedOfTxBufferStateType)ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED); 
    }
  }

  /* #40 Initialize HW specific global Descriptor state variables */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_InitDescriptorStateVariables(ctrlIdx);

  /* #50 Announce descriptor lists to hardware */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(ctrlIdx);
} /* Eth_30_Tc3xx_InitBuffersAndDescriptors() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ControllerInit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ControllerInit(
  uint8 CtrlIdx,
  uint8 CfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CfgIdx > ETH_30_TC3XX_MAX_CFGS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CONFIG;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* trigger start of runtime measurement */
    Eth_30_Tc3xx_Rtm_Start(ControllerInit);
    /* #20 Call the internal or host controller interface to initialize an Ethernet controller */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ControllerInit(localCtrlIdx, CfgIdx);
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ControllerInit(localCtrlIdx, CfgIdx);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
    /* trigger stop of runtime measurement */
    Eth_30_Tc3xx_Rtm_Stop(ControllerInit);
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_CONTROLLER_INIT, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ControllerInit */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetControllerMode(
  uint8        CtrlIdx,
  Eth_ModeType CtrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface set the Ethernet controller's mode */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_SetControllerMode(localCtrlIdx, CtrlMode);
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_SetControllerMode(localCtrlIdx, CtrlMode);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_SET_CONTROLLER_MODE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_SetControllerMode */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetControllerMode(
        uint8                               CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) CtrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrlModePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #20 Call the internal or host controller interface set the Ethernet controller's mode */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetControllerMode(localCtrlIdx, CtrlModePtr);                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetControllerMode(localCtrlIdx, CtrlModePtr);                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_CONTROLLER_MODE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_GetControllerMode */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_CtrlModeHdl.c
 *********************************************************************************************************************/
