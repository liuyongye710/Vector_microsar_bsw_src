/*
********************************************************************************
*
* File name: Fee_Cfg.c
*
* Copyright 2018-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: WangJP/2020.08.14
* Change: new created.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: LiDaY/2024.08.27
* Change: Change copyright information.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Fee_Cfg.h"
#include "Fls.h"
/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
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
#define FEE_START_SEC_VAR_INIT
#include "Fee_MemMap.h"

static VAR(Fee_BlockHeadRamType, FEE_VAR_INIT) Fee_BlockHeadInfoDyn[FEE_BLOCK_NUMBER] =
{
	{0U}
};

static VAR(Fee_SectorHeadType, FEE_VAR_INIT) Fee_SectorHeadInfoDyn[FEE_SECTOR_NUMBER] =
{
	{0U}
};

static VAR(Fee_SectorCurrentInfoType, FEE_VAR_INIT) Fee_SectorCurrentInfo[FEE_SECTOR_NUMBER] =
{
    {
        FEE_SECTOR_FREE,
        0U,
        0U,
        0U,
        0U,
        0U,
        FALSE
    },
    {
        FEE_SECTOR_FREE,
        0U,
        0U,
        0U,
        0U,
        0U,
        FALSE
    }
};

#define FEE_STOP_SEC_VAR_INIT
#include "Fee_MemMap.h"

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

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define FEE_START_SEC_CONFIG_DATA
#include "Fee_MemMap.h"
	
static CONST(Fee_SectorHeadCfgType, FEE_CONFIG_DATA) Fee_SectorHeadCfg[FEE_SECTOR_NUMBER] =
{
	{
		1U,
		0x38000U,
		0x40000U,
		&Fee_SectorCurrentInfo[0U],
		&Fee_SectorHeadInfoDyn[0U]
	},
	{
		2U,
		0x78000U,
		0x40000U,
		&Fee_SectorCurrentInfo[1U],
		&Fee_SectorHeadInfoDyn[1U]
	}
};

	
static CONST(Fee_BlockCfgType, FEE_CONFIG_DATA) Fee_BlockCfg[FEE_BLOCK_NUMBER] =
{
	{
		FALSE,
		0U,
		0U,
		&Fee_BlockHeadInfoDyn[0U]
	},
	{
		FALSE,
		4U,
		5U,
		&Fee_BlockHeadInfoDyn[1U]
	},
	{
		FALSE,
		5U,
		5U,
		&Fee_BlockHeadInfoDyn[2U]
	},
	{
		TRUE,
		8U,
		32772U,
		&Fee_BlockHeadInfoDyn[3U]
	},
	{
		TRUE,
		12U,
		16388U,
		&Fee_BlockHeadInfoDyn[4U]
	},
	{
		TRUE,
		16U,
		1028U,
		&Fee_BlockHeadInfoDyn[5U]
	}
};

CONST(Fls_FunctionListType, FEE_CONFIG_DATA) Fls_FunctionListCfg =
{
    Fls_Erase,
    Fls_Write,
    Fls_Cancel,
    Fls_GetJobResult,
    Fls_Read,
    Fls_SetMode
};

CONST(Fee_PartitionCfgType, FEE_CONFIG_DATA) Fee_PartitionCfg =
{
    FEE_SECTOR_NUMBER,    /* Sector total number */
    FEE_BLOCK_NUMBER,    /* Block total number */
    &Fee_SectorHeadCfg[0U],
    &Fee_BlockCfg[0U],
    &Fls_FunctionListCfg
};

#define FEE_STOP_SEC_CONFIG_DATA
#include "Fee_MemMap.h"

