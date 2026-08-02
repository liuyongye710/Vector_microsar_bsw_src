/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : CAN
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Can_LLDriver.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Can MCAL driver.
*
*   @addtogroup Can
*   @{
*/

#ifndef CAN_LLDRIVER_H_
#define CAN_LLDRIVER_H_

#ifdef __cplusplus
extern "C"{
#endif

 /*PRQA S 3472,1534,3630,0779,0654 EOF*/

#include "derivative.h"
#include "status.h"
#include "typedefs.h"
#include "devassert.h"
#include "common.h"
#include "Compiler.h"
#include "Can_Cfg.h"

#define CAN_LLD_H_VENDOR_ID                     176
#define CAN_LLD_H_AR_REL_MAJOR_VER              4
#define CAN_LLD_H_AR_REL_MINOR_VER              4
#define CAN_LLD_H_AR_REL_REV_VER                0
#define CAN_LLD_H_SW_MAJOR_VER                  3
#define CAN_LLD_H_SW_MINOR_VER                  0
#define CAN_LLD_H_SW_PATCH_VER                  0

#if (CAN_CFG_H_VENDOR_ID != CAN_LLD_H_VENDOR_ID)
    #error " NON-MATCHED DATA : CAN_LLD_H_VENDOR_ID "
#endif
#if (CAN_CFG_H_AR_REL_MAJOR_VER != CAN_LLD_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_AR_REL_MAJOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_MINOR_VER != CAN_LLD_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_AR_REL_MINOR_VER "
#endif
#if (CAN_CFG_H_AR_REL_REV_VER != CAN_LLD_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_AR_REL_REV_VER "
#endif
#if (CAN_CFG_H_SW_MAJOR_VER != CAN_LLD_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_SW_MAJOR_VER "
#endif
#if (CAN_CFG_H_SW_MINOR_VER != CAN_LLD_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_SW_MINOR_VER "
#endif
#if (CAN_CFG_H_SW_PATCH_VER != CAN_LLD_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : CAN_LLD_H_SW_PATCH_VER "
#endif

typedef struct M_CAN_tag MCAN_Type;

/* MCAN - Peripheral instance base addresses */
#define MCAN_0_BASE                             (0xFFEE4000u)
#define MCAN_0_P                                ((MCAN_Type *)MCAN_0_BASE)

#define MCAN_1_BASE                             (0xFFEE8000u)
#define MCAN_1_P                                ((MCAN_Type *)MCAN_1_BASE)

#define MCAN_2_BASE                             (0xFFEEC000u)
#define MCAN_2_P                                ((MCAN_Type *)MCAN_2_BASE)

#define MCAN_3_BASE                             (0xFFEF0000u)
#define MCAN_3_P                                ((MCAN_Type *)MCAN_3_BASE)

#define MCAN_4_BASE                             (0xFFEF4000u)
#define MCAN_4_P                                ((MCAN_Type *)MCAN_4_BASE)

#define MCAN_5_BASE                             (0xFFEF8000u)
#define MCAN_5_P                                ((MCAN_Type *)MCAN_5_BASE)

#define MCAN_6_BASE                             (0xFFEFC000u)
#define MCAN_6_P                                ((MCAN_Type *)MCAN_6_BASE)

#define MCAN_7_BASE                             (0xFFF00000u)
#define MCAN_7_P                                ((MCAN_Type *)MCAN_7_BASE)

#define MCAN_8_BASE                             (0xFFEBC000u)
#define MCAN_8_P                                ((MCAN_Type *)MCAN_8_BASE)

#define MCAN_9_BASE                             (0xFFEC0000u)
#define MCAN_9_P                                ((MCAN_Type *)MCAN_9_BASE)

#define MCAN_10_BASE                            (0xFFEC4000u)
#define MCAN_10_P                               ((MCAN_Type *)MCAN_10_BASE)

#define MCAN_11_BASE                            (0xFFEC8000u)
#define MCAN_11_P                               ((MCAN_Type *)MCAN_11_BASE)

#define MCAN_BASE_ADDRS                         { MCAN_0_BASE, MCAN_1_BASE, MCAN_2_BASE, MCAN_3_BASE, MCAN_4_BASE, MCAN_5_BASE, MCAN_6_BASE, MCAN_7_BASE, MCAN_8_BASE, MCAN_9_BASE, MCAN_10_BASE, MCAN_11_BASE}
#define MCAN_BASE_PTRS                          { MCAN_0_P, MCAN_1_P, MCAN_2_P, MCAN_3_P, MCAN_4_P, MCAN_5_P, MCAN_6_P, MCAN_7_P, MCAN_8_P, MCAN_9_P, MCAN_10_P, MCAN_11_P}

/* MCAN module features */
#define MCAN_INSTANCE_COUNT                     (12u)

#define CAN_FD_MAX_NO_OF_DTB_PER_FRAME 64

#define RX_MESSAGE_LIST_ENTRIES     64U

#define TX_EVENT_FIFO_LIST_ENTRIES  32U

#define FEATURE_MCAN_MSG_RAMA_START_ADR  0xFFED4000U

#define FEATURE_MCAN_MSG_RAMB_START_ADR  0xFFF04000U

#define FEATURE_MCAN_MSG_RAMC_START_ADR  0xFFECC000U

#define FEATURE_MCAN_RX_MB_NUM              (64U)

#define FEATURE_MCAN_TX_MB_NUM              (32U)

#define FEATURE_MCAN_STD_ID_NUM             (128U)

#define FEATURE_MCAN_EXT_ID_NUM             (64U)

#define FEATURE_MCAN_RAM_MESSAGES_WRD       (5120UL)

#define FEATURE_MCAN_NO_RXFIFO              (2U)

#define INTERRUPT_ALL_SIGNALS       0x3FFFFFFFUL

#define TSCC_TCP_MIN_VALUE  1
#define TSCC_TCP_MAX_VALUE 16

#define LEC_NO_OF_ERROR_CODES  8

#define MCAN_STORE_RX_FIFO0                     ((uint8)0xFCU)
#define MCAN_STORE_RX_FIFO1                     ((uint8)0xFDU)
#define MCAN_FD_ID_DESCRIPTOR                   (0x40000000U)

/* ILE defines */
#define ILE_DISABLE_INTERRUPT_LINES     0x0U
#define ILE_ENABLE_INTERRUPT_LINE_0     0x1U
#define ILE_ENABLE_INTERRUPT_LINE_1     0x2U

#define MCAN_RAMA    ((RAM_MB *)FEATURE_MCAN_MSG_RAMA_START_ADR)
#define MCAN_RAMB    ((RAM_MB *)FEATURE_MCAN_MSG_RAMB_START_ADR)
#define MCAN_RAMC    ((RAM_MB *)FEATURE_MCAN_MSG_RAMC_START_ADR)

/* ----------------------------------------------------------------------------
   -- M_CAN Register Masks
   ---------------------------------------------------------------------------- */

/* CREL Bit Fields */
#define MCAN_CREL_DAY_MASK                      0xFFu
#define MCAN_CREL_DAY_SHIFT                     0u
#define MCAN_CREL_DAY_WIDTH                     8u
#define MCAN_CREL_DAY(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_DAY_SHIFT)) \
                                                  &MCAN_CREL_DAY_MASK)
#define MCAN_CREL_MON_MASK                      0xFF00u
#define MCAN_CREL_MON_SHIFT                     8u
#define MCAN_CREL_MON_WIDTH                     8u
#define MCAN_CREL_MON(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_MON_SHIFT)) \
                                                  &MCAN_CREL_MON_MASK)
#define MCAN_CREL_YEAR_MASK                     0xF0000u
#define MCAN_CREL_YEAR_SHIFT                    16u
#define MCAN_CREL_YEAR_WIDTH                    4u
#define MCAN_CREL_YEAR(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_YEAR_SHIFT)) \
                                                  &MCAN_CREL_YEAR_MASK)
#define MCAN_CREL_SUBSTEP_MASK                  0xF00000u
#define MCAN_CREL_SUBSTEP_SHIFT                 20u
#define MCAN_CREL_SUBSTEP_WIDTH                 4u
#define MCAN_CREL_SUBSTEP(x)                    (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_SUBSTEP_SHIFT)) \
                                                  &MCAN_CREL_SUBSTEP_MASK)
#define MCAN_CREL_STEP_MASK                     0xF000000u
#define MCAN_CREL_STEP_SHIFT                    24u
#define MCAN_CREL_STEP_WIDTH                    4u
#define MCAN_CREL_STEP(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_STEP_SHIFT)) \
                                                  &MCAN_CREL_STEP_MASK)
#define MCAN_CREL_REL_MASK                      0xF0000000u
#define MCAN_CREL_REL_SHIFT                     28u
#define MCAN_CREL_REL_WIDTH                     4u
#define MCAN_CREL_REL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CREL_REL_SHIFT)) \
                                                  &MCAN_CREL_REL_MASK)
/* ENDN Bit Fields */
#define MCAN_ENDN_ETV_MASK                      0xFFFFFFFFu
#define MCAN_ENDN_ETV_SHIFT                     0u
#define MCAN_ENDN_ETV_WIDTH                     32u
#define MCAN_ENDN_ETV(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ENDN_ETV_SHIFT)) \
                                                  &MCAN_ENDN_ETV_MASK)
/* DBTP Bit Fields */
#define MCAN_DBTP_DSJW_MASK                     0xFu
#define MCAN_DBTP_DSJW_SHIFT                    0u
#define MCAN_DBTP_DSJW_WIDTH                    4u
#define MCAN_DBTP_DSJW(x)                       (((uint32)(x)) \
                                                  &MCAN_DBTP_DSJW_MASK)
#define MCAN_DBTP_DTSEG2_MASK                   0xF0u
#define MCAN_DBTP_DTSEG2_SHIFT                  4u
#define MCAN_DBTP_DTSEG2_WIDTH                  4u
#define MCAN_DBTP_DTSEG2(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_DBTP_DTSEG2_SHIFT)) \
                                                  &MCAN_DBTP_DTSEG2_MASK)
#define MCAN_DBTP_DTSEG1_MASK                   0x1F00u
#define MCAN_DBTP_DTSEG1_SHIFT                  8u
#define MCAN_DBTP_DTSEG1_WIDTH                  5u
#define MCAN_DBTP_DTSEG1(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_DBTP_DTSEG1_SHIFT)) \
                                                  &MCAN_DBTP_DTSEG1_MASK)
#define MCAN_DBTP_DBRP_MASK                     0x1F0000u
#define MCAN_DBTP_DBRP_SHIFT                    16u
#define MCAN_DBTP_DBRP_WIDTH                    5u
#define MCAN_DBTP_DBRP(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_DBTP_DBRP_SHIFT)) \
                                                  &MCAN_DBTP_DBRP_MASK)
#define MCAN_DBTP_TDC_MASK                      0x800000u
#define MCAN_DBTP_TDC_SHIFT                     23u
#define MCAN_DBTP_TDC_WIDTH                     1u
#define MCAN_DBTP_TDC(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_DBTP_TDC_SHIFT)) \
                                                  &MCAN_DBTP_TDC_MASK)
/* TEST Bit Fields */
#define MCAN_TEST_LBCK_MASK                     0x10u
#define MCAN_TEST_LBCK_SHIFT                    4u
#define MCAN_TEST_LBCK_WIDTH                    1u
#define MCAN_TEST_LBCK(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_LBCK_SHIFT)) \
                                                  &MCAN_TEST_LBCK_MASK)
#define MCAN_TEST_TX_MASK                       0x60u
#define MCAN_TEST_TX_SHIFT                      5u
#define MCAN_TEST_TX_WIDTH                      2u
#define MCAN_TEST_TX(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_TX_SHIFT)) \
                                                  &MCAN_TEST_TX_MASK)
#define MCAN_TEST_RX_MASK                       0x80u
#define MCAN_TEST_RX_SHIFT                      7u
#define MCAN_TEST_RX_WIDTH                      1u
#define MCAN_TEST_RX(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_RX_SHIFT)) \
                                                  &MCAN_TEST_RX_MASK)
#define MCAN_TEST_TXBNP_MASK                    0x1F00u
#define MCAN_TEST_TXBNP_SHIFT                   8u
#define MCAN_TEST_TXBNP_WIDTH                   5u
#define MCAN_TEST_TXBNP(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_TXBNP_SHIFT)) \
                                                  &MCAN_TEST_TXBNP_MASK)
#define MCAN_TEST_PVAL_MASK                     0x2000u
#define MCAN_TEST_PVAL_SHIFT                    13u
#define MCAN_TEST_PVAL_WIDTH                    1u
#define MCAN_TEST_PVAL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_PVAL_SHIFT)) \
                                                  &MCAN_TEST_PVAL_MASK)
#define MCAN_TEST_TXBNS_MASK                    0x1F0000u
#define MCAN_TEST_TXBNS_SHIFT                   16u
#define MCAN_TEST_TXBNS_WIDTH                   5u
#define MCAN_TEST_TXBNS(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_TXBNS_SHIFT)) \
                                                  &MCAN_TEST_TXBNS_MASK)
#define MCAN_TEST_SVAL_MASK                     0x200000u
#define MCAN_TEST_SVAL_SHIFT                    21u
#define MCAN_TEST_SVAL_WIDTH                    1u
#define MCAN_TEST_SVAL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TEST_SVAL_SHIFT)) \
                                                  &MCAN_TEST_SVAL_MASK)
/* RWD Bit Fields */
#define MCAN_RWD_WDC_MASK                       0xFFu
#define MCAN_RWD_WDC_SHIFT                      0u
#define MCAN_RWD_WDC_WIDTH                      8u
#define MCAN_RWD_WDC(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RWD_WDC_SHIFT)) \
                                                  &MCAN_RWD_WDC_MASK)
