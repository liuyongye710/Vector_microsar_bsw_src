/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file     Can.c / Can_Irq.c / Can_Local.h
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/
/*****************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Ces          Senol Cendere             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
| Was          Andreas Weinrauch         Vector Informatik GmbH
| Rna          Ruediger Naas             Vector Informatik GmbH
| Tkr          Torsten Kercher           Vector Informatik GmbH
| Hzo          Han Zhao                  Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver   Author  Description
| ---------  ---  ------  ----------------------------------------------------
| Refer to the module's header file.
|************************************************************************** */

#if !defined(CAN_LOCAL_H)
#define  CAN_LOCAL_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
#include "Can.h"         /* include also all needed types */
/* \trace SPEC-1583 */
#include "SchM_Can.h"

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0600u) /* \trace SPEC-1699, SPEC-3837 */
# error "Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Header file are inconsistent!"
#endif
#if( DRVCAN_TRICOREMULTICANASR_VERSION != 0x0316u)
# error "Source and Header file are inconsistent!"
#endif

#if( DRVCAN_TRICOREMULTICANASR_RELEASE_VERSION != 0x00u)
# error "Source and Header file are inconsistent!"
#endif

#  if( CAN_GEN_TricoreMulticanAsr_VERSION != 0x0101u)
#   error "Source and Generated file are inconsistent!"
#  endif

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#define C_ENABLE_COPY_TX_DATA

#if defined(C_ENABLE_MIXED_ID) || defined(C_ENABLE_EXTENDED_ID)
# define CAN_ID_IDE_MASK            0x80000000UL
# define CAN_ID_FD_MASK             0x40000000UL /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x1FFFFFFFUL
# define CAN_ID_MASK_STD            0x000007FFUL
# define CAN_ID_UNUSED_MASK         0x20000000UL
#else
# define CAN_ID_IDE_MASK            0x0000U
# define CAN_ID_FD_MASK             0x4000U /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x07FFU
# define CAN_ID_MASK_STD            0x07FFU
# define CAN_ID_UNUSED_MASK         0x3800U
#endif
#define kCanAllChannels             ((CanChannelHandle)0xFFU)

#if !defined(C_DRV_INTERNAL) /* COV_CAN_INTERNAL */
# error "Can_Local.h should only be included by Can.c"
#endif
#if defined(kCanNumberOfChannels) /* COV_CAN_COMPATIBILITY */
# undef kCanNumberOfChannels /* may happen for MultiDirverInstance */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfChannels Can_GetControllerMax()
/* if kCanNumberOfChannels used to declare a table/dimension this table has to be generated to be also Link-Time-capable */
/*  -> see ESCAN00028069 controller-amount has to be Link-Time-capable */
#if defined(kCanNumberOfHwChannels) /* COV_CAN_COMPATIBILITY */
# undef kCanNumberOfHwChannels /* may happen for MultiDirverInstance */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
/* compatibility to common-can drivers */
/* real amount of controllers in this system (LT and PB) */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COM_STACK_LIB */ /* COV_CAN_MICROSAR_VERSION */
#  define kCanNumberOfHwChannels kCanNumberOfChannels
#else
# if ( CAN_COMMON_CAN == STD_ON )
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanHwChannelMax)
# else
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanControllerMax)
# endif
#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((CanChannelHandle)0)
# define canHwChannel                           ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((CanChannelHandle)0)
#else
# define channel                                Controller
#  define canHwChannel                          Controller
#  define CAN_HL_HW_CHANNEL_STARTINDEX(ch)      (ch)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(ch)       (ch)
#endif

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# if !defined(CAN_EMULATE_SLEEP) /* COV_CAN_COMPATIBILITY */
#  define CAN_EMULATE_SLEEP STD_ON /* always on for AutoSar4 */
# endif
# if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
#  define CAN_TRANSITION_CHECK STD_ON /* default may be deactivated by user configuration */
# endif
#else
# if !defined(CAN_EMULATE_SLEEP) /* COV_CAN_COMPATIBILITY */
#  define CAN_EMULATE_SLEEP STD_OFF
# endif
# if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
#  define CAN_TRANSITION_CHECK STD_OFF
# endif
#endif
#if !defined(CAN_REINIT_START) /* COV_CAN_COMPATIBILITY */
# define CAN_REINIT_START STD_OFF
#endif

#if !defined(CAN_OS_TICK2MS) /* COV_CAN_COMPATIBILITY */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
#  error "CAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
# endif
# define CAN_OS_TICK2MS(tick) (tick) /* used direct by 401 implementation */
#endif
#if !defined(CAN_OS_COUNTER_ID) /* COV_CAN_COMPATIBILITY */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
#  error "CAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
# endif
# define CAN_OS_COUNTER_ID CanTimeoutDurationCounterId /* used direct by 401 implementation */
#endif

#if !defined(CAN_RX_BASICCAN_TYPE) /* compatibility Cfg5 to GENy */ /* COV_CAN_COMPATIBILITY */
# define CAN_RX_BASICCAN_TYPE    RxBasicCANType
# define CAN_RX_FULLCAN_TYPE     RxFullCANType
# define CAN_TX_BASICCAN_TYPE    TxBasicCANType
# define CAN_TX_FULLCAN_TYPE     TxFullCANType
# define CAN_UNUSED_CAN_TYPE     UnusedCANType
#endif
#if !defined(CAN_TX_BASICCAN_MUX_TYPE) /* COV_CAN_COMPATIBILITY */
# define CAN_TX_BASICCAN_MUX_TYPE   TxBasicCANType /* not supported in GENy for now */
#endif

#if !defined(CAN_ID_MASK_IN_GENERIC_CALLOUT) /* COV_CAN_COMPATIBILITY */
# define CAN_ID_MASK_IN_GENERIC_CALLOUT (CAN_ID_IDE_MASK | CAN_ID_FD_MASK | CAN_ID_MASK)
/* May be changed to mask out FD-bit: (CAN_ID_IDE_MASK | CAN_ID_MASK) */
#endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable Can_ActiveSendState */
#define CAN_FREE_OBJ                (uint8)0xFF     /* mark objects as free */
#define kCanBufferFree              CAN_FREE_OBJ    /* compatibility for cancel in HW task */
#define CAN_CANCEL_OBJ              (uint8)0xFE     /* mark object as currently cancelling */
#define kCanBufferCancel            CAN_CANCEL_OBJ  /* compatibility for LL cancel interrupt / task */
#define CAN_CANCEL_OBJ_SW           (uint8)0xFD
#define CAN_SEND_OBJ                (uint8)0x01     /* occupied send object */

#if defined(C_ENABLE_CAN_RAM_CHECK)
/* for variable Can_MailboxState */
# define CAN_ENABLE_OBJ             (uint8)0x00     /* enabled mailbox */
# define CAN_DISABLED_OBJ           (uint8)0x01     /* disabled mailbox */
#endif

/* general return values */
#define kCanFailed                  CAN_NOT_OK
#define kCanOk                      CAN_OK
#define kCanNotSupported            CAN_NOT_SUPPORTED
#define kCanRequested               CAN_REQUESTED

#define kCanTrue                    0x01
#define kCanFalse                   0x00

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COM_STACK_LIB */ /* COV_CAN_MICROSAR_VERSION */
# define Can_GetControllerMax()                         Can_GetSizeOfControllerData()

# define Can_GetCanControllerDefaultBaudrate(Index)     Can_GetCanControllerDefaultBaudrateOfControllerConfig(Index)
# define Can_GetCanControllerDefaultBaudrateIdx(Index)  Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(Index)
# if !defined(Can_GetMailboxRxBasicLengthOfControllerConfig) /* If no Object is available ComStackLib do not generate start-stop index */
#  define Can_GetMailboxRxBasicLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetRxBasicHandleMax(Index)                 Can_GetMailboxRxBasicLengthOfControllerConfig(Index)
# define Can_GetRxBasicHandleStart(Index)               (Can_HwHandleType)Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index)
# define Can_GetRxBasicHandleStop(Index)                (Can_HwHandleType)Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index)
# define Can_GetRxBasicHwStart(Index)                   Can_GetRxBasicHwStartOfControllerConfig(Index)
# define Can_GetRxBasicHwStop(Index)                    Can_GetRxBasicHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxRxFullLengthOfControllerConfig)
#  define Can_GetMailboxRxFullLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxRxFullStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxRxFullEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetRxFullHandleMax(Index)                  Can_GetMailboxRxFullLengthOfControllerConfig(Index)
# define Can_GetRxFullHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxRxFullStartIdxOfControllerConfig(Index)
# define Can_GetRxFullHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxRxFullEndIdxOfControllerConfig(Index)
# define Can_GetRxFullHwStart(Index)                    Can_GetRxFullHwStartOfControllerConfig(Index)
# define Can_GetRxFullHwStop(Index)                     Can_GetRxFullHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxTxBasicLengthOfControllerConfig) /* COV_CAN_GENDATA_FAILURE */
#  define Can_GetMailboxTxBasicLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetTxBasicHandleMax(Index)                 Can_GetMailboxTxBasicLengthOfControllerConfig(Index)
# define Can_GetTxBasicHandleStart(Index)               (Can_HwHandleType)Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index)
# define Can_GetTxBasicHandleStop(Index)                (Can_HwHandleType)Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index)
# define Can_GetTxBasicHwStart(Index)                   Can_GetTxBasicHwStartOfControllerConfig(Index)
# define Can_GetTxBasicHwStop(Index)                    Can_GetTxBasicHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxTxFullLengthOfControllerConfig)
#  define Can_GetMailboxTxFullLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxTxFullStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxTxFullEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetTxFullHandleMax(Index)                  Can_GetMailboxTxFullLengthOfControllerConfig(Index)
# define Can_GetTxFullHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxTxFullStartIdxOfControllerConfig(Index)
# define Can_GetTxFullHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxTxFullEndIdxOfControllerConfig(Index)
# define Can_GetTxFullHwStart(Index)                    Can_GetTxFullHwStartOfControllerConfig(Index)
# define Can_GetTxFullHwStop(Index)                     Can_GetTxFullHwStopOfControllerConfig(Index)
# if !defined(Can_GetMailboxUnusedLengthOfControllerConfig)  /* COV_CAN_GENDATA_FAILURE */
#  define Can_GetMailboxUnusedLengthOfControllerConfig(Index) 0
#  define Can_GetMailboxUnusedStartIdxOfControllerConfig(Index) 0
#  define Can_GetMailboxUnusedEndIdxOfControllerConfig(Index) 0
# endif
# define Can_GetUnusedHandleMax(Index)                  Can_GetMailboxUnusedLengthOfControllerConfig(Index)
# define Can_GetUnusedHandleStart(Index)                (Can_HwHandleType)Can_GetMailboxUnusedStartIdxOfControllerConfig(Index)
# define Can_GetUnusedHandleStop(Index)                 (Can_HwHandleType)Can_GetMailboxUnusedEndIdxOfControllerConfig(Index)
# define Can_GetUnusedHwStart(Index)                    Can_GetUnusedHwStartOfControllerConfig(Index)
# define Can_GetUnusedHwStop(Index)                     Can_GetUnusedHwStopOfControllerConfig(Index)

# define Can_GetDLC_FIFO(Index)                         Can_GetDLC_FIFOOfMailbox(Index)
# define Can_GetHwHandle(Index)                         Can_GetHwHandleOfMailbox(Index)
# define Can_GetIDValue(Index)                          Can_GetIDValueOfMailbox(Index)
# define Can_GetMailboxType(Index)                      Can_GetMailboxTypeOfMailbox(Index)
# define Can_GetMailboxDataLen(Index)                   Can_GetMaxDataLenOfMailbox(Index)
# define Can_GetMailboxFdPadding(Index)                 Can_GetFdPaddingOfMailbox(Index)
# define Can_GetMailboxController(Index)                (CanChannelHandle)Can_GetControllerConfigIdxOfMailbox(Index)

