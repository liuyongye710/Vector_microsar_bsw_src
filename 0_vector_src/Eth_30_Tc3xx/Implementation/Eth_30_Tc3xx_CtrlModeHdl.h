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
/*!        \file  Eth_30_Tc3xx_CtrlModeHdl.h
 *        \brief  Controller mode handling header of the Ethernet controller driver
 *
 *      \details  Provides access to the controller mode handling related API of the Ethernet controller driver.
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

#if !defined (ETH_30_TC3XX_CTRLMODEHDL_H)
# define ETH_30_TC3XX_CTRLMODEHDL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_LL_CtrlModeHdl.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_ControllerInit() */
# define ETH_30_TC3XX_SID_CONTROLLER_INIT                             (0x02u)
/*!< Service ID: Eth_30_Tc3xx_SetControllerMode() */
# define ETH_30_TC3XX_SID_SET_CONTROLLER_MODE                         (0x03u)
/*!< Service ID: Eth_30_Tc3xx_GetControllerMode() */
# define ETH_30_TC3XX_SID_GET_CONTROLLER_MODE                         (0x04u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes an Ethernet controller
 *  \details     Function initializes an Ethernet controller and the related variables so it is possible to set it in
 *               operation afterwards.
 *  \param[in]   CtrlIdx  Identifier of the Ethernet controller
 *  \param[in]   CfgIdx   Identifier of the configuration (only 0 allowed)
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ControllerInit(
  uint8 CtrlIdx,
  uint8 CfgIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetControllerMode
 **********************************************************************************************************************/
/*! \brief       Sets the operation mode of an Ethernet controller
 *  \details     Function sets the operation mode of the Ethernet controller so it is either turned off (no frame
 *               reception and transmission) or turned on (frames can be transmitted and received).
 *  \param[in]   CtrlIdx   Identifier of the Ethernet controller
 *  \param[in]   CtrlMode  Operation mode that shall be applied:
 *                         ETH_MODE_DOWN - Ethernet controller shall be turned off
 *                         ETH_MODE_ACTIVE - Ethernet controller shall be turned on
 *  \return      E_NOT_OK - Operation mode couldn't be applied
 *  \return      E_OK - Operation mode successfully applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetControllerMode(
  uint8        CtrlIdx,
  Eth_ModeType CtrlMode);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetControllerMode
 **********************************************************************************************************************/
/*! \brief       Retrieves the current operation mode of an Ethernet controller
 *  \details     -
 *  \param[in]   CtrlIdx      Identifier of the Ethernet controller
 *  \param[out]  CtrlModePtr  Operation mode retrieved
 *  \return      E_NOT_OK - Retrieval of operation mode failed
 *  \return      E_OK - Operation mode successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetControllerMode(
        uint8                               CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) CtrlModePtr);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_CTRLMODEHDL_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_CtrlMode.h
 *********************************************************************************************************************/
