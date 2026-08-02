/*********************************************************************************//*!
*   \file           T1_flexInterface.h
*
*   \brief          T1.flex interface declarations and macros
*
*   \par Visibility
*                   External
*
*   \author nick
*
*   \version 2.5.5.0 r39019
*
*   \copyright GLIWA GmbH embedded systems, Weilheim i.OB. All rights reserved
*************************************************************************************/

#ifndef T1_FLEX_INTERFACE_H_
#define T1_FLEX_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_scopeInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if ! defined T1_TARGET_ADDRESS_TYPE
typedef T1_uint32_t T1_flexAddr_t;
#endif /* defined T1_TARGET_ADDRESS_TYPE */

typedef struct
{
    T1_flexAddr_t begin;
    T1_flexAddr_t end;
} const T1_flexRange_t;

/*! \brief T1.flex global data for one core. */
typedef struct
{
    T1_uint16Least_t        flexBpBudget_;  /* 32-bit type is too expensive on C166 */
    void                  (*pCodeBpBHandler_)( void );
    /* pCodeBpAHandler and pDataBpAHandler are adjacent for targets with 1 code BP. */
    void                  (*pCodeBpAHandler_)( void );
    void                  (*pDataBpAHandler_)( void );
    void                  (*pDataBpAWriteHandler_)( void );
    void                  (*pDataBpBHandler_)( void );
    void                  (*pDataBpBWriteHandler_)( void );
    void                  (*pAfterSwStopAHandler_)( void );
    T1_flexAddr_t          pAfterSwStopAAddr_;
    void                  (*pAfterSwStopBHandler_)( void );
    T1_flexAddr_t          pAfterSwStopBAddr_;
#if defined T1_FLEX_SINGLESTEP
    void                  (*pSavedBpHandler_)( void );
#endif /* defined T1_FLEX_SINGLESTEP */
    T1_uint8Least_t         savedIcuReg_;
    T1_uint8Least_t         savedIcuRegB_;
    T1_uint32_t             hitCounterData_;
    T1_uint32_t             hitCounterCode_;
    T1_uint32_t             minRestrHitCounter_;
    T1_uint32_t             maxRestrHitCounter_;
    T1_uint8_t              stopwatchIdx_;
    T1_uint8_t              lastStopwatchIdx_;
    T1_uint16_t             afterXevents_;
    T1_uint16_t             savedPreemptionCounter_;
    volatile T1_uint16_t    preemptionCounter_;
    T1_uint32_t             currentRestrHitCounter_;
    T1_uint16Least_t        flexAnalysisCapacity_;

    /* duration counters for code breakpoints A and B */
    T1_uint32_t             durationCounterCodeA_;
    T1_uint32_t             durationCounterCodeB_;

    /* duration counter for data breakpoint A */
    T1_uint32_t             durationCounterDataA_;

    T1_uint32_t             flexTxState_;
    T1_flexAddr_t          *pAddrs_;
    T1_uint16Least_t        rwMask_;    /* target-specific read-write mask for data */

#if defined T1_FLEX_SINGLESTEP
    T1_uint32_t             savedStepVal_;
    T1_flexAddr_t           interruptedUEDMAddr_;
#   if defined T1_ARM7R
    T1_uint32_t             savedCRVal_;
    T1_uint16_t             dbgbcrVals[4];
#   elif defined T1_ARM7M
    T1_flexAddr_t           pSavedCodeAddrA_;
    T1_flexAddr_t           pSavedCodeAddrB_;
    T1_uint16_t             savedCodeA_;
    T1_uint16_t             savedCodeB_;
#   endif /* defined T1_ARM7R/T1_ARM7M */
#endif /* defined T1_FLEX_SINGLESTEP */

    T1_uint32_t             runningMeasMask_;

    T1_uint32_t             uedFilterRange_[2][2]; /* 2x min/max */

    T1_flexAddr_t           pDataAddrA_;
    T1_flexAddr_t           pDataAddrB_;
    T1_uint16_t             dataLengthA_;
    T1_uint16_t             dataLengthB_;

    T1_bool_t               restrictNextMeasurement_;
    T1_bool_t               budgetExpired_;
    T1_uint8_t              nofNCAs_;
    T1_uint8_t              flexOverrunState_;

#if defined T1_USE_SCOPE_GLOBALS_PARAM
    T1_scopeGlobals_t      *pFlexScopeGlobals_;
#endif /* defined T1_USE_SCOPE_GLOBALS_PARAM */
#if defined T1_NOF_CORES
    T1_uint8_t              coreId_;
#else /* ! defined T1_NOF_CORES */
    /* False between the start of the measurement and the first stopwatch start */
    T1_bool_t               swStarted_;
#endif /* defined T1_NOF_CORES */
}
T1_flexGlobals_t;

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_FLEX_PLUGIN_ID               (2u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX
/*! \brief T1.flex entry in plugin table. */
#   define T1_flexPlugin                (&T1_flexPluginStruct)
#else
#   define T1_flexPlugin                (T1_DISABLED_PLUGIN)
#endif

#if ! defined T1_CORE_ID_TO_FLEX_GLOBALS
#   if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE
#       if 1 == T1_NOF_CORES
#           define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )    (&T1_flexGlobals0)
#       elif 2 == T1_NOF_CORES
#           define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )    \
            ( ( 0 == (coreId_) ) ? (&T1_flexGlobals0) : (&T1_flexGlobals1) )
#       else
#           define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )    (T1_flexGlobalsPC[coreId_])
#       endif /* T1_NOF_CORES */
#   else /* single core or clone */
#       define T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )        (&T1_flexGlobals)
#   endif /* T1_NOF_CORES */
#endif /* ! defined T1_CORE_ID_TO_FLEX_GLOBALS */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX && defined T1_COUNT_PREEMPTION
/*
 * Increment and decrement are not atomic but it does not matter because interrupts
 * leave T1_preemptionCounter unchanged.
 */
#   define T1_INCR_PREEMPTIONS( te_ )                                   \
        T1_INCR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), te_ )
#   define T1_DECR_PREEMPTIONS( te_ )                                   \
        T1_DECR_PREEMPTIONS_PC( T1_GetCoreIdOffset( ), te_ )
#   define T1_INCR_PREEMPTIONS_PC( coreId_, te_ )                       \
    do                                                                  \
    {                                                                   \
        ++(T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )->preemptionCounter_);  \
        { te_; }                                                        \
    }                                                                   \
    while( 0 )
#   define T1_DECR_PREEMPTIONS_PC( coreId_, te_ )                       \
    do                                                                  \
    {                                                                   \
        { te_; }                                                        \
        --(T1_CORE_ID_TO_FLEX_GLOBALS( coreId_ )->preemptionCounter_);  \
    }                                                                   \
    while( 0 )
#else
#   define T1_INCR_PREEMPTIONS( te_ )               do { te_; } while ( 0 )
#   define T1_DECR_PREEMPTIONS( te_ )               do { te_; } while ( 0 )
#   define T1_INCR_PREEMPTIONS_PC( coreId_, te_ )   do { te_; } while ( 0 )
#   define T1_DECR_PREEMPTIONS_PC( coreId_, te_ )   do { te_; } while ( 0 )
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX && defined T1_COUNT_PREEMPTION */

/*----------------------------------------------------------------------------------*/
/*--- forward declaration of optional callbacks ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN void T1_CODE T1_FlexUedMTriggerOnVal(     T1_nofEntries_t afterXevents,
                                                    T1_uint32_t     writtenValue    );
T1_EXTERN void T1_CODE T1_FlexUedMTriggerOnValPC(   T1_uint8Least_t coreId,
                                                    T1_nofEntries_t afterXevents,
                                                    T1_uint32_t     writtenValue    );
T1_EXTERN T1_uint8Least_t T1_CODE T1_FlexDisallowExternalDebug( void );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_flexPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t        * const T1_SEC_CONST_32 T1_addrsPC[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t                T1_SEC_NO_INIT_32 T1_addrs[];
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t                T1_SEC_NO_INIT_32_CORE0 T1_addrsCore0[];
#   define T1_STOP_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t                T1_SEC_NO_INIT_32_CORE1 T1_addrsCore1[];
#   define T1_STOP_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"
T1_EXTERN T1_flexAddr_t                T1_SEC_NO_INIT_32_CORE2 T1_addrsCore2[];
#   define T1_STOP_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"

#   ifdef T1_MULTICORE_CLONE

#       define T1_START_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t              T1_SEC_NO_INIT_32_CLONE T1_flexGlobals;
#       define T1_STOP_SEC_NO_INIT_32_CLONE
#       include "T1_MemMap.h"

#   else /* !T1_MULTICORE_CLONE */

