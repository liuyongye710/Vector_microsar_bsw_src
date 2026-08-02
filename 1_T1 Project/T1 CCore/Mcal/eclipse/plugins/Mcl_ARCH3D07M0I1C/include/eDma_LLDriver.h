/**************************************************************************** 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : eDma
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
*   @file    eDma_LLDriver.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of eDma MCAL driver.
*
*   @addtogroup eDma
*   @{
*/

#ifndef EDMA_LLDRIVER_H_
#define EDMA_LLDRIVER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "derivative.h"
#include "typedefs.h"
#include "status.h"
#include "eDma_Cfg.h"
#include "eDma_Irq.h"

/* PRQA S 1534 EOF */
/* PRQA S 3472 EOF */
/* PRQA S 3630 EOF */

#define EDMA_LLD_H_VENDOR_ID                     176
#define EDMA_LLD_H_AR_REL_MAJOR_VER              4
#define EDMA_LLD_H_AR_REL_MINOR_VER              4
#define EDMA_LLD_H_AR_REL_REV_VER                0
#define EDMA_LLD_H_SW_MAJOR_VER                  3
#define EDMA_LLD_H_SW_MINOR_VER                  0
#define EDMA_LLD_H_SW_PATCH_VER                  0

#if (EDMA_CFG_H_VENDOR_ID != EDMA_LLD_H_VENDOR_ID)
    #error " NON-MATCHED DATA : EDMA_LLD_H_VENDOR_ID "
#endif
#if (EDMA_CFG_H_AR_REL_MAJOR_VER != EDMA_LLD_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_AR_REL_MAJOR_VER "
#endif
#if (EDMA_CFG_H_AR_REL_MINOR_VER != EDMA_LLD_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_AR_REL_MINOR_VER "
#endif
#if (EDMA_CFG_H_AR_REL_REV_VER != EDMA_LLD_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_AR_REL_REV_VER "
#endif
#if (EDMA_CFG_H_SW_MAJOR_VER != EDMA_LLD_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_SW_MAJOR_VER "
#endif
#if (EDMA_CFG_H_SW_MINOR_VER != EDMA_LLD_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_SW_MINOR_VER "
#endif
#if (EDMA_CFG_H_SW_PATCH_VER != EDMA_LLD_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : EDMA_LLD_H_SW_PATCH_VER "
#endif

#define EDMA_DEV_ERR(x)                         DEV_ASSERT(x)

#define EDMA_CH0_CH127_INT                      (1U)
#define EDMA_CH0_CH127_ERROR_INT                (1U)
#define EDMA_ERROR_INTERRUPT_LINES              (1U)

#define MODULES_EDMA_CHANNELS                   (64U)
#define EDMA_MAPPED_CHN_INTERRUPT_LINES         ((uint32)128U)

#define EDMA_TOTAL_CHANNELS                     (MODULES_EDMA_CHANNELS * EDMA_INSTANCE_COUNT)

#define TCD_SIZE_CALC(number)                   (((number) * 32U) - 1U)
#define TCD_ADDR_CALC(address)                  (((uint32)(address) + 31UL) & ~0x1FUL)

/* Physical channel number for channel configuration #0 - #127*/
#define EDMA_CHN0_NUMBER        (0U)
#define EDMA_CHN1_NUMBER        (1U)
#define EDMA_CHN2_NUMBER        (2U)
#define EDMA_CHN3_NUMBER        (3U)
#define EDMA_CHN4_NUMBER        (4U)
#define EDMA_CHN5_NUMBER        (5U)
#define EDMA_CHN6_NUMBER        (6U)
#define EDMA_CHN7_NUMBER        (7U)
#define EDMA_CHN8_NUMBER        (8U)
#define EDMA_CHN9_NUMBER        (9U)
#define EDMA_CHN10_NUMBER       (10U)
#define EDMA_CHN11_NUMBER       (11U)
#define EDMA_CHN12_NUMBER       (12U)
#define EDMA_CHN13_NUMBER       (13U)
#define EDMA_CHN14_NUMBER       (14U)
#define EDMA_CHN15_NUMBER       (15U)
#define EDMA_CHN16_NUMBER       (16U)
#define EDMA_CHN17_NUMBER       (17U)
#define EDMA_CHN18_NUMBER       (18U)
#define EDMA_CHN19_NUMBER       (19U)
#define EDMA_CHN20_NUMBER       (20U)
#define EDMA_CHN21_NUMBER       (21U)
#define EDMA_CHN22_NUMBER       (22U)
#define EDMA_CHN23_NUMBER       (23U)
#define EDMA_CHN24_NUMBER       (24U)
#define EDMA_CHN25_NUMBER       (25U)
#define EDMA_CHN26_NUMBER       (26U)
#define EDMA_CHN27_NUMBER       (27U)
#define EDMA_CHN28_NUMBER       (28U)
#define EDMA_CHN29_NUMBER       (29U)
#define EDMA_CHN30_NUMBER       (30U)
#define EDMA_CHN31_NUMBER       (31U)
#define EDMA_CHN32_NUMBER       (32U)
#define EDMA_CHN33_NUMBER       (33U)
#define EDMA_CHN34_NUMBER       (34U)
#define EDMA_CHN35_NUMBER       (35U)
#define EDMA_CHN36_NUMBER       (36U)
#define EDMA_CHN37_NUMBER       (37U)
#define EDMA_CHN38_NUMBER       (38U)
#define EDMA_CHN39_NUMBER       (39U)
#define EDMA_CHN40_NUMBER       (40U)
#define EDMA_CHN41_NUMBER       (41U)
#define EDMA_CHN42_NUMBER       (42U)
#define EDMA_CHN43_NUMBER       (43U)
#define EDMA_CHN44_NUMBER       (44U)
#define EDMA_CHN45_NUMBER       (45U)
#define EDMA_CHN46_NUMBER       (46U)
#define EDMA_CHN47_NUMBER       (47U)
#define EDMA_CHN48_NUMBER       (48U)
#define EDMA_CHN49_NUMBER       (49U)
#define EDMA_CHN50_NUMBER       (50U)
#define EDMA_CHN51_NUMBER       (51U)
#define EDMA_CHN52_NUMBER       (52U)
#define EDMA_CHN53_NUMBER       (53U)
#define EDMA_CHN54_NUMBER       (54U)
#define EDMA_CHN55_NUMBER       (55U)
#define EDMA_CHN56_NUMBER       (56U)
#define EDMA_CHN57_NUMBER       (57U)
#define EDMA_CHN58_NUMBER       (58U)
#define EDMA_CHN59_NUMBER       (59U)
#define EDMA_CHN60_NUMBER       (60U)
#define EDMA_CHN61_NUMBER       (61U)
#define EDMA_CHN62_NUMBER       (62U)
#define EDMA_CHN63_NUMBER       (63U)
#define EDMA_CHN64_NUMBER       (64U)
#define EDMA_CHN65_NUMBER       (65U)
#define EDMA_CHN66_NUMBER       (66U)
#define EDMA_CHN67_NUMBER       (67U)
#define EDMA_CHN68_NUMBER       (68U)
#define EDMA_CHN69_NUMBER       (69U)
#define EDMA_CHN70_NUMBER       (70U)
#define EDMA_CHN71_NUMBER       (71U)
#define EDMA_CHN72_NUMBER       (72U)
#define EDMA_CHN73_NUMBER       (73U)
#define EDMA_CHN74_NUMBER       (74U)
#define EDMA_CHN75_NUMBER       (75U)
#define EDMA_CHN76_NUMBER       (76U)
#define EDMA_CHN77_NUMBER       (77U)
#define EDMA_CHN78_NUMBER       (78U)
#define EDMA_CHN79_NUMBER       (79U)
#define EDMA_CHN80_NUMBER       (80U)
#define EDMA_CHN81_NUMBER       (81U)
#define EDMA_CHN82_NUMBER       (82U)
#define EDMA_CHN83_NUMBER       (83U)
#define EDMA_CHN84_NUMBER       (84U)
#define EDMA_CHN85_NUMBER       (85U)
#define EDMA_CHN86_NUMBER       (86U)
#define EDMA_CHN87_NUMBER       (87U)
#define EDMA_CHN88_NUMBER       (88U)
#define EDMA_CHN89_NUMBER       (89U)
#define EDMA_CHN90_NUMBER       (90U)
#define EDMA_CHN91_NUMBER       (91U)
#define EDMA_CHN92_NUMBER       (92U)
#define EDMA_CHN93_NUMBER       (93U)
#define EDMA_CHN94_NUMBER       (94U)
#define EDMA_CHN95_NUMBER       (95U)
#define EDMA_CHN96_NUMBER       (96U)
#define EDMA_CHN97_NUMBER       (97U)
#define EDMA_CHN98_NUMBER       (98U)
#define EDMA_CHN99_NUMBER       (99U)
#define EDMA_CHN100_NUMBER      (100U)
#define EDMA_CHN101_NUMBER      (101U)
#define EDMA_CHN102_NUMBER      (102U)
#define EDMA_CHN103_NUMBER      (103U)
#define EDMA_CHN104_NUMBER      (104U)
#define EDMA_CHN105_NUMBER      (105U)
#define EDMA_CHN106_NUMBER      (106U)
#define EDMA_CHN107_NUMBER      (107U)
#define EDMA_CHN108_NUMBER      (108U)
#define EDMA_CHN109_NUMBER      (109U)
#define EDMA_CHN110_NUMBER      (110U)
#define EDMA_CHN111_NUMBER      (111U)
#define EDMA_CHN112_NUMBER      (112U)
#define EDMA_CHN113_NUMBER      (113U)
#define EDMA_CHN114_NUMBER      (114U)
#define EDMA_CHN115_NUMBER      (115U)
#define EDMA_CHN116_NUMBER      (116U)
#define EDMA_CHN117_NUMBER      (117U)
#define EDMA_CHN118_NUMBER      (118U)
#define EDMA_CHN119_NUMBER      (119U)
#define EDMA_CHN120_NUMBER      (120U)
#define EDMA_CHN121_NUMBER      (121U)
#define EDMA_CHN122_NUMBER      (122U)
#define EDMA_CHN123_NUMBER      (123U)
#define EDMA_CHN124_NUMBER      (124U)
#define EDMA_CHN125_NUMBER      (125U)
#define EDMA_CHN126_NUMBER      (126U)
#define EDMA_CHN127_NUMBER      (127U)

#define DMAMUX_AVAILABLE
#define DMAMUX_HAS_TRIG

#define DMAMUX_CHANNELS                         (16U)
#define DMAMUX_SOURCE_NUMS                      (64UL)

#define DMAMUX_CHN_REG_INDEX(x)                 (x)
#define DMAMUX_CHCFG_ENBL(x)                    (uint8)((uint32)(x) << DMAMUX_CHCFG_ENBL_SHIFT)
#define DMAMUX_CHCFG_TRIG(x)                    (uint8)((uint32)(x) << DMAMUX_CHCFG_TRIG_SHIFT)
#define DMAMUX_CHCFG_SOURCE(x)                  ((x) << DMAMUX_CHCFG_SOURCE_SHIFT)

#define DMAMUX_CH_WIDTH                         (6UL)
#define DMAMUX_REQ_SRC_TO_INSTANCE(x)           ((x) >> (uint32)DMAMUX_CH_WIDTH)
#define DMAMUX_REQ_SRC_TO_CH(x)                 ((x) & ((uint32)DMAMUX_SOURCE_NUMS - 1UL))
#define DMAMUX_DMA_CH_TO_CH(x)                  (((x) < 32U)?((x) & (0x7U)):((x) & (15U)))

#define EDMA_CHANNELS                           (64UL)
#define EDMA_CH_WIDTH                           (6U)
#define EDMA_MCH_TO_INSTANCE(x)                 ((x) >> EDMA_CH_WIDTH)
#define EDMA_MCH_TO_CH(x)                       ((x) & ((uint32)EDMA_CHANNELS - 1UL))
#define EDMA_CHN_TO_DCHPRI_INDEX(x)             (x)
#define EDMA_INSTANCE_COUNT                     (2UL)
#define EDMA_MAPPED_CHANNELS                    (EDMA_CHANNELS * EDMA_INSTANCE_COUNT)

typedef volatile struct eDMA_tag  DMA_Type;

#define DMA_0_BASE                              (0xFC0A0000UL)
#define DMA_0_P                                 ((DMA_Type *)DMA_0_BASE)
#define DMA_1_BASE                              (0xFC0A4000UL)
#define DMA_1_P                                 ((DMA_Type *)DMA_1_BASE)
#define DMA_BASE_ADDRS                          { DMA_0_BASE, DMA_1_BASE }
#define DMA_BASE_PTRS                           { DMA_0_P, DMA_1_P }
#define DMA_CHN_IRQS                            { DMA0_CH0_IRQ53,   DMA0_CH1_IRQ54,   \
                                                  DMA0_CH2_IRQ55,   DMA0_CH3_IRQ56,   \
                                                  DMA0_CH4_IRQ57,   DMA0_CH5_IRQ58,   \
                                                  DMA0_CH6_IRQ59,   DMA0_CH7_IRQ60,   \
                                                  DMA0_CH8_IRQ61,   DMA0_CH9_IRQ62,   \
                                                  DMA0_CH10_IRQ63,  DMA0_CH11_IRQ64,  \
                                                  DMA0_CH12_IRQ65,  DMA0_CH13_IRQ66,  \
                                                  DMA0_CH14_IRQ67,  DMA0_CH15_IRQ68,  \
                                                  DMA0_CH16_IRQ69,  DMA0_CH17_IRQ70,  \
                                                  DMA0_CH18_IRQ71,  DMA0_CH19_IRQ72,  \
                                                  DMA0_CH20_IRQ73,  DMA0_CH21_IRQ74,  \
                                                  DMA0_CH22_IRQ75,  DMA0_CH23_IRQ76,  \
                                                  DMA0_CH24_IRQ77,  DMA0_CH25_IRQ78,  \
                                                  DMA0_CH26_IRQ79,  DMA0_CH27_IRQ80,  \
                                                  DMA0_CH28_IRQ81,  DMA0_CH29_IRQ82,  \
                                                  DMA0_CH30_IRQ83,  DMA0_CH31_IRQ84,  \
                                                  DMA0_CH32_IRQ85,  DMA0_CH33_IRQ86,  \
                                                  DMA0_CH34_IRQ87,  DMA0_CH35_IRQ88,  \
                                                  DMA0_CH36_IRQ89,  DMA0_CH37_IRQ90,  \
                                                  DMA0_CH38_IRQ91,  DMA0_CH39_IRQ92,  \
                                                  DMA0_CH40_IRQ93,  DMA0_CH41_IRQ94,  \
                                                  DMA0_CH42_IRQ95,  DMA0_CH43_IRQ96,  \
                                                  DMA0_CH44_IRQ97,  DMA0_CH45_IRQ98,  \
                                                  DMA0_CH46_IRQ99,  DMA0_CH47_IRQ100, \
                                                  DMA0_CH48_IRQ101, DMA0_CH49_IRQ102, \
                                                  DMA0_CH50_IRQ103, DMA0_CH51_IRQ104, \
                                                  DMA0_CH52_IRQ105, DMA0_CH53_IRQ106, \
                                                  DMA0_CH54_IRQ107, DMA0_CH55_IRQ108, \
                                                  DMA0_CH56_IRQ109, DMA0_CH57_IRQ110, \
                                                  DMA0_CH58_IRQ111, DMA0_CH59_IRQ112, \
                                                  DMA0_CH60_IRQ113, DMA0_CH61_IRQ114, \
                                                  DMA0_CH62_IRQ115, DMA0_CH63_IRQ116, \
                                                  DMA1_CH0_IRQ117,  DMA1_CH1_IRQ118,  \
                                                  DMA1_CH2_IRQ119,  DMA1_CH3_IRQ120,  \
                                                  DMA1_CH4_IRQ121,  DMA1_CH5_IRQ122,  \
                                                  DMA1_CH6_IRQ123,  DMA1_CH7_IRQ124,  \
                                                  DMA1_CH8_IRQ125,  DMA1_CH9_IRQ126,  \
                                                  DMA1_CH10_IRQ127, DMA1_CH11_IRQ128, \
                                                  DMA1_CH12_IRQ129, DMA1_CH13_IRQ130, \
                                                  DMA1_CH14_IRQ131, DMA1_CH15_IRQ132, \
                                                  DMA1_CH16_IRQ133, DMA1_CH17_IRQ134, \
                                                  DMA1_CH18_IRQ135, DMA1_CH19_IRQ136, \
                                                  DMA1_CH20_IRQ137, DMA1_CH21_IRQ138, \
                                                  DMA1_CH22_IRQ139, DMA1_CH23_IRQ140, \
                                                  DMA1_CH24_IRQ141, DMA1_CH25_IRQ142, \
                                                  DMA1_CH26_IRQ143, DMA1_CH27_IRQ144, \
                                                  DMA1_CH28_IRQ145, DMA1_CH29_IRQ146, \
                                                  DMA1_CH30_IRQ147, DMA1_CH31_IRQ148, \
                                                  DMA1_CH32_IRQ149, DMA1_CH33_IRQ150, \
                                                  DMA1_CH34_IRQ151, DMA1_CH35_IRQ152, \
                                                  DMA1_CH36_IRQ153, DMA1_CH37_IRQ154, \
                                                  DMA1_CH38_IRQ155, DMA1_CH39_IRQ156, \
                                                  DMA1_CH40_IRQ157, DMA1_CH41_IRQ158, \
                                                  DMA1_CH42_IRQ159, DMA1_CH43_IRQ160, \
                                                  DMA1_CH44_IRQ161, DMA1_CH45_IRQ162, \
                                                  DMA1_CH46_IRQ163, DMA1_CH47_IRQ164, \
                                                  DMA1_CH48_IRQ165, DMA1_CH49_IRQ166, \
                                                  DMA1_CH50_IRQ167, DMA1_CH51_IRQ168, \
                                                  DMA1_CH52_IRQ169, DMA1_CH53_IRQ170, \
                                                  DMA1_CH54_IRQ171, DMA1_CH55_IRQ172, \
                                                  DMA1_CH56_IRQ173, DMA1_CH57_IRQ174, \
                                                  DMA1_CH58_IRQ175, DMA1_CH59_IRQ176, \
                                                  DMA1_CH60_IRQ177, DMA1_CH61_IRQ178, \
                                                  DMA1_CH62_IRQ179, DMA1_CH63_IRQ180  }
#define DMA_ERROR_IRQS                          { DMA0_ERR0_127_IRQ52 }

/*----------------------------------------------------------------------------
 -- DMA  Masks
 ---------------------------------------------------------------------------- */

#define DMA_CR_EDBG_MASK                        0x2UL
#define DMA_CR_EDBG_SHIFT                       1u
#define DMA_CR_EDBG_WIDTH                       1u
#define DMA_CR_EDBG(x)                          (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_EDBG_SHIFT)) \
                                                    &DMA_CR_EDBG_MASK)
#define DMA_CR_ERCA_MASK                        0x4UL
#define DMA_CR_ERCA_SHIFT                       2u
#define DMA_CR_ERCA_WIDTH                       1u
#define DMA_CR_ERCA(x)                          (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_ERCA_SHIFT)) \
                                                  &DMA_CR_ERCA_MASK)
#define DMA_CR_ERGA_MASK                        0x8UL
#define DMA_CR_ERGA_SHIFT                       3u
#define DMA_CR_ERGA_WIDTH                       1u
#define DMA_CR_ERGA(x)                          (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_ERGA_SHIFT)) \
                                                  &DMA_CR_ERGA_MASK)
#define DMA_CR_HOE_MASK                         0x10UL
#define DMA_CR_HOE_SHIFT                        4u
#define DMA_CR_HOE_WIDTH                        1u
#define DMA_CR_HOE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_HOE_SHIFT)) \
                                                  &DMA_CR_HOE_MASK)
#define DMA_CR_HALT_MASK                        0x20u
#define DMA_CR_HALT_SHIFT                       5u
#define DMA_CR_HALT_WIDTH                       1u
#define DMA_CR_HALT(x)                          (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_HALT_SHIFT)) \
                                                  &DMA_CR_HALT_MASK)
#define DMA_CR_CLM_MASK                         0x40UL
#define DMA_CR_CLM_SHIFT                        6u
#define DMA_CR_CLM_WIDTH                        1u
#define DMA_CR_CLM(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_CLM_SHIFT)) \
                                                  &DMA_CR_CLM_MASK)
#define DMA_CR_EMLM_MASK                        0x80UL
#define DMA_CR_EMLM_SHIFT                       7u
#define DMA_CR_EMLM_WIDTH                       1u
#define DMA_CR_EMLM(x)                          (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_EMLM_SHIFT)) \
                                                  &DMA_CR_EMLM_MASK)
#define DMA_CR_GRP0PRI_MASK                     0x300u
#define DMA_CR_GRP0PRI_SHIFT                    8u
#define DMA_CR_GRP0PRI_WIDTH                    2u
#define DMA_CR_GRP0PRI(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_GRP0PRI_SHIFT)) \
                                                  &DMA_CR_GRP0PRI_MASK)
#define DMA_CR_GRP1PRI_MASK                     0xC00u
#define DMA_CR_GRP1PRI_SHIFT                    10u
#define DMA_CR_GRP1PRI_WIDTH                    2u
#define DMA_CR_GRP1PRI(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_GRP1PRI_SHIFT)) \
                                                  &DMA_CR_GRP1PRI_MASK)
#define DMA_CR_GRP2PRI_MASK                     0x3000u
#define DMA_CR_GRP2PRI_SHIFT                    12u
#define DMA_CR_GRP2PRI_WIDTH                    2u
#define DMA_CR_GRP2PRI(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_GRP2PRI_SHIFT)) \
                                                  &DMA_CR_GRP2PRI_MASK)
#define DMA_CR_GRP3PRI_MASK                     0xC000u
#define DMA_CR_GRP3PRI_SHIFT                    14u
#define DMA_CR_GRP3PRI_WIDTH                    2u
#define DMA_CR_GRP3PRI(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_GRP3PRI_SHIFT)) \
                                                  &DMA_CR_GRP3PRI_MASK)
#define DMA_CR_ECX_MASK                         0x10000UL
#define DMA_CR_ECX_SHIFT                        16u
#define DMA_CR_ECX_WIDTH                        1u
#define DMA_CR_ECX(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_ECX_SHIFT)) \
                                                  &DMA_CR_ECX_MASK)
#define DMA_CR_CX_MASK                          0x20000UL
#define DMA_CR_CX_SHIFT                         17u
#define DMA_CR_CX_WIDTH                         1u
#define DMA_CR_CX(x)                            (((uint32)(((uint32)(x)) \
                                                  << DMA_CR_CX_SHIFT)) \
                                                  &DMA_CR_CX_MASK)
/* ES Bit Fields */
#define DMA_ES_DBE_MASK                         0x1u
#define DMA_ES_DBE_SHIFT                        0u
#define DMA_ES_DBE_WIDTH                        1u
#define DMA_ES_DBE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_DBE_SHIFT)) \
                                                  &DMA_ES_DBE_MASK)
#define DMA_ES_SBE_MASK                         0x2u
#define DMA_ES_SBE_SHIFT                        1u
#define DMA_ES_SBE_WIDTH                        1u
#define DMA_ES_SBE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_SBE_SHIFT)) \
                                                  &DMA_ES_SBE_MASK)
#define DMA_ES_SGE_MASK                         0x4u
#define DMA_ES_SGE_SHIFT                        2u
#define DMA_ES_SGE_WIDTH                        1u
#define DMA_ES_SGE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_SGE_SHIFT)) \
                                                  &DMA_ES_SGE_MASK)
#define DMA_ES_NCE_MASK                         0x8u
#define DMA_ES_NCE_SHIFT                        3u
#define DMA_ES_NCE_WIDTH                        1u
#define DMA_ES_NCE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_NCE_SHIFT)) \
                                                  &DMA_ES_NCE_MASK)
#define DMA_ES_DOE_MASK                         0x10u
#define DMA_ES_DOE_SHIFT                        4u
#define DMA_ES_DOE_WIDTH                        1u
#define DMA_ES_DOE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_DOE_SHIFT)) \
                                                  &DMA_ES_DOE_MASK)
#define DMA_ES_DAE_MASK                         0x20u
#define DMA_ES_DAE_SHIFT                        5u
#define DMA_ES_DAE_WIDTH                        1u
#define DMA_ES_DAE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_DAE_SHIFT)) \
                                                  &DMA_ES_DAE_MASK)
#define DMA_ES_SOE_MASK                         0x40u
#define DMA_ES_SOE_SHIFT                        6u
#define DMA_ES_SOE_WIDTH                        1u
#define DMA_ES_SOE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_SOE_SHIFT)) \
                                                  &DMA_ES_SOE_MASK)
#define DMA_ES_SAE_MASK                         0x80u
#define DMA_ES_SAE_SHIFT                        7u
#define DMA_ES_SAE_WIDTH                        1u
#define DMA_ES_SAE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_SAE_SHIFT)) \
                                                  &DMA_ES_SAE_MASK)
#define DMA_ES_ERRCHN_MASK                      0x3F00u
#define DMA_ES_ERRCHN_SHIFT                     8u
#define DMA_ES_ERRCHN_WIDTH                     6u
#define DMA_ES_ERRCHN(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_ERRCHN_SHIFT)) \
                                                  &DMA_ES_ERRCHN_MASK)
#define DMA_ES_CPE_MASK                         0x4000u
#define DMA_ES_CPE_SHIFT                        14u
#define DMA_ES_CPE_WIDTH                        1u
#define DMA_ES_CPE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_CPE_SHIFT)) \
                                                  &DMA_ES_CPE_MASK)
#define DMA_ES_GPE_MASK                         0x8000u
#define DMA_ES_GPE_SHIFT                        15u
#define DMA_ES_GPE_WIDTH                        1u
#define DMA_ES_GPE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_GPE_SHIFT)) \
                                                  &DMA_ES_GPE_MASK)
#define DMA_ES_ECX_MASK                         0x10000u
#define DMA_ES_ECX_SHIFT                        16u
#define DMA_ES_ECX_WIDTH                        1u
#define DMA_ES_ECX(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_ECX_SHIFT)) \
                                                  &DMA_ES_ECX_MASK)
#define DMA_ES_UCE_MASK                         0x20000u
#define DMA_ES_UCE_SHIFT                        17u
#define DMA_ES_UCE_WIDTH                        1u
#define DMA_ES_UCE(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_UCE_SHIFT)) \
                                                  &DMA_ES_UCE_MASK)
#define DMA_ES_VLD_MASK                         0x80000000u
#define DMA_ES_VLD_SHIFT                        31u
#define DMA_ES_VLD_WIDTH                        1u
#define DMA_ES_VLD(x)                           (((uint32)(((uint32)(x)) \
                                                  << DMA_ES_VLD_SHIFT)) \
                                                  &DMA_ES_VLD_MASK)
/* ERQH Bit Fields */
#define DMA_ERQH_ERQ32_MASK                     0x1u
#define DMA_ERQH_ERQ32_SHIFT                    0u
#define DMA_ERQH_ERQ32_WIDTH                    1u
#define DMA_ERQH_ERQ32(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ32_SHIFT)) \
                                                  &DMA_ERQH_ERQ32_MASK)
#define DMA_ERQH_ERQ33_MASK                     0x2u
#define DMA_ERQH_ERQ33_SHIFT                    1u
#define DMA_ERQH_ERQ33_WIDTH                    1u
#define DMA_ERQH_ERQ33(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ33_SHIFT)) \
                                                  &DMA_ERQH_ERQ33_MASK)
#define DMA_ERQH_ERQ34_MASK                     0x4u
#define DMA_ERQH_ERQ34_SHIFT                    2u
#define DMA_ERQH_ERQ34_WIDTH                    1u
#define DMA_ERQH_ERQ34(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ34_SHIFT)) \
                                                  &DMA_ERQH_ERQ34_MASK)
#define DMA_ERQH_ERQ35_MASK                     0x8u
#define DMA_ERQH_ERQ35_SHIFT                    3u
#define DMA_ERQH_ERQ35_WIDTH                    1u
#define DMA_ERQH_ERQ35(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ35_SHIFT)) \
                                                  &DMA_ERQH_ERQ35_MASK)
#define DMA_ERQH_ERQ36_MASK                     0x10u
#define DMA_ERQH_ERQ36_SHIFT                    4u
#define DMA_ERQH_ERQ36_WIDTH                    1u
#define DMA_ERQH_ERQ36(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ36_SHIFT)) \
                                                  &DMA_ERQH_ERQ36_MASK)
#define DMA_ERQH_ERQ37_MASK                     0x20u
#define DMA_ERQH_ERQ37_SHIFT                    5u
#define DMA_ERQH_ERQ37_WIDTH                    1u
#define DMA_ERQH_ERQ37(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ37_SHIFT)) \
                                                  &DMA_ERQH_ERQ37_MASK)
#define DMA_ERQH_ERQ38_MASK                     0x40u
#define DMA_ERQH_ERQ38_SHIFT                    6u
#define DMA_ERQH_ERQ38_WIDTH                    1u
#define DMA_ERQH_ERQ38(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ38_SHIFT)) \
                                                  &DMA_ERQH_ERQ38_MASK)
#define DMA_ERQH_ERQ39_MASK                     0x80u
#define DMA_ERQH_ERQ39_SHIFT                    7u
#define DMA_ERQH_ERQ39_WIDTH                    1u
#define DMA_ERQH_ERQ39(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ39_SHIFT)) \
                                                  &DMA_ERQH_ERQ39_MASK)
#define DMA_ERQH_ERQ40_MASK                     0x100u
#define DMA_ERQH_ERQ40_SHIFT                    8u
#define DMA_ERQH_ERQ40_WIDTH                    1u
#define DMA_ERQH_ERQ40(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ40_SHIFT)) \
                                                  &DMA_ERQH_ERQ40_MASK)
#define DMA_ERQH_ERQ41_MASK                     0x200u
#define DMA_ERQH_ERQ41_SHIFT                    9u
#define DMA_ERQH_ERQ41_WIDTH                    1u
#define DMA_ERQH_ERQ41(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ41_SHIFT)) \
                                                  &DMA_ERQH_ERQ41_MASK)
#define DMA_ERQH_ERQ42_MASK                     0x400u
#define DMA_ERQH_ERQ42_SHIFT                    10u
#define DMA_ERQH_ERQ42_WIDTH                    1u
#define DMA_ERQH_ERQ42(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ42_SHIFT)) \
                                                  &DMA_ERQH_ERQ42_MASK)
#define DMA_ERQH_ERQ43_MASK                     0x800u
#define DMA_ERQH_ERQ43_SHIFT                    11u
#define DMA_ERQH_ERQ43_WIDTH                    1u
#define DMA_ERQH_ERQ43(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ43_SHIFT)) \
                                                  &DMA_ERQH_ERQ43_MASK)
#define DMA_ERQH_ERQ44_MASK                     0x1000u
#define DMA_ERQH_ERQ44_SHIFT                    12u
#define DMA_ERQH_ERQ44_WIDTH                    1u
#define DMA_ERQH_ERQ44(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ44_SHIFT)) \
                                                  &DMA_ERQH_ERQ44_MASK)
#define DMA_ERQH_ERQ45_MASK                     0x2000u
#define DMA_ERQH_ERQ45_SHIFT                    13u
#define DMA_ERQH_ERQ45_WIDTH                    1u
#define DMA_ERQH_ERQ45(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ45_SHIFT)) \
                                                  &DMA_ERQH_ERQ45_MASK)
#define DMA_ERQH_ERQ46_MASK                     0x4000u
#define DMA_ERQH_ERQ46_SHIFT                    14u
#define DMA_ERQH_ERQ46_WIDTH                    1u
#define DMA_ERQH_ERQ46(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ46_SHIFT)) \
                                                  &DMA_ERQH_ERQ46_MASK)
