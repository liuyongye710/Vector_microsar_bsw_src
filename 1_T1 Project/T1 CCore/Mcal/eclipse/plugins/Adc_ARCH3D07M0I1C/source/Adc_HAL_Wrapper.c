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
*   @file    Adc_HAL_Wrapper.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Adc MCAL driver.
*
*   @addtogroup Adc
*   @{
*/

/* PRQA S 0380, 1006, 3432 EOF */
/* PRQA S 2844, 0491, 2934, 2977, 2877, 2983, 2053, 3604 EOF */    /* QAC_CWE */

#ifdef __cplusplus
extern "C"{
#endif

#include "Adc_HAL_Wrapper.h"
#include "Adc_Irq.h"
#include "eDma.h"
#include "SchM_Adc.h"

#define ADC_HAL_WRA_C_VENDOR_ID                     176
#define ADC_HAL_WRA_C_AR_REL_MAJOR_VER              4
#define ADC_HAL_WRA_C_AR_REL_MINOR_VER              4
#define ADC_HAL_WRA_C_AR_REL_REV_VER                0
#define ADC_HAL_WRA_C_SW_MAJOR_VER                  3
#define ADC_HAL_WRA_C_SW_MINOR_VER                  0
#define ADC_HAL_WRA_C_SW_PATCH_VER                  0

#if (ADC_VENDOR_ID               != ADC_HAL_WRA_C_VENDOR_ID)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_VENDOR_ID "
#endif
#if (ADC_AR_REL_MAJOR_VER    != ADC_HAL_WRA_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_AR_REL_MAJOR_VER "
#endif
#if (ADC_AR_REL_MINOR_VER    != ADC_HAL_WRA_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_AR_REL_MINOR_VER "
#endif
#if (ADC_AR_REL_REV_VER != ADC_HAL_WRA_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_AR_REL_REV_VER "
#endif
#if (ADC_SW_MAJOR_VER        != ADC_HAL_WRA_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_SW_MAJOR_VER "
#endif
#if (ADC_SW_MINOR_VER        != ADC_HAL_WRA_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_SW_MINOR_VER "
#endif
#if (ADC_SW_PATCH_VER        != ADC_HAL_WRA_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : ADC_HAL_WRA_C_SW_PATCH_VER "
#endif

#define ADC_START_SEC_VAR_INIT
#include "Adc_MemMap.h"
static P2CONST(Adc_ConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_HAL_ConfigPtr[ADC_CORE_NUM] = {NULL};
#define ADC_STOP_SEC_VAR_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
static FUNC(uint8, ADC_CODE) EqAdc_GetAdcConfig \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    P2CONST(Adc_ConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_ConfigPtr, \
    P2VAR(Eqadc_AdcConfigTempType, ADC_CONST, ADC_APPL_CONST) pAdc_AdcConfigTemp
)
{
    VAR(Adc_GroupType, ADC_VAR) u16Adc_GroupId = 0U;
    VAR(uint8, AUTOMATIC) u8Adc_ConfigNum = 0U;
    VAR(boolean, ADC_VAR) bAdc_AdcId0flag = FALSE;
    VAR(boolean, ADC_VAR) bAdc_AdcId1flag = FALSE;
    VAR(EqadcAdcIdxType, AUTOMATIC) eAdc_Id;
    VAR(uint8, AUTOMATIC) u8Adc_Index = 0U;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
#if (ADC_ENABLE_MULTICORE == STD_ON)
    VAR(uint32, AUTOMATIC) CurrentCoreId = Adc_GetCoreID();
    VAR(uint8, AUTOMATIC) u8Adc_Coreflag = 0U;
#endif
    static VAR(Eqadc_AdcConfigType, ADC_VAR) sAdc_ConfigArray[ADC_CORE_NUM][EQADC_ADC_NUM];
    
    for(u16Adc_GroupId = 0; u16Adc_GroupId < ADC_CONFIG_GROUPS; u16Adc_GroupId++)
    {
#if (ADC_ENABLE_MULTICORE == STD_ON)
        u8Adc_Coreflag = (uint8)((CurrentCoreId) & (pAdc_ConfigPtr->Adc_CoreMapItem[u16Adc_GroupId].GroupCoreId));
        if((u8Adc_Coreflag != 0) && (sAdc_GroupState[u16Adc_GroupId] == ADC_GROUP_STATUS_UNINIT)
            && (sAdc_AdcHwInitState[pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId] == ADC_HW_STATUS_UNINIT))
        {
#endif
            if((pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId >= ((Adc_HwUnitType)u8Adc_Instance*(Adc_HwUnitType)2))/* polyspace RTE:NIV,IDP */
                && (pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId < (((Adc_HwUnitType)u8Adc_Instance+(Adc_HwUnitType)1)*(Adc_HwUnitType)2)))/* polyspace RTE:NIV */
            {
#if (ADC_ENABLE_MULTICORE == STD_ON)
                sAdc_GroupState[u16Adc_GroupId] = ADC_GROUP_STATUS_INITED;
                sAdc_AdcHwInitState[pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId] = ADC_HW_STATUS_INITED;
#endif
                if((pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId % (Adc_HwUnitType)2) == 0U)
                {
                    eAdc_Id = EQADC_ADC_0;
                }
                else
                {
                    eAdc_Id = EQADC_ADC_1;
                }
                if((pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId == ((Adc_HwUnitType)u8Adc_Instance*(Adc_HwUnitType)2)) && (bAdc_AdcId0flag == FALSE))
                {
                    sAdc_ConfigArray[u32Adc_ICoreId][0].AdcIdx = eAdc_Id;/* polyspace RTE:OBAI */
                    sAdc_ConfigArray[u32Adc_ICoreId][0].AdcExtMuxEn = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].ExtMuxEn;/* polyspace RTE:NIV */
                    sAdc_ConfigArray[u32Adc_ICoreId][0].TimeBaseSel = EQADC_TBS_INTERNAL;
                    sAdc_ConfigArray[u32Adc_ICoreId][0].ClkSel = EQADC_CLK_SEL_PS_DIV;
                    sAdc_ConfigArray[u32Adc_ICoreId][0].ClkPrescale = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].Clk_Prescale;/* polyspace RTE:NIV */
                    sAdc_ConfigArray[u32Adc_ICoreId][0].AdcGainCalibConst = 0x4000U;
                    sAdc_ConfigArray[u32Adc_ICoreId][0].AdcOffsetCalibConst = 0;
                    sAdc_ConfigArray[u32Adc_ICoreId][0].ImmediateConvCmdEn = FALSE;
                    bAdc_AdcId0flag = TRUE;
                    u8Adc_ConfigNum++;
                    u8Adc_Index = 0U;
                }
                if((pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].HwUnitId == (((Adc_HwUnitType)u8Adc_Instance*(Adc_HwUnitType)2)+(Adc_HwUnitType)1)) && (bAdc_AdcId1flag == FALSE))
                {
                    sAdc_ConfigArray[u32Adc_ICoreId][1].AdcIdx = eAdc_Id;/* polyspace RTE:OBAI */
                    sAdc_ConfigArray[u32Adc_ICoreId][1].AdcExtMuxEn = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].ExtMuxEn;/* polyspace RTE:NIV */
                    sAdc_ConfigArray[u32Adc_ICoreId][1].TimeBaseSel = EQADC_TBS_INTERNAL;
                    sAdc_ConfigArray[u32Adc_ICoreId][1].ClkSel = EQADC_CLK_SEL_PS_DIV;
                    sAdc_ConfigArray[u32Adc_ICoreId][1].ClkPrescale = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_GroupId].Clk_Prescale;/* polyspace RTE:NIV */
                    sAdc_ConfigArray[u32Adc_ICoreId][1].AdcGainCalibConst = 0x4000U;
                    sAdc_ConfigArray[u32Adc_ICoreId][1].AdcOffsetCalibConst = 0;
                    sAdc_ConfigArray[u32Adc_ICoreId][1].ImmediateConvCmdEn = FALSE;
                    bAdc_AdcId1flag = TRUE;
                    u8Adc_ConfigNum++;
                    u8Adc_Index = 1U;
                }
            }
            if(u8Adc_ConfigNum == 2U)
            {
                u8Adc_Index = 2U;
            }
#if (ADC_ENABLE_MULTICORE == STD_ON)
        }
