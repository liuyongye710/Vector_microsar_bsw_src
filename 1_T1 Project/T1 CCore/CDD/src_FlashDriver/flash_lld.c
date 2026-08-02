/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3008PT
* DESCRIPTION : CCFC3008PT flash low level drivers code
* HISTORY     : Initial version
* @file     flash_lld.c
* @version  1.0
* @date     2023 - 04 - 11
* @brief    Initial version.
*
*****************************************************************************/

#include "flash_lld.h" /* PRQA S 0380 */
#include "intc_lld.h"

/* Flash EHV value */
static uint8_t FLS_EHV_Val = 0U;
uint8_t g_swapStatus = 0U;
#ifdef FLS_AC_LOAD
/* Function pointer of access code */
static fls_acload_t FLS_AcCodePtr;
#if defined(START_FROM_FLASH)
/* SRAM buffer for access code */
static uint32_t FLS_AcCodeArea[32] = {0U}; /* PRQA S 3218 */
#endif
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#ifdef FLS_AC_LOAD
static void FLS_AccessCode(void)
{
    /* Set MCR EHV bit, start operation */
    FLS_FMC.MCR.B.EHV = 1U;

    /* Wait MCR DONE bit is set */
    while (FLS_FMC.MCR.B.DONE == 0x0U)
    {
    }
}
#endif

/*
 * @brief Get the inter_write address
 *
 * This function will return the inter_write address depend on selected block
 *
 * @param[in] blkSel The selected flash block info.
 * @return Operation status
 */
static uint32_t FLS_LLD_GetInterWriteAddr(const fls_blk_sel_t * blkSel)
{
    uint8_t i = 0U;
    uint8_t offset = 0U;
    uint32_t addr = 0U;

    if (blkSel->lowBlkSel > 0U)
    {
        offset = FLS_LOW_OFFSET;
        for (i = 0U; i < FLS_LOW_BLOCK; i++)
        {
            if (((blkSel->lowBlkSel & (1UL << i)) >> i) == 1UL)
            {
                addr = flashInfo[i + offset].addrStart; /* PRQA S 2985 */
                break;
            }
        }
    }
    else if (blkSel->midBlkSel > 0U)
    {
        offset = FLS_MID_OFFSET;
        for (i = 0U; i < FLS_MID_BLOCK; i++)
        {
            if (((blkSel->midBlkSel & (1UL << i)) >> i) == 1UL)
            {
                addr = flashInfo[i + offset].addrStart;
                break;
            }
        }
    }
    else if (blkSel->highBlkSel > 0U)
    {
        offset = FLS_HIGH_OFFSET;
        for (i = 0U; i < FLS_HIGH_BLOCK; i++)
        {
            if (((blkSel->highBlkSel & (1UL << i)) >> i) == 1UL)
            {
                addr = flashInfo[i + offset].addrStart;
                break;
            }
        }
    }
    else if (blkSel->first256KBlkSel > 0U)
    {
        offset = FLS_256K_FIRST_OFFSET;
        for (i = 0U; i < FLS_256K_BLOCK_FIRST; i++)
        {
            if (((blkSel->first256KBlkSel & (1UL << i)) >> i) == 1UL)
            {
                addr = flashInfo[i + offset].addrStart;
                break;
            }
        }
    }
#if (FLS_256K_BLOCK_SECOND != 0U)
    else if (blkSel->second256KBlkSel > 0U)
    {
        offset = FLS_256K_SECOND_OFFSET;
        for (i = 0U; i < FLS_256K_BLOCK_SECOND; i++)
        {
            if (((blkSel->second256KBlkSel & (1UL << i)) >> i) == 1UL)
            {
                addr = flashInfo[i + offset].addrStart;
                break;
            }
        }
    }
#endif
    else
    {
    }

    return addr;
}


/*
 * @brief Check the status of flash erase operate
 *
 * This function will check the status of ongoing high voltage in erase
 *
 * @param[out] pStatus The status of flash erase after calling the function.
 * @return Operation status
 */
static status_t FLS_LLD_CheckErsExec(uint8_t * pStatus)
{
    status_t ret = STATUS_SUCCESS;
    *pStatus = FLS_OK;

    /* Check EGOOD (PEG) */
    if (FLS_FMC.MCR.B.PEG != 0U)
    {
        /* Clear EHV if it is high */
        if ( (FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U) )
        {
            /* Clear EHV */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
        else
        {
            *pStatus = FLS_ERS_WRITE;
        }
    }
    else
    {
        /* EGOOD (PEG) is low */
        ret = STATUS_ERROR;

        /* Clear EHV if it is high */
        if ( (FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U) )
        {
            /* Clear EHV */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
    }

    if (*pStatus != FLS_ERS_WRITE)
    {
        /* Clear ERS */
        FLS_FMC.MCR.B.ERS = 0U;
    }

    return ret;
}

/*
 * @brief Check the status of flash program operate
 *
 * This function will check the status of ongoing high voltage in program
 *
 * @param[in] pCtxData Storing context variables.
 * @param[out] pStatus The status of flash program after calling the function.
 * @return Operation status
 */
static status_t FLS_LLD_CheckPgmExec(fls_ctx_data_t * pCtxData,
                                              uint8_t * pStatus)
{
    status_t ret = STATUS_SUCCESS;
    *pStatus = FLS_OK;

    /* check PEG */
    if (FLS_FMC.MCR.B.PEG != 0U) /* PEG is high */
    {
        /* Clear EHV if it is high */
        if ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U))
        {
            /* Clear EHV */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
            /* If there is remaining data needs to be programmed */
            if ((pCtxData->size) != 0x0U)
            {
                /* Call FLASH_LLD_Program to continue the operation */
                ret = FLASH_LLD_Program(pCtxData);

                if (ret == STATUS_SUCCESS)
                {
                    ret = STATUS_FLASH_INPROGRESS;
                }
            }
            else /* pCtxData->size == 0 */
            {
                /* Program finished successfully, clear PGM */
                FLS_FMC.MCR.B.PGM = 0U;
            }
        }
        else /* EHV == 0 */
        {
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                *pStatus = FLS_ERS_SUS_PGM_WRITE;
            }
            else
            {
                *pStatus = FLS_PGM_WRITE;
            }
        }
    }
    else /* PEG is low */
    {
        if ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U))
        {
            /* Clear EHV */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
        else /* EHV == 0 */
        {
            /* PEG is invalid at this stage */
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                *pStatus = FLS_ERS_SUS_PGM_WRITE;
            }
            else
            {
                *pStatus = FLS_PGM_WRITE;
            }
        }
        /* Program finished unsuccessfully, clear PGM */
        FLS_FMC.MCR.B.PGM = 0U;
        ret = STATUS_ERROR;
    }

    return ret;
}

/*
 * @brief Execute program operation
 *
 * This function will do program operation
 *
 * @param[in] pCtxData Storing context variables.
 * @return Operation status
 */
static status_t FLS_LLD_PgmExec(fls_ctx_data_t * pCtxData)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t srcIndex;
    uint32_t temp;

    if (0U != pCtxData->size)
    {
        /* Set MCR_PGM to start program operation */
        FLS_FMC.MCR.B.PGM = 1U;

        if (FLS_FMC.MCR.B.PGM == 0U)
        {
            ret = STATUS_FLASH_ERROR_ENABLE;
        }
        else
        {
            /* Compute the buffer size used in the program cycle and calculate number of word for interlock write */
            if (pCtxData->size > FLS_PROGRAMABLE_SIZE)
            {
                temp = FLS_PROGRAMABLE_SIZE / FLS_WORD_SIZE;
            }
            else
            {
                temp = pCtxData->size / FLS_WORD_SIZE;
            }

            /* Program data */
            for (srcIndex = 0U; srcIndex < temp; srcIndex++)
            {
                /* Programming write */
                *(volatile uint32_t *)(pCtxData->dest) = *(volatile uint32_t *)(pCtxData->src);
                /* Update dest, size, source index */
                pCtxData->dest += FLS_WORD_SIZE;
                pCtxData->src += FLS_WORD_SIZE;
                pCtxData->size -= FLS_WORD_SIZE;

                /* Is it time to do page programming?  */
                if (0U == (pCtxData->dest % FLS_PROGRAMABLE_SIZE))
                {
                    break;
                }
            }

            /* Set MCR_EHV bit */
            if (FLS_OP_SYNC == pCtxData->mode)
            {
//                INTC_LLD_Set_Global_Disable();
//                FLS_AcCodePtr();
//                INTC_LLD_Set_Global_Enable();
            }
            else
            {
                FLS_FMC.MCR.B.EHV = 1U;
            }
        }
    }
    else
    {
    }

    return ret;
}

/*
 * @brief Execute suspend operation
 *
 * This function will suspend the program, erase activities
 *
 * @param[out] susStatus The status of suspend after calling the function.
 * @return Operation status
 */
static void FLS_LLD_SusExec(uint8_t * susStatus)
{
    uint16_t susDelay = 0U;
    uint32_t i = 450U;

    if (FLS_FMC.MCR.B.EHV == 0U)
    {
        if (FLS_FMC.MCR.B.PGM != 0U)
        {
            *susStatus = FLS_PGM_WRITE;

            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                *susStatus = FLS_ERS_SUS_PGM_WRITE;
            }
        }
        else
        {
            *susStatus = FLS_ERS_WRITE;
        }
        /* Wait MCR DONE bit is set */
        while ((FLS_FMC.MCR.B.DONE == 0x0U) && (i > 0U))
        {
            i--;
        }
    }
    else
    {
        if (FLS_FMC.MCR.B.PGM != 0x0U)
        {
            /* Set MCR_PSUS bit */
            FLS_FMC.MCR.B.PSUS = 1U;
            for (susDelay = 0U; susDelay < 160U; susDelay++)
            {}
        }
        else
        {
            /* Set MCR-ESUS bit */
            FLS_FMC.MCR.B.ESUS = 1U;
            for (susDelay = 0U; susDelay < 320U; susDelay++)
            {}
        }
    }
}

/*
 * @brief Config Flash Calibration Region Descriptor
 *
 * This function will config flash calibration region descriptor.
 *
 * @param[in] cdrIndex: The Index of Calibration Remap Descriptor.
 * @param[in] remapConfig: The config of Calibration Region Descriptor.
 * @return Operation status
 */
static status_t FLS_LLD_OverlayConfig(uint32_t cdrIndex, flash_remap_config_t const *remapConfig)
{
    status_t ret = STATUS_SUCCESS;

    /* check flash region count */
    if (cdrIndex < PFLASH_PFCRD_COUNT)
    {
        /* set the Logical Start Address, ensure the most 4-bit LSB are 0*/
        PFLASH.PFCRD[cdrIndex].Word0.R = remapConfig->flsLogicAddr&0xFFFFFFF0U;

        /* set the Physical Start Address, ensure the most 4-bit LSB are 0*/
        PFLASH.PFCRD[cdrIndex].Word1.R = remapConfig->ramPhyAddr&0xFFFFFFF0U;

        /* enable Crossbar master and configure the region size*/
        PFLASH.PFCRD[cdrIndex].Word2.R = 0xFFFF0000U|(uint32_t)(remapConfig->remapSize);

        /* enable the corresponding Calibration Remap Descriptor */
        PFLASH.PFCRDE.R |= ((uint32_t)(1UL<<(31U-cdrIndex)))&0xFFFFFFFFU; /* PRQA S 2985 */
    }
    else
    {
        ret = STATUS_ERROR;
    }

    return ret;
}

/*
 * @brief Check the program operation
 *
 * This function will check the status of ongoing program operation.
 *
 * @param[in] pCtxData: Storing context variables.
 * @param[out] opRet: Return the status of flash.
 * @return Operation status
 */