#define DMA_ERQH_ERQ47_MASK                     0x8000u
#define DMA_ERQH_ERQ47_SHIFT                    15u
#define DMA_ERQH_ERQ47_WIDTH                    1u
#define DMA_ERQH_ERQ47(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ47_SHIFT)) \
                                                  &DMA_ERQH_ERQ47_MASK)
#define DMA_ERQH_ERQ48_MASK                     0x10000u
#define DMA_ERQH_ERQ48_SHIFT                    16u
#define DMA_ERQH_ERQ48_WIDTH                    1u
#define DMA_ERQH_ERQ48(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ48_SHIFT)) \
                                                  &DMA_ERQH_ERQ48_MASK)
#define DMA_ERQH_ERQ49_MASK                     0x20000u
#define DMA_ERQH_ERQ49_SHIFT                    17u
#define DMA_ERQH_ERQ49_WIDTH                    1u
#define DMA_ERQH_ERQ49(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ49_SHIFT)) \
                                                  &DMA_ERQH_ERQ49_MASK)
#define DMA_ERQH_ERQ50_MASK                     0x40000u
#define DMA_ERQH_ERQ50_SHIFT                    18u
#define DMA_ERQH_ERQ50_WIDTH                    1u
#define DMA_ERQH_ERQ50(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ50_SHIFT)) \
                                                  &DMA_ERQH_ERQ50_MASK)
#define DMA_ERQH_ERQ51_MASK                     0x80000u
#define DMA_ERQH_ERQ51_SHIFT                    19u
#define DMA_ERQH_ERQ51_WIDTH                    1u
#define DMA_ERQH_ERQ51(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ51_SHIFT)) \
                                                  &DMA_ERQH_ERQ51_MASK)
#define DMA_ERQH_ERQ52_MASK                     0x100000u
#define DMA_ERQH_ERQ52_SHIFT                    20u
#define DMA_ERQH_ERQ52_WIDTH                    1u
#define DMA_ERQH_ERQ52(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ52_SHIFT)) \
                                                  &DMA_ERQH_ERQ52_MASK)
#define DMA_ERQH_ERQ53_MASK                     0x200000u
#define DMA_ERQH_ERQ53_SHIFT                    21u
#define DMA_ERQH_ERQ53_WIDTH                    1u
#define DMA_ERQH_ERQ53(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ53_SHIFT)) \
                                                  &DMA_ERQH_ERQ53_MASK)
#define DMA_ERQH_ERQ54_MASK                     0x400000u
#define DMA_ERQH_ERQ54_SHIFT                    22u
#define DMA_ERQH_ERQ54_WIDTH                    1u
#define DMA_ERQH_ERQ54(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ54_SHIFT)) \
                                                  &DMA_ERQH_ERQ54_MASK)
#define DMA_ERQH_ERQ55_MASK                     0x800000u
#define DMA_ERQH_ERQ55_SHIFT                    23u
#define DMA_ERQH_ERQ55_WIDTH                    1u
#define DMA_ERQH_ERQ55(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ55_SHIFT)) \
                                                  &DMA_ERQH_ERQ55_MASK)
#define DMA_ERQH_ERQ56_MASK                     0x1000000u
#define DMA_ERQH_ERQ56_SHIFT                    24u
#define DMA_ERQH_ERQ56_WIDTH                    1u
#define DMA_ERQH_ERQ56(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ56_SHIFT)) \
                                                  &DMA_ERQH_ERQ56_MASK)
#define DMA_ERQH_ERQ57_MASK                     0x2000000u
#define DMA_ERQH_ERQ57_SHIFT                    25u
#define DMA_ERQH_ERQ57_WIDTH                    1u
#define DMA_ERQH_ERQ57(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ57_SHIFT)) \
                                                  &DMA_ERQH_ERQ57_MASK)
#define DMA_ERQH_ERQ58_MASK                     0x4000000u
#define DMA_ERQH_ERQ58_SHIFT                    26u
#define DMA_ERQH_ERQ58_WIDTH                    1u
#define DMA_ERQH_ERQ58(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ58_SHIFT)) \
                                                  &DMA_ERQH_ERQ58_MASK)
#define DMA_ERQH_ERQ59_MASK                     0x8000000u
#define DMA_ERQH_ERQ59_SHIFT                    27u
#define DMA_ERQH_ERQ59_WIDTH                    1u
#define DMA_ERQH_ERQ59(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ59_SHIFT)) \
                                                  &DMA_ERQH_ERQ59_MASK)
#define DMA_ERQH_ERQ60_MASK                     0x10000000u
#define DMA_ERQH_ERQ60_SHIFT                    28u
#define DMA_ERQH_ERQ60_WIDTH                    1u
#define DMA_ERQH_ERQ60(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ60_SHIFT)) \
                                                  &DMA_ERQH_ERQ60_MASK)
#define DMA_ERQH_ERQ61_MASK                     0x20000000u
#define DMA_ERQH_ERQ61_SHIFT                    29u
#define DMA_ERQH_ERQ61_WIDTH                    1u
#define DMA_ERQH_ERQ61(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ61_SHIFT)) \
                                                  &DMA_ERQH_ERQ61_MASK)
#define DMA_ERQH_ERQ62_MASK                     0x40000000u
#define DMA_ERQH_ERQ62_SHIFT                    30u
#define DMA_ERQH_ERQ62_WIDTH                    1u
#define DMA_ERQH_ERQ62(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ62_SHIFT)) \
                                                  &DMA_ERQH_ERQ62_MASK)
#define DMA_ERQH_ERQ63_MASK                     0x80000000u
#define DMA_ERQH_ERQ63_SHIFT                    31u
#define DMA_ERQH_ERQ63_WIDTH                    1u
#define DMA_ERQH_ERQ63(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQH_ERQ63_SHIFT)) \
                                                  &DMA_ERQH_ERQ63_MASK)
/* ERQL Bit Fields */
#define DMA_ERQL_ERQ0_MASK                      0x1u
#define DMA_ERQL_ERQ0_SHIFT                     0u
#define DMA_ERQL_ERQ0_WIDTH                     1u
#define DMA_ERQL_ERQ0(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ0_SHIFT)) \
                                                  &DMA_ERQL_ERQ0_MASK)
#define DMA_ERQL_ERQ1_MASK                      0x2u
#define DMA_ERQL_ERQ1_SHIFT                     1u
#define DMA_ERQL_ERQ1_WIDTH                     1u
#define DMA_ERQL_ERQ1(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ1_SHIFT)) \
                                                  &DMA_ERQL_ERQ1_MASK)
#define DMA_ERQL_ERQ2_MASK                      0x4u
#define DMA_ERQL_ERQ2_SHIFT                     2u
#define DMA_ERQL_ERQ2_WIDTH                     1u
#define DMA_ERQL_ERQ2(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ2_SHIFT)) \
                                                  &DMA_ERQL_ERQ2_MASK)
#define DMA_ERQL_ERQ3_MASK                      0x8u
#define DMA_ERQL_ERQ3_SHIFT                     3u
#define DMA_ERQL_ERQ3_WIDTH                     1u
#define DMA_ERQL_ERQ3(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ3_SHIFT)) \
                                                  &DMA_ERQL_ERQ3_MASK)
#define DMA_ERQL_ERQ4_MASK                      0x10u
#define DMA_ERQL_ERQ4_SHIFT                     4u
#define DMA_ERQL_ERQ4_WIDTH                     1u
#define DMA_ERQL_ERQ4(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ4_SHIFT)) \
                                                  &DMA_ERQL_ERQ4_MASK)
#define DMA_ERQL_ERQ5_MASK                      0x20u
#define DMA_ERQL_ERQ5_SHIFT                     5u
#define DMA_ERQL_ERQ5_WIDTH                     1u
#define DMA_ERQL_ERQ5(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ5_SHIFT)) \
                                                  &DMA_ERQL_ERQ5_MASK)
#define DMA_ERQL_ERQ6_MASK                      0x40u
#define DMA_ERQL_ERQ6_SHIFT                     6u
#define DMA_ERQL_ERQ6_WIDTH                     1u
#define DMA_ERQL_ERQ6(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ6_SHIFT)) \
                                                  &DMA_ERQL_ERQ6_MASK)
#define DMA_ERQL_ERQ7_MASK                      0x80u
#define DMA_ERQL_ERQ7_SHIFT                     7u
#define DMA_ERQL_ERQ7_WIDTH                     1u
#define DMA_ERQL_ERQ7(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ7_SHIFT)) \
                                                  &DMA_ERQL_ERQ7_MASK)
#define DMA_ERQL_ERQ8_MASK                      0x100u
#define DMA_ERQL_ERQ8_SHIFT                     8u
#define DMA_ERQL_ERQ8_WIDTH                     1u
#define DMA_ERQL_ERQ8(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ8_SHIFT)) \
                                                  &DMA_ERQL_ERQ8_MASK)
#define DMA_ERQL_ERQ9_MASK                      0x200u
#define DMA_ERQL_ERQ9_SHIFT                     9u
#define DMA_ERQL_ERQ9_WIDTH                     1u
#define DMA_ERQL_ERQ9(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ9_SHIFT)) \
                                                  &DMA_ERQL_ERQ9_MASK)
#define DMA_ERQL_ERQ10_MASK                     0x400u
#define DMA_ERQL_ERQ10_SHIFT                    10u
#define DMA_ERQL_ERQ10_WIDTH                    1u
#define DMA_ERQL_ERQ10(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ10_SHIFT)) \
                                                  &DMA_ERQL_ERQ10_MASK)
#define DMA_ERQL_ERQ11_MASK                     0x800u
#define DMA_ERQL_ERQ11_SHIFT                    11u
#define DMA_ERQL_ERQ11_WIDTH                    1u
#define DMA_ERQL_ERQ11(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ11_SHIFT)) \
                                                  &DMA_ERQL_ERQ11_MASK)
#define DMA_ERQL_ERQ12_MASK                     0x1000u
#define DMA_ERQL_ERQ12_SHIFT                    12u
#define DMA_ERQL_ERQ12_WIDTH                    1u
#define DMA_ERQL_ERQ12(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ12_SHIFT)) \
                                                  &DMA_ERQL_ERQ12_MASK)
#define DMA_ERQL_ERQ13_MASK                     0x2000u
#define DMA_ERQL_ERQ13_SHIFT                    13u
#define DMA_ERQL_ERQ13_WIDTH                    1u
#define DMA_ERQL_ERQ13(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ13_SHIFT)) \
                                                  &DMA_ERQL_ERQ13_MASK)
#define DMA_ERQL_ERQ14_MASK                     0x4000u
#define DMA_ERQL_ERQ14_SHIFT                    14u
#define DMA_ERQL_ERQ14_WIDTH                    1u
#define DMA_ERQL_ERQ14(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ14_SHIFT)) \
                                                  &DMA_ERQL_ERQ14_MASK)
#define DMA_ERQL_ERQ15_MASK                     0x8000u
#define DMA_ERQL_ERQ15_SHIFT                    15u
#define DMA_ERQL_ERQ15_WIDTH                    1u
#define DMA_ERQL_ERQ15(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ15_SHIFT)) \
                                                  &DMA_ERQL_ERQ15_MASK)
#define DMA_ERQL_ERQ16_MASK                     0x10000u
#define DMA_ERQL_ERQ16_SHIFT                    16u
#define DMA_ERQL_ERQ16_WIDTH                    1u
#define DMA_ERQL_ERQ16(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ16_SHIFT)) \
                                                  &DMA_ERQL_ERQ16_MASK)
#define DMA_ERQL_ERQ17_MASK                     0x20000u
#define DMA_ERQL_ERQ17_SHIFT                    17u
#define DMA_ERQL_ERQ17_WIDTH                    1u
#define DMA_ERQL_ERQ17(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ17_SHIFT)) \
                                                  &DMA_ERQL_ERQ17_MASK)
#define DMA_ERQL_ERQ18_MASK                     0x40000u
#define DMA_ERQL_ERQ18_SHIFT                    18u
#define DMA_ERQL_ERQ18_WIDTH                    1u
#define DMA_ERQL_ERQ18(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ18_SHIFT)) \
                                                  &DMA_ERQL_ERQ18_MASK)
#define DMA_ERQL_ERQ19_MASK                     0x80000u
#define DMA_ERQL_ERQ19_SHIFT                    19u
#define DMA_ERQL_ERQ19_WIDTH                    1u
#define DMA_ERQL_ERQ19(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ19_SHIFT)) \
                                                  &DMA_ERQL_ERQ19_MASK)
#define DMA_ERQL_ERQ20_MASK                     0x100000u
#define DMA_ERQL_ERQ20_SHIFT                    20u
#define DMA_ERQL_ERQ20_WIDTH                    1u
#define DMA_ERQL_ERQ20(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ20_SHIFT)) \
                                                  &DMA_ERQL_ERQ20_MASK)
#define DMA_ERQL_ERQ21_MASK                     0x200000u
#define DMA_ERQL_ERQ21_SHIFT                    21u
#define DMA_ERQL_ERQ21_WIDTH                    1u
#define DMA_ERQL_ERQ21(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ21_SHIFT)) \
                                                  &DMA_ERQL_ERQ21_MASK)
#define DMA_ERQL_ERQ22_MASK                     0x400000u
#define DMA_ERQL_ERQ22_SHIFT                    22u
#define DMA_ERQL_ERQ22_WIDTH                    1u
#define DMA_ERQL_ERQ22(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ22_SHIFT)) \
                                                  &DMA_ERQL_ERQ22_MASK)
#define DMA_ERQL_ERQ23_MASK                     0x800000u
#define DMA_ERQL_ERQ23_SHIFT                    23u
#define DMA_ERQL_ERQ23_WIDTH                    1u
#define DMA_ERQL_ERQ23(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ23_SHIFT)) \
                                                  &DMA_ERQL_ERQ23_MASK)
#define DMA_ERQL_ERQ24_MASK                     0x1000000u
#define DMA_ERQL_ERQ24_SHIFT                    24u
#define DMA_ERQL_ERQ24_WIDTH                    1u
#define DMA_ERQL_ERQ24(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ24_SHIFT)) \
                                                  &DMA_ERQL_ERQ24_MASK)
#define DMA_ERQL_ERQ25_MASK                     0x2000000u
#define DMA_ERQL_ERQ25_SHIFT                    25u
#define DMA_ERQL_ERQ25_WIDTH                    1u
#define DMA_ERQL_ERQ25(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ25_SHIFT)) \
                                                  &DMA_ERQL_ERQ25_MASK)
#define DMA_ERQL_ERQ26_MASK                     0x4000000u
#define DMA_ERQL_ERQ26_SHIFT                    26u
#define DMA_ERQL_ERQ26_WIDTH                    1u
#define DMA_ERQL_ERQ26(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ26_SHIFT)) \
                                                  &DMA_ERQL_ERQ26_MASK)
#define DMA_ERQL_ERQ27_MASK                     0x8000000u
#define DMA_ERQL_ERQ27_SHIFT                    27u
#define DMA_ERQL_ERQ27_WIDTH                    1u
#define DMA_ERQL_ERQ27(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ27_SHIFT)) \
                                                  &DMA_ERQL_ERQ27_MASK)
#define DMA_ERQL_ERQ28_MASK                     0x10000000u
#define DMA_ERQL_ERQ28_SHIFT                    28u
#define DMA_ERQL_ERQ28_WIDTH                    1u
#define DMA_ERQL_ERQ28(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ28_SHIFT)) \
                                                  &DMA_ERQL_ERQ28_MASK)
#define DMA_ERQL_ERQ29_MASK                     0x20000000u
#define DMA_ERQL_ERQ29_SHIFT                    29u
#define DMA_ERQL_ERQ29_WIDTH                    1u
#define DMA_ERQL_ERQ29(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ29_SHIFT)) \
                                                  &DMA_ERQL_ERQ29_MASK)
#define DMA_ERQL_ERQ30_MASK                     0x40000000u
#define DMA_ERQL_ERQ30_SHIFT                    30u
#define DMA_ERQL_ERQ30_WIDTH                    1u
#define DMA_ERQL_ERQ30(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ30_SHIFT)) \
                                                  &DMA_ERQL_ERQ30_MASK)
#define DMA_ERQL_ERQ31_MASK                     0x80000000u
#define DMA_ERQL_ERQ31_SHIFT                    31u
#define DMA_ERQL_ERQ31_WIDTH                    1u
#define DMA_ERQL_ERQ31(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERQL_ERQ31_SHIFT)) \
                                                  &DMA_ERQL_ERQ31_MASK)
/* EEIH Bit Fields */
#define DMA_EEIH_EEI32_MASK                     0x1u
#define DMA_EEIH_EEI32_SHIFT                    0u
#define DMA_EEIH_EEI32_WIDTH                    1u
#define DMA_EEIH_EEI32(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI32_SHIFT)) \
                                                  &DMA_EEIH_EEI32_MASK)
#define DMA_EEIH_EEI33_MASK                     0x2u
#define DMA_EEIH_EEI33_SHIFT                    1u
#define DMA_EEIH_EEI33_WIDTH                    1u
#define DMA_EEIH_EEI33(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI33_SHIFT)) \
                                                  &DMA_EEIH_EEI33_MASK)
#define DMA_EEIH_EEI34_MASK                     0x4u
#define DMA_EEIH_EEI34_SHIFT                    2u
#define DMA_EEIH_EEI34_WIDTH                    1u
#define DMA_EEIH_EEI34(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI34_SHIFT)) \
                                                  &DMA_EEIH_EEI34_MASK)
#define DMA_EEIH_EEI35_MASK                     0x8u
#define DMA_EEIH_EEI35_SHIFT                    3u
#define DMA_EEIH_EEI35_WIDTH                    1u
#define DMA_EEIH_EEI35(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI35_SHIFT)) \
                                                  &DMA_EEIH_EEI35_MASK)
#define DMA_EEIH_EEI36_MASK                     0x10u
#define DMA_EEIH_EEI36_SHIFT                    4u
#define DMA_EEIH_EEI36_WIDTH                    1u
#define DMA_EEIH_EEI36(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI36_SHIFT)) \
                                                  &DMA_EEIH_EEI36_MASK)
#define DMA_EEIH_EEI37_MASK                     0x20u
#define DMA_EEIH_EEI37_SHIFT                    5u
#define DMA_EEIH_EEI37_WIDTH                    1u
#define DMA_EEIH_EEI37(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI37_SHIFT)) \
                                                  &DMA_EEIH_EEI37_MASK)
#define DMA_EEIH_EEI38_MASK                     0x40u
#define DMA_EEIH_EEI38_SHIFT                    6u
#define DMA_EEIH_EEI38_WIDTH                    1u
#define DMA_EEIH_EEI38(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI38_SHIFT)) \
                                                  &DMA_EEIH_EEI38_MASK)
#define DMA_EEIH_EEI39_MASK                     0x80u
#define DMA_EEIH_EEI39_SHIFT                    7u
#define DMA_EEIH_EEI39_WIDTH                    1u
#define DMA_EEIH_EEI39(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI39_SHIFT)) \
                                                  &DMA_EEIH_EEI39_MASK)
#define DMA_EEIH_EEI40_MASK                     0x100u
#define DMA_EEIH_EEI40_SHIFT                    8u
#define DMA_EEIH_EEI40_WIDTH                    1u
#define DMA_EEIH_EEI40(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI40_SHIFT)) \
                                                  &DMA_EEIH_EEI40_MASK)
#define DMA_EEIH_EEI41_MASK                     0x200u
#define DMA_EEIH_EEI41_SHIFT                    9u
#define DMA_EEIH_EEI41_WIDTH                    1u
#define DMA_EEIH_EEI41(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI41_SHIFT)) \
                                                  &DMA_EEIH_EEI41_MASK)
#define DMA_EEIH_EEI42_MASK                     0x400u
#define DMA_EEIH_EEI42_SHIFT                    10u
#define DMA_EEIH_EEI42_WIDTH                    1u
#define DMA_EEIH_EEI42(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI42_SHIFT)) \
                                                  &DMA_EEIH_EEI42_MASK)
#define DMA_EEIH_EEI43_MASK                     0x800u
#define DMA_EEIH_EEI43_SHIFT                    11u
#define DMA_EEIH_EEI43_WIDTH                    1u
#define DMA_EEIH_EEI43(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI43_SHIFT)) \
                                                  &DMA_EEIH_EEI43_MASK)
#define DMA_EEIH_EEI44_MASK                     0x1000u
#define DMA_EEIH_EEI44_SHIFT                    12u
#define DMA_EEIH_EEI44_WIDTH                    1u
#define DMA_EEIH_EEI44(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI44_SHIFT)) \
                                                  &DMA_EEIH_EEI44_MASK)
#define DMA_EEIH_EEI45_MASK                     0x2000u
#define DMA_EEIH_EEI45_SHIFT                    13u
#define DMA_EEIH_EEI45_WIDTH                    1u
#define DMA_EEIH_EEI45(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI45_SHIFT)) \
                                                  &DMA_EEIH_EEI45_MASK)
#define DMA_EEIH_EEI46_MASK                     0x4000u
#define DMA_EEIH_EEI46_SHIFT                    14u
#define DMA_EEIH_EEI46_WIDTH                    1u
#define DMA_EEIH_EEI46(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI46_SHIFT)) \
                                                  &DMA_EEIH_EEI46_MASK)
#define DMA_EEIH_EEI47_MASK                     0x8000u
#define DMA_EEIH_EEI47_SHIFT                    15u
#define DMA_EEIH_EEI47_WIDTH                    1u
#define DMA_EEIH_EEI47(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI47_SHIFT)) \
                                                  &DMA_EEIH_EEI47_MASK)
#define DMA_EEIH_EEI48_MASK                     0x10000u
#define DMA_EEIH_EEI48_SHIFT                    16u
#define DMA_EEIH_EEI48_WIDTH                    1u
#define DMA_EEIH_EEI48(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI48_SHIFT)) \
                                                  &DMA_EEIH_EEI48_MASK)
#define DMA_EEIH_EEI49_MASK                     0x20000u
#define DMA_EEIH_EEI49_SHIFT                    17u
#define DMA_EEIH_EEI49_WIDTH                    1u
#define DMA_EEIH_EEI49(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI49_SHIFT)) \
                                                  &DMA_EEIH_EEI49_MASK)
#define DMA_EEIH_EEI50_MASK                     0x40000u
#define DMA_EEIH_EEI50_SHIFT                    18u
#define DMA_EEIH_EEI50_WIDTH                    1u
#define DMA_EEIH_EEI50(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI50_SHIFT)) \
                                                  &DMA_EEIH_EEI50_MASK)
#define DMA_EEIH_EEI51_MASK                     0x80000u
#define DMA_EEIH_EEI51_SHIFT                    19u
#define DMA_EEIH_EEI51_WIDTH                    1u
#define DMA_EEIH_EEI51(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI51_SHIFT)) \
                                                  &DMA_EEIH_EEI51_MASK)
#define DMA_EEIH_EEI52_MASK                     0x100000u
#define DMA_EEIH_EEI52_SHIFT                    20u
#define DMA_EEIH_EEI52_WIDTH                    1u
#define DMA_EEIH_EEI52(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI52_SHIFT)) \
                                                  &DMA_EEIH_EEI52_MASK)
#define DMA_EEIH_EEI53_MASK                     0x200000u
#define DMA_EEIH_EEI53_SHIFT                    21u
#define DMA_EEIH_EEI53_WIDTH                    1u
#define DMA_EEIH_EEI53(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI53_SHIFT)) \
                                                  &DMA_EEIH_EEI53_MASK)
#define DMA_EEIH_EEI54_MASK                     0x400000u
#define DMA_EEIH_EEI54_SHIFT                    22u
#define DMA_EEIH_EEI54_WIDTH                    1u
#define DMA_EEIH_EEI54(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI54_SHIFT)) \
                                                  &DMA_EEIH_EEI54_MASK)
#define DMA_EEIH_EEI55_MASK                     0x800000u
#define DMA_EEIH_EEI55_SHIFT                    23u
#define DMA_EEIH_EEI55_WIDTH                    1u
#define DMA_EEIH_EEI55(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI55_SHIFT)) \
                                                  &DMA_EEIH_EEI55_MASK)
#define DMA_EEIH_EEI56_MASK                     0x1000000u
#define DMA_EEIH_EEI56_SHIFT                    24u
#define DMA_EEIH_EEI56_WIDTH                    1u
#define DMA_EEIH_EEI56(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI56_SHIFT)) \
                                                  &DMA_EEIH_EEI56_MASK)
#define DMA_EEIH_EEI57_MASK                     0x2000000u
#define DMA_EEIH_EEI57_SHIFT                    25u
#define DMA_EEIH_EEI57_WIDTH                    1u
#define DMA_EEIH_EEI57(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI57_SHIFT)) \
                                                  &DMA_EEIH_EEI57_MASK)
#define DMA_EEIH_EEI58_MASK                     0x4000000u
#define DMA_EEIH_EEI58_SHIFT                    26u
#define DMA_EEIH_EEI58_WIDTH                    1u
#define DMA_EEIH_EEI58(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI58_SHIFT)) \
                                                  &DMA_EEIH_EEI58_MASK)
#define DMA_EEIH_EEI59_MASK                     0x8000000u
#define DMA_EEIH_EEI59_SHIFT                    27u
#define DMA_EEIH_EEI59_WIDTH                    1u
#define DMA_EEIH_EEI59(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI59_SHIFT)) \
                                                  &DMA_EEIH_EEI59_MASK)
#define DMA_EEIH_EEI60_MASK                     0x10000000u
#define DMA_EEIH_EEI60_SHIFT                    28u
#define DMA_EEIH_EEI60_WIDTH                    1u
#define DMA_EEIH_EEI60(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI60_SHIFT)) \
                                                  &DMA_EEIH_EEI60_MASK)
#define DMA_EEIH_EEI61_MASK                     0x20000000u
#define DMA_EEIH_EEI61_SHIFT                    29u
#define DMA_EEIH_EEI61_WIDTH                    1u
#define DMA_EEIH_EEI61(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI61_SHIFT)) \
                                                  &DMA_EEIH_EEI61_MASK)
#define DMA_EEIH_EEI62_MASK                     0x40000000u
#define DMA_EEIH_EEI62_SHIFT                    30u
#define DMA_EEIH_EEI62_WIDTH                    1u
#define DMA_EEIH_EEI62(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI62_SHIFT)) \
                                                  &DMA_EEIH_EEI62_MASK)
#define DMA_EEIH_EEI63_MASK                     0x80000000u
#define DMA_EEIH_EEI63_SHIFT                    31u
#define DMA_EEIH_EEI63_WIDTH                    1u
#define DMA_EEIH_EEI63(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIH_EEI63_SHIFT)) \
                                                  &DMA_EEIH_EEI63_MASK)
/* EEIL Bit Fields */
#define DMA_EEIL_EEI0_MASK                      0x1u
#define DMA_EEIL_EEI0_SHIFT                     0u
#define DMA_EEIL_EEI0_WIDTH                     1u
#define DMA_EEIL_EEI0(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI0_SHIFT)) \
                                                  &DMA_EEIL_EEI0_MASK)
#define DMA_EEIL_EEI1_MASK                      0x2u
#define DMA_EEIL_EEI1_SHIFT                     1u
#define DMA_EEIL_EEI1_WIDTH                     1u
#define DMA_EEIL_EEI1(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI1_SHIFT)) \
                                                  &DMA_EEIL_EEI1_MASK)
#define DMA_EEIL_EEI2_MASK                      0x4u
#define DMA_EEIL_EEI2_SHIFT                     2u
#define DMA_EEIL_EEI2_WIDTH                     1u
#define DMA_EEIL_EEI2(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI2_SHIFT)) \
                                                  &DMA_EEIL_EEI2_MASK)
#define DMA_EEIL_EEI3_MASK                      0x8u
#define DMA_EEIL_EEI3_SHIFT                     3u
#define DMA_EEIL_EEI3_WIDTH                     1u
#define DMA_EEIL_EEI3(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI3_SHIFT)) \
                                                  &DMA_EEIL_EEI3_MASK)
#define DMA_EEIL_EEI4_MASK                      0x10u
#define DMA_EEIL_EEI4_SHIFT                     4u
#define DMA_EEIL_EEI4_WIDTH                     1u
#define DMA_EEIL_EEI4(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI4_SHIFT)) \
                                                  &DMA_EEIL_EEI4_MASK)
#define DMA_EEIL_EEI5_MASK                      0x20u
#define DMA_EEIL_EEI5_SHIFT                     5u
#define DMA_EEIL_EEI5_WIDTH                     1u
#define DMA_EEIL_EEI5(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI5_SHIFT)) \
                                                  &DMA_EEIL_EEI5_MASK)
#define DMA_EEIL_EEI6_MASK                      0x40u
#define DMA_EEIL_EEI6_SHIFT                     6u
#define DMA_EEIL_EEI6_WIDTH                     1u
#define DMA_EEIL_EEI6(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI6_SHIFT)) \
                                                  &DMA_EEIL_EEI6_MASK)
#define DMA_EEIL_EEI7_MASK                      0x80u
#define DMA_EEIL_EEI7_SHIFT                     7u
#define DMA_EEIL_EEI7_WIDTH                     1u
#define DMA_EEIL_EEI7(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI7_SHIFT)) \
                                                  &DMA_EEIL_EEI7_MASK)
#define DMA_EEIL_EEI8_MASK                      0x100u
#define DMA_EEIL_EEI8_SHIFT                     8u
#define DMA_EEIL_EEI8_WIDTH                     1u
#define DMA_EEIL_EEI8(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI8_SHIFT)) \
                                                  &DMA_EEIL_EEI8_MASK)
#define DMA_EEIL_EEI9_MASK                      0x200u
#define DMA_EEIL_EEI9_SHIFT                     9u
#define DMA_EEIL_EEI9_WIDTH                     1u
#define DMA_EEIL_EEI9(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI9_SHIFT)) \
                                                  &DMA_EEIL_EEI9_MASK)
#define DMA_EEIL_EEI10_MASK                     0x400u
#define DMA_EEIL_EEI10_SHIFT                    10u
#define DMA_EEIL_EEI10_WIDTH                    1u
#define DMA_EEIL_EEI10(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI10_SHIFT)) \
                                                  &DMA_EEIL_EEI10_MASK)
#define DMA_EEIL_EEI11_MASK                     0x800u
#define DMA_EEIL_EEI11_SHIFT                    11u
#define DMA_EEIL_EEI11_WIDTH                    1u
#define DMA_EEIL_EEI11(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI11_SHIFT)) \
                                                  &DMA_EEIL_EEI11_MASK)
#define DMA_EEIL_EEI12_MASK                     0x1000u
#define DMA_EEIL_EEI12_SHIFT                    12u
#define DMA_EEIL_EEI12_WIDTH                    1u
#define DMA_EEIL_EEI12(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI12_SHIFT)) \
                                                  &DMA_EEIL_EEI12_MASK)
#define DMA_EEIL_EEI13_MASK                     0x2000u
#define DMA_EEIL_EEI13_SHIFT                    13u
#define DMA_EEIL_EEI13_WIDTH                    1u
#define DMA_EEIL_EEI13(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI13_SHIFT)) \
                                                  &DMA_EEIL_EEI13_MASK)
#define DMA_EEIL_EEI14_MASK                     0x4000u
#define DMA_EEIL_EEI14_SHIFT                    14u
#define DMA_EEIL_EEI14_WIDTH                    1u
#define DMA_EEIL_EEI14(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI14_SHIFT)) \
                                                  &DMA_EEIL_EEI14_MASK)
#define DMA_EEIL_EEI15_MASK                     0x8000u
#define DMA_EEIL_EEI15_SHIFT                    15u
#define DMA_EEIL_EEI15_WIDTH                    1u
#define DMA_EEIL_EEI15(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI15_SHIFT)) \
                                                  &DMA_EEIL_EEI15_MASK)
#define DMA_EEIL_EEI16_MASK                     0x10000u
#define DMA_EEIL_EEI16_SHIFT                    16u
#define DMA_EEIL_EEI16_WIDTH                    1u
#define DMA_EEIL_EEI16(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI16_SHIFT)) \
                                                  &DMA_EEIL_EEI16_MASK)
