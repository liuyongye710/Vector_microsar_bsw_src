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
/*!        \file  Eth_30_Tc3xx_MiiAccess.c
 *        \brief  MiiAccess implementation
 *
 *      \details  MiiAccess implementation of the Ethernet controller driver.
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

#define ETH_30_TC3XX_MII_ACCESS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_MiiAccess.h"
#include "Eth_30_Tc3xx_MiiAccess_Int.h"
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */


#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_WriteMii
 **********************************************************************************************************************/
/*! \brief       Triggers a write command on the MDIO interface of a Ethernet controller
 *  \details     Function triggers a write command on the MDIO interface according to clause 22 of the IEEE
 *               specification.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx  5-Bit address of the counter part on MDIO interface (MII address)
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx   5-Bit address of the register that shall be written
 *               [range: 0 <= regIdx < 32]
 *  \param[in]   regVal   Value that shall be written to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     ANY
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_MII_ACCESS_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_WriteMii(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal);
#endif /* ETH_30_TC3XX_MII_INTERFACE */

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ReadMii
 **********************************************************************************************************************/
/*! \brief       Triggers a read command on the MDIO interface of a Ethernet controller an provides the result
 *  \details     Function triggers a read command on the MDIO interface according to clause 22 of the IEEE
 *               specification and provides the result of the read.
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx   5-Bit address of the counter part on MDIO interface (MII address)
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx    5-Bit address of the register that shall be read
 *               [range: 0 <= regIdx < 32]
 *  \param[out]  regValPtr  Buffer to store the result of the read command
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK -
 *  \context     ANY
 *  \reentrant   TRUE  for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_MII_ACCESS_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ReadMii(
        uint8                         ctrlIdx,
        uint8                         trcvIdx,
        uint8                         regIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr);
#endif /* ETH_30_TC3XX_MII_INTERFACE */


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_WriteMii
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
 */
ETH_30_TC3XX_MII_ACCESS_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_WriteMii(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType hwLoopTimeout = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Prevention of another trigger for the same action while it is not completed yet) */
  Eth_30_Tc3xx_EnterExclusiveArea(MII); 

  /* #20 Call the hardware dependent interface to trigger a MII-Management write opration */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMiiTrigger(ctrlIdx, trcvIdx, regIdx, regVal);

  /* #30 If the MII-Management write operation is still pending */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsMiiOperationPending(ctrlIdx) == TRUE)
  {
    /* #310 If the timeout for the MII-Management write operation is reached */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #3110 If configured, report the error code E_ACCESS to the DEM and return that the management access is not
       *       working correctly */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = ETH_E_NO_ACCESS;
      break;
    }
    /* #320 If the timeout value is not yet reached, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #40 If the MII-Management write operation has completed without timeout */
  if (hwLoopTimeout <= Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
  {
    /* #410 Return that the management access is OK */
    retVal = ETH_OK;
  }

  /* #50 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(MII); 

  return retVal;
} /* Eth_30_Tc3xx_Internal_WriteMii() */
#endif /* ETH_30_TC3XX_MII_INTERFACE */

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ReadMii
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
ETH_30_TC3XX_MII_ACCESS_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ReadMii(
        uint8                         ctrlIdx,
        uint8                         trcvIdx,
        uint8                         regIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType hwLoopTimeout = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Prevention of another trigger for the same action while it is not completed yet
   *                                   and consistency of triggered event and retrieved result) */
  Eth_30_Tc3xx_EnterExclusiveArea(MII); 

  /* #20 Call the hardware dependent interface to trigger a MII-Management read opration */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ReadMiiTrigger(ctrlIdx, trcvIdx, regIdx);

  /* 30 If the MII-Management read operation is still pending */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsMiiOperationPending(ctrlIdx) == TRUE)
  {
    /* #310 If the timeout for the MII-Management read operation is reached */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #3110 If configured, report the error code E_ACCESS to the DEM and return that the management access is not
       *       working correctly */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = ETH_E_NO_ACCESS;
      break;
    }
    /* #320 If the timeout value is not yet reached, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #40 If the MII-Management read operation has completed without timeout */
  if (hwLoopTimeout <= Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
  {
    /* #410 Retrieve the read result */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_GetReadMiiResult(ctrlIdx, regValPtr);                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
    /* #420 Return that the management access is OK */
    retVal = ETH_OK;
  }

  /* #50 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(MII); 

  return retVal;
} /* Eth_30_Tc3xx_Internal_ReadMii() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

#endif /* ETH_30_TC3XX_MII_INTERFACE */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_WriteMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_WriteMii(
  uint8  CtrlIdx,
  uint8  TrcvIdx,
  uint8  RegIdx,
  uint16 RegVal)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

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
  else if (RegIdx >= ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to write on the MII-management interface */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_WriteMii(localCtrlIdx, TrcvIdx, RegIdx, RegVal);
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_WriteMii(localCtrlIdx, TrcvIdx, RegIdx, RegVal);
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_WRITE_MII, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_WriteMii */
#endif /* ETH_30_TC3XX_MII_INTERFACE */

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReadMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReadMii(
        uint8                         CtrlIdx,
        uint8                         TrcvIdx,
        uint8                         RegIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = CtrlIdx;

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
  else if (RegIdx > ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (RegValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to read on the MII-management interface */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ReadMii(localCtrlIdx, TrcvIdx, RegIdx, RegValPtr);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ReadMii(localCtrlIdx, TrcvIdx, RegIdx, RegValPtr);                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_READ_MII, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ReadMii */
#endif /* ETH_30_TC3XX_MII_INTERFACE */


#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MiiAccess.c
 *********************************************************************************************************************/
