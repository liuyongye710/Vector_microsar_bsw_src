/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : Adc
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
*   @file    Adc_LLDriver.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Adc MCAL driver.
*
*   @addtogroup Adc
*   @{
*/

#ifndef ADC_LLDRIVER_H
#define ADC_LLDRIVER_H

#include "eDma_LLDriver.h"
#include "derivative.h"
#include "Adc_Cfg.h"

#define ADC_LLD_H_VENDOR_ID                     176
#define ADC_LLD_H_AR_REL_MAJOR_VER              4
#define ADC_LLD_H_AR_REL_MINOR_VER              4
#define ADC_LLD_H_AR_REL_REV_VER                0
#define ADC_LLD_H_SW_MAJOR_VER                  3
#define ADC_LLD_H_SW_MINOR_VER                  0
#define ADC_LLD_H_SW_PATCH_VER                  0

#if (ADC_VENDOR_ID               != ADC_LLD_H_VENDOR_ID)
    #error " NON-MATCHED DATA : ADC_LLD_H_VENDOR_ID "
#endif
#if (ADC_AR_REL_MAJOR_VER    != ADC_LLD_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_AR_REL_MAJOR_VER "
#endif
#if (ADC_AR_REL_MINOR_VER    != ADC_LLD_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_AR_REL_MINOR_VER "
#endif
#if (ADC_AR_REL_REV_VER != ADC_LLD_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_AR_REL_REV_VER "
#endif
#if (ADC_SW_MAJOR_VER        != ADC_LLD_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_SW_MAJOR_VER "
#endif
#if (ADC_SW_MINOR_VER        != ADC_LLD_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_SW_MINOR_VER "
#endif
#if (ADC_SW_PATCH_VER        != ADC_LLD_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : ADC_LLD_H_SW_PATCH_VER "
#endif

/* PRQA S 3472 EOF */
/* PRQA S 1534 EOF */
/* PRQA S 3630 EOF */

/*******************************************************************************
 * EQADC module *    OnChip ADC
 *  EQADCx      *       ADC0
 *              *       ADC1
 *******************************************************************************
 *******************************************************************************
 *  EQADC0      *   ADC0(RM hardware resources: ADC0)
 *              *   ADC1(RM hardware resources: ADC1)
 *******************************************************************************
 *  EQADC1      *   ADC0(RM hardware resources: ADC2)
 *              *   ADC1(RM hardware resources: ADC3)
 *******************************************************************************
 *  EQADC2      *   ADC0(RM hardware resources: ADC4)
 *              *   ADC1(RM hardware resources: ADC5)
 *******************************************************************************
 *  EQADC3      *   ADC0(RM hardware resources: ADC6)
 *              *   ADC1(RM hardware resources: ADC7)
 *******************************************************************************
 *  EQADC4      *   ADC0(RM hardware resources: ADC8)
 *              *   ADC1(RM hardware resources: ADC9)
 *******************************************************************************/

typedef struct EQADC_tag EQADC_TagType;

#define EQADC_DET_SUPPORT           (FALSE)
#define EQADC_DET_ERR(x)            DEV_ASSERT(x)

#define EQADC_TIMEOUT_COUNT         (ADC_TIMEOUT)

/* @brief Number of EQADC instances */
#define ADC_EQADC_MAX_INSTANCE      (5U)

/* @brief EQADC - Size of Registers Arrays */
#define EQADC_CFIFO_COUNT           (6U)
#define EQADC_RFIFO_COUNT           (6U)
#define EQADC_CFIFO_ENTRY_COUNT     (4U)
#define EQADC_RFIFO_ENTRY_COUNT     (4U)

/* @brief EQADC instance base address */
#define EQADC0_BASEADDR             ((uint32)0xFFE00000UL)
#define EQADC1_BASEADDR             ((uint32)0xFBE08000UL)
#define EQADC2_BASEADDR             ((uint32)0xFFE10000UL)
#define EQADC3_BASEADDR             ((uint32)0xFBE18000UL)
#define EQADC4_BASEADDR             ((uint32)0xFBE20000UL)

/* @brief EQADC instance base pointer */
#define EQADC0_PTR                  ((EQADC_TagType *) EQADC0_BASEADDR)
#define EQADC1_PTR                  ((EQADC_TagType *) EQADC1_BASEADDR)
#define EQADC2_PTR                  ((EQADC_TagType *) EQADC2_BASEADDR)
#define EQADC3_PTR                  ((EQADC_TagType *) EQADC3_BASEADDR)
#define EQADC4_PTR                  ((EQADC_TagType *) EQADC4_BASEADDR)

/* @brief EQADC instance base address array */
#define EQADC_BASE_ADDR_ARRAY       {EQADC0_BASEADDR, EQADC1_BASEADDR, EQADC2_BASEADDR, EQADC3_BASEADDR, EQADC4_BASEADDR}

/* @brief EQADC instance base pointer array */
#define EQADC_BASE_PTR_ARRAY        {EQADC0_PTR, EQADC1_PTR, EQADC2_PTR, EQADC3_PTR, EQADC4_PTR}

typedef struct SIUL2_tag SIUL2_TagType;

/* @brief SIUL2 base address */
#define SIUL2_BASEADDR              ((uint32_t)0xFFFC0000UL)

/* @brief SIUL2 base pointer */
#define SIUL2_PTR                   ((SIUL2_TagType *) SIUL2_BASEADDR)

/* @brief Number of on-chip ADC modules per EQADC instance */
#define EQADC_ADC_NUM               (2U)
#define EQADC_ALT_CONFIG_NUM        (8U)
#define EQADC_NUM_EXT_ALT_CONFIGS   EQADC_ALT_CONFIG_NUM
#define EQADC_RED_LINE_CLIENT_NUM   (2U)

/* @brief EQADC FIFO interrupt & DMA select */
#define EQADC_IRQDMA_REQ_SEL_CFIFOFILL    (EQADC_IDCR0_CFFS1_MASK)
#define EQADC_IRQDMA_REQ_SEL_RFIFODRAIN   (EQADC_IDCR0_RFDS1_MASK)

/* @brief EQADC FIFO interrupt & DMA source */
#define EQADC_IRQ_EN_NON_COHERENCY          (EQADC_IDCR0_NCIE1_MASK)   /* Non-Coherency Interrupt Enable */
#define EQADC_IRQ_EN_TRIGGER_OVERRUN        (EQADC_IDCR0_TORIE1_MASK)  /* Trigger Overrun Interrupt Enable */
#define EQADC_IRQ_EN_PAUSE                  (EQADC_IDCR0_PIE1_MASK)    /* Pause Interrupt Enable */
#define EQADC_IRQ_EN_END_OF_QUEUE           (EQADC_IDCR0_EOQIE1_MASK)  /* End of Queue Interrupt Enable */
#define EQADC_IRQ_EN_CFIFO_UNDERFLOW        (EQADC_IDCR0_CFUIE1_MASK)  /* CFIFO Underflow Interrupt Enable */
#define EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL     (EQADC_IDCR0_CFFE1_MASK)   /* CFIFO Fill Enable */
#define EQADC_IRQ_EN_RFIFO_OVERFLOW         (EQADC_IDCR0_RFOIE1_MASK)  /* RFIFO Overflow Interrupt Enable */
#define EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN    (EQADC_IDCR0_RFDE1_MASK)   /* RFIFO Drain Enable */
#define EQADC_IRQ_EN_GRP_ALL                (EQADC_IRQ_EN_NON_COHERENCY | \
                                             EQADC_IRQ_EN_PAUSE | \
                                             EQADC_IRQ_EN_END_OF_QUEUE | \
                                             EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL | \
                                             EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN)  /* No TORIE/CFUIE/RFOIE, for GTM module use */
#define EQADC_IRQ_EN_ALL                    (EQADC_IRQ_EN_NON_COHERENCY | \
                                             EQADC_IRQ_EN_TRIGGER_OVERRUN | \
                                             EQADC_IRQ_EN_PAUSE | \
                                             EQADC_IRQ_EN_END_OF_QUEUE | \
                                             EQADC_IRQ_EN_CFIFO_UNDERFLOW | \
                                             EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL | \
                                             EQADC_IRQ_EN_RFIFO_OVERFLOW | \
                                             EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN)
#define EQADC_DMA_EN_ALL                    (EQADC_IRQ_DMA_REQ_EN_CFIFO_FILL | \
                                             EQADC_IRQ_DMA_REQ_EN_RFIFODRAIN)

/* @brief EQADC FIFO status flags */
#define EQADC_FIFO_FLAG_NON_COHERENCY       (EQADC_FISR_NCFX_MASK)
#define EQADC_FIFO_FLAG_TRIG_OVERRUN        (EQADC_FISR_TORFX_MASK)
#define EQADC_FIFO_FLAG_PAUSE               (EQADC_FISR_PFX_MASK)
#define EQADC_FIFO_FLAG_END_OF_QUEUE        (EQADC_FISR_EOQFX_MASK)
#define EQADC_FIFO_FLAG_CFIFO_UNDERFLOW     (EQADC_FISR_CFUFX_MASK)
#define EQADC_FIFO_FLAG_CFIFO_FILL          (EQADC_FISR_CFFFX_MASK)
#define EQADC_FIFO_FLAG_RFIFO_OVERFLOW      (EQADC_FISR_RFOFX_MASK)
#define EQADC_FIFO_FLAG_RFIFO_DRAIN         (EQADC_FISR_RFDFX_MASK)
#define EQADC_FIFO_FLAG_ALL                 (EQADC_FIFO_FLAG_NON_COHERENCY | \
                                             EQADC_FIFO_FLAG_TRIG_OVERRUN | \
                                             EQADC_FIFO_FLAG_PAUSE | \
                                             EQADC_FIFO_FLAG_END_OF_QUEUE | \
                                             EQADC_FIFO_FLAG_CFIFO_UNDERFLOW | \
                                             EQADC_FIFO_FLAG_CFIFO_FILL | \
                                             EQADC_FIFO_FLAG_RFIFO_OVERFLOW | \
                                             EQADC_FIFO_FLAG_RFIFO_DRAIN)

