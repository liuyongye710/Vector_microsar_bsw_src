/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007PT
* DESCRIPTION : CCFC3007PT features h file
* HISTORY     : Initial version
* @file     CCFC3007PT_features.h
* @version  3.0.0
* @date     2023 - 04 - 11
* @brief    Initial version.
*
*****************************************************************************/
/*PRQA S 0723 EOF*/
#ifndef CCFC3007PT_FEATURES_H_
#define CCFC3007PT_FEATURES_H_

#include "CCFC3007PT.h"
#include "common.h"

/* Enable checker core for z70 */
#define CHECKER_CORE_ENABLE

/* MCU(PLL,CGM,ME_MC) module features */

/* @brief Key and inverted key values so write access to MCTL register is permitted */
#define FEATURE_MC_ME_KEY           (0x5AF0U)
#define FEATURE_MC_ME_KEY_INV       (0xA50FU)

/* @brief Fast IRC trimmed clock frequency(16MHz). */
#define FEATURE_IRCOSC0_FREQ (16000000U)

/* @brief Fast XOSC clock frequency(40MHz). */
#define FEATURE_XOSC0_FREQ   (40000000U)

/* FLASH module features */

/* Base pointer of flash peripheral */
#define FLS_FMC                     (C55FMC)

/* The size of 16K block. */
#define FLS_16KB_SIZE  (0x4000U)
/* The size of 32K block. */
#define FLS_32KB_SIZE  (0x8000U)
/* The size of 64K block. */
#define FLS_64KB_SIZE  (0x10000U)
/* The size of 256K block. */
#define FLS_256KB_SIZE (0x40000U)

/*
 * @brief Flash block number for each address space
 * */
/* Low Block Number. */
#define FLS_LOW_16K_BLOCK        (6U)
#define FLS_LOW_32K_BLOCK        (2U)
#define FLS_LOW_64K_BLOCK        (4U)
#define FLS_LOW_BLOCK            (FLS_LOW_16K_BLOCK + FLS_LOW_32K_BLOCK + FLS_LOW_64K_BLOCK)
#define FLS_LOW_OFFSET           (0U)

/* Mid Block Number. */
#define FLS_MID_16K_BLOCK        (4U)
#define FLS_MID_32K_BLOCK        (2U)
#define FLS_MID_64K_BLOCK        (2U)
#define FLS_MID_BLOCK            (FLS_MID_16K_BLOCK + FLS_MID_32K_BLOCK + FLS_MID_64K_BLOCK)
#define FLS_MID_OFFSET           (FLS_LOW_BLOCK)

/* High Block Number. */
#define FLS_HIGH_16K_BLOCK       (0U)
#define FLS_HIGH_32K_BLOCK       (0U)
#define FLS_HIGH_64K_BLOCK       (8U)
#define FLS_HIGH_BLOCK           (FLS_HIGH_16K_BLOCK + FLS_HIGH_32K_BLOCK + FLS_HIGH_64K_BLOCK)
#define FLS_HIGH_OFFSET          (FLS_LOW_BLOCK + FLS_MID_BLOCK)

/* 256K Block Number. */
#define FLS_256K_BLOCK_FIRST     (32U)
#define FLS_256K_BLOCK_SECOND    (16U)
#define FLS_256K_BLOCK           (FLS_256K_BLOCK_FIRST + FLS_256K_BLOCK_SECOND)
#define FLS_256K_FIRST_OFFSET    (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK)
#define FLS_256K_SECOND_OFFSET   (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK + FLS_256K_BLOCK_FIRST)

/* ALL Block Number. */
#define FLS_BLOCK_ALL            (FLS_LOW_BLOCK + FLS_MID_BLOCK + FLS_HIGH_BLOCK + FLS_256K_BLOCK)

/*
 * @brief Flash block mask define
 */
/* Flash block lock mask */
#define FLS_LOCK_OFFSET_LOW     (16U)
#define FLS_LOCK_MASK_LOW       (0xFFFFFFFFU >> (32U - FLS_LOW_BLOCK))
#define FLS_LOCK_MASK_MID       (0xFFFFFFFFU >> (32U - FLS_MID_BLOCK))
#define FLS_LOCK_MASK_HIGH      (0xFFFFFFFFU >> (32U - FLS_HIGH_BLOCK))
#define FLS_LOCK_MASK_FIR256K   (0xFFFFFFFFU >> (32U - FLS_256K_BLOCK_FIRST))
#define FLS_LOCK_MASK_SEC256K   (0x0000FFFFU)

/* Flash block select mask */
#define FLS_SEL_MASK_LOW        (0xFFFFFFFFU >> (32U - FLS_LOW_BLOCK))
#define FLS_SEL_MASK_MID        (0xFFFFFFFFU >> (32U - FLS_MID_BLOCK))
#define FLS_SEL_MASK_HIGH       (0xFFFFFFFFU >> (32U - FLS_HIGH_BLOCK))
#define FLS_SEL_MASK_FIR256K    (0xFFFFFFFFU >> (32U - FLS_256K_BLOCK_FIRST))
#define FLS_SEL_MASK_SEC256K    (0x0000FFFFU)

/* Flash register numbers */
#define FLS_REG_NUM             (29U)

typedef struct
{
    uint32_t addrStart;
    uint32_t addrEnd;
    uint32_t lockSelReg;
    uint32_t lockSelBit;
    uint32_t blockSize;
} flash_info_t;

typedef struct
{
    const char * regName;
    uint32_t defValue;
    uint32_t regAddr;
} flash_regs_t;

static const flash_info_t flashInfo[FLS_BLOCK_ALL] = {
        /* Low Block */
        {0x00404000U, 0x00407FFFU, 0U, 16U, FLS_16KB_SIZE},   // block 0    P0 (BAF)
        {0x00FC0000U, 0x00FC3FFFU, 0U, 17U, FLS_16KB_SIZE},   // block 1    P0 (Normal Code)
        {0x00FC4000U, 0x00FC7FFFU, 0U, 18U, FLS_16KB_SIZE},   // block 2    P0 (Normal Code)
        {0x00FC8000U, 0x00FCBFFFU, 0U, 19U, FLS_16KB_SIZE},   // block 3    P1 (Normal Code)
        {0x00FCC000U, 0x00FCFFFFU, 0U, 20U, FLS_16KB_SIZE},   // block 4    P1 (Normal Code)
        {0x0060C000U, 0x0060FFFFU, 0U, 21U, FLS_16KB_SIZE},   // block 5    P1 (HSM Code)
        {0x00FD0000U, 0x00FD7FFFU, 0U, 22U, FLS_32KB_SIZE},   // block 6    P0 (Normal Code)
        {0x00FD8000U, 0x00FDFFFFU, 0U, 23U, FLS_32KB_SIZE},   // block 7    P1 (Normal Code)
        {0x00FE0000U, 0x00FEFFFFU, 0U, 24U, FLS_64KB_SIZE},   // block 8    P0 (Normal Code)
        {0x00FF0000U, 0x00FFFFFFU, 0U, 25U, FLS_64KB_SIZE},   // block 9    P0 (Normal Code)
        {0x00610000U, 0x0061FFFFU, 0U, 26U, FLS_64KB_SIZE},   // block 10   P1 (HSM Code)
        {0x00620000U, 0x0062FFFFU, 0U, 27U, FLS_64KB_SIZE},   // block 11   P1 (HSM Code)

        /* Mid Block */
        {0x00680000U, 0x00683FFFU, 0U, 0U, FLS_16KB_SIZE},    // block 12   P2 (HSM Data)
        {0x00684000U, 0x00687FFFU, 0U, 1U, FLS_16KB_SIZE},    // block 13   P2 (HSM Data)
        {0x00688000U, 0x0068BFFFU, 0U, 2U, FLS_16KB_SIZE},    // block 14   P2 (HSM Data)
        {0x0068C000U, 0x0068FFFFU, 0U, 3U, FLS_16KB_SIZE},    // block 15   P2 (HSM Data)
        {0x00690000U, 0x00697FFFU, 0U, 4U, FLS_32KB_SIZE},    // block 16   P2 (HSM Data)
        {0x00698000U, 0x0069FFFFU, 0U, 5U, FLS_32KB_SIZE},    // block 17   P2 (HSM Data)
        {0x006A0000U, 0x006AFFFFU, 0U, 6U, FLS_64KB_SIZE},    // block 18   P2 (HSM Data)
        {0x006B0000U, 0x006BFFFFU, 0U, 7U, FLS_64KB_SIZE},    // block 19   P2 (HSM Data)

        /* High Block */
        {0x00800000U, 0x0080FFFFU, 1U, 0U, FLS_64KB_SIZE},    // block 20   P3 (EEPROM)
        {0x00810000U, 0x0081FFFFU, 1U, 1U, FLS_64KB_SIZE},    // block 21   P3 (EEPROM)
        {0x00820000U, 0x0082FFFFU, 1U, 2U, FLS_64KB_SIZE},    // block 22   P3 (EEPROM)
        {0x00830000U, 0x0083FFFFU, 1U, 3U, FLS_64KB_SIZE},    // block 23   P3 (EEPROM)
        {0x00840000U, 0x0084FFFFU, 1U, 4U, FLS_64KB_SIZE},    // block 24   P3 (EEPROM)
        {0x00850000U, 0x0085FFFFU, 1U, 5U, FLS_64KB_SIZE},    // block 25   P3 (EEPROM)
        {0x00860000U, 0x0086FFFFU, 1U, 6U, FLS_64KB_SIZE},    // block 26   P3 (EEPROM)
        {0x00870000U, 0x0087FFFFU, 1U, 7U, FLS_64KB_SIZE},    // block 27   P3 (EEPROM)

        /* 256K Block */
        {0x01000000U, 0x0103FFFFU, 2U, 0U, FLS_256KB_SIZE},   // block 28   P4
        {0x01040000U, 0x0107FFFFU, 2U, 1U, FLS_256KB_SIZE},   // block 29   P4
        {0x01080000U, 0x010BFFFFU, 2U, 2U, FLS_256KB_SIZE},   // block 30   P4
        {0x010C0000U, 0x010FFFFFU, 2U, 3U, FLS_256KB_SIZE},   // block 31   P4
        {0x01100000U, 0x0113FFFFU, 2U, 4U, FLS_256KB_SIZE},   // block 32   P4
        {0x01140000U, 0x0117FFFFU, 2U, 5U, FLS_256KB_SIZE},   // block 33   P4
        {0x01180000U, 0x011BFFFFU, 2U, 6U, FLS_256KB_SIZE},   // block 34   P4
        {0x011C0000U, 0x011FFFFFU, 2U, 7U, FLS_256KB_SIZE},   // block 35   P4
        {0x01200000U, 0x0123FFFFU, 2U, 8U, FLS_256KB_SIZE},   // block 36   P5
        {0x01240000U, 0x0127FFFFU, 2U, 9U, FLS_256KB_SIZE},   // block 37   P5
        {0x01280000U, 0x012BFFFFU, 2U, 10U, FLS_256KB_SIZE},  // block 38   P5
        {0x012C0000U, 0x012FFFFFU, 2U, 11U, FLS_256KB_SIZE},  // block 39   P5
        {0x01300000U, 0x0133FFFFU, 2U, 12U, FLS_256KB_SIZE},  // block 40   P5
        {0x01340000U, 0x0137FFFFU, 2U, 13U, FLS_256KB_SIZE},  // block 41   P5
        {0x01380000U, 0x013BFFFFU, 2U, 14U, FLS_256KB_SIZE},  // block 42   P5
        {0x013C0000U, 0x013FFFFFU, 2U, 15U, FLS_256KB_SIZE},  // block 43   P5
        {0x01400000U, 0x0143FFFFU, 2U, 16U, FLS_256KB_SIZE},  // block 44   P6
        {0x01440000U, 0x0147FFFFU, 2U, 17U, FLS_256KB_SIZE},  // block 45   P6
        {0x01480000U, 0x014BFFFFU, 2U, 18U, FLS_256KB_SIZE},  // block 46   P6
        {0x014C0000U, 0x014FFFFFU, 2U, 19U, FLS_256KB_SIZE},  // block 47   P6
        {0x01500000U, 0x0153FFFFU, 2U, 20U, FLS_256KB_SIZE},  // block 48   P6
        {0x01540000U, 0x0157FFFFU, 2U, 21U, FLS_256KB_SIZE},  // block 49   P6
        {0x01580000U, 0x015BFFFFU, 2U, 22U, FLS_256KB_SIZE},  // block 50   P6
        {0x015C0000U, 0x015FFFFFU, 2U, 23U, FLS_256KB_SIZE},  // block 51   P6
        {0x01600000U, 0x0163FFFFU, 2U, 24U, FLS_256KB_SIZE},  // block 52   P7
        {0x01640000U, 0x0167FFFFU, 2U, 25U, FLS_256KB_SIZE},  // block 53   P7
        {0x01680000U, 0x016BFFFFU, 2U, 26U, FLS_256KB_SIZE},  // block 54   P7
        {0x016C0000U, 0x016FFFFFU, 2U, 27U, FLS_256KB_SIZE},  // block 55   P7
        {0x01700000U, 0x0173FFFFU, 2U, 28U, FLS_256KB_SIZE},  // block 56   P7
        {0x01740000U, 0x0177FFFFU, 2U, 29U, FLS_256KB_SIZE},  // block 57   P7
        {0x01780000U, 0x017BFFFFU, 2U, 30U, FLS_256KB_SIZE},  // block 58   P7
        {0x017C0000U, 0x017FFFFFU, 2U, 31U, FLS_256KB_SIZE},  // block 59   P7
        {0x01800000U, 0x0183FFFFU, 3U, 0U, FLS_256KB_SIZE},   // block 60   P8
        {0x01840000U, 0x0187FFFFU, 3U, 1U, FLS_256KB_SIZE},   // block 61   P8
        {0x01880000U, 0x018BFFFFU, 3U, 2U, FLS_256KB_SIZE},   // block 62   P8
        {0x018C0000U, 0x018FFFFFU, 3U, 3U, FLS_256KB_SIZE},   // block 63   P8
        {0x01900000U, 0x0193FFFFU, 3U, 4U, FLS_256KB_SIZE},   // block 64   P8
        {0x01940000U, 0x0197FFFFU, 3U, 5U, FLS_256KB_SIZE},   // block 65   P8
        {0x01980000U, 0x019BFFFFU, 3U, 6U, FLS_256KB_SIZE},   // block 66   P8
        {0x019C0000U, 0x019FFFFFU, 3U, 7U, FLS_256KB_SIZE},   // block 67   P8
        {0x01A00000U, 0x01A3FFFFU, 3U, 8U, FLS_256KB_SIZE},   // block 68   P9
        {0x01A40000U, 0x01A7FFFFU, 3U, 9U, FLS_256KB_SIZE},   // block 69   P9
        {0x01A80000U, 0x01ABFFFFU, 3U, 10U, FLS_256KB_SIZE},  // block 70   P9
        {0x01AC0000U, 0x01AFFFFFU, 3U, 11U, FLS_256KB_SIZE},  // block 71   P9
        {0x01B00000U, 0x01B3FFFFU, 3U, 12U, FLS_256KB_SIZE},  // block 72   P9
        {0x01B40000U, 0x01B7FFFFU, 3U, 13U, FLS_256KB_SIZE},  // block 73   P9
        {0x01B80000U, 0x01BBFFFFU, 3U, 14U, FLS_256KB_SIZE},  // block 74   P9
        {0x01BC0000U, 0x01BFFFFFU, 3U, 15U, FLS_256KB_SIZE},  // block 75   P9
};

static const flash_regs_t flashRegs[FLS_REG_NUM] = {
        {"MCR",    0x00000600U,     0xfffe0000U},
        {"MCRA",   0x00000600U,     0xfffe0004U},
        {"MCRE",   0x1880054BU,     0xfffe0008U},
        {"LOCK0",  0xBFFFFFFFU,     0xfffe0010U},
        {"LOCK1",  0x0000FFFFU,     0xfffe0014U},
        {"LOCK2",  0xFFFFFFFFU,     0xfffe0018U},
        {"LOCK3",  0x0000FFFFU,     0xfffe001cU},
        {"LOCK0A", 0xBFFFFFFFU,     0xfffe0028U},
        {"LOCK1A", 0x0000FFFFU,     0xfffe002cU},
        {"SEL0",   0x00000000U,     0xfffe0038U},
        {"SEL1",   0x00000000U,     0xfffe003cU},
        {"SEL2",   0x00000000U,     0xfffe0040U},
        {"SEL3",   0x00000000U,     0xfffe0044U},
        {"UT0",    0x00000001U,     0xfffe0054U},
        {"UM0",    0x00000000U,     0xfffe0058U},
        {"UM1",    0x00000000U,     0xfffe005cU},
        {"UM2",    0x00000000U,     0xfffe0060U},
        {"UM3",    0x00000000U,     0xfffe0064U},
        {"UM4",    0x00000000U,     0xfffe0068U},
        {"UM5",    0x00000000U,     0xfffe006cU},
        {"UM6",    0x00000000U,     0xfffe0070U},
        {"UM7",    0x00000000U,     0xfffe0074U},
        {"UM8",    0x00000000U,     0xfffe0078U},
        {"UM9",    0x00000000U,     0xfffe007cU},
        {"OPP0",   0x30010000U,     0xfffe0080U},
        {"OPP1",   0x0000FF00U,     0xfffe0084U},
        {"OPP2",   0x00000000U,     0xfffe0088U},
        {"OPP3",   0x00000000U,     0xfffe008cU},
        {"TMD",    0x00000000U,     0xfffe0090U},
};

/* PFLASH module features */

/* Count of Calibration Region Descriptor */
#define PFLASH_PFCRD_COUNT               (32U)
/* Count of Safe Calibration Region Descriptor */
#define PFLASH_PFCRD_SAFE_COUNT          (PFLASH_PFCRD_COUNT/2)
/*
 * Safe Calibration Control
 * 0U: normal calibration
 * 1U: safe calibration
 * */
#define PFLASH_Safe_Calibration          (0U)
/* Flash Remap Size */
typedef enum
{
    REMAP_SIZE_32B =   5U,
    REMAP_SIZE_64B =   6U,
    REMAP_SIZE_128B =  7U,
    REMAP_SIZE_256B =  8U,
    REMAP_SIZE_512B =  9U,
    REMAP_SIZE_1KB =   10U,
    REMAP_SIZE_2KB =   11U,
    REMAP_SIZE_4KB =   12U,
    REMAP_SIZE_8KB =   13U,
    REMAP_SIZE_16KB =  14U,
    REMAP_SIZE_32KB =  15U,
    REMAP_SIZE_64KB =  16U,
    REMAP_SIZE_128KB = 17U,
    REMAP_SIZE_256KB = 18U,
    REMAP_SIZE_512KB = 19U,
    REMAP_SIZE_1MB =   20U,
    REMAP_SIZE_2MB =   21U,
    REMAP_SIZE_4MB =   22U,
    REMAP_SIZE_8MB =   23U
} flash_remap_size_t;

typedef struct
{
    uint32_t flsLogicAddr;
    uint32_t ramPhyAddr;
    flash_remap_size_t remapSize;
} flash_remap_config_t;

