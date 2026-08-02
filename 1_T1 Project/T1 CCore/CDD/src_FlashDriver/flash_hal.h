/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3008PT
* DESCRIPTION : CCFC3008PT flash hal drivers h file
* HISTORY     : Initial version
* @file     flash_hal.h
* @version  1.0
* @date     2023 - 08 - 29
* @brief    Initial version.
*
*****************************************************************************/

#ifndef FLASH_HAL_H_
#define FLASH_HAL_H_

#include "flash_lld.h"

typedef struct
{
    const uint8_t lockBlk[FLS_BLOCK_ALL];
} flash_config_t;

/*
 * @brief Initializes the FLASH module
 *
 * This function will initialize flash module.
 *
 * @param[in] flsConfig: flash config for module init.
 * @return Operation status
 */
status_t FLASH_HAL_Init(const flash_config_t * flsConfig);

/*
 * @brief Flash erase operation
 *
 * This function is to do flash erase operation.
 *
 * @param[in] eraseAddr: flash erase start address.
 * @param[in] len: flash erase length.
 * @param[in] mode: means the operate mode of erase.
              FLS_OP_SYNC: means sync erase operate.
              FLS_OP_ASYNC: means async erase operate.
 * @return Operation status
 */
status_t FLASH_HAL_Erase(uint32_t eraseAddr, uint32_t len, uint32_t mode);

/*
 * @brief Flash write operation
 *
 * This function is to do flash write operation.
 *
 * @param[in] writeAddr: flash write start address.
 * @param[in] srcAddr: flash write data buffer.
 * @param[in] len: flash write length.
 * @param[in] mode: means the operate mode of erase.
              FLS_OP_SYNC: means sync erase operate.
              FLS_OP_ASYNC: means async erase operate.
 * @return Operation status
 */
status_t FLASH_HAL_Write(uint32_t writeAddr, uint8_t * srcAddr, uint32_t len, uint32_t mode);

/*
 * @brief Flash read operation
 *
 * This function is to do flash read operation.
 *
 * @param[in] readAddr: flash read start address.
 * @param[out] srcAddr: flash read data buffer.
 * @param[in] len: flash read length.
 * @return Operation status
 */
status_t FLASH_HAL_Read(uint32_t readAddr, uint8_t * srcAddr, uint32_t len);

/*
 * @brief Flash compare operation
 *
 * This function is to compare the data is right or not.
 *
 * @param[in] compareAddr: Destination address for compare.(4 bytes aligned)
 * @param[in] srcAddr: Source buffer address for compare.(4 bytes aligned)
 * @param[in] len: Size of the flash region to compare.(4 bytes aligned)
 * @param[out] pFailAddr: Return the first failing address in flash.
 * @return Operation status
 */
status_t FLASH_HAL_Compare(uint32_t compareAddr, uint8_t * srcAddr, uint32_t len, uint32_t * pFailAddr);

#endif /* FLASH_HAL_H_ */
