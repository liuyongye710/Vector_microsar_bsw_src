/* PRQA S 2053, 0380 ,3432 EOF */ 
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

/**
*   @file    Fls_AutoSar_Wrapper.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of FLS MCAL driver.
*
*   @addtogroup FLS
*   @{
*/

#include "Fls_AutoSar_Wrapper.h"
#include "Fls_HAL_Wrapper.h"
#include "Det.h"

#define FLS_ATC_WRA_C_VENDOR_ID                     176
#define FLS_ATC_WRA_C_AR_REL_MAJOR_VER              4
#define FLS_ATC_WRA_C_AR_REL_MINOR_VER              4
#define FLS_ATC_WRA_C_AR_REL_REV_VER                0
#define FLS_ATC_WRA_C_SW_MAJOR_VER                  3
#define FLS_ATC_WRA_C_SW_MINOR_VER                  0
#define FLS_ATC_WRA_C_SW_PATCH_VER                  0

#if (FLS_VENDOR_ID_OUTPUT != FLS_ATC_WRA_C_VENDOR_ID)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_VENDOR_ID "
#endif
#if (FLS_AR_REL_MAJOR_VER_OUTPUT != FLS_ATC_WRA_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_AR_REL_MAJOR_VER "
#endif
#if (FLS_AR_REL_MINOR_VER_OUTPUT != FLS_ATC_WRA_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_AR_REL_MINOR_VER "
#endif
#if (FLS_AR_REL_REVISION_VER_OUTPUT != FLS_ATC_WRA_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_AR_REL_REV_VER "
#endif
#if (FLS_SW_MAJOR_VERSION_OUTPUT != FLS_ATC_WRA_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_SW_MAJOR_VER "
#endif
#if (FLS_SW_MINOR_VERSION_OUTPUT != FLS_ATC_WRA_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_SW_MINOR_VER "
#endif
#if (FLS_SW_PATCH_VERSION_OUTPUT != FLS_ATC_WRA_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : FLS_ATC_WRA_C_SW_PATCH_VER "
#endif