#define DMA_EEIL_EEI17_MASK                     0x20000u
#define DMA_EEIL_EEI17_SHIFT                    17u
#define DMA_EEIL_EEI17_WIDTH                    1u
#define DMA_EEIL_EEI17(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI17_SHIFT)) \
                                                  &DMA_EEIL_EEI17_MASK)
#define DMA_EEIL_EEI18_MASK                     0x40000u
#define DMA_EEIL_EEI18_SHIFT                    18u
#define DMA_EEIL_EEI18_WIDTH                    1u
#define DMA_EEIL_EEI18(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI18_SHIFT)) \
                                                  &DMA_EEIL_EEI18_MASK)
#define DMA_EEIL_EEI19_MASK                     0x80000u
#define DMA_EEIL_EEI19_SHIFT                    19u
#define DMA_EEIL_EEI19_WIDTH                    1u
#define DMA_EEIL_EEI19(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI19_SHIFT)) \
                                                  &DMA_EEIL_EEI19_MASK)
#define DMA_EEIL_EEI20_MASK                     0x100000u
#define DMA_EEIL_EEI20_SHIFT                    20u
#define DMA_EEIL_EEI20_WIDTH                    1u
#define DMA_EEIL_EEI20(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI20_SHIFT)) \
                                                  &DMA_EEIL_EEI20_MASK)
#define DMA_EEIL_EEI21_MASK                     0x200000u
#define DMA_EEIL_EEI21_SHIFT                    21u
#define DMA_EEIL_EEI21_WIDTH                    1u
#define DMA_EEIL_EEI21(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI21_SHIFT)) \
                                                  &DMA_EEIL_EEI21_MASK)
#define DMA_EEIL_EEI22_MASK                     0x400000u
#define DMA_EEIL_EEI22_SHIFT                    22u
#define DMA_EEIL_EEI22_WIDTH                    1u
#define DMA_EEIL_EEI22(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI22_SHIFT)) \
                                                  &DMA_EEIL_EEI22_MASK)
#define DMA_EEIL_EEI23_MASK                     0x800000u
#define DMA_EEIL_EEI23_SHIFT                    23u
#define DMA_EEIL_EEI23_WIDTH                    1u
#define DMA_EEIL_EEI23(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI23_SHIFT)) \
                                                  &DMA_EEIL_EEI23_MASK)
#define DMA_EEIL_EEI24_MASK                     0x1000000u
#define DMA_EEIL_EEI24_SHIFT                    24u
#define DMA_EEIL_EEI24_WIDTH                    1u
#define DMA_EEIL_EEI24(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI24_SHIFT)) \
                                                  &DMA_EEIL_EEI24_MASK)
#define DMA_EEIL_EEI25_MASK                     0x2000000u
#define DMA_EEIL_EEI25_SHIFT                    25u
#define DMA_EEIL_EEI25_WIDTH                    1u
#define DMA_EEIL_EEI25(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI25_SHIFT)) \
                                                  &DMA_EEIL_EEI25_MASK)
#define DMA_EEIL_EEI26_MASK                     0x4000000u
#define DMA_EEIL_EEI26_SHIFT                    26u
#define DMA_EEIL_EEI26_WIDTH                    1u
#define DMA_EEIL_EEI26(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI26_SHIFT)) \
                                                  &DMA_EEIL_EEI26_MASK)
#define DMA_EEIL_EEI27_MASK                     0x8000000u
#define DMA_EEIL_EEI27_SHIFT                    27u
#define DMA_EEIL_EEI27_WIDTH                    1u
#define DMA_EEIL_EEI27(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI27_SHIFT)) \
                                                  &DMA_EEIL_EEI27_MASK)
#define DMA_EEIL_EEI28_MASK                     0x10000000u
#define DMA_EEIL_EEI28_SHIFT                    28u
#define DMA_EEIL_EEI28_WIDTH                    1u
#define DMA_EEIL_EEI28(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI28_SHIFT)) \
                                                  &DMA_EEIL_EEI28_MASK)
#define DMA_EEIL_EEI29_MASK                     0x20000000u
#define DMA_EEIL_EEI29_SHIFT                    29u
#define DMA_EEIL_EEI29_WIDTH                    1u
#define DMA_EEIL_EEI29(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI29_SHIFT)) \
                                                  &DMA_EEIL_EEI29_MASK)
#define DMA_EEIL_EEI30_MASK                     0x40000000u
#define DMA_EEIL_EEI30_SHIFT                    30u
#define DMA_EEIL_EEI30_WIDTH                    1u
#define DMA_EEIL_EEI30(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI30_SHIFT)) \
                                                  &DMA_EEIL_EEI30_MASK)
#define DMA_EEIL_EEI31_MASK                     0x80000000u
#define DMA_EEIL_EEI31_SHIFT                    31u
#define DMA_EEIL_EEI31_WIDTH                    1u
#define DMA_EEIL_EEI31(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_EEIL_EEI31_SHIFT)) \
                                                  &DMA_EEIL_EEI31_MASK)
/* SERQ Bit Fields */
#define DMA_SERQ_SERQ_MASK                      0x3Fu
#define DMA_SERQ_SERQ_SHIFT                     0u
#define DMA_SERQ_SERQ_WIDTH                     6u
#define DMA_SERQ_SERQ(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SERQ_SERQ_SHIFT)) \
                                                  &DMA_SERQ_SERQ_MASK)
#define DMA_SERQ_SAER_MASK                      0x40u
#define DMA_SERQ_SAER_SHIFT                     6u
#define DMA_SERQ_SAER_WIDTH                     1u
#define DMA_SERQ_SAER(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SERQ_SAER_SHIFT)) \
                                                  &DMA_SERQ_SAER_MASK)
#define DMA_SERQ_NOP_MASK                       0x80u
#define DMA_SERQ_NOP_SHIFT                      7u
#define DMA_SERQ_NOP_WIDTH                      1u
#define DMA_SERQ_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_SERQ_NOP_SHIFT)) \
                                                  &DMA_SERQ_NOP_MASK)
/* CERQ Bit Fields */
#define DMA_CERQ_CERQ_MASK                      0x3Fu
#define DMA_CERQ_CERQ_SHIFT                     0u
#define DMA_CERQ_CERQ_WIDTH                     6u
#define DMA_CERQ_CERQ(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CERQ_CERQ_SHIFT)) \
                                                  &DMA_CERQ_CERQ_MASK)
#define DMA_CERQ_CAER_MASK                      0x40u
#define DMA_CERQ_CAER_SHIFT                     6u
#define DMA_CERQ_CAER_WIDTH                     1u
#define DMA_CERQ_CAER(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CERQ_CAER_SHIFT)) \
                                                  &DMA_CERQ_CAER_MASK)
#define DMA_CERQ_NOP_MASK                       0x80u
#define DMA_CERQ_NOP_SHIFT                      7u
#define DMA_CERQ_NOP_WIDTH                      1u
#define DMA_CERQ_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_CERQ_NOP_SHIFT)) \
                                                  &DMA_CERQ_NOP_MASK)
/* SEEI Bit Fields */
#define DMA_SEEI_SEEI_MASK                      0x3Fu
#define DMA_SEEI_SEEI_SHIFT                     0u
#define DMA_SEEI_SEEI_WIDTH                     6u
#define DMA_SEEI_SEEI(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SEEI_SEEI_SHIFT)) \
                                                  &DMA_SEEI_SEEI_MASK)
#define DMA_SEEI_SAEE_MASK                      0x40u
#define DMA_SEEI_SAEE_SHIFT                     6u
#define DMA_SEEI_SAEE_WIDTH                     1u
#define DMA_SEEI_SAEE(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SEEI_SAEE_SHIFT)) \
                                                  &DMA_SEEI_SAEE_MASK)
#define DMA_SEEI_NOP_MASK                       0x80u
#define DMA_SEEI_NOP_SHIFT                      7u
#define DMA_SEEI_NOP_WIDTH                      1u
#define DMA_SEEI_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_SEEI_NOP_SHIFT)) \
                                                  &DMA_SEEI_NOP_MASK)
/* CEEI Bit Fields */
#define DMA_CEEI_CEEI_MASK                      0x3Fu
#define DMA_CEEI_CEEI_SHIFT                     0u
#define DMA_CEEI_CEEI_WIDTH                     6u
#define DMA_CEEI_CEEI(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CEEI_CEEI_SHIFT)) \
                                                  &DMA_CEEI_CEEI_MASK)
#define DMA_CEEI_CAEE_MASK                      0x40u
#define DMA_CEEI_CAEE_SHIFT                     6u
#define DMA_CEEI_CAEE_WIDTH                     1u
#define DMA_CEEI_CAEE(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CEEI_CAEE_SHIFT)) \
                                                  &DMA_CEEI_CAEE_MASK)
#define DMA_CEEI_NOP_MASK                       0x80u
#define DMA_CEEI_NOP_SHIFT                      7u
#define DMA_CEEI_NOP_WIDTH                      1u
#define DMA_CEEI_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_CEEI_NOP_SHIFT)) \
                                                  &DMA_CEEI_NOP_MASK)
/* CINT Bit Fields */
#define DMA_CINT_CINT_MASK                      0x3Fu
#define DMA_CINT_CINT_SHIFT                     0u
#define DMA_CINT_CINT_WIDTH                     6u
#define DMA_CINT_CINT(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CINT_CINT_SHIFT)) \
                                                  &DMA_CINT_CINT_MASK)
#define DMA_CINT_CAIR_MASK                      0x40u
#define DMA_CINT_CAIR_SHIFT                     6u
#define DMA_CINT_CAIR_WIDTH                     1u
#define DMA_CINT_CAIR(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CINT_CAIR_SHIFT)) \
                                                  &DMA_CINT_CAIR_MASK)
#define DMA_CINT_NOP_MASK                       0x80u
#define DMA_CINT_NOP_SHIFT                      7u
#define DMA_CINT_NOP_WIDTH                      1u
#define DMA_CINT_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_CINT_NOP_SHIFT)) \
                                                  &DMA_CINT_NOP_MASK)
/* CERR Bit Fields */
#define DMA_CERR_CERR_MASK                      0x3Fu
#define DMA_CERR_CERR_SHIFT                     0u
#define DMA_CERR_CERR_WIDTH                     6u
#define DMA_CERR_CERR(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CERR_CERR_SHIFT)) \
                                                  &DMA_CERR_CERR_MASK)
#define DMA_CERR_CAEI_MASK                      0x40u
#define DMA_CERR_CAEI_SHIFT                     6u
#define DMA_CERR_CAEI_WIDTH                     1u
#define DMA_CERR_CAEI(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CERR_CAEI_SHIFT)) \
                                                  &DMA_CERR_CAEI_MASK)
#define DMA_CERR_NOP_MASK                       0x80u
#define DMA_CERR_NOP_SHIFT                      7u
#define DMA_CERR_NOP_WIDTH                      1u
#define DMA_CERR_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_CERR_NOP_SHIFT)) \
                                                  &DMA_CERR_NOP_MASK)
/* SSRT Bit Fields */
#define DMA_SSRT_SSRT_MASK                      0x3Fu
#define DMA_SSRT_SSRT_SHIFT                     0u
#define DMA_SSRT_SSRT_WIDTH                     6u
#define DMA_SSRT_SSRT(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SSRT_SSRT_SHIFT)) \
                                                  &DMA_SSRT_SSRT_MASK)
#define DMA_SSRT_SAST_MASK                      0x40u
#define DMA_SSRT_SAST_SHIFT                     6u
#define DMA_SSRT_SAST_WIDTH                     1u
#define DMA_SSRT_SAST(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_SSRT_SAST_SHIFT)) \
                                                  &DMA_SSRT_SAST_MASK)
#define DMA_SSRT_NOP_MASK                       0x80u
#define DMA_SSRT_NOP_SHIFT                      7u
#define DMA_SSRT_NOP_WIDTH                      1u
#define DMA_SSRT_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_SSRT_NOP_SHIFT)) \
                                                  &DMA_SSRT_NOP_MASK)
/* CDNE Bit Fields */
#define DMA_CDNE_CDNE_MASK                      0x3Fu
#define DMA_CDNE_CDNE_SHIFT                     0u
#define DMA_CDNE_CDNE_WIDTH                     6u
#define DMA_CDNE_CDNE(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CDNE_CDNE_SHIFT)) \
                                                  &DMA_CDNE_CDNE_MASK)
#define DMA_CDNE_CADN_MASK                      0x40u
#define DMA_CDNE_CADN_SHIFT                     6u
#define DMA_CDNE_CADN_WIDTH                     1u
#define DMA_CDNE_CADN(x)                        (((uint8)(((uint8)(x)) \
                                                  << DMA_CDNE_CADN_SHIFT)) \
                                                  &DMA_CDNE_CADN_MASK)
#define DMA_CDNE_NOP_MASK                       0x80u
#define DMA_CDNE_NOP_SHIFT                      7u
#define DMA_CDNE_NOP_WIDTH                      1u
#define DMA_CDNE_NOP(x)                         (((uint8)(((uint8)(x)) \
                                                  << DMA_CDNE_NOP_SHIFT)) \
                                                  &DMA_CDNE_NOP_MASK)
/* INTH Bit Fields */
#define DMA_INTH_INT32_MASK                     0x1u
#define DMA_INTH_INT32_SHIFT                    0u
#define DMA_INTH_INT32_WIDTH                    1u
#define DMA_INTH_INT32(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT32_SHIFT)) \
                                                  &DMA_INTH_INT32_MASK)
#define DMA_INTH_INT33_MASK                     0x2u
#define DMA_INTH_INT33_SHIFT                    1u
#define DMA_INTH_INT33_WIDTH                    1u
#define DMA_INTH_INT33(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT33_SHIFT)) \
                                                  &DMA_INTH_INT33_MASK)
#define DMA_INTH_INT34_MASK                     0x4u
#define DMA_INTH_INT34_SHIFT                    2u
#define DMA_INTH_INT34_WIDTH                    1u
#define DMA_INTH_INT34(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT34_SHIFT)) \
                                                  &DMA_INTH_INT34_MASK)
#define DMA_INTH_INT35_MASK                     0x8u
#define DMA_INTH_INT35_SHIFT                    3u
#define DMA_INTH_INT35_WIDTH                    1u
#define DMA_INTH_INT35(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT35_SHIFT)) \
                                                  &DMA_INTH_INT35_MASK)
#define DMA_INTH_INT36_MASK                     0x10u
#define DMA_INTH_INT36_SHIFT                    4u
#define DMA_INTH_INT36_WIDTH                    1u
#define DMA_INTH_INT36(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT36_SHIFT)) \
                                                  &DMA_INTH_INT36_MASK)
#define DMA_INTH_INT37_MASK                     0x20u
#define DMA_INTH_INT37_SHIFT                    5u
#define DMA_INTH_INT37_WIDTH                    1u
#define DMA_INTH_INT37(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT37_SHIFT)) \
                                                  &DMA_INTH_INT37_MASK)
#define DMA_INTH_INT38_MASK                     0x40u
#define DMA_INTH_INT38_SHIFT                    6u
#define DMA_INTH_INT38_WIDTH                    1u
#define DMA_INTH_INT38(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT38_SHIFT)) \
                                                  &DMA_INTH_INT38_MASK)
#define DMA_INTH_INT39_MASK                     0x80u
#define DMA_INTH_INT39_SHIFT                    7u
#define DMA_INTH_INT39_WIDTH                    1u
#define DMA_INTH_INT39(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT39_SHIFT)) \
                                                  &DMA_INTH_INT39_MASK)
#define DMA_INTH_INT40_MASK                     0x100u
#define DMA_INTH_INT40_SHIFT                    8u
#define DMA_INTH_INT40_WIDTH                    1u
#define DMA_INTH_INT40(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT40_SHIFT)) \
                                                  &DMA_INTH_INT40_MASK)
#define DMA_INTH_INT41_MASK                     0x200u
#define DMA_INTH_INT41_SHIFT                    9u
#define DMA_INTH_INT41_WIDTH                    1u
#define DMA_INTH_INT41(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT41_SHIFT)) \
                                                  &DMA_INTH_INT41_MASK)
#define DMA_INTH_INT42_MASK                     0x400u
#define DMA_INTH_INT42_SHIFT                    10u
#define DMA_INTH_INT42_WIDTH                    1u
#define DMA_INTH_INT42(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT42_SHIFT)) \
                                                  &DMA_INTH_INT42_MASK)
#define DMA_INTH_INT43_MASK                     0x800u
#define DMA_INTH_INT43_SHIFT                    11u
#define DMA_INTH_INT43_WIDTH                    1u
#define DMA_INTH_INT43(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT43_SHIFT)) \
                                                  &DMA_INTH_INT43_MASK)
#define DMA_INTH_INT44_MASK                     0x1000u
#define DMA_INTH_INT44_SHIFT                    12u
#define DMA_INTH_INT44_WIDTH                    1u
#define DMA_INTH_INT44(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT44_SHIFT)) \
                                                  &DMA_INTH_INT44_MASK)
#define DMA_INTH_INT45_MASK                     0x2000u
#define DMA_INTH_INT45_SHIFT                    13u
#define DMA_INTH_INT45_WIDTH                    1u
#define DMA_INTH_INT45(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT45_SHIFT)) \
                                                  &DMA_INTH_INT45_MASK)
#define DMA_INTH_INT46_MASK                     0x4000u
#define DMA_INTH_INT46_SHIFT                    14u
#define DMA_INTH_INT46_WIDTH                    1u
#define DMA_INTH_INT46(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT46_SHIFT)) \
                                                  &DMA_INTH_INT46_MASK)
#define DMA_INTH_INT47_MASK                     0x8000u
#define DMA_INTH_INT47_SHIFT                    15u
#define DMA_INTH_INT47_WIDTH                    1u
#define DMA_INTH_INT47(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT47_SHIFT)) \
                                                  &DMA_INTH_INT47_MASK)
#define DMA_INTH_INT48_MASK                     0x10000u
#define DMA_INTH_INT48_SHIFT                    16u
#define DMA_INTH_INT48_WIDTH                    1u
#define DMA_INTH_INT48(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT48_SHIFT)) \
                                                  &DMA_INTH_INT48_MASK)
#define DMA_INTH_INT49_MASK                     0x20000u
#define DMA_INTH_INT49_SHIFT                    17u
#define DMA_INTH_INT49_WIDTH                    1u
#define DMA_INTH_INT49(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT49_SHIFT)) \
                                                  &DMA_INTH_INT49_MASK)
#define DMA_INTH_INT50_MASK                     0x40000u
#define DMA_INTH_INT50_SHIFT                    18u
#define DMA_INTH_INT50_WIDTH                    1u
#define DMA_INTH_INT50(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT50_SHIFT)) \
                                                  &DMA_INTH_INT50_MASK)
#define DMA_INTH_INT51_MASK                     0x80000u
#define DMA_INTH_INT51_SHIFT                    19u
#define DMA_INTH_INT51_WIDTH                    1u
#define DMA_INTH_INT51(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT51_SHIFT)) \
                                                  &DMA_INTH_INT51_MASK)
#define DMA_INTH_INT52_MASK                     0x100000u
#define DMA_INTH_INT52_SHIFT                    20u
#define DMA_INTH_INT52_WIDTH                    1u
#define DMA_INTH_INT52(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT52_SHIFT)) \
                                                  &DMA_INTH_INT52_MASK)
#define DMA_INTH_INT53_MASK                     0x200000u
#define DMA_INTH_INT53_SHIFT                    21u
#define DMA_INTH_INT53_WIDTH                    1u
#define DMA_INTH_INT53(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT53_SHIFT)) \
                                                  &DMA_INTH_INT53_MASK)
#define DMA_INTH_INT54_MASK                     0x400000u
#define DMA_INTH_INT54_SHIFT                    22u
#define DMA_INTH_INT54_WIDTH                    1u
#define DMA_INTH_INT54(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT54_SHIFT)) \
                                                  &DMA_INTH_INT54_MASK)
#define DMA_INTH_INT55_MASK                     0x800000u
#define DMA_INTH_INT55_SHIFT                    23u
#define DMA_INTH_INT55_WIDTH                    1u
#define DMA_INTH_INT55(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT55_SHIFT)) \
                                                  &DMA_INTH_INT55_MASK)
#define DMA_INTH_INT56_MASK                     0x1000000u
#define DMA_INTH_INT56_SHIFT                    24u
#define DMA_INTH_INT56_WIDTH                    1u
#define DMA_INTH_INT56(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT56_SHIFT)) \
                                                  &DMA_INTH_INT56_MASK)
#define DMA_INTH_INT57_MASK                     0x2000000u
#define DMA_INTH_INT57_SHIFT                    25u
#define DMA_INTH_INT57_WIDTH                    1u
#define DMA_INTH_INT57(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT57_SHIFT)) \
                                                  &DMA_INTH_INT57_MASK)
#define DMA_INTH_INT58_MASK                     0x4000000u
#define DMA_INTH_INT58_SHIFT                    26u
#define DMA_INTH_INT58_WIDTH                    1u
#define DMA_INTH_INT58(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT58_SHIFT)) \
                                                  &DMA_INTH_INT58_MASK)
#define DMA_INTH_INT59_MASK                     0x8000000u
#define DMA_INTH_INT59_SHIFT                    27u
#define DMA_INTH_INT59_WIDTH                    1u
#define DMA_INTH_INT59(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT59_SHIFT)) \
                                                  &DMA_INTH_INT59_MASK)
#define DMA_INTH_INT60_MASK                     0x10000000u
#define DMA_INTH_INT60_SHIFT                    28u
#define DMA_INTH_INT60_WIDTH                    1u
#define DMA_INTH_INT60(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT60_SHIFT)) \
                                                  &DMA_INTH_INT60_MASK)
#define DMA_INTH_INT61_MASK                     0x20000000u
#define DMA_INTH_INT61_SHIFT                    29u
#define DMA_INTH_INT61_WIDTH                    1u
#define DMA_INTH_INT61(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT61_SHIFT)) \
                                                  &DMA_INTH_INT61_MASK)
#define DMA_INTH_INT62_MASK                     0x40000000u
#define DMA_INTH_INT62_SHIFT                    30u
#define DMA_INTH_INT62_WIDTH                    1u
#define DMA_INTH_INT62(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT62_SHIFT)) \
                                                  &DMA_INTH_INT62_MASK)
#define DMA_INTH_INT63_MASK                     0x80000000u
#define DMA_INTH_INT63_SHIFT                    31u
#define DMA_INTH_INT63_WIDTH                    1u
#define DMA_INTH_INT63(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTH_INT63_SHIFT)) \
                                                  &DMA_INTH_INT63_MASK)
/* INTL Bit Fields */
#define DMA_INTL_INT0_MASK                      0x1u
#define DMA_INTL_INT0_SHIFT                     0u
#define DMA_INTL_INT0_WIDTH                     1u
#define DMA_INTL_INT0(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT0_SHIFT)) \
                                                  &DMA_INTL_INT0_MASK)
#define DMA_INTL_INT1_MASK                      0x2u
#define DMA_INTL_INT1_SHIFT                     1u
#define DMA_INTL_INT1_WIDTH                     1u
#define DMA_INTL_INT1(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT1_SHIFT)) \
                                                  &DMA_INTL_INT1_MASK)
#define DMA_INTL_INT2_MASK                      0x4u
#define DMA_INTL_INT2_SHIFT                     2u
#define DMA_INTL_INT2_WIDTH                     1u
#define DMA_INTL_INT2(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT2_SHIFT)) \
                                                  &DMA_INTL_INT2_MASK)
#define DMA_INTL_INT3_MASK                      0x8u
#define DMA_INTL_INT3_SHIFT                     3u
#define DMA_INTL_INT3_WIDTH                     1u
#define DMA_INTL_INT3(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT3_SHIFT)) \
                                                  &DMA_INTL_INT3_MASK)
#define DMA_INTL_INT4_MASK                      0x10u
#define DMA_INTL_INT4_SHIFT                     4u
#define DMA_INTL_INT4_WIDTH                     1u
#define DMA_INTL_INT4(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT4_SHIFT)) \
                                                  &DMA_INTL_INT4_MASK)
#define DMA_INTL_INT5_MASK                      0x20u
#define DMA_INTL_INT5_SHIFT                     5u
#define DMA_INTL_INT5_WIDTH                     1u
#define DMA_INTL_INT5(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT5_SHIFT)) \
                                                  &DMA_INTL_INT5_MASK)
#define DMA_INTL_INT6_MASK                      0x40u
#define DMA_INTL_INT6_SHIFT                     6u
#define DMA_INTL_INT6_WIDTH                     1u
#define DMA_INTL_INT6(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT6_SHIFT)) \
                                                  &DMA_INTL_INT6_MASK)
#define DMA_INTL_INT7_MASK                      0x80u
#define DMA_INTL_INT7_SHIFT                     7u
#define DMA_INTL_INT7_WIDTH                     1u
#define DMA_INTL_INT7(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT7_SHIFT)) \
                                                  &DMA_INTL_INT7_MASK)
#define DMA_INTL_INT8_MASK                      0x100u
#define DMA_INTL_INT8_SHIFT                     8u
#define DMA_INTL_INT8_WIDTH                     1u
#define DMA_INTL_INT8(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT8_SHIFT)) \
                                                  &DMA_INTL_INT8_MASK)
#define DMA_INTL_INT9_MASK                      0x200u
#define DMA_INTL_INT9_SHIFT                     9u
#define DMA_INTL_INT9_WIDTH                     1u
#define DMA_INTL_INT9(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT9_SHIFT)) \
                                                  &DMA_INTL_INT9_MASK)
#define DMA_INTL_INT10_MASK                     0x400u
#define DMA_INTL_INT10_SHIFT                    10u
#define DMA_INTL_INT10_WIDTH                    1u
#define DMA_INTL_INT10(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT10_SHIFT)) \
                                                  &DMA_INTL_INT10_MASK)
#define DMA_INTL_INT11_MASK                     0x800u
#define DMA_INTL_INT11_SHIFT                    11u
#define DMA_INTL_INT11_WIDTH                    1u
#define DMA_INTL_INT11(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT11_SHIFT)) \
                                                  &DMA_INTL_INT11_MASK)
#define DMA_INTL_INT12_MASK                     0x1000u
#define DMA_INTL_INT12_SHIFT                    12u
#define DMA_INTL_INT12_WIDTH                    1u
#define DMA_INTL_INT12(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT12_SHIFT)) \
                                                  &DMA_INTL_INT12_MASK)
#define DMA_INTL_INT13_MASK                     0x2000u
#define DMA_INTL_INT13_SHIFT                    13u
#define DMA_INTL_INT13_WIDTH                    1u
#define DMA_INTL_INT13(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT13_SHIFT)) \
                                                  &DMA_INTL_INT13_MASK)
#define DMA_INTL_INT14_MASK                     0x4000u
#define DMA_INTL_INT14_SHIFT                    14u
#define DMA_INTL_INT14_WIDTH                    1u
#define DMA_INTL_INT14(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT14_SHIFT)) \
                                                  &DMA_INTL_INT14_MASK)
#define DMA_INTL_INT15_MASK                     0x8000u
#define DMA_INTL_INT15_SHIFT                    15u
#define DMA_INTL_INT15_WIDTH                    1u
#define DMA_INTL_INT15(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT15_SHIFT)) \
                                                  &DMA_INTL_INT15_MASK)
#define DMA_INTL_INT16_MASK                     0x10000u
#define DMA_INTL_INT16_SHIFT                    16u
#define DMA_INTL_INT16_WIDTH                    1u
#define DMA_INTL_INT16(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT16_SHIFT)) \
                                                  &DMA_INTL_INT16_MASK)
#define DMA_INTL_INT17_MASK                     0x20000u
#define DMA_INTL_INT17_SHIFT                    17u
#define DMA_INTL_INT17_WIDTH                    1u
#define DMA_INTL_INT17(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT17_SHIFT)) \
                                                  &DMA_INTL_INT17_MASK)
#define DMA_INTL_INT18_MASK                     0x40000u
#define DMA_INTL_INT18_SHIFT                    18u
#define DMA_INTL_INT18_WIDTH                    1u
#define DMA_INTL_INT18(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT18_SHIFT)) \
                                                  &DMA_INTL_INT18_MASK)
#define DMA_INTL_INT19_MASK                     0x80000u
#define DMA_INTL_INT19_SHIFT                    19u
#define DMA_INTL_INT19_WIDTH                    1u
#define DMA_INTL_INT19(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT19_SHIFT)) \
                                                  &DMA_INTL_INT19_MASK)
#define DMA_INTL_INT20_MASK                     0x100000u
#define DMA_INTL_INT20_SHIFT                    20u
#define DMA_INTL_INT20_WIDTH                    1u
#define DMA_INTL_INT20(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT20_SHIFT)) \
                                                  &DMA_INTL_INT20_MASK)
#define DMA_INTL_INT21_MASK                     0x200000u
#define DMA_INTL_INT21_SHIFT                    21u
#define DMA_INTL_INT21_WIDTH                    1u
#define DMA_INTL_INT21(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT21_SHIFT)) \
                                                  &DMA_INTL_INT21_MASK)
#define DMA_INTL_INT22_MASK                     0x400000u
#define DMA_INTL_INT22_SHIFT                    22u
#define DMA_INTL_INT22_WIDTH                    1u
#define DMA_INTL_INT22(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT22_SHIFT)) \
                                                  &DMA_INTL_INT22_MASK)
#define DMA_INTL_INT23_MASK                     0x800000u
#define DMA_INTL_INT23_SHIFT                    23u
#define DMA_INTL_INT23_WIDTH                    1u
#define DMA_INTL_INT23(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT23_SHIFT)) \
                                                  &DMA_INTL_INT23_MASK)
#define DMA_INTL_INT24_MASK                     0x1000000u
#define DMA_INTL_INT24_SHIFT                    24u
#define DMA_INTL_INT24_WIDTH                    1u
#define DMA_INTL_INT24(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT24_SHIFT)) \
                                                  &DMA_INTL_INT24_MASK)
#define DMA_INTL_INT25_MASK                     0x2000000u
#define DMA_INTL_INT25_SHIFT                    25u
#define DMA_INTL_INT25_WIDTH                    1u
#define DMA_INTL_INT25(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT25_SHIFT)) \
                                                  &DMA_INTL_INT25_MASK)
#define DMA_INTL_INT26_MASK                     0x4000000u
#define DMA_INTL_INT26_SHIFT                    26u
#define DMA_INTL_INT26_WIDTH                    1u
#define DMA_INTL_INT26(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT26_SHIFT)) \
                                                  &DMA_INTL_INT26_MASK)
#define DMA_INTL_INT27_MASK                     0x8000000u
#define DMA_INTL_INT27_SHIFT                    27u
#define DMA_INTL_INT27_WIDTH                    1u
#define DMA_INTL_INT27(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT27_SHIFT)) \
                                                  &DMA_INTL_INT27_MASK)
#define DMA_INTL_INT28_MASK                     0x10000000u
#define DMA_INTL_INT28_SHIFT                    28u
#define DMA_INTL_INT28_WIDTH                    1u
#define DMA_INTL_INT28(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT28_SHIFT)) \
                                                  &DMA_INTL_INT28_MASK)
#define DMA_INTL_INT29_MASK                     0x20000000u
#define DMA_INTL_INT29_SHIFT                    29u
#define DMA_INTL_INT29_WIDTH                    1u
#define DMA_INTL_INT29(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT29_SHIFT)) \
                                                  &DMA_INTL_INT29_MASK)
#define DMA_INTL_INT30_MASK                     0x40000000u
#define DMA_INTL_INT30_SHIFT                    30u
#define DMA_INTL_INT30_WIDTH                    1u
#define DMA_INTL_INT30(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT30_SHIFT)) \
                                                  &DMA_INTL_INT30_MASK)
#define DMA_INTL_INT31_MASK                     0x80000000u
#define DMA_INTL_INT31_SHIFT                    31u
#define DMA_INTL_INT31_WIDTH                    1u
#define DMA_INTL_INT31(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_INTL_INT31_SHIFT)) \
                                                  &DMA_INTL_INT31_MASK)
/* ERRH Bit Fields */
#define DMA_ERRH_ERR32_MASK                     0x1u
#define DMA_ERRH_ERR32_SHIFT                    0u
#define DMA_ERRH_ERR32_WIDTH                    1u
#define DMA_ERRH_ERR32(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR32_SHIFT)) \
                                                  &DMA_ERRH_ERR32_MASK)
#define DMA_ERRH_ERR33_MASK                     0x2u
#define DMA_ERRH_ERR33_SHIFT                    1u
#define DMA_ERRH_ERR33_WIDTH                    1u
#define DMA_ERRH_ERR33(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR33_SHIFT)) \
                                                  &DMA_ERRH_ERR33_MASK)
#define DMA_ERRH_ERR34_MASK                     0x4u
#define DMA_ERRH_ERR34_SHIFT                    2u
#define DMA_ERRH_ERR34_WIDTH                    1u
#define DMA_ERRH_ERR34(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR34_SHIFT)) \
                                                  &DMA_ERRH_ERR34_MASK)
#define DMA_ERRH_ERR35_MASK                     0x8u
#define DMA_ERRH_ERR35_SHIFT                    3u
#define DMA_ERRH_ERR35_WIDTH                    1u
#define DMA_ERRH_ERR35(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR35_SHIFT)) \
                                                  &DMA_ERRH_ERR35_MASK)
#define DMA_ERRH_ERR36_MASK                     0x10u
#define DMA_ERRH_ERR36_SHIFT                    4u
#define DMA_ERRH_ERR36_WIDTH                    1u
#define DMA_ERRH_ERR36(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR36_SHIFT)) \
                                                  &DMA_ERRH_ERR36_MASK)
#define DMA_ERRH_ERR37_MASK                     0x20u
#define DMA_ERRH_ERR37_SHIFT                    5u
#define DMA_ERRH_ERR37_WIDTH                    1u
#define DMA_ERRH_ERR37(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR37_SHIFT)) \
                                                  &DMA_ERRH_ERR37_MASK)
#define DMA_ERRH_ERR38_MASK                     0x40u
#define DMA_ERRH_ERR38_SHIFT                    6u
#define DMA_ERRH_ERR38_WIDTH                    1u
#define DMA_ERRH_ERR38(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR38_SHIFT)) \
                                                  &DMA_ERRH_ERR38_MASK)
#define DMA_ERRH_ERR39_MASK                     0x80u
#define DMA_ERRH_ERR39_SHIFT                    7u
#define DMA_ERRH_ERR39_WIDTH                    1u
#define DMA_ERRH_ERR39(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR39_SHIFT)) \
                                                  &DMA_ERRH_ERR39_MASK)
#define DMA_ERRH_ERR40_MASK                     0x100u
#define DMA_ERRH_ERR40_SHIFT                    8u
#define DMA_ERRH_ERR40_WIDTH                    1u
#define DMA_ERRH_ERR40(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR40_SHIFT)) \
                                                  &DMA_ERRH_ERR40_MASK)
#define DMA_ERRH_ERR41_MASK                     0x200u
#define DMA_ERRH_ERR41_SHIFT                    9u
#define DMA_ERRH_ERR41_WIDTH                    1u
#define DMA_ERRH_ERR41(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR41_SHIFT)) \
                                                  &DMA_ERRH_ERR41_MASK)
#define DMA_ERRH_ERR42_MASK                     0x400u
#define DMA_ERRH_ERR42_SHIFT                    10u
#define DMA_ERRH_ERR42_WIDTH                    1u
#define DMA_ERRH_ERR42(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR42_SHIFT)) \
                                                  &DMA_ERRH_ERR42_MASK)
#define DMA_ERRH_ERR43_MASK                     0x800u
#define DMA_ERRH_ERR43_SHIFT                    11u
#define DMA_ERRH_ERR43_WIDTH                    1u
#define DMA_ERRH_ERR43(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR43_SHIFT)) \
                                                  &DMA_ERRH_ERR43_MASK)
#define DMA_ERRH_ERR44_MASK                     0x1000u
#define DMA_ERRH_ERR44_SHIFT                    12u
#define DMA_ERRH_ERR44_WIDTH                    1u
#define DMA_ERRH_ERR44(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR44_SHIFT)) \
                                                  &DMA_ERRH_ERR44_MASK)
#define DMA_ERRH_ERR45_MASK                     0x2000u
#define DMA_ERRH_ERR45_SHIFT                    13u
#define DMA_ERRH_ERR45_WIDTH                    1u
#define DMA_ERRH_ERR45(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR45_SHIFT)) \
                                                  &DMA_ERRH_ERR45_MASK)
#define DMA_ERRH_ERR46_MASK                     0x4000u
#define DMA_ERRH_ERR46_SHIFT                    14u
#define DMA_ERRH_ERR46_WIDTH                    1u
#define DMA_ERRH_ERR46(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR46_SHIFT)) \
                                                  &DMA_ERRH_ERR46_MASK)
#define DMA_ERRH_ERR47_MASK                     0x8000u
#define DMA_ERRH_ERR47_SHIFT                    15u
#define DMA_ERRH_ERR47_WIDTH                    1u
#define DMA_ERRH_ERR47(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR47_SHIFT)) \
                                                  &DMA_ERRH_ERR47_MASK)
#define DMA_ERRH_ERR48_MASK                     0x10000u
#define DMA_ERRH_ERR48_SHIFT                    16u
#define DMA_ERRH_ERR48_WIDTH                    1u
#define DMA_ERRH_ERR48(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR48_SHIFT)) \
                                                  &DMA_ERRH_ERR48_MASK)
#define DMA_ERRH_ERR49_MASK                     0x20000u
#define DMA_ERRH_ERR49_SHIFT                    17u
#define DMA_ERRH_ERR49_WIDTH                    1u
#define DMA_ERRH_ERR49(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR49_SHIFT)) \
                                                  &DMA_ERRH_ERR49_MASK)
#define DMA_ERRH_ERR50_MASK                     0x40000u
#define DMA_ERRH_ERR50_SHIFT                    18u
#define DMA_ERRH_ERR50_WIDTH                    1u
#define DMA_ERRH_ERR50(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR50_SHIFT)) \
                                                  &DMA_ERRH_ERR50_MASK)
#define DMA_ERRH_ERR51_MASK                     0x80000u
#define DMA_ERRH_ERR51_SHIFT                    19u
#define DMA_ERRH_ERR51_WIDTH                    1u
#define DMA_ERRH_ERR51(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR51_SHIFT)) \
                                                  &DMA_ERRH_ERR51_MASK)
#define DMA_ERRH_ERR52_MASK                     0x100000u
#define DMA_ERRH_ERR52_SHIFT                    20u
#define DMA_ERRH_ERR52_WIDTH                    1u
#define DMA_ERRH_ERR52(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR52_SHIFT)) \
                                                  &DMA_ERRH_ERR52_MASK)
#define DMA_ERRH_ERR53_MASK                     0x200000u
#define DMA_ERRH_ERR53_SHIFT                    21u
#define DMA_ERRH_ERR53_WIDTH                    1u
#define DMA_ERRH_ERR53(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR53_SHIFT)) \
                                                  &DMA_ERRH_ERR53_MASK)
#define DMA_ERRH_ERR54_MASK                     0x400000u
#define DMA_ERRH_ERR54_SHIFT                    22u
#define DMA_ERRH_ERR54_WIDTH                    1u
#define DMA_ERRH_ERR54(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR54_SHIFT)) \
                                                  &DMA_ERRH_ERR54_MASK)
#define DMA_ERRH_ERR55_MASK                     0x800000u
#define DMA_ERRH_ERR55_SHIFT                    23u
#define DMA_ERRH_ERR55_WIDTH                    1u
#define DMA_ERRH_ERR55(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR55_SHIFT)) \
                                                  &DMA_ERRH_ERR55_MASK)
#define DMA_ERRH_ERR56_MASK                     0x1000000u
#define DMA_ERRH_ERR56_SHIFT                    24u
#define DMA_ERRH_ERR56_WIDTH                    1u
#define DMA_ERRH_ERR56(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR56_SHIFT)) \
                                                  &DMA_ERRH_ERR56_MASK)
#define DMA_ERRH_ERR57_MASK                     0x2000000u
#define DMA_ERRH_ERR57_SHIFT                    25u
#define DMA_ERRH_ERR57_WIDTH                    1u
#define DMA_ERRH_ERR57(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR57_SHIFT)) \
                                                  &DMA_ERRH_ERR57_MASK)
#define DMA_ERRH_ERR58_MASK                     0x4000000u
#define DMA_ERRH_ERR58_SHIFT                    26u
#define DMA_ERRH_ERR58_WIDTH                    1u
#define DMA_ERRH_ERR58(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR58_SHIFT)) \
                                                  &DMA_ERRH_ERR58_MASK)
#define DMA_ERRH_ERR59_MASK                     0x8000000u
#define DMA_ERRH_ERR59_SHIFT                    27u
#define DMA_ERRH_ERR59_WIDTH                    1u
#define DMA_ERRH_ERR59(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR59_SHIFT)) \
                                                  &DMA_ERRH_ERR59_MASK)
#define DMA_ERRH_ERR60_MASK                     0x10000000u
#define DMA_ERRH_ERR60_SHIFT                    28u
#define DMA_ERRH_ERR60_WIDTH                    1u
#define DMA_ERRH_ERR60(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR60_SHIFT)) \
                                                  &DMA_ERRH_ERR60_MASK)
#define DMA_ERRH_ERR61_MASK                     0x20000000u
#define DMA_ERRH_ERR61_SHIFT                    29u
#define DMA_ERRH_ERR61_WIDTH                    1u
#define DMA_ERRH_ERR61(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR61_SHIFT)) \
                                                  &DMA_ERRH_ERR61_MASK)
#define DMA_ERRH_ERR62_MASK                     0x40000000u
#define DMA_ERRH_ERR62_SHIFT                    30u
#define DMA_ERRH_ERR62_WIDTH                    1u
#define DMA_ERRH_ERR62(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR62_SHIFT)) \
                                                  &DMA_ERRH_ERR62_MASK)
#define DMA_ERRH_ERR63_MASK                     0x80000000u
#define DMA_ERRH_ERR63_SHIFT                    31u
#define DMA_ERRH_ERR63_WIDTH                    1u
#define DMA_ERRH_ERR63(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRH_ERR63_SHIFT)) \
                                                  &DMA_ERRH_ERR63_MASK)
/* ERRL Bit Fields */
#define DMA_ERRL_ERR0_MASK                      0x1u
#define DMA_ERRL_ERR0_SHIFT                     0u
#define DMA_ERRL_ERR0_WIDTH                     1u
#define DMA_ERRL_ERR0(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR0_SHIFT)) \
                                                  &DMA_ERRL_ERR0_MASK)
#define DMA_ERRL_ERR1_MASK                      0x2u
#define DMA_ERRL_ERR1_SHIFT                     1u
#define DMA_ERRL_ERR1_WIDTH                     1u
#define DMA_ERRL_ERR1(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR1_SHIFT)) \
                                                  &DMA_ERRL_ERR1_MASK)
#define DMA_ERRL_ERR2_MASK                      0x4u
#define DMA_ERRL_ERR2_SHIFT                     2u
#define DMA_ERRL_ERR2_WIDTH                     1u
#define DMA_ERRL_ERR2(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR2_SHIFT)) \
                                                  &DMA_ERRL_ERR2_MASK)
#define DMA_ERRL_ERR3_MASK                      0x8u
#define DMA_ERRL_ERR3_SHIFT                     3u
#define DMA_ERRL_ERR3_WIDTH                     1u
#define DMA_ERRL_ERR3(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR3_SHIFT)) \
                                                  &DMA_ERRL_ERR3_MASK)
#define DMA_ERRL_ERR4_MASK                      0x10u
#define DMA_ERRL_ERR4_SHIFT                     4u
#define DMA_ERRL_ERR4_WIDTH                     1u
#define DMA_ERRL_ERR4(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR4_SHIFT)) \
                                                  &DMA_ERRL_ERR4_MASK)
#define DMA_ERRL_ERR5_MASK                      0x20u
#define DMA_ERRL_ERR5_SHIFT                     5u
#define DMA_ERRL_ERR5_WIDTH                     1u
#define DMA_ERRL_ERR5(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR5_SHIFT)) \
                                                  &DMA_ERRL_ERR5_MASK)
#define DMA_ERRL_ERR6_MASK                      0x40u
#define DMA_ERRL_ERR6_SHIFT                     6u
#define DMA_ERRL_ERR6_WIDTH                     1u
#define DMA_ERRL_ERR6(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR6_SHIFT)) \
                                                  &DMA_ERRL_ERR6_MASK)
#define DMA_ERRL_ERR7_MASK                      0x80u
#define DMA_ERRL_ERR7_SHIFT                     7u
#define DMA_ERRL_ERR7_WIDTH                     1u
#define DMA_ERRL_ERR7(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR7_SHIFT)) \
                                                  &DMA_ERRL_ERR7_MASK)
#define DMA_ERRL_ERR8_MASK                      0x100u
#define DMA_ERRL_ERR8_SHIFT                     8u
#define DMA_ERRL_ERR8_WIDTH                     1u
#define DMA_ERRL_ERR8(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR8_SHIFT)) \
                                                  &DMA_ERRL_ERR8_MASK)
#define DMA_ERRL_ERR9_MASK                      0x200u
#define DMA_ERRL_ERR9_SHIFT                     9u
#define DMA_ERRL_ERR9_WIDTH                     1u
#define DMA_ERRL_ERR9(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR9_SHIFT)) \
                                                  &DMA_ERRL_ERR9_MASK)
#define DMA_ERRL_ERR10_MASK                     0x400u
#define DMA_ERRL_ERR10_SHIFT                    10u
#define DMA_ERRL_ERR10_WIDTH                    1u
#define DMA_ERRL_ERR10(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR10_SHIFT)) \
                                                  &DMA_ERRL_ERR10_MASK)
#define DMA_ERRL_ERR11_MASK                     0x800u
#define DMA_ERRL_ERR11_SHIFT                    11u
#define DMA_ERRL_ERR11_WIDTH                    1u
#define DMA_ERRL_ERR11(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR11_SHIFT)) \
                                                  &DMA_ERRL_ERR11_MASK)
#define DMA_ERRL_ERR12_MASK                     0x1000u
#define DMA_ERRL_ERR12_SHIFT                    12u
#define DMA_ERRL_ERR12_WIDTH                    1u
#define DMA_ERRL_ERR12(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR12_SHIFT)) \
                                                  &DMA_ERRL_ERR12_MASK)
#define DMA_ERRL_ERR13_MASK                     0x2000u
#define DMA_ERRL_ERR13_SHIFT                    13u
#define DMA_ERRL_ERR13_WIDTH                    1u
#define DMA_ERRL_ERR13(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR13_SHIFT)) \
                                                  &DMA_ERRL_ERR13_MASK)
#define DMA_ERRL_ERR14_MASK                     0x4000u
#define DMA_ERRL_ERR14_SHIFT                    14u
#define DMA_ERRL_ERR14_WIDTH                    1u
#define DMA_ERRL_ERR14(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR14_SHIFT)) \
                                                  &DMA_ERRL_ERR14_MASK)
#define DMA_ERRL_ERR15_MASK                     0x8000u
#define DMA_ERRL_ERR15_SHIFT                    15u
#define DMA_ERRL_ERR15_WIDTH                    1u
#define DMA_ERRL_ERR15(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR15_SHIFT)) \
                                                  &DMA_ERRL_ERR15_MASK)
#define DMA_ERRL_ERR16_MASK                     0x10000u
#define DMA_ERRL_ERR16_SHIFT                    16u
#define DMA_ERRL_ERR16_WIDTH                    1u
#define DMA_ERRL_ERR16(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR16_SHIFT)) \
                                                  &DMA_ERRL_ERR16_MASK)
#define DMA_ERRL_ERR17_MASK                     0x20000u
#define DMA_ERRL_ERR17_SHIFT                    17u
#define DMA_ERRL_ERR17_WIDTH                    1u
#define DMA_ERRL_ERR17(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR17_SHIFT)) \
                                                  &DMA_ERRL_ERR17_MASK)
#define DMA_ERRL_ERR18_MASK                     0x40000u
#define DMA_ERRL_ERR18_SHIFT                    18u
#define DMA_ERRL_ERR18_WIDTH                    1u
#define DMA_ERRL_ERR18(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR18_SHIFT)) \
                                                  &DMA_ERRL_ERR18_MASK)
#define DMA_ERRL_ERR19_MASK                     0x80000u
#define DMA_ERRL_ERR19_SHIFT                    19u
#define DMA_ERRL_ERR19_WIDTH                    1u
#define DMA_ERRL_ERR19(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR19_SHIFT)) \
                                                  &DMA_ERRL_ERR19_MASK)
#define DMA_ERRL_ERR20_MASK                     0x100000u
#define DMA_ERRL_ERR20_SHIFT                    20u
#define DMA_ERRL_ERR20_WIDTH                    1u
#define DMA_ERRL_ERR20(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR20_SHIFT)) \
                                                  &DMA_ERRL_ERR20_MASK)
#define DMA_ERRL_ERR21_MASK                     0x200000u
#define DMA_ERRL_ERR21_SHIFT                    21u
#define DMA_ERRL_ERR21_WIDTH                    1u
#define DMA_ERRL_ERR21(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR21_SHIFT)) \
                                                  &DMA_ERRL_ERR21_MASK)
#define DMA_ERRL_ERR22_MASK                     0x400000u
#define DMA_ERRL_ERR22_SHIFT                    22u
#define DMA_ERRL_ERR22_WIDTH                    1u
#define DMA_ERRL_ERR22(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR22_SHIFT)) \
                                                  &DMA_ERRL_ERR22_MASK)
#define DMA_ERRL_ERR23_MASK                     0x800000u
#define DMA_ERRL_ERR23_SHIFT                    23u
#define DMA_ERRL_ERR23_WIDTH                    1u
#define DMA_ERRL_ERR23(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR23_SHIFT)) \
                                                  &DMA_ERRL_ERR23_MASK)
#define DMA_ERRL_ERR24_MASK                     0x1000000u
#define DMA_ERRL_ERR24_SHIFT                    24u
#define DMA_ERRL_ERR24_WIDTH                    1u
#define DMA_ERRL_ERR24(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR24_SHIFT)) \
                                                  &DMA_ERRL_ERR24_MASK)
#define DMA_ERRL_ERR25_MASK                     0x2000000u
#define DMA_ERRL_ERR25_SHIFT                    25u
#define DMA_ERRL_ERR25_WIDTH                    1u
#define DMA_ERRL_ERR25(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR25_SHIFT)) \
                                                  &DMA_ERRL_ERR25_MASK)
#define DMA_ERRL_ERR26_MASK                     0x4000000u
#define DMA_ERRL_ERR26_SHIFT                    26u
#define DMA_ERRL_ERR26_WIDTH                    1u
#define DMA_ERRL_ERR26(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR26_SHIFT)) \
                                                  &DMA_ERRL_ERR26_MASK)
#define DMA_ERRL_ERR27_MASK                     0x8000000u
#define DMA_ERRL_ERR27_SHIFT                    27u
#define DMA_ERRL_ERR27_WIDTH                    1u
#define DMA_ERRL_ERR27(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR27_SHIFT)) \
                                                  &DMA_ERRL_ERR27_MASK)
#define DMA_ERRL_ERR28_MASK                     0x10000000u
#define DMA_ERRL_ERR28_SHIFT                    28u
#define DMA_ERRL_ERR28_WIDTH                    1u
#define DMA_ERRL_ERR28(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR28_SHIFT)) \
                                                  &DMA_ERRL_ERR28_MASK)
#define DMA_ERRL_ERR29_MASK                     0x20000000u
#define DMA_ERRL_ERR29_SHIFT                    29u
#define DMA_ERRL_ERR29_WIDTH                    1u
#define DMA_ERRL_ERR29(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR29_SHIFT)) \
                                                  &DMA_ERRL_ERR29_MASK)
#define DMA_ERRL_ERR30_MASK                     0x40000000u
#define DMA_ERRL_ERR30_SHIFT                    30u
#define DMA_ERRL_ERR30_WIDTH                    1u
#define DMA_ERRL_ERR30(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR30_SHIFT)) \
                                                  &DMA_ERRL_ERR30_MASK)
#define DMA_ERRL_ERR31_MASK                     0x80000000u
#define DMA_ERRL_ERR31_SHIFT                    31u
#define DMA_ERRL_ERR31_WIDTH                    1u
#define DMA_ERRL_ERR31(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_ERRL_ERR31_SHIFT)) \
                                                  &DMA_ERRL_ERR31_MASK)
/* HRSH Bit Fields */
#define DMA_HRSH_HRS32_MASK                     0x1u
#define DMA_HRSH_HRS32_SHIFT                    0u
#define DMA_HRSH_HRS32_WIDTH                    1u
#define DMA_HRSH_HRS32(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS32_SHIFT)) \
                                                  &DMA_HRSH_HRS32_MASK)
#define DMA_HRSH_HRS33_MASK                     0x2u
#define DMA_HRSH_HRS33_SHIFT                    1u
#define DMA_HRSH_HRS33_WIDTH                    1u
#define DMA_HRSH_HRS33(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS33_SHIFT)) \
                                                  &DMA_HRSH_HRS33_MASK)
#define DMA_HRSH_HRS34_MASK                     0x4u
#define DMA_HRSH_HRS34_SHIFT                    2u
#define DMA_HRSH_HRS34_WIDTH                    1u
#define DMA_HRSH_HRS34(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS34_SHIFT)) \
                                                  &DMA_HRSH_HRS34_MASK)
#define DMA_HRSH_HRS35_MASK                     0x8u
#define DMA_HRSH_HRS35_SHIFT                    3u
#define DMA_HRSH_HRS35_WIDTH                    1u
#define DMA_HRSH_HRS35(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS35_SHIFT)) \
                                                  &DMA_HRSH_HRS35_MASK)
#define DMA_HRSH_HRS36_MASK                     0x10u
#define DMA_HRSH_HRS36_SHIFT                    4u
#define DMA_HRSH_HRS36_WIDTH                    1u
#define DMA_HRSH_HRS36(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS36_SHIFT)) \
                                                  &DMA_HRSH_HRS36_MASK)
#define DMA_HRSH_HRS37_MASK                     0x20u
#define DMA_HRSH_HRS37_SHIFT                    5u
#define DMA_HRSH_HRS37_WIDTH                    1u
#define DMA_HRSH_HRS37(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS37_SHIFT)) \
                                                  &DMA_HRSH_HRS37_MASK)
#define DMA_HRSH_HRS38_MASK                     0x40u
#define DMA_HRSH_HRS38_SHIFT                    6u
#define DMA_HRSH_HRS38_WIDTH                    1u
#define DMA_HRSH_HRS38(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS38_SHIFT)) \
                                                  &DMA_HRSH_HRS38_MASK)
#define DMA_HRSH_HRS39_MASK                     0x80u
#define DMA_HRSH_HRS39_SHIFT                    7u
#define DMA_HRSH_HRS39_WIDTH                    1u
#define DMA_HRSH_HRS39(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS39_SHIFT)) \
                                                  &DMA_HRSH_HRS39_MASK)
#define DMA_HRSH_HRS40_MASK                     0x100u
#define DMA_HRSH_HRS40_SHIFT                    8u
#define DMA_HRSH_HRS40_WIDTH                    1u
#define DMA_HRSH_HRS40(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS40_SHIFT)) \
                                                  &DMA_HRSH_HRS40_MASK)
#define DMA_HRSH_HRS41_MASK                     0x200u
#define DMA_HRSH_HRS41_SHIFT                    9u
#define DMA_HRSH_HRS41_WIDTH                    1u
#define DMA_HRSH_HRS41(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS41_SHIFT)) \
                                                  &DMA_HRSH_HRS41_MASK)
#define DMA_HRSH_HRS42_MASK                     0x400u
#define DMA_HRSH_HRS42_SHIFT                    10u
#define DMA_HRSH_HRS42_WIDTH                    1u
#define DMA_HRSH_HRS42(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS42_SHIFT)) \
                                                  &DMA_HRSH_HRS42_MASK)
#define DMA_HRSH_HRS43_MASK                     0x800u
#define DMA_HRSH_HRS43_SHIFT                    11u
#define DMA_HRSH_HRS43_WIDTH                    1u
#define DMA_HRSH_HRS43(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS43_SHIFT)) \
                                                  &DMA_HRSH_HRS43_MASK)
#define DMA_HRSH_HRS44_MASK                     0x1000u
#define DMA_HRSH_HRS44_SHIFT                    12u
#define DMA_HRSH_HRS44_WIDTH                    1u
#define DMA_HRSH_HRS44(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS44_SHIFT)) \
                                                  &DMA_HRSH_HRS44_MASK)
#define DMA_HRSH_HRS45_MASK                     0x2000u
#define DMA_HRSH_HRS45_SHIFT                    13u
#define DMA_HRSH_HRS45_WIDTH                    1u
#define DMA_HRSH_HRS45(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS45_SHIFT)) \
                                                  &DMA_HRSH_HRS45_MASK)
#define DMA_HRSH_HRS46_MASK                     0x4000u
#define DMA_HRSH_HRS46_SHIFT                    14u
#define DMA_HRSH_HRS46_WIDTH                    1u
#define DMA_HRSH_HRS46(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS46_SHIFT)) \
                                                  &DMA_HRSH_HRS46_MASK)
#define DMA_HRSH_HRS47_MASK                     0x8000u
#define DMA_HRSH_HRS47_SHIFT                    15u
#define DMA_HRSH_HRS47_WIDTH                    1u
#define DMA_HRSH_HRS47(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS47_SHIFT)) \
                                                  &DMA_HRSH_HRS47_MASK)
#define DMA_HRSH_HRS48_MASK                     0x10000u
#define DMA_HRSH_HRS48_SHIFT                    16u
#define DMA_HRSH_HRS48_WIDTH                    1u
#define DMA_HRSH_HRS48(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS48_SHIFT)) \
                                                  &DMA_HRSH_HRS48_MASK)
#define DMA_HRSH_HRS49_MASK                     0x20000u
#define DMA_HRSH_HRS49_SHIFT                    17u
#define DMA_HRSH_HRS49_WIDTH                    1u
#define DMA_HRSH_HRS49(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS49_SHIFT)) \
                                                  &DMA_HRSH_HRS49_MASK)
#define DMA_HRSH_HRS50_MASK                     0x40000u
#define DMA_HRSH_HRS50_SHIFT                    18u
#define DMA_HRSH_HRS50_WIDTH                    1u
#define DMA_HRSH_HRS50(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS50_SHIFT)) \
                                                  &DMA_HRSH_HRS50_MASK)
#define DMA_HRSH_HRS51_MASK                     0x80000u
#define DMA_HRSH_HRS51_SHIFT                    19u
#define DMA_HRSH_HRS51_WIDTH                    1u
#define DMA_HRSH_HRS51(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS51_SHIFT)) \
                                                  &DMA_HRSH_HRS51_MASK)
#define DMA_HRSH_HRS52_MASK                     0x100000u
#define DMA_HRSH_HRS52_SHIFT                    20u
#define DMA_HRSH_HRS52_WIDTH                    1u
#define DMA_HRSH_HRS52(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS52_SHIFT)) \
                                                  &DMA_HRSH_HRS52_MASK)
#define DMA_HRSH_HRS53_MASK                     0x200000u
#define DMA_HRSH_HRS53_SHIFT                    21u
#define DMA_HRSH_HRS53_WIDTH                    1u
#define DMA_HRSH_HRS53(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS53_SHIFT)) \
                                                  &DMA_HRSH_HRS53_MASK)
#define DMA_HRSH_HRS54_MASK                     0x400000u
#define DMA_HRSH_HRS54_SHIFT                    22u
#define DMA_HRSH_HRS54_WIDTH                    1u
#define DMA_HRSH_HRS54(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS54_SHIFT)) \
                                                  &DMA_HRSH_HRS54_MASK)
#define DMA_HRSH_HRS55_MASK                     0x800000u
#define DMA_HRSH_HRS55_SHIFT                    23u
#define DMA_HRSH_HRS55_WIDTH                    1u
#define DMA_HRSH_HRS55(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS55_SHIFT)) \
                                                  &DMA_HRSH_HRS55_MASK)
#define DMA_HRSH_HRS56_MASK                     0x1000000u
#define DMA_HRSH_HRS56_SHIFT                    24u
#define DMA_HRSH_HRS56_WIDTH                    1u
#define DMA_HRSH_HRS56(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS56_SHIFT)) \
                                                  &DMA_HRSH_HRS56_MASK)
#define DMA_HRSH_HRS57_MASK                     0x2000000u
#define DMA_HRSH_HRS57_SHIFT                    25u
#define DMA_HRSH_HRS57_WIDTH                    1u
#define DMA_HRSH_HRS57(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS57_SHIFT)) \
                                                  &DMA_HRSH_HRS57_MASK)
#define DMA_HRSH_HRS58_MASK                     0x4000000u
#define DMA_HRSH_HRS58_SHIFT                    26u
#define DMA_HRSH_HRS58_WIDTH                    1u
#define DMA_HRSH_HRS58(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS58_SHIFT)) \
                                                  &DMA_HRSH_HRS58_MASK)
#define DMA_HRSH_HRS59_MASK                     0x8000000u
#define DMA_HRSH_HRS59_SHIFT                    27u
#define DMA_HRSH_HRS59_WIDTH                    1u
#define DMA_HRSH_HRS59(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS59_SHIFT)) \
                                                  &DMA_HRSH_HRS59_MASK)
#define DMA_HRSH_HRS60_MASK                     0x10000000u
#define DMA_HRSH_HRS60_SHIFT                    28u
#define DMA_HRSH_HRS60_WIDTH                    1u
#define DMA_HRSH_HRS60(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS60_SHIFT)) \
                                                  &DMA_HRSH_HRS60_MASK)
#define DMA_HRSH_HRS61_MASK                     0x20000000u
#define DMA_HRSH_HRS61_SHIFT                    29u
#define DMA_HRSH_HRS61_WIDTH                    1u
#define DMA_HRSH_HRS61(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS61_SHIFT)) \
                                                  &DMA_HRSH_HRS61_MASK)
#define DMA_HRSH_HRS62_MASK                     0x40000000u
#define DMA_HRSH_HRS62_SHIFT                    30u
#define DMA_HRSH_HRS62_WIDTH                    1u
#define DMA_HRSH_HRS62(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS62_SHIFT)) \
                                                  &DMA_HRSH_HRS62_MASK)
#define DMA_HRSH_HRS63_MASK                     0x80000000u
#define DMA_HRSH_HRS63_SHIFT                    31u
#define DMA_HRSH_HRS63_WIDTH                    1u
#define DMA_HRSH_HRS63(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSH_HRS63_SHIFT)) \
                                                  &DMA_HRSH_HRS63_MASK)
/* HRSL Bit Fields */
#define DMA_HRSL_HRS0_MASK                      0x1u
#define DMA_HRSL_HRS0_SHIFT                     0u
#define DMA_HRSL_HRS0_WIDTH                     1u
#define DMA_HRSL_HRS0(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS0_SHIFT)) \
                                                  &DMA_HRSL_HRS0_MASK)
#define DMA_HRSL_HRS1_MASK                      0x2u
#define DMA_HRSL_HRS1_SHIFT                     1u
#define DMA_HRSL_HRS1_WIDTH                     1u
#define DMA_HRSL_HRS1(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS1_SHIFT)) \
                                                  &DMA_HRSL_HRS1_MASK)
#define DMA_HRSL_HRS2_MASK                      0x4u
#define DMA_HRSL_HRS2_SHIFT                     2u
#define DMA_HRSL_HRS2_WIDTH                     1u
#define DMA_HRSL_HRS2(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS2_SHIFT)) \
                                                  &DMA_HRSL_HRS2_MASK)
