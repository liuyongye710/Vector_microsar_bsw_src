/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : Adc
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Adc_Irq.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Adc MCAL driver.
*
*   @addtogroup Adc
*   @{
*/

/* PRQA S 0380, 1006, 3432 EOF */
/* PRQA S 2844, 0491, 3604, 2983 EOF */    /* QAC_CWE */

#ifdef __cplusplus
extern "C"{
#endif

#define ADC_IRQ_C_VENDOR_ID                     176
#define ADC_IRQ_C_AR_REL_MAJOR_VER              4
#define ADC_IRQ_C_AR_REL_MINOR_VER              4
#define ADC_IRQ_C_AR_REL_REV_VER                0
#define ADC_IRQ_C_SW_MAJOR_VER                  3
#define ADC_IRQ_C_SW_MINOR_VER                  0
#define ADC_IRQ_C_SW_PATCH_VER                  0

#include "Adc_Irq.h"
#include "Adc_HAL_Wrapper.h"
#include "Adc_AutoSar_Wrapper.h"
#include "SchM_Adc.h"
#include"IoHwAb.h"
#if (ADC_VENDOR_ID               != ADC_IRQ_C_VENDOR_ID)
    #error " NON-MATCHED DATA : ADC_IRQ_C_VENDOR_ID "
#endif
#if (ADC_AR_REL_MAJOR_VER    != ADC_IRQ_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_AR_REL_MAJOR_VER "
#endif
#if (ADC_AR_REL_MINOR_VER    != ADC_IRQ_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_AR_REL_MINOR_VER "
#endif
#if (ADC_AR_REL_REV_VER != ADC_IRQ_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_AR_REL_REV_VER "
#endif
#if (ADC_SW_MAJOR_VER        != ADC_IRQ_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_SW_MAJOR_VER "
#endif
#if (ADC_SW_MINOR_VER        != ADC_IRQ_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_SW_MINOR_VER "
#endif
#if (ADC_SW_PATCH_VER        != ADC_IRQ_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : ADC_IRQ_C_SW_PATCH_VER "
#endif

#define ADC_START_SEC_VAR_INIT
#include "Adc_MemMap.h"
VAR(uint16, ADC_VAR) Adc_gIrqMapping[ADC_CORE_NUM][30U] = {{0}, {0}, {0}};
#define ADC_STOP_SEC_VAR_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA /* PRQA S 1514 */
#include "Adc_MemMap.h"
static CONSTP2VAR(EQADC_TagType, ADC_CONST, ADC_APPL_CONST) EqadcBase[ADC_EQADC_MAX_INSTANCE] = EQADC_BASE_PTR_ARRAY; /* PRQA S 3218 */
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) Update_GroupStatus(VAR(uint16, ADC_VAR) u16Adc_GroupId)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();

    if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupResultIndex /* polyspace RTE:OBAI,NIP */
        >= ((Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].StreamNumSamp) /* polyspace RTE:OBAI,NIP,NIV,IDP */
            * (Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ChannelCount)))/* polyspace RTE:OBAI,NIP,NIV */
    {
        sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupStatus = ADC_STREAM_COMPLETED;
    }

#if(STD_ON == ADC_ENABLE_QUEUING)
     Adc_SchedulerMain(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].HwUnitId);
#endif

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
    if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupSwitchNotifCall == ADC_GROUP_NOTIFICATION_ENABLED)
    {
        if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].GroupNotif != NULL_PTR)/* polyspace RTE:NIP */
        {
            Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].GroupNotif();/* polyspace RTE:COR */
        }
    }
