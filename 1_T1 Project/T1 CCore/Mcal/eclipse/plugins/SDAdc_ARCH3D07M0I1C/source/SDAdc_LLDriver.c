/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS, " AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     SDAdc_LLDriver.c
* @version  3.0.0
* @date     2023 - 09 - 01
* @brief    Initial version.
*
*****************************************************************************/
/* PRQA S 0380,2985,3432,4397,2991,2995,2844,3604,2844,4342,1880,2052,1258,4344,1852,4434,2024 EOF*/

#ifdef __cplusplus
extern "C"{
#endif

#include "SDAdc.h"
#include "SDAdc_LLDriver.h"		/* PRQA S 0380,4095*/
#include "intc_lld.h"
#include "eDma.h"
#include "SchM_Sdadc.h"

#define SDADC_LLD_C_VENDOR_ID                     176
#define SDADC_LLD_C_AR_REL_MAJOR_VER              4
#define SDADC_LLD_C_AR_REL_MINOR_VER              4
#define SDADC_LLD_C_AR_REL_REV_VER                0
#define SDADC_LLD_C_SW_MAJOR_VER                  3
#define SDADC_LLD_C_SW_MINOR_VER                  0
#define SDADC_LLD_C_SW_PATCH_VER                  0

#if (SDADC_CFG_H_VENDOR_ID               != SDADC_LLD_C_VENDOR_ID)
    #error " NON-MATCHED DATA : SDADC_LLD_C_VENDOR_ID "
#endif
#if (SDADC_CFG_H_AR_REL_MAJOR_VER    != SDADC_LLD_C_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_AR_REL_MAJOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_MINOR_VER    != SDADC_LLD_C_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_AR_REL_MINOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_REV_VER != SDADC_LLD_C_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_AR_REL_REV_VER "
#endif
#if (SDADC_CFG_H_SW_MAJOR_VER        != SDADC_LLD_C_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_SW_MAJOR_VER "
#endif
#if (SDADC_CFG_H_SW_MINOR_VER        != SDADC_LLD_C_SW_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_SW_MINOR_VER "
#endif
#if (SDADC_CFG_H_SW_PATCH_VER        != SDADC_LLD_C_SW_PATCH_VER)
    #error " NON-MATCHED DATA : SDADC_LLD_C_SW_PATCH_VER "
#endif

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
static FUNC(uint32, SDADC_CODE) SDADC_LLD_CalculateGain(CONST(Sdadc_InstanceType, SDADC_CONST) instance);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
static FUNC(uint32, SDADC_CODE) SDADC_LLD_CalculateOffset(CONST(Sdadc_InstanceType, SDADC_CONST) instance, VAR(uint32, SDADC_VAR) gainVal);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"
static CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) Adc_SdadcBase[ADC_SDADC_MAX_INSTANCE] = SDADC_BASE_PTR_ARRAY;
#define SDADC_STOP_SEC_CONFIG_DATA
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Demodulator Input Configuration Register (SDADC_DICFG: ITRMODE)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_DICFG_SetIntegratorTriggerMode \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) IntegratorTriggerMode \
)
{
    BasePtr->DICFG.R = SDADC_DICFG_ITRMODE(IntegratorTriggerMode);/* polyspace RTE:IDP */  
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"
/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: CALIB_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_FCFGM_SetCalibEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_CALIB_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_CALIB_EN_MASK;      /* polyspace RTE:NIV,IDP */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Interrupt Enable Configuration Register (SDADC_IECFG: FWM_INT_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_IECFG_SetFifoWaterMarkerIntEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->IECFG.R &= ~SDADC_IECFG_FWM_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
    else
    {
        BasePtr->IECFG.R |= SDADC_IECFG_FWM_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Control Register (SDADC_CTRL: SDADC_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_CTRL_SetSdadcEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    BasePtr->CTRL.R = ((EnDis == FALSE) ? 0UL : SDADC_CTRL_EN_MASK);/* polyspace RTE:IDP */  
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Gain Correction Register (SDADC_GAINCORR: CICSHIFT)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_GAINCORR_SetCorrection \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) CorrMultiFactor, \
    CONST(uint8, SDADC_CONST) CICShift \
)
{
    BasePtr->GAINCORR.R = SDADC_GAINCORR_GAINFACTOR(CorrMultiFactor) | SDADC_GAINCORR_CICSHIFT(CICShift);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Gain Calibration Register (SDADC_GAINCAL: CALFACTOR)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_GAINCAL_SetMultiFactor \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) CalMultiFactor \
)
{
    BasePtr->GAINCAL.R = SDADC_GAINCAL_CALFACTOR(CalMultiFactor);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, CIC Filter (SDADC_FCFGC: CFMDF)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGC_SetCICFilterDecFactor \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) CICFilterDecFactor \
)
{
    BasePtr->FCFGC.R &= ~SDADC_FCFGC_CFMDF_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCFGC.R |= SDADC_FCFGC_CFMDF(CICFilterDecFactor);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, CIC Filter (SDADC_FCFGC: CFMSV)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGC_SetCICFilterStartVal \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) CICFilterStartVal \
)
{
    BasePtr->FCFGC.R &= ~SDADC_FCFGC_CFMSV_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCFGC.R |= SDADC_FCFGC_CFMSV(CICFilterStartVal);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Counter Register, CIC Filter (SDADC_FCNTC: CFMDCNT)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCNTC_SetCICFilterDecCounter \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) CICFilterDecCounter \
)
{
    BasePtr->FCNTC.R &= ~SDADC_FCNTC_CFMDCNT_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCNTC.R |= SDADC_FCNTC_CFMDCNT(CICFilterDecCounter);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: FIR0EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetFIR0FilterEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_FIR0EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_FIR0EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: FIR1EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetFIR1FilterEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_FIR1EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_FIR1EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: OVCEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetOvershootCompenEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_OVCEN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_OVCEN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: FIR1DEC)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetFIR1FilterDecRate \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) FIR1FilterDecRate \
)
{
    if (FIR1FilterDecRate == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_FIR1DEC_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_FIR1DEC_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: CICMOD)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetCICFilterMode \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) CICFilterMode \
)
{
    if (CICFilterMode == SDADC_CIC_MODE_CIC3)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_CICMOD_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_CICMOD_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: PFEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetPrefilterEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_PFEN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_PFEN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: COMPTR_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetBoundaryComparatorEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_COMPTR_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_COMPTR_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: EXT_MESH_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetExtMeshClkEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_EXT_MESH_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_EXT_MESH_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: OCEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetOffsetCompenFilterEn \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) OffsetCompenFilterEn \
)
{
    BasePtr->FCFGM.R &= ~SDADC_FCFGM_OCEN_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCFGM.R |= SDADC_FCFGM_OCEN(OffsetCompenFilterEn);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: CH_WRAP_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetChannelWraparoundEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_CH_WRAP_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_CH_WRAP_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Configuration Register, Main (SDADC_FCFGM: DIFF_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFGM_SetDifferenceEnDis 
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFGM.R &= ~SDADC_FCFGM_DIFF_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFGM.R |= SDADC_FCFGM_DIFF_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Offset Compensation Register (SDADC_OFFCOMP: OFFSET)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OFFCOMP_SetOffsetVal \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) OffsetVal \
)
{
    BasePtr->OFFCOMP.R = SDADC_OFFCOMP_OFFSET(OffsetVal);     /* polyspace RTE:NIV */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint32, SDADC_CODE) SDADC_OFFCOMP_GetOffsetVal(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint32)(BasePtr->OFFCOMP.R);     /* polyspace RTE:NIV */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Interrupt Enable Configuration Register (SDADC_IECFG: FOV_INT_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IECFG_SetFifoOverFlowIntEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->IECFG.R &= ~SDADC_IECFG_FOV_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
    else
    {
        BasePtr->IECFG.R |= SDADC_IECFG_FOV_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Interrupt Enable Configuration Register (SDADC_IECFG: DOV_INT_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IECFG_SetDataOverFlowIntEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->IECFG.R &= ~SDADC_IECFG_DOV_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
    else
    {
        BasePtr->IECFG.R |= SDADC_IECFG_DOV_INT_EN_MASK;     /* polyspace RTE:NIV,IDP */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Interrupt Enable Configuration Register (SDADC_IECFG: DMA_REQ_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IECFG_SetDMAReqEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->IECFG.R &= ~SDADC_IECFG_DMA_REQ_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->IECFG.R |= SDADC_IECFG_DMA_REQ_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC FIFO Configuration Register (SDADC_FCFG: FIFOSIZE)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFG_SetFifoSize
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) FifoSize \
)
{
    BasePtr->FCFG.R &= ~SDADC_FCFG_FIFOSIZE_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCFG.R |= SDADC_FCFG_FIFOSIZE(FifoSize);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC FIFO Configuration Register (SDADC_FCFG: FIFOWM)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFG_SetFifoWaterMarkerVal \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) FifoWaterMarkerVal \
)
{
    BasePtr->FCFG.R &= ~SDADC_FCFG_FIFOWM_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCFG.R |= SDADC_FCFG_FIFOWM(FifoWaterMarkerVal);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC FIFO Configuration Register (SDADC_FCFG: INFOEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFG_SetInfoEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFG.R &= ~SDADC_FCFG_INFOEN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFG.R |= SDADC_FCFG_INFOEN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC FIFO Configuration Register (SDADC_FCFG: SIGNEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCFG_SetSignEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCFG.R &= ~SDADC_FCFG_SIGNEN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCFG.R |= SDADC_FCFG_SIGNEN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC FIFO Data Register (SDADC_FDATA: DATA)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint32, SDADC_CODE) SDADC_FDATA_GetFifoData(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint32)(BasePtr->FDATA.R);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"
/*******************************************************************************
 * @brief SDADC Integrator Status Register (SDADC_ISTAT: INTEN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint8, SDADC_CODE) SDADC_ISTAT_GetIntegrationEn(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint8)((BasePtr->ISTAT.R & SDADC_ISTAT_INTEN_MASK) >> SDADC_ISTAT_INTEN_SHIFT);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Intermediate Integration Value Register (SDADC_IIVAL: IVAL)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint32, SDADC_CODE) SDADC_IIVAL_GetInterIntegrationVal(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint32)(BasePtr->IIVAL.R);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: ISC)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetIntegratorShiftCtrl \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) IntegratorShiftCtrl \
)
{
    BasePtr->IWCTR.R &= ~SDADC_IWCTR_ISC_MASK;     /* polyspace RTE:NIV */
    BasePtr->IWCTR.R |= SDADC_IWCTR_ISC(IntegratorShiftCtrl);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: IWS)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetIntegrationWindowSize \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) IntegrationWindowSize \
)
{
    if (IntegrationWindowSize == FALSE)
    {
        BasePtr->IWCTR.R &= ~SDADC_IWCTR_IWS_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->IWCTR.R |= SDADC_IWCTR_IWS_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: FRC)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetFilterRestartCtrl \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) FilterRestartCtrl \
)
{
    if (FilterRestartCtrl == FALSE)
    {
        BasePtr->IWCTR.R &= ~SDADC_IWCTR_FRC_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->IWCTR.R |= SDADC_IWCTR_FRC_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: REPVAL)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetIntegrationCycle \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) IntegrationCycle \
)
{
    BasePtr->IWCTR.R &= ~SDADC_IWCTR_REPVAL_MASK;     /* polyspace RTE:NIV */
    BasePtr->IWCTR.R |= SDADC_IWCTR_REPVAL(IntegrationCycle);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: NVALDIS)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetNumberOfValDiscarded \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) NumberOfValDiscarded \
)
{
    BasePtr->IWCTR.R &= ~SDADC_IWCTR_NVALDIS_MASK;     /* polyspace RTE:NIV */
    BasePtr->IWCTR.R |= SDADC_IWCTR_NVALDIS(NumberOfValDiscarded);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Integration Window Control Register (SDADC_IWCTR: NVALINT)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_IWCTR_SetNumberOfValAccumulated \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) NumberOfValAccumulated \
)
{
    BasePtr->IWCTR.R &= ~SDADC_IWCTR_NVALINT_MASK;     /* polyspace RTE:NIV */
    BasePtr->IWCTR.R |= SDADC_IWCTR_NVALINT(NumberOfValAccumulated);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"


/*******************************************************************************
 * @brief SDADC Boundary Select Register (SDADC_BOUNDSEL: BOUNDARYL / BOUNDARYU)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_BOUNDSEL_SetLowerUpperBoundaryLimit \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) LowerBoundaryLimit, \
    CONST(uint16, SDADC_CONST) UpperBoundaryLimit \
)
{
    BasePtr->BOUNDSEL.R = SDADC_BOUNDSEL_BOUNDARYL(LowerBoundaryLimit) | SDADC_BOUNDSEL_BOUNDARYU(UpperBoundaryLimit);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC WaterMarker Interrupt State Register (SDADC_WMINTSTAT: FWM_INT)
 *
 * @note  Read / Write 1 clear.
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint8, SDADC_CODE) SDADC_WMINTSTAT_GetWaterMarkerIntState(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint8)(BasePtr->WMINTSTAT.R & SDADC_WMINTSTAT_FWM_INT_MASK);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_WMINTSTAT_ClearWaterMarkerIntState(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    BasePtr->WMINTSTAT.R = SDADC_WMINTSTAT_FWM_INT_MASK;     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC OverFlow Interrupt State Register
 *          (SDADC_OVINTSTAT: FOV_INT / DOV_INT)
 *
 * @note  Read / Write 1 clear.
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint8, SDADC_CODE) SDADC_OVINTSTAT_GetDataOverFlowIntState(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint8)((BasePtr->OVINTSTAT.R & SDADC_OVINTSTAT_DOV_INT_MASK) >> 1U);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVINTSTAT_ClearDataOverFlowIntState(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{															/* PRQA S 4391 */						
    BasePtr->OVINTSTAT.R = SDADC_OVINTSTAT_DOV_INT_MASK;	/* PRQA S 4391 */	/* polyspace RTE:IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint8, SDADC_CODE) SDADC_OVINTSTAT_GetFifoOverFlowIntState(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint8)(BasePtr->OVINTSTAT.R & SDADC_OVINTSTAT_FOV_INT_MASK);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVINTSTAT_ClearFifoOverFlowIntState(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{															/* PRQA S 4391 */
    BasePtr->OVINTSTAT.R = SDADC_OVINTSTAT_FOV_INT_MASK;	/* PRQA S 4391 */	/* polyspace RTE:IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Overshoot Compensation Configuration Register
 *          (SDADC_OVSCFG: SRFS)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVSCFG_SetSlewRateFilterStrength \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) SlewRateFilterStrength \
)
{
    BasePtr->OVSCFG.R &= ~SDADC_OVSCFG_SRFS_MASK;     /* polyspace RTE:NIV */
    BasePtr->OVSCFG.R |= SDADC_OVSCFG_SRFS(SlewRateFilterStrength);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Overshoot Compensation Configuration Register
 *          (SDADC_OVSCFG: SRFRT)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVSCFG_SetSlewRateFilterRunTime \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) SlewRateFilterRunTime \
)
{
    BasePtr->OVSCFG.R &= ~SDADC_OVSCFG_SRFRT_MASK;     /* polyspace RTE:NIV */
    BasePtr->OVSCFG.R |= SDADC_OVSCFG_SRFRT(SlewRateFilterRunTime);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Overshoot Compensation Configuration Register
 *          (SDADC_OVSCFG: SDM)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVSCFG_SetStepDetectionMode \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) StepDetectionMode \
)
{
    if (StepDetectionMode == FALSE)
    {
        BasePtr->OVSCFG.R &= ~SDADC_OVSCFG_SDM_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->OVSCFG.R |= SDADC_OVSCFG_SDM_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Overshoot Compensation Configuration Register
 *          (SDADC_OVSCFG: SDTH)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_OVSCFG_SetStepDetectionThreshold \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint16, SDADC_CONST) StepDetectionThreshold \
)
{
    BasePtr->OVSCFG.R &= ~SDADC_OVSCFG_SDTH_MASK;     /* polyspace RTE:NIV */
    BasePtr->OVSCFG.R |= SDADC_OVSCFG_SDTH(StepDetectionThreshold);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Hardware Trigger Configuration Register
 *          (SDADC_HTCFG: HT0 ~ HT15)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_HTCFG_SetHwTriggerEdge \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint32, SDADC_CONST) HwTrigIdx, \
    CONST(uint32, SDADC_CONST) HwTrigEdge \
)
{
    if (HwTrigIdx < SDADC_HW_TRIG_CNT)
    {	
        /* PRQA S 1891 */	
        if((SDADC_HTCFG_HT0_WIDTH * HwTrigIdx) <= 32U)
        {
            BasePtr->HTCFG.R &= ~(SDADC_HTCFG_HT0_MASK  << (SDADC_HTCFG_HT0_WIDTH * HwTrigIdx));			/* PRQA S 1891 */       /* polyspace RTE:NIV */  
        }
        if((SDADC_HTCFG_HT0_WIDTH * HwTrigIdx) <= 32U)
        {
            BasePtr->HTCFG.R |= ((HwTrigEdge & SDADC_HTCFG_HT0_MASK) << (SDADC_HTCFG_HT0_WIDTH * HwTrigIdx));	/* PRQA S 1891 */	     /* polyspace RTE:NIV */
        }
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Software Trigger Configuration Register (SDADC_STCFG: SH_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_STCFG_SetSoftTrigEn(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    BasePtr->STCFG.R = SDADC_STCFG_SH_EN_MASK;/* polyspace RTE:IDP */  
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Software Trigger Configuration Register (SDADC_STCFG: SH_CLR)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_STCFG_ClearSoftTrig(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    BasePtr->STCFG.R = SDADC_STCFG_SH_CLR_MASK;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Software Trigger Configuration Register (SDADC_STCFG: FSRSTN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_STCFG_SetFifoSoftReset(CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    BasePtr->STCFG.R = SDADC_STCFG_FSRSTN_MASK;/* polyspace RTE:IDP */  
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Chain Discard Register (SDADC_FCDIS: FCDIS_EN)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCDIS_SetFilterChainDiscardEnDis \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(boolean, SDADC_CONST) EnDis \
)
{
    if (EnDis == FALSE)
    {
        BasePtr->FCDIS.R &= ~SDADC_FCDIS_FCDIS_EN_MASK;     /* polyspace RTE:NIV */
    }
    else
    {
        BasePtr->FCDIS.R |= SDADC_FCDIS_FCDIS_EN_MASK;     /* polyspace RTE:NIV */
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Filter Chain Discard Register (SDADC_FCDIS: FCDIS_NUM)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_FCDIS_SetFilterChainDiscardNum \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) FilterChainDiscardNum \
)
{
    BasePtr->FCDIS.R &= ~SDADC_FCDIS_FCDIS_NUM_MASK;     /* polyspace RTE:NIV */
    BasePtr->FCDIS.R |= SDADC_FCDIS_FCDIS_NUM(FilterChainDiscardNum);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Channel default & wrap Register (SDADC_CH_WRAP: CH_DFLT /CH_NUM)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_CH_WRAP_SetChannelDefault \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) ChannelDefault, \
    CONST(uint8, SDADC_CONST) ChannelWrap \
)
{
    BasePtr->CH_WRAP.R = SDADC_CH_WRAP_CH_DFLT(ChannelDefault) | SDADC_CH_WRAP_CH_NUM(ChannelWrap);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Analog Channel Resistor Select Register (SDADC_RES)
 *******************************************************************************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_RES_SetResistorSelChan \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) res_p_lv, \
    CONST(uint8, SDADC_CONST) res_n_lv \
)
{
    BasePtr->RES.R = SDADC_RES_RES_N_LV(res_n_lv) | SDADC_RES_RES_P_LV(res_p_lv);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

/*******************************************************************************
 * @brief SDADC Analog Module Configuration Register (SDADC_ATT)
 **************************************************************** ***************/
#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(void, SDADC_CODE) SDADC_ATT_SetAnalogModuleCfg \
(
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr, \
    CONST(uint8, SDADC_CONST) gain_lv, \
    CONST(uint8, SDADC_CONST) vcom_sel_lv, \
    CONST(uint8, SDADC_CONST) adc_div_lv \
)
{
    BasePtr->ATT.R = (SDADC_ATT_GAIN_LV(gain_lv) | SDADC_ATT_VCOM_SEL_LV(vcom_sel_lv) | 	/* polyspace RTE:IDP */
                      SDADC_ATT_ADC_DIV_LV(adc_div_lv));
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
SDADC_INLINE FUNC(uint32, SDADC_CODE) SDADC_ATT_GetAnalogModuleCfg(CONSTP2CONST(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr)
{
    return (uint32)(BasePtr->ATT.R);     /* polyspace RTE:NIV,IDP */
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_Init \
(
	CONST(Sdadc_InstanceType, SDADC_CONST) instance, \
	CONSTP2CONST(Sdadc_ConfigType, SDADC_CONST, SDADC_APPL_CONST) ConfigPtr, \
	CONST(uint16, SDADC_CONST) Trig_Sel
)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    DEV_ASSERT(ConfigPtr != NULL);

    VAR(uint8, SDADC_VAR) u8inst = (uint8)instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[u8inst];

	VAR(uint32, SDADC_VAR) gain_cal_val, offset_cal_val = 0U;

	P2VAR(uint32, SDADC_VAR, SDADC_APPL_CONST) SDAdc_MSCR[ADC_SDADC_MAX_INSTANCE] =
	{
		(uint32 *)(0xfffc0b88U), //SIUL2_MSCR[594] 
		(uint32 *)(0xfffc0b8cU), //SIUL2_MSCR[595] 
		(uint32 *)(0xfffc0b90U), //SIUL2_MSCR[596] 
		(uint32 *)(0xfffc0b94U), //SIUL2_MSCR[597] 
		(uint32 *)(0xfffc0b98U), //SIUL2_MSCR[598] 
		(uint32 *)(0xfffc0b9CU), //SIUL2_MSCR[599] 
		(uint32 *)(0xfffc0ba0U), //SIUL2_MSCR[600] 
		(uint32 *)(0xfffc0ba4U), //SIUL2_MSCR[601] 
		(uint32 *)(0xfffc0ba8U), //SIUL2_MSCR[602] 
	};
	VAR(Sdadc_HwTrigSourceType, SDADC_VAR) SDAdc_HwTrigMap[] =
	{
		TOM2_4_SOURCE,
		TOM2_5_SOURCE,
		TOM2_6_SOURCE,
		TOM2_7_SOURCE,
		TOM2_8_SOURCE,
		TOM2_9_SOURCE,
		TOM2_10_SOURCE,
		TOM2_11_SOURCE,
		ATOM3_0_SOURCE,
		ATOM3_1_SOURCE,
		ATOM3_2_SOURCE,
		ATOM3_3_SOURCE,
		ATOM3_4_SOURCE,
		ATOM3_5_SOURCE,
		ATOM3_6_SOURCE,
		ATOM3_7_SOURCE,
	};
	P2VAR(uint32, SDADC_VAR, SDADC_APPL_DATA) MSCRPtr = SDAdc_MSCR[instance];
    DEV_ASSERT((ConfigPtr->AnalogCfg.PreGain == SDADC_PRE_GAIN_X1) || \
               (ConfigPtr->AnalogCfg.PreGain == SDADC_PRE_GAIN_X2) || \
               (ConfigPtr->AnalogCfg.PreGain == SDADC_PRE_GAIN_X4));
    DEV_ASSERT((uint8)(ConfigPtr->AnalogCfg.VcomSel) <= (uint8)SDADC_VCOM_SEL_VREF_L);
    DEV_ASSERT((uint8)(ConfigPtr->AnalogCfg.ClkDiv) <= (uint8)SDADC_CLK_DIV_8);
    
	SchM_Enter_SDADC_EXCLUSIVE_AREA_00();

    /* Analog Module PRE configuration */
    SDADC_ATT_SetAnalogModuleCfg(BasePtr, 1U, (uint8)(ConfigPtr->AnalogCfg.VcomSel), (uint8)(ConfigPtr->AnalogCfg.ClkDiv));
    /* Calculate Gain Value */
    gain_cal_val = SDADC_LLD_CalculateGain((Sdadc_InstanceType)u8inst);

    /* Calculate Offset Value */
    offset_cal_val = SDADC_LLD_CalculateOffset((Sdadc_InstanceType)u8inst, gain_cal_val);

    SDADC_CTRL_SetSdadcEnDis(BasePtr, FALSE);

    SDADC_STCFG_ClearSoftTrig(BasePtr);

    SDADC_STCFG_SetFifoSoftReset(BasePtr);

    SDADC_ATT_SetAnalogModuleCfg(BasePtr, (uint8)(ConfigPtr->AnalogCfg.PreGain), (uint8)(ConfigPtr->AnalogCfg.VcomSel), (uint8)(ConfigPtr->AnalogCfg.ClkDiv));

    VAR(uint16, SDADC_VAR) cicFilterDecimationFactor = 0;
    VAR(uint8, SDADC_VAR) cicFilterOutputShifter = 0;
    VAR(boolean, SDADC_VAR) fir0State = TRUE, fir1State = TRUE, preFilterState = TRUE;

    switch(ConfigPtr->OsrVal)
    {
		case SDADC_OSR_12:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 5U;

				cicFilterOutputShifter = 2U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}

				fir0State = FALSE;

				preFilterState = FALSE;
			}
			else
			{
				cicFilterDecimationFactor = 2U;

				cicFilterOutputShifter = 3U;

				fir0State = FALSE;
			}

			break;
		}

		case SDADC_OSR_16:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 3U;

				cicFilterOutputShifter = 3U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}

				fir0State = FALSE;
			}
			else
			{
				cicFilterDecimationFactor = 3U;

				cicFilterOutputShifter = 4U;

				fir0State = FALSE;
			}

			break;
		}

		case SDADC_OSR_24:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 5U;

				cicFilterOutputShifter = 6U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}

				fir0State = FALSE;
			}
			else
			{
				cicFilterDecimationFactor = 2U;

				cicFilterOutputShifter = 7U;
			}

			break;
		}

		case SDADC_OSR_32:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 3U;

				cicFilterOutputShifter = 3U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 3U;

				cicFilterOutputShifter = 4U;
			}

			break;
		}

		case SDADC_OSR_48:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 5U;

				cicFilterOutputShifter = 6U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 5U;

				cicFilterOutputShifter = 7U;
			}

			break;
		}

		case SDADC_OSR_64:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 7U;

				cicFilterOutputShifter = 7U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 7U;

				cicFilterOutputShifter = 8U;
			}

			break;
		}

		case SDADC_OSR_96:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 11U;

				cicFilterOutputShifter = 10U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 11U;

				cicFilterOutputShifter = 11U;
			}

			break;
		}

		case SDADC_OSR_128:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 15U;

				cicFilterOutputShifter = 11U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 15U;

				cicFilterOutputShifter = 12U;
			}

			break;
		}

		case SDADC_OSR_160:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 19U;

				cicFilterOutputShifter = 12U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 19U;

				cicFilterOutputShifter = 13U;
			}

			break;
		}

		case SDADC_OSR_192:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 23U;

				cicFilterOutputShifter = 13U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 23U;

				cicFilterOutputShifter = 14U;
			}

			break;
		}

		case SDADC_OSR_224:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 27U;

				cicFilterOutputShifter = 14U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 27U;

				cicFilterOutputShifter = 15U;
			}

			break;
		}

		case SDADC_OSR_256:
		{
			if(ConfigPtr->ChanSel.DifferenceEn == FALSE)
			{
				cicFilterDecimationFactor = 31U;

				cicFilterOutputShifter = 15U;

				if((uint8)(ConfigPtr->AnalogCfg.PreGain) == (uint8)2U)
				{
					cicFilterOutputShifter = (uint8)(cicFilterOutputShifter + (uint8)1U);
				}
			}
			else
			{
				cicFilterDecimationFactor = 31U;

				cicFilterOutputShifter = 16U;
			}

			break;
		}

		default:
		{
			/* Nothing todo */
			break;
		}
    }


    
	SDADC_GAINCORR_SetCorrection(BasePtr, (uint16)gain_cal_val, cicFilterOutputShifter);

    SDADC_FCFGC_SetCICFilterDecFactor(BasePtr, cicFilterDecimationFactor);

    SDADC_FCFGC_SetCICFilterStartVal(BasePtr, (uint16)(cicFilterDecimationFactor + (uint16)1U));

	SDADC_OFFCOMP_SetOffsetVal(BasePtr, (uint16)offset_cal_val);

	SDADC_FCNTC_SetCICFilterDecCounter(BasePtr, cicFilterDecimationFactor);

	SDADC_CH_WRAP_SetChannelDefault(BasePtr, ConfigPtr->ChanSel.ChanDefaultId, ConfigPtr->ChanWrap.ChanWraparoundNum);

	SDADC_GAINCAL_SetMultiFactor(BasePtr, 0x1000U);

    SDADC_FCFGM_SetFIR0FilterEnDis(BasePtr, fir0State);

    SDADC_FCFGM_SetFIR1FilterEnDis(BasePtr, fir1State);

    SDADC_FCFGM_SetOvershootCompenEnDis(BasePtr, ConfigPtr->FirFilter.OvershootCompEn);

    SDADC_FCFGM_SetFIR1FilterDecRate(BasePtr, (uint8)(ConfigPtr->FirFilter.Fir1DecimationRate));

    SDADC_FCFGM_SetCICFilterMode(BasePtr, (((ConfigPtr->FirFilter.CicMode) != FALSE) ? (uint8)1U : (uint8)0U));

    SDADC_FCFGM_SetPrefilterEnDis(BasePtr, preFilterState);

    if(ConfigPtr->Comparator.BoundaryComparatorEn == TRUE)
    {
        SDADC_FCFGM_SetBoundaryComparatorEnDis(BasePtr, TRUE);

        SDADC_BOUNDSEL_SetLowerUpperBoundaryLimit(BasePtr, ConfigPtr->Comparator.LowerBoundary, ConfigPtr->Comparator.UpperBoundary);
    }

    SDADC_FCFGM_SetExtMeshClkEnDis(BasePtr, (((uint32)(ConfigPtr->ExtMeshClkSel) != 0U) ? (boolean)TRUE : (boolean)FALSE));

    if(ConfigPtr->DCTestEn == FALSE)
    {
        SDADC_FCFGM_SetOffsetCompenFilterEn(BasePtr, (uint8)(ConfigPtr->FirFilter.OffsetCompFilterEn));
        SDADC_RES_SetResistorSelChan(BasePtr, (((ConfigPtr->Res_P_En) != FALSE) ? (uint8)1U : (uint8)0U), (((ConfigPtr->Res_N_En) != FALSE) ? (uint8)1U : (uint8)0U));
    }
    else
    {
    	SDADC_FCFGM_SetOffsetCompenFilterEn(BasePtr, FALSE);
    }

    SDADC_FCFGM_SetChannelWraparoundEnDis(BasePtr, ConfigPtr->ChanWrap.ChanWraparoundEn);

    SDADC_FCFGM_SetDifferenceEnDis(BasePtr, ConfigPtr->ChanSel.DifferenceEn);

    SDADC_FCFGM_SetCalibEnDis(BasePtr, ConfigPtr->FirFilter.CalibrationEn);

    SchM_Enter_SDADC_EXCLUSIVE_AREA_01();

    /* Overshoot Compensation */
    if (ConfigPtr->FirFilter.OvershootCompEn != FALSE)
    {
        DEV_ASSERT(ConfigPtr->OvershootComp.StepDetectionThreshold <= SDADC_OVERSHOOT_STEP_DETECTION_THRESHOLD_MAX);

        SDADC_OVSCFG_SetSlewRateFilterStrength(BasePtr, (uint8)(ConfigPtr->OvershootComp.SlewRateFilterStrength));

        SDADC_OVSCFG_SetSlewRateFilterRunTime(BasePtr, (uint8)(ConfigPtr->OvershootComp.SlewRateFilterRunTime));

        SDADC_OVSCFG_SetStepDetectionMode(BasePtr, (uint8)(ConfigPtr->OvershootComp.StepDetectionMode));

        SDADC_OVSCFG_SetStepDetectionThreshold(BasePtr, ConfigPtr->OvershootComp.StepDetectionThreshold);
    }

    /* Interrupt/DMA Enable Configuration */
    SDADC_IECFG_SetFifoWaterMarkerIntEnDis(BasePtr, ConfigPtr->IntDma.FifoWaterMarkerIntEn);

    SDADC_IECFG_SetFifoOverFlowIntEnDis(BasePtr, ConfigPtr->IntDma.FifoOverFlowIntEn);

    SDADC_IECFG_SetDataOverFlowIntEnDis(BasePtr, ConfigPtr->IntDma.DataOverFlowIntEn);

    SDADC_IECFG_SetDMAReqEnDis(BasePtr, ConfigPtr->IntDma.DmaReqEn);

	/* Integration configuration */
    if(ConfigPtr->IntegratorEn == TRUE)
    {
		DEV_ASSERT((ConfigPtr->Integrator.IntegratorTrigMode) <= SDADC_INTEGRATOR_TRIG_MODE_ALWAYS_ACTIVE);
		DEV_ASSERT((ConfigPtr->Integrator.IntegratorShiftCtrl) <= SDADC_INTEGRATOR_SHIFT_CTRL_SEL_BITS_9_25);

		SDADC_DICFG_SetIntegratorTriggerMode(BasePtr, (uint8)(ConfigPtr->Integrator.IntegratorTrigMode));

		SDADC_IWCTR_SetIntegratorShiftCtrl(BasePtr, (uint8)(ConfigPtr->Integrator.IntegratorShiftCtrl));

		SDADC_IWCTR_SetIntegrationWindowSize(BasePtr, (uint8)(ConfigPtr->Integrator.IntegrationWindowSize));

		SDADC_IWCTR_SetFilterRestartCtrl(BasePtr, (uint8)(ConfigPtr->Integrator.FilterChainRestartCtrl));

		SDADC_IWCTR_SetIntegrationCycle(BasePtr, ConfigPtr->Integrator.NumOfIntegrationCycles);

		SDADC_IWCTR_SetNumberOfValDiscarded(BasePtr, ConfigPtr->Integrator.NumOfDiscardedVal);

		SDADC_IWCTR_SetNumberOfValAccumulated(BasePtr, ConfigPtr->Integrator.NumOfAccumulatedVal);
    }

	/* Filter Chain Discard */
	SDADC_FCDIS_SetFilterChainDiscardEnDis(BasePtr, ConfigPtr->FilterChainDiscard.FilterChainDiscardEn);

	SDADC_FCDIS_SetFilterChainDiscardNum(BasePtr, ConfigPtr->FilterChainDiscard.FilterChainDiscardNum);

	/* FIFO Configuration */
	DEV_ASSERT(ConfigPtr->FifoCfg.FifoSize <= SDADC_FIFO_SIZE_MAX);
	DEV_ASSERT(ConfigPtr->FifoCfg.FifoSize >= ConfigPtr->FifoCfg.FifoWaterMarker);

	SDADC_FCFG_SetFifoSize(BasePtr, ConfigPtr->FifoCfg.FifoSize);

	SDADC_FCFG_SetFifoWaterMarkerVal(BasePtr, ConfigPtr->FifoCfg.FifoWaterMarker);

	SDADC_FCFG_SetInfoEnDis(BasePtr, ConfigPtr->FifoCfg.InfoEn);

	SDADC_FCFG_SetSignEnDis(BasePtr, ConfigPtr->FifoCfg.SignEn);

	if(Trig_Sel < (uint16)HWTRIGSEL_SDADC0)
	{
		*MSCRPtr = (uint32)SDAdc_HwTrigMap[Trig_Sel];
	}
	/* Hardware Trigger Configuration */
	for(uint32 i = 0U; i < SDADC_HW_TRIG_CNT; i++)
	{
		SDADC_HTCFG_SetHwTriggerEdge(BasePtr, i, (uint32)(ConfigPtr->HwTrigSel[i]));
	}

    /* Clear flag */
    SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);
    SDADC_OVINTSTAT_ClearDataOverFlowIntState(BasePtr);
    SDADC_OVINTSTAT_ClearFifoOverFlowIntState(BasePtr);

    SchM_Exit_SDADC_EXCLUSIVE_AREA_00();
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_DeInit(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));

    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;
    if(instance_l >= ADC_SDADC_MAX_INSTANCE)
    {
    	return;
    }

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];
//    uint8 i;

    /* SDADC disable */
    SDADC_CTRL_SetSdadcEnDis(BasePtr, FALSE);

    /* Flush FIFO */
    SDADC_STCFG_SetFifoSoftReset(BasePtr);

    /* Interrupt/DMA */
    BasePtr->IECFG.R    = 0UL;
    /* Control */
    BasePtr->FCFGM.R    = 0UL;
    BasePtr->DICFG.R    = 0UL;
    /* Configuration */
    BasePtr->GAINCORR.R = 0UL;
    BasePtr->GAINCAL.R  = 0UL;
    BasePtr->FCFGC.R    = 0UL;
    BasePtr->OFFCOMP.R  = 0UL;
    BasePtr->FCFG.R     = SDADC_FCFG_FIFOSIZE(SDADC_FIFO_SIZE_MAX);
    BasePtr->IWCTR.R    = 0UL;
    BasePtr->BOUNDSEL.R = 0UL;
    BasePtr->OVSCFG.R   = 0UL;
    BasePtr->HTCFG.R    = 0UL;
    BasePtr->FCDIS.R    = 0UL;
    BasePtr->CH_WRAP.R  = 0UL;

    SDADC_RES_SetResistorSelChan(BasePtr, 0U, 0U);
    SDADC_ATT_SetAnalogModuleCfg(BasePtr, 0U, 0U, 0U);

    /* Clear flag */
    SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);
    SDADC_OVINTSTAT_ClearDataOverFlowIntState(BasePtr);
    SDADC_OVINTSTAT_ClearFifoOverFlowIntState(BasePtr);

	MC_RGM.PRST1.R = 0x1f000000;
	MC_RGM.PRST5.R = 0x1f000000;
	MC_RGM.PRST1.R = 0x00000000;
	MC_RGM.PRST5.R = 0x00000000;

}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ModuleEnable(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));

    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_CTRL_SetSdadcEnDis(BasePtr, TRUE);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ModuleDisable(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));

    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_CTRL_SetSdadcEnDis(BasePtr, FALSE);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