status_t FLASH_LLD_CheckProgramStatus(fls_ctx_data_t * pCtxData,
                                      uint8_t * opRet)
{
    status_t ret = STATUS_SUCCESS;

    if ( (pCtxData == NULL) || (opRet == NULL))
    {
        ret = STATUS_ERROR;
        return ret;
    }

    *opRet = FLS_OK;

    /* There must be a program operation */
    if (FLS_FMC.MCR.B.PGM != 0U)
    {
        /* If DONE bit goes high */
        if (FLS_FMC.MCR.B.DONE != 0U)
        {
            /* If the operation is suspended */
            if (FLS_FMC.MCR.B.PSUS != 0U)
            {
                /* Check if the suspended program is PGM_SUS or ERS_SUS_PGM_SUS */
                if (FLS_FMC.MCR.B.ERS != 0U)
                {
                    *opRet = FLS_ERS_SUS_PGM_SUS;
                }
                else
                {
                    *opRet = FLS_PGM_SUS;
                }
            }
            else
            {
                ret = FLS_LLD_CheckPgmExec(pCtxData, opRet);
            }
        }
        else
        {
            /* DONE bit is still low means the operation is in-progress */
            ret = STATUS_FLASH_INPROGRESS;
        }
    }

    return ret;
}

/*
 * @brief Check the erase operation
 *
 * This function will check the status of ongoing erase operation.
 *
 * @param[out] opRet: Return the state of flash.
 * @return Operation status
 */
status_t FLASH_LLD_CheckEraseStatus(uint8_t * opRet)
{
    status_t ret = STATUS_SUCCESS;

    if (opRet == NULL)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    *opRet = FLS_OK;

    /* There must be an erase operation */
    if (FLS_FMC.MCR.B.ERS != 0U)
    {
        /* If DONE bit goes high */
        if (FLS_FMC.MCR.B.DONE != 0U)
        {
            /* If the operation is suspended */
            if (FLS_FMC.MCR.B.ESUS != 0U)
            {
                *opRet = FLS_ERS_SUS;
            }
            else
            {
                ret = FLS_LLD_CheckErsExec(opRet);
            }
        }
        else
        {
            /* DONE bit is still low means the operation is in-progress */
            ret = STATUS_FLASH_INPROGRESS;
        }
    }

    return ret;
}

/*
 * @brief Initializes the FLASH module
 *
 * This function will initialize flash module.
 *
 * @param[in] lockBlk: Indicating the lock status of flash module.
 * @return Operation status
 */
status_t FLASH_LLD_Init(const uint8_t * lockBlk)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t i = 0;
    uint32_t lockValue = 0U;
    uint32_t lock2 = 0U;

    /* unLock Flash Block*/
    FLS_FMC.LOCK0.B.LOWLOCK = 0U;
    FLS_FMC.LOCK0.B.MIDLOCK = 0U;
    FLS_FMC.LOCK1.B.HIGHLOCK = 0U;
    FLS_FMC.LOCK2.B.A256KLOCK = 0U;
    FLS_FMC.LOCK3.B.A256KLOCK = 0U;

    /* lock Flash Block*/
    for (i = 0; i < FLS_BLOCK_ALL; i++)
    {
        if (1U == lockBlk[i])
        {
            if (0U == flashInfo[i].lockSelReg)
            {
                FLS_FMC.LOCK0.R |= (1UL << flashInfo[i].lockSelBit);
            }
            else if (1U == flashInfo[i].lockSelReg)
            {
                FLS_FMC.LOCK1.R |= (1UL << flashInfo[i].lockSelBit);
            }
            else if (2U == flashInfo[i].lockSelReg)
            {
                lockValue |= (1UL << flashInfo[i].lockSelBit);
            }
            else if (3U == flashInfo[i].lockSelReg)
            {
                FLS_FMC.LOCK3.R |= (1UL << flashInfo[i].lockSelBit);
            }
            else
            {
                /* No operation */
            }
        }
    }

    /* If Swapped to B partition */
    if (1U == g_swapStatus)
    {
        lock2 = (((lockValue >> 8U) & 0x000000FFU) | ((lockValue << 8U) & 0x0000FF00U));
    }
    else
    {
        lock2 = lockValue & FLS_LOCK_MASK_FIR256K;
    }
    FLS_FMC.LOCK2.R |= lock2;

    /* Clear error bits */
    FLS_FMC.MCR.B.EER = 1U;
    FLS_FMC.MCR.B.RWE = 1U;
    FLS_FMC.MCR.B.SBC = 1U;
    FLS_FMC.MCR.B.RVE = 1U;
    FLS_FMC.MCR.B.RRE = 1U;
    FLS_FMC.MCR.B.AEE = 1U;
    FLS_FMC.MCR.B.EEE = 1U;

#ifdef FLS_AC_LOAD
#if defined(START_FROM_FLASH)
    /* Copy Flash Access Code to SRAM */
    uint32_t * RomPtr = (uint32_t *)&FLS_AccessCode; /* PRQA S 0307,3678 */
    uint32_t * RomEndPtr = RomPtr + (sizeof(FLS_AcCodeArea)/4U); /* PRQA S 3678 */
    uint32_t * RamPtr = (uint32_t *)FLS_AcCodeArea;

    for (; (uint32_t)RomPtr < (uint32_t)RomEndPtr; RomPtr++)
    {
        *RamPtr = *RomPtr;
        RamPtr++;
    }

    FLS_AcCodePtr = (fls_acload_t)&FLS_AcCodeArea; /* PRQA S 0307 */
#else
    /* If Flash Access Code in SRAM */
    FLS_AcCodePtr = (fls_acload_t)&FLS_AccessCode;
#endif
#endif

    return ret;
}

/* ********************************************* */




/*
 * @brief Get flash block lock status
 *
 * This function will get the lock status for selected flash block.
 *
 * @param[in] lockedBlkSel: Select the special flash block.
 * @param[out] lockedBlkStatus: Return lock status of selected flash block.
 * @return Operation status
 */
