/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3008PT
* DESCRIPTION : CCFC3008PT flash hal drivers code
* HISTORY     : Initial version
* @file     flash_hal.c
* @version  1.0
* @date     2023 - 08 - 29
* @brief    Initial version.
*
*****************************************************************************/

#include "flash_hal.h" /* PRQA S 0380 */
#include "typedefs.h"

/*
 * @brief Select flash block for erase
 *
 * This function is to get special block select state.
 *
 * @param[in] infoIndex: flash block index.
 * @param[out] blkSel: Select the special flash block for erasing.
 * @return Operation status
 */
static status_t FLS_HAL_Get_Select(uint32_t infoIndex, fls_blk_sel_t * blkSel)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t selOffset = 0U;

    /* check infoIndex */
    if (infoIndex >= FLS_BLOCK_ALL)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    /* clear blkSel */
    blkSel->lowBlkSel = 0x0U;
    blkSel->midBlkSel = 0x0U;
    blkSel->highBlkSel = 0x0U;
    blkSel->first256KBlkSel = 0x0U;
    blkSel->second256KBlkSel = 0x0U;

    /* Select flash block to erase */
    if (infoIndex < FLS_LOW_BLOCK)
    {
        blkSel->lowBlkSel = (1UL << infoIndex);
    }
    else if (infoIndex < (FLS_LOW_BLOCK + FLS_MID_BLOCK))
    {
        selOffset = infoIndex - FLS_LOW_BLOCK;
        blkSel->midBlkSel = (1UL << selOffset);
    }
    else if (infoIndex < (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK))
    {
        selOffset = infoIndex - (FLS_LOW_BLOCK + FLS_MID_BLOCK);
        blkSel->highBlkSel = (1UL << selOffset);
    }
    else if (infoIndex < (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK + FLS_256K_BLOCK_FIRST))
    {
        selOffset = infoIndex - (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK);
        blkSel->first256KBlkSel = (1UL << selOffset);
    }
    else
    {
        selOffset = infoIndex - (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK + FLS_256K_BLOCK_FIRST);
        blkSel->second256KBlkSel = (1UL << selOffset);
    }

    return ret;
}

/*
 * @brief Check address is block aligned or not.
 *
 * This function is to check address is block aligned or not.
 *
 * @param[in] addr: flash erase start address.
 * @param[in] len: flash erase length.
 * @param[out] blkSel: Select the special flash block for erasing.
 * @return Operation status
 */
static status_t FLS_HAL_eraseVerify(uint32_t addr, uint32_t len, fls_blk_sel_t * blkSel)
{
    status_t ret = STATUS_ERROR;
    uint32_t i = 0U;

    for (i = 0; i < FLS_BLOCK_ALL; i++)
    {
        if ((addr == flashInfo[i].addrStart) &&
            ((addr+len) == (flashInfo[i].addrEnd + 1U)))
        {
            FLS_HAL_Get_Select(i, blkSel);
            ret = STATUS_SUCCESS;
            break;
        }
    }

    return ret;
}

/*
 * @brief Flash boundary judge.
 *
 * This function is to check flash boundary.
 *
 * @param[in] addr: flash operate address.
 * @param[in] len: flash operate length.
 * @return Operation status
 */
static status_t FLS_HAL_boundaryJudge(uint32_t addr, uint32_t len)
{
    status_t ret = STATUS_ERROR;
    uint32_t i = 0U;

    if (0U == len)
    {
        return ret;
    }

    for (i = 0; i < FLS_BLOCK_ALL; i++)
    {
        if ((addr >= flashInfo[i].addrStart) &&
            ((addr+len) <= (flashInfo[i].addrEnd + 1U)))
        {
            ret = STATUS_SUCCESS;
            break;
        }
    }

    return ret;
}

/*
 * @brief Initializes the FLASH module
 *
 * This function will initialize flash module.
 *
 * @param[in] flsConfig: flash config for module init.
 * @return Operation status
 */
status_t FLASH_HAL_Init(const flash_config_t * flsConfig)
{
    status_t ret = STATUS_SUCCESS;

    ret = FLASH_LLD_Init(flsConfig->lockBlk);

    return ret;
}

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
status_t FLASH_HAL_Erase(uint32_t eraseAddr, uint32_t len, uint32_t mode)
{
    status_t ret = STATUS_SUCCESS;
    fls_blk_sel_t blkSel;
    uint8_t opRet;

#ifdef FLASH_BIN_TEST
    FLASH_Erase_t FLASH_Erase_Ptr;
    FLASH_Erase_Ptr = (FLASH_Erase_t)FLASH_Erase_Bin;
#endif

    ret = FLS_HAL_eraseVerify(eraseAddr, len, &blkSel);
    if (STATUS_SUCCESS != ret)
    {
        return ret;
    }

    if ((mode != FLS_OP_ASYNC) && (mode != FLS_OP_SYNC))
    {
        ret = STATUS_ERROR;
        return ret;
    }

    /* Call FLASH_LLD_Erase to start erase */
#ifdef FLASH_BIN_TEST
    if ( NULL_PTR != FLASH_Erase_Ptr)
    {
        ret = FLASH_Erase_Ptr(blkSel.lowBlkSel,blkSel.midBlkSel,blkSel.highBlkSel,blkSel.first256KBlkSel,blkSel.second256KBlkSel,g_swapStatus);
    }
#else
    ret = FLASH_Erase(blkSel.lowBlkSel,blkSel.midBlkSel,blkSel.highBlkSel,blkSel.first256KBlkSel,blkSel.second256KBlkSel,g_swapStatus);/* WangM */
    //ret = FLASH_LLD_Erase(FLS_ERS_MAIN_SPACE, &blkSel, mode);
#endif
    if (STATUS_SUCCESS != ret)
    {
        return ret;
    }

    /* Call FLASH_LLD_CheckEraseStatus to confirm erase successful or not */
    do
    {
        ret = FLASH_LLD_CheckEraseStatus(&opRet);
    }while(ret == STATUS_FLASH_INPROGRESS);

    if ((STATUS_SUCCESS != ret) || (FLS_OK != opRet))
    {
        ret = STATUS_ERROR;
    }

    return ret;
}

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
status_t FLASH_HAL_Write(uint32_t writeAddr, uint8_t * srcAddr, uint32_t len, uint32_t mode)
{
    status_t ret = STATUS_SUCCESS;
    fls_ctx_data_t pCtxData;
    uint8_t opRet;

#ifdef FLASH_BIN_TEST
    FLASH_Program_t FLASH_Program_Ptr;
    FLASH_Program_Ptr = (FLASH_Program_t)FLASH_Porgram_Bin;

#endif

    ret = FLS_HAL_boundaryJudge(writeAddr, len);
    if (STATUS_SUCCESS != ret)
    {
        return ret;
    }

    if (NULL == srcAddr)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    if ((mode != FLS_OP_ASYNC) && (mode != FLS_OP_SYNC))
    {
        ret = STATUS_ERROR;
        return ret;
    }

    /* Call FLASH_LLD_Program to start program */
    pCtxData.dest = writeAddr;
    pCtxData.src = (uint32_t)srcAddr;
    pCtxData.size = len;
    pCtxData.mode = mode;

#ifdef FLASH_BIN_TEST
    if( NULL_PTR != FLASH_Program_Ptr )
    {
        ret = FLASH_Program_Ptr(pCtxData.dest, pCtxData.src, pCtxData.size);
    }
#else
     ret = FLASH_Program(pCtxData.dest, pCtxData.src, pCtxData.size);/* WangM */
    //ret = FLASH_LLD_Program(&pCtxData);
#endif

    if (STATUS_SUCCESS != ret)
    {
        return ret;
    }

    /* Call FLASH_LLD_CheckProgramStatus to confirm program successful or not */
    do
    {
        ret = FLASH_LLD_CheckProgramStatus(&pCtxData, &opRet);
    }while(ret == STATUS_FLASH_INPROGRESS);

    if ((STATUS_SUCCESS != ret) || (FLS_OK != opRet))
    {
        ret = STATUS_ERROR;
    }

    return ret;
}

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
status_t FLASH_HAL_Read(uint32_t readAddr, uint8_t * srcAddr, uint32_t len)
{
    status_t ret = STATUS_SUCCESS;

    ret = FLS_HAL_boundaryJudge(readAddr, len);
    if (STATUS_SUCCESS != ret)
    {
        return ret;
    }

    if (NULL == srcAddr)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    cc_memcpy((uint8_t *)(srcAddr), (const uint8_t *)readAddr, len);

    return ret;
}


