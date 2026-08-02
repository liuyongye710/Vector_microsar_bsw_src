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
*   @file    Adc_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Adc MCAL driver.
*
*   @addtogroup Adc
*   @{
*/

#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "Mcal.h"
#include "eDma_LLDriver.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
#define ADC_VENDOR_ID                    176
#define ADC_AR_REL_MAJOR_VER             4
#define ADC_AR_REL_MINOR_VER             4
#define ADC_AR_REL_REV_VER               0
#define ADC_SW_MAJOR_VER                 3
#define ADC_SW_MINOR_VER                 0
#define ADC_SW_PATCH_VER                 0

#define ADC_MODULE_ID                    123

/*============================================FILE VERSION CHECKS===================================*/

#if (ADC_VENDOR_ID != MCAL_VENDOR_ID)
#error "NON-MATCHED DATA : MCAL_VENDOR_ID"
#endif

/* Check if current file and MCU header file are of the same Autosar version */
#if (ADC_AR_REL_MAJOR_VER != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "NON-MATCHED DATA : MCAL_AR_MAJOR_VER"
#endif
#if (ADC_AR_REL_MINOR_VER != MCAL_AR_RELEASE_MINOR_VERSION)
#error "NON-MATCHED DATA : MCAL_AR_MINOR_VER"
#endif
#if (ADC_AR_REL_REV_VER != MCAL_AR_RELEASE_REVISION_VERSION)
#error "NON-MATCHED DATA : MCAL_AR_PATCH_VER"
#endif

/* Check if current file and MCU header file are of the same Software version */
#if (ADC_SW_MAJOR_VER != MCAL_SW_MAJOR_VERSION)
#error "NON-MATCHED DATA : MCAL_SW_MAJOR_VER"
#endif
#if (ADC_SW_MINOR_VER != MCAL_SW_MINOR_VERSION)
#error "NON-MATCHED DATA : MCAL_SW_MINOR_VER"
#endif
#if (ADC_SW_PATCH_VER != MCAL_SW_PATCH_VERSION)
#error "NON-MATCHED DATA : MCAL_SW_PATCH_VER"
#endif


#define ADC_PRECOMPILE_SUPPORT     (STD_OFF)

#define ADC_DEINIT_API     (STD_ON)
#define ADC_DEV_ERROR_DETECT     (STD_ON)
#define ADC_ENABLE_LIMIT_CHECK     (STD_OFF)
#define ADC_ENABLE_QUEUING     (STD_OFF)
#define ADC_ENABLE_START_STOP_GROUP_API     (STD_ON)
#define ADC_GRP_NOTIF_CAPABILITY     (STD_OFF)
#define ADC_HW_TRIGGER_API     (STD_ON)
#define ADC_POWER_STATE_SUPPORTED     (STD_OFF)
#define ADC_POWER_STATE_ASYNCH_TRANSTION     (STD_OFF)
#define ADC_READ_GROUP_API     (STD_ON)
#define ADC_VERSION_INFO_API     (STD_ON)
#define ADC_ENABLE_MULTICORE     (STD_ON)
#define ADC_DEM_REPORT_ERROR_ENABLE     (STD_OFF)
#define ADC_INT_RFOF_ENABLE     (STD_OFF)
#define ADC_INT_TORF_ENABLE     (STD_OFF)
/*The inline switch is on*/
#define ADC_INLINE     LOCAL_INLINE



#define ADC_PRIORITY_IMPLEMENTATION (PRIORITY_NONE)

#define ADC_MAX_CHANNEL (8U)

#define ADC_MAX_GROUPS (2U)

#define ADC_CONFIG_GROUPS (18U)

#define ADC_CONFIG_UNIT (10U)

#define ADC_TIMEOUT (65535UL)

#define ADC_QUEUE_MAX_DEPTH (1U)

#define ADC_RESULT_ALIGNMENT (ADC_ALIGN_RIGHT) 

#define ADC_MAX_HW_UNITS (10U)

#define ADC_DEFAULT_COREID 2U

/** Specification of ADC Driver : [SWS_Adc_00099] **/
/* Number of channels per group configuration. */
#define ADC_GROUP_0_CHANNEL_NUM      2

/* The channel index 0 of group 0. */
#define GROUP_0_ADC0_0_AN5_Current_U_L1  0U

#define ADC_GROUP_0_ADC0_0_AN5_Current_U_L1  0U


/* The channel index 1 of group 0. */
#define GROUP_0_ADC0_1_AN13_Current_W_L2  1U

#define ADC_GROUP_0_ADC0_1_AN13_Current_W_L2  1U

#define ADC_GROUP_1_CHANNEL_NUM      2

/* The channel index 0 of group 1. */
#define GROUP_1_ADC0_2_AN11_u_DC1_L1  0U

#define ADC_GROUP_1_ADC0_2_AN11_u_DC1_L1  0U


/* The channel index 1 of group 1. */
#define GROUP_1_ADC0_5_AN6_Temp_IGBT_U  1U

#define ADC_GROUP_1_ADC0_5_AN6_Temp_IGBT_U  1U

#define ADC_GROUP_2_CHANNEL_NUM      2

/* The channel index 0 of group 2. */
#define GROUP_2_ADC1_8_AN7_Current_V_L1  0U

#define ADC_GROUP_2_ADC1_8_AN7_Current_V_L1  0U


/* The channel index 1 of group 2. */
#define GROUP_2_ADC1_9_AN12_Current_U_L2  1U

#define ADC_GROUP_2_ADC1_9_AN12_Current_U_L2  1U

#define ADC_GROUP_3_CHANNEL_NUM      2

/* The channel index 0 of group 3. */
#define GROUP_3_ADC1_10_AN10_Current_DC1_L1  0U

#define ADC_GROUP_3_ADC1_10_AN10_Current_DC1_L1  0U


/* The channel index 1 of group 3. */
#define GROUP_3_ADC_1_13_AN4_Temp_IGBT_V  1U

#define ADC_GROUP_3_ADC_1_13_AN4_Temp_IGBT_V  1U

#define ADC_GROUP_4_CHANNEL_NUM      2

/* The channel index 0 of group 4. */
#define GROUP_4_ADC2_0_AN17_Current_W_L1  0U

#define ADC_GROUP_4_ADC2_0_AN17_Current_W_L1  0U


/* The channel index 1 of group 4. */
#define GROUP_4_ADC2_1_AN19_Current_V_L2  1U

#define ADC_GROUP_4_ADC2_1_AN19_Current_V_L2  1U

#define ADC_GROUP_5_CHANNEL_NUM      2

/* The channel index 0 of group 5. */
#define GROUP_5_ADC2_2_AN23_Temp_Motor0  0U

#define ADC_GROUP_5_ADC2_2_AN23_Temp_Motor0  0U


/* The channel index 1 of group 5. */
#define GROUP_5_ADC2_3_AN29_Temp_IGBT_W  1U

#define ADC_GROUP_5_ADC2_3_AN29_Temp_IGBT_W  1U

#define ADC_GROUP_6_CHANNEL_NUM      2

/* The channel index 0 of group 6. */
#define GROUP_6_ADC3_4_AN27_Current_U2_L1  0U

#define ADC_GROUP_6_ADC3_4_AN27_Current_U2_L1  0U


/* The channel index 1 of group 6. */
#define GROUP_6_ADC3_5_AN31_Current_W2_L2  1U

#define ADC_GROUP_6_ADC3_5_AN31_Current_W2_L2  1U

#define ADC_GROUP_7_CHANNEL_NUM      2

/* The channel index 0 of group 7. */
#define GROUP_7_ADC3_8_AN16_u_DCK1_L1  0U

#define ADC_GROUP_7_ADC3_8_AN16_u_DCK1_L1  0U


/* The channel index 1 of group 7. */
#define GROUP_7_ADC3_9_AN18_Temp_IGBT_U2  1U

#define ADC_GROUP_7_ADC3_9_AN18_Temp_IGBT_U2  1U

#define ADC_GROUP_8_CHANNEL_NUM      2

/* The channel index 0 of group 8. */
#define GROUP_8_ADC4_0_AN33_Current_V2_L1  0U

#define ADC_GROUP_8_ADC4_0_AN33_Current_V2_L1  0U


/* The channel index 1 of group 8. */
#define GROUP_8_ADC4_1_AN43_Current_U2_L2  1U

#define ADC_GROUP_8_ADC4_1_AN43_Current_U2_L2  1U

#define ADC_GROUP_9_CHANNEL_NUM      2

/* The channel index 0 of group 9. */
#define GROUP_9_ADC4_2_AN41_Current_DC2_L1  0U

#define ADC_GROUP_9_ADC4_2_AN41_Current_DC2_L1  0U


/* The channel index 1 of group 9. */
#define GROUP_9_ADC4_3_AN35_eFuCurrent1_L1  1U

#define ADC_GROUP_9_ADC4_3_AN35_eFuCurrent1_L1  1U

#define ADC_GROUP_10_CHANNEL_NUM      2

/* The channel index 0 of group 10. */
#define GROUP_10_ADC5_1_AN36_Current_W2_L1  0U

#define ADC_GROUP_10_ADC5_1_AN36_Current_W2_L1  0U


/* The channel index 1 of group 10. */
#define GROUP_10_ADC5_8_AN32_Temp_Motor1  1U

#define ADC_GROUP_10_ADC5_8_AN32_Temp_Motor1  1U

#define ADC_GROUP_11_CHANNEL_NUM      2

/* The channel index 0 of group 11. */
#define GROUP_11_ADC5_8_AN32_Temp_Motor1  0U

#define ADC_GROUP_11_ADC5_8_AN32_Temp_Motor1  0U


/* The channel index 1 of group 11. */
#define GROUP_11_ADC5_9_AN37_eFuCurrent2_L1  1U

#define ADC_GROUP_11_ADC5_9_AN37_eFuCurrent2_L1  1U

#define ADC_GROUP_12_CHANNEL_NUM      3

/* The channel index 0 of group 12. */
#define GROUP_12_ADC6_3_AN57_Decoding_cos_Positive  0U

#define ADC_GROUP_12_ADC6_3_AN57_Decoding_cos_Positive  0U


/* The channel index 1 of group 12. */
#define GROUP_12_ADC6_4_AN50_Decoding_Exc_Positive  1U

#define ADC_GROUP_12_ADC6_4_AN50_Decoding_Exc_Positive  1U


/* The channel index 2 of group 12. */
#define GROUP_12_ADC6_4_AN50_Decoding_Exc_Positive  2U

#define ADC_GROUP_12_ADC6_4_AN50_Decoding_Exc_Positive  2U

#define ADC_GROUP_13_CHANNEL_NUM      1

/* The channel index 0 of group 13. */
#define GROUP_13_ADC6_5_AN48_eFuCurrent3_L1  0U

#define ADC_GROUP_13_ADC6_5_AN48_eFuCurrent3_L1  0U

#define ADC_GROUP_14_CHANNEL_NUM      3

/* The channel index 0 of group 14. */
#define GROUP_14_ADC7_8_AN58_Decoding_sin_Negative  0U

#define ADC_GROUP_14_ADC7_8_AN58_Decoding_sin_Negative  0U


/* The channel index 1 of group 14. */
#define GROUP_14_ADC7_11_AN51_Decoding_cos_Negative  1U

#define ADC_GROUP_14_ADC7_11_AN51_Decoding_cos_Negative  1U


/* The channel index 2 of group 14. */
#define GROUP_14_ADC7_12_AN56_Decoding_Exc_Negative  2U

#define ADC_GROUP_14_ADC7_12_AN56_Decoding_Exc_Negative  2U

#define ADC_GROUP_15_CHANNEL_NUM      1

/* The channel index 0 of group 15. */
#define GROUP_15_ADC7_13_AN49_eFuTemp  0U

#define ADC_GROUP_15_ADC7_13_AN49_eFuTemp  0U

#define ADC_GROUP_16_CHANNEL_NUM      2

/* The channel index 0 of group 16. */
#define GROUP_16_ADC8_1_AN74_u_DCK2_L1  0U

#define ADC_GROUP_16_ADC8_1_AN74_u_DCK2_L1  0U


/* The channel index 1 of group 16. */
#define GROUP_16_ADC8_9_AN75_AN_25V_Ref  1U

#define ADC_GROUP_16_ADC8_9_AN75_AN_25V_Ref  1U

#define ADC_GROUP_17_CHANNEL_NUM      8

/* The channel index 0 of group 17. */
#define GROUP_17_ADC9_68_AN68_AD_IO1  0U

#define ADC_GROUP_17_ADC9_68_AN68_AD_IO1  0U


/* The channel index 1 of group 17. */
#define GROUP_17_ADC9_69_AN69_AD_IO2  1U

#define ADC_GROUP_17_ADC9_69_AN69_AD_IO2  1U


/* The channel index 2 of group 17. */
#define GROUP_17_ADC9_70_AN70_AD_IO3  2U

#define ADC_GROUP_17_ADC9_70_AN70_AD_IO3  2U


/* The channel index 3 of group 17. */
#define GROUP_17_ADC9_71_AN71_AD_IO4  3U

#define ADC_GROUP_17_ADC9_71_AN71_AD_IO4  3U


/* The channel index 4 of group 17. */
#define GROUP_17_ADC9_76_AN76_AN_KL30  4U

#define ADC_GROUP_17_ADC9_76_AN76_AN_KL30  4U


/* The channel index 5 of group 17. */
#define GROUP_17_ADC9_77_AN77_Temp_Water0  5U

#define ADC_GROUP_17_ADC9_77_AN77_Temp_Water0  5U


/* The channel index 6 of group 17. */
#define GROUP_17_ADC9_78_AN78_Temp_Motor2  6U

#define ADC_GROUP_17_ADC9_78_AN78_Temp_Motor2  6U


/* The channel index 7 of group 17. */
#define GROUP_17_ADC9_79_AN79_AN_15V_BK  7U

#define ADC_GROUP_17_ADC9_79_AN79_AN_15V_BK  7U


/** Specification of ADC Driver : [SWS_Adc_00099] **/
/* The symbolic name of the group. */
#define ADC_GROUP_AdcGroup_Current1_U1_W2     0U
#define ADC_GROUP_AdcGroup0_10ms     1U
#define ADC_GROUP_AdcGroup_Current1_V1_U2     2U
#define ADC_GROUP_AdcGroup1_10ms     3U
#define ADC_GROUP_AdcGroup_Current1_W1_V2     4U
#define ADC_GROUP_AdcGroup2_10ms     5U
#define ADC_GROUP_AdcGroup_Current2_U1_W2     6U
#define ADC_GROUP_AdcGroup3_10ms     7U
#define ADC_GROUP_AdcGroup_Current2_V1_U2     8U
#define ADC_GROUP_AdcGroup4_10ms     9U
#define ADC_GROUP_AdcGroup_Current2_W1_V2     10U
#define ADC_GROUP_AdcGroup5_10ms     11U
#define ADC_GROUP_AdcGroup_RdcDiag_Pos     12U
#define ADC_GROUP_AdcGroup6_10ms     13U
#define ADC_GROUP_AdcGroup_RdcDiag_Neg     14U
#define ADC_GROUP_AdcGroup7_10ms     15U
#define ADC_GROUP_AdcGroup8_10ms     16U
#define ADC_GROUP_AdcGroup9_10ms     17U





#endif /* ADC_CFG_H */

/** @} */
