
/* PRQA S 2053,0380,0305 EOF */ 
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
*   @file    Fls_Cfg.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of FLS MCAL driver.
*
*   @addtogroup FLS
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

#include "Fls_Cfg.h"

#define FLS_VENDOR_ID_PLUGIN_CFG_C          176
#define FLS_AR_REL_MAJOR_VER_CFG_C          4
#define FLS_AR_REL_MINOR_VER_CFG_C          4
#define FLS_AR_REL_REVISION_VER_CFG_C       0
#define FLS_SW_MAJOR_VERSION_CFG_C          3
#define FLS_SW_MINOR_VERSION_CFG_C          0
#define FLS_SW_PATCH_VERSION_CFG_C          0

#if (MCAL_VENDOR_ID != FLS_VENDOR_ID_PLUGIN_CFG_C)
    #error " NON-MATCHED DATA : FLS_VENDOR_ID_PLUGIN_CFG_C "
#endif
#if (MCAL_AR_RELEASE_MAJOR_VERSION != FLS_AR_REL_MAJOR_VER_CFG_C)
    #error " NON-MATCHED DATA : FLS_AR_REL_MAJOR_VER_CFG_C "
#endif
#if (MCAL_AR_RELEASE_MINOR_VERSION != FLS_AR_REL_MINOR_VER_CFG_C)
    #error " NON-MATCHED DATA : FLS_AR_REL_MINOR_VER_CFG_C "
#endif
#if (MCAL_AR_RELEASE_REVISION_VERSION != FLS_AR_REL_REVISION_VER_CFG_C)
    #error " NON-MATCHED DATA : FLS_AR_REL_REVISION_VER_CFG_C "
#endif
#if (MCAL_SW_MAJOR_VERSION != FLS_SW_MAJOR_VERSION_CFG_C)
    #error " NON-MATCHED DATA : FLS_SW_MAJOR_VERSION_CFG_C "
#endif
#if (MCAL_SW_MINOR_VERSION != FLS_SW_MINOR_VERSION_CFG_C)
    #error " NON-MATCHED DATA : FLS_SW_MINOR_VERSION_CFG_C "
#endif
#if (MCAL_SW_PATCH_VERSION != FLS_SW_PATCH_VERSION_CFG_C)
    #error " NON-MATCHED DATA : FLS_SW_PATCH_VERSION_CFG_C "
#endif

extern FUNC( void, FLS_CODE ) Fee_JobEndNotification( void );

extern FUNC( void, FLS_CODE ) Fee_JobErrorNotification( void );

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(Fls_AddressType, FLS_VAR) gFls_JobAddrIt = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(Fls_AddressType, FLS_VAR) gFls_JobAddrEnd = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(volatile Fls_SectorIndex_Type, FLS_VAR) gFls_JobSectorIt = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(Fls_SectorIndex_Type, FLS_VAR) gFls_JobSectorEnd = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(uint8, FLS_VAR) gFls_JobStart = 0U;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(uint32, FLS_VAR) gFls_MaxRead = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(uint32, FLS_VAR) gFls_MaxWrite = 0UL;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(MemIf_StatusType, FLS_VAR) gFls_ModuleStatus = MEMIF_UNINIT;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(MemIf_JobResultType, FLS_VAR) gFls_JobResult = MEMIF_JOB_OK;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(Fls_Job_Type, FLS_VAR) gFls_Job = FLS_JOB_ERASE;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(volatile MemIf_JobResultType, FLS_VAR) gFls_LLDJobResult = MEMIF_JOB_OK;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT
#include "Fls_MemMap.h"
VAR(Fls_LLDJob_Type, FLS_VAR) gFls_LLDJob = FLASH_JOB_NONE;
#define FLS_STOP_SEC_VAR_INIT
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(uint8, FLS_CONST) FlsConfig_FlsSectorFlags[63] =
{
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_0) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_1) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_2) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_3) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_4) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_5) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_6) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_7) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_8) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_9) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_10) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_11) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_12) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_13) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_14) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_15) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_16) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_17) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_18) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_19) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_20) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_21) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_22) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_23) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_24) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_25) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_26) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_27) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_28) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_29) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_30) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_31) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_32) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_33) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_34) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_35) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_36) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_37) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_38) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_39) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_40) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_41) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_42) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_43) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_44) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_45) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_46) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_47) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_48) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_49) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_50) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_51) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_52) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_53) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_54) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_55) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_56) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_57) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_58) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_59) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_60) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH, /* (FlsSector_61) */
    FLS_SECTOR_ERASE_ASYNCH |FLS_PAGE_WRITE_ASYNCH /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(uint16, FLS_CONST) FlsConfig_FlsSectorUnlock[63] =
{
    0U, /* (FlsSector_0) */
    1U, /* (FlsSector_1) *//* WangM for Boot*/
    0U, /* (FlsSector_2) */
    0U, /* (FlsSector_3) */
    0U, /* (FlsSector_4) */
    0U, /* (FlsSector_5) */
    0U, /* (FlsSector_6) */
    1U, /* (FlsSector_7) */
    1U, /* (FlsSector_8) */
    1U, /* (FlsSector_9) */
    1U, /* (FlsSector_10) */
    1U, /* (FlsSector_11) */
    1U, /* (FlsSector_12) */
    1U, /* (FlsSector_13) */
    1U, /* (FlsSector_14) */
    0U, /* (FlsSector_15) */
    0U, /* (FlsSector_16) */
    0U, /* (FlsSector_17) */
    0U, /* (FlsSector_18) */
    0U, /* (FlsSector_19) */
    0U, /* (FlsSector_20) */
    0U, /* (FlsSector_21) */
    0U, /* (FlsSector_22) */
    0U, /* (FlsSector_23) */
    0U, /* (FlsSector_24) */
    0U, /* (FlsSector_25) */
    0U, /* (FlsSector_26) */
    0U, /* (FlsSector_27) */
    0U, /* (FlsSector_28) */
    0U, /* (FlsSector_29) */
    0U, /* (FlsSector_30) */
    0U, /* (FlsSector_31) */
    0U, /* (FlsSector_32) */
    0U, /* (FlsSector_33) */
    0U, /* (FlsSector_34) */
    0U, /* (FlsSector_35) */
    0U, /* (FlsSector_36) */
    0U, /* (FlsSector_37) */
    0U, /* (FlsSector_38) */
    0U, /* (FlsSector_39) */
    0U, /* (FlsSector_40) */
    1U, /* (FlsSector_41) *//* WangM for Calibration*/
    1U, /* (FlsSector_42) *//* WangM for Calibration*/
    1U, /* (FlsSector_43) *//* WangM for Calibration*/
    0U, /* (FlsSector_44) */
    0U, /* (FlsSector_45) */
    0U, /* (FlsSector_46) */
    0U, /* (FlsSector_47) */
    0U, /* (FlsSector_48) */
    0U, /* (FlsSector_49) */
    0U, /* (FlsSector_50) */
    0U, /* (FlsSector_51) */
    0U, /* (FlsSector_52) */
    0U, /* (FlsSector_53) */
    0U, /* (FlsSector_54) */
    0U, /* (FlsSector_55) */
    0U, /* (FlsSector_56) */
    0U, /* (FlsSector_57) */
    0U, /* (FlsSector_58) */
    0U, /* (FlsSector_59) */
    0U, /* (FlsSector_60) */
    0U, /* (FlsSector_61) */
    0U, /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(Fls_AddressType, FLS_CONST) FlsConfig_FlsSectorEndAddr[63] =
{
    0x3fff, /* (FlsSector_0) */
    0x7fff, /* (FlsSector_1) */
    0xbfff, /* (FlsSector_2) */
    0xffff, /* (FlsSector_3) */
    0x17fff, /* (FlsSector_4) */
    0x27fff, /* (FlsSector_5) */
    0x37fff, /* (FlsSector_6) */
    0x47fff, /* (FlsSector_7) */
    0x57fff, /* (FlsSector_8) */
    0x67fff, /* (FlsSector_9) */
    0x77fff, /* (FlsSector_10) */
    0x87fff, /* (FlsSector_11) */
    0x97fff, /* (FlsSector_12) */
    0xa7fff, /* (FlsSector_13) */
    0xb7fff, /* (FlsSector_14) */
    0xf7fff, /* (FlsSector_15) */
    0x137fff, /* (FlsSector_16) */
    0x177fff, /* (FlsSector_17) */
    0x1b7fff, /* (FlsSector_18) */
    0x1f7fff, /* (FlsSector_19) */
    0x237fff, /* (FlsSector_20) */
    0x277fff, /* (FlsSector_21) */
    0x2b7fff, /* (FlsSector_22) */
    0x2f7fff, /* (FlsSector_23) */
    0x337fff, /* (FlsSector_24) */
    0x377fff, /* (FlsSector_25) */
    0x3b7fff, /* (FlsSector_26) */
    0x3f7fff, /* (FlsSector_27) */
    0x437fff, /* (FlsSector_28) */
    0x477fff, /* (FlsSector_29) */
    0x4b7fff, /* (FlsSector_30) */
    0x4f7fff, /* (FlsSector_31) */
    0x537fff, /* (FlsSector_32) */
    0x577fff, /* (FlsSector_33) */
    0x5b7fff, /* (FlsSector_34) */
    0x5f7fff, /* (FlsSector_35) */
    0x637fff, /* (FlsSector_36) */
    0x677fff, /* (FlsSector_37) */
    0x6b7fff, /* (FlsSector_38) */
    0x6f7fff, /* (FlsSector_39) */
    0x737fff, /* (FlsSector_40) */
    0x777fff, /* (FlsSector_41) */
    0x7b7fff, /* (FlsSector_42) */
    0x7f7fff, /* (FlsSector_43) */
    0x837fff, /* (FlsSector_44) */
    0x877fff, /* (FlsSector_45) */
    0x8b7fff, /* (FlsSector_46) */
    0x8f7fff, /* (FlsSector_47) */
    0x937fff, /* (FlsSector_48) */
    0x977fff, /* (FlsSector_49) */
    0x9b7fff, /* (FlsSector_50) */
    0x9f7fff, /* (FlsSector_51) */
    0xa37fff, /* (FlsSector_52) */
    0xa77fff, /* (FlsSector_53) */
    0xab7fff, /* (FlsSector_54) */
    0xaf7fff, /* (FlsSector_55) */
    0xb37fff, /* (FlsSector_56) */
    0xb77fff, /* (FlsSector_57) */
    0xbb7fff, /* (FlsSector_58) */
    0xbf7fff, /* (FlsSector_59) */
    0xc37fff, /* (FlsSector_60) */
    0xc77fff, /* (FlsSector_61) */
    0xcb7fff, /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(Fls_AddressType, FLS_CONST) FlsConfig_FlsSectorStartAddr[63] = 
{
    0x0, /* (FlsSector_0) */
    0x4000, /* (FlsSector_1) */
    0x8000, /* (FlsSector_2) */
    0xc000, /* (FlsSector_3) */
    0x10000, /* (FlsSector_4) */
    0x18000, /* (FlsSector_5) */
    0x28000, /* (FlsSector_6) */
    0x38000, /* (FlsSector_7) */
    0x48000, /* (FlsSector_8) */
    0x58000, /* (FlsSector_9) */
    0x68000, /* (FlsSector_10) */
    0x78000, /* (FlsSector_11) */
    0x88000, /* (FlsSector_12) */
    0x98000, /* (FlsSector_13) */
    0xa8000, /* (FlsSector_14) */
    0xb8000, /* (FlsSector_15) */
    0xf8000, /* (FlsSector_16) */
    0x138000, /* (FlsSector_17) */
    0x178000, /* (FlsSector_18) */
    0x1b8000, /* (FlsSector_19) */
    0x1f8000, /* (FlsSector_20) */
    0x238000, /* (FlsSector_21) */
    0x278000, /* (FlsSector_22) */
    0x2b8000, /* (FlsSector_23) */
    0x2f8000, /* (FlsSector_24) */
    0x338000, /* (FlsSector_25) */
    0x378000, /* (FlsSector_26) */
    0x3b8000, /* (FlsSector_27) */
    0x3f8000, /* (FlsSector_28) */
    0x438000, /* (FlsSector_29) */
    0x478000, /* (FlsSector_30) */
    0x4b8000, /* (FlsSector_31) */
    0x4f8000, /* (FlsSector_32) */
    0x538000, /* (FlsSector_33) */
    0x578000, /* (FlsSector_34) */
    0x5b8000, /* (FlsSector_35) */
    0x5f8000, /* (FlsSector_36) */
    0x638000, /* (FlsSector_37) */
    0x678000, /* (FlsSector_38) */
    0x6b8000, /* (FlsSector_39) */
    0x6f8000, /* (FlsSector_40) */
    0x738000, /* (FlsSector_41) */
    0x778000, /* (FlsSector_42) */
    0x7b8000, /* (FlsSector_43) */
    0x7f8000, /* (FlsSector_44) */
    0x838000, /* (FlsSector_45) */
    0x878000, /* (FlsSector_46) */
    0x8b8000, /* (FlsSector_47) */
    0x8f8000, /* (FlsSector_48) */
    0x938000, /* (FlsSector_49) */
    0x978000, /* (FlsSector_50) */
    0x9b8000, /* (FlsSector_51) */
    0x9f8000, /* (FlsSector_52) */
    0xa38000, /* (FlsSector_53) */
    0xa78000, /* (FlsSector_54) */
    0xab8000, /* (FlsSector_55) */
    0xaf8000, /* (FlsSector_56) */
    0xb38000, /* (FlsSector_57) */
    0xb78000, /* (FlsSector_58) */
    0xbb8000, /* (FlsSector_59) */
    0xbf8000, /* (FlsSector_60) */
    0xc38000, /* (FlsSector_61) */
    0xc78000, /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(Fls_LengthType, FLS_CONST) FlsConfig_FlsPageSize[63] =
{
    8UL, /* (FlsSector_0) */
    8UL, /* (FlsSector_1) */
    8UL, /* (FlsSector_2) */
    8UL, /* (FlsSector_3) */
    8UL, /* (FlsSector_4) */
    8UL, /* (FlsSector_5) */
    8UL, /* (FlsSector_6) */
    8UL, /* (FlsSector_7) */
    8UL, /* (FlsSector_8) */
    8UL, /* (FlsSector_9) */
    8UL, /* (FlsSector_10) */
    8UL, /* (FlsSector_11) */
    8UL, /* (FlsSector_12) */
    8UL, /* (FlsSector_13) */
    8UL, /* (FlsSector_14) */
    8UL, /* (FlsSector_15) */
    8UL, /* (FlsSector_16) */
    8UL, /* (FlsSector_17) */
    8UL, /* (FlsSector_18) */
    8UL, /* (FlsSector_19) */
    8UL, /* (FlsSector_20) */
    8UL, /* (FlsSector_21) */
    8UL, /* (FlsSector_22) */
    8UL, /* (FlsSector_23) */
    8UL, /* (FlsSector_24) */
    8UL, /* (FlsSector_25) */
    8UL, /* (FlsSector_26) */
    8UL, /* (FlsSector_27) */
    8UL, /* (FlsSector_28) */
    8UL, /* (FlsSector_29) */
    8UL, /* (FlsSector_30) */
    8UL, /* (FlsSector_31) */
    8UL, /* (FlsSector_32) */
    8UL, /* (FlsSector_33) */
    8UL, /* (FlsSector_34) */
    8UL, /* (FlsSector_35) */
    8UL, /* (FlsSector_36) */
    8UL, /* (FlsSector_37) */
    8UL, /* (FlsSector_38) */
    8UL, /* (FlsSector_39) */
    8UL, /* (FlsSector_40) */
    8UL, /* (FlsSector_41) */
    8UL, /* (FlsSector_42) */
    8UL, /* (FlsSector_43) */
    8UL, /* (FlsSector_44) */
    8UL, /* (FlsSector_45) */
    8UL, /* (FlsSector_46) */
    8UL, /* (FlsSector_47) */
    8UL, /* (FlsSector_48) */
    8UL, /* (FlsSector_49) */
    8UL, /* (FlsSector_50) */
    8UL, /* (FlsSector_51) */
    8UL, /* (FlsSector_52) */
    8UL, /* (FlsSector_53) */
    8UL, /* (FlsSector_54) */
    8UL, /* (FlsSector_55) */
    8UL, /* (FlsSector_56) */
    8UL, /* (FlsSector_57) */
    8UL, /* (FlsSector_58) */
    8UL, /* (FlsSector_59) */
    8UL, /* (FlsSector_60) */
    8UL, /* (FlsSector_61) */
    8UL, /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
static CONST(Fls_PhysicalSector_Type, FLS_CONST) FlsConfig_FlsPhysicalSector[63] =
{
    FLS_DATA_L1, /* (FlsSector_0) */
    FLS_DATA_L2, /* (FlsSector_1) */
    FLS_DATA_L3, /* (FlsSector_2) */
    FLS_DATA_L4, /* (FlsSector_3) */
    FLS_DATA_L6, /* (FlsSector_4) */
    FLS_DATA_L8, /* (FlsSector_5) */
    FLS_DATA_L9, /* (FlsSector_6) */
    FLS_DATA_H0, /* (FlsSector_7) */
    FLS_DATA_H1, /* (FlsSector_8) */
    FLS_DATA_H2, /* (FlsSector_9) */
    FLS_DATA_H3, /* (FlsSector_10) */
    FLS_DATA_H4, /* (FlsSector_11) */
    FLS_DATA_H5, /* (FlsSector_12) */
    FLS_DATA_H6, /* (FlsSector_13) */
    FLS_DATA_H7, /* (FlsSector_14) */
    FLS_DATA_B0, /* (FlsSector_15) */
    FLS_DATA_B1, /* (FlsSector_16) */
    FLS_DATA_B2, /* (FlsSector_17) */
    FLS_DATA_B3, /* (FlsSector_18) */
    FLS_DATA_B4, /* (FlsSector_19) */
    FLS_DATA_B5, /* (FlsSector_20) */
    FLS_DATA_B6, /* (FlsSector_21) */
    FLS_DATA_B7, /* (FlsSector_22) */
    FLS_DATA_B8, /* (FlsSector_23) */
    FLS_DATA_B9, /* (FlsSector_24) */
    FLS_DATA_B10, /* (FlsSector_25) */
    FLS_DATA_B11, /* (FlsSector_26) */
    FLS_DATA_B12, /* (FlsSector_27) */
    FLS_DATA_B13, /* (FlsSector_28) */
    FLS_DATA_B14, /* (FlsSector_29) */
    FLS_DATA_B15, /* (FlsSector_30) */
    FLS_DATA_B16, /* (FlsSector_31) */
    FLS_DATA_B17, /* (FlsSector_32) */
    FLS_DATA_B18, /* (FlsSector_33) */
    FLS_DATA_B19, /* (FlsSector_34) */
    FLS_DATA_B20, /* (FlsSector_35) */
    FLS_DATA_B21, /* (FlsSector_36) */
    FLS_DATA_B22, /* (FlsSector_37) */
    FLS_DATA_B23, /* (FlsSector_38) */
    FLS_DATA_B24, /* (FlsSector_39) */
    FLS_DATA_B25, /* (FlsSector_40) */
    FLS_DATA_B26, /* (FlsSector_41) */
    FLS_DATA_B27, /* (FlsSector_42) */
    FLS_DATA_B28, /* (FlsSector_43) */
    FLS_DATA_B29, /* (FlsSector_44) */
    FLS_DATA_B30, /* (FlsSector_45) */
    FLS_DATA_B31, /* (FlsSector_46) */
    FLS_DATA_B32, /* (FlsSector_47) */
    FLS_DATA_B33, /* (FlsSector_48) */
    FLS_DATA_B34, /* (FlsSector_49) */
    FLS_DATA_B35, /* (FlsSector_50) */
    FLS_DATA_B36, /* (FlsSector_51) */
    FLS_DATA_B37, /* (FlsSector_52) */
    FLS_DATA_B38, /* (FlsSector_53) */
    FLS_DATA_B39, /* (FlsSector_54) */
    FLS_DATA_B40, /* (FlsSector_55) */
    FLS_DATA_B41, /* (FlsSector_56) */
    FLS_DATA_B42, /* (FlsSector_57) */
    FLS_DATA_B43, /* (FlsSector_58) */
    FLS_DATA_B44, /* (FlsSector_59) */
    FLS_DATA_B45, /* (FlsSector_60) */
    FLS_DATA_B46, /* (FlsSector_61) */
    FLS_DATA_B47, /* (FlsSector_62) */
};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA
#include "Fls_MemMap.h"
CONST(Fls_ConfigType, FLS_CONST) Fls_Config =
{
    (Fls_AcErasePtrType)1074528128,/* FlsAcErase */
    (Fls_AcWritePtrType)1074528128,/* FlsAcWrite */
    0.0,/* FlsCallCycle */
    MEMIF_MODE_FAST,/* FlsDefaultMode */
    1048576U,/* FlsMaxReadFastMode */
    1024U,/* FlsMaxReadNormalMode */
    256U,/* FlsMaxWriteFastMode */
    8U,/* FlsMaxWriteNormalMode */
    NULL_PTR,/* FlsEndNotification */
    NULL_PTR,/* FlsErrorNotification */
    63U,/* FlsSectorCount */
    &FlsConfig_FlsSectorStartAddr,/* FlsSectorStartAddr */
    &FlsConfig_FlsSectorEndAddr,/* FlsSectorEndAddr */
    &FlsConfig_FlsPhysicalSector,/* FlsPhysicalSector */
    &FlsConfig_FlsSectorFlags,/* FlsSectorFlags */
    &FlsConfig_FlsSectorUnlock,/* FlsSectorUnlock */
    &FlsConfig_FlsPageSize,/* FlsPageSize */
	NULL_PTR

};
#define FLS_STOP_SEC_CONFIG_DATA
#include "Fls_MemMap.h"



#ifdef __cplusplus
}
#endif
