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
/*!        \file  Eth_30_Tc3xx_LL_CtrlModeHdl_Ifc_Int.h
 *        \brief  Lower layer controller mode handling private header file
 *
 *      \details  Private declarations of lower layer controller mode handling of component.
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
#if !defined (ETH_30_TC3XX_LL_CTRLMODEHDL_IFC_INT_H)
# define ETH_30_TC3XX_LL_CTRLMODEHDL_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Types_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE                                LOCAL_INLINE
# endif

# define ETH_30_TC3XX_ALIGN_PADDING                                   (2u)

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetCounters()
 *********************************************************************************************************************/
/*! \brief       Function for resetting statistic counters of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which statistic counters should be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*! \brief       Function for announcing the descriptor base addresses to hardware
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which descriptors shall be announced
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief        Function for initializing an RX descriptor
 *  \details      -
 *  \param[in]    ctrlIdx          Index of Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    globalDescrRingIdx     Index of descriptor ring to be initialized
 *                [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]    globalDescrIdx         Index of descriptor to be initialized
 *                [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[in]    rxBufIdx         Index of buffer to be mapped to the reception descriptor to be initialized
 *                [range: 0 <= rxBufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(rxBufferHandlingIdx)]
 *  \context      TASK
 *  \synchronous  TRUE
 *  \reentrant    FALSE
 *  \pre          -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor(
  uint8                                       ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        globalDescrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                globalDescrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for initializing a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring to be initialized
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   globalDescrIdx         Index of descriptor to be initialized
 *               [range: 0 <= globalDescrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous  TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         globalDescrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitDescriptorStateVariables()
 *********************************************************************************************************************/
/*! \brief       Function for initializing descriptor state variables, if needed by the lower layer
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */

ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnableMac()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for resetting the MAC (if needed by hardware)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsResetMacFinished()
 *********************************************************************************************************************/
/*! \brief       Function for checking for the completion of the reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be checked for completion of reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC reset is finished
 *  \return      FALSE - MAC reset is not finished yet
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisableMac()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMacEnabled()
 *********************************************************************************************************************/
/*! \brief       Function for checking the mode of the MAC (enabled, disabled)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for mode
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC is enabled
 *  \return      FALSE - MAC is disabled
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMacEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PreResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for hardware specific operations which need to be executed before MAC reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac(
  uint8 ctrlIdx);
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WaitfSPBCycles()
 *********************************************************************************************************************/
/*! \brief       The function provides the necessary fSPB cycles delay
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   fspbcycles       fSPB cycles count for delay
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WaitfSPBCycles(
    uint8 ctrlIdx,
    uint8 fspbcycles );

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty()
 *********************************************************************************************************************/
/*! \brief       This function checks whether the RxQi Debug registers are empty or not
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   debugRegMask     Register Mask to check status of reg
 *  \return      E_OK - RxQi Debug registers contents are empty
 *  \return      E_NOT_OK - RxQi Debug registers contents are not empty
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask );

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty()
 *********************************************************************************************************************/
/*! \brief       This function checks whether the TxQi Debug registers are empty or not
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   debugRegMask     Register Mask to check status of reg
 *  \return      E_OK - TxQi Debug registers contents are empty
 *  \return      E_NOT_OK - TxQi Debug registers contents are not empty
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask );

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*! \brief       Rearms the MAC for being able to receive frames on the respective descriptor ring again
 *  \details     Function sets registers that rearm the RX DMA to receive frames on the respective RX descriptor
 *               ring again.
 *  \param[in]   ctrlIdx          Index of controller that shall be rearmed for reception
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   globalDescrRingIdx     Index of descriptor ring that shall be rearmed for reception
 *               [range: 0 <= globalDescrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Eth controllers
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PerformAdditionalHwConfig()
 *********************************************************************************************************************/
/*! \brief       This function performs the controller specific additional configurations.
 *  \details     This function can be used to perform additional hardware specific configurations such as Indirect 
 *               register access, VLAN-ID based frame queuing configurations etc.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware specific configuration successful
 *  \return      E_NOT_OK - Hardware specific configuration not successful
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_CTRL_MODE_HDL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_CTRLMODEHDL_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_CtrlModeHdl_Ifc_Int.h
 *********************************************************************************************************************/