#endif
    }
    pAdc_AdcConfigTemp->AdcConfigArray = sAdc_ConfigArray[u32Adc_ICoreId];
    pAdc_AdcConfigTemp->AdcConfigNum = u8Adc_ConfigNum;
    return u8Adc_Index;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) || (ADC_HW_TRIGGER_API == STD_ON)
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) EqAdc_GetCFiFoConfig \
(
    P2CONST(Adc_GroupConfigType, ADC_VAR, ADC_APPL_CONST) Adc_GroupConfig, \
    P2VAR(Eqadc_CfifoConfigType, ADC_VAR, ADC_APPL_CONST) pAdc_CfifoConfig
)
{
    pAdc_CfifoConfig->CfifoIdx = Adc_GroupConfig->CFifo;/* polyspace RTE:NIV */
    pAdc_CfifoConfig->CfifoMode = EQADC_CFIFO_MODE_DISABLE;
    pAdc_CfifoConfig->DmaChanDisReqOnTransComplete = Adc_GroupConfig->DMACompleteClearERQ;/* polyspace RTE:NIV */
    if(Adc_GroupConfig->IntDma_Sel == EQADC_FILL_SEL_DMA)/* polyspace RTE:NIV */
    {
        pAdc_CfifoConfig->IntDmaFillSel = EQADC_FILL_SEL_DMA;
    }
    else
    {
        pAdc_CfifoConfig->IntDmaFillSel = EQADC_FILL_SEL_INT;
    }
    if(Adc_GroupConfig->IntDma_Sel == EQADC_FILL_SEL_DMA)
    {
        pAdc_CfifoConfig->DmaMappedChan = Adc_GroupConfig->DmaMappedChan;/* polyspace RTE:NIV */
        pAdc_CfifoConfig->SourcePtr = Adc_GroupConfig->StrPtr;/* polyspace RTE:NIP */
        pAdc_CfifoConfig->SourceLen = (uint16)((Adc_GroupConfig->ChannelCount) * (Adc_GroupConfig->StreamNumSamp)  * (Adc_GroupConfig->DmaSampleNum));/* polyspace RTE:NIV,OVFL */
        pAdc_CfifoConfig->Callback = Adc_GroupConfig->Callback;/* polyspace RTE:NIP */
        pAdc_CfifoConfig->CallbackParam = Adc_GroupConfig->CallbackParam;/* polyspace RTE:NIP */
    }
    else
    {
        pAdc_CfifoConfig->DmaMappedChan = 0U;
        pAdc_CfifoConfig->SourcePtr = NULL;
        pAdc_CfifoConfig->SourceLen = 0U;
        pAdc_CfifoConfig->Callback = NULL;
        pAdc_CfifoConfig->CallbackParam = NULL;
    }
    pAdc_CfifoConfig->HwTrigSel = EQADC_HW_TRIG_NOT_CONNECTED;
    pAdc_CfifoConfig->Cfifo0EntryExtensionEn = 0U;
    pAdc_CfifoConfig->Cfifo0AdvanceMode = EQADC_CFIFO0_AMODE_DISABLE;
    pAdc_CfifoConfig->Cfifo0AdvanceTrigSel = EQADC_ADVANCE_TRIG_NOT;
    if(Adc_GroupConfig->SwOrHw == ADC_TRIGG_SRC_SW)/* polyspace RTE:NIV */
    {
        pAdc_CfifoConfig->HwTrigSel = EQADC_HW_TRIG_NOT_CONNECTED;
        if(Adc_GroupConfig->ConvMode == ADC_CONV_MODE_ONESHOT)/* polyspace RTE:NIV */
        {
            pAdc_CfifoConfig->CfifoMode    = (Eqadc_CfifoModeType)EQADC_CFIFO_MODE_SINGLE_SW_TRIG;
        }
        else if(Adc_GroupConfig->ConvMode == ADC_CONV_MODE_CONTINUOUS)
        {
            pAdc_CfifoConfig->CfifoMode = (Eqadc_CfifoModeType)EQADC_CFIFO_MODE_CONT_SW_TRIG;
        }
        else
        {
            /* No action */
        }
    }
#if (ADC_HW_TRIGGER_API == STD_ON)
    else if(Adc_GroupConfig->SwOrHw == ADC_TRIGG_SRC_HW)
    {
        pAdc_CfifoConfig->HwTrigSel = Adc_GroupConfig->HwTrigSrc;/* polyspace RTE:NIV */
        if(Adc_GroupConfig->HwTriggerSignal == ADC_HW_TRIG_RISING_EDGE)/* polyspace RTE:NIV */
        {
            pAdc_CfifoConfig->CfifoMode = (Eqadc_CfifoModeType)EQADC_CFIFO_MODE_CONT_RISING_EDGE_EXT_TRIG;
        }
        else if(Adc_GroupConfig->HwTriggerSignal == ADC_HW_TRIG_FALLING_EDGE)
        {
            pAdc_CfifoConfig->CfifoMode = (Eqadc_CfifoModeType)EQADC_CFIFO_MODE_CONT_FALLING_EDGE_EXT_TRIG;
        }
        else if(Adc_GroupConfig->HwTriggerSignal == ADC_HW_TRIG_BOTH_EDGES)
        {
            pAdc_CfifoConfig->CfifoMode = (Eqadc_CfifoModeType)EQADC_CFIFO_MODE_CONT_BOTH_EDGES_EXT_TRIG;
        }
        else
        {
            /* No action */
        }
    }
#endif
    else
    {
        /* No action */
    }
    return;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
ADC_INLINE FUNC(void, ADC_CODE) EqAdc_GetResultDmaConfig \
(
    P2CONST(Adc_GroupConfigType, ADC_VAR, ADC_APPL_CONST) Adc_GroupConfig, \
    P2VAR(Eqadc_ResultDmaConfigType, ADC_VAR, ADC_APPL_CONST) pAdc_ResultDmaConfig
)
{
    pAdc_ResultDmaConfig->RfifoIdx = Adc_GroupConfig->Eqadc_ConvCmd[0].RfifoMsgTag;/* polyspace RTE:NIV,NIP,IDP */
    pAdc_ResultDmaConfig->ResultDmaMappedChan = Adc_GroupConfig->ResultDmaMappedChan;/* polyspace RTE:NIV */
    pAdc_ResultDmaConfig->DestPtr = Adc_GroupConfig->DestPtr;/* polyspace RTE:NIP */
    pAdc_ResultDmaConfig->DestLen = (uint16)((Adc_GroupConfig->ChannelCount) * (Adc_GroupConfig->StreamNumSamp) * (Adc_GroupConfig->DmaSampleNum));/* polyspace RTE:NIV,OVFL */
    pAdc_ResultDmaConfig->Callback = Adc_GroupConfig->ResultIrq;/* polyspace RTE:NIP */
    pAdc_ResultDmaConfig->CallbackParam = Adc_GroupConfig->ResultCallbackParam;/* polyspace RTE:NIP */
    pAdc_ResultDmaConfig->EnHalfDestCallback = FALSE;
    return;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
ADC_INLINE FUNC(void, ADC_CODE) EqAdc_GetAlternateConfig \
(
    P2CONST(Adc_GroupConfigType, ADC_VAR, ADC_APPL_CONST) Adc_GroupConfig, \
    P2VAR(Eqadc_AlternateConfigType, ADC_VAR, ADC_APPL_CONST) pAdc_AlternateConfig
)
{
    VAR(Eqadc_ResolutionSelType, AUTOMATIC) eAdc_Resolution = EQADC_RES_SEL_12_BITS;

    pAdc_AlternateConfig->AltConfigSel = Adc_GroupConfig->Adc_AlternatSet->AltConfigSel;/* polyspace RTE:NIV,NIP,IDP */
    pAdc_AlternateConfig->ResultTransInhibit = Adc_GroupConfig->Adc_AlternatSet->ResultTransInhibit;/* polyspace RTE:NIV */
    pAdc_AlternateConfig->AltConvResultDEST = Adc_GroupConfig->Adc_AlternatSet->AltConvResultDEST;/* polyspace RTE:NIV */
    pAdc_AlternateConfig->FMTA_SignEn = Adc_GroupConfig->Adc_AlternatSet->FMTA_SignEn;/* polyspace RTE:NIV */
    if(Adc_GroupConfig->Resolution == ADC_RESOLUTION_BIT10)/* polyspace RTE:NIV */
    {
        eAdc_Resolution = EQADC_RES_SEL_10_BITS;
    }
    else if(Adc_GroupConfig->Resolution == ADC_RESOLUTION_BIT8)
    {
        eAdc_Resolution = EQADC_RES_SEL_8_BITS;
    }
    else
    {
        eAdc_Resolution = EQADC_RES_SEL_12_BITS;
    }
    pAdc_AlternateConfig->AdcResSel = eAdc_Resolution;
    pAdc_AlternateConfig->AdcPreGain = Adc_GroupConfig->Adc_AlternatSet->AdcPreGain;/* polyspace RTE:NIV */
    pAdc_AlternateConfig->AdcAltGain[0] = 0x4000U;     /*ADC0*/
    pAdc_AlternateConfig->AdcAltGain[1] = 0x4000U;     /*ADC1*/
    pAdc_AlternateConfig->AdcAltOffset[0] = 0x0000U; /*ADC0*/
    pAdc_AlternateConfig->AdcAltOffset[1] = 0x0000U; /*ADC1*/
    return;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
#endif  /* STD_ON == ADC_ENABLE_START_STOP_GROUP_API ADC_HW_TRIGGER_API == STD_ON*/

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_Init \
( \
    P2CONST(Adc_ConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_ConfigPtr \
) 
{
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    VAR(Adc_GroupType, ADC_VAR) u16Adc_CfgGroup = 0U;
    VAR(Adc_HwUnitType, ADC_VAR) u16Adc_UnitOfGroup = 0U;
    VAR(boolean, ADC_VAR) bAdc_AdcConfig_0 = FALSE;
    VAR(boolean, ADC_VAR) bAdc_AdcConfig_1 = FALSE;
    VAR(boolean, ADC_VAR) bAdc_AdcConfig_2 = FALSE;
    VAR(boolean, ADC_VAR) bAdc_AdcConfig_3 = FALSE;
    VAR(boolean, ADC_VAR) bAdc_AdcConfig_4 = FALSE;

    VAR(Eqadc_AdcConfigTempType, ADC_VAR) sAdc_AdcConfigTemp;
    VAR(uint8, AUTOMATIC) u8Adc_Index = 0U;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    static VAR(Adc_EqadcConfigType, ADC_VAR) sAdc_HAL_Eqadc_Cfg[ADC_CORE_NUM];
    static VAR(EqadcHwInstanceType, ADC_VAR) sAdc_EqadcHwInst[ADC_CORE_NUM];

    if(pAdc_ConfigPtr != NULL)
    {
        for(u16Adc_CfgGroup = 0; u16Adc_CfgGroup < ADC_CONFIG_GROUPS; u16Adc_CfgGroup++)
        {
            u16Adc_UnitOfGroup = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].HwUnitId;/* polyspace RTE:NIV,IDP */
            if(((u16Adc_UnitOfGroup == 0U) || (u16Adc_UnitOfGroup == 1U)) && (bAdc_AdcConfig_0 == FALSE))
            {
                sAdc_EqadcHwInst[u32Adc_ICoreId].Eqadc_HwInstId = EQADC_INSTANCE_0;/* polyspace RTE:OBAI */
                sAdc_EqadcHwInst[u32Adc_ICoreId].ExtTrigDigitalFilterLen = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].ExtTrigDigFilter;/* polyspace RTE:NIV */
                sAdc_EqadcHwInst[u32Adc_ICoreId].DebugModeEn = FALSE;
                sAdc_EqadcHwInst[u32Adc_ICoreId].TimeBasePresDiv = EQADC_TBC_CLK_PS_DISABLED;
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst = &sAdc_EqadcHwInst[u32Adc_ICoreId];

                u8Adc_Index = EqAdc_GetAdcConfig(0U, pAdc_ConfigPtr, &sAdc_AdcConfigTemp);
                if(sAdc_AdcConfigTemp.AdcConfigNum == 1U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = &sAdc_AdcConfigTemp.AdcConfigArray[u8Adc_Index];
                }
                else if(sAdc_AdcConfigTemp.AdcConfigNum == 2U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = sAdc_AdcConfigTemp.AdcConfigArray;
                }
                else
                {
                    /* No action */
                }
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigNum = sAdc_AdcConfigTemp.AdcConfigNum;

                bAdc_AdcConfig_0 = TRUE;
            }
            else if(((u16Adc_UnitOfGroup == 2U) || (u16Adc_UnitOfGroup == 3U)) && (bAdc_AdcConfig_1 == FALSE))
            {
                sAdc_EqadcHwInst[u32Adc_ICoreId].Eqadc_HwInstId = EQADC_INSTANCE_1;/* polyspace RTE:OBAI */
                sAdc_EqadcHwInst[u32Adc_ICoreId].ExtTrigDigitalFilterLen = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].ExtTrigDigFilter;/* polyspace RTE:NIV */
                sAdc_EqadcHwInst[u32Adc_ICoreId].DebugModeEn = FALSE;
                sAdc_EqadcHwInst[u32Adc_ICoreId].TimeBasePresDiv = EQADC_TBC_CLK_PS_DISABLED;
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst = &sAdc_EqadcHwInst[u32Adc_ICoreId];

                u8Adc_Index = EqAdc_GetAdcConfig(1U, pAdc_ConfigPtr, &sAdc_AdcConfigTemp);
                if(sAdc_AdcConfigTemp.AdcConfigNum == 1U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = &sAdc_AdcConfigTemp.AdcConfigArray[u8Adc_Index];
                }
                else if(sAdc_AdcConfigTemp.AdcConfigNum == 2U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = sAdc_AdcConfigTemp.AdcConfigArray;
                }
                else
                {
                    /* No action */
                }
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigNum = sAdc_AdcConfigTemp.AdcConfigNum;

                bAdc_AdcConfig_1 = TRUE;
            }
            else if(((u16Adc_UnitOfGroup == 4U) || (u16Adc_UnitOfGroup == 5U)) && (bAdc_AdcConfig_2 == FALSE))
            {
                sAdc_EqadcHwInst[u32Adc_ICoreId].Eqadc_HwInstId = EQADC_INSTANCE_2;/* polyspace RTE:OBAI */
                sAdc_EqadcHwInst[u32Adc_ICoreId].ExtTrigDigitalFilterLen = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].ExtTrigDigFilter;/* polyspace RTE:NIV */
                sAdc_EqadcHwInst[u32Adc_ICoreId].DebugModeEn = FALSE;
                sAdc_EqadcHwInst[u32Adc_ICoreId].TimeBasePresDiv = EQADC_TBC_CLK_PS_DISABLED;
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst = &sAdc_EqadcHwInst[u32Adc_ICoreId];

                u8Adc_Index = EqAdc_GetAdcConfig(2U, pAdc_ConfigPtr, &sAdc_AdcConfigTemp);
                if(sAdc_AdcConfigTemp.AdcConfigNum == 1U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = &sAdc_AdcConfigTemp.AdcConfigArray[u8Adc_Index];
                }
                else if(sAdc_AdcConfigTemp.AdcConfigNum == 2U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = sAdc_AdcConfigTemp.AdcConfigArray;
                }
                else
                {
                    /* No action */
                }
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigNum = sAdc_AdcConfigTemp.AdcConfigNum;

                bAdc_AdcConfig_2 = TRUE;
            }
            else if(((u16Adc_UnitOfGroup == 6U) || (u16Adc_UnitOfGroup == 7U)) && (bAdc_AdcConfig_3 == FALSE))
            {
                sAdc_EqadcHwInst[u32Adc_ICoreId].Eqadc_HwInstId = EQADC_INSTANCE_3;/* polyspace RTE:OBAI */
                sAdc_EqadcHwInst[u32Adc_ICoreId].ExtTrigDigitalFilterLen = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].ExtTrigDigFilter;/* polyspace RTE:NIV */
                sAdc_EqadcHwInst[u32Adc_ICoreId].DebugModeEn = FALSE;
                sAdc_EqadcHwInst[u32Adc_ICoreId].TimeBasePresDiv = EQADC_TBC_CLK_PS_DISABLED;
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst = &sAdc_EqadcHwInst[u32Adc_ICoreId];

                u8Adc_Index = EqAdc_GetAdcConfig(3U, pAdc_ConfigPtr, &sAdc_AdcConfigTemp);
                if(sAdc_AdcConfigTemp.AdcConfigNum == 1U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = &sAdc_AdcConfigTemp.AdcConfigArray[u8Adc_Index];
                }
                else if(sAdc_AdcConfigTemp.AdcConfigNum == 2U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = sAdc_AdcConfigTemp.AdcConfigArray;
                }
                else
                {
                    /* No action */
                }
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigNum = sAdc_AdcConfigTemp.AdcConfigNum;

                bAdc_AdcConfig_3 = TRUE;
            }
            else if(((u16Adc_UnitOfGroup == 8U) || (u16Adc_UnitOfGroup == 9U)) && (bAdc_AdcConfig_4 == FALSE))
            {
                sAdc_EqadcHwInst[u32Adc_ICoreId].Eqadc_HwInstId = EQADC_INSTANCE_4;/* polyspace RTE:OBAI */
                sAdc_EqadcHwInst[u32Adc_ICoreId].ExtTrigDigitalFilterLen = pAdc_ConfigPtr->Adc_GroupConfig[u16Adc_CfgGroup].ExtTrigDigFilter;/* polyspace RTE:NIV */
                sAdc_EqadcHwInst[u32Adc_ICoreId].DebugModeEn = FALSE;
                sAdc_EqadcHwInst[u32Adc_ICoreId].TimeBasePresDiv = EQADC_TBC_CLK_PS_DISABLED;
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst = &sAdc_EqadcHwInst[u32Adc_ICoreId];

                u8Adc_Index = EqAdc_GetAdcConfig(4U, pAdc_ConfigPtr, &sAdc_AdcConfigTemp);
                if(sAdc_AdcConfigTemp.AdcConfigNum == 1U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = &sAdc_AdcConfigTemp.AdcConfigArray[u8Adc_Index];
                }
                else if(sAdc_AdcConfigTemp.AdcConfigNum == 2U)
                {
                    sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigArray = sAdc_AdcConfigTemp.AdcConfigArray;
                }
                else
                {
                    /* No action */
                }
                sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AdcConfigNum = sAdc_AdcConfigTemp.AdcConfigNum;

                bAdc_AdcConfig_4 = TRUE;
            }
            else
            {
                /* No action */
            }

            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].CfifoConfigArray = NULL;/* polyspace RTE:OBAI */
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].CfifoConfigNum = 0U;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].ResultDmaConfigArray = NULL;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].ResultDmaConfigNum = 0U;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AlternateConfigNum = 0U;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].AlternateConfigArray = NULL;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].RedLineClientConfigNum = 0U;
            sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].RedLineClientConfigArray = NULL;


            SchM_Enter_ADC_EXCLUSIVE_AREA_24();