#endif
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Adc_GetResultIrq \
( \
    VAR(EqadcInstanceType, AUTOMATIC) eAdc_instance, \
    VAR(EqadcFifoIdxType, AUTOMATIC) eAdc_Rfifo_x,\
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_GroupId \
)
{
    VAR(boolean, ADC_VAR) ConverFlag = FALSE;
    VAR(Eqadc_ConvCmdType, ADC_VAR) sAdc_ConvCmdTemp = {0};
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    CONSTP2VAR(EQADC_TagType, ADC_CONST, ADC_APPL_CONST) pAdc_BasePtr = EqadcBase[(uint8)eAdc_instance];
#if (ADC_ENABLE_MULTICORE == STD_ON)
    VAR(uint32, AUTOMATIC) CurrentCoreId = Adc_GetCoreID();
    VAR(uint8, AUTOMATIC) u8Adc_Coreflag = 0U;
    u8Adc_Coreflag = (uint8)((CurrentCoreId) & (Adc_ConfigPtr[u32Adc_ICoreId]->Adc_CoreMapItem[u16Adc_GroupId].GroupCoreId));
    if(u8Adc_Coreflag != 0)
    {
#endif
        SchM_Enter_ADC_CRITICAL_AREA_00();

        sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].StreamNumSamp++;/* polyspace RTE:OBAI */

        sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupResultBufferPtr[sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupResultIndex] /* polyspace RTE:IDP */
            = EQADC_LLD_RfifoPopData(eAdc_instance, eAdc_Rfifo_x);
        sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupResultIndex++;
        if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].IntDma_Sel != EQADC_FILL_NOT_INT)/* polyspace RTE:NIV,IDP */
        {
            pAdc_BasePtr->FISR[(uint8)eAdc_Rfifo_x].R = EQADC_FISR_RFDFX_MASK;/* polyspace RTE:OBAI */
        }
        
        if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupStatus == ADC_BUSY)
        {
            sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupStatus = ADC_COMPLETED;
        }

        if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].StreamNumSamp >= Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].StreamNumSamp)/* polyspace RTE:NIV */
        {
            sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].StreamNumSamp = 0U;
            sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].ChannelCount++;

            if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].ChannelCount >= Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ChannelCount)/* polyspace RTE:NIV */
            {
                //The conversion finished
                sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].ChannelCount = 0U;
                
                Update_GroupStatus(u16Adc_GroupId);
                if((Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ConvMode == ADC_CONV_MODE_CONTINUOUS)/* polyspace RTE:NIV */
                    || (Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].SwOrHw == ADC_TRIGG_SRC_HW))/* polyspace RTE:NIV */
                {
                    sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupResultIndex = 0U;
                }
                ConverFlag = TRUE;
            }
        }

        if(ConverFlag != TRUE)
        {
            sAdc_ConvCmdTemp = Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].Eqadc_ConvCmd[sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].ChannelCount];/* polyspace RTE:NIP,NIV,IDP */

            if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].StreamNumSamp != 1U)
            {
                if(((sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].StreamNumSamp + 1U) < Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].StreamNumSamp)
                    && (sAdc_ConvCmdTemp.Eoq == TRUE))
                {
                    sAdc_ConvCmdTemp.Eoq = FALSE;
                }
            }
            if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].IntDma_Sel != EQADC_FILL_NOT_INT)
            {
                pAdc_BasePtr->FISR[(uint8)eAdc_Rfifo_x].R = EQADC_FISR_RFDFX_MASK;/* polyspace RTE:OBAI */
            }
            EQADC_LLD_CfifoPushConvCmd(eAdc_instance, Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].CFifo, &sAdc_ConvCmdTemp);/* polyspace RTE:NIV */
        }

        if(((Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ConvMode == ADC_CONV_MODE_CONTINUOUS)/* polyspace RTE:NIV */
                || (Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].SwOrHw == ADC_TRIGG_SRC_HW)) && (ConverFlag == TRUE))/* polyspace RTE:NIV */
        {
            ConverFlag = FALSE;
            sAdc_ConvCmdTemp = Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].Eqadc_ConvCmd[0];/* polyspace RTE:NIP,NIV,IDP */

            if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].StreamNumSamp != 1U)
            {
                sAdc_ConvCmdTemp.Eoq = FALSE;
            }
            if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].IntDma_Sel != EQADC_FILL_NOT_INT)
            {
                pAdc_BasePtr->FISR[(uint8)eAdc_Rfifo_x].R = EQADC_FISR_RFDFX_MASK;/* polyspace RTE:OBAI */
            }
            EQADC_LLD_CfifoPushConvCmd(eAdc_instance, Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].CFifo, &sAdc_ConvCmdTemp);/* polyspace RTE:NIV */
        }
        SchM_Exit_ADC_CRITICAL_AREA_00();
#if (ADC_ENABLE_MULTICORE == STD_ON)
    }