static FUNC(uint32, SDADC_CODE) SDADC_LLD_CalculateGain(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));

    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    VAR(uint32, SDADC_VAR) attValue;

    VAR(uint8, SDADC_VAR) attVcomSelValue, attClkDivValue;

	VAR(uint32, SDADC_VAR) gain_corr_p = 0x1000;

	VAR(uint32, SDADC_VAR) gain_corr_n = 0x1000;

	VAR(uint32, SDADC_VAR) gain_sft_mask = 0x1000;

	VAR(uint32, SDADC_VAR) hard_data ,gain_corr= 0;

	

    attValue = SDADC_ATT_GetAnalogModuleCfg(BasePtr);

    attClkDivValue = (uint8)((attValue & SDADC_ATT_ADC_DIV_LV_MASK) >> SDADC_ATT_ADC_DIV_LV_SHIFT);

    attVcomSelValue = (uint8)((attValue & SDADC_ATT_VCOM_SEL_LV_MASK) >> SDADC_ATT_VCOM_SEL_LV_SHIFT);

    SDADC_ATT_SetAnalogModuleCfg(BasePtr, 1U, attVcomSelValue, attClkDivValue);

    SDADC_RES_SetResistorSelChan(BasePtr, 0U, 0U);

    SDADC_CTRL_SetSdadcEnDis(BasePtr, FALSE);

    SDADC_CH_WRAP_SetChannelDefault(BasePtr, 6U, 0U);

    SDADC_GAINCORR_SetCorrection(BasePtr, 0U, 0U);

    SDADC_GAINCAL_SetMultiFactor(BasePtr, 0x1000U);

    SDADC_FCFGC_SetCICFilterDecFactor(BasePtr, 5U);

    SDADC_FCFGC_SetCICFilterStartVal(BasePtr, 7U);

    SDADC_FCNTC_SetCICFilterDecCounter(BasePtr, 5U);

    SDADC_OFFCOMP_SetOffsetVal(BasePtr, 0U);

    SDADC_FCFGM_SetFIR0FilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetFIR1FilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetOvershootCompenEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetFIR1FilterDecRate(BasePtr, 0U);

    SDADC_FCFGM_SetCICFilterMode(BasePtr, 0U);

    SDADC_FCFGM_SetPrefilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetBoundaryComparatorEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetExtMeshClkEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetOffsetCompenFilterEn(BasePtr, 0U);

    SDADC_FCFGM_SetChannelWraparoundEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetDifferenceEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetCalibEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetFifoWaterMarkerIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetFifoOverFlowIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetDataOverFlowIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetDMAReqEnDis(BasePtr, FALSE);

    SDADC_FCFG_SetFifoSize(BasePtr, 0x40U);

    SDADC_FCFG_SetFifoWaterMarkerVal(BasePtr, 0x20U);

    SDADC_FCFG_SetInfoEnDis(BasePtr, FALSE);

    SDADC_FCFG_SetSignEnDis(BasePtr, FALSE);

    SDADC_FCDIS_SetFilterChainDiscardEnDis(BasePtr, TRUE);

    SDADC_FCDIS_SetFilterChainDiscardNum(BasePtr, 0x80U);

    SDADC_CTRL_SetSdadcEnDis(BasePtr, TRUE);





    /*GAIN_CAL_P*/
    while(gain_sft_mask != (uint32)0U)
	{
    	SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);

		SDADC_GAINCORR_SetCorrection(BasePtr, (uint16)gain_corr_p, 0x07U);

		SDADC_STCFG_SetSoftTrigEn(BasePtr);

		while(SDADC_WMINTSTAT_GetWaterMarkerIntState(BasePtr) == 0U)
		{
			;
		}

		hard_data = SDADC_FDATA_GetFifoData(BasePtr);

	    hard_data = hard_data & 0x0000FFFFU;

	    SDADC_STCFG_ClearSoftTrig(BasePtr);

		delay(0x200U);

		SDADC_STCFG_SetFifoSoftReset(BasePtr);

		if(hard_data > 0x0007000U)
		{
			gain_corr_p = (gain_corr_p & (~gain_sft_mask)) | (gain_sft_mask >> 1);

		}
		else
		{
			gain_corr_p = gain_corr_p + (gain_sft_mask >> 1);
		}

		gain_sft_mask = gain_sft_mask >> 1;
	}

    /*GAIN_CAL_N*/
	gain_sft_mask = 0x1000U;

    SDADC_CH_WRAP_SetChannelDefault(BasePtr, 7U, 0U);

	while(gain_sft_mask != (uint32)0U)
	{
    	SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);

		SDADC_GAINCORR_SetCorrection(BasePtr, (uint16)gain_corr_n, 0x07U);

		SDADC_STCFG_SetSoftTrigEn(BasePtr);

		while(SDADC_WMINTSTAT_GetWaterMarkerIntState(BasePtr) == 0U)
		{
			;
		}

		hard_data = SDADC_FDATA_GetFifoData(BasePtr);

	    hard_data = hard_data & 0x0000FFFFU;

	    SDADC_STCFG_ClearSoftTrig(BasePtr);

		delay(0x200U);

		SDADC_STCFG_SetFifoSoftReset(BasePtr);

		if(hard_data < 0x0009000U)
		{
			gain_corr_n = (gain_corr_n & (~gain_sft_mask)) | (gain_sft_mask >> 1);
		}
		else
		{
			gain_corr_n = gain_corr_n + (gain_sft_mask >> 1);
		}

		gain_sft_mask = gain_sft_mask >> 1;
	}

	gain_corr = (gain_corr_p + gain_corr_n ) >> 1;

	return gain_corr ;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
