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
/*!        \file  Eth_30_Tc3xx_Generic.h
 *        \brief  Public header file of generic unit of Ethernet controller driver
 *
 *      \details  Provides access to the Ethernet controller drivers API.
 *
 *********************************************************************************************************************/
#if !defined(ETH_30_TC3XX_GENERIC_H)
# define ETH_30_TC3XX_GENERIC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_Init() */
# define ETH_30_TC3XX_SID_INIT                                        (0x01u)
/*!< Service ID: Eth_30_Tc3xx_GetVersionInfo() */
# define ETH_30_TC3XX_SID_GET_VERSION_INFO                            (0x0Du)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitMemory
 **********************************************************************************************************************/
/*! \brief       Initializes *_INIT_*-variables
 *  \details     Service to initialize module global variables at power up. This function initializes the variables in
 *               *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is uninitialized
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitMemory( void );

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the module
 *  \details     Function initializes the module Eth_30_Tc3xx. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   CfgPtr  Pointer to post-build configuration or null pointer
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module's *_INIT*_-variables are initialized either by Eth_30_Tc3xx_InitMemory() or startup code
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Init(
  P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_CONST, ETH_30_TC3XX_CONST) CfgPtr);

# if (ETH_30_TC3XX_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Retrieves the version information of the component.
 *  \details     Function retrieves the Vendor ID, Module ID and software version of the component.
 *  \param[out]  VersionInfoPtr  Buffer to store the _Intversion information
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-137688
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, AUTOMATIC) VersionInfoPtr);
# endif /* ETH_30_TC3XX_VERSION_INFO_API */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_GENERIC_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Generic.h
 *********************************************************************************************************************/
