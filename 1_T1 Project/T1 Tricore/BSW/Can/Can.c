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

/* \trace SPEC-1570 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL /* compatibility */
#define CAN_SOURCE     /* testability */
#define __CAN_SRC__              /* compatibility RTM not aware of multi driver instance */
#if !defined(__CAN_SRC__) /* driver use ORGANI without infix */ /* COV_CAN_INTERNAL */
# define __CAN_SRC__    /* for all MSR module (used by RTM) */
#endif
/* PRQA S 3109 EOF */ /* MD_Can_3109 */
/* PRQA S 0750 EOF */ /* MD_Can_0750 */
/* PRQA S 3412 EOF */ /* MD_Can_3412 */
/* PRQA S 3458 EOF */ /* MD_Can_3458 */
/* PRQA S 3453 EOF */ /* MD_Can_3453 */
/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0857 EOF */ /* MD_Can_0857 */
/* PRQA S 0828 EOF */ /* MD_Can_0828 */
/* PRQA S 0715 EOF */ /* MD_Can_0715 */

/* \trace SPEC-1408, SPEC-1590, SPEC-1588 */
/* \trace SPEC-1392 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* \trace SPEC-1707 */
#include "CanIf.h"       /* for version check */
#include "Can_Local.h"    /* have to be last include due to channel define will lead to problems */

#if defined( C_ENABLE_USE_VSTDLIB )  /* COV_CAN_VSTDLIB_USE */
# include "vstdlib.h"
#endif

#if (CAN_DEV_ERROR_REPORT == STD_ON)
/* \trace SPEC-1596 */
# include "Det.h"
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
#  include "v_ver.h"
# endif
#endif

#if !defined(CAN_AMD_RUNTIME_MEASUREMENT) /* COV_CAN_COMPATIBILITY */
# define CAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_AMD_RUNTIME_MEASUREMENT */
# include "AmdRtm.h"
#endif

#if !defined(CAN_RUNTIME_MEASUREMENT_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# define C_ENABLE_RUNTIME_MEASUREMENT_SUPPORT
# include "Rtm.h"
#endif

#if defined(C_ENABLE_CAN_FD_FULL)
# if defined(C_ENABLE_RX_QUEUE)
#  include "vstdlib.h"
# endif
#endif

/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0600u) /* \trace SPEC-1699, SPEC-3837 */
# error "Source and Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_GEN_BASE_VERSION) /* COV_CAN_COMPATIBILITY */
# if (CAN_GEN_BASE_VERSION              != 0x0106u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#elif defined(CAN_GEN_BASE_CFG5_VERSION) /* COV_CAN_COMPATIBILITY */
# define CAN_GEN_BASE_VERSION  CAN_GEN_BASE_CFG5_VERSION
# if (CAN_GEN_BASE_CFG5_VERSION         != 0x0103u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_GEN_BASE_VERSION nor CAN_GEN_BASE_CFG5_VERSION is defined"
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

#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
/* The name of this constant variable is defined via v_ver.h and depends on the version of the C file. The value of the constant variable is also defined externally and is used for consistency checks, too. */
#  define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_CONST(V_NONE, uint32, CONST) DRVCAN_TRICOREMULTICANASR_LIB_SYMBOL = DRVCAN_TRICOREMULTICANASR_LIB_VERSION;   /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED   /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif
#endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(CAN_USE_NO_VECTOR_IF) /* for testability */
# define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#else
# if defined(CANIF_VENDOR_ID) /* COV_CAN_COMPATIBILITY */
#  if (CANIF_VENDOR_ID == 0x001E) /* COV_CAN_COMPATIBILITY */
#   define CAN_USE_VECTOR_IF
#   if defined(IF_ASRIFCAN_VERSION) /* COV_CAN_COMPATIBILITY */
#    if (IF_ASRIFCAN_VERSION < 0x0410) /* COV_CAN_COMPATIBILITY */
#     define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#    endif
#   endif
#  else
#   define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#  endif
# else
#  define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
# endif
#endif
/* Compatibility to CBD */
/* instead of direct canCanInterruptCounter[] use Can_GetCanInterruptCounter(Index) abstraction for ComStackLib */

#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanHookBegin_Can_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookEnd_Can_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookBegin_Can_InitController()                    Rtm_Start(RtmConf_RtmMeasurementPoint_Can_InitController)
# define CanHookEnd_Can_InitController()                      Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_InitController)
# define CanHookBegin_Can_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookEnd_Can_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookBegin_Can_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Write)
# define CanHookEnd_Can_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Write)

#else /* BRS runtime measurement */
# define CanHookBegin_Can_Init()
# define CanHookEnd_Can_Init()
# define CanHookBegin_Can_InitController() \

# define CanHookEnd_Can_InitController() \

# define CanHookBegin_Can_SetControllerMode() \

# define CanHookEnd_Can_SetControllerMode() \

# define CanHookBegin_Can_Write() \

# define CanHookEnd_Can_Write() \

#endif

#define CanHookBegin_CanHL_TxConfirmation() \

#define CanHookEnd_CanHL_TxConfirmation() \

#define CanHookBegin_CanBasicCanMsgReceived() \

#define CanHookEnd_CanBasicCanMsgReceived() \

#define CanHookBegin_CanFullCanMsgReceived() \

#define CanHookEnd_CanFullCanMsgReceived() \

#define CanHookBegin_Can_MainFunction_Write() \

#define CanHookEnd_Can_MainFunction_Write() \

#define CanHookBegin_Can_MainFunction_Read() \

#define CanHookEnd_Can_MainFunction_Read() \

/* Define chiphardware                     */
/* Constants concerning can chip registers */
/* control registers for msg objects       */

/*!
 *  Internal comment removed.
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

/*! CAN_NCR register bit masks */
#define C_NCR_RESET          ((vuint16)0x0000)   /*!< remove Init bit and clear all other bits (no FD, no ErrInt) */
#define C_NCR_INIT           ((vuint16)0x0001)   /*!< Offline(stop) and busoff information */
#define C_NCR_TxRxIE         ((vuint16)0x0002)   /*!< enable Tx,Rx interrupts */
#define C_NCR_ErrIE          ((vuint16)0x0008)   /*!< enable Error interrupt */
#define C_NCR_IE             ((vuint16)0x000E)   /*!< enable all interrupt */
#define C_NCR_CCE            ((vuint16)0x0040)   /*!< bittiming, ports, errorregs can be written */
#define C_NCR_CALM           ((vuint16)0x0080)   /*!< enter CAN Analyzer Mode */
#define C_NCR_FDEN           ((vuint16)0x0200)   /*!< enable CANFD */

/*! CAN_NSR register bit masks */
#define C_NSR_LEC            ((vuint16)0x0003)   /*!< error code */
#define C_NSR_TXOK           ((vuint16)0x0008)   /*!< tx is done */
#define C_NSR_RXOK           ((vuint16)0x0010)   /*!< rx occure */
#define C_NSR_ALERT          ((vuint16)0x0020)   /*!< boff, ewarn, list err, init set ... warning about */
#define C_NSR_EWRN           ((vuint16)0x0040)   /*!< Warninglevel reached */
#define C_NSR_BOFF           ((vuint16)0x0080)   /*!< Busoff detected */

/*! CAN_MOCTR register bit masks */
#define C_MOCTR_RXPND        ((vuint16)0x0001)   /*!< Pending Rx */
#define C_MOCTR_TXPND        ((vuint16)0x0002)   /*!< pending Tx */
#define C_MOCTR_RXUPD        ((vuint16)0x0004)   /*!< Rx updated */
#define C_MOCTR_NEWDAT       ((vuint16)0x0008)   /*!< New Data in MsgObject */
#define C_MOCTR_MSGLOST      ((vuint16)0x0010)   /*!< 2. NEWDAT appears (used for Overrun notification) */
#define C_MOCTR_MSGVAL       ((vuint16)0x0020)   /*!< MsgObject contains valid data */
#define C_MOCTR_RTSEL        ((vuint16)0x0040)   /*!< Rx/Tx selected */
#define C_MOCTR_RXEN         ((vuint16)0x0080)   /*!< ready for rx */
#define C_MOCTR_TXREQ        ((vuint16)0x0100)   /*!< request tx */
#define C_MOCTR_TXEN0        ((vuint16)0x0200)   /*!< user enable tx */
#define C_MOCTR_TXEN1        ((vuint16)0x0400)   /*!< hw enable tx */
#define C_MOCTR_DIR          ((vuint16)0x0800)   /*!< direction tx=1 or rx=0 */
#define C_MOCTR_ALL          ((vuint16)0x0FFF)   /*!< clear all flags */

/*! CAN_MOFCR register bit masks */
#define C_MOFCR_MODE_NORMAL  (0x00)  /*!< Standard Message Object (Tx or Rx) */
#define C_MOFCR_MODE_RXBASE  (0x01)  /*!< Fifo Base Object for Rx */
#define C_MOFCR_MODE_FDBASE  (0x05)  /*!< FD Base Object */
#define C_MOFCR_IE_RX        (0x01)  /*!< Enable Rx-Interrupt for this Object */
#define C_MOFCR_IE_TX        (0x02)  /*!< Enable Tx-Interrupt for this Object */
#define C_MOFCR_IE_OVR       (0x04)  /*!< Enable Overrun-Interrupt for this Object */
#define C_MOFCR_IE_SDT       (0x40)  /*!< Single data transfer enable */
#define C_MOFCR_IE_STT       (0x80)  /*!< Single transmit enable */
#define C_MOFCR_DLC          C_DLC_M /*!< Mask for DLC */
#define C_MOFCR_BRS          (0x20)  /*!< Fast Bit timing*/
#define C_MOFCR_EDL          (0x40)  /*!< Extended data length*/

/*! CAN_MOAMR register bit masks */
#define C_MOAMRHI_CLOSE      ((vuint16)0x1FFFU) /*!< exact match */
#define C_MOAMRHI_OPEN       ((vuint16)0x0000U) /*!< all match */
#define C_MOAMRLO_CLOSE      ((vuint16)0xFFFFU) /*!< exact match */
#define C_MOAMRLO_OPEN       ((vuint16)0x0000U) /*!< all match */

#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_DECODE_DLI",488 /* MD_Can_17.4 */
#endif

#if !defined( kCanISRPrio_0 ) /* compatibility for 1 channel exception */ /* COV_CAN_COMPATIBILITY */
# if defined( kCanISRPrio )   /* old expresson used by CANGen for single channel system */ /* COV_CAN_COMPATIBILITY */
# define kCanISRPrio_0 kCanISRPrio
# endif
#endif
#if !defined( kCanISRGroup_0 ) /* compatibility for 1 channel exception */ /* COV_CAN_COMPATIBILITY */
# if defined( kCanISRGroup )   /* old expresson used by CANGen for single channel system */ /* COV_CAN_COMPATIBILITY */
# define kCanISRGroup_0 kCanISRGroup
# endif
#endif
/* define unused node-priorities (fill table) */
#if !defined( kCanISRPrio_0 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_0 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_1 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_1 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_2 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_2 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_3 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_3 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_4 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_4 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_5 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_5 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_6 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_6 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_7 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_7 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_8 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_8 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_9 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_9 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_10 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_10 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_11 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_11 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_12 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_12 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_13 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_13 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_14 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_14 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRPrio_15 ) /* COV_CAN_kCanISRPrio */
# define kCanISRPrio_15 0x00  /* unused node - no prio available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_0 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_0 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_1 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_1 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_2 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_2 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_3 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_3 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_4 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_4 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_5 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_5 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_6 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_6 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_7 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_7 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_8 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_8 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_9 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_9 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_10 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_10 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_11 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_11 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_12 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_12 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_13 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_13 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_14 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_14 0x00  /* unused node - no group available (first is always available - see above) */
#endif
#if !defined( kCanISRGroup_15 ) /* COV_CAN_kCanISRPrio */
# define kCanISRGroup_15 0x00  /* unused node - no group available (first is always available - see above) */
#endif

/* no compiler abstraction here pointers are always 32 bit and cast does not work for Tasking compiler */
#define CANLL_SRC_OFFSET     (15)
#define CANLL_TRUE           ((vuint8)0x01)
#define CANLL_FALSE          ((vuint8)0x00)

/* attention for Workaround TC.21 the Prio must be higher than for dummy */
/* for Workaround TC.23 Prio have to be equal over all channel and objects */
#define C_MOARHI_PRIO_DUMMY  ((vuint16)0x4000)
/* may cause problems Errata TC.23 because of Tx filtering */
/* general */

#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_SRC_PTR",0303,3372 /* MD_Can_0303_HWaccess, MD_Can_3372_LL_SrcOffset */
#endif
#if defined ( kCanSRCAdr ) /* Aurix: extern SRC (other layout used) */ /* COV_CAN_AURIX_DERIVATIVE */
# if (CAN_SAFE_BSW == STD_ON)
# define CAN_SRC_PTR(ch)      ( (V_DEF_P2VAR_PARA(volatile, vuint32, VAR_NOINIT, INT_CTRL)) (kCanSRCAdr) )[(Can_GetSrcNum(ch) & 0x0F)] /* SBSW_CAN_LL09 */
# else
# define CAN_SRC_PTR(ch)      ( (V_DEF_P2VAR_PARA(volatile, vuint32, VAR_NOINIT, INT_CTRL)) (kCanSRCAdr) )[Can_GetSrcNum(ch)]
# endif  
# define CAN_SRC_PTR_RAM(ch)  ( (V_DEF_P2VAR_PARA(volatile, vuint32, VAR_NOINIT, INT_CTRL)) (kCanSRCAdr) )[CanSrcNum_Ram[(ch)]]
# define C_ICR_IE_MASK        (0x00000400UL)
# define C_ICR_CR_INIT        (0x02000400UL) /* clear pending and enable this service */
# define C_ICR_CLR_IPND       (0x02000000UL) /* clear pending request */
# define C_ICR_IPND           (0x01000000UL) /* pending mask */
#else
# define CAN_SRC_PTR(ch)      ( (CanChipMsgPtr) (kCanBaseAdr+ 0xC0) )[CANLL_SRC_OFFSET-Can_GetSrcNum(ch)]
# define CAN_SRC_PTR_RAM(ch)  ( (CanChipMsgPtr) (kCanBaseAdr+ 0xC0) )[CANLL_SRC_OFFSET-CanSrcNum_Ram[(ch)]]
# define C_ICR_IE_MASK        (0x00001000UL)
# define C_ICR_CR_INIT        (0x00005000UL) /* clear pending and enable this service */
# define C_ICR_CLR_IPND       (0x00004000UL) /* clear pending request */
# define C_ICR_IPND           (0x00002000UL) /* pending mask */
#endif

#define C_PAN_BUSY           ((vuint16)0x0100)
#define C_PAN_ALLOC_TO_LIST  ((vuint16)0x0002)
#define C_PAN_RESET_LIST     ((vuint16)0x0001)

#define C_CLC_IS_DISABLE     ((vuint16)0x0002)
#define C_CLC_DISABLE        ((vuint16)0x0001)
#define C_CLC_START          ((vuint16)0x0008)

#define C_MCR_INIT_CLOCK     ((vuint16)0x0000) /* TC1:use fclc  TC2:start Init */
#define C_MCR_CLOCK_MASK     ((vuint16)0x000F)

#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_GET_MAILBOX_ADDRESS",0303 /* MD_Can_0303_HWaccess */
#endif
#if (CAN_SAFE_BSW == STD_ON) || defined C_ENABLE_MULTIPLE_CELLS
# define CAN_GET_MAILBOX_ADDRESS(x) (pCanCellMailbox=(CanMsgObjStructPtr)&canCellPtr->Obj[(uint8)CAN_HWOBJ_SAFE_MASK(x)])
#else
# define CAN_GET_MAILBOX_ADDRESS(x) (pCanCellMailbox=(CanMsgObjStructPtr)&canCellPtr->Obj[(x)])
#endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
/* CAN_HL_TX_OFFSET_HW_TO_LOG(ch) not supported for LL use CanHL_GetTxHwToLogHandle or CanHL_GetTxLogToHwHandle instead */
#else
# define CAN_HL_TX_OFFSET_HW_TO_LOG(ch) (Can_GetTxOffsetHwToLog(ch)) /* used in LL */
#endif

/* for LL compatibility */
#if defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* COV_CAN_GEN_HW_START_STOP_IDX */
# define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     (Can_GetTxBasicHwStart(hwch))
#  define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxFullHwStart(hwch))
# define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHwStart(hwch))
# define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   (Can_GetUnusedHwStart(hwch))
# define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHwStart(hwch))
# define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHwStart(hwch))
#  define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxBasicHwStop(hwch))
# define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHwStop(hwch))
# define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    (Can_GetUnusedHwStop(hwch))
# define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHwStop(hwch))
# define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHwStop(hwch))
#else
# define CAN_ASR_HW_TX_NORMAL_INDEX(hwch)     (Can_GetHwHandle(Can_GetTxBasicHandleStart(hwch)))
#  define CAN_ASR_HW_TX_STARTINDEX(hwch)      (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch))
# if !defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
/* >= R19 --> size for each Object may differ for MULTIPLEXED_TRANSMISSION (please use ENABLE_GEN_HW_START_STOP_IDX instead) */
#  define CAN_ASR_HW_TX_STOPINDEX(hwch)       (CAN_ASR_HW_TX_STARTINDEX(hwch) + (Can_GetTxBasicHandleMax(hwch) * CAN_MULTIPLEXED_TX_MAX) + Can_GetTxFullHandleMax(hwch))
# endif
#  define CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetHwHandle(Can_GetTxFullHandleStart(hwch)))
#  define CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)   (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch) + Can_GetTxFullHandleMax(hwch))

# define CAN_ASR_HW_UNUSED_STARTINDEX(hwch)   (Can_GetHwHandle(Can_GetUnusedHandleStart(hwch)))
# define CAN_ASR_HW_UNUSED_STOPINDEX(hwch)   ((Can_GetUnusedHandleStart(hwch) != Can_GetUnusedHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetUnusedHandleStop(hwch)-1)) + Can_GetDLC_FIFO((Can_GetUnusedHandleStop(hwch)-1))) : (Can_GetHwHandle(Can_GetUnusedHandleStart(hwch))))

#  define CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetHwHandle(Can_GetRxFullHandleStart(hwch)))
#  define CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)   ((Can_GetRxFullHandleStart(hwch) != Can_GetRxFullHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetRxFullHandleStop(hwch)-1))+1) : (Can_GetHwHandle(Can_GetRxFullHandleStart(hwch))))

#  define CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetHwHandle(Can_GetRxBasicHandleStart(hwch)))
#  define CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)  ((Can_GetRxBasicHandleStart(hwch) != Can_GetRxBasicHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetRxBasicHandleStop(hwch)-1)) + Can_GetDLC_FIFO((Can_GetRxBasicHandleStop(hwch)-1))) : \
  (Can_GetHwHandle(Can_GetRxBasicHandleStart(hwch))))
# if !defined(CAN_HL_HW_TX_NORMAL_INDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     CAN_ASR_HW_TX_NORMAL_INDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_FULL_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_FULL_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_STARTINDEX(hwch)       CAN_ASR_HW_TX_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_STOPINDEX(hwch)        CAN_ASR_HW_TX_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_UNUSED_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   CAN_ASR_HW_UNUSED_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_UNUSED_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    CAN_ASR_HW_UNUSED_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_FULL_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_FULL_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_BASIC_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_BASIC_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)
# endif
#endif
/* may be used by LL to free TX mailbox between CanLL_TxBegin and CanLL_TxEnd (only necessary when not using CanLL_TxStart return value) */
#define CAN_FREE_TX_OBJECT(obj) Can_SetActiveSendState(obj, CAN_FREE_OBJ)

#if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
/* define first index to array CanHwObjIndivPolling[][] */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
#   define CAN_HWOBJINDIVPOLLING_INDEX0                    (V_ACTIVE_IDENTITY_LOG)
#  else
#   define CAN_HWOBJINDIVPOLLING_INDEX0                    (0)
#  endif
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
# if !defined(CAN_RAM_CHECK_MAILBOX_RESULT) /* May be defined by test suite to stimulate RAM_CHECK failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((hwObjHandle))
#  else
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((ch), (hwObjHandle))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_FINISHED_CTP) /* May be defined by test suite to check RAM_CHECK finished / executed */
#  define CAN_RAM_CHECK_FINISHED_CTP(ch)
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
# if !defined(CAN_RAM_CHECK_BEGIN_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch) CanLL_InitBeginIsRegisterCorrupt()
#  else
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch) CanLL_InitBeginIsRegisterCorrupt((ch))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_END_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_END_REG_RESULT(ch) CanLL_InitEndIsRegisterCorrupt()
#  else
#   define CAN_RAM_CHECK_END_REG_RESULT(ch) CanLL_InitEndIsRegisterCorrupt((ch))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_READ_BACK_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  define CAN_RAM_CHECK_READ_BACK_RESULT(ch)
# endif
#endif

#define CanHL_IsStart(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_START) == CAN_STATUS_START)
#define CanHL_IsSleep(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP)
#define CanHL_IsStop(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_STOP) == CAN_STATUS_STOP)
#define CanHL_IsBusOff(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_BUSOFF) == CAN_STATUS_BUSOFF)
#define CanHL_IsControllerInit(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_INIT) == CAN_STATUS_INIT)

#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
# define cantVIdentityMsk uint16
# define CanSetActiveIdentity(identityLog) \
{ \
  canActiveIdentityLog = (identityLog); \
  canActiveIdentityMsk = (cantVIdentityMsk) (((cantVIdentityMsk) 1) << (identityLog)); \
}
# if defined V_ACTIVE_IDENTITY_MSK
#  undef V_ACTIVE_IDENTITY_MSK  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_MSK                canActiveIdentityMsk
# if defined V_ACTIVE_IDENTITY_LOG
#  undef V_ACTIVE_IDENTITY_LOG  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_LOG                canActiveIdentityLog
#endif

#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
# define PDUINFO_PTR PduInfoPtr_var
#else
# define PDUINFO_PTR PduInfo
#endif
#if defined(C_ENABLE_CAN_FD_USED)
# define PDUINFO_ID  pduInfo_var_id
# define PDUINFO_DLC pduInfo_var_dlc
#else
# define PDUINFO_ID  PDUINFO_PTR->id
# define PDUINFO_DLC PDUINFO_PTR->length
#endif

#if !defined(CAN_APPLICATION_DEM_REPORTERROR) /* COV_CAN_COMPATIBILITY */
# define CAN_APPLICATION_DEM_REPORTERROR STD_OFF
#endif
#if (CAN_APPLICATION_DEM_REPORTERROR == STD_OFF) /* COV_CAN_USER_CONFIG */
# define Can_Dem_ReportError(EventId) ( (void) Dem_ReportErrorStatus((EventId), DEM_EVENT_STATUS_FAILED) )
#endif

#if defined(C_ENABLE_CAN_FD_USED) /* also for BRS because DLC may be bigger than 8 and will be checked by CanIf */
# define CAN_DECODE_DLI(dlc) (Can_DliToBytesMap[((uint8)(dlc)) & ((uint8)0xFu)])
# define CAN_ENCODE_DLI(length) (((uint8)Can_BytesToDliMap[(length)]) & ((uint8)0x0Fu))
#else
# define CAN_DECODE_DLI(dlc) (dlc)
# define CAN_ENCODE_DLI(length) (length)
#endif
#if defined(C_ENABLE_CAN_FD_FULL)
# define CAN_MAX_RX_DATALEN         Can_GetMaxRxDataLen()
# define CAN_MAX_TX_DATALEN         Can_GetMaxTxDataLen()
# define CAN_MAX_DATALEN_OBJ(Index) Can_GetMailboxDataLen(Index)
#else
# define CAN_MAX_RX_DATALEN         8u
# define CAN_MAX_TX_DATALEN         8u
# define CAN_MAX_DATALEN_OBJ(Index) 8u
#endif
#define CanHL_IsFdMessage(id) (((id) & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK) /* used for LL */ /* \trace SPEC-60432, SPEC-50586 */
#define CanHL_IsFdTxBrs(ch)   (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(ch)) == CAN_FD_RXTX) /* used for LL */ /* \trace SPEC-60432, SPEC-50586 */

#if (CAN_MICROSAR_VERSION == CAN_MSR403) /* COV_CAN_MICROSAR_VERSION */
# define CAN_MULTIPLEXED_TX_MAX_OBJ(hth) ((Can_GetMailboxType(hth) == CAN_TX_BASICCAN_MUX_TYPE) ? CAN_MULTIPLEXED_TX_MAX : 1)
#else
# define CAN_MULTIPLEXED_TX_MAX_OBJ(hth) CAN_MULTIPLEXED_TX_MAX
#endif

#if (CAN_SAFE_BSW == STD_ON)
#define CAN_NODE_NUM (Can_GetNodeNum(canHwChannel) & 0x07) /* ensure adress range */
#else
#define CAN_NODE_NUM Can_GetNodeNum(canHwChannel)
#endif

#if defined(C_ENABLE_MULTIPLE_CELLS)
# if defined(C_ENABLE_MULTIPLE_DRIVERS)   /* COV_CAN_MULTIPLE_DRIVERS */
# error "The usage of multiple CAN cells in conjunction with Multiple Driver feature is not allowed"
# endif
#endif

#if ( CAN_PROTECTED_MODE == STD_ON ) /* get by base */  /* COV_CAN_COMPATIBILITY */
#  define C_ENABLE_PROTECTED_MODE /* may be organified */
#endif

#if defined(MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_SFR_PROTECT_RESET16",0277 /* MD_Can_0277_negation */
#endif

#if defined( C_ENABLE_USE_VSTDLIB )           /* COV_CAN_VSTDLIB_USE */
#  define CAN_SFR_PROTECT_OFF()    VStdUnlockInit()
#  define CAN_SFR_PROTECT_ON()     VStdLockInit()
#  if defined( C_ENABLE_NESTED_INTERRUPTS )   /* COV_CAN_VSTDLIB_USE */
#   define CAN_ENABLE_GLOBAL_ISR() VStdEnableInt()
#  endif
#elif defined( C_ENABLE_PROTECTED_MODE ) && !defined (kCanSRCAdr) /* COV_CAN_AURIX_DERIVATIVE */
# define CAN_SFR_PROTECT_OFF()               osClearENDINIT()
# define CAN_SFR_PROTECT_ON()                osSetENDINIT()
# if defined( C_ENABLE_NESTED_INTERRUPTS ) 
#  error "Do not configure 'Support Nested Interrupts' in your CAN Driver this should be done by OS in Protected Systems"
# endif
#else /* part of Appl code (default) */
# define CAN_SFR_PROTECT_OFF()    Appl_UnlockEndinit()
# define CAN_SFR_PROTECT_ON()     Appl_LockEndinit()
# if defined( C_ENABLE_NESTED_INTERRUPTS ) 
#  define CAN_ENABLE_GLOBAL_ISR() Appl_EnableInt()
# endif
#endif
#if defined(C_ENABLE_PROTECTED_MODE)
# if defined(C_ENABLE_MULTIPLE_CELLS)
#  define CAN_SFR_PROTECT_WRITE32_PER_CELL(reg, value, cancell) osWritePeripheral32((((cancell) == CAN_MULTICAN)?CAN_PROTECTED_AREA_ENDINIT:CAN_PROTECTED_AREA_ENDINIT_MULTICANR), (vuint32)(&(reg)), value)
#  define CAN_PROTECTED_AREA_ENDINIT_COMMON ((Can_GetCellInfoIdxOfCell(channel) == CAN_MULTICAN)?CAN_PROTECTED_AREA_ENDINIT:CAN_PROTECTED_AREA_ENDINIT_MULTICANR)
#  define CAN_PROTECTED_AREA_ENDINIT_CHANNEL (((canll_ch) == CAN_MULTICAN)?CAN_PROTECTED_AREA_ENDINIT:CAN_PROTECTED_AREA_ENDINIT_MULTICANR)
# else
#  define CAN_PROTECTED_AREA_ENDINIT_COMMON CAN_PROTECTED_AREA_ENDINIT
#  define CAN_PROTECTED_AREA_ENDINIT_CHANNEL CAN_PROTECTED_AREA_ENDINIT
# endif
# define CAN_SFR_PROTECT_WRITE32(reg, value) osWritePeripheral32(CAN_PROTECTED_AREA_ENDINIT_COMMON, (vuint32)(&(reg)), value)
# define CAN_SFR_PROTECT_WRITE16(reg, value) osWritePeripheral16(CAN_PROTECTED_AREA_ENDINIT_CHANNEL, (vuint32)(&(reg)), value)
# define CAN_SFR_PROTECT_SET16(reg, bits)    osModifyPeripheral16(CAN_PROTECTED_AREA_ENDINIT_COMMON, (vuint32)(&(reg)), (vuint16)0xFFFFu, (bits))
# define CAN_SFR_PROTECT_RESET16(reg, bits)  osModifyPeripheral16(CAN_PROTECTED_AREA_ENDINIT_COMMON, (vuint32)(&(reg)), (vuint16)~(bits), (vuint16)0x0000)
# if defined ( kCanSRCAdr ) /* Aurix use external interrupt controller */ /* COV_CAN_AURIX_DERIVATIVE */
#  define CAN_SRC_PROTECT_WRITE(reg, value)  osWritePeripheral32(CAN_PROTECTED_AREA_SRC, (vuint32)(&(reg)), value)
#  define CAN_SRC_PROTECT_SET(reg, bits)     osModifyPeripheral32(CAN_PROTECTED_AREA_SRC, (vuint32)(&(reg)), (vuint32)0xFFFFFFFFUL, (bits))
#  define CAN_SRC_PROTECT_RESET(reg, bits)   osModifyPeripheral32(CAN_PROTECTED_AREA_SRC, (vuint32)(&(reg)), (vuint32)~(bits), (vuint32)0x00000000UL)
# else /* TriCore use CAN cell internal interrupt controller */
#  define CAN_SRC_PROTECT_WRITE(reg, value)  (reg) = (value);
#  define CAN_SRC_PROTECT_SET(reg, bits)     (reg) |= (bits);
#  define CAN_SRC_PROTECT_RESET(reg, bits)   (reg) &= ((vuint32)~(bits));
# endif
#else
# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SFR_PROTECT_WRITE32",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SFR_PROTECT_WRITE16",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SFR_PROTECT_SET16",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SFR_PROTECT_RESET16",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SRC_PROTECT_WRITE",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SRC_PROTECT_SET",0303 /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CAN_SRC_PROTECT_RESET",0303 /* MD_Can_0303_HWaccess */
# endif
# define CAN_SFR_PROTECT_WRITE32(reg, value) (reg) = (value);
# define CAN_SFR_PROTECT_WRITE16(reg, value) (reg) = (value);
# define CAN_SFR_PROTECT_SET16(reg, bits)    (reg) |= (bits);
# define CAN_SFR_PROTECT_RESET16(reg, bits)  (reg) &= ((vuint16)~(bits));
# define CAN_SRC_PROTECT_WRITE(reg, value)   (reg) = (value);
# define CAN_SRC_PROTECT_SET(reg, bits)      (reg) |= (bits);
# define CAN_SRC_PROTECT_RESET(reg, bits)    (reg) &= ((vuint32)~(bits));
#endif

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsHWObjFree",0303 /* MD_Can_0303_HWaccess */
# endif
#  define CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ) \
         ((canCellPtr->Obj[(vuint8)(txObjHandle)].MoCtrL & C_MOCTR_TXREQ) == (vuint16)0x0000u)
# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY)  (kCanFalse != kCanFalse)  /* avoid misra warning */

#define CanLL_HwIsStop( CAN_HW_CHANNEL_CANPARA_ONLY ) \
    (Can_GetHaltOfControllerData(canHwChannel)==CANLL_TRUE)

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",0303 /* MD_Can_0303_HWaccess */
# endif
# define CanLL_HwIsBusOff( CAN_HW_CHANNEL_CANPARA_ONLY )  \
        (((canCellPtr->Node[CAN_NODE_NUM].NSR & C_NSR_BOFF)==C_NSR_BOFF) || \
         ((!CanLL_HwIsStop(canHwChannel)) && ((canCellPtr->Node[CAN_NODE_NUM].NCR & C_NCR_INIT)==C_NCR_INIT)))

#if defined( C_ENABLE_EXTENDED_STATUS )
#  if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#   pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",0303 /* MD_Can_0303_HWaccess */
#  endif
#  define CanLL_HwIsPassive( CAN_HW_CHANNEL_CANPARA_ONLY )  \
         ((canCellPtr->Node[CAN_NODE_NUM].NECnt_Tec > 127) || (canCellPtr->Node[CAN_NODE_NUM].NECnt_Rec > 127))

#  if defined(MISRA_CHECK) /* COV_CAN_MISRA */
#   pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",0303 /* MD_Can_0303_HWaccess */
#  endif
#  define CanLL_HwIsWarning( CAN_HW_CHANNEL_CANPARA_ONLY ) \
         ((canCellPtr->Node[CAN_NODE_NUM].NSR & C_NSR_EWRN)==C_NSR_EWRN)
#endif /* C_ENABLE_EXTENDED_STATUS */

#if defined(C_ENABLE_HWBUFFER)
/* temporary buffer for Rx data in one of last CAN-cell mailboxes */
# define TmpRxMailbox      canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK((CAN_MAX_NUM_MSGOBJ-1)-CAN_NODE_NUM)]
# define pTmpRxMailboxMsg  ((CanChipMsgPtr)&canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK(CAN_MAX_NUM_MSGOBJ-1-CAN_NODE_NUM)])
# define pTmpRxMailboxData ((CanChipDataPtr) (kCanBaseAdr + 0x200 + CAN_MAX_NODE*0x100 + ((CAN_MAX_NUM_MSGOBJ-1)-CAN_NODE_NUM)*32 + 0x10)) /* ESCAN00040099 */
#else
/* temporary buffer for Rx data in RAM */
# define TmpRxMailbox      Can_GetTmpRxMsgMailbox(canHwChannel)
# define pTmpRxMailboxMsg  ((CanChipMsgPtr)    &Can_GetTmpRxMsgMailbox(canHwChannel))
# define pTmpRxMailboxData ((CanChipDataPtr)   &Can_GetTmpRxMsgMailbox(canHwChannel).MoDR[0])
#endif

#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
# define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(channel, loop)
# define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(channel, loop)
# define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(channel, loop)
#else
# define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(loop)
# define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(loop)
# define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(loop)
#endif

/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* BR:012 */
V_DEF_CONST(V_NONE, uint8, CONST) Can_MainVersion         = (uint8)CAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_SubVersion          = (uint8)CAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_ReleaseVersion      = (uint8)CAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */

#if defined(C_ENABLE_CAN_FD_USED)
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_DliToBytesMap[16] = /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0,  1,  2,  3,
  4,  5,  6,  7,
  8, 12, 16, 20,
 24, 32, 48, 64
};
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_BytesToDliMap[65] = /* PRQA S 3218 */ /* MD_Can_3218 */
{
/* 00..07 */  0,  1,  2,  3,  4,  5,  6,  7,
/* 08..15 */  8,  9,  9,  9,  9, 10, 10, 10,
/* 16..23 */ 10, 11, 11, 11, 11, 12, 12, 12,
/* 24..31 */ 12, 13, 13, 13, 13, 13, 13, 13,
/* 32..39 */ 13, 14, 14, 14, 14, 14, 14, 14,
/* 40..47 */ 14, 14, 14, 14, 14, 14, 14, 14,
/* 48..55 */ 14, 15, 15, 15, 15, 15, 15, 15,
/* 56..63 */ 15, 15, 15, 15, 15, 15, 15, 15,
/* 64     */ 15
};
#endif

/* Global constants with CAN driver main and subversion */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* ROM CATEGORY 4 START */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) CanMemCheckValues2x32bit[3][2] =   /* PRQA S 3218 */ /* MD_Can_3218 */
{
  { 0xAAAAAAAAUL, 0xAAAAAAAAUL },
  { 0x55555555UL, 0x55555555UL },
  { 0x00000000UL, 0x00000000UL }
};
V_DEF_CONST(CAN_STATIC, vuint8, CONST) CanMemCheckValues8bit[3] =      /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAU, 0x55U, 0x00U
};
V_DEF_CONST(CAN_STATIC, vuint16, CONST) CanMemCheckValues16bit[3] =    /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAU, 0x5555U, 0x0000U
};
# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
V_DEF_CONST(CAN_STATIC, vuint32, CONST) CanMemCheckValues32bit[3] =    /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAAAAAUL, 0x55555555UL, 0x00000000UL
};
/* ROM CATEGORY 4 END */
# endif
#endif

#define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
/*! bitmask of the active channels in the current identity */
V_DEF_VAR(V_NONE, uint16, VAR_NOINIT) canActiveIdentityMsk; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
/*! the activated identity handle */
V_DEF_VAR(V_NONE, uint8, VAR_NOINIT)  canActiveIdentityLog; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
#endif

# if !defined(C_ENABLE_MULTIPLE_DRIVERS) /* COV_CAN_MULTIPLE_DRIVERS */
V_DEF_VAR(V_NONE, vuint16, VAR_NOINIT) canLLTempRead; /* avoid compiler optimization by global declaration */ /* PRQA S 3408,1514 */ /* MD_Can_Asr_3408, MD_Can_3218 */
# endif

/***************************************************************************************/
/* local data definitions   (need also INFIX because STATIC may be defined to nothing) */
/***************************************************************************************/
/* \trace SPEC-1585 */
/*! Semaphore to block reentrancy for Can_MainFunction_Read() */
V_DEF_VAR(CAN_STATIC, Can_ReturnType, VAR_NOINIT) canRxTaskActive;
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
/*! Save API context in witch the DET is called (Init, InitController, SetControllerMode, disable/enableControlerInterrupts) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_NOINIT) canApiContext;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_RX_QUEUE)
V_DEF_VAR(CAN_STATIC, uint16, VAR_NOINIT) canRxQueueMaxDataSize; /* PRQA S 3218 */ /* MD_Can_3218 */
#endif

V_DEF_VAR(CAN_STATIC, uint16, VAR_NOINIT) CanNumberOfMaxBasicCAN;

/* Just for Debugging */
# if defined (C_ENABLE_MULTIPLE_CELLS)
V_DEF_VAR(CAN_STATIC volatile, tCanCellStructPtr, VAR_NOINIT) canCellDbgPtr0;  /* PRQA S 3218 */ /* MD_Can_3218_LL_canCellPtr */
V_DEF_VAR(CAN_STATIC volatile, tCanCellStructPtr, VAR_NOINIT) canCellDbgPtr1;  /* PRQA S 3218 */ /* MD_Can_3218_LL_canCellPtr */
# else
V_DEF_VAR(CAN_STATIC volatile, tCanCellStructPtr, VAR_NOINIT) canCellDbgPtr;  /* PRQA S 3218 */ /* MD_Can_3218_LL_canCellPtr */
# endif

/***************************************************************************/
/*  Safe Check LL                                                            */
/***************************************************************************/
#if !defined(CAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_SAFE_BSW   STD_OFF
#else
# if (CAN_SAFE_BSW == STD_ON)
#  if defined(C_ENABLE_MULTIPLE_DRIVERS)                || \
     (CAN_RX_HW_FIFO_FULL_NOTIFICATION == STD_ON)       || \
     !defined(CanClockDividor)                          || \
     !defined(kCanMCRValue)                             || \
     !defined(C_ENABLE_TX_PRIO_BYID)                    || \
     defined(C_DISABLE_ISR_PROTOTYPE)                   || \
     !defined(kCanSRCAdr)
#   error "Unsupported Feature activated for SafeBSW"
#  endif
#  if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
#   if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
#    define CAN_USE_PHYSTOLOG_MAPPING
#   endif
#  else
#   if defined(C_ENABLE_MULTI_ECU_CONFIG)
#    define CAN_USE_PHYSTOLOG_MAPPING
#   endif
#  endif
# endif
#endif

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ! Mark module to be initialized (used to check double/none initialization) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_INIT) canConfigInitFlag = CAN_STATUS_UNINIT;
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* not static because of debug/test usage */
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*! Pointer to the current configuration */
V_DEF_P2CONST (V_NONE, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */ /* PRQA S 3408,1504 */ /* MD_Can_3408_extLinkage */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#else
# define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* PRQA S 3408,3218,1514 */ /* MD_Can_3408_extLinkage,MD_Can_3218 */
# else
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = &CanConfig; /* PRQA S 3408,3218,1514 */ /* MD_Can_3408_extLinkage,MD_Can_3218 */
# endif
# define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/***************************************************************************/
/*  Safe Check                                                             */
/***************************************************************************/
#if !defined(CAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_SAFE_BSW   STD_OFF
#else
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) || \
     !defined(CAN_DEV_ERROR_DETECT) || \
     defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) || \
     !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) || \
     defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) || \
     defined(C_ENABLE_PARTIAL_NETWORK) || \
     defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) || \
     defined(CAN_ENABLE_BUSOFF_SUPPORT_API) || \
     defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) || \
     (CAN_EMULATE_SLEEP != STD_ON) || \
     !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) || \
     (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) || \
     !defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* COV_CAN_SAFE_BSW_EXCLUSION */
#   error "Unsupported Feature activated for SafeBSW"
#  endif
# endif
#endif

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
# if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_WAKEUP_SUPPORT need activated CAN_SLEEP_SUPPORT"
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
# if (CAN_LOOP_MAX == 0)
#  error "CAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
#if !defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG TX */
# if (CAN_MULTI_ECU_CONFIG == STD_ON)
#  error "C_ENABLE_MULTI_ECU_CONFIG organified but generated like supported"
# endif
#endif
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if (CAN_DEV_ERROR_DETECT == STD_OFF)
#   error "CAN_DEV_TIMEOUT_DETECT is switched on but CAN_DEV_ERROR_DETECT is not"
#  endif
# endif
#endif
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
#  error "No need to switch on partial Network for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
#  error "BUSOFF_SUPPORT_API not supported for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) /* COV_CAN_EXTENDED_STATE_MACHINE */
#  error "CAN_EXTENDED_STATE_MACHINE not supported for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  error "CAN_DEV_TIMEOUT_DETECT not supported for MicroSar in version 4.x"
# endif
#endif
#if (CAN_MIRROR_MODE == STD_ON) && (!defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) || (CAN_GENERIC_PRECOPY == STD_OFF))
# error "CAN_MIRROR_MODE need CAN_GENERIC_CONFIRMATION with CAN_API2 and CAN_GENERIC_PRECOPY as STD_ON"
#endif
#if !defined(CAN_MULTIPLEXED_TX_MAX)
# error "CAN_MULTIPLEXED_TX_MAX is not generated"
#endif
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON) /* COV_CAN_MULTIPLEXED_TRANSMISSION */
# if (CAN_MULTIPLEXED_TX_MAX != 3) /* CM_CAN_HL19 */
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#else
# if (CAN_MULTIPLEXED_TX_MAX != 1) /* CM_CAN_HL19 */
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#endif
#if (CAN_RAM_CHECK != CAN_NONE)
# if defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) /* COV_CAN_EXTENDED_STATE_MACHINE */
# error "Feature RAM_CHECK is not available in combination with EXTENDED_STATE_MACHINE"
/* no STOP mode called after WAKEUP but need to run RAM check */
# endif
#endif
#if (CAN_MULTIPLE_BASICCAN_TX == STD_ON)
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* cancellation does not work in CanHL_WritePrepareCancelTx for multiple BasicCAN messages, and is not useful for FIFO queue in CanIf (normally combined with multiple BCAN)*/
# error "CAN_MULTIPLE_BASICCAN_TX and CAN_HW_TRANSMIT_CANCELLATION are STD_ON but this combination is not supported"
# endif
#endif

#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
#  error "Extended RamCheck is only available for MICROSAR403"
# endif
#endif

/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_HW_LOOP_TIMER) /* always used for sync mode */ /* COV_CAN_MICROSAR_VERSION */

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
/* TickRefType is pointer to TickType but unknown here */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanHL_ApplCanTimerStart",432
#  pragma PRQA_MACRO_MESSAGES_OFF "CanHL_ApplCanTimerEnd",432
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( timerIdx );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( timerIdx );
# else
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( channel, (timerIdx) );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( channel, (timerIdx) );
# endif
# define CanHL_ApplCanTimerLoop( timerIdx )   if (ApplCanTimerLoop( CAN_CHANNEL_CANPARA_FIRST (timerIdx) ) != CAN_OK) \
                                              { \
                                                break; \
                                              }

# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/* Internal handling of HW loops (like AutoSar) - otherwise ApplCanTimer... is defined an implemented by Application */
/****************************************************************************
| NAME:             ApplCanTimerStart
****************************************************************************/
/* Used as macro to save runtime and code */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/* \trace SPEC-1640 */
#    define ApplCanTimerStart(source)     ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout(0,(source))))
#   else
#    define ApplCanTimerStart(source)     (Can_GetCanLoopTimeout(0,(source)) = 0)
#   endif
#  else
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
#    define ApplCanTimerStart(ch, source) ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout((ch),(source))))
#   else
#    define ApplCanTimerStart(ch, source) (Can_GetCanLoopTimeout((ch),(source)) = 0)
#   endif
#  endif
/****************************************************************************
| NAME:             ApplCanTimerLoop
****************************************************************************/
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
 */
/*
|<DataModelStart>| ApplCanTimerLoop
Relation_Context:
OneChOpt, HardwareLoop, HardwareCancelByAppl
Relation:
DevErrorDetect, OneChOpt
HardwareLoop
PnEnable
CanDevTimeoutDetect
ProdErrorDetect
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop( CAN_CHANNEL_CANTYPE_FIRST uint8 source ) /* PRQA S 3219 */ /* MD_Can_Asr_3219 */
{ /* \trace SPEC-3952 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  uint8 errorId;
  uint8 apiId;
  errorId = CAN_E_NO_ERROR;
  apiId = CAN_HW_ACCESS_ID;
  retval = CAN_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and source is valid (no INIT check because may be used inside power on INIT) */
  if (source >= CAN_LOOP_AMOUNT) /* CM_CAN_HL22 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
  /* #100 In case of MSR4: */
    TickType elapsedTime;
    TickType startTime;
    /* #110 Calculate the elapsed since time the start of this hardware loop (identified by parameter source). */
    /* Get start time (set by ApplCanTimerStart - temporary variable because GetElapsedValue modify original data */
    startTime = Can_GetCanLoopTimeout(channel,source);
    /* Get elapsed time - from start time to now */
    /* #120 Throw DET error when GetElapsedValue() failed */
    if ( GetElapsedValue( CAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != (StatusType)E_OK ) /* PRQA S 432 */ /* TickRefType is pointer to TickType but unknown here */ /* SBSW_CAN_HL37 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_TIMEOUT_DET;
    }
    else
    {
      /* #130 Check if time out occurs for HW loop checks (none mode transition) \trace SPEC-1594 */
      if ( (TickType)CAN_OS_TICK2MS( elapsedTime ) < (TickType)CAN_TIMEOUT_DURATION ) /* COV_CAN_HARDWARE_FAILURE */
      { /* no time out occur return OK */
        retval = CAN_OK;
      }
#   if defined(C_ENABLE_HW_LOOP_TIMER) /* COV_CAN_MICROSAR_VERSION */
      else
      { /* Mode Change synchronous & HW loop check */
        /* #140 Throw DET error and set hardware cancellation flag */
        if (source < CAN_LOOP_MAX) /* COV_CAN_HARDWARE_FAILURE */
        { 
          errorId = CAN_E_TIMEOUT_DET;
          Can_SetIsHardwareCanceled(channel,TRUE); /* SBSW_CAN_HL14 */
        }
      }
#   endif
    }
    CAN_DUMMY_STATEMENT(startTime); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  else
  /* #200 In case of MSR3: */
    /* #210 Increment HW loop counter */
    Can_GetCanLoopTimeout(channel,source)++; /* SBSW_CAN_HL15 */
    /* #220 Check if time out occurs */
    if ( Can_GetCanLoopTimeout(channel,source) >= CAN_TIMEOUT_DURATION ) /* \trace SPEC-3953 */
    {
#   if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
      /* #230 Do not throw error when partial network is active for this controller */
      if ( Can_IsTimeoutCall(channel) )
#   endif
      { /* #240 Throw DET or DEM error and set hardware cancellation flag */
#   if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
        apiId = canApiContext;
        errorId = CAN_E_TIMEOUT_DET;
#   else
#    if (CAN_PROD_ERROR_DETECT == STD_ON) /* \trace SPEC-1398 */ /* is explicit ignored due to vector general requirements */
        Can_Dem_ReportError(canDemErrorTimeout); /* \trace SPEC-1726, SPEC-1725, SPEC-3846, SPEC-3824, SPEC-3928 */
#    endif
#   endif
        Can_SetIsHardwareCanceled(channel,TRUE); /* SBSW_CAN_HL14 */
      }
    }
    else
    {
  /* #300 no time out occur return OK */
      retval = CAN_OK;
    }
#  endif /* CAN_MSR3/4 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)  
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(apiId, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(apiId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/****************************************************************************
| NAME:             ApplCanTimerEnd
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define ApplCanTimerEnd ApplCanTimerStart
# endif /* (CAN_HW_LOOP_SUPPORT_API == STD_OFF) */

#else /* C_ENABLE_HW_LOOP_TIMER */
/* no HW loop is used at all */
# define CanHL_ApplCanTimerStart( timerIdx )
# define CanHL_ApplCanTimerLoop( timerIdx )
# define CanHL_ApplCanTimerEnd( timerIdx )
#endif

/****************************************************************************
| NAME:             CanInit
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanInit
Relation_Context:
Relation:
OneChOpt
ChannelAmount
BusOffRecovery
HardwareLoop
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInit( CAN_CHANNEL_CANTYPE_FIRST uint8 initObject ) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  
  /* ----- Development Error Checks ------------------------------------- */
  /* parameter initObject is already checked by caller */
  /* parameter channel is already checked by caller */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Reinitialize the controller (Call fitting controller initialization function Can_InitController()) */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(initObject - (uint8)(Can_GetInitObjectStartIndex(channel))) & 0x03u))); /* SBSW_CAN_HL03 */
#else
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
    CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
    /* #110 Switch to START mode if BUSOFF handling is done by application */
    /* normally CanResetBusOffStart/STOP (and CanResetBusSleep) use this call so no other action is needed.
       But when application do this call the state has to be set to START here because it will not be done in SetControllerMode(). */
    { 
      (void)Can_SetControllerMode((uint8)channel, CAN_T_START);
    }
#endif
  }
}

/****************************************************************************
| NAME:             Can_CleanUpSendState
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CleanUpSendState
Relation_Context:
Relation:
OneChOpt
MultiplexedTx
CommonCan
IfTxBuffer
TxFullCANSupport
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) Can_CleanUpSendState( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle logTxObjHandle;
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  CanObjectHandle logTxObjHandleStop;
# endif
  Can_HwHandleType Htrh;
  /* ----- Implementation ----------------------------------------------- */
  /* parameter channel is already checked by caller */
  /* #10 set all BasicCAN TX Objects to state FREE to allow a new transmission */
  Htrh = Can_GetTxBasicHandleStart(canHwChannel);
# if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; Htrh < Can_GetTxBasicHandleStop(canHwChannel); Htrh++)
# endif
  {
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Htrh));
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    logTxObjHandleStop = logTxObjHandle + (Can_HwHandleType)CAN_MULTIPLEXED_TX_MAX_OBJ(Htrh); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    for (; logTxObjHandle < logTxObjHandleStop; logTxObjHandle++)
# endif
    {
      Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
    }
  }
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  /* #20 set all FullCAN TX Objects to state FREE to allow a new transmission */
  for (Htrh = Can_GetTxFullHandleStart(canHwChannel); Htrh < Can_GetTxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Htrh));
    Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */ 
  }
# endif
}

/****************************************************************************
| NAME:             CanHL_StartTransition
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_StartTransition
Relation_Context:
Relation:
OneChOpt
CommonCan
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StartTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  { /* #20 HW request transition (LL) \trace SPEC-1628 */
    /* activate node */
    {
      uint16 ncr_local = C_NCR_RESET;
      CanXC800GlobalInterruptDeclare
      CanXC800GlobalInterruptDisable();
    #if !defined( C_ENABLE_ERROR_POLLING )
      ncr_local |=  C_NCR_ErrIE;
    #endif
    #if defined( C_ENABLE_CAN_FD_USED ) 
      if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE )
      {
        ncr_local |= C_NCR_FDEN;
      }
    #endif
    #if defined(C_ENABLE_SILENT_MODE)
      if (Can_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
      {
        /* set node to silent mode (Analyzer Mode of MultiCAN) */
        ncr_local |=  C_NCR_CALM;
      }
    #endif
      CAN_SET_NCR_GLOBAL( CAN_NODE_NUM, ncr_local);  /* SBSW_CAN_LL01 */
      CanXC800GlobalInterruptRestore();
    }
    Can_SetHaltOfControllerData(canHwChannel, CANLL_FALSE); /* SBSW_CAN_LL02 */
    Can_SetBusOffNotifiedOfControllerData(canHwChannel, CANLL_FALSE); /* enable busoff detection after Init-flag is reset */ /* SBSW_CAN_LL02 */
  } /* loop canHwChannel */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #70 transition finished synchronous return OK and change internal state */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_START)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #80 allow reinitialization in notification */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* #90 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STARTED );
#endif
    retval = CAN_OK;
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_StopTransition
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_StopTransition
Relation_Context:
Relation:
OneChOpt
CommonCan
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StopTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #20 ESCAN00073272 need Can_InitController() (in case of HW failure) */
  if( (Can_GetLogStatus(channel) & (CAN_STATUS_STOP | CAN_STATUS_START)) == 0 ) /* COV_CAN_HARDWARE_FAILURE */
  {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
#else
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
#endif
  }
  {
    /* #25 set STOP request if not done in Can_InitController() before */
    { /* #40 HW request transition (LL) \trace SPEC-1632 */
        Can_SetHaltOfControllerData(canHwChannel, CANLL_TRUE);  /* SBSW_CAN_LL02 */
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
      #if defined( C_ENABLE_CAN_FD_USED ) 
        if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE ) 
        {
          CAN_SET_NCR_GLOBAL(CAN_NODE_NUM, (C_NCR_INIT | C_NCR_FDEN)); /* SBSW_CAN_LL01 */
        }
        else
      #endif
        {
          CAN_SET_NCR_GLOBAL(CAN_NODE_NUM, C_NCR_INIT); /* SBSW_CAN_LL01 */  
        }
        CanXC800GlobalInterruptRestore();
      }
    } /* loop canHwChannel */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      /* #110 transition finished synchronous return OK and change internal state */
      retval = CAN_OK;
      { /* #120 Use short initialization instead of Can_InitController() (LL) \trace SPEC-1627, SPEC-1646, SPEC-3965 */
        CanHL_StopReinit(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
      Can_CleanUpSendState(CAN_CHANNEL_CANPARA_ONLY);
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #130 allow reinitialization in notification */
      Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
      /* #140 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
      CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STOPPED );
#endif
    }
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_WakeupTransition
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_WakeupTransition
Relation_Context:
Relation:
OneChOpt
Wakeup
CommonCan
HardwareLoop
RamCheck, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WakeupTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  /* ----- Implementation ----------------------------------------------- */
  { /* #130 emulated SLEEP (CAN_NOT_SUPPORTED is CAN_OK) (stay in STOP mode instead) \trace SPEC-1638 */
    /* #140 transition finished synchronous return OK and change internal state */
    retval = CAN_OK;
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
      /* #150 do standard RAM check CanHL_DoRamCheck() */
    Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* Like PowerOn */ /* SBSW_CAN_HL02 */
    CanHL_DoRamCheck(CAN_CHANNEL_CANPARA_ONLY);
#endif
    /* #160 delete SLEEP for CAN_EMULATE_SLEEP and set to STOP \trace SPEC-1653 */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #170 allow reinitialization in notification */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* #180 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STOPPED );
#endif
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_DoRamCheck
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_DoRamCheck
Relation_Context:
Wakeup
RamCheck
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_DoRamCheck( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* SLEEP is already set as logical status for first WAKEUP after SLEEP (changed to STOP after this) */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
  /* #20 remove mark ongoing state change (force STOP transition in Can_InitController()) */
  Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
# endif
  Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_RAM_CHECK); /* SBSW_CAN_HL01 */
  /* #30 call Can_InitController() to perform the RAM check */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
  Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
}
#endif /* C_ENABLE_CAN_RAM_CHECK */

/****************************************************************************
| NAME:             CanHL_SleepTransition
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_SleepTransition
Relation_Context:
Relation:
Wakeup, CommonCan
Wakeup, ExtendedStateMachine
Wakeup, PnEnable
Wakeup, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_SleepTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #150 no WAKEUP-source-ref: do emulated SLEEP mode \trace SPEC-1629, SPEC-1641, SPEC-1645, SPEC-3914, SPEC-3927 */
  {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
    /* #160 controller stay in STOP mode / CAN_NOT_SUPPORTED is CAN_OK */
    retval = CAN_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#endif
#if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
    retval = CAN_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_SLEEP)); /* SBSW_CAN_HL02 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #170 allow reinitialization in notification */
    Can_SetStatusReq(channel, Can_GetStatusReq(channel)& (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
    /* #180 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_SLEEP );
# endif
#endif
  }
# if (CAN_EMULATE_SLEEP == STD_OFF) /* COV_CAN_EMULATE_SLEEP */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
# endif
  return retval;
} /* PRQA S 6010,6030,6050,6080*/ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             CanHL_WritePrepare
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_WritePrepare
Relation_Context:
Relation:
TxFullCANSupport
HwCancelTx
HwCancelTx, MultiplexedTx
MultiplexedTx, HwCancelTx, IdenticalIdCancel
ChannelAmount
TxBasicAmount
TxFullAmount
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_WritePrepare( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle  logTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 calculate logical TX mailbox handle for FullCAN or for BasicCAN (Multiplexed TX) as start value */
  logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Hth));
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  { /* #20 BasicCAN preparation - search for hardware and logical transmit handle and do cancellation */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    uint8_least muxTx;
    uint8_least muxTx_max;
    uint8_least muxTx_use;
    muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Hth); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    muxTx_use = muxTx_max;
#endif
    /* \trace SPEC-1677, SPEC-3800, SPEC-1672, SPEC-1679, SPEC-1673, SPEC-1671 */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    for (muxTx = 0; muxTx < muxTx_max; muxTx++)
    { /* #30 over all multiplexed TX objects: find free mailbox or mailbox with identical ID*/
      if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
      { /* #60 else priority 1 - find free mailbox (no cancellation) */
        break;
      }
      logTxObjHandle++;
    }
    if (muxTx == muxTx_max)
    { /* #90 found no free mailbox - so set to last valid handle */
      muxTx = 0; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
      logTxObjHandle--;
    } /* #100 otherwise the muxTx and logTxObjHandle are the free or to be cancelled one */
#else /* C_ENABLE_MULTIPLEXED_TRANSMISSION */
#endif
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    CAN_DUMMY_STATEMENT(muxTx_use); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  } /* end BasicCAN handling */
  /* #200 no special FullCAN handling needed */
  CAN_DUMMY_STATEMENT(PduInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return logTxObjHandle;
}

/****************************************************************************
| NAME:             CanHL_WriteStart
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_WriteStart
Relation_Context:
Relation:
GenericPreTransmit
CanFdSupport
GenericPreTransmit, DynamicFullCanTxID, TxFullCANSupport
IDType, MixedId, DynamicFullCanTxID, TxFullCANSupport
OneChOpt
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, CanObjectHandle logTxObjHandle, Can_PduInfoPtrType PduInfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 free TX mailbox found so start transmission \trace SPEC-1744 */
  if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
  {
    Can_HwHandleType txObjHandle;
    Can_SduPtrType   CanMemCopySrcPtr;
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
    /* #20 temporary buffer to avoid data modification on constant data */
    Can_PduType PduInfo_var;
#endif
#if defined(C_ENABLE_CAN_FD_USED)
    Can_IdType pduInfo_var_id;
    uint8 pduInfo_var_dlc;
# if defined(C_ENABLE_CAN_FD_FULL)
    uint8 pduInfo_var_dli;
# endif
#endif
    V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    # if defined(C_ENABLE_CAN_FD_FULL)
    V_DEF_P2SFR_CAN(volatile, tCanFdMsgObjStruct, AUTOMATIC) pCanFdCellMailbox;
    # endif
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
    Can_PduInfoPtrType_var PduInfoPtr_var;
    /* #25 PduInfo copy from ROM pointer context to RAM pointer context */
    PduInfoPtr_var = &PduInfo_var;
    PduInfo_var.id = PduInfo->id; 
    PduInfo_var.length = PduInfo->length;
    PduInfo_var.sdu = PduInfo->sdu;
    PduInfo_var.swPduHandle = PduInfo->swPduHandle;
    Appl_GenericPreTransmit( (uint8)channel, PduInfoPtr_var );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL24 */
#endif
#if defined(C_ENABLE_CAN_FD_USED)
    pduInfo_var_id = PDUINFO_PTR->id;
    if (PduInfo->length <= 8) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)
      { /* #30 remove FD flag when no FD support is activated in this initialization structure and DLC not greater than 8 */
        /* CAN FD also support an extended payload which allows the transmission of up to 64 bytes.
        This feature also depends on the CAN FD configuration (see CanControllerFdBaudrateConfig).
        Therefore, if the CAN FD feature is enabled and the CAN FD flag is set in CanId passed to
         Can_Write(), CanDrv supports the transmission of PDUs with a length up to 64 bytes.
        If there is a request to transmit a CAN FD frame without the CAN FD feature enabled the
        frame is sent as conventional CAN frame as long as the PDU length <= 8 bytes. */
        pduInfo_var_id = pduInfo_var_id & ((Can_IdType)(CAN_ID_IDE_MASK | CAN_ID_MASK)); /* CAN_FD_   mask out the FD bit */
      }
    }
#endif
    /* #40 remember PDU and send state to use it in Confirmation function \trace SPEC-1675, SPEC-3921 */
    Can_SetActiveSendPdu(logTxObjHandle, PDUINFO_PTR->swPduHandle); /* SBSW_CAN_HL05 */
    Can_SetActiveSendState(logTxObjHandle, CAN_SEND_OBJ); /* SBSW_CAN_HL04 */
    txObjHandle =  CanHL_GetTxLogToHwHandle(CAN_CHANNEL_CANPARA_FIRST logTxObjHandle);
#if defined(C_ENABLE_CAN_FD_USED)
    /* #50 CAN FD convert data length (0-64) to DLC (0-15) and to DLI (0-8,12,16,20,24,32,48,64) */
    pduInfo_var_dlc = CAN_ENCODE_DLI(PDUINFO_PTR->length);
# if defined(C_ENABLE_CAN_FD_FULL)
    pduInfo_var_dli = CAN_DECODE_DLI(pduInfo_var_dlc);
# endif
#endif
    /* #55 HW prepare transmission (LL) */
    {
      CanXC800GlobalInterruptDeclare    /* PRQA S 3334 */ /* MD_Can_3334_LL_IntDec */
      CanXC800GlobalInterruptDisable();
      CAN_GET_MAILBOX_ADDRESS(txObjHandle);
      CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_TXEN0); /* delete enable flag */ /* SBSW_CAN_LL06 */
      CanXC800GlobalInterruptRestore();
    }
    /* #60 Set ID, ID type and DLC in HW register depend on ID type */
#if defined(C_ENABLE_EXTENDED_ID)
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PDUINFO_ID) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK)
    {
#  if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#   if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
      if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#   endif
#  endif
      {
        CAN_SET_PMAILBOX_MoARHi(MK_STDID0(PDUINFO_ID)); /* SBSW_CAN_LL06 */
        # if defined( C_ENABLE_EXTENDED_ID )   /* COV_CAN_EXTENDED_ID */
        CAN_SET_PMAILBOX_MoARLo(MK_STDID1(PDUINFO_ID)); /* SBSW_CAN_LL06 */
        # endif
      }
      CAN_SET_PMAILBOX_MoFCR_DLC(MK_TX_DLC(PDUINFO_DLC) & C_MOFCR_DLC); /* SBSW_CAN_LL06 */
      # if defined( C_ENABLE_CAN_FD_USED )
      {
        uint8 mode = C_MOFCR_MODE_NORMAL;
        /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXTX as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is active */
        if ( (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE) && ((PDUINFO_PTR->id & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK ) )
        {
          mode |= (C_MOFCR_EDL | C_MOFCR_MODE_FDBASE);
          /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXONLY as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is deactivated */
          if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_FD_RXTX )
          {
            mode |= C_MOFCR_BRS;
          }
        }
        CAN_SET_PMAILBOX_MoFCR_Mode(mode); /* configure mode */ /* SBSW_CAN_LL06 */
      }
      # endif
      
    }
    else
# endif
    {
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
      if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#  endif
# endif
      {
        CAN_SET_PMAILBOX_MoARHi(MK_EXTID0(PDUINFO_ID)); /* SBSW_CAN_LL06 */
        # if defined( C_ENABLE_EXTENDED_ID )   /* COV_CAN_EXTENDED_ID */
        CAN_SET_PMAILBOX_MoARLo(MK_EXTID1(PDUINFO_ID)); /* SBSW_CAN_LL06 */
        # endif
      }
      CAN_SET_PMAILBOX_MoFCR_DLC(MK_TX_DLC_EXT(PDUINFO_DLC) & C_MOFCR_DLC); /* SBSW_CAN_LL06 */
      # if defined( C_ENABLE_CAN_FD_USED )
      {
        uint8 mode = C_MOFCR_MODE_NORMAL;
        /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXTX as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is active */
        if ( (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE) && ((PDUINFO_PTR->id & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK ) )
        {
          mode |= (C_MOFCR_EDL | C_MOFCR_MODE_FDBASE);
          /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXONLY as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is deactivated */
          if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_FD_RXTX )
          {
            mode |= C_MOFCR_BRS;
          }
        }
        CAN_SET_PMAILBOX_MoFCR_Mode(mode); /* configure mode */ /* SBSW_CAN_LL06 */
      }
      # endif
      
    }
#else
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
    if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#  endif
# endif
    {
      CAN_SET_PMAILBOX_MoARHi(MK_STDID0(PDUINFO_ID)); /* SBSW_CAN_LL06 */
      # if defined( C_ENABLE_EXTENDED_ID )   /* COV_CAN_EXTENDED_ID */
      CAN_SET_PMAILBOX_MoARLo(MK_STDID1(PDUINFO_ID)); /* SBSW_CAN_LL06 */
      # endif
    }
    CAN_SET_PMAILBOX_MoFCR_DLC(MK_TX_DLC(PDUINFO_DLC) & C_MOFCR_DLC); /* SBSW_CAN_LL06 */
    # if defined( C_ENABLE_CAN_FD_USED )
    {
      uint8 mode = C_MOFCR_MODE_NORMAL;
      /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXTX as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is active */
      if ( (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE) && ((PDUINFO_PTR->id & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK ) )
      {
        mode |= (C_MOFCR_EDL | C_MOFCR_MODE_FDBASE);
        /* CAN_INIT_OBJ_FD_CONFIG is set to CAN_FD_RXONLY as soon as a CanControllerFdBaudrateConfig is created AND Tx Bit Rate switch is deactivated */
        if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_FD_RXTX )
        {
          mode |= C_MOFCR_BRS;
        }
      }
      CAN_SET_PMAILBOX_MoFCR_Mode(mode); /* configure mode */ /* SBSW_CAN_LL06 */
    }
    # endif
    