status_t FLASH_LLD_GetLock(uint8_t lockedBlkSel,
                           uint32_t * lockedBlkStatus)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t lockValue = 0U;

    /* Determine which address space is selected */
    switch (lockedBlkSel)
    {
        case FLS_BLK_LOW:
            *lockedBlkStatus = (FLS_FMC.LOCK0.B.LOWLOCK & FLS_LOCK_MASK_LOW);
            break;
        case FLS_BLK_MID:
            *lockedBlkStatus = (FLS_FMC.LOCK0.B.MIDLOCK & FLS_LOCK_MASK_MID);
            break;
        case FLS_BLK_HIGH:
            *lockedBlkStatus = (FLS_FMC.LOCK1.B.HIGHLOCK & FLS_LOCK_MASK_HIGH);
            break;
        case FLS_BLK_FIRST_256K:
            lockValue = (FLS_FMC.LOCK2.B.A256KLOCK & FLS_LOCK_MASK_FIR256K);
            /* If Swapped to B partition */
            if (1U == g_swapStatus)
            {
                *lockedBlkStatus = (((lockValue >> 8U) & 0x000000FFU) | ((lockValue << 8U) & 0x0000FF00U));
            }
            else
            {
                *lockedBlkStatus = lockValue;
            }
            break;
        case FLS_BLK_SECOND_256K:
            *lockedBlkStatus = (FLS_FMC.LOCK3.R & FLS_LOCK_MASK_SEC256K);
            break;
        default:
            ret = STATUS_ERROR;
            break;
    }

    return ret;
}

/*
 * @brief Set flash block lock status
 *
 * This function will set the lock status for selected flash block.
 *
 * @param[in] lockedBlkSel: Select the special flash block.
 * @param[in] lockedBlkStatus: The lock status will set to the selected flash block.
 * @return Operation status
 */
status_t FLASH_LLD_SetLock(uint8_t lockedBlkSel,
                           uint32_t lockedBlkStatus)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t value = 0x0U;                   /* value of block lock */

    /* Check which address space need to set lock, then:
     * 1. Clear block lock field.
     * 2. Set block lock field.
     * 3. Check block lock field.
     * */
    switch (lockedBlkSel)
    {
        case FLS_BLK_LOW:
            value = lockedBlkStatus & FLS_LOCK_MASK_LOW;
            FLS_FMC.LOCK0.B.LOWLOCK = 0U;
            FLS_FMC.LOCK0.B.LOWLOCK = value;
            if ((FLS_FMC.LOCK0.B.LOWLOCK & FLS_LOCK_MASK_LOW) != value)
            {
                ret = STATUS_ERROR;
            }
            break;
        case FLS_BLK_MID:
            value = lockedBlkStatus & FLS_LOCK_MASK_MID;
            FLS_FMC.LOCK0.B.MIDLOCK = 0U;
            FLS_FMC.LOCK0.B.MIDLOCK = value;
            if ((FLS_FMC.LOCK0.B.MIDLOCK & FLS_LOCK_MASK_MID) != value)
            {
                ret = STATUS_ERROR;
            }
            break;
        case FLS_BLK_HIGH:
            value = lockedBlkStatus & FLS_LOCK_MASK_HIGH;
            FLS_FMC.LOCK1.B.HIGHLOCK = 0U;
            FLS_FMC.LOCK1.B.HIGHLOCK = value;
            if ((FLS_FMC.LOCK1.B.HIGHLOCK & FLS_LOCK_MASK_HIGH) != value)
            {
                ret = STATUS_ERROR;
            }
            break;
        case FLS_BLK_FIRST_256K:
            /* If Swapped to B partition */
            if (1U == g_swapStatus)
            {
                value = (((lockedBlkStatus >> 8U) & 0x000000FFU) | ((lockedBlkStatus << 8U) & 0x0000FF00U));
            }
            else
            {
                value = lockedBlkStatus & FLS_LOCK_MASK_FIR256K;
            }
            FLS_FMC.LOCK2.B.A256KLOCK = 0U;
            FLS_FMC.LOCK2.B.A256KLOCK = value;
            if ((FLS_FMC.LOCK2.B.A256KLOCK & FLS_LOCK_MASK_FIR256K) != value)
            {
                ret = STATUS_ERROR;
            }
            break;
        case FLS_BLK_SECOND_256K:
            value = lockedBlkStatus & FLS_LOCK_MASK_SEC256K;
            FLS_FMC.LOCK3.B.A256KLOCK = 0U;
            FLS_FMC.LOCK3.B.A256KLOCK = value;
            if ((FLS_FMC.LOCK3.R & FLS_LOCK_MASK_SEC256K) != value)
            {
                ret = STATUS_ERROR;
            }
            break;
        default:
            ret = STATUS_ERROR;
            break;
    }

    return ret;
}

/*
 * @brief Erase the selected flash block
 *
 * This function is to do erase operation for selected flash block.
 *
 * @param[in] eraseSpace: Select flash main space.
 * @param[in] blkSel: Select the special flash block for erasing.
 * @param[in] mode: means the operate mode of erase.
              FLS_OP_SYNC: means sync erase operate.
              FLS_OP_ASYNC: means async erase operate.
 * @return Operation status
 */