#  define Can_GetCanHwObjIndivPolling(ch,Index)          Can_GetHwObjIndivPolling((Index))

# define Can_GetCanToCanIfChannelMapping(Index)          Can_GetCanIfChannelId((Index))

/* VAR */
# define Can_GetLastInitObject(Index)                   Can_GetLastInitObjectOfControllerData(Index)
# define Can_SetLastInitObject(Index,Value)             Can_SetLastInitObjectOfControllerData(Index,Value)
# define Can_GetCanInterruptOldStatus(Index)            Can_GetCanInterruptOldStatusOfControllerData(Index)
# define Can_SetCanInterruptOldStatus(Index,Value)      Can_SetCanInterruptOldStatusOfControllerData(Index,Value)
# define Can_GetCanInterruptCounter(Index)              Can_GetCanInterruptCounterOfControllerData(Index)
# define Can_SetCanInterruptCounter(Index,Value)        Can_SetCanInterruptCounterOfControllerData(Index,Value)
# define Can_IsIsWakeup(Index)                          Can_IsIsWakeupOfControllerData(Index)
# define Can_SetIsWakeup(Index,Value)                   Can_SetIsWakeupOfControllerData(Index,Value)
# define Can_IsIsBusOff(Index)                          Can_IsIsBusOffOfControllerData(Index)
# define Can_SetIsBusOff(Index,Value)                   Can_SetIsBusOffOfControllerData(Index,Value)
# define Can_GetStatusReq(Index)                        Can_GetStatusReqOfControllerData(Index)
# define Can_SetStatusReq(Index,Value)                  Can_SetStatusReqOfControllerData(Index,Value)
# define Can_GetLogStatus(Index)                        Can_GetLogStatusOfControllerData(Index)
# define Can_SetLogStatus(Index,Value)                  Can_SetLogStatusOfControllerData(Index,Value)
# define Can_GetCanLoopTimeout(ch, Index)               (Can_GetLoopTimeoutOfControllerData(ch))[(Index)]
# define Can_IsIsHardwareCanceled(Index)                Can_IsIsHardwareCanceledOfControllerData(Index)
# define Can_SetIsHardwareCanceled(Index,Value)         Can_SetIsHardwareCanceledOfControllerData(Index,Value)
# define Can_GetMirrorModeState(Index)                  Can_GetMirrorModeStateOfControllerData(Index)
# define Can_SetMirrorModeState(Index,Value)            Can_SetMirrorModeStateOfControllerData(Index,Value)
# define Can_GetSilentModeState(Index)                  Can_GetSilentModeStateOfControllerData(Index)
# define Can_SetSilentModeState(Index,Value)            Can_SetSilentModeStateOfControllerData(Index,Value)

# define Can_GetCanTxBasicDataBuffer(ch,muxTx)          (Can_GetTxBasicDataBuffer(ch))[(muxTx)]

# define Can_GetActiveSendPdu(Index)                    Can_GetPduOfActiveSendObject(Index)
# define Can_SetActiveSendPdu(Index,Value)              Can_SetPduOfActiveSendObject(Index,Value)
# define Can_GetActiveSendState(Index)                  Can_GetStateOfActiveSendObject(Index)
# define Can_SetActiveSendState(Index,Value)            Can_SetStateOfActiveSendObject(Index,Value)
# define Can_GetActiveSendPduInfo(Index)                Can_GetPduInfoOfActiveSendObject(Index)
# define Can_GetActiveSendId(Index)                     (Can_GetPduInfoOfActiveSendObject(Index)).id
# define Can_SetActiveSendId(Index,Value)               (Can_GetPduInfoOfActiveSendObject(Index)).id = (Value)
# define Can_GetActiveSendLength(Index)                 (Can_GetPduInfoOfActiveSendObject(Index)).length
# define Can_SetActiveSendLength(Index,Value)           (Can_GetPduInfoOfActiveSendObject(Index)).length = (Value)
# define Can_GetActiveSendSdu(Index)                    (Can_GetPduInfoOfActiveSendObject(Index)).sdu
# define Can_SetActiveSendSdu(Index,Value)              (Can_GetPduInfoOfActiveSendObject(Index)).sdu = (Value)
# define Can_GetActiveSendSwPduHandle(Index)            (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle
# define Can_SetActiveSendSwPduHandle(Index,Value)      (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle = (Value)

#else /* without ComStackLib */

# if defined(CAN_ENABLE_SELECTABLE_PB)
/* \trace SPEC-1727 */
/* Pointer parameter of initialization function used (selectable Post-Build) */
#  define CAN_GLOBAL_CONFIG(x)                          Can_ConfigDataPtr->x      /* PRQA S 3410 */ /* MD_Can_3410 */
#  define CAN_CONTROLLER_CONFIG_INIT                    (Can_ConfigDataPtr->CanControllerConfig_TabPtr)
#  define CAN_CONTROLLER_CONFIG(hwch)                   (Can_ConfigDataPtr->CanControllerConfig_TabPtr[(hwch)])
#  define CAN_MAILBOX                                   (Can_ConfigDataPtr->CanMailbox_TabPtr)
#  define CAN_INIT_OBJ_START_IDX                        (Can_ConfigDataPtr->CanInitObjectStartIndex_TabPtr)
#  define CAN_INIT_OBJ_BAUDRATE                         (Can_ConfigDataPtr->CanInitObjectBaudrate_TabPtr)
#  define CAN_INIT_OBJ_FD_BRS_CONFIG                    (Can_ConfigDataPtr->CanInitObjectFdConfig_TabPtr)
#  define CanHwObjIndivPolling                          (Can_ConfigDataPtr->CanHwObjIndivPolling_TabPtr) /* PRQA S 3436 */ /* MD_Can_3436 */
#  define CAN_PARTIAL_NET                               (Can_ConfigDataPtr->CanPartialNetwork_TabPtr)
/* hardware specific starts here */
# define CanInitBT                canConfigPtr->CanInitBTPtr     /* PRQA S 3436 */ /* MD_Can_3436 */
# define CanInitMaskH             canConfigPtr->CanInitMaskHPtr  /* PRQA S 3436 */ /* MD_Can_3436 */
# define CanInitMaskL             canConfigPtr->CanInitMaskLPtr  /* PRQA S 3436 */ /* MD_Can_3436 */
# define CanInitCodeH             canConfigPtr->CanInitCodeHPtr  /* PRQA S 3436 */ /* MD_Can_3436 */
/* *********************************************************************** */
/* Access macros to generated Data                                         */
/* Abstract all generated Data like done in ComStackLib(Cfg5) for GenTools */
/* without ComStackLib support (GENy)                                      */
/* e.g.                                                                    */
/*  if defined(CAN_GEN_COM_STACK_LIB)                                      */
/*  else                                                                   */
/*   define Can_GetFilterStartIdx(Index)      CanFilterStartIdx[(Index)]   */
/*   define Can_GetCBTR0OfInitObject(Index)   CanInitObject[(Index)].CBTR0 */
/*   define Can_GetCBTR1OfInitObject(Index)   CanInitObject[(Index)].CBTR1 */
/*  endif                                                                  */
/* Use  or  for ASR here (only for COM_STACK_LIB defines) */
/* *********************************************************************** */
# else
/* \trace SPEC-1728 */
/* Pointer parameter of initialization function not used (no selectable Post-Build or Link-Time configuration) */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
#   define CAN_GLOBAL_CONFIG(x)                         Can_ConfigDataPtr->x      /* PRQA S 3410 */ /* MD_Can_3410 */
#  else
#   define CAN_GLOBAL_CONFIG(x)                         CanConfig.x               /* PRQA S 3410 */ /* MD_Can_3410 */
#  endif
#  define CAN_CONTROLLER_CONFIG_INIT                    CanControllerConfig
#  define CAN_CONTROLLER_CONFIG(hwch)                   CanControllerConfig[(hwch)]
#  define CAN_MAILBOX                                   CanMailbox
#  define CAN_INIT_OBJ_START_IDX                        CanInitObjectStartIndex
#  define CAN_INIT_OBJ_BAUDRATE                         CanInitObjectBaudrate
#  define CAN_INIT_OBJ_FD_BRS_CONFIG                    CanInitObjectFdConfig
#  define CAN_PARTIAL_NET                               CanPartialNetwork
# endif

/* CONST PB */
# define Can_GetBaseDll_GeneratorVersion()              CAN_GLOBAL_CONFIG(Can_BaseDll_GeneratorVersion)
# define Can_GetPlatformDll_GeneratorVersion()          CAN_GLOBAL_CONFIG(Can_PlatformDll_GeneratorVersion)
# define Can_GetPrecompileCRC()                         CAN_GLOBAL_CONFIG(Can_ePrecompileCRC)
# define Can_GetLinktimeCRC()                           CAN_GLOBAL_CONFIG(Can_eLinktimeCRC)
# define Can_GetIdentitySelected()                      CAN_GLOBAL_CONFIG(IdentitySelected)
# define Can_GetControllerMax()                         CAN_GLOBAL_CONFIG(CanControllerMax)
# define Can_GetHwChannelMax()                          CAN_GLOBAL_CONFIG(CanHwChannelMax)
# define Can_GetMaxRxDataLen()                          CAN_GLOBAL_CONFIG(CanMaxRxDataLen)
# define Can_GetMaxTxDataLen()                          CAN_GLOBAL_CONFIG(CanMaxTxDataLen)
# define Can_GetFinalMagicNumber()                      CAN_GLOBAL_CONFIG(FinalMagicNumber)

# define Can_GetCanControllerDefaultBaudrate(Index)     CAN_CONTROLLER_CONFIG(Index).CanControllerDefaultBaudrate
# define Can_GetCanControllerDefaultBaudrateIdx(Index)  CAN_CONTROLLER_CONFIG(Index).CanControllerDefaultBaudrateIdx
# define Can_GetRxBasicHandleMax(Index)                 CAN_CONTROLLER_CONFIG(Index).RxBasicHandleMax
# define Can_GetRxBasicHandleStart(Index)               CAN_CONTROLLER_CONFIG(Index).RxBasicHandleStart
# define Can_GetRxBasicHandleStop(Index)                CAN_CONTROLLER_CONFIG(Index).RxBasicHandleStop
# define Can_GetRxBasicHwStart(Index)                   CAN_CONTROLLER_CONFIG(Index).RxBasicHwStart
# define Can_GetRxBasicHwStop(Index)                    CAN_CONTROLLER_CONFIG(Index).RxBasicHwStop
# define Can_GetRxFullHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).RxFullHandleMax
# define Can_GetRxFullHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).RxFullHandleStart
# define Can_GetRxFullHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).RxFullHandleStop
# define Can_GetRxFullHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).RxFullHwStart
# define Can_GetRxFullHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).RxFullHwStop
# define Can_GetTxBasicHandleMax(Index)                 CAN_CONTROLLER_CONFIG(Index).TxBasicHandleMax
# define Can_GetTxBasicHandleStart(Index)               CAN_CONTROLLER_CONFIG(Index).TxBasicHandleStart
# define Can_GetTxBasicHandleStop(Index)                CAN_CONTROLLER_CONFIG(Index).TxBasicHandleStop
# define Can_GetTxBasicHwStart(Index)                   CAN_CONTROLLER_CONFIG(Index).TxBasicHwStart
# define Can_GetTxBasicHwStop(Index)                    CAN_CONTROLLER_CONFIG(Index).TxBasicHwStop
# define Can_GetTxFullHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).TxFullHandleMax
# define Can_GetTxFullHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).TxFullHandleStart
# define Can_GetTxFullHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).TxFullHandleStop
# define Can_GetTxFullHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).TxFullHwStart
# define Can_GetTxFullHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).TxFullHwStop
# define Can_GetUnusedHandleMax(Index)                  CAN_CONTROLLER_CONFIG(Index).UnusedHandleMax
# define Can_GetUnusedHandleStart(Index)                CAN_CONTROLLER_CONFIG(Index).UnusedHandleStart
# define Can_GetUnusedHandleStop(Index)                 CAN_CONTROLLER_CONFIG(Index).UnusedHandleStop
# define Can_GetUnusedHwStart(Index)                    CAN_CONTROLLER_CONFIG(Index).UnusedHwStart
# define Can_GetUnusedHwStop(Index)                     CAN_CONTROLLER_CONFIG(Index).UnusedHwStop

# define Can_GetDLC_FIFO(Index)                         CAN_MAILBOX[(Index)].DLC_FIFO
# define Can_GetHwHandle(Index)                         CAN_MAILBOX[(Index)].HwHandle
# define Can_GetIDValue(Index)                          CAN_MAILBOX[(Index)].IDValue
# define Can_GetMailboxType(Index)                      CAN_MAILBOX[(Index)].MailboxType
# define Can_GetMailboxDataLen(Index)                   8 /* just for DET check against maximum value - FD-mode2 not supported for GENy */
# define Can_GetMailboxController(Index)                CAN_MAILBOX[(Index)].MsgController

# define Can_GetInitObjectStartIndex(Index)             CAN_INIT_OBJ_START_IDX[(Index)]
# define Can_GetInitObjectBaudrate(Index)               CAN_INIT_OBJ_BAUDRATE[(Index)]
# define Can_GetInitObjectFdBrsConfig(Index)            CAN_INIT_OBJ_FD_BRS_CONFIG[(Index)]

# define Can_GetPartialNetwork(Index)                   CAN_PARTIAL_NET[(Index)] /* only CAN_MSR3 */

# define Can_GetCanHwObjIndivPolling(ch,Index)          CanHwObjIndivPolling[ch][(Index)]

/* CONST */
# define Can_GetWakeupSourceRef(Index)                  CanWakeupSourceRef[(Index)]
# define Can_GetControllerBaudrateConfig(Index)         Can_ControllerBaudrateConfig[(Index)] /* only CAN_MSR40 */
# define Can_GetHwChannelStartIndex(Index)              CanHwChannelStartIndex[(Index)]
# define Can_GetHwChannelToChannel(Index)               CanHwChannelToChannel[(Index)]
# define Can_GetChannelIdentityAssignment(Index)        CanChannelIdentityAssignment[(Index)]
# define Can_GetCanToCanIfChannelMapping(Index)         (Index)
# define Can_GetTxOffsetHwToLog(Index)                  canTxOffsetHwToLog[(Index)]

/* VAR */
# define Can_GetSizeOfRxQueueBuffer()                   kCanRxQueueSize

# define Can_GetActiveSendPdu(Index)                    CanActiveSendPdu[(Index)]
# define Can_SetActiveSendPdu(Index,Value)              CanActiveSendPdu[(Index)] = (Value)
# define Can_GetActiveSendState(Index)                  CanActiveSendState[(Index)]
# define Can_SetActiveSendState(Index,Value)            CanActiveSendState[(Index)] = (Value)
# define Can_GetActiveSendPduInfo(Index)                CanActiveSendId[(Index)]
# define Can_GetActiveSendId(Index)                     CanActiveSendId[(Index)].id
# define Can_SetActiveSendId(Index,Value)               CanActiveSendId[(Index)].id = (Value)
# define Can_GetActiveSendLength(Index)                 CanActiveSendId[(Index)].length
# define Can_SetActiveSendLength(Index,Value)           CanActiveSendId[(Index)].length = (Value)
# define Can_GetActiveSendSdu(Index)                    CanActiveSendId[(Index)].sdu
# define Can_SetActiveSendSdu(Index,Value)              CanActiveSendId[(Index)].sdu = (Value)
# define Can_GetActiveSendSwPduHandle(Index)            CanActiveSendId[(Index)].swPduHandle
# define Can_SetActiveSendSwPduHandle(Index,Value)      CanActiveSendId[(Index)].swPduHandle = (Value)

# define Can_GetLastInitObject(Index)                   lastInitObject[(Index)]
# define Can_SetLastInitObject(Index,Value)             lastInitObject[(Index)] = (Value)
# define Can_GetCanInterruptOldStatus(Index)            canCanInterruptOldStatus[(Index)]
# define Can_SetCanInterruptOldStatus(Index,Value)      canCanInterruptOldStatus[(Index)] = (Value)
# define Can_GetCanInterruptCounter(Index)              canInterruptCounter[(Index)]
# define Can_SetCanInterruptCounter(Index,Value)        canInterruptCounter[(Index)] = (Value)
# define Can_IsIsWakeup(Index)                          (canIsWakeup[(Index)] != FALSE)
# define Can_SetIsWakeup(Index,Value)                   canIsWakeup[(Index)] = (Value)
# define Can_IsIsBusOff(Index)                          (canIsBusOff[(Index)] != FALSE)
# define Can_SetIsBusOff(Index,Value)                   canIsBusOff[(Index)] = (Value)
# define Can_GetStatusReq(Index)                        canStatusReq[(Index)] /* only CAN_MSR4 or RAM_CHECK */
# define Can_SetStatusReq(Index,Value)                  canStatusReq[(Index)] = (Value) /* only CAN_MSR4 or RAM_CHECK */
# define Can_GetLogStatus(Index)                        canStatus[(Index)]
# define Can_SetLogStatus(Index,Value)                  canStatus[(Index)] = (Value)
# define Can_GetCanLoopTimeout(ch, Index)               canLoopTimeout[(ch)][(Index)]
# define Can_IsIsHardwareCanceled(Index)                (canIsHardwareCanceled[(Index)] != FALSE)
# define Can_SetIsHardwareCanceled(Index,Value)         canIsHardwareCanceled[(Index)] = (Value)
# define Can_GetMirrorModeState(Index)                  canMirrorMode[(Index)]             /* GENy will be generated by platforms that support this feature */
# define Can_SetMirrorModeState(Index,Value)            canMirrorMode[(Index)] = (Value)   /* GENy will be generated by platforms that support this feature */
# define Can_GetSilentModeState(Index)                  canSilentMode[(Index)]             /* GENy will be generated by platforms that support this feature */
# define Can_SetSilentModeState(Index,Value)            canSilentMode[(Index)] = (Value)   /* GENy will be generated by platforms that support this feature */
# define Can_GetMailboxState(Index)                     canMailboxState[(Index)] /* only RAM_CHECK */
# define Can_SetMailboxState(Index,Value)               canMailboxState[(Index)] = (Value) /* only RAM_CHECK */

# define Can_GetCanTxBasicDataBuffer(ch,muxTx)          canTxBasicDataBuffer[(ch)][(muxTx)]
# define Can_GetRxQueueInfo()                           (canRxQueueInfo)
# define Can_GetRxQueueBuffer(Index)                    (canRxQueueBuffer[(Index)])
# define Can_IsTimeoutCall(Index)                       (canTimeoutCall[(Index)] != FALSE) /* only CAN_MSR3 */
# define Can_SetTimeoutCall(Index,Value)                canTimeoutCall[(Index)] = (Value)

#endif

# if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COM_STACK_LIB */ /* COV_CAN_MICROSAR_VERSION */
/* HighLevel */
#  if !defined(Can_GetLastInitObject)
#   define Can_GetLastInitObject(Index)          lastInitObject[(Index)]
#  endif

/* CONST PB */
#  define Can_GetNodeNum(Index)                                     CanNodeNum[(Index)]
#  define Can_GetHalt(Index)                                        canllHalt[(Index)]
#  define Can_GetTmpRxMsgMailbox(Index)                             tmpRxMsgMailbox[(Index)] 
#  define Can_GetBusOffNotified(Index)                              canllBusOffNotified[(Index)]
#  define Can_GetHwObjIndivPolling(Index)                           CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][(Index)]
#  define Can_GetSrcNum(Index)                                      CanSrcNum[(Index)]
#  define Can_GetRxBasicHandleMaxOfControllerConfig(Index)          CAN_CONTROLLER_CONFIG_INIT[(Index)].RxBasicHandleMax 
#  define Can_GetInitBT(Index)                                      CanInitBT[(Index)]
#  define Can_GetInitMaskL(Index)                                   CanInitMaskL[(Index)]
#  define Can_GetInitMaskH(Index)                                   CanInitMaskH[(Index)]
#  define Can_GetInitCodeL(Index)                                   CanInitCodeL[(Index)]
#  define Can_GetInitCodeH(Index)                                   CanInitCodeH[(Index)]
#  define Can_GetInitPortSel(Index)                                 CanInitPortSel[(Index)]
#  define Can_GetPhysPrio(Index)                                    canPhysPrio[(Index)]

# endif

/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
#define C_HL_DISABLE_OVERRUN_IN_STATUS

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_ID

/* Specify the ID tables which contain the ID type */
# define C_LL_RX_IDTYPE_TABLE      CanRxId0
# define C_LL_TX_IDTYPE_TABLE      CanTxId0

#define C_HL_DISABLE_DUMMY_FCT_CALL

#define C_HL_DISABLE_TX_MSG_DESTROYED

#define C_HL_DISABLE_CANCEL_IN_HW_TASK

#define C_HL_DISABLE_HW_EXIT_TRANSMIT 

#define C_HL_ENABLE_LAST_INIT_OBJ

#define C_HL_ENABLE_CAN_IRQ_DISABLE

#define C_HL_DISABLE_ADJUST_RXHANDLE

#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_DISABLE_COPROCESSOR_SUPPORT

#define C_HL_ENABLE_RETRANSMIT_FCT

#define C_HL_DISABLE_RETRANSMIT_CONF_ISR

#define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

# if (CAN_FD_NISO == STD_ON) /* COV_NISO_PED */
# define C_ENABLE_FD_NISO
# else
# define C_DISABLE_FD_NISO
# endif
# if (CAN_FD_PED == STD_ON) /* COV_NISO_PED */
# define C_ENABLE_FD_PED  
# else
# define C_DISABLE_FD_PED    
# endif  

/* default defines for advanced Interrupt control */
# if !defined(C_ENABLE_NESTED_INTERRUPTS) && !defined(C_DISABLE_NESTED_INTERRUPTS) /* COV_CAN_COMPATIBILITY */
#  define C_ENABLE_NESTED_INTERRUPTS
# endif
# if !defined(C_ENABLE_CAN_INTERRUPT_CONTROL) && !defined(C_DISABLE_CAN_INTERRUPT_CONTROL) /* COV_CAN_INTERRUPT_CONTROL */
#  define C_ENABLE_CAN_INTERRUPT_CONTROL
# endif

#if !defined(C_ENABLE_SUPPORT_REMOTE_FRAME) && !defined(C_DISABLE_SUPPORT_REMOTE_FRAME) /* COV_CAN_COMPATIBILITY */
# define C_DISABLE_SUPPORT_REMOTE_FRAME
#endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#define C_DLC_M           ((vuint8)0x0Fu)

/* Transmit priority is set in the upper 2 bits, EID/SID is set in the bit below prio */
#define C_EID_MASK_16     ((vuint16)kCanIdTypeExt)
#define C_EID_MASK_32     (((vuint32)kCanIdTypeExt) << 16)
#define C_EID_NOT_MASK_16 kCanIdTypeExtMask

/* macros to set DLC and ID in rx-,tx-structures -------------------------- */
/* MK... macros are used by the generation tool to fill the rx and tx structures */
/* In case the IDE bit is located in the ID registers, this bit has to be handled as must match.
   In general, this is done by setting the IDE bit to 0 in the .._MASK_.. macros.
*/

#define MK_RX_RANGE_MASK_IDSTD0(id)   ( MK_STDID0(id) )
#define MK_RX_RANGE_MASK_IDSTD1(id)   ( 0x00u )
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_CODE_IDSTD0(id)   ( MK_STDID0(id) & C_PRIO_NOT_MASK_16 )
#define MK_RX_RANGE_CODE_IDSTD1(id)   ( 0x00u )
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_MASK_IDEXT0(id)   ( MK_EXTID0(id) & C_EID_NOT_MASK_16 )
#define MK_RX_RANGE_MASK_IDEXT1(id)   ( MK_EXTID1(id) )
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_CODE_IDEXT0(id)   ( MK_EXTID0(id) & C_PRIO_NOT_MASK_16 )
#define MK_RX_RANGE_CODE_IDEXT1(id)   ( MK_EXTID1(id) )
/* macros with postfix 2-4 not used */

/*lint -emacro( (778), MK_STDID0) */
#define MK_STDID0(id)            (C_OBJ_PRIO_16 | (vuint16)(((id) & (vuint16)0x07FFu) << 2))
#define MK_STDID1(id)            ((vuint16)0x0000u)
/* macros with postfix 2-4 not used */

/*lint -emacro( (572,778), MK_EXTID0) */
#define MK_EXTID0(id)            (C_OBJ_PRIO_16 | C_EID_MASK_16 | (vuint16)(((id)&(vuint32)0x1FFF0000UL) >> 16) )
#define MK_EXTID1(id)            ((vuint16) (id))
/* macros with postfix 2-4 not used */

#define MK_TX_DLC(dlc)       ((dlc) & C_DLC_M)
#define MK_TX_DLC_EXT(dlc)   (MK_TX_DLC(dlc))

/* extract  DLC from register format to logical format */
#define XT_TX_DLC(dlc)       ((dlc) & C_DLC_M)

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CanResetBusOffStart(a)  (CanInit(a))  

# define CanResetBusOffEnd(a)

/* Bus-Sleep functions */
# define CanResetBusSleep(a)     (CanInit(a))

#else
# define CanResetBusOffStart(ch, a)  (CanInit((ch), (a)))  
# define CanResetBusOffEnd(ch, a)
  
/* Bus-Sleep functions */
# define CanResetBusSleep(ch, a)     (CanInit((ch), (a)))
#endif
 
#if defined(MISRA_CHECK)  /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdRaw0",3305 /*  MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdRaw1",3305 /*  MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",310,3305  /* MD_Can_0310, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",310,3305  /* MD_Can_0310, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",310,3305 /* MD_Can_0310, MD_Can_3305_LL */
#endif
/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/

# define CanRxActualIdRaw0(rxStruct)   ((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[13]))
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdRaw1(rxStruct)   ((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[12]))
/* macros with postfix 2-4 not used */
#else
/* macros with postfix 1-4 not used */
#endif

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
#  if defined(CAN_GEN_COM_STACK_LIB) && !defined(C_ENABLE_HWBUFFER) /* COV_CAN_COM_STACK_LIB */
#   define CanRxActualExtId(rxStruct)         (((rxStruct)->pChipMsgObj[1]) & (vuint32)0x1FFFFFFFUL)
#   if defined( C_ENABLE_EXTENDED_ID )
#    define CanRxActualIdExtHi(rxStruct)      ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[7]) & (vuint8)0x1Fu )
#    define CanRxActualIdExtMidHi(rxStruct)   ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[6]) )
#    define CanRxActualIdExtMidLo(rxStruct)   ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[5]) )
#    define CanRxActualIdExtLo(rxStruct)      ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[4]) )
#   endif
#  else
#   define CanRxActualExtId(rxStruct)         (((rxStruct)->pChipMsgObj[6]) & (vuint32)0x1FFFFFFFUL)
#   if defined( C_ENABLE_EXTENDED_ID )
#    define CanRxActualIdExtHi(rxStruct)      ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[0x1B]) & (vuint8)0x1Fu )
#    define CanRxActualIdExtMidHi(rxStruct)   ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[0x1A]) )
#    define CanRxActualIdExtMidLo(rxStruct)   ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[0x19]) )
#    define CanRxActualIdExtLo(rxStruct)      ((((CanChipMsgPtr8)((rxStruct)->pChipMsgObj))[0x18]) )
#   endif
#  endif

#if defined(CAN_GEN_COM_STACK_LIB) && !defined(C_ENABLE_HWBUFFER)  /* COV_CAN_COM_STACK_LIB */
 #define CanRxActualStdId(rxStruct)       (((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[3])>>2) & (vuint16)0x07FFU)

 #define CanRxActualData(rxStruct, i)     ((rxStruct)->pChipData[i])
 #define CanRxActualDLC(rxStruct)         (((rxStruct)->pChipData[-0x05]) & C_DLC_M)
 #define CanRxActualFdType(rxStruct)      (((rxStruct)->pChipData[-0x08]) & kCanFdTypeFd)
 #define CanRxActualIdType(rxStruct)      ((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[3]) & C_EID_MASK_16)
#else
 #define CanRxActualStdId(rxStruct)       (((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[13])>>2) & (vuint16)0x07FFU)

 #define CanRxActualData(rxStruct, i)     ((rxStruct)->pChipData[i])
 #define CanRxActualDLC(rxStruct)         (((rxStruct)->pChipData[-0x0D]) & C_DLC_M)
 #define CanRxActualFdType(rxStruct)      (((rxStruct)->pChipData[-0x10]) & kCanFdTypeFd)
 #define CanRxActualIdType(rxStruct)      ((((CanChipMsgPtr16)((rxStruct)->pChipMsgObj))[13]) & C_EID_MASK_16)
#endif
/*lint -emacro( (826), CanRxActualIdType) */

# if defined (C_SINGLE_RECEIVE_CHANNEL )
#  define CanRxActualErrorCounter()        (*((CanChipMsgPtr8)(CanNodeAdr[0]+(vuint32)0x14)))
#  define CanTxActualErrorCounter()        (*((CanChipMsgPtr8)(CanNodeAdr[0]+(vuint32)0x15)))
# else
#  define CanRxActualErrorCounter(ch)      (*((CanChipMsgPtr8)(CanNodeAdr[(ch)]+(vuint32)0x14)))
#  define CanTxActualErrorCounter(ch)      (*((CanChipMsgPtr8)(CanNodeAdr[(ch)]+(vuint32)0x15)))
# endif

/* Macros for CAN message access within GenericConfirmation() function */
#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualStdId",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualExtId",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualDLC",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualIdType",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualFdType",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
#endif
#define CanTxActualStdId(txConfStruct)        (((((CanChipMsgPtr16)((txConfStruct)->pChipMsgObj))[13])>>2) & (vuint16)0x07FFU)
#define CanTxActualExtId(txConfStruct)        (((txConfStruct)->pChipMsgObj[6]) & (vuint32)0x1FFFFFFFUL)
#define CanTxActualDLC(txConfStruct)          ((((CanChipMsgPtr8)((txConfStruct)->pChipMsgObj))[3]) & C_DLC_M)
#define CanTxActualIdType(txConfStruct)       ((((CanChipMsgPtr16)((txConfStruct)->pChipMsgObj))[13]) & C_EID_MASK_16)
#define CanTxActualData(txConfStruct,i)       ((txConfStruct)->pChipData[i])
#define CanTxActualFdType(txConfStruct)       (((CanChipMsgPtr8)((txConfStruct)->pChipMsgObj))[0] & kCanFdTypeFd)
/* Macros for CAN message access within PreTransmit() function */
#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxWriteActId",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxWriteActDLC",3458 /* MD_Can_3458 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxWriteActExtId",310,3458,3305 /* MD_Can_0310, MD_Can_3458, MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanMsgTransmitSetStdId",3458 /* MD_Can_3458 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanMsgTransmitSetExtId",3458 /* MD_Can_3458 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanMsgTransmitSetDlc",3458 /* MD_Can_3458 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanMsgTransmitSetData",3458 /* MD_Can_3458 */
#endif
#define CanTxWriteActId(txStruct, id)      { ((CanChipMsgPtr16)((txStruct).pChipData[0x0A])) = MK_STDID0((id));   }/* PRQA S 3458 */ /* MD_Can_3458 */

# define CanTxWriteActDLC(txStruct, dlc)   { ((txStruct).pChipData[0x0D]) = ((vuint8) (dlc));}/* PRQA S 3458 */ /* MD_Can_3458 */
# define CanTxWriteActExtId(txStruct, id)  { ((CanChipMsgPtr)((txStruct).pChipData[0x08])) = ((C_OBJ_PRIO_32 | C_EID_MASK_32 | ((id) & (vuint32)0x1FFFFFFFUL)));  }/* PRQA S 3458 */ /* MD_Can_3458 */

/* Macros to fill variables of the type tCanMsgTransmitStruct */
#define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)               { (pCanMsgTransmitStruct)->IdRaw0 = MK_STDID0((id));  \
                                                                          (pCanMsgTransmitStruct)->IdRaw1 = MK_STDID1((id));  }/* PRQA S 3458 */ /* MD_Can_3458 */
#define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)               { (pCanMsgTransmitStruct)->IdRaw0 = MK_EXTID0((id));  \
                                                                          (pCanMsgTransmitStruct)->IdRaw1 = MK_EXTID1((id));  }/* PRQA S 3458 */ /* MD_Can_3458 */
#define CanMsgTransmitSetDlc(pCanMsgTransmitStruct, dlc)                { (pCanMsgTransmitStruct)->DlcRaw = MK_TX_DLC((dlc)); }/* PRQA S 3458 */ /* MD_Can_3458 */
#define CanMsgTransmitSetData(pCanMsgTransmitStruct, dataByte, msgData) { (pCanMsgTransmitStruct)->DataFld[dataByte] = (msgData); }/* PRQA S 3458 */ /* MD_Can_3458 */

/* macros for buffer access */
#define StartRxReadSync()          (VStdSuspendAllInterrupts())
#define EndRxReadSync()            (VStdResumeAllInterrupts())

#define StartRxWriteSync()         (VStdSuspendAllInterrupts())
#define EndRxWriteSync()           (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()         (VStdSuspendAllInterrupts())
#define EndTxWriteSync()           (VStdResumeAllInterrupts())

#define StartRxWriteCANSync() 
#define EndRxWriteCANSync()   

#define StartRxReadCANSync()  
#define EndRxReadCANSync()    

/* look for newdat-bit and read until no change */
#define StartRxFullCANReadSync(Obj)
#define EndRxFullCANReadSync(Obj)

#define StartRxFullCANWriteSync(obj)
#define EndRxFullCANWriteSync(obj)

/* macros for flag access */
#define CanStartFlagWriteSync()    (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()      (VStdResumeAllInterrupts())

#define CAN_HL_MIN(x,y) (((x)>(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */
#define CAN_HL_MAX(x,y) (((x)<(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */

/***************************************************************************************************/
/* Macros for dummy statements */
#if !defined(CAN_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT(x) (x) = (x)
# else
#  define CAN_DUMMY_STATEMENT(x)
# endif
#endif
#if !defined(CAN_DUMMY_STATEMENT_CONST) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT_CONST(x) (void)(x)
# else
#  define CAN_DUMMY_STATEMENT_CONST(x)
# endif
#endif

/***************************************************************************************************/
/* Macros for DET and assertions */
#if (CAN_DEV_ERROR_REPORT == STD_ON) /* \trace SPEC-1404, SPEC-1696, SPEC-3803, SPEC-3849 */
/* \trace SPEC-1725, SPEC-1403, SPEC-1568, SPEC-3781, SPEC-3819 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
#  define Can_CallDetReportError(api, err) ((void) Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# else
#  define Can_CallDetReportError(api, err) (Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# endif
# define assertHardware(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define C_ENABLE_HARDWARE_CHECK
# define C_ENABLE_INTERNAL_CHECK
# define C_ENABLE_USER_CHECK
# define C_ENABLE_GEN_CHECK
#else
# define Can_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif
# define CAN_IS_NO_ERROR(errorId)

/***************************************************************************************************/
/* Macros for Critical Area abstraction */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# define Can_EnterCritical(area)     SchM_Enter_Can_##area() /* PRQA S 0342 */ /* MD_Can_0342 */
# define Can_LeaveCritical(area)     SchM_Exit_Can_##area() /* PRQA S 0342*/ /* MD_Can_0342 */
#else
# define Can_EnterCritical(area)     SchM_Enter_Can(area) /* do not use double brackets here ESCAN00060494 */
# define Can_LeaveCritical(area)     SchM_Exit_Can(area)
#endif

#define CanDeclareGlobalInterruptOldStatus
/* CAN_EXCLUSIVE_AREA_0 called only by LL code */
#define CanSingleGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanSingleGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptDisable()           Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptRestore()           Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)

/* For LL: parameter has to be 'channel' not CAN_CHANNEL_PARA_ONLY */
# define CAN_CAN_INTERRUPT_RESTORE(ch)  Can_EnableControllerInterrupts((uint8)(ch))
# define CAN_CAN_INTERRUPT_DISABLE(ch)  Can_DisableControllerInterrupts((uint8)(ch))

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */

/***************************************************************************/
/* error codes                                                             */
/***************************************************************************/
/* error numbers for User Assertions 0x20-0x3f - hardware depended */

/* error numbers for Generation tool Assertions 0x60-0x7f - hardware depended */
#define kErrorBasicCANMask                   ((vuint8)0x60)
#define kErrorInterruptMaskTable             ((vuint8)0x61)
#define kErrorMailboxLayout                  ((vuint8)0x62)
/* error numbers for Hardware Assertions 0xa0-0xbf - hardware depended */
#define kErrorUnknownInterrupt               ((vuint8)0xa0)
#define kErrorUnknownISRPriority             ((vuint8)0xa1)
#define kErrorUnknownISRGroup                ((vuint8)0xa2)
/* error numbers for Internal Assertions 0xe0-0xff - hardware depended */

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* Defines / data types / structures / unions                              */
/***************************************************************************/
#define CAN_MULTICAN                   0u
#define CAN_MULTICANR                  1u
#define CAN_MULTICANR_CH_OFFSET        8u
#define CAN_MULTICANR_MSGOBJ_OFFSET    256u

#if defined(C_ENABLE_MULTIPLE_CELLS)
# define kCanBaseAdr                   (Can_GetBaseAdrOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel)))
# if defined(C_ENABLE_CONFIGURE_SRC_ADDRESS) /* COV_CAN_AURIX_DERIVATIVE */
#  define kCanSRCAdr                   (Can_GetSrcAdrOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel)))
# endif
# define CAN_MAX_NUM_MSGOBJ            (Can_GetMaxMailboxAmountOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel)))
# define CAN_MAX_PND_REG               (CAN_MAX_MAILBOX_AMOUNT >> 5)  /* ESCAN00093346 */
#else
# if (kCanNumberOfPhysChannels <= CAN_MULTICANR_CH_OFFSET)  /* COV_CAN_GENDATA_FAILURE */
#  define canll_channel_offset 0u
# else
#  define canll_channel_offset CAN_MULTICANR_CH_OFFSET
# endif
#endif

#if (CAN_SAFE_BSW == STD_ON)
/* Define HW Object Index Safe Mask according to the number of HW Objects in the corresponding CAN cell */
# if !defined(C_ENABLE_MULTIPLE_CELLS)
#  define CAN_HWOBJ_SAFE_MASK(x)             ((x) & (CAN_MAX_MAILBOX_AMOUNT - 1u))
#  define CAN_MAX_NUM_NODE_SAFE_LIMIT        CAN_MAX_HW_NODE_AMOUNT
#  if (CAN_HWOBJ_SAFE_MASK(CAN_MAX_MAILBOX_AMOUNT) != 0)
#   error "The HW Object Index Safe Mask is not valid. Please double check if CAN_MAX_MAILBOX_AMOUNT is a power of 2!"
#  endif
# else /* when C_ENABLE_MULTIPLE_CELLS is defined */
#  define CAN_HWOBJ_SAFE_MASK(x)             ((x) & (Can_GetMaxMailboxAmountOfCellInfo(((x) < 256) ? CAN_MULTICAN : CAN_MULTICANR) - 1u))
#  define CAN_MAX_NUM_NODE_SAFE_LIMIT        (Can_GetMaxHwNodeAmountOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel)))
/* Safe mask check will happen in runtime, when C_ENABLE_MULTIPLE_CELLS is defined */
# endif
#else
# define CAN_HWOBJ_SAFE_MASK(x)              (x)
#endif

/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */
/* ESCAN00073593 struct is not defined as volatile because the generated one for ASR is not too */
typedef  struct tCanMsgObj
{                             /* 1000h + 0x20 * m */
  vuint8  MoFCR_Mode;         /*!< Message Object Function Control Register; Section: Message Mode Control    +0x00 */
  vuint8  MoFCR_Gate;         /*!< Message Object Function Control Register; Section: Gateway                 +0x01 */
  vuint8  MoFCR_IE;           /*!< Message Object Function Control Register; Section: interrupts              +0x02 */
  vuint8  MoFCR_DLC;          /*!< Message Object Function Control Register; Section: DLC                     +0x03 */
  vuint8  MoFGPR_BOT;         /*!< Message Object FIFO Pointer Register; Section Bottom Pointer               +0x04 */
  vuint8  MoFGPR_TOP;         /*!< Message Object FIFO Pointer Register; Section Top Pointer                  +0x05 */
  vuint8  MoFGPR_CUR;         /*!< Message Object FIFO Pointer Register; Section Current Pointer              +0x06 */
  vuint8  MoFGPR_SEL;         /*!< Message Object FIFO Pointer Register; Section Select Pointer               +0x07 */
  vuint16 MoIPR;              /*!< Message Object Interrupt Pointer Register                                  +0x08 */
  vuint16 reserved;           /*!< Message Object Interrupt Pointer Register: CAN Frame Counter (not used)    +0x0A */
  vuint16 MoAMRLo;            /*!< Message Object Acceptance Mask Register Low                                +0x0C */
  vuint16 MoAMRHi;            /*!< Message Object Acceptance Mask Register High                               +0x0E */
  vuint32 MoDR[2];            /*!< Message Object Data Register    2x 32 bit                                  +0x10 */
  vuint16 MoARLo;             /*!< Message Object Arbitration Register  Low                                   +0x18 */
  vuint16 MoARHi;             /*!< Message Object Arbitration Register  High                                  +0x1A */
  vuint16 MoCtrL;             /*!< Message Object Control Register Low                                        +0x1C */
  vuint16 MoCtrH;             /*!< Message Object Control Register Low                                        +0x1E */
} tCanMsgObjStruct;  /* CAN_MSG_OBJ_PTR */

#if defined(C_ENABLE_CAN_FD_FULL)
typedef  struct tCanFdMsgObj
{                             /* 1000h + 0x20 * m */ 
  vuint32 MoDR[7];            /*!< Message Object Data Register    7x 32 bit                                  +0x00 */
  vuint16 MoCtrL;             /*!< Message Object Control Register Low                                        +0x1C */
  vuint16 MoCtrH;             /*!< Message Object Control Register High                                       +0x1E */
} tCanFdMsgObjStruct;  /* CAN_MSG_OBJ_PTR */
#endif

V_DEF_P2SFR_CAN_TYPE(volatile, tCanMsgObjStruct) CanMsgObjStructPtr;
# if defined(C_ENABLE_CAN_FD_FULL)
V_DEF_P2SFR_CAN_TYPE(volatile, tCanFdMsgObjStruct) CanFdMsgObjStructPtr;
# endif
# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFCR_Mode",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFCR_IE",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFCR_DLC",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR_FDSlave",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR_FIFO_BASE",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoIPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoAMRLo",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoAMRHi",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoDR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoARLo",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoARHi",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoCtrL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoCtrH",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFCR_Mode",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFCR_IE",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFCR_DLC",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR_FIFO_BASE",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR_BOT",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR_TOP",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MoFGPR_SEL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoIPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoAMRLo",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoAMRHi",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoDR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoARLo",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoARHi",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoCtrL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoCtrH",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_RET_MoCtrL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR_BOT",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR_TOP",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR_CUR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MoFGPR_SEL",0303 /* MD_Can_0303_HWaccess */
# endif
# define CAN_SET_MoFCR_Mode(x, value) (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFCR_Mode) = (value)
# define CAN_SET_MoFCR_IE(x, value)   (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFCR_IE) = (value)
# define CAN_SET_MoFCR_DLC(x, value)  (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFCR_DLC) = (value)
# define CAN_SET_MoFGPR(x, obj)       (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR) = ( ((vuint32)((vuint8)(obj))<<24) | ((vuint32)((vuint8)(obj))<<16) | ((vuint32)((vuint8)(x))<<8) | (vuint32)((vuint8)(obj)) )
# define CAN_SET_MoFGPR_FDSlave(x)    (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR) = ( ((vuint32)((vuint8)(x))<<24) | ((vuint32)((vuint8)(x))<<16) | ((vuint32)(((vuint8)(x))+2)<<8) | (vuint32)(((vuint8)(x))+1) )
# define CAN_SET_MoFGPR_FIFO_BASE(x, base, last)     (CanObjectHandle)(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR) = ( ((vuint32)((vuint8)(base))<<24) | ((vuint32)((vuint8)(base))<<16) | (((vuint32)((vuint8)(last)))<<8) | (vuint32)((vuint8)(base)) )

# define CAN_SET_MoFGPR_BOT(x, value) (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR_BOT) = (value)
# define CAN_SET_MoFGPR_TOP(x, value) (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR_TOP) = (value)
# define CAN_SET_MoFGPR_SEL(x, value) (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoFGPR_SEL) = (value)

# define CAN_SET_MoIPR(x, value)      (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoIPR) = (value)
# define CAN_SET_MoAMRLo(x, value)    (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoAMRLo) = (value)
# define CAN_SET_MoAMRHi(x, value)    (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoAMRHi) = (value)
# define CAN_SET_MoDR(x, valuePtr)    {(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoDR[0]) = (valuePtr)[0]; \
                                       (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoDR[1]) = (valuePtr)[1]; }
# define CAN_SET_MoARLo(x, value)     (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoARLo) = (value)
# define CAN_SET_MoARHi(x, value)     (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoARHi) = (value)
# define CAN_SET_MoCtrL(x, value)     (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoCtrL) = (value)
# define CAN_SET_MoCtrH(x, value)     (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])->MoCtrH) = (value)
# define CAN_GET_MoFCR_Mode(x, value) (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFCR_Mode)
# define CAN_GET_MoFCR_Gate(x, value) (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFCR_Gate)
# define CAN_GET_MoFCR_IE(x, value)   (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFCR_IE)
# define CAN_GET_MoFCR_DLC(x, value)  (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFCR_DLC)
# define CAN_GET_MoFGPR(x, value)     (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFGPR)

# define CAN_GET_MoFGPR_BOT(x, value) (value) = ((CanObjectHandle)(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFGPR_BOT))
# define CAN_GET_MoFGPR_TOP(x, value) (value) = ((CanObjectHandle)(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFGPR_TOP))
# define CAN_GET_MoFGPR_CUR(x, value) (value) = ((CanObjectHandle)(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFGPR_CUR))
# define CAN_GET_MoFGPR_SEL(x, value) (value) = ((CanObjectHandle)(((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoFGPR_SEL))

# define CAN_GET_MoIPR(x, value)      (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoIPR)
# define CAN_GET_MoAMRLo(x, value)    (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoAMRLo)
# define CAN_GET_MoAMRHi(x, value)    (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoAMRHi)
# define CAN_GET_MoDR(x, valuePtr)    {(valuePtr)[0] = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoDR[0]); \
                                       (valuePtr)[1] = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoDR[1]); }

# define CAN_GET_MoARLo(x, value)     (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoARLo)
# define CAN_GET_MoARHi(x, value)     (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoARHi)
# define CAN_GET_MoCtrL(x, value)     (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoCtrL)
# define CAN_GET_MoCtrH(x, value)     (value) = (((CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)(x)])->MoCtrH)

# define CAN_SET_PMAILBOX_MoFCR_Mode(value) pCanCellMailbox->MoFCR_Mode = (value)
# define CAN_SET_PMAILBOX_MoFCR_IE(value)   pCanCellMailbox->MoFCR_IE = (value)
# define CAN_SET_PMAILBOX_MoFCR_DLC(value)  pCanCellMailbox->MoFCR_DLC = (value)

# define CAN_SET_PMAILBOX_MoFGPR_BOT(value) pCanCellMailbox->MoFGPR_BOT = (value)
# define CAN_SET_PMAILBOX_MoFGPR_TOP(value) pCanCellMailbox->MoFGPR_TOP = (value)
# define CAN_SET_PMAILBOX_MoFGPR_SEL(value) pCanCellMailbox->MoFGPR_SEL = (value)

# define CAN_SET_PMAILBOX_MoIPR(value)      pCanCellMailbox->MoIPR = (value)
# define CAN_SET_PMAILBOX_MoAMRLo(value)    pCanCellMailbox->MoAMRLo = (value)
# define CAN_SET_PMAILBOX_MoAMRHi(value)    pCanCellMailbox->MoAMRHi = (value)
# define CAN_SET_PMAILBOX_MoDR(valuePtr)    {pCanCellMailbox->MoDR[0] = (valuePtr)[0];  \
                                                pCanCellMailbox->MoDR[1] = (valuePtr)[1]; }
# define CAN_SET_PMAILBOX_MoARLo(value)     pCanCellMailbox->MoARLo = (value)
# define CAN_SET_PMAILBOX_MoARHi(value)     pCanCellMailbox->MoARHi = (value)
# define CAN_SET_PMAILBOX_MoCtrL(value)     pCanCellMailbox->MoCtrL = (value)
# define CAN_SET_PMAILBOX_MoCtrH(value)     pCanCellMailbox->MoCtrH = (value)
# define CAN_GET_PMAILBOX_MoFCR_Mode(value) (value) = pCanCellMailbox->MoFCR_Mode
# define CAN_GET_PMAILBOX_MoFCR_Gate(value) (value) = pCanCellMailbox->MoFCR_Gate
# define CAN_GET_PMAILBOX_MoFCR_IE(value)   (value) = pCanCellMailbox->MoFCR_IE
# define CAN_GET_PMAILBOX_MoFCR_DLC(value)  (value) = pCanCellMailbox->MoFCR_DLC
# define CAN_GET_PMAILBOX_MoFGPR(value)     (value) = pCanCellMailbox->MoFGPR

# define CAN_GET_PMAILBOX_MoFGPR_BOT(value) (value) = (CanObjectHandle)(pCanCellMailbox->MoFGPR_BOT)
# define CAN_GET_PMAILBOX_MoFGPR_TOP(value) (value) = (CanObjectHandle)(pCanCellMailbox->MoFGPR_TOP)
# define CAN_GET_PMAILBOX_MoFGPR_CUR(value) (value) = (CanObjectHandle)(pCanCellMailbox->MoFGPR_CUR)
# define CAN_GET_PMAILBOX_MoFGPR_SEL(value) (value) = (CanObjectHandle)(pCanCellMailbox->MoFGPR_SEL)

# define CAN_GET_PMAILBOX_MoIPR(value)      (value) = pCanCellMailbox->MoIPR
# define CAN_GET_PMAILBOX_MoAMRLo(value)    (value) = pCanCellMailbox->MoAMRLo
# define CAN_GET_PMAILBOX_MoAMRHi(value)    (value) = pCanCellMailbox->MoAMRHi
# define CAN_GET_PMAILBOX_MoDR(valuePtr)    {(valuePtr)[0] = pCanCellMailbox->MoDR[0]; \
                                             (valuePtr)[1] = pCanCellMailbox->MoDR[1]; }

# define CAN_GET_PMAILBOX_MoARLo(value)     (value) = pCanCellMailbox->MoARLo
# define CAN_GET_PMAILBOX_MoARHi(value)     (value) = pCanCellMailbox->MoARHi
# define CAN_GET_PMAILBOX_MoCtrL(value)     (value) = pCanCellMailbox->MoCtrL
# define CAN_GET_PMAILBOX_MoCtrH(value)     (value) = pCanCellMailbox->MoCtrH

# define CAN_RET_MoCtrL(x)            canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK(x)].MoCtrL
# define  CanXC800GlobalInterruptDeclare
# define  CanXC800GlobalInterruptDisable()
# define  CanXC800GlobalInterruptRestore()

typedef volatile struct tCanNode
{
  vuint16 NCR;                /*!< Node Control Register             +0x00 */
  vuint16 reserved1;
  vuint16 NSR;                /*!< Node Status Register              +0x04 */
  vuint16 reserved2;
  vuint16 NIPR;               /*!< Node Interrupt Pointer Register   +0x08 */
  vuint16 reserved3;
  vuint16 NPCR;               /*!< Node Port Control Register        +0x0C */
  vuint16 reserved4;
#if defined( C_ENABLE_CAN_FD_USED )
  vuint32 NBTR;               /*!< Node Bit Timing Register, Extended view if FDEN in CAN_NCR is set        +0x10 */
#else
  vuint16 NBTR;               /*!< Node Bit Timing Register, Standard view if FDEN in CAN_NCR is  not set   +0x10 */
  vuint16 reserved5;          
#endif  
  vuint8  NECnt_Rec;          /*!< Node Error Counter Register section "Receive error counter"              +0x14 */ 
  vuint8  NECnt_Tec;          /*!< Node Error Counter Register section "Transmit error counter"             +0x15 */ 
  vuint8  NECnt_EWRNLVL;      /*!< Node Error Counter Register section "Error warning level"                +0x16 */
  vuint8  reserved6;          /*!< Node Error Counter Register section not used                             +0x17 */
  vuint16 NFCRL;              /*!< Node Frame Counter, low word not used                                    +0x18 */
  vuint16 NFCRH;              /*!< Node Frame Counter, high word                                            +0x20 */
#if defined( C_ENABLE_CAN_FD_USED )
  vuint8  reserved7[0x1C];    
  vuint32 FNBTR;              /*!< Fast Node Bit Timing register                                            +0x38 */
  vuint32 NTDCR;              /*!< Node Transmitter Delay Compensation Register                             +0x3C */
  vuint8  reserved8[0xC0];    /* up to next node */
#else 
  vuint8  reserved7[0xE4];    /* up to next Node */
#endif
} tCanNodeStruct;  /* CAN_NODE_PTR */

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanNodeStruct) CanNodeStructPtr;
# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NSR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NIPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NPCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NBTR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_FNBTR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NTDCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NECnt_Rec",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NECnt_Tec",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NECnt_EWRNLVL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NSR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NIPR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NPCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NBTR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NECnt_Rec",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NECnt_Tec",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_NECnt_EWRNLVL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_RET_NCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NCR_GLOBAL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_NCR_CELL",0303 /* MD_Can_0303_HWaccess */
# endif
# define CAN_SET_NCR(x, value)           pCanCellNode->NCR = (value)
# define CAN_SET_NSR(x, value)           pCanCellNode->NSR = (value)
# define CAN_SET_NIPR(x, value)          pCanCellNode->NIPR = (value)
# define CAN_SET_NPCR(x, value)          pCanCellNode->NPCR = (value)
# define CAN_SET_NBTR(x, value)          pCanCellNode->NBTR = (value)
# define CAN_SET_FNBTR(x, value)         pCanCellNode->FNBTR = (value)
# define CAN_SET_NTDCR(x, value)         pCanCellNode->NTDCR = (value)
# define CAN_SET_NECnt_Rec(x, value)     pCanCellNode->NECnt_Rec = (value)
# define CAN_SET_NECnt_Tec(x, value)     pCanCellNode->NECnt_Tec = (value)
# define CAN_SET_NECnt_EWRNLVL(x, value) pCanCellNode->NECnt_EWRNLVL = (value)
# define CAN_GET_NCR(x, value)           (value) = pCanCellNode->NCR
# define CAN_GET_NSR(x, value)           (value) = pCanCellNode->NSR
# define CAN_GET_NIPR(x, value)          (value) = pCanCellNode->NIPR
# define CAN_GET_NPCR(x, value)          (value) = pCanCellNode->NPCR
# define CAN_GET_NBTR(x, value)          (value) = pCanCellNode->NBTR
# define CAN_GET_NECnt_Rec(x, value)     (value) = pCanCellNode->NECnt_Rec
# define CAN_GET_NECnt_Tec(x, value)     (value) = pCanCellNode->NECnt_Tec
# define CAN_GET_NECnt_EWRNLVL(x, value) (value) = pCanCellNode->NECnt_EWRNLVL
# define CAN_RET_NCR(x)                  canCellPtr->Node[(x)].NCR
# define CAN_SET_NCR_GLOBAL(x, value)    canCellPtr->Node[(x)].NCR = (value)

# if defined (C_ENABLE_MULTIPLE_CELLS)
#  define CAN_SET_NCR_CELL(cell, x, value) ((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(cell))->Node[(x)].NCR = (value)
# endif

typedef volatile struct tCanModul
{
  vuint16 LISTHi[CAN_MAX_LIST]; /*!< List Register Hi                                      +0x100 */
  vuint16 LISTLo[CAN_MAX_LIST]; /*!< List Register Lo                                      +0x100 */
  vuint32 MSPND[CAN_MAX_MSPND]; /*!< Message Pending Register                              +0x140 */
  vuint32 MSID[CAN_MAX_MSID];   /*!< Message Index Register                                +0x180 */
  vuint32 MSIMask;              /*!< Message Index Mask Registger                          +0x1C0 */
  vuint16 PanCmd;               /*!< Panel Control Register: Panel Command                 +0x1C4 */
  vuint16 PanPara;              /*!< Panel Control Register: Panel Para                    +0x1C6 */
  vuint16 regMCR;               /*!< Module Control Register                               +0x1C8 */
  vuint16 reserved4;
  vuint32 regMITR;              /*!< Module Interrupt Trigger Control Register  (unused)   +0x1CC */
  vuint8  reserved5[0x30];      /*!< unused                                                       */
} tCanModulStruct;  /* CAN_MODUL_CTR_PTR */

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MSPND",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MSIMask",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_PanCmd",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_PanPara",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_CAN_SET_MSPND",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MSPND",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MSID",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MSIMask",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_PanCmd",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_PanPara",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MCR",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_CAN_SET_MSPND",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_PanCmd_CELL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_PanPara_CELL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_PanCmd_CELL",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SET_MCR_CELL",0303 /* MD_Can_0303_HWaccess */
# endif
# if (CAN_SAFE_BSW == STD_ON)
# define CAN_SET_MSPND(x, value) canCellPtr->Modul.MSPND[((x) & 0x07)] = (value)
# else
# define CAN_SET_MSPND(x, value) canCellPtr->Modul.MSPND[(x)] = (value)
# endif
/* # define CAN_SET_MSID(x, value)  canCellPtr->Modul.MSID[(x)] = (value) */
# define CAN_SET_MSIMask(value)  canCellPtr->Modul.MSIMask = (value)
# define CAN_SET_PanCmd(value)   canCellPtr->Modul.PanCmd = (value)
# define CAN_SET_PanPara(value)  canCellPtr->Modul.PanPara = (value)
# define CAN_SET_MCR(value)      canCellPtr->Modul.regMCR = (value)
# define CAN_GET_MSPND(x, value) (value) = canCellPtr->Modul.MSPND[(x)]
# define CAN_GET_MSID(x, value)  (value) = (vuint8)(canCellPtr->Modul.MSID[(x)] & (vuint32)0x000000FFu)
# define CAN_GET_MSIMask(value)  (value) = canCellPtr->Modul.MSIMask
# define CAN_GET_PanCmd(value)   (value) = canCellPtr->Modul.PanCmd
# define CAN_GET_PanPara(value)  (value) = canCellPtr->Modul.PanPara
# define CAN_GET_MCR(value)      (value) = canCellPtr->Modul.regMCR
# if defined (C_ENABLE_MULTIPLE_CELLS)
# define CAN_SET_PanCmd_CELL(cell, value)   ((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(cell))->Modul.PanCmd = (value)
# define CAN_SET_PanPara_CELL(cell, value)  ((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(cell))->Modul.PanPara = (value)
# define CAN_GET_PanCmd_CELL(cell, value)   (value) = ((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(cell))->Modul.PanCmd
# define CAN_SET_MCR_CELL(cell, value)      ((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(cell))->Modul.regMCR = (value)
# endif

typedef volatile struct tCanController
{
  vuint16 CLC;                /* Clock control         +0x00 (only TriCore) */
  vuint8  reserved1[6];       /*  */
  vuint32 ID;                 /* Cell id               +0x08 (ununsed / not all derivatives) */
  vuint32 FDR;                /* Clock Dividor         +0x0c */
  vuint8  reserved2[0xB0];    /*  */
  vuint32 Src[16];            /* Interrupt Service     +0xc0 (amount depend on derivatives - seperate for MultiCan+) */
} tCanControllerStruct;  /* CAN_CONTROLLER_PTR */

typedef volatile struct tCanCell
{                                                   /* BaseAddress + ... */
  tCanControllerStruct Ctrl;                        /* 0     - 0x100 */
  tCanModulStruct      Modul;                       /* 0x100 - 0x1D0 */
  tCanNodeStruct       Node[CAN_MAX_NODE];          /* 0x200 - x(derivative) / include reserved */
# if defined(C_ENABLE_MULTIPLE_CELLS)
  tCanMsgObjStruct     Obj[CAN_MAX_MAILBOX_AMOUNT]; /* x - y (derivative) */
# else
  tCanMsgObjStruct     Obj[CAN_MAX_NUM_MSGOBJ];     /* x - y (derivative) */
# endif
} tCanCellStruct;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanCellStruct) tCanCellStructPtr;

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "canCellPtr",0303 /* MD_Can_0303_HWaccess */
# endif
# define canCellPtr       ((tCanCellStructPtr) kCanBaseAdr)

typedef struct sCanRxInfoStruct
{
  CanChipMsgPtr  pChipMsgObj;
  CanChipDataPtr pChipData;
  Can_IdType localId;
  Can_HwHandleType localHrh;
  uint8 localDlc;
  /* LL specific part */
} tCanRxInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxInfoStruct, VAR_NOINIT) CanRxInfoPtrType;

#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
typedef struct sCanTxInfoStruct
{
  CanChipDataPtr pChipData;
  /* LL specific part */
  CanChipMsgPtr  pChipMsgObj;
} tCanTxInfoStruct;
#endif

typedef struct sCanInitInfoStruct
{
  CAN_CHANNEL_CANTYPE_LOCAL
  CanInitHandle  initObject;
  uint8 isMbCorrupt;
  uint8 isChCorrupt;
  /* LL specific part */
  vuint8 canllNode; /* do not use here CanChannelHandle - compiler abstraction for automatic not allowed */
  
} tCanInitInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanInitInfoStruct, VAR_NOINIT) CanInitInfoPtrType;
#define CAN_HL_INFO_INIT_PTR(member)(initInfo->member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_INIT(member)    (initInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

typedef struct sCanRxBasicInfoStruct
{
  tCanRxInfoStruct rxInfo;
  CanObjectHandle rxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL
  /* LL specific part */
  vuint16 canMoCtrl;
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  canHwLoopRetValType canHwLoopRetVal;
  #endif
  CanXC800GlobalInterruptDeclare
} tCanRxBasicInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxBasicInfoStruct, VAR_NOINIT) CanRxBasicInfoPtrType;
#define CAN_HL_INFO_RXBASIC_PTR(member) ((*rxBasicInfo).member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_RXBASIC(member)     (rxBasicInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

typedef struct sCanRxFullInfoStruct
{
  tCanRxInfoStruct rxInfo;
  CanObjectHandle rxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL
  /* LL specific part */
  #if defined( C_ENABLE_FULLCAN_OVERRUN )
  vuint8 copy_cnt;
  #endif
  vuint8 canPndReg;
  vuint32 canPndBit;
  vuint16 canMoCtrl;
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  canHwLoopRetValType canHwLoopRetVal;
  #endif
  V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CanXC800GlobalInterruptDeclare
} tCanRxFullInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxFullInfoStruct, VAR_NOINIT) CanRxFullInfoPtrType;
#define CAN_HL_INFO_RXFULL_PTR(member) ((*rxFullInfo).member) /* PRQA S 3410 */ /* MD_Can_3410 */
#define CAN_HL_INFO_RXFULL(member)     (rxFullInfo.member)  /* PRQA S 3410 */ /* MD_Can_3410 */

V_DEF_P2VAR_TYPE(V_NONE, CanObjectHandle, VAR_NOINIT) CanHlObjectHandlePtrType;
    
/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
*  CanHL_InitRxBasicCANSubSetMask()
************************************************************************************************************/
/*! \brief         set the mask and arbitration register
 *  \details       called out of init Rx Basic CAN objects function
 *  \param[in]     initInfo         pointer to a structure which contains all necessary informations for init
 *  \param[in]     hwObjHandle      actual hwobject to be configured
 *  \param[in]     Htrh             actual logigal object to be configured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE)  CanHL_InitRxBasicCANSubSetMask(CanInitInfoPtrType initInfo, Can_HwHandleType hwObjHandle, Can_HwHandleType Htrh);

/************************************************************************************************************
*  CanHL_InitRxBasicCANSubCloseMask()
************************************************************************************************************/
/*! \brief         close the hardware filter completely
 *  \details       called out of init Rx Basic CAN objects function
 *  \param[in]     initInfo         pointer to a structure which contains all necessary informations for init
 *  \param[in]     hwObjHandle      actual hwobject to be configured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE)  CanHL_InitRxBasicCANSubCloseMask(CanInitInfoPtrType initInfo, Can_HwHandleType hwObjHandle);
#endif

#if defined(C_ENABLE_CAN_FD_FULL)
/************************************************************************************************************
 *  CanLL_GetFdData()
 ***********************************************************************************************************/
/*! \brief         copy extended FD data
 *  \details       copy the extended data of FD frames to buffer
 *  \param[in]     msgObjHandle   index of the CAN msg object which contains the extended data
 *  \param[in]     bufferPtr      pointer to a buffer where to copy the data to
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetFdData(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle msgObjHandle, uint32* bufferPtr);
#endif
#if defined(C_ENABLE_CAN_INTERRUPT_CONTROL) /* COV_CAN_INTERRUPT_CONTROL */
/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         disable CAN interrupt
 *  \details       saves the current status (enable or disable) of all 
 *                 CAN interrupts to localInterruptOldFlagPtr
 *                 and disables all CAN interrupts  (RX, TX, error, wakeup).
 *  \param[in]     canHwCh              CAN HW controller
 *  \param[out]    localInterruptOldFlagPtr  get old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CanChannelHandle  Controller, CanLLCanIntOldPtrType localInterruptOldFlagPtr);
/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 **********************************************************************************************************/
/*! \brief         enable CAN interrupt
 *  \details       restores all CAN interrupts (RX, TX, error, wakeup).
 *  \param[in]     canHwCh              CAN HW controller
 *  \param[in]     localInterruptOldFlag     old interrupt state to be restored
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CanChannelHandle  Controller, tCanLLCanIntOld localInterruptOldFlag);
#endif
#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_IsMailboxCorrupt()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the current mailbox at index hwObjHandle by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  \param[in]     hwObjHandle         Handle to hardware object
 *  \return        kCanTrue:    Mailbox is corrupt
 *  \return        kCanFalse:   Mailbox is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the channel register at the beginning of the initialization by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  \return        kCanTrue:    Channel is corrupt
 *  \return        kCanFalse:   Channel is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

# endif
#endif

/************************************************************************************************************
 *  CanLL_Reset_MoCtr()
 ***********************************************************************************************************/
/*! \brief         Register control function
 *  \details       reset register MOCTR and read back result if extended RAM check is active.
 *  \param[in]     Controller          CAN controller
 *  \param[in]     regPtr              uint16 pointer to the corresponding register MOCTRCAN.
 *  \param[in]     value               pattern of bits to be cleared
 *  \param[in]     readMask            mask of bits to be verified
 *  \return        kCanTrue:           mailbox is corrupt
 *  \return        kCanFalse:          mailbox is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanLL_Reset_MoCtr( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask );

/************************************************************************************************************
 *  CanLL_Set_MoCtr()
 ***********************************************************************************************************/
/*! \brief         Register control function
 *  \details       set register MOCTR and read back result if extended RAM check is active.
 *  \param[in]     Controller          CAN controller
 *  \param[in]     regPtr              uint16 pointer to the corresponding register MOCTRCAN.
 *  \param[in]     value               pattern of bits to be cleared
 *  \param[in]     readMask            mask of bits to be verified
 *  \return        kCanTrue:           mailbox is corrupt
 *  \return        kCanFalse:          mailbox is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanLL_Set_MoCtr( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask );

#if (CAN_SAFE_BSW == STD_ON)
/************************************************************************************************************
 *  CanLL_CheckGeneratedDataAccess()
***********************************************************************************************************/
/*! \brief         Accesses the generated data and validates it.
 *  \details       validate the generated node index and Safe Mask for message object index.
 *  \param[in]     Controller          CAN controller
 *  \return        CAN_E_GENDATA:      an error is detected
 *  \return        CAN_E_NO_ERROR:     no error is detected during this check
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckGeneratedDataAccess(CAN_CHANNEL_CANTYPE_ONLY);
#endif

/************************************************************************************************************
 *  CanInit()
 ***********************************************************************************************************/
/*! \brief         Wrapper for Can_InitController()
 *  \details       Initialization of controller specific CAN hardware. \n
 *                 The CAN driver registers and variables are initialized. \n
 *                 The CAN controller is fully initialized and left back within the state "STOP mode", ready to change to "Running Mode".
 *                 Called from LowLevel driver code while bus off handling or in case of mode transition that requires a reinitialization.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     initObject    Index of the initialization structure to be initialized (specifies the baud rate to be used.)
 *  \pre           initObject has to be valid
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInit(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject);
/************************************************************************************************************
 *  Can_CleanUpSendState()
 ***********************************************************************************************************/
/*! \brief         Clean up send state
 *  \details       Reset active send state (semaphore blocking TX while send).
 *                 Called by Can_SetControllerMode(), Can_Mainfunction_Mode() (Can_InitController() do same but without this call).
 *  \param[in]     Controller    CAN controller \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) Can_CleanUpSendState(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_HW_LOOP_TIMER) /* always used for sync mode */ /* COV_CAN_MICROSAR_VERSION */
# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/************************************************************************************************************
 *  ApplCanTimerLoop()
 ***********************************************************************************************************/
/*! \brief         Time out monitoring
 *  \details       Service function to check (against generated maximum loop value) whether a hardware loop shall be continued or broken.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \return        CAN_NOT_OK  when loop shall be broken (observation stops) \n
 *                             CAN_NOT_OK should only be used in case of a time out occurs due to a hardware issue. \n
 *                             After this an appropriate error handling is needed (see chapter Hardware Loop Check / Time out Monitoring).
 *  \return        CAN_OK      when loop shall be continued (observation continues)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Please refer to chapter "Hardware Loop Check".
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop(CAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif
#endif

/************************************************************************************************************
 *  CanHL_StartTransition()
 ***********************************************************************************************************/
/*! \brief         Request START
 *  \details       Handle START transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StartTransition(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_StopTransition()
 ***********************************************************************************************************/
/*! \brief         Request STOP
 *  \details       Handle STOP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StopTransition(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_WakeupTransition()
 ***********************************************************************************************************/
/*! \brief         Request WAKEUP
 *  \details       Handle WAKEUP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WakeupTransition(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_DoRamCheck()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Start RAM check by set request and start Can_InitController doing the check.
 *                 Called by CanHL_WakeupTransition(), Wakeup Processing, Can_RamCheckExecution().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_DoRamCheck(CAN_CHANNEL_CANTYPE_ONLY);
#endif

/************************************************************************************************************
 *  CanHL_SleepTransition()
 ***********************************************************************************************************/
/*! \brief         Request SLEEP
 *  \details       Handle SLEEP transition and wait ASR3:synchronous, ASR4:asynchronous-short time and notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller    CAN controller (Controller must be in valid range). \n
 *                               (only if not using "Optimize for one controller")
 *  \return        CAN_NOT_OK    transition rejected
 *  \return        CAN_OK        transition finished successful or is ongoing asynchronous
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_SleepTransition(CAN_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_WritePrepare()
 ***********************************************************************************************************/
/*! \brief         TX preparation
 *  \details       Search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary
 *                 Called by Can_Write().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     Hth              hardware transmit handle from (CanMailboxId)
 *  \param[in]     PduInfo          PDU info include ID, DLC, data, PDU
 *  \return        logTxObjHandle   logical transmit handle to be send
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_WritePrepare(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo);

/************************************************************************************************************
 *  CanHL_WriteStart()
 ***********************************************************************************************************/
/*! \brief         TX start
 *  \details       Write ID, DLC and Data to FullCAN or BasicCAN object and set transmit request
 *                 Called by Can_Write().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     Hth             hardware transmit handle from (CanMailboxId)
 *  \param[in]     logTxObjHandle  logical TX object handle
 *  \param[in]     PduInfo         PDU info include ID, DLC, data, PDU
 *  \return        CAN_NOT_OK      transmission failed.
 *  \return        CAN_OK          transmission successful.
 *  \return        CAN_BUSY        transition object busy - repeat it.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, CanObjectHandle logTxObjHandle, Can_PduInfoPtrType PduInfo);

/************************************************************************************************************
 *  CanHL_GetTxHwToLogHandle()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     hwTxObjHandle   Handle to hardware mailbox
 *  \return        logical handle for the given hardware mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwTxObjHandle);

/************************************************************************************************************
 *  CanHL_GetTxLogToHwHandle()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Logical to hardware Handle conversion.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     logTxObjHandle  Logical handle of TX mailbox
 *  \return        hardware mailbox for the given logical handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_HwHandleType, STATIC_CODE) CanHL_GetTxLogToHwHandle(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle);

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_RamCheckMailboxNotification()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     hwObjHandle      Handle to hardware object
 *  \param[in]     htrh             Hrh or Hth of the hardware object
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle, Can_HwHandleType htrh);
#endif

/************************************************************************************************************
 *  CanHL_SetValue8()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue8(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr8 regPtr, uint8 value, uint8 readMask);

/************************************************************************************************************
 *  CanHL_SetValue16()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue16(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask);

/************************************************************************************************************
 *  CanHL_SetValue32()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by Can_InitController().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \return        kCanTrue         RamCheck failed.
 *  \return        kCanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, uint32 value, uint32 readMask);

/************************************************************************************************************
 *  CanHL_InitBegin()
 ***********************************************************************************************************/
/*! \brief         Start Initialization
 *  \details       LL implementation see token CanLL_InitBegin description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin(CanInitInfoPtrType initInfo);

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitTxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX FullCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN(CanInitInfoPtrType initInfo);
#endif

/************************************************************************************************************
 *  CanHL_InitTxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX BasicCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN(CanInitInfoPtrType initInfo);

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX FullCAN
 *  \details       LL implementation see token CanLL_InitFullCANObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN(CanInitInfoPtrType initInfo);
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX BasicCAN
 *  \details       LL implementation see token CanLL_InitBasicCANObj description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN(CanInitInfoPtrType initInfo);
#endif

/************************************************************************************************************
 *  CanHL_InitEnd_InitMode()
 ***********************************************************************************************************/
/*! \brief         End Initialization
 *  \details       LL implementation see token CanLL_InitEnd_InitMode description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode(CanInitInfoPtrType initInfo);

/************************************************************************************************************
 *  CanHL_InitEnd_StopMode()
 ***********************************************************************************************************/
/*! \brief         Transition to STOP
 *  \details       LL implementation see token CanLL_InitEnd_StopMode description.
 *                 Called by Can_InitController().
 *  \param[in]     initInfo          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_StopMode(CanInitInfoPtrType initInfo);

/************************************************************************************************************
 *  CanHL_StopReinit()
 ***********************************************************************************************************/
/*! \brief         Reinitialization after STOP
 *  \details       LL implementation see token CanLL_StopReinit description.
 *                 Called by Can_InitController().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopReinit(CAN_HW_CHANNEL_CANTYPE_ONLY);

/************************************************************************************************************
 *  CanHL_InitPowerOn()
 ***********************************************************************************************************/
/*! \brief         Power on initialization
 *  \details       LL implementation see token CanLL_InitPowerOn description.
 *                 Called by Can_InitController().
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOn(void);

/************************************************************************************************************
 *  CanHL_InitPowerOnChannelSpecific()
 ***********************************************************************************************************/
/*! \brief         Power on channel initialization
 *  \details       LL implementation see token CanLL_InitPowerOnChannelSpecific description.
 *                 Called by Can_Init().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedBegin()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN start
 *  \details       RX BasicCAN handling start.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[in]     rxBasicInfo          include controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedBegin(CanRxBasicInfoPtrType rxBasicInfo);

/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedSearch()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN search
 *  \details       RX BasicCAN search logical HRH from hardware hwRxHandle.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[out]    rxBasicInfo          include Hrh, controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedSearch(CanRxBasicInfoPtrType rxBasicInfo);

/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivedEnd()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN end
 *  \details       RX BasicCAN handling end.
 *                 Called by CanBasicCanMsgReceived().
 *  \param[in]     rxBasicInfo          include controller and all LL specific settings.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivedEnd(CanRxBasicInfoPtrType rxBasicInfo);

# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxBasicMsgReceivePolling()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN polling
 *  \details       RX BasicCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivePolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedBegin()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN start
 *  \details       RX FullCAN handling start.
 *                 Called by CanFullCanMsgReceived().
 *  \param[in]     rxFullInfo          include controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedBegin(CanRxFullInfoPtrType rxFullInfo);

/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedSearch()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN search
 *  \details       RX FullCAN search logical HRH from hardware hwTxHandle.
 *                 Called by CanFullCanMsgReceived().
 *  \param[out]    rxFullInfo          include HRH, controller and all LL specific settings.
 *  \return        CAN_NOT_OK      reception failed.
 *  \return        CAN_OK          reception successful.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedSearch(CanRxFullInfoPtrType rxFullInfo);

/************************************************************************************************************
 *  CanHL_RxFullMsgReceivedEnd()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN end
 *  \details       RX FullCAN handling end.
 *                 Called by CanFullCanMsgReceived().
 *  \param[in]     rxFullInfo          include controller and all LL specific settings.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivedEnd(CanRxFullInfoPtrType rxFullInfo);

# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxFullMsgReceivePolling()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN polling
 *  \details       RX FullCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivePolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_RxMsgReceivedNotification()
 ***********************************************************************************************************/
/*! \brief         RX notification
 *  \details       RX queue and notification handling for BasicCAN and FullCAN reception.
 *                 Called by CanBasicCanMsgReceived(),CanFullCanMsgReceived().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxInfo          include controller and all LL specific settings.
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANTYPE_FIRST CanRxInfoPtrType rxInfo);
#endif

#if defined(C_ENABLE_RX_QUEUE)
/************************************************************************************************************
 *  CanHL_RxQueueExecution()
 ***********************************************************************************************************/
/*! \brief         RX queue
 *  \details       RX queue execution and notification.
 *                 Called by Can_MainFunction_Read().
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxQueueExecution(void);
#endif

/************************************************************************************************************
 *  CanHL_TxConfirmation()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation handling
 *  \details       Called for a transmit or cancel event. Finish transmission by free send mailbox and call confirmation. \n
 *                 Called for FullCAN and BasicCAN handling.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     txObjHandle   transmit hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanBasicCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive BasicCAN data and call indication function.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     rxObjHandle   received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanFullCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive FullCAN data and call indication function.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \param[in]     rxObjHandle   received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_ErrorHandling()
 ***********************************************************************************************************/
/*! \brief         BUSOFF handling
 *  \details       Handler for bus off situation.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/************************************************************************************************************
 *  CanHL_TxTaskConfPendingHandling()
 ***********************************************************************************************************/
/*! \brief         Tx task confirmation
 *  \details       Tx task handle the pending mailboxes.
 *                 Called by Can_MainFunction_Write().
 *  \param[in]     Controller    CAN controller. \n
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxTaskConfPendingHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);
#endif

#define CAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
/************************************************************************************************************
 *  Can_InitController()
 ***********************************************************************************************************/
/*! \brief         Initialization of controller specific CAN hardware.
 *  \details       The CAN driver registers and variables are initialized. \n
 *                 The CAN controller is fully initialized and left back within the state "STOP Mode", ready to change to "Running Mode".
 *  \param[in]     Controller            CAN controller
 *  \param[in]     ControllerConfigPtr   Pointer to the configuration data structure.
 *  \pre           Disabled Interrupts.
 *  \pre           Can_Init() has to be called.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Has to be called during the start up sequence before CAN communication takes place. \n
 *                 Must not be called while in "SLEEP Mode".
***********************************************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr );
#endif

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CAN_LOCAL_H */

/* End of channel */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCAN Erzeugungsgangnummer: 601 */

