/*
********************************************************************************
*
* File name: NvM_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 130
* Author/Date : WangJP/2021.08.14
* Change: New created.
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: WangLX/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.1
* Author/Date: WangLX/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef NVM_CFG_H_
#define NVM_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "NvM_Types.h"
#include "NvM_Def.h"
#include "Crc.h"
#include "Nvm_Appl.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define NVM_NUM_OF_BLOCK_TOTAL                               (5U)
#define NVM_BLOCK_REAL_NUMBER                                (NVM_NUM_OF_BLOCK_TOTAL - 1U)
#define NVM_BLOCK_REMAIN_NUMBER                              (NVM_BLOCK_REAL_NUMBER - 1U)
#define NVM_BLOCK_MAX_LENGTH                                 (32774U)
#define NVM_API_CONFIG_CLASS_1                               (1U)
#define NVM_API_CONFIG_CLASS_2                               (3U)
#define NVM_API_CONFIG_CLASS_3                               (7U)
#define NVM_API_CONFIG_CLASS                                 (NVM_API_CONFIG_CLASS_3)
#define NVM_CRC_NUM_OF_BYTES                                 (128U)
#define NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION          (STD_ON)
#define NVM_JOB_PRIORITIZATION                               (STD_ON)
#define NVM_POLLING_MODE                                     (STD_ON)
#define NVM_REPEAT_MIRROR_OPERATIONS                         (3U)
#define NVM_SET_RAM_BLOCK_STATUS_API                         (STD_ON)
#define NVM_VERSION_INFO_API                                 (STD_OFF)
#define NVM_DRV_MODE_SWITCH                                  (STD_ON)
#define NVM_DEV_ERROR_DETECT                                 (STD_ON)
#define NVM_MULTI_BLOCK_CALLBACK                             (STD_OFF)
#define NVM_COMPILED_CONFIG_ID                               (1U)
#define NVM_DATASET_SELECTION_BITS                           (2U)
#define NVM_DYNAMIC_CONFIGURATION                            (STD_ON)
#define NVM_SIZE_IMMEDIATE_JOB_QUEUE                         (5U)
#define NVM_SIZE_STANDARD_JOB_QUEUE                          (5U)
#define NVM_MULTI_BLOCK_CALLBACK_ENABLE                      (STD_OFF)
#define NVM_WRITEVERIFY_ENABLE                               (STD_OFF)
#define NVM_WRITEVERIFY_LENGTH                               (0U)
#define NVM_BLOCKID_DSM_NVM_DATA_BLOCK (2U)
#define NVM_BLOCKID_APP_NVM_DATA_BLOCK (3U)
#define NVM_BLOCKID_DATA_NVM_ONFLY_BLOCK (4U)
#define NVM_STOP_SERVICES                                    (STD_OFF)
#define NVM_BLOCKID_MULTI            (0U)
#define NVM_BLOCKID_CONFIGURE        (1U)
#define NVM_RAM_GREATER_THAN_NV_1 ((sizeof(dsm_nvm_data) > (NVM_BLOCK_MAX_LENGTH - 6)) ? 0 : 1)
struct NvM_BlockLenCheck_1_Type
{
	uint8 dsm_nvm_data_block[NVM_RAM_GREATER_THAN_NV_1];
};
#define NVM_RAM_GREATER_THAN_NV_2 ((sizeof(app_nvm_data) > (NVM_BLOCK_MAX_LENGTH - 6)) ? 0 : 1)
struct NvM_BlockLenCheck_2_Type
{
	uint8 app_nvm_data_block[NVM_RAM_GREATER_THAN_NV_2];
};
#define NVM_RAM_GREATER_THAN_NV_3 ((sizeof(data_nvm_onfly) > (NVM_BLOCK_MAX_LENGTH - 6)) ? 0 : 1)
struct NvM_BlockLenCheck_3_Type
{
	uint8 data_nvm_onfly_block[NVM_RAM_GREATER_THAN_NV_3];
};

/*
********************************************************************************
*    Global Types
********************************************************************************
*/

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define NVM_START_SEC_VAR_INIT
#include "NvM_MemMap.h"

extern VAR(uint8, NVM_VAR_INIT) NvM_CompiledConfigId[NVM_COMPILEDCONFIGID_LENGHT];

#define NVM_STOP_SEC_VAR_INIT
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_NO_INIT
#include "NvM_MemMap.h"

extern VAR(Nvm_BlockManagment_st, NVM_VAR_NO_INIT) NvM_gstaBlockVar[NVM_NUM_OF_BLOCK_TOTAL];
extern VAR(Nvm_BlockAdministrator_st, NVM_VAR_NO_INIT) NvM_gstaBlockAdmini[NVM_NUM_OF_BLOCK_TOTAL];
extern VAR(uint8, NVM_VAR_NO_INIT) Nvm_InternalBuffer[NVM_BLOCK_MAX_LENGTH];

#define NVM_STOP_SEC_VAR_NO_INIT
#include "NvM_MemMap.h"
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define NVM_START_SEC_CONFIG_DATA
#include "NvM_MemMap.h"

extern CONST(NvM_Block_Descriptor_Table_st, NVM_CONFIG_DATA) NvM_Block_Descriptor_Table[NVM_NUM_OF_BLOCK_TOTAL];

#define NVM_STOP_SEC_CONFIG_DATA
#include "NvM_MemMap.h"

/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif /* NVM_CFG_H_ */

