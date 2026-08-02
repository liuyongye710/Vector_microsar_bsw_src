/**************************************************************************** 
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
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    eTPU.c
*   @version 1.0.1
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eTPU MCAL driver.
*
*   @addtogroup eTPU
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

#include "eTPU.h"
#include "Det.h"

P2CONST(eTPU_ConfigType, ETPU_CONST, ETPU_APPL_CONST) eTPU_ConfigPtr = NULL_PTR;

static const uint32_t etpu_global[] = {0x000000FFU, 0x00000000U};

static const uint32_t etpu_code_buff[] = 
                             { 0x40434049U,0x40434049U,0x405A002EU,0xC088C088U,
                               0xC0884075U,0xC0884066U,0xC0884075U,0xC0884066U,
                               0x4082C088U,0x4082C088U,0x4082C088U,0x4082C088U,
                               0x40824075U,0x40824066U,0x40824075U,0x40824066U,
                               0xC0C9C0C9U,0xC0C9C0C9U,0xC0C9C0C9U,0xC0C9009FU,
                               0x009C008FU,0x40A140C5U,0x40A140C5U,0x40A140C5U,
                               0x40A140C5U,0x40A140C5U,0x40A140C5U,0x40A140C5U,
                               0xC0C9C0C9U,0xC0C9C0C9U,0x40A140C5U,0x40A140C5U,
                               0xF320047FU,0x3BF93FB4U,0x0003301DU,0xF28004BFU,
                               0x00033099U,0xF2C004FFU,0x00033119U,0xF200053FU,
                               0x00033219U,0xF240057FU,0x00033819U,0x9FF37A00U,
                               0xFFFFCCF9U,0x4FEFF6BFU,0x580FF7E5U,0xCFE9F980U,
                               0x0802ABA2U,0xCFFFF980U,0x4FF33FFFU,0xF3A806FFU,
                               0x39FD2FF4U,0x4FF00FFFU,0x39FC2FF4U,0xBFEFFB81U,
                               0x3B1E3FF4U,0xBFF37A85U,0xF3E007FFU,0xFB3F0CFBU,
                               0x4F58FDFEU,0xF7E00D9FU,0xFFFBFCF9U,0x4FF8FBFEU,
                               0xFFFAFCF9U,0xF7E00F7FU,0x4F3FFFFFU,0xBFEFFB84U,
                               0xBFE80A81U,0xBF197A85U,0xBFE80A80U,0xF7E009BFU,
                               0x7C193FDBU,0xBFEFFB84U,0xBFE80A81U,0xBF197A85U,
                               0x7FF83FDBU,0xBFEFFB81U,0x3BF8FFF4U,0xF0C00ABFU,
                               0xF3C00A7FU,0xF7E00A9FU,0x4AFFFFFFU,0x49FFFFFFU,
                               0x6FFFFFFFU,0xF3C00B1FU,0xF7E00B3FU,0x49FFFFFFU,
                               0x4AFFFFFFU,0x6FFFFFFFU,0xBFEFFB84U,0xBFE80A83U,
                               0xBF197A85U,0xCFEFF980U,0xF5000C3FU,0xBFEFFB85U,
                               0x7FF83FDBU,0xBFEFFB82U,0xBFFFFB80U,0xBFEFFB83U,
                               0xF7E009BFU,0xBFFFFB81U,0xCFE8F980U,0x0BF2ABD2U,
                               0xCFFFF980U,0xFFFF3CF9U,0xCFEF7A80U,0x3B1E2FF4U,
                               0xBFEFFB81U,0x3BF8FFF4U,0xF0C00E3FU,0xF7E00E5FU,
                               0x4AFFFFFFU,0x49FFFFFFU,0xBFFE7A84U,0xDFEF3A81U,
                               0xAF1E7A85U,0xCFE8F980U,0x0BF2ABD2U,0xCFFFF980U,
                               0xFFFF3CF9U,0xCFEF7A80U,0x3B1E2FF4U,0xBFEFFB81U,
                               0x3BF8FFF4U,0xF0C0101FU,0xF7E0103FU,0x49FFFFFFU,
                               0x4AFFFFFFU,0xF7C00E5FU,0xBFEFFB85U,0x3BF83FF4U,
                               0xCFE9F980U,0x0802ABA2U,0xCFFFF980U,0x6FFFFF9FU,
                               0xFFC0041FU,0x6FFFFFFFU,0x3BF01FD4U,0x3BF11FD4U,
                               0x3BF71FD4U,0xFFFFCCF9U,0x3BF21FD4U,0xFFF8FCF9U,
                               0x4FF00FFFU,0x5B7FFFF9U,0xCFEFF980U,0xF548131FU,
                               0x593FFFFFU,0xCFEFF980U,0xF508131FU,0x5A5FFFFFU,
                               0x4FF9FFFFU,0xBFFFFF01U,0xFF3FFCFBU,0x47EFF6BFU,
                               0xFFF8FCF9U,0xF7E0123FU,0x4FF33FFFU,0xF7E0121FU,
                               0xFFF9FCF9U,0xBFEFFB81U,0xBDF87A81U,0xBFE80A80U,
                               0x3819FFF4U,0xF480151FU,0xBFFE7A83U,0xF7C0167FU,
                               0xBFFE7A82U,0xFFFF3CF9U,0xF3A0161FU,0xFFFF7CF9U,
                               0xCFEFF885U,0xFFC0115FU,0xCFEFF886U,0xFFC0115FU,
                               0xF3C0167FU,0xFF7FFCFBU,0x47EFF6BFU,0xF240189FU,
                               0xBFEFFB81U,0xBFE80A80U,0x3819FFF4U,0xF480175FU,
                               0xBFF37A83U,0x6FFFFFFFU,0xBFF37A82U,0xFFFF3CF9U,
                               0xF3A0185FU,0xFFFF7CF9U,0xCFEFF885U,0xFFC0115FU,
                               0xCFEFF886U,0xFFC0115FU,0xF3C0189FU,0xFF7FFCFBU,
                               0x47EFF6BFU,0xBFEFFB84U,0x3BF82FF4U,0xF7E0143FU,
                               0x3BFE3FF4U,0xFFC0041FU,0x6FFFFFFFU,0x00000000U,
                               0x00000000U,0x00000000U,0x00000000U,0x00000000U,
};


FUNC(void, ETPU_CODE) eTPU_Init(P2CONST(eTPU_ConfigType, ETPU_CONST, ETPU_APPL_CONST) ConfigPtr)
{
    VAR(uint8, AUTOMATIC) count = 0U;
    VAR(uint8, AUTOMATIC) etpuGroup = 0U;
    

    #if ( ETPU_PRECOMPILE_SUPPORT == STD_ON )
        eTPU_ConfigPtr = &etpuConfig;
    #else 
        eTPU_ConfigPtr = ConfigPtr;
    #endif

    for (count = 0U; count < ETPU_INSTANCE_NUM; count++)
    {
        if( ETPU_INSTANCE_A_B_SUPPORT == STD_ON )
        {
            if(ETPU_LLD_Init (ETPU_INSTANCE_A_B,
                &eTPU_ConfigPtr[count].etpuConfigParameter,
            (uint32_t const *) etpu_code_buff,
            sizeof (etpu_code_buff),
            (uint32_t const *) etpu_global,
            sizeof (etpu_global)) )
            {
                Det_ReportError((uint16)ETPU_MODULE_ID, (uint8)ETPU_INSTANCE, 0, ETPU_E_PARAM_DATA);
            }

            ETPU_LLD_TimerStart(ETPU_INSTANCE_A_B);
        }

        if( ETPU_INSTANCE_C_SUPPORT == STD_ON && eTPU_ConfigPtr[count].etpuInstanceId == ETPU_CONFIG_INSTANCE_C )
        {
            if(ETPU_LLD_Init (ETPU_INSTANCE_C,
                &eTPU_ConfigPtr[count].etpuConfigParameter,
            (uint32_t const *) etpu_code_buff,
            sizeof (etpu_code_buff),
            (uint32_t const *) etpu_global,
            sizeof (etpu_global)))
            {
                Det_ReportError((uint16)ETPU_MODULE_ID, (uint8)ETPU_INSTANCE, 0, ETPU_E_PARAM_DATA);
            }

            ETPU_LLD_TimerStart(ETPU_INSTANCE_C);
        }
    }
            
}

#ifdef __cplusplus
}
#endif