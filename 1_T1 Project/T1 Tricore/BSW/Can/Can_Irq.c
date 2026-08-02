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

/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL
#define CAN_IRQ_SOURCE     /* testability */

/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0828 EOF */ /* MD_Can_0828 */
/* PRQA S 0857 EOF */ /* MD_Can_0857 */

#include "Can.h"
#if defined(V_OSTYPE_OSEK) /* COV_CAN_OS_USAGE */
# include "osek.h"
#endif
/* \trace SPEC-1408 */
#if defined(V_OSTYPE_AUTOSAR) /* COV_CAN_OS_USAGE */
# include "Os.h"
#endif

/* ECO_IGNORE_BLOCK_END */

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
/* external declarations and compatibility defines                         */
/***************************************************************************/
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
V_DEF_VAR(extern, uint16, VAR_NOINIT) canActiveIdentityMsk; /* PRQA S 3447,3210 */ /* MD_Can_Asr_3447,MD_Can_Asr_Unused */
V_DEF_VAR(extern, uint8, VAR_NOINIT)  canActiveIdentityLog; /* PRQA S 3447,3210 */ /* MD_Can_Asr_3447,MD_Can_Asr_Unused */

# if defined V_ACTIVE_IDENTITY_MSK
#  undef V_ACTIVE_IDENTITY_MSK  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_MSK                canActiveIdentityMsk
# if defined V_ACTIVE_IDENTITY_LOG
#  undef V_ACTIVE_IDENTITY_LOG  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_LOG                canActiveIdentityLog
#endif

#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_P2CONST (extern, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr; /* PRQA S 3447,3451,3210 */ /* MD_Can_Asr_3447,MD_Can_Asr_3451,MD_Can_Asr_Unused */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/***************************************************************************/
/* Interrupt Service Routine                                               */
/***************************************************************************/
#define CAN_START_SEC_CODE  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* \trace SPEC-1579, SPEC-1395, SPEC-1567 */

#if defined(CAN_GEN_COM_STACK_LIB) /* COV_CAN_COM_STACK_LIB */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
#  define CAN_USE_PHYSTOLOG_MAPPING
# endif
#else
# if defined(C_ENABLE_MULTI_ECU_CONFIG)
#  define CAN_USE_PHYSTOLOG_MAPPING
# endif
#endif

#if defined( C_LL_INTERRUPT_ISR_ACTIVE )
/* **************************************************************************
| NAME:             CanIsr_0
| CALLED BY:        HLL, ASR: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|
|  Attention:  <Name> has to be repleased with the name of the ISR. 
|              Naming conventions: with Name = "", "Rx", "Tx", "RxTx", "Wakeup", "Status" 
|  The name of the ISR will always have a channel index at the end. Even in single channel
|  systems.
************************************************************************** */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_0
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_0 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_0 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_0(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_0), CODE) CanIsr_0(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_0) && (kCanUsedCore_0 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_0) __vector_table(kCanUsedCore_0), CODE) CanIsr_0(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_0), CODE) CanIsr_0(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(0));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_0);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_1
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_1 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_1 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_1(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_1), CODE) CanIsr_1(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_1) && (kCanUsedCore_1 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_1) __vector_table(kCanUsedCore_1), CODE) CanIsr_1(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_1), CODE) CanIsr_1(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(1));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_1);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_2
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_2 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_2 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_2(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_2), CODE) CanIsr_2(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_2) && (kCanUsedCore_2 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_2) __vector_table(kCanUsedCore_2), CODE) CanIsr_2(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_2), CODE) CanIsr_2(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(2));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_2);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_3
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_3 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_3 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_3(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_3), CODE) CanIsr_3(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_3) && (kCanUsedCore_3 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_3) __vector_table(kCanUsedCore_3), CODE) CanIsr_3(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_3), CODE) CanIsr_3(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(3));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_3);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_4
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_4 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_4 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_4(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_4), CODE) CanIsr_4(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_4) && (kCanUsedCore_4 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_4) __vector_table(kCanUsedCore_4), CODE) CanIsr_4(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_4), CODE) CanIsr_4(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(4));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_4);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_5
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_5 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_5 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_5(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_5), CODE) CanIsr_5(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_5) && (kCanUsedCore_5 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_5) __vector_table(kCanUsedCore_5), CODE) CanIsr_5(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_5), CODE) CanIsr_5(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(5));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_5);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_6
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_6 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_6 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_6(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_6), CODE) CanIsr_6(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_6) && (kCanUsedCore_6 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_6) __vector_table(kCanUsedCore_6), CODE) CanIsr_6(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_6), CODE) CanIsr_6(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(6));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_6);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_7
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_7 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_7 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_7(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_7), CODE) CanIsr_7(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_7) && (kCanUsedCore_7 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_7) __vector_table(kCanUsedCore_7), CODE) CanIsr_7(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_7), CODE) CanIsr_7(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(7));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_7);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_8
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_8 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_8 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_8(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_8), CODE) CanIsr_8(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_8) && (kCanUsedCore_8 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_8) __vector_table(kCanUsedCore_8), CODE) CanIsr_8(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_8), CODE) CanIsr_8(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(8));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_8);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_8) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_9
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_9 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_9 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_9(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_9), CODE) CanIsr_9(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_9) && (kCanUsedCore_9 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_9) __vector_table(kCanUsedCore_9), CODE) CanIsr_9(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_9), CODE) CanIsr_9(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(9));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_9);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_9) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_10
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_10 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_10 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_10(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_10), CODE) CanIsr_10(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_10) && (kCanUsedCore_10 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_10) __vector_table(kCanUsedCore_10), CODE) CanIsr_10(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_10), CODE) CanIsr_10(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(10));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_10);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_10) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_11
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_11 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_11 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_11(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_11), CODE) CanIsr_11(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_11) && (kCanUsedCore_11 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_11) __vector_table(kCanUsedCore_11), CODE) CanIsr_11(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_11), CODE) CanIsr_11(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(11));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_11);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_11) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_12
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_12 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_12 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_12(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_12), CODE) CanIsr_12(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_12) && (kCanUsedCore_12 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_12) __vector_table(kCanUsedCore_12), CODE) CanIsr_12(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_12), CODE) CanIsr_12(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(12));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_12);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_12) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_13
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_13 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_13 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_13(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_13), CODE) CanIsr_13(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_13) && (kCanUsedCore_13 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_13) __vector_table(kCanUsedCore_13), CODE) CanIsr_13(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_13), CODE) CanIsr_13(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(13));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_13);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_13) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_14
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_14 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_14 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_14(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_14), CODE) CanIsr_14(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_14) && (kCanUsedCore_14 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_14) __vector_table(kCanUsedCore_14), CODE) CanIsr_14(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_14), CODE) CanIsr_14(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(14));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_14);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_14) */
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanIsr<Name>_15
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if defined( kCanPhysToLogChannelIndex_15 )  /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( C_ENABLE_OSEK_OS_INTCAT2 )
ISR( CanIsr_15 )
#  else /* CAT1 or VOID */
#   if defined(C_ENABLE_ISRVOID)
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_15(void)
#   else /* CAT1 */
#    if defined( C_COMP_TASKING_TRICORE_MULTICAN ) /* COV_CAN_DERIVATIVE_SWITCH */
#     if defined( COMPILER_VERSION_1 )             /* COV_CAN_DERIVATIVE_SWITCH */
V_DEF_FUNC(V_NONE, void _interrupt(kCanISRPrio_15), CODE) CanIsr_15(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#     else
#      if  defined(kCanUsedCore_15) && (kCanUsedCore_15 != 0)  /*ESCAN00078744*/ /* COV_CAN_CORE0_USED */
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_15) __vector_table(kCanUsedCore_15), CODE) CanIsr_15(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      else
V_DEF_FUNC(V_NONE, void __interrupt(kCanISRPrio_15), CODE) CanIsr_15(void) /* PRQA S 3408 */ /* MD_Can_3408_LL_ISR */
#      endif
#     endif
#    endif
#   endif /* CAT1 */
#  endif /* CAT1 or VOID */
{
#  if defined(C_ENABLE_MULTICHANNEL_API) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#   if defined( CAN_USE_PHYSTOLOG_MAPPING ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
  /* call Interrupthandling with identity dependend logical channel */
  CanInterrupt(Can_GetPhysToLogChannel(15));
#   else
  /* call Interrupthandling with logical channel */
  CanInterrupt(kCanPhysToLogChannelIndex_15);
#   endif
#  else
  CanInterrupt( );
#  endif
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_15) */
/* CODE CATEGORY 1 END */

#endif  /* Not a pure polling configuration */

#define CAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
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

