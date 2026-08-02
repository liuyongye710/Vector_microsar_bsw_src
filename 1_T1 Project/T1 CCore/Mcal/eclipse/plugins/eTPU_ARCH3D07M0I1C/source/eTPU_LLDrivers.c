/**************************************************************************** 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    eTPU_LLDriver.c
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eTPU MCAL driver.
*
*   @addtogroup eTPU
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "eTPU_LLDrivers.h"

etpu_instance_t eTPUInstance[2] =
{
    /* ETPU A && ETPU B */
    {(eTPU_Type *)0xFFDC0000U, 0xFFDD0000U, 0xFFDC8000U, 0xFFDCBFFFU, 0xFFDCC000U, (uint32 *)0, 1},
    /* ETPU C */
    {(eTPU_Type *)0xFBF80000U, 0xFBF90000U, 0xFBF88000U, 0xFBF8BFFFU, 0xFBF8C000U, (uint32 *)0, 0},
};

/*
 * @brief This function initializes the eTPU module.
 *
 * This function does not configure the pins, only the eTPU.
 *
 * @param[in] p_etpu_config : This is the structure used to initialize the eTPU
 * @param[in] *code : This is a pointer to an image of the eTPU code.
 * @param[in] code_size : This is the size of the eTPU code in bytes.
 * @param[in] *globals : This is a pointer to the global eTPU data that needs to be initialized.
 * @param[in] globals_size : This is the size of the global data in bytes.
 * @return
 */
FUNC(status_t, ETPU_CODE)ETPU_LLD_Init \
( \
    VAR(uint8, AUTOMATIC) etpuGroup, \
    P2CONST(etpu_global_param_t, AUTOMATIC, ETPU_APPL_CONST) p_etpu_config, \
    P2CONST(uint32, AUTOMATIC, ETPU_APPL_CONST) code, \
    VAR(uint32, AUTOMATIC) code_size, \
    P2CONST(uint32, AUTOMATIC, ETPU_APPL_CONST) globals, \
    VAR(uint32, AUTOMATIC) globals_size
)
{
    status_t ret = STATUS_SUCCESS;
    uint32 *code_end;
    sint32 unused_code_ram;
    sint8 x;

    unused_code_ram = (((sint32)eTPUInstance[etpuGroup].eTPU->MCR.B.SCMSIZE + 1 ) * 2048) - (sint32)code_size;
    if(unused_code_ram < 0)
    {
        ret = STATUS_ETPU_WRONG_CODE_SIZE;
    }

    /* 1. Load microcode */
    /* In order for the MISC function to work with code that is small than
    * the code memory any unused locations must be set to zero. */
    if (ret == STATUS_SUCCESS)
    {
        eTPUInstance[etpuGroup].eTPU->ECR_A.B.MDIS = 1;    /* stop eTPU_A */
        eTPUInstance[etpuGroup].eTPU->ECR_B.B.MDIS = 1;    /* stop eTPU_B */
        eTPUInstance[etpuGroup].eTPU->MCR.B.VIS = 1;       /* enable CPU writes to eTPU code memory */

        x = 0;
        while(x < 5)
        {
            if(eTPUInstance[etpuGroup].eTPU->MCR.B.VIS == 1U)
            {
                break;
            }
            x++;
        }
        if(x > 4)
        {
            ret = STATUS_TIMEOUT;
        }
    }

    if (ret == STATUS_SUCCESS)
    {
        /* Copy microcode */
        code_end = (uint32*)ETPU_LLD_MemCopy_32((uint32 *)(eTPUInstance[etpuGroup].code_start), code, code_size);    /*PRQA S 0310,3305,0563 */

        /* Clear rest of program memory */
        ETPU_LLD_MemSet_32(code_end, 0, (uint32)unused_code_ram);

        eTPUInstance[etpuGroup].eTPU->MCR.B.VIS = 0;    /* disable CPU writes to eTPU code memory */

        /* Configure MISC */
        eTPUInstance[etpuGroup].eTPU->MISCCMPR.R = p_etpu_config->misc; /*write MISC value before enabled in MCR */
        eTPUInstance[etpuGroup].eTPU->MCR.R = p_etpu_config->mcr;

        /* Configure Engine 1 */
        eTPUInstance[etpuGroup].eTPU->ECR_A.R = p_etpu_config->ecr_a;
        if(eTPUInstance[etpuGroup].eTPU->ECR_A.B.MDIS == 0U)
        {
            eTPUInstance[etpuGroup].eTPU->TBCR_A.R = p_etpu_config->tbcr_a;
            eTPUInstance[etpuGroup].eTPU->REDCR_A.R = p_etpu_config->stacr_a;
        }

        /* Configure Engine 2 */
        /* Not all parts have a second eTPU engine, if yes, these write are ignored. */
        eTPUInstance[etpuGroup].eTPU->ECR_B.R = p_etpu_config->ecr_b;
        if(eTPUInstance[etpuGroup].eTPU->ECR_B.B.MDIS == 0U)
        {
            eTPUInstance[etpuGroup].eTPU->TBCR_B.R = p_etpu_config->tbcr_b;
            eTPUInstance[etpuGroup].eTPU->REDCR_B.R = p_etpu_config->stacr_b;
        }

        /* 3. Copy initial global values to parameter RAM. */
        eTPUInstance[etpuGroup].free_param = (uint32*)ETPU_LLD_MemCopy_32((uint32 *)eTPUInstance[etpuGroup].data_ram_start, (uint32 const *)globals, globals_size);    /*PRQA S 0310,3305,0563 */
        eTPUInstance[etpuGroup].free_param = (uint32*)((((uint32)eTPUInstance[etpuGroup].free_param + 7U) >> 3) << 3); /* round up to 8s */
    }

    ETPU_LLD_TimerStart(etpuGroup); /*start timebases*/

    return ret;
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_TimerStart
****************************************************************************//*!
* @brief   This function starts the timebases.
*
* @note    This functions synchronously starts the timebases of all timer
*          modules on a device.
*
* @param   channel - The eTPU channel number
*******************************************************************************/
FUNC(void, ETPU_CODE) ETPU_LLD_TimerStart \
( \
    VAR(uint8, AUTOMATIC) etpuGroup
)
{
    eTPUInstance[etpuGroup].eTPU->MCR.B.GTBE = 1;
    eTPUInstance[etpuGroup].eTPU->MCR.B.VIS = 0;
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_Malloc_32
****************************************************************************//*!
* @brief   This function allocates DATA RAM (parameter RAM) for a channel.
*
* @param   num_bytes - this is the number of bytes that is required to
*          allocate in DATA RAM.
*
* @return  A pointer to allocated DATA RAM. If the requested amount of memory
*          is larger than the available amount of memory then 0 is returned.
*
* @warning This function is non-reentrant and uses the @ref fs_free_param global.
*          The granularity of eTPU DATA RAM allocation for channel parameters
*          is 8 bytes. The requested size is enlarged to a multiple of 8 bytes.
*******************************************************************************/
uint32 *ETPU_LLD_Malloc_32(uint8 etpuGroup,
                          uint16 num_bytes)
{
    uint32 *pba;

    pba = eTPUInstance[etpuGroup].free_param;
    eTPUInstance[etpuGroup].free_param += (((num_bytes + 7U) >> 3U) << 1U);

    if(eTPUInstance[etpuGroup].free_param > (uint32 *)eTPUInstance[etpuGroup].data_ram_end)
    {
        return NULL_PTR;
    }
    else
    {
        return (pba);
    }
}

uint32 *ETPU_LLD_Malloc2(uint8 etpuGroup,
                           uint8 channel,
                          uint16 num_bytes)
{
    uint32 *pba;

    if(eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA == 0)  /*PRQA S 1863 */
    {
        pba = eTPUInstance[etpuGroup].free_param;
        eTPUInstance[etpuGroup].free_param += (((num_bytes+7)>>3)<<1);        /*PRQA S 1860 */
        if(eTPUInstance[etpuGroup].free_param > (uint32 *)eTPUInstance[etpuGroup].data_ram_end)
        {
            return (NULL_PTR);
        }
        else
        {
            return (pba);
        }
    }
    else
    {
        return (ETPU_LLD_GetDataRam(etpuGroup, channel));
    }
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_MemCopy_32
****************************************************************************//*!
* @brief   This function is similar to the standard C memset() function
*          however it sets 32-bit words rather than bytes.
*
* @param   *dest - The pointer to the destination location
* @param   *source - The pointer to the source location
* @param   size - The size of the data to copy in bytes
*
* @return  A pointer to the end of the copied data.
*
* @warning The *dest and *source pointers should be aligned to a 32-bit
*          address. If they are not it may cause memory exceptions. Moving
*          data to the eTPU code memory that is not 32-bit aligned is
*          undefined. The size should be a multiple of 4. If it is not
*          it is rounded down.
*******************************************************************************/
uint8 *ETPU_LLD_MemCopy_32(uint32 *dest,
                            uint32 const *source,
                            uint32 size)
{
    uint8 *p = (uint8 *)dest;
    uint8 const *q = (uint8 const *)source;
    uint32 size_l = size;

    while(size_l != 0U)
    {
        *p = *q;
        p++;
        q++;
        size_l--;
    }

    return p;
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_MemSet_32
****************************************************************************//*!
* @brief   This function is similar to the standard C memcpy() function
*          however it copies 32-bit words rather than bytes.
*
* @param   *start - The pointer to the start location
* @param   *value - The value to write to memory
* @param   size - The size of the data to set in bytes
*
* @warning The *start pointers should be aligned to a 32-bit address.
*          If it is not it may cause memory exceptions. Writing
*          data to the eTPU code memory that is not 32-bit aligned is
*          undefined. The size should be a multiple of 4. If it is not
*          it is rounded down.
*******************************************************************************/
FUNC(uint8, ETPU_CODE) ETPU_LLD_MemSet_32 \
( \
    P2VAR( uint32, AUTOMATIC, ETPU_APPL_DATA ) start, \
    VAR( uint32, AUTOMATIC ) value, \
    VAR( uint32, AUTOMATIC ) size
)
{
    uint32 *p = start;
    uint32 size_l = size;

    size_l = size_l >> 2U;

    while(size_l != 0U)
    {
        *p = value;
        p++;
        size_l--;
    }
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_CoherentRead24
****************************************************************************//*!
* @brief   This function coherently reads two 24-bit variables from the eTPU
*          DATA RAM, using the Coherent Dual-Parameter Controller (CDC).
*
* @param   channel - The eTPU channel number
* @param   offset1 - The offset to the first 24-bit variable to be read
* @param   offset2 - The offset to the second 24-bit variable to be read
* @param   *value1 - A pointer to where the first variable value will be stored
* @param   *value2 - A pointer to where the second variable value will be stored
*
* @return  Zero or an error code. Error codes that can be returned are:
*          - @ref ETPU_ERROR_MALLOC - When there is not enough available
*            memory for the temporally buffer in eTPU DATA RAM
*          - @ref ETPU_ERROR_ADDRESS - When the variable offsets do not allow
*            the CDC operation.
*******************************************************************************/
FUNC(uint32, ETPU_CODE) ETPU_LLD_CoherentRead24 \
( \
    VAR(uint8, AUTOMATIC) etpuGroup, \
    VAR(uint8, AUTOMATIC) channel, \
    VAR(uint32, AUTOMATIC) offset1, \
    VAR(uint32, AUTOMATIC) offset2, \
    P2VAR(uint32, AUTOMATIC, ETPU_APPL_DATA) value1, \
    P2VAR(uint32, AUTOMATIC, ETPU_APPL_DATA) value2
)
{
    uint32 addr1, addr2, ctbase1, ctbase2;
    uint32 addr_b;
    uint32 err_code = 0;

    /* check there is a DATA RAM space for the temporally buffer */
    if (((uint32)eTPUInstance[etpuGroup].free_param + 8U) > eTPUInstance[etpuGroup].data_ram_end)
    {
        err_code = ETPU_ERROR_MALLOC;
    }
    else
    {
        /* SDM-relative word addresses of parameters (4 byte granularity) */
        addr1 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset1 - 1U) >> 2;
        addr2 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset2 - 1U) >> 2;
        ctbase1 = addr1 >> 7;
        ctbase2 = addr2 >> 7;

        if(ctbase1 != ctbase2)
        {
            err_code = ETPU_ERROR_ADDRESS;
        }
        else
        {
            /* SDM-relative doubleword address of buffer (8 byte granularity) */
            addr_b = ((uint32)eTPUInstance[etpuGroup].free_param - eTPUInstance[etpuGroup].data_ram_start) >> 3;

            eTPUInstance[etpuGroup].eTPU->CDCR.R = ((uint32)1U << 31U) + (ctbase1 << 26U) + (addr_b << 16U) \
                            + ((addr1 & 0x7FU) << 8U) + (addr2 & 0x7FU);

            /* now host receives wait states untill the transfer is done */

            /* read values from temporary buffer */
            *value1 = ((uint32)(*( eTPUInstance[etpuGroup].free_param))<<8U)>>8U;
            *value2 = ((*(eTPUInstance[etpuGroup].free_param + 1))<<8)>>8;
        }
    }

    return (err_code);
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_CoherentRead32
****************************************************************************//*!
* @brief   This function coherently reads two 32-bit variables from the eTPU
*          DATA RAM, using the Coherent Dual-Parameter Controller (CDC).
*
* @param   channel - The eTPU channel number
* @param   offset1 - The offset to the first 32-bit variable to be read
* @param   offset2 - The offset to the second 32-bit variable to be read
* @param   *value1 - A pointer to where the first variable value will be stored
* @param   *value2 - A pointer to where the second variable value will be stored
*
* @return  Zero or an error code. Error codes that can be returned are:
*          - @ref ETPU_ERROR_MALLOC - When there is not enough available
*            memory for the temporally buffer in eTPU DATA RAM
*          - @ref ETPU_ERROR_ADDRESS - When the variable offsets do not allow
*            the CDC operation.
*******************************************************************************/
FUNC(uint32, ETPU_CODE) ETPU_LLD_CoherentRead32 \
( \
    VAR(uint8, AUTOMATIC) etpuGroup, \
    VAR(uint8, AUTOMATIC) channel, \
    VAR(uint32, AUTOMATIC) offset1, \
    VAR(uint32, AUTOMATIC) offset2, \
    P2VAR(uint32, AUTOMATIC, ETPU_APPL_DATA) value1, \
    P2VAR(uint32, AUTOMATIC, ETPU_APPL_DATA) value2
)
{
    uint32 addr1, addr2, ctbase1, ctbase2;
    uint32 addr_b;
    uint32 err_code = 0;

    /* check there is a DATA RAM space for the temporally buffer */
    if (((uint32)eTPUInstance[etpuGroup].free_param + 8U) > eTPUInstance[etpuGroup].data_ram_end)
    {
        err_code = ETPU_ERROR_MALLOC;
    }
    else
    {
        /* SDM-relative word addresses of parameters (4 byte granularity) */
        addr1 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset1) >> 2;
        addr2 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset2) >> 2;
        ctbase1 = addr1 >> 7;
        ctbase2 = addr2 >> 7;

        if(ctbase1 != ctbase2)
        {
            err_code = ETPU_ERROR_ADDRESS;
        }
        else
        {
            /* SDM-relative doubleword address of buffer (8 byte granularity) */
            addr_b = ((uint32)eTPUInstance[etpuGroup].free_param - eTPUInstance[etpuGroup].data_ram_start) >> 3;

            eTPUInstance[etpuGroup].eTPU->CDCR.R = ((uint32)1U << 31U) + (ctbase1 << 26U) + (addr_b << 16U) + ((uint32)1U << 15U) \
                            + ((addr1 & 0x7FU) << 8U) + (addr2 & 0x7FU);

            /* now host receives wait states untill the transfer is done */

            /* read values from temporary buffer */
            *value1 = *(eTPUInstance[etpuGroup].free_param);
            *value2 = *(eTPUInstance[etpuGroup].free_param + 1);
        }
    }

    return (err_code);
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_CoherentWrite24
****************************************************************************//*!
* @brief   This function coherently writes two 24-bit variables into the eTPU
*          DATA RAM, using the Coherent Dual-Parameter Controller (CDC).
*
* @param   channel - The eTPU channel number
* @param   offset1 - The offset to the first 24-bit variable to be written
* @param   offset2 - The offset to the second 24-bit variable to be written
* @param   value1 - The first variable value
* @param   value2 - The second variable value
*
* @return  Zero or an error code. Error codes that can be returned are:
*          - @ref ETPU_ERROR_MALLOC - When there is not enough available
*            memory for the temporally buffer in eTPU DATA RAM
*          - @ref ETPU_ERROR_ADDRESS - When the variable offsets do not allow
*            the CDC operation.
*******************************************************************************/
FUNC(uint32, ETPU_CODE) ETPU_LLD_CoherentWrite24 \
( \
    VAR(uint8, AUTOMATIC) etpuGroup, \
    VAR(uint8, AUTOMATIC) channel, \
    VAR(uint32, AUTOMATIC) offset1, \
    VAR(uint32, AUTOMATIC) offset2, \
    VAR(sint32, AUTOMATIC) value1, \
    VAR(sint32, AUTOMATIC) value2
)
{
    uint32 addr1, addr2, ctbase1, ctbase2;
    uint32 addr_b;
    uint32 err_code = 0;

    /* check there is a DATA RAM space for the temporally buffer */
    if (((uint32)eTPUInstance[etpuGroup].free_param + 8U) > eTPUInstance[etpuGroup].data_ram_end)
    {
        err_code = ETPU_ERROR_MALLOC;
    }
    else
    {
        /* write values to the temporary buffer */
        *(eTPUInstance[etpuGroup].free_param) = (uint32)value1;
        *(eTPUInstance[etpuGroup].free_param + 1) = (uint32)value2;

        /* SDM-relative word addresses of parameters (4 byte granularity) */
        addr1 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset1 - 1U) >> 2;
        addr2 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset2 - 1U) >> 2;
        ctbase1 = addr1 >> 7;
        ctbase2 = addr2 >> 7;

        if(ctbase1 != ctbase2)
        {
            err_code = ETPU_ERROR_ADDRESS;
        }
        else
        {
            /* SDM-relative doubleword address of buffer (8 byte granularity) */
            addr_b = ((uint32)eTPUInstance[etpuGroup].free_param - eTPUInstance[etpuGroup].data_ram_start) >> 3;

            eTPUInstance[etpuGroup].eTPU->CDCR.R = ((uint32)1U << 31U) + (ctbase1 << 26U) + (addr_b << 16U) + (1U << 7U) \
                            + ((addr1 & 0x7FU) << 8U) + (addr2 & 0x7FU);

            /* now host receives wait states untill the transfer is done */
        }
    }

    return (err_code);
}

/*******************************************************************************
* FUNCTION: ETPU_LLD_CoherentWrite32
****************************************************************************//*!
* @brief   This function coherently writes two 32-bit variables into the eTPU
*          DATA RAM, using the Coherent Dual-Parameter Controller (CDC).
*
* @param   channel - The eTPU channel number
* @param   offset1 - The offset to the first 32-bit variable to be written
* @param   offset2 - The offset to the second 32-bit variable to be written
* @param   value1 - The first variable value
* @param   value2 - The second variable value
*
* @return  Zero or an error code. Error codes that can be returned are:
*          - @ref ETPU_ERROR_MALLOC - When there is not enough available
*            memory for the temporally buffer in eTPU DATA RAM
*          - @ref ETPU_ERROR_ADDRESS - When the variable offsets do not allow
*            the CDC operation.
*******************************************************************************/
FUNC(uint32, ETPU_CODE) ETPU_LLD_CoherentWrite32 \
( \
    VAR(uint8, AUTOMATIC) etpuGroup, \
    VAR(uint8, AUTOMATIC) channel, \
    VAR(uint32, AUTOMATIC) offset1, \
    VAR(uint32, AUTOMATIC) offset2, \
    VAR(sint32, AUTOMATIC) value1, \
    VAR(sint32, AUTOMATIC) value2
)
{
    uint32 addr1, addr2, ctbase1, ctbase2;
    uint32 addr_b;
    uint32 err_code = 0;

    /* check there is a DATA RAM space for the temporally buffer */
    if (((uint32)eTPUInstance[etpuGroup].free_param + 8U) > eTPUInstance[etpuGroup].data_ram_end)
    {
        err_code = ETPU_ERROR_MALLOC;
    }
    else
    {
        /* write values to the temporary buffer */
        *(eTPUInstance[etpuGroup].free_param) = value1;
        *(eTPUInstance[etpuGroup].free_param + 1) = value2;

        /* SDM-relative word addresses of parameters (4 byte granularity) */
        addr1 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset1) >> 2;
        addr2 = (((uint32)eTPUInstance[etpuGroup].eTPU->CHAN[channel].CR.B.CPBA << 3) + offset2) >> 2;
        ctbase1 = addr1 >> 7;
        ctbase2 = addr2 >> 7;

        if(ctbase1 != ctbase2)
        {
            err_code = ETPU_ERROR_ADDRESS;
        }
        else
        {
            /* SDM-relative doubleword address of buffer (8 byte granularity) */
            addr_b = ((uint32)eTPUInstance[etpuGroup].free_param - eTPUInstance[etpuGroup].data_ram_start) >> 3;

            eTPUInstance[etpuGroup].eTPU->CDCR.R = ((uint32)1U << 31U) + (ctbase1 << 26U) + (addr_b << 16U) + ((uint32)1U << 15U) + (1U << 7U) \
                            + ((addr1 & 0x7FU) << 8U) + (addr2 & 0x7FU);

            /* now host receives wait states untill the transfer is done */

        }
    }
    
    return (err_code);
}

#ifdef __cplusplus
}
#endif