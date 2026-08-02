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
/*!        \file  Eth_30_Tc3xx_Generic.c
 *        \brief  Ethernet controller driver implementation
 *
 *      \details  Core part of the Ethernet controller driver implementation.
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

#define ETH_30_TC3XX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_Generic_Int.h"
#include "Eth_30_Tc3xx_LL.h"

#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
# include "Eth_30_Tc3xx_LL_TimeSync.h"
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
#include "EthIf_Cbk.h"
#if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
# include "NvM.h"
#endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */



/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_LOCAL /* COV_ETH_COMPATIBILITY */
# define ETH_30_TC3XX_LOCAL                                           static
#endif

#ifndef ETH_30_TC3XX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
# define ETH_30_TC3XX_LOCAL_INLINE                                    LOCAL_INLINE
#endif
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
VAR(Eth_StateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ModuleInitialized;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsRxDescriptorsValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all RX Descriptors fulfill minimum alignment requirements.
 *  \details    -
 *  \param[in]  ctrlIdx          Index of controller which shall be reset
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment RX Descriptors of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment RX Descriptors of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxDescriptorsValidAlignment(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxDescriptorsValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all TX Descriptors fulfill minimum alignment requirements.
 *  \details    -
 *  \param[in]  ctrlIdx          Index of controller which shall be reset
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment TX Descriptors of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment TX Descriptors of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxDescriptorsValidAlignment(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsRxBuffersValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all RX Buffers fulfill minimum alignment requirements.
 *  \details    -
 *  \param[in]  ctrlIdx          Index of controller which shall be reset
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment Rx Buffers of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment Rx Buffers of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxBuffersValidAlignment(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBuffersValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all TX Buffers fulfill minimum alignment requirements.
 *  \details    -
 *  \param[in]  ctrlIdx          Index of controller which shall be reset
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment Tx Buffers of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment Tx Buffers of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBuffersValidAlignment(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all RX \ TX Descriptors and Buffers fulfill minimum alignment requirements.
 *  \details    -
 *  \param[out] ctrlIdxPtr  Identifier of the Ethernet controller in case alignment is not fulfilled and return
 *                          value is FALSE.
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidAlignment(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ctrlIdxPtr);
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)

/***********************************************************************************************************************
 *  Eth_30_Eth_30_Tc3xx_IsRxDescriptorsValidAlignment
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxDescriptorsValidAlignment(
    uint8 ctrlIdx)
{
  boolean result = TRUE;
  Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType rxDescrHandlingIdx;

  /* #10 Loop over all RX Descriptor rings */
  for (rxDescrHandlingIdx = Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
      rxDescrHandlingIdx < Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); rxDescrHandlingIdx++)
  {
    /* PRQA S 0303, 0306 1 */ /* MD_Eth_30_Tc3xx_0303, MD_Eth_30_Tc3xx_0306 */
    uint32 rxDescAddr = (uint32) Eth_30_Tc3xx_GetAddrRxDescr(
        Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(rxDescrHandlingIdx));
    /* #110 If the currently checked RX descriptor ring does not fulfill the minimum alignment requirement */
    if ((rxDescAddr % (uint32) ETH_30_TC3XX_LL_DESC_ALIGN_BYTE) != 0u)
    {
      /* #1110 Return that the alignment is not valid */
      result = FALSE;
      break;
    }
  }

 return result;
} /* Eth_30_Tc3xx_IsRxDescriptorsValidAlignment() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxDescriptorsValidAlignment
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxDescriptorsValidAlignment(
    uint8 ctrlIdx)
{
  boolean result = TRUE;
  Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType txDescrHandlingIdx;

  /* #10 Loop over all TX Descriptor rings */
  for (txDescrHandlingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx++)
  {
    /* PRQA S 0303, 0306 1 */ /* MD_Eth_30_Tc3xx_0303, MD_Eth_30_Tc3xx_0306 */
    uint32 txDescAddr = (uint32) Eth_30_Tc3xx_GetAddrTxDescr(
        Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(txDescrHandlingIdx));

    /* #110 If the currently checked TX descriptor ring does not fulfill the minimum alignment requirement */
    if ((txDescAddr % (uint32) ETH_30_TC3XX_LL_DESC_ALIGN_BYTE) != 0u)
    {
      /* #1110 Return that the alignment is not valid */
      result = FALSE;
      break;
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsTxDescriptorsValidAlignment() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsRxBuffersValidAlignment
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxBuffersValidAlignment(
    uint8 ctrlIdx)
{
  boolean result = TRUE;
  Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType rxBufferHandlingIdx;

  /* #10 Loop over all RX Buffer queues */
  for (rxBufferHandlingIdx = Eth_30_Tc3xx_GetRxBufferHandlingStartIdxOfEthCtrl(ctrlIdx);
      rxBufferHandlingIdx < Eth_30_Tc3xx_GetRxBufferHandlingEndIdxOfEthCtrl(ctrlIdx); rxBufferHandlingIdx++)
  {
    /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
    uint32 rxBufferAddr = (uint32) (Eth_30_Tc3xx_GetAddrRxBuffer(
        Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(rxBufferHandlingIdx)));

    /* #110 If the currently checked RX buffer queue does not fulfill the minimum alignment requirement */
    if (((rxBufferAddr % (uint32) ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE) != 0u))
    {
      /* #1110 Return that the alignment is not valid */
      result = FALSE;
      break;
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsRxBuffersValidAlignment() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBuffersValidAlignment
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBuffersValidAlignment(
    uint8 ctrlIdx)
{
  boolean result = TRUE;

  Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx =
      Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
  Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType txBufferStartIdx =
      Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);

  /* #10 Check the TX buffer list for the minimum alignment requirement */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  if (((uint32) Eth_30_Tc3xx_GetAddrTxBuffer(txBufferStartIdx) % (uint32) ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE) != 0u)
  {
    /* #110 Return that the alignment is not valid */
    result = FALSE;
  }

  return result;
} /* Eth_30_Tc3xx_IsTxBuffersValidAlignment() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidAlignment
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidAlignment(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ctrlIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_SizeOfEthCtrlType ethCtrlIdx;
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop over all controllers */
  for (ethCtrlIdx = 0; ethCtrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl(); ethCtrlIdx++)
  {
     /* #110 Check if all Rx Descriptor rings are valid aligned */
     if(Eth_30_Tc3xx_IsRxDescriptorsValidAlignment(ethCtrlIdx) == FALSE)
     {
       /* #1110 Return that the alignment is not valid */
       result = FALSE;
     }

     /* #120 Check if all Rx Buffers are valid aligned */
     if(Eth_30_Tc3xx_IsRxBuffersValidAlignment(ethCtrlIdx) == FALSE)
     {
       /* #1210 Return that the alignment is not valid */
       result = FALSE;
     }

     /* #130 Check if all Tx Descriptor rings are valid aligned */
     if(Eth_30_Tc3xx_IsTxDescriptorsValidAlignment(ethCtrlIdx) == FALSE)
     {
       /* #1310 Return that the alignment is not valid */
       result = FALSE;
     }

     /* #140 Check if all Tx Buffers are valid aligned */
     if(Eth_30_Tc3xx_IsTxBuffersValidAlignment(ethCtrlIdx) == FALSE)
     {
       /* #1410 Return that the alignment is not valid */
       result = FALSE;
     }

     /* #150 If one of the previous checks failed */
     if(result == FALSE)
     {
       /* #1510 Leave the loop so the result can be reported */
       break;
     }
  }

  /* #20 Return the first controller index for which the alignment was not valid */
  *ctrlIdxPtr = (uint8)ethCtrlIdx;                                                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return result;
} /* Eth_30_Tc3xx_IsValidAlignment() */

#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  {
    /* #10 Initialize state variables for DET checks */
    Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_UNINIT;
  }
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
} /* Eth_30_Tc3xx_InitMemory() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Init
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
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Init(
  P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_CONST, ETH_30_TC3XX_CONST) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least ctrlIdx = 0;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  uint8 ctrlIdxNoValidAlignment;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* #10 Assign the parameter config pointer to the global config data pointer variable */
  Eth_30_Tc3xx_ConfigDataPtr = CfgPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #20 Initialize the controller index for the alignment check */
  if (Eth_30_Tc3xx_ConfigDataPtr != NULL_PTR)
  {
    ctrlIdxNoValidAlignment = Eth_30_Tc3xx_GetSizeOfEthCtrl();
  }

  /* #30 Check plausibility of the input parameter */
  if (CfgPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
  /* #40 If the descriptor and/or buffer alignment is invalid */
  else if (Eth_30_Tc3xx_IsValidAlignment(&ctrlIdxNoValidAlignment) == FALSE)                                          /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  {
    /* #410 Set the local controller index to the returned value for which the alignment was invalid */
    ctrlIdx = ctrlIdxNoValidAlignment;
    errorId = ETH_30_TC3XX_E_INV_ALIGNMENT;
  }
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
      Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_INIT;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

    /* #50 Loop over all configured controllers */
    for (ctrlIdx = 0; ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl(); ctrlIdx++)
    {
      Eth_30_Tc3xx_InitialMacAddressIterType initialMacAddrIdx;
      Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;
      /* #510 Initialize global mode variables */
      Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ETH_MODE_DOWN);                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

      /* #520 Copy physical address from ROM to RAM variable */
      initialMacAddrIdx = Eth_30_Tc3xx_GetInitialMacAddressStartIdxOfEthCtrl(ctrlIdx);

      for (activeMacAddrIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
           activeMacAddrIdx < Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(ctrlIdx);
           activeMacAddrIdx++)
      {
        Eth_30_Tc3xx_SetActiveMacAddress(activeMacAddrIdx,                                                            /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
            Eth_30_Tc3xx_GetInitialMacAddress(initialMacAddrIdx));

        initialMacAddrIdx++;
      }
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
      /* #530 Copy register base address from ROM to RAM variable */
      Eth_30_Tc3xx_SetRegBaseAddrOfEthCtrlState((uint8)ctrlIdx,                                                       /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
          Eth_30_Tc3xx_GetAutosarRtmRegBaseAddrOfEthCtrl((uint8)ctrlIdx));
      /* #540 Enable MII Access so that Transceiver can be initialized during VSwitchInit */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_EnableMiiAccess((uint8)ctrlIdx);
#else
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
      ETH_30_TC3XX_DUMMY_STATEMENT_CONST(ctrlIdxNoValidAlignment); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */

      /* #550 Initialize the measurement counters */
      Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
    }
  }

  ETH_30_TC3XX_DUMMY_STATEMENT_CONST(CfgPtr); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx((uint8)ctrlIdx), ETH_30_TC3XX_SID_INIT, errorId);  /* PRQA S 2985 */ /* MD_Eth_30_Tc3xx_2985 */
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_Init() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_MainFunction
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_MainFunction( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent main function */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_MainFunction(); /* PRQA S 2987 */ /* MD_Eth_30_Tc3xx_2987 */
} /* Eth_30_Tc3xx_MainFunction */

#if (ETH_30_TC3XX_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVersionInfo(
  P2VAR(Std_VersionInfoType, ETH_30_TC3XX_APPL_DATA, ETH_30_TC3XX_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
   uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter for plausibility */
  if (VersionInfoPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* #20 Return Vendor Id, Module Id and SW version number */
    VersionInfoPtr->vendorID = ETH_30_TC3XX_VENDOR_ID;                                                                /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->moduleID = ETH_30_TC3XX_MODULE_ID;                                                                /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_major_version = ETH_30_TC3XX_SW_MAJOR_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_minor_version = ETH_30_TC3XX_SW_MINOR_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_patch_version = ETH_30_TC3XX_SW_PATCH_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, 0, ETH_30_TC3XX_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_GetVersionInfo() */
#endif /* ETH_30_TC3XX_VERSION_INFO_API */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:
  MD_Eth_30_Tc3xx_2987:
    Reason:     Legacy files depend on the existence of a Main Function.
    Risk:       None.
    Prevention: None.

  MD_Eth_30_Tc3xx_2986:
    Reason:     Legacy core-extension design demands this call.
    Risk:       None.
    Prevention: None.

  MD_Eth_30_Tc3xx_2982:
    Reason:     First read/write access is variant depending. Possible initialization before possible write access
                does not harm but improves code readability.
    Risk:       There is no risk.
    Prevention: Covered by code review.
  
  MD_Eth_30_Tc3xx_0303:
    Reason:     Hardware accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk as the register is mapped to the respective memory address.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_0310:
    Reason:     The pointer where the cast led to has a less stricter alignment. The cast
                is necessary since the array represents a continuous data buffer.
    Risk:       There is no risk since the array is a continuous data buffer.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3305:
    Reason:     The cast is necessary since the array represents a continuous data buffer and the Ethernet header
                has a length of 14 bytes
    Risk:       There is no risk since the array is a continuous data buffer. which is not divisible by 4.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3219:
    Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                by all implementation files which include this header file.
    Risk:       None.
    Prevention: None.

  MD_Eth_30_Tc3xx_3415:
   Reason:      Avoid nesting of control structures.
   Risk:        There is no risk because the functions called only retrieve data and don't manipulate them.
   Prevention:  Covered by component tests.

  MD_Eth_30_Tc3xx_0306:
    Reason:     Descriptor word accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk because descriptor pointers are only available with 32 bit length
    Prevention: Covered by code review.
  
  MD_Eth_30_Tc3xx_2985:
    Reason:     Transformation of the CtrlIdx is only relevant for multicontroller configurations. In this case
                the operation is not redundant.
    Risk:       The redundant assignment might be confusing.
    Prevention: The usage of this justification is restricted to the transformation of the CtrlIdx.

*/

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETH_COMPATIBILITY
    \ACCEPT XF xf
    \ACCEPT TX tx
    \REASON [MSR_COV_COMPATIBILITY]

  \ID COV_ETH_MII_INTERFACE
    \ACCEPT TX
    \REASON Switching off this feature is not supported and therefore it is always active. The related service API
            should be configurable by AUTOSAR but this is not supported by using MICROSAR EthIf which
            always needs the MII interface.

  \ID COV_ETH_PERIPHERAL_ACCESS
    \ACCEPT XF
    \REASON This feature is not used by this derivative and therefore it is always deactivated.

  \ID COV_ETH_TEST_SUITE
    \ACCEPT TX
    \REASON This code is only used by ETH test suite for testing purpose and therefore excluded from (MISRA) metrics.

  \ID COV_ETH_TEST_SUITE_UNIT_TESTS
    \ACCEPT TX
    \REASON This code is only deactivated by ETH test suite for unit testing purpose.

  \ID COV_ETH_HOST_CTRL_INTERFACE
    \ACCEPT XF
    \ACCEPT TX
    \REASON This is only relevant for drivers which are wrapping a host controller driver. For all other Ethernet
            drivers, it has to be turned off.

 COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN
   \ID SBSW_ETH_30_TC3XX_COMMON_CSL01
     \DESCRIPTION Access of generated data by usage of index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL01]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL02
     \DESCRIPTION Access of generated data that is referred to over another index that is limited to the data's size
                  (via an indirection) using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL02]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL03
     \DESCRIPTION Access of generated data by usage of indirection index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL03]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING
     \DESCRIPTION Access of generated data in ring structure by usage of start-index plus an index referring to the
                  current position, both provided by ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_GLOBAL_DESCR_IDX]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK
     \DESCRIPTION Access of generated data in a stack structure by usage of start-index plus an index referring to the
                  current position, both provided by ComStackLib.
     \COUNTERMEASURE \R The retrieved index is checked to not exceed the end index provided by ComStackLib.
                        [CM_ETH_30_TC3XX_CSL03] for the correctness of the index.

   \ID SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR
     \DESCRIPTION Pointer to stack variable passed as function argument.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_REF_OF_STACK_VAR]

   \ID SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to a public API.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a function to an internal function
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_PASS_CSL0X
     \DESCRIPTION Passing a local pointer variable referencing an Ethernet transmission or reception buffer pointer
                  provided by offset calculation with offsets obtained through ComStackLib shifted by a constant
                  positive offset of less than 60 Bytes as parameter to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet transmission buffer array and at least
                        60 valid Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the
                        correctness of the start offset.

   \ID SBSW_ETH_30_TC3XX_PUB_FCT_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to an external function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The shift position of the buffer adjusted by the switch interface is verified
                        with another runtime-check and the length returned by the switch interface after the buffer was
                        adjusted.

   \ID SBSW_ETH_30_TC3XX_OPT_API_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC_CSL03
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to a configurable function pointer obtained with ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset and the retrieval of the function pointer. The shift position of the buffer
                        adjusted by the switch interface is verified with another runtime-check and the length returned
                        by the switch interface after the buffer was adjusted. [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03] for
                        the correctness of the function pointer.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_SHIFTED_LOCAL_BUF_PTR_WITH_LENGTH_PASS_SWT_IFC
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to an internal function alongside with the returned length of the
                  switch interface.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The length returned by the switch interface after the adjustment of the buffer
                        is passed to the function as well.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X
     \DESCRIPTION Passing a reference to a local pointer variable with immediate value assignment referencing an
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes  and a reference to a
                  stack variable as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The passed reference is obtained by using the address operator.
                        [CM_ETH_30_TC3XX_REF_OF_STACK_VAR] for the reference to the stack variable.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_PARAM_PASS_CSL0X
     \DESCRIPTION Passing a reference to a local pointer variable with immediate value assignment referencing an
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes  and a reference to a
                  function parameter as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The passed references are obtained by using the address operator. The caller
                        has to make sure that the parameter is in valid memory.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X
     \DESCRIPTION Accessing a local pointer variable with immediate value assignment referencing an Ethernet 
                  transmission or reception buffer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after.[CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the
                        index used for getting the start offset and [CM_ETH_30_TC3XX_CSL03]. The obtained pointer is
                        immediately assigned to the variable that is accessed.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_DESCR
     \DESCRIPTION Accessing a local pointer variable with immediate value assignment referencing an Ethernet
                  transmission or reception buffer pointer provided by the content of a descriptor variable referenced
                  by a local pointer provided by ComStackLib over a parameter given into the accessing function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the index used for getting the descriptor pointer.
                        The obtained buffer pointer is immediately assigned to the local variable that is accessed.
                        The initialization of the descriptor ensures that a valid buffer is assigned to the descriptor
                        so that the access at byte-positions at less than 60 Bytes are valid.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS
     \DESCRIPTION Accessing a variable provided by reference as parameter upon the call of the function referencing an
                  Ethernet transmission or reception buffer pointer at a Byte-index  position of less than 60 Bytes.
     \COUNTERMEASURE \N The caller is responsible to provide a valid pointer to a buffer variable according to the CDD.
                        The access at a Byte-index position at less than 60 Bytes is valid.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR
     \DESCRIPTION Passing a pointer provided during a call to a function and a pointer to a stack variable as parameters
                  to an internal function
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR] and [CM_ETH_30_TC3XX_REF_OF_STACK_VAR].

   \ID SBSW_ETH_30_TC3XX_PHYS_ADDR_PTR_ACCESS
     \DESCRIPTION Accessing an array containing a 6-Byte physical address provided as pointer parameter to a internal
                  function.
     \COUNTERMEASURE \R The caller of the function has to make sure no null pointer is passed. The called function makes
                        sure that only 6 bytes are accessed since the passed variable shall be an IEEE 802.3 compliant
                        Ethernet physical address.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_GEN_PTR_PASS_CSL03
     \DESCRIPTION Passing a pointer provided by ComStackLib according to CSL03
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL03]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib passing a pointer as
     parameter which is provided as parameter to the function calling the function pointer.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03], [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_AND_STACK_REF_PASS
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib passing a pointer which is
                  provided as parameter to the function calling the function pointer and a reference
                  to a stack variable as parameters
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03], [CM_ETH_30_TC3XX_CALLER_PARAM_PTR] and
                        [CM_ETH_30_TC3XX_REF_OF_STACK_VAR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_AND_CSL_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function and a pointer provided by ComStackLib
                  from an index given as parameter in the calling function as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK], [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the index with
                        which the pointer is retrieved.

   \ID SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01
     \DESCRIPTION Accessing a local pointer variable whose value is provided by ComStackLib with an index given
                  as parameter into the accessing internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL01] for the index parameter, the
                        local pointer variable is declared and initialized in advance of the access.

   \ID SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL03
     \DESCRIPTION Accessing a local pointer variable whose value is provided by ComStackLib with an index given
                  as parameter into the accessing internal function by providing the access index over an indirection.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL03] for the index parameter, the
                        local pointer variable is declared and initialized in advance of the access.

   \ID SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL03
     \DESCRIPTION Accessing a global variable provided by ComStackLib with an index given
                  as parameter into the accessing internal function by providing the access index over an indirection.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL03].

   \ID SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02
     \DESCRIPTION Accessing a global variable provided by ComStackLib directly with an index given as parameter into the
                  accessing internal function. The accessed array has the same size as the array for which the index
                  parameter is valid according to the CDD which is ensured by an indirection in the ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL02].

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02
     \DESCRIPTION Pass of a pointer which is accessed from generated data that is referred to over an index that is
                  limited to the same size (via an indirection) using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL02]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS
     \DESCRIPTION Write access to data using index passed as function argument during call of a internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD]

   \ID SBSW_ETH_30_TC3XX_REGISTER_ACCESS
     \DESCRIPTION The function accesses a hardware register using a reference calculated out of a generated base address
                  and a pre-defined additional register offset given as a parameter into the function
     \COUNTERMEASURE \T The code inspection and tests on hardware ensure that the memory location
                        referenced contains the registers with the same offsets as specified.

   \ID SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01
     \DESCRIPTION Access of optional function pointer using ComStackLib.
     \COUNTERMEASURE \R Index used according to [CM_ETH_30_TC3XX_CSL01] to resolve respective function-pointer,
                        additional runtime check for NULL_PTR performed. Signature of the function used to define
                        function-pointer checked by compiler. The User has to check generated function-pointer according
                        to SMI-8. Due toCSL limitation a workaround is applied to generate an array of size one for this
                        structure. Therefore the index is fixed to 0.

   \ID SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL03
     \DESCRIPTION Access of optional function pointer using ComStackLib over an indirection.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function
                  and passing of a pointer provided by the ComStackLib when accessing a measurement data structure
                  element.
     \COUNTERMEASURE \N For the public function parameter pass [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]
                        For the pointer provided by CSL [CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_NULL_PARAM_PTR_AND_CSL_MEM_PTR_PASS_CSL_DATA
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function
                  and passing of a pointer provided by the ComStackLib when accessing a measurement data structure
                  element.
     \COUNTERMEASURE \N For the null pointer parameter pass [CM_ETH_30_TC3XX_NULL_PARAM_PTR]
                        For the pointer provided by CSL [CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_ACCESS_POSSIBLE_NULL_PTR_AFTER_NULL_PTR_CHECK
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function with
                  possible NULL pointer after NULL pointer check.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_NULL_PARAM_PTR]

   SBSW_JUSTIFICATION_END */

/*
  \CM CM_ETH_30_TC3XX_CSL01                   Qualified use-case CSL01 of ComStackLib.

  \CM CM_ETH_30_TC3XX_CSL02                   Qualified use-case CSL02 of ComStackLib.

  \CM CM_ETH_30_TC3XX_CSL03                   Qualified use-case CSL03 of ComStackLib.

  \CM CM_ETH_30_TC3XX_FCT_PTR_CSL03           Index according to [CM_ETH_30_TC3XX_CSL03] used to resolve respective
                                             function-pointer, signature of function used to define function-pointer
                                             checked by compiler and user must check generated function-pointer
                                             according to SMI-8.

  \CM CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03       In addition to [CM_ETH_30_TC3XX_FCT_PTR_CSL03] the function pointer is
                                             checked for being not NULL pointer (what indicates that function isn't
                                             present) before calling the function by using the function pointer.

  \CM CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK     Parameter pointer provided to public API is checked for not being NULL
                                             pointer before usage.

  \CM CM_ETH_30_TC3XX_CALLER_PARAM_PTR        The caller of the function passing the pointer to the other function
                                             ensures that the pointer is valid according to functions CDD.

  \CM CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD    The caller passing the index to the callee ensures that the index is
                                             within the range given in CDD.

  \CM CM_ETH_30_TC3XX_REF_OF_STACK_VAR        Pointer is generated by referencing a stack variable by the address
                                             operator.

  \CM CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK  A runtime check prevents invalid pointer or array accesses to be
                                             performed in the program flow after the check. The validity is checked by
                                             addition of a defined, positive and constant valid offset to a start
                                             index of a  ComStackLibArray obtained by using the ComStackLib and
                                             comparing the calculated offset to the end offset of the same array also
                                             obtained by  the ComStackLib. All operations performed at addresses
                                             corresponding to smaller offsets to the start offset than the checked
                                             offset are then as well within the valid borders of the accessed array
                                             and thus valid themselves. The addresses corresponding to the constant
                                             offsets to the start index are as well obtained by using the ComStackLib.
                                             The defines used to obtain the valid positive shifted offsets are protected
                                             by using preprocessor checks with error directives becoming active, if the
                                             offsets exceed the valid range.

   \CM CM_ETH_30_TC3XX_GLOBAL_DESCR_IDX       A runtime check prevents invalid use of a index variable to be performed
                                             in the program flow after the check. The index is referring to a
                                             transmission or reception descriptor variable. These variables are
                                             organized in rings with a global start index for every first descriptor
                                             in the ring that can be obtained by using the ComStackLib. This global
                                             start index is added to a ring-local processing position as well provided
                                             by ComStackLib to obtain the unique or global descriptor index of the
                                             currently processed descriptor.
                                             The index is checked to be smaller than the global end index of the
                                             currently processed descriptor ring to be considered valid.

  \CM CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX    Due to CSL limitation a workaround is applied to generate an array of size
                                             one for the measurement data structure. Therefore the index is fixed to 0
                                             and defined as constant macro. According to C standard zero size array
                                             declarations are not allowed.
  \CM CM_ETH_30_TC3XX_NULL_PARAM_PTR          The null pointer is intentionally passed and it is checked before
                                             accessing in the called functions CDD.
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx.c
 *********************************************************************************************************************/
