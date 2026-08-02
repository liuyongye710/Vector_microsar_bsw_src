/*PRQA S 0380,2053,1258,1259,0704,0686,4523 EOF*/
/****************************************************************************
*
* Copyright (c) 2022  C*Core -   All Rights Reserved
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
*   @file    Gpt_cfg.c
*   @implements     Gpt_cfg.c_Artifact
*   @version 3.0.0
*
*   @brief   AUTOSAR Gpt -  GPT driver configuration source file.
*   @details GPT driver source file, containing C and XPath constructs for generating Gpt
*            configuration source file for the Post-build configuration variant.
*
*   @addtogroup GPT_MODULE
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

#include "Gpt_Cfg.h"
#include "Gpt.h"
#include "Gpt_Rtc_LLDriver.h"

/*================================SOURCE FILE VERSION INFORMATION===================================*/
#define GPT_VENDOR_ID_OUTPUT                    176
#define GPT_CFG_AR_MAJOR_VER                    4
#define GPT_CFG_AR_MINOR_VER                    4
#define GPT_CFG_AR_PATCH_VER                    0 
#define GPT_CFG_SW_MAJOR_VER                    3
#define GPT_CFG_SW_MINOR_VER                    0
#define GPT_CFG_SW_PATCH_VER                    0
/*==================================FILE VERSION CHECKS=============================================*/
#if (MCAL_VENDOR_ID != GPT_VENDOR_ID_OUTPUT)
    #error " NON-MATCHED DATA : GPT_VENDOR_ID_OUTPUT "
#endif
#if (MCAL_AR_RELEASE_MAJOR_VERSION != GPT_CFG_AR_MAJOR_VER)
    #error " NON-MATCHED DATA : GPT_CFG_AR_MAJOR_VER "
#endif
#if (MCAL_AR_RELEASE_MINOR_VERSION != GPT_CFG_AR_MINOR_VER)
    #error " NON-MATCHED DATA : GPT_CFG_AR_MINOR_VER "
#endif
#if (MCAL_AR_RELEASE_REVISION_VERSION != GPT_CFG_AR_PATCH_VER)
    #error " NON-MATCHED DATA : GPT_CFG_AR_PATCH_VER "
#endif
#if (MCAL_SW_MAJOR_VERSION != GPT_CFG_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : GPT_CFG_SW_MAJOR_VER "
#endif
#if (MCAL_SW_MINOR_VERSION != GPT_CFG_SW_MINOR_VER)
    #error " NON-MATCHED DATA : GPT_CFG_SW_MINOR_VER "
#endif
#if (MCAL_SW_PATCH_VERSION != GPT_CFG_SW_PATCH_VER)
    #error " NON-MATCHED DATA : GPT_CFG_SW_PATCH_VER "
#endif

/*==================================LOCAL FUNCTION PROTOTYPES=======================================*/

/*======================================LOCAL MACROS================================================*/

/*=====================================LOCAL CONSTANTS==============================================*/

/*=====================================LOCAL VARIABLES==============================================*/

/*=====================================GLOBAL CONSTANTS=============================================*/




#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)

