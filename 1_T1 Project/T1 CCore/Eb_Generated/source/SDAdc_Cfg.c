/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS, " AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     SDAdc_Cfg.c
* @version  3.0.0
* @date     2024 - 03 - 06
* @brief    Initial version.
*
*****************************************************************************/
/* PRQA S 0380,0704 EOF*/
#ifdef __cplusplus
extern "C"{
#endif

#include "SDAdc.h"

#define SDADC_CFG_C_VENDOR_ID                       176
#define SDADC_CFG_C_AR_REL_MAJOR_VER                4
#define SDADC_CFG_C_AR_REL_MINOR_VER                4
#define SDADC_CFG_C_AR_REL_REV_VER                  0
#define SDADC_CFG_C_SW_MAJOR_VER                    3
#define SDADC_CFG_C_SW_MINOR_VER                    0
#define SDADC_CFG_C_SW_PATCH_VER                    0

#if (SDADC_CFG_H_VENDOR_ID               != SDADC_CFG_C_VENDOR_ID)
    #error " NON-MATCHED DATA : SDADC_CFG_C_VENDOR_ID "
#endif
#if (SDADC_CFG_H_AR_REL_MAJOR_VER    != SDADC_CFG_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_AR_REL_MAJOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_MINOR_VER    != SDADC_CFG_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_AR_REL_MINOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_REV_VER != SDADC_CFG_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_AR_REL_REV_VER "
#endif
#if (SDADC_CFG_H_SW_MAJOR_VER        != SDADC_CFG_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_SW_MAJOR_VER "
#endif
#if (SDADC_CFG_H_SW_MINOR_VER        != SDADC_CFG_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_SW_MINOR_VER "
#endif
#if (SDADC_CFG_H_SW_PATCH_VER        != SDADC_CFG_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : SDADC_CFG_C_SW_PATCH_VER "
#endif



/* SDADC_CFG_CHANNEL_ID_0 */
#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
static CONST(Sdadc_ConfigType, SDADC_VAR) Sdadc_Config_0 = 
{
    .ChanSel            = {
        .ChanDefaultId          = 0U,
        .DifferenceEn           =TRUE
    },
    .ExtMeshClkSel      = SDADC_MESH_SEL_ADC_CORE, 
	.DCTestEn           =FALSE,
	.AnalogCfg          = {
			.PreGain = SDADC_PRE_GAIN_X1,
			.VcomSel = SDADC_VCOM_SEL_HALF_OF_VREF_H,
			.ClkDiv  = SDADC_CLK_DIV_1,
	},
	.OsrVal             = SDADC_OSR_64, 
    .FirFilter          = {
        .Fir1DecimationRate     = SDADC_FIR1_DECI_2_TO_1,
        .CicMode                =FALSE,
        .OvershootCompEn        =FALSE,
        .OffsetCompFilterEn     = SDADC_OFFSET_COMPENSATION_FILTER_DISABLED, 
        .CalibrationEn          =FALSE
    },
    .OvershootComp      = {
        .SlewRateFilterStrength = SDADC_SLEW_RATE_FILTER_STRENGTH_MAX,
        .SlewRateFilterRunTime  = SDADC_SLEW_RATE_FILTER_RUNTIME_16_IN_CYCLES,
        .StepDetectionMode      =  SDADC_STEP_DETECTION_MODE_LAST_INPUT,
        .StepDetectionThreshold = 0U    /*  <= 0x7FF */
    },
	.Res_P_En           =FALSE,
	.Res_N_En           =FALSE,
    .IntDma             = {
        .FifoWaterMarkerIntEn   =FALSE,
        .FifoOverFlowIntEn      = FALSE,
        .DataOverFlowIntEn      = FALSE,
        .DmaReqEn               =TRUE
    },
	.IntegratorEn       =FALSE,
    .Integrator         = {
        .IntegratorTrigMode     = SDADC_INTEGRATOR_TRIG_MODE_BYPASSED, 
        .IntegrationWindowSize  = SDADC_INTEGRATION_WINDOW_SIZE_INTERNAL_CTRL,
        .NumOfDiscardedVal      = 0U,
        .NumOfAccumulatedVal    = 0U, 
        .NumOfIntegrationCycles = 0U,
        .IntegratorShiftCtrl    = SDADC_INTEGRATOR_SHIFT_CTRL_SEL_BITS_4_20,  
        .FilterChainRestartCtrl = SDADC_FILTER_CHAIN_RESTART_ENABLE
    },
    .FilterChainDiscard = {
        .FilterChainDiscardEn   =TRUE,
        .FilterChainDiscardNum  = 0U 
    },
    .ChanWrap           = {
        .ChanWraparoundEn       =FALSE,
        .ChanWraparoundNum      = 0U 
    },
    .Comparator         = {
        .BoundaryComparatorEn   =FALSE,
        .LowerBoundary          = 0U, 
        .UpperBoundary          = 0U 
    },
    .FifoCfg            = {
        .FifoSize               = 64U,    /* Max(default) is 0x40 */
        .FifoWaterMarker        = 32U, 
        .InfoEn                 =FALSE,
        .SignEn                 =FALSE
    },
    .HwTrigSel          = {
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc0  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc1  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc2  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc3  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc4  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc5  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc6  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc7  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc8  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc9  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc10 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc11 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc12 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc13 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc14 */
        SDADC_HW_TRIG_DISABLE/* HwTrigSrc15 */
    },
    .DmaCfg             = {
        .DmaCh          = EDMA_CHN81_NUMBER,
        .DmaConfigPtr   =
		{
			.minorLpMap = 0U,
			.srcAddr = 0U,
			.destAddr = 0U,
			.srcTransDataSize = EDMA_TRANSFER_SIZE_4B,
			.destTransDataSize = EDMA_TRANSFER_SIZE_4B,
			.srcAddrOffset = (sint16)0U,
			.destAddrOffset = (sint16)0U,
			.srcAddrAdjustLast = (sint16)0U,
			.destAddrAdjustLast = (sint16)0U,
			.srcAddrModulo = EDMA_ADDRESS_MODULO_OFF,
			.destAddrModulo = EDMA_ADDRESS_MODULO_OFF,
			.minorTransByte = 0U,
			.featureScatterGatherEn = FALSE,
			.featureScatterGatherNextDescriptor = 0U,
			.completeIntEn = FALSE,
		},
		.DreqEn         =TRUE,
		.Callback       =NULL_PTR,
        .CallbackParam  = NULL_PTR
    }
};
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

/* SDADC_CFG_CHANNEL_ID_1 */
#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
static CONST(Sdadc_ConfigType, SDADC_VAR) Sdadc_Config_1 = 
{
    .ChanSel            = {
        .ChanDefaultId          = 0U,
        .DifferenceEn           =TRUE
    },
    .ExtMeshClkSel      = SDADC_MESH_SEL_ADC_CORE, 
	.DCTestEn           =FALSE,
	.AnalogCfg          = {
			.PreGain = SDADC_PRE_GAIN_X1,
			.VcomSel = SDADC_VCOM_SEL_HALF_OF_VREF_H,
			.ClkDiv  = SDADC_CLK_DIV_2,
	},
	.OsrVal             = SDADC_OSR_64, 
    .FirFilter          = {
        .Fir1DecimationRate     = SDADC_FIR1_DECI_2_TO_1,
        .CicMode                =FALSE,
        .OvershootCompEn        =FALSE,
        .OffsetCompFilterEn     = SDADC_OFFSET_COMPENSATION_FILTER_DISABLED, 
        .CalibrationEn          =FALSE
    },
    .OvershootComp      = {
        .SlewRateFilterStrength = SDADC_SLEW_RATE_FILTER_STRENGTH_MAX,
        .SlewRateFilterRunTime  = SDADC_SLEW_RATE_FILTER_RUNTIME_16_IN_CYCLES,
        .StepDetectionMode      =  SDADC_STEP_DETECTION_MODE_LAST_INPUT,
        .StepDetectionThreshold = 0U    /*  <= 0x7FF */
    },
	.Res_P_En           =FALSE,
	.Res_N_En           =FALSE,
    .IntDma             = {
        .FifoWaterMarkerIntEn   =FALSE,
        .FifoOverFlowIntEn      = FALSE,
        .DataOverFlowIntEn      = FALSE,
        .DmaReqEn               =TRUE
    },
	.IntegratorEn       =FALSE,
    .Integrator         = {
        .IntegratorTrigMode     = SDADC_INTEGRATOR_TRIG_MODE_BYPASSED, 
        .IntegrationWindowSize  = SDADC_INTEGRATION_WINDOW_SIZE_INTERNAL_CTRL,
        .NumOfDiscardedVal      = 0U,
        .NumOfAccumulatedVal    = 0U, 
        .NumOfIntegrationCycles = 0U,
        .IntegratorShiftCtrl    = SDADC_INTEGRATOR_SHIFT_CTRL_SEL_BITS_4_20,  
        .FilterChainRestartCtrl = SDADC_FILTER_CHAIN_RESTART_ENABLE
    },
    .FilterChainDiscard = {
        .FilterChainDiscardEn   =TRUE,
        .FilterChainDiscardNum  = 0U 
    },
    .ChanWrap           = {
        .ChanWraparoundEn       =FALSE,
        .ChanWraparoundNum      = 0U 
    },
    .Comparator         = {
        .BoundaryComparatorEn   =FALSE,
        .LowerBoundary          = 0U, 
        .UpperBoundary          = 0U 
    },
    .FifoCfg            = {
        .FifoSize               = 64U,    /* Max(default) is 0x40 */
        .FifoWaterMarker        = 32U, 
        .InfoEn                 =FALSE,
        .SignEn                 =FALSE
    },
    .HwTrigSel          = {
        SDADC_HW_TRIG_EDGE_BOTH,  /* HwTrigSrc0  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc1  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc2  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc3  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc4  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc5  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc6  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc7  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc8  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc9  */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc10 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc11 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc12 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc13 */
        SDADC_HW_TRIG_DISABLE,  /* HwTrigSrc14 */
        SDADC_HW_TRIG_DISABLE/* HwTrigSrc15 */
    },
    .DmaCfg             = {
        .DmaCh          = EDMA_CHN80_NUMBER,
        .DmaConfigPtr   =
		{
			.minorLpMap = 0U,
			.srcAddr = 0U,
			.destAddr = 0U,
			.srcTransDataSize = EDMA_TRANSFER_SIZE_4B,
			.destTransDataSize = EDMA_TRANSFER_SIZE_4B,
			.srcAddrOffset = (sint16)0U,
			.destAddrOffset = (sint16)0U,
			.srcAddrAdjustLast = (sint16)0U,
			.destAddrAdjustLast = (sint16)0U,
			.srcAddrModulo = EDMA_ADDRESS_MODULO_OFF,
			.destAddrModulo = EDMA_ADDRESS_MODULO_OFF,
			.minorTransByte = 0U,
			.featureScatterGatherEn = FALSE,
			.featureScatterGatherNextDescriptor = 0U,
			.completeIntEn = FALSE,
		},
		.DreqEn         =FALSE,
		.Callback       =&eDMA_SDADC_Notification,
        .CallbackParam  = NULL_PTR
    }
};
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
static CONST(SdAdc_InstanceConfigType, SDADC_VAR) SdAdc_InstanceConfig[2] =
{ 
    /* SDADC_CFG_CHANNEL_ID_0 */
	{
		.Sdadc_InstanceId = SDADC_INSTANCE_0, 
		.Sdadc_Config = &Sdadc_Config_0,
		.Sdadc_BufferMode = SDADC_STREAM_LINEAR_BUFFER,
        .Sdadc_ConvMethod = SDADC_USE_DMA,
		.Sdadc_NewResultNotify =NULL_PTR,
		.Sdadc_BufferFullNotifyPtr =NULL_PTR, 
		.Sdadc_SwOrHw = SOFTWARE_TRIG,
        .Sdadc_HwTrigSrc =NO_HWTRIG,
        .Sdadc_HwTrigRegId =SDADC_TRIGREG_DISABLE,
        .Sdadc_HwTrigChID =SDADC_TRIG_DEFAULT    
	},
    /* SDADC_CFG_CHANNEL_ID_1 */
	{
		.Sdadc_InstanceId = SDADC_INSTANCE_1, 
		.Sdadc_Config = &Sdadc_Config_1,
		.Sdadc_BufferMode = SDADC_STREAM_LINEAR_BUFFER,
        .Sdadc_ConvMethod = SDADC_USE_DMA,
		.Sdadc_NewResultNotify =NULL_PTR,
		.Sdadc_BufferFullNotifyPtr =NULL_PTR, 
		.Sdadc_SwOrHw = HARDWARE_TRIG,
        .Sdadc_HwTrigSrc =HWTRIGSEL_SDADC0,
        .Sdadc_HwTrigRegId =SDADC_TRIGREG_DISABLE,
        .Sdadc_HwTrigChID =SDADC_TRIG_DEFAULT    
	},
};
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
static CONST(SdAdc_CoreMapItemType, SDADC_CONST) SdAdc_CoreMap[SDADC_INSTANCE_CDG_NUM]=
{
    {
        .SdAdc_ChannelIndex = 0U,
        .SdAdc_CoreId = 1U
    },
    {
        .SdAdc_ChannelIndex = 1U,
        .SdAdc_CoreId = 1U
    },
};
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
CONST(SdAdc_TotalConfigType, SDADC_CONST) SdAdc_TotalConfig = 
{
    .SdAdc_InstanceConfig = SdAdc_InstanceConfig,
    .SdAdc_CoreMapItem = SdAdc_CoreMap
};
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

#ifdef __cplusplus
}
#endif
 