#define EQADC_STAC_BUS_CLIENT_1 (0U)
#define EQADC_STAC_BUS_CLIENT_2 (1U)

/*******************************************************************************
 * @brief EQADC Command FIFO Trigger Source.
 *
 * @param x: CFIFO number
 *******************************************************************************/
#define EQADC_TRIG_NULL_VAL                 ((uint8)(0U))
#define EQADC_TRIG_RTI_VAL                  ((uint8)(1U))
#define EQADC_TRIG_PIT0_CH0_VAL             ((uint8)(2U))
#define EQADC_TRIG_PIT0_CH1_VAL             ((uint8)(3U))
#define EQADC_TRIG_PIT1_CH0_VAL             ((uint8)(4U))
#define EQADC_TRIG_PIT1_CH1_VAL             ((uint8)(5U))
#define EQADC_TRIG_ETRIG0_VAL(x)            ((uint8)((((uint8)(x) % 2U) == 0U) ? 96U : 7U))
#define EQADC_TRIG_ETRIG1_VAL(x)            ((uint8)((((uint8)(x) % 2U) == 0U) ? 7U : 96U))
#define EQADC_TRIG_ETPUA28_VAL              ((uint8)(12U))
#define EQADC_TRIG_ETPUA29_VAL              ((uint8)(13U))
#define EQADC_TRIG_ETPUA30_VAL              ((uint8)(14U))
#define EQADC_TRIG_ETPUA31_VAL              ((uint8)(15U))
#define EQADC_TRIG_ETPUB28_VAL              ((uint8)(16U))
#define EQADC_TRIG_ETPUB29_VAL              ((uint8)(17U))
#define EQADC_TRIG_ETPUB30_VAL              ((uint8)(18U))
#define EQADC_TRIG_ETPUB31_VAL              ((uint8)(19U))
#define EQADC_TRIG_ETPUC28_VAL              ((uint8)(20U))
#define EQADC_TRIG_ETPUC29_VAL              ((uint8)(21U))
#define EQADC_TRIG_ETPUC30_VAL              ((uint8)(22U))
#define EQADC_TRIG_ETPUC31_VAL              ((uint8)(23U))
#define EQADC_TRIG_EMIOS0_CH16_VAL          ((uint8)(24U))
#define EQADC_TRIG_EMIOS0_CH17_VAL          ((uint8)(25U))
#define EQADC_TRIG_EMIOS0_CH18_VAL          ((uint8)(26U))
#define EQADC_TRIG_EMIOS0_CH19_VAL          ((uint8)(27U))
#define EQADC_TRIG_EMIOS0_CH20_VAL          ((uint8)(28U))
#define EQADC_TRIG_EMIOS0_CH21_VAL          ((uint8)(29U))
#define EQADC_TRIG_EMIOS0_CH22_VAL          ((uint8)(30U))
#define EQADC_TRIG_EMIOS0_CH23_VAL          ((uint8)(31U))
#define EQADC_TRIG_ETPUA7_VAL               ((uint8)(6U))     /* ETPU trigger CFIFO_1 only */
#define EQADC_TRIG_ETPUA14_VAL              ((uint8)(6U))     /* ETPU trigger CFIFO_2 only */
#define EQADC_TRIG_ETPUA22_VAL              ((uint8)(6U))     /* ETPU trigger CFIFO_3 only */
#define EQADC_TRIG_ETPUA26_VAL              ((uint8)(32U))    /* ETPU trigger CFIFO_5 only */
#define EQADC_TRIG_ETPUA27_VAL              ((uint8)(32U))    /* ETPU trigger CFIFO_4 only */
#define EQADC_TRIG_EMIOS1_CH2_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_0 only */
#define EQADC_TRIG_EMIOS1_CH3_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_1 only */
#define EQADC_TRIG_EMIOS1_CH4_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_5 only */
#define EQADC_TRIG_EMIOS1_CH5_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_4 only */
#define EQADC_TRIG_EMIOS1_CH6_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_3 only */
#define EQADC_TRIG_EMIOS1_CH7_VAL           ((uint8)(64U))    /* eMOIS trigger CFIFO_2 only */

/*******************************************************************************
 * @brief EQADC CFIFO0 Advance Trigger Source.
 *******************************************************************************/
#define EQADC_ATRIG_NULL_VALUE                  ((uint8)(0U))
#define EQADC_ATRIG_RTI_VALUE                   ((uint8)(1U))
#define EQADC_ATRIG_PIT0_CH0_VALUE              ((uint8)(2U))
#define EQADC_ATRIG_PIT0_CH1_VALUE              ((uint8)(3U))
#define EQADC_ATRIG_PIT1_CH0_VALUE              ((uint8)(4U))
#define EQADC_ATRIG_PIT1_CH1_VALUE              ((uint8)(5U))
#define EQADC_ATRIG_ETPUA30_PIT0CH0_VAL         ((uint8)(8U))
#define EQADC_ATRIG_ETPUA30_PIT0CH1_VAL         ((uint8)(9U))
#define EQADC_ATRIG_ETPUA28_VAL                 ((uint8)(12U))
#define EQADC_ATRIG_ETPUA29_VAL                 ((uint8)(13U))
#define EQADC_ATRIG_ETPUA30_VAL                 ((uint8)(14U))
#define EQADC_ATRIG_ETPUA31_VAL                 ((uint8)(15U))
#define EQADC_ATRIG_ETPUC28_VAL                 ((uint8)(16U))
#define EQADC_ATRIG_ETPUC29_VAL                 ((uint8)(17U))
#define EQADC_ATRIG_ETPUC30_VAL                 ((uint8)(18U))
#define EQADC_ATRIG_ETPUC31_VAL                 ((uint8)(19U))
#define EQADC_ATRIG_EMIOS1_2_PIT1_0_VAL         ((uint8)(20U))
#define EQADC_ATRIG_EMIOS1_2_PIT1_1_VAL         ((uint8)(21U))
#define EQADC_ATRIG_EMIOS0_CH23_VAL             ((uint8)(31U))

/* Internal Channel Function Enable */
#define SSCM_VRC33_ENABLE           (*(vuint32_t *)(0xFFFF8038UL))
#define EQADC_PCT_VREF_EN_MSAK      (0x00000004U)
#define EQADC_TSENS_EN_MSAK         (0x00000008U)

/* eTRIG pin */
#define ETRIG0_PAD                  (PA0)
#define ETRIG1_PAD                  (PF2)

/* Multiplexed address signals(MA) pin */
#define MA0_PAD                     (PN4)
#define MA0_PAD_SSS                 (PAD_SSS_13)
#define MA1_PAD                     (PH6)
#define MA1_PAD_SSS                 (PAD_SSS_13)
#define MA2_PAD                     (PM6)
#define MA2_PAD_SSS                 (PAD_SSS_12)

