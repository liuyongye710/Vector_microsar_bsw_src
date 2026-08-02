/* PRQA S 1535, 0722 EOF */
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
*   @file    Fls_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of FLS MCAL driver.
*
*   @addtogroup FLS
*   @{
*/

#ifndef FLS_CFG_H
#define FLS_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

#include "StandardTypes.h"
#include "MemIf_Types.h"
#include "Mcal.h"

#define FLS_VENDOR_ID_OUTPUT                      176
#define FLS_MODULE_ID_OUTPUT                      92
#define FLS_AR_REL_MAJOR_VER_OUTPUT               4
#define FLS_AR_REL_MINOR_VER_OUTPUT               4
#define FLS_AR_REL_REVISION_VER_OUTPUT            0
#define FLS_SW_MAJOR_VERSION_OUTPUT               3
#define FLS_SW_MINOR_VERSION_OUTPUT               0
#define FLS_SW_PATCH_VERSION_OUTPUT               0
#define FLS_INSTANCE                              0

#if (MCAL_VENDOR_ID != FLS_VENDOR_ID_OUTPUT)
    #error " NON-MATCHED DATA : FLS_VENDOR_ID_OUTPUT "
#endif
#if (MCAL_AR_RELEASE_MAJOR_VERSION != FLS_AR_REL_MAJOR_VER_OUTPUT)
    #error " NON-MATCHED DATA : FLS_AR_REL_MAJOR_VER_OUTPUT "
#endif
#if (MCAL_AR_RELEASE_MINOR_VERSION != FLS_AR_REL_MINOR_VER_OUTPUT)
    #error " NON-MATCHED DATA : FLS_AR_REL_MINOR_VER_OUTPUT "
#endif
#if (MCAL_AR_RELEASE_REVISION_VERSION != FLS_AR_REL_REVISION_VER_OUTPUT)
    #error " NON-MATCHED DATA : FLS_AR_REL_REVISION_VER_OUTPUT "
#endif
#if (MCAL_SW_MAJOR_VERSION != FLS_SW_MAJOR_VERSION_OUTPUT)
    #error " NON-MATCHED DATA : FLS_SW_MAJOR_VERSION_OUTPUT "
#endif
#if (MCAL_SW_MINOR_VERSION != FLS_SW_MINOR_VERSION_OUTPUT)
    #error " NON-MATCHED DATA : FLS_SW_MINOR_VERSION_OUTPUT "
#endif
#if (MCAL_SW_PATCH_VERSION != FLS_SW_PATCH_VERSION_OUTPUT)
    #error " NON-MATCHED DATA : FLS_SW_PATCH_VERSION_OUTPUT "
#endif

typedef uint32 Fls_SectorIndex_Type;

typedef uint32 Fls_AddressType;

/* Specification of Flash Driver : [SWS_Fls_00370] */
typedef uint32 Fls_LengthType;

typedef uint32 Fls_SectorCount_Type;

typedef P2FUNC( void, FLS_CODE, Fls_ACCallbackPtr_Type )  ( void );

typedef P2FUNC(void, FLS_CODE, Fls_JobEndNotificationPtr_Type)(void);

typedef P2FUNC(void, FLS_CODE, Fls_Error_NotificationPtr_Type)(void);

typedef P2FUNC(void, FLS_CODE, Fls_JobErrorNotificationPtr_Type)(void);

typedef P2FUNC( void, FLS_CODE, Fls_AcErasePtrTO_Type ) 
(
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) u32Fls_timerCounterAC
);
typedef P2FUNC( void, FLS_CODE, Fls_AcErasePtrNoTO_Type ) (void);

typedef P2FUNC( void, FLS_CODE, Fls_AcWritePtrTO_Type ) 
(
    P2VAR(volatile uint32, AUTOMATIC, FLS_CODE) u32Fls_timerCounterAC
);
typedef P2FUNC( void, FLS_CODE, Fls_AcWritePtrNoTO_Type ) (void);

typedef enum
{
    FLASH_JOB_NONE = 0,
    FLASH_JOB_ERASE,
    FLASH_JOB_ERASE_TEMP,
    FLASH_JOB_WRITE,
    FLASH_JOB_ERASE_BLANK_CHECK
} Fls_LLDJob_Type;

typedef enum
{
    FLS_JOB_ERASE = 0,
    FLS_JOB_WRITE,
    FLS_JOB_READ,
    FLS_JOB_COMPARE,
    FLS_JOB_BLANK_CHECK

} Fls_Job_Type;

typedef enum
{
    /* Low Block */
    FLS_DATA_L0,
    FLS_DATA_L1,
    FLS_DATA_L2,
    FLS_DATA_L3,
    FLS_DATA_L4,
    FLS_DATA_L5,
    FLS_DATA_L6,
    FLS_DATA_L7,
    FLS_DATA_L8,
    FLS_DATA_L9,
    FLS_DATA_L10,
    FLS_DATA_L11,
    /* Mid Block */
    FLS_DATA_M0,
    FLS_DATA_M1,
    FLS_DATA_M2,
    FLS_DATA_M3,
    FLS_DATA_M4,
    FLS_DATA_M5,
    FLS_DATA_M6,
    FLS_DATA_M7,
    /* High Block */
    FLS_DATA_H0,
    FLS_DATA_H1,
    FLS_DATA_H2,
    FLS_DATA_H3,
    FLS_DATA_H4,
    FLS_DATA_H5,
    FLS_DATA_H6,
    FLS_DATA_H7,
    /* 256K Block */
    FLS_DATA_B0,
    FLS_DATA_B1,
    FLS_DATA_B2,
    FLS_DATA_B3,
    FLS_DATA_B4,
    FLS_DATA_B5,
    FLS_DATA_B6,
    FLS_DATA_B7,
    FLS_DATA_B8,
    FLS_DATA_B9,
    FLS_DATA_B10,
    FLS_DATA_B11,
    FLS_DATA_B12,
    FLS_DATA_B13,
    FLS_DATA_B14,
    FLS_DATA_B15,
    FLS_DATA_B16,
    FLS_DATA_B17,
    FLS_DATA_B18,
    FLS_DATA_B19,
    FLS_DATA_B20,
    FLS_DATA_B21,
    FLS_DATA_B22,
    FLS_DATA_B23,
    FLS_DATA_B24,
    FLS_DATA_B25,
    FLS_DATA_B26,
    FLS_DATA_B27,
    FLS_DATA_B28,
    FLS_DATA_B29,
    FLS_DATA_B30,
    FLS_DATA_B31,
    FLS_DATA_B32,
    FLS_DATA_B33,
    FLS_DATA_B34,
    FLS_DATA_B35,
    FLS_DATA_B36,
    FLS_DATA_B37,
    FLS_DATA_B38,
    FLS_DATA_B39,
    FLS_DATA_B40,
    FLS_DATA_B41,
    FLS_DATA_B42,
    FLS_DATA_B43,
    FLS_DATA_B44,
    FLS_DATA_B45,
    FLS_DATA_B46,
    FLS_DATA_B47,
} Fls_PhysicalSector_Type;

typedef struct
{
    uint32 id;  
    uint32 status ;     
}Fls_ErrorType; 

extern VAR(Fls_AddressType, FLS_VAR) gFls_JobAddrIt;

extern VAR(Fls_AddressType, FLS_VAR) gFls_JobAddrEnd;

extern VAR(volatile MemIf_JobResultType, FLS_VAR) gFls_LLDJobResult;

extern VAR(Fls_LLDJob_Type, FLS_VAR) gFls_LLDJob;

extern VAR(volatile Fls_SectorIndex_Type, FLS_VAR) gFls_JobSectorIt;

extern VAR(Fls_SectorIndex_Type, FLS_VAR) gFls_JobSectorEnd;

extern VAR(uint8, FLS_VAR) gFls_JobStart;

extern VAR(uint32, FLS_VAR) gFls_MaxRead;

extern VAR(uint32, FLS_VAR) gFls_MaxWrite;

extern VAR(MemIf_StatusType, FLS_VAR) gFls_ModuleStatus;

extern VAR(MemIf_JobResultType, FLS_VAR) gFls_JobResult;

extern VAR(Fls_Job_Type, FLS_VAR) gFls_Job;

#define FLS_SECTOR_ERASE_ASYNCH     (1U)

#define FLS_PAGE_WRITE_ASYNCH       (2U)

#define FLS_PRECOMPILE_SUPPORT        (STD_OFF)

#define FLS_DEV_ERROR_DETECT        (STD_ON)

#define FLS_CANCEL_API        (STD_ON)

#define FLS_COMPARE_API        (STD_ON)

#define FLS_GET_JOB_RESULT_API        (STD_ON)

#define FLS_GET_STATUS_API        (STD_ON)

#define FLS_SET_MODE_API        (STD_ON)

#define FLS_VERSION_INFO_API        (STD_ON)

#define FLS_BLANK_CHECK_API        (STD_ON)

#define FLS_AC_LOAD_ON_JOB_START        (STD_OFF)

#define FLS_USE_INTERRUPTS        (STD_OFF)

#define FLS_ERASE_VERIFICATION_ENABLED        (STD_ON)

#define FLS_WRITE_VERIFICATION_ENABLED        (STD_ON)

#define FLS_INLINE     LOCAL_INLINE


#define FLS_TIMEOUT_SUPERVISION_ENABLED        (STD_ON)

#define FLS_ASYNC_WRITE_TIMEOUT_VALUE    0U

#define FLS_ASYNC_ERASE_TIMEOUT_VALUE    0U

#define FLS_SYNC_WRITE_TIMEOUT_VALUE    0U

#define FLS_SYNC_ERASE_TIMEOUT_VALUE    0U

#define FLS_AC_SIZE_ERASE    0x0U

#define FLS_AC_SIZE_WRITE    0x0U

#define FLS_ERASED_VALUE    0xffffffffU

#define FLS_BASE_ADDRESS 0U

#define FLS_PAGE_SIZE    8U

#define FLS_TOTAL_SIZE ((*(gFls_ConfigPtr->paSectorEndAddr))[gFls_ConfigPtr->u32SectorCount - 1U] + 1U)  /*polyspace RTE:OBAI*/


#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    /* access routine with timeout parameters */
    typedef Fls_AcErasePtrTO_Type Fls_AcErasePtrType;
    typedef Fls_AcWritePtrTO_Type Fls_AcWritePtrType;
#else
    /* access routine without timeout parameters */
    typedef Fls_AcErasePtrNoTO_Type Fls_AcErasePtrType;
    typedef Fls_AcWritePtrNoTO_Type Fls_AcWritePtrType;
#endif /* FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON */




typedef struct {
    Fls_AcErasePtrType acErasePtr;
    Fls_AcWritePtrType acWritePtr;
    float64   FlsCallCycle;
    VAR(MemIf_ModeType, FLS_VAR) eDefaultMode;
    Fls_LengthType u32MaxReadFastMode;
    Fls_LengthType u32MaxReadNormalMode;
    Fls_LengthType u32MaxWriteFastMode;
    Fls_LengthType u32MaxWriteNormalMode;
    Fls_JobEndNotificationPtr_Type jobEndNotificationPtr;
    Fls_JobErrorNotificationPtr_Type jobErrorNotificationPtr;
    Fls_SectorCount_Type u32SectorCount;
    CONST( Fls_AddressType, FLS_CONST) (*paSectorStartAddr)[]; 
    CONST( Fls_AddressType, FLS_CONST) (*paSectorEndAddr)[];
    CONST( Fls_PhysicalSector_Type, FLS_CONST) (*pSectorList)[];
    CONST( uint8, FLS_CONST) (*paSectorFlags)[];
    CONST( uint16, FLS_CONST ) (*sectorUnlock)[];
    CONST( Fls_LengthType, FLS_CONST) (*paSectorPageSize)[];
    Fls_Error_NotificationPtr_Type FlsRegErrorNotification;
} Fls_ConfigType;

extern CONST(Fls_ConfigType, FLS_CONST) Fls_Config;

#ifdef __cplusplus
}
#endif

#endif /* FLS_CFG_H */