#define MCAN_RWD_WDV_MASK                       0xFF00u
#define MCAN_RWD_WDV_SHIFT                      8u
#define MCAN_RWD_WDV_WIDTH                      8u
#define MCAN_RWD_WDV(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RWD_WDV_SHIFT)) \
                                                  &MCAN_RWD_WDV_MASK)
/* CCCR Bit Fields */
#define MCAN_CCCR_INIT_MASK                     (0x1u)
#define MCAN_CCCR_INIT_SHIFT                    (0u)
#define MCAN_CCCR_INIT_WIDTH                    1u
#define MCAN_CCCR_INIT(x)                       (uint32)((x \
                                                  <<MCAN_CCCR_INIT_SHIFT) \
                                                  &MCAN_CCCR_INIT_MASK)
#define MCAN_CCCR_CCE_MASK                      0x2u
#define MCAN_CCCR_CCE_SHIFT                     1u
#define MCAN_CCCR_CCE_WIDTH                     1u
#define MCAN_CCCR_CCE(x)                        (uint32)((x \
                                                  <<MCAN_CCCR_CCE_SHIFT) \
                                                  &MCAN_CCCR_CCE_MASK)
#define MCAN_CCCR_ASM_MASK                      0x4u
#define MCAN_CCCR_ASM_SHIFT                     2u
#define MCAN_CCCR_ASM_WIDTH                     1u
#define MCAN_CCCR_ASM(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_ASM_SHIFT)) \
                                                  &MCAN_CCCR_ASM_MASK)
#define MCAN_CCCR_CSA_MASK                      0x8u
#define MCAN_CCCR_CSA_SHIFT                     3u
#define MCAN_CCCR_CSA_WIDTH                     1u
#define MCAN_CCCR_CSA(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_CSA_SHIFT)) \
                                                  &MCAN_CCCR_CSA_MASK)
#define MCAN_CCCR_CSR_MASK                      0x10u
#define MCAN_CCCR_CSR_SHIFT                     4u
#define MCAN_CCCR_CSR_WIDTH                     1u
#define MCAN_CCCR_CSR(x)                        (uint32)((x \
                                                  <<MCAN_CCCR_CSR_SHIFT) \
                                                  &MCAN_CCCR_CSR_MASK)
#define MCAN_CCCR_MON_MASK                      0x20u
#define MCAN_CCCR_MON_SHIFT                     5u
#define MCAN_CCCR_MON_WIDTH                     1u
#define MCAN_CCCR_MON(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_MON_SHIFT)) \
                                                  &MCAN_CCCR_MON_MASK)
#define MCAN_CCCR_DAR_MASK                      0x40u
#define MCAN_CCCR_DAR_SHIFT                     6u
#define MCAN_CCCR_DAR_WIDTH                     1u
#define MCAN_CCCR_DAR(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_DAR_SHIFT)) \
                                                  &MCAN_CCCR_DAR_MASK)
#define MCAN_CCCR_TEST_MASK                     0x80u
#define MCAN_CCCR_TEST_SHIFT                    7u
#define MCAN_CCCR_TEST_WIDTH                    1u
#define MCAN_CCCR_TEST(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_TEST_SHIFT)) \
                                                  &MCAN_CCCR_TEST_MASK)
#define MCAN_CCCR_FDOE_MASK                     0x100u
#define MCAN_CCCR_FDOE_SHIFT                    8u
#define MCAN_CCCR_FDOE_WIDTH                    1u
#define MCAN_CCCR_FDOE(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_FDOE_SHIFT)) \
                                                  &MCAN_CCCR_FDOE_MASK)
#define MCAN_CCCR_BRSE_MASK                     0x200u
#define MCAN_CCCR_BRSE_SHIFT                    9u
#define MCAN_CCCR_BRSE_WIDTH                    1u
#define MCAN_CCCR_BRSE(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_BRSE_SHIFT)) \
                                                  &MCAN_CCCR_BRSE_MASK)
#define MCAN_CCCR_UTSU_MASK                     0x400u
#define MCAN_CCCR_UTSU_SHIFT                    10u
#define MCAN_CCCR_UTSU_WIDTH                    1u
#define MCAN_CCCR_UTSU(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_UTSU_SHIFT)) \
                                                  &MCAN_CCCR_UTSU_MASK)
#define MCAN_CCCR_WMM_MASK                      0x800u
#define MCAN_CCCR_WMM_SHIFT                     11u
#define MCAN_CCCR_WMM_WIDTH                     1u
#define MCAN_CCCR_WMM(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_UTSU_SHIFT)) \
                                                  &MCAN_CCCR_UTSU_MASK)
#define MCAN_CCCR_PHDX_MASK                     0x1000u
#define MCAN_CCCR_PHDX_SHIFT                    12u
#define MCAN_CCCR_PHDX_WIDTH                    1u
#define MCAN_CCCR_PHDX(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_PHDX_SHIFT)) \
                                                  &MCAN_CCCR_PHDX_MASK)
#define MCAN_CCCR_EFBI_MASK                     0x2000u
#define MCAN_CCCR_EFBI_SHIFT                    13u
#define MCAN_CCCR_EFBI_WIDTH                    1u
#define MCAN_CCCR_EFBI(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_EFBI_SHIFT)) \
                                                  &MCAN_CCCR_EFBI_MASK)
#define MCAN_CCCR_TXP_MASK                      0x4000u
#define MCAN_CCCR_TXP_SHIFT                     14u
#define MCAN_CCCR_TXP_WIDTH                     1u
#define MCAN_CCCR_TXP(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_TXP_SHIFT)) \
                                                  &MCAN_CCCR_TXP_MASK)
#define MCAN_CCCR_NISO_MASK                     0x8000u
#define MCAN_CCCR_NISO_SHIFT                    15u
#define MCAN_CCCR_NISO_WIDTH                    1u
#define MCAN_CCCR_NISO(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_CCCR_NISO_SHIFT)) \
                                                  &MCAN_CCCR_NISO_MASK)
/* NBTP Bit Fields */
#define MCAN_NBTP_NTSEG2_MASK                   0x3Fu
#define MCAN_NBTP_NTSEG2_SHIFT                  0u
#define MCAN_NBTP_NTSEG2_WIDTH                  7u
#define MCAN_NBTP_NTSEG2(x)                     (((uint32)(x)) \
                                                  &MCAN_NBTP_NTSEG2_MASK)
#define MCAN_NBTP_NTSEG1_MASK                   0xFF00u
#define MCAN_NBTP_NTSEG1_SHIFT                  8u
#define MCAN_NBTP_NTSEG1_WIDTH                  8u
#define MCAN_NBTP_NTSEG1(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_NBTP_NTSEG1_SHIFT)) \
                                                  &MCAN_NBTP_NTSEG1_MASK)
#define MCAN_NBTP_NBRP_MASK                     0x1FF0000u
#define MCAN_NBTP_NBRP_SHIFT                    16u
#define MCAN_NBTP_NBRP_WIDTH                    9u
#define MCAN_NBTP_NBRP(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_NBTP_NBRP_SHIFT)) \
                                                  &MCAN_NBTP_NBRP_MASK)
#define MCAN_NBTP_NSJW_MASK                     0xFE000000u
#define MCAN_NBTP_NSJW_SHIFT                    25u
#define MCAN_NBTP_NSJW_WIDTH                    7u
#define MCAN_NBTP_NSJW(x)                       ((uint32)(((uint32)(x)) \
                                                  <<MCAN_NBTP_NSJW_SHIFT))
/* TSCC Bit Fields */
#define MCAN_TSCC_TSS_MASK                      0x3u
#define MCAN_TSCC_TSS_SHIFT                     0u
#define MCAN_TSCC_TSS_WIDTH                     2u
#define MCAN_TSCC_TSS(x)                        (((uint32)(x)) \
                                                  &MCAN_TSCC_TSS_MASK)
#define MCAN_TSCC_TCP_MASK                      0xF0000u
#define MCAN_TSCC_TCP_SHIFT                     16u
#define MCAN_TSCC_TCP_WIDTH                     4u
#define MCAN_TSCC_TCP(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TSCC_TCP_SHIFT)) \
                                                  &MCAN_TSCC_TCP_MASK)
/* TSCV Bit Fields */
#define MCAN_TSCV_TSC_MASK                      0xFFFFu
#define MCAN_TSCV_TSC_SHIFT                     0u
#define MCAN_TSCV_TSC_WIDTH                     16u
#define MCAN_TSCV_TSC(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TSCV_TSC_SHIFT)) \
                                                  &MCAN_TSCV_TSC_MASK)
/* TOCC Bit Fields */
#define MCAN_TOCC_ETOC_MASK                     0x1u
#define MCAN_TOCC_ETOC_SHIFT                    0u
#define MCAN_TOCC_ETOC_WIDTH                    1u
#define MCAN_TOCC_ETOC(x)                       (uint32)((x \
                                                  <<MCAN_TOCC_ETOC_SHIFT) \
                                                  &MCAN_TOCC_ETOC_MASK)
#define MCAN_TOCC_TOS_MASK                      0x6u
#define MCAN_TOCC_TOS_SHIFT                     1u
#define MCAN_TOCC_TOS_WIDTH                     2u
#define MCAN_TOCC_TOS(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TOCC_TOS_SHIFT)) \
                                                  &MCAN_TOCC_TOS_MASK)
#define MCAN_TOCC_TOP_MASK                      0xFFFF0000u
#define MCAN_TOCC_TOP_SHIFT                     16u
#define MCAN_TOCC_TOP_WIDTH                     16u
#define MCAN_TOCC_TOP(x)                        ((uint32)(((uint32)(x)) \
                                                  <<MCAN_TOCC_TOP_SHIFT))
/* TOCV Bit Fields */
#define MCAN_TOCV_TOC_MASK                      0xFFFFu
#define MCAN_TOCV_TOC_SHIFT                     0u
#define MCAN_TOCV_TOC_WIDTH                     16u
#define MCAN_TOCV_TOC(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TOCV_TOC_SHIFT)) \
                                                  &MCAN_TOCV_TOC_MASK)
/* ECR Bit Fields */
#define MCAN_ECR_TEC_MASK                       0xFFu
#define MCAN_ECR_TEC_SHIFT                      0u
#define MCAN_ECR_TEC_WIDTH                      8u
#define MCAN_ECR_TEC(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ECR_TEC_SHIFT)) \
                                                  &MCAN_ECR_TEC_MASK)
#define MCAN_ECR_REC_MASK                       0x7F00u
#define MCAN_ECR_REC_SHIFT                      8u
#define MCAN_ECR_REC_WIDTH                      7u
#define MCAN_ECR_REC(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ECR_REC_SHIFT)) \
                                                  &MCAN_ECR_REC_MASK)
#define MCAN_ECR_RP_MASK                        0x8000u
#define MCAN_ECR_RP_SHIFT                       15u
#define MCAN_ECR_RP_WIDTH                       1u
#define MCAN_ECR_RP(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ECR_RP_SHIFT)) \
                                                  &MCAN_ECR_RP_MASK)
#define MCAN_ECR_CEL_MASK                       0xFF0000u
#define MCAN_ECR_CEL_SHIFT                      16u
#define MCAN_ECR_CEL_WIDTH                      8u
#define MCAN_ECR_CEL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ECR_CEL_SHIFT)) \
                                                  &MCAN_ECR_CEL_MASK)
/* PSR Bit Fields */
#define MCAN_PSR_LEC_MASK                       0x7u
#define MCAN_PSR_LEC_SHIFT                      0u
#define MCAN_PSR_LEC_WIDTH                      3u
#define MCAN_PSR_LEC(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_LEC_SHIFT)) \
                                                  &MCAN_PSR_LEC_MASK)
#define MCAN_PSR_ACT_MASK                       0x18u
#define MCAN_PSR_ACT_SHIFT                      3u
#define MCAN_PSR_ACT_WIDTH                      2u
#define MCAN_PSR_ACT(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_ACT_SHIFT)) \
                                                  &MCAN_PSR_ACT_MASK)
#define MCAN_PSR_EP_MASK                        0x20u
#define MCAN_PSR_EP_SHIFT                       5u
#define MCAN_PSR_EP_WIDTH                       1u
#define MCAN_PSR_EP(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_EP_SHIFT)) \
                                                  &MCAN_PSR_EP_MASK)
#define MCAN_PSR_EW_MASK                        0x40u
#define MCAN_PSR_EW_SHIFT                       6u
#define MCAN_PSR_EW_WIDTH                       1u
#define MCAN_PSR_EW(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_EW_SHIFT)) \
                                                  &MCAN_PSR_EW_MASK)
#define MCAN_PSR_BO_MASK                        0x80u
#define MCAN_PSR_BO_SHIFT                       7u
#define MCAN_PSR_BO_WIDTH                       1u
#define MCAN_PSR_BO(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_BO_SHIFT)) \
                                                  &MCAN_PSR_BO_MASK)
#define MCAN_PSR_DLEC_MASK                      0x700u
#define MCAN_PSR_DLEC_SHIFT                     8u
#define MCAN_PSR_DLEC_WIDTH                     3u
#define MCAN_PSR_DLEC(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_DLEC_SHIFT)) \
                                                  &MCAN_PSR_DLEC_MASK)
#define MCAN_PSR_RESI_MASK                      0x800u
#define MCAN_PSR_RESI_SHIFT                     11u
#define MCAN_PSR_RESI_WIDTH                     1u
#define MCAN_PSR_RESI(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_RESI_SHIFT)) \
                                                  &MCAN_PSR_RESI_MASK)
#define MCAN_PSR_RBRS_MASK                      0x1000u
#define MCAN_PSR_RBRS_SHIFT                     12u
#define MCAN_PSR_RBRS_WIDTH                     1u
#define MCAN_PSR_RBRS(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_RBRS_SHIFT)) \
                                                  &MCAN_PSR_RBRS_MASK)