/* MEMU module features */
/* Peripheral RAM ECC Correctable Error Detect */
#define MEMU_ERR_FLAG_PR_CE   (0x00100000U)
/* Peripheral RAM ECC Uncorrectable Error Detect */
#define MEMU_ERR_FLAG_PR_UCE  (0x00080000U)
/* Peripheral RAM ECC Correctable error Overflow */
#define MEMU_ERR_FLAG_PR_CEO  (0x00040000U)
/* Peripheral RAM ECC Uncorrectable error Overflow */
#define MEMU_ERR_FLAG_PR_UCO  (0x00020000U)
/* Peripheral RAM ECC Error buffer Overflow */
#define MEMU_ERR_FLAG_PR_EBO  (0x00010000U)
/* Flash ECC Correctable Error Detect */
#define MEMU_ERR_FLAG_F_CE    (0x00001000U)
/* Flash ECC Uncorrectable Error Detect */
#define MEMU_ERR_FLAG_F_UCE   (0x00000800U)
/* Flash ECC Correctable Error Overflow */
#define MEMU_ERR_FLAG_F_CEO   (0x00000400U)
/* Flash ECC Uncorrectable Error Overflow */
#define MEMU_ERR_FLAG_F_UCO   (0x00000200U)
/* Flash ECC Error buffer Overflow */
#define MEMU_ERR_FLAG_F_EBO   (0x00000100U)
/* System RAM ECC and MBIST Correctable Error Detect */
#define MEMU_ERR_FLAG_SR_CE   (0x00000010U)
/* System RAM ECC and MBIST Uncorrectable Error Detect */
#define MEMU_ERR_FLAG_SR_UCE  (0x00000008U)
/* System RAM ECC and MBIST Correctable error Overflow */
#define MEMU_ERR_FLAG_SR_CEO  (0x00000004U)
/* System RAM ECC and MBIST Uncorrectable error Overflow */
#define MEMU_ERR_FLAG_SR_UCO  (0x00000002U)
/* System RAM ECC and MBIST Error buffer Overflow */
#define MEMU_ERR_FLAG_SR_EBO  (0x00000001U)

/* MEMU_ERR_FLAG grouped */
#define MEMU_ERR_FLAG_PERRAM_all               (0x001F0000U)
#define MEMU_ERR_FLAG_FLASH_all                (0x00001F00U)
#define MEMU_ERR_FLAG_SYSRAM_all               (0x0000001FU)
#define MEMU_ERR_FLAG_correctable_all          (0x00101010U)
#define MEMU_ERR_FLAG_uncorrectable_all        (0x00080808U)
#define MEMU_ERR_FLAG_correctable_overflows    (0x00040404U)
#define MEMU_ERR_FLAG_uncorrectable_overflows  (0x00020202U)
#define MEMU_ERR_FLAG_buffer_overflows         (0x00010101U)
#define MEMU_ERR_FLAG_PERRAM_overflows         (0x00070000U)
#define MEMU_ERR_FLAG_FLASH_overflows          (0x00000700U)
#define MEMU_ERR_FLAG_SYSRAM_overflows         (0x00000007U)

/* SMPU module features */

/* Total number of bus masters */
#define SMPU_MASTER_COUNT            (12U)

/* Max index of bus masters */
#define SMPU_MASTER_MAX_INDEX        (15U)

/* The SMPU Logical Bus Master Numbers */
#define SMPU_MASTER_CORE0            (0U)  // Core 0 (e200z710)
#define SMPU_MASTER_CORE1            (1U)  // Core 1 (e200z710)
#define SMPU_MASTER_CORE2            (2U)  // Core 2 (e200z425)
#define SMPU_MASTER_DMA0             (3U)  // DMA0
#define SMPU_MASTER_ENET             (4U)  // Ethernet
#define SMPU_MASTER_FLEXRAY0         (5U)  // FlexRay0
#define SMPU_MASTER_DMA1             (11U) // DMA1
#define SMPU_MASTER_FLEXRAY1         (13U) // FlexRay1
#define SMPU_MASTER_HSM              (14U) // HSM (Hardware Security Mode)
#define SMPU_MASTER_DEBUG_CORE0      (8U)
#define SMPU_MASTER_DEBUG_CORE1      (9U)
#define SMPU_MASTER_DEBUG_CORE2      (10U)
/* Size of Registers Arrays */
#define SMPU_ERR_COUNT                           (16u)

typedef volatile struct SMPU_tag  SMPU_Type;

/* Number of instances of the SMPU module. */
#define SMPU_INSTANCE_COUNT                      (2u)

/* SMPU0 base pointer */
#define SMPU0                                   ((volatile SMPU_Type *)(0xFC010000UL))
/* SMPU1 base pointer */
#define SMPU1                                   ((volatile SMPU_Type *)(0xFC014000UL))

/* SMPU0 protect address region */
#define SMPU0_START_ADDR            (0x00000000U)
#define SMPU0_END_ADDR              (0xEFFFFFFFU)

/* SMPU1 protect address region */
#define SMPU1_START_ADDR            (0xF0000000U)
#define SMPU1_END_ADDR              (0xFFFFFFFFU)


/* Core MPU module features */

typedef union  {
  vuint32_t R;
  struct {
    vuint32_t  :8;
    vuint32_t RASIZE:7;  /* Number of Bits of Real Address supported */
    vuint32_t  :6;
    vuint32_t PIDSIZE:5; /* PID Register Size */
    vuint32_t NMPUS:2;   /* Number of MPUs */
    vuint32_t NTLBS:2;   /* Number of TLBs */
    vuint32_t MAVN:2;    /* MMU Architecture Version Number */
  } B;
} MMUCFG;

typedef union  {
  vuint32_t R;
  struct {
    vuint32_t FASSOC:1;  /* Fully Associative */
    vuint32_t  :7;
    vuint32_t MINSIZE:4; /* Minimum Region Size */
    vuint32_t MAXSIZE:4; /* Maximum Region Size */
    vuint32_t IPROT:1;   /* Invalidate Protect Capability */
    vuint32_t  :1;
    vuint32_t UAMSKA:1;  /* Upper Address Masking Availability */
    vuint32_t  :4;
    vuint32_t SHENTRY:3; /* Number of Shared (configurable for I or D) Entries */
    vuint32_t DENTRY:3;  /* Number of Data Entries */
    vuint32_t IENTRY:3;  /* Number of Instruction Entries */
  } B;
} MPU0CFG;

/* Maximum region size in bytes */
#define CMPU_MAX_REGION_SIZE    (4*1024*1024*1024ULL)
/* Minimum region size in bytes */
#define CMPU_MIN_REGION_SIZE    (8U)

/* MPU0CSR0 Bit Fields */
#define CMPU_CSR_BYPS_MASK          0x0000E000u
#define CMPU_CSR_BYPS_SHIFT         13u
#define CMPU_CSR_BYPS(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_BYPS_SHIFT))&CMPU_CSR_BYPS_MASK)
#define CMPU_CSR_BYPS_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_CSR_BYPS_MASK))>>CMPU_CSR_BYPS_SHIFT)
#define CMPU_CSR_BYPU_MASK          0x00001C00u
#define CMPU_CSR_BYPU_SHIFT         10u
#define CMPU_CSR_BYPU(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_BYPU_SHIFT))&CMPU_CSR_BYPU_MASK)
#define CMPU_CSR_BYPU_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_CSR_BYPU_MASK))>>CMPU_CSR_BYPU_SHIFT)
#define CMPU_CSR_DEN_MASK           0x000000E0u
#define CMPU_CSR_DEN_SHIFT          5u
#define CMPU_CSR_DEN(x)             (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_DEN_SHIFT))&CMPU_CSR_DEN_MASK)
#define CMPU_CSR_DEN_GET(x)         (((uint32_t)(((uint32_t)(x))&CMPU_CSR_DEN_MASK))>>CMPU_CSR_DEN_SHIFT)
#define CMPU_CSR_TIDCTL_MASK        0x00000008u
#define CMPU_CSR_TIDCTL_SHIFT       3u
#define CMPU_CSR_TIDCTL(x)          (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_TIDCTL_SHIFT))&CMPU_CSR_TIDCTL_MASK)
#define CMPU_CSR_TIDCTL_GET(x)      (((uint32_t)(((uint32_t)(x))&CMPU_CSR_TIDCTL_MASK))>>CMPU_CSR_TIDCTL_SHIFT)
#define CMPU_CSR_MPUFI_MASK         0x00000002u
#define CMPU_CSR_MPUFI_SHIFT        1u
#define CMPU_CSR_MPUFI(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_MPUFI_SHIFT))&CMPU_CSR_MPUFI_MASK)/*PRQA S 3471*/
#define CMPU_CSR_MPUFI_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_CSR_MPUFI_MASK))>>CMPU_CSR_MPUFI_SHIFT)
#define CMPU_CSR_MPUEN_MASK         0x00000001u
#define CMPU_CSR_MPUEN_SHIFT        0u
#define CMPU_CSR_MPUEN(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_CSR_MPUEN_SHIFT))&CMPU_CSR_MPUEN_MASK)
#define CMPU_CSR_MPUEN_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_CSR_MPUEN_MASK))>>CMPU_CSR_MPUEN_SHIFT)

/* MAS0 Bit Fields */
#define CMPU_MAS0_VALID_MASK        0x80000000u
#define CMPU_MAS0_VALID_SHIFT       31u
#define CMPU_MAS0_VALID(x)          (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_VALID_SHIFT))&CMPU_MAS0_VALID_MASK)
#define CMPU_MAS0_VALID_GET(x)      (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_VALID_MASK))>>CMPU_MAS0_VALID_SHIFT)
#define CMPU_MAS0_IPROT_MASK        0x40000000u
#define CMPU_MAS0_IPROT_SHIFT       30u
#define CMPU_MAS0_IPROT(x)          (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_IPROT_SHIFT))&CMPU_MAS0_IPROT_MASK)
#define CMPU_MAS0_IPROT_GET(x)      (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_IPROT_MASK))>>CMPU_MAS0_IPROT_SHIFT)
#define CMPU_MAS0_SEL_MASK          0x30000000u
#define CMPU_MAS0_SEL_SHIFT         28u
#define CMPU_MAS0_SEL(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_SEL_SHIFT))&CMPU_MAS0_SEL_MASK)
#define CMPU_MAS0_SEL_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_SEL_MASK))>>CMPU_MAS0_SEL_SHIFT)
#define CMPU_MAS0_RO_MASK           0x04000000u
#define CMPU_MAS0_RO_SHIFT          26u
#define CMPU_MAS0_RO(x)             (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_RO_SHIFT))&CMPU_MAS0_RO_MASK)
#define CMPU_MAS0_RO_GET(x)         (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_RO_MASK))>>CMPU_MAS0_RO_SHIFT)
#define CMPU_MAS0_DEBUG_MASK        0x02000000u
#define CMPU_MAS0_DEBUG_SHIFT       25u
#define CMPU_MAS0_DEBUG(x)          (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_DEBUG_SHIFT))&CMPU_MAS0_DEBUG_MASK)
#define CMPU_MAS0_DEBUG_GET(x)      (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_DEBUG_MASK))>>CMPU_MAS0_DEBUG_SHIFT)
#define CMPU_MAS0_INST_MASK         0x01000000u
#define CMPU_MAS0_INST_SHIFT        24u
#define CMPU_MAS0_INST(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_INST_SHIFT))&CMPU_MAS0_INST_MASK)
#define CMPU_MAS0_INST_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_INST_MASK))>>CMPU_MAS0_INST_SHIFT)
#define CMPU_MAS0_SHD_MASK          0x00800000u
#define CMPU_MAS0_SHD_SHIFT         23u
#define CMPU_MAS0_SHD(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_SHD_SHIFT))&CMPU_MAS0_SHD_MASK)
#define CMPU_MAS0_SHD_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_SHD_MASK))>>CMPU_MAS0_SHD_SHIFT)
#define CMPU_MAS0_ESEL_MASK         0x000F0000u
#define CMPU_MAS0_ESEL_SHIFT        16u
#define CMPU_MAS0_ESEL(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_ESEL_SHIFT))&CMPU_MAS0_ESEL_MASK)
#define CMPU_MAS0_ESEL_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_ESEL_MASK))>>CMPU_MAS0_ESEL_SHIFT)
#define CMPU_MAS0_UAMSK_MASK        0x00007000u
#define CMPU_MAS0_UAMSK_SHIFT       12u
#define CMPU_MAS0_UAMSK(x)          (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_UAMSK_SHIFT))&CMPU_MAS0_UAMSK_MASK)
#define CMPU_MAS0_UAMSK_GET(x)      (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_UAMSK_MASK))>>CMPU_MAS0_UAMSK_SHIFT)
#define CMPU_MAS0_UW_MASK           0x00000800u
#define CMPU_MAS0_UW_SHIFT          11u
#define CMPU_MAS0_UW(x)             (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_UW_SHIFT))&CMPU_MAS0_UW_MASK)
#define CMPU_MAS0_UW_GET(x)         (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_UW_MASK))>>CMPU_MAS0_UW_SHIFT)
#define CMPU_MAS0_SW_MASK           0x00000400u
#define CMPU_MAS0_SW_SHIFT          10u
#define CMPU_MAS0_SW(x)             (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_SW_SHIFT))&CMPU_MAS0_SW_MASK)
#define CMPU_MAS0_SW_GET(x)         (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_SW_MASK))>>CMPU_MAS0_SW_SHIFT)
#define CMPU_MAS0_UXR_MASK          0x00000200u
#define CMPU_MAS0_UXR_SHIFT         9u
#define CMPU_MAS0_UXR(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_UXR_SHIFT))&CMPU_MAS0_UXR_MASK)
#define CMPU_MAS0_UXR_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_UXR_MASK))>>CMPU_MAS0_UXR_SHIFT)
#define CMPU_MAS0_SXR_MASK          0x00000100u
#define CMPU_MAS0_SXR_SHIFT         8u
#define CMPU_MAS0_SXR(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_SXR_SHIFT))&CMPU_MAS0_SXR_MASK)
#define CMPU_MAS0_SXR_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_SXR_MASK))>>CMPU_MAS0_SXR_SHIFT)
#define CMPU_MAS0_IOVR_MASK         0x00000080u
#define CMPU_MAS0_IOVR_SHIFT        7u
#define CMPU_MAS0_IOVR(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_IOVR_SHIFT))&CMPU_MAS0_IOVR_MASK)
#define CMPU_MAS0_IOVR_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_IOVR_MASK))>>CMPU_MAS0_IOVR_SHIFT)
#define CMPU_MAS0_GOVR_MASK         0x00000040u
#define CMPU_MAS0_GOVR_SHIFT        6u
#define CMPU_MAS0_GOVR(x)           (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_GOVR_SHIFT))&CMPU_MAS0_GOVR_MASK)
#define CMPU_MAS0_GOVR_GET(x)       (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_GOVR_MASK))>>CMPU_MAS0_GOVR_SHIFT)
#define CMPU_MAS0_I_MASK            0x00000008u
#define CMPU_MAS0_I_SHIFT           3u
#define CMPU_MAS0_I(x)              (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_I_SHIFT))&CMPU_MAS0_I_MASK)
#define CMPU_MAS0_I_GET(x)          (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_I_MASK))>>CMPU_MAS0_I_SHIFT)
#define CMPU_MAS0_G_MASK            0x00000002u
#define CMPU_MAS0_G_SHIFT           1u
#define CMPU_MAS0_G(x)              (((uint32_t)(((uint32_t)(x))<<CMPU_MAS0_G_SHIFT))&CMPU_MAS0_G_MASK)
#define CMPU_MAS0_G_GET(x)          (((uint32_t)(((uint32_t)(x))&CMPU_MAS0_G_MASK))>>CMPU_MAS0_G_SHIFT)

/* MAS1 Bit Fields */
#define CMPU_MAS1_TID_MASK          0x00FF0000u
#define CMPU_MAS1_TID_SHIFT         16u
#define CMPU_MAS1_TID(x)            (((uint32_t)(((uint32_t)(x))<<CMPU_MAS1_TID_SHIFT))&CMPU_MAS1_TID_MASK)
#define CMPU_MAS1_TID_GET(x)        (((uint32_t)(((uint32_t)(x))&CMPU_MAS1_TID_MASK))>>CMPU_MAS1_TID_SHIFT)
#define CMPU_MAS1_TIDMSK_MASK       0x000000FFu
#define CMPU_MAS1_TIDMSK_SHIFT      0u
#define CMPU_MAS1_TIDMSK(x)         (((uint32_t)(((uint32_t)(x))<<CMPU_MAS1_TIDMSK_SHIFT))&CMPU_MAS1_TIDMSK_MASK)
#define CMPU_MAS1_TIDMSK_GET(x)     (((uint32_t)(((uint32_t)(x))&CMPU_MAS1_TIDMSK_MASK))>>CMPU_MAS1_TIDMSK_SHIFT)

/* EMIOS module features */
/* @brief EMIOS support all modes for each channel. */
#define FEATURE_EMIOS_ALL_MODE_ON_CHANNEL
/* @brief EMIOS support Quadrature decode mode. */
#define FEATURE_EMIOS_QD_MODE_SUPPORT
/* @brief EMIOS has channel pair in the IRQ interrupt. */
#define FEATURE_EMIOS_CHANNELS_PER_IRQ          (1U)
/* @brief EMIOS number channels maximum. */
#define FEATURE_EMIOS_CHANNEL_MAX_COUNT         (32U)
/* @brief EMIOS channels and counter buses select. */
#define FEATURE_EMIOS_BUS_A_SELECT              (1U)
#define FEATURE_EMIOS_BUS_B_SELECT              (1U)
#define FEATURE_EMIOS_BUS_C_SELECT              (0U)
#define FEATURE_EMIOS_BUS_D_SELECT              (1U)
#define FEATURE_EMIOS_BUS_E_SELECT              (0U)
#define FEATURE_EMIOS_BUS_F_SELECT              (0U)
/* @brief EMIOS channels and counter buses offset. */
#define FEATURE_EMIOS_BUS_B_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_C_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_D_SELECT_OFFSET(x)    (x)
#define FEATURE_EMIOS_BUS_E_SELECT_OFFSET(x)    (x)
/* @brief EMIOS number of channels available. */
#define FEATURE_EMIOS_CH_7_0_ENABLE             (1U)
#define FEATURE_EMIOS_CH_15_8_ENABLE            (0U)
#define FEATURE_EMIOS_CH_23_16_ENABLE           (1U)
#define FEATURE_EMIOS_CH_31_24_ENABLE           (0U)
#define FEATURE_EMIOS_CH_COUNT                  ((FEATURE_EMIOS_CH_7_0_ENABLE   * 8U) + \
                                                 (FEATURE_EMIOS_CH_15_8_ENABLE  * 8U) + \
                                                 (FEATURE_EMIOS_CH_23_16_ENABLE * 8U) + \
                                                 (FEATURE_EMIOS_CH_31_24_ENABLE * 8U))
/* @brief EMIOS channels offset. */
#define FEATURE_EMIOS_CH_7_0_SUB_OFFSET(x)      (x)
#define FEATURE_EMIOS_CH_15_8_SUB_OFFSET(x)     (x)
#define FEATURE_EMIOS_CH_23_16_SUB_OFFSET(x)    ((x) - 8U)
#define FEATURE_EMIOS_CH_31_24_SUB_OFFSET(x)    (x)

