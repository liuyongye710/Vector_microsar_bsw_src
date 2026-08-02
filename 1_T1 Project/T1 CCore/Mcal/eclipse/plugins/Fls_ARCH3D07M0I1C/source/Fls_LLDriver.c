/* PRQA S 2053, 3432, 0310 EOF */
/**************************************************************************** 
* 

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
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/
/* PRQA S 1863,1006 ,3401,3400,3397,0498 ,2934 EOF */ 
/**
*   @file    Fls_LLDriver.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of FLS MCAL driver.
*
*   @addtogroup FLS
*   @{
*/

/* PRQA S 0488, 0751, 3305 EOF */

#include "Fls_LLDriver.h" /* PRQA S 0380 */
#include "Fls.h"
#include "Det.h"

#define FLS_LLD_WRA_C_VENDOR_ID                     176
#define FLS_LLD_WRA_C_AR_REL_MAJOR_VER              4
#define FLS_LLD_WRA_C_AR_REL_MINOR_VER              4
#define FLS_LLD_WRA_C_AR_REL_REV_VER                0
#define FLS_LLD_WRA_C_SW_MAJOR_VER                  3
#define FLS_LLD_WRA_C_SW_MINOR_VER                  0
#define FLS_LLD_WRA_C_SW_PATCH_VER                  0

#if (FLS_VENDOR_ID_OUTPUT != FLS_LLD_WRA_C_VENDOR_ID)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_VENDOR_ID "
#endif
#if (FLS_AR_REL_MAJOR_VER_OUTPUT != FLS_LLD_WRA_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_AR_REL_MAJOR_VER "
#endif
#if (FLS_AR_REL_MINOR_VER_OUTPUT != FLS_LLD_WRA_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_AR_REL_MINOR_VER "
#endif
#if (FLS_AR_REL_REVISION_VER_OUTPUT != FLS_LLD_WRA_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_AR_REL_REV_VER "
#endif
#if (FLS_SW_MAJOR_VERSION_OUTPUT != FLS_LLD_WRA_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_SW_MAJOR_VER "
#endif
#if (FLS_SW_MINOR_VERSION_OUTPUT != FLS_LLD_WRA_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_SW_MINOR_VER "
#endif
#if (FLS_SW_PATCH_VERSION_OUTPUT != FLS_LLD_WRA_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : FLS_LLD_WRA_C_SW_PATCH_VER "
#endif

#define Fls_ReportRuntimeError(ApiId, ErrorId) \
        (void)Det_ReportRuntimeError( (uint16)FLS_MODULE_ID, FLS_INSTANCE, (ApiId), (ErrorId) );

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
static VAR( uint32, AUTOMATIC) FLS_EHV_Val = 0U;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

