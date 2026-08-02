#include "tester_can.h"
#include "Det.h"
#include "StandardTypes.h"
#include "Compiler.h"
#include "Can_GeneralTypes.h"
#include "console.h"
#include "CanIf.h"
#include "shell.h"
#include <string.h>
#include "Gpt_Stm_LLDriver.h"
#include "intc_lld.h"

#define CAN_DLC       8
#define CAN_FD_DLC    64
#define CAN_FD_DLC_48 48
#define CAN_FD_DLC_32 32
#define CAN_FD_DLC_24 24
#define CAN_FD_DLC_20 20
#define CAN_FD_DLC_16 16
#define CAN_FD_DLC_12 12
#define CAN_TEST_CASE_MAX 10
#define CAN_1_TX_MAX 55
#define CAN_2_TX_MAX 34
#define CAN_3_TX_MAX 14
#define CAN_4_TX_MAX 34

#define CAN_FUNC_UNITS(id)       CAN_000##id
#define CAN_FUNC_TENS(id)        CAN_00##id
#define CAN_FUNC_HUNDREDS(id)    CAN_0##id

static uint8 txBuffer_can_1[CAN_DLC];
static uint8 txBuffer_can_2[CAN_DLC];
static uint8 txBuffer_can_3[CAN_DLC];
static uint8 txBuffer_can_4[CAN_DLC];
static uint8 McanController[5U] = {
#ifdef CAN1
    CAN1,
#else
    0xFF,
#endif
#ifdef CAN2
    CAN2,
#else
    0xFF,
#endif
#ifdef CAN3
    CAN3,
#else
    0xFF,
#endif
#ifdef CAN4
    CAN4,
#else
    0xFF,
#endif
#ifdef CAN5
    CAN5,
#else
    0xFF,
#endif
};

static CanfuncMachine can_funcs[] = {
    {"CAN_0001", CAN_0001},
    {"CAN_0002", CAN_0002},
    {"CAN_0003", CAN_0003},
    {"CAN_0004", CAN_0004},
    {"CAN_0005", CAN_0005},
    {"CAN_0006", CAN_0006},
    {"CAN_0007", CAN_0007},
    {"CAN_0008", CAN_0008},
    {"CAN_0009", CAN_0009},
    {"CAN_0010", CAN_0010},
};

void CAN_IRQ_Priority() {
    INTC_LLD_Set_IRQ_Priority(MCAN1_0_IRQ688, INTR_PRI_7);
    INTC_LLD_Set_IRQ_Priority(MCAN2_0_IRQ690, INTR_PRI_7);
    INTC_LLD_Set_IRQ_Priority(MCAN3_0_IRQ692, INTR_PRI_7);
    INTC_LLD_Set_IRQ_Priority(MCAN4_0_IRQ694, INTR_PRI_7);
    INTC_LLD_Set_IRQ_Priority(MCAN10_0_IRQ447, INTR_PRI_7);

    INTC_LLD_Set_IRQ_Handle(MCAN1_0_IRQ688, &ISR_M_CAN1_0);
    INTC_LLD_Set_IRQ_Handle(MCAN2_0_IRQ690, &ISR_M_CAN2_0);
    INTC_LLD_Set_IRQ_Handle(MCAN3_0_IRQ692, &ISR_M_CAN3_0);
    INTC_LLD_Set_IRQ_Handle(MCAN4_0_IRQ694, &ISR_M_CAN4_0);
    INTC_LLD_Set_IRQ_Handle(MCAN10_0_IRQ447, &ISR_M_CAN10_0);

    INTC_LLD_Set_IRQ_Enable(MCAN1_0_IRQ688);
    INTC_LLD_Set_IRQ_Enable(MCAN2_0_IRQ690);
    INTC_LLD_Set_IRQ_Enable(MCAN3_0_IRQ692);
    INTC_LLD_Set_IRQ_Enable(MCAN4_0_IRQ694);
    INTC_LLD_Set_IRQ_Enable(MCAN10_0_IRQ447);
}

extern VAR(Can_DriverStateType, CAN_VAR) g_eCan_DriverState;

void CAN_0001() {
    Can_Init(&Can_Config);

    if (g_eCan_DriverState == CAN_READY) {
        PSPRINTF("CAN_0001 is ok\n");
    } else {
        PSPRINTF("CAN_0001 is not ok g_eCan_DriverState[%d]\n", g_eCan_DriverState);
    }
}

void CAN_0002() {
    memset(txBuffer_can_1, 0x11, CAN_DLC);
    memset(txBuffer_can_2, 0x22, CAN_DLC);
#ifdef CAN1
    CAN_0001();
    Can_SetControllerMode(CAN1, CAN_CS_STARTED);
    Can_SetControllerMode(CAN2, CAN_CS_STARTED);

    static uint32 tx_can1_Id[CAN_1_TX_MAX] = {0xD8FEF500U, 0xD8FEF100U, 0xD8E0FF00U, 0xD8FD0700U, \
                                              0xD8FECA00U, 0xD8FD7C00U, 0xD8FEE300U, 0xD8FF7100U, \
                                              0xCCF00400U, 0xCCF00300U, 0xD8FEDF00U, 0xD8FEEF00U, \
                                              0xD8FCE400U, 0xD8FF7400U, 0xD8F0000FU, 0xD8F00029U, \
                                              0xD8FEEE00U, 0xD8FE6900U, 0xD8FEE500U, 0xD8FEF600U, \
                                              0xD8FEE900U, 0xD8FEF200U, 0xD9FE3100U, 0xD9FE3200U, \
                                              0xD9FE3300U, 0xD9FE3400U, 0xD9FE3500U, 0xD9FE3600U, \
                                              0xD9FE3700U, 0xD9FE3800U, 0xD9FE3900U, 0xD9FE4000U, \
                                              0xD9FE4100U, 0xD9FE4200U, 0xD9FE4300U, 0xD9FE4400U, \
                                              0xD9FE4500U, 0xD9FE6100U, 0xD9FE6200U, 0xD8FEE10FU, \
                                              0xD8FEE129U, 0xD8EA2700U, 0xD8EAFF00U, 0xD8FF8000U, \
                                              0xD8FF7F00U, 0xD8FEDA00U, 0xD8FE5600U, 0xDCECFF00U, \
                                              0xDCECFF0FU, 0xDCECFF29U, 0xDCEBFF00U, 0xDCEBFF0FU, \
                                              0xDCEBFF29U, 0xD8FEE000U, 0xD8FEC100U};
    
    static uint32 tx_can2_Id[CAN_2_TX_MAX] = {0xC8FF8200U, 0xD8EA5100U, 0xD8EA5200U, 0xD8EAFF00U, \
                                              0xD9FE5100U, 0xD9FE5200U, 0xD9FE5300U, 0xD9FE5400U, \
                                              0xD9FE5500U, 0xD9FE5600U, 0xD9FE5700U, 0xD9FE5800U, \
                                              0xD9FE5900U, 0xD9FE6000U, 0xD9FE6100U, 0xD9FE6200U, \
                                              0xD9FE6300U, 0xD9FE6400U, 0xD9FE6500U, 0xD9FE7100U, \
                                              0xD9FE7200U, 0xD9FE7300U, 0xD9FE7400U, 0xD9FE7500U, \
                                              0xD8FEDF00U, 0xD8FFDC00U, 0xD8FF7600U, 0xD8FF6300U, \
                                              0xD4FF023DU, 0xD8FFEF00U, 0xD8FFF000U, 0xD8FF3100U, \
                                              0xCCFFC600U, 0xD8FF1000U};

    Can_PduType pduInfo_can_1;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Can_PduType pduInfo_can_2;
    pduInfo_can_2.length = CAN_DLC;
    pduInfo_can_2.sdu = txBuffer_can_2;
    pduInfo_can_2.swPduHandle = 1;

    Std_ReturnType ret = 0U;
    uint32 index_can1 = 0U;
    uint32 index_can2 = 0U;

    while (index_can1 < CAN_1_TX_MAX)
    {
        pduInfo_can_1.id = tx_can1_Id[index_can1];
        ret = Can_Write(TX_CAN1, &pduInfo_can_1);
        Gpt_Stm_LLD_DelayMs(STM1, 50U);
        PSPRINTF("CAN_0002 can1 ret[%d]\n", ret);
        if (ret == 0U)
        {
            index_can1++;
        }

    }

    while (index_can2 < CAN_2_TX_MAX)
    {
        pduInfo_can_2.id = tx_can2_Id[index_can2];
        ret = Can_Write(TX_CAN2, &pduInfo_can_2);
        Gpt_Stm_LLD_DelayMs(STM1, 50U);
        PSPRINTF("CAN_0002 can2 ret[%d]\n", ret);
        if (ret == 0U)
        {
            index_can2++;
        }
    }
#endif
}

