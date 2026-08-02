/* PRQA S 0380, 1006, 3432, 4558, 4115 EOF */
/* PRQA S 0491, 2844, 3604, 4397 EOF */   /* CWE */
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
*   @file    Can_LLDriver.c
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

 /*PRQA S 0380,1503,1505,3469,2016,2023,2024,2004,2984,0404,4404,0499,0654,2985 EOF*/
#include "Can_LLDriver.h"
#include "Can_Cfg.h"
#include "Can.h"
#include "SchM_Can.h"
#ifdef CAN_TIMEOUT_USE_OS
    #include "Os.h"
#endif

#define CAN_LLD_C_VENDOR_ID                     176
#define CAN_LLD_C_AR_REL_MAJOR_VER              4
#define CAN_LLD_C_AR_REL_MINOR_VER              4
#define CAN_LLD_C_AR_REL_REV_VER                0
#define CAN_LLD_C_SW_MAJOR_VER                  3
#define CAN_LLD_C_SW_MINOR_VER                  0
#define CAN_LLD_C_SW_PATCH_VER                  0

#if (CAN_CFG_H_VENDOR_ID != CAN_LLD_C_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_LLD_C_VENDOR_ID "
#endif
#if (CAN_CFG_H_AR_REL_MAJOR_VER != CAN_LLD_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_AR_REL_MAJOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_MINOR_VER != CAN_LLD_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_AR_REL_MINOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_REV_VER != CAN_LLD_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_AR_REL_REV_VER "
#endif
#if (CAN_CFG_H_SW_MAJOR_VER != CAN_LLD_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_SW_MAJOR_VER "
#endif
#if (CAN_CFG_H_SW_MINOR_VER != CAN_LLD_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_SW_MINOR_VER "
#endif
#if (CAN_CFG_H_SW_PATCH_VER != CAN_LLD_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_LLD_C_SW_PATCH_VER "
#endif

#define CAN_START_SEC_CONFIG_DATA
#include "Can_MemMap.h"
CONSTP2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) g_mcanBase[MCAN_INSTANCE_COUNT];
CONSTP2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) g_mcanBase[MCAN_INSTANCE_COUNT] = MCAN_BASE_PTRS;
#define CAN_STOP_SEC_CONFIG_DATA
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT
#include "Can_MemMap.h"
static VAR(uint32, CAN_VAR) s_u32Can_TimeOut[CAN_CORE_NUM] = {0U};
#define CAN_STOP_SEC_VAR_INIT
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT
#include "Can_MemMap.h"
static VAR(uint8, CAN_VAR) s_u32Can_IsTimeOut[CAN_CORE_NUM] = {0U};
#define CAN_STOP_SEC_VAR_INIT
#include "Can_MemMap.h"

extern VAR(uint16, CAN_VAR) g_u16Can_CurBaudRateId[CAN_CONTROLLER_COUNT];

extern VAR(Controller_mapping, AUTOMATIC) s_sInsToCtrlMap[CAN_MOD_BUTT];

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(status_t, CAN_CODE) Can_LLD_NecessarySpace \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(CANConfig, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(boolean, CAN_CODE) Can_LLD_TxIsReqPending \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_TxWriteMsgToBuffer \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buff_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_TxMsgSingleRequest \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_RxCopyMsgFromRamToList \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Msg_addr_in_msg_ram, \
    VAR(rx_info_struct, AUTOMATIC) sCan_Rx_info \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_RxRecDedicatedMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Ded_buffer_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"


#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(status_t,CAN_CODE)MCAN_MsgRamPartitioningCheck \
( \
    P2CONST(MCANPartitionConfig, AUTOMATIC, CAN_APPL_CONST) pCan_Data \
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) RamA = 0U;
    VAR(uint32, AUTOMATIC) RamB = 0U;
    VAR(uint32, AUTOMATIC) RamC = 0U;
    VAR(status_t, AUTOMATIC) eCan_StatusRet = STATUS_ERROR;

    for(i = 0U; i < MCAN_INSTANCE_COUNT; i++)
    {
        if(pCan_Data->McanCtrl[i].IsUsed == TRUE)
        {
            if(pCan_Data->McanCtrl[i].CanId < 4U)
            {
                RamA += pCan_Data->McanCtrl[i].mram_size_words;
            }
            else if(pCan_Data->McanCtrl[i].CanId < 8U)
            {
                RamB += pCan_Data->McanCtrl[i].mram_size_words;
            }
            else
            {
                RamC += pCan_Data->McanCtrl[i].mram_size_words;
            }
        }
    }
    if((RamA > FEATURE_MCAN_RAM_MESSAGES_WRD )|| (RamB > FEATURE_MCAN_RAM_MESSAGES_WRD)|| (RamC > FEATURE_MCAN_RAM_MESSAGES_WRD))
    {
        eCan_StatusRet = STATUS_ERROR;
    }
    else
    {
        eCan_StatusRet = STATUS_SUCCESS;
    }
    return eCan_StatusRet;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE)MCAN_ClearAllReceivedFlags \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    pCan_Base->NDAT1.R = 0xFFFFFFFFU;
    pCan_Base->NDAT2.R = 0xFFFFFFFFU;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) u32TotalElapsedTime = 0U;
#ifdef CAN_TIMEOUT_USE_OS
    static VAR(TickType, AUTOMATIC) CurrentValue[CAN_CORE_NUM] = {0U};
    static VAR(TickType, AUTOMATIC) ElapsedValue[CAN_CORE_NUM] = {0U};
