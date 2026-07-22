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
/*!        \file  Eth_30_Tc3xx_MacHdl.c
 *        \brief  Mac handling implementation
 *
 *      \details  Mac handling implementation of the Ethernet controller driver.
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

#define ETH_30_TC3XX_MAC_HDL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_MacHdl.h"
#include "Eth_30_Tc3xx_MacHdl_Int.h"
#include "Eth_30_Tc3xx_Int.h"

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! \brief      Checks whether the MAC address is all-zero
 *  \details    -
 *  \param[in]  macAddrPtr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't all zero
 *  \return     TRUE  - MAC address is all zero
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetPhysAddr
 **********************************************************************************************************************/
/*! \brief       Retrieves the currently active MAC address of an Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  physAddrPtr  Buffer of at least 6 byte to pass the MAC address
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetPhysAddr(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetPhysAddr
 *********************************************************************************************************************/
/*! \brief       Sets the MAC address of an Ethernet controller
 *  \details     Function sets the MAC address of an Ethernet controller. Dependent on the configuration of the "Write
 *               MAC address" feature the change is persisted in non-volatile RAM and also available after a power-
 *               cycle of the MCU.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   physAddrPtr  Buffer holding the MAC address that shall be applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetPhysAddr(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr);

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of a Ethernet controller
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    ctrlIdx               Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    physAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    action                Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return       E_NOT_OK - Filter modification failed
 *  \return       E_OK - Filter successfully updated
 *  \context      TASK
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 *********************************************************************************************************************/
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(
          uint8                                      ctrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                       action);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of a Ethernet controller for a normal MAC
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    ctrlIdx               Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    physAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    action                Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return       E_NOT_OK - Filter modification failed
 *  \return       E_OK - Filter successfully updated
 *  \context      TASK
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *********************************************************************************************************************/
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(
          uint8                                       ctrlIdx,
  P2CONST(uint8,                AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                        action);
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least addrIdx;
  boolean     isZeroAddress = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all six bytes of the given MAC address */
  for (addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++)
  {
    /* #110 The currently checked byte is not equal to zero */
    if (macAddrPtr[(uint8)addrIdx] != 0x00u)
    {
      /* #1110 Return that the given MAC-address is no zero-address */
      isZeroAddress = FALSE;
      break;
    }
  }
  return isZeroAddress;
} /* Eth_30_Tc3xx_IsZeroAddress() */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetPhysAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetPhysAddr(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least physAddrPtrIdx;
  Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the configured physical address of the controller */
  for (physAddrPtrIdx = 0; physAddrPtrIdx < ETH_PHYS_ADDR_LEN_BYTE; physAddrPtrIdx++)
  {
    activeMacAddrIdx = physAddrPtrIdx + Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);

    physAddrPtr[physAddrPtrIdx] = Eth_30_Tc3xx_GetActiveMacAddress(activeMacAddrIdx);                                 /* SBSW_ETH_30_TC3XX_PHYS_ADDR_PTR_ACCESS */
  }
} /* Eth_30_Tc3xx_Internal_GetPhysAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetPhysAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetPhysAddr(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least physAddrPtrIdx = 0;
  Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the given physical address into the corresponding RAM variable */
  for (activeMacAddrIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
       activeMacAddrIdx < Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(ctrlIdx);
       activeMacAddrIdx++)
  {
    Eth_30_Tc3xx_SetActiveMacAddress(activeMacAddrIdx, physAddrPtr[physAddrPtrIdx]);                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

    physAddrPtrIdx++;
  }

  /* #20 Write the physical address to registers */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMacAddressToRegister(ctrlIdx, physAddrPtr);                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

#if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
  {
    /* #30 Request the NvM to perform a write to the non-volatile memory, if enabled */
    uint8 status = NVM_REQ_PENDING;
    Std_ReturnType retVal;

    retVal = NvM_GetErrorStatus(Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(ctrlIdx), &status);                               /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */

    if ((retVal == E_OK) && (status != NVM_REQ_PENDING))
    {
      /* set block Status to true */
      NvM_SetRamBlockStatus(Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(ctrlIdx), TRUE);
    }
  }
#endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */

} /* Eth_30_Tc3xx_Internal_SetPhysAddr() */

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter
 *********************************************************************************************************************/
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
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(
          uint8                                       ctrlIdx,
  P2CONST(uint8,                AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                        action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent interface to perform hardware specific filter mode settings for hash filtering */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_SetMulticastFilteringMode(ctrlIdx);

  /* #20 Enter exclusive area (Reason: Consistency of global counter variables and number of corresponding calls) */
  Eth_30_Tc3xx_EnterExclusiveArea(MULTICAST_FILTER);

  /* #30 If a broadcast address is given as parameter into the function */
  if (Eth_30_Tc3xx_IsBroadcast(physAddrPtr) == TRUE)                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    /* #310 If the action parameter given into the function indicates that the address should be added to the filter */
    if (action == ETH_ADD_TO_FILTER)
    {
      /* #3110 If the parameter combination corresponds to a request to enable the promiscuous mode and the
       *       corresponding counter has not yet overflown */
      if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) < ETH_30_TC3XX_UINT8_MAX)
      {
        /* #31110 Increment the promiscuous mode counter */
        Eth_30_Tc3xx_IncPromiscuousModeCounter(ctrlIdx);                                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
        retVal = E_OK;

        /* #31120 If the request to enable the promiscuous mode was the first one since it was disabled or after
         *        reset */
        if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) == 1u)
        {
          /* #311210 Enable the promiscuous mode */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_EnablePromiscuousMode(ctrlIdx);
        }
      }
      /* #3120 If the parameter combination corresponds to a request to enable the promiscuous mode and the
       *       corresponding counter has overflown */
      else
      {
        /* #31210 Too much activations of promiscuous mode, the request is denied */
      }
    }
    /* #320 If the action parameter given into the function indicates that the address should be removed from the
     *      filter */
    else /* ETH_30_TC3XX_REMOVE_FROM_FILTER */
    {
      /* #3210 If the parameter combination corresponds to a request to disable the promiscuous mode and the
       *       corresponding counter is still bigger than zero */
      if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) > 0u)
      {
        /* #32110 Decrement the promiscuous mode counter */
        Eth_30_Tc3xx_DecPromiscuousModeCounter(ctrlIdx);                                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
        retVal = E_OK;

        /* #32120 If the promiscuous mode counter is zero again, which means that all requests to enable the
         *        promiscuous mode were withdrawn */
        if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) == 0u)
        {
          /* #321210 Disable the promiscuous mode */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_DisablePromiscuousMode(ctrlIdx);
        }
      }
      /* #3220 If the parameter combination corresponds to a request to disable the promiscuous mode and the
       *       corresponding counter is already zero */
      else
      {
        /* #32210 The request to disable the promiscuous mode is denied because it was not enabled */
      }
    }
  }
  /* #40 If a zero address is given as parameter into the function to indicate that all filters should be closed */
  else if (Eth_30_Tc3xx_IsZeroAddress(physAddrPtr) == TRUE)                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;

    /* #410 Disable  promiscuous mode */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_DisablePromiscuousMode(ctrlIdx);

    /* #420 Close all multicast filters */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_CloseAllMulticastFilters(ctrlIdx);

    /* #430 set all filter bucket counters to their initial value */
    for (multicastBucketCountersIdx = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
         multicastBucketCountersIdx < Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
         multicastBucketCountersIdx++)
    {
      Eth_30_Tc3xx_SetMulticastBucketCounters(multicastBucketCountersIdx, 0);                                            /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    }

    /* #440 Set the promiscuous mode counter to its initial value */
    Eth_30_Tc3xx_SetPromiscuousModeCounter(ctrlIdx, 0);                                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

    retVal = E_OK;
  }
  /* #50 If a MAC address without special function defined by AUTOSAR shall be handled */
  else
  {
    /* #510 Call the internal interface to handle normal MAC addresses */
    retVal = Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(ctrlIdx, physAddrPtr, action);                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }
  /* #60 Leave the exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(MULTICAST_FILTER);

  return retVal;
} /* Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC
 *********************************************************************************************************************/
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
 */
ETH_30_TC3XX_MAC_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(
          uint8                                      ctrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                       action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 hash;
  uint32 bucketMask;
  boolean isUpperReg;
  Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;
  Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType multicastBucketCountersEndIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent interface to calculate the multicast filter register hash */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(ctrlIdx, physAddrPtr, &hash, &isUpperReg, &bucketMask);           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
  /* #20 Retrieve the index of the corresponding bucket counter with the returned hash */
  multicastBucketCountersIdx    = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
  multicastBucketCountersEndIdx = Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
  /* #30 If the retrieved index is correct */
  if (multicastBucketCountersIdx < multicastBucketCountersEndIdx)
  {
    /* #310 If the action parameter given into the function indicates that the address shall be added to the filter */
    if (ETH_ADD_TO_FILTER == action)
    {
      /* #3110 If the multicast bucket counter for the corresponding register is still below its max value */
      if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) < ETH_30_TC3XX_BUCKET_MAX_CNT)
      {
        /* #31110 Increment the multicast bucket counter */
        Eth_30_Tc3xx_IncMulticastBucketCounters(multicastBucketCountersIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

        /* #31120 If the multicast bucket counter for the corresponding register is equal to one, the address is
         *        requested for the first time after it was removed or reset */
        if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) == 1u)
        {
          /* #311210 Write the previously retrieved bucket mask into the bucket register */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_SetMulticastFilterBucketRegister(ctrlIdx, bucketMask, isUpperReg);
        }
        /* #31130 Return that the request was successful */
        retVal = E_OK;
      }
    }
    /* #320 If the action parameter given into the function indicates that the address shall be removed from the
     *      filter */
    else
    {
      /* #3210 If the multicast bucket counter for the corresponding register is still greater than zero */
      if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) > 0u)
      {
        /* #32110 Decrement the multicast bucket counter */
        Eth_30_Tc3xx_DecMulticastBucketCounters(multicastBucketCountersIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

        /* #32120 If the counter reaches zero, indicating that enough requests to remove the address from the filter
         *        were performed */
        if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) == 0u)
        {
          /* #321210 Clear the previously retrieved bucket mask from the bucket register */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_ResetMulticastFilterBucketRegister(ctrlIdx, bucketMask, isUpperReg);
        }
        /* #32130 Return that the request was successful */
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetPhysAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPhysAddr(
        uint8                        CtrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)

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
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #20 Call the internal or host controller interface get the Ethernet controller's physical address */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_GetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_GetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
/* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_PHYS_ADDR, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_GetPhysAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPhysAddr(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
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
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface set the Ethernet controller's physical address */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_SetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_SetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_SET_PHYS_ADDR, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_SetPhysAddr() */

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter(
          uint8                                      CtrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) PhysAddrPtr,
          Eth_FilterActionType                       Action)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to update the physical address filter  */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(localCtrlIdx, PhysAddrPtr, Action);                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_UpdatePhysAddrFilter(localCtrlIdx, PhysAddrPtr, Action);                        /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_UPDATE_PHYS_ADDR_FILTER, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_UpdatePhysAddrFilter */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MacHdl.c
 *********************************************************************************************************************/