status_t FLASH_LLD_Erase(uint8_t eraseSpace,
                         fls_blk_sel_t * blkSel,
                         uint32_t mode)
{
    status_t ret = STATUS_SUCCESS;
    uint32_t interlockWriteAddress = 0U;

    if (blkSel == NULL)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    /* Check for validity of erase option */
    if (eraseSpace == FLS_ERS_MAIN_SPACE)
    {
        interlockWriteAddress = FLS_LLD_GetInterWriteAddr(blkSel);
        if (0U == interlockWriteAddress)
        {
            ret = STATUS_ERROR;
            return ret;
        }
    }
    else
    {
        ret = STATUS_ERROR;
        return ret;
    }

    if ((FLS_FMC.MCR.B.PGM != 0U) || ((FLS_FMC.MCR.B.ERS != 0U) && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.ESUS != 0U))))
    {
        ret = STATUS_BUSY;
    }
    else
    {
        /* Set MCR_ERS to start erase operation */
        FLS_FMC.MCR.B.ERS = 1U;

        if (FLS_FMC.MCR.B.ERS == 0U)
        {
            ret = STATUS_FLASH_ERROR_ENABLE;
        }
        else
        {
            /* Correct the block selection for the case we erase Main array */

            /* Mask off reserved bits for low address space */
            blkSel->lowBlkSel &= FLS_SEL_MASK_LOW;
            /* Mask off reserved bits for mid address space */
            blkSel->midBlkSel &= FLS_SEL_MASK_MID;
            /* Mask off reserved bits for high address space */
            blkSel->highBlkSel &= FLS_SEL_MASK_HIGH;
            /* Mask off reserved bits for first 256K address space */
            blkSel->first256KBlkSel &= FLS_SEL_MASK_FIR256K;
            /* Mask off reserved bits for second 256K address space */
            blkSel->second256KBlkSel &= FLS_SEL_MASK_SEC256K;

            /* No blocks to be selected for erase, just return */
            if ((blkSel->lowBlkSel | blkSel->midBlkSel | blkSel->highBlkSel |
                  blkSel->first256KBlkSel | blkSel->second256KBlkSel) == 0U) /* PRQA S 2992, 2996 */
            {
                /* Return with STATUS_SUCCESS */
                FLS_FMC.MCR.B.ERS = 0U;
            }
            else
            {
                /* Set the block selection registers */
                FLS_FMC.SEL0.B.LOWSEL = blkSel->lowBlkSel;
                FLS_FMC.SEL0.B.MIDSEL = blkSel->midBlkSel;
                FLS_FMC.SEL1.R = blkSel->highBlkSel;
                /* If Swapped to B partition */
                if (1U == g_swapStatus)
                {
                    FLS_FMC.SEL2.R = (((blkSel->first256KBlkSel >> 8U) & 0x000000FFU) | ((blkSel->first256KBlkSel << 8U) & 0x0000FF00U)); /* PRQA S 2985 */
                }
                else
                {
                    FLS_FMC.SEL2.R = blkSel->first256KBlkSel;
                }
                FLS_FMC.SEL3.R = blkSel->second256KBlkSel;
            }

            /* Check if ERS bit is set */
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                /* Interlock write */
                *((volatile uint32_t*)interlockWriteAddress) = 0xFFFFFFFFU;
                /* Write a 1 to MCR_EHV */
                if (FLS_OP_SYNC == mode)
                {
//                    INTC_LLD_Set_Global_Disable();
//                    FLS_AcCodePtr();
//                    INTC_LLD_Set_Global_Enable();
                }
                else
                {
                    FLS_FMC.MCR.B.EHV = 1U;
                }
                /* Not wait until MCR_DONE is set */
            }
        }
    }

    return ret;
}


/*
 * @brief Program operation for flash
 *
 * This function is to do program operation for flash.
 *
 * @param[in] pCtxData: Storing context variables.
 * @return Operation status
 */
status_t FLASH_LLD_Program(fls_ctx_data_t * pCtxData)
{
    status_t ret = STATUS_SUCCESS;

    if ( (pCtxData == NULL) || ((pCtxData->dest % FLS_DWORD_SIZE) != 0U) || ((pCtxData->size % FLS_WORD_SIZE) != 0U) )
    {
        ret = STATUS_ERROR;
        return ret;
    }

    if (((FLS_FMC.MCR.B.PGM != 0U) && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.PSUS != 0U))) ||
         ((FLS_FMC.MCR.B.ERS != 0U) && (FLS_FMC.MCR.B.ESUS == 0U)))
    {
        /*
         * Return busy: program in progress, program in suspended, erase in progress
         * */
        ret = STATUS_BUSY;
    }
    else
    {
        /*
         * Do program: no program and erase, erase_suspend and EHV is low
         * */
        ret = FLS_LLD_PgmExec(pCtxData);
    }

    return ret;
}

/*
 * @brief Perform a sum over the specified flash
 *
 * This function perform a sum(32 bit) over the specified flash without carry.
 *
 * @param[in] dest: Destination address to the specified flash memory.(4 bytes aligned)
 * @param[in] size: Size in bytes of the flash region to check sum.(4 bytes aligned)
 * @param[in] checkWordSize: The number of word need to calculate sum in each cycle.
 * @param[out] pSum: Return the sum value.
 * @return Operation status
 */
status_t FLASH_LLD_CheckSum(uint32_t dest,
                            uint32_t size,
                            uint32_t checkWordSize,
                            uint32_t *pSum)
{
    uint32_t destIndex = 0U;
    uint32_t temp = 0U;
    uint32_t destTmp = dest;
    uint32_t sizeTmp = size;

    if ( ((destTmp | sizeTmp) % FLS_WORD_SIZE) != 0U )
    {
        return STATUS_ERROR;
    }

    /* Initialize the sum variable */
    *pSum = 0U;

    while (sizeTmp != 0U)
    {
        /* Number of words needs to be checked sum */
        temp = sizeTmp / FLS_WORD_SIZE;

        /* In each check sum cycle, we take up to a certain words */
        if (temp >= checkWordSize)
        {
            temp = checkWordSize;
        }

        /* Word by word checksum */
        for (destIndex = 0U; destIndex < temp; destIndex++)
        {
            *pSum += *(volatile uint32_t *)destTmp;
            destTmp += FLS_WORD_SIZE;
            sizeTmp -= FLS_WORD_SIZE;
        }
    }

    return STATUS_SUCCESS;
}

