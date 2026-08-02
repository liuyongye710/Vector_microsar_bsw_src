/*
********************************************************************************
*
* File name: J1939Tp_Lcfg.c
*
* Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: lizhiheng/2020.03.30
* Change: Clear the module configurations.
* Cause: Release version V3.0
********************************************************************************
* Version: 3.1
* Author/Date: YanCL/2024/6/25
* Change: Update copyright information.
* Cause: Update
********************************************************************************
*/
/*
*******************************************************************************
*    Include
*******************************************************************************
*/
#include "J1939Tp_Cfg.h"
#include "CanIf.h"
#include "PduR_J1939Tp.h"
#include "J1939Tp_Int.h"

/*
*******************************************************************************
*    Local Macros
*******************************************************************************
*/
/*
*******************************************************************************
*    Local Types
*******************************************************************************
*/
/*
*******************************************************************************
*    Local Variables
*******************************************************************************
*/
/*
*******************************************************************************
*    Local Constants
*******************************************************************************
*/
/*
*******************************************************************************
*    Local Functions
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Variable
*******************************************************************************
*/
#define J1939TP_START_SEC_VAR_INIT
#include "J1939Tp_MemMap.h"

VAR(J1939Tp_RxPduStateType, J1939TP_VAR_INIT) J1939Tp_RxPduState[J1939TP_RXPDU_NUM + 1U] = {0U};
VAR(J1939Tp_RxSduStateType, J1939TP_VAR_INIT) J1939Tp_RxSduState[J1939TP_RXNSDU_NUMBER + 1U] = {0U};
VAR(J1939Tp_TxPduStateType, J1939TP_VAR_INIT) J1939Tp_TxPduState[J1939TP_TXPDU_NUM + 1U] = {0U};
VAR(J1939Tp_TxSduStateType, J1939TP_VAR_INIT) J1939Tp_TxSduState[J1939TP_TXNSDU_NUMBER + 1U ] = {0U};

#define J1939TP_STOP_SEC_VAR_INIT
#include "J1939Tp_MemMap.h"

/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
#define J1939TP_START_SEC_CONFIG_DATA
#include "J1939Tp_MemMap.h"

CONST(J1939Tp_RxChannelType, J1939TP_CONFIG_DATA) J1939Tp_RxChannel[J1939TP_RXCHANNEL_NUMBER + 1U] = {
	{
		0U
	}
};

CONST(J1939Tp_RxSdu_Type, J1939TP_CONFIG_DATA) J1939Tp_RxSduInfo[J1939TP_RXNSDU_NUMBER + 1U] =
{
	{
		0U
	}
};

CONST(J1939Tp_RxPduType, J1939TP_CONFIG_DATA) J1939Tp_RxPdu[J1939TP_RXPDU_NUM + 1U] =
{
	{
		0U
	}
};

CONST(J1939Tp_TxChannelType, J1939TP_CONFIG_DATA) J1939Tp_TxChannel[J1939TP_TXCHANNEL_NUMBER + 1U] =
{
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		239U,
		0xffffU,
		0x0U,
		0x1U,
		0U,
		2U
	},
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		240U,
		0xffffU,
		0x2U,
		0x3U,
		2U,
		3U
	},
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		48U,
		0xffffU,
		0x4U,
		0x5U,
		3U,
		4U
	},
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		26U,
		0xffffU,
		0x6U,
		0x7U,
		4U,
		5U
	},
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		46U,
		0xffffU,
		0x8U,
		0x9U,
		5U,
		6U
	},
	{
		TRUE,
		J1939TP_NO_ADDRESS_CONFIGURED,
		FALSE,
		255U,
		J1939TP_PROTOCOL_BAM,
		TRUE,
		96U,
		0xffffU,
		0xaU,
		0xbU,
		6U,
		7U
	},
	{
		0U
	}
};

VAR(J1939Tp_TxSdu_Type, J1939TP_CONFIG_DATA) J1939Tp_TxSduInfo[J1939TP_TXNSDU_NUMBER + 1U] = /* WangM CONST-->VAR */
{
	{
		FALSE,
		0xfee3,
		1U,
		0U,
		34U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		6U,
		0U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		7U,
		1U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		30U,
		2U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		32U,
		3U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		33U,
		4U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		FALSE,
		0xfeca,
		40U,
		5U,
		48U,
		0U,
		J1939TP_NO_CFG_DIRECT
	},
	{
		0U
	}
};

CONST(J1939Tp_TxPduType, J1939TP_CONFIG_DATA) J1939Tp_TxPdu[J1939TP_TXPDU_NUM + 1U] =
{
	{
		0x8U,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x9U,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0x6U,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x7U,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0x1bU,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x1cU,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0x17U,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x18U,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0x19U,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x1aU,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0x1dU,
		J1939TP_TPCM_PDUTYPEOFTXPDU
	},
	{
		0x1eU,
		J1939TP_TPDT_PDUTYPEOFTXPDU
	},
	{
		0U
	}
};

#define J1939TP_STOP_SEC_CONFIG_DATA
#include "J1939Tp_MemMap.h"