#define DMA_HRSL_HRS3_MASK                      0x8u
#define DMA_HRSL_HRS3_SHIFT                     3u
#define DMA_HRSL_HRS3_WIDTH                     1u
#define DMA_HRSL_HRS3(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS3_SHIFT)) \
                                                  &DMA_HRSL_HRS3_MASK)
#define DMA_HRSL_HRS4_MASK                      0x10u
#define DMA_HRSL_HRS4_SHIFT                     4u
#define DMA_HRSL_HRS4_WIDTH                     1u
#define DMA_HRSL_HRS4(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS4_SHIFT)) \
                                                  &DMA_HRSL_HRS4_MASK)
#define DMA_HRSL_HRS5_MASK                      0x20u
#define DMA_HRSL_HRS5_SHIFT                     5u
#define DMA_HRSL_HRS5_WIDTH                     1u
#define DMA_HRSL_HRS5(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS5_SHIFT)) \
                                                  &DMA_HRSL_HRS5_MASK)
#define DMA_HRSL_HRS6_MASK                      0x40u
#define DMA_HRSL_HRS6_SHIFT                     6u
#define DMA_HRSL_HRS6_WIDTH                     1u
#define DMA_HRSL_HRS6(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS6_SHIFT)) \
                                                  &DMA_HRSL_HRS6_MASK)
#define DMA_HRSL_HRS7_MASK                      0x80u
#define DMA_HRSL_HRS7_SHIFT                     7u
#define DMA_HRSL_HRS7_WIDTH                     1u
#define DMA_HRSL_HRS7(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS7_SHIFT)) \
                                                  &DMA_HRSL_HRS7_MASK)
#define DMA_HRSL_HRS8_MASK                      0x100u
#define DMA_HRSL_HRS8_SHIFT                     8u
#define DMA_HRSL_HRS8_WIDTH                     1u
#define DMA_HRSL_HRS8(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS8_SHIFT)) \
                                                  &DMA_HRSL_HRS8_MASK)
#define DMA_HRSL_HRS9_MASK                      0x200u
#define DMA_HRSL_HRS9_SHIFT                     9u
#define DMA_HRSL_HRS9_WIDTH                     1u
#define DMA_HRSL_HRS9(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS9_SHIFT)) \
                                                  &DMA_HRSL_HRS9_MASK)
#define DMA_HRSL_HRS10_MASK                     0x400u
#define DMA_HRSL_HRS10_SHIFT                    10u
#define DMA_HRSL_HRS10_WIDTH                    1u
#define DMA_HRSL_HRS10(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS10_SHIFT)) \
                                                  &DMA_HRSL_HRS10_MASK)
#define DMA_HRSL_HRS11_MASK                     0x800u
#define DMA_HRSL_HRS11_SHIFT                    11u
#define DMA_HRSL_HRS11_WIDTH                    1u
#define DMA_HRSL_HRS11(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS11_SHIFT)) \
                                                  &DMA_HRSL_HRS11_MASK)
#define DMA_HRSL_HRS12_MASK                     0x1000u
#define DMA_HRSL_HRS12_SHIFT                    12u
#define DMA_HRSL_HRS12_WIDTH                    1u
#define DMA_HRSL_HRS12(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS12_SHIFT)) \
                                                  &DMA_HRSL_HRS12_MASK)
#define DMA_HRSL_HRS13_MASK                     0x2000u
#define DMA_HRSL_HRS13_SHIFT                    13u
#define DMA_HRSL_HRS13_WIDTH                    1u
#define DMA_HRSL_HRS13(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS13_SHIFT)) \
                                                  &DMA_HRSL_HRS13_MASK)
#define DMA_HRSL_HRS14_MASK                     0x4000u
#define DMA_HRSL_HRS14_SHIFT                    14u
#define DMA_HRSL_HRS14_WIDTH                    1u
#define DMA_HRSL_HRS14(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS14_SHIFT)) \
                                                  &DMA_HRSL_HRS14_MASK)
#define DMA_HRSL_HRS15_MASK                     0x8000u
#define DMA_HRSL_HRS15_SHIFT                    15u
#define DMA_HRSL_HRS15_WIDTH                    1u
#define DMA_HRSL_HRS15(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS15_SHIFT)) \
                                                  &DMA_HRSL_HRS15_MASK)
#define DMA_HRSL_HRS16_MASK                     0x10000u
#define DMA_HRSL_HRS16_SHIFT                    16u
#define DMA_HRSL_HRS16_WIDTH                    1u
#define DMA_HRSL_HRS16(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS16_SHIFT)) \
                                                  &DMA_HRSL_HRS16_MASK)
#define DMA_HRSL_HRS17_MASK                     0x20000u
#define DMA_HRSL_HRS17_SHIFT                    17u
#define DMA_HRSL_HRS17_WIDTH                    1u
#define DMA_HRSL_HRS17(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS17_SHIFT)) \
                                                  &DMA_HRSL_HRS17_MASK)
#define DMA_HRSL_HRS18_MASK                     0x40000u
#define DMA_HRSL_HRS18_SHIFT                    18u
#define DMA_HRSL_HRS18_WIDTH                    1u
#define DMA_HRSL_HRS18(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS18_SHIFT)) \
                                                  &DMA_HRSL_HRS18_MASK)
#define DMA_HRSL_HRS19_MASK                     0x80000u
#define DMA_HRSL_HRS19_SHIFT                    19u
#define DMA_HRSL_HRS19_WIDTH                    1u
#define DMA_HRSL_HRS19(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS19_SHIFT)) \
                                                  &DMA_HRSL_HRS19_MASK)
#define DMA_HRSL_HRS20_MASK                     0x100000u
#define DMA_HRSL_HRS20_SHIFT                    20u
#define DMA_HRSL_HRS20_WIDTH                    1u
#define DMA_HRSL_HRS20(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS20_SHIFT)) \
                                                  &DMA_HRSL_HRS20_MASK)
#define DMA_HRSL_HRS21_MASK                     0x200000u
#define DMA_HRSL_HRS21_SHIFT                    21u
#define DMA_HRSL_HRS21_WIDTH                    1u
#define DMA_HRSL_HRS21(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS21_SHIFT)) \
                                                  &DMA_HRSL_HRS21_MASK)
#define DMA_HRSL_HRS22_MASK                     0x400000u
#define DMA_HRSL_HRS22_SHIFT                    22u
#define DMA_HRSL_HRS22_WIDTH                    1u
#define DMA_HRSL_HRS22(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS22_SHIFT)) \
                                                  &DMA_HRSL_HRS22_MASK)
#define DMA_HRSL_HRS23_MASK                     0x800000u
#define DMA_HRSL_HRS23_SHIFT                    23u
#define DMA_HRSL_HRS23_WIDTH                    1u
#define DMA_HRSL_HRS23(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS23_SHIFT)) \
                                                  &DMA_HRSL_HRS23_MASK)
#define DMA_HRSL_HRS24_MASK                     0x1000000u
#define DMA_HRSL_HRS24_SHIFT                    24u
#define DMA_HRSL_HRS24_WIDTH                    1u
#define DMA_HRSL_HRS24(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS24_SHIFT)) \
                                                  &DMA_HRSL_HRS24_MASK)
#define DMA_HRSL_HRS25_MASK                     0x2000000u
#define DMA_HRSL_HRS25_SHIFT                    25u
#define DMA_HRSL_HRS25_WIDTH                    1u
#define DMA_HRSL_HRS25(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS25_SHIFT)) \
                                                  &DMA_HRSL_HRS25_MASK)
#define DMA_HRSL_HRS26_MASK                     0x4000000u
#define DMA_HRSL_HRS26_SHIFT                    26u
#define DMA_HRSL_HRS26_WIDTH                    1u
#define DMA_HRSL_HRS26(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS26_SHIFT)) \
                                                  &DMA_HRSL_HRS26_MASK)
#define DMA_HRSL_HRS27_MASK                     0x8000000u
#define DMA_HRSL_HRS27_SHIFT                    27u
#define DMA_HRSL_HRS27_WIDTH                    1u
#define DMA_HRSL_HRS27(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS27_SHIFT)) \
                                                  &DMA_HRSL_HRS27_MASK)
#define DMA_HRSL_HRS28_MASK                     0x10000000u
#define DMA_HRSL_HRS28_SHIFT                    28u
#define DMA_HRSL_HRS28_WIDTH                    1u
#define DMA_HRSL_HRS28(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS28_SHIFT)) \
                                                  &DMA_HRSL_HRS28_MASK)
#define DMA_HRSL_HRS29_MASK                     0x20000000u
#define DMA_HRSL_HRS29_SHIFT                    29u
#define DMA_HRSL_HRS29_WIDTH                    1u
#define DMA_HRSL_HRS29(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS29_SHIFT)) \
                                                  &DMA_HRSL_HRS29_MASK)
#define DMA_HRSL_HRS30_MASK                     0x40000000u
#define DMA_HRSL_HRS30_SHIFT                    30u
#define DMA_HRSL_HRS30_WIDTH                    1u
#define DMA_HRSL_HRS30(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS30_SHIFT)) \
                                                  &DMA_HRSL_HRS30_MASK)
#define DMA_HRSL_HRS31_MASK                     0x80000000u
#define DMA_HRSL_HRS31_SHIFT                    31u
#define DMA_HRSL_HRS31_WIDTH                    1u
#define DMA_HRSL_HRS31(x)                       (((uint32)(((uint32)(x)) \
                                                  << DMA_HRSL_HRS31_SHIFT)) \
                                                  &DMA_HRSL_HRS31_MASK)
/* GPOR Bit Fields */
#define DMA_GPOR_GPOR_MASK                      0xFFFFFFFFu
#define DMA_GPOR_GPOR_SHIFT                     0u
#define DMA_GPOR_GPOR_WIDTH                     32u
#define DMA_GPOR_GPOR(x)                        (((uint32)(((uint32)(x)) \
                                                  << DMA_GPOR_GPOR_SHIFT)) \
                                                  &DMA_GPOR_GPOR_MASK)
/* DCHPRI Bit Fields */
#define DMA_DCHPRI_CHPRI_MASK                   0xFu
#define DMA_DCHPRI_CHPRI_SHIFT                  0u
#define DMA_DCHPRI_CHPRI_WIDTH                  4u
#define DMA_DCHPRI_CHPRI(x)                     (uint8)(((((uint32)(x)) \
                                                  << DMA_DCHPRI_CHPRI_SHIFT)) \
                                                  &DMA_DCHPRI_CHPRI_MASK)
#define DMA_DCHPRI_GRPPRI_MASK                  0x30u
#define DMA_DCHPRI_GRPPRI_SHIFT                 4u
#define DMA_DCHPRI_GRPPRI_WIDTH                 2u
#define DMA_DCHPRI_GRPPRI(x)                    (((uint8)(((uint8)(x)) \
                                                  << DMA_DCHPRI_GRPPRI_SHIFT)) \
                                                  &DMA_DCHPRI_GRPPRI_MASK)
#define DMA_DCHPRI_DPA_MASK                     0x40u
#define DMA_DCHPRI_DPA_SHIFT                    6u
#define DMA_DCHPRI_DPA_WIDTH                    1u
#define DMA_DCHPRI_DPA(x)                       (((uint8)(((uint8)(x)) \
                                                  << DMA_DCHPRI_DPA_SHIFT)) \
                                                  &DMA_DCHPRI_DPA_MASK)
#define DMA_DCHPRI_ECP_MASK                     0x80u
#define DMA_DCHPRI_ECP_SHIFT                    7u
#define DMA_DCHPRI_ECP_WIDTH                    1u
#define DMA_DCHPRI_ECP(x)                       (((uint8)(((uint8)(x)) \
                                                  << DMA_DCHPRI_ECP_SHIFT)) \
                                                  &DMA_DCHPRI_ECP_MASK)

/* MASTER ID */
#define DMA_DCHMID_MID_MASK                   0xFu
#define DMA_DCHMID_MID_SHIFT                  0u
#define DMA_DCHMID_MID_WIDTH                  4u
#define DMA_DCHMID_MID(x)                     (uint8)(((((uint32)(x)) \
                                                  << DMA_DCHMID_MID_SHIFT)) \
                                                  &DMA_DCHMID_MID_MASK)
#define DMA_DCHMID_PAL_MASK                     0x40u
#define DMA_DCHMID_PAL_SHIFT                    6u
#define DMA_DCHMID_PAL_WIDTH                    1u
#define DMA_DCHMID_PAL(x)                       (((uint8)(((uint8)(x)) \
                                                  << DMA_DCHMID_PAL_SHIFT)) \
                                                  &DMA_DCHMID_PAL_MASK)
#define DMA_DCHMID_EMI_MASK                     0x80u
#define DMA_DCHMID_EMI_SHIFT                    7u
#define DMA_DCHMID_EMI_WIDTH                    1u
#define DMA_DCHMID_EMI(x)                       (((uint8)(((uint8)(x)) \
                                                  << DMA_DCHMID_EMI_SHIFT)) \
                                                  &DMA_DCHMID_EMI_MASK)

/* TCD_SADDR Bit Fields */
#define DMA_TCD_SADDR_SADDR_MASK                0xFFFFFFFFu
#define DMA_TCD_SADDR_SADDR_SHIFT               0u
#define DMA_TCD_SADDR_SADDR_WIDTH               32u
#define DMA_TCD_SADDR_SADDR(x)                  (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_SADDR_SADDR_SHIFT)) \
                                                  &DMA_TCD_SADDR_SADDR_MASK)
/* TCD_ATTR Bit Fields */
#define DMA_TCD_ATTR_DSIZE_MASK                 0x7U
#define DMA_TCD_ATTR_DSIZE_SHIFT                0u
#define DMA_TCD_ATTR_DSIZE_WIDTH                3u
#define DMA_TCD_ATTR_DSIZE(x)                   (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_ATTR_DSIZE_SHIFT)) \
                                                  &DMA_TCD_ATTR_DSIZE_MASK)
#define DMA_TCD_ATTR_DMOD_MASK                  0xF8u
#define DMA_TCD_ATTR_DMOD_SHIFT                 3u
#define DMA_TCD_ATTR_DMOD_WIDTH                 5u
#define DMA_TCD_ATTR_DMOD(x)                    (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_ATTR_DMOD_SHIFT)) \
                                                  &DMA_TCD_ATTR_DMOD_MASK)
#define DMA_TCD_ATTR_SSIZE_MASK                 0x700u
#define DMA_TCD_ATTR_SSIZE_SHIFT                8u
#define DMA_TCD_ATTR_SSIZE_WIDTH                3u
#define DMA_TCD_ATTR_SSIZE(x)                   (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_ATTR_SSIZE_SHIFT)) \
                                                  &DMA_TCD_ATTR_SSIZE_MASK)
#define DMA_TCD_ATTR_SMOD_MASK                  0xF800u
#define DMA_TCD_ATTR_SMOD_SHIFT                 11u
#define DMA_TCD_ATTR_SMOD_WIDTH                 5u
#define DMA_TCD_ATTR_SMOD(x)                    (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_ATTR_SMOD_SHIFT)) \
                                                  &DMA_TCD_ATTR_SMOD_MASK)
/* TCD_SOFF Bit Fields */
#define DMA_TCD_SOFF_SOFF_MASK                  0xFFFFu
#define DMA_TCD_SOFF_SOFF_SHIFT                 0u
#define DMA_TCD_SOFF_SOFF_WIDTH                 16u
#define DMA_TCD_SOFF_SOFF(x)                    (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_SOFF_SOFF_SHIFT)) \
                                                  &DMA_TCD_SOFF_SOFF_MASK)
/* TCD_NBYTES_MLNO Bit Fields */
#define DMA_TCD_NBYTES_MLNO_NBYTE_MASK          0xFFFFFFFFu
#define DMA_TCD_NBYTES_MLNO_NBYTE_SHIFT         0u
#define DMA_TCD_NBYTES_MLNO_NBYTE_WIDTH         32u
#define DMA_TCD_NBYTES_MLNO_NBYTES(x)           (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NBYTES_MLNO_NBYTE_SHIFT)) \
                                                  &DMA_TCD_NBYTES_MLNO_NBYTE_MASK)
/* TCD_NBYTES_MLOFFNO Bit Fields */
#define DMA_TCD_NBYTES_MLOFFNO_NB_MASK          0x3FFFFFFFu
#define DMA_TCD_NBYTES_MLOFFNO_NB_SHIFT         0u
#define DMA_TCD_NBYTES_MLOFFNO_NB_WIDTH         30u
#define DMA_TCD_NBYTES_MLOFFNO_NBYTES(x)        (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NBYTES_MLOFFNO_NB_SHIFT)) \
                                                  &DMA_TCD_NBYTES_MLOFFNO_NB_MASK)
#define DMA_TCD_NB_MLOFFNO_DMLOE_MASK           0x40000000u
#define DMA_TCD_NB_MLOFFNO_DMLOE_SHIFT          30u
#define DMA_TCD_NB_MLOFFNO_DMLOE_WIDTH          1u
#define DMA_TCD_NBYTES_MLOFFNO_DMLOE(x)         (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFNO_DMLOE_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFNO_DMLOE_MASK)
#define DMA_TCD_NB_MLOFFNO_SMLOE_MASK           0x80000000u
#define DMA_TCD_NB_MLOFFNO_SMLOE_SHIFT          31u
#define DMA_TCD_NB_MLOFFNO_SMLOE_WIDTH          1u
#define DMA_TCD_NBYTES_MLOFFNO_SMLOE(x)         (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFNO_SMLOE_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFNO_SMLOE_MASK)
/* TCD_NBYTES_MLOFFYES Bit Fields */
#define DMA_TCD_NB_MLOFFYES_NB_MASK             0x3FFUL
#define DMA_TCD_NB_MLOFFYES_NB_SHIFT            0u  /* PRQA S 0791 */
#define DMA_TCD_NB_MLOFFYES_NB_WIDTH            10u /* PRQA S 0791 */
#define DMA_TCD_NBYTES_MLOFFYES_NBYTES(x)       (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFYES_NB_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFYES_NB_MASK)
#define DMA_TCD_NB_MLOFFYES_MLOFF_MASK          0x3FFFFC00u
#define DMA_TCD_NB_MLOFFYES_MLOFF_SHIFT         10u
#define DMA_TCD_NB_MLOFFYES_MLOFF_WIDTH         20u
#define DMA_TCD_NBYTES_MLOFFYES_MLOFF(x)        (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFYES_MLOFF_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFYES_MLOFF_MASK)
#define DMA_TCD_NB_MLOFFYES_DMLOE_MASK          0x40000000u
#define DMA_TCD_NB_MLOFFYES_DMLOE_SHIFT         30u
#define DMA_TCD_NB_MLOFFYES_DMLOE_WIDTH         1u
#define DMA_TCD_NBYTES_MLOFFYES_DMLOE(x)        (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFYES_DMLOE_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFYES_DMLOE_MASK)
#define DMA_TCD_NB_MLOFFYES_SMLOE_MASK          0x80000000u
#define DMA_TCD_NB_MLOFFYES_SMLOE_SHIFT         31u
#define DMA_TCD_NB_MLOFFYES_SMLOE_WIDTH         1u
#define DMA_TCD_NBYTES_MLOFFYES_SMLOE(x)        (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_NB_MLOFFYES_SMLOE_SHIFT)) \
                                                  &DMA_TCD_NB_MLOFFYES_SMLOE_MASK)
/* TCD_SLAST Bit Fields */
#define DMA_TCD_SLAST_SLAST_MASK                0xFFFFFFFFu
#define DMA_TCD_SLAST_SLAST_SHIFT               0u
#define DMA_TCD_SLAST_SLAST_WIDTH               32u
#define DMA_TCD_SLAST_SLAST(x)                  (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_SLAST_SLAST_SHIFT)) \
                                                  &DMA_TCD_SLAST_SLAST_MASK)
/* TCD_DADDR Bit Fields */
#define DMA_TCD_DADDR_DADDR_MASK                0xFFFFFFFFu
#define DMA_TCD_DADDR_DADDR_SHIFT               0u
#define DMA_TCD_DADDR_DADDR_WIDTH               32u
#define DMA_TCD_DADDR_DADDR(x)                  (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_DADDR_DADDR_SHIFT)) \
                                                  &DMA_TCD_DADDR_DADDR_MASK)
/* TCD_CITER_ELINKNO Bit Fields */
#define DMA_TCD_CITER_ELINKNO_CTR_MASK          0x7FFFu
#define DMA_TCD_CITER_ELINKNO_CTR_SHIFT         0u
#define DMA_TCD_CITER_ELINKNO_CTR_WIDTH         15u
#define DMA_TCD_CITER_ELINKNO_CITER(x)          (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CITER_ELINKNO_CTR_SHIFT)) \
                                                  &DMA_TCD_CITER_ELINKNO_CTR_MASK)
#define DMA_TCD_CITER_ELINKNO_ELK_MASK          0x8000u
#define DMA_TCD_CITER_ELINKNO_ELK_SHIFT         15u
#define DMA_TCD_CITER_ELINKNO_ELK_WIDTH         1u
#define DMA_TCD_CITER_ELINKNO_ELINK(x)          (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CITER_ELINKNO_ELK_SHIFT)) \
                                                  &DMA_TCD_CITER_ELINKNO_ELK_MASK)
/* TCD_CITER_ELINKYES Bit Fields */
#define DMA_TCD_CTR_ELKYES_CITER_MASK           0x1FFu
#define DMA_TCD_CTR_ELKYES_CITER_SHIFT          0u
#define DMA_TCD_CTR_ELKYES_CITER_WIDTH          9u
#define DMA_TCD_CITER_ELINKYES_CITER(x)         (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CTR_ELKYES_CITER_SHIFT)) \
                                                  &DMA_TCD_CTR_ELKYES_CITER_MASK)
#define DMA_TCD_CTR_ELNKYES_LNKCH_MASK          0x7E00u
#define DMA_TCD_CTR_ELNKYES_LNKCH_SHIFT         9u
#define DMA_TCD_CTR_ELNKYES_LNKCH_WIDTH         6u
#define DMA_TCD_CITER_ELINKYES_LINKCH(x)        (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CTR_ELNKYES_LNKCH_SHIFT)) \
                                                  &DMA_TCD_CTR_ELNKYES_LNKCH_MASK)
#define DMA_TCD_CTR_ELINKYES_ELK_MASK           0x8000u
#define DMA_TCD_CTR_ELINKYES_ELK_SHIFT          15u
#define DMA_TCD_CTR_ELINKYES_ELK_WIDTH          1u
#define DMA_TCD_CITER_ELINKYES_ELINK(x)         (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CTR_ELINKYES_ELK_SHIFT)) \
                                                  &DMA_TCD_CTR_ELINKYES_ELK_MASK)
/* TCD_DOFF Bit Fields */
#define DMA_TCD_DOFF_DOFF_MASK                  0xFFFFu
#define DMA_TCD_DOFF_DOFF_SHIFT                 0u
#define DMA_TCD_DOFF_DOFF_WIDTH                 16u
#define DMA_TCD_DOFF_DOFF(x)                    (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_DOFF_DOFF_SHIFT)) \
                                                  &DMA_TCD_DOFF_DOFF_MASK)
/* TCD_DLASTSGA Bit Fields */
#define DMA_TCD_DLASTSGA_DLASTSGA_MASK          0xFFFFFFFFu
#define DMA_TCD_DLASTSGA_DLASTSGA_SHIFT         0u
#define DMA_TCD_DLASTSGA_DLASTSGA_WIDTH         32u
#define DMA_TCD_DLASTSGA_DLASTSGA(x)            (((uint32)(((uint32)(x)) \
                                                  << DMA_TCD_DLASTSGA_DLASTSGA_SHIFT)) \
                                                  &DMA_TCD_DLASTSGA_DLASTSGA_MASK)
/* TCD_BITER_ELINKNO Bit Fields */
#define DMA_TCD_BITER_ELINKNO_BTR_MASK          0x7FFFu
#define DMA_TCD_BITER_ELINKNO_BTR_SHIFT         0u
#define DMA_TCD_BITER_ELINKNO_BTR_WIDTH         15u
#define DMA_TCD_BITER_ELINKNO_BITER(x)          (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_BITER_ELINKNO_BTR_SHIFT)) \
                                                  &DMA_TCD_BITER_ELINKNO_BTR_MASK)
#define DMA_TCD_BITER_ELINKNO_ELK_MASK          0x8000u
#define DMA_TCD_BITER_ELINKNO_ELK_SHIFT         15u
#define DMA_TCD_BITER_ELINKNO_ELK_WIDTH         1u
#define DMA_TCD_BITER_ELINKNO_ELINK(x)          (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_BITER_ELINKNO_ELK_SHIFT)) \
                                                  &DMA_TCD_BITER_ELINKNO_ELK_MASK)
/* TCD_BITER_ELINKYES Bit Fields */
#define DMA_TCD_BTR_ELINKYES_BTR_MASK           0x1FFu
#define DMA_TCD_BTR_ELINKYES_BTR_SHIFT          0u
#define DMA_TCD_BTR_ELINKYES_BTR_WIDTH          9u
#define DMA_TCD_BITER_ELINKYES_BITER(x)         (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_BTR_ELINKYES_BTR_SHIFT)) \
                                                  &DMA_TCD_BTR_ELINKYES_BTR_MASK)
#define DMA_TCD_BTR_ELKYES_LINKCH_MASK          0x7E00u
#define DMA_TCD_BTR_ELKYES_LINKCH_SHIFT         9u
#define DMA_TCD_BTR_ELKYES_LINKCH_WIDTH         6u
#define DMA_TCD_BITER_ELINKYES_LINKCH(x)        (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_BTR_ELKYES_LINKCH_SHIFT)) \
                                                  &DMA_TCD_BTR_ELKYES_LINKCH_MASK)
#define DMA_TCD_BTR_ELKYES_ELINK_MASK           0x8000u
#define DMA_TCD_BTR_ELKYES_ELINK_SHIFT          15u
#define DMA_TCD_BTR_ELKYES_ELINK_WIDTH          1u
#define DMA_TCD_BITER_ELINKYES_ELINK(x)         (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_BTR_ELKYES_ELINK_SHIFT)) \
                                                  &DMA_TCD_BTR_ELKYES_ELINK_MASK)
/* TCD_CSR Bit Fields */
#define DMA_TCD_CSR_START_MASK                  0x1u
#define DMA_TCD_CSR_START_SHIFT                 0u
#define DMA_TCD_CSR_START_WIDTH                 1u
#define DMA_TCD_CSR_START(x)                    (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CSR_START_SHIFT)) \
                                                  &DMA_TCD_CSR_START_MASK)
#define DMA_TCD_CSR_INTMAJOR_MASK               0x2u
#define DMA_TCD_CSR_INTMAJOR_SHIFT              1u
#define DMA_TCD_CSR_INTMAJOR_WIDTH              1u
#define DMA_TCD_CSR_INTMAJOR(x)                 (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_INTMAJOR_SHIFT)) \
                                                  &DMA_TCD_CSR_INTMAJOR_MASK)
#define DMA_TCD_CSR_INTHALF_MASK                0x4u
#define DMA_TCD_CSR_INTHALF_SHIFT               2u
#define DMA_TCD_CSR_INTHALF_WIDTH               1u
#define DMA_TCD_CSR_INTHALF(x)                  (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_INTHALF_SHIFT)) \
                                                  &DMA_TCD_CSR_INTHALF_MASK)
#define DMA_TCD_CSR_DREQ_MASK                   0x8u
#define DMA_TCD_CSR_DREQ_SHIFT                  3u
#define DMA_TCD_CSR_DREQ_WIDTH                  1u
#define DMA_TCD_CSR_DREQ(x)                     (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_DREQ_SHIFT)) \
                                                  &DMA_TCD_CSR_DREQ_MASK)
#define DMA_TCD_CSR_ESG_MASK                    0x10u
#define DMA_TCD_CSR_ESG_SHIFT                   4u
#define DMA_TCD_CSR_ESG_WIDTH                   1u
#define DMA_TCD_CSR_ESG(x)                      (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_ESG_SHIFT)) \
                                                  &DMA_TCD_CSR_ESG_MASK)
#define DMA_TCD_CSR_MAJORELINK_MASK             0x20u
#define DMA_TCD_CSR_MAJORELINK_SHIFT            5u
#define DMA_TCD_CSR_MAJORELINK_WIDTH            1u
#define DMA_TCD_CSR_MAJORELINK(x)               (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_MAJORELINK_SHIFT)) \
                                                  &DMA_TCD_CSR_MAJORELINK_MASK)
#define DMA_TCD_CSR_ACTIVE_MASK                 0x40u
#define DMA_TCD_CSR_ACTIVE_SHIFT                6u
#define DMA_TCD_CSR_ACTIVE_WIDTH                1u
#define DMA_TCD_CSR_ACTIVE(x)                   (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CSR_ACTIVE_SHIFT)) \
                                                  &DMA_TCD_CSR_ACTIVE_MASK)
#define DMA_TCD_CSR_DONE_MASK                   0x80u
#define DMA_TCD_CSR_DONE_SHIFT                  7u
#define DMA_TCD_CSR_DONE_WIDTH                  1u
#define DMA_TCD_CSR_DONE(x)                     (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CSR_DONE_SHIFT)) \
                                                  &DMA_TCD_CSR_DONE_MASK)
#define DMA_TCD_CSR_MAJORLINKCH_MASK            0x3F00u
#define DMA_TCD_CSR_MAJORLINKCH_SHIFT           8u
#define DMA_TCD_CSR_MAJORLINKCH_WIDTH           6u
#define DMA_TCD_CSR_MAJORLINKCH(x)              (uint16)(((((uint32)(x)) \
                                                  << DMA_TCD_CSR_MAJORLINKCH_SHIFT)) \
                                                  &DMA_TCD_CSR_MAJORLINKCH_MASK)
#define DMA_TCD_CSR_BWC_MASK                    0xC000u
#define DMA_TCD_CSR_BWC_SHIFT                   14u
#define DMA_TCD_CSR_BWC_WIDTH                   2u
#define DMA_TCD_CSR_BWC(x)                      (((uint16)(((uint16)(x)) \
                                                  << DMA_TCD_CSR_BWC_SHIFT)) \
                                                  &DMA_TCD_CSR_BWC_MASK)

#define DMAMUX_CHANNEL_COUNT                    (16u)

typedef struct
{
    volatile VAR(uint8, AUTOMATIC) CHCFG[DMAMUX_CHANNEL_COUNT];   /** Control Register, offset: 0x0 */
} DMAMUX_Type, *DMAMUX_MemMapPtr; /* PRQA S 1535 */

#define DMAMUX_INSTANCE_COUNT                   (10UL)

#define DMAMUX_0_BASE                           (0xFFF6C000UL)
#define DMAMUX_1_BASE                           (0xFFF6C200UL)
#define DMAMUX_2_BASE                           (0xFFF6C400UL)
#define DMAMUX_3_BASE                           (0xFFF6C600UL)
#define DMAMUX_4_BASE                           (0xFFF6C800UL)
#define DMAMUX_5_BASE                           (0xFFF6CA00UL)
#define DMAMUX_6_BASE                           (0xFFF6CC00UL)
#define DMAMUX_7_BASE                           (0xFFF6CE00UL)
#define DMAMUX_8_BASE                           (0xFFF6D000UL)
#define DMAMUX_9_BASE                           (0xFFF6D200UL)