/*
 * @brief Suspend a flash operation
 *
 * This function will suspend a flash operation which is in progress.
 *
 * @param[out] susStatus: Return suspend state after call this function.
 * @return Operation status
 */
status_t FLASH_LLD_Suspend(uint8_t * susStatus)
{
    uint32_t count = 450U;

    if ( susStatus == NULL)
    {
        return STATUS_ERROR;
    }

    *susStatus = FLS_NO_SUS;

    /* No program/erase sequence */
    if ((FLS_FMC.MCR.B.PGM == 0U) && (FLS_FMC.MCR.B.ERS == 0U))
    {
        /* Nothing to do */
    }
    else
    {
        if (((FLS_FMC.MCR.B.PGM != 0U) && (FLS_FMC.MCR.B.PSUS == 0U)) ||
             ((FLS_FMC.MCR.B.ERS != 0U) && (FLS_FMC.MCR.B.ESUS == 0U)))
        {
            FLS_LLD_SusExec(susStatus);
        }

        /* Check the high voltage is cleared or not */
        if ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U))
        {
            if (FLS_FMC.MCR.B.PSUS != 0U)
            {
                *susStatus = FLS_PGM_SUS;

                if (FLS_FMC.MCR.B.ESUS != 0U)
                {
                    *susStatus = FLS_ERS_SUS_PGM_SUS;
                }
            }
            else
            {
                *susStatus = FLS_ERS_SUS;
            }

            /* Wait MCR DONE bit is set */
            while ((FLS_FMC.MCR.B.DONE == 0U) && (count > 0U))
            {
                count--;
            }

            /* Set MCR_EHV to 0 */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
    }

    return STATUS_SUCCESS;
}

/*
 * @brief Resume the suspended flash operation
 *
 * This function will resume the suspended flash operation.
 *
 * @param[out] resStatus: Return resume state after call this function.
 * @return Operation status
 */
status_t FLASH_LLD_Resume(uint8_t * resStatus)
{
    uint32_t bitMask = 0U;                       /* PSUS or ESUS bit to be cleared */
    uint32_t count = 0U;                         /* the loop count for the wait loop */

    if ( resStatus == NULL)
    {
        return STATUS_ERROR;
    }

    *resStatus = FLS_RES_NOTHING;

    /* Resume the operation according to the interface selection */
    count = 15U;

    /* Program in suspend state or entering suspend state */
    if (FLS_FMC.MCR.B.PSUS != 0U)
    {
        *resStatus = FLS_RES_PGM;
        bitMask = 0x1U;

        if (FLS_FMC.MCR.B.ESUS != 0U)
        {
            /* Erase-suspended program is suspended */
            *resStatus = FLS_RES_ERS_PGM;
        }
    }
    else
    {
        /* Erase in suspend state or entering suspend state */
        if ((FLS_FMC.MCR.B.ESUS != 0U) && (FLS_FMC.MCR.B.PGM == 0U))
        {
            *resStatus = FLS_RES_ERS;
            bitMask = 0x2U;
        }
        else
        {
            /* No suspended operation */
        }
    }

    if (*resStatus != FLS_RES_NOTHING)
    {
        /* Set MCR_EHV bit */
        FLS_FMC.MCR.B.EHV = 1U;

        /* Clear the MCR_PSUS bit */
        if (bitMask == 0x1U)
        {
            FLS_FMC.MCR.B.PSUS = 0U;
        }

        /* Clear the MCR_ESUS bit */
        if (bitMask == 0x2U)
        {
            FLS_FMC.MCR.B.ESUS = 0U;
        }

        /* Wait the MCR_DONE bit goes low */
        while ((FLS_FMC.MCR.B.DONE != 0U) && (count > 0U))
        {
            count--;
        }
    }

    return STATUS_SUCCESS;
}


/*
 * @brief Get the over-program protection status
 *
 * This function will return the over-program protection status.
 *
 * @param[in] flsBlk: Select the special flash block to get over-program protection status.
 * @param[out] protStatus: Return bit map for over-program protection status.
 * @return Operation status
 */
status_t FLASH_LLD_GetOverPgmProtStatus(uint8_t flsBlk,
                                        uint32_t * protStatus)
{
    status_t ret = STATUS_SUCCESS;

    /* Determine which address space is selected */
    switch (flsBlk)
    {
        case FLS_BLK_LOW:
            *protStatus = (FLS_FMC.OPP0.B.LOWOPP & FLS_SEL_MASK_LOW);
            break;
        case FLS_BLK_MID:
            *protStatus = (FLS_FMC.OPP0.B.MIDOPP & FLS_SEL_MASK_MID);
            break;
        case FLS_BLK_HIGH:
            *protStatus = (FLS_FMC.OPP1.B.HIGHOPP & FLS_SEL_MASK_HIGH);
            break;
        case FLS_BLK_FIRST_256K:
            *protStatus = (FLS_FMC.OPP2.B.A256KOPP & FLS_SEL_MASK_FIR256K);
            break;
        case FLS_BLK_SECOND_256K:
            *protStatus = (FLS_FMC.OPP3.R & FLS_SEL_MASK_SEC256K);
            break;
        default:
            ret = STATUS_ERROR;
            break;
    }

    return ret;
}

/*
 * @brief Enable flash command complete interrupt.
 *
 * This function will enable flash command complete interrupt.
 */
void FLASH_LLD_EnableCmdCompleteInterupt(void)
{
    /* Enable the command complete interrupt */
    FLS_FMC.MCR.B.PECIE = 1U;
}

/*
 * @brief Disable flash command complete interrupt.
 *
 * This function will disable flash command complete interrupt.
 *
 */
void FLASH_LLD_DisableCmdCompleteInterupt(void)
{
    /* Disable the command complete interrupt */
    FLS_FMC.MCR.B.PECIE = 0U;
}

/*
 * @brief Flash command complete interrupt handle function.
 *
 * The interrupt handle function for flash command complete interrupt.
 *
 */
void FLASH_Cmd_Done_ISR(void)
{
    FLS_FMC.MCR.B.PECIE = 0U;
    if (FLS_FMC.MCR.B.EHV != 0U)
    {
        FLS_FMC.MCR.B.EHV = 0U;
        FLS_EHV_Val = 1U;
    }
    else
    {
        FLS_EHV_Val = 0U;
    }
}

/*
 * @brief Disable flash cache
 *
 * This function used to disable flash cache.
 *
 * @param[in] port: Select flash port to disable cache.
 * @param[out] originValue: Return the original value of PFCR.
 * @return Operation status
 */
status_t FLASH_LLD_DisableCache(uint8_t port, uint32_t *originValue)
{
    status_t ret = STATUS_SUCCESS;

    if (port > FLS_PORT2)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    if (FLS_PORT1 == port)
    {
        /* Read the values of the register of flash configuration */
        *originValue = PFLASH.PFCR1.R;

        /* Disable Caches */
        PFLASH.PFCR1.B.P0_BFEN = 0U;
    }
    else
    {
        /* Read the values of the register of flash configuration */
        *originValue = PFLASH.PFCR2.R;

        /* Disable Caches */
        PFLASH.PFCR2.B.P1_BFEN = 0U;
    }

    return ret;
}

/*
 * @brief Restore flash cache
 *
 * This function will restore configuration register.
 *
 * @param[in] port: Select flash port to restore.
 * @param[in] originValue: The original value of PFCR.
 * @return Operation status
 */
status_t FLASH_LLD_RestoreCache(uint8_t port, uint32_t originValue)
{
    status_t ret = STATUS_SUCCESS;

    if (port > FLS_PORT2)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    if (FLS_PORT1 == port)
    {
        /* Restore configuration register of flash configuration */
        PFLASH.PFCR1.R = originValue;
    }
    else
    {
        /* Restore configuration register of flash configuration */
        PFLASH.PFCR2.R = originValue;
    }

    return ret;
}

/*
 * @brief Enable Flash Calibration Region Descriptor
 *
 * This function will Enable flash calibration region descriptor.
 *
 * @param[in] cdrIndex: The Index of Calibration Remap Descriptor.
 * @param[in] remapConfig: The config of Calibration Region Descriptor.
 * @return Operation status
 */
status_t FLASH_LLD_Overlay_Config_Enable(uint32_t cdrIndex, flash_remap_config_t *remapConfig) /* PRQA S 3673 */
{
    status_t ret = STATUS_SUCCESS;

#if PFLASH_Safe_Calibration
    /* check flash region count */
    if (cdrIndex >= PFLASH_PFCRD_SAFE_COUNT)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    ret = FLS_LLD_OverlayConfig(cdrIndex, remapConfig);
    ret = FLS_LLD_OverlayConfig((cdrIndex+PFLASH_PFCRD_SAFE_COUNT), remapConfig);
#else
    /* check flash region count */
    if (cdrIndex >= PFLASH_PFCRD_COUNT)
    {
        ret = STATUS_ERROR;
        return ret;
    }

    ret = FLS_LLD_OverlayConfig(cdrIndex, remapConfig);
#endif

    return ret;
}

/*
 * @brief Disable Flash Calibration Region Descriptor
 *
 * This function will disable flash calibration region descriptor.
 *
 * @return Operation status
 */
status_t FLASH_LLD_Overlay_Config_Disable(uint32_t cdrIndex)
{
    status_t ret = STATUS_SUCCESS;

    /* check flash region count */
#if PFLASH_Safe_Calibration
    if (cdrIndex >= PFLASH_PFCRD_SAFE_COUNT)
    {
        ret = STATUS_ERROR;
        return ret;
    }
    /* disable the corresponding Calibration Remap Descriptor */
    PFLASH.PFCRDE.R &= (~(uint32_t)(1UL<<(31U-cdrIndex)))&0xFFFFFFFFU; /* PRQA S 2985 */
    PFLASH.PFCRDE.R &= (~(uint32_t)(1UL<<(31U-(cdrIndex+PFLASH_PFCRD_SAFE_COUNT))))&0xFFFFFFFFU; /* PRQA S 2985 */
#else
    if (cdrIndex >= PFLASH_PFCRD_COUNT)
    {
        ret = STATUS_ERROR;
        return ret;
    }
    /* disable the corresponding Calibration Remap Descriptor */
    PFLASH.PFCRDE.R &= (~(uint32_t)(1UL<<(31U-cdrIndex)))&0xFFFFFFFFU; /* PRQA S 2985 */
#endif

    return STATUS_SUCCESS;
}

/*
 * @brief Enable Flash Global Calibration remap
 *
 * This function will enable flash global calibration remap.
 *
 * @return Operation status
 */
status_t FLASH_LLD_Overlay_Golbal_Enable(void)
{
    /* enable the global Calibration remap */
#if PFLASH_Safe_Calibration
    PFLASH.PFCRCR.B.SAFE_CAL = 1U;
#else
    PFLASH.PFCRCR.B.SAFE_CAL = 0U;
#endif

    PFLASH.PFCRCR.B.GRMEN = 1U;

    return STATUS_SUCCESS;
}

/*
 * @brief Disable Flash Global Calibration remap
 *
 * This function will disable flash global calibration remap.
 *
 * @return Operation status
 */
status_t FLASH_LLD_Overlay_Golbal_Disable(void)
{
    /* disable the global Calibration remap */
    PFLASH.PFCRCR.B.GRMEN = 0U;

    return STATUS_SUCCESS;
}

/*
 * @brief Erase the selected flash block
 *
 * This function is to do erase operation for selected flash block.
 *
 * @param[in] lowSel: Select bits for low block.
 * @param[in] midSel: Select bits for mid block.
 * @param[in] highSel: Select bits for high block.
 * @param[in] first256KSel: Select bits for first of 256K block.
 * @param[in] second256KSel: Select bits for second of 256K block.
 * @param[in] swapStatus: Flash Swap Status.
 * @return Operation status
 */