/* Single ended Channel */
#define EQADC_CH0                   (0U)    /* Channel 0:   Single ended conversion */
#define EQADC_CH1                   (1U)    /* Channel 1:   Single ended conversion */
#define EQADC_CH2                   (2U)    /* Channel 2:   Single ended conversion */
#define EQADC_CH3                   (3U)    /* Channel 3:   Single ended conversion */
#define EQADC_CH4                   (4U)    /* Channel 4:   Single ended conversion */
#define EQADC_CH5                   (5U)    /* Channel 5:   Single ended conversion */
#define EQADC_CH6                   (6U)    /* Channel 6:   Single ended conversion */
#define EQADC_CH7                   (7U)    /* Channel 7:   Single ended conversion */
#define EQADC_CH8                   (8U)    /* Channel 8:   Single ended conversion */
#define EQADC_CH9                   (9U)    /* Channel 9:   Single ended conversion */
#define EQADC_CH10                  (10U)   /* Channel 10:  Single ended conversion */
#define EQADC_CH11                  (11U)   /* Channel 11:  Single ended conversion */
#define EQADC_CH12                  (12U)   /* Channel 12:  Single ended conversion */
#define EQADC_CH13                  (13U)   /* Channel 13:  Single ended conversion */
#define EQADC_CH14                  (14U)   /* Channel 14:  Single ended conversion */
#define EQADC_CH15                  (15U)   /* Channel 15:  Single ended conversion */
#define EQADC_CH16                  (16U)   /* Channel 16:  Single ended conversion */
#define EQADC_CH17                  (17U)   /* Channel 17:  Single ended conversion */
#define EQADC_CH18                  (18U)   /* Channel 18:  Single ended conversion */
#define EQADC_CH19                  (19U)   /* Channel 19:  Single ended conversion */
#define EQADC_CH20                  (20U)   /* Channel 20:  Single ended conversion */
#define EQADC_CH21                  (21U)   /* Channel 21:  Single ended conversion */
#define EQADC_CH22                  (22U)   /* Channel 22:  Single ended conversion */
#define EQADC_CH23                  (23U)   /* Channel 23:  Single ended conversion */
#define EQADC_CH24                  (24U)   /* Channel 24:  Single ended conversion */
#define EQADC_CH25                  (25U)   /* Channel 25:  Single ended conversion */
#define EQADC_CH26                  (26U)   /* Channel 26:  Single ended conversion */
#define EQADC_CH27                  (27U)   /* Channel 27:  Single ended conversion */
#define EQADC_CH28                  (28U)   /* Channel 28:  Single ended conversion */
#define EQADC_CH29                  (29U)   /* Channel 29:  Single ended conversion */
#define EQADC_CH30                  (30U)   /* Channel 30:  Single ended conversion */
#define EQADC_CH31                  (31U)   /* Channel 31:  Single ended conversion */
#define EQADC_CH32                  (32U)   /* Channel 32:  Single ended conversion */
#define EQADC_CH33                  (33U)   /* Channel 33:  Single ended conversion */
#define EQADC_CH34                  (34U)   /* Channel 34:  Single ended conversion */
#define EQADC_CH35                  (35U)   /* Channel 35:  Single ended conversion */
#define EQADC_CH36                  (36U)   /* Channel 36:  Single ended conversion */
#define EQADC_CH37                  (37U)   /* Channel 37:  Single ended conversion */
#define EQADC_CH38                  (38U)   /* Channel 38:  Single ended conversion */
#define EQADC_CH39                  (39U)   /* Channel 39:  Single ended conversion */
#define EQADC_CH40                  (40U)   /* Channel 40:  Single ended conversion */
#define EQADC_CH41                  (41U)   /* Channel 41:  Single ended conversion */
#define EQADC_CH42                  (42U)   /* Channel 42:  Single ended conversion */
#define EQADC_CH43                  (43U)   /* Channel 43:  Single ended conversion */
#define EQADC_CH44                  (44U)   /* Channel 44:  Single ended conversion */
#define EQADC_CH45                  (45U)   /* Channel 45:  Single ended conversion */
#define EQADC_CH46                  (46U)   /* Channel 46:  Single ended conversion */
#define EQADC_CH47                  (47U)   /* Channel 47:  Single ended conversion */
#define EQADC_CH48                  (48U)   /* Channel 48:  Single ended conversion */
#define EQADC_CH49                  (49U)   /* Channel 49:  Single ended conversion */
#define EQADC_CH50                  (50U)   /* Channel 50:  Single ended conversion */
#define EQADC_CH51                  (51U)   /* Channel 51:  Single ended conversion */
#define EQADC_CH52                  (52U)   /* Channel 52:  Single ended conversion */
#define EQADC_CH53                  (53U)   /* Channel 53:  Single ended conversion */
#define EQADC_CH56                  (56U)   /* Channel 56:  Single ended conversion */
#define EQADC_CH57                  (57U)   /* Channel 57:  Single ended conversion */
#define EQADC_CH58                  (58U)   /* Channel 58:  Single ended conversion */
#define EQADC_CH59                  (59U)   /* Channel 59:  Single ended conversion */
#define EQADC_CH60                  (60U)   /* Channel 60:  Single ended conversion */
#define EQADC_CH61                  (61U)   /* Channel 61:  Single ended conversion */
#define EQADC_CH64                  (64U)   /* Channel 64:  Single ended conversion */
#define EQADC_CH65                  (65U)   /* Channel 65:  Single ended conversion */
#define EQADC_CH66                  (66U)   /* Channel 66:  Single ended conversion */
#define EQADC_CH67                  (67U)   /* Channel 67:  Single ended conversion */
#define EQADC_CH68                  (68U)   /* Channel 68:  Single ended conversion */
#define EQADC_CH69                  (69U)   /* Channel 69:  Single ended conversion */
#define EQADC_CH70                  (70U)   /* Channel 70:  Single ended conversion */
#define EQADC_CH71                  (71U)   /* Channel 71:  Single ended conversion */
#define EQADC_CH72                  (72U)   /* Channel 72:  Single ended conversion */
#define EQADC_CH73                  (73U)   /* Channel 73:  Single ended conversion */
#define EQADC_CH74                  (74U)   /* Channel 74:  Single ended conversion */
#define EQADC_CH75                  (75U)   /* Channel 75:  Single ended conversion */
#define EQADC_CH76                  (76U)   /* Channel 76:  Single ended conversion */
#define EQADC_CH77                  (77U)   /* Channel 77:  Single ended conversion */
#define EQADC_CH78                  (78U)   /* Channel 78:  Single ended conversion */
#define EQADC_CH79                  (79U)   /* Channel 79:  Single ended conversion */
#define EQADC_CH80                  (80U)   /* Channel 80:  Single ended conversion */
#define EQADC_CH81                  (81U)   /* Channel 81:  Single ended conversion */
#define EQADC_CH82                  (82U)   /* Channel 82:  Single ended conversion */
#define EQADC_CH83                  (83U)   /* Channel 83:  Single ended conversion */
#define EQADC_CH84                  (84U)   /* Channel 84:  Single ended conversion */
#define EQADC_CH85                  (85U)   /* Channel 85:  Single ended conversion */
#define EQADC_CH86                  (86U)   /* Channel 86:  Single ended conversion */
#define EQADC_CH87                  (87U)   /* Channel 87:  Single ended conversion */
#define EQADC_CH(x)                 (x) /* Channel x:   Single ended conversion */

/* Differential Channel */
#define EQADC_DAN_CH128             (128U)  /* Channel 128: Differential conversion */
#define EQADC_DAN_CH129             (129U)  /* Channel 129: Differential conversion */
#define EQADC_DAN_CH130             (130U)  /* Channel 130: Differential conversion */
#define EQADC_DAN_CH131             (131U)  /* Channel 131: Differential conversion */
#define EQADC_DAN_CH132             (132U)  /* Channel 132: Differential conversion */
#define EQADC_DAN_CH133             (133U)  /* Channel 133: Differential conversion */

/* Internal Channel (Only EQADC4_ADC1(ADC9) has.) */
#define EQADC_CH_VDD_REG2_PMU       (62U)   /* Channel: VDD_REG_2_PMU (1V)  */
#define EQADC_CH_VDD_REG_PMU        (63U)   /* Channel: VDD_REG_PMU   (1V)  */
#define EQADC_CH_VDD_HV_PMC         (88U)   /* Channel: VDD_HV_PMC    (5V)  */
#define EQADC_CH_VDD_HV_OSC         (89U)   /* Channel: VDD_HV_OSC    (5V)  */
#define EQADC_CH_VDD_HV_FLA         (90U)   /* Channel: VDD_HV_FLA  (3.3V)  */
#define EQADC_CH_VDD_HV_IO_FLEX     (91U)   /* Channel: VDD_HV_IO_FLEX(5V)  */
#define EQADC_CH_VDD_HV_IO_5V       (92U)   /* Channel: VDD_HV_IO_5V  (5V)  */
#define EQADC_CH_VDD_HV_IO_MAIN     (93U)   /* Channel: VDD_HV_IO_MAIN(5V)  */
#define EQADC_CH_VDD_LV             (95U)   /* Channel: VDD_LV      (1.1V)  */
#define EQADC_CH_TEMP_SENSOR        (120U)  /* Channel: Temperature Sensor  */
#define EQADC_CH_VDD_PCT75_VREF     (122U)  /* Channel: 75% VREF            */
#define EQADC_CH_VDD_PCT50_VREF     (123U)  /* Channel: 50% VREF            */
#define EQADC_CH_VDD_PCT25_VREF     (124U)  /* Channel: 25% VREF            */

/* External Multiplexing Channel (Only EQADC4_ADC1(ADC9) has.) */
#define EQADC_EXT0_CH192            (192U)  /* Channel 192: External multiplexing 0 */
#define EQADC_EXT0_CH193            (193U)  /* Channel 193: External multiplexing 0 */
#define EQADC_EXT0_CH194            (194U)  /* Channel 194: External multiplexing 0 */
#define EQADC_EXT0_CH195            (195U)  /* Channel 195: External multiplexing 0 */
#define EQADC_EXT0_CH196            (196U)  /* Channel 196: External multiplexing 0 */
#define EQADC_EXT0_CH197            (197U)  /* Channel 197: External multiplexing 0 */
#define EQADC_EXT0_CH198            (198U)  /* Channel 198: External multiplexing 0 */
#define EQADC_EXT0_CH199            (199U)  /* Channel 199: External multiplexing 0 */
#define EQADC_EXT1_CH200            (200U)  /* Channel 200: External multiplexing 1 */
#define EQADC_EXT1_CH201            (201U)  /* Channel 201: External multiplexing 1 */
#define EQADC_EXT1_CH202            (202U)  /* Channel 202: External multiplexing 1 */
#define EQADC_EXT1_CH203            (203U)  /* Channel 203: External multiplexing 1 */
#define EQADC_EXT1_CH204            (204U)  /* Channel 204: External multiplexing 1 */
#define EQADC_EXT1_CH205            (205U)  /* Channel 205: External multiplexing 1 */
#define EQADC_EXT1_CH206            (206U)  /* Channel 206: External multiplexing 1 */
#define EQADC_EXT1_CH207            (207U)  /* Channel 207: External multiplexing 1 */
#define EQADC_EXT2_CH208            (208U)  /* Channel 208: External multiplexing 2 */
#define EQADC_EXT2_CH209            (209U)  /* Channel 209: External multiplexing 2 */
#define EQADC_EXT2_CH210            (210U)  /* Channel 210: External multiplexing 2 */
#define EQADC_EXT2_CH211            (211U)  /* Channel 211: External multiplexing 2 */
#define EQADC_EXT2_CH212            (212U)  /* Channel 212: External multiplexing 2 */
#define EQADC_EXT2_CH213            (213U)  /* Channel 213: External multiplexing 2 */
#define EQADC_EXT2_CH214            (214U)  /* Channel 214: External multiplexing 2 */
#define EQADC_EXT2_CH215            (215U)  /* Channel 215: External multiplexing 2 */
#define EQADC_EXT3_CH216            (216U)  /* Channel 216: External multiplexing 3 */
#define EQADC_EXT3_CH217            (217U)  /* Channel 217: External multiplexing 3 */
#define EQADC_EXT3_CH218            (218U)  /* Channel 218: External multiplexing 3 */
#define EQADC_EXT3_CH219            (219U)  /* Channel 219: External multiplexing 3 */
#define EQADC_EXT3_CH220            (220U)  /* Channel 220: External multiplexing 3 */
#define EQADC_EXT3_CH221            (221U)  /* Channel 221: External multiplexing 3 */
#define EQADC_EXT3_CH222            (222U)  /* Channel 222: External multiplexing 3 */
#define EQADC_EXT3_CH223            (223U)  /* Channel 223: External multiplexing 3 */

/* EQADC Resolution count */
#define EQADC_RESOLUTION_BIT12      (0x3FFCU)   /* Resolution 12 bits: 0xFFFU << 2U */
#define EQADC_RESOLUTION_BIT10      (0x3FF0U)   /* Resolution 10 bits: 0x3FFU << 4U */
#define EQADC_RESOLUTION_BIT8       (0x3FC0U)   /* Resolution 8 bits:  0xFFU << 6U  */

