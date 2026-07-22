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
/*!        \file  Eth_30_Tc3xx_Types.h
 *        \brief  Public header file of Ethernet driver for data type access
 *
 *      \details  Contains data type declaration that shall be accessible in a public manner.
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

#if !defined (ETH_30_TC3XX_TYPES_H)
# define ETH_30_TC3XX_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Eth_GeneralTypes.h"
# include "Eth_30_Tc3xx_Cfg.h"
# include "Eth_30_Tc3xx_LL_Types.h"
# include "Eth_30_Tc3xx_GenTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define ETH_30_TC3XX_VENDOR_ID                                       (30u)
# define ETH_30_TC3XX_MODULE_ID                                       (88u)

/* ----- ETH DET Error codes ----- */
/*!< used to check if no error occurred - use a value unequal to any error code */
# define ETH_30_TC3XX_E_NO_ERROR                                      (0x00u)
/*!< Error code: API called with wrong controller index */
# define ETH_30_TC3XX_E_INV_CTRL_IDX                                  (0x01u)
/*!< Error code: API called while module was not initialized correctly */
# define ETH_30_TC3XX_E_NOT_INITIALIZED                               (0x02u)
/*!< Error code: API called with wrong pointer parameter (NULL_PTR) */
# define ETH_30_TC3XX_E_INV_POINTER                                   (0x03u)
/*!< Error code: API called with invalid parameter */
# define ETH_30_TC3XX_E_INV_PARAM                                     (0x04u)
/*!< Error code: Initialization triggered for an unknown configuration */
# define ETH_30_TC3XX_E_INV_CONFIG                                    (0x05u)
/*!< Error code: API called while module was in an invalid mode */
# define ETH_30_TC3XX_E_INV_MODE                                      (0x06u)
/*!< Error code: Invalid alignment of buffer or descriptor */
# define ETH_30_TC3XX_E_INV_ALIGNMENT                                 (0x07u)

# define ETH_30_TC3XX_NSEC_PER_SEC                                    (1000000000uL)

/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/
/*! Width of a register */
typedef uint32                                                     Eth_30_Tc3xx_RegWidthType;
/*! Offset within the register space of the Ethernet controller */
typedef uint32                                                     Eth_30_Tc3xx_RegOffsetType;
/*! Register access type */
typedef volatile Eth_30_Tc3xx_RegWidthType                          Eth_30_Tc3xx_RegAccessType;
/*! Pointer to a register */
typedef P2VAR(Eth_30_Tc3xx_RegAccessType, AUTOMATIC, MSR_REGSPACE)  Eth_30_Tc3xx_RegPtrType;

/**********************************************************************************************************************
 *  PUBLIC DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#endif /* ETH_30_TC3XX_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Types.h
 *********************************************************************************************************************/

