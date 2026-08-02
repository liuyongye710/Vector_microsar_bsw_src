/*
********************************************************************************
*
*  File name: PduR_Lcfg.c
*
*  Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: LuQ/2024.05.20
* Change: New create.
* Cause: New
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "PduR_Lcfg.h"
#include "PduR_Core.h"
#include "PduR_Router.h"
#include "PduR_PBcfg.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#define PDUR_CONFIGURATION_ID (1U)

#if (STD_OFF == PDUR_ZERO_COST_OPERATION)

#define PDUR_MAX_ROUTING_PATH_CNT (47U)
#define PDUR_MAX_ROUTING_PATH_GROUP_CNT (5U)
#define PDUR_MAX_ROUTING_TABLE_CNT (1U)
#define PDUR_DESTINATION_LIST_SIZE (47U)

#ifdef PDUR_SUPPORT_GETWAY

#define PDUR_TPBUFFER_LENGTH (0U)
#if PDUR_TPBUFFER_LENGTH >= (0xFFFFU)
#error PDUR_TPBUFFER_LENGTH exceeds the acceptable range.
#endif

#endif

#define PDUR_TXBUFFER_LENGTH (0U)
#if PDUR_TXBUFFER_LENGTH >= (0xFFFFU)
#error PDUR_TXBUFFER_LENGTH exceeds the acceptable range.
#endif

#define PDUR_BSW_MODLUES_LIST_SIZE (5U)

#if (STD_ON == PDUR_SUPPORT_MULTICORE)
#define PDUR_SHARE_BUFFER_SIZE (0U)
#endif /* #if (STD_ON == PDUR_SUPPORT_MULTICORE) */

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


#if ((STD_ON == PDUR_SUPPORT_GETWAY) || (defined PDUR_SUPPORT_TP_GETWAY))
/* Save the TP buffer status. */
#ifdef PDUR_SUPPORT_TP_GETWAY

#if ( PDUR_TPBUFFER_LENGTH > 0U )
#define PDUR_START_SEC_VAR_NO_INIT
#include "PduR_MemMap.h"
static PduR_TpBuffer_Type PduR_TpBufferStatus[PDUR_TPBUFFER_LENGTH];
#define PDUR_STOP_SEC_VAR_NO_INIT
#include "PduR_MemMap.h"
#endif  /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

#if ( PDUR_DESTINATION_LIST_SIZE > 0U )
#define PDUR_START_SEC_VAR_NO_INIT
#include "PduR_MemMap.h"
static PduRDstPduThreshold_Type PduR_DstPduThresholdList[PDUR_DESTINATION_LIST_SIZE];
#define PDUR_STOP_SEC_VAR_NO_INIT
#include "PduR_MemMap.h"
#endif  /* #if ( PDUR_DESTINATION_LIST_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_GETWAY */

#endif  /* #if ((STD_ON == PDUR_SUPPORT_GETWAY) || (defined PDUR_SUPPORT_TP_GETWAY)) */

#if (STD_ON == PDUR_SUPPORT_MULTICORE)

#endif	/* #if (STD_ON == PDUR_SUPPORT_MULTICORE) */

#if (STD_ON == PDUR_SUPPORT_GETWAY)

#ifdef PDUR_SUPPORT_TP_GETWAY

#if ( PDUR_TPBUFFER_LENGTH > 0U )


#endif  /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

#endif	/* #ifdef PDUR_SUPPORT_TP_GETWAY */

#if ( PDUR_TXBUFFER_LENGTH > 0U )


#endif  /* #if ( PDUR_TXBUFFER_LENGTH > 0U ) */

#define PDUR_START_SEC_GLOBAL_VAR_INIT
#include "PduR_MemMap.h"
static uint8 PduR_RoutingPathFlag[(PDUR_MAX_ROUTING_PATH_CNT / 8U) + (((PDUR_MAX_ROUTING_PATH_CNT % 8U) + 7U) / 8U)] = { 0U };
P2VAR(uint8, PDUR_VAR_INIT, PDUR_APPL_DATA) PduR_RoutingPathFlagTable = &PduR_RoutingPathFlag[0];
#define PDUR_STOP_SEC_GLOBAL_VAR_INIT
#include "PduR_MemMap.h"

/*
********************************************************************************
*    Local Constants
********************************************************************************
*/

#if ( PDUR_TXBUFFER_LENGTH > 0U )


