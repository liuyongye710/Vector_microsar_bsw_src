/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  EthTrcv_30_Rtl9000_LL_Regs.h
 *        \brief  Ethernet transceiver driver lower layer header file
 *
 *      \details  Header file containing the Register offset, mask and shift information for the Ethernet Transceiver
 *                driver lower layer
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_RTL9000_LL_REGS_H)
# define ETHTRCV_30_RTL9000_LL_REGS_H
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* HW Version */
# define ETHTRCV_30_RTL9000_RTL_OUI                                     (0x0732u)
# define ETHTRCV_30_RTL9000_REV                                         (0x0u)

/* Common Bit-Ops */

/* General Registers */
/* Base Registers */
# define ETHTRCV_30_RTL9000_PAGE_0                                      (0x0000u)
# define ETHTRCV_30_RTL9000_REG_OFFS_BMCR                               (0x0000u)
# define ETHTRCV_30_RTL9000_REG_OFFS_BMSR                               (0x0001u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYIDR1                            (0x0002u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYIDR2                            (0x0003u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYCR                              (0x0009u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSR1                             (0x000Au)
# define ETHTRCV_30_RTL9000_REG_OFFS_MACR                               (0x000Du)
# define ETHTRCV_30_RTL9000_REG_OFFS_MAADR                              (0x000Eu)

# define ETHTRCV_30_RTL9000_PAGE_A42                                    (0x0A42u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSFR                             (0x0010u)
# define ETHTRCV_30_RTL9000_REG_OFFS_RTCTCR                             (0x0011u)
# define ETHTRCV_30_RTL9000_REG_OFFS_GINER                              (0x0012u)
# define ETHTRCV_30_RTL9000_REG_OFFS_GINMR                              (0x0014u)
# define ETHTRCV_30_RTL9000_REG_OFFS_SLPCR                              (0x0015u)
# define ETHTRCV_30_RTL9000_REG_OFFS_LKTCR                              (0x0016u)

# define ETHTRCV_30_RTL9000_PAGE_A43                                    (0x0A43u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSCR                             (0x0018u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSR2                             (0x001Au)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSRAD                            (0x001Bu)
# define ETHTRCV_30_RTL9000_REG_OFFS_PHYSRD                             (0x001Cu)
# define ETHTRCV_30_RTL9000_REG_OFFS_GINSR                              (0x001Du)
# define ETHTRCV_30_RTL9000_REG_OFFS_PAGSR                              (0x001Fu)

# define ETHTRCV_30_RTL9000_PAGE_A47                                    (0x0A47u)
# define ETHTRCV_30_RTL9000_REG_OFFS_GPSFR                              (0x0015u)

# define ETHTRCV_30_RTL9000_PAGE_A5A                                    (0x0A5Au)
# define ETHTRCV_30_RTL9000_REG_OFFS_SLPCAP                             (0x0014u)

# define ETHTRCV_30_RTL9000_PAGE_A60                                    (0x0A60u)
# define ETHTRCV_30_RTL9000_REG_OFFS_SLR                                (0x0011u)
# define ETHTRCV_30_RTL9000_REG_OFFS_PCR                                (0x0014u)

# define ETHTRCV_30_RTL9000_PAGE_A61                                    (0x0A61u)
# define ETHTRCV_30_RTL9000_REG_OFFS_LKTR                               (0x0010u)

# define ETHTRCV_30_RTL9000_PAGE_NONE                                   (0xFFFFu)
# define ETHTRCV_30_RTL9000_PAGE_DEFAULT                                (ETHTRCV_30_RTL9000_PAGE_A42)

/* Extended Registers */
# define ETHTRCV_30_RTL9000_REG_OFFS_SNRR                               (0xA8C0u)
# define ETHTRCV_30_RTL9000_REG_OFFS_MERR                               (0xA8E0u)
# define ETHTRCV_30_RTL9000_REG_OFFS_CLENR                              (0xA890u)
# define ETHTRCV_30_RTL9000_REG_OFFS_SSCCR                              (0xD012u)
# define ETHTRCV_30_RTL9000_REG_OFFS_RXDVCR                             (0xD050u)
# define ETHTRCV_30_RTL9000_REG_OFFS_LEDCR                              (0xD040u)
# define ETHTRCV_30_RTL9000_REG_OFFS_LED_PTP                            (0xD42Au)
# define ETHTRCV_30_RTL9000_REG_OFFS_HIDDEN_REG1                        (0xD41Eu)
# define ETHTRCV_30_RTL9000_REG_OFFS_HIDDEN_REG2                        (0xA42Cu)
# define ETHTRCV_30_RTL9000_REG_OFFS_CH_STATUS_CABLE_LENGTH             (0x8022u)
# define ETHTRCV_30_RTL9000_REG_OFF_OPCR2                               (0xDD00u)
# define ETHTRCV_30_RTL9000_REG_OFF_OPCR4                               (0xDD20u)
# define ETHTRCV_30_RTL9000_REG_OFF_REMOTE_LB                           (0xC800u)  /* register is not documented */

/* BMCR register access (Basic Mode Control Register) */
# define ETHTRCV_30_RTL9000_REG_BMCR_RESET                              (0x8000u)
# define ETHTRCV_30_RTL9000_REG_BMCR_LOOPBACK                           (0x4000u)
# define ETHTRCV_30_RTL9000_REG_BMCR_SPEED_SELECTION                    (0x2000u)
# define ETHTRCV_30_RTL9000_REG_BMCR_POWER_DOWN                         (0x0800u)
# define ETHTRCV_30_RTL9000_REG_BMCR_ISOLATE                            (0x0400u)
# define ETHTRCV_30_RTL9000_REG_BMCR_DUPLEX_MODE_FULL                   (0x0100u)

# define ETHTRCV_30_RTL9000_REG_BMCR_RESET_SHIFT                        (15u)

/* BMSR register access (Basic Mode Status Register) */
# define ETHTRCV_30_RTL9000_REG_BMSR_PREAMP_SUP                         (0x0040u)
# define ETHTRCV_30_RTL9000_REG_BMSR_LINK_STATE                         (0x0004u)
# define ETHTRCV_30_RTL9000_REG_BMSR_JABBER_DET                         (0x0002u)

/* PHYIDR1/2 register access (PHY ID1/2 Register) */
# define ETHTRCV_30_RTL9000_REG_PHYIDR1_OUI_MSB                         (0x001Cu)
# define ETHTRCV_30_RTL9000_REG_PHYIDR2_OUI_LSB                         (0xC800u)
# define ETHTRCV_30_RTL9000_REG_PHYIDR2_OUI_LSB_MASK                    (0xFC00u)

/* PHYCR register access (PHY Control Register) */
# define ETHTRCV_30_RTL9000_REG_PHYCR_TESTMODE_MASK                     ((0x8000u) | \
                                                                         (0x4000u) | \
                                                                         (0x2000u))

# define ETHTRCV_30_RTL9000_REG_OFFS_PHYCR_PHYTESTMODE_LSHIFT           (13u)
# define ETHTRCV_30_RTL9000_REG_PHYCR_MASTER                             (0x0800u)

/* PHYSCR register access (PHY Specific Control Register) */
# define ETHTRCV_30_RTL9000_REG_PHYSCR_PHYAD0_ENABLE                    (0x2000u)
# define ETHTRCV_30_RTL9000_REG_PHYSCR_MDI_LOOPBACK                     (0x0400u)

/* PHYSR1 register access (PHY Status Register1) */
# define ETHTRCV_30_RTL9000_REG_PHYSR1_MASTER_SLAVE_STATE               (0x4000u)
# define ETHTRCV_30_RTL9000_REG_PHYSR1_LOCAL_REC_STATE                  (0x2000u)
# define ETHTRCV_30_RTL9000_REG_PHYSR1_REMOTE_REC_STATE                 (0x1000u)

/* PHYSFR register access (PHY Status Sub-flag Register) */
# define ETHTRCV_30_RTL9000_REG_PHYSFR_MASK                             ((0x0004u) | \
                                                                         (0x0002u) | \
                                                                         (0x0001u))
# define ETHTRCV_30_RTL9000_REG_PHYSFR_PHY_INIT                         (0x1u)
# define ETHTRCV_30_RTL9000_REG_PHYSFR_PHY_READY                        (0x3u)
# define ETHTRCV_30_RTL9000_REG_PHYSFR_PHY_RESET                        (0x4u)
# define ETHTRCV_30_RTL9000_REG_PHYSFR_PHY_POWDN                        (0x5u)

/* SSCCR register access (SSC Control Register) */
# define ETHTRCV_30_RTL9000_REG_SSCCR_RMII_REF_CLK_SSC                  (0x0004u)
# define ETHTRCV_30_RTL9000_REG_SSCCR_SYS_CLK_SSC                       (0x0001u)

/* RTCTCR register access (RTCT Control Register) */
# define ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_DONE                   (0x8000u)
# define ETHTRCV_30_RTL9000_REG_RTCTCR_CABLEDIAG_ENABLE                 (0x0001u)

/* RTCT Cable Status Indication */
# define ETHTRCV_30_RTL9000_CABLE_STAT_NORMAL                           (0x60u)
# define ETHTRCV_30_RTL9000_CABLE_STAT_SHORT                            (0x50u)
# define ETHTRCV_30_RTL9000_CABLE_STAT_OPEN                             (0x48u)
# define ETHTRCV_30_RTL9000_CABLE_STAT_RSHIFT                           (8u)

/* OPCR2 register access (OP Control Register 2) */
# define ETHTRCV_30_RTL9000_REG_OPCR2_OPCMD_MASK                        ((0x0010u) | \
                                                                         (0x0008u) | \
                                                                         (0x0004u) | \
                                                                         (0x0002u) | \
                                                                         (0x0001u))

/* OPCR4 register access (OP Control Register 4) */
# define ETHTRCV_30_RTL9000_REG_OPCR4_OPCMD2_MASK                       ((0x0008u) | \
                                                                         (0x0004u) | \
                                                                         (0x0002u) | \
                                                                         (0x0001u))
# define ETHTRCV_30_RTL9000_REG_OPCR4_OPCMD2_NORMAL                      (0xBu)

/* REMOTE_LB register access (undocumented register to enable remote loopback) */
# define ETHTRCV_30_RTL9000_REG_REMOTE_LB_ENABLE                        (0x0010u)
# define ETHTRCV_30_RTL9000_REG_REMOTE_LB_DISABLE_MASK                  (0xFFu)   /* undocumented register mask */

#endif /* ETHTRCV_30_RTL9000_LL_REGS_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_Tja1100_LL_Regs.h
 *********************************************************************************************************************/
