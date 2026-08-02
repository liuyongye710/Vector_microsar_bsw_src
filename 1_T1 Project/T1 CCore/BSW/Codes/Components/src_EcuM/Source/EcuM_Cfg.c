/*
********************************************************************************
*
* File name: EcuM_Cfg.c
*
* Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
*  Version: 1.0
* Author/Date : yong.zhang/2019.11.26
*  Change: New created
*  Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: TianL/2024.8.5
* Change: Modify copyright.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "EcuM.h"

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
#define ECUM_START_SEC_GLOBAL_VAR_NO_INIT
#include "EcuM_MemMap.h"

#if( ECUM_WAKEUP_SOURCE_LIST > 0U )
VAR(uint32, ECUM_VAR_NO_INIT) EcuM_ValidationTimeoutArray[ECUM_WAKEUP_SOURCE_LIST];
#endif

#define ECUM_STOP_SEC_GLOBAL_VAR_NO_INIT
#include "EcuM_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define ECUM_START_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

#if( ECUM_WAKEUP_SOURCE_LIST > 0U )
CONST(EcuM_WakeupSourceListType, ECUM_CONFIG_DATA) EcuM_WakeupSourceList[ECUM_WAKEUP_SOURCE_LIST] =
{
    {0, 0, 0, (FALSE), 0xFF, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 1, (FALSE), 0xFF, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 2, (FALSE), 0xFF, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 3, (FALSE), 0xFF, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 4, (FALSE), 0xFF, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 5, (FALSE), 0, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 6, (FALSE), 1, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 7, (FALSE), 2, 0, ECUM_CORE_ID_MASTER},
    {0, 0, 8, (FALSE), 3, 0, ECUM_CORE_ID_MASTER},
};
#endif

#if( ECUM_GODOWN_ALLOWED_USER > 0U )
CONST(uint8, ECUM_CONFIG_DATA) EcuM_GoDownAllowedUser[ECUM_GODOWN_ALLOWED_USER]=
{
};
#endif

#if( ECUM_SLEEP_MODE_COUNT > 0U )
CONST(EcuM_SleepModeType, ECUM_CONFIG_DATA) Ecum_SleepMode[ECUM_SLEEP_MODE_COUNT] =
{
};
#endif

CONST(EcuM_ConfigType, ECUM_CONFIG_DATA) EcuM_Config = {0};


CONST(EcuM_ConfigParaType, ECUM_CONFIG_DATA) EcuM_ConfigParaData[ECUM_NUMBER_OF_CORES]={
	{0, ECUM_RESOURCE_CORE0},
	{1, ECUM_RESOURCE_CORE1},
	{2, ECUM_RESOURCE_CORE2},
};

#define ECUM_STOP_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

