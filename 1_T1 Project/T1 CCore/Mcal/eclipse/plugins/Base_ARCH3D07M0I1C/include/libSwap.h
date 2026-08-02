/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3008PT
* DESCRIPTION : CCFC3008PT flash swap h file
* HISTORY     : Initial version
* @file     libSwap.h
* @version  1.0
* @date     2023 - 08 - 08
* @brief    Initial version.
*
*****************************************************************************/

#ifndef LIBSWAP_H_
#define LIBSWAP_H_


/*
 * @brief Swap to Flash A partition
 *
 * This function is to Swap Flash A partition.
 *
 * @return 0U: Swap success.
 *         1U: Swap fail.
 */
uint8_t FLASH_Swap_A(void);

/*
 * @brief Swap to Flash B partition
 *
 * This function is to Swap Flash B partition.
 *
 * @return 0U: Swap success.
 *         1U: Swap fail.
 */
uint8_t FLASH_Swap_B(void);

/*
 * @brief Get Flash Swap status
 *
 * This function is to Get Flash Swap status.
 *
 * @return 0U: is A partition.
 *         1U: is B partition.
 */
uint8_t FLASH_Get_Swap_Status(void);

#endif /* LIBSWAP_H_ */