#endif  /* #if ( PDUR_TXBUFFER_LENGTH > 0U ) */

#ifdef PDUR_SUPPORT_TP_GETWAY

#if ( PDUR_TPBUFFER_LENGTH > 0U )



#endif  /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

#endif /* #ifdef PDUR_SUPPORT_TP_GETWAY */

#endif

#if (STD_ON == PDUR_SUPPORT_MULTICORE)

#endif	/* #if (STD_ON == PDUR_SUPPORT_MULTICORE) */

	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRBswModules_Type PduRBswModules_List[PDUR_BSW_MODLUES_LIST_SIZE] =
{
	{
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_MODULE_ID_CANIF_IF,
	},
	{
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_MODULE_ID_CANTP_TP,
	},
	{
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_TRUE,
		PDUR_TRUE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_MODULE_ID_COM_UP,
	},
	{
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_MODULE_ID_DCM_UP,
	},
	{
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_TRUE,
		PDUR_FALSE,
		PDUR_FALSE,
		PDUR_MODULE_ID_J1939TP_TP,
	},
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type PduR_PduRDestinationList[PDUR_DESTINATION_LIST_SIZE] =
{
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		0U,
		0U,
		0U,
		0U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		1U,
		1U,
		0U,
		1U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		2U,
		2U,
		0U,
		1U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		3U,
		3U,
		0U,
		2U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		4U,
		4U,
		0U,
		3U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		5U,
		5U,
		0U,
		4U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		6U,
		6U,
		0U,
		6U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		7U,
		7U,
		0U,
		7U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		8U,
		8U,
		0U,
		5U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		9U,
		9U,
		0U,
		0U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		10U,
		10U,
		0U,
		1U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		11U,
		11U,
		0U,
		2U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		12U,
		12U,
		0U,
		3U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		13U,
		13U,
		0U,
		4U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		14U,
		14U,
		0U,
		5U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		15U,
		15U,
		0U,
		6U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		16U,
		16U,
		0U,
		7U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		17U,
		17U,
		0U,
		8U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		18U,
		18U,
		0U,
		9U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		19U,
		19U,
		0U,
		10U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		20U,
		20U,
		0U,
		11U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[1U],
		3U,
		21U,
		21U,
		0U,
		0U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[3U],
		1U,
		22U,
		22U,
		0U,
		0U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[3U],
		1U,
		23U,
		23U,
		0U,
		1U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		24U,
		24U,
		0U,
		13U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		25U,
		25U,
		0U,
		12U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		26U,
		26U,
		0U,
		13U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		27U,
		27U,
		0U,
		14U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		28U,
		28U,
		0U,
		14U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		29U,
		29U,
		0U,
		15U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		30U,
		30U,
		0U,
		30U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		31U,
		31U,
		0U,
		16U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		32U,
		32U,
		0U,
		32U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		33U,
		33U,
		0U,
		33U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		34U,
		34U,
		0U,
		17U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		35U,
		35U,
		0U,
		18U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		36U,
		36U,
		0U,
		19U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		37U,
		37U,
		0U,
		20U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		38U,
		38U,
		0U,
		21U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[0U],
		2U,
		39U,
		39U,
		0U,
		22U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_TRUE,
		&PduRBswModules_List[4U],
		4U,
		40U,
		40U,
		0U,
		40U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		41U,
		41U,
		0U,
		15U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		42U,
		42U,
		0U,
		16U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		43U,
		43U,
		0U,
		17U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		44U,
		44U,
		0U,
		18U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		45U,
		45U,
		0U,
		19U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
	{
		PDUR_FALSE,
		&PduRBswModules_List[2U],
		0U,
		46U,
		46U,
		0U,
		20U,
		PDUR_TP_THRESHOLD_INVALID,
		PDUR_DIRECT,
		NULL_PTR,
		NULL_PTR,
		PDUR_MUL_TAB_INVALID_IDX
	},
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_0[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		0U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_1[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		1U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_2[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		2U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_3[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		3U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_4[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		4U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_5[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		5U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_6[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		6U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_7[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		7U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_8[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		8U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_9[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		0U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_10[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		1U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_11[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		2U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_12[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		3U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_13[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		4U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_14[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		5U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_15[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		6U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_16[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		7U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_17[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		8U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_18[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		9U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_19[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		10U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_20[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		11U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_21[] =
{
	{
		&PduRBswModules_List[3U],
		0U,
		0U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_22[] =
{
	{
		&PduRBswModules_List[1U],
		0U,
		1U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_23[] =
{
	{
		&PduRBswModules_List[1U],
		0U,
		0U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_24[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		9U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_25[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		16U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_26[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		17U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_27[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		18U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_28[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		10U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_29[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		11U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_30[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		12U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_31[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		13U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_32[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		14U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_33[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		15U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_34[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		16U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_35[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		17U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_36[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		18U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_37[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		19U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_38[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		20U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_39[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		21U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_40[] =
{
	{
		&PduRBswModules_List[2U],
		0U,
		22U,
		PDUR_TRUE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_41[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		19U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_42[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		20U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_43[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		21U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_44[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		22U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_45[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		23U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRSrcPdu_Type PduR_Src_46[] =
{
	{
		&PduRBswModules_List[0U],
		0U,
		24U,
		PDUR_FALSE,
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_0[] =
{
	&PduR_PduRDestinationList[0U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_1[] =
{
	&PduR_PduRDestinationList[1U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_2[] =
{
	&PduR_PduRDestinationList[2U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_3[] =
{
	&PduR_PduRDestinationList[3U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_4[] =
{
	&PduR_PduRDestinationList[4U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_5[] =
{
	&PduR_PduRDestinationList[5U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_6[] =
{
	&PduR_PduRDestinationList[6U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_7[] =
{
	&PduR_PduRDestinationList[7U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_8[] =
{
	&PduR_PduRDestinationList[8U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_9[] =
{
	&PduR_PduRDestinationList[9U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_10[] =
{
	&PduR_PduRDestinationList[10U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_11[] =
{
	&PduR_PduRDestinationList[11U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_12[] =
{
	&PduR_PduRDestinationList[12U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_13[] =
{
	&PduR_PduRDestinationList[13U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_14[] =
{
	&PduR_PduRDestinationList[14U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_15[] =
{
	&PduR_PduRDestinationList[15U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_16[] =
{
	&PduR_PduRDestinationList[16U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_17[] =
{
	&PduR_PduRDestinationList[17U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_18[] =
{
	&PduR_PduRDestinationList[18U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_19[] =
{
	&PduR_PduRDestinationList[19U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_20[] =
{
	&PduR_PduRDestinationList[20U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_21[] =
{
	&PduR_PduRDestinationList[21U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_22[] =
{
	&PduR_PduRDestinationList[22U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_23[] =
{
	&PduR_PduRDestinationList[23U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_24[] =
{
	&PduR_PduRDestinationList[24U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_25[] =
{
	&PduR_PduRDestinationList[25U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_26[] =
{
	&PduR_PduRDestinationList[26U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_27[] =
{
	&PduR_PduRDestinationList[27U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_28[] =
{
	&PduR_PduRDestinationList[28U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_29[] =
{
	&PduR_PduRDestinationList[29U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_30[] =
{
	&PduR_PduRDestinationList[30U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_31[] =
{
	&PduR_PduRDestinationList[31U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_32[] =
{
	&PduR_PduRDestinationList[32U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_33[] =
{
	&PduR_PduRDestinationList[33U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_34[] =
{
	&PduR_PduRDestinationList[34U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_35[] =
{
	&PduR_PduRDestinationList[35U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_36[] =
{
	&PduR_PduRDestinationList[36U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_37[] =
{
	&PduR_PduRDestinationList[37U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_38[] =
{
	&PduR_PduRDestinationList[38U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_39[] =
{
	&PduR_PduRDestinationList[39U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_40[] =
{
	&PduR_PduRDestinationList[40U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_41[] =
{
	&PduR_PduRDestinationList[41U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_42[] =
{
	&PduR_PduRDestinationList[42U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_43[] =
{
	&PduR_PduRDestinationList[43U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_44[] =
{
	&PduR_PduRDestinationList[44U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_45[] =
{
	&PduR_PduRDestinationList[45U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduR_Dest_46[] =
{
	&PduR_PduRDestinationList[46U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRRoutingPath_Type PduR_RoutingPathTable[(PDUR_MAX_ROUTING_PATH_CNT + 1)] =
{
	{
		PduR_Dest_0,
		PduR_Src_0
	},
	{
		PduR_Dest_1,
		PduR_Src_1
	},
	{
		PduR_Dest_2,
		PduR_Src_2
	},
	{
		PduR_Dest_3,
		PduR_Src_3
	},
	{
		PduR_Dest_4,
		PduR_Src_4
	},
	{
		PduR_Dest_5,
		PduR_Src_5
	},
	{
		PduR_Dest_6,
		PduR_Src_6
	},
	{
		PduR_Dest_7,
		PduR_Src_7
	},
	{
		PduR_Dest_8,
		PduR_Src_8
	},
	{
		PduR_Dest_9,
		PduR_Src_9
	},
	{
		PduR_Dest_10,
		PduR_Src_10
	},
	{
		PduR_Dest_11,
		PduR_Src_11
	},
	{
		PduR_Dest_12,
		PduR_Src_12
	},
	{
		PduR_Dest_13,
		PduR_Src_13
	},
	{
		PduR_Dest_14,
		PduR_Src_14
	},
	{
		PduR_Dest_15,
		PduR_Src_15
	},
	{
		PduR_Dest_16,
		PduR_Src_16
	},
	{
		PduR_Dest_17,
		PduR_Src_17
	},
	{
		PduR_Dest_18,
		PduR_Src_18
	},
	{
		PduR_Dest_19,
		PduR_Src_19
	},
	{
		PduR_Dest_20,
		PduR_Src_20
	},
	{
		PduR_Dest_21,
		PduR_Src_21
	},
	{
		PduR_Dest_22,
		PduR_Src_22
	},
	{
		PduR_Dest_23,
		PduR_Src_23
	},
	{
		PduR_Dest_24,
		PduR_Src_24
	},
	{
		PduR_Dest_25,
		PduR_Src_25
	},
	{
		PduR_Dest_26,
		PduR_Src_26
	},
	{
		PduR_Dest_27,
		PduR_Src_27
	},
	{
		PduR_Dest_28,
		PduR_Src_28
	},
	{
		PduR_Dest_29,
		PduR_Src_29
	},
	{
		PduR_Dest_30,
		PduR_Src_30
	},
	{
		PduR_Dest_31,
		PduR_Src_31
	},
	{
		PduR_Dest_32,
		PduR_Src_32
	},
	{
		PduR_Dest_33,
		PduR_Src_33
	},
	{
		PduR_Dest_34,
		PduR_Src_34
	},
	{
		PduR_Dest_35,
		PduR_Src_35
	},
	{
		PduR_Dest_36,
		PduR_Src_36
	},
	{
		PduR_Dest_37,
		PduR_Src_37
	},
	{
		PduR_Dest_38,
		PduR_Src_38
	},
	{
		PduR_Dest_39,
		PduR_Src_39
	},
	{
		PduR_Dest_40,
		PduR_Src_40
	},
	{
		PduR_Dest_41,
		PduR_Src_41
	},
	{
		PduR_Dest_42,
		PduR_Src_42
	},
	{
		PduR_Dest_43,
		PduR_Src_43
	},
	{
		PduR_Dest_44,
		PduR_Src_44
	},
	{
		PduR_Dest_45,
		PduR_Src_45
	},
	{
		PduR_Dest_46,
		PduR_Src_46
	},
	{
		NULL_PTR,
		NULL_PTR
	}
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRRoutingTable_Type PduR_RoutingTable = { PduR_RoutingPathTable };
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

#if ( PDUR_MAX_ROUTING_PATH_GROUP_CNT > 0U )

	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduRRoutingPathGroup_Com[] =
{
	&PduR_PduRDestinationList[9U],
	&PduR_PduRDestinationList[10U],
	&PduR_PduRDestinationList[11U],
	&PduR_PduRDestinationList[12U],
	&PduR_PduRDestinationList[13U],
	&PduR_PduRDestinationList[14U],
	&PduR_PduRDestinationList[15U],
	&PduR_PduRDestinationList[16U],
	&PduR_PduRDestinationList[17U],
	&PduR_PduRDestinationList[18U],
	&PduR_PduRDestinationList[19U],
	&PduR_PduRDestinationList[20U],
	&PduR_PduRDestinationList[25U],
	&PduR_PduRDestinationList[26U],
	&PduR_PduRDestinationList[27U],
	&PduR_PduRDestinationList[42U],
	&PduR_PduRDestinationList[43U],
	&PduR_PduRDestinationList[44U],
	&PduR_PduRDestinationList[45U],
	&PduR_PduRDestinationList[46U],
	&PduR_PduRDestinationList[41U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduRRoutingPathGroup_Dcm[] =
{
	&PduR_PduRDestinationList[22U],
	&PduR_PduRDestinationList[23U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduRRoutingPathGroup_CanIf[] =
{
	&PduR_PduRDestinationList[0U],
	&PduR_PduRDestinationList[2U],
	&PduR_PduRDestinationList[3U],
	&PduR_PduRDestinationList[4U],
	&PduR_PduRDestinationList[5U],
	&PduR_PduRDestinationList[8U],
	&PduR_PduRDestinationList[24U],
	&PduR_PduRDestinationList[28U],
	&PduR_PduRDestinationList[29U],
	&PduR_PduRDestinationList[31U],
	&PduR_PduRDestinationList[34U],
	&PduR_PduRDestinationList[35U],
	&PduR_PduRDestinationList[36U],
	&PduR_PduRDestinationList[37U],
	&PduR_PduRDestinationList[38U],
	&PduR_PduRDestinationList[39U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduRRoutingPathGroup_CanTp[] =
{
	&PduR_PduRDestinationList[21U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
	
#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRDestPdu_Type* const PduRRoutingPathGroup_J1939Tp[] =
{
	&PduR_PduRDestinationList[1U],
	&PduR_PduRDestinationList[6U],
	&PduR_PduRDestinationList[7U],
	&PduR_PduRDestinationList[30U],
	&PduR_PduRDestinationList[32U],
	&PduR_PduRDestinationList[33U],
	&PduR_PduRDestinationList[40U],
	NULL_PTR
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

	
#define PDUR_START_SEC_VAR_INIT
#include "PduR_MemMap.h"
static PduRRoutingPathGroup_Type PduR_RoutingPathGroupList[PDUR_MAX_ROUTING_PATH_GROUP_CNT] =
{
	{
		PDUR_TRUE,
		0U,
		&PduRRoutingPathGroup_Com[0U]
	},
	{
		PDUR_TRUE,
		1U,
		&PduRRoutingPathGroup_Dcm[0U]
	},
	{
		PDUR_TRUE,
		2U,
		&PduRRoutingPathGroup_CanIf[0U]
	},
	{
		PDUR_TRUE,
		3U,
		&PduRRoutingPathGroup_CanTp[0U]
	},
	{
		PDUR_TRUE,
		4U,
		&PduRRoutingPathGroup_J1939Tp[0U]
	},
};
#define PDUR_STOP_SEC_VAR_INIT
#include "PduR_MemMap.h"

#endif  /* #if ( PDUR_MAX_ROUTING_PATH_GROUP_CNT > 0U ) */

#if (STD_ON == PDUR_SUPPORT_MULICAST)

#ifdef PDUR_SUPPORT_TP_MULICAST

#if ( PDUR_DESTINATION_TP_SIZE > 0U )


#endif  /* #if ( PDUR_DESTINATION_TP_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_MULICAST */

#ifdef PDUR_SUPPORT_IF_MULICAST

#if ( PDUR_DESTINATION_IF_SIZE > 0U )


#endif  /* #if ( PDUR_DESTINATION_IF_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_IF_MULICAST */

#endif  /* #if (STD_ON == PDUR_SUPPORT_MULICAST) */

#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"
static const PduRRoutingTables_Type PduR_RoutingTables = {

    PDUR_CONFIGURATION_ID,              /* .PduRConfigurationId */          /* 1..1 */
    PDUR_MAX_ROUTING_PATH_CNT,          /* .PduRMaxRoutingPathCnt */        /* 1..1 */
    PDUR_MAX_ROUTING_PATH_GROUP_CNT,    /* .PduRMaxRoutingPathGroupCnt */   /* 1..1 */
    PDUR_MAX_ROUTING_TABLE_CNT,         /* .PduRMaxRoutingTableCnt */       /* 1..1 */

#if ( PDUR_MAX_ROUTING_PATH_GROUP_CNT > 0U )
    &PduR_RoutingPathGroupList[0U],     /* .PduRRoutingPathGroup */
#else   /* #if ( PDUR_MAX_ROUTING_PATH_GROUP_CNT > 0U ) */
    NULL_PTR,
#endif  /* #if ( PDUR_MAX_ROUTING_PATH_GROUP_CNT > 0U ) */

    &PduR_RoutingTable,                 /* .PduRRoutingTable */
    PduR_PduRDestinationList,           /* .PduRDestPduList */

#if (STD_ON == PDUR_SUPPORT_GETWAY)

#ifdef PDUR_SUPPORT_TP_GETWAY

#if ( PDUR_DESTINATION_LIST_SIZE > 0U )
    &PduR_DstPduThresholdList[0U],      /* .PduRDstPduThrPtr */
#else   /* #if ( PDUR_DESTINATION_LIST_SIZE > 0U ) */
    NULL_PTR,
#endif  /* #if ( PDUR_DESTINATION_LIST_SIZE > 0U ) */

#if ( PDUR_TPBUFFER_LENGTH > 0U )
    &PduR_TpBufferTable,                /* .PduRTpBufferTable */
#else   /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */
    NULL_PTR,                           /* .PduRTpBufferTable */
#endif  /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_GETWAY */

#if ( PDUR_TXBUFFER_LENGTH > 0U )
    &PduR_TxBufferTable,                /* .PduRTxBufferTable */     		/* 0..1 */
#else   /* #if ( PDUR_TXBUFFER_LENGTH > 0U ) */
    NULL_PTR,                           /* .PduRTxBufferTable */     		/* 0..1 */
#endif  /* #if ( PDUR_TXBUFFER_LENGTH > 0U ) */

#endif  /* #if (STD_ON == PDUR_SUPPORT_GETWAY) */

#ifdef PDUR_SUPPORT_TP_MULICAST

#if ( PDUR_DESTINATION_TP_SIZE > 0U )
    &PduR_TpMulList[0U],                /* .PduR_TpMulPtr */
#else   /* #if ( PDUR_DESTINATION_TP_SIZE > 0U ) */
    NULL_PTR,
#endif  /* #if ( PDUR_DESTINATION_TP_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_MULICAST */

#ifdef PDUR_SUPPORT_IF_MULICAST

#if ( PDUR_DESTINATION_IF_SIZE > 0U )
    &PduR_IfMulList[0U]                 /* .PduR_IfMulPtr */
#else   /* #if ( PDUR_DESTINATION_IF_SIZE > 0U ) */
    NULL_PTR
#endif  /* #if ( PDUR_DESTINATION_IF_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_IF_MULICAST */
};
#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"


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
#endif /* #if (STD_OFF == PDUR_ZERO_COST_OPERATION) */

#define PDUR_START_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

const PduR_PBConfigType PduR_PBConfigTable = {

#if ( STD_ON == PDUR_ZERO_COST_OPERATION )

    PDUR_CONFIGURATION_ID,

#else   /* #if ( STD_ON == PDUR_ZERO_COST_OPERATION ) */
	PDUR_DESTINATION_LIST_SIZE,

#ifdef PDUR_SUPPORT_TP_MULICAST

#if ( PDUR_DESTINATION_TP_SIZE > 0U )
    PDUR_DESTINATION_TP_SIZE,
#else   /* #if ( PDUR_DESTINATION_TP_SIZE > 0U ) */
    0U,
#endif  /* #if ( PDUR_DESTINATION_TP_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_MULICAST */

#ifdef PDUR_SUPPORT_IF_MULICAST

#if ( PDUR_DESTINATION_IF_SIZE > 0U )
    PDUR_DESTINATION_IF_SIZE,
#else   /* #if ( PDUR_DESTINATION_IF_SIZE > 0U ) */
    0U,
#endif  /* #if ( PDUR_DESTINATION_IF_SIZE > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_IF_MULICAST */

    &PduR_RoutingTables,

#ifdef PDUR_SUPPORT_TP_GETWAY

#if ( PDUR_TPBUFFER_LENGTH > 0U )

    &PduR_TpBufferStatus[0U],

#else   /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

    NULL_PTR,

#endif  /* #if ( PDUR_TPBUFFER_LENGTH > 0U ) */

#endif  /* #ifdef PDUR_SUPPORT_TP_GETWAY */
#endif  /* #if ( STD_ON == PDUR_ZERO_COST_OPERATION ) */
#if ( STD_ON == PDUR_SUPPORT_MULTICORE )
	&PduR_BufferTable[0],
	&PduR_ApplicationTable[0]
#endif /* #if ( STD_ON == PDUR_SUPPORT_MULTICORE ) */

};

#define PDUR_STOP_SEC_CONFIG_DATA
#include "PduR_MemMap.h"