#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t              T1_SEC_NO_INIT_32 T1_flexGlobals;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"

#   endif /* T1_MULTICORE_CLONE */

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const              T1_SEC_CONST_8 T1_nofAddrs;
T1_EXTERN T1_uint8_t const              T1_SEC_CONST_8 T1_nofAddrsPC[];
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const              T1_SEC_CONST_8 T1_32852;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexRange_t                T1_SEC_CONST_32 T1_33108[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_uint32_t                   T1_SEC_NO_INIT_32 T1_swdStart;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t              T1_SEC_NO_INIT_32_CORE0 T1_flexGlobals0;
#   define T1_STOP_SEC_NO_INIT_32_CORE0
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t              T1_SEC_NO_INIT_32_CORE1 T1_flexGlobals1;
#   define T1_STOP_SEC_NO_INIT_32_CORE1
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t              T1_SEC_NO_INIT_32_CORE2 T1_flexGlobals2;
#   define T1_STOP_SEC_NO_INIT_32_CORE2
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX */

#if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t * const  T1_SEC_CONST_32 T1_flexGlobalsPC[];
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#elif defined T1_MULTICORE_CLONE

#   define T1_START_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t          T1_SEC_NO_INIT_32_CLONE T1_flexGlobals;
#   define T1_STOP_SEC_NO_INIT_32_CLONE
#   include "T1_MemMap.h"

#else

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexGlobals_t          T1_SEC_NO_INIT_32 T1_flexGlobals;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#endif /* T1_NOF_CORES */

/*----------------------------------------------------------------------------------*/
/*--- external function declarations -----------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
T1_EXTERN T1_CODE void T1_FlexOHAddr( T1_uint32_t pAddrStart );
T1_EXTERN T1_CODE void T1_FlexOHAddrPC( T1_uint8Least_t coreId, T1_uint32_t pAddrStart );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#if defined T1_TRICORE

#   if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE

#       define T1_START_SEC_CODE_DMS_CORE0
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore0( void );
#       define T1_STOP_SEC_CODE_DMS_CORE0
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE1
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore1( void );
#       define T1_STOP_SEC_CODE_DMS_CORE1
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE2
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore2( void );
#       define T1_STOP_SEC_CODE_DMS_CORE2
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE3
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore3( void );
#       define T1_STOP_SEC_CODE_DMS_CORE3
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE4
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore4( void );
#       define T1_STOP_SEC_CODE_DMS_CORE4
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE5
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore5( void );
#       define T1_STOP_SEC_CODE_DMS_CORE5
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE6
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore6( void );
#       define T1_STOP_SEC_CODE_DMS_CORE6
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE7
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore7( void );
#       define T1_STOP_SEC_CODE_DMS_CORE7
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE8
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore8( void );
#       define T1_STOP_SEC_CODE_DMS_CORE8
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE9
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore9( void );
#       define T1_STOP_SEC_CODE_DMS_CORE9
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE10
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore10( void );
#       define T1_STOP_SEC_CODE_DMS_CORE10
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE11
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore11( void );
#       define T1_STOP_SEC_CODE_DMS_CORE11
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE12
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore12( void );
#       define T1_STOP_SEC_CODE_DMS_CORE12
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE13
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore13( void );
#       define T1_STOP_SEC_CODE_DMS_CORE13
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_DMS_CORE14
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandlerCore14( void );
#       define T1_STOP_SEC_CODE_DMS_CORE14
#       include "T1_MemMap.h"

#   elif defined T1_MULTICORE_CLONE

#       define T1_START_SEC_CODE_DMS_CLONE
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandler( void );
#       define T1_STOP_SEC_CODE_DMS_CLONE
#       include "T1_MemMap.h"

#   else /* single core */

#       define T1_START_SEC_CODE_DMS
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_OuterExceptionHandler( void );
#       define T1_STOP_SEC_CODE_DMS
#       include "T1_MemMap.h"

#   endif /* defined T1_NOF_CORES */

#endif /* defined T1_TRICORE */

#endif /* T1_FLEX_INTERFACE_H_ */