/* PWM_PAL module features */
#define FEATURE_PWMPAL_EMIOS_HAS_CHANNEL_MAPPING    (1)
#define PWMPAL_INDEX_2_HW_CHANNELS {0,1,2,3,4,5,6,7,16,17,18,19,20,21,22,23}

/* SIUL2 GPIO PCRS */
#define  PA0    0U
#define  PA1    1U
#define  PA2    2U
#define  PA3    3U
#define  PA4    4U
#define  PA5    5U
#define  PA6    6U
#define  PA7    7U
#define  PA8    8U
#define  PA9    9U
#define  PA10   10U
#define  PA11   11U
#define  PA12   12U
#define  PA13   13U
#define  PA14   14U
#define  PA15   15U
#define  PB0    16U
#define  PB1    17U
#define  PB2    18U
#define  PB3    19U
#define  PB4    20U
#define  PB5    21U
#define  PB6    22U
#define  PB7    23U
#define  PB8    24U
#define  PB9    25U
#define  PB10   26U
#define  PB11   27U
#define  PB12   28U
#define  PB13   29U
#define  PB14   30U
#define  PB15   31U
#define  PC_0   32U
#define  PC1    33U
#define  PC2    34U
#define  PC3    35U
#define  PC4    36U
#define  PC5    37U
#define  PC6    38U
#define  PC7    39U
#define  PC8    40U
#define  PC9    41U
#define  PC10   42U
#define  PC11   43U
#define  PC12   44U
#define  PC13   45U
#define  PC14   46U
#define  PC15   47U
#define  PD0    48U
#define  PD1    49U
#define  PD2    50U
#define  PD3    51U
#define  PD4    52U
#define  PD5    53U
#define  PD6    54U
#define  PD7    55U
#define  PD8    56U
#define  PD9    57U
#define  PD10   58U
#define  PD11   59U
#define  PD12   60U
#define  PD13   61U
#define  PD14   62U
#define  PD15   63U
#define  PE0    64U
#define  PE1    65U
#define  PE2    66U
#define  PE3    67U
#define  PE4    68U
#define  PE5    69U
#define  PE6    70U
#define  PE7    71U
#define  PE8    72U
#define  PE9    73U
#define  PE10   74U
#define  PE11   75U
#define  PE12   76U
#define  PE13   77U
#define  PE14   78U
#define  PE15   79U
#define  PF0    80U
#define  PF1    81U
#define  PF2    82U
#define  PF3    83U
#define  PF4    84U
#define  PF5    85U
#define  PF6    86U
#define  PF7    87U
#define  PF8    88U
#define  PF9    89U
#define  PF10   90U
#define  PF11   91U
#define  PF12   92U
#define  PF13   93U
#define  PF14   94U
#define  PF15   95U
#define  PG0    96U
#define  PG1    97U
#define  PG2    98U
#define  PG3    99U
#define  PG4    100U
#define  PG5    101U
#define  PG6    102U
#define  PG7    103U
#define  PG8    104U
#define  PG9    105U
#define  PG10   106U
#define  PG11   107U
#define  PG12   108U
#define  PG13   109U
#define  PG14   110U
#define  PG15   111U
#define  PH0    112U
#define  PH1    113U
#define  PH2    114U
#define  PH3    115U
#define  PH4    116U
#define  PH5    117U
#define  PH6    118U
#define  PH7    119U
#define  PH8    120U
#define  PH9    121U
#define  PH10   122U
#define  PH11   123U
#define  PH12   124U
#define  PH13   125U
#define  PH14   126U
#define  PH15   127U
#define  PI0    128U
#define  PI1    129U
#define  PI2    130U
#define  PI3    131U
#define  PI4    132U
#define  PI5    133U
#define  PI6    134U
#define  PI7    135U
#define  PI8    136U
#define  PI9    137U
#define  PI10   138U
#define  PI11   139U
#define  PI12   140U
#define  PI13   141U
#define  PI14   142U
#define  PI15   143U
#define  PJ0    144U
#define  PJ1    145U
#define  PJ2    146U
#define  PJ3    147U
#define  PJ4    148U
#define  PJ5    149U
#define  PJ6    150U
#define  PJ7    151U
#define  PJ8    152U
#define  PJ9    153U
#define  PJ10   154U
#define  PJ11   155U
#define  PJ12   156U
#define  PJ13   157U
#define  PJ14   158U
#define  PJ15   159U
#define  PK0    160U
#define  PK1    161U
#define  PK2    162U
#define  PK3    163U
#define  PK4    164U
#define  PK5    165U
#define  PK6    166U
#define  PK7    167U
#define  PK8    168U
#define  PK9    169U
#define  PK10   170U
#define  PK11   171U
#define  PK12   172U
#define  PK13   173U
#define  PK14   174U
#define  PK15   175U
#define  PL0    176U
#define  PL1    177U
#define  PL2    178U
#define  PL3    179U
#define  PL4    180U
#define  PL5    181U
#define  PL6    182U
#define  PL7    183U
#define  PL8    184U
#define  PL9    185U
#define  PL10   186U
#define  PL11   187U
#define  PL12   188U
#define  PL13   189U
#define  PL14   190U
#define  PL15   191U
#define  PM0    192U
#define  PM1    193U
#define  PM2    194U
#define  PM3    195U
#define  PM4    196U
#define  PM5    197U
#define  PM6    198U
#define  PM7    199U
#define  PM8    200U
#define  PM9    201U
#define  PM10   202U
#define  PM11   203U
#define  PM12   204U
#define  PM13   205U
#define  PM14   206U
#define  PM15   207U
#define  PN0    208U
#define  PN1    209U
#define  PN2    210U
#define  PN3    211U
#define  PN4    212U
#define  PN5    213U
#define  PN6    214U
#define  PN7    215U
#define  PN8    216U
#define  PN9    217U
#define  PN10   218U
#define  PN11   219U
#define  PN12   220U
#define  PN13   221U
#define  PN14   222U
#define  PN15   223U
#define  PQ0    224U
#define  PQ1    225U
#define  PQ2    226U
#define  PQ3    227U
#define  PQ4    228U
#define  PQ5    229U
#define  PQ6    230U
#define  PQ7    231U
#define  PQ8    232U
#define  PQ9    233U
#define  PQ10   234U
#define  PQ11   235U
#define  PQ12   236U
#define  PQ13   237U
#define  PQ14   238U
#define  PQ15   239U
#define  PR0    241U
#define  PR1    242U
#define  PR2    243U
#define  PR3    244U
#define  PR4    245U
#define  PR5    246U
#define  PR6    247U
#define  PR7    248U
#define  PR8    249U
#define  PR9    250U
#define  PR10   251U
#define  PR11   252U
#define  PR12   253U
#define  PR13   254U
#define  PR14   255U
#define  PR15   256U
#define  PS0    257U
#define  PS1    258U
#define  PS2    259U
#define  PS3    260U
#define  PS4    261U
#define  PS5    262U
#define  PS6    263U
#define  PS7    264U
#define  PS8    265U
#define  PS9    266U
#define  PS10   267U
#define  PS11   268U
#define  PS12   269U
#define  PS13   270U
#define  PS14   271U
#define  PS15   272U
#define  PT0    273U
#define  PT1    274U
#define  PT2    275U
#define  PT3    276U
#define  PT4    277U
#define  PT5    278U
#define  PT6    279U
#define  PT7    280U
#define  PT8    281U
#define  PT9    282U
#define  PT10   283U
#define  PT11   284U
#define  PT12   285U
#define  PT13   286U
#define  PT14   287U
#define  PT15   288U
#define  PV0    289U
#define  PV1    290U
#define  PV2    291U
#define  PV3    292U
#define  PV4    293U
#define  PV5    294U
#define  PV6    295U
#define  PV7    296U
#define  PV8    297U
#define  PV9    298U
#define  PV10   299U
#define  PV11   300U
#define  PV12   301U
#define  PV13   302U
#define  PV14   303U
#define  PV15   304U
#define  PW0    305U
#define  PW1    306U
#define  PW2    307U
#define  PW3    308U
#define  PW4    309U
#define  PW5    310U
#define  PW6    311U
#define  PW7    312U
#define  PW8    313U
#define  PW9    314U
#define  PW10   315U
#define  PW11   316U
#define  PW12   317U
#define  PW13   318U
#define  PW14   319U
#define  PW15   320U
#define  PX0    321U
#define  PX1    322U
#define  PX2    240U
#define  PX3    323U
#define  PX4    324U
#define  PX5    325U
#define  PX6    326U
#define  PX7    327U
#define  PX8    328U
#define  PX9    329U
#define  PX10   330U
#define  PX11   331U
#define  PX12   332U
#define  PX13   333U
#define  PX14   334U
#define  PX15   335U
#define  PY0    336U
#define  PY1    337U
#define  PY2    338U
#define  PY3    339U
#define  PY4    340U

/*
 * @brief EIRQ Pin definition
 */
#define EIRQ0           (0U)
#define EIRQ1           (1U)
#define EIRQ2           (2U)
#define EIRQ3           (3U)
#define EIRQ4           (4U)
#define EIRQ5           (5U)
#define EIRQ6           (6U)
#define EIRQ7           (7U)
#define EIRQ8           (8U)
#define EIRQ9           (9U)
#define EIRQ10          (10U)
#define EIRQ11          (11U)
#define EIRQ12          (12U)
#define EIRQ13          (13U)
#define EIRQ14          (14U)
#define EIRQ15          (15U)
#define EIRQ_MAX_NUM    (16U)

/* The SIUL2 EIRQ MUX index for EIRQ0 - EIRQ6 */
#define  EIRQ0_INDEX       (779U)
#define  EIRQ1_INDEX       (780U)
#define  EIRQ2_INDEX       (781U)
#define  EIRQ3_INDEX       (782U)
#define  EIRQ4_INDEX       (783U)
#define  EIRQ5_INDEX       (784U)
#define  EIRQ6_INDEX       (785U)

/* The SIUL2 EIRQ pins */
#define  EIRQ0_PQ0     (0U)
#define  EIRQ0_PR12    (1U)
#define  EIRQ0_PA0     (2U)
#define  EIRQ1_PQ1     (3U)
#define  EIRQ1_PH1     (4U)
#define  EIRQ2_PV2     (5U)
#define  EIRQ2_PF5     (6U)
#define  EIRQ3_PV1     (7U)
#define  EIRQ3_PM10    (8U)
#define  EIRQ4_PV11    (9U)
#define  EIRQ4_PH13    (10U)
#define  EIRQ5_PV12    (11U)
#define  EIRQ5_PM5     (12U)
#define  EIRQ5_PF2     (13U)
#define  EIRQ6_PF13    (14U)
#define  EIRQ6_PE3     (15U)
#define  EIRQ7_PA2     (16U)
#define  EIRQ8_PH12    (17U)
#define  EIRQ9_PF14    (18U)
#define  EIRQ10_PE10   (19U)
#define  EIRQ11_PG15   (20U)
#define  EIRQ12_PF4    (21U)
#define  EIRQ13_PF6    (22U)
#define  EIRQ14_PF7    (23U)
#define  EIRQ15_PF8    (24U)

/* The SIUL2 EIRQ max pin num */
#define  EIRQ_MAX_PINS (25U)

typedef struct
{
    uint8_t  eirq_index;
    uint32_t mux_index;
    uint32_t pad_mux;
    uint16_t eirq_pin;
} siul_eirq_info_t;

static const siul_eirq_info_t eirqInfo[EIRQ_MAX_PINS] = {
        {EIRQ0,  EIRQ0_INDEX, 0U, PQ0},
        {EIRQ0,  EIRQ0_INDEX, 1U, PR12},
        {EIRQ0,  EIRQ0_INDEX, 2U, PA0},
        {EIRQ1,  EIRQ1_INDEX, 0U, PQ1},
        {EIRQ1,  EIRQ1_INDEX, 1U, PH1},
        {EIRQ2,  EIRQ2_INDEX, 0U, PV2},
        {EIRQ2,  EIRQ2_INDEX, 1U, PF5},
        {EIRQ3,  EIRQ3_INDEX, 0U, PV1},
        {EIRQ3,  EIRQ3_INDEX, 1U, PM10},
        {EIRQ4,  EIRQ4_INDEX, 0U, PV11},
        {EIRQ4,  EIRQ4_INDEX, 1U, PH13},
        {EIRQ5,  EIRQ5_INDEX, 0U, PV12},
        {EIRQ5,  EIRQ5_INDEX, 1U, PM5},
        {EIRQ5,  EIRQ5_INDEX, 2U, PF2},
        {EIRQ6,  EIRQ6_INDEX, 0U, PF13},
        {EIRQ6,  EIRQ6_INDEX, 1U, PE3},
        {EIRQ7,  0U, 0U, PA2},
        {EIRQ8,  0U, 0U, PH12},
        {EIRQ9,  0U, 0U, PF14},
        {EIRQ10, 0U, 0U, PE10},
        {EIRQ11, 0U, 0U, PG15},
        {EIRQ12, 0U, 0U, PF4},
        {EIRQ13, 0U, 0U, PF6},
        {EIRQ14, 0U, 0U, PF7},
        {EIRQ15, 0U, 0U, PF8},
};

typedef enum
{
    INTR_PRI_0 = 0U,
    INTR_PRI_1 = 1U,
    INTR_PRI_2 = 2U,
    INTR_PRI_3 = 3U,
    INTR_PRI_4 = 4U,
    INTR_PRI_5 = 5U,
    INTR_PRI_6 = 6U,
    INTR_PRI_7 = 7U,
    INTR_PRI_8 = 8U,
    INTR_PRI_9 = 9U,
    INTR_PRI_10 = 10U,
    INTR_PRI_11 = 11U,
    INTR_PRI_12 = 12U,
    INTR_PRI_13 = 13U,
    INTR_PRI_14 = 14U,
    INTR_PRI_15 = 15U,
    INTR_PRI_16 = 16U,
    INTR_PRI_17 = 17U,
    INTR_PRI_18 = 18U,
    INTR_PRI_19 = 19U,
    INTR_PRI_20 = 20U,
    INTR_PRI_21 = 21U,
    INTR_PRI_22 = 22U,
    INTR_PRI_23 = 23U,
    INTR_PRI_24 = 24U,
    INTR_PRI_25 = 25U,
    INTR_PRI_26 = 26U,
    INTR_PRI_27 = 27U,
    INTR_PRI_28 = 28U,
    INTR_PRI_29 = 29U,
    INTR_PRI_30 = 30U,
    INTR_PRI_31 = 31U,
    INTR_PRI_32 = 32U,
    INTR_PRI_33 = 33U,
    INTR_PRI_34 = 34U,
    INTR_PRI_35 = 35U,
    INTR_PRI_36 = 36U,
    INTR_PRI_37 = 37U,
    INTR_PRI_38 = 38U,
    INTR_PRI_39 = 39U,
    INTR_PRI_40 = 40U,
    INTR_PRI_41 = 41U,
    INTR_PRI_42 = 42U,
    INTR_PRI_43 = 43U,
    INTR_PRI_44 = 44U,
    INTR_PRI_45 = 45U,
    INTR_PRI_46 = 46U,
    INTR_PRI_47 = 47U,
    INTR_PRI_48 = 48U,
    INTR_PRI_49 = 49U,
    INTR_PRI_50 = 50U,
    INTR_PRI_51 = 51U,
    INTR_PRI_52 = 52U,
    INTR_PRI_53 = 53U,
    INTR_PRI_54 = 54U,
    INTR_PRI_55 = 55U,
    INTR_PRI_56 = 56U,
    INTR_PRI_57 = 57U,
    INTR_PRI_58 = 58U,
    INTR_PRI_59 = 59U,
    INTR_PRI_60 = 60U,
    INTR_PRI_61 = 61U,
    INTR_PRI_62 = 62U,
    INTR_PRI_63 = 63U,
    INTR_PRI_BUTT,
} IntrPrior;

typedef enum
{
    NotAvail_IRQn       = -128,     /**< Not available device specific interrupt */
    INTR_ID_0           = 0U, /* Software setable flag 0 INTC_SSCIR0[CLR0] */
    INTR_ID_1, /* Software setable flag 1 INTC_SSCIR0[CLR1] */
    INTR_ID_2, /* Software setable flag 2 INTC_SSCIR0[CLR2] */
    INTR_ID_3, /* Software setable flag 3 INTC_SSCIR0[CLR3] */
    INTR_ID_4, /* Software setable flag 4 INTC_SSCIR0[CLR4] */
    INTR_ID_5, /* Software setable flag 5 INTC_SSCIR0[CLR5] */
    INTR_ID_6, /* Software setable flag 6 INTC_SSCIR0[CLR6] */
    INTR_ID_7, /* Software setable flag 7 INTC_SSCIR0[CLR7] */
    INTR_ID_8, /* Software setable flag 8 INTC_SSCIR0[CLR8] */
    INTR_ID_9, /* Software setable flag 9 INTC_SSCIR0[CLR9] */
    INTR_ID_10, /* Software setable flag 10 INTC_SSCIR0[CLR10] */
    INTR_ID_11, /* Software setable flag 11 INTC_SSCIR0[CLR11] */
    INTR_ID_12, /* Software setable flag 12 INTC_SSCIR0[CLR12] */
    INTR_ID_13, /* Software setable flag 13 INTC_SSCIR0[CLR13] */
    INTR_ID_14, /* Software setable flag 14 INTC_SSCIR0[CLR14] */
    INTR_ID_15, /* Software setable flag 15 INTC_SSCIR0[CLR15] */
    INTR_ID_16, /* Software setable flag 16 INTC_SSCIR0[CLR16] */
    INTR_ID_17, /* Software setable flag 17 INTC_SSCIR0[CLR17] */
    INTR_ID_18, /* Software setable flag 18 INTC_SSCIR0[CLR18] */
    INTR_ID_19, /* Software setable flag 19 INTC_SSCIR0[CLR19] */
    INTR_ID_20, /* Software setable flag 20 INTC_SSCIR0[CLR20] */
    INTR_ID_21, /* Software setable flag 21 INTC_SSCIR0[CLR21] */
    INTR_ID_22, /* Software setable flag 22 INTC_SSCIR0[CLR22] */
    INTR_ID_23, /* Software setable flag 23 INTC_SSCIR0[CLR23] */
    INTR_ID_24, /* Software setable flag 24 INTC_SSCIR0[CLR24] */
    INTR_ID_25, /* Software setable flag 25 INTC_SSCIR0[CLR25] */
    INTR_ID_26, /* Software setable flag 26 INTC_SSCIR0[CLR26] */
    INTR_ID_27, /* Software setable flag 27 INTC_SSCIR0[CLR27] */
    INTR_ID_28, /* Software setable flag 28 INTC_SSCIR0[CLR28] */
    INTR_ID_29, /* Software setable flag 29 INTC_SSCIR0[CLR29] */
    INTR_ID_30, /* Software setable flag 30 INTC_SSCIR0[CLR30] */
    INTR_ID_31, /* Software setable flag 31 INTC_SSCIR0[CLR31] */
    INTR_ID_32, /* Platform watchdog timer0 SWT_0_IR[TIF] */
    INTR_ID_33, /* Platform watchdog timer1 SWT_1_IR[TIF] */
    INTR_ID_34, /* Platform watchdog timer2 SWT_2_IR[TIF] */
    INTR_ID_35, /* Platform watchdog timer3 SWT_3_IR[TIF] */
    INTR_ID_36, /* Platform periodic timer 0_0 (STM) STM_0_CIR0[CIF] */
    INTR_ID_37, /* Platform periodic timer 0_1 (STM) STM_0_CIR1[CIF] */
    INTR_ID_38, /* Platform periodic timer 0_2 (STM) STM_0_CIR2[CIF] */
    INTR_ID_39, /* Platform periodic timer 0_3 (STM) STM_0_CIR3[CIF] */
    INTR_ID_40, /* Platform periodic timer 1_0 (STM) STM_1_CIR0[CIF] */
    INTR_ID_41, /* Platform periodic timer 1_1 (STM) STM_1_CIR1[CIF] */
    INTR_ID_42, /* Platform periodic timer 1_2 (STM) STM_1_CIR2[CIF] */
    INTR_ID_43, /* Platform periodic timer 1_3 (STM) STM_1_CIR3[CIF] */
    INTR_ID_44, /* Platform periodic timer 2_0 (STM) STM_2_CIR0[CIF] */
    INTR_ID_45, /* Platform periodic timer 2_1 (STM) STM_2_CIR1[CIF] */
    INTR_ID_46, /* Platform periodic timer 2_2 (STM) STM_2_CIR2[CIF] */
    INTR_ID_47, /* Platform periodic timer 2_3 (STM) STM_2_CIR3[CIF] */
    INTR_ID_48,
    INTR_ID_49,
    INTR_ID_50,
    INTR_ID_51,
    DMA0_ERR0_127_IRQ52,/* eDMA Combined Error 127 - 0 eDMA Channel Error Flags */
    DMA0_CH0_IRQ53,     /* eDMA Channel 0 DMA_INTL[INT0] */
    DMA0_CH1_IRQ54,     /* eDMA Channel 1 DMA_INTL[INT1] */
    DMA0_CH2_IRQ55,     /* eDMA Channel 2 DMA_INTL[INT2] */
    DMA0_CH3_IRQ56,     /* eDMA Channel 3 DMA_INTL[INT3] */
    DMA0_CH4_IRQ57,     /* eDMA Channel 4 DMA_INTL[INT4] */
    DMA0_CH5_IRQ58,     /* eDMA Channel 5 DMA_INTL[INT5] */
    DMA0_CH6_IRQ59,     /* eDMA Channel 6 DMA_INTL[INT6] */
    DMA0_CH7_IRQ60,     /* eDMA Channel 7 DMA_INTL[INT7] */
    DMA0_CH8_IRQ61,     /* eDMA Channel 8 DMA_INTL[INT8] */
    DMA0_CH9_IRQ62,     /* eDMA Channel 9 DMA_INTL[INT9] */
    DMA0_CH10_IRQ63,    /* eDMA Channel 10 DMA_INTL[INT10] */
    DMA0_CH11_IRQ64,    /* eDMA Channel 11 DMA_INTL[INT11] */
    DMA0_CH12_IRQ65,    /* eDMA Channel 12 DMA_INTL[INT12] */
    DMA0_CH13_IRQ66,    /* eDMA Channel 13 DMA_INTL[INT13] */
    DMA0_CH14_IRQ67,    /* eDMA Channel 14 DMA_INTL[INT14] */
    DMA0_CH15_IRQ68,    /* eDMA Channel 15 DMA_INTL[INT15] */
    DMA0_CH16_IRQ69,    /* eDMA Channel 16 DMA_INTL[INT16] */
    DMA0_CH17_IRQ70,    /* eDMA Channel 17 DMA_INTL[INT17] */
    DMA0_CH18_IRQ71,    /* eDMA Channel 18 DMA_INTL[INT18] */
    DMA0_CH19_IRQ72,    /* eDMA Channel 19 DMA_INTL[INT19] */
    DMA0_CH20_IRQ73,    /* eDMA Channel 20 DMA_INTL[INT20] */
    DMA0_CH21_IRQ74,    /* eDMA Channel 21 DMA_INTL[INT21] */
    DMA0_CH22_IRQ75,    /* eDMA Channel 22 DMA_INTL[INT22] */
    DMA0_CH23_IRQ76,    /* eDMA Channel 23 DMA_INTL[INT23] */
    DMA0_CH24_IRQ77,    /* eDMA Channel 24 DMA_INTL[INT24] */
    DMA0_CH25_IRQ78,    /* eDMA Channel 25 DMA_INTL[INT25] */
    DMA0_CH26_IRQ79,    /* eDMA Channel 26 DMA_INTL[INT26] */
    DMA0_CH27_IRQ80,    /* eDMA Channel 27 DMA_INTL[INT27] */
    DMA0_CH28_IRQ81,    /* eDMA Channel 28 DMA_INTL[INT28] */
    DMA0_CH29_IRQ82,    /* eDMA Channel 29 DMA_INTL[INT29] */
    DMA0_CH30_IRQ83,    /* eDMA Channel 30 DMA_INTL[INT30] */
    DMA0_CH31_IRQ84,    /* eDMA Channel 31 DMA_INTL[INT31] */
    DMA0_CH32_IRQ85,    /* eDMA Channel 32 DMA_INTH[INT32] */
    DMA0_CH33_IRQ86,    /* eDMA Channel 33 DMA_INTH[INT33] */
    DMA0_CH34_IRQ87,    /* eDMA Channel 34 DMA_INTH[INT34] */
    DMA0_CH35_IRQ88,    /* eDMA Channel 35 DMA_INTH[INT35] */
    DMA0_CH36_IRQ89,    /* eDMA Channel 36 DMA_INTH[INT36] */
    DMA0_CH37_IRQ90,    /* eDMA Channel 37 DMA_INTH[INT37] */
    DMA0_CH38_IRQ91,    /* eDMA Channel 38 DMA_INTH[INT38] */
    DMA0_CH39_IRQ92,    /* eDMA Channel 39 DMA_INTH[INT39] */
    DMA0_CH40_IRQ93,    /* eDMA Channel 40 DMA_INTH[INT40] */
    DMA0_CH41_IRQ94,    /* eDMA Channel 41 DMA_INTH[INT41] */
    DMA0_CH42_IRQ95,    /* eDMA Channel 42 DMA_INTH[INT42] */
    DMA0_CH43_IRQ96,    /* eDMA Channel 43 DMA_INTH[INT43] */
    DMA0_CH44_IRQ97,    /* eDMA Channel 44 DMA_INTH[INT44] */
    DMA0_CH45_IRQ98,    /* eDMA Channel 45 DMA_INTH[INT45] */
    DMA0_CH46_IRQ99,    /* eDMA Channel 46 DMA_INTH[INT46] */
    DMA0_CH47_IRQ100,   /* eDMA Channel 47 DMA_INTH[INT47] */
    DMA0_CH48_IRQ101,   /* eDMA Channel 48 DMA_INTH[INT48] */
    DMA0_CH49_IRQ102,   /* eDMA Channel 49 DMA_INTH[INT49] */
    DMA0_CH50_IRQ103,   /* eDMA Channel 50 DMA_INTH[INT50] */
    DMA0_CH51_IRQ104,   /* eDMA Channel 51 DMA_INTH[INT51] */
    DMA0_CH52_IRQ105,   /* eDMA Channel 52 DMA_INTH[INT52] */
    DMA0_CH53_IRQ106,   /* eDMA Channel 53 DMA_INTH[INT53] */
    DMA0_CH54_IRQ107,   /* eDMA Channel 54 DMA_INTH[INT54] */
    DMA0_CH55_IRQ108,   /* eDMA Channel 55 DMA_INTH[INT55] */
    DMA0_CH56_IRQ109,   /* eDMA Channel 56 DMA_INTH[INT56] */
    DMA0_CH57_IRQ110,   /* eDMA Channel 57 DMA_INTH[INT57] */
    DMA0_CH58_IRQ111,   /* eDMA Channel 58 DMA_INTH[INT58] */
    DMA0_CH59_IRQ112,   /* eDMA Channel 59 DMA_INTH[INT59] */
    DMA0_CH60_IRQ113,   /* eDMA Channel 60 DMA_INTH[INT60] */
    DMA0_CH61_IRQ114,   /* eDMA Channel 61 DMA_INTH[INT61] */
    DMA0_CH62_IRQ115,   /* eDMA Channel 62 DMA_INTH[INT62] */
    DMA0_CH63_IRQ116,   /* eDMA Channel 63 DMA_INTH[INT63] */
    DMA1_CH0_IRQ117,    /* eDMA Channel 64 DMA_INTH[INT64] */
    DMA1_CH1_IRQ118,    /* eDMA Channel 65 DMA_INTH[INT65] */
    DMA1_CH2_IRQ119,    /* eDMA Channel 66 DMA_INTH[INT66] */
    DMA1_CH3_IRQ120,    /* eDMA Channel 67 DMA_INTH[INT67] */
    DMA1_CH4_IRQ121,    /* eDMA Channel 68 DMA_INTH[INT68] */
    DMA1_CH5_IRQ122,    /* eDMA Channel 69 DMA_INTH[INT69] */
    DMA1_CH6_IRQ123,    /* eDMA Channel 70 DMA_INTH[INT70] */
    DMA1_CH7_IRQ124,    /* eDMA Channel 71 DMA_INTH[INT71] */
    DMA1_CH8_IRQ125,    /* eDMA Channel 72 DMA_INTH[INT72] */
    DMA1_CH9_IRQ126,    /* eDMA Channel 73 DMA_INTH[INT73] */
    DMA1_CH10_IRQ127,   /* eDMA Channel 74 DMA_INTH[INT74] */
    DMA1_CH11_IRQ128,   /* eDMA Channel 75 DMA_INTH[INT75] */
    DMA1_CH12_IRQ129,   /* eDMA Channel 76 DMA_INTH[INT76] */
    DMA1_CH13_IRQ130,   /* eDMA Channel 77 DMA_INTH[INT77] */
    DMA1_CH14_IRQ131,   /* eDMA Channel 78 DMA_INTH[INT78] */
    DMA1_CH15_IRQ132,   /* eDMA Channel 79 DMA_INTH[INT79] */
    DMA1_CH16_IRQ133,   /* eDMA Channel 80 DMA_INTH[INT80] */
    DMA1_CH17_IRQ134,   /* eDMA Channel 81 DMA_INTH[INT81] */
    DMA1_CH18_IRQ135,   /* eDMA Channel 82 DMA_INTH[INT82] */
    DMA1_CH19_IRQ136,   /* eDMA Channel 83 DMA_INTH[INT83] */
    DMA1_CH20_IRQ137,   /* eDMA Channel 84 DMA_INTH[INT84] */
    DMA1_CH21_IRQ138,   /* eDMA Channel 85 DMA_INTH[INT85] */
    DMA1_CH22_IRQ139,   /* eDMA Channel 86 DMA_INTH[INT86] */
    DMA1_CH23_IRQ140,   /* eDMA Channel 87 DMA_INTH[INT87] */
    DMA1_CH24_IRQ141,   /* eDMA Channel 88 DMA_INTH[INT88] */
    DMA1_CH25_IRQ142,   /* eDMA Channel 89 DMA_INTH[INT89] */
    DMA1_CH26_IRQ143,   /* eDMA Channel 90 DMA_INTH[INT90] */
    DMA1_CH27_IRQ144,   /* eDMA Channel 91 DMA_INTH[INT91] */
    DMA1_CH28_IRQ145,   /* eDMA Channel 92 DMA_INTH[INT92] */
    DMA1_CH29_IRQ146,   /* eDMA Channel 93 DMA_INTH[INT93] */
    DMA1_CH30_IRQ147,   /* eDMA Channel 94 DMA_INTH[INT94] */
    DMA1_CH31_IRQ148,   /* eDMA Channel 95 DMA_INTH[INT95] */
    DMA1_CH32_IRQ149,   /* eDMA Channel 96 DMA_INTH[INT96] */
    DMA1_CH33_IRQ150,   /* eDMA Channel 97 DMA_INTH[INT97] */
    DMA1_CH34_IRQ151,   /* eDMA Channel 98 DMA_INTH[INT98] */
    DMA1_CH35_IRQ152,   /* eDMA Channel 99 DMA_INTH[INT99] */
    DMA1_CH36_IRQ153,   /* eDMA Channel 100 DMA_INTH[INT100] */
    DMA1_CH37_IRQ154,   /* eDMA Channel 101 DMA_INTH[INT101] */
    DMA1_CH38_IRQ155,   /* eDMA Channel 102 DMA_INTH[INT102] */
    DMA1_CH39_IRQ156,   /* eDMA Channel 103 DMA_INTH[INT103] */
    DMA1_CH40_IRQ157,   /* eDMA Channel 104 DMA_INTH[INT104] */
    DMA1_CH41_IRQ158,   /* eDMA Channel 105 DMA_INTH[INT105] */
    DMA1_CH42_IRQ159,   /* eDMA Channel 106 DMA_INTH[INT106] */
    DMA1_CH43_IRQ160,   /* eDMA Channel 107 DMA_INTH[INT107] */
    DMA1_CH44_IRQ161,   /* eDMA Channel 108 DMA_INTH[INT108] */
    DMA1_CH45_IRQ162,   /* eDMA Channel 109 DMA_INTH[INT109] */
    DMA1_CH46_IRQ163,   /* eDMA Channel 110 DMA_INTH[INT110] */
    DMA1_CH47_IRQ164,   /* eDMA Channel 111 DMA_INTH[INT111] */
    DMA1_CH48_IRQ165,   /* eDMA Channel 112 DMA_INTH[INT112] */
    DMA1_CH49_IRQ166,   /* eDMA Channel 113 DMA_INTH[INT113] */
    DMA1_CH50_IRQ167,   /* eDMA Channel 114 DMA_INTH[INT114] */
    DMA1_CH51_IRQ168,   /* eDMA Channel 115 DMA_INTH[INT115] */
    DMA1_CH52_IRQ169,   /* eDMA Channel 116 DMA_INTH[INT116] */
    DMA1_CH53_IRQ170,   /* eDMA Channel 117 DMA_INTH[INT117] */
    DMA1_CH54_IRQ171,   /* eDMA Channel 118 DMA_INTH[INT118] */
    DMA1_CH55_IRQ172,   /* eDMA Channel 119 DMA_INTH[INT119] */
    DMA1_CH56_IRQ173,   /* eDMA Channel 120 DMA_INTH[INT120] */
    DMA1_CH57_IRQ174,   /* eDMA Channel 121 DMA_INTH[INT121] */
    DMA1_CH58_IRQ175,   /* eDMA Channel 122 DMA_INTH[INT122] */
    DMA1_CH59_IRQ176,   /* eDMA Channel 123 DMA_INTH[INT123] */
    DMA1_CH60_IRQ177,   /* eDMA Channel 124 DMA_INTH[INT124] */
    DMA1_CH61_IRQ178,   /* eDMA Channel 125 DMA_INTH[INT125] */
    DMA1_CH62_IRQ179,   /* eDMA Channel 126 DMA_INTH[INT126] */
    DMA1_CH63_IRQ180,   /* eDMA Channel 127 DMA_INTH[INT127] */
    INTR_ID_181,
    INTR_ID_182,
    INTR_ID_183,
    INTR_ID_184,
    INTR_ID_185, /* Flash controller Prog/Erase/Suspend IRQ_0 MCR[DONE] */
    INTR_ID_186,
    INTR_ID_187,
    INTR_ID_188,
    INTR_ID_189,
    INTR_ID_190,
    INTR_ID_191,
    INTR_ID_192,
    INTR_ID_193,
    INTR_ID_194,
    INTR_ID_195,
    INTR_ID_196,
    INTR_ID_197,
    INTR_ID_198,
    INTR_ID_199,
    INTR_ID_200,
    INTR_ID_201,
    INTR_ID_202,
    INTR_ID_203,
    INTR_ID_204,
    INTR_ID_205,
    INTR_ID_206,
    INTR_ID_207,
    INTR_ID_208,
    INTR_ID_209,
    INTR_ID_210,
    INTR_ID_211,
    INTR_ID_212,
    INTR_ID_213,
    INTR_ID_214,
    INTR_ID_215,
    INTR_ID_216,
    INTR_ID_217,
    INTR_ID_218, /* Ethernet_0_0 EIR[TXF] */
    INTR_ID_219, /* Ethernet_0_1 EIR[RXF] */
    INTR_ID_220, /* Ethernet_0_2 EIR[HBERR] EIR[BABR] EIR[BABT] EIR[GRA] */
    INTR_ID_221,
    INTR_ID_222,
    INTR_ID_223,
    INTR_ID_224,
    INTR_ID_225,
    INTR_ID_226, /* Periodic Interrupt Timer (PIT0) PIT_0_TFLG0[TIF] */
    INTR_ID_227, /* Periodic Interrupt Timer (PIT1) PIT_0_TFLG1[TIF] */
    INTR_ID_228, /* Periodic Interrupt Timer (PIT2) PIT_0_TFLG2[TIF] */
    INTR_ID_229, /* Periodic Interrupt Timer (PIT3) PIT_0_TFLG3[TIF] */
    INTR_ID_230, /* Periodic Interrupt Timer (PIT4) PIT_0_TFLG4[TIF] */
    INTR_ID_231, /* Periodic Interrupt Timer (PIT5) PIT_0_TFLG5[TIF] */
    INTR_ID_232, /* Periodic Interrupt Timer (PIT6) PIT_0_TFLG6[TIF] */
    INTR_ID_233, /* Periodic Interrupt Timer (PIT7) PIT_0_TFLG7[TIF] */
    INTR_ID_234,
    INTR_ID_235,
    INTR_ID_236,
    INTR_ID_237,
    INTR_ID_238,
    INTR_ID_239, /* PIT_RTI PIT_0_RTI_TFLG[TIF] */
    INTR_ID_240, /* PIT_64_Upper PIT_1_TFLG0[TIF] */
    INTR_ID_241, /* PIT_64_Lower PIT_1_TFLG1[TIF] */
    INTR_ID_242, /* XOSC counter XOSC */
    INTR_ID_243, /* SIU External Interrupt_0 SIU External Interrupt_0 */
    INTR_ID_244, /* SIU External Interrupt_1 SIU External Interrupt_1 */
    INTR_ID_245,
    INTR_ID_246,
    INTR_ID_247,
    INTR_ID_248,
    INTR_ID_249,
    INTR_ID_250,
    INTR_ID_251, /* MC_ME 0 ME_IS[I_SAFE] */
    INTR_ID_252, /* MC_ME 1 ME_IS[I_MTC] */
    INTR_ID_253, /* MC_ME 2 ME_IS[I_IMODE] */
    INTR_ID_254, /* MC_ME 3 ME_IS[I_ICONF] */
    INTR_ID_255, /* MC_RGM 0 MC_RGM Functional and destructive reset alternate event interrupt */
    INTR_ID_256,
    INTR_ID_257,
    INTR_ID_258,
    INTR_ID_259, /* DSPI0_0 DSPI_0_SR[TFUF] | DSPI_0_SR[RFOF] | DSPI_0_SR[TFIWF] */
    INTR_ID_260, /* DSPI0_1 DSPI_0_SR[EOQF] */
    INTR_ID_261, /* DSPI0_2 DSPI_0_SR[TFFF] */
    INTR_ID_262, /* DSPI0_3 DSPI_0_SR[TCF] */
    INTR_ID_263, /* DSPI0_4 DDSPI_0_SR[RFDF] */
    INTR_ID_264,
    INTR_ID_265,
    INTR_ID_266, /* DSPI0_7 DSPI_0_SR[SPEF] */
    INTR_ID_267,
    INTR_ID_268, /* DSPI1_0 DSPI_1_SR[TFUF] | DSPI_1_SR[RFOF] | */
    INTR_ID_269, /* DSPI1_1 DSPI_1_SR[EOQF] */
    INTR_ID_270, /* DSPI1_2 DSPI_1_SR[TFFF] */
    INTR_ID_271, /* DSPI1_3 DSPI_1_SR[TCF] */
    INTR_ID_272, /* DSPI1_4 DSPI_1_SR[RFDF] */
    INTR_ID_273,
    INTR_ID_274,
    INTR_ID_275, /* DSPI1_7 DSPI_1_SR[SPEF] */
    INTR_ID_276,
    INTR_ID_277, /* DSPI2_0 DSPI_2_SR[TFUF] | DSPI_2_SR[RFOF]| */
    INTR_ID_278, /* DSPI2_1 DSPI_2_SR[EOQF] */
    INTR_ID_279, /* DSPI2_2 DSPI_2_SR[TFFF] */
    INTR_ID_280, /* DSPI2_3 DSPI_2_SR[TCF] */
    INTR_ID_281, /* DSPI2_4 DSPI_2_SR[RFDF] */
    INTR_ID_282,
    INTR_ID_283,
    INTR_ID_284, /* DSPI2_7 DSPI_2_SR[SPEF] */
    INTR_ID_285,
    INTR_ID_286, /* DSPI3_0 DSPI_3_SR[TFUF] | DSPI_3_SR[RFOF]| */
    INTR_ID_287, /* DSPI3_1 DSPI_3_SR[EOQF] */
    INTR_ID_288, /* DSPI3_2 DSPI_3_SR[TFFF] */
    INTR_ID_289, /* DSPI3_3 DSPI_3_SR[TCF] */
    INTR_ID_290, /* DSPI3_4 DSPI_3_SR[RFDF] */
    INTR_ID_291,
    INTR_ID_292,
    INTR_ID_293, /* DSPI3_7 DSPI_3_SR[SPEF] */
    INTR_ID_294,
    INTR_ID_295, /* DSPI4_0 DSPI_4_SR[TFUF] | DSPI_4_SR[RFOF]| */
    INTR_ID_296, /* DSPI4_1 DSPI_4_SR[EOQF] */
    INTR_ID_297, /* DSPI4_2 DSPI_4_SR[TFFF] */
    INTR_ID_298, /* DSPI4_3 DSPI_4_SR[TCF] */
    INTR_ID_299, /* DSPI4_4 DSPI_4_SR[RFDF] */
    INTR_ID_300, /* DSPI4_5 DSPI_4_SR[SPITCF] | */
    INTR_ID_301, /* DSPI4_6 DSPI_4_SR[DSITCF] | */
    INTR_ID_302, /* DSPI4_7 DSPI_4_SR[SPEF] | DSPI_4_SR[DPEF] */
    INTR_ID_303, /* DSPI4_8 DSPI_4_SR[DDIF] */
    INTR_ID_304, /* DSPI5_0 DSPI_5_SR[TFUF] | DSPI_5_SR[RFOF]| */
    INTR_ID_305, /* DSPI5_1 DSPI_5_SR[EOQF] */
    INTR_ID_306, /* DSPI5_2 DSPI_5_SR[TFFF] */
    INTR_ID_307, /* DSPI5_3 DSPI_5_SR[TCF] */
    INTR_ID_308, /* DSPI5_4 DSPI_5_SR[RFDF] */
    INTR_ID_309, /* DSPI5_5 DSPI_5_SR[SPITCF] | DSPI_5_SR[CMD_TCF] */
    INTR_ID_310, /* DSPI5_6 DSPI_5_SR[DSITCF] | DSPI_5_SR[CMDFFF] */
    INTR_ID_311, /* DSPI5_7 DSPI_5_SR[SPEF] | DSPI_5_SR[DPEF] */
    INTR_ID_312, /* DSPI5_8 DSPI_5_SR[DDIF] */
    INTR_ID_313, /* DSPI6_0 DSPI_6_SR[TFUF] | DSPI_6_SR[RFOF]| */
    INTR_ID_314, /* DSPI6_1 DSPI_6_SR[EOQF] */
    INTR_ID_315, /* DSPI6_2 DSPI_6_SR[TFFF] */
    INTR_ID_316, /* DSPI6_3 DSPI_6_SR[TCF] */
    INTR_ID_317, /* DSPI6_4 DSPI_6_SR[RFDF] */
    INTR_ID_318, /* DSPI6_5 DSPI_6_SR[SPITCF] | DSPI_6_SR[CMD_TCF] */
    INTR_ID_319, /* DSPI6_6 DSPI_6_SR[DSITCF] | DSPI_6_SR[CMDFFF] */
    INTR_ID_320, /* DSPI6_7 DSPI_6_SR[SPEF] | DSPI_6_SR[DPEF] */
    INTR_ID_321, /* DSPI6_8 DSPI_6_SR[DDIF] */
    INTR_ID_322,
    INTR_ID_323,
    INTR_ID_324,
    INTR_ID_325,
    INTR_ID_326,
    INTR_ID_327,
    INTR_ID_328,
    INTR_ID_329,
    INTR_ID_330,
    INTR_ID_331,
    INTR_ID_332,
    INTR_ID_333,
    INTR_ID_334,
    INTR_ID_335,
    INTR_ID_336,
    INTR_ID_337,
    INTR_ID_338,
    INTR_ID_339,
    INTR_ID_340,
    INTR_ID_341,
    INTR_ID_342,
    INTR_ID_343,
    INTR_ID_344,
    INTR_ID_345,
    INTR_ID_346,
    INTR_ID_347,
    INTR_ID_348,
    INTR_ID_349,
    INTR_ID_350,
    INTR_ID_351,
    INTR_ID_352,
    INTR_ID_353,
    INTR_ID_354,
    INTR_ID_355,
    INTR_ID_356,
    INTR_ID_357,
    INTR_ID_358,
    INTR_ID_359,
    INTR_ID_360,
    INTR_ID_361,
    INTR_ID_362,
    INTR_ID_363,
    INTR_ID_364,
    INTR_ID_365,
    INTR_ID_366,
    INTR_ID_367, /* DSPI12_0 DSPI_12_SR[TFUF] | DSPI_12_SR[RFOF]| */
    INTR_ID_368, /* DSPI12_1 DSPI_12_SR[EOQF] */
    INTR_ID_369, /* DSPI12_2 DSPI_12_SR[TFFF] */
    INTR_ID_370, /* DSPI12_3 DSPI_12_SR[TCF] */
    INTR_ID_371, /* DSPI12_4 DSPI_12_SR[RFDF] */
    INTR_ID_372,
    INTR_ID_373,
    INTR_ID_374, /* DSPI12_7 DSPI_12_SR[SPEF] */
    INTR_ID_375,
    INTR_ID_376, /* Linflex/eSCI0_0 LINFlex_0_RXI */
    INTR_ID_377, /* Linflex/eSCI0_1 LINFlex_0_TXI */
    INTR_ID_378, /* Linflex/eSCI0_2 LINFlex_0_ERR */
    INTR_ID_379,
    INTR_ID_380, /* Linflex/eSCI1_0 LINFlex_1_RXI */
    INTR_ID_381, /* Linflex/eSCI1_1 LINFlex_1_TXI */
    INTR_ID_382, /* Linflex/eSCI1_2 LINFlex_1_ERR */
    INTR_ID_383,
    INTR_ID_384, /* Linflex/eSCI2_0 LINFlex_2_RXI */
    INTR_ID_385, /* Linflex/eSCI2_1 LINFlex_2_TXI */
    INTR_ID_386, /* Linflex/eSCI2_2 LINFlex_2_ERR */
    INTR_ID_387,
    INTR_ID_388,
    INTR_ID_389,
    INTR_ID_390,
    INTR_ID_391,
    INTR_ID_392,
    INTR_ID_393,
    INTR_ID_394,
    INTR_ID_395,
    INTR_ID_396,
    INTR_ID_397,
    INTR_ID_398,
    INTR_ID_399,
    INTR_ID_400,
    INTR_ID_401,
    INTR_ID_402,
    INTR_ID_403,
    INTR_ID_404,
    INTR_ID_405,
    INTR_ID_406,
    INTR_ID_407,
    INTR_ID_408,
    INTR_ID_409,
    INTR_ID_410,
    INTR_ID_411,
    INTR_ID_412,
    INTR_ID_413,
    INTR_ID_414,
    INTR_ID_415,
    INTR_ID_416, /* Linflex/eSCI16_0 LINFlex_16_RXI */
    INTR_ID_417, /* Linflex/eSCI16_1 LINFlex_16_TXI */
    INTR_ID_418, /* Linflex/eSCI16_2 LINFlex_16_ERR */
    INTR_ID_419,
    INTR_ID_420,
    INTR_ID_421,
    INTR_ID_422,
    INTR_ID_423,
    INTR_ID_424,
    INTR_ID_425,
    INTR_ID_426,
    INTR_ID_427,
    INTR_ID_428,
    INTR_ID_429,
    INTR_ID_430,
    INTR_ID_431,
    INTR_ID_432, /* Linflex/eSCI14_0 LINFlex_14_RXI */
    INTR_ID_433, /* Linflex/eSCI14_1 LINFlex_14_TXI */
    INTR_ID_434, /* Linflex/eSCI14_2 LINFlex_14_ERR */
    INTR_ID_435,
    INTR_ID_436, /* Linflex/eSCI15_0 LINFlex_15_RXI */
    INTR_ID_437, /* Linflex/eSCI15_1 LINFlex_15_TXI */
    INTR_ID_438, /* Linflex/eSCI15_2 LINFlex_15_ERR */
    INTR_ID_439,
    INTR_ID_440, /* IIC_0_0 I2C0_SR[IBAL] | I2C0_SR[TCF] | */
    INTR_ID_441,
    INTR_ID_442, /* IIC_1_0 I2C1_SR[IBAL] | I2C1_SR[TCF] | */
    INTR_ID_443,
    INTR_ID_444,
    MCAN9_0_IRQ445,
    MCAN9_1_IRQ446,
    MCAN10_0_IRQ447,
    MCAN10_1_IRQ448,
    MCAN11_0_IRQ449,
    MCAN11_1_IRQ450,
    MCAN12_0_IRQ451,
    MCAN12_1_IRQ452,
    FLEXRAY0_0_IRQ453, /* FlexRay_0_0 FR_0_LRNEIF | DRNEIF */
    FLEXRAY0_1_IRQ454, /* FlexRay_0_1 FR_0_LRCEIF | DRCEIF */
    FLEXRAY0_2_IRQ455, /* FlexRay_0_2 FR_0_FNEAIF */
    FLEXRAY0_3_IRQ456, /* FlexRay_0_3 FR_0_FNEBIF */
    FLEXRAY0_4_IRQ457, /* FlexRay_0_4 FR_0_WUPIF */
    FLEXRAY0_5_IRQ458, /* FlexRay_0_5 FR_0_PRIF */
    FLEXRAY0_6_IRQ459, /* FlexRay_0_6 FR_0_CHIF */
    FLEXRAY0_7_IRQ460, /* FlexRay_0_7 FR_0_TBIF */
    FLEXRAY0_8_IRQ461, /* FlexRay_0_8 FR_0_RBIF */
    FLEXRAY0_9_IRQ462, /* FlexRay_0_9 FR_0_MIF */
    FLEXRAY0_10_IRQ463, /* FlexRay_0_10 FR_0_STPCLK */
    INTR_ID_464,
    FLEXRAY1_0_IRQ465, /* FlexRay_1_0 FR_1_LRNEIF | DRNEIF */
    FLEXRAY1_1_IRQ466, /* FlexRay_1_1 FR_1_LRCEIF | DRCEIF */
    FLEXRAY1_2_IRQ467, /* FlexRay_1_2 FR_1_FNEAIF */
    FLEXRAY1_3_IRQ468, /* FlexRay_1_3 FR_1_FNEBIF */
    FLEXRAY1_4_IRQ469, /* FlexRay_1_4 FR_1_WUPIF */
    FLEXRAY1_5_IRQ470, /* FlexRay_1_5 FR_1_PRIF */
    FLEXRAY1_6_IRQ471, /* FlexRay_1_6 FR_1_CHIF */
    FLEXRAY1_7_IRQ472, /* FlexRay_1_7 FR_1_TBIF */
    FLEXRAY1_8_IRQ473, /* FlexRay_1_8 FR_1_RBIF */
    FLEXRAY1_9_IRQ474, /* FlexRay_1_9 FR_1_MIF */
    FLEXRAY1_10_IRQ475, /* FlexRay_1_10 FR_1_STPCLK */
    INTR_ID_476,
    INTR_ID_477, /* Power Monitor Unit GR_S[VD15] | GR_S[VD14] | GR_S[VD13] | */
    INTR_ID_478, /* Power management Unit (temp sensor) EPR_TD[TEMP_3] | EPR_TD[TEMP_2] | */
    INTR_ID_479,
    INTR_ID_480, /* PLL_0_0 PLL0SR[LOLF] */
    INTR_ID_481,
    INTR_ID_482, /* PLL_1_0 PLL1SR[LOLF] */
    INTR_ID_483,
    INTR_ID_484, /* PLL_0_1 PLL0SR[EXTPDF] */
    INTR_ID_485, /* PLL_1_1 PLL1SR[EXTPDF] */
    INTR_ID_486,
    INTR_ID_487,
    INTR_ID_488, /* FCCU_0 FCCU_IRQ_STAT[ALRM_STAT] */
    INTR_ID_489, /* FCCU_1 FCU_IRQ_STAT[CFG_TO_STAT] */
    INTR_ID_490, /* FCCU_2 FCCU_SCFS[RCCS0] */
    INTR_ID_491, /* FCCU_3 FCCU_SCFS[RCCS1] */
    INTR_ID_492,
    INTR_ID_493,
    INTR_ID_494, /* STCU2_0 STCU_RUNSW[LBIE] */
    INTR_ID_495, /* STCU2_1 STCU_RUNSW[MBIE] */
    INTR_ID_496, /* Hardware Security Module 0 HSM2HTIE[0] */
    INTR_ID_497, /* Hardware Security Module 1 HSM2HTIE[1] */
    INTR_ID_498, /* Hardware Security Module 2 HSM2HTIE[2] */
    INTR_ID_499, /* Hardware Security Module 3 HSM2HTIE[3] */
    INTR_ID_500, /* Hardware Security Module 4 HSM2HTIE[4] */
    INTR_ID_501, /* Hardware Security Module 5 HSM2HTIE[5] */
    INTR_ID_502, /* Hardware Security Module 6 HSM2HTIE[6] */
    INTR_ID_503, /* Hardware Security Module 7 HSM2HTIE[7] */
    INTR_ID_504, /* Hardware Security Module 8 HSM2HTIE[8] */
    INTR_ID_505, /* Hardware Security Module 9 HSM2HTIE[9] */
    INTR_ID_506, /* Hardware Security Module 10 HSM2HTIE[10] */
    INTR_ID_507, /* Hardware Security Module 11 HSM2HTIE[11] */
    INTR_ID_508, /* Hardware Security Module 12 HSM2HTIE[12] */
    INTR_ID_509, /* Hardware Security Module 13 HSM2HTIE[13] */
    INTR_ID_510, /* Hardware Security Module 14 HSM2HTIE[14] */
    INTR_ID_511, /* Hardware Security Module 15 HSM2HTIE[15] */
    INTR_ID_512, /* Hardware Security Module 16 HSM2HTIE[16] */
    INTR_ID_513, /* Hardware Security Module 17 HSM2HTIE[17] */
    INTR_ID_514, /* Hardware Security Module 18 HSM2HTIE[18] */
    INTR_ID_515, /* Hardware Security Module 19 HSM2HTIE[19] */
    INTR_ID_516, /* Hardware Security Module 20 HSM2HTIE[20] */
    INTR_ID_517, /* Hardware Security Module 21 HSM2HTIE[21] */
    INTR_ID_518, /* Hardware Security Module 22 HSM2HTIE[22] */
    INTR_ID_519, /* Hardware Security Module 23 HSM2HTIE[23] */
    INTR_ID_520, /* Hardware Security Module 24 HSM2HTIE[24] */
    INTR_ID_521, /* Hardware Security Module 25 HSM2HTIE[25] */
    INTR_ID_522, /* Hardware Security Module 26 HSM2HTIE[26] */
    INTR_ID_523, /* Hardware Security Module 27 HSM2HTIE[27] */
    INTR_ID_524, /* Hardware Security Module 28 HSM2HTIE[28] */
    INTR_ID_525, /* Hardware Security Module 29 HSM2HTIE[29] */
    INTR_ID_526, /* Hardware Security Module 30 HSM2HTIE[30] */
    INTR_ID_527, /* Hardware Security Module 31 HSM2HTIE[31] */
    INTR_ID_528, /* SAR_ADC0 SAR_ADC0 */
    EQADC01_FISR_TORF_RFOF_CFUF, /* EQADC01_FISR_TORF_RFOF_CFUF */
    INTR_ID_530, /* SAR_ADC2 SAR_ADC2 */
	EQADC23_FISR_TORF_RFOF_CFUF, /* EQADC23_FISR_TORF_RFOF_CFUF */
    INTR_ID_532, /* SAR_ADC4 SAR_ADC4 */
	EQADC45_FISR_TORF_RFOF_CFUF, /* EQADC45_FISR_TORF_RFOF_CFUF */
    INTR_ID_534, /* SAR_ADC6 SAR_ADC6 */
	EQADC67_FISR_TORF_RFOF_CFUF, /* EQADC67_FISR_TORF_RFOF_CFUF */
    INTR_ID_536, /* SAR_ADC8 SAR_ADC8 */
	EQADC89_FISR_TORF_RFOF_CFUF, /* EQADC89_FISR_TORF_RFOF_CFUF */
    INTR_ID_538, /* SAR_ADC10 SAR_ADC10 */
    INTR_ID_539, /* SAR_ADC11 SAR_ADC11 */
    INTR_ID_540,
    INTR_ID_541,
    INTR_ID_542,
    INTR_ID_543, /* SAR_ADCB SAR_ADCB */
    INTR_ID_544, /* SD_ADC0 SD_ADC0 */
    INTR_ID_545, /* SD_ADC1 SD_ADC1 */
    INTR_ID_546, /* SD_ADC2 SD_ADC2 */
    INTR_ID_547, /* SD_ADC3 SD_ADC3 */
    INTR_ID_548, /* SD_ADC4 SD_ADC4 */
    INTR_ID_549, /* SD_ADC5 SD_ADC5 */
    INTR_ID_550, /* SD_ADC6 SD_ADC6 */
    INTR_ID_551, /* SD_ADC7 SD_ADC7 */
    INTR_ID_552, /* SD_ADC8 SD_ADC8 */
    INTR_ID_553, /* SD_ADC9 SD_ADC9 */
    INTR_ID_554,
    INTR_ID_555,
    INTR_ID_556,
    INTR_ID_557,
    INTR_ID_558, /* SENT_COMBINED_FAST_0 SENT_0_FMSG_RDY[0] | */
    INTR_ID_559, /* SENT_COMBINED_SLOW_0 SENT_0_SMSG_RDY[0] | */
    INTR_ID_560, /* SENT_COMBINED_ERR_0 SENT_0_GBL_STATUS[FMDU] | */
    INTR_ID_561, /* SENT_COMBINED_FAST_1 SENT_1_FMSG_RDY[0] | */
    INTR_ID_562, /* SENT_COMBINED_SLOW_1 SENT_1_SMSG_RDY[0] | */
    INTR_ID_563, /* SENT_COMBINED_ERR_1 SENT_1_GBL_STATUS[FMDU] | */
    SENT0_CH0_FAST_IRQ564,  /* SENT_0_CH0_FAST, SENT_0_FMSG_RDY[0] */
    SENT0_CH0_SLOW_IRQ565,  /* SENT_0_CH0_SLOW, SENT_0_SMSG_RDY[0] */
    SENT0_CH0_ERR_IRQ566,   /* SENT_0_CH0_ERR,  SENT_0_CH0_STATUS[4:7] | */
    SENT0_CH1_FAST_IRQ567,  /* SENT_0_CH1_FAST, SENT_0_FMSG_RDY[1] */
    SENT0_CH1_SLOW_IRQ568,  /* SENT_0_CH1_SLOW, SENT_0_SMSG_RDY[1] */
    SENT0_CH1_ERR_IRQ569,   /* SENT_0_CH1_ERR,  SENT_0_CH1_STATUS[4:7] | */
    SENT0_CH2_FAST_IRQ570,  /* SENT_0_CH2_FAST, SENT_0_FMSG_RDY[2] */
    SENT0_CH2_SLOW_IRQ571,  /* SENT_0_CH2_SLOW, SENT_0_SMSG_RDY[2] */
    SENT0_CH2_ERR_IRQ572,   /* SENT_0_CH2_ERR,  SENT_0_CH2_STATUS[4:7] | */
    SENT0_CH3_FAST_IRQ573,  /* SENT_0_CH3_FAST, SENT_0_FMSG_RDY[3] */
    SENT0_CH3_SLOW_IRQ574,  /* SENT_0_CH3_SLOW, SENT_0_SMSG_RDY[3] */
    SENT0_CH3_ERR_IRQ575,   /* SENT_0_CH3_ERR,  SENT_0_CH3_STATUS[4:7] | */
    SENT0_CH4_FAST_IRQ576,  /* SENT_0_CH4_FAST, SENT_0_FMSG_RDY[4] */
    SENT0_CH4_SLOW_IRQ577,  /* SENT_0_CH4_SLOW, SENT_0_SMSG_RDY[4] */
    SENT0_CH4_ERR_IRQ578,   /* SENT_0_CH4_ERR,  SENT_0_CH4_STATUS[4:7] | */
    SENT1_CH0_FAST_IRQ579,  /* SENT_1_CH0_FAST, SENT_1_FMSG_RDY[0] */
    SENT1_CH0_SLOW_IRQ580,  /* SENT_1_CH0_SLOW, SENT_1_SMSG_RDY[0] */
    SENT1_CH0_ERR_IRQ581,   /* SENT_1_CH0_ERR,  SENT_1_CH0_STATUS[4:7] | */
    SENT1_CH1_FAST_IRQ582,  /* SENT_1_CH1_FAST, SENT_1_FMSG_RDY[1] */
    SENT1_CH1_SLOW_IRQ583,  /* SENT_1_CH1_SLOW, SENT_1_SMSG_RDY[1] */
    SENT1_CH1_ERR_IRQ584,   /* SENT_1_CH1_ERR,  SENT_1_CH1_STATUS[4:7] | */
    SENT1_CH2_FAST_IRQ585,  /* SENT_1_CH2_FAST, SENT_1_FMSG_RDY[2] */
    SENT1_CH2_SLOW_IRQ586,  /* SENT_1_CH2_SLOW, SENT_1_SMSG_RDY[2] */
    SENT1_CH2_ERR_IRQ587,   /* SENT_1_CH2_ERR,  SENT_1_CH3_STATUS[4:7] | */
    SENT1_CH3_FAST_IRQ588,  /* SENT_1_CH3_FAST, SENT_1_FMSG_RDY[3] */
    SENT1_CH3_SLOW_IRQ589,  /* SENT_1_CH3_SLOW, SENT_1_SMSG_RDY[3] */
    SENT1_CH3_ERR_IRQ590,   /* SENT_1_CH3_ERR,  SENT_1_CH3_STATUS[4:7] | */
    SENT1_CH4_FAST_IRQ591,  /* SENT_1_CH4_FAST, SENT_1_FMSG_RDY[4] */
    SENT1_CH4_SLOW_IRQ592,  /* SENT_1_CH4_SLOW, SENT_1_SMSG_RDY[4] */
    SENT1_CH4_ERR_IRQ593,   /* SENT_1_CH4_ERR,  SENT_1_CH4_STATUS[4:7] | */
    SENT0_CH5_FAST_IRQ594,  /* SENT_0_CH5_FAST, SENT_0_FMSG_RDY[5] */
    SENT0_CH5_SLOW_IRQ595,  /* SENT_0_CH5_SLOW, SENT_0_SMSG_RDY[5] */
    SENT0_CH5_ERR_IRQ596,   /* SENT_0_CH5_ERR,  SENT_0_CH5_STATUS[4:7] | */
    SENT0_CH6_FAST_IRQ597,  /* SENT_0_CH6_FAST, SENT_0_FMSG_RDY[6] */
    SENT0_CH6_SLOW_IRQ598,  /* SENT_0_CH6_SLOW, SENT_0_SMSG_RDY[6] */
    SENT0_CH6_ERR_IRQ599,   /* SENT_0_CH6_ERR,  SENT_0_CH6_STATUS[4:7] | */
    SENT0_CH7_FAST_IRQ600,  /* SENT_0_CH7_FAST, SENT_0_FMSG_RDY[7] */
    SENT0_CH7_SLOW_IRQ601,  /* SENT_0_CH7_SLOW, SENT_0_SMSG_RDY[7] */
    SENT0_CH7_ERR_IRQ602,   /* SENT_0_CH7_ERR,  SENT_0_CH7_STATUS[4:7] | */
    SENT1_CH5_FAST_IRQ603,  /* SENT_1_CH5_FAST, SENT_1_FMSG_RDY[5] */
    SENT1_CH5_SLOW_IRQ604,  /* SENT_1_CH5_SLOW, SENT_1_SMSG_RDY[5] */
    SENT1_CH5_ERR_IRQ605,   /* SENT_1_CH5_ERR,  SENT_1_CH5_STATUS[4:7] | */
    SENT1_CH6_FAST_IRQ606,  /* SENT_1_CH6_FAST, SENT_1_FMSG_RDY[6] */
    SENT1_CH6_SLOW_IRQ607,  /* SENT_1_CH6_SLOW, SENT_1_SMSG_RDY[6] */
    SENT1_CH6_ERR_IRQ608,   /* SENT_1_CH6_ERR,  SENT_1_CH6_STATUS[4:7] | */
    INTR_ID_609,
    INTR_ID_610,
    INTR_ID_611,
    INTR_ID_612, /* PSI5_0_CH0_0 PSI5_0_CH_0_DSR[IS_DMA_TF_PM_DS] | PSI5_0_CH_0_DSR[IS_DMA_TF_SF] | */
    INTR_ID_613, /* PSI5_0_CH0_1 PSI5_0_CH_0_GISR[IS_CESM[6:1]] | */
    INTR_ID_614, /* PSI5_0_CH0_2 PSI5_0_CH_0_NDSR[NDS31] | */
    INTR_ID_615, /* PSI5_0_CH0_3 PSI5_0_CH_0_OWSR[NDS31] | */
    INTR_ID_616, /* PSI5_0_CH0_4 PSI5_0_CH_0_EISR[NDS31] | */
    INTR_ID_617, /* PSI5_0_CH0_5 PSI5_0_CH_0_DSR[*] | */
    INTR_ID_618, /* PSI5_0_CH1_0 PSI5_0_CH_1_DSR[IS_DMA_TF_PM_DS] | PSI5_0_CH_1_DSR[IS_DMA_TF_SF] | */
    INTR_ID_619, /* PSI5_0_CH1_1 PSI5_0_CH_1_GISR[IS_CESM[6:1]] | */
    INTR_ID_620, /* PSI5_0_CH1_2 PSI5_0_CH_1_NDSR[NDS31] | */
    INTR_ID_621, /* PSI5_0_CH1_3 PSI5_0_CH_1_OWSR[NDS31] | */
    INTR_ID_622, /* PSI5_0_CH1_4 PSI5_0_CH_1_EISR[NDS31] | */
    INTR_ID_623, /* PSI5_0_CH1_5 PSI5_0_CH_1_DSR[*] | */
    INTR_ID_624, /* PSI5_1_CH0_0 PSI5_1_CH_0_DSR[IS_DMA_TF_PM_DS] | PSI5_1_CH_0_DSR[IS_DMA_TF_SF] | */
    INTR_ID_625, /* PSI5_1_CH0_1 PSI5_1_CH_0_GISR[IS_CESM[6:1]] | */
    INTR_ID_626, /* PSI5_1_CH0_2 PSI5_1_CH_0_NDSR[NDS31] | */
    INTR_ID_627, /* PSI5_1_CH0_3 PSI5_1_CH_0_OWSR[NDS31] | */
    INTR_ID_628, /* PSI5_1_CH0_4 PSI5_1_CH_0_EISR[NDS31] | */
    INTR_ID_629, /* PSI5_1_CH0_5 PSI5_1_CH_0_DSR[*] | */
    INTR_ID_630, /* PSI5_0_CH2_0 PSI5_0_CH_2_DSR[IS_DMA_TF_PM_DS] | PSI5_0_CH_2_DSR[IS_DMA_TF_SF] | */
    INTR_ID_631, /* PSI5_0_CH2_1 PSI5_0_CH_2_GISR[IS_CESM[6:1]] | */
    INTR_ID_632, /* PSI5_0_CH2_2 PSI5_0_CH_2_NDSR[NDS31] | */
    INTR_ID_633, /* PSI5_0_CH2_3 PSI5_0_CH_2_OWSR[NDS31] | */
    INTR_ID_634, /* PSI5_0_CH2_4 PSI5_0_CH_2_EISR[NDS31] | */
    INTR_ID_635, /* PSI5_0_CH2_5 PSI5_0_CH_2_DSR[*] | */
    INTR_ID_636, /* PSI5_1_CH1_0 PSI5_1_CH_1_DSR[IS_DMA_TF_PM_DS] | PSI5_1_CH_1_DSR[IS_DMA_TF_SF] | */
    INTR_ID_637, /* PSI5_1_CH1_1 PSI5_1_CH_1_GISR[IS_CESM[6:1]] | */
    INTR_ID_638, /* PSI5_1_CH1_2 PSI5_1_CH_1_NDSR[NDS31] | */
    INTR_ID_639, /* PSI5_1_CH1_3 PSI5_1_CH_1_OWSR[NDS31] | */
    INTR_ID_640, /* PSI5_1_CH1_4 PSI5_1_CH_1_EISR[NDS31] | */
    INTR_ID_641, /* PSI5_1_CH1_5 PSI5_1_CH_1_DSR[*] | */
    INTR_ID_642,
    INTR_ID_643,
    INTR_ID_644,
    INTR_ID_645,
    INTR_ID_646,
    INTR_ID_647,
    INTR_ID_648,
    INTR_ID_649,
    INTR_ID_650,
    INTR_ID_651,
    INTR_ID_652,
    INTR_ID_653,
    INTR_ID_654, /* SIPI_0 SIPI_ERR[TOEn] | SIPI_ERR[TIDEn] | */
    INTR_ID_655, /* SIPI_1 SIPI_SR[GCRCE) */
    INTR_ID_656, /* SIPI_2 SIPI_CSR0[RAR] | SIPI_CSR0[ACKR] */
    INTR_ID_657, /* SIPI_3 SIPI_CSR1[RAR] | SIPI_CSR1[ACKR] */
    INTR_ID_658, /* SIPI_4 SIPI_CSR2[RAR] | SIPI_CSR2[ACKR] */
    INTR_ID_659, /* SIPI_5 SIPI_CSR3[RAR] | SIPI_CSR3[ACKR] */
    INTR_ID_660, /* SIPI_6 SIPI_SR[TE0] | SIPI_SR[TE1] | */
    INTR_ID_661, /* LFAST0_0 LFAST_0_TISR[TXPNGF] | */
    INTR_ID_662, /* LFAST0_1 LFAST_0_TISR[TXIEF] | */
    INTR_ID_663, /* LFAST0_2 LFAST_0_RISR[RXCTSF] | */
    INTR_ID_664, /* LFAST0_3 LFAST_0_RISR[RXUOF] | */
    INTR_ID_665, /* LFAST0_4 LFAST_0_RIISR[ICPFF] | */
    INTR_ID_666,
    INTR_ID_667,
    INTR_ID_668,
    INTR_ID_669,
    INTR_ID_670,
    INTR_ID_671,
    INTR_ID_672,
    INTR_ID_673,
    INTR_ID_674, /* JTAGM JTAGM_SR[SPU_INT] | JTAGM_SR[Idle] */
    INTR_ID_675, /* JDC JDC_MSR[JIN_INT] | */
    INTR_ID_676,
    INTR_ID_677, /* M_TTCAN0_0 M_TTCAN_0 interrupt line0 */
    INTR_ID_678, /* M_TTCAN0_1 M_TTCAN_0 interrupt line1 */
    INTR_ID_679, /* M_TTCAN0_2 M_TTCAN_0 Register Time Mark interrupt */
    INTR_ID_680,
    INTR_ID_681,
    INTR_ID_682,
    INTR_ID_683,
    INTR_ID_684,
    INTR_ID_685,
    INTR_ID_686,
    INTR_ID_687,
    MCAN1_0_IRQ688, /* M_CAN1_0 m_can1_int0 */
    MCAN1_1_IRQ689, /* M_CAN1_1 m_can1_int1 */
    MCAN2_0_IRQ690, /* M_CAN2_0 m_can2_int0 */
    MCAN2_1_IRQ691, /* M_CAN2_1 m_can2_int1 */
    MCAN3_0_IRQ692, /* M_CAN3_0 m_can3_int0 */
    MCAN3_1_IRQ693, /* M_CAN3_1 m_can3_int1 */
    MCAN4_0_IRQ694, /* M_CAN4_0 m_can4_int0 */
    MCAN4_1_IRQ695, /* M_CAN4_1 m_can4_int1 */
    MCAN5_0_IRQ696,
    MCAN5_1_IRQ697,
    MCAN6_0_IRQ698,
    MCAN6_1_IRQ699,
    MCAN7_0_IRQ700,
    MCAN7_1_IRQ701,
    MCAN8_0_IRQ702,
    MCAN8_1_IRQ703,
    INTR_ID_704,
    INTR_ID_705,
    INTR_ID_706, /* GTM_AEI_IRQ AEI gtm_icm.gtm_aei_irq aei */
    INTR_ID_707, /* GTM_ARU_IRQ[0] gtm_icm.gtm_aru_irq[0] */
    INTR_ID_708, /* GTM_ARU_IRQ[1] gtm_icm.gtm_aru_irq[1] */
    INTR_ID_709, /* GTM_ARU_IRQ[2] gtm_icm.gtm_aru_irq[2] */
    INTR_ID_710, /* GTM_BRC_IRQ gtm_icm.gtm_brc_irq */
    INTR_ID_711, /* GTM_CMP_IRQ gtm_icm.gtm_cmp_irq */
    INTR_ID_712, /* GTM_SPE0_IRQ gtm_icm.gtm_spe0_irq */
    INTR_ID_713, /* GTM_SPE1_IRQ gtm_icm.gtm_spe1_irq */
    INTR_ID_714, /* GTM_PSM0_IRQ[0] gtm_icm.gtm_psm0_irq[0] */
    INTR_ID_715, /* GTM_PSM0_IRQ[1] gtm_icm.gtm_psm0_irq[1] */
    INTR_ID_716, /* GTM_PSM0_IRQ[2] gtm_icm.gtm_psm0_irq[2] */
    INTR_ID_717, /* GTM_PSM0_IRQ[3] gtm_icm.gtm_psm0_irq[3] */
    INTR_ID_718, /* GTM_PSM0_IRQ[4] gtm_icm.gtm_psm0_irq[4] */
    INTR_ID_719, /* GTM_PSM0_IRQ[5] gtm_icm.gtm_psm0_irq[5] */
    INTR_ID_720, /* GTM_PSM0_IRQ[6] gtm_icm.gtm_psm0_irq[6] */
    INTR_ID_721, /* GTM_PSM0_IRQ[7] gtm_icm.gtm_psm0_irq[7] */
    INTR_ID_722, /* GTM_DPLL_IRQ[0] gtm_icm.gtm_dpll_irq[0] */
    INTR_ID_723, /* GTM_DPLL_IRQ[1] gtm_icm.gtm_dpll_irq[1] */
    INTR_ID_724, /* GTM_DPLL_IRQ[2] gtm_icm.gtm_dpll_irq[2] */
    INTR_ID_725, /* GTM_DPLL_IRQ[3] gtm_icm.gtm_dpll_irq[3] */
    INTR_ID_726, /* GTM_DPLL_IRQ[4] gtm_icm.gtm_dpll_irq[4] */
    INTR_ID_727, /* GTM_DPLL_IRQ[5] gtm_icm.gtm_dpll_irq[5] */
    INTR_ID_728, /* GTM_DPLL_IRQ[6] gtm_icm.gtm_dpll_irq[6] */
    INTR_ID_729, /* GTM_DPLL_IRQ[7] gtm_icm.gtm_dpll_irq[7] */
    INTR_ID_730, /* GTM_DPLL_IRQ[8] gtm_icm.gtm_dpll_irq[8] */
    INTR_ID_731, /* GTM_DPLL_IRQ[9] gtm_icm.gtm_dpll_irq[9] */
    INTR_ID_732, /* GTM_DPLL_IRQ[10] gtm_icm.gtm_dpll_irq[10] */
    INTR_ID_733, /* GTM_DPLL_IRQ[11] gtm_icm.gtm_dpll_irq[11] */
    INTR_ID_734, /* GTM_DPLL_IRQ[12] gtm_icm.gtm_dpll_irq[12] */
    INTR_ID_735, /* GTM_DPLL_IRQ[13] gtm_icm.gtm_dpll_irq[13] */
    INTR_ID_736, /* GTM_DPLL_IRQ[14] gtm_icm.gtm_dpll_irq[14] */
    INTR_ID_737, /* GTM_DPLL_IRQ[15] gtm_icm.gtm_dpll_irq[15] */
    INTR_ID_738, /* GTM_DPLL_IRQ[16] gtm_icm.gtm_dpll_irq[16] */
    INTR_ID_739, /* GTM_DPLL_IRQ[17] gtm_icm.gtm_dpll_irq[17] */
    INTR_ID_740, /* GTM_DPLL_IRQ[18] gtm_icm.gtm_dpll_irq[18] */
    INTR_ID_741, /* GTM_DPLL_IRQ[19] gtm_icm.gtm_dpll_irq[19] */
    INTR_ID_742, /* GTM_DPLL_IRQ[20] gtm_icm.gtm_dpll_irq[20] */
    INTR_ID_743, /* GTM_DPLL_IRQ[21] gtm_icm.gtm_dpll_irq[21] */
    INTR_ID_744, /* GTM_DPLL_IRQ[22] gtm_icm.gtm_dpll_irq[22] */
    INTR_ID_745, /* GTM_DPLL_IRQ[23] gtm_icm.gtm_dpll_irq[23] */
    INTR_ID_746, /* GTM_DPLL_IRQ[24] gtm_icm.gtm_dpll_irq[24] */
    INTR_ID_747, /* GTM_DPLL_IRQ[25] gtm_icm.gtm_dpll_irq[25] */
    INTR_ID_748, /* GTM_DPLL_IRQ[26] gtm_icm.gtm_dpll_irq[26] */
    INTR_ID_749, /* GTM_TIM0_IRQ[0] gtm_icm.gtm_tim0_irq[0] */
    INTR_ID_750, /* GTM_TIM0_IRQ[1] gtm_icm.gtm_tim0_irq[1] */
    INTR_ID_751, /* GTM_TIM0_IRQ[2] gtm_icm.gtm_tim0_irq[2] */
    INTR_ID_752, /* GTM_TIM0_IRQ[3] gtm_icm.gtm_tim0_irq[3] */
    INTR_ID_753, /* GTM_TIM0_IRQ[4] gtm_icm.gtm_tim0_irq[4] */
    INTR_ID_754, /* GTM_TIM0_IRQ[5] gtm_icm.gtm_tim0_irq[5] */
    INTR_ID_755, /* GTM_TIM0_IRQ[6] gtm_icm.gtm_tim0_irq[6] */
    INTR_ID_756, /* GTM_TIM0_IRQ[7] gtm_icm.gtm_tim0_irq[7] */
    INTR_ID_757, /* GTM_TIM1_IRQ[0] gtm_icm.gtm_tim1_irq[0] */
    INTR_ID_758, /* GTM_TIM1_IRQ[1] gtm_icm.gtm_tim1_irq[1] */
    INTR_ID_759, /* GTM_TIM1_IRQ[2] gtm_icm.gtm_tim1_irq[2] */
    INTR_ID_760, /* GTM_TIM1_IRQ[3] gtm_icm.gtm_tim1_irq[3] */
    INTR_ID_761, /* GTM_TIM1_IRQ[4] gtm_icm.gtm_tim1_irq[4] */
    INTR_ID_762, /* GTM_TIM1_IRQ[5] gtm_icm.gtm_tim1_irq[5] */
    INTR_ID_763, /* GTM_TIM1_IRQ[6] gtm_icm.gtm_tim1_irq[6] */
    INTR_ID_764, /* GTM_TIM1_IRQ[7] gtm_icm.gtm_tim1_irq[7] */
    INTR_ID_765, /* GTM_TIM2_IRQ[0] gtm_icm.gtm_tim2_irq[0] */
    INTR_ID_766, /* GTM_TIM2_IRQ[1] gtm_icm.gtm_tim2_irq[1] */
    INTR_ID_767, /* GTM_TIM2_IRQ[2] gtm_icm.gtm_tim2_irq[2] */
    INTR_ID_768, /* GTM_TIM2_IRQ[3] gtm_icm.gtm_tim2_irq[3] */
    INTR_ID_769, /* GTM_TIM2_IRQ[4] gtm_icm.gtm_tim2_irq[4] */
    INTR_ID_770, /* GTM_TIM2_IRQ[5] gtm_icm.gtm_tim2_irq[5] */
    INTR_ID_771, /* GTM_TIM2_IRQ[6] gtm_icm.gtm_tim2_irq[6] */
    INTR_ID_772, /* GTM_TIM2_IRQ[7] gtm_icm.gtm_tim2_irq[7] */
    INTR_ID_773, /* GTM_TIM3_IRQ[0] gtm_icm.gtm_tim3_irq[0] */
    INTR_ID_774, /* GTM_TIM3_IRQ[1] gtm_icm.gtm_tim3_irq[1] */
    INTR_ID_775, /* GTM_TIM3_IRQ[2] gtm_icm.gtm_tim3_irq[2] */
    INTR_ID_776, /* GTM_TIM3_IRQ[3] gtm_icm.gtm_tim3_irq[3] */
    INTR_ID_777, /* GTM_TIM3_IRQ[4] gtm_icm.gtm_tim3_irq[4] */
    INTR_ID_778, /* GTM_TIM3_IRQ[5] gtm_icm.gtm_tim3_irq[5] */
    INTR_ID_779, /* GTM_TIM3_IRQ[6] gtm_icm.gtm_tim3_irq[6] */
    INTR_ID_780, /* GTM_TIM3_IRQ[7] gtm_icm.gtm_tim3_irq[7] */
    INTR_ID_781, /* GTM_MCS0_IRQ[0] gtm_icm.gtm_mcs0_irq[0] */
    INTR_ID_782, /* GTM_MCS0_IRQ[1] gtm_icm.gtm_mcs0_irq[1] */
    INTR_ID_783, /* GTM_MCS0_IRQ[2] gtm_icm.gtm_mcs0_irq[2] */
    INTR_ID_784, /* GTM_MCS0_IRQ[3] gtm_icm.gtm_mcs0_irq[3] */
    INTR_ID_785, /* GTM_MCS0_IRQ[4] gtm_icm.gtm_mcs0_irq[4] */
    INTR_ID_786, /* GTM_MCS0_IRQ[5] gtm_icm.gtm_mcs0_irq[5] */
    INTR_ID_787, /* GTM_MCS0_IRQ[6] gtm_icm.gtm_mcs0_irq[6] */
    INTR_ID_788, /* GTM_MCS0_IRQ[7] gtm_icm.gtm_mcs0_irq[7] */
    INTR_ID_789, /* GTM_MCS1_IRQ[0] gtm_icm.gtm_mcs1_irq[0] */
    INTR_ID_790, /* GTM_MCS1_IRQ[1] gtm_icm.gtm_mcs1_irq[1] */
    INTR_ID_791, /* GTM_MCS1_IRQ[2] gtm_icm.gtm_mcs1_irq[2] */
    INTR_ID_792, /* GTM_MCS1_IRQ[3] gtm_icm.gtm_mcs1_irq[3] */
    INTR_ID_793, /* GTM_MCS1_IRQ[4] gtm_icm.gtm_mcs1_irq[4] */
    INTR_ID_794, /* GTM_MCS1_IRQ[5] gtm_icm.gtm_mcs1_irq[5] */
    INTR_ID_795, /* GTM_MCS1_IRQ[6] gtm_icm.gtm_mcs1_irq[6] */
    INTR_ID_796, /* GTM_MCS1_IRQ[7] gtm_icm.gtm_mcs1_irq[7] */
    INTR_ID_797, /* GTM_MCS2_IRQ[0] gtm_icm.gtm_mcs2_irq[0] */
    INTR_ID_798, /* GTM_MCS2_IRQ[1] gtm_icm.gtm_mcs2_irq[1] */
    INTR_ID_799, /* GTM_MCS2_IRQ[2] gtm_icm.gtm_mcs2_irq[2] */
    INTR_ID_800, /* GTM_MCS2_IRQ[3] gtm_icm.gtm_mcs2_irq[3] */
    INTR_ID_801, /* GTM_MCS2_IRQ[4] gtm_icm.gtm_mcs2_irq[4] */
    INTR_ID_802, /* GTM_MCS2_IRQ[5] gtm_icm.gtm_mcs2_irq[5] */
    INTR_ID_803, /* GTM_MCS2_IRQ[6] gtm_icm.gtm_mcs2_irq[6] */
    INTR_ID_804, /* GTM_MCS2_IRQ[7] gtm_icm.gtm_mcs2_irq[7] */
    INTR_ID_805, /* GTM_MCS3_IRQ[0] gtm_icm.gtm_mcs3_irq[0] */
    INTR_ID_806, /* GTM_MCS3_IRQ[1] gtm_icm.gtm_mcs3_irq[1] */
    INTR_ID_807, /* GTM_MCS3_IRQ[2] gtm_icm.gtm_mcs3_irq[2] */
    INTR_ID_808, /* GTM_MCS3_IRQ[3] gtm_icm.gtm_mcs3_irq[3] */
    INTR_ID_809, /* GTM_MCS3_IRQ[4] gtm_icm.gtm_mcs3_irq[4] */
    INTR_ID_810, /* GTM_MCS3_IRQ[5] gtm_icm.gtm_mcs3_irq[5] */
    INTR_ID_811, /* GTM_MCS3_IRQ[6] gtm_icm.gtm_mcs3_irq[6] */
    INTR_ID_812, /* GTM_MCS3_IRQ[7] gtm_icm.gtm_mcs3_irq[7] */
    INTR_ID_813, /* GTM_TOM0_IRQ[0] gtm_icm.gtm_tom0_irq[0] */
    INTR_ID_814, /* GTM_TOM0_IRQ[1] gtm_icm.gtm_tom0_irq[1] */
    INTR_ID_815, /* GTM_TOM0_IRQ[2] gtm_icm.gtm_tom0_irq[2] */
    INTR_ID_816, /* GTM_TOM0_IRQ[3] gtm_icm.gtm_tom0_irq[3] */
    INTR_ID_817, /* GTM_TOM0_IRQ[4] gtm_icm.gtm_tom0_irq[4] */
    INTR_ID_818, /* GTM_TOM0_IRQ[5] gtm_icm.gtm_tom0_irq[5] */
    INTR_ID_819, /* GTM_TOM0_IRQ[6] gtm_icm.gtm_tom0_irq[6] */
    INTR_ID_820, /* GTM_TOM0_IRQ[7] gtm_icm.gtm_tom0_irq[7] */
    INTR_ID_821, /* GTM_TOM1_IRQ[0] gtm_icm.gtm_tom1_irq[0] */
    INTR_ID_822, /* GTM_TOM1_IRQ[1] gtm_icm.gtm_tom1_irq[1] */
    INTR_ID_823, /* GTM_TOM1_IRQ[2] gtm_icm.gtm_tom1_irq[2] */
    INTR_ID_824, /* GTM_TOM1_IRQ[3] gtm_icm.gtm_tom1_irq[3] */
    INTR_ID_825, /* GTM_TOM1_IRQ[4] gtm_icm.gtm_tom1_irq[4] */
    INTR_ID_826, /* GTM_TOM1_IRQ[5] gtm_icm.gtm_tom1_irq[5] */
    INTR_ID_827, /* GTM_TOM1_IRQ[6] gtm_icm.gtm_tom1_irq[6] */
    INTR_ID_828, /* GTM_TOM1_IRQ[7] gtm_icm.gtm_tom1_irq[7] */
    INTR_ID_829, /* GTM_TOM2_IRQ[0] gtm_icm.gtm_tom2_irq[0] */
    INTR_ID_830, /* GTM_TOM2_IRQ[1] gtm_icm.gtm_tom2_irq[1] */
    INTR_ID_831, /* GTM_TOM2_IRQ[2] gtm_icm.gtm_tom2_irq[2] */
    INTR_ID_832, /* GTM_TOM2_IRQ[3] gtm_icm.gtm_tom2_irq[3] */
    INTR_ID_833, /* GTM_TOM2_IRQ[4] gtm_icm.gtm_tom2_irq[4] */
    INTR_ID_834, /* GTM_TOM2_IRQ[5] gtm_icm.gtm_tom2_irq[5] */
    INTR_ID_835, /* GTM_TOM2_IRQ[6] gtm_icm.gtm_tom2_irq[6] */
    INTR_ID_836, /* GTM_TOM2_IRQ[7] gtm_icm.gtm_tom2_irq[7] */
    INTR_ID_837, /* GTM_ATOM0_IRQ[0] gtm_icm.gtm_atom0_irq[0] */
    INTR_ID_838, /* GTM_ATOM0_IRQ[1] gtm_icm.gtm_atom0_irq[1] */
    INTR_ID_839, /* GTM_ATOM0_IRQ[2] gtm_icm.gtm_atom0_irq[2] */
    INTR_ID_840, /* GTM_ATOM0_IRQ[3] gtm_icm.gtm_atom0_irq[3] */
    INTR_ID_841, /* GTM_ATOM1_IRQ[0] gtm_icm.gtm_atom1_irq[0] */
    INTR_ID_842, /* GTM_ATOM1_IRQ[1] gtm_icm.gtm_atom1_irq[1] */
    INTR_ID_843, /* GTM_ATOM1_IRQ[2] gtm_icm.gtm_atom1_irq[2] */
    INTR_ID_844, /* GTM_ATOM1_IRQ[3] gtm_icm.gtm_atom1_irq[3] */
    INTR_ID_845, /* GTM_ATOM2_IRQ[0] gtm_icm.gtm_atom2_irq[0] */
    INTR_ID_846, /* GTM_ATOM2_IRQ[1] gtm_icm.gtm_atom2_irq[1] */
    INTR_ID_847, /* GTM_ATOM2_IRQ[2] gtm_icm.gtm_atom2_irq[2] */
    INTR_ID_848, /* GTM_ATOM2_IRQ[3] gtm_icm.gtm_atom2_irq[3] */
    INTR_ID_849, /* GTM_ATOM3_IRQ[0] gtm_icm.gtm_atom3_irq[0] */
    INTR_ID_850, /* GTM_ATOM3_IRQ[1] gtm_icm.gtm_atom3_irq[1] */
    INTR_ID_851, /* GTM_ATOM3_IRQ[2] gtm_icm.gtm_atom3_irq[2] */
    INTR_ID_852, /* GTM_ATOM3_IRQ[3] gtm_icm.gtm_atom3_irq[3] */
    INTR_ID_853, /* GTM_ATOM4_IRQ[0] gtm_icm.gtm_atom4_irq[0] */
    INTR_ID_854, /* GTM_ATOM4_IRQ[1] gtm_icm.gtm_atom4_irq[1] */
    INTR_ID_855, /* GTM_ATOM4_IRQ[2] gtm_icm.gtm_atom4_irq[2] */
    INTR_ID_856, /* GTM_ATOM4_IRQ[3] gtm_icm.gtm_atom4_irq[3] */
    INTR_ID_857, /* GTM_SPE2_IRQ gtm_icm.gtm_spe2_irq */
    INTR_ID_858, /* GTM_SPE3_IRQ gtm_icm.gtm_spe3_irq */
    INTR_ID_859, /* GTM_PSM1_IRQ[0] gtm_icm.gtm_psm1_irq[0] */
    INTR_ID_860, /* GTM_PSM1_IRQ[1] gtm_icm.gtm_psm1_irq[1] */
    INTR_ID_861, /* GTM_PSM1_IRQ[2] gtm_icm.gtm_psm1_irq[2] */
    INTR_ID_862, /* GTM_PSM1_IRQ[3] gtm_icm.gtm_psm1_irq[3] */
    INTR_ID_863, /* GTM_PSM1_IRQ[4] gtm_icm.gtm_psm1_irq[4] */
    INTR_ID_864, /* GTM_PSM1_IRQ[5] gtm_icm.gtm_psm1_irq[5] */
    INTR_ID_865, /* GTM_PSM1_IRQ[6] gtm_icm.gtm_psm1_irq[6] */
    INTR_ID_866, /* GTM_PSM1_IRQ[7] gtm_icm.gtm_psm1_irq[7] */
    INTR_ID_867, /* GTM_TIM4_IRQ[0] gtm_icm.gtm_tim4_irq[0] */
    INTR_ID_868, /* GTM_TIM4_IRQ[1] gtm_icm.gtm_tim4_irq[1] */
    INTR_ID_869, /* GTM_TIM4_IRQ[2] gtm_icm.gtm_tim4_irq[2] */
    INTR_ID_870, /* GTM_TIM4_IRQ[3] gtm_icm.gtm_tim4_irq[3] */
    INTR_ID_871, /* GTM_TIM4_IRQ[4] gtm_icm.gtm_tim4_irq[4] */
    INTR_ID_872, /* GTM_TIM4_IRQ[5] gtm_icm.gtm_tim4_irq[5] */
    INTR_ID_873, /* GTM_TIM4_IRQ[6] gtm_icm.gtm_tim4_irq[6] */
    INTR_ID_874, /* GTM_TIM4_IRQ[7] gtm_icm.gtm_tim4_irq[7] */
    INTR_ID_875, /* GTM_TIM5_IRQ[0] gtm_icm.gtm_tim5_irq[0] */
    INTR_ID_876, /* GTM_TIM5_IRQ[1] gtm_icm.gtm_tim5_irq[1] */
    INTR_ID_877, /* GTM_TIM5_IRQ[2] gtm_icm.gtm_tim5_irq[2] */
    INTR_ID_878, /* GTM_TIM5_IRQ[3] gtm_icm.gtm_tim5_irq[3] */
    INTR_ID_879, /* GTM_TIM5_IRQ[4] gtm_icm.gtm_tim5_irq[4] */
    INTR_ID_880, /* GTM_TIM5_IRQ[5] gtm_icm.gtm_tim5_irq[5] */
    INTR_ID_881, /* GTM_TIM5_IRQ[6] gtm_icm.gtm_tim5_irq[6] */
    INTR_ID_882, /* GTM_TIM5_IRQ[7] gtm_icm.gtm_tim5_irq[7] */
    INTR_ID_883, /* GTM_MCS4_IRQ[0] gtm_icm.gtm_mcs4_irq[0] */
    INTR_ID_884, /* GTM_MCS4_IRQ[1] gtm_icm.gtm_mcs4_irq[1] */
    INTR_ID_885, /* GTM_MCS4_IRQ[2] gtm_icm.gtm_mcs4_irq[2] */
    INTR_ID_886, /* GTM_MCS4_IRQ[3] gtm_icm.gtm_mcs4_irq[3] */
    INTR_ID_887, /* GTM_MCS4_IRQ[4] gtm_icm.gtm_mcs4_irq[4] */
    INTR_ID_888, /* GTM_MCS4_IRQ[5] gtm_icm.gtm_mcs4_irq[5] */
    INTR_ID_889, /* GTM_MCS4_IRQ[6] gtm_icm.gtm_mcs4_irq[6] */
    INTR_ID_890, /* GTM_MCS4_IRQ[7] gtm_icm.gtm_mcs4_irq[7] */
    INTR_ID_891, /* GTM_MCS5_IRQ[0] gtm_icm.gtm_mcs5_irq[0] */
    INTR_ID_892, /* GTM_MCS5_IRQ[1] gtm_icm.gtm_mcs5_irq[1] */
    INTR_ID_893, /* GTM_MCS5_IRQ[2] gtm_icm.gtm_mcs5_irq[2] */
    INTR_ID_894, /* GTM_MCS5_IRQ[3] gtm_icm.gtm_mcs5_irq[3] */
    INTR_ID_895, /* GTM_MCS5_IRQ[4] gtm_icm.gtm_mcs5_irq[4] */
    INTR_ID_896, /* GTM_MCS5_IRQ[5] gtm_icm.gtm_mcs5_irq[5] */
    INTR_ID_897, /* GTM_MCS5_IRQ[6] gtm_icm.gtm_mcs5_irq[6] */
    INTR_ID_898, /* GTM_MCS5_IRQ[7] gtm_icm.gtm_mcs5_irq[7] */
    INTR_ID_899, /* GTM_TOM3_IRQ[0] gtm_icm.gtm_tom3_irq[0] */
    INTR_ID_900, /* GTM_TOM3_IRQ[1] gtm_icm.gtm_tom3_irq[1] */
    INTR_ID_901, /* GTM_TOM3_IRQ[2] gtm_icm.gtm_tom3_irq[2] */
    INTR_ID_902, /* GTM_TOM3_IRQ[3] gtm_icm.gtm_tom3_irq[3] */
    INTR_ID_903, /* GTM_TOM3_IRQ[4] gtm_icm.gtm_tom3_irq[4] */
    INTR_ID_904, /* GTM_TOM3_IRQ[5] gtm_icm.gtm_tom3_irq[5] */
    INTR_ID_905, /* GTM_TOM3_IRQ[6] gtm_icm.gtm_tom3_irq[6] */
    INTR_ID_906, /* GTM_TOM3_IRQ[7] gtm_icm.gtm_tom3_irq[7] */
    INTR_ID_907, /* GTM_TOM4_IRQ[0] gtm_icm.gtm_tom4_irq[0] */
    INTR_ID_908, /* GTM_TOM4_IRQ[1] gtm_icm.gtm_tom4_irq[1] */
    INTR_ID_909, /* GTM_TOM4_IRQ[2] gtm_icm.gtm_tom4_irq[2] */
    INTR_ID_910, /* GTM_TOM4_IRQ[3] gtm_icm.gtm_tom4_irq[3] */
    INTR_ID_911, /* GTM_TOM4_IRQ[4] gtm_icm.gtm_tom4_irq[4] */
    INTR_ID_912, /* GTM_TOM4_IRQ[5] gtm_icm.gtm_tom4_irq[5] */
    INTR_ID_913, /* GTM_TOM4_IRQ[6] gtm_icm.gtm_tom4_irq[6] */
    INTR_ID_914, /* GTM_TOM4_IRQ[7] gtm_icm.gtm_tom4_irq[7] */
    INTR_ID_915, /* GTM_ATOM5_IRQ[0] gtm_icm.gtm_atom5_irq[0] */
    INTR_ID_916, /* GTM_ATOM5_IRQ[1] gtm_icm.gtm_atom5_irq[1] */
    INTR_ID_917, /* GTM_ATOM5_IRQ[2] gtm_icm.gtm_atom5_irq[2] */
    INTR_ID_918, /* GTM_ATOM5_IRQ[3] gtm_icm.gtm_atom5_irq[3] */
    INTR_ID_919, /* GTM_ATOM6_IRQ[0] gtm_icm.gtm_atom6_irq[0] */
    INTR_ID_920, /* GTM_ATOM6_IRQ[1] gtm_icm.gtm_atom6_irq[1] */
    INTR_ID_921, /* GTM_ATOM6_IRQ[2] gtm_icm.gtm_atom6_irq[2] */
    INTR_ID_922, /* GTM_ATOM6_IRQ[3] gtm_icm.gtm_atom6_irq[3] */
    INTR_ID_923, /* GTM_ATOM7_IRQ[0] gtm_icm.gtm_atom7_irq[0] */
    INTR_ID_924, /* GTM_ATOM7_IRQ[1] gtm_icm.gtm_atom7_irq[1] */
    INTR_ID_925, /* GTM_ATOM7_IRQ[2] gtm_icm.gtm_atom7_irq[2] */
    INTR_ID_926, /* GTM_ATOM7_IRQ[3] gtm_icm.gtm_atom7_irq[3] */
    INTR_ID_927, /* GTM_ATOM8_IRQ[0] gtm_icm.gtm_atom8_irq[0] */
    INTR_ID_928, /* GTM_ATOM8_IRQ[1] gtm_icm.gtm_atom8_irq[1] */
    INTR_ID_929, /* GTM_ATOM8_IRQ[2] gtm_icm.gtm_atom8_irq[2] */
    INTR_ID_930, /* GTM_ATOM8_IRQ[3] gtm_icm.gtm_atom8_irq[3] */
    INTR_ID_931, /* GTM_ERR_IRQ gtm_err_irq */
    INTR_ID_932,
    INTR_ID_933,
    INTR_ID_934,
    INTR_ID_935,
    INTR_ID_936,
    INTR_ID_937,
    INTR_ID_938,
    INTR_ID_939,
    INTR_ID_940,
    INTR_ID_941,
    INTR_ID_942,
    INTR_ID_943,
    INTR_ID_944,
    INTR_ID_945,
    INTR_ID_946, /* PS_SR_IRQ[0] PS_MBOX_SR_IRQ[0] */
    INTR_ID_947, /* PS_SR_IRQ[1] PS_MBOX_SR_IRQ[1] */
    INTR_ID_948, /* PS_SR_IRQ[2] PS_MBOX_SR_IRQ[2] */
    INTR_ID_949, /* PS_SR_IRQ[3] PS_MBOX_SR_IRQ[3] */
    INTR_ID_950, /* PS_SR_IRQ[4] PS_MBOX_SR_IRQ[4] */
    INTR_ID_951, /* PS_SR_IRQ[5] PS_MBOX_SR_IRQ[5] */
    INTR_ID_952, /* PS_SR_IRQ[6] PS_MBOX_SR_IRQ[6] */
    INTR_ID_953, /* PS_SR_IRQ[7] PS_MBOX_SR_IRQ[7] */
    INTR_ID_954, /* PSI5_E2SSR[1] PSI5_E2SSR[1] */
    INTR_ID_955, /* PSI5_E2SSR[2] PSI5_E2SSR[2] */
    INTR_ID_956, /* PSI5_E2SSR[3] PSI5_E2SSR[3] */
    INTR_ID_957, /* PSI5_E2SSR[4] PSI5_E2SSR[4] */
    INTR_ID_958, /* PSI5_E2SSR[5] PSI5_E2SSR[5] */
    INTR_ID_959, /* PSI5_E2SSR[6] PSI5_E2SSR[6] */
    INTR_ID_960, /* PSI5_E2SSR[7] PSI5_E2SSR[7] */
    INTR_ID_961, /* PS_GLSR PS_GLSR */
    INTR_ID_962,
    INTR_ID_963,
    INTR_ID_964,
    EQADC0_ADC01_GRP0_IRQ965,
    EQADC0_ADC01_GRP1_IRQ966,
    EQADC0_ADC01_GRP2_IRQ967,
    EQADC0_ADC01_GRP3_IRQ968,
    EQADC0_ADC01_GRP4_IRQ969,
    EQADC0_ADC01_GRP5_IRQ970,
    EQADC1_ADC23_GRP0_IRQ971,
    EQADC1_ADC23_GRP1_IRQ972,
    EQADC1_ADC23_GRP2_IRQ973,
    EQADC1_ADC23_GRP3_IRQ974,
    EQADC1_ADC23_GRP4_IRQ975,
    EQADC1_ADC23_GRP5_IRQ976,
    EQADC2_ADC45_GRP0_IRQ977,
    EQADC2_ADC45_GRP1_IRQ978,
    EQADC2_ADC45_GRP2_IRQ979,
    EQADC2_ADC45_GRP3_IRQ980,
    EQADC2_ADC45_GRP4_IRQ981,
    EQADC2_ADC45_GRP5_IRQ982,
    EQADC3_ADC67_GRP0_IRQ983,
    EQADC3_ADC67_GRP1_IRQ984,
    EQADC3_ADC67_GRP2_IRQ985,
    EQADC3_ADC67_GRP3_IRQ986,
    EQADC3_ADC67_GRP4_IRQ987,
    EQADC3_ADC67_GRP5_IRQ988,
    EQADC4_ADC89_GRP0_IRQ989,
    EQADC4_ADC89_GRP1_IRQ990,
    EQADC4_ADC89_GRP2_IRQ991,
    EQADC4_ADC89_GRP3_IRQ992,
    EQADC4_ADC89_GRP4_IRQ993,
    EQADC4_ADC89_GRP5_IRQ994,
    EMIOS0_CH3_IRQ995,
    EMIOS0_CH4_IRQ996,
    EMIOS0_CH5_IRQ997,
    EMIOS0_CH6_IRQ998,
    EMIOS0_CH7_IRQ999,
    EMIOS0_CH8_IRQ1000,
    EMIOS0_CH9_IRQ1001,
    EMIOS0_CH10_IRQ1002,
    EMIOS0_CH11_IRQ1003,
    EMIOS0_CH12_IRQ1004,
    EMIOS0_CH13_IRQ1005,
    EMIOS0_CH14_IRQ1006,
    EMIOS0_CH15_IRQ1007,
    EMIOS0_CH16_IRQ1008,
    EMIOS0_CH17_IRQ1009,
    EMIOS0_CH18_IRQ1010,
    EMIOS0_CH19_IRQ1011,
    EMIOS0_CH20_IRQ1012,
    EMIOS0_CH21_IRQ1013,
    EMIOS0_CH22_IRQ1014,
    EMIOS0_CH23_IRQ1015,
    EMIOS0_CH24_IRQ1016,
    EMIOS0_CH25_IRQ1017,
    EMIOS0_CH26_IRQ1018,
    EMIOS0_CH27_IRQ1019,
    EMIOS0_CH28_IRQ1020,
    EMIOS0_CH29_IRQ1021,
    EMIOS0_CH30_IRQ1022,/*PRQA S 0391*/
    EMIOS0_CH31_IRQ1023,
    INTR_ID_BUTT
} IntrId;

/* DSPI module features */
/* On this platform DSPI in extended mode is supported */
#define FEATURE_DSPI_HAS_EXTENDED_MODE 0U

#define DSPI0_EOQF_IRQn INTR_ID_260
#define DSPI1_EOQF_IRQn INTR_ID_269
#define DSPI2_EOQF_IRQn INTR_ID_278
#define DSPI3_EOQF_IRQn INTR_ID_287
#define DSPI4_EOQF_IRQn INTR_ID_296
#define DSPI5_EOQF_IRQn INTR_ID_305
#define DSPI6_EOQF_IRQn INTR_ID_314
#define DSPI12_EOQF_IRQn INTR_ID_368

#define DSPI0_TFFF_IRQn INTR_ID_261
#define DSPI1_TFFF_IRQn INTR_ID_270
#define DSPI2_TFFF_IRQn INTR_ID_279
#define DSPI3_TFFF_IRQn INTR_ID_288
#define DSPI4_TFFF_IRQn INTR_ID_297
#define DSPI5_TFFF_IRQn INTR_ID_306
#define DSPI6_TFFF_IRQn INTR_ID_315
#define DSPI12_TFFF_IRQn INTR_ID_369

#define DSPI0_RFDF_IRQn INTR_ID_263
#define DSPI1_RFDF_IRQn INTR_ID_272
#define DSPI2_RFDF_IRQn INTR_ID_281
#define DSPI3_RFDF_IRQn INTR_ID_290
#define DSPI4_RFDF_IRQn INTR_ID_299
#define DSPI5_RFDF_IRQn INTR_ID_308
#define DSPI6_RFDF_IRQn INTR_ID_317
#define DSPI12_RFDF_IRQn INTR_ID_371

#define DSPI0_ERR_IRQn INTR_ID_259
#define DSPI1_ERR_IRQn INTR_ID_268
#define DSPI2_ERR_IRQn INTR_ID_277
#define DSPI3_ERR_IRQn INTR_ID_286
#define DSPI4_ERR_IRQn INTR_ID_295
#define DSPI5_ERR_IRQn INTR_ID_304
#define DSPI6_ERR_IRQn INTR_ID_313
#define DSPI12_ERR_IRQn INTR_ID_367

/* Define interrupt vector for dspi */
#define FEATURES_DSPI_EOQ_INTERUPT_VECTOR    { DSPI0_EOQF_IRQn, DSPI1_EOQF_IRQn, DSPI2_EOQF_IRQn, DSPI3_EOQF_IRQn,\
                                                 DSPI4_EOQF_IRQn, DSPI5_EOQF_IRQn, DSPI6_EOQF_IRQn,DSPI12_EOQF_IRQn}

#define FEATURES_DSPI_SEND_INTERUPT_VECTOR    { DSPI0_TFFF_IRQn, DSPI1_TFFF_IRQn, DSPI2_TFFF_IRQn, DSPI3_TFFF_IRQn,\
                                                 DSPI4_TFFF_IRQn, DSPI5_TFFF_IRQn, DSPI6_TFFF_IRQn,DSPI12_TFFF_IRQn}

#define FEATURES_DSPI_RECEIVE_INTERUPT_VECTOR { DSPI0_RFDF_IRQn, DSPI1_RFDF_IRQn, DSPI2_RFDF_IRQn, DSPI3_RFDF_IRQn, \
                                                DSPI4_RFDF_IRQn, DSPI5_RFDF_IRQn, DSPI6_RFDF_IRQn,DSPI12_RFDF_IRQn}

#define FEATURES_DSPI_FAULT_INTERUPT_VECTOR   { DSPI0_ERR_IRQn, DSPI1_ERR_IRQn, DSPI2_ERR_IRQn,DSPI3_ERR_IRQn, \
                                                 DSPI4_ERR_IRQn, DSPI5_ERR_IRQn, DSPI6_ERR_IRQn, DSPI12_ERR_IRQn}

#define LINFLEXD0_RX_IRQn  INTR_ID_376
#define LINFLEXD0_TX_IRQn  INTR_ID_377
#define LINFLEXD0_ERR_IRQn INTR_ID_378

#define LINFLEXD1_RX_IRQn  INTR_ID_380
#define LINFLEXD1_TX_IRQn  INTR_ID_381
#define LINFLEXD1_ERR_IRQn INTR_ID_382

#define LINFLEXD2_RX_IRQn  INTR_ID_384
#define LINFLEXD2_TX_IRQn  INTR_ID_385
#define LINFLEXD2_ERR_IRQn INTR_ID_386

#define LINFLEXD3_RX_IRQn  INTR_ID_479
#define LINFLEXD3_TX_IRQn  INTR_ID_480
#define LINFLEXD3_ERR_IRQn INTR_ID_481

#define LINFLEXD4_RX_IRQn  INTR_ID_482
#define LINFLEXD4_TX_IRQn  INTR_ID_483
#define LINFLEXD4_ERR_IRQn INTR_ID_484

#define LINFLEXD5_RX_IRQn  INTR_ID_485
#define LINFLEXD5_TX_IRQn  INTR_ID_486
#define LINFLEXD5_ERR_IRQn INTR_ID_487

#define LINFLEXD6_RX_IRQn  INTR_ID_435
#define LINFLEXD6_TX_IRQn  INTR_ID_439
#define LINFLEXD6_ERR_IRQn INTR_ID_492

#define LINFLEXD7_RX_IRQn  INTR_ID_539
#define LINFLEXD7_TX_IRQn  INTR_ID_540
#define LINFLEXD7_ERR_IRQn INTR_ID_541

#define LINFLEXD8_RX_IRQn  INTR_ID_554
#define LINFLEXD8_TX_IRQn  INTR_ID_555
#define LINFLEXD8_ERR_IRQn INTR_ID_556

#define LINFLEXD9_RX_IRQn  INTR_ID_609
#define LINFLEXD9_TX_IRQn  INTR_ID_610
#define LINFLEXD9_ERR_IRQn INTR_ID_611

#define LINFLEXD10_RX_IRQn  INTR_ID_642
#define LINFLEXD10_TX_IRQn  INTR_ID_643
#define LINFLEXD10_ERR_IRQn INTR_ID_644

#define LINFLEXD11_RX_IRQn  INTR_ID_645
#define LINFLEXD11_TX_IRQn  INTR_ID_646
#define LINFLEXD11_ERR_IRQn INTR_ID_647

#define LINFLEXD12_RX_IRQn  INTR_ID_493
#define LINFLEXD12_TX_IRQn  INTR_ID_542
#define LINFLEXD12_ERR_IRQn INTR_ID_557

#define LINFLEXD16_RX_IRQn  INTR_ID_416
#define LINFLEXD16_TX_IRQn  INTR_ID_417
#define LINFLEXD16_ERR_IRQn INTR_ID_418

#define LINFLEXD14_RX_IRQn  INTR_ID_432
#define LINFLEXD14_TX_IRQn  INTR_ID_433
#define LINFLEXD14_ERR_IRQn INTR_ID_434

#define LINFLEXD15_RX_IRQn  INTR_ID_436
#define LINFLEXD15_TX_IRQn  INTR_ID_437
#define LINFLEXD15_ERR_IRQn INTR_ID_438

/** Interrupt vectors for the LINFlexD */
#define LINFLEXD_RX_IRQS {LINFLEXD0_RX_IRQn, LINFLEXD1_RX_IRQn, LINFLEXD2_RX_IRQn, LINFLEXD3_RX_IRQn, LINFLEXD4_RX_IRQn, LINFLEXD5_RX_IRQn, \
		                  LINFLEXD6_RX_IRQn, LINFLEXD7_RX_IRQn, LINFLEXD8_RX_IRQn, LINFLEXD9_RX_IRQn, LINFLEXD10_RX_IRQn, LINFLEXD11_RX_IRQn, \
		                  LINFLEXD12_RX_IRQn, LINFLEXD14_RX_IRQn,LINFLEXD15_RX_IRQn, LINFLEXD16_RX_IRQn}

#define LINFLEXD_TX_IRQS {LINFLEXD0_TX_IRQn, LINFLEXD1_TX_IRQn, LINFLEXD2_TX_IRQn, LINFLEXD3_TX_IRQn, LINFLEXD4_TX_IRQn, LINFLEXD5_TX_IRQn, \
		                  LINFLEXD6_TX_IRQn, LINFLEXD7_TX_IRQn, LINFLEXD8_TX_IRQn, LINFLEXD9_TX_IRQn, LINFLEXD10_TX_IRQn, LINFLEXD11_TX_IRQn, \
		                  LINFLEXD12_TX_IRQn, LINFLEXD14_TX_IRQn,LINFLEXD15_TX_IRQn, LINFLEXD16_TX_IRQn}

#define LINFLEXD_ERR_IRQS {LINFLEXD0_ERR_IRQn, LINFLEXD1_ERR_IRQn, LINFLEXD2_ERR_IRQn, LINFLEXD3_ERR_IRQn, LINFLEXD4_ERR_IRQn, LINFLEXD5_ERR_IRQn, \
		                   LINFLEXD6_ERR_IRQn, LINFLEXD7_ERR_IRQn, LINFLEXD8_ERR_IRQn, LINFLEXD9_ERR_IRQn, LINFLEXD10_ERR_IRQn, LINFLEXD11_ERR_IRQn, \
		                   LINFLEXD12_ERR_IRQn, LINFLEXD14_ERR_IRQn,LINFLEXD15_ERR_IRQn, LINFLEXD16_ERR_IRQn}

/* @brief LINFlexD "instance-implemented filters" mapping */
#define FEATURE_LINFLEXD_INST_HAS_IFCR {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, \
                                        TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE}

#define FEATURE_LINFLEXD_HAS_DMA_ENABLED 1U

#define SSI0_IRQn  INTR_ID_463
#define SSI1_IRQn  INTR_ID_464

#endif /* CCFC3007PT_FEATURES_H_ */
