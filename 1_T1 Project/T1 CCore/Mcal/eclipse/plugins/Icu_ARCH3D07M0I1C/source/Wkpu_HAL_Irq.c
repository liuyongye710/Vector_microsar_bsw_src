/* PRQA S 3432, 0380 EOF */
#include "Icu.h"
#include "Icu_Wkpu_LLDrivers.h"
#include "Wkpu_HAL_Irq.h"



/*====================================================================================================
                                        FILE VERSION CHECKS
====================================================================================================*/
#define ICU_WKPU_HAL_IRQ_VENDOR_ID_C                   176

#define ICU_WKPU_HAL_IRQ_MAJOR_VER_C                   4
#define ICU_WKPU_HAL_IRQ_MINOR_VER_C                   4
#define ICU_WKPU_HAL_IRQ_REVISION_VER_C                0

#define ICU_WKPU_HAL_IRQ_SW_MAJOR_VER_C                3
#define ICU_WKPU_HAL_IRQ_SW_MINOR_VER_C                0
#define ICU_WKPU_HAL_IRQ_SW_PATCH_VER_C                0

#if (ICU_WKPU_HAL_IRQ_VENDOR_ID_C != ICU_WKPU_HAL_IRQ_VENDOR_ID_H)
#error "NON-MATCHED DATA : ICU_VENDOR_ID_CFG"
#endif

/* Check if current file and ICU header file are of the same Autosar version */
#if (ICU_WKPU_HAL_IRQ_MAJOR_VER_C != ICU_WKPU_HAL_IRQ_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_MAJOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_MINOR_VER_C != ICU_WKPU_HAL_IRQ_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_MINOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_REVISION_VER_C != ICU_WKPU_HAL_IRQ_REVISION_VER_H)
#error "NON-MATCHED DATA : ICU_REVISION_VER_H"
#endif

/* Check if current file and ICU header file are of the same Software version */
#if (ICU_WKPU_HAL_IRQ_SW_MAJOR_VER_C != ICU_WKPU_HAL_IRQ_SW_MAJOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MAJOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_SW_MINOR_VER_C != ICU_WKPU_HAL_IRQ_SW_MINOR_VER_H)
#error "NON-MATCHED DATA : ICU_SW_MINOR_VER_H"
#endif
#if (ICU_WKPU_HAL_IRQ_SW_PATCH_VER_C != ICU_WKPU_HAL_IRQ_SW_PATCH_VER_H)
#error "NON-MATCHED DATA : ICU_SW_PATCH_VER_H"
#endif


#if defined(CCFC3007PT)
#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ0_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR0.R;/* polyspace RTE:NIV */
    for(channelId = 0U; channelId < 8U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,channelId);
        }
    }
    base->WISR0.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ1_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR0.R;/* polyspace RTE:NIV */
    for(channelId = 8U; channelId < 16U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,channelId);
        }
    }
    base->WISR0.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ2_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR0.R;/* polyspace RTE:NIV */
    for(channelId = 16U; channelId < 24U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,channelId);
        }
    }
    base->WISR0.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ3_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR0.R;/* polyspace RTE:NIV */
    for(channelId = 24U; channelId < 32U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,channelId);
        }
    }
    base->WISR0.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ4_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR1.R;/* polyspace RTE:NIV */
    for(channelId = 0U; channelId < 8U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,(uint8)((uint32)channelId + 32U));
        }
    }
    base->WISR1.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ5_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal =(uint32) base->WISR1.R;/* polyspace RTE:NIV */
    for(channelId = 8U; channelId < 16U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,(uint8)((uint32)channelId + 32U));
        }
    }
    base->WISR1.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ6_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal = (uint32)base->WISR1.R;/* polyspace RTE:NIV */
    for(channelId = 16U; channelId < 24U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,(uint8)((uint32)channelId + 32U));
        }
    }
    base->WISR1.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"
ISR(WKPU_IRQ7_Handler)
{
    CONSTP2VAR(WKPU_Type, ICU_VAR, ICU_APPL_CONST) base = Wkpu_Base[0U];
    uint8 channelId = 0U;
    uint32 regVal = 0U;
    regVal =(uint32) base->WISR1.R;/* polyspace RTE:NIV */
    for(channelId = 24U; channelId < 32U; channelId++)
    {
        if(((1UL << (uint32)channelId) & regVal)!=0U)
        {
            Icu_Wkpu_LLD_IrqCallbcak(0U,(uint8)((uint32)channelId + 32U));
        }
    }
    base->WISR1.R = regVal;
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#endif

