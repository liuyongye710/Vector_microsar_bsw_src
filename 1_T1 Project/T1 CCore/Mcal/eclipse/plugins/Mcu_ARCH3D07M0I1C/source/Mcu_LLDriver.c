/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC
*   Peripheral           : Mcu
*   Dependencies         : \
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Mcu_LLDriver.c
*   @version 3.0.0
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Mcu MCAL driver.
*
*   @addtogroup Mcu
*   @{
*/
/*PRQA S 3432,0492,4342,3397,4116,3399,2995,2991,2976,4461 EOF*/
/*PRQA S 1514,1258,2985,1257,2834,2844,1259,2834,4491,1281 EOF*/
/*PRQA S 1006,2982,3006,2020,2003,1840,1820,1330,2996,2992 EOF*/
/*PRQA S 1881,3398,4115,4558,2052 EOF*/
/*PRQA S 3400,3401,1862,1863 EOF*/
#ifdef __cplusplus
extern "C"{
#endif

#include "devassert.h"
#include "Mcu_LLDriver.h" /* PRQA S 0380 */
#if (MCU_HARDVER == 3)
#include "libSwap.h"
#endif
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif
/*====================================================================================================
HEAD FILE VERSION INFORMATION
====================================================================================================*/
#define MCU_LLD_VENDOR_ID_C                     176
#define MCU_LLD_AR_MAJOR_VER_C                  4
#define MCU_LLD_AR_MINOR_VER_C                  4
#define MCU_LLD_AR_PATCH_VER_C                  0
#define MCU_LLD_SW_MAJOR_VER_C                  3
#define MCU_LLD_SW_MINOR_VER_C                  0
#define MCU_LLD_SW_PATCH_VER_C                  0
/*====================================================================================================
FILE VERSION CHECKS
====================================================================================================*/
/* Check if current file and MCU header file are of the same vendor */
#if (MCU_LLD_VENDOR_ID != MCU_LLD_VENDOR_ID_C)
#error "NON-MATCHED DATA : MCU_LLD_VENDOR_ID_C"
#endif

/* Check if current file and MCU header file are of the same Autosar version */
#if (MCU_LLD_AR_MAJOR_VER != MCU_LLD_AR_MAJOR_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_AR_MAJOR_VER_C"
#endif
#if (MCU_LLD_AR_MINOR_VER != MCU_LLD_AR_MINOR_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_AR_MINOR_VER_C"
#endif
#if (MCU_LLD_AR_PATCH_VER != MCU_LLD_AR_PATCH_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_AR_PATCH_VER_C"
#endif

/* Check if current file and MCU header file are of the same Software version */
#if (MCU_LLD_SW_MAJOR_VER != MCU_LLD_SW_MAJOR_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_SW_MAJOR_VER_C"
#endif
#if (MCU_LLD_SW_MINOR_VER != MCU_LLD_SW_MINOR_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_SW_MINOR_VER_C"
#endif
#if (MCU_LLD_SW_PATCH_VER != MCU_LLD_SW_PATCH_VER_C)
#error "NON-MATCHED DATA : MCU_LLD_SW_PATCH_VER_C"
#endif

#define MCU_START_SEC_VAR_SHARED_INIT
#include "Mcu_MemMap.h"
volatile VAR(Mcu_CoreStatusType, MCU_VAR) Mcu_gCoreStatus[MCU_CORE_COUNT];
volatile VAR(Mcu_CoreStatusType, MCU_VAR) Mcu_gCoreStatus[MCU_CORE_COUNT] = {0U};
#define MCU_STOP_SEC_VAR_SHARED_INIT
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
static VAR(uint32, MCU_VAR) Mcu_gIrcoscClkFreq;    /* IRCOSC_CLK pMcu_Frequency          */
#define MCU_STOP_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
static VAR(uint32, MCU_VAR) Mcu_gXoscClkFreq;      /* XOSC_CLK pMcu_Frequency            */
#define MCU_STOP_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
static VAR(uint32, MCU_VAR) Mcu_gPll0Phi0ClkFreq;  /* PLL0_PHI1_CLK pMcu_Frequency       */
#define MCU_STOP_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
static VAR(uint32, MCU_VAR) Mcu_gPll0Phi1ClkFreq;  /* PLL0_PHI1_CLK pMcu_Frequency       */
#define MCU_STOP_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
static VAR(uint32, MCU_VAR) Mcu_gPll1Phi0ClkFreq;  /* PLL1_PHI0_CLK pMcu_Frequency       */
#define MCU_STOP_SEC_VAR_NO_INIT
#include "Mcu_MemMap.h"
#define MCU_START_SEC_VAR_SHARED_INIT
#include "Mcu_MemMap.h"
volatile VAR(uint32, MCU_VAR) Mcu_ReasonReg[2U];
volatile VAR(uint32, MCU_VAR) Mcu_ReasonReg[2U] = {0U};
#define MCU_STOP_SEC_VAR_SHARED_INIT
#include "Mcu_MemMap.h"



#if MCU_FCCU_ENABLE == STD_ON
#define MCU_START_SEC_VAR_INIT
#include "Mcu_MemMap.h"
static P2CONST(Mcu_FccuConfigType, MCU_CONST, MCU_APPL_CONST) Mcu_gFccuConfigPtr = NULL_PTR;
#define MCU_STOP_SEC_VAR_INIT
#include "Mcu_MemMap.h"
#endif

extern P2CONST(Mcu_ConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_gConfigPtr;
extern P2CONST(Mcu_ClockConfigType, MCU_VAR, MCU_APPL_DATA) Mcu_gClockConfigPtr;
extern VAR(Mcu_Rgm_ResetType, MCU_VAR) Mcu_gRgmConfiguration;

#if (MCU_HARDVER == 3)
extern VAR( uint8_t, AUTOMATIC) g_swapStatus;
#endif




/*!
 * @brief Enables clock sources from MC_ME
 *
 * This function enables/disables all clock sources from MC_ME
 *
 * @param[in] Mcu_SysClk Destination mode.
 * @param[in] Mcu_IrcEn   First IRCOSC clock source.
 * @param[in] Mcu_XoscEn  First XOSC clock source.
 * @param[in] Mcu_Pll0En   First PLL clock source.
 * @param[in] Mcu_Pll1En   Second PLL clock source.
 * @param[in] Mcu_ModeReg  register to be read/written
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_SetClockSources
(
    VAR(uint8, AUTOMATIC) Mcu_SysClk, \
    VAR(uint8, AUTOMATIC) Mcu_IrcEn, \
    VAR(uint8, AUTOMATIC) Mcu_XoscEn, \
    VAR(uint8, AUTOMATIC) Mcu_Pll0En, \
    VAR(uint8, AUTOMATIC) Mcu_Pll1En, \
    volatile P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) Mcu_ModeReg \
)
{
    VAR(uint32, MCU_VAR) regValue = *Mcu_ModeReg;

    regValue &= ~(MC_ME_GS_S_SYSCLK_MASK);/*PRQA S 4397*/
    regValue |= (uint8)(Mcu_SysClk & MC_ME_GS_S_SYSCLK_MASK);

    if(Mcu_IrcEn == TRUE)
    {
        regValue |= MC_ME_GS_S_IRC(1U);
    }
    else
    {
        regValue &= ~MC_ME_GS_S_IRC(1U);
    }

    if(Mcu_XoscEn == TRUE)
    {
        regValue |= MC_ME_GS_S_XOSC(1U);
    }
    else
    {
        regValue &= ~MC_ME_GS_S_XOSC(1U);
    }

    if(Mcu_Pll0En == TRUE)
    {
        regValue |= MC_ME_GS_S_PLL0(1U);
    }
    else
    {
        regValue &= ~MC_ME_GS_S_PLL0(1U);
    }

    if(Mcu_Pll1En == TRUE)
    {
        regValue |= MC_ME_GS_S_PLL1(1U);
    }
    else
    {
        regValue &= ~MC_ME_GS_S_PLL1(1U);
    }

    *Mcu_ModeReg = regValue;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*******************************************************************************
 * @brief      Get current core id
 * @param[in]  None
 * @param[out] None
 * @retval     Mcu_CoreType
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Mcu_CoreType, MCU_CODE) Mcu_LLD_Get_Core_Id(void)
{
    return (Mcu_CoreType)MFSPR(SPR_PIR); /* PRQA S 0342, 1006, 4342 */
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*******************************************************************************
 * @brief      Launch specified core
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_Launch_Core \
( \
    P2VAR(MC_ME_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    P2CONST(Mcu_CoreConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_CoreMode_ptr \
)
{
    pMcu_Base->CADDR0.R = (uint32)Mcu_CoreMode_ptr->Mcme_Caddr0_Config;
    pMcu_Base->CADDR1.R = (uint32)Mcu_CoreMode_ptr->Mcme_Caddr1_Config;
    pMcu_Base->CADDR2.R = (uint32)Mcu_CoreMode_ptr->Mcme_Caddr2_Config;
    pMcu_Base->CADDR3.R = (uint32)Mcu_CoreMode_ptr->Mcme_Caddr3_Config;
    pMcu_Base->CADDR4.R = (uint32)Mcu_CoreMode_ptr->Mcme_Caddr4_Config;
    /* set multi-core power mode */
    pMcu_Base->CCTL0.R = (uint16)Mcu_CoreMode_ptr->Mcme_Cctrl0_Config;
    pMcu_Base->CCTL1.R = (uint16)Mcu_CoreMode_ptr->Mcme_Cctrl1_Config;
    pMcu_Base->CCTL2.R = (uint16)Mcu_CoreMode_ptr->Mcme_Cctrl2_Config;
    pMcu_Base->CCTL3.R = (uint16)Mcu_CoreMode_ptr->Mcme_Cctrl3_Config;
    pMcu_Base->CCTL4.R = (uint16)Mcu_CoreMode_ptr->Mcme_Cctrl4_Config;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*******************************************************************************
 * @brief      Enter wait mode
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_Enter_Wait_Mode(void) /* PRQA S 1503 */
{
    PPCASM ("wait"); /* PRQA S 1006 */
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#ifdef ICACHE_ENABLE
/*******************************************************************************
 * @brief    [local_static] Enable or disable the ICACHE
 * @param[in]  uint32 u32Mcu_Switch_val
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Switch_ICache(VAR(uint32, AUTOMATIC) u32Mcu_Switch_val)
{
    VAR(Z7_SPR_L1CSR1_tag, MCU_VAR) Z7_SPR_L1CSR1;
    VAR(Z4_SPR_L1CSR1_tag, MCU_VAR) Z4_SPR_L1CSR1;
    VAR(Mcu_CoreType, MCU_VAR) eMcu_CoreId = Mcu_LLD_Get_Core_Id();
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    switch (eMcu_CoreId) 
    {
    case CORE_ID_Z7_0:
    case CORE_ID_Z7_1: 
    {
        Z7_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ L1CSR1 */
        Z7_SPR_L1CSR1.B.ICECE = u32Mcu_Switch_val;
        Z7_SPR_L1CSR1.B.ICE = u32Mcu_Switch_val;
        MTSPR(SPR_L1CSR1, Z7_SPR_L1CSR1.R); /* WRITE L1CSR1 */
        break;
    }
    case CORE_ID_Z4_2: 
    {
        Z4_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ L1CSR1 */
        Z4_SPR_L1CSR1.B.ICECE = u32Mcu_Switch_val;
        Z4_SPR_L1CSR1.B.ICE = u32Mcu_Switch_val;
        MTSPR(SPR_L1CSR1, Z4_SPR_L1CSR1.R); /* WRITE L1CSR1 */
        break;
    }
    default: 
    {
        Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        break;
    }
    }

    return (Std_ReturnType)Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Enable ICACHE
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Enable_ICache(void)
{
    return Mcu_LLD_Switch_ICache(ON);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Disable ICACHE
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Disable_ICache(void)
{
    return Mcu_LLD_Switch_ICache(OFF);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Invalid ICACHE by u32Mcu_Set and u32Mcu_way
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Invalid_ICache_Set_Way \
( \
    VAR(uint32, AUTOMATIC) u32Mcu_Set, \
    VAR(uint32, AUTOMATIC) u32Mcu_way \
)
{
    VAR(uint32, MCU_VAR)Mcu_Timeout;
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    Z7_SPR_L1FINV1_tag Z7_SPR_L1FINV1;
    Z7_SPR_L1CSR1_tag Z7_SPR_L1CSR1;
    Z4_SPR_L1FINV1_tag Z4_SPR_L1FINV1;
    Z4_SPR_L1CSR1_tag Z4_SPR_L1CSR1;
    Mcu_CoreType eMcu_CoreId = Mcu_LLD_Get_Core_Id();

    switch (eMcu_CoreId) 
    {
        case CORE_ID_Z7_0:
        case CORE_ID_Z7_1: 
        {
            Z7_SPR_L1FINV1.R = MFSPR(SPR_L1FINV1); /* READ SPR_L1FINV1 */
            Z7_SPR_L1FINV1.B.CWAY = u32Mcu_way;
            Z7_SPR_L1FINV1.B.CSET = u32Mcu_Set;
            MTSPR(SPR_L1FINV1, Z7_SPR_L1FINV1.R); /* WRITE SPR_L1FINV1 */
            Z7_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ SPR_L1CSR1 */
            Z7_SPR_L1CSR1.B.ICINV = 1U;
            MTSPR(SPR_L1CSR1, Z7_SPR_L1CSR1.R); /* WRITE Z7_SPR_L1CSR1 */
            Mcu_Timeout = 0U;
            do 
            {
                Z7_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ SPR_L1CSR1 */
            } while ((Z7_SPR_L1CSR1.B.ICINV == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS));
            break;
        }
        case CORE_ID_Z4_2: 
        {
            Z4_SPR_L1FINV1.R = MFSPR(SPR_L1FINV1); /* READ SPR_L1FINV1 */
            Z4_SPR_L1FINV1.B.CWAY = u32Mcu_way;
            Z4_SPR_L1FINV1.B.CSET = u32Mcu_Set;
            MTSPR(SPR_L1FINV1, Z4_SPR_L1FINV1.R); /* WRITE Z4_SPR_L1FINV1 */
            Z4_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ SPR_L1CSR1 */
            Z4_SPR_L1CSR1.B.ICINV = 1U;
            Mcu_Timeout = 0U;
            do 
            {
                Z4_SPR_L1CSR1.R = MFSPR(SPR_L1CSR1); /* READ SPR_L1CSR1 */
            } while ((Z4_SPR_L1CSR1.B.ICINV == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS));

            if(Mcu_Timeout >= MCU_TIMEOUT_LOOPS)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            break;
        }
        default: 
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Invalid ICACHE by address and length
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Invalid_ICache \
( \
    VAR(uint32, AUTOMATIC) u32Mcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Len \
)
{
    VAR(Std_ReturnType, MCU_VAR) u32Mcu_Ret = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_SetIdx = 0;
    VAR(uint32, MCU_VAR) u32Mcu_WayIdx = 0;
    VAR(uint32, MCU_VAR) u32Mcu_MaxAddr = u32Mcu_Base + u32Mcu_Len;
    VAR(Mcu_CoreType, MCU_VAR) eMcu_CoreId = Mcu_LLD_Get_Core_Id();;

    switch (eMcu_CoreId) 
    {
    case CORE_ID_Z7_0:
    case CORE_ID_Z7_1: 
    {
        for (u32Mcu_SetIdx = u32Mcu_Base / Z7_ICACHE_LINE;u32Mcu_SetIdx \
            < (((uint32)ALIGN_UP(u32Mcu_MaxAddr, Z7_ICACHE_LINE)) / Z7_ICACHE_LINE); u32Mcu_SetIdx++) 
        {
            for (u32Mcu_WayIdx = 0U; u32Mcu_WayIdx < Z7_ICACHE_WAY_NUM; u32Mcu_WayIdx++) 
            {
                u32Mcu_Ret |= \
                Mcu_LLD_Invalid_ICache_Set_Way(u32Mcu_SetIdx % Z7_ICACHE_SET_NUM, u32Mcu_WayIdx);
            }
        }
        break;
    }
    case CORE_ID_Z4_2: 
    {
        for (u32Mcu_SetIdx = u32Mcu_Base / Z4_ICACHE_LINE;u32Mcu_SetIdx \
            < (((uint32)ALIGN_UP(u32Mcu_MaxAddr, Z4_ICACHE_LINE)) / Z4_ICACHE_LINE); u32Mcu_SetIdx++) 
        {
            for (u32Mcu_WayIdx = 0U; u32Mcu_WayIdx < Z4_ICACHE_WAY_NUM; u32Mcu_WayIdx++) 
            {
                u32Mcu_Ret |= \
                Mcu_LLD_Invalid_ICache_Set_Way(u32Mcu_SetIdx % Z4_ICACHE_SET_NUM, u32Mcu_WayIdx);
            }
        }
        break;
    }
    default: 
    {
        u32Mcu_Ret = (Std_ReturnType)E_NOT_OK;
        break;
    }
    }

    return u32Mcu_Ret;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif
#ifdef DCACHE_ENABLE
/*******************************************************************************
 * @brief    [local_static] Enable or disable the DCACHE
 * @param[in]  uint32 u32Mcu_Switch_val
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Switch_DCache \
( \
    VAR(uint32, AUTOMATIC) u32Mcu_Switch_val \
)
{
    VAR(Z7_SPR_L1CSR0_tag, MCU_VAR) Z7_SPR_L1CSR0;
    VAR(Mcu_CoreType, MCU_VAR) eMcu_CoreId = Mcu_LLD_Get_Core_Id();
    VAR(Std_ReturnType, MCU_VAR)Mcu_RetVal = (Std_ReturnType)E_OK;
    switch (eMcu_CoreId) 
    {
        case CORE_ID_Z7_0:
        case CORE_ID_Z7_1:
        {
            Z7_SPR_L1CSR0.R = MFSPR(SPR_L1CSR0);
            Z7_SPR_L1CSR0.B.DCECE = u32Mcu_Switch_val;
            Z7_SPR_L1CSR0.B.DCE = u32Mcu_Switch_val;
            MTSPR(SPR_L1CSR0, Z7_SPR_L1CSR0.R);
            break;
        }
        case CORE_ID_Z4_2: 
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
        default:
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Enable DCACHE
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Enable_DCache(void)
{
    return Mcu_LLD_Switch_DCache(ON);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Disable DCACHE
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Disable_DCache(void)
{
    return Mcu_LLD_Switch_DCache(OFF);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Invalid DCACHE by u32Mcu_Set and u32Mcu_way
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Invalid_DCache_Set_Way \
( \
    VAR(uint32, AUTOMATIC) u32Mcu_Set, \
    VAR(uint32, AUTOMATIC) u32Mcu_way \
)
{
    VAR(uint32, MCU_VAR)Mcu_Timeout;
    VAR(Z7_SPR_L1FINV0_tag, MCU_VAR) Z7_SPR_L1FINV0;
    VAR(Z7_SPR_L1CSR0_tag, MCU_VAR) Z7_SPR_L1CSR0;
    VAR(Mcu_CoreType, MCU_VAR) eMcu_CoreId = Mcu_LLD_Get_Core_Id();
    VAR(Std_ReturnType, MCU_VAR)Mcu_RetVal = (Std_ReturnType)E_OK;
    switch (eMcu_CoreId) 
    {
        case CORE_ID_Z7_0:
        case CORE_ID_Z7_1: 
        {
            Z7_SPR_L1FINV0.R = MFSPR(SPR_L1FINV1);
            Z7_SPR_L1FINV0.B.CWAY = u32Mcu_way;
            Z7_SPR_L1FINV0.B.CSET = u32Mcu_Set;
            MTSPR(SPR_L1FINV1, Z7_SPR_L1FINV0.R);
            Z7_SPR_L1CSR0.R = MFSPR(SPR_L1CSR1);
            Z7_SPR_L1CSR0.B.DCINV = 1U;
            MTSPR(SPR_L1CSR1, Z7_SPR_L1CSR0.R);
            Mcu_Timeout = 0U;
            do 
            {
                Z7_SPR_L1CSR0.R = MFSPR(SPR_L1CSR1);
                Mcu_Timeout++;
            } while ((Z7_SPR_L1CSR0.B.DCINV == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS));
            break;
        }
        case CORE_ID_Z4_2: 
        {
            Mcu_RetVal =  (Std_ReturnType)E_NOT_OK;
        }
        default: 
        {
            Mcu_RetVal =  (Std_ReturnType)E_NOT_OK;
        }
    }

    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 * @brief      Invalid ICACHE by address and length
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Invalid_DCache \
( \
    VAR(uint32, AUTOMATIC) u32Mcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Len \
)
{
    VAR(uint32, MCU_VAR) u32Mcu_Ret = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_SetIdx = 0;
    VAR(uint32, MCU_VAR) u32Mcu_WayIdx = 0;
    VAR(uint32, MCU_VAR) u32Mcu_MaxAddr = u32Mcu_Base + u32Mcu_Len;
    VAR(Mcu_CoreType, MCU_VAR) eMcu_CoreId = Mcu_LLD_Get_Core_Id();

    switch (eMcu_CoreId) 
    {
        case CORE_ID_Z7_0:
        case CORE_ID_Z7_1: 
        {
            for (u32Mcu_SetIdx = u32Mcu_Base / Z7_DCACHE_LINE;u32Mcu_SetIdx < ((uint32)ALIGN_UP(u32Mcu_MaxAddr, Z7_DCACHE_LINE) / Z7_DCACHE_LINE); u32Mcu_SetIdx++) 
            {
                for (u32Mcu_WayIdx = 0U; u32Mcu_WayIdx < Z7_DCACHE_WAY_NUM; u32Mcu_WayIdx++) 
                {
                    u32Mcu_Ret |= Mcu_LLD_Invalid_DCache_Set_Way(u32Mcu_SetIdx % Z7_DCACHE_SET_NUM, u32Mcu_WayIdx);
                }
            }
            break;
        }
        case CORE_ID_Z4_2: 
        {
            u32Mcu_Ret =  (Std_ReturnType)E_NOT_OK;
            break;
        }
        default: 
        {
            u32Mcu_Ret =  (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return u32Mcu_Ret;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif

/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_SetIrc
 * Description   : Configures IRC clock source
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_SetIrc \
( \
    P2CONST(Mcu_IrcConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_IrcConfigPtr \
)
{
    IRCOSC_StPtr->CTL.R = Mcu_IrcConfigPtr->Mcu_FircCfg;
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
    IRCOSC_StPtr->SCTL.R = Mcu_IrcConfigPtr->Mcu_SircCfg;
    #endif
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets XOSC clock source
 *
 * This function sets XOSC clock source
 *
 * @param[in] pMcu_Base             Register pMcu_Base address for the XOSC u32Mcu_Instance.
 * @param[in] u32Mcu_bypass           Crystal is used when bypass is zero
 * @param[in] bypassOption     Single ended mode is used when bypass option is different from zero, otherwise differential bypass option is used
 * @param[in] u32Mcu_StartupDelay     Startup delay
 * @param[in] mode             Xosc mode
 * @param[in] monitor          XOSC is not monitor or not
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGMCS_SetXosc \
( \
    P2VAR(XOSC_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_bypass, \
    VAR(uint32, AUTOMATIC) u32Mcu_StartupDelay \
)
{
    pMcu_Base->CTL.B.OSCBYP = u32Mcu_bypass;
    pMcu_Base->CTL.B.EOCV = (uint8)u32Mcu_StartupDelay;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_SetXosc
 * Description   : Configures XOSC clock source
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_SetXosc \
( \
    P2CONST(Mcu_XoscConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_XoscConfig \
)
{

    CGMCS_SetXosc(XOSC_StPtr, (pMcu_XoscConfig->bypassOption != XOSC_USE_CRYSTAL) ? 1UL : 0UL, \
                  (uint32)pMcu_XoscConfig->startupDelay);
    if(pMcu_XoscConfig->Mcu_xoscInterruptEn == TRUE)
    {
        XOSC_StPtr->CTL.B.M_OSC = TRUE;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC3 u32Mcu_Selector
 *
 * This function sets CGM AC3 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetAC3 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC3_SC.B.SELCTL = u32Mcu_Selector;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC4 u32Mcu_Selector
 *
 * This function sets CGM AC4 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetAC4 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC4_SC.B.SELCTL = u32Mcu_Selector;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets PLL Divider Register
 *
 * This function sets PLL Divider Register
 *
 * @param[in] pMcu_Base             Register pMcu_Base address for the PLLDIG u32Mcu_Instance.
 * @param[in] u32Mcu_Instance         Instance number
 * @param[in] u32Mcu_Phi0Divider      first output u32Mcu_Divider
 * @param[in] u32Mcu_Phi1Divider      second output u32Mcu_Divider
 * @param[in] u32Mcu_Predivider       Predivider
 * @param[in] u32Mcu_MulFactorDiv     Multiplier factor u32Mcu_Divider
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGMCS_PLLDivider \
( \
    P2VAR(PLLDIG_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Instance, \
    VAR(uint32, AUTOMATIC) u32Mcu_Phi0Divider, \
    VAR(uint32, AUTOMATIC) u32Mcu_Phi1Divider, \
    VAR(uint32, AUTOMATIC) u32Mcu_Predivider, \
    VAR(uint32, AUTOMATIC) u32Mcu_MulFactorDiv \
)
{
    /* Configure u32Mcu_Divider */
    if(u32Mcu_Instance == (uint32)0U)
    {
        pMcu_Base->PLL0DV.B.RFDPHI = u32Mcu_Phi0Divider;
        pMcu_Base->PLL0DV.B.RFDPHI1 = u32Mcu_Phi1Divider;
        pMcu_Base->PLL0DV.B.PREDIV = u32Mcu_Predivider;
        pMcu_Base->PLL0DV.B.MFD = u32Mcu_MulFactorDiv;
    }
    else 
    {
        pMcu_Base->PLL1DV.B.RFDPHI = u32Mcu_Phi0Divider;
        pMcu_Base->PLL1DV.B.MFD = u32Mcu_MulFactorDiv;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets PLL Fractional Divider
 *
 * This function sets PLL Fractional Divider
 *
 * @param[in] pMcu_Base              Register pMcu_Base address for the PLLDIG u32Mcu_Instance.
 * @param[in] bMcu_Enable            Enable fractional loop u32Mcu_Divider
 * @param[in] u32Mcu_FracDivider       Fractional loop u32Mcu_Divider value
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGMCS_SetPLLFractionalDivider \
( \
    P2VAR(PLLDIG_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_FracDivider \
)
{
    pMcu_Base->PLL1FD.B.FDEN = ((bMcu_Enable == TRUE) ? 1UL : 0UL);
    pMcu_Base->PLL1FD.B.FRCDIV = u32Mcu_FracDivider;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Configures PLL Modulation
 *
 * This function sets PLL Modulation
 *
 * @param[in] pMcu_Base              Register pMcu_Base address for the PLLDIG u32Mcu_Instance.
 * @param[in] bMcu_Enable            Enable fractional loop u32Mcu_Divider
 * @param[in] u32Mcu_FracDivider       Fractional loop u32Mcu_Divider value
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGMCS_ConfigurePllModulation \
( \
    P2VAR(PLLDIG_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_ModulationType, \
    VAR(uint32, AUTOMATIC) u32Mcu_ModulationPeriod, \
    VAR(uint32, AUTOMATIC) u32Mcu_IncrementStep \
)
{
    if(bMcu_Enable == TRUE)
    {
        pMcu_Base->PLL1FM.B.MODEN = 1UL;
        PLLDIG.PLL_CFG1 = 0xFFFFFFF2UL;
    }
    else
    {
        pMcu_Base->PLL1FM.B.MODEN = 0UL;
    }
    pMcu_Base->PLL1FM.B.MODSEL = u32Mcu_ModulationType;
    pMcu_Base->PLL1FM.B.MODPRD = u32Mcu_ModulationPeriod;
    pMcu_Base->PLL1FM.B.INCSTP = u32Mcu_IncrementStep;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_SetPll
 * Description   : Configures ARM PLL clock source
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_SetPll \
( \
    P2CONST(Mcu_PlldigConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_Config, \
    P2CONST(Mcu_CgmConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_CgmConfig, \
    VAR(uint32, AUTOMATIC) u32Mcu_Instance \
)
{
    VAR(uint32, MCU_VAR) u32Mcu_Phi0Divider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Phi1Divider = 0U;

    switch (u32Mcu_Instance)
    {
        case 0U:
        {
            CGM_SetAC3(MC_CGM_StPtr, (uint32)pMcu_CgmConfig->ac3_sc);
            break;
        }
        case 1U:
        {
            CGM_SetAC4(MC_CGM_StPtr, (uint32)pMcu_CgmConfig->ac4_sc);
            break;
        }
        default:
        {    
            /* Invalid PLL u32Mcu_Instance */
            break;
        }
    }

    u32Mcu_Phi0Divider = ((uint32)pMcu_Config->phi0Divider);
    u32Mcu_Phi1Divider = ((uint32)pMcu_Config->phi1Divider);

    /* Configure PLL */
    CGMCS_PLLDivider
    (
        PLLDIG_StPtr, \
        u32Mcu_Instance, \
        u32Mcu_Phi0Divider, \
        u32Mcu_Phi1Divider, \
        (uint32)pMcu_Config->predivider, \
        (uint32)pMcu_Config->mulFactorDiv \
    );

    if (u32Mcu_Instance == 1U)
    {
        /* Write FRCDIV - fractional u32Mcu_Divider. */
        CGMCS_SetPLLFractionalDivider \
        ( \
            PLLDIG_StPtr, \
            pMcu_Config->fracDivider, \
            pMcu_Config->fracDividerValue \
        );

        /* Configure modulation */
        CGMCS_ConfigurePllModulation \
        ( \
            PLLDIG_StPtr, pMcu_Config->modulation, (uint32)pMcu_Config->modulationType, \
            pMcu_Config->modulationPeriod, pMcu_Config->incrementStep \
        );
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM system clock first u32Mcu_Divider
 *
 * This function sets CGM system clock first u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetSC_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->SC_DC0.R = (MC_CGM_SC_DC0_DE(bMcu_Enable) | MC_CGM_SC_DC0_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM system clock 2nd u32Mcu_Divider
 *
 * This function sets CGM system clock 2nd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetSC_DC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->SC_DC1.R = (MC_CGM_SC_DC1_DE(bMcu_Enable) | MC_CGM_SC_DC1_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM system clock 3rd u32Mcu_Divider
 *
 * This function sets CGM system clock 3rd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetSC_DC2 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->SC_DC2.R = (MC_CGM_SC_DC2_DE(bMcu_Enable) | MC_CGM_SC_DC2_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM system clock 4th u32Mcu_Divider
 *
 * This function sets CGM system clock 4th u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetSC_DC3 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->SC_DC3.R = (MC_CGM_SC_DC3_DE(bMcu_Enable) | MC_CGM_SC_DC3_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM system clock 5th u32Mcu_Divider
 *
 * This function sets CGM system clock 5th u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) CGM_SetSC_DC4 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->SC_DC4.R = (MC_CGM_SC_DC4_DE(bMcu_Enable) | MC_CGM_SC_DC4_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_ConfigureSystemClockDividers
 * Description   : Configures system clocks
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_ConfigureSystemClockDividers(
    P2CONST(Mcu_CgmConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_Config )
{
    VAR(uint8, MCU_VAR) bMcu_State = TRUE;
    /*! System clock u32Mcu_Divider ratios will change with next update.
     *  Not required for Cut 1.*/
    MC_CGM_StPtr->SC_DIV_RC.R = 0x00000001UL;
    /*! System clock u32Mcu_Divider ratios updated on writing MC_CGM_StPtr->DIV_UPD_TRIG.
     * Not required for Cut 1. */
    MC_CGM_StPtr->DIV_UPD_TYPE.R = 0x80000000UL;

    VAR(uint32, MCU_VAR)Mcu_Timeout = 0u;

    /* Check hsm enable */
    if (0u != SSCM.UOPS.B.HSE)
    {
    	HSM.ALG_PARAM[1] = pMcu_Config->sc_dc1;
		HSM.HOST_FLAG = 0x000100AAUL;

		/* Wait for the service to complete */
		while ((HSM.HOST_FLAG == 0x000100AAUL) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
		{
			Mcu_Timeout++;
		}
    }

    /* First system clock u32Mcu_Divider */
    bMcu_State = (pMcu_Config->sc_dc0 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetSC_DC0
    (
        MC_CGM_StPtr, \
        bMcu_State, \
        (uint32) pMcu_Config->sc_dc0
    );

    /* Second system clock u32Mcu_Divider */
    bMcu_State = (pMcu_Config->sc_dc1 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetSC_DC1
    (
        MC_CGM_StPtr, \
        bMcu_State, \
        (uint32) pMcu_Config->sc_dc1 \
    );

    /* Third system clock u32Mcu_Divider */
    bMcu_State = (pMcu_Config->sc_dc2 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetSC_DC2
    (
        MC_CGM_StPtr, \
        bMcu_State, \
        (uint32) pMcu_Config->sc_dc2 \
    );

    /* 4th system clock u32Mcu_Divider */
    bMcu_State = (pMcu_Config->sc_dc3 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetSC_DC3
    (
        MC_CGM_StPtr, \
        bMcu_State, \
        (uint32) pMcu_Config->sc_dc3
    );

    /* 5th system clock u32Mcu_Divider */
    bMcu_State = (pMcu_Config->sc_dc4 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetSC_DC4
    (
        MC_CGM_StPtr, \
        bMcu_State, \
        (uint32) pMcu_Config->sc_dc4
    );

 // ! System clock u32Mcu_Divider ratio updates triggered.  Not required for Cut 1.
    MC_CGM_StPtr->DIV_UPD_TRIG.R = 0xfeedfaceUL;
 // ! Wait for System Clock Divider Update Status == 0. Not required for Cut 1.
    Mcu_Timeout = 0U;
    while ((MC_CGM_StPtr->DIV_UPD_STAT.B.SYS_UPD_STAT == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
    {
        Mcu_Timeout++;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 u32Mcu_Selector
 *
 * This function sets CGM AC0 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC0_SC.R = MC_CGM_AC0_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 1st u32Mcu_Divider
 *
 * This function sets CGM AC0 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) b32Mcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC0_DC0.R = (MC_CGM_AC0_DC0_DE(b32Mcu_Enable) | MC_CGM_AC0_DC0_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 2nd u32Mcu_Divider
 *
 * This function sets CGM AC0 2nd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0_DC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC0_DC1.R = \
        (MC_CGM_AC0_DC1_DE(bMcu_Enable) | MC_CGM_AC0_DC1_DIV(u32Mcu_DivValue) | MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 3rd u32Mcu_Divider
 *
 * This function sets CGM AC0 3rd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0_DC2 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC0_DC2.R = \
        (MC_CGM_AC0_DC2_DE(bMcu_Enable) | MC_CGM_AC0_DC2_DIV(u32Mcu_DivValue) | MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 4th u32Mcu_Divider
 *
 * This function sets CGM AC0 4th u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0_DC3 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC0_DC3.R = \
        (MC_CGM_AC0_DC3_DE(bMcu_Enable) | MC_CGM_AC0_DC3_DIV(u32Mcu_DivValue) | MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC0 5th u32Mcu_Divider
 *
 * This function sets CGM AC0 5th u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC0_DC4 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC0_DC4.R = (MC_CGM_AC0_DC4_DE(bMcu_Enable) | MC_CGM_AC0_DC4_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC1 u32Mcu_Selector
 *
 * This function sets CGM AC1 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC1_SC.R = MC_CGM_AC1_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC1 1st u32Mcu_Divider
 *
 * This function sets CGM AC1 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC1_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC1_DC0.R = (MC_CGM_AC1_DC0_DE(bMcu_Enable) | MC_CGM_AC1_DC0_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC2 1st u32Mcu_Divider
 *
 * This function sets CGM AC2 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC2_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC2_DC0.R = (MC_CGM_AC2_DC0_DE(bMcu_Enable) | MC_CGM_AC2_DC0_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC2 2nd u32Mcu_Divider
 *
 * This function sets CGM AC2 2nd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC2_DC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC2_DC1.R = (MC_CGM_AC2_DC1_DE(bMcu_Enable) | MC_CGM_AC2_DC1_DIV(u32Mcu_DivValue));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC5 1st u32Mcu_Divider
 *
 * This function sets CGM AC5 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivFmt \
)
{
    pMcu_Base->AC5_DC0.R = (MC_CGM_AC5_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC5_DC0_DE(bMcu_Enable));
    pMcu_Base->AC5_DC0.R |= u32Mcu_DivFmt;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC5 2nd u32Mcu_Divider
 *
 * This function sets CGM AC5 2nd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_DC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_DC1.R = (MC_CGM_AC5_DC1_DIV(u32Mcu_DivValue) | MC_CGM_AC5_DC1_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC5 3rd u32Mcu_Divider
 *
 * This function sets CGM AC5 3rd u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_DC2 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_DC2.R = (MC_CGM_AC5_DC2_DIV(u32Mcu_DivValue) | MC_CGM_AC5_DC2_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC0.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC1 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC1.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC2 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC2.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC10 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC10.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC11 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC11.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC12 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    VAR(uint8, MCU_VAR) bMcu_State = TRUE;
    bMcu_State = (bMcu_Enable == TRUE) ? TRUE : FALSE;
    pMcu_Base->AC5_CDC12.R = \
        (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_State));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC13 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC13.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC20 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC20.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC21 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC21.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC22 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC22.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC5_CDC23 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC5_CDC23.R = (MC_CGM_AC5_CDCx_DIV(u32Mcu_DivValue) | MC_CGM_AC5_CDCx_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC6 u32Mcu_Selector
 *
 * This function sets CGM AC6 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC6 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC6_SC.R = MC_CGM_AC6_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC6 1st u32Mcu_Divider
 *
 * This function sets CGM AC6 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC6_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC6_DC0.R = (MC_CGM_AC6_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC6_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC7 u32Mcu_Selector
 *
 * This function sets CGM AC7 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC7 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC7_SC.R = MC_CGM_AC7_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC7 1st u32Mcu_Divider
 *
 * This function sets CGM AC7 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC7_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC7_DC0.R = (MC_CGM_AC7_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC7_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC8 u32Mcu_Selector
 *
 * This function sets CGM AC8 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC8 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC8_SC.R = MC_CGM_AC8_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC8 1st u32Mcu_Divider
 *
 * This function sets CGM AC8 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC8_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC8_DC0.R = (MC_CGM_AC8_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC8_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC9 u32Mcu_Selector
 *
 * This function sets CGM AC9 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC9 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC9_SC.R = MC_CGM_AC9_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC9 1st u32Mcu_Divider
 *
 * This function sets CGM AC9 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC9_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC9_DC0.R = (MC_CGM_AC9_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC9_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC10 u32Mcu_Selector
 *
 * This function sets CGM AC10 u32Mcu_Selector
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] u32Mcu_Selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC10 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC10_SC.R = MC_CGM_AC10_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC10 1st u32Mcu_Divider
 *
 * This function sets CGM AC10 1st u32Mcu_Divider
 *
 * @param[in] pMcu_Base     Register pMcu_Base address for the CGM u32Mcu_Instance.
 * @param[in] bMcu_Enable   Enable u32Mcu_Divider.
 * @param[in] u32Mcu_DivValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC10_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC10_DC0.R = (MC_CGM_AC10_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC10_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
/*!
 * @brief Sets CGM AC11 selector
 *
 * This function sets CGM AC11 selector
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC11( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC11_SC.R  = MC_CGM_AC11_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC11 1st divider
 *
 * This function sets CGM AC11 1st divider
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] enable   Enable divider.
 * @param[in] divValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC11_DC0( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue \
)
{
    pMcu_Base->AC11_DC0.R = (MC_CGM_AC11_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC11_DC0_DE(bMcu_Enable));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC12 selector
 *
 * This function sets CGM AC12 selector
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] selector Selector value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC12( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint32, AUTOMATIC) u32Mcu_Selector \
)
{
    pMcu_Base->AC12_SC.R  = MC_CGM_AC12_SC_SELCTL(u32Mcu_Selector);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC12 1st divider
 *
 * This function sets CGM AC12 1st divider
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] enable   Enable divider.
 * @param[in] divValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC12_DC0 \
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC12_DC0.R \
        = (MC_CGM_AC12_DC0_DIV(u32Mcu_DivValue) | MC_CGM_AC12_DC0_DE(bMcu_Enable) | MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*!
 * @brief Sets CGM AC12 2nd divider
 *
 * This function sets CGM AC12 2nd divider
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] enable   Enable divider.
 * @param[in] divValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC12_DC1
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC12_DC1.R \
        = (MC_CGM_AC12_DC1_DIV(u32Mcu_DivValue) | MC_CGM_AC12_DC1_DE(bMcu_Enable)|MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Sets CGM AC12 3rd divider
 *
 * This function sets CGM AC12 3rd divider
 *
 * @param[in] base     Register base address for the CGM instance.
 * @param[in] enable   Enable divider.
 * @param[in] divValue Divider value.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) CGM_SetAC12_DC2
( \
    P2VAR(MC_CGM_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(uint8, AUTOMATIC) bMcu_Enable, \
    VAR(uint32, AUTOMATIC) u32Mcu_DivValue, \
    VAR(uint32, AUTOMATIC) u32Mcu_div_fmt \
)
{
    pMcu_Base->AC12_DC2.R \
        = (MC_CGM_AC12_DC2_DIV(u32Mcu_DivValue) | MC_CGM_AC12_DC2_DE(bMcu_Enable)|MC_CGM_ACX_DIV_FMT(u32Mcu_div_fmt));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif
/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_ConfigureAuxiliarySelectorsAndDividers
 * Description   : Configures auxiliary clocks
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_ConfigureAuxiliarySelectorsAndDividers \
( \
    P2CONST(Mcu_CgmConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_Config \
)
{
    VAR(uint8, MCU_VAR) bMcu_State = TRUE;
    /* Configure auxiliary clock u32Mcu_Selector 0 and dividers 0, 1, 2. */
    CGM_SetAC0(MC_CGM_StPtr, (uint32)pMcu_Config->ac0_sc);
    bMcu_State = (pMcu_Config->ac0_dc0 != CGM_CLOCK_DISABLE4) ? TRUE : FALSE;
    CGM_SetAC0_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac0_dc0);
    bMcu_State = (pMcu_Config->ac0_dc1 != CGM_CLOCK_DISABLE7) ? TRUE : FALSE;
    CGM_SetAC0_DC1(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac0_dc1, pMcu_Config->ac0_dc1_fmt);
    bMcu_State = (pMcu_Config->ac0_dc2 != CGM_CLOCK_DISABLE7) ? TRUE : FALSE;
    CGM_SetAC0_DC2(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac0_dc2, pMcu_Config->ac0_dc2_fmt);
    bMcu_State = (pMcu_Config->ac0_dc3 != CGM_CLOCK_DISABLE9) ? TRUE : FALSE;
    CGM_SetAC0_DC3(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac0_dc3, pMcu_Config->ac0_dc3_fmt);
    bMcu_State = (pMcu_Config->ac0_dc4 != CGM_CLOCK_DISABLE4) ? TRUE : FALSE;
    CGM_SetAC0_DC4(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac0_dc4);

    /* Configure auxiliary clock u32Mcu_Selector 1 and dividers 0, 1. */
    CGM_SetAC1(MC_CGM_StPtr, (uint32)pMcu_Config->ac1_sc);
    bMcu_State = (pMcu_Config->ac1_dc0 != CGM_CLOCK_DISABLE7) ? TRUE : FALSE;
    CGM_SetAC1_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac1_dc0);

    /* Configure auxiliary clock dividers 0, 1. */
    bMcu_State = (pMcu_Config->ac2_dc0 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetAC2_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac2_dc0);
    bMcu_State = (pMcu_Config->ac2_dc1 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetAC2_DC1(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac2_dc1);

#ifdef MCU_CGM_SET_AC3_AC4
    /* Configure auxiliary clock u32Mcu_Selector 3 and dividers - . */
    CGM_SetAC3(MC_CGM_StPtr, (uint32)pMcu_Config->ac3_sc);

     /* Configure auxiliary clock u32Mcu_Selector 4 and dividers - . */
    CGM_SetAC4(MC_CGM_StPtr, (uint32)pMcu_Config->ac4_sc);
#endif

    /* Configure auxiliary clock  dividers 0, 1, 2. */
    bMcu_State = (pMcu_Config->ac5_dc0 != CGM_CLOCK_DISABLE13) ? TRUE : FALSE;
    CGM_SetAC5_DC0 \
    ( \
        MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_dc0, pMcu_Config->ac5_dc0_fmt \
    );
    bMcu_State = (pMcu_Config->ac5_dc1 != CGM_CLOCK_DISABLE8) ? TRUE : FALSE;
    CGM_SetAC5_DC1(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_dc1);
    bMcu_State = (pMcu_Config->ac5_dc2 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_DC2(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_dc2);
    bMcu_State = (pMcu_Config->ac5_cdc0 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc0);
    bMcu_State = (pMcu_Config->ac5_cdc1 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC1(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc1);
    bMcu_State = (pMcu_Config->ac5_cdc2 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC2(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc2);
    bMcu_State = (pMcu_Config->ac5_cdc10 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC10(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc10);
    bMcu_State = (pMcu_Config->ac5_cdc11 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC11(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc11);
    bMcu_State = (pMcu_Config->ac5_cdc12 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC12(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc12);
    bMcu_State = (pMcu_Config->ac5_cdc13 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC13(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc13);
    bMcu_State = (pMcu_Config->ac5_cdc20 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC20(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc20);
    bMcu_State = (pMcu_Config->ac5_cdc21 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC21(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc21);
    bMcu_State = (pMcu_Config->ac5_cdc22 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC22(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc22);
    bMcu_State = (pMcu_Config->ac5_cdc23 != CGM_CLOCK_DISABLE10) ? TRUE : FALSE;
    CGM_SetAC5_CDC23(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac5_cdc23);

    /* Configure auxiliary clock u32Mcu_Selector 6 and dividers 0. */
    CGM_SetAC6(MC_CGM_StPtr, (uint32)pMcu_Config->ac6_sc);
    bMcu_State = (pMcu_Config->ac6_dc0 != CGM_CLOCK_DISABLE9) ? TRUE : FALSE;
    CGM_SetAC6_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac6_dc0);

    /* Configure auxiliary clock u32Mcu_Selector 7 and dividers 0. */
    CGM_SetAC7(MC_CGM_StPtr, (uint32)pMcu_Config->ac7_sc);
    bMcu_State = (pMcu_Config->ac7_dc0 != CGM_CLOCK_DISABLE9) ? TRUE : FALSE;
    CGM_SetAC7_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac7_dc0);

    /* Configure auxiliary clock u32Mcu_Selector 8 and dividers 0. */
    CGM_SetAC8(MC_CGM_StPtr, (uint32)pMcu_Config->ac8_sc);
    bMcu_State = (pMcu_Config->ac8_dc0 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetAC8_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac8_dc0);

    /* Configure auxiliary clock u32Mcu_Selector 9 and dividers - . */
    CGM_SetAC9(MC_CGM_StPtr, (uint32)pMcu_Config->ac9_sc);
    bMcu_State = (pMcu_Config->ac9_dc0 != CGM_CLOCK_DISABLE6) ? TRUE : FALSE;
    CGM_SetAC9_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac9_dc0);

    /* Configure auxiliary clock u32Mcu_Selector 10 and dividers 0. */
    CGM_SetAC10(MC_CGM_StPtr, (uint32)pMcu_Config->ac10_sc);
    bMcu_State = (pMcu_Config->ac10_dc0 != CGM_CLOCK_DISABLE4) ? TRUE : FALSE;
    CGM_SetAC10_DC0(MC_CGM_StPtr, bMcu_State, (uint32) pMcu_Config->ac10_dc0);
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
    /* Configure auxiliary clock selector 11 and dividers 0. */
    CGM_SetAC11(MC_CGM_StPtr, (uint32)pMcu_Config->ac11_sc);
    bMcu_State = (pMcu_Config->ac11_dc0 != CGM_CLOCK_DISABLE4) ? TRUE : FALSE;
    CGM_SetAC11_DC0(MC_CGM_StPtr,bMcu_State,(uint32) pMcu_Config->ac11_dc0);

    /* Configure auxiliary clock selector 12 and dividers 0. */
    CGM_SetAC12(MC_CGM_StPtr, (uint32)pMcu_Config->ac12_sc);
    bMcu_State = (pMcu_Config->ac12_dc0 != CGM_CLOCK_DISABLE13) ? TRUE : FALSE;
    CGM_SetAC12_DC0(MC_CGM_StPtr,bMcu_State,(uint32) pMcu_Config->ac12_dc0,pMcu_Config->ac12_dc0_fmt);
    bMcu_State = (pMcu_Config->ac12_dc1 != CGM_CLOCK_DISABLE13) ? TRUE : FALSE;
    CGM_SetAC12_DC1(MC_CGM_StPtr,bMcu_State,(uint32) pMcu_Config->ac12_dc1,pMcu_Config->ac12_dc1_fmt);
    bMcu_State = (pMcu_Config->ac12_dc2 != CGM_CLOCK_DISABLE13) ? TRUE : FALSE;
    CGM_SetAC12_DC2(MC_CGM_StPtr,bMcu_State,(uint32) pMcu_Config->ac12_dc2,pMcu_Config->ac12_dc2_fmt);
    #endif
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetIrcoscFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    /* This clock source is not enabled in current mode. */
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status;

    if ((MC_ME_StPtr->GS.R & MC_ME_GS_S_IRC_MASK) != (uint32)0U)
    {
        *pMcu_Frequency = Mcu_gIrcoscClkFreq;
        eMcu_Status = (Std_ReturnType)E_OK;
    }
    else
    {
        *pMcu_Frequency = (uint32)0U;
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetXoscFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    /* This clock source is not enabled in current mode. */
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status;

    if ((MC_ME_StPtr->GS.R & MC_ME_GS_S_XOSC_MASK) != (uint32)0U)
    {
        *pMcu_Frequency = Mcu_gXoscClkFreq;
        eMcu_Status = E_OK;
    }
    else
    {
        *pMcu_Frequency = (uint32)0U;
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetPll0Phi1Freq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    /* This clock source is not enabled in current mode. */
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status;

    if ((MC_ME_StPtr->GS.R & MC_ME_GS_S_PLL0_MASK)!= (uint32)0U)
    {
        *pMcu_Frequency = Mcu_gPll0Phi1ClkFreq;
        eMcu_Status = (Std_ReturnType)E_OK;
    }
    else
    {
        *pMcu_Frequency = (uint32)0U;
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_CalculateFrequenciesOfClockSources
 * Description   : Configures clock sources
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_CalculateFrequenciesOfClockSources(VAR(uint8, AUTOMATIC) bMcu_Runtime)
{
    VAR(uint32, MCU_VAR) u32Mcu_MultiplyFactor = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_FractionalDivider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_OutputDivider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_OutputDivider1 = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Frequency = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_pll0VcoClkFreq;   /* PLL0_PHI1_CLK pMcu_Frequency       */
    VAR(uint32, MCU_VAR) u32Mcu_pll1VcoClkFreq;   /* PLL0_PHI1_CLK pMcu_Frequency       */

    if (FALSE == bMcu_Runtime)
    {
        Mcu_gIrcoscClkFreq = FEATURE_IRCOSC0_FREQ;
        Mcu_gXoscClkFreq = MCU_XOSC_FREQ;

        /* Calculate the pll input reference */
        /* Check the pll input reference */
         if (0U == MC_CGM_StPtr->AC3_SC.B.SELCTL)
        {
            /* Gets input u32Mcu_Frequency - IRCCOSC */
            (void)CLOCK_GetIrcoscFreq(&u32Mcu_Frequency);
        }
        else if (1U == MC_CGM_StPtr->AC3_SC.B.SELCTL)
        {
            /* Gets input u32Mcu_Frequency - XOSC */
            (void)CLOCK_GetXoscFreq(&u32Mcu_Frequency);
        }
        else
        {
            /* Invalid input reference */
            /* Do nothing */
        }

        u32Mcu_MultiplyFactor      = PLLDIG_StPtr->PLL0DV.B.MFD;
        u32Mcu_FractionalDivider   = PLLDIG_StPtr->PLL0DV.B.PREDIV;
        u32Mcu_OutputDivider       = PLLDIG_StPtr->PLL0DV.B.RFDPHI;
        u32Mcu_OutputDivider1      = PLLDIG_StPtr->PLL0DV.B.RFDPHI1;

        u32Mcu_pll0VcoClkFreq = (((uint32)2U *u32Mcu_Frequency) /u32Mcu_FractionalDivider)*u32Mcu_MultiplyFactor; /* polyspace RTE:ZDV */
        if(u32Mcu_OutputDivider != (uint32)0U)
        {
            Mcu_gPll0Phi0ClkFreq = u32Mcu_pll0VcoClkFreq / ((uint32)2U * u32Mcu_OutputDivider);
        }
        else
        {
            Mcu_gPll0Phi0ClkFreq = u32Mcu_pll0VcoClkFreq;
        }
        Mcu_gPll0Phi1ClkFreq = u32Mcu_pll0VcoClkFreq / ((uint32)2U * u32Mcu_OutputDivider1); /* polyspace RTE:ZDV */

        /* Check the pll input reference */
        if (1U == MC_CGM_StPtr->AC4_SC.B.SELCTL)
        {
            /* Gets input u32Mcu_Frequency - XOSC */
            (void)CLOCK_GetXoscFreq(&u32Mcu_Frequency);
        }
        else if (0x03U == MC_CGM_StPtr->AC4_SC.B.SELCTL)
        {
            (void)CLOCK_GetPll0Phi1Freq(&u32Mcu_Frequency);
        }
        else
        {
            /* Invalid input reference */
            /* Do nothing */
        }

        u32Mcu_MultiplyFactor      = PLLDIG_StPtr->PLL1DV.B.MFD;  
        u32Mcu_OutputDivider       = PLLDIG_StPtr->PLL1DV.B.RFDPHI;  

   
        u32Mcu_pll1VcoClkFreq = (u32Mcu_Frequency )*u32Mcu_MultiplyFactor;
        if(u32Mcu_OutputDivider != (uint32)0U)
        {
            Mcu_gPll1Phi0ClkFreq = u32Mcu_pll1VcoClkFreq /((uint32)2U * u32Mcu_OutputDivider);
        }
        else
        {
            Mcu_gPll1Phi0ClkFreq = u32Mcu_pll1VcoClkFreq;
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetPll0Phi0Freq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    /* This clock source is not enabled in current mode. */
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status;

    if ((MC_ME_StPtr->GS.R & MC_ME_GS_S_PLL0_MASK) != (uint32)0U)
    {
        *pMcu_Frequency = Mcu_gPll0Phi0ClkFreq;
        eMcu_Status = (Std_ReturnType)E_OK;
    }
    else
    {
        *pMcu_Frequency = (uint32)0U;
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE)CLOCK_GetPll1Phi0Freq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    /* This clock source is not enabled in current mode. */
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status;

    if ((MC_ME_StPtr->GS.R & MC_ME_GS_S_PLL1_MASK) != (uint32)0U)
    {
        *pMcu_Frequency = Mcu_gPll1Phi0ClkFreq;
        eMcu_Status = (Std_ReturnType)E_OK;
    }
    else
    {
        *pMcu_Frequency = (uint32)0U;
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetSystemClockSelectorOutFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;

    switch (MC_ME_StPtr->GS.B.S_SYSCLK)
    {
    case (CGM_SYSTEM_CLOCK_SRC_IRCOSC):
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case (CGM_SYSTEM_CLOCK_SRC_XOSC):
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }
    case (CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0):
    {   
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }
    case (CGM_SYSTEM_CLOCK_SRC_PLL1_PHI0):
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    /* Invalid clock source for system clock */
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
        break;
    }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetClockSourceFreq
 * Description   : This function returns the pMcu_Frequency of a given clock source
 *
 * Implements CLOCK_SYS_GetClockSourceFreq_Activity
 * END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetClockSourceFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    *pMcu_Frequency = 0U;

    switch (eMcu_McMePeriNameConfig)
    {
    case IRCOSC_CLK:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case XOSC_CLK:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }
    case PLL0_PHI0_CLK:
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }
    case PLL0_PHI1_CLK:
    {
        eMcu_Status = CLOCK_GetPll0Phi1Freq(pMcu_Frequency);
        break;
    }

    case PLL1_PHI0_CLK:
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }

    default:
    {
        /* This clock source is not supported. */
        eMcu_Status = E_UNSUPPORTED;
        break;
    }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetSystemClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) scsClkFreq = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    *pMcu_Frequency = 0U;

    eMcu_Status = CLOCK_GetSystemClockSelectorOutFreq(&scsClkFreq);

    if (eMcu_Status == (Std_ReturnType)E_OK)
    {
        /* System clock and core clock are the same. */
        if (eMcu_McMePeriNameConfig == HSM_CLK)
        {
            *pMcu_Frequency = scsClkFreq;
        }
        else if ((eMcu_McMePeriNameConfig == FXBAR_CLK) \
                || (eMcu_McMePeriNameConfig == BD_CLK) \
                || (eMcu_McMePeriNameConfig == IOP_CLK))
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->SC_DC0.B.DIV + (uint32)1U);
            scsClkFreq /= u32Mcu_Divider;
            *pMcu_Frequency = scsClkFreq;
        }
        else if (eMcu_McMePeriNameConfig == SXBAR_CLK)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->SC_DC1.B.DIV  + (uint32)1U);
            scsClkFreq /= u32Mcu_Divider;
            *pMcu_Frequency = scsClkFreq;
        }
        else if (eMcu_McMePeriNameConfig == PBRIDGEx_CLK)
        {
            if (MC_CGM_StPtr->SC_DC2.B.DE == (uint32)1U)
            {
                u32Mcu_Divider = MC_CGM_StPtr->SC_DC2.B.DIV;
            }
            *pMcu_Frequency = scsClkFreq / (u32Mcu_Divider + (uint32)1u);
        }

        else if ((eMcu_McMePeriNameConfig == CORE_CLK) || (eMcu_McMePeriNameConfig == CHKR_CLK))
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->SC_DC3.B.DIV + (uint32)1U);
            scsClkFreq /= u32Mcu_Divider;
            *pMcu_Frequency = scsClkFreq;
        }
        else
        {
            eMcu_Status = (Std_ReturnType)E_NOT_OK;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/* PER ADC*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetPERClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    
    if(eMcu_McMePeriNameConfig != PER_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        switch (MC_CGM_StPtr->AC0_SC.B.SELCTL)
        {
        case CGM_SOURCE_SEL_IRCOSC:
        {
            eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_XOSC:
        {
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL0_PHI0:
        {
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
            break;
        }
        default:
        {
            /* Invalid value of AC0 u32Mcu_Selector */
            break;
        }
        }

        if (MC_CGM_StPtr->AC0_DC0.B.DE == (uint32)1U)
        {
            u32Mcu_Divider =  (uint32)((uint32)MC_CGM_StPtr->AC0_DC0.B.DIV + (uint32)1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
 
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/* SAR ADC*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetAdcSarClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    
    if(eMcu_McMePeriNameConfig != ADCSAR_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u32Mcu_Selector = MC_CGM_StPtr->AC0_SC.B.SELCTL;

        switch (u32Mcu_Selector)
        {
        case CGM_SOURCE_SEL_IRCOSC:
        {
            eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_XOSC:
        {
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL0_PHI0:
        {    
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL1_PHI0:
        {
            eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
            break;
        }
        default:
        {
            /*do nothing*/
            break;
        }
        }

        if (MC_CGM_StPtr->AC0_DC2.B.DE == (uint32)1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC0_DC2.B.DIV  + (uint32)1U);

            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/* SD ADC*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetAdcsdClockFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = (uint32)0U;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = (uint32)0U;

    u32Mcu_Selector = MC_CGM_StPtr->AC0_SC.B.SELCTL;  

    switch (u32Mcu_Selector)
    {
    case CGM_SOURCE_SEL_IRCOSC:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }

    case CGM_SOURCE_SEL_XOSC:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }

    case CGM_SOURCE_SEL_PLL0_PHI0:
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL1_PHI0:
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }

    if (MC_CGM_StPtr->AC0_DC1.B.DE == (uint32)1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC0_DC1.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetDspiAClockFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;

    u32Mcu_Selector = MC_CGM_StPtr->AC0_SC.B.SELCTL;  

    switch (u32Mcu_Selector)
    {
    case CGM_SOURCE_SEL_IRCOSC:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_XOSC:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }

    case CGM_SOURCE_SEL_PLL0_PHI0:
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }

    case CGM_SOURCE_SEL_PLL1_PHI0:
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }

    if (MC_CGM_StPtr->AC0_DC3.B.DE == (uint32)1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC0_DC3.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*DSPI1, LIN, PSI5 - S*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetDspiBClockFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;

    u32Mcu_Selector = MC_CGM_StPtr->AC0_SC.B.SELCTL;  

    switch (u32Mcu_Selector)
    {
    case CGM_SOURCE_SEL_IRCOSC:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_XOSC:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL0_PHI0:
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }

    case CGM_SOURCE_SEL_PLL1_PHI0:
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }

    if (MC_CGM_StPtr->AC0_DC4.B.DE == (uint32)1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC0_DC4.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*PSI5*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetPSI5ClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_divider1 = 0;
    VAR(uint32, MCU_VAR) u32Mcu_divider2 = 0;
    VAR(uint32, MCU_VAR) u32Mcu_divider3 = 0;;

    eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);

    switch (eMcu_McMePeriNameConfig)
    {
    case PSI5_f189_CLK:
    {
        u32Mcu_Divider =  (uint32)((uint32)MC_CGM_StPtr->AC5_DC0.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_f125_CLK:
    {
        u32Mcu_Divider =  (uint32)((uint32)MC_CGM_StPtr->AC5_DC1.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_1us_CLK:
    {
        u32Mcu_Divider =  (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_TS_CLK:
    { 
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC0.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_DDSR0_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC1.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC10.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_DDSR1_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC1.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC11.B.DIV + (uint32)1U);
        u32Mcu_Divider = (uint32)((uint32)u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3);
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_DDSR2_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC1.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC12.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_DDSR3_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC1.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC13.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_WD0_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC2.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC10.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_WD1_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC2.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC11.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_WD2_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC2.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC12.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    case PSI5_S_WD3_CLK:
    {
        u32Mcu_divider1 = (uint32)((uint32)MC_CGM_StPtr->AC5_DC2.B.DIV + (uint32)1U);
        u32Mcu_divider2 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC2.B.DIV + (uint32)1U);
        u32Mcu_divider3 = (uint32)((uint32)MC_CGM_StPtr->AC5_CDC13.B.DIV + (uint32)1U);
        u32Mcu_Divider = u32Mcu_divider1 * u32Mcu_divider2 * u32Mcu_divider3;
        *pMcu_Frequency /= u32Mcu_Divider;
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*SYSCLK0*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetSYS0ClockFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    u32Mcu_Selector = MC_CGM_StPtr->AC6_SC.B.SELCTL;  

    switch (u32Mcu_Selector)
    {
    case CGM_SOURCE_SEL_IRCOSC:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_XOSC:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL0_PHI0:
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL1_PHI0:
    {
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }

    if (MC_CGM_StPtr->AC6_DC0.B.DE == (uint32)1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC6_DC0.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*SYSCLK1*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetSYS1ClockFreq \
( \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    u32Mcu_Selector = MC_CGM_StPtr->AC7_SC.B.SELCTL;  

    switch (u32Mcu_Selector)
    {
    case CGM_SOURCE_SEL_IRCOSC:
    {
        eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_XOSC:
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL0_PHI0:
    {    
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
    }
    case CGM_SOURCE_SEL_PLL1_PHI0:
    {    
        eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
        break;
    }
    default:
    {
        /* Do nothing */
        break;
    }
    }

    if (MC_CGM_StPtr->AC7_DC0.B.DE == (uint32)1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC7_DC0.B.DIV + (uint32)1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*LIN*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetLfastClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != LFAST_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u32Mcu_Selector = MC_CGM_StPtr->AC1_SC.B.SELCTL;  

        switch (u32Mcu_Selector)
        {
        case CGM_SOURCE_SEL_XOSC:
        {      
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL0_PHI0:
        { 
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL1_PHI0:
        {
            eMcu_Status = CLOCK_GetPll1Phi0Freq(pMcu_Frequency);
            break;
        }
        case CGM_LFASTx_SOURCE_SYS_PIN:
        { 
            *pMcu_Frequency = (uint32)0U;
            break;
        }
        default:
        {
            /* Do nothing */
            break;
        }
        }

        if (MC_CGM_StPtr->AC1_DC0.B.DE == (uint32)1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC1_DC0.B.DIV + (uint32)1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }

    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/* flexRay*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetFlexrayClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != FlexRay_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);

        if (MC_CGM_StPtr->AC2_DC0.B.DE == (uint32)1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC2_DC0.B.DIV + (uint32)1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*SENT CLOCK*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetSentClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != SENT_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);

        if (MC_CGM_StPtr->AC2_DC1.B.DE == (uint32)1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC2_DC1.B.DIV + (uint32)1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*MCAN TTCAN*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetFlexcanClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != CAN_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u32Mcu_Selector = MC_CGM_StPtr->AC8_SC.B.SELCTL;

        switch (u32Mcu_Selector)
        {
        case CGM_SOURCE_SEL_XOSC:
        {
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL0_PHI0:
        {
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
            break;
        }
        default:
        {
            /* There is no support in CGM for FLECAN clock selection */
            *pMcu_Frequency = (uint32)0U;
            break;
        }
        }

        if (MC_CGM_StPtr->AC8_DC0.B.DE == (uint32)1U)
        {
            u32Mcu_Divider =  (uint32)((uint32)MC_CGM_StPtr->AC8_DC0.B.DIV + 1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/* RTI */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetRtiClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != RTI_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u32Mcu_Selector = MC_CGM_StPtr->AC9_SC.B.SELCTL;

        switch (u32Mcu_Selector)
        {
        case CGM_SOURCE_SEL_IRCOSC:
        {
            eMcu_Status = CLOCK_GetIrcoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_XOSC:
        {    
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        default:
        {
            /* Do nothing */
            break;
        }
        }

        if (MC_CGM_StPtr->AC9_DC0.B.DE == 1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC9_DC0.B.DIV + 1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }


    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*ETHERNET*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetEnetClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) u32Mcu_Selector = 0U;
    VAR(uint32, MCU_VAR) u32Mcu_Divider = 0U;

    if(eMcu_McMePeriNameConfig != RTI_CLK)
    {
        eMcu_Status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        u32Mcu_Selector = MC_CGM_StPtr->AC9_SC.B.SELCTL;

        switch (u32Mcu_Selector)
        {
        case CGM_SOURCE_SEL_XOSC:
        {
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
            break;
        }
        case CGM_SOURCE_SEL_PLL0_PHI0:
        {
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
            break;
        }
        default:
        {
            /* There is no support in CGM for FLECAN clock selection */
            *pMcu_Frequency = (uint32)0U;
            break;
        }
        }

        if (MC_CGM_StPtr->AC10_DC0.B.DE == 1U)
        {
            u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC10_DC0.B.DIV + 1U);
            *pMcu_Frequency /= u32Mcu_Divider;
        }
    }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
/*I2S*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetI2SClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, AUTOMATIC) eMcu_Status = (Std_ReturnType)E_OK;
    VAR(uint32, AUTOMATIC) u32Mcu_Selector = 0U;
    VAR(uint32, AUTOMATIC) u32Mcu_Divider = 0U;
    if((eMcu_McMePeriNameConfig != I2S0_CLK)&&(eMcu_McMePeriNameConfig != I2S1_CLK)&&(eMcu_McMePeriNameConfig != I2S_M_CLK))
    {
        return E_NOT_OK;
    }

    u32Mcu_Selector = MC_CGM_StPtr->AC12_SC.B.SELCTL;

    switch (u32Mcu_Selector)
    {
        case CGM_SOURCE_SEL_XOSC:
            eMcu_Status = CLOCK_GetXoscFreq(pMcu_Frequency);
        break;

        case CGM_SOURCE_SEL_PLL0_PHI0:
            eMcu_Status = CLOCK_GetPll0Phi0Freq(pMcu_Frequency);
        break;
        default:
            /* There is no support in CGM for FLECAN clock selection */
            *pMcu_Frequency = 0U;
            break;
    }

    if(eMcu_McMePeriNameConfig == I2S_M_CLK)
    {
     if (MC_CGM_StPtr->AC12_DC0.B.DE == 1U)
     {
         u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC12_DC0.B.DIV + 1U);
         *pMcu_Frequency /= u32Mcu_Divider;
     }
    }

   if(eMcu_McMePeriNameConfig == I2S0_CLK)
   {
    if (MC_CGM_StPtr->AC12_DC1.B.DE == 1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC12_DC1.B.DIV + 1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }
   }

   if(eMcu_McMePeriNameConfig == I2S1_CLK)
   {
    if (MC_CGM_StPtr->AC12_DC2.B.DE == 1U)
    {
        u32Mcu_Divider = (uint32)((uint32)MC_CGM_StPtr->AC12_DC2.B.DIV + 1U);
        *pMcu_Frequency /= u32Mcu_Divider;
    }
   }
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif
/*FUNCTION**********************************************************************
 * Function Name : CLOCK_SYS_GetModuleClockFreq
 * Description   : Gets module clock pMcu_Frequency
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) CLOCK_GetModuleClockFreq \
( \
    VAR(clock_names_t, AUTOMATIC) eMcu_McMePeriNameConfig, \
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) pMcu_Frequency \
)
{
    VAR(Std_ReturnType, MCU_VAR) eMcu_Status = (Std_ReturnType)E_OK;

    if (eMcu_McMePeriNameConfig < END_OF_CLK_SOURCES)
    {
        eMcu_Status = CLOCK_GetClockSourceFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
    }
    else if (eMcu_McMePeriNameConfig < END_OF_SYSTEM_CLKS)
    {
        eMcu_Status = CLOCK_GetSystemClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
    }
    else if (eMcu_McMePeriNameConfig < END_OF_AC0_CLK)
    {
        switch (eMcu_McMePeriNameConfig)
        {
        case PER_CLK:
        {
            eMcu_Status = CLOCK_GetPERClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
            break;
        }
        case ADCSD_CLK:
        {
            eMcu_Status = CLOCK_GetAdcSarClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
            break;
        }
        case ADCSAR_CLK:
        {
            eMcu_Status = CLOCK_GetAdcsdClockFreq(pMcu_Frequency);
            break;
        }
        case DSPI_A_CLK:
        {
            eMcu_Status = CLOCK_GetDspiAClockFreq(pMcu_Frequency);
            break;
        }
        case DSPI_B_CLK:
        case LIN_CLK:
        case PSI5_S_CLK:
        {
            eMcu_Status = CLOCK_GetDspiBClockFreq(pMcu_Frequency);
            break;
        }
        default:
        {
            eMcu_Status = (Std_ReturnType)E_NOT_OK;
            break;
        }
        }
    }
    else if (eMcu_McMePeriNameConfig < END_OF_AC6_CLK)
    {
        eMcu_Status = CLOCK_GetSYS0ClockFreq(pMcu_Frequency);
    }
    else if (eMcu_McMePeriNameConfig < END_OF_AC7_CLK)
    {
        eMcu_Status = CLOCK_GetSYS1ClockFreq(pMcu_Frequency);
    }
    else if (eMcu_McMePeriNameConfig < END_OF_AC1_CLK)
    {
        eMcu_Status = CLOCK_GetLfastClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
    }
    else if (eMcu_McMePeriNameConfig < END_OF_AC2_CLK)
    {
        if (eMcu_McMePeriNameConfig == FlexRay_CLK)
        {
            eMcu_Status = CLOCK_GetFlexcanClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
        }
        else
        {
            eMcu_Status = CLOCK_GetSentClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
        }
    }
    else if (eMcu_McMePeriNameConfig < END_OF_PSI5_CLK)
    {
        eMcu_Status = CLOCK_GetPSI5ClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
    }
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
    else if (eMcu_McMePeriNameConfig < END_OF_AC10_CLK)
    #endif
    #if (MCU_HARDVER == 3)
    else
    #endif
    {
        if (eMcu_McMePeriNameConfig == TXCLK_REF_CLK)
        {
            eMcu_Status = CLOCK_GetEnetClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
        }
        if (eMcu_McMePeriNameConfig == CAN_CLK)
        {
            eMcu_Status = CLOCK_GetFlexcanClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
        }
        if (eMcu_McMePeriNameConfig == RTI_CLK)
        {
            eMcu_Status = CLOCK_GetRtiClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
        }
    }
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
    else
    {
        (void)CLOCK_GetI2SClockFreq(eMcu_McMePeriNameConfig, pMcu_Frequency);
    }
    #endif
    return eMcu_Status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


/*FUNCTION**********************************************************************
 * Function Name : Mcu_LLD_ConfigureCgmcs
 * Description   : Configures clock sources
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_ConfigureCgmcs \
( \
    P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_Config \
)
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    if(pMcu_Config == NULL_PTR)
    {
        Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        Mcu_LLD_SetIrc(&pMcu_Config->cgmcsConfig.ircConfig);

        Mcu_LLD_SetXosc(&pMcu_Config->cgmcsConfig.xosc0Config);

        Mcu_LLD_SetPll(&pMcu_Config->cgmcsConfig.pll0Config, &pMcu_Config->cgmConfig, 0U);

        Mcu_LLD_SetPll(&pMcu_Config->cgmcsConfig.pll1Config, &pMcu_Config->cgmConfig, 1U);
    }
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Enables clock sources from MC_ME
 *
 * This function enables/disables all clock sources from MC_ME
 * @param[in] ModeEnable  register to be MC_ME.ME
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_SetModeEnable ( VAR(uint32, AUTOMATIC) ModeEnable )
{
    MC_ME_StPtr->ME.R = ModeEnable;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Set run periheral configuration
 *
 * This function sets run periheral configuration
 *
 * @param[in]   RunModeConfig 
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_SetRunPeripheralConfig ( VAR(uint32, AUTOMATIC) RunIdx,
                                                                 VAR(uint32, AUTOMATIC) RunModeConfig )
{
    MC_ME_StPtr->RUN_PC[RunIdx].R = RunModeConfig;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Set low periheral configuration
 *
 * This function sets low periheral configuration
 *
 * @param[in]   LpModeConfig
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_SetLowPeripheralConfig ( VAR(uint32, AUTOMATIC) RunIdx,
                                                                 VAR(uint32, AUTOMATIC) LpModeConfig )
{
    MC_ME_StPtr->LP_PC[RunIdx].R = LpModeConfig;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
* @brief Sets Peripheral clock control register
*
* @param[in] pMcu_Base             mc_me pMcu_Base pointer
* @param[in] eMcu_McMePeriNameConfig        clock name
* @param[in] u8Mcu_RunConfigIndex   running configuration index
* @param[in] u8Mcu_LowConfigIndex   low configuration index
*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_SetPeripheralClockControl \
( \
    P2VAR(MC_ME_Type, AUTOMATIC, MCU_APPL_DATA) pMcu_Base, \
    VAR(Mcu_McMePeriNameType, AUTOMATIC) eMcu_PeripheralName, \
    VAR(uint8, AUTOMATIC) u8Mcu_RunConfigIndex, \
    VAR(uint8, AUTOMATIC) u8Mcu_LowConfigIndex \
)
{
   /* Configure the low and run configurations */
   if (eMcu_PeripheralName != MC_ME_INVALID_INDEX)
   {
       pMcu_Base->PCTL[eMcu_PeripheralName].R \
           = (uint8)((MC_ME_PCTLn_RUN_CFG(u8Mcu_RunConfigIndex) | MC_ME_PCTLn_LP_CFG(u8Mcu_LowConfigIndex)));
   }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_ChangeSysClk( P2VAR(MC_ME_Type, AUTOMATIC, MCU_APPL_DATA) Mcu_McmePtr, \
                                                                VAR(Mcu_CgmClkSelType, AUTOMATIC) Mcu_ClkSel )
{
    switch ((Mcu_McModeType)(Mcu_McmePtr->GS.B.S_CURRENT_MODE))
    {
        case me_mc_drun_mode:
        {
            Mcu_McmePtr->DRUN_MC.B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        case me_mc_run0_mode:
        {
            Mcu_McmePtr->RUN_MC[0].B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        case me_mc_run1_mode:
        {
            Mcu_McmePtr->RUN_MC[1].B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        case me_mc_run2_mode:
        {
            Mcu_McmePtr->RUN_MC[2].B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        case me_mc_run3_mode:
        {
            Mcu_McmePtr->RUN_MC[3].B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        case me_mc_halt0_mode:
        {
            Mcu_McmePtr->HALT0_MC.B.SYSCLK = (uint32) Mcu_ClkSel;
            break;
        }
        default:
        {
            /* Do nothing */
            break;
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief MC_ME mode change.
 *
 * This function is changing mode in MC_ME module
 *
 * @param[in] Mcu_McmePtr Register Mcu_McmePtr address for the MC_ME u32Mcu_Instance.
 * @param[in] Mcu_TargetMode Destination mode.
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(Std_ReturnType, MCU_CODE) MC_ME_ChangeMode( P2VAR(MC_ME_Type, AUTOMATIC, MCU_APPL_DATA) Mcu_McmePtr, \
                                                              VAR(Mcu_McModeType, AUTOMATIC) Mcu_TargetMode )
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) Mcu_CurrentMode = 0;
    VAR(uint32, MCU_VAR) Mcu_Timeout = 0;

    if (Mcu_TargetMode != me_mc_mode_notchange)
    {
         Mcu_CurrentMode = (uint32)Mcu_TargetMode;
    }
    else
    {
        Mcu_CurrentMode = Mcu_McmePtr->GS.B.S_CURRENT_MODE;
    }

    /* Change takes effect after mode transition. */
    Mcu_McmePtr->MCTL.R = MC_ME_MCTL_TARGET_MODE(Mcu_CurrentMode) \
                        | MC_ME_MCTL_KEY(FEATURE_MC_ME_KEY);
    Mcu_McmePtr->MCTL.R = MC_ME_MCTL_TARGET_MODE(Mcu_CurrentMode) \
                        | MC_ME_MCTL_KEY(FEATURE_MC_ME_KEY_INV);

    while ((Mcu_McmePtr->GS.B.S_MTRANS == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
    {
        Mcu_Timeout++;
    } //  Wait for mode transition to complete
    if(Mcu_Timeout >= MCU_TIMEOUT_LOOPS)
    {
        Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
    }
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_ChangeMode(VAR(Mcu_McModeType, AUTOMATIC) Mcu_TargetMode)
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    VAR(uint8, MCU_VAR) Mcu_Loop = 0U;
    for(Mcu_Loop = 0U; Mcu_Loop < 3U; Mcu_Loop++)
    {
        Mcu_RetVal = MC_ME_ChangeMode(MC_ME_StPtr, Mcu_TargetMode);
        if(Mcu_RetVal != E_OK)
        {
            Mcu_RetVal = MC_ME_ChangeMode(MC_ME_StPtr, me_mc_safe_mode);
            if(Mcu_RetVal != E_OK)
            {
                break;
            }
            else
            {
                /* Do Nothing */
            }
            Mcu_RetVal = MC_ME_ChangeMode(MC_ME_StPtr, me_mc_drun_mode);
            if(Mcu_RetVal != E_OK)
            {
                break;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            break;
        }
    }

    if(Mcu_RetVal != E_OK)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuFailOfChangeModeNotification != NULL_PTR) /* polyspace RTE:IDP */
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuFailOfChangeModeNotification();
        }
    }
    else
    {
        /* Do Nothing */
    }

    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_ClockPCS_Init(void)
{
    VAR(uint32, MCU_VAR) Mcu_PWRLVL;
    if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_drun_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->DRUN_MC.B.PWRLVL + 1U) % 8U;
        MC_ME_StPtr->DRUN_MC.B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_safe_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->SAFE_MC.B.PWRLVL + 1U) % 8U;
        MC_ME_StPtr->SAFE_MC.B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_run0_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->RUN_MC[0U].B.PWRLVL + 1U) % 8U; /* polyspace RTE:NIV */
        MC_ME_StPtr->RUN_MC[0U].B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_run1_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->RUN_MC[1U].B.PWRLVL + 1U) % 8U; /* polyspace RTE:NIV */
        MC_ME_StPtr->RUN_MC[1U].B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_run2_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->RUN_MC[2U].B.PWRLVL + 1U) % 8U; /* polyspace RTE:NIV */
        MC_ME_StPtr->RUN_MC[2U].B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_run3_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->RUN_MC[3U].B.PWRLVL + 1U) % 8U; /* polyspace RTE:NIV */
        MC_ME_StPtr->RUN_MC[3U].B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE == (uint32)me_mc_halt0_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->HALT0_MC.B.PWRLVL + 1U) % 8U;
        MC_ME_StPtr->HALT0_MC.B.PWRLVL = Mcu_PWRLVL;
    }
    else if(MC_ME_StPtr->GS.B.S_CURRENT_MODE ==(uint32) me_mc_stop0_mode)
    {
        Mcu_PWRLVL = (MC_ME_StPtr->STOP0_MC.B.PWRLVL + 1U) % 8U;
        MC_ME_StPtr->STOP0_MC.B.PWRLVL = Mcu_PWRLVL;
    }
    else
    {
        /* Do nothing */
    }

    MC_CGM_StPtr->PCS_SDUR.R = 16U;

    MC_CGM_StPtr->PCS_DIVC1.R = 0x03E70008U;
    MC_CGM_StPtr->PCS_DIVE1.R = 0x000004E1U;

    MC_CGM_StPtr->PCS_DIVC2.R = 0x03E70008U;
    MC_CGM_StPtr->PCS_DIVE2.R = 0x00001869U;

    MC_CGM_StPtr->PCS_DIVC4.R = 0x0294000CU;
    MC_CGM_StPtr->PCS_DIVE4.R = 0x0000493DU;
    MC_CGM_StPtr->PCS_DIVS4.R = 0x00004C17U;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


/*!
 * @brief Resets configuration of clock sources in MC_ME_StPtr->
 *
 * Resets configuration of clock sources in MC_ME_StPtr-> Enables IRC type clock sources and sets an IRC type clock source as system clock in all modes.
 *
 * @param[in] pMcu_Base   Register pMcu_Base address for the MC_ME u32Mcu_Instance.
 * @param[in] Mcu_SysClk Destination mode. */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_ResetClockSourcesConfiguration( void )
{
#if 1
   /* Enables IRC sources. Disables XOSC and PLL sources. Sets IRC source as system clock */
    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->DRUN_MC.R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->RUN_MC[0U].R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->RUN_MC[1U].R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->RUN_MC[2U].R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->RUN_MC[3U].R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->SAFE_MC.R));

    MC_ME_SetClockSources(0U, TRUE, FALSE, FALSE, FALSE, (volatile uint32*)&(MC_ME_StPtr->TEST_MC.R));
#endif
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*!
 * @brief Resets configuration of McMePeripheral in MC_ME_StPtr->
 *
 * Resets configuration of McMePeripheral in MC_ME_StPtr-> Disables module clocks in all modes.
 *
 * @param[in] pMcu_Base   Register pMcu_Base address for the MC_ME u32Mcu_Instance. */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) MC_ME_ResetPeripheralsConfiguration( void )
{
#if 1
    VAR(uint32, MCU_VAR) index = 0U;
    /* Reset run peripheral configurations */
    for (index = (uint32)0U; index < ((uint32)MC_ME_RUN_CONFIG_COUNT); index++)
    {
        MC_ME_SetRunPeripheralConfig ( index, 0U );
    }
    /* Reset low peripheral configurations */
    for (index = (uint32)0U; index < ((uint32)MC_ME_LOWPOWER_CONFIG_COUNT); index++)
    {
        MC_ME_SetLowPeripheralConfig( index, 0U );
    }

    for (index = (uint32)0U; index < (uint32)255U; index++)
    {
        /* Set peripheral clock control */
        MC_ME_SetPeripheralClockControl(MC_ME_StPtr, (Mcu_McMePeriNameType)index, 0U, 0U);
    }
#endif
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*FUNCTION**********************************************************************
 * Function Name : CLOCK_SYS_Reset
 * Description   : Clears peripheral clock gating and all clock sources. Only an IRC
 * type clock source is enabled and u32Mcu_Set as system clock source.
 *END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Reset(void)
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) Mcu_Timeout = 0;

    MC_RGM.PRST0.R = 0xFFFFFFFF;
    MC_RGM.PRST1.R = 0xFFFFFFFF;
    MC_RGM.PRST2.R = 0xFFFFFFFF;
    MC_RGM.PRST3.R = 0xFFFFFFFF;
    MC_RGM.PRST4.R = 0xFFFFFFFF;
    MC_RGM.PRST5.R = 0xFFFFFFFF;
    MC_RGM.PRST6.R = 0xFFFFFFFF;
    MC_RGM.PRST7.R = 0xFFFFFFFF;

    MC_RGM.PRST0.R = 0;
    MC_RGM.PRST1.R = 0;
    MC_RGM.PRST2.R = 0;
    MC_RGM.PRST3.R = 0;
    MC_RGM.PRST4.R = 0;
    MC_RGM.PRST5.R = 0;
    MC_RGM.PRST6.R = 0;
    MC_RGM.PRST7.R = 0;

    LINFlexD_4.LINCR1.B.INIT = 1;
    LINFlexD_4.LINCR1.B.SLEEP = 1;
    LINFlexD_4.UARTCR.B.RxEn = 0;
    LINFlexD_4.UARTCR.B.TxEn = 0;
    LINFlexD_4.DMARXE.R = 0x0;
    LINFlexD_4.DMATXE.R = 0x0;

    LINFlexD_5.LINCR1.B.INIT = 1;
    LINFlexD_5.LINCR1.B.SLEEP = 1;
    LINFlexD_5.UARTCR.B.RxEn = 0;
    LINFlexD_5.UARTCR.B.TxEn = 0;
    LINFlexD_5.DMARXE.R = 0x0;
    LINFlexD_5.DMATXE.R = 0x0;

    LINFlexD_6.LINCR1.B.INIT = 1;
    LINFlexD_6.LINCR1.B.SLEEP = 1;
    LINFlexD_6.UARTCR.B.RxEn = 0;
    LINFlexD_6.UARTCR.B.TxEn = 0;
    LINFlexD_6.DMARXE.R = 0x0;
    LINFlexD_6.DMATXE.R = 0x0;

    /* Resets configuration of McMePeripheral in MC_ME_StPtr-> */
    MC_ME_ResetPeripheralsConfiguration();

    /* Resets configuration of clock sources in MC_ME_StPtr-> */
    MC_ME_ResetClockSourcesConfiguration();

    /* Change takes effect after mode transition. */ /* DRUN */
    MC_ME_StPtr->MCTL.R = (MC_ME_MCTL_TARGET_MODE(0x03U) | MC_ME_MCTL_KEY(0x5AF0U));
    MC_ME_StPtr->MCTL.R = (MC_ME_MCTL_TARGET_MODE(0x03U) | MC_ME_MCTL_KEY(0xA50FU));

    Mcu_Timeout = 0U;
    while ((MC_ME_StPtr->GS.B.S_MTRANS == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
    {
        Mcu_Timeout++;
    } //  Wait for mode transition to complete
    if(Mcu_Timeout >= MCU_TIMEOUT_LOOPS)
    {
        Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
    }

    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
        /*! System clock divider ratios will change with next update.
        *  Not required for Cut 1.*/
        MC_CGM_StPtr->SC_DIV_RC.R = 0x00000001;
        /*! System clock divider ratios updated on writing MC_CGM_StPtr->DIV_UPD_TRIG.
        * Not required for Cut 1. */
        MC_CGM_StPtr->DIV_UPD_TYPE.R = 0x80000000;

        // PBRIDGEA/PBRIDGEB_CLK at syst clk div by 12 ... (50 MHz)
        MC_CGM_StPtr->SC_DC2.R = 0x80000000;

        Mcu_Timeout = 0U;
        if (0u != SSCM.UOPS.B.HSE)
        {
        	HSM.ALG_PARAM[1] = 0U;
    		HSM.HOST_FLAG = 0x000100AAUL;

    		/* Wait for the service to complete */
    		while ((HSM.HOST_FLAG == 0x000100AAUL) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
    		{
    			Mcu_Timeout++;
    		}
        }

        // SXBAR_CLK at syst clk div by 6 ... (100 MHz)
        MC_CGM_StPtr->SC_DC1.R = 0x80000000;

        // FXBAR_CLK, BD_CLK, IOP_CLK at syst clk div by 3 ... (200 MHz)
        MC_CGM_StPtr->SC_DC0.R = 0x80000000;

        // COMP/CHKR_CLK at syst clk div by 2 ... (300 MHz)
        MC_CGM_StPtr->SC_DC3.R = 0x80000000;

        // CLKOUT at syst clk div by 11 ... (54.55 MHz)
        MC_CGM_StPtr->SC_DC4.R = 0x80000000;
        //MC_CGM_StPtr->SC_DC4.R = 0x80080000;
        //! System clock divider ratio updates triggered.  Not required for Cut 1.
        MC_CGM_StPtr->DIV_UPD_TRIG.R = 0xfeedface;
        //! Wait for System Clock Divider Update Status == 0. Not required for Cut 1.
        
        while ((MC_CGM_StPtr->DIV_UPD_STAT.B.SYS_UPD_STAT == 1) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
        {
            Mcu_Timeout++;
        }
        if(Mcu_Timeout >= MCU_TIMEOUT_LOOPS)
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
        MC_CGM_StPtr->AC3_SC.B.SELCTL = 0x00;   //connect XOSC to the PLL0 input
        MC_CGM_StPtr->AC4_SC.B.SELCTL = 0x01;         //connect XOSC to the PLL1 input

        // Set PLL0 to 300 MHz with 40MHz XOSC reference
        // PREDIV =  1, MFD = 15, RFDPHI = 2, RFDPHI1 = 8
        PLLDIG.PLL0DV.R = 0;
        // Set PLL1 to 600 MHz with 40MHz XOSC reference
        PLLDIG.PLL1DV.R = 0;                // MFD = 30, RFDPHI = 1

        MC_CGM_StPtr->AC0_SC.R  = 0x01000000;     //Selects the source for auxiliary clock 0 = PLL0_PHI

        MC_CGM_StPtr->AC0_DC0.R =  0x0;      //Auxiliary Clock0 Divisor0 = 8
        MC_CGM_StPtr->AC0_DC1.R =  0x0;      //Auxiliary Clock0 Divisor1 = 20
        MC_CGM_StPtr->AC0_DC2.R =  0x0;      //Auxiliary Clock0 Divisor2 = 10
        MC_CGM_StPtr->AC0_DC3.R =  0x0;      //Auxiliary Clock0 Divisor3 = 4
        MC_CGM_StPtr->AC0_DC4.R =  0x0;      //Auxiliary Clock0 Divisor4 = 4

        MC_CGM_StPtr->AC1_DC0.R =  0x0;      //Auxiliary Clock1 Divisor0 = 16

        MC_CGM_StPtr->AC2_DC0.R =  0x0;       //Auxiliary Clock2 Divisor0 = 10
        MC_CGM_StPtr->AC2_DC1.R =  0x0;       //Auxiliary Clock2 Divisor1= 4

        MC_CGM_StPtr->AC5_DC0.R = 0x00000000;      //Auxiliary Clock5 Divisor0 =6613,Divider Value Format =2

        MC_CGM_StPtr->AC5_DC1.R = 0x00000000;      //Auxiliary Clock5 Divisor1 = 200

        MC_CGM_StPtr->AC5_DC2.R = 0x00000000;     //Auxiliary Clock5 Divisor2  = 400

        MC_CGM_StPtr->AC5_CDC0.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor0 = 12

        MC_CGM_StPtr->AC5_CDC1.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor1 = 12

        MC_CGM_StPtr->AC5_CDC10.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor10 =2

        MC_CGM_StPtr->AC5_CDC11.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor11 = 2

        MC_CGM_StPtr->AC5_CDC12.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor12 =2

        MC_CGM_StPtr->AC5_CDC13.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor13 = 2

        MC_CGM_StPtr->AC5_CDC2.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor2 = 12

        MC_CGM_StPtr->AC5_CDC20.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor20 = 2

        MC_CGM_StPtr->AC5_CDC21.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor21 = 2

        MC_CGM_StPtr->AC5_CDC22.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor22 =2

        MC_CGM_StPtr->AC5_CDC23.R =0x00000000;     //Auxiliary Clock5 Cascaded Divisor23 = 2

        MC_CGM_StPtr->AC6_SC.R  = 0x01000000;      //Auxiliary Clock6 Source_Select =Select PLL0_PHI

        MC_CGM_StPtr->AC7_SC.R  = 0x01000000;      //Auxiliary Clock7 Source_Select =Select PLL0_PHI

        MC_CGM_StPtr->AC8_SC.R  = 0x01000000;      //Auxiliary Clock8 Source_Select =Select PLL0_PHI

        MC_CGM_StPtr->AC9_SC.R  = 0x01000000;      //Auxiliary Clock9 Source_Select =Select XOSC/IRCOSC

        MC_CGM_StPtr->AC10_SC.R  = 0x01000000;      //Auxiliary Clock10 Source_Select =Select XOSC/IRCOSC

        MC_CGM_StPtr->AC11_SC.R  = 0x01000000;      //Auxiliary Clock10 Source_Select =Select PLL0_PHI

        MC_CGM_StPtr->AC12_SC.R  = 0x01000000;      //Auxiliary Clock10 Source_Select =Select XOSC/IRCOSC

        /* Change takes effect after mode transition. */ /* DRUN */
        MC_ME_StPtr->MCTL.R = (MC_ME_MCTL_TARGET_MODE(0x03U) | MC_ME_MCTL_KEY(0x5AF0U));
        MC_ME_StPtr->MCTL.R = (MC_ME_MCTL_TARGET_MODE(0x03U) | MC_ME_MCTL_KEY(0xA50FU));
        Mcu_Timeout = 0U;
        while ((MC_ME_StPtr->GS.B.S_MTRANS == 1U) && (Mcu_Timeout < MCU_TIMEOUT_LOOPS))
        {
            Mcu_Timeout++;
        } //  Wait for mode transition to complete
        if(Mcu_Timeout >= MCU_TIMEOUT_LOOPS)
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    FIRST_CMU->CSR.B.RCDIV = (uint32)3U;
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_RgmInit(P2CONST(Mcu_RgmConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_RgmConfigPtr)
{
    #if(MCU_PERFORM_RESET_API == STD_ON)
    Mcu_gRgmConfiguration = Mcu_RgmConfigPtr->Mcu_RgmResetType;
    #endif
    /* Event Reset Disable Register (RGM_DERD) */
    MC_RGM.DERD.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_DestResetOpt;
    /* Event Alternate Request Register (RGM_DEAR) */
    MC_RGM.DEAR.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_DestSafeIsrOpt;
    /* Bidirectional Reset Enable Register (RGM_DBRE) */
    MC_RGM.DBRE.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_DestExtPinReset;
    /* Functional */
    MC_RGM.FERD.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_FuncResetOpt;
    MC_RGM.FEAR.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_FuncSafeIsrOpt;
    MC_RGM.FBRE.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_FuncExtPinReset;
    /* Event Short Sequence Register (RGM_FESS) */
    MC_RGM.FESS.R = (uint32)Mcu_RgmConfigPtr->Mcrgm_FuncPhase1or3Opt;
    if(((uint32)1U<<(uint32)MCU_POWER_ON_RESET) == MC_RGM.DES.R)
    {
        /* Reset Escalation Threshold Register (RGM_FRET) */
        MC_RGM.FRET.R = (uint8)Mcu_RgmConfigPtr->Mcrgm_FuncThresholdReset;
        /* Reset Escalation Threshold Register (RGM_DRET) */
        MC_RGM.DRET.R = (uint8)Mcu_RgmConfigPtr->Mcrgm_DesThresholdReset;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_PmcInit(P2CONST(Mcu_PmcConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_PmcConfigPtr)
{
    PMCDIG.IE_P.R = (uint32)(Mcu_PmcConfigPtr->Pmc_IerConfig | PMC_IER_IE_EN_MASK32);
    PMCDIG.REE_VD3.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD3ResetEventEn);
    PMCDIG.REE_VD4.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD4ResetEventEn);
    PMCDIG.REE_VD7.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD7ResetEventEn);
    PMCDIG.REE_VD8.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD8ResetEventEn);
    PMCDIG.REE_VD9.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD9ResetEventEn);
    PMCDIG.REE_VD10.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD10ResetEventEn);
    PMCDIG.REE_VD12.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD12ResetEventEn);
    PMCDIG.REE_VD13.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD13ResetEventEn);
    PMCDIG.REE_VD14.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD14ResetEventEn);
    PMCDIG.REE_VD15.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD15ResetEventEn);
    PMCDIG.REE_TD.R = (uint32)(Mcu_PmcConfigPtr->Pmc_TempResEventEn);
    PMCDIG.RES_VD3.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD3ResetEventSel);
    PMCDIG.RES_VD4.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD4ResetEventSel);
    PMCDIG.RES_VD7.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD7ResetEventSel);
    PMCDIG.RES_VD8.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD8ResetEventSel);
    PMCDIG.RES_VD9.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD9ResetEventSel);
    PMCDIG.RES_VD12.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD12ResetEventSel);
    PMCDIG.RES_VD13.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD13ResetEventSel);
    PMCDIG.RES_VD14.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD14ResetEventSel);
    PMCDIG.RES_VD15.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD15ResetEventSel);
    PMCDIG.RES_TD.R = (uint32)(Mcu_PmcConfigPtr->Pmc_TempResEventSel);
    PMCDIG.FEE_VD3.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD3FccuEventEn);
    PMCDIG.FEE_VD4.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD4FccuEventEn);
    PMCDIG.FEE_VD7.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD7FccuEventEn);
    PMCDIG.FEE_VD8.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD8FccuEventEn);
    PMCDIG.FEE_VD9.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD9FccuEventEn);
    PMCDIG.FEE_VD10.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD10FccuEventEn);
    PMCDIG.FEE_VD12.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD12FccuEventEn);
    PMCDIG.FEE_VD13.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD13FccuEventEn);
    PMCDIG.FEE_VD14.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD14FccuEventEn);
    PMCDIG.FEE_VD15.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VD15FccuEventEn);
    PMCDIG.FEE_TD.R = (uint32)(Mcu_PmcConfigPtr->Pmc_TempFccuEventEn);
    PMCDIG.CTL_TD.R = (uint32)(Mcu_PmcConfigPtr->Pmc_TempDetConfig) | 0x00000040UL;
    PMCDIG.VSIO.R = (uint32)(Mcu_PmcConfigPtr->Pmc_VoltageSupply);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_McMeIrqConfig(VAR(uint32, AUTOMATIC) Mcu_McMeIrqConfig)
{
    MC_ME_StPtr->IM.R = Mcu_McMeIrqConfig;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
MCU_INLINE FUNC(void, MCU_CODE) Mcu_LLD_McMeRunConfig(P2CONST(Mcu_McMeConfigType, AUTOMATIC, MCU_APPL_DATA) Mcu_McMeCfgPtr)
{
    VAR(uint32, MCU_VAR)  index = 0;
    /* Set run peripheral configurations */
    for (index = (uint32)0U; index < ((uint32)MC_ME_RUN_CONFIG_COUNT); index++)
    {
        MC_ME_SetRunPeripheralConfig (index, Mcu_McMeCfgPtr->McMeRunConfig[index]);
    }

    /* Set low peripheral configurations */
    for (index = (uint32)0U; index < ((uint32)MC_ME_LOWPOWER_CONFIG_COUNT); index++)
    {
        MC_ME_SetLowPeripheralConfig (index, Mcu_McMeCfgPtr->McMeLowPowerConfig[index]);
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_APPL_DATA) pMcu_ConfigPtr)
{
    if(pMcu_ConfigPtr->Mcu_CtrlConfigPtr->Mcu_BootCore == Mcu_LLD_Get_Core_Id())
    {
        #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
        *((volatile uint32*)0xfffa059CU) |= (0x1000u | 0x800u);    /* Open PMU_CFG */
        #endif
//        Mcu_LLD_Launch_Core(MC_ME_StPtr, pMcu_ConfigPtr->Mcu_CoreConfigPtr);
        (void)Mcu_LLD_ChangeMode(me_mc_mode_notchange);
    }

    if(pMcu_ConfigPtr->Mcu_CtrlConfigPtr->Mcu_InitCore == Mcu_LLD_Get_Core_Id())
    {
        Mcu_LLD_McMeIrqConfig(pMcu_ConfigPtr->Mcu_McMeConfigPtr->Mcu_McMeIrqCfg);
        MC_ME_SetModeEnable(pMcu_ConfigPtr->Mcu_McMeConfigPtr->McMeMe);
        (void)Mcu_LLD_ChangeMode(me_mc_mode_notchange);
        /* Infinite reset Contorl */
        Mcu_LLD_RgmInit(pMcu_ConfigPtr->Mcu_RgmConfigPtr);
        Mcu_LLD_PmcInit(pMcu_ConfigPtr->Mcu_PmcConfigPtr);
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Mcu_LLD_Clock_Init
 * Description   : This function sets the system to target configuration, it
 * only sets the clock modules registers for clock mode change, but not send
 * notifications to drivers.
 *
 * Implements CLOCK_DRV_Init_Activity
 * END**************************************************************************/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_SysCLockCheck(
    P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pMcu_ClockConfigPtr )
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_NOT_OK;

    /* Check whether the current clock source is enabled */
    if(MC_ME_StPtr->GS.B.S_IRC == pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.irc0 /* polyspace RTE:IDP */
        && MC_ME_StPtr->GS.B.S_XOSC == pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.xosc0 /* polyspace RTE:IDP */
        && MC_ME_StPtr->GS.B.S_PLL0 == pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.pll0 /* polyspace RTE:IDP */
        && MC_ME_StPtr->GS.B.S_PLL1 == pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.pll1 /* polyspace RTE:IDP */
        && MC_ME_StPtr->GS.B.S_SYSCLK == pMcu_ClockConfigPtr->mode_configuration.sysclk) /* polyspace RTE:IDP */
    {
        Mcu_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
    }

    /* Check the clock source configuration */
    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
        /* AC3 */
        if(pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.pll0 == 1U)
        {
            if(MC_CGM_StPtr->AC3_SC.B.SELCTL == pMcu_ClockConfigPtr->cgmConfig.ac3_sc)
            {
                Mcu_RetVal = (Std_ReturnType)E_OK;
            }
            else
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
        }
        /* AC4 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->mode_configuration.clocksEnabled.pll1 == 1U)
            {
                if(MC_CGM_StPtr->AC4_SC.B.SELCTL == pMcu_ClockConfigPtr->cgmConfig.ac4_sc)
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
            }
        }
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(((pMcu_ClockConfigPtr->cgmcsConfig.ircConfig.Mcu_FircCfg & 0x800000U) >> 23) == IRCOSC_StPtr->CTL.B.FIRCOFF_ST_DBY
            	&& ((pMcu_ClockConfigPtr->cgmcsConfig.ircConfig.Mcu_FircCfg & 0x1F0000U) >> 16) == IRCOSC_StPtr->CTL.B.USER_TRIM
				&& ((pMcu_ClockConfigPtr->cgmcsConfig.ircConfig.Mcu_FircCfg & 0x1F00U) >> 8) == IRCOSC_StPtr->CTL.B.FIRCDIV
				#if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4) || (MCU_HARDVER == 5))
//                && pMcu_ClockConfigPtr->cgmcsConfig.ircConfig.Mcu_SircCfg == IRCOSC_StPtr->SCTL.R
                #endif 
                && pMcu_ClockConfigPtr->cgmcsConfig.xosc0Config.startupDelay == XOSC_StPtr->CTL.B.EOCV 
                && pMcu_ClockConfigPtr->cgmcsConfig.xosc0Config.Mcu_xoscInterruptEn == XOSC_StPtr->CTL.B.M_OSC
                && pMcu_ClockConfigPtr->cgmcsConfig.xosc0Config.bypassOption == XOSC_StPtr->CTL.B.OSCBYP
                && pMcu_ClockConfigPtr->cgmcsConfig.pll0Config.predivider == PLLDIG_StPtr->PLL0DV.B.PREDIV
                && pMcu_ClockConfigPtr->cgmcsConfig.pll0Config.mulFactorDiv == PLLDIG_StPtr->PLL0DV.B.MFD
                && pMcu_ClockConfigPtr->cgmcsConfig.pll0Config.phi0Divider == PLLDIG_StPtr->PLL0DV.B.RFDPHI
                && pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.mulFactorDiv == PLLDIG_StPtr->PLL1DV.B.MFD
                && pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.phi0Divider == PLLDIG_StPtr->PLL1DV.B.RFDPHI
                && pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.fracDivider == PLLDIG_StPtr->PLL1FD.B.FDEN
                && pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.modulation == PLLDIG_StPtr->PLL1FM.B.MODEN
                && (!(pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.fracDivider) ||
                     (pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.fracDividerValue == PLLDIG_StPtr->PLL1FD.B.FRCDIV))
                && (!(pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.modulation) || 
                     (pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.modulationType == PLLDIG_StPtr->PLL1FM.B.MODSEL &&
                      pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.incrementStep == PLLDIG_StPtr->PLL1FM.B.INCSTP &&
                      pMcu_ClockConfigPtr->cgmcsConfig.pll1Config.modulationPeriod == PLLDIG_StPtr->PLL1FM.B.MODPRD))
                )
            {
                Mcu_RetVal = (Std_ReturnType)E_OK;
            }
            else
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    /* System clock check */
    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
        if(  (pMcu_ClockConfigPtr->cgmConfig.sc_dc0) == MC_CGM_StPtr->SC_DC0.B.DIV
          && (pMcu_ClockConfigPtr->cgmConfig.sc_dc1) == MC_CGM_StPtr->SC_DC1.B.DIV
          && (pMcu_ClockConfigPtr->cgmConfig.sc_dc2) == MC_CGM_StPtr->SC_DC2.B.DIV
          && (pMcu_ClockConfigPtr->cgmConfig.sc_dc3) == MC_CGM_StPtr->SC_DC3.B.DIV
          && (pMcu_ClockConfigPtr->cgmConfig.sc_dc4) == MC_CGM_StPtr->SC_DC4.B.DIV)
        {
            Mcu_RetVal = (Std_ReturnType)E_OK;
        }
        else
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_PeriCLockCheck(
    P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pMcu_ClockConfigPtr )
{
	VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    /* Peripheral clock check */
    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
        /* AC0 */
        if( pMcu_ClockConfigPtr->cgmConfig.ac0_sc != MC_CGM_StPtr->AC0_SS.B.SELSTAT )
        {
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            if((pMcu_ClockConfigPtr->cgmConfig.ac0_dc0 != CGM_CLOCK_DISABLE4)
                != (MC_CGM_StPtr->AC0_DC0.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac0_dc0 != MC_CGM_StPtr->AC0_DC0.B.DIV) && MC_CGM_StPtr->AC0_DC0.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac0_dc1 !=CGM_CLOCK_DISABLE7 )
                != (MC_CGM_StPtr->AC0_DC1.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac0_dc1 != MC_CGM_StPtr->AC0_DC1.B.DIV) && MC_CGM_StPtr->AC0_DC1.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc1_fmt != MC_CGM_StPtr->AC0_DC1.B.DIV_FMT) && MC_CGM_StPtr->AC0_DC1.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc2 != CGM_CLOCK_DISABLE7)
                != (MC_CGM_StPtr->AC0_DC2.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc2 != MC_CGM_StPtr->AC0_DC2.B.DIV) && MC_CGM_StPtr->AC0_DC2.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc2_fmt != MC_CGM_StPtr->AC0_DC2.B.DIV_FMT) && MC_CGM_StPtr->AC0_DC2.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc3 != CGM_CLOCK_DISABLE9)
                != (MC_CGM_StPtr->AC0_DC3.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc3 != MC_CGM_StPtr->AC0_DC3.B.DIV) && MC_CGM_StPtr->AC0_DC3.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc3_fmt != MC_CGM_StPtr->AC0_DC3.B.DIV_FMT) && MC_CGM_StPtr->AC0_DC3.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc4 != CGM_CLOCK_DISABLE4)
                != (MC_CGM_StPtr->AC0_DC4.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if ((pMcu_ClockConfigPtr->cgmConfig.ac0_dc4 != MC_CGM_StPtr->AC0_DC4.B.DIV) && MC_CGM_StPtr->AC0_DC4.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                Mcu_RetVal = (Std_ReturnType)E_OK;
            }
        }

        /* AC1 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac1_sc != MC_CGM_StPtr->AC1_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac1_dc0 != CGM_CLOCK_DISABLE7)
                    != (MC_CGM_StPtr->AC1_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac1_dc0 != MC_CGM_StPtr->AC1_DC0.B.DIV) && MC_CGM_StPtr->AC1_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC2 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if((pMcu_ClockConfigPtr->cgmConfig.ac2_dc0 != CGM_CLOCK_DISABLE6)
                != (MC_CGM_StPtr->AC2_DC0.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac2_dc0 != MC_CGM_StPtr->AC2_DC0.B.DIV) && MC_CGM_StPtr->AC2_DC0.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac2_dc1 != CGM_CLOCK_DISABLE6)
                != (MC_CGM_StPtr->AC2_DC1.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac2_dc1 != MC_CGM_StPtr->AC2_DC1.B.DIV) && MC_CGM_StPtr->AC2_DC1.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                Mcu_RetVal = (Std_ReturnType)E_OK;
            }
        }

        /* AC5 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc0 != CGM_CLOCK_DISABLE13)
                != (MC_CGM_StPtr->AC5_DC0.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc0 != MC_CGM_StPtr->AC5_DC0.B.DIV) && MC_CGM_StPtr->AC5_DC0.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc0_fmt != MC_CGM_StPtr->AC5_DC0.B.DIV_FMT) && MC_CGM_StPtr->AC5_DC0.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc1 != CGM_CLOCK_DISABLE8)
                != (MC_CGM_StPtr->AC5_DC1.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc1 != MC_CGM_StPtr->AC5_DC1.B.DIV) && MC_CGM_StPtr->AC5_DC1.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc2 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_DC2.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_dc2 != MC_CGM_StPtr->AC5_DC2.B.DIV) && MC_CGM_StPtr->AC5_DC2.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc0 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC0.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc0 != MC_CGM_StPtr->AC5_CDC0.B.DIV) && MC_CGM_StPtr->AC5_CDC0.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc1 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC1.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc1 != MC_CGM_StPtr->AC5_CDC1.B.DIV) && MC_CGM_StPtr->AC5_CDC1.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc2 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC2.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc2 != MC_CGM_StPtr->AC5_CDC2.B.DIV) && MC_CGM_StPtr->AC5_CDC2.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc10 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC10.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc10 != MC_CGM_StPtr->AC5_CDC10.B.DIV) && MC_CGM_StPtr->AC5_CDC10.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc11 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC11.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc11 != MC_CGM_StPtr->AC5_CDC11.B.DIV) && MC_CGM_StPtr->AC5_CDC11.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc12 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC12.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc12 != MC_CGM_StPtr->AC5_CDC12.B.DIV) && MC_CGM_StPtr->AC5_CDC12.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc13 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC13.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc13 != MC_CGM_StPtr->AC5_CDC13.B.DIV) && MC_CGM_StPtr->AC5_CDC13.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc20 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC20.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc20 != MC_CGM_StPtr->AC5_CDC20.B.DIV) && MC_CGM_StPtr->AC5_CDC20.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc21 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC21.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc21 != MC_CGM_StPtr->AC5_CDC21.B.DIV) && MC_CGM_StPtr->AC5_CDC21.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc22 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC22.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc22 != MC_CGM_StPtr->AC5_CDC22.B.DIV) && MC_CGM_StPtr->AC5_CDC22.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc23 != CGM_CLOCK_DISABLE10)
                != (MC_CGM_StPtr->AC5_CDC23.B.DE))
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else if((pMcu_ClockConfigPtr->cgmConfig.ac5_cdc23 != MC_CGM_StPtr->AC5_CDC23.B.DIV) && MC_CGM_StPtr->AC5_CDC23.B.DE)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                Mcu_RetVal = (Std_ReturnType)E_OK;
            }
        }

        /* AC6 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac6_sc != MC_CGM_StPtr->AC6_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac6_dc0 != CGM_CLOCK_DISABLE9)
                    != (MC_CGM_StPtr->AC6_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac6_dc0 != MC_CGM_StPtr->AC6_DC0.B.DIV) && MC_CGM_StPtr->AC6_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC7 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac7_sc != MC_CGM_StPtr->AC7_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac7_dc0 != CGM_CLOCK_DISABLE9)
                    != (MC_CGM_StPtr->AC7_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac7_dc0 != MC_CGM_StPtr->AC7_DC0.B.DIV) && MC_CGM_StPtr->AC7_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC8 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac8_sc != MC_CGM_StPtr->AC8_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac8_dc0 != CGM_CLOCK_DISABLE6)
                    != (MC_CGM_StPtr->AC8_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac8_dc0 != MC_CGM_StPtr->AC8_DC0.B.DIV) && MC_CGM_StPtr->AC8_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC9 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac9_sc != MC_CGM_StPtr->AC9_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac9_dc0 != CGM_CLOCK_DISABLE6)
                    != (MC_CGM_StPtr->AC9_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac9_dc0 != MC_CGM_StPtr->AC9_DC0.B.DIV) && MC_CGM_StPtr->AC9_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC10 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac10_sc != MC_CGM_StPtr->AC10_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac10_dc0 != CGM_CLOCK_DISABLE4)
                    != (MC_CGM_StPtr->AC10_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac10_dc0 != MC_CGM_StPtr->AC10_DC0.B.DIV) && MC_CGM_StPtr->AC10_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC11 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac11_sc != MC_CGM_StPtr->AC11_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac11_dc0 != CGM_CLOCK_DISABLE4)
                    != (MC_CGM_StPtr->AC11_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac11_dc0 != MC_CGM_StPtr->AC11_DC0.B.DIV) && MC_CGM_StPtr->AC11_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

        /* AC12 */
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            if(pMcu_ClockConfigPtr->cgmConfig.ac12_sc != MC_CGM_StPtr->AC12_SS.B.SELSTAT)
            {
                Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc0 != CGM_CLOCK_DISABLE13)
                    != (MC_CGM_StPtr->AC12_DC0.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc0 != MC_CGM_StPtr->AC12_DC0.B.DIV) && MC_CGM_StPtr->AC12_DC0.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc1 != CGM_CLOCK_DISABLE13)
                    != (MC_CGM_StPtr->AC12_DC1.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc1 != MC_CGM_StPtr->AC12_DC1.B.DIV) && MC_CGM_StPtr->AC12_DC1.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc2 != CGM_CLOCK_DISABLE13)
                    != (MC_CGM_StPtr->AC12_DC2.B.DE))
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else if((pMcu_ClockConfigPtr->cgmConfig.ac12_dc2 != MC_CGM_StPtr->AC12_DC2.B.DIV) && MC_CGM_StPtr->AC12_DC2.B.DE)
                {
                    Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
                }
                else
                {
                    Mcu_RetVal = (Std_ReturnType)E_OK;
                }
            }
        }

    }
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"




/*FUNCTION**********************************************************************
 *
 * Function Name : Mcu_LLD_Clock_Init
 * Description   : This function sets the system to target configuration, it
 * only sets the clock modules registers for clock mode change, but not send
 * notifications to drivers.
 *
 * Implements CLOCK_DRV_Init_Activity
 * END**************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Clock_Init (
    P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pMcu_ClockConfigPtr )
{
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
#ifdef MCU_FLASH_WAIT_STATUS_CONFIG
    VAR(uint32, MCU_VAR) RegValue;
#endif

    Mcu_RetVal = Mcu_LLD_SysCLockCheck(pMcu_ClockConfigPtr);
    if(Mcu_RetVal == (Std_ReturnType)E_OK)
    {
    	Mcu_RetVal = Mcu_LLD_PeriCLockCheck(pMcu_ClockConfigPtr);
    	if(Mcu_RetVal != (Std_ReturnType)E_OK)
    	{
            /* Configure auxiliary u32Mcu_Selector and dividers */
            (void)Mcu_LLD_ConfigureAuxiliarySelectorsAndDividers(&pMcu_ClockConfigPtr->cgmConfig);
            Mcu_RetVal = (Std_ReturnType)E_OK;
    	}
    }
    else
    {
        /* Clears peripheral clock gating and all clock sources in all power modes.
         * Only an IRC type clock source is enabled and IRC as system clock source. */
        Mcu_RetVal = Mcu_LLD_Reset();
        if(Mcu_RetVal != E_OK)
        {
            /* Do nothing */
        }
        else
        {
            (void)Mcu_LLD_ClockPCS_Init();
            /* Configure clock sources. */
            (void)Mcu_LLD_ConfigureCgmcs(pMcu_ClockConfigPtr);
            /* Configure system dividers */
            (void)Mcu_LLD_ConfigureSystemClockDividers(&pMcu_ClockConfigPtr->cgmConfig);
            /* Configure auxiliary u32Mcu_Selector and dividers */
            (void)Mcu_LLD_ConfigureAuxiliarySelectorsAndDividers(&pMcu_ClockConfigPtr->cgmConfig);

            #ifdef MCU_FLASH_WAIT_STATUS_CONFIG
            RegValue = PFLASH.PFCR1.R;
            RegValue &= ( uint32)(~( uint32)(FLASHC_PFCR1_APC_MASK32 | FLASHC_PFCR1_RWSC_MASK32));
            RegValue |= ( uint32)((FLASHC_PFCR1_APC_MASK32 | FLASHC_PFCR1_RWSC_MASK32) & pMcu_ClockConfigPtr->Mcu_FlashWSConfig);
            /* Set the AddressPipelining/Write/Read Wait State Control. */
            PFLASH.PFCR1.R = (volatile uint32)RegValue;
            #endif
            PRAMC.PRCR1.R = (uint32)pMcu_ClockConfigPtr->Mcu_SRamWSConfig;
            /* Configure peripheral clock gating, system clock source
            * and clock sources in all power modes. */
            Mcu_LLD_McMeRunConfig(Mcu_gConfigPtr->Mcu_McMeConfigPtr);
            Mcu_LLD_PeriModeSet(pMcu_ClockConfigPtr->PeriConfigPtr);

            Mcu_RetVal = (Std_ReturnType)E_OK;
        }
    }
    #if (MCU_HARDVER == 3)
    /* Get Flash Swap Status */
    g_swapStatus = FLASH_Get_Swap_Status();
    #endif
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_GetPllStatus(void)
{
    VAR(Std_ReturnType, MCU_VAR) RetResult = (Std_ReturnType)E_OK;
    VAR(uint32, MCU_VAR) unlock_Count = 0U;
    VAR(uint32, MCU_VAR) Pll_Flag = 0U;

    if (PLLDIG_StPtr->PLL0CR.B.CLKCFG == (uint32)MCU_PLLCR_CFG_MASK)
    {
        Pll_Flag++;
        if(PLLDIG_StPtr->PLL0SR.B.LOCK != TRUE)
        {
            unlock_Count++;
        }
    }
    if (PLLDIG_StPtr->PLL1CR.B.CLKCFG == MCU_PLLCR_CFG_MASK)
    {
        Pll_Flag++;
        if(PLLDIG_StPtr->PLL1SR.B.LOCK != TRUE)
        {
            unlock_Count++;
        }
    }
    if(Pll_Flag == 0U)
    {
        RetResult = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        if (unlock_Count > 0U)
        {
            /* at leas 1 pll that was ON is unlocked return that there are unlocked PLL's */
            RetResult = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* at leas 1 pll that was ON is unlocked return that there are unlocked PLL's */
            RetResult = (Std_ReturnType)E_OK;
        }
    }
    return RetResult;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_DistributePllClock(void)
{
    VAR(uint32, MCU_VAR) fxbarClk = 0U; 
    VAR(Std_ReturnType, MCU_VAR) Mcu_RetVal = (Std_ReturnType)E_OK;
    if(Mcu_gClockConfigPtr == NULL_PTR)
    {
        /* do nothing */
    }
    else
    {
        MC_ME_ChangeSysClk(MC_ME_StPtr, Mcu_gClockConfigPtr->mode_configuration.sysclk);
        (void)Mcu_LLD_ChangeMode(me_mc_mode_notchange);

        Mcu_LLD_CalculateFrequenciesOfClockSources(FALSE);
        Mcu_RetVal = CLOCK_GetModuleClockFreq(FXBAR_CLK, &fxbarClk);
        if(Mcu_RetVal == (Std_ReturnType)E_OK)
        {
            /* Config RWSC */
            if (fxbarClk == 100000000U)
            {
                PFLASH.PFCR1.B.RWSC = (uint32)3U;
            }
            else
            {
                PFLASH.PFCR1.B.RWSC = (uint32)7U;
            }
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_LLD_Wkpu_Reset(void)
{
    MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.R;
    XOSC_StPtr->CTL.B.I_OSC = XOSC_StPtr->CTL.B.I_OSC;
    /* Clear WKPU.WISR */
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
    WKPU.WISR0.R  = 0xFFFFFFFFUL;
    WKPU.WISR1.R  = 0xFFFFFFFFUL;
    #endif
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*******************************************************************************
 * @brief      Set current chip mode
 * @param[in]  ChipMode chip_mode
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Std_ReturnType, MCU_CODE) Mcu_LLD_Set_Chip_Mode \
( \
    P2CONST(Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_ModeConfigPtr
)
{
    VAR(Std_ReturnType, MCU_CODE)Mcu_RetVal = (Std_ReturnType)E_OK;

    switch (pMcu_ModeConfigPtr->Mcu_ChipMode) 
    {
        case me_mc_reset_mode:
        {
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_reset_mode);
            break;
        }
        case me_mc_test_mode: 
        {
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_test_mode);
            break;
        }
        case me_mc_safe_mode:
        {
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_safe_mode);
            break;
        }
        case me_mc_drun_mode:
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->DRUN_MC.R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_drun_mode);
            break;
        }
        case me_mc_run0_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->RUN_MC[0].R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_run0_mode);
            break;
        }
        case me_mc_run1_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->RUN_MC[1].R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_run1_mode);
            break;
        }
        case me_mc_run2_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->RUN_MC[2].R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_run2_mode);
            break;
        }
        case me_mc_run3_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->RUN_MC[3].R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_run3_mode);
            break;
        }
        case me_mc_halt0_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->HALT0_MC.R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_halt0_mode);
            break;
        }
        case me_mc_stop0_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                  (volatile uint32 *)&MC_ME_StPtr->STOP0_MC.R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_stop0_mode);
            break;
        }
        #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4))
        case me_mc_standby_mode: 
        {
            MC_ME_SetClockSources(pMcu_ModeConfigPtr->Mcu_TargetClock,
                                  pMcu_ModeConfigPtr->Mcu_IRC_En,
                                  pMcu_ModeConfigPtr->Mcu_XOSC_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL0_En,
                                  pMcu_ModeConfigPtr->Mcu_PLL1_En,
                                 (volatile uint32 *) &MC_ME_StPtr->STANDBY_MC.R);
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_standby_mode);
            break;
        }
        #endif
        case me_mc_reset_des_mode: 
        {
            Mcu_RetVal = Mcu_LLD_ChangeMode(me_mc_reset_des_mode);
            break;
        }
        default: 
        { 
            /* PRQA S 2024 */
            Mcu_RetVal = (Std_ReturnType)E_NOT_OK;
            break;
        }
    };
    return Mcu_RetVal;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_SetMode \
( \
    P2CONST(Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_ModeConfigPtr
)
{
    P2CONST(Mcu_ModeConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_TargetModeConfigPtr;
    VAR(Mcu_ModeConfigType, MCU_VAR) Mcu_CurrentModeConfig;
    VAR(Mcu_ModeConfigType, MCU_VAR) Mcu_LowPowerModeConfig;

    Mcu_TargetModeConfigPtr = pMcu_ModeConfigPtr;

    if  ( (Mcu_TargetModeConfigPtr->Mcu_ChipMode == me_mc_halt0_mode) /* polyspace RTE:IDP */
        || (Mcu_TargetModeConfigPtr->Mcu_ChipMode == me_mc_stop0_mode) ) /* polyspace RTE:IDP */
    {
        /* The current clock mode, which needs to be restored after waking up */
        Mcu_CurrentModeConfig.Mcu_ChipMode = (Mcu_McModeType)MC_ME_StPtr->GS.B.S_CURRENT_MODE;
        Mcu_CurrentModeConfig.Mcu_IRC_En = MC_ME_StPtr->GS.B.S_IRC;
        Mcu_CurrentModeConfig.Mcu_XOSC_En = MC_ME_StPtr->GS.B.S_XOSC;
        Mcu_CurrentModeConfig.Mcu_PLL0_En = MC_ME_StPtr->GS.B.S_PLL0;
        Mcu_CurrentModeConfig.Mcu_PLL1_En = MC_ME_StPtr->GS.B.S_PLL1;
        Mcu_CurrentModeConfig.Mcu_TargetClock = MC_ME_StPtr->GS.B.S_SYSCLK;
        /* LowPower Clock */
        /* Set current mode to the same clock configuration as low power mode */
        Mcu_LowPowerModeConfig.Mcu_ChipMode = (Mcu_McModeType)MC_ME_StPtr->GS.B.S_CURRENT_MODE;
        Mcu_LowPowerModeConfig.Mcu_IRC_En = Mcu_TargetModeConfigPtr->Mcu_IRC_En;
        Mcu_LowPowerModeConfig.Mcu_XOSC_En = Mcu_TargetModeConfigPtr->Mcu_XOSC_En;
        Mcu_LowPowerModeConfig.Mcu_PLL0_En = Mcu_TargetModeConfigPtr->Mcu_PLL0_En;
        Mcu_LowPowerModeConfig.Mcu_PLL1_En = Mcu_TargetModeConfigPtr->Mcu_PLL1_En;
        Mcu_LowPowerModeConfig.Mcu_TargetClock = Mcu_TargetModeConfigPtr->Mcu_TargetClock;
        Mcu_LowPowerModeConfig.PeriConfigPtr = Mcu_TargetModeConfigPtr->PeriConfigPtr;

        /* All peripherals need to be turned off before setting the clock configuration */
        /* Synchronous low power clock mode */
        Mcu_LLD_PeriModeSet(Mcu_LowPowerModeConfig.PeriConfigPtr);
        (void)Mcu_LLD_Set_Chip_Mode(&Mcu_LowPowerModeConfig);
        /* Turn off the interrupt flag that may affect wakeup */
        Mcu_LLD_Wkpu_Reset();
        /* Enter low power */
        (void)Mcu_LLD_Set_Chip_Mode(Mcu_TargetModeConfigPtr);
        if(Mcu_gClockConfigPtr != NULL_PTR)
        {
            Mcu_LLD_PeriModeSet(Mcu_gClockConfigPtr->PeriConfigPtr);
        }
        (void)Mcu_LLD_Set_Chip_Mode(&Mcu_CurrentModeConfig);
    }
    #if ((MCU_HARDVER == 2) || (MCU_HARDVER == 4)) 
    else if (Mcu_TargetModeConfigPtr->Mcu_ChipMode == me_mc_standby_mode)
    {
        /* LowPower Clock */
        /* Set current mode to the same clock configuration as low power mode */
        Mcu_LowPowerModeConfig.Mcu_ChipMode = me_mc_drun_mode; // (Mcu_McModeType)MC_ME_StPtr->GS.B.S_CURRENT_MODE;
        Mcu_LowPowerModeConfig.Mcu_IRC_En = Mcu_TargetModeConfigPtr->Mcu_IRC_En;
        Mcu_LowPowerModeConfig.Mcu_XOSC_En = Mcu_TargetModeConfigPtr->Mcu_XOSC_En;
        Mcu_LowPowerModeConfig.Mcu_PLL0_En = Mcu_TargetModeConfigPtr->Mcu_PLL0_En;
        Mcu_LowPowerModeConfig.Mcu_PLL1_En = Mcu_TargetModeConfigPtr->Mcu_PLL1_En;
        Mcu_LowPowerModeConfig.Mcu_TargetClock = Mcu_TargetModeConfigPtr->Mcu_TargetClock;
        Mcu_LowPowerModeConfig.PeriConfigPtr = Mcu_TargetModeConfigPtr->PeriConfigPtr;
        /* All peripherals need to be turned off before setting the clock configuration */
        Mcu_LLD_PeriModeSet(Mcu_LowPowerModeConfig.PeriConfigPtr);
        /* Synchronous low power clock mode */
        (void)Mcu_LLD_Set_Chip_Mode(&Mcu_LowPowerModeConfig);
        /* PMU_CFG */
        *((volatile uint32*)0xfffa059CU) &= (uint32)(~(0x1000UL | 0x800UL));   /* Close PMU_CFG */
        /* Turn off the interrupt flag that may affect wakeup */
        Mcu_LLD_Wkpu_Reset();
        /* Enter low power */
        (void)Mcu_LLD_Set_Chip_Mode(Mcu_TargetModeConfigPtr);
    }
    #endif
    else
    {
        #if 0
        if( ((Mcu_TargetModeConfigPtr->Mcu_PLL0_En == 1U) || (Mcu_TargetModeConfigPtr->Mcu_PLL1_En == 1U))
            && (MC_ME_StPtr->GS.B.S_XOSC == 0U))
        {
            Mcu_CurrentModeConfig.Mcu_ChipMode = me_mc_drun_mode;
            Mcu_CurrentModeConfig.Mcu_IRC_En = Mcu_TargetModeConfigPtr->Mcu_IRC_En;
            Mcu_CurrentModeConfig.Mcu_XOSC_En = Mcu_TargetModeConfigPtr->Mcu_XOSC_En;
            Mcu_CurrentModeConfig.Mcu_PLL0_En = 0U;
            Mcu_CurrentModeConfig.Mcu_PLL1_En = 0U;
            Mcu_CurrentModeConfig.Mcu_TargetClock = CGM_SYSTEM_CLOCK_SRC_IRCOSC;
            (void)Mcu_LLD_Set_Chip_Mode(&Mcu_CurrentModeConfig);
        }
        #endif
        (void)Mcu_LLD_Set_Chip_Mode(Mcu_TargetModeConfigPtr);
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"



#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Mcu_ResetType, MCU_CODE) Mcu_LLD_GetResetReason(void)
{
    VAR(Mcu_ResetType, MCU_VAR) ResetReason = MCU_NO_RESET_REASON;
    VAR(uint32, MCU_VAR) RegValue = 0U;
    VAR(uint32, MCU_VAR) Index = 0U;
    VAR(uint32, MCU_VAR) ResetOffset = 0U;
    VAR(uint32, MCU_VAR) Count = 0U;

    RegValue = (MC_RGM.DES.R & RGM_DES_RWBITS_MASK32);
    if(RegValue != 0U)
    {
        Mcu_ReasonReg[0U] = RegValue;
    }
    RegValue = (MC_RGM.FES.R & RGM_FES_RWBITS_MASK32);
    if(RegValue != 0U)
    {
        Mcu_ReasonReg[1U] = RegValue;
    }

    for(Index = 0x00U; Index < 0x20U; Index++)
    {
        if(((uint32)(0x01UL << Index) & RGM_DES_RWBITS_MASK32) != 0U)
        {
            if((Mcu_ReasonReg[0U] & (uint32)(0x01UL << Index)) != 0U)
            {
                if(Count == 0U)
                {
                    ResetReason = (Mcu_ResetType) ResetOffset;
                    Count++;
                }
                else
                {
                    ResetReason = (Mcu_ResetType) MCU_MULTIPLE_RESET_REASON;
                    break;
                }
            }
            ResetOffset++;
        }
    }

    for(Index = 0x00U; Index < 0x20U; Index++)
    {
        if((((uint32)0x01UL << Index) & RGM_FES_RWBITS_MASK32) != 0U)
        {
            if((Mcu_ReasonReg[1U] & (uint32)(0x01UL << Index)) != 0U)
            {
                if(Count == 0U)
                {
                    ResetReason = (Mcu_ResetType) ResetOffset;
                    Count++;
                }
                else
                {
                    ResetReason = (Mcu_ResetType) MCU_MULTIPLE_RESET_REASON;
                    break;
                }
            }
            ResetOffset++;
        }
    }

    MC_RGM.DES.R = MC_RGM.DES.R;
    MC_RGM.FES.R = (MC_RGM.FES.R & RGM_FES_RWBITS_MASK32);
    return (Mcu_ResetType)ResetReason;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_LLD_GetResetRaw(void)
{
    VAR(Mcu_RawResetType, MCU_VAR) ResetRaw = (Mcu_RawResetType)0U;
    VAR(uint32, MCU_VAR) RegValue = 0U;
    VAR(uint32, MCU_VAR) ResetOffset = 0U;
    VAR(uint32, MCU_VAR) Index = 0U;

    RegValue = (uint32)(MC_RGM.DES.R & RGM_DES_RWBITS_MASK32);
    if(RegValue != 0U)
    {
        Mcu_ReasonReg[0U] = RegValue;
    }
    RegValue = (MC_RGM.FES.R & RGM_FES_RWBITS_MASK32);
    if(RegValue != 0U)
    {
        Mcu_ReasonReg[1U] = RegValue;
    }

    for(Index = 0x00U; Index < 0x20U; Index++)
    {
        if(((uint32)(0x01UL << Index) & RGM_DES_RWBITS_MASK32) != 0U)/*PRQA S 2896*/
        {
            if((Mcu_ReasonReg[0U] & (uint32)(0x01UL << Index)) != 0U)
            {
                if(ResetOffset < 32U)
                {
                    ResetRaw |= (uint32)(0x01UL << ResetOffset);
                }
            }
            ResetOffset++;
        }
    }
    for(Index = 0x00U; Index < 0x20U; Index++)
    {
        if(((uint32)(0x01UL << Index) & (uint32)RGM_FES_RWBITS_MASK32) != 0U)/*PRQA S 2896*/
        {
            if((Mcu_ReasonReg[1U] & (Mcu_RawResetType)(0x01UL << Index)) != 0U)
            {
                if(ResetOffset < 32U)
                {
                    ResetRaw |= (uint32)(0x01UL << ResetOffset);
                }
            }
            ResetOffset++;
        }
    }

    MC_RGM.DES.R = MC_RGM.DES.R;
    MC_RGM.FES.R = MC_RGM.FES.R;
    return (Mcu_RawResetType)ResetRaw;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(Mcu_RamStateType, MCU_CODE) Mcu_LLD_GetRamState(void)
{
    VAR(Mcu_RamStateType, MCU_VAR) RamState = MCU_RAMSTATE_INVALID;

    if(MEMU.ERR_FLAG.B.SR_CE == TRUE)
    {
    /* Do nothing */
    }
    else if(MEMU.ERR_FLAG.B.SR_UCE == TRUE)
    {
    /* Do nothing */
    }
    else if(MEMU.ERR_FLAG.B.PR_CE == TRUE)
    {
    /* Do nothing */
    }
    else if(MEMU.ERR_FLAG.B.PR_UCE == TRUE)
    {
    /* Do nothing */
    }
    else
    {
        RamState = MCU_RAMSTATE_VALID;
    }

    return (Mcu_RamStateType)RamState;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_PeriModeSet (P2CONST(Mcu_PeriConfigType, AUTOMATIC, MCU_APPL_CONST) PeriConfigPtr)
{
    VAR(uint32, MCU_VAR) index;
    for(index = 0U; index < (uint32)MC_ME_PERIPH_INSTANCE_COUNT; index++)
    {
        MC_ME_StPtr->PCTL[(uint8)PeriConfigPtr[index].McMePeriNameConfig].R = (     /* polyspace RTE:OBAI */
                                  (uint8)MC_ME_PCTLn_RUN_CFG(PeriConfigPtr[index].McMeRunConfig)
                                | (uint8)MC_ME_PCTLn_LP_CFG(PeriConfigPtr[index].McMeLowPowerConfig) );
    }
    (void)Mcu_LLD_ChangeMode(me_mc_mode_notchange);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_PeriResetPend 
    (P2CONST(Mcu_PeripheralResetType, AUTOMATIC, MCU_APPL_CONST) ResetConfigPtr)
{
    MC_RGM.PRST0.R = ResetConfigPtr->RgmGroup0;
    MC_RGM.PRST1.R = ResetConfigPtr->RgmGroup1;
    MC_RGM.PRST2.R = ResetConfigPtr->RgmGroup2;
    MC_RGM.PRST3.R = ResetConfigPtr->RgmGroup3;
    MC_RGM.PRST4.R = ResetConfigPtr->RgmGroup4;
    MC_RGM.PRST5.R = ResetConfigPtr->RgmGroup5;
    MC_RGM.PRST6.R = ResetConfigPtr->RgmGroup6;
    MC_RGM.PRST7.R = ResetConfigPtr->RgmGroup7;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_PeriResetClose (VAR(void, AUTOMATIC))
{
    MC_RGM.PRST0.R = 0x0U;
    MC_RGM.PRST1.R = 0x0U;
    MC_RGM.PRST2.R = 0x0U;
    MC_RGM.PRST3.R = 0x0U;
    MC_RGM.PRST4.R = 0x0U;
    MC_RGM.PRST5.R = 0x0U;
    MC_RGM.PRST6.R = 0x0U;
    MC_RGM.PRST7.R = 0x0U;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_CoreSynchronise (VAR(void, AUTOMATIC))
{
    VAR(uint8, MCU_VAR) CoreId;
    VAR(uint8, MCU_VAR) CoreIdx;
    volatile VAR(uint8, MCU_VAR) CoreStatus = CORE_NOT_READY;
    CoreId = Mcu_LLD_Get_Core_Id();
    Mcu_gCoreStatus[CoreId] = CORE_READY; /* polyspace RTE:OBAI */

    while(CoreStatus == CORE_NOT_READY)
    {
        for(CoreIdx=0; CoreIdx < MCU_CORE_COUNT; CoreIdx++)
        {
            if(Mcu_gCoreStatus[CoreIdx] == CORE_NOT_READY)
            {
                break;
            }
        }
        if(CoreIdx == MCU_CORE_COUNT)
        {
            CoreStatus = CORE_READY;
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#if MCU_FCCU_ENABLE == STD_ON
/*
 * @brief Clear Fault Status Register
 *
 * This function use to clear the rf fault status register
 *
 * @param[in] faultIndex: FCCU failure input signal index
 * @retval    E_OK: success clearing faults
 *            Std_ReturnTypeIMEOUT: timeout operation
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
Std_ReturnType FCCU_LLD_ClearFaults(uint8 faultIndex) /* PRQA S 1505 */
{
    uint8 index, regIdx, bitPos;
    uint32 timeout;
    Std_ReturnType status = (Std_ReturnType)E_OK;

    if (faultIndex >= FCCU_MAX_FAULTS_NO)
    {
        for (index = 0U; index < FCCU_RF_MAX_GROUP; index++)
        {
            /* set recoverable fault key */
            FCCU.RFK.R = FCCU_RECOVERABLE_FAULT_KEY;
            /* clear all faults */
            FCCU.RF_S[index].R = 0xFFFFFFFFU;
            /* wait operation 12 done */
            timeout = FCCU_OP_TIMEOUT_CONFIG;

            while ((FCCU.CTRL.B.OPS == (uint8)FCCU_OPS_IN_PROGRESS) && (timeout > 0U))
            {
                timeout--;
            }

            /* timeout happen */
            if (timeout == 0U)
            {
                status = (Std_ReturnType)E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        regIdx = faultIndex >> 5U;   /* divide by 32 */
        bitPos = faultIndex & 0x1FU; /* modulo by 32 */

        /* set recoverable fault key */
        FCCU.RFK.R = FCCU_RECOVERABLE_FAULT_KEY;
        if(bitPos < 32U)
        {
            /* clear all faults */
            FCCU.RF_S[regIdx].R = (uint32)(1UL << (uint32)bitPos);
        }
        /* wait operation 12 done */
        timeout = FCCU_OP_TIMEOUT_CONFIG;

        while ((FCCU.CTRL.B.OPS == (uint8)FCCU_OPS_IN_PROGRESS) && (timeout > 0U))
        {
            timeout--;
        }

        /* timeout happen */
        if (timeout == 0U)
        {
            status = (Std_ReturnType)E_NOT_OK;
        }


    }
    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Run operation
 *
 * This function use to run fcc operation
 *
 * @param[in] opRun: operation run
 * @retval    E_OK: success run operation
 *            Std_ReturnTypeIMEOUT: timeout run operation
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_RunOperation(const fccu_op_run_t opRun) /* PRQA S 1505 */
{
    Std_ReturnType status = (Std_ReturnType)E_OK;
    uint32 timeout = FCCU_OP_TIMEOUT_CONFIG;

    /* wait for the last operation complete */
    while (((uint8)FCCU_OPS_IN_PROGRESS == FCCU.CTRL.B.OPS) && (timeout != 0U))
    {
        timeout--;
    }

    if (0U == timeout)
    {
        status = (Std_ReturnType)E_NOT_OK;
    }

    if (status == (Std_ReturnType)E_OK)
    {
        /* get operation status */
        switch (opRun)
        {
            case FCCU_RUN_OP1:
                FCCU.CTRLK.R = FCCU_UNLOCK_OP1_KEY;
                FCCU.CTRL.R = (uint32)FCCU_RUN_OP1;
                break;
            case FCCU_RUN_OP2:
                FCCU.CTRLK.R = FCCU_UNLOCK_OP2_KEY;
                FCCU.CTRL.R = (uint32)FCCU_RUN_OP2;
                break;
            default:
                FCCU.CTRL.R = (uint32)opRun;
                break;
        }

        timeout = FCCU_OP_TIMEOUT_CONFIG;
        /* wait for the last operation complete */
        while (((uint8)FCCU_OPS_IN_PROGRESS == FCCU.CTRL.B.OPS) && (timeout != 0U))
        {
            timeout--;
        }

        if (0U == timeout)
        {
            status = (Std_ReturnType)E_NOT_OK;
        }
    }
    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Read Recoverable Faults
 *
 * This function update and read recoverable faults
 *
 * @param[in] flags: faults flags
 * @retval    E_OK: success run operation
 *            Std_ReturnTypeIMEOUT: timeout operation
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_ReadFaults(fccu_faults_flags_t *flags) /* PRQA S 1505 */
{
    uint8 index;
    Std_ReturnType status = (Std_ReturnType)E_OK;

    for (index = 0; index < FCCU_RF_MAX_GROUP; index++)
    {
        status = FCCU_LLD_RunOperation(FCCU_RUN_OP10);
        if ((Std_ReturnType)E_OK == status)
        {
            flags->faultsFlags[index] = FCCU.RF_S[index].R;
        }
        else
        {
            return status;
        }
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Read FCCU state
 *
 * This function use to read fccu state
 *
 * @retval the state of fccu module
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static fccu_status_t FCCU_LLD_GetState(void) /* PRQA S 1505 */
{
    Std_ReturnType status;
    fccu_status_t fccuStatus = FCCU_UNKNOWN_STATE;

    status = FCCU_LLD_RunOperation(FCCU_RUN_OP3);
    if ((Std_ReturnType)E_OK == status)
    {
        switch (FCCU.STAT.B.STATUS)
        {
            case 0U:
                fccuStatus = FCCU_NORMAL_STATE;
                break;
            case 1U:
                fccuStatus = FCCU_CONFIG_STATE;
                break;
            case 2U:
                fccuStatus = FCCU_ALARM_STATE;
                break;
            default:
                fccuStatus = FCCU_FAULT_STATE;
                break;
        }
    }

    return fccuStatus;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static uint8 FCCU_LLD_CheckFaultFlags(const fccu_faults_flags_t *faultFlags)
{
    uint32_t index;
    uint32_t bits;
    uint8 ret = FALSE;

    for (index = 0U; index < FCCU_RF_MAX_GROUP; index++)
    {
        for (bits = 0; bits < 32U; bits++)
        {
            if (index == 0U)
            {
                if (bits != 3U) /* do not check FCCU channel 3 faults input */
                {
                    if ((faultFlags->faultsFlags[index] & (0x1UL << bits)) != 0U)
                    {
                        ret = TRUE;
                        break;
                    }
                }
            }
            else if (index == 1U)
            {
                if ((bits != 11U) && (bits != 19U) && (bits != 22U)) /* do not check FCCU channel 43,51,54 faults input */
                {
                    if ((faultFlags->faultsFlags[index] & (0x1UL << bits)) != 0U)
                    {
                        ret = TRUE;
                        break;
                    }
                }
            }
            else
            {
                if ((faultFlags->faultsFlags[index] & (0x1UL << bits)) != 0U)
                {
                    ret = TRUE;
                    break;
                }
            }
        }

        if (TRUE == ret)
        {
            break;
        }
    }

    return ret;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/* @brief Set FCCU into config state
 *
 * This function set fccu into config state
 *
 * @retval E_OK: success to set fccu in config state
 *         Std_ReturnTypeIMEOUT: timeout operation
 *         FCCU_ERROR_SET_CONFIG: fail to set fccu in config state
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_SetConfigState(void) /* PRQA S 1505 */
{
    Std_ReturnType status = FCCU_ERROR_OTHER;
    fccu_status_t fccuStatus;
    fccu_faults_flags_t faultsFlags;
    uint8 isFaultExist = TRUE;
    uint32 timeout = FCCU_OP_TIMEOUT_CONFIG;
    uint8 fccuOpStatus;

    /* Unlock configuration */
    FCCU.TRANS_LOCK.R = FCCU_TRANSKEY_UNLOCK_VAL;

    fccuStatus = FCCU_LLD_GetState();
    if (fccuStatus == FCCU_NORMAL_STATE)
    {
        /* clear all faults */
        status = FCCU_LLD_ClearFaults(FCCU_MAX_FAULTS_NO);
        if ((Std_ReturnType)E_OK == status)
        {
            fccuOpStatus = (uint8)FCCU.CTRL.B.OPS;
            if ((uint8)FCCU_OPS_SUCCESSFUL != fccuOpStatus)
            {
                /* read FCCU state */
                (void)FCCU_LLD_RunOperation(FCCU_RUN_OP3);
            }

            /* set fccu to enter config state */
            (void)FCCU_LLD_RunOperation(FCCU_RUN_OP1);
        }
        fccuStatus = FCCU_LLD_GetState();
        if (FCCU_CONFIG_STATE == fccuStatus)
        {
            status = (Std_ReturnType)E_OK;
        }
        else
        {
            status = FCCU_ERROR_SET_CONFIG;
        }
    }
    else if (fccuStatus == FCCU_CONFIG_STATE)
    {
        status = (Std_ReturnType)E_OK;
    }
    else if (fccuStatus == FCCU_UNKNOWN_STATE)
    {
        status = FCCU_ERROR_SET_CONFIG;
    }
    else /* Alarm or Fault State */
    {
        do
        {
            status = FCCU_LLD_ClearFaults(FCCU_MAX_FAULTS_NO);
            if ((Std_ReturnType)E_OK == status)
            {
                status = FCCU_LLD_ReadFaults(&faultsFlags);
                if ((Std_ReturnType)E_OK == status)
                {
                    isFaultExist = FCCU_LLD_CheckFaultFlags(&faultsFlags);
                }
            }
            timeout--;
        } while ((isFaultExist == (uint8)TRUE) && (timeout != 0U));

        if (timeout == 0U)
        {
            status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* set fccu in noraml state */
            (void)FCCU_LLD_RunOperation(FCCU_RUN_OP2);
            if (FCCU_NORMAL_STATE != FCCU_LLD_GetState())
            {
                status = FCCU_ERROR_SET_CONFIG;
            }
            else
            {
                /* set fccu in config state */
                (void)FCCU_LLD_RunOperation(FCCU_RUN_OP1);
                if (FCCU_CONFIG_STATE != FCCU_LLD_GetState())
                {
                    status = FCCU_ERROR_SET_CONFIG;
                }
                else
                {
                    status = (Std_ReturnType)E_OK;
                }
            }
        }
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Set FCCU into normal state
 *
 * @retval E_OK: set fccu successfully
 *         FCCU_ERROR_SET_NORMAL: fails to set fccu state
 *         Std_ReturnTypeIMEOUT: run operation timeout
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_SetNormalState(void) /* PRQA S 1505 */
{
    uint8 isFaultExist = TRUE;
    uint32 timeout = FCCU_OP_TIMEOUT_CONFIG;
    Std_ReturnType status = FCCU_ERROR_OTHER;
    fccu_status_t fccuStatus;
    fccu_faults_flags_t faultsFlags;

    fccuStatus = FCCU_LLD_GetState();
    if (FCCU_NORMAL_STATE == fccuStatus)
    {
        /* fccu already in normal state */
        status = (Std_ReturnType)E_OK;
    }
    else if (FCCU_CONFIG_STATE == fccuStatus)
    {
        /* set fccu into noraml state */
        (void)FCCU_LLD_RunOperation(FCCU_RUN_OP2);
        if (FCCU_NORMAL_STATE == FCCU_LLD_GetState())
        {
            status = (Std_ReturnType)E_OK;
        }
        else
        {
            status = FCCU_ERROR_SET_NORMAL;
        }
    }
    else if ((FCCU_ALARM_STATE == fccuStatus) || (FCCU_FAULT_STATE == fccuStatus))
    {
        do
        {
            status = FCCU_LLD_ClearFaults(FCCU_MAX_FAULTS_NO);
            if ((Std_ReturnType)E_OK == status)
            {
                status = FCCU_LLD_ReadFaults(&faultsFlags);
                if ((Std_ReturnType)E_OK == status)
                {
                    isFaultExist = FCCU_LLD_CheckFaultFlags(&faultsFlags);
                }
            }
            timeout--;
        } while ((isFaultExist == TRUE) && (timeout != 0U));

        if (timeout == 0U)
        {
            status = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            (void)FCCU_LLD_RunOperation(FCCU_RUN_OP2);
            if (FCCU_NORMAL_STATE == FCCU_LLD_GetState())
            {
                status = (Std_ReturnType)E_OK;
            }
            else
            {
                status = FCCU_ERROR_SET_NORMAL;
            }
        }
    }
    else
    {
        status = FCCU_ERROR_SET_NORMAL;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Defines the preset value of the watchdog timer for the
 *        recovery from the CONFIG state
 *
 *
 * @param[in] to: configuration time-out value
 * @retval E_OK: set configuration timeout successfully
 *         FCCU_ERROR_CONFIG_TIMEOUT: fail to set configuration timeout
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
Std_ReturnType FCCU_LLD_SetCfgTimeout(uint8 to) /* PRQA S 1503 */
{
    fccu_status_t fccuState;
    Std_ReturnType status;

    fccuState = FCCU_LLD_GetState();
    if (FCCU_CONFIG_STATE == fccuState)
    {
        status = FCCU_LLD_SetNormalState();
        if ((Std_ReturnType)E_OK != status)
        {
            status = FCCU_ERROR_CONFIG_TIMEOUT;
        }
        else
        {
            FCCU.CFG_TO.R = to;
        }
    }
    else
    {
        FCCU.CFG_TO.R = to;
        status = (Std_ReturnType)E_OK;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Lock the fccu configuration
 *
 *
 * @param[in] lock: type of lock
 * @retval None
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static void FCCU_LLD_LockConfig(const Mcu_FccuLockType lock) /* PRQA S 1505 */
{
    switch (lock)
    {
        case FCCU_TRANSIENTLY_UNLOCK:
            FCCU.TRANS_LOCK.B.TRANSKEY = FCCU_TRANSKEY_UNLOCK_VAL;
            break;
        case FCCU_TRANSIENTLY_LOCK:
            FCCU.TRANS_LOCK.B.TRANSKEY = FCCU_TRANSKEY_LOCK_VAL;
            break;
        case FCCU_PERANENTLY_LOCK:
            FCCU.PERMNT_LOCK.B.PERMNTKEY = FCCU_PERMENTKEY_LOCK_VAL;
            break;
        default:
            /* Do nothing */
            break;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Check fccu IRQ_STAT register
 *
 *
 * @param[in] intStatus: status of interrupt
 * @retval 1: int bit occurs in IRQ_STAT register
 *         0: int bit nor occurs
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
uint8 FCCU_LLD_CheckIntStatus(fccu_int_status_t intStatus) /* PRQA S 1505 */
{
    uint32 regIrqStat = (uint32)FCCU.IRQ_STAT.R;
    if((uint32)intStatus < 32U)
    {
        regIrqStat &= (1UL << (uint32)intStatus);
    }
    return (regIrqStat != 0UL) ? 1U : 0U;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Clear fccu interrupt flag
 *
 *
 * @param[in] intStatus: status of interrupt
 * @retval None
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static void FCCU_LLD_ClearIntFlag(fccu_int_status_t intStatus) /* PRQA S 1505 */
{
    uint32 regIrqStat = 0U;
    if((uint32)intStatus < 32U)
    {
        FCCU.IRQ_STAT.R = FCCU.IRQ_STAT.R & ~(1UL << (uint32)intStatus);
        regIrqStat = (uint32)(1UL << (uint32)intStatus);
    }
    FCCU.IRQ_STAT.R = regIrqStat;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_ClockFailureCmu_ISR(void);
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*
 * @brief FCCU Alarm Interrupt Callback function
 *
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static void FCCU_LLD_AlarmIrqCallback(void)
{
    uint8 index;
    uint8 reg_index, bit_pos;
    VAR(uint32, MCU_VAR)Mcu_FccuRf;
    /* Update faults status */
    (void)FCCU_LLD_RunOperation(FCCU_RUN_OP10);

    for (index = 0U; index < Mcu_gFccuConfigPtr->Mcu_FccuRfCfgNumber; index++)
    {
        reg_index = Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel >> 5U; /* divide by 32 */
        bit_pos = Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel & 0x1FU; /* modulo by 32 */
        if(bit_pos < 32U)
        {
            Mcu_FccuRf = (uint32)FCCU.RF_S[reg_index].R;
            Mcu_FccuRf = (Mcu_FccuRf & (1UL << (uint32)bit_pos));
            if ((reg_index < FCCU_RF_MAX_GROUP) && ( Mcu_FccuRf != 0UL))
            {
                if((Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_FM_PLL_0_CH_29) 
                || (Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_FM_PLL_1_CH_30)
                || (Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_CMU_0_OSC_CH_31)
                || (Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_CMU_0_PLL_CH_32)
                || (Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_CMU_COMP_SUBSYS_CH_33)
                || (Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel == (uint8)FCCU_FAILURE_CMU_OTHER_CH_34))
                {
                    Mcu_ClockFailureCmu_ISR();
                }
                /* Clear Fault */
                (void)FCCU_LLD_ClearFaults(Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[index].Mcu_FccuChannel);
            }
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Set the recoverable fault configuration
 *
 *
 * @param[in] cfg: recoverable fault configuration
 * @retval E_OK: set recoverable configuration successfully
 *         FCCU_ERROR_SET_NORMAL: fail to set fccu in noraml state
 *         FCCU_ERROR_SET_CONFIG: fail to set fccu in config state
 *         Std_ReturnTypeIMEOUT: run operation timeout
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_SetRfConfig(const Mcu_FccuRfConfigType *cfg) /* PRQA S 1505 */
{
    uint8 regIdx;
    uint8 bitPos;
    Std_ReturnType status = (Std_ReturnType)E_OK;

    status = FCCU_LLD_SetConfigState();
    if ((Std_ReturnType)E_OK == status)
    {
        /* set rf configurations */
        regIdx = cfg->Mcu_FccuChannel >> 5U;   /* divide by 32 */
        bitPos = cfg->Mcu_FccuChannel & 0x1FU; /* modulo by 32 */
        if(bitPos < 32U)
        {
            /* recoverable fault configuration */
            FCCU.RF_CFG[regIdx].R = ((uint32)(FCCU.RF_CFG[regIdx].R & ~((uint32)1UL << bitPos))) | ((uint32)(((uint32)cfg->Mcu_FccuRecoveryConfig) << bitPos));

            /* allow fccu moves ALARM or FAULT state */
            FCCU.RF_E[regIdx].R = (FCCU.RF_E[regIdx].R & ~(1UL << bitPos)) | (1UL << bitPos);

            /* set timeout enable
            * 0 FCCU moves into the FAULT state if the respective fault is enabled
            * 1 FCCU moves into the ALARM state if the respective fault is enabled
            */
            FCCU.RF_TOE[regIdx].R = (FCCU.RF_TOE[regIdx].R & ~(1UL << bitPos)) \
                                    | (((cfg->Mcu_FccuToAlarmEn == TRUE) ? 1UL : 0UL) << bitPos);

            /* set irq alarm en */
            FCCU.IRQ_ALARM_EN[regIdx].R = (FCCU.IRQ_ALARM_EN[regIdx].R & ~(1UL << bitPos)) \
                                        | (((cfg->Mcu_FccuRfReactionEnCfg.irq_alarm_en == TRUE) ? 1UL : 0UL) << bitPos);
            /* set nmi en */
            FCCU.NMI_EN[regIdx].R = (FCCU.NMI_EN[regIdx].R & ~(1UL << bitPos)) \
                                | (((cfg->Mcu_FccuRfReactionEnCfg.nmi_en == TRUE) ? 1UL : 0UL) << bitPos);

            /* set eout signaling enable */
            FCCU.EOUT_SIG_EN[regIdx].R = (FCCU.EOUT_SIG_EN[regIdx].R & ~(1UL << bitPos))
                                    | (((cfg->Mcu_FccuRfReactionEnCfg.eout_sig_en == TRUE) ? 1UL : 0UL) << bitPos);

            /* set reset Mcu_FccuRfReactionEnCfg */
            regIdx = cfg->Mcu_FccuChannel >> 4U;   /* divide by 16 */
            bitPos = (uint8)((cfg->Mcu_FccuChannel & 0xFU) << 1U); /* modulo by 16 */

            FCCU.RFS_CFG[regIdx].R = (FCCU.RFS_CFG[regIdx].R & ~(3UL << bitPos)) | (((uint32)cfg->Mcu_FccuReactionConfig ) << bitPos);
        }

        status = (Std_ReturnType)FCCU_LLD_SetNormalState();
    }
    else
    {
        status = (Std_ReturnType)E_NOT_OK;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Set fccu eout configuration
 *
 *
 * @param[in] eoutCfg: configuration of errpin out
 * @retval E_OK: set fccu eout configuration successfully
 *         FCCU_ERROR_SET_EOUT: fail to set fccu eout configuration
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static Std_ReturnType FCCU_LLD_SetEout(const Mcu_FccuEoutConfigType *eoutCfg) /* PRQA S 1505,3673 */
{
    Std_ReturnType status;

    status = FCCU_LLD_SetConfigState();
    if ((Std_ReturnType)E_OK == status)
    {
        FCCU.CFG.B.FCCU_SET_AFTER_RESET = (eoutCfg->set_after_reset == TRUE) ? 1U : 0U;
        // FCCU.CFG.B.FCCU_SET_CLEAR = (uint8)eoutCfg->control;
        // FCCU.CFG.B.OD = (uint8)eoutCfg->output;
        FCCU.CFG.B.SM = (uint8)eoutCfg->switch_mode;
        FCCU.CFG.B.PS = (uint8)eoutCfg->polarity_sel;
        FCCU.CFG.B.FOM = (uint8)eoutCfg->mode;
        FCCU.DELTA_T.B.DELTA_T = eoutCfg->delta_t_value;
    }
    else
    {
         status = FCCU_ERROR_SET_EOUT;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Read the FCCU frozen status flags
 *
 *
 * @param[in] frozenType: type of frozen status
 * @param[in] frozenStatus: pointer to frozen status address
 * @retval E_OK: read status successfully
 *         FCCU_ERROR_UPDATE_FREEZE: fail to read frozen status
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
Std_ReturnType FCCU_LLD_GetFrozenStatus(fccu_frozen_type_t frozenType, uint16 *frozenStatus) /* PRQA S 1503 */
{
    Std_ReturnType status = FCCU_ERROR_UPDATE_FREEZE;

    switch (frozenType)
    {
    case FCCU_FROZEN_N2AF_STATUS:
        status = FCCU_LLD_RunOperation(FCCU_RUN_OP4);
        if ((Std_ReturnType)E_OK != status)
        {
            return status;
        }
        if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
        {
            *frozenStatus = (uint16)FCCU.N2AF_STATUS.B.NAFS;
            status = (Std_ReturnType)E_OK;
        }
        break;
    case FCCU_FROZEN_A2FF_STATUS:
        status = FCCU_LLD_RunOperation(FCCU_RUN_OP5);
        if ((Std_ReturnType)E_OK != status)
        {
            return status;
        }
        if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
        {
            *frozenStatus = (uint16)FCCU.A2FF_STATUS.B.AFFS;
            status = (Std_ReturnType)E_OK;
        }
        break;
    case FCCU_FROZEN_N2FF_STATUS:
        status = FCCU_LLD_RunOperation(FCCU_RUN_OP6);
        if ((Std_ReturnType)E_OK != status)
        {
            return status;
        }
        if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
        {
            *frozenStatus = (uint16)FCCU.N2FF_STATUS.B.NFFS;
            status = (Std_ReturnType)E_OK;
        }
        break;
    case FCCU_FROZEN_F2AF_STATUS:
        status = FCCU_LLD_RunOperation(FCCU_RUN_OP7);
        if ((Std_ReturnType)E_OK != status)
        {
            return status;
        }
        if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
        {
            *frozenStatus = (uint16)FCCU.F2A_STATUS.B.FAFS;
            status = (Std_ReturnType)E_OK;
        }
        break;
    default:
        status = FCCU_ERROR_UPDATE_FREEZE;
        break;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Clear the freeze status register
 *
 *
 * @retval E_OK: clear status register successfully
 *         E_OK: fail to clear status register
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
Std_ReturnType FCCU_LLD_ClearFreezeStatus(void) /* PRQA S 1503 */
{
    Std_ReturnType status;

    (void)FCCU_LLD_RunOperation(FCCU_RUN_OP13);
    if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
    {
        status = (Std_ReturnType)E_OK;
    }
    else
    {
        status = FCCU_ERROR_CLEAR_FREEZE;
    }

    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Return the XTMR register value
 *
 *
 * @param[in] xtmrType: type of xtmr value
 * @retval the value of XTMR register
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
uint32 FCCU_LLD_GetXtmrValue(fccu_xtmr_type_t xtmrType) /* PRQA S 1503 */
{
    Std_ReturnType status = (Std_ReturnType)E_OK;
    uint32 value = 0U;

    switch (xtmrType)
    {
        case FCCU_XTMR_ALARM:
            status = FCCU_LLD_RunOperation(FCCU_RUN_OP17);
            break;
        case FCCU_XTMR_CFG:
            status = FCCU_LLD_RunOperation(FCCU_RUN_OP19);
            break;
        case FCCU_XTMR_ETMR:
            status = FCCU_LLD_RunOperation(FCCU_RUN_OP20);
            break;
        default:
            value = 0U;
            break;
    }

    if ((Std_ReturnType)E_OK == status)
    {
        if ((uint8)FCCU_OPS_SUCCESSFUL == FCCU.CTRL.B.OPS)
        {
            value = FCCU.XTMR.R;
        }
    }

    return value;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Trigger a recoverable fault fake to test
 *
 *
 * @param[in] fakeCode: trogger fake fault Mcu_FccuChannel
 * @retval None
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
void FCCU_LLD_SetRfFake(fccu_failure_inputs_t fakeCode)
{
    FCCU.RFF.B.FRFC = (uint8)fakeCode;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*
 * @brief Initializes the fccu module
 *
 *
 * @param[in] config: fccu module configuration
 * @param[in] rfConfig: fccu recoverable faults configuration
 * @retval    E_OK: init successfully
 *            FCCU_ERROR_SET_NORMAL: fail to set fccu goto normal state
 *            FCCU_ERROR_SET_CONFIG: fail to set fccu goto config state
 *            Std_ReturnTypeIMEOUT: in case of a timeout operation
 */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
VAR(Std_ReturnType, MCU_CODE)Mcu_LLD_FccuInit
(
    P2CONST( Mcu_FccuConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_FccuConfigPtr
)
{
    Std_ReturnType status = FCCU_ERROR_OTHER;\
    VAR(uint8, MCU_VAR)Mcu_Idx;
    Mcu_gFccuConfigPtr = Mcu_FccuConfigPtr;
    /* set debug mode */
    FCCU.CTRL.B.DEBUG = FALSE;
    /* set filter bypass and width */
    FCCU.CTRL.B.FILTER_BYPASS = (uint32)Mcu_gFccuConfigPtr->Mcu_FccuFilterBypassEn;
    if (TRUE == Mcu_gFccuConfigPtr->Mcu_FccuFilterBypassEn)
    {
        FCCU.CTRL.B.FILTER_WIDTH = Mcu_gFccuConfigPtr->Mcu_FccuFilterWidth;
    }
    /* enable timeout interrupt */
    if (Mcu_gFccuConfigPtr->Mcu_FccuIrqTypeConfig == FCCU_IRQ_CFG_TO_IEN)
    {
        FCCU.IRQ_EN.B.CFG_TO_IEN = 0x1U;
    }

    /* set fccu goto config state */
    status = FCCU_LLD_SetConfigState();
    if ((Std_ReturnType)E_OK == status)
    {
        FCCU.CFG_TO.B.TO = Mcu_gFccuConfigPtr->Mcu_FccuCfgTimeout;

        status = FCCU_LLD_SetEout(&Mcu_gFccuConfigPtr->Mcu_FccuEoutConfig);
        if ((Std_ReturnType)E_OK != status)
        {
            return status;
        }

        for (Mcu_Idx = 0U; Mcu_Idx < Mcu_gFccuConfigPtr->Mcu_FccuRfCfgNumber; Mcu_Idx++)
        {
            status = FCCU_LLD_SetRfConfig(&Mcu_gFccuConfigPtr->Mcu_FccuRfConfigPtr[Mcu_Idx]);
            if ((Std_ReturnType)E_OK != status)
            {
                break;
            }
        }
    }

    if ((Std_ReturnType)E_OK == status)
    {
        status = FCCU_LLD_SetNormalState();
        if ((Std_ReturnType)E_OK == status)
        {
            FCCU_LLD_LockConfig(Mcu_gFccuConfigPtr->Mcu_FccuLockTypeConfig);
        }
    }
    return status;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif

#if MCU_FCCU_ENABLE == STD_ON
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
static FUNC(void, MCU_CODE) Mcu_ClockFailureCmu_ISR(void)
{
    VAR(uint32, MCU_VAR) IndexCmu = 0U;
    CONSTP2VAR(CMU_Type, MCU_CONST, MCU_APPL_CONST) Mcu_CmuPtr[] = CMU_BASE_PTRS;
    #if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    (void)Dem_SetEventStatus(Mcu_gConfigPtr->Mcu_DemConfigPtr->Mcu_E_ClockFailureCfg.id, Mcu_gConfigPtr->Mcu_DemConfigPtr->Mcu_E_ClockFailureCfg.id);
    #endif

    #if (MCU_CLOCKS_FAILURE_EN == STD_ON)
    if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_ClockFailureNotification != NULL_PTR)
    {
        (void)Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_ClockFailureNotification();
    }
    #endif

    for(IndexCmu = 0U; IndexCmu < CMU_INSTANCE_COUNT; IndexCmu++)
    {
        if(Mcu_CmuPtr[IndexCmu]->ISR.R != 0U)
        {
            Mcu_CmuPtr[IndexCmu]->ISR.R = Mcu_CmuPtr[IndexCmu]->ISR.R;
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_XoscISR(void)
{
    if(Mcu_gConfigPtr != NULL_PTR)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_XoscStartupNotification != NULL_PTR)
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_XoscStartupNotification();
        }
    }
    if(XOSC_StPtr->CTL.B.I_OSC == TRUE)
    {
        XOSC_StPtr->CTL.B.I_OSC = TRUE;
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_InvalidConfig_ISR(void)
{
    if(MC_ME_StPtr->IS.B.I_ICONF_CC == TRUE)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification_Core != NULL_PTR) /* polyspace RTE:IDP */
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification_Core();
        }
        MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_ICONF_CC;
    }else if(MC_ME_StPtr->IS.B.I_ICONF_CU == TRUE)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification_Clock != NULL_PTR) /* polyspace RTE:IDP */
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification_Clock();
        }
        MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_ICONF_CU;
    }
    else if(MC_ME_StPtr->IS.B.I_ICONF == TRUE)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification != NULL_PTR) /* polyspace RTE:IDP */
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidConfigNotification();
        }
        MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_ICONF;
    }
    else
    {
        /* Do nothing */
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_InvalidMode_ISR(void)
{
    if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidModeNotification != NULL_PTR) /* polyspace RTE:IDP */
    {
        Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_InvalidModeNotification();
    }
    MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_IMODE;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_SafeMode_ISR(void)
{
    if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_SafeModeNotification != NULL_PTR) /* polyspace RTE:IDP */
    {
        Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_SafeModeNotification();
    }
    MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_SAFE;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_ModeComplete_ISR(void)
{
    if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_ModeCompleteNotification != NULL_PTR) /* polyspace RTE:IDP */
    {
        Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_ModeCompleteNotification();
    }
    MC_ME_StPtr->IS.R = MC_ME_StPtr->IS.B.I_MTC;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_VoltageError_ISR(void)
{
    VAR(uint16, MCU_VAR) VoltageIsrFlag = 0U;
    if(PMCDIG.EPR_VD3.R != 0U)
    {
        PMCDIG.EPR_VD3.R = PMCDIG.EPR_VD3.R;
        VoltageIsrFlag |= (uint16)(1UL << 3);
    }
    if(PMCDIG.EPR_VD4.R != 0U)
    {
        PMCDIG.EPR_VD4.R = PMCDIG.EPR_VD4.R;
        VoltageIsrFlag |= (uint16)(1UL << 4);
    }
    if(PMCDIG.EPR_VD7.R != 0U)
    {
        PMCDIG.EPR_VD7.R = PMCDIG.EPR_VD7.R;
        VoltageIsrFlag |= (uint16)(1UL << 7);
    }
    if(PMCDIG.EPR_VD8.R != 0U)
    {
        PMCDIG.EPR_VD8.R = PMCDIG.EPR_VD8.R;
        VoltageIsrFlag |= (uint16)(1UL << 8);
    }
    if(PMCDIG.EPR_VD9.R != 0U)
    {
        PMCDIG.EPR_VD9.R = PMCDIG.EPR_VD9.R;
        VoltageIsrFlag |= (uint16)(1UL << 9);
    }
    if(PMCDIG.EPR_VD10.R != 0U)
    {
        PMCDIG.EPR_VD10.R = PMCDIG.EPR_VD10.R;
        VoltageIsrFlag |= (uint16)(1UL << 10);
    }
    if(PMCDIG.EPR_VD12.R != 0U)
    {
        PMCDIG.EPR_VD12.R = PMCDIG.EPR_VD12.R;
        VoltageIsrFlag |= (uint16)(1UL << 12);
    }
    if(PMCDIG.EPR_VD13.R != 0U)
    {
        PMCDIG.EPR_VD13.R = PMCDIG.EPR_VD13.R;
        VoltageIsrFlag |= (uint16)(1UL << 13);
    }
    if(PMCDIG.EPR_VD14.R != 0U)
    {
        PMCDIG.EPR_VD14.R = PMCDIG.EPR_VD14.R;
        VoltageIsrFlag |= (uint16)(1UL << 14);
    }
    if(PMCDIG.EPR_VD15.R != 0U)
    {
        PMCDIG.EPR_VD15.R = PMCDIG.EPR_VD15.R;
        VoltageIsrFlag |= (uint16)(1UL << 15);
    }
    if(VoltageIsrFlag != 0U)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuVoltageErrorNotification != NULL_PTR) /* polyspace RTE:IDP */
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuVoltageErrorNotification();
        }
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE)Mcu_LLD_TemperatureErrorError_ISR(void)
{
    if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuTemperatureErrorNotification != NULL_PTR) /* polyspace RTE:IDP */
    {
        Mcu_gConfigPtr->Mcu_NotifyConfigPtr->McuTemperatureErrorNotification();
    }
    PMCDIG.EPR_TD.R = PMCDIG.EPR_TD.R;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#if MCU_FCCU_ENABLE == STD_ON
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_CODE) Mcu_LLD_Fccu_ISR(void)
{
    if(FCCU.IRQ_STAT.B.ALRM_STAT == TRUE)
    {
        FCCU_LLD_AlarmIrqCallback();
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_FccuAlarmNotification != NULL_PTR)
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_FccuAlarmNotification();
        }
        FCCU_LLD_ClearIntFlag(FCCU_INT_ALARM);
    }
    if(FCCU.IRQ_STAT.B.CFG_TO_STAT == TRUE)
    {
        if(Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_FccuCfgToNotification != NULL_PTR)
        {
            Mcu_gConfigPtr->Mcu_NotifyConfigPtr->Mcu_FccuCfgToNotification();
        }
        FCCU_LLD_ClearIntFlag(FCCU_INT_TIMEOUT);
    }
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif


#ifdef __cplusplus
}
#endif
