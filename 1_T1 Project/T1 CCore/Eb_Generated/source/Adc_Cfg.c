/* PRQA S 0380, 2053, 4342 EOF*/
/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : 
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Adc_Cfg.c
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Adc MCAL driver.
*
*   @addtogroup Adc
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "Adc.h"
#include "Adc_Irq.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/

#define ADC_PB_VENDOR_ID_C                 176
#define ADC_PB_AR_MAJOR_VER_C              4
#define ADC_PB_AR_MINOR_VER_C              4
#define ADC_PB_AR_PATCH_VER_C              0
#define ADC_PB_SW_MAJOR_VER_C              3
#define ADC_PB_SW_MINOR_VER_C              0
#define ADC_PB_SW_PATCH_VER_C              0

/*============================================FILE VERSION CHECKS===================================*/

#if (ADC_VENDOR_ID != ADC_PB_VENDOR_ID_C)
#error "NON-MATCHED DATA : ADC_PB_VENDOR_ID_C"
#endif

/* Check if current file and ADC header file are of the same Autosar version */
#if (ADC_AR_REL_MAJOR_VER != ADC_PB_AR_MAJOR_VER_C)
#error "NON-MATCHED DATA : ADC_PB_AR_MAJOR_VER_C"
#endif
#if (ADC_AR_REL_MINOR_VER != ADC_PB_AR_MINOR_VER_C)
#error "NON-MATCHED DATA : ADC_PB_AR_MINOR_VER_C"
#endif
#if (ADC_AR_REL_REV_VER != ADC_PB_AR_PATCH_VER_C)
#error "NON-MATCHED DATA : ADC_PB_AR_PATCH_VER_C"
#endif

/* Check if current file and ADC header file are of the same Software version */
#if (ADC_SW_MAJOR_VER != ADC_PB_SW_MAJOR_VER_C)
#error "NON-MATCHED DATA : ADC_PB_SW_MAJOR_VER_C"
#endif
#if (ADC_SW_MINOR_VER != ADC_PB_SW_MINOR_VER_C)
#error "NON-MATCHED DATA : ADC_PB_SW_MINOR_VER_C"
#endif
#if (ADC_SW_PATCH_VER != ADC_PB_SW_PATCH_VER_C)
#error "NON-MATCHED DATA : ADC_PB_SW_PATCH_VER_C"
#endif

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit0_Group0_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit0_Group0_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit0_Group0_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit0_Group0_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit0_Group1_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit0_Group1_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit0_Group1_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit0_Group1_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit1_Group2_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit1_Group2_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit1_Group2_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit1_Group2_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit1_Group3_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit1_Group3_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit1_Group3_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit1_Group3_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit2_Group4_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit2_Group4_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit2_Group4_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit2_Group4_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit2_Group5_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit2_Group5_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit2_Group5_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit2_Group5_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit3_Group6_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit3_Group6_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit3_Group6_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit3_Group6_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit3_Group7_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit3_Group7_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit3_Group7_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit3_Group7_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit4_Group8_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit4_Group8_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit4_Group8_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit4_Group8_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit4_Group9_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit4_Group9_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit4_Group9_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit4_Group9_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit5_Group10_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit5_Group10_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit5_Group10_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit5_Group10_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit5_Group11_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit5_Group11_CmdBuf[2] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit5_Group11_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit5_Group11_ResultBuf[2] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit6_Group12_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit6_Group12_CmdBuf[3] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit6_Group12_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit6_Group12_ResultBuf[3] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit6_Group13_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit6_Group13_CmdBuf[1] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit6_Group13_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit6_Group13_ResultBuf[1] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit7_Group14_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit7_Group14_CmdBuf[3] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit7_Group14_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit7_Group14_ResultBuf[3] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit7_Group15_CmdBuf(DMA buffer) */
VAR(uint32, ADC_VAR) HwUnit7_Group15_CmdBuf[1] = {0U};
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"
/* HwUnit7_Group15_ResultBuf(DMA buffer) */
VAR(uint16, ADC_VAR) HwUnit7_Group15_ResultBuf[1] = {0U};   
#define ADC_STOP_SEC_VAR_SHARED_INIT
#include "Adc_MemMap.h"



