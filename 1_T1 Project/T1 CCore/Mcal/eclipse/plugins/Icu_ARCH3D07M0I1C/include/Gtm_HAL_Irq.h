/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC 
*   Peripheral           : ICU
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
*   @file    Gtm_HAL_Irq.h
*   @version 3.0.0 
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Icu MCAL driver.
*
*   @addtogroup Icu
*   @{
*/
#ifndef GTM_HAL_IRQ_H
#define GTM_HAL_IRQ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*====================================================================================================
                                        INCLUDE FILES
====================================================================================================*/
#include "Icu_Irq.h"
#include "Icu.h"
#include "Icu_Gtm_Tim_LLDrivers.h"

/*====================================================================================================
                                SOURCE FILE VERSION INFORMATION
====================================================================================================*/

/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define GTM_HAL_IRQ_VENDOR_ID_H                   176

#define GTM_HAL_IRQ_MAJOR_VER_H                   4
#define GTM_HAL_IRQ_MINOR_VER_H                   4
#define GTM_HAL_IRQ_REVISION_VER_H                0

#define GTM_HAL_IRQ_SW_MAJOR_VER_H                3
#define GTM_HAL_IRQ_SW_MINOR_VER_H                0
#define GTM_HAL_IRQ_SW_PATCH_VER_H                0

#if (GTM_HAL_IRQ_VENDOR_ID_H != ICU_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (GTM_HAL_IRQ_MAJOR_VER_H != ICU_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (GTM_HAL_IRQ_MINOR_VER_H != ICU_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (GTM_HAL_IRQ_REVISION_VER_H != ICU_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (GTM_HAL_IRQ_SW_MAJOR_VER_H != ICU_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (GTM_HAL_IRQ_SW_MINOR_VER_H != ICU_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (GTM_HAL_IRQ_SW_PATCH_VER_H != ICU_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define GTM_CH_0    ((uint8)GTM_TIM_CH0)
#define GTM_CH_1    ((uint8)GTM_TIM_CH1)
#define GTM_CH_2    ((uint8)GTM_TIM_CH2)
#define GTM_CH_3    ((uint8)GTM_TIM_CH3)
#define GTM_CH_4    ((uint8)GTM_TIM_CH4)
#define GTM_CH_5    ((uint8)GTM_TIM_CH5)
#define GTM_CH_6    ((uint8)GTM_TIM_CH6)
#define GTM_CH_7    ((uint8)GTM_TIM_CH7)

#define ISR(IsrName)       void IsrName(void)

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
extern ISR(GTM_TIM_0_CH_0_ISR);
extern ISR(GTM_TIM_0_CH_1_ISR);
extern ISR(GTM_TIM_0_CH_2_ISR);
extern ISR(GTM_TIM_0_CH_3_ISR);
extern ISR(GTM_TIM_0_CH_4_ISR);
extern ISR(GTM_TIM_0_CH_5_ISR);
extern ISR(GTM_TIM_0_CH_6_ISR);
extern ISR(GTM_TIM_0_CH_7_ISR);
extern ISR(GTM_TIM_1_CH_0_ISR);
extern ISR(GTM_TIM_1_CH_1_ISR);
extern ISR(GTM_TIM_1_CH_2_ISR);
extern ISR(GTM_TIM_1_CH_3_ISR);
extern ISR(GTM_TIM_1_CH_4_ISR);
extern ISR(GTM_TIM_1_CH_5_ISR);
extern ISR(GTM_TIM_1_CH_6_ISR);
extern ISR(GTM_TIM_1_CH_7_ISR);
extern ISR(GTM_TIM_2_CH_0_ISR);
extern ISR(GTM_TIM_2_CH_1_ISR);
extern ISR(GTM_TIM_2_CH_2_ISR);
extern ISR(GTM_TIM_2_CH_3_ISR);
extern ISR(GTM_TIM_2_CH_4_ISR);
extern ISR(GTM_TIM_2_CH_5_ISR);
extern ISR(GTM_TIM_2_CH_6_ISR);
extern ISR(GTM_TIM_2_CH_7_ISR);
extern ISR(GTM_TIM_3_CH_0_ISR);
extern ISR(GTM_TIM_3_CH_1_ISR);
extern ISR(GTM_TIM_3_CH_2_ISR);
extern ISR(GTM_TIM_3_CH_3_ISR);
extern ISR(GTM_TIM_3_CH_4_ISR);
extern ISR(GTM_TIM_3_CH_5_ISR);
extern ISR(GTM_TIM_3_CH_6_ISR);
extern ISR(GTM_TIM_3_CH_7_ISR);
extern ISR(GTM_TIM_4_CH_0_ISR);
extern ISR(GTM_TIM_4_CH_1_ISR);
extern ISR(GTM_TIM_4_CH_2_ISR);
extern ISR(GTM_TIM_4_CH_3_ISR);
extern ISR(GTM_TIM_4_CH_4_ISR);
extern ISR(GTM_TIM_4_CH_5_ISR);
extern ISR(GTM_TIM_4_CH_6_ISR);
extern ISR(GTM_TIM_4_CH_7_ISR);
extern ISR(GTM_TIM_5_CH_0_ISR);
extern ISR(GTM_TIM_5_CH_1_ISR);
extern ISR(GTM_TIM_5_CH_2_ISR);
extern ISR(GTM_TIM_5_CH_3_ISR);
extern ISR(GTM_TIM_5_CH_4_ISR);
extern ISR(GTM_TIM_5_CH_5_ISR);
extern ISR(GTM_TIM_5_CH_6_ISR);
extern ISR(GTM_TIM_5_CH_7_ISR);
#ifdef __cplusplus
}
#endif
#endif /* GTM_HAL_IRQ_H */


