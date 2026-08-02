/*
********************************************************************************
*
* File name: NvM_Cfg.c
*
* Copyright 2018-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 130
* Author/Date: WangJP/2021.08.14
* Change: New created.
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: LQiao/2022.12.27
* Change: Default Value changed in NvM_Block_Descriptor_Table.
          Rule changed.(v13.5(SWRD_NvM_Cfg.c_CodeRule_016)-- CCOREDBUG-1616).
* Cause: Bugfix
********************************************************************************
* Version: 3.1
* Author/Date: WangLX/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "NvM_Cfg.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#define NVM_SIZEOF_RAMBLOCK_LENGTH_2             (sizeof(dsm_nvm_data))
#define NVM_SIZEOF_RAMBLOCK_LENGTH_3             (sizeof(app_nvm_data))
#define NVM_SIZEOF_RAMBLOCK_LENGTH_4             (sizeof(data_nvm_onfly))

/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define NVM_START_SEC_VAR_INIT
#include "NvM_MemMap.h"

VAR(uint8, NVM_VAR_INIT) NvM_CompiledConfigId[NVM_COMPILEDCONFIGID_LENGHT] = {0U, 0U};

#define NVM_STOP_SEC_VAR_INIT
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_NO_INIT
#include "NvM_MemMap.h"

VAR(Nvm_BlockManagment_st, NVM_VAR_NO_INIT) NvM_gstaBlockVar[NVM_NUM_OF_BLOCK_TOTAL];
VAR(Nvm_BlockAdministrator_st, NVM_VAR_NO_INIT) NvM_gstaBlockAdmini[NVM_NUM_OF_BLOCK_TOTAL];
/* Internal ram is used to integrate user data and CRC */
VAR(uint8, NVM_VAR_NO_INIT) Nvm_InternalBuffer[NVM_BLOCK_MAX_LENGTH];

#define NVM_STOP_SEC_VAR_NO_INIT
#include "NvM_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define NVM_START_SEC_CONFIG_DATA
#include "NvM_MemMap.h"