#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_Init(void)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;

    if(gFls_ConfigPtr->eDefaultMode == MEMIF_MODE_SLOW)
    {
        gFls_MaxRead = gFls_ConfigPtr->u32MaxReadNormalMode;
        gFls_MaxWrite = gFls_ConfigPtr->u32MaxWriteNormalMode;
    }
    if(gFls_ConfigPtr->eDefaultMode == MEMIF_MODE_FAST)
    {
        gFls_MaxRead = gFls_ConfigPtr->u32MaxReadFastMode;
        gFls_MaxWrite = gFls_ConfigPtr->u32MaxWriteFastMode;
    }
    
    sFls_Ret = Fls_Wrapper_InitController();

    if (sFls_Ret != STATUS_SUCCESS)
    {
        gFls_LLDJobResult = MEMIF_JOB_FAILED;
        gFls_JobResult = MEMIF_JOB_FAILED;
        #if( FLS_DEV_ERROR_DETECT == STD_ON )
        gFls_ConfigPtr = NULL_PTR;
        #endif
    }
    else
    {
        /* Specification of Flash Driver : [SWS_Fls_00323] */
        gFls_ModuleStatus = MEMIF_IDLE;
        /* Specification of Flash Driver : [SWS_Fls_00324] */
        gFls_JobResult = MEMIF_JOB_OK;
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_Erase \
( \
    VAR( Fls_AddressType, AUTOMATIC) TargetAddress, \
    VAR( Fls_LengthType, AUTOMATIC) Length \
)
{   
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_TmpJobSectorIt = 0UL;
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_TmpJobSectorEnd = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) u32Fls_TmpJobAddrEnd = 0UL;

    u32Fls_TmpJobAddrEnd = ( TargetAddress + Length ) - 1U;
    u32Fls_TmpJobSectorIt = Fls_GetSectorIndexByAddr( TargetAddress );
    u32Fls_TmpJobSectorEnd = Fls_GetSectorIndexByAddr(( TargetAddress + Length ) - 1U );
    /* Specification of Flash Driver : [SWS_Fls_00327] */
    gFls_JobSectorIt = u32Fls_TmpJobSectorIt;
    gFls_JobAddrIt = TargetAddress;
    gFls_JobAddrEnd = u32Fls_TmpJobAddrEnd;
    gFls_JobSectorEnd = u32Fls_TmpJobSectorEnd;
    gFls_Job = FLS_JOB_ERASE;
    gFls_JobStart = 1U;
    /* Specification of Flash Driver : [SWS_Fls_00328] */
    gFls_ModuleStatus = MEMIF_BUSY;
    /* Specification of Flash Driver : [SWS_Fls_00329] */
    gFls_JobResult = MEMIF_JOB_PENDING;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_Read \
( \
    VAR( Fls_AddressType, AUTOMATIC) SourceAddress, \
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) TargetAddressPtr, \
    VAR( Fls_LengthType, AUTOMATIC) Length \
)
{
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_TmpJobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) u32Fls_TmpJobAddrEnd = 0UL;

    /* Specification of Flash Driver : [SWS_Fls_00337] */
    u32Fls_TmpJobSectorIt = Fls_GetSectorIndexByAddr( SourceAddress );
    u32Fls_TmpJobAddrEnd = ( SourceAddress + Length ) - 1U;

    gFls_JobSectorIt = u32Fls_TmpJobSectorIt;
    gFls_JobSectorEnd = Fls_GetSectorIndexByAddr(u32Fls_TmpJobAddrEnd);
    gFls_JobAddrIt = SourceAddress;
    gFls_JobAddrEnd = u32Fls_TmpJobAddrEnd;
    gFls_JobDataDestPtr = TargetAddressPtr;
    gFls_Job = FLS_JOB_READ;
    gFls_JobStart = 1U;
    /* Specification of Flash Driver : [SWS_Fls_00338] */
    gFls_ModuleStatus = MEMIF_BUSY;
    /* Specification of Flash Driver : [SWS_Fls_00339] */
    gFls_JobResult = MEMIF_JOB_PENDING;

}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_SetMode \
( \
    VAR( MemIf_ModeType, FLS_CODE ) Mode \
)
{
    if (Mode == MEMIF_MODE_FAST)
    {
        gFls_MaxRead = gFls_ConfigPtr->u32MaxReadFastMode;
        gFls_MaxWrite = gFls_ConfigPtr->u32MaxWriteFastMode;
    }
    else if(Mode == MEMIF_MODE_SLOW)
    {
        gFls_MaxRead = gFls_ConfigPtr->u32MaxReadNormalMode;
        gFls_MaxWrite = gFls_ConfigPtr->u32MaxWriteNormalMode;
    }
    else
    {
        /* Do nothing */
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_Write \
( \
    VAR( Fls_AddressType, AUTOMATIC) TargetAddress, \
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) SourceAddressPtr, \
    VAR( Fls_LengthType, AUTOMATIC) Length \
)
{
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_JobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) u32Fls_JobAddrEnd = 0UL;

    /* Specification of Flash Driver : [SWS_Fls_00331] */
    u32Fls_JobSectorIt = Fls_GetSectorIndexByAddr(TargetAddress);
    u32Fls_JobAddrEnd = ( TargetAddress + Length ) - 1U;

    gFls_JobSectorIt = u32Fls_JobSectorIt;
    gFls_JobSectorEnd = Fls_GetSectorIndexByAddr(u32Fls_JobAddrEnd);
    gFls_JobAddrEnd = u32Fls_JobAddrEnd;
    gFls_JobAddrIt = TargetAddress;
    gFls_JobDataSrcPtr = SourceAddressPtr;
    gFls_Job = FLS_JOB_WRITE;
    gFls_JobStart = 1U;
    /* Specification of Flash Driver : [SWS_Fls_00332] */
    gFls_ModuleStatus = MEMIF_BUSY;
    /* Specification of Flash Driver : [SWS_Fls_00333] */
    gFls_JobResult = MEMIF_JOB_PENDING;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE)Fls_Ats_Wrapper_Cancel(void)
{
    if( MEMIF_JOB_PENDING == gFls_JobResult )
    {
        Fls_Wrapper_CancelController();
        /* Specification of Flash Driver : [SWS_Fls_00229] */
        /* Specification of Flash Driver : [SWS_Fls_00335] */
        if(( FLASH_JOB_ERASE == gFls_LLDJob ) || ( FLASH_JOB_WRITE == gFls_LLDJob ))
        {
            gFls_LLDJob = FLASH_JOB_NONE;
            gFls_LLDJobResult = MEMIF_JOB_CANCELED;
        }

        /* Specification of Flash Driver : [SWS_Fls_00143] */
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
            if(( FLS_JOB_ERASE == gFls_Job ) || ( FLS_JOB_WRITE == gFls_Job ))
            {
                Fls_UnloadAc( gFls_Job );
            }
#endif

        if(MEMIF_JOB_PENDING == gFls_LLDJobResult )
        {    
            gFls_LLDJob = FLASH_JOB_NONE;
            gFls_LLDJobResult = MEMIF_JOB_CANCELED;
        }
        else
        {
            gFls_LLDJob = FLASH_JOB_NONE;
            gFls_LLDJobResult = MEMIF_JOB_CANCELED;    
        }

        /* Specification of Flash Driver : [SWS_Fls_00336] */
        gFls_ModuleStatus = MEMIF_IDLE;
        if(MEMIF_JOB_CANCELED == gFls_LLDJobResult)
        {
            gFls_JobResult = MEMIF_JOB_CANCELED;
        }
        /* Specification of Flash Driver : [SWS_Fls_00147] */
        if( NULL_PTR != gFls_ConfigPtr->jobErrorNotificationPtr )
        {
 
            /* Specification of Flash Driver : [SWS_Fls_00193] */
            gFls_ConfigPtr->jobErrorNotificationPtr();/* polyspace RTE:COR */
        }
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE) Fls_Ats_Wrapper_Compare \
( \
    VAR( Fls_AddressType, AUTOMATIC) SourceAddress, \
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr, \
    VAR( Fls_LengthType, AUTOMATIC) Length \
)
{
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_JobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) u32Fls_JobAddrEnd = 0UL;

    /* Specification of Flash Driver : [SWS_Fls_00341] */
    u32Fls_JobSectorIt = Fls_GetSectorIndexByAddr( SourceAddress );
    u32Fls_JobAddrEnd = ( SourceAddress + Length ) - 1U;
    gFls_JobSectorIt = u32Fls_JobSectorIt;
    gFls_JobSectorEnd = Fls_GetSectorIndexByAddr(u32Fls_JobAddrEnd);
    gFls_JobAddrIt = SourceAddress;
    gFls_JobAddrEnd = u32Fls_JobAddrEnd;
    gFls_JobDataSrcPtr = TargetAddressPtr;
    gFls_Job = FLS_JOB_COMPARE;
    gFls_JobStart = 1U;
    /* Specification of Flash Driver : [SWS_Fls_00342] */
    gFls_ModuleStatus = MEMIF_BUSY;
    /* Specification of Flash Driver : [SWS_Fls_00343] */
    gFls_JobResult = MEMIF_JOB_PENDING;

}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE ) Fls_Ats_Wrapper_BlankCheck \
( \
    VAR( Fls_AddressType, AUTOMATIC) TargetAddress, \
    VAR( Fls_LengthType, AUTOMATIC) Length \
)
{
    VAR( Fls_SectorIndex_Type, AUTOMATIC ) u32Fls_JobSectorIt = 0UL;
    VAR( Fls_AddressType, AUTOMATIC ) u32Fls_JobAddrEnd = 0UL;

    u32Fls_JobSectorIt = Fls_GetSectorIndexByAddr( TargetAddress );
    u32Fls_JobAddrEnd = ( TargetAddress + Length ) - 1U;
    gFls_JobSectorIt = u32Fls_JobSectorIt;
    gFls_JobSectorEnd = Fls_GetSectorIndexByAddr(u32Fls_JobAddrEnd);
    gFls_JobAddrIt = TargetAddress;
    gFls_JobAddrEnd = u32Fls_JobAddrEnd;
    gFls_Job = FLS_JOB_BLANK_CHECK;
    gFls_JobStart = 1U;
    /* Specification of Flash Driver : [SWS_Fls_00375] */
    gFls_ModuleStatus = MEMIF_BUSY;
    /* Specification of Flash Driver : [SWS_Fls_00376] */
    gFls_JobResult = MEMIF_JOB_PENDING;

}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
FUNC(void, FLS_CODE)Fls_Ats_Wrapper_MainFunction(void)
{
    if( MEMIF_JOB_PENDING == gFls_JobResult )
    {
        VAR(MemIf_JobResultType, AUTOMATIC) eFls_WorkResult = MEMIF_JOB_OK;

        if( 1U == gFls_JobStart )
        {
            gFls_JobStart = 0U;
/* Specification of Flash Driver : [SWS_Fls_00212] */
/* Specification of Flash Driver : [SWS_Fls_00213] */
#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
            if(( FLS_JOB_ERASE == gFls_Job ) || ( FLS_JOB_WRITE == gFls_Job ))
            {
                Fls_LoadAc( gFls_Job );
            }
#endif /* FLS_AC_LOAD_ON_JOB_START == STD_ON */
            Fls_ClrJobResult();
        }

        /* Specification of Flash Driver : [SWS_Fls_00220] */
        switch(gFls_Job)
        {
            case FLS_JOB_ERASE:
            {
                eFls_WorkResult = Fls_Wrapper_EraseController();

                if(eFls_WorkResult == MEMIF_JOB_FAILED)
                {
                    /* Specification of Flash Driver : [SWS_Fls_00104] */
                    Fls_ReportTransientFault( FLS_MAINFUNCTION_ID, FLS_E_ERASE_FAILED );
                }
                gFls_LLDJob = FLASH_JOB_ERASE;
                gFls_LLDJobResult = MEMIF_JOB_PENDING; 
 
                break;
            }
            case FLS_JOB_WRITE:
            {
                eFls_WorkResult = Fls_Wrapper_WriteController();

                if(eFls_WorkResult == MEMIF_JOB_FAILED)
                {
                    /* Specification of Flash Driver : [SWS_Fls_00105] */
                    Fls_ReportTransientFault( FLS_MAINFUNCTION_ID, FLS_E_WRITE_FAILED );
                }
                gFls_LLDJob = FLASH_JOB_WRITE;
                gFls_LLDJobResult = MEMIF_JOB_PENDING;

                break;
            }
            case FLS_JOB_READ:
            {
                eFls_WorkResult = Fls_Wrapper_ReadController();

                if(eFls_WorkResult == MEMIF_JOB_FAILED)
                {
                    /* Specification of Flash Driver : [SWS_Fls_00106] */
                    Fls_ReportTransientFault( FLS_MAINFUNCTION_ID, FLS_E_READ_FAILED );
                }
                break;
            }
            #if( FLS_COMPARE_API == STD_ON )
            case FLS_JOB_COMPARE:
            {
                eFls_WorkResult = Fls_Wrapper_CompareController();

                if(eFls_WorkResult == MEMIF_JOB_FAILED)
                {
                    eFls_WorkResult = MEMIF_BLOCK_INCONSISTENT;
                    /* Specification of Flash Driver : [SWS_Fls_00107] */
                    Fls_ReportTransientFault( FLS_MAINFUNCTION_ID, FLS_E_COMPARE_FAILED );
                }
                break;
            }
            #endif
            #if( FLS_BLANK_CHECK_API == STD_ON )
            case FLS_JOB_BLANK_CHECK:
            {
                eFls_WorkResult = Fls_Wrapper_BlankCheckController();
                break;
            }
            #endif
            default:
            {
                //do nothing
                break;
            }
        }


#if( FLS_AC_LOAD_ON_JOB_START == STD_ON )
            if(( MEMIF_JOB_PENDING != eFls_WorkResult ) &&
               (( FLS_JOB_ERASE == gFls_Job ) || ( FLS_JOB_WRITE == gFls_Job ))
              )
            {
                Fls_UnloadAc( gFls_Job );
            }
#endif

        /* Specification of Flash Driver : [SWS_Fls_00345] */
        if((MEMIF_JOB_PENDING == gFls_JobResult) && (gFls_JobAddrIt > gFls_JobAddrEnd))
        {
            gFls_JobResult = MEMIF_JOB_OK;
        }
       
        if( MEMIF_JOB_OK == eFls_WorkResult )
        {
            gFls_ModuleStatus = MEMIF_IDLE;
            if( NULL_PTR != gFls_ConfigPtr->jobEndNotificationPtr )
            {
                /* Specification of Flash Driver : [SWS_Fls_00193] */
                gFls_ConfigPtr->jobEndNotificationPtr();/* polyspace RTE:COR */
            }
        }
        else if(( MEMIF_JOB_FAILED == eFls_WorkResult ) \
                || ( MEMIF_BLOCK_INCONSISTENT == eFls_WorkResult ))
        {
        	 gFls_ModuleStatus = MEMIF_IDLE;
            if( NULL_PTR != gFls_ConfigPtr->jobErrorNotificationPtr )
            {
                /* Specification of Flash Driver : [SWS_Fls_00193] */
                gFls_ConfigPtr->jobErrorNotificationPtr();/* polyspace RTE:COR */
            }
        }
        else
        {
            //do nothing
        }
    }
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
