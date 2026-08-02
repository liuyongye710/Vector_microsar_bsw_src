/* Kernbauer Version: 1.16 Konfiguration: DrvTransCan Erzeugungsgangnummer: 1 */


/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 |  FILE DESCRIPTION
 |  -------------------------------------------------------------------------------------------------------------------
 |         File:  CanTrcv_30_Tja1145.c
 |      Project:  MICROSAR
 |       Module:  CAN Transceiver driver
 |    Generator:  DaVinci Configurator
 |  Description:  Implementation of the MICROSAR CAN Transceiver Driver.
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Senol Cendere                 Ces           Vector Informatik GmbH
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Jan Hammer                    Jan           Vector Informatik GmbH
 *  Carsten Gauglitz              Gaz           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2011-07-26  Tvi     -             First Implementation
 *  1.01.00   2012-03-05  Tvi     ESCAN00057891 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00057890 AR3-1738: Add support for asynchronous transceiver driver
 *  2.00.00   2012-05-23  Tvi     ESCAN00058534 Compile error caused by usage of wrong memory class
 *                                ESCAN00060767 SetOpMode returns E_NOT_OK and reports a DET after initialization
 *  2.00.01   2012-12-05  Tvi     -             (no changes here, just merge with new HL)
 *  2.00.02   2013-02-28  Tvi     ESCAN00064688 Incorrect register address for "Wake pin status" used in CanTrcv_30_Tja1145_GetTrcvSystemData
 *  2.01.00   2013-04-10  Tvi     ESCAN00066526 Use block transfer for improved performance
 *                        Tvi     ESCAN00066527 Add support for automatic reinitialization
 *                        Tvi     ESCAN00066528 [ASR3 only] Clear wakeup flags during transition to STANDBY if PN is disabled.
 *                        Tvi     ESCAN00066529 Clear Wake Pin wakeups in ClearTrcvWufFlag
 *  2.02.00   2013-12-04  Tvi     -             (no changes here, just merge with new HL)
 *  2.03.00   2014-04-22  Tvi     ESCAN00072393 Allow configuration of Bit CFDC
 *  3.00.00   2014-11-05  Seu     ESCAN00079389 AR4-698: Post-Build Selectable (Identity Manager)
 *  3.01.00   2015-07-28  Seu     ESCAN00083361 Unexpectedly wake-up reason "WU_BY_SYSERR" is reported / set
 *  3.02.00   2015-10-07  Seu     ESCAN00081058 FEAT-427: SafeBSW Step I
 *            2015-12-01  Seu     ESCAN00086914 Add support for "CanTrcvHwPnSupport" = false
 *            2015-12-01  Seu     ESCAN00086226 ECU does NOT: go to standby/sleep / wake-up / answer at all
 *  3.02.01   2015-01-20  Seu     ESCAN00087596 Compiler warning: ctc E553 "no break or comment before case label"
 *  3.03.00   2016-01-20  Seu     ESCAN00087581 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088822 Add Postbuild Loadable Support for Tja1145-CanTrcvDrv
 *  3.04.00   2016-04-05  Seu     ESCAN00089226 FEAT-1688: SafeBSW Step 4
 *  3.04.01   2016-06-22  Seu     ESCAN00090613 Compiler error: Syntax Error caused by undefined compiler class: CANTRCV_30_TJA1145_VAR
 *  3.05.00   2016-08-01  Seu     ESCAN00091504 Improve code coverage
 *            2016-11-01  Seu     ESCAN00092619 Driver does not work as expected
 *            2016-11-23  Seu     ESCAN00092984 Add support for asynchronous SPI without polling support
 *            2016-12-15  Seu     ESCAN00093320 Compiler error: error #20: identifier "CanTrcv_30_Tja1145_RdStatusTask" is undefined
 *            2017-01-23  Seu     ESCAN00093677 ECU does not go to sleep / CanTrcv does not answer with indication function in case of shut down sequence
 *  3.06.00   2017-01-31  Seu     ESCAN00093786 Improve doxygen comments
 *            2017-02-06  Seu     ESCAN00094661 Improve CDD
 *            2017-04-05  Seu     ESCAN00092283 Error frame is caused in case of start-up of ECU
 *  3.06.01   2017-08-29  Jan     ESCAN00096444 Support ATA6570
 *  3.07.00   2018-08-23  Jan     STORYC-6321   MISRA-C:2012 Compliance
 *  3.08.00   2019-04-29  Gaz     STORYC-8228   Deactivate Wakeup Source in case Wakeup by Bus is deactivated
 * *******************************************************************************************************************/
 
/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Jan Hammer                    Jan           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-02-25  Fn      -             Intitial revision of the core implementation
 *  01.00.01  2008-04-17  Fn      -             Update of the include file names
 *  01.01.00  2008-06-26  Ou      ESCAN00027616 Various compile errors, problems with Organi
 *  01.02.00  2008-09-12  Ou      ESCAN00029980 Compiler failure due to wrong definition of SW version
 *  01.03.00  2008-10-07  Ou      ESCAN00028298 Several warnings due to unreferenced local variables
 *                        Ou      ESCAN00029572 DrvTrans__coreCanxAsr raise DET error if CanTrcv_SetOpMode is called with invalid TrcvWakeupMode
 *                        Ou      ESCAN00030536 Compile error at extended version check
 *  01.04.00  2008-12-11  Ou      ESCAN00031771 Adjust wakeup by bus handling for platforms which cannot be woken up with a CAN frame
 *  01.05.00  2009-02-19  Tvi     ESCAN00033258 GetBusWuReason may return an invalid value
 *  01.06.00  2009-02-26  Tvi     ESCAN00033383 Don't throw DET error in case the same mode is requested again
 *                        Tvi     ESCAN00033398 Compiler warnings when using different transceiver types within the same stack
 *                        Tvi     ESCAN00033413 Possible out of bounds access in SetOpMode if DET is enabled
 *  02.00.00  2009-06-29  Fn      ESCAN00035913 CAN Transceiver channel does not wake up
 *  02.00.01  2009-10-15  Tvi     ESCAN00038495 Compile error: unknown type definitions in dio.h
 *  02.01.00  2009-11-04  Tvi     ESCAN00036841 OP_MODE_SLEEP should be independent of GENERAL_WAKE_UP_SUPPORT
 *                        Tvi     ESCAN00038945 Use different DioPins tokens for GetOpMode and CHECK_WA
 *                        Tvi     ESCAN00038946 Rename filenames to match BSW00347
 *                        Tvi     ESCAN00038947 CanTrcv087 has to be implemented the correct way
 *                        Tvi     ESCAN00039039 Add support for timers
 *                        Tvi     ESCAN00039041 Allow transition to OP_MODE_NORMAL even if it is the current OpMode
 *                        Tvi     ESCAN00039043 Implement an initialization via OP_MODE_NORMAL
 *                        Tvi     ESCAN00039194 Disable IcuNotification when entering Normal mode in Init and SetOpMode
 *  02.02.00  2010-05-04  Tvi     ESCAN00040088 Compiler Warning: unused parameter 'TrcvWakeupMode'
 *  02.20.00  2010-07-01  Tvi     ESCAN00046512 Add support for partial network transceivers
 *            2010-11-29  Tvi     ESCAN00046781 Support Multiple Identity Configuration
 *                                ESCAN00045601 "Channel Used" parameter not well implemented
 *                                ESCAN00046813 Adapt AUTOSAR version check
 *                                ESCAN00047668 Critical areas should be Trcv specific
 *  02.20.01  2011-02-08  Tvi     ESCAN00048498 Wrong DEM Events used
 *  02.20.02  2011-03-11  Tvi     ESCAN00049830 Remove ASR Version check for SPI / DIO
 *                                ESCAN00049831 [PN only] Store wakeup event and report them if Trcv is in Standby mode
 *  03.00.00  2011-05-05  Tvi     ESCAN00051930 Add support for ASR3.2.1
 *                                ESCAN00051564 Remove the AUTOSAR Release Version Check
 *  03.01.00  2011-11-22  Tvi     ESCAN00054349 AR3-1738: Add support for asynchronous transceiver driver
 *                                ESCAN00053272 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053265 AR3-2069: Remove non-SchM code for critical section handling
 *  03.01.01  2012-02-12  Tvi     ESCAN00057892 [PN only] CanTrcv does not wakeup when Synchronous SPI is being used
 *                        Tvi     ESCAN00056788 Compiler error/warning: DRVTRANS__CORECANXASR_RELEASE_VERSION' redefined
 *  04.00.00  2012-05-21  Tvi     ESCAN00058641 AR4-95: Provide CanTrcv according ASR 4, Asynchronous Transceiver Mode Changes
 *                                ESCAN00059656 Add support for SetPNActivationState according to ASR4
 *                                ESCAN00060455 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  04.00.01  2012-09-27  Tvi     ESCAN00061779 [CFG5/ASR4 only]: Compiler error about unkown struct member instanceID
 *  04.01.00  2012-10-08  Tvi     ESCAN00062121 Report DEM if PN is not available
 *                        Tvi     ESCAN00066283 AR4-352: Support partial networking
 *  04.02.00  2013-11-20  Tvi     ESCAN00071370 AR4-569: [CanTrcv]  Incompatible  argument  in call to EcuM_SetWakeupEvent()
 *  04.03.00  2014-01-10  Tvi     ESCAN00073861 AR4-345: Implement PF4_PostBuildSelectable
 *  05.00.00  2014-09-24  Seu     ESCAN00076622 AR4-698: Post-Build Selectable (Identity Manager)
 *  05.00.01  2014-11-13  Seu     -             MISRA deviation comment for rule 6080 added (APIs: *_ClearTrcvWufFlag() and *_CheckWakeFlag())
 *  05.01.00  2015-05-04  Seu     ESCAN00077814 Support for CAN Transceiver on System-Basis Chips (SBCs)
 *            2015-07-23  Seu     ESCAN00084154 Only since R13: Compiler error: C2059: syntax error : '{'
 *            2015-07-23  Seu     ESCAN00083583 Adapt in order to fix ESCAN00083361 / ESCAN00083362
 *            2015-07-23  Seu     ESCAN00083395 Compiler warning: parameter is never used
 *  05.01.01  2015-09-24  Seu     ESCAN00085451 Support usage of Partial Networking for SBCs.
 *  05.01.02  2015-10-06  Seu     ESCAN00085678 Initialize requestState in case of INTERFACE_SBC and PN is used
 *  05.02.00  2015-02-04  Seu     ESCAN00080310 FEAT-427: SafeBSW Step I
 *            2015-10-05  Seu     ESCAN00081795 FEAT-1275: SafeBSW Step 2
 *            2015-10-05  Seu     ESCAN00085154 FEAT-1527: SafeBSW Step 3
 *  05.03.00  2016-01-16  Seu     ESCAN00087580 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088810 Add Postbuild Loadable Support for CanTrcvDrv
 *  05.04.00  2016-04-05  Seu     ESCAN00087813 FEAT-1688: SafeBSW Step 4
 *            2016-05-19  Seu     ESCAN00090097 Compiler error: Syntax Error caused by undefined compiler class
 *  05.04.01  2016-08-02  Seu     ESCAN00091270 MISRA deviation: MISRA-C:2004 Rule 8.8
 *            2016-08-17  Seu     ESCAN00091505 Improve code coverage and doxygen comments
 *            2016-10-17  Seu     ESCAN00091616 Compiler error: identifier index not declared
 *  05.05.00  2016-11-23  Seu     ESCAN00092817 Add support for asynchronous SPI without polling support
 *            2016-11-29  Seu     ESCAN00093075 [Only: Tja1145 / E52013] In case of startup of ECU SysErr-wakeup is reported instead of PowerOn-wakeup
 *            2016-12-06  Seu     ESCAN00093177 Omit interrupted transition: STANDBY -> NORMAL (pending) -> SLEEP  [only async SPI]
 *  05.06.00  2017-04-05  Seu     ESCAN00094603 Add support for requirements: CanTrcv_00230, CanTrcv_00190, CanTrcv_00191
 *            2017-04-05  Seu     ESCAN00094658 Improve doxygen comments
 *  05.06.01  2017-05-30  Seu     ESCAN00095350 Add: SafeBSW support for DIO-CanTrcv, flexibility for SPI-CanTrcv
 *  05.07.00  2018-08-21  Jan     STORYC-4868   MISRA-C:2012 Compliance
 *  05.08.00  2019-05-03  Jan     ESCAN00102288 Spi_DataType to Spi_DataBufferType: Incompatible data type.
 *            2019-05-03  Jan     STORYC-8282   Add emulated Sleep mode
 *            2019-05-13  Jan     STORYC-8389   Improve PTH of API: CanTrcv_SetOpMode()
 * *******************************************************************************************************************/

/* PRQA S 0715 EOF */ /* MD_MSR_1.1_715 */
/* PRQA S 0850 EOF */ /* MD_MSR_MacroArgumentEmpty */
/* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */
/* PRQA S 3453 EOF */ /* MD_MSR_FctLikeMacro */
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/* ********************************************************************************************************************
 *  INCLUDES
 * *******************************************************************************************************************/
#define CANTRCV_30_TJA1145_INCLUDE_INTERNAL
#define V_CANTRCV_30_TJA1145_SOURCE

/* \trace SPEC-19973, SPEC-20008, SPEC-19954, SPEC-19965 */
/* \trace SPEC-14977, SPEC-15093, SPEC-15086, SPEC-14969 */
#include "CanTrcv_30_Tja1145.h"

# include "Spi.h"


#include "CanIf.h"

#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif

#include "EcuM.h"


#if (CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON)
# include "Tm.h"
#endif


/* *********************************************************************************************************************
 *  VERSION CHECK
 * ********************************************************************************************************************/

#if (DRVTRANS__CORECANXASR_VERSION                             != 0x0508u)
# error "Module CanTrcv_30_Tja1145: Source and Header files are inconsistent!"
#endif
#if (DRVTRANS__CORECANXASR_RELEASE_VERSION                     != 0x00u)
# error "Module CanTrcv_30_Tja1145: Source and Header files are inconsistent!"
#endif


/* ** Version Check: CFG5 - Base part ** */
#define CANTRCV_30_TJA1145_BASE_GENDATA_COMP_VERSION     0x0105u

#if (CANTRCV_30_TJA1145_GENTOOL_CFG5_BASE_COMP_VERSION != CANTRCV_30_TJA1145_BASE_GENDATA_COMP_VERSION)
# error "Module CanTrcv_30_Tja1145: Source and Generated Header files are inconsistent! [BASE]"
#endif


# if defined(CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP)
# else
/* \trace SPEC-46905 */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
#    define CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP STD_ON
#  else
#    define CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP STD_OFF
#  endif
# endif


# if (DRVTRANS_TJA1145CANSPIASR_VERSION                    != 0x0308u)
#  error "Module CanTrcv_30_Tja1145: Source and Header files are inconsistent!"
# endif
# if (DRVTRANS_TJA1145CANSPIASR_RELEASE_VERSION            != 0x00u)
#  error "Module CanTrcv_30_Tja1145: Source and Header files are inconsistent!"
# endif

/* ** Version Check: CFG5 - HW specific part ** */
#define CANTRCV_30_TJA1145_HW_GENDATA_COMP_VERSION     0x0105u

#if (CANTRCV_30_TJA1145_GENTOOL_CFG5_HW_COMP_VERSION != CANTRCV_30_TJA1145_HW_GENDATA_COMP_VERSION)
# error "Module CanTrcv_30_Tja1145: Source and Generated Header files are inconsistent! [HW-specific]"
#endif








/* ********************************************************************************************************************
 *  LOCAL DEFINES
 * ********************************************************************************************************************/


#if !defined (CANTRCV_30_TJA1145_LOCAL)
# define CANTRCV_30_TJA1145_LOCAL             static
#endif

#if !defined (CANTRCV_30_TJA1145_LOCAL_INLINE)
# define CANTRCV_30_TJA1145_LOCAL_INLINE      LOCAL_INLINE
#endif

# if !defined(CanTrcv_SpiDataType)
#  define CanTrcv_SpiDataType Spi_DataType
# endif
# if defined(CANTRCV_30_TJA1145_AUTO_REINIT)
# else
#  define CANTRCV_30_TJA1145_AUTO_REINIT STD_OFF
# endif


#define CanTrcvCfg_IsChannelUsed(ch)                   CanTrcv_30_Tja1145_IsChannelUsed(ch)
#define CanTrcvCfg_IsWakeupByBusUsed(ch)               CanTrcv_30_Tja1145_IsWakeupByBusUsed(ch)
#define CanTrcvCfg_GetWakeupSource(ch)                 CanTrcv_30_Tja1145_GetWakeupSource(ch)
#define CanTrcvCfg_GetWakeupSourceSyserr(ch)           CanTrcv_30_Tja1145_GetWuSrcSyserr(ch)
#define CanTrcvCfg_GetWakeupSourcePor(ch)              CanTrcv_30_Tja1145_GetWuSrcPor(ch)
#define CanTrcvCfg_IsIcuChannelSet(ch)                 CanTrcv_30_Tja1145_IsIcuChannelSetOfChannel(ch)
#define CanTrcvCfg_GetIcuChannel(ch)                   CanTrcv_30_Tja1145_GetIcuChannelOfChannel(ch)
#define CanTrcvCfg_GetMagicNumber()                    CanTrcv_30_Tja1145_GetFinalMagicNumber()
#define CanTrcvCfg_GetGeneratorCompatibilityVersion()  CanTrcv_30_Tja1145_GetGeneratorCompatibilityVersion()

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
# define CanTrcvCfg_IsPnEnabled(ch)               CanTrcv_30_Tja1145_IsPnEnabled(ch)
#endif



/* --- Flags to handle any kind of requests --- */

/* 
* Please note CanTrcv_30_Tja1145_Prob_Type.requestState is a 32bit value: |4.byte|3.byte|2.byte|1.byte|
* The bits/bytes are reserved/used as follows:
* LL: |4.byte|
* HL: |3.byte| - |1.byte|
*/
# define CanTrcv_30_Tja1145_Req_None                     0x00000000u   /* No request pending                     */

/* ! Operation modes requests */
#  define CanTrcv_30_Tja1145_Req_OpModeMask              0x0000000Fu   /* Mask to query operation mode requests  */
#  define CanTrcv_30_Tja1145_Req_OpModeNormal            0x00000001u   /* Normal operation mode                  */
#  define CanTrcv_30_Tja1145_Req_OpModeStandby           0x00000002u   /* Standby mode                           */
#  define CanTrcv_30_Tja1145_Req_OpModeSleep             0x00000004u   /* Sleep mode                             */

# define CanTrcv_30_Tja1145_Req_CbByBusFlag              0x00000040u   /* Request to execute CheckWakeup         */

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
#  define CanTrcv_30_Tja1145_Req_OpModeNormalPn          0x00000008u   /* Special mode with Pn enabled in Normal */

#  define CanTrcv_30_Tja1145_Req_ClrWufFlag              0x00000010u   /* Request to execute ClearTrcvWufFlag    */
#  define CanTrcv_30_Tja1145_Req_ChkWakFlag              0x00000020u   /* Request to execute CheckWakeFlag       */

#   define CanTrcv_30_Tja1145_Req_ConfirmPnAvailability  0x00001000u   /* Request to confirm Pn avaibility       */

#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
#    if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
#     define CanTrcv_30_Tja1145_Req_ReInitPn             0x00000100u   /* Request to re-init the PN-configuration in case of asynchronous SPI is configured */
#    endif
#    define CanTrcv_30_Tja1145_Req_SyncSpiTx             0x00010000u   /* Request to execute synchronous transmission in case of asynchronous SPI is configured */
#   endif

# endif /* PN */


/* --- Macros to set/get/clear pending requests ---                                */

/* !!! DO NOT use Set* / Clr* in HW specific parts unless stated otherwise     !!! */
/* !!! Ensure data consistency when using Set* / Clr* by using interrupt locks !!! */

/* Check if ANY request is pending. Returns TRUE if at least one of the requests above is pending  */
# define CanTrcv_30_Tja1145_IsReqFlagPnd(index) (CanTrcv_30_Tja1145_Prob[index].requestState != CanTrcv_30_Tja1145_Req_None)

/* Generic macros. DO NOT use. Use the explicit macros instead. Behavior may change in future      */
# define CanTrcv_30_Tja1145_SetFlagReq(index, flag) CanTrcv_30_Tja1145_Prob[index].requestState   |= (flag)
# define CanTrcv_30_Tja1145_ClrFlagReq(index, flag) CanTrcv_30_Tja1145_Prob[index].requestState   &= ~((uint32)(flag))
# define CanTrcv_30_Tja1145_GetFlagReq(index, flag) ( CanTrcv_30_Tja1145_Prob[index].requestState &  (flag) )

/* Set/Get/Clear the currently requested operation mode */
#  define CanTrcv_30_Tja1145_ClrOpModeReq(index) ( CanTrcv_30_Tja1145_Prob[index].requestState &=  ~((uint32)CanTrcv_30_Tja1145_Req_OpModeMask) )
#  define CanTrcv_30_Tja1145_GetOpModeReq(index) ( CanTrcv_30_Tja1145_Prob[index].requestState & CanTrcv_30_Tja1145_Req_OpModeMask)
#  define CanTrcv_30_Tja1145_SetOpModeReq(index, mode) \
   CanTrcv_30_Tja1145_Prob[index].requestState &=  (~((uint32)CanTrcv_30_Tja1145_Req_OpModeMask)); \
   CanTrcv_30_Tja1145_Prob[index].requestState |=  (mode)

/* Set/Get/Clear a request to process a call to CanTrcv_30_Tja1145_CheckWakeup */
#  define CanTrcv_30_Tja1145_SetCbByBusFlagReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_CbByBusFlag)
#  define CanTrcv_30_Tja1145_ClrCbByBusFlagReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_CbByBusFlag)
#  define CanTrcv_30_Tja1145_GetCbByBusFlagReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_CbByBusFlag)

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/* Set/Get/Clear a request to process a call to CanTrcv_30_Tja1145_ClearTrcvWufFlag */
#  define CanTrcv_30_Tja1145_SetClrWufFlagReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_ClrWufFlag)
#  define CanTrcv_30_Tja1145_ClrClrWufFlagReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_ClrWufFlag)
#  define CanTrcv_30_Tja1145_GetClrWufFlagReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_ClrWufFlag)

/* Set/Get/Clear a request to process a call to CanTrcv_30_Tja1145_CheckWakeFlag */
#  define CanTrcv_30_Tja1145_SetChkWakFlagReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_ChkWakFlag)
#  define CanTrcv_30_Tja1145_ClrChkWakFlagReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_ChkWakFlag)
#  define CanTrcv_30_Tja1145_GetChkWakFlagReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_ChkWakFlag)

/* Set/Get/Clear a request to call CanIf_CanTrcv_ConfirmPnAvaibility from CanTrcv_30_Tja1145_GetStatusFlagsIndication */
#   define CanTrcv_30_Tja1145_SetConfirmPnAvailabilityReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_ConfirmPnAvailability)
#   define CanTrcv_30_Tja1145_ClrConfirmPnAvailabilityReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_ConfirmPnAvailability)
#   define CanTrcv_30_Tja1145_GetConfirmPnAvailabilityReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_ConfirmPnAvailability)

#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
#    if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
#     define CanTrcv_30_Tja1145_SetReInitPnReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_ReInitPn)
#     define CanTrcv_30_Tja1145_ClrReInitPnReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_ReInitPn)
#     define CanTrcv_30_Tja1145_GetReInitPnReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_ReInitPn)
#    endif
#    define CanTrcv_30_Tja1145_SetSyncSpiTxReq(index) CanTrcv_30_Tja1145_SetFlagReq(index, CanTrcv_30_Tja1145_Req_SyncSpiTx)
#    define CanTrcv_30_Tja1145_ClrSyncSpiTxReq(index) CanTrcv_30_Tja1145_ClrFlagReq(index, CanTrcv_30_Tja1145_Req_SyncSpiTx)
#    define CanTrcv_30_Tja1145_GetSyncSpiTxReq(index) CanTrcv_30_Tja1145_GetFlagReq(index, CanTrcv_30_Tja1145_Req_SyncSpiTx)
#   endif

# endif /* PN */


/* ********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 * ********************************************************************************************************************/
#define CANTRCV_30_TJA1145_IS_INIT                         1u
#define CANTRCV_30_TJA1145_IS_NOT_INIT                     0u

/* ********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 * ********************************************************************************************************************/
#define CanTrcv_EnterCritical() SchM_Enter_CanTrcv_30_Tja1145_CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0()
#define CanTrcv_LeaveCritical() SchM_Exit_CanTrcv_30_Tja1145_CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0()



#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
# define CanTrcv_DetReportError(apiId, errorId)  ((void)Det_ReportError((CANTRCV_30_TJA1145_MODULE_ID), (CANTRCV_30_TJA1145_INSTANCE_ID), (apiId), (errorId)))
#else
# define CanTrcv_DetReportError(apiId, errorId)
#endif


#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
#  define CanTrcv_ReportErrorNoTrcvControl(apiId) CanTrcv_DetReportError( (apiId), CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL)
#endif


/* If no errors should be reported */
#if defined(CanTrcv_ReportErrorNoTrcvControl)
#else
# define CanTrcv_ReportErrorNoTrcvControl(apiId)
#endif



# define CANTRCV_30_TJA1145_SF_WUP_BUS  0x0001u
# define CANTRCV_30_TJA1145_SF_WUP_PIN  0x0002u
# define CANTRCV_30_TJA1145_SF_WUP_POR  0x0004u
# define CANTRCV_30_TJA1145_SF_ERR_BUS  0x0100u
# define CANTRCV_30_TJA1145_SF_ERR_SYS  0x0200u
# define CANTRCV_30_TJA1145_SF_ERR_CFG  0x0400u

# define CANTRCV_30_TJA1145_GET_SF_INIT (CANTRCV_30_TJA1145_SF_WUP_BUS|CANTRCV_30_TJA1145_SF_WUP_PIN|CANTRCV_30_TJA1145_SF_WUP_POR|CANTRCV_30_TJA1145_SF_ERR_SYS|CANTRCV_30_TJA1145_SF_ERR_CFG)
# define CANTRCV_30_TJA1145_GET_SF_SETOPMODE (CANTRCV_30_TJA1145_SF_ERR_SYS|CANTRCV_30_TJA1145_SF_ERR_CFG)
# define CANTRCV_30_TJA1145_GET_SF_CBWAKEUPBYBUS (CANTRCV_30_TJA1145_SF_WUP_BUS|CANTRCV_30_TJA1145_SF_WUP_PIN|CANTRCV_30_TJA1145_SF_ERR_SYS)
# define CANTRCV_30_TJA1145_GET_SF_MAINFUNCTIONDIAGNOSTICS (CANTRCV_30_TJA1145_SF_ERR_BUS)
# define CANTRCV_30_TJA1145_GET_SF_MAINFUNCTION (CANTRCV_30_TJA1145_SF_WUP_PIN|CANTRCV_30_TJA1145_SF_WUP_BUS)

/* The macro CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON returns true if the
   given wakeup reason indicates an external wakeup event */
# if !defined(CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON)
#  if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
#   define CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON(wuReason)               \
                        ((wuReason) == CANTRCV_30_TJA1145_WU_BY_BUS)    || \
                        ((wuReason) == CANTRCV_30_TJA1145_WU_BY_PIN)    || \
                        ((wuReason) == CANTRCV_30_TJA1145_WU_BY_SYSERR)

#  else
#   define CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON(wuReason)               \
                        ((wuReason) == CANTRCV_30_TJA1145_WU_BY_PIN)    || \
                        ((wuReason) == CANTRCV_30_TJA1145_WU_BY_BUS)
#  endif
# endif /* !defined(CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON) */

#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
# define CANTRCV_30_TJA1145_IS_INITIALIZED(channel) \
                  ( (CanTrcv_30_Tja1145_IsInitialized == CANTRCV_30_TJA1145_IS_INIT) \
                    && (CanTrcv_30_Tja1145_Prob[channel].isInit == CANTRCV_30_TJA1145_IS_INIT) \
                  )
#endif



/* Wakeup events */
# define CanTrcv_30_Tja1145_StateWupIsBus(statusFlags)  (   ( ((statusFlags).Tes & CanTrcv_30_Tja1145_Tes_CW)   != 0x00u )      )

# define CanTrcv_30_Tja1145_StateWupIsPin(statusFlags)  (   ( ((statusFlags).Ecs & CanTrcv_30_Tja1145_Ecs_WPE)  != 0x00u )      )

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
# define CanTrcv_30_Tja1145_StateWupIsPor(statusFlags)  (   ( ((statusFlags).Ecs & CanTrcv_30_Tja1145_Ecs_SYSE) != 0x00u )  &&  \
                                                                ( ((statusFlags).Ses & CanTrcv_30_Tja1145_Ses_PO)   != 0x00u )      )
                                                                
# define CanTrcv_30_Tja1145_StateWupIsValid(statusFlags)    ( CanTrcv_30_Tja1145_StateWupIsBus(statusFlags) || \
                                                              CanTrcv_30_Tja1145_StateWupIsPin(statusFlags) )



/* Error events */
# define CanTrcv_30_Tja1145_StateErrIsBus(statusFlags)  (   ( ((statusFlags).Ecs & CanTrcv_30_Tja1145_Ecs_TRXE) != 0x00u )  &&  \
                                                                ( ((statusFlags).Tes & CanTrcv_30_Tja1145_Tes_CF)   != 0x00u )      )
                                                                
# define CanTrcv_30_Tja1145_StateErrIsSys(statusFlags)  (   ( ((statusFlags).Ts  & CanTrcv_30_Tja1145_Ts_CPNERR)!= 0x00u )      )

# define CanTrcv_30_Tja1145_StateErrIsCfg(statusFlags)  (   ( ((statusFlags).Ts  & CanTrcv_30_Tja1145_Ts_CPNS)  == 0x00u )      )

# define CANTRCV_30_TJA1145_CHECK_BAUDRATE(index)       ( ( (CanTrcv_GetBaudrate(index) == 0x02u) || \
                                                                (CanTrcv_GetBaudrate(index) == 0x03u) || \
                                                                (CanTrcv_GetBaudrate(index) == 0x05u) || \
                                                                (CanTrcv_GetBaudrate(index) == 0x07u)    \
                                                              ) ? E_OK : E_NOT_OK)

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
#  define CANTRCV_30_TJA1145_IS_SPI_FREE(index)     ((CanTrcv_30_Tja1145_FifoInfo[index].NumFree == CANTRCV_30_TJA1145_NUM_TASKS) && (!CanTrcv_30_Tja1145_IsReqFlagPnd(index)))
# endif
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

/* Possibility to overwrite the Spi_SyncTransmit API */
#if defined(CANTRCV_30_TJA1145_SPI_SYNC_TRANSMIT)
#else
# define CANTRCV_30_TJA1145_SPI_SYNC_TRANSMIT(Ret, Seq)  (Ret) = Spi_SyncTransmit(Seq)
# define CANTRCV_30_TJA1145_SPI_ENABLE_SYNC_DEFAULT_IMPL

/* The Spi Mainfunction can be specified here */
# if defined(CANTRCV_30_TJA1145_SPI_MAINFUNCTION)
# else
#  define CANTRCV_30_TJA1145_SPI_MAINFUNCTION()      Spi_MainFunction_Driving()
# endif
#endif

/* ************ Register layout *************/

/*! 
 * Internal comment removed. *
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
/*! Main control registers */
#define CanTrcv_30_Tja1145_Mc   0x01u                   /*!< Mode Control Register    */
#define CanTrcv_30_Tja1145_Ms   0x03u                   /*!< Main Status Register     */
#define CanTrcv_30_Tja1145_See  0x04u                   /*!< System Event Enable      */
#define CanTrcv_30_Tja1145_Mc0  0x06u                   /*!< Memory control 0 (GP)    */
#define CanTrcv_30_Tja1145_Mc1  0x07u                   /*!< Memory control 1 (GP)    */
#define CanTrcv_30_Tja1145_Mc2  0x08u                   /*!< Memory control 2 (GP)    */
#define CanTrcv_30_Tja1145_Mc4  0x09u                   /*!< Memory control 4 (GP)    */
#define CanTrcv_30_Tja1145_Lc   0x0Au                   /*!< Lock control             */

/*! Transceiver Control registers */
#define CanTrcv_30_Tja1145_Cc   0x20u                   /*!< CAN Control              */
#define CanTrcv_30_Tja1145_Ts   0x22u                   /*!< Transceiver Status       */
#define CanTrcv_30_Tja1145_Tee  0x23u                   /*!< Transceiver Event Enable */

/*! Partial Networking Configuration Registers */
#define CanTrcv_30_Tja1145_Dr   0x26u                   /*!< Data Rate Register       */
#define CanTrcv_30_Tja1145_Id0  0x27u                   /*!< Identifier Register 0    */
#define CanTrcv_30_Tja1145_Id1  0x28u                   /*!< Identifier Register 1    */
#define CanTrcv_30_Tja1145_Id2  0x29u                   /*!< Identifier Register 2    */
#define CanTrcv_30_Tja1145_Id3  0x2au                   /*!< Identifier Register 3    */
#define CanTrcv_30_Tja1145_Mk0  0x2bu                   /*!< Mask Register 0          */
#define CanTrcv_30_Tja1145_Mk1  0x2cu                   /*!< Mask Register 1          */
#define CanTrcv_30_Tja1145_Mk2  0x2du                   /*!< Mask Register 2          */
#define CanTrcv_30_Tja1145_Mk3  0x2eu                   /*!< Mask Register 3          */
#define CanTrcv_30_Tja1145_Fc   0x2fu                   /*!< Frame Control Register   */
#define CanTrcv_30_Tja1145_Db0  0x68u                   /*!< Data Byte Registr 0      */
#define CanTrcv_30_Tja1145_Db1  0x69u                   /*!< Data Byte Registr 1      */
#define CanTrcv_30_Tja1145_Db2  0x6au                   /*!< Data Byte Registr 2      */
#define CanTrcv_30_Tja1145_Db3  0x6bu                   /*!< Data Byte Registr 3      */
#define CanTrcv_30_Tja1145_Db4  0x6cu                   /*!< Data Byte Registr 4      */
#define CanTrcv_30_Tja1145_Db5  0x6du                   /*!< Data Byte Registr 5      */
#define CanTrcv_30_Tja1145_Db6  0x6eu                   /*!< Data Byte Registr 6      */
#define CanTrcv_30_Tja1145_Db7  0x6fu                   /*!< Data Byte Registr 7      */

/*! WAKE Pin registers */
#define CanTrcv_30_Tja1145_Wps  0x4bu                   /*!< WAKE pin Status Register */
#define CanTrcv_30_Tja1145_Wpe  0x4cu                   /*!< WAKE pin Enable          */

/*! Event capturing registers */
#define CanTrcv_30_Tja1145_Ecs  0x60u                   /*!< Event Capture Status     */
#define CanTrcv_30_Tja1145_Ses  0x61u                   /*!< System Event Status      */
#define CanTrcv_30_Tja1145_Tes  0x63u                   /*!< Transceiver Event Status */
#define CanTrcv_30_Tja1145_Wes  0x64u                   /*!< WAKE pin Event Status    */

/*! Identification Register */
#define CanTrcv_30_Tja1145_Isr  0x7eu                   /*!< Identification Status Register = 0x70 */



/*! Mc Register */
#define CanTrcv_30_Tja1145_Mc_MC_Mask     0x07u         /*!< Mode Control Mask              */  
#define CanTrcv_30_Tja1145_Mc_MC_Sleep    0x01u         /*!< Sleep Mode                     */
#define CanTrcv_30_Tja1145_Mc_MC_Standby  0x04u         /*!< Standby Mode                   */
#define CanTrcv_30_Tja1145_Mc_MC_Normal   0x07u         /*!< Normal Mode                    */

/*! Ts Register */
#define CanTrcv_30_Tja1145_Ts_CFS         0x01u         /*!< CAN Failures Status            */
#define CanTrcv_30_Tja1145_Ts_CBSS        0x08u         /*!< CAN Bus Silence Status         */
#define CanTrcv_30_Tja1145_Ts_COSCS       0x10u         /*!< CAN Oscillator Status          */
#define CanTrcv_30_Tja1145_Ts_CPNS        0x20u         /*!< CAN Partial Networking Status  */
#define CanTrcv_30_Tja1145_Ts_CPNERR      0x40u         /*!< CAN Partial Networking Error   */

/*! Tee Register */
#define CanTrcv_30_Tja1145_Tee_CWE        0x01u         /*!< CAN wake-up capture enable     */
#define CanTrcv_30_Tja1145_Tee_CFE        0x02u         /*!< CAN failure capture enable     */
#define CanTrcv_30_Tja1145_Tee_CBSE       0x10u         /*!< CAN bus silence capture enable */

/*! CC Register */
#define CanTrcv_30_Tja1145_Cc_CMC_Mask    0x03u         /*!< CAN Mode control mask          */
#define CanTrcv_30_Tja1145_Cc_CMC_Offline 0x00u         /*!< CMC = Offline                  */
#define CanTrcv_30_Tja1145_Cc_CMC_Normal  0x01u         /*!< CMC = Normal                   */
#define CanTrcv_30_Tja1145_Cc_CMC_Listen  0x03u         /*!< CMC = Listen                   */
#define CanTrcv_30_Tja1145_Cc_CPNC        0x10u         /*!< CAN Partial Networking Control */
#define CanTrcv_30_Tja1145_Cc_PNCOK       0x20u         /*!< Partiion Networking Config OK  */
#define CanTrcv_30_Tja1145_Cc_CFDC        0x40u         /*!< CAN FD tolerance enabled       */

/*! Wpe register */
#define CanTrcv_30_Tja1145_Wpe_WPFE       0x01u         /*!< Wake pin falling edge capture  */
#define CanTrcv_30_Tja1145_Wpe_WPRE       0x02u         /*!< Wake pin rising edge capture   */

/*! Ecs Register */
#define CanTrcv_30_Tja1145_Ecs_SYSE       0x01u         /*!< System event status            */
#define CanTrcv_30_Tja1145_Ecs_TRXE       0x04u         /*!< Transceiver event status       */
#define CanTrcv_30_Tja1145_Ecs_WPE        0x08u         /*!< Wake pin event status          */

/*! Ses Register */
#define CanTrcv_30_Tja1145_Ses_SPIF       0x02u         /*!< SPI failure event              */
#define CanTrcv_30_Tja1145_Ses_OTW        0x04u         /*!< Overtemperature warning event  */
#define CanTrcv_30_Tja1145_Ses_PO         0x10u         /*!< Power-on event                 */

/*! Tes Register */
#define CanTrcv_30_Tja1145_Tes_CW         0x01u         /*!< CAN Wake-up event              */
#define CanTrcv_30_Tja1145_Tes_CF         0x02u         /*!< CAN failure event              */
#define CanTrcv_30_Tja1145_Tes_CBS        0x10u         /*!< CAN bus silence event          */
#define CanTrcv_30_Tja1145_Tes_PNFDE      0x20u         /*!< PN Frame Detection Error event */

/*! Wes Register */
#define CanTrcv_30_Tja1145_Wes_WPF        0x01u         /*!< WAKE pin falling edge event    */
#define CanTrcv_30_Tja1145_Wes_WPR        0x02u         /*!< WAKE pin rising edge event     */


/* Build an address */
#define CanTrcv_30_Tja1145_MkAdr(adr,ro) (uint8)( (( (adr)<<1 )&0xFEu) | (ro) )

/* Default flags for WAKE Pin */
#if defined(CANTRCV_30_TJA1145_WAKE_PIN_EVENT_RISING)
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_RISING STD_ON
#endif
#if defined(CANTRCV_30_TJA1145_WAKE_PIN_EVENT_FALLING)
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_FALLING STD_ON
#endif

/* Determines if any Wakeup by Pin event is configured */
#if ((CANTRCV_30_TJA1145_WAKE_PIN_EVENT_RISING == STD_ON) || (CANTRCV_30_TJA1145_WAKE_PIN_EVENT_FALLING == STD_ON))
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENTS STD_ON
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENTS STD_OFF
#endif

/* Macro to get if Wakeup by Pin is used or not */
#if (CANTRCV_30_TJA1145_WAKE_PIN_EVENTS == STD_ON)
# define CanTrcvCfg_IsWakeupByPinUsed() (TRUE != FALSE)
#else
# define CanTrcvCfg_IsWakeupByPinUsed() (TRUE == FALSE)
#endif

#if (CANTRCV_30_TJA1145_WAKE_PIN_EVENT_FALLING == STD_ON)
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_FALLING CanTrcv_30_Tja1145_Wes_WPF
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_FALLING 0x00u
#endif
#if (CANTRCV_30_TJA1145_WAKE_PIN_EVENT_RISING == STD_ON)
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_RISING CanTrcv_30_Tja1145_Wes_WPR
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_RISING 0x00u
#endif


#if defined(CANTRCV_30_TJA1145_WAKE_PIN_SETTING)
#else
# define CANTRCV_30_TJA1145_WAKE_PIN_SETTING(channel) (CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_FALLING|CANTRCV_30_TJA1145_WAKE_PIN_EVENT_VAL_RISING)
#endif


/* --- Spi requests --- */
#define CANTRCV_30_TJA1145_REQ_NONE              0x00u
#define CANTRCV_30_TJA1145_REQ_RW_STATUS         0x01u
#define CANTRCV_30_TJA1145_REQ_RW_MODE           0x02u
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) /* In order to ensure consistent usage. */
# define CANTRCV_30_TJA1145_REQ_RW_IDMASKDB      0x03u
#endif
       
/* --- ReadDiagState --- */
#define CANTRCV_30_TJA1145_RD_DIAG_STATE_IDLE    0x00u
#define CANTRCV_30_TJA1145_RD_DIAG_STATE_PENDING 0x01u
#define CANTRCV_30_TJA1145_RD_DIAG_STATE_WAIT    0x02u
#define CANTRCV_30_TJA1145_RD_DIAG_STATE_FAILED  0xFFu
       
/* --- RwStatus request types --- */
#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)) /* In order to ensure consistent usage. */
# define CANTRCV_30_TJA1145_RT_RD_STATUS         0x01u
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) /* In order to ensure consistent usage. */
# define CANTRCV_30_TJA1145_RT_CLR_WUF           0x02u
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */
#define CANTRCV_30_TJA1145_RT_CLR_ALL            0x03u
       
/* --- Task handling --- */
/* Tasks IDs */
#define CANTRCV_30_TJA1145_TASK_ID_CHANGE_OP_MODE     0x00u

#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
# define CANTRCV_30_TJA1145_TASK_ID_RD_STATUS         0x01u
#endif

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
# define CANTRCV_30_TJA1145_TASK_ID_CLR_WUF_FLAG      0x02u
# if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
#  define CANTRCV_30_TJA1145_TASK_ID_REINIT           0x03u
#  define CANTRCV_30_TJA1145_NUM_TASKS                0x04u
# else
#  define CANTRCV_30_TJA1145_NUM_TASKS                0x03u
# endif /* CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON */
#else
# if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
#  define CANTRCV_30_TJA1145_NUM_TASKS                0x02u
# else
#  define CANTRCV_30_TJA1145_NUM_TASKS                0x01u
# endif
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

/* Main states */
#define CANTRCV_30_TJA1145_TASK_STOPPED        0x00u
#define CANTRCV_30_TJA1145_TASK_WAIT_START     0x01u
#define CANTRCV_30_TJA1145_TASK_RUNNING        0x02u


/* SubStates, ACTIONs */
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
/* CMT == ChangeModeTask */
/* SUBSTATEs */
# define CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_STATUS    0x00u
# define CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_STATUS   0x01u
# define CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_MODE      0x02u
# define CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_MODE     0x03u
/* ACTIONs: 1st-nibble: SUBSTATE, 2nd-nibble: EVENT */
# define CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_STATUS      0x0Eu /* Action fulfillment: CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_STATUS && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
# define CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_STATUS     0x13u /* Action fulfillment: CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_STATUS && CANTRCV_30_TJA1145_TASK_EV_RW_STATUS */
# define CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_MODE        0x2Eu /* Action fulfillment: CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_MODE && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
# define CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_MODE       0x34u /* Action fulfillment: CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_MODE && CANTRCV_30_TJA1145_TASK_EV_RW_MODE */

/* ANYT == any task */
/* SUBSTATEs */
# define CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE            0xEEu
# define CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED          0xFFu
/* ACTIONs */
# define CANTRCV_30_TJA1145_ANYT_ACTION_START_TASK        0xDDu /* Action fulfillment: CANTRCV_30_TJA1145_TASK_STOPPED && CANTRCV_30_TJA1145_TASK_EV_START */
# define CANTRCV_30_TJA1145_ANYT_ACTION_NONE              0xEEu /* Nothing to do */
# define CANTRCV_30_TJA1145_ANYT_ACTION_FAILED            0xFFu /* Execution of task has failed */


# if ((CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON))
/* RIT == ReInitTask */
/* SUBSTATEs */
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_IDMASK   0x00u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_IDMASK  0x01u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_IDMASK   0x02u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_IDMASK  0x03u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_DB       0x04u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_DB      0x05u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_DB       0x06u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_DB      0x07u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RW_MODE     0x08u
#  define CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RW_MODE    0x09u
/* ACTIONs: 1st-nibble: SUBSTATE, 2nd-nibble: EVENT */
#  define CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_IDMASK     0x0Eu /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_IDMASK && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
#  define CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_IDMASK    0x15u /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_IDMASK && CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB */
#  define CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_IDMASK     0x2Eu /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_IDMASK && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
#  define CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_IDMASK    0x35u /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_IDMASK && CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB */
#  define CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_DB         0x4Eu /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_DB && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
#  define CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_DB        0x55u /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_DB && CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB */
#  define CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_DB         0x6Eu /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_DB && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
#  define CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_DB        0x75u /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_DB && CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB */
#  define CANTRCV_30_TJA1145_RIT_ACTION_REQ_RW_MODE       0x8Eu /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RW_MODE && CANTRCV_30_TJA1145_TASK_EV_CYCLE */
#  define CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RW_MODE      0x94u /* Action fulfillment: CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RW_MODE && CANTRCV_30_TJA1145_TASK_EV_RW_MODE */
# endif /* ((CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)) */
#endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */

/* Events */
#define CANTRCV_30_TJA1145_TASK_EV_START                  0x02u
#define CANTRCV_30_TJA1145_TASK_EV_RW_STATUS              0x03u
#define CANTRCV_30_TJA1145_TASK_EV_RW_MODE                0x04u
#define CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB            0x05u
#define CANTRCV_30_TJA1145_TASK_EV_CYCLE                  0x0Eu
#define CANTRCV_30_TJA1145_TASK_EV_NONE                   0xFFu     


/* --- Synchronous / asynchronous access handler --- */
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
# define CanTrcv_30_Tja1145_StartTaskChangeOpMode(index)           CanTrcv_30_Tja1145_StartTask((index), CANTRCV_30_TJA1145_TASK_ID_CHANGE_OP_MODE)
# define CanTrcv_30_Tja1145_StartTaskRdStatus(index)               CanTrcv_30_Tja1145_StartTask((index), CANTRCV_30_TJA1145_TASK_ID_RD_STATUS)

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
#  define CanTrcv_30_Tja1145_StartTaskClrWufFlag(index)            CanTrcv_30_Tja1145_StartTask((index), CANTRCV_30_TJA1145_TASK_ID_CLR_WUF_FLAG)
#  if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
#   define CanTrcv_30_Tja1145_StartTaskReInit(index)               CanTrcv_30_Tja1145_StartTask((index), CANTRCV_30_TJA1145_TASK_ID_REINIT)
#  endif /* (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */
# endif /* (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */

#else /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */

# define CanTrcv_30_Tja1145_StartTaskChangeOpMode(CanTrcvIndex)    CanTrcv_30_Tja1145_ChangeModeTaskSync(CanTrcvIndex)
# define CanTrcv_30_Tja1145_StartTaskRdStatus(CanTrcvIndex)        CanTrcv_30_Tja1145_RdStatusTask(CanTrcvIndex)

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
#  define CanTrcv_30_Tja1145_StartTaskClrWufFlag(CanTrcvIndex)     CanTrcv_30_Tja1145_ClrWufFlagTask(CanTrcvIndex)
#  if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
#   define CanTrcv_30_Tja1145_StartTaskReInit(CanTrcvIndex)        CanTrcv_30_Tja1145_ReInitTaskSync(CanTrcvIndex)
#  endif
# endif

#endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */

/* Data access macros */
#define CanTrcv_GetBaudrate(Index)                   CanTrcv_30_Tja1145_GetBaudrateOfPnCfg(Index)
#define CanTrcv_GetCanId0(Index)                     CanTrcv_30_Tja1145_GetCanId0OfPnCfg(Index)
#define CanTrcv_GetCanId1(Index)                     CanTrcv_30_Tja1145_GetCanId1OfPnCfg(Index)
#define CanTrcv_GetCanId2(Index)                     CanTrcv_30_Tja1145_GetCanId2OfPnCfg(Index)
#define CanTrcv_GetCanId3(Index)                     CanTrcv_30_Tja1145_GetCanId3OfPnCfg(Index)
#define CanTrcv_GetCanIdMask0(Index)                 CanTrcv_30_Tja1145_GetCanIdMask0OfPnCfg(Index)
#define CanTrcv_GetCanIdMask1(Index)                 CanTrcv_30_Tja1145_GetCanIdMask1OfPnCfg(Index)
#define CanTrcv_GetCanIdMask2(Index)                 CanTrcv_30_Tja1145_GetCanIdMask2OfPnCfg(Index)
#define CanTrcv_GetCanIdMask3(Index)                 CanTrcv_30_Tja1145_GetCanIdMask3OfPnCfg(Index)
#define CanTrcv_GetFrameControl(Index)               CanTrcv_30_Tja1145_GetFrameControlOfPnCfg(Index)
#define CanTrcv_GetDataMask0(Index)                  CanTrcv_30_Tja1145_GetDataMask0OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask1(Index)                  CanTrcv_30_Tja1145_GetDataMask1OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask2(Index)                  CanTrcv_30_Tja1145_GetDataMask2OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask3(Index)                  CanTrcv_30_Tja1145_GetDataMask3OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask4(Index)                  CanTrcv_30_Tja1145_GetDataMask4OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask5(Index)                  CanTrcv_30_Tja1145_GetDataMask5OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask6(Index)                  CanTrcv_30_Tja1145_GetDataMask6OfPnPayloadCfg(Index)
#define CanTrcv_GetDataMask7(Index)                  CanTrcv_30_Tja1145_GetDataMask7OfPnPayloadCfg(Index)
#define CanTrcv_GetCanTrcvSeqRWDataLarge(Index)      CanTrcv_30_Tja1145_GetCanTrcvSeqRWDataLargeOfSpiSequenceCfg(Index)
#define CanTrcv_GetCanTrcvSeqRWDataMedium(Index)     CanTrcv_30_Tja1145_GetCanTrcvSeqRWDataMediumOfSpiSequenceCfg(Index)
#define CanTrcv_GetCanTrcvSpiChRWData_0(Index)       CanTrcv_30_Tja1145_GetCanTrcvSpiChRWData_0OfSpiChannelCfg(Index)
#define CanTrcv_GetCanTrcvSpiChRWData_1(Index)       CanTrcv_30_Tja1145_GetCanTrcvSpiChRWData_1OfSpiChannelCfg(Index)
#define CanTrcv_GetCanTrcvSpiChRWData_2(Index)       CanTrcv_30_Tja1145_GetCanTrcvSpiChRWData_2OfSpiChannelCfg(Index)
#define CanTrcv_GetCanTrcvSpiChRWData_3(Index)       CanTrcv_30_Tja1145_GetCanTrcvSpiChRWData_3OfSpiChannelCfg(Index)

#define CanTrcv_IsFdToleranceEnabled(Index)          CanTrcv_30_Tja1145_IsFdToleranceEnabled(Index)

#define CANTRCV_30_TJA1145_IS_MAIN_FCT_REQ(index)     (!CanTrcv_30_Tja1145_IsReqFlagPnd(index))


/* --- Emulated Sleep mode --- */
#  if ((CANTRCV_30_TJA1145_WAKE_PIN_EVENTS == STD_OFF) && (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_OFF))
#   define CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT STD_ON
#  else
#   define CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT STD_OFF
#  endif

/* ********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 * ********************************************************************************************************************/


#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
/* Types necessary for task handling */
typedef Std_ReturnType(*CanTrcv_30_Tja1145_TaskFunctionType) (uint8 CanTrcvIndex, uint8 event, uint8 taskState);

typedef struct
{
  CanTrcv_30_Tja1145_TaskFunctionType TaskFunction;
} CanTrcv_30_Tja1145_TaskInfoType;
#endif

typedef struct
{
  uint8 reg; /* Value of register / address to access (LSB signals whether write ('0') or read access ('1') */
  uint8 size; /* Length of payload (the one byte required for register/address excluded) */
  P2CONST(uint8, TYPEDEF, CANTRCV_30_TJA1145_APPL_VAR) ptr;

} CanTrcv_30_Tja1145_SpiTxBlockType;

typedef struct
{
  CanTrcv_30_Tja1145_SpiTxBlockType block[4];
  uint8 numberOfBlocks; /* Signals how many "blocks" are / shall be used */
} CanTrcv_30_Tja1145_SpiTxBlockSeqType;

#define rdwr_block(bk, r, sz, p) \
  (bk).reg = (r); (bk).size = (sz); (bk).ptr = (P2CONST(uint8, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR))(p)

#define write_block(bk, r, sz, p) rdwr_block(bk, CanTrcv_30_Tja1145_MkAdr(r, 0u), sz, p)
#define read_block(bk, r, sz, p) rdwr_block(bk, CanTrcv_30_Tja1145_MkAdr(r, 1u), sz, p)
  

  


/* ********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 * ********************************************************************************************************************/

#define CANTRCV_30_TJA1145_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
 /*
 * Specifies whether the CanTrcv module is initialized.
 */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
CANTRCV_30_TJA1145_LOCAL VAR(uint8, CANTRCV_30_TJA1145_VAR_INIT) CanTrcv_30_Tja1145_IsInitialized = CANTRCV_30_TJA1145_IS_NOT_INIT;
# endif

#define CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */



#define CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*
 * ! In following variable CAN transceiver channel specific settings are stored e.g. the wake-up reason or the current operating mode. 
 * For more information see the description of type: CanTrcv_30_Tja1145_Prob_Type.
 */
VAR(CanTrcv_30_Tja1145_Prob_Type, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_Prob[CANTRCV_30_TJA1145_MAX_CHANNEL]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1145_3408 */

/* These vars are not static to allow easy debugging */

#define CANTRCV_30_TJA1145_SPI_BUFFER_SIZE 14

VAR(CanTrcv_SpiDataType, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_SpiInBuffer[CANTRCV_30_TJA1145_MAX_CHANNEL][CANTRCV_30_TJA1145_SPI_BUFFER_SIZE]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1145_3408 */
VAR(CanTrcv_SpiDataType, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_SpiOutBuffer[CANTRCV_30_TJA1145_MAX_CHANNEL][CANTRCV_30_TJA1145_SPI_BUFFER_SIZE]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1145_3408 */

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
CANTRCV_30_TJA1145_LOCAL VAR(CanTrcv_30_Tja1145_TaskStateType, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_ScheduleFifo[CANTRCV_30_TJA1145_MAX_CHANNEL][CANTRCV_30_TJA1145_NUM_TASKS];
CANTRCV_30_TJA1145_LOCAL VAR(CanTrcv_30_Tja1145_FifoInfoType, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_FifoInfo[CANTRCV_30_TJA1145_MAX_CHANNEL];
CANTRCV_30_TJA1145_LOCAL VAR(uint8, CANTRCV_30_TJA1145_VAR_NOINIT) CanTrcv_30_Tja1145_TaskActive[CANTRCV_30_TJA1145_MAX_CHANNEL][CANTRCV_30_TJA1145_NUM_TASKS];
#endif

#if (CANTRCV_30_TJA1145_USE_INIT_POINTER == STD_ON)
/* ! In following variable the configuration is stored during the initialization of the CAN transceiver driver in case of a Post-build loadable / selectable configuration. */
CANTRCV_30_TJA1145_LOCAL P2CONST(CanTrcv_30_Tja1145_ConfigType, CANTRCV_30_TJA1145_VAR_NOINIT, CANTRCV_30_TJA1145_INIT_DATA) CanTrcv_30_Tja1145_ConfigDataPtr;
#endif

#define CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define CANTRCV_30_TJA1145_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  LOCAL FUNCTIONS
 * ********************************************************************************************************************/
/* Local function declarations */

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
#  if (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_VerifyData
 **********************************************************************************************************************/
/*! \brief       Verifies if all PN-specific settings were written correctly to CAN transceiver hardware during the initialization.
 *  \details     This function has no service id. Called by transceiver driver within: CanTrcv_30_Tja1145_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Read PN-specific settings from CAN transceiver hardware correspond to written ones.
 *               E_NOT_OK: Read PN-specific settings from CAN transceiver hardware differ from written ones.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) and (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_VerifyData(uint8 CanTrcvIndex);
#  endif /* SPI_COMMENT */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckWakeFlagIndication
 **********************************************************************************************************************/
/*! \brief       Indication to be called by SeqEndNotification of the SPI-driver.
 *  \details     This function has no service id. Called by transceiver driver within: CanTrcv_30_Tja1145_CheckWakeFlag().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     TASK|ISR
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckWakeFlagIndication(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ClearTrcvWufFlagIndication
 **********************************************************************************************************************/
/*! \brief       Indication to be called by SeqEndNotification of the SPI-driver.
 *  \details     This function has no service id. Called by transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClearTrcvWufFlagIndication(uint8 CanTrcvIndex);
# endif /* PN */


#  if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CbWakeupByBusIndication
 **********************************************************************************************************************/
/*! \brief       Has to be called if the request to CbWakeupByBus has completed.
 *  \details     This function has no service id. Called by transceiver driver within: CanTrcv_30_Tja1145_CheckWakeup() and LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CbWakeupByBusIndication(uint8 CanTrcvIndex);
#  endif


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetStatusFlagsIndication
 **********************************************************************************************************************/
/*! \brief       Handles the storage and usage of status flags.
 *  \details     This function has no service id. Called by SPI driver / transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetStatusFlagsIndication(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_TrcvModeIndication
 **********************************************************************************************************************/
/*! \brief       Indication to be called by SeqEndNotification of the SPI-driver.
 *  \details     Updates the internal mode state variable of transceiver channel (CanTrcvIndex) and notifies the CanIf.
 *               This function has no service id. Called by transceiver driver within: CanTrcv_30_Tja1145_SetOpMode() and LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   modeSet: TRUE The requested mode was set, FALSE the requested mode was NOT set.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_TrcvModeIndication(uint8 CanTrcvIndex, boolean modeSet);


#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
#   if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetSyncSpiTxSem
 **********************************************************************************************************************/
/*! \brief       Locks the SPI for synchronous transmission in case of asynchronous SPI is configured.
 *  \details     This function has no service id. In case of the API returns TRUE the SPI interface for synchronous transmission 
 *               can be used otherwise NOT. After usage of SPI for synchronous transmission the SPI must be released by usage 
 *               of API CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      TRUE: Locking of SPI for synchronous transmission succeeded.
 *               FALSE: Locking of SPI for synchronous transmission failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) && (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(boolean, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetSyncSpiTxSem(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem
 **********************************************************************************************************************/
/*! \brief       To be used to release the lock of SPI for synchronous transmission in case of asynchronous 
 *               SPI is configured.
 *  \details     This function has no service id.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) && (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(uint8 CanTrcvIndex);
#   endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ProcessNextOpModeReq
 **********************************************************************************************************************/
/*! \brief       Verifies if another mode change was requested after the last one.
 *  \details     This function has no service id.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Another mode change was requested after the last one. Process the new one.
 *               E_NOT_OK: No other mode change was requested after the last one.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ProcessNextOpModeReq(uint8 CanTrcvIndex);
#  endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF */

#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReportWakeup
 **********************************************************************************************************************/
/*! \brief       Reports the wake-up reason to the upper layer.
 *  \details     This function has no service id. Called by transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReportWakeup(uint8 CanTrcvIndex);
#endif

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! \brief       LL: Initializes the LL-specific channel data of the CAN transceiver hardware.
 *  \details     This function is called for ALL channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               Called by transceiver driver within: CanTrcv_30_Tja1145_Init().
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_LL_InitChannel
 **********************************************************************************************************************/
/*! \brief       LL: Initializes the LL-specific channel data of the CAN transceiver hardware.
 *  \details     This function is called only for "used" (== activated) channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *               Called by transceiver driver within: CanTrcv_30_Tja1145_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_LL_InitChannel(uint8 CanTrcvIndex);

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_InitSubInitPn
 **********************************************************************************************************************/
/*! \brief       Initializes the PN-data of the CAN transceiver hardware.
 *  \details     This function is called only for "used" (== activated) channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *               Called by transceiver driver within: CanTrcv_30_Tja1145_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   getStatusFlagRetVal: Status of determination of CAN transceiver HW status flags.
 *  \param[in]   pnEnabled: Status of partial networking within the configuration. TRUE: enabled, FALSE: disabled.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_InitSubInitPn(uint8 CanTrcvIndex, Std_ReturnType getStatusFlagRetVal, boolean pnEnabled);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckPnAvailability
 **********************************************************************************************************************/
/*! \brief       Checks whether PN-functionality is available by HW or not and adapts the internal state 
*                variable accordingly.
 *  \details     The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1145_MAX_CHANNEL.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckPnAvailability(uint8 CanTrcvIndex);
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


#if (CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeWaitTime
 **********************************************************************************************************************/
/*! \brief       Waits actively in order to ensure successful mode transition.
 *  \details     This function has no service id. 
 *  \param[in]   currentOpMode: Current operating mode of the CAN transceiver.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeWaitTime(CanTrcv_30_Tja1145_TrcvModeType currentOpMode);
#endif /* CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeNormal
 **********************************************************************************************************************/
/*! \brief       Execute mode transition to NORMAL.
 *  \details     This function has no service id.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Change of operation mode to NORMAL was successful.
 *  \return      E_NOT_OK: Change of operation mode has failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      ANY
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeNormal(uint8 CanTrcvIndex);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeStandby
 **********************************************************************************************************************/
/*! \brief       Execute mode transition to STANDBY.
 *  \details     This function has no service id.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Change of operation mode to STANDBY was successful.
 *  \return      E_NOT_OK: Change of operation mode has failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      ANY
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeStandby(uint8 CanTrcvIndex);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeSleep
 **********************************************************************************************************************/
/*! \brief       Execute mode transition to SLEEP.
 *  \details     This function has no service id.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Change of operation mode to SLEEP was successful.
 *  \return      E_NOT_OK: Change of operation mode has failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      ANY
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeSleep(uint8 CanTrcvIndex);



/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_CmtActionReqRwStatus
 **********************************************************************************************************************/
/*! \brief       This API requests a read-access to status-flags of CAN transceiver HW.
 *  \details     In addition due to read-access to status-flags they are cleared. This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]   doSync: <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Read-access to status-flags accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Read-access to status-flags rejected / failed.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) or (<doSync> == TRUE) else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionReqRwStatus(uint8 CanTrcvIndex, boolean doSync);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CmtActionReqRwMode
 **********************************************************************************************************************/
/*! \brief       This API requests write-read-access to Mode-registers of CAN transceiver HW.
 *  \details     The mentioned Mode-registers are: CAN-control and Mode-control.
 *               Called by transceiver driver within CanTrcv_30_Tja1145_ChangeModeTaskAsync().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   doSync: <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Write-read-access to Mode-registers accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Write-read-access to Mode-registers rejected / failed.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>
 *  \synchronous TRUE if doSync == TRUE else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionReqRwMode(uint8 CanTrcvIndex, boolean doSync);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_VerifyOpMode
 **********************************************************************************************************************/
/*! \brief       Verifies if the requested operating mode was successfully set in HW.
 *  \details     Just compares register values to be set with read ones.
 *               Called by transceiver driver within CanTrcv_30_Tja1145_ChangeModeTask<Synch/Asynch>.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: The requested operating mode was set successfully.
 *               E_PENDING: A new another operating mode change was requested in between. (only in case of asynchronous SPI-interface)
 *               E_NOT_OK: The requested operating mode was NOT set.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_VerifyOpMode(uint8 CanTrcvIndex);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_CmtActionWaitRwMode
 **********************************************************************************************************************/
/*! \brief        This function verifies if the requested mode change was executed successfully.
 *  \details      If verification succeeds higher layer (CanIf) is indicated. This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of CAN transceiver channel
 *  \return       E_OK: Verification passed. The requested operating mode change was set.
 *                E_PENDING: Verification was omitted because the operating mode change was rescheduled in between and 
 *                hence is still in process. (only in case of asynchronous SPI-interface)
 *                E_NOT_OK: Verification failed. The requested operating mode change was NOT set.
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>
 *  \synchronous  TRUE
 *  \config       -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionWaitRwMode(uint8 CanTrcvIndex);


#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ChangeModeTaskSync
 **********************************************************************************************************************/
/*! \brief        Task to change the operation mode.
 *  \details      This function changes the current operation mode in synchronous manner. This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CAN transceiver channel
 *  \return       E_OK: The requested operating mode was set successfully.
 *                E_NOT_OK: The requested operating mode was NOT set / an error occurred.
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  FALSE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ChangeModeTaskSync(uint8 CanTrcvIndex);

#else /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */

/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_StartTask
 **********************************************************************************************************************/
/*! \brief        This API tries to start the task with ID <TaskId>.
 *  \details      If the same task (<TaskId>) was already scheduled or is executed this API returns E_PENDING. 
 *                If the execution slot is blocked (= another task has state RUNNING) the task is stored at the
 *                end of the schedule-FIFO and is scheduled after all preceding tasks had finished. This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CanTrcv
 *  \param[in]    TaskId: ID of the task to be rescheduled.
 *  \return       E_OK: Task was scheduled successfully.
 *                E_PENDING: The same task was already scheduled. Higher level has to decide what to do.
 *                E_NOT_OK: A critical error occurred. The task can NOT be executed (should always lead to a DEM event in the caller).
 *  \pre          - 
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_StartTask(uint8 CanTrcvIndex, uint8 TaskId);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ReSchedule
 **********************************************************************************************************************/
/*! \brief        Reschedules a task that has finished or is in a consistent state.
 *  \details      This API is called internally. The rescheduled task is executed directly afterwards, without respecting 
 *                the current schedule-FIFO.
 *  \param[in]    CanTrcvIndex: CAN transceiver channel.
 *  \param[in]    TaskId: Index of the task to be rescheduled.
 *  \return       E_OK: Rescheduling succeeded. 
 *                E_NOT_OK: Rescheduling failed. 
 *  \pre          The task with ID TaskId is scheduled currently.
 *                Must only be called within the task-function which corresponds to value of <TaskId>.
 *                Return value of the task must be STOPPED.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReSchedule(uint8 CanTrcvIndex, uint8 TaskId);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_Schedule
 **********************************************************************************************************************/
/*! \brief        Schedules the event to the currently active task.
 *  \details      If event is CYCLE and there is at least one task in the schedule-FIFO this function starts the next pending task.
 *                This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CanTrcv
 *  \param[in]    event: Event that shall be processed
 *  \return       E_OK: Scheduling was successful. 
 *                E_NOT_OK: An error occurred.
 *  \pre          -
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_Schedule(uint8 CanTrcvIndex, uint8 event);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_AnyTaskConditionalContinue
 **********************************************************************************************************************/
/*! \brief        This function determines the next subState dependent on value of <eVal>.
 *  \details      This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]    eVal        : Value from which the next subState is evaluated, valid values are: E_OK, E_NOT_OK
 *  \param[in]    nextSubState: subState in case of <eVal> is E_OK
 *  \param[in]    failSubState: subState in case of <eVal> is E_NOT_OK
 *  \pre          -
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_AnyTaskConditionalContinue(uint8 CanTrcvIndex, uint8 eVal, uint8 nextSubState, uint8 failSubState);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_CmtGetNextAction
 **********************************************************************************************************************/
/*! \brief        This API returns the next action to be processed in case of processing of API: CanTrcv_30_Tja1145_ChangeModeTaskAsync().
 *  \details      This API is called internally.
 *  \param[in]    taskState: Current state of the task (STOPPED, RUNNING)
 *  \param[in]    currentSubState: Current subState
 *  \param[in]    event: Event that shall be processed
 *  \return       The next action to be executed by API: CanTrcv_30_Tja1145_ChangeModeTaskAsync().
 *  \pre          -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(uint8, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtGetNextAction(uint8 taskState, uint8 currentSubState, uint8 event, boolean doSync);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ChangeModeTaskAsync
 **********************************************************************************************************************/
/*! \brief        Task to change the operation mode. This function changes the current operation mode in asynchronous manner.
 *  \details      This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CAN transceiver channel
 *  \param[in]    event: Event that shall be processed
 *  \param[in]    taskState: Current state of the task (STOPPED, RUNNING)
 *  \return       E_OK: The requested operating mode was set successfully.
 *                E_PENDING: The task has not finished yet.
 *                E_NOT_OK: The requested operating mode was NOT set / an error occurred.
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  FALSE
 *  \config       (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ChangeModeTaskAsync(uint8 CanTrcvIndex, uint8 event, uint8 taskState);
#endif  /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */

#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RdStatusTask
 **********************************************************************************************************************/
/*! \brief        Task to read the status-flags registers and to clear the BUSERR flag at the same time.
 *  \details      Only one request can be active at the same time. This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CAN transceiver channel
 *  \param[in]    event: Event that shall be processed (only if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \param[in]    taskState: Current state of the task (STOPPED, RUNNING) (only if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \return       E_OK: Task has finished successfully. 
 *                E_PENDING: The task has not finished yet. (only if asynchronous SPI-interface)
 *                E_NOT_OK: Task execution failed due to an error occurred. 
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON else FALSE
 *  \config       (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RdStatusTask(uint8 CanTrcvIndex);
# else
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RdStatusTask(uint8 CanTrcvIndex, uint8 event, uint8 taskState);
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ClrWufFlagTask
 **********************************************************************************************************************/
/*! \brief        Task to clear any pending wakeup flag (WUF/WUP) from the underlying CAN transceiver HW.
 *  \details      Only one request can be active at the same time. This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of the CanTrcv
 *  \param[in]    event: Event that shall be processed (Only if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \param[in]    taskState: Current state of the task (STOPPED, RUNNING) (Only if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \return       E_OK: Task has finished successfully. 
 *                E_PENDING: The task has not finished yet.
 *                E_NOT_OK: Task execution failed due to an error occurred. 
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE if CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON else FALSE
 *  \config       (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClrWufFlagTask(uint8 CanTrcvIndex);
# else
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClrWufFlagTask(uint8 CanTrcvIndex, uint8 event, uint8 taskState);
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionReqWrIdMask
 **********************************************************************************************************************/
/*! \brief        This function writes values of registers: Baudrate, CanId2, CanIdMask1 and FrameControl.
 *  \details      This API is called internally.
 *  \param[in]    CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]    doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return       E_OK: Writing of registers mentioned above was successful else E_NOT_OK.
 *  \pre          Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context      ANY
 *  \reentrant    TRUE only for different <CanTrcvIndex>.
 *  \synchronous  TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config       (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqWrIdMask(uint8 CanTrcvIndex, boolean doSync);


# if ((CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)) /* COV_CANTRCV_LL_TJA1145_VARCOV_INVALID_MEASURE */
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionReqRdIdMask
 **********************************************************************************************************************/
/*! \brief       This function reads from CAN transceiver hardware following registers:
 *               Baudrate, CanId2, CanIdMask1 and FrameControl.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]   doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Reading of IdMask-registers succeeded else E_NOT_OK.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRdIdMask(uint8 CanTrcvIndex, boolean doSync);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionWaitRdIdMask
 **********************************************************************************************************************/
/*! \brief       This function verifies the correctness of registers: Baudrate, CanId2, CanIdMask1 and FrameControl.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \return      E_OK: Verification passed. E_NOT_OK: Verification failed.
 *  \pre         The APIs: CanTrcv_30_Tja1145_RitActionReqWrIdMask() and CanTrcv_30_Tja1145_RitActionReqRdIdMask() must be
 *               called before this one.
 *               Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRdIdMask(uint8 CanTrcvIndex);
# endif /* (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */

/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionReqWrDb
 **********************************************************************************************************************/
/*! \brief       This function writes the values of registers: DataMask0, DataMask3 and DataMask6.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]   doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Initialization was successful else E_NOT_OK.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqWrDb(uint8 CanTrcvIndex, boolean doSync);


# if ((CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)) /* COV_CANTRCV_LL_TJA1145_VARCOV_INVALID_MEASURE */
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionReqRdDb
 **********************************************************************************************************************/
/*! \brief       This function reads the values of registers: DataMask0, DataMask3 and DataMask6.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]   doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Reading of registers succeeded else E_NOT_OK.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRdDb(uint8 CanTrcvIndex, boolean doSync);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionWaitRdDb
 **********************************************************************************************************************/
/*! \brief       This function verifies the correctness of registers: DataMask0, DataMask3 and DataMask6.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \return      E_OK: Verification passed. E_NOT_OK: Verification failed.
 *  \pre         The APIs: CanTrcv_30_Tja1145_HwPnCfgWriteDb() and CanTrcv_30_Tja1145_HwPnCfgReadDb() must be
 *               called before this one.
 *               Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRdDb(uint8 CanTrcvIndex);
# endif /* (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */


# if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionReqRwMode
 **********************************************************************************************************************/
/*! \brief       This function writes PN-enabling values into CAN transceiver HW.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \param[in]   doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK: Writing of PN-enabling values passed else E_NOT_OK (failed).
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if <doSync> == TRUE, FALSE if <doSync> == FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRwMode(uint8 CanTrcvIndex, boolean doSync);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitActionWaitRwMode
 **********************************************************************************************************************/
/*! \brief       This function verifies the PN-enabling within the CAN transceiver HW.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: Index of CAN transceiver channel
 *  \return      E_OK: Verification of PN-enabling passed else E_NOT_OK (failed).
 *  \pre         The API: CanTrcv_30_Tja1145_RitActionReqRwMode() must be called before this one.
 *               Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRwMode(uint8 CanTrcvIndex);


#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ReInitTaskSync
 **********************************************************************************************************************/
/*! \brief       This API re-initializes the PN-configuration of CAN transceiver HW in synchronous manner.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \return      E_OK: Re-initialization of CAN transceiver HW successfully executed else E_NOT_OK (Re-initialization failed).
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) && 
 *               (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReInitTaskSync(uint8 CanTrcvIndex);

#  else /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */

/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RitGetNextAction
 **********************************************************************************************************************/
/*! \brief       This API returns the next action to be processed in case of processing of API: CanTrcv_30_Tja1145_ReInitTaskAsync().
 *  \details     This API is called internally.
 *  \param[in]   taskState      : Current state of the task (STOPPED, RUNNING)
 *  \param[in]   currentSubState: Current subState
 *  \param[in]   event          : Event that shall be processed
 *  \return      The next action to be executed by API: CanTrcv_30_Tja1145_ReInitTaskAsync().
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) && 
 *               (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(uint8, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitGetNextAction(uint8 taskState, uint8 currentSubState, uint8 event);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_ReInitTaskAsync
 **********************************************************************************************************************/
/*! \brief       This API re-initializes the PN-configuration of CAN transceiver HW in synchronous manner.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   event: Event that shall be processed
 *  \param[in]   taskState: Current state of the task (STOPPED, RUNNING)
 *  \return      E_OK: Re-initialization of CAN transceiver HW successfully executed
 *               E_PENDING: Re-initialization of CAN transceiver HW is in progress.
 *               E_NOT_OK: Re-initialization of CAN transceiver HW failed.
 *  \pre         Must be called within active critical area: CANTRCV_30_TJA1145_EXCLUSIVE_AREA_0.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous FALSE
 *  \config      (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) && 
 *               (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReInitTaskAsync(uint8 CanTrcvIndex, uint8 event, uint8 taskState);
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
# endif /* CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON */
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RequestStatus
 **********************************************************************************************************************/
/*! \brief       This API requests to read status-flags from CAN transceiver HW.
 *  \details     This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   whichFlags  : Which status-flags are to be requested, following values are possible:
 *               CANTRCV_30_TJA1145_GET_SF_INIT, CANTRCV_30_TJA1145_GET_SF_CBWAKEUPBYBUS, CANTRCV_30_TJA1145_GET_SF_MAINFUNCTION.
 *  \return      E_OK    : Request accepted / executed (depends on <whichFlags>)
 *               E_NOT_OK: Request rejected / failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RequestStatus(uint8 CanTrcvIndex, uint16 whichFlags);
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RwStatus
 **********************************************************************************************************************/
/*! \brief       This API reads the status-flags of CAN transceiver HW.
 *  \details     By the way: due to read-access to status-flags they are cleared. This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   isSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \param[in]   requestType : Which kind of status-flags, following values are possible: 
 *               CANTRCV_30_TJA1145_RT_RD_STATUS, CANTRCV_30_TJA1145_RT_CLR_WUF, CANTRCV_30_TJA1145_RT_CLR_ALL.
 *  \return      E_OK    : Read-access to status-flags accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Read-access to status-flags rejected / failed.
 *  \pre         The caller must ensure that this API is called only if SPI is free for channel <CanTrcvIndex>.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) or (<doSync> == TRUE) else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RwStatus(uint8 CanTrcvIndex, boolean isSync, uint32 requestType);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_RwMode
 **********************************************************************************************************************/
/*! \brief       This API do a write-read-access to Mode-registers of CAN transceiver HW.
 *  \details     The mentioned Mode-registers are: CAN-control and Mode-control. This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   isSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK    : Write-read-access to Mode-registers accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Write-read-access to Mode-registers rejected / failed.
 *  \pre         The caller must ensure that this API is called only if SPI is free for channel <CanTrcvIndex>.
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) or (<doSync> == TRUE) else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RwMode(uint8 CanTrcvIndex, boolean isSync);

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
#else
/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_SpiIndication
 **********************************************************************************************************************/
/*! \brief       This API is an internal SPI-end-notification function which indicates a successful process of a SPI-sequence.
 *  \details     This API is required to be internal one in case of synchronous SPI-interface is used.
 *               This API is required to be external one in case of asynchronous SPI-interface is used and must be called
 *               within the SpiEndNotification of the SPI-driver. This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiIndication(uint8 CanTrcvIndex);
#endif


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_PrepareTxBlock
 **********************************************************************************************************************/
/*! \brief       This API prepares an internal SPI-block of data for transmission via the SPI-driver.
 *  \details     In addition the external buffer is set up within the SPI-driver. This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   blockIdx    : Index of data-block to be transmitted.
 *  \param[in]   blockInfo   : Pointer to an internal SPI-block of data to be transmitted via the SPI.
 *  \param[in]   spiChannel  : SPI-channel, following values are possible: *RWData_3, *RWData_2, *RWData_1, *RWData_0.
 *  \return      E_OK    : Preparation of an internal SPI-block for transmission succeeded.
 *               E_NOT_OK: Preparation of an internal SPI-block for transmission failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_PrepareTxBlock(uint8 CanTrcvIndex, uint8 blockIdx, P2CONST(CanTrcv_30_Tja1145_SpiTxBlockSeqType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) blockInfo, Spi_ChannelType spiChannel);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_SpiTransmitBlock
 **********************************************************************************************************************/
/*! \brief       This API requests the SPI-driver to transmit an internal SPI-block of data.
 *  \details     This API calls the internal APIs: (1) CanTrcv_30_Tja1145_PrepareTxBlock() and (2) CanTrcv_30_Tja1145_SpiTransmit()
 *               in order firstly to prepare an internal SPI-block (1) and secondly to transmit it via a correct SPI-sequence.
 *               This API is called internally.
 *  \param[in]   CanTrcvIndex: CAN transceiver channel
 *  \param[in]   blockInfo   : Pointer to an internal SPI-block of data to be transmitted via the SPI.
 *  \param[in]   doSync      : <TRUE> synchronous SPI-transmission is required. <FALSE> asynchronous transmission is required.
 *  \return      E_OK    : Transmit-request via SPI accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Transmit-request via SPI rejected / failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) or (<doSync> == TRUE) else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiTransmitBlock(uint8 CanTrcvIndex, P2CONST(CanTrcv_30_Tja1145_SpiTxBlockSeqType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) blockInfo, boolean isSync);


/***********************************************************************************************************************
 *  CanTrcv_30_Tja1145_SpiTransmit
 **********************************************************************************************************************/
/*! \brief       This API requests the SPI-driver to transmit a SPI-sequence.
 *  \details     This API is called internally.
 *  \param[in]   Sequence    : SPI-sequence, following values are possible: *Large, *Medium, *Normal.
 *  \param[in]   doSync      : <TRUE> synchronous execution is required. <FALSE> asynchronous execution is required.
 *  \return      E_OK    : Transmit-request via SPI accepted / executed (only in case of synchronous transmission)
 *               E_NOT_OK: Transmit-request via SPI rejected / failed.
 *  \pre         The external buffer must be prepared before transmission e.g. via the API: CanTrcv_30_Tja1145_PrepareTxBlock().
 *  \context     ANY
 *  \reentrant   TRUE only for different <CanTrcvIndex>.
 *  \synchronous TRUE if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) or (<doSync> == TRUE) else FALSE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiTransmit(Spi_SequenceType Sequence, boolean isSync);

/* -- end of section code -- */
#define CANTRCV_30_TJA1145_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ** ** ** */

#define CANTRCV_30_TJA1145_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* -- start of section const -- */

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
CANTRCV_30_TJA1145_LOCAL CONST(CanTrcv_30_Tja1145_TaskInfoType, CANTRCV_30_TJA1145_CONST) CanTrcv_30_Tja1145_TaskInfoTable[CANTRCV_30_TJA1145_NUM_TASKS] = /* PRQA S 3218 1 */ /* MD_CanTrcv_30_Tja1145_8.9 */
{
  { CanTrcv_30_Tja1145_ChangeModeTaskAsync }  /* CANTRCV_30_TJA1145_TASK_ID_CHANGE_OP_MODE */
#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
                                     ,
  { CanTrcv_30_Tja1145_RdStatusTask }         /* CANTRCV_30_TJA1145_TASK_ID_RD_STATUS */
#endif
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
                                       ,
  { CanTrcv_30_Tja1145_ClrWufFlagTask },      /* CANTRCV_30_TJA1145_TASK_ID_CLR_WUF_FLAG */
# if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
  { CanTrcv_30_Tja1145_ReInitTaskAsync }      /* CANTRCV_30_TJA1145_TASK_ID_REINIT */
# endif /* CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON */
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */
};
#endif

/* -- end of section cost -- */
#define CANTRCV_30_TJA1145_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ** ** ** */

#define CANTRCV_30_TJA1145_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* -- start of section code -- */


/* ********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 * ********************************************************************************************************************/

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_InitMemory(void)
{
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #100 Mark driver as uninitialized. */
  CanTrcv_30_Tja1145_IsInitialized = CANTRCV_30_TJA1145_IS_NOT_INIT;
#endif
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex)
{
  /* #100 Initialize the CAN transceiver channel-specific settings (independent active or inactive one) (LL-specific). */
  #if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  uint8 taskId;
  CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead = 0; /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxWrite = 0; /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree = CANTRCV_30_TJA1145_NUM_TASKS; /* SBSW_CANTRCV_HL_TJA1145_1 */
  /* Initialize the sub-state of worker */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  
  for (taskId = 0; taskId < CANTRCV_30_TJA1145_NUM_TASKS; ++taskId)
  {
    CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][taskId] = 0xffu; /* SBSW_CANTRCV_LL_TJA1145_1 */
  }
  #endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_LL_InitChannel
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_LL_InitChannel(uint8 CanTrcvIndex)
{
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqInfoBlock;
  uint8 seeValue, teeValue, wpeValue;
  Std_ReturnType retVal;

  /* #100 Initialize the CAN transceiver channel-specific settings (only active one) (LL-specific). */
  
  /* Activate events */
  
  /* OTW = off, SPIF = off */
  seeValue = 0x00u;
  
  if(CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex)) /* COV_CANTRCV_LL_TJA1145_CODECOV_WU_BY_BUS_NOT_EACH_CFG */
  {
    /* CBSE = off, CFE = off, CWE = on */
    teeValue = (uint8)(CanTrcv_30_Tja1145_Tee_CWE);
  }
  else
  {
    /* CBSE = off, CFE = off, CWE = off */
    teeValue = 0x00u;
  }
  
  /* WRE = on, WPFE = on */
  wpeValue = (uint8)(CANTRCV_30_TJA1145_WAKE_PIN_SETTING(CanTrcvIndex));
  
  
  /* Transmit these settings via SPI (synchronous mode) */
  write_block(seqInfoBlock.block[0], CanTrcv_30_Tja1145_See, 1u, &seeValue); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[1], CanTrcv_30_Tja1145_Tee, 1u, &teeValue); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[2], CanTrcv_30_Tja1145_Wpe, 1u, &wpeValue); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqInfoBlock.numberOfBlocks = 3;
  retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqInfoBlock, TRUE); /* SBSW_CANTRCV_HL_TJA1145_3 */
  
  if (retVal == E_NOT_OK)
  {
    CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_TJA1145_INIT_ID);
  }
  
}


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_LL_InitChannelPnData
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_InitSubInitPn(uint8 CanTrcvIndex, Std_ReturnType getStatusFlagRetVal, boolean pnEnabled)
{
  /* #100 Initialize the PN-configuration only if PN is enabled within the configuration and determination of status flags from CAN transceiver HW succeeded. */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if ((pnEnabled == TRUE) && (getStatusFlagRetVal == E_OK) && (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsRdy == TRUE))
#  else
  if ((pnEnabled == TRUE) && (getStatusFlagRetVal == E_OK))
#  endif
  {
    /* #110 Determine and store (overwrite the wake-up reason) whether POR or SYSERR is set. If one of them is set the PN configuration must be re-loaded. */
    if (
        (CanTrcv_30_Tja1145_StateWupIsPor(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) ||
        (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) ||
        (CanTrcv_30_Tja1145_StateErrIsCfg(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) )  /* ASR extension: CFGERR has to be checked too! */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_POWER_ON */
    {
      Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

      /* NOTE: Do NOT change the order between POWER_ON and SYSERR detection. Reason in case of POWER_ON is set SYSERR is set as well -> but in this case POWER_ON 
       * is the relevant one [see: ESCAN00093075]. */
      if (CanTrcv_30_Tja1145_StateWupIsPor(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_POWER_ON */
      {
        /* Store / overwrite the the wake-up reason: POWER_ON */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_POWER_ON; /* \trace SPEC-14972 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      else
      if (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_POWER_ON */
      {
        /* Store / overwrite the wake-up reason: BY_SYSERR */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_BY_SYSERR; /* \trace SPEC-15005 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      else
      {
        /* Nothing. */
      }

      {
        /* \trace SPEC-15068 */
        retVal  = CanTrcv_30_Tja1145_RitActionReqWrIdMask(CanTrcvIndex, TRUE);
        
        retVal |= CanTrcv_30_Tja1145_RitActionReqWrDb(CanTrcvIndex, TRUE);
        
      }

      /* #120 Verify if channel specific initialization of PN was successful. If fails report error and disable PN functionality in SW. */
# if (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON)
      if (retVal == E_OK)
      {
        retVal = CanTrcv_30_Tja1145_VerifyData((uint8)CanTrcvIndex);
      }
# endif
      if (retVal != E_OK)
      {
        /* \trace SPEC-20013 */
        CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_TJA1145_INIT_ID);

        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
      }

      /* Dummy statement to prevent compiler warnings */
      CANTRCV_30_TJA1145_DUMMY_STATEMENT(retVal); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */

    } /* porFlag == CANTRCV_30_TJA1145_FLAG_SET || sysErrFlag == CANTRCV_30_TJA1145_FLAG_SET */
  }
  else /* pnEnabled == TRUE  */
  {
    /* if pn is disabled, data is considered as always valid */
  }
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckPnAvailability
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckPnAvailability(uint8 CanTrcvIndex)
{
  if ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
      (!(CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))) &&
      (!(CanTrcv_30_Tja1145_StateErrIsCfg(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)))) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
  {
    /* #100 If PN functionality is available in HW: Inform the CanIf about this and set internally that PN is available in HW. */

    /* \trace SPEC-15087, SPEC-19956 */
    CanIf_30_Tja1145_ConfirmPnAvailability(CanTrcvIndex);

    /* Report that PN is available again */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
  else
  {
    /* ESCAN00083583 */
    if ((CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) ||
        (CanTrcv_30_Tja1145_StateErrIsCfg(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
    {
      /* PN does NOT work due to CFGERR or SYSERR occurred */

      /* #110 If PN-functionality is NOT available in HW: set internally that PN is NOT available in HW. */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
    }
  }
}
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_Init
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_Init( P2CONST(CanTrcv_30_Tja1145_ConfigType, AUTOMATIC, CANTRCV_30_TJA1145_INIT_DATA) ConfigPtr )
{
  /* \trace SPEC-14971 */

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* ESCAN00076622 */
#if (CANTRCV_30_TJA1145_USE_INIT_POINTER == STD_ON)
  /* #100 Store the configuration pointer. (Required before any check especially for PBL-configurations due to access to GeneratorCompatibilityVersion and MagicNumber via the ConfigPtr.) */
  CanTrcv_30_Tja1145_ConfigDataPtr = ConfigPtr;

# if ((CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)) /* COV_CANTRCV_HL_LL_TJA1145_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #10 Check if parameter ConfigPtr is valid. */
  if (ConfigPtr == NULL_PTR)
  {
#  if (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_TJA1145_VARCOV_SW_FEAT_NOT_SUPPORTED */
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1145_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
#  endif /* (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */

#  if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) /* COV_CANTRCV_HL_LL_TJA1145_VARCOV_SW_FEAT_NOT_SUPPORTED */
    /* \trace SPEC-14948 */
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
#  endif /* (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) */
  }
  else
# endif /* (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
# if (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_TJA1145_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #20 Check the generator compatibility version */
  if (CanTrcvCfg_GetGeneratorCompatibilityVersion() != (uint32)((CANTRCV_30_TJA1145_BASE_GENDATA_COMP_VERSION << 16u) | CANTRCV_30_TJA1145_HW_GENDATA_COMP_VERSION)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1145_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  /* #30 Check the magic number */
  else if (CanTrcvCfg_GetMagicNumber() != CANTRCV_30_TJA1145_FINAL_MAGIC_NUMBER) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1145_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
# endif /* (CANTRCV_30_TJA1145_CONFIGURATION_VARIANT == CANTRCV_30_TJA1145_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
#endif /* (CANTRCV_30_TJA1145_USE_INIT_POINTER == STD_ON) */
  {
    uint8_least index;





#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
    /* #110 Set transceiver driver as initialized at all. */
    CanTrcv_30_Tja1145_IsInitialized = CANTRCV_30_TJA1145_IS_INIT;
#endif

    /* #120 Run through all transceiver channels and initialize them.*/
    for(index = 0; index < CANTRCV_30_TJA1145_MAX_CHANNEL; ++index)
    {

      /* Initialize variables */

      /* Initialize LL */
      CanTrcv_30_Tja1145_LL_InitMemoryChannelBegin((uint8)index);

      /* #130 Set the channel states concerning: initialization, wake-up report and wake-up reason to default values. */
      CanTrcv_30_Tja1145_Prob[index].isInit = CANTRCV_30_TJA1145_IS_NOT_INIT; /* SBSW_CANTRCV_HL_TJA1145_1 */
      CanTrcv_30_Tja1145_Prob[index].wakeUpReport = CANTRCV_30_TJA1145_WU_ENABLE; /* SBSW_CANTRCV_HL_TJA1145_1 */
      CanTrcv_30_Tja1145_Prob[index].wakeUpReason = CANTRCV_30_TJA1145_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1145_1 */

      /* #140 Set the channel state concerning: request state to default values (only SPI-interface or SBC-interface with PN). */
      CanTrcv_30_Tja1145_Prob[index].requestState = CanTrcv_30_Tja1145_Req_None; /* SBSW_CANTRCV_HL_TJA1145_1 */

      /* #150 Set the channel state concerning: current operating mode to default values (only SPI-interface). */
      CanTrcv_30_Tja1145_Prob[index].curOpMode = CANTRCV_30_TJA1145_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1145_1 */
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 

#  if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
      /* #160 Set the channel states concerning: wake-up during state transition detection, status flags to default values (only asynchronous SPI-interface). */
      CanTrcv_30_Tja1145_Prob[index].wakeUpInTransitionDetected = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#  endif

      CanTrcv_30_Tja1145_Prob[index].statusFlagsRdy = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
      CanTrcv_30_Tja1145_Prob[index].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */

      CanTrcv_30_Tja1145_Prob[index].nextRequestState = CanTrcv_30_Tja1145_Req_None; /* SBSW_CANTRCV_HL_TJA1145_1 */
# endif

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
      /* #170 Set the channel states concerning: Partial networking to default values (only PN). */
      CanTrcv_30_Tja1145_Prob[index].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
      CanTrcv_30_Tja1145_Prob[index].isPnEnabled = FALSE; /* is configured in _Init() */ /* SBSW_CANTRCV_HL_TJA1145_1 */
#endif


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) 
      /* #180 Check the configured baudrate (only PN). */
      if (CANTRCV_30_TJA1145_CHECK_BAUDRATE(index) != E_OK) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
      {
        /* \trace SPEC-15101 */
        errorId = CANTRCV_30_TJA1145_E_BAUDRATE_NOT_SUPPORTED;
      }
      else
#endif
      /* ----- Implementation ----------------------------------------------- */

      /* #190 Initialize next parameters only for active transceiver channels. */
      if(CanTrcvCfg_IsChannelUsed(index))
      {
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
        uint8 pnEnabled;
#endif

# if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
    ( (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) ) 
        Std_ReturnType getStatusFlagRetVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
# endif

        Std_ReturnType modeSet = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

        /* #200 If no wake-up event occurred during initialization the default reason is RESET. */
        CanTrcv_30_Tja1145_Prob[index].wakeUpReason = CANTRCV_30_TJA1145_WU_RESET; /* SBSW_CANTRCV_HL_TJA1145_1 */

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
        pnEnabled = CanTrcvCfg_IsPnEnabled(index); /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */

        /* #210 Set the channel states concerning: partial networking to configured values (only PN). */
        CanTrcv_30_Tja1145_Prob[index].pnAvailable = pnEnabled; /* SBSW_CANTRCV_HL_TJA1145_1 */
        CanTrcv_30_Tja1145_Prob[index].isPnEnabled = pnEnabled; /* SBSW_CANTRCV_HL_TJA1145_1 */
#endif

        /* #220 Do additional checks: wake-up event, HW status, PN configuration. (critical section is used). */

#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
    ( (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) ) 
        /* \trace SPEC-14953 */


          /* #230 Check general status flags. If fails report error. */
        getStatusFlagRetVal = CanTrcv_30_Tja1145_RequestStatus((uint8)index, CANTRCV_30_TJA1145_GET_SF_INIT);
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
        if ((getStatusFlagRetVal == E_NOT_OK) || (CanTrcv_30_Tja1145_Prob[index].statusFlagsRdy == FALSE))
#  else
        if ((getStatusFlagRetVal == E_NOT_OK))
#  endif
        {
          /* \trace SPEC-20013 */
          CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_TJA1145_INIT_ID);
        }
#endif /* CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON || CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

        /* #240 Determine whether a wake-up event (BY_BUS, BY_PIN) occurred or NOT. If occurred store it. */
#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
        if ((getStatusFlagRetVal == E_OK) && (CanTrcv_30_Tja1145_Prob[index].statusFlagsRdy == TRUE))
#  else
        if ((getStatusFlagRetVal == E_OK))
#  endif
        {
          if (CanTrcv_30_Tja1145_StateWupIsBus(CanTrcv_30_Tja1145_Prob[index].statusFlags))
          {
            /* A wakeup occurred. The reason is: BY_BUS */
            CanTrcv_30_Tja1145_Prob[index].wakeUpReason = CANTRCV_30_TJA1145_WU_BY_BUS; /* SBSW_CANTRCV_HL_TJA1145_1 */
          }
          else if (CanTrcv_30_Tja1145_StateWupIsPin(CanTrcv_30_Tja1145_Prob[index].statusFlags)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
          {
            /* A wakeup occurred. The reason is: BY_PIN */
            CanTrcv_30_Tja1145_Prob[index].wakeUpReason = CANTRCV_30_TJA1145_WU_BY_PIN; /* SBSW_CANTRCV_HL_TJA1145_1 */
          }
          else
          {
            /* Nothing. */
          }
        }
#endif /* CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON */


        /* Do some generic initialization of LL */
        CanTrcv_30_Tja1145_LL_InitChannel((uint8)index);

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
        /* #250 Initialize the CAN transceiver HW according partial networking configuration. */
        CanTrcv_30_Tja1145_InitSubInitPn((uint8)index, getStatusFlagRetVal, pnEnabled);
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
        /* #260 Report the detected wake-up event to the upper layer. */
        CanTrcv_30_Tja1145_ReportWakeup((uint8)index);
#endif

        /* #270 Set the operating mode to NORMAL. In case of SPI-interface always synchronous. (critical section used) */

#if (CANTRCV_30_TJA1145_USE_ICU == STD_ON)
        /* #280 If ICU is configured, disable ICU. */
        if (CanTrcvCfg_IsIcuChannelSet(index)) /* \trace SPEC-14950 */
        {
          Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(index) ); /* \trace SPEC-14973*/
        }
#endif

        /* This is always synchronous */
        CanTrcv_30_Tja1145_SetOpModeReq(index, CanTrcv_30_Tja1145_Req_OpModeNormal); /* SBSW_CANTRCV_HL_TJA1145_1 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
        modeSet = CanTrcv_30_Tja1145_StartTaskChangeOpMode((uint8)index);




        /* #300 Check if setting of operating mode was successful. */
        if (modeSet == E_OK)
        {
          /* #310 Mode change was successful: Store the current operating mode. (only SPI-interface) */
          CanTrcv_30_Tja1145_Prob[index].curOpMode = CANTRCV_30_TJA1145_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1145_1 */

          /* #320 Mode change was successful: Clear all pending requests. (only SPI-interface) */
          CanTrcv_30_Tja1145_Prob[index].requestState = CanTrcv_30_Tja1145_Req_None; /* SBSW_CANTRCV_HL_TJA1145_1 */
          /* #330 Mode change was successful: Set current transceiver channel to initialized. */
          CanTrcv_30_Tja1145_Prob[index].isInit = CANTRCV_30_TJA1145_IS_INIT; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }
        else
        {
          /* \trace SPEC-20013 */
          /* #340 Mode change was NOT successful: Report error. */
          errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
        }
      } /* CanTrcvChannelUsed == TRUE */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) && (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
      else
      {
        /* Just to prevent MISRA violations */
      }
#endif
    } /* for (...) */
  } /* if (ConfigPtr == NULL_PTR) .. else */

#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_TJA1145_CODECOV_NOT_EACH_CONFIG */
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_INIT_ID, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif
  
#if (CANTRCV_30_TJA1145_USE_INIT_POINTER == STD_OFF)
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpMode
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  Std_ReturnType modeSet = E_NOT_OK;

  CanTrcv_30_Tja1145_TrcvModeType currentOpMode;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19976 */  
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19976 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15064 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute transition of operating mode only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #110 Check if the current operating mode equals the requested one. */
      (void)CanTrcv_30_Tja1145_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1145_3 */

      if ((currentOpMode == OpMode) && (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) == CanTrcv_30_Tja1145_Req_None)) /* \trace SPEC-15090 */ /* COV_CANTRCV_HL_TJA1145_CODECOV_OP_MODE_REQ_NONE */
      {
        /* \trace SPEC-19955 */
        returnVal = E_OK;
        /* The mode was verified within GetOpMode, so the mode was set */
        modeSet = E_OK;

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
        /* #130 The requested one equals the current one. Do NOT execute the mode change request. */
        if ((currentOpMode == CANTRCV_30_TJA1145_OP_MODE_NORMAL) &&
            (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable == TRUE) && (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE))
        {
          /* #140 The requested one equals the current one. If PN is available and enabled confirm the PN availability. (only PN) */
          CanIf_30_Tja1145_ConfirmPnAvailability(CanTrcvIndex); /* \trace SPEC-15087, SPEC-19956 */
        }
#endif

        /* #150 The requested one equals the current one. Inform the CanIf about the successful mode change. (only SPI-interface) */
        CanIf_30_Tja1145_TrcvModeIndication(CanTrcvIndex, currentOpMode); /* \trace SPEC-20006 */
      }
      else
      {
# if (CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT == STD_OFF)
        /* #160 Verify that no wakeup source at the current channel is enabled (only if EMULATED_SLEEP is supported) */
        if((!CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex)) && (!CanTrcvCfg_IsWakeupByPinUsed())) /* PRQA S 2992 */ /* MD_CanTrcv_30_Tja1145_Emulated_Sleep */ /* COV_CANTRCV_HL_TJA1145_CODECOV_NOT_EACH_CONFIG */
        {
# endif /* CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT == STD_OFF */
          /* #165 Verify if mode request is from STANDBY to SLEEP (only if EMULATED_SLEEP is supported) */
          if ((currentOpMode == CANTRCV_30_TJA1145_OP_MODE_STANDBY) && (OpMode == CANTRCV_30_TJA1145_OP_MODE_SLEEP) && (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) == CanTrcv_30_Tja1145_Req_None)) /* PRQA S 2880 */ /* MD_MSR_Unreachable */ /* COV_CANTRCV_HL_TJA1145_CODECOV_OP_MODE_REQ_NONE */
          {
            /* #170 Set OpMode to SLEEP; HW will remain in STANDBY (only if EMULATED_SLEEP is supported) */
            CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode = CANTRCV_30_TJA1145_OP_MODE_SLEEP; /* SBSW_CANTRCV_HL_TJA1145_1 */

            /* #180 Inform the CanIf about the successful mode change to SLEEP (only if EMULATED_SLEEP is supported and SPI-interface) */
            CanIf_30_Tja1145_TrcvModeIndication(CanTrcvIndex, CANTRCV_30_TJA1145_OP_MODE_SLEEP); /* \trace SPEC-20006 */

            /* \trace SPEC-19955 */
            returnVal = E_OK;

            /* The mode was set directly */
            modeSet = E_OK;
          }
# if (CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT == STD_OFF)
        }
# endif /* CANTRCV_30_TJA1145_EMULATED_SLEEP_CH_INDEPENDENT == STD_OFF */
      }
      if (modeSet == E_NOT_OK)
      {
        /* #190 The requested one does NOT equal the current one. Execute the requested mode change. (critical section is used) */
        /* \trace SPEC-19962 */
        switch(OpMode)
        {
          /* #200 Mode change request to NORMAL. */
          case CANTRCV_30_TJA1145_OP_MODE_NORMAL:
            /* #210 Check whether it is an internal wake-up. If yes store the wake-up reason. */         
            if(
               (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_TJA1145_WU_ERROR))
            {
              /* Transceiver is switched from STANDBY/SLEEP -> NORMAL and has not detected any wakeup.
                 This is considered as internal wakeup. */
              CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_INTERNALLY; /* SBSW_CANTRCV_HL_TJA1145_1 */
            }

            CanTrcv_EnterCritical();

            modeSet = CanTrcv_30_Tja1145_SetOpModeNormal(CanTrcvIndex);
            returnVal = E_OK;
            CanTrcv_LeaveCritical();
            break;

          /* #300 Mode change request to STANDBY. (only if supported by HW) */
          case CANTRCV_30_TJA1145_OP_MODE_STANDBY:
            CanTrcv_EnterCritical();
            /* #310 Mode transition to STANDBY is only possible from NORMAL. Otherwise DET error is reported. */
            if(currentOpMode != CANTRCV_30_TJA1145_OP_MODE_NORMAL) /* \trace SPEC-19955 */
            {
#  if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
              /* \trace SPEC-19985 */
              errorId = CANTRCV_30_TJA1145_E_TRCV_NOT_NORMAL;
#  endif
            }
            else
            {
              /* #320 Current mode is NORMAL: Execute mode request. */
              modeSet = CanTrcv_30_Tja1145_SetOpModeStandby(CanTrcvIndex);
              returnVal = E_OK;
            }
            CanTrcv_LeaveCritical();
            break;

          /* #400 Mode change request to SLEEP. (only if supported by HW) */
          case CANTRCV_30_TJA1145_OP_MODE_SLEEP:
            CanTrcv_EnterCritical();
            /* #410 Mode transition to SLEEP is only possible from STANDBY. Otherwise DET error is reported. */
            if(currentOpMode != CANTRCV_30_TJA1145_OP_MODE_STANDBY) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
            {
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
              /* \trace SPEC-19964 */
              errorId = CANTRCV_30_TJA1145_E_TRCV_NOT_STANDBY;
# endif
            }
            else
            {
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
              if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) != 0x0u) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
              {
                if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) == CanTrcv_30_Tja1145_Req_OpModeNormal) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
                {
                  /* Invalid transition */
                  returnVal = E_NOT_OK;
                }
                else
                {
                  /* #420 If any mode request is currently pending queue this request and cancel previous worker. (only asynchronous SPI-interface) */
                  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState = CanTrcv_30_Tja1145_Req_OpModeSleep; /* SBSW_CANTRCV_HL_TJA1145_1 */
                  modeSet = E_OK;
                  returnVal = E_OK;
                }
              }
              else
# endif
              {
                modeSet = CanTrcv_30_Tja1145_SetOpModeSleep(CanTrcvIndex);
                returnVal = E_OK;
              }
            }
            CanTrcv_LeaveCritical();
            break;

          /* #500 Check if parameter OpMode is valid. */
          default:
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
            /* \trace SPEC-14963 */
            errorId = CANTRCV_30_TJA1145_E_PARAM_TRCV_OP_MODE;
#endif
            break;
          } /* switch() */
      } /* currentOpMode == OpMode */

      /* #600 If mode request executed successfully then inform the CanIf else report error. */
      if (returnVal == E_OK)
      {
        /* For SPI transceivers, the operating mode is verified directly after setting */
        if (modeSet != E_OK) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
        {
          /* \trace SPEC-20011 */
          errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;

          returnVal = E_NOT_OK;
        } /* currentOpMode != OpMode */
      } /* returnVal == E_OK */
    } /* channelUsed == TRUE */
  }

#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_SETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif
  return returnVal;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetOpMode
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;



  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter OpMode is valid. */
  if(OpMode == NULL_PTR)
  {
    /* \trace SPEC-14958 */
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15042 */
    errorId =  CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #200 DIO-interface: Read the mode from status of PINs of underlying HW. (critical section used) */
      /* #201 SPI-interface: Read the mode from state variable. */
      /* #202 SBC-interface: Read the mode via SBC module API. (critical section used) */
      {
        /* \trace SPEC-19974 */

        
        if ( (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode == CANTRCV_30_TJA1145_OP_MODE_NORMAL) )
        {
          /* CAN transceiver is in normal operation mode */
          *OpMode = CANTRCV_30_TJA1145_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1145_2 */
          returnVal = E_OK;
        }

        
        if ( (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode == CANTRCV_30_TJA1145_OP_MODE_SLEEP) )
        {
          /* CAN transceiver is in sleep mode */
          *OpMode = CANTRCV_30_TJA1145_OP_MODE_SLEEP; /* SBSW_CANTRCV_HL_TJA1145_2 */
          returnVal = E_OK;
        }


        
        if ( (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode == CANTRCV_30_TJA1145_OP_MODE_STANDBY) )
        {
          /* CAN transceiver is in standby mode */
          *OpMode = CANTRCV_30_TJA1145_OP_MODE_STANDBY; /* SBSW_CANTRCV_HL_TJA1145_2 */
          returnVal = E_OK;
        }
      }

      /* #210 If reading of operating mode NOT succeeded report error. */
      if (returnVal == E_NOT_OK) /* PRQA S 2992,2996 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
      {
        /* \trace SPEC-19940 */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }
    } /* Channel is used */
  } /* DET checks passed */
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_GETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

 return returnVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetBusWuReason
 **********************************************************************************************************************/
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
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) Reason)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

#if (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1145_WAKEUP_NONE) 
  CanTrcv_30_Tja1145_TrcvModeType currentOpMode;
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if the return-parameter Reason is valid. */
  if(Reason == NULL_PTR)
  {
    /* \trace SPEC-15063 */
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15059 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* UREQ00015010 */
      /* #200 Check the wake-up reason for validity. */
#if (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1145_WAKEUP_NONE) 
      if(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_TJA1145_WU_ERROR)
      {
        /* #300 If wake-up reason is invalid return WU_ERROR. */
        *Reason = CANTRCV_30_TJA1145_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1145_2 */

        /* #310 Wake-up reason is invalid (WU_ERROR). This is OK only in case of transceiver channel is in NORMAL mode. */
        (void)CanTrcv_30_Tja1145_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1145_3 */

        if(currentOpMode != CANTRCV_30_TJA1145_OP_MODE_NORMAL)
        {
          /* \trace SPEC-19980 */
          /* #320 Being in any mode except NORMAL with WU_ERROR is an error hence report it. */
          errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
        }
      }
      else
      {
        /* #400 Wake-up reason is valid (neither WU_ERROR nor WU_NOT_SUPPORTED). Return the current wake-up reason.*/
        *Reason = CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason; /* SBSW_CANTRCV_HL_TJA1145_2 */
        returnVal = E_OK;
      }
#else /* (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1145_WAKEUP_NONE) */
      *Reason = CANTRCV_30_TJA1145_WU_NOT_SUPPORTED; /* SBSW_CANTRCV_HL_TJA1145_2 */
#endif /* (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1145_WAKEUP_NONE) */
    } /* IsChannelUsed */
  }
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_GETBUSWUREASON_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif
  
  return returnVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetWakeupMode
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15077 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1145_WAKEUP_NONE) 
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      /* #200 Set the requested wake-up mode. */
      switch(TrcvWakeupMode)
      {
        case CANTRCV_30_TJA1145_WU_ENABLE:
             /* \trace SPEC-19990 */
             CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_TJA1145_WU_ENABLE; /* SBSW_CANTRCV_HL_TJA1145_1 */

             /* #300 In addition: If requested wake-up mode is WU_ENABLE report if wake-up event(s) is/are pending. */
# if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
     (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
             CanTrcv_30_Tja1145_ReportWakeup(CanTrcvIndex);
# endif

             returnVal = E_OK;
             break;

        case CANTRCV_30_TJA1145_WU_DISABLE:
             /* \trace SPEC-20012 */
             CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_TJA1145_WU_DISABLE; /* SBSW_CANTRCV_HL_TJA1145_1 */

             returnVal = E_OK;
             break;

        case CANTRCV_30_TJA1145_WU_CLEAR:
             /* \trace SPEC-19961 */
             /* #500 In addition: If requested wake-up mode is WU_CLEAR clear the wake-up reason and all detected wake-up events. */
             CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1145_1 */
             returnVal = E_OK;

             break;
        default:
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
             /* #40 Check if parameter TrcvWakeupMode is valid. */
             errorId = CANTRCV_30_TJA1145_E_PARAM_TRCV_WAKEUP_MODE; /* \trace SPEC-15036 */
# endif
             break;
      }
    }
#endif /* CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1145_WAKEUP_NONE */
  }
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_SETWAKEUPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif  
  
#if (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1145_WAKEUP_NONE) 
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(TrcvWakeupMode); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# if(CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(CanTrcvIndex); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif
#endif
  /* \trace SPEC-19978: Not implemented as no need to query HW at this place. */

  return returnVal;
}


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckWakeup
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckWakeup(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;



  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-19994 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active and wake-up detection is enabled. (critical section used) */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      if(CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex) &&
         (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReport == CANTRCV_30_TJA1145_WU_ENABLE)) /* COV_CANTRCV_HL_TJA1145_CODECOV_IS_WU_BY_BUS_USED */
      {
        CanTrcv_EnterCritical();

        /* #110 Is the transceiver channel in NORMAL? (only DIO-/SBC-interface) */
        /* #200 Check if there are any wake-up events pending in HW. */
        if (CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
        {
          /* #300 Any wake-up event is pending: Check if currently an operating mode change is requested. (only asynchronous SPI-interface) */
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
          if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) != 0u)
          {
            /* #310 Currently operating mode change is requested: Store the detected wake-up event. (only asynchronous SPI-interface) */
            CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */

            returnVal = E_OK; /* Request acknowledged */
          }
          else
#   endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
          /* #320 In which operating mode is the transceiver channel? (only SPI-interface) */
          if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode == CANTRCV_30_TJA1145_OP_MODE_NORMAL)
          {
#   if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
            /* #330 Operating mode NORMAL: No valid wake-up event detected. Inform EcuM that the check-wake-up-procedure has completed. (only SPI-interface) */
            EcuM_EndCheckWakeup( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) ); /* \trace SPEC-40535 */
#   endif
            returnVal = E_NOT_OK; /* No wakeup detected */
          }
          else
          {
            /* #340 Operating mode STANDBY / SLEEP: Report the detected wake-up event to the EcuM. */
            CanTrcv_30_Tja1145_ReportWakeup(CanTrcvIndex);

#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
            /* #350 Clear any wake-up event that occurred during mode transition (only asynchronous SPI-interface) */
            CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#   endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
            returnVal = E_OK; /* wake-up detected  */
          }
        }
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
        else if ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew == TRUE) &&
                 ((CanTrcv_30_Tja1145_StateWupIsBus(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))
                 || (CanTrcv_30_Tja1145_StateWupIsPin(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))
#    if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
                 || ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
                     (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))
                    )
#    endif /* (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */
                  )
                ) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
        {
          /* #360 If there are already valid wake-up status flags. Do NOT request new flags but use the valid ones instead. (only asynchronous SPI-interface) */

          /* #370 Mark the used wake-up flags as used. (only asynchronous SPI-interface) */
          CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */

          /* #380 Evaluate the wake-up flags. */
          CanTrcv_30_Tja1145_CbWakeupByBusIndication(CanTrcvIndex);

          returnVal = E_OK; /* Request acknowledged */ /* \trace SPEC-20014  */
        }
#   endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
        else
        {
          /* #400 No pending wake-up flags. Request the underlying HW for wake-up flags. */

          CanTrcv_30_Tja1145_SetCbByBusFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

          returnVal = CanTrcv_30_Tja1145_RequestStatus((uint8)CanTrcvIndex, CANTRCV_30_TJA1145_GET_SF_CBWAKEUPBYBUS);
          /* --> Flags will be processed in GetStatusFlagsIndication + CbWakeupByBusIndication */

          if (returnVal == E_NOT_OK)
          {
            /* Remove request as it failed */
            CanTrcv_30_Tja1145_ClrCbByBusFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

#   if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
            /* #410 If NO valid wake-up events detected. Inform EcuM that the check-wake-up-procedure has completed. (only SPI-interface) */
            EcuM_EndCheckWakeup( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) ); /* \trace SPEC-40535 */
#   endif /* CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON */
          }
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
          /* For synchronous SPI an external wake-up reason indicates that a wake-up occurred. */
          else if (CANTRCV_30_TJA1145_IS_EXTERNAL_WU_REASON(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
          {
            /* Wake-up detected - Return E_OK */
            returnVal = E_OK;
          }
          else
          {
            returnVal = E_NOT_OK;  /* No wake-up detected */
          }
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

          /* #500 If any wake-up event detected determine the wake-up reason (e.g BY_BUS, BY_PIN). (only DIO-interface or SBC-interface) */

        }

        CanTrcv_LeaveCritical();

      }
    }
#else
    returnVal = E_NOT_OK;
#endif /* CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED */
  }
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_CHECKWAKEUP_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif  
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF) && (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_OFF)
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(CanTrcvIndex); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif
  return returnVal;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */


#  if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CbWakeupByBusIndication
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CbWakeupByBusIndication(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTrcv_30_Tja1145_TrcvWakeupReasonType localWakeUpReason = CANTRCV_30_TJA1145_WU_ERROR;

# if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
  boolean wakeupNotified = FALSE;
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Determine the wake-up reason. (critical section used) */
  CanTrcv_EnterCritical();

# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
  if ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable == TRUE) && (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
      (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)) )
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_SYSERR;
  }
  else
# endif
  if ((CanTrcv_30_Tja1145_StateWupIsBus(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)))
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_BUS;
  }
  else if ((CanTrcv_30_Tja1145_StateWupIsPin(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_PIN;
  }
  else
  {
    /* Nothing. */
  }

  if (localWakeUpReason != CANTRCV_30_TJA1145_WU_ERROR)
  {
    /* #200 If a valid wake-up reason was detected, set the wake-up reason. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = localWakeUpReason; /* SBSW_CANTRCV_HL_TJA1145_1 */

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) != 0x0u)
    {
      /* #210 In addition: If the wake-up event was detected during mode transition store this. (only asynchronous SPI-interface) */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#  if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
      wakeupNotified = TRUE;
#  endif
    }
    else
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
    if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode != CANTRCV_30_TJA1145_OP_MODE_NORMAL) /* COV_CANTRCV_HL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
    {
      /* #220 If transceiver channel is currently in power-down mode (STANDBY / SLEEP) inform EcuM about detected wake-up event. */
      CanTrcv_30_Tja1145_ReportWakeup(CanTrcvIndex);
# if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
      wakeupNotified = TRUE;
# endif
    }
    else
    {
      /* No report.. */
    }
  } /* (localWakeUpReason != CANTRCV_30_TJA1145_WU_ERROR) */

  CanTrcv_30_Tja1145_ClrCbByBusFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

  CanTrcv_LeaveCritical();

# if (CANTRCV_30_TJA1145_USE_ENDCHECKWAKEUP == STD_ON)
  if (wakeupNotified == FALSE)
  {
    /* #300 If NO valid wake-up reason detected, inform EcuM that the check-wake-up-procedure has completed. */
    EcuM_EndCheckWakeup( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) ); /* \trace SPEC-40535 */
  }
# endif
}
#  endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) */


#if (CANTRCV_30_TJA1145_GET_VERSION_INFO == STD_ON) /* \trace SPEC-15105 */
/* \trace SPEC-19953 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter VersionInfo is valid. */
  if(VersionInfo == NULL_PTR)
  {
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  else
# endif /* CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* \trace SPEC-14986, SPEC-15032 */
    /* #100 Retrieve the version information: VENDOR_ID, MODULE_ID, SW_MAJOR-, SW_MINOR- and SW_PATCH-version. */
    VersionInfo->vendorID = CANTRCV_30_TJA1145_VENDOR_ID; /* SBSW_CANTRCV_HL_TJA1145_2 */
    VersionInfo->moduleID = CANTRCV_30_TJA1145_MODULE_ID; /* SBSW_CANTRCV_HL_TJA1145_2 */

    VersionInfo->sw_major_version = CANTRCV_30_TJA1145_SW_MAJOR_VERSION; /* SBSW_CANTRCV_HL_TJA1145_2 */
    VersionInfo->sw_minor_version = CANTRCV_30_TJA1145_SW_MINOR_VERSION; /* SBSW_CANTRCV_HL_TJA1145_2 */
    VersionInfo->sw_patch_version = CANTRCV_30_TJA1145_SW_PATCH_VERSION; /* SBSW_CANTRCV_HL_TJA1145_2 */
  }
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_GETVERSIONINFO_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif 
}
#endif /* CANTRCV_30_TJA1145_GET_VERSION_INFO == STD_ON */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_TrcvModeIndication
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_TrcvModeIndication(uint8 CanTrcvIndex, boolean modeSet)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 requestedMode = 0; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  if (modeSet == TRUE)
  {
    /* #100 If mode execution succeeded, adapt the internal mode state variable. */
    /* Get the current requested mode */
    requestedMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

    switch (requestedMode)
    {
    case CanTrcv_30_Tja1145_Req_OpModeNormal:
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode = CANTRCV_30_TJA1145_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1145_1 */
      break;

    case CanTrcv_30_Tja1145_Req_OpModeStandby:
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode = CANTRCV_30_TJA1145_OP_MODE_STANDBY; /* SBSW_CANTRCV_HL_TJA1145_1 */
      break;

    case CanTrcv_30_Tja1145_Req_OpModeSleep: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode = CANTRCV_30_TJA1145_OP_MODE_SLEEP; /* SBSW_CANTRCV_HL_TJA1145_1 */
      break;

    default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
      requestedMode = 0xffffffffu; /* PRQA S 2983 */ /* MD_MSR_RetVal */ /* Just suppress the wakeup notification */
      /* Indication without any request... old mode should be still valid */
      break;
    }
  }

  /* #110 Release mode request pending bit. After this new requests are accepted. (critical section is used) */
  CanTrcv_EnterCritical();
  CanTrcv_30_Tja1145_ClrOpModeReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_LeaveCritical();

#  if (CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON)
    /* #115 Wait until operating mode transition completes. (only if configured) */
    CanTrcv_30_Tja1145_SetOpModeWaitTime(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode);
#  endif

  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT)
  {
    /* #120 If transceiver channel is initialized, inform the CanIf about successful mode change. */
    CanIf_30_Tja1145_TrcvModeIndication(CanTrcvIndex, CanTrcv_30_Tja1145_Prob[CanTrcvIndex].curOpMode); /* \trace SPEC-20006 */

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
#  if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
    if ((requestedMode != 0xffffffffu) &&
        (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected == TRUE)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    {
      /* #130 If in addition a wake-up event occurred during mode transition report the detected wake-up event. (only asynchronous SPI-interface) */
      CanTrcv_30_Tja1145_ReportWakeup(CanTrcvIndex);
    }

    /* #140 Clear any wake-up event that occurred during mode transition. (only asynchronous SPI-interface) */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#  endif /* CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON */
# endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF */
  }
}


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/* \trace SPEC-19989 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetTrcvSystemData
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetTrcvSystemData(uint8 CanTrcvIndex, P2VAR(uint32, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) TrcvSysData )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19942 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19942 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15025 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  /* #40 Check if parameter TrcvSysData is valid. */
  else if(TrcvSysData == NULL_PTR)
  {
    /* \trace SPEC-15098*/
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  else
# endif /* CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      if (CanTrcv_30_Tja1145_IsReqFlagPnd(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY */
#  else
      if (CanTrcv_30_Tja1145_GetSyncSpiTxSem(CanTrcvIndex) == FALSE)
#  endif
      {
        /* #200 SPI is busy: Do NOT execute current request. (only SPI-interface) */
      }
      else
      {
        uint32          regVal;

        CanTrcv_30_Tja1145_SpiTxBlockSeqType seqBlockInfo;


        /* #300 SPI is NOT busy: Read the value of the diagnostic register. (critical section used) */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
        CanTrcv_EnterCritical();
#  endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

        /* \trace SPEC-15026 */
        read_block(seqBlockInfo.block[0], CanTrcv_30_Tja1145_Ms,  1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
        read_block(seqBlockInfo.block[1], CanTrcv_30_Tja1145_Ts,  1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
        read_block(seqBlockInfo.block[2], CanTrcv_30_Tja1145_Wps, 1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
        seqBlockInfo.numberOfBlocks = 3;
        
        retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqBlockInfo, TRUE); /* SBSW_CANTRCV_HL_TJA1145_3 */
        
        if (retVal == E_OK)
        {
          regVal = (  ( (uint32)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][1])          ) |
                      ( (uint32)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][5])  << 0x08u) |
                      ( (uint32)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][9])  << 0x10u) );
        }
        

#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
        CanTrcv_LeaveCritical();
#  else
        CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(CanTrcvIndex);
#  endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

        if (retVal == E_OK)
        {
          *TrcvSysData = regVal; /* SBSW_CANTRCV_HL_TJA1145_2 */
        }
        else
        {
          /* retVal is already E_NOT_OK, no need to overwrite it here */
          /* \trace SPEC-19997 */
          /* #310 If reading of diagnostic register failed, report error. */
          errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
        }
      }
    } /* IsChannelUsed */
  }
  
# if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_GETTRCVSYSTEMDATA_ID, errorId);
  }
# else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif  
  
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* PN or SBC */


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ClearTrcvWufFlag
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClearTrcvWufFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19970 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19970 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15018 */
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if( CanTrcvCfg_IsChannelUsed(CanTrcvIndex) )
# endif
    {

      CanTrcv_EnterCritical();

      /* #110 Clear wake-up reason and all wake-up events detected during initialization. */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1145_1 */

      /* #120 Store the current request. It will be cleared within indication. */
      CanTrcv_30_Tja1145_SetClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

      /* \trace SPEC-14997 */
      retVal = CanTrcv_30_Tja1145_StartTaskClrWufFlag(CanTrcvIndex);

      if (retVal == E_NOT_OK)
      {
        /* #130 If unable to clear the wake-up flag, clear this request. */
        CanTrcv_30_Tja1145_ClrClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
      }

      CanTrcv_LeaveCritical();

      /* The indication is called from the SPI-callback */

      if (retVal == E_NOT_OK)
      {
        /* retVal is already E_NOT_OK, no need to overwrite it here */
        /* \trace SPEC-19943 */
        /* #140 If unable to clear the wake-up flag, report error. */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
      }
    } /* IsChannelUsed */
  }
  
#if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_CLEARTRCVWUFFLAG_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif  
  
  return retVal;
}


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ClearTrcvWufFlagIndication
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClearTrcvWufFlagIndication(uint8 CanTrcvIndex)
{
  /* #100 Clear the request to clear the wake-up flag in HW. */
  CanTrcv_EnterCritical();
  CanTrcv_30_Tja1145_ClrClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_LeaveCritical();

  /* #110 Inform CanIf about successful completion of request. */
  CanIf_30_Tja1145_ClearTrcvWufFlagIndication(CanTrcvIndex); /* \trace SPEC-19983 */
}


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReadTrcvTimeoutFlag
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReadTrcvTimeoutFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Tja1145_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) FlagState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19984 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19984 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK; 
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  /* #40 Check if parameter FlagState is valid. */
  else if(FlagState == NULL_PTR)
  {
    /* \trace SPEC-14943 */
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  else
# endif /* (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
    if (CanTrcv_30_Tja1145_IsReqFlagPnd(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY */
#   else
    if (CanTrcv_30_Tja1145_GetSyncSpiTxSem(CanTrcvIndex) == FALSE)
#   endif
    {
      /* #200 SPI is busy: Do NOT execute current request. (only SPI-interface) */
    }
    else
    {
      /* #300 SPI is NOT busy: Read the value of the time-out flag. (critical section is used) */

#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_EnterCritical();
#   endif

      /* \trace SPEC-20010 */
      /* not supported as this flag is only available if it is considered as wakeup event */
      retVal = E_NOT_OK;
      
      CANTRCV_30_TJA1145_DUMMY_STATEMENT(CanTrcvIndex); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
      CANTRCV_30_TJA1145_DUMMY_STATEMENT((*FlagState)); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */ /* SBSW_CANTRCV_HL_TJA1145_2 */
      
      
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_LeaveCritical();
#   else
      CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(CanTrcvIndex);
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

      if (retVal == E_NOT_OK) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
      {
        /* #310 If reading of time-out flag failed, report error. */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_READTRCVTIMEOUTFLAG_ID, errorId);
  }
# else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif  

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ClearTrcvTimeoutFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClearTrcvTimeoutFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-19948 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19948 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
    if (CanTrcv_30_Tja1145_IsReqFlagPnd(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY */
#   else
    if (CanTrcv_30_Tja1145_GetSyncSpiTxSem(CanTrcvIndex) == FALSE)
#   endif
    {
      /* #200 SPI is busy: Do NOT execute current request. (only SPI-interface) */
    }
    else
    {
      /* #300 SPI is NOT busy: Clear the value of the time-out flag. (critical section is used) */
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_EnterCritical();
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

      /* \trace SPEC-19996 */
      /* not supported as this flag is only available if it is considered as wakeup event */
      retVal = E_NOT_OK;
      
      /* Dummy statements to prevent compiler warnings */
      CANTRCV_30_TJA1145_DUMMY_STATEMENT(CanTrcvIndex); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
      

#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_LeaveCritical();
#   else
      CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(CanTrcvIndex);
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

      if (retVal == E_NOT_OK) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
      {
        /* #310 If clearing of the time-out flag failed, report error. */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_CLEARTRCVTIMEOUTFLAG_ID, errorId);
  }
# else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif  

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReadTrcvSilenceFlag
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReadTrcvSilenceFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Tja1145_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) FlagState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-20000 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20000 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  /* #40 Check if parameter FlagState is valid. */
  else if(FlagState == NULL_PTR)
  {
    /* \trace SPEC-15062*/
    errorId = CANTRCV_30_TJA1145_E_PARAM_POINTER;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
    if (CanTrcv_30_Tja1145_IsReqFlagPnd(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY */
#   else
    if (CanTrcv_30_Tja1145_GetSyncSpiTxSem(CanTrcvIndex) == FALSE)
#   endif
    {
      /* #200 SPI is busy: Do NOT execute current request. (only SPI-interface) */
    }
    else
    {
      /* #300 SPI is NOT busy: Read the value of the silence flag. (critical section used) */
#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_EnterCritical();
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

      /* \trace SPEC-19999 */
      retVal = E_NOT_OK; /* Not supported for this driver */
      
      /* Dummy statements to prevent compiler warnings */
      CANTRCV_30_TJA1145_DUMMY_STATEMENT(CanTrcvIndex); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
      CANTRCV_30_TJA1145_DUMMY_STATEMENT((*FlagState)); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */ /* SBSW_CANTRCV_HL_TJA1145_2 */
      


#   if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON)
      CanTrcv_LeaveCritical();
#   else
      CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(CanTrcvIndex);
#   endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

      if (retVal == E_NOT_OK) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
      {
        /* #310 If reading of the silence flag failed, report error. */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR) /* PRQA S 2991,2995 */ /* MD_CanTrcv_30_Tja1145_14.3 */ /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_READTRCVSILENCEFLAG_ID, errorId);
  }
# else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif  

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckWakeFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckWakeFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL)
  {
    /* \trace SPEC-20005 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20005 */
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1145_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_TJA1145_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. (critical section used) */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      CanTrcv_EnterCritical();

      /* \trace SPEC-20015 */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
      if ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew == TRUE) &&
          (CanTrcv_30_Tja1145_StateWupIsValid(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
      {
        /* #200 If most current status flags are available, evaluate them. (only asynchronous SPI-interface) */

        /* There are still unread status flags. As a request is now pending,
         * Main will handle these flags any more. Thus the flags have to be
         * considered as "valid" and CheckWakeFlag indication is called
         * directly from this context.
         */
        
        /* Clear the statusFlagNew bit */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* Call the indication */
        CanTrcv_30_Tja1145_CheckWakeFlagIndication(CanTrcvIndex);

        /* This was a valid operation... */
        retVal = E_OK;
      }
      else
#  endif
      {
        /* #300 Get and evaluate status flags. (synchronous SPI-interface) Request most current status flags. (asynchronous SPI-interface) */

        /* Store the request. it will be reset on indication */
        CanTrcv_30_Tja1145_SetChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* This code should read and clear the wake flags within one step */
        retVal = CanTrcv_30_Tja1145_StartTaskRdStatus(CanTrcvIndex);

        if (retVal == E_NOT_OK)
        {
          /* No indication will occur. Clear request flag */
          CanTrcv_30_Tja1145_ClrChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
        }
      }
      CanTrcv_LeaveCritical();

      if (retVal == E_NOT_OK)
      {
        /* #310 If getting / requesting of status flags fails, report error. */
        errorId = CANTRCV_30_TJA1145_E_NO_TRCV_CONTROL;
      }
      /* --> CheckWakeFlagIndication will be called from the SPI callback */
    } /* IsChannelUsed */
  } /* DET checks passed */

# if (CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_CHECKWAKEFLAG_ID, errorId);
  }
# else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
# endif  
  
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CheckWakeFlagIndication
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CheckWakeFlagIndication(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTrcv_30_Tja1145_TrcvWakeupReasonType localWakeUpReason = CANTRCV_30_TJA1145_WU_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  CanTrcv_EnterCritical();


  /* #100 Determine the wake-up reason: BY_SYSERR (only PN), BY_BUS or BY_PIN. (critical section used) */
  if ((CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable == TRUE) && (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
      (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)))
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_SYSERR;
  }
  else if ((CanTrcv_30_Tja1145_StateWupIsBus(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags)))
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_BUS;
  }
  else if ((CanTrcv_30_Tja1145_StateWupIsPin(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags))) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
  {
    localWakeUpReason = CANTRCV_30_TJA1145_WU_BY_PIN;
  }
  else
  {
    /* Nothing. */
  }

  if (localWakeUpReason != CANTRCV_30_TJA1145_WU_ERROR)
  {
    /* #110 If any wake-up event was detected, store the wake-up reason and inform the EcuM. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = localWakeUpReason; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_30_Tja1145_ReportWakeup(CanTrcvIndex);
  }

  /* Release request */
  CanTrcv_30_Tja1145_ClrChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */

  CanTrcv_LeaveCritical();

  /* \trace SPEC-19979 */ 
  /* #120 Inform CanIf about successful execution of request to check for wake-up event(s). */
  CanIf_30_Tja1145_CheckTrcvWakeFlagIndication(CanTrcvIndex);
}
# endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_MainFunction
 **********************************************************************************************************************/
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
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least index;
  
  /* ----- Implementation ----------------------------------------------- */
  /* \trace SPEC-15067, SPEC-15085 */
  /* #100 Run through all transceiver channels. */
  for(index = 0; index < CANTRCV_30_TJA1145_MAX_CHANNEL; ++index)
  {
    if (CanTrcvCfg_IsChannelUsed(index))
    {
      if(CanTrcv_30_Tja1145_Prob[index].isInit == CANTRCV_30_TJA1145_IS_INIT)
      {
        /* #200 Execute only if transceiver channel is active and initialized. */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
        if (CanTrcv_30_Tja1145_IsReqFlagPnd(index))
        {
          /* #400 If any request flag is pending execute the pending request(s). (only asynchronous SPI-interface) */
          /* Schedule tasks */
          
          (void)CanTrcv_30_Tja1145_Schedule((uint8)index, CANTRCV_30_TJA1145_TASK_EV_CYCLE);
        }
        else
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
        /* #410 Execute only if transceiver channel is in power-down mode (STANDBY / SLEEP). (only asynchronous SPI-interface) */
        if (CanTrcv_30_Tja1145_Prob[index].curOpMode != CANTRCV_30_TJA1145_OP_MODE_NORMAL)
        {
#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) && (CANTRCV_30_TJA1145_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1145_WAKEUP_POLLING) 
          if (CanTrcvCfg_IsWakeupByBusUsed(index)) /* COV_CANTRCV_HL_TJA1145_CODECOV_IS_WU_BY_BUS_USED */
          {
            /* #420 Do NOT do anything if any request is still pending. (only SPI-interface) */
            if (!CanTrcv_30_Tja1145_IsReqFlagPnd(index)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY */
            {
              /* #210 Transceiver channel is in power-down mode (STANDBY / SLEEP) and has wake-up support enabled: Check if a wake-up event occurred. (critical section used) */
              Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

              CanTrcv_TrcvWakeupReasonType wakeupReason = CANTRCV_30_TJA1145_WU_ERROR;

              CanTrcv_EnterCritical();
              /* #430 Determine whether a wake-up event occurred or NOT from status flags read via SPI. (only SPI- / SBC-interface) */
              /* Check for status bits */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
              if (CanTrcv_30_Tja1145_Prob[index].statusFlagsNew == FALSE)
#  endif
              {
                 /* #440 If NO most current status flags are available, request them via SPI. (only SPI-interface) */

                 /* No request pending.. its safe to request diagnostic registers here..
                 * unread data will be marked as dirty. This request may be
                 * interrupted by any other request..
                 */
                retval = CanTrcv_30_Tja1145_RequestStatus((uint8)index, CANTRCV_30_TJA1145_GET_SF_MAINFUNCTION);
              }
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
              else
#  else
              if (retval == E_OK)
#  endif
              {
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
                /* #450 If most current status flags are available mark them as already used. (only asynchronous SPI-interface) */
                CanTrcv_30_Tja1145_Prob[index].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#  endif

                /* #460 If most current flags are available process them and if any wake-up event occurred determine the wake-up reason (BY_SYSERR (only PN), BY_BUS or BY_PIN). (only SPI- or SBC-interface) */
#  if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
                if ((CanTrcv_30_Tja1145_Prob[index].pnAvailable == TRUE) && (CanTrcv_30_Tja1145_Prob[index].isPnEnabled == TRUE) &&
                    (CanTrcv_30_Tja1145_StateErrIsSys(CanTrcv_30_Tja1145_Prob[index].statusFlags)))
                {
                  wakeupReason = CANTRCV_30_TJA1145_WU_BY_SYSERR;
                }
                else
#  endif
                if (CanTrcv_30_Tja1145_StateWupIsBus(CanTrcv_30_Tja1145_Prob[index].statusFlags))
                {
                  wakeupReason = CANTRCV_30_TJA1145_WU_BY_BUS;
                }
                else if (CanTrcv_30_Tja1145_StateWupIsPin(CanTrcv_30_Tja1145_Prob[index].statusFlags)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN */
                {
                  wakeupReason = CANTRCV_30_TJA1145_WU_BY_PIN;
                }
                else
                {
                  /* Nothing */
                }

                retval = E_OK;
              }

              if (retval == E_NOT_OK)
              {
                /* #470 If the check for wake-up events fails, report error. (only SPI- / SBC-interface) */
                CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_TJA1145_MAINFUNCTION_ID);
              }

              if (wakeupReason != CANTRCV_30_TJA1145_WU_ERROR)
              {
                /* #500 If any wake-up event detected, store the wake-up event. */
                CanTrcv_30_Tja1145_Prob[index].wakeUpReason = wakeupReason; /* SBSW_CANTRCV_HL_TJA1145_1 */

                if (CanTrcv_30_Tja1145_Prob[index].wakeUpReport == CANTRCV_30_TJA1145_WU_ENABLE)
                {
                  /* #510 If any wake-up event detected and wake-up detection is enabled, inform the EcuM to check for wake-up event(s). */
                  EcuM_CheckWakeup( CanTrcvCfg_GetWakeupSource(index) );
                }
              }

#  if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_OFF)
              CANTRCV_30_TJA1145_DUMMY_STATEMENT(retval); /* PRQA S 1338,2982,2983,3112 */ /* MD_MSR_DummyStmt */
#  endif
              CanTrcv_LeaveCritical();
            } /* (!CanTrcv_30_Tja1145_IsReqFlagPnd(index)) */
          }
# endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) */
        } /* CanTrcv_30_Tja1145_Prob[index].curOpMode != CANTRCV_30_TJA1145_OP_MODE_NORMAL */
#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
        else
        {
          /* Required to avoid MISRA violation */
        }
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
      } /* CanTrcv_30_Tja1145_Prob[index].isInit != CANTRCV_30_TJA1145_IS_INIT */
    } /*  CanTrcvCfg_IsChannelUsed(index)  */
  } /* for ... */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */




#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetPNActivationState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetPNActivationState(CanTrcv_30_Tja1145_PNActivationType ActivationState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_OK;
  uint8_least index, numberOfConfigurationChanges;

  numberOfConfigurationChanges = 0;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 Run through all transceiver channels. */
  for(index=0; index < CANTRCV_30_TJA1145_MAX_CHANNEL; index++)
  {
    if (CanTrcvCfg_IsChannelUsed(index))
    {
      /* #200 Do execute only if transceiver channel is active. */
# if (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON)
      /* #10 Check if transceiver channel is initialized. */
      if (CanTrcv_30_Tja1145_Prob[index].isInit != CANTRCV_30_TJA1145_IS_INIT)
      {
        /* \trace SPEC-20019 */
        CanTrcv_DetReportError(CANTRCV_30_TJA1145_SETPNACTIVATIONSTATE_ID, CANTRCV_30_TJA1145_E_UNINIT);
        retval = E_NOT_OK;
      }
# endif
      if (CanTrcvCfg_IsPnEnabled(index))
      {
        /* #210 Transceiver channel has enabled PN functionality: Adapt the setting of PN functionality according to ActivationState. */
        if (ActivationState == CANTRCV_30_TJA1145_PN_ENABLED)
        {
          CanTrcv_30_Tja1145_Prob[index].isPnEnabled = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }
        else
        {
          CanTrcv_30_Tja1145_Prob[index].isPnEnabled = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }

        ++numberOfConfigurationChanges;
      }
      else
      {
        /* #220 Transceiver channel has DISABLED PN functionality: Set PN functionality to DISABLED. */
        CanTrcv_30_Tja1145_Prob[index].isPnEnabled = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
    } /* IsChannelUsed */
  } /* for ... */

  if (numberOfConfigurationChanges == 0u)
  {
    /* #230 If no PN functionality was adapted according to ActivationState at all return E_NOT_OK. */
    retval = E_NOT_OK;
  }

  return retval;
}
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
#  if (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_VerifyData
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_VerifyData(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Verify the PN configuration written into HW. */
  if(CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
  {
    /* Read and verify: IdMask-registers */
    retval  = CanTrcv_30_Tja1145_RitActionReqRdIdMask(CanTrcvIndex, TRUE);
    retval |= CanTrcv_30_Tja1145_RitActionWaitRdIdMask(CanTrcvIndex);
  
    /* Read and verify: DataMask-registers */
    retval |= CanTrcv_30_Tja1145_RitActionReqRdDb(CanTrcvIndex, TRUE);
    retval |= CanTrcv_30_Tja1145_RitActionWaitRdDb(CanTrcvIndex);
  }
  else
  {
    /* WakeupByBus is disabled, therefore PN functionality can not be used correctly */
    retval = E_NOT_OK;
  }

  /* #110 If verification was successful return E_OK, else E_NOT_OK. */
  return retval;
}
#  endif /* (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) */
# endif /* (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetStatusFlagsIndication
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetStatusFlagsIndication(uint8 CanTrcvIndex)
{

  /* ----- Implementation ----------------------------------------------- */
  CanTrcv_EnterCritical();
  /* -- LL -- */
  /* #100 Get status flags. (critical section used) */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags.Ts  = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][1]); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags.Ecs = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][3]); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags.Ses = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][4]); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags.Tes = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][6]); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlags.Wes = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][7]); /* SBSW_CANTRCV_HL_TJA1145_1 */
  /* -- LL -- */

#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  /* #110 Mark the got status flags as available. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsRdy = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #120 Determine whether the status flags shall be processed within the *_MainFunction() or NOT. */
  if (CANTRCV_30_TJA1145_IS_MAIN_FCT_REQ(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_ALL_WU_DIS */
  {
    /* Request was set in context of MainFunction -> inform the MainFunction */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
  else
  {
    /* Request was not set in context of MainFunction -> Don't process this event in the MainFunction */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
#  endif

#  if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
  /* #130 If requested, check the availability of PN functionality in HW. */
  if ((CanTrcv_30_Tja1145_GetConfirmPnAvailabilityReq(CanTrcvIndex) != CanTrcv_30_Tja1145_Req_None))
  {
    /* Ignore this request if no normal mode is requested (may happen due to interrupted mode changes */
    if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) == CanTrcv_30_Tja1145_Req_OpModeNormal) /* COV_CANTRCV_HL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
    {
      CanTrcv_30_Tja1145_CheckPnAvailability(CanTrcvIndex);
    }
    /* #140 Clear the request for checking of availability of PN functionality in HW. */
    CanTrcv_30_Tja1145_ClrConfirmPnAvailabilityReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
#  endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

  CanTrcv_LeaveCritical();
}


#if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReportWakeup
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReportWakeup(uint8 CanTrcvIndex)
{
  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 If any wake-up event occurred, report it to EcuM. */
  /* #110 Depending on configuration report to EcuM the wake-up source which belongs to occurred wake-up reason (POWER_ON, BY_SYSERR (only PN), BY_BUS, BY_PIN). */
  switch(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason)
  {
  case CANTRCV_30_TJA1145_WU_POWER_ON: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_POWER_ON */
# if (CANTRCV_30_TJA1145_USE_EXTENDED_WU_SRC == STD_ON) 
    /* \trace SPEC-14972 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSourcePor(CanTrcvIndex) );
    break;
# endif
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
  case CANTRCV_30_TJA1145_WU_BY_SYSERR:
# if (CANTRCV_30_TJA1145_USE_EXTENDED_WU_SRC == STD_ON) 
    /* \trace SPEC-15081, SPEC-46898 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSourceSyserr(CanTrcvIndex) );
    break;
# endif
#endif
  case CANTRCV_30_TJA1145_WU_BY_BUS:
  case CANTRCV_30_TJA1145_WU_BY_PIN:
    /* \trace SPEC-14953 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) );
    break;

  default:
    /* No valid or an internal wakeup. Do not report this as wakeup event */
    break;
  }
}
#endif


# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
#  if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_GetSyncSpiTxSem
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(boolean, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_GetSyncSpiTxSem(uint8 CanTrcvIndex)
{
  boolean spiLocked;

  CanTrcv_EnterCritical();

  /* #100 Is SPI free?  (critical section is used)*/
  if (CANTRCV_30_TJA1145_IS_SPI_FREE(CanTrcvIndex)) /* COV_CANTRCV_HL_TJA1145_CODECOV_SYNC_INT_BY_SYNC */
  {
    /* #200 Yes: Lock SPI for synchronous transmission. */
    CanTrcv_30_Tja1145_SetSyncSpiTxReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
    spiLocked = TRUE;
  }
  else
  {
    /* #300 No: Reject locking of SPI for synchronous transmission. */
    spiLocked = FALSE;
  }

  CanTrcv_LeaveCritical();

  return spiLocked;
}

/***********************************************************************************************************************
| NAME:  CanTrcv_Tja1145_ReleaseSyncSpiTxSem
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReleaseSyncSpiTxSem(uint8 CanTrcvIndex)
{
  CanTrcv_EnterCritical();
  /* #100 Release semaphore for synchronous SPI-transmission. (critical section is used) */
  CanTrcv_30_Tja1145_ClrSyncSpiTxReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_LeaveCritical();
}
#  endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ProcessNextOpModeReq
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ProcessNextOpModeReq(uint8 CanTrcvIndex)
{
  Std_ReturnType retVal;

  /* #100 Was another mode change requested inbetween? */
  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState != 0x0u)
  {
    /* #110 YES: Set the mode change request to new one. Return OK. */
    CanTrcv_30_Tja1145_SetOpModeReq(CanTrcvIndex, CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState); /* SBSW_CANTRCV_HL_TJA1145_1 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState = 0x0u; /* SBSW_CANTRCV_HL_TJA1145_1 */
    retVal = E_OK;
  }
  else
  {
    /* #120 NO: Return NOT_OK. */
    retVal = E_NOT_OK;
  }

  return retVal;
}
# endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF */


#if (CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeWaitTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeWaitTime(CanTrcv_30_Tja1145_TrcvModeType currentOpMode)
{
  switch(currentOpMode)
  {
    case CANTRCV_30_TJA1145_OP_MODE_NORMAL:
      /* #100 Current mode is NORMAL. */
      /* #200 Wait actively for completion of mode transition. */
      /* \trace SPEC-2890647 */
      (void)Tm_BusyWait1us16bit(CANTRCV_30_TJA1145_SET_OP_MODE_ANY_WAIT_TIME_USEC);
      break;
    default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      break;
  } /* switch() */
}
#endif /* CANTRCV_30_TJA1145_SET_OP_MODE_WAIT_TIME_SUPPORT == STD_ON */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeNormal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeNormal(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType modeSet = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
#  if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpInTransitionDetected = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#  endif
# endif
  /* #100 If ICU is configured, disable ICU. */
#if (CANTRCV_30_TJA1145_USE_ICU == STD_ON)
  if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
  {
    Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-14973 */
  }
#endif

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) != 0x0u)
  {
    /* #200 If any mode request is currently pending, queue this request and cancel previous worker (only asynchronous SPI-interface) */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState = CanTrcv_30_Tja1145_Req_OpModeNormal; /* SBSW_CANTRCV_HL_TJA1145_1 */
    modeSet = E_OK;
  }
  else
#endif
  {
    /* #210 No mode request is currently pending. Store the current mode request. (only SPI-interface) */
    CanTrcv_30_Tja1145_SetOpModeReq(CanTrcvIndex, CanTrcv_30_Tja1145_Req_OpModeNormal); /* SBSW_CANTRCV_HL_TJA1145_1 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
    /* #220 Execute operating mode change request to NORMAL. */
    modeSet = CanTrcv_30_Tja1145_StartTaskChangeOpMode((uint8)CanTrcvIndex);

  }
  return modeSet;
}

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeStandby
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeStandby(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType modeSet = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Implementation ----------------------------------------------- */
  /* #100 If ICU is configured, enable ICU. */
#if (CANTRCV_30_TJA1145_USE_ICU == STD_ON)
  if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
  {
    Icu_EnableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-15004 */
  }
#endif
  /* #200 Reset wake-up reason. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1145_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1145_1 */

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) != 0x0u)
  {
    /* #300 If any mode request is currently pending queue this request and cancel previous worker. (only asynchronous SPI-interface) */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].nextRequestState = CanTrcv_30_Tja1145_Req_OpModeStandby; /* SBSW_CANTRCV_HL_TJA1145_1 */
    modeSet = E_OK;
  }
  else
#endif
  {
    /* #310 No mode request is currently pending. Store the mode request. (only SPI-interface) */
    CanTrcv_30_Tja1145_SetOpModeReq(CanTrcvIndex, CanTrcv_30_Tja1145_Req_OpModeStandby); /* SBSW_CANTRCV_HL_TJA1145_1 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
    /* #320 Execute operating mode change request to STANDBY. */
    modeSet = CanTrcv_30_Tja1145_StartTaskChangeOpMode(CanTrcvIndex);
  }

  return modeSet;
}

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SetOpModeSleep
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SetOpModeSleep(uint8 CanTrcvIndex) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType modeSet = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Implementation ----------------------------------------------- */
    /* #100 No mode request is currently pending. Store the mode request. (only SPI-interface) */
    CanTrcv_30_Tja1145_SetOpModeReq(CanTrcvIndex, CanTrcv_30_Tja1145_Req_OpModeSleep); /* SBSW_CANTRCV_HL_TJA1145_1 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
    /* #200 Execute operating mode change request to SLEEP. */
    modeSet = CanTrcv_30_Tja1145_StartTaskChangeOpMode(CanTrcvIndex);

  return modeSet;
}


#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_StartTask
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_StartTask(uint8 CanTrcvIndex, uint8 TaskId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;

  /* ----- Implementation ----------------------------------------------- */
  if (CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][TaskId] != 0xffu)
  {
    /* #100 If the same task is already pending, just confirm it with PENDING. */
    retval = E_PENDING;
  }
  else if (CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree > 0u) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
  {
    uint8 idxWrite;
    
    /* #200 If there is any space within the schedule-FIFO: (critical section is used)*/

    CanTrcv_EnterCritical();
    /* -- CRITICAL START -- */
    
    idxWrite = CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxWrite;
    
    /* #210 Add the requested task to the schedule-FIFO. */
    CanTrcv_30_Tja1145_ScheduleFifo[CanTrcvIndex][idxWrite].TaskId = TaskId; /* SBSW_CANTRCV_LL_TJA1145_1 */
    CanTrcv_30_Tja1145_ScheduleFifo[CanTrcvIndex][idxWrite].TaskState = CANTRCV_30_TJA1145_TASK_WAIT_START; /* SBSW_CANTRCV_LL_TJA1145_1 */
    
    /* #220 Store the FIFO-entry in the TaskActive-table. */
    CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][TaskId] = CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxWrite; /* SBSW_CANTRCV_LL_TJA1145_1 */
    
    /* #230 Adapt FIFO-parameters. */
    ++idxWrite;
    --CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree; /* SBSW_CANTRCV_LL_TJA1145_3 */
    if (idxWrite >= CANTRCV_30_TJA1145_NUM_TASKS) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
    {
      idxWrite = 0;
    }
    /* Write back idxWrite. Critical section, so no RMW will occur */
    CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxWrite = idxWrite; /* SBSW_CANTRCV_LL_TJA1145_3 */
    
    /* -- CRITICAL STOP -- */
    CanTrcv_LeaveCritical();

    /* #240 Try to start the requested task. */
    retval = CanTrcv_30_Tja1145_Schedule(CanTrcvIndex, CANTRCV_30_TJA1145_TASK_EV_START);
  }
  else
  {
    /* #300 NO space within the schedule-FIFO: Indicate that task was NOT be able to be started at all. */
    retval = E_NOT_OK; /* No more space left. */
  }
  
  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReSchedule
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReSchedule(uint8 CanTrcvIndex, uint8 TaskId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 fifoIdx;
 
  /* ----- Implementation ----------------------------------------------- */

  /* #100 Check if the requested task is executed currently. (critical section is used) */

  CanTrcv_EnterCritical();
  /* -- CRITICAL START -- */
  
  fifoIdx = CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][TaskId];
  if ( (fifoIdx >= CANTRCV_30_TJA1145_NUM_TASKS) ||
       (CanTrcv_30_Tja1145_ScheduleFifo[CanTrcvIndex][fifoIdx].TaskId != TaskId) )
  {
    /* #200 The requested task is NOT executed currently. Hence reject the request to reschedule the task. */
    retval = E_NOT_OK;
  }
  else
  {
    /* #300 The requested task is executed currently. Hence reset the requested task to state: WAIT_START. */
    CanTrcv_30_Tja1145_ScheduleFifo[CanTrcvIndex][fifoIdx].TaskState = CANTRCV_30_TJA1145_TASK_WAIT_START; /* SBSW_CANTRCV_LL_TJA1145_1 */

    /* #310 Confirm the request to reschedule the task. */
    retval = E_OK;
  }
  
  /* -- CRITICAL STOP -- */
  CanTrcv_LeaveCritical();
  
  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_Schedule
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_Schedule(uint8 CanTrcvIndex, uint8 event)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;

  P2VAR(CanTrcv_30_Tja1145_TaskStateType, AUTOMATIC, CANTRCV_30_TJA1145_VAR_NOINIT) currentTask;
  uint8 cTaskId;
  uint8 idxRead;
  uint8 numFree;

  /* ----- Implementation ----------------------------------------------- */
  retval = E_NOT_OK;
  
  CanTrcv_EnterCritical();
  /* -- CRITICAL START -- */
  
  /* #100 Save current context: schedule-FIFO-parameters. (critical section is used) */
  idxRead     = CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead;
  numFree     = CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree;
  currentTask = &CanTrcv_30_Tja1145_ScheduleFifo[CanTrcvIndex][idxRead];
  cTaskId     = currentTask->TaskId;
  
  /* -- CRITICAL STOP -- */
  CanTrcv_LeaveCritical();

  /* #110 Check if there is something in the schedule-FIFO to be processed. */
  if (numFree < CANTRCV_30_TJA1145_NUM_TASKS)
  {
    /* #200 Task to be executed found. Do process depending on passed event. */
    if ((CANTRCV_30_TJA1145_TASK_EV_CYCLE == event) &&
        (CANTRCV_30_TJA1145_TASK_WAIT_START == currentTask->TaskState))
    {
      /* #300 Event: CYCLE and no task is currently running but another task is scheduled. Hence schedule from task level. */
      event = CANTRCV_30_TJA1145_TASK_EV_START; /* PRQA S 1338 */ /* MD_CanTrcv_30_Tja1145_17.8 */
    }    
    
    if (event == CANTRCV_30_TJA1145_TASK_EV_START)
    {
      /* #400 Event: START (critical section is used) */
      boolean doStartTask = FALSE;
      
      CanTrcv_EnterCritical();
      /* -- CRITICAL START -- */
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
      if ((currentTask->TaskState == CANTRCV_30_TJA1145_TASK_WAIT_START) && (CanTrcv_30_Tja1145_GetSyncSpiTxReq(CanTrcvIndex) == 0x00u)) /* COV_CANTRCV_LL_TJA1145_CODECOV_SYNC_INT_BY_ASYNC */
#else
      if (currentTask->TaskState == CANTRCV_30_TJA1145_TASK_WAIT_START) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
#endif
      {
        /* #410 If the current task is waiting on to be started set the task state to RUNNING not before calling the task function. This serves as semaphore. */
        currentTask->TaskState = CANTRCV_30_TJA1145_TASK_STOPPED; /* SBSW_CANTRCV_LL_TJA1145_4 */
        
        /* The task shall be started now */
        doStartTask = TRUE;
      }      
  
      /* -- CRITICAL STOP -- */
      CanTrcv_LeaveCritical();
      
    
      if (doStartTask == TRUE) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
      {
        /* #420 If the current task must be started start it (critical section is used) */
        currentTask->TaskState = CANTRCV_30_TJA1145_TASK_RUNNING; /* SBSW_CANTRCV_LL_TJA1145_4 */

        if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT) /* ESCAN00092984 */
        {
          CanTrcv_EnterCritical(); /* ESCAN00086226 */
        }
        /* #430 Call the task-function the 1st time with state STOPPED. */
        retval = CanTrcv_30_Tja1145_TaskInfoTable[cTaskId].TaskFunction(CanTrcvIndex, event, CANTRCV_30_TJA1145_TASK_STOPPED); /* SBSW_CANTRCV_HL_TJA1145_4 */
        if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT) /* ESCAN00092984 */
        {
          CanTrcv_LeaveCritical(); /* ESCAN00086226 */
        }

        if (retval == E_PENDING) 
        {
          /* #440 Task execution is pending. */
          retval = E_OK;
        }
        else
        {
          /* retval == E_OK or retval == E_NOT_OK */
          /* #450 Task has already finished / failed. (critical section is used) */
          CanTrcv_EnterCritical();
          /* -- CRITICAL START -- */
          
          /* Safety measure: only modify the FIFO read index if it was not changed meanwhile */
          if ((CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead == idxRead) &&
              (currentTask->TaskState != CANTRCV_30_TJA1145_TASK_STOPPED) &&
              (CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][cTaskId] != 0xffu)) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
          {
          
            /* #451 Modify schedule-FIFO-parameter: read index. */
            ++CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead; /* SBSW_CANTRCV_LL_TJA1145_3 */
            ++CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree; /* SBSW_CANTRCV_LL_TJA1145_3 */
            if (CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead >= CANTRCV_30_TJA1145_NUM_TASKS) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
            {
              CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead = 0; /* SBSW_CANTRCV_LL_TJA1145_3 */
            }

            /* #452 Mark the finished / failed task as inactive. This allows the rescheduling of it if required. */
            CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][cTaskId] = 0xffu; /* SBSW_CANTRCV_LL_TJA1145_1 */
            currentTask->TaskState = CANTRCV_30_TJA1145_TASK_STOPPED; /* SBSW_CANTRCV_LL_TJA1145_4 */
          }
          /* -- CRITICAL STOP -- */
          CanTrcv_LeaveCritical();        
        }
      }
      else
      {
        /* #470 Another task is currently running. This is OK. Hence do only acknowledge with OK.*/
        retval = E_OK;
      }
    }
    else
    {
      if (CANTRCV_30_TJA1145_TASK_RUNNING == currentTask->TaskState) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
      {
        /* #500 Any other EVENT: Do process only if the task is in state RUNNING. */
        CanTrcv_EnterCritical(); /* ESCAN00086226 */
        /* #510 Process the occurred event. (critical section is used) */
        retval = CanTrcv_30_Tja1145_TaskInfoTable[cTaskId].TaskFunction(CanTrcvIndex, event, CANTRCV_30_TJA1145_TASK_RUNNING); /* SBSW_CANTRCV_HL_TJA1145_4 */
        CanTrcv_LeaveCritical(); /* ESCAN00086226 */

        if ((retval == E_OK) || (retval == E_NOT_OK))
        {
          /* #520 Task execution is either completed or failed. (critical section is used) */
          CanTrcv_EnterCritical();
          /* -- CRITICAL START -- */
          
          /* Safety measure: only modify the fifo read index if it was not changed meanwhile */
          if ((CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead == idxRead) &&
              (currentTask->TaskState != CANTRCV_30_TJA1145_TASK_STOPPED) &&
              (CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][cTaskId] != 0xffu)) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
          {
          
            /* #521 Modify schedule-FIFO-parameter: read index. */
            ++CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead; /* SBSW_CANTRCV_LL_TJA1145_3 */
            ++CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].NumFree; /* SBSW_CANTRCV_LL_TJA1145_3 */
            if (CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead >= CANTRCV_30_TJA1145_NUM_TASKS) /* COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG */
            {
              CanTrcv_30_Tja1145_FifoInfo[CanTrcvIndex].IdxRead = 0; /* SBSW_CANTRCV_LL_TJA1145_3 */
            }
            
            /* #522 Mark the finished / failed task as inactive. This allows the rescheduling of it if required. */
            CanTrcv_30_Tja1145_TaskActive[CanTrcvIndex][cTaskId] = 0xffu; /* SBSW_CANTRCV_LL_TJA1145_1 */
            currentTask->TaskState = CANTRCV_30_TJA1145_TASK_STOPPED; /* SBSW_CANTRCV_LL_TJA1145_4 */
          }
          
          /* -- CRITICAL STOP -- */
          CanTrcv_LeaveCritical();
        }
        else
        {
          /* Execution of task is still PENDING. Hence do only acknowledge with OK. */
          retval = E_OK;
        }
      }
      else 
      {
        /* #600 No task is running. Hence do ignore any event and acknowledge with OK. */
        retval = E_OK;
      }
    }
  }

  return retval;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#endif


#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RdStatusTask
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RdStatusTask(uint8 CanTrcvIndex)
# else
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RdStatusTask(uint8 CanTrcvIndex, uint8 event, uint8 taskState)
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;

  /* ----- Implementation ----------------------------------------------- */
  retval = E_PENDING; /* PRQA S 2982 */ /* MD_MSR_RetVal */

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (taskState == CANTRCV_30_TJA1145_TASK_STOPPED)
# endif
  {
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (event == CANTRCV_30_TJA1145_TASK_EV_START)
    /* #200 Do start the task execution if task is in STOPPED-state and the event signals to start the task. (only if asynchronous SPI-interface) */
# endif
    {
      /* #210 Request the status-flags from CAN transceiver HW. */
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
      retval = CanTrcv_30_Tja1145_RwStatus(CanTrcvIndex, FALSE, CANTRCV_30_TJA1145_RT_RD_STATUS);
# else
      retval = CanTrcv_30_Tja1145_RwStatus(CanTrcvIndex, TRUE, CANTRCV_30_TJA1145_RT_RD_STATUS);
# endif

      /* #220 Overwrite the response OK with PENDING, because the task execution has NOT completed yet. */
      if (retval == E_OK)
      {
        retval = E_PENDING;
      }
    }
  }

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (taskState == CANTRCV_30_TJA1145_TASK_RUNNING)
# endif
  {

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (event == CANTRCV_30_TJA1145_TASK_EV_RW_STATUS)
    /* #300 Do finish the task execution if task is in RUNNING-state and the event signals that status-flags have been read successfully from CAN transceiver HW. (only if asynchronous SPI-interface) */
# else
    if (retval == E_PENDING)
    /* #301 Do finish the task execution if task is in PENDING-state. (only if synchronous SPI-interface) */
# endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF */
    {
      /* #310 Task execution has finished. */
# if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
      if (CanTrcv_30_Tja1145_GetChkWakFlagReq(CanTrcvIndex) != 0x0u)
      {
        /* #311 If required and depending on request: Do call the indication: WakeFlag. */
        CanTrcv_30_Tja1145_CheckWakeFlagIndication(CanTrcvIndex);
      }
# endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

# if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
      if (CanTrcv_30_Tja1145_GetCbByBusFlagReq(CanTrcvIndex) != 0x0u)
      {
        /* #312 If required and depending on request: Do call the indication: WakeupByBus. */
        CanTrcv_30_Tja1145_CbWakeupByBusIndication(CanTrcvIndex);
      }
# endif /* CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON */

      retval = E_OK;
    }
  }

  return retval;
}
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ClrWufFlagTask
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClrWufFlagTask(uint8 CanTrcvIndex)
# else
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ClrWufFlagTask(uint8 CanTrcvIndex, uint8 event, uint8 taskState)
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_PENDING; /* PRQA S 2981 */ /* MD_MSR_RetVal */


  /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (taskState == CANTRCV_30_TJA1145_TASK_STOPPED)
#endif
  {
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (event == CANTRCV_30_TJA1145_TASK_EV_START)
    /* #100 Do start the task execution if task is in STOPPED-state and the event signals to start the task. (only if asynchronous SPI-interface) */
#endif
    {
      /* #110 Request the status-flags from CAN transceiver HW. */
      retval = CanTrcv_30_Tja1145_RwStatus(CanTrcvIndex, FALSE, CANTRCV_30_TJA1145_RT_CLR_WUF);

      /* #120 Overwrite the response OK with PENDING, because the task execution has NOT completed yet. */
      if (retval == E_OK)
      {
        retval = E_PENDING;
      }
    }
  }

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (taskState == CANTRCV_30_TJA1145_TASK_RUNNING)
#endif
  {

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (event == CANTRCV_30_TJA1145_TASK_EV_RW_STATUS)
    /* #200 Do finish the task execution if task is in RUNNING-state and the event signals that status-flags have been read successfully from CAN transceiver HW. (only if asynchronous SPI-interface) */
#else
    if (retval == E_PENDING)
    /* #201 Do finish the task execution if task is in PENDING-state. (only if synchronous SPI-interface) */
#endif 
    {
      if (CanTrcv_30_Tja1145_GetClrWufFlagReq(CanTrcvIndex) != 0x0u) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
      {
        /* #210 Depending on request: Do call the indication: WufFlag. */
        CanTrcv_30_Tja1145_ClearTrcvWufFlagIndication(CanTrcvIndex);
      }

      retval = E_OK;
    }
  }

  return retval;
}
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CmtActionReqRwMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionReqRwMode(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint32 requestedOpMode;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* #100 Determine from global request flag which operating mode is requested. */
  requestedOpMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

  /* #200 Depending on requested operating mode change set the corresponding values for Mode-registers: CanControl and ModeControl. */
  switch (requestedOpMode)
  {
  case CanTrcv_30_Tja1145_Req_OpModeNormal:
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite = CanTrcv_30_Tja1145_Cc_CMC_Normal; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite = CanTrcv_30_Tja1145_Mc_MC_Normal; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  case CanTrcv_30_Tja1145_Req_OpModeStandby:
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite = CanTrcv_30_Tja1145_Cc_CMC_Offline; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite = CanTrcv_30_Tja1145_Mc_MC_Standby; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  case CanTrcv_30_Tja1145_Req_OpModeSleep: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite = CanTrcv_30_Tja1145_Cc_CMC_Offline; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite = CanTrcv_30_Tja1145_Mc_MC_Sleep; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    /* Maybe Det */
    break;
  }

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable == TRUE)
  {
    /* #210 If required: Enable the PN within the CAN transceiver HW. */

    /* #211 Set the HW-register bit that PN configuration is OK. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite |= CanTrcv_30_Tja1145_Cc_PNCOK; /* SBSW_CANTRCV_HL_TJA1145_1 */

    if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE)
    {
      /* #212 If PN is enabled in SW in addition set HW-register bit to enable the PN in CAN transceiver HW. */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite |= CanTrcv_30_Tja1145_Cc_CPNC; /* SBSW_CANTRCV_HL_TJA1145_1 */
    }
  }
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

#if (CANTRCV_30_TJA1145_FD_TOLERANCE == STD_ON)
  if (CanTrcv_IsFdToleranceEnabled(CanTrcvIndex))
  {
    /* #220 If required: Enable the FD-tolerance within the CAN transceiver HW. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite |= (CanTrcv_30_Tja1145_Cc_CFDC); /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
#endif /* CANTRCV_30_TJA1145_FD_TOLERANCE == STD_ON */

  /* #300 Request the SPI to transmit the prepared HW-register. */
  retVal = CanTrcv_30_Tja1145_RwMode(CanTrcvIndex, doSync);

  return retVal;
} /* CanTrcv_30_Tja1145_CmtActionReqRwMode */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CmtActionReqRwStatus
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionReqRwStatus(uint8 CanTrcvIndex, boolean doSync)
{
  Std_ReturnType retVal;

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
  if ( (CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex) == CanTrcv_30_Tja1145_Req_OpModeNormal) &&
       (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT) ) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
  {
    /* #100 In case of operating mode NORMAL set and the CAN transceiver channel is already initialized: Set the request to confirm the availability of PN (if available). */
    CanTrcv_30_Tja1145_SetConfirmPnAvailabilityReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

  /* #110 Request all status-flags and by the way clear them. */
  retVal = CanTrcv_30_Tja1145_RwStatus(CanTrcvIndex, doSync, CANTRCV_30_TJA1145_RT_CLR_ALL);

  return retVal;
} /* CanTrcv_30_Tja1145_CmtActionReqRwStatus */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_VerifyOpMode
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_VerifyOpMode(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  Std_ReturnType newRequestPending;
  uint32 oldModeReq;
#endif

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  /* #100 Save the current operating mode request. (only if asynchronous SPI-interface) */
  oldModeReq = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

  /* #110 Get the next operating mode request. Do replace current operating mode request with the new one. (only if asynchronous SPI-interface) */
  newRequestPending = CanTrcv_30_Tja1145_ProcessNextOpModeReq(CanTrcvIndex);

  if ( (newRequestPending == E_OK) && (oldModeReq != CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex)) )
  {
    /* #200 Actually another operating mode change request is pending. (only if asynchronous SPI-interface) */ 

    /* #210 Reschedule the operating mode change task. (only if asynchronous SPI-interface) */
    (void)CanTrcv_30_Tja1145_ReSchedule(CanTrcvIndex, CANTRCV_30_TJA1145_TASK_ID_CHANGE_OP_MODE);
    /* #220 Do response PENDING, because the operating mode change has NOT completed yet. (only if asynchronous SPI-interface) */
    retVal = E_PENDING;
  }
  else
#endif
  {
    uint32 requestedOpMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

    /* #300 Operating mode change finished seemingly and NO other operating mode change requested in between. */

    /* #310 Verify if the requested operating mode change was executed successfully by comparing of written values of HW-registers with read ones.  */
    if ( (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite == CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlRead) )
    {
      uint8 maskedModeControlRead  = (uint8)(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlRead&CanTrcv_30_Tja1145_Mc_MC_Mask);
      uint8 maskedModeControlWrite = (uint8)(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite&CanTrcv_30_Tja1145_Mc_MC_Mask);

      /* #320 Do response OK if verification passed. */
      if ( CanTrcv_30_Tja1145_Req_OpModeSleep == requestedOpMode ) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
      {
        /* Automatic mode change SLEEP->STANDBY may occur.
         * Thus MC is considered valid if it is either SLEEP or STANDBY
         */
        if ( (CanTrcv_30_Tja1145_Mc_MC_Sleep == maskedModeControlRead) || (CanTrcv_30_Tja1145_Mc_MC_Standby == maskedModeControlRead) ) /* COV_CANTRCV_LL_TJA1145_CODECOV_HW_FAILURE */
        {
          retVal = E_OK;
        }
      }
      else
      {
        /* Normal / Standby: ModeControlWrite must be the same as ModeControlRead, at least for the valid bits */
        if ( maskedModeControlWrite == maskedModeControlRead ) /* COV_CANTRCV_LL_TJA1145_CODECOV_HW_FAILURE */
        {
          retVal = E_OK;
        }
      }
    }
  }

  return retVal;
} /* CanTrcv_30_Tja1145_VerifyOpMode */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CmtActionWaitRwMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtActionWaitRwMode(uint8 CanTrcvIndex)
{
  Std_ReturnType retVal;

  /* #100 Verify if the requested operating mode change was executed successfully by comparing of written values of HW-registers with read ones.  */
  retVal = CanTrcv_30_Tja1145_VerifyOpMode(CanTrcvIndex);

  if (retVal == E_OK)
  {
    /* #200 If verification passed: */

#if ((CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON))
    /* Save the finished request, because this one is reseted within the ModeIndication. */
    uint32 requestedOpMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);
#endif

    /* #210 Do indicate higher layer. */
    CanTrcv_30_Tja1145_TrcvModeIndication(CanTrcvIndex, TRUE);

#if ((CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON))
    if ( (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT) &&
         (requestedOpMode == CanTrcv_30_Tja1145_Req_OpModeNormal) &&
         (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable == FALSE) )
    {
      /* #220 If CAN transceiver channel is initialized, operating mode is NORMAL and PN is NOT available: Start the ReInit-task in order to reinitialize the PN-configuration. (only if configured) */
# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
      CanTrcv_30_Tja1145_SetReInitPnReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
# endif
      (void)CanTrcv_30_Tja1145_StartTaskReInit(CanTrcvIndex); /* Return value can be ignored */
    }
#endif /* (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) && (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */
  }

  return retVal;
} /* CanTrcv_30_Tja1145_CmtActionWaitRwMode */


#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ChangeModeTaskSync
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ChangeModeTaskSync(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint32 requestedOpMode;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;
  requestedOpMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

  if (requestedOpMode == CanTrcv_30_Tja1145_Req_OpModeNormal)
  {
    /* #100 In case of requested mode is NORMAL request and clear the status flags of CAN transceiver HW. */
    if (CanTrcv_30_Tja1145_CmtActionReqRwStatus(CanTrcvIndex, TRUE) == E_OK)
    {
      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  /* #110 Do further processing only if the previous one succeeded. */
  if (retVal == E_OK)
  {
    /* #120 Re-set the return value to not OK for further processing. */
    retVal = E_NOT_OK;

    /* #130 Request the CAN transceiver HW to change the operating mode. */
    if (CanTrcv_30_Tja1145_CmtActionReqRwMode(CanTrcvIndex, TRUE) == E_OK)
    {
      /* #140 Verify whether the operating mode was set successfully. */
      if (CanTrcv_30_Tja1145_CmtActionWaitRwMode(CanTrcvIndex) == E_OK)
      {
         /* #150 Return OK only if every step passed successfully. */
        retVal = E_OK;
      }
    }
  }

  if (retVal == E_NOT_OK)
  {
    /* #200 If change of operating mode FAILED: */ 

    /* #210 Indicate the higher layer about the last successful operating mode change. */
    /* NOTE: The successful indication is thrown within API: CanTrcv_30_Tja1145_CmtActionWaitRwMode(). */
    CanTrcv_30_Tja1145_TrcvModeIndication(CanTrcvIndex, FALSE);

    /* #220 Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}

#else /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_AnyTaskConditionalContinue
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_AnyTaskConditionalContinue(uint8 CanTrcvIndex, uint8 eVal, uint8 nextSubState, uint8 failSubState)
{
  /* ----- Implementation ----------------------------------------------- */
  if (eVal == E_OK)
  {
    /* #100 Do set the sub-state of state machine to <nextSubState> in case of <eVal> is E_OK. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = nextSubState; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
  else
  {
    /* eVal == E_NOT_OK */
    /* #110 Do set the sub-state of state machine to <failSubState> in case of <eVal> is E_NOT_OK. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = failSubState; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
}

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_CmtGetNextAction
 **********************************************************************************************************************/
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
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(uint8, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_CmtGetNextAction(uint8 taskState, uint8 currentSubState, uint8 event, boolean doSync) 
{
  /* ----- Local Variables ---------------------------------------------- */
   uint8 nextAction;

   /* ----- Implementation ----------------------------------------------- */
   /* Set default: nothing to do */
   nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;

   /* #100 Do a conversion of <taskState>, <currentSubState>, <event> and <doSync> into an ACTION */
   if (taskState == CANTRCV_30_TJA1145_TASK_STOPPED)
   {
     if ((currentSubState == CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE) && (event == CANTRCV_30_TJA1145_TASK_EV_START))
     {
        nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_START_TASK;
     }
   }
   else if (taskState == CANTRCV_30_TJA1145_TASK_RUNNING)
   {
    switch(currentSubState) {
    case CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_STATUS:
      if ((event == CANTRCV_30_TJA1145_TASK_EV_CYCLE) || (doSync == TRUE)) {
        nextAction = CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_STATUS;
      }
      break;
    case CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_STATUS:
      if ((event == CANTRCV_30_TJA1145_TASK_EV_RW_STATUS) || (doSync == TRUE))
      {
        nextAction = CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_STATUS;
      }
      break;
    case CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_MODE:
      if ((event == CANTRCV_30_TJA1145_TASK_EV_CYCLE) || (doSync == TRUE)) {
        nextAction = CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_MODE;
      }
      break;
    case CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_MODE:
      if ((event == CANTRCV_30_TJA1145_TASK_EV_RW_MODE) || (doSync == TRUE))
      {
        nextAction = CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_MODE;
      }
      break;
    case CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED:
      nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_FAILED;
      break;
    default:
      nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;
      break;
    }
   }
   else
   {
     nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;
   }

  return nextAction;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ChangeModeTaskAsync
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ChangeModeTaskAsync(uint8 CanTrcvIndex, uint8 event, uint8 taskState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 currentSubState, action;
  boolean doSync;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_PENDING; /* PRQA S 2982 */ /* MD_MSR_RetVal */

  /* #100 In case of context: initialization: Process this task in synchronous manner. In addition all indications must be suppressed. */
  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT)
  {
    doSync = FALSE;
  }
  else
  {
    doSync = TRUE;
  }


  /* #200 Initialize for 1st run:  What is the actual sub-state of the state machine? */
  currentSubState = CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState;
  /* #210 Initialize for 1st run: Determine what is next action to be done? */
  action = CanTrcv_30_Tja1145_CmtGetNextAction(taskState, currentSubState, event, doSync);

  do
  {
    /* #220 Execute the next ACTION to be done. */
    switch(action)
    {
      case CANTRCV_30_TJA1145_ANYT_ACTION_START_TASK:
      {
        /* Context: ANY */
        /* #300 Execute the ACTION: start the task */
        uint32 requestedOpMode = CanTrcv_30_Tja1145_GetOpModeReq(CanTrcvIndex);

        retVal = E_PENDING;

        if ( requestedOpMode == CanTrcv_30_Tja1145_Req_OpModeNormal )
        {
          /* CanTrcv220 */
          /* #310 In case of requested mode is NORMAL: 1st: Do request and clear the status flags of CAN transceiver HW. */
          CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_STATUS; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }
        else
        {
          /* SysWrite + Verify */
          /* #320 In case of requested mode is either STANDBY / SLEEP: 1st: Do request to change the operating mode.  */
          CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_MODE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }

        /* #330 In case of context: initialization: the whole task must run at once. */
        if (doSync == TRUE)
        {
          taskState = CANTRCV_30_TJA1145_TASK_RUNNING; /* PRQA S 1338 */ /* MD_CanTrcv_30_Tja1145_17.8 */
        }
      }
      break;

      case CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_STATUS:
      {
        /* #400 Execute the ACTION: Read from and by the way clear the status flags within the CAN transceiver HW. */
        retVal = CanTrcv_30_Tja1145_CmtActionReqRwStatus(CanTrcvIndex, doSync);

        /* #410: Determine from execution status of last action the next SUBSTATE: Wait on completeness of 400 or FAILED. */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_STATUS, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
        retVal = E_PENDING;
      }
      break;

      
      case CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_STATUS:
      {
        /* Context: SPI Indication */
        /* #500: Execute the ACTION: The ACTIONs 4XX completed hence the change of operating mode may be requested (ACTIONs: 6XX). */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_CMT_SUBSTATE_REQ_RW_MODE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        retVal = E_PENDING;
      }
      break;

      /* -- E STANDBY, SLEEP */
      case CANTRCV_30_TJA1145_CMT_ACTION_REQ_RW_MODE:
      {
        /* Context: Cyclic Task */
        /* #600 Execute the ACTION: Request the change of operating mode via the SPI. */
        retVal = CanTrcv_30_Tja1145_CmtActionReqRwMode(CanTrcvIndex, doSync);

        /* #610: Determine from execution status of last action the next SUBSTATE: Wait on completeness of 600 or FAILED. */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_CMT_SUBSTATE_WAIT_RW_MODE, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);

        retVal = E_PENDING;
      }
      break;

      case CANTRCV_30_TJA1145_CMT_ACTION_WAIT_RW_MODE:
      {
        /* Context: SPI Indication */
        /* #700: Execute the ACTION: Verify whether the operating mode was set up successfully in HW or NOT. */
        retVal = CanTrcv_30_Tja1145_CmtActionWaitRwMode(CanTrcvIndex);

        /* E_PENDING indicates that any mode-change-request was re-scheduled in-between (may only happen in case of asynchronous-SPI).
         * Hence the task to change the operating mode is NOT completed yet! But the SUBSTATE must be reseted as well in order to allow a new
         * mode transition. */
        if ((retVal == E_OK) || (retVal == E_PENDING))
        {
          /* #710: Verification passed (either OK or PENDING (== the operating mode change was re-scheduled in between)): Reset the SUBSTATE to IDLE. */
          CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        }
        else
        {
          /* At least: retval == E_NOT_OK  */
          /* #720: Verification of operating mode FAILED: Set the SUBSTATE to FAILED to indicate a failure. */
          CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED; /* SBSW_CANTRCV_HL_TJA1145_1 */
          retVal = E_OK; /* Indicates task finished... */
        }
      }
      break;

      case CANTRCV_30_TJA1145_ANYT_ACTION_NONE:
      {
        /* This one may happen in case of asynchronous-SPI */
        retVal = E_PENDING;
      }
      break;

      case CANTRCV_30_TJA1145_ANYT_ACTION_FAILED:
      {
        /* Context: ANY */
        /* #800: Execute the ACTION: Change of operating mode FAILED: */ 

        /* #810 Indicate the higher layer about the last successful operating mode change. */
        CanTrcv_30_Tja1145_TrcvModeIndication(CanTrcvIndex, FALSE);

        /* #820 Re-set the SUBSTATE to IDLE, task has completed. */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* #830 Unlock the SPI. */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* #840 Response ERROR to caller. */
        retVal = E_NOT_OK;
      }
      break;

      default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
      {
        retVal = E_NOT_OK;
      }
      break;
    } /* SWITCH */

    /* #230 Update the actual SUBSTATE */
    currentSubState = CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState;
    /* #240 Update the next ACTION */
    action = CanTrcv_30_Tja1145_CmtGetNextAction(taskState, currentSubState, event, doSync);

    /* #250 Continue the execution of task until there is nothing to be done anymore or the task completes. */
  } while ((currentSubState != CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE) && (action != CANTRCV_30_TJA1145_ANYT_ACTION_NONE));

  return retVal;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif /* CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON */

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionReqWrIdMask
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqWrIdMask(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqInfoBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Prepare a SPI-transmission block for write-access of content: BaudRate, CanId2, CanIdMask1 and FrameControl. */
  write_block(seqInfoBlock.block[0], CanTrcv_30_Tja1145_Dr,  3, &CanTrcv_GetBaudrate(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[1], CanTrcv_30_Tja1145_Id2, 3, &CanTrcv_GetCanId2(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[2], CanTrcv_30_Tja1145_Mk1, 3, &CanTrcv_GetCanIdMask1(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[3], CanTrcv_30_Tja1145_Fc,  1, &CanTrcv_GetFrameControl(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqInfoBlock.numberOfBlocks = 4;
  /* #101 Lock the SPI. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_IDMASKDB; /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #110 Request the SPI to transmit the prepared SPI-transmission block. */
  retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqInfoBlock, doSync); /* SBSW_CANTRCV_HL_TJA1145_3 */

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  if (retVal == E_OK)
  {
    /* #120 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
    CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
  }
  else
# else
  if (retVal == E_NOT_OK)
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
  {
    /* #130 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}

# if ((CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)) /* COV_CANTRCV_LL_TJA1145_VARCOV_INVALID_MEASURE */
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionReqRdIdMask
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRdIdMask(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqInfoBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Prepare a SPI-transmission block for read-access of content: BaudRate, CanId2, CanIdMask1 and FrameControl. */
  read_block(seqInfoBlock.block[0], CanTrcv_30_Tja1145_Dr,  3, &CanTrcv_GetBaudrate(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  read_block(seqInfoBlock.block[1], CanTrcv_30_Tja1145_Id2, 3, &CanTrcv_GetCanId2(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  read_block(seqInfoBlock.block[2], CanTrcv_30_Tja1145_Mk1, 3, &CanTrcv_GetCanIdMask1(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  read_block(seqInfoBlock.block[3], CanTrcv_30_Tja1145_Fc,  1, &CanTrcv_GetFrameControl(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqInfoBlock.numberOfBlocks = 4;
  /* #101 Lock the SPI. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_IDMASKDB; /* SBSW_CANTRCV_HL_TJA1145_1 */
  
  /* #110 Request the SPI to transmit the prepared SPI-transmission block. */
  retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqInfoBlock, doSync); /* SBSW_CANTRCV_HL_TJA1145_3 */

#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  if (retVal == E_OK)
  {
    /* #120 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
    CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
  }
  else
#  else
  if (retVal == E_NOT_OK)
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
  {
    /* #130 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionWaitRdIdMask
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRdIdMask(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 i;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_OK;

  /* #100 Verify written data of BaudRate, CanId2, CanIdMask1 and FrameControl.  */
  for (i = 0; i < 14u; ++i)
  {
    /* Don't compare the read-back of the address. ATMEL ATA6570 only: No address will be read back, therefor necessary for this hardware. */
    if ( (i == 0u) || (i == 4u) || (i == 8u) || (i == 12u) )
    {
      /* Do nothing. Only the value of the registers should be compared, not the target adress, which is not part of the pn config. */
    }
    else
    {
      /* Compare read data with written one */
      if (CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][i] != CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][i])
      {
        retVal |= E_NOT_OK;
        break; /* One mismatch found NO further process required */
      }
    }
  }

  return retVal;
}
# endif /* (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionReqWrDb
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqWrDb(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqInfoBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Prepare a SPI-transmission block for write-access of content: DataMask0 till DataMask7. */
  write_block(seqInfoBlock.block[0], CanTrcv_30_Tja1145_Db0, 3, &CanTrcv_GetDataMask0(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[1], CanTrcv_30_Tja1145_Db3, 3, &CanTrcv_GetDataMask3(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqInfoBlock.block[2], CanTrcv_30_Tja1145_Db6, 2, &CanTrcv_GetDataMask6(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqInfoBlock.numberOfBlocks = 3;
  /* #101 Lock the SPI */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_IDMASKDB; /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #110 Request the SPI to transmit the prepared SPI-transmission block. */
  retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqInfoBlock, doSync); /* SBSW_CANTRCV_HL_TJA1145_3 */

# if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  if (retVal == E_OK)
  {
    /* #120 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
    CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
  }
  else
# else
  if (retVal == E_NOT_OK)
# endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
  {
    /* #130 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}

# if ((CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON))  /* COV_CANTRCV_LL_TJA1145_VARCOV_INVALID_MEASURE */
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionReqRdDb
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRdDb(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqInfoBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Prepare a SPI-transmission block for read-access of content: DataMask0 till DataMask7. */
  read_block(seqInfoBlock.block[0], CanTrcv_30_Tja1145_Db0, 3, &CanTrcv_GetDataMask0(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  read_block(seqInfoBlock.block[1], CanTrcv_30_Tja1145_Db3, 3, &CanTrcv_GetDataMask3(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  read_block(seqInfoBlock.block[2], CanTrcv_30_Tja1145_Db6, 2, &CanTrcv_GetDataMask6(CanTrcvIndex)); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqInfoBlock.numberOfBlocks = 3;
  /* #101 Lock SPI. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_IDMASKDB; /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #110 Request the SPI to transmit the prepared SPI-transmission block. */
  retVal = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqInfoBlock, doSync); /* SBSW_CANTRCV_HL_TJA1145_3 */

#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  if (retVal == E_OK)
  {
    /* #120 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
    CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
  }
  else
#  else
  if (retVal == E_NOT_OK)
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
  {
    /* #130 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionWaitRdDb
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRdDb(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 i;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_OK;

  /* #100 Verify written data of DataMask0 till DataMask7. */
  for (i = 0; i < 11u; ++i)
  {
    /* Don't compare the read-back of the address. ATMEL ATA6570 only: No address will be read back, therefor necessary for this hardware. */
    if ( (i == 0u) || (i == 4u) || (i == 8u))
    {
      /* Do nothing. Only the value of the registers should be compared, not the target adress, which is not part of the pn config. */
    }
    else
    {
      /* Compare read data with written one */
      if (CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][i] != CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][i])
      {
          retVal |= E_NOT_OK;
          break; /* One mismatch found NO further process required */
      }
    }
  }

  return retVal;
}
# endif /* (CANTRCV_30_TJA1145_VERIFY_DATA == STD_ON) || (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */

# if (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON)
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionReqRwMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionReqRwMode(uint8 CanTrcvIndex, boolean doSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Set the HW-register bit that PN configuration is OK. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite |= CanTrcv_30_Tja1145_Cc_PNCOK; /* ESCAN00083361 */ /* SBSW_CANTRCV_HL_TJA1145_1 */

  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE)
  {
     /* #110 If PN is enabled in SW in addition set HW-register bit to enable PN in CAN transceiver HW. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite |= CanTrcv_30_Tja1145_Cc_CPNC; /* ESCAN00083361 */ /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  /* #120 Request the SPI to transmit the prepared HW-register. */
  retVal = CanTrcv_30_Tja1145_RwMode(CanTrcvIndex, doSync);

  return retVal;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitActionWaitRwMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitActionWaitRwMode(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Verify if operating mode configuration and PN-configuration have been applied within the CAN transceiver HW.  */
  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite != CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlRead)
  {
    retVal = E_NOT_OK;
  }
  if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite != CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlRead)
  {
    retVal = E_NOT_OK;
  }

  if (retVal == E_OK)
  {
    /* #110 If verification passed: Re-enable PN in software: PN is available again! */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].pnAvailable = TRUE; /* SBSW_CANTRCV_HL_TJA1145_1 */

    /* #120 If PN is enabled in SW inform the CanIf about PN availability. */
    if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isPnEnabled == TRUE)
    {
      CanIf_30_Tja1145_ConfirmPnAvailability(CanTrcvIndex);
    }
  }

  return retVal;
}


#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReInitTaskSync
 **********************************************************************************************************************/
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
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReInitTaskSync(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;

  /* #100 Write content of IdMask into CAN transceiver HW. */
  if (CanTrcv_30_Tja1145_RitActionReqWrIdMask(CanTrcvIndex, TRUE) == E_OK)
  {
    /* #110 Read content of IdMask from CAN transceiver HW. */
    if (CanTrcv_30_Tja1145_RitActionReqRdIdMask(CanTrcvIndex, TRUE) == E_OK)
    {
      /* #120 Verify content of IdMask (compare written data with read one). */
      if (CanTrcv_30_Tja1145_RitActionWaitRdIdMask(CanTrcvIndex) == E_OK)
      {
        /* #130 Write content of Db into CAN transceiver HW. */
        if (CanTrcv_30_Tja1145_RitActionReqWrDb(CanTrcvIndex, TRUE) == E_OK)
        {
          /* #140 Read content of Db from CAN transceiver HW. */
          if (CanTrcv_30_Tja1145_RitActionReqRdDb(CanTrcvIndex, TRUE) == E_OK)
          {
            /* #150 Verify content of Db (compare written data with read one). */
            if (CanTrcv_30_Tja1145_RitActionWaitRdDb(CanTrcvIndex) == E_OK)
            {
              /* #160 Write content of Mode into CAN transceiver HW. */
              if (CanTrcv_30_Tja1145_RitActionReqRwMode(CanTrcvIndex, TRUE) == E_OK)
              {
                /* #170 Verify content of Mode (compare written data with read one). */
                if (CanTrcv_30_Tja1145_RitActionWaitRwMode(CanTrcvIndex) == E_OK)
                {
                  /* #180 Return OK only if every step passed successfully. */
                  retVal = E_OK;
                }
              }
            }
          }
        }
      }
    }
  }

  if (retVal == E_NOT_OK)
  {
    /* #200 Reinitialization of PN-configuration FAILED: */

    /* #210 Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

# else /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RitGetNextAction
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL_INLINE FUNC(uint8, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RitGetNextAction(uint8 taskState, uint8 currentSubState, uint8 event)
{
  /* ----- Local Variables ---------------------------------------------- */
   uint8 nextAction;

   /* ----- Implementation ----------------------------------------------- */
   /* #100 Do a conversion of <taskState>, <currentSubState> and <event> into an ACTION */

   /* Set default: nothing to do */
   nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;

   if (taskState == CANTRCV_30_TJA1145_TASK_STOPPED)
   {
     if ((currentSubState == CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE) && (event == CANTRCV_30_TJA1145_TASK_EV_START))
     {
        nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_START_TASK;
     }
   }
   else if (taskState == CANTRCV_30_TJA1145_TASK_RUNNING)
   {
    switch(currentSubState)
    {
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_IDMASK:
      if (event == CANTRCV_30_TJA1145_TASK_EV_CYCLE) {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_IDMASK;
      }
      break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_IDMASK:
      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_IDMASK;
      }
      break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_IDMASK:
      if (event == CANTRCV_30_TJA1145_TASK_EV_CYCLE) {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_IDMASK;
      }
      break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_IDMASK:
      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_IDMASK;
      }
      break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_DB:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_CYCLE)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_DB;
      }
    }
    break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_DB:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_DB;
      }
    }
    break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_DB:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_CYCLE)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_DB;
      }
    }
    break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_DB:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_DB;
      }
    }
    break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RW_MODE:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_CYCLE)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_REQ_RW_MODE;
      }
    }
    break;
    case CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RW_MODE:
    {
      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_MODE)
      {
        nextAction = CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RW_MODE;
      }
    }
    break;
    case CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED:
      nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_FAILED;
      break;
    default:
      nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;
      break;
    }
   }
   else
   {
     nextAction = CANTRCV_30_TJA1145_ANYT_ACTION_NONE;
   }

  return nextAction;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_ReInitTaskAsync
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_ReInitTaskAsync(uint8 CanTrcvIndex, uint8 event, uint8 taskState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType taskRetVal;
  uint8 action, currentSubState;

  /* ----- Implementation ----------------------------------------------- */
  taskRetVal = E_PENDING;

  /* #200 Initialize for 1st run: What is the actual SUBSTATE? */
  currentSubState = CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState;
  /* #210 Initialize for 1st run: What is the next ACTION to be done? */
  action = CanTrcv_30_Tja1145_RitGetNextAction(taskState, currentSubState, event);

  do
  {
    /* #220 Execute the next ACTION to be done. */
    switch(action)
    {
      case CANTRCV_30_TJA1145_ANYT_ACTION_START_TASK:
      {
        /* Context: ANY */
        /* #300 Execute the ACTION: Start this task: Next SUBSTATE is to write content of IdMask into CAN transceiver HW.  */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_IDMASK; /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_IDMASK:
      {
        /* #400 Execute ACTION: Write content of IdMask into CAN transceiver HW. */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionReqWrIdMask(CanTrcvIndex, FALSE);

        /* #410 Determine from execution status of last action the next SUBSTATE: Wait on completeness of 400 or FAILED.  */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_IDMASK, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_IDMASK:
      {
        /* #500 Execute the ACTION: The ACTIONs 4XX completed hence the content of IdMask from CAN transceiver HW may be read. (ACTIONs: 6XX). */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_IDMASK; /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_IDMASK:
      {
        /* #600 Execute the ACTION: Read content of IdMask from CAN transceiver HW. */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionReqRdIdMask(CanTrcvIndex, FALSE);

        /* #610 Determine from execution status of last action the next SUBSTATE: Verify content of IdMask or FAILED.  */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_IDMASK, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_IDMASK:
      {
        /* #700 Execute the ACTION: Verify content of IdMask (compare written data with read one). */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionWaitRdIdMask(CanTrcvIndex);

        /* #710 Determine from execution status of last action the next SUBSTATE: Write content of Db into CAN transceiver HW or FAILED.  */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_WR_DB, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_REQ_WR_DB:
      {
        /* #800 Execute the ACTION: Write content of Db into CAN transceiver HW.  */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionReqWrDb(CanTrcvIndex, FALSE);

        /* #810 Determine from execution status of last action the next SUBSTATE: Wait on completeness of 800 or FAILED.  */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_WR_DB, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_WAIT_WR_DB:
      {
        /* #900 Execute the ACTION: The ACTIONs 8XX completed hence the content of Db from CAN transceiver HW may be read. (ACTIONs: 10XX). */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RD_DB; /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_REQ_RD_DB:
      {
        /* #1000 Execute ACTION: Read content of Db from CAN transceiver HW. */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionReqRdDb(CanTrcvIndex, FALSE);
        
        /* #1010 Determine from execution status of last action the next SUBSTATE: Verify content of Db of 1000 or FAILED.  */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RD_DB, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RD_DB:
      {
        /* #1100 Verify content of Db (compare written data with read one). */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionWaitRdDb(CanTrcvIndex);

        /* #1110 Determine from execution status of last action the next SUBSTATE: Write content of Mode into CAN transceiver HW or FAILED. */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_REQ_RW_MODE, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_REQ_RW_MODE:
      {
        /* #1200 Execute ACTION: Write content of Mode into CAN transceiver HW and by the way try to enable the PN-functionality within the CAN transceiver HW. */
        Std_ReturnType retVal;
        retVal = CanTrcv_30_Tja1145_RitActionReqRwMode(CanTrcvIndex, FALSE);

        /* #1210 Determine from execution status of last action the next SUBSTATE: Verify content of Mode or FAILED. */
        CanTrcv_30_Tja1145_AnyTaskConditionalContinue(CanTrcvIndex, retVal, CANTRCV_30_TJA1145_RIT_SUBSTATE_WAIT_RW_MODE, CANTRCV_30_TJA1145_ANYT_SUBSTATE_FAILED);
      }
      break;

      case CANTRCV_30_TJA1145_RIT_ACTION_WAIT_RW_MODE:
      {
        /* #1300 Execute ACTION: Verify content of Mode (compare written data with read one).  */
        taskRetVal = CanTrcv_30_Tja1145_RitActionWaitRwMode(CanTrcvIndex); /* ESCAN00093677 */

        /* #1310 Reset the SUBSTATE to IDLE because TASK has completed. */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* #1320 Clear the request flag, because the TASK has completed. */
        CanTrcv_30_Tja1145_ClrReInitPnReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      break;

      case CANTRCV_30_TJA1145_ANYT_ACTION_NONE:
      {
        /* This one may happen in case of asynchronous-SPI. */
        /* #1400 Execute ACTION: NONE: Just return PENDING to indicate that the task execution is still in progress. */
        taskRetVal = E_PENDING;
      }
      break;

      case CANTRCV_30_TJA1145_ANYT_ACTION_FAILED:
      {
        /* #1500 Execute the ACTION: Re-initialization of PN-configuration of CAN transceiver HW has FAILED: Unlock the SPI. */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        taskRetVal = E_NOT_OK;

        /* #1510 Reset the SUBSTATE to IDLE, because the TASK has completed. */
        CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState = CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        
        /* #1520 Clear the request flag, because the TASK has completed. */
        CanTrcv_30_Tja1145_ClrReInitPnReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_TJA1145_1 */
      }
      break;

      default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
      {
        taskRetVal = E_NOT_OK;
      }
      break;
    } /* SWITCH */

    /* #230 Update the actual SUBSTATE. */
    currentSubState = CanTrcv_30_Tja1145_Prob[CanTrcvIndex].WorkerSubState;
    /* #240 Update the next ACTION. */
    action = CanTrcv_30_Tja1145_RitGetNextAction(taskState, currentSubState, event);
    /* #250 Continue the execution of task until there is nothing to be done anymore or the task completes.  */
  } while ((currentSubState != CANTRCV_30_TJA1145_ANYT_SUBSTATE_NONE) && (action != CANTRCV_30_TJA1145_ANYT_ACTION_NONE));
  
  return taskRetVal;
} /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#  endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
# endif /* (CANTRCV_30_TJA1145_AUTO_REINIT == STD_ON) */
#endif /* (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RequestStatus
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RequestStatus(uint8 CanTrcvIndex, uint16 whichFlags)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Get status flags depending on value of <whichFlags>. */
  switch(whichFlags)
  {
  case CANTRCV_30_TJA1145_GET_SF_INIT:
    /* #110 Get status flags for initialization. This has to be done synchronous. Hence no task required. */
    retval = CanTrcv_30_Tja1145_RwStatus(CanTrcvIndex, TRUE, CANTRCV_30_TJA1145_RT_CLR_ALL);
    break;

  default:
# if (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON)
    /* #120 Request the status flags via the task. */
    retval = CanTrcv_30_Tja1145_StartTaskRdStatus(CanTrcvIndex);

#  if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
    if (retval == E_PENDING)
    {
      /* #130 In case of E_PENDING is returned: It is OK to query the same old flags. (only if asynchronous SPI-interface) */
      retval = E_OK;
    }
#  endif
# else
    retval = E_NOT_OK;
# endif
    break;
  }

  return retval;
}
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_PrepareTxBlock
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_PrepareTxBlock(uint8 CanTrcvIndex, uint8 blockIdx, P2CONST(CanTrcv_30_Tja1145_SpiTxBlockSeqType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) blockInfo, Spi_ChannelType spiChannel)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 i;
  uint8 bufferSize;
  uint8 bufferOffset;
  Std_ReturnType retval;
  P2CONST(CanTrcv_30_Tja1145_SpiTxBlockType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) curBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Initialize local variables concerning: block, buffer-size, buffer-offset and out-buffer according to passed parameters. */
  curBlock = &blockInfo->block[blockIdx];
  bufferSize = curBlock->size + 1u;
  bufferOffset = (uint8)(blockIdx << 2);
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][bufferOffset] = curBlock->reg; /* SBSW_CANTRCV_LL_TJA1145_5 */

  /* #110 Copy data into out-buffer. */
  if (curBlock->ptr != NULL_PTR)
  {
    for (i = 1; i < bufferSize; ++i)
    {
      CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][bufferOffset + i] = curBlock->ptr[i-1u]; /* SBSW_CANTRCV_LL_TJA1145_5 */
    }
  }

  /* #120 Set up the previously initialized out-buffer as external buffer within the SPI-driver. */
  retval = Spi_SetupEB(
      spiChannel,
      &CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][bufferOffset],
      &CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][bufferOffset],
      bufferSize); /* SBSW_CANTRCV_LL_TJA1145_5 */

  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SpiTransmitBlock
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiTransmitBlock(uint8 CanTrcvIndex, P2CONST(CanTrcv_30_Tja1145_SpiTxBlockSeqType, AUTOMATIC, CANTRCV_30_TJA1145_APPL_VAR) blockInfo, boolean isSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  Spi_SequenceType sequence;

  /* ----- Implementation ----------------------------------------------- */
  retval = E_OK;

  /* #100 Prepare the external buffer for transmission via the SPI-driver according to passed parameters.  */
  switch(blockInfo->numberOfBlocks) {
  case 4:
    retval  = CanTrcv_30_Tja1145_PrepareTxBlock(CanTrcvIndex, 3, blockInfo,
                                                  CanTrcv_GetCanTrcvSpiChRWData_3(CanTrcvIndex)); /* SBSW_CANTRCV_HL_TJA1145_3 */
    /* This comment is required to fix: ESCAN00087596. */
  case 3: /* PRQA S 2003 */ /* MD_CanTrcv_30_Tja1145_2003 */
    retval |= CanTrcv_30_Tja1145_PrepareTxBlock(CanTrcvIndex, 2, blockInfo,
                                                  CanTrcv_GetCanTrcvSpiChRWData_2(CanTrcvIndex)); /* SBSW_CANTRCV_HL_TJA1145_3 */
    retval |= CanTrcv_30_Tja1145_PrepareTxBlock(CanTrcvIndex, 1, blockInfo,
                                                  CanTrcv_GetCanTrcvSpiChRWData_1(CanTrcvIndex)); /* SBSW_CANTRCV_HL_TJA1145_3 */
    /* This comment is required to fix: ESCAN00087596. */
  case 1: /* PRQA S 2003 */ /* MD_CanTrcv_30_Tja1145_2003 */
    retval |= CanTrcv_30_Tja1145_PrepareTxBlock(CanTrcvIndex, 0, blockInfo,
                                                  CanTrcv_GetCanTrcvSpiChRWData_0(CanTrcvIndex)); /* SBSW_CANTRCV_HL_TJA1145_3 */
    break;
  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
    break;
  }

  /* #110 Determine the correct SPI-sequence from passed parameters */
  switch(blockInfo->numberOfBlocks) {
  case 4:
    sequence = CanTrcv_GetCanTrcvSeqRWDataLarge(CanTrcvIndex);
    break;
  case 3:
    sequence = CanTrcv_GetCanTrcvSeqRWDataMedium(CanTrcvIndex);
    break;
  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    retval = E_NOT_OK;
    break;
  }

  if (retval == E_OK)
  {
    /* #120 If passed parameters are OK do transmit via SPI-driver. */
    retval = CanTrcv_30_Tja1145_SpiTransmit(sequence, isSync);
  }

  return retval;

}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SpiTransmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiTransmit(Spi_SequenceType Sequence, boolean isSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;

  /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
  if (isSync == FALSE)
  {
    /* #100 Do an asynchronous SPI-transmission if required. (only asynchronous SPI-interface)*/
    retval = Spi_AsyncTransmit(Sequence);

    /* ESCAN00092619: No adaption of retval required, already either E_OK or E_NOT_OK is returned. */
  }
  else
#endif
  {
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) && defined(CANTRCV_30_TJA1145_SPI_ENABLE_SYNC_DEFAULT_IMPL) 
    /* #120 Do a simulated synchronous SPI-transmission via active polling of API: Spi_GetSequenceResult() if required. (only asynchronous SPI-interface AND default such kind of implementation is active)*/ 
    retval = Spi_AsyncTransmit(Sequence);

    if (retval == E_OK)
    {
      /* Wait while sequence is pending */
      do
      {
        CANTRCV_30_TJA1145_SPI_MAINFUNCTION();
        retval = Spi_GetSequenceResult(Sequence);
      } while (retval == SPI_SEQ_PENDING);

      if (retval == SPI_SEQ_OK)
      {
        retval = E_OK;
      }
    }

#else
    /* #130 Do a synchronous SPI-transmission. (This one can be overwritten by user.)*/
    CANTRCV_30_TJA1145_SPI_SYNC_TRANSMIT(retval, Sequence);
#endif
  }

  /* #140 Adapt the return value. Only OK or not OK must be returned! */
  if (retval != E_OK)
  {
    /* Correct return value */
    retval = E_NOT_OK;
  }

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(isSync); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif

  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RwMode
 **********************************************************************************************************************/
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
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RwMode(uint8 CanTrcvIndex, boolean isSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  CanTrcv_30_Tja1145_SpiTxBlockSeqType seqBufferInfo;


  /* ----- Implementation ----------------------------------------------- */

  /* #100 Allocate the SPI. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_MODE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  retval = E_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */

  /* #110 Set-up the SPI-out-buffers for write- and read-access of Mode-registers. */

  /* *** WRITE *** */
  /* #120 Set-up write-access to Can-control and Mode-control registers. */
  write_block(seqBufferInfo.block[0], CanTrcv_30_Tja1145_Cc, 1, &CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlWrite); /* PRQA S 0312 */ /* MD_CanTrcv_30_Tja1145_0312 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqBufferInfo.block[1], CanTrcv_30_Tja1145_Mc, 1, &CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlWrite); /* PRQA S 0312 */ /* MD_CanTrcv_30_Tja1145_0312 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  /* *** WRITE *** */

  /* *** READ *** */
  /* #130 Set-up read-access to Can-control register. */
  read_block(seqBufferInfo.block[2], CanTrcv_30_Tja1145_Cc, 1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */

  /* #140 Set-up read-access to Mode-control register. */
  read_block(seqBufferInfo.block[3], CanTrcv_30_Tja1145_Mc, 1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqBufferInfo.numberOfBlocks = 4;
  /* *** READ *** */

  /* #150 Process the set-up SPI-access. */
  retval = CanTrcv_30_Tja1145_SpiTransmitBlock(CanTrcvIndex, &seqBufferInfo, isSync); /* SBSW_CANTRCV_HL_TJA1145_3 */

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
  if (retval == E_OK)
  {
    /* #160 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
    CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
  }
  else
#else
  if (retval == E_NOT_OK)
#endif /* (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) */
  {
    /* #170 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_RwStatus
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1145_LOCAL FUNC(Std_ReturnType, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_RwStatus(uint8 CanTrcvIndex, boolean isSync, uint32 requestType)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  CanTrcv_30_Tja1145_StatusFlagsType clrFlags;

  /* ----- Implementation ----------------------------------------------- */
  retval = E_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 

  /* #100 Mark data of status flags as invalid. (only asynchronous SPI) */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsNew = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].statusFlagsRdy = FALSE; /* SBSW_CANTRCV_HL_TJA1145_1 */
#endif  

  /* #110 Allocate the SPI. */
  CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_RW_STATUS; /* SBSW_CANTRCV_HL_TJA1145_1 */

  clrFlags.Ecs = 0;
  clrFlags.Ses = 0;
  clrFlags.Tes = 0;
  clrFlags.Wes = 0;    

  /* #120 Clear the status flags depending on <requestType>. */
  switch(requestType)
  {
#if ((CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON))
      case CANTRCV_30_TJA1145_RT_RD_STATUS:
      {
        clrFlags.Tes = CanTrcv_30_Tja1145_Tes_CF;
      }
      break;
#endif /* (CANTRCV_30_TJA1145_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON) */
#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
    case CANTRCV_30_TJA1145_RT_CLR_WUF:
    {
      clrFlags.Tes = (uint8)(CanTrcv_30_Tja1145_Tes_CF|CanTrcv_30_Tja1145_Tes_CW);
      clrFlags.Wes = (uint8)(CanTrcv_30_Tja1145_Wes_WPR|CanTrcv_30_Tja1145_Wes_WPF);  
    }
    break;
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */
    case CANTRCV_30_TJA1145_RT_CLR_ALL:
    {
      clrFlags.Ecs = (uint8)(CanTrcv_30_Tja1145_Ecs_SYSE|CanTrcv_30_Tja1145_Ecs_TRXE|CanTrcv_30_Tja1145_Ecs_WPE);
      clrFlags.Ses = (uint8)(CanTrcv_30_Tja1145_Ses_SPIF|CanTrcv_30_Tja1145_Ses_OTW|CanTrcv_30_Tja1145_Ses_PO);
      clrFlags.Tes = (uint8)(CanTrcv_30_Tja1145_Tes_CW|CanTrcv_30_Tja1145_Tes_CF|CanTrcv_30_Tja1145_Tes_CBS|CanTrcv_30_Tja1145_Tes_PNFDE);
      clrFlags.Wes = (uint8)(CanTrcv_30_Tja1145_Wes_WPR|CanTrcv_30_Tja1145_Wes_WPF);          
    }
    break;
    default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    {
      /* Do nothing */
    }
    break;
  }
  
  retval = E_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
 
  /* #130 Set-up the external buffer within the SPI-driver.  */
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][0] = CanTrcv_30_Tja1145_MkAdr(CanTrcv_30_Tja1145_Ts, 1u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  retval  = Spi_SetupEB(CanTrcv_GetCanTrcvSpiChRWData_0(CanTrcvIndex),
                      &CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][0],
                      &CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][0],
                      2); /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][2] = CanTrcv_30_Tja1145_MkAdr(CanTrcv_30_Tja1145_Ecs, 0u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][3] = clrFlags.Ecs; /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][4] = clrFlags.Ses; /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  
  retval |= Spi_SetupEB(CanTrcv_GetCanTrcvSpiChRWData_1(CanTrcvIndex),
                      &CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][2],
                      &CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][2],
                      3); /* SBSW_CANTRCV_LL_TJA1145_5 */

  
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][5] = CanTrcv_30_Tja1145_MkAdr(CanTrcv_30_Tja1145_Tes, 0u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][6] = clrFlags.Tes; /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][7] = clrFlags.Wes; /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  retval |= Spi_SetupEB(CanTrcv_GetCanTrcvSpiChRWData_2(CanTrcvIndex),
                      &CanTrcv_30_Tja1145_SpiOutBuffer[CanTrcvIndex][5],
                      &CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][5],
                      3); /* SBSW_CANTRCV_LL_TJA1145_5 */

  /* #140 Process the set-up SPI-access. */
  if (retval == E_OK)
  {
    retval = CanTrcv_30_Tja1145_SpiTransmit(CanTrcv_GetCanTrcvSeqRWDataMedium(CanTrcvIndex), isSync);

#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_ON) 
    if (retval == E_OK)
    {
      /* #150 If SPI-access PASSED: Call the SPI-indication by itself. (only synchronous SPI-interface) */
      CanTrcv_30_Tja1145_SpiIndication(CanTrcvIndex);
    }
#endif
  }

  if (retval == E_NOT_OK)
  {
    /* #160 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retval;
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1145_SpiIndication
 **********************************************************************************************************************/
/*! Internal comment removed. *
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
 **********************************************************************************************************************/
#if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiIndication(uint8 CanTrcvIndex)
#else
CANTRCV_30_TJA1145_LOCAL FUNC(void, CANTRCV_30_TJA1145_CODE) CanTrcv_30_Tja1145_SpiIndication(uint8 CanTrcvIndex)
#endif
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 event = CANTRCV_30_TJA1145_TASK_EV_NONE;
  uint8 errorId = CANTRCV_30_TJA1145_E_NO_ERROR;

#if ((CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)) 
  if(CanTrcvIndex >= CANTRCV_30_TJA1145_MAX_CHANNEL) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
  {
    errorId = CANTRCV_30_TJA1145_E_INVALID_CAN_NETWORK;
  }
  else
#endif /* (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #100 Process depending on requested SPI-access. */
    switch(CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType)
    {
    case CANTRCV_30_TJA1145_REQ_RW_MODE:
      /* #200 SPI-access: Mode-registers: Copy read values. */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanControlRead  = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][9]); /* SBSW_CANTRCV_HL_TJA1145_1 */
      CanTrcv_30_Tja1145_Prob[CanTrcvIndex].ModeControlRead = (uint8)(CanTrcv_30_Tja1145_SpiInBuffer[CanTrcvIndex][13]); /* SBSW_CANTRCV_HL_TJA1145_1 */

      /* #210 Set-up the corresponding event. */
      event = CANTRCV_30_TJA1145_TASK_EV_RW_MODE;
      break;

    case CANTRCV_30_TJA1145_REQ_RW_STATUS:
      /* #300 SPI-access: Status-flags: Set-up the corresponding event. */
      event = CANTRCV_30_TJA1145_TASK_EV_RW_STATUS;
      break;

#if (CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON)
    case CANTRCV_30_TJA1145_REQ_RW_IDMASKDB:
      /* #310 SPI-access: IdMask / Db: Set-up the corresponding event. */
      event = CANTRCV_30_TJA1145_TASK_EV_RW_IDMASKDB;
      break;
#endif /* CANTRCV_30_TJA1145_HW_PN_SUPPORT == STD_ON */

    default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
      break;
    }

    if (event != CANTRCV_30_TJA1145_TASK_EV_NONE) /* COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE */
    {
      /* #400 Any event occurred: */

      if (event == CANTRCV_30_TJA1145_TASK_EV_RW_STATUS)
      {
        /* #410 Event: New status-flags received: Process them before calling the task because the task may need them. */
        CanTrcv_30_Tja1145_GetStatusFlagsIndication(CanTrcvIndex);
      }

  #if (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) 
      if (CanTrcv_30_Tja1145_Prob[CanTrcvIndex].isInit == CANTRCV_30_TJA1145_IS_INIT)
      {
         /* #420 If CanTrcv-driver is already initialized: Send the occurred event to the current active task. (only asynchronous SPI-interface) */
        (void)CanTrcv_30_Tja1145_Schedule(CanTrcvIndex, event);
      }
  #endif
    }

    /* #500 Unlock the SPI. */
    CanTrcv_30_Tja1145_Prob[CanTrcvIndex].CanTrcvSpiReqType = CANTRCV_30_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

#if ((CANTRCV_30_TJA1145_DEV_ERROR_REPORT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF)) 
  if (errorId != CANTRCV_30_TJA1145_E_NO_ERROR) /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA */
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1145_SPIINDICATION_ID, errorId);
  }
#else
  CANTRCV_30_TJA1145_DUMMY_STATEMENT(errorId); /* PRQA S 1338,2983,3112 */ /* MD_MSR_DummyStmt */
#endif /* (CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON) && (CANTRCV_30_TJA1145_SPI_ACCESS_SYNCHRONOUS == STD_OFF) */
}



#define CANTRCV_30_TJA1145_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* **************************************************************************/
/*  MISRA deviations                                                        */
/* **************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_CanTrcv_30_Tja1145_14.3:
  Reason: Result or value is always true or false depend on configuration aspect and used HW specific implementation
  Risk: Incorrect value return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.
  
MD_CanTrcv_30_Tja1145_3408:
  Reason: Some local variables are declared without static declaration to allow better debugging.
  Risk: Name conflict.
  Prevention: All external variables are prefixed with <Msn>

MD_CanTrcv_30_Tja1145_Emulated_Sleep:
  Reason: When the wakeup source WakeupByPin is used (configuration aspect) the 'if' controlling expression is always false.
  Risk: None. When using the wake source WakeupByPin, the emulated sleep must not be used. 
  Prevention: -
MD_CanTrcv_30_Tja1145_8.9:
  Reason: Definition of CanTrcv_30_Tja1145_TaskInfoTable in global section because of better over-view.
  Risk: Name conflict.
  Prevention: Check for name conflicts.
MD_CanTrcv_30_Tja1145_2003:
  Reason: No break at the end of case due to performance improvement.
  Risk: Incorrect behavior.
  Prevention: Static code inspection.

MD_CanTrcv_30_Tja1145_0312:
  Reason: It is ok to loose volatile here as the values must not be changed until the value is used. 
  Risk: Data changes before it is being used.
  Prevention: Locking mechanism and code review.

MD_CanTrcv_30_Tja1145_17.8:
  Reason: Variable is used to determine the initial state of the operation and is then modified to signal the following states.
  Risk: None because the variable is not further used if it doesn't match an expected value and is not returned to the callee.
  Prevention: -

*/


/* **************************************************************************/
/*  SILENT justifications                                                   */
/* **************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CANTRCV_HL_TJA1145_1
\DESCRIPTION The variable "CanTrcv_30_Tja1145_Prob[]" must be accessed with index which is < CANTRCV_30_TJA1145_MAX_CHANNEL. 
\COUNTERMEASURE \N In case of an internal access initiated by the CanTrcv-driver itself this is ensured by the driver itself. The internal
access index is generated by a FOR-loop-count-index which runs from "0" until "CANTRCV_30_TJA1145_MAX_CHANNEL-1".
In case of an external access initiated by an upper layer e.g. CanIf this is ensured if CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON.


\ID SBSW_CANTRCV_HL_TJA1145_2
\DESCRIPTION Write access to a pointer passed by an upper layer e.g. CanIf. Source data is of the same type as the destination data.
\COUNTERMEASURE \N The caller ensures that a valid pointer is passed. By the way compiler ensures that no memory violation occurs.


\ID SBSW_CANTRCV_HL_TJA1145_3
\DESCRIPTION Function call with passed pointer to a stack variable as parameter.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid pointer is passed. By the way the compiler ensures that no memory violation occurs.


\ID SBSW_CANTRCV_HL_TJA1145_4
\DESCRIPTION Function pointer call.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid function pointer is used. Used function pointer is retrieved from a constant table which is NOT generated. 
                   By the way the compiler ensures that no memory violation occurs.



\ID SBSW_CANTRCV_LL_TJA1145_1
\DESCRIPTION The variables "CanTrcv_30_Tja1145_TaskActive[][]" and "CanTrcv_30_Tja1145_ScheduleFifo[][]" must be accessed with indexes:
1. dimension < CANTRCV_30_TJA1145_MAX_CHANNEL and
2. dimension < CANTRCV_30_TJA1145_NUM_TASKS. 
\COUNTERMEASURE \N 
Valid access to 1. dimension: In case of an internal access initiated by the CanTrcv-driver itself this is ensured by the driver itself. The internal
                              access index is generated by a FOR-loop-count-index which runs from "0" until "CANTRCV_30_TJA1145_MAX_CHANNEL-1".
                              In case of an external access initiated by an upper layer e.g. CanIf this is ensured if CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON.
Valid access to 2. dimension: Accesses are initiated by the CanTrcv-driver itself and are ensured by the driver itself.


\ID SBSW_CANTRCV_LL_TJA1145_2
\DESCRIPTION Write access to a variable of type "CanTrcv_30_Tja1145_SpiTxBlockSeqType". 
The size of member "block" is "4" and is static. Hence in case of access to this array-member the access-index must be < 4. 
The value of "numberOfBlocks" must be 1, 2, 3 or 4.
\COUNTERMEASURE \N Any access to such kind of variable is initiated by the CanTrcv-driver itself and is ensured by the driver itself.


\ID SBSW_CANTRCV_LL_TJA1145_3
\DESCRIPTION The variable "CanTrcv_30_Tja1145_FifoInfo[]" must be accessed with index which is < CANTRCV_30_TJA1145_MAX_CHANNEL. 
\COUNTERMEASURE \N In case of such access is initiated this is ensured if CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON.


\ID SBSW_CANTRCV_LL_TJA1145_4
\DESCRIPTION Pointer write access to "currentTask" within the API CanTrcv_30_Tja1145_Schedule(). 
\COUNTERMEASURE \N [SBSW_CANTRCV_LL_TJA1145_1]


\ID SBSW_CANTRCV_LL_TJA1145_5
\DESCRIPTION The variables "CanTrcv_30_Tja1145_SpiInBuffer[][]" and "CanTrcv_30_Tja1145_SpiOutBuffer[][]" must be accessed with indexes:
1. dimension < CANTRCV_30_TJA1145_MAX_CHANNEL and
2. dimension < CANTRCV_30_TJA1145_SPI_BUFFER_SIZE. 
\COUNTERMEASURE \N 
Valid access to 1. dimension: In case of an internal access initiated by the CanTrcv-driver itself this is ensured by the driver itself. The internal
                              access index is generated by a FOR-loop-count-index which runs from "0" until "CANTRCV_30_TJA1145_MAX_CHANNEL-1".
                              In case of an external access initiated by an upper layer e.g. CanIf this is ensured if CANTRCV_30_TJA1145_DEV_ERROR_DETECT == STD_ON.
Valid access to 2. dimension: Accesses are initiated by the CanTrcv-driver itself and are ensured by the driver itself. (see also [SBSW_CANTRCV_LL_TJA1145_2])


SBSW_JUSTIFICATION_END */


/* **************************************************************************/
/*  COVERAGE justifications                                                 */
/* **************************************************************************/
/* START_COVERAGE_JUSTIFICATION


\ID COV_CANTRCV_HL_TJA1145_VARCOV_AVOID_COREVER_REDEF
  \ACCEPT TX
  \REASON Avoids the re-definition of CORE-version in case of multiple CanTrcv-driver are used. Hence decision "F" can NOT be fulfilled. Correct functionality is ensured by code inspection.


\ID COV_CANTRCV_HL_TJA1145_CODECOV_NOT_EACH_CONFIG
  \ACCEPT XF
  \ACCEPT XF xf xx
  \ACCEPT XF tf xf
  \REASON The stimulation is not possible in each configuration. It will be ensured by inspection that all decisions are covered
          in at least one configuration. In addition correct functionality is verified by code inspection.


\ID COV_CANTRCV_HL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE
  \ACCEPT TX
  \REASON The code is required due to HL-LL-concept and in order to prevent malfunctions in case of programming of LL. 
          Hence the stimulation is not possible in case of correct programming of LL. The correct functionality is verified by code inspection.


\ID COV_CANTRCV_HL_TJA1145_CODECOV_IS_WU_BY_BUS_USED
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Condition / decision not covered by automatic tests. Affected code has low complexity because no else-path is available. 
          The code is verified by code inspection.


\ID COV_CANTRCV_HL_TJA1145_CODECOV_OP_MODE_REQ_NONE
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tx
  \REASON Condition not covered by automatic tests but both decisions are covered. Affected code has low complexity. 
          The code is verified by code inspection.


\ID COV_CANTRCV_HL_TJA1145_CODECOV_SYNC_INT_BY_SYNC
  \ACCEPT TF tf tx
  \REASON The condition is tested manually by TCASE: TCASE-481987. In addition correctness of code is ensured by code inspection.



\ID COV_CANTRCV_LL_TJA1145_VARCOV_INVALID_MEASURE
  \ACCEPT TF tx tf
  \REASON Affected condition-decision is fulfilled in fact but is NOT measured properly by variant-coverage-report-generator.


\ID COV_CANTRCV_HL_LL_TJA1145_VARCOV_HW_FEAT_NOT_SUPPORTED
  \ACCEPT TF
  \ACCEPT TF tf tf
  \ACCEPT TF tf tf tf
  \ACCEPT XX
  \REASON Generally all condition-decision variants are covered.


\ID COV_CANTRCV_HL_LL_TJA1145_VARCOV_SW_FEAT_NOT_SUPPORTED
  \ACCEPT TF
  \ACCEPT TX tf tf
  \REASON Generally all condition-decision variants are covered.
          In case of "TX tf tf" Affected condition-decision is fulfilled in fact but is NOT measured properly by variant-coverage-report-generator.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_INVALID_GENDATA
  \ACCEPT XF xf xf tx xx
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all condition-decision variants can be stimulated, because therefore the generated data must be manipulated which is NOT applicable.
          Correct functionality is ensured by code review.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_HW_SPECIFIC
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf xf
  \REASON Depending on used HW and due to HL-LL-concept NOT all condition-decision variants can be stimulated.
          Correct functionality is ensured by code review.
          The features: "TimeoutFlag" and "SilenceFlag" are NOT supported by Tja1145.
          In case of Tja1145 the bit "CPNS" (*IsCfg()) is linked with bit "CPNERR" (*IsSys()).


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT
  \ACCEPT X
  \ACCEPT TF tx tf
  \REASON X: Default is used in order to ensure defined behaviour.
          TF tx tf: Due to previous default handling not all conditions can be stimulated.
          At ALL: Correct functionality is ensured by code review.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_SPI_BUSY
  \ACCEPT TX
  \ACCEPT XF
  \REASON TX/XF: This one can only be stimulated in case of an interruption while the SPI-interface is already busy. 
                 This scenario can NOT be stimulated reliable and with acceptable effort. The code is verified by code inspection.


\ID COV_CANTRCV_LL_TJA1145_CODECOV_HW_FAILURE
  \ACCEPT TX
  \ACCEPT TX tx xx
  \ACCEPT TX tf tx
  \REASON [COV_MSR_HW_FAILURE]


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_POWER_ON
  \ACCEPT TF xf xx tf xf
  \ACCEPT TX
  \ACCEPT XF xf xx
  \ACCEPT X
  \REASON The detection of wakeup reason POWER_ON is verified by manual execution of TCASE: TCASE-388159. In addition the code is verified by code inspection.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_WU_BY_PIN
  \ACCEPT XF
  \ACCEPT TF tf xf tf
  \ACCEPT TF xf tf
  \ACCEPT TF tf tf xf
  \ACCEPT TF tf tf xf tf tf
  \ACCEPT TF tf tf xf tf xf
  \REASON The detection of wakeup reason BY_PIN is verified by manual execution of TCASE-388160. In addition the code is verified by code inspection.
          TF tf tf xf tf xf:  For the Ata6570 the BY_BUS flag is always set when creating a SysErr during testing, therefore this scenario is also acceptable.


\ID COV_CANTRCV_LL_TJA1145_CODECOV_DEFENSIVE_CODING_STYLE
  \ACCEPT TX
  \ACCEPT TF tx tf
  \ACCEPT TX tx tx tx
  \REASON The code is required due to HL-LL-concept / synchronous/asynchronous SPI and in order to prevent malfunctions in case of programming of HL and LL and
          usage of synchronous / asynchronous SPI. 
          Hence the stimulation is not possible in case of correct programming of HL and LL. The correct functionality is verified by code review.
          TX tx tx tx: Safety measure in case of asynchronous SPI is used. The correct functionality is verified by code review.


\ID COV_CANTRCV_LL_TJA1145_CODECOV_SYNC_INT_BY_ASYNC
  \ACCEPT TF tf tx
  \REASON The condition is tested manually by TCASE: TCASE-469650. In addition correctness of code is ensured by code inspection.


\ID COV_CANTRCV_LL_TJA1145_CODECOV_ASYNC_NOT_EACH_CFG
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all conditions / decisions can be stimulated in case of only one task is available. Correctness of code is ensured by configurations where affected conditions / decisions 
          are stimulated. In addition correctness of code is ensured by code inspection.


\ID COV_CANTRCV_LL_TJA1145_CODECOV_WU_BY_BUS_NOT_EACH_CFG
  \ACCEPT TX
  \ACCEPT XF
  \REASON It is not possible to have WakeupByBus enabled and disabled in each configuration. 
          It will be ensured by inspection that both decisions are covered in at least one configuration.
          In addition correct functionality is verified by code review.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP
  \ACCEPT XX
  \ACCEPT TX
  \ACCEPT XF
  \REASON If all wakeup sources from a CAN transceiver channel are disabled, it is not possible to enter sleep mode in the corresponding hardware.
          It will be ensured by inspection that sleep mode for the hardware is covered in at least one configuration. 
          In addition correct functionality is verified by code review.


\ID COV_CANTRCV_HL_LL_TJA1145_CODECOV_ALL_WU_DIS
  \ACCEPT XF
  \REASON Not all conditions / decisions can be stimulated in case of all wakeup sources from a CAN transceiver channel are disabled.
          It will be ensured by inspection that both decisions are covered in at least one configuration. 
          In addition correct functionality is verified by code review. 



END_COVERAGE_JUSTIFICATION */ 

/* ********************************************************************************************************************
 *  END OF FILE
 * *******************************************************************************************************************/
