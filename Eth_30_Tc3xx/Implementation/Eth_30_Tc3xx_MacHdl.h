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
/*!        \file  Eth_30_Tc3xx_MacHdl.h
 *        \brief  Mac Handling header of the Ethernet controller driver
 *
 *      \details  Provides access to the mac handling related API of the Ethernet controller driver.
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

#if !defined (ETH_30_TC3XX_MACHDL_H)
# define ETH_30_TC3XX_MACHDL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_LL_MacHdl.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_GetPhysAddr() */
# define ETH_30_TC3XX_SID_GET_PHYS_ADDR                               (0x08u)
/*!< Service ID: Eth_30_Tc3xx_UpdatePhysAddrFilter() */
# define ETH_30_TC3XX_SID_UPDATE_PHYS_ADDR_FILTER                     (0x12u)
/*!< Service ID: Eth_30_Tc3xx_SetPhysAddr() */
# define ETH_30_TC3XX_SID_SET_PHYS_ADDR                               (0x13u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetPhysAddr
 **********************************************************************************************************************/
/*! \brief       Retrieves the currently active MAC address of an Ethernet controller
 *  \details     -
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[out]  PhysAddrPtr  Buffer of at least 6 byte to pass the MAC address
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPhysAddr(
        uint8                        CtrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! \brief       Sets the MAC address of an Ethernet controller
 *  \details     Function sets the MAC address of an Ethernet controller. Dependent on the configuration of the "Write
 *               MAC address" feature the change is persisted in non-volatile RAM and also available after a power-
 *               cycle of the MCU.
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[in]   PhysAddrPtr  Buffer holding the MAC address that shall be applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPhysAddr(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of an Ethernet controller
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    CtrlIdx               Identifier of the Ethernet controller
 *  \param[in]    PhysAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    Eth_FilterActionType  Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return      E_NOT_OK - Filter modification failed
 *  \return      E_OK - Filter successfully updated
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 *********************************************************************************************************************/
FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter(
          uint8                                      CtrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) PhysAddrPtr,
          Eth_FilterActionType                       Action);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_MACHDL_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_MacHdl.h
 *********************************************************************************************************************/