uint32_t FLASH_Erase(uint32_t lowSel, uint32_t midSel, uint32_t highSel, uint32_t first256KSel, uint32_t second256KSel, uint8_t swapStatus)
{
	uint32_t ret = 0x000U;
    uint32_t interlockWriteAddress = 0x00800000U;

    if ((FLS_FMC.MCR.B.PGM != 0U) || ((FLS_FMC.MCR.B.ERS != 0U) && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.ESUS != 0U))))
    {
        ret = 0x002U;
    }
    else
    {
        /* Set MCR_ERS to start erase operation */
        FLS_FMC.MCR.B.ERS = 1U;

        if (FLS_FMC.MCR.B.ERS == 0U)
        {
            ret = 0x901U;
        }
        else
        {
            /* Correct the block selection for the case we erase Main array */

            /* Mask off reserved bits for low address space */
        	lowSel &= FLS_SEL_MASK_LOW;
            /* Mask off reserved bits for mid address space */
        	midSel &= FLS_SEL_MASK_MID;
            /* Mask off reserved bits for high address space */
            highSel &= FLS_SEL_MASK_HIGH;
            /* Mask off reserved bits for first 256K address space */
            first256KSel &= FLS_SEL_MASK_FIR256K;
            /* Mask off reserved bits for second 256K address space */
            second256KSel &= FLS_SEL_MASK_SEC256K;

            /* No blocks to be selected for erase, just return */
            if ((lowSel | midSel | highSel |
            		first256KSel | second256KSel) == 0U) /* PRQA S 2992, 2996 */
            {
                /* Return with STATUS_SUCCESS */
                FLS_FMC.MCR.B.ERS = 0U;
            }
            else
            {
                /* Set the block selection registers */
                FLS_FMC.SEL0.B.LOWSEL = lowSel;
                FLS_FMC.SEL0.B.MIDSEL = midSel;
                FLS_FMC.SEL1.R = highSel;
                /* If Swapped to B partition */
                if (1U == swapStatus)
                {
                    FLS_FMC.SEL2.R = (((first256KSel >> 8U) & 0x000000FFU) | ((first256KSel << 8U) & 0x0000FF00U)); /* PRQA S 2985 */
                }
                else
                {
                    FLS_FMC.SEL2.R = first256KSel;
                }
                FLS_FMC.SEL3.R = second256KSel;
            }

            /* Check if ERS bit is set */
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                /* Interlock write */
                *((volatile uint32_t*)interlockWriteAddress) = 0xFFFFFFFFU;

                /* Write a 1 to MCR_EHV */
                FLS_FMC.MCR.B.EHV = 1U;

                /* Wait MCR DONE bit is set */
                while (FLS_FMC.MCR.B.DONE == 0x0U)
                {
                }

                /* Clear EHV */
                FLS_FMC.MCR.B.EHV = 0U;
                /* Clear ERS */
                FLS_FMC.MCR.B.ERS = 0U;
            }
        }
    }

    return ret;
}

/*
 * @brief Program operation for flash
 *
 * This function is to do program operation for flash.
 *
 * @param[in] dest: Destination address for flash operate.
 * @param[in] src: Source address for flash operate.
 * @param[in] size: Size of the flash operate.
 * @return Operation status
 */
uint32_t FLASH_Program(uint32_t dest, uint32_t src, uint32_t size)
{
	uint32_t ret = 0x000U;
    uint32_t srcIndex = 0U;
    uint32_t temp;
	uint32_t destVal = dest;
	uint32_t srcVal = src;
	uint32_t sizeVal = size;

    if ( ((destVal % FLS_DWORD_SIZE) != 0U) || ((sizeVal % FLS_WORD_SIZE) != 0U) )
    {
        ret = 0x001U;
        return ret;
    }

    if (((FLS_FMC.MCR.B.PGM != 0U) && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.PSUS != 0U))) ||
         ((FLS_FMC.MCR.B.ERS != 0U) && (FLS_FMC.MCR.B.ESUS == 0U)))
    {
        /*
         * Return busy: program in progress, program in suspended, erase in progress
         * */
        ret = 0x002U;
    }
    else
    {
        /*
         * Do program: no program and erase, erase_suspend and EHV is low
         * */
        if (0U != sizeVal)
        {
            /* Set MCR_PGM to start program operation */
            FLS_FMC.MCR.B.PGM = 1U;

            if (FLS_FMC.MCR.B.PGM == 0U)
            {
                ret = 0x901U;
            }
            else
            {
            	while (sizeVal != 0x0U)
            	{
					/* Compute the buffer size used in the program cycle and calculate number of word for interlock write */
					if (sizeVal > FLS_PROGRAMABLE_SIZE)
					{
						temp = FLS_PROGRAMABLE_SIZE / FLS_WORD_SIZE;
					}
					else
					{
						temp = sizeVal / FLS_WORD_SIZE;
					}

					/* Program data */
					for (srcIndex = 0U; srcIndex < temp; srcIndex++)
					{
						/* Programming write */
						*(volatile uint32_t *)(destVal) = *(volatile uint32_t *)(srcVal);
						/* Update dest, size, source index */
						destVal += FLS_WORD_SIZE;
						srcVal += FLS_WORD_SIZE;
						sizeVal -= FLS_WORD_SIZE;

						/* Is it time to do page programming?  */
						if (0U == (destVal % FLS_PROGRAMABLE_SIZE))
						{
							break;
						}
					}

					/* Set MCR EHV bit, start operation */
					FLS_FMC.MCR.B.EHV = 1U;

					/* Wait MCR DONE bit is set */
					while (FLS_FMC.MCR.B.DONE == 0x0U)
					{
					}

					/* Clear EHV */
					FLS_FMC.MCR.B.EHV = 0U;
            	}
                /* Clear PGM */
                FLS_FMC.MCR.B.PGM = 0U;
            }
        }
        else
        {
        }
    }

    return ret;
}








