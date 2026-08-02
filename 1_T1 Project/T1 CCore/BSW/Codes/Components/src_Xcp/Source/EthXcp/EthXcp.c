/*
********************************************************************************
*
* File name: EthXcp.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: FangT/2021.03.03
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.05.08
* Change: Modify the EthXcp code specification according to AutoSar requirements.
* Cause: Updata
********************************************************************************
* Version: 3.1
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2021.11.1
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: FangT/2021.11.11
* Change: Modify the problem of converting u8 to u32.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: FangT/2021.11.23
* Change: The EthData data type is changed to uint8.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: FangT/2022.03.01
* Change: 1.Increase the receive queue.
*         2.Call Sendcallback after sending data.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: FangT/2022.03.16
* Change: 1.Change the send length to uint32 type.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: ShiRong/2022.06.21
* Change: Clear compile warnings.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: ShiRong/2022.11.3
* Change: Modify the adaptive length of Ethernet dto and cto.
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: ShiRong/2022.12.22
* Change: The modified ethereal measurement cannot exceed 255.
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: ShiRong/2023.03.09
* Change: 1.Fix the bug of calibration long scale quantitative data receiving
*           error.
*         2.Modify the data processing of STIM function.
* Cause: Bugfix
********************************************************************************
* Version: 3.12
* Author/Date: LinZhC/2023.12.20
* Change: Modify the parameter type of the Xcp Command function.
* Cause: Bugfix
********************************************************************************
* Version: 3.13
* Author/Date: LinZhC/2024.01.10
* Change: 1.Modified compatibility of multi-bus and multi-PDU configurations.
*           The following changes have been modify:
*       (1) Synchronize count and status code and logic from XcpOnCan to
*       (2) Modify the implementation logic of EthXcp_Init,EthXcp_GetRxMsg,
*           XcpOnEth. Xcp_SoAdIfRxIndication,Xcp_SoAdIfTxConfirmation,
*           EthXcp_Send. Otherwise, data from multiple buses or PDUs cannot
*           be processed.
*         2.Modified QAC, Polyspace warnings and issues.The following changes 
*           have been modify:
*       (1) Parentheses are added to polynomial expressions in the
*           CanXcp_GetRxMsg function.
*       (2) Call a function that has a return value but does not use its return
*           value, so add void to modify it.
* Cause: Update
********************************************************************************
* Version: 3.14
* Author/Date: LinZhC/2024.02.20
* Change: Fix compile error.
* Cause: Update
********************************************************************************
* Version: 3.15
* Author/Date: LinZhC/2024.02.28
* Change: 1.#if...#endif appending.
* Cause: Update
********************************************************************************
* Version: 3.16
* Author/Date: LinZhC/2024.03.13
* Change: 1.If a line of code is too long, shorten it.
*         2.fixed and optimized logical issues with queue sending.
*         3.fixed an issue with QAC/Plyspace code check.
*         4.Optimize send/receive data processing logic to prevent array
*           overflows.
* Cause: Update
********************************************************************************
* Version: 3.17
* Author/Date: LinZhC/2024.04.01
* Change: 1.Add Xcp_EthDaqTxConfirmEnable.
*         2.Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.18
* Author/Date: KangJH/2024.05.22
* Change: Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.19
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.20
* Author/Date: KangJH/2024.07.09
* Change: Receive data 4-byte alignment.
* Cause: Bugfix
********************************************************************************
* Version: 3.21
* Author/Date: KangJH/2024.08.13
* Change: Modify copyright information.
* Cause: Update
********************************************************************************
* Version: 3.22
* Author/Date: KangJH/2024.08.30
* Change: When transmitting a frame of DTO data, add the length of the
*         header information.
* Cause: Bugfix
********************************************************************************
* Version: 3.23
* Author/Date: KangJH/2024.09.10
* Change: 1.Modify the XcpTxPduId check condition in the Xcp_SoAdIfTxConfirmation
*         function.
*         2.Modify the initial value of Xcp_EthDaqTxConfirmEnable.
* Cause: Bugfix
********************************************************************************
* Version: 3.24
* Author/Date: KangJH/2024.10.12
* Change: Add macro XCP_ONETHERNET_ENABLE to fix the errors when XCPonEthernet
*         function is disable.
* Cause: Bugfix
********************************************************************************
* Version: 3.25
* Author/Date: KangJH/2024.10.13
* Change: Disable related functions when EthXcp is disabled.
* Cause: Bugfix
********************************************************************************
* Version: 3.26
* Author/Date: KangJH/2024.10.23
* Change: Supports TCP communication connections.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "EthXcp.h"
#include "EthXcp_Cfg.h"
#if( XCP_ONETHERNET_ENABLE == STD_ON )
#include "EthXcp_Lcfg.h"
#include "SoAd.h"
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */

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
#if( XCP_ONETHERNET_ENABLE == STD_ON )
#define XCP_START_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"
static VAR(EthXcpFrame_st, XCP_VAR_NO_INIT) EthXcpFrameAry[XCPBLOCK_SIZE];
#define XCP_STOP_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
static VAR(uint8, XCP_VAR_INIT) Xcp_EthFrameCount = XCP_INIT_0;
static VAR(uint8, XCP_VAR_INIT) Xcp_EthFrameIndex = XCP_INIT_0;
static VAR(uint8, XCP_VAR_INIT) Xcp_EthFrameHeader = XCP_INIT_1;
static VAR(boolean, XCP_VAR_INIT) Xcp_EthModuleState = FALSE;
static VAR(uint8, XCP_VAR_INIT) Xcp_EthDataBuff[XCP_ETH_DATA_SIZE] = {XCP_INIT_0};
static VAR(uint8, XCP_VAR_INIT) Xcp_EthXcpCommandTimeCounter = XCP_INIT_0;
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

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
#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
VAR(uint8, XCP_VAR_INIT) Xcp_EthResData[XCP_ETHERNET_MAX_CTO + XCP_VALUE_4] = {XCP_INIT_0};
VAR(uint16, XCP_VAR_INIT) Xcp_EthCtrTx = XCP_INIT_0;
VAR(uint8, XCP_VAR_INIT) Xcp_EthGetStatus = TRUE;
VAR(uint8, XCP_VAR_INIT) Xcp_EthDaqTxConfirmEnable = TRUE;
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/*
********************************************************************************
* Function Name: EthXcp_Init
*
* Explanation: ETHXCP initialization.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) EthXcp_Init(void)
{
    uint8 index;
    uint16 soadId = XCP_INIT_0;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    Xcp_EthFrameCount = XCP_INIT_0;
    Xcp_EthFrameIndex = XCP_INIT_0;
    Xcp_EthFrameHeader = XCP_INIT_1;
    Xcp_EthGetStatus = TRUE;
    Xcp_EthXcpCommandTimeCounter = XCP_INIT_0;
    XCP_gstETH_msgvar_rx.msgmode = XCP_INIT_1;
    XCP_gstETH_msgvar_tx.msgmode = XCP_INIT_1;
    Xcp_EthModuleState = TRUE;
    Xcp_EthCtrTx = XCP_INIT_0;

    for( index = XCP_INDEX_0; index < XCP_CONNECTION_CFG_NUM; index++ )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[index];
        /* Check the current bus type. */
        if( XCP_BUS_ETHERNET == xcpConnCfgPtr->XcpBusType )
        {
#if( XCP_ON_TCP_ENABLE == STD_ON )
            /* Enable monitoring. */
            (void)SoAd_GetSoConId(xcpConnCfgPtr->XcpOpenSocketPduRef, &soadId);
            (void)SoAd_OpenSoCon(soadId);
#else
            (void)SoAd_GetSoConId(Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduRef, &soadId);
            (void)SoAd_OpenSoCon(soadId);
#endif  /* XCP_ON_TCP_ENABLE == STD_ON */
        }
    }
}

/*
********************************************************************************
* Function Name: EthXcp_MainFunction
*
* Explanation: Called by XCP_main,Get Eth messages and execute commands.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) EthXcp_MainFunction(void)
{
    uint8 avcDlc;
    /* The sequence number in the Xcp_ConnectionCfg list. */
    uint32 avConnectionId = XCP_INVALID_CONNECTION_ID;
    Xcp_CtoType acaMsg = {XCP_INIT_0};

    if( XCP_VALUE_0 == EthXcp_GetRxMsg(&avcDlc, &avConnectionId, &acaMsg.dwords[XCP_INDEX_0]) )
    {
        Xcp_Command((uint8)avConnectionId, (const Xcp_CtoType*)&acaMsg);
    }
}

/*
********************************************************************************
* Function Name: EthXcp_GetRxMsg
*
* Explanation: Get Eth messages.
*
* param: avcpDlc: ID of the received message.
*        avlpId: Length of the received message.
*
* retval: XCP_E_OK: get tx msg success.
*         XCP_E_NOT_OK: get tx msg fail.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) EthXcp_GetRxMsg
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_CONST) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_CONST) avlpData
)
{
    uint8 index;
    uint8 msgLen = XCP_INIT_0;
    uint8 msgLenFourtimes = XCP_INIT_0;
    Std_ReturnType retValue = XCP_E_NOT_OK;

    /* Send confirmation timing. */
    Xcp_EthXcpCommandTimeCounter++;
    if( XCP_VALUE_0 == Xcp_EthFrameCount )
    {
        Xcp_EthXcpCommandTimeCounter = XCP_VALUE_0;
        if( TRUE != Xcp_EthGetStatus )
        {
            Xcp_EthGetStatus = TRUE;
        }
        retValue = XCP_E_NOT_OK;
    }
    else if( TRUE != Xcp_EthGetStatus )
    {
        /* Send confirmation timeout. */
        if( TRANSMITTIMEOUT < Xcp_EthXcpCommandTimeCounter )
        {
            /* Xcp_MemClr(&XcpFrameAry, XCPBLOCK_SIZE * sizeof(XcpFrameAry)); */
            Xcp_EthGetStatus = TRUE;
            Xcp_EthFrameCount = XCP_VALUE_0;
            Xcp_EthFrameIndex = XCP_VALUE_0;
            Xcp_EthFrameHeader = XCP_VALUE_1;
        }
        retValue = XCP_E_NOT_OK;
    }
    else
    {
        Xcp_EthXcpCommandTimeCounter = XCP_VALUE_0;
        if ( XCP_ETHERNET_MAX_CTO < EthXcpFrameAry[Xcp_EthFrameHeader].length )
        {
            msgLen = XCP_ETHERNET_MAX_CTO;
        }
        if ( XCP_ETH_FRAME_MIN_LEN > EthXcpFrameAry[Xcp_EthFrameHeader].length )
        {
            msgLen = XCP_ETH_FRAME_MIN_LEN;
        }
        else
        {
            msgLen = EthXcpFrameAry[Xcp_EthFrameHeader].length;
        }
        /* 4-byte alignment. */
        msgLen = SET_VALUE_ALIGN(msgLen, uint8, sizeof(uint32));
        *avlpId = EthXcpFrameAry[Xcp_EthFrameHeader].connectionId;
        *avcpDlc = msgLen;
        msgLenFourtimes = msgLen / XCP_BYTE_ALIGNMENT_4;

#if( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
        for( index = XCP_INDEX_0; index < msgLenFourtimes; index++ )
        {
            avlpData[index] = EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_3 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_2 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_1 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_0 + (index * XCP_VALUE_4)];
        }
#else
        for( index = XCP_INDEX_0; index < msgLenFourtimes; index++ )
        {
            avlpData[index] = EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_0 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_1 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_2 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8)
                                + EthXcpFrameAry[Xcp_EthFrameHeader].data[XCP_INDEX_3 + (index * XCP_VALUE_4)];
        }
#endif  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
        /* Clear receive flag. */
        Xcp_EthGetStatus = FALSE;
        Xcp_EthFrameCount--;
        if( Xcp_EthFrameHeader == (XCPBLOCK_SIZE - XCP_VALUE_1) )
        {
            Xcp_EthFrameHeader = XCP_VALUE_0;
        }
        else
        {
            Xcp_EthFrameHeader++;
        }
        retValue = XCP_E_OK;
    }

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_SoAdIfRxIndication
*
* Explanation: SoAd receive indicate.
*
* param: XcpRxPduId: ID of the received EthPduID.
*        XcpRxPduPtr: PduInfoType_structure.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_SoAdIfRxIndication
(
    PduIdType XcpRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, XCP_APPL_CONST)XcpRxPduPtr
)
{
    PduInfoType ethPduInfoPtr = {NULL_PTR, XCP_INIT_0};
    uint8 errorId = XCP_E_NO_ERROR;
    uint8 index = XCP_INVALID_XCP_PDU_ID;
    uint8 connectionId = XCP_INVALID_CONNECTION_ID;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( (XCP_BUS_NULL != Xcp_ConnectionStatus.busType)
        && (XCP_BUS_ETHERNET != Xcp_ConnectionStatus.busType) )
    {
        /* There are currently other buses connected to XCP. */
    }
    else if( Xcp_EthModuleState != TRUE )
    {
        errorId = XCP_E_NOT_INITIALIZED;
    }
    else if( XcpRxPduPtr == NULL_PTR )
    {
        errorId = XCP_E_PARAM_POINTER;
    }
    else if( XCP_CONNECTION_CFG_NUM > XCP_VALUE_0 )
    {
        connectionId = Xcp_ConnectionStatus.connectionId;
        /* Check whether the PDUID corresponding to the current connectionID is
            the same as that in Xcp_ConnectionCfg. */
        if( XCP_BUS_NULL == Xcp_ConnectionStatus.busType )
        {
            for( index = XCP_INDEX_0; index < XCP_CONNECTION_CFG_NUM; index++ )
            {
                xcpConnCfgPtr = &Xcp_ConnectionCfg[index];
                if( XcpRxPduId == Xcp_RxPdu[xcpConnCfgPtr->RxXcpPduIdRef].XcpPduId )
                {
                    errorId = XCP_E_NO_ERROR;
                    connectionId = index;
                    break;
                }
                else
                {
                    /* Do nothing. */
                }
            }
            if( XCP_CONNECTION_CFG_NUM == index )
            {
                errorId = XCP_E_INVALID_PDUID;
                connectionId = XCP_INVALID_CONNECTION_ID;
            }
        }
        else
        {
            if( XCP_CONNECTION_CFG_NUM > connectionId )
            {
                xcpConnCfgPtr = &Xcp_ConnectionCfg[connectionId];
                if( XcpRxPduId == Xcp_RxPdu[xcpConnCfgPtr->RxXcpPduIdRef].XcpPduId )
                {
                    errorId = XCP_E_NO_ERROR;
                }
                else
                {
                    errorId = XCP_E_INVALID_PDUID;
                }
            }
            else
            {
                errorId = XCP_E_INVALID_PDUID;
            }
        }
        if( XCP_E_INVALID_PDUID != errorId )
        {
            if( XCP_ETHERNET_MAX_CTO < XcpRxPduPtr->SduLength )
            {
                ethPduInfoPtr.SduLength = XCP_ETHERNET_MAX_CTO;
            }
            else
            {
                ethPduInfoPtr.SduLength = (PduLengthType)(XcpRxPduPtr->SduLength - XCP_VALUE_4);
            }
            ethPduInfoPtr.SduDataPtr = XcpRxPduPtr->SduDataPtr + XCP_VALUE_4;
            if( (*ethPduInfoPtr.SduDataPtr) <= XCP_PID_STIM_END )
            {
#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
                Xcp_StimDataProcess(ethPduInfoPtr.SduDataPtr, ethPduInfoPtr.SduLength);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */
            }
            else
            {
                Xcp_MemCpy8(EthXcp_RxPduInfo[XCP_INDEX_0].data,ethPduInfoPtr.SduDataPtr,ethPduInfoPtr.SduLength);

                if( Xcp_EthFrameIndex == (XCPBLOCK_SIZE - XCP_VALUE_1) )
                {
                    Xcp_EthFrameIndex = XCP_VALUE_0;
                }
                else
                {
                    Xcp_EthFrameIndex++;
                }
                EthXcpFrameAry[Xcp_EthFrameIndex].ID = XCP_gstETH_msgvar_rx.Id;
                EthXcpFrameAry[Xcp_EthFrameIndex].connectionId = connectionId;
                EthXcpFrameAry[Xcp_EthFrameIndex].length = (uint8)ethPduInfoPtr.SduLength;
                for( index = XCP_INDEX_0; index < ethPduInfoPtr.SduLength; index++ )
                {
                    EthXcpFrameAry[Xcp_EthFrameIndex].data[index] = XCP_gcaETH_Msg_CRO[index];
                }
                Xcp_EthFrameCount++;
            }
        }
    }
    else
    {
        /* Do nothing. */
    }
    Xcp_Det_ErrorReport(XCP_SID_RXINDICATION, errorId);
}

/*
********************************************************************************
* Function Name: Xcp_EthIfTxConfirmation
*
* Explanation: SoAd send completion prompt indicate.
*
* param: XcpTxPduId: PduID of the transmitted data.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_SoAdIfTxConfirmation(PduIdType XcpTxPduId)
{
    uint8 errorId = XCP_E_NO_ERROR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( Xcp_EthModuleState != TRUE )
    {
        errorId = XCP_E_NOT_INITIALIZED;
    }
    else
    {
        if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
        {
            xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
            if( XcpTxPduId == Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduId )
            {
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
                (void)Xcp_SendCallBack(xcpConnCfgPtr->TxXcpPduIdRef);
#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
                if( TRUE == Xcp_EthDaqTxConfirmEnable )
                {
                    (void)Xcp_SendCallBack();
                }
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
            }
        }
#if( XCP_BLOCK_UPLOAD != STD_ON )
        Xcp_EthGetStatus = TRUE;
#endif  /* XCP_BLOCK_UPLOAD != STD_ON */
    }
    Xcp_Det_ErrorReport(XCP_SID_TXCONFIRMATION, errorId);
}

/*
********************************************************************************
* Function Name: EthXcp_Send
*
* Explanation: Xcp messages are sent over the Eth.
*
* param: len: Data frame length.
*        msg: The address to send the message.
*
* retval: XCP_E_OK: The request has been accepted
*         XCP_E_NOT_OK: The request has not been accepted, e.g. due to a still ongoing
*                   transmission in the corresponding socket or the to be transmitted
*                    message is too long.
********************************************************************************
*/
FUNC(Std_ReturnType, XCP_CODE) EthXcp_Send(uint16 len, P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg)
{
    Std_ReturnType stdRet = XCP_E_NOT_OK;
    uint16 acIndex;
    PduInfoType ethIfTxInfoPtr;
    const uint8* src;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( (XCP_ETHERNET_MAX_DTO + XCP_ETH_DAQ_DTO_HEAD_LEN) < len )
    {
        ethIfTxInfoPtr.SduLength = XCP_ETHERNET_MAX_DTO + XCP_ETH_DAQ_DTO_HEAD_LEN;
    }
    else
    {
        ethIfTxInfoPtr.SduLength = len;
    }
    ethIfTxInfoPtr.SduDataPtr = &Xcp_EthDataBuff[XCP_INDEX_0];
    src = msg;

    for( acIndex = XCP_INDEX_0; acIndex < ethIfTxInfoPtr.SduLength; acIndex++ )
    {
        ethIfTxInfoPtr.SduDataPtr[acIndex]= *src;
        src++;
    }

    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
#if( XCP_ONETHERNET_ENABLE == STD_ON )
        stdRet = SoAd_IfTransmit(Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduRef, &ethIfTxInfoPtr);
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
    }

    return stdRet;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
#endif  /* XCP_ONETHERNET_ENABLE == STD_ON */