extern VAR( fls_acload_t, AUTOMATIC) pFls_AcCodePtr;

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR( uint32, AUTOMATIC) FLS_AcCodeArea[32] = {0U}; /* PRQA S 3408 */
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
static P2CONST( volatile uint8, FLS_VAR, FLS_APPL_CONST ) volatile gFls_ReadAddressPtr = NULL_PTR;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_CheckEraseStatus \
( \
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) pFls_OpRet \
);
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_Erase \
( \
    VAR( uint8, AUTOMATIC ) u8Fls_EraseSpace, \
    P2VAR( fls_blksel_t, AUTOMATIC, FLS_APPL_DATA ) pFls_BlkSel, \
    VAR( uint32, AUTOMATIC) u32Fls_Mode \
);
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*****************************************************************************
** Service Name      : Fls_LLD_CalcInitDataLength                                              
** 
** 
**  Description      : Used to calculate the number of bytes read from flash 
**                     memory until the source pointer is aligned with the data 
**                     width and the optimized wide flash memory read can start.                         
**                                                                            
**  Parameters (in)  : u8Fls_SourceAddrPtr: Source pointer
**                     u32Fls_TotalBytes: Total number of bytes read                      
**                                                                            
**  Parameters (out) : None                                                   
**                                                                            
**  Return value     : uint32: The length of the initial 8-bit flash read(in bytes)                                                  
**                                                                            
******************************************************************************/
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( uint32, FLS_CODE ) Fls_LLD_CalcInitDataLength
( 
    P2CONST( volatile uint8, AUTOMATIC, FLS_APPL_CONST ) u8Fls_SourceAddrPtr,
    CONST(uint32, AUTOMATIC) u32Fls_TotalBytes 
)
{
    VAR(uint32, AUTOMATIC) u32Fls_length = 0UL;

    u32Fls_length = ( (uint32)u8Fls_SourceAddrPtr ) & ( sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - 1UL );

    if ( u32Fls_length != 0U )
    {
        u32Fls_length = sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - u32Fls_length;
    }

    if( u32Fls_length > u32Fls_TotalBytes ) 
    {
        u32Fls_length = u32Fls_TotalBytes;
    }
    
    return u32Fls_length;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*****************************************************************************
** Service Name      : Fls_LLD_CalcWideDataLength                                              
** 
** 
**  Description      : Used to calculate the number of bytes read from flash 
**                     memory until the source pointer is misaligned with the 
**                     data bus width.                         
**                                                                            
**  Parameters (in)  : u32Fls_InitDataLength: Calculated by 
**                     Fls_LLD_CalcInitDataLength function
**                     u32Fls_TotalBytes: Total number of bytes read                      
**                                                                            
**  Parameters (out) : None                                                   
**                                                                            
**  Return value     : uint32: The length of the initial 32-bit or 64-bit 
**                             flash read(in bytes)                                                  
**                                                                            
******************************************************************************/
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( uint32, FLS_CODE ) Fls_LLD_CalcWideDataLength
(
    CONST(uint32, AUTOMATIC) u32Fls_InitDataLength,
    CONST(uint32, AUTOMATIC) u32Fls_TotalBytes 
)
{
    VAR(uint32, AUTOMATIC) u32Fls_length = 0UL;

    u32Fls_length = (( u32Fls_TotalBytes - u32Fls_InitDataLength ) & (~( sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE) - 1UL )));

    return u32Fls_length;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_Init \
( \
    P2CONST( uint8, FLS_VAR, FLS_APPL_CONST )  pFls_LockBlk \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    VAR( uint32, AUTOMATIC) u32Fls_Index = 0;

    /* unLock Flash Block*/
    FLS_FMC.LOCK0.B.LOWLOCK = 0U;
    FLS_FMC.LOCK0.B.MIDLOCK = 0U;
    FLS_FMC.LOCK1.B.HIGHLOCK = 0U;
    FLS_FMC.LOCK2.B.A256KLOCK = 0U;
    FLS_FMC.LOCK3.B.A256KLOCK = 0U;

    /* lock Flash Block*/
    for (u32Fls_Index = 0; u32Fls_Index < FLS_BLOCK_ALL; u32Fls_Index++)
    {
        if (1U == pFls_LockBlk[u32Fls_Index]) /* PRQA S 0492 */
        {
            VAR( uint8, AUTOMATIC) SelBit = (uint8)flashInfo[u32Fls_Index].lockSelBit;
            if (SelBit < 32U)
            {
	            if (0U == flashInfo[u32Fls_Index].lockSelReg)
	            {
	                FLS_FMC.LOCK0.R |= (1UL << SelBit);
	            }
	            else if (1U == flashInfo[u32Fls_Index].lockSelReg)
	            {
	                FLS_FMC.LOCK1.R |= (1UL << SelBit);
	            }
	            else if (2U == flashInfo[u32Fls_Index].lockSelReg)
	            {
	                FLS_FMC.LOCK2.R |= (1UL << SelBit);
	            }
	            else if (3U == flashInfo[u32Fls_Index].lockSelReg)
	            {
	                FLS_FMC.LOCK3.R |= (1UL << SelBit);
	            }
	            else
	            {
	                /* No operation */
				}			
			}
        }
    }

    /* Clear error bits */
    FLS_FMC.MCR.B.EER = 1U;
    FLS_FMC.MCR.B.RWE = 1U;
    FLS_FMC.MCR.B.SBC = 1U;
    FLS_FMC.MCR.B.RVE = 1U;
    FLS_FMC.MCR.B.RRE = 1U;
    FLS_FMC.MCR.B.AEE = 1U;
    FLS_FMC.MCR.B.EEE = 1U;

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#if( FLS_ERASE_VERIFICATION_ENABLED == STD_ON )
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) Fls_LLD_VerifyErase \
( \
    P2CONST(volatile uint32, AUTOMATIC, FLS_APPL_CONST ) u32Fls_FlashAreaPtr, \
	CONST( Fls_LengthType, AUTOMATIC) u32Fls_DataLength \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    P2CONST( volatile uint8, AUTOMATIC, FLS_APPL_CONST ) u8Fls_FlashAreaEndPtr = NULL_PTR;

    u8Fls_FlashAreaEndPtr = ((volatile const uint8 *)u32Fls_FlashAreaPtr) + u32Fls_DataLength;
    gFls_ReadAddressPtr = ((volatile const uint8 *)u32Fls_FlashAreaPtr);

    while( (uint32)gFls_ReadAddressPtr < (uint32)u8Fls_FlashAreaEndPtr )
    {
        if( FLS_ERASED_VALUE != *((volatile const uint32*)gFls_ReadAddressPtr) )  /*polyspace RTE:IDP,NIV*/
        {
            break;
        }   

        gFls_ReadAddressPtr += sizeof(uint32);
    }
    if( gFls_ReadAddressPtr != u8Fls_FlashAreaEndPtr )
    {
        Fls_ReportRuntimeError(FLS_MAINFUNCTION_ID, FLS_E_VERIFY_ERASE_FAILED);
        sFls_Ret = STATUS_ERROR;
    }
	if(FLS_FMC.MCR.B.EER == 1)
	{
		if(gFls_ConfigPtr->FlsRegErrorNotification != NULL_PTR)
		{
			gFls_ConfigPtr->FlsRegErrorNotification();/* polyspace RTE:COR */
		}
		FLS_FMC.MCR.B.EER = 1;
		sFls_Ret = STATUS_ERROR;
	}

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
#endif

#if( FLS_WRITE_VERIFICATION_ENABLED == STD_ON )
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) Fls_LLD_VerifyWrite \
( \
    P2CONST( volatile uint32, AUTOMATIC, FLS_APPL_CONST ) pFls_FlashAreaPtr, \
    P2CONST( uint32, AUTOMATIC, FLS_APPL_CONST ) pFls_UserBufferPtr, \
    CONST( Fls_LengthType, AUTOMATIC) u32Fls_DataLength \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    P2CONST( volatile uint8, AUTOMATIC, FLS_APPL_CONST ) u8Fls_FlashAreaEndPtr = NULL_PTR;
    P2CONST( volatile uint8, FLS_VAR, FLS_APPL_CONST ) volatile gFls_CompareAddressPtr = NULL_PTR;

    u8Fls_FlashAreaEndPtr = ((volatile const uint8 *)pFls_FlashAreaPtr) + u32Fls_DataLength;
    gFls_CompareAddressPtr = ((const uint8 *)pFls_UserBufferPtr);
    gFls_ReadAddressPtr = ((volatile const uint8 *)pFls_FlashAreaPtr);

    while( (uint32)gFls_ReadAddressPtr < (uint32)u8Fls_FlashAreaEndPtr )
    {
        if( *((volatile const uint32*)gFls_ReadAddressPtr) !=  /* polyspace RTE:IDP,NIV */
            *((volatile const uint32*)gFls_CompareAddressPtr) )  /* polyspace RTE:IDP,NIV */
        {
            break;
        }
        
        gFls_CompareAddressPtr += sizeof(uint32);
        gFls_ReadAddressPtr += sizeof(uint32);
    }

    if( gFls_ReadAddressPtr != u8Fls_FlashAreaEndPtr )
    {
        /* Specification of Flash Driver : [SWS_Fls_00314] */
        /* Specification of Flash Driver : [SWS_Fls_00056] */
        Fls_ReportRuntimeError(FLS_MAINFUNCTION_ID, FLS_E_VERIFY_WRITE_FAILED);
        sFls_Ret = STATUS_ERROR;
    }
	if(FLS_FMC.MCR.B.EER == 1)
	{
		if(gFls_ConfigPtr->FlsRegErrorNotification != NULL_PTR)
		{
			gFls_ConfigPtr->FlsRegErrorNotification();/* polyspace RTE:COR */
		}
		FLS_FMC.MCR.B.EER = 1;
		sFls_Ret = STATUS_ERROR;
	}

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
#endif

/*
 * @brief Execute suspend operation
 *
 * This function will suspend the program, erase activities
 *
 * @param[out] u8Fls_SusStatus The status of suspend after calling the function.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( void, FLS_CODE ) FLS_LLD_SusExec_Cancel \
( \
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) u8Fls_SusStatus \
)
{
    VAR( uint16, AUTOMATIC) u16Fls_SusDelay = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_Index = ABT_OPT_TIMEOUT_COUNTER;

    if (FLS_FMC.MCR.B.EHV == 0U)
    {
        if (FLS_FMC.MCR.B.PGM != 0U)
        {
            *u8Fls_SusStatus = FLS_PGM_WRITE;

            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                *u8Fls_SusStatus = FLS_ERS_SUS_PGM_WRITE;
            }
        }
        else
        {
            *u8Fls_SusStatus = FLS_ERS_WRITE;
        }
        /* Wait MCR DONE bit is set */
        while ((FLS_FMC.MCR.B.DONE == 0x0U) && (u32Fls_Index > 0U))
        {
            u32Fls_Index--;
        }
    }
    else
    {
        if (FLS_FMC.MCR.B.PGM != 0x0U)
        {
            /* Set MCR_PSUS bit */
            FLS_FMC.MCR.B.PSUS = 1U;
            for (u16Fls_SusDelay = 0U; u16Fls_SusDelay < 160U; u16Fls_SusDelay++)
            {}
        }
        else
        {
            /* Set MCR-ESUS bit */
            FLS_FMC.MCR.B.ESUS = 1U;
            for (u16Fls_SusDelay = 0U; u16Fls_SusDelay < 320U; u16Fls_SusDelay++)
            {}
        }
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#if (FLS_CANCEL_API == STD_ON )
/*****************************************************************************
** Service Name      : Fls_LLD_Cancel                                              
** 
** 
**  Description      : Used to cancel the last working operation of the driver layer.                     
**                                                                            
**  Parameters (in)  : None                       
**                                                                            
**  Parameters (out) : None                                                   
**                                                                            
**  Return value     : None                                                 
**                                                                            
******************************************************************************/
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) Fls_LLD_Cancel(P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) u8Fls_SusStatus)
{
    VAR( uint32, AUTOMATIC) u32Fls_Count = ABT_OPT_TIMEOUT_COUNTER;

    if ( u8Fls_SusStatus == NULL)
    {
        return STATUS_ERROR;
    }

    *u8Fls_SusStatus = FLS_NO_SUS;

    /* No program/erase sequence */
    if ((FLS_FMC.MCR.B.PGM == 0U) && (FLS_FMC.MCR.B.ERS == 0U))
    {
        /* Nothing to do */
    }
    else
    {
        if (((FLS_FMC.MCR.B.PGM != 0U) && (FLS_FMC.MCR.B.PSUS == 0U))\
             || ((FLS_FMC.MCR.B.ERS != 0U) && (FLS_FMC.MCR.B.ESUS == 0U)))
        {
            FLS_LLD_SusExec_Cancel(u8Fls_SusStatus);
        }

        /* Check the high voltage is cleared or not */
        if ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U))
        {
            if (FLS_FMC.MCR.B.PSUS != 0U)
            {
                *u8Fls_SusStatus = FLS_PGM_SUS;

                if (FLS_FMC.MCR.B.ESUS != 0U)
                {
                    *u8Fls_SusStatus = FLS_ERS_SUS_PGM_SUS;
                }
            }
            else
            {
                *u8Fls_SusStatus = FLS_ERS_SUS;
            }

            /* Wait MCR DONE bit is set */
            while ((FLS_FMC.MCR.B.DONE == 0U) && (u32Fls_Count > 0U))
            {
                u32Fls_Count--;
            }

            /* Set MCR_EHV to 0 */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
    }

    return STATUS_SUCCESS;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
#endif /* FLS_CANCEL_API == STD_ON */


/*
 * @brief FLS_Get_Offset_Select
 *
 * Flash get special block offset and select state.
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLS_SDK_Get_Offset_Select \
( \
    VAR( uint16, AUTOMATIC) u16Fls_FlashBlock, \
    VAR( uint32, AUTOMATIC) u32Fls_Index, \
    P2VAR( uint32, AUTOMATIC, FLS_APPL_DATA ) u32Fls_Offset, \
    P2VAR( fls_blksel_t, AUTOMATIC, FLS_APPL_DATA ) pFls_BlkSel)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;

    /* Check index */
    if (u32Fls_Index >= 32U)
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }
    else
    {
        /*
        * clear pFls_BlkSel
        *
        *  */
        pFls_BlkSel->lowBlkSel = 0x0U;
        pFls_BlkSel->midBlkSel = 0x0U;
        pFls_BlkSel->highBlkSel = 0x0U;
        pFls_BlkSel->first256KBlkSel = 0x0U;
        pFls_BlkSel->second256KBlkSel = 0x0U;

        /* Select flash block to erase */
        switch (u16Fls_FlashBlock)
        {
            case FLS_BLK_LOW:
            {
                 *u32Fls_Offset = FLS_LOW_OFFSET;
                pFls_BlkSel->lowBlkSel = (1UL << u32Fls_Index);
                break;
            }
            case FLS_BLK_MID:
            {
                *u32Fls_Offset = FLS_MID_OFFSET;
                pFls_BlkSel->midBlkSel = (1UL << u32Fls_Index);
                break;
            }
            case FLS_BLK_HIGH:
            {
                *u32Fls_Offset = FLS_HIGH_OFFSET;
                pFls_BlkSel->highBlkSel = (1UL << u32Fls_Index);
                break;
            }
            case FLS_BLK_FIRST_256K:
            {
                *u32Fls_Offset = FLS_256K_FIRST_OFFSET;
                pFls_BlkSel->first256KBlkSel = (1UL << u32Fls_Index);
                break;
            }
            case FLS_BLK_SECOND_256K:
            {
                *u32Fls_Offset = FLS_256K_SECOND_OFFSET;
                pFls_BlkSel->second256KBlkSel = (1UL << u32Fls_Index);
                break;
            }
            default:
            {
                sFls_Ret = STATUS_ERROR;
                break;
            }
        }
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( uint32, FLS_CODE ) FLS_SDK_LLD_GetInterWriteAddr(const fls_blksel_t * pFls_BlkSel)
{
    VAR( uint8, AUTOMATIC) u8Fls_Index = 0U;
    VAR( uint8, AUTOMATIC) u8Fls_Offset = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_Addr = 0U;

    if (pFls_BlkSel->lowBlkSel > 0U)
    {
        u8Fls_Offset = FLS_LOW_OFFSET;
        for (u8Fls_Index = 0U; u8Fls_Index < FLS_LOW_BLOCK; u8Fls_Index++)
        {
            if (((pFls_BlkSel->lowBlkSel & (1UL << u8Fls_Index)) >> u8Fls_Index) == 1UL)
            {
                u32Fls_Addr = flashInfo[u8Fls_Index + u8Fls_Offset].addrStart; /* PRQA S 2985 */
                break;
            }
        }
    }
    else if (pFls_BlkSel->midBlkSel > 0U)
    {
        u8Fls_Offset = FLS_MID_OFFSET;
        for (u8Fls_Index = 0U; u8Fls_Index < FLS_MID_BLOCK; u8Fls_Index++)
        {
            if (((pFls_BlkSel->midBlkSel & (1UL << u8Fls_Index)) >> u8Fls_Index) == 1UL)
            {
                u32Fls_Addr = flashInfo[u8Fls_Index + u8Fls_Offset].addrStart;
                break;
            }
        }
    }
    else if (pFls_BlkSel->highBlkSel > 0U)
    {
        u8Fls_Offset = FLS_HIGH_OFFSET;
        for (u8Fls_Index = 0U; u8Fls_Index < FLS_HIGH_BLOCK; u8Fls_Index++)
        {
            if (((pFls_BlkSel->highBlkSel & (1UL << u8Fls_Index)) >> u8Fls_Index) == 1UL)
            {
                u32Fls_Addr = flashInfo[u8Fls_Index + u8Fls_Offset].addrStart;
                break;
            }
        }
    }
    else if (pFls_BlkSel->first256KBlkSel > 0U)
    {
        u8Fls_Offset = FLS_256K_FIRST_OFFSET;
        for (u8Fls_Index = 0U; u8Fls_Index < FLS_256K_BLOCK_FIRST; u8Fls_Index++)
        {
            if (((pFls_BlkSel->first256KBlkSel & (1UL << u8Fls_Index)) >> u8Fls_Index) == 1UL)
            {
                u32Fls_Addr = flashInfo[u8Fls_Index + u8Fls_Offset].addrStart;
                break;
            }
        }
    }
#if (FLS_256K_BLOCK_SECOND != 0U)
    else if (pFls_BlkSel->second256KBlkSel > 0U)
    {
        u8Fls_Offset = FLS_256K_SECOND_OFFSET;
        for (u8Fls_Index = 0U; u8Fls_Index < FLS_256K_BLOCK_SECOND; u8Fls_Index++)
        {
            if (((pFls_BlkSel->second256KBlkSel & (1UL << u8Fls_Index)) >> u8Fls_Index) == 1UL)
            {
                u32Fls_Addr = flashInfo[u8Fls_Index + u8Fls_Offset].addrStart;
                break;
            }
        }
    }
#endif
    else
    {
    }

    return u32Fls_Addr;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( uint32, FLS_CODE ) FLS_SDK_LLD_AddrInvalid(VAR( uint32, AUTOMATIC) u32Fls_addr)
{
    VAR( uint32, AUTOMATIC) u32Fls_Index = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_valid = 0U;

    for (u32Fls_Index = 0U; u32Fls_Index < FLS_BLOCK_ALL; u32Fls_Index++)
    {
        VAR( uint32, AUTOMATIC) u32Fls_addrStart = 0U;
        VAR( uint32, AUTOMATIC) u32Fls_addrEnd = 0U;

        u32Fls_addrStart = flashInfo[u32Fls_Index].addrStart;
        u32Fls_addrEnd   = flashInfo[u32Fls_Index].addrEnd;

        if ((u32Fls_addrStart <= u32Fls_addr) && (u32Fls_addr <= u32Fls_addrEnd))
        {
            VAR( uint32, AUTOMATIC) u32Fls_fmcSelReg = 0U;

            VAR( uint32, AUTOMATIC) u32Fls_lockSelReg = 0U;
            VAR( uint32, AUTOMATIC) u32Fls_lockSelBit = 0U;

            u32Fls_lockSelReg = flashInfo[u32Fls_Index].lockSelReg;
            u32Fls_lockSelBit = flashInfo[u32Fls_Index].lockSelBit;

            switch (u32Fls_lockSelReg)
            {
                case 0U:
                {
                    u32Fls_fmcSelReg = FLS_FMC.SEL0.R;
                    break;
                }

                case 1U:
                {
                    u32Fls_fmcSelReg = FLS_FMC.SEL1.R;
                    break;
                }

                case 2U:
                {
                    u32Fls_fmcSelReg = FLS_FMC.SEL2.R;
                    break;
                }

                case 3U:
                {
                    u32Fls_fmcSelReg = FLS_FMC.SEL3.R;
                    break;
                }

                default: /* PRQA S 2016 */
                {
                    break;
                }
            }

            if (0U != (u32Fls_fmcSelReg & (1U << u32Fls_lockSelBit))) /* PRQA S 1891, 4397 */
            {
                u32Fls_valid = 1U;
                break;
            }
        }
    }

    return u32Fls_valid;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( void, FLS_CODE ) FLS_SDK_LLD_DCacheInvalid(void) /* PRQA S 3006 */
{
	VAR( uint32, AUTOMATIC) u32DCache_Way  = 0U;
    VAR( uint32, AUTOMATIC) u32DCache_Set  = 0U;

    for (u32DCache_Way = 0U; u32DCache_Way < 2U; u32DCache_Way++)
    {
        for (u32DCache_Set = 0U; u32DCache_Set < 64U; u32DCache_Set++)
        {
            VAR( uint32, AUTOMATIC) u32DCache_Temp = 0U;

            VAR( uint32, AUTOMATIC) u32DCache_Tag  = 0U;
            VAR( uint32, AUTOMATIC) u32DCache_Valid  = 0U;

            u32DCache_Temp = 0x80000005U | (u32DCache_Way << 28U) | (u32DCache_Set << 19U);

            MTDCR(351, u32DCache_Temp);
            u32DCache_Temp = MFDCR(350);

            u32DCache_Tag   = u32DCache_Temp & 0xFFFFF800U;
            u32DCache_Valid = (u32DCache_Temp & 0x100U) >> 8U;

            if ((u32DCache_Valid != 0U) && (0U != FLS_SDK_LLD_AddrInvalid(u32DCache_Tag)))
            {
                u32DCache_Temp = 0x5U | (u32DCache_Way << 24U) | (u32DCache_Set << 5U);

                MTSPR(1016, u32DCache_Temp);
            }
        }
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
/*
 * @brief Execute program operation
 *
 * This function will do program operation
 *
 * @param[in] pFls_CtxData Storing context variables.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLS_SDK_LLD_PgmExec \
( \
    P2VAR( fls_ctxdata_t, AUTOMATIC, FLS_APPL_DATA ) pFls_CtxData \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    VAR( uint32, AUTOMATIC) u32Fls_SrcIndex = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_Temp = 0U;

    if (0U != pFls_CtxData->u32Fls_Size)
    {
        /* Set MCR_PGM to start program operation */
        FLS_FMC.MCR.B.PGM = 1U;

        if (FLS_FMC.MCR.B.PGM == 0U)
        {
            sFls_Ret = STATUS_FLASH_ERROR_ENABLE;
        }
        else
        {
            /* Disable Cache */
            PFLASH.PFCR1.B.P0_BFEN = 0U;
            PFLASH.PFCR2.B.P1_BFEN = 0U;
            /* Compute the buffer u32Fls_Size used in the program cycle and calculate number of word for interlock write */
            if (pFls_CtxData->u32Fls_Size > FLS_SDK_PROGRAMABLE_SIZE)
            {
                u32Fls_Temp = FLS_SDK_PROGRAMABLE_SIZE / FLS_SDK_WORD_SIZE;
            }
            else
            {
                u32Fls_Temp = pFls_CtxData->u32Fls_Size / FLS_SDK_WORD_SIZE;
            }

            /* Program data */
            for (u32Fls_SrcIndex = 0U; u32Fls_SrcIndex < u32Fls_Temp; u32Fls_SrcIndex++)
            {
                /* Programming write */
                *(volatile uint32 *)(pFls_CtxData->u32Fls_Dest) /*polyspace RTE:IDP,NIV*/ 
                    = *(volatile uint32 *)(pFls_CtxData->u32Fls_Src); /*polyspace RTE:IDP,NIV*/
                
                /* Update u32Fls_Dest, u32Fls_Size, source index */
                pFls_CtxData->u32Fls_Dest += FLS_SDK_WORD_SIZE;
                pFls_CtxData->u32Fls_Src += FLS_SDK_WORD_SIZE;
                pFls_CtxData->u32Fls_Size -= FLS_SDK_WORD_SIZE;

                /* Is it time to do page programming?  */
                if (0U == (pFls_CtxData->u32Fls_Dest % FLS_SDK_PROGRAMABLE_SIZE))
                {
                    break;
                }
            }
            
            /* Set MCR_EHV bit */
            if (FLS_OP_SYNC == pFls_CtxData->u32Fls_Mode)
            {
            #if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )                   
                pFls_AcCodePtr(&u32Fls_TimerCounterAC);  /*polyspace RTE:COR*/
                if( 0U == u32Fls_TimerCounterAC )
                {
                    sFls_Ret = STATUS_TIMEOUT;
                    Fls_ReportRuntimeError( FLS_MAINFUNCTION_ID, FLS_E_TIMEOUT);
                }
            #else
                pFls_AcCodePtr();
            #endif
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

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*
 * @brief Check the status of flash erase operate
 *
 * This function will check the status of ongoing high voltage in erase
 *
 * @param[out] pFls_Status The status of flash erase after calling the function.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLS_SDK_LLD_CheckErsExec(uint8 * pFls_Status)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;
    *pFls_Status = FLS_OK;

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
            *pFls_Status = FLS_ERS_WRITE;
        }
    }
    else
    {
        /* EGOOD (PEG) is low */
        sFls_Ret = STATUS_ERROR;

        /* Clear EHV if it is high */
        if ( (FLS_FMC.MCR.B.EHV != 0U) || (FLS_EHV_Val == 1U) )
        {
            /* Clear EHV */
            FLS_FMC.MCR.B.EHV = 0U;
            FLS_EHV_Val = 0U;
        }
    }

    if (*pFls_Status != FLS_ERS_WRITE)
    {
        /* Clear ERS */
        FLS_FMC.MCR.B.ERS = 0U;
        /* Enable Cache */
        PFLASH.PFCR1.B.P0_BFEN = 1U;
        PFLASH.PFCR2.B.P1_BFEN = 1U;
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*
 * @brief Check the erase operation
 *
 * This function will check the status of ongoing erase operation.
 *
 * @param[out] pFls_OpRet: Return the state of flash.
 * @return Operation status
 */


#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_CheckEraseStatus \
( \
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) pFls_OpRet \
)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;

    if (pFls_OpRet == NULL)
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    *pFls_OpRet = FLS_OK;

    /* There must be an erase operation */
    if (FLS_FMC.MCR.B.ERS != 0U)
    {
        /* If DONE bit goes high */
        if (FLS_FMC.MCR.B.DONE != 0U)
        {
            /* If the operation is suspended */
            if (FLS_FMC.MCR.B.ESUS != 0U)
            {
                *pFls_OpRet = FLS_ERS_SUS;
            }
            else
            {
                sFls_Ret = FLS_SDK_LLD_CheckErsExec(pFls_OpRet);
            }

        }
        else
        {
 			#if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )
            u32Fls_TimerCounterAC--;
            if( 0U == u32Fls_TimerCounterAC )
            {
                /* Specification of Flash Driver : [SWS_Fls_00361] */
                /* Specification of Flash Driver : [SWS_Fls_00360] */
                sFls_Ret = STATUS_TIMEOUT;
                Det_ReportRuntimeError((uint16)FLS_MODULE_ID, FLS_INSTANCE, FLS_MAINFUNCTION_ID, FLS_E_TIMEOUT); /* PRQA S 3200 */
                u32Fls_TimerCounterAC = FLS_ASYNC_ERASE_TIMEOUT_VALUE;
            }
            else
            {
            #endif
                sFls_Ret = STATUS_FLASH_INPROGRESS;
            #if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )
            }
            #endif /* FLS_TIMEOUT_HANDLING == STD_ON */
            
           
        }
    }
    else
	{
		sFls_Ret = STATUS_INITIALIZED;
	}

    return sFls_Ret;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"







/*
 * @brief Program operation for flash
 *
 * This function is to do program operation for flash.
 *
 * @param[in] pFls_CtxData: Storing context variables.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_Program \
( \
    P2VAR( fls_ctxdata_t, AUTOMATIC, FLS_APPL_DATA ) pFls_CtxData \
)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;

    if ( (pFls_CtxData == NULL) || ((pFls_CtxData->u32Fls_Dest % FLS_SDK_DWORD_SIZE) != 0U) \
        || ((pFls_CtxData->u32Fls_Size % FLS_SDK_DWORD_SIZE) != 0U) )
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    if (((FLS_FMC.MCR.B.PGM != 0U) && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.PSUS != 0U))) \
        || ((FLS_FMC.MCR.B.ERS != 0U) && (FLS_FMC.MCR.B.ESUS == 0U)))
    {
        /*
         * Return busy: program in progress, program in suspended, erase in progress
         * */
        sFls_Ret = STATUS_BUSY;
    }
    else
    {
        /*
         * Do program: no program and erase, erase_suspend and EHV is low
         * */
        sFls_Ret = FLS_SDK_LLD_PgmExec(pFls_CtxData);
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"


/*
 * @brief Check the status of flash program operate
 *
 * This function will check the status of ongoing high voltage in program
 *
 * @param[in] pFls_CtxData Storing context variables.
 * @param[out] pFls_Status The status of flash program after calling the function.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLS_SDK_LLD_CheckPgmExec \
( \
    P2VAR( fls_ctxdata_t, AUTOMATIC, FLS_APPL_DATA ) pFls_CtxData, \
    uint8 * pFls_Status \
)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;
    *pFls_Status = FLS_OK;

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
            if ((pFls_CtxData->u32Fls_Size) != 0x0U)  /* polyspace RTE:NIV */
            {
                /* Call FLASH_LLD_Program to continue the operation */
                sFls_Ret = FLASH_SDK_LLD_Program(pFls_CtxData);

                if (sFls_Ret == STATUS_SUCCESS)
                {
                    sFls_Ret = STATUS_FLASH_INPROGRESS;
                }
            }
            else /* pFls_CtxData->u32Fls_Size == 0 */
            {
                /* Program finished successfully, clear PGM */
                FLS_FMC.MCR.B.PGM = 0U;
                /* Enable Cache */
                PFLASH.PFCR1.B.P0_BFEN = 1U;
                PFLASH.PFCR2.B.P1_BFEN = 1U;
            }
        }
        else /* EHV == 0 */
        {
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                *pFls_Status = FLS_ERS_SUS_PGM_WRITE;
            }
            else
            {
                *pFls_Status = FLS_PGM_WRITE;
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
                *pFls_Status = FLS_ERS_SUS_PGM_WRITE;
            }
            else
            {
                *pFls_Status = FLS_PGM_WRITE;
            }
        }
        /* Program finished unsuccessfully, clear PGM */
        FLS_FMC.MCR.B.PGM = 0U;
        sFls_Ret = STATUS_ERROR;
        /* Enable Cache */
        PFLASH.PFCR1.B.P0_BFEN = 1U;
        PFLASH.PFCR2.B.P1_BFEN = 1U;
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*
 * @brief Check the program operation
 *
 * This function will check the status of ongoing program operation.
 *
 * @param[in] pFls_CtxData: Storing context variables.
 * @param[out] pFls_OpRet: Return the status of flash.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_CheckProgramStatus \
( \
    P2VAR( fls_ctxdata_t, AUTOMATIC, FLS_APPL_DATA ) pFls_CtxData, \
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) pFls_OpRet \
)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;
    if ( (pFls_CtxData == NULL) || (pFls_OpRet == NULL))
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    *pFls_OpRet = FLS_OK;

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
                    *pFls_OpRet = FLS_ERS_SUS_PGM_SUS;
                }
                else
                {
                    *pFls_OpRet = FLS_PGM_SUS;
                }
            }
            else
            {
                sFls_Ret = FLS_SDK_LLD_CheckPgmExec(pFls_CtxData, pFls_OpRet);
            }
        }
        else
        {
            /* DONE bit is still low means the operation is in-progress */
            #if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )
            u32Fls_TimerCounterAC--;
            if( 0U == u32Fls_TimerCounterAC )
            {
                /* Specification of Flash Driver : [SWS_Fls_00361] */
                /* Specification of Flash Driver : [SWS_Fls_00362] */
				sFls_Ret = STATUS_TIMEOUT;
                Fls_ReportRuntimeError(FLS_MAINFUNCTION_ID, FLS_E_TIMEOUT);
				 u32Fls_TimerCounterAC = FLS_ASYNC_WRITE_TIMEOUT_VALUE;
            }
			else 
			{
            #endif /* FLS_TIMEOUT_HANDLING == STD_ON */
            	sFls_Ret = STATUS_FLASH_INPROGRESS; 
			#if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )
            }
            #endif /* FLS_TIMEOUT_HANDLING == STD_ON */
        }
    }
    else 
    {
        sFls_Ret = STATUS_INITIALIZED;
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*
 * @brief Erase the selected flash block
 *
 * This function is to do erase operation for selected flash block.
 *
 * @param[in] u8Fls_EraseSpace: Select flash main space.
 * @param[in] pFls_BlkSel: Select the special flash block for erasing.
 * @param[in] u32Fls_Mode: means the operate u32Fls_Mode of erase.
              FLS_OP_SYNC: means sync erase operate.
              FLS_OP_ASYNC: means async erase operate.
 * @return Operation status
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FLS_INLINE FUNC( status_t, FLS_CODE ) FLASH_SDK_LLD_Erase \
( \
    VAR( uint8, AUTOMATIC ) u8Fls_EraseSpace, \
    P2VAR( fls_blksel_t, AUTOMATIC, FLS_APPL_DATA ) pFls_BlkSel, \
    VAR( uint32, AUTOMATIC) u32Fls_Mode \
)
{
    VAR( status_t, AUTOMATIC)  sFls_Ret = STATUS_SUCCESS;
    VAR( uint32, AUTOMATIC)  u32Fls_InterlockWriteAddress = 0U;

    if (pFls_BlkSel == NULL)
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }
    /* Check for validity of erase option */
    if (u8Fls_EraseSpace == FLS_ERS_MAIN_SPACE)
    {
        u32Fls_InterlockWriteAddress = FLS_SDK_LLD_GetInterWriteAddr(pFls_BlkSel);
        if (0U == u32Fls_InterlockWriteAddress)
        {
            sFls_Ret = STATUS_ERROR;
            return sFls_Ret;
        }
    }
    else
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    if ((FLS_FMC.MCR.B.PGM != 0U) || ((FLS_FMC.MCR.B.ERS != 0U) \
        && ((FLS_FMC.MCR.B.EHV != 0U) || (FLS_FMC.MCR.B.ESUS != 0U))))
    {
        sFls_Ret = STATUS_BUSY;
    }
    else
    {
        /* Set MCR_ERS to start erase operation */
        FLS_FMC.MCR.B.ERS = 1U;

        if (FLS_FMC.MCR.B.ERS == 0U)
        {
            sFls_Ret = STATUS_FLASH_ERROR_ENABLE;
        }
        else
        {
            /* Correct the block selection for the case we erase Main array */

            /* Mask off reserved bits for low address space */
            pFls_BlkSel->lowBlkSel &= FLS_SEL_MASK_LOW;
            /* Mask off reserved bits for mid address space */
            pFls_BlkSel->midBlkSel &= FLS_SEL_MASK_MID;
            /* Mask off reserved bits for high address space */
            pFls_BlkSel->highBlkSel &= FLS_SEL_MASK_HIGH;
            /* Mask off reserved bits for first 256K address space */
            pFls_BlkSel->first256KBlkSel &= FLS_SEL_MASK_FIR256K; /* PRQA S 2985 */
            /* Mask off reserved bits for second 256K address space */
            pFls_BlkSel->second256KBlkSel &= FLS_SEL_MASK_SEC256K;

            /* No blocks to be selected for erase, just return */
            if ((pFls_BlkSel->lowBlkSel | pFls_BlkSel->midBlkSel | pFls_BlkSel->highBlkSel \
                | pFls_BlkSel->first256KBlkSel | pFls_BlkSel->second256KBlkSel) == 0U) /* PRQA S 2992, 2996 */
            {
                /* Return with STATUS_SUCCESS */
                FLS_FMC.MCR.B.ERS = 0U;
            }
            else
            {
                /* Set the block selection registers */
                FLS_FMC.SEL0.B.LOWSEL = pFls_BlkSel->lowBlkSel;
                FLS_FMC.SEL0.B.MIDSEL = pFls_BlkSel->midBlkSel;
                FLS_FMC.SEL1.R = pFls_BlkSel->highBlkSel;
                FLS_FMC.SEL2.R = pFls_BlkSel->first256KBlkSel;
                FLS_FMC.SEL3.R = pFls_BlkSel->second256KBlkSel;
            }
        
            /* Check if ERS bit is set */
            if (FLS_FMC.MCR.B.ERS != 0U)
            {
                /* Disable Cache */
                PFLASH.PFCR1.B.P0_BFEN = 0U;
                PFLASH.PFCR2.B.P1_BFEN = 0U;
                /* Interlock write */
                *((volatile uint32*)u32Fls_InterlockWriteAddress) = FLS_ERASED_VALUE;  /*polyspace RTE:IDP*/
                /* Write a 1 to MCR_EHV */
                if (FLS_OP_SYNC == u32Fls_Mode)
                {
                #if( FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON )                   
                    pFls_AcCodePtr(&u32Fls_TimerCounterAC);  /*polyspace RTE:COR*/
                    if( 0U == u32Fls_TimerCounterAC )
                    {
                        sFls_Ret = STATUS_TIMEOUT;
                        Fls_ReportRuntimeError( FLS_MAINFUNCTION_ID, FLS_E_TIMEOUT);
                    }
                #else
                    pFls_AcCodePtr();
                #endif
                }
                else
                {  
                    FLS_FMC.MCR.B.EHV = 1U;
                }
                /* Not wait until MCR_DONE is set */
            }
        }
        
    }
    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"



/*
 * @brief FLS_Erase
 *
 * Flash erase special block.
 */
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLS_SDK_Erase \
( \
    VAR( uint16, AUTOMATIC) u16Fls_FlashBlock, \
    VAR( uint32, AUTOMATIC) u32Fls_Index, \
    VAR( uint16, AUTOMATIC ) bFls_Mode \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    VAR( fls_blksel_t, AUTOMATIC) pFls_BlkSel;
    VAR( uint8, AUTOMATIC)  u8Fls_OpRet;
    VAR( uint32, AUTOMATIC) u32Fls_Offset = 0U;

    if (u16Fls_FlashBlock > FLS_BLK_SECOND_256K)
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }
    
    /*
     * Flash erase operate
     *
     *  */
    sFls_Ret = FLASH_SDK_LLD_CheckEraseStatus(&u8Fls_OpRet);
    
    if(sFls_Ret == STATUS_SUCCESS && (FLS_OK == u8Fls_OpRet) )
	{
        FLS_SDK_LLD_DCacheInvalid();   // Make the erased flash space in Dcache invalid
        return sFls_Ret;	
	}
    else if(sFls_Ret == STATUS_INITIALIZED )
	{
    /* Get flash block offset and select state */
		sFls_Ret = FLS_SDK_Get_Offset_Select(u16Fls_FlashBlock, u32Fls_Index, &u32Fls_Offset, &pFls_BlkSel);
		if (STATUS_SUCCESS != sFls_Ret)
		{
			return sFls_Ret;
		}
		/* Call FLASH_LLD_Erase to start erase */
		sFls_Ret = FLASH_SDK_LLD_Erase(FLS_ERS_MAIN_SPACE, &pFls_BlkSel, bFls_Mode);
		if (STATUS_SUCCESS != sFls_Ret)
		{
			return sFls_Ret;
		}

		/* Call FLASH_LLD_CheckEraseStatus to confirm erase successful or not */

		sFls_Ret = FLASH_SDK_LLD_CheckEraseStatus(&u8Fls_OpRet);


		if ((STATUS_SUCCESS != sFls_Ret) || (FLS_OK != u8Fls_OpRet))
		{
			return sFls_Ret;
		}

		/* Check offset and index */
		if ((u32Fls_Offset + u32Fls_Index) >= FLS_BLOCK_ALL)
		{
			sFls_Ret = STATUS_ERROR;
			return sFls_Ret;
		 }
    }
    else 
    {
        return sFls_Ret;
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLS_SDK_Read  \
( \
    VAR( uint32, AUTOMATIC) u32Fls_dest, \
    VAR( uint32, AUTOMATIC) u32Fls_size,  \
    P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) pDataPtr
)
{
    VAR(uint32, AUTOMATIC) u32Fls_InitDataLength = 0UL;
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    P2CONST(volatile uint8, AUTOMATIC, FLS_APPL_CONST) Fls_ReadEndAddressPtr = NULL_PTR;
    P2CONST(volatile uint8, AUTOMATIC, FLS_APPL_CONST) u8Fls_ReadBlockAddressEndPtr = NULL_PTR;

    gFls_ReadAddressPtr = (volatile const uint8 *)u32Fls_dest;
    Fls_ReadEndAddressPtr = gFls_ReadAddressPtr + u32Fls_size;

    u32Fls_InitDataLength = Fls_LLD_CalcInitDataLength( gFls_ReadAddressPtr, u32Fls_size );
    u8Fls_ReadBlockAddressEndPtr = gFls_ReadAddressPtr + u32Fls_InitDataLength;

    while( (uint32)gFls_ReadAddressPtr < (uint32)u8Fls_ReadBlockAddressEndPtr )   
    {
        *pDataPtr = *gFls_ReadAddressPtr;  /*polyspace RTE:IDP,NIV*/
        pDataPtr++;
        gFls_ReadAddressPtr++;
    }

    u8Fls_ReadBlockAddressEndPtr += Fls_LLD_CalcWideDataLength( u32Fls_InitDataLength, u32Fls_size );
    while( (uint32)gFls_ReadAddressPtr < (uint32)u8Fls_ReadBlockAddressEndPtr )   
    {
        *((FLS_LLD_DATA_BUS_WIDTH_TYPE*)pDataPtr) = /*polyspace RTE:IDP,NIV*/
        *((volatile const FLS_LLD_DATA_BUS_WIDTH_TYPE*)gFls_ReadAddressPtr); /*polyspace RTE:IDP,NIV*/
        pDataPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE);
        gFls_ReadAddressPtr += sizeof(FLS_LLD_DATA_BUS_WIDTH_TYPE);
    }

    while( (uint32)gFls_ReadAddressPtr < (uint32)Fls_ReadEndAddressPtr )    
    {
        *pDataPtr = *gFls_ReadAddressPtr;  /*polyspace RTE:IDP,NIV*/
        pDataPtr++;
        gFls_ReadAddressPtr++;
    }
    if(FLS_FMC.MCR.B.EER == 1)
    {
        if(gFls_ConfigPtr->FlsRegErrorNotification != NULL_PTR)
        {
            gFls_ConfigPtr->FlsRegErrorNotification();/* polyspace RTE:COR */
        }
        FLS_FMC.MCR.B.EER = 1;
        sFls_Ret = STATUS_ERROR;
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(status_t, FLS_CODE) FLASH_SDK_LLD_Abort(void)
{
    volatile VAR(uint32, AUTOMATIC) u32Fls_clearFlag = 0x0U;
    VAR( uint32, AUTOMATIC) u32Fls_count = 450U;

    volatile VAR(uint32, AUTOMATIC) u32Fls_erase = 0x0U;
    u32Fls_erase = FLS_FMC.MCR.B.ERS;
    if (FLS_FMC.MCR.B.ESUS != 0U)
    {
        if (FLS_FMC.MCR.B.PSUS != 0U)
        {
            u32Fls_clearFlag = 0x3U;
        }
        else
        {
            u32Fls_clearFlag = 0x2U;
        }
    }
    else
    {
        if (FLS_FMC.MCR.B.PSUS != 0U)
        {
            u32Fls_clearFlag = 0x1U;
        }
    }

    if ((u32Fls_clearFlag & 0x1U) != 0x0U)  /* Program-suspended Erase-suspended or Program-suspended only */
    {
        /* Wait MCR DONE bit is set to program-suspended operation accomplish */
        while ((FLS_FMC.MCR.B.DONE == 0U) && (u32Fls_count > 0U))
        {
            u32Fls_count--;
        }
        /* Set MCR_EHV bit then clear MCR_PSUS to resume program operation */
        FLS_FMC.MCR.B.EHV = 1U;
        FLS_FMC.MCR.B.PSUS = 0U;
    }

    if ((u32Fls_clearFlag & 0x2U) != 0x0U)
    {
        /* Clear EHV to abort program operation and then clear MCR_PGM */
        FLS_FMC.MCR.B.EHV = 0U;
        /* Wait MCR DONE bit is set */
        while ((FLS_FMC.MCR.B.DONE == 0U) && (u32Fls_count > 0U))
        {
            u32Fls_count--;
        }
        FLS_FMC.MCR.B.PGM = 0U;
        /* Set MCR_EHV bit then clear MCR_PSUS to resume erase operation */
        FLS_FMC.MCR.B.EHV = 1U;
        FLS_FMC.MCR.B.ESUS = 0U;
    }

    /* Clear EHV bit to abort flash operation */
    FLS_FMC.MCR.B.EHV = 0U;
    /* Wait MCR DONE bit is set */
    while ((FLS_FMC.MCR.B.DONE == 0U) && (u32Fls_count > 0U))
    {
        u32Fls_count--;
    }

    /* Clear PGM, ERS bit */
    FLS_FMC.MCR.B.PGM = 0U;
    FLS_FMC.MCR.B.ERS = 0U;
    /* Enable Cache */
    PFLASH.PFCR1.B.P0_BFEN = 1U;
    PFLASH.PFCR2.B.P1_BFEN = 1U;

    if (u32Fls_erase != 0x0U)
    {
        FLS_SDK_LLD_DCacheInvalid();
    }

    return STATUS_SUCCESS;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLASH_LLD_BlankCheck \
( \
    VAR( uint32, AUTOMATIC) u32Fls_Dest, \
    VAR( uint32, AUTOMATIC) u32Fls_Size, \
    VAR( uint32, AUTOMATIC) u32Fls_CheckWordSize, \
    P2VAR( uint32, AUTOMATIC, FLS_APPL_DATA ) pFls_FailAddr \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    VAR( uint32, AUTOMATIC) u32Fls_DestIndex = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_Temp = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_DestTmp = u32Fls_Dest;
    VAR( uint32, AUTOMATIC) u32Fls_SizeTmp = u32Fls_Size;

    if (((u32Fls_DestTmp | u32Fls_SizeTmp) % FLS_SDK_WORD_SIZE) != 0U)
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    while ((u32Fls_SizeTmp > 0U) && (STATUS_SUCCESS == sFls_Ret))
    {
        /* Number of words needs to be checked for blank */
        u32Fls_Temp = u32Fls_SizeTmp / FLS_SDK_WORD_SIZE;

        /* In each blank check cycle, we take up to a certain words */
        if (u32Fls_Temp >= u32Fls_CheckWordSize)
        {
            u32Fls_Temp = u32Fls_CheckWordSize;
        }

        /* Word by word blank check */
        for (u32Fls_DestIndex = 0U; u32Fls_DestIndex < u32Fls_Temp; u32Fls_DestIndex++)
        {
            if ((*(volatile uint32 *)u32Fls_DestTmp) != 0xFFFFFFFFU) /*polyspace RTE:NIV,IDP*/
            {
                sFls_Ret = STATUS_ERROR;
                *pFls_FailAddr = u32Fls_DestTmp;
                break;
            }
            u32Fls_DestTmp += FLS_SDK_WORD_SIZE;
            u32Fls_SizeTmp -= FLS_SDK_WORD_SIZE;
        }
        if(FLS_FMC.MCR.B.EER == 1)
		{
			if(gFls_ConfigPtr->FlsRegErrorNotification != NULL_PTR)
			{
				gFls_ConfigPtr->FlsRegErrorNotification();/* polyspace RTE:COR */
			}
			FLS_FMC.MCR.B.EER = 1;
			sFls_Ret = STATUS_ERROR;
		}
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC( status_t, FLS_CODE ) FLASH_LLD_ProgramVerify \
( \
    VAR( uint32, AUTOMATIC) u32Fls_Dest, \
    VAR( uint32, AUTOMATIC) u32Fls_Size, \
    VAR( uint32, AUTOMATIC) u32Fls_Src, \
    VAR( uint32, AUTOMATIC) u32Fls_CheckWordSize, \
    P2VAR( uint32, AUTOMATIC, FLS_APPL_DATA ) pFls_FailAddr \
)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    VAR( uint32, AUTOMATIC) u32Fls_DestIndex = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_Temp = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_ValDest = 0U;
    VAR( uint32, AUTOMATIC) u32Fls_DestTmp = u32Fls_Dest;
    VAR( uint32, AUTOMATIC) u32Fls_SizeTmp = u32Fls_Size;
    VAR( uint32, AUTOMATIC) u32Fls_SrcTmp = u32Fls_Src;

    if ( ((u32Fls_DestTmp | u32Fls_SizeTmp | u32Fls_Src) % FLS_SDK_WORD_SIZE) != 0U )
    {
        sFls_Ret = STATUS_ERROR;
        return sFls_Ret;
    }

    while ((u32Fls_SizeTmp > 0U) && (STATUS_SUCCESS == sFls_Ret))
    {
        /* Number of words needs to be verified */
        u32Fls_Temp = u32Fls_SizeTmp / FLS_SDK_WORD_SIZE;

        /* In each verify cycle, we take up to a certain words */
        if (u32Fls_Temp >= u32Fls_CheckWordSize)
        {
            u32Fls_Temp = u32Fls_CheckWordSize;
        }

        /* Word by word verify */
        for (u32Fls_DestIndex = 0U; u32Fls_DestIndex < u32Fls_Temp; u32Fls_DestIndex++)
        {
            u32Fls_ValDest = *(volatile uint32 *)u32Fls_DestTmp; /*polyspace RTE:NIV,IDP*/
            if (u32Fls_ValDest != *(volatile uint32 *)u32Fls_SrcTmp)  /*polyspace RTE:NIV,IDP*/
            {
                sFls_Ret = STATUS_ERROR;
                *pFls_FailAddr = u32Fls_DestTmp;
                break;
            }

            u32Fls_DestTmp += FLS_SDK_WORD_SIZE;
            u32Fls_SrcTmp += FLS_SDK_WORD_SIZE;
            u32Fls_SizeTmp -= FLS_SDK_WORD_SIZE;
        }
        if(FLS_FMC.MCR.B.EER == 1)
		{
			if(gFls_ConfigPtr->FlsRegErrorNotification != NULL_PTR)
			{
				gFls_ConfigPtr->FlsRegErrorNotification();/* polyspace RTE:COR */
			}
			FLS_FMC.MCR.B.EER = 1;
			sFls_Ret = STATUS_ERROR;
		}
    }

    return sFls_Ret;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