#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_0[2] =
{   
    /* group 0 channel index 0: ADC0_0_AN5_Current_U_L1 CH0 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 0U, */
        .ChanNum            = EQADC_CH0,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 0 channel index 1: ADC0_1_AN13_Current_W_L2 CH1 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 1U, */
        .ChanNum            = EQADC_CH1,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_0[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_1[2] =
{   
    /* group 1 channel index 0: ADC0_2_AN11_u_DC1_L1 CH2 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 2U, */
        .ChanNum            = EQADC_CH2,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 1 channel index 1: ADC0_5_AN6_Temp_IGBT_U CH5 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 5U, */
        .ChanNum            = EQADC_CH5,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_1[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_2[2] =
{   
    /* group 2 channel index 0: ADC1_8_AN7_Current_V_L1 CH8 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 8U, */
        .ChanNum            = EQADC_CH8,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 2 channel index 1: ADC1_9_AN12_Current_U_L2 CH9 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 9U, */
        .ChanNum            = EQADC_CH9,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_2[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_3[2] =
{   
    /* group 3 channel index 0: ADC1_10_AN10_Current_DC1_L1 CH10 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 10U, */
        .ChanNum            = EQADC_CH10,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 3 channel index 1: ADC_1_13_AN4_Temp_IGBT_V CH13 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 13U, */
        .ChanNum            = EQADC_CH13,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_3[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_4[2] =
{   
    /* group 4 channel index 0: ADC2_0_AN17_Current_W_L1 CH0 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 0U, */
        .ChanNum            = EQADC_CH0,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 4 channel index 1: ADC2_1_AN19_Current_V_L2 CH1 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 1U, */
        .ChanNum            = EQADC_CH1,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_4[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_5[2] =
{   
    /* group 5 channel index 0: ADC2_2_AN23_Temp_Motor0 CH2 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 2U, */
        .ChanNum            = EQADC_CH2,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 5 channel index 1: ADC2_3_AN29_Temp_IGBT_W CH3 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 3U, */
        .ChanNum            = EQADC_CH3,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_5[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_6[2] =
{   
    /* group 6 channel index 0: ADC3_4_AN27_Current_U2_L1 CH4 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 4U, */
        .ChanNum            = EQADC_CH4,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 6 channel index 1: ADC3_5_AN31_Current_W2_L2 CH5 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 5U, */
        .ChanNum            = EQADC_CH5,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_6[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_7[2] =
{   
    /* group 7 channel index 0: ADC3_8_AN16_u_DCK1_L1 CH8 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 8U, */
        .ChanNum            = EQADC_CH8,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 7 channel index 1: ADC3_9_AN18_Temp_IGBT_U2 CH9 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 9U, */
        .ChanNum            = EQADC_CH9,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_7[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_8[2] =
{   
    /* group 8 channel index 0: ADC4_0_AN33_Current_V2_L1 CH0 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 0U, */
        .ChanNum            = EQADC_CH0,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 8 channel index 1: ADC4_1_AN43_Current_U2_L2 CH1 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 1U, */
        .ChanNum            = EQADC_CH1,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_8[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_9[2] =
{   
    /* group 9 channel index 0: ADC4_2_AN41_Current_DC2_L1 CH2 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 2U, */
        .ChanNum            = EQADC_CH2,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 9 channel index 1: ADC4_3_AN35_eFuCurrent1_L1 CH3 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 3U, */
        .ChanNum            = EQADC_CH3,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_9[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_10[2] =
{   
    /* group 10 channel index 0: ADC5_1_AN36_Current_W2_L1 CH1 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 1U, */
        .ChanNum            = EQADC_CH1,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 10 channel index 1: ADC5_8_AN32_Temp_Motor1 CH8 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 8U, */
        .ChanNum            = EQADC_CH8,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_10[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_11[2] =
{   
    /* group 11 channel index 0: ADC5_8_AN32_Temp_Motor1 CH8 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 8U, */
        .ChanNum            = EQADC_CH8,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 11 channel index 1: ADC5_9_AN37_eFuCurrent2_L1 CH9 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_3,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 9U, */
        .ChanNum            = EQADC_CH9,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_11[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_12[3] =
{   
    /* group 12 channel index 0: ADC6_3_AN57_Decoding_cos_Positive CH3 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 3U, */
        .ChanNum            = EQADC_CH3,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 12 channel index 1: ADC6_4_AN50_Decoding_Exc_Positive CH4 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 4U, */
        .ChanNum            = EQADC_CH4,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 12 channel index 2: ADC6_4_AN50_Decoding_Exc_Positive CH4 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 4U, */
        .ChanNum            = EQADC_CH4,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_12[3] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_13[1] =
{   
    /* group 13 channel index 0: ADC6_5_AN48_eFuCurrent3_L1 CH5 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 5U, */
        .ChanNum            = EQADC_CH5,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_13[1] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_14[3] =
{   
    /* group 14 channel index 0: ADC7_8_AN58_Decoding_sin_Negative CH8 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 8U, */
        .ChanNum            = EQADC_CH8,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 14 channel index 1: ADC7_11_AN51_Decoding_cos_Negative CH11 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 11U, */
        .ChanNum            = EQADC_CH11,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 14 channel index 2: ADC7_12_AN56_Decoding_Exc_Negative CH12 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 12U, */
        .ChanNum            = EQADC_CH12,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_14[3] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_15[1] =
{   
    /* group 15 channel index 0: ADC7_13_AN49_eFuTemp CH13 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_2,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 13U, */
        .ChanNum            = EQADC_CH13,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_15[1] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_16[2] =
{   
    /* group 16 channel index 0: ADC8_1_AN74_u_DCK2_L1 CH1 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 1U, */
        .ChanNum            = EQADC_CH1,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 16 channel index 1: ADC8_9_AN75_AN_25V_Ref CH9 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)0U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_0,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 9U, */
        .ChanNum            = EQADC_CH9,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_16[2] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ConvCmdType, ADC_VAR) Eqadc_ConvCfg_17[8] =
{   
    /* group 17 channel index 0: ADC9_68_AN68_AD_IO1 CH68 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 68U, */
        .ChanNum            = EQADC_CH68,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 1: ADC9_69_AN69_AD_IO2 CH69 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 69U, */
        .ChanNum            = EQADC_CH69,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 2: ADC9_70_AN70_AD_IO3 CH70 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 70U, */
        .ChanNum            = EQADC_CH70,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 3: ADC9_71_AN71_AD_IO4 CH71 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 71U, */
        .ChanNum            = EQADC_CH71,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 4: ADC9_76_AN76_AN_KL30 CH76 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 76U, */
        .ChanNum            = EQADC_CH76,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 5: ADC9_77_AN77_Temp_Water0 CH77 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 77U, */
        .ChanNum            = EQADC_CH77,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 6: ADC9_78_AN78_Temp_Motor2 CH78 */
    {
        .Eoq                = FALSE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 78U, */
        .ChanNum            = EQADC_CH78,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
    /* group 17 channel index 7: ADC9_79_AN79_AN_15V_BK CH79 */
    {
        .Eoq                = TRUE,
        .Pause              = FALSE,
        .RepeatStart        = FALSE,
        .cBufNum            = (uint8)1U,
        .CalibConvResEn     = FALSE,
        .RfifoMsgTag        = EQADC_FIFO_1,
        .LongSampTime       = (Eqadc_LongSampTimeType)2U,
        .TimeStampReq       = FALSE,
        .FormatSignEn       = FALSE,
        /* 79U, */
        .ChanNum            = EQADC_CH79,
        .AltConfigSel       = EQADC_ALT_CONFIG_DISABLE,
        .FlushOrFMT         = FALSE
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Eqadc_ChannelLimitType, ADC_VAR) ChannelLimit_cfg_17[8] =
{
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
    {
        .RangeSelect =ADC_RANGE_ALWAYS,
        .LimitCheck =FALSE,
        .HighLimit =0U,
        .LowLimit =0U,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#endif

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Adc_GroupConfigType, ADC_VAR) Group_Cfg[18] =
{   
    /* Group 0, ADC0, HardWareTrig */
    {
        .HwUnitId = 0U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN1_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit0_Group0_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN0_NUMBER,
        .ResultIrq =&Eqadc0_DmaResult0,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit0_Group0_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_0,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_0,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_0,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 1, ADC0, HardWareTrig */
    {
        .HwUnitId = 0U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN3_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit0_Group1_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN2_NUMBER,
        .ResultIrq =&Eqadc0_DmaResult1,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit0_Group1_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_1,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_1,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_1,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 2, ADC1, HardWareTrig */
    {
        .HwUnitId = 1U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN5_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit1_Group2_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN4_NUMBER,
        .ResultIrq =&Eqadc0_DmaResult2,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit1_Group2_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_2,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_2,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_2,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 3, ADC1, HardWareTrig */
    {
        .HwUnitId = 1U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN7_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit1_Group3_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN6_NUMBER,
        .ResultIrq =&Eqadc0_DmaResult3,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit1_Group3_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_3,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_3,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_3,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 4, ADC2, HardWareTrig */
    {
        .HwUnitId = 2U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN17_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit2_Group4_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN16_NUMBER,
        .ResultIrq =&Eqadc1_DmaResult0,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit2_Group4_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_0,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_4,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_4,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 5, ADC2, HardWareTrig */
    {
        .HwUnitId = 2U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN19_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit2_Group5_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN18_NUMBER,
        .ResultIrq =&Eqadc1_DmaResult1,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit2_Group5_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_1,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG0,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_5,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_5,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 6, ADC3, HardWareTrig */
    {
        .HwUnitId = 3U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN21_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit3_Group6_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN20_NUMBER,
        .ResultIrq =&Eqadc1_DmaResult2,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit3_Group6_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_2,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_6,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_6,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 7, ADC3, HardWareTrig */
    {
        .HwUnitId = 3U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN23_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit3_Group7_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN22_NUMBER,
        .ResultIrq =&Eqadc1_DmaResult3,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit3_Group7_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_3,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_7,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_7,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 8, ADC4, HardWareTrig */
    {
        .HwUnitId = 4U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN25_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit4_Group8_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN24_NUMBER,
        .ResultIrq =&Eqadc2_DmaResult0,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit4_Group8_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_0,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_8,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_8,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 9, ADC4, HardWareTrig */
    {
        .HwUnitId = 4U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN27_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit4_Group9_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN26_NUMBER,
        .ResultIrq =&Eqadc2_DmaResult1,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit4_Group9_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_1,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_9,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_9,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 10, ADC5, HardWareTrig */
    {
        .HwUnitId = 5U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN29_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit5_Group10_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN28_NUMBER,
        .ResultIrq =&Eqadc2_DmaResult2,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit5_Group10_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_2,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_10,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_10,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 11, ADC5, HardWareTrig */
    {
        .HwUnitId = 5U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN31_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit5_Group11_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN30_NUMBER,
        .ResultIrq =&Eqadc2_DmaResult3,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit5_Group11_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_3,
        .HwTrigSrc =EQADC_HW_TRIG_ETRIG1,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_11,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_11,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 12, ADC6, HardWareTrig */
    {
        .HwUnitId = 6U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN33_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit6_Group12_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN32_NUMBER,
        .ResultIrq =&Eqadc3_DmaResult0,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit6_Group12_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 3U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_0,
        .HwTrigSrc =EQADC_HW_TRIG_EMIOS0_CH22,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_12,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_12,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 13, ADC6, SoftWareTrig */
    {
        .HwUnitId = 6U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN35_NUMBER,
        .DMACompleteClearERQ =TRUE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit6_Group13_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN34_NUMBER,
        .ResultIrq =&Eqadc3_DmaResult1,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit6_Group13_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_SW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_BOTH_EDGES,
        .StreamNumSamp =1U,
        .ChannelCount = 1U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_1,
        .HwTrigSrc =EQADC_HW_TRIG_NOT_CONNECTED,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_13,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_13,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 14, ADC7, HardWareTrig */
    {
        .HwUnitId = 7U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN37_NUMBER,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit7_Group14_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN36_NUMBER,
        .ResultIrq =&Eqadc3_DmaResult2,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit7_Group14_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_HW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 3U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_2,
        .HwTrigSrc =EQADC_HW_TRIG_EMIOS0_CH23,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_14,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_14,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 15, ADC7, SoftWareTrig */
    {
        .HwUnitId = 7U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)1U,
        .DmaMappedChan =EDMA_CHN39_NUMBER,
        .DMACompleteClearERQ =TRUE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =HwUnit7_Group15_CmdBuf,
        .ResultDmaMappedChan =EDMA_CHN38_NUMBER,
        .ResultIrq =&Eqadc3_DmaResult2,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =HwUnit7_Group15_ResultBuf,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_SW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_BOTH_EDGES,
        .StreamNumSamp =1U,
        .ChannelCount = 1U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_2,
        .HwTrigSrc =EQADC_HW_TRIG_NOT_CONNECTED,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_15,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_15,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 16, ADC8, SoftWareTrig */
    {
        .HwUnitId = 8U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)0U,
        .DmaMappedChan =0,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =NULL_PTR,
        .ResultDmaMappedChan =0,
        .ResultIrq =NULL_PTR,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =NULL_PTR,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_SW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_FALLING_EDGE,
        .StreamNumSamp =1U,
        .ChannelCount = 2U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_0,
        .HwTrigSrc =EQADC_HW_TRIG_NOT_CONNECTED,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_16,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_16,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
    /* Group 17, ADC9, SoftWareTrig */
    {
        .HwUnitId = 9U,
        .ExtTrigDigFilter = 0U,
        .Clk_Prescale = (Eqadc_ClkPrescaleType)1U,
        .ExtMuxEn =FALSE,
        .IntDma_Sel = (Eqadc_IntDmaFillSelType)0U,
        .DmaMappedChan =0,
        .DMACompleteClearERQ =FALSE,
        .Callback =NULL_PTR,
        .CallbackParam =NULL_PTR,
        .StrPtr =NULL_PTR,
        .ResultDmaMappedChan =0,
        .ResultIrq =NULL_PTR,
        .ResultCallback =NULL_PTR,
        .ResultCallbackParam =NULL_PTR,
        .DestPtr =NULL_PTR,
        .DmaSampleNum =1U,
        .SwOrHw = ADC_TRIGG_SRC_SW,
        .Prio = 0U,
        .ConvMode = ADC_CONV_MODE_ONESHOT,
        .StreamBufMode = ADC_STREAM_BUFFER_LINEAR,
        .AccessMode = ADC_ACCESS_MODE_SINGLE,
        .HwTriggerSignal = ADC_HW_TRIG_BOTH_EDGES,
        .StreamNumSamp =1U,
        .ChannelCount = 8U,
        .GroupNotif =NULL_PTR,
        .GroupNotif_OverFlow =NULL_PTR,
        .CFifo = EQADC_FIFO_1,
        .HwTrigSrc =EQADC_HW_TRIG_NOT_CONNECTED,
        .Resolution = ADC_RESOLUTION_BIT12,
        .Eqadc_ConvCmd = Eqadc_ConvCfg_17,
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        .Eqadc_ChannelLimit = ChannelLimit_cfg_17,
#endif
        .Adc_AlternatSet =NULL_PTR,
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
static CONST(Adc_CoreMapItemType, ADC_CONST) Adc_CoreMap[ADC_CONFIG_GROUPS]=
{
    {
        .GroupId = 0U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 1U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 2U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 3U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 4U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 5U,
        .GroupCoreId = 1U
    },
    {
        .GroupId = 6U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 7U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 8U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 9U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 10U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 11U,
        .GroupCoreId = 2U
    },
    {
        .GroupId = 12U,
        .GroupCoreId = 4U
    },
    {
        .GroupId = 13U,
        .GroupCoreId = 4U
    },
    {
        .GroupId = 14U,
        .GroupCoreId = 4U
    },
    {
        .GroupId = 15U,
        .GroupCoreId = 4U
    },
    {
        .GroupId = 16U,
        .GroupCoreId = 4U
    },
    {
        .GroupId = 17U,
        .GroupCoreId = 4U
    },
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
CONST(Adc_ConfigType, ADC_CONST) Adc_Config =
{
    .Adc_GroupConfig = Group_Cfg,
    .Adc_CoreMapItem = Adc_CoreMap
};
#define ADC_STOP_SEC_CONFIG_DATA
#include "Adc_MemMap.h"
#ifdef __cplusplus
}
#endif