void CAN_0003() {
    memset(txBuffer_can_3, 0x33, CAN_DLC);
    memset(txBuffer_can_4, 0x44, CAN_DLC);
#ifdef CAN3
    CAN_0001();
    Can_SetControllerMode(CAN3, CAN_CS_STARTED);
    Can_SetControllerMode(CAN4, CAN_CS_STARTED);

    static uint32 tx_can3_Id[CAN_3_TX_MAX] = {0xD8DAF100U, 0x7A2U, 0x7A3U, 0x7A4U, 0x7A5U, \
                                              0x7A6U, 0x7A7U, 0x7A8U, 0x7A9U, 0x7AAU, \
											  0x7ABU, 0x7ACU, 0x7ADU, 0x7AEU};

    static uint32 tx_can4_Id[CAN_4_TX_MAX] = {0xC8FF8200U, 0xD8EA5100U, 0xD8EA5200U, 0xD8EAFF00U, \
                                              0xD9FE5100U, 0xD9FE5200U, 0xD9FE5300U, 0xD9FE5400U, \
                                              0xD9FE5500U, 0xD9FE5600U, 0xD9FE5700U, 0xD9FE5800U, \
                                              0xD9FE5900U, 0xD9FE6000U, 0xD9FE6100U, 0xD9FE6200U, \
                                              0xD9FE6300U, 0xD9FE6400U, 0xD9FE6500U, 0xD9FE7100U, \
                                              0xD9FE7200U, 0xD9FE7300U, 0xD9FE7400U, 0xD9FE7500U, \
                                              0xD8FEDF00U, 0xD8FFDC00U, 0xD8FF7600U, 0xD8FF6300U, \
                                              0xD4FF023DU, 0xD8FFEF00U, 0xD8FFF000U, 0xD8FF3100U, \
                                              0xCCFFC600U, 0xD8FF1000U};

    Can_PduType pduInfo_can_3;
    pduInfo_can_3.length = CAN_DLC;
    pduInfo_can_3.sdu = txBuffer_can_3;
    pduInfo_can_3.swPduHandle = 2;

    Can_PduType pduInfo_can_4;
    pduInfo_can_4.length = CAN_DLC;
    pduInfo_can_4.sdu = txBuffer_can_4;
    pduInfo_can_4.swPduHandle = 3;

    Std_ReturnType ret = 0U;
    uint32 index_can3 = 0U;
    uint32 index_can4 = 0U;

    while (index_can3 < CAN_3_TX_MAX)
    {
        pduInfo_can_3.id = tx_can3_Id[index_can3];
        ret = Can_Write(TX_CAN3, &pduInfo_can_3);
        Gpt_Stm_LLD_DelayMs(STM1, 50U);
        PSPRINTF("CAN_0003 can3 ret[%d]\n", ret);
        if (ret == 0U)
        {
            index_can3++;
        }
    }

    while (index_can4 < CAN_4_TX_MAX)
    {
        pduInfo_can_4.id = tx_can4_Id[index_can4];
        ret = Can_Write(TX_CAN4, &pduInfo_can_4);
        Gpt_Stm_LLD_DelayMs(STM1, 50U);
        PSPRINTF("CAN_0003 can4 ret[%d]\n", ret);
        if (ret == 0U)
        {
            index_can4++;
        }
    }
#endif
}

