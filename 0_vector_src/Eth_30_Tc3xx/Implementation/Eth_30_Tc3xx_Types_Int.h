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
/*!        \file  Eth_30_Tc3xx_Types_Int.h
 *        \brief  Private header file of Ethernet driver for data type access
 *
 *      \details  Contains data type declaration that shall be accessible in a private manner.
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

#if !defined (ETH_30_TC3XX_TYPES_INT_H)
# define ETH_30_TC3XX_TYPES_INT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Ethertype indices and shifts */
# define ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX                          (0u)
# define ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX                          (1u)
# define ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_RSHIFT                       (8u)
# define ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_LSHIFT                       (8u)

/* Tx Confirmation */
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING               (0u)
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING                   (1u)

/* Descriptor status */
# define ETH_30_TC3XX_DESCRIPTOR_NOT_READY                            (0u)
# define ETH_30_TC3XX_DESCRIPTOR_READY                                (1u)
# define ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED                          (2u)

# define ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED              (ETH_30_TC3XX_UINT16_MAX)

# define ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED                       (0u)
# define ETH_30_TC3XX_TIMESYNC_TS_REQUESTED                           (1u)


# define ETH_30_TC3XX_MAX_CFGS_TOTAL                                  (1u)

# define ETH_30_TC3XX_MAX_MII_REG_TOTAL                               (32u)

# define ETH_30_TC3XX_MULTICAST_BUCKET_COUNTERS                       (64u)
# define ETH_30_TC3XX_BUCKET_MAX_CNT                                  (0xFFu)

# define ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS                   (-1)

# define ETH_30_TC3XX_VLAN_ETHER_TYPE                                 (0x8100u)
# define ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET                      (2u)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_MASK                              (0xE0u)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT                             (5u)

# define ETH_30_TC3XX_VLAN_ID_BYTE_MASK                               (0x0FFFu)

# define ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE                (0xFFFFFFFFu)

# define ETH_30_TC3XX_INVALID_FIFO_IDX                                (0xFFu)

# define ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING                       (0xFFu)

# define ETH_30_TC3XX_ISR_NO_OS_SUPPORT                               (0u)
# define ETH_30_TC3XX_ISR_CATEGORY_1                                  (1u)
# define ETH_30_TC3XX_ISR_CATEGORY_2                                  (2u)

/* Frame attributes */

# define ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE                       (2u)
# define ETH_30_TC3XX_HDR_LEN_BYTE                                    (14u)
# define ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE                          (12u)
# define ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE                          (60u)
# define ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE                        (ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE - \
                                                                      ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE - \
                                                                      ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE)
/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PUBLIC DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#endif /* ETH_30_TC3XX_TYPES_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Types_Int.h
 *********************************************************************************************************************/