/* EQADC Reference voltage value (millivolt) */
#define EQADC_VRH_MVOLT             (5000U)
#define EQADC_VRL_MVOLT             (0U)
#define EQADC_PCT50_VREF_MVOLT      (2500U)
#define EQADC_PCT75_VREF_MVOLT      (3750U)
#define EQADC_PCT25_VREF_MVOLT      (1250U)
#define EQADC_VDD3V3_MVOLT          (3300U)
#define EQADC_VDD_PMU_MVOLT         (1000U)
#define EQADC_VDD_LV_MVOLT          (1100U)

#define EQADC_PCT75_VREF_CAL_RES    (12288U)    /* CAL_Result(expected), (5V * 75% * 4096(12 bits) / 5V) << 2U */
#define EQADC_PCT25_VREF_CAL_RES    (4096U)     /* CAL_Result(expected), (5V * 25% * 4096(12 bits) / 5V) << 2U */

#define EQADC_ADC_GCC_INT_WIDTH     (1U)
#define EQADC_ADC_GCC_FRAC_WIDTH    (14U)
#define EQADC_ADC_GCC_WIDTH         (EQADC_ADC_GCC_INT_WIDTH + EQADC_ADC_GCC_FRAC_WIDTH)

#define EQADC_ADC_OCC_FORM1         (1U)
#define EQADC_ADC_OCC_FORM2         (2U)
#define EQADC_ADC_OCC_FORM          EQADC_ADC_OCC_FORM1

/*******************************************************************************
 * EQADC On-Chip ADC Read/Write LowLevelDriver switch(For test).
 *******************************************************************************/
#define EQADC_ONCHIPADC_RW_LLD      (TRUE)

#define DEM_EVENTID_DEINIT              (0x0U)
#define DEM_EVENTID_SETADCREGVALUESSE   (0x1U)
#define DEM_EVENTID_GETADCREGVALUESSE   (0x2U)
#define DME_EVENTID_INIT                (0x3U)

#define DEM_EVENT_TIMEOUT   (0x0U)

/*******************************************************************************
 * @brief EQADC instance number.
 *
 * @note  This chip has five instances of the EQADC module.
 *******************************************************************************/
typedef enum
{
    EQADC_INSTANCE_0                = 0U,
    EQADC_INSTANCE_1                = 1U,
    EQADC_INSTANCE_2                = 2U,
    EQADC_INSTANCE_3                = 3U,
    EQADC_INSTANCE_4                = 4U
} EqadcInstanceType;

/*******************************************************************************
 * @brief EQADCx's on-chip ADC number.
 *
 * @note  Each EQADC module: controls two independent analog-to-digital (ADC):
 *          ADC0 and ADC1.
 *******************************************************************************/
typedef enum
{
    EQADC_ADC_0                     = 0U,
    EQADC_ADC_1                     = 1U
} EqadcAdcIdxType;

/*******************************************************************************
 * @brief EQADC ADC hardware unit number
 *******************************************************************************/
#define EQADC_ADC_UNIT_0            (0U)    /* EQADC_INSTANCE_0 -> EQADC_ADC_0 */
#define EQADC_ADC_UNIT_1            (1U)    /* EQADC_INSTANCE_0 -> EQADC_ADC_1 */
#define EQADC_ADC_UNIT_2            (2U)    /* EQADC_INSTANCE_1 -> EQADC_ADC_0 */
#define EQADC_ADC_UNIT_3            (3U)    /* EQADC_INSTANCE_1 -> EQADC_ADC_1 */
#define EQADC_ADC_UNIT_4            (4U)    /* EQADC_INSTANCE_2 -> EQADC_ADC_0 */
#define EQADC_ADC_UNIT_5            (5U)    /* EQADC_INSTANCE_2 -> EQADC_ADC_1 */
#define EQADC_ADC_UNIT_6            (6U)    /* EQADC_INSTANCE_3 -> EQADC_ADC_0 */
#define EQADC_ADC_UNIT_7            (7U)    /* EQADC_INSTANCE_3 -> EQADC_ADC_1 */
#define EQADC_ADC_UNIT_8            (8U)    /* EQADC_INSTANCE_4 -> EQADC_ADC_0 */
#define EQADC_ADC_UNIT_9            (9U)    /* EQADC_INSTANCE_4 -> EQADC_ADC_1 */

/*******************************************************************************
 * @brief EQADCx's CFIFO/RFIFO number.
 *
 * @note  Each EQADC module: six CFIFO + six RFIFO.
 *******************************************************************************/
typedef enum
{
    EQADC_FIFO_0                    = 0U,
    EQADC_FIFO_1                    = 1U,
    EQADC_FIFO_2                    = 2U,
    EQADC_FIFO_3                    = 3U,
    EQADC_FIFO_4                    = 4U,
    EQADC_FIFO_5                    = 5U,
} EqadcFifoIdxType;

typedef enum
{
    EQADC_FISR_NON_COHERENCY        = 0U,
    EQADC_FISR_TRIG_OVERRUN         = 1U,
    EQADC_FISR_PAUSE                = 2U,
    EQADC_FISR_END_OF_QUEUE         = 3U,
    EQADC_FISR_CFIFO_UNDERFLOW      = 4U,
    EQADC_FISR_CFIFO_SINGLE_SCAN    = 5U,
    EQADC_FISR_CFIFO_FILL           = 6U,
    EQADC_FISR_RFIFO_OVERFLOW       = 7U,
    EQADC_FISR_RFIFO_DRAIN          = 8U,
    EQADC_FISR_CFIFO_ENTRY_COUNT    = 9U,
    EQADC_FISR_CFIFO_TRANS_NEXT_PTR = 10U,
    EQADC_FISR_RFIFO_ENTRY_COUNT    = 11U,
    EQADC_FISR_RFIFO_POP_NEXT_PTR   = 12U
} Eqadc_FifoIntStatusType;

typedef enum
{
    EQADC_CFIFO_MODE_DISABLE                        = 0U,   /* CFIFO Operation Mode: Disabled */
    EQADC_CFIFO_MODE_SINGLE_SW_TRIG                 = 1U,   /* CFIFO Operation Mode: Software Trigger, Single Scan */
    EQADC_CFIFO_MODE_SINGLE_LOW_LVL_GATED_EXT_TRIG  = 2U,   /* CFIFO Operation Mode: Low Level Gated External Trigger, Single Scan */
    EQADC_CFIFO_MODE_SINGLE_HIGH_LVL_GATED_EXT_TRIG = 3U,   /* CFIFO Operation Mode: High Level Gated External Trigger, Single Scan */
    EQADC_CFIFO_MODE_SINGLE_FALLING_EDGE_EXT_TRIG   = 4U,   /* CFIFO Operation Mode: Falling Edge External Trigger, Single Scan */
    EQADC_CFIFO_MODE_SINGLE_RISING_EDGE_EXT_TRIG    = 5U,   /* CFIFO Operation Mode: Rising Edge External Trigger, Single Scan */
    EQADC_CFIFO_MODE_SINGLE_BOTH_EDGES_EXT_TRIG     = 6U,   /* CFIFO Operation Mode: Falling or Rising Edge External Trigger, Single Scan */
    EQADC_CFIFO_MODE_CONT_SW_TRIG                   = 9U,   /* CFIFO Operation Mode: Software Trigger, Continuous Scan */
    EQADC_CFIFO_MODE_CONT_LOW_LVL_GATED_EXT_TRIG    = 10U,  /* CFIFO Operation Mode: Low Level Gated External Trigger, Continuous Scan */
    EQADC_CFIFO_MODE_CONT_HIGH_LVL_GATED_EXT_TRIG   = 11U,  /* CFIFO Operation Mode: High Level Gated External Trigger, Continuous Scan */
    EQADC_CFIFO_MODE_CONT_FALLING_EDGE_EXT_TRIG     = 12U,  /* CFIFO Operation Mode: Falling Edge External Trigger, Continuous Scan */
    EQADC_CFIFO_MODE_CONT_RISING_EDGE_EXT_TRIG      = 13U,  /* CFIFO Operation Mode: Rising Edge External Trigger, Continuous Scan */
    EQADC_CFIFO_MODE_CONT_BOTH_EDGES_EXT_TRIG       = 14U   /* CFIFO Operation Mode: Falling or Rising Edge External Trigger, Continuous Scan */
} Eqadc_CfifoModeType;

typedef enum
{
    EQADC_CFIFO0_AMODE_DISABLE                          = 0U,   /* CFIFO0 Advance Trigger Operation Mode: Disabled */
    EQADC_CFIFO0_AMODE_SINGLE_SW_TRIG                   = 1U,   /* CFIFO0 Advance Trigger Operation Mode: Software Trigger, Single Scan */
    EQADC_CFIFO0_AMODE_SINGLE_LOW_LVL_GATED_EXT_TRIG    = 2U,   /* CFIFO0 Advance Trigger Operation Mode: Low Level Gated External Trigger, Single Scan */
    EQADC_CFIFO0_AMODE_SINGLE_HIGH_LVL_GATED_EXT_TRIG   = 3U,   /* CFIFO0 Advance Trigger Operation Mode: High Level Gated External Trigger, Single Scan */
    EQADC_CFIFO0_AMODE_SINGLE_FALLING_EDGE_EXT_TRIG     = 4U,   /* CFIFO0 Advance Trigger Operation Mode: Falling Edge External Trigger, Single Scan */
    EQADC_CFIFO0_AMODE_SINGLE_RISING_EDGE_EXT_TRIG      = 5U,   /* CFIFO0 Advance Trigger Operation Mode: Rising Edge External Trigger, Single Scan */
    EQADC_CFIFO0_AMODE_SINGLE_BOTH_EDGES_EXT_TRIG       = 6U    /* CFIFO0 Advance Trigger Operation Mode: Falling or Rising Edge External Trigger, Single Scan */
} Eqadc_Cfifo0AModeType;