void CAN_0004() {
    CAN_0001();
#ifdef CAN1
#ifdef TX_CAN1
    memset(txBuffer_can_1, 0x80, CAN_DLC);
    Can_SetControllerMode(CAN1, CAN_CS_STARTED);
    Can_ControllerStateType state = CAN_CS_UNINIT;

    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Can_GetControllerMode(CAN1, &state);
    while (state == CAN_CS_STARTED)
    {
        Gpt_Stm_LLD_DelayMs(STM1, 500U);

        Can_Write(TX_CAN1, &pduInfo_can_1);
        Can_GetControllerMode(CAN1, &state);
    }

    if (state == CAN_CS_STOPPED)
    {
        PSPRINTF("CAN_0004 is ok\n");
    }
    else
    {
        PSPRINTF("CAN_0004 is not ok state[%d]\n", state);
    }
#endif
#endif
}

void CAN_0005() {
#ifdef CAN1
#ifdef TX_CAN1
    static uint8 num = 0U;
    memset(txBuffer_can_1, 0x80, CAN_DLC);
    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    uint32 count = 0U;
    uint32 flag = 0U;
    Std_ReturnType ret = E_NOT_OK;

    if (num == 0U)
    {
        CAN_0001();
        Can_SetControllerMode(CAN1, CAN_CS_STARTED);
        while (count < 10U)
        {
            count++;
            Gpt_Stm_LLD_DelayMs(STM1, 100U);

            Can_Write(TX_CAN1, &pduInfo_can_1);
        }
        num++;
    }
    else
    {
        num = 0U;
        count = 0U;
        while (count < 10)
        {
            count++;
            Gpt_Stm_LLD_DelayMs(STM1, 100U);

            ret = Can_Write(TX_CAN1, &pduInfo_can_1);
            if (ret != 0)
            {
                flag++;
            }
        }
        if (flag != 0)
        {
            PSPRINTF("CAN_0005 is ok\n");
        }
        else
        {
            PSPRINTF("CAN_0005 is not ok\n");
        }
    }
#endif
#endif
}

void CAN_0006() {
#ifdef CAN1
#ifdef TX_CAN1
    static uint8 num = 0U;
    
    Can_ControllerStateType state = CAN_CS_UNINIT;
    memset(txBuffer_can_1, 0x80, CAN_DLC);
    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    uint32 count = 0U;
    if (num == 0U)
    {
        CAN_0001();
        Can_SetControllerMode(CAN1, CAN_CS_STARTED);
        while (count < 10U)
        {
            count++;
            Gpt_Stm_LLD_DelayMs(STM1, 100U);

            Can_Write(TX_CAN1, &pduInfo_can_1);
        }

        while (state != CAN_CS_STOPPED)
        {
            Can_GetControllerMode(CAN1, &state);
        }

        num++;
    }
    else
    {
        num = 0U;
        Can_SetControllerMode(CAN1, CAN_CS_STARTED);
        count = 0U;
        while (count < 10U)
        {
            count++;
            Gpt_Stm_LLD_DelayMs(STM1, 100U);

            Can_Write(TX_CAN1, &pduInfo_can_1);
        }
    }
#endif
#endif
}

void CAN_0007() {
#ifdef CAN1
    CAN_0001();
    Can_SetControllerMode(CAN1, CAN_CS_STOPPED);
    Can_SetControllerMode(CAN1, CAN_CS_SLEEP);

    memset(txBuffer_can_1, 0x11, CAN_DLC);
    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Std_ReturnType ret = E_NOT_OK;
    uint32 count = 0U;

    while (count < 10U)
    {
        count++;
        Gpt_Stm_LLD_DelayMs(STM1, 100U);

        Can_Write(TX_CAN1, &pduInfo_can_1);
    }
#endif
}

