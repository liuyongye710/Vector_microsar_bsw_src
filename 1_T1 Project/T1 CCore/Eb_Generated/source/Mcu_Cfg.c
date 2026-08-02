/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC
*   Peripheral           : MCU
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/
/*PRQA S 1258,1259,380,3408,0704,0499,4399,2053 EOF*/
/**
*   @file    Mcu_PBcfg.c
*   @version 3.0.0
*
*      AUTOSAR 4.4.0 - Common Level Driver source file.
*    Autosar layer of Mcu MCAL driver.
*
*   @addtogroup Mcu
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==============================================INCLUDE FILES=======================================*/

#include "Mcu_Cfg.h"
#include "Mcu.h"
#include "Mcu_LLDriver.h"

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/

#define MCU_PB_VENDOR_ID_C                 176
#define MCU_PB_AR_MAJOR_VER_C              4
#define MCU_PB_AR_MINOR_VER_C              4
#define MCU_PB_AR_PATCH_VER_C              0
#define MCU_PB_SW_MAJOR_VER_C              3
#define MCU_PB_SW_MINOR_VER_C              0
#define MCU_PB_SW_PATCH_VER_C              0

/*============================================FILE VERSION CHECKS===================================*/

#if (MCU_PB_VENDOR_ID_C != MCU_CFG_VENDOR_ID)
#error "NON-MATCHED DATA : MCU_CFG_VENDOR_ID"
#endif

/* Check if current file and MCU header file are of the same Autosar version */
#if (MCU_PB_AR_MAJOR_VER_C != MCU_CFG_AR_MAJOR_VER)
#error "NON-MATCHED DATA : MCU_CFG_AR_MAJOR_VER"
#endif
#if (MCU_PB_AR_MINOR_VER_C != MCU_CFG_AR_MINOR_VER)
#error "NON-MATCHED DATA : MCU_CFG_AR_MINOR_VER"
#endif
#if (MCU_PB_AR_PATCH_VER_C != MCU_CFG_AR_PATCH_VER)
#error "NON-MATCHED DATA : MCU_CFG_AR_PATCH_VER"
#endif

/* Check if current file and MCU header file are of the same Software version */
#if (MCU_PB_SW_MAJOR_VER_C != MCU_CFG_SW_MAJOR_VER)
#error "NON-MATCHED DATA : MCU_CFG_SW_MAJOR_VER"
#endif
#if (MCU_PB_SW_MINOR_VER_C != MCU_CFG_SW_MINOR_VER)
#error "NON-MATCHED DATA : MCU_CFG_SW_MINOR_VER"
#endif
#if (MCU_PB_SW_PATCH_VER_C != MCU_CFG_SW_PATCH_VER)
#error "NON-MATCHED DATA : MCU_CFG_SW_PATCH_VER"
#endif


/* MCU_HARDVAR 2 */







/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_CoreConfigType, MCU_CONST) Mcu_CoreConfiguration = 
{
    .Mcme_Caddr0_Config = (uint32)(MC_ME_CADDR_RESET_ENABLE | (0x01100000U & MC_ME_CADDR_ADDR_MASK32) ),
    /* Core Control Register (ME_CADDR1) */
    .Mcme_Caddr1_Config = (uint32)(MC_ME_CADDR_RESET_ENABLE | (0x01100000U & MC_ME_CADDR_ADDR_MASK32) ),
    /* Core Contro2 Register (ME_CADDR3) */
    .Mcme_Caddr2_Config = (uint32)(MC_ME_CADDR_RESET_ENABLE),
    /* Core Contro3 Register (ME_CADDR3) */
    .Mcme_Caddr3_Config = (uint32)(MC_ME_CADDR_RESET_ENABLE | (0x01100000U & MC_ME_CADDR_ADDR_MASK32) ),
    /* Core Contro4 Register (ME_CADDR3) */
    .Mcme_Caddr4_Config = (uint32)(MC_ME_CADDR_RESET_DISABLE | (0x00000000U & MC_ME_CADDR_ADDR_MASK32) ),

    /* Core Control Register (ME_CCTL0) */
    .Mcme_Cctrl0_Config = (uint16)(
        (MC_ME_CCTL_RUN3_ON) |
        (MC_ME_CCTL_RUN2_ON) |
        (MC_ME_CCTL_RUN1_ON) |
        (MC_ME_CCTL_RUN0_ON) |
        (MC_ME_CCTL_DRUN_ON) |
        (MC_ME_CCTL_SAFE_ON)
    ),
    /* Core Control Register (ME_CCTL1) */
    .Mcme_Cctrl1_Config = (uint16)(
        (MC_ME_CCTL_RUN3_ON) |
        (MC_ME_CCTL_RUN2_ON) |
        (MC_ME_CCTL_RUN1_ON) |
        (MC_ME_CCTL_RUN0_ON) |
        (MC_ME_CCTL_DRUN_ON) |
        (MC_ME_CCTL_SAFE_ON)
    ),
    /* Core Control Register (ME_CCTL2) */
    .Mcme_Cctrl2_Config = (uint16)(
        (MC_ME_CCTL_RUN3_ON) |
        (MC_ME_CCTL_RUN2_ON) |
        (MC_ME_CCTL_RUN1_ON) |
        (MC_ME_CCTL_RUN0_ON) |
        (MC_ME_CCTL_DRUN_ON) |
        (MC_ME_CCTL_SAFE_ON)
    ),
    /* Core Control Register (ME_CCTL3) */
    .Mcme_Cctrl3_Config = (uint16)(
        (MC_ME_CCTL_RUN3_ON) |
        (MC_ME_CCTL_RUN2_ON) |
        (MC_ME_CCTL_RUN1_ON) |
        (MC_ME_CCTL_RUN0_ON) |
        (MC_ME_CCTL_DRUN_ON) |
        (MC_ME_CCTL_SAFE_ON)
    ),
    /* Core Control Register (ME_CCTL4) */
    .Mcme_Cctrl4_Config = (uint16)(
        (MC_ME_CCTL_RUN3_OFF) |
        (MC_ME_CCTL_RUN2_OFF) |
        (MC_ME_CCTL_RUN1_OFF) |
        (MC_ME_CCTL_RUN0_OFF) |
        (MC_ME_CCTL_DRUN_OFF) |
        (MC_ME_CCTL_SAFE_OFF)
    ),
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_PeriConfigType, MCU_CONST) McuPeripheralConfig_0[]= 
{
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EBI0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LFAST_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SIPI0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SIUL_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PIT_RTC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PIT_RTC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DMAMUX_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CRC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAM_RAM_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAM_RAM_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_RAM_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_RAM_CTRL_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_SAMPLER_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_RTC_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_16_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_14_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_IIC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SENT_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_FLEXRAY_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_b_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_GTMINT_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ETPU_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ETPU_C_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EMIOS_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EMIOS_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_I2S_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_I2S_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_S_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CRC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_15_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_IIC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SENT_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_FLEXRAY_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TMEP0,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TMEP1,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_PeriConfigType, MCU_CONST) McuPeripheralConfig_1[]= 
{
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EBI0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LFAST_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SIPI0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SIUL_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PIT_RTC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PIT_RTC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DMAMUX_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CRC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAM_RAM_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAM_RAM_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_RAM_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_RAM_CTRL_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_MCAN9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TTCAN_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CAN_SAMPLER_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_RTC_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_16_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_14_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_IIC_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SENT_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_FLEXRAY_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_b_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_GTMINT_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ETPU_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ETPU_C_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EMIOS_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_EMIOS_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_I2S_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_I2S_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_4_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CANFD_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_S_0_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_CRC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSD_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_15_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_12_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_11_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_LINFlexD_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_DSPI_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_IIC_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_SENT_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_FLEXRAY_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_PSI5_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_10_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_9_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_8_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_7_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_6_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_5_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_3_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_2_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_ADCSAR_1_INDEX,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TMEP0,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
    {
        .McMePeriNameConfig = (Mcu_McMePeriNameType)MC_ME_PCTL_TMEP1,
        .McMeRunConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0,
        .McMeLowPowerConfig = (Mcu_McMePeriConfigType)MC_ME_PERIPH_CONFIG_0 },
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_McMeConfigType, MCU_CONST) Mcu_McMeConfiguration = 
{
    .McMeMe = (uint32)(
        /* McuModeRun1 */  (uint32) (MCU_MCME_RUN1)
        /* McuModeRun2 */ |(uint32) (MCU_MCME_RUN2)
        /* McuModeRun3 */ |(uint32) (0U)
        /* McuModeHalt */ |(uint32) (MCU_MCME_HALT)
        /* McuModeStop */ |(uint32) (MCU_MCME_STOP)
        /* McuModeStandby */ |(uint32) (MCU_MCME_STANDBY)
    ),

    .McMeRunConfig = {
        (uint32) ( /* McuRunConfig 0 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (MCU_MCME_DRUN)
                /* McuModeRun0 */ |(uint32) (MCU_MCME_RUN0)
                /* McuModeRun1 */ |(uint32) (MCU_MCME_RUN1)
                /* McuModeRun2 */ |(uint32) (MCU_MCME_RUN2)
                /* McuModeRun3 */ |(uint32) (MCU_MCME_RUN3) ),
        (uint32) ( /* McuRunConfig 1 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 2 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 3 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 4 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 5 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 6 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
        (uint32) ( /* McuRunConfig 7 */
                /* McuModeSafe */  (uint32) (0U)
                /* McuModeDrun */ |(uint32) (0U)
                /* McuModeRun0 */ |(uint32) (0U)
                /* McuModeRun1 */ |(uint32) (0U)
                /* McuModeRun2 */ |(uint32) (0U)
                /* McuModeRun3 */ |(uint32) (0U) ),
    },

    .McMeLowPowerConfig = {
        (uint32)( /* McuLowPowerConfig 0 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 1 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 2 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 3 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 4 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 5 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 6 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
        (uint32)( /* McuLowPowerConfig 7 */
            /* McuModeHalt */     (uint32) (0U)
            /* McuModeStop */    |(uint32) (0U)
            /* McuModeStandby */ |(uint32) (0U) ),
    },

    .McMePeripheralConfig = {
        /* McuPeripheralConfig 0 */&McuPeripheralConfig_0[0U],
        /* McuPeripheralConfig 1 */&McuPeripheralConfig_1[0U],
    },

    .Mcu_McMeIrqCfg = (uint32_t)(
        (uint32_t)(0U)
        |(uint32_t)(0U)
        |(uint32_t)(0U)
        |(uint32_t)(0U)
        |(uint32_t)(0U)
        |(uint32_t)(0U)
    ),
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_PeripheralResetType, MCU_CONST) McuResetSetting_0 = 
{
    .RgmGroup0 = (uint32)( 0U
        ),

    .RgmGroup1 = (uint32)( 0U
                | MCU_RGM_MCAN_12
                | MCU_RGM_ADCSD_0
                | MCU_RGM_ADCSD_2
                | MCU_RGM_ADCSD_4
                | MCU_RGM_ADCSD_6
                | MCU_RGM_ADCSD_8
                | MCU_RGM_CRC_0
                | MCU_RGM_DMAMUX_0
        ),

    .RgmGroup2 = (uint32)( 0U
                | MCU_RGM_LINFlexD_0
                | MCU_RGM_LINFlexD_1
                | MCU_RGM_LINFlexD_3
                | MCU_RGM_LINFlexD_14
                | MCU_RGM_LINFlexD_16
                | MCU_RGM_TTCAN2
                | MCU_RGM_MCAN_9
                | MCU_RGM_MCAN_10
                | MCU_RGM_MCAN_8
                | MCU_RGM_MCAN_7
                | MCU_RGM_MCAN_6
                | MCU_RGM_MCAN_5
                | MCU_RGM_CAN_RAM_CTR
                | MCU_RGM_TTCAN
                | MCU_RGM_MCAN_1
                | MCU_RGM_MCAN_2
                | MCU_RGM_MCAN_3
                | MCU_RGM_MCAN_4
                | MCU_RGM_CAN_RAM1_CTR
        ),

    .RgmGroup3 = (uint32)( 0U
                | MCU_RGM_ADCSAR_0
                | MCU_RGM_ADCSAR_4
                | MCU_RGM_ADCSAR_b
                | MCU_RGM_PSI5_0
                | MCU_RGM_FLEXRAY_0
                | MCU_RGM_SENT_0
                | MCU_RGM_IIC_0
                | MCU_RGM_DSPI_0
                | MCU_RGM_DSPI_1
                | MCU_RGM_DSPI_4
                | MCU_RGM_DSPI_6
        ),
    
    .RgmGroup4 = (uint32)( 0U
                | MCU_RGM_CANFD12
                | MCU_RGM_CANFD11
                | MCU_RGM_CANFD10
                | MCU_RGM_CANFD9
                | MCU_RGM_CANFD8
                | MCU_RGM_CANFD7
                | MCU_RGM_CANFD6
                | MCU_RGM_CANFD5
                | MCU_RGM_CANFD4
                | MCU_RGM_CANFD3
                | MCU_RGM_CANFD2
                | MCU_RGM_CANFD1
                | MCU_RGM_EMIOS1
                | MCU_RGM_EMIOS0
                | MCU_RGM_ETPU_C
                | MCU_RGM_ETPU
                | MCU_RGM_GTMINT
        ),

    .RgmGroup5 = (uint32)( 0U
                | MCU_RGM_ADCSD_1
                | MCU_RGM_ADCSD_3
                | MCU_RGM_ADCSD_5
                | MCU_RGM_ADCSD_7
                | MCU_RGM_ADCSD_9
                | MCU_RGM_FCCU
                | MCU_RGM_CRC_1
                | MCU_RGM_PSI5_S_0
        ),

    .RgmGroup6 = (uint32)( 0U
                | MCU_RGM_LINFlexD_2
                | MCU_RGM_LINFlexD_7
                | MCU_RGM_LINFlexD_8
                | MCU_RGM_LINFlexD_9
                | MCU_RGM_LINFlexD_10
                | MCU_RGM_LINFlexD_11
                | MCU_RGM_LINFlexD_12
                | MCU_RGM_LINFlexD_15
        ),

    .RgmGroup7 = (uint32)( 0U
                | MCU_RGM_ADCSAR_1
                | MCU_RGM_ADCSAR_2
                | MCU_RGM_ADCSAR_3
                | MCU_RGM_ADCSAR_5
                | MCU_RGM_ADCSAR_6
                | MCU_RGM_ADCSAR_7
                | MCU_RGM_ADCSAR_8
                | MCU_RGM_ADCSAR_9
                | MCU_RGM_ADCSAR_10
                | MCU_RGM_PSI5_1
                | MCU_RGM_FLEXRAY_1
                | MCU_RGM_SENT_1
                | MCU_RGM_IIC_1
                | MCU_RGM_DSPI_2
                | MCU_RGM_DSPI_3
                | MCU_RGM_DSPI_5
        ),
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_PeripheralResetType, MCU_CONST) McuResetSetting_1 = 
{
    .RgmGroup0 = (uint32)( 0U
        ),

    .RgmGroup1 = (uint32)( 0U
                | MCU_RGM_MCAN_12
                | MCU_RGM_ADCSD_0
                | MCU_RGM_ADCSD_2
                | MCU_RGM_ADCSD_4
                | MCU_RGM_ADCSD_6
                | MCU_RGM_ADCSD_8
                | MCU_RGM_CRC_0
                | MCU_RGM_DMAMUX_0
        ),

    .RgmGroup2 = (uint32)( 0U
                | MCU_RGM_DSPI_12
                | MCU_RGM_LINFlexD_0
                | MCU_RGM_LINFlexD_1
                | MCU_RGM_LINFlexD_3
                | MCU_RGM_LINFlexD_14
                | MCU_RGM_LINFlexD_16
                | MCU_RGM_TTCAN2
                | MCU_RGM_MCAN_9
                | MCU_RGM_MCAN_10
                | MCU_RGM_MCAN_8
                | MCU_RGM_MCAN_7
                | MCU_RGM_MCAN_6
                | MCU_RGM_MCAN_5
                | MCU_RGM_CAN_RAM_CTR
                | MCU_RGM_TTCAN
                | MCU_RGM_MCAN_1
                | MCU_RGM_MCAN_2
                | MCU_RGM_MCAN_3
                | MCU_RGM_MCAN_4
                | MCU_RGM_CAN_RAM1_CTR
                | MCU_RGM_MCAN_11
        ),

    .RgmGroup3 = (uint32)( 0U
                | MCU_RGM_ADCSAR_0
                | MCU_RGM_ADCSAR_4
                | MCU_RGM_ADCSAR_b
                | MCU_RGM_PSI5_0
                | MCU_RGM_FLEXRAY_0
                | MCU_RGM_SENT_0
                | MCU_RGM_IIC_0
                | MCU_RGM_DSPI_0
                | MCU_RGM_DSPI_1
                | MCU_RGM_DSPI_4
                | MCU_RGM_DSPI_6
        ),
    
    .RgmGroup4 = (uint32)( 0U
                | MCU_RGM_CANFD12
                | MCU_RGM_CANFD11
                | MCU_RGM_CANFD10
                | MCU_RGM_CANFD9
                | MCU_RGM_CANFD8
                | MCU_RGM_CANFD7
                | MCU_RGM_CANFD6
                | MCU_RGM_CANFD5
                | MCU_RGM_CANFD4
                | MCU_RGM_CANFD3
                | MCU_RGM_CANFD2
                | MCU_RGM_CANFD1
                | MCU_RGM_EMIOS1
                | MCU_RGM_EMIOS0
                | MCU_RGM_ETPU_C
                | MCU_RGM_ETPU
                | MCU_RGM_GTMINT
        ),

    .RgmGroup5 = (uint32)( 0U
                | MCU_RGM_ADCSD_1
                | MCU_RGM_ADCSD_3
                | MCU_RGM_ADCSD_5
                | MCU_RGM_ADCSD_7
                | MCU_RGM_ADCSD_9
                | MCU_RGM_FCCU
                | MCU_RGM_CRC_1
                | MCU_RGM_PSI5_S_0
        ),

    .RgmGroup6 = (uint32)( 0U
                | MCU_RGM_LINFlexD_2
                | MCU_RGM_LINFlexD_7
                | MCU_RGM_LINFlexD_8
                | MCU_RGM_LINFlexD_9
                | MCU_RGM_LINFlexD_10
                | MCU_RGM_LINFlexD_11
                | MCU_RGM_LINFlexD_12
                | MCU_RGM_LINFlexD_15
        ),

    .RgmGroup7 = (uint32)( 0U
                | MCU_RGM_ADCSAR_1
                | MCU_RGM_ADCSAR_2
                | MCU_RGM_ADCSAR_3
                | MCU_RGM_ADCSAR_5
                | MCU_RGM_ADCSAR_6
                | MCU_RGM_ADCSAR_7
                | MCU_RGM_ADCSAR_8
                | MCU_RGM_ADCSAR_9
                | MCU_RGM_ADCSAR_10
                | MCU_RGM_PSI5_1
                | MCU_RGM_FLEXRAY_1
                | MCU_RGM_SENT_1
                | MCU_RGM_IIC_1
                | MCU_RGM_DSPI_2
                | MCU_RGM_DSPI_3
                | MCU_RGM_DSPI_5
        ),
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_RgmConfigType, MCU_CONST)  Mcu_RgmConfiguration = 
{
    #if (MCU_PERFORM_RESET_API == STD_ON)
    .Mcu_RgmResetType =MCU_DEST_RESET,
    #endif /* (MCU_PERFORM_RESET_API == STD_ON) */
    /* RGM_FRET Register Configuration. */
    .Mcrgm_FuncThresholdReset = (uint8)(8U),
    /* RGM_DRET Register Configuration. */
    .Mcrgm_DesThresholdReset = (uint8)(8U),
    .Mcrgm_DestResetOpt = (uint32)(RGM_PORST_RESET),
    .Mcrgm_DestSafeIsrOpt = (uint32)(RGM_PORST_ALT_EVENT_SAFE),
    .Mcrgm_DestExtPinReset = (uint32)(0x00000000U),
    .Mcrgm_FuncResetOpt = (uint32)(
        (RGM_VOR_FUNC_EVENT_RESET) |
        (RGM_TSR_FUNC_EVENT_SAFE_INT) |
        (RGM_ESR1_EVENT_RESET)
    ),
    .Mcrgm_FuncSafeIsrOpt = (uint32)(
        (RGM_VOR_FUNC_EVENT_SAFE) |
        (RGM_TSR_FUNC_EVENT_SAFE) |
        (RGM_ESR1_EVENT_SAFE)
    ),
    .Mcrgm_FuncExtPinReset = (uint32)(
        (RGM_VOR_FUNC_EXT_RESET_B_DIS) |
        (RGM_TSR_FUNC_EXT_RESET_B_DIS) |
        (RGM_HSM_FUNC_ASSERT_ESR0_DIS) |
        (RGM_FCCU_SOFT_EXT_RESET_B_DIS) |
        (RGM_FCCU_HARD_EXT_RESET_B_DIS) |
        (RGM_SOFT_FUNC_EXT_RESET_B_DIS) |
        (RGM_ESR1_ASSERT_ESR0_DIS)
    ),
    .Mcrgm_FuncPhase1or3Opt = (uint32)(
        (RGM_VOR_FUNC_RESET_PHASE1) |
        (RGM_TSR_FUNC_RESET_PHASE1) |
        (RGM_JTAG_FUNC_RESET_PHASE1) |
        (RGM_SOFT_FUNC_RESET_PHASE1) |
        (RGM_ESR1_RESET_PHASE1) |
        (RGM_ESR0_RESET_PHASE1)
    ),
    .PeriResetConfig = {
            &McuResetSetting_0,
            &McuResetSetting_1,
    }
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"




#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_PmcConfigType, MCU_CONST)  Mcu_PmcConfiguration = 
{
    .Pmc_IerConfig = (uint32)(
        PMC_IER_VD15IE_A_ENA|
        PMC_IER_VD15IE_C_ENA|
        PMC_IER_VD14IE_A_ENA|
        PMC_IER_VD14IE_IM_ENA|
        PMC_IER_VD13IE_IM_ENA|
        PMC_IER_VD12IE_F_ENA|
        PMC_IER_VD10IE_A_ENA|
        PMC_IER_VD10IE_F_ENA|
        PMC_IER_VD9IE_O_ENA|
        PMC_IER_VD9IE_O_H_ENA|
        PMC_IER_VD9IE_IO_5V_H_ENA|
        PMC_IER_VD9IE_IO_5V_ENA|
        PMC_IER_VD9IE_PMC_H_ENA|
        PMC_IER_VD9IE_PMC_ENA|
        PMC_IER_VD8IE_C_ENA|
        PMC_IER_VD8IE_F_ENA|
        PMC_IER_VD7IE_C_ENA|
        PMC_IER_VD4IE_C_ENA|
        PMC_IER_VD3IE_P_ENA|
        PMC_IER_VD3IE_F_ENA),
    .Pmc_VD3ResetEventEn = (uint32)(
        PMC_REE_VD3_HVD3_P_ENA|
        PMC_REE_VD3_LVD3_F_ENA|
        PMC_REE_VD3_LVD3_C_ENA),
    .Pmc_VD4ResetEventEn = (uint32)(
        PMC_REE_VD4_LVD4_C_ENA),
    .Pmc_VD7ResetEventEn = (uint32)(
        PMC_REE_VD7_HVD7_C_ENA),
    .Pmc_VD8ResetEventEn = (uint32)(
        PMC_REE_VD8_LVD8_F_ENA|
        PMC_REE_VD8_HVD8_C_ENA),
    .Pmc_VD9ResetEventEn = (uint32)(
        PMC_REE_VD9_HVD9_O_DIS|
        PMC_REE_VD9_HVD9_IO_5V_DIS|
        PMC_REE_VD9_HVD9_PMC_DIS|
        PMC_REE_VD9_LVD9_O_ENA|
        PMC_REE_VD9_LVD9_IO_5V_ENA|
        PMC_REE_VD9_LVD9_PMC_ENA),
    .Pmc_VD10ResetEventEn = (uint32)(
        PMC_REE_VD10_LVD10_A_ENA|
        PMC_REE_VD10_LVD10_F_ENA),
    .Pmc_VD12ResetEventEn = (uint32)(
        PMC_REE_VD12_HVD12_F_ENA),
    .Pmc_VD13ResetEventEn = (uint32)(
        PMC_REE_VD13_LVD13_IM_ENA),
    .Pmc_VD14ResetEventEn = (uint32)(
        PMC_REE_VD14_LVD14_A_ENA|
        PMC_REE_VD14_HVD14_IM_ENA),
    .Pmc_VD15ResetEventEn = (uint32)(
        PMC_REE_VD15_HVD15_A_ENA|
        PMC_REE_VD15_HVD15_C_ENA),
    .Pmc_VD3ResetEventSel = (uint32)(
        PMC_RES_VD3_HVD3_P_DIS|
        PMC_RES_VD3_LVD3_F_DIS|
        PMC_RES_VD3_LVD3_C_DIS),
    .Pmc_VD4ResetEventSel = (uint32)(
        PMC_RES_VD4_LVD4_C_DIS),
    .Pmc_VD7ResetEventSel = (uint32)(
        PMC_RES_VD7_HVD7_C_DIS),
    .Pmc_VD8ResetEventSel = (uint32)(
        PMC_RES_VD8_LVD8_F_DIS|
        PMC_RES_VD8_HVD8_C_DIS),
    .Pmc_VD9ResetEventSel = (uint32)(
        PMC_RES_VD9_HVD9_O_DIS|
        PMC_RES_VD9_HVD9_IO_5V_DIS|
        PMC_RES_VD9_HVD9_PMC_DIS),
    .Pmc_VD12ResetEventSel = (uint32)(
        PMC_RES_VD12_HVD12_F_DIS),
    .Pmc_VD13ResetEventSel = (uint32)(
        PMC_RES_VD13_LVD13_IM_DIS),
    .Pmc_VD14ResetEventSel = (uint32)(
        PMC_RES_VD14_LVD14_A_DIS|
        PMC_RES_VD14_HVD14_IM_DIS),
    .Pmc_VD15ResetEventSel = (uint32)(
        PMC_RES_VD15_HVD15_A_DIS|
        PMC_RES_VD15_HVD15_C_DIS),
    .Pmc_VD3FccuEventEn = (uint32)(
        PMC_FEE_VD3_FEE3_P_ENA|
        PMC_FEE_VD3_FEE3_F_ENA|
        PMC_FEE_VD3_FEE3_C_ENA),
    .Pmc_VD4FccuEventEn = (uint32)(
        PMC_FEE_VD4_FEE4_C_ENA),
    .Pmc_VD7FccuEventEn = (uint32)(
        PMC_FEE_VD7_FEE7_C_ENA),
    .Pmc_VD8FccuEventEn = (uint32)(
        PMC_FEE_VD8_FEE8_F_ENA|
        PMC_FEE_VD8_FEE8_C_ENA),
    .Pmc_VD9FccuEventEn = (uint32)(
        PMC_FEE_VD9_FEE9_O_ENA|
        PMC_FEE_VD9_FEE9_IO_5V_DIS|
        PMC_FEE_VD9_FEE9_PMC_ENA|
        PMC_FEE_VD9_FEE9_O_H_DIS|
        PMC_FEE_VD9_FEE9_IO_5V_H_ENA|
        PMC_FEE_VD9_FEE9_PMC_ENA),
    .Pmc_VD10FccuEventEn = (uint32)(
        PMC_FEE_VD10_FEE10_A_ENA|
        PMC_FEE_VD10_FEE10_F_ENA),
    .Pmc_VD12FccuEventEn = (uint32)(
        PMC_FEE_VD12_FEE12_F_ENA),
    .Pmc_VD13FccuEventEn = (uint32)(
        PMC_FEE_VD13_FEE13_IM_ENA),
    .Pmc_VD14FccuEventEn = (uint32)(
        PMC_FEE_VD14_FEE14_A_ENA|
        PMC_FEE_VD14_FEE14_IM_ENA),
    .Pmc_VD15FccuEventEn = (uint32)(
        PMC_FEE_VD15_FEE15_A_ENA|
        PMC_FEE_VD15_FEE15_C_ENA),
    .Pmc_VoltageSupply = (uint32)(
        PMC_VSIO_VSIO_IF2_ENA|
        PMC_VSIO_VSIO_IF_ENA|
        PMC_VSIO_VSIO_IJ_ENA|
        PMC_VSIO_VSIO_IM_ENA),
    .Pmc_TempResEventEn = (uint32)(
        PMC_REE_TD_TEMP_3_DIS|
        PMC_REE_TD_TEMP_2_DIS|
        PMC_REE_TD_TEMP_0_DIS),
    .Pmc_TempResEventSel = (uint32)(
        PMC_RES_TD_TEMP_3_DIS|
        PMC_RES_TD_TEMP_2_DIS|
        PMC_RES_TD_TEMP_0_DIS),
    .Pmc_TempDetConfig = (uint32)(
        PMC_CTL_TD_TS3IE_DIS|
        PMC_CTL_TD_TS2IE_DIS|
        PMC_CTL_TD_TS0IE_DIS|
        ((uint32)( (uint32)((0U) << (uint32)8U) & PMC_CTL_TD_TRIM_ADJ_OVER )) |
        ((uint32)( (uint32)((0U) << (uint32)2U) & PMC_CTL_TD_TRIM_ADJ_UNDER )) |
        PMC_CTL_TD_DOUT_ENA|
        PMC_CTL_TD_AOUT_ENA),
    .Pmc_TempFccuEventEn = (uint32)(
        PMC_FEE_TD_FEE_TS3_DIS|
        PMC_FEE_TD_FEE_TS2_DIS|
        PMC_FEE_TD_FEE_TS0_DIS)
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_ClockConfigType, MCU_CONST) Mcu_ClockConfiguration[] = 
{
    {
    .cgmConfig = {
        .sc_dc0 = (Mcu_CgmClkDivType)2,
        .sc_dc1 = (Mcu_CgmClkDivType)5,
        .sc_dc2 = (Mcu_CgmClkDivType)11,
        .sc_dc3 = (Mcu_CgmClkDivType)1,
        .sc_dc4 = (Mcu_CgmClkDivType)11,
        .ac0_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac0_dc0 = (Mcu_CgmClkDivType)4,
        .ac0_dc1_fmt =0,
        .ac0_dc1 = (Mcu_CgmClkDivType)19,
        .ac0_dc2_fmt =0,
        .ac0_dc2 = (Mcu_CgmClkDivType)7,
        .ac0_dc3_fmt =0,
        .ac0_dc3 = (Mcu_CgmClkDivType)3,
        .ac0_dc4 = (Mcu_CgmClkDivType)3,
        .ac1_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac1_dc0 = (Mcu_CgmClkDivType)0,
        .ac2_dc0 = (Mcu_CgmClkDivType)9,
        .ac2_dc1 = (Mcu_CgmClkDivType)3,
        .ac3_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac4_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI1,
        .ac5_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac5_dc0_fmt =CGM_CLOCK_DISABLE4,
        .ac5_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE8,
        .ac5_dc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc10 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc11 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc12 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc13 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc20 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc21 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc22 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc23 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac6_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac6_dc0 = (Mcu_CgmClkDivType)399,
        .ac7_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac7_dc0 = (Mcu_CgmClkDivType)3,
        .ac8_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac8_dc0 = (Mcu_CgmClkDivType)7,
        .ac9_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac9_dc0 = (Mcu_CgmClkDivType)0,
        .ac10_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac10_dc0 = (Mcu_CgmClkDivType)7,
        .ac11_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_PLL0_PHI0,
        .ac11_dc0 = (Mcu_CgmClkDivType)7,
        .ac12_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac12_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc0_fmt =CGM_CLOCK_DISABLE4,
        .ac12_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc1_fmt =CGM_CLOCK_DISABLE4,
        .ac12_dc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc2_fmt =CGM_CLOCK_DISABLE4        },
    .cgmcsConfig = {
        .ircConfig = {
            .Mcu_FircCfg = (uint32)(
                (uint32)(0U << 16U)  /* FIRC Trim */
               |(uint32)(0U<< 23U) /* FIRCOFF_STDBY */
               |(uint32)(0U << 8U) /* FIRC DIV */
            ),
            .Mcu_SircCfg = (uint32)(
                (uint32)(1U) /* SIRC Enable */
               |(uint32)(0U << 8U) /* SIRC DIV */
            )
        },
        .xosc0Config = {
            .freq = (uint32) 20000000,
            .startupDelay = (uint16) 100,
            .bypassOption = (Mcu_XoscBypassType)XOSC_USE_CRYSTAL,
            .Mcu_xoscInterruptEn =FALSE,
            },
        .pll0Config = {
            .predivider = (Mcu_PlldigClkPredivType) 2,
            .mulFactorDiv = (uint8) 40,
            .phi0Divider = (Mcu_PlldigClkoutDivType) 1,
            .phi1Divider = (Mcu_PlldigClkoutDivType) 8
            },
        .pll1Config = { 
            .mulFactorDiv = (uint8) 12,
            .phi0Divider = (Mcu_PlldigClkPredivType) 0,
            .modulation = (uint8)FALSE,
            .modulationType = (Mcu_PlldigModType)DOWN_SPREAD_MODULATION,
            .modulationPeriod = (uint16) 0,
            .incrementStep = (uint16) 0,
            .fracDivider = (uint8)FALSE,
            .fracDividerValue = (uint16) 0
            }
        },
    .Mcu_SRamWSConfig = (uint32)(
        ((uint32)(((uint32)2U<< (uint32)8U) & PRAMC_PRCR1_PRI_MASK32)) |
        (PRAMC_PRCR1_P1_BO_ENA) |
        (PRAMC_PRCR1_P0_BO_ENA) |
        (PRAMC_PRCR1_P1_RB_ENA) |
        (PRAMC_PRCR1_P0_RB_ENA) |
        (PRAMC_PRCR1_FT_ENA)),
    .mode_configuration = {
        .clocksEnabled = {
            .irc0 = (uint8)TRUE,
            .xosc0 = (uint8)TRUE,
            .pll0 = (uint8)TRUE,
            .pll1 = (uint8)TRUE            },
        .sysclk = (Mcu_CgmSysClkSrcType)CGM_SYSTEM_CLOCK_SRC_PLL1_PHI0,
        },
    .PeriConfigPtr = &McuPeripheralConfig_0[0U],
    },
    {
    .cgmConfig = {
        .sc_dc0 = (Mcu_CgmClkDivType)0,
        .sc_dc1 = (Mcu_CgmClkDivType)0,
        .sc_dc2 = (Mcu_CgmClkDivType)0,
        .sc_dc3 = (Mcu_CgmClkDivType)0,
        .sc_dc4 = (Mcu_CgmClkDivType)0,
        .ac0_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .ac0_dc0 = (Mcu_CgmClkDivType)0,
        .ac0_dc1_fmt =CGM_CLOCK_DISABLE4,
        .ac0_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE7,
        .ac0_dc2_fmt =CGM_CLOCK_DISABLE4,
        .ac0_dc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE7,
        .ac0_dc3_fmt =CGM_CLOCK_DISABLE4,
        .ac0_dc3 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE9,
        .ac0_dc4 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE4,
        .ac1_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac1_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE7,
        .ac2_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE6,
        .ac2_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE6,
        .ac3_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .ac4_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac5_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac5_dc0_fmt =CGM_CLOCK_DISABLE4,
        .ac5_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE8,
        .ac5_dc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc10 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc11 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc12 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc13 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc20 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc21 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc22 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac5_cdc23 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE10,
        .ac6_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .ac6_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE9,
        .ac7_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .ac7_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE9,
        .ac8_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac8_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE6,
        .ac9_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .ac9_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE6,
        .ac10_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac10_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE4,
        .ac11_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac11_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE4,
        .ac12_sc = (Mcu_CgmClkSelType)CGM_SYSTEM_CLOCK_SRC_XOSC,
        .ac12_dc0 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc0_fmt =CGM_CLOCK_DISABLE4,
        .ac12_dc1 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc1_fmt =CGM_CLOCK_DISABLE4,
        .ac12_dc2 = (Mcu_CgmClkDivType)CGM_CLOCK_DISABLE13,
        .ac12_dc2_fmt =CGM_CLOCK_DISABLE4        },
    .cgmcsConfig = {
        .ircConfig = {
            .Mcu_FircCfg = (uint32)(
                (uint32)(0U << 16U)  /* FIRC Trim */
               |(uint32)(0U<< 23U) /* FIRCOFF_STDBY */
               |(uint32)(0U << 8U) /* FIRC DIV */
            ),
            .Mcu_SircCfg = (uint32)(
                (uint32)(1U) /* SIRC Enable */
               |(uint32)(0U << 8U) /* SIRC DIV */
            )
        },
        .xosc0Config = {
            .freq = (uint32) 20000000,
            .startupDelay = (uint16) 100,
            .bypassOption = (Mcu_XoscBypassType)XOSC_USE_CRYSTAL,
            .Mcu_xoscInterruptEn =FALSE,
            },
        .pll0Config = {
            .predivider = (Mcu_PlldigClkPredivType) 4,
            .mulFactorDiv = (uint8) 80,
            .phi0Divider = (Mcu_PlldigClkoutDivType) 8,
            .phi1Divider = (Mcu_PlldigClkoutDivType) 5
            },
        .pll1Config = { 
            .mulFactorDiv = (uint8) 24,
            .phi0Divider = (Mcu_PlldigClkPredivType) 4,
            .modulation = (uint8)FALSE,
            .modulationType = (Mcu_PlldigModType)DOWN_SPREAD_MODULATION,
            .modulationPeriod = (uint16) 0,
            .incrementStep = (uint16) 0,
            .fracDivider = (uint8)FALSE,
            .fracDividerValue = (uint16) 0
            }
        },
    .Mcu_SRamWSConfig = (uint32)(
        ((uint32)(((uint32)2U<< (uint32)8U) & PRAMC_PRCR1_PRI_MASK32)) |
        (PRAMC_PRCR1_P1_BO_ENA) |
        (PRAMC_PRCR1_P0_BO_ENA) |
        (PRAMC_PRCR1_P1_RB_ENA) |
        (PRAMC_PRCR1_P0_RB_ENA) |
        (PRAMC_PRCR1_FT_ENA)),
    .mode_configuration = {
        .clocksEnabled = {
            .irc0 = (uint8)TRUE,
            .xosc0 = (uint8)TRUE,
            .pll0 = (uint8)FALSE,
            .pll1 = (uint8)FALSE            },
        .sysclk = (Mcu_CgmSysClkSrcType)CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        },
    .PeriConfigPtr = &McuPeripheralConfig_1[0U],
    },
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_ModeConfigType, MCU_CONST) Mcu_ModeConfiguration[] = 
{
    {
        .Mcu_ModeConfigId = 0,
        .Mcu_ChipMode =me_mc_run0_mode,
        .Mcu_TargetClock =CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .Mcu_IRC_En =TRUE,
        .Mcu_XOSC_En =TRUE,
        .Mcu_PLL0_En =TRUE,
        .Mcu_PLL1_En =TRUE,
        .PeriConfigPtr =NULL_PTR    },
    {
        .Mcu_ModeConfigId = 1,
        .Mcu_ChipMode =me_mc_run0_mode,
        .Mcu_TargetClock =CGM_SYSTEM_CLOCK_SRC_IRCOSC,
        .Mcu_IRC_En =TRUE,
        .Mcu_XOSC_En =FALSE,
        .Mcu_PLL0_En =FALSE,
        .Mcu_PLL1_En =FALSE,
        .PeriConfigPtr =NULL_PTR    },
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_RamConfigType, MCU_CONST) Mcu_RamConfiguration[] = 
{
    {
        /* The ID for Ram Sector configuration. */
        (Mcu_RamSectionType)0U,
        /* RAM section base address: Start of Mcu_RamConfig[0]. */
        (uint8 *)0x40000000U,
        /* RAM section size: Section base address (must be aligned to 4 bytes). */
        (Mcu_RamSizeType)0x00000400U,
        (uint64) ( 
            ((uint64)0x00U << 0U)
            | ((uint64)0x00U << 8U)
            | ((uint64)0x00U << 16U)
            | ((uint64)0x00U << 24U)
            | ((uint64)0x00U << 32U)
            | ((uint64)0x00U << 40U)
            | ((uint64)0x00U << 48U)
            | ((uint64)0x00U << 56U)
        ),
        /* RAM section write size (maximum allowed: 8). */
        (Mcu_RamWriteSizeType)8U
    },
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"



#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
static CONST(Mcu_CtrlConfigType, MCU_CONST) Mcu_CtrlConfiguration = 
{
    .Mcu_BootCore = CORE_ID_Z4_2,
    .Mcu_InitCore = CORE_ID_Z4_2
};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
CONST( Mcu_NotifyConfigType, MCU_CONST) Mcu_NotifyConfiguration = {
    .Mcu_XoscStartupNotification =NULL_PTR,
    .McuFailOfChangeModeNotification = NULL_PTR,
    .Mcu_InvalidConfigNotification_Core =NULL_PTR,
    .Mcu_InvalidConfigNotification_Clock =NULL_PTR,
    .Mcu_InvalidConfigNotification =NULL_PTR,
    .Mcu_InvalidModeNotification =NULL_PTR,
    .Mcu_SafeModeNotification =NULL_PTR,
    .Mcu_ModeCompleteNotification =NULL_PTR,
    .McuVoltageErrorNotification =NULL_PTR,
    .McuTemperatureErrorNotification =NULL_PTR,

};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"
CONST(Mcu_ConfigType, MCU_CONST) McuModuleConfiguration = 
{
    .Mcu_NotifyConfigPtr = &Mcu_NotifyConfiguration,
    .Mcu_CtrlConfigPtr = &Mcu_CtrlConfiguration,
    .Mcu_CoreConfigPtr = &Mcu_CoreConfiguration,
    .Mcu_McMeConfigPtr = &Mcu_McMeConfiguration,
    .Mcu_RgmConfigPtr = &Mcu_RgmConfiguration,
    .Mcu_PmcConfigPtr = &Mcu_PmcConfiguration,
    .NoClockConfig = 2U,
    .Mcu_ClockConfigPtr = &Mcu_ClockConfiguration[0U],
    .NoModeConfig = 2U,
    .Mcu_ModeConfigPtr = &Mcu_ModeConfiguration[0U],
    .NoRamSectionConfig = 1U,
    .Mcu_RamConfigPtr = &Mcu_RamConfiguration[0U]};
#define MCU_STOP_SEC_CONFIG_DATA
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif


