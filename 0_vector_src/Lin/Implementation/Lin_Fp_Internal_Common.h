/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/*!        \file  Lin_Fp_Internal_Common.h
 *        \brief  AUTOSAR LIN Driver Frame Processor
 *
 *      \details  Internal header for ASCLIN hardware frame processor (Tricore)
 *
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  14.00.00  2018-04-03  vislpr  -             Implement new AUTOSAR 4 LIN driver for Tricore
 *                        visap   -             Rework review findings
 *  14.01.00  2018-08-31  visjgl  TASK-89105    MISRA 2012
 *                        visjgl  FIX-4948      No Lin communication possible if F_ASCLINS is selected as Clock Source
 *  14.01.01  2019-05-13  visap   TASK-123308   Reduce inter-byte space by new IDLE default setting
 *  14.02.00  2019-09-30  visjgl  TASK-133546   Implement user selectable break and break delimiter length feature
 *  15.00.00  2020-03-10  viskja                R24 Master support
 *  15.01.00  2020-09-09  visjgl  LIN-139       R24 Slave support
 *  15.01.01  2020-11-19  vispwf  LIN-164       Quality cleanup
 *  15.01.02  2021-07-19  visjgl  LIN-411       Slave node: After GoToSleep command the LIN driver channel cannot wake up / does not respond
 *  15.02.00  2022-03-15  viskja  LIN-371       Add support for Tc4xx
 *********************************************************************************************************************/

#if !defined (LIN_FP_INTERNAL_COMMON)
# define LIN_FP_INTERNAL_COMMON

/*!
  \name Component version information (decimal version of ALM implementation package)
  \{
*/
# define LIN_PLATFORM_MAJOR_VERSION                             15
# define LIN_PLATFORM_MINOR_VERSION                             2
# define LIN_PLATFORM_PATCH_VERSION                             0
/*! \} */

/***********************************************************************************************************************
 *  Hardware Software Interface
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *
 *
 *
 *
 *
 */

/*!
  \name Hardware register layout
  \{
*/
# if (LIN_NEW_REGISTER_STRUCTURE_USED == STD_OFF)
struct Lin_RegisterStructTag
{
  VAR(uint32, TYPEDEF) CLC;         /*!< Offset Address 0x0000: Clock Control Register */
  VAR(uint32, TYPEDEF) IOCR;        /*!< Offset Address 0x0004: Input Output Control Register */
  VAR(uint32, TYPEDEF) ID;          /*!< Offset Address 0x0008: Module Identification Register */
  VAR(uint32, TYPEDEF) TXFIFOCON;   /*!< Offset Address 0x000C: TX FIFO Configuration Register */
  VAR(uint32, TYPEDEF) RXFIFOCON;   /*!< Offset Address 0x0010: RX FIFO Configuration Register */
  VAR(uint32, TYPEDEF) BITCON;      /*!< Offset Address 0x0014: Bit Timing Configuration Register */
  VAR(uint32, TYPEDEF) FRAMECON;    /*!< Offset Address 0x0018: Frame Configuration Register */
  VAR(uint32, TYPEDEF) DATCON;      /*!< Offset Address 0x001C: Data Configuration Register */
  VAR(uint32, TYPEDEF) BRG;         /*!< Offset Address 0x0020: Baud Rate Generation Register */
  VAR(uint32, TYPEDEF) BRD;         /*!< Offset Address 0x0024: Baud Rate Detection Register */
  VAR(uint32, TYPEDEF) LINCON;      /*!< Offset Address 0x0028: LIN Configuration Register */
  VAR(uint32, TYPEDEF) LINBTIMER;   /*!< Offset Address 0x002C: LIN Break Timer Register */
  VAR(uint32, TYPEDEF) LINHTIMER;   /*!< Offset Address 0x0030: LIN Header Timer Register */
  VAR(uint32, TYPEDEF) FLAGS;       /*!< Offset Address 0x0034: Flags Register */
  VAR(uint32, TYPEDEF) FLAGSSET;    /*!< Offset Address 0x0038: Flags Set Register */
  VAR(uint32, TYPEDEF) FLAGSCLEAR;  /*!< Offset Address 0x003C: Flags Clear Register */
  VAR(uint32, TYPEDEF) FLAGSENABLE; /*!< Offset Address 0x0040: Flags Enable Register */
  VAR(uint32, TYPEDEF) TXDATA;      /*!< Offset Address 0x0044: Transmit Data Register */
  VAR(uint32, TYPEDEF) RXDATA;      /*!< Offset Address 0x0048: Receive Data Register */
  VAR(uint32, TYPEDEF) CSR;         /*!< Offset Address 0x004C: Clock Selection Register */
};

# elif (LIN_NEW_REGISTER_STRUCTURE_USED == STD_ON)
struct Lin_RegisterStructTag
{
  VAR(uint32, TYPEDEF) CLC;         /*!< Offset Address 0x0000: Clock Control Register */
  VAR(uint32, TYPEDEF) OCS;         /*!< Offset Address 0x0004: OCDS Control and Status Register */
  VAR(uint32, TYPEDEF) ID;          /*!< Offset Address 0x0008: Module Identification Register */
  VAR(uint32, TYPEDEF) UNUSED[61];  /*!< Unused Registers for ASCLIN */
  VAR(uint32, TYPEDEF) IOCR;        /*!< Offset Address 0x0100: Input and Output Control Register */
  VAR(uint32, TYPEDEF) TXFIFOCON;   /*!< Offset Address 0x0104: TxFIFO Configuration Register */
  VAR(uint32, TYPEDEF) RXFIFOCON;   /*!< Offset Address 0x0108: RxFIFO Configuration Register */
  VAR(uint32, TYPEDEF) BITCON;      /*!< Offset Address 0x010C: Bit Configuration Register */
  VAR(uint32, TYPEDEF) FRAMECON;    /*!< Offset Address 0x0110: Frame Control Register */
  VAR(uint32, TYPEDEF) DATCON;      /*!< Offset Address 0x0114: Data Configuration Register */
  VAR(uint32, TYPEDEF) BRG;         /*!< Offset Address 0x0118: Baud Rate Generation Register */
  VAR(uint32, TYPEDEF) BRD;         /*!< Offset Address 0x011C: Baud Rate Detection Register */
  VAR(uint32, TYPEDEF) LINCON;      /*!< Offset Address 0x0120: LIN Contro Register */
  VAR(uint32, TYPEDEF) LINBTIMER;   /*!< Offset Address 0x0124: LIN Break Timer Register */
  VAR(uint32, TYPEDEF) LINHTIMER;   /*!< Offset Address 0x0128: LIN Header Timer Register */
  VAR(uint32, TYPEDEF) FLAGS;       /*!< Offset Address 0x012C: Flags Register */
  VAR(uint32, TYPEDEF) FLAGSSET;    /*!< Offset Address 0x0130: Flags Set Register */
  VAR(uint32, TYPEDEF) FLAGSCLEAR;  /*!< Offset Address 0x0134: Flags Clear Register */
  VAR(uint32, TYPEDEF) FLAGSENABLE; /*!< Offset Address 0x0138: Flags Enable Register */
  VAR(uint32, TYPEDEF) CSR;         /*!< Offset Address 0x013C: Clock Selection Register */
  VAR(uint32, TYPEDEF) TXDATA;      /*!< Offset Address 0x0140: Transmit Data Register */
  VAR(uint32, TYPEDEF) RESERVED[8]; /*!< Unused Registers for ASCLIN */
  VAR(uint32, TYPEDEF) RXDATA;      /*!< Offset Address 0x0160: Receive Data Register */
};
# endif
/*! \} */

/***********************************************************************************************************************
 *  Used registers and bits (bit mask)
 **********************************************************************************************************************/
/*!
\name Bitmasks for register LIN_CSR
\{
*/
          /*! Clock Select mask */
# define LIN_CSR_CLKSEL_MASK                                    ((uint32)0x0000001FU)
/*! \} */

/*!
  \name Defines for register LIN_FRAMECON
  \{
*/
# if !defined (LIN_FRAMECON_IDLE)  /* COV_LIN_USER_DEPENDENT */
          /* ODD=0, PEN=0, CEN=1, MSB=0, MODE=3(LIN), LEAD->Generator , STOP=1, IDLE=0 */
#  define LIN_FRAMECON_DEFAULT                                  ((uint32)0x20030200U)
# else
#  define LIN_FRAMECON_DEFAULT                                  ((uint32)0x20030200U) | ((uint32)(LIN_FRAMECON_IDLE & 0x01C0U))
# endif /* LIN_FRAMECON_IDLE */
/*! \} */

/*!
  \name Defines for register LIN_BITCON
  \{
*/
          /* 3 samples per bit, bits 7,8 and 9, oversampling factor 16 */
# define LIN_BITCON_DEFAULT                                     ((uint32)0x890F0000U)
/*! \} */

/*!
  \name Defines for register LIN_DATCON
  \{
*/
          /* response timeout to 256 */
# define LIN_DATCON_MAXRESP                                     ((uint32)0x00FF0000U)
          /* response mode set to response part */
# define LIN_DATCON_RM_RESP                                     ((uint32)0x00004000U)
          /* classic checksum mode */
# define LIN_DATCON_CSM_CLASSIC                                 ((uint32)0x00000000U)
          /* classic checksum mode */
# define LIN_DATCON_CSM_ENH                                     ((uint32)0x00008000U)
          /* header only mode */
# define LIN_DATCON_HO                                          ((uint32)0x00002000U)
/*! \} */

/*!
  \name Defines for register LIN_RXFIFOCON
  \{
*/
          /* flush Rx FIFO, disable inlet */
# define LIN_RXFIFOCON_CLEAR_STOP                               ((uint32)0x00000001U)
          /* enable inlet, get 1 byte per read */
# define LIN_RXFIFOCON_ENABLE                                   ((uint32)0x00000042U)
          /* FIFO filling level mask */
# define LIN_RXFIFOCON_FILL_MASK                                ((uint32)0x001F0000U)
          /* only PID received */
# define LIN_RXFIFOCON_PID_RECVD                                ((uint32)0x00010000U)
/*! \} */

/*!
  \name Defines for register LIN_TXFIFOCON
  \{
*/
          /* flush Tx FIFO, disable outlet, inlet width = 1 */
# define LIN_TXFIFOCON_CLEAR_STOP                               ((uint32)0x00000041U)
          /* enable outlet, inlet width = 1 => take one byte into FIFO per write to TXDATA register */
# define LIN_TXFIFOCON_ENABLE                                   ((uint32)0x00000042U)
/*! \} */

/*!
  \name Define for registers FLAGS, FLAGSENABLE, FLAGSCLEAR, FLAGSSET ( interrupt bits / flags )
  \{
*/
          /* Transmit Header End */
# define LIN_FLAGS_TH                                           ((uint32)0x00000001U)
          /* Transmit Response End */
# define LIN_FLAGS_TR                                           ((uint32)0x00000002U)
          /* Receive Header End */
# define LIN_FLAGS_RH                                           ((uint32)0x00000004U)
          /* Receive Response End */
# define LIN_FLAGS_RR                                           ((uint32)0x00000008U)
          /* Falling Edge 1 -> 0, detecting a wakeup frame is only possible via the FED flag */
# define LIN_FLAGS_FED                                          ((uint32)0x00000020U)
          /* Transmit Wake Request */
# define LIN_FLAGS_TWRQ                                         ((uint32)0x00002000U)
          /* Transmit Header Request */
# define LIN_FLAGS_THRQ                                         ((uint32)0x00004000U)
          /* Transmit Response Request */
# define LIN_FLAGS_TRRQ                                         ((uint32)0x00008000U)
          /* Framing Error */
# define LIN_FLAGS_FE                                           ((uint32)0x00040000U)
          /* Header Timeout */
# define LIN_FLAGS_HT                                           ((uint32)0x00080000U)
          /* Response Timeout */
# define LIN_FLAGS_RT                                           ((uint32)0x00100000U)
          /* LIN Parity Error */
# define LIN_FLAGS_LP                                           ((uint32)0x00400000U)
          /* LIN Checksum Error */
# define LIN_FLAGS_LC                                           ((uint32)0x01000000U)
          /* Collision Detection */
# define LIN_FLAGS_CE                                           ((uint32)0x02000000U)

# define LIN_FLAGS_ERROR                                        ((uint32)( LIN_FLAGS_FE | \
                                                                      LIN_FLAGS_RT | \
                                                                      LIN_FLAGS_LC | \
                                                                      LIN_FLAGS_CE ))

# define LIN_FLAGS_ERROR_SLAVE                                  ((uint32)( LIN_FLAGS_FE | \
                                                                      LIN_FLAGS_HT | \
                                                                      LIN_FLAGS_RT | \
                                                                      LIN_FLAGS_LP | \
                                                                      LIN_FLAGS_LC | \
                                                                      LIN_FLAGS_CE ))

# define LIN_FLAGS_ALL_MASTER                                   ((uint32)( LIN_FLAGS_ERROR | \
                                                                      LIN_FLAGS_TR    | \
                                                                      LIN_FLAGS_RR    | \
                                                                      LIN_FLAGS_TH ))

# define LIN_FLAGSCLEAR_ALL                                     ((uint32)( 0xFFFFFFFFU ))
/*! \} */

/*!
  \name Wakeup pattern
  \{
*/
# if !defined (LIN_WAKEUP_PATTERN) /* COV_LIN_USER_DEPENDENT */
#  define LIN_WAKEUP_PATTERN                                    ((uint8)0x80U)
# endif
/*! \} */


/***********************************************************************************************************************
 *  FRAMEPROCESSOR LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/*!
  \name Frameprocessor Local function macros
  \{
*/
# if (LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_OFF) /* COV_LIN_SLAVE_SL_ALWAYS_NOT_ON */
/* Replace function call to nothing */
#  define Lin_Fp_Slave_Interrupt(ChannelConfigIdx)              /*! Remove the function in Master_only configuration*/
#  define Lin_Fp_EnableHeaderReception(ChannelConfigIdx)        /*! Remove the function in Master_only configuration*/

# endif /* LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_OFF */

# if ( (LIN_ABDOFCHANNELCONFIG == STD_OFF) || (LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_OFF) ) /* COV_LIN_NO_ABD */
/* Replace function call to nothing */
#  define Lin_Fp_ConfigureBRD( ChannelConfigIdx )               /*! Remove the function in Master_only and ADB configuration*/

# endif /* LIN_ABDOFCHANNELCONFIG == STD_OFF */
/*! \} */


/**********************************************************************************************************************
 *  Os API
 *********************************************************************************************************************/
# include "Os.h"
# if !defined osWritePeripheral32
#  define LIN_PROTECTED_AREA_ENDINIT                            0U
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#  define osWritePeripheral32( a, b, c )                              *((uint32*)(b)) = (c)
# endif

/***********************************************************************************************************************
 *  Appl_UnlockEndinit
 **********************************************************************************************************************/
/*! \brief       Unlock Endinit-Protect.
 *  \details     Unlocks registers that are normally protected through Endinit-Protect.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        The user application has provide this function.
 **********************************************************************************************************************/
extern FUNC(void, LIN_APPL_CODE) Appl_UnlockEndinit( void );


/***********************************************************************************************************************
 *  Appl_LockEndinit
 **********************************************************************************************************************/
/*! \brief       Lock Endinit-Protect.
 *  \details     Locks registers that are normally protected through Endinit-Protect.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        The user application has provide this function.
 **********************************************************************************************************************/
extern FUNC(void, LIN_APPL_CODE) Appl_LockEndinit( void );


#endif /* LIN_FP_INTERNAL_COMMON */

/**********************************************************************************************************************
 *  END OF FILE: Lin_Fp_Internal_Common.h
 *********************************************************************************************************************/