typedef enum
{
    EQADC_FILL_SEL_INT          = 0U,
    EQADC_FILL_SEL_DMA          = 1U,
    EQADC_FILL_NOT_INT          = 2U,
} Eqadc_IntDmaFillSelType;

/*******************************************************************************
 * @brief Time Base Counter Clock Prescaler (ADC_TSCR: TBC_CLK_PS).
 *
 * @note  If TBC_CLK_PS is not set to disabled,
 *          it must not be changed to any other value besides disabled.
 *******************************************************************************/
typedef enum
{
    EQADC_TBC_CLK_PS_DISABLED   = 0U,   /* The time base counter clock prescaler is disabled */
    EQADC_TBC_CLK_PS_DIV_1      = 1U,   /* System clock divide factor: 1 */
    EQADC_TBC_CLK_PS_DIV_2      = 2U,   /* System clock divide factor: 2 */
    EQADC_TBC_CLK_PS_DIV_4      = 3U,   /* System clock divide factor: 4 */
    EQADC_TBC_CLK_PS_DIV_6      = 4U,   /* System clock divide factor: 6 */
    EQADC_TBC_CLK_PS_DIV_8      = 5U,   /* System clock divide factor: 8 */
    EQADC_TBC_CLK_PS_DIV_10     = 6U,   /* System clock divide factor: 10 */
    EQADC_TBC_CLK_PS_DIV_12     = 7U,   /* System clock divide factor: 12 */
    EQADC_TBC_CLK_PS_DIV_16     = 8U,   /* System clock divide factor: 16 */
    EQADC_TBC_CLK_PS_DIV_32     = 9U,   /* System clock divide factor: 32 */
    EQADC_TBC_CLK_PS_DIV_64     = 10U,  /* System clock divide factor: 64 */
    EQADC_TBC_CLK_PS_DIV_128    = 11U,  /* System clock divide factor: 128 */
    EQADC_TBC_CLK_PS_DIV_256    = 12U,  /* System clock divide factor: 256 */
    EQADC_TBC_CLK_PS_DIV_512    = 13U   /* System clock divide factor: 512 */
} Eqadc_TimeBaseCountClkPresType;

/*******************************************************************************
 * @brief Time base Selection for ADC0/1 (ADCx_CR: ADCx_TBSEL).
 *
 * @note  This selection is overridden by the corresponding field ATBSEL in the
 *          ADC_ACRx registers when the alternate conversion command is used.
 *******************************************************************************/
typedef enum
{
    EQADC_TBS_INTERNAL          = 0U,   /* Selects internally generated time base as time stamp */
    EQADC_TBS_STACCCR_SRV1      = 1U,   /* Selects imported time base 1 indicated by SRV1 bit field of EQADC_STACCCR */
    EQADC_TBS_STACCCR_SRV2      = 2U    /* Selects imported time base 2 indicated by SRV2 bit field of EQADC_STACCCR */
} Eqadc_TimeBaseSelType;

/*******************************************************************************
 * @brief Clock Selector for ADC0/1 (ADCx_CR: ADCx_CLK_SEL).
 *
 * @note  The ADC0/1_CLK_SEL bits must only be written when the ADC0/1_EN bit
 *          is negated.
 *        ADC0/1_CLK_SEL can be set during the same write cycle used to set
 *          ADC0/1_EN.
 *******************************************************************************/
typedef enum
{
    EQADC_CLK_SEL_PS_DIV        = 0U,   /* Prescaler output clock is selected: EQADC_CLK_PS_DIV_x. */
    EQADC_CLK_SEL_MAX_FREQ      = 1U    /* Platform clock is selected: maximum frequency. */
} Eqadc_ClkSelType;

/*******************************************************************************
 * @brief Clock Prescaler Field for ADC0/1 (ADCx_CR: ADCx_CLK_PS).
 *
 * @note  The ADC0/1_CLK_PS bits must only be written when the ADC0/1_EN bit
 *          is negated.
 *        ADC0/1_CLK_PS can be set during the same write cycle used to set
 *          ADC0/1_EN.
 *******************************************************************************/
typedef enum
{
    EQADC_CLK_PS_DIV_2          = 0U,   /* Platform Clock Divide Factor: 2 */
    EQADC_CLK_PS_DIV_4          = 1U,   /* Platform Clock Divide Factor: 4 */
    EQADC_CLK_PS_DIV_6          = 2U,   /* Platform Clock Divide Factor: 6 */
    EQADC_CLK_PS_DIV_8          = 3U,   /* Platform Clock Divide Factor: 8 */
    EQADC_CLK_PS_DIV_10         = 4U,   /* Platform Clock Divide Factor: 10 */
    EQADC_CLK_PS_DIV_12         = 5U,   /* Platform Clock Divide Factor: 12 */
    EQADC_CLK_PS_DIV_14         = 6U,   /* Platform Clock Divide Factor: 14 */
    EQADC_CLK_PS_DIV_16         = 7U,   /* Platform Clock Divide Factor: 16 */
    EQADC_CLK_PS_DIV_18         = 8U,   /* Platform Clock Divide Factor: 18 */
    EQADC_CLK_PS_DIV_20         = 9U,   /* Platform Clock Divide Factor: 20 */
    EQADC_CLK_PS_DIV_22         = 10U,  /* Platform Clock Divide Factor: 22 */
    EQADC_CLK_PS_DIV_24         = 11U,  /* Platform Clock Divide Factor: 24 */
    EQADC_CLK_PS_DIV_26         = 12U,  /* Platform Clock Divide Factor: 26 */
    EQADC_CLK_PS_DIV_28         = 13U,  /* Platform Clock Divide Factor: 28 */
    EQADC_CLK_PS_DIV_30         = 14U,  /* Platform Clock Divide Factor: 30 */
    EQADC_CLK_PS_DIV_32         = 15U,  /* Platform Clock Divide Factor: 32 */
    EQADC_CLK_PS_DIV_34         = 16U,  /* Platform Clock Divide Factor: 34 */
    EQADC_CLK_PS_DIV_36         = 17U,  /* Platform Clock Divide Factor: 36 */
    EQADC_CLK_PS_DIV_38         = 18U,  /* Platform Clock Divide Factor: 38 */
    EQADC_CLK_PS_DIV_40         = 19U,  /* Platform Clock Divide Factor: 40 */
    EQADC_CLK_PS_DIV_42         = 20U,  /* Platform Clock Divide Factor: 42 */
    EQADC_CLK_PS_DIV_44         = 21U,  /* Platform Clock Divide Factor: 44 */
    EQADC_CLK_PS_DIV_46         = 22U,  /* Platform Clock Divide Factor: 46 */
    EQADC_CLK_PS_DIV_48         = 23U,  /* Platform Clock Divide Factor: 48 */
    EQADC_CLK_PS_DIV_50         = 24U,  /* Platform Clock Divide Factor: 50 */
    EQADC_CLK_PS_DIV_52         = 25U,  /* Platform Clock Divide Factor: 52 */
    EQADC_CLK_PS_DIV_54         = 26U,  /* Platform Clock Divide Factor: 54 */
    EQADC_CLK_PS_DIV_56         = 27U,  /* Platform Clock Divide Factor: 56 */
    EQADC_CLK_PS_DIV_58         = 28U,  /* Platform Clock Divide Factor: 58 */
    EQADC_CLK_PS_DIV_60         = 29U,  /* Platform Clock Divide Factor: 60 */
    EQADC_CLK_PS_DIV_62         = 30U,  /* Platform Clock Divide Factor: 62 */
    EQADC_CLK_PS_DIV_64         = 31U   /* Platform Clock Divide Factor: 64 */
} Eqadc_ClkPrescaleType;

typedef enum
{
    EQADC_ALT_CONFIG_DISABLE    = 0x0U,     /* Select Standard Configuration for the conversion command */
    EQADC_ALT_CONFIG_SEL_1      = 0x8U,     /* Select Alternate Configuration 1 for the conversion command */
    EQADC_ALT_CONFIG_SEL_2      = 0x9U,     /* Select Alternate Configuration 2 for the conversion command */
    EQADC_ALT_CONFIG_SEL_3      = 0xAU,     /* Select Alternate Configuration 3 for the conversion command */
    EQADC_ALT_CONFIG_SEL_4      = 0xBU,     /* Select Alternate Configuration 4 for the conversion command */
    EQADC_ALT_CONFIG_SEL_5      = 0xCU,     /* Select Alternate Configuration 5 for the conversion command */
    EQADC_ALT_CONFIG_SEL_6      = 0xDU,     /* Select Alternate Configuration 6 for the conversion command */
    EQADC_ALT_CONFIG_SEL_7      = 0xEU,     /* Select Alternate Configuration 7 for the conversion command */
    EQADC_ALT_CONFIG_SEL_8      = 0xFU      /* Select Alternate Configuration 8 for the conversion command */
} Eqadc_AltConfigSelType;

typedef enum
{
    EQADC_ALT_DEST_RFIFO        = 0x0U,
    EQADC_ALT_DEST_DECFILT_A    = 0x1U,
    EQADC_ALT_DEST_DECFILT_B    = 0x2U,
    EQADC_ALT_DEST_DECFILT_C    = 0x3U,
    EQADC_ALT_DEST_DECFILT_D    = 0x4U,
    EQADC_ALT_DEST_DECFILT_E    = 0x5U,
    EQADC_ALT_DEST_DECFILT_F    = 0x6U,
    EQADC_ALT_DEST_DECFILT_G    = 0x7U,
    EQADC_ALT_DEST_DECFILT_A_E  = 0x8U,
    EQADC_ALT_DEST_DECFILT_B_E  = 0x9U,
    EQADC_ALT_DEST_DECFILT_C_E  = 0xAU,
    EQADC_ALT_DEST_DECFILT_D_E  = 0xBU,
    EQADC_ALT_DEST_DECFILT_A_G  = 0xCU,
    EQADC_ALT_DEST_DECFILT_B_G  = 0xDU,
    EQADC_ALT_DEST_DECFILT_C_G  = 0xEU,
    EQADC_ALT_DEST_DECFILT_D_G  = 0xFU
} Eqadc_AltConfigDestType;

