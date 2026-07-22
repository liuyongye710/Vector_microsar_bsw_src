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
/*!        \file  Eth_30_Tc3xx_Rx_Ifc_Int.h
 *        \brief  Declaration of private Ethernet controller receive implementation
 *
 *      \details  Provides access to the private receive related API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_RX_IFC_INT_H)
# define ETH_30_TC3XX_RX_IFC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_RX_LOCAL /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_RX_LOCAL                                          static
# endif

# ifndef ETH_30_TC3XX_RX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_RX_LOCAL_INLINE                                   LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReceiveFifo
 **********************************************************************************************************************/
/*! \brief       Wrapper function to Eth_30_Tc3xx_Internal_Receive
 *  \details     When VLAN-ID based frame queuing is enabled, we need do retain the DMA index on which the interrupt
 *               is triggered so that only the core specific to the DMA will process the received frame. However
 *               Eth_30_Tc3xx_Receive doesn't allow to pass the DMA index. Hence this wrapper function is used
 *               to call the Eth_30_Tc3xx_Internal_Receive directly along with the DMA index.
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(0xFF) in case of VLAN-ID based
 *                            frame queuing disabled.
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
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReceiveFifo(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr);

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_RX_IFC_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Rx_Ifc_Int.h
 *********************************************************************************************************************/