#endif
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;
    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/

    if(((pCan_Base->CCCR.R & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT) == 0U)/* polyspace RTE:NIV */
    {
        pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_INIT_MASK) | MCAN_CCCR_INIT(1U);
        /*
            [SWS_Can_00398] The function Can_SetControllerMode shall use the system 
            service GetCounterValue for timeout monitoring to avoid blocking functions.
        */
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
        #endif
        while ((((pCan_Base->CCCR.R & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT) == 0U) \
               && ((u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId])))/* polyspace RTE:OBAI */
        {
            #ifdef CAN_TIMEOUT_USE_OS
                (void)GetElapsedValue
                (
                    (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                    &CurrentValue[u32Can_CoreId],
                    &ElapsedValue[u32Can_CoreId]
                );
                u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
            #else
                u32TotalElapsedTime++;
            #endif
        }
        if (u32TotalElapsedTime >= s_u32Can_TimeOut[u32Can_CoreId])/* polyspace RTE:OBAI */
        {
            s_u32Can_IsTimeOut[u32Can_CoreId] = 1U;
        }
        else
        {
            s_u32Can_IsTimeOut[u32Can_CoreId] = 0U;
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(boolean,CAN_CODE) MCAN_isInitState \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    if(((pCan_Base->CCCR.R & MCAN_CCCR_INIT_MASK) >> /* polyspace RTE:NIV */
         MCAN_CCCR_INIT_SHIFT) == 0U)
    {
        bCan_Ret = FALSE;
    }
    else
    {
        bCan_Ret = TRUE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_RsetInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    DEV_ASSERT(pCan_Base != NULL_PTR);

    VAR(uint32, AUTOMATIC) u32TotalElapsedTime = 0U;
#ifdef CAN_TIMEOUT_USE_OS
    static VAR(TickType, AUTOMATIC) CurrentValue[CAN_CORE_NUM] = {0U};
    static VAR(TickType, AUTOMATIC) ElapsedValue[CAN_CORE_NUM] = {0U};
#endif
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
    if(((pCan_Base->CCCR.R & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT) == 1U)/* polyspace RTE:NIV,IDP */
    {
        pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_INIT_MASK) | MCAN_CCCR_INIT(0U);
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
        #endif
        SchM_Enter_CAN_EXCLUSIVE_AREA_06();
        while ((((pCan_Base->CCCR.R & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT) == 1U) \
                && ((u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId])))/* polyspace RTE:OBAI */
        {
            #ifdef CAN_TIMEOUT_USE_OS
                (void)GetElapsedValue
                (
                    (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                    &CurrentValue[u32Can_CoreId],
                    &ElapsedValue[u32Can_CoreId]
                );
                u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
            #else
                u32TotalElapsedTime++;
            #endif
        }
        SchM_Exit_CAN_EXCLUSIVE_AREA_06();
        if (u32TotalElapsedTime >= s_u32Can_TimeOut[u32Can_CoreId])/* polyspace RTE:OBAI */
        {
            s_u32Can_IsTimeOut[u32Can_CoreId] = 1U;
        }
        else
        {
            s_u32Can_IsTimeOut[u32Can_CoreId] = 0U;
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetConfigChangeEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) u32TotalElapsedTime = 0U;
#ifdef CAN_TIMEOUT_USE_OS
    static VAR(TickType, AUTOMATIC) CurrentValue[CAN_CORE_NUM] = {0U};
    static VAR(TickType, AUTOMATIC) ElapsedValue[CAN_CORE_NUM] = {0U};
#endif
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
    MCAN_SetInit(pCan_Base);
    #ifdef CAN_TIMEOUT_USE_OS
        (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
    #endif
    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_CCE_MASK) | MCAN_CCCR_CCE(1U);/* polyspace RTE:NIV */
    SchM_Enter_CAN_EXCLUSIVE_AREA_15();
    while (((pCan_Base->CCCR.R & (MCAN_CCCR_INIT_MASK | MCAN_CCCR_CCE_MASK)) \
           != (MCAN_CCCR_INIT_MASK | MCAN_CCCR_CCE_MASK)) && (u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId]))/* polyspace RTE:OBAI */
    {
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetElapsedValue
            (
                (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                &CurrentValue[u32Can_CoreId],
                &ElapsedValue[u32Can_CoreId]
            );
            u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
        #else
            u32TotalElapsedTime++;
        #endif
    }
    SchM_Exit_CAN_EXCLUSIVE_AREA_15();
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_IsFDEnabled \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (((pCan_Base->CCCR.R & MCAN_CCCR_FDOE_MASK) ==  MCAN_CCCR_FDOE_MASK) ? 1U : 0U);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetPayloadSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base, \
    VAR(mode_type_t, AUTOMATIC) eCan_Type \
)
{
    VAR(uint32, AUTOMATIC) payloadSize = 8U;
    VAR(uint32, AUTOMATIC) payloadCode = 0U;

    if (eCan_Type == MCAN_TX_BUFF)
    {
        payloadCode = ((pCan_Base->TXESC.R & MCAN_TXESC_TBDS_MASK) >> MCAN_TXESC_TBDS_SHIFT);/* polyspace RTE:NIV */
    }

    if (eCan_Type == MCAN_RX_BUFF)
    {
        payloadCode = ((pCan_Base->RXESC.R & MCAN_RXESC_RBDS_MASK) >> MCAN_RXESC_RBDS_SHIFT);/* polyspace RTE:NIV */
    }

    if (eCan_Type == MCAN_RX_FIFO0)
    {
        payloadCode = ((pCan_Base->RXESC.R & MCAN_RXESC_F0DS_MASK) >> MCAN_RXESC_F0DS_SHIFT);/* polyspace RTE:NIV */
    }

    if (eCan_Type == MCAN_RX_FIFO1)
    {
        payloadCode = ((pCan_Base->RXESC.R & MCAN_RXESC_F1DS_MASK) >> MCAN_RXESC_F1DS_SHIFT);/* polyspace RTE:NIV */
    }

    switch (payloadCode)
    {
    case (uint32)MCAN_PAYLOAD_SIZE_64:
    {
        payloadSize = 64U;
        break;
    }
    case (uint32)MCAN_PAYLOAD_SIZE_48:
    {
        payloadSize = 48U;
        break;
    }
    case (uint32)MCAN_PAYLOAD_SIZE_32:
    {
        payloadSize = 32U;
        break;
    }
    default:
    {
        payloadSize = ((payloadCode << 2U) + 8U);
        break;
    }
    }
    return (uint8)payloadSize;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_ConvertDLCToDataLength \
( \
    VAR(uint16, AUTOMATIC) u16Can_Dlc \
)
{
    VAR(uint8, AUTOMATIC) u8Can_DlcDatalength = 0U;

    DEV_ASSERT(u16Can_Dlc <= 15U);

    if (u16Can_Dlc <= 8U)
    {
        u8Can_DlcDatalength = (uint8)u16Can_Dlc;
    }
    else
    {
        switch (u16Can_Dlc)
        {
        case 9U:
        {
            u8Can_DlcDatalength = 12U;
            break;
        }
        case 10U:
        {
            u8Can_DlcDatalength = 16U;
            break;
        }
        case 11U:
        {
            u8Can_DlcDatalength = 20U;
            break;
        }
        case 12U:
        {
            u8Can_DlcDatalength = 24U;
            break;
        }
        case 13U:
        {
            u8Can_DlcDatalength = 32U;
            break;
        }
        case 14U:
        {
            u8Can_DlcDatalength = 48U;
            break;
        }
        case 15U:
        {
            u8Can_DlcDatalength = 64U;
            break;
        }
        default:
        {
            u8Can_DlcDatalength = (0U);
            break;
        }
        }
    }

    return u8Can_DlcDatalength;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTestMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Enable \
)
{
    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_TEST_MASK) | MCAN_CCCR_TEST(u8Can_Enable);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetLoopBackMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Enable \
)
{
    pCan_Base->TEST.R = (pCan_Base->TEST.R & ~MCAN_TEST_LBCK_MASK) | MCAN_TEST_LBCK(u8Can_Enable);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_EnableBusMonitorMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Enable \
)
{
    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_MON_MASK) | MCAN_CCCR_MON(u8Can_Enable);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_EnableTestMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(loopback_mode, AUTOMATIC) eCan_Type \
)
{
    if ((pCan_Base->CCCR.R & MCAN_CCCR_TEST_MASK) != MCAN_CCCR_TEST_MASK)/* polyspace RTE:NIV */
    {
        MCAN_SetTestMode(pCan_Base, TRUE);
    }

    if (eCan_Type == MCAN_LOOPBACK_INTERNAL)
    {
        MCAN_SetLoopBackMode(pCan_Base, TRUE);
        MCAN_EnableBusMonitorMode(pCan_Base, TRUE);
    }

    if (eCan_Type == MCAN_LOOPBACK_EXTERNAL)
    {
        MCAN_SetLoopBackMode(pCan_Base, TRUE);
        MCAN_EnableBusMonitorMode(pCan_Base, FALSE);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetNominalTimeSegments \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(bt_config_struct, AUTOMATIC, CAN_APPL_CONST) pCan_TimeSeg \
)
{
    (pCan_Base->NBTP.R) = ((pCan_Base->NBTP.R) & ~(MCAN_NBTP_NTSEG2_MASK /* polyspace RTE:NIV */
            | MCAN_NBTP_NTSEG1_MASK | MCAN_NBTP_NBRP_MASK | MCAN_NBTP_NSJW_MASK));

    (pCan_Base->NBTP.R) = ((pCan_Base->NBTP.R) \
                                   | (MCAN_NBTP_NTSEG1(((uint32)pCan_TimeSeg->phase_seg1 \
                                           + (uint32)pCan_TimeSeg->prop_seg) - 1U) \
                                   | MCAN_NBTP_NTSEG2((uint32)pCan_TimeSeg->phase_seg2 - 1U) \
                                   | MCAN_NBTP_NBRP((uint32)pCan_TimeSeg->brp - 1U) \
                                   | MCAN_NBTP_NSJW((uint32)pCan_TimeSeg->sjw - 1U)));
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetNonIsoOperation \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Format \
)
{
    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_NISO_MASK) | MCAN_CCCR_NISO(BOOLTOUINT(bCan_Format));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetDataTimeSegments \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(bt_config_struct, AUTOMATIC, CAN_APPL_CONST) pCan_TimeSeg \
)
{
    (pCan_Base->DBTP.R) = ((pCan_Base->DBTP.R) & ~(MCAN_DBTP_DTSEG2_MASK | MCAN_DBTP_DTSEG1_MASK /* polyspace RTE:NIV */
                                | MCAN_DBTP_DBRP_MASK | MCAN_DBTP_DSJW_MASK | MCAN_DBTP_TDC_MASK));

    (pCan_Base->DBTP.R) = ((pCan_Base->DBTP.R) \
                                   | (MCAN_DBTP_DTSEG1(((uint32)pCan_TimeSeg->phase_seg1 \
                                           + (uint32)pCan_TimeSeg->prop_seg) - 1U) \
                                   | MCAN_DBTP_DTSEG2((uint32)pCan_TimeSeg->phase_seg2 - 1U) \
                                   | MCAN_DBTP_DBRP((uint32)pCan_TimeSeg->brp - 1U) \
                                   | MCAN_DBTP_DSJW((uint32)pCan_TimeSeg->sjw - 1U) \
                                   | MCAN_DBTP_TDC(BOOLTOUINT(pCan_TimeSeg->tdc))));

    (pCan_Base->TDCR.R) = ((pCan_Base->TDCR.R) & ~MCAN_TDCR_TDCO_MASK) /* polyspace RTE:NIV */
                                   | MCAN_TDCR_TDCO(pCan_TimeSeg->tdc_offset);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetFDDataEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Enable \
)
{

    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_FDOE_MASK) | MCAN_CCCR_FDOE(BOOLTOUINT(bCan_Enable));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetBitRateSwitch \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Enable \
)
{
    pCan_Base->CCCR.R = (pCan_Base->CCCR.R & ~MCAN_CCCR_BRSE_MASK) | MCAN_CCCR_BRSE(BOOLTOUINT(bCan_Enable));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetBitTiming \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(bt_config_canfd_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    MCAN_SetNominalTimeSegments(pCan_Base, &pCan_Config->nominal);

    if(pCan_Config->fd_ena != 0U)
    {
        MCAN_SetDataTimeSegments(pCan_Base, &pCan_Config->data);
        MCAN_SetFDDataEnable(pCan_Base, TRUE);
    }
    else
    {
        MCAN_SetFDDataEnable(pCan_Base, FALSE);
    }

    if(pCan_Config->brs_ena != 0U)
    {
        MCAN_SetBitRateSwitch(pCan_Base, TRUE);
    }
    else
    {
        MCAN_SetBitRateSwitch(pCan_Base, FALSE);
    }

    if(pCan_Config->is_noiso != 0U)
    {
        MCAN_SetNonIsoOperation(pCan_Base, TRUE);
    }
    else
    {
        MCAN_SetNonIsoOperation(pCan_Base, FALSE);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetRejectRemoteStdFrame \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Enable \
)
{
    pCan_Base->GFC.R = (pCan_Base->GFC.R & ~MCAN_GFC_RRFS_MASK) | MCAN_GFC_RRFS(BOOLTOUINT(bCan_Enable));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetRejectRemoteExtFrame \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Enable \
)
{
    pCan_Base->GFC.R = (pCan_Base->GFC.R & ~MCAN_GFC_RRFE_MASK) | MCAN_GFC_RRFE(BOOLTOUINT(bCan_Enable));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetAcceptNonMatchStdFrame \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(GFC_accept_non_matching_frames_enum, AUTOMATIC) eCan_Value \
)
{
    pCan_Base->GFC.R = (pCan_Base->GFC.R & ~MCAN_GFC_ANFS_MASK) | MCAN_GFC_ANFS(eCan_Value);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetAcceptNonMatchExtFrame \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(GFC_accept_non_matching_frames_enum, AUTOMATIC) eCan_Value \
)
{
    pCan_Base->GFC.R = (pCan_Base->GFC.R & ~MCAN_GFC_ANFE_MASK) | MCAN_GFC_ANFE(eCan_Value);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_GlobalFilterConfig \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_global_filter_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    MCAN_SetAcceptNonMatchStdFrame(pCan_Base, pCan_Config->anfs);
    MCAN_SetAcceptNonMatchExtFrame(pCan_Base, pCan_Config->anfe);

    if(pCan_Config->rrfs == TRUE)
    {
        MCAN_SetRejectRemoteStdFrame(pCan_Base, TRUE);
    }
    else if(pCan_Config->rrfs == FALSE)
    {
        MCAN_SetRejectRemoteStdFrame(pCan_Base, FALSE);
    }
    else
    {
        /* do nothing */
    }

    if(pCan_Config->rrfe == TRUE)
    {
        MCAN_SetRejectRemoteExtFrame(pCan_Base, TRUE);
    }
    else if(pCan_Config->rrfe == FALSE)
    {
        MCAN_SetRejectRemoteExtFrame(pCan_Base, FALSE);
    }
    else
    {
        /* do nothing */
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetStdIDFilterAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    pCan_Base->SIDFC.R = (pCan_Base->SIDFC.R & ~MCAN_SIDFC_FLSSA_MASK) /* polyspace RTE:NIV */
                          | (u32Can_Address & MCAN_SIDFC_FLSSA_MASK);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetStdIDFilterSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->SIDFC.R = (pCan_Base->SIDFC.R & ~MCAN_SIDFC_LSS_MASK) | MCAN_SIDFC_LSS(u8Can_Size);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetStdIDFilterSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (uint8)((pCan_Base->SIDFC.R & MCAN_SIDFC_LSS_MASK) >> MCAN_SIDFC_LSS_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetFilterSTDSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) size;

    size = MCAN_GetStdIDFilterSize(pCan_Base);
    value = (pCan_Base->SIDFC.R & MCAN_SIDFC_FLSSA_MASK) + (size << 2U);/* polyspace RTE:NIV */

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetSTD_IdFilter \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(mcan_id_table_t, AUTOMATIC, CAN_APPL_CONST) PCan_IdFilter, \
    VAR(uint8, AUTOMATIC) u8Can_Fl_idx \
)
{
    DEV_ASSERT(PCan_IdFilter != NULL_PTR);

    VAR(uint32, AUTOMATIC) filterAddress;
    VAR(uint32, AUTOMATIC) u32Can_Start_Adr = 0U;

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base = g_mcanBase[eCan_Instance];

    if(eCan_Instance < MCAN_MOD_ID_5)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMA_START_ADR;
    }
    else if(eCan_Instance < MCAN_MOD_ID_9)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMB_START_ADR;
    }
    else
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMC_START_ADR;
    }

    filterAddress = (pCan_Base->SIDFC.R & MCAN_SIDFC_FLSSA_MASK) + ((uint32)u8Can_Fl_idx << 2U);/* polyspace RTE:NIV */
    filterAddress = u32Can_Start_Adr + filterAddress;

    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) stdFlElem = (uint32 *)filterAddress;

    *stdFlElem = (uint32)PCan_IdFilter->filterType << MCAN_STD_FILTER_ID_SFT_SHIFT;/* polyspace RTE:IDP */
    *stdFlElem |= MCAN_STD_FILTER_ID_SFEC_MASK \
               & ((uint32)PCan_IdFilter->filterConfig << MCAN_STD_FILTER_ID_SFEC_SHIFT);
    *stdFlElem |= MCAN_STD_FILTER_ID_SSYNC_MASK \
               & ((uint32)PCan_IdFilter->ssync << MCAN_STD_FILTER_ID_SSYNC_SHIFT);
    *stdFlElem |= MCAN_STD_FILTER_ID_SFID1_MASK \
               & (PCan_IdFilter->id1 << MCAN_STD_FILTER_ID_SFID1_SHIFT);
    *stdFlElem |= MCAN_STD_FILTER_ID_SFID2_MASK & (PCan_IdFilter->id2);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetExtIDFilterAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    pCan_Base->XIDFC.R = (pCan_Base->XIDFC.R & ~MCAN_XIDFC_FLESA_MASK) /* polyspace RTE:NIV */
            | (u32Can_Address & MCAN_XIDFC_FLESA_MASK);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetExtIDFilterSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->XIDFC.R = (pCan_Base->XIDFC.R & ~MCAN_XIDFC_LSE_MASK) | MCAN_XIDFC_LSE(u8Can_Size);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetExtIDFilterSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (uint8)((pCan_Base->XIDFC.R & MCAN_XIDFC_LSE_MASK) >> MCAN_XIDFC_LSE_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetFilterEXTSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) size;

    size = MCAN_GetExtIDFilterSize(pCan_Base);
    value = (pCan_Base->XIDFC.R & MCAN_XIDFC_FLESA_MASK) + (size << 3U);/* polyspace RTE:NIV */

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetEXT_IdFilter \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(mcan_id_table_t, AUTOMATIC, CAN_APPL_CONST) PCan_IdFilter, \
    VAR(uint8, AUTOMATIC) u8Can_Fl_idx \
)
{
    DEV_ASSERT(PCan_IdFilter != NULL_PTR);

    VAR(uint32, AUTOMATIC) filterAddress;
    VAR(uint32, AUTOMATIC) u32Can_Start_Adr = 0U;

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base = g_mcanBase[eCan_Instance];

    if(eCan_Instance < MCAN_MOD_ID_5)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMA_START_ADR;
    }
    else if(eCan_Instance < MCAN_MOD_ID_9)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMB_START_ADR;
    }
    else
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMC_START_ADR;
    }

    filterAddress = (pCan_Base->XIDFC.R & MCAN_XIDFC_FLESA_MASK) + ((uint32)u8Can_Fl_idx << 3U);/* polyspace RTE:NIV */
    filterAddress = u32Can_Start_Adr + filterAddress;

    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) extFlElem0 = (uint32 *)filterAddress;

    filterAddress = filterAddress + 4U;

    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) extFlElem1 = (uint32 *)filterAddress;

    *extFlElem0 =  ((uint32)PCan_IdFilter->filterConfig << MCAN_EXT_FILTER_ID_EFEC_SHIFT);/* polyspace RTE:IDP */
    *extFlElem0 |= MCAN_EXT_FILTER_ID_EFID1_MASK & PCan_IdFilter->id1;
    *extFlElem1 =  ((uint32)PCan_IdFilter->filterType << MCAN_EXT_FILTER_ID_EFT_SHIFT);/* polyspace RTE:IDP */
    *extFlElem1 |= MCAN_EXT_FILTER_ID_ESYNC_MASK \
                & ((uint32)PCan_IdFilter->esync << MCAN_EXT_FILTER_ID_ESYNC_SHIFT);
    *extFlElem1 |= MCAN_EXT_FILTER_ID_EFID2_MASK & PCan_IdFilter->id2;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_RxFilterInit \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(mcan_filter_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config, \
    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) pCan_Address \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    VAR(uint8, AUTOMATIC) idx;
    VAR(uint8, AUTOMATIC) ext_idx = 0U;
    VAR(uint8, AUTOMATIC) std_idx = 0U;
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base = g_mcanBase[eCan_Instance];

    MCAN_SetStdIDFilterAddress(pCan_Base, *pCan_Address);
    MCAN_SetStdIDFilterSize(pCan_Base, pCan_Config->std_filters);
    *pCan_Address = MCAN_GetFilterSTDSpace(pCan_Base);
    MCAN_SetExtIDFilterAddress(pCan_Base, *pCan_Address);
    MCAN_SetExtIDFilterSize(pCan_Base, pCan_Config->ext_filters);
    *pCan_Address = MCAN_GetFilterEXTSpace(pCan_Base);

    for(idx = 0U; idx < (pCan_Config->std_filters + pCan_Config->ext_filters); idx++)
    {
        if(pCan_Config->filterconfigs[idx].isExtendedFrame == TRUE)
        {
            MCAN_SetEXT_IdFilter(eCan_Instance,&pCan_Config->filterconfigs[idx], ext_idx);
            ext_idx++;
        }
        else
        {
            MCAN_SetSTD_IdFilter(eCan_Instance, &pCan_Config->filterconfigs[idx], std_idx);
            std_idx++;
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_FIFOSetSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    if (u8Can_FifoIdx == 0U)
    {
        pCan_Base->RXF0C.R = (pCan_Base->RXF0C.R & ~MCAN_RXF0C_F0S_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF0C_F0S(u8Can_Size);
    }
    else
    {
        pCan_Base->RXF1C.R = (pCan_Base->RXF1C.R & ~MCAN_RXF1C_F1S_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF1C_F1S(u8Can_Size);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_FIFOSetStartAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    if (u8Can_FifoIdx == 0U)
    {
        pCan_Base->RXF0C.R = (pCan_Base->RXF0C.R & ~MCAN_RXF0C_F0SA_MASK) /* polyspace RTE:NIV */
                | (u32Can_Address&MCAN_RXF0C_F0SA_MASK);
    }
    else
    {
        pCan_Base->RXF1C.R = (pCan_Base->RXF1C.R & ~MCAN_RXF1C_F1SA_MASK) /* polyspace RTE:NIV */
                | (u32Can_Address&MCAN_RXF1C_F1SA_MASK);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_FIFOSetOpMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx, \
    VAR(fifo_op_mode_t, AUTOMATIC) eCan_Mode \
)
{
    if (u8Can_FifoIdx == 0U)
    {
        pCan_Base->RXF0C.R = (pCan_Base->RXF0C.R & ~MCAN_RXF0C_F0OM_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF0C_F0OM(eCan_Mode);
    }
    else
    {
        pCan_Base->RXF1C.R = (pCan_Base->RXF1C.R & ~MCAN_RXF1C_F1OM_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF1C_F1OM(eCan_Mode);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_FIFOSetWaterMark \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx, \
    VAR(uint8, AUTOMATIC) u8Can_Level \
)
{
    if (u8Can_FifoIdx == 0U)
    {
        pCan_Base->RXF0C.R = (pCan_Base->RXF0C.R & ~MCAN_RXF0C_F0WM_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF0C_F0WM(u8Can_Level);
    }
    else
    {
        pCan_Base->RXF1C.R = (pCan_Base->RXF1C.R & ~MCAN_RXF1C_F1WM_MASK) /* polyspace RTE:NIV */
                | MCAN_RXF1C_F1WM(u8Can_Level);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_FIFOSetPayloadSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx, \
    VAR(mcan_fd_payload_size_t, AUTOMATIC) eCan_Size \
)
{
    if (u8Can_FifoIdx == 0U)
    {
        pCan_Base->RXESC.R = (pCan_Base->RXESC.R & ~MCAN_RXESC_F0DS_MASK) /* polyspace RTE:NIV */
                | MCAN_RXESC_F0DS(eCan_Size);
    }
    else
    {
        pCan_Base->RXESC.R = (pCan_Base->RXESC.R & ~MCAN_RXESC_F1DS_MASK) /* polyspace RTE:NIV */
                | MCAN_RXESC_F1DS(eCan_Size);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_FIFOGetSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx \
)
{
    VAR(uint8, AUTOMATIC) value = 0U;

    if (u8Can_FifoIdx == 0U)
    {
        value = ((uint8)((pCan_Base->RXF0C.R & MCAN_RXF0C_F0S_MASK) >> MCAN_RXF0C_F0S_SHIFT));/* polyspace RTE:NIV */
    }
    else
    {
        value = ((uint8)((pCan_Base->RXF1C.R & MCAN_RXF1C_F1S_MASK) >> MCAN_RXF1C_F1S_SHIFT));/* polyspace RTE:NIV */
    }

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetRxFIFOSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_FifoIdx \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) arbitration_field_size = 8U;
    VAR(uint32, AUTOMATIC) size =  MCAN_FIFOGetSize(pCan_Base, u8Can_FifoIdx);

    if (u8Can_FifoIdx == 0U)
    {
        VAR(uint32, AUTOMATIC) paysize = MCAN_GetPayloadSize(pCan_Base, MCAN_RX_FIFO0);
        value = (pCan_Base->RXF0C.R & MCAN_RXF0C_F0SA_MASK) /* polyspace RTE:NIV */
                 + (size *(paysize+arbitration_field_size));
    }
    else if (u8Can_FifoIdx == 1U)
    {
        VAR(uint32, AUTOMATIC) paysize = MCAN_GetPayloadSize(pCan_Base, MCAN_RX_FIFO1);
        value = (pCan_Base->RXF1C.R & MCAN_RXF1C_F1SA_MASK) /* polyspace RTE:NIV */
                 + (size *(paysize+arbitration_field_size));
    }
    else
    {
        /* do nothing */
    }
    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_RxFifoInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_fifo_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config, \
    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) pCan_Address \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    MCAN_FIFOSetSize(pCan_Base, 0U, 0U);
    MCAN_FIFOSetStartAddress(pCan_Base, 0U, 0U);
    MCAN_FIFOSetSize(pCan_Base, 1U, 0U);
    MCAN_FIFOSetStartAddress(pCan_Base, 1U, 0U);

    if ((pCan_Config->rx_fifo_needed == MCAN_RXFIFO_0_ENABLE) \
        || (pCan_Config->rx_fifo_needed == MCAN_RXFIFO_0_1_ENABLE))
    {
        MCAN_FIFOSetOpMode(pCan_Base, 0U, pCan_Config->modeFIFO);
        MCAN_FIFOSetWaterMark(pCan_Base, 0U, pCan_Config->fifo_watermark);
        MCAN_FIFOSetSize(pCan_Base, 0U, pCan_Config->fifo_size_elems);
        MCAN_FIFOSetPayloadSize(pCan_Base, 0U, pCan_Config->payload);
        MCAN_FIFOSetStartAddress(pCan_Base, 0U, *pCan_Address);
        *pCan_Address = MCAN_GetRxFIFOSpace(pCan_Base, 0U);
    }
    if ((pCan_Config->rx_fifo_needed == MCAN_RXFIFO_1_ENABLE) \
        || (pCan_Config->rx_fifo_needed == MCAN_RXFIFO_0_1_ENABLE))
    {
        MCAN_FIFOSetOpMode(pCan_Base, 1U, pCan_Config->modeFIFO);
        MCAN_FIFOSetWaterMark(pCan_Base, 1U, pCan_Config->fifo_watermark);
        MCAN_FIFOSetSize(pCan_Base, 1U, pCan_Config->fifo_size_elems);
        MCAN_FIFOSetPayloadSize(pCan_Base, 1U, pCan_Config->payload);
        MCAN_FIFOSetStartAddress(pCan_Base, 1U, *pCan_Address);
        *pCan_Address = MCAN_GetRxFIFOSpace(pCan_Base, 1U);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetRxBuffAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    pCan_Base->RXBC.R = (pCan_Base->RXBC.R & ~MCAN_RXBC_RBSA_MASK) /* polyspace RTE:NIV */
            | (u32Can_Address & MCAN_RXBC_RBSA_MASK);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetRxElementdSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(mcan_fd_payload_size_t, AUTOMATIC) eCan_Size \
)
{
    pCan_Base->RXESC.R = (pCan_Base->RXESC.R & ~MCAN_RXESC_RBDS_MASK) /* polyspace RTE:NIV */
            | MCAN_RXESC_RBDS((uint32)eCan_Size);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetRxMBSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Rx_buffer_size_elems \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) size = u8Can_Rx_buffer_size_elems;
    VAR(uint32, AUTOMATIC) arbitration_field_size = 8U;
    VAR(uint32, AUTOMATIC) paysize = MCAN_GetPayloadSize(pCan_Base, MCAN_RX_BUFF);

    value = (pCan_Base->RXBC.R & MCAN_RXBC_RBSA_MASK) + (size *(paysize+arbitration_field_size));/* polyspace RTE:NIV */

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_RxDedicatedBuffersInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_dedicated_buffers_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config, \
    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) pCan_Address \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    MCAN_SetRxBuffAddress(pCan_Base, *pCan_Address);
    MCAN_SetRxElementdSize(pCan_Base, pCan_Config->payload);

    *pCan_Address = MCAN_GetRxMBSpace(pCan_Base, pCan_Config->rx_buffer_size_elems);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxEventFifoSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->TXEFC.R = (pCan_Base->TXEFC.R & ~MCAN_TXEFC_EFS_MASK) | MCAN_TXEFC_EFS(u8Can_Size);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxEventWaterMark \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->TXEFC.R = (pCan_Base->TXEFC.R & ~MCAN_TXEFC_EFWM_MASK) /* polyspace RTE:NIV */
                          | MCAN_TXEFC_EFWM(u8Can_Size);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxEventFifoAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    pCan_Base->TXEFC.R = (pCan_Base->TXEFC.R & ~MCAN_TXEFC_EFSA_MASK) /* polyspace RTE:NIV */
                          | (u32Can_Address & MCAN_TXEFC_EFSA_MASK);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetTxEventFifoSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (uint8)((pCan_Base->TXEFC.R & MCAN_TXEFC_EFS_MASK) >> MCAN_TXEFC_EFS_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetTxEventFifoSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) size = MCAN_GetTxEventFifoSize(pCan_Base);
    VAR(uint32, AUTOMATIC) arbitration_field_size = 8U;

    value = (pCan_Base->TXEFC.R & MCAN_TXEFC_EFSA_MASK) + (size*(arbitration_field_size));/* polyspace RTE:NIV */

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_TxEventFifoInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_tx_event_fifo_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config, \
    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) pCan_Address \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    MCAN_SetTxEventFifoAddress(pCan_Base, *pCan_Address);
    MCAN_SetTxEventWaterMark(pCan_Base, pCan_Config->fifo_watermark);
    MCAN_SetTxEventFifoSize(pCan_Base, pCan_Config->fifo_size_elems);
    *pCan_Address = MCAN_GetTxEventFifoSpace(pCan_Base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxBuffAddress \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Address \
)
{
    pCan_Base->TXBC.R = (pCan_Base->TXBC.R & ~MCAN_TXBC_TBSA_MASK) | (u32Can_Address & MCAN_TXBC_TBSA_MASK);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxBuffSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->TXBC.R = (pCan_Base->TXBC.R & ~MCAN_TXBC_NDTB_MASK) | MCAN_TXBC_NDTB(u8Can_Size);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetTxFifoQueueSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint8, AUTOMATIC) u8Can_Size \
)
{
    pCan_Base->TXBC.R = (pCan_Base->TXBC.R & ~MCAN_TXBC_TFQS_MASK) | MCAN_TXBC_TFQS(u8Can_Size);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE)  MCAN_SetTxElementdSize \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(mcan_fd_payload_size_t, AUTOMATIC) eCan_Size \
)
{
    pCan_Base->TXESC.R = (pCan_Base->TXESC.R & ~MCAN_TXESC_TBDS_MASK) /* polyspace RTE:NIV */
            | MCAN_TXESC_TBDS((uint32)eCan_Size);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE)  MCAN_SetTxFifoEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(boolean, AUTOMATIC) bCan_Enable \
)
{
    pCan_Base->TXBC.R = (pCan_Base->TXBC.R & ~MCAN_TXBC_TFQM_MASK) | MCAN_TXBC_TFQM(BOOLTOUINT(bCan_Enable));/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetTxBuffSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (uint8)((pCan_Base->TXBC.R & MCAN_TXBC_NDTB_MASK) >> MCAN_TXBC_NDTB_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint8,CAN_CODE) MCAN_GetTxFifoSize \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return (uint8)((pCan_Base->TXBC.R & MCAN_TXBC_TFQS_MASK) >> MCAN_TXBC_TFQS_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetTxMBSpace \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    VAR(uint32, AUTOMATIC) value = 0U;
    VAR(uint32, AUTOMATIC) size = (uint32)MCAN_GetTxBuffSize(pCan_Base) \
            + (uint32)MCAN_GetTxFifoSize(pCan_Base);
    VAR(uint32, AUTOMATIC) arbitration_field_size = 8U;
    VAR(uint32, AUTOMATIC) paysize = MCAN_GetPayloadSize(pCan_Base, MCAN_TX_BUFF);

    value = (pCan_Base->TXBC.R & MCAN_TXBC_TBSA_MASK) + (size *(paysize+arbitration_field_size));/* polyspace RTE:NIV */

    return value;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_TxBufferInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_tx_buffer_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config, \
    P2VAR(uint32, AUTOMATIC,CAN_APPL_DATA) pCan_Address \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    MCAN_SetTxBuffAddress(pCan_Base, *pCan_Address);
    MCAN_SetTxBuffSize(pCan_Base, pCan_Config->ded_buffers_number);
    MCAN_SetTxFifoQueueSize(pCan_Base, pCan_Config->fifo_queue_size);
    MCAN_SetTxElementdSize(pCan_Base, pCan_Config->payload);
    *pCan_Address = MCAN_GetTxMBSpace(pCan_Base);
    if(pCan_Config->FIFO_true_QUEUE_false  != 0U)
    {
        MCAN_SetTxFifoEnable(pCan_Base, FALSE);
    }
    else
    {
        MCAN_SetTxFifoEnable(pCan_Base, TRUE);
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_ClearNotEnableInterStatus \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    uint32 ire_enabled = (uint32)pCan_Base->IE.R;/* polyspace RTE:NIV */
    pCan_Base->IR.R = ~ire_enabled;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_InterEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Ir_enable \
)
{
    pCan_Base->IE.R = ((pCan_Base->IE.R & ~INTERRUPT_ALL_SIGNALS) /* polyspace RTE:NIV */
            | (u32Can_Ir_enable & INTERRUPT_ALL_SIGNALS));
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_InterDisableAllSignals \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base \
)
{
    SchM_Enter_CAN_EXCLUSIVE_AREA_13();
    pCan_Base->IE.R = (pCan_Base->IE.R & ~INTERRUPT_ALL_SIGNALS);/* polyspace RTE:NIV */
    SchM_Exit_CAN_EXCLUSIVE_AREA_13();
    pCan_Base->TXBTIE.R = 0U;
    pCan_Base->TXBCIE.R = 0U;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_InterLineEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Ile_enable \
)
{
    pCan_Base->ILE.R = ((pCan_Base->ILE.R & ~(MCAN_ILE_EINT0_MASK | MCAN_ILE_EINT1_MASK)) /* polyspace RTE:NIV */
                   | (u32Can_Ile_enable&(MCAN_ILE_EINT0_MASK | MCAN_ILE_EINT1_MASK)));
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_InterLineSelect \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Ir_line_select \
)
{
    pCan_Base->ILS.R = ((pCan_Base->ILS.R & ~INTERRUPT_ALL_SIGNALS) /* polyspace RTE:NIV */
                   | (u32Can_Ir_line_select & INTERRUPT_ALL_SIGNALS));
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_TxBufferTranInterEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Tx_buffer_tran_inter \
)
{
    pCan_Base->TXBTIE.R = ((pCan_Base->TXBTIE.R & ~0xFFFFFFFFU) | u32Can_Tx_buffer_tran_inter);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_TxBufferCancelFinishedInterEnable \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(uint32, AUTOMATIC) u32Can_Tx_buffer_cnacel_inter \
)
{
    pCan_Base->TXBCIE.R = ((pCan_Base->TXBCIE.R & ~0xFFFFFFFFU) | u32Can_Tx_buffer_cnacel_inter);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_InterruptInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_inter_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    if(pCan_Config == NULL_PTR)
    {
        return;
    }

    DEV_ASSERT((pCan_Config->ir_line0_select & pCan_Config->ir_line1_select) == 0U);
    DEV_ASSERT(((pCan_Config->ir_line0_select + pCan_Config->ir_line1_select) \
               | INTERRUPT_ALL_SIGNALS) == INTERRUPT_ALL_SIGNALS );

    VAR(uint32, AUTOMATIC) ir_enable;
    VAR(uint32, AUTOMATIC) ir_line_enable;

    ir_enable = pCan_Config->ir_line0_select | pCan_Config->ir_line1_select;

    MCAN_ClearNotEnableInterStatus(pCan_Base);
    MCAN_InterEnable(pCan_Base, ir_enable);

    ir_line_enable = ILE_DISABLE_INTERRUPT_LINES;

    if(pCan_Config->ir_line0_select != 0U)
    {
        ir_line_enable += ILE_ENABLE_INTERRUPT_LINE_0;
    }
    if(pCan_Config->ir_line1_select != 0U)
    {
        ir_line_enable += ILE_ENABLE_INTERRUPT_LINE_1;
    }

    MCAN_InterLineEnable(pCan_Base, ir_line_enable);

    MCAN_InterLineSelect(pCan_Base, pCan_Config->ir_line1_select);

    MCAN_TxBufferTranInterEnable(pCan_Base, pCan_Config->tx_buffer_tran_ir_enable);

    MCAN_TxBufferCancelFinishedInterEnable(pCan_Base, \
            pCan_Config->tx_buffer_cancel_fin_ir_enable);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_SetOperationMode \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    VAR(mcan_operation_modes_t, AUTOMATIC) eCan_Mode \
)
{
    if (eCan_Mode == MCAN_LOOPBACK_MODE)
    {
        MCAN_EnableTestMode(pCan_Base, MCAN_LOOPBACK_INTERNAL);
    }
    else if (eCan_Mode == MCAN_NORMAL_MODE)
    {
        MCAN_SetLoopBackMode(pCan_Base, FALSE);
        MCAN_EnableBusMonitorMode(pCan_Base, FALSE);
    }
    else if (eCan_Mode == MCAN_LISTEN_ONLY_MODE)
    {
        MCAN_SetLoopBackMode(pCan_Base, FALSE);
        MCAN_EnableBusMonitorMode(pCan_Base, TRUE);
    }
    else
    {
        /* do nothing */
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void,CAN_CODE) MCAN_TimestampcounterAndTimeoutcounterInit \
( \
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base, \
    P2CONST(mcan_timestamp_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    if(pCan_Config == NULL)
    {
        return;
    }

    pCan_Base->TSCC.R = (pCan_Base->TSCC.R & ~MCAN_TSCC_TSS_MASK) | MCAN_TSCC_TSS(pCan_Config->ts_select);/* polyspace RTE:NIV */
    pCan_Base->TSCC.R = (pCan_Base->TSCC.R & ~MCAN_TSCC_TCP_MASK) \
                    | MCAN_TSCC_TCP(pCan_Config->ts_counter_prescaler - 1U);

    pCan_Base->TOCC.R = (pCan_Base->TOCC.R & ~MCAN_TOCC_TOS_MASK) | MCAN_TOCC_TOS(pCan_Config->to_select);/* polyspace RTE:NIV */
    pCan_Base->TOCC.R = (pCan_Base->TOCC.R & ~MCAN_TOCC_TOP_MASK) | MCAN_TOCC_TOP(pCan_Config->to_period);

    if(pCan_Config->to_counter_enable == TRUE)
    {
        pCan_Base->TOCC.R = (pCan_Base->TOCC.R & ~MCAN_TOCC_ETOC_MASK) | MCAN_TOCC_ETOC(1U);
    }
    else if(pCan_Config->to_counter_enable == FALSE)
    {
        pCan_Base->TOCC.R = (pCan_Base->TOCC.R & ~MCAN_TOCC_ETOC_MASK) | MCAN_TOCC_ETOC(0U);
    }
    else
    {
        /* do nothing */
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetBoState \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return pCan_Base->PSR.R & MCAN_PSR_BO_MASK;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(uint32,CAN_CODE) MCAN_GetEpState \
( \
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) pCan_Base \
)
{
    return pCan_Base->PSR.R & MCAN_PSR_EP_MASK;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(status_t, CAN_CODE) Can_LLD_NecessarySpace \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(CANConfig, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(pCan_Config != NULL_PTR);
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];

    VAR(uint32, AUTOMATIC) numofwords = 0U;
    VAR(uint32, AUTOMATIC) WordsOfFilter = 0U;
    VAR(uint32, AUTOMATIC) WordsOfRxfifo = 0U;
    VAR(uint32, AUTOMATIC) WordsOfTxevent = 0U;
    VAR(uint32, AUTOMATIC) WordsOfTxbufferAndFifo = 0U;
    VAR(uint32, AUTOMATIC) WordsOfRxbuffer = 0U;
    VAR(status_t, AUTOMATIC) eCan_StatusRet = STATUS_ERROR;

    if(pCan_Config->filterconfig != NULL)
    {
        WordsOfFilter = (uint32)pCan_Config->filterconfig->std_filters \
                         + ((uint32)pCan_Config->filterconfig->ext_filters << 1U);
    }

    if(pCan_Config->rxfifoconfig != NULL)
    {
        if ((pCan_Config->rxfifoconfig->rx_fifo_needed == MCAN_RXFIFO_0_ENABLE) \
            || (pCan_Config->rxfifoconfig->rx_fifo_needed== MCAN_RXFIFO_0_1_ENABLE))
        {
            WordsOfRxfifo = (2U + ((uint32)MCAN_GetPayloadSize(base, MCAN_RX_FIFO0) >> 2U)) \
                             *pCan_Config->rxfifoconfig->fifo_size_elems;
        }
        if ((pCan_Config->rxfifoconfig->rx_fifo_needed == MCAN_RXFIFO_1_ENABLE) \
            || (pCan_Config->rxfifoconfig->rx_fifo_needed == MCAN_RXFIFO_0_1_ENABLE))
        {
            WordsOfRxfifo += (2U + ((uint32)MCAN_GetPayloadSize(base, MCAN_RX_FIFO1) >> 2U)) \
                              *(uint32)pCan_Config->rxfifoconfig->fifo_size_elems;
        }
    }

    if(pCan_Config->txeventconfig != NULL)
    {
        WordsOfTxevent = ((uint32)pCan_Config->txeventconfig->fifo_size_elems << 1U);
    }

    if(pCan_Config->txbufferconfig != NULL)
    {
        WordsOfTxbufferAndFifo = ((uint32)pCan_Config->txbufferconfig->ded_buffers_number \
                                  + (uint32)pCan_Config->txbufferconfig->fifo_queue_size) \
                                  *(2U + ((uint32)MCAN_GetPayloadSize(base, MCAN_TX_BUFF) >> 2U));
    }

    if(pCan_Config->rxbufferconfig != NULL)
    {
        WordsOfRxbuffer = (2U + ((uint32)MCAN_GetPayloadSize(base, MCAN_RX_BUFF) >> 2U)) \
                           *pCan_Config->rxbufferconfig->rx_buffer_size_elems;
    }

    numofwords = WordsOfFilter + WordsOfRxfifo + WordsOfTxevent \
                 + WordsOfTxbufferAndFifo + WordsOfRxbuffer;

    if(numofwords > pCan_Config->data->McanCtrl[eCan_Instance].mram_size_words)
    {
        eCan_StatusRet = STATUS_ERROR;
    }
    else
    {
        eCan_StatusRet = STATUS_SUCCESS;
    }
    return eCan_StatusRet;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
/* PRQA S 2755 EOF */
FUNC(status_t, CAN_CODE) Can_LLD_Init \
( \
    VAR(uint8, AUTOMATIC) u8Can_ControllerId, \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(CANConfig, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(pCan_Config != NULL_PTR);

    VAR(status_t, AUTOMATIC) status;
    VAR(uint32, AUTOMATIC) idx;
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) pCan_Base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
    VAR(uint32, AUTOMATIC) address = 0U;
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
    *(uint32*)0xffff804cU = 0U; // enable MCAN

    status = MCAN_MsgRamPartitioningCheck(pCan_Config->data);
    if (status == STATUS_SUCCESS)
    {
        if(eCan_Instance < MCAN_MOD_ID_5)
        {
            SchM_Enter_CAN_EXCLUSIVE_AREA_07();
            for (idx = (pCan_Config->data->McanCtrl[eCan_Instance].BaseWord); \
                 idx < ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) \
                 + pCan_Config->data->McanCtrl[eCan_Instance].mram_size_words); idx++)
            {
                MCAN_RAMA->RAM[idx] = 0U;/* polyspace RTE:IDP,OBAI */
            }
            SchM_Exit_CAN_EXCLUSIVE_AREA_07();
            address = ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) << 2U);
        }
        else if (eCan_Instance < MCAN_MOD_ID_9)
        {
            SchM_Enter_CAN_EXCLUSIVE_AREA_08();
            for (idx = (pCan_Config->data->McanCtrl[eCan_Instance].BaseWord); \
                 idx < ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) \
                 + pCan_Config->data->McanCtrl[eCan_Instance].mram_size_words); idx++)
            {
                MCAN_RAMB->RAM[idx] = 0U;/* polyspace RTE:IDP,OBAI */
            }
            SchM_Exit_CAN_EXCLUSIVE_AREA_08();
            address = ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) << 2U);
        }
        else
        {
            SchM_Enter_CAN_EXCLUSIVE_AREA_18();
            for (idx = (pCan_Config->data->McanCtrl[eCan_Instance].BaseWord); \
                 idx < ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) \
                 + pCan_Config->data->McanCtrl[eCan_Instance].mram_size_words); idx++)
            {
                MCAN_RAMC->RAM[idx] = 0U;/* polyspace RTE:IDP,OBAI */
            }
            SchM_Exit_CAN_EXCLUSIVE_AREA_18();
            address = ((pCan_Config->data->McanCtrl[eCan_Instance].BaseWord) << 2U);
        }
    }

    if (status == STATUS_SUCCESS)
    {
        MCAN_ClearAllReceivedFlags(pCan_Base);
        MCAN_SetConfigChangeEnable(pCan_Base);
        if (1U == s_u32Can_IsTimeOut[u32Can_CoreId])/* polyspace RTE:OBAI */
        {
            status = STATUS_TIMEOUT;
        }
    }

    if (STATUS_SUCCESS == status)
    {
        for (idx = 0; idx < pCan_Config->baudRateConfigCount; idx++)
        {
            if (g_u16Can_CurBaudRateId[u8Can_ControllerId] == pCan_Config->timingconfig[idx].baudRateConfigId)
            {
                MCAN_SetBitTiming(pCan_Base, &pCan_Config->timingconfig[idx]);
                break;
            }
        }
        MCAN_GlobalFilterConfig(pCan_Base, pCan_Config->globalfilterconfig);
        MCAN_RxFilterInit(eCan_Instance, pCan_Config->filterconfig, &address);
        MCAN_RxFifoInit(pCan_Base, pCan_Config->rxfifoconfig, &address);
        MCAN_TxEventFifoInit(pCan_Base, pCan_Config->txeventconfig, &address);
        MCAN_TxBufferInit(pCan_Base, pCan_Config->txbufferconfig, &address);
        MCAN_RxDedicatedBuffersInit(pCan_Base, pCan_Config->rxbufferconfig, &address);
        status = Can_LLD_NecessarySpace(eCan_Instance, pCan_Config);
    }

    if (STATUS_SUCCESS == status)
    {
        MCAN_SetOperationMode(pCan_Base, pCan_Config->mcanMode);

        MCAN_TimestampcounterAndTimeoutcounterInit(pCan_Base, pCan_Config->stampconfig);

        if (1U == s_u32Can_IsTimeOut[u32Can_CoreId])
        {
            status = STATUS_TIMEOUT;
        }
    }

    return status;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_Deint(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    MCAN_SetConfigChangeEnable(base);

    MCAN_InterDisableAllSignals(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxIsEnableTranPause \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Enable \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    MCAN_SetConfigChangeEnable(base);

    base->CCCR.R = (base->CCCR.R & ~MCAN_CCCR_TXP_MASK) | MCAN_CCCR_TXP(u8Can_Enable);/* polyspace RTE:NIV */

    while (((base->CCCR.R & MCAN_CCCR_TXP_MASK) >> MCAN_CCCR_TXP_SHIFT) != u8Can_Enable)
    {

    }

    MCAN_RsetInit(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxIsEnableDar \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Enable \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    MCAN_SetConfigChangeEnable(base);

    base->CCCR.R = (base->CCCR.R & ~MCAN_CCCR_DAR_MASK) | MCAN_CCCR_DAR(u8Can_Enable);/* polyspace RTE:NIV */

    while (((base->CCCR.R & MCAN_CCCR_DAR_MASK) >> MCAN_CCCR_DAR_SHIFT) != u8Can_Enable)
    {

    }
    MCAN_RsetInit(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_EnterSleepStatus(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) u32TotalElapsedTime = 0U;
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
#ifdef CAN_TIMEOUT_USE_OS
    static VAR(TickType, AUTOMATIC) CurrentValue[CAN_CORE_NUM] = {0U};
    static VAR(TickType, AUTOMATIC) ElapsedValue[CAN_CORE_NUM] = {0U};
#endif
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/

    base->CCCR.R = (base->CCCR.R & ~MCAN_CCCR_CSR_MASK) | MCAN_CCCR_CSR(1U);/* polyspace RTE:NIV */
    #ifdef CAN_TIMEOUT_USE_OS
        (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
    #endif
    while ((((base->CCCR.R & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT) == 0U)
            && (u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId]))/* polyspace RTE:OBAI */
    {
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetElapsedValue
            (
                (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                &CurrentValue[u32Can_CoreId],
                &ElapsedValue[u32Can_CoreId]
            );
            u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
        #else
            u32TotalElapsedTime++;
        #endif
    }
    u32TotalElapsedTime = 0U;
    #ifdef CAN_TIMEOUT_USE_OS
        (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
    #endif
    while ((((base->CCCR.R & MCAN_CCCR_CSA_MASK) >> MCAN_CCCR_CSA_SHIFT) == 0U)
            && (u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId]))/* polyspace RTE:OBAI */
    {
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetElapsedValue
            (
                (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                &CurrentValue[u32Can_CoreId],
                &ElapsedValue[u32Can_CoreId]
            );
            u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
        #else
            u32TotalElapsedTime++;
        #endif
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_WakeUp(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) u32TotalElapsedTime = 0U;
#ifdef CAN_TIMEOUT_USE_OS
    static VAR(TickType, AUTOMATIC) CurrentValue[CAN_CORE_NUM] = {0U};
    static VAR(TickType, AUTOMATIC) ElapsedValue[CAN_CORE_NUM] = {0U};
#endif
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    base->CCCR.R = (base->CCCR.R & ~MCAN_CCCR_CSR_MASK) | MCAN_CCCR_CSR(0U);/* polyspace RTE:NIV */
    #ifdef CAN_TIMEOUT_USE_OS
        (void)GetCounterValue((CounterType)CAN_TIMEOUT_COUNTER_NAME, &CurrentValue[u32Can_CoreId]);
    #endif
    while ((((base->CCCR.R & MCAN_CCCR_CSA_MASK) >> MCAN_CCCR_CSA_SHIFT) == 1U)
            && (u32TotalElapsedTime < s_u32Can_TimeOut[u32Can_CoreId]))/* polyspace RTE:OBAI */
    {
        #ifdef CAN_TIMEOUT_USE_OS
            (void)GetElapsedValue
            (
                (CounterType)CAN_TIMEOUT_COUNTER_NAME,
                &CurrentValue[u32Can_CoreId],
                &ElapsedValue[u32Can_CoreId]
            );
            u32TotalElapsedTime += (uint32)ElapsedValue[u32Can_CoreId];
        #else
            u32TotalElapsedTime++;
        #endif
    }

    MCAN_RsetInit(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_SetExtendIDMask \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Mask \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    MCAN_SetConfigChangeEnable(base);

    base->XIDAM.R = (base->XIDAM.R & ~MCAN_XIDAM_EIDM_MASK) | MCAN_XIDAM_EIDM(u32Can_Mask);/* polyspace RTE:NIV */

    while (((base->XIDAM.R & MCAN_XIDAM_EIDM_MASK) >> MCAN_XIDAM_EIDM_SHIFT) != u32Can_Mask)
    {

    }

    MCAN_RsetInit(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(boolean, CAN_CODE) Can_LLD_TxIsReqPending \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];

    if(u8Can_Tx_buffer_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u8Can_Tx_buffer_index);
    }

    if( ((base->TXBRP.R) & mask) == 0U)/* polyspace RTE:NIV */
    {
        bCan_Ret = FALSE;
    }
    else
    {
        bCan_Ret = TRUE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_TxWriteMsgToBuffer \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buff_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(pCan_Tx_msg_ptr != NULL);
    DEV_ASSERT(u8Can_Tx_buff_index < FEATURE_MCAN_TX_MB_NUM);

    VAR(uint32, AUTOMATIC) ram_write_addr = 0U;
    VAR(uint8, AUTOMATIC)  payload_size = 0U;
    VAR(uint32, AUTOMATIC) ram_word = 0U;
    VAR(uint32, AUTOMATIC) payload_bytes_to_write = 0U;
    VAR(uint32, AUTOMATIC) curr_payload_word = 0U;
    VAR(uint32, AUTOMATIC) u32Can_Start_Adr = 0U;

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];

    if(eCan_Instance < MCAN_MOD_ID_5)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMA_START_ADR;
    }
    else if(eCan_Instance < MCAN_MOD_ID_9)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMB_START_ADR;
    }
    else
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMC_START_ADR;
    }

    payload_size = MCAN_GetPayloadSize(base, MCAN_TX_BUFF);
    ram_write_addr =((base->TXBC.R & MCAN_TXBC_TBSA_MASK) + u32Can_Start_Adr) /* polyspace RTE:NIV */
                     + ((uint32)u8Can_Tx_buff_index *((uint32)payload_size + 8U));

    if (pCan_Tx_msg_ptr->idtype == STANDARD_ID)
    {
        ram_word = pCan_Tx_msg_ptr->id << MCAN_TX_BUFFER_STD_ID_SHIFT;
    }
    else
    {
        ram_word = pCan_Tx_msg_ptr->id + MCAN_TX_BUFFER_XTD_MASK;
    }

    if (pCan_Tx_msg_ptr->remote == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_RTR_MASK;
    }

    if (pCan_Tx_msg_ptr->esi == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_ESI_MASK;
    }

    *(uint32 *)(ram_write_addr) = ram_word;/* polyspace RTE:IDP */

    ram_word = ((uint32)pCan_Tx_msg_ptr->dlc << MCAN_TX_BUFFER_DLC_SHIFT) & MCAN_TX_BUFFER_DLC_MASK;
    if (pCan_Tx_msg_ptr->fdf == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_FDF_MASK;
    }

    if (pCan_Tx_msg_ptr->brs == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_BRS_MASK;
    }

    if (pCan_Tx_msg_ptr->efc == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_EFC_MASK;
        ram_word = ram_word + ((uint32)pCan_Tx_msg_ptr->mm << MCAN_TX_BUFFER_MM_SHIFT);
    }

    if (pCan_Tx_msg_ptr->tx_tsce == TRUE)
    {
        ram_word = ram_word + MCAN_TX_BUFFER_TSCE_MASK;
    }
    *(uint32 *)(ram_write_addr + 4U) = ram_word;/* polyspace RTE:IDP */

    payload_bytes_to_write = (uint32)MCAN_ConvertDLCToDataLength(pCan_Tx_msg_ptr->dlc);
    
    while(payload_bytes_to_write > 0U)
    {
        ram_word = (((uint32)pCan_Tx_msg_ptr->data[(curr_payload_word<<2U)]) \
                    +((uint32)pCan_Tx_msg_ptr->data[(curr_payload_word<<2U)+1U] <<  8U) \
                    +((uint32)pCan_Tx_msg_ptr->data[(curr_payload_word<<2U)+2U] << 16U) \
                    +((uint32)pCan_Tx_msg_ptr->data[(curr_payload_word<<2U)+3U] << 24U));
        SchM_Enter_CAN_EXCLUSIVE_AREA_09();
        *(uint32 *)(ram_write_addr + 8U + (curr_payload_word *4U)) = ram_word;/* polyspace RTE:IDP */
        SchM_Exit_CAN_EXCLUSIVE_AREA_09();
        curr_payload_word++;

        if (payload_bytes_to_write >= 4U)
        {
            payload_bytes_to_write = (payload_bytes_to_write - 4U);
        }
        else
        {
            payload_bytes_to_write = 0U;
        }
    }
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_TxMsgSingleRequest \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];

    if(u8Can_Tx_buffer_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u8Can_Tx_buffer_index);
    }

    base->TXBAR.R = ((base->TXBAR.R) & ~MCAN_TXBAR_AR_MASK) | mask;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxMsgScanSend \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Mask \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    base->TXBAR.R = ((base->TXBAR.R) & ~MCAN_TXBAR_AR_MASK) | u32Can_Mask;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxSendDedicatedMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(pCan_Tx_msg_ptr != NULL);
    DEV_ASSERT(u8Can_Tx_buffer_index < FEATURE_MCAN_TX_MB_NUM);
    DEV_ASSERT(pCan_Tx_msg_ptr->direction == TX_DIR);

    VAR(uint32, AUTOMATIC) msgs_sent = 0U;
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
    VAR(uint32, AUTOMATIC) retry_cnt = 0U;

    while(Can_LLD_TxIsReqPending(eCan_Instance, u8Can_Tx_buffer_index) == TRUE)
    {
        if(retry_cnt < (base->TXBC.B.NDTB - 1U)) /* PRQA S 1891 *//* polyspace RTE:NIV */
        {
            retry_cnt++;
            if(u8Can_Tx_buffer_index < (base->TXBC.B.NDTB - 1U))
            {
                u8Can_Tx_buffer_index++; /* PRQA S 1338 */
            }
            else
            {
                u8Can_Tx_buffer_index = 0U; /* PRQA S 1338 */
            }
        }
        else
        {
            return msgs_sent;
        }
    }
    Can_LLD_TxWriteMsgToBuffer(eCan_Instance, pCan_Tx_msg_ptr, u8Can_Tx_buffer_index);
    Can_LLD_TxMsgSingleRequest(eCan_Instance, u8Can_Tx_buffer_index);
    msgs_sent = 1U;
    return msgs_sent;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxSendFifoQueueMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(pCan_Tx_msg_ptr != NULL);
    DEV_ASSERT(pCan_Tx_msg_ptr->direction == TX_DIR);

    VAR(uint32, AUTOMATIC) msgs_sent = 0U;
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if((((base->TXFQS.R) & MCAN_TXFQS_TFQF_MASK) >> MCAN_TXFQS_TFQF_SHIFT) == 0U)/* polyspace RTE:NIV */
    {
        Can_LLD_TxWriteMsgToBuffer
        (
            eCan_Instance,
            pCan_Tx_msg_ptr,
            (uint8)(((base->TXFQS.R) & MCAN_TXFQS_TFQPI_MASK) >> MCAN_TXFQS_TFQPI_SHIFT)
        );
        Can_LLD_TxMsgSingleRequest
        (
            eCan_Instance,
            (uint8)(((base->TXFQS.R) & MCAN_TXFQS_TFQPI_MASK) >> MCAN_TXFQS_TFQPI_SHIFT)
        );
        msgs_sent = 1U;
    }
    else
    {
        msgs_sent = 0U;
    }

    return msgs_sent;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxFifoGetNumOfFreeElems(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    return ((base->TXFQS.R & MCAN_TXFQS_TFFL_MASK) >> MCAN_TXFQS_TFFL_SHIFT);/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxSendRequestCancel \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buf_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if(u8Can_Tx_buf_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u8Can_Tx_buf_index);
    }

    base->TXBCR.R = (( base->TXBCR.R) & ~MCAN_TXBCR_CR_MASK) | mask;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_TxSendReqCancelFinshed \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buf_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if(u8Can_Tx_buf_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u8Can_Tx_buf_index);
    }

    if(((base->TXBCF.R) & mask) != 0U)/* polyspace RTE:NIV */
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_TxTranOccured \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Tx_buf_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if(u32Can_Tx_buf_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u32Can_Tx_buf_index);
    }

    if(((base->TXBTO.R) & mask) != 0U)/* polyspace RTE:NIV */
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

extern FUNC(void, CAN_CODE) MCAN_RxNotifiy \
( \
    VAR(uint8, AUTOMATIC) u8Can_ControllerIdx, \
    VAR(uint32, AUTOMATIC) u32Can_CanObjectId, \
    P2CONST(can_msg_struct, CAN_VAR, CAN_APPL_DATA) pCan_MsgInfo \
);

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_RxCopyMsgFromRamToList \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Msg_addr_in_msg_ram, \
    VAR(rx_info_struct, AUTOMATIC) sCan_Rx_info \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) i = 0U;
    VAR(uint32, AUTOMATIC) ram_word = 0U;
    VAR(uint32, AUTOMATIC) byte_index = 0U;
    VAR(uint32, AUTOMATIC) bytes_to_read = 0U;
    VAR(can_msg_struct, AUTOMATIC) msg_ptr = {0};
    VAR(uint32, AUTOMATIC) u32Can_HwObjectIdex = 0U;
    VAR(boolean, AUTOMATIC) bCan_IsFifo0 = FALSE;
    VAR(boolean, AUTOMATIC) bCan_IsFifo1 = FALSE;
    VAR(boolean, AUTOMATIC) bCan_IsBuffer = FALSE;
    P2CONST(mcan_hwObject, AUTOMATIC, CAN_APPL_DATA) pCan_HwObject = NULL_PTR;
    VAR(uint8, AUTOMATIC) u8Can_ControllerId = 0U;

    bytes_to_read = CAN_FD_MAX_NO_OF_DTB_PER_FRAME;

    msg_ptr.direction = RX_DIR;
    msg_ptr.rx_info = sCan_Rx_info;

    while(bytes_to_read > 0U)
    {
        ram_word = *(uint32 *)(u32Can_Msg_addr_in_msg_ram + (i *4U));/* polyspace RTE:NIV,IDP */

        if (i == 0U)
        {
            /*
                [SWS_Can_00423] In case of an Extended CAN frame, the Can module shall 
                convert the ID to a standardized format since the Upper layer (CANIF) does not know 
                whether the received CAN frame is a Standard CAN frame or Extended CAN frame. 
                In case of an Extended CAN frame, MSB of a received CAN frame ID needs to be 
                made as 1 to mark the received CAN frame as Extended.
            */
            if ((ram_word & MCAN_RX_BUFFER_XTD_MASK) == 0U)
            {
                msg_ptr.idtype = STANDARD_ID;
                msg_ptr.id = (uint32)((ram_word \
                               & MCAN_RX_BUFFER_STD_ID_MASK) >> MCAN_RX_BUFFER_STD_ID_SHIFT);
            }
            else
            {
                msg_ptr.idtype = EXTENDED_ID;
                msg_ptr.id = (ram_word & MCAN_RX_BUFFER_EXT_ID_MASK);
            }

            if ((ram_word & MCAN_RX_BUFFER_RTR_MASK) == 0U)
            {
                msg_ptr.remote = FALSE;
            }
            else
            {
                msg_ptr.remote = TRUE;
            }

            if ((ram_word & MCAN_RX_BUFFER_ESI_MASK) == 0U)
            {
                msg_ptr.esi = FALSE;
            }
            else
            {
                msg_ptr.esi = TRUE;
            }
        }
        else if(i == 1U)
        {
            msg_ptr.dlc = (uint16)((ram_word \
                                      & MCAN_RX_BUFFER_DLC_MASK)>> MCAN_RX_BUFFER_DLC_SHIFT);

            bytes_to_read =  (uint32)MCAN_ConvertDLCToDataLength(msg_ptr.dlc);

            if ((ram_word & MCAN_RX_BUFFER_FDF_MASK) == 0U)
            {
                msg_ptr.fdf = FALSE;
            }
            else
            {
                msg_ptr.fdf = TRUE;
            }

            if ((ram_word & MCAN_RX_BUFFER_BRS_MASK) == 0U)
            {
                msg_ptr.brs = FALSE;
            }
            else
            {
                msg_ptr.brs = TRUE;
            }

            msg_ptr.rx_info.rx_timestamp = ram_word & MCAN_RX_BUFFER_RXTS_MASK;
        }
        else
        {
            byte_index = (i - 2U) * 4U;
            msg_ptr.data[byte_index] = (uint8)(ram_word & 0x000000FFU);
            msg_ptr.data[byte_index +1U] = (uint8)((ram_word & 0x0000FF00U) >> 8U);
            msg_ptr.data[byte_index +2U] = (uint8)((ram_word & 0x00FF0000U) >> 16U);
            msg_ptr.data[byte_index +3U] = (uint8)((ram_word & 0xFF000000U) >> 24U);
            if (bytes_to_read >= 4U)
            {
                bytes_to_read = bytes_to_read - 4U;
            }
            else
            {
                bytes_to_read = 0U;
            }
        }

        i++;
    }
    
    u8Can_ControllerId = s_sInsToCtrlMap[eCan_Instance].controllerId;
    for (u32Can_HwObjectIdex = 0; u32Can_HwObjectIdex < g_pCan_CurConfig->HwObjCount; u32Can_HwObjectIdex++)/* polyspace RTE:IDP */
    {
        pCan_HwObject = &g_pCan_CurConfig->hwObjectConfig[u32Can_HwObjectIdex];
        if ((pCan_HwObject->CanObjectType == RECEIVE) && (u8Can_ControllerId == pCan_HwObject->CanControllerId))/* polyspace RTE:IDP */
        {
            if (msg_ptr.rx_info.rx_via == FIFO_0)
            {
                if ((pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO0))
                {
                    if (FILTER_TYPE_RANGE_ID == pCan_HwObject->filterType)
                    {
                        if ((pCan_HwObject->filterCode <= msg_ptr.id) && (msg_ptr.id <= pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo0 = TRUE;
                        }
                    }
                    else if (FILTER_TYPE_DUAL_ID == pCan_HwObject->filterType)
                    {
                        if ((msg_ptr.id == pCan_HwObject->filterCode) || (msg_ptr.id == pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo0 = TRUE;
                        }
                    }
                    else
                    {
                        if ((pCan_HwObject->filterCode & pCan_HwObject->filterMask) == (msg_ptr.id & pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo0 = TRUE;
                        }
                    }
                }
            }
            else if (msg_ptr.rx_info.rx_via == FIFO_1)
            {
                if ((pCan_HwObject->mbIdex == MCAN_STORE_RX_FIFO1))
                {
                    if (FILTER_TYPE_RANGE_ID == pCan_HwObject->filterType)
                    {
                        if ((pCan_HwObject->filterCode <= msg_ptr.id) && (msg_ptr.id <= pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo1 = TRUE;
                        }
                    }
                    else if (FILTER_TYPE_DUAL_ID == pCan_HwObject->filterType)
                    {
                        if ((msg_ptr.id == pCan_HwObject->filterCode) || (msg_ptr.id == pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo1 = TRUE;
                        }
                    }
                    else
                    {
                        if ((pCan_HwObject->filterCode & pCan_HwObject->filterMask) == (msg_ptr.id & pCan_HwObject->filterMask))
                        {
                            bCan_IsFifo1 = TRUE;
                        }
                    }
                }
            }
            else
            {
                if (msg_ptr.rx_info.buffer_index == pCan_HwObject->mbIdex)
                {
                    bCan_IsBuffer = TRUE;
                }
            }
        }

        if (bCan_IsFifo0 || bCan_IsFifo1 || bCan_IsBuffer)
        {
            MCAN_RxNotifiy(u8Can_ControllerId, pCan_HwObject->CanObjectId, &msg_ptr);
            break;
        }
    }

}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
CAN_INLINE FUNC(void, CAN_CODE) Can_LLD_RxRecDedicatedMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Ded_buffer_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT(u32Can_Ded_buffer_index <= FEATURE_MCAN_RX_MB_NUM);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];

    VAR(uint32, AUTOMATIC) u32Can_Start_Adr = 0U;

    VAR(uint32, AUTOMATIC) paysize = MCAN_GetPayloadSize(base, MCAN_RX_BUFF);
    VAR(uint32, AUTOMATIC) ram_read_addr;
    VAR(rx_info_struct, AUTOMATIC) sCan_Rx_info;

    if(eCan_Instance < MCAN_MOD_ID_5)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMA_START_ADR;
    }
    else if(eCan_Instance < MCAN_MOD_ID_9)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMB_START_ADR;
    }
    else
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMC_START_ADR;
    }

    ram_read_addr = ((base->RXBC.R & MCAN_RXBC_RBSA_MASK) /* polyspace RTE:NIV */
                     + u32Can_Start_Adr) + (u32Can_Ded_buffer_index *(paysize + 8U));

    sCan_Rx_info.rx_via = DEDICATED_RX_BUFFER;
    sCan_Rx_info.buffer_index = u32Can_Ded_buffer_index;
    sCan_Rx_info.rx_timestamp = 0U;

    Can_LLD_RxCopyMsgFromRamToList(eCan_Instance, ram_read_addr, sCan_Rx_info);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_RxDedicateBufProcNewMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) ded_buffer_index = 0U;
    VAR(uint32, AUTOMATIC) msgs_read = 0U;
    VAR(uint32, AUTOMATIC) mask = 0U;
    VAR(uint8, AUTOMATIC) j = 0U;
    VAR(uint32, AUTOMATIC) new_data_reg[2U];

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */


    new_data_reg[0] = base->NDAT1.R;/* polyspace RTE:NIV */
    new_data_reg[1] = base->NDAT2.R;/* polyspace RTE:NIV */

    for (j = 0U; j < 2U; ++j)
    {
        ded_buffer_index = (uint32)j *32U;
        mask = 1U;

        while (new_data_reg[j] > 0U)
        {
            if ((mask & new_data_reg[j]) != 0U)
            {
                if (ded_buffer_index > FEATURE_MCAN_RX_MB_NUM)
                {
                    return msgs_read;
                }
                Can_LLD_RxRecDedicatedMsg(eCan_Instance, ded_buffer_index);
                msgs_read++;

                if (j==0U)
                {
                    base->NDAT1.R = mask;
                }
                else
                {
                    base->NDAT2.R = mask;;
                }
                new_data_reg[j]=new_data_reg[j] & ~mask;
            }
            ded_buffer_index++;
            mask = mask << 1U;
        }
    }

    return msgs_read;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_RxRecFifoMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Rx_fifo_number \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);
    DEV_ASSERT((u32Can_Rx_fifo_number == 0U) || (u32Can_Rx_fifo_number == 1U));

    VAR(uint32, AUTOMATIC) paysize;
    VAR(uint32, AUTOMATIC) msgs_read = 0U;
    VAR(uint32, AUTOMATIC) ram_read_addr;
    VAR(rx_info_struct, AUTOMATIC) sCan_Rx_info;
    VAR(uint32, AUTOMATIC) RXF0S_F0GI_temp = 0U;
    VAR(uint32, AUTOMATIC) RXF1S_F1GI_temp = 0U;
    VAR(uint32, AUTOMATIC) u32Can_Start_Adr = 0U;
    VAR(uint32, AUTOMATIC) cycle_index_flg = 0U;

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if(eCan_Instance < MCAN_MOD_ID_5)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMA_START_ADR;
    }
    else if(eCan_Instance < MCAN_MOD_ID_9)
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMB_START_ADR;
    }
    else
    {
        u32Can_Start_Adr = FEATURE_MCAN_MSG_RAMC_START_ADR;
    }

    switch (u32Can_Rx_fifo_number)
    {
    case 0:
    {
        while(((((base->RXF0S.R) & MCAN_RXF0S_F0FL_MASK) >> MCAN_RXF0S_F0FL_SHIFT) > 0U) && (cycle_index_flg < 64U))/* polyspace RTE:NIV */
        {
            RXF0S_F0GI_temp = ((base->RXF0S.R & MCAN_RXF0S_F0GI_MASK) >> MCAN_RXF0S_F0GI_SHIFT);
            msgs_read++;
            paysize = MCAN_GetPayloadSize(base, MCAN_RX_FIFO0);
            ram_read_addr = ((base->RXF0C.R & MCAN_RXF0C_F0SA_MASK) /* polyspace RTE:NIV */
                                + u32Can_Start_Adr) \
                                + (RXF0S_F0GI_temp * (paysize + 8U));
            sCan_Rx_info.rx_via = FIFO_0;
            sCan_Rx_info.buffer_index = RXF0S_F0GI_temp;
            sCan_Rx_info.rx_timestamp = 0U;
            Can_LLD_RxCopyMsgFromRamToList(eCan_Instance, ram_read_addr, sCan_Rx_info);
            base->RXF0A.R = (base->RXF0A.R & ~MCAN_RXF0A_F0AI_MASK) /* polyspace RTE:NIV */
                                | MCAN_RXF0A_F0AI(RXF0S_F0GI_temp);
            cycle_index_flg++;
        }
        break;
    }
    case 1:
    {
        while(((((base->RXF1S.R) & MCAN_RXF1S_F1FL_MASK) >> MCAN_RXF1S_F1FL_SHIFT) > 0U) && (cycle_index_flg < 64U))/* polyspace RTE:NIV */
        {
            RXF1S_F1GI_temp = ((base->RXF1S.R & MCAN_RXF1S_F1GI_MASK) >> MCAN_RXF1S_F1GI_SHIFT);
            msgs_read++;
            paysize = MCAN_GetPayloadSize(base, MCAN_RX_FIFO1);
            ram_read_addr = ((base->RXF1C.R & MCAN_RXF1C_F1SA_MASK) /* polyspace RTE:NIV */
                                + u32Can_Start_Adr) \
                                + (RXF1S_F1GI_temp * (paysize + 8U));
            sCan_Rx_info.rx_via = FIFO_1;
            sCan_Rx_info.rx_timestamp = 0U;
            sCan_Rx_info.buffer_index = RXF1S_F1GI_temp;
            Can_LLD_RxCopyMsgFromRamToList(eCan_Instance, ram_read_addr, sCan_Rx_info);
            base->RXF1A.R = (base->RXF1A.R & ~MCAN_RXF1A_F1AI_MASK) /* polyspace RTE:NIV */
                                | MCAN_RXF1A_F1AI(RXF1S_F1GI_temp);
            cycle_index_flg++;
        }
        break;
    }
    default:
    {
        /* nothing */
        break;
    }
    }

    return msgs_read;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_IsDataLost \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Rx_fifo_number \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint8, AUTOMATIC) IsDataLost = 0U;
    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    VAR(uint32, AUTOMATIC) IR_REG_VAULE = base->IR.R;/* polyspace RTE:NIV */
    if (u32Can_Rx_fifo_number == 0U)
    {
        if((IR_REG_VAULE & MCAN_IR_RF0L_MASK) != 0U)
        {
            base->IR.R = MCAN_IR_RF0L_MASK;
            IsDataLost = 1U;
        }

        if((IR_REG_VAULE & MCAN_IR_RF0F_MASK) != 0U)
        {
            base->IR.R = MCAN_IR_RF0F_MASK;
            IsDataLost = 1U;
        }
    }
    else
    {
        if((IR_REG_VAULE & MCAN_IR_RF1F_MASK) != 0U)
        {
            base->IR.R = MCAN_IR_RF1F_MASK;
            IsDataLost = 1U;
        }

        if((IR_REG_VAULE & MCAN_IR_RF1L_MASK) != 0U)
        {
            base->IR.R = MCAN_IR_RF1L_MASK;
            IsDataLost = 1U;
        }
    }
    return IsDataLost;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_InterDisableAllSignals(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
    MCAN_InterDisableAllSignals(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_InterruptInit \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(mcan_inter_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
    MCAN_InterruptInit(base, pCan_Config);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_IsBusOff(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if (MCAN_PSR_BO_MASK == MCAN_GetBoState(base))
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_IsErrorActive(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if (MCAN_PSR_EP_MASK != MCAN_GetEpState(base))
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_GetRxErrorCounter(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    return (uint8)base->ECR.B.REC;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_GetTxErrorCounter(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    return (uint8)base->ECR.B.TEC;/* polyspace RTE:NIV */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_IsFDEnabled(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    return MCAN_IsFDEnabled(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isInitState(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    return MCAN_isInitState(base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isSleep(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;

    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if ((((base->CCCR.R & MCAN_CCCR_CSR_MASK) >> MCAN_CCCR_CSR_SHIFT) == 1U))/* polyspace RTE:NIV */
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_SetTimeOut(VAR(uint32, CAN_VAR) u32Can_TimeOutDuration)
{
    VAR(uint32, AUTOMATIC) u32Can_CoreId = 0U;

    u32Can_CoreId = Can_GetCoreID();    /*get coreid*/
    s_u32Can_TimeOut[u32Can_CoreId] = u32Can_TimeOutDuration;/* polyspace RTE:OBAI */
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_RsetInit(VAR(MCANModId, AUTOMATIC) eCan_Instance)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    P2VAR(MCAN_Type, AUTOMATIC, CAN_APPL_DATA) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */
    MCAN_RsetInit((MCAN_Type*)(uint32)base);
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isTxInterruptMb \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Tx_buf_index \
)
{
    DEV_ASSERT(eCan_Instance < CAN_MOD_BUTT);

    VAR(uint32, AUTOMATIC) mask = 0U;
    VAR(boolean, AUTOMATIC) bCan_Ret = FALSE;
    P2CONST(MCAN_Type, AUTOMATIC, CAN_APPL_CONST) base = g_mcanBase[eCan_Instance];/* polyspace RTE:OBAI */

    if(u32Can_Tx_buf_index < FEATURE_MCAN_TX_MB_NUM)
    {
        mask = (uint32)(1UL << u32Can_Tx_buf_index);
    }

    if(((base->TXBTIE.R) & mask) != 0U)/* polyspace RTE:NIV */
    {
        bCan_Ret = TRUE;
    }
    else
    {
        bCan_Ret = FALSE;
    }

    return bCan_Ret;
}
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif
