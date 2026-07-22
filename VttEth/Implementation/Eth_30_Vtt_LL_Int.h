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
/*!        \file  Eth_30_Vtt_LL_Int.h
 *        \brief  Lower layer private header file
 *
 *      \details  Private data of lower layer part of component.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Vtt_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Vtt_LL.h
 *********************************************************************************************************************/
#if !defined (ETH_30_VTT_LL_INT_H)
# define ETH_30_VTT_LL_INT_H

# include "Eth_30_Vtt_HwAccess_Int.h"
# include "VttCntrl_Eth.h"
# include "SchM_Eth_30_Vtt.h"

/*------- ETH Frame offsets as byte index offsets ------------------------- */
/*! Reception frame: Byte index offset of destination MAC-Address */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_DST                         (2u)
/*! Reception frame: Byte index offset of source MAC-Address */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_SRC                         (8u)
/*! Reception frame: Byte index offset of Ethertype */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_TYPE                        (14u)
/*! Reception frame: Byte index offset of Payload */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_DATA                        (16u)
/*! Transmission frame: Byte index offset destination MAC-Address */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_TX_DST                         (0u)
/*! Transmission frame: Byte index offset of source MAC-Address */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_TX_SRC                         (6u)
/*! Transmission frame: Byte index offset of Ethertype */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_TX_TYPE                        (12u)
/*! Transmission frame: Byte index offset of Payload */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_TX_DATA                        (14u)
/*! Definition of the buffer space in Bytes occupied by the FCS */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE              (0u)
/*! Definition of the length of destination and source MAC address */
# define ETH_30_VTT_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE         (12u)

# define ETH_30_VTT_BEGIN_CRITICAL_SECTION_XXX()                      \
                                                                      SchM_Enter_Eth_30_Vtt_ETH_30_VTT_EXCLUSIVE_AREA_XXX()
# define ETH_30_VTT_END_CRITICAL_SECTION_XXX()                        \
                                                                      SchM_Exit_Eth_30_Vtt_ETH_30_VTT_EXCLUSIVE_AREA_XXX()

/* ISR related */
# define ETH_30_VTT_TX                                                (0U)
# define ETH_30_VTT_RX                                                (0U)

#endif /* ETH_30_VTT_LL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL_Int.h
 *********************************************************************************************************************/