#if (ADC_ENABLE_MULTICORE == STD_ON)
            if(sAdc_AdcConfigTemp.AdcConfigNum != 0U)
            {
#endif
                Eqadc_LLD_Init(sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId].EqadcHwInst->Eqadc_HwInstId, &sAdc_HAL_Eqadc_Cfg[u32Adc_ICoreId]);/* polyspace RTE:IDP */
#if (ADC_ENABLE_MULTICORE == STD_ON)
            }
            
#endif
            SchM_Exit_ADC_EXCLUSIVE_AREA_24();
        }
        u8Adc_retVal = (Std_ReturnType)E_OK;
        pAdc_HAL_ConfigPtr[u32Adc_ICoreId] = pAdc_ConfigPtr;
    }
    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#if (STD_ON == ADC_DEINIT_API)
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_DeInit(void) 
{
    VAR(uint8, ADC_VAR) u8Adc_Instance = 0;
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    SchM_Enter_ADC_EXCLUSIVE_AREA_25();
    for (u8Adc_Instance = 0; u8Adc_Instance < ADC_EQADC_MAX_INSTANCE; u8Adc_Instance++)
    {
        Adc_Eqadc_LLD_DeInit((EqadcInstanceType)u8Adc_Instance); /* PRQA S 4342 */    /* QAC_CWE */
        u8Adc_retVal = (Std_ReturnType)E_OK;
    }
    SchM_Exit_ADC_EXCLUSIVE_AREA_25();
    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
#endif

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_StartGroupConversion \
( \
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_Group \
)
{
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_OK;
    VAR(Adc_HwUnitType, ADC_VAR) u16Adc_HwUnitId = 0U;
    VAR(EqadcInstanceType, ADC_VAR) eAdc_instance = EQADC_INSTANCE_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x = EQADC_FIFO_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Rfifo_x = EQADC_FIFO_0;
    VAR(Eqadc_CfifoConfigType, ADC_VAR) sAdc_CfifoConfig;
    VAR(Eqadc_ResultDmaConfigType, ADC_VAR) sAdc_ResultDmaConfig;
    VAR(Eqadc_AlternateConfigType, ADC_VAR) sAdc_AlternateConfig;
    VAR(Eqadc_ConvCmdType, ADC_VAR) sAdc_ConvCmdTemp;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    u16Adc_HwUnitId = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId;/* polyspace RTE:NIV,IDP,OBAI */
    if(u16Adc_HwUnitId < (Adc_HwUnitType)2U)
    {
        eAdc_instance = EQADC_INSTANCE_0;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)4U)
    {
        eAdc_instance = EQADC_INSTANCE_1;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)6U)
    {
        eAdc_instance = EQADC_INSTANCE_2;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)8U)
    {
        eAdc_instance = EQADC_INSTANCE_3;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)10U)
    {
        eAdc_instance = EQADC_INSTANCE_4;
    }
    else
    {
        u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    }

    if((Adc_HwUnitType)eAdc_instance == (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId/(Adc_HwUnitType)2))
    {
        eAdc_Cfifo_x = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo;/* polyspace RTE:NIV */
        eAdc_Rfifo_x = (EqadcFifoIdxType) \
                (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd->RfifoMsgTag);/* polyspace RTE:NIV,NIP,IDP */
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Adc_AlternatSet != NULL_PTR)/* polyspace RTE:NIP */
        {
            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_SINGLE_SW_TRIG);
            EqAdc_GetAlternateConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_AlternateConfig);
            Eqadc_SetAlternateConfig(eAdc_instance, eAdc_Cfifo_x, &sAdc_AlternateConfig);
        }
        EqAdc_GetCFiFoConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_CfifoConfig);
        (void)EQADC_SetCfifoConfig((uint8)eAdc_instance, &sAdc_CfifoConfig);
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_DMA)/* polyspace RTE:NIV,IDP */
        {
            EqAdc_GetResultDmaConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_ResultDmaConfig);
            sAdc_ResultDmaConfig.DestPtr = sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_Group].GroupResultBufferPtr;
            Eqadc_SetResultDmaConfig(eAdc_instance, &sAdc_ResultDmaConfig);
        }

        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_INT)/* polyspace RTE:NIV,IDP */
        {
            sAdc_ConvCmdTemp = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd[0];/* polyspace RTE:NIV,NIP,IDP */

            if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp != 1U)/* polyspace RTE:NIV */
            {
                sAdc_ConvCmdTemp.Eoq = FALSE;
            }
            Adc_gIrqMapping[u32Adc_ICoreId][((uint8)eAdc_instance * (uint8)EQADC_RFIFO_COUNT) + (uint8)eAdc_Rfifo_x] = u16Adc_Group;/* polyspace RTE:OBAI*/
            EQADC_LLD_CfifoPushConvCmd(eAdc_instance, eAdc_Cfifo_x, &sAdc_ConvCmdTemp);
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, TRUE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, TRUE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, TRUE);
#endif
            if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ConvMode == ADC_CONV_MODE_ONESHOT)/* polyspace RTE:NIV */
            {
                EQADC_LLD_SingleScanEn(eAdc_instance, eAdc_Cfifo_x);
            }

        }
        else if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_DMA)
        {
            Adc_gIrqMapping[u32Adc_ICoreId][((uint8)eAdc_instance * (uint8)EQADC_RFIFO_COUNT) + (uint8)eAdc_Rfifo_x] = u16Adc_Group;/* polyspace RTE:OBAI */
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, EQADC_IRQDMA_REQ_SEL_CFIFOFILL, TRUE);
            EQADC_LLD_DmaEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL, TRUE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IDCR0_RFDS1_MASK, TRUE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, TRUE);
            sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_Group].GroupResultIndex = (Adc_StreamNumSampleType)((pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ChannelCount) /* polyspace RTE:NIV */
                    * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp));/* polyspace RTE:NIV */
             EQADC_LLD_SetCQueueConvCmd(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd[0], /* polyspace RTE:NIV,NIP */
                     (uint8)((pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ChannelCount) * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp) /* polyspace RTE:NIV */
                    * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaSampleNum)), /* polyspace RTE:NIV,OVFL */
                     (uint8)pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp, pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaSampleNum, /* polyspace RTE:NIV */
                    pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StrPtr);/* polyspace RTE:NIV,NIP */
            (void) EDMA_SetChannelRequest(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaMappedChan);/* polyspace RTE:NIV,IDP */
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, TRUE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, TRUE);
#endif
            EQADC_LLD_SingleScanEn(eAdc_instance, eAdc_Cfifo_x);
        }
        else
        {
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, TRUE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, TRUE);
#endif
            sAdc_ConvCmdTemp = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd[0];/* polyspace RTE:NIV,NIP,IDP */

            if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp != 1U)/* polyspace RTE:NIV */
            {
                sAdc_ConvCmdTemp.Eoq = FALSE;
            }
            EQADC_LLD_CfifoPushConvCmd(eAdc_instance, eAdc_Cfifo_x, &sAdc_ConvCmdTemp);
            if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ConvMode == ADC_CONV_MODE_ONESHOT)/* polyspace RTE:NIV */
            {
                EQADC_LLD_SingleScanEn(eAdc_instance, eAdc_Cfifo_x);
            }
        }
    }
    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_StopGroupConversion \
( \
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_Group \
)
{
    VAR(uint16, ADC_VAR) u16Adc_IntDmaMask;
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_OK;
    VAR(Adc_HwUnitType, ADC_VAR) u16Adc_HwUnitId = 0U;
    VAR(EqadcInstanceType, ADC_VAR) eAdc_instance = EQADC_INSTANCE_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x = EQADC_FIFO_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Rfifo_x = EQADC_FIFO_0;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    u16Adc_HwUnitId = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId;/* polyspace RTE:NIV,IDP,OBAI */
    if(u16Adc_HwUnitId < (Adc_HwUnitType)2U)
    {
        eAdc_instance = EQADC_INSTANCE_0;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)4U)
    {
        eAdc_instance = EQADC_INSTANCE_1;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)6U)
    {
        eAdc_instance = EQADC_INSTANCE_2;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)8U)
    {
        eAdc_instance = EQADC_INSTANCE_3;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)10U)
    {
        eAdc_instance = EQADC_INSTANCE_4;
    }
    else
    {
        u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    }

    if((Adc_HwUnitType)eAdc_instance == (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId/(Adc_HwUnitType)2))
    {
        eAdc_Cfifo_x = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo;/* polyspace RTE:NIV */
        eAdc_Rfifo_x = (EqadcFifoIdxType)(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd->RfifoMsgTag);/* polyspace RTE:NIV,NIP,IDP */
            
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Adc_AlternatSet != NULL_PTR)/* polyspace RTE:NIP */
        {
            Eqadc_DeinitAlternateConfig(eAdc_instance, eAdc_Cfifo_x);
        }
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_INT)/* polyspace RTE:NIV */
        {
            u16Adc_IntDmaMask = (uint16)(EQADC_IRQ_EN_ALL \
                & ((uint16)~((uint16)(EQADC_IRQ_EN_RFIFO_OVERFLOW | EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN))));
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, FALSE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, FALSE);
#endif    
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, FALSE);
#endif
            for(uint32 i = 0U; i < 100000U; i++){}
            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_DISABLE);
            EQADC_CFCRxSetInvalidate((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x);
            while(EQADC_LLD_GetFifoFlagStatus(eAdc_instance, eAdc_Rfifo_x, EQADC_FISR_RFIFO_ENTRY_COUNT) != 0U)
            {
                (void)EQADC_LLD_RfifoPopData(eAdc_instance, eAdc_Rfifo_x);
            }

            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_RFIFO_DRAIN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_END_OF_QUEUE);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_CFIFO_UNDERFLOW);
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, u16Adc_IntDmaMask, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis \
            ( \
                (uint8)eAdc_instance, \
                (uint8)eAdc_Cfifo_x, \
                (uint16)EQADC_IRQDMA_REQ_SEL_CFIFOFILL, \
                FALSE \
            );

            EQADC_CFCRx_SetCfifoxEntryExtEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
            EQADC_CFCRx_SetAMode0((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO0_AMODE_DISABLE);
            EQADC_CFCR_CfifoStreamModeEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
        }
        else
        {
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IDCR0_RFDS1_MASK, FALSE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, FALSE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, FALSE);
#endif

            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, EQADC_IRQDMA_REQ_SEL_CFIFOFILL, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL, FALSE);

            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_DISABLE);
            EQADC_CFCRxSetInvalidate((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x);

            while(EQADC_LLD_GetFifoFlagStatus(eAdc_instance, eAdc_Rfifo_x, EQADC_FISR_RFIFO_ENTRY_COUNT) != 0U)
            {
                (void)EQADC_LLD_RfifoPopData(eAdc_instance, eAdc_Rfifo_x);
            }

            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_RFIFO_DRAIN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_CFIFO_UNDERFLOW);

            EQADC_CFCRx_SetCfifoxEntryExtEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
            EQADC_CFCRx_SetAMode0((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO0_AMODE_DISABLE);
            EQADC_CFCR_CfifoStreamModeEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
        }
    }

    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
#endif /* (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */
#if (STD_ON == ADC_HW_TRIGGER_API)
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_EnableHardwareTrigger \
( \
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_Group \
) 
{
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_OK;
    VAR(Adc_HwUnitType, ADC_VAR) u16Adc_HwUnitId = 0U;
    VAR(EqadcInstanceType, ADC_VAR) eAdc_instance = EQADC_INSTANCE_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x = EQADC_FIFO_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Rfifo_x = EQADC_FIFO_0;
    VAR(Eqadc_CfifoConfigType, ADC_VAR) sAdc_CfifoConfig;
    VAR(Eqadc_ResultDmaConfigType, ADC_VAR) sAdc_ResultDmaConfig;
    VAR(Eqadc_AlternateConfigType, ADC_VAR) sAdc_AlternateConfig;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    u16Adc_HwUnitId = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId;/* polyspace RTE:NIV,IDP,OBAI */
    VAR(Eqadc_ConvCmdType, ADC_VAR) sAdc_ConvCmdTemp = {0};
    if(u16Adc_HwUnitId < (Adc_HwUnitType)2U)
    {
        eAdc_instance = EQADC_INSTANCE_0;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)4U)
    {
        eAdc_instance = EQADC_INSTANCE_1;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)6U)
    {
        eAdc_instance = EQADC_INSTANCE_2;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)8U)
    {
        eAdc_instance = EQADC_INSTANCE_3;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)10U)
    {
        eAdc_instance = EQADC_INSTANCE_4;
    }
    else
    {
        u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    }

    if((Adc_HwUnitType)eAdc_instance == (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId/(Adc_HwUnitType)2))
    {
        SchM_Enter_ADC_EXCLUSIVE_AREA_28();
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Adc_AlternatSet != NULL_PTR)/* polyspace RTE:NIP */
        {
            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_SINGLE_SW_TRIG);
            EqAdc_GetAlternateConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_AlternateConfig);
            Eqadc_SetAlternateConfig(eAdc_instance, eAdc_Cfifo_x, &sAdc_AlternateConfig);
        }
        EqAdc_GetCFiFoConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_CfifoConfig);
        (void)EQADC_SetCfifoConfig((uint8)eAdc_instance, &sAdc_CfifoConfig);
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_DMA)/* polyspace RTE:NIV,IDP */
        {
            EqAdc_GetResultDmaConfig(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group], &sAdc_ResultDmaConfig);
            sAdc_ResultDmaConfig.DestPtr = sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_Group].GroupResultBufferPtr;
            Eqadc_SetResultDmaConfig(eAdc_instance, &sAdc_ResultDmaConfig);
        }
        eAdc_Cfifo_x = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo;/* polyspace RTE:NIV,IDP */
        eAdc_Rfifo_x = (EqadcFifoIdxType)(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd->RfifoMsgTag);/* polyspace RTE:NIV,NIP,IDP */
                
        EQADC_LLD_SingleScanEn(eAdc_instance, pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo);
        EQADC_LLD_SetCfifoHwTrigSource(eAdc_instance, pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo, \
                pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwTrigSrc);/* polyspace RTE:NIV */
        if(eAdc_Cfifo_x == EQADC_FIFO_0)
        {
            EQADC_LLD_SetCfifo0AdvanceTrigSource(eAdc_instance, sAdc_CfifoConfig.Cfifo0AdvanceTrigSel);
        }
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_INT)/* polyspace RTE:NIV */
        {
            sAdc_ConvCmdTemp = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd[0];/* polyspace RTE:NIV */

            if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp != 1U)/* polyspace RTE:NIV */
            {
                sAdc_ConvCmdTemp.Eoq = FALSE;
            }
            Adc_gIrqMapping[u32Adc_ICoreId][((uint8)eAdc_instance * (uint8)EQADC_RFIFO_COUNT) + (uint8)eAdc_Rfifo_x] = u16Adc_Group;/* polyspace RTE:OBAI */
            EQADC_LLD_CfifoPushConvCmd(eAdc_instance, eAdc_Cfifo_x, &sAdc_ConvCmdTemp);
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, TRUE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, TRUE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, TRUE);
#endif
        }
        else if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_DMA)
        {
            Adc_gIrqMapping[u32Adc_ICoreId][((uint8)eAdc_instance * (uint8)EQADC_RFIFO_COUNT) + (uint8)eAdc_Rfifo_x] = u16Adc_Group;/* polyspace RTE:OBAI */
            sAdc_RunningGroup[u32Adc_ICoreId][u16Adc_Group].GroupResultIndex = (Adc_StreamNumSampleType)((pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ChannelCount) /* polyspace RTE:NIV */
                    * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp));/* polyspace RTE:NIV */
            EQADC_LLD_SetCQueueConvCmd(&pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Eqadc_ConvCmd[0],  /* polyspace RTE:NIV */
                    (uint8)((pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].ChannelCount) * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp)/* polyspace RTE:NIV */
                    * (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaSampleNum)), /* polyspace RTE:NIV,OVFL */
                    (uint8)pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StreamNumSamp, pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaSampleNum, \
                    pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].StrPtr);/* polyspace RTE:NIV,NIP */
            (void) EDMA_SetChannelRequest(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].DmaMappedChan);/* polyspace RTE:NIV,IDP */
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, TRUE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, TRUE);
#endif
            EQADC_LLD_SingleScanEn(eAdc_instance, eAdc_Cfifo_x);
        }
        else
        {
            /* No action */
        }
        SchM_Exit_ADC_EXCLUSIVE_AREA_28();
    }

    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(Std_ReturnType, ADC_CODE) Adc_Wrapper_DisableHardwareTrigger \