/** Peripheral DMAMUX_0~9 base pointer */
#define DMAMUX0_P                               ((DMAMUX_Type *)DMAMUX_0_BASE)
#define DMAMUX1_P                               ((DMAMUX_Type *)DMAMUX_1_BASE)
#define DMAMUX2_P                               ((DMAMUX_Type *)DMAMUX_2_BASE)
#define DMAMUX3_P                               ((DMAMUX_Type *)DMAMUX_3_BASE)
#define DMAMUX4_P                               ((DMAMUX_Type *)DMAMUX_4_BASE)
#define DMAMUX5_P                               ((DMAMUX_Type *)DMAMUX_5_BASE)
#define DMAMUX6_P                               ((DMAMUX_Type *)DMAMUX_6_BASE)
#define DMAMUX7_P                               ((DMAMUX_Type *)DMAMUX_7_BASE)
#define DMAMUX8_P                               ((DMAMUX_Type *)DMAMUX_8_BASE)
#define DMAMUX9_P                               ((DMAMUX_Type *)DMAMUX_9_BASE)

#define DMAMUX_BASE_PTRS                        { DMAMUX0_P, DMAMUX1_P, DMAMUX2_P, DMAMUX3_P, \
                                                  DMAMUX4_P, DMAMUX5_P, DMAMUX6_P, DMAMUX7_P, \
                                                  DMAMUX8_P, DMAMUX9_P }

#define DMAMUX_CHCFG_ENBL_SHIFT                 7U
#define DMAMUX_CHCFG_ENBL_MASK                  0x80U
#define DMAMUX_CHCFG_SOURCE_SHIFT               0U
#define DMAMUX_CHCFG_SOURCE_MASK                0x3FU
#define DMAMUX_CHCFG_TRIG_SHIFT                 6U
#define DMAMUX_CHCFG_TRIG_MASK                  0x40U

typedef enum
{
    EDMA_INSTANCE_0 = 0U,
    EDMA_INSTANCE_1 = 1U
} eDMAIstanceNumType;

typedef enum
{
    DMAMUX_INSTANCE_0 = 0U,
    DMAMUX_INSTANCE_1 = 1U,
    DMAMUX_INSTANCE_2 = 2U,
    DMAMUX_INSTANCE_3 = 3U,
    DMAMUX_INSTANCE_4 = 4U,
    DMAMUX_INSTANCE_5 = 5U,
    DMAMUX_INSTANCE_6 = 6U,
    DMAMUX_INSTANCE_7 = 7U,
    DMAMUX_INSTANCE_8 = 8U,
    DMAMUX_INSTANCE_9 = 9U
} DMAMUXInstanceNumType;

typedef enum
{
    EDMA_CHN_STATUS_NORMAL = 0U,           /* eDMA channel normal state. */
    EDMA_CHN_STATUS_ERROR = 1U                  /* An error occurred in the eDMA channel. */
} eDMAChnStatusType;

typedef enum
{
    EDMA_ARBITRATION_MODE_FIXED_PRIORITY = 0U,  /* Fixed Priority */
    EDMA_ARBITRATION_MODE_ROUND_ROBIN = 1U           /* Round - Robin arbitration */
} eDMASelArbitrationModeType;

typedef struct
{
    VAR(uint32, AUTOMATIC) errh;
    VAR(uint32, AUTOMATIC) errl;
} eDMAErrorRegisterType;

typedef enum
{
    EDMA_GRP_PRIORITY0 = 0U,
    EDMA_GRP_PRIORITY1 = 1U,
    EDMA_GRP_PRIORITY2 = 2U,
    EDMA_GRP_PRIORITY3 = 3U
} eDMAGroupPriorityType;

typedef struct
{
    VAR(eDMASelArbitrationModeType, AUTOMATIC) setChnArbitMode;         /* eDMA channel arbitration. */
    VAR(eDMASelArbitrationModeType, AUTOMATIC) groupArbitration;        /* eDMA group arbitration. */

    VAR(eDMAGroupPriorityType, AUTOMATIC) prioGroup0;                   /* eDMA group 0 priority. */
    VAR(eDMAGroupPriorityType, AUTOMATIC) prioGroup1;                   /* eDMA group 1 priority. */
    VAR(eDMAGroupPriorityType, AUTOMATIC) prioGroup2;                   /* eDMA group 2 priority. */
    VAR(eDMAGroupPriorityType, AUTOMATIC) prioGroup3;                   /* eDMA group 3 priority. */

    VAR(boolean, AUTOMATIC) haltOnError;
} eDMAModuleConfigType;

typedef enum
{
    EDMA_TRANSFER_SIZE_1B  = 0x0U,
    EDMA_TRANSFER_SIZE_2B  = 0x1U,
    EDMA_TRANSFER_SIZE_4B  = 0x2U,
    EDMA_TRANSFER_SIZE_16B = 0x4U,
} eDMATransferSizeType;

typedef enum
{
    EDMA_TRANSFER_TYPE_PERIPHTOMEM = 0U,   /* Transfer from peripheral to memory */
    EDMA_TRANSFER_TYPE_MEMTOPERIPH = 1U,        /* Transfer from memory to peripheral */
    EDMA_TRANSFER_TYPE_MEMTOMEM = 2U,           /* Transfer from memory to memory */
    EDMA_TRANSFER_TYPE_PERIPHTOPERIPH = 3U      /* Transfer from peripheral to peripheral */
} eDMATransferType;

typedef struct
{
    VAR(uint32, AUTOMATIC) address;
    VAR(uint32, AUTOMATIC) length;
    VAR(eDMATransferType, AUTOMATIC) type;
} eDMAScatterGatherListType;

typedef enum
{
    EDMA_CHN_PRIORITY0 = 0U,
    EDMA_CHN_PRIORITY1 = 1U,
    EDMA_CHN_PRIORITY2 = 2U,
    EDMA_CHN_PRIORITY3 = 3U,
    EDMA_CHN_PRIORITY4 = 4U,
    EDMA_CHN_PRIORITY5 = 5U,
    EDMA_CHN_PRIORITY6 = 6U,
    EDMA_CHN_PRIORITY7 = 7U,
    EDMA_CHN_PRIORITY8 = 8U,
    EDMA_CHN_PRIORITY9 = 9U,
    EDMA_CHN_PRIORITY10 = 10U,
    EDMA_CHN_PRIORITY11 = 11U,
    EDMA_CHN_PRIORITY12 = 12U,
    EDMA_CHN_PRIORITY13 = 13U,
    EDMA_CHN_PRIORITY14 = 14U,
    EDMA_CHN_PRIORITY15 = 15U,

    EDMA_CHN_PRIORITY_DEFALUT = 255U
} eDMAChannelPriorityType;

typedef enum
{
    EDMA_ADDRESS_MODULO_OFF = 0U,
    EDMA_ADDRESS_MODULO_2B = 1U,
    EDMA_ADDRESS_MODULO_4B = 2U,
    EDMA_ADDRESS_MODULO_8B = 3U,
    EDMA_ADDRESS_MODULO_16B = 4U,
    EDMA_ADDRESS_MODULO_32B = 5U,
    EDMA_ADDRESS_MODULO_64B = 6U,
    EDMA_ADDRESS_MODULO_128B = 7U,
    EDMA_ADDRESS_MODULO_256B = 8U,
    EDMA_ADDRESS_MODULO_512B = 9U,
    EDMA_ADDRESS_MODULO_1KB = 10U,
    EDMA_ADDRESS_MODULO_2KB = 11U,
    EDMA_ADDRESS_MODULO_4KB = 12U,
    EDMA_ADDRESS_MODULO_8KB = 13U,
    EDMA_ADDRESS_MODULO_16KB = 14U,
    EDMA_ADDRESS_MODULO_32KB = 15U,
    EDMA_ADDRESS_MODULO_64KB = 16U,
    EDMA_ADDRESS_MODULO_128KB = 17U,
    EDMA_ADDRESS_MODULO_256KB = 18U,
    EDMA_ADDRESS_MODULO_512KB = 19U,
    EDMA_ADDRESS_MODULO_1MB = 20U,
    EDMA_ADDRESS_MODULO_2MB = 21U,
    EDMA_ADDRESS_MODULO_4MB = 22U,
    EDMA_ADDRESS_MODULO_8MB = 23U,
    EDMA_ADDRESS_MODULO_16MB = 24U,
    EDMA_ADDRESS_MODULO_32MB = 25U,
    EDMA_ADDRESS_MODULO_64MB = 26U,
    EDMA_ADDRESS_MODULO_128MB = 27U,
    EDMA_ADDRESS_MODULO_256MB = 28U,
    EDMA_ADDRESS_MODULO_512MB = 29U,
    EDMA_ADDRESS_MODULO_1GB = 30U,
    EDMA_ADDRESS_MODULO_2GB = 31U
} eDMAModuloType;