#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
static CONSTP2CONST(Gpt_HwPredefChannelConfig, GPT_CONST, GPT_APPL_CONST) Gpt_pInitPredefTimerChannel[GPT_HW_PREDEFTIMER_NUM]=
{
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 
#endif


#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
static CONST(Gpt_HwChannelConfig, GPT_CONST) Instance_InitHwChannel_0 =
{
    .u8HwChannel = (uint8)(PIT_0_CH_0), /* GPT physical channel no. */
    .eHwModule = (Gpt_Module)(GPT_MODULE_PIT), /* hardware module ID */
    .bFreezeEnable = (boolean)(FALSE), /* Freeze Enable */
    .u32GtmChannelRegCtrl1 = (uint32)0U, /* Not used for PIT */
#if (GPT_GTM_OUTPUT_ENABLE_MODE == STD_ON)
    .bGtmSupportEnableOutput = (boolean)FALSE, /* Not used for PIT */
#endif
    .u8StmPrescaler = (uint8)(0U), /* Not used for PIT */
    .u32ClkFreq = 80000000U,
    .eRtcClk = RTC_FIRC_CLK,
    .eRtcDiv = RTC_DIV512,
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 

#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
static CONST(Gpt_ChannelConfig, GPT_CONST) Gpt_InitChannel[1] =
{
        
    
        
    

    /*GptChannelConfiguration_0 configuration data*/
    {   
        .u8Instance = (0U), /* GPT instance */
        .bEnableWakeup = (boolean)TRUE, /* Wakeup capability */
        .pfNotification = (NULL_PTR), /* Channel notification */
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
        .uWakeupSource = (EcuM_WakeupSourceType)0U, /* Wakeup information */
#endif
        .uChannelTickValueMax = (Gpt_ValueType)(4294967295U), /* Maximum ticks value*/
        .eChannelMode = (Gpt_ChannelMode)(GPT_CH_MODE_CONTINUOUS), /* Timer mode:continous/one-shot */
        .pHwChannelConfig = &Instance_InitHwChannel_0
    },
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 

#if (GPT_ENABLE_MULTICORE == STD_ON)
#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
static CONST(Gpt_CoreMapItemType, GPT_CONST) Gpt_CoreMap[GPT_HW_CHANNEL_NUM]=
{
    {
        .u8HwChannel = 0,
        .u8CoreId = 4
    },
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 
#endif

#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet;
CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet =
{
    (Gpt_ChannelType)1U,
    &Gpt_InitChannel
#if (GPT_ENABLE_MULTICORE == STD_ON)
    ,Gpt_CoreMap
#endif
#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
    ,Gpt_pInitPredefTimerChannel
#endif
    /*Hardware to logic channel mapping.*/
    ,{
        
        GPT_CHN_NOT_USED,                        /*mapping of STM_0_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_0_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_0_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_0_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_1_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_1_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_1_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_1_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_2_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_2_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_2_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of STM_2_CH_3*/

        
        Gpt_GptChannelConfiguration_0,                        /*mapping of PIT_0_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_0_CH_RTI*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of PIT_1_CH_RTI*/

        
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_8*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_9*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_10*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_11*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_12*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_13*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_14*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_0_CH_15*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_8*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_9*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_10*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_11*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_12*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_13*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_14*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_1_CH_15*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_8*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_9*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_10*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_11*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_12*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_13*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_14*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_2_CH_15*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_8*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_9*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_10*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_11*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_12*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_13*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_14*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_3_CH_15*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_0*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_1*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_2*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_3*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_4*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_5*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_6*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_7*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_8*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_9*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_10*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_11*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_12*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_13*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_14*/
        GPT_CHN_NOT_USED,                        /*mapping of GTM_4_CH_15*/

        
        GPT_CHN_NOT_USED,                        /*mapping of RTC_0_CH_0*/

        
        GPT_CHN_NOT_USED                        /*mapping of API_0_CH_0*/
    }
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 

/**************************************** GTM CMU **************************************************/
#if(GPT_ENABLE_GTMCMU == STD_ON)

#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
static CONST(GPT_GTM_CMU_ClkConfigType, GPT_CONST) GtmCmu_clocks_Cfg[2] =
{
    /* for each configured clock */
        {
            /* CMU Clock ID */
            .clockId = (GPT_GTM_CMU_Clock_Type) (GPT_GTM_CMU_CLK0),
            /* CMU Clock control register */
            .clockControlRegister = (uint32) (
                                              ((0UL) << CMU_CLK_X_CTRL_CLK_CNT_OFFSET)
                                             )
        },
        {
            /* CMU Clock ID */
            .clockId = (GPT_GTM_CMU_Clock_Type) (GPT_GTM_CMU_CLK1),
            /* CMU Clock control register */
            .clockControlRegister = (uint32) (
                                              ((7UL) << CMU_CLK_X_CTRL_CLK_CNT_OFFSET)
                                             )
        }

};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 

#define GPT_START_SEC_CONFIG_DATA
#include "Gpt_MemMap.h"
CONST(Gpt_GtmCmuConfigType, GPT_CONST) Gpt_Gtm_Cmu_PBCfg;
CONST(Gpt_GtmCmuConfigType, GPT_CONST) Gpt_Gtm_Cmu_PBCfg =
{
      /* CMU configuration */
      {
          /* CMU Global Clock Control Numerator */
          .global_clock_numerator = (uint32) (1UL),
          /* CMU Global Clock Control Denominator */
          .global_clock_denominator = (uint32) (1UL),
          /* CMU clock enable register */
          .cmu_clk_control_register = (uint32)(
                    ( (CMU_CLK_EN_ENABLE_CLOCK)<<CMU_CLK_EN_EN_FXCLK_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_ECLK2_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_ECLK1_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_ECLK0_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK7_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK6_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK5_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK4_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK3_OFFSET)|
                    ( (CMU_CLK_EN_DISABLE_CLOCK)<<CMU_CLK_EN_EN_CLK2_OFFSET)|
                    ( (CMU_CLK_EN_ENABLE_CLOCK)<<CMU_CLK_EN_EN_CLK1_OFFSET)|
                    ( (CMU_CLK_EN_ENABLE_CLOCK)<<CMU_CLK_EN_EN_CLK0_OFFSET)
                  ),
          /* CMU FXCLK_Sel register */
          .cmu_fxclk_sel_register = (uint32)(CMU_FXCLK_CTRL_CMU_CLK1<<CMU_FXCLK_CTRL_FXCLK_SEL_OFFSET),
          /* number of clocks configured */
          .count_of_configured_clocks = (uint8)(2U),
          &GtmCmu_clocks_Cfg
      },

      /* TBU configuration */
      {
          /* TBU channel enable register */
          .tbu_channel0_enable_reg = (uint8)TBU_CHEN_DISABLE_CHANNEL,
          .tbu_channel1_enable_reg = (uint8)TBU_CHEN_DISABLE_CHANNEL,
          .tbu_channel2_enable_reg = (uint8)TBU_CHEN_DISABLE_CHANNEL,
          /* TBU channel 0 control */
          .tbu_ch0_control_clk_src = (uint8)0U,
          .tbu_ch0_control_low_res = (uint8)0U,
          /* TBU channel 1 control */
          .tbu_ch1_control_clk_src = (uint8)0U,
          .tbu_ch1_control_ch_mode = (uint8)0U,
          /* TBU channel 2 control */
          .tbu_ch2_control_clk_src = (uint8)0U,
          .tbu_ch2_control_ch_mode = (uint8)0U,

      }
};
#define GPT_STOP_SEC_CONFIG_DATA
#include "Gpt_MemMap.h" 

#endif

#ifdef __cplusplus
}
#endif

/** @} */