typedef enum
{
    EQADC_RES_SEL_12_BITS       = 0U,
    EQADC_RES_SEL_10_BITS       = 1U,
    EQADC_RES_SEL_8_BITS        = 2U
} Eqadc_ResolutionSelType;

typedef enum
{
    EQADC_PRE_GAIN_X1           = 0U,
    EQADC_PRE_GAIN_X2           = 1U,
    EQADC_PRE_GAIN_X4           = 2U
} Eqadc_PreGainType;

typedef enum
{
    EQADC_CH_PULL_DISABLED      = 0U,
    EQADC_CH_PULL_UP            = 1U,
    EQADC_CH_PULL_DOWN          = 2U,
    EQADC_CH_PULL_UP_DOWN       = 3U
} Eqadc_ChanPullType;

typedef enum
{
    EQADC_PULL_STR_200KOHM      = 1U,
    EQADC_PULL_STR_100KOHM      = 2U,
    EQADC_PULL_STR_5KOHM        = 3U
} Eqadc_PullStrengthType;



typedef enum
{
    EQADC_SRV_ETPU_A_TCR_1      = 0U,
    EQADC_SRV_ETPU_B_TCR_1      = 1U,
    EQADC_SRV_ETPU_A_TCR_2      = 2U,
    EQADC_SRV_ETPU_B_TCR_2      = 3U
} Eqadc_RedLineServerDataSlotSelType;

typedef enum
{
    EQADC_REDLINE_BITS_SEL_TBASE_0_15   = 0U,
    EQADC_REDLINE_BITS_SEL_TBASE_1_16   = 1U,
    EQADC_REDLINE_BITS_SEL_TBASE_2_17   = 2U,
    EQADC_REDLINE_BITS_SEL_TBASE_3_18   = 3U,
    EQADC_REDLINE_BITS_SEL_TBASE_4_19   = 4U,
    EQADC_REDLINE_BITS_SEL_TBASE_5_20   = 5U,
    EQADC_REDLINE_BITS_SEL_TBASE_6_21   = 6U,
    EQADC_REDLINE_BITS_SEL_TBASE_7_22   = 7U,
    EQADC_REDLINE_BITS_SEL_TBASE_8_23   = 8U
} Eqadc_RedLineBitsSelType;

typedef enum
{
    EQADC_CFIFO_STATUS_IDLE             = 0U,
    EQADC_CFIFO_STATUS_WAITING_FOR_TRIG = 2U,
    EQADC_CFIFO_STATUS_TRIGGERED        = 3U
} Eqadc_CfifoStatusType;

typedef enum
{
    EQADC_MSG_TAG_RFIFO0                = 0U,
    EQADC_MSG_TAG_RFIFO1                = 1U,
    EQADC_MSG_TAG_RFIFO2                = 2U,
    EQADC_MSG_TAG_RFIFO3                = 3U,
    EQADC_MSG_TAG_RFIFO4                = 4U,
    EQADC_MSG_TAG_RFIFO5                = 5U,
    EQADC_MSG_TAG_NULL_MSG              = 8U,
    EQADC_MSG_TAG_RESERVED_0            = 9U,
    EQADC_MSG_TAG_RESERVED_1            = 10U
} Eqadc_RfifoMsgTagType;

typedef enum
{
    EQADC_ADCLK_SAMPLING_CYCLES_2       = 0U,
    EQADC_ADCLK_SAMPLING_CYCLES_8       = 1U,
    EQADC_ADCLK_SAMPLING_CYCLES_64      = 2U,
    EQADC_ADCLK_SAMPLING_CYCLES_128     = 3U
} Eqadc_LongSampTimeType;

typedef enum
{
    EQADC_CONFIG_CMD_WRITE              = 0U,
    EQADC_CONFIG_CMD_READ               = 1U
} Eqadc_RwConfigCmdType;

typedef enum
{
    EQADC_ADC_REG_CR         = 0x01U,    /* The address of ADC0/ADC1 Configuration Control Register */
    EQADC_ADC_REG_TSCR       = 0x02U,    /* The address of Time Stamp Control Register */
    EQADC_ADC_REG_TBCR       = 0x03U,    /* The address of Time Base Counter Register */
    EQADC_ADC_REG_GCCR       = 0x04U,    /* The address of ADC0/ADC1 Gain Calibration Constant Register */
    EQADC_ADC_REG_OCCR       = 0x05U,    /* The address of ADC0/ADC1 Offset Calibration Constant Register */
    EQADC_ADC_REG_ACR1       = 0x30U,    /* The address of Alternate Configuration 1 Control Register */
    EQADC_ADC_REG_AGR1       = 0x31U,    /* The address of ADC0/ADC1 Alternate Gain 1 Register */
    EQADC_ADC_REG_AOR1       = 0x32U,    /* The address of ADC0/ADC1 Alternate Offset 1 Register */
    EQADC_ADC_REG_ACR2       = 0x34U,    /* The address of Alternate Configuration 2 Control Register */
    EQADC_ADC_REG_AGR2       = 0x35U,    /* The address of ADC0/ADC1 Alternate Gain 2 Register */
    EQADC_ADC_REG_AOR2       = 0x36U,    /* The address of ADC0/ADC1 Alternate Offset 2 Register */
    EQADC_ADC_REG_ACR3       = 0x38U,    /* The address of Alternate Configuration 3 Control Register */
    EQADC_ADC_REG_ACR4       = 0x3CU,    /* The address of Alternate Configuration 4 Control Register */
    EQADC_ADC_REG_ACR5       = 0x40U,    /* The address of Alternate Configuration 5 Control Register */
    EQADC_ADC_REG_ACR6       = 0x44U,    /* The address of Alternate Configuration 6 Control Register */
    EQADC_ADC_REG_ACR7       = 0x48U,    /* The address of Alternate Configuration 7 Control Register */
    EQADC_ADC_REG_ACR8       = 0x4CU     /* The address of Alternate Configuration 8 Control Register */
} Eqadc_OnChipAdcRegAddrType;

typedef enum
{
    EQADC_HW_TRIG_NOT_CONNECTED = 0U,
    EQADC_HW_TRIG_RTI           = 1U,
    EQADC_HW_TRIG_PIT0_CH0      = 2U,
    EQADC_HW_TRIG_PIT0_CH1      = 3U,
    EQADC_HW_TRIG_PIT1_CH0      = 4U,
    EQADC_HW_TRIG_PIT1_CH1      = 5U,
    EQADC_HW_TRIG_ETRIG0        = 6U,
    EQADC_HW_TRIG_ETRIG1        = 7U,
    EQADC_HW_TRIG_ETPUA28       = 8U,
    EQADC_HW_TRIG_ETPUA29       = 9U,
    EQADC_HW_TRIG_ETPUA30       = 10U,
    EQADC_HW_TRIG_ETPUA31       = 11U,
    EQADC_HW_TRIG_ETPUB28       = 12U,
    EQADC_HW_TRIG_ETPUB29       = 13U,
    EQADC_HW_TRIG_ETPUB30       = 14U,
    EQADC_HW_TRIG_ETPUB31       = 15U,
    EQADC_HW_TRIG_ETPUC28       = 16U,
    EQADC_HW_TRIG_ETPUC29       = 17U,
    EQADC_HW_TRIG_ETPUC30       = 18U,
    EQADC_HW_TRIG_ETPUC31       = 19U,
    EQADC_HW_TRIG_EMIOS0_CH16   = 20U,
    EQADC_HW_TRIG_EMIOS0_CH17   = 21U,
    EQADC_HW_TRIG_EMIOS0_CH18   = 22U,
    EQADC_HW_TRIG_EMIOS0_CH19   = 23U,
    EQADC_HW_TRIG_EMIOS0_CH20   = 24U,
    EQADC_HW_TRIG_EMIOS0_CH21   = 25U,
    EQADC_HW_TRIG_EMIOS0_CH22   = 26U,
    EQADC_HW_TRIG_EMIOS0_CH23   = 27U,
    EQADC_HW_TRIG_ETPUA7        = 28U,  /* ETPU trigger CFIFO_1 only */
    EQADC_HW_TRIG_ETPUA14       = 29U,  /* ETPU trigger CFIFO_2 only */
    EQADC_HW_TRIG_ETPUA22       = 30U,  /* ETPU trigger CFIFO_3 only */
    EQADC_HW_TRIG_ETPUA26       = 31U,  /* ETPU trigger CFIFO_5 only */
    EQADC_HW_TRIG_ETPUA27       = 32U,  /* ETPU trigger CFIFO_4 only */
    EQADC_HW_TRIG_EMIOS1_CH2    = 33U,  /* eMOIS trigger CFIFO_0 only */
    EQADC_HW_TRIG_EMIOS1_CH3    = 34U,  /* eMOIS trigger CFIFO_1 only */
    EQADC_HW_TRIG_EMIOS1_CH4    = 35U,  /* eMOIS trigger CFIFO_5 only */
    EQADC_HW_TRIG_EMIOS1_CH5    = 36U,  /* eMOIS trigger CFIFO_4 only */
    EQADC_HW_TRIG_EMIOS1_CH6    = 37U,  /* eMOIS trigger CFIFO_3 only */
    EQADC_HW_TRIG_EMIOS1_CH7    = 38U   /* eMOIS trigger CFIFO_2 only */
} Eqadc_HwTrigSourceSelType;


typedef enum
{
    EQADC_ADVANCE_TRIG_NOT          = 0U,
    EQADC_ATRIG_RTI                 = 1U,
    EQADC_ATRIG_PIT0_CH0            = 2U,
    EQADC_ATRIG_PIT0_CH1            = 3U,
    EQADC_ATRIG_PIT1_CH0            = 4U,
    EQADC_ATRIG_PIT1_CH1            = 5U,
    EQADC_ATRIG_ETPUA30_PIT0_CH0    = 6U,
    EQADC_ATRIG_ETPUA30_PIT0_CH1    = 7U,
    EQADC_ATRIG_ETPUA28             = 8U,
    EQADC_ATRIG_ETPUA29             = 9U,
    EQADC_ATRIG_ETPUA30             = 10U,
    EQADC_ATRIG_ETPUA31             = 11U,
    EQADC_ATRIG_ETPUC28             = 12U,
    EQADC_ATRIG_ETPUC29             = 13U,
    EQADC_ATRIG_ETPUC30             = 14U,
    EQADC_ATRIG_ETPUC31             = 15U,
    EQADC_ATRIG_EMIOS1_CH2_PIT1_CH0 = 16U,
    EQADC_ATRIG_EMIOS1_CH2_PIT1_CH1 = 17U,
    EQADC_ATRIG_EMIOS0_CH23         = 18U
} Eqadc_AdvanceTrigSourceSelType;

/*******************************************************************************
 * @brief Structure for on-chip ADC.
 *
 * @note on-chip ADC0/ADC1
 *******************************************************************************/
typedef struct
{
    /* Index of the on-chip ADC to be configured. */
    VAR(EqadcAdcIdxType, AUTOMATIC) AdcIdx;

    /* External Multiplexer enable/disable for ADC0/1. */
    VAR(boolean, AUTOMATIC) AdcExtMuxEn;

    /* Time base Selection for ADC0/1 */
    VAR(Eqadc_TimeBaseSelType, AUTOMATIC) TimeBaseSel;

    /* Clock Selector for ADC0/1 */
    VAR(Eqadc_ClkSelType, AUTOMATIC) ClkSel;

    /* Clock Prescaler Field for ADC0/1 */
    VAR(Eqadc_ClkPrescaleType, AUTOMATIC) ClkPrescale;

    /* It is a unsigned 15-bit fixed pointed value.
     * The gain calibration constant is an unsigned fixed point number expressed
     *  in the GCC_INT.GCC_FRAC binary format. */
    VAR(uint16, AUTOMATIC) AdcGainCalibConst;

    /* OCC0/1 contains the offset calibration constant used to fine-tune ADC0/1 conversion results.
     * Negative values should be expressed using the two's complement representation. */
    VAR(int16_t, AUTOMATIC) AdcOffsetCalibConst;
    VAR(boolean, AUTOMATIC) ImmediateConvCmdEn;
} Eqadc_AdcConfigType;

/*******************************************************************************
 * @brief Structure for CFIFO (Command FIFO).
 *
 * @note
 *******************************************************************************/
typedef struct
{
    VAR(EqadcFifoIdxType, AUTOMATIC) CfifoIdx;
    VAR(Eqadc_CfifoModeType, AUTOMATIC) CfifoMode;
    VAR(Eqadc_IntDmaFillSelType, AUTOMATIC) IntDmaFillSel;
    VAR(uint8, AUTOMATIC) DmaMappedChan;
    VAR(boolean,  AUTOMATIC) DmaChanDisReqOnTransComplete;
    P2VAR(uint32, AUTOMATIC, ADC_APPL_DATA ) SourcePtr;
    VAR(uint32, AUTOMATIC) SourceLen;
    VAR(eDMACallbackType, AUTOMATIC) Callback;
    P2VAR(void, AUTOMATIC, ADC_APPL_DATA ) CallbackParam;
    VAR(Eqadc_HwTrigSourceSelType, AUTOMATIC) HwTrigSel; /* SIUL2_ISEL4~7 */

    /* CFIFO0 only */
    VAR(boolean, AUTOMATIC) Cfifo0EntryExtensionEn;
    VAR(Eqadc_Cfifo0AModeType, AUTOMATIC) Cfifo0AdvanceMode;
    VAR(Eqadc_AdvanceTrigSourceSelType, AUTOMATIC) Cfifo0AdvanceTrigSel;    /* SIUL2_ISEL9 */
} Eqadc_CfifoConfigType;

typedef struct
{
    VAR(EqadcFifoIdxType, AUTOMATIC) RfifoIdx;
    VAR(uint8, AUTOMATIC) ResultDmaMappedChan;
    P2VAR(uint16, AUTOMATIC, ADC_APPL_DATA ) DestPtr;
    VAR(uint32, AUTOMATIC) DestLen;
    VAR(eDMACallbackType, AUTOMATIC) Callback;
    P2VAR(void, AUTOMATIC, ADC_APPL_DATA ) CallbackParam;
    VAR(boolean, AUTOMATIC) EnHalfDestCallback;
} Eqadc_ResultDmaConfigType;

typedef struct
{
    VAR(Eqadc_AltConfigSelType, AUTOMATIC) AltConfigSel;
    VAR(boolean, AUTOMATIC) ResultTransInhibit;
    VAR(Eqadc_AltConfigDestType, AUTOMATIC) AltConvResultDEST;
    VAR(boolean, AUTOMATIC) FMTA_SignEn;
    VAR(Eqadc_ResolutionSelType, AUTOMATIC) AdcResSel;
    VAR(Eqadc_PreGainType, AUTOMATIC) AdcPreGain;
    /* Alternate Configuration 1: Alternate Gain 1(ADC0 and ADC1) + Alternate Offset 1(ADC0 and ADC1),
     * Alternate Configuration 2: Alternate Gain 2(ADC0 and ADC1) + Alternate Offset 2(ADC0 and ADC1) */
    VAR(uint16, AUTOMATIC) AdcAltGain[EQADC_ADC_NUM];
    VAR(uint16, AUTOMATIC) AdcAltOffset[EQADC_ADC_NUM];
} Eqadc_AlternateConfigType;

typedef struct
{
    VAR(uint8, AUTOMATIC) clientIdx;
    VAR(Eqadc_RedLineBitsSelType, AUTOMATIC) TimeBaseBitsSel;
    VAR(Eqadc_RedLineServerDataSlotSelType, AUTOMATIC) SRVnSel;
} Eqadc_RedLineClientConfigType;

typedef struct
{
    VAR(EqadcInstanceType, AUTOMATIC) Eqadc_HwInstId;

    /* Debug mode entry request (EQADC_MCR DBG) */
    VAR(boolean, AUTOMATIC) DebugModeEn;

    /* External Trigger Digital Filter Length (EQADC_ETDFR DFL) */
    VAR(uint8, AUTOMATIC) ExtTrigDigitalFilterLen;

    VAR(Eqadc_TimeBaseCountClkPresType, AUTOMATIC) TimeBasePresDiv;
} EqadcHwInstanceType;

typedef struct
{
    P2VAR(EqadcHwInstanceType, AUTOMATIC, ADC_APPL_DATA ) EqadcHwInst;
    VAR(uint8, AUTOMATIC) AdcConfigNum;
    P2VAR(Eqadc_AdcConfigType, AUTOMATIC, ADC_APPL_DATA ) AdcConfigArray;
    VAR(uint8, AUTOMATIC) CfifoConfigNum;
    P2VAR(Eqadc_CfifoConfigType, AUTOMATIC, ADC_APPL_DATA ) CfifoConfigArray;
    VAR(uint8, AUTOMATIC) ResultDmaConfigNum;
    P2VAR(Eqadc_ResultDmaConfigType, AUTOMATIC, ADC_APPL_DATA ) ResultDmaConfigArray;
    VAR(uint8, AUTOMATIC) AlternateConfigNum;
    P2VAR(Eqadc_AlternateConfigType, AUTOMATIC, ADC_APPL_DATA ) AlternateConfigArray;
    VAR(uint8, AUTOMATIC) RedLineClientConfigNum;
    P2VAR(Eqadc_RedLineClientConfigType, AUTOMATIC, ADC_APPL_DATA ) RedLineClientConfigArray;
} Adc_EqadcConfigType;

typedef struct
{
    VAR(boolean, AUTOMATIC) Eoq;
    VAR(boolean, AUTOMATIC) Pause;
    VAR(boolean, AUTOMATIC) RepeatStart;
    VAR(uint8, AUTOMATIC) cBufNum;
    VAR(boolean, AUTOMATIC) CalibConvResEn;
    VAR(EqadcFifoIdxType, AUTOMATIC) RfifoMsgTag;
    VAR(Eqadc_LongSampTimeType, AUTOMATIC) LongSampTime;
    VAR(boolean, AUTOMATIC) TimeStampReq;
    VAR(boolean, AUTOMATIC) FormatSignEn;
    VAR(uint8, AUTOMATIC) ChanNum;
    VAR(Eqadc_AltConfigSelType, AUTOMATIC) AltConfigSel;
    VAR(boolean, AUTOMATIC) FlushOrFMT;
} Eqadc_ConvCmdType;

typedef struct
{
    VAR(boolean, AUTOMATIC) Eoq;
    VAR(boolean, AUTOMATIC) Pause;
    VAR(boolean, AUTOMATIC) RepeatStart;
    VAR(uint8, AUTOMATIC) cBufNum;
    VAR(Eqadc_RwConfigCmdType, AUTOMATIC) RwCfgCmdType;
    VAR(uint16, AUTOMATIC) AdcRegValue;
    VAR(Eqadc_OnChipAdcRegAddrType, AUTOMATIC) AdcRegAddr;
    VAR(Eqadc_RfifoMsgTagType, AUTOMATIC) RfifoMsgTag;
} Eqadc_ConfigCmdType;

typedef enum
{
    EQADC_CAL_STANDARD_CONFIG   = EQADC_ALT_CONFIG_DISABLE, /* ADCx_GCCR, ADCx_OCCR */
    EQADC_CAL_ALT_CONFIG_1      = EQADC_ALT_CONFIG_SEL_1,   /* ADCx_AGR1, ADCx_AOR1 */
    EQADC_CAL_ALT_CONFIG_2      = EQADC_ALT_CONFIG_SEL_2    /* ADCx_AGR2, ADCx_AOR2 */
} Eqadc_CalibCfgSelType;

typedef struct
{
    VAR(Eqadc_CalibCfgSelType, AUTOMATIC) CalibCfgSel;
    VAR(EqadcFifoIdxType, AUTOMATIC) CfifoIdx;
    VAR(EqadcFifoIdxType, AUTOMATIC) RfifoIdx;
    VAR(Eqadc_LongSampTimeType, AUTOMATIC) LongSampTime;
    VAR(uint32, AUTOMATIC) TimeoutCal;
    VAR(uint16, AUTOMATIC) GainCalibConst;
    VAR(int16, AUTOMATIC) OffsetCalibConst;
} Eqadc_CalibConfigInfoType;

