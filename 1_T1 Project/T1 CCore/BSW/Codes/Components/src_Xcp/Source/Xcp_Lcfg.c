/*
********************************************************************************
*
* File name: Xcp_Lcfg.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : yong.zhang/2019.12.28
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date : fangtao/2020.8.11
* Change: Added channel name and length.
* Cause: Bugfix.
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.1
* Author/Date: lqiao/2022.09.16
* Change: Add XCP_gcaCAN_Msg_CRO and XCP_gcaCAN_Msg_DTO
* Cause: new.
********************************************************************************
* Version: 3.2
* Author/Date: ChenQJ/2023.10.31
* Change: Fix compile warning.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: lqiao/2024.05.16
* Change: Delete XcpEventName_Array.
          Modify XcpEventName.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Xcp.h"
/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
#define DAQ      (0U) 
#define DAQ_STIM (1U) 
#define STIM     (2U)

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
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static FUNC(uint8, XCP_CODE) XcpGetRand
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)xcpBufferRand,
    uint8 avcLength
);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define XCP_START_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"
VAR(uint8, XCP_VAR_NO_INIT) XCP_gcaCAN_Msg_CRO[64];
VAR(uint8, XCP_VAR_NO_INIT) XCP_gcaCAN_Msg_DTO[64];
#if( (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) )
VAR(Xcp_Addr_st, XCP_VAR_NO_INIT) Xcp_Addr_Temp[XCP_OVERLAY_CNT];
#endif
#define XCP_STOP_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
VAR(uint8, XCP_VAR_INIT) Xcp_Resource_Array[XCP_SAFELEN] = {0};
VAR(Xcp_NvmBlockId_st, XCP_VAR_INIT) Xcp_NvmBlockId[XCP_BLOCK_NUM + 1U] = 
{
    { 0xFFFFU, XCP_E_NOT_OK, XCP_E_NOT_OK, NULL_PTR, 0U }
};
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define XCP_START_SEC_CONFIG_DATA
#include "Xcp_MemMap.h"
#if( XCP_EVENT_CHANNEL_NUM > 0 )
CONST(Xcp_EventChannelType, XCP_CONFIG_DATA) Xcp_EventChannel[XCP_EVENT_CHANNEL_NUM] =
{
	{0, 1, 0, 0, 1, DAQ_TIMESTAMP_UNIT_10MS, 4, 0},
	{0, 1, 1, 0, 5, DAQ_TIMESTAMP_UNIT_10MS, 4, 0},
	{0, 1, 2, 0, 10, DAQ_TIMESTAMP_UNIT_10MS, 4, 0},
};
#endif

CONST(uint8, XCP_CONFIG_DATA) XcpEventName[XCP_EVENT_CHANNEL_NUM][15]=
{
    {"XcpEvent_10ms"},
    {"XcpEvent_50ms"},
    {"XcpEvent_100ms"},
};

CONST(uint8, XCP_CONFIG_DATA) XcpEventNameLength[XCP_EVENT_CHANNEL_NUM] = 
{
	13U,
	13U,
	14U,
};

#if( XCP_DTO_NUM > XCP_VALUE_0 )
CONST(Xcp_DtoType, XCP_CONFIG_DATA) Xcp_Dto[XCP_DTO_NUM] =
{
};
#endif

#if( XCP_ODTENTRY_NUM > XCP_VALUE_0 )
CONST(Xcp_OdtEntryType, XCP_CONFIG_DATA) Xcp_OdtEntry[XCP_ODTENTRY_NUM] = 
{
};
#endif

#if( XCP_ODT_NUM > XCP_VALUE_0 )
CONST(Xcp_OdtType, XCP_CONFIG_DATA) Xcp_Odt[XCP_ODT_NUM] =
{
};
#endif

#if( XCP_DAQ_LIST_NUM > 0 )
CONST(Xcp_DaqListType, XCP_CONFIG_DATA) Xcp_DaqList[XCP_DAQ_LIST_NUM] =
{
};
#endif

CONST(Xcp_PduType, XCP_CONFIG_DATA) Xcp_RxPdu[XCP_RXPDU_LIST] =
{
	{0, 13},
};

CONST(Xcp_PduType, XCP_CONFIG_DATA) Xcp_TxPdu[XCP_TXPDU_LIST] =
{
	{0, 11},
};





CONST(Xcp_ConnectionCfgType, XCP_CONFIG_DATA) Xcp_ConnectionCfg[XCP_CONNECTION_CFG_NUM + 1U] = 
{
    { 0U, XCP_BUS_CAN, 0U, 0U, 0U, 8U, 8U, 7U, XCPTS_NO_TIME_STAMP },
    { XCP_INVALID_CONNECTION_ID, XCP_BUS_NULL, 0xFFU, 0xFFU, 0U, 0U, 0U, 0U, XCPTS_NO_TIME_STAMP }
};

#define XCP_STOP_SEC_CONFIG_DATA
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

static FUNC(uint8, XCP_CODE) XcpGetRand
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)xcpBufferRand,
    uint8 avcLength
)
{
    uint8 retVal = E_NOT_OK;
    XCP_DUMMY_STATEMENT(xcpBufferRand);
    XCP_DUMMY_STATEMENT(avcLength);
	retVal = CalAppl_GetRand(xcpBufferRand, avcLength); /* WangM */
    /* Provide customers with code to write random data */
    return retVal; 
}

FUNC(void, XCP_CODE) XcpGetSeed(void)
{
    uint8 retVal = E_NOT_OK; 
    if( XCP_SAFELEN > XCP_VALUE_0 )
    {
        retVal = XcpGetRand(Xcp_Resource_Array, XCP_SAFELEN);

        if( E_OK == retVal )
        {
            /* Write decryption code for clients */
			retVal = CalAppl_CalKey((uint8*)&Xcp_Resource_Array); /* WangM */
        }
        else
        {
        
        }
    }
    else
    {
    
    }
    /* Provide customers with the key to write and obtain security algorithms */
}

FUNC(uint8, XCP_CODE) XcpUnlock
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)avcpKey,
    uint8 avcLength
)
{
    uint8 reValue = E_NOT_OK;
    XCP_DUMMY_STATEMENT(avcpKey);
    XCP_DUMMY_STATEMENT(avcLength);
	reValue = CalAppl_CompareKey(avcpKey, avcLength); /* WangM */
    /* Provide decryption to customers */

    return reValue;
}

/*
********************************************************************************
* Function Name: XcpAppl_FlashClear
*
* Explanation: Execute clear data instruction interface.
*
* param: setMta: Starting address for clearing data.
* param: clearSize: Clear the size of data.
*
* retval: XCP_E_OK: Successfully cleared
		  XCP_E_NOT_OK: Clearing unsuccessful.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) XcpAppl_FlashClear
(
    uint32 setMta,
    uint32 clearSize
)
{
    uint8 ret = XCP_E_NOT_OK;
    /* Provide decryption to customers */
    XCP_DUMMY_STATEMENT(setMta);
    XCP_DUMMY_STATEMENT(clearSize);

    return ret;
}

/*
********************************************************************************
* Function Name: XcpAppl_FlashProgram
*
* Explanation: Execute program flushing interface.
*
* param: setMta: Brush Start Address.
* param: dataPtr:Data to be written.
* param: Size of data to be flushed.
*
* retval: XCP_E_OK: Brush successfully
		  XCP_E_NOT_OK: Brushing unsuccessful.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) XcpAppl_FlashProgram
(
    uint32 setMta,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)dataPtr,
    uint32 writeSize
)
{
    uint8 ret = XCP_E_NOT_OK;
    XCP_DUMMY_STATEMENT(setMta);
    XCP_DUMMY_STATEMENT(dataPtr);
    XCP_DUMMY_STATEMENT(writeSize);
    /* Provide decryption to customers */

    return ret;
}

/*
********************************************************************************
* Function Name: XcpAppl_Reset
*
* Explanation: Execute flush reset command interface.
*
* param: None.
*
* retval: XCP_E_OK: Reset successful
		  XCP_E_NOT_OK: Reset failed.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) XcpAppl_Reset(void)
{
    uint8 ret = XCP_E_NOT_OK;

    /* Provide decryption to customers */
    return ret;
}

#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
/*
********************************************************************************
* Function Name: XcpOverlayMapping
*
* Explanation: Enable and disable the overlay function interface.
*
* param: None.
*
* retval: XCP_E_OK: Successfully configured
		  XCP_E_NOT_OK: Configure failed.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) XcpOverlayMapping
(
	uint8 segment,
	uint8 page,
	uint8 mode
)
{
	uint8 ret = XCP_E_NOT_OK;
	XCP_DUMMY_STATEMENT(segment);
	XCP_DUMMY_STATEMENT(page);
	XCP_DUMMY_STATEMENT(mode);
	return ret;
}
#endif  /* RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY */


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


