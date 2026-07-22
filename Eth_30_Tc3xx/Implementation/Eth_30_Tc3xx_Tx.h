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
/*!        \file  Eth_30_Tc3xx_Tx.h
 *        \brief  Declaration of Ethernet controller transmit implementation
 *
 *      \details  Provides access to the transmit related API of the Ethernet controller driver.
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

#if !defined (ETH_30_TC3XX_TX_H)
# define ETH_30_TC3XX_TX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_LL_Tx.h"

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_ProvideTxBuffer() */
# define ETH_30_TC3XX_SID_PROVIDE_TX_BUFFER                           (0x09u)
/*!< Service ID: Eth_30_Tc3xx_Transmit() */
# define ETH_30_TC3XX_SID_TRANSMIT                                    (0x0Au)
/*!< Service ID: Eth_30_Tc3xx_TxConfirmation() */
# define ETH_30_TC3XX_SID_TX_CONFIRMATION                             (0x0Cu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief          Provides a buffer that can be used to transmit an Ethernet frame
 *  \details        Function provides a buffer that can be used to transmit an Ethernet frame. The buffer is locked and
 *                  therefore protected against reuse until the transmission of the frame is confirmed after transmission
 *                  was triggered (Eth_Transmit() and consecutive Eth_TxConfirmation()) or buffer is intentionally released
 *                  by calling Eth_Transmit() with LenByte=0.
 *  \param[in]      CtrlIdx     Identifier of the Ethernet controller
 *  \param[out]     BufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     BufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  LenBytePtr  Buffer used to determine the requested and the provide length of the buffer:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            Ethernet controller is operational in mode ACTIVE
 */
FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer(
              uint8                                                      CtrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) BufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        LenBytePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Transmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header and triggers the transmission of the Ethernet frame.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   BufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *  \param[in]   FrameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   TxConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   LenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   PhysAddrPtr     MAC address the frame shall be sent to
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *  \pre         Buffer was acquired by Eth_ProvideTxBuffer()
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Transmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer with a specific source MAC
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header (using a specific source MAC address instead of the Ethernet controllers one) and triggers the
 *               transmission of the Ethernet frame.
 *  \param[in]   CtrlIdx         Identifier of the Ethernet controller
 *  \param[in]   BufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *  \param[in]   FrameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   TxConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   LenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   PhysAddrDstPtr  Destination MAC address
 *  \param[in]   PhysAddrSrcPtr  Source MAC address
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *  \pre         Buffer was acquired by Eth_ProvideTxBuffer()
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit(
          uint8                               CtrlIdx,
          uint8                               BufIdx,
          Eth_FrameType                       FrameType,
          boolean                             TxConfirmation,
          uint16                              LenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrSrcPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmation
 **********************************************************************************************************************/
/*! \brief       Triggers the transmission confirmation of a previously Ethernet frame transmitted
 *  \details     Function triggers the transmission confirmation of a previously Ethernet frame transmitted and unlocks
 *               the buffer associated to the Ethernet frame so it is able to be used for frame transmission again.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmation(
  uint8 CtrlIdx );

#endif /* ETH_30_TC3XX_TX_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Tx.h
 *********************************************************************************************************************/