#endif
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP0(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_0, Adc_gIrqMapping[u32Adc_ICoreId][0]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP1(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_1, Adc_gIrqMapping[u32Adc_ICoreId][1]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP2(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_2, Adc_gIrqMapping[u32Adc_ICoreId][2]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP3(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_3, Adc_gIrqMapping[u32Adc_ICoreId][3]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP4(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_4, Adc_gIrqMapping[u32Adc_ICoreId][4]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_GRP5(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_0, EQADC_FIFO_5, Adc_gIrqMapping[u32Adc_ICoreId][5]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP0(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_0, Adc_gIrqMapping[u32Adc_ICoreId][6]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP1(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_1, Adc_gIrqMapping[u32Adc_ICoreId][7]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP2(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_2, Adc_gIrqMapping[u32Adc_ICoreId][8]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP3(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_3, Adc_gIrqMapping[u32Adc_ICoreId][9]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP4(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_4, Adc_gIrqMapping[u32Adc_ICoreId][10]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_GRP5(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_1, EQADC_FIFO_5, Adc_gIrqMapping[u32Adc_ICoreId][11]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP0(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_0, Adc_gIrqMapping[u32Adc_ICoreId][12]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP1(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_1, Adc_gIrqMapping[u32Adc_ICoreId][13]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP2(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_2, Adc_gIrqMapping[u32Adc_ICoreId][14]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP3(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_3, Adc_gIrqMapping[u32Adc_ICoreId][15]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP4(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_4, Adc_gIrqMapping[u32Adc_ICoreId][16]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_GRP5(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_2, EQADC_FIFO_5, Adc_gIrqMapping[u32Adc_ICoreId][17]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP0(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_0, Adc_gIrqMapping[u32Adc_ICoreId][18]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP1(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_1, Adc_gIrqMapping[u32Adc_ICoreId][19]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP2(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_2, Adc_gIrqMapping[u32Adc_ICoreId][20]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP3(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_3, Adc_gIrqMapping[u32Adc_ICoreId][21]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP4(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_4, Adc_gIrqMapping[u32Adc_ICoreId][22]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_GRP5(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_3, EQADC_FIFO_5, Adc_gIrqMapping[u32Adc_ICoreId][23]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP0(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_0, Adc_gIrqMapping[u32Adc_ICoreId][24]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP1(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_1, Adc_gIrqMapping[u32Adc_ICoreId][25]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP2(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_2, Adc_gIrqMapping[u32Adc_ICoreId][26]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP3(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_3, Adc_gIrqMapping[u32Adc_ICoreId][27]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP4(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_4, Adc_gIrqMapping[u32Adc_ICoreId][28]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_GRP5(void)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Adc_GetResultIrq(EQADC_INSTANCE_4, EQADC_FIFO_5, Adc_gIrqMapping[u32Adc_ICoreId][29]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) Eqadc_DmaResult(VAR(Adc_GroupType, ADC_VAR) u16Adc_GroupId)
{
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Update_GroupStatus(u16Adc_GroupId);
    if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ResultCallback != NULL_PTR)/* polyspace RTE:NIP,IDP,OBAI */
    {
        Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ResultCallback /* polyspace RTE:COR */
        (
            Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ResultCallbackParam, /* polyspace RTE:NIP */
            EDMA_CHN_STATUS_NORMAL, \
            Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].ResultDmaMappedChan /* polyspace RTE:NIV */
        );
    }
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult0 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][0]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult1 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][1]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult2 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][2]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult3 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][3]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult4 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][4]);/* polyspace RTE:NIP,OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc0_DmaResult5 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][5]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult0 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][6]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult1 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][7]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult2 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][8]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult3 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][9]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult4 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][10]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc1_DmaResult5 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][11]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult0 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][12]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult1 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][13]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult2 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][14]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult3 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][15]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult4 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][16]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc2_DmaResult5 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][17]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult0 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][18]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult1 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][19]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult2 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][20]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult3 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][21]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult4 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][22]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc3_DmaResult5 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][23]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult0 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][24]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult1 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][25]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult2 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][26]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult3 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][27]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult4 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][28]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc4_DmaResult5 \
( \
    P2CONST(void,             AUTOMATIC, ADC_CODE) parameter, \
    VAR(eDMAChnStatusType,  AUTOMATIC) status, \
    VAR(uint8,              AUTOMATIC) mappedChannel \
)
{
    (void)parameter;
    (void)status;
    (void)mappedChannel;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    Eqadc_DmaResult(Adc_gIrqMapping[u32Adc_ICoreId][29]);/* polyspace RTE:OBAI */
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) Adc_OverFlowFunc(VAR(EqadcInstanceType, AUTOMATIC) eAdc_Instance)
{
#if (ADC_INT_RFOF_ENABLE ==  STD_ON) || (ADC_INT_TORF_ENABLE ==  STD_ON)
    CONSTP2VAR(EQADC_TagType, ADC_CONST, ADC_APPL_CONST) Adc_BasePTR[ADC_EQADC_MAX_INSTANCE] = EQADC_BASE_PTR_ARRAY;
#endif
    VAR(uint32, AUTOMATIC) FISR_RFOF_Value = 0U;
    VAR(uint32, AUTOMATIC) FISR_CFUF_Value = 0U;
    VAR(uint32, AUTOMATIC) FISR_TORF_Value = 0U;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID(); /* PRQA S 2983 */
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_GroupId = 0U; /* PRQA S 2983 */

#if (ADC_ENABLE_MULTICORE == STD_ON)
    VAR(uint32, AUTOMATIC) CurrentCoreId = Adc_GetCoreID();
    VAR(uint8, AUTOMATIC) u8Adc_Coreflag = 0U;
#endif
#else
    (void)eAdc_Instance;
#endif

    for(uint8 Fifo_Index = 0U; Fifo_Index < EQADC_RFIFO_COUNT; Fifo_Index++)
    {
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
        FISR_RFOF_Value = Adc_BasePTR[eAdc_Instance]->FISR[Fifo_Index].B.RFOFX;
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
        FISR_TORF_Value = Adc_BasePTR[eAdc_Instance]->FISR[Fifo_Index].B.TORFX;
#endif
        if((FISR_RFOF_Value == 1U) || (FISR_CFUF_Value == 1U) || (FISR_TORF_Value == 1U)) /* PRQA S 2992, 2996 */
        {
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_ClearFifoIntFlag(eAdc_Instance, (EqadcFifoIdxType)Fifo_Index, EQADC_FIFO_FLAG_RFIFO_OVERFLOW);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_ClearFifoIntFlag(eAdc_Instance, (EqadcFifoIdxType)Fifo_Index, EQADC_FIFO_FLAG_TRIG_OVERRUN);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            u16Adc_GroupId = Adc_gIrqMapping[u32Adc_ICoreId][((uint8)eAdc_Instance * EQADC_RFIFO_COUNT) + Fifo_Index];
#if (ADC_ENABLE_MULTICORE == STD_ON)
            u8Adc_Coreflag = (uint8)((CurrentCoreId) & (Adc_ConfigPtr[u32Adc_ICoreId]->Adc_CoreMapItem[u16Adc_GroupId].GroupCoreId));
            if(u8Adc_Coreflag != 0)
            {
#endif /* ADC_ENABLE_MULTICORE == STD_ON */
                SchM_Enter_ADC_EXCLUSIVE_AREA_12();
                if(sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_GroupId].GroupSwitchNotifCall == ADC_GROUP_NOTIFICATION_ENABLED)
                {
                    if(Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].GroupNotif_OverFlow != NULL_PTR)
                    {
                        Adc_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_GroupId].GroupNotif_OverFlow();
                    }
                }
                SchM_Exit_ADC_EXCLUSIVE_AREA_12();
#if (ADC_ENABLE_MULTICORE == STD_ON)
            }
#endif /* ADC_ENABLE_MULTICORE == STD_ON */
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */
        }
    }
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC01_FISR_Overflow(void)
{
    Adc_OverFlowFunc(EQADC_INSTANCE_0);
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC23_FISR_Overflow(void)
{
    Adc_OverFlowFunc(EQADC_INSTANCE_1);
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC45_FISR_Overflow(void)
{
    Adc_OverFlowFunc(EQADC_INSTANCE_2);
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC67_FISR_Overflow(void)
{
    Adc_OverFlowFunc(EQADC_INSTANCE_3);
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) ADC89_FISR_Overflow(void)
{
    Adc_OverFlowFunc(EQADC_INSTANCE_4);
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#ifdef __cplusplus
}
#endif