void CAN_0008() {
#ifdef CAN1
    CAN_0001();
    Can_SetControllerMode(CAN1, CAN_CS_STOPPED);
    Can_SetControllerMode(CAN1, CAN_CS_SLEEP);
    Can_SetControllerMode(CAN1, CAN_CS_STOPPED);
    Can_SetControllerMode(CAN1, CAN_CS_STARTED);

    memset(txBuffer_can_1, 0x11, CAN_DLC);
    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Std_ReturnType ret = E_NOT_OK;
    uint32 count = 0U;

    while (count < 10U)
    {
        count++;
        Gpt_Stm_LLD_DelayMs(STM1, 100U);

        Can_Write(TX_CAN1, &pduInfo_can_1);
    }
#endif
}

void CAN_0009() {
#ifdef CAN1
#ifdef TX_CAN1
    CAN_0001();
    memset(txBuffer_can_1, 0x80, CAN_DLC);
    Can_SetControllerMode(CAN1, CAN_CS_STARTED);

    Can_PduType pduInfo_can_1;
    pduInfo_can_1.id = 0xD8FEF500U;
    pduInfo_can_1.length = 9;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Can_Write(TX_CAN1, &pduInfo_can_1);
    if ((Det_ModuleId == CAN_MODULE_ID) && (CAN_E_PARAM_DATA_LENGTH == Det_ErrorId))
    {
        PSPRINTF("CAN_0009 is ok\n");
    }
    else
    {
        PSPRINTF("CAN_0009 is not ok\n");
    }
#endif
#endif
}