CONST(NvM_Block_Descriptor_Table_st, NVM_CONFIG_DATA) NvM_Block_Descriptor_Table[NVM_NUM_OF_BLOCK_TOTAL] =
{
    {
        0U,                                /* Nv Block ID (BlockId >= 1). */
        NVM_BLOCKLEN_AUTOCAL_OFF,          /* Define whether enable auto block length calculate. */
        NVM_BLOCK_CRC_UNUSE,               /* Checksum Algorithm Type. */
        NVM_BLOCK_MANAGENMENT_NATIVE,      /* Mangment type. */
        NVM_BLOCK_AUTO_VALID_OFF,
        NVM_BLOCK_CRC_COMP_OFF,            /* Defines whether the CRC of the RAM Block shall be compared. */
        NVM_BLOCK_USE_SYNC_MECHANISM_OFF,  /* Defines whether synchronization mechanism is used, used the callback. */
        NVM_BLOCK_WRITE_PROT_OFF,          /* Defines an initial write protection of the NV block. */
        0U,                                /* Defines the maximum number of read retries. */
        0U,                                /* Defines the maximum number of write retries for a NVRAM block. */
        NVM_BSWM_INFORMATION_OFF,          /* informed BswM he current status of the specified block. */
        NVM_CALC_RAM_BLOCK_CRC_OFF,        /* Defines CRC usage for the NVRAM block. */
        1U,                                /* EA or FEE. */
        NVM_RESISTANT_TO_CHANGED_SW_OFF,   /* Defines whether a NVRAM block shall be treated resistant to configuration changes or not. */
        NVM_SELECT_BLOCK_4_READALL_OFF,    /* Defines whether a NVRAM block shall be processed during NvM_ReadAll or not. */
        NVM_SELECT_BLOCK_4_WRITEALL_OFF,   /* Defines whether a NVRAM block shall be processed during NvM_WriteAll or not. */
        NVM_STATIC_BLOCK_ID_CHECK_OFF,     /* Reserved, Defines if the Static Block ID check is enabled. */
        NVM_WRITE_BLOCK_ONCE_OFF,          /* Defines write protection after first write. */
        NVM_BLOCK_SETBLOCKSTATUS_OFF,      /* Defines if NvMSetRamBlockStatusApi shall be used for this block or not. */
        NVM_WRITE_VERIFICATION_OFF,        /* Reserved, Defines if Write Verification is enabled. */
        0U,                                /* FEE/EA_BLOCK_NUMBER = (NvMNvBlockBaseNumber << NvMDatasetSelectionBits)+ DataIndex. */
        0U,                                /* Defines the NV block data length in bytes. */
        0U,
        0U,
        255U,                              /* Defines the job priority for a NVRAM block */
        0U,                                /* Defines the number of multiple NV blocks,DATASET 2-155, NATIVE 1, REDUNDANT 2. */
        0U,                                /* Reserved, Defines the number of multiple ROM blocks in a contiguous area according to the given block management type. */
        0U,                                /* Defines the number of bytes to compare in each step when comparing the content of a RAM Block and a block read back. */
        NULL_PTR,                          /* Ram Block buffer pointer. */
        NULL_PTR,                          /* Rom Block buffer pointer. */
        NULL_PTR,                          /* Init Callback function. */
        NULL_PTR,                          /* Read RamBlock From Nv Callback function. */
        NULL_PTR,                          /* WriteRamBlock To Nv Callback function. */
        NULL_PTR                           /* Job End Callback function. */
    },
    {
        1U,                                /* Nv Block ID (BlockId >= 1). */
        NVM_BLOCKLEN_AUTOCAL_OFF,          /* Define whether enable auto block length calculate. */
        NVM_BLOCK_CRC_8,                   /* Checksum Algorithm Type. */
        NVM_BLOCK_MANAGENMENT_REDUNDANT,   /* Mangment type. */
        NVM_BLOCK_AUTO_VALID_OFF,
        NVM_BLOCK_CRC_COMP_OFF,            /* Defines whether the CRC of the RAM Block shall be compared. */
        NVM_BLOCK_USE_SYNC_MECHANISM_OFF,  /* Defines whether synchronization mechanism is used, used the callback. */
        NVM_BLOCK_WRITE_PROT_OFF,          /* Defines an initial write protection of the NV block. */
        0U,                                /* Defines the maximum number of read retries. */
        0U,                                /* Defines the maximum number of write retries for a NVRAM block. */
        NVM_BSWM_INFORMATION_OFF,          /* informed BswM he current status of the specified block. */
        NVM_CALC_RAM_BLOCK_CRC_ON,         /* Defines CRC usage for the NVRAM block. */
        1U,                                /* EA or FEE. */
        NVM_RESISTANT_TO_CHANGED_SW_ON,   /* Defines whether a NVRAM block shall be treated resistant to configuration changes or not. */
        NVM_SELECT_BLOCK_4_READALL_ON,     /* Defines whether a NVRAM block shall be processed during NvM_ReadAll or not. */
        NVM_SELECT_BLOCK_4_WRITEALL_ON,    /* Defines whether a NVRAM block shall be processed during NvM_WriteAll or not. */
        NVM_STATIC_BLOCK_ID_CHECK_OFF,     /* Reserved, Defines if the Static Block ID check is enabled. */
        NVM_WRITE_BLOCK_ONCE_OFF,          /* Defines write protection after first write. */
        NVM_BLOCK_SETBLOCKSTATUS_OFF,      /* Defines if NvMSetRamBlockStatusApi shall be used for this block or not. */
        NVM_WRITE_VERIFICATION_OFF,        /* Reserved, Defines if Write Verification is enabled. */
	    4U,
        5U,                                /* Defines the NV block data length in bytes. */
        0U,
        0U,
        255U,                              /* Defines the job priority for a NVRAM block */
        2U,                                /* Defines the number of multiple NV blocks,DATASET 2-155, NATIVE 1, REDUNDANT 2. */
        0U,                                /* Reserved, Defines the number of multiple ROM blocks in a contiguous area according to the given block management type. */
        0U,                                /* Defines the number of bytes to compare in each step when comparing the content of a RAM Block and a block read back. */
        (uint8*)&NvM_CompiledConfigId,     /* Ram Block buffer pointer. */
        NULL_PTR,                          /* Rom Block buffer pointer. */
        NULL_PTR,                          /* Init Callback function. */
        NULL_PTR,                          /* Read RamBlock From Nv Callback function. */
        NULL_PTR,                          /* WriteRamBlock To Nv Callback function. */
        NULL_PTR                           /* Job End Callback function. */
    },
    {
        2U,
        NVM_BLOCKLEN_AUTOCAL_OFF,
        NVM_BLOCK_CRC_16,
        NVM_BLOCK_MANAGENMENT_NATIVE,
        NVM_BLOCK_AUTO_VALID_ON,
        NVM_BLOCK_CRC_COMP_ON,
        NVM_BLOCK_USE_SYNC_MECHANISM_OFF,
        NVM_BLOCK_WRITE_PROT_OFF,
        3U,
        3U,
        NVM_BSWM_INFORMATION_OFF,
        NVM_CALC_RAM_BLOCK_CRC_ON,
        1U,
        NVM_RESISTANT_TO_CHANGED_SW_ON,
        NVM_SELECT_BLOCK_4_READALL_ON,
        NVM_SELECT_BLOCK_4_WRITEALL_ON,
        NVM_STATIC_BLOCK_ID_CHECK_ON,
        NVM_WRITE_BLOCK_ONCE_OFF,
        NVM_BLOCK_SETBLOCKSTATUS_ON,
        NVM_WRITE_VERIFICATION_OFF,
        8U,
        32772U,
        32768U,
        NVM_SIZEOF_RAMBLOCK_LENGTH_2,
        0U,
        1U,
        1U,
        0U,
        (uint8*)&dsm_nvm_data,
        (uint8*)&dsm_default_data,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        3U,
        NVM_BLOCKLEN_AUTOCAL_OFF,
        NVM_BLOCK_CRC_16,
        NVM_BLOCK_MANAGENMENT_NATIVE,
        NVM_BLOCK_AUTO_VALID_ON,
        NVM_BLOCK_CRC_COMP_ON,
        NVM_BLOCK_USE_SYNC_MECHANISM_OFF,
        NVM_BLOCK_WRITE_PROT_OFF,
        3U,
        3U,
        NVM_BSWM_INFORMATION_OFF,
        NVM_CALC_RAM_BLOCK_CRC_ON,
        1U,
        NVM_RESISTANT_TO_CHANGED_SW_ON,
        NVM_SELECT_BLOCK_4_READALL_ON,
        NVM_SELECT_BLOCK_4_WRITEALL_ON,
        NVM_STATIC_BLOCK_ID_CHECK_ON,
        NVM_WRITE_BLOCK_ONCE_OFF,
        NVM_BLOCK_SETBLOCKSTATUS_ON,
        NVM_WRITE_VERIFICATION_OFF,
        12U,
        16388U,
        16384U,
        NVM_SIZEOF_RAMBLOCK_LENGTH_3,
        0U,
        1U,
        1U,
        0U,
        (uint8*)&app_nvm_data,
        (uint8*)&app_default_data,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },
    {
        4U,
        NVM_BLOCKLEN_AUTOCAL_OFF,
        NVM_BLOCK_CRC_16,
        NVM_BLOCK_MANAGENMENT_NATIVE,
        NVM_BLOCK_AUTO_VALID_ON,
        NVM_BLOCK_CRC_COMP_ON,
        NVM_BLOCK_USE_SYNC_MECHANISM_OFF,
        NVM_BLOCK_WRITE_PROT_OFF,
        3U,
        3U,
        NVM_BSWM_INFORMATION_OFF,
        NVM_CALC_RAM_BLOCK_CRC_ON,
        1U,
        NVM_RESISTANT_TO_CHANGED_SW_ON,
        NVM_SELECT_BLOCK_4_READALL_ON,
        NVM_SELECT_BLOCK_4_WRITEALL_ON,
        NVM_STATIC_BLOCK_ID_CHECK_ON,
        NVM_WRITE_BLOCK_ONCE_OFF,
        NVM_BLOCK_SETBLOCKSTATUS_ON,
        NVM_WRITE_VERIFICATION_OFF,
        16U,
        1028U,
        1024U,
        NVM_SIZEOF_RAMBLOCK_LENGTH_4,
        0U,
        1U,
        1U,
        0U,
        (uint8*)&data_nvm_onfly,
        (uint8*)&data_onfly_default,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
    },

};

#define NVM_STOP_SEC_CONFIG_DATA
#include "NvM_MemMap.h"