#define MCAN_PSR_RFDF_MASK                      0x2000u
#define MCAN_PSR_RFDF_SHIFT                     13u
#define MCAN_PSR_RFDF_WIDTH                     1u
#define MCAN_PSR_RFDF(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_RFDF_SHIFT)) \
                                                  &MCAN_PSR_RFDF_MASK)
#define MCAN_PSR_PXE_MASK                       0x4000u
#define MCAN_PSR_PXE_SHIFT                      14u
#define MCAN_PSR_PXE_WIDTH                      1u
#define MCAN_PSR_PXE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_PXE_SHIFT)) \
                                                  &MCAN_PSR_PXE_MASK)
#define MCAN_PSR_TDCV_MASK                      0x7F0000u
#define MCAN_PSR_TDCV_SHIFT                     16u
#define MCAN_PSR_TDCV_WIDTH                     7u
#define MCAN_PSR_TDCV(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_PSR_TDCV_SHIFT)) \
                                                  &MCAN_PSR_TDCV_MASK)
/* TDCR Bit Fields */
#define MCAN_TDCR_TDCF_MASK                     0x7Fu
#define MCAN_TDCR_TDCF_SHIFT                    0u
#define MCAN_TDCR_TDCF_WIDTH                    7u
#define MCAN_TDCR_TDCF(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TDCR_TDCF_SHIFT)) \
                                                  &MCAN_TDCR_TDCF_MASK)
#define MCAN_TDCR_TDCO_MASK                     0x7F00u
#define MCAN_TDCR_TDCO_SHIFT                    8u
#define MCAN_TDCR_TDCO_WIDTH                    7u
#define MCAN_TDCR_TDCO(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TDCR_TDCO_SHIFT)) \
                                                  &MCAN_TDCR_TDCO_MASK)
/* IR Bit Fields */
#define MCAN_IR_RF0N_MASK                       0x1u
#define MCAN_IR_RF0N_SHIFT                      0u
#define MCAN_IR_RF0N_WIDTH                      1u
#define MCAN_IR_RF0N(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF0N_SHIFT)) \
                                                  &MCAN_IR_RF0N_MASK)
#define MCAN_IR_RF0W_MASK                       0x2u
#define MCAN_IR_RF0W_SHIFT                      1u
#define MCAN_IR_RF0W_WIDTH                      1u
#define MCAN_IR_RF0W(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF0W_SHIFT)) \
                                                  &MCAN_IR_RF0W_MASK)
#define MCAN_IR_RF0F_MASK                       0x4u
#define MCAN_IR_RF0F_SHIFT                      2u
#define MCAN_IR_RF0F_WIDTH                      1u
#define MCAN_IR_RF0F(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF0F_SHIFT)) \
                                                  &MCAN_IR_RF0F_MASK)
#define MCAN_IR_RF0L_MASK                       0x8u
#define MCAN_IR_RF0L_SHIFT                      3u
#define MCAN_IR_RF0L_WIDTH                      1u
#define MCAN_IR_RF0L(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF0L_SHIFT)) \
                                                  &MCAN_IR_RF0L_MASK)
#define MCAN_IR_RF1N_MASK                       0x10u
#define MCAN_IR_RF1N_SHIFT                      4u
#define MCAN_IR_RF1N_WIDTH                      1u
#define MCAN_IR_RF1N(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF1N_SHIFT)) \
                                                  &MCAN_IR_RF1N_MASK)
#define MCAN_IR_RF1W_MASK                       0x20u
#define MCAN_IR_RF1W_SHIFT                      5u
#define MCAN_IR_RF1W_WIDTH                      1u
#define MCAN_IR_RF1W(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF1W_SHIFT)) \
                                                  &MCAN_IR_RF1W_MASK)
#define MCAN_IR_RF1F_MASK                       0x40u
#define MCAN_IR_RF1F_SHIFT                      6u
#define MCAN_IR_RF1F_WIDTH                      1u
#define MCAN_IR_RF1F(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF1F_SHIFT)) \
                                                  &MCAN_IR_RF1F_MASK)
#define MCAN_IR_RF1L_MASK                       0x80u
#define MCAN_IR_RF1L_SHIFT                      7u
#define MCAN_IR_RF1L_WIDTH                      1u
#define MCAN_IR_RF1L(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_RF1L_SHIFT)) \
                                                  &MCAN_IR_RF1L_MASK)
#define MCAN_IR_HPM_MASK                        0x100u
#define MCAN_IR_HPM_SHIFT                       8u
#define MCAN_IR_HPM_WIDTH                       1u
#define MCAN_IR_HPM(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_HPM_SHIFT)) \
                                                  &MCAN_IR_HPM_MASK)
#define MCAN_IR_TC_MASK                         0x200u
#define MCAN_IR_TC_SHIFT                        9u
#define MCAN_IR_TC_WIDTH                        1u
#define MCAN_IR_TC(x)                           (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TC_SHIFT)) \
                                                  &MCAN_IR_TC_MASK)
#define MCAN_IR_TCF_MASK                        0x400u
#define MCAN_IR_TCF_SHIFT                       10u
#define MCAN_IR_TCF_WIDTH                       1u
#define MCAN_IR_TCF(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TCF_SHIFT)) \
                                                  &MCAN_IR_TCF_MASK)
#define MCAN_IR_TFE_MASK                        0x800u
#define MCAN_IR_TFE_SHIFT                       11u
#define MCAN_IR_TFE_WIDTH                       1u
#define MCAN_IR_TFE(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TFE_SHIFT)) \
                                                  &MCAN_IR_TFE_MASK)
#define MCAN_IR_TEFN_MASK                       0x1000u
#define MCAN_IR_TEFN_SHIFT                      12u
#define MCAN_IR_TEFN_WIDTH                      1u
#define MCAN_IR_TEFN(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TEFN_SHIFT)) \
                                                  &MCAN_IR_TEFN_MASK)
#define MCAN_IR_TEFW_MASK                       0x2000u
#define MCAN_IR_TEFW_SHIFT                      13u
#define MCAN_IR_TEFW_WIDTH                      1u
#define MCAN_IR_TEFW(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TEFW_SHIFT)) \
                                                  &MCAN_IR_TEFW_MASK)
#define MCAN_IR_TEFF_MASK                       0x4000u
#define MCAN_IR_TEFF_SHIFT                      14u
#define MCAN_IR_TEFF_WIDTH                      1u
#define MCAN_IR_TEFF(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TEFF_SHIFT)) \
                                                  &MCAN_IR_TEFF_MASK)
#define MCAN_IR_TEFL_MASK                       0x8000u
#define MCAN_IR_TEFL_SHIFT                      15u
#define MCAN_IR_TEFL_WIDTH                      1u
#define MCAN_IR_TEFL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TEFL_SHIFT)) \
                                                  &MCAN_IR_TEFL_MASK)
#define MCAN_IR_TSW_MASK                        0x10000u
#define MCAN_IR_TSW_SHIFT                       16u
#define MCAN_IR_TSW_WIDTH                       1u
#define MCAN_IR_TSW(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TSW_SHIFT)) \
                                                  &MCAN_IR_TSW_MASK)
#define MCAN_IR_MRAF_MASK                       0x20000u
#define MCAN_IR_MRAF_SHIFT                      17u
#define MCAN_IR_MRAF_WIDTH                      1u
#define MCAN_IR_MRAF(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_MRAF_SHIFT)) \
                                                  &MCAN_IR_MRAF_MASK)
#define MCAN_IR_TOO_MASK                        0x40000u
#define MCAN_IR_TOO_SHIFT                       18u
#define MCAN_IR_TOO_WIDTH                       1u
#define MCAN_IR_TOO(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_TOO_SHIFT)) \
                                                  &MCAN_IR_TOO_MASK)
#define MCAN_IR_DRX_MASK                        0x80000u
#define MCAN_IR_DRX_SHIFT                       19u
#define MCAN_IR_DRX_WIDTH                       1u
#define MCAN_IR_DRX(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_DRX_SHIFT)) \
                                                  &MCAN_IR_DRX_MASK)
#define MCAN_IR_BEC_MASK                        0x100000u
#define MCAN_IR_BEC_SHIFT                       20u
#define MCAN_IR_BEC_WIDTH                       1u
#define MCAN_IR_BEC(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_BEC_SHIFT)) \
                                                  &MCAN_IR_BEC_MASK)
#define MCAN_IR_BEU_MASK                        0x200000u
#define MCAN_IR_BEU_SHIFT                       21u
#define MCAN_IR_BEU_WIDTH                       1u
#define MCAN_IR_BEU(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_BEU_SHIFT)) \
                                                  &MCAN_IR_BEU_MASK)
#define MCAN_IR_ELO_MASK                        0x400000u
#define MCAN_IR_ELO_SHIFT                       22u
#define MCAN_IR_ELO_WIDTH                       1u
#define MCAN_IR_ELO(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_ELO_SHIFT)) \
                                                  &MCAN_IR_ELO_MASK)
#define MCAN_IR_EP_MASK                         0x800000u
#define MCAN_IR_EP_SHIFT                        23u
#define MCAN_IR_EP_WIDTH                        1u
#define MCAN_IR_EP(x)                           (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_EP_SHIFT)) \
                                                  &MCAN_IR_EP_MASK)
#define MCAN_IR_EW_MASK                         0x1000000u
#define MCAN_IR_EW_SHIFT                        24u
#define MCAN_IR_EW_WIDTH                        1u
#define MCAN_IR_EW(x)                           (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_EW_SHIFT)) \
                                                  &MCAN_IR_EW_MASK)
#define MCAN_IR_BO_MASK                         0x2000000u
#define MCAN_IR_BO_SHIFT                        25u
#define MCAN_IR_BO_WIDTH                        1u
#define MCAN_IR_BO(x)                           (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_BO_SHIFT)) \
                                                  &MCAN_IR_BO_MASK)
#define MCAN_IR_WDI_MASK                        0x4000000u
#define MCAN_IR_WDI_SHIFT                       26u
#define MCAN_IR_WDI_WIDTH                       1u
#define MCAN_IR_WDI(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_WDI_SHIFT)) \
                                                  &MCAN_IR_WDI_MASK)
#define MCAN_IR_PEA_MASK                        0x8000000u
#define MCAN_IR_PEA_SHIFT                       27u
#define MCAN_IR_PEA_WIDTH                       1u
#define MCAN_IR_PEA(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_PEA_SHIFT)) \
                                                  &MCAN_IR_PEA_MASK)
#define MCAN_IR_PED_MASK                        0x10000000u
#define MCAN_IR_PED_SHIFT                       28u
#define MCAN_IR_PED_WIDTH                       1u
#define MCAN_IR_PED(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_PED_SHIFT)) \
                                                  &MCAN_IR_PED_MASK)
#define MCAN_IR_ARA_MASK                        0x20000000u
#define MCAN_IR_ARA_SHIFT                       29u
#define MCAN_IR_ARA_WIDTH                       1u
#define MCAN_IR_ARA(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IR_ARA_SHIFT)) \
                                                  &MCAN_IR_ARA_MASK)

/* IE Bit Fields */
#define MCAN_IE_RF0NE_MASK                      0x1u
#define MCAN_IE_RF0NE_SHIFT                     0u
#define MCAN_IE_RF0NE_WIDTH                     1u
#define MCAN_IE_RF0NE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF0NE_SHIFT)) \
                                                  &MCAN_IE_RF0NE_MASK)
#define MCAN_IE_RF0WE_MASK                      0x2u
#define MCAN_IE_RF0WE_SHIFT                     1u
#define MCAN_IE_RF0WE_WIDTH                     1u
#define MCAN_IE_RF0WE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF0WE_SHIFT)) \
                                                  &MCAN_IE_RF0WE_MASK)
#define MCAN_IE_RF0FE_MASK                      0x4u
#define MCAN_IE_RF0FE_SHIFT                     2u
#define MCAN_IE_RF0FE_WIDTH                     1u
#define MCAN_IE_RF0FE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF0FE_SHIFT)) \
                                                  &MCAN_IE_RF0FE_MASK)
#define MCAN_IE_RF0LE_MASK                      0x8u
#define MCAN_IE_RF0LE_SHIFT                     3u
#define MCAN_IE_RF0LE_WIDTH                     1u
#define MCAN_IE_RF0LE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF0LE_SHIFT)) \
                                                  &MCAN_IE_RF0LE_MASK)
#define MCAN_IE_RF1NE_MASK                      0x10u
#define MCAN_IE_RF1NE_SHIFT                     4u
#define MCAN_IE_RF1NE_WIDTH                     1u
#define MCAN_IE_RF1NE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF1NE_SHIFT)) \
                                                  &MCAN_IE_RF1NE_MASK)
#define MCAN_IE_RF1WE_MASK                      0x20u
#define MCAN_IE_RF1WE_SHIFT                     5u
#define MCAN_IE_RF1WE_WIDTH                     1u
#define MCAN_IE_RF1WE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF1WE_SHIFT)) \
                                                  &MCAN_IE_RF1WE_MASK)
#define MCAN_IE_RF1FE_MASK                      0x40u
#define MCAN_IE_RF1FE_SHIFT                     6u
#define MCAN_IE_RF1FE_WIDTH                     1u
#define MCAN_IE_RF1FE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF1FE_SHIFT)) \
                                                  &MCAN_IE_RF1FE_MASK)
#define MCAN_IE_RF1LE_MASK                      0x80u
#define MCAN_IE_RF1LE_SHIFT                     7u
#define MCAN_IE_RF1LE_WIDTH                     1u
#define MCAN_IE_RF1LE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_RF1LE_SHIFT)) \
                                                  &MCAN_IE_RF1LE_MASK)
#define MCAN_IE_HPME_MASK                       0x100u
#define MCAN_IE_HPME_SHIFT                      8u
#define MCAN_IE_HPME_WIDTH                      1u
#define MCAN_IE_HPME(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_HPME_SHIFT)) \
                                                  &MCAN_IE_HPME_MASK)
