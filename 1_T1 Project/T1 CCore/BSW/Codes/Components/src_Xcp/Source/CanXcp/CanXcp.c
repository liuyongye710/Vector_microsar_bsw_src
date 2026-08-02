/*
********************************************************************************
*
* File name: CanXcp.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: SunPF/2018.07.10
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date: YongZ/2020.07.02
* Change: Add release software number
* Cause: Update
********************************************************************************
* Version: 3.1
* Author/Date: FangT/2020.08.11
* Change: Modify the sending function according to configuration requirements.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: FangT/2020.08.21
* Change: Added det function.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: FangT/2020.09.15
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: FangT/2021.06.30
* Change: Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: FangT/2021.08.18
* Change: Modify the code specification.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: FangT/2021.08.31
* Change: Eliminate compilation warnings.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: FangT/2021.10.29
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.9
* Author/Date: FangT/2021.11.1
* Change: Modify coding style.
* Cause: Optimization
********************************************************************************
* Version: 3.10
* Author/Date: FangT/2021.11.11
* Change: Modify the problem of converting u8 to u32.
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: FangT/2022.03.16
* Change: 1.Change the send length to uint32 type.
* Cause: Optimization
********************************************************************************
* Version: 3.23
* Author/Date: ShiRong/2022.06.16
* Change: Clear compile warnings.
* Cause: Optimization
*******************************************************************************
* Version: 3.24
* Author/Date: ShiRong/2022.09.16
* Change: Add XcpOnCANFD function.
* Cause: Update
*******************************************************************************
* Version: 3.25
* Author/Date: ShiRong/2023.02.02
* Change: Add multi-pair PDU function.
* Cause: Update
*******************************************************************************
* Version: 3.26
* Author/Date: ShiRong/2023.03.09
* Change: 1.Fix the bug of calibration long scale quantitative data receiving error.
*         2.Modify the data processing of STIM function.
* Cause: Bug
*******************************************************************************
* Version: 3.27
* Author/Date: ShiRong/2023.03.14
* Change: 1.Fix the bug of sending confirmation.
* Cause: BugFix
*******************************************************************************
* Version: 3.28
* Author/Date: ShiRong/2023.05.06
* Change: Add Block Transfer Mode.
* Cause: Update
*******************************************************************************
* Version: 3.29
* Author/Date: ShiRong/2023.08.02
* Change: Add sending confirmation timeout judgment function.
* Cause: Update
*******************************************************************************
* Version: 3.30
* Author/Date: ShiRong/2023.08.17
* Change: The sending confirmation time affects the block transmission function.
* Cause: Bugfix
*******************************************************************************
* Version: 3.31
* Author/Date: ShiRong/2023.09.26
* Change: Optimize sending confirmation.
* Cause: Update
*******************************************************************************
* Version: 3.32
* Author/Date: LinZhC/2023.12.20
* Change: Modify the parameter type of the Xcp Command function.
* Cause: Bugfix
*******************************************************************************
* Version: 3.33
* Author/Date: LinZhC/2024.01.10
* Change: 1.Modified compatibility of multi-bus and multi-PDU configurations.
*           The following changes have been modify:
*       (1) The Xcp_CanGetStatus and Xcp_CanCommandTimeCounter variables were moved
*           from xcp.c to this file.
*       (2) Modify the implementation logic of Xcp_CanIfRxIndication,
*           Xcp_CanIfTxConfirmation, CanXcp_Send. Otherwise, data from multiple
*           buses or PDUs cannot be processed.
*       (3) Modify the CanXcp_Init function to clear some counts and states.
*         2.Modified QAC, Polyspace warnings and issues.The following changes 
*           have been modify:
*       (1) Parentheses are added to polynomial expressions in the
*           CanXcp_GetRxMsg function.
*       (2) Call a function that has a return value but does not use its
*           return value, so add void to modify it.
* Cause: Update
*******************************************************************************
* Version: 3.34
* Author/Date: LinZhC/2024.03.13
* Change: 1.#if...#endif appending.
*         2.fixed and optimized logical issues with queue sending.
*         3.fixed an issue with QAC/Plyspace code check.
*         4.Optimize send/receive data processing logic to prevent array
*           overflows.
* Cause: Update
*******************************************************************************
* Version: 3.35
* Author/Date: LinZhC/2024.04.01
* Change: 1.remove redundant code.
*         2.modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.36
* Author/Date: KangJH/2024.05.22
* Change: Modify coding specification problems.
* Cause: Update
********************************************************************************
* Version: 3.37
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
* Version: 3.38
* Author/Date: KangJH/2024.07.09
* Change: Receive data 4-byte alignment.
* Cause: Bugfix
********************************************************************************
* Version: 3.39
* Author/Date: KangJH/2024.10.12
* Change: Add macro XCP_ONCAN_ENABLE to fix the errors when XCPonCAN function
*         is disable.
* Cause: Bugfix
********************************************************************************
* Version: 3.40
* Author/Date: KangJH/2024.10.13
* Change: Disable related functions when CanXcp is disabled.
* Cause: Bugfix
********************************************************************************
* Version: 3.41
* Author/Date: KangJH/2024.10.14
* Change: Move the header file Xcp.h reference to CanXcp.h.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "CanXcp.h"
#if( XCP_ONCAN_ENABLE == STD_ON )
#include "CanXcp_Lcfg.h"
#endif  /* XCP_ONCAN_ENABLE == STD_ON */

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
#if( XCP_ONCAN_ENABLE == STD_ON )
#define XCP_START_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"
static VAR(CanXcpFrame_st, XCP_VAR_NO_INIT) Xcp_CanFrameAry[XCPBLOCK_SIZE];
#define XCP_STOP_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
static VAR(uint8, XCP_VAR_INIT) Xcp_CanFrameIndex = XCP_INIT_0;
static VAR(uint8, XCP_VAR_INIT) Xcp_CanFrameCount = XCP_INIT_0;
static VAR(uint8, XCP_VAR_INIT) Xcp_CanFrameHeader = XCP_INIT_1;
static VAR(boolean, XCP_VAR_INIT) Xcp_CanModuleState = FALSE;
static VAR(uint8, XCP_VAR_INIT) Xcp_CanCommandTimeCounter = XCP_INIT_0;
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
VAR(uint8, XCP_VAR_INIT) Xcp_CanGetStatus = TRUE;
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
* Function Name: CanXcp_Init
*
* Explanation: CANXCP initialization.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) CanXcp_Init(void)
{
    Xcp_CanFrameIndex = XCP_INIT_0;
    Xcp_CanFrameCount = XCP_INIT_0;
    Xcp_CanFrameHeader = XCP_INIT_1;
    Xcp_CanGetStatus = TRUE;
    Xcp_CanCommandTimeCounter = XCP_INIT_0;
    XCP_gstCAN_msgvar_rx.msgmode = XCP_INIT_1;
    XCP_gstCAN_msgvar_tx.msgmode = XCP_INIT_1;
    Xcp_CanModuleState = TRUE;
}

/*
********************************************************************************
* Function Name: CanXcp_MainFunction
*
* Explanation: Called by XCP_main,Get Can messages and execute commands.
*
* param: None
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) CanXcp_MainFunction(void)
{
    uint8 avcDlc = XCP_INIT_0;
    /* The sequence number in the Xcp_ConnectionCfg list. */
    uint32 avConnectionId = XCP_INVALID_CONNECTION_ID;
    Xcp_CtoType acaMsg = {XCP_INIT_0};

    /* Get received msg. */
    if( XCP_E_OK == CanXcp_GetRxMsg(&avcDlc, &avConnectionId, &acaMsg.dwords[XCP_INDEX_0]) )
    {
        /* Handle command. */
        Xcp_Command((uint8)avConnectionId, (const Xcp_CtoType*) &acaMsg);
    }
}

/*
********************************************************************************
* Function Name: CanXcp_GetRxMsg
*
* Explanation: Get CAN messages.
*
* param: avcpDlc: ID of the received message.
*        avlpId: Length of the received message.
*
* retval: XCP_E_OK: get tx msg success.
*         XCP_E_NOT_OK: get tx msg fail.
********************************************************************************
*/
FUNC(uint8, XCP_CODE) CanXcp_GetRxMsg
(
    P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA) avcpDlc,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_DATA) avlpId,
    P2VAR(uint32, AUTOMATIC, XCP_APPL_DATA) avlpData
)
{
    Std_ReturnType retValue = XCP_E_NOT_OK;
    uint8 index;
    uint8 msgLen = XCP_INIT_0;
    uint8 msgLenFourtimes = XCP_INIT_0;

    /* Send confirmation timing. */
    Xcp_CanCommandTimeCounter++;
    if( XCP_VALUE_0 == Xcp_CanFrameCount )
    {
        Xcp_CanCommandTimeCounter = XCP_VALUE_0;
        if( TRUE != Xcp_CanGetStatus )
        {
            Xcp_CanGetStatus = TRUE;
        }
        retValue = XCP_E_NOT_OK;
    }
    else if( TRUE != Xcp_CanGetStatus )
    {
        /* Send confirmation timeout. */
        if( TRANSMITTIMEOUT < Xcp_CanCommandTimeCounter )
        {
            /* Xcp_MemClr(&Xcp_CanFrameAry, XCPBLOCK_SIZE * sizeof(XcpFrameAry)); */
            Xcp_CanGetStatus = TRUE;
            Xcp_CanFrameIndex = XCP_VALUE_0;
            Xcp_CanFrameCount = XCP_VALUE_0;
            Xcp_CanFrameHeader = XCP_VALUE_1;
        }
        retValue = XCP_E_NOT_OK;
    }
    else
    {
        Xcp_CanCommandTimeCounter = XCP_VALUE_0;
        if( XCP_CANFD_MAX_CTO < Xcp_CanFrameAry[Xcp_CanFrameHeader].length )
        {
            msgLen = XCP_CANFD_MAX_CTO;
        }
        else if( XCP_CAN_MAX_CTO >= Xcp_CanFrameAry[Xcp_CanFrameHeader].length )
        {
            msgLen = XCP_CAN_MAX_CTO;
        }
        else
        {
            msgLen = Xcp_CanFrameAry[Xcp_CanFrameHeader].length;
        }
        /* 4-byte alignment. */
        msgLen = SET_VALUE_ALIGN(msgLen, uint8, sizeof(uint32));
        *avlpId = Xcp_CanFrameAry[Xcp_CanFrameHeader].connectionId;
        *avcpDlc = msgLen;
        msgLenFourtimes = msgLen / XCP_BYTE_ALIGNMENT_4;

#if( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
        for( index = XCP_INDEX_0; index < msgLenFourtimes; index++ )
        {
            avlpData[index] = Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_3 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_2 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_1 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_0 + (index * XCP_VALUE_4)];
        }

#else
        for( index = XCP_INDEX_0; index < msgLenFourtimes; index++ )
        {
            avlpData[index] = Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_0 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_1 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_2 + (index * XCP_VALUE_4)];
            avlpData[index] = (avlpData[index] << XCP_SHIFT_8) + Xcp_CanFrameAry[Xcp_CanFrameHeader].data[XCP_INDEX_3 + (index * XCP_VALUE_4)];
        }

#endif  /* CPU_BYTE_ORDER == LOW_BYTE_FIRST */
        /* Clear receive flag. */
        Xcp_CanGetStatus = FALSE;
        Xcp_CanFrameCount--;
        if( Xcp_CanFrameHeader == (XCPBLOCK_SIZE - XCP_VALUE_1) )
        {
            Xcp_CanFrameHeader = XCP_VALUE_0;
        }
        else
        {
            Xcp_CanFrameHeader++;
        }
        retValue = XCP_E_OK;
    }

    return retValue;
}

/*
********************************************************************************
* Function Name: Xcp_CanIfRxIndication
*
* Explanation: Canif receive indicate.
*
* param: XcpRxPduId: ID of the received CAN_PDU.
*        XcpRxPduPtr: PduInfoType_structure.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_CanIfRxIndication
(
    PduIdType XcpRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, XCP_APPL_CONST) XcpRxPduPtr
)
{
    uint8 errorId = XCP_E_NO_ERROR;
    uint8 index = XCP_INVALID_XCP_PDU_ID;
    uint8 connectionId = XCP_INVALID_CONNECTION_ID;
    uint32 xcp_DateLen = XcpRxPduPtr->SduLength;
    uint8* Xcp_Stim_Date = (uint8*) XcpRxPduPtr->SduDataPtr;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( (XCP_BUS_NULL != Xcp_ConnectionStatus.busType) 
        && (XCP_BUS_CAN != Xcp_ConnectionStatus.busType)
        && (XCP_BUS_CANFD != Xcp_ConnectionStatus.busType) )
    {
        /* There are currently other buses connected to XCP. */
    }
    else if( Xcp_CanModuleState != TRUE )
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

                if( XcpRxPduId == Xcp_RxPdu[xcpConnCfgPtr->RxXcpPduIdRef].XcpPduRef )
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
                if( XcpRxPduId == Xcp_RxPdu[xcpConnCfgPtr->RxXcpPduIdRef].XcpPduRef )
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
            if( XCP_CANFD_MAX_CTO < XcpRxPduPtr->SduLength )
            {
                xcp_DateLen = XCP_CANFD_MAX_CTO;
            }
            else
            {
                xcp_DateLen = XcpRxPduPtr->SduLength;
            }
            /* Check Msg ID. */
            if( (*Xcp_Stim_Date) <= XCP_PID_STIM_END )
            {
#if( XCP_MULTIPDUIDSUPPORT == STD_OFF )
                Xcp_StimDataProcess(Xcp_Stim_Date, xcp_DateLen);
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_OFF */
            }
            else
            {
                Xcp_MemCpy8(CanXcp_RxPduInfo[XCP_INDEX_0].data, XcpRxPduPtr->SduDataPtr, xcp_DateLen);
                if( Xcp_CanFrameIndex == (XCPBLOCK_SIZE - XCP_VALUE_1) )
                {
                    Xcp_CanFrameIndex = XCP_VALUE_0;
                }
                else
                {
                    Xcp_CanFrameIndex++;
                }
                Xcp_CanFrameAry[Xcp_CanFrameIndex].ID = XCP_gstCAN_msgvar_rx.Id;
                Xcp_CanFrameAry[Xcp_CanFrameIndex].connectionId = connectionId;
                Xcp_CanFrameAry[Xcp_CanFrameIndex].length = (uint8)xcp_DateLen;
                for( index = XCP_INDEX_0; index < xcp_DateLen; ++index )
                {
                    Xcp_CanFrameAry[Xcp_CanFrameIndex].data[index] = XCP_gcaCAN_Msg_CRO[index];
                }
                /* Set Receive count */
                Xcp_CanFrameCount++;
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
* Function Name: Xcp_CanIfTxConfirmation
*
* Explanation: canif send completion prompt indicate.
*
* param: XcpTxPduId: PduID of the transmitted data.
*
* retval: None
********************************************************************************
*/
FUNC(void, XCP_CODE) Xcp_CanIfTxConfirmation(PduIdType XcpTxPduId)
{
    uint8 errorId = XCP_E_NO_ERROR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( TRUE != Xcp_CanModuleState )
    {
        errorId = XCP_E_NOT_INITIALIZED;
    }
    else
    {
        if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
        {
            xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
            /* Check Msg ID. */
            if( XcpTxPduId == Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduRef )
            {
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
                (void)Xcp_SendCallBack(xcpConnCfgPtr->TxXcpPduIdRef);
#else  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
                (void)Xcp_SendCallBack();
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */
            }
        }
#if( XCP_BLOCK_UPLOAD != STD_ON )
        Xcp_CanGetStatus = TRUE;
#endif  /* XCP_BLOCK_UPLOAD != STD_ON */
    }
    Xcp_Det_ErrorReport(XCP_SID_TXCONFIRMATION, errorId);
}

/*
********************************************************************************
* Function Name: CanXcp_Send
*
* Explanation: xcp messages are sent over the can bus.
*
* param: len: Data frame length.
*        msg: The address to send the message.
*
* retval: XCP_E_OK: Transmit request has been accepted.
*         XCP_E_NOT_OK: Transmit request has not been accepted.
********************************************************************************
*/
#if( XCP_MULTIPDUIDSUPPORT == STD_ON )
FUNC(Std_ReturnType, XCP_CODE) CanXcp_Send(uint8 pduid, uint32 len, P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg)
{
    uint8 acIndex;
    uint8 acaData[XCP_INDEX_8] = {XCP_INIT_0};
    PduInfoType canIfTxInfoPtr = {NULL_PTR, XCP_INIT_0};
    Std_ReturnType stdRet = XCP_E_NOT_OK;
    const uint8* src = NULL_PTR;
    uint8* dst = NULL_PTR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    canIfTxInfoPtr.SduLength = len;
    canIfTxInfoPtr.SduDataPtr = acaData;
    src = msg;
    dst = XCP_gcaCAN_Msg_DTO;

    for( acIndex = XCP_INDEX_0; acIndex < len; acIndex++ )
    {
        *dst = *src;
        canIfTxInfoPtr.SduDataPtr[acIndex] = *src;
        dst++;
        src++;
    }

    /* Call CanDriver Interface. */
    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
        stdRet = CanIf_Transmit(Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduRef, &canIfTxInfoPtr);
    }

    return stdRet;
}
#else
FUNC(Std_ReturnType, XCP_CODE) CanXcp_Send(uint32 len, P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST) msg)
{
    uint8 acIndex;
    uint8 acaData[XCP_CANFD_MAX_DTO] = {XCP_INIT_0};
    PduInfoType canIfTxInfoPtr = {NULL_PTR, XCP_INIT_0};
    Std_ReturnType stdRet = XCP_E_NOT_OK;
    const uint8* src = NULL_PTR;
    uint8* dst = NULL_PTR;
    const Xcp_ConnectionCfgType* xcpConnCfgPtr = NULL_PTR;

    if( XCP_CANFD_MAX_DTO < len )
    {
        canIfTxInfoPtr.SduLength = XCP_CANFD_MAX_DTO;
    }
    else
    {
        canIfTxInfoPtr.SduLength = len;
    }

    canIfTxInfoPtr.SduDataPtr = acaData;
    src = msg;
    dst = XCP_gcaCAN_Msg_DTO;

    for( acIndex = XCP_INDEX_0; acIndex < canIfTxInfoPtr.SduLength; acIndex++ )
    {
        *dst = *src;
        canIfTxInfoPtr.SduDataPtr[acIndex] = *src;
        dst++;
        src++;
    }
    /* Call CanDriver Interface. */
    if( XCP_CONNECTION_CFG_NUM > Xcp_ConnectionStatus.connectionId )
    {
        xcpConnCfgPtr = &Xcp_ConnectionCfg[Xcp_ConnectionStatus.connectionId];
        stdRet = CanIf_Transmit(Xcp_TxPdu[xcpConnCfgPtr->TxXcpPduIdRef].XcpPduRef, &canIfTxInfoPtr);
    }

    return stdRet;
}
#endif  /* XCP_MULTIPDUIDSUPPORT == STD_ON */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
#endif  /* XCP_ONCAN_ENABLE == STD_ON */