void CAN_0010() {
    memset(txBuffer_can_1, 0x11, CAN_DLC);
    memset(txBuffer_can_2, 0x22, CAN_DLC);
    memset(txBuffer_can_3, 0x33, CAN_DLC);
    memset(txBuffer_can_4, 0x44, CAN_DLC);
#ifdef CAN1
    CAN_0001();
    Can_SetControllerMode(CAN1, CAN_CS_STARTED);
    Can_SetControllerMode(CAN2, CAN_CS_STARTED);
    Can_SetControllerMode(CAN3, CAN_CS_STARTED);
    Can_SetControllerMode(CAN4, CAN_CS_STARTED);

    static uint32 tx_can1_Id[CAN_1_TX_MAX] = {0xD8FEF500U, 0xD8FEF100U, 0xD8E0FF00U, 0xD8FD0700U, \
                                              0xD8FECA00U, 0xD8FD7C00U, 0xD8FEE300U, 0xD8FF7100U, \
                                              0xCCF00400U, 0xCCF00300U, 0xD8FEDF00U, 0xD8FEEF00U, \
                                              0xD8FCE400U, 0xD8FF7400U, 0xD8F0000FU, 0xD8F00029U, \
                                              0xD8FEEE00U, 0xD8FE6900U, 0xD8FEE500U, 0xD8FEF600U, \
                                              0xD8FEE900U, 0xD8FEF200U, 0xD9FE3100U, 0xD9FE3200U, \
                                              0xD9FE3300U, 0xD9FE3400U, 0xD9FE3500U, 0xD9FE3600U, \
                                              0xD9FE3700U, 0xD9FE3800U, 0xD9FE3900U, 0xD9FE4000U, \
                                              0xD9FE4100U, 0xD9FE4200U, 0xD9FE4300U, 0xD9FE4400U, \
                                              0xD9FE4500U, 0xD9FE6100U, 0xD9FE6200U, 0xD8FEE10FU, \
                                              0xD8FEE129U, 0xD8EA2700U, 0xD8EAFF00U, 0xD8FF8000U, \
                                              0xD8FF7F00U, 0xD8FEDA00U, 0xD8FE5600U, 0xDCECFF00U, \
                                              0xDCECFF0FU, 0xDCECFF29U, 0xDCEBFF00U, 0xDCEBFF0FU, \
                                              0xDCEBFF29U, 0xD8FEE000U, 0xD8FEC100U};
    
    static uint32 tx_can2_Id[CAN_2_TX_MAX] = {0xC8FF8200U, 0xD8EA5100U, 0xD8EA5200U, 0xD8EAFF00U, \
                                              0xD9FE5100U, 0xD9FE5200U, 0xD9FE5300U, 0xD9FE5400U, \
                                              0xD9FE5500U, 0xD9FE5600U, 0xD9FE5700U, 0xD9FE5800U, \
                                              0xD9FE5900U, 0xD9FE6000U, 0xD9FE6100U, 0xD9FE6200U, \
                                              0xD9FE6300U, 0xD9FE6400U, 0xD9FE6500U, 0xD9FE7100U, \
                                              0xD9FE7200U, 0xD9FE7300U, 0xD9FE7400U, 0xD9FE7500U, \
                                              0xD8FEDF00U, 0xD8FFDC00U, 0xD8FF7600U, 0xD8FF6300U, \
                                              0xD4FF023DU, 0xD8FFEF00U, 0xD8FFF000U, 0xD8FF3100U, \
                                              0xCCFFC600U, 0xD8FF1000U};

    static uint32 tx_can3_Id[CAN_3_TX_MAX] = {0xD8DAF100U, 0x7A2U, 0x7A3U, 0x7A4U, 0x7A5U, \
                                              0x7A6U, 0x7A7U, 0x7A8U, 0x7A9U, 0x7AAU, \
											  0x7ABU, 0x7ACU, 0x7ADU, 0x7AEU};

    static uint32 tx_can4_Id[CAN_4_TX_MAX] = {0xC8FF8200U, 0xD8EA5100U, 0xD8EA5200U, 0xD8EAFF00U, \
                                              0xD9FE5100U, 0xD9FE5200U, 0xD9FE5300U, 0xD9FE5400U, \
                                              0xD9FE5500U, 0xD9FE5600U, 0xD9FE5700U, 0xD9FE5800U, \
                                              0xD9FE5900U, 0xD9FE6000U, 0xD9FE6100U, 0xD9FE6200U, \
                                              0xD9FE6300U, 0xD9FE6400U, 0xD9FE6500U, 0xD9FE7100U, \
                                              0xD9FE7200U, 0xD9FE7300U, 0xD9FE7400U, 0xD9FE7500U, \
                                              0xD8FEDF00U, 0xD8FFDC00U, 0xD8FF7600U, 0xD8FF6300U, \
                                              0xD4FF023DU, 0xD8FFEF00U, 0xD8FFF000U, 0xD8FF3100U, \
                                              0xCCFFC600U, 0xD8FF1000U};

    Can_PduType pduInfo_can_1;
    pduInfo_can_1.length = CAN_DLC;
    pduInfo_can_1.sdu = txBuffer_can_1;
    pduInfo_can_1.swPduHandle = 0;

    Can_PduType pduInfo_can_2;
    pduInfo_can_2.length = CAN_DLC;
    pduInfo_can_2.sdu = txBuffer_can_2;
    pduInfo_can_2.swPduHandle = 1;

    Can_PduType pduInfo_can_3;
    pduInfo_can_3.length = CAN_DLC;
    pduInfo_can_3.sdu = txBuffer_can_3;
    pduInfo_can_3.swPduHandle = 2;

    Can_PduType pduInfo_can_4;
    pduInfo_can_4.length = CAN_DLC;
    pduInfo_can_4.sdu = txBuffer_can_4;
    pduInfo_can_4.swPduHandle = 3;

    Std_ReturnType ret = 0U;
    uint32 index_can1 = 0U;
    uint32 index_can2 = 0U;
    uint32 index_can3 = 0U;
    uint32 index_can4 = 0U;

    while (index_can1 < CAN_1_TX_MAX || index_can2 < CAN_2_TX_MAX || index_can3 < CAN_3_TX_MAX || index_can4 < CAN_4_TX_MAX)
    {
        if (index_can1 < CAN_1_TX_MAX)
        {
            pduInfo_can_1.id = tx_can1_Id[index_can1];
            ret = Can_Write(TX_CAN1, &pduInfo_can_1);
            Gpt_Stm_LLD_DelayMs(STM1, 50U);
            PSPRINTF("CAN_0010 can1 ret[%d]\n", ret);
            if (ret == 0U)
            {
                index_can1++;
            }
        }

        if (index_can2 < CAN_2_TX_MAX)
        {
            pduInfo_can_2.id = tx_can2_Id[index_can2];
            ret = Can_Write(TX_CAN2, &pduInfo_can_2);
            Gpt_Stm_LLD_DelayMs(STM1, 50U);
            PSPRINTF("CAN_0010 can2 ret[%d]\n", ret);
            if (ret == 0U)
            {
                index_can2++;
            }
        }

        if (index_can3 < CAN_3_TX_MAX)
        {
            pduInfo_can_3.id = tx_can3_Id[index_can3];
            ret = Can_Write(TX_CAN3, &pduInfo_can_3);
            Gpt_Stm_LLD_DelayMs(STM1, 50U);
            PSPRINTF("CAN_0010 can3 ret[%d]\n", ret);
            if (ret == 0U)
            {
                index_can3++;
            }
        }

        if (index_can4 < CAN_4_TX_MAX)
        {
            pduInfo_can_4.id = tx_can4_Id[index_can4];
            ret = Can_Write(TX_CAN4, &pduInfo_can_4);
            Gpt_Stm_LLD_DelayMs(STM1, 50U);
            PSPRINTF("CAN_0010 can4 ret[%d]\n", ret);
            if (ret == 0U)
            {
                index_can4++;
            }
        }

        if (index_can1 >= CAN_1_TX_MAX)
        {
            index_can1 = 0;
        }
        
        if (index_can2 >= CAN_2_TX_MAX)
        {
            index_can2 = 0;
        }
        
        if (index_can3 >= CAN_3_TX_MAX)
        {
            index_can3= 0;
        }
        
        if (index_can4 >= CAN_4_TX_MAX)
        {
            index_can4 = 0;
        }
    }
#endif
}

int can_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }
    else
    {
        if (argc == 2)
        {
            if (!strcmp(agrv[1], "deinit")) 
            {
                Can_DeInit();
                PSPRINTF("Can_DeInit end!\n");
            }
            else if (!strcmp(agrv[1], "irq"))
            {
                CAN_IRQ_Priority();
            }
            else if (!strcmp(agrv[1], "stop"))
            {
                PSPRINTF("Please enter the number of the device you want to stop [1-5]!\n");
            }
            else if (!strcmp(agrv[1], "help"))
            {
                PSPRINTF("deinit ------- CMD ------- Can_DeInit()\n\
            irq ---------- CMD ------- Register/enable MCAN1 and MCAN2 interrupt numbers\n\
            stop --------- CMD ------- Migrate the module status to stop\n\
            [1 - %d] ----- CMD ------- ID of the test case\n", CAN_TEST_CASE_MAX);
            }
            else
            {
                uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if ((id >= 1) && (id <= CAN_TEST_CASE_MAX)) 
                {
                    if (can_funcs[id - 1].canfunc != NULL_PTR)
                    {
                        can_funcs[id - 1].canfunc();
                    }
                    else
                    {
                        PSPRINTF("error: The ID entered does not correspond to the test code\n");
                    }
                }
                else
                {
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, CAN_TEST_CASE_MAX);
                }
            }
        }
        else
        {
            if (!strcmp(agrv[1], "stop")) 
            {
                uint32 ControllerId = (uint32)atoi(agrv[2]);
                if ((ControllerId > CAN_CONTROLLER_COUNT) || (ControllerId < 1))
                {
                    PSPRINTF("error: Invalid parameter[%d], please enter the value of [1-5]!\n", ControllerId);
                }
                else
                {
                    if (McanController[ControllerId - 1] != 0xFF)
                    {
                        Can_SetControllerMode(McanController[ControllerId - 1], CAN_CS_STOPPED);
                    }
                    else
                    {
                        PSPRINTF("error: The corresponding MCAN%d device is not used!\n", ControllerId);
                    }
                }
            }
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), can_test, can_func, deint or number of test case);