#define MCAN_IE_TCE_MASK                        0x200u
#define MCAN_IE_TCE_SHIFT                       9u
#define MCAN_IE_TCE_WIDTH                       1u
#define MCAN_IE_TCE(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TCE_SHIFT)) \
                                                  &MCAN_IE_TCE_MASK)
#define MCAN_IE_TCFE_MASK                       0x400u
#define MCAN_IE_TCFE_SHIFT                      10u
#define MCAN_IE_TCFE_WIDTH                      1u
#define MCAN_IE_TCFE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TCFE_SHIFT)) \
                                                  &MCAN_IE_TCFE_MASK)
#define MCAN_IE_TFEE_MASK                       0x800u
#define MCAN_IE_TFEE_SHIFT                      11u
#define MCAN_IE_TFEE_WIDTH                      1u
#define MCAN_IE_TFEE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TFEE_SHIFT)) \
                                                  &MCAN_IE_TFEE_MASK)
#define MCAN_IE_TEFNE_MASK                      0x1000u
#define MCAN_IE_TEFNE_SHIFT                     12u
#define MCAN_IE_TEFNE_WIDTH                     1u
#define MCAN_IE_TEFNE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TEFNE_SHIFT)) \
                                                  &MCAN_IE_TEFNE_MASK)
#define MCAN_IE_TEFWE_MASK                      0x2000u
#define MCAN_IE_TEFWE_SHIFT                     13u
#define MCAN_IE_TEFWE_WIDTH                     1u
#define MCAN_IE_TEFWE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TEFWE_SHIFT)) \
                                                  &MCAN_IE_TEFWE_MASK)
#define MCAN_IE_TEFFE_MASK                      0x4000u
#define MCAN_IE_TEFFE_SHIFT                     14u
#define MCAN_IE_TEFFE_WIDTH                     1u
#define MCAN_IE_TEFFE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TEFFE_SHIFT)) \
                                                  &MCAN_IE_TEFFE_MASK)
#define MCAN_IE_TEFLE_MASK                      0x8000u
#define MCAN_IE_TEFLE_SHIFT                     15u
#define MCAN_IE_TEFLE_WIDTH                     1u
#define MCAN_IE_TEFLE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TEFLE_SHIFT)) \
                                                  &MCAN_IE_TEFLE_MASK)
#define MCAN_IE_TSWE_MASK                       0x10000u
#define MCAN_IE_TSWE_SHIFT                      16u
#define MCAN_IE_TSWE_WIDTH                      1u
#define MCAN_IE_TSWE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TSWE_SHIFT)) \
                                                  &MCAN_IE_TSWE_MASK)
#define MCAN_IE_MRAFE_MASK                      0x20000u
#define MCAN_IE_MRAFE_SHIFT                     17u
#define MCAN_IE_MRAFE_WIDTH                     1u
#define MCAN_IE_MRAFE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_MRAFE_SHIFT)) \
                                                  &MCAN_IE_MRAFE_MASK)
#define MCAN_IE_TOOE_MASK                       0x40000u
#define MCAN_IE_TOOE_SHIFT                      18u
#define MCAN_IE_TOOE_WIDTH                      1u
#define MCAN_IE_TOOE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_TOOE_SHIFT)) \
                                                  &MCAN_IE_TOOE_MASK)
#define MCAN_IE_DRXE_MASK                       0x80000u
#define MCAN_IE_DRXE_SHIFT                      19u
#define MCAN_IE_DRXE_WIDTH                      1u
#define MCAN_IE_DRXE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_DRXE_SHIFT)) \
                                                  &MCAN_IE_DRXE_MASK)
#define MCAN_IE_BECE_MASK                       0x100000u
#define MCAN_IE_BECE_SHIFT                      20u
#define MCAN_IE_BECE_WIDTH                      1u
#define MCAN_IE_BECE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_BECE_SHIFT)) \
                                                  &MCAN_IE_BECE_MASK)
#define MCAN_IE_BEUE_MASK                       0x200000u
#define MCAN_IE_BEUE_SHIFT                      21u
#define MCAN_IE_BEUE_WIDTH                      1u
#define MCAN_IE_BEUE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_BEUE_SHIFT)) \
                                                  &MCAN_IE_BEUE_MASK)
#define MCAN_IE_ELOE_MASK                       0x400000u
#define MCAN_IE_ELOE_SHIFT                      22u
#define MCAN_IE_ELOE_WIDTH                      1u
#define MCAN_IE_ELOE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_ELOE_SHIFT)) \
                                                  &MCAN_IE_ELOE_MASK)
#define MCAN_IE_EPE_MASK                        0x800000u
#define MCAN_IE_EPE_SHIFT                       23u
#define MCAN_IE_EPE_WIDTH                       1u
#define MCAN_IE_EPE(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_EPE_SHIFT)) \
                                                  &MCAN_IE_EPE_MASK)
#define MCAN_IE_EWE_MASK                        0x1000000u
#define MCAN_IE_EWE_SHIFT                       24u
#define MCAN_IE_EWE_WIDTH                       1u
#define MCAN_IE_EWE(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_EWE_SHIFT)) \
                                                  &MCAN_IE_EWE_MASK)
#define MCAN_IE_BOE_MASK                        0x2000000u
#define MCAN_IE_BOE_SHIFT                       25u
#define MCAN_IE_BOE_WIDTH                       1u
#define MCAN_IE_BOE(x)                          (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_BOE_SHIFT)) \
                                                  &MCAN_IE_BOE_MASK)
#define MCAN_IE_WDIE_MASK                       0x4000000u
#define MCAN_IE_WDIE_SHIFT                      26u
#define MCAN_IE_WDIE_WIDTH                      1u
#define MCAN_IE_WDIE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_WDIE_SHIFT)) \
                                                  &MCAN_IE_WDIE_MASK)
#define MCAN_IE_PEAE_MASK                       0x8000000u
#define MCAN_IE_PEAE_SHIFT                      27u
#define MCAN_IE_PEAE_WIDTH                      1u
#define MCAN_IE_PEAE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_PEAE_SHIFT)) \
                                                  &MCAN_IE_PEAE_MASK)
#define MCAN_IE_PEDE_MASK                       0x10000000u
#define MCAN_IE_PEDE_SHIFT                      28u
#define MCAN_IE_PEDE_WIDTH                      1u
#define MCAN_IE_PEDE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_PEDE_SHIFT)) \
                                                  &MCAN_IE_PEDE_MASK)
#define MCAN_IE_ARAE_MASK                       0x20000000u
#define MCAN_IE_ARAE_SHIFT                      29u
#define MCAN_IE_ARAE_WIDTH                      1u
#define MCAN_IE_ARAE(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_IE_ARAE_SHIFT)) \
                                                  &MCAN_IE_ARAE_MASK)
/* ILS Bit Fields */
#define MCAN_ILS_RF0NL_MASK                     0x1u
#define MCAN_ILS_RF0NL_SHIFT                    0u
#define MCAN_ILS_RF0NL_WIDTH                    1u
#define MCAN_ILS_RF0NL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF0NL_SHIFT)) \
                                                  &MCAN_ILS_RF0NL_MASK)
#define MCAN_ILS_RF0WL_MASK                     0x2u
#define MCAN_ILS_RF0WL_SHIFT                    1u
#define MCAN_ILS_RF0WL_WIDTH                    1u
#define MCAN_ILS_RF0WL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF0WL_SHIFT)) \
                                                  &MCAN_ILS_RF0WL_MASK)
#define MCAN_ILS_RF0FL_MASK                     0x4u
#define MCAN_ILS_RF0FL_SHIFT                    2u
#define MCAN_ILS_RF0FL_WIDTH                    1u
#define MCAN_ILS_RF0FL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF0FL_SHIFT)) \
                                                  &MCAN_ILS_RF0FL_MASK)
#define MCAN_ILS_RF0LL_MASK                     0x8u
#define MCAN_ILS_RF0LL_SHIFT                    3u
#define MCAN_ILS_RF0LL_WIDTH                    1u
#define MCAN_ILS_RF0LL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF0LL_SHIFT)) \
                                                  &MCAN_ILS_RF0LL_MASK)
#define MCAN_ILS_RF1NL_MASK                     0x10u
#define MCAN_ILS_RF1NL_SHIFT                    4u
#define MCAN_ILS_RF1NL_WIDTH                    1u
#define MCAN_ILS_RF1NL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF1NL_SHIFT)) \
                                                  &MCAN_ILS_RF1NL_MASK)
#define MCAN_ILS_RF1WL_MASK                     0x20u
#define MCAN_ILS_RF1WL_SHIFT                    5u
#define MCAN_ILS_RF1WL_WIDTH                    1u
#define MCAN_ILS_RF1WL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF1WL_SHIFT)) \
                                                  &MCAN_ILS_RF1WL_MASK)
#define MCAN_ILS_RF1FL_MASK                     0x40u
#define MCAN_ILS_RF1FL_SHIFT                    6u
#define MCAN_ILS_RF1FL_WIDTH                    1u
#define MCAN_ILS_RF1FL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF1FL_SHIFT)) \
                                                  &MCAN_ILS_RF1FL_MASK)
#define MCAN_ILS_RF1LL_MASK                     0x80u
#define MCAN_ILS_RF1LL_SHIFT                    7u
#define MCAN_ILS_RF1LL_WIDTH                    1u
#define MCAN_ILS_RF1LL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_RF1LL_SHIFT)) \
                                                  &MCAN_ILS_RF1LL_MASK)
#define MCAN_ILS_HPML_MASK                      0x100u
#define MCAN_ILS_HPML_SHIFT                     8u
#define MCAN_ILS_HPML_WIDTH                     1u
#define MCAN_ILS_HPML(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_HPML_SHIFT)) \
                                                  &MCAN_ILS_HPML_MASK)
#define MCAN_ILS_TCL_MASK                       0x200u
#define MCAN_ILS_TCL_SHIFT                      9u
#define MCAN_ILS_TCL_WIDTH                      1u
#define MCAN_ILS_TCL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TCL_SHIFT)) \
                                                  &MCAN_ILS_TCL_MASK)
#define MCAN_ILS_TCFL_MASK                      0x400u
#define MCAN_ILS_TCFL_SHIFT                     10u
#define MCAN_ILS_TCFL_WIDTH                     1u
#define MCAN_ILS_TCFL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TCFL_SHIFT)) \
                                                  &MCAN_ILS_TCFL_MASK)
#define MCAN_ILS_TFEL_MASK                      0x800u
#define MCAN_ILS_TFEL_SHIFT                     11u
#define MCAN_ILS_TFEL_WIDTH                     1u
#define MCAN_ILS_TFEL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TFEL_SHIFT)) \
                                                  &MCAN_ILS_TFEL_MASK)
#define MCAN_ILS_TEFNL_MASK                     0x1000u
#define MCAN_ILS_TEFNL_SHIFT                    12u
#define MCAN_ILS_TEFNL_WIDTH                    1u
#define MCAN_ILS_TEFNL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TEFNL_SHIFT)) \
                                                  &MCAN_ILS_TEFNL_MASK)
#define MCAN_ILS_TEFWL_MASK                     0x2000u
#define MCAN_ILS_TEFWL_SHIFT                    13u
#define MCAN_ILS_TEFWL_WIDTH                    1u
#define MCAN_ILS_TEFWL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TEFWL_SHIFT)) \
                                                  &MCAN_ILS_TEFWL_MASK)
#define MCAN_ILS_TEFFL_MASK                     0x4000u
#define MCAN_ILS_TEFFL_SHIFT                    14u
#define MCAN_ILS_TEFFL_WIDTH                    1u
#define MCAN_ILS_TEFFL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TEFFL_SHIFT)) \
                                                  &MCAN_ILS_TEFFL_MASK)
#define MCAN_ILS_TEFLL_MASK                     0x8000u
#define MCAN_ILS_TEFLL_SHIFT                    15u
#define MCAN_ILS_TEFLL_WIDTH                    1u
#define MCAN_ILS_TEFLL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TEFLL_SHIFT)) \
                                                  &MCAN_ILS_TEFLL_MASK)
#define MCAN_ILS_TSWL_MASK                      0x10000u
#define MCAN_ILS_TSWL_SHIFT                     16u
#define MCAN_ILS_TSWL_WIDTH                     1u
#define MCAN_ILS_TSWL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TSWL_SHIFT)) \
                                                  &MCAN_ILS_TSWL_MASK)
#define MCAN_ILS_MRAFL_MASK                     0x20000u
#define MCAN_ILS_MRAFL_SHIFT                    17u
#define MCAN_ILS_MRAFL_WIDTH                    1u
#define MCAN_ILS_MRAFL(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_MRAFL_SHIFT)) \
                                                  &MCAN_ILS_MRAFL_MASK)
#define MCAN_ILS_TOOL_MASK                      0x40000u
#define MCAN_ILS_TOOL_SHIFT                     18u
#define MCAN_ILS_TOOL_WIDTH                     1u
#define MCAN_ILS_TOOL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_TOOL_SHIFT)) \
                                                  &MCAN_ILS_TOOL_MASK)
#define MCAN_ILS_DRXL_MASK                      0x80000u
#define MCAN_ILS_DRXL_SHIFT                     19u
#define MCAN_ILS_DRXL_WIDTH                     1u
#define MCAN_ILS_DRXL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_DRXL_SHIFT)) \
                                                  &MCAN_ILS_DRXL_MASK)
#define MCAN_ILS_BECL_MASK                      0x100000u
#define MCAN_ILS_BECL_SHIFT                     20u
#define MCAN_ILS_BECL_WIDTH                     1u
#define MCAN_ILS_BECL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_BECL_SHIFT)) \
                                                  &MCAN_ILS_BECL_MASK)
#define MCAN_ILS_BEUL_MASK                      0x200000u
#define MCAN_ILS_BEUL_SHIFT                     21u
#define MCAN_ILS_BEUL_WIDTH                     1u
#define MCAN_ILS_BEUL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_BEUL_SHIFT)) \
                                                  &MCAN_ILS_BEUL_MASK)
#define MCAN_ILS_ELOL_MASK                      0x400000u
#define MCAN_ILS_ELOL_SHIFT                     22u
#define MCAN_ILS_ELOL_WIDTH                     1u
#define MCAN_ILS_ELOL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_ELOL_SHIFT)) \
                                                  &MCAN_ILS_ELOL_MASK)
#define MCAN_ILS_EPL_MASK                       0x800000u
#define MCAN_ILS_EPL_SHIFT                      23u
#define MCAN_ILS_EPL_WIDTH                      1u
#define MCAN_ILS_EPL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_EPL_SHIFT)) \
                                                  &MCAN_ILS_EPL_MASK)
#define MCAN_ILS_EWL_MASK                       0x1000000u
#define MCAN_ILS_EWL_SHIFT                      24u
#define MCAN_ILS_EWL_WIDTH                      1u
#define MCAN_ILS_EWL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_EWL_SHIFT)) \
                                                  &MCAN_ILS_EWL_MASK)
#define MCAN_ILS_BOL_MASK                       0x2000000u
#define MCAN_ILS_BOL_SHIFT                      25u
#define MCAN_ILS_BOL_WIDTH                      1u
#define MCAN_ILS_BOL(x)                         (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_BOL_SHIFT)) \
                                                  &MCAN_ILS_BOL_MASK)
#define MCAN_ILS_WDIL_MASK                      0x4000000u
#define MCAN_ILS_WDIL_SHIFT                     26u
#define MCAN_ILS_WDIL_WIDTH                     1u
#define MCAN_ILS_WDIL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_WDIL_SHIFT)) \
                                                  &MCAN_ILS_WDIL_MASK)
#define MCAN_ILS_PEAL_MASK                      0x8000000u
#define MCAN_ILS_PEAL_SHIFT                     27u
#define MCAN_ILS_PEAL_WIDTH                     1u
#define MCAN_ILS_PEAL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_PEAL_SHIFT)) \
                                                  &MCAN_ILS_PEAL_MASK)
#define MCAN_ILS_PEDL_MASK                      0x10000000u
#define MCAN_ILS_PEDL_SHIFT                     28u
#define MCAN_ILS_PEDL_WIDTH                     1u
#define MCAN_ILS_PEDL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_PEDL_SHIFT)) \
                                                  &MCAN_ILS_PEDL_MASK)
#define MCAN_ILS_ARAL_MASK                      0x20000000u
#define MCAN_ILS_ARAL_SHIFT                     29u
#define MCAN_ILS_ARAL_WIDTH                     1u
#define MCAN_ILS_ARAL(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILS_ARAL_SHIFT)) \
                                                  &MCAN_ILS_ARAL_MASK)
/* ILE Bit Fields */
#define MCAN_ILE_EINT0_MASK                     0x1u
#define MCAN_ILE_EINT0_SHIFT                    0u
#define MCAN_ILE_EINT0_WIDTH                    1u
#define MCAN_ILE_EINT0(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILE_EINT0_SHIFT)) \
                                                  &MCAN_ILE_EINT0_MASK)
#define MCAN_ILE_EINT1_MASK                     0x2u
#define MCAN_ILE_EINT1_SHIFT                    1u
#define MCAN_ILE_EINT1_WIDTH                    1u
#define MCAN_ILE_EINT1(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_ILE_EINT1_SHIFT)) \
                                                  &MCAN_ILE_EINT1_MASK)
/* GFC Bit Fields */
#define MCAN_GFC_RRFE_MASK                      0x1u
#define MCAN_GFC_RRFE_SHIFT                     0u
#define MCAN_GFC_RRFE_WIDTH                     1u
#define MCAN_GFC_RRFE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_GFC_RRFE_SHIFT)) \
                                                  &MCAN_GFC_RRFE_MASK)
#define MCAN_GFC_RRFS_MASK                      0x2u
#define MCAN_GFC_RRFS_SHIFT                     1u
#define MCAN_GFC_RRFS_WIDTH                     1u
#define MCAN_GFC_RRFS(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_GFC_RRFS_SHIFT)) \
                                                  &MCAN_GFC_RRFS_MASK)
#define MCAN_GFC_ANFE_MASK                      0xCu
#define MCAN_GFC_ANFE_SHIFT                     2u
#define MCAN_GFC_ANFE_WIDTH                     2u
#define MCAN_GFC_ANFE(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_GFC_ANFE_SHIFT)) \
                                                  &MCAN_GFC_ANFE_MASK)
#define MCAN_GFC_ANFS_MASK                      0x30u
#define MCAN_GFC_ANFS_SHIFT                     4u
#define MCAN_GFC_ANFS_WIDTH                     2u
#define MCAN_GFC_ANFS(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_GFC_ANFS_SHIFT)) \
                                                  &MCAN_GFC_ANFS_MASK)
/* SIDFC Bit Fields */
#define MCAN_SIDFC_FLSSA_MASK                   0xFFFCu
#define MCAN_SIDFC_FLSSA_SHIFT                  2u
#define MCAN_SIDFC_FLSSA_WIDTH                  14u
#define MCAN_SIDFC_FLSSA(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_SIDFC_FLSSA_SHIFT)) \
                                                  &MCAN_SIDFC_FLSSA_MASK)
#define MCAN_SIDFC_LSS_MASK                     0xFF0000u
#define MCAN_SIDFC_LSS_SHIFT                    16u
#define MCAN_SIDFC_LSS_WIDTH                    8u
#define MCAN_SIDFC_LSS(x)                       ((uint32)(((uint32)(x)) \
                                                  <<MCAN_SIDFC_LSS_SHIFT))
/* XIDFC Bit Fields */
#define MCAN_XIDFC_FLESA_MASK                   0xFFFCu
#define MCAN_XIDFC_FLESA_SHIFT                  2u
#define MCAN_XIDFC_FLESA_WIDTH                  14u
#define MCAN_XIDFC_FLESA(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_XIDFC_FLESA_SHIFT)) \
                                                  &MCAN_XIDFC_FLESA_MASK)
#define MCAN_XIDFC_LSE_MASK                     0x7F0000u
#define MCAN_XIDFC_LSE_SHIFT                    16u
#define MCAN_XIDFC_LSE_WIDTH                    7u
#define MCAN_XIDFC_LSE(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_XIDFC_LSE_SHIFT)) \
                                                  &MCAN_XIDFC_LSE_MASK)
/* XIDAM Bit Fields */
#define MCAN_XIDAM_EIDM_MASK                    0x1FFFFFFFu
#define MCAN_XIDAM_EIDM_SHIFT                   0u
#define MCAN_XIDAM_EIDM_WIDTH                   29u
#define MCAN_XIDAM_EIDM(x)                      (((uint32)(x)) \
                                                  &MCAN_XIDAM_EIDM_MASK)
/* HPMS Bit Fields */
#define MCAN_HPMS_BIDX_MASK                     0x3Fu
#define MCAN_HPMS_BIDX_SHIFT                    0u
#define MCAN_HPMS_BIDX_WIDTH                    6u
#define MCAN_HPMS_BIDX(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_HPMS_BIDX_SHIFT)) \
                                                  &MCAN_HPMS_BIDX_MASK)
#define MCAN_HPMS_MSI_MASK                      0xC0u
#define MCAN_HPMS_MSI_SHIFT                     6u
#define MCAN_HPMS_MSI_WIDTH                     2u
#define MCAN_HPMS_MSI(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_HPMS_MSI_SHIFT)) \
                                                  &MCAN_HPMS_MSI_MASK)
#define MCAN_HPMS_FIDX_MASK                     0x7F00u
#define MCAN_HPMS_FIDX_SHIFT                    8u
#define MCAN_HPMS_FIDX_WIDTH                    7u
#define MCAN_HPMS_FIDX(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_HPMS_FIDX_SHIFT)) \
                                                  &MCAN_HPMS_FIDX_MASK)
#define MCAN_HPMS_FLST_MASK                     0x8000u
#define MCAN_HPMS_FLST_SHIFT                    15u
#define MCAN_HPMS_FLST_WIDTH                    1u
#define MCAN_HPMS_FLST(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_HPMS_FLST_SHIFT)) \
                                                  &MCAN_HPMS_FLST_MASK)
/* NDAT1 Bit Fields */
#define MCAN_NDAT1_ND1_MASK                     0xFFFFFFFFu
#define MCAN_NDAT1_ND1_SHIFT                    0u
#define MCAN_NDAT1_ND1_WIDTH                    32u
#define MCAN_NDAT1_ND1(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_NDAT1_ND1_SHIFT)) \
                                                  &MCAN_NDAT1_ND1_MASK)
/* NDAT2 Bit Fields */
#define MCAN_NDAT2_ND2_MASK                     0xFFFFFFFFu
#define MCAN_NDAT2_ND2_SHIFT                    0u
#define MCAN_NDAT2_ND2_WIDTH                    32u
#define MCAN_NDAT2_ND2(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_NDAT2_ND2_SHIFT)) \
                                                  &MCAN_NDAT2_ND2_MASK)
/* RXF0C Bit Fields */
#define MCAN_RXF0C_F0SA_MASK                    0xFFFCu
#define MCAN_RXF0C_F0SA_SHIFT                   2u
#define MCAN_RXF0C_F0SA_WIDTH                   14u
#define MCAN_RXF0C_F0SA(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0C_F0SA_SHIFT)) \
                                                  &MCAN_RXF0C_F0SA_MASK)
#define MCAN_RXF0C_F0S_MASK                     0x7F0000u
#define MCAN_RXF0C_F0S_SHIFT                    16u
#define MCAN_RXF0C_F0S_WIDTH                    7u
#define MCAN_RXF0C_F0S(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0C_F0S_SHIFT)) \
                                                  &MCAN_RXF0C_F0S_MASK)
#define MCAN_RXF0C_F0WM_MASK                    0x7F000000u
#define MCAN_RXF0C_F0WM_SHIFT                   24u
#define MCAN_RXF0C_F0WM_WIDTH                   7u
#define MCAN_RXF0C_F0WM(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0C_F0WM_SHIFT)) \
                                                  &MCAN_RXF0C_F0WM_MASK)
#define MCAN_RXF0C_F0OM_MASK                    0x80000000u
#define MCAN_RXF0C_F0OM_SHIFT                   31u
#define MCAN_RXF0C_F0OM_WIDTH                   1u
#define MCAN_RXF0C_F0OM(x)                      ((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0C_F0OM_SHIFT))
/* RXF0S Bit Fields */
#define MCAN_RXF0S_F0FL_MASK                    0x7Fu
#define MCAN_RXF0S_F0FL_SHIFT                   0u
#define MCAN_RXF0S_F0FL_WIDTH                   7u
#define MCAN_RXF0S_F0FL(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0S_F0FL_SHIFT)) \
                                                  &MCAN_RXF0S_F0FL_MASK)
#define MCAN_RXF0S_F0GI_MASK                    0x3F00u
#define MCAN_RXF0S_F0GI_SHIFT                   8u
#define MCAN_RXF0S_F0GI_WIDTH                   6u
#define MCAN_RXF0S_F0GI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0S_F0GI_SHIFT)) \
                                                  &MCAN_RXF0S_F0GI_MASK)
#define MCAN_RXF0S_F0PI_MASK                    0x3F0000u
#define MCAN_RXF0S_F0PI_SHIFT                   16u
#define MCAN_RXF0S_F0PI_WIDTH                   6u
#define MCAN_RXF0S_F0PI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0S_F0PI_SHIFT)) \
                                                  &MCAN_RXF0S_F0PI_MASK)
#define MCAN_RXF0S_F0F_MASK                     0x1000000u
#define MCAN_RXF0S_F0F_SHIFT                    24u
#define MCAN_RXF0S_F0F_WIDTH                    1u
#define MCAN_RXF0S_F0F(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0S_F0F_SHIFT)) \
                                                  &MCAN_RXF0S_F0F_MASK)
#define MCAN_RXF0S_RF0L_MASK                    0x2000000u
#define MCAN_RXF0S_RF0L_SHIFT                   25u
#define MCAN_RXF0S_RF0L_WIDTH                   1u
#define MCAN_RXF0S_RF0L(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0S_RF0L_SHIFT)) \
                                                  &MCAN_RXF0S_RF0L_MASK)
/* RXF0A Bit Fields */
#define MCAN_RXF0A_F0AI_MASK                    0x3Fu
#define MCAN_RXF0A_F0AI_SHIFT                   0u
#define MCAN_RXF0A_F0AI_WIDTH                   6u
#define MCAN_RXF0A_F0AI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF0A_F0AI_SHIFT)) \
                                                  &MCAN_RXF0A_F0AI_MASK)
/* RXBC Bit Fields */
#define MCAN_RXBC_RBSA_MASK                     0xFFFCu
#define MCAN_RXBC_RBSA_SHIFT                    2u
#define MCAN_RXBC_RBSA_WIDTH                    14u
#define MCAN_RXBC_RBSA(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXBC_RBSA_SHIFT)) \
                                                  &MCAN_RXBC_RBSA_MASK)
/* RXF1C Bit Fields */
#define MCAN_RXF1C_F1SA_MASK                    0xFFFCu
#define MCAN_RXF1C_F1SA_SHIFT                   2u
#define MCAN_RXF1C_F1SA_WIDTH                   14u
#define MCAN_RXF1C_F1SA(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1C_F1SA_SHIFT)) \
                                                  &MCAN_RXF1C_F1SA_MASK)
#define MCAN_RXF1C_F1S_MASK                     0x7F0000u
#define MCAN_RXF1C_F1S_SHIFT                    16u
#define MCAN_RXF1C_F1S_WIDTH                    7u
#define MCAN_RXF1C_F1S(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1C_F1S_SHIFT)) \
                                                  &MCAN_RXF1C_F1S_MASK)
#define MCAN_RXF1C_F1WM_MASK                    0x7F000000u
#define MCAN_RXF1C_F1WM_SHIFT                   24u
#define MCAN_RXF1C_F1WM_WIDTH                   7u
#define MCAN_RXF1C_F1WM(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1C_F1WM_SHIFT)) \
                                                  &MCAN_RXF1C_F1WM_MASK)
#define MCAN_RXF1C_F1OM_MASK                    0x80000000u
#define MCAN_RXF1C_F1OM_SHIFT                   31u
#define MCAN_RXF1C_F1OM_WIDTH                   1u
#define MCAN_RXF1C_F1OM(x)                      ((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1C_F1OM_SHIFT))
/* RXF1S Bit Fields */
#define MCAN_RXF1S_F1FL_MASK                    0x7Fu
#define MCAN_RXF1S_F1FL_SHIFT                   0u
#define MCAN_RXF1S_F1FL_WIDTH                   7u
#define MCAN_RXF1S_F1FL(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_F1FL_SHIFT)) \
                                                  &MCAN_RXF1S_F1FL_MASK)
#define MCAN_RXF1S_F1GI_MASK                    0x3F00u
#define MCAN_RXF1S_F1GI_SHIFT                   8u
#define MCAN_RXF1S_F1GI_WIDTH                   6u
#define MCAN_RXF1S_F1GI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_F1GI_SHIFT)) \
                                                  &MCAN_RXF1S_F1GI_MASK)
#define MCAN_RXF1S_F1PI_MASK                    0x3F0000u
#define MCAN_RXF1S_F1PI_SHIFT                   16u
#define MCAN_RXF1S_F1PI_WIDTH                   6u
#define MCAN_RXF1S_F1PI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_F1PI_SHIFT)) \
                                                  &MCAN_RXF1S_F1PI_MASK)
#define MCAN_RXF1S_F1F_MASK                     0x1000000u
#define MCAN_RXF1S_F1F_SHIFT                    24u
#define MCAN_RXF1S_F1F_WIDTH                    1u
#define MCAN_RXF1S_F1F(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_F1F_SHIFT)) \
                                                  &MCAN_RXF1S_F1F_MASK)
#define MCAN_RXF1S_RF1L_MASK                    0x2000000u
#define MCAN_RXF1S_RF1L_SHIFT                   25u
#define MCAN_RXF1S_RF1L_WIDTH                   1u
#define MCAN_RXF1S_RF1L(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_RF1L_SHIFT)) \
                                                  &MCAN_RXF1S_RF1L_MASK)
#define MCAN_RXF1S_DMS_MASK                     0xC0000000u
#define MCAN_RXF1S_DMS_SHIFT                    30u
#define MCAN_RXF1S_DMS_WIDTH                    2u
#define MCAN_RXF1S_DMS(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1S_DMS_SHIFT)) \
                                                  &MCAN_RXF1S_DMS_MASK)
/* RXF1A Bit Fields */
#define MCAN_RXF1A_F1AI_MASK                    0x3Fu
#define MCAN_RXF1A_F1AI_SHIFT                   0u
#define MCAN_RXF1A_F1AI_WIDTH                   6u
#define MCAN_RXF1A_F1AI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXF1A_F1AI_SHIFT)) \
                                                  &MCAN_RXF1A_F1AI_MASK)
/* RXESC Bit Fields */
#define MCAN_RXESC_F0DS_MASK                    0x7u
#define MCAN_RXESC_F0DS_SHIFT                   0u
#define MCAN_RXESC_F0DS_WIDTH                   3u
#define MCAN_RXESC_F0DS(x)                      (((uint32)(x)) \
                                                  &MCAN_RXESC_F0DS_MASK)
#define MCAN_RXESC_F1DS_MASK                    0x70u
#define MCAN_RXESC_F1DS_SHIFT                   4u
#define MCAN_RXESC_F1DS_WIDTH                   3u
#define MCAN_RXESC_F1DS(x)                      ((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXESC_F1DS_SHIFT))
#define MCAN_RXESC_RBDS_MASK                    0x700u
#define MCAN_RXESC_RBDS_SHIFT                   8u
#define MCAN_RXESC_RBDS_WIDTH                   3u
#define MCAN_RXESC_RBDS(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_RXESC_RBDS_SHIFT)) \
                                                  &MCAN_RXESC_RBDS_MASK)
/* TXBC Bit Fields */
#define MCAN_TXBC_TBSA_MASK                     0xFFFCu
#define MCAN_TXBC_TBSA_SHIFT                    2u
#define MCAN_TXBC_TBSA_WIDTH                    14u
#define MCAN_TXBC_TBSA(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBC_TBSA_SHIFT)) \
                                                  &MCAN_TXBC_TBSA_MASK)
#define MCAN_TXBC_NDTB_MASK                     0x3F0000u
#define MCAN_TXBC_NDTB_SHIFT                    16u
#define MCAN_TXBC_NDTB_WIDTH                    6u
#define MCAN_TXBC_NDTB(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBC_NDTB_SHIFT)) \
                                                  &MCAN_TXBC_NDTB_MASK)
#define MCAN_TXBC_TFQS_MASK                     0x3F000000u
#define MCAN_TXBC_TFQS_SHIFT                    24u
#define MCAN_TXBC_TFQS_WIDTH                    6u
#define MCAN_TXBC_TFQS(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBC_TFQS_SHIFT)) \
                                                  &MCAN_TXBC_TFQS_MASK)
#define MCAN_TXBC_TFQM_MASK                     0x40000000u
#define MCAN_TXBC_TFQM_SHIFT                    30u
#define MCAN_TXBC_TFQM_WIDTH                    1u
#define MCAN_TXBC_TFQM(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBC_TFQM_SHIFT)) \
                                                  &MCAN_TXBC_TFQM_MASK)
/* TXFQS Bit Fields */
#define MCAN_TXFQS_TFFL_MASK                    0x3Fu
#define MCAN_TXFQS_TFFL_SHIFT                   0u
#define MCAN_TXFQS_TFFL_WIDTH                   6u
#define MCAN_TXFQS_TFFL(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXFQS_TFFL_SHIFT)) \
                                                  &MCAN_TXFQS_TFFL_MASK)
#define MCAN_TXFQS_TFGI_MASK                    0x1F00u
#define MCAN_TXFQS_TFGI_SHIFT                   8u
#define MCAN_TXFQS_TFGI_WIDTH                   5u
#define MCAN_TXFQS_TFGI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXFQS_TFGI_SHIFT)) \
                                                  &MCAN_TXFQS_TFGI_MASK)
#define MCAN_TXFQS_TFQPI_MASK                   0x1F0000u
#define MCAN_TXFQS_TFQPI_SHIFT                  16u
#define MCAN_TXFQS_TFQPI_WIDTH                  5u
#define MCAN_TXFQS_TFQPI(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXFQS_TFQPI_SHIFT)) \
                                                  &MCAN_TXFQS_TFQPI_MASK)
#define MCAN_TXFQS_TFQF_MASK                    0x200000u
#define MCAN_TXFQS_TFQF_SHIFT                   21u
#define MCAN_TXFQS_TFQF_WIDTH                   1u
#define MCAN_TXFQS_TFQF(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXFQS_TFQF_SHIFT)) \
                                                  &MCAN_TXFQS_TFQF_MASK)
/* TXESC Bit Fields */
#define MCAN_TXESC_TBDS_MASK                    0x7u
#define MCAN_TXESC_TBDS_SHIFT                   0u
#define MCAN_TXESC_TBDS_WIDTH                   3u
#define MCAN_TXESC_TBDS(x)                      (((uint32)(x)) \
                                                  &MCAN_TXESC_TBDS_MASK)
/* TXBRP Bit Fields */
#define MCAN_TXBRP_TRP_MASK                     0xFFFFFFFFu
#define MCAN_TXBRP_TRP_SHIFT                    0u
#define MCAN_TXBRP_TRP_WIDTH                    32u
#define MCAN_TXBRP_TRP(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBRP_TRP_SHIFT)) \
                                                  &MCAN_TXBRP_TRP_MASK)
/* TXBAR Bit Fields */
#define MCAN_TXBAR_AR_MASK                      0xFFFFFFFFu
#define MCAN_TXBAR_AR_SHIFT                     0u
#define MCAN_TXBAR_AR_WIDTH                     32u
#define MCAN_TXBAR_AR(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBAR_AR_SHIFT)) \
                                                  &MCAN_TXBAR_AR_MASK)
/* TXBCR Bit Fields */
#define MCAN_TXBCR_CR_MASK                      0xFFFFFFFFu
#define MCAN_TXBCR_CR_SHIFT                     0u
#define MCAN_TXBCR_CR_WIDTH                     32u
#define MCAN_TXBCR_CR(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBCR_CR_SHIFT)) \
                                                  &MCAN_TXBCR_CR_MASK)
/* TXBTO Bit Fields */
#define MCAN_TXBTO_TO_MASK                      0xFFFFFFFFu
#define MCAN_TXBTO_TO_SHIFT                     0u
#define MCAN_TXBTO_TO_WIDTH                     32u
#define MCAN_TXBTO_TO(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBTO_TO_SHIFT)) \
                                                  &MCAN_TXBTO_TO_MASK)
/* TXBCF Bit Fields */
#define MCAN_TXBCF_CF_MASK                      0xFFFFFFFFu
#define MCAN_TXBCF_CF_SHIFT                     0u
#define MCAN_TXBCF_CF_WIDTH                     32u
#define MCAN_TXBCF_CF(x)                        (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBCF_CF_SHIFT)) \
                                                  &MCAN_TXBCF_CF_MASK)
/* TXBTIE Bit Fields */
#define MCAN_TXBTIE_TIE_MASK                    0xFFFFFFFFu
#define MCAN_TXBTIE_TIE_SHIFT                   0u
#define MCAN_TXBTIE_TIE_WIDTH                   32u
#define MCAN_TXBTIE_TIE(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBTIE_TIE_SHIFT)) \
                                                  &MCAN_TXBTIE_TIE_MASK)
/* TXBCIE Bit Fields */
#define MCAN_TXBCIE_CFIE_MASK                   0xFFFFFFFFu
#define MCAN_TXBCIE_CFIE_SHIFT                  0u
#define MCAN_TXBCIE_CFIE_WIDTH                  32u
#define MCAN_TXBCIE_CFIE(x)                     (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXBCIE_CFIE_SHIFT)) \
                                                  &MCAN_TXBCIE_CFIE_MASK)
/* TXEFC Bit Fields */
#define MCAN_TXEFC_EFSA_MASK                    0xFFFCu
#define MCAN_TXEFC_EFSA_SHIFT                   2u
#define MCAN_TXEFC_EFSA_WIDTH                   14u
#define MCAN_TXEFC_EFSA(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFC_EFSA_SHIFT)) \
                                                  &MCAN_TXEFC_EFSA_MASK)
#define MCAN_TXEFC_EFS_MASK                     0x3F0000u
#define MCAN_TXEFC_EFS_SHIFT                    16u
#define MCAN_TXEFC_EFS_WIDTH                    6u
#define MCAN_TXEFC_EFS(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFC_EFS_SHIFT)) \
                                                  &MCAN_TXEFC_EFS_MASK)
#define MCAN_TXEFC_EFWM_MASK                    0x3F000000u
#define MCAN_TXEFC_EFWM_SHIFT                   24u
#define MCAN_TXEFC_EFWM_WIDTH                   6u
#define MCAN_TXEFC_EFWM(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFC_EFWM_SHIFT)) \
                                                  &MCAN_TXEFC_EFWM_MASK)
/* TXEFS Bit Fields */
#define MCAN_TXEFS_EFFL_MASK                    0x3Fu
#define MCAN_TXEFS_EFFL_SHIFT                   0u
#define MCAN_TXEFS_EFFL_WIDTH                   6u
#define MCAN_TXEFS_EFFL(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFS_EFFL_SHIFT)) \
                                                  &MCAN_TXEFS_EFFL_MASK)
#define MCAN_TXEFS_EFGI_MASK                    0x1F00u
#define MCAN_TXEFS_EFGI_SHIFT                   8u
#define MCAN_TXEFS_EFGI_WIDTH                   5u
#define MCAN_TXEFS_EFGI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFS_EFGI_SHIFT)) \
                                                  &MCAN_TXEFS_EFGI_MASK)
#define MCAN_TXEFS_EFPI_MASK                    0x1F0000u
#define MCAN_TXEFS_EFPI_SHIFT                   16u
#define MCAN_TXEFS_EFPI_WIDTH                   5u
#define MCAN_TXEFS_EFPI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFS_EFPI_SHIFT)) \
                                                  &MCAN_TXEFS_EFPI_MASK)
#define MCAN_TXEFS_EFF_MASK                     0x1000000u
#define MCAN_TXEFS_EFF_SHIFT                    24u
#define MCAN_TXEFS_EFF_WIDTH                    1u
#define MCAN_TXEFS_EFF(x)                       (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFS_EFF_SHIFT)) \
                                                  &MCAN_TXEFS_EFF_MASK)
#define MCAN_TXEFS_TEFL_MASK                    0x2000000u
#define MCAN_TXEFS_TEFL_SHIFT                   25u
#define MCAN_TXEFS_TEFL_WIDTH                   1u
#define MCAN_TXEFS_TEFL(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFS_TEFL_SHIFT)) \
                                                  &MCAN_TXEFS_TEFL_MASK)
/* TXEFA Bit Fields */
#define MCAN_TXEFA_EFAI_MASK                    0x1Fu
#define MCAN_TXEFA_EFAI_SHIFT                   0u
#define MCAN_TXEFA_EFAI_WIDTH                   5u
#define MCAN_TXEFA_EFAI(x)                      (((uint32)(((uint32)(x)) \
                                                  <<MCAN_TXEFA_EFAI_SHIFT)) \
                                                  &MCAN_TXEFA_EFAI_MASK)

/* ----------------------------------------------------------------------------
   -- Message RAM Masks
   ---------------------------------------------------------------------------- */

/* standard message id filter element */
#define MCAN_STD_FILTER_ID_SFT_MASK              0xC0000000U
#define MCAN_STD_FILTER_ID_SFT_SHIFT             30U
#define MCAN_STD_FILTER_ID_SFT_WIDTH             2U

#define MCAN_STD_FILTER_ID_SFEC_MASK             0x38000000U
#define MCAN_STD_FILTER_ID_SFEC_SHIFT            27U
#define MCAN_STD_FILTER_ID_SFEC_WIDTH            3U

#define MCAN_STD_FILTER_ID_SFID1_MASK            0x7FF0000U
#define MCAN_STD_FILTER_ID_SFID1_SHIFT           16U
#define MCAN_STD_FILTER_ID_SFID1_WIDTH           11U

#define MCAN_STD_FILTER_ID_SSYNC_MASK            0x0080000U
#define MCAN_STD_FILTER_ID_SSYNC_SHIFT           15U
#define MCAN_STD_FILTER_ID_SSYNC_WIDTH           1U

#define MCAN_STD_FILTER_ID_SFID2_MASK            0x7FFU
#define MCAN_STD_FILTER_ID_SFID2_SHIFT           0U
#define MCAN_STD_FILTER_ID_SFID2_WIDTH           11U

/* extended message id filter element */
#define MCAN_EXT_FILTER_ID_EFEC_MASK             0xE0000000U
#define MCAN_EXT_FILTER_ID_EFEC_SHIFT            29U
#define MCAN_EXT_FILTER_ID_EFEC_WIDTH            3U

#define MCAN_EXT_FILTER_ID_EFID1_MASK            0x1FFFFFFFU
#define MCAN_EXT_FILTER_ID_EFID1_SHIFT           0U
#define MCAN_EXT_FILTER_ID_EFID1_WIDTH           29U

#define MCAN_EXT_FILTER_ID_EFT_MASK              0xC0000000U
#define MCAN_EXT_FILTER_ID_EFT_SHIFT             30U
#define MCAN_EXT_FILTER_ID_EFT_WIDTH             2U

#define MCAN_EXT_FILTER_ID_ESYNC_MASK            0x20000000U
#define MCAN_EXT_FILTER_ID_ESYNC_SHIFT           29U
#define MCAN_EXT_FILTER_ID_ESYNC_WIDTH           1U

#define MCAN_EXT_FILTER_ID_EFID2_MASK            0x1FFFFFFFU
#define MCAN_EXT_FILTER_ID_EFID2_SHIFT           0U
#define MCAN_EXT_FILTER_ID_EFID2_WIDTH           29U

/* tx Buffer Element */
#define MCAN_MSG_ID_EXT_MASK                (0x80000000U)

#define MCAN_TX_BUFFER_ESI_MASK             0x80000000U
#define MCAN_TX_BUFFER_ESI_SHIFT            31U
#define MCAN_TX_BUFFER_ESI_WIDTH            1U

#define MCAN_TX_BUFFER_XTD_MASK             0x40000000U
#define MCAN_TX_BUFFER_XTD_SHIFT            30U
#define MCAN_TX_BUFFER_XTD_WIDTH            1U

#define MCAN_TX_BUFFER_RTR_MASK             0x20000000U
#define MCAN_TX_BUFFER_RTR_SHIFT            29U
#define MCAN_TX_BUFFER_RTR_WIDTH            1U

#define MCAN_TX_BUFFER_STD_ID_MASK          0x1FFC0000U
#define MCAN_TX_BUFFER_STD_ID_SHIFT         18U
#define MCAN_TX_BUFFER_STD_ID_WIDTH         11U

#define MCAN_TX_BUFFER_EXT_ID_MASK          0x1FFFFFFFU
#define MCAN_TX_BUFFER_EXT_ID_SHIFT         0U
#define MCAN_TX_BUFFER_EXT_ID_WIDTH         29U

#define MCAN_TX_BUFFER_MM_MASK              0xFF000000U
#define MCAN_TX_BUFFER_MM_SHIFT             24U
#define MCAN_TX_BUFFER_MM_WIDTH             8U

#define MCAN_TX_BUFFER_EFC_MASK             0x800000U
#define MCAN_TX_BUFFER_EFC_SHIFT            23U
#define MCAN_TX_BUFFER_EFC_WIDTH            1U

#define MCAN_TX_BUFFER_TSCE_MASK            0x400000U
#define MCAN_TX_BUFFER_TSCE_SHIFT           22U
#define MCAN_TX_BUFFER_TSCE_WIDTH           1U

#define MCAN_TX_BUFFER_FDF_MASK            0x200000U
#define MCAN_TX_BUFFER_FDF_SHIFT           21U
#define MCAN_TX_BUFFER_FDF_WIDTH           1U

#define MCAN_TX_BUFFER_BRS_MASK            0x100000U
#define MCAN_TX_BUFFER_BRS_SHIFT           20U
#define MCAN_TX_BUFFER_BRS_WIDTH           1U

#define MCAN_TX_BUFFER_DLC_MASK            0xF0000U
#define MCAN_TX_BUFFER_DLC_SHIFT           16U
#define MCAN_TX_BUFFER_DLC_WIDTH           4U

#define MCAN_TX_BUFFER_MM_HIGHBYTE_MASK    0xFF00U
#define MCAN_TX_BUFFER_MM_HBYTE_SHIFT      8U
#define MCAN_TX_BUFFER_MM_HBYTE_WIDTH      8U

/* tx event fifo element*/
#define MCAN_TX_EVENT_FIFO_ESI_MASK             0x80000000U
#define MCAN_TX_EVENT_FIFO_ESI_SHIFT            31U
#define MCAN_TX_EVENT_FIFO_ESI_WIDTH            1U

#define MCAN_TX_EVENT_FIFO_XTD_MASK             0x40000000U
#define MCAN_TX_EVENT_FIFO_XTD_SHIFT            30U
#define MCAN_TX_EVENT_FIFO_XTD_WIDTH            1U

#define MCAN_TX_EVENT_FIFO_RTR_MASK             0x20000000U
#define MCAN_TX_EVENT_FIFO_RTR_SHIFT            29U
#define MCAN_TX_EVENT_FIFO_RTR_WIDTH            1U

#define MCAN_TX_EVENT_FIFO_STD_ID_MASK          0x1FFC0000U
#define MCAN_TX_EVENT_FIFO_STD_ID_SHIFT         18U
#define MCAN_TX_EVENT_FIFO_STD_ID_WIDTH         11U

#define MCAN_TX_EVENT_FIFO_EXT_ID_MASK          0x1FFFFFFFU
#define MCAN_TX_EVENT_FIFO_EXT_ID_SHIFT         0U
#define MCAN_TX_EVENT_FIFO_EXT_ID_WIDTH         29U

#define MCAN_TX_EVENT_FIFO_MM_MASK              0xFF000000U
#define MCAN_TX_EVENT_FIFO_MM_SHIFT             24U
#define MCAN_TX_EVENT_FIFO_MM_WIDTH             8U

#define MCAN_TX_EVENT_FIFO_ET_MASK              0xC00000U
#define MCAN_TX_EVENT_FIFO_ET_SHIFT             22U
#define MCAN_TX_EVENT_FIFO_ET_WIDTH             2U

#define MCAN_TX_EVENT_FIFO_FDF_MASK             0x200000U
#define MCAN_TX_EVENT_FIFO_FDF_SHIFT            21U
#define MCAN_TX_EVENT_FIFO_FDF_WIDTH            1U

#define MCAN_TX_EVENT_FIFO_BRS_MASK             0x100000U
#define MCAN_TX_EVENT_FIFO_BRS_SHIFT            20U
#define MCAN_TX_EVENT_FIFO_BRS_WIDTH            1U

#define MCAN_TX_EVENT_FIFO_DLC_MASK             0xF0000U
#define MCAN_TX_EVENT_FIFO_DLC_SHIFT            16U
#define MCAN_TX_EVENT_FIFO_DLC_WIDTH            4U

#define MCAN_TX_EVENT_FIFO_TXTS_MASK            0xFFFFU
#define MCAN_TX_EVENT_FIFO_TXTS_SHIFT           0U
#define MCAN_TX_EVENT_FIFO_TXTS_WIDTH           16U

/*rx Buffer and FIFO Element*/ 

#define MCAN_RX_BUFFER_ESI_MASK             0x80000000U
#define MCAN_RX_BUFFER_ESI_SHIFT            31U
#define MCAN_RX_BUFFER_ESI_WIDTH            1U

#define MCAN_RX_BUFFER_XTD_MASK             0x40000000U
#define MCAN_RX_BUFFER_XTD_SHIFT            30U
#define MCAN_RX_BUFFER_XTD_WIDTH            1U

#define MCAN_RX_BUFFER_RTR_MASK             0x20000000U
#define MCAN_RX_BUFFER_RTR_SHIFT            29U
#define MCAN_RX_BUFFER_RTR_WIDTH            1U

#define MCAN_RX_BUFFER_STD_ID_MASK          0x1FFC0000U
#define MCAN_RX_BUFFER_STD_ID_SHIFT         18U
#define MCAN_RX_BUFFER_STD_ID_WIDTH         11U

#define MCAN_RX_BUFFER_EXT_ID_MASK          0x1FFFFFFFU
#define MCAN_RX_BUFFER_EXT_ID_SHIFT         0U
#define MCAN_RX_BUFFER_EXT_ID_WIDTH         29U

#define MCAN_RX_BUFFER_ANMF_MASK            0x80000000U
#define MCAN_RX_BUFFER_ANMF_SHIFT           31U
#define MCAN_RX_BUFFER_ANMF_WIDTH           1U

#define MCAN_RX_BUFFER_FIDX_MASK            0x7F000000U
#define MCAN_RX_BUFFER_FIDX_SHIFT           24U
#define MCAN_RX_BUFFER_FIDX_WIDTH           7U

#define MCAN_RX_BUFFER_FDF_MASK            0x200000U
#define MCAN_RX_BUFFER_FDF_SHIFT           21U
#define MCAN_RX_BUFFER_FDF_WIDTH           1U

#define MCAN_RX_BUFFER_BRS_MASK            0x100000U
#define MCAN_RX_BUFFER_BRS_SHIFT           20U
#define MCAN_RX_BUFFER_BRS_WIDTH           1U

#define MCAN_RX_BUFFER_DLC_MASK            0xF0000U
#define MCAN_RX_BUFFER_DLC_SHIFT           16U
#define MCAN_RX_BUFFER_DLC_WIDTH           4U

#define MCAN_RX_BUFFER_RXTS_MASK            0xFFFFU
#define MCAN_RX_BUFFER_RXTS_SHIFT           0U
#define MCAN_RX_BUFFER_RXTS_WIDTH           16U

typedef P2FUNC(void, CAN_CODE, errorCallBack_Type)(VAR(uint8, AUTOMATIC) u8Can_ControllerId);
typedef P2FUNC(void, CAN_CODE, mrafCallBack_Type)(VAR(uint8, AUTOMATIC) u8Can_ControllerId);

typedef struct
{
    VAR(uint32, AUTOMATIC)                       RAM[FEATURE_MCAN_RAM_MESSAGES_WRD];
} RAM_MB;

/* CAN module ID */
typedef enum
{
    MCAN_MOD_ID_1,
    MCAN_MOD_ID_2,
    MCAN_MOD_ID_3,
    MCAN_MOD_ID_4,
    MCAN_MOD_ID_5,
    MCAN_MOD_ID_6,
    MCAN_MOD_ID_7,
    MCAN_MOD_ID_8,
    MCAN_MOD_ID_9,
    MCAN_MOD_ID_10,
    MCAN_MOD_ID_11,
    MCAN_MOD_ID_12,
    CAN_MOD_BUTT
} MCANModId;

typedef struct
{
    VAR(MCANModId, AUTOMATIC)                    instance;
    VAR(uint8, AUTOMATIC)                        controllerId;
}Controller_mapping;

typedef struct
{
    VAR(uint8, AUTOMATIC)                        CanId;
    VAR(boolean, AUTOMATIC)                      IsUsed;
    VAR(uint32, AUTOMATIC)                       BaseWord;
    VAR(uint32, AUTOMATIC)                       mram_size_words;
}McanControlInfor;

typedef struct
{
    P2VAR(McanControlInfor, AUTOMATIC,CAN_APPL_DATA) McanCtrl;
}MCANPartitionConfig;

typedef enum{
    MCAN_LOOPBACK_INTERNAL,
    MCAN_LOOPBACK_EXTERNAL
}loopback_mode;

typedef enum {
    MCAN_NORMAL_MODE,
    MCAN_LISTEN_ONLY_MODE,
    MCAN_LOOPBACK_MODE,
    MCAN_TEST_MODE,
    MCAN_DISABLE_MODE
}mcan_operation_modes_t;

typedef enum {
    MCAN_PAYLOAD_SIZE_8  ,
    MCAN_PAYLOAD_SIZE_12 ,
    MCAN_PAYLOAD_SIZE_16 ,
    MCAN_PAYLOAD_SIZE_20 ,
    MCAN_PAYLOAD_SIZE_24 ,
    MCAN_PAYLOAD_SIZE_32 ,
    MCAN_PAYLOAD_SIZE_48 ,
    MCAN_PAYLOAD_SIZE_64
}mcan_fd_payload_size_t;

typedef enum{
    MCAN_TX_BUFF,
    MCAN_RX_BUFF,
    MCAN_RX_FIFO0,
    MCAN_RX_FIFO1,
}mode_type_t;