typedef enum
{
    /* DMAMUX_0: DMAMUX Channel 0 - 7 (eDMA_0 Channel 0 - 7) */
    DMAMUX0_RESERVED_0_A            = 0U,   /* DMAMUX_0: Source 0  */
    DMAMUX0_ADC_SAR_0_EOC           = 1U,   /* DMAMUX_0: Source 1  */
    DMAMUX0_ADC_SAR_1_EOC           = 2U,   /* DMAMUX_0: Source 2  */
    DMAMUX0_ADC_SAR_B_EOC           = 3U,   /* DMAMUX_0: Source 3  */
    DMAMUX0_ADC_SD_0_EOC            = 4U,   /* DMAMUX_0: Source 4  */
    DMAMUX0_DSPI_0_RX               = 5U,   /* DMAMUX_0: Source 5  */
    DMAMUX0_DSPI_0_TX               = 6U,   /* DMAMUX_0: Source 6  */
    DMAMUX0_DSPI_4_RX               = 7U,   /* DMAMUX_0: Source 7  */
    DMAMUX0_DSPI_4_TX               = 8U,   /* DMAMUX_0: Source 8  */
    DMAMUX0_RESERVED_1              = 9U,   /* DMAMUX_0: Source 9  */
    DMAMUX0_ADC_SAR_4_EOC           = 10U,  /* DMAMUX_0: Source 10 */
    DMAMUX0_ADC_SD_3_EOC            = 11U,  /* DMAMUX_0: Source 11 */
    DMAMUX0_MCAN_1                  = 12U,  /* DMAMUX_0: Source 12 */
    DMAMUX0_MCAN_2                  = 13U,  /* DMAMUX_0: Source 13 */
    DMAMUX0_SENT_0_RX_FAST          = 14U,  /* DMAMUX_0: Source 14 */
    DMAMUX0_SENT_0_RX_SLOW          = 15U,  /* DMAMUX_0: Source 15 */
    DMAMUX0_LINFLEXD_0_RX           = 16U,  /* DMAMUX_0: Source 16 */
    DMAMUX0_LINFLEXD_0_TX           = 17U,  /* DMAMUX_0: Source 17 */
    DMAMUX0_LINFLEXD_14_RX          = 18U,  /* DMAMUX_0: Source 18 */
    DMAMUX0_DSPI_0_CMD              = 19U,  /* DMAMUX_0: Source 19 */
    DMAMUX0_DSPI_4_CMD              = 20U,  /* DMAMUX_0: Source 20 */
    DMAMUX0_MCAN_3                  = 21U,  /* DMAMUX_0: Source 21 */
    DMAMUX0_MCAN_4                  = 22U,  /* DMAMUX_0: Source 22 */
    DMAMUX0_MCAN_5                  = 23U,  /* DMAMUX_0: Source 23 */
    DMAMUX0_MCAN_6                  = 24U,  /* DMAMUX_0: Source 24 */
    DMAMUX0_MCAN_7                  = 25U,  /* DMAMUX_0: Source 25 */
    DMAMUX0_MCAN_8                  = 26U,  /* DMAMUX_0: Source 26 */
    DMAMUX0_ETPU_0                  = 27U,  /* DMAMUX_0: Source 27 */
    DMAMUX0_ETPU_1                  = 28U,  /* DMAMUX_0: Source 28 */
    DMAMUX0_ETPU_2                  = 29U,  /* DMAMUX_0: Source 29 */
    DMAMUX0_ETPU_12                 = 30U,  /* DMAMUX_0: Source 30 */
    DMAMUX0_ETPU_13                 = 31U,  /* DMAMUX_0: Source 31 */
    DMAMUX0_ETPU_14                 = 32U,  /* DMAMUX_0: Source 32 */
    DMAMUX0_ETPU_15                 = 33U,  /* DMAMUX_0: Source 33 */
    DMAMUX0_ETPU_28                 = 34U,  /* DMAMUX_0: Source 34 */
    DMAMUX0_ETPU_29                 = 35U,  /* DMAMUX_0: Source 35 */
    DMAMUX0_ETPUC_0                 = 36U,  /* DMAMUX_0: Source 36 */
    DMAMUX0_ETPUC_1                 = 37U,  /* DMAMUX_0: Source 37 */
    DMAMUX0_ETPUC_2                 = 38U,  /* DMAMUX_0: Source 38 */
    DMAMUX0_ETPUC_3                 = 39U,  /* DMAMUX_0: Source 39 */
    DMAMUX0_ETPUC_12                = 40U,  /* DMAMUX_0: Source 40 */
    DMAMUX0_ETPUC_13                = 41U,  /* DMAMUX_0: Source 41 */
    DMAMUX0_ETPUC_14                = 42U,  /* DMAMUX_0: Source 42 */
    DMAMUX0_ETPUC_15                = 43U,  /* DMAMUX_0: Source 43 */
    DMAMUX0_ETPUC_28                = 44U,  /* DMAMUX_0: Source 44 */
    DMAMUX0_ETPUC_29                = 45U,  /* DMAMUX_0: Source 45 */
    DMAMUX0_ETPUC_30                = 46U,  /* DMAMUX_0: Source 46 */
    DMAMUX0_ETPUC_31                = 47U,  /* DMAMUX_0: Source 47 */
    DMAMUX0_RESERVED_2              = 48U,  /* DMAMUX_0: Source 48 */
    DMAMUX0_RESERVED_3              = 49U,  /* DMAMUX_0: Source 49 */
    DMAMUX0_RESERVED_4              = 50U,  /* DMAMUX_0: Source 50 */
    DMAMUX0_EQADC0_ADC01_RFIFO0     = 51U,  /* DMAMUX_0: Source 51 */
    DMAMUX0_EQADC0_ADC01_RFIFO1     = 52U,  /* DMAMUX_0: Source 52 */
    DMAMUX0_EQADC0_ADC01_RFIFO2     = 53U,  /* DMAMUX_0: Source 53 */
    DMAMUX0_EQADC0_ADC01_RFIFO3     = 54U,  /* DMAMUX_0: Source 54 */
    DMAMUX0_EQADC0_ADC01_RFIFO4     = 55U,  /* DMAMUX_0: Source 55 */
    DMAMUX0_EQADC0_ADC01_RFIFO5     = 56U,  /* DMAMUX_0: Source 56 */
    DMAMUX0_EQADC0_ADC01_CFIFO0     = 57U,  /* DMAMUX_0: Source 57 */
    DMAMUX0_EQADC0_ADC01_CFIFO1     = 58U,  /* DMAMUX_0: Source 58 */
    DMAMUX0_EQADC0_ADC01_CFIFO2     = 59U,  /* DMAMUX_0: Source 59 */
    DMAMUX0_EQADC0_ADC01_CFIFO3     = 60U,  /* DMAMUX_0: Source 60 */
    DMAMUX0_EQADC0_ADC01_CFIFO4     = 61U,  /* DMAMUX_0: Source 61 */
    DMAMUX0_EQADC0_ADC01_CFIFO5     = 62U,  /* DMAMUX_0: Source 62 */
    DMAMUX0_ALWAYS_ON_0             = 63U,  /* DMAMUX_0: Source 63 */

    /* DMAMUX_1: DMAMUX Channel 8 - 15 (eDMA_0 Channel 8 - 15) */
    DMAMUX1_RESERVED_0_A            = 64U,  /* DMAMUX_1: Source 0  */
    DMAMUX1_DSPI_12_RX              = 65U,  /* DMAMUX_1: Source 1  */
    DMAMUX1_DSPI_12_TX              = 66U,  /* DMAMUX_1: Source 2  */
    DMAMUX1_LINFLEXD_0_RX           = 67U,  /* DMAMUX_1: Source 3  */
    DMAMUX1_LINFLEXD_0_TX           = 68U,  /* DMAMUX_1: Source 4  */
    DMAMUX1_LINFLEXD_1_RX           = 69U,  /* DMAMUX_1: Source 5  */
    DMAMUX1_LINFLEXD_1_TX           = 70U,  /* DMAMUX_1: Source 6  */
    DMAMUX1_LINFLEXD_14_RX          = 71U,  /* DMAMUX_1: Source 7  */
    DMAMUX1_LINFLEXD_14_TX          = 72U,  /* DMAMUX_1: Source 8  */
    DMAMUX1_SENT_0_FAST             = 73U,  /* DMAMUX_1: Source 9  */
    DMAMUX1_SENT_0_SLOW             = 74U,  /* DMAMUX_1: Source 10 */
    DMAMUX1_SIPI_CH0                = 75U,  /* DMAMUX_1: Source 11 */
    DMAMUX1_SIPI_CH1                = 76U,  /* DMAMUX_1: Source 12 */
    DMAMUX1_SIPI_CH2                = 77U,  /* DMAMUX_1: Source 13 */
    DMAMUX1_SIPI_CH3                = 78U,  /* DMAMUX_1: Source 14 */
    DMAMUX1_SIUL2_REQ0              = 79U,  /* DMAMUX_1: Source 15 */
    DMAMUX1_SIUL2_REQ1              = 80U,  /* DMAMUX_1: Source 16 */
    DMAMUX1_GTM_TIM0_IRQ0           = 81U,  /* DMAMUX_1: Source 17 */
    DMAMUX1_GTM_TIM0_IRQ1           = 82U,  /* DMAMUX_1: Source 18 */
    DMAMUX1_GTM_TIM0_IRQ2           = 83U,  /* DMAMUX_1: Source 19 */
    DMAMUX1_GTM_TIM0_IRQ3           = 84U,  /* DMAMUX_1: Source 20 */
    DMAMUX1_GTM_TIM0_IRQ4           = 85U,  /* DMAMUX_1: Source 21 */
    DMAMUX1_GTM_TIM0_IRQ5           = 86U,  /* DMAMUX_1: Source 22 */
    DMAMUX1_GTM_TIM0_IRQ6           = 87U,  /* DMAMUX_1: Source 23 */
    DMAMUX1_GTM_TIM0_IRQ7           = 88U,  /* DMAMUX_1: Source 24 */
    DMAMUX1_GTM_TOM0_IRQ0           = 89U,  /* DMAMUX_1: Source 25 */
    DMAMUX1_GTM_TOM0_IRQ1           = 90U,  /* DMAMUX_1: Source 26 */
    DMAMUX1_GTM_TOM0_IRQ2           = 91U,  /* DMAMUX_1: Source 27 */
    DMAMUX1_GTM_TOM0_IRQ3           = 92U,  /* DMAMUX_1: Source 28 */
    DMAMUX1_GTM_TOM0_IRQ4           = 93U,  /* DMAMUX_1: Source 29 */
    DMAMUX1_GTM_TOM0_IRQ5           = 94U,  /* DMAMUX_1: Source 30 */
    DMAMUX1_GTM_TOM0_IRQ6           = 95U,  /* DMAMUX_1: Source 31 */
    DMAMUX1_GTM_TOM0_IRQ7           = 96U,  /* DMAMUX_1: Source 32 */
    DMAMUX1_GTM_ATOM0_IRQ0          = 97U,  /* DMAMUX_1: Source 33 */
    DMAMUX1_GTM_ATOM0_IRQ1          = 98U,  /* DMAMUX_1: Source 34 */
    DMAMUX1_GTM_ATOM0_IRQ2          = 99U,  /* DMAMUX_1: Source 35 */
    DMAMUX1_GTM_ATOM0_IRQ3          = 100U, /* DMAMUX_1: Source 36 */
    DMAMUX1_GTM_MCS0_IRQ0           = 101U, /* DMAMUX_1: Source 37 */
    DMAMUX1_GTM_MCS0_IRQ1           = 102U, /* DMAMUX_1: Source 38 */
    DMAMUX1_GTM_MCS0_IRQ2           = 103U, /* DMAMUX_1: Source 39 */
    DMAMUX1_GTM_MCS0_IRQ3           = 104U, /* DMAMUX_1: Source 40 */
    DMAMUX1_GTM_MCS0_IRQ4           = 105U, /* DMAMUX_1: Source 41 */
    DMAMUX1_GTM_MCS0_IRQ5           = 106U, /* DMAMUX_1: Source 42 */
    DMAMUX1_GTM_MCS0_IRQ6           = 107U, /* DMAMUX_1: Source 43 */
    DMAMUX1_GTM_MCS0_IRQ7           = 108U, /* DMAMUX_1: Source 44 */
    DMAMUX1_LINFLEXD_15_RX          = 109U, /* DMAMUX_1: Source 45 */
    DMAMUX1_LINFLEXD_15_TX          = 110U, /* DMAMUX_1: Source 46 */
    DMAMUX1_DSPI_5_RX               = 111U, /* DMAMUX_1: Source 47 */
    DMAMUX1_DSPI_5_TX               = 112U, /* DMAMUX_1: Source 48 */
    DMAMUX1_DSPI_5_CMD              = 113U, /* DMAMUX_1: Source 49 */
    DMAMUX1_DSPI_12_CMD             = 114U, /* DMAMUX_1: Source 50 */
    DMAMUX1_RESERVED_1              = 115U, /* DMAMUX_1: Source 51 */
    DMAMUX1_RESERVED_2              = 116U, /* DMAMUX_1: Source 52 */
    DMAMUX1_DSPI_0_RX               = 117U, /* DMAMUX_1: Source 53 */
    DMAMUX1_DSPI_0_TX               = 118U, /* DMAMUX_1: Source 54 */
    DMAMUX1_ADC_SAR_0_EOC           = 119U, /* DMAMUX_1: Source 55 */
    DMAMUX1_ADC_SAR_4_EOC           = 120U, /* DMAMUX_1: Source 56 */
    DMAMUX1_ADC_SD_3_EOC            = 121U, /* DMAMUX_1: Source 57 */
    DMAMUX1_RESERVED_3              = 122U, /* DMAMUX_1: Source 58 */
    DMAMUX1_ALWAYS_ON_0             = 123U, /* DMAMUX_1: Source 59 */
    DMAMUX1_ALWAYS_ON_1             = 124U, /* DMAMUX_1: Source 60 */
    DMAMUX1_ALWAYS_ON_2             = 125U, /* DMAMUX_1: Source 61 */
    DMAMUX1_ALWAYS_ON_3             = 126U, /* DMAMUX_1: Source 62 */
    DMAMUX1_ALWAYS_ON_4             = 127U, /* DMAMUX_1: Source 63 */

    /* DMAMUX_2: DMAMUX Channel 16 - 23 (eDMA_0 Channel 16 - 23) */
    DMAMUX2_RESERVED_0_A            = 128U, /* DMAMUX_2: Source 0  */
    DMAMUX2_ADC_SAR_2_EOC           = 129U, /* DMAMUX_2: Source 1  */
    DMAMUX2_ADC_SD_1_EOC            = 130U, /* DMAMUX_2: Source 2  */
    DMAMUX2_DSPI_1_RX               = 131U, /* DMAMUX_2: Source 3  */
    DMAMUX2_DSPI_1_TX               = 132U, /* DMAMUX_2: Source 4  */
    DMAMUX2_SENT_1_FAST             = 133U, /* DMAMUX_2: Source 5  */
    DMAMUX2_SENT_1_SLOW             = 134U, /* DMAMUX_2: Source 6  */
    DMAMUX2_PSI5_0_CH0_RX_PSI5      = 135U, /* DMAMUX_2: Source 7  */
    DMAMUX2_PSI5_0_CH0_RX_SENT      = 136U, /* DMAMUX_2: Source 8  */
    DMAMUX2_SIUL2_REQ2              = 137U, /* DMAMUX_2: Source 9  */
    DMAMUX2_SIUL2_REQ4              = 138U, /* DMAMUX_2: Source 10 */
    DMAMUX2_GTM_PSM0_IRQ0           = 139U, /* DMAMUX_2: Source 11 */
    DMAMUX2_GTM_PSM0_IRQ1           = 140U, /* DMAMUX_2: Source 12 */
    DMAMUX2_GTM_PSM0_IRQ2           = 141U, /* DMAMUX_2: Source 13 */
    DMAMUX2_GTM_PSM0_IRQ3           = 142U, /* DMAMUX_2: Source 14 */
    DMAMUX2_GTM_TIM1_IRQ0           = 143U, /* DMAMUX_2: Source 15 */
    DMAMUX2_GTM_TIM1_IRQ1           = 144U, /* DMAMUX_2: Source 16 */
    DMAMUX2_GTM_TIM1_IRQ2           = 145U, /* DMAMUX_2: Source 17 */
    DMAMUX2_GTM_TIM1_IRQ3           = 146U, /* DMAMUX_2: Source 18 */
    DMAMUX2_GTM_TOM1_IRQ0           = 147U, /* DMAMUX_2: Source 19 */
    DMAMUX2_GTM_TOM1_IRQ1           = 148U, /* DMAMUX_2: Source 20 */
    DMAMUX2_GTM_TOM1_IRQ2           = 149U, /* DMAMUX_2: Source 21 */
    DMAMUX2_GTM_TOM1_IRQ3           = 150U, /* DMAMUX_2: Source 22 */
    DMAMUX2_GTM_ATOM1_IRQ0          = 151U, /* DMAMUX_2: Source 23 */
    DMAMUX2_GTM_ATOM1_IRQ1          = 152U, /* DMAMUX_2: Source 24 */
    DMAMUX2_GTM_MCS1_IRQ0           = 153U, /* DMAMUX_2: Source 25 */
    DMAMUX2_GTM_MCS1_IRQ1           = 154U, /* DMAMUX_2: Source 26 */
    DMAMUX2_GTM_MCS1_IRQ2           = 155U, /* DMAMUX_2: Source 27 */
    DMAMUX2_GTM_MCS1_IRQ3           = 156U, /* DMAMUX_2: Source 28 */
    DMAMUX2_GTM_TIM2_IRQ0           = 157U, /* DMAMUX_2: Source 29 */
    DMAMUX2_GTM_TIM2_IRQ1           = 158U, /* DMAMUX_2: Source 30 */
    DMAMUX2_GTM_TIM2_IRQ2           = 159U, /* DMAMUX_2: Source 31 */
    DMAMUX2_GTM_TIM2_IRQ3           = 160U, /* DMAMUX_2: Source 32 */
    DMAMUX2_GTM_ATOM2_IRQ0          = 161U, /* DMAMUX_2: Source 33 */
    DMAMUX2_GTM_ATOM2_IRQ1          = 162U, /* DMAMUX_2: Source 34 */
    DMAMUX2_GTM_MCS2_IRQ0           = 163U, /* DMAMUX_2: Source 35 */
    DMAMUX2_GTM_MCS2_IRQ1           = 164U, /* DMAMUX_2: Source 36 */
    DMAMUX2_GTM_MCS2_IRQ2           = 165U, /* DMAMUX_2: Source 37 */
    DMAMUX2_GTM_MCS2_IRQ3           = 166U, /* DMAMUX_2: Source 38 */
    DMAMUX2_GTM_ATOM3_IRQ0          = 167U, /* DMAMUX_2: Source 39 */
    DMAMUX2_GTM_ATOM3_IRQ1          = 168U, /* DMAMUX_2: Source 40 */
    DMAMUX2_ADC_SD_2_EOC            = 169U, /* DMAMUX_2: Source 41 */
    DMAMUX2_DSPI_1_CMD              = 170U, /* DMAMUX_2: Source 42 */
    DMAMUX2_DSPI_2_RX               = 171U, /* DMAMUX_2: Source 43 */
    DMAMUX2_DSPI_2_TX               = 172U, /* DMAMUX_2: Source 44 */
    DMAMUX2_LINFLEXD_2_RX           = 173U, /* DMAMUX_2: Source 45 */
    DMAMUX2_LINFLEXD_2_TX           = 174U, /* DMAMUX_2: Source 46 */
    DMAMUX2_GTM_SPE0                = 175U, /* DMAMUX_2: Source 47 */
    DMAMUX2_GTM_SPE1                = 176U, /* DMAMUX_2: Source 48 */
    DMAMUX2_PSI5_SPS                = 177U, /* DMAMUX_2: Source 49 */
    DMAMUX2_PSI5_SRX                = 178U, /* DMAMUX_2: Source 50 */
    DMAMUX2_EQADC1_ADC23_RFIFO0     = 179U, /* DMAMUX_2: Source 51 */
    DMAMUX2_EQADC1_ADC23_RFIFO1     = 180U, /* DMAMUX_2: Source 52 */
    DMAMUX2_EQADC1_ADC23_RFIFO2     = 181U, /* DMAMUX_2: Source 53 */
    DMAMUX2_EQADC1_ADC23_RFIFO3     = 182U, /* DMAMUX_2: Source 54 */
    DMAMUX2_EQADC1_ADC23_RFIFO4     = 183U, /* DMAMUX_2: Source 55 */
    DMAMUX2_EQADC1_ADC23_RFIFO5     = 184U, /* DMAMUX_2: Source 56 */
    DMAMUX2_EQADC1_ADC23_CFIFO0     = 185U, /* DMAMUX_2: Source 57 */
    DMAMUX2_EQADC1_ADC23_CFIFO1     = 186U, /* DMAMUX_2: Source 58 */
    DMAMUX2_EQADC1_ADC23_CFIFO2     = 187U, /* DMAMUX_2: Source 59 */
    DMAMUX2_EQADC1_ADC23_CFIFO3     = 188U, /* DMAMUX_2: Source 60 */
    DMAMUX2_EQADC1_ADC23_CFIFO4     = 189U, /* DMAMUX_2: Source 61 */
    DMAMUX2_EQADC1_ADC23_CFIFO5     = 190U, /* DMAMUX_2: Source 62 */
    DMAMUX2_ALWAYS_ON_0             = 191U, /* DMAMUX_2: Source 63 */

    /* DMAMUX_3: DMAMUX Channel 24 - 31 (eDMA_0 Channel 24 - 31) */
    DMAMUX3_RESERVED_0_A            = 192U, /* DMAMUX_3: Source 0  */
    DMAMUX3_ADC_SAR_3_EOC           = 193U, /* DMAMUX_3: Source 1  */
    DMAMUX3_DSPI_2_RX               = 194U, /* DMAMUX_3: Source 2  */
    DMAMUX3_DSPI_2_TX               = 195U, /* DMAMUX_3: Source 3  */
    DMAMUX3_LINFLEXD_2_RX           = 196U, /* DMAMUX_3: Source 4  */
    DMAMUX3_LINFLEXD_2_TX           = 197U, /* DMAMUX_3: Source 5  */
    DMAMUX3_I2C_0_RX                = 198U, /* DMAMUX_3: Source 6  */
    DMAMUX3_I2C_0_TX                = 199U, /* DMAMUX_3: Source 7  */
    DMAMUX3_PSI5_1_CH0_RX_PSI5      = 200U, /* DMAMUX_3: Source 8  */
    DMAMUX3_PSI5_1_CH0_RX_SENT      = 201U, /* DMAMUX_3: Source 9  */
    DMAMUX3_SIUL2_REQ5              = 202U, /* DMAMUX_3: Source 10 */
    DMAMUX3_GTM_PSM0_IRQ4           = 203U, /* DMAMUX_3: Source 11 */
    DMAMUX3_GTM_PSM0_IRQ5           = 204U, /* DMAMUX_3: Source 12 */
    DMAMUX3_GTM_PSM0_IRQ6           = 205U, /* DMAMUX_3: Source 13 */
    DMAMUX3_GTM_PSM0_IRQ7           = 206U, /* DMAMUX_3: Source 14 */
    DMAMUX3_GTM_TIM1_IRQ4           = 207U, /* DMAMUX_3: Source 15 */
    DMAMUX3_GTM_TIM1_IRQ5           = 208U, /* DMAMUX_3: Source 16 */
    DMAMUX3_GTM_TIM1_IRQ6           = 209U, /* DMAMUX_3: Source 17 */
    DMAMUX3_GTM_TIM1_IRQ7           = 210U, /* DMAMUX_3: Source 18 */
    DMAMUX3_GTM_TOM1_IRQ4           = 211U, /* DMAMUX_3: Source 19 */
    DMAMUX3_GTM_TOM1_IRQ5           = 212U, /* DMAMUX_3: Source 20 */
    DMAMUX3_GTM_TOM1_IRQ6           = 213U, /* DMAMUX_3: Source 21 */
    DMAMUX3_GTM_TOM1_IRQ7           = 214U, /* DMAMUX_3: Source 22 */
    DMAMUX3_GTM_ATOM1_IRQ2          = 215U, /* DMAMUX_3: Source 23 */
    DMAMUX3_GTM_ATOM1_IRQ3          = 216U, /* DMAMUX_3: Source 24 */
    DMAMUX3_GTM_MCS1_IRQ4           = 217U, /* DMAMUX_3: Source 25 */
    DMAMUX3_GTM_MCS1_IRQ5           = 218U, /* DMAMUX_3: Source 26 */
    DMAMUX3_GTM_MCS1_IRQ6           = 219U, /* DMAMUX_3: Source 27 */
    DMAMUX3_GTM_MCS1_IRQ7           = 220U, /* DMAMUX_3: Source 28 */
    DMAMUX3_GTM_TIM2_IRQ4           = 221U, /* DMAMUX_3: Source 29 */
    DMAMUX3_GTM_TIM2_IRQ5           = 222U, /* DMAMUX_3: Source 30 */
    DMAMUX3_GTM_TIM2_IRQ6           = 223U, /* DMAMUX_3: Source 31 */
    DMAMUX3_GTM_TIM2_IRQ7           = 224U, /* DMAMUX_3: Source 32 */
    DMAMUX3_GTM_ATOM2_IRQ2          = 225U, /* DMAMUX_3: Source 33 */
    DMAMUX3_GTM_ATOM2_IRQ3          = 226U, /* DMAMUX_3: Source 34 */
    DMAMUX3_GTM_MCS2_IRQ4           = 227U, /* DMAMUX_3: Source 35 */
    DMAMUX3_GTM_MCS2_IRQ5           = 228U, /* DMAMUX_3: Source 36 */
    DMAMUX3_GTM_MCS2_IRQ6           = 229U, /* DMAMUX_3: Source 37 */
    DMAMUX3_GTM_MCS2_IRQ7           = 230U, /* DMAMUX_3: Source 38 */
    DMAMUX3_GTM_ATOM3_IRQ2          = 231U, /* DMAMUX_3: Source 39 */
    DMAMUX3_GTM_ATOM3_IRQ3          = 232U, /* DMAMUX_3: Source 40 */
    DMAMUX3_SIUL2_REQ8              = 233U, /* DMAMUX_3: Source 41 */
    DMAMUX3_SIUL2_REQ3              = 234U, /* DMAMUX_3: Source 42 */
    DMAMUX3_ADC_SD_3_EOC            = 235U, /* DMAMUX_3: Source 43 */
    DMAMUX3_ADC_SAR_6_EOC           = 236U, /* DMAMUX_3: Source 44 */
    DMAMUX3_DSPI_2_CMD              = 237U, /* DMAMUX_3: Source 45 */
    DMAMUX3_DSPI_1_RX               = 238U, /* DMAMUX_3: Source 46 */
    DMAMUX3_DSPI_1_TX               = 239U, /* DMAMUX_3: Source 47 */
    DMAMUX3_ADC_SAR_2_EOC           = 240U, /* DMAMUX_3: Source 48 */
    DMAMUX3_ADC_SD_2_EOC            = 241U, /* DMAMUX_3: Source 49 */
    DMAMUX3_PSI5_S_TX               = 242U, /* DMAMUX_3: Source 50 */
    DMAMUX3_EQADC2_ADC45_RFIFO0     = 243U, /* DMAMUX_3: Source 51 */
    DMAMUX3_EQADC2_ADC45_RFIFO1     = 244U, /* DMAMUX_3: Source 52 */
    DMAMUX3_EQADC2_ADC45_RFIFO2     = 245U, /* DMAMUX_3: Source 53 */
    DMAMUX3_EQADC2_ADC45_RFIFO3     = 246U, /* DMAMUX_3: Source 54 */
    DMAMUX3_EQADC2_ADC45_RFIFO4     = 247U, /* DMAMUX_3: Source 55 */
    DMAMUX3_EQADC2_ADC45_RFIFO5     = 248U, /* DMAMUX_3: Source 56 */
    DMAMUX3_EQADC2_ADC45_CFIFO0     = 249U, /* DMAMUX_3: Source 57 */
    DMAMUX3_EQADC2_ADC45_CFIFO1     = 250U, /* DMAMUX_3: Source 58 */
    DMAMUX3_EQADC2_ADC45_CFIFO2     = 251U, /* DMAMUX_3: Source 59 */
    DMAMUX3_EQADC2_ADC45_CFIFO3     = 252U, /* DMAMUX_3: Source 60 */
    DMAMUX3_EQADC2_ADC45_CFIFO4     = 253U, /* DMAMUX_3: Source 61 */
    DMAMUX3_EQADC2_ADC45_CFIFO5     = 254U, /* DMAMUX_3: Source 62 */
    DMAMUX3_ALWAYS_ON_0             = 255U, /* DMAMUX_3: Source 63 */

    /* DMAMUX_4: DMAMUX Channel 32 - 47 (eDMA_0 Channel 32 - 47) */
    DMAMUX4_RESERVED_0_A            = 256U, /* DMAMUX_4: Source 0  */
    DMAMUX4_ADC_SAR_4_EOC           = 257U, /* DMAMUX_4: Source 1  */
    DMAMUX4_ADC_SAR_6_EOC           = 258U, /* DMAMUX_4: Source 2  */
    DMAMUX4_ADC_SD_2_EOC            = 259U, /* DMAMUX_4: Source 3  */
    DMAMUX4_ADC_SD_3_EOC            = 260U, /* DMAMUX_4: Source 4  */
    DMAMUX4_DSPI_3_RX               = 261U, /* DMAMUX_4: Source 5  */
    DMAMUX4_DSPI_3_TX               = 262U, /* DMAMUX_4: Source 6  */
    DMAMUX4_LIN_0_RX                = 263U, /* DMAMUX_4: Source 7  */
    DMAMUX4_LIN_0_TX                = 264U, /* DMAMUX_4: Source 8  */
    DMAMUX4_LIN_14_RX               = 265U, /* DMAMUX_4: Source 9  */
    DMAMUX4_LIN_14_TX               = 266U, /* DMAMUX_4: Source 10 */
    DMAMUX4_PSI5_0_CH1_RX_PSI5      = 267U, /* DMAMUX_4: Source 11 */
    DMAMUX4_PSI5_0_CH1_RX_SENT      = 268U, /* DMAMUX_4: Source 12 */
    DMAMUX4_SIPI_CH0                = 269U, /* DMAMUX_4: Source 13 */
    DMAMUX4_SIPI_CH1                = 270U, /* DMAMUX_4: Source 14 */
    DMAMUX4_SIUL2_REQ9              = 271U, /* DMAMUX_4: Source 15 */
    DMAMUX4_GTM_TIM0_IRQ0           = 272U, /* DMAMUX_4: Source 16 */
    DMAMUX4_GTM_TIM0_IRQ1           = 273U, /* DMAMUX_4: Source 17 */
    DMAMUX4_GTM_TOM0_IRQ0           = 274U, /* DMAMUX_4: Source 18 */
    DMAMUX4_GTM_TOM0_IRQ1           = 275U, /* DMAMUX_4: Source 19 */
    DMAMUX4_GTM_PSM0_IRQ0           = 276U, /* DMAMUX_4: Source 20 */
    DMAMUX4_GTM_PSM0_IRQ1           = 277U, /* DMAMUX_4: Source 21 */
    DMAMUX4_GTM_PSM0_IRQ2           = 278U, /* DMAMUX_4: Source 22 */
    DMAMUX4_GTM_PSM0_IRQ3           = 279U, /* DMAMUX_4: Source 23 */
    DMAMUX4_GTM_TOM1_IRQ0           = 280U, /* DMAMUX_4: Source 24 */
    DMAMUX4_GTM_TOM1_IRQ1           = 281U, /* DMAMUX_4: Source 25 */
    DMAMUX4_GTM_TIM3_IRQ0           = 282U, /* DMAMUX_4: Source 26 */
    DMAMUX4_GTM_TIM3_IRQ1           = 283U, /* DMAMUX_4: Source 27 */
    DMAMUX4_GTM_TIM3_IRQ2           = 284U, /* DMAMUX_4: Source 28 */
    DMAMUX4_GTM_TIM3_IRQ3           = 285U, /* DMAMUX_4: Source 29 */
    DMAMUX4_GTM_MCS3_IRQ0           = 286U, /* DMAMUX_4: Source 30 */
    DMAMUX4_GTM_MCS3_IRQ1           = 287U, /* DMAMUX_4: Source 31 */
    DMAMUX4_GTM_MCS3_IRQ2           = 288U, /* DMAMUX_4: Source 32 */
    DMAMUX4_GTM_MCS3_IRQ3           = 289U, /* DMAMUX_4: Source 33 */
    DMAMUX4_DSPI_3_CMD              = 290U, /* DMAMUX_4: Source 34 */
    DMAMUX4_ADC_SD_1_EOC            = 291U, /* DMAMUX_4: Source 35 */
    DMAMUX4_ADC_SD_4_EOC            = 292U, /* DMAMUX_4: Source 36 */
    DMAMUX4_ADC_SD_5_EOC            = 293U, /* DMAMUX_4: Source 37 */
    DMAMUX4_ADC_SAR_0_EOC           = 294U, /* DMAMUX_4: Source 38 */
    DMAMUX4_DSPI_0_CMD              = 295U, /* DMAMUX_4: Source 39 */
    DMAMUX4_DSPI_0_RX               = 296U, /* DMAMUX_4: Source 40 */
    DMAMUX4_DSPI_0_TX               = 297U, /* DMAMUX_4: Source 41 */
    DMAMUX4_AMU0                    = 298U, /* DMAMUX_4: Source 42 */
    DMAMUX4_MCAN_5                  = 299U, /* DMAMUX_4: Source 43 */
    DMAMUX4_MCAN_6                  = 300U, /* DMAMUX_4: Source 44 */
    DMAMUX4_SIUL2_REQ6              = 301U, /* DMAMUX_4: Source 45 */
    DMAMUX4_SIUL2_REQ7              = 302U, /* DMAMUX_4: Source 46 */
    DMAMUX4_SIUL2_REQ12             = 303U, /* DMAMUX_4: Source 47 */
    DMAMUX4_SIUL2_REQ13             = 304U, /* DMAMUX_4: Source 48 */
    DMAMUX4_SIUL2_REQ14             = 305U, /* DMAMUX_4: Source 49 */
    DMAMUX4_SIUL2_REQ15             = 306U, /* DMAMUX_4: Source 50 */
    DMAMUX4_EQADC3_ADC67_RFIFO0     = 307U, /* DMAMUX_4: Source 51 */
    DMAMUX4_EQADC3_ADC67_RFIFO1     = 308U, /* DMAMUX_4: Source 52 */
    DMAMUX4_EQADC3_ADC67_RFIFO2     = 309U, /* DMAMUX_4: Source 53 */
    DMAMUX4_EQADC3_ADC67_RFIFO3     = 310U, /* DMAMUX_4: Source 54 */
    DMAMUX4_EQADC3_ADC67_RFIFO4     = 311U, /* DMAMUX_4: Source 55 */
    DMAMUX4_EQADC3_ADC67_RFIFO5     = 312U, /* DMAMUX_4: Source 56 */
    DMAMUX4_EQADC3_ADC67_CFIFO0     = 313U, /* DMAMUX_4: Source 57 */
    DMAMUX4_EQADC3_ADC67_CFIFO1     = 314U, /* DMAMUX_4: Source 58 */
    DMAMUX4_EQADC3_ADC67_CFIFO2     = 315U, /* DMAMUX_4: Source 59 */
    DMAMUX4_EQADC3_ADC67_CFIFO3     = 316U, /* DMAMUX_4: Source 60 */
    DMAMUX4_EQADC3_ADC67_CFIFO4     = 317U, /* DMAMUX_4: Source 61 */
    DMAMUX4_EQADC3_ADC67_CFIFO5     = 318U, /* DMAMUX_4: Source 62 */
    DMAMUX4_ALWAYS_ON_0             = 319U, /* DMAMUX_4: Source 63 */

    /* DMAMUX_5: DMAMUX Channel 48 - 63 (eDMA_0 Channel 48 - 63) */
    DMAMUX5_RESERVED_0_A            = 320U, /* DMAMUX_5: Source 0  */
    DMAMUX5_ADC_SAR_7_EOC           = 321U, /* DMAMUX_5: Source 1  */
    DMAMUX5_ADC_SD_4_EOC            = 322U, /* DMAMUX_5: Source 2  */
    DMAMUX5_ADC_SD_5_EOC            = 323U, /* DMAMUX_5: Source 3  */
    DMAMUX5_DSPI_5_RX               = 324U, /* DMAMUX_5: Source 4  */
    DMAMUX5_DSPI_5_TX               = 325U, /* DMAMUX_5: Source 5  */
    DMAMUX5_LIN_1_RX                = 326U, /* DMAMUX_5: Source 6  */
    DMAMUX5_LIN_1_TX                = 327U, /* DMAMUX_5: Source 7  */
    DMAMUX5_LIN_15_RX               = 328U, /* DMAMUX_5: Source 8  */
    DMAMUX5_LIN_15_TX               = 329U, /* DMAMUX_5: Source 9  */
    DMAMUX5_SENT_0_FAST             = 330U, /* DMAMUX_5: Source 10 */
    DMAMUX5_SENT_0_SLOW             = 331U, /* DMAMUX_5: Source 11 */
    DMAMUX5_SIPI_CH2                = 332U, /* DMAMUX_5: Source 12 */
    DMAMUX5_SIPI_CH3                = 333U, /* DMAMUX_5: Source 13 */
    DMAMUX5_SIUL2_REQ10             = 334U, /* DMAMUX_5: Source 14 */
    DMAMUX5_GTM_TIM0_IRQ2           = 335U, /* DMAMUX_5: Source 15 */
    DMAMUX5_GTM_TIM0_IRQ3           = 336U, /* DMAMUX_5: Source 16 */
    DMAMUX5_GTM_TIM0_IRQ4           = 337U, /* DMAMUX_5: Source 17 */
    DMAMUX5_GTM_TIM0_IRQ5           = 338U, /* DMAMUX_5: Source 18 */
    DMAMUX5_GTM_PSM0_IRQ4           = 339U, /* DMAMUX_5: Source 19 */
    DMAMUX5_GTM_PSM0_IRQ5           = 340U, /* DMAMUX_5: Source 20 */
    DMAMUX5_GTM_PSM0_IRQ6           = 341U, /* DMAMUX_5: Source 21 */
    DMAMUX5_GTM_PSM0_IRQ7           = 342U, /* DMAMUX_5: Source 22 */
    DMAMUX5_GTM_TOM1_IRQ4           = 343U, /* DMAMUX_5: Source 23 */
    DMAMUX5_GTM_TOM1_IRQ5           = 344U, /* DMAMUX_5: Source 24 */
    DMAMUX5_GTM_TIM3_IRQ4           = 345U, /* DMAMUX_5: Source 25 */
    DMAMUX5_GTM_TIM3_IRQ5           = 346U, /* DMAMUX_5: Source 26 */
    DMAMUX5_GTM_TIM3_IRQ6           = 347U, /* DMAMUX_5: Source 27 */
    DMAMUX5_GTM_TIM3_IRQ7           = 348U, /* DMAMUX_5: Source 28 */
    DMAMUX5_GTM_MCS3_IRQ4           = 349U, /* DMAMUX_5: Source 29 */
    DMAMUX5_GTM_MCS3_IRQ5           = 350U, /* DMAMUX_5: Source 30 */
    DMAMUX5_GTM_MCS3_IRQ6           = 351U, /* DMAMUX_5: Source 31 */
    DMAMUX5_GTM_MCS3_IRQ7           = 352U, /* DMAMUX_5: Source 32 */
    DMAMUX5_DSPI_5_CMD              = 353U, /* DMAMUX_5: Source 33 */
    DMAMUX5_MCAN_1                  = 354U, /* DMAMUX_5: Source 34 */
    DMAMUX5_MCAN_2                  = 355U, /* DMAMUX_5: Source 35 */
    DMAMUX5_DSPI3_RX                = 356U, /* DMAMUX_5: Source 36 */
    DMAMUX5_DSPI3_TX                = 357U, /* DMAMUX_5: Source 37 */
    DMAMUX5_ADC_SAR_3_EOC           = 358U, /* DMAMUX_5: Source 38 */
    DMAMUX5_LIN_2_RX                = 359U, /* DMAMUX_5: Source 39 */
    DMAMUX5_LIN_2_TX                = 360U, /* DMAMUX_5: Source 40 */
    DMAMUX5_ADC_SAR_1_EOC           = 361U, /* DMAMUX_5: Source 41 */
    DMAMUX5_AMU1                    = 362U, /* DMAMUX_5: Source 42 */
    DMAMUX5_MCAN_7                  = 363U, /* DMAMUX_5: Source 43 */
    DMAMUX5_MCAN_8                  = 364U, /* DMAMUX_5: Source 44 */
    DMAMUX5_MCAN_9                  = 365U, /* DMAMUX_5: Source 45 */
    DMAMUX5_MCAN_10                 = 366U, /* DMAMUX_5: Source 46 */
    DMAMUX5_MCAN_11                 = 367U, /* DMAMUX_5: Source 47 */
    DMAMUX5_MCAN_12                 = 368U, /* DMAMUX_5: Source 48 */
    DMAMUX5_RESERVED_1_A            = 369U, /* DMAMUX_5: Source 49 */
    DMAMUX5_RESERVED_2_A            = 370U, /* DMAMUX_5: Source 50 */
    DMAMUX5_EQADC4_ADC89_RFIFO0     = 371U, /* DMAMUX_5: Source 51 */
    DMAMUX5_EQADC4_ADC89_RFIFO1     = 372U, /* DMAMUX_5: Source 52 */
    DMAMUX5_EQADC4_ADC89_RFIFO2     = 373U, /* DMAMUX_5: Source 53 */
    DMAMUX5_EQADC4_ADC89_RFIFO3     = 374U, /* DMAMUX_5: Source 54 */
    DMAMUX5_EQADC4_ADC89_RFIFO4     = 375U, /* DMAMUX_5: Source 55 */
    DMAMUX5_EQADC4_ADC89_RFIFO5     = 376U, /* DMAMUX_5: Source 56 */
    DMAMUX5_EQADC4_ADC89_CFIFO0     = 377U, /* DMAMUX_5: Source 57 */
    DMAMUX5_EQADC4_ADC89_CFIFO1     = 378U, /* DMAMUX_5: Source 58 */
    DMAMUX5_EQADC4_ADC89_CFIFO2     = 379U, /* DMAMUX_5: Source 59 */
    DMAMUX5_EQADC4_ADC89_CFIFO3     = 380U, /* DMAMUX_5: Source 60 */
    DMAMUX5_EQADC4_ADC89_CFIFO4     = 381U, /* DMAMUX_5: Source 61 */
    DMAMUX5_EQADC4_ADC89_CFIFO5     = 382U, /* DMAMUX_5: Source 62 */
    DMAMUX5_ALWAYS_ON_0             = 383U, /* DMAMUX_5: Source 63 */

    /* DMAMUX_6: DMAMUX Channel 64 - 79 (eDMA_1 Channel 0 - 15) */
    DMAMUX6_RESERVED_0_A            = 384U, /* DMAMUX_6: Source 0  */
    DMAMUX6_ADC_SAR_8_EOC           = 385U, /* DMAMUX_6: Source 1  */
    DMAMUX6_ADC_SAR_9_EOC           = 386U, /* DMAMUX_6: Source 2  */
    DMAMUX6_ADC_SAR_10_EOC          = 387U, /* DMAMUX_6: Source 3  */
    DMAMUX6_ADC_SAR_5_EOC           = 388U, /* DMAMUX_6: Source 4  */
    DMAMUX6_ADC_SD_6_EOC            = 389U, /* DMAMUX_6: Source 5  */
    DMAMUX6_ADC_SD_7_EOC            = 390U, /* DMAMUX_6: Source 6  */
    DMAMUX6_ADC_SD_8_EOC            = 391U, /* DMAMUX_6: Source 7  */
    DMAMUX6_ADC_SD_9_EOC            = 392U, /* DMAMUX_6: Source 8  */
    DMAMUX6_PSI5_0_CH2_RX_PSI5      = 393U, /* DMAMUX_6: Source 9  */
    DMAMUX6_PSI5_0_CH2_RX_SENT      = 394U, /* DMAMUX_6: Source 10 */
    DMAMUX6_PSI5_1_CH1_RX_PSI5      = 395U, /* DMAMUX_6: Source 11 */
    DMAMUX6_PSI5_1_CH1_RX_SENT      = 396U, /* DMAMUX_6: Source 12 */
    DMAMUX6_DSPI_6_RX               = 397U, /* DMAMUX_6: Source 13 */
    DMAMUX6_DSPI_6_TX               = 398U, /* DMAMUX_6: Source 14 */
    DMAMUX6_DSPI_6_CMD              = 399U, /* DMAMUX_6: Source 15 */
    DMAMUX6_LIN_16_RX               = 400U, /* DMAMUX_6: Source 16 */
    DMAMUX6_LIN_16_TX               = 401U, /* DMAMUX_6: Source 17 */
    DMAMUX6_I2C_1_RX                = 402U, /* DMAMUX_6: Source 18 */
    DMAMUX6_I2C_1_TX                = 403U, /* DMAMUX_6: Source 19 */
    DMAMUX6_GTM_PSM1_IRQ0           = 404U, /* DMAMUX_6: Source 20 */
    DMAMUX6_GTM_PSM1_IRQ1           = 405U, /* DMAMUX_6: Source 21 */
    DMAMUX6_GTM_PSM1_IRQ2           = 406U, /* DMAMUX_6: Source 22 */
    DMAMUX6_GTM_PSM1_IRQ3           = 407U, /* DMAMUX_6: Source 23 */
    DMAMUX6_DSPI_1_CMD              = 408U, /* DMAMUX_6: Source 24 */
    DMAMUX6_DSPI_1_RX               = 409U, /* DMAMUX_6: Source 25 */
    DMAMUX6_DSPI_1_TX               = 410U, /* DMAMUX_6: Source 26 */
    DMAMUX6_DSPI_12_CMD             = 411U, /* DMAMUX_6: Source 27 */
    DMAMUX6_DSPI_12_RX              = 412U, /* DMAMUX_6: Source 28 */
    DMAMUX6_DSPI_12_TX              = 413U, /* DMAMUX_6: Source 29 */
    DMAMUX6_SENT_1_RX_FAST          = 414U, /* DMAMUX_6: Source 30 */
    DMAMUX6_SENT_1_RX_SLOW          = 415U, /* DMAMUX_6: Source 31 */
    DMAMUX6_GTM_TOM1_IRQ0           = 416U, /* DMAMUX_6: Source 32 */
    DMAMUX6_GTM_TOM1_IRQ1           = 417U, /* DMAMUX_6: Source 33 */
    DMAMUX6_GTM_TOM1_IRQ2           = 418U, /* DMAMUX_6: Source 34 */
    DMAMUX6_GTM_TOM1_IRQ3           = 419U, /* DMAMUX_6: Source 35 */
    DMAMUX6_GTM_TOM1_IRQ4           = 420U, /* DMAMUX_6: Source 36 */
    DMAMUX6_GTM_TOM1_IRQ5           = 421U, /* DMAMUX_6: Source 37 */
    DMAMUX6_GTM_TOM1_IRQ6           = 422U, /* DMAMUX_6: Source 38 */
    DMAMUX6_GTM_TOM1_IRQ7           = 423U, /* DMAMUX_6: Source 39 */
    DMAMUX6_GTM_TOM2_IRQ0           = 424U, /* DMAMUX_6: Source 40 */
    DMAMUX6_GTM_TOM2_IRQ1           = 425U, /* DMAMUX_6: Source 41 */
    DMAMUX6_GTM_TOM2_IRQ2           = 426U, /* DMAMUX_6: Source 42 */
    DMAMUX6_GTM_TOM2_IRQ3           = 427U, /* DMAMUX_6: Source 43 */
    DMAMUX6_GTM_TOM2_IRQ4           = 428U, /* DMAMUX_6: Source 44 */
    DMAMUX6_GTM_TOM2_IRQ5           = 429U, /* DMAMUX_6: Source 45 */
    DMAMUX6_GTM_TOM2_IRQ6           = 430U, /* DMAMUX_6: Source 46 */
    DMAMUX6_GTM_TOM2_IRQ7           = 431U, /* DMAMUX_6: Source 47 */
    DMAMUX6_MCAN_3                  = 432U, /* DMAMUX_6: Source 48 */
    DMAMUX6_ETPUC_0                 = 433U, /* DMAMUX_6: Source 49 */
    DMAMUX6_ETPUC_1                 = 434U, /* DMAMUX_6: Source 50 */
    DMAMUX6_ETPUC_2                 = 435U, /* DMAMUX_6: Source 51 */
    DMAMUX6_ETPUC_3                 = 436U, /* DMAMUX_6: Source 52 */
    DMAMUX6_ETPUC_4                 = 437U, /* DMAMUX_6: Source 53 */
    DMAMUX6_ETPUC_5                 = 438U, /* DMAMUX_6: Source 54 */
    DMAMUX6_ETPUC_6                 = 439U, /* DMAMUX_6: Source 55 */
    DMAMUX6_ETPUC_7                 = 440U, /* DMAMUX_6: Source 56 */
#if defined(CCFC3008PT)
    DMAMUX6_RESERVED_1              = 441U, /* DMAMUX_6: Source 57 */
    DMAMUX6_RESERVED_2              = 442U, /* DMAMUX_6: Source 58 */
    DMAMUX6_RESERVED_3              = 443U, /* DMAMUX_6: Source 59 */
    DMAMUX6_RESERVED_4              = 444U, /* DMAMUX_6: Source 60 */
#endif
#if defined(CCFC3007PT)
    DMAMUX6_I2S_0_TX                = 441U, /* DMAMUX_6: Source 57 */
    DMAMUX6_I2S_0_RX                = 442U, /* DMAMUX_6: Source 58 */
    DMAMUX6_I2S_1_TX                = 443U, /* DMAMUX_6: Source 59 */
    DMAMUX6_I2S_1_RX                = 444U, /* DMAMUX_6: Source 60 */
#endif
    DMAMUX6_RESERVED_5              = 445U, /* DMAMUX_6: Source 61 */
    DMAMUX6_RESERVED_6              = 446U, /* DMAMUX_6: Source 62 */
    DMAMUX6_ALWAYS_ON_0             = 447U, /* DMAMUX_6: Source 63 */

    /* DMAMUX_7: DMAMUX Channel 80 - 95 (eDMA_1 Channel 16 - 31) */
    DMAMUX7_RESERVED_0_A            = 448U, /* DMAMUX_7: Source 0  */
    DMAMUX7_GTM_MCS4_IRQ0           = 449U, /* DMAMUX_7: Source 1  */
    DMAMUX7_GTM_MCS4_IRQ1           = 450U, /* DMAMUX_7: Source 2  */
    DMAMUX7_GTM_MCS4_IRQ2           = 451U, /* DMAMUX_7: Source 3  */
    DMAMUX7_GTM_MCS4_IRQ3           = 452U, /* DMAMUX_7: Source 4  */
    DMAMUX7_GTM_MCS4_IRQ4           = 453U, /* DMAMUX_7: Source 5  */
    DMAMUX7_GTM_MCS4_IRQ5           = 454U, /* DMAMUX_7: Source 6  */
    DMAMUX7_GTM_MCS4_IRQ6           = 455U, /* DMAMUX_7: Source 7  */
    DMAMUX7_GTM_MCS4_IRQ7           = 456U, /* DMAMUX_7: Source 8  */
    DMAMUX7_GTM_MCS5_IRQ0           = 457U, /* DMAMUX_7: Source 9  */
    DMAMUX7_GTM_MCS5_IRQ1           = 458U, /* DMAMUX_7: Source 10 */
    DMAMUX7_GTM_MCS5_IRQ2           = 459U, /* DMAMUX_7: Source 11 */
    DMAMUX7_GTM_MCS5_IRQ3           = 460U, /* DMAMUX_7: Source 12 */
    DMAMUX7_GTM_MCS5_IRQ4           = 461U, /* DMAMUX_7: Source 13 */
    DMAMUX7_GTM_MCS5_IRQ5           = 462U, /* DMAMUX_7: Source 14 */
    DMAMUX7_GTM_MCS5_IRQ6           = 463U, /* DMAMUX_7: Source 15 */
    DMAMUX7_GTM_MCS5_IRQ7           = 464U, /* DMAMUX_7: Source 16 */
    DMAMUX7_GTM_ATOM5_IRQ0          = 465U, /* DMAMUX_7: Source 17 */
    DMAMUX7_GTM_ATOM5_IRQ1          = 466U, /* DMAMUX_7: Source 18 */
    DMAMUX7_GTM_ATOM5_IRQ2          = 467U, /* DMAMUX_7: Source 19 */
    DMAMUX7_GTM_ATOM5_IRQ3          = 468U, /* DMAMUX_7: Source 20 */
    DMAMUX7_GTM_ATOM6_IRQ0          = 469U, /* DMAMUX_7: Source 21 */
    DMAMUX7_GTM_ATOM6_IRQ1          = 470U, /* DMAMUX_7: Source 22 */
    DMAMUX7_GTM_ATOM6_IRQ2          = 471U, /* DMAMUX_7: Source 23 */
    DMAMUX7_GTM_ATOM6_IRQ3          = 472U, /* DMAMUX_7: Source 24 */
    DMAMUX7_GTM_TOM3_IRQ0           = 473U, /* DMAMUX_7: Source 25 */
    DMAMUX7_GTM_TOM3_IRQ1           = 474U, /* DMAMUX_7: Source 26 */
    DMAMUX7_GTM_TOM3_IRQ2           = 475U, /* DMAMUX_7: Source 27 */
    DMAMUX7_GTM_TOM3_IRQ3           = 476U, /* DMAMUX_7: Source 28 */
    DMAMUX7_GTM_TOM3_IRQ4           = 477U, /* DMAMUX_7: Source 29 */
    DMAMUX7_GTM_TOM3_IRQ5           = 478U, /* DMAMUX_7: Source 30 */
    DMAMUX7_GTM_TOM3_IRQ6           = 479U, /* DMAMUX_7: Source 31 */
    DMAMUX7_GTM_TOM3_IRQ7           = 480U, /* DMAMUX_7: Source 32 */
    DMAMUX7_ADC_SD_6_EOC            = 481U, /* DMAMUX_7: Source 33 */
    DMAMUX7_ADC_SD_7_EOC            = 482U, /* DMAMUX_7: Source 34 */
    DMAMUX7_PSI5_0_CH0_RX_PSI5      = 483U, /* DMAMUX_7: Source 35 */
    DMAMUX7_PSI5_0_CH0_RX_SENT      = 484U, /* DMAMUX_7: Source 36 */
    DMAMUX7_PSI5_0_CH1_RX_PSI5      = 485U, /* DMAMUX_7: Source 37 */
    DMAMUX7_PSI5_0_CH1_RX_SENT      = 486U, /* DMAMUX_7: Source 38 */
    DMAMUX7_PSI5_0_CH2_RX_PSI5      = 487U, /* DMAMUX_7: Source 39 */
    DMAMUX7_PSI5_0_CH2_RX_SENT      = 488U, /* DMAMUX_7: Source 40 */
    DMAMUX7_ADC_SD_0_EOC            = 489U, /* DMAMUX_7: Source 41 */
    DMAMUX7_ADC_SD_1_EOC            = 490U, /* DMAMUX_7: Source 42 */
    DMAMUX7_ADC_SD_2_EOC            = 491U, /* DMAMUX_7: Source 43 */
    DMAMUX7_ADC_SD_3_EOC            = 492U, /* DMAMUX_7: Source 44 */
    DMAMUX7_DSPI_3_CMD              = 493U, /* DMAMUX_7: Source 45 */
    DMAMUX7_DSPI_3_RX               = 494U, /* DMAMUX_7: Source 46 */
    DMAMUX7_DSPI_3_TX               = 495U, /* DMAMUX_7: Source 47 */
    DMAMUX7_DSPI_5_CMD              = 496U, /* DMAMUX_7: Source 48 */
    DMAMUX7_DSPI_5_RX               = 497U, /* DMAMUX_7: Source 49 */
    DMAMUX7_DSPI_5_TX               = 498U, /* DMAMUX_7: Source 50 */
    DMAMUX7_MCAN_4                  = 499U, /* DMAMUX_7: Source 51 */
#if defined(CCFC3008PT)
    DMAMUX7_RESERVED_1              = 500U, /* DMAMUX_7: Source 52 */
    DMAMUX7_RESERVED_2              = 501U, /* DMAMUX_7: Source 53 */
    DMAMUX7_RESERVED_3              = 502U, /* DMAMUX_7: Source 54 */
    DMAMUX7_RESERVED_4              = 503U, /* DMAMUX_7: Source 55 */
#endif
#if defined(CCFC3007PT)
    DMAMUX7_SSI_0_TX                = 500U, /* DMAMUX_7: Source 52 */
	DMAMUX7_SSI_0_RX                = 501U, /* DMAMUX_7: Source 53 */
	DMAMUX7_SSI_1_TX                = 502U, /* DMAMUX_7: Source 54 */
	DMAMUX7_SSI_1_RX                = 503U, /* DMAMUX_7: Source 55 */
#endif
    DMAMUX7_RESERVED_5              = 504U, /* DMAMUX_7: Source 56 */
    DMAMUX7_RESERVED_6              = 505U, /* DMAMUX_7: Source 57 */
    DMAMUX7_RESERVED_7              = 506U, /* DMAMUX_7: Source 58 */
    DMAMUX7_RESERVED_8              = 507U, /* DMAMUX_7: Source 59 */
    DMAMUX7_RESERVED_9              = 508U, /* DMAMUX_7: Source 60 */
    DMAMUX7_RESERVED_10             = 509U, /* DMAMUX_7: Source 61 */
    DMAMUX7_RESERVED_11             = 510U, /* DMAMUX_7: Source 62 */
    DMAMUX7_ALWAYS_ON_0             = 511U, /* DMAMUX_7: Source 63 */

    /* DMAMUX_8: DMAMUX Channel 96 - 111 (eDMA_1 Channel 32 - 47) */
    DMAMUX8_RESERVED_0_A            = 512U, /* DMAMUX_8: Source 0  */
    DMAMUX8_GTM_TIM4_IRQ0           = 513U, /* DMAMUX_8: Source 1  */
    DMAMUX8_GTM_TIM4_IRQ1           = 514U, /* DMAMUX_8: Source 2  */
    DMAMUX8_GTM_TIM4_IRQ2           = 515U, /* DMAMUX_8: Source 3  */
    DMAMUX8_GTM_TIM4_IRQ3           = 516U, /* DMAMUX_8: Source 4  */
    DMAMUX8_GTM_TIM4_IRQ4           = 517U, /* DMAMUX_8: Source 5  */
    DMAMUX8_GTM_TIM4_IRQ5           = 518U, /* DMAMUX_8: Source 6  */
    DMAMUX8_GTM_TIM4_IRQ6           = 519U, /* DMAMUX_8: Source 7  */
    DMAMUX8_GTM_TIM4_IRQ7           = 520U, /* DMAMUX_8: Source 8  */
    DMAMUX8_GTM_TIM5_IRQ0           = 521U, /* DMAMUX_8: Source 9  */
    DMAMUX8_GTM_TIM5_IRQ1           = 522U, /* DMAMUX_8: Source 10 */
    DMAMUX8_GTM_TIM5_IRQ2           = 523U, /* DMAMUX_8: Source 11 */
    DMAMUX8_GTM_TIM5_IRQ3           = 524U, /* DMAMUX_8: Source 12 */
    DMAMUX8_GTM_TIM5_IRQ4           = 525U, /* DMAMUX_8: Source 13 */
    DMAMUX8_GTM_TIM5_IRQ5           = 526U, /* DMAMUX_8: Source 14 */
    DMAMUX8_GTM_TIM5_IRQ6           = 527U, /* DMAMUX_8: Source 15 */
    DMAMUX8_GTM_TIM5_IRQ7           = 528U, /* DMAMUX_8: Source 16 */
    DMAMUX8_GTM_ATOM7_IRQ0          = 529U, /* DMAMUX_8: Source 17 */
    DMAMUX8_GTM_ATOM7_IRQ1          = 530U, /* DMAMUX_8: Source 18 */
    DMAMUX8_GTM_ATOM7_IRQ2          = 531U, /* DMAMUX_8: Source 19 */
    DMAMUX8_GTM_ATOM7_IRQ3          = 532U, /* DMAMUX_8: Source 20 */
    DMAMUX8_GTM_ATOM8_IRQ0          = 533U, /* DMAMUX_8: Source 21 */
    DMAMUX8_GTM_ATOM8_IRQ1          = 534U, /* DMAMUX_8: Source 22 */
    DMAMUX8_GTM_ATOM8_IRQ2          = 535U, /* DMAMUX_8: Source 23 */
    DMAMUX8_GTM_ATOM8_IRQ3          = 536U, /* DMAMUX_8: Source 24 */
    DMAMUX8_GTM_TOM4_IRQ0           = 537U, /* DMAMUX_8: Source 25 */
    DMAMUX8_GTM_TOM4_IRQ1           = 538U, /* DMAMUX_8: Source 26 */
    DMAMUX8_GTM_TOM4_IRQ2           = 539U, /* DMAMUX_8: Source 27 */
    DMAMUX8_GTM_TOM4_IRQ3           = 540U, /* DMAMUX_8: Source 28 */
    DMAMUX8_GTM_TOM4_IRQ4           = 541U, /* DMAMUX_8: Source 29 */
    DMAMUX8_GTM_TOM4_IRQ5           = 542U, /* DMAMUX_8: Source 30 */
    DMAMUX8_GTM_TOM4_IRQ6           = 543U, /* DMAMUX_8: Source 31 */
    DMAMUX8_GTM_TOM4_IRQ7           = 544U, /* DMAMUX_8: Source 32 */
    DMAMUX8_ADC_SD_8_EOC            = 545U, /* DMAMUX_8: Source 33 */
    DMAMUX8_PSI5_1_CH0_RX_PSI5      = 546U, /* DMAMUX_8: Source 34 */
    DMAMUX8_PSI5_1_CH0_RX_SENT      = 547U, /* DMAMUX_8: Source 35 */
    DMAMUX8_PSI5_1_CH1_RX_PSI5      = 548U, /* DMAMUX_8: Source 36 */
    DMAMUX8_PSI5_1_CH1_RX_SENT      = 549U, /* DMAMUX_8: Source 37 */
    DMAMUX8_ADC_SAR_0_EOC           = 550U, /* DMAMUX_8: Source 38 */
    DMAMUX8_ADC_SAR_1_EOC           = 551U, /* DMAMUX_8: Source 39 */
    DMAMUX8_ADC_SAR_2_EOC           = 552U, /* DMAMUX_8: Source 40 */
    DMAMUX8_ADC_SAR_B_EOC           = 553U, /* DMAMUX_8: Source 41 */
    DMAMUX8_ADC_SD_4_EOC            = 554U, /* DMAMUX_8: Source 42 */
    DMAMUX8_DSPI_4_CMD              = 555U, /* DMAMUX_8: Source 43 */
    DMAMUX8_DSPI_4_RX               = 556U, /* DMAMUX_8: Source 44 */
    DMAMUX8_DSPI_4_TX               = 557U, /* DMAMUX_8: Source 45 */
#if defined(CCFC3008PT)
    DMAMUX8_RESERVED_1              = 558U, /* DMAMUX_8: Source 46 */
    DMAMUX8_RESERVED_2              = 559U, /* DMAMUX_8: Source 47 */
    DMAMUX8_RESERVED_3              = 560U, /* DMAMUX_8: Source 48 */
    DMAMUX8_RESERVED_4              = 561U, /* DMAMUX_8: Source 49 */
    DMAMUX8_RESERVED_5              = 562U, /* DMAMUX_8: Source 50 */
    DMAMUX8_RESERVED_6              = 563U, /* DMAMUX_8: Source 51 */
    DMAMUX8_RESERVED_7              = 564U, /* DMAMUX_8: Source 52 */
    DMAMUX8_RESERVED_8              = 565U, /* DMAMUX_8: Source 53 */
    DMAMUX8_RESERVED_9              = 566U, /* DMAMUX_8: Source 54 */
    DMAMUX8_RESERVED_10             = 567U, /* DMAMUX_8: Source 55 */
    DMAMUX8_RESERVED_11             = 568U, /* DMAMUX_8: Source 56 */
    DMAMUX8_RESERVED_12             = 569U, /* DMAMUX_8: Source 57 */
    DMAMUX8_RESERVED_13             = 570U, /* DMAMUX_8: Source 58 */
    DMAMUX8_RESERVED_14             = 571U, /* DMAMUX_8: Source 59 */
    DMAMUX8_RESERVED_15             = 572U, /* DMAMUX_8: Source 60 */
    DMAMUX8_RESERVED_16             = 573U, /* DMAMUX_8: Source 61 */
    DMAMUX8_RESERVED_17             = 574U, /* DMAMUX_8: Source 62 */
#endif
#if defined(CCFC3007PT)
    DMAMUX8_LIN_3_TX                = 558U, /* DMAMUX_8: Source 46 */
    DMAMUX8_LIN_3_RX                = 559U, /* DMAMUX_8: Source 47 */
    DMAMUX8_LIN_4_TX                = 560U, /* DMAMUX_8: Source 48 */
    DMAMUX8_LIN_4_RX                = 561U, /* DMAMUX_8: Source 49 */
    DMAMUX8_LIN_5_TX                = 562U, /* DMAMUX_8: Source 50 */
    DMAMUX8_LIN_5_RX                = 563U, /* DMAMUX_8: Source 51 */
    DMAMUX8_LIN_6_TX                = 564U, /* DMAMUX_8: Source 52 */
    DMAMUX8_LIN_6_RX                = 565U, /* DMAMUX_8: Source 53 */
    DMAMUX8_LIN_7_TX                = 566U, /* DMAMUX_8: Source 54 */
    DMAMUX8_LIN_7_RX                = 567U, /* DMAMUX_8: Source 55 */
    DMAMUX8_LIN_8_TX                = 568U, /* DMAMUX_8: Source 56 */
    DMAMUX8_LIN_8_RX                = 569U, /* DMAMUX_8: Source 57 */
    DMAMUX8_LIN_9_TX                = 570U, /* DMAMUX_8: Source 58 */
    DMAMUX8_LIN_9_RX                = 571U, /* DMAMUX_8: Source 59 */
    DMAMUX8_LIN_10_TX               = 572U, /* DMAMUX_8: Source 60 */
    DMAMUX8_LIN_10_RX               = 573U, /* DMAMUX_8: Source 61 */
    DMAMUX8_LIN_11_TX               = 574U, /* DMAMUX_8: Source 62 */
#endif
    DMAMUX8_ALWAYS_ON_0             = 575U, /* DMAMUX_8: Source 63 */

    /* DMAMUX_9: DMAMUX Channel 112 - 127 (eDMA_1 Channel 48 - 63) */
    DMAMUX9_RESERVED_0_A            = 576U, /* DMAMUX_9: Source 0  */
    DMAMUX9_GTM_PSM1_IRQ0           = 577U, /* DMAMUX_9: Source 1  */
    DMAMUX9_GTM_PSM1_IRQ1           = 578U, /* DMAMUX_9: Source 2  */
    DMAMUX9_GTM_PSM1_IRQ2           = 579U, /* DMAMUX_9: Source 3  */
    DMAMUX9_GTM_PSM1_IRQ3           = 580U, /* DMAMUX_9: Source 4  */
    DMAMUX9_GTM_PSM1_IRQ4           = 581U, /* DMAMUX_9: Source 5  */
    DMAMUX9_GTM_PSM1_IRQ5           = 582U, /* DMAMUX_9: Source 6  */
    DMAMUX9_GTM_PSM1_IRQ6           = 583U, /* DMAMUX_9: Source 7  */
    DMAMUX9_GTM_PSM1_IRQ7           = 584U, /* DMAMUX_9: Source 8  */
    DMAMUX9_GTM_SPE2                = 585U, /* DMAMUX_9: Source 9  */
    DMAMUX9_GTM_SPE3                = 586U, /* DMAMUX_9: Source 10 */
    DMAMUX9_I2C_0_RX                = 587U, /* DMAMUX_9: Source 11 */
    DMAMUX9_I2C_0_TX                = 588U, /* DMAMUX_9: Source 12 */
    DMAMUX9_GTM_ATOM5_IRQ0          = 589U, /* DMAMUX_9: Source 13 */
    DMAMUX9_GTM_ATOM5_IRQ1          = 590U, /* DMAMUX_9: Source 14 */
    DMAMUX9_GTM_ATOM7_IRQ0          = 591U, /* DMAMUX_9: Source 15 */
    DMAMUX9_GTM_ATOM7_IRQ1          = 592U, /* DMAMUX_9: Source 16 */
    DMAMUX9_GTM_TOM3_IRQ0           = 593U, /* DMAMUX_9: Source 17 */
    DMAMUX9_GTM_TOM3_IRQ1           = 594U, /* DMAMUX_9: Source 18 */
    DMAMUX9_GTM_TOM3_IRQ2           = 595U, /* DMAMUX_9: Source 19 */
    DMAMUX9_GTM_TOM3_IRQ3           = 596U, /* DMAMUX_9: Source 20 */
    DMAMUX9_GTM_TOM3_IRQ4           = 597U, /* DMAMUX_9: Source 21 */
    DMAMUX9_GTM_TOM3_IRQ5           = 598U, /* DMAMUX_9: Source 22 */
    DMAMUX9_GTM_TOM3_IRQ6           = 599U, /* DMAMUX_9: Source 23 */
    DMAMUX9_GTM_TOM3_IRQ7           = 600U, /* DMAMUX_9: Source 24 */
    DMAMUX9_GTM_TOM4_IRQ0           = 601U, /* DMAMUX_9: Source 25 */
    DMAMUX9_GTM_TOM4_IRQ1           = 602U, /* DMAMUX_9: Source 26 */
    DMAMUX9_GTM_TOM4_IRQ2           = 603U, /* DMAMUX_9: Source 27 */
    DMAMUX9_GTM_TOM4_IRQ3           = 604U, /* DMAMUX_9: Source 28 */
    DMAMUX9_GTM_TOM4_IRQ4           = 605U, /* DMAMUX_9: Source 29 */
    DMAMUX9_GTM_TOM4_IRQ5           = 606U, /* DMAMUX_9: Source 30 */
    DMAMUX9_GTM_TOM4_IRQ6           = 607U, /* DMAMUX_9: Source 31 */
    DMAMUX9_GTM_TOM4_IRQ7           = 608U, /* DMAMUX_9: Source 32 */
    DMAMUX9_ADC_SD_9_EOC            = 609U, /* DMAMUX_9: Source 33 */
    DMAMUX9_MCAN_1                  = 610U, /* DMAMUX_9: Source 34 */
    DMAMUX9_MCAN_2                  = 611U, /* DMAMUX_9: Source 35 */
    DMAMUX9_ADC_SAR_3_EOC           = 612U, /* DMAMUX_9: Source 36 */
    DMAMUX9_ADC_SAR_4_EOC           = 613U, /* DMAMUX_9: Source 37 */
    DMAMUX9_ADC_SAR_6_EOC           = 614U, /* DMAMUX_9: Source 38 */
    DMAMUX9_ADC_SAR_7_EOC           = 615U, /* DMAMUX_9: Source 39 */
    DMAMUX9_ADC_SD_5_EOC            = 616U, /* DMAMUX_9: Source 40 */
    DMAMUX9_DSPI_2_CMD              = 617U, /* DMAMUX_9: Source 41 */
    DMAMUX9_DSPI2_RX                = 618U, /* DMAMUX_9: Source 42 */
    DMAMUX9_DSPI2_TX                = 619U, /* DMAMUX_9: Source 43 */
    DMAMUX9_SIUL2_REQ11             = 620U, /* DMAMUX_9: Source 44 */
    DMAMUX9_EMIOS_0_CH0             = 621U, /* DMAMUX_9: Source 45 */
    DMAMUX9_EMIOS_0_CH1             = 622U, /* DMAMUX_9: Source 46 */
    DMAMUX9_EMIOS_0_CH2             = 623U, /* DMAMUX_9: Source 47 */
    DMAMUX9_EMIOS_0_CH3             = 624U, /* DMAMUX_9: Source 48 */
    DMAMUX9_EMIOS_0_CH4             = 625U, /* DMAMUX_9: Source 49 */
    DMAMUX9_EMIOS_0_CH6             = 626U, /* DMAMUX_9: Source 50 */
    DMAMUX9_EMIOS_0_CH7             = 627U, /* DMAMUX_9: Source 51 */
    DMAMUX9_EMIOS_0_CH16            = 628U, /* DMAMUX_9: Source 52 */
    DMAMUX9_EMIOS_0_CH17            = 629U, /* DMAMUX_9: Source 53 */
    DMAMUX9_EMIOS_0_CH18            = 630U, /* DMAMUX_9: Source 54 */
    DMAMUX9_EMIOS_0_CH19            = 631U, /* DMAMUX_9: Source 55 */
    DMAMUX9_EMIOS_1_CH0             = 632U, /* DMAMUX_9: Source 56 */
    DMAMUX9_EMIOS_1_CH1             = 633U, /* DMAMUX_9: Source 57 */
    DMAMUX9_EMIOS_1_CH2             = 634U, /* DMAMUX_9: Source 58 */
    DMAMUX9_EMIOS_1_CH3             = 635U, /* DMAMUX_9: Source 59 */
#if defined(CCFC3008PT)
    DMAMUX9_RESERVED_1              = 636U, /* DMAMUX_9: Source 60 */
    DMAMUX9_RESERVED_2              = 637U, /* DMAMUX_9: Source 61 */
    DMAMUX9_RESERVED_3              = 638U, /* DMAMUX_9: Source 62 */
#endif
#if defined(CCFC3007PT)
    DMAMUX9_LIN_11_RX               = 636U, /* DMAMUX_9: Source 60 */
    DMAMUX9_LIN_12_TX               = 637U, /* DMAMUX_9: Source 61 */
    DMAMUX9_LIN_12_RX               = 638U, /* DMAMUX_9: Source 62 */
#endif
    DMAMUX9_ALWAYS_ON_0             = 639U  /* DMAMUX_9: Source 63 */
} eDMARequestSourceType;