static FUNC(uint32, SDADC_CODE) SDADC_LLD_CalculateOffset(CONST(Sdadc_InstanceType, SDADC_CONST) instance, VAR(uint32, SDADC_VAR) gainVal)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));

    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    VAR(uint32, SDADC_VAR) attValue;

    VAR(uint8, SDADC_VAR) attVcomSelValue, attClkDivValue;

	VAR(uint32, SDADC_VAR) offcmp_n1 = 0;

	VAR(uint16, SDADC_VAR) off_data;

	VAR(uint16, SDADC_VAR) abs_res;

    attValue = SDADC_ATT_GetAnalogModuleCfg(BasePtr);

    attClkDivValue = (uint8)((attValue & SDADC_ATT_ADC_DIV_LV_MASK) >> SDADC_ATT_ADC_DIV_LV_SHIFT);

    attVcomSelValue = (uint8)((attValue & SDADC_ATT_VCOM_SEL_LV_MASK) >> SDADC_ATT_VCOM_SEL_LV_SHIFT);

    SDADC_ATT_SetAnalogModuleCfg(BasePtr, 1U, attVcomSelValue, attClkDivValue);

    SDADC_RES_SetResistorSelChan(BasePtr, 0U, 0U);

    /*Step 1*/
    SDADC_CTRL_SetSdadcEnDis(BasePtr, FALSE);

    SDADC_CTRL_SetSdadcEnDis(BasePtr, TRUE);

    /*Step 2*/
    SDADC_CH_WRAP_SetChannelDefault(BasePtr, 5U, 0U);

    delay(0x200U);

    SDADC_GAINCORR_SetCorrection(BasePtr, (uint16)gainVal, 7U);

    SDADC_FCNTC_SetCICFilterDecCounter(BasePtr, 5U);

    SDADC_GAINCAL_SetMultiFactor(BasePtr, 0x1000U);

    SDADC_FCFGC_SetCICFilterDecFactor(BasePtr, 5U);

    SDADC_FCFGC_SetCICFilterStartVal(BasePtr, 6U);

    SDADC_FCFGM_SetFIR0FilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetFIR1FilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetOvershootCompenEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetFIR1FilterDecRate(BasePtr, 0U);

    SDADC_FCFGM_SetCICFilterMode(BasePtr, 0U);

    SDADC_FCFGM_SetPrefilterEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetBoundaryComparatorEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetExtMeshClkEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetOffsetCompenFilterEn(BasePtr, 0x4U);

    SDADC_FCFGM_SetChannelWraparoundEnDis(BasePtr, FALSE);

    SDADC_FCFGM_SetDifferenceEnDis(BasePtr, TRUE);

    SDADC_FCFGM_SetCalibEnDis(BasePtr, FALSE);

    SDADC_OFFCOMP_SetOffsetVal(BasePtr, 0U);

    SDADC_IECFG_SetFifoWaterMarkerIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetFifoOverFlowIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetDataOverFlowIntEnDis(BasePtr, TRUE);

    SDADC_IECFG_SetDMAReqEnDis(BasePtr, FALSE);

    SDADC_FCFG_SetFifoSize(BasePtr, 0x40U);

    SDADC_FCFG_SetFifoWaterMarkerVal(BasePtr, 0x20U);

    SDADC_FCDIS_SetFilterChainDiscardEnDis(BasePtr, TRUE);

    SDADC_FCDIS_SetFilterChainDiscardNum(BasePtr, 0xFFU);

    /*Step 3*/
	SDADC_STCFG_SetSoftTrigEn(BasePtr);

    delay(0x200U);

    /*Step 4*/
	while(1)
	{
		while(SDADC_WMINTSTAT_GetWaterMarkerIntState(BasePtr) == FALSE)
		{

		}

		(void)SDADC_FDATA_GetFifoData(BasePtr);

	    /*Step 5*/
		off_data = (uint16)(SDADC_OFFCOMP_GetOffsetVal(BasePtr) & 0x0000FFFFU) ;
		if(((sint32)offcmp_n1 - (sint32)off_data) > (sint32)0U)
		{
			abs_res = (sint32)offcmp_n1 - (sint32)off_data;
		}
		else
		{
			abs_res = (sint32)off_data - (sint32)offcmp_n1;
		}
		
		if(abs_res > (sint32)0x03U)
		{
	    	SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);
			offcmp_n1 = off_data;

		}
		else
		{
			break;
		}
	}
	return off_data;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(uint32, SDADC_CODE) SDADC_LLD_GetFifoData(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;
    if(instance_l >= ADC_SDADC_MAX_INSTANCE)
    {
        return 0;
    }
    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];
    return SDADC_FDATA_GetFifoData(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_SetSoftTrigger(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

	SDADC_STCFG_SetSoftTrigEn(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(boolean, SDADC_CODE) SDADC_LLD_GetWaterMarkerIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    VAR(boolean, SDADC_VAR) ret;

    ret = (SDADC_WMINTSTAT_GetWaterMarkerIntState(BasePtr) != 0U) ? (boolean)TRUE : (boolean)FALSE;

    return ret;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ClearWaterMarkerIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_WMINTSTAT_ClearWaterMarkerIntState(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(boolean, SDADC_CODE) SDADC_LLD_GetDataOverFlowIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    VAR(boolean, SDADC_VAR) ret;

    ret = (SDADC_OVINTSTAT_GetDataOverFlowIntState(BasePtr) != 0U) ? (boolean)TRUE : (boolean)FALSE;

    return ret;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ClearDataOverFlowIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_OVINTSTAT_ClearDataOverFlowIntState(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(boolean, SDADC_CODE) SDADC_LLD_GetFifoOverFlowIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    VAR(boolean, SDADC_VAR) ret;

    ret = (SDADC_OVINTSTAT_GetFifoOverFlowIntState(BasePtr) != 0U) ? (boolean)TRUE : (boolean)FALSE;

    return ret;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ClearFifoOverFlowIntState(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_OVINTSTAT_ClearFifoOverFlowIntState(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_SetInterruptState(CONST(Sdadc_InstanceType, SDADC_CONST) instance, VAR(Sdadc_InterruptType, SDADC_VAR) intType, VAR(boolean, SDADC_VAR) intState)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    if(SDADC_INT_WATERMARKER == intType)
    {
        SDADC_IECFG_SetFifoWaterMarkerIntEnDis(BasePtr, intState);
    }
    else if(SDADC_INT_DATAOVERRUN == intType)
    {
    	SDADC_IECFG_SetDataOverFlowIntEnDis(BasePtr, intState);
    }
    else if(SDADC_INT_FIFOOVERRUN == intType)
    {
    	SDADC_IECFG_SetFifoOverFlowIntEnDis(BasePtr, intState);
    }
    else
    {
        /*Null*/
    }
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ResetFifo(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    SDADC_STCFG_SetFifoSoftReset(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) SDADC_LLD_ConfigDma \
(
	CONST(Sdadc_InstanceType, SDADC_CONST) instance, \
	VAR(Sdadc_DmaCfgType, SDADC_VAR) config \
)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];
    (void)BasePtr;

    VAR(uint8, SDADC_VAR) dmaChannel;

    VAR(uint32, SDADC_VAR) sdadc_dma_src;

    dmaChannel = config.DmaCh;


	switch(instance)
	{
		case SDADC_INSTANCE_0:
		{
			if(dmaChannel <= 7U)
			{
				sdadc_dma_src = (uint32)DMAMUX0_ADC_SD_0_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_0_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_1:
		{
			if((dmaChannel >= 16U)&&(dmaChannel <= 23U))
			{
				sdadc_dma_src = (uint32)DMAMUX2_ADC_SD_1_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_1_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_2:
		{
			if((dmaChannel >= 16U)&&(dmaChannel <= 23U))
			{
				sdadc_dma_src = (uint32)DMAMUX2_ADC_SD_2_EOC;
			}
			else if((dmaChannel >= 32U)&&(dmaChannel <= 47U))
			{
				sdadc_dma_src = (uint32)DMAMUX4_ADC_SD_2_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_2_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_3:
		{
			if(dmaChannel <= 7U)
			{
				sdadc_dma_src = (uint32)DMAMUX0_ADC_SD_3_EOC;
			}
			else if((dmaChannel >= 8U)&&(dmaChannel <= 15U))
			{
				sdadc_dma_src = (uint32)DMAMUX1_ADC_SD_3_EOC;
			}
			else if((dmaChannel >= 32U)&&(dmaChannel <= 47U))
			{
				sdadc_dma_src = (uint32)DMAMUX4_ADC_SD_3_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_3_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_4:
		{
			if((dmaChannel >= 48U)&&(dmaChannel <= 63U))
			{
				sdadc_dma_src = (uint32)DMAMUX5_ADC_SD_4_EOC;
			}
			else if((dmaChannel >= 96U)&&(dmaChannel <= 111U))
			{
				sdadc_dma_src = (uint32)DMAMUX8_ADC_SD_4_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_6:
		{
			if((dmaChannel >= 64U)&&(dmaChannel <= 79U))
			{
				sdadc_dma_src = (uint32)DMAMUX6_ADC_SD_6_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_6_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_7:
		{
			if((dmaChannel >= 64U)&&(dmaChannel <= 79U))
			{
				sdadc_dma_src = (uint32)DMAMUX6_ADC_SD_7_EOC;
			}
			else if((dmaChannel >= 80U)&&(dmaChannel <= 95U))
			{
				sdadc_dma_src = (uint32)DMAMUX7_ADC_SD_7_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		case SDADC_INSTANCE_8:
		{
			if((dmaChannel >= 64U)&&(dmaChannel <= 79U))
			{
				sdadc_dma_src = (uint32)DMAMUX6_ADC_SD_8_EOC;
			}
			else if((dmaChannel >= 96U)&&(dmaChannel <= 111U))
			{
				sdadc_dma_src = (uint32)DMAMUX8_ADC_SD_8_EOC;
			}
			else
			{
				return;
			}

			break;
		}

		default:
		{
			return;
		}
	}

    (void)EDMA_LLD_SetChannelSourceConfig(dmaChannel, sdadc_dma_src, FALSE);

    (void)EDMA_LLD_SetLoopTransferConfig(dmaChannel, &config.DmaConfigPtr);

    if(config.DreqEn == TRUE)
    {
        EDMA_SetChnDisRequestsOnTransferComplete(dmaChannel, TRUE);
    }

    (void) EDMA_LLD_SetUpCallback(dmaChannel,
    		config.Callback, config.CallbackParam);

    (void)EDMA_LLD_SetChannelRequest(dmaChannel);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(uint32, SDADC_CODE) SDADC_LLD_GetRecentAccumulation(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    return SDADC_IIVAL_GetInterIntegrationVal(BasePtr);
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(boolean, SDADC_CODE) SDADC_LLD_GetIntegrationEnable(CONST(Sdadc_InstanceType, SDADC_CONST) instance)
{
    DEV_ASSERT(((uint8)instance < ADC_SDADC_MAX_INSTANCE) && ((uint8)instance != 5U));
    VAR(Sdadc_InstanceType, SDADC_VAR) instance_l = instance;

    CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) BasePtr = Adc_SdadcBase[(uint8)instance_l];

    return ( SDADC_ISTAT_GetIntegrationEn(BasePtr) != 0U) ? (boolean)TRUE : (boolean)FALSE;
}
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#ifdef __cplusplus
}
#endif