typedef struct
{
    VAR(uint16, AUTOMATIC)                       brp;
    VAR(uint16, AUTOMATIC)                       prop_seg;
    VAR(uint16, AUTOMATIC)                       phase_seg1;
    VAR(uint16, AUTOMATIC)                       phase_seg2;
    VAR(uint16, AUTOMATIC)                       sjw;
    VAR(boolean, AUTOMATIC)                      tdc;
    VAR(uint16, AUTOMATIC)                       tdc_offset;
    VAR(uint16, AUTOMATIC)                       tdc_filter_window;
}bt_config_struct;

typedef struct
{
    VAR(uint16, AUTOMATIC)                       baudRateConfigId;
    VAR(bt_config_struct, AUTOMATIC)             nominal;
    VAR(bt_config_struct, AUTOMATIC)             data;
    VAR(boolean, AUTOMATIC)                      fd_ena;
    VAR(boolean, AUTOMATIC)                      brs_ena;
    VAR(boolean, AUTOMATIC)                      is_noiso;
}bt_config_canfd_struct;

typedef enum
{
  ACC_NON_MTCH_FRAMES_IN_RX_FIFO0 = 0x0,
  ACC_NON_MTCH_FRAMES_IN_RX_FIFO1 = 0x1,
  REJECT_NON_MATCHING_FRAMES             = 0x3
}GFC_accept_non_matching_frames_enum;

typedef struct
{
    VAR(GFC_accept_non_matching_frames_enum, AUTOMATIC) anfs;
    VAR(GFC_accept_non_matching_frames_enum, AUTOMATIC) anfe;
    VAR(boolean, AUTOMATIC)                             rrfs;
    VAR(boolean, AUTOMATIC)                             rrfe;
}mcan_global_filter_config_t;

typedef enum
{
    FILTER_TYPE_RANGE_ID,
    FILTER_TYPE_DUAL_ID,
    FILTER_TYPE_CLASIC,
    FILTER_TYPE_DISABLE
}filter_type;

typedef enum
{
    FILTER_CONF_DISABLE,
    FILTER_CONF_RX_FIFO0,
    FILTER_CONF_RX_FIFO1,
    FILTER_CONF_REJECT_ID,
    FILTER_CONF_SET_PRIO,
    FILTER_CONF_SET_PRIO_RX_FIFO0,
    FILTER_CONF_SET_PRIO_RX_FIFO1,
    FILTER_CONF_RX_BUFF
} filter_element_config_t;

typedef struct
{
    VAR(filter_type, AUTOMATIC)                  filterType;
    VAR(filter_element_config_t, AUTOMATIC)     filterConfig;
    VAR(boolean, AUTOMATIC)                      isExtendedFrame;
    VAR(uint32, AUTOMATIC)                       ssync;
    VAR(uint32, AUTOMATIC)                       esync;
    VAR(uint32, AUTOMATIC)                       id1;
    VAR(uint32, AUTOMATIC)                       id2;
}mcan_id_table_t;

typedef struct
{
    P2CONST(mcan_id_table_t, AUTOMATIC, CAN_APPL_CONST)    filterconfigs;
    VAR(uint8, AUTOMATIC)                                  std_filters;
    VAR(uint8, AUTOMATIC)                                  ext_filters;
}mcan_filter_config_t;

typedef enum
{
    MCAN_RXFIFO_DISABLED,
    MCAN_RXFIFO_0_ENABLE,
    MCAN_RXFIFO_1_ENABLE,
    MCAN_RXFIFO_0_1_ENABLE
}mcan_rxfifo_mode_t;

typedef enum
{
    FIFO_MODE_BLOCKING,
    FIFO_MODE_OVERWRITE
}fifo_op_mode_t;

typedef struct
{
    VAR(mcan_rxfifo_mode_t, AUTOMATIC)          rx_fifo_needed;
    VAR(fifo_op_mode_t, AUTOMATIC)              modeFIFO;
    VAR(uint8, AUTOMATIC)                       fifo_size_elems;
    VAR(uint8, AUTOMATIC)                       fifo_watermark;
    VAR(mcan_fd_payload_size_t, AUTOMATIC)      payload;
}mcan_fifo_config_t;

typedef struct
{
    VAR(uint8, AUTOMATIC)                        fifo_size_elems;
    VAR(uint8, AUTOMATIC)                        fifo_watermark;
}mcan_tx_event_fifo_config_t;

typedef struct
{
    VAR(uint8, AUTOMATIC)                        FIFO_true_QUEUE_false;
    VAR(uint8, AUTOMATIC)                        fifo_queue_size;
    VAR(uint8, AUTOMATIC)                        ded_buffers_number;
    VAR(mcan_fd_payload_size_t, AUTOMATIC)       payload;
}mcan_tx_buffer_config_t;

typedef struct
{
    VAR(uint8, AUTOMATIC)                        rx_buffer_size_elems;
    VAR(mcan_fd_payload_size_t, AUTOMATIC)       payload;
}mcan_dedicated_buffers_config_t;

typedef struct
{
    VAR(uint32, AUTOMATIC)                       ir_line0_select;
    VAR(uint32, AUTOMATIC)                       ir_line1_select;
    VAR(uint32, AUTOMATIC)                       tx_buffer_tran_ir_enable;
    VAR(uint32, AUTOMATIC)                       tx_buffer_cancel_fin_ir_enable;
}mcan_inter_config_t;

typedef enum {
    TSCC_TSS_TIMESTMP_CNTR_VALUE_ALWAYS_0         = 0x0,
    TSCC_TSS_TIMESTMP_CNTR_VALUE_ACCORDING_TO_TCP = 0x1,
    TSCC_TSS_TIMESTMP_CNTR_VALUE_EXTERNAL_USED    = 0x2
}tscc_tss_timestamp_select_enum;

typedef enum {
    TOCC_TOS_CONTINUOUS_OPERATION       = 0x0,
    TOCC_TOS_TMO_CNTRD_BY_TX_EVENT_FIFO = 0x1,
    TOCC_TOS_TMO_CNTRD_BY_RX_FIFO_0     = 0x2,
    TOCC_TOS_TMO_CNTRD_BY_RX_FIFO_1     = 0x3
}tocc_tos_timeout_select_enum;

typedef struct
{
    VAR(uint32, AUTOMATIC)                         ts_counter_prescaler;
    VAR(tscc_tss_timestamp_select_enum, AUTOMATIC) ts_select;
    VAR(tocc_tos_timeout_select_enum, AUTOMATIC)   to_select;
    VAR(uint16, AUTOMATIC)                         to_period;
    VAR(boolean, AUTOMATIC)                        to_counter_enable;
}mcan_timestamp_config_t;

typedef enum
{
    STANDARD_ID    = 0,
    EXTENDED_ID    = 1,
    STD_AND_EXT_ID = 2
} can_id_type_enum;

typedef enum
{
    TX_DIR = 0,
    RX_DIR = 1
} can_msg_dir_enum;

typedef enum
{
    FIFO_0              = 0,
    FIFO_1              = 1,
    DEDICATED_RX_BUFFER = 2
} rx_buffer_type_enum;

typedef struct
{
    VAR(rx_buffer_type_enum, AUTOMATIC)          rx_via;
    VAR(uint32, AUTOMATIC)                       buffer_index;
    VAR(uint32, AUTOMATIC)                       rx_timestamp;
} rx_info_struct;

typedef struct
{
    VAR(boolean, AUTOMATIC)                      remote;
    VAR(can_id_type_enum, AUTOMATIC)             idtype;
    VAR(uint32, AUTOMATIC)                       id;
    VAR(boolean, AUTOMATIC)                      fdf;
    VAR(boolean, AUTOMATIC)                      brs;
    VAR(boolean, AUTOMATIC)                      esi;
    VAR(uint16, AUTOMATIC)                       dlc;
    VAR(uint8, AUTOMATIC)                        data[CAN_FD_MAX_NO_OF_DTB_PER_FRAME];
    VAR(can_msg_dir_enum, AUTOMATIC)             direction;
    VAR(rx_info_struct, AUTOMATIC)               rx_info;
    VAR(boolean, AUTOMATIC)                      efc;
    VAR(uint8, AUTOMATIC)                        tx_tsce;
    VAR(uint8, AUTOMATIC)                        mm;
} can_msg_struct;

typedef enum
{
    RESERVED                               = 0,
    TX_EVENT                               = 1,
    transmission_in_spite_of_cancellation  = 2
} tx_event_fifo_elem_event_type_enum;

typedef struct
{
    VAR(boolean, AUTOMATIC)                            esi;
    VAR(can_id_type_enum, AUTOMATIC)                   idtype;
    VAR(boolean, AUTOMATIC)                            remote;
    VAR(uint32, AUTOMATIC)                             id;
    VAR(uint16, AUTOMATIC)                             mm;
    VAR(tx_event_fifo_elem_event_type_enum, AUTOMATIC) et;
    VAR(boolean, AUTOMATIC)                            fdf;
    VAR(boolean, AUTOMATIC)                            brs;
    VAR(uint16, AUTOMATIC)                             dlc;
    VAR(uint32, AUTOMATIC)                             tx_timestamp;
} tx_event_element_struct;/* PRQA S 1535 */

typedef enum {
    RECEIVE  = 0U,
    TRANSMIT = 1U
} Can_ObjectType;

typedef struct
{
    CONST(uint32, CAN_CONST)                     CanObjectId;
    CONST(uint32, CAN_CONST)                     CanControllerId;
    CONST(can_id_type_enum, CAN_CONST)           CanIdType;
    CONST(uint32, CAN_CONST)                     mbIdex;
    CONST(uint32, CAN_CONST)                     mbPayloadLength;
    CONST(uint8, CAN_CONST)                      isPolling;
    CONST(Can_ObjectType, CAN_CONST)             CanObjectType;
    CONST(uint8, CAN_CONST)                      CanFdPaddingValue;
    CONST(uint8, CAN_CONST)                      PeriodIndex;
    CONST(filter_type, AUTOMATIC)                filterType;
    CONST(uint32, AUTOMATIC)                     filterCode;
    CONST(uint32, AUTOMATIC)                     filterMask;
} mcan_hwObject;

typedef struct
{
    CONST(MCANModId, CAN_CONST)     controllerId;
    CONST(uint16, CAN_CONST)        defaultBaudRateId;
    CONST(uint16, CAN_CONST)        baudRateConfigCount;
    P2CONST(MCANPartitionConfig, CAN_CONST, CAN_APPL_CONST)              data;
    P2CONST(bt_config_canfd_struct, CAN_CONST, CAN_APPL_CONST)           timingconfig;
    P2CONST(mcan_global_filter_config_t, CAN_CONST, CAN_APPL_CONST)      globalfilterconfig;
    P2CONST(mcan_filter_config_t, CAN_CONST, CAN_APPL_CONST)             filterconfig;
    P2CONST(mcan_fifo_config_t, CAN_CONST, CAN_APPL_CONST)               rxfifoconfig;
    P2CONST(mcan_tx_event_fifo_config_t, CAN_CONST, CAN_APPL_CONST)      txeventconfig;
    P2CONST(mcan_tx_buffer_config_t, CAN_CONST, CAN_APPL_CONST)          txbufferconfig;
    P2CONST(mcan_dedicated_buffers_config_t, CAN_CONST, CAN_APPL_CONST)  rxbufferconfig;
    P2CONST(mcan_inter_config_t, CAN_CONST, CAN_APPL_CONST)              interconfig;
    P2CONST(mcan_timestamp_config_t, CAN_CONST, CAN_APPL_CONST)          stampconfig;
    CONST(mcan_operation_modes_t, CAN_CONST)                             mcanMode;
    CONST(mrafCallBack_Type, CAN_CONST)                                  MRAFNotification;
    CONST(errorCallBack_Type, CAN_CONST)                                 ErrorNotification;
} CANConfig;

typedef struct
{
    CONST(MCANModId, CAN_CONST)     controllerId;
    CONST(uint32, CAN_CONST)        CoreId;
} mcan_core_map_t;

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(status_t, CAN_CODE) Can_LLD_Init \
( \
    VAR(uint8, AUTOMATIC) u8Can_ControllerId, \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(CANConfig, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_Deint(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxIsEnableTranPause \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Enable \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxIsEnableDar \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Enable \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_EnterSleepStatus(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_WakeUp(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_SetExtendIDMask \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Mask \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxMsgScanSend \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Mask \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxSendDedicatedMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buffer_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxSendFifoQueueMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(can_msg_struct, AUTOMATIC, CAN_APPL_CONST) pCan_Tx_msg_ptr \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_TxFifoGetNumOfFreeElems(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_TxSendRequestCancel \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buf_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_TxSendReqCancelFinshed \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint8, CAN_VAR) u8Can_Tx_buf_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_TxTranOccured \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Tx_buf_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_RxDedicateBufProcNewMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint32, CAN_CODE) Can_LLD_RxRecFifoMsg \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Rx_fifo_number \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_IsDataLost \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Rx_fifo_number \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_InterDisableAllSignals(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_InterruptInit \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    P2CONST(mcan_inter_config_t, AUTOMATIC, CAN_APPL_CONST) pCan_Config \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_IsBusOff(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_IsErrorActive(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_GetRxErrorCounter(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_GetTxErrorCounter(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(uint8, CAN_CODE) Can_LLD_IsFDEnabled(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isInitState(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isSleep(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_SetTimeOut(VAR(uint32, CAN_VAR) u32Can_TimeOutDuration);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(void, CAN_CODE) Can_LLD_RsetInit(VAR(MCANModId, AUTOMATIC) eCan_Instance);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
FUNC(boolean, CAN_CODE) Can_LLD_isTxInterruptMb \
( \
    VAR(MCANModId, AUTOMATIC) eCan_Instance, \
    VAR(uint32, CAN_VAR) u32Can_Tx_buf_index \
);
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif
