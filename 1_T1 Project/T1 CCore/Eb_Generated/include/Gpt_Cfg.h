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
*   @file    Gpt_Cfg.h
*   @implements    Gpt_Cfg.h_Artifact
*   @version 3.0.0
*
*   @brief   AUTOSAR Gpt  - Gpt driver configuration header file.
*   @details GPT driver header file, containing C and XPath constructs for generating Gpt
*            configuration header file.
*
*   @addtogroup GPT_MODULE
*   @{
*/

#ifndef GPT_CFG_H
#define GPT_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "Mcal.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
#define GPT_VENDOR_ID                           176
#define GPT_CFG_AR_MAJOR_VER                    4
#define GPT_CFG_AR_MINOR_VER                    4
#define GPT_CFG_AR_PATCH_VER                    0
#define GPT_CFG_SW_MAJOR_VER                    3
#define GPT_CFG_SW_MINOR_VER                    0
#define GPT_CFG_SW_PATCH_VER                    0


/*============================================FILE VERSION CHECKS===================================*/
#if (MCAL_VENDOR_ID != GPT_VENDOR_ID)
    #error " NON-MATCHED DATA : GPT_VENDOR_ID "
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


/*=================================================Constants========================================*/

/*===========================================VARIABLE DECLARATIONS==================================*/

/*============================================DEFINES AND MACROS====================================*/
/* Error report support */
#define GPT_DEV_ERROR_DETECT                    (STD_OFF)
#define GPT_DEV_VALID_DETECT                    (GPT_DEV_ERROR_DETECT)

/*API support */
#define GPT_VERSION_INFO_API                    (STD_ON)

#define GPT_DEINIT_API                          (STD_ON)

#define GPT_TIME_ELAPSED_API                    (STD_ON)

#define GPT_TIME_REMAINING_API                  (STD_ON)

#define GPT_ENABLE_DISABLE_NOTIFICATION_API     (STD_ON)

#define GPT_WAKEUP_FUNCTIONALITY_API            (STD_ON)

#define GPT_PREDEFTIMER_FUNCTIONALITY_API       (STD_ON)

#define GPT_REPORT_WAKEUP_SOURCE                (STD_ON)

#define GPT_PIT_CHAIN_MODE                      (STD_OFF)

#define GPT_SET_CLOCK_MODE                      (STD_OFF)

#define GPT_CHANGE_NEXT_TIMEOUT_VALUE           (STD_OFF)

#define GPT_PRECOMPILE_SUPPORT                  (STD_OFF)

#define GPT_ENABLE_GTMCMU                       (STD_ON)

#define GPT_INLINE                              LOCAL_INLINE

#define GPT_ENABLE_MULTICORE                    (STD_OFF)


/* Used for GTM channel */
#define GPT_GTM_OUTPUT_ENABLE_MODE              (STD_OFF)

#define GPT_CHN_NOT_USED    (255U)

/* Define all GPT physical channel no */


#define GTM_0_CH_0                 0x0
#define GTM_0_CH_1                 0x1
#define GTM_0_CH_2                 0x2
#define GTM_0_CH_3                 0x3
#define GTM_0_CH_4                 0x4
#define GTM_0_CH_5                 0x5
#define GTM_0_CH_6                 0x6
#define GTM_0_CH_7                 0x7
#define GTM_0_CH_8                 0x8
#define GTM_0_CH_9                 0x9
#define GTM_0_CH_10                 0xa
#define GTM_0_CH_11                 0xb
#define GTM_0_CH_12                 0xc
#define GTM_0_CH_13                 0xd
#define GTM_0_CH_14                 0xe
#define GTM_0_CH_15                 0xf
#define GTM_1_CH_0                 0x20
#define GTM_1_CH_1                 0x21
#define GTM_1_CH_2                 0x22
#define GTM_1_CH_3                 0x23
#define GTM_1_CH_4                 0x24
#define GTM_1_CH_5                 0x25
#define GTM_1_CH_6                 0x26
#define GTM_1_CH_7                 0x27
#define GTM_1_CH_8                 0x28
#define GTM_1_CH_9                 0x29
#define GTM_1_CH_10                 0x2a
#define GTM_1_CH_11                 0x2b
#define GTM_1_CH_12                 0x2c
#define GTM_1_CH_13                 0x2d
#define GTM_1_CH_14                 0x2e
#define GTM_1_CH_15                 0x2f
#define GTM_2_CH_0                 0x40
#define GTM_2_CH_1                 0x41
#define GTM_2_CH_2                 0x42
#define GTM_2_CH_3                 0x43
#define GTM_2_CH_4                 0x44
#define GTM_2_CH_5                 0x45
#define GTM_2_CH_6                 0x46
#define GTM_2_CH_7                 0x47
#define GTM_2_CH_8                 0x48
#define GTM_2_CH_9                 0x49
#define GTM_2_CH_10                 0x4a
#define GTM_2_CH_11                 0x4b
#define GTM_2_CH_12                 0x4c
#define GTM_2_CH_13                 0x4d
#define GTM_2_CH_14                 0x4e
#define GTM_2_CH_15                 0x4f
#define GTM_3_CH_0                 0x60
#define GTM_3_CH_1                 0x61
#define GTM_3_CH_2                 0x62
#define GTM_3_CH_3                 0x63
#define GTM_3_CH_4                 0x64
#define GTM_3_CH_5                 0x65
#define GTM_3_CH_6                 0x66
#define GTM_3_CH_7                 0x67
#define GTM_3_CH_8                 0x68
#define GTM_3_CH_9                 0x69
#define GTM_3_CH_10                 0x6a
#define GTM_3_CH_11                 0x6b
#define GTM_3_CH_12                 0x6c
#define GTM_3_CH_13                 0x6d
#define GTM_3_CH_14                 0x6e
#define GTM_3_CH_15                 0x6f
#define GTM_4_CH_0                 0x80
#define GTM_4_CH_1                 0x81
#define GTM_4_CH_2                 0x82
#define GTM_4_CH_3                 0x83
#define GTM_4_CH_4                 0x84
#define GTM_4_CH_5                 0x85
#define GTM_4_CH_6                 0x86
#define GTM_4_CH_7                 0x87
#define GTM_4_CH_8                 0x88
#define GTM_4_CH_9                 0x89
#define GTM_4_CH_10                 0x8a
#define GTM_4_CH_11                 0x8b
#define GTM_4_CH_12                 0x8c
#define GTM_4_CH_13                 0x8d
#define GTM_4_CH_14                 0x8e
#define GTM_4_CH_15                 0x8f
#define PIT_0_CH_RTI                 0x8
#define PIT_0_CH_0                 0x0
#define PIT_0_CH_1                 0x1
#define PIT_0_CH_2                 0x2
#define PIT_0_CH_3                 0x3
#define PIT_0_CH_4                 0x4
#define PIT_0_CH_5                 0x5
#define PIT_0_CH_6                 0x6
#define PIT_0_CH_7                 0x7
#define PIT_1_CH_0                 0x10
#define PIT_1_CH_1                 0x11
#define STM_0_CH_0                 0x0
#define STM_0_CH_1                 0x1
#define STM_0_CH_2                 0x2
#define STM_0_CH_3                 0x3
#define STM_1_CH_0                 0x10
#define STM_1_CH_1                 0x11
#define STM_1_CH_2                 0x12
#define STM_1_CH_3                 0x13
#define STM_2_CH_0                 0x20
#define STM_2_CH_1                 0x21
#define STM_2_CH_2                 0x22
#define STM_2_CH_3                 0x23
#define RTC_0_CH_0                 0x0U
#define API_0_CH_0				   0x1U

/* Config all GPT channel number */

#define GPT_HW_CHANNEL_NUM                      (1U)
        
#define GPT_HW_PREDEFTIMER_NUM                  (4U)
/* retry times */
#define GPT_RETRY_TIMEOUT_COUNTER               (10UL)

#define GPT_DEFAULT_COREID                      2U

#define GPT_STM_MODULE_INDEX        (0U)      /* index where the STM channels start*/
#define GPT_PIT_MODULE_INDEX        (12U)     /* index where the PIT channels start*/
#define GPT_GTM_MODULE_INDEX        (30U)     /* index where the GTM channels start*/
#define GPT_RTC_MODULE_INDEX        (110U)    /* index where the RTC channels start*/
#define GPT_API_MODULE_INDEX        (111U)    /* index where the API channels start*/

#define GPT_CHANNEL_IDX_NUM    (120U)



#define GptChannelConfiguration_0                           (Gpt_GptChannelConfiguration_0)

#define Gpt_GptChannelConfiguration_0                        ((Gpt_ChannelType)0U) 


/*===================================================ENUMS==========================================*/

/*=======================================STRUCTURES AND OTHER TYPEDEFS==============================*/

/*===============================================LOCAL FUNCTIONS====================================*/

/*==============================================GLOBAL FUNCTIONS====================================*/

#ifdef __cplusplus
}
#endif

#endif  /* GPT_CFG_H */

/** @} */