( \
    VAR(Adc_GroupType, AUTOMATIC) u16Adc_Group \
)
{
    VAR(uint16, ADC_VAR) u16Adc_IntDmaMask;
    VAR(Std_ReturnType, ADC_VAR) u8Adc_retVal = (Std_ReturnType)E_OK;
    VAR(Std_ReturnType, ADC_VAR) u8Adc_SetCfifoTrigRet = (Std_ReturnType)E_OK;
    VAR(Adc_HwUnitType, ADC_VAR) u16Adc_HwUnitId = 0U;
    VAR(EqadcInstanceType, ADC_VAR) eAdc_instance = EQADC_INSTANCE_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x = EQADC_FIFO_0;
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Rfifo_x = EQADC_FIFO_0;
    VAR(uint32, AUTOMATIC) u32Adc_ICoreId = GetCoreID();
    u16Adc_HwUnitId = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId;/* polyspace RTE:NIV,IDP,OBAI */
    if(u16Adc_HwUnitId < (Adc_HwUnitType)2U)
    {
        eAdc_instance = EQADC_INSTANCE_0;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)4U)
    {
        eAdc_instance = EQADC_INSTANCE_1;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)6U)
    {
        eAdc_instance = EQADC_INSTANCE_2;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)8U)
    {
        eAdc_instance = EQADC_INSTANCE_3;
    }
    else if(u16Adc_HwUnitId < (Adc_HwUnitType)10U)
    {
        eAdc_instance = EQADC_INSTANCE_4;
    }
    else
    {
        u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
    }

    if((u8Adc_retVal == (Std_ReturnType)E_OK)
        && ((Adc_HwUnitType)eAdc_instance == (pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].HwUnitId/(Adc_HwUnitType)2)))
    {
        eAdc_Cfifo_x = pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].CFifo;/* polyspace RTE:NIV */
        eAdc_Rfifo_x = (EqadcFifoIdxType)(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].\
            Eqadc_ConvCmd->RfifoMsgTag);/* polyspace RTE:NIV,NIP,IDP */
        SchM_Enter_ADC_EXCLUSIVE_AREA_29();
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].Adc_AlternatSet != NULL_PTR)/* polyspace RTE:NIP */
        {
            Eqadc_DeinitAlternateConfig(eAdc_instance, eAdc_Cfifo_x);
        }
        if(pAdc_HAL_ConfigPtr[u32Adc_ICoreId]->Adc_GroupConfig[u16Adc_Group].IntDma_Sel == EQADC_FILL_SEL_INT)/* polyspace RTE:NIV */
        {
            u16Adc_IntDmaMask = (uint16)(EQADC_IRQ_EN_ALL \
                & ((uint16)~((uint16)(EQADC_IRQ_EN_RFIFO_OVERFLOW | EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN))));

            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, FALSE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, FALSE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, FALSE);
#endif

            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_DISABLE);
            EQADC_CFCRxSetInvalidate((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x);

            while(EQADC_LLD_GetFifoFlagStatus(eAdc_instance, eAdc_Rfifo_x, EQADC_FISR_RFIFO_ENTRY_COUNT) != 0U)
            {
                (void)EQADC_LLD_RfifoPopData(eAdc_instance, eAdc_Rfifo_x);
            }
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_CFIFO_UNDERFLOW);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_TRIG_OVERRUN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_RFIFO_DRAIN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_END_OF_QUEUE);


            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, u16Adc_IntDmaMask, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis \
            ( \
                (uint8)eAdc_instance, \
                (uint8)eAdc_Cfifo_x, \
                (uint16)EQADC_IRQDMA_REQ_SEL_CFIFOFILL, \
                FALSE \
            );
            u8Adc_SetCfifoTrigRet = EQADC_ISELx_SetCfifoTrig((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint8)EQADC_TRIG_NULL_VAL);
            if(u8Adc_SetCfifoTrigRet == (Std_ReturnType)E_NOT_OK)
            {
                u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
            }
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, u16Adc_IntDmaMask, FALSE);
            EQADC_CFCRx_SetAMode0((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO0_AMODE_DISABLE);
            EQADC_CFCR_CfifoStreamModeEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
            u8Adc_SetCfifoTrigRet = EQADC_ISELx_SetCfifo0AdvanceTrig((uint8)eAdc_instance, (uint8)EQADC_ATRIG_NULL_VALUE);
            if(u8Adc_SetCfifoTrigRet == (Std_ReturnType)E_NOT_OK)
            {
                u8Adc_retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Rfifo_x, EQADC_IDCR0_RFDS1_MASK, FALSE);
#if (ADC_INT_RFOF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Rfifo_x, EQADC_IRQ_EN_RFIFO_OVERFLOW, FALSE);
#endif
#if (ADC_INT_TORF_ENABLE ==  STD_ON)
            EQADC_LLD_IntEnDis(eAdc_instance, eAdc_Cfifo_x, EQADC_IRQ_EN_TRIGGER_OVERRUN, FALSE);
#endif

            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, EQADC_IRQDMA_REQ_SEL_CFIFOFILL, FALSE);
            EQADC_IDCRx_FifoIntDmaEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL, FALSE);

            EQADC_CFCRxSetMode((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO_MODE_DISABLE);
            EQADC_CFCRxSetInvalidate((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x);

            while(EQADC_LLD_GetFifoFlagStatus(eAdc_instance, eAdc_Rfifo_x, EQADC_FISR_RFIFO_ENTRY_COUNT) != 0U)
            {
                (void)EQADC_LLD_RfifoPopData(eAdc_instance, eAdc_Rfifo_x);
            }
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_RFIFO_DRAIN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Rfifo_x, EQADC_FIFO_FLAG_TRIG_OVERRUN);
            EQADC_LLD_ClearFifoIntFlag(eAdc_instance, eAdc_Cfifo_x, EQADC_FIFO_FLAG_CFIFO_UNDERFLOW);



            EQADC_CFCRx_SetCfifoxEntryExtEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
            EQADC_CFCRx_SetAMode0((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, (uint32)EQADC_CFIFO0_AMODE_DISABLE);
            EQADC_CFCR_CfifoStreamModeEnDis((uint8)eAdc_instance, (uint8)eAdc_Cfifo_x, FALSE);
        }
        SchM_Exit_ADC_EXCLUSIVE_AREA_29();
    }

    return u8Adc_retVal;
}
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */

#ifdef __cplusplus
}
#endif