#endif
    if(PDUINFO_PTR->sdu != NULL_PTR)
    { /* #70 Set CAN data in HW register (LL) - only when data pointer is not null \trace SPEC-1680, SPEC-1572, SPEC-1678, SPEC-60421 */
      CanMemCopySrcPtr = PDUINFO_PTR->sdu;
#if defined(C_ENABLE_CAN_FD_FULL)
      { /* - do not copy data with 32bit access because of failure with GNU compiler
           - do not use 32bit copy because of possible 8bit allignment for application data */
        vuint8           canllidx;
        vuint8           MofcrMode;
        
        for (canllidx = 0; canllidx < 8; canllidx++)
        {
          ((CanChipDataSfrPtr) &pCanCellMailbox->MoDR[0])[canllidx] = CanMemCopySrcPtr[canllidx]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
        }
        CAN_GET_PMAILBOX_MoFCR_Mode(MofcrMode); /* SBSW_CAN_LL06 */
        if ( (MofcrMode & C_MOFCR_MODE_FDBASE) == C_MOFCR_MODE_FDBASE)
        {
          if (PDUINFO_PTR->length > 8)
          {
            pCanFdCellMailbox = (CanFdMsgObjStructPtr) &canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK(txObjHandle+1)]; /* PRQA S 310 */ /* MD_Can_0310 */
            for(canllidx = 8; canllidx < PDUINFO_PTR->length; canllidx ++)
            {
              ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-8] = CanMemCopySrcPtr[canllidx]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
            }
            for(canllidx = PDUINFO_PTR->length; canllidx < 36 ; canllidx ++)
            {
              ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-8] = Can_GetMailboxFdPadding(Hth); /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
            }
            if (PDUINFO_PTR->length > 36)
            {
              pCanFdCellMailbox = (CanFdMsgObjStructPtr) &canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK(txObjHandle+2)]; /* PRQA S 310 */ /* MD_Can_0310 */
              for(canllidx = 36; canllidx < PDUINFO_PTR->length; canllidx ++)
              {
                ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-36] = CanMemCopySrcPtr[canllidx]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
              }
              for(canllidx = PDUINFO_PTR->length; canllidx < 64 ; canllidx ++)
              {
                ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-36] = Can_GetMailboxFdPadding(Hth); /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
              }
            }
            else
            {
              pCanFdCellMailbox = (CanFdMsgObjStructPtr) &canCellPtr->Obj[(vuint8)CAN_HWOBJ_SAFE_MASK(txObjHandle+2)]; /* PRQA S 310 */ /* MD_Can_0310 */
              /* padding position 36 - 63 */
              for(canllidx = 36; canllidx < 64 ; canllidx ++)
              {
                ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-36] = Can_GetMailboxFdPadding(Hth); /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
              }        
            }
          }
        }
      }
#else
      { /* - do not copy data with 32bit access because of failure with GNU compiler
           - do not use 32bit copy because of possible 8bit allignment for application data */
        vuint8           canllidx;
        for (canllidx = 0; canllidx < 8; canllidx++)
        {
          ((CanChipDataSfrPtr) &pCanCellMailbox->MoDR[0])[canllidx] = CanMemCopySrcPtr[canllidx]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
        }
      }
#endif
    }
    /* #80 HW start transmission (LL) */
    retval = CAN_OK; /* default is OK - LL set it to kCanFailed/CAN_NOT_OK in case of issue */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
    {
      CanXC800GlobalInterruptDeclare   /* PRQA S 3334 */ /* MD_Can_3334_LL_IntDec */
      CanXC800GlobalInterruptDisable();
      CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_RTSEL); /* delete sel bit */  /* SBSW_CAN_LL06 */
      CAN_SET_PMAILBOX_MoCtrH(C_MOCTR_TXEN0 | C_MOCTR_TXEN1 | C_MOCTR_TXREQ | C_MOCTR_NEWDAT); /* SBSW_CAN_LL06 */
      CanXC800GlobalInterruptRestore();
    }
    /* HW finish transmission (LL) */
  }
  else
  { /* #200 no free TX mailbox found so return busy - also in case cancellation (BasicCAN) was possible \trace SPEC-1754, SPEC-1764, SPEC-1747, SPEC-3878, SPEC-3856 */
    retval = CAN_BUSY;
  }
  CAN_DUMMY_STATEMENT(Hth); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return retval;
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             CanHL_GetTxHwToLogHandle
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_GetTxHwToLogHandle
Relation_Context:
TxFullCANSupport
HwCancelTx
Relation:
DevErrorDetect
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetTxHwToLogHandle( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwTxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle logTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
  /* #10 get logical handle from generated indirection table */
  logTxObjHandle = (CanObjectHandle) Can_GetTxIndirectionHwToLog((hwTxObjHandle) + Can_GetTxIndirectionHwToLogStart(channel));
#else
  /* #20 get logical handle by add generated offset to hardware handle */
  logTxObjHandle = (CanObjectHandle)(hwTxObjHandle + Can_GetTxOffsetHwToLog(channel));
#endif
#if (CAN_SAFE_BSW == STD_ON)
  if ((logTxObjHandle + CAN_MULTIPLEXED_TX_MAX) >= (Can_HwHandleType)Can_GetSizeOfActiveSendObject()) /* CM_CAN_HL03 */ /* COV_CAN_GENDATA_FAILURE */
  { /* just to secure SilentBSW */
    logTxObjHandle = (Can_HwHandleType)(Can_GetSizeOfActiveSendObject() - CAN_MULTIPLEXED_TX_MAX); /* -1 is used later on so don't use 0 here */
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return logTxObjHandle;
}

/****************************************************************************
| NAME:             CanHL_GetTxLogToHwHandle
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_GetTxLogToHwHandle
Relation_Context:
HwCancelTx
Relation:
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_HwHandleType, STATIC_CODE) CanHL_GetTxLogToHwHandle( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_HwHandleType hwTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
  /* #10 get hardware handle from generated indirection table */
  hwTxObjHandle = (Can_HwHandleType) Can_GetTxIndirectionLogToHw(logTxObjHandle);
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#else
  /* #20 get hardware handle by subtract generated offset from logical handle */
  hwTxObjHandle = (Can_HwHandleType)(logTxObjHandle - Can_GetTxOffsetHwToLog(channel));
#endif
  return hwTxObjHandle;
}

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_RamCheckMailboxNotification
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RamCheckMailboxNotification
Relation_Context:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Relation:
RamCheck
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
RxFullAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle, Can_HwHandleType htrh ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 notify application about corrupt mailbox */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  CanIf_RamCheckCorruptMailbox((uint8)Can_GetCanToCanIfChannelMapping(channel), htrh);
# else
#  if defined(C_ENABLE_NOTIFY_CORRUPT_MAILBOX) /* with Mailbox Notification */
  Appl_CanCorruptMailbox((uint8)channel, (hwObjHandle));
#  endif
# endif
  /* #20 deactivate mailbox */
  Can_SetMailboxState(htrh, CAN_DISABLED_OBJ); /* SBSW_CAN_HL34 */
  /* #30 deactivate controller */
  Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */

  CAN_DUMMY_STATEMENT(hwObjHandle); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(htrh); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
}
#endif

/****************************************************************************
| NAME:             CanHL_SetValue8
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetValue8
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue8( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr8 regPtr, uint8 value, uint8 readMask ) /* PRQA S 3219 */ /* MD_Can_Asr_3219 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint8 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

/****************************************************************************
| NAME:             CanHL_SetValue16
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetValue16
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue16( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask ) /* PRQA S 3219 */ /* MD_Can_Asr_3219 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint16 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

/****************************************************************************
| NAME:             CanHL_SetValue32
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetValue32
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue32( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, uint32 value, uint32 readMask ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 3219 */ /* MD_Can_Asr_3219 */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint32 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

/****************************************************************************
| NAME:             CanHL_InitBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitBegin
Relation_Context:
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR;
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;

  /* #10 Set controller to initialization mode (LL) */
  #if (CAN_SAFE_BSW == STD_ON)
  if (CanLL_CheckGeneratedDataAccess(CAN_CHANNEL_CANPARA_ONLY) != CAN_E_NO_ERROR) /* COV_CAN_GENDATA_ERROR */
  {
    errorId = CAN_E_GENDATA;
  }
  else
  #endif
  {
    Can_SetBusOffNotifiedOfControllerData(canHwChannel, CANLL_TRUE); /* lint !e661 suppress busoff detection while Init-flag is set */  /* SBSW_CAN_LL02 */

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* #20 Execute pattern RamCheck */
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    initInfo->isChCorrupt |= CAN_RAM_CHECK_BEGIN_REG_RESULT(channel); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
  } 
#endif

  /* #30 Initialize controller registers (Begin section) (LL) */
    {
      V_DEF_P2SFR_CAN(V_NONE, tCanNodeStruct, AUTOMATIC)     pCanCellNode;
      CanXC800GlobalInterruptDeclare
      CanXC800GlobalInterruptDisable();
      initInfo->canllNode = CAN_NODE_NUM;  /* SBSW_CAN_LL07 */
      pCanCellNode = (CanNodeStructPtr) &canCellPtr->Node[initInfo->canllNode];
      initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellNode->NSR, (vuint16)0x0000u, 0x7338U);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NCR, ( C_NCR_CCE | C_NCR_INIT ), 0x03FFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    #if defined( C_ENABLE_CAN_FD_USED )
      if (Can_GetInitObjectFdBrsConfig(initObject) != CAN_NONE )
      {
        initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NCR, ( C_NCR_CCE | C_NCR_INIT | C_NCR_FDEN ), 0x03FFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isChCorrupt |= CanHL_SetValue32( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->FNBTR, Can_GetInitBTFast(initObject), 0x00007FFFUL);    /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isChCorrupt |= CanHL_SetValue32( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NTDCR, Can_GetInitTDCO(initObject), 0x00008F00UL);      /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
        initInfo->isChCorrupt |= CanHL_SetValue32( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NBTR, Can_GetInitBT(initObject), 0xFDF8F3FUL);          /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
      }
      else
      {
        initInfo->isChCorrupt |= CanHL_SetValue32( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NBTR, Can_GetInitBT(initObject), 0x0000FFFFUL);             /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
      }
    # if defined( C_ENABLE_FD_NISO )  /* COV_NISO_PED */
      ((CanNodeStructPtr) &canCellPtr->Node[0])->NBTR |= 0x00008000UL;
    # endif
    # if defined( C_ENABLE_FD_PED )   /* COV_NISO_PED */
      ((CanNodeStructPtr) &canCellPtr->Node[1])->NBTR |= 0x00008000UL;
    # endif
    #else
      initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NBTR, Can_GetInitBT(initObject), 0xFFFFUL);             /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
    #endif  
      /* all 4 interrupts of node x occure in 1 CAN_ISR x */
      initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NIPR, ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<8) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<12)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
      /* set the rx-source for this node 0x000 - 0x111 possible for other P6-pinning */
      initInfo->isChCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NPCR, (vuint16)Can_GetInitPortSel(canHwChannel), 0x0107U); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isChCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NECnt_Rec, (vuint8)0x00, 0xFFU);                            /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isChCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NECnt_Tec, (vuint8)0x00, 0xFFU);                            /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isChCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST & pCanCellNode->NECnt_EWRNLVL, (vuint8)0x60, 0xFFU);                        /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      CanXC800GlobalInterruptRestore();
    }
  }

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
} /* PRQA S 6010,6050 */ /* MD_MSR_STPTH,MD_MSR_STCAL */

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitTxFullCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitTxFullCAN
Relation_Context:
TxFullCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
IDType
DynamicFullCanTxID
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CanObjectHandle logTxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  errorId = CAN_E_NO_ERROR;
  /* #10 iterate over all FullCAN TX */
  for (Htrh = Can_GetTxFullHandleStart(canHwChannel); Htrh < Can_GetTxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* #20 initialize FullCAN TX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    hwObjHandle = Can_GetHwHandle(Htrh);
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
    Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for FullCAN TX mailboxes */
    initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    {
      initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* HW specific TX initialization (LL) */
    {
    CanXC800GlobalInterruptDeclare
    V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
    
    CanXC800GlobalInterruptDisable();
    /* reset mailbox (clear MSGVAL before alloc to list) */
    initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
    
    if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
    {
      /* insert msg-object (idx) in list (node+1) */
      CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
      /* will not be checked by extended RAM check, write access is encapsulated into inline function, PanCmd is not readable, PanPar is tested via pattern*/
      
    }
    initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    {
      initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_TXEN1 | C_MOCTR_DIR) , 0x0C20U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
    }
    # if defined(C_ENABLE_CAN_FD_FULL)
    if(Can_GetMaxDataLenOfMailbox(Htrh) <= 8)   /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
    #endif
    {
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_NORMAL, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    }
    initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    #if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_TX_POLLING))
    # if defined ( C_ENABLE_INDIVIDUAL_POLLING )
    if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
    # endif
    {
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_TX, 0xFFU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    }
    #endif
    #if defined(C_ENABLE_CAN_FD_FULL)
    if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
    {
      uint8 index; 
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)(hwObjHandle+1), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)(hwObjHandle+2), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      
      for (index=0; index <2; index++)
      { 
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle+index+1);
        /* reset mailbox (clear MSGVAL before alloc to list) */    
        initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
        if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
        {
          /* insert msg-object (idx) in list (node+1) */
          CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, (hwObjHandle+index+1), C_PAN_ALLOC_TO_LIST); /* move to unused channel*/
        }
        initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_MSGVAL, 0x0020U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      }
      CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
    }
    #else
    /* !C_ENABLE_CAN_FD_FULL */
    #endif            
    CanXC800GlobalInterruptRestore();
    }
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* if needed the initialization of ID, DLC and type is done in InitTxObj to avoid problems with uninitialized registers */ /* COV_DYNAMIC_FULLCAN_ID */
    /* #40 set ID and DLC for FullCAN TX mailboxes */
#  if defined(C_ENABLE_EXTENDED_ID)
#   if defined(C_ENABLE_MIXED_ID)
    if ( (Can_GetIDValue(Htrh) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
        CAN_SET_MoARHi(hwObjHandle, MK_STDID0(Can_GetIDValue(Htrh)));
      # if defined( C_ENABLE_EXTENDED_ID )
        CAN_SET_MoARLo(hwObjHandle, MK_STDID1(Can_GetIDValue(Htrh)));
      # endif
        CanXC800GlobalInterruptRestore();
      }
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
        CAN_SET_MoFCR_DLC(hwObjHandle, MK_TX_DLC(Can_GetDLC_FIFO(Htrh)));
        CanXC800GlobalInterruptRestore();
      }
    }
    else
#   endif
    {
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
        CAN_SET_MoARHi(hwObjHandle, MK_EXTID0(Can_GetIDValue(Htrh)));
      # if defined( C_ENABLE_EXTENDED_ID )
        CAN_SET_MoARLo(hwObjHandle, MK_EXTID1(Can_GetIDValue(Htrh)));
      # endif
        CanXC800GlobalInterruptRestore();
      }
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
        CAN_SET_MoFCR_DLC(hwObjHandle, MK_TX_DLC_EXT(Can_GetDLC_FIFO(Htrh)));
        CanXC800GlobalInterruptRestore();
      }
    }
#  else
    {
      CanXC800GlobalInterruptDeclare
      CanXC800GlobalInterruptDisable();
      CAN_SET_MoARHi(hwObjHandle, MK_STDID0(Can_GetIDValue(Htrh)));
    # if defined( C_ENABLE_EXTENDED_ID )
      CAN_SET_MoARLo(hwObjHandle, MK_STDID1(Can_GetIDValue(Htrh)));
    # endif
      CanXC800GlobalInterruptRestore();
    }
    {
      CanXC800GlobalInterruptDeclare
      CanXC800GlobalInterruptDisable();
      CAN_SET_MoFCR_DLC(hwObjHandle, MK_TX_DLC(Can_GetDLC_FIFO(Htrh)));
      CanXC800GlobalInterruptRestore();
    }
#  endif
# endif
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
    }
    if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CAN_SET_MoCtrL(hwObjHandle, C_MOCTR_MSGVAL); /* disable object */  /* SBSW_CAN_LL06 */
      if (initInfo->isMbCorrupt == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
      }
    }
# endif
  }
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

/****************************************************************************
| NAME:             CanHL_InitTxBasicCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitTxBasicCAN
Relation_Context:
Relation:
MultiplexedTx
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CanObjectHandle logTxObjHandle;
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  CanObjectHandle logTxObjHandleStop;
  uint8_least muxTx_max;
#endif
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
#endif

  Htrh = Can_GetTxBasicHandleStart(canHwChannel);
#if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; Htrh < Can_GetTxBasicHandleStop(canHwChannel); Htrh++)
#endif
  { /* #10 iterate over all logical BasicCAN TX */
    hwObjHandle = Can_GetHwHandle(Htrh); /* do not use: hwObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) - Htrh may used by LL */
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Htrh); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    logTxObjHandleStop = logTxObjHandle + (Can_HwHandleType) muxTx_max;
    for (; logTxObjHandle < logTxObjHandleStop; logTxObjHandle++)
#endif
    { /* #20 initialize BasicCAN TX mailboxes */
      Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
#if defined(C_ENABLE_CAN_RAM_CHECK)
      /* #30 RAM check for BasicCAN TX mailboxes */
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      {
        initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
      } 
      else
      {
        initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
      }
#endif
      /* HW specific TX initialization (LL) */
      {
      CanXC800GlobalInterruptDeclare
      V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
      CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      
      CanXC800GlobalInterruptDisable();
      /* reset mailbox (clear MSGVAL before alloc to list) */
      initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      
      if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
      {
        /* insert msg-object (idx) in list (node+1) */
        CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
        /* will not be checked by extended RAM check, write access is encapsulated into inline function, PanCmd is not readable, PanPar is tested via pattern*/
        
      }
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      {
        initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_TXEN1 | C_MOCTR_DIR) , 0x0C20U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      }
      # if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) <= 8)   /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      #endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_NORMAL, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      #if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_TX_POLLING))
      # if defined ( C_ENABLE_INDIVIDUAL_POLLING )
      if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      # endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_TX, 0xFFU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      #endif
      #if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      {
        uint8 index; 
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)(hwObjHandle+1), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)(hwObjHandle+2), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        
        for (index=0; index <2; index++)
        { 
          CAN_GET_MAILBOX_ADDRESS(hwObjHandle+index+1);
          /* reset mailbox (clear MSGVAL before alloc to list) */    
          initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
          {
            /* insert msg-object (idx) in list (node+1) */
            CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, (hwObjHandle+index+1), C_PAN_ALLOC_TO_LIST); /* move to unused channel*/
          }
          initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_MSGVAL, 0x0020U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
        }
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      }
      #else
      /* !C_ENABLE_CAN_FD_FULL */
      #endif            
      CanXC800GlobalInterruptRestore();
      }
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
      { /* PowerOn */
        Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
      }
      if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
      { /* #45 deactivate corrupt mailbox */
        CAN_SET_MoCtrL(hwObjHandle, C_MOCTR_MSGVAL); /* disable object */  /* SBSW_CAN_LL06 */
        if (initInfo->isMbCorrupt == kCanTrue)
        {  /* #50 notify application about corrupt mailbox and deactivate controller */
          CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
        }
      }
#endif
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
      hwObjHandle += (Can_HwHandleType)(Can_GetDLC_FIFO(Htrh) / muxTx_max); /* PRQA S 3199,3198 */ /* MD_Can_3199_dummy */
#endif
    }
  }
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxFullCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitRxFullCAN
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
IDType
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  for (Htrh = Can_GetRxFullHandleStart(canHwChannel); Htrh < Can_GetRxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* #10 iterate over all FullCAN RX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    hwObjHandle=Can_GetHwHandle(Htrh);
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for FullCAN RX mailboxes */
    initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    {
      initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* #30 set ID for FullCAN RX mailboxes (LL) */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
    if ( (Can_GetIDValue(Htrh) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      {
      CanXC800GlobalInterruptDeclare
      V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
      CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      
      CanXC800GlobalInterruptDisable();
      
      initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
      {
        /* insert msg-object (idx) in list (node+1) */
        CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
      }
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      {
        initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      }
      {
        initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, (C_EID_MASK_16 | C_MOAMRHI_CLOSE) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRLo, C_MOAMRLO_CLOSE , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, MK_STDID0(Can_GetIDValue(Htrh)) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # if defined( C_ENABLE_EXTENDED_ID )  /* COV_CAN_EXTENDED_ID */
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARLo, MK_STDID1(Can_GetIDValue(Htrh)) , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # endif
      # if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) <= 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
      # endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_NORMAL, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_RX_FULLCAN_POLLING))
      #  if defined ( C_ENABLE_INDIVIDUAL_POLLING )
      if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      #  endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_RX, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      # endif
      # if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
      {
        uint8 index;
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)(hwObjHandle+1), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)(hwObjHandle+2), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      
        for (index=0; index <2; index++) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
        {
          CAN_GET_MAILBOX_ADDRESS(hwObjHandle+index+1);
          initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */ /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
          {
            /* insert msg-object (idx) in list (node+1) */
            CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, (hwObjHandle+index+1), C_PAN_ALLOC_TO_LIST); /* move to unused channel*/
          }
          {
            initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          }
        }
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      }
      # endif            
      CanXC800GlobalInterruptRestore();
      }
    }
    else
#  endif
    {
      {
      CanXC800GlobalInterruptDeclare
      V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
      CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      
      CanXC800GlobalInterruptDisable();
      
      initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
      {
        /* insert msg-object (idx) in list (node+1) */
        CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
      }
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      {
        initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      }
      {
        initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, (C_EID_MASK_16 | C_MOAMRHI_CLOSE) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRLo, C_MOAMRLO_CLOSE , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, MK_EXTID0(Can_GetIDValue(Htrh)) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # if defined( C_ENABLE_EXTENDED_ID )  /* COV_CAN_EXTENDED_ID */
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARLo, MK_EXTID1(Can_GetIDValue(Htrh)) , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # endif
      # if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) <= 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
      # endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_NORMAL, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_RX_FULLCAN_POLLING))
      #  if defined ( C_ENABLE_INDIVIDUAL_POLLING )
      if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      #  endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_RX, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      }
      # endif
      # if defined(C_ENABLE_CAN_FD_FULL)
      if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
      {
        uint8 index;
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)(hwObjHandle+1), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)(hwObjHandle+2), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      
        for (index=0; index <2; index++) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
        {
          CAN_GET_MAILBOX_ADDRESS(hwObjHandle+index+1);
          initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */ /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
          {
            /* insert msg-object (idx) in list (node+1) */
            CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, (hwObjHandle+index+1), C_PAN_ALLOC_TO_LIST); /* move to unused channel*/
          }
          {
            initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          }
        }
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
      }
      # endif            
      CanXC800GlobalInterruptRestore();
      }
    }
# else
    {
    CanXC800GlobalInterruptDeclare
    V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
    
    CanXC800GlobalInterruptDisable();
    
    initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
    if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
    {
      /* insert msg-object (idx) in list (node+1) */
      CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
    }
    initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    {
      initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
    }
    {
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, (C_EID_MASK_16 | C_MOAMRHI_CLOSE) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRLo, C_MOAMRLO_CLOSE , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    }
    initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, MK_STDID0(Can_GetIDValue(Htrh)) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    # if defined( C_ENABLE_EXTENDED_ID )  /* COV_CAN_EXTENDED_ID */
    initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARLo, MK_STDID1(Can_GetIDValue(Htrh)) , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    # endif
    # if defined(C_ENABLE_CAN_FD_FULL)
    if(Can_GetMaxDataLenOfMailbox(Htrh) <= 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
    # endif
    {
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_NORMAL, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    }
    initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    # if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_RX_FULLCAN_POLLING))
    #  if defined ( C_ENABLE_INDIVIDUAL_POLLING )
    if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
    #  endif
    {
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_RX, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    }
    # endif
    # if defined(C_ENABLE_CAN_FD_FULL)
    if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
    {
      uint8 index;
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)(hwObjHandle+1), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)(hwObjHandle+2), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
    
      for (index=0; index <2; index++) /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
      {
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle+index+1);
        initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
        if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */ /* COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER */
        {
          /* insert msg-object (idx) in list (node+1) */
          CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, (hwObjHandle+index+1), C_PAN_ALLOC_TO_LIST); /* move to unused channel*/
        }
        {
          initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, (C_MOCTR_MSGVAL | C_MOCTR_RXEN) , 0x00A0U ); /* configure as Rx */ /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
        }
      }
      CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
    }
    # endif            
    CanXC800GlobalInterruptRestore();
    }
# endif
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
    }
    if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CAN_SET_MoCtrL(hwObjHandle, C_MOCTR_MSGVAL); /* disable object */ /* SBSW_CAN_LL06 */
      if (initInfo->isMbCorrupt == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
      }
    }
# endif
  }

# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxBasicCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitRxBasicCAN
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  for (Htrh = Can_GetRxBasicHandleStart(canHwChannel); Htrh < Can_GetRxBasicHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* #10 iterate over all BasicCAN RX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    for (hwObjHandle = Can_GetHwHandle(Htrh); hwObjHandle < (Can_HwHandleType)(Can_GetHwHandle(Htrh) + Can_GetDLC_FIFO(Htrh)); hwObjHandle++)
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* #20 RAM check for BasicCAN RX mailboxes */
      initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      {
        initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
      } 
# endif
      /* #30 initialize BasicCAN RX mailboxes (LL) */
      {
        CanXC800GlobalInterruptDeclare
        V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
        Can_HwHandleType mailboxidx;
        CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
        
        CanXC800GlobalInterruptDisable();
        
        initInfo->isMbCorrupt |= CanLL_Reset_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrL, C_MOCTR_ALL, 0x0FFFU ); /* reset mailbox (clear MSGVAL before alloc to list) */  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, 0x00, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
                  
        mailboxidx = hwObjHandle - Can_GetHwHandle(Htrh);
       
        switch(mailboxidx)
        {
        case 0:
      # if defined(C_ENABLE_CAN_FD_FULL)      
          if(Can_GetMaxDataLenOfMailbox(Htrh) > 8) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
          {
            /*Master object of a FD group*/
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
         
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT,  (uint8)(hwObjHandle+1), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP,  (uint8)(hwObjHandle+2), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE, C_MOFCR_IE_SDT, 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */ 
          }
          else      
      # endif
          {
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_RXBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */            
            
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT, (uint8)hwObjHandle, 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP, (uint8)((hwObjHandle + Can_GetDLC_FIFO(Htrh)) - 1), 0xFFUL);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
          }
          CanHL_InitRxBasicCANSubSetMask(initInfo, hwObjHandle, Htrh ); /* SBSW_CAN_HL31 */
          {
            initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_RXEN, 0x00A0U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          }
          break;
        case 3: /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      # if defined(C_ENABLE_CAN_FD_FULL)      
          if(Can_GetMaxDataLenOfMailbox(Htrh) > 8)  /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
          {
            /*Master object of a FD group*/
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_Mode, C_MOFCR_MODE_FDBASE, 0x0FU);  /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_BOT,  (uint8)(hwObjHandle+1), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_TOP,  (uint8)(hwObjHandle+2), 0xFFUL);   /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
            CanHL_InitRxBasicCANSubSetMask(initInfo, hwObjHandle, Htrh ); /* SBSW_CAN_HL31 */
            initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_RXEN, 0x00A0U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
          }
          else
      # endif /* C_ENABLE_CAN_FD_FULL */          
          {
            {
              initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_MSGVAL , 0x0020U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
            }  
          }
          break;
        default:  
          CanHL_InitRxBasicCANSubCloseMask(initInfo, hwObjHandle); /* SBSW_CAN_HL31 */
          break;
        } /*switch*/
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_CUR,  (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFGPR_SEL,  (uint8)hwObjHandle, 0xFFUL);       /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */    
            
        if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
        {
          /* insert msg-object (idx) in list (node+1) */
          CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST (initInfo->canllNode+1), hwObjHandle, C_PAN_ALLOC_TO_LIST);
        }
        initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoIPR, (vuint16)((Can_GetSrcNum(canHwChannel) & 0x0Fu) | ((vuint16)(Can_GetSrcNum(canHwChannel) & 0x0Fu)<<4) | ((vuint16)(hwObjHandle & 0xFFu)<<8)), 0xFFFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
      # if defined (C_ENABLE_INDIVIDUAL_POLLING) || (!defined (C_ENABLE_INDIVIDUAL_POLLING) && !defined(C_ENABLE_RX_BASICCAN_POLLING))
      #  if defined ( C_ENABLE_INDIVIDUAL_POLLING )        
        if (Can_GetHwObjIndivPolling(hwObjHandle) == (vuint8)0x00) /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
      #  endif
        {
          initInfo->isMbCorrupt |= CanHL_SetValue8( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoFCR_IE,(pCanCellMailbox->MoFCR_IE | C_MOFCR_IE_RX), 0xFFU); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
        }
      # endif
      {      
        initInfo->isMbCorrupt |= CanLL_Set_MoCtr( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoCtrH, C_MOCTR_MSGVAL, 0x0020U ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL08 */
      }
      CanXC800GlobalInterruptRestore();
      }
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
      { /* PowerOn */
        Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
      }
      if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
      { /* #45 deactivate corrupt mailbox */
        CAN_SET_MoCtrL(hwObjHandle, C_MOCTR_MSGVAL); /* disable object */ /* SBSW_CAN_LL06 */
        if (initInfo->isMbCorrupt == kCanTrue)
        {  /* #50 notify application about corrupt mailbox and deactivate controller */
          CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
        }
      }
# endif
    }
  }
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

/****************************************************************************
| NAME:             CanHL_InitEnd_InitMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitEnd_InitMode
Relation_Context:
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;

  /* #20 HW specific initialization end (LL) */
  {
    vuint8 canllidx;  
    CanXC800GlobalInterruptDeclare
    CanXC800GlobalInterruptDisable();
  
  /* delete all pending messages for this channel */
    for (canllidx=0; canllidx < CAN_MAX_PND_REG; canllidx++)
    {
  #if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
      CAN_SET_MSPND(canllidx, ~Can_GetGlobalInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllidx)); /* SBSW_CAN_LL03 */
      /* only set by HW */
  #else
      CAN_SET_MSPND(canllidx, ~CanInterruptPendingMask[canHwChannel].GlobalMask[canllidx]); /* SBSW_CAN_LL03 */
  #endif
    }
  
  /* set interrupt prio and enable interrupt */
  #if defined(C_ENABLE_CAN_INTERRUPT_CONTROL) /* COV_CAN_INTERRUPT_CONTROL */
    if ( (Can_GetLogStatus(channel) & kCanHwIsInit) == 0 ) /* only in power on init */
    {
  # if defined(C_ENABLE_MULTIPLE_CELLS)
      vuint8 canll_channel_offset;
      if (Can_GetCellInfoIdxOfCell(canHwChannel) == CAN_MULTICAN)
      {
        canll_channel_offset = 0u;
      } 
      else
      {
        canll_channel_offset = CAN_MULTICANR_CH_OFFSET;
      }
  # endif
      /* else canll_channel_offset is a global define with a constant value */
  
      assertInternal (Can_GetPhysPrio(CAN_NODE_NUM + canll_channel_offset) != 0, channel, kErrorUnknownISRPriority)   /* lint !e774 !e506 */ /* COV_CAN_GENDATA_FAILURE */
  #  if defined( C_LL_INTERRUPT_ISR_ACTIVE ) /* ! pure polling configuration */
  #   if defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
      /* enable Service and clear pending IR, IR prio will not be written in case of OS IR Control */
      (void)osEnableInterruptSource(Can_GetIsrOsId(canHwChannel), TRUE);
  #   else
      CAN_SRC_PROTECT_WRITE(CAN_SRC_PTR(canHwChannel), (C_ICR_CR_INIT | (vuint32)Can_GetPhysPrio(CAN_NODE_NUM + canll_channel_offset)));  /* SBSW_CAN_LL09 */
  #   endif  
  #  endif
    }
  #endif /* C_ENABLE_CAN_INTERRUPT_CONTROL */
    CanXC800GlobalInterruptRestore();
  }

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}

/****************************************************************************
| NAME:             CanHL_InitEnd_StopMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitEnd_StopMode
Relation_Context:
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_StopMode( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;

  /* #10 HW specific initialization transition to STOP (LL) */
  Can_SetHaltOfControllerData(canHwChannel, CANLL_TRUE); /* SBSW_CAN_LL02 */

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}

/****************************************************************************
| NAME:             CanHL_StopReinit
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StopReinit
Relation_Context:
Wakeup, RamCheck
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopReinit( CAN_HW_CHANNEL_CANTYPE_ONLY ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 do a short initialization instead of full Can_InitController() in case of STOP transition (CanLL_StopReinit) */
  /* #20 Delete all Pending Interrupt and Pending flags for TX,RX,BUSOFF and WAKEUP */
  vuint8 canllidx;
  CanObjectHandle objHandle;
  V_DEF_P2SFR_CAN(V_NONE, tCanNodeStruct, AUTOMATIC)     pCanCellNode;
  pCanCellNode = (CanNodeStructPtr) &canCellPtr->Node[CAN_NODE_NUM];
  CanXC800GlobalInterruptDeclare
  CanXC800GlobalInterruptDisable();
  /* enable acess to control registers */
  #if defined( C_ENABLE_CAN_FD_USED ) 
  if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE )
  {
    CAN_SET_NCR_GLOBAL(CAN_NODE_NUM, ( C_NCR_CCE | C_NCR_INIT | C_NCR_FDEN )); /* SBSW_CAN_LL01 */
  }
  else
  #endif
  {
  CAN_SET_NCR_GLOBAL(CAN_NODE_NUM, ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL01 */
  }
  /* delete all pending interrupts */
  for (canllidx=0; canllidx < CAN_MAX_PND_REG; canllidx++)
  {
  #if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
    CAN_SET_MSPND(canllidx, ~Can_GetGlobalInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllidx)); /* SBSW_CAN_LL03 */
  #else
    CAN_SET_MSPND(canllidx, ~CanInterruptPendingMask[canHwChannel].GlobalMask[canllidx]); /* SBSW_CAN_LL03 */
  #endif
  }
  CAN_SET_NSR(CAN_NODE_NUM, (vuint16)0x00); /* delete status include busoff (C_NSR_ALERT) */ /* SBSW_CAN_LL01 */
  CAN_SET_NECnt_Rec(CAN_NODE_NUM, (vuint8)0x00); /* SBSW_CAN_LL01 */
  CAN_SET_NECnt_Tec(CAN_NODE_NUM, (vuint8)0x00); /* SBSW_CAN_LL01 */
  CAN_SET_NECnt_EWRNLVL(CAN_NODE_NUM, (vuint8)96); /* SBSW_CAN_LL01 */
  /* delete all pending polling flags (and status) */
  for ( objHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); objHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); objHandle++ )
  {
    CAN_SET_MoCtrL( objHandle, (C_MOCTR_TXPND | C_MOCTR_TXEN0)); /* delete pending and enable */ /* SBSW_CAN_LL06 */
  }
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
  for ( objHandle = CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel); objHandle < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel); objHandle++ )
  {
    CAN_SET_MoCtrL( objHandle, (C_MOCTR_RXPND | C_MOCTR_NEWDAT)); /* delete pending flag */ /* SBSW_CAN_LL06 */
  }
  #endif
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  for ( objHandle = CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); objHandle < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); objHandle++ ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    CAN_SET_MoCtrL( objHandle, (C_MOCTR_RXPND | C_MOCTR_NEWDAT)); /* delete pending flag */ /* SBSW_CAN_LL06 */
  }
  #endif
  CanXC800GlobalInterruptRestore();
}

/****************************************************************************
| NAME:             CanHL_InitPowerOn
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitPowerOn
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOn(void)
{
  /* #10 HW general power on initialization (LL) */
  {
    CAN_CHANNEL_CANTYPE_LOCAL
    vuint8 canll_ch;
  #if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = 0;
  #endif
  # if defined (C_ENABLE_MULTIPLE_CELLS)
    canCellDbgPtr0 = (tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(CAN_MULTICAN); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
    canCellDbgPtr1 = (tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(CAN_MULTICANR); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # else
    canCellDbgPtr = (tCanCellStructPtr)kCanBaseAdr; /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # endif
  #if !defined(C_ENABLE_MULTIPLE_DRIVERS) /* COV_CAN_MULTIPLE_DRIVERS */
    CAN_SFR_PROTECT_OFF();
  #  if defined(C_ENABLE_MULTIPLE_CELLS)
    /* iterate CAN cells */
    for (canll_ch=0; canll_ch<2; canll_ch++)
    {
        CAN_SFR_PROTECT_WRITE16(((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(canll_ch))->Ctrl.CLC, C_CLC_START); /* start CAN-clock / disable sleep */ /* SBSW_CAN_LL03 */ /* PRQA S 303 */ /* MD_Can_303_LL_CastBaseAddress */
      canLLTempRead = canCellPtr->Ctrl.CLC; /* lint !e552  needed before write to fdr -> workaround */
  #   if defined(CanClockDividor) /* COV_CAN_CANCLOCKDIVIDOR */
  #    if defined(C_ENABLE_PROTECTED_MODE)
      CAN_SFR_PROTECT_WRITE32_PER_CELL(((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(canll_ch))->Ctrl.FDR, CanClockDividor, canll_ch); /* set dividor for baudrate-clock */ /* SBSW_CAN_LL03 */ /* PRQA S 303 */ /* MD_Can_303_LL_CastBaseAddress */
  #    else /* if C_ENABLE_PROTECTED_MODE not defined */
      CAN_SFR_PROTECT_WRITE32(((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(canll_ch))->Ctrl.FDR, CanClockDividor); /* set dividor for baudrate-clock */ /* SBSW_CAN_LL03 */ /* PRQA S 303 */ /* MD_Can_303_LL_CastBaseAddress */
  #    endif
  #   else /* if CanClockDividor not defined */
  #    if defined(C_ENABLE_PROTECTED_MODE)
      CAN_SFR_PROTECT_WRITE32_PER_CELL(((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(canll_ch))->Ctrl.FDR, CanClockDividor[0], canll_ch); /* preset dividor */ /* SBSW_CAN_LL03 */  /* PRQA S 303 */ /* MD_Can_303_LL_CastBaseAddress */
  #    else /* if C_ENABLE_PROTECTED_MODE not defined */
      CAN_SFR_PROTECT_WRITE32(((tCanCellStructPtr)Can_GetBaseAdrOfCellInfo(canll_ch))->Ctrl.FDR, CanClockDividor[0]); /* preset dividor */ /* SBSW_CAN_LL03 */  /* PRQA S 303 */ /* MD_Can_303_LL_CastBaseAddress */
  #    endif
  #   endif
    }
  #  else
    CAN_SFR_PROTECT_WRITE16(canCellPtr->Ctrl.CLC, C_CLC_START); /* start CAN-clock / disable sleep */ /* SBSW_CAN_LL03 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
    canLLTempRead = canCellPtr->Ctrl.CLC; /* lint !e552  needed before write to fdr -> workaround */
  #   if defined(CanClockDividor) /* COV_CAN_CANCLOCKDIVIDOR */
    CAN_SFR_PROTECT_WRITE32(canCellPtr->Ctrl.FDR, CanClockDividor); /* set dividor for baudrate-clock */ /* SBSW_CAN_LL03 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #   else
    CAN_SFR_PROTECT_WRITE32(canCellPtr->Ctrl.FDR, CanClockDividor[0]); /* preset dividor */ /* SBSW_CAN_LL03 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #   endif
  #  endif
    CAN_SFR_PROTECT_ON();
    /* Workaround for high frequency clock to ensure FDR write */
  # if defined(C_ENABLE_MULTIPLE_CELLS)
    CanLL_WaitForListReadyMultiple(CAN_CHANNEL_CANPARA_ONLY); /* reset list finished (< 50 Fsys-clk) */
  # else
    CanLL_WaitForListReady(CAN_CHANNEL_CANPARA_ONLY); /* reset list finished (< 50 Fsys-clk) */
  # endif
  #endif
  #if defined(C_ENABLE_MULTIPLE_DRIVERS) /* COV_CAN_MULTIPLE_DRIVERS */
    for (canll_ch=0; canll_ch < kCanNumberOfChannels; canll_ch++) 
    {
      /* deactivate all used channel and activate in CanInit() again */
      
  # if (CAN_SAFE_BSW == STD_ON)
      CAN_SET_NCR_GLOBAL((Can_GetNodeNum(canll_ch) & 0x07), ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL01 */
  # else 
      CAN_SET_NCR_GLOBAL(Can_GetNodeNum(canll_ch), ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL01 */
  # endif
    }
  #else
  # if defined (C_ENABLE_MULTIPLE_CELLS)
    for (canll_ch=0; canll_ch<Can_GetMaxHwNodeAmountOfCellInfo(CAN_MULTICAN); canll_ch++) 
    {   /* Reset List needs Init-mode for all nodes */
   /* deactivate all channels of MultiCAN and activate in CanInit() again */
      CAN_SET_NCR_CELL(CAN_MULTICAN, canll_ch, ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL13 */
    }
    for (canll_ch=0; canll_ch<Can_GetMaxHwNodeAmountOfCellInfo(CAN_MULTICANR); canll_ch++) 
    {   /* Reset List needs Init-mode for all nodes */
   /* deactivate all channels of MultiCANR and activate in CanInit() again */
      CAN_SET_NCR_CELL(CAN_MULTICANR, canll_ch, ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL13 */
    }
  # else
    for (canll_ch=0; canll_ch < CAN_MAX_NUM_NODE; canll_ch++) 
    {   /* Reset List needs Init-mode for all nodes */
      /* deactivate all channel and activate in CanInit() again */
  #  if (CAN_SAFE_BSW == STD_ON)
      CAN_SET_NCR_GLOBAL((canll_ch & 0x07), ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL01 */
  #  else 
      CAN_SET_NCR_GLOBAL(canll_ch, ( C_NCR_CCE | C_NCR_INIT )); /* SBSW_CAN_LL01 */
  #  endif
    }
  # endif
  # if defined (C_ENABLE_MULTIPLE_CELLS)
    CanLL_SetListCmdMultiple( CAN_CHANNEL_CANPARA_FIRST C_PAN_RESET_LIST);
    CanLL_WaitForListReadyMultiple(CAN_CHANNEL_CANPARA_ONLY); /* reset list finished (< 50 Fsys-clk) */
    CAN_SET_MCR_CELL( CAN_MULTICAN, C_MCR_INIT_CLOCK ); /* SBSW_CAN_LL12 */
  #  if defined( kCanMCRValue ) /* since MultiCAN+, 2 steps are necessary (first clear selection, second set new clock) */ /* COV_CAN_MCR */
    ApplCanWaitSetMCR();
    CAN_SET_MCR_CELL( CAN_MULTICAN, (vuint16)kCanMCRValue ); /* after all CCE are set */ /* SBSW_CAN_LL12 */
  #  endif
    CAN_SET_MCR_CELL( CAN_MULTICANR, C_MCR_INIT_CLOCK ); /* SBSW_CAN_LL12 */
  #  if defined( kCanMCRValue ) /* since MultiCAN+, 2 steps are necessary (first clear selection, second set new clock) */ /* COV_CAN_MCR */
    ApplCanWaitSetMCR();
    CAN_SET_MCR_CELL( CAN_MULTICANR, (vuint16)kCanMCRValue ); /* after all CCE are set */ /* SBSW_CAN_LL12 */
  #  endif
  # else
    CanLL_SetListCmd( CAN_CHANNEL_CANPARA_FIRST 0, 0, C_PAN_RESET_LIST);
    CanLL_WaitForListReady(CAN_CHANNEL_CANPARA_ONLY); /* reset list finished (< 50 Fsys-clk) */
    CAN_SET_MCR( C_MCR_INIT_CLOCK ); /* SBSW_CAN_LL03 */
  #  if defined( kCanMCRValue ) /* since MultiCAN+, 2 steps are necessary (first clear selection, second set new clock) */ /* COV_CAN_MCR */
    ApplCanWaitSetMCR();
    CAN_SET_MCR( (vuint16)kCanMCRValue ); /* after all CCE are set */ /* SBSW_CAN_LL03 */
  #  endif
  # endif
  #endif
    CanNumberOfMaxBasicCAN = 0;
  }
}

/****************************************************************************
| NAME:             CanHL_InitPowerOnChannelSpecific
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitPowerOnChannelSpecific
Relation_Context:
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOnChannelSpecific( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* #10 HW controller specific power on initialization (LL) */
  if ( Can_GetRxBasicHandleMax(channel) > CanNumberOfMaxBasicCAN ) /* COV_CAN_GENDATA_FAILURE */ 
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    CanNumberOfMaxBasicCAN = Can_GetRxBasicHandleMax(channel);
  }

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedBegin
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedBegin( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller; /* PRQA S 3199 */ /* MD_MSR_14.2 */
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle; /* PRQA S 3199 */ /* MD_MSR_14.2 */

  /* #10 HW reception handling begin (LL) */
  {
    V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    Can_HwHandleType localHrh; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #if defined( C_ENABLE_OVERRUN )
    vuint8 copy_cnt; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #endif
    vuint8 canPndReg; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    vuint32 canPndBit; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  # if defined(C_ENABLE_CAN_FD_FULL)
    canHwLoopRetValType canHwLoopRetVal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  # endif  
  #endif
  # if defined( C_ENABLE_OVERRUN )
    copy_cnt = 0;
  # endif
  
    for (localHrh = Can_GetRxBasicHandleStart(canHwChannel); localHrh < Can_GetRxBasicHandleStop(canHwChannel); localHrh++) /* SBSW_CAN_HL29 */ /* COV_CAN_GENDATA_FAILURE */
    {
      if ( (rxObjHandle >= Can_GetHwHandle(localHrh)) && (rxObjHandle < (CanObjectHandle)(Can_GetHwHandle(localHrh)+Can_GetDLC_FIFO(localHrh))) ) /* COV_CAN_GENDATA_FAILURE */
      {
        break;
      }
    }
  # if defined(C_ENABLE_CAN_FD_FULL)
    CAN_GET_MAILBOX_ADDRESS(rxObjHandle);
    if(Can_GetMaxDataLenOfMailbox(localHrh) > 8)  /* long data object, has no FIFO */ /* COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN */
    {
      canPndReg = (vuint8)(((vuint8)rxObjHandle) >> 5);
      canPndBit = (vuint32)1 << (rxObjHandle & 0x1Fu);
      CAN_GET_PMAILBOX_MoCtrL(rxBasicInfo->canMoCtrl); /* SBSW_CAN_LL11 */
      if( (rxBasicInfo->canMoCtrl & C_MOCTR_MSGVAL) == 0 ) /*MSGVAL will be deleted by HW after reception*/
      {
        CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_RXPND | C_MOCTR_NEWDAT); /* delete pending flag */ /* SBSW_CAN_LL06 */
        CAN_SET_MSPND(canPndReg, ~canPndBit);        /* delete pending interrupt */              /* SBSW_CAN_LL06 */  
        CAN_GET_PMAILBOX_MoARHi(TmpRxMailbox.MoARHi);  /* SBSW_CAN_LL10 */  /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #  if defined( C_ENABLE_EXTENDED_ID )
        CAN_GET_PMAILBOX_MoARLo(TmpRxMailbox.MoARLo);   /* SBSW_CAN_LL10 */
  #  endif
        CAN_GET_PMAILBOX_MoFCR_Mode(TmpRxMailbox.MoFCR_Mode);  /* SBSW_CAN_LL10 */
        CAN_GET_PMAILBOX_MoFCR_DLC(TmpRxMailbox.MoFCR_DLC);    /* SBSW_CAN_LL10 */
        CAN_GET_PMAILBOX_MoDR(TmpRxMailbox.MoDR);              /* SBSW_CAN_LL10 */ /* SBSW_CAN_LL10 */
        if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 8)
        {
          CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+1, &TmpRxMailbox.MoDR[2]); /* SBSW_CAN_LL18 */ 
        }
        if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 36)
        {
          CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+2, &TmpRxMailbox.MoDR[9]);  /* SBSW_CAN_LL18 */
        }
        CAN_SET_PMAILBOX_MoCtrH(C_MOCTR_MSGVAL); /* enable object */ /* SBSW_CAN_LL06 */
      }
      else
      {
        CanXC800GlobalInterruptDisable();
  #  if defined( C_ENABLE_HW_LOOP_TIMER )
        CanLL_ApplCanTimerStart(kCanLoopRx); /* SBSW_CAN_LL19 */
  #  endif
        do
        { /* repeat until consistent data , msgval should not be used here */
          CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_RXPND | C_MOCTR_NEWDAT); /* delete pending flag */ /* SBSW_CAN_LL06 */
          CAN_SET_MSPND(canPndReg, ~canPndBit);        /* delete pending interrupt */ /* SBSW_CAN_LL03 */
  #  if defined( C_ENABLE_OVERRUN )
          copy_cnt++;
  #  endif
          CAN_GET_PMAILBOX_MoARHi(TmpRxMailbox.MoARHi);  /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #  if defined( C_ENABLE_EXTENDED_ID )
          CAN_GET_PMAILBOX_MoARLo(TmpRxMailbox.MoARLo);   /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #  endif
          /* copy the EDL bit*/
          CAN_GET_PMAILBOX_MoFCR_Mode(TmpRxMailbox.MoFCR_Mode);  /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
          CAN_GET_PMAILBOX_MoFCR_DLC(TmpRxMailbox.MoFCR_DLC);    /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
          CAN_GET_PMAILBOX_MoDR(TmpRxMailbox.MoDR);              /* SBSW_CAN_LL10 */ /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
          if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 8)
          {
            CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+1, &TmpRxMailbox.MoDR[2]); /* SBSW_CAN_LL18 */
          }
          if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 36)      
          {
            CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+2, &TmpRxMailbox.MoDR[9]);  /* SBSW_CAN_LL18 */
          }
          CAN_GET_PMAILBOX_MoCtrL(rxBasicInfo->canMoCtrl); /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #  if defined( C_ENABLE_HW_LOOP_TIMER )
          canHwLoopRetVal = CanLL_ApplCanTimerLoop(kCanLoopRx);
        } while( ((rxBasicInfo->canMoCtrl & (C_MOCTR_NEWDAT | C_MOCTR_RXUPD)) != (vuint16)0x0000u) && (canHwLoopRetVal != kCanFailed) ); /* COV_CAN_NOT_STIMULATEABLE */
  #  else
        } while( (rxBasicInfo->canMoCtrl & (C_MOCTR_NEWDAT | C_MOCTR_RXUPD)) != (vuint16)0x0000u ); /* COV_CAN_NOT_STIMULATEABLE */
  #  endif
  #  if defined( C_ENABLE_HW_LOOP_TIMER )
        CanLL_ApplCanTimerEnd(kCanLoopRx); /* SBSW_CAN_LL19 */
  #  endif
  #  if defined( C_ENABLE_OVERRUN )
        if (copy_cnt > 1)  /* COV_CAN_DOUBLE_RECEPTION */
        {
          rxBasicInfo->canMoCtrl |= C_MOCTR_MSGLOST; /* set overrun bit */ /* SBSW_CAN_LL11 */
        }
  #  endif
        CanXC800GlobalInterruptRestore();
  #  if defined( C_ENABLE_HW_LOOP_TIMER )
        if(canHwLoopRetVal == kCanFailed) /* COV_CAN_HARDWARE_FAILURE */
        { /* do not proceed when data is inconsistent (no notification) */
          /* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
          goto finishBasicCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
        }
  #  endif
      }
    }
    else  /* FIFO handling */
  # endif  /*  # if defined(C_ENABLE_CAN_FD_FULL)       */
    {
      CanObjectHandle rxObjHandleActReadPtr;
  # if (CAN_RX_HW_FIFO_FULL_NOTIFICATION == STD_ON) /* COV_CAN_FIFO_FULL_NOTIFICATION */
      CanObjectHandle rxObjHandleCurPtr;
  # endif
      CanObjectHandle rxObjHandleBase;
      rxObjHandleBase = Can_GetHwHandle(localHrh);
      /* rxObjHandle of baseobject issues the reception */
      CAN_GET_MoFGPR_SEL(rxObjHandleBase, rxObjHandleActReadPtr);
  
      CAN_GET_MAILBOX_ADDRESS(rxObjHandleActReadPtr); /* COV_CAN_MULTIPLE_CELL_MASK */
  
      while((pCanCellMailbox->MoCtrL & C_MOCTR_RXPND) != C_MOCTR_RXPND)
      {
        /* increment the read pointer based on rxObjHandleBase */
        CanLL_IncSELPtr(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandleBase);
        /* read back actual read pointer */
        CAN_GET_MoFGPR_SEL(rxObjHandleBase, rxObjHandleActReadPtr);
        /* get mailbox adress of actual readmailbox */
        CAN_GET_MAILBOX_ADDRESS(rxObjHandleActReadPtr);  /* COV_CAN_MULTIPLE_CELL_MASK */
      }
      rxBasicInfo->rxObjHandle = rxObjHandleActReadPtr; /* needed for Overrun notification on main part of function CanBasicCanMsgReceived() */ /* SBSW_CAN_LL11 */
  # if defined(C_ENABLE_MULTIPLE_CELLS)
      if (Can_GetCellInfoIdxOfCell(canHwChannel) == CAN_MULTICANR) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        rxBasicInfo->rxObjHandle += CAN_MULTICANR_MSGOBJ_OFFSET; /* SBSW_CAN_LL11 */
      }
  # endif
      canPndReg = (vuint8)(rxObjHandleActReadPtr >> 5);
      canPndBit = (vuint32)1 << (rxObjHandleActReadPtr & 0x1Fu);
      CAN_GET_PMAILBOX_MoCtrL(rxBasicInfo->canMoCtrl); /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # if (CAN_RX_HW_FIFO_FULL_NOTIFICATION == STD_ON) /* COV_CAN_FIFO_FULL_NOTIFICATION */
      CAN_GET_MoFGPR_CUR(rxObjHandleBase, rxObjHandleCurPtr);
      if (rxObjHandleActReadPtr == rxObjHandleCurPtr)
      {
        ApplCanRxFiFoFull(canHwChannel);
      }
  # endif
      CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_RXPND | C_MOCTR_NEWDAT); /* delete pending flag */ /* SBSW_CAN_LL06 */
      CAN_SET_MSPND(canPndReg, ~canPndBit);        /* delete pending interrupt */ /* SBSW_CAN_LL03 */
      CAN_GET_PMAILBOX_MoARHi(TmpRxMailbox.MoARHi);   /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # if defined( C_ENABLE_EXTENDED_ID )
      CAN_GET_PMAILBOX_MoARLo(TmpRxMailbox.MoARLo);   /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # endif
  # if defined(C_ENABLE_CAN_FD_USED)
      CAN_GET_PMAILBOX_MoFCR_Mode(TmpRxMailbox.MoFCR_Mode); /* SBSW_CAN_LL15 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # endif
      CAN_GET_PMAILBOX_MoFCR_DLC(TmpRxMailbox.MoFCR_DLC);    /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      CAN_GET_PMAILBOX_MoDR(TmpRxMailbox.MoDR);              /* SBSW_CAN_LL10 */ /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      CanLL_IncSELPtr(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandleBase);
    }
  }

  /* #20 HW get mailbox pointer (LL) */
  (rxBasicInfo->rxInfo.pChipMsgObj) = pTmpRxMailboxMsg; /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */

  /* #30 HW get data pointer (LL) */
  (rxBasicInfo->rxInfo.pChipData)   = pTmpRxMailboxData; /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */

  retval = CAN_OK;
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
  goto finishBasicCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
finishBasicCan:
  return retval;
} /* PRQA S 6030 */ /* MD_MSR_STCYC*/

/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedSearch
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedSearch
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedSearch( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller;
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle;
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  /* #10 HRH Search linear (multiple BasicCAN) */
  for (rxBasicInfo->rxInfo.localHrh = Can_GetRxBasicHandleStart(canHwChannel); rxBasicInfo->rxInfo.localHrh < Can_GetRxBasicHandleStop(canHwChannel); rxBasicInfo->rxInfo.localHrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* SBSW_CAN_HL29 */ /* SBSW_CAN_HL29 */ /* COV_CAN_BASICCAN_SEARCH_LINEAR */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    if ( (rxObjHandle >= Can_GetHwHandle(rxBasicInfo->rxInfo.localHrh)) && (rxObjHandle < (CanObjectHandle)(Can_GetHwHandle(rxBasicInfo->rxInfo.localHrh)+Can_GetDLC_FIFO(rxBasicInfo->rxInfo.localHrh))) ) /* COV_CAN_BASICCAN_SEARCH_LINEAR */
    {
      retval = CAN_OK;
      break;
    }
  }
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedEnd
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivedEnd( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller; /* PRQA S 3199 */ /* MD_MSR_14.2 */
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle; /* PRQA S 3199 */ /* MD_MSR_14.2 */

  /* #10 HW release mailbox (LL) */

  CAN_DUMMY_STATEMENT(rxObjHandle);  /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller);   /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivePolling
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivePolling
Relation_Context:
RxBasicCANSupport, RxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivePolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_HwHandleType Htrh;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  { /* no global basic flag - only basic or n-fullcan availabel */
    /* #20 loop over all BasicCAN mailboxes */
    for (Htrh = Can_GetRxBasicHandleStart(canHwChannel); Htrh < Can_GetRxBasicHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
    { /* loop over all BasicCAN mailboxes with gap */ /* PRQA S 3201 */ /* MD_Can_3201 */
      for (rxObjHandle = Can_GetHwHandle(Htrh); rxObjHandle < (CanObjectHandle)(Can_GetHwHandle(Htrh) + Can_GetDLC_FIFO(Htrh)); rxObjHandle++)
      { /* over all BasicCAN mailbox HW (FIFO/Shadow) */
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
        /* #30 check individual polling flag */
        if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,rxObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
        { 
          /* #40 check mailbox pending flag */
          if( (CAN_RET_MoCtrL(rxObjHandle) & C_MOCTR_RXPND)==C_MOCTR_RXPND )
          { /* basic Rx is pending */
            /* #50 disable CAN interrupts \trace SPEC-1569, SPEC-3785 */
            Can_DisableControllerInterrupts((uint8)channel);
            /* #60 mailbox notification CanBasicCanMsgReceived() */
            CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
            /* #70 enable CAN interrupts */
            Can_EnableControllerInterrupts((uint8)channel);
          }
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedBegin
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedBegin( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->Controller;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #10 HW reception handling begin (LL) */
  {
    V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #if defined( C_ENABLE_FULLCAN_OVERRUN )  
    vuint8 copy_cnt; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #endif  
    vuint8 canPndReg; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    vuint32 canPndBit; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    canHwLoopRetValType canHwLoopRetVal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #endif  
    CAN_GET_MAILBOX_ADDRESS(rxObjHandle);
  #if defined( C_ENABLE_FULLCAN_OVERRUN )
    copy_cnt = 0;
  #endif
    canPndReg = (vuint8)(((vuint8)rxObjHandle) >> 5);
    canPndBit = (vuint32)1 << (rxObjHandle & 0x1Fu);
    CanXC800GlobalInterruptDisable();
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    CanLL_ApplCanTimerStart(kCanLoopRx); /* SBSW_CAN_LL19 */
  #endif
    do
    { /* repeat until consistent data , msgval should not be used here */
      CAN_SET_PMAILBOX_MoCtrL(C_MOCTR_RXPND | C_MOCTR_NEWDAT); /* delete pending flag */ /* SBSW_CAN_LL06 */
      CAN_SET_MSPND(canPndReg, ~canPndBit);        /* delete pending interrupt */ /* SBSW_CAN_LL03 */
  #if defined( C_ENABLE_FULLCAN_OVERRUN )
      copy_cnt++;
  #endif
      CAN_GET_PMAILBOX_MoARHi(TmpRxMailbox.MoARHi); /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #if defined( C_ENABLE_EXTENDED_ID )
      CAN_GET_PMAILBOX_MoARLo(TmpRxMailbox.MoARLo); /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #endif
      /* copy the EDL bit*/
  # if defined(C_ENABLE_CAN_FD_USED)
      CAN_GET_PMAILBOX_MoFCR_Mode(TmpRxMailbox.MoFCR_Mode); /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #endif
      CAN_GET_PMAILBOX_MoFCR_DLC(TmpRxMailbox.MoFCR_DLC);   /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      CAN_GET_PMAILBOX_MoDR(TmpRxMailbox.MoDR);             /* SBSW_CAN_LL10 */ /* SBSW_CAN_LL10 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  # if defined(C_ENABLE_CAN_FD_FULL)
      if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 8)
      {
        CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+1, &TmpRxMailbox.MoDR[2]);   /* SBSW_CAN_LL18 */
      }
      if(CAN_DECODE_DLI(TmpRxMailbox.MoFCR_DLC & C_DLC_M) > 36)      
      {
        CanLL_GetFdData(CAN_CHANNEL_CANPARA_FIRST rxObjHandle+2, &TmpRxMailbox.MoDR[9]);   /* SBSW_CAN_LL18 */
      }
  #endif  
      CAN_GET_PMAILBOX_MoCtrL(rxFullInfo->canMoCtrl); /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  #if defined( C_ENABLE_HW_LOOP_TIMER )
      canHwLoopRetVal = CanLL_ApplCanTimerLoop(kCanLoopRx);
    } while( ((rxFullInfo->canMoCtrl & (C_MOCTR_NEWDAT | C_MOCTR_RXUPD)) != (vuint16)0x0000u) && (canHwLoopRetVal != kCanFailed) ); /* COV_CAN_NOT_STIMULATEABLE */
  #else
    } while( (rxFullInfo->canMoCtrl & (C_MOCTR_NEWDAT | C_MOCTR_RXUPD)) != (vuint16)0x0000u ); /* COV_CAN_NOT_STIMULATEABLE */
  #endif
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    CanLL_ApplCanTimerEnd(kCanLoopRx); /* SBSW_CAN_LL19 */
  #endif
  #if defined( C_ENABLE_FULLCAN_OVERRUN )
    if (copy_cnt > 1) /* COV_CAN_HARDWARE_FAILURE */
    {
      rxFullInfo->canMoCtrl |= C_MOCTR_MSGLOST; /* set overrun bit */ /* SBSW_CAN_LL11 */
    }
  #endif
    CanXC800GlobalInterruptRestore();
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    if(canHwLoopRetVal == kCanFailed) /* COV_CAN_HARDWARE_FAILURE */
    { /* do not proceed when data is inconsistent (no notification) */
      /* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
      goto finishRxFullCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
    }
  #endif
  }
  
  /* #20 HW get mailbox pointer (LL) */
  (rxFullInfo->rxInfo.pChipMsgObj) = pTmpRxMailboxMsg; /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */

  /* #30 HW get data pointer (LL) */
  (rxFullInfo->rxInfo.pChipData) = pTmpRxMailboxData; /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */

  retval = CAN_OK;
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
  goto finishRxFullCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
finishRxFullCan:
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedSearch
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedSearch
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedSearch( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->channel;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #10 HRH Search linear */
  for (rxFullInfo->rxInfo.localHrh = Can_GetRxFullHandleStart(canHwChannel); rxFullInfo->rxInfo.localHrh < Can_GetRxFullHandleStop(canHwChannel); rxFullInfo->rxInfo.localHrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* SBSW_CAN_HL30 */ /* SBSW_CAN_HL30 */ /* COV_CAN_FULLCAN_SEARCH_LINEAR */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    if (Can_GetHwHandle(rxFullInfo->rxInfo.localHrh) == (Can_HwHandleType)rxObjHandle)
    {
      break;
    }
  }

  retval = CAN_OK;
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedEnd
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivedEnd( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->channel;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #10 HW release mailbox (LL) */

  CAN_DUMMY_STATEMENT(rxObjHandle);  /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller);   /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivePolling
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedEnd
Relation_Context:
RxFullCANSupport, RxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivePolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_HwHandleType Htrh;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  { /* no global basic flag - only basic or n-fullcan availabel */
    /* #20 loop over all FullCAN mailboxes */
    for (Htrh = Can_GetRxFullHandleStart(canHwChannel); Htrh < Can_GetRxFullHandleStop(canHwChannel); Htrh++ ) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      rxObjHandle = Can_GetHwHandle(Htrh);
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,rxObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      { /* #40 check mailbox pending flag */
        if( (CAN_RET_MoCtrL(rxObjHandle) & C_MOCTR_RXPND)==C_MOCTR_RXPND )
        {
          /* #50 disable CAN Interrupt \trace SPEC-1569, SPEC-3785 */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #60 mailbox notification CanFullCanMsgReceived() */
          CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
          /* #70 enable CAN Interrupt */
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxMsgReceivedNotification
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_RxMsgReceivedNotification
Relation_Context:
RxFullCANSupport, RxBasicCANSupport
Relation:
RxQueue, DevErrorDetect
RxQueue, CanFdSupport
RxQueue, GenericPreCopy, MirrorMode
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification( CAN_CHANNEL_CANTYPE_FIRST CanRxInfoPtrType rxInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined(C_ENABLE_RX_QUEUE) && (CAN_GENERIC_PRECOPY == STD_ON)
  Can_ReturnType generic_retval;
# endif
  uint8 errorId;
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 RX queue */
# if defined(C_ENABLE_RX_QUEUE)
  /**************************** RxQueue handling **********************************/
    /* #20 EXCLUSIVE_AREA_4 secure RxQueue data handling */
  Can_EnterCritical(CAN_EXCLUSIVE_AREA_4);
  if (Can_GetRxQueueInfo().Count < Can_GetSizeOfRxQueueBuffer()) /* COV_CAN_GENDATA_FAILURE */
  { /* #30 Queue not full: */
    /* #45 copy HRH, ID, DLC and data to RX queue */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).Hrh = rxInfo->localHrh; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).id  = rxInfo->localId; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).dlc = rxInfo->localDlc; /* SBSW_CAN_HL18 */

#  if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (canRxQueueMaxDataSize < rxInfo->localDlc) /* CM_CAN_HL17 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_DLC;
    }
    else
#  endif
    {

#  if defined(C_ENABLE_CAN_FD_FULL)
      /* #46 copy data with VStdLib optimized copy routine for CAN-FD messages (use alignment info) */
      VStdMemCpy((void*)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data, (void*)rxInfo->pChipData, rxInfo->localDlc); /* SBSW_CAN_HL19 */ /* PRQA S 0312 */ /* MD_Can_0312 */
#  else
      {
        uint8_least i;
        for (i = 0; i < rxInfo->localDlc; i++)
        {
          Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data[i] = CanRxActualData(rxInfo,i); /* SBSW_CAN_HL19 */
        }
      }
#  endif
    }
      /* #47 increase pointer to next queue element */
    Can_GetRxQueueInfo().Count++;
    if (Can_GetRxQueueInfo().WriteIndex < (uint16)(Can_GetSizeOfRxQueueBuffer() - 1) ) /* CM_CAN_HL24 */
    {
      Can_GetRxQueueInfo().WriteIndex++;
    }
    else
    {
      Can_GetRxQueueInfo().WriteIndex = 0; /* CM_CAN_HL24 */
    }
  }
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  else 
  { /* #50 Queue full: last message will be lost -> overrun in queue do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
    errorId = CAN_E_RXQUEUE;
  }
#  endif
  Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4);
# else /* C_ENABLE_RX_QUEUE */
  /* #100 no RX queue */
  /* -------------------------- Interface + APPL Notifications --- */
    /* #110 call Appl_GenericPrecopy() depend on configuration and if mirror mode is active */
#  if (CAN_GENERIC_PRECOPY == STD_ON)
#   if defined(C_ENABLE_MIRROR_MODE)
  if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
  { /* do not call Appl_GenericPrecopy() in case mirror mode was disabled */
    generic_retval = CAN_OK;
  }
  else
#   endif
  { /* \trace SPEC-3960 */
    generic_retval = Appl_GenericPrecopy((uint8)channel, (rxInfo->localId & CAN_ID_MASK_IN_GENERIC_CALLOUT), rxInfo->localDlc, (Can_DataPtrType)rxInfo->pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL06 */
  }
  if (generic_retval == CAN_OK) /* \trace SPEC-15119 */
#  endif
  { /* #120 call CanIf_RxIndication() if mirror mode is no active or Appl_GenericPrecopy() return OK \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
    CanIf_RxIndication(rxInfo->localHrh, rxInfo->localId, rxInfo->localDlc, (Can_DataPtrType)rxInfo->pChipData); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL07 */
  }
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}
#endif

#if defined(C_ENABLE_RX_QUEUE)
/****************************************************************************
| NAME:             CanHL_RxQueueExecution
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_RxQueueExecution
Relation_Context:
RxQueue
Relation:
GenericPreCopy, OneChOpt, CommonCan
GenericPreCopy, OneChOpt, DevErrorDetect
GenericPreCopy, MirrorMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxQueueExecution( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute RxQueue (over all channels) */
  while ( Can_GetRxQueueInfo().Count != (uint16)0 )
  { /* #20 over all filled RxQueue elements */
# if (CAN_GENERIC_PRECOPY == STD_ON)
    Can_ReturnType generic_retval;
    CAN_CHANNEL_CANTYPE_LOCAL
    generic_retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh);
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #30 Check controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#   endif
#  endif
#  if defined(C_ENABLE_MIRROR_MODE)
    if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
    { /* #40 MirrorMode: only when mirror is activated for this controller */
      generic_retval = CAN_OK;
    }
    else
#  endif
    { /* #50 call Appl_GenericPrecopy() */
      generic_retval = Appl_GenericPrecopy( (uint8)channel, /* PRQA S 2004 */ /* MD_Can_Asr_2004 */
                (Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id & CAN_ID_MASK_IN_GENERIC_CALLOUT),
                Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
                (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL06 */
    }
    if (generic_retval == CAN_OK)
# endif
    { /* #60 call CanIf_RxIndication() if Appl_GenericPrecopy() return OK or no generic precopy is used \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
      CanIf_RxIndication( Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh, /* SBSW_CAN_HL07 */
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id,
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
              (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL07 */
    }
    /* #70 EXCLUSIVE_AREA_4 secure RxQueue handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_4);
    /* #80 get next RxQueue element pointer */
    if (Can_GetRxQueueInfo().ReadIndex >= (uint16)(Can_GetSizeOfRxQueueBuffer() - 1) ) /* CM_CAN_HL25 */
    {
      Can_GetRxQueueInfo().ReadIndex = 0; /* CM_CAN_HL25 */
    }
    else
    {
      Can_GetRxQueueInfo().ReadIndex++;
    }
    Can_GetRxQueueInfo().Count--;
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4);
  }
  return errorId;
}
#endif

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/****************************************************************************
| NAME:             CanHL_TxTaskConfPendingHandling
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_TxTaskConfPendingHandling
Relation_Context:
TxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxTaskConfPendingHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  CanObjectHandle txObjHandle;
  {
    for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ )
    { /* #10 over all TX mailboxes */
# if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,txObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
# endif
      { /* #20 polling object? do individual polling */
        if( (CAN_RET_MoCtrL(txObjHandle) & C_MOCTR_TXPND)==C_MOCTR_TXPND ) /* lint !e737 */
        {
          /* #25 Lock CAN controller interrupts. (avoid nested call of confirmation (individual polling) and CancelTx interrupt confirmation out of Can interrupt like TP) */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #30 confirmation pending - do handling \trace SPEC-1574, SPEC-3779 */
          CanHL_TxConfirmation( CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }
}
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanHL_InitRxBasicCANSubSetMask
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE)  CanHL_InitRxBasicCANSubSetMask(CanInitInfoPtrType initInfo, Can_HwHandleType hwObjHandle, Can_HwHandleType Htrh)
{
  vuint8 canllmaskidx;
  CAN_CHANNEL_CANTYPE_LOCAL
  V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  canllmaskidx = (vuint8) ((vuint8)(Htrh-Can_GetRxBasicHandleStart(canHwChannel)) + (initInfo->initObject*CanNumberOfMaxBasicCAN));
  CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
  
  /* #10 Set acceptance mask and arbitration register */
# if defined( C_ENABLE_EXTENDED_ID )
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARLo, Can_GetInitCodeL(canllmaskidx) , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRLo, Can_GetInitMaskL(canllmaskidx) , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
#  if defined( C_ENABLE_MIXED_ID )
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, C_OBJ_PRIO_16 | Can_GetInitCodeH(canllmaskidx) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, Can_GetInitMaskH(canllmaskidx) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
#  else /* ext_id only */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, (C_OBJ_PRIO_16 | C_EID_MASK_16 | Can_GetInitCodeH(canllmaskidx)) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, C_EID_MASK_16 | Can_GetInitMaskH(canllmaskidx) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
#  endif 
# else /* std_id only */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, C_OBJ_PRIO_16 | Can_GetInitCodeH(canllmaskidx) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, C_EID_MASK_16 | Can_GetInitMaskH(canllmaskidx) , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
# endif          
}

/****************************************************************************
| NAME:             CanHL_InitRxBasicCANSubCloseMask
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE)  CanHL_InitRxBasicCANSubCloseMask(CanInitInfoPtrType initInfo, Can_HwHandleType hwObjHandle)
{
  V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif

  /* #10 Close the mask completly, no CAN ID will match */
  CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRHi, C_MOAMRHI_CLOSE , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoAMRLo, C_MOAMRLO_CLOSE , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARHi, C_OBJ_PRIO_16 , 0x3FFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
  initInfo->isMbCorrupt |= CanHL_SetValue16( CAN_CHANNEL_CANPARA_FIRST &pCanCellMailbox->MoARLo, 0x0000 , 0xFFFFU ); /* SBSW_CAN_LL07 */ /* SBSW_CAN_LL14 */
}
/* CODE CATEGORY 4 END */
#endif

#if defined(C_ENABLE_CAN_FD_FULL) 
/* CODE CATEGORY 2 START */
/****************************************************************************
| NAME:             CanLL_GetFdData
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetFdData(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle msgObjHandle, uint32* bufferPtr)
{
  uint8 index; 
  for (index = 0; index < 7; index++)
  {
    /* #10 copy extended data from FD frame into local buffer */
    bufferPtr[index] = ((CanFdMsgObjStructPtr) &canCellPtr->Obj[(uint8)(msgObjHandle & 0xFF)])->MoDR[index]; /* SBSW_CAN_LL18 */ /* PRQA S 310 */ /* MD_Can_0310 */
  }
}
/* CODE CATEGORY 2 END */
#endif
#if defined(C_ENABLE_CAN_INTERRUPT_CONTROL) /* COV_CAN_INTERRUPT_CONTROL */
/* CODE CATEGORY 2 START */

/****************************************************************************
| NAME:             CanLL_CanInterruptDisable
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CanChannelHandle  Controller, CanLLCanIntOldPtrType localInterruptOldFlagPtr)
{
#  if defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  *(localInterruptOldFlagPtr) = (CAN_SRC_PTR(canHwChannel) & C_ICR_IE_MASK); /* SBSW_CAN_LL17 */
  (void)osDisableInterruptSource(Can_GetIsrOsId(canHwChannel));
#  else
   /* #10 save actual global IR status */
  *(localInterruptOldFlagPtr) = CAN_SRC_PTR(canHwChannel); /* SBSW_CAN_LL17 */
  /* #20 disable global interrupts */
  CAN_SRC_PROTECT_RESET(CAN_SRC_PTR(canHwChannel), C_ICR_IE_MASK);  /* SBSW_CAN_LL09 */
#  endif  
}
/* CODE CATEGORY 2 END */

/* CODE CATEGORY 2 START */
/****************************************************************************
| NAME:             CanLL_CanInterruptRestore
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CanChannelHandle  Controller, tCanLLCanIntOld localInterruptOldFlag)
{
#  if defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  if(localInterruptOldFlag == C_ICR_IE_MASK) /* COV_CAN_TESTSUITE_NOT_APPLICABLE_WITH_LOCKED_IR */
  {
    (void)osEnableInterruptSource(Can_GetIsrOsId(canHwChannel), FALSE);
  }
#  else
  /* #10 enable global interrupt */
  CAN_SRC_PROTECT_SET(CAN_SRC_PTR(canHwChannel), ((localInterruptOldFlag) & C_ICR_IE_MASK)); /* SBSW_CAN_LL09 */
#  endif  
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_IsMailboxCorrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle)
{
  vuint8 canllidx;
  vuint8 ret_val;
  V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_GET_MAILBOX_ADDRESS(hwObjHandle);
  ret_val = kCanFalse;
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  canHwChannel = canHwChannel; /* dummy avoid lint warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  /* at this point the mailbox is not initialized therefore the contents are not saved! */
  {
    /* #10 Iterate test patterns */
    for(canllidx = 0; canllidx < 3; canllidx++)
    {
      vuint8  var_MoFCR_DLC;
      vuint16 var_MoARHi, var_MoARLo;
      vuint32 var_MoDR[2];
      CanXC800GlobalInterruptDeclare
      CanXC800GlobalInterruptDisable();
      /* write Id, Dlc, data registers with CanMemCheckValues..bit[canllidx] and verify the content */ 
      /* #20 DLC and IDE register check */
      CAN_SET_PMAILBOX_MoFCR_DLC(CanMemCheckValues8bit[canllidx]  & C_MOFCR_DLC); /* SBSW_CAN_LL06 */
      /* #30 ID register check */
      CAN_SET_PMAILBOX_MoARHi(CanMemCheckValues16bit[canllidx]);                  /* SBSW_CAN_LL06 */  
      CAN_SET_PMAILBOX_MoARLo(CanMemCheckValues16bit[canllidx]);                  /* SBSW_CAN_LL06 */
      CAN_GET_PMAILBOX_MoFCR_DLC(var_MoFCR_DLC);                                  /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      CAN_GET_PMAILBOX_MoARHi(var_MoARHi);                                        /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      CAN_GET_PMAILBOX_MoARLo(var_MoARLo);                                        /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      /* #40 Data register check */
      CAN_SET_PMAILBOX_MoDR(CanMemCheckValues2x32bit[canllidx]); /* PRQA S 310,311 */ /* MD_Can_0310, MD_Can_0311 */ /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL06 */
      /* #50 Check if register values are valid */
      CAN_GET_PMAILBOX_MoDR(var_MoDR);                                            /* SBSW_CAN_LL11 */ /* SBSW_CAN_LL11 */ /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
      if( (var_MoFCR_DLC != (CanMemCheckValues8bit[canllidx]  & C_MOFCR_DLC) ) ||
          (var_MoARHi    != CanMemCheckValues16bit[canllidx] )                 ||
          (var_MoARLo    != CanMemCheckValues16bit[canllidx] )                 ||
          (var_MoDR[0] != CanMemCheckValues2x32bit[canllidx][0])               ||
          (var_MoDR[1] != CanMemCheckValues2x32bit[canllidx][1]) )                  /* COV_CAN_HARDWARE_FAILURE */
      {
        ret_val = kCanTrue; /* the mailbox is corrupt */
        /* no break allowed by QAC */
      }
      CanXC800GlobalInterruptRestore();
    }
  }
  return(ret_val);
}
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_InitBeginIsRegisterCorrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 canRegistersRamCheckFailed;
  V_DEF_P2SFR_CAN(V_NONE, tCanNodeStruct, AUTOMATIC)     pCanCellNode;
  vuint8 canllidx;

  CanXC800GlobalInterruptDeclare
  CanXC800GlobalInterruptDisable();
  pCanCellNode = (CanNodeStructPtr) &canCellPtr->Node[CAN_NODE_NUM];

  canRegistersRamCheckFailed = CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &pCanCellNode->NCR,( C_NCR_CCE | C_NCR_INIT ), 0x0041 );  /* SBSW_CAN_LL14 */
  /* CANFD does not need to be considered here (RAM check), NCR and NBTR will be written later*/
  /* #10 Iterate test patterns */
  for(canllidx = 0; canllidx < 3; canllidx++)
  {
    vuint8  var_rec, var_tec, var_warn;
    vuint16 var_ncr, var_npcr, var_nipr, var_para;
    vuint32 var_msi;
#  if defined( C_ENABLE_CAN_FD_USED ) 
    vuint32 var_nbtr;
#  else
    vuint16 var_nbtr;
#  endif  
    /* #20 Write pattern to controller register */
    /* write control registers with CanMemCheckValues..bit[canllidx] and verify the content */ 
    /* NCR: bit0: do not change mode here, bit4: already init-mode do not set to avoid error-interrupt set, 
            bit5: read only, bit6-8 no mode change here, bit9-31 read only */
    CAN_SET_NCR(pCanCellNode->canllNode, (CanMemCheckValues16bit[canllidx] & 0x000EU) | C_NCR_CCE | C_NCR_INIT); /* SBSW_CAN_LL01 */
    /* NPCR: bit3-7,9-31: read only */
    CAN_SET_NPCR(pCanCellNode->canllNode, (CanMemCheckValues16bit[canllidx] & 0x0107U)); /* SBSW_CAN_LL01 */
    CAN_SET_NBTR(pCanCellNode->canllNode, (CanMemCheckValues16bit[canllidx] & 0xFFFFU)); /* SBSW_CAN_LL01 */
    CAN_SET_NECnt_Rec(pCanCellNode->canllNode, (CanMemCheckValues8bit[canllidx]  & 0xFFU)); /* SBSW_CAN_LL01 */
    CAN_SET_NECnt_Tec(pCanCellNode->canllNode, (CanMemCheckValues8bit[canllidx]  & 0xFFU)); /* SBSW_CAN_LL01 */
    CAN_SET_NECnt_EWRNLVL(pCanCellNode->canllNode, (CanMemCheckValues8bit[canllidx]  & 0xFFU)); /* SBSW_CAN_LL01 */
    CAN_SET_NIPR(pCanCellNode->canllNode, (CanMemCheckValues16bit[canllidx] & 0xFFFFU)); /* SBSW_CAN_LL01 */
    CAN_SET_PanPara( (CanMemCheckValues16bit[canllidx] & 0xFFFFU)); /* SBSW_CAN_LL03 */
    CAN_SET_MSIMask( (CanMemCheckValues32bit[canllidx] & 0xFFFFFFFFUL)); /* SBSW_CAN_LL03 */
    /* read back */
    CAN_GET_NCR(pCanCellNode->canllNode, var_ncr);
    /* NPCR: bit3-7,9-31: read only */
    CAN_GET_NPCR(pCanCellNode->canllNode, var_npcr);
    CAN_GET_NBTR(pCanCellNode->canllNode, var_nbtr);
    CAN_GET_NECnt_Rec(pCanCellNode->canllNode, var_rec);
    CAN_GET_NECnt_Tec(pCanCellNode->canllNode, var_tec);
    CAN_GET_NECnt_EWRNLVL(pCanCellNode->canllNode, var_warn);
    CAN_GET_NIPR(pCanCellNode->canllNode, var_nipr);
    CAN_GET_PanPara( var_para );
    CAN_GET_MSIMask( var_msi );
    /* #30 Check if register values are valid */
    if( (var_ncr  != ((CanMemCheckValues16bit[canllidx] & 0x000EU) | C_NCR_CCE | C_NCR_INIT)) ||
        (var_npcr != (CanMemCheckValues16bit[canllidx] & 0x0107U))                            ||
        (var_nbtr != (CanMemCheckValues16bit[canllidx] & 0xFFFFU))                            ||
        (var_rec  != (CanMemCheckValues8bit[canllidx]  & 0xFFU))                              ||
        (var_tec  != (CanMemCheckValues8bit[canllidx]  & 0xFFU))                              ||
        (var_warn != (CanMemCheckValues8bit[canllidx]  & 0xFFU))                              ||
        (var_nipr != (CanMemCheckValues16bit[canllidx] & 0xFFFFU))                            ||
        (var_para != (CanMemCheckValues16bit[canllidx] & 0xFFFFU))                            ||
        (var_msi  != (CanMemCheckValues32bit[canllidx] & 0xFFFFFFFFUL))  )  /* COV_CAN_HARDWARE_FAILURE */
    {
      canRegistersRamCheckFailed |= kCanTrue; /* the channel is corrupt */
    }
  
    /* excluded registers 
      "Node[].NSR"    (only write 0) 
      "Node[].NFCR"   (unused) 
      "Modul.MSPND"   (only write 0) 
      "Modul.List"    (read only) 
      "Modul.regMITR"    (unused) 
      "Modul.ID"      (unused) 
      "Modul.PanCmd"  (read only or combined with unwanted action)
      "Modul.MSID"    (read only)
      "Modul.MSIMask" (not channel specific)
    */
  } 
  /* #40 If FD is enabled, the Bittiming register differs regarding layout */
#  if defined( C_ENABLE_CAN_FD_USED ) 
  {
    vuint32 var_nbtr;
    for(canllidx = 0; canllidx < 3; canllidx++)
    {
      CAN_SET_NCR(pCanCellNode->canllNode, (CanMemCheckValues16bit[canllidx] & 0x000EU) | C_NCR_CCE | C_NCR_INIT | C_NCR_FDEN); /* SBSW_CAN_LL01 */
      CAN_SET_NBTR(pCanCellNode->canllNode, (CanMemCheckValues32bit[canllidx] & 0x0FDF8F3FUL)); /* SBSW_CAN_LL01 */
      CAN_GET_NBTR(pCanCellNode->canllNode, var_nbtr);
      if (var_nbtr != (CanMemCheckValues32bit[canllidx] & 0x0FDF8F3FUL))  /* COV_CAN_HARDWARE_FAILURE */
      {
        canRegistersRamCheckFailed |= kCanTrue; /* the channel is corrupt */
      }
    }
  }
#  endif    
  CanXC800GlobalInterruptRestore();
  return(canRegistersRamCheckFailed);
}
/* CODE CATEGORY 4 END */

# endif
#endif

#if defined( C_LL_INTERRUPT_ISR_ACTIVE ) /* ! pure polling configuration */
/* **************************************************************************
| NAME:             CanInterrupt( canHwChannel )
| CALLED BY:        CanIsr_<physicalChannelIndex>()
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt structure
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (BUSOFF, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an RX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   a wakeup has to be generated. 
|
|                   If an TX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be adapted to 
|                   really used name of the interrupt functions.
|
************************************************************************** */
#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterrupt( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanObjectHandle canllHwobj;
  vuint8  canllPndRegIdx;
  vuint8  canllPndReg;
  vuint32 canllPndRegBit;
# if !defined( C_ENABLE_ERROR_POLLING)
  vuint16 canllNSR;
  V_DEF_P2SFR_CAN(V_NONE, tCanNodeStruct, AUTOMATIC)     pCanCellNode;
# endif
# if !defined( C_ENABLE_ERROR_POLLING)
  pCanCellNode = (CanNodeStructPtr) &canCellPtr->Node[CAN_NODE_NUM];
# endif
# if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanInterrupt);
# endif

# if defined( C_ENABLE_NESTED_INTERRUPTS )
  CAN_ENABLE_GLOBAL_ISR();  /* nested on: enable Interrupts with higher priority (XC2000 higher prio ISR is always on) */ /* SBSW_CAN_LL21 */
# endif
  for (canllPndRegIdx=0; canllPndRegIdx<CAN_MAX_PND_REG; )
  { /* any pending in the pending-regs */
# if (defined( C_ENABLE_NESTED_INTERRUPTS ) ) 
    {
      CanDeclareGlobalInterruptOldStatus
      CanNestedGlobalInterruptDisable();
# endif
# if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
      CAN_SET_MSIMask( Can_GetGlobalInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllPndRegIdx) );/* lint !e662 */ /* SBSW_CAN_LL03 */
# else
      CAN_SET_MSIMask( CanInterruptPendingMask[canHwChannel].GlobalMask[canllPndRegIdx] );/* lint !e662 */                           /* SBSW_CAN_LL03 */
# endif      
      CAN_GET_MSID(canllPndRegIdx, canllPndReg);
# if (defined( C_ENABLE_NESTED_INTERRUPTS ) ) 
      CanNestedGlobalInterruptRestore();
    }
# endif
    if (canllPndReg != (vuint8)32) 
    {
      /* else found pending interrupt source */
      canllHwobj =  ((CanObjectHandle)canllPndReg + ((CanObjectHandle)canllPndRegIdx<<5)); /* calculate hwobject-index */
      canllPndRegBit = ((0x00000001UL)<<canllPndReg);                      /* calculate pending bit for mask */
# if defined(C_ENABLE_MULTIPLE_CELLS)
      if (Can_GetCellInfoIdxOfCell(canHwChannel) == CAN_MULTICANR) {
        canllHwobj += CAN_MULTICANR_MSGOBJ_OFFSET;
      }
# endif

      /***************** Tx-Interrupts ***********************************************/
# if !defined( C_ENABLE_TX_POLLING) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#  if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
      if ( (Can_GetTxInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllPndRegIdx) & canllPndRegBit) == canllPndRegBit )/* lint !e662 */ /* COV_CAN_ONLY_TX_INTERRUPT */
#  else
      if ( (CanInterruptPendingMask[canHwChannel].TxMask[canllPndRegIdx] & canllPndRegBit) == canllPndRegBit )/* lint !e662 */
#  endif      
      {
        CanXC800GlobalInterruptDeclare
        CanXC800GlobalInterruptDisable();
        CAN_SET_MSPND(canllPndRegIdx, ~canllPndRegBit); /* delete pending interrupt */ /* SBSW_CAN_LL03 */
        CanXC800GlobalInterruptRestore();
        CanHL_TxConfirmation(CAN_CHANNEL_CANPARA_FIRST canllHwobj);
      }
      else
# endif
      {
      /***************** RxFull-Interrupts ***********************************************/
# if defined ( C_ENABLE_RX_FULLCAN_OBJECTS ) && (!defined (C_ENABLE_RX_FULLCAN_POLLING) || defined( C_ENABLE_INDIVIDUAL_POLLING ))
#  if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
        if ( (Can_GetRxFullInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllPndRegIdx) & canllPndRegBit) == canllPndRegBit )/* lint !e662 */ /* COV_CAN_INDIVIDUAL_POLLING */
#  else
        if ( (CanInterruptPendingMask[canHwChannel].RxFullMask[canllPndRegIdx] & canllPndRegBit) == canllPndRegBit )/* lint !e662 */
#  endif        
        {
          CanFullCanMsgReceived( CAN_CHANNEL_CANPARA_FIRST canllHwobj );
        }
        else
# endif
        {
        /***************** RxBasic-Interrupts ***********************************************/
# if defined ( C_ENABLE_RX_BASICCAN_OBJECTS ) && (!defined (C_ENABLE_RX_BASICCAN_POLLING) || defined( C_ENABLE_INDIVIDUAL_POLLING ))
#  if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
          if ( (Can_GetRxBasicInterruptPendingMask((vuint8)(canHwChannel*CAN_MAX_PND_REG) + canllPndRegIdx) & canllPndRegBit) == canllPndRegBit )/* lint !e662 */ /* COV_CAN_INDIVIDUAL_POLLING */
#  else
          if ( (CanInterruptPendingMask[canHwChannel].RxBasicMask[canllPndRegIdx] & canllPndRegBit) == canllPndRegBit )/* lint !e662 */
#  endif          
          {
            CanBasicCanMsgReceived ( CAN_CHANNEL_CANPARA_FIRST canllHwobj );
          }
          else
# endif
          {
            CanXC800GlobalInterruptDeclare
            CanXC800GlobalInterruptDisable();
            CAN_SET_MSPND(canllPndRegIdx, ~canllPndRegBit); /* delete pending interrupt */ /* SBSW_CAN_LL03 */
            CanXC800GlobalInterruptRestore();
            Can_CallDetReportError(CAN_HW_ACCESS_ID, kErrorUnknownInterrupt);
          }
        }
      }
    } else {
      canllPndRegIdx++; /* no pending is found .. continue search */ /* PRQA S 2469 */ /* MD_Can_2469_LL_ISR */
    }
  }
# if !defined( C_ENABLE_ERROR_POLLING)
  {
    CanXC800GlobalInterruptDeclare
    CanXC800GlobalInterruptDisable();
    CAN_GET_NSR(CAN_NODE_NUM, canllNSR);
    CanXC800GlobalInterruptRestore();
    if ( (canllNSR & C_NSR_ALERT) == C_NSR_ALERT )
    { /* warning or busoff occure */
      /***************** Status-Interrupts *******************************************/
      CanXC800GlobalInterruptDisable();
      CAN_SET_NSR(CAN_NODE_NUM, (canllNSR & ((vuint16)~C_NSR_ALERT))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
      CanXC800GlobalInterruptRestore();
      CanHL_ErrorHandling(CAN_CHANNEL_CANPARA_ONLY);
    }
  }
# endif
# if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanInterrupt);
# endif
} /* end CanInterrupt */ /* lint !e550 */ /* PRQA S 6050,6080 */ /* MD_MSR_STCAL,MD_MSR_STMIF */
/* CODE CATEGORY 1 END */

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ISR necessary; no pure polling configuration*/

/****************************************************************************
| NAME:             CanLL_SetListCmd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_SetListCmd(CAN_HW_CHANNEL_CANTYPE_FIRST vuint8 node, Can_HwHandleType hwObjHandle,  vuint16 PanCmd )
{
  /* #10 Set command to configure the mailboxes */
  CanLL_WaitForListReady(CAN_CHANNEL_CANPARA_ONLY);
  CAN_SET_PanPara( (((vuint16)(node)) << 8) | ((vuint8)(hwObjHandle)) );  /* SBSW_CAN_LL03 */
  CAN_SET_PanCmd( PanCmd );                                               /* SBSW_CAN_LL03 */
}

#if defined(C_ENABLE_MULTIPLE_CELLS)
/****************************************************************************
| NAME:             CanLL_SetListCmdMultiple
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_SetListCmdMultiple(CAN_HW_CHANNEL_CANTYPE_FIRST vuint16 PanCmd )
{
  /* #10 Set command to configure the mailboxes if multiple CAN cells are active */
  CanLL_WaitForListReadyMultiple(CAN_CHANNEL_CANPARA_ONLY);
  CAN_SET_PanPara_CELL( CAN_MULTICAN, 0 ); /* SBSW_CAN_LL12 */
  CAN_SET_PanCmd_CELL( CAN_MULTICAN, PanCmd ); /* SBSW_CAN_LL12 */
  CAN_SET_PanPara_CELL( CAN_MULTICANR, 0 ); /* SBSW_CAN_LL12 */
  CAN_SET_PanCmd_CELL( CAN_MULTICANR, PanCmd ); /* SBSW_CAN_LL12 */
}
#endif

/****************************************************************************
| NAME:             CanLL_WaitForListReady
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WaitForListReady( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* #10 Wait until the CAN cell is ready to receive the next command */
  vuint16 regval16;    
#if defined( C_ENABLE_HW_LOOP_TIMER )
  CanLL_ApplCanTimerStart(kCanLoopListInit); /* lint !e722 */ /* SBSW_CAN_LL19 */
#endif
  do
  {
#if defined( C_ENABLE_HW_LOOP_TIMER )        
    if (CanLL_ApplCanTimerLoop(kCanLoopListInit)==0)   /* COV_CAN_HARDWARE_FAILURE */
    {
        Can_SetIsHardwareCanceled(channel, TRUE); /* SBSW_CAN_HL14 */
        break; /* lint !e722 */
    }
#endif      
    CAN_GET_PanCmd(regval16);
  }while ( (regval16 & C_PAN_BUSY)==C_PAN_BUSY ); /* COV_CAN_PANNEL_CMD */
#if defined( C_ENABLE_HW_LOOP_TIMER )          
   CanLL_ApplCanTimerEnd(kCanLoopListInit);  /* SBSW_CAN_LL19 */
#else
  CAN_DUMMY_STATEMENT(channel);
#endif  
}

#if defined(C_ENABLE_MULTIPLE_CELLS)
/****************************************************************************
| NAME:             CanLL_WaitForListReadyMultiple
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WaitForListReadyMultiple( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint16 regval16;
  vuint16 regval16R;
# if defined( C_ENABLE_HW_LOOP_TIMER )
  CanLL_ApplCanTimerStart(kCanLoopListInit); /* lint !e722 */ /* SBSW_CAN_LL19 */
# endif
  do
  {
# if defined( C_ENABLE_HW_LOOP_TIMER )        
    if (CanLL_ApplCanTimerLoop(kCanLoopListInit)==0)   /* COV_CAN_HARDWARE_FAILURE */
    {
        Can_SetIsHardwareCanceled(channel, TRUE); /* SBSW_CAN_HL14 */
        break; /* lint !e722 */
    }
# endif
    CAN_GET_PanCmd_CELL(CAN_MULTICAN, regval16);
    CAN_GET_PanCmd_CELL(CAN_MULTICANR, regval16R);
  } while ( ((regval16 & C_PAN_BUSY)==C_PAN_BUSY) || ((regval16R & C_PAN_BUSY)==C_PAN_BUSY) ); /* COV_CAN_PANNEL_CMD */
# if defined( C_ENABLE_HW_LOOP_TIMER )          
   CanLL_ApplCanTimerEnd(kCanLoopListInit); /* SBSW_CAN_LL19 */
# else
  CAN_DUMMY_STATEMENT(channel);
# endif  
}
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanLL_IncSELPtr
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_IncSELPtr( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle actHandle) /* COV_CAN_NO_RXFIFO */
{
  CanObjectHandle botValue;
  CanObjectHandle topValue;
  CanObjectHandle actValue;

  V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_GET_MAILBOX_ADDRESS(actHandle);
  
  /* #10 Increments the read pointer of the HW Rx FIFO  */
  CAN_GET_PMAILBOX_MoFGPR_TOP(topValue); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  CAN_GET_PMAILBOX_MoFGPR_SEL(actValue); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
  
  if( actValue == topValue)
  {
    CAN_GET_PMAILBOX_MoFGPR_BOT(botValue); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
    CAN_SET_PMAILBOX_MoFGPR_SEL((uint8)botValue); /* SBSW_CAN_HL06 */
  }
  else
  {
    CAN_SET_PMAILBOX_MoFGPR_SEL((uint8)(actValue+1)); /* SBSW_CAN_HL06 */
  }

# if !defined(C_ENABLE_MULTIPLE_CELLS)
  CAN_DUMMY_STATEMENT(canHwChannel);
# endif
}
#endif

/****************************************************************************
| NAME:             CanLL_Reset_MoCtr
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanLL_Reset_MoCtr( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask )
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_LL20 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint16 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (((uint16)~value) & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue;
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

/****************************************************************************
| NAME:             CanLL_Set_MoCtr
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanLL_Set_MoCtr( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask )
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_LL20 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint16 readBack;
    readBack = regPtr[-1];
    if ((readBack & readMask) != ((value) & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue;
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

#if (CAN_SAFE_BSW == STD_ON)
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_CheckGeneratedDataAccess()
****************************************************************************/
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
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckGeneratedDataAccess(CAN_CHANNEL_CANTYPE_ONLY)
{
  vuint8 error = CAN_E_NO_ERROR;
  CanChannelHandle physChannel = Can_GetNodeNum(canHwChannel);
  vuint8 physSrcIndex = Can_GetSrcNum(canHwChannel);
# if defined(C_ENABLE_MULTIPLE_CELLS)
  vuint8 secondCellNodeOffset;
  secondCellNodeOffset = (vuint8)((Can_GetCellInfoIdxOfCell(canHwChannel) == CAN_MULTICAN) ? 0 : 8);
  /* #10 Check if the Safe Mask is valid for both CAN cells in the case C_ENABLE_MULTIPLE_CELLS is defined. */
  if ((CAN_HWOBJ_SAFE_MASK(Can_GetMaxMailboxAmountOfCellInfo(CAN_MULTICAN)) != 0) || (CAN_HWOBJ_SAFE_MASK(Can_GetMaxMailboxAmountOfCellInfo(CAN_MULTICANR)) != 0)) /* COV_CAN_GENDATA_ERROR */
  {
    /* #20 The HW Object Index Safe Mask is not valid. The attribute MaxMailboxAmount of either or both CAN cells in Can_CellInfo are not a power of 2. */
    error = CAN_E_GENDATA;
  }
# endif
  /* #30 Check if the value of the accessed generated data is in the valid range for the current channel. */
# if defined(C_ENABLE_MULTIPLE_CELLS)
  if ((physChannel >= Can_GetMaxHwNodeAmountOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel))) || (physSrcIndex >= Can_GetMaxHwNodeAmountOfCellInfo(Can_GetCellInfoIdxOfCell(canHwChannel))))/* PRQA S 3356,3359 *//* COV_CAN_GENDATA_ERROR */
# else
  if ((physChannel >= CAN_MAX_HW_NODE_AMOUNT) || (physSrcIndex >= CAN_MAX_HW_NODE_AMOUNT))/* PRQA S 3356,3359 *//* COV_CAN_GENDATA_ERROR */
# endif
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      /* #40 If invalid value for the LogToPhys mapping is recognized set error. */
      error = CAN_E_GENDATA;
    }
# if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_MULTIPLE_CHANNEL_ADDITIONAL_CHECK */
#  if defined(CAN_USE_PHYSTOLOG_MAPPING)
  /* #50 Check if the mapping of the physical channels to the corresponding logical channels is correct. */
  else if(Can_GetPhysToLogChannel(physChannel) != canHwChannel) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_GENDATA_ERROR */
  {
    /* #60 If invalid value for the PhysToLog mapping is recognized set error. */
    error = CAN_E_GENDATA;
  }
#  else
  else
  {
    /* #70 Determine the physical channel to check and set an error if it is mapped to an invalid  logical channel. */
# if defined(C_ENABLE_MULTIPLE_CELLS)
    switch (physChannel + secondCellNodeOffset)
# else
    switch (physChannel)
# endif
    {
      case 0: /* PRQA S 3201 */  /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_0) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_0 != canHwChannel)  /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 1: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_1) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_1 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 2: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_2) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_2 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 3: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_3) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_3 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 4: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_4) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_4 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 5: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_5) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_5 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 6: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_6) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_6 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 7: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_7) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_7 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
#  if defined(C_ENABLE_MULTIPLE_CELLS)
      case 8: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_8) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_8 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 9: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_9) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_9 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 10: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_10) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_10 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 11: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_11) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_11 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 12: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_12) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_12 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 13: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_13) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_13 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 14: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_14) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_14 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
      case 15: /* PRQA S 3201 */ /* MD_Can_3201 *//* COV_CAN_CHANNEL_NOT_USED */
#   if defined(kCanPhysToLogChannelIndex_15) /* COV_CAN_CHANNEL_NOT_USED */
        if(kCanPhysToLogChannelIndex_15 != canHwChannel) /* COV_CAN_CHANNEL_NOT_USED */
#   endif
        {
          error = CAN_E_GENDATA;
        }
        break;
#  endif
      default: /* PRQA S 2018 *//* COV_CAN_GENDATA_ERROR */
        error = CAN_E_GENDATA;
        break;
    }
  }
#  endif
# endif
  return error;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif

/****************************************************************************
| NAME:             CanHL_TxConfirmation
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_TxConfirmation
Relation_Context:
Relation:
CommonCan
DevErrorDetect, TxPolling, OneChOpt
TransmitCancellationAPI
UseVectorCanIf, IfTxBuffer, GenericConfirmation
HwCancelTx
GenericConfirmation, MirrorMode
GenericConfirmation, IDType
HwCancelTx, TransmitCancellationAPI, DevErrorDetect
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_CanHL_TxConfirmation();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  /* #10 Check if parameter controller and txObjHandle is valid (only for Interrupt system, polling do this by caller) */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (((txObjHandle < CAN_HL_HW_TX_STARTINDEX(canHwChannel)) || (txObjHandle >= CAN_HL_HW_TX_STOPINDEX(canHwChannel)))) /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanObjectHandle logTxObjHandle;
    PduIdType tmp_pdu;
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
    uint8_least tmp_state;
#endif
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_ReturnType generic_retval;
#endif
#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    /* #100 EXCLUSIVE_AREA_3 needed to avoid another can_write while interface send out of queue (first send out of queue avoid inversion) or call GenericConfirmation2 (data consistency) */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_3);
#endif
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST (Can_HwHandleType)txObjHandle);
    {
      /* #120 Pre Release HW transmit object (LL) */
      /* set message object as free (invalid), Tx Pending reset, disable object */
      CAN_SET_MoCtrL(txObjHandle, (C_MOCTR_TXPND | C_MOCTR_TXEN0)); /* SBSW_CAN_LL06 */
      /* #130 Remember PDU for confirmation parameter */
      tmp_pdu   = Can_GetActiveSendPdu(logTxObjHandle);
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
      /* #140 Remember SEND STATE which may be modified due to new transmit call in indication */
      tmp_state = (uint8_least)Can_GetActiveSendState(logTxObjHandle);
#endif
      { /* #200 Set send state to free to allow next TX out of confirmation or direct (reload queue) */
        /* #210 Notify the application by call Appl_GenericConfirmation() and CanIf_TxConfirmation() */
        /*      - Appl_GenericConfirmation() if configured and mirror mode is active
                and afterwards depend of return value
                - CanIf_TxConfirmation() if generic confirmation return OK, or no generic is used, and TX is not cancelled */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1)
        Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
        if (Appl_GenericConfirmation( tmp_pdu ) == CAN_OK)
#elif defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
# if defined(C_ENABLE_MIRROR_MODE)
        if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
        { /* MirrorMode is inactive so call the following CanIf_TxConfirmation() */
          Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
          generic_retval = CAN_OK;
        }
        else
# endif
        { /* #230 For generic confirmation with API2 copy PDU data as parameter for Appl_GenericConfirmation() */
          Can_PduType canPdu;
          tCanTxInfoStruct canTxInfoStruct;
          
          # if defined(C_ENABLE_CAN_FD_FULL)
          /* If FD Full is enabled, a RAM buffer will be used to cache the whole payload data of this message,
            in order to store the FD message data in a continuous memory block */
          vuint8 canllidx;
          vuint8 messageLen;
          vuint8 tmpMirrorBuffer[64];
          V_DEF_P2SFR_CAN(volatile, tCanMsgObjStruct, AUTOMATIC) pCanCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
          V_DEF_P2SFR_CAN(volatile, tCanFdMsgObjStruct, AUTOMATIC) pCanFdCellMailbox; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
          
          CAN_GET_MAILBOX_ADDRESS(txObjHandle);
          messageLen = CAN_DECODE_DLI((pCanCellMailbox->MoFCR_DLC) & C_DLC_M);
          (canTxInfoStruct.pChipData) = (CanChipDataPtr) (&tmpMirrorBuffer[0]);
          for(canllidx=0; canllidx < 8; canllidx++)
          {
            tmpMirrorBuffer[canllidx] = ((CanChipDataSfrPtr) &pCanCellMailbox->MoDR[0])[canllidx]; /* PRQA S 310 */ /* MD_Can_0310 *//* SBSW_CAN_LL05 */
          }
          if (messageLen > 8)
          {
            pCanFdCellMailbox = (CanFdMsgObjStructPtr) &canCellPtr->Obj[(vuint8)(txObjHandle+1)]; /* PRQA S 310 */ /* MD_Can_0310 */
            for(canllidx = 8; canllidx < 36; canllidx ++)
            {
              tmpMirrorBuffer[canllidx] = ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-8]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
            }
            if (messageLen > 36)
            {
              pCanFdCellMailbox = (CanFdMsgObjStructPtr) &canCellPtr->Obj[(vuint8)(txObjHandle+2)]; /* PRQA S 310 */ /* MD_Can_0310 */
              for(canllidx = 36; canllidx < 64; canllidx ++)
              {
                tmpMirrorBuffer[canllidx] = ((CanChipDataSfrPtr) &pCanFdCellMailbox->MoDR[0])[canllidx-36]; /* PRQA S 310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL05 */
              }
            }
          }
          # else
          (canTxInfoStruct.pChipData) = ((CanChipDataPtr) (kCanBaseAdr + 0x200 + CAN_MAX_NODE*0x100 + ((vuint8)(txObjHandle))*32 + 0x10)); /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */ /* ESCAN00040099 */
          # endif
          (canTxInfoStruct.pChipMsgObj) = ((CanChipMsgPtr) (kCanBaseAdr + 0x200 + CAN_MAX_NODE*0x100 + ((vuint8)(txObjHandle))*32)); /* PRQA S 310,303,306 */ /* MD_Can_0310, MD_Can_0303_HWaccess, MD_Can_0303_HWaccess */ /* SBSW_CAN_LL11 */ 
          canPdu.sdu = (Can_SduPtrType)canTxInfoStruct.pChipData; /* PRQA S 0312 */ /* MD_Can_0312 */
          canPdu.length = CAN_DECODE_DLI(CanTxActualDLC((&canTxInfoStruct)));
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanTxActualIdType((&canTxInfoStruct)) == kCanIdTypeStd)
          { /* Mixed ID */
            canPdu.id = (Can_IdType)CanTxActualStdId((&canTxInfoStruct));
          }
          else
#  endif  /* pure Extended ID */
          { /* Extended ID */
            canPdu.id = (Can_IdType)(CanTxActualExtId((&canTxInfoStruct)) | CAN_ID_IDE_MASK);
          }
# else    /* Standard ID */
          canPdu.id = CanTxActualStdId((&canTxInfoStruct));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
          if ( CanTxActualFdType((&canTxInfoStruct)) == kCanFdTypeFd )
          {
            canPdu.id |= (Can_IdType)CAN_ID_FD_MASK;
          }
# endif
          canPdu.id &= CAN_ID_MASK_IN_GENERIC_CALLOUT;
          canPdu.swPduHandle = tmp_pdu;
          Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
          /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
          generic_retval = Appl_GenericConfirmation( (uint8)channel, &canPdu ); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL32 */
        }
        /* #300 Appl_GenericConfirmation() decide to call Indication */
        if (generic_retval == CAN_OK)
#else /* no generic confirmation */
        Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
#endif
        {
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
          /* #310 If TX is SW cancelled call CanIf_CancelTxNotification() */
          if (tmp_state == CAN_CANCEL_OBJ_SW) /* COV_CAN_CANCEL_SW_STIMULATION */
          {
            CanIf_CancelTxNotification( tmp_pdu, FALSE );
          }
          else
#endif  /* #320 otherwise call CanIf_TxConfirmation() */
          {
            CanIf_TxConfirmation( tmp_pdu ); /* \trace SPEC-1726, SPEC-1571 */
          }
        }
#if (defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)) && (CAN_TRANSMIT_BUFFER == STD_ON)
        /* #350 otherwise no CanIf_TxConfirmation() will be called so call CanIf_CancelTxNotification() just to notify IF to restart sending out of Queue */
        else
        {
# if (CAN_CANCEL_SUPPORT_API == STD_OFF)
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# else
          CanIf_CancelTxNotification( tmp_pdu, FALSE );
# endif
        }
#endif
      }
      /* #500 Post release HW transmit object (LL) */
    }

#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_3);
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  if (errorId != CAN_E_NO_ERROR) /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_TXCNF_ID, errorId);
  }
# endif
#endif
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CanHookEnd_CanHL_TxConfirmation();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanBasicCanMsgReceived
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanBasicCanMsgReceived
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, TxPolling, IndividualPolling
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxBasicInfoStruct rxBasicInfo;
  CanHookBegin_CanBasicCanMsgReceived();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  rxBasicInfo.Controller = Controller;
# endif
  rxBasicInfo.rxObjHandle = rxObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined(C_ENABLE_RX_BASICCAN_POLLING)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif 
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanHL_RxBasicMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanHL_RxBasicMsgReceivedBegin(&rxBasicInfo) == CAN_OK) /* SBSW_CAN_HL26 */ /* COV_CAN_RxBasicMsgReceivedBegin */
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* -------------------------- RAM check failed --- */
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
# if defined(C_ENABLE_OVERRUN)
        /* -------------------------- Overrun --- */
        if( (rxBasicInfo.canMoCtrl & C_MOCTR_MSGLOST) == C_MOCTR_MSGLOST )
        {
          {
            CanXC800GlobalInterruptDeclare   /* PRQA S 3334 */ /* MD_Can_3334_LL_IntDec */
            CanXC800GlobalInterruptDisable();
            CAN_SET_MoCtrL(rxBasicInfo.rxObjHandle, C_MOCTR_MSGLOST); /* delete overrun */  /* SBSW_CAN_LL06 */
            CanXC800GlobalInterruptRestore();
          }
          /* #40 Overrun occur so notify upper layer \trace SPEC-1686 */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanOverrun( (uint8)channel );
#   endif
        }
# endif
        /* \trace SPEC-1346 */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxBasicInfo.rxInfo.localDlc = CAN_DECODE_DLI(CanRxActualDLC((&rxBasicInfo.rxInfo)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&rxBasicInfo.rxInfo)) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxBasicInfo.rxInfo.localId = (Can_IdType)CanRxActualStdId((&rxBasicInfo.rxInfo));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxBasicInfo.rxInfo.localId = (Can_IdType)(CanRxActualExtId((&rxBasicInfo.rxInfo)) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxBasicInfo.rxInfo.localId = CanRxActualStdId((&rxBasicInfo.rxInfo));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&rxBasicInfo.rxInfo)) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxBasicInfo.rxInfo.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&rxBasicInfo.rxInfo)) != kCanFdTypeFd) && (rxBasicInfo.rxInfo.localDlc > 8)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
            /* -------------------------- Search HRH  --- */
            /* #130 search HRH for the given rxObjHandle CanHL_RxBasicMsgReceivedSearch() */
            if (CanHL_RxBasicMsgReceivedSearch(&rxBasicInfo) == CAN_OK) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* SBSW_CAN_HL26 */ /* COV_CAN_GENDATA_FAILURE */
            {
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_BASICCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING))
              /* #140 Check HRH is BasicCAN (already checked in polling task - do it only for interrupt) */
              if ( (rxBasicInfo.rxInfo.localHrh < Can_GetRxBasicHandleStart(canHwChannel)) || /* PRQA S 3356,3355,3358 */ /* MD_Can_13.7 */
                   (rxBasicInfo.rxInfo.localHrh >= Can_GetRxBasicHandleStop(canHwChannel)) )  /* PRQA S 3355 */ /* MD_Can_13.7 */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
              {
                errorId = CAN_E_PARAM_HANDLE;
              } 
              else
#  endif
# endif
              /* #145 DLC is not bigger than expected length from mailbox (MAX over all BasicCAN msg) */
              if (rxBasicInfo.rxInfo.localDlc > CAN_MAX_DATALEN_OBJ(rxBasicInfo.rxInfo.localHrh)) /* ESCAN00084263 */ /* PRQA S 3201 */ /* MD_Can_3201 */ /* COV_CAN_HARDWARE_FAILURE */
              {
                errorId = CAN_E_PARAM_DLC;
              }
              else
              {
                /* -------------------------- Notification --- */
                /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
                errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &rxBasicInfo.rxInfo); /* SBSW_CAN_HL26 */
              }
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxBasicMsgReceivedEnd() */
    CanHL_RxBasicMsgReceivedEnd(&rxBasicInfo); /* SBSW_CAN_HL26 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CanHookEnd_CanBasicCanMsgReceived();
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanFullCanMsgReceived
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanFullCanMsgReceived
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, TxPolling, IndividualPolling
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxFullInfoStruct rxFullInfo;
  CanHookBegin_CanFullCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  rxFullInfo.Controller = channel;
# endif
  rxFullInfo.rxObjHandle = rxObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanHL_RxFullMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanHL_RxFullMsgReceivedBegin(&rxFullInfo) == CAN_OK) /* SBSW_CAN_HL27 */ /* COV_CAN_RxFullMsgReceivedBegin */
    {
  /* -------------------------- RAM check failed --- */
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
        /* -------------------------- Overrun --- */
# if defined(C_ENABLE_FULLCAN_OVERRUN)
        if( (rxFullInfo.canMoCtrl & C_MOCTR_MSGLOST) == C_MOCTR_MSGLOST )
        {
          {
            CanXC800GlobalInterruptDeclare   /* PRQA S 3334 */ /* MD_Can_3334_LL_IntDec */
            CanXC800GlobalInterruptDisable();
            CAN_SET_MoCtrL(rxObjHandle, C_MOCTR_MSGLOST); /* delete overrun */ /* SBSW_CAN_LL06 */
            CanXC800GlobalInterruptRestore();
          }
          /* #40 Overrun occur so notify upper layer */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* \trace SPEC-1686 */ /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanFullCanOverrun( (uint8)channel );
#   endif
        }
# endif
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxFullInfo.rxInfo.localDlc = CAN_DECODE_DLI(CanRxActualDLC((&rxFullInfo.rxInfo)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&rxFullInfo.rxInfo)) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID*/
            rxFullInfo.rxInfo.localId = (Can_IdType)CanRxActualStdId((&rxFullInfo.rxInfo));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxFullInfo.rxInfo.localId = (Can_IdType)(CanRxActualExtId((&rxFullInfo.rxInfo)) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxFullInfo.rxInfo.localId = CanRxActualStdId((&rxFullInfo.rxInfo));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&rxFullInfo.rxInfo)) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxFullInfo.rxInfo.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
# endif
            /* -------------------------- Search HRH --- */
            /* #130 search HRH for the given rxObjHandle */
            if (CanHL_RxFullMsgReceivedSearch(&rxFullInfo) == CAN_OK) /* SBSW_CAN_HL27 */ /* COV_CAN_GENDATA_FAILURE */
            {
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_FULLCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)) /* COV_CAN_RX_FULLCAN_POLLING */
              /* #140 Check HRH is FullCAN (already checked in polling task - do it only for interrupt) */
              if ( (rxFullInfo.rxInfo.localHrh < Can_GetRxFullHandleStart(canHwChannel)) || /* PRQA S 3356,3355,3358 */ /* MD_Can_13.7 */
                   (rxFullInfo.rxInfo.localHrh >= Can_GetRxFullHandleStop(canHwChannel)) )  /* PRQA S 3355 */ /* MD_Can_13.7 */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
              {
                errorId = CAN_E_PARAM_HANDLE;
              }
              else
#  endif
# endif
              /* #145 DLC is not bigger than expected length from mailbox */
              if (rxFullInfo.rxInfo.localDlc > CAN_MAX_DATALEN_OBJ(rxFullInfo.rxInfo.localHrh)) /* ESCAN00084263 */ /* PRQA S 3201 */ /* MD_Can_3201 */ /* COV_CAN_HARDWARE_FAILURE */
              {
                errorId = CAN_E_PARAM_DLC;
              }
              else
              {
                /* -------------------------- Notification --- */
                /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
                errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &rxFullInfo.rxInfo); /* SBSW_CAN_HL27 */
              }
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxFullMsgReceivedEnd() */
    CanHL_RxFullMsgReceivedEnd(&rxFullInfo); /* SBSW_CAN_HL27 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CanHookEnd_CanFullCanMsgReceived();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_ErrorHandling
****************************************************************************/
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
 */
/*
|<DataModelStart>| CanHL_ErrorHandling
Relation_Context:
Relation:
CommonCan
DevErrorDetect, StatusPolling, OneChOpt
BusOffRecovery, OneChOpt
Overrun
DevErrorDetect
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_ERROR_POLLING) /* COV_CAN_ERROR_POLLING */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Pre Error handling (LL) */
    if( (Can_GetBusOffNotifiedOfControllerData(canHwChannel)==CANLL_FALSE) &&
        ((CAN_RET_NCR(CAN_NODE_NUM) & C_NCR_INIT)==C_NCR_INIT) &&
        (Can_GetHaltOfControllerData(canHwChannel)==CANLL_FALSE)  ) /* COV_CAN_BUSOFF_NOTIFICATION */
    { /* don't use busoff-flag here -> after resync deleted */
      Can_SetBusOffNotifiedOfControllerData(canHwChannel, CANLL_TRUE); /* lint !e661 */ /* SBSW_CAN_LL02 */
      /* #90 EXCLUSIVE_AREA_6 secure mode changes */
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_6);
      /* #100 BUSOFF occur -> ECU Manager restart Controller (no ResetBusOffStart/End needed) */
      Can_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */ /* attention: platform use this for BUSOFF 128*11 treatment!!! */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_BUSOFF); /* SBSW_CAN_HL02 */
#if !defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
      /* #110 CanResetBusOffStart need when BUSOFF handled by Application */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
      CanResetBusOffStart(channel, Can_GetLastInitObject(channel));
# else
      CanResetBusOffStart(Can_GetLastInitObject(channel));
# endif
#endif
      /* #115 Controller is in STOP mode after CanResetBusOffStart \trace SPEC-1578, SPEC-1664, SPEC-1663, SPEC-3828 */
      /* #120 Status changed to STOP - no more call of STOP from CAN Interface */
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6);
      /* #130 notify higher layer by call CanIf_ControllerBusOff() \trace SPEC-1726, SPEC-1578 */
      CanIf_ControllerBusOff((uint8)Can_GetCanToCanIfChannelMapping(channel));
    }
    /* #200 Post Error handling (LL) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*-------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CAN_VERSION_INFO_API == STD_ON) /* \trace SPEC-1716, SPEC-3964 */
/****************************************************************************
| NAME:             Can_GetVersionInfo
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_GetVersionInfo
Relation_Context:
VersionInfoApi
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo )
{ /* \trace SPEC-1723, SPEC-3881 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter versionInfo is an illegal null pointer \trace SPEC-1721, SPEC-3847 */
  if (VersionInfo == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  { /* #100 copy version info to given pointer parameter \trace SPEC-1717, SPEC-3845 */
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID   = CAN_VENDOR_ID; /* SBSW_CAN_HL10 */
    VersionInfo->moduleID   = CAN_MODULE_ID; /* SBSW_CAN_HL10 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
    VersionInfo->instanceID = CAN_INSTANCE_ID; /* SBSW_CAN_HL10 */
# endif
    VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION; /* SBSW_CAN_HL10 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_VERSION_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

/****************************************************************************
| NAME:             Can_InitMemory
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_InitMemory
Relation_Context:
Relation:
Variant
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void )
{ /* BR:011 */
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 mark driver as uninitialized \trace SPEC-1650, SPEC-3787 */
  canConfigInitFlag = CAN_STATUS_UNINIT;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
  /* #20 reset global configuration pointer */
  Can_ConfigDataPtr = NULL_PTR;
#endif /* otherwise constant pointer is used */
  /* #30 HW reset memory */
  /* only needed by ASR (and only if variables have to be initialized but will not be done in normal init) */
#if(CAN_DEV_ERROR_DETECT == STD_OFF)
  CAN_DUMMY_STATEMENT(canConfigInitFlag); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
/****************************************************************************
| NAME:             Can_InitStruct
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_InitStruct
Relation_Context:
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitStruct( uint8 Controller, uint8 Index )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller and index are valid */
  if ( (channel >= kCanNumberOfChannels) || (Index >= (uint8)(Can_GetInitObjectStartIndex(channel+1) - Can_GetInitObjectStartIndex(channel))) ) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  { /* #20 set initialization structure that should be used for next controller initialization. */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + Index)); /* SBSW_CAN_HL11 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON) && !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if ((CAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
/****************************************************************************
| NAME:             Can_ChangeBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ChangeBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20314 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId;
  retVal = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* explicit default as Issue - remove when baud rate fit */ /* \trace SPEC-20321 */
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-20338 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-20331 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-1655, SPEC-20312 */
    errorId = CAN_E_TRANSITION;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel+1); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 set baud rate and reinitialize controller to activate baud rate \trace SPEC-1669 */
        Can_SetLastInitObject(channel, (uint8)baudrateIndex); /* SBSW_CAN_HL11 */
        Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
        retVal = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHANGE_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif

# if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_CheckBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CheckBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20311 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId;
  retVal = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* \trace SPEC-20317 */
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT \trace SPEC-20328, SPEC-20318 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels )
  { /* \trace SPEC-20335 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel+1); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 requested baud rate is set - return OK */
        retVal = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHECK_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retVal;
}
# endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

# if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_SetBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{ /* \trace SPEC-50605 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  /* #5 return E_NOT_OK in case no fitting baudrate is found \trace-2622524 */
  retval = E_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-50595 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-50587 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-50584 */
    errorId = CAN_E_TRANSITION;
  }
  else
  if ( BaudRateConfigID >= (uint16)(Can_GetInitObjectStartIndex(channel+1) - Can_GetInitObjectStartIndex(channel)) )
  { /* \trace SPEC-50625, SPEC-50563 */
    errorId = CAN_E_PARAM_BAUDRATE;
  }
  else
#  endif
  { /* #50 set baud rate and reinitialize controller to activate baud rate */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + BaudRateConfigID)); /* SBSW_CAN_HL11 */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
    Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
#  endif
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */ /* \trace SPEC-50576, SPEC-50563, SPEC-50617 */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
    /* #60 check if hardware cancellation appear while mode change, so for the baud rate set is not successful \trace SPEC-60434 */
    if ( !Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
#  endif
    {
      retval = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SET_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* CAN_SET_BAUDRATE_API == STD_ON */
#endif /* only MSR403 */

/****************************************************************************
| NAME:             Can_Init
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_Init
Relation_Context:
Relation:
Variant, DevErrorDetect
PrecompileAndLinktimeCRCCheck
DevErrorDetect, Variant, CommonCan
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
RxQueue
Variant
OneChOpt
RamCheck
Wakeup
PnEnable
MirrorMode
SilentMode
ChangeBaudrate
UseVectorCanIf
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr )
{ /* \trace SPEC-1587, SPEC-3850, SPEC-3794, SPEC-1708, SPEC-3826, SPEC-3861 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_Init();
  errorId = CAN_E_NO_ERROR;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER) /* PostBuild (load+sel) */
  Can_ConfigDataPtr = ConfigPtr; /* \trace SPEC-1394, SPEC-1575 */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* PostBuildLoadable */
  if (ConfigPtr == NULL_PTR)
  { /* #10 EcuM null pointer configuration check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
  }
  else
#  if (CAN_FINALMAGICNUMBER == STD_ON) /* COV_CAN_FINALMAGICNUMBER */
  if (Can_GetFinalMagicNumber() != 20510u) /* COV_CAN_GENDATA_FAILURE */
  { /* #20 EcuM wrong magic number check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
#  endif
# else
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #30 Check if all parameters are valid \trace SPEC-1724, SPEC-3789 */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
  /* #40 Check wrong magic number */
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  /* not CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK --> not PostBuildLoadable so CAN_FINALMAGICNUMBER is always false */
#   else
  if (Can_GetFinalMagicNumber() != 0xaffeu) /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#   endif
#  endif
# endif
#else
  CAN_DUMMY_STATEMENT(ConfigPtr); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199, 3198 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
  ConfigPtr = Can_ConfigDataPtr; /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* CAN_ENABLE_USE_INIT_ROOT_POINTER */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag != CAN_STATUS_UNINIT)
  {
    /* #60 Check already initialized -> 2nd call is not allowed \trace SPEC-1712, SPEC-3934, SPEC-3767, SPEC-1722 */
    errorId = CAN_E_TRANSITION;
  }
  else
#endif
  if (  ( Can_GetBaseDll_GeneratorVersion()     != (uint16)CAN_GEN_BASE_VERSION ) ||  /* PRQA S 3325 */ /* MD_Can_3325 */
        ( Can_GetPlatformDll_GeneratorVersion() != (uint16)CAN_GEN_TricoreMulticanAsr_VERSION ) ) /* COV_CAN_GENDATA_FAILURE */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #70 EcuM generator and compatibility version check and notification */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* not for PostBuildSelectable */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
# else
    errorId = CAN_E_UNINIT;
# endif
#else
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0);
#endif
  }
  else
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if (CAN_CRC_CHECK == STD_ON)
  if (( Can_GetPrecompileCRC() != CAN_PRECOMPILE_CRC ) || ( Can_GetLinktimeCRC() != Can_LinktimeCRC )) /* COV_CAN_GENDATA_FAILURE */
  { /* #80 EcuM generator pre compile and link time CRC check and notification */
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0u);
  }
  else
# endif
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if CAN_DEV_ERROR_DETECT == STD_ON
#  if defined(CAN_ENABLE_SELECTABLE_PB) 
  if (
       (kCanNumberOfChannels > kCanNumberOfMaxUsedControllers) ||
       (kCanNumberOfUsedHwChannels > kCanNumberOfMaxUsedControllers) )
  { /* #90 check consistency of generated Data (real channel amount against maximum value) */
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    {
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
      Can_SignedHwHandleType tmp_objcnt;
      tmp_objcnt=0;
#endif
      canRxTaskActive = CAN_FREE;
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_INIT_ID;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_RX_QUEUE)
      /* #110 delete RxQueue (all channels) */
      Can_GetRxQueueInfo().WriteIndex = 0;  /* CM_CAN_HL24 */
      Can_GetRxQueueInfo().ReadIndex = 0;
      Can_GetRxQueueInfo().Count = 0;
      canRxQueueMaxDataSize = (uint16) (sizeof(Can_GetRxQueueBuffer(0).data) / sizeof(Can_GetRxQueueBuffer(0).data[0]));
#endif
      /* #120 Set active Identity */
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
      CanSetActiveIdentity(Can_GetIdentitySelected());
#endif
      /* #130 HW specific power on (LL) */
      CanHL_InitPowerOn();

      canConfigInitFlag = CAN_STATUS_INIT; /* \trace SPEC-1648, SPEC-3962, SPEC-3943 */ /* before Controller initialization begin */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
      for (channel = 0; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#endif
      { /* #132 for each controller */
#if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
        if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_FAILURE */
        { /* #134 not for inactive controller */
          continue; /* PRQA S 0770 */ /* MD_Can_0770 */
        }
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* generated as tool-table */
        /* #136 calculate logical TX handle (HW to log - done here because of multiple ECU) */
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetTxFullHwStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel)));
# else
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetHwHandle(Can_GetTxFullHandleStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel))));
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
        tmp_objcnt = (Can_SignedHwHandleType)(tmp_objcnt + (Can_SignedHwHandleType)Can_GetTxFullHandleMax(CAN_HL_HW_CHANNEL_STARTINDEX(channel)) + (Can_SignedHwHandleType)(Can_GetTxBasicHandleMax(CAN_HL_HW_CHANNEL_STARTINDEX(channel)) * CAN_MULTIPLEXED_TX_MAX));
# endif
#endif
        /* #140 initialize start up values for each controllers */
        Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK)
        Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_RAM_CHECK); /* execute power on RamCheck*/ /* SBSW_CAN_HL01 */
#endif
        Can_SetIsBusOff(channel, FALSE);  /* start up: no BUSOFF */ /* SBSW_CAN_HL08 */
        Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel))); /* SBSW_CAN_HL11 */
        Can_SetCanInterruptCounter(channel, 0); /* SBSW_CAN_HL12 */
#if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
        Can_SetTimeoutCall(channel,TRUE); /* SBSW_CAN_HL13 */
#endif
#if defined(C_ENABLE_MIRROR_MODE)
        Can_SetMirrorModeState(channel, CDDMIRROR_INACTIVE); /* SBSW_CAN_HL20 */
#endif
#if defined(C_ENABLE_SILENT_MODE)
        Can_SetSilentModeState(channel, CAN_SILENT_INACTIVE); /* SBSW_CAN_HL20 */
#endif
        /* #155 HW channel specific power on */
        CanHL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANPARA_ONLY);

        /* #160 set baud rate and initialize all CAN controllers \trace SPEC-1587, SPEC-1656, SPEC-3981 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
        Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(0));      /* use always first initStruct */ /* SBSW_CAN_HL03 */
#elif defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
        Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* set to STOP mode before set baud rate to avoid DET */ /* SBSW_CAN_HL02 */
# if (CAN_SET_BAUDRATE_API == STD_ON)
        (void)Can_SetBaudrate((uint8)channel, Can_GetCanControllerDefaultBaudrateIdx(CAN_HL_HW_CHANNEL_STARTINDEX(channel)));
# else
        (void)Can_ChangeBaudrate((uint8)channel, Can_GetCanControllerDefaultBaudrate(CAN_HL_HW_CHANNEL_STARTINDEX(channel))); /* \trace SPEC-15127 */
# endif
#else
# if !defined(CAN_USE_VECTOR_IF) 
        /* #170 call Can_InitController() - For Vector ASR3 this will be done within Can Interface */
        Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
#endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_Init();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_InitController
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_InitController
Relation_Context:
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
RamCheck
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
CommonCan
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
RamCheck
Wakeup
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr )
#elif defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerBaudrateConfigPtrType Config )
#elif  defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr )
#endif
{ /* \trace SPEC-1719, SPEC-1589, SPEC-1346, SPEC-1565, SPEC-3883 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_InitController();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Config pointer is valid and state is INIT \trace SPEC-3962 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1718, SPEC-3797 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1713, SPEC-3821 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  if (Config == NULL_PTR)
  { /* \trace SPEC-1711, SPEC-3774 */
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
#endif
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  /* #50 Check controller is in active ECU - otherwise nothing to do here */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 )  /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    tCanInitInfoStruct initInfo;
    /* #100 initialization controller states and initialization objects --- */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_SetLastInitObject(channel, (uint8)((uint8)Can_GetInitObjectStartIndex(channel) + (uint8)*Config)); /* SBSW_CAN_HL11 */
#endif
    initInfo.initObject = Can_GetLastInitObject(channel);
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
    initInfo.Controller = channel;
#endif
    initInfo.isChCorrupt = kCanFalse;
    /* #110 clean up status (do not activate communication and let SLEEP and initialization to detect ram-check request) */
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    { /* #112 standard RAM check will be performed so delete old status CAN_DEACTIVATE_CONTROLLER */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & CAN_STATUS_INIT);  /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #114 extended RAM check may be performed so delete old status except CAN_DEACTIVATE_CONTROLLER */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(CAN_DEACTIVATE_CONTROLLER | CAN_STATUS_INIT));  /* SBSW_CAN_HL02 */
    }
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
    canApiContext = CAN_INITCTR_ID;
#   endif
#  endif
# endif
#endif
    { /* #125 begin initialization CanHL_InitBegin() */
      {
        errorId = CanHL_InitBegin(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
      {
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
        /* #140 do TX FullCAN initialization CanHL_InitTxFullCAN()*/
        CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
        { /* do it only when no error occur before */
          errorId = CanHL_InitTxFullCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
        }
#endif
        /* #150 do TX BasicCAN initialization CanHL_InitTxBasicCAN() */
        CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
        { /* do it only when no error occur before */
          errorId = CanHL_InitTxBasicCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
        }
      } /* Common CAN:  TX only on first hwChannel */
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
      /* #170 do RX FullCAN initialization CanHL_InitRxFullCAN() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitRxFullCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#endif
#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
      /* #180 do RX BasicCAN initialization CanHL_InitRxBasicCAN() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitRxBasicCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#endif
      /* #190 end initialization CanHL_InitEnd_InitMode() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitEnd_InitMode(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      { 
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        /* #200 extended RamChecks new issue occur - notify corrupt register / deactivate controller */
        if (initInfo.isChCorrupt == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          CanIf_RamCheckCorruptController((uint8)Can_GetCanToCanIfChannelMapping(channel));
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
        }
# else
        if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        { /* #210 standard RAM check issue occur - call Appl_CanRamCheckFailed() */
          if (Appl_CanRamCheckFailed((uint8)channel) != CAN_DEACTIVATE_CONTROLLER)
          { /* #220 let the application decide if communication stay disabled as set by RAM check or not */
            Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* Application decide to activate communication in case RAM_CHECK failed */  /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
          }
        }
# endif
        CAN_RAM_CHECK_FINISHED_CTP(channel)
      }
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
      /* #230 no STOP transition for defect Controllers */
      if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
      {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        /* #250 BUSOFF, WAKEUP and Re-initialization lead direct to STOP mode, otherwise it is only a re-initialization with transition afterwards. */
        if ( (Can_GetStatusReq(channel) & CAN_REQ_INIT_NO_STOP) != CAN_REQ_INIT_NO_STOP ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        { /* #260 no more polling or notification, BUSOFF, WAKEUP notified before otherwise Re-initialization only allowed in STOP mode */
          Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
#endif
          /* #270 Switch to STOP mode CanHL_InitEnd_StopMode() */
          CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
          { /* do it only when no error occur before */
            errorId = CanHL_InitEnd_StopMode(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
          }
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP);  /* \trace SPEC-1657, SPEC-1647 set STOP */ /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        }
#endif
      }
    } /* end of loop over all HW channels */
    { /* #280 set controller init flag when no issue occure before */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | (CAN_STATUS_INIT)); /* SBSW_CAN_HL02 */
    }
#if defined(C_ENABLE_CAN_RAM_CHECK)
    Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_RAM_CHECK))); /* deactivate RamCheck - finished */ /* SBSW_CAN_HL01 */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ 
#endif
  } /* controller active in multiple ECU configuration */

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INITCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  CAN_DUMMY_STATEMENT(ControllerConfigPtr); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_InitController();
} /* PRQA S 6010,6050,6030,6080 */ /* MD_Can_Asr_STPTH,MD_MSR_STCAL,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_SetControllerMode
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_SetControllerMode
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
RamCheck
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
BusOffRecovery
ReInitStart
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{ /* \trace SPEC-1715, SPEC-3894 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_ReturnType retval;
  CanHookBegin_Can_SetControllerMode();
  retval = CAN_NOT_OK;  /* \trace SPEC-1407 */ /* For successful transition it is set explicit to CAN_OK */
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Transition is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1731, SPEC-3962, SPEC-3872 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1732 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    errorId = CAN_E_PARAM_CONTROLLER; /* \trace SPEC3874 */
  }
  else
# endif
#endif
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  /* #40 Check controller is in active ECU */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 ) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* only for active Controller */
#endif
  { /* #50 second level check (modes and transitions) only valid when controller is in active ECU and valid */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (!CanHL_IsControllerInit(channel))
    { /* #60 Check controller is initialized \trace SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
    if ((!CanHL_IsStop(channel)) && (Transition == CAN_T_START))
    { /* #70 Check No-STOP -> START-Req is invalid \trace SPEC-1637, SPEC-3862 */ /* ESCAN00073272 */
      errorId = CAN_E_TRANSITION;
    }
    else
# if (CAN_TRANSITION_CHECK == STD_ON)  /* ASR4 extension SREQ00000291 */ /* COV_CAN_USER_CONFIG */
    if ( ((!CanHL_IsStop(channel)) && (!CanHL_IsSleep(channel)) && ((Transition == CAN_T_WAKEUP) || (Transition == CAN_T_SLEEP))) ||
         ((CanHL_IsSleep(channel)) && (Transition == CAN_T_STOP)) )
    { /* #80 Check  No STOP Nor SLEEP -> SLEEP-Req   or   No SLEEP Nor STOP --> WAKEUP-Req   is invalid \trace SPEC-1654, SPEC-1649 */
      /* #90 Check  No START Nor STOP -> STOP-Req is invalid \trace SPEC-1652 */
      errorId = CAN_E_TRANSITION; /* trace SPEC-3862 */
    }
    else
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #95 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_6);
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_SETCTR_ID;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
      /* #110 reset flag that may be set in LL-initialization or HW-loop as notification that transition failed */
      Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
#endif
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #120 mark ongoing state change (suppress STOP transition in Can_InitController()) */ 
      Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_INIT_NO_STOP); /* SBSW_CAN_HL01 */
#endif
      /* #125 HW begin mode transition */
      switch(Transition)
      {
      case CAN_T_START: /* \trace SPEC-3963 */
        /* #200 Handle --- START --- transition */
#if !defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
        if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        { /* #210 BUSOFF occur so finish BUSOFF handling with CanResetBusOffEnd() */
          /* #215 reset BUSOFF flag - do this before CanResetBusOffEnd() so LL may overwrite it */
          Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
          CanResetBusOffEnd(channel, Can_GetLastInitObject(channel));
# else
          CanResetBusOffEnd(Can_GetLastInitObject(channel));
# endif
          /* #220 do not re-initialization after BUSOFF, this will be done while CanResetBusOffStart/End() */
        }
        else
#endif
        {
#if (CAN_REINIT_START == STD_ON) 
          /* #230 additional to STOP-transition-re initialization a Can_InitController() may be activated for START transition \trace SPEC-1730 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
          Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
          Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
          if ( Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
          { /* #240 break START transition when Can_InitContoller() failed */
            break;  /* PRQA S 3333 */ /* MD_Can_14.6 */
          }
#endif
        }
        /* #250 START: set request and wait limited time and notify upper Layer - CanHL_StartTransition() */
        retval = CanHL_StartTransition(CAN_CHANNEL_CANPARA_ONLY);
        break;

      case CAN_T_STOP: /* \trace SPEC-3976 */
        /* #300 Handle --- STOP --- transition */
        /* #310 ESCAN00032291: no call of STOP inside BUSOFF (avoid blocking) */
        if (!Can_IsIsBusOff(channel)) /* COV_CAN_HARDWARE_FAILURE */
        {
          /* #320 STOP: set request and wait limited time and notify upper Layer - CanHL_StopTransition() */
          retval = CanHL_StopTransition(CAN_CHANNEL_CANPARA_ONLY);
        } /* IsBusOff */
        break;

      case CAN_T_WAKEUP:
        /* #400 Handle --- WAKEUP --- transition */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* does not appear in MSR30 (synchronous) */ /* COV_CAN_MICROSAR_VERSION */
        if ( (Can_GetStatusReq(channel) & CAN_REQ_SLEEP) == CAN_REQ_SLEEP )
        { /* #410 ASR4: Check WAKEUP not allowed while transition to SLEEP \trace SPEC-1573, SPEC-1402, SPEC-1403, SPEC-3848, SPEC-1660 */
          errorId = CAN_E_TRANSITION;
        }
        else
#endif
        {
          /* #420 WAKEUP: set request and wait limited time and notify upper Layer (RAM-check, Emulated SLEEP handling) - CanHL_WakeupTransition() */
          retval = CanHL_WakeupTransition(CAN_CHANNEL_CANPARA_ONLY);
        }
        break;

      case CAN_T_SLEEP: /* \trace SPEC-3926, SPEC-1639 */
        /* #500 Handle --- SLEEP --- transition */
        /* #510 SLEEP: set request and wait limited time and notify upper Layer (Emulated SLEEP handling) - CanHL_SleepTransition() */
        retval = CanHL_SleepTransition(CAN_CHANNEL_CANPARA_ONLY);
        break; /* CAN_T_SLEEP */

      default: /* PRQA S 2018 */ /* MD_Can_Asr_2018 */
        /* #600 check unknown transition, return NOT_OK \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION; /* \trace SPEC-1733, SPEC-1407 */
        break;
      } /* switch */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #700 remove mark ongoing state change (suppress STOP transition in Can_InitController()) */ 
      Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
      if ( Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #705 while mode change a hardware cancellation appear and there for the mode change is not successful */
        Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
        /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION;
        retval = CAN_NOT_OK; /* \trace SPEC-3782, SPEC-3769 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        /* #710 ASR4: no more status polling - request failed */ 
        Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
# endif
      }
#endif
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SETCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_SetControllerMode();
  return retval;
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_DisableControllerInterrupts
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_DisableControllerInterrupts
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
IntLock, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1746, SPEC-3886 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1750, SPEC-3880, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1742, SPEC-3860 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #30 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1750, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1);
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
    canApiContext = CAN_DIINT_ID;
#   endif
#  endif
# endif
#endif
    if (Can_GetCanInterruptCounter(channel) == 0)
    { /* #110 Disable only when not disabled before (count nesting) \trace SPEC-1735, SPEC-1745, SPEC-3783 */
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      { /* #120 Disable CAN interrupt for each HW channel */
        CanLL_CanInterruptDisable(canHwChannel, &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_HL16 */
      }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      /* #130 Let application Disable CAN interrupt ApplCanInterruptDisable() */
      ApplCanInterruptDisable((uint8)channel);
#endif
    }
    Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel)+1); /* \trace SPEC-1748, SPEC-3875, SPEC-3876 */ /* SBSW_CAN_HL12 */
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_DIINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6050,6080 */ /* MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_EnableControllerInterrupts
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_EnableControllerInterrupts
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
IntLock, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1741, SPEC-3891 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-3866, SPEC-1739, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1752, SPEC-3858 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #30 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1739, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1);
    if (Can_GetCanInterruptCounter(channel) != 0)
    { /* #110 Enable only when disabled before (count nesting) \trace SPEC-1749, SPEC-1748, SPEC-3875 */
      Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel)-1); /* SBSW_CAN_HL12 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_ENINT_ID;
#   endif
#  endif
# endif
#endif
      if (Can_GetCanInterruptCounter(channel) == 0) /* \trace SPEC-1736, SPEC-1756, SPEC-3877 */
      {
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        { /* #120 Disable CAN interrupt for each HW channel */
          CanLL_CanInterruptRestore(canHwChannel, Can_GetCanInterruptOldStatus(canHwChannel));
        }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        /* #130 Let application Enable CAN interrupt ApplCanInterruptRestore() */
        ApplCanInterruptRestore((uint8)channel);
#endif
      }
    }
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_ENINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6050,6080 */ /* MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_Write
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_Write
Relation_Context:
Relation:
CommonCan
DevErrorDetect, MicrosarVersion
OneChOpt, CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
DevErrorDetect, TxFullCANSupport
DevErrorDetect, CanFdSupport
DevErrorDetect, MixedId
RamCheck
UseVectorCanIf
DevErrorDetect
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{ /* \trace SPEC-1751, SPEC-3887,   SPEC-1760, SPEC-1406 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  CanHookBegin_Can_Write();
  errorId = CAN_E_NO_ERROR;
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1759, SPEC-3864 */
    errorId = CAN_E_UNINIT;
  }
  else
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  if (Hth >= Can_GetSizeOfMailbox()) {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
#if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
    if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
    { /* #30 Check controller is in active ECU */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
    if (!CanHL_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1407, SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
    { /* \trace SPEC-1763, SPEC-3870 */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
    if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) && (PduInfo->length != 0)))
    { /* \trace SPEC-1761, SPEC-3868 */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# if !defined(C_ENABLE_CAN_FD_USED)
    if ( CanHL_IsFdMessage(PduInfo->id) )
    { /* no CAN_FD: Check parameter PduInfo->id should not have FD bit in ID */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    if ( ((PduInfo->length > 8) && (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)) ||
         (PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth)) ) /* COV_CAN_GENDATA_FAILURE */
         { /* \trace SPEC-1758, SPEC-3865 */
      /* \trace SPEC-60433 */ /* CAN_FD: Check parameter PduInfo->length is smaller than 9 for none FD configuration
         If development error detection for the CAN module is enabled and the CAN Controller is not in CAN FD mode (no CanControllerFdBaudrateConfig):
         The function Can_Write shall raise the error CAN_E_PARAM_DLC and shall return CAN_NOT_OK if the length is more than 8 byte.() */
      /* CAN_FD: Check parameter PduInfo->length against PDU maximum size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# else
    if ( PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth) ) /* CM_CAN_HL20 */
    { /* \trace SPEC-1758 */ /* Check parameter PduInfo->length against maximum buffer size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# endif
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PduInfo->id & (Can_IdType)CAN_ID_IDE_MASK) != (Can_IdType)CAN_ID_IDE_MASK ) && ( (PduInfo->id & (Can_IdType)CAN_ID_MASK) > (Can_IdType)CAN_ID_MASK_STD ) )
    { /* Check parameter PduInfo->id for STD ID is in STD range (EXT is always in range) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
    if ( (PduInfo->id & (Can_IdType)CAN_ID_UNUSED_MASK) != 0 )
    { /* Check parameter PduInfo->id contains illegal bits (e.g. bigger ID value than MAX for given type) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
#endif
    /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #150 reject deactivated mailbox (by RamCheck) */
    if (Can_GetMailboxState(Hth) == CAN_DISABLED_OBJ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      retval = CAN_NOT_OK;
    }
    else
#endif
    /* #180 check Hardware is in BUSOFF recovery state and is not able to handle a request: return BUSY \trace SPEC-1764 */
    if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      retval = CAN_NOT_OK; /* ESCAN00096369 */
    }
    else
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #200 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_HARDWARE_FAILURE */
#endif
    {
      CanObjectHandle  logTxObjHandle;
      /* #210 EXCLUSIVE_AREA_2: Interrupts may not be locked and re-entrant call may occur. */
      /*                        Time in between ID search and lock of mailbox is critical 
                                (only when no Vector Interface used otherwise CanIf EXCLUSIVE_AREA is used instead) 
                                Can_Write() could be called re-entrant, there for also for polling systems the interrupts have to be locked  
                                this is essential while check for mailbox is free (in between if (free) and set to not free) and save PDU handle */
#if !defined(CAN_USE_VECTOR_IF)
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_2);
#endif
      /* #220 search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary */
      logTxObjHandle = CanHL_WritePrepare(CAN_CHANNEL_CANPARA_FIRST Hth, PduInfo); /* SBSW_CAN_HL28 */
      /* #230 start transmission for given handle (if free) and return state */
      retval = CanHL_WriteStart(CAN_CHANNEL_CANPARA_FIRST Hth, logTxObjHandle, PduInfo); /* SBSW_CAN_HL28 */

#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
      /* avoid change of PDU information due to TX interrupt while changing */
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_2);
#endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_Write();
  return retval;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             ASR4.x - Can_CheckWakeup / ASR3.x - Can_Cbk_CheckWakeup
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CheckWakeup
Relation_Context:
Relation:
Wakeup, DevErrorDetect, OneChOpt
Wakeup, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
{ /* \trace SPEC-1740, SPEC-3922 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  retval = E_NOT_OK; /* \trace SPEC-1407 */
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Write
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_MainFunction_Write
Relation_Context:
Relation:
TxPolling, HwCancelTx, DevErrorDetect
TxPolling, HwCancelTx, OneChOpt
TxPolling, HwCancelTx, Variant
TxPolling, HwCancelTx, Wakeup
TxPolling, HwCancelTx, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void )
{ /* \trace SPEC-3873, SPEC-1766 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_TX_POLLING) 
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  CanHookBegin_Can_MainFunction_Write();
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_Write() */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3784, SPEC-1767,  SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-3962 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #60 do not access CAN hardware in SLEEP */
          {
# if defined(C_ENABLE_TX_POLLING) /* always true when no hw-cancel is supported */ /* COV_CAN_TX_POLLING TX */
            /* #100 do confirmation handling for pending mailboxes */
            CanHL_TxTaskConfPendingHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
          } /* CanHL_IsSleep */
        } /* end of loop over all HW channels */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif

#else
  CanHookBegin_Can_MainFunction_Write();
#endif /* C_ENABLE_TX_POLLING */
  CanHookEnd_Can_MainFunction_Write();
}

/****************************************************************************
| NAME:             Can_MainFunction_Read
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_MainFunction_Read
Relation_Context:
Relation:
DevErrorDetect
RxPolling, OneChOpt
RxPolling, Variant
RxPolling, DevErrorDetect
RxPolling, Wakeup
RxPolling, CommonCan
RxPolling, RxFullCANSupport
RxPolling, RxBasicCANSupport
RxQueue
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void )
{ /* \trace SPEC-3871, SPEC-1776 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_MainFunction_Read();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check Driver is initialized \trace SPEC-3841, SPEC-1784, SPEC-3852,  SPEC-3962 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  {
    errorId = CAN_E_UNINIT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  /* #20 semaphore to secure parallel access to RX buffers interrupt or polling \trace SPEC-1569, SPEC-3785 */
  if ( canRxTaskActive == CAN_FREE)  /* PRQA S 2004 */ /* MD_Can_Asr_2004 */
  {
#if defined(C_ENABLE_RX_POLLING) /* COV_CAN_RX_POLLING */
    CAN_CHANNEL_CANTYPE_LOCAL
#endif
    canRxTaskActive = CAN_BUSY; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if defined(C_ENABLE_RX_POLLING) /* \trace SPEC-1782, SPEC-3771 */ /* COV_CAN_RX_POLLING */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #30 iterate over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #60 Check controller is initialized \trace SPEC-3962 */
        errorId = CAN_E_UNINIT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #70 do not access CAN hardware in SLEEP */
          { /* #80 over all HW channel \trace SPEC-3814, SPEC-1774 */
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
            /* #90 search for all pending FullCAN mailbox objects and call notification */
            CanHL_RxFullMsgReceivePolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
            /* #100 search for all pending BasicCAN mailbox objects and call notification */
            CanHL_RxBasicMsgReceivePolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
          } /* CanHL_IsSleep */
        } /* end of loop over all HW channels */
      }
    }
#endif /* C_ENABLE_RX_POLLING */
#if defined(C_ENABLE_RX_QUEUE)
    /* #200 execute RxQueue CanHL_RxQueueExecution() */
    errorId |= CanHL_RxQueueExecution();
#endif
    canRxTaskActive = CAN_FREE;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_MainFunction_Read();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_BusOff
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_BusOff
Relation_Context:
Relation:
StatusPolling, DevErrorDetect
StatusPolling, OneChOpt
StatusPolling, Variant
StatusPolling, Wakeup
StatusPolling, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void )
{ /* \trace SPEC-1783, SPEC-3867 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_ERROR_POLLING) /* \trace SPEC-1778, SPEC-3818 */ /* COV_CAN_ERROR_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3835,  SPEC-1780, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-3962 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #60 do not access CAN hardware in SLEEP */
          { /* #70 loop over all HW controllers and call CanHL_ErrorHandling() \trace SPEC-1772, SPEC-3790 */
            /* #80 disable CAN interrupts */
            Can_DisableControllerInterrupts((uint8)channel);
            CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
            Can_EnableControllerInterrupts((uint8)channel);
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_BO_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#endif /* C_ENABLE_ERROR_POLLING */
}

/****************************************************************************
| NAME:             Can_MainFunction_Wakeup
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_MainFunction_Wakeup
Relation_Context:
Relation:
WakeupPolling, Wakeup, DevErrorDetect
WakeupPolling, Wakeup, OneChOpt
WakeupPolling, Wakeup, Variant
WakeupPolling, Wakeup, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void )
{ /* \trace SPEC-1770, SPEC-3885 */
  /* ----- Local Variables ---------------------------------------------- */
}

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/****************************************************************************
| NAME:             Can_MainFunction_Mode
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_MainFunction_Mode
Relation_Context:
Relation:
DevErrorDetect
OneChOpt
Variant
Wakeup
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Mode( void )
{ /* \trace SPEC-1775 */
  /* ----- Local Variables ---------------------------------------------- */
} /* PRQA S 6030,6050 */ /* MD_MSR_STCYC,MD_MSR_STCAL */

#endif

/****************************************************************************
| NAME:             Can_CancelTx
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_CancelTx
Relation_Context:
Relation:
TransmitCancellationAPI, CommonCan
TransmitCancellationAPI, DevErrorDetect
TransmitCancellationAPI, TxFullCANSupport
TransmitCancellationAPI, OneChOpt, CommonCan
TransmitCancellationAPI, DevErrorDetect, OneChOpt
TransmitCancellationAPI, DevErrorDetect, Variant
TransmitCancellationAPI, MultiplexedTx, TxFullCANSupport
TransmitCancellationAPI, MultiplexedTx, HwCancelTx
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
  /* ----- Local Variables ---------------------------------------------- */
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
  CAN_CHANNEL_CANTYPE_LOCAL
  Can_HwHandleType txObjHandle;
  CanObjectHandle logTxObjHandle;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  if (Hth >= Can_GetSizeOfMailbox())
  { /* #20 Check Hth is in range */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#  endif
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
  { /* #30 Check Hth is FullCAN or BasicCAN */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
# if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
# endif
    txObjHandle = Can_GetHwHandle(Hth);
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST txObjHandle);  
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #40 Check parameter controller is in range */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
    if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 ) /* COV_CAN_GENDATA_FAILURE */
    { /* #50 Check controller is in active ECU */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    { /* #60 Check parameter controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_IsControllerInit(channel))
    { /* #70 Check controller is initialized \trace SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      { /* #100 is BasicCAN */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) /* \trace SPEC-1677, SPEC-3957 */
        uint8_least muxTx;
        uint8_least muxTx_max;
        muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Hth); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        for (muxTx = 0; muxTx < muxTx_max; muxTx++)
# endif
        { /* #110 over all Multiplexed TX objects - search for handle */
          if (Can_GetActiveSendPdu(logTxObjHandle) == PduId)
          {
            if ((Can_GetActiveSendState(logTxObjHandle) == CAN_SEND_OBJ)
                )  /* COV_CAN_CANCEL_SW_STIMULATION */
            { /* #120 PDU found in active send list - handle found */
              Can_SetActiveSendState(logTxObjHandle, CAN_CANCEL_OBJ_SW); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
              /* #130 CANCEL_IN_HW is active - just suppress TX confirmation */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
              break;
# endif
            }
          }
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
          logTxObjHandle++;
          txObjHandle++;
# endif
        }
      }
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      else
      { /* #200 is FullCAN */
        if (Can_GetActiveSendPdu(logTxObjHandle) == PduId)
        {
          if ((Can_GetActiveSendState(logTxObjHandle) == CAN_SEND_OBJ)
             )  /* COV_CAN_CANCEL_SW_STIMULATION */
          { /* #210 mailbox to cancel is valid (PDU, handle, send state OK) */
            Can_SetActiveSendState(logTxObjHandle, CAN_CANCEL_OBJ_SW); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
            /* #220 CANCEL_FULLCAN_IN_HW is active - just suppress TX confirmation */
          }
        }
      }
# endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#else /* CAN_CANCEL_SUPPORT_API == STD_ON */
  CAN_DUMMY_STATEMENT(Hth); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(PduId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* CAN_CANCEL_SUPPORT_API == STD_ON */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_ResetBusOffStart
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ResetBusOffStart
Relation_Context:
Relation:
BusOffRecovery, DevErrorDetect, OneChOpt
BusOffRecovery, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffStart( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #60 do BUSOFF handling begin by call CanResetBusOffStart() - controller should be stopped afterwards but does not wait for bus transition here */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    CanResetBusOffStart(channel, Can_GetLastInitObject(channel));
# else
    CanResetBusOffStart(Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#else
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* ( BUSOFF_SUPPORT_API ) */
}

/****************************************************************************
| NAME:             Can_ResetBusOffEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ResetBusOffEnd
Relation_Context:
Relation:
BusOffRecovery, DevErrorDetect, OneChOpt
BusOffRecovery, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffEnd( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* #60 reset BUSOFF flag do this before CanResetBusOffEnd() so LL may overwrite it */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetIsBusOff(channel,FALSE); /* SBSW_CAN_HL08 */ 
    /* #70 do BUSOFF finish handling by call CanResetBusOffEnd() - controller should be re initialized afterwards */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    CanResetBusOffEnd(channel, Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
    CanResetBusOffEnd(Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#else
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* ( BUSOFF_SUPPORT_API ) */
}

#if (CAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_GetStatus
****************************************************************************/
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
 */
/*
|<DataModelStart>| Can_GetStatus
Relation_Context:
Relation:
CanGetStatus, CommonCan
CanGetStatus, DevErrorDetect, OneChOpt
CanGetStatus, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 canReturnCode;
  uint8 errorId;
  /* not used */
  errorId = CAN_E_NO_ERROR;
  canReturnCode = CAN_STATUS_INCONSISTENT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* not used */
    /* #100 set logical state as return value */
    canReturnCode = (uint8)Can_GetLogStatus(channel); /* PRQA S 3198 */ /* MD_MSR_14.2 */
    if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #150 set BUSOFF - BUSOFF can only happen on first HW channel (with TX objects) */
      canReturnCode |= CAN_STATUS_BUSOFF;
    }
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    {    
      if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #160 set Error Passive */
        canReturnCode |= CAN_STATUS_PASSIVE;
      }    
      if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #170 set Error Warning */
        canReturnCode |= CAN_STATUS_WARNING;
      }
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return (uint8)canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if defined(C_ENABLE_MIRROR_MODE)
/****************************************************************************
| NAME:             Can_SetMirrorMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetMirrorMode
Relation_Context:
MirrorMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_SetMirrorMode( uint8 Controller , CddMirror_MirrorModeType mirrorMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetMirrorModeState(channel, mirrorMode); /* SBSW_CAN_HL20 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#if defined(C_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             Can_SetSilentMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetSilentMode
Relation_Context:
SilentMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetSilentMode( uint8 Controller, Can_SilentModeType silentMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Std_ReturnType retVal;
  errorId = CAN_E_NO_ERROR;
  retVal = E_NOT_OK;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetSilentModeState(channel, silentMode); /* SBSW_CAN_HL20 */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return retVal;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             Can_RamCheckExecute
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckExecute
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckExecute( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 Do RamCheck by execute Can_InitController() with activated check */
    /* ----- Implementation ----------------------------------------------- */
    CanHL_DoRamCheck(CAN_CHANNEL_CANPARA_ONLY);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableMailbox
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckEnableMailbox
Relation_Context:
RamCheck
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableMailbox( Can_HwHandleType htrh )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
  if (htrh >= Can_GetSizeOfMailbox()) { /* CM_CAN_HL28 */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #15 disable controller to force reinitialization afterwards in Can_RamCheckEnableController() */
    Can_SetLogStatus(Can_GetMailboxController(htrh), CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL40 */
    /* #20 reactivate mailbox */
    Can_SetMailboxState(htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableController
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckEnableController
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableController( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {

    /* ----- Implementation ----------------------------------------------- */
    /* #30 activate controller only when currently disabled */
    if ( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      /* #40 call Can_InitController() to activate mailboxes and controller after RAM check issue */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER)));  /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
      Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
      Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: SPEC-1597, SPEC-3898, SPEC-3972 */
/* Currently no use-case / not supported: SPEC-1601, SPEC-3889, SPEC-1592, SPEC-1582 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Asr_Unused
Misra Rule Major
  Reason: Symbol not needed in each configuration or for each platform/derivative
  Risk: None
  Prevention: None

MD_Can_Asr_0781
Misra Rule 5.6
  Reason: Same name is used for same kind of data
  Risk: None
  Prevention: None

MD_Can_Asr_3408_libCheck
Misra Rule 8.8
  Reason: external linkage used for library check
  Risk: library check failed.
  Prevention: Integration test version check

MD_Can_Asr_3447
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_Asr_3408
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_Asr_3451
Misra Rule 8.8
  Reason: external linked symbol used in more than one file but should not be declared in header to prevent a external visibility
  Risk: different declaration of same object
  Prevention: possible conflicts checked by linker

MD_Can_Asr_3353_logTxobjHandle
Misra Rule 9.1
  Reason: Because CAN_MULTIPLEXED_TX_MAX is at least 1 the variable logTxobjHandle_use is always set before
  Risk: None
  Prevention: None

MD_Can_Asr_3353_CommonCanTransition
Misra Rule 9.1
  Reason: TransitionDone will be set depend on CommonCAN loop usage. Because CommonCAN loop will always be entered the value will be set.
  Risk: None
  Prevention: None

MD_Can_Asr_3418
Misra Rule 12.10
  Reason: comma operator in for-loop header used to get a compact code
  Risk: None
  Prevention: None

MD_Can_Asr_2018
Misra Rule 14.1
  Reason: default case is not necessary for all configurations
  Risk: None
  Prevention: None

MD_Can_Asr_3219
Misra Rule 14.1
  Reason: static function is not used depend on configuration aspect. No preprocessor used here to avoid unreadable code.
  Risk: None
  Prevention: None

MD_Can_Asr_2004
Misra Rule 14.10
  Reason: no default handling needed for if-else-if here
  Risk: missing default handling
  Prevention: Review

MD_Can_Asr_0881_abstract
Misra Rule 19.12
  Reason: Compiler abstraction need replacement of classes to avoid name conflict. Order of ## operator is irrelevant here.
  Risk: None
  Prevention: None

MD_Can_Asr_3689_MuxTx
Misra Rule 21.1
  Reason: muxTx index seems to be out of bounds for the array canTxBasicDataBuffer but it is limited to maximum size of array.
  Risk: None
  Prevention: Review

MD_Can_Asr_STPTH
Misra Metric STPTH
  Reason: control structure to evaluate ErrorId used sequential instead of nested to increase readability. PTH is 128 times lower than the worst case value from QAC.
  Risk: None
  Prevention: Review

MD_Can_3436:
Major
  Reason: Compatibility define used here.
  Risk: name conflict.
  Prevention: Code review and compiler check for name conflicts.

MD_Can_3199_dummy:
Redundancy
  Reason: Dummy assignment used to satisfy API parameters that are never used.
  Risk: None.
  Prevention: None.

MD_Can_0715:
Misra Rule 1.1
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0828:
Misra Rule 1.1
  Reason: Nesting of #if statements bigger than 8 depends on configuration aspects.
  Risk: Compiler does not support that.
  Prevention: Used Compilers checked and limitations form ANSI is not relevant.

MD_Can_0857:
Misra Rule 1.1
  Reason: Macros used to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0505:
Misra Rule 1.2
  Reason: Assertion prevents dereferencing a NULL pointer
  Risk: Undefined behaviour.
  Prevention: Code inspection.

MD_Can_0277_negation:
Misra Rule 3.1
  Reason: negation of an unsigned value used to mask bits.
  Risk: None.
  Prevention: None.

MD_Can_0277_invalid:
Misra Rule 3.1
  Reason: define a invalid value by use highest value of the given data type.
  Risk: None.
  Prevention: None.

MD_Can_3218:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used only once, or defined global to improve overview.
  Risk: name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_Can_3207:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used or not once in this particular configuration.
  Risk: unnecessary RAM occupied.
  Prevention: Compiler optimize and check for name conflicts.
  
MD_Can_3408_extLinkage:
Misra Rule 8.8
  Reason: Declaration of generated data is only internal to restrict visibility
  Risk: None.
  Prevention: None.

MD_Can_3447:
Misra Rule 8.8
  Reason: This appears only in internal test configurations.
  Risk: Symbolic conflict for other module.
  Prevention: -
  
MD_Can_3684:
Misra Rule 8.12
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3760_LogToHw:
Misra Rule 10.01
  Reason: Calculating hardware index out of logical need a negative value in calcuation, but result is always positive.
  Risk: Data access out of bounce.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_1281:
Misra Rule 10.6
  Reason: type of casting variable can be configured
  Risk: wrong size of data type could be used
  Prevention: Code inspection.

MD_Can_0303_HWaccess:
Misra Rule 11.3
  Reason: Hardware access need pointer to CAN cell as volatile.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_0310:
Misra Rule 11.4
  Reason: cast increase performance here.
  Risk: pointer alignment does not fit and wrong memory is accessed.
  Prevention: Code inspection and component test.

MD_Can_0311:
Misra Rule 11.5
  Reason: Const pointer used only for read access. Same macro is used also for none const pointer.
  Risk: None.
  Prevention: None.

MD_Can_0312:
Misra Rule 11.5
  Reason: cast to none volatile pointer is ok here because usage of data is read only here.
  Risk: Upper Layer has to make sure that there is no write access to this data.
  Prevention: Documentation of API.

MD_Can_13.7:
Misra Rule 13.7
  Reason: Result or value is always true or false depend on configuration aspect and used platform specific implementation
  Risk: Incorrect platform specific return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3201:
Misra Rule 14.1
  Reason: Configuration or platform specific dependent unreachable code.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3325:
Misra Rule 14.1
  Reason: This control expression is always true or false depend on configuration aspect and used platform specific implementation.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.
  
MD_Can_3109:
Misra Rule 14.3
  Reason: Empty statements occur multiple times because macros used like functions, and configuration aspects may deactivate complete functionality.
  Risk: Functionality unexpected missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2001:
Misra Rule 14.4
  Reason: 'goto' statement used to optimize code (readability and runtime).
  Risk: Incorrect jump.
  Prevention: Code inspection.

MD_Can_0770:
Misra Rule 14.5
  Reason: 'continue' statement used to optimize code (readability and runtime).
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_14.6:
Misra Rule 14.6
  Reason: multiple break used for optimize code runtime
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_2006:
Misra Rule 14.7
  Reason: Multiple return path used to optimize code (readability and runtime).
  Risk: Return a function too soon.
  Prevention: Code inspection.

MD_Can_1330:
Misra Rule 16.4
  Reason: no impact on functionality, due to different configurations the function paramters can be different
  Risk: traceability could be diffcult 
  Prevention: Code inspection.
  
MD_Can_1334:
Misra Rule 16.4
  Reason: no impact on functionality, due to different configurations the function paramters can be different
  Risk: traceability could be diffcult 
  Prevention: Code inspection.
  
MD_Can_3673:
Misra Rule 16.7
  Reason: no change due to compatibility of the API
  Risk: data could be modified without intention
  Prevention: Code inspection.
  
MD_Can_17.4:
Misra Rule 17.4
  Reason: Pointer arithmetic used multiple times to optimize runtime.
  Risk: Access wrong memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0750:
Misra Rule 18.4
  Reason: Using union type to handel configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.
  
MD_Can_0759:
Misra Rule 18.4
  Reason: Using union type to handle configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.

MD_Can_3412:
Misra Rule 19.4
  Reason: Complex Macros with unrecognised code-fragment used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3458:
Misra Rule 19.4
  Reason:Complex Macros with unbraced code statement blocks used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3460:
Misra Rule 19.4
  Reason: void used as macro to get configuration specific API.
  Risk: Readability reduced.
  Prevention: Compile test.
  
MD_Can_0841:
Misra Rule 19.6
  Reason:undefine macro for compatibility reasons and re-usage of platform specific code.
  Risk: Meaning of macro is uncertain and may lead to wrong implementation.
  Prevention: Code inspection, compile tests and runtime tests.

MD_Can_3453:
Misra Rule 19.7
  Reason: Complex Macros used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_0850:
Misra Rule 19.8
  Reason: Macro argument is empty depend on usage of compiler abstraction.
  Risk: None.
  Prevention: Code inspection.

  MD_Can_3410:
Misra Rule 19.10
  Reason: Parameter used in structures that does not allow brackets
  Risk: None atomic parameter lead to compile errors
  Prevention: Used parameter is always atomic depend on usage

MD_Can_0342:
Misra Rule 19.13
  Reason: Glue operator used to abstract AuotSar compiler abstraction
  Risk: Only K&R compiler support glue operator
  Prevention: Compile test show whether compiler accept glue operator

MD_Can_0291:
Misra Rule 21.1
  Reason: "if" query prevents negative arithmetic result
  Risk: index of array could be negative and therefore undefined
  Prevention: Code inspection. 
  
MD_Can_3382:
Misra Rule 21.1
  Reason: "if" query prevents overflow arithmetic result
  Risk: index of array could exceed dimension (due to overflow) and therefore undefined
  Prevention: Code inspection.  
  
MD_Can_3689:
Misra Rule 21.1
  Reason: assertion prevents out of bound indexing
  Risk: undefined behaviour
  Prevention: Code inspection. Index cannot exceed the maximum dimension of the array.
  
MD_Can_3415:
Misra Rule 12.4
  Reason: the right hand operand is not compulsory to execute
  Risk: None
  Prevention: Code inspection. The lack of right hand operand execution cannot affect the following codes

MD_Can_3305_LL:
Major
  Reason: Pointer cast to stricter alignment is no problem here because it points to a aligned struct
  Risk: None.
  Prevention: None.

MD_Can_3334_LL_IntDec:
Misra Rule 5.2
  Reason: Nested declaration use same name because it is the same usage.
  Risk: None.
  Prevention: None

MD_Can_3218_LL_canCellPtr:
Misra Rule 8.7
  Reason: canCellDbgPtr is defined only for debug purpose and is therefor not used in code
  Risk: None
  Prevention: None

MD_Can_3408_LL_ISR:
Misra Rule 8.8
  Reason: No declaration need for interrupt service routine (direct added to interrupt vector by keyword)
  Risk: None
  Prevention: None

MD_Can_3408_LL_SFR:
Misra Rule 8.8
  Reason: No declaration need for special function register as intrinsic keyword
  Risk: None
  Prevention: None

MD_Can_3353_LL_checkInterruptPendingMask:
Misra Rule 9.1
  Reason: No additional check here, variable "checkInterruptPendingMask" is always initialized and dimension is not greater than CAN_MAX_PND_REG.
  Risk: Access unknown memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2469_LL_ISR:
Misra Rule 13.6
  Reason: Loop counter modified within loop context to improve runtime.
  Risk: Endless loop or not all interrupts handled.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3673_LL_CopyCan:
Misra Rule 16.7
  Reason: For compatibility reason the API use none const pointer.
  Risk: The data may be modified illegal.
  Prevention: User docu inform about usage.

MD_Can_3673_LL:
Misra Rule 16.7
  Reason: none const pointer used to avoid cast problems.
  Risk: Const data try to be modified, but does not work.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3372_LL_SrcOffset:
Misra Rule 21.1
  Reason: Offset for SRC register is calculated by subtract a generated value but value range for subtract is uncritical.
  Risk: Wrong register will be written.
  Prevention: Generation tool limit the possible values.
  
MD_Can_0883_LL_DoubleInclude
Misra Rule 19.15
  Reason: known QAC issue, #if - #elif - #else stucuture which issues this message.
  Risk: none
  Prevention: none

MD_Can_303_LL_CastBaseAddress
Misra Rule 11.3
  Reason: Intended to cast from address to a pointer
  Risk: none
  Prevention: none
*/

/****************************************************************************/
/*  Silent deviations                                                       */
/****************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CAN_HL01
 \DESCRIPTION Write access to CanStatusReq with controller as index. Controller index is checked against sizeof CanStatusReq in Can_SetControllerMode(), Can_RamCheckExecute(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL02
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller index is checked against sizeof CanLogStatus in Can_SetControllerMode(), CanHL_ErrorHandling(), Can_RamCheckEnableController(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL03
 \DESCRIPTION Call Can_InitController() with parameter configuration pointer, which is never been used within MSR403. Error directive ensures that preprocessor switch MSR403 is set in SafeBSW context.
 \COUNTERMEASURE \N The configuration pointer is never used in called function (only used for MSR401 to get data).

\ID SBSW_CAN_HL04
 \DESCRIPTION Write access to CanActiveSendState with logTxObjHandle as index. LogTxObjHandle is checked against size of ActiveSendObject in Can_CleanUpSendState(), CanHL_WritePrepare(), CanHL_InitTxFullCAN(), CanHL_InitTxBasicCAN(), CanHL_TxTaskCancelationHandling(), CanHL_TxConfirmation() and Can_CancelTx().
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL05
 \DESCRIPTION Write access to CanActiveSendPdu with logTxObjHandle as index. LogTxObjHandle is checked against size of ActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL06
 \DESCRIPTION Call Can_GenericPrecopy() with parameter data pointer. The data pointer is only used for read access and it is always a valid pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL07
 \DESCRIPTION Call CanIf_RxIndication() with parameter data pointer. The data pointer is only used for read access. Parameter is of type P2CONST in API.
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL08
 \DESCRIPTION Write access to CanIsBusOff with controller as index. Controller index is checked against sizeof CanIsBusOff in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL09
 \DESCRIPTION Write access to CanIsWakeup with controller as index. Controller index is checked against sizeof CanIsWakeup in CanHL_WakeUpHandling(), Can_CheckWakeup(), Can_InitController() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL10
 \DESCRIPTION Write access to VersionInfo pointer within function Can_GetVersionInfo()
 \COUNTERMEASURE \N caller of Can_GetVersionInfo() has to ensure that VersionInfo pointer is valid. (global description available)

\ID SBSW_CAN_HL11
 \DESCRIPTION Write access to CanLastInitObject with controller as index. Controller index is checked against sizeof CanLastInitObject in Can_InitStruct(), Can_ChangeBaudrate(), Can_SetBaudrate() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL12
 \DESCRIPTION Write access to CanInterruptCounter with controller as index. Controller index is checked against sizeof CanInterruptCounter in Can_Init(), Can_EnableControllerInterrupts() and Can_DisableControllerInterrupts()
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL13
 \DESCRIPTION Write access to CanTimeoutCall with controller as index. Controller index is checked against sizeof CanTimeoutCall in Can_Init(), Can_SetControllerMode() and Can_Mainfunction_Mode().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL14
 \DESCRIPTION Write access to CanIsHardwareCanceled with controller as index. Controller index is checked against sizeof CanIsHardwareCanceled in Can_Init(), Can_SetControllerMode(), Can_SetBaudrate() and ApplCanTimerLoop().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL15
 \DESCRIPTION Write access to CanLoopTimeout with controller and source as index. Controller index is checked against sizeof CanLoopTimeout.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL22]

\ID SBSW_CAN_HL16
 \DESCRIPTION Call CanLL_CanInterruptDisable() with parameter CanInterruptOldStatus as pointer (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL17
 \DESCRIPTION Call CanHL_SortlogTxObjHandlePrioList() with parameter logTxObjHandlePrioList as pointer (module local defined).
 \COUNTERMEASURE \N [CM_CAN_HL19]

\ID SBSW_CAN_HL18
 \DESCRIPTION Write access to CanRxQueueBuffer with queue write index. Write index is checked against size of CanRxQueueBuffer.
 \COUNTERMEASURE \R [CM_CAN_HL24]

\ID SBSW_CAN_HL19
 \DESCRIPTION Write access to CanRxQueueBuffer.data with queue write index and data index. Write index is checked against size of CanRxQueueBuffer. (see also generator CM_CAN_HL04 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_HL24]
                 \R [CM_CAN_HL17]

\ID SBSW_CAN_HL20
 \DESCRIPTION Write access to CanMirrorModeState with controller as index. Controller is checked against size of CanMirrorModeState.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL21
 \DESCRIPTION Write access to logTxObjHandlePrioList with muxTx as index. Index is checked against size of logTxObjHandlePrioList.
 \COUNTERMEASURE \R [CM_CAN_HL19]

\ID SBSW_CAN_HL22
 \DESCRIPTION Write access to CanTxBasicDataBuffer with controller, muxTx and dataByte as index. Controller Index is checked against size of CanTxBasicDataBuffer (first dimension). Second dimension is statically defined CAN_MULTIPLEXED_TX_MAX and given as user type in ComStackLib. Third dimension is checked against size of table.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL20]

\ID SBSW_CAN_HL23
 \DESCRIPTION Write access to CanActiveSendPduInfo with logTxObjHandle as index. LogTxObjHandle is checked against size of CanActiveSendPduInfo.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL24
 \DESCRIPTION Call Appl_GenericPreTransmit() with parameter PduInfoPtr_var pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL25
 \DESCRIPTION Call CanIf_CancelTxConfirmation() with parameter CanActiveSendPduInfo[logTxObjHandle] as pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL26
 \DESCRIPTION Call CanHL_RxBasicMsgReceivedBegin(), CanHL_RxBasicMsgReceivedSearch(), CanHL_RxMsgReceivedNotification() and CanHL_RxBasicMsgReceivedEnd() with parameter rxBasicInfo pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL27
 \DESCRIPTION Call CanHL_RxFullMsgReceivedBegin(), CanHL_RxFullMsgReceivedSearch(), CanHL_RxFullReceivedNotification() and CanHL_RxFullMsgReceivedEnd() with parameter rxFullInfo pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL28
 \DESCRIPTION Call CanHL_WritePrepare(), CanHL_WriteStart() and CanHL_WritePrepareCancelTx() with parameter PduInfo pointer secured by caller part of Can_Write() description.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL29
 \DESCRIPTION Write access to rxBasicInfo (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL30
 \DESCRIPTION Write access to rxFullInfo (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL31
 \DESCRIPTION Call Initialization subroutines with initInfo pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL32
 \DESCRIPTION Call Appl_GenericConfirmation with canPdu pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL33
 \DESCRIPTION Write access to CanBusOffCounter with controller as index. Controller index is checked against sizeof CanBusOffCounter in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL34
 \DESCRIPTION Write access to CanMailboxState with mailbox handle as index. Index secured by ComStackLib [CM_CAN_HL29] and [CM_CAN_HL30] and checked against size of CanMailboxState.
 \COUNTERMEASURE \R [CM_CAN_HL28]

\ID SBSW_CAN_HL35
 \DESCRIPTION Call with pointer to CAN cell register for write and read access.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL36
 \DESCRIPTION Write access to initInfo structure as pointer (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL37
 \DESCRIPTION Call GetElapsedValue with timer value pointers as parameter (module local defined).
 \COUNTERMEASURE \N The timer values are static and always valid.

\ID SBSW_CAN_HL38
 \DESCRIPTION Call GetCounterValue with timer value pointers as parameter. definition of kCanLoopXXX as index in LoopTimeout table is always smaller than the dimension of the table given as static user type in ComStackLib.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL39
 \DESCRIPTION Undefine preprocessor switch to stimulate user defined feature (only test purpose).
 \COUNTERMEASURE \N Redefinement activates a none documented feature.

\ID SBSW_CAN_HL40
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller is secured by qualified use-case CSL03 of ComStackLib.
 \COUNTERMEASURE \N [CM_CAN_HL02]

\ID SBSW_CAN_HL41
 \DESCRIPTION Write access to CanActiveSendState with logTxObjHandle as index. logTxObjHandle is temporary stored in a list of [1,3] elements where each element is initialized to a valid value and always written with size check before.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_LL01
\DESCRIPTION Access to a hardware register (Node section) of the CAN cell using a pointer.
\COUNTERMEASURE \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.
                \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative.
                \R A runtime check function CanLL_CheckGeneratedDataAccess() ensures the Node index is valid.

\ID SBSW_CAN_LL02
\DESCRIPTION Access to Can_Halt, Can_BusOffNotified.. with controller as index.
\COUNTERMEASURE \R A runtime check ensures that the data fields of Can_Halt, Can_BusOffNotified.. have sufficient sizes.

\ID SBSW_CAN_LL03
\DESCRIPTION Access to a hardware register (Global section) of the CAN cell using a pointer access.
\COUNTERMEASURE \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.
                \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative.

\ID SBSW_CAN_LL04
\DESCRIPTION Access to a CAN message object via object index.
\COUNTERMEASURE \N CAN_HWOBJ_SAFE_MASK is applied here to ensure the index not to exceed the range of message objects in this derivative.

\ID SBSW_CAN_LL05
\DESCRIPTION Copy data into CAN message object via Pointer pCanCellMailbox. The txObjHandle for calculating pCanCellMailbox is limited via CAN_HWOBJ_SAFE_MASK.
\COUNTERMEASURE  \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative
                 \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.

\ID SBSW_CAN_LL06
\DESCRIPTION Access to a CAN message object via txObjHandle/hwObjHandle and canCellPtr. txObjHandle/hwObjHandle is limited via CAN_HWOBJ_SAFE_MASK for calculation pCanCellMailbox.
\COUNTERMEASURE  \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative
                 \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.

\ID SBSW_CAN_LL07
\DESCRIPTION Write access to static structure via pointer initInfo.
\COUNTERMEASURE  \N Structure is static defined, write access to structure is ensured by compiler

\ID SBSW_CAN_LL08
\DESCRIPTION  Function call CanLL_Set_MoCtr() with a pointer to a CAN Mailbox register. The txObjHandle for calculating pCanCellMailbox is limited via CAN_HWOBJ_SAFE_MASK.
\COUNTERMEASURE  \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.
                 \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative

\ID SBSW_CAN_LL09
\DESCRIPTION Access to a interrupt source register
\COUNTERMEASURE  \S Verify that the generated address for the interrupt controller kCanSRCAdr matches.
                 \R A runtime check function CanLL_CheckGeneratedDataAccess() ensures the Src index is valid.

\ID SBSW_CAN_LL10
\DESCRIPTION Write access to TmpRxMailbox which is, dependent of configuration, a static buffer or a CAN message buffer. (Configuration: "CanSecureTempBuffer")
\COUNTERMEASURE \N In case of CanSecureTempBuffer, SBSW_CAN_LL03 becomes relevant, in case of RAM buffer, the compiler secures the access

\ID SBSW_CAN_LL11
\DESCRIPTION Write access to static variable rxBasicInfo/rxFullInfo
\COUNTERMEASURE \N The compiler secures the correct access

\ID SBSW_CAN_LL12
\DESCRIPTION Access to a hardware register (Global section) of the CAN cell using a pointer access derived by constant. This is only relevant if both CAN cells (MultiCAN and MultiCANR) are active.
\COUNTERMEASURE  \S Verify that entries BaseAdr and SrcAdr for the table Can_CellInfo match for the used derivative. The table must have 2 entries, the first for the MultiCAN cell, the second for the MultiCANE cell. 
                 \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.

\ID SBSW_CAN_LL13
\DESCRIPTION Access to a hardware register (Node section) of the CAN cell using a pointer access derived by constant.
\COUNTERMEASURE \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell.
                \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative and that the generated value defined with "Can_GetControllerMax"\
                matches the available number of CAN channels for the used derivative.

\ID SBSW_CAN_LL14
\DESCRIPTION Function call CanHL_SetValueXX() with a pointer to a CAN Node/Mailbox register.
\COUNTERMEASURE \T TCASE-448:Code inspection ensures that the defined access structures match the memory structure of the CAN cell and that the fitting\
                             SetValueXX() function is called to ensure that the pointer destination is accessed with the correct size.
                \S Verify that the generated address for the CAN cell kCanBaseAdr/kCanSRCAdr matches for the used derivative

\ID SBSW_CAN_LL15
\DESCRIPTION Write access to structure TmpRxMailbox.
\COUNTERMEASURE \T TCASE-448:Code inspection ensures that structure elements MoFCR_Mode of the two types tCanMsgObjStruct and tCanTmpMsgObjStruct have the same size. The two types are generated but static.

\ID SBSW_CAN_LL17
\DESCRIPTION Write access to Can_GetCanInterruptOldStatus via reference
\COUNTERMEASURE \N Caller ensures valid pointer.

\ID SBSW_CAN_LL18
\DESCRIPTION Function Call: CanLL_GetFdData with parameter:pointer to address.
\COUNTERMEASURE \T TCASE-448: The parameter are static, code inspection ensures that the variable of type TmpRxMailbox is not written out of bounds. The type is generated but static.

\ID SBSW_CAN_LL19
 \DESCRIPTION Call GetCounterValue with timer value pointers as parameter.
 \COUNTERMEASURE \R parameter channel is a qualified use-case with SATURATION-strategy
                 \T TCASE-448: Code inspection ensures that CAN_LOOP_MAX is > than the biggest value for the "ApplCanTimerStart" defines. CAN_LOOP_MAX is generated but static. 

\ID SBSW_CAN_LL20
 \DESCRIPTION Write access to CAN cell register.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_LL21
 \DESCRIPTION Call of intrinsic function without prototype
 \COUNTERMEASURE \N Function has no parameter, not possible to include compiler header

SBSW_JUSTIFICATION_END */

/* Counter measurement description

\CM_CAN_HL01 A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM_CAN_HL02 Qualified use-case CSL03 of ComStackLib (CanMailbox.ControllerConfigIdx is always in range of controller ControllerData)
\CM_CAN_HL03 A runtime check ensures logObjHandle is in valid range for Can_ActiveSendObject table (Qualified use-case CSL01 of ComStackLib - Can_ActiveSendObject size is extended by CAN_MULTIPLEXED_TX_MAX within generator to allow an access to logObjHandle+CAN_MULTIPLEXED_TX_MAX).
\CM_CAN_HL04 Qualified use-case CSL02 of ComStackLib (size of CanTxBasicDataBuffer == size of ControllerData).
\CM_CAN_HL17 A runtime check ensures DLC index is always smaller than the dimension of CanRxQueueBuffer.data.
\CM_CAN_HL18 A runtime check ensures HRH values is always in range of start stop index of the given mailbox type. (Qualified use-case CSL03 of ComStackLib - start-stop index fit to mailbox entrys)
\CM_CAN_HL19 Static defined size of logTxObjHandlePrioList (muxTx limited to 1 or 3 by preprocessor define), or pointer to this static variable used.
\CM_CAN_HL20 A runtime check ensures size of CanTxBasicDataBuffer (dataByte). For CAN-FD it is checked against the size of the table. For none CAN-FD size is checked against 8 as defined.
\CM_CAN_HL22 A runtime check ensures source index for LoopTimeout array is always smaller than the dimension of LoopTimeout.
\CM_CAN_HL24 A runtime check ensures RxQueue write index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL25 A runtime check ensures RxQueue read index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL28 A runtime check ensures htrh index is always smaller than the dimension of CanMailboxState (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL29 Qualified use-case CSL02 of ComStackLib (size of CanMailboxState == size of CanMailbox) 
\CM_CAN_HL30 Qualified use-case CSL03 of ComStackLib (CanMailbox - CanController Start/Stop HtrhIndex).

*/

/****************************************************************************/
/*  Coverage Justification                                                  */
/****************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CAN_MISRA
  \ACCEPT XF
  \ACCEPT TX
  \REASON only used for MISRA analysis not active in production code.

\ID COV_CAN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xf
  \ACCEPT XF tf tf
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to older AUTOSAR/Component versions. 

\ID COV_CAN_INTERNAL
  \ACCEPT XF
  \ACCEPT TX
  \REASON This switch is always active within CAN driver context. Secure visibility of internal interface and cannot be stimulated to off while test. The code is verified by code inspection.

\ID COV_CAN_USER_CONFIG
  \ACCEPT TX
  \REASON This switch is used to ensure compatibility to none Vector stacks. It will be deactivated on demand in a special integration SIP. The code is verified by code inspection.

\ID COV_CAN_CANCEL_SW_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf xf
  \REASON It is not possible to stimulate a sw cancellation while the message is already start to send when hw cancellation is active. The code is verified by code inspection.

\ID COV_CAN_MICROSAR_VERSION
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TX tx xf
  \ACCEPT TX xf tx
  \ACCEPT TX xf xf
  \ACCEPT TX tx tf
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tx tf
  \ACCEPT TF xf tf
  \ACCEPT TF tf tx
  \REASON The MicroSar version is not changeable in a project. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_MULTI_ECU_CONFIG
  \ACCEPT XF
  \REASON The feature Multiple ECU Configurations is not supported for MSR403 but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_AMD_RUNTIME_MEASUREMENT
  \ACCEPT XF
  \REASON The feature AMD Runtime Measurement is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_DEV_TIMEOUT_DETECT
  \ACCEPT XF
  \REASON The feature Develop Timeout Detect is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_BUSOFF_SUPPORT_API
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature Busoff Support API is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_EXTENDED_STATE_MACHINE
  \ACCEPT XF
  \REASON The feature Extended State Machine is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_DYNAMIC_FULLCAN_ID
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature Dynamic FullCAN ID is always supported for SafeBSW but may be not used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_FINALMAGICNUMBER
  \ACCEPT TX
  \REASON Switch is always true is OK here no side effect will occur when switch is false verified by review.

\ID COV_CAN_SAFE_BSW_EXCLUSION
  \ACCEPT XF xf tx xf tx xf xf xf xf xf xf tx xf tx
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \REASON BUSOFF not stimulated in each configruation. The behavior does not depend on each configuration variant but TCASE-274 takes long runtime and will not be executed for each configuration.   

\ID COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG
  \ACCEPT XF
  \ACCEPT TX
  \REASON Wakeup may be always activated or deactivated depend on configuration. Not all configurations contain activated or deactivated wakeup for at least one controller, but is sufficiantly tested in some configuations with both settings.

---------------- LL ------------------

\ID COV_CAN_GEN_HW_START_STOP_IDX
  \ACCEPT TX
  \REASON The feature GEN_HW_START_STOP is always supported for SafeBSW but may be not used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_PARTIAL_NETWORK
  \ACCEPT XF
  \REASON The feature Partial Network is not supported for SafeBSW but be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.
  
\ID COV_CAN_MULTIPLE_DRIVERS
  \ACCEPT XF
  \ACCEPT TX
  \REASON The feature Multiple CAN drivers is not supported for SafeBSW (BETA feature). A MSSV plugin enforces this configuration for SafeBSW.    

\ID COV_CAN_PROTECTED_MODE
  \ACCEPT XF xf tx
  \ACCEPT XF xf tf
  \ACCEPT XX
  \ACCEPT XF
  \REASON The feature protected mode is not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.  
  
\ID COV_CAN_FIFO_FULL_NOTIFICATION
  \ACCEPT XF
  \REASON The feature FIFO Full notification is developement feature and not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.  
  
\ID COV_CAN_DISABLE_ISR_PROTOTYPE
  \ACCEPT TX
  \REASON The feature "Disable ISR Prototype" is not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.    

\ID COV_CAN_PRIOBYID
  \ACCEPT TX xf xf
  \ACCEPT TX 
  \REASON The feature Prio By CAN ID is default and must not be deactivated for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.    
  
\ID COV_CAN_EQUAL_CHANNEL_LAYOUT
  \ACCEPT TX
  \ACCEPT XF
  \REASON The test is executed on defined channels. The channel layout is equal for each channel.
  
\ID COV_CAN_BUSOFF_NOTIFICATION
  \ACCEPT TF tf tf tf tf xf tf tf tf tf xx tx
  \ACCEPT XF tx xf xx
  \ACCEPT TF tx tf tx
  \REASON Busoff notification is called only for one time, set init flag is mandatory otherwise a hardware failure had happend, in STOP mode no busoff is possible -> defensiv programming
  
\ID COV_CAN_DERIVATIVE_SWITCH
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \REASON Only one derivative can be tested for one time. To check supported derivatives, please look for the "Equivalent Hardware Checklist"

\ID COV_CAN_CANCLOCKDIVIDOR
  \ACCEPT TX
  \REASON Must be defined for ASR4 and SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.
  
\ID COV_CAN_MCR
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TX tf tx
  \REASON Must be defined for Aurix derivates. A MSSV plugin enforces this configuration for SafeBSW.  
  
\ID COV_CAN_SLEEP_SUPPORT
  \ACCEPT XF
  \REASON The feature is platform specific. Tricore does not support sleep/wakeup.

\ID COV_CAN_WAKEUP_SUPPORT
  \ACCEPT XF
  \REASON The feature is platform specific. Tricore does not support sleep/wakeup.

\ID COV_CAN_EMULATE_SLEEP
  \ACCEPT TX
  \ACCEPT TX tf tx
  \ACCEPT TX tx tx
  \ACCEPT TX xf tx
  \ACCEPT XF
  \REASON The feature Emulated Sleep is always supported for SafeBSW but used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_EXTENDED_ID
  \ACCEPT XF
  \ACCEPT TX
  \REASON Lowlevel token is used for for different positions with different preprocessor context.
  
\ID COV_CAN_TX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific.

\ID COV_CAN_RX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific.

\ID COV_CAN_RX_BASICCAN_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific.

\ID COV_CAN_RX_FULLCAN_POLLING
  \ACCEPT TF
  \REASON The feature configuration specific.

\ID COV_CAN_WAKEUP_POLLING
  \ACCEPT XF
  \REASON The feature is platform specific. Tricore does not support sleep/wakeup.
  
\ID COV_CAN_INDIVIDUAL_POLLING
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON Gendata failure OR FullCAN Rx raised the IR and BasicCAN Rx is configured as polling or vice versa.

\ID COV_CAN_GENERIC_CONFIRMATION_API2
  \ACCEPT XF
  \REASON The feature is platform and Project specific.
\ID COV_CAN_HW_TRANSMIT_CANCELLATION
  \ACCEPT XF
  \REASON The feature is platform specific. Tricore does not support cancel.

\ID COV_CAN_COMMON_CAN
  \ACCEPT XF
  \REASON The feature is platform specific. Tricore does not support CommonCAN.

\ID COV_CAN_GENDATA_ERROR
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT XF xf xf
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_MULTIPLE_CELL_MASK
  \ACCEPT XF
  \ACCEPT TX
  \REASON The Hardware message object for multiple cells could only select one cell according to configuration.

\ID COV_CAN_CHANNEL_NOT_USED
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \REASON Depends on configrations, some channels are not used and/or not available in certain derivatives.

\ID COV_CAN_BASICCAN_FULLCAN_FD_TYPE_DIFFER
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON In some configrations Basic CAN and Full CAN are with different FD type (e.g. Basic CAN FD FULL used while Full CAN use FD none). C_ENABLE_CAN_FD_FULL is defined then, which will cause some code not covered during runtime.

\ID COV_CAN_TXINDIRECTIONHWTOLOG
  \ACCEPT XF
  \REASON The feature is platform specific.

\ID COV_CAN_EXTENDED_STATUS
  \ACCEPT TX
  \REASON The feature is platform specific always on or off.

\ID COV_CAN_RxBasicMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific.

\ID COV_CAN_RxFullMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific.

\ID COV_CAN_HARDWARE_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tf tx
  \ACCEPT XF xf xx
  \ACCEPT XF xf
  \ACCEPT TF tf xf
  \ACCEPT TF tf tf xf
  \ACCEPT XF xf tf xf
  \ACCEPT XF xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_FAILURE
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TF tx tf tf
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \ACCEPT TF tx tf
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.  

\ID COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG
  \ACCEPT TF tx tf tf
  \ACCEPT TF tf tx tf
  \ACCEPT TF tf tf tx
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_AURIX_DERIVATIVE
  \ACCEPT TX
  \ACCEPT XF tf tx
  \REASON Code only valid for AURIX derivatives, other derivatives not relevant. A MSSV plugin enforces this configuration for SafeBSW.
  
\ID COV_CAN_COM_STACK_LIB
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Comstacklib is obligatory for SAFE-BSW. Else path needed for compatibility with Canbedded 

\ID COV_CAN_kCanISRPrio
  \ACCEPT XF
  \ACCEPT TX
  \REASON ISR Prio is used or not, not all 15 IR priorities are possible to be varied.
  
\ID COV_CAN_OS_USAGE
  \ACCEPT TX
  \ACCEPT TX xf tx
  \ACCEPT TX tx xf
  \ACCEPT XF
  \ACCEPT XF xf tx
  \ACCEPT XF tf tf
  \REASON OS is used by integration test.

\ID COV_CAN_LOCK_ISR_BY_APPL
  \ACCEPT TX tf tf
  \ACCEPT TF xf tf 
  \REASON CAN interrupts never locked by application only within tests. It is not part of the component test to check application code. The code is verified by code inspection.

\ID COV_CAN_RAM_CHECK
  \ACCEPT TF
  \REASON The feature is platform specific.

\ID COV_CAN_BASICCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TF tx tf
  \ACCEPT TF tx tx
  \REASON Received BasicCAN mailbox is always a valid object and found while search.

\ID COV_CAN_FULLCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received FullCAN mailbox is always a valid object and found while search.

\ID COV_CAN_RAM_CHECK_NO_STIMULATION
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \REASON some configurations do not stimulate RamCheck by test suite, to check the standard CAN driver behaviour.

\ID COV_CAN_INTERRUPT_CONTROL
  \ACCEPT TX
  \ACCEPT TX xf xf
  \REASON Interrupt control is always active. To deactivate this is a non documented, non safety feature. A precompile check ensures that the switch is not set.
  
\ID COV_CAN_NOT_STIMULATEABLE
  \ACCEPT XF xf tf xf
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \REASON some configurations do not stimulate RamCheck by test suite, to check the standard CAN driver behaviour.
  
\ID COV_NISO_PED
  \ACCEPT XF
  \REASON No hardware available yet which supports the feature NISO and PED
  
\ID COV_CAN_VSTDLIB_USE
  \ACCEPT XF
  \ACCEPT TX
  \REASON special usecase, not configurable by generation tool
  
\ID COV_CAN_CORE0_USED
  \ACCEPT TX
  \ACCEPT XF tx xf
  \REASON The test is executed on one defined core. The behaviour of the cores are equal.
  
\ID COV_CAN_HWOBJINDIVPOLLING
  \ACCEPT TF
  \ACCEPT TX
  \REASON The feature is platform specific. For Tricore this is always true if CANFD Full is configured.
 
\ID COV_CAN_SAFE_BSW
  \ACCEPT TF
  \REASON For Safe-BSW this switch may be true or false.
  
\ID COV_CAN_DECISION_NOT_SWITCHABLE_WITHOUT_MULTIPLEBASICCAN
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT X
  \REASON If only one Rx/Tx Basic CAN message is configured, several parameter like object lenght, FIFO size or "polling" can not vary within one configuration.
  
\ID COV_CAN_DOUBLE_RECEPTION
  \ACCEPT XF
  \REASON Second message is received during the first ist actually processed. For test, it is not possible to hit this time slot definitely.
  
\ID COV_CAN_ONLY_TX_INTERRUPT
  \ACCEPT TX
  \REASON If only Tx is configured with interrupt, this decision is always true.

\ID COV_CAN_NO_RXFIFO
  \ACCEPT X
  \REASON If all Rx Basic CAN objects are configured as CANFD Full, no RX Fifo is available.

\ID COV_CAN_TESTSUITE_NOT_APPLICABLE_WITH_LOCKED_IR
  \ACCEPT TX
  \REASON This decision could only be stimulated if testsuite would start up with locked global interrupts, this is not applicable.

\ID COV_CAN_PANNEL_CMD
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf xf
  \REASON CPU needs to wait for CAN during writing a pannel command. This may happen without any delay or not.

\ID COV_CAN_LL_MULTIPLE_CHANNEL_ADDITIONAL_CHECK
  \ACCEPT TX
  \REASON These are additional checks for multiple channel configurations. If single channel applies, these checks are not necessary. 

END_COVERAGE_JUSTIFICATION */ 

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