typedef struct
{
    VAR(uint8, AUTOMATIC) AdcConfigNum;
    P2VAR(Eqadc_AdcConfigType, AUTOMATIC, ADC_APPL_DATA ) AdcConfigArray;
} Eqadc_AdcConfigTempType;

typedef struct
{
    VAR(uint8, AUTOMATIC) CfifoConfigNum;
    P2VAR(Eqadc_CfifoConfigType, AUTOMATIC, ADC_APPL_DATA ) CfifoConfigArray;
} Eqadc_CfifoConfigTempType;

typedef struct
{
    VAR(uint8, AUTOMATIC) ResultDmaConfigNum;
    P2VAR(Eqadc_ResultDmaConfigType, AUTOMATIC, ADC_APPL_DATA ) ResultDmaConfig;
} Eqadc_ResultDmaConfigTempType;

/*******************************************************************************
 * Function declaration.
 *******************************************************************************/
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc_LLD_Init \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_EqadcInst, \
    CONSTP2CONST(Adc_EqadcConfigType, ADC_CONST, ADC_APPL_CONST ) sAdc_ConfigPtr \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

extern FUNC(void, ADC_CODE) Adc_Eqadc_LLD_DeInit \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance \
);

extern FUNC(status_t, ADC_CODE) EQADC_LLD_CalibConvResult \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx, \
    CONSTP2VAR(Eqadc_CalibConfigInfoType, ADC_CONST, ADC_APPL_CONST) pAdc_CalCfgPtr \
);

extern FUNC(uint8, ADC_CODE) EQADC_LLD_GetDebugEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetDebugEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(boolean, ADC_CONST) bAdc_EnDis \
);

extern FUNC(uint8, ADC_CODE) EQADC_LLD_GetExtTrigDigitalFilterLength \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetExtTrigDigitalFilterLength \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_DigitalFilterLen \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetCQueueConfigCmd \
( \
    CONSTP2CONST(Eqadc_ConfigCmdType, ADC_CONST, ADC_APPL_CONST) pAdc_ConfigCmdPtr, \
    CONST(uint8, ADC_CONST) u8Adc_CmdCount, \
    CONSTP2VAR(uint32, ADC_CONST, ADC_APPL_CONST) pAdc_CQueueMemDest \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_CfifoPushConvCmd \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONSTP2CONST(Eqadc_ConvCmdType, ADC_CONST, ADC_APPL_CONST) pAdc_ConvCmdPtr \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetCQueueConvCmd \
( \
    CONSTP2CONST(Eqadc_ConvCmdType, ADC_CONST, ADC_APPL_CONST) pAdc_ConvCmdPtr, \
    CONST(uint8, ADC_CONST) u8Adc_CmdCount, \
    CONST(uint8, ADC_CONST) u8Adc_StreamNumSamp, \
    CONST(uint8, ADC_CONST) u8Adc_DmaSampleNum, \
    CONSTP2VAR(uint32, ADC_CONST, ADC_APPL_CONST) pAdc_CQueueMemDest \
);

extern FUNC(uint16, ADC_CODE)  EQADC_LLD_RfifoPopData \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_RfifoIdx \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SingleScanEn \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SingleScanEn_Sync \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx \
);

extern FUNC(status_t, ADC_CODE) EQADC_LLD_SetCfifoInvalidate \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx \
);

extern FUNC(Eqadc_CfifoModeType, ADC_CODE) EQADC_LLD_GetCfifoMode \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx \
);

extern FUNC(status_t, ADC_CODE) EQADC_LLD_SetCfifoMode \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(Eqadc_CfifoModeType, ADC_CONST) eAdc_CfifoModeTarget \
);

extern FUNC(uint8, ADC_CODE) EQADC_LLD_GetCfifo0EntryExtEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetCfifo0EntryExtEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(boolean, ADC_CONST) bAdc_EnDis \
);

extern FUNC(Eqadc_Cfifo0AModeType, ADC_CODE) EQADC_LLD_GetCfifo0AdvanceMode \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance \
);

extern FUNC(status_t, ADC_CODE) EQADC_LLD_SetCfifo0AdvanceMode \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(Eqadc_Cfifo0AModeType, ADC_CONST) eAdc_AdvanceTrigMode \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_IntEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx, \
    VAR(uint16, AUTOMATIC) u16Adc_IntMask, \
    VAR(boolean, AUTOMATIC) bAdc_EnDis \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_ClearFifoIntFlag \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx, \
    VAR(uint32, AUTOMATIC) u32Adc_FifoFlagMask \
);

extern FUNC(uint16, ADC_CODE) EQADC_LLD_GetCfifoTransferCounter \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetCfifoTransferCounter \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(uint16, ADC_CONST) u16Adc_TransCount \
);

extern FUNC(Eqadc_CfifoStatusType, ADC_CODE) EQADC_LLD_GetCFifoStatusSnapshot \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx \
);

extern FUNC(EqadcFifoIdxType, ADC_CODE) EQADC_LLD_GetLastCFifoSnapshot \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx \
);

extern FUNC(uint16, ADC_CODE) EQADC_LLD_GetTransCountLastCFifoSnapshot \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx \
);

extern FUNC(void, ADC_CODE) EQADC_LLD_SetRedLineClientConfig \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_ClientIdx, \
    CONST(Eqadc_RedLineBitsSelType, ADC_CONST) eAdc_RedLineTbaseBitSel, \
    CONST(Eqadc_RedLineServerDataSlotSelType, ADC_CONST) eAdc_RedLineSlotSel \
);

extern FUNC(uint32, ADC_CODE) EQADC_LLD_GetCfifoEntryData \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(uint8, ADC_CONST) u8Adc_EntryIdx \
);

extern FUNC(uint32, ADC_CODE) EQADC_LLD_GetCfifo0ExtEntryData \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_EntryIdx \
);

extern FUNC(uint32, ADC_CODE) EQADC_LLD_GetRfifoEntryData \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_RfifoIdx, \
    CONST(uint8, ADC_CONST) u8Adc_EntryIdx \
);

#if EQADC_ONCHIPADC_RW_LLD
extern FUNC(void, ADC_CODE) EQADC_LLD_SetAdcRegValueSSE \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(Eqadc_OnChipAdcRegAddrType, ADC_CONST) eAdc_AdcReg, \
    CONST(uint16, ADC_CONST) u16Adc_AdcRegVal \
);

extern FUNC(uint16, ADC_CODE) EQADC_LLD_GetAdcRegValueSSE \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcAdcIdxType, ADC_CONST) eAdc_AdcIdx, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_RfifoIdx, \
    CONST(Eqadc_OnChipAdcRegAddrType, ADC_CONST) eAdc_AdcReg \
);
#endif
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_CFCRxSetInvalidate \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(uint8, ADC_CODE) EQADC_ISELx_SetCfifoTrig \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx, \
    CONST(uint8, ADC_CONST) u8Adc_TrigSourceVal\
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_CFCRx_SetCfifoxEntryExtEnDis \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx, \
    CONST(boolean, ADC_CONST) bAdc_EnDis \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_CFCRx_SetAMode0 \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx, \
    CONST(uint32, ADC_CONST) u32Adc_Cfifo0AdvanceMode0 \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_CFCR_CfifoStreamModeEnDis \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx, \
    CONST(boolean, ADC_CONST) bAdc_EnDis \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(uint8, ADC_CODE) EQADC_ISELx_SetCfifo0AdvanceTrig \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_AdvanceTrigVal \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_IDCRx_FifoIntDmaEnDis \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_FifoIdx, \
    CONST(uint16, ADC_CONST) u16Adc_FifoIntDmaMask, \
    CONST(boolean, ADC_CONST) bAdc_EnDis \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_LLD_SetCfifoHwTrigSource \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_CfifoIdx, \
    CONST(Eqadc_HwTrigSourceSelType, ADC_CONST) eAdc_TrigSourceSel \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(uint32, ADC_CODE) EQADC_LLD_GetFifoIntFlag \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(uint16, ADC_CODE) EQADC_LLD_GetIntDmaCtrlEn \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_LLD_SetCfifo0AdvanceTrigSource \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(Eqadc_AdvanceTrigSourceSelType, ADC_CONST) eAdc_AdvTrigSourceSel \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_CFCRxSetMode \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_CfifoIdx, \
    CONST(uint32, ADC_CONST) u32Adc_CfifoModeTarget \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_LLD_DmaEnDis \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx, \
    VAR(uint16, AUTOMATIC) u16Adc_DmaMask, \
    VAR(boolean, AUTOMATIC) bAdc_EnDis \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc_SetResultDmaConfig \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_EqadcInst, \
    P2CONST(Eqadc_ResultDmaConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_ResultDmaConfig \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(status_t, ADC_CODE)  EQADC_SetCfifoConfig \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONSTP2CONST(Eqadc_CfifoConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_CfifoCfgPtr \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(uint8, ADC_CODE) EQADC_LLD_GetFifoFlagStatus \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_Instance, \
    CONST(EqadcFifoIdxType, ADC_CONST) eAdc_FifoIdx, \
    CONST(Eqadc_FifoIntStatusType, ADC_CONST) eAdc_FifoStatusSel \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc_SetAlternateConfig \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_EqadcInst, \
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x, \
    P2CONST(Eqadc_AlternateConfigType, ADC_CONST, ADC_APPL_CONST) pAdc_AlternateConfig \
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) Eqadc_DeinitAlternateConfig \
( \
    CONST(EqadcInstanceType, ADC_CONST) eAdc_EqadcInst, \
    VAR(EqadcFifoIdxType, ADC_VAR) eAdc_Cfifo_x
);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_CODE) EQADC_LLD_InternalFuncEn(void);
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#endif /* ADC_LLDriver_H_ */

/** @} */
