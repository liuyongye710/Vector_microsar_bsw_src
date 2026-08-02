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
/*!        \file  Eth_30_Tc3xx_TimeSync_Ifc_Int.h
 *        \brief  Declaration of private Ethernet controller hardware timer implementation
 *
 *      \details  Provides access to the private hardware timer related API of the Ethernet controller driver.
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
#if !defined (ETH_30_TC3XX_TIME_SYNC_IFC_INT_H)
# define ETH_30_TC3XX_TIME_SYNC_IFC_INT_H

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#  include "Eth_30_Tc3xx_Types_Int.h"
#  include "Eth_30_Tc3xx_LL_Ifc_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined(ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE                         LOCAL_INLINE
# endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the time synchronization structures
 *  \details     -
 *  \param[in]   CtrlIdx              Identifier of the Eth controller
*                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Initialization finished successfully
 *  \return      E_NOT_OK - Initialization failed
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_Init(
  uint8 CtrlIdx);

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_MemMap */

# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

#endif /* ETH_30_TC3XX_TIME_SYNC_IFC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync_Ifc_Int.h
 *********************************************************************************************************************/
