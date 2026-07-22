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
/*!        \file  Eth_30_Tc3xx_MiiAccess.h
 *        \brief  MiiAccess header of the Ethernet controller driver
 *
 *      \details  Provides access to the Mii related API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_MIIACCESS_H)
# define ETH_30_TC3XX_MIIACCESS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_LL_MiiAccess.h"

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_WriteMii() */
# define ETH_30_TC3XX_SID_WRITE_MII                                   (0x05u)
/*!< Service ID: Eth_30_Tc3xx_ReadMii() */
# define ETH_30_TC3XX_SID_READ_MII                                    (0x06u)
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_WriteMii
 **********************************************************************************************************************/
/*! \brief       Triggers a write command on the MDIO interface of an Ethernet controller
 *  \details     Function triggers a write command on the MDIO interface according to clause 22 of the IEEE
 *               specification.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \param[in]   TrcvIdx  Address of the counter part on MDIO interface (MII address)
 *  \param[in]   RegIdx   Address of the register that shall be written
 *  \param[in]   RegVal   Value that shall be written to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     ANY
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_WriteMii(
  uint8  CtrlIdx,
  uint8  TrcvIdx,
  uint8  RegIdx,
  uint16 RegVal);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReadMii
 **********************************************************************************************************************/
/*! \brief       Triggers a read command on the MDIO interface of an Ethernet controller and provides the result
 *  \details     Function triggers a read command on the MDIO interface according to clause 22 of the IEEE
 *               specification and provides the result of the read.
 *  \param[in]   CtrlIdx    Identifier of the Ethernet controller
 *  \param[in]   TrcvIdx    Address of the counter part on MDIO interface (MII address)
 *  \param[in]   RegIdx     Address of the register that shall be read
 *  \param[out]  RegValPtr  Buffer to store the result of the read command
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK -
 *  \context     ANY
 *  \reentrant   TRUE  for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReadMii(
        uint8                         CtrlIdx,
        uint8                         TrcvIdx,
        uint8                         RegIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_MIIACCESS_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MiiAccess.h
 *********************************************************************************************************************/
