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
/*!        \file  Eth_30_Vtt_CfgAccess_Int.h
 *        \brief  Configuration access header file
 *
 *      \details  Provides inline functions to access the configuration in an abstracted way.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
#if !defined (ETH_30_VTT_CFG_ACCESS_INT_H)
# define ETH_30_VTT_CFG_ACCESS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Vtt_Lcfg.h"
# include "Eth_30_Vtt_HwAccess_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETH_30_VTT_CFG_ACCESS_INLINE)
#  define ETH_30_VTT_CFG_ACCESS_INLINE                                LOCAL_INLINE
# endif /* ETH_30_VTT_CFG_ACCESS_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_VTT_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_GetRxDescr
 *********************************************************************************************************************/
/*! \brief       Retrieves a reception descriptor of a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \param[in]   descrIdx       Identifier of the reception descriptor
 *  \return      Reception descriptor
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Vtt_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_GetRxDescr(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_IsRxInterruptModeEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if reception processing with the help of interrupts is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Interrupt processing isn't enabled
 *  \return      TRUE - Interrupt processing is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_IsRxInterruptModeEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_IsTxInterruptModeEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if transmisson processing with the help of interrupts is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Interrupt processing isn't enabled
 *  \return      TRUE - Interrupt processing is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_IsTxInterruptModeEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_GetRxDescr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Vtt_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_GetRxDescr( /* PRQA S 3219 */ /* MD_Eth_30_Vtt_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx)
{
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx);
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx);
  return (Eth_30_Vtt_RxDescriptorType *)Eth_30_Vtt_GetAddrRxDescr((Eth_30_Vtt_RxDescrIterType)descrIdx);
} /* Eth_30_Vtt_Cfg_GetRxDescr() */


/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_IsRxInterruptModeEnabled
 *********************************************************************************************************************/
/*! Internal comment removed. *
 *
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_IsRxInterruptModeEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Vtt_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Vtt_IsRxInterruptEnabledOfEthCtrl(ctrlIdx);
} /* Eth_30_Vtt_Cfg_IsRxInterruptModeEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_Cfg_IsTxInterruptModeEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 */
ETH_30_VTT_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_Cfg_IsTxInterruptModeEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Vtt_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Vtt_IsTxInterruptEnabledOfEthCtrl(ctrlIdx);
} /* Eth_30_Vtt_Cfg_IsTxInterruptModeEnabled() */



# define ETH_30_VTT_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_VTT_CFG_ACCESS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_CfgAccess_Int.h
 *********************************************************************************************************************/