typedef void (*eDMACallbackType) \
( \
	P2CONST(void, AUTOMATIC, EDMA_APPL_DATA) parameter, \
    VAR(eDMAChnStatusType, AUTOMATIC) status, \
    VAR(uint8, AUTOMATIC) mappedChannel \
);

typedef struct
{
    VAR(eDMAChannelPriorityType, AUTOMATIC) chnPrioSet;     /* eDMA channel priority - only used when channel
                                                               arbitration mode is 'Fixed priority'. */
    VAR(uint8, AUTOMATIC) mappedChnConfig;                  /* eDMA virtual channel number */

    VAR(eDMARequestSourceType, AUTOMATIC) reqSource;        /* Selects the source of the DMA request for this channel */

    VAR(eDMACallbackType, AUTOMATIC) callback;              /* Callback that will be registered for this channel */
    P2VAR(void, AUTOMATIC, EDMA_APPL_DATA) callbackParam;   /* Parameter passed to the channel callback */
    VAR(boolean, AUTOMATIC) triggerEn;                      /* Enables the periodic trigger capability for the DMA channel. */

    VAR(boolean, AUTOMATIC) chnErrIntEn;                    /* enable/disable eDMA error channel interrupt. */
    VAR(boolean, AUTOMATIC) preemptionEn;                   /* Channel n can be temporarily suspended by the service request of a higher priority channel */
    VAR(boolean, AUTOMATIC) preemptAbilityDisable;          /* Channel n cannot suspend any channel, regardless of channel priority */
    VAR(boolean, AUTOMATIC) MasterIdReplicationEn;          /* Enable Master ID replication */
} eDMAChanConfigType;

typedef struct
{
    VAR(uint8, AUTOMATIC) channel;                          /* eDMA virtual channel number */    
    VAR(boolean, AUTOMATIC) isUsed;                         /* Mark whether the channel is in use */ 
    VAR(eDMAChannelPriorityType, AUTOMATIC) chPriority;     /* Channel priority. Unused channels are assigned a default priority */ 
} eDMAChPriorityCfg;

typedef struct
{
    VAR(uint8, AUTOMATIC) mappedChn;                        /* Virtual channel number. */
    VAR(eDMACallbackType, AUTOMATIC) callback;              /* Callback function pointer for the eDMA channel. It will
                                                               be called at the eDMA channel complete and eDMA channel error. */
    P2VAR(void, AUTOMATIC, EDMA_APPL_DATA) parameter;       /* Parameter for the callback function pointer. */
    volatile VAR(eDMAChnStatusType, AUTOMATIC) status;      /* eDMA channel status. */
} eDMAChnStateType;

typedef struct
{
    VAR(uint32, AUTOMATIC) SADDR;
    VAR(uint16, AUTOMATIC) ATTR;
    VAR(sint16, AUTOMATIC) SOFF;
    VAR(uint32, AUTOMATIC) NBYTES;
    VAR(sint32, AUTOMATIC) SLAST;
    VAR(uint32, AUTOMATIC) DADDR;
    VAR(uint16, AUTOMATIC) CITER;
    VAR(sint16, AUTOMATIC) DOFF;
    VAR(sint32, AUTOMATIC) DLAST_SGA;
    VAR(uint16, AUTOMATIC) BITER;
    VAR(uint16, AUTOMATIC) CSR;
} eDMASwTcdType;

typedef struct
{
    VAR(uint32, AUTOMATIC) majorLpIterCnt;                  /* Number of major loop iterations. */
    VAR(boolean, AUTOMATIC) srcAddrOffsetEn;                /* Selects whether the minor loop offset is applied to the
                                                               source address upon minor loop completion. */
    VAR(boolean, AUTOMATIC) dstAddrOffsetEn;                /* Selects whether the minor loop offset is applied to the
                                                               destination address upon minor loop completion. */
    VAR(sint32, AUTOMATIC) minorLpOffset;                   /* Sign - extended offset applied to the source or destination address
                                                               to form the next - state value after the minor loop completes. */
    VAR(boolean, AUTOMATIC) minorLpLinkEn;                  /* Enables channel - to - channel linking on minor loop complete. */
    VAR(uint8, AUTOMATIC) minorLpLinkChn;                   /* The number of the next channel to be started by DMA
                                                               engine when minor loop completes. */
    VAR(boolean, AUTOMATIC) majorLpLinkEn;                  /* Enables channel - to - channel linking on major loop complete. */
    VAR(uint8, AUTOMATIC) majorLpLinkChn;                   /* The number of the next channel to be started by DMA
                                                               engine when major loop completes. */
} eDMALoopTransferConfigType;

typedef struct
{
    VAR(boolean, AUTOMATIC) minorLpMap;                             /* Configure minor loop map. */
    VAR(uint32, AUTOMATIC) srcAddr;                                 /* Memory address pointing to the source data. */
    VAR(uint32, AUTOMATIC) destAddr;                                /* Memory address pointing to the destination data. */
    VAR(eDMATransferSizeType, AUTOMATIC) srcTransDataSize;          /* Source data transfer size. */
    VAR(eDMATransferSizeType, AUTOMATIC) destTransDataSize;         /* Destination data transfer size. */
    VAR(sint16, AUTOMATIC) srcAddrOffset;                           /* Sign - extended offset applied to the current source address
                                                                       to form the next - state value as each source read/write
                                                                       is completed. */
    VAR(sint16, AUTOMATIC) destAddrOffset;                          /* Sign - extended offset applied to the current destination
                                                                       address to form the next - state value as each source
                                                                       read/write is completed. */
    VAR(sint32, AUTOMATIC) srcAddrAdjustLast;                       /* Last source address adjustment. */
    VAR(sint32, AUTOMATIC) destAddrAdjustLast;                      /* Last destination address adjustment. Note here it is only
                                                                       valid when scatter/gather feature is not enabled. */
    VAR(eDMAModuloType, AUTOMATIC) srcAddrModulo;                   /* Source address modulo. */
    VAR(eDMAModuloType, AUTOMATIC) destAddrModulo;                  /* Destination address modulo. */
    VAR(uint32, AUTOMATIC) minorTransByte;                          /* Number of bytes to be transferred in each service request
                                                                       of the channel. */
    VAR(boolean, AUTOMATIC) featureScatterGatherEn;                 /* Enable scatter gather feature. */
    VAR(uint32, AUTOMATIC) featureScatterGatherNextDescriptor;      /* The address of the next descriptor to be used, when
                                                                       scatter/gather feature is enabled.
                                                                       Note: this value is not used when scatter/gather
                                                                       feature is disabled. */
    VAR(boolean, AUTOMATIC) completeIntEn;                          /* Enable the interrupt request when the major loop
                                                                       count completes */
    P2VAR(eDMALoopTransferConfigType, AUTOMATIC, EDMA_APPL_DATA) lpTransConfigPtr;   /* Pointer to loop transfer configuration structure
                                                                                        (defines minor/major loop attributes)
                                                                                        Note: this field is only used when minor loop mapping is
                                                                                        enabled from DMA configuration. */
} eDMATransferConfigType;

typedef enum
{
    EDMA_CHN_ENABLE_ERROR_INT = 0U,         /* Error interrupt */
    EDMA_CHN_ENABLE_HALF_MAJOR_LOOP_INT = 1U,    /* Half major loop interrupt. */
    EDMA_CHN_ENABLE_MAJOR_LOOP_DONE_INT = 2U     /* Complete major loop interrupt. */
} eDMAChannelInterruptType;

typedef struct
{
    P2VAR(eDMAChnStateType, AUTOMATIC, EDMA_APPL_DATA) volatile mapChnState[(uint32)EDMA_MAPPED_CHANNELS]; /* Pointer array storing channel state. */
} edma_state_t;

#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetUpCallback \
( \
    VAR(uint8, AUTOMATIC) mappedChannel,
    VAR(eDMACallbackType, AUTOMATIC) callback,
    P2VAR(void, AUTOMATIC, EDMA_APPL_DATA) parameter \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_HW_ClearIntStatus(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SwRequestTriggerEn(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetChannelSourceConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel,
    VAR(uint32, AUTOMATIC) request,
    VAR(boolean, AUTOMATIC) triggerEn \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_ChannelInit \
( \
    P2VAR(eDMAChnStateType, AUTOMATIC, EDMA_APPL_DATA) eedma_channelState, \
    P2CONST(eDMAChanConfigType, EDMA_CONST, EDMA_APPL_CONST) eedma_channelConfig \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_ModuleInit \
( \
    P2VAR(edma_state_t, AUTOMATIC, EDMA_APPL_DATA) edmaState, \
    P2CONST(eDMAModuleConfigType, EDMA_CONST, EDMA_APPL_CONST) userConfig, \
    CONSTP2VAR(eDMAChnStateType, EDMA_CONST, EDMA_APPL_CONST) chnStateArray[], \
    CONSTP2CONST(eDMAChanConfigType, EDMA_CONST, EDMA_APPL_CONST) chnConfigArray[], \
    VAR(uint32, AUTOMATIC) chnCount \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"

#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_NoUsedChInit \
( \
    CONSTP2CONST(eDMAChPriorityCfg, EDMA_CONST, EDMA_APPL_CONST) chPriorityCfgs \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"

#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_ClearSwTCDStruct \
( \
    P2VAR(eDMASwTcdType, AUTOMATIC, EDMA_APPL_DATA) swtcd \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetSglTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) dataBufferSize \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetMultiTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferType, AUTOMATIC) type, \
    VAR(uint32, AUTOMATIC) srcAddr, \
    VAR(uint32, AUTOMATIC) destAddr, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) blockSize, \
    VAR(uint32, AUTOMATIC) blockCount, \
    VAR(boolean, AUTOMATIC) disableReqOnCompletion \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetLoopTransferConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMATransferConfigType, EDMA_CONST, EDMA_APPL_CONST) transferConfig \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_CopyConfigToSwTCD \
( \
    P2CONST(eDMATransferConfigType, EDMA_CONST, EDMA_APPL_CONST) config,
    P2VAR(eDMASwTcdType, AUTOMATIC, EDMA_APPL_DATA)stcd \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetScatterGatherTrfCfg \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    P2CONST(eDMASwTcdType, EDMA_CONST, EDMA_APPL_CONST) stcd, \
    VAR(eDMATransferSizeType, AUTOMATIC) transferSize, \
    VAR(uint32, AUTOMATIC) bytesOnEachRequest, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST, EDMA_APPL_CONST) srcList, \
    P2CONST(eDMAScatterGatherListType, EDMA_CONST, EDMA_APPL_CONST) destList, \
    VAR(uint8, AUTOMATIC) tcdCount \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_SetChannelRequest(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(status_t, EDMA_CODE) EDMA_LLD_ClearChannelRequest(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_ClearHwTCD(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnSrcAddr \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnSrcAddrOffset \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnSrcAddrRdTrfSize \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnSrcAddrLastAdj \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnDestAddrLastAdj \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint32, AUTOMATIC) adjust \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnDestAddr \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) address \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnDestAddrOffset \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(sint16, AUTOMATIC) offset \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnDestdrWrTrfSize \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMATransferSizeType, AUTOMATIC) size \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnMinorLpTrfByte \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nbytes \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnMajorLpIterCount \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) majorLoopCount \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(uint32, EDMA_CODE) EDMA_LLD_GetChnRemainingIterCnt \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnSctGthLinkMode \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(uint32, AUTOMATIC) nextTCDAddr \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetChnDisReqOnTrfComp \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(boolean, AUTOMATIC) disable \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_SetInterruptConfig \
( \
    VAR(uint8, AUTOMATIC) mappedChannel, \
    VAR(eDMAChannelInterruptType, AUTOMATIC) intSrc, \
    VAR(boolean, AUTOMATIC) enable \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_CancelExcutingChnTrf(VAR(boolean, AUTOMATIC) error);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_WaitChnTransferDone(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(eDMAChnStatusType, EDMA_CODE) EDMA_LLD_GetChnConfigStatus \
( \
    VAR(uint8, AUTOMATIC) mappedChannel \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_IRQHandler(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_LLD_ErrorIRQHandler(VAR(uint8, AUTOMATIC) mappedChannel);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(void, EDMA_CODE) EDMA_Ch0_Ch127_Error_IRQHandler(void);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(boolean, EDMA_CODE) EDMA_LLD_GetMasterID_PAL \
(\
    VAR(eDMAIstanceNumType, AUTOMATIC) instance, \
    VAR(uint8, AUTOMATIC) channel \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"
#define EDMA_START_SEC_CODE
#include "Edma_MemMap.h"
FUNC(uint8, EDMA_CODE) EDMA_LLD_GetMasterID_MID \
(\
    VAR(eDMAIstanceNumType, AUTOMATIC) instance, \
    VAR(uint8, AUTOMATIC) channel \
);
#define EDMA_STOP_SEC_CODE
#include "Edma_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* EDMA_LLD__H_ */
