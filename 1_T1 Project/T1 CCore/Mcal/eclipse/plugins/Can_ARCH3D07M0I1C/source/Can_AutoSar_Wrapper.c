/* PRQA S 0380, 1006, 3432, 2053 EOF */ 
/* PRQA S 0491, 2844, 3604 EOF */   /* CWE */
/**************************************************************************** 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : CAN
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Can_AutoSar_Wrapper.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "Can_AutoSar_Wrapper.h"
#include "Can_HAL_Wrapper.h"
#include "Can_Cfg.h"
#include "CanIf_Cbk.h"
#include "SchM_Can.h"
#include "Det.h"
#ifdef CAN_TIMEOUT_USE_OS
    #include "Os.h"
#endif

#define CAN_ATS_WRA_C_VENDOR_ID                     176
#define CAN_ATS_WRA_C_AR_REL_MAJOR_VER              4
#define CAN_ATS_WRA_C_AR_REL_MINOR_VER              4
#define CAN_ATS_WRA_C_AR_REL_REV_VER                0
#define CAN_ATS_WRA_C_SW_MAJOR_VER                  3
#define CAN_ATS_WRA_C_SW_MINOR_VER                  0
#define CAN_ATS_WRA_C_SW_PATCH_VER                  0

#if (CAN_CFG_H_VENDOR_ID != CAN_ATS_WRA_C_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_VENDOR_ID "
#endif
#if (CAN_CFG_H_AR_REL_MAJOR_VER != CAN_ATS_WRA_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_AR_REL_MAJOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_MINOR_VER != CAN_ATS_WRA_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_AR_REL_MINOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_REV_VER != CAN_ATS_WRA_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_AR_REL_REV_VER "
#endif
#if (CAN_CFG_H_SW_MAJOR_VER != CAN_ATS_WRA_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_SW_MAJOR_VER "
#endif
#if (CAN_CFG_H_SW_MINOR_VER != CAN_ATS_WRA_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_SW_MINOR_VER "
#endif
#if (CAN_CFG_H_SW_PATCH_VER != CAN_ATS_WRA_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_ATS_WRA_C_SW_PATCH_VER "
#endif

#define MCAN_TX_BUFFER_MAX 32U

typedef enum {
    MB_IDLE = 0U,
    MB_BUSY = 1U
} Can_MBStateType;

typedef struct {
    PduIdType           canIfPduId;
    Can_MBStateType     txMbState;
} Can_MBInfoType;

typedef struct {
    Can_MBInfoType txMbInfo[MCAN_TX_BUFFER_MAX];
} Can_ControllerInfo;

#define CAN_START_SEC_VAR_INIT
#include "Can_MemMap.h"
static VAR(Can_ControllerInfo, CAN_VAR) s_sCan_ControllerInfo[CAN_CONTROLLER_COUNT] = {
    {.txMbInfo[0] = {0U}} /*PRQA S 0691*/ 
};
#define CAN_STOP_SEC_VAR_INIT
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT
#include "Can_MemMap.h"
static VAR(uint8, CAN_VAR) s_u8Can_gInterDisableCnt[CAN_CONTROLLER_COUNT] = {0U};
#define CAN_STOP_SEC_VAR_INIT
#include "Can_MemMap.h"

#ifdef CanLPduReceiveCalloutFunction
extern FUNC(Std_ReturnType, CAN_CODE) CanLPduReceiveCalloutFunction \
( \
    VAR(uint8, AUTOMATIC) u8Can_Hrh, \
    VAR(Can_IdType, AUTOMATIC) u32Can_CanId, \
    VAR(uint8, AUTOMATIC) u8Can_Dlc, \
    P2CONST(uint8, AUTOMATIC, CAN_APPL_CONST) u8Can_SduPtr \
);
#endif

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(Std_ReturnType, CAN_CODE) Can_Wrapper_SetStopMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(PduLengthType, CAN_CODE) MCAN_Wrapper_ConvertDLCToDataLength \
( \
    VAR(uint16, AUTOMATIC) u16Can_Dlc \
)
{
    VAR(PduLengthType, AUTOMATIC) u32Can_DataLen = 0U;

    if (u16Can_Dlc <= 8U)
    {
        u32Can_DataLen = (PduLengthType)u16Can_Dlc;
    }
    else 
    {
        switch (u16Can_Dlc)
        {
        case 9U:  
        {
            u32Can_DataLen = 12U;
            break;
        }
        case 10U:
        {
            u32Can_DataLen = 16U;
            break;
        }
        case 11U:
        {
            u32Can_DataLen = 20U;
            break;
        }
        case 12U:
        {
            u32Can_DataLen = 24U;
            break;
        }
        case 13U:
        {
            u32Can_DataLen = 32U;
            break;
        }
        case 14U:
        {
            u32Can_DataLen = 48U;
            break;
        }
        case 15U:
        {
            u32Can_DataLen = 64U;
            break;
        }
        default:
        {
            u32Can_DataLen = 0U;
            break;
        }
        }
    }

    return u32Can_DataLen;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) MCAN_RxNotifiy \
( \
    VAR(uint8, AUTOMATIC) u8Can_ControllerIdx, \
    VAR(uint32, AUTOMATIC) u32Can_CanObjectId, \
    P2CONST(can_msg_struct, CAN_VAR, CAN_APPL_DATA) pCan_MsgInfo \
)
{
    VAR(Can_HwType, AUTOMATIC) sCan_Mailbox = {0U};
    VAR(PduInfoType, AUTOMATIC) sCan_PduInfo = {0U};

    sCan_Mailbox.Hoh = (Can_HwHandleType)u32Can_CanObjectId;
    sCan_Mailbox.ControllerId = u8Can_ControllerIdx;
    /*
        [SWS_Can_00501] CanDrv shall indicate whether the received message is a 
        conventional CAN frame or a CAN FD frame as described in Can_IdType.
    */
    if (pCan_MsgInfo->fdf == TRUE)
    {
        sCan_Mailbox.CanId = (pCan_MsgInfo->id | MCAN_FD_ID_DESCRIPTOR);
    }
    else
    {
        sCan_Mailbox.CanId = pCan_MsgInfo->id;
    }

    if (pCan_MsgInfo->idtype == EXTENDED_ID)
    {
        sCan_Mailbox.CanId |= MCAN_MSG_ID_EXT_MASK;
    }
    sCan_PduInfo.SduLength = MCAN_Wrapper_ConvertDLCToDataLength(pCan_MsgInfo->dlc);
    sCan_PduInfo.SduDataPtr = (uint8*)(uint32)pCan_MsgInfo->data;
    /*
        [SWS_Can_00279] On L-PDU reception, the Can module shall call the RX 
        indication callback function CanIf_RxIndication with ID, Hoh, abstract CanIf 
        ControllerId in parameter Mailbox, and the Data Length and pointer to the L-SDU 
        buffer in parameter PduInfoPtr.
        [SWS_Can_00396] The RX-interrupt service routine of the corresponding HW 
        resource or the function Can_MainFunction_Read in case of polling mode shall call 
        the callback function CanIf_RxIndication.
    */
#ifdef CanLPduReceiveCalloutFunction
    if (E_OK == CanLPduReceiveCalloutFunction
                (
                    (uint8)u32Can_CanObjectId,
                    sCan_Mailbox.CanId,
                    (uint8)sCan_PduInfo.SduLength,
                    sCan_PduInfo.SduDataPtr
                )
        )
    {
#endif
        CanIf_RxIndication(&sCan_Mailbox, &sCan_PduInfo);
#ifdef CanLPduReceiveCalloutFunction
    }
#endif
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_Rx_CallBack_Pro(VAR(uint8, AUTOMATIC) u8Can_ControllerId)
{
    (void)u8Can_ControllerId;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_Tx_CallBack_Pro(VAR(uint8, AUTOMATIC) u8Can_ControllerId)
{
    VAR(uint8, AUTOMATIC) u8Can_MbIndex = 0U;
    VAR(uint8, AUTOMATIC) u8Can_TempNum = 0U;
    P2VAR(Can_MBInfoType, AUTOMATIC, CAN_APPL_DATA) pCan_MsgInfo = NULL_PTR;

    pCan_MsgInfo = s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo;
    u8Can_TempNum = g_pCan_CurConfig->controllerConfig[u8Can_ControllerId]/* polyspace RTE:IDP */
                    .txbufferconfig->ded_buffers_number;
    for (u8Can_MbIndex = 0U; u8Can_MbIndex < u8Can_TempNum; u8Can_MbIndex++)
    {
        if (TRUE == Can_Wrapper_isTxInterruptMb(u8Can_ControllerId, u8Can_MbIndex))
        {
            SchM_Enter_CAN_EXCLUSIVE_AREA_16();
            if ((TRUE == Can_Wrapper_TxOccurred(u8Can_ControllerId, u8Can_MbIndex))
                && (pCan_MsgInfo[u8Can_MbIndex].txMbState == MB_BUSY))/* polyspace RTE:IDP */
            {
                pCan_MsgInfo[u8Can_MbIndex].txMbState = MB_IDLE;
                SchM_Exit_CAN_EXCLUSIVE_AREA_16();
                CanIf_TxConfirmation(pCan_MsgInfo[u8Can_MbIndex].canIfPduId);
            }
            else
            {
                SchM_Exit_CAN_EXCLUSIVE_AREA_16();
            }
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_BusOff_CallBack_Pro(VAR(uint8, AUTOMATIC) u8Can_ControllerId)
{
    (void)Can_Wrapper_SetStopMode(u8Can_ControllerId);
    CanIf_ControllerBusOff(u8Can_ControllerId);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_InitController(VAR(uint8, AUTOMATIC) u8Can_ControllerId)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, CAN_VAR) u32Can_TimeOutDuration;
    VAR(uint8, AUTOMATIC) u8Can_TempIndex = 0U;
#ifdef CAN_TIMEOUT_USE_OS
    VAR(float32, AUTOMATIC) f32Can_TempTimeOut;

    f32Can_TempTimeOut = (float32)(CAN_TIMEOUT_DURATION / (float32)CAN_TIMEOUT_COUNTER_TICK2NS());
    if ((f32Can_TempTimeOut - (float32)((uint32)f32Can_TempTimeOut)) > (float32)0)
    {
        u32Can_TimeOutDuration = (uint32)f32Can_TempTimeOut + 1U;
    }
    else
    {
        u32Can_TimeOutDuration = (uint32)f32Can_TempTimeOut;
    }
#else
    u32Can_TimeOutDuration = CAN_TIMEOUT_DURATION;
#endif
    Can_Wrapper_SetTimeOut(u32Can_TimeOutDuration);
    u8Can_ret = Can_Wrapper_InitController(u8Can_ControllerId);
    Can_Wrapper_InitCallback(&Can_Rx_CallBack_Pro, &Can_Tx_CallBack_Pro, &Can_BusOff_CallBack_Pro, 
                            g_pCan_CurConfig->controllerConfig[u8Can_ControllerId].ErrorNotification,
                            g_pCan_CurConfig->controllerConfig[u8Can_ControllerId].MRAFNotification);
    for (u8Can_TempIndex = 0U; u8Can_TempIndex < MCAN_TX_BUFFER_MAX; u8Can_TempIndex++)
    {
        SchM_Enter_CAN_EXCLUSIVE_AREA_00();
        s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo[u8Can_TempIndex].txMbState = MB_IDLE;
        s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo[u8Can_TempIndex].canIfPduId = 0U;
        SchM_Exit_CAN_EXCLUSIVE_AREA_00();
    }
    s_u8Can_gInterDisableCnt[u8Can_ControllerId] = 0U;
    if (u8Can_ret == (Std_ReturnType)E_OK)
    {
        /*
            [SWS_Can_00259] The function Can_Init shall set all CAN controllers in the state STOPPED.
        */
        g_eCan_ControllerState[u8Can_ControllerId] = CAN_CS_STOPPED;
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_DeInitController(VAR(uint8, AUTOMATIC) u8Can_ControllerId)
{
    VAR(uint8, AUTOMATIC) u8Can_TempIndex = 0U;

    if ((Can_Wrapper_isSleep(u8Can_ControllerId)) == TRUE)
    {
        Can_Wrapper_exitSleep(u8Can_ControllerId);
    }
    Can_Wrapper_DeInitController(u8Can_ControllerId);

    for (u8Can_TempIndex = 0U; u8Can_TempIndex < MCAN_TX_BUFFER_MAX; u8Can_TempIndex++)
    {
        SchM_Enter_CAN_EXCLUSIVE_AREA_23();
        s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo[u8Can_TempIndex].txMbState = MB_IDLE;
        s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo[u8Can_TempIndex].canIfPduId = 0U;
        SchM_Exit_CAN_EXCLUSIVE_AREA_23();
    }
    s_u8Can_gInterDisableCnt[u8Can_ControllerId] = 0U;
    g_eCan_ControllerState[u8Can_ControllerId] = CAN_CS_UNINIT;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(Std_ReturnType, CAN_CODE) Can_Wrapper_SetStartMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;
    if (CAN_CS_STOPPED != g_eCan_ControllerState[u8Can_Controller])
    {
        /*
            [SWS_Can_00409] When the function Can_SetControllerMode
            (CAN_CS_STARTED) is entered and the CAN controller is not in state STOPPED it 
            shall detect a invalid state transition
        */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, CAN_SID_SET_CONTROLLER_MODE, CAN_E_TRANSITION);
#endif
    }
    else 
    {
        /* SWS_Can_00384 */
        /*
            [SWS_Can_00261] The function Can_SetControllerMode(CAN_CS_STARTED)
            shall set the hardware registers in a way that makes the CAN controller participating 
            on the network.
            [SWS_Can_00196] The function Can_SetControllerMode shall enable interrupts 
            that are needed in the new state.
        */
        Can_AutoSar_Wrapper_InitController(u8Can_Controller);
        Can_Wrapper_RsetInit(u8Can_Controller);
        /*
            [SWS_Can_00425] Enabling of CAN interrupts shall not be executed, when CAN 
            interrupts have been disabled by function Can_DisableControllerInterrupts.
            [SWS_Can_00426] Disabling of CAN interrupts shall not be executed, when CAN 
            interrupts have been disabled by function Can_DisableControllerInterrupts.
        */
        if (s_u8Can_gInterDisableCnt[u8Can_Controller] == 0U)
        {
            Can_Wrapper_DisableInterrupts(u8Can_Controller);
            Can_Wrapper_EnableInterrupts(u8Can_Controller);
        }

        u8Can_ret = (Std_ReturnType)E_OK;
    }
    return u8Can_ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(Std_ReturnType, CAN_CODE) Can_Wrapper_SetSleepMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;
    /*
        [SWS_Can_00405]  This logical sleep mode shall left only, if function
        Can_SetControllerMode(CAN_CS_STOPPED) is called.
        [SWS_Can_00411]  When the function Can_SetControllerMode(CAN_CS_SLEEP)
        is entered and the CAN controller is neither in state STOPPED nor in state SLEEP, it 
        shall detect a invalid state transition
    */
    if (CAN_CS_STARTED == g_eCan_ControllerState[u8Can_Controller])
    {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, CAN_SID_SET_CONTROLLER_MODE, CAN_E_TRANSITION);
#endif
    }
    else 
    {
        if (CAN_CS_SLEEP == g_eCan_ControllerState[u8Can_Controller])
        {
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        else
        {
            /*
                [SWS_Can_00404] The CAN hardware shall remain in state STOPPED, while the 
                logical SLEEP state is active
                [SWS_Can_00265] The function Can_SetControllerMode(CAN_CS_SLEEP) shall 
                set the controller into sleep mode.
                [SWS_Can_00290] If the CAN HW does not support a sleep mode, the function 
                Can_SetControllerMode(CAN_CS_SLEEP) shall set the CAN controller to the logical sleep mode.
            */
            u8Can_ret = Can_Wrapper_EnterSleep(u8Can_Controller);
        }
    }
    return u8Can_ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(Std_ReturnType, CAN_CODE) Can_Wrapper_SetStopMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;
    VAR(uint8, AUTOMATIC) u8Can_TempIndex = 0U;

    if (CAN_CS_STOPPED == g_eCan_ControllerState[u8Can_Controller])
    {
        u8Can_ret = (Std_ReturnType)E_OK;
    }
    else 
    {
        if (CAN_CS_STARTED == g_eCan_ControllerState[u8Can_Controller])
        {
            /*
                [SWS_Can_00263] The function Can_SetControllerMode(CAN_CS_STOPPED)
                shall set the bits inside the CAN hardware such that the CAN controller stops 
                participating on the network.
                [SWS_Can_00282]  The function Can_SetControllerMode(CAN_CS_STOPPED)
                shall cancel pending messages.
            */
            Can_Wrapper_DeInitController(u8Can_Controller);
            for (u8Can_TempIndex = 0U; u8Can_TempIndex < MCAN_TX_BUFFER_MAX; u8Can_TempIndex++)
            {
                SchM_Enter_CAN_EXCLUSIVE_AREA_01();
                s_sCan_ControllerInfo[u8Can_Controller].txMbInfo[u8Can_TempIndex].txMbState = MB_IDLE;
                s_sCan_ControllerInfo[u8Can_Controller].txMbInfo[u8Can_TempIndex].canIfPduId = 0U;
                SchM_Exit_CAN_EXCLUSIVE_AREA_01();
            }
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STOPPED;
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        else if (CAN_CS_SLEEP == g_eCan_ControllerState[u8Can_Controller])
        {
            /*
                [SWS_Can_00267]  If the CAN HW does not support a sleep mode, the transition
                from SLEEP to STOPPED shall return from the logical sleep mode, but have no 
                effect to the CAN controller state (as the controller is already in stopped state)
            */
            if ((Can_Wrapper_isSleep(u8Can_Controller)) == TRUE)
            {
                Can_Wrapper_exitSleep(u8Can_Controller);
            }
            Can_Wrapper_DeInitController(u8Can_Controller);
            for (u8Can_TempIndex = 0U; u8Can_TempIndex < MCAN_TX_BUFFER_MAX; u8Can_TempIndex++)
            {
                SchM_Enter_CAN_EXCLUSIVE_AREA_02();
                s_sCan_ControllerInfo[u8Can_Controller].txMbInfo[u8Can_TempIndex].txMbState = MB_IDLE;
                s_sCan_ControllerInfo[u8Can_Controller].txMbInfo[u8Can_TempIndex].canIfPduId = 0U;
                SchM_Exit_CAN_EXCLUSIVE_AREA_02();
            }
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STOPPED;
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        else
        {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError \
            ( \
                (uint16)CAN_MODULE_ID, \
                (uint8)CAN_INSTANCE, \
                CAN_SID_SET_CONTROLLER_MODE, \
                CAN_E_TRANSITION \
            );
#endif
        }
    }
    return u8Can_ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(Std_ReturnType, CAN_CODE) Can_AutoSar_Wrapper_SetControllerMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller, \
    VAR(Can_ControllerStateType, AUTOMATIC) eCan_Transition \
)
{
    /*
        [SWS_Can_00200] If development error detection for the Can module is enabled: if 
        an invalid transition has been requested, the function Can_SetControllerMode shall 
        raise the error CAN_E_TRANSITION and return E_NOT_OK.
    */
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;

    switch (eCan_Transition)
    {
    case CAN_CS_STARTED: 
    {
        /*
            [SWS_Can_00384]  Each time the CAN controller state machine is triggered with
            the state transition value CAN_CS_STARTED, the function Can_SetControllerMode
            shall re-initialize the CAN controller with the same controller configuration set 
            previously used by functions Can_SetBaudrate or Can_Init
        */
        if ((Std_ReturnType)E_OK == Can_Wrapper_SetStartMode(u8Can_Controller))
        {
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STARTED;
            CanIf_ControllerModeIndication(u8Can_Controller, CAN_CS_STARTED);
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        break;
    }
    case CAN_CS_SLEEP: 
    {
        if ((Std_ReturnType)E_OK == Can_Wrapper_SetSleepMode(u8Can_Controller))
        {
            /*
                [SWS_Can_00257] When the CAN hardware supports sleep mode and is triggered 
                to transition into SLEEP state, the Can module shall set the controller to the SLEEP 
                state from which the hardware can be woken over CAN Bus.
                [SWS_Can_00258] When the CAN hardware does not support sleep mode and is 
                triggered to transition into SLEEP state, the Can module shall emulate a logical 
                SLEEP state from which it returns only, when it is triggered by software to transition 
                into STOPPED state.
            */
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_SLEEP;
            CanIf_ControllerModeIndication(u8Can_Controller, CAN_CS_SLEEP);
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        break;
    }
    case CAN_CS_STOPPED: 
    {
        if ((Std_ReturnType)E_OK == Can_Wrapper_SetStopMode(u8Can_Controller))
        {
            CanIf_ControllerModeIndication(u8Can_Controller, CAN_CS_STOPPED);
            u8Can_ret = (Std_ReturnType)E_OK;
        }
        break;
    }
    default:
    {
        /* do nothing */
        break;
    }
    }

    return u8Can_ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_DisableInterrupts(VAR(uint8, AUTOMATIC) u8Can_Controller)
{
    /*
        [SWS_Can_00426] Disabling of CAN interrupts shall not be executed, when CAN 
        interrupts have been disabled by function Can_DisableControllerInterrupts.
    */
    SchM_Enter_CAN_EXCLUSIVE_AREA_12();
    s_u8Can_gInterDisableCnt[u8Can_Controller]++;
    if (1U == s_u8Can_gInterDisableCnt[u8Can_Controller])
    {
        SchM_Exit_CAN_EXCLUSIVE_AREA_12();
        /*
            [SWS_Can_00049] The function Can_DisableControllerInterrupts shall access the 
            CAN controller registers to disable all interrupts for that CAN controller only, if 
            interrupts for that CAN Controller are enabled.
        */
        Can_Wrapper_DisableInterrupts(u8Can_Controller);
    }
    else
    {
        SchM_Exit_CAN_EXCLUSIVE_AREA_12();
    }
    /*
        [SWS_Can_00202] When Can_DisableControllerInterrupts has been called several 
        times, Can_EnableControllerInterrupts must be called as many times before the 
        interrupts are re-enabled.
    */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_EnableInterrupts(VAR(uint8, AUTOMATIC) u8Can_Controller)
{
    if (s_u8Can_gInterDisableCnt[u8Can_Controller] > 0U)
    {
        /*
            [SWS_Can_00208] The function Can_EnableControllerInterrupts shall perform no 
            action when Can_DisableControllerInterrupts has not been called before.
        */
        SchM_Enter_CAN_EXCLUSIVE_AREA_14();
        s_u8Can_gInterDisableCnt[u8Can_Controller]--;
        if (s_u8Can_gInterDisableCnt[u8Can_Controller] == 0U)
        {
            Can_Wrapper_EnableInterrupts(u8Can_Controller);
            SchM_Exit_CAN_EXCLUSIVE_AREA_14();
        }
        else
        {
            SchM_Exit_CAN_EXCLUSIVE_AREA_14();
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(Can_ErrorStateType, CAN_CODE) Can_AutoSar_Wrapper_GetErrorState \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(Can_ErrorStateType, AUTOMATIC)  eCan_CtrlErrState = CAN_ERRORSTATE_BUSOFF;
    if ((Can_Wrapper_IsBusOff(u8Can_Controller)) == TRUE)
    {
        eCan_CtrlErrState = CAN_ERRORSTATE_BUSOFF;
    }
    else if ((Can_Wrapper_IsErrorActive(u8Can_Controller)) == TRUE)
    {
        eCan_CtrlErrState = CAN_ERRORSTATE_ACTIVE;
    }
    else 
    {
        eCan_CtrlErrState = CAN_ERRORSTATE_PASSIVE;
    }
    return eCan_CtrlErrState;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(Can_ControllerStateType, CAN_CODE) Can_AutoSar_Wrapper_GetMode \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(Can_ControllerStateType, AUTOMATIC) eCan_Data = CAN_CS_UNINIT;
    if (u8Can_Controller < CAN_CONTROLLER_COUNT)
    {
        eCan_Data = g_eCan_ControllerState[u8Can_Controller];
    }
    else
    {
        /* do nothing */
    }
    return eCan_Data;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_AutoSar_Wrapper_GetRxErrorCounter \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    return Can_Wrapper_GetRxErrorCounter(u8Can_Controller);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_AutoSar_Wrapper_GetTxErrorCounter(VAR(uint8, AUTOMATIC) u8Can_Controller)
{
    return Can_Wrapper_GetTxErrorCounter(u8Can_Controller);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(Std_ReturnType, CAN_CODE) Can_AutoSar_Wrapper_Write \
( \
    VAR(Can_HwHandleType, AUTOMATIC) u16Can_Hth, \
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) pCan_PduInfo \
)
{
    VAR(Std_ReturnType, AUTOMATIC) u8Can_ret = (Std_ReturnType)E_NOT_OK;
    VAR(uint32, AUTOMATIC) u32Can_TempIdex = 0U;
    P2VAR(Can_MBInfoType, AUTOMATIC, CAN_APPL_DATA) pCan_MbInfo = NULL_PTR;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_TempHwObj = NULL_PTR;
#if (CAN_MULTICORE_ENABLED == STD_ON)
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
#endif
#if (CAN_TRIGGER_TRANSMIT_EN == STD_ON)
    VAR(PduInfoType, AUTOMATIC) sCan_TxPduInfo = {NULL_PTR, 0U};
    #if (STD_ON == CAN_FD_MODE_ENABLE)
        VAR(uint8, AUTOMATIC) u8Can_TxSduData[64] = {0U};
    #else
        VAR(uint8, AUTOMATIC) u8Can_TxSduData[8] = {0U};
    #endif
    VAR(Can_PduType, AUTOMATIC) Can_TriggerPdu = {0U};
#endif

    for (u32Can_TempIdex = 0; u32Can_TempIdex < CAN_MB_COUNT; u32Can_TempIdex++)
    {
        pCan_TempHwObj = &g_pCan_CurConfig->hwObjectConfig[u32Can_TempIdex];/* polyspace RTE:IDP */
        if ((u16Can_Hth == pCan_TempHwObj->CanObjectId) \
            && (pCan_TempHwObj->CanObjectType == TRANSMIT))
        {
            /*
                [SWS_Can_00218] The function Can_Write shall return E_NOT_OK and if 
                development error detection for the CAN module is enabled shall raise the error 
                CAN_E_PARAM_DATA_LENGTH
                [SWS_Can_00486] The CAN Frame has to be sent according to the two most
                significant bits of Can_PduType->id. The CAN FD frame bit is only evaluated if
                CAN Controller is in CAN FD mode (valid CanControllerFdBaudrateConfig).
            */
            if (((pCan_PduInfo->length > 64U) \
                || (pCan_PduInfo->length > pCan_TempHwObj->mbPayloadLength)) \
                || ((pCan_PduInfo->length > 8U) \
                && ((Can_Wrapper_IsFDEnabled(((uint8)pCan_TempHwObj->CanControllerId)) == 0U) \
                                        || ((pCan_PduInfo->id & MCAN_FD_ID_DESCRIPTOR) == 0U))))
            {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, CAN_SID_WRITE,
                                    CAN_E_PARAM_DATA_LENGTH);
#endif
                break;
            }
#if (CAN_MULTICORE_ENABLED == STD_ON)
            else if (u32Can_CoreId != g_pCan_CurConfig->coreMap[pCan_TempHwObj->CanControllerId].CoreId)/* polyspace RTE:IDP */
            {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE, CAN_SID_WRITE,
                                        CAN_E_PARAM_CONFIG);
                break;
#endif
            }
#endif
            else
            {
                pCan_MbInfo = s_sCan_ControllerInfo[pCan_TempHwObj->CanControllerId].txMbInfo;
                if (pCan_MbInfo[pCan_TempHwObj->mbIdex].txMbState == MB_IDLE)/* polyspace RTE:IDP */
                {
                    pCan_MbInfo[pCan_TempHwObj->mbIdex].txMbState = MB_BUSY;
                    pCan_MbInfo[pCan_TempHwObj->mbIdex].canIfPduId = pCan_PduInfo->swPduHandle;
#if (CAN_TRIGGER_TRANSMIT_EN == STD_ON)
                    /*
                        [SWS_Can_00504] If the trigger transmit API is enabled for the hardware object, 
                        Can_Write() shall interpret a null pointer as SDU (Can_PduType.Can_SduPtrType = 
                        NULL) as request for using the trigger transmit interface. If so and the hardware 
                        object is free, Can_Write() shall call CanIf_TriggerTransmit() with the maximum size 
                        of the message buffer to acquire the PDU’s data.
                    */
                    if (pCan_PduInfo->sdu == NULL_PTR)
                    {
                        SchM_Enter_CAN_EXCLUSIVE_AREA_03();
                        sCan_TxPduInfo.SduDataPtr = u8Can_TxSduData;
                        sCan_TxPduInfo.SduLength = pCan_PduInfo->length;
                        SchM_Exit_CAN_EXCLUSIVE_AREA_03();
                        u8Can_ret = CanIf_TriggerTransmit(pCan_PduInfo->swPduHandle, &sCan_TxPduInfo);
                        /*
                            [SWS_Can_00506] Can_Write() shall return E_NOT_OK if the trigger transmit API 
                            (CanIf_TriggerTransmit()) returns E_NOT_OK.
                        */
                        if ((Std_ReturnType)E_OK == u8Can_ret)
                        {
                            SchM_Enter_CAN_EXCLUSIVE_AREA_04();
                            Can_TriggerPdu.swPduHandle = pCan_PduInfo->swPduHandle;
                            Can_TriggerPdu.length = (uint8)(sCan_TxPduInfo.SduLength);
                            Can_TriggerPdu.id = pCan_PduInfo->id;
                            Can_TriggerPdu.sdu = sCan_TxPduInfo.SduDataPtr;
                            SchM_Exit_CAN_EXCLUSIVE_AREA_04();
                            u8Can_ret = Can_Wrapper_Write \
                                        ( \
                                            u32Can_TempIdex, \
                                            &Can_TriggerPdu, \
                                            (uint8)(pCan_TempHwObj->mbIdex), \
                                            pCan_TempHwObj->CanFdPaddingValue \
                                        );
                        }
                        else
                        {
                            SchM_Enter_CAN_EXCLUSIVE_AREA_05();
                            pCan_MbInfo[pCan_TempHwObj->mbIdex].txMbState = MB_IDLE;
                            SchM_Exit_CAN_EXCLUSIVE_AREA_05();
                        }
                    }
                    else
                    {
#endif  
                        u8Can_ret = Can_Wrapper_Write \
                                    ( \
                                        u32Can_TempIdex, \
                                        pCan_PduInfo, \
                                        (uint8)(pCan_TempHwObj->mbIdex), \
                                        pCan_TempHwObj->CanFdPaddingValue \
                                    );
#if (CAN_TRIGGER_TRANSMIT_EN == STD_ON)
                    }
#endif
                    if ((Std_ReturnType)E_OK != u8Can_ret)
                    {
                        /*
                            [SWS_Can_00214] The function Can_Write shall return CAN_BUSY if a 
                            preemptive call of Can_Write has been issued, that could not be handled reentrant 
                            (i.e. a call with the same HTH).
                        */
                        u8Can_ret = CAN_BUSY;
                    }
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
                    /*
                        [SWS_Can_00277] The Can module shall allow that the functionality "Multiplexed 
                        Transmission" is statically configurable (ON | OFF) at pre-compile time.
                        [SWS_Can_00402]
                        [SWS_Can_00403] The Can module shall support multiplexed transmission for 
                        devices, which send L-PDUs in order of L-PDU priority.
                    */
                    if (u8Can_ret == E_OK)
                    {
                        break;
                    }
#else /* CAN_MULTIPLEXED_TRANSMISSION */
                    break;
#endif /* CAN_MULTIPLEXED_TRANSMISSION */
                }
                else
                {
                    u8Can_ret = CAN_BUSY;
                }
            }
        }
    }
    return u8Can_ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_TxPolling(VAR(uint32, AUTOMATIC) u32Can_HwObjectIdex)
{
    VAR(uint8, AUTOMATIC) u8Can_ControllerId = 0U;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_HwObject = NULL_PTR;
    P2VAR(Can_MBInfoType, AUTOMATIC, CAN_APPL_DATA) pCan_MbInfo = NULL_PTR;
#if (CAN_MULTICORE_ENABLED == STD_ON)
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
#endif
    pCan_HwObject = &g_pCan_CurConfig->hwObjectConfig[u32Can_HwObjectIdex];
    u8Can_ControllerId = (uint8)(pCan_HwObject->CanControllerId);/* polyspace RTE:IDP */
#if (CAN_MULTICORE_ENABLED == STD_ON)
    if (u32Can_CoreId == g_pCan_CurConfig->coreMap[u8Can_ControllerId].CoreId)
    {
#endif
        pCan_MbInfo = s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo;
        if ((pCan_HwObject->isPolling == 1U) && (pCan_HwObject->CanObjectType == TRANSMIT))
        {
            if (TRUE == Can_Wrapper_TxOccurred(u8Can_ControllerId, pCan_HwObject->mbIdex))
            {
                /*
                    [SWS_Can_00276] The function Can_Write shall store the swPduHandle that is 
                    given inside the parameter PduInfo until the Can module calls the 
                    CanIf_TxConfirmation for this request where the swPduHandle is given as parameter.
                    [SWS_Can_00016] The Can module shall call CanIf_TxConfirmation to indicate a 
                    successful transmission. It shall either called by the TX-interrupt service routine of 
                    the corresponding HW resource or inside the Can_MainFunction_Write in case of 
                    polling mode.
                */
                SchM_Enter_CAN_EXCLUSIVE_AREA_19();
                if (pCan_MbInfo[pCan_HwObject->mbIdex].txMbState == MB_BUSY)/* polyspace RTE:IDP */
                {
                    pCan_MbInfo[pCan_HwObject->mbIdex].txMbState = MB_IDLE;
                    SchM_Exit_CAN_EXCLUSIVE_AREA_19();
                    CanIf_TxConfirmation(pCan_MbInfo[pCan_HwObject->mbIdex].canIfPduId);
                }
                else
                {
                    SchM_Exit_CAN_EXCLUSIVE_AREA_19();
                }
            }
        }
#if (CAN_MULTICORE_ENABLED == STD_ON)
    }
#endif
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_TxPollingMul \
( \
    VAR(uint32, AUTOMATIC) u32Can_HwObjectIdex, \
    VAR(uint8, AUTOMATIC) u8Can_PeriodIdx \
)
{
    VAR(uint8, AUTOMATIC) u8Can_ControllerId = 0U;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_HwObject = NULL_PTR;
    P2VAR(Can_MBInfoType, AUTOMATIC, CAN_APPL_DATA) pCan_MbInfo = NULL_PTR;
#if (CAN_MULTICORE_ENABLED == STD_ON)
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
#endif
    pCan_HwObject = &g_pCan_CurConfig->hwObjectConfig[u32Can_HwObjectIdex];/* polyspace RTE:IDP */
    u8Can_ControllerId = (uint8)(pCan_HwObject->CanControllerId);/* polyspace RTE:IDP */
#if (CAN_MULTICORE_ENABLED == STD_ON)
    if (u32Can_CoreId == g_pCan_CurConfig->coreMap[u8Can_ControllerId].CoreId)
    {
#endif
        pCan_MbInfo = s_sCan_ControllerInfo[u8Can_ControllerId].txMbInfo;
        if ((pCan_HwObject->isPolling == 1U) && (pCan_HwObject->CanObjectType == TRANSMIT) \
            && (u8Can_PeriodIdx == pCan_HwObject->PeriodIndex))
        {
            if (TRUE == Can_Wrapper_TxOccurred(u8Can_ControllerId, pCan_HwObject->mbIdex))
            {
                /*
                    [SWS_Can_00276] The function Can_Write shall store the swPduHandle that is 
                    given inside the parameter PduInfo until the Can module calls the 
                    CanIf_TxConfirmation for this request where the swPduHandle is given as parameter.
                    [SWS_Can_00016] The Can module shall call CanIf_TxConfirmation to indicate a 
                    successful transmission. It shall either called by the TX-interrupt service routine of 
                    the corresponding HW resource or inside the Can_MainFunction_Write in case of 
                    polling mode.
                */
                SchM_Enter_CAN_EXCLUSIVE_AREA_17();
                if (pCan_MbInfo[pCan_HwObject->mbIdex].txMbState == MB_BUSY)/* polyspace RTE:IDP */
                {
                    pCan_MbInfo[pCan_HwObject->mbIdex].txMbState = MB_IDLE;
                    SchM_Exit_CAN_EXCLUSIVE_AREA_17();
                    CanIf_TxConfirmation(pCan_MbInfo[pCan_HwObject->mbIdex].canIfPduId);
                }
                else
                {
                    SchM_Exit_CAN_EXCLUSIVE_AREA_17();
                }
            }
        }
#if (CAN_MULTICORE_ENABLED == STD_ON)
    }
#endif
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_RxPolling(VAR(uint8, AUTOMATIC) u8Can_ControllerIdx)
{
    VAR(uint32, AUTOMATIC) u32Can_HwObjectIdex = 0U;
    VAR(uint8, AUTOMATIC) u8Can_IsDataLost = 0U;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_HwObject = NULL_PTR;

    for (u32Can_HwObjectIdex = 0; u32Can_HwObjectIdex < g_pCan_CurConfig->HwObjCount; u32Can_HwObjectIdex++)
    {
        pCan_HwObject = &g_pCan_CurConfig->hwObjectConfig[u32Can_HwObjectIdex];
        if ((pCan_HwObject->isPolling == 1U) /* polyspace RTE:IDP */
            && (pCan_HwObject->CanObjectType == RECEIVE) \
            && (u8Can_ControllerIdx == pCan_HwObject->CanControllerId))
        {
            if (pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO0)
            {
                u8Can_IsDataLost = Can_Wrapper_IsDataLost(u8Can_ControllerIdx, 0U);
                if (u8Can_IsDataLost == 1U)
                {
                    (void)Det_ReportRuntimeError \
                    ( \
                        (uint16)CAN_MODULE_ID, \
                        (uint8)CAN_INSTANCE, \
                        (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                        (uint8)CAN_E_DATALOST \
                    );
                }
                (void)Can_Wrapper_RxRecFifoMsg(u8Can_ControllerIdx, 0U);
            }
            else if (pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO1)
            {
                u8Can_IsDataLost = Can_Wrapper_IsDataLost(u8Can_ControllerIdx, 1U);
                if (u8Can_IsDataLost == 1U)
                {
                    (void)Det_ReportRuntimeError \
                    ( \
                        (uint16)CAN_MODULE_ID, \
                        (uint8)CAN_INSTANCE, \
                        (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                        (uint8)CAN_E_DATALOST \
                    );
                }
                (void)Can_Wrapper_RxRecFifoMsg(u8Can_ControllerIdx, 1U);
            }
            else
            {
                (void)Can_Wrapper_RxDedicatedBufferProcessNewMsg(u8Can_ControllerIdx);
            }
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_RxPollingMul \
( \
    VAR(uint8, AUTOMATIC) u8Can_ControllerIdx, \
    VAR(uint8, AUTOMATIC) u8Can_PeriodIdx \
)
{
    VAR(uint32, AUTOMATIC) u32Can_HwObjectIdex = 0U;
    VAR(uint8, AUTOMATIC) u8Can_IsDataLost = 0U;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_HwObject = NULL_PTR;

    for (u32Can_HwObjectIdex = 0; u32Can_HwObjectIdex < g_pCan_CurConfig->HwObjCount; u32Can_HwObjectIdex++)/* polyspace RTE:IDP */
    {
        pCan_HwObject = &g_pCan_CurConfig->hwObjectConfig[u32Can_HwObjectIdex];

        if ((pCan_HwObject->isPolling == 1U) /* polyspace RTE:IDP */
                && (pCan_HwObject->CanObjectType == RECEIVE) \
                && (u8Can_ControllerIdx == pCan_HwObject->CanControllerId) \
                && (u8Can_PeriodIdx == pCan_HwObject->PeriodIndex))
        {
            if (pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO0)
            {
                u8Can_IsDataLost = Can_Wrapper_IsDataLost(u8Can_ControllerIdx, 0U);
                if (u8Can_IsDataLost == 1U)
                {
                    (void)Det_ReportRuntimeError \
                    ( \
                        (uint16)CAN_MODULE_ID, \
                        (uint8)CAN_INSTANCE, \
                        (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                        (uint8)CAN_E_DATALOST \
                    );
                }
                (void)Can_Wrapper_RxRecFifoMsg(u8Can_ControllerIdx, 0U);
            }
            else if (pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO1)
            {
                u8Can_IsDataLost = Can_Wrapper_IsDataLost(u8Can_ControllerIdx, 1U);
                if (u8Can_IsDataLost == 1U)
                {
                    (void)Det_ReportRuntimeError \
                    ( \
                        (uint16)CAN_MODULE_ID, \
                        (uint8)CAN_INSTANCE, \
                        (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                        (uint8)CAN_E_DATALOST \
                    );
                }
                (void)Can_Wrapper_RxRecFifoMsg(u8Can_ControllerIdx, 1U);
            }
            else
            {
                (void)Can_Wrapper_RxDedicatedBufferProcessNewMsg(u8Can_ControllerIdx);
            }
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_BusOffPolling(VAR(uint8, AUTOMATIC) u8Can_Controller)
{
    if ((Can_Wrapper_IsBusOff(u8Can_Controller)) == TRUE)
    {
        /*
            [SWS_Can_00272] After bus-off detection, the CAN controller shall transition to the 
            state STOPPED and the Can module shall ensure that the CAN controller doesn’t 
            participate on the network anymore.
            [SWS_Can_00273] After bus-off detection, the Can module shall cancel still 
            pending messages.
            [SWS_Can_00274] The Can module shall disable or suppress automatic bus-off recovery.
        */
        (void)Can_Wrapper_SetStopMode(u8Can_Controller);
        /* 
            [SWS_Can_00020] The CanIf module is notified with the function CanIf_ControllerBusOff after 
            STOPPED state is reached referring to the corresponding CAN controller with 
            the abstract CanIf ControllerId
        */
        CanIf_ControllerBusOff(u8Can_Controller);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_WakeUpPolling(VAR(uint8, AUTOMATIC) u8Can_Controller)
{
    if ((Can_Wrapper_isSleep(u8Can_Controller)) == TRUE)
    {
        SchM_Enter_CAN_EXCLUSIVE_AREA_22();
        Can_Wrapper_exitSleep(u8Can_Controller);
        g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STOPPED;
        SchM_Exit_CAN_EXCLUSIVE_AREA_22();
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_AutoSar_Wrapper_ControllerModePolling \
( \
    VAR(uint8, AUTOMATIC) u8Can_Controller \
)
{
    VAR(boolean, AUTOMATIC) bCan_Temp1 = FALSE;
    VAR(boolean, AUTOMATIC) bCan_Temp2 = FALSE;

    if (CAN_CS_SLEEP != g_eCan_ControllerState[u8Can_Controller])
    { 
        /*
            [SWS_Can_00370] The function Can_Mainfunction_Mode shall poll a flag of the 
            CAN status register until the flag signals that the change takes effect and notify the 
            upper layer with function CanIf_ControllerModeIndication about a successful state 
            transition referring to the corresponding CAN controller with the abstract CanIf ControllerId.
        */
        bCan_Temp1 = (boolean)((CAN_CS_STARTED == g_eCan_ControllerState[u8Can_Controller]) ? TRUE : FALSE);
        bCan_Temp2 = (boolean)((CAN_CS_STOPPED == g_eCan_ControllerState[u8Can_Controller]) ? TRUE : FALSE);
        if ((Can_Wrapper_isInitState(u8Can_Controller) == TRUE) && (bCan_Temp1 == TRUE))
        {
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STOPPED;
            /*
                [SWS_Can_00373]  The function Can_Mainfunction_Mode shall call the function
                CanIf_ControllerModeIndication to notify the upper layer about a successful state 
                transition of the corresponding CAN controller referred by abstract CanIf ControllerId, 
                in case the state transition was triggered by function Can_SetControllerMode.
            */
            CanIf_ControllerModeIndication(u8Can_Controller, CAN_CS_STOPPED);
        }
        else if ((Can_Wrapper_isInitState(u8Can_Controller) != TRUE) && (bCan_Temp2 == TRUE))
        {
            g_eCan_ControllerState[u8Can_Controller] = CAN_CS_STARTED;
            CanIf_ControllerModeIndication(u8Can_Controller, CAN_CS_STARTED);
        }
        else
        {
            /* nothing */
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif
